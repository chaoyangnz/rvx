#!/usr/bin/env bash

BIN_PATH=build/debug
BIN_FILE=${BIN_PATH}/arvos.bin

PATH=$PATH:./xpacks/.bin

clean() {
  rm -rf build
}

build() {
  cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -B build/release .
  cd build/release
  make
  cd -

  cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" -B build/debug .
  cd build/debug
  make
  cd -
}

start() {
  debug=$1
  flags=""
  path="build/release"
  if [ "$debug" == 'debug' ]; then
    flags="-gdb tcp::1234 -S"
    path="build/debug"
  fi
  sudo xfel ddr d1
#  sudo xfel write 0x80000000 fw_jump.bin
  sudo xfel write 0x40000000 ${BIN_FILE}
  sudo xfel exec 0x40000000
#  sudo xfel exec 0x80000000
}

stop() {
    #telnet localhost 4321 << EOF
    #quit
    #EOF

    { sleep 2; echo "quit";  } | telnet localhost 4321
}

monitor() {
    telnet localhost 4321
}

debug() {
  ./xpacks/.bin/riscv-none-elf-gdb \
  ${BIN_FILE} \
  -ex "set arch riscv:rv64" \
  -ex "target remote localhost:4321"
}

command=$1
subcommand=$2

case $command in
  help)
    echo "Usage: ./dev.sh clean|build|start|monitor|stop"
    ;;
  clean)
    clean
    ;;
  build)
    build $subcommand
    ;;
  start)
    start $subcommand
    ;;
  monitor)
    monitor
    ;;
  stop)
    stop
    ;;
  debug)
    debug
    ;;
  *)
    build
    start
    ;;
esac
