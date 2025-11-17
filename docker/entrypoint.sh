#!/bin/bash
set -euo pipefail

APP_DIR=${APP_DIR:-/app}
BUILD_DIR=${BUILD_DIR:-${APP_DIR}/build}
BINARY_NAME=${BINARY_NAME:-PuyoGame}
EXECUTABLE="${BUILD_DIR}/${BINARY_NAME}"

configure_and_build() {
	cmake -S "${APP_DIR}" -B "${BUILD_DIR}"
	cmake --build "${BUILD_DIR}" -- -j"$(nproc)"
}

if [[ ! -x "${EXECUTABLE}" || "${FORCE_REBUILD:-0}" == "1" ]]; then
	echo "Building ${BINARY_NAME} with CMake..."
	configure_and_build
fi

CMD_TO_RUN=("$EXECUTABLE")
if [[ $# -gt 0 ]]; then
	CMD_TO_RUN=("$@")
fi

SHOULD_USE_HEADLESS=0
if [[ "${FORCE_HEADLESS:-0}" == "1" ]]; then
	SHOULD_USE_HEADLESS=1
elif [[ -z "${DISPLAY:-}" ]]; then
	SHOULD_USE_HEADLESS=1
else
	DISPLAY_NUMBER=${DISPLAY##*:}
	DISPLAY_NUMBER=${DISPLAY_NUMBER%%.*}
	SOCK_PATH="/tmp/.X11-unix/X${DISPLAY_NUMBER}"
	if [[ ! -S "${SOCK_PATH}" ]]; then
		echo "Warning: DISPLAY=${DISPLAY} but ${SOCK_PATH} is not accessible. Falling back to headless mode."
		SHOULD_USE_HEADLESS=1
	fi
fi

if [[ "${SHOULD_USE_HEADLESS}" == "1" ]]; then
	XVFB_RESOLUTION=${XVFB_RESOLUTION:-1920x1080x24}
	echo "Starting ${CMD_TO_RUN[*]} via Xvfb (${XVFB_RESOLUTION})."
	exec xvfb-run --auto-servernum --server-args="-screen 0 ${XVFB_RESOLUTION}" "${CMD_TO_RUN[@]}"
else
	echo "Starting ${CMD_TO_RUN[*]} with DISPLAY=${DISPLAY}."
	exec "${CMD_TO_RUN[@]}"
fi
