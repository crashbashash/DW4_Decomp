#!/bin/bash
# Driven by decomp-permuter as:  bash compile.sh <source.c> -o <out.o>
#
# Two constraints collide and this script resolves them:
#   * the permuter REQUIRES the candidate to be named `base.c` (it checks for
#     exactly that filename, and it is the file it mutates), but
#   * MWCC only provides a `bool` type in C++ mode, and it selects the language
#     from the file EXTENSION.
# Retail materialises the flag test as a boolean, so we need C++: copy the source
# to a .cpp path and let MWCC see that instead.
ROOT=$(cd "$(dirname "$0")/../../.." && pwd)
WIBO=${DW4_WIBO:-$ROOT/local/wibo}
MWCC=${DW4_MWCC:-$ROOT/local/mwcps2/3.0-011126/mwccps2.exe}
export MWCIncludes=${MWCIncludes:-$(dirname "$1")}
tmp=$(mktemp --suffix=.cpp)
cp "$1" "$tmp"
"$WIBO" "$MWCC" -c -O3 "$tmp" -o "$3"
rc=$?
rm -f "$tmp"
exit $rc
