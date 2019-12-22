# SC16IS752
Driver for SC16IS752 

![SC16IS752-2](https://user-images.githubusercontent.com/6020549/71316920-4d722800-24bc-11ea-93dc-627e2a2cc1c0.JPG)

![SC16IS752-1](https://user-images.githubusercontent.com/6020549/71316919-4d722800-24bc-11ea-96c7-85b5d014bfe0.JPG)

# for Ardino & ESP8266

## for i2c

|SC16IS752||Arduino|ESP8266|
|:-:|:-:|:-:|:-:|
|VCC|--|5V|5V|
|GND|--|GND|GND|
|RESET|--|Reset|PullUp|
|A0/CS|--|5V(*1)|5V(*1)|
|A1/SI|--|5V(*1)|5V(*1)|
|NC/SO|--|N/C|N/C|
|IRQ|--|N/C|N/C|
|I2C/SPI|--|5V|5V|
|SCL/SCLK|--|SCL(*2)|SCL(*2)|
|SDA/VSS|--|SDA(*2)|SDA(*2)|

(*1)i2c address selection   
(*2)Requires PullUp


## for SPI

|SC16IS752||Arduino|ESP8266|
|:-:|:-:|:-:|:-:|
|VCC|--|5V|5V|
|GND|--|GND|GND|
|RESET|--|Reset|PullUp|
|A0/CS|--|CS|CS|
|A1/SI|--|MOSI|MOSI|
|NC/SO|--|MISO|MISO|
|IRQ|--|N/C|N/C|
|I2C/SPI|--|GND|GND|
|SCL/SCLK|--|SCK|SCLK|
|SDA/VSS|--|GND|GND|

---

# for Raspberry Pi
