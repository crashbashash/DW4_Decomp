# CRI SFD files: the Sofdec player library

The CRI SFD library (`CRI SFD/PS2EE Ver.1.946` at `0x4f4d00`) is the core of the Sofdec movie player under
the MWSFD front end. Its functions check a handle with one routine and report numeric error codes
(`0xFF000xxx`) through another, so the files have almost no message strings; their boundaries come from the
error-code runs, the handle sub-objects each file works on, and their data and read-only data. Each builds with
Sony EE GCC 2.96 at `-O2 -G0` as one whole file each (`cri_<name>` in `units.tsv`, their rows in
`unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)). The file names are best
guesses from what each file does.

| file | range | what it is | evidence |
| --- | --- | --- | --- |
| `src/cri/sfadx.c` | `0x29b3a8` up to `0x29cee8` | the ADX audio handler: drives ADXT for a movie's audio | its handler table at `0x4f4b18` (14 entries in code order) and the data after it up to `(c)CRI` at `0x4f4b68`; codes `0xC03` to `0xC0A` |
| `src/cri/sfdusr.c` | `0x29cee8` up to `0x29d4a0` | the handler-interface wrappers and a second handler | codes `0x1A1` to `0x1A4`; the second handler table at `0x4f4b70` |
| `src/cri/sfdbuf.c` | `0x29d4a0` up to `0x29ece8` | the stream and buffer channels (116-byte entries at handle +4872) | its init and finish hooks are called from the library init and finish; codes `0x401` to `0x40c`; its bss at `0x57fab0` |
| `src/cri/sfmpv.c` | `0x2a2f30` up to `0x2a8b50` | the video (MPV) handler: plane layout, decode slots, picture and time-stamp handling, the handler entry points | its handler table follows the SFD build string; codes `0xF01` to `0xF31` and `0x181` to `0x189`; the bss block `0x5855b0` its init clears; the previous handler group ends with `0x2a2f20` |
| `src/cri/sfmpvps2.c` | `0x2a8b50` up to `0x2aa2f0` | the PS2 side of MPV: `sceMpeg`, IPU and DMA transfers, semaphores | its own data word `0x4beb10`, bss at `0x585630` and read-only data at `0x4f4e88`; code `0xF40`; called from the MPV handler |
| `src/cri/sfdply.c` | `0x2aa2f0` up to `0x2ac6d0` | the player handle: create, destroy, start, stop, pause, the server | codes `0x131` to `0x146` and `0x201` to `0x206`; the handle table at `0x4beadc` |
| `src/cri/sfdring.c` | `0x2ac6d0` up to `0x2acb30` | the PTS queues (the SDK's `sfd_pts.o`): 16-byte entries in a ring at entry +56 of the stream table | the SDK member's order and sizes; codes `0x165`, `0x421` |
| `src/cri/sfdrec.c` | `0x2acb30` up to `0x2ad8f8` | the 0xDD8-byte time record at handle +13864 | codes `0x151` to `0x15C` |
| `src/cri/sfdcond.c` | `0x2ad8f8` up to `0x2ae010` | the handle's condition arrays and their defaults | codes `0x111` to `0x11C`; the default table at `0x4be8d8` |
| `src/cri/sftim.c` | `0x2ae010` up to `0x2afc08` | the time block at handle +0xD28 and the time-code conversions | its init and finish are called from the library init; the frame-rate and converter tables at `0x4f5060` and `0x4f5090` |
| `src/cri/sfdtrn.c` | `0x2afc08` up to `0x2b0408` | the module table and the per-handle stream graph at handle +7976 | its first function is the library's second init; code `0x302` |
| `src/cri/sfdtst.c` | `0x2b0408` up to `0x2b0ed0` | the time-stamp debug object (`tst`) and its moving averages | its data `0x4beb40` up to `0x4beb54` and its read-only data `0x4f50d0` up to `0x4f5278` (the field-name header and its print format) |

`sfadx.c` and `sfdbuf.c` share `include/dw4/cri/sj.h`; `sfmpv.c` and `sfmpvps2.c` share `include/dw4/cri/sfmpv.h`; `sfdply.c` and `sfdring.c` share
`include/dw4/cri/sfdply.h`. The other files declare their types themselves.
`sftim_Tc2Time29D`, the 29.97 drop-frame time-code converter, is named from the RE4 GameCube symbol table
([adonis-singh/re4](https://github.com/adonis-singh/re4), `config/G4BE08/sym_map.tsv`, unit `lib/sfd_tim.c`).
Names the SDK alone could not settle follow three more sources, cited by name: the order of the same files in the
RE4 GameCube symbol table (`lib/sfd_pl2.c`, `sfd_ply.c`, `sfd_mpv.c`, `sfd_mpvf.c`, `sfd_pts.c`, `sfd_set.c`,
`sfd_tim.c`, `sfd_tmr.c`, `sfd_trn.c`, `sfd_tst.c`, `sfd_buf.c`); the names the
[Persona 4 decompilation](https://github.com/Raikaru/Persona4-Decompilation) proves masked-exact against unstripped
Devil Kings, Onimusha: Dawn of Dreams and Resident Evil 4 builds (`docs/cri/proven_names.json`), taken where the
DW4 function holds the same slot with a near-equal size; and the SDK members' order where a 2004 body grew past
the 2002 one. Names from what a function does are in the medium list below.

## Types

- The ADX handler's sub-context at handle +8188 is declared `int` and cast to its struct at each use, as the
  owner approved for the cvFs, HTCI, DVCI and SFX pointers on the same condition
  ([CRI cvFs](cri-cvfs.md#integer-typed-slots)).
- A buffer channel's field at +20 is typed as a stream pointer, and memory-kind channels keep a byte size
  there through a cast; its position is cast to and from `int`. The owner approved landing it this way.
  The original most likely declared the entry body as a union of channel kinds.
- The MPV link at player +8120 and the decoder handle are `void *`: the function that clears a slot's outputs
  matches only when its `void **` out-parameters and the link share an alias set.
- The record file's time block and the time file's block are the same handle memory seen by two files; each
  file declares the fields it uses.

## Open questions

- The same handle is declared separately in several files (`SfdPly`, `SfdAdxHn`, `SfdUsrHn`, `SfdBufHn`), and
  the interface at +8460 has different slot signatures in the ADX handler and the wrappers; one shared
  declaration is a readability task.
- Where the ADX handler file starts rests on the data order alone.
- Whether `0x2a8b50` up to `0x2a96d0` (the IPU and DMA helpers, called only from later functions) is a file of its
  own in front of the MPV PS2 file.
- The ring file's split from the player file, and the one-line wrapper at `0x2ad8f8` (record file or condition
  file), have no evidence in the code either way.
- Some time-block counters at handle +0xD28 +680 up to +744 are updated from the V-sync path, and several
  functions that use them read them as `volatile` accesses would, but a `volatile` on the whole block breaks
  other functions. Which fields the original declared `volatile` is open; those functions have no source and
  link from the retail image.
- The free-slot claim at `0x2a85a0` reads a slot's state and reference count in one 64-bit load. No plain C
  with the slot's shared `int` fields reproduces that, so it has no source.
- Medium confidence: `SFTIM_Init`, `SFTIM_Finish`, `SFTIM_InitHn`, `SFTIM_InitTtu` and `SFTIM_InitTcode` (`0x2ae010`, `0x2ae020`,
  `0x2ae028`, `0x2ae248`, `0x2ae290`) come from the order of the Persona 3 FES PlayStation 2 symbol list (provenance not stated) and the
  GameCube library's map (`sfd_tim.c`), which has the same five in the same sequence; the bodies of `SFTIM_Init` agree with the
  GameCube source. `SFD_SetUsrTimeFn`, `SFD_SetExtClockFn` and `SFD_UpdateTime` (`0x2aed78`, `0x2aee00`, `0x2aeef0`) come from the same
  list: eight consecutive function sizes from `0x2aed60` match. In DW4 `SFD_UpdateTime` loops over every handle when given
  none; the 2002 `SFD_UpdateTime` body is its one-handle helper `sftim_UpdateTimeHn`.
- `SFADXT_Create`, `sfmpv_BsearchDelim` and `sfmpv_IsLate` follow the CRI PS2 SDK archive `libmwsfde.a` (recvx-decomp-cri,
  github.com/SkeletonPicture/recvx-decomp-cri; members `sfd_adxt.o`, `sfd_mpv.o`) and the Resident Evil 4 CRI sources `sfd_adxt.c`
  and `sfd_mpv.c` kept in the Persona 4 decompilation (github.com/Raikaru/Persona4-Decompilation, `src/cri/re4/`). `SFADXT_Create` matches only when the ADXT handle, the ring, handle slot 7's work and
  the four volume and pan entries of the output interface share the alias set of the renderer pointer read from the ADXT handle
  (the SDK's `ADXRNA` is `void *`), so `sfadx.c` keeps them untyped; typed pointers reorder the stores.
- `sfxcnv_CnvFrmYcc420plnToZ` and `sfxcnv_CnvFrmArgb8888mbToZ` of the SDK's `sfx_cnv.o` are `0x2b4dc8` and `0x2b4f58` with
  only the handle offsets changed. `0x2b4dc8` matches once the planar source block's seventh word is a pointer: the
  zero stored there then shares no alias set with the plane loads and is scheduled first. `0x2b4f58` still differs in
  where a constant store into the source block is scheduled.
- More bodies follow the SDK archive `libmwsfde.a` with only the offsets changed: `SFBUF_AringGetRead` (`sfd_buf.o`),
  `sfmpv_ChkBufSiz` and `sfmpv_NeedSafeDlmRefresh` (`0x2a3ef8`) of `sfd_mpv.o`, `sftst_DebWrite` (`0x2b0cf8`) of
  `sfd_tst.o`, which in DW4 also prints the handle and the 64-bit fields as `%ld`, and `sfply_InitHn` (`0x2ab8b8`) of
  `sfd_ply.o`. The RE4 `sfd_mpv.c`, `sfd_ply.c` and `sfd_tim.c` give the statement order. The delimiter check passes
  its caller's start-code word as the search's out-parameter. The handle creation matches only when the creation
  parameters' buffer address at +4 is a pointer: as an `int`, its aligned store and the handle's state stores share
  an alias set and keep their source order.
- The frame-buffer check keeps an empty loop over the frame count when no buffer block is given, as retail runs it.
- The frame-information copy at `0x2a7e30` (SDK `sfmpv_SetFrmInf`) uses a register copy of the destination for its first
  fields. After the picture-structure branch it reloads the destination pointer before every store and keeps each source
  load behind the previous store, as it would if those stores could alias the pointer. No field typing found so far does
  this.
- `sfmpv_ReadPtsQue` (`0x2a4fb8`) is the SDK's `sfd_mpv.o` member at that position before `sfmpv_InitComplementPts`; the SDK body is an older 32-bit form, so the name is medium.
- `sfmpv_IsEmptySkip` (`0x2a6510`) is named from the Resident Evil 4 CRI source `sfd_mpv.c` in the Persona 4 decompilation (`src/cri/re4/`), where the same-signature test follows `sfmpv_IsPtypeSkip` in the chunk-accept chain.
- `SFTIM_GetTime` (`0x2ae968`) is the time-and-unit read that the Resident Evil 4 `sfmpv_IsLateSkip` calls (`sfd_mpv.c` in the Persona 4 decompilation), at the SDK `sfd_tim.o` position before `SFD_GetNowTime`.
- `SFADXT_SetSpeed` (`0x29b4c8`) is the `SetSpeed` slot of the ADXT output interface that `SFADXT_Create` installs, named from the Resident Evil 4 `sfd_adxt.c` in the Persona 4 decompilation and the SDK `sfd_adxt.o` order.
- `SFTST_Calc` is the SDK `sfd_tst.o` member with DW4's leading enable word; it matches with the excess error computed
  before the difference test, the absolute value written on the difference expression, and both time projections
  written as `base != -1 ? ... : 0`.
- `sfmpv_SetFrmPara` follows the RE4 `sfd_mpv.c` body with `SFD_CalcYccPlane`'s 64-byte stride arithmetic; its frame
  parameter block (SDK `SFMPV_MPVFRM`) is `SfdFrmPara`. `0x2a5248` is the RE4 `sfmpv_CalcRepeatField` with the time-code
  copy and the backward-reference retime moved into calls.
- The transfer slot's ring id is the enum `SfdBufId` and its work handle a union of the drivers' work types
  ([a read through a union member](understanding-shapes.md#scheduling-ee-gcc)): with those types `sfmpv_GetActiveSize`,
  `sfmpv_DecodeOneUnit` and `sfmpvf_SearchStbyFrm` (with `SfdSlot **` out-parameters) match. `sfmps_DemuxChunk` still differs
  in the register of one constant, which keeps a shared store from merging. `sfmpv_DecodeFrm` hoists the stack
  load of its address-taken byte count above the frame-counter stores and keeps the frame count's load below them:
  forcing only the byte count's alias-set high word non-zero under gdb reproduces retail, so it is the
  [address-taken local](understanding-shapes.md#scheduling-ee-gcc) case and waits on the text compiled before it
  (`sfmpv_CalcAudioTotTime`, which differs by the same mechanism, among it).
- `sfply_ResetHn` is the RE4 `sfd_ply.c` `sfply_ResetHn` ([Resident Evil 4 decompilation](https://github.com/adonis-singh/re4)):
  it keeps the error callback, the timer's clock callbacks, speed and PTS-manager entry, and the seek work across
  a re-create. It matches with those `SfdD28` fields and the error block typed as the callbacks and pointers
  they are; `sfdrec.c` still keeps its own untyped copy of `SfdD28`.
- `mwPlyCreateSofdec` differs only in the delay slot of the first free-handle test, which retail fills from the
  branch target; `mwsfcre_CreateSfd` in the registers holding two of the buffer-size globals. Both need names for
  the size globals and the three SFD create-parameter templates, and the player status as an enum.
- Medium confidence, from the RE4 GameCube order alone: `SFMPV_SaveCond` and `SFMPV_RestoreCond` (after `SFD_SetMpvCond`),
  `SFMPVF_SearchFrmObj` and `SFMPVF_SearchVfrmData` (the first two of `sfd_mpvf.c`), `sfmpvf_ReferNextFrmReady` and
  `sfmpvf_SearchStbyFrm` (after `SFD_IsNextFrmReady`), `SFPTS_IsPtsQueFull` (last of `sfd_pts.c`) and `SFTST_SetTstFlg`
  (after `SFTST_Create`). No alternative reading fits the bodies.
- Medium confidence, where the SDK member's body (B or C) or its order and the RE4 GameCube order agree: `SFD_Create`,
  `SFD_SetVideoPts`, `SFPTS_WritePtsQue`, `SFPTS_ReadPtsQue`, `SFD_GetCond`, `SFPL2_Pause`, `SFPL2_Standby`, `SFTIM_VbIn`,
  `SFTIM_GetAudioStartSample`, `sftim_Tc2TimeN`, `SFTIM_Pause`, `SFTRN_CallTrtTrif`, `SFTRN_SetPrepFlg`/`GetPrepFlg`,
  `SFTRN_SetTermFlg`/`GetTermFlg` and `SFTRN_IsSetup`. No alternative reading fits the bodies.
- Medium confidence, from the SDK order where the 2004 body grew (alternative: none unless given): `sfpl2_PauseExec`,
  `sfply_AdjustEtrg`, `sfply_Fin`, `sfply_ChkCrePara`, `sfply_SearchFreeHn`, `sfmpv_DecodeSomePic`, `sfmpv_CalcVideoTotTime`,
  `sfmpv_AddRtotSj`, `sfmpv_Nfrm2Pts`, `sfmpv_DoReformTc`, `sfmpv_NextTc`, `sfmpv_SetHeadTtu`, `sfmpv_SetDecTtu`,
  `sfmpv_UpdateDefect`, `sfmpv_SetFrmTime`, `sfmpv_ErrFn`, `SFMPV_Destroy`, `sfmpv_AddReadSub`, `SFMPVP_Destroy`,
  `SFMPVP_SearchPsc`, `sfbuf_CreateSj`, `sfpts_SetupPtsQue`, `sfpts_WritePtsQueSub`, `sfpts_ReadPtsQueSub`,
  `sfpts_SearchPtsQue`, `sfsee_GetInSjReadTot`, `SFSET_GetTrHn`, `SFD_GetMvInf`, `sftim_AddHnVbIn`, `sftim_AddExtClock`,
  `sftrn_ConnTrnBuf`, `sftrn_ConnBufTrn`, `sfadxt_SetSvrFreq` and `sfadxt_SetTimeFn`. `sfmpvps2_setD3_CHCR` is the SDK's
  static `setD3_CHCR` with the file prefix, as the Sony `libipu` copy keeps the plain name.
- Medium confidence, from the Persona 4 proven names at the aligned slot: `SFD_ExecServer`, `SFD_LockFrm` and `SFD_UnlockFrm`.
- Medium confidence, from what the function does: `sfply_EnoughAiData` (the audio twin of `sfply_EnoughViData`; alternative
  `sfply_EnoughAuData`), `sfmpv_SetPicUsrBuf` (the body behind `SFD_SetPicUsrBuf`; alternative `SFMPV_SetPicUsrBuf`),
  `sfadxt_UpdateFlowCnt` and `sfmpv_UpdateFlowCnt` (the 64-bit flow totals, in the words of the GameCube
  `SFBUF_UpdateFlowCnt`), `sfbuf_InitSjUuid`, `sfbuf_IsSjRbf` and `sfbuf_IsSjMem` (the SJ kind test by interface UUID),
  and `sftim_UpdateTimeHn` (alternative `sftim_UpdateTimeOne`).
- Renamed after this review, the earlier names being guesses the order and bodies contradict: the four `sfring_*`
  functions are the SDK's `SFPTS_WritePtsQue`, `sfpts_WritePtsQueSub`, `sfpts_SearchPtsQue` and `SFPTS_IsPtsQueFull`;
  `sftrn_SetFlagA`/`GetFlagA`/`SetFlagB`/`GetFlagB` are `SFTRN_SetPrepFlg`/`GetPrepFlg`/`SetTermFlg`/`GetTermFlg` (the
  first and second words of a transfer entry, as in `sfd_trn.o`); `SFD_GetCondDef` is `SFD_GetCond` and
  `SFD_GetHnHdrInf` is `SFD_GetMvInf`.
- Still unnamed, for want of a source or a single reading: the empty function after `sfadxt_ExecServerSub`, the
  three-word reset between `sfply_InitPlyInf` and `sfply_InitTmrInf`, the frame-time projection between
  `sfmpv_CalcRepeatField` and `sfmpv_ReformTc`, the reference-error sum after `sfmpv_SetFrmPara`, the standby-slot
  timestamp copy before `sfmpv_SetFrmTime`, the three picture user-data helpers before `sfmpv_GoDdelim`, the
  record-header offset after `sfmpv_AddReadSub`, the ready-frame count before `SFD_IsNextFrmReady`, the user-header
  decode after `sfmpv_SetCondY16`, and the `sceMpeg` handle getter after `SFMPVP_IsPscEnough`.
- Data, medium: `sfmpv_fps_round`, `sfmpv_conv_29_97` and `sfmpv_conv_59_94` (the rounded frame rates and the two
  drop-frame divisor tables `sfmpv_Pts2Tc` reads) and the PTS-manager reset callback `SFPLY_ResetPtsm` take the
  names of the same tables and pointer in the RE4 `sfd_mpv.c` and `sfd_ply.c` of the Persona 4 decompilation. So do
  `sfmpv_work`, `sfmpv_para`, `sfmpv_rfb_adr_tbl`, `sfmpv_ta_adr_tbl`, `sfmpv_picusr_pbuf`, `sfmpv_picusr_bufnum`,
  `sfmpv_picusr_buf1siz` and `sfmpv_discard_wsiz` (the decoder work, the parameters and the buffer tables `SFMPV_Init`,
  `SFD_SetMpvPara` and `SFMPV_Create`/`SFMPV_Destroy` copy), `sfply_last_hnctrl_wksiz` (the handle work size
  `sfply_InitHn` compares), `SFTIM_prate` and `sftim_tc2time` (the frame-rate and time-code converter tables),
  `sftim_as_pts`, `sftim_a_sample`, `sftim_v_time` and `sftim_v_sample` (the start samples the two
  `SFTIM_Get*StartSample` record), `sftst_debout_write` and `sftst_debout_round` (the debug-output write and wrap
  pointers), `sfadxt_adxterr` (the last ADXT error code) and `sfbuf_sjrbf_uuid`/`sfbuf_sjmem_uuid` (the interface
  UUIDs `sfbuf_InitSjUuid` records), each in the RE4 sources or symbol table with the same use.
- The SDK's relocations name both `0x4bead4` and `0x4bead8` `SFLIB_libwork`: they are members of the library work at
  `sfd_lib` (its `+0x1fc` and `+0x200`, the RE4 `sfd_ply.c` and `sfd_adxt.c` `SFLIB_libwork.x1fc`/`.x200`), which DW4
  declares as separate words. They are named by role: the reset flag `SFPLY_SetResetFlg` stores (`sfply_reset_flg`) and
  the ADXT handle `sfadxt_SaveAdxtHn` keeps across a reset (`sfadxt_save_hn`). Whether `sfd_lib` should take the
  RE4 name `SFLIB_libwork`, with these words as its members, is open; so is the time-file view of the same work at
  `0x4bea88`.
