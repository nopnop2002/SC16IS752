# SPI_GPIO_IRQ
The IRQ needs to be pulled up with an external resistor because the PCB pattern is wrong.   
Connect the IRQ to PIN # 2 (INT0).   
Connect GPIO0 to the Switch.   

```
UNO                         SWC16IL752
5V-------------+            +-----------
               |            |
             10Kohm         |
               +------------GPIO0
             Swtch          |
               |            |
GND------------+            |
                            |
                            |
INT------------+------------IRQ
               |            |
5V----10Kohm---+            |
                            |
                            +----------

```
