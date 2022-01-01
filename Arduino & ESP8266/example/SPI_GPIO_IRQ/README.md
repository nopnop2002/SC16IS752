# SPI_GPIO_IRQ
Input interrupt using push switch.   
The IRQ needs to be pulled up with an external resistor because the PCB pattern is wrong.   
Connect the IRQ to PIN #2 (INT0).   
Connect GPIO0 to the Push Switch.   

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
INT------------+-----------IRQ
               |            |
5V----10Kohm---+            |
                            |
                            +----------

```
