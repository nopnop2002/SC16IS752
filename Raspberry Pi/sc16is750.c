/*
Description:
This is a example code for Sandbox Electronics' I2C/SPI to UART bridge module.
You can get one of those products on
http://sandboxelectronics.com

Version:
V0.1

Release Date:
2014-02-16

Author:
Tiequan Shao		  info@sandboxelectronics.com

Lisence:
CC BY-NC-SA 3.0

Please keep the above information when you use this code in your project.
*/


//#define SC16IS750_DEBUG_PRINT
#include <stdio.h>	
#include <stdint.h>
#include <stdbool.h>  
#include <stdlib.h>  
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include "sc16is750.h"




void SC16IS750_init(SC16IS750_t * dev, uint8_t protocol, uint8_t addr_sspin)
{
	dev->protocol = protocol;
	if ( dev->protocol == SC16IS750_PROTOCOL_I2C ) {
		//dev->device_address_i2c = (addr_sspin>>1);
		dev->device_address_i2c = addr_sspin;
	} else {
		dev->device_address_sspin = addr_sspin;
	}
	dev->peek_flag = 0;
//	timeout = 1000;
}

void SC16IS750_begin(SC16IS750_t * dev, uint32_t baud, long crystal_freq)
{
	dev->crystal_freq = crystal_freq;
	if ( dev->protocol == SC16IS750_PROTOCOL_I2C) {
		dev->i2c_fd = wiringPiI2CSetup(dev->device_address_i2c);
	} else {
		pinMode(dev->device_address_sspin, OUTPUT);
		digitalWrite(dev->device_address_sspin, HIGH);
		dev->spi_channel = 0;
		wiringPiSPISetup(dev->spi_channel, 4*1000*1000);
		digitalWrite(dev->device_address_sspin, LOW);
	};
	SC16IS750_ResetDevice(dev);
	SC16IS750_FIFOEnable(dev, SC16IS750_CHANNEL, 1);
	SC16IS750_SetBaudrate(dev, SC16IS750_CHANNEL, baud);
	SC16IS750_SetLine(dev, SC16IS750_CHANNEL, 8, 0, 1);
}

void SC16IS752_begin(SC16IS750_t * dev, uint32_t baud_A, uint32_t baud_B, long crystal_freq)
{
	dev->crystal_freq = crystal_freq;
	if ( dev->protocol == SC16IS750_PROTOCOL_I2C) {
		dev->i2c_fd = wiringPiI2CSetup(dev->device_address_i2c);
	} else {
		pinMode(dev->device_address_sspin, OUTPUT);
		digitalWrite(dev->device_address_sspin, HIGH);
		dev->spi_channel = 0;
		wiringPiSPISetup(dev->spi_channel, 4*1000*1000);
	};
	SC16IS750_ResetDevice(dev);
	SC16IS750_FIFOEnable(dev, SC16IS752_CHANNEL_A, 1);
	SC16IS750_FIFOEnable(dev, SC16IS752_CHANNEL_B, 1);
	SC16IS750_SetBaudrate(dev, SC16IS752_CHANNEL_A, baud_A);
	SC16IS750_SetBaudrate(dev, SC16IS752_CHANNEL_B, baud_B);
	SC16IS750_SetLine(dev, SC16IS752_CHANNEL_A, 8, 0, 1);
	SC16IS750_SetLine(dev, SC16IS752_CHANNEL_B, 8, 0, 1);
}

int SC16IS750_available(SC16IS750_t * dev, uint8_t channel)
{
	return SC16IS750_FIFOAvailableData(dev, channel);
}

int SC16IS750_read(SC16IS750_t * dev, uint8_t channel)
{
	if ( dev->peek_flag == 0) {
		return SC16IS750_ReadByte(dev, channel);
	} else {
		dev->peek_flag = 0;
		return dev->peek_buf;
	}
}

void SC16IS750_write(SC16IS750_t * dev, uint8_t channel, uint8_t val)
{
	SC16IS750_WriteByte(dev, channel, val);
}

void SC16IS750_pinMode(SC16IS750_t * dev, uint8_t pin, uint8_t i_o)
{
	SC16IS750_GPIOSetPinMode(dev, pin, i_o);
}

void SC16IS750_digitalWrite(SC16IS750_t * dev, uint8_t pin, uint8_t value)
{
	SC16IS750_GPIOSetPinState(dev, pin, value);
}

uint8_t SC16IS750_digitalRead(SC16IS750_t * dev, uint8_t pin)
{
   return SC16IS750_GPIOGetPinState(dev, pin);
}


uint8_t SC16IS750_ReadRegister(SC16IS750_t * dev, uint8_t channel, uint8_t reg_addr)
{
	uint8_t result;
	//printf("ReadRegister channel=%d reg_addr=%x\n",channel, (reg_addr<<3 | channel<<1));
	if ( dev->protocol == SC16IS750_PROTOCOL_I2C ) {	// register read operation via I2C
		result = wiringPiI2CReadReg8(dev->i2c_fd, (reg_addr<<3 | channel<<1));
		//printf("result=0x%x\n",result);
	} else if (dev->protocol == SC16IS750_PROTOCOL_SPI) {	//register read operation via SPI
		digitalWrite(dev->device_address_sspin, LOW);
		delayMicroseconds(10);
		unsigned char spi_data[2];
		spi_data[0] = 0x80|(reg_addr<<3 | channel<<1);
		spi_data[1] = 0xff;
		//printf("spi_data[in]=0x%x 0x%x\n",spi_data[0],spi_data[1]);
		wiringPiSPIDataRW(dev->spi_channel, spi_data, 2);
		delayMicroseconds(10);
		digitalWrite(dev->device_address_sspin, HIGH);
		//printf("spi_data[out]=0x%x 0x%x\n",spi_data[0],spi_data[1]);
		result = spi_data[1];
	}
	return result;

}

void SC16IS750_WriteRegister(SC16IS750_t * dev, uint8_t channel, uint8_t reg_addr, uint8_t val)
{
	//printf("WriteRegister channel=%d reg_addr=%x val=%x\n",channel, (reg_addr<<3 | channel<<1), val);
	if ( dev->protocol == SC16IS750_PROTOCOL_I2C ) {	// register read operation via I2C
		wiringPiI2CWriteReg8(dev->i2c_fd, (reg_addr<<3 | channel<<1), val);
	} else {
		digitalWrite(dev->device_address_sspin, LOW);
		delayMicroseconds(10);
		unsigned char spi_data[2];
		spi_data[0] = (reg_addr<<3 | channel<<1);
		spi_data[1] = val;
		wiringPiSPIDataRW(dev->spi_channel, spi_data, 2);
		delayMicroseconds(10);
		digitalWrite(dev->device_address_sspin, HIGH);
	}
	return ;
}

int16_t SC16IS750_SetBaudrate(SC16IS750_t * dev, uint8_t channel, uint32_t baudrate) //return error of baudrate parts per thousand
{
	uint16_t divisor;
	uint8_t prescaler;
	uint32_t actual_baudrate;
	int16_t error;
	uint8_t temp_lcr;
	if ( (SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_MCR)&0x80) == 0) { //if prescaler==1
	prescaler = 1;
	} else {
	prescaler = 4;
	}

	//divisor = (SC16IS750_CRYSTCAL_FREQ/prescaler)/(baudrate*16);
	uint32_t divisor1 = dev->crystal_freq/prescaler;
    //printf("divisor1=%d\n",divisor1);
	uint32_t divisor2 = baudrate*16;
    //printf("divisor2=%d\n",divisor2);
	//divisor = (dev->crystal_freq/prescaler)/(baudrate*16);
    if (divisor2 > divisor1) {
		printf("This baudrate (%d) is not support\n",baudrate);
		return 0;
	}
	divisor = divisor1/divisor2;
    //printf("baudrate=%d divisor=%d\n",baudrate,divisor);

	temp_lcr = SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_LCR);
	temp_lcr |= 0x80;
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_LCR, temp_lcr);
	//write to DLL
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_DLL, (uint8_t)divisor);
	//write to DLH
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_DLH, (uint8_t)(divisor>>8));
	temp_lcr &= 0x7F;
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_LCR, temp_lcr);


	//actual_baudrate = (SC16IS750_CRYSTCAL_FREQ/prescaler)/(16*divisor);
	divisor1 = dev->crystal_freq/prescaler;
	//printf("divisor1=%d\n",divisor1);
	divisor2 = 16*divisor;
	//printf("divisor2=%d\n",divisor2);
	//actual_baudrate = (dev->crystal_freq/prescaler)/(16*divisor);
	actual_baudrate = divisor1 / divisor2;
	error = ((float)actual_baudrate-baudrate)*1000/baudrate;
#ifdef	SC16IS750_DEBUG_PRINT
	printf("Desired baudrate: ");
	printf("%x\n", baudrate);
	printf("Calculated divisor: ");
	printf("%x\n", divisor);
	printf("Actual baudrate: ");
	printf("%x\n", actual_baudrate);
	printf("Baudrate error: ");
	printf("%x\n", error);
#endif

	return error;

}

void SC16IS750_SetLine(SC16IS750_t * dev, uint8_t channel, uint8_t data_length, uint8_t parity_select, uint8_t stop_length )
{
	uint8_t temp_lcr;
	temp_lcr = SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_LCR);
	temp_lcr &= 0xC0; //Clear the lower six bit of LCR (LCR[0] to LCR[5]
#ifdef	SC16IS750_DEBUG_PRINT
	printf("LCR Register:0x");
	printf("%x\n", temp_lcr);
#endif
	switch (data_length) {		  //data length settings
	case 5:
		break;
	case 6:
		temp_lcr |= 0x01;
		break;
	case 7:
		temp_lcr |= 0x02;
		break;
	case 8:
		temp_lcr |= 0x03;
		break;
	default:
		temp_lcr |= 0x03;
		break;
	}

	if ( stop_length == 2 ) {
	temp_lcr |= 0x04;
	}

	switch (parity_select) {		//parity selection length settings
	case 0:				//no parity
		 break;
	case 1:				//odd parity
		temp_lcr |= 0x08;
		break;
	case 2:				//even parity
		temp_lcr |= 0x18;
		break;
	case 3:				//force '1' parity
		temp_lcr |= 0x03;
		break;
	case 4:				//force '0' parity
		break;
	default:
		break;
	}

	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_LCR, temp_lcr);
}

void SC16IS750_GPIOSetPinMode(SC16IS750_t * dev, uint8_t pin_number, uint8_t i_o)
{
	uint8_t temp_iodir;

	temp_iodir = SC16IS750_ReadRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IODIR);
	if ( i_o == OUTPUT ) {
	  temp_iodir |= (0x01 << pin_number);
	} else {
	  temp_iodir &= (uint8_t)~(0x01 << pin_number);
	}

	SC16IS750_WriteRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IODIR, temp_iodir);
	return;
}

void SC16IS750_GPIOSetPinState(SC16IS750_t * dev, uint8_t pin_number, uint8_t pin_state)
{
	uint8_t temp_iostate;

	temp_iostate = SC16IS750_ReadRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOSTATE);
	if ( pin_state == 1 ) {
	  temp_iostate |= (0x01 << pin_number);
	} else {
	  temp_iostate &= (uint8_t)~(0x01 << pin_number);
	}

	SC16IS750_WriteRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOSTATE, temp_iostate);
	return;
}


uint8_t SC16IS750_GPIOGetPinState(SC16IS750_t * dev, uint8_t pin_number)
{
	uint8_t temp_iostate;

	temp_iostate = SC16IS750_ReadRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOSTATE);
	if ( ( temp_iostate & (0x01 << pin_number) ) == 0 ) {
	  return 0;
	}
	return 1;
}

uint8_t SC16IS750_GPIOGetPortState(SC16IS750_t * dev)
{

	return SC16IS750_ReadRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOSTATE);

}

void SC16IS750_GPIOSetPortMode(SC16IS750_t * dev, uint8_t port_io)
{
	SC16IS750_WriteRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IODIR, port_io);
	return;
}

void SC16IS750_GPIOSetPortState(SC16IS750_t * dev, uint8_t port_state)
{
	SC16IS750_WriteRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOSTATE, port_state);
	return;
}

void SC16IS750_SetPinInterrupt(SC16IS750_t * dev, uint8_t io_int_ena)
{
	SC16IS750_WriteRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOINTENA, io_int_ena);
	return;
}

void SC16IS750_ResetDevice(SC16IS750_t * dev)
{
	uint8_t reg;

	reg = SC16IS750_ReadRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOCONTROL);
	reg |= 0x08;
	SC16IS750_WriteRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOCONTROL, reg);

	return;
}

void SC16IS750_ModemPin(SC16IS750_t * dev, uint8_t gpio) //gpio == 0, gpio[7:4] are modem pins, gpio == 1 gpio[7:4] are gpios
{
	uint8_t temp_iocontrol;

	temp_iocontrol = SC16IS750_ReadRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOCONTROL);
	if ( gpio == 0 ) {
	temp_iocontrol |= 0x02;
	} else {
	temp_iocontrol &= 0xFD;
	}
	SC16IS750_WriteRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOCONTROL, temp_iocontrol);

	return;
}

void SC16IS750_GPIOLatch(SC16IS750_t * dev, uint8_t latch)
{
	uint8_t temp_iocontrol;

	temp_iocontrol = SC16IS750_ReadRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOCONTROL);
	if ( latch == 0 ) {
	temp_iocontrol &= 0xFE;
	} else {
	temp_iocontrol |= 0x01;
	}
	SC16IS750_WriteRegister(dev, SC16IS752_CHANNEL_BOTH, SC16IS750_REG_IOCONTROL, temp_iocontrol);

	return;
}

void SC16IS750_InterruptControl(SC16IS750_t * dev, uint8_t channel, uint8_t int_ena)
{
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_IER, int_ena);
}

uint8_t SC16IS750_InterruptPendingTest(SC16IS750_t * dev, uint8_t channel)
{
	return (SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_IIR) & 0x01);
}

void SC16IS750_isr(SC16IS750_t * dev, uint8_t channel)
{
	uint8_t irq_src;

	irq_src = SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_IIR);
	irq_src = (irq_src >> 1);
	irq_src &= 0x3F;

	switch (irq_src) {
	case 0x06:			//Receiver Line Status Error
		break;
	case 0x0c:		 //Receiver time-out interrupt
		break;
	case 0x04:		 //RHR interrupt
		break;
	case 0x02:		 //THR interrupt
		break;
	case 0x00:			//modem interrupt;
		break;
	case 0x30:			//input pin change of state
		break;
	case 0x10:			//XOFF
		break;
	case 0x20:			//CTS,RTS
		break;
	default:
		break;
	}
	return;
}

void SC16IS750_FIFOEnable(SC16IS750_t * dev, uint8_t channel, uint8_t fifo_enable)
{
	uint8_t temp_fcr;

	temp_fcr = SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_FCR);

	if (fifo_enable == 0){
	temp_fcr &= 0xFE;
	} else {
	temp_fcr |= 0x01;
	}
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_FCR, temp_fcr);

	return;
}

void SC16IS750_FIFOReset(SC16IS750_t * dev, uint8_t channel, uint8_t rx_fifo)
{
	 uint8_t temp_fcr;

	temp_fcr = SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_FCR);

	if (rx_fifo == 0){
	temp_fcr |= 0x04;
	} else {
	temp_fcr |= 0x02;
	}
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_FCR, temp_fcr);

	return;

}

void SC16IS750_FIFOSetTriggerLevel(SC16IS750_t * dev, uint8_t channel, uint8_t rx_fifo, uint8_t length)
{
	uint8_t temp_reg;

	temp_reg = SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_MCR);
	temp_reg |= 0x04;
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_MCR, temp_reg); //SET MCR[2] to '1' to use TLR register or trigger level control in FCR register

	temp_reg = SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_EFR);
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_EFR, temp_reg|0x10); //set ERF[4] to '1' to use the  enhanced features
	if (rx_fifo == 0) {
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_TLR, length<<4); //Tx FIFO trigger level setting
	} else {
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_TLR, length);	 //Rx FIFO Trigger level setting
	}
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_EFR, temp_reg); //restore EFR register

	return;
}

uint8_t SC16IS750_FIFOAvailableData(SC16IS750_t * dev, uint8_t channel)
{
#ifdef	SC16IS750_DEBUG_PRINT
	printf("=====Available data:");
	printf("%x\n", SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_RXLVL));
#endif
   return SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_RXLVL);
//	  return SC16IS750_ReadRegister(dev, SC16IS750_REG_LSR) & 0x01;
}

uint8_t SC16IS750_FIFOAvailableSpace(SC16IS750_t * dev, uint8_t channel)
{
   return SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_TXLVL);

}

void SC16IS750_WriteByte(SC16IS750_t * dev, uint8_t channel, uint8_t val)
{
	uint8_t tmp_lsr;
 /*   while ( SC16IS750_FIFOAvailableSpace(dev, channel) == 0 ){
#ifdef	SC16IS750_DEBUG_PRINT
		printf("No available space\n");
#endif

	};

#ifdef	SC16IS750_DEBUG_PRINT
	printf("++++++++++++Data sent\n");
#endif
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_THR, val);
*/
	do {
		tmp_lsr = SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_LSR);
	} while ((tmp_lsr&0x20) ==0);

	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_THR, val);



}

int SC16IS750_ReadByte(SC16IS750_t * dev, uint8_t channel)
{
	volatile uint8_t val;
	if (SC16IS750_FIFOAvailableData(dev, channel) == 0) {
#ifdef	SC16IS750_DEBUG_PRINT
	printf("No data available\n");
#endif
		return -1;

	} else {

#ifdef	SC16IS750_DEBUG_PRINT
	printf("***********Data available***********\n");
#endif
	  val = SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_RHR);
	  return val;
	}


}

void SC16IS750_EnableTransmit(SC16IS750_t * dev, uint8_t channel, uint8_t tx_enable)
{
	uint8_t temp_efcr;
	temp_efcr = SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_EFCR);
	if ( tx_enable == 0) {
	temp_efcr |= 0x04;
	} else {
	temp_efcr &= 0xFB;
	}
	SC16IS750_WriteRegister(dev, channel, SC16IS750_REG_EFCR, temp_efcr);

	return;
}

uint8_t SC16IS750_ping(SC16IS750_t * dev)
{
	SC16IS750_WriteRegister(dev, SC16IS752_CHANNEL_A, SC16IS750_REG_SPR, 0x55);
	if (SC16IS750_ReadRegister(dev, SC16IS752_CHANNEL_A, SC16IS750_REG_SPR) !=0x55) {
		return 0;
	}

	SC16IS750_WriteRegister(dev, SC16IS752_CHANNEL_A, SC16IS750_REG_SPR, 0xAA);
	if (SC16IS750_ReadRegister(dev, SC16IS752_CHANNEL_A, SC16IS750_REG_SPR) !=0xAA) {
		return 0;
	}

	return 1;

}
/*
void SC16IS750_setTimeout(SC16IS750_t * dev, uint32_t time_out)
{
	dev->timeout = time_out;
}

size_t SC16IS750_readBytes(SC16IS750_t * dev, char *buffer, size_t length)
{
	size_t count=0;
	int16_t tmp;

	while (count < length) {
		tmp = SC16IS750_readwithtimeout(dev);
		if (tmp < 0) {
			break;
		}
		*buffer++ = (char)tmp;
		count++;
	}

	return count;
}

int16_t SC16IS750_readwithtimeout(SC16IS750_t * dev)
{
  int16_t tmp;
  uint32_t time_stamp;
  time_stamp = millis();
  do {
	tmp = SC16IS750_read(dev);
	if (tmp >= 0) return tmp;
  } while(millis() - time_stamp < timeout);
  return -1;	 // -1 indicates timeout
}
*/

void SC16IS750_flush(SC16IS750_t * dev, uint8_t channel)
{
	uint8_t tmp_lsr;

	do {
		tmp_lsr = SC16IS750_ReadRegister(dev, channel, SC16IS750_REG_LSR);
	} while ((tmp_lsr&0x20) ==0);


}

int SC16IS750_peek(SC16IS750_t * dev, uint8_t channel)
{
	if ( dev->peek_flag == 0 ) {
		dev->peek_buf = SC16IS750_ReadByte(dev, channel);
		if (  dev->peek_buf >= 0 ) {
			dev->peek_flag = 1;
		}
	}

	return dev->peek_buf;

}

