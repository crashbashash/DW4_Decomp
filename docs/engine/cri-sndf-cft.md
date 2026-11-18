# CRI SNDF and CFT

The first two files of the Sofdec block, each compiled as one whole file with Sony EE GCC 2.96 at `-O2 -G0`
(their rows in `units.tsv` and `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/sndf.c` | `cri_sndf` | `0x280b98` up to `0x283018` | SNDF (`SNDF Ver.2.09c`), the sound driver's EE side: SIF RPC to the IOP, voices, programs, streams and pan tables | its first function reads the build-string pointer at `0x4bb10c`; every function uses its context at `0x572a00`, its RPC buffers or its status block at `0x5717c0`; its data `0x4bb100` up to `0x4bb3e8` |
| `src/cri/cft.c` | `cri_cft` | `0x283018` up to `0x285118` | CFT (`CRI CFT/PS2EE Ver.1.57`): colour-format and alpha-plane conversion tables | its data starts at `0x4bb3e8` (the name-message pointer) with the 0x1800-byte table block at `0x4bb3f8`; the next module's data starts at `0x4bcbf8` |

## Open questions

- `SNDF_Init` (`0x280b98`) reads the build-string pointer once and discards it, in the delay slot of the call to
  `sceSifInitRpc`; the owner approved that read under [build-string reads](source-approvals.md#build-string-reads),
  declared `char *const volatile` (with `char *volatile` the read lands before the call). Its two bind-wait loops,
  zero words included, come from plain C (the compiler's loop alignment); a braced `break` in the second loop adds a
  word of padding. Its parameter is `SndfInitParam`, read from what the IOP's init command (`0x1300`) does with the
  four words: the first is the size of the IOP work area it allocates when the second, an IOP address, is 0; a
  nonzero third initialises libsd and sets the master volumes; the fourth is the voice-transfer DMA channel
  (`sndf_dma_channel`). The pointer member is load-bearing: under type-based aliasing its load does not depend on
  the `sndf_dma_channel` store, and the copy's loads then come in retail's order (fourth, first, third, second);
  with four `int`s the second and third swap.
- CFT's init stores its version string in a `volatile` word, approved under
  [build-string stores](source-approvals.md#build-string-stores).
- `SNDF_GetControl` (`0x281568`) reads three bytes of the status block's per-channel control values. They are a flat
  byte array indexed `channel * SNDF_CONTROL_SIZE + n`, which is load-bearing: with a struct per channel (constant
  field offset) the compiler builds the shared `0xA009`/`0xA00A` tail's address as base plus index and ties the sum
  to the base register, where retail (and the flat index, whose constant rides with the index) ties it to the
  index. What each of the three bytes holds is open.
- The SNDF entry points the game calls for its sound banks (port sizes, transfer start and status, freeing a
  port, the control and master-parameter messages) are named from what they do and how the game uses them;
  no string or other build carries the library's own names for them.
- `sndf_CallRpc` (medium; alternative `sndf_SendCommand`) is named from what it does: it copies the arguments into the
  shared buffer `sndf_rpc_buf` and sends one command to `sndf_cmd_client` under `sndf_rpc_busy`.
- The rest of `sndf.c` takes behaviour names, medium, with the alternative in brackets. No other build has SNDF;
  the evidence is the command each one sends, what the game's IOP module (`SNDFI.IRX`, `SNDF Driver Ver 2.09c`, the
  RPC servers `SNDF` and `SFSV` that `SNDF_Init` binds) does for that command, and the sibling calls in
  `sndfcmd.c`. The 32 channels are the bank ports. Start and stop: `SNDF_Stop` (`SNDF_End`) sends `0x200` and clears
  `sndf_started`, undoing `SNDF_Start`'s `0x100`; `sndf_InitContext` (`sndf_ResetContext`) is `SNDF_Start`'s reset of
  `sndf_context`. Banks: `SNDF_LoadBank` (`SNDF_TransferSync`) runs `SNDF_StartTransfer` to completion;
  `sndf_ExecTransfer` (`sndf_TransferBlock`) moves one block of an upload through the IOP buffer to SPU memory with
  sdrdrv's voice transfer, while `sndf_dma_channel` (the fourth `SNDF_Init` parameter) is idle; `SNDF_OpenPort`
  (`SNDF_SetupPort`, `0xA00`) opens a port once its bank is in place, as `SNDF_FreePort`'s `0x700` closes it;
  `SNDF_LoadIopBank` (`SNDF_OpenIopPort`, `0x800`) has the IOP check a bank already in IOP memory, send its waveform
  and open the port; `sndf_GetPortArea` (`sndf_CalcPortAddr`) gives a closed port's IOP table and SPU addresses from
  the sizes `SNDF_SetPortSizes` recorded, and `SNDF_GetPortSizes` reads them back (`0xFE00`). Read-backs:
  `SNDF_GetControl` (`SNDF_GetVoiceStatus`) and `SNDF_GetCtrlChange` (`SNDF_GetProgramParam`) return what
  `SNDF_SendControl` and `SNDF_SendCtrlChange` set, with the same kind codes; `SNDF_GetOutputMode`
  (`SNDF_GetSpeakerMode`) the mode the IOP sets from the `0xA00009`/`0xA00008`/`0xA00029` messages;
  `SNDF_GetSoundStatus` (`SNDF_IsSoundPlaying`) a sound slot's state; `SNDF_GetPlayStatus` (`SNDF_IsPortPlaying`)
  whether one of the status block's 16 play entries is on the port. IOP state: `SNDF_GetProcTime` (`SNDF_GetLoad`)
  the microseconds the IOP server's last pass took; `SNDF_GetQueueCount` (`SNDF_GetMessageCount`) the EE messages
  still queued on the IOP and the IOP's own; `SNDF_ClearQueue` (`SNDF_ResetQueue`, `0xF900`) empties both;
  `SNDF_GetVoiceCount` (`SNDF_GetVoiceListCount`, `0xFD00`) the counts of the IOP's four lists of its 48 voices;
  `SNDF_GetEffect` (`SNDF_GetReverb`, `0xFC00`) the bank and preset of the current effect (preset 127 is off);
  `SNDF_GetErrorMessage` (`SNDF_GetLastError`, `0xFB00`) the message word the IOP last refused for a pitch outside
  the SPU range. Events: an `0xA024` message leaves an event byte on the IOP; `SNDF_SetCallback`
  (`SNDF_EntryEventFunc`, `0x1700`) stores the function `sndf_SvrCallback` (`sndf_SvrEndFunc`, the end function of
  `SNDF_ExecServer`'s call to `sndf_svr_client`) hands that event to, and turns on its delivery in the server reply
  `sndf_svr_recvbuf`; `SNDF_GetEvent` (`SNDF_ClearEvent`, `0xE00`) reads and clears it. Which voice states the four
  `SNDF_GetVoiceCount` lists hold, and what the 16 play entries are (sequences or streams), is open.
- The data words take the same kind of names: `sndf_initialized` (set by `SNDF_Init`'s `0x1300`), `sndf_started`,
  `sndf_svr_sendbuf` (the command block `SNDF_ExecServer` sends), `sndf_svr_busy` (only cleared, by
  `sndf_SvrCallback`; alternative `sndf_svr_pending`) and `sndf_rpc_init_flag` (set first in `SNDF_Init`, read by
  nothing). The context fields follow the IOP side: `sizesSet` is what `SNDF_StartTransfer` requires of
  `SNDF_SetPortSizes`, `transIdle` the last voice-transfer status, and the status block's `outputMode`, `procTime`,
  `msgQueued`, `iopMsgQueued` and `voiceCount` are the IOP words it copies there.
- The SNDF message calls in the file after `sndf.c` (none of which the game calls) take behaviour names, medium, with
  the alternative in brackets. The messages are MIDI-shaped (a status byte with bit 7 set, byte-swapped into the
  queue): `SNDF_SendChMessage` (`SNDF_SendPortMessage`) sends one to a channel below 32; `SNDF_SendVoiceMessage`
  (`SNDF_SendMidiMessage`) builds a channel-voice message from kind 8..13 and two 7-bit bytes; `SNDF_SendCtrlChange`
  (`SNDF_SendPortControl`) sends 0xB0 control changes, the 14-bit ones as an MSB/LSB pair; `SNDF_SetChannelParam`
  (`SNDF_SendChannelControl`) sends the 0xA5-0xA7 messages as `SNDF_SetMasterParam` sends 0xA4. The sound slots
  (1..24, queue kind 3): `SNDF_StartSound` (`SNDF_PlaySe`, command 0xF00, returns the slot), `SNDF_StopSound`
  (0x1000; `SNDF_KeyOffSound`), `SNDF_ReleaseSound` (0x1100; `SNDF_PauseSound`), `SNDF_SetSoundPanVol` (0x1200, an
  angle turned into a pan position, through `sndf_pan_remap` in output mode 2, and a volume clamped to 255),
  `SNDF_StartChannelSound` (an 0xA0 message for a channel, started through `SNDF_StartSound`) and
  `SNDF_SetSoundPitch` (0x1800, semitones and cents as `SNDF_SeqCommand`'s command 8). Whether 0x1000 and 0x1100 are
  stop and release or another pair is open.
- `CFT_Init` (medium) holds the SDK `cft_lib.o` slot before `CFT_Finish` and stores the CFT build string.
  `CFT_SetMaxAlpha` and `CFT_GetMaxAlpha` (medium; alternative a `cft_` prefix) keep the word `CFT_Init` sets to 128
  and `SFX_SetMaxAlpha` forwards to. `CFT_MakeYcc422ColAdjTbl` and `CFT_MakeArgb8888ColAdjTbl` hold the SDK `cftfx.o`
  slots with the same sizes, and the SFX table makers call them as in the SDK.
- `CFT_GetVersionStr` (`0x283098`) returns the address of the word that holds the maximum alpha (`cft_max_alpha`), not
  a string; `CFT_Init` writes the build string itself (`cft_version_ptr`). Whether the slot kept the 2002 name is open.
- The file opens with the common part the RE4 CRI library (RE4 decompilation in the
  [Persona 4 decompilation](https://github.com/Raikaru/Persona4-Decompilation), `src/cri/re4/cft_common.c`) calls
  `cft_common.c`: `cftcom_function_name` holds the same "This CFT function doesn't support ..." string there, so the
  getter is `CFT_GetFunctionName` and the setter `CFT_SetFunctionName` (medium). The next word is
  `cftcom_optimize_speed` with `CFT_SetOptimizeSpeed`/`CFT_GetOptimizeSpeed` (medium; alternative the `..._size`
  switch, the second of the two the RE4 file has). The 0x1800-byte table is the SDK `cftfx.o` `cftcoladjtbl`.
- The three macroblock alpha loops before `UTY_CmpTime` are named from what they do (medium): `cft_MergeArgb8888mbAlpha`
  (`cft_SetAlphaFromSecondHalf`) sets each pixel's alpha from the red byte of the second half of its row, halved plus
  one; `cft_CopyMbAlphaToArgb8888` and `cft_CopyMbAlphaToArgb8888mb` copy a macroblock's alpha plane (the second 384
  bytes of 768) through a table into a line-ordered or macroblock-ordered ARGB8888 buffer. None is called.
