"""units.py — resolve a symbol to its definition in a multi-function source file.

The repository holds *translation units*: `src/lua/api.c` defines 116 functions,
`src/game/camera.c` will define a system's worth.  The matching build, though, is
per function — `verify_one` compiles one function and compares its 4-byte words to
retail, and the relink places one object per function.  This module is the bridge:
it finds the function definitions in a file and can emit the file with all but one
of them removed, so any single function can be compiled on its own.

The removal is by blanking, not by rebuilding the file: every byte outside the
dropped definitions is kept, so `#include`s, prototypes, `extern` declarations,
`typedef`s, file-scope `static` *declarations* and `inline` helpers survive.  (A plain
`static` function that a sibling calls would be dropped with its definition; make it
`inline` or put it in a header, so a unit stays self-contained.)

This is deliberately a text transform, not a C parser: the code being split is
machine-generated and regular, and the compiler remains the authority on whether
the result is valid.
"""
import itertools
import os
import re
import asmsources
import srctext
import unitobjects

_EXTS = (".c", ".cpp", asmsources.EXT)
# Temp prefixes for the one-function splits; skipped by `scan`, ignored by git.
TMP_PREFIX = "dw4u_"
_SEQ = itertools.count()


def _clean(text):
    """Comments and string/char literals -> spaces, newlines preserved.

    Length and line structure are unchanged, so offsets into the result are valid
    offsets into the original — which is what lets `extract` blank a definition.
    """
    out, i, n = [], 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
            out.append(" " * (j - i))
            i = j
        elif c == "/" and i + 1 < n and text[i + 1] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append("".join(ch if ch == "\n" else " " for ch in text[i:j]))
            i = j
        elif c in "\"'":
            q, j = c, i + 1
            while j < n:
                if text[j] == "\\":
                    j += 2
                    continue
                if text[j] == q:
                    j += 1
                    break
                j += 1
            out.append(" " * (j - i))
            i = j
        else:
            out.append(c)
            i += 1
    return "".join(out)


def _match_brace(clean, i):
    """Index just past the `}` that closes the `{` at `i`."""
    depth = 0
    n = len(clean)
    while i < n:
        if clean[i] == "{":
            depth += 1
        elif clean[i] == "}":
            depth -= 1
            if depth == 0:
                return i + 1
        i += 1
    return n


def _declarator_name(sig):
    """The function name in a definition signature, or None.

    Not simply "the last identifier before a `(`": a parameter can be a function
    pointer (`int (**arg0)()`), whose `int (` looks like a declarator.  The position
    that actually names the function is the identifier before the paren that opens
    the parameter list — the one whose matching `)` is the last thing before `{`.
    """
    s = sig.rstrip()
    if s.endswith(")"):
        depth = 0
        for k in range(len(s) - 1, -1, -1):
            if s[k] == ")":
                depth += 1
            elif s[k] == "(":
                depth -= 1
                if depth == 0:
                    j = k
                    while j > 0 and s[j - 1].isspace():
                        j -= 1
                    e = j
                    while j > 0 and (s[j - 1].isalnum() or s[j - 1] == "_"):
                        j -= 1
                    if e > j:
                        return s[j:e]
                    break
    m = None
    for mm in re.finditer(r"([A-Za-z_]\w*)\s*\(", sig):   # K&R fallback
        m = mm
    return m.group(1) if m else None


# A K&R definition head: `name(a, b)`, then one declaration per parameter, then the body's `{`.
_KR_HEAD = re.compile(r"[^;(){}]*\b([A-Za-z_]\w*)\s*\(\s*[A-Za-z_]\w*(?:\s*,\s*[A-Za-z_]\w*)*\s*\)"
                      r"\s*(?:[^;(){}]+;\s*)+\Z")


def _kr_head(clean, starts, brace):
    """(name, start) of the K&R definition whose body opens at `brace`, or None.

    The parameter declarations end in `;`, so by the `{` the statement scan has moved past
    the declarator: `starts` holds the statements since the last definition to look back over.
    """
    for start in starts:
        m = _KR_HEAD.match(clean, start, brace)
        if m and m.end() == brace:
            return m.group(1), start
    return None


def definitions(text):
    """-> [(name, start, end)] top-level function definitions, in file order.

    A top-level `{` opens a definition when the text since the previous top-level
    `;`/`}`/definition holds a declarator (`name(`).  `extern "C" { … }` and other
    bare blocks have no declarator and are skipped; an `extern "C" { ... }` linkage block is transparent (its definitions are
    top-level ones; the wrapper itself stays in place when `extract` blanks the others).
    """
    clean = _clean(text)
    out, depth, stmt_start, i, n = [], 0, 0, 0, len(clean)
    in_extern = False
    starts = []
    while i < n:
        c = clean[i]
        if c == "#" and depth == 0 and not clean[clean.rfind("\n", 0, i) + 1:i].strip():
            # a preprocessor line, continuations included, is skipped whole: braces in a
            # one-line `#define F(x) do { ... } while (0)` would otherwise end the statement
            # early and make the next directive read as a definition of `F`
            end = i
            while True:
                end = clean.find("\n", end)
                if end < 0:
                    end = n
                    break
                if clean[end - 1] != "\\":
                    break
                end += 1
            if not clean[stmt_start:i].strip():
                stmt_start = end + 1
            i = end + 1
            continue
        if c == "{":
            if depth == 0:
                sig = clean[stmt_start:i]
                if sig.strip() == "extern" and not in_extern:
                    # `extern "C" { ... }` (the string literal is blanked by _clean) is a linkage block, not a body:
                    # the definitions inside it are top-level definitions
                    in_extern = True
                    stmt_start = i + 1
                    i += 1
                    continue
                name = _declarator_name(sig)
                if not sig.strip():
                    head = _kr_head(clean, starts, i)
                    if head:
                        name, stmt_start = head
                        sig = clean[stmt_start:i]
                if name and sig.strip() and not clean[stmt_start:i + 1].lstrip().startswith("#"):
                    end = _match_brace(clean, i)
                    # Start at the declaration, not at the comment/whitespace before
                    # it: `clean` blanks comments to spaces, so the leading blanks
                    # are the file's provenance header, which must not become part
                    # of the emitted body.
                    seg = clean[stmt_start:i]
                    start = stmt_start + (len(seg) - len(seg.lstrip()))
                    out.append((name, start, end))
                    i, stmt_start, depth = end, end, 0
                    starts = []
                    continue
            depth += 1
        elif c == "}":
            if depth == 0 and in_extern:
                in_extern = False
                stmt_start = i + 1
                i += 1
                continue
            depth = max(0, depth - 1)
            if depth == 0:
                stmt_start = i + 1
                starts = []
        elif c == ";" and depth == 0:
            starts.append(stmt_start)
            stmt_start = i + 1
        elif c == "\n" and depth == 0:
            # a preprocessor line is not part of a definition's signature.  Without this,
            # an `#include` left as the only thing before a file's first function makes
            # that function look like it starts with `#`, so `definitions` skips it --
            # which silently broke `extract` for a unit whose first function needed no
            # forward declaration (found when scripts/retype_receiver_class.py added the
            # reflected.h include to src/game/beNDMWItemDisk.c).
            if clean[stmt_start:i].lstrip().startswith("#"):
                stmt_start = i + 1
        i += 1
    return out


def scan(src_dir="src", symbols="config/SLUS-20836/symbols.txt", unit_objects=None):
    """{symbol: path} for every function defined under `src_dir`.

    The filename is no longer the symbol once a file holds several functions, so
    this reads the definitions rather than trusting the name. Registered
    compiler-emitted members share their actual owner's source path.
    """
    out, shared = {}, set()
    for root, dirs, files in os.walk(src_dir):
        dirs.sort()
        for f in sorted(files):
            if not f.endswith(_EXTS) or f.startswith(TMP_PREFIX):
                continue
            path = os.path.join(root, f)
            if asmsources.is_assembly(path):
                # only an owner-approved hand-written routine may be assembly (tools/asmsources.py)
                found = [(name, 0, 0) for name in asmsources.approved_definitions(path)]
            else:
                # a unity-built library unit is only includes of its fragments: read what the
                # compiler sees
                found = definitions(srctext.read(path))
            for name, _s, _e in found:
                # A stock file can hold a definition its build compiles out (pngrutil.c's WinCE
                # strtod). Its unit row names what it really defines, so such a name stays with
                # the source that owns it.
                if os.sep + "third_party" + os.sep in path and name in out:
                    continue
                # within one file these are `#ifdef` alternatives; a real clash fails to compile
                if out.get(name, path) != path:
                    # two stock files may each keep a `static` of one name: the unit row says
                    # which is the retail function, and a name retail lacks belongs to neither
                    if not unitobjects.is_shared_static(name, symbols, unit_objects):
                        raise ValueError("%s defines %s, already defined in %s"
                                         % (path, name, out[name]))
                    shared.add(name)
                out[name] = path
    for name in shared:
        del out[name]
    return unitobjects.augment_sources(out, symbols, unit_objects)


def extract(text, name):
    """`text` with every top-level definition except `name` blanked out.

    The result is a compilable one-function unit that keeps the file's includes,
    prototypes and declarations.
    """
    kept = False
    buf = list(text)
    for nm, s, e in definitions(text):
        if nm == name:
            kept = True
            continue
        if re.search(r"\binline\b", text[s:text.index("{", s)]):
            continue
        for k in range(s, e):
            if buf[k] != "\n":
                buf[k] = " "
    if not kept:
        raise KeyError("%s is not defined here" % name)
    return "".join(buf)


def standalone(path, name, symbols="config/SLUS-20836/symbols.txt", unit_objects=None):
    """A compilable path for one function of `path` -> (path, temp-to-remove|None).

    A registered emitted member selects its owner's source definition.
    A single-function file is returned untouched (the common case, and it keeps
    `make check` from writing 6,000 temp files), and so is a whole-file unit.  A multi-function file is split
    into a dot-named sibling, so `#include`s relative to the unit still resolve and
    `scan` skips it.
    """
    if asmsources.is_assembly(path):
        text = open(path).read()
        if len(asmsources.definitions(text)) <= 1:
            return path, None
        tmp = os.path.join(os.path.dirname(path),
                           "%s%d_%d%s" % (TMP_PREFIX, os.getpid(), next(_SEQ), asmsources.EXT))
        open(tmp, "w").write(asmsources.extract(text, name))
        return tmp, tmp
    text = open(path).read()
    name = unitobjects.source_owner(name, symbols, unit_objects)
    if len(definitions(text)) <= 1 or unitobjects.is_whole_file(name, symbols, unit_objects):
        return path, None
    ext = os.path.splitext(path)[1]
    # The name is deliberately short and has no leading dot: MWCC reads `.foo.c`
    # as the extension `foo.c` and refuses it, and it truncates paths past ~80
    # characters, which a symbol-named temp easily exceeds (`Gap__Bec__…`).
    tmp = os.path.join(os.path.dirname(path),
                       "%s%d_%d%s" % (TMP_PREFIX, os.getpid(), next(_SEQ), ext))
    open(tmp, "w").write(extract(text, name))
    return tmp, tmp
