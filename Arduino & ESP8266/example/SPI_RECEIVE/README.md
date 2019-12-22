# I2C_SELFTEST

Connect TX(A-CH) and RX(B-CH) with a short wire   
Connect TX(B-CH) and RX(A-CH) with a short wire   

__Connections should be as short as possible__

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
  //Serial.println("Hello this is Arduino");
  delay(1000);
}
```

