# SC16IS750 Driver for RaspberryPi

![SC16IS750](https://user-images.githubusercontent.com/6020549/71384102-bd022780-2622-11ea-8f5a-25f2fd733f19.JPG)

---

## sc16is750_selftest

Connect TX and RX with a short wire   

__Connections should be as short as possible__

```
sudo ./sc16is750_selftest I2C i2c_address

sudo ./sc16is750_selftest SPI chip_select_gpio
```

---

## sc16is750_receive

Connect RX and TX of other computer at any baud rate   

__Connections should be as short as possible__


### Sketch of the other side
```
#define baudrate 115200L

void setup() {
  Serial.begin(baudrate);
}

void loop() {
  char buf[64];
  sprintf(buf,"Hello Wold, Baudrate is %ld", baudrate);
  Serial.println(buf);
  //Serial.println("Hello this is Arduino");
  delay(1000);
}
```

```
sudo ./sc16is750_receiver I2C i2c_address baudrate

sudo ./sc16is750_receiver SPI chip_select_gpio baudrate
```

![sc16is750-i2c](https://user-images.githubusercontent.com/6020549/71321400-0b68d680-24fc-11ea-951a-8325eff93eb8.jpg)

![sc16is750-spi](https://user-images.githubusercontent.com/6020549/71321404-0e63c700-24fc-11ea-9b35-11d1daa33cc6.jpg)

---

## sc16is750_gpio

Connect GPIO0 and LED   

```
sudo ./sc16is750_gpio I2C i2c_address

sudo ./sc16is750_gpio SPI chip_select_gpio
```

---

# SC16IS752 Driver for RaspberryPi

![SC16IS752-1](https://user-images.githubusercontent.com/6020549/71384120-e327c780-2622-11ea-8b85-b35da2f9deaa.JPG)

---

## sc16is752_selftest

Connect TX of ChannelA and RX of ChannelB with a short wire   
Connect TX of ChannelB and RX of ChannelA with a short wire   

__Connections should be as short as possible__

```
sudo ./sc16is752_selftest I2C i2c_address

sudo ./sc16is752_selftest SPI chip_select_gpio
```

---

## sc16is752_receive

Connect RX and TX of other computer at any baud rate   

__Connections should be as short as possible__


```
sudo ./sc16is752_receiver I2C i2c_address channelA_baudrate channelB_baudrate

sudo ./sc16is752_receiver SPI chip_select_gpio channelA_baudrate channelB_baudrate
```

![Raspberry-i2c](https://user-images.githubusercontent.com/6020549/71444661-5f6ef780-2756-11ea-8af5-1f83be2090b1.jpg)

![Raspberry-spi](https://user-images.githubusercontent.com/6020549/71444662-6138bb00-2756-11ea-978a-69cba5271bd5.jpg)

---

## sc16is752_gpio

Connect GPIO0 and LED   

```
sudo ./sc16is752_gpio I2C i2c_address

sudo ./sc16is752_gpio SPI chip_select_gpio
```

