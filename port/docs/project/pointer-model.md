# The pointer model — how a 32-bit game becomes a 64-bit native program

This is port task **P1.5**, and it is a *decision*, because everything downstream (the platform
shims, the asset loaders, the renderer) depends on it. The decompilation itself does not choose:
it keeps the game's own 32-bit spelling, and this document says what the port does with it.

## Why a decision is forced

The game was built for a 32-bit address space and stores addresses in 32-bit fields. Measured in
`data/reflection.json`: **1,567 of 3,680 fields (43 %) are reference-typed** —
`igObjectRefMetaField` 1,278, `igStringMetaField` 144, `igRawRefMetaField` 76,
`igMemoryRefMetaField` 69. The matched C stores and reads them as `int`, performs pointer
arithmetic on them (1,013 literal `*(int *)((char *)(x) + N)` sites, plus the pointer walks), and
the CRT hands the allocator the whole address space above the image:

| fact | value | source |
| --- | --- | --- |
| image / BSS end | `0x0058D280` | `docs/engine/binary.md`, finding [#380](../../../docs/findings/findings-0251-0500.md#f380) |
| heap | `SetupHeap(0x0058D280, -1)` — the image's end to the top of RAM | CRT startup, re-linked by the repo |
| address space | 32 MB, flat LOAD segment, 1 MB stack at the top | `docs/engine/binary.md` |
| reference fields | 4-byte handles that hold **resolved pointers** at runtime (the loader converts the pack's ids to pointers in a later pass) | finding [#423](../../../docs/findings/findings-0251-0500.md#f423) |

On a 64-bit host a pointer is 8 bytes, so a resolved pointer no longer fits the field that holds
it. That is the whole problem, and there are exactly three ways out.

## The options

**(a) Raw 32-bit handles plus a guest arena (recommended).**
Allocate one host region for the guest and keep every address in it 32-bit. The allocator shim
hands out arena offsets where the game called `malloc`, and nothing in the game's data layout
changes. This is the only option that needs **no change to the matched C**, so the byte-identity
oracle keeps working and the port can boot while the decompilation is still in progress.

**(b) A 4-byte handle type plus the same arena.**
Same runtime model as (a), but the *C* says what a field is: a 4-byte struct
(`typedef struct { uint32_t off; } dw4_ref;`) instead of `int`. A member access `p->_pImage.off`
compiles to the same 4-byte load, so this stays codegen-identical and therefore still matches —
but the code becomes readable, and the port keeps a single place to add bounds checks, arena
relocation or an eventual widening. This is the shape P1 should aim at; it is (a) with the types
written down.

**(c) 64-bit host pointers in the fields.**
The clean end state for a native program, and the most work: every reference field widens to 8
bytes, which changes the struct layout on both sides (the matched C and `reflection.json`), breaks
byte-identity as a comparison, and requires finding every place the game assumes a pointer is 32
bits (the 1,013 arithmetic sites, the pack loader's id→pointer pass, the save format, the disc
format). It also changes nothing about the *risk* the porting plan names — the renderer and the
asset path — while making the decompilation's oracle unusable in the meantime.

## Decision

**Take (a) now, aim at (b), and treat (c) as a later, optional widening.**

The reasons are the plan's own:

* **The oracle matters more than the pointer width.** Byte-identity is how the decompilation banks
  verified behaviour; a change that breaks it removes the only check the port has while it is being
  written.
* **(c) does not de-risk the port.** The plan's caution is that the risk is the graphics and asset
  path; the pointer width is orthogonal to it, so it should not be paid for first.
* **(b) is achievable without a big-bang.** Because a 4-byte handle type is layout-identical, the
  conversion is incremental and each step is checked by `make check` — the same property that made
  the typed-coverage batches safe.

## What this implies for the decompilation (P1)

1. **A reference field stays 4 bytes.** Typed coverage should name it (`p->_pImage`) but not
   change its width, and the port's handle type is defined in one port header, not in
   `include/dw4/reflected.h` (which mirrors the reflection metadata).
2. **No field access may assume `sizeof(void *) == 4` in new C.** Matched C is exempt (it is the
   retail spelling), but anything written for the port — the shims, the loaders, the renderer —
   uses the handle type.
3. **The arena boundary is one file.** Everything the game does with an address goes through the
   allocator and the handle accessors, so the port has exactly one place to translate between a
   guest offset and a host pointer.

## Where this stands

The handle type exists and is exercised: `dw4_handle` in [`../../include/dw4/scene.h`](../../include/dw4/scene.h)
is `{ uint32_t off; }` and it is the only way the loader hands anything out — `dw4_scene_handle(id)`
and `dw4_scene_host(h)`, with the arena's first payload at `0x1000` so a zero handle is NULL. The
scene loader (finding [#481](../../../docs/findings/findings-0251-0500.md#f481)) places 50,497 ids and resolves every mesh through those handles.

The reference rewriting is done too: `dw4_scene_load` performs finding [#423](../../../docs/findings/findings-0251-0500.md#f423)'s id -> pointer pass, and
which values are references comes from the value's own descriptor — its type id **is** the kind
(finding [#482](../../../docs/findings/findings-0251-0500.md#f482): type 0 is always an object id or NULL, type 7 always a pool-block id or NULL, with no
value of either kind ever outside the id space). The (class, offset) table this section used to
expect was not needed. What is still not rewritten is the *contents* of a memory block, because a
block can be shared and the item kind belongs to the field that points at it.

## First action (when the port starts)

Define the handle type in the port's platform header, use it in one ported function, and confirm
with `make check` that the member access is still the same 4-byte load. That is the whole test of
option (b), and it costs one function.
