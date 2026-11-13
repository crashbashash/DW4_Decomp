# CRI ADXT: the playback handle and its server

ADXT is the layer games call to play ADX sound: a handle owns an input ring buffer filled by an ADXSTM stream
(or an SJ the caller supplies, or memory), an ADXSJD decoder writing one output SJ per channel, and an ADXRNA
renderer that sends those outputs to the IOP. Two files hold it, each compiled as one whole file with Sony EE GCC
2.96 at `-O2 -G0` (`cri_adxt` and `cri_adxtsvr` in `units.tsv`, their rows in `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)). They share `include/dw4/cri/adxt.h`: the handle
(`AdxtObj`), its states (`AdxtStat`), what it plays from (`AdxtPmode`), the recovery modes (`AdxtRmode`) and the
error codes.

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/adxt.c` | `cri_adxt` | `0x26b248` up to `0x26da28` | creating and destroying handles, the starts (file, AFS, memory, ACX index, SJ) and stop, time, volume, pan and balance, reload sizes, buffer queries, pause, the server pass over every handle, and the stubs PS2 keeps for other platforms' settings | its messages run in code order from `ntmp0=%4d` (`0x4ee4c8`, after the MFS/HST device file's last `MFS`) to `E8101207: can't create sj (ADXT_StartMemIdx)`; its settings words sit in `.data` from the time mode (`0x4a8e4c`) to the time drift (`0x4a8e9c`) |
| `src/cri/adxtsvr.c` | `cri_adxtsvr` | `0x26da28` up to `0x26ee44` | the per-handle state machine (header, preparing, playing, decode end, play end), the loop-start, loop-end, end-of-stream and link traps, recovery and the read and error checks | its strings start a new section at `0x4eedd0` (eight bytes past the end of `adxt.c`'s last message, more than string alignment gives) with `adxt_trap_entry`'s message; the loop-start trap installs the loop-end trap at `0x26dae0`; its `.data` starts on a 16-byte boundary at `0x4a8ea0` (the header callback, the playing-state counters, the renderer count at decode end), before ADXPD's at `0x4a8eb0` |

## Behaviour

A start only records what to play: a file start sets the stream request and state DECINFO, and the server pass
(`ADXT_ExecServer`, run from the ADXM threads) opens the file once the stream has stopped, waits for the decoder
to decode the header, then sizes the decode step from the server frequency and the block size, arms either the
loop traps (a looping stream: the end-of-stream callback rewinds the file to the loop start sector, the loop-end
trap skips the input to the next loop start and restores the decoder's history saved at the loop start) or the
link trap (seamless playback: the footer of one stream and the header of the next are dropped from the input and
the decoder restarts on the next), and configures the renderer. PREP starts the renderer once enough output is
queued; PLAYING turns into DECEND when the decoder has ended and every output is drained below 64 bytes; DECEND
pads silence until the renderer has played everything, then PLAYEND.

The time in a V-sync mode (`ADXT_SetTimeMode`: NTSC 59.94, PAL 50 per second) counts V-syncs from the base taken
at start or resume and is resynchronised to the sample time when the two drift more than 60 ms apart.

The error check counts server passes in which the decoder makes no progress or the input holds under 64 bytes;
after five seconds of passes (twenty before playback) it flags the error and, by the handle's recovery mode, stops
or restarts it from the start of its input.

## Open questions

- `adxt.c`'s start is placed where the MFS/HST device file's strings end; the settings words before its own
  (`adxt_srd_rmode_sw`, `adxt_stm_eos`, `0x4a8e40`/`0x4a8e48`) belong to that file's getters and setters and are
  read here as externs.
- No source yet: `ADXT_InsertSilence` (`0x26d328`: the drafts reproduce its shape but keep the frame length in a
  second saved register).
- `adxt_stat_prep` reads the V-sync count in the `lui`, `addiu`, `0(reg)` form, so `adxtsvr.c` redeclares the
  count `volatile` for itself, as [the ADXT tick count](source-approvals.md#adxt-ready-count) describes, and the
  other files keep the plain declaration. `ADXT_ExecHndl` follows it in the file: a call to a function already
  compiled in the file carries an exception-region note that fills the delay slot of the branch after it.
- `ADXT_ExecServer` reads and writes its phase word in the `lui`, `addiu`, `0(reg)` form and declares it
  `volatile`; it has no approval row, so it stays `unapproved`.
- One error code, `ADXT_ERR_SHRTBUF` (-1), stands for a starved input, a file that cannot be opened and a read
  error.
- Names from behaviour, without a string: `ADXT_CreatePl2`, `ADXT_DestroyAll`, `ADXT_CloseAllHandles`,
  `ADXT_StopWithoutLsc`, `ADXT_GetTimeRna`, `ADXT_GetTimeReal`, `ADXT_GetDefOutVol`, `ADXT_GetDefPan`,
  `ADXT_GetDataId`, `ADXT_SetDefSvrFreq`, `ADXT_SetAutoRcvr`, `ADXT_ExecSvr` (a wrapper of the server pass that
  nothing calls), `ADXT_SetOutMode`/`ADXT_GetOutMode` (PS2RNA's output-mode word), `ADXT_TermSupply`,
  `ADXT_EntryErrFunc`, `ADXT_DiscardSmpl`, `ADXT_SetTimeOfst`, `ADXT_AdjustSmpl`, `ADXT_EntryFltFunc`,
  `ADXT_EntryDecFunc` (its message is `ADXT_GetDecDtLen`'s), `adxt_IsHeader`, `ADXT_SetOutputMono`,
  `ADXT_SetDefKeyString`, `ADXT_ResetDefFmt`, `ADXT_StartMem`, `ADXT_InsertSilence`, `adxt_trap_entry` (its
  message names it), `adxt_stat_prep`, `adxt_stat_playing`, `adxt_stat_playend`, `adxt_ExecRdErrChk`,
  `adxt_ExecRdCompChk`; the hook at `0x4a8e64` that `ADXT_Stop` calls is `adxt_stop_func`.
- `src/cri/adxtinit.c` and `src/cri/adxtsml.c` still declare their own handle layouts; they should use
  `AdxtObj` from `adxt.h`.
