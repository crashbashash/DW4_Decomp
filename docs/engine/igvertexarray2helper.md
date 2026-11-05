# `igVertexArray2Helper` — the vertex-array accessor/binder

`Gap::Core::igVertexArray2Helper` is the Intrinsic Alchemy class that *binds* an
`igVertexArray2` to a typed view: it looks up a named vertex-data stream inside the
array and reads or writes its elements. It sits in the Alchemy graphics core
(`0x0015ff10`–`0x00164870`, the `0x141000`–`0x1f0000` region of `module-map.md`).

Status: **8 units are banked byte-identical** — the reflection pair
(`igVertexArray2Helper_Register`, `igVertexArray2Helper_GetMetaObject`) and vtable
slots 22, 24, 25, 27, 55, 57. The rest are reconstructed to the nearest source
spelling but blocked by two measured MWCC code-generation walls (below), so they are
**fail-closed** — the drafts stay in `build/m2c/`, nothing guessed is committed.
Findings **[#656](../findings/findings-0501-0750.md#f656)–[#658](../findings/findings-0501-0750.md#f658)**.

## Identity and layout

| | |
|---|---|
| Class metaobject handle | `0x0055f9d0` (`DAT_0055f9d0[0]` is the MetaObject returned by slot 22) |
| vtable | `0x005262a0`, stamped by `igVertexArray2Helper_GetVTable` (`0x0014a560`) |
| Base | `igNamedObject` (`data/class-hierarchy.tsv`); no `__RTTI__` record, so the class name comes from the `GetVTable` function (finding [#368](../findings/findings-0251-0500.md#f368)'s rule) |
| Reflected fields | **one**: `+0x0c _vertexArray` (`igObjectRefMetaField`) — the `igVertexArray2` it binds |
| vtable slots | 62 (0–61): 0/1 null (MWCC's two reserved slots), 2–21 the inherited `igObject`/`igNamedObject` defaults, **22–61 the class's own methods** |

The data classes it reads (all from `data/reflection.json`):

```
igVertexArray2  (0x55f9e0, igNamedObject)   +0x0c _internalBuffer  +0x10 _objList  +0x14 _vertexStream
igVertexData    (0x55fa58, igNamedObject)   +0x0c _data  +0x10 _componentType  +0x14 _componentIndex
                                            +0x18 _componentSize  +0x1c _userID  +0x20 _componentFraction
igVertexStream  (0x55fa10, igNamedObject)   +0x0c _stream  +0x10 _isConfigured  +0x14 _vertexDataList
                                            +0x18 _accessMode  +0x1c _primitive  +0x20 _streamMode
```

## The stream lookup

Every accessor reaches its data through one helper, `FUN_0015f580(va, componentType,
componentIndex)` — a *method of `igVertexArray2`* (it reads `va->_objList` at `+0x10`):

1. `count = va->_objList->_count` (the `igObjectList`'s `+8`);
2. for each element (array at `va->_objList + 0x10`): dynamic-cast the element to
   `igVertexData` (class check `FUN_00300cd0(elem, igVertexData_meta)`, handle
   `0x55fa58`);
3. return the first element whose `_componentType == componentType && _componentIndex
   == componentIndex`; else `0`.

`FUN_0015f580` is called by **38 functions** inside and outside this module, so it is
the shared `igVertexArray2` stream accessor, not a static of the helper class.

Two sibling helpers dispatch on the *class of the data object* and return its
component count/stride:

* `FUN_00162b50(vd)` — called only by slot 24. It calls
  `vd->_data->GetMetaObject()` (slot 22 of the list class) and compares it against
  `igFloatList`, `igLongList`, `igUnsignedCharList`, `igShortList`,
  `igUnsignedShortList` (each → returns `vd->_componentSize`, `vd + 0x18`) then
  `igVec2fList` → 2, `igVec3fList` → 3, `igVec4ucList` → 4, else 0.
* `FUN_00162ca0(vd)` — called by slots 25 and `FUN_001805a0`; same shape, fewer
  classes.

`FUN_00163770` / `FUN_00163800` are private helpers called only from slot 61.

## Slot map (22–61)

`comp` is the `componentType` constant in the retail body (`li a1,N`); the list class
is the class-check target. Get/set/pointer roles follow from the body shape (retail
stride `arg*4` or `arg*8` into the list's `+0x10` array).

| slot | VA | size | comp | list class | role |
|---|---|---|---|---|---|
| 22 | `0x00180e30` | 8 | — | — | **banked** — `GetMetaObject` (`return metafield[0]`) |
| 23 | `0x0015ff10` | 3484 | — | — | macro/packet builder (largest body) |
| 24 | `0x001624b0` | 44 | 5 | — | **banked** — `FUN_00162b50(FUN_0015f580(va,5,0))` |
| 25 | `0x001624e0` | 44 | 6 | — | **banked** — `FUN_00162ca0(FUN_0015f580(va,6,0))` |
| 26 | `0x00160cb0` | 260 | — | — | ctor/`igObject`-swap (refcount) |
| 27 | `0x00160dc0` | 52 | — | — | **banked** — `_vertexArray->_vertexStream->_accessMode (+0x18) == 2` predicate |
| 28/29/30 | `0x160e00`/`0x160ec0`/`0x160f60` | 184/156/120 | 1 | `igVec3fList` | set / get / pointer |
| 31/32/33 | `0x160fe0`/`0x1610a0`/`0x161140` | 184/156/120 | 3 | `igVec3fList` | set / get / pointer |
| 34/35/36 | `0x1611c0`/`0x161280`/`0x161320` | 184/156/120 | 7 | `igVec3fList` | set / get / pointer |
| 37/38/39 | `0x1613a0`/`0x161460`/`0x161500` | 184/156/120 | 8 | `igVec3fList` | set / get / pointer |
| 40 | `0x161580` | 268 | 2 | `igUnsignedIntList`,`igVec4ucList` | set (word vs 4×`sb`) |
| 41 | `0x161690` | 300 | 2/1 | `igUnsignedIntList`,`igVec4ucList` | set |
| 42 | `0x1617c0` | 184 | 2 | `igUnsignedIntList`,`igVec4ucList` | get word |
| 43 | `0x161880` | 216 | 2/1 | `igUnsignedIntList`,`igVec4ucList` | get |
| 44/45 | `0x161960`/`0x161bc0` | 604/424 | 5 | `igFloatList`,`igVec2fList`,`igVec3fList` | mixed get/set |
| 46/47 | `0x161d70`/`0x161f50` | 468/328 | 6 | `igUnsignedCharList`,`igVec4ucList` | mixed get/set |
| 48/49/50 | `0x1620a0`/`0x162150`/`0x1621e0` | 168/140/112 | 4 | `igVec2fList` | set / get / pointer |
| 51/52 | `0x162250`/`0x1622f0` | 156/116 | 9 | `igFloatList` | set / get |
| 53/54 | `0x162370`/`0x162420` | 168/140 | 9 | `igVec2fList` | set / get |
| 55 | `0x00180e40` | 8 | — | — | **banked** |
| 56 | `0x162510` | 856 | — | — | block copy/convert |
| 57 | `0x00162870` | 8 | — | — | **banked** |
| 58 | `0x162880` | 708 | 4 | `igFloatList` | block |
| 59/60 | `0x162d50`/`0x163260` | 1292 | — | `igFloatList`,`igVec2fList`,`igVec3fList` | block |
| 61 | `0x163810` | 4192 | — | `igFloatList`,`igVec2fList`,`igVec3fList` | block (largest) |

The four look-up tables of slots 28–39 are the same three bodies over four
`componentType`s (1, 3, 7, 8), all resolving to `igVec3fList`.

## The two walls (why the rest is fail-closed)

### 1. The null-deref dynamic-cast idiom (slots 28–39, 40–54)

Every accessor resolves its list like this in retail:

```
lw  s0, 12(v0)          ; s0 = vd->_data
beqz s0, null
lw  a1, igVec3fList_meta
jal FUN_00300cd0        ; class check
move a0, s0
beqz v0, null
b   end
lw  v0, 16(s0)          ; good path: v0 = list->_data  (the delay slot)
null:
move s0, zero
lw  v0, 16(s0)          ; null path: the *same* load, from base 0
end:
...                     ; index arithmetic on v0
```

The load `*(int *)(s0 + 16)` is **duplicated** into the good path's branch-delay slot
and the null path, and the index add is shared after the merge. Every C spelling
tried reproduces the shape but not the bytes:

* `if (p && CHECK) {} else { p = 0; } return *(int*)((char*)p+16) + idx*N;` —
  MWCC **shares** the load and inverts the block order (good/bad swapped);
* the same with the load written in **both** branches — the block order and the
  delay-slot load come out right, but MWCC **constant-folds** the null copy to
  `lw v1, 16(zero)` (one instruction) and swaps `v0`/`v1`; best result **6 differing
  instructions** (`vfunc_30`, `=13` before).
* `volatile`, C++ mode, `struct`-typed pointers, `.p`/`,s`/`,o` flags, `-O1`…`-O4`,
  and a comma/ternary selection were all tried — no change.

`tools/retype_struct_member.py --shape struct,width,leadfn,leadcall` over the whole
module banks **0 of 35**.

### 2. MWCC's load scheduler / callee-saved allocation (slots 40–47, 56, 58, vcalls)

The remaining bodies call a virtual `GetMetaObject()` on the data object and index the
resulting list. Reconstructing them with **real types** — a `VD`/`LST` struct for the
`{count, data}` list layout and a C++ class with the target `virtual` at slot 22 —
fixes the register allocation exactly as it did for `beAction2` (finding [#653](../findings/findings-0501-0750.md#f653)):

* `vfunc_42` went **46 → 9** differing instructions with
  `((LST *)(vd->data))->arr[arg1]` after two typed `GetMetaObject()` compares. The 9
  remaining are one scheduler slot: MWCC fills the second `bne`'s delay slot with the
  `return 0`'s `move v0,zero`, where retail emits `nop` and places the `move` in a
  separate block (4 bytes). Explicit `asm { nop }` only adds a second nop.
* `vfunc_40` went **compile-failure → 272/268 B** with the struct view plus the
  `igVec4ucList` branch's four byte-stores; the residual is one `addiu` where MWCC
  materialises `&arg2` into a register (retail folds the stack bytes into four
  `lbu`s) plus a register swap.

No C/C++ spelling or flag regime found so far closes either wall; both are the same
scheduler/allocator residual the tracker records for the `beAction2` handlers
(finding [#654](../findings/findings-0501-0750.md#f654)) and the framed-tail cluster (finding [#650](../findings/findings-0501-0750.md#f650)).

## Port relevance

The helper and `FUN_0015f580` define how a model's vertex streams are addressed by
`(componentType, componentIndex)` — i.e. how the engine turns the `igVertexArray2`
object graph into the typed position/normal/UV/colour buffers the port reads
(`docs/engine/model-format.md`, findings [#455](../findings/findings-0251-0500.md#f455)/#458). The element stride/component
count returned by `FUN_00162b50`/`FUN_00162ca0` is what the port's stream walker must
reproduce.
