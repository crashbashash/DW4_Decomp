# Metadata construction, ownership and registry indexing

This page covers ten complete bodies / 1,216 code bytes: the contiguous
metadata constructor/initializer/copy/release run, metadata factory, name setter,
index assignment, registry append, pointer search and base header copy dependency.
Sizes include initialization (284), naming (148), base header copy (160) and
pointer search (68). The interfaces explicitly forward their receivers,
copy source and appended metadata pointer.

## Construction and field storage

`igMetaObject_Create` (`2be4f0`, 160 bytes) uses the same system-state switch as
concrete descriptor factories. When `*586dc8` is nonzero, it registers the class,
re-reads handle `585be8` and calls `igMetaObject_CreateInstance`. Otherwise it
raw-allocates 100 bytes, conditionally runs the constructor, then unconditionally
invokes the result's current virtual slots 44 and 36 (with zero at slot 36).
Successful allocation/construction is an original lower-service assumption.

`igMetaObject_Construct` (`2fd7c0`, 84) runs object header construction, stamps
vtable `532bb0`, clears name and pool-name cells, invokes its initializer for a
non-null receiver, then creates the field-pointer container with factory
`2c2670(0)` and stores it at +40. It does not add a retain to that factory result.

This identifies a previously unresolved container: factory `2c2670` uses metadata
handle `5860d0`, decoded as reflection class **`__internalObjectList`**. Its cold
constructor `2eab70` stamps vtable `5327d0`; its allocation size is 16 bytes.
Independent retail opcode/table checks connect that factory to the metadata
constructor. Buffer +8 / count +12 are the already observed internal ABI, distinct
from the reflected `igMetaFieldList` layout. This identifies the runtime class;
it does not claim an original C++ declaration.

`igMetaObject_Init` (`2fd820`, 284) runs the original object header initializer,
sets vtable and all observed metadata defaults: version 1.0, persistence 1,
alignment 4, declared size -1; names, offsets/counts, flags, parent/proxy/instance/
child/field pointers and callback pointers are cleared. Halfword/byte widths,
unwritten padding and the repeated field-container clear are preserved by exact
source. Initialization assumes a fresh object; it does not release previous lists.

The initializer ensures the string pool, interns null, then reads/releases the
current pool-name token and publishes the interner result. The read occurs after
the callback, which matters under mutation. These defaults imply no copy/pool/default
allocation policy.

## Names and ownership

`igMetaObject_SetName` (`2fddb0`, 148) ensures the pool even for null input, interns
the supplied name, reads the current token after that callback, releases it and
publishes the captured result. Token release subtracts one at token -4 and, on
zero, calls chunk release with owner word at token -8 and header pointer token -8.
An existing canonical token is retained by the interner before the prior field
reference is released, so ownership stays stable when both names share a token.

`igMetaObject_ReleaseLists` (`2fd980`, 136) decrements the field-list reference and
calls object destruction if its low 23 bits become zero. It then re-reads the child
list pointer and applies the same release. It neither clears these member cells
nor releases other metadata members. A first destructor can change which child
list the second operation sees.

`igMetaObject_CopyConstruct` (`2fd940`, 60) delegates to base header copy, stamps
vtable and clears name and pool name. Other metadata fields are not copied by this
body. The base helper `2fef70` (160) initializes the destination header, then copies
source byte +6 bit 7. It queries the allocation owner and code helper when the
system is active. A self-copy reads the source flag after initialization has
cleared it. Allocator owner lookup/code services remain external here.

## Registry index assignment

`igMetaObject_AssignTypeId` (`2fe7a0`, 108) stores the pointer-search result in the
**word at metadata +12 (`_index`)**. This is not a halfword version field. It looks
in the registry pointer at object system +24. On -1 it calls
`igObjectSystem_AppendMetaObject` (`2d3060`, 8), then re-reads the current global
system and registry and searches again. A second -1 is stored unchanged.

The append wrapper executes its original delay-slot registry load and tail-calls
`MetaRefList_AppendRetained`, explicitly forwarding the metadata pointer. The
already recovered retaining append increments the object's reference before the
vector append. Pointer search `2ea820` (68) captures buffer +8 and signed count +12,
returns the first equal pointer's index, or -1 for empty/negative/missing ranges.
The final vector append/growth primitive is described in
[internal pointer lists](internal-object-lists.md).

## Verification and remaining work

```sh
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

Registering Work produces a pooled class name, version 1, persistence 1, an assigned
registry index, one registry entry and exactly one final metadata reference.

The internal field-list factory, constructor, buffer allocation and growth are
described in [internal pointer lists](internal-object-lists.md). Full object-system
bootstrap, further schemas, memory/array fields and gameplay receivers remain
required work.
