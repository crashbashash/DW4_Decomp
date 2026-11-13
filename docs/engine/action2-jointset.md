# `beAction2`: action components and messages

`beAction2` plays a model's actions: each running `beAction2InfoRam` walks the components of one
`beAction2Data` (MOTIONSET, JOINTSET, FADESET, WAITCHECK, FLASHSET) and updates the started ones every
frame. The paired `JOINTSET` start/update handlers at `0x00376f40` and `0x00376de0` are the reference
semantics for the other component types.

## Source

`src/game/beAction2.cpp` is one translation unit, `bec_beAction2` (`0x00375e00`–`0x00378420`),
compiled whole under the `-O4,p -inline level=8,bottomup` profile.

| Start | Bytes | Symbol | Role |
|---|---:|---|---|
| `0x00375e00` | 8 | `beAction2_Prepare` | empty (slot 32, which `beBaseInfoManager` calls before it starts and before it drops its infos) |
| `0x00375e10` | 12 | `beAction2_GetInfoMeta` | returns the `beAction2Info` meta object (slot 30) |
| `0x00375e20` | 68 | `beAction2_RegisterReceiver` | registers the ram as receiver of `ACTION`, clears `_isRun`, sets `g_enbayaPlayOnceEndOffset` to −1/30 (slot 29) |
| `0x00375e70` | 376 | `beAction2FLASHSET_Update` | when the `FLASH` timer expires, removes the flash's override attributes from the node |
| `0x00375ff0` | 848 | `beAction2FLASHSET_Start` | colour, texture-state and lighting-state overrides; red and green to 1.0, texturing and lighting off, a four-frame `FLASH` timer |
| `0x00376340` | 372 | `beAction2WAITCHECK_Update` | see [timing](action2-timing.md#waitcheck) |
| `0x003764c0` | 448 | `beAction2WAITCHECK_Start` | see [timing](action2-timing.md#waitcheck) |
| `0x00376680` | 684 | `beAction2FADESET_Update` | steps the alpha by the `FADE` timer's frame delta: in up to the limit (then removes the overrides), or out to zero |
| `0x00376930` | 1,200 | `beAction2FADESET_Start` | `H…` clears the ram's bit in the info switch's `_childMask`; otherwise colour, blend-state and lighting-state overrides and a fade in (`I…`) or out |
| `0x00376de0` | 340 | `beAction2JOINTSET_Update` | below |
| `0x00376f40` | 324 | `beAction2JOINTSET_Start` | below |
| `0x00377090` | 680 | `beAction2MOTIONSET_Update` | waits a frame, updates the combiner while it blends, then moves the remaining state onto the node's time scale |
| `0x00377340` | 960 | `beAction2MOTIONSET_Start` | plays the named animation on the ram's combiner with a hokan (transition) blend; hokan mode `S` freezes the outgoing/incoming state, loop mode `L` loops |
| `0x00377700` | 456 | `beAction2_StartComponents` | the component walker |
| `0x003778d0` | 192 | `beAction2_Update` | the per-frame driver (slot 31) |
| `0x00377990` | 2,644 | `beAction2_OnMessage` | message handler (slot 33) |
| `0x003783f0` | 12 | `beAction2_GetMeta` | returns the `beAction2` meta object (slot 20) |
| `0x00378400` | 8 | `Gap::Core::igObject::vfunc_28` | shared empty default |
| `0x00378410` | 8 | `Gap::Core::igObject::vfunc_34` | shared default returning 0 |

The attribute objects come from `igColorAttr_CreateInstance`, `igBlendStateAttr_CreateInstance`,
`igTextureStateAttr_CreateInstance` and `igLightingStateAttr_CreateInstance`, and each takes its value
through its slot 30. The stack references to them are `AttrRef<kind>`, whose destructors retail keeps from
other units (`config/SLUS-20836/unit-objects.json`, `duplicates`).

## JOINTSET

`beAction2JOINTSET` stores a range in 60 fps frames (`_startTime` at `+0x0c`, `_endTime` at
`+0x10`) and a loop-mode string reference at `+0x14`. `beAction2InfoWork` receives the range in
nanoseconds: `_jointStartTimeL` at `+0x20`, `_jointEndTimeL` at `+0x28`, and the state at
`_jointSt0` (`+0x1c`). The conversion is:

```
nanoseconds = (int64)(frames * 1,000,000,000 / 60)
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
clock is read at 2^18 ns granularity (`clock->_time >> 18` is a tick count of 262,144 ns, not a
frame count), truncated to 32 bits and converted as **unsigned**
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

## The component drivers

- `beAction2_StartComponents` (`0x00377700`, 456 B) is the per-ram Start driver. It walks the
  `beAction2Data`'s component list (an `igObjectList`-shaped `{_count, _capacity, _data}` struct at
  `_comList`) and calls each component's virtual `GetMetaObject()` to route it to one of the five
  `*_Start` handlers, advancing `_comIndex` and stopping at the first handler that returns false.
- `beAction2_Update` (`0x003778d0`, 192 B) is the per-frame Update driver. After the ram's
  `_isRun` gate and the work's `_isFreeze` gate it calls each active component's `*_Update` in type
  order (MOTIONSET, JOINTSET, FADESET, WAITCHECK, FLASHSET), keyed on the work's
  `_motionSt0`/`_jointSt0`/`_fadeSt0`/`_waitSt0`/`_flashSt0` state slots.

The Start driver matches only with the **pointer-typed list layout** and the dispatch written as a real
C++ virtual call (`component->GetMetaObject()`). Its guard reads the list through its own struct view,
because the compiler would otherwise merge that load with the ones in the loop, where retail reloads the
list for the guard, the body and the latch.

## Message handling

`beModelCtrl` is a `beAction2`: the two share vtable slots 21-34. `beModelCtrl::vfunc_33` (`0x396a80`)
holds the controller's message handling and resolves string-keyed ids through
`beMessenger_ResolveEnumValue` (`0x38d4a0`). Its 33-entry `MsgAction` table is at `0x4c58f0`, built by
`beModelCtrl_GetMessageEnum`:

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

`beAction2_OnMessage` (`0x377990`) uses a 7-entry table at `0x4c81f0`, built by `beAction2_GetMessageEnum`:
0 `ISCOMEND`, 1 `ISRUN`, 2 `GETNAMELIST`, 3 `GETAPPEARANCELIST`, 4 `GETBONEMATRIX`, 5 `ONFREEZE`,
6 `OFFREEZE`. `ONFREEZE`/`OFFREEZE` set every timer's scale and the node's `_timeScale` to 0 or 1
without a jump in node time, and set `_isFreeze`. Any other name is an action:

- `NDSP` stops the ram: it releases and empties the node's override attribute list, clears the ram's
  bit in the info switch's `_childMask`, drops the work record and every timer, clears `_isRun`, removes
  every state from the ram's combiner and frees each actor's `_boneMatrixCacheArray` and
  `_blendMatrixCacheArray` (found by name through the actor's meta object).
- any other name starts the `beAction2Data` of that name. The work record is created on first use by
  `beAction2InfoWork_CreateInstance`. A ram that was not running clears its motion, fade and wait states, asks for
  no transition (`_isNoHokan`), sets the combiner's `_animationStateTime` to 100,000,000 ns, gives the
  combiner to each actor that has no bone matrix cache (`igActor_SetAnimationSystem`) and adds the
  database's first animation. A changed data restarts the component walk at 0 and sends
  `ACTION_BROADCAST` with the info's name, the ram number and the action name.

A controller
message's argument bag is `S = beModelCtrl+0x14`, `W = S+0x10`, with typed parallel lists at `W+0x10`
(bytes), `+0x14` and `+0x18` (int), `+0x1c` (long), `+0x20` (vec3, stride 0xc), `+0x24` (mat4, stride 0x40),
`+0x28` (object refs) and `+0x2c` (strings). `beMessengerArgData_Clear` (`0x38ca40`) clears them; the
accessors are `beMessenger_AppendBool`, `AppendInt`, `GetInt`, `GetFloat`, `GetVec3`, `AppendMatrix`,
`GetMatrix`, `AppendObject`, `GetObject`, `AppendString` and `GetString` (`0x38f150..0x38f8f0`).

## Compiler profile

The unit builds under `-O4,p`. The peephole sub-flag `p` matters: under `-O3` MWCC materialises an
integral `1e9f` literal as an integer + `cvt.s.w`; with any level that carries `,p` it loads the IEEE-754
bits `0x4e6e6b28` directly (`lui 0x4e6e; ori 0x6b28; mtc1`), which is what retail does. The sub-flag has
no source-level equivalent (`#pragma peephole`, `#pragma opt_peephole`, `#pragma optimization_level` are
all ignored).

`beAction2JOINTSET_Start` gets retail's integer register allocation only when the bias goes through a
`long long` temporary for the start time:
`long long st = work->_jointStartTimeL; node->_timeBias = st - (__fixsfdi(conv * node->_timeScale) << 18);`.
`beAction2JOINTSET_Update` is a `switch` on the joint state with an explicit `case 0: break;` (the shape
`beAction2FLASHSET_Update` has): it compiles to retail's `2`, `1`, `0` compare chain. Without the
`case 0` the guard is 8 bytes short; with `case 0: return;` it is 8 bytes long. The loop is a plain
`while (now > end)` that re-reads `_jointSt0`; the compiler hoists the read out of the loop.
`beAction2FADESET_Update` reads the fade limit through a `const beAction2InfoWork *` getter
(`fadeLimit`). Any conversion on the limit operand (the getter's const conversion of `work`, or a
cast) makes the compiler evaluate it before the alpha, which puts the alpha in `f0` and the limit in
`f1` as retail has them. A plain member read, a non-const getter, `*&` or `(&…)[0]` leaves the two
registers swapped; writing the limit on the left (`limit <= alpha`) gets the registers right but
compiles to `c.le.s` instead of retail's `c.lt.s`.

## What didn't work

Under the earlier per-function profiles (`-O3,p`, before the unit was compiled whole):

- `beAction2JOINTSET_Start` stayed at 316/324 bytes: two scheduler `nop`s never appeared and the float
  register allocation differed under every tested spelling of the conversion and every `-O` level from
  `-O2` to `-O4`.
- `beAction2WAITCHECK_Update` stayed at 380/372 B and `beAction2FLASHSET_Update` at 364/376 B.
- decomp-permuter, pointed at `beAction2FLASHSET_Update`, ran ~68k candidates and never scored below
  585 (a match is 0).

## Open questions

- Slot 32 (`beAction2_Prepare`) is called by `beBaseInfoManager`'s start (slot 23) and by its info
  clear (slot 26); the subclasses that fill it acquire a pad manager or release cached databases, so its
  role is only partly established.
- `igAnimationCombiner_Update`, `igAnimationCombiner_ResetToPose` and `igAnimationCombiner_AddAnimationBlend` are named from
  their use here and their bodies; the Alchemy method names are not recovered.
- Unproven beyond `j_startback` (`AREA.AFS` entry 620): a model has two parallel registries.
  `beModelCtrlInfo` holds the sequences (`beModelCtrlInfoDataSeq`, `SQ_*` as `beModelCtrlData`) and
  `beAction2Info` holds the actions (`beAction2Data`). `beModelCtrlACTION`, `JUMP` and `WCHECK` records carry
  only a name: an ACTION step appears to link to the `beAction2Data` of the same name, and a JUMP to a
  sequence by name. `scripts/modelctrl_dump.py` prints the chains. Check this against another pack and
  the runtime lookup.
