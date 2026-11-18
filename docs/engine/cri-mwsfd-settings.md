# CRI MWSFD settings, scratchpad swap and player getters

Two whole files of the MWSFD (Sofdec player front end) sit just before `src/cri/mwsfsfx.c`. Both build
with Sony EE GCC 2.96 at `-O2 -G0 -ffunction-sections` (`cri_mwsfdrsc`, `cri_mwplyprm` in `units.tsv`,
their rows in `unit-objects.json`).

| file | code | evidence for the extent |
|---|---|---|
| `src/cri/mwsfdrsc.c` | `0x295e58` up to `0x296328` | no strings; every function serves the settings words (`mwsfd_enable`, `mwsfd_spr_cb`, `mwsfd_spr_swapped`, `mwsfd_spr_cpu_copy`) or the scratchpad swap. `MWSFD_InitRsc`/`MWSFD_FinishRsc` open it by calling `mwrsc_InitVal`; the previous file (FSof3's mwPly wrappers on `ply->sfd`) ends at `0x295e54`. It ends before the first `E…` handle-check string user |
| `src/cri/mwplyprm.c` | `0x296328` up to `0x297780` | its strings are one `.rodata` run, `0x4f39b8` (`E1122617 mwPlySetAudioSw`) to `0x4f4027` (`E309101 : Timer channel…`), right after the previous file's `mwPlyStartFnameRange` strings and right before `mwsfsfx.c`'s first string (`E201184`) at `0x4f4028`; `mwsfsfx.c` starts at `0x297780` |

## mwsfdrsc.c

While the Sofdec server runs (`mwPlySaveRsc` / `mwPlyRestoreRsc`), `MWRSC_SaveRsc` parks the game's
16 KiB scratchpad in `mwsfd_spr_save_buf` and loads Sofdec's own image from `mwsfd_spr_work_buf`;
`MWRSC_RestoreRsc` reverses it. The copies go through DMA channels 8 (from SPR) and 9 (to SPR), or
through `memcpy` when `MWSFD_SetSprCpMode` is set. `MWSFD_SetUseSPR` turns the swap off;
`MWSFD_ExecSprCbFn` passes a player handle and the enable flag to the callback set by `MWSFD_SetSprCbFn`;
nothing in the image calls either. `MWSFSEE_StartFnameSub1`, `MWSFSEE_StartFnameSub2` and `MWSFSEE_ChkSupply` are
empty hooks the player calls.

## mwplyprm.c

The public `mwPly*`/`mwSfd*` setters and getters: each checks the handle with `MWSFD_IsEnableHndl` and
forwards to the SFD decoder (`ply->sfd`), the ADXT handle (`ply->adxt`) or the file stream
(`ply->stm`). SFD condition words are set through `MWSFD_SetCond` and its wrappers (the counter and timer callbacks `mwPlyEntryDecExecCb`/`mwPlyEntryDecSkipCb`, `mwPlySetNeverSkip`, the idle auto-off of video and audio `mwply_SetVideoAutoOff`/`mwply_SetAudioAutoOff`); the file
declares the decoder's header and playback information blocks (`SfdHdrInf`, `SfdPlyInf`) and the
caller-side `MwsfdPlyInf` / `MwsfdFlowInf` locally, as nothing else reads them yet. `MwsfdPly` comes
from `include/dw4/cri/mwply.h`.

## Open questions

- The file name `mwsfdrsc.c` is CRI's (`MWRSC_SaveRsc` and `MWRSC_RestoreRsc` are the entries of the SDK's `mwsfdrsc.o`). The
  three hooks at its end (`MWSFSEE_StartFnameSub1`, `MWSFSEE_StartFnameSub2`, `MWSFSEE_ChkSupply`) are CRI's `mwsfdsee.c`, a
  separate object in the SDK archive and in the RE4 GameCube library, so the unit's end at `0x296328` may be two files; the
  evidence for the cut is not collected.
- SFD condition words are named by what the reader does where it was traced; each condition has a reader in this
  image. Medium confidence, from the GameCube build's readers of the same conditions (the setters themselves are in no symbol list):
  `MWSFD_AdjustGetFrmTiming` (44: the lead added to the clock in the time verdict of `sftim.c`, seeded at creation from
  the v-syncs per frame and the display latency), `mwply_SetSystemEndcodeSkip`/`mwply_SetVideoEndcodeSkip` (56/57, each
  ORed with condition 49 in the SFD core at `0x29ed68` and `0x29edb0`), `mwply_SetSeqHdrData` (93/94, a buffer and length
  handed to the MPV decoder while it waits for the first sequence header, read at `0x2a3850`), `mwply_SetSeqHdrCbFn`
  (77/78, the callback and object the SFD MPV driver calls with the sequence header after `MPV_SearchDelim`, read at
  `0x2a4ea8`/`0x2a4eb8`) and `mwply_SetPesCbFn` (91/92, the PES callback and object handed to the MPS decoder,
  read at `0x2a142c`/`0x2a143c`).
- Still numbered: `mwply_SetCond73` (forces the skip mode before the first timer tick, read at `0x2a63dc`) and
  `mwply_SetCond95` (writes the object and then the function into the same condition, 95; the SFD MPV driver reads it
  at `0x2a4dc0` as the sequence-size callback and its object, calls it with the width and height and reports -2 on a
  nonzero return). The GameCube build also reads the callback and the object from the one condition, so the object is lost.
  A name needs a symbol list or a clearer reading.
- `mwPlySetFastHalfpel` (`0x296dd0`) sets MPV condition 3 through `SFD_SetMpvCond` (medium confidence: CRI's Dreamcast
  header documents the function and its semantics, and the Katana library's body sets MPV condition 3). `mwPlySetIpicOnly`
  and `mwPlySetAdjustY16` set MPV conditions 4 and 5 through the same function: 4 selects the intra output table in the
  MPV decoder, and 5 is the motion-compensation chroma flag, which `SFD_SetMpvCond` forces to 0, so its setter can only
  clear it. The M2V readers of conditions 3, 4 and 5 were not traced.
- The names of `mwsfdrsc.c` follow the `mwsfdrsc.o` and `mwsfdsee.o` members of the CRI PS2 SDK archive `libmwsfde.a`
  ([recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)) where it has them: `mwrsc_WaitSprDmaEnd`,
  `MWDMA_WaitEnd` and `MWDMA_GetStat` have its bodies (high), `MWRSC_SaveRsc` and `MWRSC_RestoreRsc` near ones (medium).
  `MWSPR_SaveSprMem` and `MWSPR_RestoreSprMem` hold its slots after `mwrsc_WaitSprDmaEnd` and are called from the
  `MWRSC_` pair as there (medium); their 2002 DMA bodies are now `MWSPR_SaveSprByDma` and `MWSPR_RestoreSprByDma`, behind
  a choice of CPU or DMA copy. `mwPlySwitchToIdle` (`0x2962c8`, medium; alternative the earlier guess
  `MWSFD_ExecVsyncFrame`) is the SDK member between `MWDMA_GetStat` and `mwPlySaveRsc`, declared in the SDK's
  `crimwsfd.h`: the 2002 body waits a v-sync between saving and restoring the scratchpad, DW4's runs one
  `ADXM_ExecVsyncFrame`. The three `MWSFSEE_` hooks are the SDK names, empty here as in the RE4 GameCube
  `lib/mwsfdsee.c` ([adonis-singh/re4](https://github.com/adonis-singh/re4), `config/G4BE08/sym_map.tsv`; high). Named
  from what they do (medium): `MWSFD_InitRsc`/`MWSFD_FinishRsc`, `MWSFD_SetUseSPR`/`MWSFD_GetUseSPR`,
  `MWSFD_SetSprCbFn`/`MWSFD_ExecSprCbFn`, `mwrsc_InitVal` (with the SDK file's `mwrsc_` prefix),
  `MWSPR_SaveSprByCpu`/`MWSPR_SaveSprByDma`, `MWSPR_RestoreSprByCpu`/`MWSPR_RestoreSprByDma` and
  `MWSFD_SetSprCpMode`/`MWSFD_GetSprCpMode`.
- The getters `MWSFD_GetCond`, `MWSFD_GetStmHn`, `MWSFD_GetLscHn` and `MWSFD_GetAdxtHn` of `mwplyprm.c` have the bodies of
  the SDK's `mwsfdset.o` (high); `MWSFD_GetInputSjBufSize` and `MWSFD_GetSfxHn` near ones in the same order (medium).
- `SfdPlyInf` fields other than the ones the getters read are unknown.
