#!/usr/bin/env sh


cdup () {
  local depth=$1
  [ -z "${depth}" ] && depth=1
  while ((depth-- > 0)); do
    cd ..
  done
}
