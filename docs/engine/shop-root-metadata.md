# Generic shop-root factory and metadata

The complete contiguous six-body **3b8d90..3b8f4c** `beNDMWShopCtrl00` metadata block
(404 code bytes) and its 12-byte published parent accessor at 3b65b0 are recovered:
**104 instruction addresses** across the seven bodies /416 bytes.

All seven bodies /416 bytes have exact source. The 76-byte lazy
accessor uses the existing project padding convention. Four /212 bytes were already matched:
the factory52 and registration wrapper32 were under anonymous `FUN_` names,
alongside Register100 and GetMetaObject28. They are named and their return/callback
ABIs corrected with no additional matching credit. The newly classified parent
getter contributes **one function /12 matched bytes**. The vtable getter116 matches in [beNDMWShopCtrl00_GetVTable.cpp](../../src/unmatched/beNDMWShopCtrl00_GetVTable.cpp).
This is metadata recovery, not working shop transactions.

## Factory and published metadata

SUBWND's lifecycle calls factory3b8d90 at3d5ba0 for modes1,3–9. The factory first
calls EnsureRegistered3b8ea0, then reads the **current** published handle58ae30
and calls `igMetaObject_CreateInstance` with that metadata and the original
allocator. It does not directly call a C++ shop constructor or replace shared
allocation/metadata behavior. The returned instance address is forwarded.

ResolveMetaObject3b8dd0 reads the same handle. A null pointer, or a non-null
metadata `_validity` word36 without bit4, calls EnsureRegistered. It returns the
handle reloaded after that callback; the callback may publish a different object.
It does not assume registration succeeded or force another validity check.
GetMetaObject3b8f30 simply forwards that result. EnsureRegistered supplies the
original registrar callback to `igMetaObject_RunStaticInit`; the shared runner
and registrar own repetition/validity policy.

The published parent accessor3b65b0 returns the current word58b010 directly.
It does not register or resolve the parent. The registrar's literal argument3
points to this three-instruction body. It was previously unclaimed data;
[scripts/recover_shop_root_callback.py](../../scripts/recover_shop_root_callback.py)
checks the exact leaf words and registrar argument instructions, rejects overlaps,
creates the function transactionally in the analyzed Ghidra project, and is
idempotent. Function/symbol snapshots are regenerated without analysis. This
adds12 classified code bytes and one function without changing any image bytes.

The descriptive Create/ResolveMetaObject/EnsureRegistered/GetPublishedMetaObject
names come from body and registrar evidence through the
[name generator](../../scripts/seed_names_shop_root_metadata.py). They do not claim
original C++ method spellings. Existing reflection-owned names are retained.

## Registrar contract and parent class

Register3b8ec0 first invokes the shared registration preamble3b0a10, then forwards
this full eleven-argument tuple to `igMetaObject_RegisterClass`:

| Argument | Value / meaning |
| --- | --- |
| 0 | 0, concrete metadata |
| 1 | 58ae30, published ShopCtrl00 handle |
| 2 | 3bb630, base `beNDMWWindowCtrl` registrar |
| 3 | 3b65b0, published WindowCtrl metadata accessor |
| 4 | 3b8f30, own metadata accessor |
| 5 | 5115a0, original class name `beNDMWShopCtrl00` |
| 6 | 84, declared instance size |
| 7 | 3b8e20, vtable getter |
| 8–10 | Zero: no own field-adder or extra callback vector |

The first eight arguments use EE registers; the remaining three are64-bit stack
slots0/8/16. The
registrar returns the shared callback-state address rather than discarding it;
the corrected C signature retains exact original bytes.

The [shared registrar contract](reflection-registration.md) establishes that
arguments2/3 are base registrar/accessor. In particular **3bb630 is not an instance
constructor**. The earlier private handoff used that incorrect label; source and
tracked documentation here follow the actual registration contract. Reflection
records no own ShopCtrl00 fields and identifies WindowCtrl as its parent. WindowCtrl
has inherited window fields plus `_nowProcKazu`80. Its own field-adder remains a
separate dependency, not a shop-root transaction implementation.

## Temporary vtable object

GetVTable3b8e20 uses a128-byte private frame with a temporary object at32. It calls
`igObject_InitHeader`, captures the object-system pointer at586dc8, clears the
seven inherited reference cells at object52..76, and publishes vtable53feb0.
The reference fields are `_subWindow`, `_mother`, `_textCloseTypeList`,
`_textCloseNameList`, `_modelCloseInfoNameList`, `_modelCloseRamNoList` and
`_modelCloseSeqNameList` from `beNDMWWindow` reflection.

It reads the result through the captured system's byte offset916 into the
temporary, republishes53feb0 and invokes [cleanup3b6430(temporary,0)](window-object-lifetime.md). The captured
result is returned even if cleanup changes the same temporary cell. Uninitialized
non-reference fields are not zeroed. Header construction and cleanup are separate
services.

The ordinary vtable at53feb0 has the two-word RTTI header. Its raw byte92
contains update4267b0 (RTTI-array vfunc index21); tree update3f6490 loads byte92
at3f64bc and calls it at3f64c0. This gives a concrete next runtime dependency.
Do not mix these raw offsets with header-free GetVTable-slot numbering.

## Evidence and remaining matching work

```sh
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

The lazy76-byte body now matches with one explicit retail padding NOP and a
label preserving the null branch's direct entry at the registration call. The
non-null/not-ready path executes the NOP. This follows the existing matching convention,
without claiming the original C++ source spelling. The116-byte vtable getter matches in
[beNDMWShopCtrl00_GetVTable.cpp](../../src/unmatched/beNDMWShopCtrl00_GetVTable.cpp). No opaque assembly replacement body is used. The matched accessor retains its
original no-op within readable C++ under the established project convention.

The116 metadata bytes and the six bodies of the
[root runtime and common window tree](window-tree-and-shop-root.md)
match. Continue with actual shop
subcontrollers, price/item services and transaction results. The
[full hub goal](../systems/hub-recovery.md), dedicated LABO/CARD roots and separate
Save Keeper stagIS12 route remain open.

A separate 192 exact bytes cover that complete base-controller
cleanup dependency. Its seven member helper calls and signed deletion flag are
readable source; it contains one explicit return-register copy and original NOP.
The seven-body metadata accounting above is416/416 exact bytes: the new
cleanup body is outside that block. Header and member-cell services remain open boundaries.
