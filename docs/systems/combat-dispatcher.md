# GAMERAM combat dispatcher

`beNDMWGameRam::vfunc_34` at `0x3fca10` (41,864 bytes, 3,259 relocations) is a member of the whole-file unit
[`src/game/beNDMWGameRam.cpp`](../../src/game/beNDMWGameRam.cpp) (`0x3f6620`-`0x407080`), at its retail position after
`beNDMWGameRam_CollectNearbyNonzeroHp`. It is the
parent command callback (GETCOMMON, GETPLAYER, CTRLITEM, FIGHTCALC, CTRLPLAYER and the rest of the 22-name `Message` enum) and
contains the 36,000-byte FIGHTCALC region with its 22 sub-commands: hit checks, damage and damage rank, critical, the status times,
EXP and skill gain, the Kouka magic and the attack-attribute lookup.

The parent command switch uses the 22-name table at `0x4cc410` and the jump table at `0x519370`:

| command | name |
| --- | --- |
| 0 | GETCOMMON |
| 1-5 | GETPLAYER, GETPLAYER1, GETPLAYER2, GETPLAYER3, GETPLAYER4 |
| 6 | GAMEDATAINIT |
| 7 | GAMESTART |
| 8 | GAMEREMOVE |
| 9 | ADDHP |
| 10 | ADDMP |
| 11 | RECALCPLAYER |
| 12 | BASE2CURRENT |
| 13 | CURRENT2BASE |
| 14 | WEAPONEQUIPCHECK |
| 15 | WEAPONEQUIPSTRONG |
| 16 | DEADRESTART |
| 17 | CTRLITEM |
| 18 | FIGHTCALC |
| 19 | DISPFIGHTDATA |
| 20 | BKCHIPBITEXP |
| 21 | CTRLPLAYER |

The source is a **model that reproduces the bytes**, not a claim of the original spelling: cleaned m2c output with reviewed ABI
repairs ([draft recovery](combat-draft-recovery.md)), RAII reference locals whose destructors reproduce the retail unwind table
([exception unwind](../engine/exception-unwind.md)), `volatile` reads where retail reloads, ternaries where an if/else adds alignment
nops, and declarations placed where the register colouring needs them ([register allocation](../engine/register-allocation.md)).

## What it takes to bank a function this size

* **Compiler:** the unit's Ndmw profile, b52 `-O4,p -sdatathreshold 2 -inline level=8,bottomup -Iinclude` with exceptions on, and
  no pragma. Under bottom-up inlining the compiler stops expanding nested inline calls once a function passes
  `inline_max_total_size` (10,000 expression-node units; the dispatcher measures about 19,000), so each destructor wrapper is
  expanded at its call site while the release helper inside it stays an out-of-line call (`0x3e9110`, `0x406fa0`); the
  destructor copies and the unit's small functions inline fully.
* **Ownership** (`config/SLUS-20836/unit-objects.json`, the unit row `0x003f6620`, measured by `tools/whole_file_rows.py`):
  the dispatcher is an `emitted` member, as is `release__9StringRefFPPc` at `0x406fa0` (the out-of-line copy of
  `StringRef::release` the dispatcher calls). Destructors whose retail bodies live in other units are `duplicates` (`0x1363f0`,
  `0x3d9d50`, `0x3d9cd0`, `0x3d9c50`, `0x3d9bd0`, `0x150eb0`, `0x130720`, `0x3e9110`); the copied-reference constructor and
  destructor are `externals`. The exception record (index `0x553b80`, table `0x544fd4`, 416 bytes) comes from
  `config/SLUS-20836/exceptions.txt`. The verifier compares switch tables and exception data against retail exactly; anything
  undeclared is still rejected.
* **Two switch tables:** `0x519310` and `0x519370` (22 entries each) are compiled `.rodata` sections placed individually.
  `tools/layout.py` records a function's tables as one span (with the compiler's padding inside it), so `tools/linkgen.py` takes a
  compiled owner's individual tables from `config/SLUS-20836/jumptables.txt` and pins each at its own address.
* **Verification:** `python3 tools/check.py --no-cache --function 0x3f6620 --cand src/game/beNDMWGameRam.cpp` (the whole unit,
  including `MATCH emitted 0x3fca10 Gap__Bec__beNDMWGameRam__vfunc_34 41864B`).

## How the registers were matched

The match rests on **source forms that change the compiler's graph-colouring order**: a virtual register's id follows
where its variable is declared, nodes are pushed in ascending id when their degree is below 25, and colours are assigned in reverse
push order. The receiver `this` is `s4` in retail; it stays `s0` when any of four hot FIGHTCALC regions leaves a wide clique of
simultaneously live webs. The tools for this are `tools/dispatcher/regalloc_trace.py` (the real compiler's colouring,
instrumented, including the second pass that produces the emitted registers) and `regalloc_sim.py` (replays simplify/select from a dump in
milliseconds so id permutations can be searched without recompiling). The same method also matches `FUN_003fab90` and the messenger
callees ([callees](combat-callees.md)).

## Scope

`strcmp` is newlib's R5900 assembly (`src/newlib/strcmp.S`). The dispatcher's dynamic behaviour (indirect call targets,
hit geometry, actor programs, spawning, progression) is outside this page.

## Typed members

The dispatcher's offset accesses are written as typed members, and the full verify (code, tables, exception data) is a
match with them: 61 `(char *)` occurrences remain and raw `*(int *)((char *)` loads **0**. Of the 61 left, 58 are casts on string-returning calls
(`beMessenger_GetString`, `beDataBase_GetRecordString`, `StringPool_Intern`, ...), not offsets; the three offset-style accesses that stay raw are
`(char *)arg2 + 0x14` (the callback's message argument has no recovered class) and two `(char *)obj + 0x28` member addresses of an object whose class is
not determined (passed to `DW4Fresh::Assign` and `ObjectRef_Get_003e92a0`). The property records (`+12` value), `igDataList` (`_count`), the byte list, the folder-list slots (`+20`
value) and `beSystem._random` (`+0x30`) are written as members. Several small identical record views (`DW4Property`, `DW4PropRec`,
`DW4IntProperty`, ...) exist side by side and can be merged into one when the shared types are promoted to
`include/dw4/reflected.h`.
