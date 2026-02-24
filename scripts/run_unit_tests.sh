#!/usr/bin/env bash
set -euo pipefail
export PATH="/c/mingw64/bin:$PATH"
./build/c2x64_tests.exe "$@"