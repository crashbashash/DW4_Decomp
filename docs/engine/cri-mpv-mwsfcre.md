# CRI MPV core and MWSFD player creation

Two whole files of the Sofdec block, both Sony EE GCC 2.96 (`-O2 -G0 -ffunction-sections`), rows `cri_mpv` and
`cri_mwsfcre` in `units.tsv`.

## src/cri/mpv.c (`0x290b28` up to `0x2918c0`)

The CRI MPV (M2V) decoder library's core: `MPV_GetVersionStr`, initialisation, the handle pool, conditions, the
bridge to the lower-layer hooks and the 64-bit multiply-divide helpers.

- Extent: `MPV_GetVersionStr` and `MPV_Init` both read `cri_mpv_version`; the file's read-only data runs from the
  version string through `mpv_default_cond` (the 16 default conditions, condition 8 pointing at `MPV_MbCbFn`)
  to `mpv_build_inf` / `mpv_endian_mark` (the `ZZZZ` block `mpvlib_ChkFatal` tests); its `.data` is the
  saturation table `mpv_clamp_table` and `mpv_clamp`; its `.bss` is `mpv_version_str`, `mpv_lib`, `mpv_cur_hn`
  and `mpv_lower_work`. The next file's first string is at `0x4f2b28`, and its `.data`/`.bss` start at
  `0x4bd0e0`/`0x5777b8`.
- Types (`include/dw4/cri/mpv.h`): `MpvLib` (the work area: default conditions, option flags, the handle table
  and the 7136-byte pool), `MpvHn` (a 1024-byte pool entry; `stat` 1 free, 2 used), `MpvPicInf`, `MpvErrObj`,
  `MpvSeqInf`, `MpvBufEnt`, `MpvLowSize` and `MpvBuildInf`. The library checks its own build with
  `mpv_build_inf`: magic `0x5a5a5a5a`, `sizeof(MpvLib)`, the handle size and the pool size.
- Handles: `MPV_Create` takes the first free entry (`mpvlib_SearchFreeHn`), clears it, binds the pool buffers and
  clamp tables (`mpv_BindHnBuffers`), copies the default conditions and creates its lower-layer half
  (`mpvhook_Create`). `MPV_SetCond` with no handle changes the default and every live handle; condition 8 left 0
  becomes `MPV_MbCbFn`.
- The lower layer is reached only through the hook table `mpv_InstallHooks` fills (`mpvhook_*`); `mpv_StartLower`
  hands it the four buffer entries and the size, then `mpv_GetLowerInf` copies its picture information back.
- `UTY_MulDiv`, `UTY_MulDivRound` and `UTY_MulDivRound64` close the file; nothing places them in a file of their
  own.

## src/cri/mwsfcre.c (`0x2918c0` up to `0x293730`)

MWSFD player creation: work-area sizes, frame buffers, picture user buffers, the SFD handle set-up and teardown,
`mwPlyGetHdrInf`, and the player's allocator.

- Extent: the strings from `E206011: MwsfdCrePrm: illigal buffmt.` (`0x4f2b28`) to `E2053001 MWSFD_Malloc: cnt
  over.` (`0x4f3070`) in code order, with the `MWSFCRE_` and `mwPlyCreateSofdec` messages between; the jump table
  of `mwsfcre_IsOutFmtDirect` (`0x4f2c80`); `.data` `mwply_vtbl`, `mwsfd_option`, `mpv_frm_buf_num`,
  `mpv_frm_buf_size` (`0x4bd0e0`-`0x4bd250`) and `.bss` up to `mpv_frm_buf_table` (`0x5777b8`-`0x5777e8`). The
  first function, `mwsfcre_CalcWorkStmBuf`, is called only by this file. The next file (the MWSFD frame
  functions, from `0x293730`) begins with the `mwPlySetFrmSync` message.
- Types: `MwsfdPly`, `MwsfdCreInf` (the 48-byte creation parameters, copied into the handle) and `MwsfdMemPool`
  from `dw4/cri/mwply.h`, `MwsfdWork` from `dw4/cri/mwsfd.h`; file-local `MwsfdFrmBufs`, `MwsfdHdrInf` and
  `SfdHdrInf`.
- Allocation: `MWSFD_Malloc` takes from the creation parameters' work area (`mwsfcre_OrgMalloc`) when one was given,
  else from the functions installed with `mwPlySetMallocFn`; it records up to 32 blocks, which
  `mwsfcre_AllFree` releases through `MWSFD_Free`. `mwsfcre_IsOkUsrMalloc` refuses a creation without a work area
  when the functions are missing.
- Frame buffers: `MPV_SetFrameBuffers` registers caller buffers; `mwsfcre_MallocRfb` uses the first two when
  they are large enough and otherwise allocates the frame pool and the decoder's fixed work.
- `mwSfdDestroy` stops the SFD, destroys the additional-information SJ, sfx, link controller, stream, both
  input SJs, the SFD handle and the SST input, frees the work, reports a block still held and resets the entry.

## Open questions

- `MPV_Init` links from retail: it stores the version pointer through a `volatile` view that is not approved.
- Without source: `mwsfcre_CalcWorkFrmBuf`, `mwPlyCalcWorkSfd`, `MWSFCRE_SetSupplySj`,
  `mwsfcre_MallocTab`, `mwsfcre_CreateSfd`, `mwPlyCreateSofdec` and `mwsfdcre_IsPlayableByHdrInf`: not decompiled yet.
- Most field names in `MpvPicInf` and the outputs of `mwsfcre_CalcWorkStmBuf` are placeholders; their meaning
  needs the lower layer and the SFD work-size users.
- `mpv_GetFixedWorkSizes` and `MPV_SetFrameBuffers` keep `mpv` names though they sit in the MWSFD file.
- Medium confidence, from the Persona 3 FES PlayStation 2 symbol list (provenance not stated) placing the names by slot and size, with
  Persona 4's names proved against other CRI builds: `MPV_GetIqmAdr`/`MPV_GetNqmAdr` (`0x290b18`/`0x290b20`, two identical
  `return 0` stubs: only the list's order separates them), `MPV_IsConformable` (`0x290b38`, same slot and size), `mpvlib_SetCondAll`
  (`0x291318`) and `MWSFCRE_SetCondSfd` (`0x2929a0`, whose body is the GameCube library's condition setup).
