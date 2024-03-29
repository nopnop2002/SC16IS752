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

# Sketch of the other side using atmega328
```
#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5); // RX, TX

#define TXDEN  3

void setup()
{
  Serial.begin(115200);
  Serial.println("RS485 recv start");
  mySerial.begin(9600);
  pinMode(TXDEN, OUTPUT);
  digitalWrite(TXDEN, LOW); // slave
}

void loop()
{
  while(mySerial.available()){
    byte inChar = (byte)mySerial.read();
    Serial.write(inChar);
  }
}
```

