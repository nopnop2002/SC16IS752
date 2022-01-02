#include <SPI.h>
#include <Wire.h>
#include <SC16IS752.h>

#define IRQ  2
#define GPIO 0

SC16IS752 i2cuart = SC16IS752(SC16IS750_PROTOCOL_I2C,SC16IS750_ADDRESS_AA);

//Pin 2 should be connected to IRQ of the module.

bool isInterrupt = false;

void func() {
  //Serial.println("func");
  //The I2C library (wire.h) uses interrupts
  //and interrupts cannot be made within interrupts.
  isInterrupt = true;
}

void setup() 
{
  Serial.begin(115200);
  Serial.println("Start testing");
  // UART to Serial Bridge Initialization
  i2cuart.begin(9600, 9600);               //baudrate setting
  if (i2cuart.ping()!=1) {
    Serial.println("Device not found");
    while(1);
  } else {
    Serial.println("Device found");
  }

  attachInterrupt(0, func, CHANGE);
  //pinMode(IRQ, INPUT);

  i2cuart.pinMode(GPIO, INPUT);
  i2cuart.SetPinInterrupt(0xff); // a change in input will generate an interrupt
}

void loop() 
{
  //uint8_t irq = digitalRead(IRQ);
  //Serial.print("irq=");
  //Serial.println(irq);

  if (isInterrupt) {
    uint8_t event = i2cuart.InterruptEventTest(SC16IS752_CHANNEL_BOTH);
    Serial.print("event=");
    Serial.print(event);
    Serial.println();

    if (event == SC16IS750_INPUT_PIN_CHANGE_STATE) {
      uint8_t gpio = i2cuart.GPIOGetPortState();
      Serial.print("gpio=0x");
      Serial.println(gpio,HEX);
    }
    isInterrupt = false;
  }
  delay(1);
}
