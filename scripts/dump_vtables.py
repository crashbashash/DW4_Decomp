# dump_vtables.py — recover Metrowerks CodeWarrior RTTI records and C++
# vtables from the current Ghidra program.
#
# Digimon World 4 was built with MWCCPS2, whose RTTI emits two adjacent
# structures in rodata:
#
#   __RTTI__ClassName:            # 16 bytes
#       .4byte <ptr to class-name string>
#       .4byte <base ref>         # 0 for a root class, else a pointer to a
#                                 # slot that itself holds the base __RTTI__
#       .4byte 0
#       .4byte 0
#
#   __vt__ClassName:
#       .4byte <ptr to __RTTI__ClassName>
#       .4byte 0
#       .4byte <vfunc 0>
#       .4byte <vfunc 1>
#       ...
#
# until the next __vt__ header. The class-name string is what carries the
# `Gap::Bec::beModelCtrl`-style identifier, so this is the only route from a
# stripped binary to class/method names.
#
# Output JSON is consumed by apply_vtable_names.py.
#
#   pyghidra-run <binary> --project-path ghidra-projects/dw4 \
#       --project-name dw4 -postScript dump_vtables.py \
#       --out ghidra-projects/dw4/vtables.json
#
# Args:
#   --out PATH        default stdout
#   --codemax 0xADDR  override the code/rodata boundary (default: auto-detect)
#   --min-vfuncs N    drop tables with fewer than N entries (default 2)
#
# @category PS2
# @runtime PyGhidra

import json
import re
import struct
import typing

if typing.TYPE_CHECKING:
    from typing import Any

    currentProgram: Any = None
    getScriptArgs: Any = None

# A class identifier string: namespaced (`Gap::Bec::beModelCtrl`), a template
# instantiation (`Gap::Core::igTObjectList<...>`), or a bare engine/game type
# (`igObject`, `beBaseInfo`). Kept deliberately broad; the RTTI base-chain and
# vtable validation below are what reject noise.
_CLASS_RE = re.compile(r"^(?:Gap|ig|be)[A-Za-z0-9_:<>,\* ]{2,120}$")

# Auto-detect the code/rodata boundary: the first run of printable text of at
# least this length in the image is the start of `.rodata`.
_TEXT_RUN = 24


# Ghidra symbol names may not contain whitespace. Namespaced C++ identifiers
# (`Gap::Bec::beModelCtrl`, `igTObjectList<Gap::Attrs::igX>`) are otherwise
# legal and match the demangled convention.
_NAME_WS = re.compile(r"\s+")


def _sanitize(name):
    return _NAME_WS.sub("_", name).strip("_")


def _args(argv):
    out_path = None
    codemax = None
    min_vfuncs = 2
    i = 0
    while i < len(argv):
        a = argv[i]
        if a in ("--out", "-o") and i + 1 < len(argv):
            out_path = argv[i + 1]
            i += 2
        elif a == "--codemax" and i + 1 < len(argv):
            codemax = int(argv[i + 1], 0)
            i += 2
        elif a == "--min-vfuncs" and i + 1 < len(argv):
            min_vfuncs = int(argv[i + 1], 0)
            i += 2
        else:
            i += 1
    return out_path, codemax, min_vfuncs


def _read_image():
    """Bulk-read the program's own initialized memory into one buffer.

    Only blocks in the default address space count: the ELF loader also
    creates non-addressable overlay blocks for `.comment`, `.reginfo`,
    `.shstrtab`, `_elfHeader`, ... whose offsets are 0-based and would
    otherwise corrupt the image bounds.

    The byte array must be a JPype `JArray(JByte)`: PyGhidra does not
    marshal writes back into a plain Python `bytearray`, so
    `getBytes(addr, bytearray(n))` silently returns a buffer of zeros.

    Returns (lo, buf, hi) with byte offset = va - lo.
    """
    from jpype import JArray, JByte

    memory = currentProgram.getMemory()
    default_space = currentProgram.getAddressFactory().getDefaultAddressSpace()
    raw_blocks = memory.getBlocks()
    all_blocks = [raw_blocks[i] for i in range(len(raw_blocks))]
    blocks = [
        b
        for b in all_blocks
        if b.isInitialized() and b.getStart().getAddressSpace() == default_space
    ]
    if not blocks:
        raise SystemExit("dump_vtables: no initialized addressable memory blocks")
    lo = min(b.getStart().getOffset() for b in blocks)
    hi = max(b.getEnd().getOffset() + 1 for b in blocks)
    buf = bytearray(hi - lo)
    for b in blocks:
        start = b.getStart().getOffset()
        size = b.getEnd().getOffset() + 1 - start
        jbuf = JArray(JByte)(size)
        got = memory.getBytes(b.getStart(), jbuf)
        if got != size:
            raise SystemExit(
                f"dump_vtables: short read at {hex(start)} ({got} of {size} bytes)"
            )
        buf[start - lo:start - lo + size] = bytearray((int(x) & 0xFF) for x in jbuf)
    return lo, buf, hi


def _detect_codemax(lo, buf, hi):
    """Find the code/rodata boundary.

    MWCCPS2 emits the ELF as one merged `.text`+`.rodata` section, so there is
    no section to consult. The first 512-byte window that is >=95 % printable
    ASCII or NUL is the start of the string data; the last `jr ra` in the
    image sits just below it (measured: last `jr ra` 0x00482958, first text
    0x00483540 in Digimon World 4). A conservative bound is fine here: every
    vfunc in the binary is far below it, and the run scan stops at the next
    vtable header anyway.
    """
    win, frac = 512, 0.95
    for va in range(lo, hi - win, 4):
        off = va - lo
        sample = buf[off:off + win]
        good = sum(1 for c in sample if c == 0 or 32 <= c < 127)
        if good / win >= frac:
            return va
    return hi


def _cstr(buf, lo, va, limit=160):
    off = va - lo
    if off < 0 or off >= len(buf):
        return ""
    end = buf.find(b"\0", off, min(off + limit, len(buf)))
    if end < 0:
        return ""
    raw = bytes(buf[off:end])
    try:
        return raw.decode("ascii")
    except UnicodeDecodeError:
        return ""


def _main():
    out_path, codemax_arg, min_vfuncs = _args(list(getScriptArgs()))
    lo, buf, hi = _read_image()
    codemax = codemax_arg if codemax_arg is not None else _detect_codemax(lo, buf, hi)

    def u32(va):
        off = va - lo
        if off < 0 or off > len(buf) - 4:
            return None
        return struct.unpack_from("<I", buf, off)[0]

    def is_img(va):
        return lo <= va < hi

    def in_code(va):
        return lo <= va < codemax

    # --- 1. RTTI records: word0 -> a class-name string -------------------
    rtti = {}
    for va in range(lo, hi - 15, 4):
        if va < codemax:
            continue  # RTTI lives in rodata, never in the text range
        w = u32(va)
        if w is None or not is_img(w):
            continue
        s = _cstr(buf, lo, w, 120)
        if not s or not (2 <= len(s) <= 120) or not _CLASS_RE.match(s):
            continue
        rtti[va] = s

    # Validate the base reference: either 0 (root class) or a pointer to a
    # slot that itself holds another RTTI record's address.
    def base_ok(va):
        b = u32(va + 4)
        if b == 0:
            return True
        return is_img(b) and u32(b) in rtti

    rtti = {k: v for k, v in rtti.items() if base_ok(k)}

    # --- 2. vtable headers: {rtti_ptr, 0, vfuncs...} ---------------------
    def is_header(va):
        w = u32(va)
        if w is None or w not in rtti:
            return False
        return u32(va + 4) == 0

    headers = set()
    for va in range(codemax, hi - 8, 4):
        if is_header(va):
            # require at least min_vfuncs of the following 8 slots to be code
            nxt = [u32(va + 8 + 4 * i) for i in range(8)]
            if sum(1 for w in nxt if w is not None and in_code(w)) >= min_vfuncs:
                headers.add(va)

    vtables = {}
    for va in sorted(headers):
        vfuncs = []
        a = va + 8
        while a < hi - 3 and len(vfuncs) < 512:
            w = u32(a)
            if w is None or not in_code(w):
                break
            if is_header(a):
                break
            vfuncs.append(w)
            a += 4
        if len(vfuncs) >= min_vfuncs:
            vtables[va] = vfuncs

    # --- 3. base chain from each RTTI record ----------------------------
    def base_rec(rec):
        b = u32(rec + 4)
        if b == 0:
            return None
        w = u32(b)
        return w if (w in rtti) else None

    def base_name(cls):
        """Name of a class's base class, or None."""
        for rec, name in rtti.items():
            if name == cls:
                br = base_rec(rec)
                return rtti[br] if br is not None else None
        return None

    _anc_cache = {}

    def ancestors(cls):
        if cls in _anc_cache:
            return _anc_cache[cls]
        out = set()
        seen = {cls}
        cur = base_name(cls)
        while cur and cur not in seen:
            seen.add(cur)
            out.add(cur)
            cur = base_name(cur)
        _anc_cache[cls] = out
        return out

    # --- 4. name resolution ---------------------------------------------
    # A vfunc address is reachable from many vtables because MWCC emits one
    # shared default stub per slot and points every non-overriding class at
    # it. The declaring class is therefore the most-derived common ancestor
    # of every referencing class.
    refs = {}
    for vt, vfuncs in sorted(vtables.items()):
        cls = rtti[u32(vt)]
        for slot, w in enumerate(vfuncs):
            refs.setdefault(w, []).append((cls, slot, vt))

    names = {}
    skipped = []
    for func, uses in sorted(refs.items()):
        classes = [c for c, _, _ in uses]
        slots = {s for _, s, _ in uses}
        if len(set(classes)) == 1:
            owner, kind = classes[0], "override"
        else:
            # A shared body. Its owner is an ancestor of every referencing class.
            # The RTTI base field is NOT useful here: 578 of 579 records point
            # straight at Gap::Core::igObject, so it carries no immediate-base
            # information, and the intermediate bases (igObjectList,
            # igTObjectList<...>) have RTTI but no emitted vtable. The inference
            # below therefore only ever reaches igObject, which is enough to
            # name the global defaults but collides for group-specific ones.
            cands = set()
            for c in classes:
                cands.add(c)
                cands |= ancestors(c)
            common = {c for c in cands if all(c == o or c in ancestors(o) for o in classes)}
            if not common or len(slots) != 1:
                skipped.append((hex(func), sorted(set(classes)), sorted(slots)))
                continue
            owner, kind = max(common, key=lambda c: len(ancestors(c))), "inherited"
        slot = sorted(slots)[0]
        names[hex(func)] = {
            "name": f"{_sanitize(owner)}::vfunc_{slot:02d}",
            "owner": owner,
            "slot": slot,
            "kind": kind,
            "refs": [[c, s] for c, s, _ in uses],
        }

    # Several distinct bodies can resolve to the same owner+slot when the real
    # owner is an unnamed intermediate base. Keep the name for the widest group
    # (the global default) and demote the rest: two functions sharing one name is
    # worse than an honest blank.
    by_name = {}
    for func, info in sorted(names.items(), key=lambda kv: -len(kv[1]["refs"])):
        by_name.setdefault(info["name"], []).append(func)
    ambiguous = []
    for name, funcs in sorted(by_name.items()):
        if len(funcs) == 1:
            continue
        keep = funcs[0]
        for func in funcs[1:]:
            info = names.pop(func)
            ambiguous.append(
                {
                    "addr": func,
                    "slot": info["slot"],
                    "resolved_owner": info["owner"],
                    "refs": info["refs"],
                    "reason": "owner is an intermediate base with no emitted vtable",
                }
            )
        del name

    out = {
        "program": currentProgram.getName(),
        "language": str(currentProgram.getLanguageID()),
        "image_lo": hex(lo),
        "image_hi": hex(hi),
        "codemax": hex(codemax),
        "rtti": {
            hex(rec): {
                "name": name,
                "base_rtti": (hex(base_rec(rec)) if base_rec(rec) else None),
                "base_name": (rtti[base_rec(rec)] if base_rec(rec) else None),
            }
            for rec, name in sorted(rtti.items())
        },
        "vtables": {
            hex(vt): {
                "rtti": hex(u32(vt)),
                "class": rtti[u32(vt)],
                "vfuncs": [hex(w) for w in vfuncs],
            }
            for vt, vfuncs in sorted(vtables.items())
        },
        "names": names,
        "ambiguous": ambiguous,
        "skipped": skipped,
    }
    text = json.dumps(out, indent=1)
    if out_path:
        with open(out_path, "w", encoding="utf-8") as fh:
            fh.write(text)
        classes = {v["class"] for v in out["vtables"].values()}
        slots = sum(len(v["vfuncs"]) for v in out["vtables"].values())
        overrides = sum(1 for v in names.values() if v["kind"] == "override")
        print(
            f"dump_vtables: {len(out['rtti'])} RTTI records, "
            f"{len(out['vtables'])} vtables, {len(classes)} classes, "
            f"{slots} vfunc slots -> {len(names)} uniquely named functions "
            f"({overrides} override, {len(names) - overrides} inherited), "
            f"{len(ambiguous)} ambiguous (left unnamed), "
            f"{len(skipped)} unnamed, codemax={hex(codemax)} -> {out_path}"
        )
    else:
        print(text)


def main():
    # PyGhidra swallows an escaping exception without printing a traceback, so
    # a failing script looks like a script that produced no output. Surface it.
    import traceback

    try:
        _main()
    except BaseException:
        traceback.print_exc()
        raise


main()
