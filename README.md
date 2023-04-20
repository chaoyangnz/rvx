# RVX

A xv6 port on D1.

> Currently I run on Nezha.

## Prerequisite

- [MangoPI MQ Pro](https://mangopi.org/mangopi_mqpro)

Linux or WSL:
- [xfel](https://github.com/xboot/xfel/tree/master/docs#linux-platform-1)
- USB-UART driver: `sudo apt-get install libusb-1.0-0-dev`

Windows:
- [xfel](https://github.com/xboot/xfel/releases) (we don't use xfel in Windows actually)
- [Driver for FTDI USB-UART converter](https://ftdichip.com/drivers/)
- [FEL Driver for Allwinner Technology sunxi SoC OTG](https://zadig.akeo.ie/), this one is for FEL mode

Both: usbipd

https://blog.golioth.io/program-mcu-from-wsl2-with-usb-support/

## Get started 

In Windows:

```
usbipd wsl list
# find the bus_id of vid 1f3a:efe8
usbipd wsl -a -b 1-8
```

Now open a Serial session in Mobxterm, select serial device "COM3 (USB Serial Port (COM3))", baud rate is 115200bps

In WSL Ubuntu:

```
lsusb
# an additional usb device
# Bus 001 Device 004: ID 1f3a:efe8 Allwinner Technology sunxi SoC OTG connector in FEL/flashing mode
```

```
npm install --global xpm@latest
xpm install
./dev build
./dev start
```

check the serial port output in the above Mobxterm session tab.

## OpenSBI

```
make PLATFORM=generic FW_FDT_PATH=../d1.dtb CROSS_COMPILE=../riscv64-linux-x86_64-20200528/bin/riscv64-unknown-linux-gnu- BUILD_INFO=y FW_TEXT_ADDR=0x80000000 FW_JUMP_ADDR=0x40000000
```

## Ramdisk

The ramdisk image is embedded in `ramdisk.h`. We have to build and generate a new one automatically updating the header.

## Serial port output with `\r\n`

It is recommended to right-click in MobaXterm, `change terminal settings..`, then tick `Implicit CR in every LF`. Otherwise, the new line will not be moved to the beginning of next line.
