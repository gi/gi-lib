#!/usr/bin/env sh
#
# Utilities for path names.


###############################################################################
# Prints the absolute path of `file`.
#
# All relative path identifiers (`.` and `..`) are resolved. If `file` is a
# symbolic link, the result is the path of the link, not of the file to which
# it points.
#
# Note: By default, the result is dependent on whether the shell is configured
# to resolve symbolic links to directories to the real/physical directory
# (e.g. `set -P` or `set +P`). Use option `-L` or `-P` to override.
#
# Globals:
#   None
# Options:
#   -L - resolve directories logically
#   -P - resolve directories physically
# Arguments:
#   file - the file/directory to resolve
# Returns:
#   None
# See:
#   realpath
#   http://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
###############################################################################
abspath() {
  local opt=
  case "${1:-}" in
    -L) opt='-L'; shift ;;
    -P) opt='-P'; shift ;;
  esac
  local path="${1:-}"
  local base=
  if [ ! -d "${path}" ]; then
    base="$( basename "${path}" )"
    path="$( dirname "${path}" )"
  fi
  local dir="$( cd ${opt} "${path}" && pwd ${opt} )"
  echo "${dir}/${base}"
}


###############################################################################
# Prints the directory of the absolute path of `file`.
#
# All relative path identifiers (`.` and `..`) are resolved. If `file` is a
# symbolic link, the result is the directory of the link, not the file to which
# it points.
#
# Note: By default, the result is dependent on whether the shell is configured
# to resolve symbolic links to directories to the real/physical directory
# (e.g. `set -P` or `set +P`). Use option `-L` or `-P` to override.
#
# Globals:
#   None
# Options:
#   -L - resolve directories logically
#   -P - resolve directories physically
# Arguments:
#   file - the file/directory to resolve
# Returns:
#   None
# See:
#   realdir
#   http://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
###############################################################################
absdir() {
  echo "$( dirname "$( abspath "$@" )" )"
}


alias exists='test -e'

# Types

istype() {
  local type="${1:-}"; shift
  local path="${1:-}"; shift
  local expr=
  if [ $# -ne 0 ]; then
    echo "istype: too many arguments" >&2
    return 1
  fi
  case "${type}" in
    a | any)
      expr="-e '${path}'" ;;
    b | block)
      expr="-b '${path}'" ;;
    c | char)
      expr="-c '${path}'" ;;
    d | dir | directory)
      expr="-d '${path}'" ;;
    f | file | reg | regular)
      expr="-f '${path}'" ;;
    l | link | h)
      expr="-h '${path}'" ;;
    p | pipe | fifo)
      expr="-p '${path}'" ;;
    s | socket)
      expr="-S '${path}'" ;;
    o | other)
      expr="! \( -f '${path}' -o -d '${path}' -o -h '${path}' \)" ;;
    *)
      echo "unknown type descriptor '${type}'" >&2
      return 1
      ;;
  esac
  eval test ${expr}
}

# Permissions

isperm() {
  local perm="${1:-}"; shift
  local path="${1:-}"; shift
  local expr=
  if [ $# -ne 0 ]; then
    echo "isperm: too many arguments" >&2
    return 1
  fi
  case "${perm}" in
    r | read) expr="-r ${path}" ;;
    w | write) expr="-w ${path}" ;;
    x | exec) expr="-x ${path}" ;;
    *)
      echo "unknown permission descriptor '${perm}'" >&2
      return 1
      ;;
  esac
  eval test ${expr}
}

# Flags

isflag() {
  local flag="${1:-}"; shift
  local path="${1:-}"; shift
  local expr=
  if [ $# -ne 0 ]; then
    echo "isperm: too many arguments" >&2
    return 1
  fi
  case "${flag}" in
    u | uid | suid) expr="-u ${path}" ;;
    g | gid | sgid) expr="-g ${path}" ;;
    *)
      echo "unknown flag descriptor '${flag}'" >&2
      return 1
      ;;
  esac
  eval test ${expr}
}


isabs() {
  true
}


issame() {
  true
}
