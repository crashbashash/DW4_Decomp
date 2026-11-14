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
from collections import Counter, defaultdict

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
    (628,  "valley-overworld", "stag0103-valley-river", "River (AM_RIVER), boat, n_digilfm"),
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
    (540,  "quest-dungeons", "quest-5-6-rare-six-doors", "quest 5/6: six-door puzzle, rare enemies (e_rare; exact stage id uncertain)"),
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
    "dungeon-1": "Dungeon 1, Valley dungeon (dng1xx)",
    "dungeon-2": "Dungeon 2, Desert dungeon (dng2xx)",
    "dungeon-3": "Dungeon 3, Forest dungeon (dng3xx)",
    "dungeon-4": "Dungeon 4, City dungeon (dng4xx)",
    "quest-dungeons": "Quest dungeons (dngq1-q8)",
    "bosses": "Boss stages (stagBS01-06)",
    "goblimon-fortress": "Goblimon fortress (stagGF01-04)",
    "evolution": "Digivolution",
    "misc": "Misc / shared",
}


def slugify(s, limit=48):
    s = s.strip().lower()
    s = re.sub(r"[^a-z0-9]+", "-", s).strip("-")
    if len(s) > limit:
        s = s[:limit].rsplit("-", 1)[0]
    return s


def kebab(identifier):
    """`LISsetDifficultMax` -> `lis-set-difficult-max`, `funcOneMessage` -> `func-one-message`."""
    m = re.match(r"([A-Z]{2,})([a-z].*)$", identifier)  # native API: PREFIX + verb + Noun
    if m:
        identifier = m.group(1) + "-" + m.group(2)
    return slugify(re.sub(r"(?<=[a-z0-9])(?=[A-Z])|(?<=[A-Z])(?=[A-Z][a-z])", "-", identifier))


_flag_meanings = None


def flag_meaning(flag):
    """The curated meaning of a flag (scripts/flag_meanings.py) as a slug of
    at most five words, or ''."""
    global _flag_meanings
    if _flag_meanings is None:
        from flag_meanings import CURATED  # imports this module, so not at load time
        _flag_meanings = {}
        for flag, (meaning, _confidence, _evidence) in CURATED.items():
            if isinstance(flag, int):
                words = slugify(meaning.split("(")[0], limit=200).split("-")
                _flag_meanings[flag] = "-".join(words[:5])
    return _flag_meanings.get(flag, "")


def most_common(items):
    """The most frequent item, ties to the first seen; None when empty."""
    if not items:
        return None
    counts = Counter(items)
    best = max(counts.values())
    return next(i for i in items if counts[i] == best)


SD_CALL = re.compile(r'be:(?:sd|DMsetSD|DMchkSD|DMswtSD)\("([A-Z0-9_]+)", (?:"([^"]*)"|nil|[^,]+), [^,]+, "([^"]*)"(?:, "([^"]*)")?')
MODEL = re.compile(r'"([gneijfx]_[a-z0-9_]+)"')


def content_name(text):
    """A slug from what a chunk the named rules miss actually does."""
    sends = SD_CALL.findall(text)
    gens = [p for (ctl, _m, cmd, p) in sends if ctl == "GENERATER" and p]
    if gens:
        started = [p for (ctl, _m, cmd, p) in sends if ctl == "GENERATER" and cmd == "START" and p]
        return "generator-" + slugify("-".join(sorted(set(started or gens), key=(started or gens).index)[:3]))
    models = [m for (ctl, m, _c, _p) in sends if m and ctl in ("MODELCTRL", "HITLANDMODEL")]
    if models:
        return "model-" + slugify(most_common(models))
    if sends:
        ctl, _m, cmd, param = sends[0]
        return slugify("-".join(x for x in (ctl, cmd, param) if x))
    methods = [m for m in re.findall(r"be:([A-Za-z]+)\(", text) if not re.match(r"[A-Z]+(get|is)", m)]
    if methods:
        return kebab(most_common(methods))
    calls = re.findall(r"\b((?:func|stageLocalFunc)[A-Z]\w*)\(", text)
    if calls:
        return kebab(most_common(calls))
    stores = re.findall(r"^\s*g_(\w+) = ", text, re.M)
    if stores:
        return "sets-" + slugify(most_common(stores))
    if not text.strip():
        return "empty"
    return "chunk"


def chunk_name(text):
    """Return a short human-readable slug describing a single chunk."""
    if re.search(r"^func[A-Z]\w* = function", text, re.M):
        return "function-library"
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
    m = re.search(r'be:FLGset\((\d+), ([^)]*)\)', text)
    if m:
        flag = int(m.group(1))
        return "-".join(("flag", str(flag), flag_meaning(flag)
                         or ("clear" if m.group(2) == "0" else "set")))
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
    return content_name(text)


def features(text):
    """Distinguishing details of a chunk, most telling first, for chunks that
    share a name: its first message, stage target, main sequence, model,
    flags, counter test, native command, controller, then any string."""
    out = []
    m = re.search(r"\bmswk(\w+) =", text)
    if m:
        out.append("msg-" + m.group(1).lower())
    m = re.search(r'"NEXTSTAGE", "([^"]+)"', text)
    if m:
        out.append("to-" + m.group(1).lower())
    seq = most_common(re.findall(r'"(SQ_[A-Z0-9_]+)', text))
    if seq:
        out.append(slugify(seq))
    model = most_common(MODEL.findall(text))
    if model:
        out.append(slugify(model))
    out += [f"flag-{f}" for f in dict.fromkeys(re.findall(r"be:FLGset\((\d+)", text))]
    out += [f"if-flag-{f}" for f in dict.fromkeys(re.findall(r"be:FLGisOn\((\d+)", text))]
    out += [f"counter-{v}" for v in dict.fromkeys(re.findall(r"be:COUNTERget\(\d+\) == (\d+)", text))]
    method = most_common([m for m in re.findall(r"be:([A-Za-z]+)\(", text)
                          if m not in ("sd", "DMsetSD", "DMchkSD", "DMswtSD", "DMrun")])
    if method:
        out.append(kebab(method))
    ctl = most_common(re.findall(r'be:(?:sd|DMsetSD|DMchkSD)\("([A-Z0-9_]+)"', text))
    if ctl:
        out.append(slugify(ctl))
    # last resort: any string the chunk uses
    out += [s for s in dict.fromkeys(slugify(s) for s in re.findall(r'"([^"\\]*)"', text)) if s]
    return out


def chunk_names(texts):
    """Names for one stage's chunks. Chunks that share a base name get the
    first of their `features` that no other chunk of the group has; one
    without such a detail keeps the bare base name (the numeric prefix keeps
    the files apart)."""
    bases = [chunk_name(t) for t in texts]
    groups = defaultdict(list)
    for i, base in enumerate(bases):
        groups[base].append(i)
    names = list(bases)
    for base, members in groups.items():
        if len(members) < 2:
            continue
        feats = {i: [f for f in features(texts[i]) if f not in base] for i in members}
        for i in members:
            others = set()
            for j in members:
                if j != i:
                    others.update(feats[j])
            unique = next((f for f in feats[i] if f not in others), None)
            if unique:
                names[i] = f"{base}-{unique}"
    return names


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
            texts = []
            for c in chunks:
                with open(os.path.join(src_entry_dir, c), encoding="utf-8") as fh:
                    texts.append(fh.read())
            for cidx, (c, name) in enumerate(zip(chunks, chunk_names(texts))):
                out_name = f"{cidx:03d}-{name}.lua"
                shutil.copy2(os.path.join(src_entry_dir, c), os.path.join(stage_dir, out_name))
                n_files += 1
            # stage readme note
            with open(os.path.join(stage_dir, "_origin.txt"), "w", encoding="utf-8") as fh:
                fh.write(f"AFS entry {entry}  |  {stage}  |  {desc}\n")
                fh.write("A file's numeric prefix is its chunk index in that pack entry.\n")
                fh.write(f"{len(chunks)} chunks\n")

    # layout doc, written into the documentation hub
    lines = [
        "# `lua/`: decompiled Lua tree layout",
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
        lines.append(f"### {ri:02d}: {REGION_TITLES.get(region, region)}")
        lines.append("")
        lines.append("| entry | stage | description |")
        lines.append("| --- | --- | --- |")
        for (entry, stage, desc) in sorted(stages, key=lambda t: t[0]):
            lines.append(f"| {entry} | `{stage}` | {desc} |")
        lines.append("")
    lines += [
        "## Chunk naming",
        "",
        "Each chunk is named by what it does (`chunk_name` in `scripts/build_lua_tree.py`), e.g.:",
        "- `layer-setup`: `funcStartLayerSet` / `funcFirstLayerSet`; `function-library`: the chunk "
        "that defines the stage's `func*` globals",
        "- `exit-to-dng204b2`: `funcStageChange(\"dng204b2\", ...)`",
        "- `npc-agumon`: an NPC (`n_agumon`) talk/interaction script",
        "- `enemy-mammos` / `boss-devl1`: enemy / boss behavior",
        "- `flag-110-set`: the first literal `be:FLGset(110, 1)` (`clear` for a 0), or the flag's "
        "curated meaning from `scripts/flag_meanings.py` when it has one "
        "(`flag-409-quest-act-in-progress-marker`)",
        "- `generator-gene-04`, `model-g-ddamagefloor`, `sets-fall0`: for a chunk no named rule "
        "covers, the generator it starts, the model it drives, the native command it sends or the "
        "global it sets",
        "- `door-d1`, `heal-hp`, `security-gate`, `damage-calc`, `bullet-hit`, ...",
        "",
        "Chunks of one stage that share a name get the first detail that no other chunk of the "
        "group has: their first message work global (`npc-agumon-msg-61240` / "
        "`npc-agumon-msg-61618`), stage target, main sequence (`layer-setup-sq-clear`), model, "
        "flag, counter test, native command or controller, then any string. A chunk with no such "
        "detail keeps the bare name; the numeric prefix keeps the original concatenation order "
        "and the files apart. Each stage folder also has a `_origin.txt` with its pack entry, "
        "stage and chunk count.",
        "",
        "## Local names",
        "",
        "The chunks carry no local names, so a local is named from how the bytecode uses it "
        "(`scripts/lua_names.py`): a closure by its body (`showText`), a value by the native "
        "getter it comes from (`ramNo`, `isCritical`), a counter (`count`), an argument by the "
        "engine's parameter name (`playerIndex`, `flagNo`), a numeric-for variable `i` / `j` / `k`. "
        "These names are inferred, not recovered; a local with no such use keeps its slot name "
        "`local_N` (parameters `arg_N`). Globals, methods and strings are the bytecode's own.",
        "",
    ]
    LAYOUT_DOC = "docs/engine/lua-tree-layout.md"
    with open(LAYOUT_DOC, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines) + "\n")

    print(f"wrote {DST}: {len(seen_entries)} stages, {n_files} chunks")


if __name__ == "__main__":
    main()
