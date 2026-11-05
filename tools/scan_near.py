#!/usr/bin/env python3
"""scan_near.py — compile every unmatched build/m2c draft, record its instruction diff.

The committed worklists are stale (most rows have no draft left). The drafts in
build/m2c/ are the real candidate set; this scans them with the same oracle
(tools/verify.py) and writes build/near_scan.jsonl, one row per draft:
{name, va, size, status, ndiff, draft}. status in {match, compile, mismatch, nosym}.
ndiff counts differing instruction words (including a size mismatch in words).
"""
import glob, json, os, re, sys
from multiprocessing import Pool

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, os.path.join(ROOT, "tools"))
import verify as vfy  # noqa: E402

SYMBOLS = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
ELF = os.environ.get("DW4_ELF", os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))


def src_stems():
    s = set()
    for p in (glob.glob(ROOT + "/src/**/*.c", recursive=True)
              + glob.glob(ROOT + "/src/**/*.cpp", recursive=True)):
        s.add(os.path.splitext(os.path.basename(p))[0])
    return s


def work_items():
    banked = src_stems()
    seen, items = set(), []
    for p in sorted(glob.glob(ROOT + "/build/m2c/*.c")) + \
             sorted(glob.glob(ROOT + "/build/m2c/*.cpp")):
        stem = os.path.splitext(os.path.basename(p))[0]
        if stem in banked or stem in seen:
            continue
        seen.add(stem)
        items.append(stem)
    return items


def one(name):
    by_name, _ = vfy.load_symbols(SYMBOLS)
    if name not in by_name:
        return {"name": name, "status": "nosym"}
    va, size = by_name[name]
    draft = os.path.join(ROOT, "build", "m2c", name + ".c")
    if not os.path.exists(draft):
        draft = os.path.join(ROOT, "build", "m2c", name + ".cpp")
    if not os.path.exists(draft):
        return {"name": name, "va": va, "size": size, "status": "nodraft"}
    ok, rep = vfy.verify_one(va, draft, symbols=SYMBOLS, elf=ELF)
    base = {"name": name, "va": va, "size": size, "draft": draft}
    if ok:
        return dict(base, status="match", ndiff=0)
    if "compile failed" in rep:
        return dict(base, status="compile", ndiff=None,
                    msg=rep.splitlines()[0][:100])
    if "defines no symbol" in rep:
        return dict(base, status="nosymobj", ndiff=None)
    ndiff = sum(1 for ln in rep.splitlines() if re.match(r"\s+\[\s*\d+\]", ln))
    szm = re.search(r"size: retail (\d+), ours (\d+)", rep)
    extra = abs(int(szm.group(1)) - int(szm.group(2))) // 4 if szm else 0
    return dict(base, status="mismatch", ndiff=ndiff + extra)


if __name__ == "__main__":
    items = work_items()
    print("scanning %d unmatched drafts" % len(items), flush=True)
    outp = os.path.join(ROOT, "build", "near_scan.jsonl")
    with open(outp, "w") as out, Pool(16) as pool:
        for i, res in enumerate(pool.imap_unordered(one, items, chunksize=4)):
            out.write(json.dumps(res) + "\n")
            if (i + 1) % 250 == 0:
                out.flush()
                print("  %d/%d" % (i + 1, len(items)), flush=True)
    print("done ->", outp)
