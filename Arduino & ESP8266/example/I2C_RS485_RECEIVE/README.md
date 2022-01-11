# I2C_RS485_RECEIVE
Receive data from RS485.   
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

SoftwareSerial mySerial(2, 3); // RX, TX

#define TXDEN  3

void setup()
{
  UCSR0B |= (1<<TXCIE0);     // TX Complete Interrupt Enable 0
  Serial.begin(9600);
  pinMode(TXDEN, OUTPUT);
}

ISR (USART_TX_vect)
{
  digitalWrite(TXDEN, LOW);
}

void loop()
{
  byte txData[10];
  for(int i=0;i<10;i++) {
    txData[i]=0x30 + i;
  }
  digitalWrite(TXDEN, HIGH);
  Serial.write(txData,10);

  delay(1000);
}
```

