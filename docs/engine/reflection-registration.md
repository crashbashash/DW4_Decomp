# Class registration and field-descriptor construction

Fourteen complete bodies (2,812 code bytes) cover the main
class registrar, inheritance, field creation/naming/layout, descriptor binding,
default storage and the original Work registrar/field adder.

The builders are inheritance 208, creation (`2fdf40`) 184, naming (`2fe000`) 208, default
storage 144 and descriptor finalization 128; inheritance is in
[igMetaObject.cpp](../../src/engine/igMetaObject.cpp), and default storage and
descriptor finalization are igMetaField methods in [igMetaField.cpp](../../src/engine/igMetaField.cpp). Of the five ownership/binding
bodies (452 bytes), the field adder is in
[igMetaObject.cpp](../../src/engine/igMetaObject.cpp) and the field configuration,
default and name setters are in [igMetaField.cpp](../../src/engine/igMetaField.cpp). The Work
registrar/adder is 300 bytes. Layout finalization
(444) is in [igMetaObject.cpp](../../src/engine/igMetaObject.cpp); main
registration (`2fe9c0`) is 744. ABI/virtual-slot views are observed projections,
not original C++ type declarations, and must not be instantiated.

## Registrar arguments and validity states

`igMetaObject_RegisterClass` (`2fe9c0`) receives the first eight arguments in EE
registers and the last three in caller stack slots +0/+8/+16:

| Argument | Meaning |
| --- | --- |
| 0 | Abstract-state value; low byte stored at metadata +26 |
| 1 | Address of the published metadata handle |
| 2/3 | Base registrar and base metadata accessor |
| 4 | Own metadata accessor, stored at +84 |
| 5 | Class name |
| 6 | Declared instance size, stored at +72 |
| 7 | Vtable getter; invoked only when argument 0 is exactly zero |
| 8 | Optional class field-adder callback |
| 9 | Optional extra callback-vector item |
| 10 | Optional zero-terminated callback-vector item list |

The registrar always queries the metadata allocator first. A missing handle
triggers the stack debug name (the 15-byte prefix at `4faf20`, with the class name
concatenated through `12a1e8` when non-null) and metadata factory `2be4f0`, then
publishes its result. Metadata factory success is a
caller/lower-service contract; there is no fallback.

Validity +36 uses independently observed bits: 1 inheritance attached, 2 class
configuration performed, 4 layout finalized, 8 registration in progress. An
already-busy entry returns zero without clearing another invocation's busy bit.
Otherwise the registrar sets busy, skips already-finalized work (returning zero), or
performs the missing inheritance/configuration/layout phases. It clears its own busy
bit at the end.

The phases nest. While bit 4 is clear and bit 2 is clear, inheritance runs first if
bit 1 is clear: the base registrar is called with the metadata and its result kept as
callback state, the base accessor supplies the parent, `2fdc50` attaches it and bit 1 is
set. Fresh configuration follows. Finalization then runs whenever bit 4 was clear, even
if configuration had already happened, and sets bit 4 as its last step.

Fresh configuration names the metadata, stores size/accessor/abstract state,
optionally calls the vtable getter and field adder, sets configured, assigns a
type ID and balances a temporary metadata reference. The field adder is called
without a defined argument; the original Work adder reads its own global handle.
When system words +100, +96 and +104 are all nonzero, it looks the class name up in the
+104 object through `30d350` and, unless that returns -1, calls the profile/stream helper
`2fe810` with the scratch output, metadata and system +96.
Layout finalization then runs, followed by metadata setup callback +76 if present.

The return is pending static-initializer callback state, rather than the class
metadata pointer. Base registration may supply that state; otherwise the registrar
allocates a twelve-byte callback container through `2ed240` and constructs it through
`2d3400`, even when there are no items. Dependency-list items append during
finalization, while argument 9 appends only when fresh configuration ran. Both
item values are explicitly passed to the append service `2d3480`.

## Inheritance and field creation

Inheritance (`2fdc50`) lazily constructs the parent's child container, appends the
child metadata and stores parent linkage. It copies vtable, alignment, runtime
prefix and declared size, then appends retained pointers for the parent's captured
field count. Parent metadata is not cloned and shared field records stay shared.

`igMetaObject_CreateFields` (`2fdf40`) iterates a constructor-address table with
the supplied signed count. Every iteration re-queries the metadata allocator,
invokes that field factory, appends a retained descriptor, and releases the
factory-owned reference. The original assumes a non-null factory result. `igMetaObject_AppendField` (`2fde50`) and the
retaining append at `2ead30` preserve the original tail-call behavior.

Internal field-pointer storage is accessed at buffer +8 / count +12. The matching
view deliberately does not use the generated reflected `igMetaFieldList` type,
whose declared member positions differ. These are observed ABI positions; the
internal container is now identified as reflection class `__internalObjectList`
through its original metadata constructor/factory chain; see
[metadata bootstrap](metadata-bootstrap.md). This does not establish an original
C++ declaration for that type.

## Field names, default storage and publication

`igMetaObject_NameFields` (`2fe000`) captures final count and uses its starting
index to select newly added descriptors while independently indexing parallel
name/handle/offset arrays from zero. For each field it configures the descriptor
and then finalizes/publishes it. The field buffer is re-read for subsequent rows.

Configuration (`2fc2c0`) interns a non-null name, retains/publishes it through the
real name helper (`2fc490`), balances its temporary, then stores external handle
address +28, member offset +8 and parent metadata +24. Default-storage ensure
(`2fc3b0`) calls virtual type-size slot 100, stores its low 16 bits, and allocates
missing storage. If the existing allocation's signed capacity is too small, it
releases and allocates again. It re-reads requested size and default pointer at
the original callback boundaries. The allocation's third argument is
one; no general allocator policy follows from it.

Descriptor finalization (`2fc630`) invokes slot 92, copies halfword +18 from a
non-null returned type record or stores -1 as type index, obtains low-16-bit size
again, invokes virtual default setter 140 with null source, and publishes the
field pointer through its external handle when present. The base default setter
(`2fc440`) ensures storage and copies `_size` bytes only for non-null source.
Storage allocation, type records, concrete field factories and interning remain
explicit lower dependencies here.

## Runtime-prefix layout

Layout finalization (`2fe0d0`) visits a captured field count through current
field-pointer storage, querying each field's low-16-bit alignment from slot 108.
It tracks maximum overall alignment (minimum four) and maximum ordinary-field
alignment (minimum four).

Ordinary fields receive internal index `ordinal - precedingRuntimeFieldCount`
and parent ownership when they are new rather than the same inherited pointer.
Runtime-only fields instead grow backward from zero: subtract size and apply
`offset &= ~(alignment - 1)`, then store that negative word offset. Required
alignment is published as a halfword. Unless declared size is -1, the runtime
prefix size becomes the negated backward offset rounded with ordinary-field
alignment. The declared-size sentinel preserves the prior prefix size.
Finalization sets validity bit 4 before notifying the object system.
The original also computes a local maximum field end without publishing it.
There is no alignment validation or clamping.

## Original Work class schema

The complete original `beMessengerWork_Register` (`3581f0`)
and `beMessengerWork_InitFields` (`358290`) follow this path. Registration supplies its
actual constant eleven-argument tuple, including field adder in stack slot zero.
The adder reads handle `588f88`, preserves inherited count, creates six fields
from table `4c5ce0`, sets the last two child-type references through original
getters `2caab0` / `36a0a0` and enables their construction. It then binds the
original name/handle/offset arrays at `4c5d00/4c5d20/4c5d40`.

The resulting names/offsets/handle publications agree with decoded
`data/reflection.json`: group name +8, information name +12, RAM number +16,
message +20, RAM-number list +24 and RAM-reference list +28. Registration leaves one
retained field reference and one name reference per descriptor, the two child
references and construction flags, validity 7 and size 32, and it is repeatable. It
does not establish complete live class bootstrap or instance creation.

## Validation and remaining work

Run from the repository root:

```sh
python3 testing/test_lua_engine_dependencies.py
make check
make typed-check
make link
```


Three new reviewed callback roots link Work registration, field addition and
vtable lookup to their actual literal argument sites. Independent retail argument
and table checks validate those roots; the inventory does not invent direct
and table checks validate those roots; the inventory does not invent direct
edges for generic indirect calls. Original base/type/vtable/field factories,
callback vectors, allocation, system/profile and interner primitives remain open.
Other messenger class schemas, concrete memory/array fields, full instance
composition and gameplay receivers remain required work. Full Lua-dependent engine
completion is not claimed.

[Object storage](object-storage.md) covers encoded lookup and the
allocation/free wrappers, [concrete factories](field-factories.md) the Work descriptor
factories, initializer chains and default hooks, and
[metadata bootstrap](metadata-bootstrap.md) the metadata factory/init, name and index
bodies and retaining registry insertion.

[Object base](object-base.md) registers `igObject` and its two manually generated
header descriptors before Work, so Work has eight total fields: those two and its six
own fields.

## Open questions

* Each of the fifteen 24-byte `<Library>Library_MarkRegistered` latches heads one library's block of classes, and
  every class registrar calls the latch of its own block first (303 for `BecLibrary_MarkRegistered`, 163 for
  `NdmwLibrary_MarkRegistered`). Nothing but the latch reads its `g_<Library>Library_registered` byte, so what the
  flag was for in the original libraries is not established.
