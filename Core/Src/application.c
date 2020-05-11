#include "main.h"
#include "application.h"


void application_init(){
	c=0;
	status=0;
	for (int i=0;i<ARRAYSIZE;i++){
		ADC_values[i]=33+i;
		ADC_Work_Buffer[i]=33+i;
	}


	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC_values, ARRAYSIZE); //Start the conversion
	channels[0] = 10;
	channels[1] = 10;
	channels[2] = 10;
	channels[3] = 10;
	channels[4] = 10;
	channels[5] = 10;
	channels[6] = 10;
	channels[7] = 10;
	channels[8] = 10;
	channels[9] = 10;

	keys[0] = 38; //Snare
	keys[1] = 50; //Hi-Tom
	keys[2] = 48; //Hi mid tom
	keys[3] = 47; //Lo mid tom
	keys[4] = 45; //lo tom
	keys[5] = 43; //hi floor tom
	keys[6] = 41; //lo floor tom
	keys[7] = 49; //crash cymb 1
	keys[8] = 51; //ride cynb 1
	keys[9] = 57; //crash cymb 2
}
void application_loop(){
	if(status==1){
		ADC_process();
		status=0;
	}
}
void application_DMA_IRQ_Callback(){
	for(int i=0;i<ARRAYSIZE;i++){
		ADC_Work_Buffer[i] = ADC_values[i];
	}
	status=1;
}
void ADC_process(void) {
	static uint16_t c[ARRAYSIZE], ADC_oldvalues[ARRAYSIZE];
	for (int i = 0; i < ARRAYSIZE; i++) {
		if (c[i] > 0) {
			c[i]--;
			continue;
		}
		if (ADC_Work_Buffer[i] > TRIG && ADC_Work_Buffer[i] < ADC_oldvalues[i]) {
			trigger(i, ADC_Work_Buffer[i]);
			c[i] = 10;
			ADC_oldvalues[i] = 0;
			continue;
		}
		else
			ADC_oldvalues[i] = ADC_Work_Buffer[i];
	}
}


void trigger(int cuerpo, int veloc) {

	static uint8_t fullCommand[3];
	fullCommand[0] = channels[cuerpo] 	| 0x90;
	fullCommand[1] = keys[cuerpo] 		& 0x7f;
	fullCommand[2] = veloc 				& 0x7f;
	HAL_UART_Transmit_DMA(&huart3, fullCommand, sizeof(fullCommand));
	return;
}
