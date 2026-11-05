#!/bin/bash
# Driven by decomp-permuter as:  bash compile.sh <source.c> -o <out.o>
#
# Same C-vs-C++ squeeze as the FUN_00130060 harness, plus one more turn:
#   * the permuter REQUIRES the candidate to be named `base.c`, but MWCC picks the
#     language from the file EXTENSION and this idiom needs C++ (only C++ has
#     `bool`), so the source is copied to a .cpp path;
#   * the permuter's own parser is C-only, so `bool` has to be introduced by a
#     `typedef _Bool bool;` line that only the C view (and pycparser) sees;
#   * decomp-permuter PREPROCESSES the candidate with `cpp` (in C mode) and hands
#     that C text to this script, so by the time MWCC sees it the #ifdef is gone
#     and the typedef is unconditional — and MWCC's C++ front end does not know
#     `_Bool`, so it errors on it. Drop the typedef line; C++ has a real `bool`.
ROOT=$(cd "$(dirname "$0")/../../.." && pwd)
WIBO=${DW4_WIBO:-$ROOT/local/wibo}
MWCC=${DW4_MWCC:-$ROOT/local/mwcps2/3.0-011126/mwccps2.exe}
export MWCIncludes=${MWCIncludes:-$(dirname "$1")}
tmp=$(mktemp --suffix=.cpp)
sed '/^typedef .* bool;$/d' "$1" > "$tmp"
"$WIBO" "$MWCC" -c -O3 "$tmp" -o "$3"
rc=$?
rm -f "$tmp"
exit $rc
