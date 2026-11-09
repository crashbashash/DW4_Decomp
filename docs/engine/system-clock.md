# System clock `sys+0x50` — source, update, and the logo CLOSE WAIT timer

**Lifecycle and normal Action2 update order are recovered.**
The clock owner is `igInsightCore`; `+0x50` is its reflected `_worldTime`.
See [the executable contracts](#executable-lifecycle-and-scheduling-contracts)
below. Hardware cadence, message-triggered starts, allocation-time defaults and
game-pause routing remain separate questions.

The int64 clock that Action2 reads at `(mgr+0xc)+0x50`: where it comes from, how it advances,
and a measured read of the logo CLOSE `WAIT` timer. Reproduce with
`scripts/system_clock_probe.py`.

Evidence classes are marked **[static]** (retail instructions), **[observed]** (memory read from
a running game or a savestate) and **[hypothesis]**.

## Complete beSystem update recovery

`beSystem::vfunc_27` (`0x003a0020`, **1,300 code bytes**) has
byte-identical typed C in `src/game/beSystemUpdate.cpp`.
The function samples `igInsightCore._worldTime`, stores the signed wrapped delta
in `_frameTimeL`, converts it to `_frameTimeF` with the original frame divisor,
and stores the new `_svWorldTimeL`. Its remaining body owns next-stage directory
preparation/publication, retained allocator and directory references, interned
stage strings, directory-info callbacks and the active first-frame flag reset.

The matching profile is the content-pinned alternate compiler with `-O3,p`.
Four distinct allocator/base variable pairs preserve the original reference
lifetimes and register assignment. The list preheader uses `0 < count` to
retain the original `slt`/branch sequence. Object reference counts are word-sized
and the active/first-frame flags are byte-sized; the clock fields are 64-bit.
The entire 1,300-byte body, including 75 relocations, matches retail. The full
matching build has zero mismatches and the relink is byte-identical.
This source recovery does not close the separate runtime cadence or pause routing
questions below.

## Ownership and the writer chain

```
EE Timer 1 count (0x10000800)  ─ FUN_0020d290 ─▶ 100 ns ticks (u64) ×100
   ─ igPsx2LongTimer::vfunc_37 (0x0032dab0) ─▶ raw time
   ─ igPsx2LongTimer::vfunc_26 (0x00330af0) ─▶ timer time  (paused flag at +0x20; base at +8; frozen value at +0x10)
   ─ FUN_00237730 (clock update) ─▶ sys+0x38 sample, +0x40 delta, +0x50 clock
   ─ read by Action2 as (beAction2+0xc → sys)+0x50
```

| Step | Address | Evidence |
|---|---|---|
| Hardware read | `0x0020d290` (`FUN_0020d290`) | **[static]** `lw 0x1000_0800` (T1_COUNT); `cvt` to float; `× f32 @ gp−32696`; truncate to u32; `+ u64 @ 0x0056c190`; then `×25×4` = **×100** into the out-parameter |
| Raw source | `0x0032dab0` `igPsx2LongTimer::vfunc_37` | **[static]** calls `0x0020d290` and returns the u64 |
| Timer time | `0x00330af0` `igPsx2LongTimer::vfunc_26` | **[static]** if byte `+0x20` ≠ 0 return `+0x10`, else `+0x10 + vfunc_37() − +8` |
| Clock update | `0x00237730` `FUN_00237730` | **[static]** see below; the writer found for `sys+0x50` |
| Caller | `0x00463bc0` `FUN_00463bc0` | **[static]** `jal 0x237730` with `a0 = *(this+0)` |

`gp` is `0x0055c870` (entry code `0x001001bc`), so the float is at `0x005548b8` and the
accumulator at `0x0056c190`.

`FUN_00237730` (`this` is the clock object at `0x006e98d8`):

```
now      = this->timer(+0x30)->vfunc_26()          # virtual slot +104
this+0x40 = now - this+0x38                         # delta
this+0x38 = now                                     # last sample
this+0x50 += (delta * (int32)this+0x48) >> 18       # scale word at +0x48
this->(+0x20)->vfunc(+92)(); this->(+0x0c)->vfunc(+92)()   # then two notifications
```

## Units and cadence **[observed]**

Live PCSX2 (stock, PINE, 6 s sample):

| Quantity | Value |
|---|---|
| Object | clock object at `0x006e98d8`, same address in all 15 repository savestates and both capture runs |
| `+0x48` scale word | `0x00040000` = 2^18, so `(delta · 2^18) >> 18` = delta: **the clock is nanoseconds** |
| Clock vs sample | `sys+0x50 == sys+0x38` on every read (361 of 361); consistent with accumulated deltas; boot initialization is not proved by these samples |
| Resolution | 100 ns (every value ≡ 0 mod 100) |
| Update rate | Reported 60.03 Hz (361 distinct values in approximately 6 s); consistent with frame cadence, but no frame counter was recorded |
| Step | min 16,125,200 / max 17,119,500 / mean 16,683,466 / stdev 171,657 ns |
| Stored delta | `+0x40` equals the observed step on 360 of 360 updates |

The reported mean step is close to 1/59.94 s (16,683,333 ns). The step is **not** a constant 16,666,667 ns: it is
the interval between two samples of Timer 1, and varies by roughly ±0.5 ms in the reported sample. Its cause is not isolated.
No raw sample sequence was retained with the aggregate live statistics,
so they have not been independently reproduced.

Timer-1 scale: the float at `0x005548b8` reads `0x3f8ae38e` ≈ 1.0850694 ≈ 10,000,000 / 9,216,000.
That is 100 ns units per timer tick for a 9.216 MHz Timer 1 (BUSCLK/16). The 64-bit accumulator
at `0x0056c190` advanced ≈ 10.1 M per second, matching 10 M × 100 ns. **[observed]** values;
the "BUSCLK/16 prescaler" reading of the constant is a **[hypothesis]** (the Timer 1 mode
register is not read by PINE).

## The logo CLOSE WAIT timer **[observed]**

Captured live (stock disc, MD5 `3185f04230b1dabd853db750e4b51108`) by saving a state every
~0.4 s through the title's "Press START button" and START press. Two states contain the timer;
the next does not.

States (not committed):
`logo-close-start+50ms.p2s`, `logo-close-start+434ms.p2s`.

```
timer          0x013b7fd8   class beBaseInfoRamTimer (vptr 0x00534830)
  +0x08  name ptr 0x00694090  "WAIT"
  +0x10  scale        0x3f800000  (1.0f)
  +0x18  base         -211,354,648,576  = -(806,254 << 18)
  +0x20  duration     0x1dcd64e0 = 499,999,968          <-- expected value, measured
  +0x28  start clock  211,354,781,300 ns  (tick 806,254, 132,724 ns into its tick)
  +0x38  1.0f
```

Chain from memory (`system_clock_probe.py verify STATE.p2s` reproduces it):

```
timer 0x013b7fd8  (array of 2 timers at 0x013c85f0: FADE 0x013b8368 [duration 0], WAIT 0x013b7fd8)
 └ list header 0x013c85e0 {count 2, cap 4, data 0x013c85f0}  ← wrapper 0x013c85d8
    └ referenced from 0x0137ef78 = act+0x28           act = 0x0137ef50
       act+0x10 = manager 0x00703e28                  (vptr 0x00539f90)
       manager+0xc = 0x006e98d8                       = the clock object
       act+0xc → beAction2InfoRam, +8 → "j_startlogo"
       act+0x38 (work 0x01371da0) +0x44 = 1           = WAITCHECK Frame pending
```

The FADE timer (duration 0) beside it and the pending Frame state identify the CLOSE program
(`FADESET OUT 30; WAITCHECK Frame 30`); OPEN uses a Joint wait and arms no WAIT timer. The
action's own name string (`CLOSE`) was seen in the graph's sequence list but not linked by pointer
to `act`, so the OPEN/CLOSE distinction rests on the timer pair and wait state **[inference]**.

Both timing readings are consistent with the model:
state clocks 211,404,741,600 (191 ticks elapsed) and 211,788,455,800 (1,654 ticks) are below
the model's completion clock 211,854,819,328 (= (806,254 + 1,908) << 18); the next state, at
212,172,185,800, no longer has the timer. This brackets completion; it does not pin the frame.

Other graphs share the duration: the dev-world state holds four completed (wait state 0) WAIT
timers on `i_stpnl01/02/04` and `p_susanoo`, all 499,999,968 with the same start tick — evidence
that the value occurs outside the logo too; this does not prove every conversion path.

**This confirms the EE-float result 499,999,968 for the 30-frame WAIT duration** (retail wrote it;
host rounding would give 500,000,000). It does not by itself validate the full FPU model.

## What is established, what is not

Established **[observed]**: clock object address, layout, units (ns), 100 ns quantization, the live WAIT duration and its chain to the clock object.

Established **[static]**: the writer chain above, including the pause flag in
`igPsx2LongTimer::vfunc_26`.

Not established:
- **Physical-frame phase and action starts.** The normal scheduler proves that
  Action2 updates follow the `_worldTime` write. The timing of every
  message-triggered action start/replacement and the exact displayed frame remain open.
- **Game routing of reset/rebase.** Timer methods and system start/stop are recovered
  below. Which stage transitions or pause commands invoke them remains unverified.
- **Skipped/doubled updates.** None seen at 100 % speed; the stored delta would absorb a skipped
  frame (the step simply grows).
- **Other `+0x50` read-modify-write units** (`FUN_002f2340`, `Gap__Core__igMallocMemoryPool__vfunc_64`,
  `igArenaMemoryPool_MemoryOperation`) were not examined. Over 361 of 361 live updates the clock
  equalled the last sample exactly, consistent with this writer. Equality does not rule out additional writers. The offset-only
  scan does not establish that the other functions operate on the same object.
- **FADE timer start.** In the first state its start equals that state's clock, unlike WAIT.
  Not analysed.

## Clock steps and consumers

The observed source has variable steps; there is no measured fixed step that establishes 1:1 behavior.
The recovered sample/scheduler path advances `_worldTime` before normal Action2 updates. Starting at
zero and mapping game pause to the timer flag still require initialization and caller evidence.
Resume's rebase arithmetic is verified; the pause-button routing is not.

The live sample above kept only aggregate statistics, **not** a replay
sequence. Consumers perform their own
`>>18` conversion. At these small absolute tick values the 1,908-tick threshold applies;
large-clock float rounding follows the qualifications in [Action2 timing](action2-timing.md).

## Reproduction

```sh
python3 scripts/system_clock_probe.py verify STATE.p2s        # clock object + timer chain
python3 scripts/system_clock_probe.py writers                 # the +0x50 read-modify-write units
```

## Independent offline review

Both named states reproduce duration 499,999,968, graph `j_startlogo`, pending Frame
wait and the manager-to-clock chain. The clock source pointer is `0x006eaac0`;
its vtable `0x0052da90` contains `0x00330af0` at +104 and `0x0032dab0` at +148.
The timer verifier checks the base/start equality, WAIT name, timer/action
vtable identities, list bounds and pointer bounds before accepting a chain.
This validates these captures; it does not establish a general address invariant.

## Executable lifecycle and scheduling contracts

These contracts cover the complete thirteen-body timer group
`0x00330a50..0x00330e58`, the adjacent system start/stop pair
`0x002371f0`/`0x00237280`, the adjacent sample/render pair
`0x00237730`/`0x002377c0`, and the scheduler/manager/gate bodies
`0x00237ec0`/`0x00378bc0`/`0x003a0540` needed to establish update order.

### Timer lifecycle

Reflection identifies `_startTime` at `+8`, `_additionalTime` at `+0x10`,
`_resetTime` at `+0x18`, and `_isStopped` at `+0x20`. Times are 64-bit words.
All addition/subtraction wraps; no monotonic clamp is present.

| Entry | Operation | State and raw-time reads |
|---|---|---|
| `0x00330af0` | Read | Stopped: return additional time without sampling. Running: additional + raw − start. |
| `0x00330be0` | Resume | Only if stopped: clear flag, sample raw, store start. Preserve additional time. |
| `0x00330c20` | Stop/pause | Only if running: sample raw, add raw − start to additional, then set flag. |
| `0x00330c80` | Reset | Copy preset to additional. If running, resample start; preserve flag. |
| `0x00330cd0` | Stop and reset | Set flag, copy preset to additional; no sample. |
| `0x00330cf0` | Restart | Clear flag, copy preset to additional, resample start even if already running. |
| `0x00330d90` | Set preset | Store argument at +0x18; does not immediately change elapsed time. |
| `0x00330da0` / `0x00330e50` | Get preset / stopped | Read +0x18 / +0x20. |

The seconds wrappers at `0x00330a50`, `0x00330b40`, `0x00330db0` and seconds
preset setter `0x00330d30` use software-double calls; that arithmetic is not
analysed here.

Pausing at time 109, waiting arbitrarily, resuming and advancing raw time by 20
returns 129. Repeated pause/resume calls do not resample or discard elapsed time.
These are method contracts, not evidence that the game's pause UI uses them.

### System start, stop and sampling

`0x002371f0` clears `_frameTime` (+0x40) and `_currentTime` (+0x38), calls the
registered managers' slot +0x64 in list order, then resumes the timer.
It **does not clear `_worldTime`**. `0x00237280` pauses the timer first, then
calls manager slot +0x68. Both reread list length while walking it.

`0x00237730` samples the timer, stores delta, stores the sample, scales delta,
adds it to world time, then invokes the dispatcher and serial scheduler, in that
order. The scale is the signed 32-bit `_currentToWorldTimeFactor` (+0x48).
The multiplication wraps to 64 bits **before** the arithmetic right shift by 18.
The multiplication goes through the helper `0x0022e440`. Unity is `0x40000`, initialized at
`0x00237490` **[static]**. Negative deltas are not clamped.

Repeated system start has a non-obvious consequence: the timer can retain its
additional time while the system forgets its previous sample. The next system
update then adds that retained time again. A start/update/stop/
start/update sequence produces world times 100 then 200 without advancing the resumed
timer. Do not treat this start method as an ordinary per-frame or per-screen reset.
Its use across normal stage loads is still open.

### Normal Action2 order: recovered and observed

The recovered call chain is:

```text
0x00463bc0 -> 0x00237730
  sample timer; write frameTime/currentTime/worldTime
  core._dispatcher (+0x20), virtual +0x5c
  core._scheduler (+0x0c), virtual +0x5c -> 0x00237ec0
    snapshot manager references; invoke each manager's virtual +0x74
    Action2 manager -> 0x00378bc0
      check beSystem and manager gates; walk groups/actions
      virtual +0x84 -> 0x003778d0 (Action2 per-action update)
```

The serial scheduler `0x00237ec0` (336 contiguous bytes) works from a snapshot. It
reads the manager list through the object at +8, captures that list's count and
resizes its own snapshot list at +0x0c to the count through `0x301ee0`. For each
index it rereads the manager list, retains that manager, releases the snapshot's
old entry with the low-23-bit rule (destroying through `0x2ff820` at zero) and
stores the manager when the index is within the snapshot's count. A second pass
calls virtual +0x74 on each snapshot entry in index order, rereading the snapshot
list each time. Finally it resizes the snapshot to zero.

The manager gates are the low bit of `beSystem._isActive` (+0x2c), zero
`_isFirstTime` (+0x2d), nonzero manager +0x1c, and zero `_isFrameSkip` (+0x2e).
The system clock advances even when a manager is gated off.

**[Observed, offline]** Both logo states contain `igInsightCore` at `0x006e98d8`,
`igSerialScheduler` at `0x006e99a0`, and its 35-entry scheduled manager list.
Action2 manager `0x00703e28` is index 17; group 43, element 0 contains
`j_startlogo` action `0x0137ef50`. The gates are open and its update slot resolves
to `0x003778d0`. Reproduce this bounded pointer-chain check with:

```sh
python3 scripts/clock_dispatch_probe.py STATE.p2s
```

Multiple managers/groups/actions all see the newly written clock in the original
list order. External dispatcher receivers and other managers have not been examined,
so they are not shown to leave the pump and shared state alone.
[Action2 timing](action2-timing.md) covers the update's timing consumers separately.
This does not establish all messenger
reentrancy, start/replacement timing or hardware frame phase.

### Render passes are separate from clock updates

`0x002377c0` checks the visual-context gate, increments `_frames`, walks renderer
slot +0x64, then conditionally slot +0x68. Three timer reads bracket traversal
and output; their differences go to +0x58/+0x60. It never advances `_worldTime`.
`0x00463bb0` forwards to this render pass.

The loops at `0x0025aab0` and `0x0025ab10` repeat render passes without another
`0x00463bc0` sample/update inside them. The other loop variant orders a sample/
update at `0x0025a828` before its render call at `0x0025a838`. Therefore source
reads, renderer frames and Action2 scheduler invocations are distinct counts.
These outer bodies are not single-frame functions:
they contain repetition and lifecycle setup/teardown.

Raw source time, timer lifecycle state, the last sample/delta and accumulated world time are
separate state. Action2 reads the accumulated value after the sample/update, and it is retained
across render-only passes.

Open: allocation/default initialization of the core and timer; all callers
of reset/pause/restart, especially game pause and stage loads; exact Timer 1
samples/frame phase; message-triggered action starts; and the external callbacks
and software-double arithmetic omitted above. The instruction-derived
pause/reset and scheduler contracts are established and are not on that list.
