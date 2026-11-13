# Model-sequence JUMP and WCHECK

The contiguous four-body group `0x00394ae0..0x00394f98` implements these commands.
All four match: `beModelCtrl_RunJump`, `beModelCtrl_StartWaitCheck` and `beModelCtrl_UpdateWaitCheck` in one-function files
under `src/unmatched/`, and the adjacent `igObject::vfunc_39`.

| Entry | Bytes | Contract |
|---|---:|---|
| `0x00394ae0` | 68 | JUMP, `(owner, work, command)`: calls owner vtable `+0x8c` with the command name (`command+8`), using the empty string if null; returns 1 regardless of the virtual result |
| `0x00394b30` | 180 | WCHECK start, `(owner, work, command)`: interns the command name, releases the previous `work+0x4c` string and assigns the new one; returns 0 |
| `0x00394bf0` | 920 | WCHECK update, `(owner, info, node, work)`: polls the wait condition, clears the wait string before resuming dispatcher `0x00395250` |
| `0x00394f90` | 8 | The adjacent empty body, already named `igObject::vfunc_39` |

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

## Limits

Update has no null guard before `strcmp`: the caller must invoke it only with a
pending wait. Allocation, string operations, strcmp, messenger, movement query,
virtual slots and `0x00395250` are callees of these bodies, not part of them. No
animation clock, rendering, audio, or whole-menu equivalence follows from this page.

## Logo sequence program

AREA entry 620's `j_startlogo` model-controller records give the logo's program:

```
SQ_OPEN:  ACTION OPEN;  WCHECK Action; JUMP SQ_WAIT
SQ_CLOSE: ACTION CLOSE; WCHECK Action; JUMP SQ_ERAS
SQ_WAIT:  (empty)
```

The retail Action2 completion chain is recovered in [`action2-timing.md`](action2-timing.md).
The strict timer/joint comparisons, shared-clock conversion, generic dispatcher
`0x00395250`, and full ISSEQNAME/ISRUN semantics still need independent recovery
and validation. This slice does not establish retail action timing or pixels.

## Gates

`make check` reports zero mismatches and every split unit round-trips;
`make link` is BYTE-IDENTICAL and `make typed-check` matches its baseline.
No console comparison covers this slice.
