#!/usr/bin/env python3
"""regalloc_trace.py SOURCE.cpp [--only-case N] [--tail N] : trace the pinned compiler's register colouring.

Compiles SOURCE.cpp with the pinned alternate compiler (local/mwcps2/combat/mwccps2.exe, -O3,p) while a debugger
patches the *running process image* (nothing on disk is modified) so that the compiler's graph-colouring pass logs
every node it pushes, plus a snapshot of the whole interference graph before and after colouring.  It then reports
where the receiver (the node with the largest degree, i.e. `this`) lands and which nodes sit next to it.

Why: the receiver colours s0 where retail has s4, and that is not a prologue problem.  See tools/dispatcher/ALLOCATION.md
for the model this script is built on and for how to read the output.

The compiler colours the function more than once: when a pass spills, it inserts spill code and colours again, and only the last
big pass produces the emitted registers.  The script therefore reports the last pass that has more than 500 nodes (--round picks
another one).  Earlier versions read the first pass, whose receiver colour is not the emitted one.

--adj DIR      also dump the full interference graph of every big pass to DIR/adjN.json ({node: [neighbours]}), and --ctx FILE the node
               table (costs, flags, push order, final colours) of the chosen pass; tools/dispatcher/regalloc_sim.py replays the
               simplify/select passes on such a dump so that what-if changes (ids, costs, edges) can be tested in milliseconds.

For any single function use tools/dispatcher/regalloc.py (it imports trace() from here); this script is the dispatcher-sized CLI.
Compilers: the patch profiles in PROFILES cover local/mwcps2/combat (the dispatcher's) and local/mwcps2/3.0-011126 (the tree default);
pass --compiler EXE and --min-nodes 1 to trace a small function by hand.  --adj DIR now also stores the IR of each pass (adjN.json:
{cls, adj, blocks}); regalloc_sim.py reads both layouts.

Needs on the host: gdb, GNU as/ld with 32-bit x86 support, and the wibo loader at local/wibo (or $DW4_WIBO).
The patch addresses are those of the pinned mwccps2.exe; the script verifies the bytes it is about to overwrite and
refuses to run on any other build.

--only-case N  keeps FIGHTCALC sub-command N (the `switch (sp494)` of the draft) and empties the other 21, which isolates
               one region's contribution (compile is ~1 s either way).
"""
import argparse, collections, os, re, shutil, struct, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
WIBO = os.environ.get("DW4_WIBO", os.path.join(ROOT, "local", "wibo"))
MWCC = os.path.join(ROOT, "local", "mwcps2", "combat", "mwccps2.exe")
LOGBASE = 0x20000000

# Per-compiler patch profiles.  Every profile describes the same instrumentation: the log lives in a 256 MB block that the script
# makes read/write inside the compiler process (mprotect from the debugger) because the compiler's own heap arena grows over any
# fixed address; the cave (a few hundred bytes of x86) sits in the slack at the end of .text.  Sites: SA/SB/SC are the three
# places where simplify() removes a node (first scan / spill pick / rescan), each a 5-byte `or word [reg+0x14], 2` that is replaced
# by a jump into the cave; CALL_SIMP / CALL_SEL are the call sites of simplify() and select() in the colouring driver; SF is the
# first spill pick (costs exist from there on).  Coloring.c: simplify() and select(), GPR and FPR classes colour in separate passes.
# The patched compiler is identified by the SHA-256 of the executable; any other build is refused.
PROFILES = {
    # local/mwcps2/combat/mwccps2.exe: simplify at 0x4c3f30, select at 0x4c42a0.
    "acf1088553362dddef7eee2d269848b03208e29fd26caa441848e57b6299786a": dict(
        name="combat", CAVE=0x53D400, LOGP=0x5B5F00, FLAG=0x5B5F04, CLS=0x5B5E1F, CNT=0x5B4610, BASE=0x5B4154, BLOCKS=0x5B412C, IRN=0x2A, IRO=0x3C,
        SIMPLIFY=0x4C3F30, SELECT=0x4C42A0,
        SA=(0x4C400F, "eax", 0x4C4014), SB=(0x4C4179, "ecx", 0x4C417E), SC=(0x4C4249, "edx", 0x4C424E),
        CALL_SIMP=0x4C4654, CALL_SEL=0x4C465A,
        SF=(0x4C4060, "d9eed9ee89d9", "fldz\n  fldz\n  mov ecx, ebx", 0x4C4066)),
    # local/mwcps2/3.0-011126/mwccps2.exe (the tree's default compiler): simplify at 0x4aedc0, select at 0x4af0f0.
    "0e16a5d6205101f840f85c02664f21cd63b39a0dec2dff417b3a61b4477f0e00": dict(
        name="3.0-011126", CAVE=0x50C400, LOGP=0x57E800, FLAG=0x57E804, CLS=0x57E036, CNT=0x57CAA4, BASE=0x57C778, BLOCKS=0x57C750, IRN=0x22, IRO=0x34,
        SIMPLIFY=0x4AEDC0, SELECT=0x4AF0F0,
        SA=(0x4AEE8D, "edx", 0x4AEE92), SB=(0x4AEFE7, "edx", 0x4AEFEC), SC=(0x4AF0A7, "edx", 0x4AF0AC),
        CALL_SIMP=0x4AF497, CALL_SEL=0x4AF49D,
        SF=(0x4AEED5, "d9eed9eed9ee89da", "fldz\n  fldz\n  fldz\n  mov edx, ebx", 0x4AEEDD)),
}
# Default: the pinned alternate compiler of the dispatcher.
DEFAULT_COMPILER = "local/mwcps2/combat/mwccps2.exe"


def profile_for(exe):
    import hashlib
    h = hashlib.sha256(open(exe, "rb").read()).hexdigest()
    if h not in PROFILES:
        raise SystemExit("no trace profile for this compiler build (%s)" % h[:12])
    return PROFILES[h]


def sites(P):
    """address -> (cave offset, kind, expected original bytes (hex), patch length)"""
    sa, sb, sc, sf = P["SA"], P["SB"], P["SC"], P["SF"]
    return {sa[0]: (0x000, "jmp", "66834814" if sa[1] == "eax" else "6683" + {"ecx": "49", "edx": "4a"}[sa[1]] + "1402", 5),
            sb[0]: (0x080, "jmp", "6683" + {"eax": "48", "ecx": "49", "edx": "4a"}[sb[1]] + "1402", 5),
            sc[0]: (0x100, "jmp", "6683" + {"eax": "48", "ecx": "49", "edx": "4a"}[sc[1]] + "1402", 5),
            P["CALL_SIMP"]: (0x180, "call", None, 5),
            P["CALL_SEL"]: (0x200, "call", None, 5),
            sf[0]: (0x280, "jmp", sf[1], len(sf[1]) // 2)}


CAVE_ASM = r"""
.intel_syntax noprefix
.macro LOGNODE ty, reg
  pushfd
  push esi
  push edi
  push ecx
  mov esi, \reg
  mov edi, dword ptr [%(LOGP)#x]
  mov dword ptr [edi], \ty
  mov dword ptr [edi+4], esi
%(copy)s  add dword ptr [%(LOGP)#x], 48
  pop ecx
  pop edi
  pop esi
  popfd
.endm
.macro DUMPNODES ty
  pushfd
  pushad
  mov edi, dword ptr [%(LOGP)#x]
  mov dword ptr [edi], \ty
  movsx ecx, byte ptr [%(CLS)#x]
  mov dword ptr [edi+4], ecx
  mov ebx, dword ptr [ecx*4+%(CNT)#x]
  mov dword ptr [edi+8], ebx
  mov esi, dword ptr [%(BASE)#x]
  add edi, 12
  imul ecx, ebx, 30
  cld
  rep movsb
  mov dword ptr [%(LOGP)#x], edi
  popad
  popfd
.endm
.text
.globl _start
_start:
siteA:
  LOGNODE 1, %(RA)s
  or word ptr [%(RA)s+0x14], 2
  jmp %(XA)#x
.balign 128
siteB:
  LOGNODE 2, %(RB)s
  or word ptr [%(RB)s+0x14], 2
  jmp %(XB)#x
.balign 128
siteC:
  LOGNODE 3, %(RC)s
  or word ptr [%(RC)s+0x14], 2
  jmp %(XC)#x
.balign 128
siteE:
  int3
  mov dword ptr [%(FLAG)#x], 0
  DUMPNODES 5
  jmp %(SIMPLIFY)#x
.balign 128
siteD:
  push dword ptr [esp+4]
  call %(SELECT)#x
  add esp, 4
  push eax
  DUMPNODES 4
  pop eax
  ret
.balign 128
siteF:
  cmp dword ptr [%(FLAG)#x], 0
  jne 1f
  mov dword ptr [%(FLAG)#x], 1
  DUMPNODES 6
1:
  %(FREPL)s
  jmp %(XF)#x
"""

REGS = {0: "zero", 2: "v0", 3: "v1", 4: "a0", 5: "a1", 6: "a2", 7: "a3", 24: "t8", 25: "t9", 28: "gp", 29: "sp", 31: "ra",
        30: "s8"}
REGS.update({8 + i: "t%d" % i for i in range(8)})
REGS.update({16 + i: "s%d" % i for i in range(8)})


def build_cave(tmp, P):
    copy = "".join("  mov ecx, dword ptr [esi+%d]\n  mov dword ptr [edi+%d], ecx\n" % (4 * i, 8 + 4 * i) for i in range(8))
    asm = os.path.join(tmp, "cave.s")
    d = dict(P, copy=copy, RA=P["SA"][1], XA=P["SA"][2], RB=P["SB"][1], XB=P["SB"][2], RC=P["SC"][1], XC=P["SC"][2],
             FREPL=P["SF"][2], XF=P["SF"][3])
    open(asm, "w").write(CAVE_ASM % d)
    subprocess.run(["as", "--32", "-o", os.path.join(tmp, "cave.o"), asm], check=True)
    subprocess.run(["ld", "-m", "elf_i386", "-Ttext=%#x" % P["CAVE"], "--oformat", "binary", "-o", os.path.join(tmp, "cave.bin"),
                    os.path.join(tmp, "cave.o")], check=True)
    return open(os.path.join(tmp, "cave.bin"), "rb").read()[:0x300]


# Debugger-side helper: the cave executes an int3 at the start of every colouring pass.  The helper walks the compiler's edge lists
# (node +0x1a -> edge {+0xc lo, +0xe hi, +4 next-if-id<hi, +8 next-otherwise}) and the IR (block list: +0x28 weight, +0x14 first
# instruction, +0 next; instruction: +0 next, +0xc opcode, +0x2a operand count, operands of 0x16 bytes at +0x3c: kind, class,
# flags (s16), node (s16)) and continues.  One adjN.json per pass: {cls, adj: {node: [neighbours]}, blocks: [[weight, [[op, [[kind,
# class, flags, node], ...]], ...]]]}.
ADJ_HELPER = r"""
import gdb, struct, json, os
OUT = os.environ["REGALLOC_ADJ_DIR"]
MINNODES = int(os.environ.get("REGALLOC_MIN_NODES", "1"))
N = [0]
def dump():
    inf = gdb.selected_inferior()
    rd = lambda a, n: bytes(inf.read_memory(a, n))
    u32 = lambda a: struct.unpack("<I", rd(a, 4))[0]
    cls = rd(%(CLS)#x, 1)[0]
    cls = cls - 256 if cls > 127 else cls
    cnt = u32(%(CNT)#x + cls * 4)
    if cnt < MINNODES:
        return
    base = u32(%(BASE)#x)
    raw = rd(base, cnt * 30)
    adj = {}
    for i in range(cnt):
        nid, = struct.unpack_from("<h", raw, i * 30 + 16)
        e, = struct.unpack_from("<I", raw, i * 30 + 0x1a)
        lst = []
        while e and len(lst) < 100000:
            lo, hi = struct.unpack_from("<hh", rd(e, 16), 12)
            nl, nr = struct.unpack_from("<II", rd(e, 16), 4)
            if nid < hi:
                lst.append(hi); e = nl
            else:
                lst.append(lo); e = nr
        adj[nid] = lst
    blocks = []
    b = u32(%(BLOCKS)#x)
    while b and len(blocks) < 100000:
        w = u32(b + 0x28)
        ins = u32(b + 0x14)
        il = []
        while ins and len(il) < 100000:
            nops, = struct.unpack("<h", rd(ins + %(IRN)#x, 2))
            ops = []
            if 0 < nops < 64:
                oraw = rd(ins + %(IRO)#x, 0x16 * nops)
                for j in range(nops):
                    k, c, f, nd = struct.unpack_from("<BBhh", oraw, 0x16 * j)
                    ops.append([k, c, f, nd])
            il.append([u32(ins + 0xc), ops])
            ins = u32(ins)
        blocks.append([w, il])
        b = u32(b)
    json.dump(dict(cls=cls, adj=adj, blocks=blocks), open(os.path.join(OUT, "adj%%d.json" %% N[0]), "w"))
    N[0] += 1
def drive():
    gdb.execute("run")
    while gdb.selected_inferior().pid != 0 and (int(gdb.parse_and_eval("$pc")) & 0xffffffff) == %(TRAPPC)#x:
        dump()
        gdb.execute("continue")
"""


def gdb_script(tmp, cave, srcdir, P):
    S = sites(P)
    L = ["set pagination off", "set confirm off", "set debuginfod enabled off", "set $done = 0", "catch syscall openat",
         "commands 1", "silent", "if $done == 0", 'if $_streq((char*)$rsi, "%s")' % srcdir, "set $done = 1",
         "call (int)mprotect(%#x,0x10000000,3)" % LOGBASE]
    chk = " && ".join("*(unsigned char*)%#x == %#x" % (a + i, b) for a, (_, _, hx, _) in S.items() if hx
                      for i, b in enumerate(bytes.fromhex(hx)))
    L.append("if %s" % chk)
    L += ["set {unsigned char}%#x = %#x" % (P["CAVE"] + i, c) for i, c in enumerate(cave)]
    for a, (off, kind, _, plen) in S.items():
        rel = P["CAVE"] + off - (a + 5)
        op = 0xE8 if kind == "call" else 0xE9
        enc = bytes([op]) + struct.pack("<i", rel) + b"\x90" * (plen - 5)
        L += ["set {unsigned char}%#x = %#x" % (a + i, b) for i, b in enumerate(enc)]
    L += ["set {int}%#x = %#x" % (P["LOGP"], LOGBASE), "set {int}%#x = 0" % P["FLAG"], 'printf "PATCHED\\n"', "else", 'printf "UNSUPPORTED-COMPILER\\n"',
          "end", "end", "end", "continue", "end", "catch syscall exit_group", "python drive()", "set $end = *(int*)%#x" % P["LOGP"],
          "if $end > %#x" % LOGBASE, "dump binary memory %s/log.bin %#x $end" % (tmp, LOGBASE), "end"]
    path = os.path.join(tmp, "run.gdb")
    helper = os.path.join(tmp, "adj.py")
    open(helper, "w").write(ADJ_HELPER % dict(P, TRAPPC=P["CAVE"] + 0x181))
    L.insert(1, "source %s" % helper)
    open(path, "w").write("\n".join(L) + "\n")
    return path


def node(b):
    nxt, l, r, cost = struct.unpack_from("<IIII", b, 0)
    nid, color, flags, deg, w18 = struct.unpack_from("<hhHhH", b, 16)
    return dict(id=nid, cost=cost, color=color, flags=flags, deg=deg)


def parse(path):
    """Log records -> list of colouring passes (dicts: init, snap, final, push), in compile order."""
    d = open(path, "rb").read()
    i, passes, cur = 0, [], None
    while i < len(d):
        t, = struct.unpack_from("<I", d, i)
        if t in (1, 2, 3):
            n = node(d[i + 8:i + 38])
            n["t"] = t
            cur["push"].append(n)
            i += 48
        elif t in (4, 5, 6):
            cls, cnt = struct.unpack_from("<ii", d, i + 4)
            nodes = [node(d[i + 12 + k * 30:i + 42 + k * 30]) for k in range(cnt)]
            if t == 5:
                cur = dict(cls=cls, init=nodes, snap=None, final=None, push=[])
                passes.append(cur)
            else:
                cur["snap" if t == 6 else "final"] = nodes
            i += 12 + cnt * 30
        else:
            raise SystemExit("bad log record %d at %d" % (t, i))
    return passes


def isolate_case(text, keep):
    """Empty every FIGHTCALC sub-command except `keep` (cases of the `switch (sp494)` block)."""
    lines = text.split("\n")
    start = next(i for i, l in enumerate(lines) if re.match(r"^\s*switch \(sp494\) \{", l))
    depth, i, labels = 0, start, []
    end = None
    while i < len(lines):
        code = lines[i]
        if depth == 1:
            m = re.match(r"^\s*case (\d+):", code)
            if m:
                labels.append((i, int(m.group(1))))
        depth += code.count("{") - code.count("}")
        if depth == 0:
            end = i
            break
        i += 1
    out = lines[:start + 1]
    bounds = [l for l, _ in labels] + [end]
    for k, (li, cn) in enumerate(labels):
        out += lines[bounds[k]:bounds[k + 1]] if cn == keep else [lines[li], "            break;"]
    return "\n".join(out + lines[end:])


def trace(source, flags="-O3,p -Iinclude", compiler=None, text=None, adj_dir=None, min_nodes=1, timeout=900):
    """Compile `source` (path; or `text` written to a scratch file named like it) with the patched `compiler` (default the
    dispatcher's pinned build) and return the colouring passes in compile order, each a dict
    {cls, init, snap, final, push, adj, blocks}: init = nodes before simplify, snap = nodes at the first spill pick (carries costs),
    final = nodes after select (carries colours), push = push order, adj = {node: [neighbours]}, blocks = the IR."""
    import json
    compiler = os.path.abspath(compiler or MWCC)
    P = profile_for(compiler)
    tmp = tempfile.mkdtemp(prefix="regalloc-")
    try:
        if text is not None:
            srcdir = os.path.join(tmp, "src")
            os.mkdir(srcdir)
            src = os.path.join(srcdir, os.path.basename(source))
            open(src, "w").write(text)
        else:
            src = os.path.abspath(source)
            srcdir = os.path.dirname(src)
        adjdir = adj_dir or os.path.join(tmp, "adj")
        os.makedirs(adjdir, exist_ok=True)
        cave = build_cave(tmp, P)
        # the debugger arms the patch when the compiler first opens the directory of its output file (-o), so that directory is
        # private to this run
        objdir = os.path.join(tmp, "obj")
        os.mkdir(objdir)
        script = gdb_script(tmp, cave, objdir, P)
        env = dict(os.environ, MWCIncludes=srcdir, REGALLOC_ADJ_DIR=os.path.abspath(adjdir), REGALLOC_MIN_NODES=str(min_nodes))
        obj = os.path.join(objdir, "t.o")
        r = subprocess.run(["gdb", "-q", "-batch", "-x", script, "--args", WIBO, compiler, "-c", *flags.split(), src, "-o", obj],
                           cwd=ROOT, env=env, capture_output=True, text=True, timeout=timeout)
        if "UNSUPPORTED-COMPILER" in r.stdout:
            raise SystemExit("the compiler image does not match the pinned build; no trace taken")
        if "PATCHED" not in r.stdout or not os.path.exists(os.path.join(tmp, "log.bin")):
            raise SystemExit("no trace taken (is gdb allowed to trace the loader?)\n" + r.stdout[-600:] + r.stderr[-600:])
        passes = parse(os.path.join(tmp, "log.bin"))
        passes = [p for p in passes if len(p["init"]) >= min_nodes]
        for k, p in enumerate(passes):
            f = os.path.join(adjdir, "adj%d.json" % k)
            if os.path.exists(f):
                g = json.load(open(f))
                p["adj"] = {int(a): b for a, b in g["adj"].items()}
                p["blocks"] = g["blocks"]
        keep_obj = None
        if os.path.exists(obj):
            keep_obj = open(obj, "rb").read()
        return passes, keep_obj
    finally:
        shutil.rmtree(tmp, ignore_errors=True)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("source")
    ap.add_argument("--only-case", type=int)
    ap.add_argument("--tail", type=int, default=12)
    ap.add_argument("--flags", default="-O3,p -Iinclude")
    ap.add_argument("--compiler", default=MWCC, help="compiler executable (default: the dispatcher's pinned build)")
    ap.add_argument("--round", type=int, default=-1, help="which big colouring pass to report (default -1, the last one)")
    ap.add_argument("--min-nodes", type=int, default=500, help="ignore passes with fewer nodes (default 500; use 1 for small functions)")
    ap.add_argument("--adj", help="directory: dump the interference graph of every pass (adjN.json, with the IR)")
    ap.add_argument("--ctx", help="file: dump the node table of the reported pass (json)")
    ap.add_argument("--ids", help="comma separated node ids: print cost, degree and colour of each")
    a = ap.parse_args()
    text = open(a.source).read()
    if a.only_case is not None:
        text = isolate_case(text, a.only_case)
    big, _obj = trace(a.source, a.flags, a.compiler, text=text if a.only_case is not None else None, adj_dir=a.adj,
                      min_nodes=a.min_nodes)
    if not big:
        raise SystemExit("no colouring pass with at least %d nodes in the log" % a.min_nodes)
    print("colouring passes: %d; reporting pass %d" % (len(big), a.round % len(big)))
    g = big[a.round]
    if a.ctx:
        import json
        json.dump(dict(init=g["init"], snap=g["snap"], final=g["final"], push=g["push"]), open(a.ctx, "w"))
    fin = {n["id"]: n for n in g["final"]}
    snap = {n["id"]: n for n in (g["snap"] or [])}
    virt = [n for n in g["init"] if n["id"] >= 32]
    this = max(virt, key=lambda n: n["deg"])
    pos = {p["id"]: k for k, p in enumerate(g["push"])}
    color = lambda i: REGS.get(fin[i]["color"], "spill" if fin[i]["color"] == -1 else str(fin[i]["color"]))
    kinds = collections.Counter(p["t"] for p in g["push"])
    print("nodes %d  pushed %d (scan %d, spill picks %d, rescan %d)" % (len(g["init"]), len(g["push"]), kinds[1], kinds[2], kinds[3]))
    print("receiver: node %d, degree %d, colour %s, pushed %d of %d" % (this["id"], this["deg"], color(this["id"]),
                                                                       pos[this["id"]] + 1, len(g["push"])))
    if a.ids:
        for i in map(int, a.ids.split(",")):
            n0 = next(n for n in g["init"] if n["id"] == i)
            print("node %d: initial degree %d, cost %s, colour %s, pushed %s" % (i, n0["deg"], snap.get(i, {}).get("cost"), color(i), pos.get(i, -1) + 1))
    print("last %d pushes (colouring order is the reverse: the last row is coloured first):" % a.tail)
    print("   id  kind    cost  deg@push  colour")
    for p in g["push"][-a.tail:]:
        print("%5d  %-6s %6s  %8d  %s" % (p["id"], {1: "scan", 2: "PICK", 3: "rescan"}[p["t"]], snap.get(p["id"], {}).get("cost", "-"),
                                          p["deg"], color(p["id"])))


if __name__ == "__main__":
    main()
