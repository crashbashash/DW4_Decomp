# CRI MWSFD frame conversion over SFX

The Sofdec player's (MWSFD, `MWSFD/PS2EE Ver.3.33s281`) front end over CRI SFX (`CRI SFX/PS2EE Ver.2.08`),
the frame-conversion library. It initialises SFX and registers its error callback, creates and destroys the
player's SFX handle, fills SFX's conversion parameters from the decoded picture's format (picture structure,
chroma format, chroma sample positions, planes), runs the conversion of a frame into the output buffer, and
passes the composition mode and the added-information (CRITAGS) block through to SFX. The messages name it
`MWSFSFX` and `mwPly`. The source is `src/cri/mwsfsfx.c`. It builds with Sony EE GCC 2.96 at `-O2 -G0` as one
whole file (`cri_mwsfsfx` in `units.tsv`, its rows in `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)).

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x297780` up to `0x298ec0` | the file opens with an init that starts SFX and registers the error callback; the functions before it are the MWSFD core's timer and stream code; the file-entry code (`mwPlyEntryFname`) starts at `0x298ec0` with its own strings |
| strings | `0x4f4028` up to `0x4f45f8` | from `MwsfdBufFmt` to the last added-information message; the previous file's last string is at `0x4f3ff8` |

The file has no data of its own. Compiling it whole matters: the conversion entry points match only with the
SFX-handle getter compiled earlier in the same file, as the call is then known not to throw.

## Types

The player (`MwsfdPly`), the frame, the conversion parameters (`MwsfdCnvPrm`, 144 bytes) and the planes
are one declaration each. The chroma format the conversion is given, and the chroma positions in the decoded
picture's information, are enums (`MwsfdChromaFmt`, `MwsfdChromaPos`): the parameter-filling function matches
only when those values are typed apart from the plain `int` fields around them, because GCC's alias analysis
then keeps their loads and stores in source order. Their constants are placeholders until the values' meanings
are known.

## Open questions

- The names of the functions and fields beyond what the messages give; the enum constants.
- Whether the added-information block at `0x298250` up to `0x2986c0` is part of this file or a file of its
  own: a function after it reads the same fields and one inside it sets SFX's user information, but nothing
  rules out a boundary.
- Three functions have no source and link from the retail image: the CRITAGS parse at `0x298468` (two words
  off: retail stores the address, the valid flag, then the size in a delay slot), and the SFX getters at
  `0x298768` (retail restores `ra` after the two output stores) and `0x298880` (retail computes a flag with
  `xori` and `movn`).
