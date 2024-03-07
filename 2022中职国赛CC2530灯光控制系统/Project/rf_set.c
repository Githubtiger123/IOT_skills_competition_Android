#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_rf.h"
#include "basic_rf.h"
#include "hal_uart.h" 
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


#define SW1 P1_2
#define SW2 P0_1
#define TT 400  //双击检测周期

#define Lamp P2_0
#define Fan P1_7
/*
Key1_count : K1的状态
1：按下1次
2：按下2次
3：按下3次
4：双击一次
*/
unsigned int Key1_count = 0;
/*
Key2_count : K2的状态
1：按下1次
2：按下2次
4：双击一次
*/
unsigned int Key2_count = 0;
/*****点对点通讯地址设置******/


#define RF_CHANNEL                0         // 频道 11~26
#define PAN_ID                    0x0     //网络id 
#define MY_ADDR                   0x0     //本机模块地址
#define SEND_ADDR                 0x0     //发送地址

/**************************************************/
static basicRfCfg_t basicRfConfig;
// 无线RF初始化
void ConfigRf_Init(void)
{
  
    basicRfConfig.panId       =   PAN_ID;
    basicRfConfig.channel     =   RF_CHANNEL;
    basicRfConfig.myAddr      =   MY_ADDR;
    basicRfConfig.ackRequest  =   TRUE;
    while(basicRfInit(&basicRfConfig) == FAILED);
    basicRfReceiveOn();
 
}

//GPIO 初始化
void InitGpio(){

  P1SEL &= ~(0x01|0x01<<1|0x01<<2|0x01<<3|0x01<<4);
  P1DIR &= ~(0x01<<2);
  P1DIR |= (0x01|0x01<<1|0x01<<3|0x01<<4);
  P0SEL &= ~(0x01<<1);
  P0DIR &= ~(0x01<<1);
  P1 = 0;
  P1SEL &= ~(0x01<<7);
  P2SEL &= ~(0x01);
  P1DIR |= (0x01<<7);
  P2DIR |= (0x01);
  Fan = 0;
  Lamp = 0;
}

unsigned int Scan_count1 = 0;//Scan_count1,Scan_count2是检测双击周期实际执行数
unsigned int Scan_count2 = 0;
void Key_Scan(){

//  SW1单击双击检测函数
  if(SW1 == 0){
  
    halMcuWaitMs(10);
    if(SW1 == 0){
    
      while(SW1 == 0);
      
      while(Scan_count1<TT){
      
        halMcuWaitMs(1);
        Scan_count1++;
        if(SW1 == 0){
        
          halMcuWaitMs(10);
          if(SW1 == 0){
          
            while(SW1 == 0);
            Key1_count = 4;//若是双击则将标志位Key1_count改为4
            Scan_count1 = 0;//重新统计双击周期
            break;
          }
        }
      }
      if(Scan_count1>=TT){
      
        Key1_count++;   //每次点击Key1_count标志位加一
        if(Key1_count>3){Key1_count = 1;}//大于3清为1
        Scan_count1 = 0;//重新统计双击周期
      }
    }
  }
//  SW2单击双击检测函数 
  if(SW2 == 0){
  
    halMcuWaitMs(10);
    if(SW2 == 0){
    
      while(SW2 == 0);
      while(Scan_count2<TT){
      
        Scan_count2++;
        halMcuWaitMs(1);
        if(SW2 == 0){
        
          halMcuWaitMs(10);
          if(SW2 == 0){
          
            while(SW2 == 0);
            Key2_count = 4;//若是双击则将标志位Key2_count改为4
            Scan_count2 = 0;//重新统计双击周期
            break;
          }
        }
      }
      if(Scan_count2>=TT){
      
        Key2_count++;//每次点击Key2_count标志位加一
        if(Key2_count>2){Key2_count = 1;}//大于2清为1
        Scan_count2 = 0;//重新统计双击周期
      }
    }
  }
 
}

//定时器初始化
void InitTimer(){ 

  T1CC0L = 0xfa;
  T1CC0H = 0x0;
  
  T1CCTL0 |= 0x01<<2;
  
  T1IE = 1;
  EA = 1;
  TIMIF |= 0x01<<6;
  
  T1CTL |= 0x0e;
}

//RGB设置绿色
void RGBSetGreen(){

  unsigned char arr[] = {0xA5,0x06,0x00,0xA0,0x00,0xFF,0x00,0xEE,0x5A};
  halUartWrite(arr,sizeof(arr));
}
//RGB设置红色
void RGBSetRed(){

  unsigned char arr[] = {0xA5,0x06,0x00,0xA0,0xFF,0x00,0x00,0xEE,0x5A};
  halUartWrite(arr,sizeof(arr));
}
//RGB设置蓝色
void RGBSetBlue(){

  unsigned char arr[] = {0xA5,0x06,0x00,0xA0,0x00,0x00,0xFF,0xEE,0x5A};
  halUartWrite(arr,sizeof(arr));
}
//复位RGB
void RGBSetClear(){

  unsigned char arr[] = {0xA5,0x06,0x00,0xA0,0x00,0x00,0x00,0xEE,0x5A};
  halUartWrite(arr,sizeof(arr));
}


unsigned char LedLink = 0; //Led是否闪烁标志位 (D3,D4)->(D5,D6) ，SW2点击控制
unsigned char isLink = 0; //是否开启RGB和LED流水灯标志位 ，SW1长按控制
unsigned int Timer_count = 0;//定时器计数标志位

//定时器中断函数
#pragma vector = T1_VECTOR
__interrupt void T1_INT(){

  T1STAT &=~ (0x01);//清中断
  Timer_count++;//计数加一
  
  //处理SW1双击闪烁
    if(isLink){ //如果Led和RGB流水灯标志位是1则开启Led和RGB流水灯
    
      switch(Timer_count){ //根据时间判断控制流水(因为定时器不可以加延时函数)
      
          case 200:
          P1 = 0;P1_1 = 1;RGBSetRed();
          break;
          case 400:
          P1 = 0;P1_0 = 1;RGBSetGreen();
          break;
          case 600:
          P1 = 0;P1_4 = 1;RGBSetBlue();
          break;
          case 800:
          P1 = 0;P1_3 = 1;
          isLink = 0; //流水一次之后判断是否继续流水(其他案件是否按下)
          break;
      }
  }
  
  //处理SW2单击闪烁
      if(LedLink){//如果Led闪烁(D3,D4)->(D5,D6)标志位是1则开启闪烁(D3,D4)->(D5,D6)
    
      switch(Timer_count){//根据时间判断控制闪烁(因为定时器不可以加延时函数)
      
        case 200:
          P1 = 0;halLedSet(1);halLedSet(2);
          break;
        case 400:
          P1 = 0;halLedSet(3);halLedSet(4);
          LedLink = 0;
          break;//流水一周期之后判断是否继续闪烁(其他按键是否按下)
      }
    }
    if(Timer_count>800)Timer_count = 0;//重新计数
}
/********************MAIN************************/
void main(void)
{
    halBoardInit();//选手不得在此函数内添加代码
    ConfigRf_Init();//选手不得在此函数内添加代码
    InitGpio();
    InitTimer();
    halMcuWaitMs(200);//等待初始化
    while(1)
    {
    /* user code start */
     Key_Scan();    //扫描按键状态
     switch(Key1_count){ //判断按键状态,并执行操作
      
        case 1:
          if(Key2_count != 0){Key2_count = 0;}//将SW2控制标志位置0,避免冲突
          P1 = 0;P1_1 = 1; //控制LED,RGB灯
          RGBSetRed();
          halMcuWaitMs(100);//等待串口发送RGB处理完成
        break;
        case 2:
          if(Key2_count != 0){Key2_count = 0;}//将SW2控制标志位置0,避免冲突
          P1 = 0;P1_0 = 1;    //控制LED,RGB灯
          RGBSetGreen();
          halMcuWaitMs(100);     //等待串口发送RGB处理完成     
        break;
        case 3:
          if(Key2_count != 0){Key2_count = 0;}//将SW2控制标志位置0,避免冲突
          P1 = 0;P1_4 = 1;  //控制LED,RGB灯
          RGBSetBlue();
          halMcuWaitMs(100);  //等待串口发送RGB处理完成   
        break;
        case 4:
          if(Key2_count != 0){Key2_count = 0;}//将SW2控制标志位置0,避免冲突
          isLink = 1; //将LED，RGB流水灯标志位打开,在定时器中处理流水灯
        break;
        
      }
     Key_Scan();  //扫描按键状态 扫描两次避免死锁
     switch(Key2_count){  //判断按键状态,并执行操作
      
        case 1:
          if(Key1_count != 0){Key1_count = 0;}//将SW1控制标志位置0,避免冲突
          LedLink = 1; //控制灯泡风扇,LED灯
          Lamp = 1;Fan = 0;
        break;
        case 2:
          if(Key1_count != 0){Key1_count = 0;}//将SW1控制标志位置0,避免冲突
          LedLink = 0;  //控制灯泡风扇,LED灯
          P1 = 0xff;
          Lamp = 0;Fan = 1;
        break;
        case 4:
          if(Key1_count != 0){Key1_count = 0;}//将SW1控制标志位置0,避免冲突
          P1 = 0; //熄灭所有
          LedLink = 0;
          Lamp = 0;Fan = 0;
          RGBSetClear();
          halMcuWaitMs(100);//等待串口发送RGB处理完成  
        break;
      }
     
    /* user code end */
    }
}