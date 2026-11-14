# Digimon World 4: Save Flag Encoding & Story-State Map

**How to read this page:** the raw save-byte observations below are evidence at
their recorded offsets. §3, §4, §6, §7, §9 and §10 quote the current Lua. An older
signed decoder showed `FLGset(N,1)` as `FLGset(N-1,0)` and `FLGset(N,0)` as
`FLGset(N-1,-1)`: the original Apocalymon write is **flag 67 = 1**, not flag 66 = 0,
and difficulty is **0/1/2**, not -1/0/1. A Lua-to-save inversion does not exist.
Labels attached to save bytes need revalidation before use in runtime/save logic; see the
[numeric audit](../../engine/lua-numeric-audit.md) and the
[script gates](../critical-path.md).

---

## 0. Value encoding

In the save file, **`0x01` = done/defeated/set** ("event happened / boss dead / flag on"),
**`0x00` = not-done/clear** ("not yet / boss alive / flag off").
Every one of the 1024 `BASE_FLAG` bytes is only ever `0x00` or `0x01`.

An inverse Lua-to-save model (`be:FLGset(N, 0)`, runtime byte `0x00`, saved as `0x01`
and `be:FLGset(N, -1)`, runtime byte `0xFF`, saved as `0x00`) is refuted:
it rests on the old decoder's `0`/`-1` values.

The observation it was built on (the Apocalymon flag, written in exactly one gameplay
location):

- `boss01-apocalymon` (`lua/11-bosses/01-boss01-apocalymon_e730/006-boss-bit-sq-ddmg.lua:113`) writes the
  flag inside the boss-death sequence (return gate spawned, victory sound): `be:FLGset(66, 0)`
  in the old decoder's text, **flag 67 = 1** in the original.
- Diff `Mcd001_op_base.ps2 → prog_world1.ps2`: `flags[66] 0x00 → 0x01`.

`Mcd001_quest5*.ps2` / `Mcd001_final_v3.ps2` were built with the **opposite** save-byte
polarity and are wrong.

**Folders are NOT inverted.** `SYSctlFlagFolder("SET", N)` → save byte `0x01`;
`"CLR", N` → `0x00`.

---

## 1. Save layout (block-relative; both 0xA000 blocks are byte-identical mirrors)

| offset | field |
| --- | --- |
| `+0x00` | u32 checksum (sum of u32 words from +4..+0xA000) |
| `+0x320` | **BASE_FLAG**: 1024 × u8 (runtime `be:FLG*` flags, ids 0–1023) |
| `+0x720` | **BASE_FLAGFOLDER**: 12 × u8 (persistent folder flags, ids 0–11) |
| `+0x72c` | BASE_COUNTER (u32 array; `[1]` @ +0x730 = junk-shop counter) |
| `+0x77c` | BASE_LEVEL (16 × u32) · `+0x7bc` BASE_EXP · `+0x7fc` BASE_SKILL · `+0xa3c` BASE_UPCNT |

`counter[2]` (@ +0x734) is a non-story per-act counter (0x66/0xcc/0xcd/0x133…),
resets to 0 at each world completion; ignore it for story state.

---

## 2. Story-state fingerprint per checkpoint (ground truth)

`boss` = save bytes 66,67,68,69,82,85 (bytes 66, 82 and 85 are not boss flags, see §3) · `chapter` = flags 701–706 · `intro` = flags 0–6

| save | folders SET | boss | chapter | intro |
| --- | --- | --- | --- | --- |
| `Mcd001_op_base` (fresh) | `[]` | 000000 | 100000 | 1010000 |
| `prog_humid_cave` (W1 d1) | `[0]` | 000000 | 100000 | 1010000 |
| `prog_cliff_dungeon` (W1 d2) | `[0,1]` | 000000 | 100000 | 1010000 |
| `prog_leomon_save` (W1 story) | `[0,1,2]` | 000000 | 100000 | 1010000 |
| `prog_world1` (W1 boss) | `[0,1,2]` | 110000 | 100000 | 1010000 |
| `prog_ophanimon_key` | `[0..3]` | 110000 | 010000 | 1001000 |
| `prog_ophanimon_key_used` | `[0..3]` | 110000 | 001000 | 1000100 |
| `prog_disable_power_plant` | `[0..3]` | 110000 | 001000 | 1000100 |
| `prog_sand_labrynth` (W2 d1) | `[0..4]` | 110000 | 001000 | 1000100 |
| `prog_ancient_ruins` (W2 d2) | `[0..5]` | 110000 | 001000 | 1000100 |
| `prog_world2` (W2 boss) | `[0..5]` | 111000 | 001000 | 1000100 |
| `prog_world3_unlocked` | `[0..5]` | 111010 | 000100 | 1000010 |
| `prog_gecko_path` (W3 d1) | `[0..6]` | 111010 | 000100 | 1000010 |
| `prog_vine_tunnel` (W3 d2) | `[0..7]` | 011010 | 000100 | 1000010 |
| `prog_vein` (W3 d3) | `[0..8]` | 011010 | 000100 | 1000010 |
| `prog_world3` (W3 boss) | `[0..8]` | 011110 | 000100 | 1000010 |
| `prog_world4_unlocked` | `[0..8]` | 011110 | 000010 | 1000001 |

The World-4 checkpoints (`prog_mecha_nest`, `prog_electro_mine`, `prog_world4`) are in §9.

---

## 3. Boss-defeat flags (`BASE_FLAG`, save byte `0x01` = defeated)

| id | boss | Lua writer (on death) | first set in diffs |
| --- | --- | --- | --- |
| 67 | Apocalymon | `entry_0730/chunk_0006:113` | `prog_world1` (W1) |
| 68 | BelialVamdemon | `entry_0737/chunk_0000:112` | `prog_world2` (W2) |
| 69 | Lucemon | `entry_0744` | `prog_world3` (W3) |
| 83 | LordKnightmon (`dng412b4`) | `entry_0425/chunk_0076:31` | `prog_electro_mine` (§9) |
| 70 | Devimon (form 3 / final) | `entry_0765/chunk_0005:132` | `prog_world4` (§9) |
| 86 | story cleared | `entry_0765/chunk_0005:134` (Hard/Very Hard only), `entry_0820/chunk_0009:30` (when flag 70 is on) | `prog_world4` (§9) |
| 610 | final scene (Hard/Very Hard only) | `entry_0765/chunk_0005:135` | *(still 0, not reached)* |

Notes:

- The boss order (from `entry_0603` stage-select chunks 0071→0075) is
  **67 (W1) → 68 (W2) → 69 (W3) → 83 (W4) → 70+86 (final)**, and the diff column agrees.
- Save byte **66 is not a boss flag**: the title script clears 36–66 on load, and the
  byte flips back to `0x00` at `prog_vine_tunnel` (W3 d2).
- `entry_0765` writes `FLGset(86,1)`/`FLGset(610,1)` only when
  `SYSgetDifficulty() > 0` (Hard or Very Hard; **Normal is 0**). `FLGset(70,1)` is
  unconditional.

---

## 4. Persistent folder flags (`BASE_FLAGFOLDER`, save byte `0x01` = SET)

Folders are the `impItem` records: the important-item page lists them, and scripts use
`SYSctlFlagFolder` for `impItem` entries. The boss keys arrive as rate-10000 drops.

| folder | set at | item (`impItem` record) |
| --- | --- | --- |
| 0 | `prog_humid_cave` | Blosso ID, Blossomon's drop (`dng101b2`) |
| 1 | `prog_cliff_dungeon` | Mammothmon ID (`dng102b3`) |
| 2 | `prog_leomon_save` | Boat Key, given in the Commander Room after Leomon's rescue |
| 3 | `prog_ophanimon_key` | Ophanimon ID; no gameplay writer found |
| 4 | `prog_sand_labrynth` | SkullGrey ID (`dng204b2`) |
| 5 | `prog_ancient_ruins` | Scorpio ID (`dng205b3`) |
| 6 | `prog_gecko_path` | Shogun ID (`dng307b2`) |
| 7 | `prog_vine_tunnel` | MRS04 ID (Vine Tunnel) |
| 8 | `prog_vein` | Diaboro ID (`dng309b4`) |
| 9 | `prog_mecha_nest` | MRE05 ID (`dng411b3`, `e_mecha5`) |
| 10 | `prog_electro_mine` | LordKnight ID (`dng412b4`, `e_ldknight`) |
| 11 | quest scripts | Offering; cleared on load and not restored |

*(Note: the W1 boss defeat (`prog_world1`) sets flag 67 (save bytes 66 and 67
both flip) but **no** folder; folder 2 is the earlier Boat Key.)*

**Flag 905 needs folders 9 and 10 SET.**
`lua/05-city-overworld/01-stag0403-city-quest-hub_e709/034-layer-setup-msg-61097.lua:102`:
```lua
if be:SYSctlFlagFolder("IS", 9) == 1 and be:SYSctlFlagFolder("IS", 10) == 1 then
    be:FLGset(905, 1)
    be:sd("MODELCTRL", "g_entrywayz04", 0, "SQ_SILENTON")
end
```

So flag 905 is set when both folders are set, in the stage's layer setup and in `026-flag-905-city-entryway-state.lua`,
which plays its sequence while 905 is clear. The chunk does not write flag 904, and 905 is not a
gate-closed marker; an `IS 8`/`IS 9`, `FLGset(904, 0)` reading is the old decoder's off-by-one. Script
folders 9 and 10 are the same folders as the table: MRE05 ID and LordKnight ID.

The game's own "everything done" snapshot (`lua/14-misc/01-stage-select-list_e603/075-flag-1-intro-step-0-msg-80024.lua`) sets
**folders 0–10** and the flags 67,68,69,70,83,86 to `1`. That is the post-game
state; **final-boss-READY = folders 0–10 set but flag 610 still `0`** (see §9
below for the observed World-4 end state).

---

## 5. Chapter / intro step flags

- **700-series = per-difficulty mirror backups** of the intro/chapter flags (see §7): on Normal,
  `700–705` mirror `1–6` and `706/707` mirror `19/20`. In the checkpoint diffs they read as a one-hot
  world chapter: 701 = W1 era → 702 (got Ophanimon key) → 703 (key used / W2) → 704 (W3) → 705 (W4),
  with advance points matching the folder table above. That is because "chapter" and "mirror" are the
  same bytes; §7's table is the authoritative interpretation.
- **1–6 = chapter one-hot, then 86** (NOT a 0→1→2… sequence):
  - flag **1** = tutorial in progress, the fresh state.
    `lua/01-lobby-hub/04-lobby-ofanimon-seraphimon_e816/096-layer-setup-sq-hide.lua` and the Terminal's
    `lua/01-lobby-hub/05-lobby-quests_e820/009-layer-setup-sq-demowait.lua` set it on arrival when flags 2–6 and 86
    are all clear, so a state with no chapter flag does not last past those stages.
  - flags **2–6** = the current chapter, one at a time: 2 (W1) → 3 (post-W1 key) → 4 (W2) → 5 (W3) →
    6 (W4). Ophanimon sets 2 and moves 2 → 3 (flags 20 and 67), Seraphimon moves 3 → 4 (flag 324) and
    4 → 5 (flag 335), and Ophanimon moves 5 → 6 (flag 69).
  - flag **86** = story cleared. The Terminal clears 6 and sets 86 once flag 70 is on; on Hard and Very
    Hard the final boss script also sets it.
- flag **0** is not story state. Field-stage layer setups and talk scripts write it (to 1 and to 0), no
  script reads it, and the title restore leaves it alone, so saves usually show it set.

---

## 6. Other flags worth knowing

- `376–380` quests 1–5, `381` final quest gate: quest-chain, **not** required
  for the main story (see `entry_0820`/`entry_0824`).
- `409, 571, 424, 385, 389`: quest sub-state, written by the quest NPCs.
- `905`: set when folders 9 and 10 are both set.
- `904`: set in the stage-select final snapshot (world 4 reached).
- `49, 82, 334, 383, 320–327, 329–333, 335`: story sub-state copied by the
  title-screen restore (`entry_0806/chunk_0006`) from per-difficulty mirror
  flags (see below).
- **Transient flags (cleared on load, NOT restored from a mirror):**
  quest flags `376–381` (+ `384–389`, `409`, `571–575`), final-scene `610`,
  `328`, and the ranges 23–34, 36–66, 71–73, 84–85, 100–319, 336–391,
  415–425, 457–468, 475, 477–478, 480–500, 514–517, 562–566, 571–575,
  593–594, 598–610. Edits to these revert to `0` after a load. (Contrast:
  1–6, 19–20, 49, 67–70, 82, 83, 86, 89–99, 320–327, 329–335 and 383 are
  *restored* from mirrors, so they persist.)

---

## 7. The mirror/restore system (why there are 700–811 "backup" flags)

`lua/00-title-menus/04-title-screen_e806/006-flag-82-clear.lua` (title screen / new game / load) clears folders and
a big flag range (`FLGset(N,0)` → save `0x00`), then restores the active story
flags from **per-difficulty mirror flags**.

**Difficulties:** **Normal = `SYSgetDifficulty() == 0`,
Hard = 1, Very Hard = 2.** Difficulty is **not stored in the save**; the editor
infers it from which mirror set is live (see below).

Active ← mirror, per difficulty:

| active | Normal (0) | Hard (1) | Very Hard (2) |
| --- | --- | --- | --- |
| intro 1–6 | 700–705 | 7–12 | 13–18 |
| 19–20 | 706–707 | 741–742 | 771–772 |
| 67–70 | 708–711 | 74–77 | 78–81 |
| 83 | 712 | 743 | 773 |
| 86 | 713 | 87 | 88 |
| 89–99 | 714–724 | 744–754 | 774–784 |
| 320–327 | 725–732 | 755–762 | 785–792 |
| 329–333 | 733–737 | 763–767 | 793–797 |
| 335 | 738 | 768 | 798 |
| 49 | 801 | 802 | 803 |
| 383 | 804 | 805 | 806 |
| 82 | 807 | 808 | 809 |
| 334 | 810 | 811 | 812 |

and folders `N ← mirror(518+N)` (Normal), `530+N` (Hard), `542+N` (Very Hard),
where folder SET ⇔ mirror byte `0x01` (direct copy). The title script restores folders 0–10 only.

`entry_0810` (character select) does the reverse copy (active → mirror) on
save. That's why diffs show changes in both the active and mirror ranges
simultaneously, and why the save editor must write **both** the active flag and
its mirror or the edit reverts on load.

---

## 8. How to build the final-boss-ready save

The end state is `prog_world4.ps2` ("after World 4
boss, black core opened"; §9). Recipe:

1. Start from the **maxed-character base** `Mcd001_op_base.ps2`.
2. Overwrite `BASE_FLAG` (1024 bytes @ +0x320) and `BASE_FLAGFOLDER`
   (12 bytes @ +0x720) with **`prog_world4.ps2`'s** values.
3. Leave everything else (character stats, items, bits) from the base.
4. `fix_checksums()` and write both mirror blocks identically.

Built on the base `prog_world4_unlocked` + folder 9, as an overlay on a
finished character. The shipped `Mcd001_final_ready.ps2` = base character + `prog_world4`
story state.

## 9. World-4 end state (ground truth from `prog_world4.ps2`)

| save | folders | boss 66,67,68,69,82,85 | 85/609/70/86/406 | chapter |
| --- | --- | --- | --- | --- |
| `prog_world4_unlocked` | 0–8 | 011110 | 0/0/0/0/0 | 000010 |
| `prog_mecha_nest` (MRE05 ID) | 0–9 | 011110 | 0/0/0/0/0 | 000010 |
| `prog_electro_mine` (LordKnight ID) | 0–10 | 011110 | 0/0/0/0/0 | 000010 |
| `prog_world4` (W4 boss + gate open) | 0–10 | 011110 | 0/0/1/1/1 | 000000 |

World-4 step diffs:

- `world4_unlocked → mecha_nest`: **folder 9** set (MRE05 ID); flags 71,72 set.
- `mecha_nest → electro_mine`: **folder 10** set (LordKnight ID); flag 83 set +
  a large block of W4 dungeon flags (0x20c–0x28b…) set.
- `electro_mine → world4`: flags **70, 86, 363, 406, 492, 711, 713, 905** set;
  intro-step **flag 6 cleared**; chapter **705 cleared** (chapter string goes
  to all-zero = story done); a large block of W4 dungeon flags cleared.

Notes:

- **Flag 610 stays `0` even at `prog_world4`.** `entry_0765` (boss06-devimon-3)
  writes 86 and 610 only when `SYSgetDifficulty() > 0` (Hard/Very Hard), and the
  run was on **Normal**.
- **Flag 86 is `1`** at `prog_world4` all the same: `entry_0820/chunk_0009` sets it
  whenever flag 70 is on.
- The Black Core gate (`entry_0709/chunk_0034`) checks **folders 9 and 10**, so it
  opens once `prog_electro_mine`'s folder 10 is set; flag 905 first appears in the
  `electro_mine → world4` diff.

---

## 10. Progression-testing findings

Experiments with a fresh character (`test_base_save.ps2`, intro step 1) settled
several things and left a few [open questions](#open-questions).

### Confirmed

- **Teleports / world access = `BASE_FLAGFOLDER` (folders 0–10) only.** Setting
  folder flags unlocks the travel points; not setting them leaves only the
  always-available starting area (Death Valley).
- **Keys/IDs are *not* separate inventory items.** A full-save diff of
  `prog_world1 → prog_ophanimon_key` changed *only* flags + folder 3 (+ the
  human's bits/X-Data). "Ophanimon key" is **folder 3**, nothing else.
- **The quest chain (376–381) is an unrelated side-quest system.** Marking it
  "done" has no effect on teleports, keys, or the main story. Its **reward** is
  digivolutions: the quest NPCs (`entry_0820` Digi-Elf giver, `entry_0824`
  quest board) call `SYSctlShinka` to unlock forms (377→4/5/6/7, 378→4/5/6/7/15,
  379→8/9/11). Those unlocks are stored in **`BASE_ISUSE`** (save `+0x76c`) and
  *do* persist even though the `376–381` flags are transient. See
  [`docs/systems/digivolution-and-sidequests.md`](../digivolution-and-sidequests.md).

### Save-editor support

A save editor for this format wants **Story**, **Disks**, **Bank** and
**Bank items** tabs plus a **Raw edits** tab (always last):

- Story: checkboxes for folders 0–11, boss flags (67/68/69/70/83/86/610),
  chapter (701–706), intro steps (0–6), quests (376–381), and lobby/system
  flags (24/501/508/931/935/936/960); checked = `0x01`;
- presets: **Fresh (tutorial)** (matches `test_base_save`), After World 1/2/3,
  All worlds + keys, Story cleared (post-game), plus "mark all quests done";
- a **difficulty selector** (auto / Normal / Hard / Very Hard); the editor
  writes the corresponding **mirror flags** in sync with the active flags so
  edits survive the load-time restore;
- Disks: the 12 disk counts; Bank: balance + 96 item slots.

*(Note: quest flags 376–381 and final-scene 610 are transient: the editor
can set them but they revert to 0 on load; see §6.)*

---

## 11. Disk folder, card list, bank (full save-record field map)

Traced from `beNDMWDegiData__LoadFromProperties` (the per-player record builder) disassembly +
the property key table `0x00517e50`. Struct offset + 8 = block offset.

| block offset | field | size / format |
| --- | --- | --- |
| `+0x00` | checksum | u32 (sum of u32 words +4..+0xA000) |
| `+0x04` | version | u32 (=4) |
| `+0x08` | ISUSE | u8 (slot in use) |
| `+0x0c` | UNIQUE | u32 (save id/seed) |
| `+0x10` | DIGIMONNAME | 16 B ASCII (`p_dorumon`) |
| `+0x30` | PLAYERNAME | 8 B fullwidth UTF-16 |
| `+0x50` | LEVEL | u32 (menu snapshot, recomputed) |
| `+0x54/58/5c/60` | HP/MHP/MP/MMP | u32 (menu snapshot) |
| `+0x64` | XDATA | u32 |
| `+0x68` | BIT | u32 (currency) |
| `+0x6c` | **DEVICEFOLDER** | 36 × u32 (30 used + 6 pad, `0xFFFFFFFF`=empty) |
| `+0xfc` | **DISKFOLDER** | 12 × u32: `(count << 16) \| (0x4000 + type)` |
| `+0x12c` | **CARDLIST** | ≤52 B, collected-card bitfield |
| `+0x160` | **BANKDEVICE** | 96 × u32 (`0xFFFFFFFF`=empty) |
| `+0x2e0` | **BANKBIT** | u32, bank balance |
| `+0x2e4` | POWERSOCKET (weapons) | 3 × u32 (device-folder indices) |
| `+0x2f0` | POWERPOCKET (weapon mods) | 5 × u32 |
| `+0x304` | armor | u32 |
| `+0x308` | armor mods | 5 × u32 |
| `+0x31c` | sub slot | u32 |
| `+0x320` | BASE_FLAG | 1024 × u8 |
| `+0x720` | BASE_FLAGFOLDER | 12 × u8 |
| `+0x72c` | BASE_COUNTER | u32 array |
| `+0x77c/7bc/7fc/a3c` | LEVEL/EXP/SKILL/UPCNT | per-species arrays |

### Disk folder (`+0xfc`, 12 × u32)

- 12 consumable disk types, ids `0x4000`–`0x400b` (category `0x40` = "disk").
  In order: **HP Disk α, HP Disk β, HP Disk γ, MP Disk α, MP Disk β,
  MP Disk γ, Cure Disk, Raise Disk, Gate Disk, Recovery, Battery Pack,
  Key Chain** (grade letters are Greek: α/β/γ/δ/ε).
- Entry = **`(count << 16) | (0x4000 + type)`**; count = how many you own.
- Fresh save = all counts 0. Observed in-game max = **9**; the disk shop
  (`entry_0828/chunk_0049`, `diskshop.lua`) consumes **8 at a time** via
  `SYSctlDiskFolder("CLR", -1, 10, 8)` and caps via `("ISMAX", -1, 10, -1)`.
- Class `beNDMWItemDisk` / `_diskIdList` / `_diskCnt` in the ELF.

### Bank

- **`BANKBIT` @ `+0x2e0`** (u32): the banked-bit balance.
  **Byte-confirmed**: `Mcd001_bank.ps2` (1M deposit) → `+0x2e0 = 0x000F4240`.
- **`BANKDEVICE` @ `+0x160`** (96 × u32): items deposited in the bank,
  `0xFFFFFFFF` = empty. Same item-id encoding as the device folder
  (byte-confirmed: 21 items decoded to real weapons/cores/boards/mods).

### Card list (`+0x12c`)

- Collected-card list (`SYSctlCardFolder("KAZU", -1)` = card count), a
  ≤52-byte bitfield; all-zero when no cards collected.

### Editor support

`dw4save.py` exposes `disk_count(i)` / `set_disk_count(i, n)`,
`bank_bit`, and `bank_device(i)`; the GUI has a **"Bank & Disks"** tab
(bank balance + 12 disk counts).

## Open questions

- **The "Key Folder" UI is not driven by folder flags alone.** A save with
  folders 0–10 set still showed no keys while the tutorial was active. The
  inventory Key Folder panel is likely gated on a further story/location state
  (not yet pinned).
- **Intro flags don't control the spawn stage.** `test_base_save` (flag 1 = 1)
  is the tutorial. A save with flag 0 = 1 and flags 1–6 all 0 loads
  into a **locked** state (no NPC chat, no levels); there is **no loadable
  pre-DigiElf state**. The new-game opening (title → char select → stagML11 →
  first DigiElf chat) is runtime-state-driven; the save record contains **no
  stage/intro/location field** (verified from `beNDMWDegiData__LoadFromProperties`).
- **The exact fresh-state flag set.** Unproven: a true fresh (tutorial) state is
  flag 1, the lobby flags 24/501/508/931/935/936/960 and mirror flag 700. Flag 2
  means World 1 access (Ophanimon already spoken to), so a fresh preset built on
  flag 2 opens the World 1 gate.
