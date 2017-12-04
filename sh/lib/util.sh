#!/usr/bin/env sh


cdup() {
  local depth="${1:-1}"
  local dir="$( pwd )"
  while ((depth-- > 0)); do
    dir="$( dirname "${dir}" )"
  done
  cd "${dir}"
}
