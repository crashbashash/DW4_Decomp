# The arena allocator

`igArenaMemoryPool` is Doug Lea's `malloc` 2.7 with a repacked chunk header. The public-domain source
gives the control flow and the declaration order of each function's locals; the header accesses, the
integrity checks and the system-memory calls are Alchemy's.

## The functions

Each is dlmalloc's routine with the pool as its first argument. The roles follow from the calls: the
pool's `MemoryOperation` calls one allocator, one releaser, one resizer and one aligned allocator, and
the string `igArenaDoCheckMallocState(E95)` names the checker.

| Retail | dlmalloc 2.7 | Evidence |
| --- | --- | --- |
| `FUN_0030f220` | `malloc_init_state` | fills the 95 bins, sets the two 256 KB thresholds, makes raw memory the top chunk |
| `FUN_00310c00` | `do_check_malloc_state` | walks the fast bins and the bins; its notices are E38 to E47, E95 and E96 |
| `FUN_00312ba0` | `sYSMALLOc` | called once by `mALLOc`; asks the pool's slot 103 for system memory |
| `FUN_00314510` | `sYSTRIm` | called by `fREe` and by the pool's trim; gives pages back through slot 104 |
| `FUN_00315170` | `mALLOc` | request size check, fast bins, small bins, `malloc_consolidate`, the bin scan |
| `FUN_00318110` | `fREe` | fast-bin push, else coalesce, unsorted list, trim over the threshold |
| `FUN_00318b40` | `malloc_consolidate` | empties the fast bins; initialises a state whose fast limit is 0 |
| `FUN_003194c0` | `rEALLOc` | calls `mALLOc`, `fREe` and `memcpy` |
| `FUN_0031b5d0` | `mEMALIGn` | calls `mALLOc` with padding, frees the lead and the remainder |

The checks dlmalloc compiles in under `DEBUG` are always present and run by level: `check_chunk` and
its relatives when `_heapIntegrityCheckLevel` is above 0, `check_malloc_state` at 2, and at 3 every
entry point checks the whole heap on entry through a scoped object (`ArenaHeapCheck`, whose
constructor and destructor both call the heap check). Each `assert` became a notice: print the pool
statistics, report, and let the answer 2 silence that check.

## The state

`ArenaState` is `malloc_state`: the fast-bin size limit with its two flag bits (bit 0 any chunks, bit 1
fast chunks; the string calls it `_maxFastBinSize`), ten fast bins, the top chunk, the last remainder,
96 bins, a four-word bin map, the trim threshold, the top pad, the mmap threshold and counts, the page
size and the contiguity flag. A bin is a 20-byte pseudo-chunk, a header word and room for the links in
either header form, so bin `i` sits at `52 + 20 * i` and the unsorted list is bin 1, which is also the
initial top. Alchemy's block list and address range follow.

## The header

Where dlmalloc keeps a size word with two flag bits, the header is `TaggedBlockHeader`: one word
holding the `used` bit (dlmalloc's `PREV_INUSE`), the count of header words less one, 19 bits of
payload size, 5 bits of pool index and three flags, the last of which (`big`) says a 12-byte header
follows. That form adds 12 more bits of size and of pool index and a second flag byte, whose bit 0
marks a system-mapped chunk (`IS_MMAPPED`). A chunk's bytes are its payload rounded to a word plus
its header words; the word before a chunk holds the size of a free chunk in front of it, as
`prev_size` does. The free-list links follow the header, so their offset is 4 or 12; the first is
dlmalloc's `fd`, the second `bk`.

The accesses are inline functions, shared in `CoreLibrary.h` after the struct:

| Inline | dlmalloc | Notes |
| --- | --- | --- |
| `alignedPayloadSize`, `chunkBytes` | `chunksize` | see the operand order below |
| `chunkLinks`, `setForwardLink`, `unlinkChunk` | `fd`, `bk`, `unlink` | |
| `chunkMemory` | `chunk2mem` | |
| `chunkIsMapped`, `chunkUsedBit` | `chunk_is_mmapped`, `prev_inuse` | |
| `initChunkHeader` | `set_head` on a new chunk | writes pool index and flags, picks the header form |
| `setChunkBytes` | `set_head` on an existing chunk | keeps the pool index; changes form only when the size requires |
| `setChunkPayload` | `set_head_size` in `mEMALIGn` | records the request size inside an unchanged chunk |
| `payloadSize`, `chunkPoolIndex`, `IS_ARENA_CHUNK` | none | the pointer check ahead of a list walk |
| `largeBinIndex` | `largebin_index` | |

`initChunkHeader` is one routine with two modes, and the malloc pool's header writes are the same
routine with no total. Given a payload size it picks the form from the size and the pool index and
takes the header's own size when the total is 0; given a size of -1 it derives the payload from the
total. With the constant -1 the second mode's leftover test, `if (total == 0) total = 12`, survives
in the bytes although that path already knows the total is 0.

## What the bytes showed

- **Chunk size into a local.** `total = chunksize(p)` reads as two statements,
  `payload = alignedPayloadSize(p); total = payload + (p->words + 1) * 4;`, where the destination's
  register depends on its declaration position. One inline returning the sum (`chunkBytes`) gives
  the same instructions and is right inside a condition or an argument, but its return value
  replaces the destination, which then colours as an inline temporary.
- **Accessors, not expressions.** A link store through `setForwardLink(p, *fb)`, a saved bit through
  `chunkUsedBit(p)` and an in-place size through a named local (`newsize = size - remainderSize`)
  each move a register that the written-out expression leaves wrong.
- **Declaration order is dlmalloc's**, with `size` ahead of `nextp` in `malloc_consolidate` and the
  loop index first in the checker.
- **The checker keeps dlmalloc's two constant asserts.** They cannot fail and emit nothing, but the
  integrity level they test is loaded before the top-chunk guard and reused by the first real check.

## Open questions

- `fREe` (`FUN_00318110`) compiles to retail's instructions with five words in another order, all in
  the block that merges the chunk into the top: retail issues `li a3,-1` before `move a2,s0` and the
  pool-index mask after the flag byte's, so the flag byte's register is reused. The same call in the
  other branch matches. The pre-scheduling order (`#pragma schedule off` in a scratch copy) is the
  same in both branches, 600 declaration orders and 432 spellings of the three statements leave it,
  and one more instruction at the head of the block flips the second pair, so the scheduler's input
  differs in something that leaves no instruction: most likely a register copy that coalescing
  removes. The draft is not in the unit.
- `sYSMALLOc`, `rEALLOc` and `mALLOc` have no source yet. Each spills four or five values to the
  stack, so the allocator's spill choices have to match as well as its colours. `sYSMALLOc` is
  `(pool, nb, bytes)`: the request size comes along so that the chunk it cuts from the old top gets
  its header from `initChunkHeader(oldTop, bytes, nb, pool, 0)`, and it is rewritten around the
  pool's pre-size (`_preSize`, `_poolPreSized`, option flag 0x40) rather than dlmalloc's contiguity
  cases: it rounds the new end of the top chunk to a page, asks slot 103 for the difference, reports
  the block through slot 109 and retries.
