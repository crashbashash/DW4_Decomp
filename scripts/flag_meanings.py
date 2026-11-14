#!/usr/bin/env python3
"""
flag_meanings.py — attach a meaning to every flag in the decomp, prioritizing
story/progression flags (curated from manual analysis) and falling back to
heuristics (device name for stage-local flags, cross-region for globals).

Output:
  * flag-meanings.md   — curated story flags organized by category + a
                         full per-flag table with confidence.
  * flag-meanings.tsv  — one row per flag: id, meaning, confidence, evidence.

Usage:
  python3 flag_meanings.py lua .
"""
import os
import re
import sys
from collections import defaultdict, Counter

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_lua_tree import ENTRY_MAP  # noqa: E402
import lua_tree  # noqa: E402
from flag_xref import arg_kind  # noqa: E402

SRC = sys.argv[1] if len(sys.argv) > 1 else "lua"
OUTDIR = sys.argv[2] if len(sys.argv) > 2 else "docs/systems/flags"

ENTRY_INFO = {e: (stage, region, desc) for (e, region, stage, desc) in ENTRY_MAP}
REGION_BY_ENTRY = {e: region for (e, region, stage, desc) in ENTRY_MAP}


# ---------------------------------------------------------------------------
# Curated meanings (confidence: high/medium)
# ---------------------------------------------------------------------------
CURATED = {
    # ---- intro / chapter steps (lobby cutscene e0816) ---------------------
    1:  ("intro step 0 (game start)", "high", "set in lobby cutscene e0816"),
    2:  ("intro step 1", "high", "set in e0816; checked by Leomon (e0820)"),
    3:  ("intro step 2", "high", "set in e0816"),
    4:  ("intro step 3", "high", "set in e0816"),
    5:  ("intro step 4", "high", "set in e0816"),
    6:  ("main story underway (intro done)", "high", "set e0816/e0820; checked in city hub e0709"),
    22: ("intro sub-step", "medium", "set in e0816"),
    20: ("intro flag (checked with 2 in e0820)", "medium", "set e0603/e0786"),
    85: ("lobby story beat", "medium", "set in e0816"),

    # ---- boss defeat / story milestones -----------------------------------
    67: ("Boss 1 (Apocalymon) defeated", "high", "set=1 in boss stage e0730"),
    68: ("Boss 2 (BelialVamdemon) defeated", "high", "set=1 in e0737"),
    69: ("Boss 3 (Lucemon) defeated", "high", "set=1 in e0744"),
    70: ("Final boss (Devimon) defeated", "high", "set=1 in e0765"),
    86: ("Final boss / main story cleared", "high", "set=1 in e0765; checked with 6 in e0709"),
    83: ("Dungeon 4 (LordKnightmon) cleared", "high", "set=1 in e0425 (dng412b4)"),
    600: ("Boss 1 story scene done", "high", "set=1 in e0730"),
    603: ("Boss 2 story scene done", "high", "set=1 in e0737"),
    607: ("Boss 3 story scene done", "high", "set=1 in e0744"),
    610: ("Final boss story scene done", "high", "set=1 in e0765"),
    609: ("Dungeon 4 story scene done", "high", "set=1 in e0425"),

    # ---- quest chain (Digilfmon quest giver, e0820) -----------------------
    362: ("city intro battle (Infermon/Megadramon) done", "high", "set=1 in e0709"),
    376: ("quest 1 done", "high", "set=1 in e0820"),
    377: ("quest 2 done", "high", "set=1 in e0820"),
    378: ("quest 3 done", "high", "set=1 in e0820"),
    379: ("quest 4 done", "high", "set=1 in e0820"),
    380: ("quest 5 done", "high", "set=1 in e0820"),
    381: ("quest chain complete (final gate)", "high", "checked in e0709"),
    384: ("quest 1 sub-step", "medium", "paired with 376 in e0820"),
    385: ("quest 2 sub-step", "medium", "paired with 377 in e0820"),
    386: ("quest 3 sub-step", "medium", "paired with 378 in e0820"),
    387: ("quest 4 sub-step", "medium", "paired with 379 in e0820"),
    388: ("quest 5 sub-step", "medium", "paired with 380 in e0820"),
    389: ("quest final sub-step", "medium", "paired with 381 in e0820"),

    # ---- quest attempt state (reset on fail, set 0 in 902/906 chunks) ----
    409: ("quest/act in-progress marker (1=done, 0=reset)", "high", "reset in 902/906 fail chunks"),
    571: ("quest/act in-progress marker", "high", "reset with 409"),
    424: ("quest/act in-progress marker", "high", "reset with 409"),

    # ---- quest board (e0824) ----------------------------------------------
    931: ("quest board slot 1 availability", "medium", "e0824"),
    932: ("quest board slot 2 availability", "medium", "e0824"),
    933: ("quest board slot 3 availability", "medium", "e0824"),
    934: ("quest board slot 4 availability", "medium", "e0824"),
    572: ("quest board chain progress 1", "medium", "e0820/e0824"),
    573: ("quest board chain progress 2", "medium", "e0820/e0824"),
    574: ("quest board chain progress 3", "medium", "e0820/e0824"),
    575: ("quest board chain progress 4", "medium", "e0820/e0824"),
    576: ("quest board chain progress 5", "medium", "e0824"),
    415: ("quest board completion sub-flag", "medium", "e0824"),
    416: ("quest board completion sub-flag", "medium", "e0824"),
    417: ("quest board completion sub-flag", "medium", "e0824"),
    418: ("quest board completion sub-flag", "medium", "e0824"),
    419: ("quest board completion sub-flag", "medium", "e0824"),
    420: ("quest board completion sub-flag", "medium", "e0824"),
    430: ("quest board completion sub-flag", "medium", "e0824"),
    469: ("quest board reward 1", "medium", "e0824"),
    471: ("quest board reward 2", "medium", "e0824"),
    473: ("quest board reward 3", "medium", "e0824"),

    # ---- city hub (e0709) -------------------------------------------------
    71:  ("city gate/lever state 1", "medium", "e0709; also set on quest completion"),
    72:  ("city gate/lever state 2", "medium", "e0709"),
    905: ("city entryway state", "medium", "set in e0709 from persistent folder 8/9"),

    # ---- shops / NPC / level gates (e0828) --------------------------------
    908: ("level gate: player Lv >= 16", "high", "e0828"),
    909: ("level gate: player Lv >= 46", "high", "e0828"),
    910: ("level gate: player Lv >= 76", "high", "e0828"),
    98:  ("valley river story event done", "high", "set in e0628; checked in shops e0828"),
    371: ("shop quest state", "medium", "checked in e0828"),
    64:  ("shop counter interaction", "medium", "e0828"),
    375: ("shop story event", "medium", "e0828"),
    392: ("shop event sub-flag", "medium", "e0828"),
    393: ("shop event sub-flag", "medium", "e0828"),
    594: ("shop story flag", "medium", "e0828"),
    27:  ("shop NPC dialogue (bank)", "medium", "e0828"),
    28:  ("shop NPC dialogue (disk)", "medium", "e0828"),
    30:  ("shop NPC dialogue", "medium", "e0828"),
    31:  ("shop NPC dialogue", "medium", "e0828"),
    32:  ("shop NPC dialogue", "medium", "e0828"),
    35:  ("shop NPC dialogue", "medium", "e0828"),

    # ---- valley river events (e0628) --------------------------------------
    89:  ("valley river event", "medium", "e0628"),
    90:  ("valley river event", "medium", "e0628"),
    91:  ("valley river event", "medium", "e0628"),
    92:  ("valley river event", "medium", "e0628"),
    93:  ("valley river event", "medium", "e0628"),
    94:  ("valley river event", "medium", "e0628"),
    95:  ("valley river event", "medium", "e0628"),
    96:  ("valley river event", "medium", "e0628"),
    97:  ("valley river event", "medium", "e0628"),

    # ---- dungeon checkpoints ---------------------------------------------
    292: ("dungeon checkpoint (block 1-2)", "medium", "set at dungeon finales"),
    293: ("dungeon checkpoint (block 2-3)", "medium", "set at dungeon finales"),
    294: ("dungeon checkpoint (block 3-4)", "medium", "set at dungeon finales"),

    # ---- one-time stage-intro tutorial gate -------------------------------
    508: ("stage-intro tutorial gate", "high", "set in every stage; checked in act-start chunk"),

    # ---- persistent flag folder (separate namespace 0-11) -----------------
    # keyed as "folder:N"
    "folder:0":  ("persistent story flag 0", "medium", "SYSctlFlagFolder"),
    "folder:1":  ("persistent story flag 1", "medium", "SYSctlFlagFolder"),
    "folder:2":  ("persistent story flag 2", "medium", "SYSctlFlagFolder"),
    "folder:3":  ("persistent story flag 3", "medium", "SYSctlFlagFolder"),
    "folder:4":  ("persistent story flag 4", "medium", "SYSctlFlagFolder"),
    "folder:5":  ("persistent story flag 5", "medium", "SYSctlFlagFolder"),
    "folder:6":  ("persistent story flag 6", "medium", "SYSctlFlagFolder"),
    "folder:7":  ("persistent story flag 7", "medium", "SYSctlFlagFolder"),
    "folder:8":  ("persistent story gate 8", "high", "checked in city hub e0709"),
    "folder:9":  ("persistent story gate 9", "high", "checked in city hub e0709"),
    "folder:10": ("LordKnightmon ID (Electro Mine)", "medium", "save observation; separate from script-derived labels"),
    "folder:11": ("persistent quest-chain marker", "high", "SET in e0824/chunk_0104; corrected signed decoding"),
}


def collect():
    """Re-extract flag ops (mirrors flag_xref.py) with device tokens."""
    ops = []
    for entry in sorted(ENTRY_INFO):
        for index, path in lua_tree.chunks(entry, SRC):
            cname = "chunk_%04d.lua" % index    # the chunk id the tables cite
            with open(path, encoding="utf-8") as fh:
                text = fh.read()
            lines = text.splitlines()
            # device/npc/enemy/stage tokens in the whole chunk
            tokens = set(re.findall(r'\b(g_[a-z0-9]+|n_[a-z0-9]+|e_[a-z0-9]+|f_[a-z0-9]+)\b', text))
            stages = set(re.findall(r'funcStage(?:Change|In)\(\s*"([^"]+)"', text))
            for lineno, line in enumerate(lines, 1):
                for m in re.finditer(r'be:FLGset\(\s*([^,]+?)\s*,\s*([^)]+?)\s*\)', line):
                    kind, val = arg_kind(m.group(1))
                    ops.append(dict(op="set", flag=val if kind == "lit" else m.group(1).strip(),
                                    kind=kind, value=m.group(2).strip(), entry=entry,
                                    chunk=cname, tokens=tokens, stages=stages))
                for m in re.finditer(r'be:FLGisOn\(\s*([^)]+?)\s*\)', line):
                    kind, val = arg_kind(m.group(1))
                    ops.append(dict(op="chk", flag=val if kind == "lit" else m.group(1).strip(),
                                    kind=kind, value="", entry=entry, chunk=cname,
                                    tokens=tokens, stages=stages))
                for m in re.finditer(r'be:SYSctlFlagFolder\(\s*"([A-Z]+)"\s*,\s*([^)]+?)\s*\)', line):
                    arg = m.group(2).strip()
                    if arg.isdigit():
                        ops.append(dict(op=f"folder:{m.group(1)}", flag=f"folder:{arg}",
                                        kind="folder", value="", entry=entry, chunk=cname,
                                        tokens=tokens, stages=stages))
    return ops


def main():
    ops = collect()
    by_flag = defaultdict(list)
    for o in ops:
        by_flag[o["flag"]].append(o)

    # build meaning for every flag
    meanings = {}
    for f, olist in by_flag.items():
        if f in CURATED:
            meanings[f] = CURATED[f]
            continue
        if isinstance(f, int) and 100 <= f <= 299:
            # stage-local: name by the most common device token near sets
            devs = Counter()
            for o in olist:
                if o["op"] == "set":
                    for t in sorted(o["tokens"]):  # sorted: ties go the same way every run
                        if t.startswith("g_"):
                            devs[t] += 1
            if devs:
                dev = devs.most_common(1)[0][0]
                meanings[f] = (f"stage-local: {dev}", "low", "heuristic (device name)")
            else:
                meanings[f] = ("stage-local scratch flag", "low", "heuristic")
            continue
        # global/story: cross-region?
        entries = {o["entry"] for o in olist}
        regions = {REGION_BY_ENTRY[e] for e in entries if e in REGION_BY_ENTRY}
        if len(regions) >= 2:
            meanings[f] = (f"global/story flag ({len(regions)} regions)", "low", "heuristic (cross-region)")
        else:
            reg = next(iter(regions), "?")
            meanings[f] = (f"regional flag ({reg})", "low", "heuristic")

    # ---- markdown ---------------------------------------------------------
    md = [
        "# Flag meanings: Digimon World 4",
        "",
        "Curated story/progression flags plus heuristic labels for the rest.",
        "Confidence: **high** = decoded from direct evidence (set-on-defeat,",
        "level gate, quest completion), **medium** = by pattern, **low** = heuristic.",
        "",
        "## Story progression (high value)",
        "",
        "| flag | meaning | evidence |",
        "| --- | --- | --- |",
    ]
    for f in sorted((x for x in meanings if isinstance(x, int)), key=int):
        m, conf, ev = meanings[f]
        if conf in ("high", "medium"):
            md.append(f"| {f} | {m} | {ev} |")

    md += ["", "## Persistent flag folder (memory card, namespace 0-11)", ""]
    md.append("| flag | meaning | evidence |")
    md.append("| --- | --- | --- |")
    for f in sorted((x for x in meanings if isinstance(x, str) and x.startswith("folder:"))):
        m, conf, ev = meanings[f]
        md.append(f"| `{f}` | {m} | {ev} |")

    # ---- TSV: every flag ---------------------------------------------------
    tsv_path = os.path.join(OUTDIR, "flag-meanings.tsv")
    with open(tsv_path, "w", encoding="utf-8") as fh:
        fh.write("flag\tmeaning\tconfidence\tevidence\n")
        for f in sorted(by_flag, key=lambda x: (1, str(x)) if not isinstance(x, int) else (0, x)):
            m, conf, ev = meanings[f]
            fh.write(f"{f}\t{m}\t{conf}\t{ev}\n")

    md_path = os.path.join(OUTDIR, "flag-meanings.md")
    with open(md_path, "w", encoding="utf-8") as fh:
        fh.write("\n".join(md) + "\n")

    hi = sum(1 for m in meanings.values() if m[1] == "high")
    med = sum(1 for m in meanings.values() if m[1] == "medium")
    print(f"flags: {len(meanings)}  (high: {hi}, medium: {med}, low: {len(meanings)-hi-med})")
    print(f"wrote {md_path}")
    print(f"wrote {tsv_path}")


if __name__ == "__main__":
    main()
