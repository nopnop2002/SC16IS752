#include <SPI.h>
#include <Wire.h>
#include <SC16IS752.h>

SC16IS752 i2cuart = SC16IS752(SC16IS750_PROTOCOL_I2C,SC16IS750_ADDRESS_AA);

#define baudrate_A 9600
#define baudrate_B 115200

void setup() 
{
  Serial.begin(115200);
  Serial.println("Start testing");
  // UART to Serial Bridge Initialization
  i2cuart.begin(baudrate_A, baudrate_B); //baudrate setting
  if (i2cuart.ping()!=1) {
      Serial.println("device not found");
      while(1);
  } else {
      Serial.println("device found");
  }
  Serial.println("start serial communication");
  Serial.print("baudrate(channel A) = ");
  Serial.println(baudrate_A);
  Serial.print("baudrate(channel B) = ");
  Serial.println(baudrate_B);

  // Enable Auto RS-485 RTS control 
  i2cuart.EnableRs485(SC16IS752_CHANNEL_A, 1);

}

void loop() 
{
  if (i2cuart.available(SC16IS752_CHANNEL_A) > 0){
    // read the incoming byte:
    char c = i2cuart.read(SC16IS752_CHANNEL_A);

    Serial.print("Channel A=");
    if (c < 0x20) {
      Serial.print(" ");
    } else {
      Serial.print("[");
      Serial.print(c);
      Serial.print("]");
    }
    Serial.print(" 0x");
    Serial.println(c,HEX);
  }


  if (i2cuart.available(SC16IS752_CHANNEL_B) > 0){
    // read the incoming byte:
    char c = i2cuart.read(SC16IS752_CHANNEL_B);

    Serial.print("Channel B=");
    if (c < 0x20) {
      Serial.print(" ");
    } else {
      Serial.print("[");
      Serial.print(c);
      Serial.print("]");
    }
    Serial.print(" 0x");
    Serial.println(c,HEX);

  }
}
