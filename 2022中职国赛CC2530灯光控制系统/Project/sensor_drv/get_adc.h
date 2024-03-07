/*************************************************************************************************
  Filename:      adc.h
 
 *****/


#ifndef SIMPLE_adc_H
#define SIMPLE_adc_H

#define ACH1    0
#define ACH2    4
#define ACH3    5
#define ACH4    6


extern  void hal_adc_Init(void); 
extern  float readAdc(void);

extern  void hal_adc4CH_Init(void);
extern  float readAdc4CH(uint8 ch);
#endif


