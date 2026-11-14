# The arena allocator

`igArenaMemoryPool` is Doug Lea's `malloc` 2.7 with a repacked chunk header. The public-domain source
gives the control flow and the declaration order of each function's locals; the header accesses, the
integrity checks and the system-memory calls are Alchemy's.

## The functions

Each is dlmalloc's routine with the pool as its first argument. The roles follow from the calls: the
pool's `MemoryOperation` calls one allocator, one releaser, one resizer and one aligned allocator, and
the notices name three of them: `igArenaDoCheckMallocState(E95)`, `igArenaSystemMalloc (E66)` and
`igArena_malloc (E67)`. The resizer's two assertions carry dlmalloc's own text, `ncopies >= 3` and
`(igUnsignedInt)(newsize) >= (igUnsignedInt)(nb)`.

| Retail | dlmalloc 2.7 | Evidence |
| --- | --- | --- |
| `igArenaMemoryPool_InitMallocState` | `malloc_init_state` | fills the 95 bins, sets the two 256 KB thresholds, makes raw memory the top chunk |
| `igArenaMemoryPool_CheckMallocState` | `do_check_malloc_state` | walks the fast bins and the bins; its notices are E38 to E47, E95 and E96 |
| `igArenaMemoryPool_SystemMalloc` | `sYSMALLOc` | called once by `mALLOc`; asks the pool's slot 103 for system memory; reports as `igArenaSystemMalloc` |
| `igArenaMemoryPool_SystemTrim` | `sYSTRIm` | called by `fREe` and by the pool's trim; gives pages back through slot 104 |
| `igArenaMemoryPool_Malloc` | `mALLOc` | request size check, fast bins, small bins, `malloc_consolidate`, the bin scan; reports as `igArena_malloc` |
| `igArenaMemoryPool_FreeChunk` | `fREe` | fast-bin push, else coalesce, unsorted list, trim over the threshold |
| `igArenaMemoryPool_MallocConsolidate` | `malloc_consolidate` | empties the fast bins; initialises a state whose fast limit is 0 |
| `igArenaMemoryPool_Realloc` | `rEALLOc` | calls `mALLOc`, `fREe`, `memcpy` and `memmove` |
| `igArenaMemoryPool_MallocAligned` | `mEMALIGn` | calls `mALLOc` with padding, frees the lead and the remainder |

The checks dlmalloc compiles in under `DEBUG` are always present and run by level: `check_chunk` and
its relatives when `_heapIntegrityCheckLevel` is above 0, `check_malloc_state` at 2, and at 3 every
entry point checks the whole heap on entry through a scoped object (`ArenaHeapCheck`, whose
constructor and destructor both call the heap check). Each `assert` became a notice: print the pool
statistics, report, and let the answer 2 silence that check.

## The state

`ArenaState` is `malloc_state`: the fast-bin size limit with its two flag bits (bit 0 any chunks, bit 1
fast chunks; the string calls it `_maxFastBinSize`), ten fast bins, the top chunk, the last remainder,
96 bins, a four-word bin map (three words are scanned), the trim threshold, the top pad, the mmap
threshold and counts, the page size and the contiguity flag. A bin (`ArenaBin`) is a 20-byte
pseudo-chunk, a chunk header and room for the links in either header form, so bin `i` sits at
`52 + 20 * i` and the unsorted list is bin 1, which is also the initial top. Alchemy's block list and
address range follow. The top and the bins are typed: `top` is a chunk pointer and a bin's header is
a `TaggedBlockHeader` member, so the allocator reaches them without a cast (see below for what a
cast costs).

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
| `initChunkHeader` | `set_head` on a new chunk | takes the arena, reads its pool index, picks the header form |
| `initFencepost` | the fencepost `size` stores of `sYSMALLOc` | an empty header with no pool, marked in use by its caller |
| `setChunkBytes` | `set_head` on an existing chunk | keeps the pool index; changes form only when the size requires |
| `setChunkPayload` | `set_head_size` in `mEMALIGn` | records the request size inside an unchanged chunk |
| `payloadSize`, `chunkPoolIndex`, `IS_ARENA_CHUNK` | none | the pointer check ahead of a list walk |
| `largeBinIndex` | `largebin_index` | |

`initChunkHeader` is one routine with two modes, and the malloc pool's header writes are the same
routine with no total. Given a payload size it picks the form from the size and the pool index and
takes the header's own size when the total is 0; given a size of -1 it derives the payload from the
total. With the constant -1 the second mode's leftover test, `if (total == 0) total = 12`, survives
in the bytes although that path already knows the total is 0. It takes the arena and reads
`_poolIndex >> 1` itself: with the index passed as an argument the load is evaluated ahead of the
size and total arguments, and the scheduler then orders one of the two header writes of `fREe`
differently from retail. A wrapper that passes the index on to a general routine is not it either:
the bottom-up inliner keeps the general routine as a call.

## What Alchemy added

- **Header size in `rEALLOc`.** A request may need the other header form than the chunk has. When
  the new form is the smaller one the chunk keeps its 12-byte header and the padded size grows by
  the difference; otherwise the payload is moved with `memmove` to its new offset before the header
  is rewritten, and the chunk's `used` bit, read before, is put back.
- **Pre-size in `sYSMALLOc`.** The request to the system is the page-rounded distance from the old
  end of the top to the new top plus one smallest chunk. While the pool's system memory is below
  `_preSize` the request becomes the whole remainder of the pre-size and `_poolPreSized` is 1; once
  it is reached the state becomes 2, with a notice when option 0x40 is set. A block the system
  cannot place after the top becomes a new top, and the old top is closed with two fenceposts and
  freed, as dlmalloc does for foreign `sbrk` memory.
- **Retries.** `sYSMALLOc` asks slot 26 of the pool for memory back (levels 0 and 1, twice at most)
  and then the out-of-memory hook (slot 21, attempt 3) before it reports E103 and returns 0; any of
  them answering nonzero restarts it. `mALLOc` consolidates the fast bins and scans once more
  before it calls `sYSMALLOc`, when the pool sits on raw memory or is not pre-sized. Option 0x10
  makes `mALLOc` allocate from the top only.

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
- **Typed state members.** With the bins declared as raw bytes and the top as a `char *`, every use
  carries a cast. Inside `mALLOc`'s loops the cast address of the unsorted bin is then moved to a
  temporary in front of the loop and spilled (one more stack slot than retail), and the validity
  check of the top loads its header flag three times where retail loads it once.
- **Statistics through getters.** The out-of-memory notices pass twelve 64-bit counters as `%u`.
  Read through `long long` getters they are loaded whole before the conditional argument
  (`Raw`/`System`) and truncated after it, as retail does; a cast on the member is narrowed to a
  32-bit load placed after the conditional.
- **Locals where the value lives.** The chunk before the victim is a block local in the small-bin
  path and in the unsorted loop, the function's `bck` serves binning and the bin scan, and
  `sYSMALLOc` reuses its new top and new end for the separately placed block: each choice decides
  which value is a later web of a reused variable, and those colour first.

## Open questions

- The four allocator entry points keep their address names. The notices give `igArenaSystemMalloc`
  for `sYSMALLOc` and `igArena_malloc` for `mALLOc`; `igArena_free`, `igArena_realloc` and
  `igArena_memalign` would follow the second pattern but no string confirms them.
- Slot 26 of the pool (`vfunc_28(int level)`) is known only from its use in `sYSMALLOc`: called with
  0 and then 1, a nonzero answer meaning memory came back.
