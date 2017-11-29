#!/usr/bin/env bash


realdir () {
  local file=$1
  local dir
  # resolve until no longer a symlink
  while [ -h "${file}" ]; do
    dir="$(cd -P "$(dirname "$file")" && pwd)"
    file="$(readlink "$file")"
    # if relative symlink, we need to resolve it relative to the path where the symlink file was located
    [[ $file != /* ]] && file="$dir/$file"
  done
  dir="$(cd -P "$(dirname "$file")" && pwd)"
  echo "$dir"
}

GI_SHLIB_DIR="$(realdir "${BASH_SOURCE[0]}")"

gi_import () {
  source "${GI_SHLIB_DIR}/$1.sh"
}
