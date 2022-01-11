#include <SPI.h>
#include <Wire.h>
#include <SC16IS752.h>

SC16IS752 i2cuart = SC16IS752(SC16IS750_PROTOCOL_I2C,SC16IS750_ADDRESS_AA);

#define baudrate_A 9600
#define baudrate_B 115200

long lastMsg = 0;

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
  i2cuart.EnableRs485(SC16IS752_CHANNEL_A, WITH_INVERT_RTS_SIGNAL);
  i2cuart.EnableRs485(SC16IS752_CHANNEL_B, WITH_INVERT_RTS_SIGNAL);
}

void loop() 
{
  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    char buf[64];
    strcpy(buf,"0123456789");
    for (int i=0;i<strlen(buf);i++) {
      i2cuart.write(SC16IS752_CHANNEL_A, buf[i]);
    }
    for (int i=0;i<strlen(buf);i++) {
      i2cuart.write(SC16IS752_CHANNEL_B, buf[i]);
    }
  }
  delay(1000);
}
