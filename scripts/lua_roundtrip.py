#!/usr/bin/env python3
"""lua_roundtrip.py — recompile every `lua/` chunk with stock Lua 4.0.1 and compare it with retail.

Each decompiled chunk (scripts/lua_tree.py resolves pack entry + chunk to its file) is compiled
with `luac -s` (tools/download_tools.py builds it at local/lua-4.0.1/bin/luac) and compared,
function by function, with the original chunk in the script pack NDMW.AFS:

  exact             instruction words, string and number constants, parameter count, vararg
                    flag and stack size agree in the main function and every nested one
  same opcodes      constants and opcode sequence agree, some operands differ
  same count        instruction counts agree
  differs           anything else, including a different nesting of functions
  failed            luac rejects the text

The recompiled chunk is read with the host's own sizes from its header (a 64-bit luac writes
8-byte size_t and Instruction); the retail one has 4-byte fields.

    python3 scripts/lua_roundtrip.py                 # counts; non-zero when exact < baseline
    python3 scripts/lua_roundtrip.py --diff 179 25   # first differing function of one chunk
    python3 scripts/lua_roundtrip.py --update-baseline

The gate is the exact count against config/lua-roundtrip-baseline.json: a decompiler change
may not lower it. Record a raised count deliberately with --update-baseline. The pack defaults
to ../local/extracted/NDMW.AFS (override with DW4_NDMW or --afs), luac to the download path
(DW4_LUAC or --luac).
"""
import argparse
import collections
import difflib
import json
import os
import struct
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import lua_tree  # noqa: E402
from lua_decompile import parse_chunk  # noqa: E402
from lua_dump import disasm  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASELINE = os.path.join(ROOT, "config", "lua-roundtrip-baseline.json")
LEVELS = ["exact", "same opcodes", "same count", "differs", "failed"]


class HostChunk:
    """A luac output file, read with the sizes its header declares."""

    def __init__(self, data):
        if data[:4] != b"\x1bLua" or data[4] != 0x40:
            raise ValueError("not a Lua 4.0 chunk")
        self.data, self.sint, self.ssize, self.sins = data, data[6], data[7], data[8]
        self.pos = 13 + 8  # 13 header bytes, then the test number (a double)

    def num(self, size):
        value = int.from_bytes(self.data[self.pos:self.pos + size], "little")
        self.pos += size
        return value

    def string(self):
        n = self.num(self.ssize)
        raw = self.data[self.pos:self.pos + n]
        self.pos += n
        return raw.rstrip(b"\0").decode("latin1") if n else None

    def function(self):
        fn = {"source": self.string()}
        self.num(self.sint)  # line defined
        fn["numparams"] = self.num(self.sint)
        fn["is_vararg"] = self.num(1)
        fn["maxstack"] = self.num(self.sint)
        for _ in range(self.num(self.sint)):  # locals (none with -s)
            self.string(); self.num(self.sint); self.num(self.sint)
        fn["locals"] = []
        for _ in range(self.num(self.sint)):  # line info
            self.num(self.sint)
        fn["kstr"] = [self.string() for _ in range(self.num(self.sint))]
        fn["knum"] = []
        for _ in range(self.num(self.sint)):
            fn["knum"].append(struct.unpack_from("<d", self.data, self.pos)[0])
            self.pos += 8
        fn["kproto"] = [self.function() for _ in range(self.num(self.sint))]
        fn["code"] = [self.num(self.sins) & 0xFFFFFFFF for _ in range(self.num(self.sint))]
        return fn


def level_of(a, b):
    """0 exact .. 3 differs for one function, ignoring nested ones."""
    same_k = a["kstr"] == b["kstr"] and a["knum"] == b["knum"]
    if same_k and a["code"] == b["code"] and a["numparams"] == b["numparams"] \
            and a["is_vararg"] == b["is_vararg"] and a["maxstack"] == b["maxstack"]:
        return 0
    if same_k and [w & 63 for w in a["code"]] == [w & 63 for w in b["code"]]:
        return 1
    return 2 if len(a["code"]) == len(b["code"]) else 3


def compare(a, b):
    """Worst level over a function and its nested functions."""
    if len(a["kproto"]) != len(b["kproto"]):
        return 3
    return max([level_of(a, b)] + [compare(x, y) for x, y in zip(a["kproto"], b["kproto"])])


def retail_chunks(afs):
    """Yield (entry, chunk index, parsed function) for every chunk of the pack, in pack order."""
    data = open(afs, "rb").read()
    for entry in range(struct.unpack_from("<I", data, 4)[0]):
        off, size = struct.unpack_from("<II", data, 8 + entry * 8)
        blob = data[off:off + size]
        cursor = index = 0
        while (pos := blob.find(b"\x1bLua", cursor)) >= 0:
            fn, used = parse_chunk(blob, pos)
            yield entry, index, fn
            cursor = pos + used
            index += 1


def recompile(luac, path, out):
    """The recompiled function, or the luac error text."""
    res = subprocess.run([luac, "-s", "-o", out, path], capture_output=True, text=True)
    if res.returncode:
        return None, (res.stderr.strip().splitlines() or ["luac failed"])[0]
    with open(out, "rb") as fh:
        return HostChunk(fh.read()).function(), None


def first_difference(a, b, path=()):
    if level_of(a, b) or len(a["kproto"]) != len(b["kproto"]):
        return a, b, path
    for i, (x, y) in enumerate(zip(a["kproto"], b["kproto"])):
        found = first_difference(x, y, path + (i,))
        if found:
            return found
    return None


def show_diff(args, out):
    entry, chunk = args.diff
    orig = next(fn for e, c, fn in retail_chunks(args.afs) if (e, c) == (entry, chunk))
    path = lua_tree.chunk_path(entry, chunk)
    new, error = recompile(args.luac, path, out)
    print(os.path.relpath(path, ROOT))
    if error:
        print("luac:", error)
        return 1
    found = first_difference(orig, new)
    if not found:
        print("exact")
        return 0
    a, b, where = found
    print(f"function {list(where)}: maxstack {a['maxstack']} / {b['maxstack']}, "
          f"nested {len(a['kproto'])} / {len(b['kproto'])}, constants "
          f"{'agree' if a['kstr'] == b['kstr'] and a['knum'] == b['knum'] else 'differ'}")
    lines = lambda fn: [l.split(None, 1)[1] for l in disasm({**fn, "kproto": []}, None).splitlines() if l.strip()]
    for line in difflib.unified_diff(lines(a), lines(b), "retail", "recompiled", n=3, lineterm=""):
        print(line)
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--afs", default=os.environ.get("DW4_NDMW", os.path.join(ROOT, "..", "local", "extracted", "NDMW.AFS")))
    ap.add_argument("--luac", default=os.environ.get("DW4_LUAC", os.path.join(ROOT, "local", "lua-4.0.1", "bin", "luac")))
    ap.add_argument("--diff", nargs=2, type=int, metavar=("ENTRY", "CHUNK"))
    ap.add_argument("--update-baseline", action="store_true")
    args = ap.parse_args(argv)
    for what, path in (("script pack", args.afs), ("luac", args.luac)):
        if not os.path.exists(path):
            sys.exit(f"{what} not found: {path} (tools/download_tools.py builds luac)")
    out = os.path.join(tempfile.mkdtemp(), "chunk.luac")
    if args.diff:
        return show_diff(args, out)

    counts = collections.Counter()
    for entry, chunk, orig in retail_chunks(args.afs):
        new, error = recompile(args.luac, lua_tree.chunk_path(entry, chunk), out)
        counts[4 if error else compare(orig, new)] += 1
    total = sum(counts.values())
    for i, name in enumerate(LEVELS):
        print(f"{name}: {counts[i]}")
    print(f"chunks: {total}")
    exact = counts[0]
    if args.update_baseline:
        with open(BASELINE, "w", encoding="utf-8") as fh:
            json.dump({"exact": exact, "chunks": total,
                       "note": "Exact recompiles of lua/ (scripts/lua_roundtrip.py). Record deliberately "
                               "with --update-baseline."}, fh, indent=1, sort_keys=True)
            fh.write("\n")
        print(f"baseline recorded: {exact}")
        return 0
    baseline = json.load(open(BASELINE, encoding="utf-8"))["exact"]
    if exact < baseline:
        print(f"FAIL: {exact} exact, below the baseline {baseline}", file=sys.stderr)
        return 1
    print(f"OK: {exact} exact (baseline {baseline})")
    return 0


if __name__ == "__main__":
    sys.exit(main())
