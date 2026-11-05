# dump_reflection.py — recover the engine's per-class reflection records
# (MetaObject field tables) from the current Ghidra program.
#
# Digimon World 4 is built on the Alchemy/Gamebryo-derived `ig` framework.
# Every class registers a `MetaObject` at static-init time through
# `FUN_002fe9c0(base_idx, &handle, alloc, copy, ?, class_name, ?, init, ?, ?,
#               method_table)`, and the matching post-create init fills the
# class's field list from four parallel rodata arrays:
#
#   [field-ctor fn ptrs][0]   one per field; the fn allocates that field's value
#   [field name ptrs   ][0]   "_" prefixed strings
#   [field desc ptrs   ][0]   BSS MetaField* slots
#   [field offsets     ][0]   byte offset inside the object
#
# all four 0-terminated and 8-byte aligned, with equal counts. The same
# static-init code calls:
#
#   FUN_002fdf40(metaobj, ctor_table, count)          -- create the fields
#   FUN_002fe000(metaobj, names, descs, offsets, start) -- name/offset them
#
# so the class name is recoverable by matching the MetaObject handle loaded at
# each call site against the `&handle` argument of the registrar call.
#
# Output JSON is consumed by apply_reflection_names.py.
#
#   pyghidra-run <binary> --project-path ghidra-projects/dw4 \
#       --project-name dw4 -postScript dump_reflection.py \
#       --out ghidra-projects/dw4/reflection.json
#
# Args:
#   --out PATH        default stdout
#   --codemax 0xADDR  override the code/rodata boundary (default: auto-detect)
#
# @category PS2
# @runtime PyGhidra

import json
import struct
import typing

if typing.TYPE_CHECKING:
    from typing import Any

    currentProgram: Any = None
    getScriptArgs: Any = None

# Registrar / field-table consumers (addresses are stable for this build).
REGISTER = 0x002FE9C0   # igMetaObject registration (class name in t1)
ADD_FIELDS_CTOR = 0x002FDF40  # create the fields from a ctor table
NAME_FIELDS = 0x002FE000      # attach names/descs/offsets to the new fields
META_FIELD_COUNT = 0x002FE470  # returns a MetaObject's field count

_TEXT_RUN = 24
_NAME_WS = __import__("re").compile(r"\s+")

# MIPS register numbers.
A0, A1, A2, A3, T0, T1, T2, T3, SP = 4, 5, 6, 7, 8, 9, 10, 11, 29


def _args(argv):
    out_path, codemax = None, None
    i = 0
    while i < len(argv):
        a = argv[i]
        if a in ("--out", "-o") and i + 1 < len(argv):
            out_path = argv[i + 1]
            i += 2
        elif a == "--codemax" and i + 1 < len(argv):
            codemax = int(argv[i + 1], 0)
            i += 2
        else:
            i += 1
    return out_path, codemax


def _read_image():
    """Bulk-read the program's initialized memory (see dump_vtables.py)."""
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
        raise SystemExit("dump_reflection: no initialized addressable memory blocks")
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
                f"dump_reflection: short read at {hex(start)} ({got} of {size} bytes)"
            )
        buf[start - lo:start - lo + size] = bytearray((int(x) & 0xFF) for x in jbuf)
    return lo, buf, hi


def _detect_codemax(lo, buf, hi):
    win, frac = 512, 0.95
    for va in range(lo, hi - win, 4):
        off = va - lo
        sample = buf[off:off + win]
        good = sum(1 for c in sample if c == 0 or 32 <= c < 127)
        if good / win >= frac:
            return va
    return hi


class Image:
    def __init__(self, lo, buf, hi, codemax):
        self.lo, self.buf, self.hi, self.codemax = lo, buf, hi, codemax

    def u32(self, va):
        off = va - self.lo
        if off < 0 or off > len(self.buf) - 4:
            return None
        return struct.unpack_from("<I", self.buf, off)[0]

    def instr(self, va):
        """Decode one MIPS word into (op, rs, rt, rd, imm, funct)."""
        w = self.u32(va)
        if w is None:
            return None
        return (w >> 26, (w >> 21) & 0x1F, (w >> 16) & 0x1F, (w >> 11) & 0x1F,
                w & 0xFFFF, w & 0x3F)

    def cstr(self, va, limit=160):
        off = va - self.lo
        if off < 0 or off >= len(self.buf):
            return ""
        end = self.buf.find(b"\0", off, min(off + limit, len(self.buf)))
        if end < 0:
            return ""
        try:
            return bytes(self.buf[off:end]).decode("ascii")
        except UnicodeDecodeError:
            return ""

    def jal_target(self, va):
        w = self.u32(va)
        if w is None or (w >> 26) != 0x03:
            return None
        return ((va + 4) & 0xF0000000) | ((w & 0x03FFFFFF) << 2)

    def find_jals(self, target, lo=None, hi=None):
        lo = self.lo if lo is None else lo
        hi = self.codemax if hi is None else hi
        out = []
        for va in range(lo, hi - 3, 4):
            if self.jal_target(va) == target:
                out.append(va)
        return out


def _sext(imm):
    return imm - 0x10000 if imm >= 0x8000 else imm


def _step(img, regs, stack, va):
    """One forward step of the tiny constant/load tracker."""
    d = img.instr(va)
    if d is None:
        return
    op, rs, rt, rd, imm, funct = d
    if op == 0x0F:                                  # lui
        regs[rt] = imm << 16
    elif op in (0x09, 0x19):                        # addiu / daddiu
        base = regs.get(rs)
        if isinstance(base, int):
            regs[rt] = base + _sext(imm)
        elif rs == 0:
            regs[rt] = _sext(imm)
        else:
            regs.pop(rt, None)
    elif op == 0x0D:                                # ori
        base = regs.get(rs)
        if isinstance(base, int):
            regs[rt] = base | imm
        else:
            regs.pop(rt, None)
    elif op == 0x00 and funct in (0x21, 0x2D):      # addu / daddu
        if rt == 0:
            regs[rd] = regs.get(rs)
        elif rs == 0:
            regs[rd] = regs.get(rt)
        elif isinstance(regs.get(rs), int) and isinstance(regs.get(rt), int):
            regs[rd] = regs[rs] + regs[rt]
        else:
            regs.pop(rd, None)
    elif op == 0x00 and funct == 0x25:              # or
        if rt == 0:
            regs[rd] = regs.get(rs)
        elif rs == 0:
            regs[rd] = regs.get(rt)
        else:
            regs.pop(rd, None)
    elif op in (0x23, 0x27):                        # lw / lwu
        base = regs.get(rs)
        if isinstance(base, int):
            regs[rt] = ("ld", base + _sext(imm))
        else:
            regs.pop(rt, None)
    elif op in (0x2B, 0x3F):                        # sw / sd
        if rs == SP:
            stack[_sext(imm)] = regs.get(rt)


def _func_start(img, va, max_back=4096):
    """Find the enclosing function's entry by walking back to its frame prologue.

    Init functions all open with `addiu sp,sp,-N`, and we stop if a `jr ra`
    (function end) lies between the candidate and the call site. This is much
    more reliable than a fixed-size window: the MetaObject handle is often kept
    in a callee-saved register loaded near the top of the function.
    """
    for k in range(1, max_back):
        a = va - 4 * k
        if a < img.lo:
            break
        d = img.instr(a)
        if d is None:
            continue
        op, rs, rt, rd, imm, funct = d
        if op == 0x09 and rs == SP and rt == SP and imm >= 0x8000:
            for b in range(a, va, 4):
                dd = img.instr(b)
                if dd is not None and dd[0] == 0 and dd[5] == 0x08:
                    break                     # crossed a `jr ra`: not our function
            else:
                return a
    return max(img.lo, va - 600 * 4)


def resolve_call(img, jal_va, window=220, include_delay=True):
    """Track register constants/loads from the function entry to a call.

    Scanning the whole enclosing function (not a fixed window) keeps
    callee-saved registers correct even when the MetaObject handle is loaded
    long before the call.
    """
    regs, stack = {}, {}
    start = _func_start(img, jal_va)
    end = jal_va + (8 if include_delay else 4)
    for va in range(start, end, 4):
        _step(img, regs, stack, va)
    return regs, stack


def _read_names(img, va, count):
    """Read `count` name pointers, stopping early on a non-string (safety)."""
    out = []
    for _ in range(count):
        w = img.u32(va)
        if not w:
            break
        s = img.cstr(w, 120)
        if not s:
            break
        out.append((w, s))
        va += 4
    return out


def _read_ints(img, va, count):
    out = []
    for _ in range(count):
        w = img.u32(va)
        if w is None or w >= 0x100000:
            break
        out.append(w)
        va += 4
    return out


def _read_descs(img, va, count):
    """Field descriptor slots are BSS pointers (above the image, below BSS top)."""
    out = []
    for _ in range(count):
        w = img.u32(va)
        if w is None or not (img.codemax <= w < 0x0058D280):
            break
        out.append(w)
        va += 4
    return out


def _run_str_ptrs(img, va, limit=512):
    """Fallback: scan until the first non-string pointer (BSS / zero pad)."""
    out = []
    while len(out) < limit:
        w = img.u32(va)
        if not w:
            break
        s = img.cstr(w, 120)
        if not s:
            break
        out.append((w, s))
        va += 4
    return out


def _ctor_type_global(img, ctor):
    """A field-type constructor loads its MetaFieldDef from a 0x58xxxx global.

    Shape: `lui at,0x58; ... lw a0, off(at); jal FUN_002fda40(a0, ctx)`. That
    global is the stable per-type token; the same ctor means the same type.
    """
    at_val = None
    for k in range(24):
        d = img.instr(ctor + 4 * k)
        if d is None:
            return None
        op, rs, rt, rd, imm, funct = d
        if op == 0x0F and rt == 1:          # lui at, hi
            at_val = imm << 16
        elif op == 0x23 and rs == 1 and rt == A0 and at_val is not None:
            return at_val + _sext(imm)
    return None


def _handle_of(img, regs, reg):
    v = regs.get(reg)
    if isinstance(v, tuple) and v[0] == "ld":
        return v[1]
    return None


def _main():
    out_path, codemax_arg = _args(list(getScriptArgs()))
    lo, buf, hi = _read_image()
    codemax = codemax_arg if codemax_arg is not None else _detect_codemax(lo, buf, hi)
    img = Image(lo, buf, hi, codemax)

    # --- 1. class registrations: handle address -> class name ------------
    meta = {}
    for j in img.find_jals(REGISTER):
        regs, stack = resolve_call(img, j)
        handle = regs.get(A1)
        name_ptr = regs.get(T1)
        if not isinstance(handle, int) or not isinstance(name_ptr, int):
            continue
        name = img.cstr(name_ptr, 120)
        if not name:
            continue
        meta[handle] = {
            "name": name,
            "name_ptr": name_ptr,
            "site": j,
            "post_init": stack.get(0) if isinstance(stack.get(0), int) else None,
        }

    # --- 2. field ctor chunks: FUN_002fdf40(metaobj, ctor_table, count) --
    ctor_chunks = {}
    for j in img.find_jals(ADD_FIELDS_CTOR):
        regs, _ = resolve_call(img, j)
        handle = _handle_of(img, regs, A0)
        table = regs.get(A1)
        count = regs.get(A2)
        if handle is None or not isinstance(table, int):
            continue
        ctors = []
        a = table
        while len(ctors) < 512:
            w = img.u32(a)
            if w is None or not (lo <= w < codemax):
                break
            ctors.append(w)
            a += 4
        ctor_chunks[handle] = {
            "table": table,
            "count": count if isinstance(count, int) else None,
            "ctors": ctors,
            "site": j,
        }

    # --- 3. field name/offset chunks: FUN_002fe000(...) ------------------
    field_chunks = {}
    unresolved = []
    for j in img.find_jals(NAME_FIELDS):
        regs, _ = resolve_call(img, j)
        handle = _handle_of(img, regs, A0)
        names_ptr = regs.get(A1)
        descs_ptr = regs.get(A2)
        offs_ptr = regs.get(A3)
        start = regs.get(T0)
        if handle is None or not isinstance(names_ptr, int):
            unresolved.append(j)
            continue
        cc = ctor_chunks.get(handle)
        n = cc["count"] if cc and isinstance(cc.get("count"), int) else None
        if n is not None:
            names = _read_names(img, names_ptr, n)
        else:
            names = _run_str_ptrs(img, names_ptr)
        descs = _read_descs(img, descs_ptr, len(names)) if isinstance(descs_ptr, int) else []
        offs = _read_ints(img, offs_ptr, len(names)) if isinstance(offs_ptr, int) else []
        field_chunks[handle] = {
            "names_ptr": names_ptr,
            "descs_ptr": descs_ptr,
            "offsets_ptr": offs_ptr,
            "start": start if isinstance(start, int) else None,
            "names": [s for _, s in names],
            "name_ptrs": [p for p, _ in names],
            "descs": descs,
            "offsets": offs,
            "site": j,
        }

    # --- 4. assemble per class ------------------------------------------
    def field_type(ctor):
        """A field's type is the MetaField class the ctor builds: the ctor
        loads that class's MetaObject handle (a 0x58xxxx global) and the same
        handle names the class at its own registration site."""
        if not ctor:
            return None, None
        tg = _ctor_type_global(img, ctor)
        if tg is None:
            return None, None
        m = meta.get(tg)
        return tg, (m["name"] if m else None)

    classes = {}
    field_types = {}
    for handle, m in meta.items():
        fields = []
        fc = field_chunks.get(handle)
        cc = ctor_chunks.get(handle)
        if fc:
            ctors = cc["ctors"] if cc else []
            for i, name in enumerate(fc["names"]):
                ctor = ctors[i] if i < len(ctors) else None
                tg, tname = field_type(ctor)
                if ctor:
                    ft = field_types.setdefault(hex(ctor), {
                        "type": tname, "type_global": hex(tg) if tg else None,
                        "fields": 0,
                    })
                    ft["fields"] += 1
                fields.append(
                    {
                        "name": name,
                        "name_ptr": fc["name_ptrs"][i] if i < len(fc["name_ptrs"]) else None,
                        "offset": fc["offsets"][i] if i < len(fc["offsets"]) else None,
                        "desc": fc["descs"][i] if i < len(fc["descs"]) else None,
                        "ctor": ctor,
                        "type": tname,
                    }
                )
        classes[hex(handle)] = {
            "class": m["name"],
            "handle": hex(handle),
            "name_ptr": hex(m["name_ptr"]),
            "register_site": hex(m["site"]),
            "post_init": hex(m["post_init"]) if m["post_init"] else None,
            "field_table": hex(fc["names_ptr"]) if fc else None,
            "ctor_table": hex(cc["table"]) if cc else None,
            "field_count": len(fields),
            "fields": fields,
        }

    out = {
        "program": currentProgram.getName(),
        "language": str(currentProgram.getLanguageID()),
        "image_lo": hex(lo),
        "image_hi": hex(hi),
        "codemax": hex(codemax),
        "counts": {
            "metaobjects": len(meta),
            "with_fields": sum(1 for c in classes.values() if c["field_count"]),
            "fields": sum(c["field_count"] for c in classes.values()),
            "field_types": len(field_types),
            "ctor_chunks": len(ctor_chunks),
            "unresolved_name_calls": len(unresolved),
        },
        "field_types": field_types,
        "classes": classes,
    }
    text = json.dumps(out, indent=1)
    if out_path:
        with open(out_path, "w", encoding="utf-8") as fh:
            fh.write(text)
        c = out["counts"]
        print(
            f"dump_reflection: {c['metaobjects']} MetaObjects, "
            f"{c['with_fields']} with fields, {c['fields']} fields "
            f"({c['ctor_chunks']} ctor chunks, "
            f"{c['unresolved_name_calls']} unresolved name calls) -> {out_path}"
        )
    else:
        print(text)


def main():
    import traceback

    try:
        _main()
    except BaseException:
        traceback.print_exc()
        raise


main()
