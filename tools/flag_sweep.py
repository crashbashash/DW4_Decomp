#!/usr/bin/env python3
"""flag_sweep.py — retry every near-miss draft under other MWCC optimisation flags.

The Action2 block needed a per-unit `-O3,p` override (finding #646); a function whose
draft is otherwise complete can match under a different `,p`/`-O` setting. This tries
a small flag set per draft and banks the first byte-identical result.
"""
import json, os, re, sys
from multiprocessing import Pool

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT + "/tools")
import verify as vfy  # noqa: E402
SYMBOLS = ROOT + "/config/symbols.txt"
ELF = os.environ.get("DW4_ELF", ROOT + "/orig/SLUS-20836/SLUS_208.36")
FLAGS = ["-O3,p", "-O4,p", "-O2,p", "-O3,s", "-O3,p,s", "-O4", "-O2"]


def do_one(row):
    name = row["name"]
    src = os.path.join(ROOT, "build", "m2c", name + ".c")
    if not os.path.exists(src):
        src = os.path.join(ROOT, "build", "m2c", name + ".cpp")
    if not os.path.exists(src):
        return dict(row, flag=None)
    for fl in FLAGS:
        ok, rep = vfy.verify_one(row["va"], src, flags=fl, symbols=SYMBOLS, elf=ELF)
        if ok:
            ext = os.path.splitext(src)[1]
            dest = os.path.join(ROOT, "src", "unmatched", name + ext)
            body = open(src).read()
            if not os.path.exists(dest):
                open(dest, "w").write(
                    "/* 0x%08x — %s. m2c draft, matches under flags '%s'\n"
                    " * (tools/flag_sweep.py + tools/verify.py). */\n" % (row["va"], name, fl)
                    + body)
            return dict(row, flag=fl, status="banked")
    return dict(row, flag=None)


if __name__ == "__main__":
    rows = [json.loads(l) for l in open(ROOT + "/build/near_scan.jsonl")]
    todo = [r for r in rows if r["status"] in ("mismatch", "compile") and r.get("va")]
    print("flag-sweeping %d candidates" % len(todo), flush=True)
    res, nbank = [], 0
    with Pool(int(os.environ.get("SWEEP_WORKERS", "16"))) as pool:
        for i, r in enumerate(pool.imap_unordered(do_one, todo, chunksize=4)):
            res.append(r)
            if r.get("status") == "banked":
                nbank += 1
                print("  BANKED %-40s %s" % (r["name"], r["flag"]), flush=True)
            if (i + 1) % 200 == 0:
                print("  %d/%d" % (i + 1, len(todo)), flush=True)
    with open(ROOT + "/build/flag_sweep.jsonl", "w") as fh:
        for r in res:
            fh.write(json.dumps(r) + "\n")
    print("flag_sweep banked %d / %d" % (nbank, len(todo)))
