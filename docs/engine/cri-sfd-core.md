# CRI SFD core files: sync queues, stream analysis, header, library core, supply and MPS handlers

These six files sit in front of the [CRI SFD player files](cri-sfd-files.md), from `0x29ece8` (after
`sfdbuf.c`) up to `0x2a2f30` (where `sfmpv.c` starts). Like the rest of the library they build with Sony EE GCC
2.96 at `-O2 -G0 -ffunction-sections`, one whole file each (`cri_<name>` in `units.tsv`, their rows in
`unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)). The file names are best guesses
from what each file does. Every SFD file starts with its own entry points, so a file's init and finish hooks, or
its public API, begin it.

| file | range | what it is | evidence |
| --- | --- | --- | --- |
| `src/cri/sfdsync.c` | `0x29ece8` up to `0x29f160` | the link-stream switch (`SFD_SetConcatPlay`, condition 49) and the queues on the time block the audio and video handlers share: the running total with its 32 past values (`SFCON_UpdateConcatTime`, `SFD_GetTimePerFile`) and the 32-entry time-stamp queue (`SFCON_WriteTotSmplQue`, `SFCON_ReadTotSmplQue`) | codes `0x161` and `0x162`; no data of its own; every function after the switch works on handle +3368 +352 up to +636 |
| `src/cri/sfdana.c` | `0x29f160` up to `0x29fe80` | stream analysis for the MWSFD header query (`SFD_AnalyCreInf`): system stream (pack spacing and mux rate), CRI header, ADX, MPEG audio and MPEG video detection | its read-only data runs from `0x4f4ba8` (the video frame rates) through the MPEG audio tables to `0x4f4d00`, right after `sfdusr.c`'s handler table and up to the SFD build string; its bss `0x57fab8` (the 2048-byte copy buffer) and `0x5802b8` (one header record); its data word `0x4be8c0` (the last MPEG audio header) |
| `src/cri/sfdhdr.c` | `0x29fe80` up to `0x2a0988` | the CRI header in private stream 2: the SFH init and finish hooks, reading a header through SFH into the handle's header record at +120, copying it to and from the work record, the stream-version query | starts with its init and finish hooks, called from the library's module init and finish (`sfd_InitModules`, `sfd_FinishModules`); its bss `0x580b50` (the SFH handle pool) follows `sfdana.c`'s header record; every function works on the 2196-byte header record |
| `src/cri/sfdlib.c` | `0x2a0988` up to `0x2a0ea0` | the library core: version string, init and finish, the error blocks (`sfd_ReportError`, `SFD_SetErrFn`, `SFD_GetErrInf`), the handle check, the lock | starts with `SFD_GetVersionStr`; the SFD build string `0x4f4d00` is its read-only data; codes `0x101`, `0x102`; the library state `0x4be8d8` (548 bytes, `sfd_lib`) and the current handle `0x4be8d0` |
| `src/cri/sfdsup.c` | `0x2a0ea0` up to `0x2a0f98` | the supply module's handler: the application writes the stream into the module's output channel itself, so the handler answers the write requests and refuses the read ones | its 14 functions are the 14 entries of the handler table at `0x4f4d50`, in table order; code `0x501` |
| `src/cri/sfmps.c` | `0x2a0f98` up to `0x2a2f30` | the MPS (system stream) handler: the stream-object API, demultiplexing the input channel into the video, audio and user-data channels, the picture record, and the 14 handler entries | its handler table at `0x4f4d88` and the PES packet table at `0x4f4dc0` (the next table, `0x4f4dd0`, is `sfmpv.c`'s); codes `0x171` and `0xD01` up to `0xD0E`; its parameter block at handle +8592, reached through the MPS slot of the stream graph (+8052) |

`src/cri/sfdana.c` and `src/cri/sfdhdr.c` share the header record (`SfdHdrInf`), and `src/cri/sfdhdr.c` and
`src/cri/sfmps.c` share the seek record's system analysis (`SfdRecSys`). The handle is `SfdPly` in
`include/dw4/cri/sfdply.h`; its parts are in `include/dw4/cri/sfd.h`. The MPS types come from `include/dw4/cri/mps.h`.

## Types

- `SfdPly` is the one definition of the 14072-byte handle, and every SFD file reads it, `sfmpv.c` and `sfmpvps2.c`
  included. Its parts follow the
  RE4 SFD object's: the creation parameters (`SfdCrePrm`, whose first word is the stream-module table
  SFTRN_InitHn reads), the conditions (`int cond[100]`, indexed by the `SFD_COND_*` enum), the buffers
  (`SfdBufEnt[8]`, +4872: a union of the ring, audio ring, frame and user-output modes), the frames
  (`SfdVfrm[16]`, +5800), the stream graph (`SfdTrnSlot[9]`, +7976, its work word a union of the modules' work
  types), the system module's work (`SfdMpsPrm`, +8592), the video work (`SfdMpv`, +9120), the ADX work
  (`SfdAdxCtx`, +13600), the audio output (`SfdAoap`, +13780), the user outputs (`SfainfList`, +13808), the seek
  record (`SfdRecSlot`, +13864) and the server statistics (`SfdTmrInf`, +13880). The library state is `SfdLibInf`
  (`sfd_lib`), with the V-sync count `SfdTimLib` at +432.
- Access through a union member is type-punned by ee-gcc 2.96 (every load and store conflicts), so the files reach
  a buffer's mode through a pointer to the mode struct where retail schedules a load across stores.
- Medium names from use: `SfdTrnSlot.readTot` (`sfsee_GetInSjReadTot`), `SfdVfrm.used`, `SfdCrePrm.unit` (the
  input's sector size; alternative: the zero padding of a short read). The seek record's analyses at +2768 and
  +3340 are the video's and the audio's (`SfdRecVideo`, `SfdRecAudio`; RE4 leaves them unassigned): the
  sfsee checks gate +2768 on condition 5 and slot 2 and +3340 on condition 6 and slot 3, and the ADX handler fills
  +3340's channel count, frequency and samples.
- The sub-objects of the handle have one definition each in `include/dw4/cri/sfd.h`, embedded in every handle
  view: the header record (`SfdHdrInf`, +120), the stream information (`SfdMvInf`, +2316), the playback information
  (`SfdPlyInf`, +2384), the error block (`SfdErrInf`, +2544) and the time work (`SfdTim`, +3368, with the time
  stabiliser `SfdTst`, the field table and the PTS manager entry inside it), plus the creation analysis
  (`SfdAnaInf`). Their layout and the member names the DW4 files did not already give follow the SFD object of the
  Resident Evil 4 decompilation's CRI library (`sfd.h`, carried as `src/cri/re4` in
  [Raikaru/Persona4-Decompilation](https://github.com/Raikaru/Persona4-Decompilation)), whose offsets match DW4's;
  those names are medium (the RE4 names are inferred from use). `MwsfdPlyInf` takes the public names of the 2002
  SDK's `crimwsfd.h`.
- `SfdAnaInf`'s three handler words are the system, video and audio handlers (RE4 `strif`/`vtrif`/`atrif`):
  `mwsfcre_DecideFtypeByHdrInf` maps them to the SDK's `MWSFD_FTYPE_SFD`, `_MPV` and `_VONLYSFD`.
- Medium names with an alternative: `SfdMvInf.fixedFlag` (+28; RE4 leaves it unnamed, DW4's init sets it to 1) and
  `privateBound` (+44, the header's private stream count); `SfdPlyInf.noSupply` (+32, the alternative
  `bpaCount`: it counts the buffer pauses `sfply_ChkBpa` starts).
- The library state `sfd_lib` (`SfdLibInf`) holds the default conditions, the init parameters, the system status
  (`sfply_sys_stat` is its field at +408), the library error block, the time, buffer and stream-graph blocks of
  `sftim.c`, `sfdbuf.c` and `sfdtrn.c`, and the handle table (`sfply_handles`, +516).
- Conditions 75 and 76 hold the application's header callback and its object, 85 and 86 the system-header
  callback and its object: `SFSET_GetCond` returns them as `int` and the files cast them back.
- The demultiplexer's system-header bounds (`MpsSysHd.audioBound`, `.videoBound`) decide when an output's play
  condition is cleared and whether a split video packet is passed on.
- The video driver's work `SfdMpv` (handle +9120) and its frames `SfdSlot` take the RE4 library's `SFMPV_WORK` and
  `SFMPV_FRM` member names where the code agrees (medium): `picstat`, `dlmmask`, `termflg`, `gopstat`
  (`SFMPVF_SetGopStat`), `nskip`, `nconcat`, `last_ngop`, `newgop`, the PTS complement state `SfdPtsComp`
  (`tmpref`, `ofst`, `max`, `ptsent`), `pendfrm`, `skipret`, `dlmwait`, `tmpref_adj`, `pts`. A frame's counts at
  +64..+80 are what `mwply_SetFrmInf` hands out as the public `MwsfdFrmObj`'s `errcnt`, `rcvcnt`, `concat_cnt`,
  `time_per_file` and `time` (2002 SDK `crimwsfd.h`), so they take those names (`cat_time` for the last) rather than
  RE4's `ndct`/`nbyte`/`gopno`; `SfdFrameInfo` carries the same words, and its detail block the `M2vPicAtr` names it
  copies. The decoder parameters `SfdMpvCond` (RE4's `SFMPV_PARA`) are named from use: reference frame size and area,
  largest picture, frame buffer size, count and area (medium; RE4 calls +0/+4 `cwidth`/`cheight`).
- The IPU input ring `SfdIpuStream` is CRI's copy of Sony's `vibuf.c`; `headSct`, `active` and `totalBytes` are
  named from use (medium), the saved DMA registers keep `r28`..`r60`. `SfdIpuCtl` counts picture start codes
  (`pscNext`, `pscFound`, `pscCount`) and keeps the last three bytes put (`tail0`..`tail2`); its error record is
  libmpeg's `sceMpegCbDataError`.
- The seek record's video analysis `SfdRecVideo` is the one `sfmpv_SetMpvHd` fills: the first picture's time and
  unit, the time state then and the sequence header's user data. A seek request `SfdRecSub` holds a time (-3 for
  none) and its unit (medium; RE4 calls the time `pos`).
- `SfdPlyInf` +20/+24/+36/+40/+44 are named from use (medium): `numSkipEmptyP`, `frmOut` (set by `SFD_GetFrm`,
  cleared by `SFD_RelFrm`), `vidShort`, `noFreeFrm`, `lockCnt`. `SfdTim` +352, +644/+648 and +676..+696 likewise:
  `concat_frmcnt`, `dec_time`/`dec_unit`, `usr_frm_sync`, `disp_sync_cnt`/`_time`/`_unit`.
- The ring delimiter has its own type `SfdBufDlm`: its second word is the end address of the data searched.
- The PES packet table at `0x4f4dc0` is `sfmps_CopyPketFn`, the copy function of each stream kind (audio, video,
  private, padding), after the read-only table of that name the `sfd_mps.o` member of the CRI PS2 SDK archive
  `libmwsfde.a` (recvx-decomp-cri, github.com/SkeletonPicture/recvx-decomp-cri) indexes by the packet's kind in
  `sfmps_CopyPketData` (high). DW4's `sfmps_PutPes` is that function grown by the stream objects of
  `SFD_SetStmObject` and the size checks; it keeps its behaviour name (whether DW4's build still calls it
  `sfmps_CopyPketData` is open).
- The sync queue's word at +4 is `samples`, the audio samples of the files joined so far: `sfmpv_CalcAudioTotTime`
  adds each joined file's count read from the queue and turns the sum into time with the queue's rate (medium;
  RE4's `SFCON` leaves it unnamed).

## Open questions

- `SFH_IsExistStmId` returns nothing in `sfh.c`, yet `sfhds_AnlyUsedStmid` tests its result; this file declares it `int`.
- The supply and MPS handlers' entries 5 to 8 are named after the ADX handler's (prepare, start, stop, pause) and
  entry 13 (`*_LoadRec`) after what the MPS handler does there; the other handlers have not been checked against
  that reading.
- `SFBUF_RingGetWrite`, `SFBUF_RingGetRead` and `SFBUF_RingAddWrite` return the buffer call's result and the last
  takes the tail length: `sfdbuf.c` declares them `void` with three parameters.
- What the MPS parameter block's words at +36 up to +48 and +344, and the video settings' word at +28, hold.
- Whether the supply handler shares `sfdlib.c`'s file: nothing in the code tells; its own error code and its own
  table put it in a file of its own here.
- Still named by offset, with no reader beyond a clear or a copy: `SfdPlyInf` +8, +12, +136, +144; `SfdTim`
  `pad332`, the PTS manager entry; `SfdIpuStream` +88/+92 and its time-stamp entries;
  `SfdCrePrm` +44..+52; `SfdFrameDetail` +72 (2 or 1 by `M2vPicAtr.f64`, whose meaning is unknown);
  `SfdRecSub` +0; the SFX handle and work (`sfx.h`), `mwsffrm.c`'s own frame views and the M2V picture attributes'
  +64/+68.
