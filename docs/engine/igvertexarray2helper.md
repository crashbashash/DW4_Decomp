# `igVertexArray2Helper` — the vertex-array accessor/binder

`Gap::Core::igVertexArray2Helper` is the Intrinsic Alchemy class that *binds* an
`igVertexArray2` to a typed view: it looks up a named vertex-data stream inside the
array and reads or writes its elements. It sits in the Alchemy graphics core
(`0x0015ff10`–`0x00164870`, the `0x141000`–`0x1f0000` region of `module-map.md`).

## Identity and layout

| | |
|---|---|
| Class metaobject handle | `0x0055f9d0` (`DAT_0055f9d0[0]` is the MetaObject returned by slot 22) |
| vtable | `0x005262a0`, stamped by `igVertexArray2Helper_GetVTable` (`0x0014a560`) |
| Base | `igNamedObject` (`data/class-hierarchy.tsv`); no `__RTTI__` record, so the class name comes from the `GetVTable` function |
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
| 22 | `0x00180e30` | 8 | — | — | `GetMetaObject` (`return metafield[0]`) |
| 23 | `0x0015ff10` | 3484 | — | — | builds the stream records of a new `igVertexArray2` (see [Open questions](#open-questions)) |
| 24 | `0x001624b0` | 44 | 5 | — | `FUN_00162b50(FUN_0015f580(va,5,0))` |
| 25 | `0x001624e0` | 44 | 6 | — | `FUN_00162ca0(FUN_0015f580(va,6,0))` |
| 26 | `0x00160cb0` | 260 | — | — | ctor/`igObject`-swap (refcount) |
| 27 | `0x00160dc0` | 52 | — | — | `_vertexArray->_vertexStream->_accessMode (+0x18) == 2` predicate |
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
| 55 | `0x00180e40` | 8 | — | — | — |
| 56 | `0x162510` | 856 | — | — | block copy/convert |
| 57 | `0x00162870` | 8 | — | — | — |
| 58 | `0x162880` | 708 | 4 | `igFloatList` | block |
| 59/60 | `0x162d50`/`0x163260` | 1292 | — | `igFloatList`,`igVec2fList`,`igVec3fList` | block |
| 61 | `0x163810` | 4192 | — | `igFloatList`,`igVec2fList`,`igVec3fList` | block (largest) |

The four look-up tables of slots 28–39 are the same three bodies over four
`componentType`s (1, 3, 7, 8), all resolving to `igVec3fList`.

## Matching

The `0x0015ff10`-`0x00164870` unit uses the `combat` profile (`-O3`, alternate compiler,
exceptions off), which the accessors need, `vfunc_30`, `vfunc_40` and `vfunc_42` included.
The duplicated-null-load cast and the
scheduler residuals below are default-compiler results, so neither stands as a wall.
Spellings and flags that failed under the default compiler say nothing about the
alternate compiler.

* **The null-checked cast (slots 28-39, 40-54).** Every accessor checks the class of
  `vd->_data` and nulls the pointer on failure. Retail duplicates the following load of
  `+16` into the good path's branch-delay slot and into the null path, where it reads from
  base 0, and shares the index add after the merge. `vfunc_30` spells it as an `if`/`else`
  that assigns the pointer in both arms, followed by one load and index expression.
* **The virtual `GetMetaObject()` bodies (slots 40-47, 56, 58).** These need real types: a
  struct for the `{count, data}` list layout and a C++ class with the target `virtual` at
  slot 22, as in `vfunc_42`.

## Vertex stream addressing

The helper and `FUN_0015f580` define how a model's vertex streams are addressed by
`(componentType, componentIndex)` — i.e. how the engine turns the `igVertexArray2`
object graph into typed position/normal/UV/colour buffers
(`docs/engine/model-format.md`). `FUN_00162b50`/`FUN_00162ca0` return the element
stride/component count.

## Open questions

`vfunc_23` builds the stream records of a new `igVertexArray2` from a layout word: bits
0/1/2 give stream kinds 1/3/2 (12/12/4-byte elements); bits 16-19 a count of kind 4 records
(8-byte elements, index in +20); bits 4-7 a count for kind 5 (count in +24); bits 8-11 kind
6 (1-byte elements); bits 20-21 a mode for kind 9 (1: 4-byte, 2: 8-byte list); bits 22/23
kinds 7/8. A record is `{list +12, kind +16, index +20, count +24}`. The meanings of the
kinds are not established.
