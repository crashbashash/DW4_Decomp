#!/usr/bin/env python3
"""lua_find_junk.py — find & disassemble Lua chunks related to the junk shop."""
import struct, sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from lua_dump import parse_chunk, OPCODES, SIZE_OP, SIZE_B, POS_B, POS_A, MAXARG_S

def find_magic(data, magic):
    starts=[]; i=0
    while True:
        j=data.find(magic, i)
        if j<0: break
        starts.append(j); i=j+1
    return starts

def collect(fn, out):
    out.append(fn)
    for s in fn["kproto"]:
        collect(s, out)

def disasm(fn, allstr, allnum, depth=0):
    out=[]
    code=fn["code"]
    for pc, ins in enumerate(code):
        op=ins & 0x3f
        b=(ins >> SIZE_OP) & ((1<<SIZE_B)-1)
        a=(ins >> POS_A) & ((1<<17)-1)
        # signed B
        b_signed = b - (1<<SIZE_B) if b & (1<<(SIZE_B-1)) else b
        name=OPCODES[op] if op < len(OPCODES) else f"OP_{op}"
        def K(i):
            i = i - MAXARG_S
            if 0 <= i < len(fn["kstr"]):
                return repr(fn["kstr"][i])
            return f"K[{i}]"
        def N(i):
            i = i - MAXARG_S
            if 0 <= i < len(fn["knum"]):
                return repr(fn["knum"][i])
            return f"N[{i}]"
        # simple arg display
        out.append(f"  {pc:4d} {name:16s} A={a:6d} B={b_signed:6d}")
    return out

def main():
    path=sys.argv[1]
    data=open(path,"rb").read()
    count=struct.unpack("<I", data[4:8])[0]
    entries=[struct.unpack("<II", data[8+i*8:8+i*8+8]) for i in range(count)]
    magic=b"\x1bLua"
    for eidx,(off,size) in enumerate(entries):
        blob=data[off:off+size]
        for cidx,s in enumerate(find_magic(blob, magic)):
            try:
                hdr, main, c = parse_chunk(blob, s)
            except Exception:
                continue
            fns=[]
            collect(main, fns)
            allstr=[]
            for fn in fns:
                allstr.extend(fn["kstr"])
            joined=" ".join(allstr).lower()
            if "junk" in joined or "hakai" in joined or "kifu" in joined:
                print(f"\n===== entry {eidx} chunk {cidx} @0x{off+s:x} =====")
                print("strings:", [x for x in allstr if len(x)<40][:40])
                for fn in fns:
                    for line in disasm(fn, allstr, []):
                        print(line)
                # only print first match of each entry to limit output
                break

if __name__=="__main__":
    main()
