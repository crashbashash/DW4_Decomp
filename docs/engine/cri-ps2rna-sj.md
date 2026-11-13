# CRI PL2ENC, ADXT Pro Logic II, PS2RNA and the SJCRS, SJERR and SJMEM stream-joint files

Six CRI files after MFCI, each compiled as one whole file with Sony EE GCC 2.96 at
`-O2 -G0 -ffunction-sections` (their rows in `units.tsv` and `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)). Each file's functions, strings and data run
in the same order.

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/pl2enc.c` | `cri_pl2enc` | `0x278610` up to `0x278f20` | PL2ENC: the Dolby Pro Logic II encoder | MFCI ends at `0x27860c`; its `.data` starts with `PL2ENC Ver.1.01` at `0x4b0dd8`, then its init count and error callback (`0x4b0e08`–`0x4b0e10`); its `.rodata` is the gain table at `0x4f0f08` and its `E0309xxxx` messages up to `0x4f1430` |
| `src/cri/adxtpl2.c` | `cri_adxtpl2` | `0x278f20` up to `0x279218` | ADXT's Pro Logic II attach and the hooks it installs | its four `E200309xxxx` ADXT messages (`0x4f1430`–`0x4f14d8`) follow PL2ENC's; it has no data of its own |
| `src/cri/ps2rna.c` | `cri_ps2rna` | `0x279218` up to `0x27b250` | PS2RNA: the ADX renderer whose voices play on the IOP | `PS2RNA Ver.1.30` at `0x4f1510` starts its strings, which run in code order to `PS2RNA_SetStmHdInfo: not implemented`; its `.data` starts with the pointer to that build string at `0x4b0e18` |
| `src/cri/sjcrs.c` | `cri_sjcrs` | `0x27b250` up to `0x27b2e0` | SJCRS: the stream joints' critical section and server-pass count | the `SJCRS_` functions; its words at `0x4b5138` and `0x4b5140` precede SJMEM's table |
| `src/cri/sjerr.c` | `cri_sjerr` | `0x27b2e0` up to `0x27b2f8` | SJERR: the stream joints' error report | the one `SJERR_` function between SJCRS and SJMEM's error callback |
| `src/cri/sjmem.c` | `cri_sjmem` | `0x27b2f8` up to `0x27bc38` | SJMEM: a stream joint over a caller's memory block | its error callback `sjmem_Error` reports `SJMEM Error`, which follows its UUID at `0x4f1a58`; the vtable at `0x4b5148` names its methods; SJRBF starts at `0x27bc38` with its own error callback |

## PL2ENC and the ADXT attach

`PL2ENC_Create` lays a `Pl2Enc` (in `include/dw4/cri/pl2enc.h`) and two 96-word surround delay lines out in
the caller's work area. Each sample is weighted by four gains from `pl2enc_gain_tbl`, picked by the position
(`PL2ENC_SetPos`, x and y from -127 to 127): left and right from x, front and surround from y. The front part
goes straight out; the surround part goes through the delay, out of phase between the two sides. The delay is
one sample per 750 Hz of the sample rate (`PL2ENC_SetSfreq`), at most 96. Every `PL2ENC_` entry point takes
`SVM_Lock` around its lower-case worker.

`ADXT_AttachPl2` needs a stereo ADXT handle. It stops the handle, creates the encoder at the decoder's stored
position and hangs it on the ADXB handle (`AdxbObj.pl2`, `pl2_x`, `pl2_y` in `include/dw4/cri/adxb.h`). It
then installs the hooks the other files call when an encoder is attached: ADXT's detach
(`adxt_detach_pl2`), ADXB's per-sample encode and reset (`adxb_pl2_exec_func`, `adxb_pl2_reset_func`) and
ADXSJD's header hook (`adxsjd_header_hook`), which passes the decoded sample rate on.

## PS2RNA

`PS2RNA_SetupVoice` sets how many IOP voices exist (stereo pairs and mono voices, at most 32). If none
are set up, the library is off and every entry point returns at once. `ps2rna_init_psj` builds one stream
path per voice: an SJRMT on the IOP, an SJUNI on the EE handed a 16 KB IOP buffer as free space, and the SJX
joining them. A handle (`Ps2Rna`, 100 bytes, 16 of them at `ps2rna_obj`) holds each setting twice, as set
and as last sent. The DTX send callback (`ps2rna_dtx_send`) turns every difference into a 16-byte command
for the IOP, so the setters only store. `PS2RNA_ExecServer` runs each active handle's transfers between
`SJCRS_BeginSvr` and `SJCRS_EndSvr`, then the DTR and SJX servers. Many entry points exist only to
report `not implemented`.

## SJMEM

An SJMEM handle reads a fixed memory block front to back on its data line. `UngetChunk` takes back only the
chunk it last handed out, and nothing can be put on either line. Every entry point takes SJCRS around a
lower-case worker that checks the handle and reports through `SJERR_CallErr`. An unknown line goes to the
handle's error callback with -3.

## Open questions

- No source yet: `pl2enc_Init` and `pl2enc_Create` (the `memcmp` that keeps PL2ENC's build string comes out
  scheduled differently: retail sets up the stack and return address around the first argument), the
  `PS2RNA_Init` and `PS2RNA_Create` bodies, the DTX send callback `ps2rna_dtx_send` and the per-handle
  server step `ps2rna_exec_one` (all four long, not attempted), and `FUN_0027b2a0` in SJCRS, which clears
  the word at `0x4b5140` in the `lui`, `addiu`, `0(reg)` form only a `volatile` gives.
- The PS2RNA names not taken from strings are guesses from behaviour: the global output mode
  (`ps2rna_outmode`, IOP command 11), the aux pair (`PS2RNA_StartAux`/`StopAux`, commands 14 and 15, and
  the per-handle `auxsw`, command 10), the two output ports (`PS2RNA_OpenPort`/`ClosePort`, commands 16 and
  17, opened from the port mode the IOP reports for `BASE_SFREQ`) and the per-handle `dualsw` (command 12,
  only when both ports are open).
- `ps2rna_dtx_recv` waits out a spin count the IOP sends back and hangs on no reply.
