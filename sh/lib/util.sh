#!/usr/bin/env bash


cd-up () {
  local depth=$1
  [ -z "${depth}" ] && depth=1
  while ((depth-- > 0)); do
    cd ..
  done
}
