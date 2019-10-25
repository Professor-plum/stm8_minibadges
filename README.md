# stm8_minibadges
Repository of mini badges using the stm8s001j3.

This repo contains all the source code and eagle files for the mini badges I've designed using the STM8S001J3 microprocessor. I've loved this little chip as it's cheaper than an ATTiny and extremely versatile. The package design leaves a bit to be desired as it wastes one pin for a required cap and the pin 1 marking is horrible but for $.23 you can't complain much.

In all my stm8 projects I do bare metal programming and utilize no libraries (I'm usually wanting to make the most of that 8K flash)

There’s also a lot of code reuse between these projects. I could probably do better at managing that, meh...

The following tools are required to compile and flash the chips:
* [ST-Link V2](http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2050601.m570.l1313.TR0.TRC0.H0.Xstlink+v2.TRS0&_nkw=stlink+v2&_sacat=0)
* [sdcc](https://sourceforge.net/projects/sdcc/files/snapshot_builds/)
* [stm8flash](https://github.com/vdudouyt/stm8flash)

Usually the process for compiling and flashing is the same for all projects. That is:

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

I apologize for the lack of code comments but don’t really care enough to do something about it :/
