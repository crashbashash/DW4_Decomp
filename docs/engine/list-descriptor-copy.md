# Inherited list storage-descriptor construction and copying

Finding [#887](../findings/findings-0751-1000.md#f887) records **eleven complete bodies / 1,468 code bytes**, all with exact
matching source, plus portable guest-reference behavior in
[list-descriptor-copy.c](../../recovered/engine/list-descriptor-copy.c).
Four new exact functions add **800 bytes**: base descriptor copy 300, memory clone 116
and two native list field-specializers 192 each. The latter 384 bytes were previously
unclassified data gaps; the analysed Ghidra snapshots now identify both callbacks.
Classified code increases by 384 bytes and the function denominator by 2; retail
bytes and linked-section size remain unchanged.

The reviewed callback recovery script checks original registrar literals, prologue,
handle load, query/replacement calls, complete 192-byte extent, epilogue and absence
of overlap before creating functions, without analysis. See
[the reproducible script](../../scripts/recover_list_specializers.py).
Existing memory constructor/copy interfaces are folded with explicit receivers and
source operands. Views for the vtable clone slot, reference header and default
pointer describe ABI positions, not original C++ declaration spelling.

## Copy constructor layers

| Body | Address | Bytes |
| --- | --- | --- |
| Base metadata-field copy | `2fc0e0` | 300 |
| Reference-field copy | `305c70` | 80 |
| Memory-reference-field copy | `2fb9a0` | 128 |
| Memory-reference construction | `2fb8e0` | 72 |
| Memory-reference initialization | `2fb930` | 108 |
| Memory-reference factory | `2bf2e0` | 160 |
| Memory-reference clone | `2bf380` | 116 |
| Default raw allocation forwarding | `2ff800` | 8 |
| Generic metadata-based clone | `300c60` | 112 |
| Object-list storage specialization | `2bd830` | 192 |
| Integer-list storage specialization | `2cac20` | 192 |

`igMetaField_CopyConstruct` delegates header copy, stamps its vtable and clears
its destination name cell before copying offset/runtime/type/size/index and
external publication fields. It retains the current source name, applies the
original destination release sequence and re-reads the source before publication.
Parent/invariance pointers and all observed reset/copy/comparison/persistence bytes
are copied without adding ownership policies.

It allocates fresh default storage using the destination's captured requested
size, publishes that pointer, then re-reads size and source-default pointer for
copying bytes. An allocator callback can change those later operands. The matching
source uses a pointer projection at +32, because treating this address as an
integer changes MWCC's load schedule. The projection preserves the observed
pointer ABI and does not modify generated reflected types.

The reference layer stamps its vtable and copies construct/destruct flags. The
memory layer stamps `532a50`, clears `_memTypeRef` and `_poolName`, and copies
ref-counting, memory type/size, reset, release and alignment values. It does not
retain those borrowed type/parent pointers or copy the cleared derived members.

These are constructor paths, not safe assignment helpers. Self-copy can clear
its source name and overwrite its source-default pointer before byte copying.
The oracle preserves that instruction behavior instead of adding alias protection.
Padding and unwritten members retain their prior contents.

## Construction and clone modes

The memory-reference descriptor factory uses class handle `585d80`, size 80 and
the normal runtime vs bootstrap switch. Cold construction runs the existing base
reference-field constructor, stamps `532a50`, clears the two derived pointer cells
and performs the initializer chain. Memory initialization sets ref-counting and
release flags, zero memory size/type, reset method 3, alignment -1 and shallow-copy
method 2. The adapter extends the concrete factory module rather than duplicating
its ancestor implementation. The current factory oracle covers 24 bodies / 2,368
bytes in 336 cases; 23 bodies / 2,292 bytes match, with header initializer 76 retained
as its existing compiler residual.

Cold `igMemoryRefMetaField_Clone` uses default raw allocation (`2ff800`) for 80 bytes
and invokes the complete copy chain when allocation is non-null. A null allocation
returns zero. The default wrapper forwards size/prefix and forces allocator zero.
The copy-flag argument has no observed effect on this cold constructor branch.

With the object system active, the clone first runs the memory-field registration
guard and delegates to `igObject_CloneViaMetadata`. That helper re-reads the current
source vtable's metadata getter, selects the source object allocator, creates an
instance and calls the existing contents-copy routine with source and flag. It
returns the instance. This checkpoint preserves that delegation, not a complete
recovery of the contents-copy/instance machinery below it. Flag enum meanings and
a new allocation-failure policy are not inferred.

## Actual inherited `_data` specialization

The native `igObjectList_InitFields` and `igIntList_InitFields` callbacks perform
the same algorithm with different published handles and element providers:

| Callback | Published class handle | Element provider | Descriptor publication |
| --- | --- | --- | --- |
| `2bd830` | `585b60` | `2bd2e0` | `585b68` |
| `2cac20` | `586880` | `2c3090` | `586888` |

Each captures its current class metadata, looks up inherited `_data` through the
real string-field selector helper, finds that descriptor's pointer index and
invokes its current virtual slot 84 with argument 1. It stores the element-provider
result as `_memType`, clears `_memSize`, selects its own descriptor-publication
cell, then runs the original finalize/retaining-replace helper. Finally it releases
the clone-owned temporary reference. It does not add null/name/copy fallback checks
or replace the captured metadata handle after provider callbacks.

The parent retains the original descriptor; the child owns the clone. This avoids
mutating the shared parent's element information. Later generic layout finalization
is responsible for updating field parent/index information where appropriate.
The element-provider implementations and full inherited `igDataList` schema remain
required recovery work.

## Verification and remaining work

```sh
python3 testing/test_list_descriptor_copy_retail.py
python3 testing/test_field_factories_retail.py
python3 testing/test_metadata_callback_services_retail.py
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

**95 original-instruction RAM/defined-return/ordered-call cases** cover all eleven
bodies, default sizes 0/4/8, null/non-null names, fresh/self copies, active/inactive
system paths, clone flags, allocation failure, post-allocation size/source mutation,
registration-time vtable changes and provider-time published-handle mutation.

Both native specialization callbacks execute the actual lookup, cold clone and
three-layer copy chain, finalization, retaining replacement and publication. The
fixture supplies an inherited descriptor ABI view and retained field list;
assertions prove parent ownership remains one, clone ownership becomes one, shared
name references become two, default buffers are distinct with matching bytes,
size/type/publication changes are correct and the parent's published descriptor
stays intact. This is component composition, not complete live class registration.

Element descriptor providers, type queries, interning, allocator/owner services,
runtime CreateInstance and generic copy contents remain controlled. The existing
78-checkpoint deferred-callback oracle still treats complete child registration
as a boundary. Fourteen independent dependency tests check reviewed callback
extents and the original memory-clone/copy-chain instruction targets. Native
gameplay is unchanged; full child-list bootstrap and Work instance creation remain
active work.

The [list registration follow-up](list-registration.md) now composes these callbacks
with the original three-field `igDataList` schema and all four list registrars under
Work dependency dispatch. Scalar singleton publication and wider type/instance
services remain explicit boundaries.
