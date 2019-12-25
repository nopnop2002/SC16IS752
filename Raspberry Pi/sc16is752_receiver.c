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
		printf("i2c_addressr=%x\n", (uint8_t)i2c_address);
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

	char c;
	while(1) {
		if (SC16IS750_available(&dev, SC16IS752_CHANNEL_A)) {
			c = SC16IS750_read(&dev, SC16IS752_CHANNEL_A);
#if 0
			if (c < 0x20) {
				printf("c_A= (0x%02x)\n",c);
			} else {
				printf("c_A=%c(0x%02x)\n",c,c);
			}
#endif
			if (c == 0x0d) {
	
			} else if (c == 0x0a) {
				printf("[%s]\n",buffer_A);
				index_A = 0;
			} else {
				buffer_A[index_A++] = c;
				buffer_A[index_A] = 0;
			}
		}

		if (SC16IS750_available(&dev, SC16IS752_CHANNEL_B)) {
			c = SC16IS750_read(&dev, SC16IS752_CHANNEL_B);
#if 0
			if (c < 0x20) {
				printf("c_B= (0x%02x)\n",c);
			} else {
				printf("c_B=%c(0x%02x)\n",c,c);
			}
#endif
			if (c == 0x0d) {
	
			} else if (c == 0x0a) {
				printf("[%s]\n",buffer_B);
				index_B = 0;
			} else {
				buffer_B[index_B++] = c;
				buffer_B[index_B] = 0;
			}
		}
	}
}

