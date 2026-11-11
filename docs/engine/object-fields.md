# Object field cleanup, persistence and reference ownership

Three separate [reference helpers used by the combat callback](../systems/combat-reference-helpers.md)
total 316 bytes. They share the packed low-23-bit destruction
rule; their original template/type identities remain unknown.

Fourteen complete bodies (1,676 code bytes) are covered here: the contiguous four-body
cleanup/persistence run at `2ffc10..2fff90`, concrete reference assignment and
construction/destruction/reset, shared zero/clear helpers, construct-flag and
metadata count/index getters.

Eight reference-field bodies (748 bytes): the object-reference assign, size, construct,
destruct and slot-34 bodies are in [igObjectRefMetaField_tail.inc](../../src/engine/core/igObjectRefMetaField_tail.inc),
and the plain reference zero, clear and construct-test bodies in
[igRefMetaField_tail.inc](../../src/engine/core/igRefMetaField_tail.inc), both
using reflected receiver fields and explicitly documented header/virtual-slot ABI
views. The metadata count and
index getters, in [igMetaObject_tail.inc](../../src/engine/core/igMetaObject_tail.inc), are 36 bytes.
The four generic cleanup/persistence bodies, `2ffc10`, `2ffcb0`, `2ffd40` and
`igObject_WritePersistentFields` (`2ffe10`, 384 bytes), are in one-function files
under `src/unmatched/`.

## Generic cleanup and field-table traversal

`igObject_DestructFieldValues` (`2ffc10`) calls object virtual slot 16 before
obtaining current metadata through slot 88. It captures the type's field count
and the base-field count from global `587198`, then visits non-base fields in
increasing index order through field virtual slot 128 (destruct value).
`igObject_ClearFieldValues` (`2ffcb0`) performs a separate traversal through slot
136 (clear/reset storage), without the leading object hook.

Both passes capture counts but re-read the pointer buffer before each callback.
The first hook can change the object's vtable before metadata lookup. Count and
buffer mutation during field callbacks preserve the original iteration bound and
new buffer accesses. These passes are distinct: the concrete object-reference
clear override may release a reference depending on its own flag before zeroing;
cleanup is not one generic host memset operation.

## Concrete object-reference fields

Reflection names `_offset` (+8), `_construct` (+52), `_destruct` (+53),
`_metaObject` (+56), `_refCounted` (+60), and `_poolName` (+64). Original accesses
and the `igObjectRefMetaField` vtable independently establish the operations:

| Address | Operation |
| --- | --- |
| `303390` | Assign a reference into `instance + _offset` |
| `303450` | Return reference storage size four |
| `303540` | Conditionally create and assign an instance of `_metaObject` |
| `303620` | Release the stored reference only when `_destruct` is nonzero |
| `303680` | Canonical `igObjectRefMetaField::vfunc_34`: release when `_refCounted`, then clear storage |
| `305500` | Zero storage using the low 16 bits of virtual type size |
| `305540` | Separate clear-slot body with the same byte-fill algorithm |
| `305cd0` | Return the one-byte `_construct` flag |

Assignment captures the old reference before checking flags. When either
`_refCounted` or `_destruct` is nonzero it retains the replacement before releasing
the old value. It then re-reads `_offset` for publication; a destructor callback
can change the destination member. Self-assignment balances retain/release.
Reference destruction uses the low 23 bits of the full header word at object +4.

Construction skips when `_construct` is zero. Otherwise a nonempty `_poolName`
uses named allocator lookup, falling back to the enclosing instance's allocator
on a missing result; an absent/empty name directly uses that enclosing allocator.
It creates `_metaObject` through the shared creation path, assigns it
through the actual reference setter and balances the temporary factory reference
when either ownership flag is set. Flags are re-read after assignment. There is no
allocation-failure or alias check.

Destruction alone does not clear the member. Clear/reset releases according to
`_refCounted` and then computes its zeroing destination. The shared zero/clear
helpers capture that destination before virtual type-size lookup; a size callback
changing `_offset` does not move this particular fill. Their size is truncated to
16 bits exactly as in the original code. The matching structural virtual-slot
view declares ABI positions and must not be instantiated; it is not a recovered
original C++ inheritance declaration.

The `_construct`, `_destruct` and `_refCounted` flags are independently observed
conditions. They do not collapse into a single ownership rule, and not every
combination is known to occur in retail class descriptors.

## Persistence size and write behavior

`igObject_GetSerializedSize` (`2ffd40`) obtains metadata, follows its `_writeProxy`
(+64) when present, and returns zero if the resulting `_persistent` byte (+25)
is zero. Otherwise it starts at eight bytes and sums field slot 196 results for
non-base fields, retaining original word arithmetic. The field callbacks decide
their own contribution; this layer does not add a persistence filter to size.

`igObject_WritePersistentFields` (`2ffe10`) first checks the original metadata's
persistent byte, then calls object slot 56 and follows its write proxy. It does
not repeat that original guard after the hook/proxy. It writes an optional
context-resolved type identifier and the separately computed serialized size as
two header words. When byte-swap is requested, the original unsigned-int field
provider's slot 208 processes those two words.

The writer visits non-base fields whose `_persistent` byte is **exactly one**
and `_isRunTime` byte is zero. It calls the existing field-write dispatcher and
advances by its returned byte count. It recomputes and returns serialized size
at the end rather than returning the output cursor distance. Header size, final size
and bytes written can therefore differ when callbacks change size contributions during
writing or persistence during the pre-write hook.

## Validation and remaining work

Run from the repository root:

```sh
make check
make typed-check
make link
```

With `_construct=1`, `_destruct=1` and `_refCounted=0`, a parent's final release through
[object destruction](object-creation.md) frees each owned child once and zeroes the
parent's slots.

The original messenger class field tables are not established. Original
registrar/descriptor recovery remains necessary. Serialization
helpers, concrete string/memory fields and broader Lua gameplay receivers also
remain open. These verified families do not establish complete Lua-dependent engine recovery.

Six reviewed virtual roots are now listed in `config/SLUS-20836/lua-dependency-roots.tsv`:
size, construct, destruct, zero, clear/reset and construct-flag entries from the
`igObjectRefMetaField` vtable at `532c80`. Messenger Work/ArgData field-constructor
records identify this concrete MetaField class in `data/reflection.json`; the
vtable snapshot establishes their entry addresses. The inventory treats them as
explicit evidenced roots, not invented direct edges from generic virtual calls.
Original runtime class-descriptor construction still requires further recovery.

[String fields](string-fields.md) cover scalar string ownership and raw codecs plus
common reset/write dispatch; original runtime class descriptors
remain a separate recovery requirement.
