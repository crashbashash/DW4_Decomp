# CRI MWSFD seamless, SST, server and stream files

Four files of the Sofdec player (MWSFD, `MWSFD/PS2EE Ver.3.33s281`) between the SFX front end
([cri-mwsfsfx.md](cri-mwsfsfx.md)) and the SFD ADX audio file (`cri_sfadx`). Each builds with Sony EE GCC
2.96 at `-O2 -G0 -ffunction-sections` as one whole file (`cri_mwsflsc`, `cri_mwsfsst`, `cri_mwsfsvr`,
`cri_mwstm` in `units.tsv`, rows in `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

| file | code | what it does |
| --- | --- | --- |
| `src/cri/mwsflsc.c` | `0x298ec0` up to `0x2996e0` | seamless playback: `mwPlyEntryFname`, `mwPlyEntryAfs` and `mwPlyEntryFnameRange` queue entries on the player's LSC; `mwPlyStartSeamless`, the `...Lp` starters, `mwPlyReleaseLp`/`mwPlyReleaseSeamless`; the queue getters; `mwPlyLinkStm` switches SFD's stream linking |
| `src/cri/mwsfsst.c` | `0x2996e0` up to `0x299fc8` | the SST input: work sizes, the input callback table (`mwsfd_SetInputCbTbl`) and the calls through it, `MWSST_Create`/`MWSST_Restart`/`MWSST_Destroy` of the SJ ring bound to SFD stream `0xC0 + stmNo` |
| `src/cri/mwsfsvr.c` | `0x299fc8` up to `0x29b068` | the server: registration of the vint/vsync/main/idle servers with SVM, SVM lock and error wrappers, `mwsfd_Error`, the per-player server step (`mwply_UpdateStat`, `mwply_CheckPrepared`, `mwsfsvr_StartStm`, `mwlSfdExecDecSvrPlaying`), the vsync and idle servers, `mwPlyExecSvrHndl` and the busy/waiting flags |
| `src/cri/mwstm.c` | `0x29b068` up to `0x29b3a8` | MWSTM, the file stream over ADXSTM: bind a file or range, start, stop, seek, flow limits |

## Extent evidence

- Strings: `mwsflsc` owns `0x4f45f8` (`E1122633: mwPlyEntryFname`) up to its `"%08x.%08x"` at `0x4f4978`, read by
  `mwPlyStartSctLp`, the last function before `0x2996e0`. The `MWSST_Create` messages follow at `0x4f4988`. The
  server's messages (`mwPlyStartXX`, `MWSTM_ReqStart`, `mwlSfdExecDecSvrPlaying`, the jump table of
  `mwsfsvr_ExecDecSvr`, `mwPlyExecSvrHndl`, `MWSFSVR_IsSvrBdrHndl`) run in code order from `0x4f4a10`; the next
  jump table, at `0x4f4b18`, belongs to `cri_sfadx`.
- Data: `mwsfd_input_cb_tbl` (`0x4be8a0`, the table and its init count) is the SST file's; the server's
  `.data` follows it (`mwsfsvr_vsync_cnt`, `mwsfsvr_vsync_cnt2`, `mwsfsvr_cur_ply`), and its `.bss` is
  `mwsfd_err_msg` (256 bytes) directly followed by the four server ids from `mwsfsvr_vint_svr_id`. The
  message buffer and the ids being adjacent puts `mwsfd_Error` and the server registration in one file.
- SST: everything from `0x2996e0` works on the SST sub-object of the player (`ply->sst`, offset 660) or on the
  input callback table; the getters `mwply_GetInputSj`/`mwply_GetInputExtHn` read its fields.
- Server: every message from `0x299fc8` to `0x29b068` names the server (`MWSFSVR_`) or a server step, and
  the code between registers or runs those servers.
- MWSTM: from `0x29b068` every function is an ADXSTM wrapper or a stub; MWSFD init and finish call
  `MWSTM_InitStatic` and `MWSTM_FinishStatic` apart from `mwsfsvr_Init`. The file ends at `cri_sfadx`.

## Types

The player and its SST sub-object (`MwsfdSst`) are in `include/dw4/cri/mwply.h`, the work area
(`MwsfdWork`) in `include/dw4/cri/mwsfd.h`, the ADXSTM handle in `include/dw4/cri/adxstm.h`. The input
callback table (`MwsfdInputCbTbl`) is local to the SST file.

## Notes

- `mwPlyLinkStm` takes its handle untyped and types it after the validity check: typed from the start,
  GCC keeps the link byte in a register across the store of `linkPrev`.
- `MWSST_Restart` and `MWSST_Destroy` pass the external handle (`sst->extHn`) to `mwsst_Stop`, which takes
  the SST; retail does this.
- The two copies of the `mwPlyStartXX` message are one static string: retail has one.
- `mwsfsvr_VsyncProc` and `mwPlyExecSvrHndl` keep the `volatile` they had as one-function files
  (no approval row, category `unapproved`).

## Open questions

- `MWSST_Create` (`0x299ce8`) and `mwsfsvr_ExecServer` (`0x29ac78`) have no source and link from retail.
- `mwsfsvr_VsyncProc` and `mwPlyExecSvrHndl` match only with a `volatile`: no plain ordering tried reproduces
  the reload/branch shapes.
- Names beyond the messages are from behaviour: the SST table's slots at 32 (`mwsst_SetPrm`) and the work-size
  pairs, `mwstm_StubThird` (a stub nothing calls; CRI's Init/InitStatic and Finish/FinishStatic pairing would
  make it `MWSTM_Finish`, a guess), and which SVM server the callbacks are meant for.
- `mwsfsvr_StartStm` (`0x29a718`) is the caller that prints `E211141 MWSTM_ReqStart: can't start '%s'`: it
  runs the stream start, binds the file range and hands the SJ to the creation code, as the GameCube library's
  static server helper does. The real `MWSTM_ReqStart` is the ADXSTM start wrapper at `0x29b328`. The name
  `mwsfsvr_StartStm` is from what the function does.
- Medium confidence, from the Persona 3 FES PlayStation 2 symbol list (provenance not stated there) placed by
  slot and size, with the names proved against other CRI builds where Persona 4's list has them: `MWSTM_SetRdSct`,
  `MWSTM_SeekSct`, `MWSTM_GetFsizeByte`, `MWSTM_SetFname`; by slot only: `MWSTM_SetTrSct`, `MWSTM_Start`,
  `MWSTM_ExecServer`, `MWSTM_GetFlowLimit`, `MWSTM_Stop`. Persona 3's `MWSTM_GetReadFlg` for `0x29b210`
  (`MWSTM_GetStatRead` here) is low confidence and not applied.
