# Object storage and encoded allocator selection

This page covers eleven complete bodies / 716 code bytes:
the contiguous helper run `300d30..301008` and its encoded-selector dependency
`2f0700`. Dispatch wrappers forward their object receiver and preserve allocation results.

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

## Verification and remaining work

Run from the repository root:

```sh
make check
make link
make typed-check
```

Concrete allocator virtual methods, capacity queries, factories, interning, type
records, callback vectors and system services lie below these wrappers and remain
separate work, as do other Lua-dependent engine modules.
