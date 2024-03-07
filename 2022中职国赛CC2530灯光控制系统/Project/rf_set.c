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
#define TT 400  //˫���������

#define Lamp P2_0
#define Fan P1_7
/*
Key1_count : K1��״̬
1������1��
2������2��
3������3��
4��˫��һ��
*/
unsigned int Key1_count = 0;
/*
Key2_count : K2��״̬
1������1��
2������2��
4��˫��һ��
*/
unsigned int Key2_count = 0;
/*****��Ե�ͨѶ��ַ����******/


#define RF_CHANNEL                0         // Ƶ�� 11~26
#define PAN_ID                    0x0     //����id 
#define MY_ADDR                   0x0     //����ģ���ַ
#define SEND_ADDR                 0x0     //���͵�ַ

/**************************************************/
static basicRfCfg_t basicRfConfig;
// ����RF��ʼ��
void ConfigRf_Init(void)
{
  
    basicRfConfig.panId       =   PAN_ID;
    basicRfConfig.channel     =   RF_CHANNEL;
    basicRfConfig.myAddr      =   MY_ADDR;
    basicRfConfig.ackRequest  =   TRUE;
    while(basicRfInit(&basicRfConfig) == FAILED);
    basicRfReceiveOn();
 
}

//GPIO ��ʼ��
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

unsigned int Scan_count1 = 0;//Scan_count1,Scan_count2�Ǽ��˫������ʵ��ִ����
unsigned int Scan_count2 = 0;
void Key_Scan(){

//  SW1����˫����⺯��
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
            Key1_count = 4;//����˫���򽫱�־λKey1_count��Ϊ4
            Scan_count1 = 0;//����ͳ��˫������
            break;
          }
        }
      }
      if(Scan_count1>=TT){
      
        Key1_count++;   //ÿ�ε��Key1_count��־λ��һ
        if(Key1_count>3){Key1_count = 1;}//����3��Ϊ1
        Scan_count1 = 0;//����ͳ��˫������
      }
    }
  }
//  SW2����˫����⺯�� 
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
            Key2_count = 4;//����˫���򽫱�־λKey2_count��Ϊ4
            Scan_count2 = 0;//����ͳ��˫������
            break;
          }
        }
      }
      if(Scan_count2>=TT){
      
        Key2_count++;//ÿ�ε��Key2_count��־λ��һ
        if(Key2_count>2){Key2_count = 1;}//����2��Ϊ1
        Scan_count2 = 0;//����ͳ��˫������
      }
    }
  }
 
}

//��ʱ����ʼ��
void InitTimer(){ 

  T1CC0L = 0xfa;
  T1CC0H = 0x0;
  
  T1CCTL0 |= 0x01<<2;
  
  T1IE = 1;
  EA = 1;
  TIMIF |= 0x01<<6;
  
  T1CTL |= 0x0e;
}

//RGB������ɫ
void RGBSetGreen(){

  unsigned char arr[] = {0xA5,0x06,0x00,0xA0,0x00,0xFF,0x00,0xEE,0x5A};
  halUartWrite(arr,sizeof(arr));
}
//RGB���ú�ɫ
void RGBSetRed(){

  unsigned char arr[] = {0xA5,0x06,0x00,0xA0,0xFF,0x00,0x00,0xEE,0x5A};
  halUartWrite(arr,sizeof(arr));
}
//RGB������ɫ
void RGBSetBlue(){

  unsigned char arr[] = {0xA5,0x06,0x00,0xA0,0x00,0x00,0xFF,0xEE,0x5A};
  halUartWrite(arr,sizeof(arr));
}
//��λRGB
void RGBSetClear(){

  unsigned char arr[] = {0xA5,0x06,0x00,0xA0,0x00,0x00,0x00,0xEE,0x5A};
  halUartWrite(arr,sizeof(arr));
}


unsigned char LedLink = 0; //Led�Ƿ���˸��־λ (D3,D4)->(D5,D6) ��SW2�������
unsigned char isLink = 0; //�Ƿ���RGB��LED��ˮ�Ʊ�־λ ��SW1��������
unsigned int Timer_count = 0;//��ʱ��������־λ

//��ʱ���жϺ���
#pragma vector = T1_VECTOR
__interrupt void T1_INT(){

  T1STAT &=~ (0x01);//���ж�
  Timer_count++;//������һ
  
  //����SW1˫����˸
    if(isLink){ //���Led��RGB��ˮ�Ʊ�־λ��1����Led��RGB��ˮ��
    
      switch(Timer_count){ //����ʱ���жϿ�����ˮ(��Ϊ��ʱ�������Լ���ʱ����)
      
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
          isLink = 0; //��ˮһ��֮���ж��Ƿ������ˮ(���������Ƿ���)
          break;
      }
  }
  
  //����SW2������˸
      if(LedLink){//���Led��˸(D3,D4)->(D5,D6)��־λ��1������˸(D3,D4)->(D5,D6)
    
      switch(Timer_count){//����ʱ���жϿ�����˸(��Ϊ��ʱ�������Լ���ʱ����)
      
        case 200:
          P1 = 0;halLedSet(1);halLedSet(2);
          break;
        case 400:
          P1 = 0;halLedSet(3);halLedSet(4);
          LedLink = 0;
          break;//��ˮһ����֮���ж��Ƿ������˸(���������Ƿ���)
      }
    }
    if(Timer_count>800)Timer_count = 0;//���¼���
}
/********************MAIN************************/
void main(void)
{
    halBoardInit();//ѡ�ֲ����ڴ˺�������Ӵ���
    ConfigRf_Init();//ѡ�ֲ����ڴ˺�������Ӵ���
    InitGpio();
    InitTimer();
    halMcuWaitMs(200);//�ȴ���ʼ��
    while(1)
    {
    /* user code start */
     Key_Scan();    //ɨ�谴��״̬
     switch(Key1_count){ //�жϰ���״̬,��ִ�в���
      
        case 1:
          if(Key2_count != 0){Key2_count = 0;}//��SW2���Ʊ�־λ��0,�����ͻ
          P1 = 0;P1_1 = 1; //����LED,RGB��
          RGBSetRed();
          halMcuWaitMs(100);//�ȴ����ڷ���RGB�������
        break;
        case 2:
          if(Key2_count != 0){Key2_count = 0;}//��SW2���Ʊ�־λ��0,�����ͻ
          P1 = 0;P1_0 = 1;    //����LED,RGB��
          RGBSetGreen();
          halMcuWaitMs(100);     //�ȴ����ڷ���RGB�������     
        break;
        case 3:
          if(Key2_count != 0){Key2_count = 0;}//��SW2���Ʊ�־λ��0,�����ͻ
          P1 = 0;P1_4 = 1;  //����LED,RGB��
          RGBSetBlue();
          halMcuWaitMs(100);  //�ȴ����ڷ���RGB�������   
        break;
        case 4:
          if(Key2_count != 0){Key2_count = 0;}//��SW2���Ʊ�־λ��0,�����ͻ
          isLink = 1; //��LED��RGB��ˮ�Ʊ�־λ��,�ڶ�ʱ���д�����ˮ��
        break;
        
      }
     Key_Scan();  //ɨ�谴��״̬ ɨ�����α�������
     switch(Key2_count){  //�жϰ���״̬,��ִ�в���
      
        case 1:
          if(Key1_count != 0){Key1_count = 0;}//��SW1���Ʊ�־λ��0,�����ͻ
          LedLink = 1; //���Ƶ��ݷ���,LED��
          Lamp = 1;Fan = 0;
        break;
        case 2:
          if(Key1_count != 0){Key1_count = 0;}//��SW1���Ʊ�־λ��0,�����ͻ
          LedLink = 0;  //���Ƶ��ݷ���,LED��
          P1 = 0xff;
          Lamp = 0;Fan = 1;
        break;
        case 4:
          if(Key1_count != 0){Key1_count = 0;}//��SW1���Ʊ�־λ��0,�����ͻ
          P1 = 0; //Ϩ������
          LedLink = 0;
          Lamp = 0;Fan = 0;
          RGBSetClear();
          halMcuWaitMs(100);//�ȴ����ڷ���RGB�������  
        break;
      }
     
    /* user code end */
    }
}