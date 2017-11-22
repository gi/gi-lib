#!/usr/bin/env bash

if [ -z "${PROJECT_DIR}" ]; then
  echo-error "project directory not defined" >&2
  exit 1
fi

PROJECT_ENV_DIR="${PROJECT_DIR}/env"
PROJECT_ENV_FILE="${PROJECT_ENV_DIR}/env.sh"
PROJECT_LOGS_DIR="${PROJECT_DIR}/logs"
PROJECT_SCRIPTS_DIR="${SCRIPTS_DIR}/scripts"


project-var-set () {
  local var="$1"
  local val="$2"
  if [[ -z "${var}" || -z "${val}" ]]; then
    echo-error "invalid variable name/value" >&2; return 1
  fi
  if [[ $(grep "${var}=" "${PROJECT_ENV_FILE}") ]]; then
    val="$(echo "${val}" | sed 's/\//\\\//g')"
    sed -i '.bak' "s/${var}=.*/${var}=\"${val}\"/" "${PROJECT_ENV_FILE}"
  else
    echo "export ${var}=\"${val}\"" >> "${PROJECT_ENV_FILE}"
  fi
}

project-path-add () {
  local path="$1"
  if [[ -z "${path}" ]]; then
    echo-error "missing path" >&2; return 1
  fi
  if [[ $(grep "PATH=\"${path}:" "${PROJECT_ENV_FILE}") ]]; then
    return
  fi
  echo "PATH=\"${path}:\${PATH}\"" >> "${PROJECT_ENV_FILE}"
}

project-env-add-source () {
  local path="$1"
  if [[ -z "${path}" ]]; then
    echo-error "missing path" >&2; return 1
  fi
  if [[ $(grep "source '${path}'" "${PROJECT_ENV_FILE}") ]]; then
    return
  fi
  echo "source '${path}'" >> "${PROJECT_ENV_FILE}"
}

project-bootstrap () {
  touch "${PROJECT_ENV_FILE}"

  project-update-env OS_INFO "${OS_INFO}"
  project-update-env OS_MACH "${OS_MACH}"
  project-update-env OS_ARCH "${OS_ARCH}"
  project-update-env OS_KERNEL "${OS_KERNEL}"
  project-update-env PROJECT_DIR "${PROJECT_DIR}"
  project-update-env PROJECT_ENV_DIR "${PROJECT_ENV_DIR}"
  project-update-env PROJECT_ENV_FILE "${PROJECT_ENV_FILE}"
  project-update-env PROJECT_LOGS_DIR "${PROJECT_LOGS_DIR}"
  project-update-env PROJECT_SCRIPTS_DIR "${PROJECT_SCRIPTS_DIR}"
  project-update-env PROJECT_SERVICES_DIR "${PROJECT_SERVICES_DIR}"

  project-add-path "${PROJECT_SCRIPTS_DIR}"
}

source "${PROJECT_ENV_FILE}"
