#!/bin/bash

set -ueo pipefail

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
cd "$SCRIPT_DIR"

git ls-files '*.cpp' '*.hpp' | xargs -n16 clang-format -i
