#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "sc16is750.h"

int main(int argc, char **argv){

	SC16IS750_t dev;
	
	if (argc < 5) {
		printf("USAGE:\n");
		printf("\t%s I2C i2c_address CHA_baudrate CHB_baudrate : For I2C\n", argv[0]);
		printf("\t%s SPI chip_select CHA_baudrate CHB_baudrate : For SPI\n", argv[0]);
		return 1;
	}
	
	if (strcmp(argv[1], "I2C") == 0) {
		long i2c_address = strtol(argv[2], NULL, 16);
		printf("i2c_addressr=0x%x\n", (uint8_t)i2c_address);
		SC16IS750_init(&dev, SC16IS750_PROTOCOL_I2C, (uint8_t)i2c_address);
	} else if (strcmp(argv[1], "SPI") == 0) {
		long chip_select = strtol(argv[2], NULL, 10);
		printf("chip_select=%ld\n", chip_select);
		SC16IS750_init(&dev, SC16IS750_PROTOCOL_SPI, (uint8_t)chip_select);
	} else {
		printf("USAGE:\n");
		printf("\t%s I2C i2c_address CHA_baudrate CHB_baudrate : For I2C\n", argv[0]);
		printf("\t%s SPI chip_select CHA_baudrate CHB_baudrate : For SPI\n", argv[0]);
		return 1;
	}

	// wiringPi Initialization
	if(wiringPiSetup() == -1) {
		printf("wiringPiSetup Fail\n");
		return 1;
	}

	// SC16IS752 Initialization
	long baudrate_A = strtol(argv[3], NULL, 10);
	long baudrate_B = strtol(argv[4], NULL, 10);
	printf("baudrate_A=%ld\n", baudrate_A);
	printf("baudrate_B=%ld\n", baudrate_B);
	SC16IS752_begin(&dev, baudrate_A, baudrate_B, 1843200UL); //baudrate&frequency setting
	if (SC16IS750_ping(&dev)!=1) {
		printf("device not found\n");
		return 1;
	} else {
		printf("device found\n");
	}
	printf("start serial communication\n");


	char buffer_A[64] = {0};
	int index_A = 0;
	char buffer_B[64] = {0};
	int index_B = 0;

	SC16IS750_setTimeout(&dev, 500);

	int16_t c;
	uint8_t channel;
	while(1) {
		c = SC16IS752_readwithtimeout(&dev, &channel);
#if 0
		printf("SC16IS752_readwithtimeout=%d %d\n", c, channel);
#endif
		if (c != -1) {
			if (channel == SC16IS752_CHANNEL_A) {
				if (index_A < sizeof(buffer_A)-1) {
					buffer_A[index_A++] = c;
					buffer_A[index_A] = 0;
				}
			} else {
				if (index_B < sizeof(buffer_B)-1) {
					buffer_B[index_B++] = c;
					buffer_B[index_B] = 0;
				}
			}
		} else {
			printf("[%s]\n",buffer_A);
			index_A = 0;
			printf("[%s]\n",buffer_B);
			index_B = 0;
		}
	}
}

