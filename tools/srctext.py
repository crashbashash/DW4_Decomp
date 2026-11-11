"""srctext.py — read a source file the way the compiler sees it.

A unity-built library unit is a short `.cpp` that only includes its header and its per-class
fragments by repository-relative path (`#include "src/engine/gui/igButton.inc"`); MWCC resolves
those from the working directory every compile runs in.  Tools that read definitions from source
text must see what the compiler sees, so `read()` replaces each `#include "src/..."` line with
the included file's text, recursively.  Other includes (`"dw4/..."`, system headers) are left as
they are: they hold declarations, not the unit's code.
"""
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]+"(src/[^"]+)"[^\n]*$', re.M)


def read(path, root=None, errors=None, _stack=()):
    """The text of `path` with every `#include "src/..."` expanded in place."""
    root = root or ROOT
    with open(path, errors=errors) as fh:
        text = fh.read()
    if '#' not in text or 'include' not in text:
        return text
    real = os.path.realpath(path)
    if real in _stack:
        raise ValueError("%s includes itself" % path)

    def expand(m):
        inc = os.path.join(root, m.group(1))
        if not os.path.isfile(inc):
            return m.group(0)
        return read(inc, root, errors, _stack + (real,))

    return _INCLUDE.sub(expand, text)


def included(path, root=None):
    """The repository paths `path` includes through `#include "src/..."`, recursively."""
    root = root or ROOT
    out = []
    with open(path, errors="replace") as fh:
        text = fh.read()
    for m in _INCLUDE.finditer(text):
        inc = os.path.join(root, m.group(1))
        if os.path.isfile(inc):
            out.append(os.path.relpath(inc, root))
            out.extend(included(inc, root))
    return out
