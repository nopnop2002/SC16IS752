# I2C_RECEIVE
Input is completed with the terminator character.   
Terminating character is CR + LF.   
Connect RX of ChannelA and other Arduno TX at 9600 bps.   
Connect RX of ChannelB and other Arduno TX at 115200 bps.   
Connect Gnd and other Arduno Gnd.   

__Connections should be as short as possible__

![atmega-i2c-receive-terminator](https://user-images.githubusercontent.com/6020549/147806077-1eedccf0-8d04-4961-95b2-a24a683e0806.jpg)

# Channel baudrate
You can specify different baudrates for channel A and channel B

# Sketch of the other side
```
#define baudrate 9600L

void setup() {
  Serial.begin(baudrate);
}

void loop() {
  char buf[64];
  sprintf(buf,"Hello Wold, Baudrate is %ld", baudrate);
  Serial.println(buf);
  delay(1000);
}
```

