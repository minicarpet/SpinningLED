# SpinningLED

17.09.16 : Initial release

Use led RGB with PWM pins
To declare one LED use 'rgbImproved led(pinPWMforRed, pinPWMforGreen, pinPWMforBlue);'

Arduino run all Hue color (from HSV to RGB) inside the loop function and LED turns on/off.

Processing can be use to monitoring the color actually on the LED and see some curves in real time of RGB value


Bluetooth is actually only compatible with Arduino 101 and is not implement yet, thanks to remove all code for BLE.
