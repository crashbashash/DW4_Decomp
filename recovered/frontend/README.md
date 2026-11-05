# Title-menu behavioral reference

[`title-menu.c`](title-menu.c) reconstructs the initialized per-frame logic of
`beNDMWTitle2::vfunc_31` at `0x003f2ef0`. It covers all six implemented top-level
states: idle, Press START, the two-row menu, Options, Game Start fade, and the
load-controller handoff. It includes the attract-loop and regional-language
branches. Names and offsets come from reflection and the retail accesses;
`T_*` enumerators identify the original strings by their ELF addresses.

The complete matching counterpart is
[`src/game/beNDMWTitle2.cpp`](../../src/game/beNDMWTitle2.cpp), including the
allocation prologue, scoped references, all three jump tables and exception
metadata. The nine-function title runtime block is byte-matched; see the
[matching recovery record](../../docs/engine/title-menu-controller.md#complete-matching-unit).
The reference in this directory retains its initialized-record engine boundary.

This is **a behavioral reference, not a matching decompilation or a complete
frontend implementation**. `title-menu.h` deliberately exposes host records,
not binary-compatible PS2 structs. Engine callbacks must preserve their order
and implement the game's model queues, text, and message semantics. The original
allocation/reference-counting prologue is outside this entry: callers supply its
initialized `CTRL` and `OPTION` records and a snapshot of controller input.
`model_tick` must not mutate that input snapshot.

The original option initializer (`beNDMWTitle2Option`) is separately byte-matched.
Do not substitute a zeroed option record for it: camera/light defaults are 0/1,
and the initialized game-RAM path restores the saved configuration.

## Verification

```sh
python3 scripts/verify_title_menu.py --elf orig/SLUS-20836/SLUS_208.36
```

The test compiles this source and `title-menu-test.c` with the host C compiler.
It executes the original tick from the user's retail ELF through a restricted
integer R5900 interpreter, preserving 64-bit scalar registers, sign-extended
word operations, and delay slots. It rejects other ELF versions. It stubs the
documented engine calls and compares **every controller/option field and the
ordered calls with their meaningful arguments** against the C result.

The default matrix is 55,264 cases: 28,800 state/input/completion combinations,
16,464 targeted regional-option combinations, and 10,000 deterministic mixed
cases. It exercises 1,713 retail instruction addresses. No retail bytes or
private memory dumps are embedded in the tests. The engine returns are simulated;
this does not verify model animation timing, text rendering, persistence,
allocation, the entire engine's input sampling, or visual equivalence.

## Scope still open

- Implementing/verifying the model queue, text, and messenger callbacks in a port.
- The downstream `beNDMWLoadCtrl2` and `beNDMWLoadIntf2` modules, including slot
  selection, character creation, name entry, difficulty, memory-card paths, and
  their subordinate helpers. The Game Start path's first module
  (`beNDMWLoadCtrl2`) has matching C/C++ for all nine runtime bodies.
  `beNDMWLoadIntf2::vfunc_31` remains a matching roadblock; current source status
  is recorded in the [title recovery](../../docs/engine/title-menu-controller.md#remaining-main-menu-family)
  and [assembly-body notes](../../docs/engine/asm-body-matches.md).
- Boot-to-menu and menu-to-game visual/timing comparison against the running game.

See [the recovery record](../../docs/engine/title-menu-controller.md) for the
state map, exact addresses, and the matching-build boundary correction.

## Load controller

[`loadctrl.c`](loadctrl.c) / [`loadctrl.h`](loadctrl.h) reconstruct the Game Start
load controller `Gap::Bec::beNDMWLoadCtrl2`:

- `0x003f1a80` **vfunc_31**, the per-frame update (2504 bytes);
- `0x003f2490` **vfunc_34**, the RUN/GAMESTART message handler (1832 bytes).

Both are covered by the same method: the source runs one flat world
(`peek`/`poke`/`call`) and every engine call is reported to the host with its
retail address and EE argument registers, so a restricted R5900 interpreter can
run the original instructions and compare.

```sh
python3 scripts/verify_loadctrl.py --elf orig/SLUS-20836/SLUS_208.36
```

The default matrix is **1,624 cases** — every `(st0, st1, st2, isTitle,
sub-controller-return)` combination of the update, every message command for a
present/absent work registry, and a randomized sweep — and compares the ordered
engine calls with their meaningful arguments and every byte written outside the
stack. The engine callees are stubbed; this does not verify the engine's own
implementations, rendering, timing, or reference lifetimes.

The update is a `beNDMWLoadCtrl2CtrlData` state machine (`_st0` at `+0x14`,
`_st1` `+0x18`, `_st2` `+0x1c`, `_st3` `+0x20`) resolved from the named work
registry by `FUN_003022c0(work, "CTRL")`, driving the `"COMMONINTF"` object's
model sub-controller (`+0x34`). The message handler builds that work from the
messenger and, for GAMESTART, reads the saved camera/light, then hands the
player to the world (`PLAYERPOINT`, `gameStart.lua`, `STAGECTL NEXTSTAGE
stagML11`). The handoff continues into `beNDMWLoadIntf2`.

## Load interface

[`loadintf2.c`](loadintf2.c) / [`loadintf2.h`](loadintf2.h) reconstruct the Game
Start slot/character/name/difficulty/card interface
`Gap::Bec::beNDMWLoadIntf2`:

- `0x003e4750` **vfunc_31**, the per-frame master update (18,616 bytes);
- `0x003e9430` **vfunc_34**, the family-build/teardown message handler (8,272
  bytes).

```sh
python3 scripts/verify_loadintf2.py --elf orig/SLUS-20836/SLUS_208.36
```

Both run the same flat-world method and are checked against the original MIPS
instructions. The default matrix is **432 message cases**, **1045 update cases**
and **626 focused direct cases**: 600 randomized single-tick rows, 4 targeted
edge rows, 40 randomized 8-tick multi-step flows on one evolving world, 6
character/game-start flows, 9 slot-selection flows (entry / movement / confirm /
cancel / backtracking / delayed completion / cursor publish / stall / complete),
and 1 deterministic regression, plus the direct cases that drive the text-order
and completion functions on the branches the flows never take. It compares the
ordered engine calls (meaningful arguments) and every non-stack byte written.
The remaining per-screen helpers and every engine callee are stubbed identically
on both sides.

### Slot-selection helpers

[`selslot.c`](selslot.c) / [`selslot.h`](selslot.h) reconstruct the
`beNDMWLoadIntf2SelSlot` per-screen helper group that the master update drives
in CTRL state 6 — the seven functions whose first argument is the SELSLOT
record:

- `0x003e0b80` `ss_clear` (40 B) — clear the run state;
- `0x003e0bb0` `ss_init` (136 B) — initialise from the manager mode;
- `0x003e2a80` `ss_pub_cursor` (140 B) — reset and publish one cursor line;
- `0x003e1760` `ss_update` (4,764 B) — pad sample, movement, confirm/cancel;
- `0x003e2b10` `ss_marks` (1,336 B) — publish/finish the marks;
- `0x003e0c40` `ss_open` (2,808 B) — open/refresh the slot base and marks;
- `0x003e3070` `ss_select` (2,776 B) — highlight the selected slot.

For these the verifier **executes the original retail instructions** on the
retail side (the interpreter descends into them) and the recovered C calls the
matching `ss_*` implementation, so the compared call stream is the helpers' own
text-order/model calls. The per-flow assertions pin the open (`0x3e3e00`),
movement (`SQ_MOVE`), confirm/select (`0x3ee190`) and cancel (`SQ_CANCEL`)
paths. See [the recovery record](../../docs/engine/load-intf2.md) for the
object model, the stub boundary and the remaining open work.

### Text-order helpers

[`textorder.c`](textorder.c) / [`textorder.h`](textorder.h) reconstruct the
three functions that turn a screen control id into the published text line —
the same trio the slot screen and the master update call:

- `0x003ebce0` `to_line` (136 B) — publish one line (name + font + style tags);
- `0x003ebe00` `to_set` (572 B) — publish the id's line list, latch the global
  text pointers `0x0058a220`/`0x0058a1e0`, fire the animation token;
- `0x003ec050` `to_pub` (196 B) — the close variant (line list only).

They are in the verifier's `REAL` set too: the original instructions run on the
retail side and the recovered C bodies run on the C side. The id table is
`0x004cda40` (stride `0xc`, low-20-bit match) and the font table is
`0x004ceb30 + fontSet*0x50 + fontIndex*4`. The runner asserts every recovered
body was entered on the retail side.

### Completion/selection helpers

[`completion.c`](completion.c) / [`completion.h`](completion.h) reconstruct the
decisions the slot screen consults:

- `0x003e4280` `cm_open_empty` (20 B) — `CommMdlCtrl._openDataList` count `<= 0`;
- `0x003e44d0` `cm_close_empty` (20 B) — the same on `_closeDataList`;
- `0x003ee190` `ds_select` (184 B) — arm the four per-player records, select one.

Completion is driven by the queue counts the accessors read (the verifier writes
them from the `cmon`/`cmcn` keys each tick), not a forced `rv` value; the
deliberate slot flows assert entry opens on tick 3, delayed-open waits for the
queue, stall never opens, and the settle fires when the queue empties.

### Common-model queue lifecycle

[`commdl.c`](commdl.c) / [`commdl.h`](commdl.h), together with the two existing
empty predicates, cover the contiguous ten-body group `0x003e3b80..0x003e46a4`.
Submissions have an executable reference for generation/play, positioned
generation and close tracking. The poller preserves duplicate requests, stops
at the newest pending entry, and handles open and close lists independently.
Run `python3 scripts/verify_commdl.py --elf orig/SLUS-20836/SLUS_208.36` for 2,676 retail/C
comparisons including ordered stores. See the [contracts and remaining engine
boundaries](../../docs/engine/common-model-controller.md). This standalone
recovery does not change the slot harness's seeded-queue boundary.

### Model-sequence waits

[`modelwait.c`](modelwait.c) / [`modelwait.h`](modelwait.h) recover the contiguous
JUMP, WCHECK start/update and no-op group (`0x00394ae0..0x00394f98`).
`python3 scripts/verify_modelwait.py --elf orig/SLUS-20836/SLUS_208.36` compares 988 calls
and all 294 instruction addresses, including ordered calls and writes.
See [the contracts and logo integration boundary](../../docs/engine/model-sequence-waits.md).

### Action2 timing and completion

[`action2time.c`](action2time.c) / [`action2time.h`](action2time.h) and
[`eefloat.c`](eefloat.c) / [`eefloat.h`](eefloat.h) recover the code that decides when
an ACTION completes: the float→int64 conversion (`0x00230110`), the node clock
(`0x00398e80`), the named timer group (`0x003a7a20..0x003a813c`), WAITCHECK and JOINTSET
Start/Update, the component walker, the per-frame driver and the `ISCOMEND` predicate.
Single-precision values are IEEE bit patterns operated on with integers (EE
round-toward-zero model), never host `float`. `Dw4Action2Api` extends the shared
peek/poke/call API with a 64-bit-argument call for two motion-clock leaves. Run
`python3 scripts/verify_action2time.py --elf orig/SLUS-20836/SLUS_208.36` for 46,132
retail/C comparisons over 1,013 covered body
instruction addresses, with five exemptions reported separately. The system clock's source and
cadence remain a boundary; see [the contracts](../../docs/engine/action2-timing.md).

### Text configuration and indexed-font wrappers ([#771](../../docs/findings/findings-0751-1000.md#f771))

The six-body text-order runtime group is fully behaviorally represented.
`to_configure` (`0x003eba10`) emits alignment/colour/text/show commands;
`to_configure_font` (`0x003ebd70`) and `to_clear_font` (`0x003ebdc0`) resolve the
font table and are called directly by the master reference. The retail comparison
passes 626 focused direct, 432 message and 1,045 update cases. All 208 reachable
instructions in these three bodies are covered, excluding two unreachable
padding nops. A messenger-rebinding regression checks that `to_line` does not
cache the messenger pointer. See [contracts and verification limits](../../docs/engine/load-intf2.md#text-order).

### System clock lifecycle and scheduling ([#772](../../docs/findings/findings-0751-1000.md#f772)–[#774](../../docs/findings/findings-0751-1000.md#f774))

[`systemclock.c`](systemclock.c) / [`systemclock.h`](systemclock.h) recover the
complete thirteen-body long-timer runtime group plus system start/stop,
sample/render and the normal scheduler path into Action2. The source is a
behavioral reference over 64-bit read/write/call callbacks. It preserves paused
elapsed time, reset/restart distinctions, signed modular scaling and callback
order. Raw source time remains supplied by the host.

`python3 scripts/verify_systemclock.py --elf orig/SLUS-20836/SLUS_208.36 --mutations`
passes 9,431 retail/C calls, covers all 585 reachable body instruction addresses,
and rejects four wrong implementations. The final Action2 update, other external
callbacks, Timer 0 and software-double leaves remain boundaries. An offline probe
checks that the two logo captures use the recovered scheduler path. See the
[clock contract and native integration guidance](../../docs/engine/system-clock.md#executable-lifecycle-and-scheduling-contracts-772774).

### Loading-card node runtime

[`loadingnode.c`](loadingnode.c) / [`loadingnode.h`](loadingnode.h) recover the
complete nine-body node/loading traversal group `0x0039a930..0x0039ae44`.
`python3 scripts/verify_loadingnode.py --elf orig/SLUS-20836/SLUS_208.36`
passes 2,631 retail/C comparisons over every reachable body instruction. See
[stage selection, clock contracts and boundaries](../../docs/engine/stage-loading.md).

### Selection sound dispatch ([#780](../../docs/findings/findings-0751-1000.md#f780))

[`sectl.c`](sectl.c) / [`sectl.h`](sectl.h) recover the complete six-body
`beSeCtl` runtime group `0x0039c900..0x0039cb6c`, including last-model lookup,
every matching action and ordered `SETSOUND` message construction.
`python3 scripts/verify_sectl.py --elf orig/SLUS-20836/SLUS_208.36` passes 392
retail/C comparisons over 150 instruction addresses. See the
[authored selection mappings and boundaries](../../docs/engine/sound-format.md#pre-lobby-selection-mapping-780).
