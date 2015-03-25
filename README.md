ChipStomp Guitar Effects Pedal
==============================

![ChipStomp](https://catmacey.files.wordpress.com/2014/06/img_0744.jpg?w=869)

This is a digital guitar effects pedal based on the Arduino compatible Chipkit DP32 platform.
The project is a merging of a ChipKit DP32 with an Open Music Labs Stompshield in a custom build PCB.

The Chipkit is an arduino compatible platform powered by a 32bit Microchip PIC processor running at 40Mhz with 32Kb RAM and 128Kb flash.  

The project is relativly simple in that it limits itself to using the PIC's internal RAM, built in 10bit ADC and utilizes two 8bit PWMs to form a single 16bit output.  Also included is a 128x64px 1.3" OLED to provide a nice user interface.

Currently the following effects are completed.
- **Flanger** : Classic wobbly tape effect.

- **Tremolo** : Low frequency modulation of the source audio.

- **Pitch shift** : Change the pitch (up or down) of the source audio without changing the playback speed.

- **Echo/Delay** : A simple lo-fi delay (700ms Max) that when combined with a bit of analogue feedback provides a nice echo.

- **Bitcrusher** : Reduces the sample rate by ratios down to 1/64 of the source rate, also reduces the bit-depth to create some nice messy sounds.

You can have all or just some of these effect running at the same time with each passing its output onto the next effects input. 


[More information is available on my blog.](http://catmacey.wordpress.com/tag/chipstomp/)


Copyright (C) 2014 Matt Casey : catmacey.com
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
	
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
