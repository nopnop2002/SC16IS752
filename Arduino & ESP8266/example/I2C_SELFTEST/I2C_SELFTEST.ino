#include <SPI.h>
#include <Wire.h>
#include <SC16IS752.h>

SC16IS752 i2cuart = SC16IS752(SC16IS750_PROTOCOL_I2C,SC16IS750_ADDRESS_AA);

//Connect TX(A-CH) and RX(B-CH) with a wire
//Connect TX(B-CH) and RX(A-CH) with a wire

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
    Serial.println("Start serial communication");
}

void loop() 
{
    i2cuart.write(SC16IS752_CHANNEL_A, 0x55);
    delay(10);
    if (i2cuart.available(SC16IS752_CHANNEL_B)==0) {
        Serial.println("Please connnect CH-A TX and CH-B RX with a wire and reset your Arduino");
        while(1);
    }        
    if (i2cuart.read(SC16IS752_CHANNEL_B)!=0x55) {
        Serial.println("Serial communication error");
        while(1);
    }   
    delay(200);

    i2cuart.write(SC16IS752_CHANNEL_B, 0xAA);
    delay(10);
    if (i2cuart.available(SC16IS752_CHANNEL_A)==0) {
        Serial.println("Please connnect CH-B TX and CH-A RX with a wire and reset your Arduino");
        while(1);
    }  
    if (i2cuart.read(SC16IS752_CHANNEL_A)!=0xAA) {
        Serial.println("Serial communication error");
        while(1);
    }   
    
    delay(200);
}
