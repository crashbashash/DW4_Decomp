# Model geometry — `igGeometryAttr`

A rendered object in DW4 is **not** a mesh handed to the GS. Its geometry is an
`igGeometryAttr` object whose vertices are consumed *sequentially* by a strip-length array; there is
no index array on the shipped models (1 of 1,006 live attributes has one). Recovering this chain is
what makes a model extractable at all — findings [#453](../findings/findings-0251-0500.md#f453)/#454/#455, with the model-name link and the
normals/UV streams in [#456](../findings/findings-0251-0500.md#f456) (corrected and completed by [#457](../findings/findings-0251-0500.md#f457)/#458).

This page is the format. The live-memory extractor used to prove it is kept with the emulator
tooling rather than in this repository (it needs a running game, which this repo deliberately does
not depend on); the offline route — reading the same geometry out of a stage's model pack — is
described under *The offline route* below.

## The object chain

Four classes carry the data, and every field offset below was read off live objects, cross-checked
against `data/reflection.json` and against the reflection offsets in the class registrar.  The names
are the reflection record's own, which is why the derived class's field is `_stripLengths` while the
base's is `_primLengths`.

```
igGeometryAttr1_5           vtable 0x005238c0   (the concrete subclass; 0x38 bytes)
  +0x0c  _vertexArray   ->  igVertexArray object
  +0x10  _indexArray    ->  igIndexArray object, or 0 (NULL)
  +0x14  _primType          4 = triangle strip, 3 = triangle list, 0 = empty slot
  +0x18  _numPrims          strip count (type 4) or triangle count (type 3)
  +0x30  _stripLengths  ->  igPrimLengthArray1_1 object, or 0 (NULL)
        (inherited from igGeometryAttr: +0x1c _offset, +0x20 _primLengths (NULL here),
         +0x24 _handle, +0x28 _dPds, +0x2c _dPdt)

igPsx2VertexArray1_1        vtable 0x00525190   (the runtime class of _vertexArray)
  +0x08  _vdata         ->  a { positions, normals } pair of heap pointers
  +0x0c  _numVerts          vertex count
  +0x30  _pBlendedVertsList / +0x34 _pBlendedNormsList   (0 on these objects)
  +0x48  _textureCoordCompiled                          (0 on these objects)

The vertex array also has a **UV stream**, but no field points at it: it is the buffer that follows
the last 12-byte stream in the loader's packed pool (see *Normals and UVs* below).

igPrimLengthArray1_1        vtable 0x00526590   (_vdata +0x08, _count +0x0c)
  +0x08  _vdata             a *direct* pointer to the u32 lengths (no descriptor)
  +0x0c  _count             number of primitives
```

Three details are easy to get wrong:

* `igVertexArray._vdata` and `igPrimLengthArray1_1._vdata` are **not the same kind of pointer**.
  The prim-length array's is the lengths themselves.  The vertex array's is a **two-pointer block
  `{positions, normals}`** — not a `{start, size}` memory ref — so `_vdata[0]` is the 12-byte-stride
  vertex buffer and `_vdata[1]` the normal buffer **or 0** (see *Normals and UVs* below).  Reading the
  block as a `{start, end}` pair makes `end - start` look like `12 * numVerts + 8` whenever a second
  buffer happens to follow the vertices; that coincidence suggests a size field, and there is
  none.
* `_primType` is at `+0x14`, **not** `+0x20` as the base-class reflection record alone would
  suggest; `igGeometryAttr1_5` adds `_stripLengths`, which lands at `+0x30` where the base's
  `_primLengths` is at `+0x20` and stays NULL.  Objects are 0x38 bytes and are allocated
  back-to-back, so reading past the end silently reads the *next* geometry attribute.
* `_vertexFormat` (`igVertexArray1_1` +0x1c) is a struct, not the stride: the buffer size always comes
  from `_numVerts * 12`.

## Connecting the vertices — no indices

Both representations walk the vertex buffer **in order**, which is why `sum(primLengths) ==
_numVerts` and `3 * numPrims == numVerts` hold and make usable self-checks.

**`_primType == 4`, triangle strip.** `_primLengths` gives the length `L` of each strip. Strip *i*
owns vertices `[off, off+L)` with `off` advancing by `L`; it contributes `L-2` triangles. A live
barrel, for example, is 494 vertices and 118 strips (`{4: 72, 3: 36, 12: 5, 7: 4, 10: 1}`) totalling
258 triangles — `sum(L) == 494 == numVerts`.

**`_primType == 3`, triangle list.** There is no prim-length array: `_numPrims` triangles read
straight through the buffer in triples (`3 * numPrims == numVerts`).

**`_primType == 0`.** An empty or recycled slot — `_vertexArray` is 0, and freed slots hold a
self-pointer at `+0x38`. Of 1,006 live attributes, 454 are strips, 337 are lists, and 215 are empty.

## Normals and UVs

`_vdata[0]` is the positions and `_vdata[1]` the normals, each `12 * _numVerts` bytes of `vec3f`; the
normals are unit length.  **`_vdata[1]` is 0 for most meshes and there is then no normal buffer at
all.**  Of the 669 extracted live models 130 carry unit-length normals and **539 carry none** (221
strip + 318 list).  (That split is a property of the **live** object graph, not of the pack: read
straight from the file, *every* mesh of a stage's drawn set in `NDMW.AFS:614` carries a unit-length
second `12*numVerts` stream — the six big terrain meshes, the floor, the props and the character — which is
why a port can shade them smoothly; finding [#559](../findings/findings-0501-0750.md#f559).)  The buffer layout in the loader's packed pool is

    [positions: 12*n][tag + pad][optional normals: 12*n][tag + pad][uv: 8*n]

so when `_vdata[1]` is 0 the buffer right after the positions is the UV, not the normals — a search of
the pool around 40 of those meshes found no `12*n` unit-length block, so the normals really are absent
rather than relocated.  `igPsx2VertexArray1_1`'s `_pBlendedNormsList` (+0x34) is 0 on all of them, so
the blended path the field name implies is not the source either.  The split is by kind, not accident:
the meshes *with* normals are effect/part meshes and props (`M_BK_op_0Shape`, `M_BK_p0Shape`,
`expnumShape`, `kouka0Shape`, the barrel), while those *without* are unlit/2D — `font*` (205),
`polySurfaceShape`, `CF_*`, `pPlaneShape`, `pCylinderShape`, `iconShape`, `win0Shape`.

The UV stream **is** real, and it is at

    uv = align8((normals if present else positions) + 12 * numVerts),   align8(x) = (x + 4 + 7) & ~7

— the 4 bytes in the gap are a pool tag and the block is then 8-byte aligned.  Each entry is an
8-byte `{u, v}` float pair, `8 * numVerts` bytes, and the buffer after it is again tag + alignment
(checked against the buffer-pointer pool for meshes both with and without normals).  Nothing in the
object points at the UV, so it is established **geometrically**: for
`pCylinderShape3` (attr `0x111ca30`, 55 verts) `u` tracks `atan2(z, x)` with correlation **0.998**,
all 55 pairs sit in `[0,1]`, and the values are dyadic (a barrel's first pair is `0.53125, 0.703125`
= 17/32, 45/64).

## Names come from the art source, not the binary

The shipped binary keeps no model names of its own, but the exported geometry does, and they survive:
model parts are named after their **DCC source objects** (Maya/3ds Max) — `M_BK17v1_barrelmShape`,
`pCylinderShape3`, `pCubeShape5`, `polySurfaceShape38`, `group2`, `barrelbody`.

They live on the shape object, and the link to a geometry attribute is a single list:

```
M_<model>Shape               vtable 0x00528e70   (826 live)
  +0x08  name pointer     ->  the DCC part name string (0 on 145 of the 826)
  +0x20  ->  exactly one igAttrList (vtable 0x00524420), { _count +0x08, _array +0x10 }; its array
             holds the shape's attr pointers, and the entry whose vtable is 0x005238c0 is that
             shape's geometry attribute
  +0x1c  ->  a wrapper (vtable 0x0052ab20) embedding the shape's FIRST attr at +0x18 — fallback
             only: it is any attr subclass (class 0x00529750 on ~1,100 other objects, not the
             geometry) and normally duplicates the +0x20 entry
```

So a geometry attribute is named by the `M_*Shape` whose attribute list contains it.  **One list per
shape, at `+0x20` — not a chain.**  The `igAttrList` objects live in a packed shared arena, so the
object 0x18 bytes past one shape's list is simply the *next shape's* list (and a shape's own inline
data array can sit there too); walking that stride claimed 637 of 752 attributes for more than one
shape and left `font000` holding 177.  The one-list rule is collision-free (826 shapes, 826 distinct
`+0x20` pointers, 786 owning exactly one geometry attr) and names **599 of the 669** extracted models
with 357 distinct DCC names.  The other 70 belong to shapes whose `+0x08` name pointer is **null**
(runtime/UI sub-meshes — small, content-unique 24-vertex glyph quads), so they are left as
`model_<address>.obj` rather than given a neighbour's name.

A dead end worth recording: the run of ~1,792 object pointers at
`0x0092a000..0x0092bbfc` looks like a table of geometry attributes and is one, but it is the
**load-time object registry**, not a name index — nothing references it by name, so no name can be read
out of it.

## What was verified

The interpretation was not inferred from the field names — it was checked by rasterising the result.
Rendering the vertices as a plain list, or ignoring the strip boundaries, shreds the mesh even with a
z-buffer; applying the rules above produces recognisable objects, including staves-and-spout barrels
and the claw/ring/box props, and the extraction run pulls **669** distinct models out of one loaded
stage with the self-checks above passing on every one.  Each OBJ also carries the `vn`/`vt`
streams, so all three buffers are exported (669 files, 669 with UVs, 130 with normals).  The same run
locates **446** of those models' vertex blocks in the stage's model pack by content, which agrees
with the offline route (see below).

## The offline route (findings [#477](../findings/findings-0251-0500.md#f477)/#478)

The offline form needs no load-level replay: a
pack states its own addressing (findings [#460](../findings/findings-0251-0500.md#f460)/#464/#478).  An `igObjectRef` id indexes the pack's remap
table, an `igMemoryRef` value **is** the id of its pool block, and blocks are laid out **4-byte aligned**
(`offset = pool_start + Σ align4(_memSize)`), which makes the pool exact.  The geometry chain resolves
through it:

```
igGeometryAttr1_5  slot 4 (+0x0c) _vertexArray  ->  an igObjectRef id
    -> igVertexArray1_1   _vdata  -> a memory block (class 7, always 80 bytes) listing this
                                     array's stream ids, and _numVerts
                          _stripLengths -> igPrimLengthArray1_1, whose data are the u32 lengths
```

for `igGeometryAttr1_5` slot *k* sits at `4*(k-1)` (`+0x10` `_indexArray` = −1, `+0x14` `_primType`,
`+0x18` `_numPrims`, `+0x30` `_stripLengths`; all confirmed by value).  Slot *numbers* are not
comparable across classes — each class numbers its own declaration chain — so the field *offsets* come
from `data/reflection.json` (a base class declares its own fields, at absolute offsets, so
`igGeometryAttr`/`igVertexArray`/`igPrimLengthArray` hold most of them), and every link is then
*validated* by the format's own arithmetic: the `_vdata` block must list a `12*_numVerts` stream and the
lengths must sum to `_numVerts`, so an offset that did not hold would show up as a skipped attribute
rather than as bad geometry.

**`_memSize` is the stream's content size exactly** — `12*_numVerts` for the positions, `8*_numVerts`
for the UVs — verified over all 549 vertex arrays of entry 621.  So a stream is found with no search:
its id gives its offset and its `_memSize` gives its length.

The extractor is `scripts/igb_models.py` (`--list`, `--tsv`, `--obj ID`, `--out-dir`), and the port has
the same reader in C (`dw4asset models`, `port/src/models.c`).  It pulls **all 549** of entry 621's
geometry attributes, and **450 of them are byte-identical to a live-extracted model**
(`scripts/extract_live_models.py`; the check is `testing/verify_models_offline.py`).  Of the rest, 52
have a vertex count the live session never held and 47 are same-count models from another part of the
stage — the dump holds only what the session had loaded, so those cannot match rather than being wrong.
`docs/engine/model-pack-621-attributes.tsv` is the committed fixture (one row per attribute: ids, mode,
counts, streams) and `scripts/verify_models_layout.py` re-derives it from the pack.

The **character model packs** (`common/p_*.igb`, e.g. entry 861 = the player) read the same way, but
they are a second record alignment: their records start at an **odd** file offset, while the stage packs
start at `2 mod 4`.  The chain finder scans every offset rather than stepping by two (finding [#536](../findings/findings-0501-0750.md#f536)),
so `igb_models.py --entry 861` yields the player's three `igGeometryAttr1_5` — the three actor **LODs**,
named `P_susanoo_Skin0Shape0/1/2` (finding [#537](../findings/findings-0501-0750.md#f537)); `docs/engine/model-pack-861-attributes.tsv` is that
fixture, re-derived by the same `make rules` check.

Note this is an **offline extractor** route — a port does not need it, because it runs the engine's own
loader over a host `igFile`, which allocates the pool itself.  What the port does need is the
addressing, and that is the same file-derived chain on both sides.

## Names in the pack (finding [#480](../findings/findings-0251-0500.md#f480))

A shape is an `igGeometry` record: its
**ordinal-2** value is the DCC part name (`pCylinderShape3`, `M_BK17v1_barrelmShape`, …) and its
**ordinal-8** value is an `igAttrList` whose `_array` (+0x10) is a block of attribute ids — the ones
that are `igGeometryAttr1_5` records are that shape's geometry, so they take its name.  That is the
same link the live walk uses from RAM (an `M_*Shape`'s list of attrs), reached from the pack instead.
Found by **ordinal, not offset**: a record's byte offsets shift with a variable-length value, because
a long name pushes everything after it along, while the container's slot numbers do not.  The list's
`_count` having to equal its array block's u32 count is the self-check.  It names **444 of the 549**
attributes of `stag0102`'s pack (`igb_models.py --tsv` carries the names, `--out-dir` writes
`model_pCylinderShape3.obj` instead of `model_13842.obj`); the other 105 belong to shapes with an
empty name and stay unnamed rather than borrowing a neighbour's.  **383 of the 386** matched models
get the same name the live namer gives them (`testing/verify_models_offline.py`) — the 3 that differ
are content duplicates, where two shapes share a vertex list and either name is right for its own
attribute.  The live path is `scripts/name_live_models.py`, which reads EE RAM once and resolves
offline (`--from` reuses a saved dump); `--rename-dir` re-applies names to the OBJs.

## Skinning, the actor graph, and the node-held material (findings [#531](../findings/findings-0501-0750.md#f531)-[#535](../findings/findings-0501-0750.md#f535))

A live render differs from the pack in two ways that are **runtime state**, so they are read from a
paused capture (`scripts/livedump.py` trims a `.p2s` to the base the readers expect):

**The per-vertex blend stream is on the vertex array, not on the model controller.**  Correcting
[#454](../findings/findings-0251-0500.md#f454)/#527, `igVertexArray1_1` carries

```
+0x20  _blendWeights   a runtime f32 array, one weight per vertex
+0x24  _blendIndices   a runtime u8 array, one bone index per vertex
+0x1c  _vertexFormat
+0x30  _pBlendedVertsList / +0x34 _pBlendedNormsList   (objects, not the blended buffers)
```

and the stream is **not in the pack**: `igVertexArray1_1._blendWeights` exists in the file but holds a
4-byte stub, because the engine allocates the real arrays at load.  So a skinned mesh is identifiable
from the live graph alone — it is the one whose vertex array has non-NULL `_blendWeights` *and*
`_blendIndices`.  **A skinned mesh is not necessarily the player** (finding [#535](../findings/findings-0501-0750.md#f535) refutes [#531](../findings/findings-0501-0750.md#f531)): on the
Goblin Pass capture the only such mesh is `ogre_skinShape`, an **Ogremon NPC**, while the player is
Susanoomon (see the actor graph below).  The bone-selection map is
`igBlendMatrixSelect._blendMatrixIndices` (+0x28, an `igIntList` of bone-count entries mapping a vertex
bone to a matrix slot), and the pose matrices are a 24-matrix `igBlendMatricesAttr._matrixCache` (+0x0c,
count +0x10) — or, for an actor, its own `_boneMatrixCacheArray` (+0x24) and `_blendMatrixCacheArray`
(+0x28).  **Open:** no back-link from a free mesh or the select to *its* `igBlendMatricesAttr` was
found — several live 24-/40-matrix caches exist with no back-pointer — so for an unparented mesh the
palette cannot be paired from the object graph and the bind pose stands.

### The player's own skinning, offline (findings [#597](../findings/findings-0501-0750.md#f597)/#598/#599)

For the player the gaps above are closed, and the answer is
*not* in the object graph:

* **The per-vertex bone indices are in the pack** (finding [#596](../findings/findings-0501-0750.md#f596)): pack 861 holds pool blocks of exactly
  `num_verts` bytes — 5483 (354, shape0), 5595 (2018, shape2), 5566 (3580, shape1) — each a u8
  bone index per vertex, values 1..23.  The neighbouring 4-bytes-per-vertex blocks (5593/5594/5565)
  are constant `1.0f` weights — **no weight data exists in the pack**.
* **The palette the GPU actually skinned with is a per-bone array staged in the VU/DMA packet area**
  (finding [#597](../findings/findings-0501-0750.md#f597)): four byte-identical 24-matrix copies (0x1b743dc0 / 0x1b53f40 / 0x1b64040 / 0x1b741c0,
  one per character draw run) with a repeated copy 0x11f0 bytes into each, indexed **directly by the
  bone byte** — the `igBlendMatrixSelect` list is not consulted for the player.  Shape1 fits the
  native GS draw at median 0.0057 model units single-bone (100 % within 0.05); the
  `igAnimationCombiner`-held palette (0x16df680, 21 slots, slot-mapped) fits the same vertices about
  7× worse, so the combiner's +0x58 pointer is the engine's own copy, not what the VU received.
* **Shape0 (the 354-vert LOD) is not drawn at all in that frame** (finding [#598](../findings/findings-0501-0750.md#f598)): none of its UVs
  appear in the character draw's 6134-vertex UV union.  A renderer of that instant draws
  `Skin0Shape1 + Skin0Shape2` only; shape2's remaining ~0.03-unit residuals sit on blend bones
  (9/10/11) and are unresolved, but sub-pixel at that camera.
* **A measurement trap worth naming** (finding [#599](../findings/findings-0501-0750.md#f599)): a staged model-space conversion with a wrong
  node/view step scores every palette candidate meaningless (medians of ~438 units); recomputing the
  conversion from the same world points (bind-vs-gs median 0.68 once posed) is what makes the sweeps
  sharp.

## The player is an actor, and its model is named by a path (finding [#535](../findings/findings-0501-0750.md#f535))

The player is **not** an `igGeometry` whose name you guess.  It is a model-controller node with an actor
rig:

```
beModelCtrlNode2 0x016de170   (the node nearest the camera's `_avgPos`)
  -> igLod 0x016de208 -> THREE igActor LODs (0x016de2d0 / 0x016dfbc8 / 0x016dfd70)
       _appearance      +0x2c -> igAppearance
         _skin          +0x0c -> igSkin
           _skinnedGraph +0x0c -> igBlendMatrixSelect (0x01667468)
             +0x1c  an igNodeList of the skin's igGeometry shapes (the meshes to draw)
             +0x20  the material attr list (igTextureBindAttr / igMaterialAttr)
       _boneMatrixCacheArray  +0x24   \  the pose, ON THE ACTOR
       _blendMatrixCacheArray +0x28   /
```

That is the graph a renderer should walk: the skinnedGraph's child list is the model, its attr list the
material, and the **actor** owns the matrix caches (where [#532](../findings/findings-0501-0750.md#f532)'s missing pairing lives).  On the Goblin
Pass capture the player's skin is `P_susanoo_Skin0Shape0/1/2` (Susanoomon), the RAM string
`common/p_susanoo.igb` names the model, and the manifest resolves `p_susanoo.igb` to **`NDMW.AFS` entry
861** (685,597 B, beside `m_`/`q_`/`s_susanoo.igb` = 845/877/893) with textures `P_susanoo01.png` /
`P_susanoo02.png`.  **Offline (finding [#537](../findings/findings-0501-0750.md#f537)):** the live skin shapes' `igVertexArray1_1` read
`numVerts` 0 / `vdata` 0 in the capture because the actor builds its geometry through the actor graph —
but the pack itself is complete: entry 861 decodes and yields its three `igGeometryAttr1_5`, all named
`P_susanoo_Skin0Shape0/1/2`, which are the actor's **three LODs** (354 / 3,580 / 2,018 verts) and each
spans the whole humanoid.  A port loads `p_susanoo.igb`; a renderer can also read the actor's
`_attachedGraphs`.  Reaching the pack needs the every-offset chain scan of finding [#536](../findings/findings-0501-0750.md#f536) (the character packs'
records sit at the odd alignment).

**A material can hang off the parent node.**  A shape's own `+0x20` list is geometry only, but a mesh's
texture can instead sit on the `igBlendMatrixSelect` (an `igAttrSet` subclass) that is its `_parentList`
entry: the `igAttrSet._attributes` (+0x20) list holds the `igTextureBindAttr`.  Reading the
parent-chain node attr sets — testing that `+0x20` really is an `igAttrList` (`0x00524420`), because on a
plain `igTransform` the same offset is `_m` — lifts the live material map from 106 to 136 geometry
attributes.  The big ground mesh and the crates still resolve nothing this way; their material is in the
staged render packet stream ([#522](../findings/findings-0501-0750.md#f522)).

## See also

* [`reflection-metadata.md`](reflection-metadata.md) — the `ig*` reflection system these field names
  come from.
* [`rtti-and-vtables.md`](rtti-and-vtables.md) — how `0x5238c0` and friends are resolved to classes.
* [`igbinary-format.md`](igbinary-format.md) — the container the model packs are written in.
* [`afs-archives.md`](afs-archives.md) — which pack holds a stage's models.
