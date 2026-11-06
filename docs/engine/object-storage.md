# Object storage and encoded allocator selection

This recovery covers eleven complete behavioral bodies / 716 code bytes:
the contiguous helper run `300d30..301008` and its encoded-selector dependency
`2f0700`. [Guest-reference C](../../recovered/engine/object-storage.c) preserves
RAM, defined returns and callback ordering. Ten bodies / 640 bytes have exact
matching source; allocation-base recovery adds 52 bytes. Encoded lookup (76 bytes)
remains a compiler residual. Previously matched dispatch wrappers now explicitly
forward their object receiver and preserve allocation results.

## Header and lookup

`igObject_GetAllocator` (`301000`, 8 bytes) loads the unsigned byte at object +7
in the original tail-transfer delay slot and passes it to
`igAllocator_ResolveEncodedIndex` (`2f0700`, 76 bytes). The selector tests low bit:
zero selects the pointer at `586f58`, one selects `586f60`. It dereferences that
pointer to obtain a table and indexes by the signed input shifted right one.
The selected table word is returned. Ordinary object callers supply only 0..255;
the selector itself neither masks to a byte nor bounds-checks its signed input.
The tables' population and allocator virtual implementations remain dependencies.

`igObject_GetAllocationBase` (`300d30`, 52 bytes) queries the current object
metadata through vtable byte slot 88, then subtracts metadata runtime-prefix size
+32 from the object address. The exact C++ view uses the recovered
`igMetaObject::_runTimeSize` field; its virtual declaration is an observed ABI
projection and must not be instantiated.

## Dispatch helpers

Every allocation helper first reselects the allocator through the object header,
then invokes its current vtable, forwarding the original arguments unchanged:

| Entry | Allocator byte slot | Arguments after receiver |
| --- | --- | --- |
| `300d70` (`igObject_AllocateStorage`) | 216 | one |
| `300db0` | 220 | two |
| `300e00` | 224 | two |
| `300e50` | 232 | two |
| `300ea0` | 236 | three |

The registration default-storage path calls `300e00(field, size, 1)`. This does
not establish the general meanings of all overload arguments; uncertain overload
names remain address symbols. Matching wrappers formerly declared void or omitted
the receiver at the allocator lookup. Those ABI declarations are corrected without
changing their verified bytes.

`300f00` (`igObject_FreeStorage`) and `300f50` are identical instruction bodies:
a null storage argument returns without allocator lookup; a non-null argument
selects the allocator and invokes slot 264 with the storage pointer. Their
original API distinction is not established; the second keeps its address name.
Their physical integer return register is not a defined result.

`igObject_DuplicateString` (`300fa0`, 84 bytes) measures the source via `12a78c`,
allocates length plus one through `300d70`, copies via `12a5fc`, and returns the
allocation. The original does not add null-input or allocation-failure handling.
Allocator selection occurs after length evaluation, so a changed object header
at that callback boundary takes effect.

## Verification and composition

Run from the repository root:

```sh
python3 testing/test_object_storage_retail.py
python3 testing/test_reflection_registration_retail.py --object-storage
make check
make link
make typed-check
```

The storage oracle passes **726 original-instruction RAM/defined-return/ordered-call
cases** across all eleven bodies. It checks all 256 header codes, negative direct
selector inputs, runtime-prefix wraparound, zero/large sizes, exact virtual slots
and arguments, null frees, empty/long string duplication and header mutation during
length measurement. Allocator virtual services and libc byte operations remain
controlled. Tail mediation executes the actual byte-load delay slot and original
selector instructions.

The registration oracle additionally passes **487 cases** with actual encoded
lookup, object allocator selection and default allocation/free wrappers composed
underneath descriptor registration. It asserts that all four storage entries
execute and compares original-instruction memory and callback traces. Concrete
allocator virtual methods, capacity queries, factories, interning, type records,
callback vectors and system services remain controlled. This removes the wrapper
boundary, not the full allocator or metadata-bootstrap boundary. Native gameplay
is unchanged; other Lua-dependent engine modules remain required work.
