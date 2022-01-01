# SPI_GPIO_IRQ
Input interrupt using push switch.   
The IRQ needs to be pulled up with an external resistor because the PCB pattern is wrong.   
Connect the IRQ to PIN #2 (INT0).   
Connect GPIO0 to the Push Switch.   

```
UNO                       Breakout
                         +------------------------
                         |
5V-------------+         |       +---------------+
               |         |       |SC16IS752      |
             10Kohm      |       |               |
               +-------GPIO0----GPIO0            |
              /  Switch  |       |               |
               |         |       |               |
GND------------+         |       |               |
                         |       |               |
                         |       |               |
INT0-----------+--------IRQ--+--IRQ              |
               |         |   |   |               |
5V----10Kohm---+         |   |   |               |
                         |   |   |               |
                         |   |   +---------------+
                         |   |
                         |   +--1Kohm--N/C
                         |
                         +-----------------------
```
