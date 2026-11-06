# Model-sequence JUMP and WCHECK

The contiguous four-body group `0x00394ae0..0x00394f98` is behaviorally
recovered in `recovered/frontend/modelwait.{c,h}`.
These are executable references, not newly byte-matched compilation units.

| Entry | Bytes | Reference contract after API |
|---|---:|---|
| `0x00394ae0` | 68 | `mw_jump(owner, work, command)` calls owner vtable `+0x8c` with the command name (`command+8`), using the empty string if null; returns 1 regardless of the virtual result |
| `0x00394b30` | 180 | `mw_start(owner, work, command)` interns the command name, releases the previous `work+0x4c` string and assigns the new one; returns 0 |
| `0x00394bf0` | 920 | `mw_update(owner, info, node, work)` polls the wait condition, clears the wait string before resuming dispatcher `0x00395250` |
| `0x00394f90` | 8 | `mw_noop` is the adjacent empty body, already named `igObject::vfunc_39` |

The start/update signatures differ: start receives the work as its second
argument, while update receives it as its fourth. Strings use full-word
reference counts at `string-4`, with the free owner at `string-8`; this is not
the low-23-bit object-reference convention. Lazy pool creation, including a
null allocation result, precedes interning and release in retail order.

Update compares names by string content, in this order:

- `TurnY` / `Landing`: call `0x00392be0(owner,node,work,2)`.
- `Action`: send `ACTION2 ISCOMEND` through `0x0038e5f0`, using the model name
  from `info+8` (empty string fallback) and slot from `node+8`; read result zero
  through `0x0038f220`. **Any nonzero 32-bit result completes the wait.**
- `Moving` / `Rotation`: call `0x00392be0` with mode 0 / 1.
- Unknown name, including empty: call owner vtable `+0xa4(owner,node)` without
  clearing the string or invoking the sequence dispatcher.

The movement query completes only when its **low byte is zero**. A result of
256 therefore completes both Action and movement waits, whereas 1 completes
Action and keeps movement waiting. On completion, string assignment to null
finishes before the dispatcher call; a new wait installed by that call survives.

## Verification

```
python3 scripts/verify_modelwait.py --elf orig/SLUS-20836/SLUS_208.36
```

The verifier compares **988 calls** against original retail instructions,
covering all **294 instruction addresses** across the four bodies. It compares
ordered meaningful engine calls, ordered non-stack writes, final memory, and
defined returns. Cases include null names, pool initialization/failure, old
string counts (including high bits and wraparound), every name branch, non-Boolean
query results, waiting ticks, completion, replacement, and dispatcher re-entry.
Function boundaries and instructions were cross-checked with MIPS objdump.
The test uses distinct interned-string and literal addresses to exercise content
comparison. It does not pass null to strcmp: the caller must invoke update only
with a pending wait.

Allocation, string operations, strcmp, messenger, movement query, virtual slots
and `0x00395250` remain explicit leaves. The test verifies caller behavior, not
the original implementation of those leaves. No animation clock, rendering,
audio, or whole-menu equivalence follows from these checks.

## Native logo integration

The native port imports the reference unchanged. Its logo program is generated
from AREA entry 620's `j_startlogo` model-controller records:

```
SQ_OPEN:  ACTION OPEN;  WCHECK Action; JUMP SQ_WAIT
SQ_CLOSE: ACTION CLOSE; WCHECK Action; JUMP SQ_ERAS
SQ_WAIT:  (empty)
```

A narrow native dispatcher walks that extracted program and invokes recovered
WCHECK/JUMP; the logo has no hardcoded successor/removal branch.
The port comparison executes original JUMP/WCHECK instructions on the oracle
side and compares their ordered calls/stores plus full title/queue/logo state
on **2,933 ticks**, including OPEN/CLOSE interruption and re-entry.

The dispatcher and virtual sequence-selection/removal behavior remain native
boundaries, shared by the two sides. **The port's Action2 completion is a
30-tick approximation** (the retail completion chain is recovered in
[`action2-timing.md`](action2-timing.md) and is not imported by the port), and all other title models retain bounded schedules.
The strict timer/joint comparisons, shared-clock conversion, generic dispatcher
`0x00395250`, and full ISSEQNAME/ISRUN semantics still need independent recovery
and validation. This slice does not establish retail action timing or pixels.

## Gates

`make check` reports zero mismatches and every split unit round-trips;
`make link` is BYTE-IDENTICAL and `make typed-check` matches its baseline.
Native `make check` and `make check-retail`
pass, as do address/undefined-behavior sanitizer title tests (leak detection
disabled). The load-interface verifier retains 11 direct + 432 message + 1,045
update cases, including, two-argument `0x003de260`, and Cross/Circle behavior.
Window presentation and live-dump pose/fog tests skip without their prerequisites,
and the host Vulkan test reports its backend unavailable where there is none.
No console comparison covers this slice.
