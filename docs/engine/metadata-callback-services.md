# Metadata lookup and deferred callback services

Six complete bodies / **568 code bytes** all have matching
source. Four new exact functions add **468 bytes**: string-field lookup 160,
metadata name lookup 20, callback-array destruction 96 and append 192. Constructor 20
and finalize/replace 80 retain existing matches with explicit interfaces.

## Corrected string-field lookup

The interpretation of `2ea780` as a list of byte offsets into another object's
buffer is **refuted**. Actual list-specialization callbacks pass a field
selector through `igMetaObject_FindFieldByName` (`2fdf20`, 20). That wrapper loads
global descriptor `585cd8`, independently identified in reflection as
`igMetaField::_fieldName` with member offset 12, and passes the metadata field list
plus selector plus query string to `2ea780`.

The correct role is **`ObjectPointerList_FindByStringField`**. Each list entry is
an object pointer. The selector's `_offset` word at +8 selects a pointer-valued
string member inside each object. The routine compares that string and returns
the current matching object pointer, or zero. Count is re-read each iteration and
the selected object pointer is re-read after comparison callbacks. It does not
retain its result.

The 160-byte routine is in
[list-string-field-find.c](../../src/engine/list-string-field-find.c).

`igMetaObject_FinalizeAndReplaceField` (`2fdea0`, 80) finalizes the incoming
descriptor, then invokes retaining replacement in the current metadata field list.
The callee retains new/releases old before its final store. The wrapper does not
release the incoming factory/clone-owned reference; its caller does that. Real
`igIntList` and `igObjectList` specialization callbacks call both helpers to locate
and replace inherited `_data` descriptors. Their whole callback bodies and copy
protocol remain recovery work.

## Three-word callback array

This array is a distinct twelve-byte ABI, without an object header:

| Offset | Meaning |
| --- | --- |
| 0 | data pointer |
| 4 | count |
| 8 | capacity |

`igArray_Construct` (`2d3400`, 20) clears data, capacity and count and returns its
receiver. `igArray_Destruct` (`2d3420`, 96) handles a null receiver, frees non-null
data through `2ed460`, and deletes the container through `2ed5c0` only when the
captured flag's signed low 16 bits are positive. It returns the original address
in `v0` and does not clear the stored members. That return is not a guarantee of
usable storage after deletion.

`igArray_Append` (`2d3480`, 192) grows only when count **equals** capacity. The
initial capacity is four. For nonzero capacity the original arithmetic is:

```
triple = wrap32(capacity * 3)
capacity = wrap32(capacity * trunc_toward_zero(triple / 2))
```

Thus ordinary capacities advance **4 -> 24 -> 864**. This is not a conventional
1.5-times growth rule. The multiply at `2d34d0` in the original words confirms
the formula: the arithmetic wraps at 32 bits and the division is signed.

A missing buffer allocates capacity times four bytes through `2ed240`, using the
allocator read from object system +52. An existing buffer reallocates through
`2ed330`. The returned buffer is published; count is then re-read and incremented
before the item is written at its prior index. Allocation callbacks can change
that index through count mutation. A count greater than capacity does not trigger
growth. There is no allocation-failure fallback.

## Verification and remaining work

```sh
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

Replacing an inherited Work descriptor leaves the parent's retained original in place,
with old and new ownership balanced by the retaining replacement.

The initializer runner, on Work's original registration, dispatches the dependency entries
`2cab90` and `36a180` in order before array cleanup. That establishes their dispatch,
not completed `igIntList` or `beBaseInfoRamList` registration.

Thirteen dependency regressions independently connect selector metadata, wrapper
instructions, specialization call sites and original registrar callback literals,
plus the original Work dependency table. Two reviewed helper roots expose this
path without inventing generic indirect-call edges.

[Descriptor copy](list-descriptor-copy.md) covers both native
specialization bodies and the complete cold memory-descriptor copy chain. The
full child registrar/inherited schema and element-provider paths remain open.
