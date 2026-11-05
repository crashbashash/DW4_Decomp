# GAMERAM combat dispatcher: matched

`beNDMWGameRam::vfunc_34` at `0x3fca10` (41,864 bytes, 3,259 relocations) rebuilds byte-for-byte from
[`src/unmatched/Gap__Bec__beNDMWGameRam__vfunc_34.cpp`](../../src/unmatched/Gap__Bec__beNDMWGameRam__vfunc_34.cpp). It is the
parent command callback (GETCOMMON, GETPLAYER, CTRLITEM, FIGHTCALC, CTRLPLAYER and the rest of the 22-name `Message` enum) and
contains the 36,000-byte FIGHTCALC region with its 22 sub-commands: hit checks, damage and damage rank, critical, the status times,
EXP and skill gain, the Kouka magic and the attack-attribute lookup. `make check` reports 9,592 exact functions with zero mismatches
and `make link` is byte-identical to retail (findings [#1071](../findings/findings-1001-1250.md#f1071)-[#1073](../findings/findings-1001-1250.md#f1073)).

The source is a **model that reproduces the bytes**, not a claim of the original spelling: cleaned m2c output with reviewed ABI
repairs ([draft recovery](combat-draft-recovery.md)), RAII reference locals whose destructors reproduce the retail unwind table
([exception unwind](../engine/exception-unwind.md)), `volatile` reads where retail reloads, ternaries where an if/else adds alignment
nops, and declarations placed where the register colouring needs them ([register allocation](../engine/register-allocation.md)).

## What it takes to bank a function this size

* **Compiler:** the pinned alternate compiler at `-O3,p -Iinclude` with `#pragma inline_depth(1)` (the destructor wrappers stay
  out-of-line inside the callback and are expanded inside the destructor copies).
* **Ownership** (`config/SLUS-20836/unit-objects.json`, `0x003fca10`): nine `duplicates` (the compiler's own copies of destructors whose retail
  bodies live in other units: `0x1363f0`, `0x3d9d50`, `0x3d9cd0`, `0x3d9c50`, `0x3d9bd0`, `0x150eb0`, `0x130720`, `0x3e9110`,
  `0x406fa0`, four of them compared a second time under their own unit's compiler profile), `externals` (`__dl__FPv`, the copied-reference
  constructor and destructor) and `exceptions` (index `0x553b80`, table `0x544fd4`, 416 bytes). The verifier compares the owner's
  switch tables and exception data against retail exactly; anything undeclared is still rejected.
* **Two switch tables:** `0x519310` and `0x519370` (22 entries each) are compiled `.rodata` sections placed individually.
  `tools/layout.py` records a function's tables as one span (with the compiler's padding inside it), so `tools/linkgen.py` takes a
  compiled owner's individual tables from `config/SLUS-20836/jumptables.txt` and pins each at its own address.
* **Verification:** `python3 tools/dispatcher/full_verify.py src/unmatched/Gap__Bec__beNDMWGameRam__vfunc_34.cpp` (code, duplicates,
  tables, exception data), `tools/dispatcher/score.py` (per-region shape/exact/extra diff), `tools/dispatcher/bank.py` (rehearsal and
  banking), described in `the archived note `README.md`` and `BANKING.md`.

## How the registers were matched

The match rests on **source forms that change the compiler's graph-colouring order**: a virtual register's id follows
where its variable is declared, nodes are pushed in ascending id when their degree is below 25, and colours are assigned in reverse
push order. The receiver `this` is `s4` in retail; it stays `s0` when any of four hot FIGHTCALC regions leaves a wide clique of
simultaneously live webs. The tools for this are `tools/dispatcher/regalloc_trace.py` (the real compiler's colouring,
instrumented, including the second pass that produces the emitted registers) and `regalloc_sim.py` (replays simplify/select from a dump in
milliseconds so id permutations can be searched without recompiling). The same method also matches `FUN_003fab90` and the messenger
callees ([callees](combat-callees.md)).

## Remaining combat work

The two non-reproducible callees (`igStrCmp`, `Matrix44_Copy`) stay assembly. The dispatcher's dynamic behaviour (indirect call targets,
hit geometry, actor programs, spawning, progression) is separate recovery work; this page claims byte identity of the callback only.

## Typed members

The dispatcher's offset accesses are written as typed members, and the full verify (code, tables, exception data) is a
match with them: 61 `(char *)` occurrences remain and raw `*(int *)((char *)` loads **0**. Of the 61 left, 58 are casts on string-returning calls
(`beMessenger_GetString`, `beDataBase_GetRecordString`, `StringPool_Intern`, ...), not offsets; the three offset-style accesses that stay raw are
`(char *)arg2 + 0x14` (the callback's message argument has no recovered class) and two `(char *)obj + 0x28` member addresses of an object whose class is
not determined (passed to `DW4Fresh::Assign` and `FUN_003e92a0`). The property records (`+12` value), `igDataList` (`_count`), the byte list, the folder-list slots (`+20`
value) and `beSystem._random` (`+0x30`) are written as members; accesses that stay raw, with the reason, are in
typing1 (archived outside the repository), typing2 (archived outside the repository), typing3 (archived outside the repository), typing4 (archived outside the repository), typing5 (archived outside the repository). Several small identical record views (`DW4Property`, `DW4PropRec`,
`DW4IntProperty`, ...) exist side by side and can be merged into one when the shared types are promoted to
`include/dw4/reflected.h`.
