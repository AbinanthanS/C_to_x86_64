#!/usr/bin/env bash
set -euo pipefail

./scripts/build.sh

# Ensure MinGW runtime DLLs are found when running tests
export PATH="/c/mingw64/bin:$PATH"

ctest --test-dir build --output-on-failure
