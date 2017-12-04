#!/usr/bin/env sh

gi import color
gi import cursor

GI_LIB_LOGGING=

log_success() {
  __echo_ok
  return 0
}

log_passed() {
  __echo_pass
  return $rc
}

log_failed() {
  __echo_fail
  return $rc
}

__echo_ok() {
  [ "$GI_LIB_LOGGING" = "color" ]
  color=$?
  [ $color ] && $MOVE_TO_COL
  echo -n "["
  [ $color ] && $SETCOLOR_SUCCESS
  echo -n $"  OK  "
  [ $color ] && $SETCOLOR_NORMAL
  echo -n "]"
  echo -ne "\r"
  return 0
}

__echo_pass() {
  [ "$GI_LIB_LOGGING" = "color" ]
  color=$?
  [ $color ] && $MOVE_TO_COL
  echo -n "["
  [ $color ] && $SETCOLOR_WARNING
  echo -n $" PASS "
  [ $color ] && $SETCOLOR_NORMAL
  echo -n "]"
  echo -ne "\r"
  return 1
}

__echo_fail() {
  [ "$GI_LIB_LOGGING" = "color" ]
  color=$?
  [ $color ] && $MOVE_TO_COL
  echo -n "["
  [ $color ] && $SETCOLOR_FAILURE
  echo -n $" FAIL "
  [ $color ] && $SETCOLOR_NORMAL
  echo -n "]"
  echo -ne "\r"
  return 1
}
