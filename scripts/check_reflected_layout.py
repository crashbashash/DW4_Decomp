#!/usr/bin/env python3
"""Check include/dw4/reflected.h with the host C compiler: it must compile as plain C11, every field
must sit at the offset the reflection metadata recorded, every struct must have the size its class
registers, and every field's type must be the one its MetaField kind prescribes.

Why: the technical specification retargets recovered code to a host build that keeps four-byte
references (an arena of 32-bit handles, port/docs/project/pointer-model.md). That only holds if the
generated structs are portable C and their layout does not depend on the compiler that reads them. The
offsets and sizes in the comments of reflected.h are the authority (data/reflection.json and the
registered instance size from asm/<Class>_Register.s); this turns each into
`_Static_assert(offsetof(Class, field) == N)` / `_Static_assert(sizeof(Class) == N)` and compiles the lot
with `cc -std=c11`. A struct that fails here would silently shift every field after it on the host.

The type check is the one scripts/gen_type_headers.py's own tables prescribe: a vector or matrix
field is `float[2|3|4|16]` whatever its position (a trailing `igVec4fMetaField` used to be emitted as
a lone `int`, which made igFogAttr 32 bytes instead of 44), a scalar kind has its scalar type, and an
array kind has its element type. The exceptions the generator records (`typed int: N matched units
read it as a word`) are accepted as such.

Usage: scripts/check_reflected_layout.py [--header include/dw4/reflected.h] [--cc cc] [--keep FILE]
Exit status 0 when the header compiles and all asserts hold.
"""
import argparse
import os
import re
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from gen_type_headers import ARRAY, SCALAR, VECTOR  # noqa: E402  (the generator's own tables)

STRUCT_RE = re.compile(r"/\* handle 0x[0-9a-f]+, \d+ field\(s\), sizeof (\d+) [^*]*\*/\n"
                       r"typedef struct (\w+) \{(.*?)\} \2;", re.S)
FIELD_RE = re.compile(r"^\s*([A-Za-z_][\w ]*?)\s*\*?(\w+)((?:\[\d+\])?)\s*;\s*(/\*[^*]*\*/\s*)?/\*\s*\+(\d+)\s+(\w+)",
                      re.M)
WORD_TYPED_RE = re.compile(r"/\* typed int: \d+ matched units read it as a word")


def expected_type(kind, ctype, count):
    """None when (ctype, count) is what `kind` prescribes, else the expected spelling."""
    if kind in SCALAR:
        want = SCALAR[kind][0]
        return None if (ctype, count) == (want, None) else want
    if kind in VECTOR:
        elem, n = VECTOR[kind]
        if (ctype, count) == (elem, n) or (ctype == "unsigned char" and count == 4 * n):
            return None
        return "%s[%d]" % (elem, n)
    if kind in ARRAY:
        elem = ARRAY[kind]
        if ctype == elem and count is not None:
            return None
        if ctype == "unsigned char" and count is not None:
            return None  # a misaligned array kept as bytes
        return "%s[N]" % elem
    return None  # igStructMetaField and unknown kinds: the span rule, nothing to prescribe


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--header", default="include/dw4/reflected.h")
    ap.add_argument("--cc", default=os.environ.get("CC", "cc"))
    ap.add_argument("--keep", help="write the generated check file here instead of a temp file")
    a = ap.parse_args()
    text = open(a.header, errors="replace").read()
    lines = ['#include <stddef.h>', '#include "dw4/%s"' % os.path.basename(a.header)]
    n_struct = n_field = n_size = n_type = 0
    type_errors = []
    for m in STRUCT_RE.finditer(text):
        size, cls, body = int(m.group(1)), m.group(2), m.group(3)
        n_struct += 1
        n_size += 1
        lines.append('_Static_assert(sizeof(%s) == %d, "sizeof %s");' % (cls, size, cls))
        for fm in FIELD_RE.finditer(body):
            ctype, name, arr, note, off, kind = fm.groups()
            if name.startswith("_pad"):
                continue
            n_field += 1
            lines.append('_Static_assert(offsetof(%s, %s) == %d, "%s.%s");' % (cls, name, int(off), cls, name))
            if note and WORD_TYPED_RE.match(note.strip()):
                continue  # a recorded exception, kept as a word on purpose
            count = int(arr[1:-1]) if arr else None
            want = expected_type(kind, ctype.strip(), count)
            n_type += 1
            if want is not None:
                type_errors.append("%s.%s +%s: %s is %s%s, kind %s wants %s"
                                   % (cls, name, off, name, ctype.strip(), arr, kind, want))
    if n_struct == 0:
        print("reflected layout: FAILED (no `sizeof N` struct headers found in %s)" % a.header)
        return 1
    lines.append("int main(void) { return 0; }")
    src = "\n".join(lines) + "\n"
    path = a.keep or tempfile.NamedTemporaryFile(suffix=".c", delete=False).name
    open(path, "w").write(src)
    try:
        r = subprocess.run([a.cc, "-std=c11", "-fsyntax-only", "-Iinclude", path],
                           capture_output=True, text=True)
    finally:
        if not a.keep:
            os.unlink(path)
    if r.returncode or type_errors:
        sys.stderr.write(r.stderr[:4000])
        for e in type_errors[:40]:
            sys.stderr.write("  " + e + "\n")
        print("reflected layout: FAILED (%d structs, %d fields checked, %d type errors)"
              % (n_struct, n_field, len(type_errors)))
        return 1
    print("reflected layout: %d structs, %d field offsets, %d struct sizes and %d field types verified "
          "with the host compiler" % (n_struct, n_field, n_size, n_type))
    return 0


if __name__ == "__main__":
    sys.exit(main())
