# LED cover of Marble Machine  

## Description
A small project from Robot System Lecture  
This repository provide Raspberry Pi's device driver
for blinking LEDs to cover a few music notes of Marble Machine  

## Demo  
[LED cover of Marble Machine](https://youtu.be/cNQ4pHiICIc)

## Requirements  
- Raspberry Pi 3B  
- [Raspberry Pi kernel build](https://github.com/ryuichiueda/raspberry_pi_kernel_build_scripts)
- Python 2.7 or later version
- Breadboard
- 9 LEDs and resistors(220[Ω])  

## Installation  
- Connect LEDs and resistors as below 
- Connect Raspberry Pi GPIO (26,19, 6, 13, 5, 21, 20, 16, 12)   
to LEDs in order from left to right
![](/IMG_0216.jpg)  

- Next, download software from Raspberry Pi terminal
 ```
 $ git clone https://github.com/anhquan18/robosys2019_raspberry_led.git
 $ cd robosys2019_raspberry_led
 $ make && sudo insmod myled.ko
 $ sudo chmod 666 /dev/myled0
 ```
 
 ## Usage
 Run the following command
 ```
 $ ./marble_machine_cover.py
 ```
 
 ## License
 This repository is licensed under the GPLv3 license, see [LICENSE](.)
