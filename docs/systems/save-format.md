# Save Format

Verified against a **real USA save**: `../local/testing/memcards/Mcd001.ps2`.

## Memory-card layout (PS2)

```
BASLUS-20836savedata/            save directory (BASLUS-20836 = USA product code)
├── icon.sys                     964 B   MC icon metadata
├── icon1.ico                    34,156 B  icon graphics
└── BASLUS-20836savedata         81,920 B  *** the save data ***
```

Extracted from a `.ps2` memory-card image (both ECC and ECC-less images occur). The data file is
exactly **80 KB**.

## The save data file (81,920 bytes)

It is **two identical 40,960-byte (0xA000) blocks** (a mirror/backup). Each block
= `[8-byte header][~2.6 KB record][zero padding to 0xA000]`.

```
Block 0 : 0x00000 .. 0x09FFF
Block 1 : 0x0A000 .. 0x13FFF   (byte-identical copy of block 0)
```

## Checksum  ⭐

Per block: **SUM of all u32 little-endian words from `block+4` to `block+0xA000`,
mod 2³²**, stored at `block+0`.

```
checksum(block) = ( Σ u32le(buf, block+4 + 4k) for k=0..(0xA000-4)/4 ) & 0xFFFFFFFF
stored at buf[block + 0]
```

Python:

```python
import struct
BLOCK = 0xA000
def block_sum(buf, base):
    s = 0
    for i in range(base + 4, base + BLOCK, 4):
        s = (s + struct.unpack_from('<I', buf, i)[0]) & 0xFFFFFFFF
    return s
def fix_checksums(buf):                 # buf = bytearray of the 81920-byte save
    for b in (0, BLOCK):
        struct.pack_into('<I', buf, b, block_sum(buf, b))
```

Verified on both real saves (`save1 SUM blk = 0x40F3E11D`, `save2 = 0x47000881`,
both equal the stored value), and used successfully to edit a save.

> **Not a whole-file XOR.** A whole-file *XOR* match is a tautology — because
> the two 0xA000-byte blocks are byte-identical mirrors, `XOR(u32, 4..EOF)`
> always equals the mirrored checksum field and thus says nothing about the
> data. The real checksum is the per-block **SUM** above (it is non-trivial and
> matches both saves).

## Block field map

Offsets are **file offsets** within a block (block base `0x00000` / `0x0A000`).
The 8-byte header is followed by the "deliver struct" (base = block+8).

| Offset | Size | Field | Real-save value |
| --- | --- | --- | --- |
| `+0x00` | u32 | **checksum** | `0x40F3E11D` |
| `+0x04` | u32 | **version** | `4` |
| `+0x08` | u8 | `ISUSE` (slot in use) | `1` |
| `+0x0c` | u32 | `UNIQUE` (id / seed) | `0x6096F82C` |
| `+0x10` | 16 B | model name `DIGIMONNAME` | `"p_dorumon"` |
| `+0x20` | 16 B | (name padding) | zeros |
| `+0x30` | 8 B | save name `PLAYERNAME` (**fullwidth UTF-16**) | `0xff41 0xff42 0xff43` = ａｂｃ ("abc") |
| `+0x38` | 24 B | (padding) | zeros |
| `+0x50` | u32 | `LEVEL` (menu snapshot only) | `1` |
| `+0x54` | u32 | `HP` (**derived** — menu only) | `170` |
| `+0x58` | u32 | `MHP` (**derived** — menu only) | `170` |
| `+0x5c` | u32 | `MP` (**derived** — menu only) | `60` |
| `+0x60` | u32 | `MMP` (**derived** — menu only) | `60` |
| `+0x64` | u32 | `XDATA` | `0` |
| `+0x68` | u32 | **`BIT`** (currency, trusted) | `0` / `187` **✔ confirmed** |
| `+0x6c` | 36 × u32 | **device folder** (`0xFFFFFFFF` = empty, trusted) | see below |
| `+0x2e4` | 3 × u32 | **weapon slots** (indices into device folder, trusted) | see below |
| `+0x470`–`+0x48b` | bytes | `BASE_FLAG[336..363]` (flags, not a technique-level table; see `docs/systems/techniques.md`) | |
| `+0x788` | u32 | **REAL level** (`BASE_LEVEL[3]`, trusted until EXP gain) | `2` |
| `+0x7c8` | u32 | **EXP** (`BASE_EXP[3]`, trusted; drives the level formula) | `398` |
| `+0x874` | u32 | single technique level — `BASE_SKILL[30]` = species 3 (Dorumon) skill slot 3 = **bash** | `7` |
| `+0xfc` | 48 B | sequential ids `0x4000..0x400B` (+ high-bit flags) | |
| other | | `0xFFFFFFFF` slot tables, flag/usage data (see the complete map below) | |
| `+0xafc`–`+0xA000` | | zero padding | |

## ✅ Complete block byte map (authoritative)

The whole 0xA000 block is mapped contiguously — **no unknown bytes**.
Verified by a pure-synthesis builder that reproduces both reference saves **byte-for-byte**
(findings [#139](../findings/findings-0001-0250.md#f139)–[#143](../findings/findings-0001-0250.md#f143)).

| File offset | Size | Field |
| --- | --- | --- |
| `+0x00` | u32 | checksum (sum of u32 words `+4..+0xA000`) |
| `+0x04` | u32 | version = 4 |
| `+0x08` | u8 | ISUSE = 1 (slot in use) |
| `+0x0c` | u32 | UNIQUE = `0x6096F82C` (stable across real saves) |
| `+0x10` | 16 B | DIGIMONNAME (ASCII model stem, e.g. `p_dorumon`) |
| `+0x20` | 16 B | padding (zeros) |
| `+0x30` | 8 B | PLAYERNAME (u16 `0xFFFF` marker + 3 fullwidth UTF-16 chars) |
| `+0x38` | 24 B | padding (zeros) |
| `+0x50` | u32 | LEVEL (menu snapshot, derived) |
| `+0x54` | u32 | HP (derived, menu only) |
| `+0x58` | u32 | MHP (derived, menu only) |
| `+0x5c` | u32 | MP (derived, menu only) |
| `+0x60` | u32 | MMP (derived, menu only) |
| `+0x64` | u32 | XDATA |
| `+0x68` | u32 | BIT (currency) |
| `+0x6c` | 36×u32 | DEVICEFOLDER (30 used + 6 pad; `0xFFFFFFFF` = empty) |
| `+0xfc` | 12×u32 | DISKFOLDER (`0x4000+i` = 0 owned of disk type i) |
| `+0x12c` | 52 B | CARDLIST (collected-card bitfield) |
| `+0x160` | 96×u32 | BANKDEVICE (`0xFFFFFFFF` = empty) |
| `+0x2e0` | u32 | BANKBIT |
| `+0x2e4` | 3×u32 | weapon slots (POWERSOCKET, device-folder indices) |
| `+0x2f0` | 5×u32 | weapon-mod sockets (POWERPOCKET) |
| `+0x304` | u32 | armor/core slot (MAINSLOT) |
| `+0x308` | 5×u32 | armor-mod sockets (MAINPOCKET) |
| `+0x31c` | u32 | sub/board slot (SUBSLOT) |
| `+0x320` | 1024×u8 | BASE_FLAG |
| `+0x720` | 12×u8 | BASE_FLAGFOLDER |
| `+0x72c` | 16×u32 | BASE_COUNTER (junk shop = `COUNTER[1]` @ `+0x730`) |
| `+0x76c` | 16×u8 | BASE_ISUSE (species-indexed; `[active species]` = 1) |
| `+0x77c` | 16×u32 | BASE_LEVEL |
| `+0x7bc` | 16×u32 | BASE_EXP |
| `+0x7fc` | 144×u32 | BASE_SKILL (16 species × 9 techniques) |
| `+0xa3c` | 176×u32 | BASE_UPCNT (16 species × 11 power-ups) |
| `+0xafc` | — | zero padding to end of block |

Struct-offset note: `FUN_003ee6d0` writes the deliver struct at `block+8`, so
struct offsets = file offsets − 8 (e.g. `sw v0,72(s0)` = file `+0x50`). The
function→field keys in write order are `ISUSE UNIQUE LEVEL HP MHP MP MMP
PLAYERNAME DIGIMONNAME XDATA BIT DEVICEFOLDER DISKFOLDER CARDLIST BANKDEVICE
BANKBIT POWERSOCKET POWERPOCKET MAINSLOT MAINPOCKET SUBSLOT BASE_FLAG
BASE_FLAGFOLDER BASE_COUNTER BASE_ISUSE BASE_LEVEL BASE_EXP BASE_SKILL
BASE_UPCNT` (`0x517e58..0x517fc0`).

`BASE_ISUSE` is at `+0x76c`, immediately after the 16-entry `BASE_COUNTER`
(not at `+0x764`, where finding [#87](../findings/findings-0001-0250.md#f87) placed it).

`Time` / `SaveDataTime` / `MakeDataTime` / `GAMEDATAINIT` are **not**
serialized: the record key table's leading `"Time"` (`0x517e50`) has no code
references, and the struct has no free byte slot for them (finding [#140](../findings/findings-0001-0250.md#f140)).

### Load-time mirror restore ⭐

On load, `entry_0806/chunk_0006` clears transient flags + all folders, then
restores **ACTIVE ← MIRROR** per difficulty. A synthesized/edited save must
write both the active value and its mirror, or the state reverts.

Normal (−1): intro `0..4 ← 699..703`; `18,19 ← 705,706`; bosses
`66,67,68 ← 707,708,709`; `82 ← 711`; `85 ← 712`; `88..97 ← 713..722`;
`319..325 ← 724..730`; `328..331 ← 732..735`; `334 ← 737`; `48 ← 800`;
`382 ← 803`; `81 ← 806`; `333 ← 809`; folders `0..9 ← 518..527`.
(Hard: intro `0..4 ← 6..10`, bosses `66..68 ← 73..75`, `82 ← 742`, `85 ← 86`,
folders `0..9 ← 530..539`. Very Hard: `0..4 ← 12..16`, `66..68 ← 77..79`,
`82 ← 772`, `85 ← 87`, folders `0..9 ← 542..551`.)

Difficulty itself is **not** serialized (finding [#137](../findings/findings-0001-0250.md#f137)) — it is runtime-only.

### Device folder — `file+0x6c` (36 × u32)

The first 9 slots of the reference save, confirmed by 2-save diff (user's
folder lists "dyno tooth a" twice at positions 4 & 8 → both read `50`):

| Slot | Offset | Item | ID |
| --- | --- | --- | --- |
| 1 | `+0x6c` | bash katana | `1293` |
| 2 | `+0x70` | shot pistol | `1299` |
| 3 | `+0x74` | crush arm | `1298` |
| 4 | `+0x78` | dyno tooth a | `50` |
| 5 | `+0x7c` | long sword a | `25` |
| 6 | `+0x80` | battle hawk a | `0` |
| 7 | `+0x84` | armour board a | `8213` |
| 8 | `+0x88` | dyno tooth a | `50` |
| 9 | `+0x8c` | kamikiri maru a | `75` |

### Weapon slots — `file+0x2e4/0x2e8/0x2ec` (3 × u32)

Each stores an **index into the device folder**; the **equipped weapon is
weapon slot 1** (`*(0x2e4)`). Confirmed when the player swapped the equipped
weapon and `+0x2e4`/`+0x2e8` flipped `0↔1`:

| Save | slot1 (`+0x2e4`) | slot2 (`+0x2e8`) | slot3 (`+0x2ec`) | Equipped |
| --- | --- | --- | --- | --- |
| 1 | `0` (bash) | `1` (shot) | `2` (crush) | bash katana |
| 2 | `1` (shot) | `0` (bash) | `2` (crush) | shot pistol |

### Character stats are **derived**, not stored

The displayed stats (strength/defence/wisdom/spirit/speed) and the elemental
resistances (fire/ice/thunder/dark) are **not present anywhere in the save file**.
They are computed at runtime from the **equipped device** (looked up by the
weapon-slot index → device-folder id → device data table). Only the loadout is
saved (device folder + weapon slots).

### LEVEL / EXP formula  ⭐ (confirmed)

`threshold(n)` = cumulative EXP required to reach level *n*:

```
threshold(n) = n³ + 137·n² − 77·n − 61
```

Integer coefficients, **zero residual** across 7 measured points. Level from EXP
= the largest *n* with `threshold(n) <= EXP` (the level-up check runs only when
EXP changes, so a freshly-loaded level is trusted as-is).

Useful values:

| level | threshold (EXP) |
| --- | --- |
| 1 | 0 |
| 2 | 341 |
| 3 | 968 |
| 10 | 13,869 |
| 20 | 61,199 |
| 30 | 147,929 |
| 40 | 280,059 |
| 50 | 463,589 |
| 60 | 704,519 |
| 70 | 1,008,849 |
| 90 | 1,831,709 |
| 99 | 2,305,352 |
| 999 | 1,133,652,152 |

Max level is 999 (in-game cap; the field itself is a u32 and accepts higher,
but the game clamps/display-caps at 999). The polynomial itself keeps growing.

**Save-edit recipes:**

- Set level directly: write level to `+0x788` (and `+0x50` for the menu) — trusted
  until the next EXP gain.
- Set level via EXP: write `EXP = threshold(n)` (or `threshold(n) .. threshold(n+1)-1`)
  to `+0x7c8`, then trigger any EXP gain in-game to force the recalc.

## Field source (static)

The block is built by **`FUN_003ee6d0`** (base `*(ctx+28)`), which reads GAMERAM
properties and writes them to struct offsets. Key→offset (from disassembly):

```
ISUSE  -> +0     UNIQUE -> +4
LEVEL  -> +72    HP  -> +76   MHP -> +80   MP -> +84   MMP -> +88
XDATA  -> +92    BIT -> +96
PLAYERNAME / ME / DIGIMONNAME / AME  -> string copies near +8..+40
later: +728, +764, +788 (+792 BASE_FLAG array), +1816 (BASE_FLAGFOLDER), +2612
```

The property key order read by the function is
`ISUSE, UNIQUE, LEVEL, HP, MHP, MP, MMP, PLAYERNAME, ME, DIGIMONNAME, AME,
XDATA, BIT, DEVICEFOLDER, …` (key strings `0x00517e58`–`0x00517ee0`).

- `BASE_LEVEL` array `+0x77c` (16×u32), `BASE_EXP` `+0x7bc` (16×u32),
  `BASE_SKILL` `+0x7fc` (16 species × 9 skill slots = 144×u32), `BASE_UPCNT`
  `+0xa3c` (16×11 u32), `BASE_FLAG` `+0x320` (1024×u8), `BASE_FLAGFOLDER`
  `+0x720`, `BASE_COUNTER` `+0x72c` (16×u32), `BASE_ISUSE` `+0x76c` (16×u8,
  species-indexed). The six attack
  styles (blunt/slash/stab/bash/shot/crush) are `BASE_SKILL[species*9 + 0..5]` —
  see [`techniques.md`](techniques.md).

**Species index order** (confirmed — see finding [#111](../findings/findings-0001-0250.md#f111)): the game derives the
species index from `DIGIMONNAME` via `FUN_003f80e0`, which linear-searches the
MODEL_NAME table (ELF `0x417b88`):
`0 agumon, 1 vmon, 2 girumon, 3 dorumon, 4 weregaru, 5 hekabut, 6 wargrey,
7 angelr, 8 beelzeb, 9 alpha, 10 bwargrey, 11 impdrafm, 12 impdrapm,
13 metalgaru, 14 dukecrim, 15 susanoo`.

## Save-system classes (C++)

| Symbol | Role | Address |
| --- | --- | --- |
| `beSaveDataDeliver` | serialiser | 0x00502b20 |
| `beSvPs2McImage128k` | "128k" image wrapper | 0x005026d0 |
| `beSaveMemoryObj` | image memory object | 0x00502b00 |
| `beSaveApi` / `beSaveUtil` / `beSaveUtilInfo(Ram)` | save API/util | 0x00502950 / 0x005024e0 / 0x00502390 |
| `beNDMWMcSlotPS2` (+ `GC`, `Xbox`) | per-platform slots | 0x00512e70 |
| `beNDMWMcUtilCtrl` | MC utility controller | 0x00512ca0 |
| `_mcUtilCtrl`, `_cardInfoList`, `_selPoint`, `_mcStat` | MC state | 0x00510d70 … |
| `_slotSaveData`, `_isHaveSaveData`, `_haveSaveData` | slot state | 0x00512c10 … |

Save class field offsets (from reflection tables):
`_data@+8`, `_dataSize@+12`, `_dataOffSet@+24`, `_imageSize@+32`,
`_image@+36`, `_saveDataSize@+40`.

Save/load code regions: **`FUN_003e4750`** (save, 18 KB), **`FUN_004081a0`**
(load, 15.8 KB), **`FUN_003ee6d0`** (per-player record builder, 2.7 KB).
PS2 MC access is via libmc (`mcman.irx`, `mcserv.irx`).

## Full saved property schema

These GAMERAM keys appear in the save/load code (`0x003e0000`–`0x003f9000`);
the keys written into the block are the ones in the complete map above:

```
Player   : BASE_LEVEL BASE_EXP BASE_SKILL BASE_UPCNT BASE_COUNTER BASE_FLAG
           BASE_FLAGFOLDER BASE_ISUSE LEVEL EXP DIGIMONNAME DIGIMONNO
           PLAYERNAME NINZU ISUSE UNIQUE XDATA BIT
Loadout  : MAINSLOT SUBSLOT MAINPOCKET POWERPOCKET POWERSOCKET POWERSOCKETNAME
           SOUBI SKILL SKILLPOINT TSUYOSA INI_WEAPON1
Bank/misc: BANKBIT BANKDEVICE CARDLIST DIFFICULTY DEVICE DEVICEFOLDER
           DISKFOLDER FLAGFOLDER COUNTER
Meta     : SaveDataTime MakeDataTime GAMEDATAINIT
```

> **Note:** the `Meta` keys (`Time` / `SaveDataTime` / `MakeDataTime` /
> `GAMEDATAINIT`) are **not** serialized into the 81920-byte save. They are
> runtime-only or memory-card directory (icon.sys) metadata (finding [#140](../findings/findings-0001-0250.md#f140)).
> The record key table's leading `"Time"` (`0x517e50`) has no code references.
> `DIFFICULTY` is not serialized either (finding [#137](../findings/findings-0001-0250.md#f137)).

## Editing recipe

1. Parse the memory-card image and take `BASLUS-20836savedata` (80 KB).
2. Edit **trusted** fields in **both** blocks, then recompute each block's SUM
   checksum and repack the image. Trusted = BIT `+0x68`, device folder `+0x6c`,
   weapon slots `+0x2e4/8/c`, real level `+0x788`, EXP `+0x7c8`.
   (HP/MP `+0x54..0x60` and LEVEL `+0x50` are menu-only — the game recomputes
   them, so don't bother editing them for gameplay effect.)
3. Recompute the checksums (per-block SUM) and write at `+0x00` and `+0xA000`.
4. Write back into the memory card image.

### Worked example

| Field | Offset | Value |
|---|---|---|
| BIT (in-game currency) | `0x68` | `999999` |
| real level | `0x788` | `50` |
| level-up counter | `0x50` | `50` |
| EXP | `0x7c8` | `1133652152` (level 999) |

## ✅ Additional offsets (confirmed by dynamic testing)

| Offset | Size | Field |
| --- | --- | --- |
| `+0x730` | u32 | junk-shop donation counter (cumulative bits) |
| `+0x2e4/2e8/2ec` | 3×u32 | weapon 1/2/3 (device-folder indices) |
| `+0x2f0..+0x300` | 5×u32 | weapon-mod slots (shared pool) |
| `+0x304` | u32 | armor (device-folder index) |
| `+0x308..+0x318` | 5×u32 | armor-mod slots |
| `+0x31c` | u32 | sub slot (device-folder index) |
| `+0x874` | u32 | single technique level |

- Device folder at `+0x6c` is not 9 slots: the used part **grows** (multi-page) within the 36-entry array.
- Item ID = `{u8 base, u8 category, u16 instance}`, `instance = (seed<<4)|mod_count`.
- Level `+0x788` is a u32; in-game max is 999 (higher values are capped/clamped).
- Junk-shop tiers: 1k/6k/26k/86k/206k/456k/956k/1956k/3956k.

---

## Memory-card creation — console-validated metadata ⭐

Notes for **building a `.ps2` from scratch** rather than editing an existing one.

Verified by synthesising cards with the DW4orge Rust rewrite and loading them in
PCSX2. Every item below was found by the console rejecting a card that was
internally consistent — valid FAT, valid ECC, readable by `ps2mc` — and that the
BIOS memory-card browser happily listed.

### Layout the game accepts

Mirror a real card's allocation rather than inventing a tidy contiguous one:

| Relative clusters | Contents |
| --- | --- |
| `0 → 1` | root directory: `.`, `..`, the save-directory entry |
| `2 → 3 → 118` | save directory: `.`, `..`, `icon1.ico`, the save, `icon.sys` |
| `4 … 37` | `icon1.ico` (34,156 B) |
| `38 … 117` | the save (81,920 B) |
| `119` | `icon.sys` (964 B) |

Indirect FAT at absolute cluster 8 (listing `9..40`); FAT at absolute clusters
9–40. Raw FAT encoding: free `0x7FFFFFFF`, allocated pointer
`0x80000000 | next`, chain end `0xFFFFFFFF`. The save directory's own `.` entry
has `length` 0 while its parent entry holds 5 — reproduce that, do not "fix" it.

### Directory entry fields the console validates

| Field | Requirement | If wrong |
| --- | --- | --- |
| created `+0x08`, modified `+0x18` | valid PS2 timestamps; a real card's values work | any invented value (including `2000-01-01`, or a recent but different date) → card refused: slot greyed out or "memory card not inserted" |
| byte `+0x14` of a directory's `.` entry | the directory's own first cluster (`2` for the save directory) | `0` → the game reports "no save data" |

Timestamp layout in the 8 bytes: `[0][sec][min][hour][day][month][year u16 LE]`.
Entry modes as stored: directory `0x8427`, file `0x8497`, root `..` `0xa426`,
save-directory `..` `0x8427`.

### Not required

Proven by deleting each from a working card and re-testing:

- the contents of **page 1** (real cards carry 8 bytes there; erased is accepted);
- the **backup block** — superblock `backup_block1`/`backup_block2` = 1022/1023,
  physical clusters 8184–8191 (erased is accepted);
- FAT entries at or after `alloc_end` (`0xFFFFFFFF` vs `0x7FFFFFFF` is irrelevant);
- ECC spare bytes on erased pages.

### Gotcha

The **BIOS browser lists a save that the game then rejects.** Test any
synthesised card in an emulator or on hardware; self-consistency and third-party
tooling agreement are not sufficient.
