# igBinary (IGB) format

Digimon World 4 (Gap::Core engine, derived from the Insomniac `ig` object
model) serializes its data as **igBinary**. Three flavors appear:

| File | Flavor |
| --- | --- |
| `NDMW.IGB` (106 KB) | standalone IGB file — a **manifest** that references sub-IGB files (`g_pack.igb`, `eng_pack.igb`, `aaacamera.igb`, …) |
| `AREA.AFS` entry 9 (430 KB) | text/data table — **no magic**, but shares the string-table + object structures |
| `NDMW.AFS` entries | "stage packs" = `[igBinary reflection metadata][Lua 4.0.1 chunks…]` |

Parser: `scripts/igb_parse.py` for the header, string table and file references, and
`scripts/igb_dir.py` for the type directory's class records and their field
descriptors.

## Fixed preamble (confirmed across 4+ files)
Every igBinary blob shares an identical tail and string table:

| field | value |
| --- | --- |
| header[8] | `0x656` = offset to interface name (`"igInterfaceDeclarationField"`) |
| header[9] | `0x30` = 48 = string count |
| header[10] | `0xfada` = validity constant |
| header[11] | `0xf0000006` (AREA) / `0xb0000006` (NDMW.AFS) = flags, with the version in the low half |

and the 48 strings are **always the same** `ig*MetaField` type names
(`igIntMetaField` … `igInterfaceDeclarationField`). Only header[0..7] are
file-specific:

| file | header[0..7] |
| --- | --- |
| NDMW.IGB | `100 0b 492 14 15628 8f9 23b4 6c` |
| AREA entry 9 | `12a8 a8 10e4 42 30048 1321 33060 685` |
| NDMW.AFS 179 | `6300 37b 3960 cf f86bc 7105 1b8330 2604` |
| NDMW.AFS 180 | `230 19 914 26 1a80 a6 15c 1e` |

header[0] differs per file (only NDMW.IGB holds `0x100`); header[1..7] are the
per-file sizes and counts of the sections that follow the string table.

## Header (12 × u32, 0x30 bytes)
The words mean the same in every blob. The values below are NDMW.IGB's.

```
0x00  hdr[0]  = 0x100                   [meaning not established]
0x04  hdr[1]  = 0x0b (11)               first object section's record count
0x08  hdr[2]  = 0x492 (1170)            [meaning not established]
0x0c  hdr[3]  = 0x14 (20)               class count
0x10  hdr[4]  = 0x15628                 object stream's byte size
0x14  hdr[5]  = 0x8f9 (2297)            second object section's record count
0x18  hdr[6]  = 0x23b4                  content pool's byte size
0x1c  hdr[7]  = 0x6c (108)              memory block count
0x20  hdr[8]  = 0x656                   offset to the interface name ("igInterfaceDeclarationField")
0x24  hdr[9]  = 48                      string count
0x28  hdr[10] = 0xfada                  validity constant
0x2c  hdr[11] = 0xf0000006              flags, with the version in the low half
```

Note: `AREA.AFS` entry 9 has the **same** `0x20..0x2c` tail
(`{0x656, 0x30, 0xfada, 0xf0000006}`) — the head (8 u32s) is file-specific.

## NDMW.IGB = the asset manifest
`NDMW.IGB` is a master list of every sub-IGB asset file. Extracted `.igb`
names (~1000+, from a full ASCII scan) include:
- `w_*.igb` — weapon models (`w_arm01..07`, `w_axe01..06`, `w_katana01..06`,
  `w_sword01..06`, `w_gun01..08`, `w_maul`, `w_saber`, `w_cutlas`, `w_dagger`,
  `w_glave`, `w_sp0203`, `w_common01..07`)
- `m_*.igb` / `p_*.igb` / `q_*.igb` / `s_*.igb` — digimon models
  (`m_dorumon`, `p_agumon`, `q_vmon`, `s_wargrey`, … ~17 species ×4 variants)
- `dng*.igb` / `stag*.igb` / `ldg*.igb` — dungeon/stage/level geometry
- `e_*.igb` — enemies (`e_arachne`, `e_skulgrey`, `e_tonogeko`, `e_torta`)
- `*_pack.igb` — language packs (`usa_pack`, `eng_pack`, `jpn_pack`, …)
- `aaacamera.igb`, `generator{h,n,v}.igb`, `lh_pack`/`ls_pack`, `bectext.igb`

The sub-IGB files themselves are **not** on the disc as loose files — they live
inside `NDMW.AFS` / `AREA.AFS` entries (the manifest maps logical `.igb` names
to AFS locations).

## String table
Immediately after the 0x30-byte header:
```
count × { u32 len, u32=1, u32=0 }     // 12-byte descriptors (len = strlen+1)
then  count concatenated null-terminated strings
```
`len` includes the NUL. `f1=1`/`f2=0` are constant (type/flags). In NDMW.IGB the
48 strings are the `ig*MetaField` type names (`igIntMetaField`,
`igStringArrayMetaField`, …, `igInterfaceDeclarationField`).

## Type directory
A list of `{null-terminated type name}{6-byte field descriptors}` records (**not**
`u32` descriptors — see §"Field descriptor encoding" below; the earlier "small
u32s" reading was one half of the mis-parse). Names
seen: `igObjectDirEntry`, `igMemoryDirEntry`, `igExternalDirEntry`,
`igExternalImageEntry`, `igExternalIndexedEntry`, `igExternalInfoEntry`,
`beNDMWAfsSetupData`, `igInfo`, `beNDMWAfsSetupInfo`, `igFileName`,
`igAdxAfsFile`, `igDataList`, `igObjectList`, … There is one record per class, so
the walked count equals `hdr[3]` (207 in NDMW.AFS entry 179). No header word is
known to point at the directory: `scripts/igb_inst.py` finds it by its opening
`igObject` record (at `0x1a3a` in entry 179, `0xd02` in the AREA `0x12a8` pack).

### Blob header field map

The header words are sizes and counts, and they mean the same whatever `hdr[0]` holds
(§"The object section headers"):

| blob | hdr[1] | hdr[3] | hdr[4] | hdr[5] | hdr[6] | hdr[7] |
| --- | --- | --- | --- | --- | --- | --- |
| meaning | section 1 records | classes | object stream bytes | section 2 records | content pool bytes | memory blocks |
| NDMW.AFS entry 179 (`0x6300`) | `0x37b` | `0xcf` | `0xf86bc` | `0x7105` | `0x1b8330` | `0x2604` |
| AREA.AFS level pack (`0x12a8`) | `0xa8` | `0x42` | `0x34420` | `0x134d` | `0x33060` | `0x685` |

None of `hdr[4..7]` is an offset. `hdr[5] + hdr[7]` is the pack's id count: the remap
table's `{tableBytes}{idCount}` prefix built from that sum is present in NDMW.IGB and in
all 2,272 igBinary blobs of the two archives.

### Field descriptor encoding — structure and semantics recovered

The old reading (`{u8 a, 0x00, u8 b, 0x00}` = two u16 `{X,Y}`) was a mis-parse. The
type directory is `{ NUL-terminated type name }{ u16 descriptors… }`, with the
descriptor block starting at the **next even offset after the NUL** (not 4-byte
aligned) and each descriptor being **three u16 = 6 bytes**:

```
u16 type_id    index into the blob's 48-name ig*MetaField table
                (0 igObjectRef, 1 igInt, 2 igBool, 6 igEnum, 16 igFloat,
                 36 igVec3f, 38 igVec4f, …)
u16 ordinal    1-based slot index in the class's flattened field-slot list
                (inherited base slots first — see §"ordinal → byte offset")
u16 size       the field's declared element size (4 int/float/ref, 2 short, 12 vec3f, 16 vec4f, …;
                NOT the slot stride)
```

This is confirmed three ways: the `size` value is a **pure function of the type id**
(observed constant per type across the whole directory — `igObjectRef`/`igInt`/
`igString`/`igEnum`/`igMemoryRef`/`igUnsignedInt` 4, `igUnsignedCharArray` 3,
`igBool`/`igUnsignedChar` 1, `igShort` 2, `igLong`/`igDouble` 8, `igVec3f` 12,
`igVec4f` 16, `igMatrix44f` 64, and large defaults for the array types
`igIntArray` 128 / `igFloatArray` 768) rather than free-form per field, the type ids
match the `ig*MetaField` names, and the loader's parser (`FUN_002e63e0`) walks the
block with a **3-short stride** (`iStack_40 = 3`), taking `[1]` as the slot index (it
adds a per-class base-table short to it, so `[1]` is *not* a finished byte offset) and
`[2]` as the field's size (`*(short *)(field + 5) = psVar19[2]`).

Worked example — `igLightAttr` (block at `0x3472` in the NDMW.AFS `0x6300` pack):

```
(17, 2,  2) (6, 4,  4) (36, 6, 12) (38, 7, 16) (38, 8, 16) (38, 9, 16)
(36,10,12) (16,11,  4) (16,12, 4) (36,13,12) (16,14, 4) (36,15,12) (36,16,12)
```

Reading `(type, ordinal, size)`: `igShort@2/2`, `igEnum@4/4`, `igVec3f@6/12`,
`igVec4f@7..9/16`, `igVec3f@10/12`, `igFloat@11,12/4`, `igVec3f@13/12`,
`igFloat@14/4`, `igVec3f@15,16/12` — which is the reflection field list
(`_lightType` enum, `_position` vec3f, `_ambient/_diffuse/_specular` vec4f, …) in
order.

Record framing: each record is `{NUL-terminated type name}` padded to the next
**even** offset, followed by N triples. No count is stored: N is only recoverable
from where the next record's name starts. The NDMW `0x6300` pack's chain is **135
records / 700 triples in `0x2604..0x4032`**, and every triple in every one of them
decodes to a `type_id < 48` with the size that type always has — which is what fixes
the framing.

At `0x4032` the region changes structure: `{u32 336, u32 46}` then the igMemory
type-name pool — 46 names, `Bootstrap`, `Default`, `Current`, `NonTracked`, `System`,
`MetaData`, `String`, `Fast`, `List`, `Temporary`, `Vertex`, `RenderList`, `Texture`,
`Application`, `World`, `Actor`, … , `User0`…`User15` — and after that a table of
32-byte records `<u32 kind, u32 0x20|0x14, u32 0, u32 value, u32 flags, u32 1,
0xffffffff, 0xffffffff>`. Those pool names are identifier-shaped, so a walk that
does **not** validate its triples reads them as records and swallows them: that is
how an earlier version of this page reported 141 records with 45 bad triples, and a
still earlier one reported 179. `scripts/igb_dir.py --verify` validates as it walks
and reports the real boundary.

### `ordinal` → byte offset (resolved)

`ordinal` is the field's **1-based slot index in the class's flattened field-slot
list**: inherited base slots first, then the class's own declared fields in
declaration order. Concretely, for a class whose declared field list is `f[0..n)`:

```
ordinal(descriptor for f[i])  ==  i + K + 1      (K = the class's inherited base-slot count)
```

**A descriptor with `ordinal <= K` is an inherited-slot marker** and corresponds to
no declared field of the class — that is the loader's `"fakeField"`/`"Generated"`
case. Testing therefore has to exclude those first; matching them against real
declared fields is what makes the rule look broken.

The test is: search `K` per class and require every descriptor with `ordinal > K` to
match a distinct declared field, by `ig*MetaField` type, in strictly increasing
declared-index order, with `ordinal - 1 - declaredIndex == K`. Of the 135 records from `0x2604` on, 93
have reflection fields and **87 satisfy the rule while 6 do not** (K = 1 for 8
classes, 2 for 21, 3 for 30, 4 for 1, 6 for 12, 7 for 4, 9 for 1, 10 for 8, 11 for
2). Of the 87, **48 are confirmed by two or more independently matched descriptors**
and 39 match on a single one, which is weak evidence — so quote 48 as the solid
figure and 87 as "consistent". The 6 non-conformers are greedy type-matching
artefacts (classes that repeat a type, or whose reflection field list is not in slot
order). `scripts/igb_dir.py --reflection data/reflection.json` reproduces all of it.

A declared field with **no** descriptor is fine and does not shift the later
ordinals: `igAnimationCombiner` (K=3) omits declared index 7 (`_hierarchyUpdated`),
so ordinal 11 is simply absent while ordinals 12…17 still map to indices 8…13.

The **byte offset is not encoded in the descriptor at all** — it is the class's
declared field offset, i.e. exactly the `offset` already in `data/reflection.json`.
The loader reaches it arithmetically (`descriptor[1] + shortTable[record[4]] -
classBase`, `FUN_002e63e0`) because at runtime it has the reflection tables; the
on-disc directory does not need to carry it. So for reading object data, take the
offsets from the reflection dump and use the directory only to learn *which*
classes and which declared fields are present.

Worked checks:

| class | descriptor ordinals | declared indices | K |
| --- | --- | --- | --- |
| `igLightAttr` | 4,6,7,8,9,10,11,12,13,14,15,16 | 0,2,3,4,5,6,7,8,9,10,11,12 | 3 |
| `igViewportAttr` | 4,5,6,7,9,10 | 0,1,2,3,5,6 | 3 |
| `igImage` | 2…22 | 0…20 | 1 |
| `igAnimationCombiner` | 4…10,12…17 | 0…6,8…13 | 3 |

`igViewportAttr` is the clean illustration of the omitted field: `_scissorExt`
(declared index 4, `igObjectRef`) has **no descriptor**, and its slot is exactly
ordinal 8 — the gap between the ordinals 7 and 9 that *are* present.

### Descriptors that match no declared field = inherited slots

Descriptors with `ordinal <= K` match no declared field of the class by
construction: they are **inherited-slot markers**, not unknown fields — the slot
belongs to a base class, whose own declaration already describes it. There are 203
of them in the verified chain: `igObjectRef` 53, `igString` 50, `igInt` 44, `igBool`
24, `igShort` 23, then a scatter of vectors and longs. (An earlier revision of this
page called them "overwhelmingly `igShortMetaField`" — that was an artefact of
matching before excluding inherited slots, which left `igShort` as the residue.) The
`(17, 2, 2)` triple does specifically head `igLightAttr`, `igViewportAttr`,
`igColorAttr`, `igTextureAttr`, …, pointing at one common base class declaring an
`igShort`. This is the loader's `"fakeField"`/`"Generated"`
case. Note the markers carry the *type* of the inherited slot, so a class whose base
contributes an `igString` shows an `igString` marker (`igAnimationCombiner` ord 2)
even though the class declares no such field of its own.

A declared field with no descriptor (`_lightId`, `_vc`, `_changed`, `_cacheable`
for `igLightAttr`) is the mirror image: a *real* slot the directory simply does not
re-state. Note `igLightAttr`'s omitted `_lightId` sits at ordinal 5 — a hole in the
middle of the sequence, so omitting a field does not shift later ordinals.

### `size` is the declared element size, not the stride

The triple's third value is a pure function of the type id — constant per type
across the whole verified chain (`igInt`/`igEnum`/`igMemoryRef`/`igObjectRef`/
`igString`/`igUnsignedInt` 4, `igUnsignedCharArray` 3, `igBool`/`igUnsignedChar`
1, `igShort` 2, `igLong`/`igDouble` 8, `igVec3f` 12, `igVec4f` 16, `igMatrix44f` 64,
and larger defaults for the array types — `igIntArray` 128, `igFloatArray` 768). It is
**not** the slot stride, and stride is not uniform: `igImage`'s two bools have size
1 but 4-byte strides (offsets 60→64, 80→84), while `igColorMaskAttr`'s four bools
have size 1 and 1-byte strides (12,13,14,15). Stride comes from the class's declared
layout, which is why the declared reflection offsets are the layout of record.

## File references
Records shaped like `{ … u32 strlen, u32=0x28, u32=0x10, "name.igb\0", … }`,
naming the sub-IGB files referenced by the manifest.

## The instance encoding — the object data (decoded)

### The object section headers

A blob carries **two object sections**, and the twelve-word header states both counts. They are not
"the object count" and a small side section — both are real record chains, in file order, and a pack's
id window spans their concatenation.

| header word | meaning | entry 622 | entry 183 | entry 621 | entry 140 |
| --- | --- | --- | --- | --- | --- |
| `hdr[1]` | **first** object section's record count | 50 | 33 | 1,122 | 6 |
| `hdr[3]` | the class count | 28 | 28 | 219 | 15 |
| `hdr[4]` | the object stream's **byte size** | 40,492 (decoded) | 8,608 (decoded) | 1,354,896 | — |
| `hdr[5]` | **second** object section's record count | 1,206 (decoded) | 266 (decoded) | 38,135 | 5 |
| `hdr[6]` | the content pool's **byte size** | 7,112 (decoded) | 1,656 (decoded) | — | — |
| `hdr[7]` | the **memory block** count (§*References are pack-local ids*) | 228 | 62 | 12,362 | 2 |

`scripts/igb_sections.py` prints both and checks them against the decoded chains; five blobs agree, and
on entry 140 the "first" section is the larger one (6 vs 5), so the two are section slots, not a
main/secondary ranking. **What they hold is fixed:** section 1 (`hdr[1]`) is the **memory/object
directory** — `igMemoryDirEntry` + `igObjectDirEntry` — and section 2 (`hdr[5]`) carries the pack's game
objects. Measured across packs: entry 622 = dir 50 (36 mem + 14 obj) / objects 1,206; 183 = 33 (19+14) /
266; 621 = 1,122 (813+309) / 38,135; 140 = 6 (2+4) / 5; 179 = 891 (627+264) / 28,933. The loader reads
the `hdr[1]` (directory) section first.

The loader parses these in `FUN_002e6090` (read off the disassembly), which maps `hdr[0]→ctx+0x7c`,
**`hdr[1]→ctx+0x70`**, `hdr[2]→ctx+0x84`, `hdr[3]→ctx+0x80`, `hdr[4]→ctx+0x94`, `hdr[5]→ctx+0x90`,
`hdr[6]→ctx+0x9c`, `hdr[7]→ctx+0x98`, `hdr[8]→ctx+0x8c`, `hdr[9]→ctx+0x88`, checks `hdr[10]` as the
validity constant (`0xfada`, against `ctx+0x60`) and takes `hdr[11]`'s low half as the version
(required < 8; its flag bits land in `ctx+0xd4/0xd5/0xd6/0xd7`, `ctx+0x124`, `ctx+0xd8`). The header is
read from **file offset 0** — the validity word is `s1+0x28`, which is `hdr[10]` only if the buffer is
the file start. The object reader `FUN_002e7390` loops **`ctx+0x70`**, i.e. it reads the `hdr[1]`
section (entry 622's 50-record chain); the `hdr[5]` section is read by another reader in the
17-section pipeline.

The section buffer itself comes from `FUN_002e9f30`: `ctx+0x108` = the buffer and **`ctx+0x104` = its
capacity** = `align4(max(ctx+0xa4, the stream's block size, the requested size))` — so `ctx+0x104` is
**not** a section length, and the readers' `cursor = ctx+0x104`, their bounds checks and the
`(ctx+0x104 - cursor) % ctx+0x104` modulo are all buffer arithmetic.

The section at `hdr[4]` is a run of records. This is the encoding:

```
{u32 classIndex}{u32 recordSize}{a value for EVERY descriptor, in ordinal order}
```

* `classIndex` indexes the type directory of §"Type directory" — **0-based, in
directory order** — so the record names its own class. No name lookup is needed.
* `recordSize` is the whole record's length, which makes the decode self-checking:
  a correct decode lands exactly on it.
* there is **no separate name field**. Slot 2 of the descriptor list is the class's
  first slot, and for a named class it is the inherited `igString` name — so the stream
  reads `{classIndex}{recordSize}{strLen}{name bytes}…` and the word that looks like a
  third header word is simply **that string's length**. Classes whose slot 2 is an
  `igInt` — the list/data families (`igVec3fList`, `igFloatList`, `igDataList`, the
  `be*List` types) — have no name at all. (An earlier reading of this page treated the
  word as a header `nameLen` and stored only descriptors with `ordinal > K`; that
  rejected every list record. Storage needs no `K` — the `K` of §"`ordinal` → byte
  offset" is only for *naming* fields.)
* a declared field with no descriptor is simply absent.
* a record's fields are read **by ordinal, not by byte offset**, whenever the class
  serialises a string before them: a long name shifts every later value.

Value widths, all little-endian:

| type | bytes | note |
| --- | --- | --- |
| `igBool`/`igChar`/`igUnsignedChar` | 1 | **padded to 4** — treating them as 1 byte derails the walk |
| `igShort`/`igUnsignedShort` | 2 | padded to 4 |
| `igInt`/`igEnum`/`igFloat`, every reference | 4 | |
| `igLong`/`igDouble` | 8 | |
| `igVec2f` / `igVec3f` / `igVec4f` | 8 / 12 / 16 | `igMatrix44f` 64 |
| any string | `{u32 len}{bytes}` | `len = align4(strlen+1)`, bytes padded to `len`, so `"direct\0"` costs 8 |

### The type id **is** the kind

A descriptor triple's `type_id` is not just a width — it names the value's type, which is what a
loader needs in order to know which values are references (an id the loader turns into a pointer) and which are plain data. `igb_inst.TID2REF` records the map and the bytes confirm it:
over six packs of `NDMW.AFS` **every value of type 0 (`igObjectRef`) is an object id or NULL, and
every value of type 7 (`igMemoryRef`) a pool-block id or NULL — 0.0 % "neither" in both cases**, while
every other type has values outside the id space (floats 88 % "neither", matrices 100 %; `igInt` only
looks like a reference because small integers land in the id range anyway).

    type 0   igObjectRef      an object id -> a pointer
    type 1   igInt            type 4   igString        type 5  igRawRef
    type 7   igMemoryRef      a pool-block id -> a pointer
    type 16  igFloat          type 36  igVec3f         type 40 igMatrix44f      ...

So the reference set is read from each value's own descriptor — no `(class, offset)` table and no
reflection involved — and `scripts/verify_field_kinds.py` re-measures the matrix.

### The content pool: blocks keyed by id, laid out 4-byte aligned

`_data` (and every other `igMemoryRef` field) is the **global id of its pool block**. The content pool
is those blocks concatenated in **id order**, each one starting on a **4-byte boundary**, so a block's
offset is

    pool_start + sum(align4(_memSize) of every igMemoryDirEntry id below it)

`pool_start` is the end of the object section and the ids come from the remap table.
`_memSize` is a byte count that need not be a multiple of 4 — the generator and texture packs are all
multiples of 4, but entry 621 has blocks of 123, 231, 302, 403, 465, 501, 681 … bytes (45 of them odd) —
and the next block starts on the next boundary, so such a block is followed by 1-3 padding bytes.

With the alignment, **`sum(align4(_memSize))` is the pool size exactly on every pack checked**:
entry 622’s 228 blocks sum to 7,112 bytes and `igVec3fList` id 0 decodes to `(-135.0, 71.92, 575.0)`, a
real spawn point; entry 621 accounts for all 3,554,920 bytes; entry 179 for all 1,803,056. The content
pool is therefore **fully** accounted for, and a geometry or texture buffer lands on its own block
start. `scripts/igb_pool.py` reads a block by id (`--id`, `--list`, `--check`, `--image`).

**Two superseded readings, kept because they were believed:** the plain sum left the big model packs
“short by ~141 bytes (621) / ~58 (179)”, read first as a **trailing normal buffer** and then
as a per-id **drift** (`p` rising `15/16 → 20 → 45 → 59 → 141`). Both are the same thing: the
alignment padding. 141 bytes is exactly `Σ(align4 − size)` on 621 — 120 from block type 3 (61 blocks),
16 from type 10 (8), 5 from type 8 (3) — and it is *scattered* along the pool as 1-3 byte pads, not a
short tail. Doing the arithmetic without `align4` is what made the offsets drift; the bytes either side
of `pool + Σ_memSize` being continuous is a stream crossing the padded end.
The texture packs declare only multiples of 4 (1024-byte palettes, `W*H` grids), so their layout is
unaffected.

### References are pack-local ids: the id remap table

**Resolved — the ids are not a load-wide ordinal.** Between the pack's two object sections (section 1,
the memory/object directory, and section 2, the game objects — §*The object section headers*) sits a
**remap table**:

```
{u32 tableBytes}{u32 idCount}    followed by idCount x u16       (tableBytes == 8 + 2*idCount)
```

Each `u16` indexes section 1. An entry that lands on an **`igObjectDirEntry`** is one of the pack's
objects, and the object entries are in **exactly the same order as section 2's records** (verified
class-for-class: 622 1,206/1,206; 621 38,135/38,135; 179 28,933/28,933). An entry that lands on an
**`igMemoryDirEntry`** is a memory block — the `_data` block of a list, and the reason the id space is
bigger than the record count. The **table position is the global id**, so

```
id  ->  the k-th object entry  ->  section-2 record k
```

and every reference in a pack resolves inside that pack's own table. `id = recordIndex + (memory
blocks before it in the table)` — exactly the deterministic-but-not-per-class `id - recordIndex` curve
the earlier passes measured:

| entry | table | ids | objects | memory blocks |
| --- | --- | --- | --- | --- |
| 622 | `+0x1580` | 1,434 | 1,206 | 228 |
| 183 | `+0x1376` | 328 | 266 | 62 |
| 621 | `+0xc2dc` | 50,497 | 38,135 | 12,362 |
| 179 | `+0xa482` | 38,665 | 28,933 | 9,732 |
| 140 | `+0x0c1c` | 7 | 5 | 2 |

**Verified end to end.** Every `igObjectRef` resolves in range and every field maps to exactly one
target class — entry 622: 304 refs, `beGeneraterData._genePosList` -> `igVec3fList` 72/72,
`_playerDataList` -> `beGeneraterPlayerDataList` 72/72, `beGeneraterItemData._dataList` ->
`beGeneraterItemDataOneList` 34/34; entry 621: 26,699 refs, `ParticleTimer.slot7` -> `igNodeList` 161,
`beAction2Data._comList` -> `igNamedObjectList` 739. The live spot-check stands and is now offline:
GENE-00 (record 846, `_pos` `(-117, 72, 609)`) reads `_genePosList` 916, and id 916 is record 845, an
`igVec3fList` whose pool content is exactly that triple.

**What this corrects.** The ids *did* reach ~1,430 against 1,206 records, but the gap is the
pack's own memory blocks, not earlier packs: the id space is pack-local and 0-based. So no load replay,
manifest or section list is needed. The conversion mechanism is unchanged — `igObjectRef`'s `0xcc`
reader (`FUN_003034e0` -> `FUN_00305580`) resolves the id with `FUN_002d7e90(list, id) =
*(*(list+0x10) + id*4)` and takes `+0x18`, and `FUN_002e7640` is where the loader builds that list from
the table. `scripts/igb_ids.py` reads it (`--id N`, `--check-refs`).

An object id cannot be told from an arena handle by range (ids reach 50,497 in a 5 MB arena), so a
reader must know which of the two it holds.

**Method note for the earlier failures.** What looked like a "load-wide creation ordinal" was the table
read as if it were the record order: the object entries *are* the record order, but the interleaved
memory entries shift every id. That is why a constant base, a rotation, a live rank and an arena offset
all missed, and why the "extras" grew with position — they are the memory blocks, in table order.

### The loader side: where the ids are built

The chain is mapped:

```
FUN_002e95e0   17-section dispatch pipeline
  |-- FUN_002e7390 / FUN_002e79a0   read ONE object section into ctx+0x28 (version >= 4 / < 4)
  |     \-- FUN_002e7100            reads ONE object
  |          \-- FUN_002fff90 / FUN_00300250   walk the class's field list
  |               \-- FUN_002fc740  = MetaField::vfunc_0xcc(field, object + field[2], cursor + 4)
  \-- FUN_002e7640 / FUN_002e78b0   build the GLOBAL object list ctx+0x8/ctx+0x10 from the remap table
```

* `FUN_002e7100` takes the cursor at `*(ctx+0x108) + *(ctx+0x50)` and its **first word is the class
  index**, resolved through the same class list `igb_dir.py` decodes (`*(ctx+0xc0)`). It does **not**
  read the file's `recordSize` — the length comes back from the field reader, and the cursor then
  advances by that plus `4 * *(ctx+0xd8)`.
* `FUN_002e7390` reads a section into `ctx+0x28` (`list[i] = obj`, one per loop iteration). That is the
  **section list the remap table indexes** — not the id space. `FUN_002e7640` then reads the table and
  fills `ctx+0x10`, which is the list `FUN_002d7e90` indexes by id (§*References are pack-local ids*).
* `FUN_002fc740` gives two useful facts on the way past: a field's **byte offset in the object is
  `field[2]`** (word 2 of the field object), and the **per-type value reader is
  `MetaField::vfunc_0xcc`**. Fields whose flag byte at `field+0x25` is set read **no** value — the
  runtime form of the directory's "declared field with no descriptor".

So the id is a direct index into the loader context's global list (`ctx+0x10`, count `ctx+0x8`), which
`FUN_002e7640` builds from the file's remap table and `FUN_00305580` reads through `FUN_002d7e90`;
`FUN_002e8a40` clears the per-file context on the way out.

### MetaField vtables and the value readers

MetaField vtables have no RTTI record (0 of 478 in the dump), and the field objects are built at runtime
by the registrar, not statically: `beGeneraterData`'s `field_table` `0x4c69f0` holds pointers to field
*names*, not to field objects. So read the vtables off a live class: MetaObject -> `_metaFields` (+40) ->
container data (+8) and count (+0xc) -> each field object's word 0. For `beGeneraterData` this gives:

| Field type | Vtable |
| --- | --- |
| `igObjectRef` | `0x532c80` |
| `igString` | `0x533180` |
| `igFloat` | `0x52ff50` |
| `igBool` | `0x531540` |
| `igInt` | `0x532670` |
| vec3f | `0x5274e0` |
| `_refCount`, `_memPoolIndex` | `0x533430` |

Do not use `0x52f230`, the vtable reached from the registrar's getter `0x2bd000`: live field objects do not
carry it, and it makes object refs look copied raw, which they are not.

Slot `0xcc` reads a value and slot `0xd0` byte-swaps it. Scalars use `igMetaField_ReadRawFieldMem`
(`0x2fc7c0`), a plain `_size`-byte copy, and `igMetaField_SwapBytes` (`0x2fd170`). `igObjectRef` and
`igString` override `0xcc`. `igObjectRefMetaField::vfunc_51` (`0x3034e0`) calls
`igRefMetaField_ReadRawFieldMem` (`0x305580`), which stores NULL when the context is null or the id is -1,
otherwise resolves the id, and then increments the referenced object's refcount at +4. `ctx+0x130` is
unrelated to references: it is the 46 memory-pool objects, used for per-object pool assignment after each
read.

### Identifying which pack a running game loaded

The authored generator fields (`_geneEnemyId`, `_startData`, `_startModeStr`,
`_fillModeStr`, `_callLua`, `_genePosIsGlobal`) form a fingerprint that is unique across the
archive: indexing all 5,901 generator records in the 143 `NDMW.AFS` packs that carry
generator classes, the live `pre-leomon` (`stag0102`) generator reading `_geneEnemyId` 36 /
`_startData` 150.0 / `"direct"` / `"wipeout"` / no `_callLua` / global 1 matches exactly one
record — `GENE-00` at `+0x8820` in **entry 622**. That pack's chain holds **72** generators
and the live world has 72 live `beGeneraterData` instances, so it is `stag0102`'s.
`_pos` must **not** be used as a fingerprint: the runtime rewrites it (§above). Note the
packs come in triples of identical size (183/184/185, 622/623/624, …) — the row-tier variants of a stage's
generator pack, not language copies; see [`enemy-spawn-system.md`](../systems/enemy-spawn-system.md).

### Looking back at the load-level replay (tracker T14) — closed

The replay is not needed. The ids resolve from the pack's own remap table (§*References are pack-local
ids*), so a pack's generator rows, drop rows, spawn positions/rotations **and now every object-to-object
binding** read offline. The load-level facts recovered on the way stay true and useful — the two object
sections (`hdr[1]` directory / `hdr[5]` objects), the loader's header->context map, `beFileListInfo`
(entry 140) naming a stage's pack pair, `FUN_002e7390`/`FUN_002e7640` — but the "section list and its
order" and the manifest were only ever a route to a base that the table already states.
### Why it reads as a small-integer stream

Records start at a **2-mod-4** file offset, so a u32 read from the section start shows
every value left-shifted by 16 bits. That is the whole of the previous "AREA's stream is
one byte late" and "NDMW opens with a small-integer run" notes — those regions are
record runs read at the wrong alignment, not a different format.

The parity is **per pack, not global**. The stage packs (`NDMW.AFS` 614/621, the AREA packs)
place their records at `2 mod 4`, but the **character model packs** (`common/p_*.igb`, e.g.
`NDMW.AFS` entry 861, the player) place theirs at the *other* parity — entry 861's first
record is at `+0x260f`, an odd offset. A chain finder therefore has to try every offset
rather than step by two from an even one; `igb_inst.find_chains` scans every byte and counts
a record as a *chain* start only when no other record ends on it. Entry 861
then decodes as section 1 = **215 records at `+0x260f`** and section 2 = **6,184 at `+0x7241`**,
exactly the blob header's `hdr[1]`/`hdr[5]`, and its geometry chain resolves to the player's
three actor LODs.

### The check, and what it has been run on

Because a record states its own size, the decoder verifies itself. Records also tile
with no gaps — an object's referenced children are stored as records right alongside —
so the walk is a **chain**: a record that fails to decode ends the region, it never
starts a gap.

* **NDMW.AFS entry 183** — a stage pack whose directory contains the `beGenerater*`
  classes — decodes as **one chain of 266 records, every one landing exactly on its own
  `recordSize`**, 8,608 bytes from `+0x1612` to `+0x37b2`. The pack holds 301 records in
  two chains. The arithmetic is not fitted to the data: `beGeneraterData` = 8 (header) +
  12 (`{u32 8}` + `"GENE-01\0"`) + 84 (vec3f 12 + bool 4 + objref 4 + objref 4 + int 4 +
  empty string 4 + `"direct"` 12 + float 4 + `"wipeout"` 12 + float 4 + `"gene01.lua"`
  16 + objref 4) = **104**, the size the file states; `beGeneraterItemDataOne` = 8 + 12 +
  12 = **32**; `igAnimation` = 8 + 8 (a 4-byte length + `"guard01\0"`) + 48 = **64**.
  The decoded graph is the whole spawn system: 1 `beGeneraterDataList`,
  12 `beGeneraterData`, 12 `beGeneraterPlayerDataList`, 11 `beGeneraterPlayerData`,
  12 `beGeneraterInfoRam`, 12 `igVec3fList`, 6 `igFloatList`, and the drop rows
  (7 `beGeneraterItemData`, 7 `beGeneraterItemDataOneList`, 22 `beGeneraterItemDataList`,
  161 `beGeneraterItemDataOne`).
* **NDMW.AFS entry 179** (the `0x6300` stage pack) — 207 classes and a chain of **28,933 records**
  (1,017,532 bytes); the pre-fix walk stopped at 891. Its biggest classes are the
  `igMemoryDirEntry`/`igObjectDirEntry` tables and the stage's own `igNodeList`/`igAttrList`
  objects (3,081 / 1,856).
* **NDMW.AFS entry 861** (`common/p_susanoo.igb`, the player model) — the character-model
  alignment: records begin at an **odd** offset and the two object sections decode as 215 +
  6,184 records, equal to `hdr[1]`/`hdr[5]`. Following the geometry chain from it yields the
  player's three actor LODs (`P_susanoo_Skin0Shape0/1/2`;
  `docs/engine/model-pack-861-attributes.tsv`).

What it makes readable with no emulator and no running game: the per-stage **generator
rows** (`_pos`, `_geneEnemyId`, `_startModeStr`/`_fillModeStr`, the frame timer
`_startData`, `_callLua` per GENE-xx/GBOX-xx entry), the **drop rows**
(`beGeneraterItemDataOne._id`/`_rank`/`_rate`, one per category), the **spawn positions and
rotations** and every other list's contents (the content pool, `--lists`) — D1 and D2 in
the tracker. The decoded field set and the `"direct"`/`"wipeout"` values match the live
`beGeneraterData` reads exactly, and the pool was verified cell-for-cell
against the running game.

Tool: `scripts/igb_inst.py` (`--blob`, `--class`, `--slot`, `--pool`, `--lists`, `--json`;
the size check is the walk itself).

### The stage model packs — what "resident" means

A stage is delivered as a **pair of `NDMW.AFS` entries**, listed by that stage's
`beFileListInfo` manifest (entries 137–177; e.g. `stag0102` = `{620, 621}`, Mummy Desert
`stag0201` = `{641, 642}`). The smaller entry is the stage's **sound + SE pack**
(`beSeData`, `beSoundData`, `beCriSfpData` — the `e_*.sfp` banks, decoded in
[`sound-format.md`](sound-format.md)); the bigger one is its
**model/setup pack**, which carries the geometry, textures, animation and the per-model
registry. The model/setup pack is identified by **content**, not by the log name: it is the one
holding `beModelCtrlInfo` / `igGeometry` / `igVertexArray` and the stage's enemy textures
(`E_goburi01.png` in 621, `E_mummy01.png` in 642). The separately-named `lh_pack.igb` /
`ls_pack.igb` leaves in the `NDMW.IGB` tree are **texture packs** (`beTextureCtrlData` /
`igTextureAttr`, no models), so the `stag<id>/separate/LH_pack.igb` log line is not by itself
proof of which entry carries the models — the class content is.

**The resident-model registry is the pack's `beModelCtrlInfo` records**, one per model,
named by the model string: `stag0102` (621) has 147, of which the enemies are `e_goburi`,
`e_ogre`, `e_blosso`; `stag0201` (642) has 146, enemies `e_mecha2`, `e_mummy`, `e_tyrano`.
The parallel per-model tables agree exactly — `beAction2Info`, `igAnimationDatabase`,
`beShadow01Info`, `beHitLandDelivInfo` — and the assets are the `igGeometry` / `igImage` /
`igSkeleton` / `igAnimation` records in the same pack (`gobr_skinShape2`, `E_goburi01.png`
in 621; `E_mummy01.png` in 642). **The boundary is pack membership, not a name table:** the
name `e_mummy` is present in *both* packs, but only as a row of the global 986-entry
`beAsTargetModelData` table; 621 has no `beModelCtrlInfo e_mummy` and no mummy asset —
exactly the "row latches, geometry lookup finds nothing" behaviour. Making a
model spawn in a stage it was not authored for therefore means porting its records into
that pack — a content edit (copy the subgraph, or overwrite a resident model's assets), not
a spawn-row change.

#### Decoding the big model packs — three corrections to the walker

The model packs are where the earlier decoder silently stopped early; each fix is general:

1. **The width of a value is the descriptor's, not a global table's.** The type directory
   states `{type, ordinal, size}` per descriptor, and `size` varies per pack for at least
   type 13 (4 bytes in the small stage packs, 8 in the model packs). Advancing by a
   hard-coded per-type width mis-aligned the record and ended the directory walk at a
   *suffix* of the class list (82 of 219). Advance by `align4(size)`, with strings
   length-prefixed.
2. **An empty string is legal** (`{u32 0}`, four bytes, no payload) — `igImage`'s trailing
   name slot is one, and rejecting it broke the chain.
3. **The last class has nothing to delimit it.** The walk finds a record's end by the next
   class name at `align2(name)+6N`; the final class's triples run straight into the
   `igMemory` type-name pool, which has no 6-aligned name. Emit its valid prefix and stop.
   With this, the walked class count equals `hdr[3]` on every pack tested (620→29, 622→28,
   621→219, 642→217).

`scripts/igb_inst.py` carries all three, and re-decodes the other packs without losing anything
(183 still 266 records, 620 617, 622 1,206 / 72 generators / 772 drop rows, NDMW.IGB 2,297) while
**entry 179 improves from an 891-record longest chain to 28,933**. The two model packs decode
**exactly against their own headers**: 621 is a single chain of **38,135 records / 1,354,896 bytes**
(= `hdr[5]`/`hdr[4]`), 642 of **35,144 / 1,239,672**.

### Still unread

Nothing structural. Every record's fields decode, every list's contents decode, and
every `igObjectRef` resolves through the pack's own remap table. What is left is
semantic: naming the classes and fields that are not in `reflection.json`, and the
pack-to-stage mapping (`beFileListInfo`, entry 140).

## Next steps (to reach the item/enemy stats)

Steps 1 and 2 are done. What remains is the object data.

1. ~~Map `ordinal` → byte offset.~~ **Resolved** — the offset is
   the class's declared offset from `data/reflection.json`; `ordinal` is the
   flattened slot index and `ordinal = i + K + 1` for declared field `f[i]`.
2. ~~Explain the omitted fields.~~ **Resolved** — a descriptor with no declared
   field is an inherited-slot marker (203 of them, all with `ordinal <= K`, and set
   out by type in §"Descriptors that match no declared field"); a declared field with no descriptor is just a slot the
   directory does not re-state. Omitting one leaves a hole and does not shift later
   ordinals.
3. ~~Walk the object graph~~ **Resolved** — §"The instance encoding": the
   section at `hdr[4]` is `{classIndex, recordSize, nameLen}{name}{fields in descriptor
   order}`, decoded and size-verified by `scripts/igb_inst.py`. Still unread: the
   `igObjectRef` reference encoding that reaches the sub-objects.

   *How the region was misread before — kept as the record of a wrong turn.* The reads
   looked shifted because **records begin at a 2-mod-4 offset**, so a u32 read from the
   section start shows each value 16 bits too high. "AREA's stream is one byte late" was
   that, read at `+1`; "NDMW opens with a small-integer run" was the same record stream
   read at the wrong alignment, which is why the `0x7f30..0x815f` values looked
   unexplained (they are a record's `classIndex`/`recordSize` words). No alignment tag
   and no non-u32 section were involved. `hdr[5]` is a record count, not an offset to
   such a section.
4. **Locate and validate** the databases (`beBaseInfoData` ×667 in `AREA.AFS`,
   `beNDMWStatusInfo` ×88 in `NDMW.AFS`). Goburimon HP ≈ 200–600 is the anchor
   (see [`../systems/enemy-data.md`](../systems/enemy-data.md)).
   **Caveat:** these two classes carry no usable field list in
   `data/reflection.json` (`beNDMWStatusInfo` has 0 fields, `beBaseInfoData` only
   `_version` @12), and their igBinary directory records list a couple of
   descriptors each — so the hp/mhp/… layout must be recovered from the stat-name
   xrefs or by fitting the instances, **not** from the reflection dump.

## What didn't work

- **`hdr[0]` as a blob's cumulative object count.** It reads 1,432 on entry 622, close to that pack's 1,434
  ids, but 32,196 on entry 621, below `hdr[1]` + `hdr[5]` = 39,257. On the object packs its meaning is not
  established.
