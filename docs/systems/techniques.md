# Techniques (attack styles + skills)

The **nine** techniques — **blunt, slash, stab, bash, shot, crush, blast, heal,
force** — and their levels are stored in the save as part of the per-**species**
`BASE_*` arrays. This doc supersedes the earlier guess that `+0x470..+0x48b` was
a "technique-level table" (that region is just a stretch of `BASE_FLAG` bytes).
The original prompt listed only six styles; the three extra slots (6/7/8) turned
out to be real techniques (blast/heal/force), confirmed by dynamic probing.

## Where the data actually lives (confirmed by disassembly)

The save block's "deliver struct" (base = block+8) is written by
`FUN_003ee6d0` and read back by `FUN_003ef5d0`. The technique-relevant fields
(the `BASE_*` arrays) are, in **file (block-relative) offsets**:

| Field | file offset | struct offset | layout |
| --- | --- | --- | --- |
| `BASE_LEVEL` | `+0x77c` | 1908 | 16 × u32, indexed by `DIGIMONNO` (species) |
| `BASE_EXP`   | `+0x7bc` | 1972 | 16 × u32, indexed by species |
| `BASE_SKILL` | `+0x7fc` | 2036 | **144 × u32 = 16 species × 9 skill slots** |
| `BASE_UPCNT` | `+0xa3c` | 2620 | 16 × 11 u32 (indexed by species) |
| `BASE_FLAG`  | `+0x320` | 792  | 1024 × u8 (flags; the old "+0x470 table" is `BASE_FLAG[336..363]`) |
| `BASE_FLAGFOLDER` | `+0x720` | 1816 | bytes |
| `BASE_COUNTER` | `+0x72c` | 1828 | u32 array (junk-shop counter = `[1]` → `+0x730`) |
| `BASE_ISUSE` | `+0x764` | 1892 | bytes |

Derivation: `struct offset = file offset − 8` (the 8-byte `{checksum,version}`
header precedes the struct).

## BASE_SKILL — the technique/skill levels

The mapping between the `BASE_*` arrays and the live `GAMERAM` properties is:

- `FUN_003f8760` (current → base, pre-save): `BASE_LEVEL[species]=LEVEL`,
  `BASE_EXP[species]=EXP`, `BASE_SKILL[species*9 + i]=SKILL[i]` for `i` in 0..8,
  `BASE_UPCNT[species*11 + i]=UPCNT[i]` for `i` in 0..10.
- `FUN_003f82a0` (base → current, post-load): the exact inverse.

`SKILL[]` is a **9-element array** on the player record. The **6 attack styles
occupy 6 of these 9 slots**; the value is the technique's level (higher =
more skilled; it is also compared against `TECHn_SKILL1..5` thresholds to unlock
special moves into `WAZALIST` — see `FUN_003fab90`).

## BASE_UPCNT — X-Data power-ups (slot order CONFIRMED)

The `UPCNT` array holds the **X-Data Keeper power-up values** (the shop that
spends X-Data to permanently boost the 7 core stats + 4 elemental resistances).
It is stored per-species at `BASE_UPCNT[species*11 + slot]` (`+0xa3c`, 16×11 u32).

Slot order (CONFIRMED by tracing `FUN_003fa850`/`FUN_003fa3b0`/`FUN_003fab90`):

| Slot | Stat | Derivation |
| --- | --- | --- |
| 0 | **HP max** (MHP) | `MHP_INI + MHP_GROW*hp_factor/100 + UPCNT[0]` |
| 1 | **MP max** (MMP) | `MMP_INI + MMP_GROW*hp_factor/100 + UPCNT[1]` |
| 2 | **Strength** (TSUYOSA) | `STR_INI + STR_GROW*stat_factor/100 + UPCNT[2]` |
| 3 | **Defense** (MAMORI) | `AC_INI + AC_GROW*stat_factor/100 + UPCNT[3]` |
| 4 | **Wisdom** (KASHIKOSA) | `INT_INI + INT_GROW*stat_factor/100 + UPCNT[4]` |
| 5 | **Spirit** (SEISHIN) | `MND_INI + MND_GROW*stat_factor/100 + UPCNT[5]` |
| 6 | **Speed** (SUBAYASA) | `DEX_INI + DEX_GROW*stat_factor/100 + UPCNT[6]` |
| 7 | Fire resistance | base + `UPCNT[7]` |
| 8 | Ice resistance | base + `UPCNT[8]` |
| 9 | Thunder resistance | base + `UPCNT[9]` |
| 10 | Dark resistance | base + `UPCNT[10]` |

Evidence: the growth-key table at `0x004cf250` is `STR_INI AC_INI INT_INI
MND_INI DEX_INI` (stat index 0..4), and `FUN_003fa850` reads
`UPCNT[species*11 + 2 + stat_index]`; `FUN_003fa3b0` reads `UPCNT[species*11+0]`
for MHP and `UPCNT[species*11+1]` for MMP; `FUN_003fab90` reads
`UPCNT[species*11+7..10]` for the four resistances. Each stat is clamped to
**1..9999** after the final equipment/temporary additions (HP/MP instead
cap above at 99999). Growth factors are piecewise tables, not the raw level;
see the recovered [growth table and recalculation contract](../../port/docs/player-stats.md).
The displayed formulas above describe the base helpers before equipment.

### Technique → SKILL slot (all 9 CONFIRMED by dynamic probe)

The digimon-database columns are ordered `TECH1..TECH6` and the growth keys are
ordered `BLUNT_GROW SLASH_GROW STAB_GROW BASH_GROW SHOT_GROW CRUSH_GROW`
(`0x00519048..0x00519098`). Dynamic probing (`probe_techmap.ps2`, values 11–19)
confirmed the full mapping, including the three extra slots:

| technique | SKILL slot | `BASE_SKILL` index (species 3) | file offset |
| --- | --- | --- | --- |
| blunt | 0 | 27 | `+0x868` |
| slash | 1 | 28 | `+0x86c` |
| stab  | 2 | 29 | `+0x870` |
| bash  | 3 | 30 | `+0x874` |
| shot  | 4 | 31 | `+0x878` |
| crush | 5 | 32 | `+0x87c` |
| blast | 6 | 33 | `+0x880` |
| heal  | 7 | 34 | `+0x884` |
| force | 8 | 35 | `+0x888` |

**To edit the active digimon's technique levels**, write the desired value to
`BASE_SKILL[species*9 + slot]` (and mirror it in the second block). The tester's
Dorumon is **species 3** (its `BASE_LEVEL[3]`/`BASE_EXP[3]` are the ones that
advance); pass `--species` if the tester evolves.

### Level cap / display colour (dynamic)
- **Type is signed int32**: `0xFFFFFFFF` displays as **−1**, and a +1 gain
  wraps −1 → 0. So the full range is **`-0x80000000 .. 0x7FFFFFFF`**
  (−2,147,483,648 .. 2,147,483,647); the usable maximum is **`0x7FFFFFFF`**.
  Negative values are valid — the editor's advanced mode allows them.
- **No low display cap**: 99 is accepted and displayed.
- **Text colour scales with the level**: value 1 = white, value 99 = **orange**.
  (Likely the same white→blue→green→yellow→orange→pink scale used for item
  rarity — to be pinned down if needed.)
- `probe_maxed.ps2` (level 99) loaded cleanly and reported "56887 till next
  lvl" = `threshold(100) − threshold(99)` — consistent with the level formula.
- **99 is NOT the functional max**: some high-tier weapons require a technique
  skill level of **2500** to use. 99 is only a display cap; the real effective
  range goes at least to 2500 (full functional cap still TBD).

### Damage effect (UNRESOLVED — testing paused)
- `0x7FFFFFFF` at level 1 **overflows the damage calc**: bash-katana hit fell
  back to baseline (4–5), same as a level-1 character.
- Level 99 + tech 9 = 9–10 dmg (bash katana); level 1 + tech 1 ≈ 4–5 dmg.
- So damage appears dominated by **level/derived-STR**, and whether the
  technique level scales damage at all (vs. only unlocking `WAZALIST` moves)
  is not yet isolated. `tech_lvl99_all1.ps2` / `tech_lvl99_all99.ps2` are ready
  to close this when resumed (fix level 99, vary tech, compare bash-katana hits).

## Open questions

- Whether maxed technique level actually boosts damage in-game (pending the
  `tech_maxed_lvl1.ps2` damage test), and the effective (vs displayed) cap.
- The item **stat** database (id→base stats) still lives in the igBinary
  objects (see `docs/systems/enemy-data.md`); the rarity seed model is now CRACKED
  (`item_stat = base + (seed & 0x7FF)`, colour thresholds).

## Editing techniques

A technique edit is written into **both** mirrored 40 KB blocks with the per-block SUM checksum
recomputed — the layout and checksum are in [`save-format.md`](save-format.md).
