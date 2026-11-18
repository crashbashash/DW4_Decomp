# CRI MPV core and MWSFD player creation

Two whole files of the Sofdec block, both Sony EE GCC 2.96 (`-O2 -G0 -ffunction-sections`), rows `cri_mpv` and
`cri_mwsfcre` in `units.tsv`.

## src/cri/mpv.c (`0x290b28` up to `0x2918c0`)

The CRI MPV (M2V) decoder library's core: `MPV_GetVersionStr`, initialisation, the handle pool, conditions, the
bridge to the lower-layer hooks and the 64-bit multiply-divide helpers.

- Extent: `MPV_GetVersionStr` and `MPV_Init` both read `cri_mpv_version`; the file's read-only data runs from the
  version string through `mpv_default_cond` (the 16 default conditions, condition 8 pointing at `MPV_MbCbFn`)
  to `mpv_build_inf` / `mpv_endian_mark` (the `ZZZZ` block `mpvlib_ChkFatal` tests); its `.data` is the
  saturation table `mpv_clamp_table` and `mpv_clamp`; its `.bss` is `mpv_version_ptr`, `mpv_lib`, `mpv_cur_hn`
  and `mpv_lower_work`. The next file's first string is at `0x4f2b28`, and its `.data`/`.bss` start at
  `0x4bd0e0`/`0x5777b8`.
- Types (`include/dw4/cri/mpv.h`): `MpvLib` (the work area: default conditions, option flags, the handle table
  and the 7136-byte pool), `MpvHn` (a 1024-byte pool entry; `stat` 1 free, 2 used), `MpvErrObj`,
  `MpvSeqInf`, `MpvMotionRange`, `MpvUdLevel` and `MpvBuildInf`. The picture attributes, the user-data sinks and the picture
  user buffer of a handle are the lower layer's `M2vPicAtr`, `M2vUsrSj` and `M2vPicUsr` (`m2v.h`), and the
  hook table (`mpvhook.h`) is typed as the M2V entry points it holds. The library checks its own build with
  `mpv_build_inf`: magic `0x5a5a5a5a`, `sizeof(MpvLib)`, the handle size and the pool size.
- Handles: `MPV_Create` takes the first free entry (`mpvlib_SearchFreeHn`), clears it, binds the pool buffers and
  clamp tables (`mpv_BindHnBuffers`), copies the default conditions and creates its lower-layer half
  (`mpvhook_Create`). `MPV_SetCond` with no handle changes the default and every live handle; condition 8 left 0
  becomes `MPV_MbCbFn`.
- The lower layer is reached only through the hook table `mpv_InstallHooks` fills (`mpvhook_*`); `mpv_StartLower`
  hands it the four buffer entries and the size, then `mpv_GetLowerInf` copies its picture information back.
- `UTY_MulDiv`, `UTY_MulDivRound` and `UTY_MulDivRound64` close the file; nothing places them in a file of their
  own.
- Fields from the RE4 `mpv.h` in the RE4 decompilation of the
  [Persona 4 decompilation](https://github.com/Raikaru/Persona4-Decompilation) (medium): the motion-compensation table
  `mcFunc[4]` at 724 (`mpv_DecPicHdr` copies the forward entry into the current one, as RE4's `mpv_hdec.c` does) and
  `stc[3]` at 860 (the "STCCODE" user-data values). The word at 396 is `rsv` (cleared by `mpvlib_InitHn`, read
  nowhere; RE4 leaves it unnamed). The scratchpad pool is `MpvPool`: block, macroblock and DCT work at 4352, 4384
  and 4448 and the clamp-table copy at 6112, ending at `MPV_POOL_SIZE`.
- Chroma siting: the picture attributes' words at 64 and 68 (`M2vPicAtr.chroma_pos_h`/`chroma_pos_v`, enum
  `M2vChromaPos`) are set to 0 and 1 by the M2V decoder and to 1 and 1 by the MPEG-1 reset, which is MPEG's siting
  (MPEG-2 4:2:0 chroma co-sited horizontally and between the lines vertically, MPEG-1 centred both ways).
  `sfmpv_SetFrmInf` copies them into `SfdFrameInfo.chromaPosH`/`chromaPosV`, and MWSFD passes them on as
  `MwsfdPicInf.chromaPosH`/`chromaPosV` to SFX's picture format (`mwsfsfx_CnvChromaPosToSfx` accepts exactly 0 and 1).
  The M2V header's `second_field` (1 while the second field of a field-coded frame is decoded) and its counter
  `field_parity` follow `calcPictureCodingExt`; the three header words `M2VHDEC_InitHn` only clears are `rsv1`..`3`.

## src/cri/mwsfcre.c (`0x2918c0` up to `0x293730`)

MWSFD player creation: work-area sizes, frame buffers, picture user buffers, the SFD handle set-up and teardown,
`mwPlyGetHdrInf`, and the player's allocator.

- Extent: the strings from `E206011: MwsfdCrePrm: illigal buffmt.` (`0x4f2b28`) to `E2053001 MWSFD_Malloc: cnt
  over.` (`0x4f3070`) in code order, with the `MWSFCRE_` and `mwPlyCreateSofdec` messages between; the jump table
  of `mwsfcre_IsOutFmtDirect` (`0x4f2c80`); `.data` `mwply_vtbl`, `mwsfd_option`, `mpv_frm_buf_num`,
  `mpv_frm_buf_size` (`0x4bd0e0`-`0x4bd250`) and `.bss` up to `mpv_frm_buf_table` (`0x5777b8`-`0x5777e8`). The
  first function, `mwsfcre_CalcWorkStmBuf`, is called only by this file. The next file (the MWSFD frame
  functions, from `0x293730`) begins with the `mwPlySetFrmSync` message.
- Types: `MwsfdPly`, `MwsfdCreInf` (the 48-byte creation parameters, copied into the handle), `MwsfdHdrInf` and
  `MwsfdMemPool` from `dw4/cri/mwply.h`, `MwsfdWork` from `dw4/cri/cri_mwsfd.h` and `SfdHdrInf` from `dw4/cri/sfd.h`;
  file-local `MwsfdFrmBufs`, `MwsfdSfdPrm`, `MwsfdMpvCond`, `MwsfdAdxCfg`, `SfdSupplyKind` and `SfdSupplyPrm`.
  `SfdSupplyPrm`'s last word is `rsv`: `MWSFCRE_SetSupplySj` always stores 0 there and `sfbuf_ChkSupSj` refuses a
  ring supply with a positive value (the RE4 CRI library's `SFBUF_SUP` in the Persona 4 decompilation,
  github.com/Raikaru/Persona4-Decompilation `src/cri/re4/sfd.h`, leaves it unnamed; medium).
- Allocation: `MWSFD_Malloc` takes from the creation parameters' work area (`mwsfcre_OrgMalloc`) when one was given,
  else from the functions installed with `mwPlySetMallocFn`; it records up to 32 blocks, which
  `mwsfcre_AllFree` releases through `MWSFD_Free`. `mwsfcre_IsOkUsrMalloc` refuses a creation without a work area
  when the functions are missing.
- Frame buffers: `MPV_SetFrameBuffers` registers caller buffers; `mwsfcre_MallocRfb` uses the first two when
  they are large enough and otherwise allocates the frame pool and the decoder's fixed work.
- `mwSfdDestroy` stops the SFD, destroys the additional-information SJ, sfx, link controller, stream, both
  input SJs, the SFD handle and the SST input, frees the work, reports a block still held and resets the entry.

## Open questions

- `MPV_Init` stores the version pointer through a `char *volatile` word, approved under
  [build-string stores](source-approvals.md#build-string-stores).
- Without source: `mwsfcre_CreateSfd` (`0x292078`). Its best C differs in about 12 words: the addresses of
  buffer-size globals (`0x5777b8` up to `0x5777d8` and `0x4bd128` up to `0x4bd228`) swap callee-saved registers and
  the MPV condition store order differs; those globals and the three SFD create-parameter templates have no names
  yet.
- `mwPlyCreateSofdec` (`0x292ba8`) searches the eight players by index (`ply = &work->ply[i]`), as the 2002 SDK
  object and the RE4 source do, and reads each in-use word through a `volatile` cast
  ([mwsfd-handle-used](source-approvals.md#mwsfd-handle-used)). The second pointer in its loop is the compiler's
  strength-reduced copy, not a variable. The player status is CRI's `MwsfdStat` enum: as an `int` its store is
  ordered against the reads of the creation parameters.
- The outputs of `mwsfcre_CalcWorkStmBuf` are placeholders; their meaning
  needs the lower layer and the SFD work-size users.
- `mpv_GetFixedWorkSizes` and `MPV_SetFrameBuffers` keep `mpv` names though they sit in the MWSFD file.
- `mpvlib_SetCondAll` (`0x291318`, after `MPV_SetCond`) and `MWSFCRE_SetCondSfd` (`0x2929a0`, between `MWSFCRE_DestroySfd`
  and `MWSFCRE_ResetSfdHn`, whose body is the GameCube library's condition setup) hold the slots of the same names in the
  CRI PS2 SDK archive `libmwsfde.a` (members `mpv_lib.o` and `mwsfdcre.o`;
  [recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)) with near bodies (medium).
- Named from what they do, as no approved source names them (medium): `mpvhdec_ReturnZero1` and `mpvhdec_ReturnZero2`
  (`0x290b18`/`0x290b20`), two identical `return 0` stubs after `MPV_MoveChunk` that nothing calls, and `MPV_IsDecodable`
  (`0x290b38`, alternative `MPV_IsMpeg1`), which finds the sequence header and accepts the stream when the M2V lower layer
  is installed, otherwise only when no sequence extension follows it. Nothing calls `MPV_IsDecodable` either.
- Each `mpvhook_*` wrapper calls one slot of the hook table and is named after the M2V function `mpv_InstallHooks`
  stores in that slot (`mpvhook_DecodePicAtr` calls the slot holding `M2V_DecodePicAtr`, and so on). Medium
  confidence; the earlier guesses `mpvhook_SetBufEnt`, `mpvhook_SetSize`, `mpvhook_SetFlagPtr`, `mpvhook_Start`,
  `mpvhook_GetPicInf`, `mpvhook_GetInf`, `mpvhook_GetRate` and `mpvhook_GetDispSize` named slots after other
  functions and are replaced. The alternative is the GameCube library's `MPVM2V_*` spelling, which covers only some
  of them.
- The three M2V header-file functions after `M2VHDEC_InitHn` are `M2V_SetUsrSj`, `M2V_SetPicUsrBuf` and
  `M2V_GetPicUsr` (medium). The [Persona 4 decompilation](https://github.com/Raikaru/Persona4-Decompilation)
  proves the first and third masked-exact as `MPV_SetUsrSj` and `MPV_GetPicUsr` in Devil Kings, Onimusha and
  Resident Evil 4 (`docs/cri/proven_names.json`); DW4 also links the MPV library, which keeps those names, so the
  M2V copies take the M2V prefix the file's other entry points use. `parseSec` and `parseUdsc` hold the SDK
  `m2v_hdec.o` slots after `parseShc` (medium); `m2vhdec_PutUsrDat` and `m2vhdec_AppendPicUsr`, which hand user
  data to the user SJ and the picture user buffer, are named from what they do (medium).
- `M2V_IsDecodable` (medium; alternative `M2V_IsMpeg2`) is the M2V library's stream check between
  `M2V_GetVersionStr` and `M2V_Init`, the slot `MPV_IsDecodable` holds in the MPV library. It walks the start codes
  with the same `MPV_SearchDelim`/`MPV_CheckDelim` calls and accepts a stream only when a sequence extension (MPEG-2)
  follows the sequence header. Its hook wrapper is `mpvhook_IsDecodable` and the slot `mpvhook_fn_IsDecodable`; nothing
  calls the wrapper.
- The hook table's words are `mpvhook_installed` and `mpvhook_fn_<entry>`, after the M2V function each holds.
