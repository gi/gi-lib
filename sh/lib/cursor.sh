#!/usr/bin/env sh
# Terminal Control: Cursor Escape Codes
#
# See 'man terminfo' for more descriptions of attributes.

cursor() {
  attr="$1"; shift
  case "$attr" in
    cols)
      # print the number of columns
      tput cols ;;
    rows)
      # print the number of rows/lines
      tput lines ;;

    # Movement

    save)
      # save the cursor position
      tput sc ;;
    restore)
      # restore the cursor position
      tput rc ;;
    pos)
      # set the cursor position: row col
      tput cup $1 $2 ;;
    row | posv)
      # set the vertical position (row)
      tput vpa $1 ;;
    col | posh)
      # set the horizontal position (column)
      tput hpa $1 ;;
    mvb | mvl | left)
      # move left/backwards
      tput cub ${1:-1} ;;
    mvf | mvr | right)
      # move right/forwards
      tput cuf ${1:-1} ;;
    mvu | up)
      # move up
      tput cuu ${1:-1} ;;
    mvd | dn | down)
      # move down
      tput cud ${1:-1} ;;
    mvul | home)
      # move to upper left, first row & column (if no cup)
      tput home ;;
    mvll | last)
      # move to lower left, last row & first column (if no cup)
      tput ll ;;
    cr)
      # carriage return
      tput cr ;;
    nl)
      # new line
      tput nel ;;

    # Visibility

    visnorm)
      # make visibility normal (undo visibility adjustments)
      tput cnorm ;;
    vishigh)
      # make visibility high
      tput cvvis ;;
    viszero)
      # make invisible
      tput civis ;;

    # Default

    *)
      tput "$attr" "$@"
  esac
}
