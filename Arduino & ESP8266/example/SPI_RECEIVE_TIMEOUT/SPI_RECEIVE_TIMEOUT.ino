#include <SPI.h>
#include <Wire.h>
#include <SC16IS752.h>

#ifdef __AVR__
 #define CS 6
#elif ESP8266 // ESP8266
 #define CS 15
#endif

SC16IS752 spiuart = SC16IS752(SC16IS750_PROTOCOL_SPI,CS); 

#define baudrate_A 9600
#define baudrate_B 115200

void setup() 
{
  Serial.begin(115200);
  Serial.println("Start testing");
  // UART to Serial Bridge Initialization
  spiuart.begin(baudrate_A, baudrate_B); //baudrate setting
  if (spiuart.ping()!=1) {
    Serial.println("Device not found");
    while(1);
  } else {
    Serial.println("Device found");
  }
  Serial.println("start serial communication");
  Serial.print("baudrate(channel A) = ");
  Serial.println(baudrate_A);
  Serial.print("baudrate(channel B) = ");
  Serial.println(baudrate_B);

  spiuart.setTimeout(500);
}

void loop() 
{
  static char buffer_A[64] = {0};
  static int index_A = 0;
  static char buffer_B[64] = {0};
  static int index_B = 0;

  int16_t c;
  uint8_t channel;

  c = spiuart.readwithtimeout(&channel);
  if (c != -1) {
    if (channel == SC16IS752_CHANNEL_A) {
      if (index_A < sizeof(buffer_A)-1) {
        buffer_A[index_A++] = c;
        buffer_A[index_A] = 0;
      }
    } else {
      if (index_B < sizeof(buffer_B)-1) {
        buffer_B[index_B++] = c;
        buffer_B[index_B] = 0;
      }
    }
  } else {
    Serial.print("Channel A=[");
    Serial.print(buffer_A);
    Serial.println("]");
    index_A = 0;
    Serial.print("Channel B=[");
    Serial.print(buffer_B);
    Serial.println("]");
    index_B = 0;
  }
}
