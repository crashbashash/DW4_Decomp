# The port's asset layer

Native readers for the game's own asset containers, written for the **source-level retarget** — the
native-port goal of the Digimon World 4 reverse-engineering project (the project plan is kept with the
decompilation work, not here).

This tree is separate from the decompilation repository
([`crashbashash/DW4_Decomp`](https://github.com/crashbashash/DW4_Decomp)) on purpose: that repository is
the recovered *knowledge* — the binary, the formats, the metadata, and the Python decoders that
recovered them — and this is *port code* that consumes it.

To run the port or its tests on a new machine, extract the disc files from a USA ISO with `tools/extract_iso.py` and profile
frame cost with `tools/profile_live.py`; see [setting up a machine](docs/README.md#setting-up-a-machine-from-a-disc-image) and
[performance profiling](docs/README.md#performance-profiling).

The title's Options settings persist in `config.ini` under the per-user
configuration directory. `--portable` stores it in `userdata/config` beside the
executable. See [Options configuration](docs/configuration.md) for the INI schema,
paths, write behavior and checks.

## Where a buffer lives (offline)

An `igBinary` reference is not a host pointer and does not need a running game:

* an **`igObjectRef`** (a field the reflection calls a reference) is a **global id**, and the id
  indexes the pack's own **remap table** — `{u32 tableBytes}{u32 idCount}` plus `idCount` u16, sitting
  between the blob's two object sections. Object entries are the pack's objects in exactly the second
  section's record order; memory entries are the objects' pool blocks;
* an **`igMemoryRef`** value (a list's `_data`, `igImage._pImage`, `igClut._pData`, a geometry buffer)
  is the **global id of its pool block**, and the content pool is those blocks concatenated in id
  order with **every block placed on a 4-byte boundary** — so
  `offset = pool_start + sum(align4(_memSize) of every igMemoryDirEntry id below it)`. `_memSize` need
  not be a multiple of 4 (entry 621 has 45 odd-sized blocks), and such a block is followed by 1-3
  padding bytes. That alignment is what makes the accounting exact: `sum(align4(_memSize))` is the pool
  size on every pack checked (621: 3,554,920; 179: 1,803,056; 622: 7,112) — the ~141-byte residual
  a plain sum leaves on the model packs *is* this padding.

So a native loader can resolve an object reference and locate its bytes from the blob alone; the
reference implementation the port is checked against is `../scripts/igb_ids.py` +
`igb_pool.py`. The reader implements it as `dw4_igb_refs_open()` / `dw4_igb_ref()` /
`dw4_igb_block()` (`include/dw4/igb.h`), driven by the `refs` command, and `make check` diffs its
numbers against the Python tools.

**The pool half:** the block accounting is **exact on both pack kinds** with the
4-byte alignment (`sum(align4(_memSize))` is the pool size: 621, 179, 622 all exact). A pack comes
in two kinds: the stage/**object** pack (621 — the object graph, the reference tables this reader
handles, and the `beTextureCtrlAttr` names) and the **texture pack** (625/626/…), whose body is its
own id→class table, a stream of serialised `igImage`/`igClut` records and a flat pool of palettes and
index buffers — the texture *buffers* are in that second kind, not in the object pack.

A texture's name is carried two ways, and in the **texture pack** the `igImage` record's own
`_pNameString` is it (the pack's textures decode by that name); `beTextureCtrlAttr._name`
is how the *object* pack's records name the same textures — entry 621's 96 controller names include all
46 the live session dumped.

## Why a separate reader at all

A source-level retarget can let the engine load its own assets: `igIGBFile_ReadFile` and its callees
are the real implementation, and the plan is to run them over a host `igFile` (P2.3). That path is
worth taking — but it needs the loader decompiled and typed first, and the asset work behind it
(textures, models, audio, FMV) does not. This layer is the part that can be written and verified
*now*:

- it is the executable spec of the container formats, cross-checked against the decompilation repo's Python decoders;
- it unblocks P3.4–P3.6 (textures/models/audio) without waiting on the loader;
- when the engine's own loader runs, this becomes the fallback/reference, not a competitor.

## What exists

| file | what |
| --- | --- |
| `include/dw4/afs.h`, `src/afs.c` | CRI **AFS** archive: entry table, `extract`, `entry_data` (`docs/engine/afs-archives.md` in the decompilation repo) |
| `include/dw4/igb.h`, `src/igb.c` | **igBinary** container: header, string table, class-directory walk, instance-record decode, chain scan, and the **reference tables** — the id remap table plus the content-pool block offsets (`docs/engine/igbinary-format.md` in the decompilation repo) |
| `include/dw4/manifest.h`, `src/manifest.c` | the **virtual filesystem**: `NDMW.IGB`'s name → (archive, entry) table |
| `include/dw4/mount.h`, `src/mount.c` | the **asset tree**: the manifest plus both archives, mapped; name → bytes, and a stage's `[pt.entry]` packs resolved |
| `include/dw4/texture.h`, `src/texture.c` | indexed texture decode: 8/4-bit indices + a palette (RGBA8888 or PS2 CSM1) → RGBA8 |
| `include/dw4/igfile.h`, `src/igfile.c` | the **host file seam** (P2.3): a plain file, an AFS entry, a manifest name, or the n-th `[pt.entry]` reference of a stage file — all mapped, none slurped |
| `include/dw4/scene.h`, `src/scene.c` | the **loader**: a pack's ids become 32-bit arena handles, and the geometry is read back through them (`dw4asset scene`) |
| `include/dw4/mesh.h`, `src/mesh.c` | the triangle rule and the OBJ text, shared by the file reader and the loader so the two cannot drift |
| `include/dw4/texpack.h`, `src/texpack.c` | the **texture pack**: record scan, id→class table, the pool layout, and the texture→palette link, so a named texture decodes with no replay (`docs/engine/texture-packs.md` in the decompilation repo) |
| `include/dw4/models.h`, `src/models.c` | the **model pack**: the geometry chain (`_vertexArray` → `igVertexArray1_1` → stream blocks → `_stripLengths`), the triangle rules and an OBJ writer, so a model extracts with no replay (`docs/engine/model-format.md`) |
| `include/dw4/skin.h`, `src/skin.c` | the **skinned character**: the runtime blend stream (`_blendWeights`/`_blendIndices`), the bone→slot map and the matrix palette, all read from a paused EE RAM dump; `dw4_skin_write_obj` writes the bind or the posed mesh |
| `include/dw4/png.h`, `src/png.c` | a dependency-free PNG writer (stored DEFLATE), so a decode can be looked at |
| `include/dw4/sfp.h`, `src/sfp.c` | CRI **`ps2_` sound banks**: `DTPK`/`TBLD`/`VAGD` chunks, the per-sound entry table, and the VAG ADPCM decoder (`docs/engine/sound-format.md` in the decompilation repo) |
| `include/dw4/wav.h`, `src/wav.c` | a minimal 16-bit PCM WAV writer, so a decoded bank can be compared against ffmpeg and heard |
| `src/dw4asset.c` | the CLI: `afs`, `cat`, `igb`, `records`, `manifest`, `find`, `mount`, `scan`, `media`, `texture`, `texpack`, `models`, `scene`, `render`, `livetex`, `skin`, `sfp` |
| `tools/crosscheck.sh` | runs the C reader and the decompilation repo's Python decoders over the real archives and diffs the numbers; also drives `verify_texture.py`, `verify_texpack.py` and `verify_sound.py` |
| `tools/verify_texture.py` | pixel-exact test of the texture decode against a reference, plus the failure path |
| `tools/verify_texpack.py` | diffs the C texture-pack reader against `igb_texpack.py` on 6 packs / 117 textures (ids, block offsets, pixels) |
| `tools/verify_models.py` | diffs the C model reader against `igb_models.py` on 4 packs / 1,529 models (stream table, counts, OBJ bytes) |
| `tools/verify_skin.py` | diffs the C skinning path against `scripts/live_skin.py` on a live EE RAM dump: bind **and** posed OBJ bytes identical for every 24-matrix palette (skipped without a dump) |
| `tools/verify_scene.py` | checks the loader against its own contract (every id placed in order, every payload the file's bytes, every handle resolving) and its OBJ output against both the file reader and `igb_models.py` |
| `tools/verify_sound.py` | sample-exact test of the VAG decode against ffmpeg's `adpcm_psx`, plus the bank/entry tables |

The two properties that make the format decodable are implemented as the same self-checks the Python
decoder relies on: the **class-directory walk** validates every `{type, ordinal, size}` triple (no
count is stored — a record's end is the next name that sits at a 6-byte-aligned offset with valid
triples), and a **record decode must land exactly on its own `recordSize`**. A false start is rejected
rather than guessed.

```sh
make                                   # build/dw4asset
make check                             # tools/crosscheck.sh (C vs ../scripts); DW4_LIVEDUMP adds the steps that read a RAM dump

./build/dw4asset afs   /path/NDMW.AFS
./build/dw4asset igb   /path/NDMW.IGB
./build/dw4asset igb --afs /path/NDMW.AFS --entry 621
./build/dw4asset records --afs /path/NDMW.AFS --entry 621 --class beGeneraterData

# the reference tables: an igObjectRef id -> its object, an igMemoryRef id -> its pool block
./build/dw4asset refs --afs /path/NDMW.AFS --entry 622 --check
./build/dw4asset refs --afs /path/NDMW.AFS --entry 622 --id 916          # -> igVec3fList
./build/dw4asset refs --afs /path/NDMW.AFS --entry 622 --id 0 --dump blk.bin

# the virtual filesystem: a name resolves to an archive entry, then to bytes
./build/dw4asset manifest /path/NDMW.IGB
./build/dw4asset find /path/NDMW.IGB /path/to/extracted-nmw-afs stag0102.igb out.igb

# the mounted tree (manifest + both archives, mapped -- cheap on 1.2 GB of archives)
./build/dw4asset mount /path/to/roms ls 'stag01'      # names, archive, entry, size
./build/dw4asset mount /path/to/roms cat stag0102.igb out.igb
./build/dw4asset mount /path/to/roms refs stag0102.igb   # its [pt.entry] packs, resolved
./build/dw4asset mount /path/to/roms check               # every name resolves

# which entries carry a class (a directory walk per entry, ~1.6s for both archives)
./build/dw4asset scan /path/to/roms igImage

# media: the three Sofdec .sfd movies, straight through ffmpeg
./build/dw4asset media /path/to/roms list
./build/dw4asset media /path/to/roms probe aeu_opening.sfd
./build/dw4asset media /path/to/roms convert aeu_opening.sfd out.mp4 -t 10

# the texture decode half, from explicit index + palette bytes
./build/dw4asset texture indices.raw out.png --w 512 --h 512 --bits 8 --pal clut.raw \
    --pal-entries 256 --pal-mode ps2csm1

# a texture pack, offline and end to end: layout, the image -> palette link, decode
./build/dw4asset texpack --afs /path/NDMW.AFS --entry 625
./build/dw4asset texpack --afs /path/NDMW.AFS --entry 625 --list
./build/dw4asset texpack --afs /path/NDMW.AFS --entry 625 --decode BJGR01.png --out bjgr.png

# the live route: a savestate's RAM, trimmed so the readers' 0x00100000 base is right
python3 scripts/livedump.py /path/state.p2s dump.bin     # 31 MB, base 0x00100000
./build/dw4asset livetex dump.bin --list
./build/dw4asset livetex dump.bin --decode E_ogre01.png --out ogre.png

# the sound pack: six CRI ps2_ banks, decoded to WAV
./build/dw4asset sfp --afs /path/NDMW.AFS --entry 620
./build/dw4asset sfp --afs /path/NDMW.AFS --entry 620 --bank 0 --wav e_goburi.wav
./build/dw4asset sfp --afs /path/NDMW.AFS --entry 620 --bank 0 --sound 2 --wav one.wav
```

`DW4_DECOMP` (default `../DW4_Decomp`) points at the decompilation checkout and `DW4_ROMS` (default
`../../local/extracted`) at a directory holding `NDMW.AFS` / `NDMW.IGB` extracted from the disc; both are
overridable so the check runs wherever the trees are.

## The virtual filesystem

`NDMW.IGB` is not only a container: decoded as igBinary it is a 20-class schema, and two
classes carry the filesystem — `beNDMWAfsSetupData` (`_name` `ndmw.afs`/`area.afs`,
`_fileCount` 972/1382) and `igAdxAfsFile` (`_name`, `_ptNumber`, `_fileNumber`, 2,080
records). So **`_ptNumber` 0 = `NDMW.AFS`, 1 = `AREA.AFS`, and `_fileNumber` is the entry
index**: a filename resolves to bytes with no guessing. The manifest names all 1,382 AREA
entries and 697 of NDMW's 972, and the two anchors that check it are known
facts — `(0, 140)` is `stag0102.igb`, and
`(1, 0)` is `aeu_opening.sfd`, an MPEG whose AREA entry 0 starts `00 00 01 ba`.

A **stage** manifest spells its own packs in the same terms: `stag0102.igb` holds the literal
strings `[0.620]/s` and `[0.621]`, where `[<part>.<entry>]` is exactly the pair above. So a stage's packs resolve through this same table:

```
$ dw4asset mount <roms> refs stag0102.igb
stag0102.igb: 2 [pt.entry] reference(s)
  [0.620] @0xc42    -> ndmw.afs   entry 620       494084 bytes
  [0.621] @0xcb2    -> ndmw.afs   entry 621      5060706 bytes
$ dw4asset mount <roms> refs stag0201.igb
  [0.641] @0xc42    -> ndmw.afs   entry 641       346670 bytes
  [0.642] @0xc8a    -> ndmw.afs   entry 642      5173220 bytes
```

So the bare indices the modding work uses are these pairs: `[0.621]` is
NDMW.AFS entry 621 and `[0.642]` is entry 642 — the model pack whose swap was measured live.

## Verified

`make check` — C and Python agree exactly, on

- `NDMW.IGB` (the 106 KB manifest): 20 classes, a 2,297-record chain over 87,592 bytes,
  `+0x2592 .. +0x17bba`;
- `NDMW.AFS` entry 621 (a 5.06 MB model pack): **219 classes, 38,135 records, 1,354,896 bytes,
  `+0x24d6a .. +0x16f9fa`** — the same figures the Python decoder reports;
- the **manifest table**: all **2,080** `name / archive / entry` rows identical to the Python
  decoder's, with `find stag0102.igb` round-tripping to the exact bytes of `NDMW.AFS` entry 140
  (and `aeu_opening.sfd` resolving to `AREA.AFS` entry 0, 40,091,648 bytes starting `00 00 01 ba`);
- the **mounted tree**: **2,079 of 2,080** named files resolve into their archive (the 2,080th is the
  manifest's own `NONE` sentinel, `pt=0 entry=-1`), and the `[pt.entry]` refs of `stag0102.igb` and
  `stag0201.igb` resolve to the sizes the modding work saw — 494,084 / 5,060,706 and 346,670 /
  5,173,220 bytes;
- the **media path**: the 3 `.sfd` movies probe as **MPEG-1 video + ADX audio** inside a CRI Sofdec
  container, and `media convert -t 2` produces an h264/AAC clip ffprobe accepts;
- the **sound path**: `NDMW.AFS` entry 620 (a stage's sound pack) holds **6** `ps2_DTPK`
  banks; the C VAG decoder reproduces ffmpeg's `adpcm_psx` output **sample-for-sample over all
  773,472 samples** of all 6 banks, at 24,000 Hz, the per-sound entry table tiles each bank's chunk
  exactly, and all **33** stage sounds are **named** (`goNATK01`, `ogDEAD01`, `TARU_BLST01`, …) from
  the pack's own `beCriSfpData`/`beSoundData` records;
- the **texture decode**: pixel-exact on synthetic 8-bit RGBA8888 and 4-bit PS2 CSM1 images (69
  pixels across two cases), and it refuses inputs that do not cover the requested size instead of
  reading past them;
- the **texture pack**, end to end and offline: on `NDMW.AFS` entries **625, 626, 618, 619, 632 and
  639** the C reader agrees with `igb_texpack.py` on every texture's ids and **block offsets**, and
  decodes the **117** textures byte-for-byte identically. On entry 625 that decode is also
  **pixel-for-pixel identical to the live dump's PNGs** (26/26 RGB) — see the section below;
- the **model pack**, end to end and offline: on `NDMW.AFS` entries **621, 179 and 642** the C reader
  agrees with `igb_models.py` on every geometry attribute's stream table (1,526 models) and writes
  **OBJ files that are byte-identical**, and all 549 of entry 621's attributes resolve (none skipped).
  At the workspace root `testing/verify_models_offline.py` compares that against the live game's own
  models: **450 of 549 byte-identical** — see *The model pack* below.

Two facts the C reader forced into the open, both worth keeping:

- **the header's meaning is per-file.** `hdr[0]` is `0x00000100` in the manifest and `0x00007dc4` in a
  model pack; only `hdr[3]` (class count) and `hdr[9]` (string count) held across both. The magic is
  reported, not required — the directory walk is the validation.
- **a chain scan must skip whole chains.** Records tile without gaps, so a found chain is maximal;
  re-walking the chain from every later offset takes **30.6 s** on entry 621. Walking
  each offset once — and validating a record without allocating its value array — is **0.22 s** for
  the same answer.

## Where the asset work stops, and why

The container formats are decoded and verified. **Finding the buffers** turns on the same fact in
every case: a memory/object reference in a pack is a **load-time ordinal**, not an offset, so a buffer is located through the pack's own id tables, never
through a file offset. Measured here:

- **Textures.** An `igImage` carries `_px`/`_py`, `_bitsIdx`, `_bytesPerRow`, `_imageSize` and the refs
  `_pImage`/`_pClut` — enough to decode, not to locate. In the packs that hold images (e.g. NDMW entry
  179, 116 `igImage` records) the **chain has no `igMemoryDirEntry` records at all**, so the block list
  is in another section of the pack. The ordinal→block map needs no loader replay: the texture pack
  states its own id space and the port reads it directly (the next section).
- **Sound** is **not** a boundary case: a stage's sound pack is an igBinary container
  whose content pool holds self-contained CRI `ps2_` banks (`DTPK`/`TBLD`/`VAGD`), and each bank's
  ADPCM decodes off-line with no ordinal to resolve. See the sound section below. The
  three movies' audio is separate: it is ADX inside Sofdec, and ffmpeg reads it directly.

## The texture pack: solved offline (`texpack`)

A texture pack needs no loader and no live session, because it **states its own addressing**:

* **the records are serialised igObjects** — `{u32 class}{u32 bytes}` then the class's fields at the
  offsets `data/reflection.json` gives. An `igImage` (class 10) carries `_px`/`_py` (+8/+12),
  `_pfmt` (+44), `_imageSize` (+48), **`_pImage` (+52)** = the grid block's id, `_pClut` (+68) and
  `_pNameString` (+88) = the name. An `igClut` (class 11) carries `_numEntries` (+12), `_stride`
  (+16) and **`_pData` (+20)** = the palette block's id;
* **the pack has an id→class table** — the object packs' `{u32 tableBytes}{u32 idCount}` +
  `idCount × u16` shape, with each entry the **class** of that id. The numbering is pack-local, and the
  table validates itself: one class's ids are exactly the clut blocks and another's exactly the
  `_pClut` values;
* **the pool is the blocks in ascending id order** (`offset = pool_base + sum(smaller ids' sizes)`),
  with `pool_base` and the pad total taken from the header and an image's grid starting one byte into
  its block;
* **`_pClut` is an id, not an offset**: the ids of a class are in creation order (= file order), so
  its *rank* among the ids of its class names the r-th `igClut` record, and that record's `_pData` is
  the palette. That link needs no live session.

```sh
./build/dw4asset texpack --afs NDMW.AFS --entry 625                    # counts, table, pool
./build/dw4asset texpack --afs NDMW.AFS --entry 625 --list             # name, size, ids, offsets
./build/dw4asset texpack --afs NDMW.AFS --entry 625 --decode BJGR01.png --out bjgr.png
```

Checked by `tools/verify_texpack.py` (6 packs, 117 textures, ids + offsets + pixels against
`igb_texpack.py`) and, on entry 625, against the live dump: **26/26 textures pixel-for-pixel**. Open
on this path: the pad *positions* are chosen by a palette-alignment score rather than read (the total
is exact from the header), and the multi-asset packs (646/676/713/720, `AREA.AFS`) are refused rather
than guessed.

## The model pack: solved offline (`models`)

A model pack needs no loader and no live session either — it is the same two facts the texture pack
uses (the ids address the pack, the pool is 4-byte aligned), plus one for the
buffer:

* **the chain is file-derived** — `igGeometryAttr1_5._vertexArray` (+0x0c) is an `igObjectRef` id
  naming an `igVertexArray1_1`, whose **`_vdata` (+0x08) names a block listing this array's streams**
  and whose `_numVerts` (+0x0c) is the count; `_primType` (+0x14) is 3 list / 4 strip, `_numPrims`
  (+0x18) the count, `_stripLengths` (+0x30) an `igPrimLengthArray1_1` whose `_lengthData` (+0x08) is
  the u32 lengths and `_numStrips` (+0x0c) their count. The offsets are the ones
  `data/reflection.json` gives;
* **a stream block's `_memSize` IS its content size** — `12*_numVerts` for the positions,
  `8*_numVerts` for the UVs — so a stream starts at its block's own (aligned) offset
  and needs no search;
* **both links self-validate**, so a wrong offset is a skipped attribute rather than bad geometry: the
  `_vdata` block must list a `12*_numVerts` stream, and the lengths must sum to `_numVerts`;
* **the model's name is in the pack too** — a shape is an `igGeometry` record whose *ordinal-2* value
  is the DCC part name and whose *ordinal-8* value is an `igAttrList`; that list's `_array` block holds
  the shape's attribute ids, so the ones that are geometry attributes take the name (the
  live `M_*Shape` link reached from the file).  Ordinals, not offsets: a record's byte offsets shift
  with the length of its name string.

```sh
./build/dw4asset models --afs NDMW.AFS --entry 621                       # pool + attribute count
./build/dw4asset models --afs NDMW.AFS --entry 621 --list                # mode, counts, streams
./build/dw4asset models --afs NDMW.AFS --entry 621 --out-dir geom/       # model_<name>.obj per model
./build/dw4asset models --afs NDMW.AFS --entry 621 --obj 13842 --out cyl.obj
```

Checked by `tools/verify_models.py` (four packs — 621/179/642 and the player's character pack 861,
1,529 models — where the C and the Python agree on the stream table *and* the **OBJ bytes are
identical**), and by
`testing/verify_models_offline.py` at the workspace root, which compares the offline result against the
live game's own models: **450 of 621's 549 are byte-identical** (the rest are models the live session
never had loaded), and **444 of the 549 attributes carry the pack's own DCC shape name** — 383 of the
386 models the live namer names get the identical name.

## Skinning: the runtime blend stream and the matrix palette (`skin`)

A model pack carries the **bind** pose; the per-vertex blend stream and the pose itself are
runtime-only, so they come from a paused game's EE RAM dump:

* `igVertexArray1_1` — `_blendWeights` (+0x20, f32 per vertex), `_blendIndices` (+0x24, u8 per
  vertex). The pack carries a 4-byte stub here, which is why the geometry alone is bind pose.
* `igBlendMatrixSelect._blendMatrixIndices` (+0x28) — an `igIntList` mapping each **vertex bone** to
  a **matrix slot**.
* `igBlendMatricesAttr._matrixCache` (+0x0c, count +0x10) — the palette: 64-byte `igMatrix44f`,
  **row-major with the translation in elements 12..14**.
* skinning is `v' = M[slot[bone]] * v`; the shipped mesh is one bone per vertex with weight 1.0.

```sh
./build/dw4asset skin <ram.bin> --list
./build/dw4asset skin <ram.bin> --palette 1 --bind bind.obj --out posed.obj
```

`tools/verify_skin.py` runs the C path and `scripts/live_skin.py` over every 24-matrix palette and
requires the bind **and** posed OBJ bytes to be identical (skipped when no dump is present).
**Open:** nothing in the object graph links the mesh/select to *its* palette, so the
palette is chosen by index into the pool rather than resolved — the transform is proven, the pairing
is not.

## The loader: a pack becomes an arena (`scene`)

`dw4asset models` reads a pack; `dw4asset scene` **loads** one, which is the shape the engine's own
loader produces (the loader converts the pack's ids into pointers in a later pass):

```sh
./build/dw4asset scene --stage /path/local/extracted stag0102.igb --ref 1 --check --list
./build/dw4asset scene --stage /path/local/extracted stag0102.igb --ref 1 --out-dir geom/
```

* **one arena, 32-bit handles** — `handle = arena offset` (0 is NULL), so the port keeps the game's
  32-bit reference width (pointer-model option (b), P1.5). Every id's payload is placed in id order
  and the table records where: 12,362 blocks + 38,135 objects = 50,497 ids for the model pack;
* **the loader allocates, so the padding is gone** — the file's 4-byte block alignment
  is a *file* fact; the arena packs densely at a 16-byte alignment and nothing here reads a file
  offset;
* **the route is the game's** — `--stage <roms> stag0102.igb --ref 1` goes manifest → stage file →
  its own `[0.621]` `[pt.entry]` reference, never an archive index;
* **the id -> pointer pass runs** — every `igObjectRef`/`igMemoryRef` value is rewritten from the
  pack's id into a handle, which is what the engine's loader does. Which values those
  are comes from the value's own descriptor: the type id **is** the kind (type 0 is
  always an object id or NULL, type 7 always a pool-block id or NULL, 0.0 % "neither" over 163,482
  values), so there is no `(class, offset)` table and no reflection involved;
* **`--check` states the contract**: every id placed in order exactly once, every **block** payload
  byte-for-byte the file's bytes (50,497 ids, 0 differ — the object records are rewritten on purpose),
  every mesh handle inside the arena, and `id->pointer: 37,816 reference(s) rewritten, 21,875 NULL,
  0 NEITHER`;
* **the meshes are renderer-ready** — a mesh points at the arena's float streams (positions, UVs)
  and carries its triangles, so the renderer never touches a pack.

`tools/verify_scene.py` (in `make check`) checks that contract and then diffs the OBJ output of the
loader, the file reader and `igb_models.py` — **549 meshes, 371 distinct names, byte-identical**.
That closes **arena == file == live** for the model path: the loader's payloads *are* the file's bytes
(asserted id by id), and the file's geometry *is* the live game's (`testing/verify_models_offline.py`
at the workspace root: 450 of 549 byte-identical).

`--graph` walks the **scene graph** on top of that: `igSceneInfo` → `igGraphPathList`
→ `igGraphPath` → its own `igNodeList` → node chains, each node giving its name (a string value), an
`igMatrix44f` (row-major, translation at words 12..14), its children and any `igGeometry` it draws —
found by descriptor *type*, never by a hardcoded class. On entry 621 that is **18 scenes / 99 nodes**
with the game's own names (`Ogremon`, `Goblimon`, `Slope`, `i_bgclear`) and plausible camera chains.
Open: these are the camera/scene-animation chains, so a stage's *objects* are placed elsewhere
(`beModelCtrlNode2`/`beModelCtrlData`).

Deliberately not done: rewriting the **contents of a memory block** (a `_vdata` block holds the ids
of the streams it lists, and the live engine sees pointers there). A block can be shared and the item
kind is a property of the *field* that points at it, so that pass needs its own rule; readers resolve
those items through `dw4_scene_handle()`. Also open on P2.3: an ISO9660 reader, so the port can
run from the disc image rather than a directory of extracted assets.

## The native host: `dw4` (P6.1)

The port builds a native **host executable**, `dw4`, with the engine's own shape — **init → object
graph → per-frame update → present**:

```sh
make                      # builds build/dw4asset and build/dw4
./build/dw4 --roms /path/to/roms --stage stag0102.igb --ref 1 --frames 3 --out-dir /tmp/run
# the placed stage (a live capture) through the game's own camera:
./build/dw4 --roms /path/to/roms --stage stag0102.igb --ref 1 --frames 1 \
    --scene capture.tsv --camera --w 640 --h 448 --out-dir /tmp/run
```

### Framing (`dw4asset render` and `dw4`)

The stage's own camera is in the pack, and using it is what makes a whole-stage frame legible.  The controls, settled:

| flag | meaning |
| --- | --- |
| `--camera [NAME]` | use the loaded pack's `igCamera` node `NAME` (default: the **stage camera**, the first camera whose composed world is not the identity).  Sets the 39.60 deg vertical fov and the 640x448-derived aspect unless `--fov`/`--aspect` override them. |
| `--view 'm0 .. m15'` | a raw row-vector view matrix (its third row is negated internally).  Overrides `--camera`; `--fov`/`--aspect` apply. |
| `--fit` | fit the drawn geometry's own bounds (the default when neither `--camera` nor `--view` is given). |
| `--span N` | draw only geometry within `N` of `--cam` (default: the drawn set's own centre), so a far-flung node cannot shrink the frame.  It is a clip, not a framing control — use `--camera` for framing. |
| `--cam X Y Z` | the `--span` clip-box centre. |

`dw4asset scene --stage <roms> <stage.igb> --ref N --cam` prints the stage camera and every
candidate; `--cam-node NAME` prints one node's chain, world and view.  `tools/verify_render.py`
pins the composed stage camera (pack-only) and, when `--scene` is given, a deterministic framed
render of the placed stage.

### The scene capture and the mesh link

The `--scene TSV` a live capture emits is the *placement* half of a frame; the pack is the
g*geometry* half.  The join between them is **not** the DCC name.  A pack repeats names (entry 614
has 475 named meshes over 290 distinct names -- 35 `polySurfaceShape1`) and its largest meshes are
unnamed, so a name join over-draws every duplicate and drops the stage shell.

`scripts/capture_scene.py --pack <AFS:ENTRY>` closes that: it content-matches each live geometry
attribute to the pack mesh with the *same vertex buffer* (the loader copies the pack bytes, so the
match is exact) and writes the pack's `igGeometryAttr` id as a fifth TSV column.  Both render paths
(`dw4`'s `engine.c`, `dw4asset render`'s `dw4asset.c`) join on that id when the column is present
and fall back to the name when it is not, so a capture without the column still renders.

The stage matters as much as the join: a live capture's dump names the stage it had loaded
(`stag0101` for the Goblin Pass crate/barrel save), and the port must be pointed at that stage's
model pack (`--stage stag0101.igb --ref 1`), not another stage's --.

The stage's **static environment is world-space geometry**.  Of the 832 live
`igGeometry` shapes, 117 have no usable matrix in their `igTransform` parent chain, and their pack
meshes are authored at stage coordinates (the player at `(421.83,72,-110.07)` sits inside them), so
identity is their placement.  `capture_scene.py --keep-unplaced` emits them instead of dropping them,
and the recovered view (`fov 0.6912`, aspect `0.7*w/h`) puts the dome mesh (pack 614 id 48646) on
the real frame's floor boundary.  Two things the `igGeometryAttr` walk does not reach and which the
model-controller graph does: the band mesh (id 21835, visible in the frame but matching no live
`igGeometryAttr`) and the posed character (the skinned bind-pose mesh covers the frame until the
TRANS VU1 family poses it) -- both live in `beModelCtrlInfoRamData`.

### The camera-matched capture

`scripts/camera_match.py` writes the whole scene TSV: the **world-space environment** (every pack
mesh whose local bbox diagonal exceeds `--big`, default 150, at identity), the **character**
(`--character MESH` at the `beModelCtrlNode2` -- vtable `0x537f40`, `_m` at +0x20 -- nearest
`--target`), and **runtime props** (`--prop MESH@NODE_ADDR`).  These are the cases the
`igGeometry` walk misses: the player's skin `gobr_skinShape2` is not in the live content match and
the crates only appear at their authored positions, but placing them at their controller nodes
reproduces the frame.

```sh
# --character auto picks the live skinned mesh (on this capture the Ogremon NPC, see below), and
# --textures reads the parent-node material, so that skin gets E_ogre01.png
python3 scripts/livedump.py <savestate>.p2s dump.bin
python3 scripts/camera_match.py --from dump.bin --pack NDMW.AFS:614 \
    --target 421.83 72 -110.07 --character auto --textures --stage-material \
    --prop M_TR32_barrelShape@0x14df9d0 --prop M_box_bodyShape@0x130a858 \
    --tsv /tmp/camera.tsv
./build/dw4asset render --stage <roms> stag0101.igb --ref 1 --scene /tmp/camera.tsv \
    --livedump dump.bin \
    --view '0.5 0.495845 0.710027 0 0 0.819868 -0.572552 0 -0.866025 0.286276 0.409934 0 \
            -115.58885 -299.804123 -223.409985 1' --fov 0.6912 --aspect 1.0 --w 640 --h 448 --gl
```

`--stage-material` is the fallback for the meshes the material walk cannot name: the
terrain mesh is RamData/packet-drawn, so `attr_pack_map`'s vertex-buffer content match never reaches it
and it ends up with no texture.  The stage's **BG ground set** carries the floor it draws (`P11G00s`,
measured against the real frame) and the **BG object set** the shell rock (`TA01BJ20`); the fallback
picks between them by each mesh's mean face normal (up-facing -> ground), so the world at least renders
with the stage's own materials instead of flat-shaded.  It is a **join fallback, not a recovered
binding** - the binding itself is still the draw-time material, and the colour match stays confounded
by the port's placeholder light rig.

The result is a legible camera-matched frame (the same world, still-posed character, crates left) and the
mesh shown is **textured — but it is the wrong character**, and that must not be read as progress on
the player.  `camera_match.py --character auto` picks the live mesh with the vertex blend stream, and on
this capture that is **`ogre_skinShape` (pack id 5150), an Ogremon NPC**, not the player.  The player is **Susanoomon**: the player node `0x016de170` -> `igLod` -> three
`igActor` LODs -> `igAppearance._skin` -> `igSkin._skinnedGraph` (`igBlendMatrixSelect` 0x01667468),
whose child list holds `P_susanoo_Skin0Shape0/1/2` and whose attr list holds the material
(`P_susanoo01.png`/`P_susanoo02.png`); the model is `common/p_susanoo.igb` = `NDMW.AFS` entry 861.  The
player skin's live vertex arrays read empty in this capture, so the frame currently draws an NPC in the
player's place.  The pack itself is complete: the offline model reader resolves entry 861's three
`igGeometryAttr1_5` (the three actor LODs, `P_susanoo_Skin0Shape0/1/2`) with no live state, and
`tools/verify_models.py` checks the C reader against the Python decoder on it.  What is genuinely useful
here: the **node-held material** and the **live texture
reader** (`--livedump`).  Still open: loading the player's `p_susanoo.igb` into the port and **posing**
it (`igActor._boneMatrixCacheArray`/`_blendMatrixCacheArray`), the world/crate
material (staged packet stream), and the light rig.

### The texture link: the material attr set

Reading a **world mesh's texture** off the geometry attribute does not work: only 39
of 1023 `igGeometryAttr1_5` link to a texture directly, and no shape attr list holds both a geometry
attr and an `igTextureBindAttr`.  The binding is one level up, in the **material attr set**
:

```
beTextureCtrlInfo._name                the set (`BGGround00n`, `BGObj00n`, `wall01z01`, the UI `i_*`)
  _dataList (+0x20) -> beTextureCtrlAttr          one per material
    _attrSet (+0x0c) -> igAttrSet
      +0x1c -> igNodeList of the igGeometry shapes the material applies to
      +0x20 _attributes -> igTextureBindAttr._texture (+0x0c)
             -> igTextureAttr._image (+0x30) -> igPsx2Image._pNameString (+0x58)
```

`scripts/texture_map.py` walks that graph offline from an EE RAM dump; `capture_scene.py --textures`
and `camera_match.py --textures` write the texture name as a **sixth TSV column**, and
`dw4asset render --scene` samples the named texture per draw (`--texentry` takes a pack list, e.g.
`618,619,625,626`, and `--livedump` takes the RAM dump itself; the lookup is the existing
`dw4_texpack`/`dw4_livetex` and the sampler the existing `dw4_render_mesh_tex`/`dw4_gl_frame_mesh`).
The walk also descends through the `beModelCtrlNode2` model nodes the material set names (an
`igSwitch` in a `wall01z01` attr set points at one), and it reads each shape's **parent-chain node
attr sets** too — a material can hang off the node, not the shape (the skinned character's
`E_ogre01.png` is on the `igBlendMatrixSelect`'s `igAttrSet._attributes`, while the shape's own
`+0x20` list is geometry only).  Together that lifts it from 90 to **136** live geometry attributes
(**52** pack ids of `NDMW.AFS:614`), including the BG ground/object sets (`TA01BJ01/02/04/18/20`,
`TA02BJ01`, `FD01BJ03/05/06/07`, `Z1BJ01LM`, `Z1BJ0600`, `P10G00n/s`, `P11G00n/s`), the `wall01z01`
set (`TA01GM02.png`), the largest live environment mesh (pack id 30486 -> `TA01BJ02.png`) and the
**skinned character** (`E_ogre01.png`, the Ogremon NPC).  In the camera-matched frame **15** of 124 rows carry a
recovered texture.  The terrain mesh's and the crates' material is still open — their parent node's
`+0x20` is not an `igAttrList`, and the texture is applied in the staged packet stream — so
the frame's brightness gap is **reduced, not closed**.

`FUN_00169840` is **not** the world-mesh source-texture path: it is a
method of `igPsx2VisualContext` (vtable `0x525870`, its slot `0x525934`), and the tables it reads are
the visual context's own `_pTexList` (+0x144) descriptor pool and `_pBufList` (+0x364) VRAM buffer
records; `FUN_00140060` is `igSetRenderDestinationAttr` (vtable `0x522f50`, slot `0x522fb0`).  It
builds a GS texture handle for a buffer already in VRAM (hence `p2LoadTexture`'s image argument is
0), i.e. render-to-texture/destination setup, not a source binding.

### The GPU backend (`--gl`) and the window (`--window`)

Normal boot displays the original Bandai, Intrinsic Alchemy and Sofdec/ADX startup cards before the opening FMV, using their authored fades and holds. No launch flag is required.

**Title start-up.** `DW4_FRAME_TRACE=1` prints `boot:` lines (milliseconds since the opening movie returned) for each step of the title's set-up. The title audio (three streamed tracks and the menu cues) decodes on a worker thread while the movie plays and the output device attaches when the movie returns (decoded synchronously after the movie it takes about 1.8 s of a 2 s wait before the title intro); the four front-end screens (title trails, title UI, Option, Game Start) also open on a worker during the movie, which leaves about 0.12 s (the stagIS10 session and the device attach) after a skip a few seconds in. **Call Digimon.** The title's *Call Digimon* runs the original `LoadIntf2` screens (memory-card chooser, data select with a status panel, Select Difficulty, log-in prompt) in a `DW4_SCENE_TITLE` scene; `make -C port check-titlecall` drives and renders them, `tools/profile_live.py --call` profiles them live. **Save cycle.** `tools/test_save_cycle.py` runs the whole loop headless against a throw-away `$XDG_DATA_HOME`: create a character, warp to the Save Keeper (`DW4_DEV_WARP="StagML12:0,stagIS12:0"`), save, relaunch, choose *Call Digimon* and enter the Terminal (see [Save Keeper](docs/save-keeper.md)). `DW4_SHOT_FRAMES="a,b,c"` limits the headless per-frame PNGs to the listed frames. **Frame pacing and profiling.** The live loop follows an absolute 60 Hz schedule (`frame_pace_sched`): each frame advances the due time by exactly one tick, so a late or early frame does not shift the ones after it, a stall of more than three ticks resets the schedule instead of fast-forwarding, and the last half millisecond is spun. The Vulkan swapchain prefers `MAILBOX` so a present never blocks on the vblank (`DW4_PRESENT=fifo` forces FIFO; the startup line `vulkan: present mode …` says which). `DW4_FRAME_TRACE=1` prints one line per second on stderr (frames/s, work time before the pacing sleep, frames over 16.7 ms, lobby tick/draw/present) plus a `draw split` line for the lobby world draw. Two headless tools measure the CPU side without a display: `tools/profile_lobby.py` (scripted boot into the Main Lobby, optional `--budget-ms`) and `make profile-hubstages` (every portal destination and the three interface scenes). Lobby world draw: a per-mesh vertex cache, whole-mesh and per-triangle frustum rejection against the same near/far/screen planes the clippers use, and direct emission of triangles that lie wholly inside the view bring the lobby mesh loop to 1.7 ms (6.8 ms without them) with byte-identical frames (checked against a recorded baseline). For a live-window profile of the connected hub, `DW4_DEV_WARP="StagML12:0,StagML13:0,StagML11:1"` (with `DW4_DEV_WARP_FRAMES=1200`, default 900) queues each stage change that many frames after the previous arrival, as the world's own exit would (Terminal `StagML11`, Central `StagML12`, Shop `StagML13`); pair it with `DW4_FRAME_TRACE=1`, a scripted `--input-script` into the lobby and `SDL_GAMECONTROLLER_IGNORE_DEVICES` for a physical pad. Unset, it does nothing. **Resident frames (high resolutions).** The GPU layer treats the CPU framebuffer as authoritative, so a pass on its own (clear, geometry, UI, plate, fade) uploads the whole frame, draws, reads the whole frame back and flips rows on the CPU: at 2560x1440 that is ~14.7 MB per pass and the cost scales with pixel count (with every pass transferring, the lobby takes ~29 ms, the title and character screens 26-34 ms). `dw4_gl_layer_defer(layer, fb, on)` keeps the frame resident in the layer's framebuffer for a run of passes (post-process passes copy it GPU-side) and reads it back once when the run closes; runs nest, other callers are unchanged. The lobby world draw, the title frame, the character-creation and login screens, the loading cards and the FPS counter each run as one resident frame, and the title layer, title UI, character UI and loading cards draw through the engine's shared frame layer (`dw4_gl_layer_share`) so no pass crosses a layer boundary. Rendered frames are byte-identical to per-pass transfers (303 sampled frames over the title/menu, character creation/login, Terminal and Central, compared against a build without resident frames). Whole-mesh and per-triangle culling of posed meshes (actors, skinned NPC instances) tests their posed bounds against the view and against the 256x256 shadow map separately. Performance is judged at the display's highest resolution only (`tools/profile_live.py`: `--menu`, `--create` and the default hub route, backends `vulkan` and `sdl`): all of them hold 60 fps at 2560x1440 on both backends.

On a display whose refresh is not a multiple of 60 Hz (for example 144 Hz) the 60 Hz updates are shown in an uneven cadence by the display itself; set the monitor to 60 or 120 Hz for even motion.

**Gamepad on both present paths.** The first gamepad SDL sees is opened by the SDL window and by the `--vulkan` swapchain window alike (same button map via `dw4_window_pad_button`, left stick, triggers, hot-plug and disconnect pause). The startup line `vulkan pad: …` / `window pad: …` shows what was opened. Verified by hand with a physical pad; there is no automated test because it needs live SDL controller events.

Windowed boot uses the GPU for title trails, menu drawing and the Main Lobby by default. For example,
`./build/dw4 --w 1280 --h 960` keeps the full rendering resolution while drawing
`j_startback` through GLES 3. `--software` selects the CPU reference renderer;
`--headless --gl` enables the same GPU passes for offline comparisons. Title UI,
Create/Call panels, animated BG02, naming/confirmation and options use ordered GPU
material replay. The title backdrop and small animated species portraits remain
on the CPU, with framebuffer upload/readback around each GPU pass.
See [lobby GPU execution](docs/lobby-rendering.md#gpu-execution-and-remaining-performance-work)
for lobby benchmarks and the remaining transfer/vertex work.
See [GPU title trails](docs/title-controller.md#gpu-title-trails) for the material
contract, fallback, validation and performance measurement.

The game's shading can run on a real GPU pipeline, not only in the software rasteriser.  `--gl`
draws the merged stage on **EGL + GLES 3** into an offscreen FBO (`src/gl_render.c`), so it needs no
display and no window:

```sh
./build/dw4 --roms /path/to/roms --stage stag0102.igb --ref 1 --frames 1 \
    --scene capture.tsv --camera --gl --out-dir /tmp/run
```

The fragment shader is the **game's shading model** — ambient + two-sided N·L diffuse, positional
`d`/`d²` (or linear) attenuation, a spotlight cone, Blinn-Phong specular — the same model
`render.c` implements, taken from the LIGHT VU1 program names.  It also
samples a **texture** through the mesh's UVs (`--texture NAME --texentry N`, the same `dw4_texpack`
decode with `v` flipped) and applies the **VU1 FOG family** (`--fog`).  The light and fog rigs are
parsed by the single implementation in `render.c` (`dw4_render_parse_light`/`load_lights`/
`parse_fog`), so the software rasteriser and the shader shade from the same `dw4_light`/`dw4_fog`.

It runs on whatever EGL provides on the host. With accessible GPU devices and drivers,
`--gl` uses hardware acceleration; otherwise EGL may fall back to llvmpipe (CPU).
EGL/GLES is optional (pkg-config, like SDL2), and the test reports a skip when it is absent.

`--gl` needs no `--view`/`--camera`: with neither it uses `dw4_render_fit_view`, the software fit
camera exposed as a matrix, per frame.  The same backend is available to the **offline stage
renderer**, not only the host: `dw4asset render --scene … --gl` and `dw4asset render --name … --gl`
both draw through EGL/GLES (`--gl` with the bare mesh *sheet* still uses the software rasteriser).
The GPU scene render is geometrically identical to the software one — the silhouettes match at
IoU 1.000; only meshes with no normal buffer shade differently (the GPU derives the face normal with
`dFdx`/`dFdy`, the software path per triangle).  `tools/verify_render.py` pins the GPU
`--name`/`--scene` frames, that `--texture` and `--fog` change them, and their determinism;
`tools/verify_host.py` pins the host `--camera --gl` frame.

```sh
# the GPU path on the offline stage renderer, with a texture and fog
./build/dw4asset render --stage <roms> stag0102.igb --ref 1 --scene capture.tsv --camera --gl \
    --texture BJGR01.png --texentry 625 --fog 'linear,1,3,0,0.10,0.11,0.15' --out-dir /tmp/run
# the host, GPU draw + SDL present, its own fit camera when no --camera is given
./build/dw4 --roms <roms> --stage stag0102.igb --ref 1 --frames 60 --scene capture.tsv --gl --window
```

The renderer's `present` step can also go through a host window (`src/window.c`, SDL2).  Both the
host and the offline stage renderer take `--window`:

```sh
./build/dw4 --roms /path/to/roms --stage stag0102.igb --ref 1 --frames 60 \
    --scene capture.tsv --camera --window --out-dir /tmp/run
# the camera-matched Goblin Pass frame, live in a window (the offline stage renderer)
./build/dw4asset render --stage <roms> stag0101.igb --ref 1 --scene camera.tsv --livedump dump.bin \
    --view '<the recovered view>' --fov 0.6912 --aspect 1.0 --frames 100000 --window --out-dir /tmp/run
```

A windowed run writes only `frame_0000.png` (the first frame) and then presents the rest live, so an
interactive run loops until the window is closed instead of flooding `out-dir` with PNGs.

SDL2 is **optional** (pkg-config, like EGL/GLES): without it `window.c` compiles to clean no-ops,
so the default build needs nothing extra.  `--headless` selects the SDL "dummy" video driver, which
runs the whole texture-upload/present path with no display — that is what `verify_host.py`
exercises, so `make check` covers it where SDL2 exists and reports the skip otherwise.

**Two present facts measured, not assumed.**  `--gl --window` on the offline renderer lands blank
(white) in the window: its GL path owns an EGL context on the same thread SDL's renderer would use,
and the composition does not survive it even though the frame written to `out-dir/frame_0000.png` is
correct — so a live frame is shown with `--window` *without* `--gl`, i.e. through the software
rasteriser (which still samples the scene rows' textures).  And `window.c` uploads the frame with
blend mode `NONE`, because the GL readback leaves the frame's alpha at ~0 (measured: alpha 0..226);
a blended present composites that away and shows black.

**A third one: the present path's channel order.**  `dw4_fb` holds R,G,B,A *bytes* — on a
little-endian host that is `ABGR8888`, which is what `window.c` creates its streaming texture as.
`SDL_PIXELFORMAT_ARGB8888` names the word order, and a texture created with it shows the
red DIGIMON logo **blue** and the blue backdrop warm, while the PNG written from the very same buffer
is correct.  That error does not announce itself (the image still looks like a menu), so the window backend
*verifies* the order: `dw4_window_order_ok` presents a test colour (200,60,20) and reads the backbuffer
back **before** present (after `SDL_RenderPresent` the content is undefined — reading after it returns
black), and both the `dw4` boot and `dw4asset render` print `window: pixel order ok (R,G,B,A
preserved)`.  `verify_host.py` requires that line, not merely that a window opened.

A boot prints the platform seam, runs the boot's **manager phase**, constructs the pack's object
graph through the reflection object model (`object.c`), then runs the frame loop: each tick runs the
ported engine function `igObject_InitHeader` (`0x2fef20`, ported verbatim as
`dw4_object_init_header` — all 4-byte offsets, so under pointer-model option (b) it needs no change)
and the **one-shot frame context** `FUN_0025a580` builds: gated on the app object's
`+0x18`, the frame object is created, `+0xe8` is set to 1 and the per-frame fields are written
(`+0x94`/`+0x98`/`+0x9c` = 0.1, `+0xa0` = 1.0, `+0x5e`/`+0xa8` = 1, the flag bytes 0), then
`+0xe8` is decremented back to 0 and the object is released — the context is acquire → run →
release every tick, not a persistent counter.  Each `present` draws the loaded geometry through the
renderer, one PNG per frame.  On `stag0102` that is **38,135 objects over 192 classes**, and the
header it produces is `+0 = 0x52f0f0`, flags `0x1`.

The **manager phase** is the engine's own first boot step: `FUN_002595e0` constructs
three Insight managers, and each is a named `_Create` factory — `igEnbayaContextPool_Create`
(`0x1a1ae0`), `igAnimationCombinerBoneInfoPool_Create` (`0x1a7cc0`), `igAnimationStatePool_Create`
(`0x1a67c0`) — of the shape `igMetaObject_RunStaticInit(<Class>_Register)` then
`igMetaObject_CreateInstance(<Class> MetaObject, owner)`.  The port reproduces that at the semantic
level: `create_instance()` allocates the class's reflected size, runs `igObject_InitHeader` and
stamps the vtable, which is `igMetaObject_CreateInstance` with the port's recovered schema standing
in for the guest MetaObject pointer.  `verify_host.py` pins the three managers, the counter and the
differing frames.

What this is and is not: it is the `main` the plan says the port is missing
(`port/docs/project/tasks.md` P2.6), and the loop is the engine's shape.  It is **not** yet the game's own
`FUN_002595e0` — that function and its callees are undecompiled, and the boot chain is mapped in the
decompilation repo's [`docs/engine/engine-boot.md`](../docs/engine/engine-boot.md)
.  The port order from here is the app object (`0x234900`/`0x234d70`), then the frame
functions `0x25a580`/`0x25a8c0`, then `main`.  `tools/verify_host.py` is in `make check`.

See [scene controller services](docs/controller-services.md) for prepared model
instances, authored window programs, lobby camera completion and the remaining
general model/renderer integration.

## Recovered title controller integration

The native title and Options screens run the unchanged recovered
`beNDMWTitle2` controller, which supplies START-only entry, clamped rows, animation waits,
confirmation/cancellation, and deferred settings commit. The slot/character/name flow is entered at the
controller's `LOADCTRL2 GENERATE_TITLE` boundary.

The native model backend uses recovered request queues. The logo also runs its
extracted Action2 program through recovered completion/timing code, driven by an
explicit clock with recovered timer pause/resume, signed time scaling and world
updates before Action2 dispatch. The default raw-source cadence remains provisional.
Other title models retain bounded schedules. Hardware cadence, game-pause routing,
exact sound-event timing/mixing and complete rendering equivalence remain open. See
[the integration and validation record](docs/title-controller.md) and
[the documentation index](docs/README.md).

## The front-end boot: power-on to the title, and into the world (P6.2)

`dw4` boots the game's own **front-end**, not just a stage — `dw4 --roms <dir>` with nothing else
does it, no analysis-tool flag:

* **boot/attract:** menu-database (`NDMW.AFS` 800) → bandai-logo (802, scene `stagis09`) → opening
  (804, `stagis10`) → title-screen (806, `stagML11`, the live `beNDMWTitle2` menu: `Game Start` /
  `Option`);
* **the title is presented and the boot STOPS there**, waiting for input: it opens on the
  **press-start screen** (the logo, the copyright and the `Press START button` line — `j_startlogo`
  + `j_startmenu01`) and only once you advance does it show the **`Game Start` / `Option`** rows
  (`j_startmenu02`), over the `stagML11` backdrop geometry;
  before any of that the `j_startback` layer's opening plays **alone** — the ring/portal grows with
  no UI for its 209-frame `SQ_OPEN` (3.48 s), which is what the game does straight
  after the FMV, so the UI's own `OPEN` is timed from the end of it, not from the boot;
* **Game Start** opens the four-slot screen; **Create Digimon** opens the native species selector
  (Dorumon, Agumon, Veemon, Guilmon). Left/Right wraps, and Circle returns to Create/Call.
* Character creation continues through naming and the completed character card to the hand-off
  into the Terminal Area (`stagML11`); see *Create Digimon species screen* below. The standalone sequencer still
  describes the 808/810/812 branch and the captured lobby destination.

```sh
./build/dw4 --roms /path/to/roms                    # power-on -> intro -> title, live, until closed
./build/dw4 --roms /path/to/roms --headless --frames 8 --out-dir /tmp/run   # offscreen title frames
./build/dw4 --skip-logos  # testing: skip startup logo cards
./build/dw4 --roms /path/to/roms --headless --input-script 5:cross --out-dir /tmp/run  # a scripted pad
python3 tools/verify_frontend.py        # runs in `make check`
```

**The window takes input.**  `src/window.c`'s `dw4_window_pump` decodes keyboard and SDL gamepad
events into `dw4_input_state` (`src/input.c`), which applies the game's own mapping — Cross =
confirm/attack, Circle = cancel/jump, Square = guard, L1 = item window, R1 = MP technique, R2 =
status, Start = status screen. The menus accept **D-pad, left stick or keyboard arrows**.
Held digital directions take priority over both stick axes so drift cannot interfere;
opposite directions cancel. Existing navigation timing also applies to the D-pad. The host keys are
**Space/Enter = Cross, Backspace/Esc = Circle, Tab = Start**.  `--input-script` feeds the same
state for a headless run.  (A test run can also set `DW4_SKIP_MOVIE=1` to skip the 64 s opening and
reach the title immediately — an env escape hatch for iteration, not part of the shipped boot path.)

**The opening FMV is skippable**, as it is on the console: press **Cross — Space or Enter on the
keyboard** — during the movie and it stops straight away and goes on to the title (`src/movie.c`
pumps the same input state the engine loop uses, so `--input-script N:cross` skips it in a headless
run too).  On the press-start screen the game waits for START (Tab); the port also accepts Cross
(Space), since that is the key a PC player reaches for.
Two facts worth keeping: `SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS` must
be set or SDL drops pad events while the window has no focus (the normal state under a compositor —
without it a real pad is silently dead), and `igPsx2Controller`/`igPsx2ControllerManager`
are `DW4_IF_INPUT` in the seam, so the engine prints `1 implemented, 2 input, 28 stub`.

**What is a stand-in:** the standalone `--stage` path is a diagnostic render (offline
stage path, fixed spin, no gameplay camera, no simulation).  The title/menu's own light-trail layer
*and* its 2-D UI tree *are* generated (see below), and character creation hands off to the first arrival
(*Create Digimon species screen* below); the current front-end and gameplay boundaries are in
[`docs/boot-contract.md`](docs/boot-contract.md).

### The title/menu presentation: the generated light-trail layer and UI tree

The engine's title screen is 2D UI whose placement is the game's own pack scene data (the logo, copyright and rows resolve from `AREA.AFS` 620's `j_startlogo`/`j_startmenu*` graphs, drawn
by `src/frontui.c`) plus an additive light-trail layer the engine regenerates every frame.  That layer is the scene model **`j_startback`** in the same pack, and `src/frontlayer.c`
**generates** it from the pack's own data — no capture, no flag; `dw4` finds everything itself:

```sh
./build/dw4                     # asset dir found automatically; the layer is generated at the title
./build/dw4 --roms <dir>        # ... or name the asset dir
```

The asset root (`NDMW.AFS`/`NDMW.IGB`) is searched beside the executable and in the usual working-tree
places (`local/extracted`, `../../local/extracted`, `roms/…`), and the boot prints what it chose
(`front-end layer: j_startback, 16 mesh(es)`).

**What is generated, and from what.**  The layer's motion is a small *scripted model controller*
carried in the same pack: `beModelCtrlData` sequences (`SQ_OPEN`, `SQ_WAIT`) whose
`beAction2JOINTSET` components are **time ranges**, not joint counts.  The port plays the recovered
schedule — `SQ_OPEN` frames `0…209` one-shot, then `SQ_WAIT` frames `240…360` looping — and each animated `igTransform` node's time is recomputed from the host's 60 fps engine
clock exactly as the engine does:

    _time = ((int64)(_timeScale * (engineTime >> 18))) << 18 + _timeBias

There is no per-frame cursor and no joint-instancing step: the layer is **16 `igGeometry` meshes /
3184 triangles drawn once each**, evaluated at their own node times and drawn
additively in a perspective screen space.  Its texture is the pack's own `sback00.png` — an 8 bpp
`igImage` plus the `igClut` its `_pClut` names — which the port decodes straight from `AREA.AFS 620`
(a byte-per-pixel grid through its palette).

**Its camera is recovered, not calibrated.**  The title script's
`SETDEMOCAMERA "entry"` selects the `beCameraCtrlInfo`/`igSceneInfo` named `entry` in `NDMW.AFS`
entry 806, whose `beCameraDemoData._cameraPath` is the `igGraphPath` 2997 over the chain
`animCamera01_60 → cameraanim_GP1 (+600) → cameraanim_group01 → cameraanim01 (+130) → igCamera
cameraanimShape01`.  The demo runs for `_totalSec` 1 s, but the path is **static**: none of its four
`igTransform` nodes carries a `_transformInput` sequence, so `beCameraMode::vfunc_28`'s per-frame
path evaluation composes the same matrix at every `_nowTimeL` (`_totalSec` only advances `_nowTimeL`
to `_timeLength` and latches `_isEnd`).  The menu-state pose is therefore the chain's own world — an
**on-axis eye at world z = 730** with a ~0.04° tilt — which the port composes from the pack
(`front-end layer camera: 'cameraanimShape01' eye (0.00 -0.00 730.00)`) and inverts to a view matrix.
There is no calibrated distance constant; `tools/verify_frontend.py` asserts the resolved eye.

**The per-draw material.**  The layer's `igGeometry` nodes carry only their geometry attribute — no
colour, material or blend record is reachable in the pack, so the blend is the
front-end's own draw state: the game draws the layer **additively** (`ALPHA 0x48`, `Cs·As + Cd`,
`PRIM` ABE=1 IIP=1), sampling the pack's `sback00` texture and applying its **alpha** (~36 % of the
texture's texels are alpha-0, so they add nothing).  The port reproduces exactly that; the only
stand-in is the VU1 shade, which the pack does not carry as data.

The result animates **every frame** at the game's 60 fps (checked by `tools/verify_frontend.py`:
four seconds of frames must differ), which a capture replay cannot do —
a capture can only ever move at PCSX2's ~5 fps screenshot rate.

The title draws its asset-backed logo and menu graphs over the layer, with font-rendered rows
as a fallback when those graphs are unavailable. The recovered controller handles START,
stick navigation, Cross confirmation and Circle cancellation.  The capture reader (`src/uireplay.c`) serves only `dw4asset`'s analysis paths
(`--ui/--ui-only/--ui-seq`) — the shipped `dw4` does not use it.

**The whole front-end is one window.**  The opening FMV presents into the boot's own window
(`dw4_movie_play_in`), not one of its own, so the movie and the title are the same surface and no
*second* window comes up at the title.  Closing it during the FMV
ends the run (`window closed during the opening FMV`), which is what closing a window should do.
The boot defaults to 1280×960; `--w/--h` set both its window and title/game framebuffer size
(for example, `./build/dw4 --w 1280 --h 960`). The movie keeps its decoded 640×480 source size;
the SDL and Vulkan presenters scale it into the boot window, then accept the title's larger
framebuffer. `tools/test_window.c` checks the SDL source-size transition and colour order.

### Game Start background

The slot screen draws `NDMW.AFS` entry 806's `BG02` scene beneath its panels:
16 meshes provide the rotating grid, drifting coloured diamonds, expanding rings and lower glow.
Their transform and UV tracks repeat over six seconds, driven at 60 Hz and reset on Game Start.
The texture, palette and blend modes come from the pack; no captured image is needed at runtime.

The projection is measured against a retail GS dump of the settled slot screen: depth is
`300 - world Z`, with focal lengths 628.03 / 659.43 at 640×448. The capture uses neutral
127 RGB, 128 alpha, alpha-test reference 12, and ordinary/additive blending by material.
This is a measured reconstruction; exact phase synchronisation and the panel-assembly transition
remain separate work. `dw4asset chr <roms> --t 1.5 --out slot.png` renders a deterministic phase.

Two shared loader rules make this possible: `_sceneGraph` is selected by its field ordinal,
including `igSwitch` roots, and animated nonuniform scaling is applied in local axes before
rotation. `verify_frontend.py` checks backdrop visibility, coloured diamonds, motion, six-second
repeat, and the existing panel colours and menu controls.

### Create Digimon species screen

The selector uses entry 806's `j_namewin02` frame, `j_digifacewin` portrait tab,
`N01` / `j_digiselcursorright` arrows and ring, and `j_chrselmesswin` prompt window.
The first switch branch is selected even when a `PromotedAttr` wraps its controller;
otherwise all four player-colour variants overlap. The portrait atlas's bottom row is
Agumon, Veemon, Guilmon, Dorumon; the selection order is Dorumon, Agumon, Veemon, Guilmon.
The small portrait badge sorts its triangles by asset depth: the backing is z=20,
the portrait is approximately z=80, and the circular rim is z=120. These depths coexist
inside the base mesh, so sorting entire meshes (or forcing the portrait to the front)
obscures the rim and exposes the portrait's polygon corners. The badge uses retail
RGB 127 / alpha 128 modulation; the red rim measures about (249,110,110), checked
against a retail capture of the first name-entry screen and the supplied PS2 footage.

`dw4_scene_load_actor_preview` additionally follows `igActor._appearance` →
`igAppearance._skin` → `igSkin._skinnedGraph`. The skin's `igBlendMatrixSelect` supplies
its material, and the parent attribute sets supply the view/projection matrices and
150×105 viewport. This preview path is opt-in; ordinary stage loads retain their existing graph.
All four original textured meshes draw in their own viewport, with no captured asset at runtime.

The four original `waitC` clips animate natively. `src/actoranim.c` resolves each
mesh's blend palette, skeleton, animation binding and compressed track source, then uses
the MIT-licensed [Enbaya decoder](third_party/enbrip/README.md). Bone quaternions and
translations are evaluated at 60 Hz; the animation's translation mask selects animated
translations versus the skeleton's rest offsets. Parent transforms and inverse bind
matrices produce the skin palette, applied to both positions and normals. These four
meshes have one unit-weight influence per vertex; unsupported weights are rejected.
Each species restarts its own clip when selected and loops at its stored duration.
The four rigs are uniquely associated by joint count; an ambiguous association fails.

The original camera and 150×105 viewport produce the close-ups once the pose is applied;
there is no guessed zoom. Preview depth uses scaled reciprocal depth because the shared
layer rasterizer rounds depth to integer GS units. Unscaled reciprocal depth rounds every
vertex to zero, incorrectly exposing rear faces, teeth and eye surfaces. Lighting
reads the enabled `igLightStateAttr` references: the warm directional light and cool
ambient light, excluding the inactive spotlight. Normals are skinned before lighting.
These are native reconstructions, visually checked against retail captures, not a claim
of phase-aligned pixel identity.

Cross opens the pack's name-entry keyboard. Its original mode/key outlines and four
scroll arrows are drawn from `j_namecursor01/02` and `j_namecursor{left,right,up,down}`.
The five-key strip scrolls only at its edges, retaining its offset when direction reverses.
The name uses 17-pixel character slots. Its insertion brackets nudge once when the
letter selection changes and rest while idle or typing; the left mode outline and centre
key outline independently loop their original quarter-second scale pulses. The candidate
letter is grey and placed letters are white (GS RGB 64 versus 114, both alpha 121), and
the candidate is hidden on confirmation. Saved PS2 draw data of
name entry with two letters supplies these colours and positions: name glyphs
start at (83.5, 15), key centres are 46 pixels apart at y=70, and mode glyphs centre on x=36.
The screen's font-atlas descriptor remains alive through rasterization. Left/Right selects a key, Up/Down changes
lowercase/uppercase/digits/symbols, Cross types, and Circle deletes or returns to the slots
when empty. Start with a nonempty name opens the question page, then Cross opens Yes/No.
The question wraps onto two lines, hides the control legend and shows the asset's
next-page marker. No or Circle preserves the edit; Yes shows the created summary, and only Start there
hands off to the lobby. The current port input limit is eight ASCII characters; the exact
retail limit and complete symbol repertoire remain to be verified. The name/species result
is retained in the caller-owned `dw4_created_player` session record across the stage load.
Circle on that summary returns to the same name and keyboard selection. The summary
shows Lv 1 and each species' HP/MP from the recovered starter values documented in
`../docs/engine/front-end-boot.md`. The [first-arrival adapter](docs/boot-contract.md#created-card-login-and-first-arrival)
spawns the player and Digi-Elf in the same boot window and presents the original greeting.
Held analog input repeats after 20 ticks, then every six ticks; those timings are estimates,
not recovered constants. The naming screens were visually checked against the supplied
PS2 recording `2026-10-09 13-51-54` (entry, reverse scrolling, question, Yes/No and created card).

`dw4asset chr <roms> --species 0 --t 0.2 --out species.png` renders a deterministic
animated preview (indices 0–3). `tools/test_actoranim.c` verifies all four rigs move, stay
finite and repeat at their own durations; `tools/test_frontchr.c` verifies name bounds,
modes, wraparound, cancellation, confirmation, idle versus selection-triggered cursor
motion, both outline pulses and candidate/placed-letter contrast. `verify_frontend.py` exercises the
headless input flow through editing, No, Yes and Start into the lobby, while preserving
species navigation and the existing title/Option checks. The portrait pass clears to transparent
coverage and composites only drawn fragments over BG02. Selection changes retain the outgoing
animated model for a fade-out, pause with the backdrop visible, then fade in the newly selected
model. Rapid input preserves the current outgoing opacity. The name changes immediately; the
asset's icon-housing turn replays on each selection, its arrows pulse, and the ring/line tracks
assemble on entry. The paired grey nameplate brackets replay their 0.333–0.500 s asset segment
on each selection (4 pixels inward and 2 vertically, then back), holding the visible rest key
instead of the later disappearance key. Fade durations (about 0.17 s out, 0.27 s clear, 0.17 s in) are estimates from
the supplied 30 fps PS2 recording, not recovered engine constants. The render regression checks
uncovered portrait pixels and retention of the old model on the first switch frame; set
`DW4_CHR_TEST_FRAMES` to an existing directory to export its normal and rapid-switch sequence.

### The opening FMV (`--movie`)

The `opening` stage's scene (`stagis10`) is only half of what that phase shows: its frame is a
**Sofdec movie** — `aus_opening.sfd` in `AREA.AFS`, MPEG-1 video + ADX audio, 64 s.
The project's FMV route is ffmpeg (P3.6), so `src/movie.c` is the *frame seam*: it resolves the
movie through the mount, decodes the video stream to raw frames and hands them over one at a time,
each presented through the host window.  The native MPEG-1 decoder replaces it behind the same two
calls without the caller changing.  A windowed boot plays it in place:

```sh
./build/dw4 --roms /path/to/roms --movie aus_opening.sfd --window   # the movie on its own
./build/dw4 --roms /path/to/roms --boot --window                    # ... as part of the boot
```

A headless `--boot` reports the FMV rather than playing it (`opening FMV: … (not played: no
window)`), so `verify_frontend.py` never blocks on 64 s of video; it still checks that the movie the
plan names resolves inside the disc's own archives. Windowed movies play their ADX soundtrack
through SDL2 and pace video to its sample clock. Title and character creation also play the
original music and menu cues automatically; see [native audio playback](docs/audio-playback.md)
for asset sources, validation and remaining sound-event/mixing boundaries.

**The frame-rate readout** (`--fps` / `--no-fps`, default `-1`) draws the same "NN fps" plate
`dw4asset render` uses over every presented frame — the movie, the boot's scene and a stage run —
and draws nothing without a window, so an `--out` PNG stays clean.  Measured on the opening movie:
1921 frames of 640x480 progress-video in 64.23 s (the stream's own 64.1 s, so the pacing is right to
0.2%), `dw4_window_present` costs 1.9 ms/frame mean and 4.2 ms worst, and the inter-frame delivery
has no stall above 33 ms.  `DW4_MV_TRACE=1` logs that per frame (`MV <n> present <ms> gap <ms>`) on
stderr, which is how those numbers were taken — **if the movie looks like it is hitching, measure
this first**: the decode side delivers all 1921 frames in 0.7 s and the port never misses its
budget, so a stutter on screen is downstream of the port (the compositor or a remote-display
chain, whose encode is content-dependent and so faults on the same scenes every time).

`src/frontend.c` is a **native stage/script sequencer** with the `be:`
API subset the front-end uses (`sd`/`DMsetSD`/`DMchkSD`/`DMrun`, `FLGset`/`FLGisOn`/`COUNTERset`,
`SYSgetArea`/`SYSgetDifficulty`/`SYSctlFlagFolder`, `LISsetDifficultMax`, `CFLclear`).  Two things
make it evidence rather than a print:

* each script entry is **loaded from the disc** and parsed as an igBinary pack; its Lua chunk names
  come from the pack's `beLuaData` records (entry 800 = `start.lua`, `gatedisc.lua`, `first.lua`,
  `boot.lua`, `func.lua`; the title entry additionally carries `gameStart.lua`,
  `snd_j_startback.lua`, `hostLoad.lua`);
* each entry's **own bytes are scanned** for the `NEXTSTAGE` / `PADINPUT` / `TITLE2` directives its
  Lua bytecode carries (Lua 4.0.1 keeps string constants inline), and the plan's expected token has
  to match — so a changed disc fails verification instead of silently passing.  The scene-stage
  packs all resolve through the manifest: `stagis09.igb` → `[0.803]`/`[0.804]`, `stagis10.igb` →
  `[0.805]`/`[0.806]`, `stagml11.igb` → `[0.820]`/`[0.819]`, `stagis11/12/13.igb` →
  `[0.807..0.812]`, and the hand-off `stagml11.igb` → model `[0.820]` / sound `[0.819]`.

Two honest limits.  The entry *order* is the reconstructed plan: the engine function that starts
the first entry at power-on is still open ("Open"), so the sequence is a plan rather
than a transition derived from engine state — and the character-select entries are a **sibling
group** (the live new-game run enters at 808; 810/812 are the other character-select entries, which
the sequencer loads but whose engine transitions are not in the script), so the hand-off to
`stagML11` is selected from the Terminal Area first-arrival script (`stagML02` is the commander
room, not the arrival stage).  The title's two rows are the recovered
`beNDMWTitle2Option` set, not read out of the script.

The **2D layer the front-end
actually shows** — the logo cards, the title art and the menu rows — is a *data path*, and it
is made of:

  - the **text** is `bectext.igb` (`NDMW.AFS` entry 79), the front-end's font asset: its classes are
    `igFont`/`igBitmapFont`/`beFontImage` with an `igCharMetricsList`, and it names `font00.png`.
    The menu strings are rendered into a bitmap font and drawn as quads (the menu's 256x128
    "GAME START / OPTION" texture is exactly that path's output).
  - the **elements** are ordinary pack data: `NDMW.AFS` entry 806 (the title screen) is an
    8,398-record pack whose named objects are a UI tree — `cursor`, `maru`, `OPEN`/`SQ_OPEN`,
    `LINEON00`/`LINESL00`, `WAIT01`, `PromotedAttr` (an `igNode`/`igGroup` hierarchy with
    `beAction2*` actions), and the screen-space quads (`mojiL`, `sen`, `pnum`, `selcurShape`, the
    cursors) are meshes in the stage packs (`stagML11`'s pack 820).
  - the **placement** is the pack's own scene data (above), not something a live
    capture supplies: a capture of the menu state resolved only 23 of 432 nodes with a matrix,
    and those are the cursor/arrow marks.

A native path has three parts: (1) loading `igNode`/`igGroup` trees with their
transforms and `beAction2*` actions, (2) drawing them through a screen-space pass (orthographic,
centre-origin, +y up — the port has the GS UI primitive, `dw4_render_ui_tri`), and
(3) decoding `bectext.igb`'s `igBitmapFont` + `font00.png` for the text.  For the text,
`src/fefont.c` decodes `bectext.igb` from the disc (the `font00.png` 512x512 grid + its linear
`igClut` + the NORMAL `igCharMetricsList`) and `dw4_engine_boot` draws the title rows with it, so the
menu text is the game's own face.  The layout geometry and the animated backdrop are the generated
UI tree and light-trail layer described above (`src/frontui.c`, `src/frontlayer.c`).

## The runtime object model (P2.6)

The loader hands out opaque payloads; this layer turns a pack's **record** into a typed `igObject`
whose fields can be read and written **by name**.  It is the engine's own shape:

* the **schema** is the recovered class metadata — `igMetaObject` (a field list and instance size)
  and `igMetaField` (name, type, absolute offset).  `tools/gen_reflection.py` turns
  `../data/reflection.json` into `src/reflection_data.c` (1074 classes / 3680 fields), and
  `make check` re-runs it with `--check` so the port and the dump cannot drift;
* a **record** is `{u32 classIndex}{u32 recordSize}{value per descriptor}` and a descriptor is
  `{type, ordinal, size}` with `ordinal = declaredIndex + K + 1`.
  `src/object.c` recovers `K` by the same type match the decompilation's `igb_inst.py:find_K` uses,
  matches each descriptor to its declared field and copies the value to that field's offset at its
  own type's width;
* access is reflection-driven: `dw4_object_get_i32/_f32/_vec3/_vec4/_str/_ref` and the matching
  setters, over `dw4asset reflect`.

```sh
./build/dw4asset reflect --afs NDMW.AFS --entry 622 --class beGeneraterData --limit 1
#   _pos = (-117, 72, 609)   _geneEnemyId = 36   _startModeStr = "direct"   _startData = 150
./build/dw4asset reflect --afs NDMW.AFS --entry 622 --json
```

The bound, from the loaded stage: `NDMW.AFS` entries 621 + 622 instantiate **39,341 records over 203
distinct classes** (`reflect --json`), and those records use **17 named MetaField types** —
`igObjectRef` (30,242 values), `igInt` (17,857), `igVec3f` (5,817), `igBool` (4,564), `igFloat`
(4,395), `igLong` (3,807), `igUnsignedInt`, `igVec4f`, `igMemoryRef`, `igEnum`, `igString`,
`igMatrix44f`, `igUnsignedChar`, `igStruct`, `igRawRef`, `igUnsignedLong`, `igShort`.  That is the
MetaField surface a running engine must implement first; construction is the `igMetaObject`
`Construct`/`CreateInstance` path and the get/set by offset the object model needs.

`tools/verify_object.py` (in `make check`) constructs **every** record of entries 621 and 622 and
diffs the named values against the decompilation's independent decoder (`igb_inst.py`):
**39,341 records / 70,077 field values, 0 disagreements** (a slot whose descriptor type does not
match the declared field is excluded, because there either side's ordinal naming is a guess).  A
record of class `beGeneraterData` round-trips exactly the fields measured live
(`_geneEnemyId` 36, `_startModeStr` `"direct"`, `_startData` 150).

Still open: the engine's **virtual dispatch** (the `igObject` vtable interface block) and the
`MetaObject` method slots — this layer constructs and reads objects, it does not yet run their
methods.  The **identity** half of dispatch is in place: every class's vtable address is in the
schema (976 of 1,074), so a live object's `+0` word names its class; what remains is the
slot-to-method *signature* (`data/vtables-getvtable.json` carries the 62 slot bodies per vtable, and
`../config/SLUS-20836/names/GetVTableSlots.tsv` names 1,177 of them).

## The first renderer: `render` (software, P4.3)

The port draws the geometry it loads, with no GPU and no window system:

```sh
./build/dw4asset render --afs NDMW.AFS --entry 621 --name pCylinderShape3 --out cyl.png
./build/dw4asset render --afs NDMW.AFS --entry 621 --out sheet.png --w 900 --h 640 --cols 9 --limit 45
./build/dw4asset render --stage <roms> stag0102.igb --ref 1 --attr 6 --wire --out wide.png
```

`src/render.c` is a small rasteriser: the camera is fitted to each mesh's bounding box, projection is
perspective, triangles are scanned by their bounding box with barycentric coordinates and interpolated
depth, and shading is the game's live light rig (below) with no per-mesh tint — written out through the
port's own PNG encoder. `pCylinderShape3` comes out as a barrel with lugs; a 45-cell sheet of entry
621 reads as rocks, crystals, a sphere, a fern, a cauldron, a diamond. `tools/verify_render.py` (in
`make check`) renders three named meshes and asserts each is not the background, covers a sane fraction
of the frame and is byte-identical across two runs.

It is the end-to-end check of everything below it — pack → arena → 32-bit handles → meshes → pixels —
and the shading uses the mesh's **own vertex normals** wherever it ships them. Every drawn mesh of the
stage packs does: the second 12-byte stream is a unit-length normal triple, and `dw4asset`'s **scene**
path interpolates it too (merging positions and UVs only shades a camera-matched
row with its per-triangle face normal while the game interpolates the mesh's normal; on the
Goblin Pass frame that is the difference between a flat-looking world and one that matches the real
frame, mean abs difference `31.27 → 28.86`). The count of 130 of 669 meshes carrying a `_vdata[1]` normal buffer
is a property of the *live* object graph, not of the pack. They are interpolated and
shaded per pixel, so a curved surface is smooth instead of faceted (`--flat` forces the face-normal
baseline back for a comparison, `--normals-only` draws just the meshes that have them); `dw4asset
render` reports the count. Texturing is in: `--texture <name> --texentry <n>` decodes a named texture from a texture pack through
the port's own reader (P3.4) and samples it per texel with barycentric UV interpolation (`v` flipped,
because the pack stores grids bottom-up), so `pCylinderShape3` with `BJGR01.png` renders as a correctly
textured barrel — the game's own palette through the mesh's own UVs. `tools/verify_render.py` asserts
the textured frame differs from the flat-shaded one and is still non-blank, and that a scene row whose mesh ships smooth normals renders differently with and without (`scene
normals`, pack 621 id 1141).

**Texture filtering is linear, from the game's own data.** The stage packs' material
sets say so: of the 323 `igTextureAttr` records behind their `igTextureBindAttr`s (packs 614 and 621),
**300 carry `_magFilter = _minFilter = 1`** — linear magnification and minification — and `_mipmapMode
= 0`, no mipmaps; the 23 that carry `0` are the placeholder records `PromotedAttr` (21) and `WN04` (2),
so every one of the 114 distinct *named* materials asks for linear, the crate's `g_woodencasez01` and
`g_bbarrelsz01` included. `_wrapS`/`_wrapT` are `1` on all of them, the same 0/1 ordering the sampler's
clamp already follows. **Nearest** sampling shows wherever a texture is magnified
— the real frame's floor is soft and a nearest-sampled port frame is blocky — and sampling linearly
moves the camera-matched frame toward the real capture: whole-frame mean abs
difference `28.86 → 27.09`, linear closer on **57.2 %** of pixels, no 32×32 block where nearest is
better. `--nearest` selects the nearest sampler, `--bilinear` is the default; `verify_render.py`'s
`tex filter` check renders one textured row both ways and asserts they differ. (This is *not* the
crate's problem: at this camera distance the crate is about 1:1 texel per pixel, so its box mean moves
by 0.1 — its residual is the invented tint.)

## The 2D overlay: replaying the HUD (`--ui`)

The engine draws the HUD and every other 2D element straight to the GS in **screen space**, so the
scene path (which walks the pack's geometry) draws nothing there -- that region was the frame's
largest remaining error.  `--ui` *replays* the draws a `.gs` dump
recorded, which closes the frame and pins the 2D blend and the screen-space mapping by measurement:

```sh
# the overlay draws, separated from the 3D ones by measurement: alpha-blended (PRIM.ABE), unlit
# (one constant per-vertex colour) and inside the framebuffer.  --stq keeps the 3D draws too and
# writes raw STQ, with a trailing blend code per row (0 opaque / 1 alpha 0x44 / 2 additive 0x48)
python3 scripts/gs_ui.py --dump <dump>.gs.zst --out /tmp/ui
./build/dw4asset render <the same arguments as any scene render> \
    --ui /tmp/ui/ui.tsv --uitex /tmp/ui --out-dir /tmp/withui
```

`gs_ui.py` writes `ui.tsv` (one row per screen-space triangle: `TEX\tx y u v r g b a` three times,
`-` for an untextured overlay) plus each TEX0's texture decoded out of the dump's VRAM in the same
`{w,h,rgba}` form `--texdir` already reads.  `dw4_render_ui_tri` (`src/render.c`) draws them in file
order -- the exporter emits them in the GS's draw order -- with the game's own modulate
(`(Ct*Cv)>>7`, `(At*Av)>>7`) and blend (`ALPHA A0 B1 C0 D1`, i.e. `(Cs-Cd)*As+Cd`), with no depth
test.  In the Goblin Pass frame that is 516 draws / 2920 triangles / 8 textures and it halves the
HUD region's error (30.45 -> 16.47 mean|d|, whole frame 16.04 -> 14.86); the placement is exact to
1 px.  It is a **reproduction** path, not the native UI a port needs -- the content is per-frame
state, the textures come from the dump -- and it is **software-path only** (`--ui` is ignored under
`--gl`, which is not built in every environment).  `tools/verify_render.py`'s `ui overlay` check
pins the plumbing and the blend (a textured red quad lands on its coordinates; a half-alpha quad
blends).

### What the dump's UI set is, exactly (`--ui`)

Without a flatness test the replay is 97.5% *background*: on the menu frame the overlay filter passes 1682 triangles
of `STQ`, of which 1642 belong to the front-end's background dome.  The discriminator is
measured, not guessed — a 2D overlay is **flat**:

    every one of the 36 genuine UI draws sits at a single Z;
    all 1159 of the dome's draws vary (190 .. 162584).

`gs_ui.py` requires that (`ui_draws`), so `--ui` replays only the UI: 36 draws, 72 triangles,
4 textures — the logo, the menu text, the cursor and the copyright, with the dome's 1159 draws left
out.  Two rules the measurement set: the draw filter tests overlap with the framebuffer — dropping any quad with a
vertex outside it throws away the **logo** (it sits 13 px above the top edge, so
the quad is clipped, not off-screen) — and the affine TSV carries no
5th coordinate, which makes the port's reader draw nothing at all.

With the dump's 3D draws put back in (`--stq`) the replay is **1257 draws / 2188 triangles** and the
frame gets close: whole-frame mean error against PCSX2's own PNG of that frame, 0 = identical —

    the port's untextured dome, UI only        85.2
    the flat UI draws only                     55.2
    everything, raw STQ, per-pixel divide      28.9

so the background *is* largely reproducible from the dump once the 3D draws stay in and the divide
happens per pixel.  Two blend facts the measurement caught, both carried per draw as a *blend
code* (0 opaque / 1 alpha / 2 additive), not as one assumed blend:

  * **816 of the 1257 draws are ADDITIVE** (`ALPHA 0x48`, `Cs*As+Cd`).  Applying the ordinary
    `(Cs-Cd)*As+Cd` to them leaves the whole backdrop measurably dark — every sampled background patch
    reads 15–25 low, because the tunnel's light passes are exactly these draws.  With 0x48 handled the
    backdrop comes up and the low-frequency error drops (19.20 -> 18.97 on an 8 px blur).
  * a **lit** draw (one colour per vertex) is kept, and its colour interpolates across the
    triangle.  This frame's 128 such draws are backdrop patches and they barely move the image
    (420 px by <= 2), so they are *not* the darkness.

What is **not** yet reproduced, stated plainly: the backdrop still comes out ~15% low in the
mid-tones.  The residual is not missing content — no ABE-off draw survives the viewport test on this
frame, so dropped opaque passes are ruled out — and it is not a pure transfer curve either: the
port-vs-reference tone map is monotone but not linear (our 16 -> 46, our 80 -> 101, our 144 -> 150,
our 240 -> 220), and a `gamma 0.80` on the port's output recovers only 29.5 -> 25.7.  Where the port
draws near-black the reference reads a flat ~32, and the dump has no full-screen base draw, so the
base is either pre-existing framebuffer content or a term of the GS blend the replay does not model
(the `C*Ad` term, with `Ad` from the destination alpha, is the next suspect).  `verify_render.py`
pins the primitive ("ui perspective: per-pixel STQ differs from per-vertex on 786 px").

### The menu's animation (`--ui-seq`)

The menu is not still, and what moves is not what you would guess.  Measured over the live menu, with
the frames as evidence rather than a theory:

  * the backdrop's **geometry does not move at all**.  Angular and radial brightness profiles, at
    sub-degree precision, correlate **0.97-0.99 across 1.4 s** with no rotation (best shift <=0.05
    deg), no radial scale (best k = 1.000) and no radial flow (best drift 0 px);
  * what changes is the **additive** layer — `ALPHA 0x48`, the streaming dotted light trails.  Its
    draw count changes every frame (384 / 850 / 808 in three consecutive captures), and of ~1100
    draws only **10** keep their screen position from one frame to the next, while those 10 are the
    *static UI* (the logo and the font textures).  The trails are the engine regenerating draws each
    frame, not a texture scroll, a spin or a camera move.

So the animation cannot be a transform applied to one captured frame, and the port replays the
engine's own frames instead:

    dw4asset render --stage <roms> stagml11.igb --ref 0 --scene <menu.tsv> --livedump <menu.bin> \
        --camera --w 640 --h 448 --ui-native 0.42 \
        --ui-seq <sequence-dir> \
        --uitex <sequence-dir>/tex --ui-seq-fps 5.2 --window --frames 1000000

`--ui-seq DIR` cycles `DIR/uiNNN.tsv` in name order, each file one captured frame in GS draw order
(so the trails stay behind the logo, as the hardware drew them), and `--ui-seq-fps` sets the rate.
`scripts/menu_anim_seq.py` builds the sequence from a list of `.gs.zst` captures; a 34-frame set
was built with it.

Two honest limits.  **The rate is the capture rate**: PCSX2's screenshot hotkey writes a GS dump every
~190 ms (5.2 fps measured, 184 ms best case), so this is the engine's real effect sampled at ~5 fps
rather than the 60 fps the game runs.  And it is a **replay, not the engine's update loop**: the
engine still has to be running to produce a sequence.  What it does show is the thing you actually
see — the replayed menu is not one frozen frame; the streams arrive and leave as they do in the game.
Measured on the port's own window, 2.5 s apart: 64% of the display changes, against 0% for a single captured frame.

Cycling whole frames (rather than only the additive draws) is deliberate: splitting by blend and
drawing the additive layer last puts the trails *over* the logo, which the hardware order does not do.

### Frame time: what it is spent on, and the 5× (`--ui-threads`)

Measured on the menu frame (640×448, 208 scene meshes + a 1937-triangle UI replay), by removing one
component at a time — the tool reports ms/frame itself.  With a per-pixel plane evaluation and a
serial replay:

    full (scene + UI + native)   62.5 ms/frame   16 fps
    scene only                    7.3 ms/frame  136 fps
    UI replay only (no scene)    64.5 ms/frame   15 fps
    UI rows, textures off        11.9 ms/frame   84 fps
    nothing                      7.8 ms/frame

So the scene is cheap, the fixed per-frame cost is ~7.5 ms, and the **textured UI replay is the
whole cost**. Two properties of `src/render.c` bring it down:

1. **The plane evaluation is outside the inner loop.** Every interpolated value is linear in x — the
   barycentric weights come from edge functions and the attributes and the GS's per-vertex colour are
   affine in those weights — so a row computes its starting values once and then only adds. There is one
   float divide per pixel, not four (the STQ reciprocal, shared by both axes). 62.5 → 41.5 ms.
2. **The replay is threaded** (`dw4_render_ui_draws`, `--ui-threads`, default one per core). The
   draws must stay in order — the blends compose — so the parallel axis is the framebuffer's **rows**:
   the frame is cut into bands and *every band replays the whole draw list*, each draw clipped to that
   band. Because a draw only writes pixels inside its own bbox, a band performs exactly the writes it
   would have performed serially, in the same order, so the result is **bit-identical** to the serial
   pass (asserted: `ui threads  1 thread vs 8: 0 px differ`, and on the menu frame 1 vs 16 threads
   100.0000% identical). 41.5 → **12.6 ms/frame, 79.6 fps**, and the window shows 62 fps through the
   Vulkan path (FIFO caps it at the display's rate).

Two honest notes. The incremental form accumulates rounding across a row, so the frame is not
bit-identical to a per-pixel evaluation: 22 of 286,720 px differ, mean |delta| 0.0006, all at
triangle edges where coverage flips — the suite's assertions hold either way (`ui perspective` 786 px,
`ui overlay`'s red and half-alpha exact). And the remaining ~7.5 ms is the per-frame fixed cost
(scene traversal and setup), still serial; the UI replay itself is only ~5 ms.

### The output path: Vulkan (`--vulkan`, `src/vk_present.c`)

The frame reaches the display through a **Vulkan swapchain** when `--vulkan` is given (`dw4
--vulkan`, or `dw4asset render --vulkan`); SDL2 creates the window and the `VkSurfaceKHR`,
because that is the supported way in on a Wayland session, but nothing of the frame goes
through SDL's renderer. There are **no shaders and no graphics pipeline**: the framebuffer is
CPU-rasterised, so the path is `vkCmdCopyBufferToImage` into the acquired swapchain image plus two
layout transitions. That keeps it small enough to reason about — and makes the one real hazard
explicit:

- **the format is chosen for byte order, not for looks.** `vkCmdCopyBufferToImage` converts nothing,
  so a `B8G8R8A8` swapchain with an R,G,B,A framebuffer presents the red logo blue — the same
  channel-order hazard as on the SDL path (`window.c`, `SDL_PIXELFORMAT_ARGB8888`). The picker prefers `R8G8B8A8_UNORM`; if
  the surface only offers `B8G8R8A8_*` the frame is swizzled on upload and the backend says so.
- **not sRGB.** `dw4_fb` holds display-encoded bytes (what the SDL path puts on screen verbatim), and
  an sRGB swapchain tells the display pipeline those bytes are linear, so it would apply a gamma
  curve and wash the frame out. `UNORM` is the pass-through, and it is preferred over the sRGB form
  of the same layout.

Where the surface offers `VK_FORMAT_R8G8B8A8_UNORM` (37) the picker lands on it with no swizzle.

**Verified by comparison, not by assertion:** `tools/verify_present.py` renders the same static frame
through both backends at the display's own size and compares what the screen actually shows —
`present: SDL vs Vulkan 100.000% identical, mean |delta| 0.000 ok`. (The same frame was also compared
against the PNG written from the framebuffer: 1,228,706 of 1,228,800 px identical, mean |delta| 0.01.)
`make check` covers it as `host vulkan: loader + device ok (…)`, which runs with SDL's dummy driver —
the device-only path needs no display, and `verify_present.py` skips when the harness has none. Without
the Vulkan or SDL2 development packages the module compiles to no-ops and the caller keeps the SDL path.

### The frame-rate readout (`--fps`, `--osd-text`)

The window's frame rate is drawn into the frame's top left — the counter is on whenever a window is
presenting, and `--fps` / `--no-fps` force or suppress it (a headless render has it off unless asked).
It is a *measured* rate, an exponential average of the **interval between successive frames** as the
loop sees them, not a requested one.  Measure the interval, not the draw: timing only
the draw reads ~240 fps on a 60 Hz output (the present, which is where the time goes, is
excluded).

**The loop is locked to the game's own rate.**  The PS2 game ticks at 60 Hz, so the boot and the stage
loops are paced to **60 fps** (`--fps-lock N`, default 60; `0` leaves the display's own rate, which on a
165 Hz monitor runs the loop — and the frame counter the engine advances — three times too fast).
Measured windowed with the lock: the plate reads 60 and the run logs `presented 1416 frame(s) in
23600 ms` = 60.0 fps.  Headless runs are deliberately **not** paced, so a dump loop stays fast.

Note what the frame rate is *not*: it says nothing about how fast the **content** moves, and on the
`--ui-seq` replay menu the content is the engine's captured frames, which change 5.2 times a second however
smoothly the swapchain presents them (measured from a screen recording: 5.24 changes/s, 200 ms apart,
81% of 30 fps video frames pixel-identical).  That gap is the visible choppiness of the replay; the
generated layer (`src/frontlayer.c`) closes it, not the renderer.  `--osd-text S` draws a fixed string instead, which is what the suite pins
(`osd readout`: ink in the top-left band, 0 px changed outside it, two strings differing on 832 px).

The glyphs come from a **5×7 bitmap font built into the rasteriser** (`dw4_fb_text`, `dw4_fb_plate` —
`0-9 . : f p s m x` only), drawn white with a 1 px shadow over a darkened plate so the number stays
readable on a bright logo. This is explicitly **not the game's text**: the engine generates its own
from `bectext.igb`'s bitmap font, and none of that is wired up here. It exists so a
diagnostic number can be read off the frame itself.

### The native half: the front-end's own UI geometry (`--ui-native`)

`--ui-native` draws the front-end's 2D layer from the *pack's own meshes* instead of a dump: a scene
row whose mesh is small (its local extent at most `--ui-extent`, default 400 units) and placed
inside the screen's coordinate range is the 2D layer -- the logo quad, the window panels
(`win0Shape1..4`), the separator lines (`sen`), the cursors (`curShape`, `selcurShape`, `wakuShape`)
-- and it draws in **screen space** (origin at the framebuffer centre, +x right, +y up, one model
unit to `--ui-scale` pixels) through the same `dw4_render_ui_tri` primitive: unlit, alpha-blended,
no depth.  The scale is what fits the layout: the panels sit at x = ±764, which lands them on a
640-wide framebuffer at `--ui-scale 0.42`.

```sh
./build/dw4asset render --stage <roms> stagml11.igb --ref 0 --scene menu.tsv \
    --livedump menu.bin --camera --w 640 --h 448 --ui-native 0.42 \
    --ui /tmp/ui/ui.tsv --uitex /tmp/ui --out-dir /tmp/menu
```

Two honest limits keep it short of the whole screen.  First, the **layout is code**: the engine
computes each element's place, so the packs carry the meshes but not all their placements, and the
capture's live node names do not all line up with the pack's (`polySurfaceShape2` in the capture vs
`polySurfaceShape100` in the pack), so only the rows that match by name get their geometry.  Second,
the **text is generated**: the menu strings are rendered into bitmap-font quads by the engine
(`bectext.igb`'s `igBitmapFont` + `font00.png`), so the pack holds no text quad to draw -- the
script above therefore pairs `--ui-native` with `--ui` for the text, and together they show the real
menu (Game Start / Option, the cursors, the copyright) over the port's own textured scene.  The
shipped front-end does not use this path: it decodes `bectext.igb` (`src/fefont.c`) and draws the pack's
own UI graphs (`src/frontui.c`), as described under the title/menu presentation above.

## Lighting (P4.4)

The shading **model** is the game's. The VU1 LIGHT programs name `AMBIENT`, `DIRECTIONAL` (infinite),
`POSITIONAL`/`LOCAL`, `SPOTLIGHT`, `LINEAR_ATT` and `_SPEC`/`_NOSPEC`, and
`igLightAttr` gives the semantic fields (position, ambient, diffuse, specular, direction, falloff,
cutoff, attenuation, shininess). `p2lighting` (`0x1fb710`) — the EE function that packs those into the
VU1's 16-byte constant records — is decoded in the decompilation repo's
[`docs/engine/p2-lighting.md`](../docs/engine/p2-lighting.md). `render.c`
implements that model: per light, an ambient term plus a two-sided `N·L` diffuse term, a positional
`d`/`d²` attenuation (or a linear cut to `range`), a spotlight cone between the falloff and cutoff
angles, and an optional Blinn-Phong `(N·H)^shininess` specular when the eye is known.

**The rig: what is in the disc, and what the game actually uses.** The *source*
objects are ordinary **`igLightAttr` records in the packs** — `scripts/pack_lights.py --list|--emit`
reads them, `NDMW.AFS:614` carrying ambient `0.5,0.5,0.55`, a key `(1.3,1.3,1.17)` along
`(0.3214,-0.866,0.383)`, and a white overhead spot at `(0,90,0)` with a 30° cone. But they are
**prototypes, not the runtime rig**: read mid-render (the only way — the tables are empty in every
savestate and in a slow whole-RAM dump) the live descriptors are **ambient
`0.25,0.20,0.35` plus one directional light of `1.20,1.15,1.20` along `(0.3214,-0.866,0.383)`** — the
same directions and cutoffs as the prototypes, different colours, and **no third light**. Those live
values appear **nowhere in the disc** (a byte search for both triples: 0 hits), so the runtime
derivation is still unknown. The built-in default is that live read **re-fitted**
(below); `--lights` takes the live read itself. The packs'
`igLightAttr` rig is not it, and the default carries no overhead spot;
`--lights FILE` overrides the default.

**The rig is fitted against a resampled reference.**
The camera-matched reference is a PCSX2 savestate screenshot: **640×480**, because the screenshot is
the 448-line framebuffer scaled by 480/448.  Comparing its top 448 rows against the port's 640×448
framebuffer mixes two vertical scales — inflating every number and moving features (an apparent
"the port's barrel sits ~12 px too high" is that artifact, not a placement error).
`tools/frame_metric.py` always resamples the reference to the frame's size, which is a no-op for a
reference that is already 640×448, and `make check` runs its `--self-test`. On the corrected
reference the live-read rig measures **19.26** (figures scored against the stretched screenshot, such
as a 27.09 → 24.73 pair, are not comparable), and a fit driven by the floor and wall alone is
**degenerate**: their normals barely vary, so the up-facing
facets of the flat-shaded props clip to white. Re-fitted with the **props in the objective** (they
are the only surfaces supplying up, radial and down normals), the rig is **ambient
`0.3005,0.2444,0.2986` plus one directional light of `0.7931,0.7938,1.3141` along
`(0.3482,-0.9370,0.0272)`** — and the frame drops, with the props leading:

| region | live-read rig | re-fitted |
| --- | --- | --- |
| whole | 19.26 | **17.92** |
| floor | 9.45 | 9.48 |
| wall | 19.81 | **16.62** |
| barrel | 22.57 | **20.77** |
| crate | 29.33 | **24.93** |

The rig is still a **fit, not a decode** — `docs/engine/p2-lighting.md` records that the values the
game feeds `p2lighting` exist nowhere on the disc — so `tools/fit_light_rig.py` drives
`build/dw4asset render` as a black box (Nelder-Mead over nine parameters) and fits it.

**What the re-fit does not fix: the props' metal trim (open).** The wooden
crate/barrel are the worst regions on the corrected reference (22.57 / 29.33 with the live-read rig, 20.77 / 24.93
re-fitted) and their **grey metal bands stay pale and blue-cast** where the game's are mid grey —
`(91.7,94.6,96.6)` against the game's `(89.2,83.7,80.4)`.  The cause is not the texture: the barrel
draw's `TEX0 0x4007950555307ca4` (`TBP 0x3ca400`) decodes out of the GS dump's own VRAM to **RGB
byte-identical** to the pack's inline `g_bbarrelsz01` (mean |Δ| 0.0).  Nor is it "unlit" (that
draw's per-vertex RGBA varies `31,25,44 … 127,127,127`, so the props *are* lit), nor culling, nor
`--flat`/`--one-sided`/`--nearest` (all worse).  It is the shading: the mesh ships normals that are
**exactly its face normals** (geometric · authored is ±1 on all 263 triangles — it is flat-shaded by
design), its hoops and rim have **+Y facets**, and the surface-to-light is ≈0.87 up, so those facets
get shade ≈1.29 and **clip to white** (a textureless render shows the hoops solid white).  Every
vertex colour the GS receives tops out at **127/255 = 0.5**.  A fit weighted on the metal pixels
bottoms out at 31.6 mean |Δ| and a rig fitted on the props alone still renders the bands pale, so the
residual is structural, not a rig value — it needs the props' own light program (the ucode map has
`LIGHT_LOCAL_OBJ_1_NOSPEC`, a one-object local light, alongside the world's `LIGHT_INFINITE_4`),
whose parameters are not on the disc either.

**Back-face culling and the strip winding.** The game culls at the VU1 clip stage
(`CLIPBACK`/`CULLBACK` and the twelve `CLIP_*_CULLFACE` programs in `docs/engine/vu1-microcode.md`),
and the port draws both faces by default.  Culling depends on the strip winding: `dw4_mesh_tris`
alternates it, because emitting `(k, k+1, k+2)` for every triangle of a strip winds **half of every strip backwards**
(96 of the barrel's 263 triangles then have a geometric normal opposing their authored one).  With the
alternating winding, culling is a **no-op on this frame** — byte-identical output, because the back faces
are already depth-occluded — so it is a knob (`--cull` / `--cull-front` / `--no-cull`, default off),
not a fix.

```sh
# use a rig read live (the read needs the game mid-render; ~300-1700 samples/s on one PINE connection)
./build/dw4asset render ... --lights <rig>.txt --ambient 0.25,0.2,0.35
# unlit: skip the light term entirely (wrong for this frame -- it measures 27.36
# on the corrected reference, against 17.98 lit)
./build/dw4asset render ... --unlit
```

A rig can also be supplied explicitly:

```sh
# the built-in rig (the re-fitted live rig, above): the default
./build/dw4asset render --afs NDMW.AFS --entry 621 --name pCylinderShape3 --out cyl.png
# an explicit rig
./build/dw4asset render --afs NDMW.AFS --entry 621 --name pCylinderShape3 --out cyl.png \
  --ambient 0.10,0.10,0.12 \
  --light 'dir,0,0,0,-0.4,-0.6,-0.7,0.9,0.9,0.85,0,0,0,0,16,0,0'
./build/dw4asset render ... --lights rig.txt      # one SPEC per line, the same format
./build/dw4asset render ... --one-sided          # max(0, N·L) instead of |N·L| (default: two-sided)
./build/dw4asset render ... --tint R,G,B          # one constant colour for every row (there is no hash tint)
./build/dw4asset render ... --uv-offset U,V      # the engine's texture matrix as a UV offset
./build/dw4asset render ... --uv-scale S         # ... and a UV scale (the tile question)
```

**The texture matrix is a UV offset, and the ground material enables one it does not carry.**
The engine's `igTextureMatrixAttr` exists and 54 instances live in a Goblin Pass dump; every one is the
identity with a translation in matrix elements 12..13 (`_isProjective = 0` throughout) — so it is a UV
offset, which is what the wall's "tile choice" turns out to mean. `BGGround00n`'s attr set enables
the unit (`igTextureMatrixStateAttr._enabled = 1`) but holds only seven attributes and **no matrix**, so
the value comes from elsewhere (the pool, a node-level sibling, or the draw code) and is still
unlocated. `--uv-offset`/`--uv-scale` are the measurement knobs for finding it: inert by default (the
baseline render is byte-identical), and a *global* affine is not the answer — a UV scale of 2–4 fixes
the wall box (mean abs error 37.5 → 24.0 against the real frame) while wrecking the floor
(`75.4,53.6,31.1 → 88.9,84.8,88.7`), i.e. the transform is per material.

**The GS dump route works.** With
`GSDumpSingleFrame = Keyboard/F8` seeded in PCSX2's `[Hotkeys]` (it is unbound as shipped) and
`pi-input key F8 --activate` while the game runs, PCSX2 writes a `.gs.zst` dump beside a PNG of the
same frame. The format is PCSX2's own (`GS/GSDump.cpp`): fake CRC `0xFFFFFFFF`, a u32 header size, a
9-word header, the serial, the screenshot, the freeze data, a `GSPrivRegSet`, then `transfer = u8 0 +
u8 index + u32 size + payload` / `readfifo = u8 2 + u32 size` / `vsync = u8 3 + GSPrivRegSet + u8 1 +
u8 field` records. `scripts/gsdump.py` walks them (verified here: 7,572 records = 7,568 transfers +
4 vsyncs, the chain walking exactly to the end of the file) and decodes the GIF packets inside.

What this frame's stream contains settles the colour question. The frame has **6,988
packets / 45,732 vertices, almost all PACKED `NREG=3`**, and the tag's `REGS` is `0xfffff412`, which
PCSX2's `GIFPath::SetTag` unpacks to registers `(2,1,4)` = **`STQ, RGBA, XYZF2`**. That is the
`STQRGBAXYZF2` complex type (`regs.U32[0] == 0x00040102`), and the handler reads the middle register's
low bytes as RGBA: the vertex format **does** carry a per-vertex colour. (The
middle register is RGBA, not `UV`; reading it as `UV` gives the false conclusion "no colour register".) The values are the engine's VU1
lighting result — the dominant `(31,25,44)` is exactly 125× the live ambient `0.25,0.20,0.35`, and
`(127,127,127)` is the clamped lit max × 0.5 — so the world is **lit**, not unlit, and the port
reproduces those colours with the live rig rather than a constant. `scripts/gsdump.py
--state|--draws` prints the freeze state and the per-draw TEX0/PRIM/vertex colours, and
`--tex TEX0 --tex-out F.png` decodes a texture out of the dump's VRAM.

**The world's blend is opaque, and the GS command stream is not in EE RAM.** All four ground
palettes are constant alpha `0x80`, which the GS reads as 1.0, so `igBlendStateAttr._enabled = 1`
(`src=4, dst=5`) reduces to a copy — the port needs no blending for these draws, and the blend is not
what darkens the wall. And the GS command stream itself cannot be read from a memory dump: a whole
32 MB scan for GIF tags finds only MIPS code, the region thought to hold "16-byte command
records" holds per-vertex data instead, and the VU1 mirrors (`0x11000000`) read as zeros through PINE.
The route to the per-draw state is a PCSX2 `.gs` dump (configure its hotkey in the host PCSX2 settings) plus a
parser for it.

A SPEC is `type,px,py,pz,dx,dy,dz,dr,dg,db,sr,sg,sb,range,shininess,falloff_deg,cutoff_deg`, with
`type` one of `dir` / `point` / `spot` (an all-zero specular is `_NOSPEC`). `--lights FILE` loads the
rig of a *specific* pack without a code change, which matters because the packs differ: `NDMW.AFS:614`
(the Goblin Pass stage) carries ambient `0.5,0.5,0.55` with a key `(0.3214,-0.866,0.383)·(1.3,1.3,1.17)`.
There is **no** per-mesh hash tint: there is no per-mesh
material colour to recover — the world materials carry **no** `igMaterialAttr`/`igColorAttr` at all,
only a texture bind plus state — so a scene row is white unless `--tint` sets one colour
for every row:

**The world material state is live-built, and the port ignores all of it.**
`beTextureCtrlInfo`/`beTextureCtrlAttr` — 90 material sets in the Goblin Pass dump, built at load time
and **not present in the pack** — carry the state the port otherwise guesses at. The two that cover
most of this frame, `BGGround00n` (ground and its rock walls) and `BGObj00n` (world objects), both say
**`igLightingStateAttr._enabled = 0`** — there is no fixed-function lighting *state*, but the VU1
still computes the per-vertex colour the GS carries — with `igBlendStateAttr._enabled = 1` (`src=4, dst=5` and `src=4,
dst=1`), `igDepthWriteStateAttr._enabled = 0`, `igCullFaceAttr._enabled = 0` and
`igTextureMatrixStateAttr._enabled = 1`. `scripts/live_materials.py --from <dump> --dump` prints them
all. Measured: `--unlit` (`75.4,53.6,31.1` floor) is closer on the **floor** than the lit frame
(`68.1,47.1,31.1`; real `69.7,47.5,30.6`) but makes the **wall** overshoot badly (`59.5,66.6,49.1`
against the real `40.9,36.5,41.2`), and the whole frame regresses to **27.36** — so the world is not
drawn unlit. What the port uses is the opposite: the game's *live* rig with no
per-mesh tint (**19.26** on the corrected reference), and then that rig re-fitted with the props
in the objective (**17.98**).

**Which texture a world mesh uses, and which mesh the frame draws.** Each
`beTextureCtrlAttr` lists the geometry shapes it applies to, so a mesh's texture is recoverable by
matching the record's shape to the pack attribute on **(primType, numPrims)** — the vertex-buffer
content match never reaches these meshes. The map: `BGGround00n` = `P11G00n` ×5 shapes + `P10G00n` ×1 +
`P10G02n` ×1, `BGGround00s` = `P11G00s` ×4 + `P10G00s` ×1, `wall01z01` = `TA01GM02` ×5, and 15
`BGObj00n` records of 1–6 shapes. **No single texture covers the world** — it
is *not* all `P11G00n`. **The map is applied:** `camera_match.py` resolves each
world row from its live material's `beTextureCtrlAttr` by the same `(primType, numPrims)` key (a key the
materials disagree on — the small UI/prop shapes — falls back to the stage-material pick rather than
guess), so each row carries its own material's texture instead of the set's first name; it changes
**0 px** on this frame because 21835 was already `P11G00n`. Measuring which rows this frame actually
draws (one row re-textured at
a time to a near-white atlas) shows **only pack 21835 is visible**: it changes 114,809 px — 41 % of the
frame and 99.8 % of the wall box — while every other row changes *zero* pixels. 21835 is the only
199-prim attribute in the pack and its live record binds `P11G00n`, which is what the port already uses,
so a texture swap is not what fixes the world geometry. **The GS dump then proves the port's choice is
right:** the world draw's `TEX0` (`0x40060805e1312fc0`, TBP `0x2fc000`, TBW 4, PSMT8
256×128, CBP `0x304000`) decodes out of the dump's VRAM to an index map **byte-identical to `P11G00n`
flipped vertically (32768/32768) with `P11G00n`'s own CT32 CLUT**, and the draw's STQ pairs match the
pack UVs exactly — so `P11G00n` *is* the real frame's world texture, the `(primType, numPrims)` key did
survive, and the map does not conflict with the real frame. The floor is `P11G00s` (`0x40063405dd30b160`) and
the character classifies to `P_susanoo01`, matching the Susanoomon player node.

**What the shading model was *not*.** Four suspects were measured on the camera-matched
Goblin Pass frame against the real PS2 frame and each is neutral or worse, so they are not to be
retried: **one-sided `N·L` is a no-op** there (`--one-sided` changes a handful of pixels — every
visible surface already has `N·L > 0`, because the key light sits behind the camera, so `|N·L|` and
`max(0,N·L)` agree); the **white tint is much worse** (wall mean `33.5,32.3,26.7 → 58.0,64.9,49.6`
against the real `40.9,36.5,41.2`); the **specular term is negligible** (zeroing it leaves the frame
means unchanged); and the **stage pack's own rig is not closer** (it collapses the wall to
`21.4,20.6,14.4` and the wall/floor ratio to 0.36 against the real 0.80 and the built-in rig's 0.63).
The one measured improvement is the meshes' **own vertex normals**, below.

**Fog** is the second VU1 family implemented, on both backends.  Its three programs
are `FOG_LINEAR`, `FOG_EXP` and `FOG_EXP2` (the `CLIP_FOG_*` variants are the same effect at the
clip stage); the fragment blends toward a fog colour by **view-space depth**.  `--fog
'<linear|exp|exp2>,start,end,density,R,G,B'` installs a caller rig and `--no-fog` drops it.

The **game's own rig is recovered** and is the *default* for a scene render.
The engine's stage fog is a `FOG_LINEAR` program — near **60** / far **300** in view-space depth —
lerping toward `FOGCOL` **0xE5CCE5** `(229,204,229)`.  The evidence is the same-instant GS dump: the
per-vertex fog value `F` is stored in the packed `XYZF2` 4th dword (PCSX2's
`GIFPackedRegHandlerSTQRGBAXYZF2`: `F = (dword44 >> 4) & 0xff` — *not* the top byte of the Z dword,
which is structurally 0, and reading it makes fog look dead), and it is linear in the
view-space depth to 0.25/255 across 44,100 vertices, while `PRIM.FGE` is set on 99.96 % of the
covered frame.  The framebuffer follows `out = C·(F/255) + FOGCOL·(1 − F/255)`.  The engine also
keeps the values as live object fields (`igPsx2VisualContext._fogEnable/_fogDensity/_fogMode/
_fogColor/_fogNear/_fogFar`), and the pair `(60, 300)` appears as a float pair across the RAM.

`dw4_render_game_fog()` returns that rig; `render.c` computes `F` **per vertex** (a function of
view-space `z`, as the VU1 does), interpolates it **affinely** in screen space like the vertex
colour, and blends.  `--fog` overrides, `--no-fog` turns it off.  On the goblin-pass capture at
`--blur 1.2` the whole-frame mean `|Δ|` falls **14.70 → 10.96** (wall 13.83 → 11.80, barrel
12.17 → 8.28, crate 16.71 → 14.36, character 23.13 → 21.89), which is the ship criterion;
`tools/verify_render.py` asserts the default actually applies (a scene render differs from
`--no-fog`) while its shading/modulate checks run with `--no-fog`.

And it is honest about what is missing: the GS's register state, the VU1 microcode's transform and
lighting, and **two load-time assignments** — the mesh → texture *binding* (`igGeometryAttr1_5` has no material reference at all, its ordinals 5/9/11/12 being NULL in all 549
attributes) and the stage's **object placement** (the model node's attr list is empty in
all 1,075 records and nothing in the file references an `igGeometry`). One live scene capture closes
both.  The **material colours** are the same shape: a mesh is drawn
with its texture if a caller or its scene row names one and white otherwise (`--tint` sets one colour
for every row) — there is no per-mesh material colour to recover, and the texture binding is a load-time
assignment on the `igTextureBindAttr`/`igGeometryAttr` path that no file record states. The live capture's material walk reads that binding (the texture link, above).

## The live path: textures work end to end

At runtime the refs are ordinary **pointers**, and the chain is reachable from an object the
live-object scan *does* see:

```
beTextureCtrlData._tex (+12) -> igTextureAttr._image (+48) -> igImage
    _pImage (+52)  the pixel buffer          _pClut (+68) -> igClut._pData (+20)  the palette
```

Following it from a running game feeds this decoder.

**46 textures** come out of a loaded save, with their real asset names, and they are correct by eye —
the status-screen label atlas (`stmojipnl01.png`: Strength/Defense/Wisdom/Spirit/Speed/LV/Max MP/Max
HP/Tech/Skill/EXP, the digits, the icons), dialogue text (`stcngmoji.png` — “Go to the destination.” /
“Stay here.”), gradients and ramps.

Three facts the pixels settled, all visible in the decoder:

- the palette is **32-bit, 4 bytes per entry, memory order R,G,B,A** (`igClut._numEntries` 256,
  `_stride` 4, `_clutSize` 1024) — PS2 CSM1 does not fit those numbers;
- textures are stored **bottom-up** (`--flip` is what makes them read the right way up);
- the source is a **plain linear 8-bit indexed image**, not swizzled — `_bytesPerRow == _px` and
  `_pfmt` 0x00010000 for all 46.

Extraction *without* a running game does not go through this path: the texture pack and the model
pack are read offline (the sections above).
Everything below the ordinal boundary — containers, tables, path lookup, the texture decode — is done
and cross-checked.

## The sound path: the `ps2_` banks decode off-line

Sound does **not** need the live path, because its buffers are inside the bank, not behind an ordinal.
A stage's sound pack (`NDMW.AFS` entry 620 for `stag0102`, the `<stage>.sfp` set) is an igBinary
container whose *content pool* holds **six self-contained CRI banks** — one per entity, named by the
pack's `beCriSfpData` records (`e_goburi.sfp`, `e_ogre.sfp`, `common_blst.sfp`, `scannon.sfp`,
`stag0102.sfp`, `e_blosso.sfp`). Each bank is three chunks at fixed offsets:

```
+0x000  ps2_DTPK   {pcm_size (+0x0c), field (+0x10), vag_size (+0x18), header_size (+0x1c) = 0x800}
+0x060  ps2_TBLD   {length (+0x0c)}, decode tables, then one 16-byte record per sound:
                  {u16 x, u16 rate, u32 a, u32 end, u32 0} — `end` is the entry boundary
+0x800  ps2_VAGD   {vag_size (+0x0c)}, 0x20-byte header, then the ADPCM
```

The ADPCM is Sony **VAG** with a 16-byte frame, but three details a plain VAG decoder gets wrong were
pinned by matching ffmpeg's `adpcm_psx` sample-for-sample:

- the samples are bytes **2..15** of the frame (byte 1 is a *control* byte, so the 14 sample bytes are
  the tail of the frame, not the head);
- byte 1 = **0x07 silences the frame** and resets the predictor — that is the end-of-sound padding
  between entries;
- the predictor feeds back the **unclamped** sample; only the output is clamped to int16 (and the
  prediction is a truncating `/ 64`).

So the whole sound layer is testable on its own:

```sh
./build/dw4asset sfp --afs /path/NDMW.AFS --entry 620            # 6 named banks, entries, names
./build/dw4asset sfp --afs /path/NDMW.AFS --entry 620 --bank 0 --wav e_goburi.wav
./build/dw4asset sfp --afs /path/NDMW.AFS --entry 620 --name goNATK01 --wav one.wav
```

The banks and their sounds are **named**: the pack's `beCriSfpData` records name each
bank and their `_pcmSize` matches the DTPK size exactly, and each `beSoundData` record says its bank
(`_fnameIdx`, via the stage's `beSoundInfo._fnameList`) and its entry (`_memoryIdx` high 16 bits). All
**33** stage entries come out named and coherent — `goDEAD01`/`goNATK01`… in `e_goburi`, `og*` in
`e_ogre`, `bl*` in `e_blosso`, the four blasts in `common_blst`, and the stage objects
(`TARU_BLST01`, `OBJ_TORCH_CRASH`, `drOFF2ON`…) in `stag0102.sfp`.

`tools/verify_sound.py` extracts the same ADPCM in Python, wraps it in a `VAGp` header, and compares
ffmpeg's decode with the C tool's WAV: **all six banks (773,472 samples) are sample-for-sample exact**,
the per-sound entry table tiles each chunk exactly, and the bank names and the 33 names are asserted.
The global `allse.sfp` bank (64 sounds) is in `sbiallse.igb`,
NDMW entry 897. Its unaligned DTPK offset requires byte-wise scanning. Title music is
standalone ADX in the archive; see [native audio playback](docs/audio-playback.md).

**Models on the live path — exactly how far the same trick gets** (the offline reader is
*The model pack* above). A heap
scan for the shape `{code-pointer, instance-word, data-pointer, count, type, flags}` finds the class
(vtable **0x00526590**, 28 objects with counts 107–711), and a graph walk from a live
`beModelCtrlNode2` finds smaller instances of it. But their buffers are **small integers** — `3`/`4`
dominating, and `13,14,13,14,…,29,29` in the small ones, i.e. a triangle-strip index list — so these
read as **index arrays, not positions**. Two measured facts bear on decoding them:

- **The reflection offsets do not match the live object.** `igIndexArray` is reflected as
  `_memPool`(+8), `_indexData`(+12), … (a data pointer at +12), but the live objects hold a **data
  pointer at +8** and a count at +12; `igVertexArray`'s reflected `_vdata`(+8)/`_numVerts`(+12) fits the
  header shape, yet the same class's buffers are index-like — so the two cannot be told apart from
  reflection alone.
- **The engine's `ig*` classes are in the recovered vtables.** The map is **976 of
  the 1,074 reflection classes** — the 478 RTTI-headed vtables plus **498 recovered from each class's
  own `<Class>_GetVTable`** (`../data/vtables-getvtable.json`). The three vtables this route
  meets all resolve — `0x525630` `igPsx2Image`, `0x522c60` `igTextureAttr`, `0x526590`
  `igPrimLengthArray1_1` — and the port's generated schema carries the address for every one of
  them (`tools/gen_reflection.py` merges both sources), so a live `+0` word names its class; the host
  check pins the three managers stamping their **own** vtables (`0x529110`/`0x529e70`/`0x52a020`)
  rather than the base `0x52f0f0`. Residual: `0x5284f0` (the largest live class, 1,507 objects) is
  not in the map because its `_GetVTable` detector prefers a base vtable for derived classes, and a
  class's **inherited** fields are a separate lookup — `igPsx2Image` reflects no own fields, `igImage`
  has 21.

What to look for next: **pair the skinning palette** — the per-vertex stream is recovered (the live
`igVertexArray1_1._blendWeights`/`_blendIndices`) and so is the bone-select map
(`igBlendMatrixSelect._blendMatrixIndices`, 33 entries over 24 matrix slots), but no field links a mesh
to its `igBlendMatricesAttr._matrixCache`, so the bind pose stands.  Then the **world/crate
material**, whose texture is applied in the staged packet stream rather than the object graph.
Two smaller leads remain from the class-map work: a buffer
whose **stride is 16 or 32 bytes** parsing as packed PS2 vertex data — none of the 28 candidates is
one; and the `igNode` chain still has to reach whatever owns the render list (`igGeometry._renderList`,
+40).

`make check` needs the game's own archives, which are **not** in this repository (no game binary is):
extract `NDMW.AFS` and `NDMW.IGB` from your disc into `DW4_ROMS`.
