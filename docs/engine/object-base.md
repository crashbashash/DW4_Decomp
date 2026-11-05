# Original igObject bootstrap and inherited header fields

Finding [#884](../findings/findings-0751-1000.md#f884) records **13 complete bodies / 1,144 code bytes**: ten bootstrap,
publication and descriptor-attachment bodies in
[object-base.c](../../recovered/engine/object-base.c), plus the unsigned descriptor
factory/constructor/initializer now included in
[field-factories.c](../../recovered/engine/field-factories.c).
All thirteen bodies / 1,144 bytes have exact matching source. Vtable lookup (48) is in
[igObject_GetVTable.c](../../src/unmatched/igObject_GetVTable.c) and manual field initialization (540) in
[igObject_InitFields.c](../../src/unmatched/igObject_InitFields.c).

Five new matching functions add **104 bytes**: empty initializer callbacks 60,
registration forwarding 12, and three newly classified leaf callbacks totaling 32.
The reviewed callback leaves were previously unclaimed data words. Their exact
instructions and registrar argument sites are checked before creating functions
in the analysed Ghidra project through
[the reproducible recovery script](../../scripts/recover_object_base_callbacks.py).
Function/symbol snapshots are regenerated with the existing dump scripts, without
analysis. Classified code increases by 32 bytes and the function denominator by 3;
the retail image and linked-section size are unchanged.

## Registrar and callback interfaces

`igObject_Register` (`2ff4f0`, 100) forwards the complete eleven-argument tuple to
`igMetaObject_RegisterClass`:

| Argument | Value |
| --- | --- |
| abstract state | 0 |
| published handle | `587198` |
| base callback registrar | `2ff460` |
| null parent metadata accessor | `2ff4a0` |
| own metadata accessor | `2ff560` |
| name | original `igObject` string at `4faf30` |
| instance size | 8 |
| vtable getter | `2ff4b0` |
| field adder | `2ff570` |
| extra callback / dependency list | zero / zero |

The existing matching wrapper now explicitly returns shared registration's callback
state. `igObject_EnsureRegistered` (`2ff4e0`, 12) forwards this registrar to the
original static initializer runner. Its entry has no new idempotence policy; the
shared registrar's validity flags govern repetition.

The nominal base callback registrar at `2ff460` (60) queries allocator key
`587040`, allocates twelve bytes and constructs the callback container when the
allocation is non-null. It returns that container or zero. It does not recursively
register another class. `2ff4a0` (8) returns null parent metadata.

The accessors at `135530`, `155b80` and `2ff560` (12 each) all return the current
word at `587198`, without lazy allocation. Their distinct roles are respectively
Work's parent accessor, base object vtable byte slot 88, and the base registrar's
own `_getMetaObjectFunction` callback. The first and last, plus the null parent
callback, are the newly classified leaves. No original C++ declaration spelling
is claimed by these ABI projections.

`igObject_GetVTable` (`2ff4b0`, 48) initializes a temporary eight-byte object header,
then reads its table word through the object-system offset at +916. The adapter
reserves 320 scratch bytes for that header, naming temporaries and shared class
registration. Tests compare the defined result and normalized temporary arguments;
unobservable stack bytes are excluded.

## Two manually registered header descriptors

The extracted static reflection table reports no own fields for `igObject` because
this field adder constructs descriptors directly rather than consuming the usual
parallel tables. **The runtime base metadata has two fields.** This is required
by the generic instance field loops' starting index; using an empty synthetic base
loses that real inherited prefix.

`igObject_InitFields` (`2ff570`, 540) performs two original construction/binding
sequences:

| Name literal | Published descriptor handle | Word offset |
| --- | --- | --- |
| `_refCount` (`4faf40`) | `5871a0` | 4 |
| `_memPoolIndex` (`4faf50`) | `5871a8` | 4 |

Each sequence re-queries the metadata allocator, invokes the unsigned integer
field factory, writes offset/publication address, interns and retains the original
name through the shared helper, balances the temporary token, clears persistence
and sets reset method3. It then finalizes/appends the descriptor to the current
published base metadata and releases the factory-owned reference. The global
metadata handle is re-read at the original attachment boundary.

`igMetaObject_FinalizeAndAppendField` (`2fde60`, 64) runs descriptor finalization,
then retaining append. It does not supply the parent's name/offset configuration
on its own. Shared layout finalization subsequently supplies parent/index fields.
The two header descriptors expose the containing word at +4; this does not turn
`_memPoolIndex` into a separate stored 32-bit member. Actual header operations still
use packed reference bits and byte +7 as recovered elsewhere.

The required unsigned field factory (`2b6d20`, 160) follows the same runtime vs
cold bootstrap switch as the other concrete descriptor factories. Its class
handle is `585738`, size 52, constructor `30e8e0` (64), initializer `30e920` (52),
and concrete vtable `533430`. Constructor and initializer delegate to the actual
base metadata field routines and stamp that vtable. They introduce no extra
value flags. All three existing exact bodies are named/folded with explicit
interfaces; this extension does not itself add matched bytes.

## Verification and integration

```sh
python3 testing/test_object_base_retail.py
python3 testing/test_field_factories_retail.py
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

**33 original-instruction RAM/defined-return/ordered-call checkpoints** cover all
ten base bodies and execute the unsigned constructor chain. They include all
published-accessor aliases, null parent, empty callback allocation/failure,
header-offset getter behavior, cold/repeated registration and initializer-runner
entry, direct field addition/publication, and original Work registration after
the real base class is registered.

Assertions prove two base descriptors, their real names/handles/offsets,
non-persistence/reset flags, unsigned vtables, size 8 and valid base metadata.
Work registration then has **eight total fields**: two shared inherited header
descriptors and six own descriptors at offsets 8/12/16/20/24/28, with internal
indexes 2..7. Header descriptor counts become two; own descriptors retain one
reference. Base/Work metadata each retain one registry-owned reference, with
registry indexes 0/1 and Work size 32. Repeat registration creates no extra fields.

The extended concrete-factory oracle passes **306 cases across 21 bodies**. Twelve
dependency regressions independently check the classified leaf words, registrar
literals and base vtable, supporting eight explicit callback roots without
inventing direct edges through generic dispatch.

Allocator, interner, type queries, callback-vector storage/cleanup, the parent's
child-list factory and Work's child-type metadata remain controlled boundaries.
This proves original base/Work metadata and field construction, not complete live
Work instance creation. Next dependencies include real `igIntList` metadata at
`586880`, `beBaseInfoRamList` metadata at `589d20`, their inherited storage fields,
and remaining type/allocator services. Native gameplay is unchanged.
