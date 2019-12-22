# SC16IS750 Driver for RaspberryPi

![sc16is750](https://user-images.githubusercontent.com/6020549/71318319-a056da00-24d2-11ea-902f-5fba0e077e05.jpg)

---

## sc16is750_selftest

Connect TX and RX with a short wire   

__Connections should be as short as possible__

---

## sc16is750_receive

Connect RX and TX of other computer at any baud rate   

__Connections should be as short as possible__


### Sketch of the other side
```
#define baudrate 9600L

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

![sc16is750-i2c](https://user-images.githubusercontent.com/6020549/71318280-30e0ea80-24d2-11ea-8041-75e893ba3bdb.jpg)

![sc16is750-spi](https://user-images.githubusercontent.com/6020549/71318281-30e0ea80-24d2-11ea-96ec-9c10ff385f7b.jpg)

---

## sc16is750_gpio

Connect GPIO0 and LED   

---

# SC16IS752 Driver for RaspberryPi

making...

