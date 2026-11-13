# CRI MWSFD core, frame side and player control

Four files of the Sofdec player library (MWSFD, `MWSFD/PS2EE Ver.3.33s281`), the layer between the
game and CRI SFD. Each builds with Sony EE GCC 2.96 at `-O2 -G0 -ffunction-sections` as one whole file
(`cri_mwsffrm`, `cri_mwsfd`, `cri_mwsfply`, `cri_mwsfrna` in `units.tsv`, their rows in
`unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)). CRI's own file names
are `mwsfdfrm.c`, `mwsfdlib.c`, `mwsfdply.c` and `mwsfdrna.c`; the library's objects sit in the image
in the alphabetical order of those names.

- `src/cri/mwsffrm.c`: the frame side. Frame sync (`mwPlySetFrmSync`, `mwPlyGetFrmSync`), the frame
  handed out by `mwPlyGetCurFrm` and its release (`mwPlyRelCurFrm`), the picture-type and plane-layout
  conversions between SFD and MWSFD (`mwl_convPtypeFromSFD`, `mwl_convPtypeToSFD`, `mwply_CopyPlanes`),
  the frame type decision (`mwsffrm_DecideFrmType`), the picture user data (`mwply_UpdatePicUsrData`,
  `mwPlyGetPicUsrData`, `mwPlyGetNextPicUsr`), and the per-picture log ring: SFD calls `mwply_LogPic`
  for each picture's user data (installed by `mwply_SetPicUsrCb`); when the data parses as an SFD
  header with a video stream, the picture's item-type-3 flag, time unit and composition mode go into
  slot `logWrite % 8`, and the `mwply_GetCurPic*` readers take slot `logPos % 8`.
- `src/cri/mwsfd.c`: the core. `MWSFD_GetVersionStr`, the work area (`MWSFLIB_GetLibWorkPtr`,
  `mwsflib_InitLibWork` and the settings getters and setters), the last error code (`MWSFLIB_SetErrCode`), the
  SFD library init and finish (`mwPlySfdInit` checks for SFD version `1.946`; `mwPlyFinishSfdFx` drops the
  init count and, at zero, destroys every player in use and finishes the libraries in order), and the
  SFD time hooks.
- `src/cri/mwsfply.c`: the player's control. `mwPlySfdStandby`/`mwPlySfdStart`, `mw_sfd_start_ex`
  (resets the SFD handle and the added-information SJ, re-applies the pause switch and starts the SST
  input), the starts from a file (`mwPlyStartFname`), a file range (`mwPlyStartFnameRange`), an AFS
  entry (`mwPlyStartAfs`), memory (`mwSfdStartMem`, an SJ made over the buffer) and a caller's SJ
  (`mwSfdStartSj`), the stop (`mwSfdStop`, `mwSfdStopDec`) and the pause (`mwSfdPause`).
- `src/cri/mwsfrna.c`: the audio output. The four wrappers that pass the output volume and pan to SFD
  (`MWSFRNA_SetOutVol`, `MWSFRNA_GetOutVol`, `MWSFRNA_SetOutPan`, `MWSFRNA_GetOutPan`).

## Extents

| file | code | strings / data | evidence |
| --- | --- | --- | --- |
| mwsffrm.c | `0x293730` up to `0x294a20` | `0x4f30a0` up to `0x4f3310`, the switch table at `0x4f32b0` | the first function is the first user of `mwPlySetFrmSync`'s message after the creation file's last (`MWSFD_Malloc`, `0x4f3070`); the messages name `mwsffrm` and `mwl_convPtype*`; the next datum is the version string |
| mwsfd.c | `0x294a20` up to `0x295358` | `mwsfd_version` `0x4f3310` up to `0x4f3688`; the work area `0x4bd250`/`0x4bd258` and the two handles of the last SFD error behind it (`mwsfd_err_mwsfdhn` `0x4be884`, `mwsfd_err_sfdhn` `0x4be888`, both stored by the error callback) | opens with the version getter and the version string, as CRI files do; see the cut below |
| mwsfply.c | `0x295358` up to `0x295df8` | `0x4f3688` up to `0x4f39b8` | starts at `mwPlySfdStandby`; see the cut below |
| mwsfrna.c | `0x295df8` up to `0x295e58` | none | the GameCube library of the same version (MWSFD/GC Ver.3.33) keeps exactly these four functions in an object of their own, `mwsfdrna.o`, linked apart from `mwsfdply.o`; here they sit between the player control and the scratchpad file (`MWSFD_InitRsc`, `0x295e58`), where `mwsfdrna` falls alphabetically |

### The cut between mwsfd.c and mwsfply.c

The cut is one of three addresses, `0x2952d0`, `0x295320` or `0x295358`, and the image cannot say
which; it is placed at `0x295358`.

- Not before `0x294f28`, not after `0x295908`: `mwSfdPause` calls `MWSFLIB_SetErrCode` right after a
  branch whose delay slot sets the same argument register. GCC 2.96 records a function it has already
  compiled in the file as unable to throw and notes that on later calls to it (`REG_EH_REGION 0`); with
  the note, the delay-slot pass drops the annul of that branch (`beql` becomes `beq`). Retail has
  `beql`, so `MWSFLIB_SetErrCode` was compiled in another file. No other function of the two files
  changes with the cut.
- Not before `0x2952d0`: by position and size `MWSFLIB_SetSeekFlg` and `MWSFLIB_GetSeekFlg` are CRI's
  functions of those names: a later PlayStation 2 build of the library carries
  the names, and its five functions between the error callback and `mwPlySfdStandby` have the sizes
  of the five here. The `MWSFLIB_` prefix is `mwsfdlib.c`'s, as `MWSFPLY_` is `mwsfdply.c`'s: in the
  GameCube library each such prefix keeps to one file. `mwsfd_GetMode` before them
  returns the player of the last SFD error (`mwsfd_err_mwsfdhn`), which `MWSFLIB_SfdErrFunc` stores.
- Not after `0x295358`: in the GameCube library `mwsfdply.o` holds the body of `mwPlySfdStandby`
  inlined into its starts, with its message, so the function is defined in `mwsfdply.c`.
- `mwply_SetTimeFn` and `mwply_ExecTime`, between those bounds, have no caller, call nothing of either
  file, own no string or data, and are absent from the GameCube library's maps and the Xbox build,
  which drop unused functions. Both files verify with the cut at any of the three addresses. They are kept with
  `mwsfd.c`: like its error callback they reach SFD through `mwPlyGetSfdHn`, where every function of
  `mwsfply.c` reads the handle's `sfd` field, and `mwply_ExecTime` takes a null handle for every
  player, as the library-wide calls do.

## Types

The player handle (`MwsfdPly`, 696 bytes) is in `include/dw4/cri/mwply.h`, its creation parameters
(`MwsfdCreInf`, the 48-byte `cprm`), the picture log entry (`MwsfdPicLog`), the SST input (`MwsfdSst`)
and the allocation pool with it. The work area (`MwsfdWork`: the init parameters, the malloc hooks, the
settings, the server hooks and the 8 players) is in `include/dw4/cri/mwsfd.h`.

Two spellings are what the retail code needs, not style:

- `MwsfdInitPrm.decSvr` is a pointer: as an `int`, `mwsflib_InitLibWork`'s loads and stores reorder.
- `mwply_ConvFrmInf` writes the MWSFD frame information through pointer-typed words (`MwsfdFrmInf`): the
  SFD side is `int`, and only with the two types apart does GCC load every source word before the stores.

## Open questions

- Without source, linking from retail: `mwPlyGetCurFrm` (`0x2937e0`) and `mwply_SetFrmInf`
  (`0x293a20`, which fills the frame information and reports `GetFps` failures), `mwply_GetPicInf`
  (`0x294390`, reads a picture header's items), `mwPlyInitSfdFx` (`0x294a58`) and the SFD error
  callback `MWSFLIB_SfdErrFunc` (`0x295010`, the `SFD ERROR(%08X)` messages). They were never decompiled.
- Whether `mwply_SetTimeFn` and `mwply_ExecTime` end `mwsfd.c` or open `mwsfply.c`; CRI's names for
  them would settle it by their prefix.
- `mwply_SetTimeFn` and `mwply_ExecTime` wrap `SFD_SetExtClockFn` and `SFD_UpdateTime` (the names a later build of
  the library carries; medium confidence, from the position and size of eight consecutive functions): the external
  clock of the sync mode and the time update of one handle or all.
- The meaning of `MwsfdPly.f692`, `src488`..`src496`, `MwsfdWork.workFlag`, and the SFD condition ids
  passed by `mwsflib_SetDefCond` (27, 7).
- Medium confidence, from the PlayStation 2 build of the library with symbols whose function sizes match this run (no GameCube map
  entry): `mwsflib_InitLibWork`, `MWSFD_SetUsePicUsr`, `MWSFD_SetPauseBdr`, `mwsflib_SetDefCond`, `mwPlyResetSfdFx`, `MWSFD_GetErrCode`,
  `MWSFLIB_SetSeekFlg`/`MWSFLIB_GetSeekFlg`, `mwPlySfdGetWritePtr`, `mwPlySfdAddWritePtr`, `mwPlyTermSupply`, `mwsfd_InitForStart`
  and `MWSFPLY_RecordFname` (its GameCube map entry is from the 3.31 library). `mwsflib_SetSvrFunc` (`0x294c10`) rests on position
  alone, its size differs in that build.
- The data word at `0x4be884` is the player of the last SFD error, which `mwsfd_GetMode` returns, and `0x4be888` is its SFD handle:
  the GameCube map names the pair `mwsfd_err_mwsfdhn` and `mwsfd_err_sfdhn`. `mwsfd_GetMode` keeps its name.
