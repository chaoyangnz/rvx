
## OpenSBI

```
make PLATFORM=generic FW_FDT_PATH=../d1.dtb CROSS_COMPILE=../riscv64-linux-x86_64-20200528/bin/riscv64-unknown-linux-gnu- BUILD_INFO=y FW_TEXT_ADDR=0x40000000 FW_JUMP_ADDR=0x80000000
```