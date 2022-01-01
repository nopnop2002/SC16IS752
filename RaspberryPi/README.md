# Software requirements
- WiringPi Library   

# SC16IS750 Driver for RaspberryPi
SC16IS750 has a single channel UART and eight GPIOs.   
14.7456MHz crystal is used for SC16IS750.   
__The maximum transfer speed of SC16IS750 is 14745600/16 = 921,600bps.__   
__However, when communicating with Arduino UNO, the maximum communication speed of UNO is 115200bps.__   


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

tvoid loop() {
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

## IRQ connector at the board
__There is a bug at the PCB routing:__   
__All boards are missing the wire between the IRQ pin of the SC16IS750 and the IRQ connector at the board.__   


```
     Breakout
     +--------------------------
     |
     |        +---------------+
     |        |SC16IS750      |
     |        |               |
     |        |               |
     |        |               |
     |        |               |
     |        |               |
     |        |               |
     |        |               |
    IRQ   +--IRQ              |
     |    |   |               |
     |    |   |               |
     |    |   |               |
     |    |   +---------------+
     |    |
     |    +--1Kohm--N/C
     |
     +--------------------------
```


# SC16IS752 Driver for RaspberryPi
SC16IS752 has a 2-channel UART and 8 GPIOs.   
1.8432Mhz crystal is used for SC16IS752.   
__The maximum transfer speed of SC16IS752 is 1843200/16 = 115,200bps.__

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

## sc16is752_receiver
Input is completed with the terminator character.   
Terminating character is CR + LF.   
Connect RX of ChannelA and other computer TX at any baud rate.   
Connect RX of ChannelB and other computer TX at any baud rate.   
Connect Gnd of Raspberry Pi and Gnd of other computer.   

__Connections should be as short as possible.__


```
sudo ./sc16is752_receiver I2C {i2c_address} {channelA_baudrate} {channelB_baudrate}

sudo ./sc16is752_receiver SPI {chip_select_gpio} {channelA_baudrate} {channelB_baudrate}
```

![sc16is752-i2c-receive-terminator](https://user-images.githubusercontent.com/6020549/147802373-4d9dde52-a9d0-4603-8c11-fdea8aa18b86.jpg)

![sc16is752-spi-receive-terminator](https://user-images.githubusercontent.com/6020549/147802379-39f06697-f2a6-4d8c-83c4-4b718235b0b8.jpg)

---

## sc16is752_receiver_timeout
Input is completed with the timeout.   
Timeout is 500 mill sec.   
Connect RX of ChannelA and other computer TX at any baud rate.   
Connect RX of ChannelB and other computer TX at any baud rate.   
Connect Gnd of Raspberry Pi and Gnd of other computer.   

__Connections should be as short as possible.__


```
sudo ./sc16is752_receiver_timeout I2C {i2c_address} {channelA_baudrate} {channelB_baudrate}

sudo ./sc16is752_receiver_timeout SPI {chip_select_gpio} {channelA_baudrate} {channelB_baudrate}
```

![sc16is752-i2c-receive-timeout](https://user-images.githubusercontent.com/6020549/147802424-02d30db7-ad47-414c-bf0f-a03c27bc9f0e.jpg)

![sc16is752-spi-receive-timeout](https://user-images.githubusercontent.com/6020549/147802430-be628a31-88f3-4dac-a989-5c2b75fc34c4.jpg)

---

## sc16is752_gpio

Connect GPIO0 and LED.   

```
sudo ./sc16is752_gpio I2C {i2c_address} 0

sudo ./sc16is752_gpio SPI {chip_select_gpio} 0
```

