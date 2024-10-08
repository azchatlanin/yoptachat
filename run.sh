#!/bin/zsh

PROJECT_NAME=$(basename $PWD)

run() {
  command meson compile -C build 
  if [[ -z "$1" ]]; then
    cd build
    ./bin/$PROJECT_NAME
    cd ..
  else
    meson test $1 -C build
  fi
}

if [ -d "build" ]; then
  run
else
  command meson setup build
  run
fi

