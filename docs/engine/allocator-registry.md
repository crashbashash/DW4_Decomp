# Allocator-owner lookup, encoded indices and allocation dispatch

**13 complete bodies / 772 code bytes**: the contiguous
owner/selector run, its list-search and default-getter dependencies, and three
allocation wrappers. They include the 140-byte
encoder, the 72-byte index search, the 56-byte default
allocation wrapper, which uses an explicit allocator ABI view, and
the 292-byte owner lookup in `src/engine/core/igObject_tail.inc`.
The shared-tail wrapper `Memory_AllocateBufferViaSharedTail` opens the memory API's run of the Core library unit,
[igMemory.inc](../../src/engine/core/igMemory.inc). Its shared tail is `FUN_002ed1e0`;
the 28-byte direct tail is `Memory_AllocateBufferDirect` (`2ed240`).

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
Shifts wrap at32 bits and results are sign-extended.
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
| `2ed240` | Direct tail dispatch to supplied allocator slot216: the size arrives first and the allocator second, and the call passes the allocator as receiver with the size as its argument |

The shared-tail wrapper's Ghidra address set contains40 bytes but spans52 bytes:
`2ed1c0..2ed1f4`. Treating its occupied-byte count as contiguous length truncates
the slot load, final `jr t9` and delay slot. `scripts/dump_function_extents.py`
exports all five reviewed spans from the analyzed project with
analysis disabled, and `tools/split.py` generates symbols/assembly from them, so the
twelve additional bytes are classified as code. `tools/test_function_extents.py` checks the
complete wrapper alongside the four other reviewed spans. Retail objdump confirms the
shared tail. The layout keeps it as two
symbols: `extent-overrides.tsv` cuts the wrapper to `2ed1c0..2ed1d4`, and the shared tail is
`FUN_002ed1e0` at `2ed1e0..2ed1f4`.

## Boundaries

Allocator virtual methods are not covered here, and neither are registry
bootstrap/publication or type/scalar publication. `igObject_CopyConstructHeader` copies the
high flag bit and stores the owner-derived encoded allocator index at byte7.

`testing/test_lua_engine_dependencies.py` verifies registry/slot/direct-call evidence and the
complete wrapper's indirect jump. The memory descriptor's slot84 clone is a reviewed
root, connecting the inherited-list descriptor copy chain to
header copying and these allocator services. This does not infer unknown virtual
receiver edges.

`tools/verify.py` handles one relocation case specially: MWCC can place a loop's
HI16 at a higher address than its paired LO16. Sorting relocations by address
changes ELF table order and falsely leaves valid pairs unresolved, so the verifier
preserves the table order. `tools/test_verify_relocations.py` reproduces the
backward pair with a negative low half; independent GNU ld relocation of the real
owner candidate agrees with the verifier on all292 bytes. This validates relocation
handling, not a claim that that candidate matches retail.

The bootstrap/context recovery also covers registry-list lifetime
and global publication. Remaining work includes compiler residuals, context-record
initialization/stack/special delegation, actual allocator virtual implementations,
scalar/type publication, object cloning and broader Lua gameplay receivers.
