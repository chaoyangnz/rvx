# RVX

A xv6 port on D1.

> Currently I run on Nezha.

## Prerequisite

- [MangoPI MQ Pro](https://mangopi.org/mangopi_mqpro)
- [xfel](https://github.com/xboot/xfel/releases)
- [FTDI driver for USB-Serial](https://ftdichip.com/drivers/) or [Zadig](https://zadig.akeo.ie/) or `sudo apt-get install libusb-1.0-0-dev`

## Get started 
```
npm install --global xpm@latest
xpm install
./dev build
./dev start
```

## OpenSBI

```
make PLATFORM=generic FW_FDT_PATH=../d1.dtb CROSS_COMPILE=../riscv64-linux-x86_64-20200528/bin/riscv64-unknown-linux-gnu- BUILD_INFO=y FW_TEXT_ADDR=0x80000000 FW_JUMP_ADDR=0x40000000
```

## Ramdisk

The ramdisk image is embedded in `ramdisk.h`. We have to build and generate a new one automatically updating the header.

## Serial port output with `\r\n`

It is recommended to right-click in MobaXterm, `change terminal settings..`, then tick `Implicit CR in every LF`. Otherwise, the new line will not be moved to the beginning of next line.
