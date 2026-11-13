# Digivolution Unlock & Side-Quest Completion

Based on static analysis (Ghidra/objdump), the decompiled Lua
(`lua/`) and save inspection. Items marked **inferred** are
supported by code + data but have **not** been confirmed live.

Numeric Lua examples and the grant/gate sections follow the
[numeric audit](../engine/lua-numeric-audit.md).
Original bytecode is the execution baseline.

## 0. Summary

- **"Can digivolve to form F" is one byte per form in a 16-byte array named
  `BASE_ISUSE`**, a runtime GAMERAM property record, serialised in the save at
  **`+0x76c`** (16 × u8).
- Set by `SYSctlShinka("SETSHINKA", player, form)`; read by
  `SYSisGetShinkaDigimon(player, form)`.
- **Form index = species/model index** (see §3).
- Side-quest *completion* is mostly **transient runtime state** (the quest-chain
  flags are cleared on load; see the [numeric audit](../engine/lua-numeric-audit.md)) plus **persisted counters**
  (`BASE_COUNTER`). The durable reward of a side quest is the digivolution byte
  in §2.

## 1. The digivolution API

| id | name | stub | real impl |
| --- | --- | --- | --- |
| 21 | `SYSisGetShinkaDigimon` | `0x00370b18` | `0x003725f0` |
| 24 | `SYSctlShinka` | `0x00370b98` | `0x003727d0` |

Both are in the 116-function native API table (see `docs/engine/script-engine-lua.md`).

### 1.1 Getter: `SYSisGetShinkaDigimon` (`0x003725f0`)

```
3725f0: a0 = a0 + 1                       ; player index+1
        v0 = player_struct(a0)            ; 0x371c10
        rec = record(v0, "BASE_ISUSE")    ; 0x3a92b0, key VA 0x0050da18
        v0 = rec->value (+12)
        ptr = v0->ptr (+16)               ; value struct: {+8 count, +16 ptr}
        return ptr[form]                  ; lbu, form in a1
```

The stub then runs the raw byte through the value wrapper at `0x00100290`
before pushing it to Lua.

### 1.2 Setter: `SYSctlShinka` (`0x003727d0`)

This is a **three-command multiplexer** on `a0` (the command string), with
`a1 = player`, `a2 = form`:

| command string | key VA | action |
| --- | --- | --- |
| `"GETEXP"` (`0x0050da50`) | `BASE_EXP` (`0x0050da58`) | return `BASE_EXP[form]` (u32 array) |
| `"GETLEVEL"` (`0x0050da68`) | `BASE_LEVEL` (`0x0050da78`) | return `BASE_LEVEL[form]` (u32 array) |
| `"SETSHINKA"` (`0x0050da88`) | `BASE_ISUSE` (`0x0050da18`) | see below |

`SETSHINKA` path:

```
s3 = BASE_ISUSE[form]                     ; read once at entry
if command != "SETSHINKA" -> return 0
if s3 != 0                -> return 0     ; already unlocked, no-op
if 0 <= form < count      -> BASE_ISUSE[form] = *(gp - 32428)
```

The written constant is a small-data global (`lbu v1,-32428(gp)`); its value was
not resolved statically but is **inferred to be 1** (the "unlocked" byte).

## 2. Storage: `BASE_ISUSE`

| | |
| --- | --- |
| Runtime | property record keyed `"BASE_ISUSE"`, byte array, per player |
| Save field | `BASE_ISUSE`, **16 × u8 at `+0x76c`** |
| Encoding | **inferred**: `0` = form locked, `1` = form unlocked/available |

Save values measured directly:

| save | Digimon | `BASE_ISUSE` @ `+0x76c` |
| --- | --- | --- |
| first save | `p_dorumon` | `[0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0]` |
| second save | `p_dorumon` | `[0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0]` |
| fresh save | `p_dorumon` | `[0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0]` |

A fresh Digimon has **only its own index set**, consistent with one byte per
form and only the starting form available.

> **`BASE_ISUSE` is not an "active species" marker (that reading does not hold).** The active
> species is derived from `DIGIMONNAME`, so `BASE_ISUSE[3]=1` on a
> Dorumon save is *the Dorumon form being unlocked*, not a separate "in use"
> marker.

### 2.1 Lua-level convention

Reward scripts query player 0 and compare the unlock byte with **0** (locked)
or **1** (available). A repeated reward can pay **2000 BITS**. A
`player=-1`, `locked=-1`, `unlocked=0`, `1999 BITS` reading is the signed-bias
error; no special Lua-to-save conversion is needed to explain those literals.
Live reward delivery and the setter's small-data constant need validation.

## 3. Form index map

Index = the 16-species/model order (`beNDMWGameRam_FindSpecies` `MODEL_NAME`
table). This is also the order of the save's `BASE_*` arrays.

| idx | model name | Digimon | starter? |
| --- | --- | --- | --- |
| 0 | `agumon` | Agumon | yes |
| 1 | `vmon` | Veemon | yes |
| 2 | `girumon` | Guilmon | yes |
| 3 | `dorumon` | Dorumon | yes |
| 4 | `weregaru` | WereGarurumon | |
| 5 | `hekabut` | HerculesKabuterimon | |
| 6 | `wargrey` | WarGreymon | |
| 7 | `angelr` | ClavisAngemon | |
| 8 | `beelzeb` | Beelzemon BM | |
| 9 | `alpha` | Alphamon | |
| 10 | `bwargrey` | BlackWarGreymon | |
| 11 | `impdrafm` | Imperialdramon Fighter Mode | |
| 12 | `impdrapm` | Imperialdramon Paladin Mode | |
| 13 | `metalgaru` | MetalGarurumon | |
| 14 | `dukecrim` | Gallantmon Chaos Mode | |
| 15 | `susanoo` | Susanomon | |

## 4. `SETSHINKA` grant sites

Every `SETSHINKA` call in the 5,291 decompiled chunks, by entry:

| entry | role | chunks | forms granted |
| --- | --- | --- | --- |
| `entry_0603` | Digi Lab attendant (`n_digilff`) | `0030` (grant-all loop), `0031`–`0046` (one per form) | `0 … 15` |
| `entry_0820` | Digi-Elf quest giver | `0011`, `0012`, `0013` | quest rewards |
| `entry_0824` | quest board | `0029`, `0030`, `0110`, `0112` | quest rewards |

Original `entry_0603/chunk_0030` loops over **0..15**;
`entry_0820/chunk_0012` also grants form 15 in a reward branch. A reading in which
form 15 has no grant site is the signed-bias error. Recheck the
original chunk and difficulty/character branch before asserting grant eligibility.

## 5. Side-quest completion gating

The Digi-Elf quest giver (`entry_0820`) and quest board (`entry_0824`) are the
reward NPCs. They gate on a mix of **counters, difficulty and flags**.

### 5.1 `entry_0820` (Digi-Elf quest giver)

Quest accept/handler chunks are `0001`–`0008`, reward handlers `0010`–`0013`.
Script values include:

| reward chunk | quest flag (+ sub-step) | grant forms present | example gates |
| --- | --- | --- | --- |
| `chunk_0010` | 376 | none | dialogue/state |
| `chunk_0011` | 377 (+385) | 4, 5, 6, 7 | `COUNTERget(player+3)` threshold 279 (Normal) / 302 (Hard, Very Hard); flag 554 |
| `chunk_0012` | 378 (+386) | 4, 5, 6, 7, 15 | `COUNTERget(0) >= 600`; flag 557 and additional difficulty branches |
| `chunk_0013` | 379 (+387) | 8, 9, 11 | flags 564..567 and difficulty branches |

These are forms present in the source, not promises that every branch grants
all listed forms. The handlers clear flags 409/571/424 and their quest/sub-step
flags with value **0**. Difficulty values are **0/1/2**. The 279/302
thresholds agree with the walkthrough numbers; a one-less reading of them is
refuted. Counter service semantics and live completion remain unverified.

### 5.2 `entry_0824` (quest board)

`chunk_0029` contains grants for forms 4..8 across several branches. Its writes
include `FLGset(475,1)` and `FLGset(432,1)`. `chunk_0030 / 0110 / 0112`
carry further grants. A single-form-4 interpretation of `chunk_0029` is wrong.

### 5.3 What persists and what does not

| state | persists in save? |
| --- | --- |
| digivolution unlock | yes: `BASE_ISUSE` @ `+0x76c` |
| kill counters | yes: `BASE_COUNTER`, 16 × u32 @ `+0x72c` |
| quest-chain flags `376–381`, sub-steps `384–389`, `409`, `571–575` | no: transient; `entry_0806/chunk_0006` clears them on load and does not restore from the mirror |
| persistent quest marker | folder `11` (`SYSctlFlagFolder("SET",11)`) |

Consequence: **you cannot mark a side quest "done" by editing a save.** The
durable result of finishing one is the digivolution byte (and any folder/BITS
change). The `376–381` gate condition itself is documented in
`docs/systems/critical-path.md` / `docs/systems/flags/flag-map.md`.

### 5.4 The walkthrough's 10 named side quests

The retail walkthrough (§5SQ) lists 10
Digi-Elf side quests (Undead Yard, Dungeon of Doom, Captive Dungeon, Barbaric
Cave, Forbidden Dungeon, ShogunGekomon, Legendary Coliseum, Trading Hall, Item
Road, Final Side Quest) with their reward Digivolutions. **The per-quest →
flag mapping for those 10 named quests is not yet established**: the scripts
above are identified, but the quest names live in the igBinary text table
(`TALKFONT…/I<n>` message ids), not in the Lua. See
the in-game quest board (§3 of the game's own manual pages) for the quest list and reward matrix.

## 6. Practical use

**Grant a digivolution in a save** (per-Digimon):

1. `BASE_ISUSE[form] = 1` at block offset `+0x76c` (both mirrored 0xA000 blocks).
2. Recompute the per-block SUM checksum (`docs/systems/save-format.md`).
3. The Digi Lab should then offer the form.

**Cannot** be done via save for quest completion; use live memory instead
(`pine write` to the transient flags + counters), or complete the quest.

**Confirm the encoding live** (recommended, closes §2.1):

```
state load op-ready
# read the runtime byte array via the player-struct chain, or
# read the save field and compare with the Digi Lab menu
# then SETSHINKA one form and re-read
```

## 7. Open items

1. **Byte → Lua encoding**: confirm live that scripts see `0` (locked) / `1`
   (available) and that rewards are delivered (see §2.1).
2. **Per-quest flag map** for the 10 named walkthrough side quests.
3. **`*(gp-32428)` constant** written by `SETSHINKA`: resolve its value.
4. **`entry_0603/chunk_0030`** grant-all loop: is it a quest reward, a debug
   path, or both?

## 8. Evidence / reproduction

- Disassembly: `mipsel-linux-gnu-objdump -d --start-address=0x003725f0 …` and
  `…0x003727d0` on `orig/SLUS-20836/SLUS_208.36`.
- String keys: VA `0x0050da18` = `BASE_ISUSE`, `0x0050da50` = `GETEXP`,
  `0x0050da58` = `BASE_EXP`, `0x0050da68` = `GETLEVEL`, `0x0050da78` =
  `BASE_LEVEL`, `0x0050da88` = `SETSHINKA` (note: `.rodata` VA = file offset +
  `0xFFF80`, not `+0x100000`).
- Lua: `lua/01-lobby-hub/05-lobby-quests_e820/chunk_001{0,1,2,3}.lua`,
  `lua/01-lobby-hub/06-lobby-quest-board_e824/029-npc-digilfm-5.lua`, `entry_0603/chunk_0030…0046.lua`.
- Saves: the three in the table above, byte range `+0x76c … +0x77c`.
