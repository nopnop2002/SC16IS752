#include <SPI.h>
#include <Wire.h>
#include <SC16IS752.h>

#ifdef __AVR__
 #define CS 6
#elif ESP8266 // ESP8266
 #define CS 15
#endif

#define IRQ  2
#define GPIO 0

SC16IS752 spiuart = SC16IS752(SC16IS750_PROTOCOL_SPI,CS); 

//Remove A0, A1 resistors which set the I2C address
//Remove SCL pull up resistors if you are using Duemilanove
//Pin 6 should be connected to CS of the module.
//Pin 2 should be connected to IRQ of the module.

bool isInterrupt =false;

void func() {
  //Serial.println("func");
  isInterrupt = true;

}

void setup() 
{
  Serial.begin(115200);
  Serial.println("Start testing");
  // UART to Serial Bridge Initialization
  spiuart.begin(SC16IS752_DEFAULT_SPEED, SC16IS752_DEFAULT_SPEED); //baudrate setting
  if (spiuart.ping()!=1) {
    Serial.println("Device not found");
    while(1);
  } else {
    Serial.println("Device found");
  }

  attachInterrupt(0, func, CHANGE);
  //pinMode(IRQ, INPUT);
  
  spiuart.pinMode(GPIO, INPUT);
  spiuart.SetPinInterrupt(0xff); // a change in input will generate an interrupt
}

void loop() 
{
  //uint8_t irq = digitalRead(IRQ);
  //Serial.print("irq=");
  //Serial.println(irq);
  
  if (isInterrupt) {
    uint8_t event = spiuart.InterruptEventTest(SC16IS752_CHANNEL_BOTH);
    Serial.print("event=");
    Serial.print(event);
    Serial.println();

    if (event == SC16IS750_INPUT_PIN_CHANGE_STATE) {
      uint8_t gpio = spiuart.GPIOGetPortState();
      Serial.print("gpio=0x");
      Serial.println(gpio,HEX);
    }
    isInterrupt = false;
  }
  delay(1);
}
