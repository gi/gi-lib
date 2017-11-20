#!/usr/bin/env bash

ECHO_PREFIX="$(basename $0): "

echo-r () {
  echo -e "\033[31m$@\033[0m"
}

echo-g () {
  echo -e "\033[32m$@\033[0m"
}

echo-y () {
  echo -e "\033[33m$@\033[0m"
}

echo-b () {
  echo -e "\033[34m$@\033[0m"
}

echo-m () {
  echo -e "\033[35m$@\033[0m"
}

echo-c () {
  echo -e "\033[36m$@\033[0m"
}

echo-w () {
  echo -e "\033[37m$@\033[0m"
}

echo-trace () {
  echo -e "${ECHO_PREFIX}[TRACE] $@"
}

echo-debug () {
  echo -e "${ECHO_PREFIX}[DEBUG] $@"
}

echo-info () {
  echo -e "${ECHO_PREFIX}[INFO] $@"
}

echo-warn () {
  echo -e "${ECHO_PREFIX}[\033[33mWARN\033[0m] $@"
}

echo-error () {
  echo -e "${ECHO_PREFIX}[\033[31mERROR\033[0m] $@"
}

echo-pass () {
  echo -e "${ECHO_PREFIX}[\033[32mPASS\033[0m] $@"
}

echo-fail () {
  echo -e "${ECHO_PREFIX}[\033[31mFAIL\033[0m] $@"
}
