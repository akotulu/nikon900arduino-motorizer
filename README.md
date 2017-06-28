# Nikon P900 Arduino Camera Stative motorizer

![Project Image](https://github.com/akotulu/nikon900arduino-motorizer/blob/master/Schematic.png)

[Youtube full preview](https://youtu.be/GD09Ut1_Xak)

First Nikons where OK, but the new **firmware** is modified, doesn't zoom so far and removed take photo every X seconds from mobile apps. Good buy, but not what the specs sheet promotes, it goes to see, even in best interest you are forced to Vatican agenda by powers in control. Wake up!

[License CC0](https://creativecommons.org/share-your-work/public-domain/cc0/)

Basic feature list:

 * Can do time lapses as long you have battery, 70A will last for ~72h
 * 256GB SD card will be enough for 24h 4k video, picture taken every 3 seconds, 128GB for 1080p
 * Easy to write your own program for remote control buttons, C language knowledge needed
 * Mediocre to setup
 * Expensive, as quality sadly is
 

Components needed:

 * Befree Live. MVH400AH - 130€
 * Sirui T-2005X - 150€
 * Nikon P900 - 600€
 * 256GB SD 95MB/sec card 200€
 * Arduino Nano 3.0 (ATMEGA328) - 27€
 * [MPU-9150 GY-9150 Nine-axis Attitude Three-axis Electronic Compass Acceleration Gyroscope Module -14€](https://www.aliexpress.com/store/product/MPU-9150-GY-9150-Nine-axis-Attitude-Three-axis-Electronic-Compass-Acceleration-Gyroscope-Module/406986_32599547733.html)
 * [DIY 400 Points Solderless Bread Board Breadboard 400 PCB Test Board for ATMEGA PIC Arduino UNO Free Shipping - 2€](https://www.aliexpress.com/item/Hot-sale-DIY-400-Points-Solderless-Bread-Board-Breadboard-400-PCB-Test-Board-for-ATMEGA-PIC/32497913498.html?spm=2114.01010208.3.9.H7lMpV&ws_ab_test=searchweb0_0,searchweb201602_5_10152_10065_10151_10068_10136_10137_10303_10060_10302_10155_10062_437_10154_10056_10055_10054_10059_303_100031_10099_10103_5320014_10102_10096_10052_10053_10142_10107_10050_10051_10170_10084_10083_10119_10080_10082_10081_10110_519_10111_10112_10113_10114_10182_10078_10079_5260014_10073_10123_10120_10189_142-10050_10110_10120,searchweb201603_16,ppcSwitch_4&btsid=6038ed5d-c89e-49ed-a676-96c3d91b0276&algo_expid=b849f023-45eb-47e3-b084-601300382894-1&algo_pvid=b849f023-45eb-47e3-b084-601300382894)
 * [140pcs U Shape Solderless Breadboard Jumper Cable Wire Kit - 1,50€](https://www.aliexpress.com/item/140-pcs-U-Shape-Solderless-Breadboard-Jumper-Cable-Wire-Kit-For-Arduino-Shield-For-raspberry-pi/32581254395.html?spm=2114.01010208.3.1.kzhsar&ws_ab_test=searchweb0_0,searchweb201602_5_10152_10065_10151_10068_10136_10137_10303_10060_10302_10155_10062_437_10154_10056_10055_10054_10059_303_100031_10099_10103_10102_10096_5320015_10052_10053_10142_10107_10050_10051_10170_10084_10083_10119_10080_10082_10081_10110_519_10111_10112_10113_10114_10182_10078_10079_5260014_10073_10123_10120_10189_142,searchweb201603_16,ppcSwitch_4&btsid=e2bce3f4-7f6f-4537-b3a2-2adac506ea97&algo_expid=393f7e97-ddae-4037-88a8-b7b07635ab58-0&algo_pvid=393f7e97-ddae-4037-88a8-b7b07635ab58)
 * [5V Stepper Motor 28BYJ-48 With Drive Test Module Board ULN2003 5 Line 4 Phase - 2,50€](https://www.aliexpress.com/item/5V-Stepper-Motor-28BYJ-48-With-Drive-Test-Module-Board-ULN2003-5-Line-4-Phase/32615355685.html?spm=2114.01010208.3.9.H9UGn8&ws_ab_test=searchweb0_0,searchweb201602_5_10152_10065_10151_10068_10136_10137_10303_10060_10302_10155_10062_437_10154_10056_10055_10054_10059_303_100031_10099_10103_10102_10096_5320015_10052_10053_10142_10107_10050_10051_10170_10084_10083_10119_10080_10082_10081_10110_519_10111_10112_10113_10114_10182_10078_10079_5260014_10073_10123_10120_10189_142-10050_10119,searchweb201603_16,ppcSwitch_4&btsid=1832fb9b-ace3-448e-bee1-acfbbbfbc4b7&algo_expid=61c79ad0-cbcd-486a-a923-640d11ed8b1a-1&algo_pvid=61c79ad0-cbcd-486a-a923-640d11ed8b1a)
 * [38Khz MCU learning board IR remote control Infrared decoder for protocol remote control For Arduino .MP3 .MP4 - 1€](https://www.aliexpress.com/item/1pcs-lot-38khz-MCU-learning-board-IR-remote-control-Infrared-decoder-for-protocol-remote-control-For/32580594393.html?spm=2114.01010208.3.1.EhBe0H&ws_ab_test=searchweb0_0,searchweb201602_5_10152_10065_10151_10068_10136_10137_10303_10060_10302_10155_10062_437_10154_10056_10055_10054_10059_303_100031_10099_10103_10102_10096_5320015_10052_10053_10142_10107_10050_10051_10170_10084_10083_10119_10080_10082_10081_10110_519_10111_10112_10113_10114_10182_10078_10079_5260014_10073_10123_10120_10189_142,searchweb201603_16,ppcSwitch_4&btsid=d52e3b3e-bab1-401c-98ad-1be947b3be5a&algo_expid=5a8579d6-dd7a-4966-83f0-5ab4d9d1dd74-0&algo_pvid=5a8579d6-dd7a-4966-83f0-5ab4d9d1dd74)
 * [LED5 IR 940nm 20deg 12mW/sr - 2,50€](https://www.aliexpress.com/item/F273-10pcs-LED-5mm-940nm-IR-Infrared-Emitting-Round-Tube-Light-diode/32660619353.html?spm=2114.01010208.3.81.y3SZVO&ws_ab_test=searchweb0_0,searchweb201602_5_10152_10065_10151_10068_10136_10137_10303_10060_10302_10155_10062_437_10154_10056_10055_10054_10059_303_100031_10099_10103_5320014_10102_10096_10052_10053_10142_10107_10050_10051_10170_10084_10083_10119_10080_10082_10081_10110_519_10111_10112_10113_10114_10182_10078_10079_10073_5260013_10123_10120_10189_142-10120,searchweb201603_16,ppcSwitch_4&btsid=37d23504-3a1d-49b1-aecb-c0a7f1bcb1d7&algo_expid=f3c0ecc6-2a9d-4f27-a86b-1860be15d583-13&algo_pvid=f3c0ecc6-2a9d-4f27-a86b-1860be15d583)
 * [Piezo Piezoelectric Buzzer Alarm Speaker - 1€](https://www.aliexpress.com/item/3pcs-BCE-12606-Passive-12-Piezo-Piezoelectric-Buzzer-Alarm-Speaker-80dB-4KHz-3mA-12-5mm-6/32813510131.html?spm=2114.01010208.3.9.GaI4Y8&ws_ab_test=searchweb0_0,searchweb201602_5_10152_10065_10151_10068_10136_10137_10303_10060_10302_10155_10062_437_10154_10056_10055_10054_10059_303_100031_10099_10103_5320014_10102_10096_10052_10053_10142_10107_10050_10051_10170_10084_10083_10119_10080_10082_10081_10110_519_10111_10112_10113_10114_10182_10078_10079_10073_5260012_10123_10120_10189_142-10120,searchweb201603_16,ppcSwitch_4&btsid=de9e1d4e-f54f-44fe-9853-e4fe23b87d75&algo_expid=8c7101e2-9865-47cf-bb4e-0fbf91cd96d6-1&algo_pvid=8c7101e2-9865-47cf-bb4e-0fbf91cd96d6)
 * [Dupont line 40pcs 20cm male to female jumper wire - 1€](https://www.aliexpress.com/item/Free-shipping-Dupont-line-40pcs-20cm-male-to-female-jumper-wire-Dupont-cable-breadboard-cable-jump/32800430829.html?spm=2114.01010208.3.32.TgT93X&ws_ab_test=searchweb0_0,searchweb201602_5_10152_10065_10151_10068_10136_10137_10303_10060_10302_10155_10062_437_10154_10056_10055_10054_10059_303_100031_10099_10103_5320014_10102_10096_10052_10053_10142_10107_10050_10051_10170_10084_10083_10119_10080_10082_10081_10110_519_10111_10112_10113_10114_10182_10078_10079_10073_5260012_10123_10120_10189_142-10120,searchweb201603_16,ppcSwitch_4&btsid=f60ec63e-d421-4b9c-afca-ec7ee0a9d68a&algo_expid=078bcb28-5ef0-4704-bd9a-26d630a018f6-4&algo_pvid=078bcb28-5ef0-4704-bd9a-26d630a018f6)
 * 8x M2 DIN 912 12.9 ST Socket Cap Screws
 * 4x M3 DIN 433 ZN Flat Washer
 * [2x USB 2.0 Extension Cable A Male - A Female Round 2.00 m Black - 10€](https://www.aliexpress.com/item/Ugreen-Super-High-Speed-M-F-Male-To-Female-USB-3-0-Extension-Extender-Cable-Data/32415077335.html?spm=2114.01010208.3.3.iYSkbt&ws_ab_test=searchweb0_0,searchweb201602_5_10152_10065_10151_10068_10136_10137_10303_10060_10302_10155_10062_437_10154_10056_10055_10054_10059_303_100031_10099_10103_5320014_10102_10096_10052_10053_10142_10107_10050_10051_10170_10084_10083_10119_10080_10082_10081_10110_519_10111_10112_10113_10114_10182_10078_10079_5260014_10073_10123_10120_10189_142,searchweb201603_16,ppcSwitch_4&btsid=f40c2d2d-4858-4f43-b53f-5ed442dd9400&algo_expid=96f5c9da-ccba-4463-af5b-bb9a8aaf0ad4-0&algo_pvid=96f5c9da-ccba-4463-af5b-bb9a8aaf0ad4)
 * Unused Male USB cable to make your own power plug
 * [200W Auto Car/Home Inverter Converter Adapter 12V To 220V Charger Two USB With Alligator Clips Cable - 19€](https://www.aliexpress.com/item/New-200W-Auto-Car-Home-Inverter-Converter-Adapter-12V-To-220V-110V-Charger-Two-USB-With/32741342488.html?spm=2114.01010208.3.1.ikm2Yw&ws_ab_test=searchweb0_0,searchweb201602_5_10152_10065_10151_10068_10136_10137_10303_10060_10302_10155_10062_437_10154_10056_10055_10054_10059_303_100031_10099_10103_5320014_10102_10096_10052_10053_10142_10107_10050_10051_10170_10084_10083_10119_10080_10082_10081_10110_519_10111_10112_10113_10114_10182_10078_10079_5260014_10073_10123_10120_10189_142-10102_10119,searchweb201603_16,ppcSwitch_4&btsid=09b2109c-b9ca-4830-ba82-12eecf2d3fad&algo_expid=1e5bf778-75f5-4ade-aa17-e2a4e59b1c86-0&algo_pvid=1e5bf778-75f5-4ade-aa17-e2a4e59b1c86)
 * 70A car battery - 100€

Most parts can be bought @ https://www.aliexpress.com, list items are links to parts
* 1 261,50 € without camera
* 661,50 € with camera
* 461,50 € with camera and SD card
* 181,50 € with camera, SD card and tripod (you need to remodel and change code)

Transport not included

*PS: Arduino Nano comes with USB Nano plug, some idiot in Arduino department changed it, used to be micro*

### Printer

* Witbox 2
* Simplify3D
* ESUN 3D Printer Filament Black 1.75mm PLA 1KG Roll
* Tesa® 4329 Yellow Masking Tape 50mm x 50m

Witbox 2 comes without heat bed, which makes it 'cheaper,' you need to use masking tape otherwise won’t stick

Use the *TEST.gcode* to validate everything fits

#### No printer

There are companies who 3D print your STL files

### Programs

* Rhinoceros - 3D model
* 123Desing - Convert svg to stl
* Photoshop - Magic Wand tool
* Arduino IDE - the tool

If new to Rhinoceros then docs folder may help you

### Pitfalls

* Motor is weak when speed is increased
* Clean the gears from printing overhead using sandpaper
* Use extra washers to level motor
* Transfer gear has 1mm cap, cut cardboard circle to make a washer if needed
* I prefer smooth rotation, but motor may get stuck. Change the program to rotate motor less frequently with higher revolutions
* Sketch uses 28888 bytes (94%) of program storage space. Maximum is 30720 bytes.
* Global variables use 1426 bytes (69%) of dynamic memory, leaving 622 bytes for local variables. Maximum is 2048 bytes
* If everything fails, model second motor on other side
* Test before going hunting, it is homemade and may not work first time

## Prerequisites

* Soldering iron
* Sanding paper
* Micro USB male to USB male cable for Arduino Nano

## Install

1. Unzip arduino-libs.zip to ./Documents/Arduino/libraries on Mac, ..\<you>\Documents\Arduino on Win
2. Calibrate MPU sensor with project found in sensor calibration folder
3. Assemble, included few images in img folder

## Logging

Arduino IDE logging serial crashes after a while, use *log.pl*; don't forget to change parameters before use

On mac you may need to install module, requires Apple Developer Tools (XCode)
```
sudo perl -MCPAN -e 'install Device::SerialPort'
```

## Commands

Button | Command
------------ | -------------
1+NEXT | Motor forwards
1+PREV | Motor backwards
2 | 24h time lapse
3+N.+N | Take picture every N seconds
X | Cancel

## Final 

01. Water is flat on every level
02. Moon meteor craters are circular 90-degree angle impact holes
03. Polaris is fixed star
04. Stars are magnetic rings, 'Nikon P900 stars'
05. Setting sun shrinks and distances itself from viewer
06. Boats disappear behind the horizon just to be seen again using binoculars
07. Moon light temperature is few degrees colder in the shade
08. Water spins direction it was poured in, still water conforms to nearest path
09. Project White Alice used firmament above to bounce radio waves
10. All satellite dishes are pointing to nearest tower
11. GPS is ground based tower system
12. Deepest hole ever drilled is 12km, hit the firmament below
13. Amateur rockets have hit the firmament above and lost their momentum instantaneously
14. Amateur balloon footages prove the Earth is a flat plane
15. Most of the mainstream cameras come with Fish Eye lens
16. Your food is being poisoned with Chloride, Fluoride, Iron, GMO and other chemicals
17. Your soul is eternal, memories erased with vaccines
18. You ARE a slave to the monetary system which is privately owned medium
19. Schools are prisons to force false lies upon you
20. Every government is controlled by Rothschild dynasty (money) and Vatican Jesuit Pope (agenda)
21. Domes ecosystem has been damaged, majority of trees have been cut down
22. There are hidden ancient places: Puma Punku, Kailasa Temple, Lake Titicaca, Rock Gate, Baalbek Lebanon
23. There are people you never heard of: Edward LeedsKalnin, Viktor Schauberger, Richard E Bird, Eric Laithwaite, Bernhard Schmidt, Dmitri Maksutov, Giordano Bruno, Leonardo da Vinci, 
23. There are movies you never heard of: Nude on the Moon (1961),The Wild Women of Wongo (1958),Kings of the Sun (1963),Atlantis: The Lost Continent (1961),Ulysses (1954),The Ten Commandments (1956),Solomon and Sheba (1959),Sins of Jezebel (1953),Slaves of Babylon (1953),King of Kings (1961),The Robe (1953), The Vikings (1958), Demetrius and the Gladiators (1954), Seven Samurai (1954),The Magnificent Seven (1960),Return of the Magnificent Seven (1966), Invitation to a Gunfighter (1964),Taras Bulba (1962), 1776 (1972),Robinson Crusoe (1954),The Magnetic Monster (1953)
24. ALL mainstream media outlets are heavily censored and controller by powers in control
25. Hemp cures every illness mind can think of
26. Animals have souls, you eat your own flesh

![Earth](https://github.com/akotulu/nikon900arduino-motorizer/blob/master/Earth.gif)
