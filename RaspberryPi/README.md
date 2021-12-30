# Software requirements
- WiringPi Library   

# SC16IS750 Driver for RaspberryPi

14.7456MHz crystal is used for SC16IS750.   

__The maximum transfer speed of SC16IS750 is 115,200bps.__

![SC16IS750](https://user-images.githubusercontent.com/6020549/71384102-bd022780-2622-11ea-8f5a-25f2fd733f19.JPG)

---

## sc16is750_selftest

Connect TX of SC16IS750 and RX of SC16IS750 with a short wire.   

__Connections should be as short as possible.__

```
git clone https://github.com/nopnop2002/SC16IS752

cd SC16IS752/RaspberryPi

make

sudo ./sc16is750_selftest I2C {i2c_address}

sudo ./sc16is750_selftest SPI {chip_select_gpio}
```

---

## sc16is750_receiver   
Input is completed with the terminator character.   
Terminating character is CR + LF.   
Connect RX of SC16IS750 and TX of other computer at any baud rate.   
Connect Gnd of Raspberry Pi and Gnd of other computer.   

__Connections should be as short as possible.__


### Sketch of the other side
```
#define baudrate 115200L

void setup() {
  Serial.begin(baudrate);
}

void loop() {
  char buf[64];
  sprintf(buf,"Hello Wold %ld, Baudrate is %ld", millis(), baudrate);
  Serial.println(buf);
  delay(1000);
}
```

```
sudo ./sc16is750_receiver I2C {i2c_address} {baudrate}

sudo ./sc16is750_receiver SPI {chip_select_gpio} {baudrate}
```

![sc16is750-i2c-receive-terminator](https://user-images.githubusercontent.com/6020549/147734850-7a2d02b6-c56f-4d56-a0a1-c1f4d9f0f194.jpg)

![sc16is750-spi-receive-terminator](https://user-images.githubusercontent.com/6020549/147734881-109f1b89-248a-4853-b11f-a4cfaf91da41.jpg)


---

## sc16is750_receiver_timeout
Input is completed with the timeout.   
Timeout is 500 mill sec.   
Connect RX of SC16IS750 and TX of other computer at any baud rate.   
Connect Gnd of Raspberry Pi and Gnd of other computer.   

__Connections should be as short as possible.__


### Sketch of the other side
```
#define baudrate 115200L

void setup() {
  Serial.begin(baudrate);
}

void loop() {
  char buf[64];
  sprintf(buf,"Hello Wold %ld, Baudrate is %ld", millis(), baudrate);
  Serial.print(buf);
  delay(1000);
}
```

```
sudo ./sc16is750_receiver_timeout I2C {i2c_address} {baudrate}

sudo ./sc16is750_receiver_timeout SPI {chip_select_gpio} {baudrate}
```

![sc16is750-i2c-receive-timeout](https://user-images.githubusercontent.com/6020549/147734923-96c09177-8693-4596-8d1e-4f35a5c8d651.jpg)

![sc16is750-spi-receive-timeout](https://user-images.githubusercontent.com/6020549/147734935-7b1b9de6-9fb7-41f4-8d65-1d667960fe99.jpg)

---
## sc16is750_gpio

Connect GPIO0 and LED.   

```
sudo ./sc16is750_gpio I2C {i2c_address} 0

sudo ./sc16is750_gpio SPI {chip_select_gpio} 0
```

---

# SC16IS752 Driver for RaspberryPi

1.8432Mhz crystal is used for SC16IS752.   

__The maximum transfer speed of SC16IS752 is 115,200bps.__

![SC16IS752-1](https://user-images.githubusercontent.com/6020549/71384120-e327c780-2622-11ea-8b85-b35da2f9deaa.JPG)

---

## sc16is752_selftest

Connect TX of ChannelA and RX of ChannelB with a short wire.   
Connect TX of ChannelB and RX of ChannelA with a short wire.   

__Connections should be as short as possible.__

```
git clone https://github.com/nopnop2002/SC16IS752

cd SC16IS752/RaspberryPi

make

sudo ./sc16is752_selftest I2C {i2c_address}

sudo ./sc16is752_selftest SPI {chip_select_gpio}
```

---

## sc16is752_receive
Input is completed with the terminator character.   
Terminating character is CR + LF.   
Connect RX of ChannelA and other computer TX at any baud rate.   
Connect RX of ChannelB and other computer TX at any baud rate.   
Connect Gnd of Raspberry Pi and Gnd of other computer.   

__Connections should be as short as possible.__


```
sudo ./sc16is752_receiver I2C i2c_address channelA_baudrate channelB_baudrate

sudo ./sc16is752_receiver SPI chip_select_gpio channelA_baudrate channelB_baudrate
```

![Raspberry-i2c](https://user-images.githubusercontent.com/6020549/71444661-5f6ef780-2756-11ea-8af5-1f83be2090b1.jpg)

![Raspberry-spi](https://user-images.githubusercontent.com/6020549/71444662-6138bb00-2756-11ea-978a-69cba5271bd5.jpg)

---

## sc16is752_gpio

Connect GPIO0 and LED.   

```
sudo ./sc16is752_gpio I2C {i2c_address}

sudo ./sc16is752_gpio SPI {chip_select_gpio}
```

