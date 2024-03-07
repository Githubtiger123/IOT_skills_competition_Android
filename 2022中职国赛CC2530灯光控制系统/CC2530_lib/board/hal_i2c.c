//=============================================================================
//    S E N S I R I O N
//=============================================================================
// Project   :  SHT3x Sample Code (V1.1)
// File      :  i2c_hal.c (V1.1)
// Brief     :  I2C驱动程序
//=============================================================================

//-- Includes -----------------------------------------------------------------
#include <ioCC2530.h>
#include "hal_i2c.h"

//-- Defines ------------------------------------------------------------------
/*
I2C总线
p1.5-scl
p1.6-sda
*/

#define I2C_IO_DIR_OUTPUT(port, pin)      st( P##port##SEL &= ~BM(pin); P##port##DIR |= BM(pin); )
#define I2C_IO_WRITE(port, pin, val)      st( P##port##_##pin## = val; )
#define I2C_IO_DIR_INPUT(port, pin, func) st( \
                                               P##port##SEL &= ~BM(pin); \
                                               P##port##DIR &= ~BM(pin); \
                                               switch (func) \
                                               { \
                                                 case MCU_IO_PULLUP: P##port##INP &= ~BM(pin); P2INP &= ~BM(port + 5); break; \
                                                 case MCU_IO_PULLDOWN: P##port##INP &= ~BM(pin); P2INP |= BM(port + 5); break; \
                                                 default: P##port##INP |= BM(pin); break; \
                                               } )
#define I2C_IO_READ(port, pin)            (P##port## & BM(pin))

#define I2C_SCL_DIR_OUT()                 I2C_IO_DIR_OUTPUT(1, 6)
#define I2C_SCL_HIGH()                    I2C_IO_WRITE(1, 6, 1)// set SCL to open-drain 置高电平
#define I2C_SCL_LOW()                     I2C_IO_WRITE(1, 6, 0)// set SCL to low 置低电平
#define I2C_SCL_DIR_IN()                  I2C_IO_DIR_INPUT(1, 6, 2)
#define I2C_SCL_READ()                    I2C_IO_READ(1, 6)     // read SCL

#define I2C_SDA_DIR_OUT()                 I2C_IO_DIR_OUTPUT(1, 5)
#define I2C_SDA_HIGH()                    I2C_IO_WRITE(1, 5, 1)// set SDA to open-drain 置高电平
#define I2C_SDA_LOW()                     I2C_IO_WRITE(1, 5, 0)// set SDA to low 置低电平
#define I2C_SDA_DIR_IN()                  I2C_IO_DIR_INPUT(1, 5, 2)
#define I2C_SDA_READ()                    I2C_IO_READ(1, 5) // read SDA

#define I2C_INPUT  1//置成输入
#define I2C_OUTPUT 0//置成输出

//-- Static function prototypes -----------------------------------------------
static etError I2c_WaitWhileClockStreching(uint8 timeout);

//-----------------------------------------------------------------------------
void I2c_sdaInOutInit(uint8 InOut)                      /* -- 根据硬件平台进行修改，初始化SDA引脚，InOut-1输入，InOut-0输出 -- */
{
  /*Configure GPIO pins*/
  if(InOut != I2C_INPUT)
  {
    I2C_SDA_DIR_OUT();
  }
  else
  {
    I2C_SDA_DIR_IN();
  }
}

void I2c_SclInOutInit(uint8 InOut)                      /* -- 根据硬件平台进行修改，初始化SCL引脚，InOut-1输入，InOut-0输出 -- */
{
  /*Configure GPIO pins*/
  if(InOut != I2C_INPUT)
  {
    I2C_SCL_DIR_OUT();
  }
  else
  {
    I2C_SCL_DIR_IN();
  }
}

void I2c_Init(void)                      /* -- adapt the init for your uC -- */
{
#if 0
    //初始化I2C总线IO口SDA、SCL
    ;
    ;
    I2C_SDA_HIGH();                  // I2C-bus idle mode SDA released
    I2C_SCL_HIGH();                  // I2C-bus idle mode SCL released

    // SDA
    // SCL
    // set open-drain output for SDA and SCL 
    //SDA、SCL设置为漏极开路
    ;
    ;
#else
  I2C_SCL_DIR_OUT();
  I2C_SDA_DIR_OUT();
  I2C_SCL_HIGH();
  I2C_SDA_HIGH();
#endif
}

//-----------------------------------------------------------------------------
void I2c_StartCondition(void)
{
    I2C_SDA_HIGH();
    DelayMicroSeconds(1);
    I2C_SCL_HIGH();
    DelayMicroSeconds(1);
    I2C_SDA_LOW();
    DelayMicroSeconds(10);  // hold time start condition (t_HD;STA)
    I2C_SCL_LOW();
    DelayMicroSeconds(10);
}

//-----------------------------------------------------------------------------
void I2c_StopCondition(void)
{
    I2C_SCL_LOW();
    DelayMicroSeconds(1);
    I2C_SDA_LOW();
    DelayMicroSeconds(1);
    I2C_SCL_HIGH();
    DelayMicroSeconds(10);  // set-up time stop condition (t_SU;STO)
    I2C_SDA_HIGH();
    DelayMicroSeconds(10);
}

//-----------------------------------------------------------------------------
etError I2c_WriteByte(uint8 txByte)
{
    etError error = NO_ERROR;
    uint8     mask;
    for(mask = 0x80; mask > 0; mask >>= 1)// shift bit for masking (8 times)
    {
        if((mask & txByte) == 0) I2C_SDA_LOW(); // masking txByte, write bit to SDA-Line
        else                     I2C_SDA_HIGH();
        DelayMicroSeconds(1);               // data set-up time (t_SU;DAT)
        I2C_SCL_HIGH();                         // generate clock pulse on SCL
        DelayMicroSeconds(5);               // SCL high time (t_HIGH)
        I2C_SCL_LOW();
        DelayMicroSeconds(1);               // data hold time(t_HD;DAT)
    }
    I2C_SDA_HIGH();                           // release SDA-line
    I2C_SCL_HIGH();                           // clk #9 for ack
    DelayMicroSeconds(1);                 // data set-up time (t_SU;DAT)
    I2c_sdaInOutInit(I2C_INPUT);          //SDA置为输入
    if(I2C_SDA_READ()) error = ACK_ERROR;       // check ack from i2c slave
    I2C_SCL_LOW();
    DelayMicroSeconds(20);                // wait to see byte package on scope
    I2c_sdaInOutInit(I2C_OUTPUT);         //SDA置为输出
    return error;                         // return error code
}

//-----------------------------------------------------------------------------
etError I2c_ReadByte(uint8 *rxByte, etI2cAck ack, uint8 timeout)
{
    etError error = NO_ERROR;
    uint8 mask;
    *rxByte = 0x00;
    I2C_SDA_HIGH();                            // release SDA-line
    I2c_sdaInOutInit(I2C_INPUT);           //SDA置为输入
    for(mask = 0x80; mask > 0; mask >>= 1) // shift bit for masking (8 times)
    {
        I2C_SCL_HIGH();                          // start clock on SCL-line
        DelayMicroSeconds(1);                // clock set-up time (t_SU;CLK)
        error = I2c_WaitWhileClockStreching(timeout);// wait while clock streching
        DelayMicroSeconds(3);                // SCL high time (t_HIGH)
        if(I2C_SDA_READ()) *rxByte |= mask;        // read bit
        I2C_SCL_LOW();
        DelayMicroSeconds(1);                // data hold time(t_HD;DAT)
    }
    I2c_sdaInOutInit(I2C_OUTPUT);          //SDA置为输出
    if(ack == ACK) I2C_SDA_LOW();              // send acknowledge if necessary
    else           I2C_SDA_HIGH();
    DelayMicroSeconds(1);                  // data set-up time (t_SU;DAT)
    I2C_SCL_HIGH();                            // clk #9 for ack
    DelayMicroSeconds(5);                  // SCL high time (t_HIGH)
    I2C_SCL_LOW();
    I2C_SDA_HIGH();                            // release SDA-line
    DelayMicroSeconds(20);                 // wait to see byte package on scope

    return error;                          // return with no error
}

//-----------------------------------------------------------------------------
etError I2c_GeneralCallReset(void)
{
    etError error;

    I2c_StartCondition();
    error = I2c_WriteByte(0x00);
    if(error == NO_ERROR) error = I2c_WriteByte(0x06);

    return error;
}

//-----------------------------------------------------------------------------
void DelayMicroSeconds(uint32 nbrOfUs)   /* -- adapt this delay for your uC -- */
{
  uint32 i;
  for(i = 0; i < nbrOfUs; i++)
  {
    asm("NOP");  // nop's may be added or removed for timing adjustment
    asm("NOP");  
    asm("NOP");  
    asm("NOP");
  }
}

//-----------------------------------------------------------------------------
static etError I2c_WaitWhileClockStreching(uint8 timeout)
{
    etError error = NO_ERROR;
    I2c_SclInOutInit(I2C_INPUT);          //SCL置为输入
    while(I2C_SCL_READ() == 0)
    {
        if(timeout-- == 0) return TIMEOUT_ERROR;
        DelayMicroSeconds(1000);
    }
    I2c_SclInOutInit(I2C_OUTPUT);         //SCL置为输出
    return error;
}
