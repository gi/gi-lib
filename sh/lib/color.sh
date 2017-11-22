#!/usr/bin/env bash
# Terminal Control: Color Escape Codes

tpt0="$(tput sgr0)"  # default

# Foreground
tptfgk="$(tput setaf 0)"  # black
tptfgr="$(tput setaf 1)"  # red
tptfgg="$(tput setaf 2)"  # green
tptfgy="$(tput setaf 3)"  # yellow
tptfgb="$(tput setaf 4)"  # blue
tptfgm="$(tput setaf 5)"  # magenta
tptfgc="$(tput setaf 6)"  # cyan
tptfgw="$(tput setaf 7)"  # white

# Foreground (intense)
tptfgki="$(tput setaf 8)"  # black (intense)
tptfgri="$(tput setaf 9)"  # red (intense)
tptfggi="$(tput setaf 10)"  # green (intense)
tptfgyi="$(tput setaf 11)"  # yellow (intense)
tptfgbi="$(tput setaf 12)"  # blue (intense)
tptfgmi="$(tput setaf 13)"  # magenta (intense)
tptfgci="$(tput setaf 14)"  # cyan (intense)
tptfgwi="$(tput setaf 15)"  # white (intense)

# Background
tptbgk="$(tput setab 0)"  # black
tptbgr="$(tput setab 1)"  # red
tptbgg="$(tput setab 2)"  # green
tptbgy="$(tput setab 3)"  # yellow
tptbgb="$(tput setab 4)"  # blue
tptbgm="$(tput setab 5)"  # magenta
tptbgc="$(tput setab 6)"  # cyan
tptbgw="$(tput setab 7)"  # white

# Background (intense)
tptbgki="$(tput setab 8)"  # black (intense)
tptbgri="$(tput setab 9)"  # red (intense)
tptbggi="$(tput setab 10)"  # green (intense)
tptbgyi="$(tput setab 11)"  # yellow (intense)
tptbgbi="$(tput setab 12)"  # blue (intense)
tptbgmi="$(tput setab 13)"  # magenta (intense)
tptbgci="$(tput setab 14)"  # cyan (intense)
tptbgwi="$(tput setab 15)"  # white (intense)

# Styles
tptbold="$(tput bold)"  # bold
tptdim="$(tput dim)"  # dim
tptul1="$(tput smul)"  # underline (on)
tptul0="$(tput rmul)"  # underline (off)
tptrev="$(tput rev)"  # reverse
tptblink="$(tput blink)"  # blink
tptso1="$(tput smso)"  # standout (on)
tptso0="$(tput rmso)"  # standout (off)
