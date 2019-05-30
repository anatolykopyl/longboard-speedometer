# longboard-speedometer

A simple Arduino based longboard speedometer.

![The thing assembled](https://imgur.com/yaxvWGg.png)

### Part list:
* [Arduino pro mini](https://ru.aliexpress.com/item/1pcs-lot-Pro-Mini-Module-Atmega328-5V-16M-with-Arduino-Compatible-With-Nano/32672852945.html)
* 4 digit 7 segment 0.56 inch display (I used HS420561K-C30, but other 0.56" 12 pin displays should work just fine)
* [TP4056 based li-ion charging circuit](https://ru.aliexpress.com/item/Free-Shipping-5V-1A-Micro-USB-18650-Lithium-Battery-Charging-Board-Charger-Module-Protection-Dual/32453058256.html)
* [Li-Po battery](https://ru.aliexpress.com/item/1-2-4-2019-603040-800/32957830163.html)
* [Reed switch](https://ru.aliexpress.com/item/Reed-sensor-module-magnetron-module-reed-switch-magnetic-switch-for-arduino/32818692044.html) (Although I recommend getting a hall sensor instead)
* 2 state switch 14 x 9 mm
* [Magnet](https://ru.aliexpress.com/item/10Pcs-Mini-Small-N35-Round-Magnet-5x1-6x3-8x3-10x1-10x2-12x2-mm-Neodymium-Magnet-Permanent/32997030821.html)
* Something to program the Arduino with

### Useful pics
![](https://imgur.com/iamUAbG.png)
![](https://imgur.com/6xkXCU7.png) 

| Pin connections||
|-----------------|--------------------------------|
| pin 2 - pin 7   | top row of the display pins    |
| pin 12 - pin 17 | botton row of the display pins |
| pin 10          | sensor data                    |
| ACC             | sensor VCC                     |
| GND             | sensor GND                     |
| VCC             | power +                        |
| GND             | power -                        |
