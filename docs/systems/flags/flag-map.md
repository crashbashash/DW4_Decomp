# Digimon World 4 — Save Flag Encoding & Story-State Map

**How to read this page ([#785](../../findings/findings-0751-1000.md#f785)/#787):** the raw save-byte observations below are
evidence at their recorded offsets. The Lua flag IDs and values quoted beside
them are not: they come from a signed decoder that shows `FLGset(N,1)` as
`FLGset(N-1,0)` and `FLGset(N,0)` as `FLGset(N-1,-1)`. The original Apocalymon
write is **flag 67 = 1**, not flag 66 = 0; difficulty is **0/1/2**, not -1/0/1.
A Lua-to-save inversion (finding [#121](../../findings/findings-0001-0250.md#f121)) does not exist. The boss/quest labels
attached to the save bytes need revalidation. Do not use the Lua-side numbers
on this page for runtime/save logic; see the
[numeric audit](../../engine/lua-numeric-audit.md) and the
[script gates](../critical-path.md).

---

## 0. Value encoding

In the save file, **`0x01` = done/defeated/set** ("event happened / boss dead / flag on"),
**`0x00` = not-done/clear** ("not yet / boss alive / flag off").
Every one of the 1024 `BASE_FLAG` bytes is only ever `0x00` or `0x01`.

An inverse Lua-to-save model — `be:FLGset(N, 0)` (runtime byte `0x00`) saved as `0x01`
and `be:FLGset(N, -1)` (runtime byte `0xFF`) saved as `0x00` — is refuted (finding [#121](../../findings/findings-0001-0250.md#f121)):
it rests on the old decoder's `0`/`-1` values.

The observation it was built on (the Apocalymon flag, written in exactly one gameplay
location):

- `boss01-apocalymon` (`lua/11-bosses/01-boss01-apocalymon_e730/006-boss-bit.lua:87`) writes the
  flag inside the boss-death sequence (return gate spawned, victory sound) — `be:FLGset(66, 0)`
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
| `+0x320` | **BASE_FLAG** — 1024 × u8 (runtime `be:FLG*` flags, ids 0–1023) |
| `+0x720` | **BASE_FLAGFOLDER** — 12 × u8 (persistent folder flags, ids 0–11) |
| `+0x72c` | BASE_COUNTER (u32 array; `[1]` @ +0x730 = junk-shop counter) |
| `+0x77c` | BASE_LEVEL (16 × u32) · `+0x7bc` BASE_EXP · `+0x7fc` BASE_SKILL · `+0xa3c` BASE_UPCNT |

`counter[2]` (@ +0x734) is a non-story per-act counter (0x66/0xcc/0xcd/0x133…),
resets to 0 at each world completion — **ignore it for story state**.

---

## 2. Story-state fingerprint per checkpoint (ground truth)

`boss` = flags 66,67,68,69,82,85 · `chapter` = flags 701–706 · `intro` = flags 0–6

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
| 66 | Apocalymon | `entry_0730/chunk_0006:87` | `prog_world1` (W1) |
| 67 | BelialVamdemon | `entry_0737/chunk_0000:86` | `prog_world1` (W1) |
| 68 | Lucemon | `entry_0744` | `prog_world2` (W2) |
| 69 | Devimon (form 3 / final) | `entry_0765/chunk_0005:105` | `prog_world3` (W3) |
| 82 | LordKnightmon (`dng412b4`) | `entry_0425/chunk_0076:29` | `prog_world3_unlocked` |
| 85 | story cleared (final boss, Hard/Very Hard only) | `entry_0765/chunk_0005:107` | *(still 0 — not reached)* |
| 609 | final scene (Hard/Very Hard only) | `entry_0765/chunk_0005:108` | *(still 0 — not reached)* |

Notes:

- The canonical boss order (from `entry_0603` stage-select chunks 0071→0075) is
  **66 (W1) → 67 (W2) → 68 (W3) → 82 (W4) → 69+85+609 (final)**. Real saves
  set them slightly earlier (66+67 at W1, 68 at W2, 69 at W3, 82 at W3-unlock),
  so trust the diff column above for "already-beaten" state, not the labels in
  `docs/systems/flags/flag-meanings.md`.
- Flag **66 is non-monotonic**: it flips back to `0x00` at `prog_vine_tunnel`
  (W3 d2). Don't rely on 66 as a persistent "defeated" marker.
- `entry_0765` writes `FLGset(85,0)`/`FLGset(609,0)` only when
  `SYSgetDifficulty() > -1` (Hard or Very Hard; **Normal is −1**, so these are
  never set on Normal). `FLGset(69,0)` is unconditional.
  (`prog_world3` has 69=1 but 85=0 — consistent with the W3 boss being a Devimon
  form whose death sets 69 while 85 stays for the true final fight.)

---

## 4. Persistent folder flags (`BASE_FLAGFOLDER`, save byte `0x01` = SET)

Observed chronological accumulation:

| folder | set at | meaning |
| --- | --- | --- |
| 0 | `prog_humid_cave` | World 1 dungeon 1 (Humid Cave / Blossomon) |
| 1 | `prog_cliff_dungeon` | World 1 dungeon 2 (Cliff Dungeon / Mammothmon) |
| 2 | `prog_leomon_save` | Saved Leomon from Goblin Fortress (W1 story event) |
| 3 | `prog_ophanimon_key` | Ophanimon key obtained (hub invasion) |
| 4 | `prog_sand_labrynth` | World 2 dungeon 1 (Sand Labrynth / SkullGrey ID) |
| 5 | `prog_ancient_ruins` | World 2 dungeon 2 (Ancient Ruins / Scorpio ID) |
| 6 | `prog_gecko_path` | World 3 dungeon 1 (Gecko Path / Shogun ID) |
| 7 | `prog_vine_tunnel` | World 3 dungeon 2 (Vine Tunnel / MRS04 ID) |
| 8 | `prog_vein` | World 3 dungeon 3 (Vein / **Diaboro ID** = key card 1) |
| 9 | `prog_mecha_nest` | World 4 dungeon 1 (Mecha Nest / **MRE05 ID** = key card 2) |
| 10 | `prog_electro_mine` | World 4 dungeon 2 (Electro Mine / **LordKnight ID**) |

*(The accumulation is **8 = Diaboro (W3), 9 = Mecha Rogue 05 (W4),
10 = LordKnightmon (W4)** — not "folder 8 = Mecha Rogue 05, folder 9 =
LordKnightmon".)*

*(Note: the W1 boss defeat — `prog_world1` — sets boss flags 66+67 but **no**
folder; folder 2 is the earlier Leomon-rescue story beat.)*

**The final-boss security gate requires folders 8 AND 9 SET.**
`lua/05-city-overworld/01-stag0403-city-quest-hub_e709/034-layer-setup-2.lua:102`:
```lua
if be:SYSctlFlagFolder("IS", 8) == 0 and be:SYSctlFlagFolder("IS", 9) == 0 then
    be:FLGset(904, 0)   -- gate-closed marker (only when a key card is missing)
    ...
end
```

The game's own "everything done" snapshot (`lua/14-misc/01-stage-select-list_e603/075-flag-1-7.lua`) sets
**folders 0–9** and the boss flags 66,67,68,82,69,85 all to `0` (Lua) → save
`0x01`. That is the post-game state; **final-boss-READY = folders 0–10 set but
flag 85/609 still `0`** (see §9 below for the observed World-4 end state).

---

## 5. Chapter / intro step flags

- **700-series = per-difficulty mirror backups** of the intro/chapter flags
  (see §7): `701/702/703` = mirror of intro `2/3/4`, `705/706` = mirror of
  `18/19`, `704` is unused. In the checkpoint diffs they read as a one-hot world
  chapter — 701=W1 era → 702 (got Ophanimon key) → 703 (key used / W2) → 704 (W3)
  → 705 (W4), with advance points matching the folder table above — because
  "chapter" and "mirror" are the same bytes; §7's table is the authoritative
  interpretation.
- **0–6 series = tutorial marker + chapter one-hot** (NOT a 0→1→2… sequence):
  - flag **1** = tutorial in progress — the true fresh state
    (`test_base_save.ps2` = flag 1 ticked).
  - flag **0** = "not in tutorial" / idle marker. `entry_0816/chunk_0096`
    ticks it when flags 1–5 + 85 are all `0` (no chapter active); it also
    stays ticked post-tutorial (op_base/world1 = flag 0 + flag 2).
    **flag 0 = 1 with flags 1–6 all `0` = LOCKED** (no NPC chat, no levels,
    can't talk to Ophanimon) — not a playable pre-intro state.
  - flags **2–6** = the current chapter, one at a time:
    2 (W1) → 3 (post-W1 key) → 4 (W2) → 5 (W3) → 6 (W4).

---

## 6. Other flags worth knowing

- `375–379` quests 1–5, `380` final quest gate — quest-chain, **not** required
  for the main story (see `entry_0820`/`entry_0824`).
- `408, 570, 423, 384, 388` — quest sub-state, written by the quest NPCs.
- `904` — final-gate-closed marker (set when folders 8/9 are missing).
- `903` — set in the stage-select final snapshot (world 4 reached).
- `48, 81, 333, 382, 500–507, 319–334` — story sub-state copied by the
  title-screen restore (`entry_0806/chunk_0006`) from per-difficulty mirror
  flags (see below).
- **Transient flags (cleared on load, NOT restored from a mirror):**
  quest flags `375–380` (+ `383–388`, `408`, `570–575`), final-scene `609`,
  `327`, and the ranges 22–33, 35–65, 70–72, 83–84, 99–318, 335–390,
  414–424, 456–467, 474, 476–477, 479, 480–499, 513–516, 561–565, 570–574,
  592–593, 597–608. Edits to these revert to `0` after a load. (Contrast:
  81/333/382/334/48/18–19/88–97/319–325/328–331 are cleared but then
  *restored* from mirrors, so they persist.)

---

## 7. The mirror/restore system (why there are 700–811 "backup" flags)

`lua/00-title-menus/04-title-screen_e806/006-flag-82.lua` (title screen / new game / load) clears folders and
a big flag range (`FLGset(N,-1)` → save `0x00`), then restores the active story
flags from **per-difficulty mirror flags**.

**Difficulties** (user-confirmed): **Normal = `SYSgetDifficulty() == -1`,
Hard = 0, Very Hard = 1.** Difficulty is **not stored in the save** — the editor
infers it from which mirror set is live (see below).

Active ← mirror, per difficulty:

| active | Normal (−1) | Hard (0) | Very Hard (1) |
| --- | --- | --- | --- |
| intro 0–4 | 699–703 | 6–10 | 12–16 |
| 18–19 | 705–706 | 740–741 | 770–771 |
| 66–68 | 707–709 | 73–75 | 77–79 |
| 82 | 711 | 742 | 772 |
| 85 | 712 | 86 | 87 |
| 88–97 | 713–722 | 743–752 | 773–782 |
| 319–325 | 724–730 | 754–760 | 784–790 |
| 328–331 | 732–735 | 762–765 | 792–795 |
| 334 | 737 | 767 | 797 |
| 48 | 800 | 801 | 802 |
| 382 | 803 | 804 | 805 |
| 81 | 806 | 807 | 808 |
| 333 | 809 | 810 | 811 |

and folders `N ← mirror(518+N)` (Normal), `530+N` (Hard), `542+N` (Very Hard),
where folder SET ⇔ mirror byte `0x01` (direct copy).

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

- **Flag 85 and 609 stay `0` even at `prog_world4`.** Those are the
  `entry_0765` (boss06-devimon-3) "story cleared" writes, gated by
  `SYSgetDifficulty() > -1` (Hard/Very Hard). The run was on **Normal**, so
  they're simply never written.
- **Flag 86 (`= FLGisOn(85)` mirror, written at character-select) is `1`** at
  `prog_world4` while active `85` is `0` — a mirror/restore divergence worth
  knowing if you re-load the save (on load, `entry_0806` restores active flags
  from the mirrors).
- The Black Core gate (`entry_0709/chunk_0034`) checks **folders 8 and 9**
  (Diaboro + MRE05), so it is already open by `prog_mecha_nest`; folder 10
  (LordKnight) is collected afterwards on the way to the World-4 boss.

---

## 10. Progression-testing findings

Experiments with a fresh character (`test_base_save.ps2`, intro step 1) settled
several things and left a few open questions.

### Confirmed

- **Teleports / world access = `BASE_FLAGFOLDER` (folders 0–10) only.** Setting
  folder flags unlocks the travel points; not setting them leaves only the
  always-available starting area (Death Valley).
- **Keys/IDs are *not* separate inventory items.** A full-save diff of
  `prog_world1 → prog_ophanimon_key` changed *only* flags + folder 3 (+ the
  human's bits/X-Data). "Ophanimon key" is **folder 3**, nothing else.
- **The quest chain (375–380) is an unrelated side-quest system.** Marking it
  "done" has no effect on teleports, keys, or the main story. Its **reward** is
  digivolutions: the quest NPCs (`entry_0820` Digi-Elf giver, `entry_0824`
  quest board) call `SYSctlShinka` to unlock forms (376→3/4/5/6, 377→3/4/5/6/14,
  378→7/8/10). Those unlocks are stored in **`BASE_ISUSE`** (save `+0x76c`) and
  *do* persist even though the `375–380` flags are transient. See
  [`docs/systems/digivolution-and-sidequests.md`](../digivolution-and-sidequests.md).

### Open questions

- **The "Key Folder" UI is not driven by folder flags alone.** A save with
  folders 0–10 set still showed no keys while the tutorial was active. The
  inventory Key Folder panel is likely gated on a further story/location state
  (not yet pinned).
- **Intro flags don't control the spawn stage.** `test_base_save` (flag 1 = 1)
  is the tutorial. flag 0 = "idle/no-chapter" (ticked by `chunk_0096` when
  flags 1–5+85 are all 0). A save with flag 0 = 1 and flags 1–6 all 0 loads
  into a **locked** state (no NPC chat, no levels) — there is **no loadable
  pre-DigiElf state**. The new-game opening (title → char select → stagML11 →
  first DigiElf chat) is runtime-state-driven; the save record contains **no
  stage/intro/location field** (verified from `FUN_003ee6d0`).

### Save-editor support

A save editor for this format wants **Story**, **Disks**, **Bank** and
**Bank items** tabs plus a **Raw edits** tab (always last):

- Story: checkboxes for folders 0–11, boss flags (66/67/68/69/82/85/609),
  chapter (701–706), intro steps (0–6), quests (375–380), and lobby/system
  flags (24/501/508/931/935/936/960) — checked = `0x01`;
- presets: **Fresh (tutorial)** (matches `test_base_save`), After World 1/2/3,
  All worlds + keys, Story cleared (post-game), plus "mark all quests done";
- a **difficulty selector** (auto / Normal / Hard / Very Hard) — the editor
  writes the corresponding **mirror flags** in sync with the active flags so
  edits survive the load-time restore;
- Disks: the 12 disk counts; Bank: balance + 96 item slots.

*(Note: quest flags 375–380 and final-scene 609 are transient — the editor
can set them but they revert to 0 on load; see §6.)*

---

## 11. Disk folder, card list, bank (full save-record field map)

Traced from `FUN_003ee6d0` (the per-player record builder) disassembly +
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
| `+0xfc` | **DISKFOLDER** | 12 × u32 — `(count << 16) \| (0x4000 + type)` |
| `+0x12c` | **CARDLIST** | ≤52 B — collected-card bitfield |
| `+0x160` | **BANKDEVICE** | 96 × u32 (`0xFFFFFFFF`=empty) |
| `+0x2e0` | **BANKBIT** | u32 — bank balance |
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

- **`BANKBIT` @ `+0x2e0`** (u32) — the banked-bit balance.
  **Byte-confirmed**: `Mcd001_bank.ps2` (1M deposit) → `+0x2e0 = 0x000F4240`.
- **`BANKDEVICE` @ `+0x160`** (96 × u32) — items deposited in the bank,
  `0xFFFFFFFF` = empty. Same item-id encoding as the device folder
  (byte-confirmed: 21 items decoded to real weapons/cores/boards/mods).

### Card list (`+0x12c`)

- Collected-card list (`SYSctlCardFolder("KAZU", -1)` = card count), a
  ≤52-byte bitfield; all-zero when no cards collected.

### Editor support

`dw4save.py` exposes `disk_count(i)` / `set_disk_count(i, n)`,
`bank_bit`, and `bank_device(i)`; the GUI has a **"Bank & Disks"** tab
(bank balance + 12 disk counts).
