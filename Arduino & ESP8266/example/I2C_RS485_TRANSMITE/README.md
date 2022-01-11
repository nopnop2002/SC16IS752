# I2C_RS485_TRANSMITE
Transmite data to RS485.   
SC16IS752 have Auto RS-485 RTS control function.   
The polarity of transmission and reception is switched automatically.   

# Wireing
RS485-BUS need terminator register.   

```
         VCC ---------------+                               +--------------- VCC
                            |                               |
                    +-------x-------+               +-------x-------+
  RTX of UNO <------| RO            |               |             RO|-----> RXD of SC16IS752
                    |              B|---------------|B              |
  TXD of UNO ------>| DI  MAX485    |               |    MAX485   DI|<----- TXD of SC16IS752
                    |               |    RS485-BUS  |               |
  D3 of UNO  --+--->| DE            |               |             DE|---+
               |    |              A|---------------|A              |   |
               +----| /RE           |               |            /RE|---+-- RTS of SC16IS752
                    +-------x-------+               +-------x-------+
                            |                               |
                           ---                             ---
```

__Connections should be as short as possible__

# Sketch of the other side
```
#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5); // RX, TX

#define TXDEN  3

void setup()
{
  mySerial.begin(115200);
  mySerial.println("recv start");
  Serial.begin(9600);
  pinMode(TXDEN, OUTPUT);
  digitalWrite(TXDEN, LOW); // slave
}

void loop()
{
  while(Serial.available()){
    byte inChar = (byte)Serial.read();
    mySerial.print(millis());
    mySerial.print(":");
    mySerial.println(inChar, HEX);
  }
}
```

