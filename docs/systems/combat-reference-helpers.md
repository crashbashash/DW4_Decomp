# Combat callback reference ownership helpers

The reference/list utility recovery now includes **fifteen complete ownership, string
and allocator bodies, 1,732 code bytes** ([#1037](../findings/findings-1001-1250.md#f1037), [#1051](../findings/findings-1001-1250.md#f1051), [#1059](../findings/findings-1001-1250.md#f1059), [#1060](../findings/findings-1001-1250.md#f1060)). Retail unwind data
identifies eight additional cleanup bodies, contributing 1,012 matched bytes.
Every one of the nineteen functions in the contiguous
`0x3e9010..0x3e93b8` utility run is now recovered: 816 code bytes in total,
excluding alignment gaps. Retain and allocator selection are direct GAMERAM
calls; the whole run provides the surrounding reference/list contract.

| Address | Bytes | Semantic role / source |
| --- | ---: | --- |
| `0x00130720` | 116 | [Deleting interned-string wrapper cleanup](../../src/engine/StringRef_Destruct_00130720.c) |
| `0x001363f0` | 128 | [Unwind reference cleanup](../../src/engine/ObjectRef_Destruct_001363f0.c) |
| `0x00150eb0` | 128 | [Unwind reference cleanup](../../src/engine/ObjectRef_Destruct_00150eb0.c) |
| `0x0033e9c0` | 128 | [Temporary owning-reference cleanup](../../src/engine/ObjectRef_Destruct_0033e9c0.c) |
| `0x003d9bd0` | 128 | [Unwind reference cleanup](../../src/engine/ObjectRef_Destruct_003d9bd0.c) |
| `0x003d9c50` | 128 | [Unwind reference cleanup](../../src/engine/ObjectRef_Destruct_003d9c50.c) |
| `0x003d9cd0` | 128 | [Unwind reference cleanup](../../src/engine/ObjectRef_Destruct_003d9cd0.c) |
| `0x003d9d50` | 128 | [Unwind reference cleanup](../../src/engine/ObjectRef_Destruct_003d9d50.c) |
| `0x003e9010` | 128 | [Deleting reference-wrapper destruction](../../src/engine/ObjectRef_Destruct_003e9010.c) |
| `0x003e90d0` | 32 | [Retain one object reference](../../src/engine/ObjectRef_Retain_003e90d0.c) |
| `0x003e9110` | 68 | [Release one object reference](../../src/engine/ObjectRef_Release_003e9110.c) |
| `0x003e9160` | 188 | [Retained list-slot replacement](../../src/engine/ObjectList_SetAtRetained_003e9160.c) |
| `0x003e92b0` | 124 | [Assign from reference storage](../../src/engine/ObjectRef_Assign_003e92b0.c) |
| `0x003e9370` | 56 | [Allocator selection](../../src/engine/Memory_SelectAllocator_003e9370.c) |
| `0x00406e60` | 124 | [Assign from an object pointer](../../src/engine/ObjectRef_AssignObject_00406e60.c) |

The generated names describe decoded operations. Address suffixes distinguish
the recovered bodies while their original template and type spellings remain
unknown. The C projects only the reviewed object prefix: an unused first word
and the 32-bit reference word at +4. It does not assert a complete original class.

## Retail unwind identities

The flat retail image preserves GAMERAM's exception-index record at `0x553b80`:
`(0x3fca10, 0xa388, 0x544fd4)`. It identifies the complete callback and its
cleanup table. Six reviewed entries associate concrete frame homes with
physical destructor targets:

| Cleanup entry | Frame offset | Destructor |
| --- | --- | --- |
| `0x545084` | `+0x408` | `0x1363f0` |
| `0x54508b` | `+0x4ac` | `0x1363f0` |
| `0x545099` | `+0x4a8` | `0x3d9d50` |
| `0x5450a0` | `+0x4a4` | `0x3d9cd0` |
| `0x5450a7` | `+0x4a0` | `0x3d9c50` |
| `0x5450ae` | `+0x49c` | `0x3d9bd0` |

Another entry at `0x545117` associates `+0x434` with `0x150eb0`, the cleanup
used by a nearby-target list. The four factory-reference destructors form a
complete contiguous 512-byte run at `0x3d9bd0..0x3d9dd0`. Their code equals the
existing `0x3e9010` destruction body and matches its pinned compiler profile.
The two core copies match the default profile; their branch scheduling differs
from the factory copies while preserving the same ownership rule.

These are physical cleanup identities and verified object-prefix operations.
Distinct entry points do not establish distinct original template spellings.
The [complete protected ranges](../engine/exception-unwind.md) are now decoded. The callback
itself remains unmatched; see [draft recovery](combat-draft-recovery.md#retail-unwind-data).

The string cleanup at `0x130720` releases its nonnull token by decrementing the
word at token−4. At zero it calls `StringChunk_ReleaseHeader` with both the owner
stored at token−8 and the header address token−8. It then optionally deletes the
wrapper for a positive signed-short flag, returns the wrapper and leaves its word
unchanged. The `0x33e9c0` cleanup is the packed object-reference operation below;
its unwind entry disproves a plain-vector interpretation of the temporary at
`+0x3e8`. These two complete bodies add 244 matched bytes.

## Ordering and destruction

Release does nothing for null. Otherwise it decrements the full word at +4,
reloads it and destroys the object when its low 23 bits are zero. The destructor
receives the object pointer in `a0`.

Both assignments capture their incoming pointer, retain a nonnull replacement,
then read the outgoing destination pointer. They release that object using the
same low-23-bit destruction test, publish the captured replacement and return
the address of destination storage. One entry reads the incoming pointer from
source storage; the other receives it directly. Retain precedes release, so
ordinary self-assignment balances ownership without a separate identity branch.

These helpers operate on the packed word, not just a separately stored count.
The readable mask widens the loaded signed word before masking with
`0x7fffffULL`. It avoids the draft's signed left-shift spelling while reproducing
the original two doubleword shifts. This is the same destruction boundary seen
in the engine's [object-reference fields](../engine/object-fields.md).

Deleting destruction first checks the wrapper pointer. It releases the contained
object using the same packed-word rule, then frees wrapper storage only when
the deletion flag narrowed to a signed short is positive. The contained word is
not cleared. This is a second complete body with the same operation sequence as
the nearby-query compiler's [emitted destructor](combat-helpers.md).

Retained slot replacement increments a nonnull replacement before reading the
old slot. That read and release are unchecked; count and index tests guard only
the final store. Destruction can change list storage, so the final store reloads
the data address. No bounds check is moved ahead of the old-slot read.

Allocator selection uses the incoming fallback when the direct-mode byte at
`0x554c14` is nonzero. Otherwise it resolves the selector word through
`Memory_GetAllocatorBySelector`. The direct path never reads the selector.

The data getter at `0x3e9090` and word getters at `0x3e90f0`/`0x3e9240` now
use the declaring `igDataList::_data` view. The two indexed bodies had inherited
an incorrect `_system` association from `beNDMWLoadIntf2`; finding [#1052](../findings/findings-1001-1250.md#f1052) retains
that association as refuted. All original getter bytes remain unchanged.

## Recovery corrections and verification

Raw m2c guessed an eight-byte count load where the original instruction is
`lw`. Correcting the load to four bytes is necessary before widening; an
eight-byte access can read a neighboring member and does not match. The release
draft also omitted the destructor's argument. The full original body proves the
call slot, and the recovered source preserves it.

All seven bodies are verified with the content-pinned alternate compiler and
`-O3,p`.
The ordinary compiler omits a zero word after the destructor call; that is a
real byte mismatch. The [compiler requirements](../engine/unit-compilers.md)
apply to checking and linking. The oracle verifies every code word and relocation,
including those interior zeros. `make check` and the byte-identical `make link`
are the integration gates; the retail assembly is never edited to accept a draft.

The [flat callback context](../../scripts/gen_combat_context.py) now declares
release as void and both assignment ABIs explicitly. It also uses the recovered
data and allocator-selector names. Reference storage uses
guest-word pointers in that analysis-only context to agree with reflected
four-byte fields. These are machine-ABI projections, not original template names.
The [three immediate helpers](combat-helpers.md), including the nearby query,
now match too. The full [calculation callback](combat-damage.md) remains
unmatched. No native gameplay integration is included.
