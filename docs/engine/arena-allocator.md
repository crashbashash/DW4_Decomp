# The arena allocator

`igArenaMemoryPool` is Doug Lea's `malloc` 2.7 with a repacked chunk header. The public-domain source
gives the control flow; it does not compile to retail as it stands.

The evidence is in `FUN_00315170` (12,180 bytes), which is `mALLOc` with its helpers inlined, in the
order the source has them:

| Retail | dlmalloc 2.7 |
| --- | --- |
| `sltiu v0,s3,-32` | `REQUEST_OUT_OF_RANGE`, `req >= -2 * MINSIZE` |
| `(req + 4 + 7) & -8`, raised to the minimum | `checked_request2size` |
| `(nb >> 3) - 2`, scaled onto the pool | `fastbin_index`, `fastbin(av, idx)` |
| a bit test on `av`, then `jal 0x318b40` | `malloc_consolidate` when the state is unset |
| `andi x,0x1f` before a `1 << n` | `idx2bit` |

**The header.** Where dlmalloc keeps a size word with two flag bits, this one is packed: the first word
holds the size from bit 5 up under a mask of `0xff00001f`, and sizes too large for it continue in the
halfword at `+8`, written `(size >> 19) & 0xfff`. Byte 3 carries a flag that moves the free-list links
from offset 4 to offset 12. That is why the masks in these functions are `0xfff` and `0x1f`, not `~7`.

**Functions.** `FUN_00315170`, `FUN_003194c0`, `FUN_00312ba0`, `FUN_0031b5d0` and `FUN_00310c00` share
the header, about 36 KB in all; which is `free`, `realloc` or `memalign` has not been settled.
`FUN_00318b40` is the consolidation step `mALLOc` calls. The header should be written as a bitfield
struct and proved on the smallest of them first: a function of 3,000 instructions cannot match while
the field accesses are hand-expanded.
