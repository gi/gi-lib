#!/usr/bin/env bash


OS_INFO="$(uname -a)" # all the system info

# the machine hardware name
# e.g. x86 / x86_64
OS_MACH="$(uname -m)"

# the processor architecture name
# e.g. i386
OS_ARCH="$(uname -p)"
case "${OS_ARCH}" in
  x86) OS_ARCH='i386' ;;
  x86_64) OS_ARCH='i386' ;;
esac

# the kernel name
OS_KERNEL="$(uname -s)"
case "${OS_KERNEL}" in
  Linux) OS_KERNEL='linux' ;;
  Darwin) OS_KERNEL='darwin' ;;
  MINGW*) OS_KERNEL='windows' ;;
esac

# the kernel version
OS_KERNEL_V="$(uname -v)"
