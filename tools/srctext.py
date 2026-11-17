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


_DIRECT = {}    # (path, root) -> ((mtime_ns, size), [repository paths its `#include "src/..."` lines name])


def included(path, root=None):
    """The repository paths `path` includes through `#include "src/..."`, recursively.

    Each file's own include lines are read once per modification time: tools ask this of every member
    of a unity-built unit (unitprofiles.asm_body_names), and re-reading its fragments for each one was
    most of an uncached `make check`."""
    root = root or ROOT
    key = (path, root)
    st = os.stat(path)
    stamp = (st.st_mtime_ns, st.st_size)
    hit = _DIRECT.get(key)
    if hit is None or hit[0] != stamp:
        with open(path, errors="replace") as fh:
            text = fh.read()
        hit = _DIRECT[key] = (stamp, [os.path.relpath(os.path.join(root, m.group(1)), root)
                                      for m in _INCLUDE.finditer(text)])
    out = []
    for rel in hit[1]:
        inc = os.path.join(root, rel)
        if os.path.isfile(inc):
            out.append(rel)
            out.extend(included(inc, root))
    return out
