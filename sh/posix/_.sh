#!/usr/bin/env sh

__test_id=0
__test_name=''
__test_text=''

example () {
  __test_id=$((${__test_id} + 1))
  __test_name="${1:-}"
  __test_text="${2:-}"
}

pass () {
  text="Test ${__test_id} ${__test_name}: ${__test_text}"
  printf "%-60s $(tput setaf 2)PASS$(tput sgr0)\n" "${text}"
}

fail () {
  text="Test ${__test_id} ${__test_name}: ${__test_text}"
  printf "%-60s $(tput setaf 1)FAIL$(tput sgr0)\n" "${text}"
}
