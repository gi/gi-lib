#!/usr/bin/env bash
#
# http://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_04

if [ -z "${file:-}" ]; then
  file="${BASH_SOURCE[0]}"
  file="${file}" sh "${file}"
  exit $?
fi

source "$(cd "$(dirname "${file}")" && pwd)/_.sh"


example "Arithmetic Expansion" '((expression))'
x=$((1 + 1))
[ "$x" -eq 2 ] && pass || fail

example "Arithmetic Expansion" '((x))'
x=1
x=$((x + 1))
[ "$x" -eq 2 ] && pass || fail

example "Arithmetic Expansion" '(($x))'
x=1
x=$(($x + 1))
[ "$x" -eq 2 ] && pass || fail

example "Arithmetic Expansion" '((x++))'
x=1
y=$((x++))
[ "$x" -eq 2 -a "$y" -eq 1 ] && pass || fail

example "Arithmetic Expansion" '((x--))'
x=1
y=$((x--))
[ "$x" -eq 0 -a "$y" -eq 1 ] && pass || fail

example "Arithmetic Expansion" '((++x))'
x=1
y=$((++x))
[ "$x" -eq 2 -a "$y" -eq 2 ] && pass || fail

example "Arithmetic Expansion" '((--x))'
x=1
y=$((--x))
[ "$x" -eq 0 -a "$y" -eq 0 ] && pass || fail

example "Arithmetic Expansion" 'exit code'
((1 == 1)); x=$?; ((1 == 2)); y=$?
[ $x -eq 0 -a $y -ne 0 ] && pass || fail
