#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "sc16is750.h"

void int_signal(void){
	printf("Signal-A\n");
}


int main(int argc, char **argv){

	SC16IS750_t dev;
	
	if (argc < 3) {
		printf("USAGE:\n");
		printf("\t%s I2C i2c_address : For I2C\n", argv[0]);
		printf("\t%s SPI chip_select : For SPI\n", argv[0]);
		return 1;
	}
	
	if (strcmp(argv[1], "I2C") == 0) {
		long i2c_address = strtol(argv[2], NULL, 16);
		printf("i2c_addressr=%x\n", (uint8_t)i2c_address);
		SC16IS750_init(&dev, SC16IS750_PROTOCOL_I2C, (uint8_t)i2c_address);
	} else if (strcmp(argv[1], "SPI") == 0) {
		long chip_select = strtol(argv[2], NULL, 10);
		printf("chip_select=%ld\n", chip_select);
		SC16IS750_init(&dev, SC16IS750_PROTOCOL_SPI, (uint8_t)chip_select);
	} else {
		printf("USAGE:\n");
		printf("\t%s I2C i2c_address : For I2C\n", argv[0]);
		printf("\t%s SPI chip_select : For SPI\n", argv[0]);
		return 1;
	}

	// wiringPi Initialization
	if(wiringPiSetup() == -1) {
		printf("wiringPiSetup Fail\n");
		return 1;
	}

	// SC16IS750 Initialization
	SC16IS750_begin(&dev, SC16IS750_DEFAULT_SPEED, 14745600UL); //baudrate&frequency setting
	if (SC16IS750_ping(&dev)!=1) {
		printf("device not found\n");
		return 1;
	} else {
		printf("device found\n");
	}

	// Set Interrupt
	int interrupu = 16;
	pinMode(interrupu, INPUT);
	pullUpDnControl(interrupu, PUD_UP);
	wiringPiISR(interrupu,INT_EDGE_BOTH,  &int_signal  );

	int gpio = 2;
	SC16IS750_pinMode(&dev, gpio, INPUT);

#if 0
	uint8_t temp_ier;
	temp_ier = SC16IS750_ReadRegister(&dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IER);
	printf("temp_ier=%x\n", temp_ier);
	temp_ier = temp_ier | 0x08;
	SC16IS750_WriteRegister(&dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IER, temp_ier);
	temp_ier = SC16IS750_ReadRegister(&dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IER);
	printf("temp_ier=%x\n", temp_ier);
#endif

#if 1
	uint8_t temp_ioint;
	temp_ioint = SC16IS750_ReadRegister(&dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOINTENA);
	printf("temp_ioint=%x\n", temp_ioint);
	uint8_t mask = 0x01 << gpio;
	printf("mask=%x\n",mask);
	temp_ioint = temp_ioint | mask;
	SC16IS750_WriteRegister(&dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOINTENA, temp_ioint);
	temp_ioint = SC16IS750_ReadRegister(&dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOINTENA);
	printf("temp_ioint=%x\n", temp_ioint);
#endif

	uint8_t prev_iir = 0;
	uint8_t prev_iostate = 0;
	while (1) {

#if 1
		uint8_t current_iir;
		current_iir = SC16IS750_ReadRegister(&dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IIR);
		if (prev_iir != current_iir) {
			printf("current_iir=%x->%x\n", prev_iir, current_iir);
		}
		prev_iir = current_iir;

		uint8_t current_iostate;
		current_iostate = SC16IS750_ReadRegister(&dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOSTATE);
		if (prev_iostate != current_iostate) {
			printf("current_iostate=%x->%x\n", prev_iostate, current_iostate);
		}
		prev_iostate = current_iostate;
#endif

#if 0
		uint8_t val = SC16IS750_digitalRead(&dev, gpio);
		printf("gpio=%d val=%d\n", gpio, val);
#endif
		delay(10);
	}
}

