# AFS Archives

Two CRI **AFS** archives hold the bulk of the game data: `NDMW.AFS` at ISO 0x1ED11000 and `AREA.AFS` at
ISO 0x5A9000.

| Archive | Entries | File size | Contents |
| --- | --- | --- | --- |
| `NDMW.AFS` | **972** | 727,056,384 B (≈727 MB) | 79 standalone ADX streams, then per-stage data packs: `ig*` reflection metadata + **5,291 Lua 4.0.1 bytecode chunks** + textures/models |
| `AREA.AFS` | **1,382** | 511,082,496 B (≈511 MB) | 3 FMV movies + level geometry/animation/texture packs |

## AFS container format
```
offset 0 : magic   "AFS\0"                 (4 bytes)
offset 4 : count   u32 LE                  (number of files)
offset 8 : entries[count] * { u32 offset, u32 size }   (8 bytes each)
...      : file data (offsets are absolute from file start)
```
The entry table ends at `8 + count*8`; the first data block usually starts
page-aligned (0x2000 for NDMW, 0x3000 for AREA).

### NDMW.AFS first entries
```
[  0] off=0x00002000 size=4401152  magic 80 00 07 fc 03 12 04 02  (ADX stream)
[  1] off=0x00434800 size=4401152  ...
[  5] off=0x013f5800 size=1078942  magic 80 00 00 24 ...          (ADX stream)
...
[967] off=0x2b536000 size=  18773  magic a4 03 00 00 28 00 00 00
[971] off=0x2b54d000 size=  29420  magic 44 05 00 00 38 00 00 00
```

### AREA.AFS first entries
```
[  0] off=0x00003000 size=40091648  magic 00 00 01 ba  -> CRI Sofdec, MPEG-1 video + ADX audio
[  1] off=0x0263f000 size=40091648  MPEG
[  2] off=0x04c7b000 size=40312832  MPEG
[  3] off=0x072ed000 size=  447477  magic a8 12 00 00 a8 00 00 00  -> {count,stride}, the text pack
...                                 (level geometry / animation packs)
```

## Lua chunk storage (NDMW.AFS)
- **5,291 Lua 4.0.1 chunks** are concatenated inside ~100 entries.
- First script entry is **entry 179**; the big script block is entries 179–832.
- Each entry is a **stage pack** = `[ig* reflection metadata][Lua chunks…]`.
  The first `1B "Lua"` magic in entry 179 is at relative offset `0x12a4a4`.
- Chunk distribution (selection):
```
entry 179 : 35 chunks   entry 816 : 155 chunks   entry 820 : 64
entry 824 : 114         entry 828 : 60           entry 832 : 5
...entries 179..832 (stride mostly 8 in the range 179..535)
```
Total: 5,291 chunks, 17,239 unique string constants.

### Finding chunks
Every chunk starts with the literal bytes `1B 4C 75 61` (`ESC "Lua"`).
Chunks are self-delimiting (a recursive `Proto` parse consumes exactly one
chunk), so no external size table is needed.

### Chunk properties
- Version byte `0x40` (Lua 4.0), little-endian, `sizeof(Instruction)=4`,
  `sizeof(Number)=8`.
- All chunks have `source = '=(none)'` (compiled from in-memory strings).
- Named script files (`bML01001.lua`, `armorshop.lua`, …) appear as **string
  constants** (passed to `_callLuaFile`), not as chunk `source` fields.

## Reflection metadata (pre-Lua region)
The bytes before the first Lua magic in a script entry are **igBinary (IGB)**
serialized reflection metadata. The type names visible there include the engine
types (`igObject`, `igNode`, `igTransform`, …) and the game types (`beBaseInfo`,
`beModelCtrl*`, `beSaveData*`, …). See `docs/engine/reflection-metadata.md`.

Example (entry 179, pre-Lua) — field names present in the metadata:
```
hp mhp mp mmp level lv def power hit waza no kazu stun sleep poison guard
beBaseInfo beBaseInfoRam beNDMWStatusInfo beNDMWStatusInfoRam beNDMWPanelWazaInfo
beLuaData beLuaDataObject beActionStarterData beModelCtrlAIData ...
```

## `NDMW.IGB` — the root manifest, which is also the virtual filesystem

A standalone 106,350-byte igBinary file (first words `00 01 00 00 0B 00 00 00 …`). Decoded,
it is a schema of **20 classes** and 2,297 objects; the container's own record decode
(`scripts/igb_inst.py`) reaches them, and two classes carry the whole filesystem
:

| class | fields | meaning |
| --- | --- | --- |
| `beNDMWAfsSetupData` | `_name`, `_fileCount` | one entry per archive: `ndmw.afs` 972, `area.afs` 1382 |
| `igAdxAfsFile` | `_name`, `_ptNumber`, `_fileNumber` | one per file: which archive, which entry |

So **`_ptNumber` 0 is `NDMW.AFS` and 1 is `AREA.AFS`**, and a name resolves to an
`(archive, entry)` pair. The manifest names **2,080 files — all 1,382 AREA entries and 697 of
NDMW's 972**. Two anchors check it: `(0, 140)` is `stag0102.igb`, the manifest at AFS entry 140, and
`(1, 0)` is `aeu_opening.sfd`, whose AREA entry 0 starts `00 00 01 ba`, an MPEG pack.

```sh
python3 scripts/afs_manifest_names.py <path>/NDMW.IGB            # name, archive, entry
python3 scripts/afs_manifest_names.py <path>/NDMW.IGB --entry 140 # -> stag0102.igb
python3 scripts/afs_manifest_names.py <path>/NDMW.IGB --grep stag01
```

What the names show about the NDMW layout: the stage manifests sit in a run
(`stag0000.igb` = entry 137, `stag0101` = 139, `stag0102` = 140, …), and after them the
entries repeat in **groups of seven** — `generatorh.igb`, `generatorn.igb`,
`generatorv.igb`, `lh_pack.igb`, `ls_pack.igb` and two **unnamed** entries. Those two
unnamed ones are the packs a stage manifest reaches *by index* rather than by name: the
`[0.620]`/`[0.621]` pair (`stag0102`'s sound and model packs) is entries 620 and 621. The
remaining unnamed entries are the 0–136 lead-in (entries 0–78 are the ADX streams) and the
same two slots in every later group.

The object mix, as a sanity check on the schema: `igAdxAfsFile` 2,080, `igNamedObject`
106, `igNamedObjectList` 105, then a handful of `beNDMWAfsSetupData`/`igInfo`/`igInfoList`
records — the lists being `igMemoryRef`s into the content pool after the stream.

### `[<ptNumber>.<fileNumber>]` — the notation a stage manifest uses

A stage's own file list spells its packs the same way the root manifest addresses them:
`stag0102.igb` (AFS entry 140) contains the literal strings **`[0.620]/s`** and
**`[0.621]`**, i.e. `<part>.<entry>` with part 0 = `NDMW.AFS`. So a stage's two unnamed packs
are **NDMW.AFS entries 620 and 621**. The indices are addresses, and the root manifest leaves
exactly those two slots in each group unnamed because a stage reaches them positionally. The `/s` suffix on
the sound pack's string is a variant marker in the list, not part of the pair.

Resolved, so the indices are no longer opaque:

| stage manifest | reference | resolves to | bytes |
| --- | --- | --- | --- |
| `stag0102.igb` (entry 140) | `[0.620]` | `NDMW.AFS` entry 620 | 494,084 |
| | `[0.621]` | `NDMW.AFS` entry 621 | 5,060,706 |
| `stag0201.igb` | `[0.641]` | `NDMW.AFS` entry 641 | 346,670 |
| | `[0.642]` | `NDMW.AFS` entry 642 | 5,173,220 |

The pair is `(base+0, base+1)` in `NDMW.AFS` — sound then model — and `642` is the pack the test
below swaps into `stag0102`. A sweep of the whole table confirms **2,079 of the 2,080 named files resolve into their archive**; the 2,080th is the
manifest's own `NONE` record (`_ptNumber` 0, `_fileNumber` -1).

### A stage's file list is what loads

A stage manifest's `_fnames` is the pack list the game loads at run time (`beFileListInfo`, managed by
`beFileListInfoManager`: singleton accessor `0x381990`, global `0x5996f8`). On a patched disc, changing
`stag0102.igb`'s `[0.621]` to `[0.642]` (same size, three digits) and loading the stage fresh from disc
through the dev stage select leaves `E_mummy01.png` and `mummy_skinShape` in RAM and no `E_goburi01.png`
or `gobr_skinShape2`. A savestate cannot test this, because it carries the already-loaded world.

A stage's model pack also carries its level geometry, so a manifest swap is a diagnostic and not a
usable mod: after that swap RAM holds `Stage0201` strings and no `Stage0102` strings, and the stage
renders as a corrupt hybrid. Loading both model packs (`[0.642]` in the sound slot, keeping `[0.621]`)
crashes the emulator during the load with wild TLB misses, while the unpatched disc loads normally. The
cause is not isolated: EE memory, or the shared objects both packs define, are the candidates. To add
an enemy to a stage, merge its records and assets into that stage's own pack.

## Area names

Area names are not in `NDMW.AFS`. They sit in the text pack `AREA.AFS` entry 3 (447,477 bytes, ISO
0x7896000) as UTF-16LE strings (some copies UTF-16BE), null-padded and mixed with menu labels, with no
contiguous block and no stage index, so the pool alone cannot map a stage to its name. The gate prompt
and the loading banner can name the same destination differently (Goblin Pass and Rotating Hall), so
they come from different tables.

## Extraction recipes
```sh
# List AFS entries (offsets/sizes) and Lua chunk counts
python3 - <<'PY'
import struct, re
d=open('NDMW.AFS','rb').read()
assert d[:4]==b'AFS\x00'
n=struct.unpack('<I', d[4:8])[0]
print('entries:', n)
PY

# Dump Lua chunks from one entry
python3 scripts/lua_dump.py /tmp/lua_179.bin --limit=2
python3 scripts/lua_extract.py /path/NDMW.AFS /tmp/dw4_lua_strings.jsonl

# Fully decompile every chunk to readable Lua (see docs/engine/lua-decompilation.md)
python3 scripts/lua_decompile.py /path/NDMW.AFS --out=build/lua_decompiled
python3 scripts/build_lua_tree.py                # files the chunks by stage into lua/
```

> **Note**: the scripts are now fully decompiled to `lua/`
> ([index](lua-tree-layout.md)). The raw bytecode tools above (`lua_dump.py`,
> `lua_extract.py`) predate the decompiler and are kept for byte-level
> inspection; the game's jump target is `pc + s + 2` (not stock `pc + 1 + s`).

## The FMV: three CRI Sofdec files

The root manifest names exactly three media files: the extension count
over all 2,080 names is **2,076 `.igb` + 3 `.sfd` + 1 `NONE`**. The movies are `aeu_opening.sfd`,
`ajp_opening.sfd` and `aus_opening.sfd`, AREA.AFS entries 0, 1 and 2 (40,091,648 B each ≈ 1:04).

They are CRI **Sofdec** — a program stream, so the `00 00 01 ba` prefix looked like MPEG-2, but ffprobe
says otherwise:

```
Duration: 00:01:04.05
Stream #0:0: Audio: adpcm_adx, 48000 Hz, 2 channels, s16p, 432 kb/s
Stream #0:1: Video: mpeg1video, 640x480, 29.97 fps
```

**MPEG-1**, not MPEG-2, and the audio is **ADX carried inside the container** — so the movies need no
reverse engineering at all: stock ffmpeg decodes both streams. (The port's `media convert` does exactly
that.)

A stage's resident sound effects are CRI `ps2_` banks inside its **sound pack** (the smaller of its pair
of AFS entries), and those decode offline — see [`sound-format.md`](sound-format.md). Music and ambience
can instead be **standalone ADX streams**: `NDMW.AFS` entries 0–78 are ADX files, each opening `80 00`
with `(c)CRI` at its header's copyright offset. The root manifest does not name them; sound metadata
reaches them by index, so `ST_CHARA`, `AM_TITLE` and `AM_START` resolve to `[0.53]`, `[0.19]` and
`[0.18]`.

## Locating an image

Every container level is decoded and cross-checked, and an image's buffers are located offline. An
`igImage` says everything needed to *decode* the image, and its references name the buffers:

```
_px 32  _py 32  _bitsIdx 8  _bytesPerRow 32  _imageSize 1024  _pfmt 0x10000
_pImage 211  _pClut 1315        <- pack-local ids, not byte offsets
```

An `igMemoryRef` such as `_pImage` is the id of its pool block, and a block's offset follows from the
pack's own directory, with no load-level replay ([`igbinary-format.md`](igbinary-format.md);
`scripts/igb_pool.py --image`). Texture packs resolve `_pClut` through their id→class table
([`texture-packs.md`](texture-packs.md)), and materials held inside a stage pack are in
[`inline-textures.md`](inline-textures.md).

**The live route reaches the same images at run time.** A scan of a loaded save finds 18,812 live
objects over 171 classes and no `igImage`/`igClut` *by class* — those classes are not among the 478
recovered vtables, which is why a vtable-keyed scan cannot see them. But the chain is reachable from
one that *is* live:

```
beTextureCtrlData._tex (+12) -> igTextureAttr._image (+48) -> igImage
    _pImage (+52)  the pixel buffer      _pClut (+68) -> igClut._pData (+20)  the palette
```

and at runtime those are ordinary **pointers**, not ordinals. Confirmed field-for-field on a live
`igImage`: `_px` 256, `_py` 128, `_pfmt` 0x00010000, `_imageSize` 32768 (= 256×128, 8 bits per index),
`_bitsIdx` 8, `_bytesPerRow` 256, `_pNameString` → `stmojipnl01.png`; its `igClut` is `_numEntries`
256, `_stride` 4, `_clutSize` 1024, so the palette is 32-bit **R,G,B,A**. Two facts the pixels settle:
row 0 is the row the GS samples at `v = 0`, so a sampler that indexes with `1 - v` flips the rows on
decode ([`inline-textures.md`](inline-textures.md)), and the source is a **plain linear
8-bit indexed image** — no swizzle — since `_bytesPerRow == _px` for all 46 reachable textures and all
share `_pfmt` 0x00010000.

Verified by eye: `stmojipnl01.png` is the status-screen label atlas (Strength/Defense/Wisdom/Spirit/
Speed/LV/Max MP/Max HP/Tech/Skill/EXP, the digits, the fire/skull/crown/star/sword/lightning/key/eye
icons), `stcngmoji.png` reads “Go to the destination.” / “Stay here.”, and the rest are gradients and
ramps. All 46 keep their real asset names
(`base01.png`, `num02.png`, `P12W00.png`, …).

## Unexplored
- `AREA.AFS` level data beyond a class census (which entries carry `igImage`, `igGeometry`, …) —
  object placement and spawn points are not parsed.
- `OUTER.DAT` (204 MB) — **completely unexplored**.
- Full igBinary parse of the reflection metadata.
