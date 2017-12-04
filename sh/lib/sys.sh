#!/usr/bin/env sh
#
# System information and functions.
#
# For possible values, see https://en.wikipedia.org/wiki/Uname.

###############################################################################
# The system/kernel name.
#
# The value is derived from `uname -s` (POSIX).
###############################################################################
SYS_NAME="$(uname -s 2> /dev/null)"

###############################################################################
# The machine hardware name.
#
# The value is derived from `uname -m` (POSIX).
###############################################################################
SYS_MACH="$(uname -m 2> /dev/null)"

###############################################################################
# The processor architecture name.
#
# The value is derived from `uname -p`.
###############################################################################
SYS_ARCH="$(uname -p 2> /dev/null)"

###############################################################################
# The operating system name.
#
# The value is derived from `uname -o`.
###############################################################################
SYS_OS="$(uname -o 2> /dev/null)"

###############################################################################
# The system release identifier.
#
# The value is derived from `uname -r` (POSIX).
###############################################################################
SYS_RELEASE="$(uname -r 2> /dev/null)"

###############################################################################
# The system/kernel version
#
# The value is derived from `uname -v` (POSIX).
###############################################################################
SYS_VERSION="$(uname -v 2> /dev/null)"
