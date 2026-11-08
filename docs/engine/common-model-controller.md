# Common-model request queues

The contiguous helper group `0x003e3b80..0x003e46a4` belongs to the reflected
`beNDMWLoadIntf2ComMdlCtrl` working object, also used by the title controller.
The logic of `0x003e3b80` is under [Submission and completion](#submission-and-completion).

| Entry | Bytes | Symbol and arguments |
|---|---:|---|
| `0x003e3b80` | 504 | `beNDMWLoadIntf2ComMdlCtrl__Start(cm, slot, name, sequence, wait)` — GENERATE, play, optional open tracking |
| `0x003e3d80` | 128 | `FUN_003e3d80(wrapper, flags)` — release wrapped object, optionally delete wrapper |
| `0x003e3e00` | 556 | `beNDMWLoadIntf2ComMdlCtrl__StartAt(cm, slot, name, sequence, vec3, wait)` — positioned GENERATE, play, optional open tracking |
| `0x003e4030` | 472 | `beNDMWLoadIntf2ComMdlCtrl__Play(cm, slot, name, sequence, wait)` |
| `0x003e4210` | 104 | `beNDMWLoadIntf2ComMdlCtrl__IsSequence(cm, slot, name, sequence)` — MODELCTRL ISSEQNAME |
| `0x003e4280` | 20 | `beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(cm)` — signed count <= 0 |
| `0x003e42a0` | 472 | `beNDMWLoadIntf2ComMdlCtrl__Close(cm, slot, name, sequence, wait)` — play and optional close tracking |
| `0x003e4480` | 72 | `beNDMWLoadIntf2ComMdlCtrl__IsRunning(cm, slot, name)` — MODELCTRL ISRUN |
| `0x003e44d0` | 20 | `beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(cm)` — signed count <= 0 |
| `0x003e44f0` | 436 | `beNDMWLoadIntf2ComMdlCtrl__Poll(cm)` — poll/drain both queues |

The names above describe observed behavior; they are not recovered method names.
`0x003e3d80` is the intervening reference-wrapper destructor, not a controller
constructor. Reflection identifies `_messenger` at +0x10, `_openDataList` at
+0x14, `_closeDataList` at +0x18. A `beLoadIntf2ComMdlData` entry has `_ramNo`
+8, `_openSQ` +0xc, `_infoName` +0x10. List count is +8, data pointer +0x10.

## Submission and completion

`0x003e3b80` sends `MODELCTRL` with the name and slot and the event `GENERATE` through the
messenger at +0x10 (`0x0038e5f0`), then does what `0x003e4030` does: it sends the same
message with the sequence as the event, and, when the wait flag asks for tracking, adds an
entry to the open list. A tracked entry is allocated through `0x003c7450`, using the
receiver's allocator (`0x00301000`) unless the byte at `0x554c14` is zero, which selects
`0x002f88e0` on the global at `0x587110`. It stores the slot at +8, interns the name into
+0x10 and the sequence into +0xc, appends through `0x00301e30` and drops its local reference.

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

## Engine boundaries

Positioned GENERATE copies the vector's 12-byte payload to a temporary before the message.

Allocation (`0x00301000`, `0x002f88e0`, `0x003c7450`), list append/remove
(`0x00301e30`, `0x002d6cf0`), object destruction (`0x002ff820`), string-pool
operations (`0x002eb010`, `0x002eadf0`, `0x002eaf60`, `0x0030c940`) and wrapper
free (`0x00100610`) are engine services outside this group, as are the messenger leaves
`0x0038d860`, `0x0038e5f0`, `0x0038f830`, `0x0038f4b0`, `0x0038e060` and
`0x0038f220`. Their implementations, animation timing and allocation failure are not
described here.

## Caller wait flags

The play/close contracts take five arguments, and retail passes the wait flag at 18
call sites of the Game Start code by reusing `t0=1` from nearby comparisons: nine in
the master update, one in `beNDMWLoadIntf2SelSlot__Close`, and six movement plus two
cancel calls in `beNDMWLoadIntf2SelSlot__UpdateSelection`. Omitting the flag, or passing
zero, is wrong there. Those movement, cancel and three-model close requests are tracked.

## Logo sequence

[Model-sequence waits](model-sequence-waits.md) recover the next contiguous
JUMP/WCHECK group. Action2 timing remains an unverified boundary.
