# `beAction2` timing and completion

The retail code that decides **when a model-controller ACTION
finishes**: the WAIT/WAITCHECK component, the named timer it arms, the JOINTSET
completion path, the node clock they share, the float-to-integer conversion under all
of them, the component walker and per-frame driver, and the `ISCOMEND` predicate the
sequence layer polls.
Every body in the table below has C source in `src/`. All classify as `match` in
`data/check-categories.tsv` except `0x00377990` (`vfunc_33`), which is `foreign-profile`:
its code bytes reproduce only under a provisional compiler override.

## Recovered bodies

| Retail | Bytes | Label | Contract |
|---|---:|---|---|
| `0x00230110` | 60 | `a2_f32_to_s64` | float → int64; sign-magnitude wrapper around the soft-double conversion `0x0022ffe8` |
| `0x00398e80` | 112 | `a2_node_time(node, clock)` | node clock: `(int64)(scale · ticks) << 18` plus bias |
| `0x003a7a20` | 736 | `a2_timer_start(act, name, duration)` | arm or re-arm the named timer on the action's property list |
| `0x003a7d00` | 128 | `a2_ref_release(ref, flags)` | release `*ref`; delete `ref` when `(int16)flags > 0`; returns `ref` |
| `0x003a7d80` | 272 | `a2_timer_exists(act, name)` | property-list lookup as a boolean |
| `0x003a7e90` | 312 | `a2_timer_complete(act, name)` | **`duration < elapsed`**, strict, signed 64-bit; a missing timer reads complete |
| `0x003a7fd0` | 364 | `a2_timer_elapsed(act, name)` | `(int64)(timer.scale · ticks) << 18` plus the timer's stored base |
| `0x00376340` | 372 | `a2_waitcheck_update(mgr, act)` | `beAction2WAITCHECK_Update` |
| `0x003764c0` | 440 | `a2_waitcheck_start(mgr, act, comp)` | `beAction2WAITCHECK_Start`; returns 0 (wait) or 1 (continue) |
| `0x00376de0` | 332 | `a2_jointset_update(mgr, act)` | `beAction2JOINTSET_Update` |
| `0x00376f40` | 324 | `a2_jointset_start(mgr, act, comp)` | `beAction2JOINTSET_Start`; returns 1 |
| `0x00377700` | 456 | `a2_start_components(mgr, act)` | `beAction2_StartComponents` |
| `0x003778d0` | 192 | `a2_update(mgr, act)` | `Gap::Bec::beAction2::vfunc_31`, the per-frame driver |
| `0x00377990` | — | `a2_msg_iscomend(mgr, act, msg)` | the `ISCOMEND` case of `vfunc_33` only; any other resolved case returns −1 |

Signatures come from the call sites, not from guesses. Every handler's first argument
is the `Gap::Bec::beAction2` manager (`mgr`) and its second the playing-action object
(`act`: `+8` bit index, `+0xc` `beAction2Data`, `+0x10` back-pointer to the manager,
`+0x14` active byte, `+0x28` property list, `+0x2c` time node, `+0x38`
`beAction2InfoWork`). `*_Start` handlers take the component as a third argument. The
driver calls `*_Update` with exactly `(mgr, act)`. `mgr+0xc` is the engine system whose
int64 clock is at `+0x50`; `mgr+0x14` is the messenger. The `a2_*` names are descriptive
labels, not committed symbols: no retail name for the timer group or the
conversion has evidence beyond the property names `WAIT` (`0x50dfd8`) and `FADE`
(`0x50dfe0`), so they remain hypotheses.

## The time model

The engine clock `sys+0x50` is an int64 count of **nanoseconds**. Every consumer reads
it through the same sequence, which fixes the resolution at 2^18 ns (262,144 ns,
≈ 0.26 ms), not frames:

```
ticks = low 32 bits of (clock >> 18)            # arithmetic shift, then truncation
f     = (float)(unsigned)ticks                  # cvt.s.w; for ticks >= 2^31 halve with a
                                                # sticky low bit, convert, add f to itself
time  = ((int64)(f * scale) << 18) + bias       # scale: node +0x78 / timer +0x10
```

`(int64)` is `0x00230110`. It converts the magnitude and negates for negative inputs; a
magnitude of 2^64 or more saturates to 2^64 − 1 (so `-x` becomes 1); magnitudes between
2^63 and 2^64 wrap as unsigned; denormals and negative zero convert to 0.

`FUN_00398ef0` writes a `beModelCtrlNode2`'s cached time at node `+112` (`_time`) separately,
from the effective time `0x00398e80` calculates. A paused snapshot can stop mid-update
(`0x003f6490` updates child windows recursively within one call), so a partial snapshot does
not show a cache or delay defect.

### Floating point is not host floating point

The EE rounds toward zero, flushes denormals, has no Inf/NaN (exponent 255 is an
ordinary number, overflow saturates to `sign|0x7fffffff`), and division by zero
saturates. The consequence is visible in the data: JOINTSET and WAITCHECK convert frame
numbers with `(int64)(1e9f · frames / 60.0f)`, and for 30 frames

```
host float:  1e9f · 30 = 0x50df8476 -> 500,000,000 ns
EE:          1e9f · 30 = 0x50df8475 ->                 / 60 -> 499,999,968 ns
```

The duration compared against elapsed time is **499,999,968 ns**, 32 ns short of half a
second.

Beyond 2^24 ticks (2^42 ns ≈ 73 minutes of continuous clock) the float cannot hold the
tick count exactly, so elapsed times coarsen.

## Named timer

The action's property list (`act+0x28`) is created lazily, with a reference-counted
assign whose count lives in the low 23 bits (release triggers when
`(count & 0x7fffff) == 0`; a count with high bits set therefore releases early).
`a2_timer_start` looks the name up, creates and registers the property when
absent, and writes, in order: base `-(f(start) << 18)` at `+0x18`, the start clock at
`+0x28`, `1.0f` at `+0x38`, the duration at `+0x20`. `a2_timer_complete` looks the timer
up, reads its duration, then calls the elapsed query (a second lookup) and compares
`duration < elapsed` as signed 64-bit integers. Elapsed time is
`f(now)` minus `f(start)`, each quantized to 2^18 ns when `scale` is 1.0, so a timer's
elapsed value moves in 262,144 ns steps.

Retail also arms a `FADE` timer with duration 0 from `FADESET_Start`; that call uses the
same function.

## WAITCHECK

`work+0x44` holds the wait state. `*_Start` dispatches on the first character of the
component's type string (a null string reads as empty):

| Type | State | Start effect | Returns |
|---|---:|---|---:|
| `J…` (`Joint`) | 3 | state only | 0 |
| `M…` (`Motion`) | 2 | state only | 0 |
| `F…` (`Frame`) | 1 | arm timer `WAIT` for `(int64)(1e9f · secs / 60.0f)`, then set state | 0 |
| `R…`, `name[3]=='S'` | — | store `secs` in the f32 global `0x58a348` | 1 |
| `R…` otherwise | 1 | `secs' = global + (float)(r) / 100`, where `r` is a virtual query on `mgr+0x10→+0x30` taken modulo `trunc(100·secs − 100·global)` (unsigned; a zero divisor leaves the dividend), then as `Frame` | 0 |
| anything else | — | nothing | 0 |

`*_Update` acts only on a pending state; each completion **clears the state first, then
resumes `a2_start_components`** (the store happens before the call):

- **Joint** completes when the low **byte** of `work+0x30` (`_jointIsEnd`) is nonzero.
- **Frame** completes when `a2_timer_complete(act, "WAIT")`.
- **Motion** consults the motion object's clock (`0x001dd4b0`, `0x001af510` are leaves)
  and completes when its updated position is not unsigned-below the end time; a zero
  end time completes at once; the guard `work+8 != 1` of the controlling element
  suppresses the check entirely.

The `R` path's meaning is not established (see [Unverified](#unverified)).

## JOINTSET

`Start` writes the loop state (`1` if the loop-mode string starts with `L`, else `2`),
the converted endpoints (`work+0x20/+0x28`), clears `work+0x30`, and rebases the node
(`bias = start − f(clock)·2^18`) so the node time equals the start of the range.
`Update` computes the node time and, **strictly while `end < now`**, applies the state:
one-shot (2) clamps to `end`, loop (1) subtracts the span. If anything changed it
rebases the bias to the new time and sets `work+0x30`. At exactly `now == end` nothing
happens, which is why a one-shot range completes one clock quantum later than a
non-strict test would. A loop whose start is not below its end never leaves the loop in
retail (an infinite spin).

## Walker, driver, ISCOMEND

`a2_start_components` resumes at `work._comIndex`, starting each component by its class
(MOTIONSET, JOINTSET, FADESET, WAITCHECK, FLASHSET are tried in that order, one virtual
`GetMetaObject` call per test) and continuing while the handler's low return byte is
nonzero. A component of an unknown class never advances in retail.

`a2_update` runs only while `act+0x14` is set and `work+0x4c` (`_isFreeze`) is clear,
and calls the `*_Update` handlers in the order MOTIONSET, **JOINTSET, FADESET,
WAITCHECK**, FLASHSET, each gated on its own state slot. JOINTSET therefore updates
before WAITCHECK within one frame: a one-shot that ends this frame completes its
`WAITCHECK Joint` in the same frame.

`ISCOMEND` (message case 0 of `vfunc_33`) answers true when **`work+0x44 == 0` and
`_comIndex == component count`**.

## The logo programs

| Action | Components | Completes when |
|---|---|---|
| OPEN | `FADESET IN 10`; `JOINTSET 0–30 OS`; `WAITCHECK Joint` | node time `> 499,999,968 ns` |
| CLOSE | `FADESET OUT 30`; `WAITCHECK Frame 30` | timer elapsed `> 499,999,968 ns` |

For scale 1.0, while both absolute tick counts remain exactly representable
(below 2^24, with no low-word wrap), both reduce to
**`ticks(now) − ticks(start) ≥ 1908`** where
`ticks = clock >> 18` (1907 ticks = 499,908,608 ns is not enough, 1908 = 500,170,752 ns
is). At the 60 fps step of 16,666,667 ns that is the 30th frame after the start when
the start clock's offset inside its tick is at least 170,742 ns, and the 31st frame
otherwise — about 35 % / 65 % over uniformly distributed phase. OPEN and CLOSE complete
on the same frame as their final `JOINTSET`/`WAITCHECK` update, and `ISCOMEND` is true
on that frame. The exact frame in the real game depends on the clock's phase and
cadence, which this page does not establish (below).

Outside that range, convert **each absolute clock separately**, then subtract;
rounding the elapsed tick difference loses retail behavior. At a 16,666,667 ns
step, start clocks `((2^25)+1)<<18`, `(2^31)<<18`, and `((2^31)+255)<<18`
complete OPEN and CLOSE on frames 30, 33, and 29 respectively.
The first case completes after only 1,907 raw ticks.
These are conditional clock-model results, not measured console timings.

## Unverified

- **Clock scheduling and resets.** The source chain and nanosecond quantization are
  now supported by static code and two independently checked logo savestates; see
  [system clock](system-clock.md). The handoff reports variable steps near 60 Hz.
  Normal scheduler order and timer reset/pause methods are now verified.
  Game-pause/stage routing, allocation defaults, message-driven starts and the exact
  displayed completion frame remain open.
- **The full EE FPU model** (truncation, denormal flush, saturation, `div` by zero)
  remains only partly measured. Both logo states contain WAIT duration 499,999,968,
  confirming that result, not every arithmetic operation or exceptional case.
- **Leaf behavior.** Property-list lookup/insert, allocation, string interning, the
  FADESET/MOTIONSET/FLASHSET handlers, the motion clock `0x001dd4b0`/`0x001af510`, the
  messenger, and `vfunc_33`'s other message cases are not established here. `FADESET`
  completion does not gate an action.
- **The node's `_timeScale`** is read, not set, here; actions are assumed to run at 1.0
  unless another writer says otherwise.
- **The `R` WAITCHECK mode's** purpose (a beat-aligned wait is the arithmetic's shape)
  is a hypothesis.
- FADESET presentation, action replacement/sequence dispatch and other models remain
  outside this recovery.
  The duration was checked in stock-emulator savestates; complete timing equivalence was not.

## Logo components

The logo's Action2 components are in AREA 620, with their frame values stored as
f32 bit patterns.
