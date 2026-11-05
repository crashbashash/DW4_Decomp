# Item / Device Database

Goal: turn the device folder (`+0x6c..0x8c`, 9×u32) and weapon slots
(`+0x2e4/8/c`) into a usable save editor — i.e. know which **item ID** gives
which **item**.

## Where the item names live

The in-game item display names are **not** in the ELF and **not** in the Lua
scripts. They are in **`AREA.AFS` entry 9** (`off=0x757d800`, `size=430021`),
which is an igBinary/reflection-serialized **text + data table**.

Entry 9 mixes:
- reflection type names (`igObjectRefMetaField`, …) at the start,
- font tables (`font000`, `font010`, …),
- a string table of **type-256 records**, which hold all the text.

### Type-256 string record format
```
{u32 0x00000100}              type tag = "string"
{u32 size<<8}                 size = strlen + 12
{u32 strlen<<8}               byte length of the string
{u8  string[strlen]}          Shift-JIS text
```
(All three header words store their value in byte 1, i.e. `value<<8`.)

Scanning entry 9 for this pattern yields **1619 strings**, of which ~540 are
item names (identified by an item-type icon prefix byte `0x81b8/0x81b9/0x81c8/
0x81c9/0x81bd/…` and/or a trailing grade letter).

Grades are the fullwidth/Greek letters **α β γ δ ε** = Shift-JIS
`0x83bf 0x83c0 0x83c1 0x83c2 0x83c3` (α/β/γ/δ/ε; in-game display = A, B, Y, D, E —
gamma renders as **Y**, not C).

Full extracted list: `ghidra-projects/dw4/item_names.txt`.

## Item categories (from the name list)
| Icon prefix | Category | Examples |
| --- | --- | --- |
| `∧` (0x81c8?) | AB chips | Wisdom Chip, Speed Chip, Spirit Chip, PWR Medal (⊂⊃∩∪), Resist ROM, Defence ROM, Drain/Dread/Assault Ram |
| `∋` | Cores | Brave Core, Wizard Core, Astral Core, Divine Core, Vulture Core, Cipher Core, Element Core, Aegis Core, Spirit Core |
| `∨` | Boards (armor) | Armor Board, Dark Board, Fire Board, Ice Board, Bolt Board, Meteor Board, Achilles Board, Atlas Board, EXP Board, BIT Board, Mana Board, Beast Board, Rack Board, Resist Board, Filter Board |
| `∈` | Weapons | see below |
| `∩∪⊂⊃` | Plugs (AB?) | Plug variants |

## Weapon list (cat `∈`)
The weapons section holds ~50 **graded** weapon models (α–ε each) plus a set of
**grade-less** special weapons:

- Graded examples: Battle Hawk, Long Sword, Dyno Tooth, Kamikiri Maru,
  Crusher, Bone Blade, Victor Sword, Dragoon, Soul Burn, War Sword, Van Blade,
  Destroyer, Light Ring, Red Moon, Rune Blade, Dbl Rapier, Light Blade,
  Apocalypse, Sword Cannon, Flame Rose, Photon Edge, Rage Hammer, Kurogane Maru,
  Denji Prince, Yasha Glass, Ankokuten, Dbl Axe, Hekatoncheir, Fang Smasher,
  Meteor Force, Slasher, Tri-edge, Dark Crimson, Doom Bringer, Mighty Talon,
  Hook Katar, D Slayer, Nova Blade, Drill Bunker, Beam Magnum, Blaster Gun,
  Sphere Nova, Omega Raptor, Grand Blade, Pain Scimitar, Sword Break, Strider,
  Infinity, …
- Grade-less: Kaiser Knuckle, Demon Arm, Nosferatus, Executor, Dbl Positron,
  Plasma Blade, Blunt Axe, Slash Sword, Stab Dagger, **Bash Katana**, Blunt Edge,
  Slash Edge, Stab Edge, Bash Edge, **Crush Arm**, **Shot Pistol**, Invisible,
  Judgment, Light Bringer, Data Destroyer, Hyakki Yako, Orochi Slayer,
  Nightmare Lance.

## The string-ID table (ELF) — how a name is fetched
`0x004cda40` — 360 records, 12-byte stride, terminated by `0xFFFFFFFF`:
```
{u32 key, u32 message_id, u32 font_subtable_ptr}
key = (flag << 16) | (category << 8) | sub          (only low 20 bits used)
```
`FUN_003ebe00` does a **linear search** on `key & 0xFFFFF`, then stores the
matched record's `message_id` to `0x0058a220` ("TXT call number") and walks the
font sub-table to set up rendering.

Categories present in this table: `0x00, 0x01, 0x03, 0x04, 0x05, 0x10, 0x11`,
each ×4 flag pages (flag `0x00/0x01/0x02/0x03` → message-id bases
~200 / ~10200 / ~20100 / ~30100). The message id is the index into the entry-9
text table used by the text system (exact message-id→string resolution still to
map — see open items).

## ✅ Weapon ID table (cat 0x00) — CONFIRMED by dynamic probe
`id = model_index * 5 + grade` (grade 0–4 = α β γ δ ε). 50 graded models
(IDs 0–249) + 2 unique grade-less weapons (250, 255).

| model | id (α) | weapon |
| --- | --- | --- |
| 0 | 0x0000 | Battle Hawk |
| 1 | 0x0005 | Van Blade |
| 2 | 0x000a | Crusher |
| 3 | 0x000f | Destroyer |
| 4 | 0x0014 | Soul Burn |
| 5 | 0x0019 | Long Sword |
| 6 | 0x001e | War Sword |
| 7 | 0x0023 | Victor Sword |
| 8 | 0x0028 | Phantom |
| 9 | 0x002d | Onslaught |
| 10 | 0x0032 | Dyno Tooth |
| 11 | 0x0037 | Red Moon |
| 12 | 0x003c | Rune Blade |
| 13 | 0x0041 | Light Ring |
| 14 | 0x0046 | Dragoon |
| 15 | 0x004b | Kamikiri Maru |
| 16 | 0x0050 | Kurogane Maru |
| 17 | 0x0055 | Denji Prince |
| 18 | 0x005a | Yasha Glass |
| 19 | 0x005f | Ankokuten |
| 20 | 0x0064 | Dbl Axe |
| 21 | 0x0069 | Rage Hammer |
| 22 | 0x006e | Hekatoncheir |
| 23 | 0x0073 | Fang Smasher |
| 24 | 0x0078 | Meteor Force |
| 25 | 0x007d | Bone Blade |
| 26 | 0x0082 | Slasher |
| 27 | 0x0087 | Tri-edge |
| 28 | 0x008c | Dark Crimson |
| 29 | 0x0091 | Doom Bringer |
| 30 | 0x0096 | Dbl Rapier |
| 31 | 0x009b | Light Blade |
| 32 | 0x00a0 | Apocalypse |
| 33 | 0x00a5 | Flame Rose |
| 34 | 0x00aa | Photon Edge |
| 35 | 0x00af | Mighty Talon |
| 36 | 0x00b4 | Hook Katar |
| 37 | 0x00b9 | D Slayer |
| 38 | 0x00be | Nova Blade |
| 39 | 0x00c3 | Drill Bunker |
| 40 | 0x00c8 | Beam Magnum |
| 41 | 0x00cd | Sword Cannon |
| 42 | 0x00d2 | Blaster Gun |
| 43 | 0x00d7 | Sphere Nova |
| 44 | 0x00dc | Omega Raptor |
| 45 | 0x00e1 | Grand Blade |
| 46 | 0x00e6 | Pain Scimitar |
| 47 | 0x00eb | Sword Break |
| 48 | 0x00f0 | Strider |
| 49 | 0x00f5 | Infinity |
| 50 | 0x00fa | **Judgment** (unique, no grade) |
| 51 | 0x00fb | **Light Bringer** (unique) |
| 52 | 0x00fc | **Data Destroyer** (unique) |
| 53 | 0x00fd | **Hyakki Yako** (unique) |
| 54 | 0x00fe | **Orochi Slayer** (unique) |
| 55 | 0x00ff | **Nightmare Lance** (unique) |

Machine-readable: `weapons.json` (256 ids, complete).

## ✅ Styled weapons (cat 0x05) — flat unique list (confirmed)
`0x0500–0x0514`, one id per weapon (no grades):
```
0x0500 Dark Shadow   0x0501 Omega Blade   0x0502 Stargazer    0x0503 Invisible
0x0504 Kaiser Knuckle 0x0505 Demon Arm    0x0506 Nosferatus   0x0507 Executor
0x0508 Dbl Positron  0x0509 Plasma Blade  0x050a Blunt Axe    0x050b Slash Sword
0x050c Stab Dagger   0x050d Bash Katana   0x050e Blunt Edge   0x050f Slash Edge
0x0510 Stab Edge     0x0511 Bash Edge     0x0512 Crush Arm    0x0513 Shot Pistol
0x0514 ?????? (unidentified, needs appraisal)
```
Invalid range: `0x0515–0x053f` (see glitch notes).

## ✅ Armor boards (cat 0x20) — stride 3, grades α/β/γ (confirmed)
`id = 0x2000 + model*3 + grade`. 14 graded boards + 2 unique:
```
model  0 Achilles Board    1 Atlas Board      2 Meteor Board
       3 Fire Board        4 Ice Board        5 Bolt Board
       6 Dark Board        7 Armor Board      8 Beast Board
       9 Rack Board       10 EXP Board       11 BIT Board
      12 Mana Board       13 Resist Board
unique: 0x202a Filter Board, 0x202b Talis of Chaos
        0x202c ?????? (unidentified)
```
Invalid range: `0x202d–0x203f` (see glitch notes).

## 🧨 Illegal-ID / glitch notes (device folder)
These are the interesting exploit levers — game does **not** validate ids on load:
- `0x0514` (weapon), `0x101f` (core), `0x202c` (board) = `??????` appraisal
  wildcards. **Appraise into a RANDOM item of their slot's category** (model +
  grade rolled at appraisal time, varies on reload); result is always **white**
  rarity — the seed is NOT preserved, so no forced-rarity exploit.
- `0x0515–0x051a` = blank items; some crash when interacted with.
- `0x051b–0x053e` = **crash on load**.
- `0x053f` = blank `"0"` weapon: loads, but cannot hit anything.
- `0x202d–0x2035` = crash opening the devices folder.
- `0x2036–0x203e` = crash, but **STRENGTH shows 9999** while in the folder.
- `0x203f` = crash, but **WISDOM shows 9999**.
(The 9999-stat boards are the most promising: if one can be equipped/loaded
without the crash, that's a broken-stat exploit.)

## Device-folder ID ↔ item ID (working model)
The device folder stores a u32 **item ID**. Layout hypothesis:
```
item_id = (flag << 16) | (category << 8) | sub
```
Verified anchors (2-save diff in `save-format.md`):

| ID | dec | cat | sub | Item |
| --- | --- | --- | --- | --- |
| 0 | 0 | 0x00 | 0x00 | Battle Hawk α |
| 25 | 25 | 0x00 | 0x19 | Long Sword α |
| 50 | 50 | 0x00 | 0x32 | Dyno Tooth α |
| 75 | 75 | 0x00 | 0x4b | Kamikiri Maru α |
| 1293 | 0x050d | 0x05 | 0x0d | Bash Katana |
| 1298 | 0x0512 | 0x05 | 0x12 | Crush Arm |
| 1299 | 0x0513 | 0x05 | 0x13 | Shot Pistol |
| 8213 | 0x2015 | 0x20 | 0x15 | Armor Board α |

Hypothesis (unconfirmed): category `0x00` = base weapons with
`sub = model_index * 5 + grade` (grade 0–4 = α–ε). That makes 0/25/50/75 the
α grade of models 0/5/10/15. The weapon model ordering (which model gets which
index) lives in the item database, not in the text table, so it still needs to
be resolved (see below).

Category `0x05` = the style-prefixed weapons (Bash/Slash/Stab/Blunt/Crush/Shot
+ Katana/Edge/Arm/Pistol/…). Category `0x20` = armor boards.

## Still open
1. **message-id → entry-9 string** exact resolution (the offset/index used by
   the text system). The string-ID table gives the message-id per key, but the
   message-id→string step (entry-9 igBinary text DB) is still unparsed.
2. **The authoritative item database** (id → stats + model) in `NDMW.AFS`
   (reflection-serialized); not parsed. This is the only remaining source of
   the item *stats* (attack/defence/stat bonuses), since the save only stores
   the id + loadout.

**Item name catalogue is COMPLETE** — all 5 categories, all grades, all stat
variants: weapons `0x00` (256) + styled `0x05` (21) + cores `0x10` (32) +
boards `0x20` (45) + mods/chips `0x30/0x34` (185 bases × inv/eq).

## Fast empirical fallback
`sleep_edit`-style probing: write candidate ids into the 9 device-folder slots,
equip them via the 3 weapon-slot indices, and read the names in-game. With the
category/sub structure above the search space is small (weapons `0x00/0x05`,
armor `0x20`, chips/cores `?`), so a handful of batched saves can pin the full
table. (See [`save-format.md`](save-format.md) for the offsets.)

---

## ✅ Confirmed additions (dynamic testing, later session)

### Item-ID instance field (corrected)
`instance(16b) = (seed << 4) | mod_count`
- `mod_count` = low nibble, 0–15; **0–5 valid, 6+ crashes** (max 5 mod slots).
- `seed` = high 12 bits = **+N quality bonus** (CRACKED, finding [#116](../findings/findings-0001-0250.md#f116)).

### Rarity seed = direct +N stat bonus; colour = seed thresholds (CRACKED)

**The low 11 bits of the seed ARE the stat bonus**:

```
item_stat = item_base_stat + (seed & 0x7FF)     # +0 .. +2047
```

Bit 11 (`0x800`) is masked off (`0x800` == `0x000`). The bonus is a **universal
+N quality value**, not stat-specific — each item type routes +N to its own
stat (weapon → attack, armor → defence, etc.), and the base stat differs per
item. Verified on 28 probe points (Battle Hawk A, base attack 143):
`seed 0x530` → `143+1328=1471`, `seed 0xFFF` → `143+2047=2190`.

**Colour = monotonic threshold of `(seed & 0x7FF)`** (27/28 probe points match;
one `0x040` anomaly likely a misread):

| colour | seed range |
| --- | --- |
| white | 0 |
| blue | 1 .. 15 |
| green | 16 .. 127 |
| yellow | 128 .. 511 |
| orange | 512 .. 1023 |
| pink | 1024 .. 2047 |

Order (CONFIRMED by tester, most common -> rarest): **white < blue < green <
yellow < orange < pink**.

#### Bit 11 (`0x800`) — purpose UNKNOWN (finding [#117](../findings/findings-0001-0250.md#f117))

The top bit of the 12-bit seed is ignored by both the stat bonus and the colour,
so the instance field is most likely really `[1 flag bit | 11 quality bits |
4 mod bits]`. Hypotheses **eliminated by the tester**:

- ❌ "new item" marker — no such system exists.
- ❌ favouriting/starred — no such system exists.
- ❌ identified/unidentified — `??????` items have their own dedicated item IDs
  (`0x0514` weapon / `0x101f` core / `0x202c` board), not a flag bit.

Still open: the actual meaning of bit 11 (future work — trace the `0x8000`
flag read/write sites in the ELF, or dynamic-test it).

### Item classes (corrected)
| cat | class |
| --- | --- |
| 0x00 | graded weapons (stride 5, α–ε) |
| 0x05 | styled weapons (flat) |
| 0x10 | **armor = cores (∋)**, stride 3, α–γ |
| 0x20 | **sub-slot = boards (∨)**, stride 3, α–γ |
| 0x30 | mod/AB-chip (in inventory) |
| 0x34 | mod/AB-chip (equipped) |

### Equipment slots (device-folder indices)
```
+0x2e4/2e8/2ec   weapon 1/2/3
+0x2f0..+0x300   5 weapon-mod slots (SHARED pool — all 3 weapons show the same mods)
+0x304           armor
+0x308..+0x318   5 armor-mod slots
+0x31c           sub slot
```
Mods reset when a weapon is re-equipped (game design). Identical chips stack
(5× Speed Chip works).

### Mod / AB-chip IDs (mods.json — full grade layout)
Base index (low byte) is **grade-major within family blocks**. Category byte
`0x30` = in inventory, `0x34` = equipped.

**3-grade families** (block of 15; α = block+0..4, β = +5..9, γ = +10..14):

| family | block | α | β | γ |
| --- | --- | --- | --- | --- |
| Wisdom Chip | 0 | 0 | 5 | 10 |
| Spirit Chip | 15 | 15 | 20 | 25 |
| Speed Chip | 30 | 30 | 35 | 40 |
| PWR Medal fire | 45 | 45 | 50 | 55 |
| PWR Medal ice | 60 | 60 | 65 | 70 |
| PWR Medal lightning | 75 | 75 | 80 | 85 |
| PWR Medal dark | 90 | 90 | 95 | 100 |
| Resist ROM fire | 120 | 120 | 125 | 130 |
| Resist ROM ice | 135 | 135 | 140 | 145 |
| Resist ROM lightning | 150 | 150 | 155 | 160 |
| Resist ROM dark | 165 | 165 | 170 | 175 |

**5-grade families** (block of 5; α..ε = block+0..4):

| family | block | α | β | γ | δ | ε |
| --- | --- | --- | --- | --- | --- | --- |
| Drain Ram | 105 | 105 | 106 | 107 | 108 | 109 |
| Dread Ram | 110 | 110 | 111 | 112 | 113 | 114 |
| Assault Ram | 115 | 115 | 116 | 117 | 118 | 119 |
| Defence ROM | 180 | 180 | 181 | 182 | 183 | 184 |

All 15 γ bases (10/25/40/55/70/85/100/107/112/117/130/145/160/175/182) match
`γ = block + 10` (3-grade) or `block + 2` (5-grade). **All grades α/β/γ/δ/ε
CONFIRMED by probe round 4.** Within a 3-grade family each grade spans 5 bases
= 5 stat tiers (base chip + higher +N variants), ascending: offset 0 = base
(no suffix); offset o (1–4) = `+variant_seq[grade_idx + o - 1]` with
`variant_seq = [30,60,120,240,360,480]`. So α=+30/+60/+120/+240,
β=+60/+120/+240/+360, γ=+120/+240/+360/+480.

## Cores (cat 0x10) — model mapping ✅ (complete)
`id = 0x1000 + model*3 + grade` (α/β/γ). Full model order confirmed:

| model | α id | core |
| --- | --- | --- |
| 0 | 0x1000 | Brave |
| 1 | 0x1003 | Aegis |
| 2 | 0x1006 | Vulture |
| 3 | 0x1009 | Cipher |
| 4 | 0x100c | Astral |
| 5 | 0x100f | Wizard |
| 6 | 0x1012 | Element |
| 7 | 0x1015 | Spirit |
| 8 | 0x1018 | Divine |

Grade-less uniques: `0x101b` Invincible, `0x101c` Mythlandia, `0x101d`
Rainbow Veil, `0x101e` Talis of Order, `0x101f` `??????` (unidentified,
needs appraisal). Invalid range: `0x1020–0x103f` = blank (`0x1026` crashes
when selected). Machine-readable: `cores.json`.

## String-ID table (0x004cda40) — static name lookup (partial)
360 records, 12-byte stride: `{u32 key, u32 message_id, u32 font_subtable_ptr}`,
terminated by `key==0xFFFFFFFF`. `key = (flag<<16)|(category<<8)|sub`; lookup
uses `key & 0xFFFFF`. `message_id` = index into the entry-9 text table
(cat 0x05→200-270, cat 0x10→1000-1304, cat 0x11→1200-1205), and the flag
selects a message-id page (flag 0/1/2/3 → base +0/+10000/+20000/+30000).
The table is **incomplete** — several confirmed items (Omega Blade 0x0501,
Crush Arm 0x0512, Divine β 0x1019) are absent, so a second name path exists.
Still useful to enumerate *valid* ids: a sub absent from this table is likely
blank/crash.

### How the message-id is consumed (text system)
`FUN_003ebe00` linear-searches the table, stores `message_id` to `0x0058a220`
("TXT call number"), and walks a **font subtable** at `0x004ceb30` (stride
`0x50`, indexed `[flag][seq]` → font-name pointer) to set up rendering.
A getter at `0x3747f0` returns the message-id. The actual string fetch then
goes through Lua API trampolines → reflection dispatch (`0x38e5d0`), i.e. it is
resolved by the runtime object system, not a static table.

### entry 9 (AREA.AFS) layout
`off=0x757d800 size=430021`. igBinary-serialized:
- header `{0x12a8, 0xa8, 0x10e4, 0x42, 0x30048, 0x1321, 0x33060, 0x685, 0x656, 0x30, 0xfada, …}`,
- reflection type names at `0x270` (`igObjectRefMetaField`, …),
- a `{len,1,0}` 12-byte descriptor array,
- font/global names (`stmojipnl01.png` @ `0x9110`, `abChip` @ `0x9130`),
- **1619 type-256 string records** (tag `0x00000100`, `{size<<8, strlen<<8, Shift-JIS}`,
  packed contiguously; icon-prefixed item names are among these).

The `message_id` is a **flat text-table index assigned by the igBinary
deserializer**, not the type-256 file order (`Dark Shadow` msg=200 is record
[#1109](../findings/findings-1001-1250.md#f1109)). Fully resolving message-id → string statically = replicating the
igBinary deserializer (same prerequisite as the NDMW.AFS item DB).
