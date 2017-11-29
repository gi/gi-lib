#!/usr/bin/env sh
# Terminal Control: Color Escape Codes
#
# Select Graphic Rendition codes

color() {
  attr="$1"; shift
  case "$attr" in
    reset)
      # reset color attributes
      tput sgr0 ;;
    fg | bg)
      # set foreground/background
      case "$attr" in
        fg) attr=setaf ;;
        bg) attr=setab ;;
      esac
      color="$1"; shift
      case "$color" in
        [0-9]*) ;;
        # normal intensity
        k | black) color=0 ;;
        r | red) color=1 ;;
        g | green) color=2 ;;
        y | yellow) color=3 ;;
        b | blue) color=4 ;;
        m | magenta) color=5 ;;
        c | cyan) color=6 ;;
        w | white) color=7 ;;
        # bright intensity
        k+ | bright-black | grey | gray) color=8 ;;
        r+ | bright-red) color=9 ;;
        g+ | bright-green) color=10 ;;
        y+ | bright-yellow) color=11 ;;
        b+ | bright-blue) color=12 ;;
        m+ | bright-magenta) color=13 ;;
        c+ | bright-cyan) color=14 ;;
        w+ | bright-white) color=15 ;;
        *)
          echo "error: unknown color descriptor '$color'" >&2
          return 1
          ;;
      esac
      tput "$attr" "$color"
      ;;
    bold)
      tput bold ;;
    dim)
      tput dim ;;
    rev | reverse)
      tput rev ;;
    blink)
      tput blink ;;
    ul | underline)
      option="$1"; shift
      case "$option" in
        1 | on)
          tput smul ;;
        0 | off)
          tput rmul ;;
        *)
          echo "error: unknown option '$option'" >&2
          return 1
          ;;
      esac
      ;;
    *)
      echo "error: unknown attribute '$attr'" >&2
      return 1
      ;;
  esac
}

