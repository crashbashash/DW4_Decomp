#!/usr/bin/env python3
"""seed_data_names.py — name the `DAT_<addr>` data symbols the matched C refers to.

The matched sources came from a decompiler that labels every address it cannot
name `DAT_<addr>`.  Most of those are not mysterious: the address is a function
that is passed as a callback, the class-name string or the class-handle slot a
`<Class>_Register` function stores through, a reflection field/constructor table,
or a plain string literal.  Each of those has hard evidence in the image, so each
gets a name that says what it is.  The build resolves a recovered name through this
table (`tools/verify.py:data_symbols`), so the name carries no address; a function
reference takes the function's own symbol.

  python3 scripts/seed_data_names.py > config/SLUS-20836/data-names.tsv.new && mv config/SLUS-20836/data-names.tsv.new config/SLUS-20836/data-names.tsv

Rules (third column of the overlay):

  function-symbol  the address is the entry of a function in config/SLUS-20836/symbols.txt;
                   the data symbol IS that function (a callback argument)
  class-handle     `handle` of a class in data/reflection.json: the slot that
                   holds the class's igMetaObject pointer
  class-name       `name_ptr` of a reflected class: its class-name string
  field-table      `field_table` of a reflected class (its igMetaField list)
  ctor-table       `ctor_table` of a reflected class
  published-accessor  a 12-byte leaf `lui at; jr ra; lw v0,lo(at)` that returns a
                   class-handle slot: the `<Class>_GetPublishedMetaObject` accessor
                   a derived class's registrar is given, as the three already named
                   in config/SLUS-20836/symbols.txt are
  string-literal   NUL-terminated printable text in the image, named after it

The overlay accumulates: once a row is applied its `DAT_` is gone from the sources,
so the generator keeps every row already in config/SLUS-20836/data-names.tsv and adds the
rows for placeholders that are still there.  Applied by tools/apply_data_names.py.
"""
import json
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF = os.path.join(ROOT, "orig/SLUS-20836/SLUS_208.36")
SCOPE = ("engine", "game", "lua", "audio", "menu", "movie")
DAT = re.compile(r"\bDAT_([0-9a-f]{8})\b")
MIN_SLUG = 3     # alphanumerics a string needs before its text is a useful name
MAX_SLUG = 32


def symbols():
    out = {}
    for ln in open(os.path.join(ROOT, "config/SLUS-20836/symbols.txt")):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        out[int(p[0], 16)] = p[2]
    return out


def segments():
    data = open(ELF, "rb").read()
    phoff, = struct.unpack_from("<I", data, 0x1c)
    phentsize, phnum = struct.unpack_from("<HH", data, 0x2a)
    segs = []
    for i in range(phnum):
        t, off, va, _pa, filesz, _memsz, _fl, _al = struct.unpack_from("<8I", data, phoff + i * phentsize)
        if t == 1:
            segs.append((va, off, filesz))
    return data, segs


def c_string(image, addr):
    data, segs = image
    for va, off, filesz in segs:
        if va <= addr < va + filesz:
            raw = data[off + addr - va: off + min(filesz, addr - va + 96)]
            end = raw.find(b"\0")
            if end < MIN_SLUG:
                return None
            text = raw[:end]
            return text.decode() if all(32 <= c < 127 for c in text) else None
    return None


LUI_AT, JR_RA, LW_V0_AT = 0x3c010000, 0x03e00008, 0x8c220000


def returned_slot(image, addr):
    """The address a `lui at; jr ra; lw v0,lo(at)` leaf loads from, or None."""
    data, segs = image
    for va, off, filesz in segs:
        if va <= addr < va + filesz - 12:
            w = struct.unpack_from("<3I", data, off + addr - va)
            if w[0] & 0xffff0000 == LUI_AT and w[1] == JR_RA and w[2] & 0xffff0000 == LW_V0_AT:
                lo = w[2] & 0xffff
                return (w[0] & 0xffff) << 16 | 0, (lo - 0x10000 if lo >= 0x8000 else lo)
    return None


def slug(text):
    words = re.sub(r"[^A-Za-z0-9]+", "_", text).strip("_")
    if sum(c.isalnum() for c in words) < MIN_SLUG or len(words) < len(text) / 2:
        return None
    return words[:MAX_SLUG].rstrip("_")


def ident(cls):
    return re.sub(r"\W", "_", cls)


def string_name(text, syms):
    """A string's name is its text, unless that cannot name it: a leading digit, or a function's name."""
    return "text_" + text if text[0].isdigit() or text in syms.values() else text


def unique(name, va, rows, copies=False):
    """`name`, or a spelling no other row holds. Copies of one string take an ordinal; two different
    data under one name keep the address, which marks them as still needing a recovered name."""
    used = {row[0] for other, row in rows.items() if other != va}
    if name not in used:
        return name
    if not copies:
        return "%s_%08x" % (name, va)
    number = 2
    while "%s_%d" % (name, number) in used:
        number += 1
    return "%s_%d" % (name, number)


def referenced():
    found = set()
    for mod in SCOPE:
        d = os.path.join(ROOT, "src", mod)
        for f in sorted(os.listdir(d)):
            for m in DAT.finditer(open(os.path.join(d, f), errors="replace").read()):
                found.add(int(m.group(1), 16))
    return sorted(found)


def main():
    syms = symbols()
    classes = json.load(open(os.path.join(ROOT, "data/reflection.json")))["classes"].values()
    handle, name_str, field_tab, ctor_tab = {}, {}, {}, {}
    for c in classes:
        for key, table in (("handle", handle), ("name_ptr", name_str),
                           ("field_table", field_tab), ("ctor_table", ctor_tab)):
            if c.get(key):
                table.setdefault(int(c[key], 16) if isinstance(c[key], str) else c[key], c["class"])
    image = segments()
    rows = {}
    table = os.path.join(ROOT, "config/SLUS-20836/data-names.tsv")
    if os.path.exists(table):
        for ln in open(table):
            if not ln.startswith("#") and ln.strip():
                va, name, rule = ln.rstrip("\n").split("\t")
                rows[int(va, 16)] = (name, rule)
    print("# GENERATED by scripts/seed_data_names.py; do not edit.")
    print("# Data symbols named from the image: function entries, reflection slots/strings/tables, string text.")
    print("# <va>\t<name>\t<rule>")
    for va, cls in sorted(handle.items()):      # also read by absolute address: `*(int *)0x58a0e0`
        rows.setdefault(va, (unique("g_%s_metaObject" % ident(cls), va, rows), "class-handle"))
    for va in referenced():
        sym = syms.get(va)
        if sym:
            name, rule = sym, "function-symbol"
        elif va in handle:
            name, rule = unique("g_%s_metaObject" % ident(handle[va]), va, rows), "class-handle"
        elif va in name_str:
            name, rule = unique("%s_className" % ident(name_str[va]), va, rows, copies=True), "class-name"
        elif va in field_tab:
            name, rule = unique("g_%s_fieldTable" % ident(field_tab[va]), va, rows), "field-table"
        elif va in ctor_tab:
            name, rule = unique("g_%s_ctorTable" % ident(ctor_tab[va]), va, rows), "ctor-table"
        elif (slot := returned_slot(image, va)) and slot[0] + slot[1] in handle:
            name, rule = unique("%s_GetPublishedMetaObject" % ident(handle[slot[0] + slot[1]]), va, rows), "published-accessor"
        else:
            text = c_string(image, va)
            s = slug(text) if text else None
            if not s:
                continue
            name, rule = unique(string_name(s, syms), va, rows, copies=True), "string-literal"
        rows[va] = (name, rule)
    for va in sorted(rows):
        print("0x%08x\t%s\t%s" % (va, rows[va][0], rows[va][1]))


if __name__ == "__main__":
    sys.exit(main())
