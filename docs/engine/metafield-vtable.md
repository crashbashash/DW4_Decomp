# MetaField vtables

The slot layout of the `igMetaField` family's vtables, and the base bodies behind each slot.

## Anchor vtables

| Class | Vtable |
| --- | --- |
| `igMetaField` | `0x52f230` |
| `igRefMetaField` | `0x52ec50` |
| `igMemoryRefMetaField` | `0x532a50` |
| `igMemoryRefArrayMetaField` | `0x52f330` |
| `igMetaObject` | `0x532bb0` |
| `igMemoryPoolInfo` | `0x52f430` |
| `igMemoryPoolInfoList` | `0x5329e0` |

MetaField subclasses inherit the base bodies through their own tables, so one address sits at the same
slot in dozens of vtables (`0x2fc210` at +0x08, `0x2fc440` at +0x8c, `0x2fd090` at +0xa4).

## Slot map

The field vtables are 0x100 bytes: +0x08..+0x54 is the embedded `igObject` interface and +0x58..+0xf0 is
`igMetaField`'s own. The offsets here are bytes; other documents give them in decimal (slot112 = +0x70).

| Slot | Role |
| --- | --- |
| +0x64 | The field's byte size. `igMetaField_FinalizeDescriptor` (`0x2fc630`) stores its result in `_size` (+0x14) and `igMetaField_AllocateArray` divides an allocation by the same slot on `_memType`. The base returns 0, `igRefMetaField` and `igMemoryRefMetaField` return 4, and `igMemoryRefArrayMetaField` returns `(_num*4) & 0xffff` |
| +0x6c | Not an alignment: base `0x2fc2a0` returns -1, refs return 4, and a caller at `0x2f0bc0` uses the result as a predicate |
| +0x70, +0x74, +0x78 | The reset techniques. `igMetaField_Reset` maps `_resetMethod` 0, 3, 2 to them; the base +0x74 is a no-op |
| +0x7c, +0x80 | Construct and destruct the value in place |
| +0x84, +0x88 | Zero the value |
| +0x8c | SetDefault |
| +0x90..+0xa0 | The copy techniques `igMetaField_CopyByTechnique` selects by number 0..4 |
| +0xa4 | Print |
| +0xa8 | The callback-driven object traversal, despite its `ReleaseElements` name |
| +0xac | Write (base: 0 when `_persistent`, else -1) |
| +0xb4..+0xc0 | The alike techniques 0..3 |
| +0xc8 | WriteRawFieldMem |
| +0xcc | ReadRawFieldMem |
| +0xd0 | `igMetaField_SwapBytes` (`0x2fd170`): byte-reverses each `_size`-byte element, the endian conversion the raw-field transfers run on the destination |
| +0xd4 | `igMetaField_SwapValue`: applies +0xd0 in place at instance + `_offset` |

## Entry thunks

`igMetaField_ShallowCopy`/`DeepCopy`/`ConstructCopy` (`0x2fc9a0`/`0x2fc9b0`/`0x2fc9c0`) are 8-byte thunks
that load `_shallowCopyMethod`/`_deepCopyMethod`/`_constructCopyMethod` (+0x27/+0x28/+0x29) into `a3` and
jump to `igMetaField_CopyByTechnique`. The `IsAlike` thunks (`0x2fcf60/70/80`) do the same with
+0x2a/+0x2b/+0x2c and `igMetaField_IsAlikeByTechnique`.

`igMemoryRefMetaField_Init` sets `_resetMethod` 3, `_refCounted` 1, `_releaseOnReset` 1, `_releaseOnCopy` 1,
`_alignmentType` -1 and `_shallowCopyMethod` 2, so its shallow copy selects +0x98 and its deep and
construct copies +0x90.

## Raw field transfers

The engine's own name for +0xc8 survives in the log format at `0x4fafd0`. +0xc8 and +0xcc both take
(field, field memory, stream) and differ only in direction: the base +0xc8 (`0x2fc830`) copies field to
stream, the base +0xcc (`0x2fc7c0`) stream to field.

The reference overrides convert between a pointer and a directory index: `0x305620` writes the index, or
`0xffffffff` when the object is not in the output directory, and `0x2fb690` reads the index, installs the
resolved pointer and learns `_memType` (+0x3c) from the resolved object's +0x24. Both then run the +0xd0
hook on the destination.

## Open questions

- **The `igObject` vtable** (`0x52f0f0`, stored by `igObject_InitHeader`). An unproven reading: it looks
  like a repeated interface block, with `vfunc_00..vfunc_19` at slots 2..21 (+0x08..+0x54), again at
  26..45 (+0x68..+0xb4), 54..73 and 74..93, and per-interface tail slots between. The type-system code's
  virtual calls appear to decode against it: +0x68 and +0xd8 as `vfunc_00` (a size or allocate call),
  +0xe0 as `vfunc_02`, +0xe4 as `vfunc_03`, +0x108 as `vfunc_12` (release). Each class's `GetVTable`
  overrides the table with its own. Worth confirming, because running object methods depends on this
  layout.
- **`0x2bf4c0` and `0x2bf5e0`** look like the `igMemoryRefMetaField` and `igRefMetaField` destructor chains:
  they store `0x532a50`/`0x52ec50`, then `0x52f230`, and release the class's ref-counted fields. But those
  classes' +0x08 slots go through `0x2fba20` -> `0x305cc0` -> `igMetaField_Destruct` instead. Until that
  discrepancy is resolved they stay unnamed.
- **The caller of `igMemoryRefMetaField_SetToDefault`** (+0x70, `0x2facc0`) is not identified.
  `igMemoryRefMetaField_Init` sets `_resetMethod` 3, which `igMetaField_Reset` sends to the no-op +0x74, so
  it must be reached by a direct slot dispatch.
- **`0x2fa700`**, the array's +0xd0, passes elemSize*_num to the global field `0x585d88`'s own +0xd0, which
  does not fit the base body's fixed `_size`. Its meaning is open.
- **Slots without a pinned role.** A virtual is identified by its slot, not its body: when one class's
  entry at +0xNN is named, the same slot elsewhere is the same virtual. These slots have no role name:
  - The copy and alike techniques. Their method names are already taken by the entry thunks, and they are
    selected by number: +0x90/+0x94/+0x98 are byte-identical memcpys (`0x2fc9d0`/`0x2fca10`/`0x2fc9f0`),
    +0x9c jumps to Reset, +0xa0 is a no-op, +0xb4 is a byte compare over `_size` (`0x2fcf90`), +0xb8/+0xbc
    tail-call +0xb4, and +0xc0 returns 1.
  - +0x5c (`0x2fc620`, returns the global `0x587190`).
  - +0x60 (`0x2fd130`, copies a value into the instance).
  - +0xc4 (`0x2fc8a0`, `(_size + 3) & ~3` when `_persistent && !_isRunTime`, else 0).
  - +0xd8..+0xec, where +0xe8/+0xec loop over +0xe4/+0xe0 but the direction of +0xe0/+0xe4 is unproven.
