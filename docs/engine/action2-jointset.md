# `beAction2` JOINTSET handlers

The `beAction2` component block contains paired `JOINTSET` start/update handlers at
`0x00376f40` and `0x00376de0`. Their data layout is recovered from the reflection records and
the retail field accesses; the handlers are the reference semantics for the other component
types.

`beAction2JOINTSET` stores a time range in seconds (`_startTime` at `+0x0c`, `_endTime` at
`+0x10`) and a loop-mode string reference at `+0x14`. `beAction2InfoWork` receives the range in
nanoseconds: `_jointStartTimeL` at `+0x20`, `_jointEndTimeL` at `+0x28`, and the state at
`_jointSt0` (`+0x1c`). The conversion is:

```
nanoseconds = (int64)(seconds * 1,000,000,000 / 60)
```

The start handler selects state 1 when the loop-mode string begins with `L`, otherwise state 2.
It writes both converted endpoints, computes the node's current time, and sets the end flag
(`_jointIsEnd`, `+0x30`) to zero. Node time is stored in `beModelCtrlNode2`: `_time` is `+0x70`,
`_timeScale` is `+0x78`, and `_timeBias` is `+0x80`.

The update handler ignores states other than 1 and 2. It computes the node time from the shared
clock, then, **strictly while `end < now`** (verified against retail at `end = now−1, now, now+1`),
applies the current state:

- state 1 (loop): add `start - end` to the current time and keep checking;
- state 2 (one-shot): clamp the current time to `end` and mark `_jointIsEnd`.

When a change occurred, it rebases `_timeBias` against the engine clock in nanoseconds. The
clock is read at 2^18 ns granularity — `clock->_time >> 18` is a tick count of 262,144 ns, not a
frame count — truncated to 32 bits and converted as **unsigned**
(`(float)(unsigned int)(clock->_time >> 18)`); MWCC lowers that to the `dsll32`/`dsra32` +
`bltz` + `(x >> 1) | (x & 1)` doubling sequence seen in retail, not a plain `cvt.s.w` of a
signed value. The resulting time is written to `node->_timeBias`, and `_jointIsEnd` is set to
one.

The field offsets and the time units agree with the model-controller schedule used by the title
front end: JOINTSET ranges are frame counts at 60 fps, represented in the runtime as nanoseconds.
Both handlers, the node-clock helper, the float-to-int64 conversion and the WAITCHECK handlers that
consume the JOINTSET end flag are now behaviorally recovered and retail-verified;
[`action2-timing.md`](action2-timing.md) records the time model (including the EE's
round-toward-zero arithmetic, which makes 30 frames 499,999,968 ns rather than 500,000,000 ns).

## The component dispatch pair

The block's two drivers are recovered and banked (finding [#653](../findings/findings-0501-0750.md#f653)):

- `beAction2_StartComponents` (`0x00377700`, 456 B) is the per-object Start driver. It walks the
  `beAction2Data`'s component list — an `igObjectList`-shaped `{_count, _capacity, _data}` struct at
  `_comList` — and calls each component's virtual `GetMetaObject()` to route it to one of the five
  `*_Start` handlers, advancing `_comIndex` and stopping at the first handler that returns false.
- `Gap::Bec::beAction2::vfunc_31` (`0x003778d0`, 192 B) is the per-frame Update driver. After the
  info's `+0x14` gate and the work's `+0x4c` gate it calls each active component's `*_Update` in type
  order (MOTIONSET, JOINTSET, FADESET, WAITCHECK, FLASHSET), keyed on the work's
  `+0x14`/`+0x1c`/`+0x34`/`+0x44`/`+0x48` "started" slots.

What made the Start driver match was recovering the original **pointer-typed list layout** and
expressing the dispatch as a real C++ virtual call (`component->GetMetaObject()`), not an offset cast:
the untyped draft would not allocate retail's registers. Both drivers also need retail's **scheduler
padding** written out as explicit `asm{nop}` — two in the Start driver (after the FLASHSET branch and
at the loop exit), four in the Update driver (after the delay slot of each `*_Update` `jal`). The
Start driver needs the `-O3,p` per-unit override; the Update driver does not.

The five handler pairs remain the open part of the block (finding [#654](../findings/findings-0501-0750.md#f654)). Every one reconstructs to
within a few instructions but none reaches byte-exactness — the same scheduler/allocator wall the
JOINTSET pair hits. A C++ **typed work struct** (base+offset member access instead of
`(char *)work + const`) is necessary: it removes a spurious saved address register and restores
retail's frame size, and for FLASHSET a two-case `switch` reproduces retail's `beq case1 / beqz
case0` dispatch. What remains is MWCC's load scheduler and callee-saved allocation —
`beAction2WAITCHECK_Update` is 380/372 B (the scheduler keeps an `s1+40` address live where retail
reloads `40(s1)`; the compare lands in `v1`, not `at`), and `beAction2FLASHSET_Update` is 364/376 B
(work and the `+0x88` object swap between `s0`/`s1`, and the DAT address `lui` is scheduled into a
branch-delay slot retail pads with a `nop`). They are parked, not banked.

That this is not a source-*shape* problem is confirmed two ways. Pointed at the
`beAction2FLASHSET_Update` target from the typed source, **decomp-permuter ran ~68k candidates and
never scored below 585** (a match is 0), and from the plain m2c draft it found no verified match
either — the residual is MWCC's register allocator and instruction scheduler, which the mutator
cannot reach. The harness is validated end-to-end: the same project built from an already-matched
unit (`Gap::Bec::beBaseInfoManager::vfunc_21`) reports `base score = 0` and exits. (The permuter's
parser cannot read the `asm { nop }` padding the dispatch pair needs, so those units are matched by
hand rather than permuted.)

## Matching status

The pair is **not banked**: both handlers are reconstructed to within a few scheduler slots but
have not reached byte-exactness, and the verifier is fail-closed.

The optimisation **sub-flag** `p` (peephole) split is confirmed and now expressible: the retail ELF
was built with **per-file** flags, recorded as finding [#646](../findings/findings-0501-0750.md#f646). Under `-O3` MWCC materialises an
integral `1e9f` literal as an integer + `cvt.s.w`; with any level that carries `,p`
(`-O2,p`/`-O3,p`/`-O4,p`) it loads the IEEE-754 bits `0x4e6e6b28` directly
(`lui 0x4e6e; ori 0x6b28; mtc1`), which is what retail does. The sub-flag has no source-level
equivalent (`#pragma peephole`, `#pragma opt_peephole`, `#pragma optimization_level` are all
ignored), and the neighbouring `FUN_0015e130` popcount matches only *without* `,p`.

The repo now supports per-unit flags (`config/SLUS-20836/unit-flags.tsv`, keyed by function VA, consulted by
`tools/unitflags.py` from both `tools/verify.py` and `tools/linkgen.py`; finding [#648](../findings/findings-0501-0750.md#f648)). A
`--unit-flags PATH` argument (or `/dev/null`) lets a sweep disable the table; the table is a
committed hand-authored overlay like `config/SLUS-20836/names/*.tsv`.

`-O3,p` is **not** by itself enough to bank the pair. With the flag pinned and the source idioms
(finding [#647](../findings/findings-0501-0750.md#f647)) applied, `beAction2JOINTSET_Start` stands at 316/324 bytes: instructions 0..16
match, but two scheduler `nop`s never appear (one after the state branch's delay slot, one after
the `mtc1` of `60.0f` in the first conversion), and the float register allocation differs (retail
keeps the `1e9f` constant in `f1`, the loaded time in `f2`, `60.0f` in `f0`; every tested spelling
of the conversion — operand order, integer-cast constant, explicit float temp — places them
differently, and no `-O` level from `-O2` to `-O4` changes it). `beAction2JOINTSET_Update` is 332B
retail vs ~320B, with the state guard's compare order and `work`'s `s`-register differing.

A two-flag sweep of all 2,954 near-miss draft candidates in `build/m2c` under `-O3` and `-O3,p`
found **no** `,p`-only match (the 130 that match, match under both and are already banked), so the
flag is a forward-looking capability rather than an immediate bank. The pair stays fail-closed; its
residual is a scheduler/allocator wall, not a flag or source-idiom one.

`beAction2JOINTSET_Update` calls `FUN_00398e80` (node-time helper) plus `FUN_00230110`
(float→nanosecond conversion).
