#!/usr/bin/env bash


###############################################################################
# Prints the directory of the canonical absolute path of `path`.
#
# All relative path identifiers (`.` and `..`) and symbolic links are resolved.
# If `path` is a symbolic link, the result is the directory of the file after
# following the link, recursively if necessary.
#
# Globals:
#   None
# Options:
#   None
# Arguments:
#   path - the path to resolve
# Returns:
#   None
# See:
#   absdir
###############################################################################
realdir() {
  local path="${1:-}"
  local dir="$( cd -P "$( dirname "${path}" )" && pwd -P )"
  # resolve until no longer a symlink
  while [ -h "${path}" ]; do
    path="$(readlink "${path}")"
    # if 'path' is a relative path, resolve it relative to 'dir'
    # the directory containing the link
    [[ "${path}" != /* ]] && path="${dir}/${path}"
    dir="$( cd -P "$( dirname "${path}" )" && pwd -P )"
  done
  echo "${dir}"
}


GI_SHLIB_DIR="$(realdir "${BASH_SOURCE[0]}")"

gi() {
  local action="${1:-}"; shift
  case "${action}" in
    import)
      for lib in "$@"; do
        local libpath="${GI_SHLIB_DIR}/${lib}.sh"
        if [ ! -f "${libpath}" ]; then
          echo "gi: unknown library '${lib}'" >&2
          return 1
        fi
        source "${libpath}"
      done
      ;;
    *)
      local script="${GI_SHLIB_DIR}/${action}.sh"
      if [ ! -f "${script}" ]; then
        echo "gi: unknown action '${action}'" >&2
        return 1
      fi
      ${SHELL} "${script}" "$@"
      return $?
      ;;
  esac
}
