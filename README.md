# SC16IS752
SC16IS752 Driver for ATmega328/ESP8266   
SC16IS750/752 Driver for RaspberryPi

![SC16IS752-2](https://user-images.githubusercontent.com/6020549/71316920-4d722800-24bc-11ea-93dc-627e2a2cc1c0.JPG)

![SC16IS752-1](https://user-images.githubusercontent.com/6020549/71316919-4d722800-24bc-11ea-96c7-85b5d014bfe0.JPG)

---

# for i2c

|SC16IS750/752||ATmega328/ESP8266|RPi|
|:-:|:-:|:-:|:-:|
|VCC|--|5V(*1)|5V(*1)|
|GND|--|GND|GND|
|RESET|--|N/C|N/C|
|A0/CS|--|5V(*2)|5V(*2)|
|A1/SI|--|5V(*2)|5V(*2)|
|NC/SO|--|N/C|N/C|
|IRQ|--|N/C|N/C|
|I2C/SPI|--|5V|5V|
|SCL/SCLK|--|SCL(*3)|SCL(*4)|
|SDA/VSS|--|SDA(*3)|SDA(*4)|

(*1)
The SC16IS750 breakout board is equipped with a MIC5219 LG33 voltage regulator, which provides 3.3V to the chip.   
The SC16IS752 breakout board is equipped with a AMS1117-3.3 voltage regulator, which provides 3.3V to the chip.   
Therefore, the level of i2c is 3.3V, but all pins are 5V tolerant.   
It can be used with either 3.3V MPU or 5V MPU.   

(*2)i2c address selection   
|A0|A1|Address|
|:-:|:-:|:-:|
|5V|5V|0x48|
|5V|GND|0x49|
|GND|5V|0x4C|
|GND|GND|0x4D|

(*3)Requires PullUp   
(*4)No Requires PullUp   

---

# for SPI

|SC16IS750/752||ATmega328/ESP8266/Rpi|
|:-:|:-:|:-:|
|VCC|--|5V(*1)|
|GND|--|GND|
|RESET|--|N/C|
|A0/CS|--|CS|
|A1/SI|--|MOSI|
|NC/SO|--|MISO|
|IRQ|--|N/C|
|I2C/SPI|--|GND|
|SCL/SCLK|--|SCK|
|SDA/VSS|--|GND|

(*1)
The SC16IS750 breakout board is equipped with a MIC5219 LG33 voltage regulator, which provides 3.3V to the chip.   
The SC16IS752 breakout board is equipped with a AMS1117-3.3 voltage regulator, which provides 3.3V to the chip.   
Therefore, the level of SPI is 3.3V, but all pins are 5V tolerant.   
It can be used with either 3.3V MPU or 5V MPU.   

# Baudrate generator
SC16IS750/752 has baudrate generator.   
Since the communication speed is used by dividing the frequency of the crystal, an error may occur depending on the communication speed.   
How to divide is described in the data sheet, but for example, using a 3.072MHz crystal,   
When setting the communication speed of 3600bps, it is necessary to divide the frequency of the crystal by 53.3333,   
Since such a value cannot be set in the register, sets 54 in the register.   
As a result, the actual communication speed will be 3555bps.   
This calculation can be calculated with the following code.   
```
#include <stdio.h>
void main() {
  long crystal_freq = 3072000; // 3,072,000MHz
  long prescaler = 1;
  long baudrate = 3600;
  long divisor1 = crystal_freq/prescaler;
  long divisor2 = baudrate*16;
  double divisorf = (double)divisor1/(double)divisor2;
  long divisor = divisorf + 0.999;
  printf("divisor1=%ld divisor2=%ld divisor=%ld divisorf=%f\n",
    divisor1, divisor2, divisor, divisorf);

  long actual_baudrate = (divisor1/divisor)/16;
  printf("actual_baudrate=%ld\n", actual_baudrate);
}
```
