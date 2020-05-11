/*
 * application.h
 *
 *  Created on: May 10, 2020
 *      Author: Joaquin
 */

#ifndef SRC_APPLICATION_H_
#define SRC_APPLICATION_H_

#define ARRAYSIZE 9
#define TRIG 200
uint16_t ADC_values[ARRAYSIZE], ADC_Work_Buffer[ARRAYSIZE];
uint32_t status;
uint8_t channels[9],keys[9];
int c;

void ADC_process();
void trigger(int, int);
void application_init();
void application_loop();
void application_DMA_IRQ_Callback();
int DebugWrite(uint8_t* str);

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart3;
#endif /* SRC_APPLICATION_H_ */
