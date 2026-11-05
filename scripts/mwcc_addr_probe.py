#!/usr/bin/env python3
"""MWCC stack/addressing probe: why a frame slot's offset does or does not fold
into a load displacement (the `*_GetVTable` plain-family wall).

Builds minimal C snippets, compiles each with the project's MWCC (wibo) and
disassembles the function, so the addressing rule can be re-measured on this
toolchain rather than taken on faith.

Usage:
    python3 scripts/mwcc_addr_probe.py                 # print the rule probes
    python3 scripts/mwcc_addr_probe.py --sweep         # + enumerate the fold space

The rule it demonstrates (MWCC 3.0-011126 / 2.4 / 2.3.3, PS2):
  * `arr[i]` as a *value* folds the frame symbol's offset into the load
    displacement, and the load width AND index scale both follow sizeof(element):
        char u[16]; u[i]   ->  addu v0,i,sp ; lb   v0,16(v0)
        int  u[4]; u[i]    ->  sll  v0,i,2 ; addu v0,v0,sp ; lw v0,16(v0)
    so a *word* value-subscript always carries a scale-4 `sll`; a scale-1 word
    load is not representable in C (no sizeof==1 type loads 4 bytes).
  * `&arr[i]`, `arr + i`, `*(T *)((char *)arr + i)` do NOT fold: MWCC emits
    `addu v0,i,sp ; addiu v0,v0,D ; lw v0,0(v0)`.
  * A trailing constant folds into the load only when the addend base is a
    *register* (a parameter, a loaded pointer, `__builtin_frame_address`), never
    when it is the frame pointer `sp` itself -- see the `base` probes below.
"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
WIBO = os.path.join(ROOT, "local", "wibo")
MWCC = os.path.join(ROOT, "local", "mwcps2", "3.0-011126", "mwccps2.exe")
SCRATCH = os.path.join(ROOT, "build", "addr-probe")
FLAGS = ["-O3", "-Iinclude"]

HDR = (
    "int igObject_InitHeader(void*);\n"
    "extern int DAT_005225b0[4];\n"
    "extern void *DAT_00586dc8[4];\n"
)
SLOT = "*(int *)((char *)DAT_00586dc8[0] + 916)"


def compile_insns(src, tag, flags=FLAGS):
    """Compile one snippet and return [(va, word, mnemonic, operands), ...]."""
    os.makedirs(SCRATCH, exist_ok=True)
    c = os.path.join(SCRATCH, tag + ".c")
    o = os.path.join(SCRATCH, tag + ".o")
    with open(c, "w") as fh:
        fh.write(src)
    r = subprocess.run([WIBO, MWCC, "-c", *flags, c, "-o", o],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0 or not os.path.exists(o):
        return None, r.stdout + r.stderr
    r2 = subprocess.run(["mipsel-linux-gnu-objdump", "-d", "-z", o],
                        capture_output=True, text=True)
    ins = []
    for line in r2.stdout.splitlines():
        m = re.match(r"\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)(?:\s+(.*))?$", line)
        if m:
            ins.append((int(m.group(1), 16), m.group(2), m.group(3),
                        (m.group(4) or "").strip()))
    return ins, r2.stdout


def show(tag, body, flags=FLAGS):
    ins, raw = compile_insns(HDR + body, tag, flags)
    print("== %s" % tag)
    if ins is None:
        print("   compile failed: " + raw.strip().splitlines()[-1][:120])
        return
    for va, _w, mn, ops in ins:
        print("   %08x %-7s %s" % (va, mn, ops))


RULE_PROBES = [
    ("value-subscript/char", "int f(void){ char u[16]; igObject_InitHeader(u); "
                             "*(int*)u=(int)&DAT_005225b0[0]; return u[" + SLOT + "]; }"),
    ("value-subscript/int", "int f(void){ int u[4]; igObject_InitHeader(u); "
                            "u[0]=(int)&DAT_005225b0[0]; return u[" + SLOT + "]; }"),
    ("addr-of-subscript", "void *f(void){ char u[16]; igObject_InitHeader(u); "
                          "*(int*)u=(int)&DAT_005225b0[0]; return *(void **)&u[" + SLOT + "]; }"),
    ("pointer-arith", "void *f(void){ char u[16]; igObject_InitHeader(u); "
                      "*(int*)u=(int)&DAT_005225b0[0]; return *(void **)(u + " + SLOT + "); }"),
    ("register-base", "int f(int *p, int i){ return *(int *)((char *)p + i + 16); }"),
]


def main(argv):
    for tag, body in RULE_PROBES:
        show(tag.replace("/", "_"), body + "\n")
    if "--sweep" in argv:
        _space()


# ---------------------------------------------------------------------------
# The generator space reported in docs/engine/getvtable-fold.md (finding #659).
# ---------------------------------------------------------------------------
def _space():
    idx = [SLOT, "(unsigned)(" + SLOT + ")", "(char)(" + SLOT + ")",
           "(short)(" + SLOT + ")", "(" + SLOT + ")*1", "(" + SLOT + ")+0",
           "(" + SLOT + ")>>2"]
    aggs = {
        "c16":  ("char u[16];", "igObject_InitHeader(u); *(int*)u=(int)&DAT_005225b0[0];", "u"),
        "i4":   ("int u[4];", "igObject_InitHeader(u); u[0]=(int)&DAT_005225b0[0];", "u"),
        "vp2":  ("void *u[2];", "igObject_InitHeader(u); u[0]=&DAT_005225b0[0];", "u"),
        "un":   ("union { int i[4]; char c[16]; } u;", "igObject_InitHeader(&u); u.i[0]=(int)&DAT_005225b0[0];", "(char *)&u"),
    }
    rets = ["*(void **)({B} + {I})", "*(int *)({B} + {I})", "*(void **)({I} + {B})",
            "*(void **)((char *){B} + {I})", "((void **){B})[{I}]",
            "*(void **)&{B}[{I}]"]
    n = 0
    hits = 0
    detail = []
    for an, (decl, init, base) in aggs.items():
        for r in rets:
            for i in idx:
                expr = r.format(B=base, I=i)
                body = "void *f(void){ %s %s return %s; }" % (decl, init, expr)
                ins, _raw = compile_insns(HDR + body, "sw_%s_%d" % (an, n))
                n += 1
                if ins is None:
                    continue
                ops = [mn + " " + o for _v, _w, mn, o in ins]
                for k in range(len(ops) - 1):
                    if re.match(r"addu \w+,\w+,sp$", ops[k]) and \
                       re.match(r"lw \w+,[1-9]\d*\(\w+\)$", ops[k + 1]):
                        hits += 1
                        detail.append((an, expr, ops[k:k + 2]))
    print("\nSWEEP: %d forms tested, %d fold-hits (`addu Rd,Ri,sp` immediately "
          "followed by `lw Rd,D(Rd)`, D>0)" % (n, hits))
    for an, expr, tail in detail[:10]:
        print("   [%s] %s -> %s" % (an, expr, " ; ".join(tail)))


if __name__ == "__main__":
    main(sys.argv[1:])
