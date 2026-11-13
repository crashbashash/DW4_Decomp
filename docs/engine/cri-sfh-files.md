# CRI SFD output handlers, SFH and SFX alpha

Four whole files between the SFD time-stamp file (`src/cri/sfdtst.c`) and the SFX conversion code, each compiled
with Sony EE GCC 2.96 at `-O2 -G0` (their rows in `units.tsv` and `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)). The file names and the function names outside SFH and the
SFX alpha code are best guesses from behaviour. SFH's version string names its library, and the SFH and
SFX alpha functions carry CRI's own names, taken from the GameCube builds of the same library versions
(Resident Evil 4, Shadow the Hedgehog) and the Persona 3 FES PlayStation 2 symbol list.

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/sfdainf.c` | `cri_sfdainf` | `0x2b0ed0` up to `0x2b1410` | the additional-information channel: the handler of stream graph slot 8, which passes the slot's buffer channel to up to three user outputs (`SFD_SetAinfMem`, `SFD_SetAinfSj`) | errors `0xFF0006xx` only in this run; its 14-entry handler table at `0x4f5278` lists the functions in code order from `sfainf_InitFn` to `sfainf_TermFn`; the setters reset the list the table's create entry builds |
| `src/cri/sfdout.c` | `cri_sfdout` | `0x2b1410` up to `0x2b16e0` | the output handler of stream graph slot 6: the application reads the slot's buffer channel through its GetRead and AddRead entries, gated by the time block | errors `0xFF0007xx`; its handler table at `0x4f52b0` follows the first and lists `sfout_InitFn` up to `sfout_TermFn` in code order |
| `src/cri/sfh.c` | `cri_sfh` | `0x2b16e0` up to `0x2b2ee8` | SFH (`CRI SFH/PS2EE Ver.1.19`): the header sector of a Sofdec stream: handle pool, magic and version checks, file information and the per-stream audio and video descriptors | its read-only data `0x4f52f0` up to `0x4f53b0` (the `SFH Version` and copyright strings, the build string `SFH_GetVersionStr` returns, `SofdecStream`, `Ver.` and the jump table of `sfh_FrmRateCodeToRate`) follows the second handler table; its bss is `0x585688` up to `0x5856a0` |
| `src/cri/sfxa.c` | `cri_sfxa` | `0x2b2ee8` up to `0x2b31d8` | SFX alpha: the alpha handles an SFX handle keeps (`SfxHn.ahn`): the parameters of the CFT colour table and the three alpha levels of the CFT alpha tables, then three frame helpers | its data `sfxa_lib` (`0x4beb58`, 200 bytes) sits between the time-stamp file's data and SFX's library object at `0x4bec28`; `sfxa_Init` and `sfxa_Finish` are called from SFX's init and finish; the SFX conversion code at `0x2b31d8` starts with the next read-only data (`sfxcnv_` messages) |

Each file declares its own types. The two handlers see the stream graph entry (`0x44` bytes at handle +7976) only
as far as they use it; `SfainfTrn.list` is the word the graph code keeps as `f8`. SFH's handle (`SfhHn`, 16 bytes)
points at the header in memory (`SfhHdr`); a stream descriptor (`SfhStm`, 64 bytes, 26 of them at +384) is read
as `SfhAudioStm` or `SfhVideoStm` by its MPEG stream id (`chkStmId`). The audio descriptor's bytes at `0x1A` and `0x1B` are the MPEG audio layer (`SfhAudioStm.layer`, read by
`SFH_AnlyElemLayer`) and the channel count (`SfhAudioStm.chNum`, `SFH_AnlyElemChNum`), followed by the sampling rate
(`smpHz`); the other descriptor field names are guesses from what the getters return. `SFXA_Destroy` writes the in-use word through a `volatile` pointer and is
`unapproved`.

`SFH_Create` reads the pool's three words (capacity, count, table) into locals of their own before its full-pool
test. That decides more than the loads: the pool's address then sits in `a0`, the table load fills the delay slot of
the full-pool branch, and from there the delay-slot filler counts `a0` as live at the search loop's head, so the
loop's closing branch takes the loop test into its slot rather than the argument move that follows it
([delay slots](understanding-shapes.md#delay-slots-ee-gcc)). With the count tested straight from the pool the
address sits in `v1` and the loop comes out with the move in the slot and a pad before the loop head.

## Open questions

- `sfxalp_SearchFreeHn` (`0x2b2fa0`) matches with a `volatile`-qualified read of the in-use word. Retail leaves
  the loop branch's delay slot empty where the compiler fills it, and plain C cannot change that fill under this
  compiler, so the function is `unapproved`, like SFX's own free-handle search
  ([CRI SFX and SUD](cri-sfx-sud.md#open-questions)).
- The handler tables at `0x4f5278` and `0x4f52b0` are not defined in C; nothing in the code references them, only
  the module lists in MWSFD's data.
- What the stream graph slots 6 and 8 carry: the file names `sfdout` and `sfdainf` rest on behaviour and on the
  MWSFD caller that sets the additional-information stream join through `SFD_SetAinfSj`.
- `SFX_SetClipping`, `SFX_SetBottomUpDstBuf` and `SFX_SetBottomUpPlnBuf` are called from nowhere in the image.
- Medium confidence: the SFH getters of the file, element and header fields outside the `SFH_AnlyNumElem*` and `SFH_AnlyFtr*`
  names (the other `SFH_Anly*` getters, `SFH_IsSfdHeader`, `SFH_IsExistStmId`, `SFH_IsEffFtrInf`, `SFH_AnlyMaxPicSiz` and
  `SFH_AnlyAvrPicSiz` with the two version-2.25 header words), the SFH static helpers (`clearObjInf`, `initObjInf`,
  `initSfhObj`, `setHnCreate`, `initLibWork`, `isFreeObj`, `isEffectiveVer`, `isEffectiveObj`, `searchStmId`, `getToolVer`,
  `convAsciiToDigit`, `getElemInfPtr`, `isEnableAudFtr`, `isEnableVidFtr`, `chkStmId`) and the SFX alpha names `SFXA_SetLumiPrm`,
  `SFXA_GetLumiPrm`, `SFXA_SetAlp3Prm`, `SFXA_GetAlp3Prm`, `sfxalp_SearchFreeHn`, `sfxalp_InitHn`, `SFX_SetClipping`,
  `SFX_SetBottomUpDstBuf` and `SFX_SetBottomUpPlnBuf` (`SFXA_Create`, `SFXA_Destroy`, `SFXA_MakeAlpLumiTbl`,
  `SFXA_MakeAlp3110Tbl`, `SFXA_MakeAlp3211Tbl` and `SFXA_IsNeedUpdateLumiTbl` come from the GameCube library's own symbols and are
  high). Source: the Persona 3 FES PlayStation 2 symbol list (its provenance is not stated), whose order and
  sizes match this library one for one, with Persona 4's proven names where it has them and the Shadow the Hedgehog `sfh_main.c`
  for the offsets and tests. The two bottom-up helpers have identical bodies, so the Dst/Pln split rests on that list's order
  alone; the GameCube library keeps them in `sfx_cnv.c`, not in the SFX alpha file.
- `SFH_GetVersionStr` and `sfh_IsStatAnalysed` keep their names: the Persona 3 list has `SFH_CheckStructSiz` and an unnamed
  function in those slots (low confidence).
