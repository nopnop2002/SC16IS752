# SC16IS752
SC16IS750/752 Driver for Arduino/ESP8266/RaspberryPi

I forked from [here](https://github.com/SandboxElectronics/UART_Bridge)   

![SC16IS752-2](https://user-images.githubusercontent.com/6020549/71316920-4d722800-24bc-11ea-93dc-627e2a2cc1c0.JPG)

![SC16IS752-1](https://user-images.githubusercontent.com/6020549/71316919-4d722800-24bc-11ea-96c7-85b5d014bfe0.JPG)

---

# for i2c

|SC16IS750/752||Arduino/ESP8266/Rpi|
|:-:|:-:|:-:|
|VCC|--|5V|
|GND|--|GND|
|RESET|--|N/C|
|A0/CS|--|5V(*1)|
|A1/SI|--|5V(*1)|
|NC/SO|--|N/C|
|IRQ|--|N/C|
|I2C/SPI|--|5V|
|SCL/SCLK|--|SCL(*2)|
|SDA/VSS|--|SDA(*2)|

(*1)i2c address selection   
(*2)Requires PullUp

---

# for SPI

|SC16IS750/752||Arduino/ESP8266/Rpi|
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

