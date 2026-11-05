#!/usr/bin/env python3
"""
lua_dump.py — parse Lua 4.0.1 binary chunks (as found in Digimon World 4's
NDMW.AFS) and dump a readable disassembly.

Lua 4.0.1 binary format (lundump.c):
  Header (21 bytes):
    0x1B, "Lua", version(0x40), endian(1=LE), sizeof(int)=4, sizeof(size_t)=4,
    sizeof(Instruction)=4, SIZE_INSTRUCTION=32, SIZE_OP=6, SIZE_B=9,
    sizeof(Number)=8, test-number(8 bytes)
  Proto:
    source:  size_t len + len bytes (includes trailing NUL; 0 => NULL)
    lineDefined:  int32
    numparams:    int32
    is_vararg:    u8
    maxstacksize: int32
    locals:  n=int32, then n * (varname:str, startpc:int32, endpc:int32)
    lines:   n=int32, then n * int32
    constants: nkstr=int32 + strings; nknum=int32 + doubles; nkproto=int32 + protos
    code:    n=int32, then n * u32 instruction
All integers little-endian.

Usage:
  python3 lua_dump.py <blob> [--limit N] [--text]
Finds every 0x1B"Lua" magic and disassembles each chunk.
"""
import struct
import sys

# opcode enum (Lua 4.0.1 lopcodes.h)
OPCODES = [
    "OP_END", "OP_RETURN", "OP_CALL", "OP_TAILCALL", "OP_PUSHNIL", "OP_POP",
    "OP_PUSHINT", "OP_PUSHSTRING", "OP_PUSHNUM", "OP_PUSHNEGNUM",
    "OP_PUSHUPVALUE", "OP_GETLOCAL", "OP_GETGLOBAL", "OP_GETTABLE",
    "OP_GETDOTTED", "OP_GETINDEXED", "OP_PUSHSELF", "OP_CREATETABLE",
    "OP_SETLOCAL", "OP_SETGLOBAL", "OP_SETTABLE", "OP_SETLIST", "OP_SETMAP",
    "OP_ADD", "OP_ADDI", "OP_SUB", "OP_MULT", "OP_DIV", "OP_POW",
    "OP_CONCAT", "OP_MINUS", "OP_NOT", "OP_JMPNE", "OP_JMPEQ", "OP_JMPLT",
    "OP_JMPLE", "OP_JMPGT", "OP_JMPGE", "OP_JMPT", "OP_JMPF", "OP_JMPONT",
    "OP_JMPONF", "OP_JMP", "OP_PUSHNILJMP", "OP_FORPREP", "OP_FORLOOP",
    "OP_LFORPREP", "OP_LFORLOOP", "OP_CLOSURE",
]

# instruction layout
SIZE_OP = 6
SIZE_B = 9
SIZE_A = 17
POS_B = SIZE_OP
POS_A = SIZE_OP + SIZE_B
MAXARG_S = ((1 << 26) - 1) >> 1  # stock Lua 4.0.1: 2^25 - 1


class Chunk:
    def __init__(self, data, off):
        self.data = data
        self.off = off
        self.pos = off
        self.strings = []
        self.numbers = []

    def u8(self):
        v = self.data[self.pos]
        self.pos += 1
        return v

    def u32(self):
        v = struct.unpack_from("<I", self.data, self.pos)[0]
        self.pos += 4
        return v

    def i32(self):
        v = struct.unpack_from("<i", self.data, self.pos)[0]
        self.pos += 4
        return v

    def f64(self):
        v = struct.unpack_from("<d", self.data, self.pos)[0]
        self.pos += 8
        return v

    def read_string(self):
        size = self.u32()
        if size == 0:
            return None
        raw = self.data[self.pos:self.pos + size]
        self.pos += size
        # strip trailing NUL
        return raw.rstrip(b"\x00").decode("latin1", "replace")


def parse_function(c):
    source = c.read_string()
    line_defined = c.i32()
    numparams = c.i32()
    is_vararg = c.u8()
    maxstack = c.i32()

    nloc = c.i32()
    locals_ = []
    for _ in range(nloc):
        varname = c.read_string()
        startpc = c.i32()
        endpc = c.i32()
        locals_.append((varname, startpc, endpc))

    nlines = c.i32()
    lineinfo = [c.i32() for _ in range(nlines)]

    nkstr = c.i32()
    kstr = [c.read_string() for _ in range(nkstr)]
    kstr_base = len(c.strings)
    c.strings.extend(kstr)

    nknum = c.i32()
    knum = [c.f64() for _ in range(nknum)]
    knum_base = len(c.numbers)
    c.numbers.extend(knum)

    nkproto = c.i32()
    kproto = [parse_function(c) for _ in range(nkproto)]

    ncode = c.i32()
    code = [c.u32() for _ in range(ncode)]

    return {
        "source": source,
        "lineDefined": line_defined,
        "numparams": numparams,
        "is_vararg": is_vararg,
        "maxstack": maxstack,
        "locals": locals_,
        "lineinfo": lineinfo,
        "kstr": kstr,
        "kstr_base": kstr_base,
        "knum": knum,
        "knum_base": knum_base,
        "kproto": kproto,
        "code": code,
    }


def disasm(fn, c):
    lines = []
    for pc, ins in enumerate(fn["code"]):
        op = ins & 0x3F
        if op >= len(OPCODES):
            lines.append(f"    {pc:4d}  ??? {op}")
            continue
        name = OPCODES[op]
        # decode operands by opcode type
        u = ins >> SIZE_OP
        s = u - MAXARG_S
        b = (ins >> POS_B) & ((1 << SIZE_B) - 1)
        a = (ins >> POS_A) & ((1 << SIZE_A) - 1)

        def kstr(idx):
            if 0 <= idx < len(fn["kstr"]):
                return repr(fn["kstr"][idx])
            return f"kstr[{idx}]"

        def knum(idx):
            if 0 <= idx < len(fn["knum"]):
                return repr(fn["knum"][idx])
            return f"knum[{idx}]"

        def local(idx):
            if 0 <= idx < len(fn["locals"]):
                return fn["locals"][idx][0]
            return f"loc[{idx}]"

        # operand kinds from lopcodes.h comments
        U_OPS = {"OP_RETURN", "OP_PUSHNIL", "OP_POP", "OP_PUSHUPVALUE",
                 "OP_CREATETABLE", "OP_SETMAP", "OP_CLOSURE"}
        S_OPS = {"OP_PUSHINT", "OP_ADDI"}
        K_OPS = {"OP_PUSHSTRING", "OP_GETGLOBAL", "OP_GETDOTTED",
                 "OP_PUSHSELF", "OP_SETGLOBAL"}
        N_OPS = {"OP_PUSHNUM", "OP_PUSHNEGNUM"}
        L_OPS = {"OP_GETLOCAL", "OP_GETINDEXED", "OP_SETLOCAL"}
        AB_OPS = {"OP_CALL", "OP_TAILCALL", "OP_SETTABLE", "OP_SETLIST"}
        J_OPS = {"OP_JMPNE", "OP_JMPEQ", "OP_JMPLT", "OP_JMPLE", "OP_JMPGT",
                 "OP_JMPGE", "OP_JMPT", "OP_JMPF", "OP_JMPONT", "OP_JMPONF",
                 "OP_JMP", "OP_PUSHNILJMP", "OP_FORPREP", "OP_FORLOOP",
                 "OP_LFORPREP", "OP_LFORLOOP"}

        if name in U_OPS:
            arg = f"u={u}"
        elif name in S_OPS:
            arg = f"s={s}"
        elif name in K_OPS:
            arg = f"K[{u}]={kstr(u)}"
        elif name in N_OPS:
            arg = f"N[{u}]={knum(u)}"
        elif name in L_OPS:
            arg = f"L[{u}]={local(u)}"
        elif name in AB_OPS:
            arg = f"A={a} B={b}"
        elif name == "OP_PUSHNILJMP":
            arg = f"(->pc {pc + 2})"
        elif name in J_OPS:
            target = pc + 1 + s
            arg = f"J={s} (->pc {target})"
        else:
            arg = ""
        lines.append(f"    {pc:4d}  {name}  {arg}")
    return "\n".join(lines)


def parse_chunk(data, off):
    c = Chunk(data, off)
    # header
    assert c.u8() == 0x1B, "bad ID_CHUNK"
    sig = bytes([c.u8(), c.u8(), c.u8()])
    assert sig == b"Lua", f"bad signature {sig}"
    version = c.u8()
    endian = c.u8()
    sz_int = c.u8()
    sz_sizet = c.u8()
    sz_instr = c.u8()
    sz_instr_bits = c.u8()
    sz_op = c.u8()
    sz_b = c.u8()
    sz_num = c.u8()
    test_num = c.f64()
    hdr = {
        "version": version, "endian": endian, "sz_int": sz_int,
        "sz_sizet": sz_sizet, "sz_instr": sz_instr,
        "sz_instr_bits": sz_instr_bits, "sz_op": sz_op, "sz_b": sz_b,
        "sz_num": sz_num, "test_num": test_num,
    }
    main = parse_function(c)
    return hdr, main, c


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    flags = [a for a in sys.argv[1:] if a.startswith("--")]
    limit = None
    for f in flags:
        if f.startswith("--limit="):
            limit = int(f.split("=")[1])
    if not args:
        print(__doc__)
        return
    path = args[0]
    data = open(path, "rb").read()

    magic = b"\x1bLua"
    starts = []
    i = 0
    while True:
        j = data.find(magic, i)
        if j < 0:
            break
        starts.append(j)
        i = j + 1

    print(f"{path}: {len(starts)} Lua chunk(s)")
    if limit:
        starts = starts[:limit]

    for idx, off in enumerate(starts):
        try:
            hdr, main, c = parse_chunk(data, off)
        except Exception as e:
            print(f"--- chunk {idx} @ 0x{off:x}: PARSE ERROR {e}")
            continue
        print(f"\n=== chunk {idx} @ 0x{off:x} (end 0x{c.pos:x}) "
              f"ver=0x{hdr['version']:02x} endian={hdr['endian']} ===")
        print(f"  source={main['source']!r} line={main['lineDefined']} "
              f"params={main['numparams']} vararg={main['is_vararg']} "
              f"maxstack={main['maxstack']}")
        print(f"  strings({len(main['kstr'])}): {[s for s in main['kstr']]}")
        if main["knum"]:
            print(f"  numbers({len(main['knum'])}): {main['knum']}")
        if main["locals"]:
            print(f"  locals: {[(l[0], l[1], l[2]) for l in main['locals']]}")
        if main["kproto"]:
            print(f"  sub-protos: {len(main['kproto'])}")
        print("  code:")
        print(disasm(main, c))


if __name__ == "__main__":
    main()
