# Player → enemy hit, critical chance and damage (`FIGHTCALC`)

How the retail game decides whether a player's hit is a **critical** and how much damage it does,
including the critical bonus. Recovered from the retail ELF and checked live against a running game
(see [Verification](#verification)). Related: the weapon/skill storage in
[`techniques.md`](techniques.md), the enemy columns in [`enemy-data.md`](enemy-data.md), and the
property system in [`../engine/property-system.md`](../engine/property-system.md).

## Matching recovery boundary

FIGHTCALC is a nested command family of `beNDMWGameRam_OnMessage`, not a
standalone function. Its setup and cases occupy the contiguous physical region
`0x003fde30..0x00406ad0` (36,000 bytes), sharing the enclosing 41,864-byte
dispatcher's frame and return. The original name table is `FightCom`, with 22
commands covering both directions of hit/damage/status calculations, EXP,
skill growth, player-to-player magic and player attack element lookup.
The [generated inventory](combat-inventory.md) records the switch targets,
direct calls, unresolved indirect call sites and actual source coverage.
The [three immediate helpers](combat-helpers.md) are
the 128-byte deleting destructor, 132-byte technique-row lookup and 652-byte
nearby query, totaling 912 bytes.
The [26 contiguous BLT/BLP Lua helpers](combat-lua-api.md) total 5,372 bytes.
The calculation dispatcher itself is
`src/game/beNDMWGameRam.cpp`.
The [draft recovery notes](combat-draft-recovery.md) describe its reviewed
argument slots, byte/word access widths, address units and protected repairs.
Its three [reference-ownership helpers](combat-reference-helpers.md) total
316 bytes, with explicit release/assignment call slots in the
generated analysis context.

The 26 contiguous BLT/BLP Lua helpers are
wrappers separate from the calculation rules. Five status-duration
helpers had disjoint Ghidra bodies whose byte counts truncated their epilogues.
Reviewed spans restore eight bytes apiece without changing retail bytes. The full dispatcher's reviewed
span ends at `0x00406d98`, before eight padding bytes.

The initial whole-dispatcher m2c draft references undefined incoming
`saved_reg_s0`/`saved_reg_s3`. Known accessor signatures remove spurious call
arguments containing `MULT_HI` in a later draft.
The initial report that only one switch table was emitted is refuted: the
compiler emits two different sections both named `.rodata`. Verification and
linking now preserve their section indices, individual relocations and separate
retail placements, including the raw padding between tables. Six
regressions cover an independent GNU link, both table contents, corrupt/missing
tables, unresolved relocations and preserved layout gaps.
These drafts remain private, outside `src/`; removing
or initializing incoming registers requires the path checks below. The per-case
addresses below are interior labels, not independently
bankable functions.

The full callback also needs its unused middle ABI argument preserved: receiver
is `a0`, command object is `a2`, and omitting the `a1` slot shifts the command to
the wrong register. Its seven matrix and fifteen vector scratch buffers cannot
remain m2c's guessed four-byte integers: known callees write 64 and 12 bytes
respectively. Correcting widths alone does not match the original frame; the
diagnostic grows from 720 to 1,328 bytes versus the original 1,200.
Using the reviewed call slots and aggregate types together now reproduces the
original 1,200-byte frame in a diagnostic; the instructions still differ.
Generate the flat decompiler context with
`python3 scripts/gen_combat_context.py`, then pass
`--context build/combat-context.c` to the m2c pipeline. It reuses the generated
reflected receiver and models four-byte reference words, scalar calls, `f12`
float append, matrices/vectors and the skill/resistance tables. Resulting drafts
still need standalone declarations, pointer-stride cleanup and full verification.

Attack-category recovery also required a decompiler arithmetic correction:
signed multiply-high by `0x68db8bad`, arithmetic shift by 12 and addition of the
logical sign bit form one signed division by 10000. Upstream m2c retained an
extra sign correction after prematurely folding the product. The constrained
compatibility rule and full-domain integer proof are in
[`tools/m2c_compat.py`](../../tools/m2c_compat.py) and
[`testing/test_m2c_compat.py`](../../testing/test_m2c_compat.py).
The correction now covers eleven reviewed reciprocal/shift pairs for divisors
3, 5, 10, 20, 40, 50, 80, 100, 400, 1000 and 10000, each proved over the complete
signed 32-bit domain. The unshifted `/3` case needs separate
positive and negative endpoint bounds. Partial expressions separated by control-flow
merges can remain `MULT_HI`; they need an actual signed high-product expression,
not an undeclared helper call or a premature truncating division.

## Incoming register and return checks

`python3 scripts/verify_combat_initialization.py` checks the reviewed retail
callback with a conservative constant domain. Loads and call results are
unknown, caller-save constants are dropped after call delay slots, and the two
switches retain all their targets. On paths before the first `s0` assignment,
the only incoming-register snapshot is the verified prologue save; no gameplay
read remains. The apparent critical-bonus read cannot be reached from the
zero-base-damage path because damage stays zero and the later guards skip it.
Changing just that path's zero assignment to one exposes six reads, making the
counterfactual check sensitive to the guard.

The `P2ESKILLUP` row search has a separate domain condition. Its original level
arithmetic admits a current skill only below these thresholds:

| Level | Admission threshold |
| --- | --- |
| 1–36 | `30 × level` |
| 37–107 | `20 × level + 360` |
| 108–227 | `10 × level + 1430` |
| 228–999 | `8 × level + 1884` |

The largest threshold is 9876; the final search boundary is 10000. Every skill
admitted at levels 1–999 therefore finds a row and assigns `s3`. This is
a pre-increment gate, not the maximum stored skill. Out-of-range edited levels
are outside the proof and can exhaust the search without assigning the index;
do not add a zero initialization to conceal that path. Six regression checks
cover original instructions, the nonzero-damage counterfactual, all 999 level
caps, a lowered final search boundary, unsupported opcodes and changed switches.
This constrained analysis does not establish complete callback equivalence.

The enclosing `CTRLITEM` case also needs its acknowledged return preserved:
its paths return one through `0x3fde08`/`0x3fde10`, even for an unhandled
subgroup/action. The draft's outer-switch `break` followed by falling off an
integer function loses that result.

## Where the code is

Lua asks the native `FIGHTCALC` object for a result by key name. `BLTisCritical`
(`0x003749a0`, [`src/game/be.cpp`](../../src/game/be.cpp)) sends the key `P2EISCRITICAL` plus three ints
(the MDL cache fields `0x58a208`, `0x58a1f4`, `0x58a1fc`) and reads a bool back; it contains no
game logic. The handlers sit in one dispatcher switch:

| Piece | Address |
|---|---|
| Key-name table (22 pointers, `E2PISHITCHECK` first) | `0x004cc350` |
| Name → id dictionary builder | [`FightCom_GetMetaEnum`](../../src/game/ndmw/beNDMWGameRam.inc), `0x003c9be0` (second table at `0x004cc3b0` is just ids 0–21); 84 bytes |
| Dispatcher jump table (22 entries) | `0x00519310` |
| Case 2, `P2EISCRITICAL` | `0x003fe130` |
| Case 5, `P2EDAMAGE` | `0x003fe550`–`0x003ff030` |

## Does the hit crit? (`P2EISCRITICAL`)

Arguments: `arg0` attacker index, `arg1` target row, `arg2` attack code. `arg2 / 10000 == 4` marks a
technique; otherwise it is a weapon hit. `rand` is the game RNG, see [`rng.md`](rng.md).

| Hit | Crit when |
|---|---|
| Weapon | `rand % 200 < CHIMEIRITSU` of the attacker's property folder (chance `CHIMEIRITSU / 200`) |
| Technique, no element | `rand % 100 < tech.CHIMEIRITSU` (`pcTech` database row) |
| Technique, with element | `rand % 1000 < (tech.CHIMEIRITSU + 100) × ⌊10000 / (⌊1.2 × enemy.RES_<element>⌋ + 50)⌋ / 100` |

The element comes from the technique's `ZOKUSEI` (`fire`, `ice`, `thunder`, `dark`, `poison`);
`RES_*` is read from the `enemy` database row of the target. All divisions are integer.

## Damage (`P2EDAMAGE`)

Arguments: `arg0` attacker index, `arg1` target row, `arg2` attack code, `arg3` **critical flag**,
plus a pointer argument. Let `S = SKILL[WEAPONSKILLNO]` for a weapon hit, or the same array indexed by
the technique's `SKILL` column for a technique.

1. **Base damage**
   - Weapon: `(6·TSUYOSA + 4·S) / D`, where `D` is `MAMORI − down[5]`. `down[5]` is the target work's
     `_downDataList` entry 5, the power-down defence, zero without a status (`D` is about 125 for a row-5
     Goblin in the test state).
   - Technique: `(20·(−tech.HP) + 10·KASHIKOSA + 5·S) / enemy.SEISHIN`.
2. **Element**
   - Technique with an element: `dmg × (1000 − enemy.RES_<element>) / 1000`.
   - Weapon with an element: `dmg += dmg × (1000 − enemy.RES_<element>) / 1000`, only when
     `enemy.RES_<element> < rand % 1000`. For a weapon hit this is a chance of a bonus, not a multiplier.
3. Clamp to `0..99999`.
4. **Critical bonus** (when `arg3 != 0`): `dmg += dmg × bonus / 100`, with

   | `S` | `bonus` (percent) |
   |---|---|
   | ≤ 1000 | `S / 20 + 30` (30–80) |
   | 1001–2000 | `(S − 1000) / 50 + 80` (80–100) |
   | > 2000 | `(S − 2000) / 100 + 100` (100 and up) |

   `SKILL` values run to 9999, so the largest bonus is 179 percent (2.79× the normal hit).
5. **Random spread**: `r = rand % (25 × dmg)`, then by `rand & 3`: `(950·dmg + r) / 1000`,
   `(975·dmg + r) / 1000`, `(1000·dmg + r) / 1000`, `(1025·dmg + r) / 1000`. The last roll also sets the
   high-roll flag returned to the script.
6. Clamp to `0..99999`.
7. Weapon hits then apply `HPDRAIN` and `MPDRAIN` (percent of the damage) to the attacker.

The handler returns damage, element index (−1 for none) and the high-roll flag.

## What `S` is

`WEAPONSKILLNO` is a slot number 0–8 copied from the equipped weapon's `SKILL` attribute when stats are
recalculated. `SKILL` is the player's 9-slot integer array
([`techniques.md`](techniques.md)); Bash is slot 3. `S` is the player's value in that slot, not the
weapon type itself.

## Verification

Static: the cases above were read from the disassembly. Live: in a savestate with an ordinary Goblin
(649 HP), the player's `TSUYOSA`, `CHIMEIRITSU`, `WEAPONSKILLNO` and `SKILL` values were written in RAM
and the Goblin's HP delta was read after each hit (strength 2000, HP reset between swings).

| Setup | Normal hit | Crit hit (`CHIMEIRITSU` 200) | Crit ÷ normal | Formula |
|---|---|---|---|---|
| `S` = 0 | ~96 | 117–124 | ~1.2–1.3 | 1.30 |
| `S` = 1500 | ~146 | 270–276 | ~1.85–1.9 | 1.90 |
| `S` = 5000 | 247–260 | 559–568 | ~2.25 | 2.30 |

Index test: with `SKILL[3] = 5000` and `SKILL[1] = 0`, `WEAPONSKILLNO = 3` gave 238–255 (crit 559) and
`WEAPONSKILLNO = 1` gave 90–97 (crit 114), so the routine reads `SKILL[WEAPONSKILLNO]`. Some swings hit
twice and the ±5 percent spread shows in the numbers.

## Open

- That `arg3` is exactly the `BLTisCritical` result at the Lua call site (it behaves as the critical flag).
- The technique and elemental crit-chance rows and the technique base formula are from the disassembly
  only; they were not exercised live.
- `WEAPONSKILLNO` was written directly; a live equip of a real Bash Katana was not watched.
