# SC16IS752
SC16IS752 Driver for ATmega328/ESP8266   
SC16IS750/752 Driver for RaspberryPi

![SC16IS752-2](https://user-images.githubusercontent.com/6020549/71316920-4d722800-24bc-11ea-93dc-627e2a2cc1c0.JPG)

![SC16IS752-1](https://user-images.githubusercontent.com/6020549/71316919-4d722800-24bc-11ea-96c7-85b5d014bfe0.JPG)

---

# for i2c

|SC16IS750/752||ATmega328/ESP8266|RPi|
|:-:|:-:|:-:|:-:|
|VCC|--|5V|5V|
|GND|--|GND|GND|
|RESET|--|N/C|N/C|
|A0/CS|--|5V(*1)|5V(*1)|
|A1/SI|--|5V(*1)|5V(*1)|
|NC/SO|--|N/C|N/C|
|IRQ|--|N/C|N/C|
|I2C/SPI|--|5V|5V|
|SCL/SCLK|--|SCL(*2)|SCL(*3)|
|SDA/VSS|--|SDA(*2)|SDA(*3)|

(*1)i2c address selection   
|A0|A1|Address|
|:-:|:-:|:-:|
|Vdd|Vdd|0x90|
|Vdd|Vss|0x92|
|Vss|Vdd|0x98|
|Vss|Vss|0x9A|
(*2)Requires PullUp   
(*3)No Requires PullUp

---

# for SPI

|SC16IS750/752||ATmega328/ESP8266/Rpi|
|:-:|:-:|:-:|
|VCC|--|5V|
|GND|--|GND|
|RESET|--|N/C|
|A0/CS|--|CS|
|A1/SI|--|MOSI|
|NC/SO|--|MISO|
|IRQ|--|N/C|
|I2C/SPI|--|GND|
|SCL/SCLK|--|SCK|
|SDA/VSS|--|GND|

