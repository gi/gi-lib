#!/usr/bin/env bash

if [ -z "${file:-}" ]; then
  file="${BASH_SOURCE[0]}"
  file="${file}" sh "${file}"
  exit $?
fi

source "$(cd "$(dirname "${file}")" && pwd)/_.sh"


example "Command Substitution" '$(command)'
x="$(echo foo)"
[ "$x" = "foo" ] && pass || fail
