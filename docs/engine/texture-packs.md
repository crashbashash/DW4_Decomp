# Texture packs — the second container shape

An `NDMW.AFS` archive holds **two kinds of pack**, and a texture's bytes live in the second kind. This
page records what is known about it; the object-graph kind is
[`igbinary-format.md`](igbinary-format.md).

| kind | example entry | body |
| --- | --- | --- |
| **object / stage pack** | 621 (5 MB) | the igBinary object graph: two object sections, the id remap table, the content pool (`igbinary-format.md`), plus the `beTextureCtrlAttr` records whose `_name` is a texture's name |
| **texture pack** | 625 / 626 / 618 / 619 (≈200 KB) | a class directory, a string table, an **id→class table**, a stream of serialised `igImage`/`igClut` objects, and a flat **pool** of palettes and index buffers |

A stage therefore loads *both*: the object pack supplies the names and the scene, the texture pack the
image data. Reading only the object pack is why an earlier pass concluded the palette "was not in the
pack" (finding [#465](../findings/findings-0251-0500.md#f465), refuted by [#467](../findings/findings-0251-0500.md#f467)) — the search was in the wrong entry.

Everything below is reproducible offline; nothing needs a load replay, a RAM dump or the loader
decompiled. A live PNG dump was the ground truth that pinned it.

## The records are serialised igObjects

The stream after the header is a sequence of ordinary igBinary records, each opening with a
**`{u32 class}{u32 bytes}`** header, followed by the object's fields at the offsets
`data/reflection.json` gives for the class. Two classes matter (entry 625 numbering):

```
igImage   class 10, 104|108 bytes   igClut  class 11, 28 bytes
```

| igImage | off | | igClut | off |
| --- | --- | --- | --- | --- |
| `_px` `_py` `_pz` `_ps` | +8 +12 +16 +20 | | `_fmt` | +8 |
| `_order` | +24 | | `_numEntries` | +12 |
| `_bitsRed/Grn/Blu/Alpha` | +28…+40 | | `_stride` | +16 |
| `_pfmt` | +44 (= `0x10000`) | | `_pData` | **+20** |
| `_imageSize` | +48 (= `W*H`) | | `_clutSize` | +24 |
| `_pImage` | **+52** | | | |
| `_pName` | +56 (`-1`) | | | |
| `_localImage` `_bitsInt` `_pClut` | +60 +64 **+68** | | | |
| `_bitsIdx` `_bytesPerRow` | +72 +76 | | | |
| `_compressed` `_bitsDepth` | +80 +84 | | | |
| `_pNameString` | +88 (`{u32 len}{bytes}`) | | | |

So an igImage record carries its own **name**, **size** (`_px`/`_py`, `_bytesPerRow` repeats the
width), its **grid block id** (`_pImage`) and its **palette reference** (`_pClut`). The run earlier
work read as a separate "descriptor entry" — `[1, 0, C, bitsIdx, DIM, 0, 0, namelen, name]` — is
just this record's own tail (`_localImage`, `_bitsInt`, `_pClut`, `_bitsIdx`, `_bytesPerRow`, …,
`_pNameString`), which is why the record looked 60 bytes long (finding [#476](../findings/findings-0251-0500.md#f476) supersedes [#469](../findings/findings-0251-0500.md#f469)/#470).

An igClut's `_pData` is the id of its palette block. Palette entries are `A R G B` with a **varying**
alpha — many textures have a transparent or partly-transparent entry 0 — so a palette block must not
be recognised by testing bytes for `0xFF`; only its RGB (bytes 1..3) is reliable, and then only at
its own offset.

## The id→class table and the texture→palette link — solved (finding [#476](../findings/findings-0251-0500.md#f476))

`_pClut` is **an id in the pack's own id space, not a block id**. That space is declared by the same
`{u32 tableBytes}{u32 idCount}` + `idCount × u16` shape the object packs use for their id remap table
(`igbinary-format.md`, finding [#460](../findings/findings-0251-0500.md#f460)) — but here each entry is the **class of that id**:

* entry 625: `+0x1099`, `tableBytes 388`, `idCount 190`. The space interleaves the pack's objects
  and their memory blocks, so it is longer than the record stream.
* the class numbering is **pack-local**: 625 has clut block `0` / igClut object `8`, 626 has `4`/`1`,
  619 `0`/`18`, 632 `1`/`16`.
* the table validates itself: one class's id set is exactly the clut blocks' ids and another's
  exactly the igImages' `_pClut` values, and the two counts must agree (26 = 26 for 625).

The ids of a class appear in the loader's **creation order, which is file order**, so the rank of an
id within its class is that object's position in the stream. Hence:

```
palette_block = igClut_records_in_file_order[ rank( _pClut among the ids of its class ) ]._pData
```

and the texture→palette link needs nothing else. (The rank is monotone in the clut record index —
0→3, 1→20, … 25→188 on entry 625 — which is the signature of an id rather than an offset.)

The name→grid half is then just the record's own `_pImage`, and both halves are checked: all **26**
textures of entry 625 decode **pixel-for-pixel** against the live dump through

```
pool offset → grid block (+1) → palette block → RGB
```

`scripts/igb_texpack.py --textures` prints name/size/image id/palette id; `--decode NAME --out F`
writes one texture as raw RGBA.

## The pool order (finding [#472](../findings/findings-0251-0500.md#f472))

The pool is the records' data blocks laid out in **ascending id order**: a clut contributes `N*4`
bytes (1024 for a 256-entry palette), an image `W*H`:

```
offset(id) = pool_base + sum(sizes of blocks with a smaller id)
```

An **image block has a one-byte prefix**, so its grid data begins at `block + 1`; a palette has none,
so its entries begin at the block. The pack header states the pool's own geometry (finding [#473](../findings/findings-0251-0500.md#f473)):

```
hdr[6] == sum(block sizes) + 4*(nclut + 2)      hdr[7] == nclut + nimg + 3
table_start = EOF - 1 - hdr[6]                   pool_base = table_start + 4*nclut
pad_total   = hdr[6] - 4*nclut - sum == 8        (four-byte slots)
```

Both identities hold with no exception on all **44** texture data packs of `NDMW.AFS`, and for
entry 625 they give `pool_base = 0x2c08`, the value the live ground truth pins independently. A pad
is a four-byte slot, so it can only sit in a gap of the id sequence; its position is chosen to line
up the most palettes (reproducing 625 exactly) but is not yet pinned on every pack, while the base
and the pad total are exact.

A pad **reuses the id of the block it follows**, so a table of layout rows must skip pad rows or it
silently picks the four-byte pad instead of the block. And because an image's data is one byte longer
than its block, its last byte lands on the next block's first byte — which is why a palette's
entry-0 **alpha** byte is unreliable (it is the preceding image's last grid byte) even though its RGB
is the palette's own index-0 colour.

The rule reproduces entry 625 exactly: 52 blocks tile `0x2c08 … 0x30910` (file size `0x30911`, one
trailing byte). The verified layout is `texture-pack-625-layout.tsv`, the verified pairing is
`texture-pack-625-textures.tsv`, and `../scripts/verify_texpack_layout.py` re-diffs both.

Pack coverage today: the class table validates and pairs on entries **625, 626, 618, 619, 632, 639**;
646, 676, 713 and 720 do not (multi-asset packs). Pixel-exactness against live data is checked on
625, whose textures are the ones that were dumped.

## Findings

`#466` (names are `beTextureCtrlAttr._name`), `#467` (texture packs; buffers located), `#468` (pool
analysis + ground truth), `#472` (the pool order), `#473` (the base and pads out of the header),
`#474` (the name→image link), **`#476` (the record shape and the texture→palette link — supersedes
[#469](../findings/findings-0251-0500.md#f469)/#470)**. `#465` is refuted; `#471` holds the dynamic ground truth that pinned the exact offsets.
