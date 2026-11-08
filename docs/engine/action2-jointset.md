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

The block's two drivers are recovered and banked:

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

All five handler pairs match retail: they verify byte-identical from `src/unmatched/` with `-O3,p`
under the alternate compiler (the `combat` profile in `config/SLUS-20836/units.tsv`). A C++ **typed work
struct** (base+offset member access instead of `(char *)work + const`) is necessary: it removes a
spurious saved address register and restores retail's frame size. For FLASHSET a two-case `switch`
reproduces retail's `beq case1 / beqz case0` dispatch.

## Message handling

`beModelCtrl` is a `beAction2`: the two share vtable slots 21-34. `beModelCtrl::vfunc_33` (`0x396a80`)
holds the controller's message handling and resolves string-keyed ids through
`beMessenger_ResolveEnumValue` (`0x38d4a0`). Its 33-entry `MsgAction` table is at `0x4c58f0`, built by
`FUN_00356ab0`:

| ids | names |
| --- | --- |
| 0-4 | `GENERATE`, `GENERATE_NDSP`, `REMOVE`, `GETINFONAME`, `GETINFONAME_RUN` |
| 5-9 | `SETMATRIX`, `CHKBULLET`, `SETLABEL`, `SETEFFECT`, `SETSOUND` |
| 10-13 | `GETMATRIX`, `GETMATRIX_ALL`, `GETMATRIX_ACTIVE`, `GETTRCDATA` |
| 14-17 | `GETHP`, `SETHP`, `GETRECNO`, `ACTION1` |
| 18-21 | `ONCTRL`, `OFCTRL`, `ONFREEZE`, `OFFREEZE` |
| 22-24 | `SETLODHIGH`, `RESETLODHIGH`, `MOVETRANS` |
| 25-27 | `SETCONVEYOR`, `SETQUICKSAND`, `SETSLIPPEDFLOOR` |
| 28-32 | `ISRUN`, `ISSEQNAME`, `ONHITBULLETBOX`, `OFHITBULLETBOX`, `GETSEQNAMELIST` |

`beAction2::vfunc_33` (`0x377990`) uses a 7-entry table at `0x4c81f0`, built by `FUN_0036dcd0`: 0 `ISCOMEND`,
1 `ISRUN`, 2 `GETNAMELIST`, 3 `GETAPPEARANCELIST`, 4 `GETBONEMATRIX`, 5 `ONFREEZE`, 6 `OFFREEZE`. Any other
name starts or stops the action, stopping only for `NDSP`.

`beAction2InfoWork` is created lazily by `FUN_0036c2a0` and sits at `beAction2+0x38`. A controller
message's argument bag is `S = beModelCtrl+0x14`, `W = S+0x10`, with typed parallel lists at `W+0x10`
(bytes), `+0x14` and `+0x18` (int), `+0x1c` (long), `+0x20` (vec3, stride 0xc), `+0x24` (mat4, stride 0x40),
`+0x28` (object refs) and `+0x2c` (strings). `beMessengerArgData_Clear` (`0x38ca40`) clears them; the
accessors are `beMessenger_AppendBool`, `AppendInt`, `GetInt`, `GetFloat`, `GetVec3`, `AppendMatrix`,
`GetMatrix`, `AppendObject`, `GetObject`, `AppendString` and `GetString` (`0x38f150..0x38f8f0`).

## Matching status

Both JOINTSET handlers match under the `combat` profile (`-O3,p`).

`beAction2JOINTSET_Start` gets retail's integer register allocation (`work->_jointSt0` in `s1`, params in
`s0`, node reusing `s0`) only when the bias goes through a `long long` temporary for the start time:
`long long st = work->_jointStartTimeL; node->_timeBias = st - (__fixsfdi(conv * node->_timeScale) << 18);`.
The literal's spelling does not matter: `1e9f` and `1000000000.0f` fold identically.

The optimisation **sub-flag** `p` (peephole) matters here: the retail ELF was built with **per-file**
flags. Under `-O3` MWCC materialises an integral `1e9f` literal as an integer + `cvt.s.w`; with any level
that carries `,p` (`-O2,p`/`-O3,p`/`-O4,p`) it loads the IEEE-754 bits `0x4e6e6b28` directly
(`lui 0x4e6e; ori 0x6b28; mtc1`), which is what retail does. The sub-flag has no source-level
equivalent (`#pragma peephole`, `#pragma opt_peephole`, `#pragma optimization_level` are all
ignored), and the neighbouring `FUN_0015e130` popcount matches only *without* `,p`.

A unit's flags are its profile in `config/SLUS-20836/units.tsv`. `config/SLUS-20836/unit-flags.tsv`, keyed
by function VA and consulted through `tools/unitflags.py` by both `tools/verify.py` and
`tools/linkgen.py`, holds per-function overrides. A `--unit-flags PATH` argument (or `/dev/null`) lets a
sweep disable the table; the table is a committed hand-authored overlay like
`config/SLUS-20836/names/*.tsv`.

`beAction2JOINTSET_Update` calls `FUN_00398e80` (node-time helper) plus `__fixsfdi`
(float→nanosecond conversion).

## What didn't work

Everything here was measured under the default compiler. The differences are that compiler's, not a
limit of the source: the same handlers match under the `combat` profile.

- `-O3,p` with the source idioms applied leaves `beAction2JOINTSET_Start` at 316/324 bytes: instructions
  0..16 match, but two scheduler `nop`s never appear (one after the state branch's delay slot, one after
  the `mtc1` of `60.0f` in the first conversion), and the float register allocation differs (retail
  keeps the `1e9f` constant in `f1`, the loaded time in `f2`, `60.0f` in `f0`; every tested spelling of
  the conversion — operand order, integer-cast constant, explicit float temp — places them differently,
  and no `-O` level from `-O2` to `-O4` changes it). `beAction2JOINTSET_Update` is 332 B retail vs ~320 B,
  with the state guard's compare order and `work`'s `s`-register differing.
- `beAction2WAITCHECK_Update` stays at 380/372 B (the scheduler keeps an `s1+40` address live where retail
  reloads `40(s1)`; the compare lands in `v1`, not `at`), and `beAction2FLASHSET_Update` at 364/376 B
  (work and the `+0x88` object swap between `s0`/`s1`, and the DAT address `lui` is scheduled into a
  branch-delay slot retail pads with a `nop`).
- decomp-permuter, pointed at `beAction2FLASHSET_Update` from the typed source, ran ~68k candidates and
  never scored below 585 (a match is 0), and from the plain m2c draft it found no verified match
  either. The harness itself is sound: the same project built from an already-matched unit
  (`Gap::Bec::beBaseInfoManager::vfunc_21`) reports `base score = 0` and exits. The permuter's parser
  cannot read the `asm { nop }` padding the dispatch pair needs, so those units are matched by hand.
- A two-flag sweep of all 2,954 near-miss draft candidates in `build/m2c` under `-O3` and `-O3,p` found no
  `,p`-only match: the 130 that match do so under both.

## Open questions

- Unproven beyond `j_startback` (`AREA.AFS` entry 620): a model has two parallel registries.
  `beModelCtrlInfo` holds the sequences (`beModelCtrlInfoDataSeq`, `SQ_*` as `beModelCtrlData`) and
  `beAction2Info` holds the actions (`beAction2Data`). `beModelCtrlACTION`, `JUMP` and `WCHECK` records carry
  only a name: an ACTION step appears to link to the `beAction2Data` of the same name, and a JUMP to a
  sequence by name. `scripts/modelctrl_dump.py` prints the chains. Check this against another pack and
  the runtime lookup.
