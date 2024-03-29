# stm8_minibadges
Repository of mini badges using the stm8s001j3.

![Metroid](/Metroid/metroid.gif)
![Pitfall](/Pitfall/pitfall.gif)
![Doom](/Doom/doom.gif)
![Phoenix](/Phoenix/s2.gif)

This repo contains all the source code and eagle files for the mini badges I've designed using the STM8S001J3 microprocessor. I've loved this little chip as it's cheaper than an ATTiny and extremely versatile. The package design leaves a bit to be desired as it wastes one pin for a required cap and the pin 1 marking is horrible but for $.23 you can't complain much.

## Assembly

I'd recommend soldering the LCD down first, followed by the STM8 chip (note the orientation) then the resistor and capacitor. Finally, solder on the pin header legs once all the surface mount components are down. 

![Layout](/layout.JPG)


## Flashing

In all my stm8 projects I do bare metal programming and utilize no libraries (I'm usually wanting to make the most of that 8K flash)

There’s also a lot of code reuse between these projects. I could probably do better at managing that, meh...

The following tools are required to compile and flash the chips:
* [ST-Link V2](http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2050601.m570.l1313.TR0.TRC0.H0.Xstlink+v2.TRS0&_nkw=stlink+v2&_sacat=0)
* [sdcc](https://sourceforge.net/projects/sdcc/files/snapshot_builds/)
* [stm8flash](https://github.com/vdudouyt/stm8flash)

![Pinmap](/pins.png)

To flash the badge there are only three that need to be connected from the ST-Link to the minibadge. 
* That is 3V3 to the lower 3V
* GND to ether GND
* SWIM to NC12 (4th pin from the right on the bottom row)

Usually, the process for compiling and flashing is the same for all projects. That is:

```bash
>sdcc -lstm8 -mstm8 --out-fmt-ihx main.c
>stm8flash -c stlinkv2 -p stm8s001j3 -w main.ihx
```

The stm8flash command usually needs to be executed twice, the first rarely takes.
A successful flash outputs something similar to this

```
Determine FLASH area
Due to its file extension (or lack thereof), "main.ihx" is considered as INTEL HEX format!
4456 bytes at 0x8000... OK
Bytes written: 4456
```

I apologize for the lack of code comments but I don’t really care enough to do something about it :/

The colors may be inverted depending on the TFT LCD type you have. The simple fix is to locate the line `ST7735_Write(ST7735_INVOFF, CMD);` in the main.c file and change it to `ST7735_Write(ST7735_INVON, CMD);` or vice versa. Then recompile and reflash.

The official documentation for this chip can be found at https://www.st.com/resource/en/datasheet/stm8s001j3.pdf
