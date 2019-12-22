# SC16IS750 Driver for RaspberryPi

---

## sc16is750_selftest

Connect TX and RX with a short wire   

__Connections should be as short as possible__

![sc16is750-selftest](https://user-images.githubusercontent.com/6020549/71321397-f8ee9d00-24fb-11ea-8a50-662e032d4c87.jpg)

---

## sc16is750_receive

Connect RX and TX of other computer at any baud rate   

```
sudo ./sc16is750_selftest I2C i2c_address

sudo ./sc16is750_selftest SPI chip_select_gpio
```

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

![sc16is750-gpio](https://user-images.githubusercontent.com/6020549/71321405-1de31000-24fc-11ea-810f-bf2b29bbf1ec.jpg)

---

# SC16IS752 Driver for RaspberryPi

making...

