# RVX

A xv6 port on D1.

> Currently I run on Nezha.


# Development (Ubuntu)

## Prerequisite

- [Nazhe](https://d1.docs.aw-ol.com/en/d1_dev/)

Unbuntu:
- USB-UART driver: `sudo apt install libusb-1.0-0-dev`
- build [xfel](https://github.com/xboot/xfel/tree/master/docs#linux-platform-1)
- COM GUI: [cutecom]: `sudo apt install cutecom`

## Validation

- `lsusb`

Bus 001 Device 004: ID 0403:6001 Future Technology Devices International, Ltd FT232 Serial (UART) IC
Bus 001 Device 005: ID 1f3a:efe8 Allwinner Technology sunxi SoC OTG connector in FEL/flashing mode

`sudo adduser <user> dialout`

- `sudo xfel version`

AWUSBFEX ID=0x00185900(D1/F133) dflag=0x44 dlength=0x08 scratchpad=0x00045000

## Build

```
npm install --global xpm@latest
xpm install
./dev build
```

Now open a Serial session in `Cutecom` GUI, select serial device "/dev/ttyUSB0", baud rate is 115200bps

Run `./dev start`

See UTART output in `Cutecom`.


# Development (Windows + WSL)

## Prerequisite

- [MangoPI MQ Pro](https://mangopi.org/mangopi_mqpro)

WSL:
- build [xfel](https://github.com/xboot/xfel/tree/master/docs#linux-platform-1)
- USB-UART driver: `sudo apt-get install libusb-1.0-0-dev`

Windows:
- [xfel](https://github.com/xboot/xfel/releases) (we don't use xfel in Windows actually)
- [Driver for FTDI USB-UART converter](https://ftdichip.com/drivers/)
- [FEL Driver for Allwinner Technology sunxi SoC OTG](https://zadig.akeo.ie/), this one is for FEL mode

Both: usbipd

https://blog.golioth.io/program-mcu-from-wsl2-with-usb-support/

## Validation

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

## BUild

```
npm install --global xpm@latest
xpm install
./dev build
./dev start
```

check the serial port output in the above Mobxterm session tab.

