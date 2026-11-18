# CRI SNDF and CFT

The first two files of the Sofdec block, each compiled as one whole file with Sony EE GCC 2.96 at `-O2 -G0`
(their rows in `units.tsv` and `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/sndf.c` | `cri_sndf` | `0x280b98` up to `0x283018` | SNDF (`SNDF Ver.2.09c`), the sound driver's EE side: SIF RPC to the IOP, voices, programs, streams and pan tables | its first function reads the build-string pointer at `0x4bb10c`; every function uses its context at `0x572a00`, its RPC buffers or its status block at `0x5717c0`; its data `0x4bb100` up to `0x4bb3e8` |
| `src/cri/cft.c` | `cri_cft` | `0x283018` up to `0x285118` | CFT (`CRI CFT/PS2EE Ver.1.57`): colour-format and alpha-plane conversion tables | its data starts at `0x4bb3e8` (the name-message pointer) with the 0x1800-byte table block at `0x4bb3f8`; the next module's data starts at `0x4bcbf8` |

## Open questions

- SNDF's init (`0x280b98`) reads the build-string pointer once and discards it, in the delay slot of the call to
  `sceSifInitRpc`; the owner approved that read as a `char *volatile` word under
  [build-string reads](source-approvals.md#build-string-reads), to land once the function matches. Its two
  bind-wait loops, zero words included, come from plain C (the compiler's loop alignment). The best C still
  differs in twelve words: retail computes the first RPC client's address into a saved register before the flag
  store and fills the call's delay slot with the read, where the C computes the address last; and two loads of
  the parameter copy at the end are swapped. Statement orders, a local client pointer, `do`/`for` loop shapes, an
  inline bind helper, the real `sceSifInitRpc` prototype and a permuter run left the prologue unchanged.
- CFT's init stores its version string in a `volatile` word, approved under
  [build-string stores](source-approvals.md#build-string-stores).
- The function at `0x281568`, whose shared tail serves the `0xA009` and `0xA00A` commands, has no source: the best
  C is 3 words off, the voice address built in another operand order (retail loads the status-block address first,
  then shifts the channel and adds).
- The SNDF entry points the game calls for its sound banks (port sizes, transfer start and status, freeing a
  port, the control and master-parameter messages) are named from what they do and how the game uses them;
  no string or other build carries the library's own names for them.
- `sndf_CallRpc` (medium; alternative `sndf_SendCommand`) is named from what it does: it copies the arguments into the
  shared buffer and sends one command under a busy flag. The rest of SNDF's internal functions (the one-command
  wrappers, the status-block getters, the port and channel helpers) stay unnamed: the command codes they send
  (`0x200`, `0x800`, `0xE00`, `0xF900`, `0xFB00` and others) are not named by any string or other build.
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
