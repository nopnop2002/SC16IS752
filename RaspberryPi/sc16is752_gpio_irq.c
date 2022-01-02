#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wiringPi.h>
#include "sc16is750.h"

bool isInterrupt = false;

void int_signal(void){
	//printf("int_signal\n");
	isInterrupt = true;
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
		printf("i2c_addressr=0x%x\n", (uint8_t)i2c_address);
		SC16IS750_init(&dev, SC16IS750_PROTOCOL_I2C, (uint8_t)i2c_address, SC16IS750_DUAL_CHANNEL);
	} else if (strcmp(argv[1], "SPI") == 0) {
		long chip_select = strtol(argv[2], NULL, 10);
		printf("chip_select=%ld\n", chip_select);
		SC16IS750_init(&dev, SC16IS750_PROTOCOL_SPI, (uint8_t)chip_select, SC16IS750_DUAL_CHANNEL);
	} else {
		printf("USAGE:\n");
		printf("\t%s I2C i2c_address : For I2C\n", argv[0]);
		printf("\t%s SPI chip_select : For SPI\n", argv[0]);
		return 1;
	}

	int gpio = 0;
	if (argc == 4) {
		gpio = strtol(argv[3], NULL, 10);
	}
	printf("gpio=%d\n", gpio);

	// wiringPi Initialization
	if(wiringPiSetup() == -1) {
		printf("wiringPiSetup Fail\n");
		return 1;
	}

	// SC16IS750 Initialization
	SC16IS750_begin(&dev, SC16IS750_DEFAULT_SPEED, SC16IS750_CHANNEL_NONE, 14745600UL); //baudrate&frequency setting
	if (SC16IS750_ping(&dev)!=1) {
		printf("device not found\n");
		return 1;
	} else {
		printf("device found\n");
	}

	// Set Interrupt
	int irq = 16;
	pinMode(irq, INPUT);
	//pullUpDnControl(irq, PUD_UP);
	wiringPiISR(irq, INT_EDGE_BOTH, &int_signal);

	SC16IS750_pinMode(&dev, gpio, INPUT);
	SC16IS750_SetPinInterrupt(&dev, 0xff);

	while (1) {
#if 0
		int value=digitalRead(irq);
		printf("irq value=%d\n",value);
#endif

		if (isInterrupt) {
			int16_t event = SC16IS750_InterruptEventTest(&dev, SC16IS750_CHANNEL_BOTH);

			if (event == SC16IS750_INPUT_PIN_CHANGE_STATE) {
				uint8_t gpio = SC16IS750_GPIOGetPortState(&dev);
				printf("gpio=0x%x\n", gpio);
			}
		isInterrupt = false;
		}

		delay(10);
	}
}

