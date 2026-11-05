#!/usr/bin/env python3
"""
build_lua_tree.py — organize the decompiler's output into `lua/`, the human-readable
tree with descriptive stage + chunk names (the one copy of the scripts the repository keeps).

scripts/lua_decompile.py writes `entry_NNNN/chunk_MMMM.lua` per pack entry into a scratch
folder; this copies each chunk, unchanged, to `lua/<region>/<stage>_e<entry>/<MMM>-<name>.lua`
(scripts/lua_tree.py resolves an entry and chunk number to that path).

Usage:
  python3 scripts/lua_decompile.py <NDMW.AFS> --out=build/lua_decompiled
  python3 scripts/build_lua_tree.py [src_dir] [dst_dir]
"""
import os
import re
import shutil
import sys
from collections import defaultdict

SRC = sys.argv[1] if len(sys.argv) > 1 else "build/lua_decompiled"
DST = sys.argv[2] if len(sys.argv) > 2 else "lua"

# ---------------------------------------------------------------------------
# Entry -> (region, stage folder name, description)
# Region order = game progression. Entry numbers are kept for cross-reference
# to the pack entry (the `_e<entry>` suffix of a stage folder).
# ---------------------------------------------------------------------------
REGIONS = [
    "title-menus",
    "lobby-hub",
    "valley-overworld",
    "desert-overworld",
    "forest-overworld",
    "city-overworld",
    "dungeon-1",
    "dungeon-2",
    "dungeon-3",
    "dungeon-4",
    "quest-dungeons",
    "bosses",
    "goblimon-fortress",
    "evolution",
    "misc",
]

# (entry_number, region, stage_name, description)
ENTRY_MAP = [
    # ---- title / menus -----------------------------------------------------
    (800,  "title-menus", "menu-database",          "DBBase + font database load"),
    (802,  "title-menus", "bandai-logo",            "Bandai logo + rating splash (stagis09)"),
    (804,  "title-menus", "opening",                "Opening movie setup (stagis10)"),
    (806,  "title-menus", "title-screen",           "Title screen (AM_TITLE)"),
    (808,  "title-menus", "character-select-1",     "Character select + shop cards"),
    (810,  "title-menus", "character-select-2",     "Character select / difficulty"),
    (812,  "title-menus", "character-select-3",     "Character select / difficulty"),
    (814,  "title-menus", "endroll",                "End roll / staff credits"),
    # ---- lobby / hub -------------------------------------------------------
    (816,  "lobby-hub", "lobby-ofanimon-seraphimon", "Lobby cutscene (n_ofanim, n_seraph)"),
    (820,  "lobby-hub", "lobby-quests",             "Lobby quest giver (n_leomon)"),
    (824,  "lobby-hub", "lobby-quest-board",        "Lobby quest board dialogue"),
    (828,  "lobby-hub", "lobby-shops",              "Lobby shops: bank + disk (bankshop.lua, diskshop.lua)"),
    (534,  "lobby-hub", "plaza-npc-hub",            "Plaza where all NPCs gather (item change hub, Z0101)"),
    (536,  "lobby-hub", "item-change-blackwargreymon", "Item change NPC (n_bwargrey)"),
    (538,  "lobby-hub", "item-change-agumon",       "Item change NPC (n_agumon)"),
    # ---- valley overworld --------------------------------------------------
    (614,  "valley-overworld", "stag0101-valley-entrance", "Leads to dungeon 1 (dng101b1) + Goblimon fortress (stagGF01)"),
    (621,  "valley-overworld", "stag0102-valley-crossroads", "Leads to dng102b1"),
    (628,  "valley-overworld", "stag0103-valley-river", "River (AM_RIVER) — boat, n_digilfm"),
    (635,  "valley-overworld", "stag0104-valley-cliff", "Leads to dng103f1"),
    # ---- desert overworld --------------------------------------------------
    (642,  "desert-overworld", "stag0201-desert-entrance", "Leads to dungeon 2 (dng204b1)"),
    (649,  "desert-overworld", "stag0202-desert-ruins", "Leads to dng205b1"),
    (658,  "desert-overworld", "stag0203-desert-crossroads", "Crossroads / turnstyle"),
    (665,  "desert-overworld", "stag0204-desert-canyon", "Leads to dng206f1"),
    (672,  "desert-overworld", "stag0205-desert-oasis", "Leads to Goblimon fortress (stagGF04)"),
    # ---- forest overworld --------------------------------------------------
    (679,  "forest-overworld", "stag0301-forest-entrance", "Leads to dng307b1 / dng309b1"),
    (686,  "forest-overworld", "stag0302-forest-grove", "Leads to dng308b1"),
    (695,  "forest-overworld", "stag0303-forest-cave", "Connector between grove and deep forest"),
    (702,  "forest-overworld", "stag0304-forest-deep", "Leads to dng310f1"),
    # ---- city overworld ----------------------------------------------------
    (709,  "city-overworld", "stag0403-city-quest-hub", "Teleports to dungeon 4 + quests q1-q8"),
    (716,  "city-overworld", "stag0404-city-magnet-flower", "Magnet-flower puzzle (g_magnetflore)"),
    (723,  "city-overworld", "city-boss4-approach", "Approach to boss 4 (stagBS04)"),
    # ---- dungeon 1 ---------------------------------------------------------
    (179,  "dungeon-1", "dng101b1", "block 1 (entrance)"),
    (187,  "dungeon-1", "dng101b2", "block 1 (security gate; e_blosso, e_scum)"),
    (195,  "dungeon-1", "dng102b1", "block 2 (entrance)"),
    (203,  "dungeon-1", "dng102b2", "block 2 (security gate)"),
    (210,  "dungeon-1", "dng102b3", "block 2 (e_mammos)"),
    (218,  "dungeon-1", "dng103f1", "final area 1"),
    (226,  "dungeon-1", "dng103f2", "final area 2 -> boss stagBS01"),
    # ---- dungeon 2 ---------------------------------------------------------
    (233,  "dungeon-2", "dng204b1", "block 1 (entrance)"),
    (241,  "dungeon-2", "dng204b2", "block 1 (e_minotaru, e_skulgrey)"),
    (249,  "dungeon-2", "dng205b1", "block 2 (entrance)"),
    (257,  "dungeon-2", "dng205b2", "block 2 (e_mummy, e_pharaoh)"),
    (265,  "dungeon-2", "dng205b3", "block 2 (e_anomalo, e_mecha1/2)"),
    (273,  "dungeon-2", "dng206f1", "final area 1"),
    (281,  "dungeon-2", "dng206f2", "final area 2 -> boss stagBS02"),
    # ---- dungeon 3 ---------------------------------------------------------
    (288,  "dungeon-3", "dng307b1", "block 1 (entrance)"),
    (296,  "dungeon-3", "dng307b2", "block 1 (e_tonogeko)"),
    (304,  "dungeon-3", "dng308b1", "block 2 (entrance)"),
    (312,  "dungeon-3", "dng308b2", "block 2 (security gate)"),
    (319,  "dungeon-3", "dng308b3", "block 2 (e_mecha4)"),
    (327,  "dungeon-3", "dng309b1", "block 3 (entrance)"),
    (335,  "dungeon-3", "dng309b2", "block 3 (security gate)"),
    (342,  "dungeon-3", "dng309b3", "block 3 (security gate)"),
    (349,  "dungeon-3", "dng309b4", "block 3 (e_diabolo)"),
    (357,  "dungeon-3", "dng310f1", "final area 1"),
    (365,  "dungeon-3", "dng310f2", "final area 2"),
    (372,  "dungeon-3", "dng310f3", "final area 3 -> boss stagBS03"),
    # ---- dungeon 4 ---------------------------------------------------------
    (379,  "dungeon-4", "dng411b1", "block 1 (entrance)"),
    (387,  "dungeon-4", "dng411b2", "block 1 (security gate)"),
    (394,  "dungeon-4", "dng411b3", "block 1 (e_mecha5, e_rare)"),
    (402,  "dungeon-4", "dng412b1", "block 2 (entrance)"),
    (410,  "dungeon-4", "dng412b2", "block 2 (security gate)"),
    (417,  "dungeon-4", "dng412b3", "block 2 (security gate)"),
    (425,  "dungeon-4", "dng412b4", "block 2 (e_ldknight = LordKnightmon)"),
    # ---- quest dungeons ----------------------------------------------------
    (433,  "quest-dungeons", "dngq1b1e", "quest 1 stage 1"),
    (441,  "quest-dungeons", "dngq1b2e", "quest 1 stage 2 (e_mammos)"),
    (449,  "quest-dungeons", "dngq2b1e", "quest 2 stage 1 (timed)"),
    (457,  "quest-dungeons", "dngq2b2e", "quest 2 stage 2 easy (mummy puzzle)"),
    (464,  "quest-dungeons", "dngq2b2h", "quest 2 stage 2 hard (timed, e_mummy)"),
    (471,  "quest-dungeons", "dngq3b1e", "quest 3 stage 1"),
    (479,  "quest-dungeons", "dngq3b2e", "quest 3 stage 2 (n_dorumon)"),
    (486,  "quest-dungeons", "dngq4b1e", "quest 4 stage 1 easy"),
    (494,  "quest-dungeons", "dngq4b1h", "quest 4 stage 1 hard"),
    (502,  "quest-dungeons", "dngq4b1v", "quest 4 stage 1 very hard"),
    (510,  "quest-dungeons", "dngq4b2e", "quest 4 stage 2 easy"),
    (518,  "quest-dungeons", "dngq4b2h", "quest 4 stage 2 hard"),
    (526,  "quest-dungeons", "dngq4b2v", "quest 4 stage 2 very hard"),
    (540,  "quest-dungeons", "quest-5-6-rare-six-doors", "quest 5/6 — six-door puzzle, rare enemies (e_rare; exact stage id uncertain)"),
    (548,  "quest-dungeons", "dngq7b1e", "quest 7 stage 1"),
    (556,  "quest-dungeons", "dngq7b2e", "quest 7 stage 2 (e_tonogeko)"),
    (564,  "quest-dungeons", "dngq8b1e", "quest 8 stage 1"),
    (572,  "quest-dungeons", "dngq8b2e", "quest 8 stage 2"),
    (579,  "quest-dungeons", "dngq8b3e", "quest 8 stage 3 easy"),
    (587,  "quest-dungeons", "dngq8b3h", "quest 8 stage 3 hard"),
    (595,  "quest-dungeons", "dngq8b3v", "quest 8 stage 3 very hard (e_ldknight)"),
    # ---- bosses ------------------------------------------------------------
    (730,  "bosses", "boss01-apocalymon", "f_apocaly (Apocalymon) + f_bit"),
    (737,  "bosses", "boss02-belialvamdemon", "f_belvam (BelialVamdemon)"),
    (744,  "bosses", "boss03-lucemon", "f_luce"),
    (751,  "bosses", "boss04-devimon-1", "f_devl1 (Devimon form 1)"),
    (758,  "bosses", "boss05-devimon-2", "f_devl2x (Devimon form 2)"),
    (765,  "bosses", "boss06-devimon-3", "f_devl3 (Devimon final, AM_DEVI3)"),
    # ---- goblimon fortress -------------------------------------------------
    (772,  "goblimon-fortress", "fortress-gate", "Breaking gate (stagGF02)"),
    (779,  "goblimon-fortress", "fortress-hub", "Fortress hub (stagGF01/03/04)"),
    (786,  "goblimon-fortress", "fortress-leomon", "Leomon encounter (AM_LEOMN, n_leomon)"),
    (793,  "goblimon-fortress", "fortress-exit", "Fortress exit (stag0205, stagGF02)"),
    # ---- evolution ---------------------------------------------------------
    (832,  "evolution", "digivolution", "Digivolution stage (AM_EVOLV)"),
    # ---- misc --------------------------------------------------------------
    (603,  "misc", "stage-select-list", "Master stage list + quest/time script refs"),
    (607,  "misc", "stage-clear-sequence", "Stage clear sequence (stageend, stag0001)"),
]

REGION_TITLES = {
    "title-menus": "Title screens & menus",
    "lobby-hub": "Digimon City (lobby / item-change hub)",
    "valley-overworld": "Valley overworld (stag0101-0104)",
    "desert-overworld": "Desert overworld (stag0201-0205)",
    "forest-overworld": "Forest overworld (stag0301-0304)",
    "city-overworld": "City overworld (stag0401-0404)",
    "dungeon-1": "Dungeon 1 — Valley dungeon (dng1xx)",
    "dungeon-2": "Dungeon 2 — Desert dungeon (dng2xx)",
    "dungeon-3": "Dungeon 3 — Forest dungeon (dng3xx)",
    "dungeon-4": "Dungeon 4 — City dungeon (dng4xx)",
    "quest-dungeons": "Quest dungeons (dngq1-q8)",
    "bosses": "Boss stages (stagBS01-06)",
    "goblimon-fortress": "Goblimon fortress (stagGF01-04)",
    "evolution": "Digivolution",
    "misc": "Misc / shared",
}


def slugify(s):
    s = s.strip().lower()
    s = re.sub(r"[^a-z0-9]+", "-", s)
    return s.strip("-")


def chunk_name(text):
    """Return a short human-readable slug describing a single chunk."""
    if "funcStartLayerSet" in text or "funcFirstLayerSet" in text:
        return "layer-setup"
    m = re.search(r'funcStageChange\("([^"]+)"', text)
    if m:
        return "exit-to-" + m.group(1).lower()
    if "funcSecurityGate" in text:
        return "security-gate"
    m = re.search(r'funcHealGate\("([^"]+)"', text)
    if m:
        return "heal-" + m.group(1).lower()
    m = re.search(r'funcOpenMessage\("talk",\s*"n_([a-z0-9]+)"', text)
    if m:
        return "npc-" + m.group(1)
    m = re.search(r"\bf_([a-z0-9]+)", text)
    if m:
        return "boss-" + m.group(1)
    m = re.search(r"\be_([a-z0-9]+)", text)
    if m:
        return "enemy-" + m.group(1)
    m = re.search(r"\bg_d([1-9])door", text)
    if m:
        return "door-d" + m.group(1)
    m = re.search(r'be:FLGset\((\d+)', text)
    if m:
        return "flag-" + m.group(1)
    m = re.search(r'be:FLGset\(be:MDLgetRamNo\(\) \+ (\d+)', text)
    if m:
        return "flag-ramno+" + m.group(1)
    if "CFLclear" in text or "SETDEMOCAMERA" in text or "animCamera" in text:
        return "camera"
    if "_ERRORMESSAGE" in text:
        return "status-stub"
    if "MDLgetBulletName" in text:
        return "bullet-hit"
    if "MDLaddHp" in text or "funcTechWazaHitCheck" in text or "funcTameWazaHitCheck" in text:
        return "damage-calc"
    m = re.search(r'mswk(\w+)', text)
    if m:
        return "msg-" + m.group(1).lower()
    m = re.search(r'"([A-Za-z0-9_]+\.lua)"', text)
    if m:
        return "script-" + m.group(1).lower()
    if '"SOUND"' in text or "BGMSTOP" in text or "ENVSTOP" in text:
        return "sound-music"
    if "funcStageIn" in text:
        return "stage-in"
    if "be:MDLsetSeq" in text:
        return "model-seq"
    if "funcPlayerStatusSet" in text:
        return "player-status"
    if "be:DMrun" in text:
        return "dm-run"
    return "chunk"


def main():
    if not os.path.isdir(SRC):
        sys.exit(f"source dir not found: {SRC}")
    if os.path.exists(DST):
        print(f"removing existing {DST}")
        shutil.rmtree(DST)
    os.makedirs(DST)

    # index entry -> (region, stage, desc)
    by_entry = {e: (r, s, d) for (e, r, s, d) in ENTRY_MAP}
    seen_entries = set()
    n_files = 0

    # build per-region structure
    region_stages = defaultdict(list)  # region -> [(entry, stage, desc)]
    for (e, r, s, d) in ENTRY_MAP:
        if e in seen_entries:
            sys.exit(f"duplicate entry in map: {e}")
        seen_entries.add(e)
        region_stages[r].append((e, s, d))

    # sanity: every AFS entry dir must be covered
    src_entries = set()
    for name in os.listdir(SRC):
        m = re.match(r"entry_(\d+)$", name)
        if m:
            src_entries.add(int(m.group(1)))
    missing = src_entries - seen_entries
    if missing:
        print("WARNING: entries not covered by ENTRY_MAP:")
        print(sorted(missing))
    extra = seen_entries - src_entries
    if extra:
        print("WARNING: map entries not present on disk:")
        print(sorted(extra))

    # generate tree
    for ri, region in enumerate(REGIONS):
        stages = region_stages.get(region, [])
        if not stages:
            continue
        # sort stages by entry number (keeps AFS order within a region)
        stages.sort(key=lambda t: t[0])
        region_dir = os.path.join(DST, f"{ri:02d}-{region}")
        os.makedirs(region_dir, exist_ok=True)

        for si, (entry, stage, desc) in enumerate(stages, 1):
            stage_dir = os.path.join(region_dir, f"{si:02d}-{stage}_e{entry}")
            os.makedirs(stage_dir, exist_ok=True)
            src_entry_dir = os.path.join(SRC, f"entry_{entry:04d}")
            chunks = sorted(
                [c for c in os.listdir(src_entry_dir) if c.endswith(".lua")],
                key=lambda c: int(re.search(r"(\d+)", c).group(1)),
            )
            used = defaultdict(int)
            for cidx, c in enumerate(chunks):
                with open(os.path.join(src_entry_dir, c), encoding="utf-8") as fh:
                    text = fh.read()
                base = chunk_name(text)
                used[base] += 1
                suffix = f"-{used[base]}" if used[base] > 1 else ""
                out_name = f"{cidx:03d}-{base}{suffix}.lua"
                shutil.copy2(os.path.join(src_entry_dir, c), os.path.join(stage_dir, out_name))
                n_files += 1
            # stage readme note
            with open(os.path.join(stage_dir, "_origin.txt"), "w", encoding="utf-8") as fh:
                fh.write(f"AFS entry {entry}  |  {stage}  |  {desc}\n")
                fh.write("A file's numeric prefix is its chunk index in that pack entry.\n")
                fh.write(f"{len(chunks)} chunks\n")

    # layout doc — written into the documentation hub
    lines = [
        "# `lua/` — decompiled Lua tree layout",
        "",
        "`lua/` holds every Lua chunk of `NDMW.AFS`, decompiled and filed by stage. A stage folder's "
        "`_e<N>` suffix is the pack entry and a file's numeric prefix its chunk index in that entry "
        "(`scripts/lua_tree.py` resolves the pair to a path). This file is the index for the tree.",
        "",
        "## Layout",
        "",
    ]
    for ri, region in enumerate(REGIONS):
        stages = region_stages.get(region, [])
        if not stages:
            continue
        lines.append(f"### {ri:02d} — {REGION_TITLES.get(region, region)}")
        lines.append("")
        lines.append("| entry | stage | description |")
        lines.append("| --- | --- | --- |")
        for (entry, stage, desc) in sorted(stages, key=lambda t: t[0]):
            lines.append(f"| {entry} | `{stage}` | {desc} |")
        lines.append("")
    lines += [
        "## Chunk naming",
        "",
        "Each chunk is named by what it does, e.g.:",
        "- `000-layer-setup.lua` — `funcStartLayerSet` / `funcFirstLayerSet`",
        "- `012-exit-to-dng204b2.lua` — `funcStageChange(\"dng204b2\", ...)`",
        "- `005-npc-agumon.lua` — an NPC (`n_agumon`) talk/interaction script",
        "- `003-enemy-mammos.lua` / `004-boss-devimon-1.lua` — enemy / boss behavior",
        "- `007-flag-123.lua` — `be:FLGset(123, 0)` (flag reset) + related logic",
        "- `002-door-d1.lua`, `006-heal-hp.lua`, `009-security-gate.lua`, ...",
        "",
        "The numeric prefix keeps the original concatenation order. "
        "Each stage folder also has a `_origin.txt` with the original "
        "`entry_NNNN` it came from.",
        "",
    ]
    LAYOUT_DOC = "docs/engine/lua-tree-layout.md"
    with open(LAYOUT_DOC, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines) + "\n")

    print(f"wrote {DST} — {len(seen_entries)} stages, {n_files} chunks")


if __name__ == "__main__":
    main()
