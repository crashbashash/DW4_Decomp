#!/usr/bin/env python3
"""apply_names.py — apply `config/SLUS-20836/names/` to the tree as one verified batch.

Renaming a function is a cross-file refactor: its unit file, the definition inside
it, every caller in `src/`, the `asm/<name>.s` unit and the label every other asm
unit jumps to all carry the name.  Doing that by hand, one function at a time, is
why naming stalled; a whole module's worth can be done at once instead.

For every overlay entry whose name differs from `config/SLUS-20836/symbols.txt`:

  1. rewrite each reference to `<old>` as `<new>` in every source, header and `.inc`
     fragment under `src/` and `include/`, which covers the definition, every
     declaration and every call site, in the function column of
     `config/source-approvals.tsv` and `config/assembly-sources.tsv`, and in the
     `emitted`/`duplicates`/`externals` keys and `symbol` of
     `config/SLUS-20836/unit-objects.json` (by address: a key is renamed only when the
     address it holds is the renamed function's);
  2. move a one-function unit to `src/<module>/` (the overlay's third column);
  3. delete the stale `asm/<old>.s`;
  4. regenerate `config/SLUS-20836/symbols.txt` and `asm/` with `tools/split.py`, which also
     rewrites every asm caller's `jal` for free.

A reference is an identifier that names the function.  The rewrite reads the C
around each occurrence and leaves alone what is not one:

  * string and character literals (retail data: a CRI error string naming its
    function must stay byte-exact) and `#include` paths;
  * a member (`.x`, `->x`, `Class::x`), a struct/class field, a tag, a label, a
    macro name, and a local, parameter or file `static` of the same name together
    with every use inside its scope;
  * comment words, when the old name is also an ordinary identifier or a plain
    lower-case word.

It refuses the batch, before writing anything, when:

  * an old name is also an ordinary identifier in the tree (a member, field, local,
    parameter, label or tag: renaming the start-up `entry` must not touch every
    `entry` local).  The error lists each file and use; `--generic NAME` rewrites
    that name's references anyway, still skipping everything listed above;
  * a batch reuses a name (`A` moves from X to Y while X gets a new name, a swap or
    a chain) and a file's text does not say whether it already uses the batch's
    names.  The evidence is the file's other batch names (an old-only name means it
    has not been renamed, a new-only name that it has) and the address order of its
    definitions.  A file already using the new names is left as it is; `--assume-old
    PATH` / `--assume-new PATH` settle a file the evidence does not;
  * a rewritten reference would be captured by a local, parameter or C++ member of
    the new name, or a C++ file has a member of the old name and unqualified uses.

All renames of one file happen in one pass, so a swap never renames its own result.

Dry-run by default.  After `--apply`, `make check` must still be green and
`make link` byte-identical — the batch is only done when both are.

  apply_names.py                       # show what would change
  apply_names.py --apply               # do it
  apply_names.py --apply --no-regen    # skip step 4 (e.g. symbols already current)
  apply_names.py --apply --check       # ...and run make check + make link
"""
import argparse
import json
import os
import re
import shutil
import subprocess
import sys
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import asmsources  # noqa: E402
import split  # noqa: E402  (tools/split.py — load_names/sanitize are the name rules)
import srctree  # noqa: E402


def current(symbols):
    """{va: name} from `config/SLUS-20836/symbols.txt`."""
    out = {}
    for ln in open(symbols):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        out[int(p[0], 16)] = p[2]
    return out


def plan(names, cur):
    """-> (renames, errors); renames = [(va, old, new, module)] sorted by va."""
    by_name = {n: v for v, n in cur.items()}
    renaming = {v for v in names if v in cur}
    renames, errors, taken = [], [], {}
    for va in sorted(names):
        nm, mod = names[va]
        if va not in cur:
            errors.append("0x%08x is not in config/SLUS-20836/symbols.txt" % va)
            continue
        new, old = split.sanitize(nm), cur[va]
        if new == old:
            continue
        if new in taken and taken[new] != va:
            errors.append("0x%08x and 0x%08x both want the name %s" % (taken[new], va, new))
            continue
        taken[new] = va
        # A name may be *freed* by another entry in this same batch (a chain of
        # swaps); only a name held by a function staying put is a real collision.
        holder = by_name.get(new)
        if holder is not None and holder != va and holder not in renaming:
            errors.append("0x%08x -> %s collides with 0x%08x" % (va, new, holder))
            continue
        renames.append((va, old, new, mod))
    return renames, errors


# ---------------------------------------------------------------------------------------------
# Reading C: just enough to tell a reference to a function from a word that only looks like one.

_LEX = re.compile(r"""
    (?P<comment>//[^\n]*|/\*.*?(?:\*/|\Z))
  | (?P<include>\#[ \t]*include[ \t]*(?:"[^"\n]*"|<[^>\n]*>))
  | (?P<string>(?:u8|[LuU])?"(?:\\.|[^"\\\n])*"|(?:u8|[LuU])?'(?:\\.|[^'\\\n])*')
  | (?P<number>\.?[0-9](?:[eEpP][+-]|[\w.])*)
  | (?P<ident>[A-Za-z_]\w*)
  | (?P<punct>->|::|==|!=|<=|>=|&&|\|\||<<=?|>>=?|\+\+|--|[-+*/%&|^]=|\S)
""", re.S | re.X)
_WORD = re.compile(r"[A-Za-z_]\w*")
_PLAIN_WORD = re.compile(r"[a-z]+")

# a word before an identifier that makes it an operand, not a declared name
_EXPR_WORDS = frozenset((
    "return", "case", "goto", "sizeof", "else", "do", "throw", "new", "delete", "typeof",
    "__typeof__", "alignof", "__alignof__", "defined", "if", "while", "for", "switch"))
_TAGS = frozenset(("struct", "class", "union", "enum", "typename"))
_PP_NAMED = frozenset(("define", "undef", "ifdef", "ifndef"))
_DECL_QUALS = frozenset(("*", "&", "const", "volatile", "__restrict", "restrict"))
_FIELD_END = frozenset((";", ",", "[", ":", "=", "(", "}"))
_ASM_WORDS = frozenset(("asm", "__asm__", "__asm"))
_NOT_A_FUNCTION = frozenset(("__attribute__", "__declspec")) | _ASM_WORDS
# what an identifier is, when it is not a reference to the function of that name
OTHER_ROLES = ("member", "field", "decl", "local", "object", "label", "tag", "macro", "scope", "ambiguous")
_OBJECT_USE = re.compile(r"\s*(?:->|\.[A-Za-z_])")
CXX_EXTS = (".cpp", ".cc", ".cxx", ".hpp", ".hh")


class Occurrence:
    __slots__ = ("start", "end", "name", "role", "captured")

    def __init__(self, start, end, name, role, captured=False):
        self.start, self.end, self.name, self.role, self.captured = start, end, name, role, captured


class Scan:
    """One file read for the names of a batch."""

    def __init__(self):
        self.occurrences = []          # code identifiers that are batch names
        self.comments = []             # (start, end) of every comment
        self.comment_words = Counter()  # batch names written in comments
        self.string_words = Counter()   # batch names written in string literals
        self.definitions = []          # function names defined at file scope, in text order


class _Block:
    __slots__ = ("kind", "shadow", "parens", "stmt")

    def __init__(self, kind, parens, stmt):
        self.kind, self.shadow, self.parens, self.stmt = kind, set(), parens, stmt


def _logical_line_end(text, start):
    end = text.find("\n", start)
    while end != -1 and text[start:end].rstrip("\r").endswith("\\"):
        start = end + 1
        end = text.find("\n", start)
    return len(text) if end == -1 else end


def _block_kind(toks, stmt, i, stack, parens):
    """What a `{` at toks[i] opens: 'code', 'asm' (an MWCC `asm` function or block), 'agg'
    (struct/class/union/enum body), 'init' or 'ns'."""
    top = stack[-1].kind if stack else "ns"
    if top == "init":
        return "init"
    words = [t for _, t, _, _ in toks[stmt:i]]
    if not _ASM_WORDS.isdisjoint(words):
        return "asm"
    if parens:
        return "init" if words and words[-1] == ")" else "code"
    if not words:
        return "code"
    if words[-1] in (")", "const", "else", "do", "try"):
        return "code"
    if "namespace" in words or (words[0] == "extern" and len(words) > 1 and words[1] == '"'):
        return "ns"
    depth, assigned, aggregate = 0, False, False
    for w in words:
        if w in ("(", "["):
            depth += 1
        elif w in (")", "]"):
            depth -= 1
        elif depth == 0 and w == "=":
            assigned = True
        elif depth == 0 and w in ("struct", "class", "union", "enum"):
            aggregate = True
    if assigned:
        return "init"
    return "agg" if aggregate else "code"


def language(path):
    """'asm' for an assembly source, 'c', 'cxx', or 'either' for a header or fragment."""
    if path.endswith(asmsources.EXT):
        return "asm"
    if path.endswith(".c"):
        return "c"
    return "cxx" if path.endswith(CXX_EXTS) else "either"


def scan(text, interest, sub, lang="c"):
    """Read `text` (in `language`) for the identifiers in `interest`, classifying each occurrence.

    A role of 'ref' is a reference to the global function of that name; every other role
    (OTHER_ROLES) is a different entity spelled the same.  `captured` marks a reference whose
    new name, `sub[name]`, is a local or parameter in scope there."""
    cxx = lang == "cxx"
    s = Scan()
    toks = []
    pp, pp_end = [], -1    # the tokens of the preprocessor line being read, and where it ends
    for m in _LEX.finditer(text):
        kind, t, st, en = m.lastgroup, m.group(), m.start(), m.end()
        if kind == "comment":
            s.comments.append((st, en))
            for w in _WORD.findall(t):
                if w in interest:
                    s.comment_words[w] += 1
            continue
        if kind in ("string", "include"):
            for w in _WORD.findall(t):
                if w in interest:
                    s.string_words[w] += 1
            if kind == "string" and st >= pp_end:
                toks.append(("string", '"', st, en))
            continue
        if st >= pp_end and t == "#" and not text[text.rfind("\n", 0, st) + 1:st].strip():
            pp, pp_end = [], _logical_line_end(text, st)
        if st < pp_end:
            # A preprocessor line is no part of the C around it: a name it defines or tests
            # is a macro, anything else a use.
            if kind == "ident" and t in interest:
                prev = pp[-1] if pp else None
                if (len(pp) == 2 and prev in _PP_NAMED) or prev == "defined" or (
                        prev == "(" and len(pp) > 1 and pp[-2] == "defined"):
                    role = "macro"
                elif prev in (".", "->"):
                    role = "member"
                elif _OBJECT_USE.match(text, en):
                    role = "object"
                else:
                    role = "ref"
                s.occurrences.append(Occurrence(st, en, t, role))
            pp.append(t)
            continue
        toks.append((kind, t, st, en))

    if lang == "asm":
        for i, (kind, t, st, en) in enumerate(toks):
            if kind != "ident" or (st and text[st - 1] == "."):
                continue
            if i + 1 < len(toks) and toks[i + 1][1] == ":":
                s.definitions.append(t)
            if t in interest:
                s.occurrences.append(Occurrence(st, en, t, "ref"))
        return s

    stack, parens, stmt, pending = [], [], 0, {}
    file_shadow, cxx_fields = set(), set()
    def_name = None        # the first `name(` of a file-scope statement; "" when not a plain name
    asm_stmt = -1          # the statement an `asm` keyword was last seen in

    def at_file_scope():
        return all(b.kind == "ns" for b in stack)

    def in_scope(name):
        return name in file_shadow or any(name in b.shadow for b in stack)

    def word(k):
        return toks[k][1] if k < len(toks) else None

    for i, (kind, t, st, en) in enumerate(toks):
        if kind == "punct":
            if t == "(":
                before = toks[i - 1] if i else None
                if (not parens and def_name is None and at_file_scope()
                        and (before is None or before[1] not in _NOT_A_FUNCTION)):
                    plain = before is not None and before[0] == "ident" and (i < 2 or toks[i - 2][1] != "::")
                    def_name = before[1] if plain else ""
                parens.append(i > 0 and toks[i - 1][1] == "for")
            elif t == ")":
                if parens:
                    parens.pop()
            elif t == "{":
                block = _Block(_block_kind(toks, stmt, i, stack, parens), parens, stmt)
                pending_here = pending.pop(len(stack), set())
                if block.kind in ("code", "asm"):
                    block.shadow |= pending_here
                    if not parens and at_file_scope() and def_name:
                        s.definitions.append(def_name)
                stack.append(block)
                parens, stmt, def_name = [], i + 1, None
            elif t == "}":
                if stack:
                    block = stack.pop()
                    parens = block.parens
                    stmt = i + 1 if block.kind in ("code", "asm", "ns") else block.stmt
                else:                                    # a fragment closing its includer's block
                    parens, stmt = [], i + 1
                def_name = None
            elif t == ";" and not parens:
                stmt, def_name = i + 1, None
                pending.pop(len(stack), None)
            continue
        if kind == "string":
            # an inline-asm operand is code, not data: the symbols it names are references
            if asm_stmt == stmt:
                for m in _WORD.finditer(text, st, en):
                    if m.group() in interest and text[m.start() - 1] not in ".%$":
                        s.string_words[m.group()] -= 1
                        s.occurrences.append(Occurrence(m.start(), m.end(), m.group(), "ref"))
            continue
        if kind != "ident":
            continue
        if t in _ASM_WORDS:
            asm_stmt = stmt
        if t not in interest:
            continue

        prev = toks[i - 1][1] if i else None
        prev2 = toks[i - 2] if i > 1 else None
        nxt = toks[i + 1][1] if i + 1 < len(toks) else None
        top = stack[-1].kind if stack else "ns"
        fnptr = False
        if prev in (".", "->"):
            role = "member"
        elif nxt in ("->", "."):
            role = "object"                              # no function has members
        elif top == "asm":
            role = "ref"
        elif prev == "::":
            role = "member" if prev2 and (prev2[0] == "ident" or prev2[1] == ">") else "ref"
        elif nxt == "::":
            role = "scope"
        elif prev in _TAGS:
            role = "tag"
        elif prev == "goto":
            role = "label"
        elif top == "agg" and not parens:
            role = "field" if nxt in _FIELD_END else "ref"
        elif nxt == ":" and not parens and top == "code" and prev in (";", "{", "}", None):
            role = "label"
        else:
            j = i - 1
            while j >= 0 and toks[j][1] in _DECL_QUALS:
                j -= 1
            q = toks[j] if j >= 0 else None
            # after a `*` or `&`, `a * name` is an operand unless `a` starts a declaration
            pointer = any(toks[k][1] in ("*", "&") for k in range(j + 1, i))
            typed = not pointer or j < 1 or toks[j - 1][1] in (";", "{", "}", "(", ",") or (
                toks[j - 1][0] == "ident" and toks[j - 1][1] not in _EXPR_WORDS)
            fnptr = prev == "*" and prev2 and prev2[1] == "(" and nxt == ")"
            if fnptr:
                # `T (*name)(...)`: a function pointer, as a member or a variable
                role = "field" if top == "agg" and len(parens) == 1 else "decl"
            elif typed and q and ((q[0] == "ident" and q[1] not in _EXPR_WORDS)
                                  or (q[1] == ">" and toks[stmt][0] == "ident"
                                      and any(toks[k][1] == "<" for k in range(stmt, j)))):
                if nxt != "(":
                    role = "decl"
                elif (lang != "c" and top == "code" and not parens and not pointer
                      and not (word(i + 2) == ")" or word(i + 2) == "void" and word(i + 3) == ")")
                      and not any(w == "extern" for _, w, _, _ in toks[stmt:i])):
                    role = "decl"                        # C++ `T name(args);` constructs an object
                else:
                    role = "ref"                         # `T name(` declares the function itself
            elif (prev == "," and not parens and stmt + 1 < i and toks[stmt][0] == "ident"
                  and toks[stmt][1] not in _EXPR_WORDS
                  and (toks[stmt + 1][0] == "ident" or toks[stmt + 1][1] in ("*", "&"))):
                role = "ref" if nxt == "(" else "decl"   # `T a, name;`
            else:
                role = "ref"
        if role == "decl":
            if len(parens) > (1 if fnptr else 0):
                if parens[-1] and stack:                 # `for (T name = ...`
                    stack[-1].shadow.add(t)
                else:                                    # a parameter: the next body's
                    pending.setdefault(len(stack), set()).add(t)
            elif at_file_scope():
                if any(w in ("static", "typedef") for _, w, _, _ in toks[stmt:i]):
                    file_shadow.add(t)
                else:
                    role = "ref"                         # a file-scope declaration of the symbol
            else:
                stack[-1].shadow.add(t)
        elif role == "field" and cxx:
            cxx_fields.add(t)
        elif role == "ref" and in_scope(t):
            role = "local"
        captured = role == "ref" and t in sub and in_scope(sub[t])
        s.occurrences.append(Occurrence(st, en, t, role, captured))

    if cxx_fields:
        for o in s.occurrences:
            if o.role == "ref" and o.name in cxx_fields:
                o.role = "ambiguous"                     # may be `this->name`
            elif o.role == "ref" and sub.get(o.name) in cxx_fields:
                o.captured = True
    return s


def _inversions(addrs):
    return sum(1 for i in range(len(addrs)) for j in range(i + 1, len(addrs)) if addrs[i] > addrs[j])


def _line(text, pos):
    return text.count("\n", 0, pos) + 1


def source_paths(src, include):
    """Every source, header and fragment the batch rewrites."""
    return sorted(os.path.join(root, filename)
                  for top in (src, include) if os.path.isdir(top)
                  for root, _, files in os.walk(top)
                  for filename in files
                  if filename.endswith(srctree.EXTS + (asmsources.EXT, ".h", ".inc"))
                  and not filename.startswith("dw4u_"))


def rewrite_sources(paths, sub, cur_by_name, final_by_name, generic_ok=(), assume_old=(), assume_new=(),
                    rel=os.path.relpath):
    """-> (new_texts {path: text}, states {path: 'old'|'new'}, errors, notes).

    `sub` maps every old name to its new one; `cur_by_name`/`final_by_name` give each name's
    address before and after the batch (for the definition-order evidence)."""
    olds, news = set(sub), set(sub.values())
    chain = olds & news
    old_only, new_only = olds - news, news - olds
    interest = olds | news
    assume_old = {os.path.abspath(p) for p in assume_old}
    assume_new = {os.path.abspath(p) for p in assume_new}

    scans = {}
    for path in paths:
        text = open(path, errors="surrogateescape").read()
        if interest.isdisjoint(_WORD.findall(text)):
            continue
        scans[path] = (text, scan(text, interest, sub, language(path)))

    errors, notes = [], []

    # 1. an old name that is also an ordinary identifier somewhere is not rewritten blindly
    other_uses = {}
    for path, (text, s) in scans.items():
        for o in s.occurrences:
            if o.name in olds and o.role in OTHER_ROLES:
                other_uses.setdefault(o.name, set()).add(path)
    generic = set(other_uses)
    for name in sorted(generic - set(generic_ok)):
        lines = []
        for path, (text, s) in sorted(scans.items()):
            roles = Counter(o.role for o in s.occurrences if o.name == name)
            if s.string_words[name]:
                roles["in a string"] = s.string_words[name]
            if s.comment_words[name]:
                roles["in a comment"] = s.comment_words[name]
            if roles:
                lines.append("    %s: %s" % (rel(path), ", ".join(
                    "%d %s" % (n, r) for r, n in sorted(roles.items()))))
        errors.append("`%s` (-> %s) is also an ordinary identifier, so its occurrences are not all the "
                      "function (`ref` is a reference to it; %s are other things of the same name):\n%s\n"
                      "  rename those uses first, or pass `--generic %s` to rewrite only the references "
                      "(never strings, comments, members, or locals and their uses)"
                      % (name, sub[name], "/".join(OTHER_ROLES), "\n".join(lines), name))
    commentable = {n for n in olds if n not in generic and not _PLAIN_WORD.fullmatch(n)}

    # 2. per file: which names its text uses, when the batch reuses a name
    states = {}
    for path, (text, s) in scans.items():
        refs = {o.name for o in s.occurrences if o.role == "ref"}
        if not chain or refs.isdisjoint(chain):
            continue
        votes, why = set(), []
        if os.path.abspath(path) in assume_old:
            votes, why = {"old"}, ["--assume-old"]
        elif os.path.abspath(path) in assume_new:
            votes, why = {"new"}, ["--assume-new"]
        else:
            stale, fresh = sorted(refs & old_only), sorted(refs & new_only)
            if stale:
                votes.add("old")
                why.append("old names " + ", ".join(stale[:4]) + (" ..." if len(stale) > 4 else ""))
            if fresh:
                votes.add("new")
                why.append("new names " + ", ".join(fresh[:4]) + (" ..." if len(fresh) > 4 else ""))
            if not set(s.definitions).isdisjoint(chain):
                before = _inversions([cur_by_name[n] for n in s.definitions if n in cur_by_name])
                after = _inversions([final_by_name[n] for n in s.definitions if n in final_by_name])
                if before != after:
                    votes.add("old" if before < after else "new")
                    why.append("its definitions are in address order under the %s names"
                               % ("old" if before < after else "new"))
        reused = ", ".join(sorted(refs & chain))
        if len(votes) == 1:
            states[path] = votes.pop()
            if states[path] == "new":
                notes.append("%s already uses the new names (%s): left as is" % (rel(path), "; ".join(why)))
        elif votes:
            errors.append("%s mixes the batch's old and new names (%s), and also uses %s, whose meaning "
                          "the batch changes: finish its renames by hand, or pass --assume-old/--assume-new"
                          % (rel(path), "; ".join(why), reused))
        else:
            errors.append("%s uses only names this batch reuses (%s), so it cannot tell whether the file "
                          "already has the new names: pass --assume-old %s (it has the names in "
                          "symbols.txt) or --assume-new %s" % (rel(path), reused, rel(path), rel(path)))

    # 3. the rewrite itself, one pass per file
    new_texts, string_kept = {}, Counter()
    for path, (text, s) in scans.items():
        state = states.get(path)
        if state == "new":
            code_map = {}
            comment_map = {n: sub[n] for n in commentable & old_only}
        else:
            code_map = sub
            comment_map = {n: sub[n] for n in commentable if state == "old" or n not in chain}
        for n, c in s.string_words.items():
            if n in olds:
                string_kept[n] += c
        edits = []
        for o in s.occurrences:
            if o.name not in code_map or (o.name in generic and o.name not in generic_ok):
                continue
            if o.role == "ambiguous":
                errors.append("%s:%d: `%s` is also a member of a class this C++ file defines, so this "
                              "use may be `this->%s`: qualify it or rename it by hand"
                              % (rel(path), _line(text, o.start), o.name, o.name))
            elif o.role == "ref":
                if o.captured:
                    errors.append("%s:%d: renaming `%s` to `%s` here would name the local or member `%s`"
                                  % (rel(path), _line(text, o.start), o.name, code_map[o.name],
                                     code_map[o.name]))
                edits.append((o.start, o.end, code_map[o.name]))
        if comment_map:
            for start, end in s.comments:
                for m in _WORD.finditer(text, start, end):
                    if m.group() in comment_map:
                        edits.append((m.start(), m.end(), comment_map[m.group()]))
        if edits:
            edits.sort()
            out, pos = [], 0
            for start, end, repl in edits:
                out.append(text[pos:start])
                out.append(repl)
                pos = end
            out.append(text[pos:])
            new_texts[path] = "".join(out)
    if string_kept:
        notes.append("left %d mentions inside string literals as they are (%s)" % (
            sum(string_kept.values()),
            ", ".join("%s x%d" % kv for kv in sorted(string_kept.items())[:8])
            + (" ..." if len(string_kept) > 8 else "")))
    return new_texts, states, errors, notes


def rename_unit_objects(data, renamed):
    """Rename `unit-objects.json` keys in place by address -> (count, errors).

    `renamed` is {va: (old, new)}.  An `emitted`/`duplicates`/`externals` key is renamed only
    when the address it holds is a renamed function's and the key is that function's old name;
    a row's `symbol` likewise against the row's own address."""
    count, errors = 0, []
    for unit, row in data.items():
        for field in ("emitted", "duplicates", "externals"):
            entries = row.get(field)
            if not isinstance(entries, dict):
                continue
            out, changed = {}, False
            for name, addr in entries.items():
                hit = renamed.get(int(addr, 16))
                if hit and hit[0] == name:
                    name, changed = hit[1], True
                    count += 1
                if name in out:
                    errors.append("unit-objects.json %s %s: two entries would be named %s"
                                  % (unit, field, name))
                out[name] = addr
            if changed:
                row[field] = out
        hit = renamed.get(int(unit, 16))
        if hit and row.get("symbol") == hit[0]:
            row["symbol"] = hit[1]
            count += 1
    return count, errors


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--names", default="config/SLUS-20836/names")
    ap.add_argument("--symbols", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--unit-objects",
                    help="default: unit-objects.json beside --symbols")
    ap.add_argument("--src", default="src")
    ap.add_argument("--asm", default="asm")
    ap.add_argument("--apply", action="store_true", help="commit (default: dry run)")
    ap.add_argument("--no-regen", action="store_true",
                    help="do not re-run tools/split.py after the move")
    ap.add_argument("--check", action="store_true",
                    help="after applying, run `make check` and `make link`")
    ap.add_argument("--generic", action="append", default=[], metavar="NAME",
                    help="rewrite the references to old name NAME although it is also an ordinary "
                         "identifier (repeatable)")
    ap.add_argument("--assume-old", action="append", default=[], metavar="PATH",
                    help="PATH still uses the names in symbols.txt (repeatable)")
    ap.add_argument("--assume-new", action="append", default=[], metavar="PATH",
                    help="PATH already uses the batch's new names (repeatable)")
    a = ap.parse_args(argv)

    names = split.load_names(a.names)
    if not names:
        print("apply_names: %s has no entries (nothing to do)" % a.names)
        return 0
    cur = current(a.symbols)
    renames, errors = plan(names, cur)
    for e in errors:
        print("error: " + e, file=sys.stderr)
    if errors:
        return 2
    if not renames:
        print("apply_names: %d overlay entries, all already applied" % len(names))
        return 0

    # `thunk_<target>` is named after its target, so renaming the target renames the thunk
    # (`split.py` emits `thunk_<new>`); an explicit alias overlay takes precedence.
    sub = {old: new for _, old, new, _ in renames}
    for _, old, new, _ in renames:
        sub.setdefault("thunk_" + old, "thunk_" + new)
    cur_by_name = {n: v for v, n in cur.items()}
    final = dict(cur)
    final.update((va, new) for va, _, new, _ in renames)
    final_by_name = {n: v for v, n in final.items()}
    # Every source in src/ (a same-basename .c/.cpp pair included), and the headers and `.inc`
    # fragments in src/ and the shared include/ tree, which declare and call functions too.
    tree = os.path.dirname(os.path.abspath(a.src))
    paths = source_paths(a.src, os.path.join(tree, "include"))
    new_texts, states, errs, notes = rewrite_sources(
        paths, sub, cur_by_name, final_by_name, a.generic, a.assume_old, a.assume_new,
        rel=lambda p: os.path.relpath(p, tree))
    errors += errs

    # one-function units move to their module folder under the new name; a file that
    # already carries its new name (a swap applied by hand) only changes folder
    idx = srctree.index(a.src)
    moves = []
    for va, old, new, mod in renames:
        path = idx.get(old)
        if path is None or states.get(path) == "new":
            path = idx.get(new) if states.get(idx.get(new)) == "new" else None
        if path is None:
            continue
        dest = os.path.join(a.src, mod, new + path[path.rfind("."):])
        if os.path.abspath(dest) != os.path.abspath(path):
            moves.append((path, dest))
    leaving = {os.path.abspath(p) for p, _ in moves}
    seen = set()
    for path, dest in moves:
        d = os.path.abspath(dest)
        if d in seen or (os.path.exists(dest) and d not in leaving):
            errors.append("%s already exists" % dest)
        seen.add(d)

    renamed = {va: (old, new) for va, old, new, _ in renames}
    unit_objects = a.unit_objects or os.path.join(os.path.dirname(os.path.abspath(a.symbols)),
                                                  "unit-objects.json")
    uo_data, uo_count = None, 0
    if os.path.exists(unit_objects):
        uo_data = json.load(open(unit_objects))
        uo_count, errs = rename_unit_objects(uo_data, renamed)
        errors += errs

    print("apply_names: %d/%d entries rename something (%d units to move, %d new asm labels)"
          % (len(renames), len(names), len(moves), len(renames)))
    moving = {os.path.splitext(os.path.basename(dest))[0] for _, dest in moves}
    for va, old, new, mod in renames[:40]:
        where = ("-> %s/%s" % (mod, new)) if new in moving else "(no unit yet)"
        print("  0x%08x  %-28s -> %-32s %s" % (va, old, new, where))
    if len(renames) > 40:
        print("  ... and %d more" % (len(renames) - 40))
    print("%d source files to rewrite, %d unit-objects.json keys to rename"
          % (len(new_texts), uo_count))
    for path in sorted(new_texts)[:40]:
        print("  " + os.path.relpath(path, tree))
    if len(new_texts) > 40:
        print("  ... and %d more" % (len(new_texts) - 40))
    for n in notes:
        print("note: " + n)
    for e in errors:
        print("error: " + e, file=sys.stderr)
    if errors:
        print("apply_names: refused (%d errors); nothing was written" % len(errors), file=sys.stderr)
        return 2
    if not a.apply:
        print("\n(dry run — re-run with --apply)")
        return 0

    # 1. rewrite src/ references, the approval tables and unit-objects.json
    for path, text in new_texts.items():
        open(path, "w", errors="surrogateescape").write(text)
    # the owner's source approvals name their functions by symbol in the second column
    approvals = os.path.join(tree, "config", "source-approvals.tsv")
    if os.path.exists(approvals):
        text = open(approvals).read()
        lines = []
        for line in text.splitlines(True):
            cols = line.split("\t")
            if not line.startswith("#") and len(cols) > 2 and cols[1] in sub:
                cols[1] = sub[cols[1]]
            lines.append("\t".join(cols))
        if "".join(lines) != text:
            open(approvals, "w").write("".join(lines))
    # the assembly approval table names its functions by symbol in the first column
    asm_table = os.path.join(tree, "config", os.path.basename(asmsources.TABLE))
    if os.path.exists(asm_table):
        text = open(asm_table).read()
        lines = []
        for line in text.splitlines(True):
            head, sep, rest = line.partition("\t")
            lines.append(line if line.startswith("#") or not sep else sub.get(head, head) + sep + rest)
        if "".join(lines) != text:
            open(asm_table, "w").write("".join(lines))
    if uo_count:
        with open(unit_objects, "w") as fh:
            fh.write(json.dumps(uo_data, indent=2) + "\n")

    # 2. move each one-function unit to its module folder (through temporary names, so a
    #    swap of two units never finds its destination taken)
    staged = []
    for n, (path, dest) in enumerate(moves):
        tmp = "%s.apply_names-%d" % (path, n)
        shutil.move(path, tmp)
        staged.append((tmp, dest))
    for tmp, dest in staged:
        os.makedirs(os.path.dirname(dest), exist_ok=True)
        shutil.move(tmp, dest)

    # 3. drop the stale asm units so the regenerated tree has no duplicate label.
    removed = 0
    for va, old, new, mod in renames:
        stale = os.path.join(a.asm, old + ".s")
        if os.path.exists(stale):
            os.remove(stale)
            removed += 1

    print("rewrote %d files, moved %d, renamed %d unit-objects.json keys, removed %d stale asm units"
          % (len(new_texts), len(moves), uo_count, removed))

    # 4. regenerate the layout + asm from the overlay.
    if not a.no_regen:
        cmd = [sys.executable, os.path.join(ROOT, "tools", "split.py"),
               "--symbols", "--names", a.names]
        r = subprocess.run(cmd, cwd=ROOT)
        if r.returncode:
            return r.returncode
        # `split.py` writes the units it knows and never deletes, so a name it no
        # longer uses — an overlay entry removed, or a function whose symbol moved —
        # would leave an orphan asm unit behind.  asm/ is generated from the symbol
        # list, so anything not in it is stale by definition.
        names = {ln.split()[2] for ln in open(a.symbols)
                 if ln.strip() and not ln.startswith("#")}
        pruned = 0
        for f in os.listdir(a.asm):
            if f.endswith(".s") and f[:-2] not in names:
                os.remove(os.path.join(a.asm, f))
                pruned += 1
        if pruned:
            print("pruned %d stale asm units" % pruned)

    if a.check:
        for tgt in (["make", "check"], ["make", "link"]):
            r = subprocess.run(tgt, cwd=ROOT)
            if r.returncode:
                print("apply_names: `%s` failed" % " ".join(tgt), file=sys.stderr)
                return r.returncode
    else:
        print("\nnext: `make check` (must be green) and `make link` (must be byte-identical)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
