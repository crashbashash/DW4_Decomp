# CRI SFX and SUD

The last CRI files of the Sofdec block, each compiled as one whole file with Sony EE GCC 2.96 at `-O2 -G0`
(their rows in `units.tsv` and `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/sfx.c` | `cri_sfx` | `0x2b3788` up to `0x2b4210` | SFX (`CRI SFX/PS2EE Ver.2.08`), the frame-conversion library's handles and conversion entry points | its messages start with the version string at `0x4f57b8`; its library object at `0x4bec28` (1000 bytes) ends where the Z file's data begins |
| `src/cri/sfxz.c` | `cri_sfxz` | `0x2b4210` up to `0x2b50e8` | SFX's Z-buffer conversion | it repeats `SFXINFE` (GCC shares identical strings only within a file); its messages run to `sfxcnv_CnvZbitToCft`; its object at `0x4bf010` |
| `src/cri/sud.c` | `cri_sud` | `0x2b50e8` up to `0x2b5d50` | SUD (`CRI SUD/PS2EE Ver.0.05`): user-data headers and the EE timer | its init returns the version string at `0x4f59c0`; its messages and tables follow SFX's; its data at `0x4bf280` |

SUD's timer words and the timer-register tables are declared `volatile`
([source approvals](source-approvals.md#sud-timer)); the timer tick is approved, the timer init and read are
`unapproved`. SFX's and SUD's inits store their version strings in `volatile` words
([build-string stores](source-approvals.md#build-string-stores)), and the SFX handles' in-use word is read and cleared
through a `volatile` pointer ([sfx-handle-used-flag](source-approvals.md#sfx-handle-used-flag)); all are approved.
The two SFX files share `include/dw4/cri/sfx.h`. A plane's address (`SfxPlane.addr`) is declared `int` and
cast at use, as the owner approved for the cvFs, HTCI and DVCI pointers on the same condition
([CRI cvFs](cri-cvfs.md#integer-typed-slots)).
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
- Still unnamed: the Z handle's callback and callback-argument setters, the line-and-pixel plane shift after
  `sfx_ClipFrame`, the forward to the CFT word at `0x4bb3ec`, the seven SFX forwards after `SFX_GetTypeCcs` and the SUD
  analysers they call (the 2004 user-data fields from offset 20 on), the Z-table forward after `sfxzmv_GetZfrmInf`, the
  three `float` timer conversions after `UTY_TmrToSec`, the one-word timer-unit store before `UTY_InitTsum` (whether it
  or the wrapper before `UTY_GetTmrUnit` is the SDK's `UTY_SetTmrUnit`; the order picks the wrapper), and the PS2 timer
  accumulation words `UTY_InitTmr` sets up after `utytmr_save_mode`, which have no RE4 counterpart.
