> **NOTE (findings [#172](../findings/findings-0001-0250.md#f172)/#255):** the enemy stat table is *plain data inside the ISO*
> (`AREA.AFS`, 665 identical copies) and can therefore be rewritten directly in the disc image:
> changing a stat is a data patch, not a RAM-side patch — see [`../engine/afs-archives.md`](../engine/afs-archives.md).
>
> **Row coverage (finding [#255](../findings/findings-0251-0500.md#f255)):** the 649-row table holds 580 live rows
> — all **31 `e_*`** types (regular enemies + area bosses) and **8 `f_*` story-boss rows**
> (`f_apocaly`, `f_belvam`, `f_luce`, `f_luce2`, `f_devl1`, `f_devl1b`, `f_devl22`, `f_devl3`),
> plus 9 `g_*` destructibles. The many other `f_*` model variants
> listed below (`f_devl1c/e/f/f2/f3`, `f_devl2`, `f_devl21-26/250`, `f_devl31/31g/32`,
> `f_luce1`) have **no row of their own** and are believed to reuse their family's row — not
> yet proven. The 69 empty rows are unused slot-grid cells (HP 0, no model).

# 16 — Enemy Roster & Stat DB

Full enemy list plus the decode of the enemy **stat** data.
Stats are NOT in the save file — they live in the igBinary object graph inside
`NDMW.AFS` / `AREA.AFS` (see [`docs/engine/igbinary-format.md`](../engine/igbinary-format.md)).

## Enemy model namespaces

Three namespaces hold fightable models. `m_*` (playable as monsters) and `s_*`/`q_*`
are NOT enemies; `n_*` single-letter names are texture/material noise, not models.

| Prefix | Meaning | Count |
| --- | --- | --- |
| `e_*` | regular enemies + area bosses | 31 |
| `f_*` | story bosses (the "devil" family + Apocalymon/MaloMyotismon/Lucemon) | 26 |
| `n_*` (digimon only) | NPCs (Leomon, Seraphimon, Ophanimon, Mamemon, Gekomon, Metete, Recorder) | 7 |

### `e_*` — 31 regular enemies

| Model | Display name (US) |
| --- | --- |
| `e_anomalo` | **Scorpiomon** (= Anomalocarimon in JP) |
| `e_arachne` | Arukenimon |
| `e_blosso` | Blossomon |
| `e_cockatri` | Kokatorimon (Cockatrimon) |
| `e_diabolo` | Diaboromon |
| `e_geko` | Gekomon |
| `e_goburi` | Goburimon |
| `e_impdra` | Imperialdramon |
| `e_infermo` | Infermon |
| `e_ldknight` | LordKnightmon |
| `e_mammos` | Mammothmon |
| `e_maridevi` | MarineDevimon |
| `e_mecha1` | Machinedramon v1 |
| `e_mecha2` | Machinedramon v2 |
| `e_mecha3` | Machinedramon v3 |
| `e_mecha4` | Machinedramon v4 |
| `e_mecha4bs` | Machinedramon v4 (boss) |
| `e_mecha5` | Machinedramon v5 |
| `e_megadra` | Megadramon |
| `e_minotaru` | Minotarumon |
| `e_mummy` | Mummymon |
| `e_nume` | Numemon |
| `e_ogre` | Ogremon |
| `e_otama` | Otamamon |
| `e_pharaoh` | Pharaohmon |
| `e_rare` | Raremon |
| `e_scum` | Sukamon |
| `e_skulgrey` | SkullGreymon |
| `e_tonogeko` | TonosamaGekomon |
| `e_torta` | Tortomon |
| `e_tyrano` | Tyrannomon |

Sub-variants present as models: `e_mecha2st0203`, `e_mecha4dn`, `e_mecha5dn`,
`e_rare02`, `e_nume_skin0Shape2` (skin, not a distinct type).

### `f_*` — 26 boss models

| Model | Enemy | Family |
| --- | --- | --- |
| `f_apocaly` | Apocalymon | boss |
| `f_belvam` | MaloMyotismon | = BelialVamdemon |
| `f_devl1` (+`b/c/e/f/f2/f3/h/i`) | **Devimon** | 9 variants |
| `f_devl2`, `f_devl21`–`f_devl26` (+`250`) | **Myotismon** | 8 variants |
| `f_devl3`, `f_devl31`, `f_devl31g`, `f_devl32` | devil-family v3 (name TBD) | 4 variants |
| `f_luce`, `f_luce1`, `f_luce2` | **Lucemon** | 3 forms |

Display names confirmed in `AREA.AFS` text: `Devimon`, `Myotismon`,
`MaloMyotismon`, `Lucemon`, `Scorpiomon`, `Apokarimon` (=Apocalymon), etc.
The `f_devl3*` display name is not yet confirmed (no `Daemon`/`VenomMyotismon`
string found).

### `n_*` digimon NPCs

`n_leomon` (Leomon), `n_seraph` (Seraphimon), `n_ofanim` (Ophanimon),
`n_prmame` (Mamemon), `n_gekoa` (Gekomon NPC), `n_metete` (Metete),
`n_recorder` (Recorder). These are **regular NPCs, not bosses**.

## Stat DB location

- **`beBaseInfoData`** — type name refs in `AREA.AFS`; a "×667" instance count is a
  miscount of the stat table's 665 copies (§"The enemy stat table" below).
- **`beNDMWStatusInfo`** — 88 instances in `NDMW.AFS` (≈ 64 enemies/NPCs + playable).
- Field model: the **names** `hp mhp mp mmp level lv def power hit waza
  no kazu` + `stun sleep poison guard powerdown attackdown` (18 total) exist as
  strings, but they are **not** reflection field records — see
  §"Field descriptor encoding" below and finding **[#291](../findings/findings-0251-0500.md#f291)**.

### Key addresses

| Item | Address |
| --- | --- |
| AREA.AFS blob (level pack, magic `0x12a8`) | `0x72ed000` |
| …type directory (`beBaseInfo` etc.) | `0x72ee34d` |
| …enemy name hash table | `0x7300261` |
| NDMW.AFS blob (stage pack, magic `0x6300`) | `0x1055b000` |
| …`beNDMWStatusInfo` type definition | `0x1055efc4` |

## igBinary object-graph decode — current state

### Blob header (12×u32)

Every blob shares the tail `{hdr[8]=0x656, hdr[9]=0x30, hdr[10]=0xfada,
hdr[11]=0xf0000006|0xb0000006}`. The head (0..7) is file/type-specific.

**NDMW.AFS blob (`0x6300`)** — `0x1055b000`:
```
hdr[0]=0x6300   magic
hdr[1]=0x37b    MetaField type-name list (48 names, NUL-terminated)
hdr[2]=0x3960   type directory  ({name}{u32 descriptors})
hdr[3]=0xcf     type-index table (bytes)
hdr[4]=0xf86bc  OBJECT DATA (serialized instances)
hdr[5]=0x7105   index table (repeating {0x4ff,0x2000,0,x,…} records)
hdr[6]=0x1b8330 0xff padding (empty)
hdr[7]=0x2604   field-descriptor table
```

**AREA.AFS blob (`0x12a8`)** — `0x72ed000`:
```
hdr[5]=0x134d   type directory
hdr[7]=0x685    type-name strings (VertexArrayData, ImageData, …)
hdr[6]=0x33060  float/font data
hdr[4]=0x34420  object data
```

### Type directory records

`{ NUL-terminated type name }{ u32 descriptors... }`, names 4-byte aligned.

### Field descriptor encoding

Each descriptor is **6 bytes / three u16**: `{type_id, ordinal, size}`. A
4-byte `{X,Y}` reading is a mis-parse (the block is only 2-byte aligned, not 4).
`type_id` indexes the 48-name `ig*MetaField` table, `size` is the field's declared
element size, and `ordinal` is the field's **1-based slot index in the class's
flattened field-slot list**. Full write-up, the framing rule and worked examples:
[`../engine/igbinary-format.md`](../engine/igbinary-format.md) §"Field descriptor
encoding".

**Ordinal and offset (findings [#290](../findings/findings-0251-0500.md#f290)/#292):**

- `ordinal = i + K + 1` for the class's declared field `f[i]`, where `K` (the
  inherited base-slot count) is **constant per class** — over the 135 records, 93 have
  reflection fields; **87 satisfy the rule** (K = 1 ×8, 2 ×21, 3 ×30, 4 ×1, 6 ×12,
  7 ×4, 9 ×1, 10 ×8, 11 ×2), **48 of them confirmed by ≥2 descriptors** and 39 on a
  single one; 6 fail to greedy type-matching artefacts.
- The byte offset is **not in the descriptor**; it is the class's declared offset
  from `data/reflection.json`, which *is* the igBinary layout (descriptor `size` is
  the element size, not the stride — `igImage`'s bools are size 1 with stride 4,
  `igColorMaskAttr`'s are size 1 with stride 1).
- A descriptor with `ordinal <= K` matches no declared field: those are
  **inherited-slot markers**, 203 of them (`igObjectRef` 53, `igString` 50, `igInt`
  44, `igBool` 24, `igShort` 23, …), and are the loader's `"fakeField"`/`"Generated"`
  case. A declared field with *no* descriptor
  (e.g. `igLightAttr`'s `_lightId` at ordinal 5, `_vc`, `_changed`, `_cacheable`) is
  just a slot the directory does not re-state, and its omission leaves a hole
  without shifting later ordinals.

**The stat layout is *not* in the reflection dump (finding [#291](../findings/findings-0251-0500.md#f291)).**
The `beNDMWStatusInfo`/`beBaseInfo*` entries in `data/reflection.json` do not give the
stat fields' offsets:
`beNDMWStatusInfo` has `field_count 0`, `beBaseInfoData` has exactly one field
(`_version`, `igIntMetaField` @12) and `beBaseInfo` two (`_dataList` @20,
`_ramList` @24). Their igBinary directory records are equally thin
(`beNDMWStatusInfo` @NDMW blob+`0x3fc4` = `(igString,2,4)(igBool,4,1)(igObjectRef,5,4)…`;
`beBaseInfoData` @+`0x24b2` = `(igString,2,4)(igInt,3,4)`). So the hp/mhp/… layout
must come from the stat-name xrefs or from fitting the object instances — **not**
from `reflection.json`. (Consistent with finding [#288](../findings/findings-0251-0500.md#f288): the class registers no
fields of its own.)

The 48 MetaField names (string table @ `0x30`): `igObjectRefMetaField(0)
igIntMetaField(1) igBoolMetaField(2) igCharMetaField(3) igStringMetaField(4)
igRawRefMetaField(5) igEnumMetaField(6) igMemoryRefMetaField(7) …`.

### Enemy name hash table (`AREA.AFS 0x7300261`)

Entries: `{ name\0 }{ pad }{ value byte at offset ≡ 1 (mod 4) }`.
Observed value bytes: mostly `0x01`; some `0x1e`(e_ogre,e_cockatri),
`0x2e`(f_apocaly), `0x2d`(e_mecha3), `0x21`(f_luce2). Semantics TBD (category?
data index?).

### Validation anchor

"Goburimon (`e_goburi`) HP ≈ 200–600", inferred from ~57–64 damage hits, is not a
valid anchor: `e_goburi` has **several rows** in the
649-row table (row 1 → 58, row 5 → 649, rows 379-393 → the crown ladder), so a single
number cannot serve as an anchor. Any "HP ≈ N" anchor should name the **row**
(§"The enemy stat table" below) — that is the stable identifier.

## The live stat read path (corroborates [#182](../findings/findings-0001-0250.md#f182))

> **This section is corroboration.** The path is confirmed as
> finding **[#182](../findings/findings-0001-0250.md#f182)** and documented in
> [`enemy-spawn-system.md`](enemy-spawn-system.md); the table it reads from is decoded
> as **[#205](../findings/findings-0001-0250.md#f205)**. Read it as confirmation that the same conclusions reproduce
> from savestates, and for the `FUN_00394400`/`"ONE"` mechanism, which only this
> section describes.

Read out of a running game rather than decoded from the igBinary layout — which is the
project's standard for a stat claim.

### The populator: `FUN_00394400` (`0x394400`)

This is the "focus this model and refresh the cached stat block" function. Its
provenance, read off `0x394520`–`0x3945bc`:

```
container = *(model + 0x28)                       // model is the arg (MDL entity)
record    = FUN_003022c0(container, *(0x585be0), "ONE")   // key "ONE" @0x50ef60
status    = *(record + 0x14)
*(0x58a1e4) = *(model + 8)                  // RamNo
*(0x58a1e8) = *(record + 0x10) + 0x20       // transform
*(0x58a1ec) = *(*(status +  8) + 0x0c)      // field object (+0x08) -- see caveat
*(0x58a1f0) = *(*(status + 0x0c) + 0x0c)    // current HP   [= #182's [InfoWork+0x0c]+0x0c]
*(0x58a1f4) = *(status + 0x10)              // the stat-table ROW  [#182: elite-scaled stat]
*(0x58a1f8) = <name argument>               // InfoName
```

This **corroborates the confirmed finding [#182](../findings/findings-0001-0250.md#f182)**: [#182](../findings/findings-0001-0250.md#f182) establishes the current HP as
`[InfoWork+0x0c] + 0x0c` (verified
by live damage, 2816→2431) and `InfoWork+0x10` as an elite-scaled stat which it
explicitly **refutes as HP** — both true, because `+0x10` is the **row** and the crown
ladder scales that row. [`enemy-spawn-system.md`](enemy-spawn-system.md) states
the same layout (`beNDMWMdlPEBaseInfoWork`, vtable `0x53D3E0`, `+0x10` row,
`[+0x0c]+0x0c` current HP).

**Caveat on the `+0x08` label.** Calling `*(*(status+8)+0xc)` "MHP" is this page's
inference, not an established name — nothing else corroborates it. For the uncrowned
`e_goburi` it yields 649, which is the row-5 HPMAX, so `+0x08` is *plausibly* the
max-HP field object, but treat the name as unverified and check it (the same
field-object mechanism reaches current HP through `+0x0c`).

`FUN_00394400` is also the **sole writer** of the MDL block (one store site in the
whole ELF), and it re-writes HP after the UI update when HP did not change — a meter
clamp, not a second stat source.

### Measured values across savestates

`InfoName` = `*(0x58a1f8)`, MHP = `*(0x58a1ec)`, row = `*(0x58a1f4)`. The third column
is the **row into the 649-row table**, not a per-species id — that is why the same
enemy appears with different values:

| State | InfoName | row | `*(0x58a1ec)` | |
| --- | --- | --- | --- | --- |
| `normal_lvl1_before_load` | `e_goburi` | 0 | 50 | |
| `goblin_pass_crate_barrell` | `e_goburi` | 0 | 50 | |
| `normal_lvl1_before_crown_enemy` | `e_goburi` | 1 | 58 | = [#205](../findings/findings-0001-0250.md#f205)'s row 1 `e_goburi` 58 |
| `before_crown_spawn` / `before_enemy_spawn` / `no_crown` / `pink_crown` | `e_goburi` | 5 | **649** | = [#205](../findings/findings-0001-0250.md#f205)/rng-verification row 5 |
| `before_load_area` | `p_susanoo` | — | 99999 | |
| `dw4-inworld`, `op-ready`, `all_worlds_gate` | `n_digilff` | — | 100 | |

So the same enemy has **different RecNo and MHP in different stages** — RecNo is the
*instance's* row in the 649-row table, not a fixed per-species id.

### The live entity records

The same triples exist as heap records in a **72-byte-stride** table, with the name
at `+0x0c`, the record index at `+0x10` and max HP at `+0x14`:

```
+0x00  0            +0x10  RecNo
+0x04  self-ptr     +0x14  MHP
+0x08  0            +0x18  0
+0x0c  name ptr     +0x1c  0x08000281  (flags)
```

Reading the live table in `before_crown_spawn` (10 loaded entities):

| name | RecNo | MHP |
| --- | --- | --- |
| `e_goburi` ×7 | 5 | 649 |
| `e_ogre` ×2 | 36 | 662 |
| `g_boxfield` | 371 | 100 |

That is the *instantiated* set for the loaded stage. Each record is a per-instance copy
of a row of the 649-row stat table (below); there is no separate definition table.

## The enemy stat table (`AREA.AFS` / ISO)

This page owns the table ([`docs/README.md`](../README.md)
points "the 649-row stat table" here). It is findings **[#195](../findings/findings-0001-0250.md#f195)** and **[#205](../findings/findings-0001-0250.md#f205)**, both
confirmed:

| | |
| --- | --- |
| **Rows** | **649**, replicated as **665 byte-identical copies** ("×667" is a miscount of this) |
| **Where** | plain data in `AREA.AFS` / the ISO — **fully patchable without code patches** |
| **HPMAX** | `i32`, **column-major** @ ISO `0x78D64C5` |
| **12 stats** | `i16`, **row-major** @ ISO `0x78DACB9` |
| **3 bytes** | `CHIMEIRITSU`, `MAHIRITSU`, `RARITY` — `u8`, row-major @ ISO `0x78DA51D` |

Anchors from [#205](../findings/findings-0001-0250.md#f205): row 370 = destructible crate, 100 HP / 100 TSUYOSA / RARITY 0;
row 60 = boss 3194/3564; row 1 = `e_goburi` 58; 69 rows are zeroed. Only **60 of the
649 rows have `RARITY > 0`** — 4 types × 3 tiers × 5 crown ranks (`e_goburi`
379-393, `e_mummy` 394-408, `e_otama` 409-423, `e_mecha2` 610-624) — and [#205](../findings/findings-0001-0250.md#f205) decodes
the whole crown ladder from them (HP = rank1 + 100·(rank−1), TSUYOSA/KASHIKOSA
×1.25 per rank in tier 0, MAMORI +8..12/rank, SEISHIN +10/rank, EXP ×1.1^(rank−1),
colour rank1 green → 5 yellow).

**There is no 88-row table.** "88" is the `beNDMWStatusInfo` *instance* count;
the stat table is 649 rows, and a `×667`/`×88`
framing has no other provenance. See finding **[#301](../findings/findings-0251-0500.md#f301)**, refuted.

### How a live entity reaches the table

```
beGeneraterInfoWork   +0x1c _geneEnemyName (e.g. e_goburi)   (spawn system)
                      +0x20 row        +0x24 HPMAX          +0x28 1.0f
beNDMWMdlPEBaseInfoWork (vtable 0x53D3E0, the enemy InfoWork)
                      +0x10 row        [+0x0c]+0x0c current HP      (findings #182/#298)
```

So an entity carrying `(name, row, HPMAX)` in RAM is a **per-instance copy of a row**
— e.g. row 5 → 649 at `0x17ff7a0`, row 386 → 3200 for a pink-crown `e_goburi`
([`rng-verification.md`](rng-verification.md)). The same enemy type spans several rows
(1, 5, and the 379-393 crown ladder), so a single "Goburimon HP" does not exist — which
is why an "HP ≈ 200–600" anchor is unreliable.

## Next steps

> **The stats themselves are answered.** The 649-row table is decoded ([#205](../findings/findings-0001-0250.md#f205))
> and the live read path is proven ([#182](../findings/findings-0001-0250.md#f182), [#298](../findings/findings-0251-0500.md#f298)/#299). Do not hunt for another stat table:
> an "88-record `beNDMWStatusInfo` definition table" is finding **[#301](../findings/findings-0251-0500.md#f301)**,
> **refuted**, and the `×667`/`×88` counts are a miscount of [#205](../findings/findings-0001-0250.md#f205)'s 665 copies.
> Following the MDL block is not a route to the stats either — it is a cache whose
> producing chain resolves to 0 ([#300](../findings/findings-0251-0500.md#f300)).

The genuinely open work here is the igBinary **object graph** (below), not the stats.
The descriptor structure and the `ordinal` → byte offset rule are not part of it
(§"Field descriptor encoding", findings [#290](../findings/findings-0251-0500.md#f290)/#292):

1. **Walk the object instances** at `hdr[4]` (`0x34420` here) using the type
   directory, reading each field per its resolved type. The instance encoding at
   `hdr[4]` is described in [`../engine/igbinary-format.md`](../engine/igbinary-format.md)
   §"The instance encoding" (finding [#417](../findings/findings-0251-0500.md#f417)).
2. **Recover the `beBaseInfoData`/`beNDMWStatusInfo` layout** — these two classes
   have no usable field list in `data/reflection.json` (finding [#291](../findings/findings-0251-0500.md#f291)), so this is
   a prerequisite for the dump below, not a given. Start from the xrefs to the
   `hp`/`mhp`/`powerdown` strings in `data/strings.json`.
3. Dump all 88 `beNDMWStatusInfo` instances and the `beBaseInfoData` records into a
   spreadsheet, validated against a named stat-table row (§"Validation anchor"), not
   a single "Goburimon HP" figure.
