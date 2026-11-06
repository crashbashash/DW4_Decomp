# PS2 save-file codec

`src/saveimage.c` translates between one retail **BASLUS-20836savedata** file (81,920 bytes) and the
players' GAMERAM records. It is the import/export layer for the agreed "individual exported PS2 save file"
(technical spec, *Agreed save requirements*); the native PC save library format is still undecided and is
not defined here. The retail evidence is the record serializer `3ee6d0` (records → deliver struct), the loader
`3ef5d0` (struct → records), the id converter `3ef1e0` and the five `beNDMWItem*` `vfunc_23/24` pairs.

## File layout

| Piece | Evidence |
| --- | --- |
| Two **mirrored** blocks of `0xA000` bytes; block word 0 is the checksum, word 1 the version (4) | the second block is byte-identical to the first in every retail file |
| Checksum = sum (mod 2³²) of the u32 words from block+4 to block+`0xA000` | verified on all six samples below |
| Four **character records**, one per player slot, `0x2000` bytes apart from file offset 8 | retail resaves carry records at `0x8`, `0x2008`, `0x4008`, `0x6008`; `SaveCtrl` (`407120`) loops four slots |
| Record = the "deliver struct", offsets below, relative to the record base | serializer `3ee6d0` and loader `3ef5d0`, decompiled with `tools/m2c_one.py` |

Deliver-struct offsets (add `8 + 0x2000 × slot` for the file offset):

| Offset | Key | Shape |
| --- | --- | --- |
| `0x00` / `0x04` | `ISUSE` / `UNIQUE` | byte / i32 |
| `0x08` | `DIGIMONNAME` | NUL-terminated string, 32 bytes |
| `0x28`, `0x2A` | `PLAYERNAME` | marker `0xFFFF`, then up to eight u16 codes |
| `0x48..0x58` | `LEVEL`, `HP`, `MHP`, `MP`, `MMP` | i32 |
| `0x5C`, `0x60` | `XDATA`, `BIT` | i32 |
| `0x64`, `0xF4` | `DEVICEFOLDER` (36), `DISKFOLDER` (12) | item ids, empty `0xFFFFFFFF` |
| `0x124` | `CARDLIST` | 50 bytes |
| `0x158`, `0x2D8` | `BANKDEVICE` (96), `BANKBIT` | item ids, i32 |
| `0x2DC`, `0x2E8`, `0x2FC`, `0x300`, `0x314` | `POWERSOCKET` (3), `POWERPOCKET` (5), `MAINSLOT` (1), `MAINPOCKET` (5), `SUBSLOT` (1) | index into `DEVICEFOLDER`, or −1 |
| `0x318`, `0x718` | `BASE_FLAG` (1,024 bytes), `BASE_FLAGFOLDER` (12 bytes) | bytes |
| `0x724`, `0x764` | `BASE_COUNTER` (16 × i32), `BASE_ISUSE` (16 bytes) | |
| `0x774`, `0x7B4`, `0x7F4`, `0xA34` | `BASE_LEVEL` (16), `BASE_EXP` (16), `BASE_SKILL` (144), `BASE_UPCNT` (176) | i32 |

The equipment lists store the *position* of the equipped object inside `DEVICEFOLDER` (retail compares object
identity); the port keeps the same value in its host-only `*REF` arrays and re-projects the lists on load.
The loader skips empty ids, so folders are stored compacted.

## Item ids

`kind = id >> 12 & 0xF` selects the class. All classes share record (bits 0-9) and equipped (bit 10); the rest:

| Kind | Class | Extra fields |
| --- | --- | --- |
| 0, 1 | weapon, blue armor | pocket bits 16-19, revision bits 20-30 |
| 2 | yellow armor | revision bits 20-30 |
| 3 | ability chip | none |
| 4 | disk | revision (quantity) bits 16-19 |

A kind nibble above 4 (including `0xFFFFFFFF`) is an empty entry; `3ef1e0` stores NULL for it.
`dw4_saveimage_item_encode` refuses a field that does not fit instead of truncating it.

## Behaviour

- `dw4_saveimage_verify`: size, version 4, both checksums and the mirror.
- `dw4_saveimage_store(players, player, slot, image)`: rewrites the slot in both blocks of a valid image
  (use `dw4_saveimage_init` for an empty one), refreshing the checksums; the other slots are untouched and the
  image is unchanged on failure.
- `dw4_saveimage_load(players, player, slot, image, size)`: verifies the image, decodes every key into a private
  copy of the player and commits only when all of it decodes. The loader allocates the name object with eight
  codes and zero-pads it, as retail does.
- `dw4_savefile_write` replaces the destination atomically (temporary file in the same directory, flush,
  re-read, verify, rename); a failed write leaves the previous valid file and no partial file behind.
  `dw4_savefile_read` returns only a verified image.

Not stored in a save, so the caller rebuilds them after a load: species (`DIGIMONNO`), the
current stats from `BASE_*`, the equipped weapon model (`POWERSOCKETNAME`) and every recalculated stat.

## Verification (headless)

`make -C port check-saveimage` (`tools/test_saveimage.c`):

- every item class at its field limits, bit placement, and refusal of unrepresentable fields;
- verification failures: wrong size, flipped bit in either block, wrong version, a self-consistent block that
  does not mirror the other;
- a synthesized character with every region populated stores, loads into another character and stores back
  byte-identically; a corrupt image or a bad slot changes nothing; atomic file write/read, a refused write
  keeping the old file, and refusal of a 37-item folder;
- **six retail-written files** are loaded into player records and stored back **byte-identical** (a fresh
  save, two level-up saves, a level-999 save, a two-character and a four-character resave). The files are
  private and outside Git; the test skips explicitly when `$DW4_SAVE_SAMPLES` (default `../../local`) has none.

## Boundaries

- A record whose name marker is not `0xFFFF` stores a narrow name for the US converter `382eb0`
  (table `4c8880`); it is refused with an error rather than guessed.
- The unused region after `BASE_UPCNT` and the `0x8008..0xA000` tail are written as zero, which matches every
  retail sample; their meaning, if any, is not recovered.
- No PS2 memory-card container (`ps2mc`, icon, `icon.sys`) and no `.psu`/`.max` export is implemented; the
  codec handles the raw save file only. The native PC library and the exact import/export workflow remain
  open decisions in the specification.

## Host memory card

`dw4_memcard_*` (`src/memcard.c`, `include/dw4/memcard.h`) wraps this codec in a directory-backed card: scan which of the
four slots hold a character, save several players into one file, load a slot, and refuse (never overwrite) a damaged file.
See [Save Keeper](save-keeper.md#host-memory-card-and-the-savectrl-rules).
