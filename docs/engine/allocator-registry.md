# Allocator-owner lookup, encoded indices and allocation dispatch

Finding [#894](../findings/findings-0751-1000.md#f894) recovers **13 complete bodies / 772 code bytes** in
[allocator-registry.c](../../recovered/engine/allocator-registry.c): the contiguous
owner/selector run, its list-search and default-getter dependencies, and three
allocation wrappers. Eleven bodies / 692 bytes have exact source, among them the 140-byte
encoder and 72-byte index search (**212 matched bytes**), the default
allocation wrapper, exact at56 bytes with an explicit allocator ABI view, and
owner lookup292 in `src/unmatched/Memory_FindOwningAllocator.cpp`.
The shared-tail allocation wrapper52 (`Memory_AllocateBufferViaSharedTail` and its
shared tail `FUN_002ed1e0`) and direct tail28 have no C source yet, with readable
behavioral recovery.

Seven names in `config/SLUS-20836/names/AllocatorRegistry.tsv` describe observed operations.
The adjacent status/constant/no-op leaves retain address names because their wider
roles are not established. ABI projection names are not claims of original C++
class or method spelling.

## Owning-allocator search (`2f04f0`)

`Memory_FindOwningAllocator` searches the registry at `586f60` first, then `586f58`.
Each list uses data+0, signed count+4 and capacity+8. Each pass captures its initial
count minus1 and scans backward. Every row reloads the global registry pointer and
its data pointer. The second registry's count is captured only after the first pass
finishes. A null entry is skipped.

For a non-null candidate, virtual slot132 must return nonzero, then slot340 receives
the candidate and requested buffer and must return nonzero. The first such
candidate wins. The candidate pointer remains captured between those calls, but
its current vtable is reloaded for the second call. No reference is retained and
there is no special null-buffer guard; the virtual predicate determines whether
that buffer is owned. No match returns null.

## Encoding and resolving indices

`igAllocator_EncodeIndex` (`2f0670`) first reads object-system runtime byte0 through
`586dc8`. If active and allocator slot116 returns zero, it finds the allocator in
registry58 and returns `index << 1`. Otherwise it reloads the runtime byte: inactive
returns zero; active finds the allocator in registry60 and returns `(index << 1)|1`.
A slot116 callback can therefore change the second mode check, while the first
successful branch does not check mode again.

`igMemoryPoolInfoList_IndexOf` (`2fa5c0`) captures signed count and searches forward
for pointer equality, returning -1 when absent. Encoding does not reject that -1:
an absent entry produces signed -2 in the even registry or -1 in the odd registry.
The portable adapter preserves wrapping32-bit shifts and sign-extended results.
`2f0650` is the original encoder tail alias.

The separately recovered resolver (`2f0700`) selects a registry using bit0 and indexes
its data using arithmetic `encoded >> 1`. It adds no bounds check, including for
negative indices. The status leaf (`2f0620`) writes the current word at `4fb418`;
`2f0630` returns zero, `2f0640` returns -1 and `2f0660` is an original no-op.

## Allocation dispatch and repaired boundary

`Memory_GetDefaultAllocator` (`2f00d0`) tail-calls `2f88e0` with selector2. The [bootstrap/context recovery](registry-bootstrap.md) covers
that dispatch and its concrete selector/name receivers. The wrappers preserve these paths:

| Entry | Operation |
| --- | --- |
| `2ed1c0` | Size/allocator arguments branch to an internal shared tail, then invoke allocator slot216 |
| `2ed200` | Resolve the default allocator, then invoke its slot216 with captured size |
| `2ed240` | Direct tail dispatch to supplied allocator slot216 |

The shared-tail wrapper's Ghidra address set contains40 bytes but spans52 bytes:
`2ed1c0..2ed1f4`. Treating its occupied-byte count as contiguous length truncates
the slot load, final `jr t9` and delay slot. `scripts/dump_function_extents.py`
exports all five reviewed spans from the analyzed project with
analysis disabled, and `tools/split.py` generates symbols/assembly from them, so the
twelve additional bytes are classified as code. `tools/test_function_extents.py` checks the
complete wrapper alongside the four other reviewed spans. Retail objdump and
original-instruction execution independently confirm the shared tail. The layout keeps it as two
symbols: `extent-overrides.tsv` cuts the wrapper to `2ed1c0..2ed1d4`, and the shared tail is
`FUN_002ed1e0` at `2ed1e0..2ed1f4`.

## Verification and boundaries

`python3 testing/test_allocator_registry_retail.py` checks **186** original-instruction
RAM, defined-return and ordered-call checkpoints across all13 bodies and actual
owner/wrapper/buffer duplication/free composition. Cases cover reverse precedence,
null entries/buffers, eligibility/ownership combinations, empty/negative counts,
callback-time vtable/data/registry publication changes, second-pass capture,
mode/kind changes, absent indices, negative resolution, leaf results and wrappers.
Allocator virtual methods remain controlled leaves.

`python3 testing/test_memory_field_values_retail.py --allocator-registry` checks
**114** states with original array, buffer, owner, encoder/index and wrapper bodies
composed into real metadata and populated Work/list lifetime. Its extra runtime
header-copy checkpoint runs `igObject_CopyConstructHeader`: the high flag bit is
copied and owner-derived encoded allocator index is stored at byte7. Allocator
virtual behavior, registry bootstrap/publication and type/scalar publication remain
bounded. Other fixture modes still pass their original113 checkpoints.

Nineteen dependency tests verify registry/slot/direct-call evidence and the complete
wrapper's indirect jump. The memory descriptor's slot84 clone is a reviewed
root, connecting the inherited-list descriptor copy chain to
header copying and these allocator services. This does not infer unknown virtual
receiver edges.

Finding [#895](../findings/findings-0751-1000.md#f895) covers `tools/verify.py` relocation handling: MWCC can place a loop's
HI16 at a higher address than its paired LO16. Sorting relocations by address
changes ELF table order and falsely leaves valid pairs unresolved, so the verifier
preserves the table order. `tools/test_verify_relocations.py` reproduces the
backward pair with a negative low half; independent GNU ld relocation of the real
owner candidate agrees with the verifier on all292 bytes. This validates relocation
handling, not a claim that that candidate matches retail.

The bootstrap/context recovery also covers registry-list lifetime
and global publication. Remaining work includes compiler residuals, context-record
initialization/stack/special delegation, actual allocator virtual implementations,
scalar/type publication, object cloning and broader Lua gameplay receivers. Native gameplay
is unchanged.
