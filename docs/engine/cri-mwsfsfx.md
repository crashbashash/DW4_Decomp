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

The player (`MwsfdPly`, 696 bytes, one of the 8 entries of the MWSFD work area) is declared once in
`include/dw4/cri/mwply.h`, which the MWSFD files share; the frame the conversion reads (`MwsfdFrm`, local to this
file) and SFX's side of it (`SfxFrame` with its three `SfxPlane`s and the `SfxPicFmt`, in `include/dw4/cri/sfx.h`) are
one declaration each. The chroma format the conversion is given (`SfxChromaFmt`), and the chroma positions in the
decoded picture's information (`MwsfdChromaPos`), are enums: the parameter-filling function matches only when those
values are typed apart from the plain `int` fields around them, because GCC's alias analysis then keeps their loads
and stores in source order. Their constants are placeholders until the values' meanings are known.

## Open questions

- The names of the functions and fields beyond what the messages give; the enum constants.
- Whether the added-information block at `0x298250` up to `0x2986c0` is part of this file or a file of its
  own: a function after it reads the same fields and one inside it sets SFX's user information, but nothing
  rules out a boundary.
- `mwsfd_GetCriTags` matches with the tag pointer and size read into `char *` and `int` locals, and
  `mwPlyGetSfxZinf` with its chunk as a local `SfdSjChunk`, which places the `ld ra` as retail does.
- Names after the SDK `mwsfdsfx.o` and the RE4 GameCube symbol table's `lib/mwsfdsfx.c` order, and the file's own
  messages: `mwPlyFxGetOutBufPitchHeight` and `MWSFSFX_SetOutBufSize` carry their own error strings and replace the
  shifted `mwPlyFxSetOutBufSize`/`mwPlyFxGetOutBufSize`; `MWSFSFX_SetPicUsrDat` and `MWSFSFX_IsFrmCcs` call
  `SFX_SetPicUsrDat` and `SFX_GetTypeCcs` as the SDK's do (and `MWSFD_IsFrmCcs` tail-calls the latter, as in the SDK),
  so the earlier `mwsfsfx_SetPicUsr` and `MWSFSFX_SetPicUsrDat` moved one slot each. Medium (alternative in brackets
  where one exists): `MWSFSFX_SetFxType`, `mwPlyFxSetOutBufPitchHeight` and `mwPlyFxSetOutBufSize` (GameCube order),
  `mwPlyFxGetOutBufSize`, `mwPlyFxSetAlp3Prm`/`mwPlyFxGetAlp3Prm` (`MWSFD_SetAlp3Prm`), `MWSFSFX_GetSudVersion`,
  `MWSFD_SetMaxAlpha` and `MWSFD_GetMaxAlpha` (both messages say `MWSFD_GetMaxAlpha`; the setter's is a copy), and
  the picture-format converters `mwsfsfx_SetPicFmtToSfx` (`mwsfsfx_SetFrmDetail`), `mwsfsfx_CnvPicStructToSfx`,
  `mwsfsfx_CnvChromaFmtToSfx` and `mwsfsfx_CnvChromaPosToSfx`, named from the fields their messages give.
- `MWSFD_SetCcirFx` and `MWSFD_GetCcirFx` (medium; alternative an `mwPlyFx` prefix) forward to `SFX_SetCcirFx` and
  `SFX_GetCcirFx`, between `MWSFD_GetProgOut` and `MWSFD_SetMaxAlpha` in the run of `MWSFD_` forwards.
- The forwards after `MWSFD_IsFrmCcs` take the names of the SFX calls they make (medium, behaviour, see the SUD notes
  in [CRI SFX and SUD](cri-sfx-sud.md)): `MWSFD_IsFrmIntl`, `MWSFD_GetFrmExtScan`, `MWSFD_GetFrmExtFlag`,
  `MWSFD_GetFrmExtVal0`..`3`; the Z-callback forward is `MWSFD_SetZTblCbFn` and the last forward before
  `mwPlyEntryFname` is `MWSFD_SetOptimizeSpeed` (to `SFX_SetOptimizeSpeed` and `CFT_SetOptimizeSpeed`). None is called.
- The converted frame is the shared `MwsfdFrm` (`include/dw4/cri/mwply.h`); `mwsfsfx_SetNfrm` takes its
  `fno_per_file`, and the player's `usrBuf.concatCnt` (reset to -1 here) is the concatenation count of the last frame.
