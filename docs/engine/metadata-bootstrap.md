# Metadata construction, ownership and registry indexing

Ten complete behavioral bodies / 1,216 code bytes are in
[metadata-bootstrap.c](../../recovered/engine/metadata-bootstrap.c): the contiguous
metadata constructor/initializer/copy/release run, metadata factory, name setter,
index assignment, registry append, pointer search and base header copy dependency.
Eight bodies / 988 bytes have exact source. Initialization (284) and naming (148)
add **432 matched bytes**; base header copy (160) and pointer search (68) retain
assembly. Existing matching interfaces now explicitly forward their receivers,
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
it does not claim an original C++ declaration. The actual list factory and buffer
allocation remain controlled in this checkpoint's metadata composition.

`igMetaObject_Init` (`2fd820`, 284) runs the original object header initializer,
sets vtable and all observed metadata defaults: version 1.0, persistence 1,
alignment 4, declared size -1; names, offsets/counts, flags, parent/proxy/instance/
child/field pointers and callback pointers are cleared. Halfword/byte widths,
unwritten padding and the repeated field-container clear are preserved by exact
source. Initialization assumes a fresh object; it does not release previous lists.

The initializer ensures the string pool, interns null, then reads/releases the
current pool-name token and publishes the interner result. The read occurs after
the callback, which matters under mutation. No copy/pool/default allocation policy
is synthesized from these defaults.

## Names and ownership

`igMetaObject_SetName` (`2fddb0`, 148) ensures the pool even for null input, interns
the supplied name, reads the current token after that callback, releases it and
publishes the captured result. Token release subtracts one at token -4 and, on
zero, calls chunk release with owner word at token -8 and header pointer token -8.
An existing canonical token is retained by the interner before the prior field
reference is released; an explicit alias case checks stable ownership.

`igMetaObject_ReleaseLists` (`2fd980`, 136) decrements the field-list reference and
calls object destruction if its low 23 bits become zero. It then re-reads the child
list pointer and applies the same release. It neither clears these member cells
nor releases other metadata members. A first destructor can change which child
list the second operation sees; the oracle includes that case.

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
The final vector append/growth primitive remains controlled.

## Verification and composition

```sh
python3 testing/test_metadata_bootstrap_retail.py
python3 testing/test_reflection_registration_retail.py --metadata
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

**214 original-instruction RAM/defined-return/ordered-call cases** cover all ten
bodies, composed object header/raw allocation, factory modes and handle reloading,
header/copy flags including self-copy, pool creation, callback-time name mutation,
canonical alias retention, reference count flags, list aliasing/destructor mutation,
negative list counts and registry replacement during insertion.

**487 registration cases** additionally compose original metadata factory,
initialization, pooled naming, registry pointer search and retaining insertion,
plus original concrete Work descriptor factories, default hooks and storage
wrappers. Executed-entry assertions cover all seven metadata entries reached by
registration. The original Work path produces a pooled class name, version 1,
persistence 1, index zero, one registry entry and exactly one final metadata
reference, alongside all previously checked descriptor schema/default assertions.

The internal field-list factory, type queries, base-class registration, allocator
virtual methods/table population, interning, vector append/growth, profile and
other system services remain controlled. Runtime CreateInstance is still a lower
boundary in this module's standalone oracle. Other generic descriptors in the
registration suite remain synthetic. Full object-system bootstrap, original
instance composition, further schemas, memory/array fields and gameplay receivers
remain required work. Native gameplay is unchanged.

The `--internal-lists` registration mode now also executes the original internal
field-list factory, constructor, buffer allocation and growth. See
[internal pointer lists](internal-object-lists.md) for current coverage and lower
allocator/byte/type boundaries. The standalone metadata oracle retains its
controlled list factory to isolate that module.
