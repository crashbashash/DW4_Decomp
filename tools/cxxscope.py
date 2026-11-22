#!/usr/bin/env python3
"""cxxscope.py — the one spelling of a converted class's out-of-line definitions.

The kit's .cpp files (alchemy-kit_202309 sources/lib/insight, sources/lib/viewer) and igen's generated ODLSource
define a class's members inside the class's namespaces, the head naming the class alone:

    namespace Gap {
    namespace Gui {

    void igRenderer::setVisualContext(igVisualContext *context)
    {
        ...
    }

    }
    }

never `void Gap::Gui::igRenderer::setVisualContext(...)` at file scope. tools/gen_odl_source.py writes its fragments
this way and tools/memberize.py writes its definitions this way; both take the block's lines from here.

`respell(text)` rewrites a file's file-scope definitions whose head qualifies a Gap class
(`T Gap::<Library>::<Class>::<member>(...) {`, a static datum `T Gap::<Library>::<Class>::<name>;`) into that form:
the head loses `Gap::<Library>::` (and so does its return type, which the block's scope now finds), and each run of
such definitions of one library with nothing but blanks and comments between them goes into one block, the comment
lines right above the first going in with it. A block that ends where another of the same library begins becomes one.
A free function between two members ends a block: it stays outside, where its linkage is the one it had.

Unqualified names in a member's body are looked up in its class and the class's namespaces either way; the head's
return type is the only text the block's scope reads differently, and the declaration in the class (inside the
same namespaces) already reads it that way.
"""
import re
import sys
import os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import units  # noqa: E402

_QUALIFIED = re.compile(r"\bGap\s*::\s*([A-Za-z_]\w*)\s*::\s*([A-Za-z_]\w*)\s*::\s*"
                        r"(operator\s*(?:new|delete)\b(?:\s*\[\s*\])?|~?\s*[A-Za-z_]\w*)")
_BLOCK_HEAD = re.compile(r"(?m)^namespace Gap \{\nnamespace ([A-Za-z_]\w*) \{\n")


def _member_name(name):
    """A member's name as a head spells it: `~igRenderer`, `operator new`, `operator delete[]`."""
    if name.startswith("operator"):
        return "operator " + re.sub(r"\s+", "", name[len("operator"):])
    return re.sub(r"\s+", "", name)


def split(qualified):
    """(`Gap::Gui`, `igRenderer`) for `Gap::Gui::igRenderer`; ("", name) for a class in no namespace."""
    parts = [p for p in re.split(r"\s*::\s*", qualified) if p]
    return "::".join(parts[:-1]), parts[-1]


def open_lines(namespace):
    """The lines opening `namespace` (`Gap::Gui`): one `namespace X {` per level."""
    return ["namespace %s {" % part for part in namespace.split("::") if part]


def close_lines(namespace):
    return ["}" for part in namespace.split("::") if part]


def _blocks(clean):
    """[(start, end)] of the text inside every `namespace ... {` block of a file (its `clean` text)."""
    out = []
    for m in re.finditer(r"\bnamespace\s+[A-Za-z_]\w*\s*\{", clean):
        out.append((m.end(), units._match_brace(clean, m.end() - 1)))
    return out


def _first_paren(head):
    depth = 0
    for i, ch in enumerate(head):
        if ch == "<":
            depth += 1
        elif ch == ">":
            depth -= 1
        elif ch == "(" and depth <= 0:
            return i
    return -1


def _statement_start(clean, pos):
    at = max(clean.rfind(";", 0, pos), clean.rfind("}", 0, pos), clean.rfind("{", 0, pos)) + 1
    while True:
        while at < pos and clean[at].isspace():
            at += 1
        line = clean.rfind("\n", 0, at) + 1
        if at < pos and clean[at] == "#" and not clean[line:at].strip():
            end = clean.find("\n", at)
            at = pos if end < 0 or end > pos else end + 1
            continue
        return at


def _strip_namespace(text, library):
    """`text` with each `Gap::<library>::` qualification dropped (the block's scope finds the name)."""
    return re.sub(r"\bGap\s*::\s*%s\s*::\s*" % re.escape(library), "", text)


def _items(text, clean):
    """[(start, end, library, edits)] of the file-scope definitions to respell: (start, end) the definition's
    text, edits [(start, end, replacement)] inside it."""
    blocks = _blocks(clean)
    inside = lambda pos: any(s <= pos < e for s, e in blocks)  # noqa: E731
    items, defs = [], units.definitions(text)
    for _name, start, end in defs:
        if inside(start):
            continue
        brace = clean.find("{", start)
        head = clean[start:brace]
        paren = _first_paren(head)
        if paren < 0:
            continue
        found = [m for m in _QUALIFIED.finditer(head, 0, paren) if not head[m.end():paren].strip()]
        if not found:
            continue
        m = found[-1]
        library = m.group(1)
        edits = [(start, start + m.start(), _strip_namespace(text[start:start + m.start()], library)),
                 (start + m.start(), start + m.end(), "%s::%s" % (m.group(2), _member_name(m.group(3))))]
        items.append((start, end, library, edits))
    for m in _QUALIFIED.finditer(clean):
        if inside(m.start()) or any(s <= m.start() < e for _n, s, e in defs):
            continue
        start = _statement_start(clean, m.start())
        lead = clean[start:m.start()]
        after = re.match(r"\s*([;=\[])", clean[m.end():])
        if not after or re.search(r"\bextern\b|[=(&]", lead) or not re.search(r"[A-Za-z_]", lead) or \
                clean[max(0, m.start() - 3):m.start()].rstrip().endswith((".", "->", "::")):
            continue
        end = clean.find(";", m.end())
        if end < 0:
            continue
        library = m.group(1)
        edits = [(start, m.start(), _strip_namespace(text[start:m.start()], library)),
                 (m.start(), m.end(), "%s::%s" % (m.group(2), m.group(3)))]
        items.append((start, end + 1, library, edits))
    return sorted(items)


def _lead_comments(text, clean, start):
    """Where a definition's own comment lines begin: the comment-only lines right above its first line."""
    at = text.rfind("\n", 0, start) + 1
    while at > 0:
        prev = text.rfind("\n", 0, at - 1) + 1
        line, blank = text[prev:at - 1], clean[prev:at - 1]
        if not line.strip() or blank.strip():
            break
        at = prev
    return at


def respell(text):
    """`text` with its Gap-qualified file-scope definitions in their namespaces (the module docstring)."""
    clean = units._clean(text)
    items = _items(text, clean)
    if not items:
        return merge_blocks(text)
    groups = []
    for item in items:
        start = _lead_comments(text, clean, item[0])
        if groups and groups[-1][-1][2] == item[2] and not clean[groups[-1][-1][1]:item[0]].strip() \
                and groups[-1][-1][1] <= start:
            groups[-1].append(item)
        else:
            groups.append([item])
    out, at = [], 0
    for group in groups:
        start = _lead_comments(text, clean, group[0][0])
        end = text.find("\n", group[-1][1])
        end = len(text) if end < 0 else end + 1
        namespace = "Gap::" + group[0][2]
        out.append(text[at:start])
        out.append("\n".join(open_lines(namespace)) + "\n\n")
        pos = start
        for _s, _e, _lib, edits in group:
            for s, e, r in edits:
                out.append(text[pos:s])
                out.append(r)
                pos = e
        out.append(text[pos:end])
        if not text[pos:end].endswith("\n"):
            out.append("\n")
        out.append("\n".join(close_lines(namespace)) + "\n")
        at = end
    out.append(text[at:])
    return merge_blocks("".join(out))


def merge_blocks(text):
    """`text` with each `namespace Gap { namespace X {` block that only blanks separate from the next block of the
    same library made one block with it."""
    while True:
        clean = units._clean(text)
        heads = [(m.start(), m.group(1), units._match_brace(clean, m.start() + len("namespace Gap "))) for m in
                 _BLOCK_HEAD.finditer(text) if not clean[clean.rfind("\n", 0, m.start()) + 1:m.start()].strip()]
        merged = False
        for (a_start, a_lib, a_end), (b_start, b_lib, _b_end) in zip(heads, heads[1:]):
            closers = text.rfind("}\n}", 0, a_end)
            if a_lib != b_lib or text[a_end:b_start].strip() or closers != a_end - 3:
                continue
            body_end = text.rfind("\n", 0, closers) + 1           # the inner block's last line ends here
            head_end = b_start + len("namespace Gap {\nnamespace %s {\n" % b_lib)
            if text[head_end:head_end + 1] == "\n":
                head_end += 1
            text = text[:body_end] + "\n" + text[head_end:]
            merged = True
            break
        if not merged:
            return text
