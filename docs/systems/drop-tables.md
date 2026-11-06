# Item drop tables (destructible boxes, enemies, bosses)

**Status:** format solved and **live-verified**. The Guard Room
(`stagGF01`) box drop tables are read out in §5.
**Method:** the pack is parsed as igBinary ([`../../scripts/igb_inst.py`](../../scripts/igb_inst.py))
and the tables are read out of the RAM of a save state.

---

## 1. Two different things drop items

| Path | Who rolls the table | Used by |
|---|---|---|
| **Generator drop** | `FUN_00384800`, called from the `beGenerater` update (`0x384ed0`, `0x385140`, `0x385300`) | `GENE-*` enemies, and the `GBOX-*` / `GBRL-*` / `GWCS-*` prop generators |
| Lua-placed props | no generator exists, so nothing rolls | props placed by `MODELCTRL … GENERATE` (e.g. the practice stage's rocks/bushes) |

So a breakable's drop table lives on whatever *generator* spawned it. The
`g_*` prop generators are ordinary `beGeneraterData` rows whose `_geneEnemyId`
points at a `g_*` row of the 649-row stat table.

## 2. The structure

```
beGeneraterData                       (vtable 0x535EB0)
  +0x40 _playerDataList ──► beGeneraterPlayerDataList
                              └─ beGeneraterPlayerData        (vtable 0x535DE0)
                                   +0x08 _geneCount
                                   +0x0c _geneMaxCount
                                   +0x10 _itemDataList     ──┐  indexed by DIFFICULTY
                                   +0x14 _itemLastDataList ──┘
                                        └─ beGeneraterItemData
                                             +0x08 NAME  (e.g. "nZ1obje1")
                                             +0x0c ──► beGeneraterItemDataOneList
                                                          └─ beGeneraterItemDataOne
                                                               +0x08 category string
                                                               +0x0c item id
                                                               +0x10 _rank
                                                               +0x14 _rate
```

* The **outer** list is indexed by difficulty: `_itemDataList[DIFFICULTY]`, where
  `DIFFICULTY` is read from a `GAMERAM` `DIFFICULTY` object (`iVar7+0xc`).
* `_itemLastDataList` replaces `_itemDataList` when the caller passes a flag and the
  generator holds exactly one enemy.
* `beGenerater` also carries an `_isPerfectDrop` field (`0x5050b8` is its reflection name
  string, not the flag — §5) and a `PERFECTDROP` method.

### The roll (`FUN_00384800`)

```c
r = RNG() % 10000;
for (k = 0; k < oneList->count; k++) {
    r -= oneList->data[k]->_rate;
    if (r < 1) { /* k is the drop */ }
}
```

Therefore `P(entry k) = _rate_k / 10000` and

**`P(nothing drops) = 1 − Σ(_rate) / 10000`.**

The guard-room box table `nZ1obje1` sums to **4330**, so on Normal a broken case
drops *something* only **43.3 %** of the time; `hZ1obje1` 60.5 %, `vZ1obje1` 59.1 %.
Boss tables usually sum to exactly 10000 (always a drop).

The winning entry is then spawned as a model through `MODELCTRL … GENERATE`, with
the category resolved against the engine table at **`0x4c8f30`**:
`conItem · insItem · impItem · weapon · armor1 · armor2 · abChip`.

## 3. Where the tables live, and how to name them

Every stage's generators live in a small **generator pack** (its own
`generatorH/N/V.igb`) next to the stage's Lua pack. Stage → AFS entry is
authoritative: **NDMW.AFS entries 80–177 are `beFileListInfo` manifests**, one per
stage, each carrying the stage name and its pack indices as `[0.NNN]` strings.

| stage | manifest entry | packs | generator packs |
|---|---|---|---|
| `stagGF01` (Guard Room) | 161 | 771, **772** | **773 / 774 / 775** |
| `stagGF02` | 162 | 778, 779 | 780 / 781 / 782 |
| `stagGF03` (X Digimon Lab boss) | 163 | 785, **786** | **787 / 788 / 789** |
| `stagGF04` | 164 | 792, 793 | 794 / 795 / 796 |
| `stag0102` (valley crossroads) | 140 | 620, **621** | 622 / 623 / 624 |
| `stag0101` (valley entrance) | 139 | 613, 614 | 615 / 616 / 617 |

> This **corrects the `lua/12-goblimon-fortress` folder labels**: entry 772
> is `stagGF01` (the Guard Room, the stage whose Lua spawns `g_trapboxz05`), 779 is
> `stagGF02`, **786 is `stagGF03`** (where the Goblin Fortress boss `e_mecha4`
> actually runs — entry 787 holds `nZ1mec41`), 793 is `stagGF04`.

Table names are self-describing: **`n`/`h`/`v` = Normal / Hard / Very Hard**, `Z1` =
World 1, then a source tag: `obje` (breakable object), `cont` (box/container),
`gobr` (Goburimon), `ogre`, `rare` (Raremon), `blos` (Blossomon), `mec4` (`e_mecha4`).

### Which family uses which pool (live, `stag0102`)

| generator | model | stat row | drop pool |
|---|---|---|---|
| `GBOX-*` | `g_box`, `g_boxfield` | 370, 371 | **`Z1cont1`** |
| `GBRL-*` | `g_bbarrelsz01/02` | 372, 373 | **`Z1obje1`** |
| `GWCS-*` | `g_woodencasez01/02/03/05` | 375–378 | **`Z1obje1`** |

So *boxes* and *barrels/cases* are two different pools. The fortress has **no boxes
at all**: `773/774/775` contain no `GBOX-*` and no `cont1` table.

### Is a list per stage, per generator, or per family?

**None of those as a mechanism — the lists are a per-zone *library*, and every
generator holds an explicit pointer into it.** There is no name lookup, no
inheritance and no fallback:

* The reference is a raw pointer on the generator itself: `beGeneraterData +0x40`
  → `beGeneraterPlayerData` → `+0x10`/`+0x14`. `FUN_00384800`'s caller loads it and
  rolls; nothing anywhere resolves a list *by name*.
* **There is no "zone default" to fall back to.** A generator whose list is empty
  drops nothing, full stop — verified live: zeroing every weight in the active
  `nZ1gobr3` produced no drops at all rather than a fallback to some other list
.
* What *looks* like a default is an authoring pattern. One zone pack's region in the
  ISO lists a whole family library, all three difficulties at once:

  `gobr1  nume1  ogre1  obje1  cont1  bit  gate  reizu`  (× `n`/`h`/`v`)

  i.e. the pack authors one list per **family** (goblin, numemon, ogremon, object,
  container, …), and `naming = <difficulty><zone><family><variant>`: `nZ1gobr3` is
  Normal / zone `Z1` / goblins / variant 3.
* Every generator in `stagGF01` that drops then simply points at the family list it
  wants, and the pack's igBinary serialisation shares one object between them:

  | generators | list | note |
  |---|---|---|
  | 23 (all Goburimon spawners) | `n/h/vZ1gobr3` | same three **objects** (`0x12b49c8`/`0x13ed230`/`0x13ed708`) |
  | `GWCS-05` (the crates) | `n/h/vZ1obje1` | a different family, so a different list |
  | `GENE-19` | `comonNOTG01` ×3 | an explicitly authored **empty** list |

  So `GENE-19` and `GWCS-05` are not *overriding* anything — they are authored
  against other lists, and the engine treats all three cases identically.
* Packs that want the same loot carry their own copy of it: `Z1obje1` occurs 45
  times in the ISO = ~15 packs × 3 difficulties, each occurrence sitting among that
  pack's other same-zone family names. Same duplication pattern as the enemy stat
  table's 665 byte-identical copies, and the reason the same pool name (e.g.
  `Z1obje1` here and in `stag0102`) shows up in more than one stage.

**Practical consequence:** "which Goburimon do I kill?" never matters, but "which
*family* am I fighting?" always does — and a stage script can point one group at a
list other than its family's (that is the only sense in which overrides exist).

## 4. Reading a pack statically

A generator pack is igBinary:
`[type directory][object directory][object data][list-data pool]`, with
`hdr[4]` = object-data bytes, `hdr[5]` = object count, `hdr[6]` = pool bytes
(all three verified exactly: the objects tile `hdr[4]`, and the pool is the last
`hdr[6]` bytes). The type directory can be parsed with [`../../scripts/igb_dir.py`](../../scripts/igb_dir.py)
and the object records with [`../../scripts/igb_inst.py`](../../scripts/igb_inst.py); resolving generator → `_playerDataList` → item tables goes
through the pack's id remap table (§6).

The object **payloads** decode cleanly (names, rows, rates all coherent). The
reference fields and the list element arrays are **pack-local ids** — not object
indices, and not monotone with file order — that index the pack's own remap table,
so the pointers are followed through that table (§6).

**Cross-check against a live read:** the table *counts* and the *contents*.
`obje_live.json` (read from a save state) was matched against the packs by
(category, id, rank, rate) tuples, and the counts line up exactly, e.g. for
`stagGF01`:

| pack OneList count | table |
|---|---|
| 0 | `comonNOTG01` (the "no drop" table — live-verified empty) |
| **17 / 37 / 30** | `nZ1obje1` / `hZ1obje1` / `vZ1obje1` |
| 11 / 25 / 21 | `nZ1gobr3` / `hZ1gobr3` / `vZ1gobr3` |

Self-consistency check: the pack holds 139 `beGeneraterItemDataOne` objects; the
Guard Room's object tables reference 84 of them (83 distinct, 1 shared) and the
Goburimon tables 57 (56 distinct, 1 shared) → **83 + 56 = 139 exactly**.

## 5. The Guard Room (`stagGF01`) destructible boxes

The Guard Room's breakables are:

* generator **`GWCS-05`**, stat row **378 = `g_woodencasez05`** — the wooden cases.
  (The walkthrough counts ten boxes in the room, one of them the trap; the pack
  contains exactly one `beGeneraterPlayerData` with `_geneCount = 9`, which is
  *suggestive* of the nine plain cases but is not proven to belong to `GWCS-05`);
* Lua-placed `MODELCTRL` props (entry 772 `chunk_0009`):
  `g_breakinggatez05` ×4 and — the walkthrough's "trap box" — **`g_trapboxz05`** ×1.

`stagGF01`'s pack contains only two drop pools, `Z1gobr3` and `Z1obje1`, so the
Guard Room's breakable pool is **`Z1obje1`**, at the three difficulties
(Normal / Hard / Very Hard):

### `nZ1obje1` — Normal — 17 entries, Σ = 4330/10000 (43.3 % chance of any drop)

| category | id | rank | rate | P | item |
|---|---|---|---|---|---|
| `weapon` | 0 | 0 | 100 | 1.0 % | Battle Hawk |
| `weapon` | 25 | 0 | 100 | 1.0 % | Long Sword |
| `weapon` | 50 | 0 | 100 | 1.0 % | Dyno Tooth |
| `weapon` | 75 | 0 | 100 | 1.0 % | Kamikiri Maru |
| `armor1` | 18 | 0 | 60 | 0.6 % | Element Core α ᴵ |
| `armor1` | 9 | 0 | 60 | 0.6 % | Cipher Core α ᴵ |
| `armor1` | 0 | 0 | 60 | 0.6 % | Brave Core α ᴵ |
| `insItem` | 0 | 0 | 1000 | 10.0 % | install item |
| `insItem` | 0 | 1 | 600 | 6.0 % | install item |
| `insItem` | 0 | 2 | 300 | 3.0 % | install item |
| `insItem` | 0 | 3 | 100 | 1.0 % | install item |
| `insItem` | 0 | 4 | 50 | 0.5 % | install item |
| `conItem` | 0 | 0 | 1000 | 10.0 % | consumable |
| `conItem` | 3 | 0 | 100 | 1.0 % | consumable |
| `conItem` | 1 | 0 | 300 | 3.0 % | consumable |
| `conItem` | 7 | 0 | 150 | 1.5 % | consumable |
| `conItem` | 8 | 0 | 150 | 1.5 % | consumable |

### `hZ1obje1` — Hard — 37 entries, Σ = 6050/10000 (60.5 %)

| category | ids | rate each | item |
|---|---|---|---|
| `weapon` | 8, 33, 58, 83, 108, 133, 158, 233 | 200 | Van Blade · War Sword · Red Moon · Kurogane Maru · Rage Hammer · Slasher · Light Blade · Pain Scimitar |
| `weapon` | 183, 208 | 150 | Hook Katar · Sword Cannon |
| `weapon` | 7, 32, 57, 82, 107, 132, 157, 232, 182, 207 | 200 | same eight models at the next grade + Hook Katar / Sword Cannon |
| `weapon` | 4, 29, 54, 79, 104, 129, 154, 229, 179, 204 | 100 | Battle Hawk · Long Sword · Dyno Tooth · Kamikiri Maru · Dbl Axe · Bone Blade · Dbl Rapier · Grand Blade · Mighty Talon · Beam Magnum |
| `armor1` | 19, 10, 1 | 100 | Element / Cipher / Brave Core **β** ᴵ |
| `insItem` | 0 (rank 0) | 250 | install item |
| `conItem` | 1 / 4 / 2 | 300 / 200 / 100 | consumables |

### `vZ1obje1` — Very Hard — 30 entries, Σ = 5910/10000 (59.1 %)

| category | ids | rate each | item |
|---|---|---|---|
| `weapon` | 20, 45, 70, 95, 120, 145, 170, 245, 195, 220 | 10 | Soul Burn · Onslaught · Dragoon · Ankokuten · Meteor Force · Doom Bringer · Photon Edge · **Infinity** · Drill Bunker · Omega Raptor |
| `armor1` | 24, 15, 6 | 20 | Divine / Wizard / Vulture Core α ᴵ |
| `armor2` | 26, 23, 20, 17, 14, 11, 8, 5, 2 | 10 | boards (ids in the `armor2` sub-table) |
| `insItem` | 0 (rank 0) | **4000** | install item — 40 % of all breaks |
| `conItem` | 1 / 4 / 2 / 5 / 9 / 7 / 8 | 500 / 50 / 300 / 10 / 100 / 600 / 100 | consumables |

All names in this table were resolved from the game's own item tables in RAM
(§5b) — nothing is inferred from the file names. Weapon ids resolve
through `item_ids.json` (verified, 52 models × stride 5, so id = 5·model + grade
and a weapon's grade is part of its name here, e.g. `Battle Hawk ε`). `armor1`
ids are cores (9 models × 3 grades, order Brave, Aegis, Vulture, Cipher, Astral,
Wizard, Element, Spirit, Divine), `armor2` ids are boards
(14 models × 3 grades, order Achilles, Atlas, Meteor, Fire, Ice, Bolt, Dark,
Armor, Beast, Rack, EXP, BIT, Mana, Resist — `docs/systems/items.md`), `insItem` is
the sub-slot family (BIT, x-data and the plugs, §5b) and `conItem` indexes the 12-row
consumable table.

**Shape of the table:** a case pays an install item or a consumable far more often
than gear (21 % + 16 % on Normal vs ~4 % for weapons+cores). On Very Hard the table
becomes *mostly* one install item (40 %) plus a shot at the top-tier grade-less
weapons (Infinity, Omega Raptor, …) at 0.1 % each.

### The Guard Room's Goburimon tables (`Z1gobr3`) — live, resolved

**All 23 enemy generators in `stagGF01` point at the same three lists** (verified:
every one of them resolves to `nZ1gobr3`/`hZ1gobr3`/`vZ1gobr3`, and each table's
content is identical across all of them, so *which* Goburimon dies cannot matter).
The one exception is **`GENE-19`**, whose three lists are all `comonNOTG01` — **0
entries, i.e. it can never drop anything** (that is the 14-enemy wave the stage script
starts after the breakable gate is cracked, `01-fortress-gate_e772/017-damage-calc-3.lua`).
Rows 0 and 2 (`_geneEnemyId`) are both ordinary `e_goburi` rows.

The live split of the three lists is 11 / 25 / 21 = 57 references.

**Normal** (`nZ1gobr3`) — 11 entries, Σ 3502/10000 = **35.02 %** drop chance

| category | id | rank | rate | = item |
|---|---|---|---|---|
| `insItem` | 0 | 0 | 1600 (16.00 %) | BIT |
| `conItem` | 0 | 0 | 500 (5.00 %) | HP Disk α |
| `conItem` | 7 | 0 | 300 (3.00 %) | Raise Disk |
| `weapon` | 0 | 0 | 250 (2.50 %) | Battle Hawk α |
| `weapon` | 25 | 0 | 250 (2.50 %) | Long Sword α |
| `weapon` | 50 | 0 | 250 (2.50 %) | Dyno Tooth α |
| `weapon` | 75 | 0 | 250 (2.50 %) | Kamikiri Maru α |
| `conItem` | 8 | 0 | 50 (0.50 %) | Gate Disk |
| `conItem` | 11 | 0 | 30 (0.30 %) | Key Chain |
| `conItem` | 10 | 0 | 20 (0.20 %) | B. Pack |
| `insItem` | 1 | 0 | 2 (0.02 %) | x-data |

**Hard** (`hZ1gobr3`) — 25 entries, Σ 3170/10000 = **31.70 %** drop chance

| category | id | rank | rate | = item |
|---|---|---|---|---|
| `insItem` | 0 | 3 | 600 (6.00 %) | BIT |
| `conItem` | 1 | 0 | 200 (2.00 %) | HP Disk β |
| `conItem` | 8 | 0 | 200 (2.00 %) | Gate Disk |
| `weapon` | 9 | 0 | 150 (1.50 %) | Van Blade ε |
| `weapon` | 34 | 0 | 150 (1.50 %) | War Sword ε |
| `weapon` | 59 | 0 | 150 (1.50 %) | Red Moon ε |
| `weapon` | 84 | 0 | 150 (1.50 %) | Kurogane Maru ε |
| `weapon` | 184 | 0 | 150 (1.50 %) | Hook Katar ε |
| `weapon` | 209 | 0 | 150 (1.50 %) | Sword Cannon ε |
| `weapon` | 109 | 0 | 100 (1.00 %) | Rage Hammer ε |
| `weapon` | 134 | 0 | 100 (1.00 %) | Slasher ε |
| `weapon` | 159 | 0 | 100 (1.00 %) | Light Blade ε |
| `weapon` | 234 | 0 | 100 (1.00 %) | Pain Scimitar ε |
| `weapon` | 8 | 0 | 80 (0.80 %) | Van Blade δ |
| `weapon` | 33 | 0 | 80 (0.80 %) | War Sword δ |
| `weapon` | 58 | 0 | 80 (0.80 %) | Red Moon δ |
| `weapon` | 83 | 0 | 80 (0.80 %) | Kurogane Maru δ |
| `weapon` | 108 | 0 | 80 (0.80 %) | Rage Hammer δ |
| `weapon` | 133 | 0 | 80 (0.80 %) | Slasher δ |
| `weapon` | 158 | 0 | 80 (0.80 %) | Light Blade δ |
| `weapon` | 183 | 0 | 80 (0.80 %) | Hook Katar δ |
| `weapon` | 208 | 0 | 80 (0.80 %) | Sword Cannon δ |
| `weapon` | 233 | 0 | 80 (0.80 %) | Pain Scimitar δ |
| `insItem` | 1 | 0 | 50 (0.50 %) | x-data |
| `insItem` | 2 | 0 | 20 (0.20 %) | x-data |

**Very Hard** (`vZ1gobr3`) — 21 entries, Σ 4050/10000 = **40.50 %** drop chance

| category | id | rank | rate | = item |
|---|---|---|---|---|
| `insItem` | 0 | 0 | 900 (9.00 %) | BIT |
| `insItem` | 0 | 2 | 500 (5.00 %) | BIT |
| `insItem` | 0 | 4 | 400 (4.00 %) | BIT |
| `conItem` | 0 | 0 | 300 (3.00 %) | HP Disk α |
| `conItem` | 8 | 0 | 200 (2.00 %) | Gate Disk |
| `conItem` | 10 | 0 | 200 (2.00 %) | B. Pack |
| `conItem` | 11 | 0 | 200 (2.00 %) | Key Chain |
| `conItem` | 1 | 0 | 150 (1.50 %) | HP Disk β |
| `conItem` | 7 | 0 | 100 (1.00 %) | Raise Disk |
| `weapon` | 20 | 0 | 100 (1.00 %) | Soul Burn α |
| `weapon` | 45 | 0 | 100 (1.00 %) | Onslaught α |
| `weapon` | 70 | 0 | 100 (1.00 %) | Dragoon α |
| `weapon` | 95 | 0 | 100 (1.00 %) | Ankokuten α |
| `weapon` | 117 | 0 | 100 (1.00 %) | Fang Smasher γ |
| `weapon` | 142 | 0 | 100 (1.00 %) | Dark Crimson γ |
| `weapon` | 167 | 0 | 100 (1.00 %) | Flame Rose γ |
| `weapon` | 192 | 0 | 100 (1.00 %) | Nova Blade γ |
| `weapon` | 217 | 0 | 100 (1.00 %) | Sphere Nova γ |
| `weapon` | 242 | 0 | 100 (1.00 %) | Strider γ |
| `conItem` | 2 | 0 | 50 (0.50 %) | HP Disk γ |
| `insItem` | 2 | 0 | 50 (0.50 %) | x-data |

**The "last enemy" list is inert here.** `FUN_00384800`'s caller picks
`_itemLastDataList` (+0x14) instead of `_itemDataList` (+0x10) when the generator is
down to its final enemy (`0x384948: bne v0,v1` then `lw v0,20(a0)` vs `lw v0,16(a0)`).
**All 24 spawners in `stagGF01` have the two lists byte-identical**, so the rule never
changes a roll in this stage — nothing in the fortress is a guaranteed drop.

**`_isPerfectDrop` is not at `0x5050b8`.** That address holds the
*reflection name string* `"_isPerfectDrop"` (the next string is `beFontInfo`), not the
flag. The engine does have a `PERFECTDROP` generator method (index 5 of the name table
at `0x4c6b50`), but **no Lua script in the game ever calls it** (`grep PERFECTDROP`
over `lua/`: 0 hits), so there is no reachable
"always drop" state in normal play.

### The container pool (`Z1cont1`) — "boxes", and the bit barrel (`Z1bit`)

Read live out of **`stag0101`** (Valley Entrance, in front of the Goblin Pass gate). This state has both prop
families side by side, which settles the family→pool map by direct observation:

| generator | row | pool | that is |
|---|---|---|---|
| `GBOX-01` | 371 | `n/h/vZ1cont1` | the square **box/crate** |
| `GBRL-01` | 372 | **`nZ1bit`** / `hZ1obje1` / `vZ1obje1` | a **barrel** (count 1) |
| `GBRL-02` | 372 | `n/h/vZ1obje1` | a **barrel** (count 4) |

So: **cases and barrels share `Z1obje1`, boxes/containers use `Z1cont1`** — and one
barrel generator in this stage is pointed at a Normal-only list `nZ1bit`, which is
just two entries:

| pool | entries | Σ / 10000 | drop chance | what it gives |
|---|---|---|---|---|
| `nZ1cont1` | 20 | 7150 | **71.50 %** | consumables-heavy: HP Disk α 12 %, HP Disk β 10 %, MP Disk α 10 %, MP Disk β 8 %, **Raise Disk 8 %**, three α cores 3 % each, Gate Disk 2 %, four starter weapons 2 % each, Recovery 1 %, Beam Magnum 1 %, five α boards 0.5 % each |
| `hZ1cont1` | 32 | 4270 | **42.70 %** | HP/MP Disk α–γ, Raise Disk 2 %, B. Pack 1.2 %, ten β boards 0.5 % each, ten α weapons 0.5 % each |
| `vZ1cont1` | 46 | 6720 | **67.20 %** | HP Disk β 20 %, HP Disk γ 15 %, BIT 12 %, then the only **`abChip`** drops found in any table so far (12 chips at 0.2 % each) plus α/β/γ boards and ten α weapons 0.5 % |
| `nZ1bit` | 2 | 6000 | **60.00 %** | `insItem` 0 rank 0 at 45 % + rank 1 at 15 % — **BIT only** |

#### The special Normal-only lists (`Z1gate`, `Z1bit`)

**Two more generators in this stage are pointed at Normal-only lists and fall back to
`h/vZ1obje1` on the other difficulties** — a pattern worth knowing before reading any
Normal column as "the" table:

| generator | row | Normal | Hard / Very Hard |
|---|---|---|---|
| `GWCS-01` | 375 | **`nZ1gate`** | `hZ1obje1` / `vZ1obje1` |
| `GBRL-01` | 372 | **`nZ1bit`** | `hZ1obje1` / `vZ1obje1` |

`nZ1gate` is two entries summing to **exactly 10000** — a guaranteed drop:

| pool | entries | Σ | Gate Disk | Raise Disk |
|---|---|---|---|---|
| `nZ1gate` | 2 | 10000 | **8500 (85.00 %)** | 1500 (15.00 %) |

That is the *gate case* — one per stage (`GWCS-01`, model `g_woodencasez01` in the
`g_woodencasez` family, the same family as `GWCS-05` = `g_woodencasez05`). It is why a
player reports "the box by the gate gives Gate Disks ~90 % of the time on Normal"
while the crate tables above say 1.5 %: **both are true, of different cases.** On
Hard and Very Hard the gate case reverts to the ordinary crate list, so the Gate Disk
really is 1.5 % there. Verified against a player report. The gate case is not part of
the `GBOX`/`Z1cont1` container family.

#### The raise case (`nZ1reizu`) and the epic weapon pools

Two further specials in the same stage:

| pool | entries | Σ | contents |
|---|---|---|---|
| `nZ1reizu` | 2 | 10000 | `conItem` 7 (Raise Disk) **9000 (90.00 %)** + `insItem` 0 rank 0 1000 (10.00 %) |
| `comonEPIC01`–`16` | 1 each | 10000 each | one guaranteed grade-less unique weapon each, weapon ids **250–265** |

`nZ1reizu` is the *raise case* (`GWCS-03`, Normal only, same fallback rule as the gate
case). The sixteen `comonEPIC` pools are used by `GENE-e00`–`e15` (all stat row 636) —
sixteen guaranteed-unique-weapon spawns. Of the RAM images examined they appear only in
`stag0101`. Every `comonEPIC` entry carries `_rank` 200, a value seen in no other list; its
meaning is unknown, and the drop path does not read `_rank`. Weapon ids 256–265 are unnamed in `dw4_itemnames.py` (its model list ends
at 255, and the id space extends at least to 276 — see the `vZ1cont1` row above).

#### Auditing a stage for missed tables

Dumping only the pools that look familiar misses the gate, raise and bit containers.
The general failure mode is a generator whose
**three difficulty lists are not one family**, so `check_pools.py <ram.bin>` reports:

* generators whose `n`/`h`/`v` list names differ in their stem (a special list),
* generators whose `_itemLastDataList` (+0x14) differs from `_itemDataList` (+0x10),
* every distinct list the stage references, so nothing stays undumped by accident.

| RAM image | stage | specials | `last` ≠ `item` |
|---|---|---|---|
| `/tmp/gf01.bin` | `stagGF01` | none | none |
| `/tmp/goblin_pass.bin`, `snapshots/crown6.bin` | `stag0101` | `nZ1gate`, `nZ1reizu`, `nZ1bit`, `comonEPIC01`–`16` | none |
| `snapshots/{before,after}_spawn.bin`, `pink_ram.bin`, `nc_ram.bin` | `stag0102` | none | none |

**Consequence for the tables above:** the `stagGF01` crate and enemy tables (this
document's §5 and §5c) are complete — that stage has no special or last-enemy lists.
Stages with no RAM image captured remain unaudited.

Method: dump each named list out of a RAM image; enumerate every pool a stage's generators
reference so nothing stays undumped by accident.

**This also confirms the shared-pool claim by content, not just by name:**
`nZ1obje1` in `stag0101` is byte-identical to `nZ1obje1` in `stagGF01` (17 entries,
Σ 4330, same weights), and likewise `hZ1obje1` (37, Σ 6050). Different packs, same
authored list.

**Known naming gaps** in the item-name mapping exposed by `vZ1cont1`
(model lists are too short): `armor1` id 31, `armor2` id 44, `weapon` 276, and all 12
`abChip` ids print unresolved. The ids grade by rule but the model order tables need
extending.

### Reference — the Goblin Fortress boss (`stagGF03`)

`GENE-00` row 60 = `e_mecha4`, tables `n/h/vZ1mec41`; **Normal is exactly
10000/10000** (a guaranteed drop): `weapon` 175 (Mighty Talon) 250, `weapon` 200
(Beam Magnum) 250, `insItem` 1 @7000, `insItem` 2 @2500. Hard = 34 entries
Σ 9400, Very Hard = 25 entries Σ 8730. The stage's generator packs `787/788/789`
hold only these `Z1mec41` boss tables; they have no object table.

## 5b. Item names — how (category, id, rank) becomes a display name

The display names are **not** in the ELF and not in the Lua. They live in the loaded
**`AREA.AFS` entry 9 igBinary object graph in RAM**, as **one string column per
category**, each row being `{NAME, MODEL/slot, DESCRIPTION}` — except weapons, which
use 4 rows per item `{name, model, stat, description}`. The columns are found with the
standard string-column pattern (`col + 0x34` → container → `+0x10` → data array of
string objects → `+8` = text):

| category | column | data array | rows | id rule |
|---|---|---|---|---|
| `weapon` | `0x174c210` | `0x17597a0` | 4 per item | `id = model*5 + grade` (α–ε) |
| `armor1` (cores) | — | — | 3 per item | `id = model*3 + grade` (α–γ) |
| `armor2` (boards) | — | — | 3 per item | `id = model*3 + grade` (α–γ) |
| `insItem` | `0x1749658` | `0x174a2b8` | 3 per item | family id (see the warning below) |
| `conItem` | `0x17475c8` | `0x17530f0` | 3 per item | `id = row` (12 rows) |
| `abChip` (chips) | `0x17444c0` | `0x1746bc8` | 3 per item | `id = row` |
| plugs / BIT | `0x1749658` | `0x174a2b8` | 3 per item | `id = row` |

* **`insItem` = the sub-slot family**: `BIT`, three `¶ Data` entries, then eleven plug
  types × 2 variants (`Strgth.↑Plug`, `Def.↑Plug`, `MaxHP/MaxMP/Wisdom/Spirit/Speed↑Plug`,
  `⊂/⊃/∪/∩↑Plug`), slots `g_000bit` / `g_000xdata1` / `g_000xdata2`.

  **Naming:** the row that can be misread as `P Data` is
  **x-data** — confirmed in game. Its display string is `b"\x81\xf7 Data"`
  (CP932 `0x81F7` = U+00B6 PILCROW, not a "P"), its model/slot string is `xdata`
  (hence `g_000xdata1/2`) and its pickup icon is an X. Other items in the same table
  use *different* symbol bytes — `0x81B8` (∈) for `Data_Destroyer`, `0x81C9` (∨) for
  `BIT_Board_α`, `0x81BC`–`0x81BF` (⊂⊃∪∩) for the four elemental plugs, `0x81AA` (↑)
  for the stat plugs — so the symbol byte carries meaning and must not be flushed to
  ASCII. A pick-up of this entry was watched on screen: it grants **5** of the item.

> **⚠ Do not attribute the 20-element × 5-grade table (`0x174be70`, Petty Fire … ∞ Bind)
> to `insItem`.** That is the **`wazaPanel`** technique table. The game's database name
> list (RAM `0x17dd1e0`, alphabetical) is
> `abChip armor1 armor2 conItem eneatk enemy impItem insItem pcTech shinka weapon wazaPanel`
> — `insItem` is a distinct DB from `wazaPanel`/`pcTech`/`eneatk`. Attributing that table
> to `insItem` produces a false "skills drop from crates" claim.
>
> **Settled live:** forcing `insItem id 0` in the Guard Room's live table drops the
> **bit item** (seen on the ground); the same id at `rank 4` drops the *same* item, so the
> repeated rows are one item at five probabilities and the `rank` field is not read by the
> drop path. The insItem rows do pay out, so the 43.3 % Normal figure is real.
* **Consumables** in id order: HP Disk α/β/γ, MP Disk α/β/γ, Cure Disk, Raise Disk,
  Gate Disk, Recovery, B. Pack, Key Chain (12 rows — matching the highest `conItem`
  id in any drop table, 11).
* Resolver: the item-name mapping..

Caveat: the drop routine as decompiled passes only the id + the category ordinal on to
`MODELCTRL … GENERATE` and does not visibly read `beGeneraterItemDataOne +0x10`, so the
meaning of the `rank` field is unresolved — see the warning above.

## 6. Fully offline

The table counts, the object references and the element arrays are all static:

* object-reference fields and the list element arrays store **ids** that index the pack's
  own **remap table** (between the blob's two object sections), so any id resolves to its
  record offline — `scripts/igb_ids.py`. The table's object entries *are* the
  record order, with the objects' memory blocks interleaved; reading the ids as a "loader
  instantiation order" numbering is a misreading of that table. No live RAM is involved.
* a list is serialised as `{u32 count, u32 capacity, u32 X}` and **`X` is an ordering key,
  not an offset**: lay the lists out in ascending `X` and the pool reconstructs exactly
. The Hard and Very-Hard arrays do not overlap because each list's block is placed
  by its key, not indexed by `X`.

So a stage's drop rows read from the file: `beGeneraterData._playerDataList` ->
`beGeneraterPlayerDataList` -> `beGeneraterPlayerData._itemDataList` ->
`beGeneraterItemDataList` -> `beGeneraterItemData` -> `_dataList` ->
`beGeneraterItemDataOneList`, whose elements resolve to `beGeneraterItemDataOne` rows with
their category name and `_id`/`_rank`/`_rate`. Worked example: **entry 622 yields 895 rows**
(`conItem id=3 rank=0 rate=150`, `armor1 id=9 rank=0 rate=600`, `insItem id=3 rank=0
rate=1600`, ...). The live-save recipe below is a way to cross-check a table, not a
requirement.

The three difficulty-tier packs of a stage do not split the drop table:
stag0102's three tier packs (622/623/624) carry the **same** 772-row drop table, differing
only in `_geneEnemyId` (the enemy stat-row band), so there is nothing to split — the
difficulty axis between the packs is entirely in `_geneEnemyId`.

## 7. Reproducing

The method, in five steps:

1. **stage → pack** — read the `beFileListInfo` manifest to find the stage's generator pack
   (entry 161 for `stagGF01`).
2. **pack → tables** — parse the pack (`.igb`) and list the tables it contains (entry 773 holds
   `GWCS-05` on row 378).
3. **live resolution** — extract `eeMemory.bin` from a `.p2s` with
   [`../../scripts/p2s_ram.py`](../../scripts/p2s_ram.py) and walk the generators named `GWCS`.
4. **validate** — check the static decode against the live tables by the consistency search above.
5. **names** — resolve any `(category, id, rank)` through the item-name mapping
   (`../../data/item_names.txt`).

### Proving a table entry in the running game

To find out what an entry actually *gives*, neutralise the table and force it:

Read 32 MB of EE RAM (over PINE, or offline out of a save state), locate the live generator's
tables (`GWCS-05` = the Guard Room crates), then zero every `rate` in the list, set exactly one
entry — addressed by its `(category, id, rank)` triple — to `10000`, and smash a crate.

* Entry layout: `rate` = `entry + 0x14`, and `entry` comes from the OneList data array.
* With one entry at 10000 and the rest at 0 the chosen entry is deterministic, so the item
  that appears is that entry — the fastest way to identify any drop row.
* Match entries by the **category string** at `entry + 0x08`, which addresses any
  category/id/rank in any of the three difficulty tables.
* Difficulty matters: only the table for the save's difficulty is read. Zeroing the other
  two and still getting drops proves which one is live (Normal, for the dev-world states).
* **Restore the rates when done** — they are live memory, and the game keeps playing.

## 8. Open

* The `insItem` `rank → grade` plumbing (see the §5b caveat).
* Whether `_itemLastDataList` differs from `_itemDataList` for any real generator
  game-wide. In `stagGF01` all 24 spawners have them byte-identical (§5), so the
  last-enemy rule is inert there; a different stage could make the final enemy of a
  group a guaranteed drop.
* Whether the Lua-placed `MODELCTRL` props (`g_trapboxz05`, `g_breakinggatez05`) roll
  anything at all — they have no generator, so by §1 they currently cannot.


## 9. Stage generators (World 1 sweep)

A sweep of World 1 — 4 overworld rooms, the 7 `dng1**` dungeon floors, the 4 Goblin Fortress
rooms and one boss arena — settled several questions about how generators and their lists are
authored. (The per-room catalogue built from it is a working artifact, not part of this repo.)

### Which world a stage belongs to

Every generator's drop list is named `<difficulty>Z<world><family><variant>` — so the
**zone digit is the world**: `Z1` Death Valley, `Z2` Dry Land, `Z3` Venom Jungle.
Verified both ways on `dng101b1` (all `Z1*`, banner "Death Valley") and `dng204b1`
(all `Z2*`, banner "Dry Land"). The `dng<world>**` numbering agrees with it.

**Exception — boss arenas.** Their chest lists are *stage-local*: `n/h/vBS01cont1`,
`BS02cont1`, `BS03cont1`, … with no `Z` zone at all, so the pool test cannot place them.
Use the area named on the arena's own load banner (`stagBS02` → Dry Land, `BS03` → Venom
Jungle, `BS04`–`06` → Machine Pit).

### Boss chests are not authored spawns

Each boss arena carries exactly **one** destructible generator, yet beating a boss spawns
about **four chests**. They are created by the script on the kill and roll the arena's own
`<stage>cont1` list. So an arena's generator data alone does not describe its loot, and a
"1 destructible" reading there is correct rather than a failed parse. `stagBS04` and
`BS05` have no `cont1` list at all; `BS06` does.

### The `ML` and `IS` families have no drop tables

Verified by dump: `stagML11` (main lobby) and `stagIS20` both contain **zero generators**,
so no table exists to document. `ML` is the hub and its menus; `IS` is menu and
intro/ending cinematic content. Consequence for routing: warping back to `stagML11` after
the Goblin Fortress returns to a hub with nothing on it.

### Notes from loading stages for a dump

The engine's own stage select (see [`dev-stage-debug-menu.md`](dev-stage-debug-menu.md) §6) reaches every
stage, so it is the way to load one. Reading a stage means: select the destination, confirm from
the game's own load log that the requested stage loaded (retry once otherwise), then take the RAM
out of a save state. Pitfalls that cost real time:

* **Arrival briefings are multi-page and appear *after* the load** (Numenume River's is
  several screens). Pressing a fixed number of times either misses them or fires into a
  menu. "Has the frame stopped changing" is the **wrong** test — a playing game changes
  constantly; the functional test is whether the character can move.
* **A dump taken mid-load is partially instantiated.** `stagGF03` first parsed as one
  generator because the state was saved during the load. The load log is written early, so
  a verified load does not mean the stage is playable yet.
* The dev-menu cursor starts on `つぎのページ`, so list entry *k* needs **k+1** stick-downs,
  and screen *n* needs **n−1** Cross presses. Drive it with the analog stick (the d-pad was ignored on the pre-fix virtual pad; retail menus accept it on a working pad).

### Reading the room names off the load banners

Each banner shows the room name in the top band and the area name in the bottom band,
both over a "Now Loading" pattern. Cropping the two bands and reading them with OCR works for
most banners but **mangles the area name** where the text sits over the pattern, so the
folder-naming step prefers a known area name over raw OCR; the unreadable banners were read by
hand.

### What is left

Worlds 2–4 proper: the `stag02**`/`03**`/`04**` overworld stages, the `dng2**`/`dng3**`/
`dng4**` dungeons and the `dngq*` family. The zone test classifies each as it is dumped.
