# CRI SFX and SUD

The last CRI files of the Sofdec block, each compiled as one whole file with Sony EE GCC 2.96 at `-O2 -G0`
(their rows in `units.tsv` and `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/sfxcnv.c` | `cri_sfxcnv` | `0x2b31d8` up to `0x2b3788` | SFX conversion: the check that a conversion table must be rebuilt, the table makers per composition kind and the stream-information lookup | it starts with the `sfxcnv_` messages that follow SFX alpha's data; the SFX file (`0x2b3788`) opens with its own version string |
| `src/cri/sfx.c` | `cri_sfx` | `0x2b3788` up to `0x2b4210` | SFX (`CRI SFX/PS2EE Ver.2.08`), the frame-conversion library's handles and conversion entry points | its messages start with the version string at `0x4f57b8`; its library object at `0x4bec28` (1000 bytes) ends where the Z file's data begins |
| `src/cri/sfxz.c` | `cri_sfxz` | `0x2b4210` up to `0x2b50e8` | SFX's Z-buffer conversion | it repeats `SFXINFE` (GCC shares identical strings only within a file); its messages run to `sfxcnv_CnvZbitToCft`; its object at `0x4bf010` |
| `src/cri/sud.c` | `cri_sud` | `0x2b50e8` up to `0x2b5d50` | SUD (`CRI SUD/PS2EE Ver.0.05`): user-data headers and the EE timer | its init returns the version string at `0x4f59c0`; its messages and tables follow SFX's; its data at `0x4bf280` |

SUD's timer words and the timer-register tables are declared `volatile`, and the timer init, read and finish are
approved ([source approvals](source-approvals.md#sud-timer)). SFX's and SUD's inits store their version strings in
`volatile` words ([build-string stores](source-approvals.md#build-string-stores)), and the SFX handles' in-use word is
read and cleared through a `volatile` pointer ([sfx-handle-used-flag](source-approvals.md#sfx-handle-used-flag)); all
are approved. The SFX files share `include/dw4/cri/sfx.h`. A plane's address (`SfxPlane.addr`) is declared `int` and
cast at use; the owner approved that on the condition that the typing describes the types rather than one call site
([the same condition as HTCI](cri-htci.md#integer-typed-list-pointer)).
`SFX_DecideTableAlph3` (the conversion file's alpha-3 table choice) is named from the RE4 GameCube symbol table
([adonis-singh/re4](https://github.com/adonis-singh/re4), `config/G4BE08/sym_map.tsv`, unit `lib/sfx_cnv.c`).
The setters, the user-data forwards and the Z, alpha and colour-adjust table makers follow the SDK's `sfx_set.o`,
`sfx_sud.o`, `sfx_cnv.o` and `sfx_zmv.o` order and the RE4 GameCube symbol table's `lib/sfx_set.c`, `sfx_sud.c`,
`sfx_cnv.c`, `sfx_zmv.c`, `sud_lib.c` and `uty_tmr.c`; `SFX_SetAlp3Prm`, `SFX_SetMaxAlpha`, `SFXZ_GetZfrmRange` and
`SFXCNV_MakeCcirFromY` are names the [Persona 4 decompilation](https://github.com/Raikaru/Persona4-Decompilation)
proves masked-exact against Devil Kings and Onimusha builds (`docs/cri/proven_names.json`), taken at the aligned slot.
The callers fix the setter run: each `MWSFD_*`/`MWSFSFX_*` forward calls the SFX setter of its own name, which moved
`SFX_SetColAdj`, `SFX_SetSplitField`, `SFX_SetProgOut` (and their getters), `SFX_SetALumiPrm`, `SFX_GetALumiPrm` and
`SFX_SetOutBufSize` one slot each from where the first pass had put them; the 2004 additions at the end of the run
are `SFX_SetCnvBottomUp`/`SFX_GetCnvBottomUp` (the SFX side of `mwPlySetCnvBottomUp`) and `SFX_SetFxType`/
`SFX_GetFxType`/`SFX_SetUnitWidth` (GameCube order).

## Open questions

- Whether the function at `0x2b3780` (returns 17) starts the SFX file or ends the conversion file before it.
- Medium confidence (alternative in brackets where one exists): `SFX_GetFxType`, `SFX_SetUnitWidth`, `SFX_GetAlp3Prm`,
  `SFX_SetCnvBottomUp`/`SFX_GetCnvBottomUp` (`SFX_SetBottomUp`), `SFX_SetMaxAlpha`, `SFX_GetMaxAlpha`,
  `SFX_IsEnablePicUsr`, `SFX_GetSudVersion` (`SFX_GetTypeVersion`), `SFX_SetALumiPrm`, `SFX_GetALumiPrm`, the split-field
  and progressive-output pairs, `SFX_SetZbit`/`SFX_GetZbit` (`SFXZ_SetZbit`), `SFX_MakeTable`, `sfxcnv_IsNeedUpdateTbl`,
  `sfxcnv_MakeZTbl` (the SDK's Z16/Z32 makers merged), `sfxcnv_MakeCcirTbl`, `sfxcnv_MakeAlp3110Tbl`, `SFXCNV_MakeCcirFromY`,
  `sfxzmv_InitHn`, `SFXZ_MakeCnvZTbl` (was `SFXZ_MakeCnvZ32Tbl`; it serves both depths), `sfxzmv_MakeCnvZTbl`,
  `sfxzmv_MakeZ32TblFromOrgZ32`, `SUD_AnalyVersion` (`SUD_GetVersion`), `SUD_SearchSudDat` (was `SUD_FindTag`),
  `UTY_FinishTmr`, `UTY_IsTmrVoid` and `UTY_SetTmrUnit`; also, where the SDK body (B or C) or the SDK order and the
  RE4 GameCube order agree, `SFX_SetFxType`, `SFX_SetOutBufSize`, `SFX_SetColAdj`/`SFX_GetColAdj`, `SFX_SetPicUsrDat`,
  `SFX_GetTypeDivField`, `SFX_GetTypeCcs`, `SFX_SetAlp3Prm`, `SFXZ_GetZfrmRange`, `SFX_CnvFrmZ16`/`Z24`/`Z32`,
  `SUD_SetFmtTypeToBuf`, `UTY_InitTmr`, `UTY_GetTmr` and the four `sfxcnv_Make*Tbl` forwards with an SDK B body.
- `SFX_GetCcirFx` (medium) is the RE4 GameCube symbol table's `lib/sfx_lib.c` function of that name, whose body in the
  RE4 sources returns the library work's `ccir_fx` word; DW4 reads the same word, at the same offset 20, and
  `SFX_SetCcirFx` (medium) is its setter, which `sfx_InitLibWork` calls with 1 where the RE4 `SFX_Init` stores 1 itself.
  `SFX_SetForceSplit`/`SFX_GetForceSplit` (medium; alternative an `sfxcnv_` prefix) store and return `sfxcnv_forcesplit`.
- Data, medium, from the SDK `sfx_lib.o` and the RE4 sources: `sfx_init_cnt`, `sfxcnv_forcesplit` and `sfx_libwork`;
  from the RE4 `uty_tmr.c` with the same use: `utytmr_init_cnt` and `utytmr_ch`. From use: `utytmr_save_mode` (the
  timer mode word `UTY_InitTmr` saves and `UTY_FinishTmr` restores), `sfx_version_ptr` and `sud_version_ptr` (the
  build-string pointers, as `mpv_version_ptr`).
- The SDK `uty_tmr.o` names the PS2 timer words by order and size: `utytmr_main` and `utytmr_sub` (the 16-byte clock
  and its saved copy), `utytmr_ptr` and `utytmr_lock`, and the register tables `utytmr_t_mode`/`utytmr_t_count`
  (high). The SDK and RE4 call the build-string pointers `sfx_dummy`/`sud_dummy`; the `*_version_ptr` names stay
  for now, as for MPV and MPS.
- Behaviour names, medium (alternative in brackets): `SFX_SetZTblCbFn`/`SFX_SetZTblCbArg` (`SFX_SetZCbFn`), the Z
  handle's table callback that `sfxzmv_MakeCnvZTbl` calls in place of its Z16/Z32 makers; `sfx_ClipBufInf`
  (`sfxset_ClipBufInf`), the per-plane step of `sfx_ClipFrame` as `sfxset_ShiftBufInfByLine` is of
  `SFX_ShiftYccPtrByLine`; `SFX_SetOptimizeSpeed`, the forward to `CFT_SetOptimizeSpeed`; `UTY_TmrToUsecF`,
  `UTY_TmrToMsecF`, `UTY_TmrToSecF` (`...Float`), the `float` forms of the SDK conversions; `utytmr_SetUnit`, the
  one-word store both `UTY_InitTmr` and `UTY_SetTmrUnit` call (alternative: it is the SDK's `UTY_SetTmrUnit`).
- The 2004 SUD record: `SUD_SetFmtTypeToBuf` writes the letters at bytes 18-20 from its A/D, N/C and P/I tables, so
  `SUD_AnalyTypeIntl` (`SUD_AnalyTypeScan`) reads the third ('I'). The version-2 fields after it have no source and
  are named by what is read, not what they mean: `SUD_AnalyExtScan` (byte 21, 'P' 1, 'I' 2),
  `SUD_AnalyExtFlag` (byte 22 is not 'A') and `SUD_AnalyExtVal0`..`3` (three hexadecimal digits each at 23, 26, 29
  and 32, ending the 0x23-byte record), through `sud_AnalyHex3`, `sud_StrToUl` (a `strtoul` wrapper) and, for the
  record size, `sud_GetSudDatSize` (the RE4 CRI library's `SUD_SearchSudDat` stores the same 0x23). The SFX forwards
  take the matching `SFX_GetTypeIntl`/`SFX_GetExt*` names. What the four values and the two letters stand for is open.
- The handle's fields follow its setters and the RE4 CRI library's `SFX_OBJ` (in its 9.31 order, with the word at 36):
  `fxtype`, `unitWidth`, `zscale` (default 1), `zoffset`, `colAdj`, `tblPtn`, `splitField` (default -1), `progOut`,
  `cnvBottomUp`; the library work's word at 20 is `ccirFx` (RE4 `ccir_fx`). A frame's tag block is `tagData`/`tagSize`
  (RE4 `tag_a`/`tag_b`), and its picture format carries `progressiveFrame`, `topFieldFirst` and `repeatFirstField`
  from the MWSFD picture information.
  The RE4 CRI library cited here is the RE4 decompilation in the
  [Persona 4 decompilation](https://github.com/Raikaru/Persona4-Decompilation) (`src/cri/re4/sfx.h`, `sfx_lib.c`,
  `sfx_sud.c`, `sud_lib.c`); the SDK objects are `libmwsfde.a` of
  [recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri).
- Still unnamed: the Z-table forward after `sfxzmv_GetZfrmInf` (in `sfxz.c`).
- Without source: `sfxzmv_GetZfrmInf` (`0x2b45b0`, 4 words off: retail fills the first branch's delay slot from the
  branch target and schedules the copy of the size parameter before the return-address save) and
  `sfxcnv_CnvFrmArgb8888mbToZ` (`0x2b4f58`, 18 words off: the height load and a constant store into the source block
  are scheduled later than in the SDK body it follows; the other conversion, `sfxcnv_CnvFrmYcc420plnToZ`, matches).
