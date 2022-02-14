# I2C_ECHO
Converts the entered characters from uppercase to lowercase and from lowercase to uppercase and sends them back.   
```abcdEFGH-->ABCDefgh```   
Connect RX of ChannelA and other Arduno TX at 9600 bps.   
Connect RX of ChannelB and other Arduno TX at 115200 bps.   
Connect Gnd and other Arduno Gnd.   

__Connections should be as short as possible__

# Channel baudrate
You can specify different baudrates for channel A and channel B

# Sketch of the other side using atmega328
```
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

#define baudrate 9600L

long lastMsg = 0;

void setup() {
  Serial.begin(115200);
  mySerial.begin(baudrate);
}

void loop() {
  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    char buf[64];
    sprintf(buf,"Hello Wold %ld, Baudrate is %ld", millis(), baudrate);
    mySerial.println(buf);
  }

  if (mySerial.available() > 0) {
    int data = mySerial.read();
    Serial.write(data);
    //Serial.println(data, HEX);
  }  

}
```

