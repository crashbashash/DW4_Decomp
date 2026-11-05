# Common-model request queues

The contiguous helper group `0x003e3b80..0x003e46a4` belongs to the reflected
`beNDMWLoadIntf2ComMdlCtrl` working object, also used by the title controller.
`recovered/frontend/commdl.{c,h}` reconstructs its behavior over the existing
peek/poke/call API. The two empty predicates remain in `completion.c`.
These are behavioral references, not byte-matched compilation units.

| Entry | Bytes | Behavioral label and arguments after API |
|---|---:|---|
| `0x003e3b80` | 504 | `cm_start(cm, slot, name, sequence, wait)` — GENERATE, play, optional open tracking |
| `0x003e3d80` | 128 | `cm_ref_destroy(wrapper, flags)` — release wrapped object, optionally delete wrapper |
| `0x003e3e00` | 556 | `cm_start_at(cm, slot, name, sequence, vec3, wait)` — positioned GENERATE, play, optional open tracking |
| `0x003e4030` | 472 | `cm_play(cm, slot, name, sequence, wait)` |
| `0x003e4210` | 104 | `cm_is_sequence(cm, slot, name, sequence)` — MODELCTRL ISSEQNAME |
| `0x003e4280` | 20 | `cm_open_empty(cm)` — signed count <= 0 |
| `0x003e42a0` | 472 | `cm_close(cm, slot, name, sequence, wait)` — play and optional close tracking |
| `0x003e4480` | 72 | `cm_is_running(cm, slot, name)` — MODELCTRL ISRUN |
| `0x003e44d0` | 20 | `cm_close_empty(cm)` — signed count <= 0 |
| `0x003e44f0` | 436 | `cm_poll(cm)` — poll/drain both queues |

The names above describe observed behavior; they are not recovered method names.
`0x003e3d80` is the intervening reference-wrapper destructor, not a controller
constructor. Reflection identifies `_messenger` at +0x10, `_openDataList` at
+0x14, `_closeDataList` at +0x18. A `beLoadIntf2ComMdlData` entry has `_ramNo`
+8, `_openSQ` +0xc, `_infoName` +0x10. List count is +8, data pointer +0x10.

## Submission and completion

Every submission sends its sequence even when untracked. Tracking occurs only
when `(wait & 255) == 1`; two and 255 are not true, while 257 is. Entries are
appended independently, including repeated requests for the same model.
Allocator selection, string assignment and the local reference release follow
the original instruction order. Object releases mask the low 23 reference bits;
string releases test the entire decremented word. Wrapper deletion tests the
signed low 16 bits of its flags.

Polling visits the open list **newest first**. If ISSEQNAME's low byte is one,
it stops visiting that list, even if older entries have completed. Otherwise
it releases/removes that entry, clears the new tail slot and continues backwards.
The close list is visited independently with the same rule, using ISRUN instead.
A sequence change can therefore release an open wait while a close wait remains
pending until removal. `0x003e44f0` does not fill queues; the submission helpers
do.

## Verification and boundaries

```
python3 scripts/verify_commdl.py --elf orig/SLUS-20836/SLUS_208.36
```

The test executes all ten original bodies and compares 2,676 calls against C,
including ordered non-stack stores, final memory, query results and ordered
lower-engine calls with meaningful arguments. Cases cover tracking flags,
allocator branches, lazy string-pool creation (including null), old string
release, masked references, negative/empty lists, queue blocking, independent
close progress, duplicate requests, draining and re-entry. Positioned GENERATE
compares the copied vector's raw 12-byte payload, not the temporary address.
Function shapes were cross-checked with MIPS objdump against retail.

Allocation (`0x00301000`, `0x002f88e0`, `0x003c7450`), list append/remove
(`0x00301e30`, `0x002d6cf0`), object destruction (`0x002ff820`), string-pool
operations (`0x002eb010`, `0x002eadf0`, `0x002eaf60`, `0x0030c940`) and wrapper
free (`0x00100610`) remain explicit engine boundaries. Messenger leaves
`0x0038d860`, `0x0038e5f0`, `0x0038f830`, `0x0038f4b0`, `0x0038e060`,
`0x0038f220` are also supplied by the harness. Their original implementations
and animation timing are not verified by this test. Coverage of all ten bodies
is not a claim that every possible engine-side mutation or allocation failure
has been verified.

The native port imports this source unchanged and uses these queues for
title/Options. Its model executor still supplies bounded action durations and
sequence/running queries. A separate integration comparison executes the original
title and queue bodies against that same lower executor for 2,921 ticks, comparing
controller/options, queues, model state, text, handoff and attract state every tick.
This establishes integration at that boundary, not rendering, audio or timing
identity with a running console. The Game Start slot verifier still seeds its
queues; integrating the recovered submissions there is separate work.

## Caller wait flags ([#758](../findings/findings-0751-1000.md#f758))

The play/close contracts take five arguments, and Game Start C passes the wait
flag at 18 call sites where retail reuses `t0=1` from nearby comparisons: nine
in the master update, one in `ss_marks`, and six movement plus two cancel calls
in `ss_update`. Omitting the flag, or passing zero, is wrong there. The verifier
compares that fifth argument and the four meaningful ISSEQNAME arguments.
Explicit movement/cancel
checks and a direct three-model close regression pin tracked submission. The
slot matrix is 11 focused direct, 432 message and 1,045 update cases. This
strengthens call equivalence but does not replace that harness's queue seeds.

## Validation

- No matched-code coverage is claimed for this group.
- Behavioral checks: common-model 2,676; title 55,264; load controller 1,624;
  load interface 11 direct + 432 message + 1,045 update cases, including [#742](../findings/findings-0501-0750.md#f742).
- Native `make check` and `make check-retail` pass. Address/undefined-behavior
  sanitizer checks pass for title/queue tests, including storage reuse and
  overflow. Leak detection is unavailable under the test runner's tracing.
- Window-presentation and live-dump pose/fog tests skip without their required
  session/capture inputs. No synchronized console/native frame or audio
  comparison exists.

## Logo sequence ([#759](../findings/findings-0751-1000.md#f759)–[#760](../findings/findings-0751-1000.md#f760))

[Model-sequence waits](model-sequence-waits.md) recover the next contiguous
JUMP/WCHECK group. The port uses the extracted logo command program and
executes original helper instructions in the 2,933-tick integration oracle.
Action2 timing and the native dispatcher remain shared, unverified boundaries.
