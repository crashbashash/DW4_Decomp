# `lua/` — decompiled Lua tree layout

`lua/` holds every Lua chunk of `NDMW.AFS`, decompiled and filed by stage. A stage folder's `_e<N>` suffix is the pack entry and a file's numeric prefix its chunk index in that entry (`scripts/lua_tree.py` resolves the pair to a path). This file is the index for the tree.

## Layout

### 00 — Title screens & menus

| entry | stage | description |
| --- | --- | --- |
| 800 | `menu-database` | DBBase + font database load |
| 802 | `bandai-logo` | Bandai logo + rating splash (stagis09) |
| 804 | `opening` | Opening movie setup (stagis10) |
| 806 | `title-screen` | Title screen (AM_TITLE) |
| 808 | `character-select-1` | Character select + shop cards |
| 810 | `character-select-2` | Character select / difficulty |
| 812 | `character-select-3` | Character select / difficulty |
| 814 | `endroll` | End roll / staff credits |

### 01 — Digimon City (lobby / item-change hub)

| entry | stage | description |
| --- | --- | --- |
| 534 | `plaza-npc-hub` | Plaza where all NPCs gather (item change hub, Z0101) |
| 536 | `item-change-blackwargreymon` | Item change NPC (n_bwargrey) |
| 538 | `item-change-agumon` | Item change NPC (n_agumon) |
| 816 | `lobby-ofanimon-seraphimon` | Lobby cutscene (n_ofanim, n_seraph) |
| 820 | `lobby-quests` | Lobby quest giver (n_leomon) |
| 824 | `lobby-quest-board` | Lobby quest board dialogue |
| 828 | `lobby-shops` | Lobby shops: bank + disk (bankshop.lua, diskshop.lua) |

### 02 — Valley overworld (stag0101-0104)

| entry | stage | description |
| --- | --- | --- |
| 614 | `stag0101-valley-entrance` | Leads to dungeon 1 (dng101b1) + Goblimon fortress (stagGF01) |
| 621 | `stag0102-valley-crossroads` | Leads to dng102b1 |
| 628 | `stag0103-valley-river` | River (AM_RIVER) — boat, n_digilfm |
| 635 | `stag0104-valley-cliff` | Leads to dng103f1 |

### 03 — Desert overworld (stag0201-0205)

| entry | stage | description |
| --- | --- | --- |
| 642 | `stag0201-desert-entrance` | Leads to dungeon 2 (dng204b1) |
| 649 | `stag0202-desert-ruins` | Leads to dng205b1 |
| 658 | `stag0203-desert-crossroads` | Crossroads / turnstyle |
| 665 | `stag0204-desert-canyon` | Leads to dng206f1 |
| 672 | `stag0205-desert-oasis` | Leads to Goblimon fortress (stagGF04) |

### 04 — Forest overworld (stag0301-0304)

| entry | stage | description |
| --- | --- | --- |
| 679 | `stag0301-forest-entrance` | Leads to dng307b1 / dng309b1 |
| 686 | `stag0302-forest-grove` | Leads to dng308b1 |
| 695 | `stag0303-forest-cave` | Connector between grove and deep forest |
| 702 | `stag0304-forest-deep` | Leads to dng310f1 |

### 05 — City overworld (stag0401-0404)

| entry | stage | description |
| --- | --- | --- |
| 709 | `stag0403-city-quest-hub` | Teleports to dungeon 4 + quests q1-q8 |
| 716 | `stag0404-city-magnet-flower` | Magnet-flower puzzle (g_magnetflore) |
| 723 | `city-boss4-approach` | Approach to boss 4 (stagBS04) |

### 06 — Dungeon 1 — Valley dungeon (dng1xx)

| entry | stage | description |
| --- | --- | --- |
| 179 | `dng101b1` | block 1 (entrance) |
| 187 | `dng101b2` | block 1 (security gate; e_blosso, e_scum) |
| 195 | `dng102b1` | block 2 (entrance) |
| 203 | `dng102b2` | block 2 (security gate) |
| 210 | `dng102b3` | block 2 (e_mammos) |
| 218 | `dng103f1` | final area 1 |
| 226 | `dng103f2` | final area 2 -> boss stagBS01 |

### 07 — Dungeon 2 — Desert dungeon (dng2xx)

| entry | stage | description |
| --- | --- | --- |
| 233 | `dng204b1` | block 1 (entrance) |
| 241 | `dng204b2` | block 1 (e_minotaru, e_skulgrey) |
| 249 | `dng205b1` | block 2 (entrance) |
| 257 | `dng205b2` | block 2 (e_mummy, e_pharaoh) |
| 265 | `dng205b3` | block 2 (e_anomalo, e_mecha1/2) |
| 273 | `dng206f1` | final area 1 |
| 281 | `dng206f2` | final area 2 -> boss stagBS02 |

### 08 — Dungeon 3 — Forest dungeon (dng3xx)

| entry | stage | description |
| --- | --- | --- |
| 288 | `dng307b1` | block 1 (entrance) |
| 296 | `dng307b2` | block 1 (e_tonogeko) |
| 304 | `dng308b1` | block 2 (entrance) |
| 312 | `dng308b2` | block 2 (security gate) |
| 319 | `dng308b3` | block 2 (e_mecha4) |
| 327 | `dng309b1` | block 3 (entrance) |
| 335 | `dng309b2` | block 3 (security gate) |
| 342 | `dng309b3` | block 3 (security gate) |
| 349 | `dng309b4` | block 3 (e_diabolo) |
| 357 | `dng310f1` | final area 1 |
| 365 | `dng310f2` | final area 2 |
| 372 | `dng310f3` | final area 3 -> boss stagBS03 |

### 09 — Dungeon 4 — City dungeon (dng4xx)

| entry | stage | description |
| --- | --- | --- |
| 379 | `dng411b1` | block 1 (entrance) |
| 387 | `dng411b2` | block 1 (security gate) |
| 394 | `dng411b3` | block 1 (e_mecha5, e_rare) |
| 402 | `dng412b1` | block 2 (entrance) |
| 410 | `dng412b2` | block 2 (security gate) |
| 417 | `dng412b3` | block 2 (security gate) |
| 425 | `dng412b4` | block 2 (e_ldknight = LordKnightmon) |

### 10 — Quest dungeons (dngq1-q8)

| entry | stage | description |
| --- | --- | --- |
| 433 | `dngq1b1e` | quest 1 stage 1 |
| 441 | `dngq1b2e` | quest 1 stage 2 (e_mammos) |
| 449 | `dngq2b1e` | quest 2 stage 1 (timed) |
| 457 | `dngq2b2e` | quest 2 stage 2 easy (mummy puzzle) |
| 464 | `dngq2b2h` | quest 2 stage 2 hard (timed, e_mummy) |
| 471 | `dngq3b1e` | quest 3 stage 1 |
| 479 | `dngq3b2e` | quest 3 stage 2 (n_dorumon) |
| 486 | `dngq4b1e` | quest 4 stage 1 easy |
| 494 | `dngq4b1h` | quest 4 stage 1 hard |
| 502 | `dngq4b1v` | quest 4 stage 1 very hard |
| 510 | `dngq4b2e` | quest 4 stage 2 easy |
| 518 | `dngq4b2h` | quest 4 stage 2 hard |
| 526 | `dngq4b2v` | quest 4 stage 2 very hard |
| 540 | `quest-5-6-rare-six-doors` | quest 5/6 — six-door puzzle, rare enemies (e_rare; exact stage id uncertain) |
| 548 | `dngq7b1e` | quest 7 stage 1 |
| 556 | `dngq7b2e` | quest 7 stage 2 (e_tonogeko) |
| 564 | `dngq8b1e` | quest 8 stage 1 |
| 572 | `dngq8b2e` | quest 8 stage 2 |
| 579 | `dngq8b3e` | quest 8 stage 3 easy |
| 587 | `dngq8b3h` | quest 8 stage 3 hard |
| 595 | `dngq8b3v` | quest 8 stage 3 very hard (e_ldknight) |

### 11 — Boss stages (stagBS01-06)

| entry | stage | description |
| --- | --- | --- |
| 730 | `boss01-apocalymon` | f_apocaly (Apocalymon) + f_bit |
| 737 | `boss02-belialvamdemon` | f_belvam (BelialVamdemon) |
| 744 | `boss03-lucemon` | f_luce |
| 751 | `boss04-devimon-1` | f_devl1 (Devimon form 1) |
| 758 | `boss05-devimon-2` | f_devl2x (Devimon form 2) |
| 765 | `boss06-devimon-3` | f_devl3 (Devimon final, AM_DEVI3) |

### 12 — Goblimon fortress (stagGF01-04)

| entry | stage | description |
| --- | --- | --- |
| 772 | `fortress-gate` | Breaking gate (stagGF02) |
| 779 | `fortress-hub` | Fortress hub (stagGF01/03/04) |
| 786 | `fortress-leomon` | Leomon encounter (AM_LEOMN, n_leomon) |
| 793 | `fortress-exit` | Fortress exit (stag0205, stagGF02) |

### 13 — Digivolution

| entry | stage | description |
| --- | --- | --- |
| 832 | `digivolution` | Digivolution stage (AM_EVOLV) |

### 14 — Misc / shared

| entry | stage | description |
| --- | --- | --- |
| 603 | `stage-select-list` | Master stage list + quest/time script refs |
| 607 | `stage-clear-sequence` | Stage clear sequence (stageend, stag0001) |

## Chunk naming

Each chunk is named by what it does, e.g.:
- `000-layer-setup.lua` — `funcStartLayerSet` / `funcFirstLayerSet`
- `012-exit-to-dng204b2.lua` — `funcStageChange("dng204b2", ...)`
- `005-npc-agumon.lua` — an NPC (`n_agumon`) talk/interaction script
- `003-enemy-mammos.lua` / `004-boss-devimon-1.lua` — enemy / boss behavior
- `007-flag-123.lua` — `be:FLGset(123, 0)` (flag reset) + related logic
- `002-door-d1.lua`, `006-heal-hp.lua`, `009-security-gate.lua`, ...

The numeric prefix keeps the original concatenation order. Each stage folder also has a `_origin.txt` with the original `entry_NNNN` it came from.

