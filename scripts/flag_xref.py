#!/usr/bin/env python3
"""
flag_xref.py — build a cross-reference of every flag used in the decompiled
Lua, so the flag/story-progression system can be read as a map.

Extracts:
  * be:FLGset(N, V)      — runtime flag write (ordinary script values 0/1)
  * be:FLGisOn(N)        — runtime flag read
  * be:SYSctlFlagFolder  — persistent (memory-card) flag folder IS/SET/CLR
  * be:COUNTERset/get    — counters (act/chapter, quest totals, timers)

Output (written to OUTDIR; default docs/systems/flags):
  * flag-xref.tsv  — one row per operation (grep / spreadsheet friendly); the
                     canonical form of the mapping (schema: docs/systems/flags/README.md)

Usage:
  python3 flag_xref.py lua .
"""
import os
import re
import sys
from collections import defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_lua_tree import ENTRY_MAP  # noqa: E402
import lua_tree  # noqa: E402

SRC = sys.argv[1] if len(sys.argv) > 1 else "lua"
OUTDIR = sys.argv[2] if len(sys.argv) > 2 else "docs/systems/flags"

# entry -> (stage, region, desc)
ENTRY_INFO = {e: (stage, region, desc) for (e, region, stage, desc) in ENTRY_MAP}
REGION_BY_ENTRY = {e: region for (e, region, stage, desc) in ENTRY_MAP}


def short_line(s, maxlen=90):
    s = " ".join(s.split())
    return s if len(s) <= maxlen else s[: maxlen - 1] + "…"


# ---------------------------------------------------------------------------
# known flag meanings (from manual analysis of the lobby/act chunks)
# ---------------------------------------------------------------------------
KNOWN = {
    86:   "story gate (checked with level-gate 908 in lobby)",
    98:   "story gate (Digilf intro/quest line done)",
    371:  "quest state (checked in lobby dialogue)",
    376:  "quest flag (set by Leomon in lobby-quests)",
    377:  "story flag (set in act-902 fail sequence + lobby)",
    378:  "quest flag (Leomon lobby-quests)",
    379:  "quest flag (Leomon lobby-quests)",
    381:  "story flag (set in act-906 fail sequence)",
    385:  "story flag (set in act-902 fail sequence)",
    389:  "story flag (set in act-906 fail sequence)",
    409:  "global story/act marker (set with COUNTER 902/906 fail sequences)",
    424:  "story flag (set in act fail sequences)",
    508:  "stage-intro tutorial gate (checked in act-start chunk)",
    571:  "story flag (set with 409 in fail sequences)",
    908:  "level gate: player level >= 16",
    909:  "level gate: player level >= 46",
    910:  "level gate: player level >= 76",
}


def arg_kind(a):
    a = a.strip()
    if re.fullmatch(r"-?\d+", a):
        return ("lit", int(a))
    m = re.fullmatch(r"(?:(\d+)\s*\+\s*)?be:MDLgetRamNo\(\)\s*\+\s*(\d+)", a)
    if m:
        # ramNo + N  (or C + ramNo + N); record the additive constant
        return ("ramno", int(m.group(2)))
    m = re.fullmatch(r"be:MDLgetRamNo\(\)\s*\+\s*(\d+)", a)
    if m:
        return ("ramno", int(m.group(1)))
    return ("expr", a)


def main():
    ops = []  # dicts
    for entry in sorted(ENTRY_INFO):
        for index, path in lua_tree.chunks(entry, SRC):
            cname = "chunk_%04d.lua" % index    # the chunk id the tables cite
            with open(path, encoding="utf-8") as fh:
                lines = fh.read().splitlines()
            for lineno, line in enumerate(lines, 1):
                # FLGset
                for m in re.finditer(r'be:FLGset\(\s*([^,]+?)\s*,\s*([^)]+?)\s*\)', line):
                    kind, val = arg_kind(m.group(1))
                    ops.append(dict(op="set", flag=val if kind == "lit" else m.group(1).strip(),
                                    kind=kind, value=m.group(2).strip(),
                                    entry=entry, chunk=cname, line=lineno,
                                    text=short_line(line)))
                # FLGisOn
                for m in re.finditer(r'be:FLGisOn\(\s*([^)]+?)\s*\)', line):
                    kind, val = arg_kind(m.group(1))
                    ops.append(dict(op="chk", flag=val if kind == "lit" else m.group(1).strip(),
                                    kind=kind, value="", entry=entry, chunk=cname,
                                    line=lineno, text=short_line(line)))
                # FlagFolder (persistent)
                for m in re.finditer(r'be:SYSctlFlagFolder\(\s*"([A-Z]+)"\s*,\s*([^)]+?)\s*\)', line):
                    ops.append(dict(op=f"folder:{m.group(1)}", flag=m.group(2).strip(),
                                    kind="folder", value="", entry=entry, chunk=cname,
                                    line=lineno, text=short_line(line)))
                # Counters
                for m in re.finditer(r'be:COUNTERset\(\s*([^,]+?)\s*,\s*([^)]+?)\s*\)', line):
                    ops.append(dict(op="ctr:set", flag=f"COUNTER {m.group(1).strip()}",
                                    kind="counter", value=m.group(2).strip(),
                                    entry=entry, chunk=cname, line=lineno,
                                    text=short_line(line)))
                for m in re.finditer(r'be:COUNTERget\(\s*([^)]+?)\s*\)', line):
                    ops.append(dict(op="ctr:get", flag=f"COUNTER {m.group(1).strip()}",
                                    kind="counter", value="", entry=entry, chunk=cname,
                                    line=lineno, text=short_line(line)))

    # ---- TSV --------------------------------------------------------------
    tsv_path = os.path.join(OUTDIR, "flag-xref.tsv")
    with open(tsv_path, "w", encoding="utf-8") as fh:
        fh.write("op\tflag\tkind\tvalue\tentry\tstage\tchunk\tline\ttext\n")
        for o in ops:
            stage = ENTRY_INFO[o["entry"]][0]
            fh.write("\t".join([
                o["op"], str(o["flag"]), o["kind"], o["value"],
                str(o["entry"]), stage, o["chunk"], str(o["line"]), o["text"],
            ]) + "\n")

    by_flag = defaultdict(list)
    for o in ops:
        by_flag[o["flag"]].append(o)

    print(f"ops: {len(ops)}  unique flags: {len(by_flag)}")
    print(f"wrote {tsv_path}")


if __name__ == "__main__":
    main()
