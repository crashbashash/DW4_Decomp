# Model geometry — `igGeometryAttr`

A rendered object in DW4 is **not** a mesh handed to the GS. Its geometry is an
`igGeometryAttr` object whose vertices are consumed *sequentially* by a strip-length array; there is
no index array on the shipped models (1 of 1,006 live attributes has one). Recovering this chain is
what makes a model extractable at all.

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
  from `_numVerts * 12`.  At run time `igPsx2VertexArray1_1._vertexFormat` is a bitmask: bit 22
  (`0x400000`) is positions, 12 bytes per vertex through `_vdata`+68, and bit 23 (`0x800000`) is normals
  through +72.  No other bit is tested in the decompiled engine and no vertex-array consumer has a
  colour element, so per-vertex colour comes from the VU1 shade.  The GS vertex packing is VU1
  microcode, not C.

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
second `12*numVerts` stream — the six big terrain meshes, the floor, the props and the character.)  The buffer layout in the loader's packed pool is

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

## The offline route

The offline form needs no load-level replay: a
pack states its own addressing.  An `igObjectRef` id indexes the pack's remap
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

The extractor is `scripts/igb_models.py` (`--list`, `--tsv`, `--obj ID`, `--out-dir`).  It pulls **all 549** of entry 621's
geometry attributes, and **450 of them are byte-identical to a live-extracted model**
(`scripts/extract_live_models.py`; the check is `testing/verify_models_offline.py`).  Of the rest, 52
have a vertex count the live session never held and 47 are same-count models from another part of the
stage — the dump holds only what the session had loaded, so those cannot match rather than being wrong.
`docs/engine/model-pack-621-attributes.tsv` is the committed fixture (one row per attribute: ids, mode,
counts, streams) and `scripts/verify_models_layout.py` re-derives it from the pack.

The **character model packs** (`common/p_*.igb`, e.g. entry 861 = the player) read the same way, but
they are a second record alignment: their records start at an **odd** file offset, while the stage packs
start at `2 mod 4`.  The chain finder scans every offset rather than stepping by two,
so `igb_models.py --entry 861` yields the player's three `igGeometryAttr1_5` — the three actor **LODs**,
named `P_susanoo_Skin0Shape0/1/2`; `docs/engine/model-pack-861-attributes.tsv` is that
fixture, re-derived by the same `make rules` check.

Note this is an **offline extractor** route: the engine's own loader allocates the pool itself over
`igFile`, and its addressing is the same file-derived chain.

## Names in the pack

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

## Scene graphs in the pack

A stage's scene graph reads offline.  `igSceneInfo` has a name at ordinal 2 and `_sceneGraph` at ordinal
5, which is either an `igNode` root or an `igGraphPathList`.  An `igGraphPath` reaches its roots through
a separate `igNodeList` (an `igObjectRef`); walking the path's own `igMemoryRef` finds no nodes.  A
list's items are ids in the block behind its `igMemoryRef`.  A node carries a name, optionally an
`igMatrix44f` (type 40, row-major, translation at words 12..14), an `igNodeList` of children and a
reference to an `igGeometry`.  Find each value by its descriptor type, not by class or offset.

Scene names are the game's own entity names (`Ogremon`, `Goblimon`, `Sdc0102a`, `Slope`).  Stage packs
also hold camera and scene-animation chains in these graphs, such as `animCamera03_300` ->
`cameraanim_GP1` -> `cameraanim_group01`.  `igSceneInfo`'s own `igNodeList` (ordinal 11) is empty in all
18 records of entry 621.

Geometry nodes and their transforms are in these graphs, not in the model-controller records.
`beModelCtrlNode2` (1,075 records in entry 621) carries a name, an `igMatrix44f` and an `igNodeList` of
children; its `igAttrList` is empty in every record, so it holds no geometry attribute directly.  The
`*InfoRam*` classes are referenced by no record and are built at run time (all 1,075
`beModelCtrlInfoRamData` have no parent).  Walking `_sceneGraph` on `stag0102`'s pack gives 18 scenes,
11,736 nodes and 2,724 named `igGeometry` nodes.

`igGeometryAttr1_5` has no material reference: ordinals 5, 9, 11 and 12 are NULL in all 549 attributes of
entry 621, and only 4 (`igVertexArray1_1`) and 13 (`igPrimLengthArray1_1`) are ever set.  Texture-side
names (`TA01GM07.png`) do not match model DCC names (`pCylinderShape3`), so name matching is no route to
a mesh's texture.  In the pack the texture side is `igTextureBindAttr` ordinal 4 -> `igTextureAttr`
ordinal 12 -> `igImage`, and `beTextureCtrlAttr` ordinal 2 is the texture's name, ordinal 3 an
`igAttrSet`.

## The live model graph

```
beModelCtrlInfo         vtable 0x537c10   (148 in stag0102), the per-model registry
  +8   _name
  +20  _dataList        beModelCtrlInfoDataHit 'HIT', beModelCtrlInfoDataSeq 'SEQ'
  +24  _ramList         a list of beBaseInfoRam (vtable 0x539e90)

beModelCtrlNode2        vtable 0x537f40, a transform node
  +28  _childList       walks to G_* groups (vtable 0x5284f0) and M_*Shape meshes (0x528e70)

beModelCtrlInfoRamData  vtable 0x537bb0, 24 bytes, holds no geometry
  +16  _node
  +20  _work
```

`igVertexArray`, `igVertexArray1_1` and `igIndexArray` are abstract: their registrars (`0x14ba30`,
`0x14b720`, `0x14d8a0`) pass no GetVTable.  `igVertexArray2` (vtable `0x526410`) and
`igVertexArray2Helper` (`0x5262a0`) are concrete, but neither has a live instance.

**Reading a dump.**  Live `igGeometry` objects can be read from a saved EE RAM dump with no emulator
(`scripts/capture_scene.py`).  Two traps: the objects are 4-byte aligned, so an 8-byte-stepped scan finds
none, and `+0x10` `_parentList` is a list whose array's first entry is the parent node, not the node
itself.  A node's world matrix composes its chain's `igTransform` `_m` (+32) child x parent.  Keep only
affine matrices (last row 0,0,0,1, orthonormal rotation rows): a wrong field then reads as garbage and
is dropped instead of multiplied in.

**A live vertex array can be drained.**  An `igGeometryAttr1_5`'s `_vertexArray` can read `_vdata` 0,
`_numVerts` 0: the game copies the geometry into render buffers and frees the array.  Those buffers hold
the pack's streams unchanged.  For the Goblin Pass crate the 415-vertex position stream at `0x0143c3c0`,
the normals after it and the UV stream at `0x0143eab0` are byte-identical to the pack decode, with a size
word (`0x26f0` = 2*4980 + 8) just before the UVs, and the inline image's index block is intact at
`0x0130ac20`.  A second, reordered copy of similar values at `0x00e379dc` is not the crate's stream.

**Node and bone matrices.**  `igTransform._m` (+0x20) is a node's local matrix.  Slot 37 of the
`beModelCtrlNode2` vtable (`0x537f40`), `Gap__Core__igObject__vfunc_37`, sets it: when `_transformInput` (+0x68) is
non-NULL it passes `node+0x20` and the source matrix to that object's `vfunc_0x5c`.  `SETMATRIX` and
`MOVETRANS` call this slot.  A skinned actor's bone matrices are `igActor._boneMatrixCacheArray` and
`_blendMatrixCacheArray`, reset on action start by `beAction2::vfunc_33`.  The runtime bone array is
`igAnimationState+0x54`, stride 0x40 (getters `0x1e34c0`/`0x1e34d0`).  `GETBONEMATRIX` resolves a joint
name through the model at action+0x34 and pushes a 0x40-byte matrix.  `FUN_00398ef0` is the candidate
per-frame walk: it writes `node._time` and composes parent * local.

## Skinning, the actor graph, and the node-held material

A live render differs from the pack in two ways that are **runtime state**, so they are read from a
paused capture (`scripts/livedump.py` trims a `.p2s` to the base the readers expect):

**The per-vertex blend stream is on the vertex array, not on the model controller.**
`igVertexArray1_1` carries

```
+0x20  _blendWeights   a runtime f32 array, one weight per vertex
+0x24  _blendIndices   a runtime u8 array, one bone index per vertex
+0x1c  _vertexFormat
+0x30  _pBlendedVertsList / +0x34 _pBlendedNormsList   (objects, not the blended buffers)
```

and the stream is **not in the pack**: `igVertexArray1_1._blendWeights` exists in the file but holds a
4-byte stub, because the engine allocates the real arrays at load.  So a skinned mesh is identifiable
from the live graph alone — it is the one whose vertex array has non-NULL `_blendWeights` *and*
`_blendIndices`.  **A skinned mesh is not necessarily the player**: on the
Goblin Pass capture the only such mesh is `ogre_skinShape`, an **Ogremon NPC**, while the player is
Susanoomon (see the actor graph below).  The bone-selection map is
`igBlendMatrixSelect._blendMatrixIndices` (+0x28, an `igIntList` of bone-count entries mapping a vertex
bone to a matrix slot), and the pose matrices are a 24-matrix `igBlendMatricesAttr._matrixCache` (+0x0c,
count +0x10) — or, for an actor, its own `_boneMatrixCacheArray` (+0x24) and `_blendMatrixCacheArray`
(+0x28).  **Open:** no back-link from a free mesh or the select to *its* `igBlendMatricesAttr` was
found — several live 24-/40-matrix caches exist with no back-pointer — so for an unparented mesh the
palette cannot be paired from the object graph and the bind pose stands.

`gobr_skinShape2` (pack 614 attr 22308) is a Goburimon, not the player.  Its live parent group
`gobr_main` is a root that no `beModelCtrlNode2` reaches, its texture is `E_goburi01.png` and its
animation is `karada_Trans1`/`SQ_WALK`.  The live-attr to pack-id content match misses this skinned mesh,
so its texture has to be resolved by live shape name.

**The skinning-matrix upload.**  `FUN_001e9770` reads an `igBlendMatricesAttr` pool palette and stages it
for VU1: a loop at `0x001E98F0..0x001E9934` copies 64-byte records.  The upload descriptor is at
`*(0x568F04)` (cursor at +48), and the stride is `*(0x562D48) << 6`, where `*(0x562D48)` is the matrix
count (24 for the player palette).  A snapshot of VU1 data memory holds matrices but none of the player's
bind positions, and EE RAM has one full copy of the mesh.  The pool palette is duplicated byte for byte
in a second attr and appears compacted (duplicate dropped, reordered) in a per-object buffer near the
player node.  Changing the pool palette, the actor's matrix caches or the bind vertices in memory never
alters the frame, because the pose is recomputed before each render.

### The player's own skinning, offline

For the player the gaps above are closed, and the answer is
*not* in the object graph:

* **The per-vertex bone indices are in the pack**: pack 861 holds pool blocks of exactly
  `num_verts` bytes — 5483 (354, shape0), 5595 (2018, shape2), 5566 (3580, shape1) — each a u8
  bone index per vertex, values 1..23.  The neighbouring 4-bytes-per-vertex blocks (5593/5594/5565)
  are constant `1.0f` weights — **no weight data exists in the pack**.
* **The palette the GPU actually skinned with is a per-bone array staged in the VU/DMA packet area**
: four byte-identical 24-matrix copies (0x1b743dc0 / 0x1b53f40 / 0x1b64040 / 0x1b741c0,
  one per character draw run) with a repeated copy 0x11f0 bytes into each, indexed **directly by the
  bone byte** — the `igBlendMatrixSelect` list is not consulted for the player.  Shape1 fits the
  native GS draw at median 0.0057 model units single-bone (100 % within 0.05); the
  `igAnimationCombiner`-held palette (0x16df680, 21 slots, slot-mapped) fits the same vertices about
  7× worse, so the combiner's +0x58 pointer is the engine's own copy, not what the VU received.
* **Shape0 (the 354-vert LOD) is not drawn at all in that frame**: none of its UVs
  appear in the character draw's 6134-vertex UV union.  A renderer of that instant draws
  `Skin0Shape1 + Skin0Shape2` only; shape2's remaining ~0.03-unit residuals sit on blend bones
  (9/10/11) and are unresolved, but sub-pixel at that camera.
* **A measurement trap worth naming**: a staged model-space conversion with a wrong
  node/view step scores every palette candidate meaningless (medians of ~438 units); recomputing the
  conversion from the same world points (bind-vs-gs median 0.68 once posed) is what makes the sweeps
  sharp.

## The player is an actor, and its model is named by a path

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
material, and the **actor** owns the matrix caches (the pairing a free mesh lacks).  On the Goblin
Pass capture the player's skin is `P_susanoo_Skin0Shape0/1/2` (Susanoomon), the RAM string
`common/p_susanoo.igb` names the model, and the manifest resolves `p_susanoo.igb` to **`NDMW.AFS` entry
861** (685,597 B, beside `m_`/`q_`/`s_susanoo.igb` = 845/877/893) with textures `P_susanoo01.png` /
`P_susanoo02.png`.  **Offline:** the live skin shapes' `igVertexArray1_1` read
`numVerts` 0 / `vdata` 0 in the capture because the actor builds its geometry through the actor graph —
but the pack itself is complete: entry 861 decodes and yields its three `igGeometryAttr1_5`, all named
`P_susanoo_Skin0Shape0/1/2`, which are the actor's **three LODs** (354 / 3,580 / 2,018 verts) and each
spans the whole humanoid.  The model loads from `p_susanoo.igb`, and the actor's `_attachedGraphs` also
reach it.  Reaching the pack needs the every-offset chain scan (the character packs'
records sit at the odd alignment).

**A material can hang off the parent node.**  A shape's own `+0x20` list is geometry only, but a mesh's
texture can instead sit on the `igBlendMatrixSelect` (an `igAttrSet` subclass) that is its `_parentList`
entry: the `igAttrSet._attributes` (+0x20) list holds the `igTextureBindAttr`.  Reading the
parent-chain node attr sets — testing that `+0x20` really is an `igAttrList` (`0x00524420`), because on a
plain `igTransform` the same offset is `_m` — lifts the live material map from 106 to 136 geometry
attributes.  The big ground mesh and the crates still resolve nothing this way.  Their binding is the
live-built material attr set: `beTextureCtrlAttr._attrSet` (+0xc), whose `+0x1c` list holds the shapes
and `+0x20` the `igTextureBindAttr`.

## See also

* [`reflection-metadata.md`](reflection-metadata.md) — the `ig*` reflection system these field names
  come from.
* [`rtti-and-vtables.md`](rtti-and-vtables.md) — how `0x5238c0` and friends are resolved to classes.
* [`igbinary-format.md`](igbinary-format.md) — the container the model packs are written in.
* [`afs-archives.md`](afs-archives.md) — which pack holds a stage's models.

## Open questions

* Which buffer supplies the vertices that are skinned.  VU1 data memory holds none of the player's bind
  positions and EE RAM has one full copy of the mesh, but the source of the skinned stream is unproven.

## What didn't work

* **Reading a world mesh's texture off its shape.**  Of 832 live `igGeometry` shapes none has an
  `igTextureBindAttr` in its own `+0x20` attr list, no attr list holds both a geometry attr and a texture
  bind (0 of 2,766), and only 39 of 1,023 `igGeometryAttr1_5` reach a texture by any pointer field (32 of
  them `font00.png`).
* **Reading the texture out of a staged packet stream in EE RAM.**  The region `0x00cc3000-0x00d3xxxx`
  holds per-vertex data, a whole-RAM scan finds no GIF tags there, and per-draw state has to come from a
  GS dump.
