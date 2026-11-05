#!/usr/bin/env python3
"""regalloc_graph.py SOURCE.cpp [--only-case N] [--out graph.json] : dump the compiler's interference graph and IR.

Same harness as regalloc_trace2.py (patched compiler image, gdb, wibo).  A breakpoint on the entry of simplify() (0x4c3f30)
walks the edge lists that hang off every node (record layout read from the pinned compiler: node +0x10 id, +0x16 degree,
+0x1a first edge; edge +0x0c / +0x0e the two endpoint ids, +0x04 / +0x08 next edge for the low / high endpoint) and the IR
(block list at 0x5b412c: +0x28 weight, +0x14 first instruction; instruction +0x0c opcode, +0x2a operand count, operands of
0x16 bytes at +0x3c: kind, class, flags, node; flag bit 1 = use, bit 2 = def) and writes, per colouring pass,

    <out>.<nodes>          nodes (id, degree, flags) and edges
    <out>.blocks.<nodes>   blocks: [weight, [[opcode, n_operands, [[kind, class, flags, node], ...]], ...]]
    <out>.log              push order, costs (at the first pick) and final colours of the biggest pass

The GPR pass is the biggest one; with spills the compiler colours twice and the second pass (more nodes) is the real one.
regalloc_sim.py replays the push order and the colours from these files exactly (checked on the whole function), so a
hypothetical change to the graph or to a cost can be tried in milliseconds.
"""
import argparse, json, os, shutil, subprocess, sys, tempfile
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import regalloc_trace2 as rt

PY = r'''
import gdb, json
OUT = %(out)r
def _rd(a, n):
    return bytes(gdb.selected_inferior().read_memory(a, n))
def _u32(a): return int.from_bytes(_rd(a, 4), "little")
def _s16(a): return int.from_bytes(_rd(a, 2), "little", signed=True)
class _B(gdb.Breakpoint):
    def stop(self):
        cls = int.from_bytes(_rd(0x5b5e1f, 1), "little", signed=True)
        cnt = _u32(0x5b4610 + cls * 4)
        base = _u32(0x5b4154)
        nodes, edges = [], []
        for i in range(cnt):
            a = base + 30 * i
            nid = _s16(a + 0x10); deg = _s16(a + 0x16); flags = _s16(a + 0x14)
            nodes.append(dict(id=nid, deg=deg, flags=flags))
            e = _u32(a + 0x1a)
            guard = 0
            while e and guard < 100000:
                guard += 1
                lo = _s16(e + 0xc); hi = _s16(e + 0xe)
                if nid < hi:
                    edges.append([nid, hi]); e = _u32(e + 4)
                else:
                    e = _u32(e + 8)
        blocks = []
        b = _u32(0x5b412c)
        guard = 0
        while b and guard < 200000:
            guard += 1
            w = _u32(b + 0x28)
            ins = _u32(b + 0x14)
            k = 0
            first = []
            while ins and k < 100000:
                nops = _s16(ins + 0x2a)
                first.append([_u32(ins + 0xc), nops, [[_rd(ins + 0x3c + 0x16 * j, 1)[0], _rd(ins + 0x3c + 0x16 * j + 1, 1)[0], _s16(ins + 0x3c + 0x16 * j + 2), _s16(ins + 0x3c + 0x16 * j + 4)] for j in range(max(nops, 0))]])
                ins = _u32(ins)
                k += 1
            blocks.append([w, first])
            b = _u32(b)
        with open(OUT + ".blocks.%%d" %% cnt, "w") as f:
            json.dump(blocks, f)
        with open(OUT + ".%%d" %% cnt, "w") as f:
            json.dump(dict(cls=cls, nodes=nodes, edges=edges), f)
        return False
def install():
    _B("*0x4c3f30")
'''

def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("source"); ap.add_argument("--only-case", type=int); ap.add_argument("--out", default="regalloc-graph.json")
    a = ap.parse_args()
    text = open(a.source).read()
    if a.only_case is not None:
        text = rt.isolate_case(text, a.only_case)
    tmp = tempfile.mkdtemp(prefix="regalloc-")
    try:
        srcdir = os.path.join(tmp, "src"); os.mkdir(srcdir)
        src = os.path.join(srcdir, "t.cpp"); open(src, "w").write(text)
        cave = rt.build_cave(tmp)
        script = rt.gdb_script(tmp, cave, srcdir)
        pyf = os.path.join(tmp, "g.py"); open(pyf, "w").write(PY % dict(out=a.out))
        s = open(script).read().replace('printf "PATCHED\\n"', 'source %s\npython install()\nprintf "PATCHED\\n"' % pyf)
        open(script, "w").write(s)
        env = dict(os.environ, MWCIncludes=srcdir)
        r = subprocess.run(["gdb", "-q", "-batch", "-x", script, "--args", rt.WIBO, rt.MWCC, "-c", "-O3,p", "-Iinclude", src, "-o",
                            os.path.join(srcdir, "t.o")], cwd=rt.ROOT, env=env, capture_output=True, text=True, timeout=900)
        lg = os.path.join(tmp, "log.bin")
        if os.path.exists(lg):
            g = rt.parse(lg)
            extra = dict(push=[[p["id"], p["t"], p["deg"]] for p in g["push"]], cost={n["id"]: n["cost"] for n in (g["snap"] or [])},
                         color={n["id"]: n["color"] for n in (g["final"] or [])})
            json.dump(extra, open(a.out + ".log", "w"))
        else:
            print(r.stdout[-300:], r.stderr[-300:])
    finally:
        shutil.rmtree(tmp, ignore_errors=True)

main()
