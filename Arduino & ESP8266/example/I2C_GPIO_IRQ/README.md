# I2C_GPIO_IRQ
Input interrupt using push switch.   
The IRQ needs to be pulled up with an external resistor because the PCB pattern is wrong.   
Connect the IRQ to PIN #2 (INT0).   
Connect GPIO0 to the Push Switch.   

__The I2C library (wire.h) uses interrupts and interrupts cannot be made within interrupts.__   


```
UNO                         SWC16IL752
5V-------------+            +-----------
               |            |
             10Kohm         |
               +-----------GPIO0
              /  Switch     |
               |            |
GND------------+            |
                            |
                            |
INT0-----------+-----------IRQ
               |            |
5V----10Kohm---+            |
                            |
                            +----------

```
