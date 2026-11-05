#!/bin/bash
# Run decomp-permuter on one function. Long-running by design -- it is a search.
set -eu
DIR=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$DIR/../../.." && pwd)
PERMUTER=${DW4_PERMUTER:-$ROOT/local/decomp-permuter}
VENV_PY=${DW4_PERMUTER_PY:-$ROOT/local/permuter-venv/bin/python}

[ -x "$VENV_PY" ] || { echo "missing venv: python3 -m venv $ROOT/local/permuter-venv && $ROOT/local/permuter-venv/bin/pip install toml" >&2; exit 2; }
[ -d "$PERMUTER" ] || { echo "missing permuter at $PERMUTER" >&2; exit 2; }

export DW4_WIBO=${DW4_WIBO:-$ROOT/local/wibo}
export DW4_MWCC=${DW4_MWCC:-$ROOT/local/mwcps2/3.0-011126/mwccps2.exe}

bash "$DIR/build_target.sh"
exec "$VENV_PY" "$PERMUTER/permuter.py" "$DIR" -j "$(nproc)" "$@"
