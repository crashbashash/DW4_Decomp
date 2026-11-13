# CRI ADX small files: SPSD and WAV readers, ADXCRS, the file-system server and CRI CFG

Five small CRI files, each compiled as one whole file with Sony EE GCC 2.96 at `-O2 -G0` (their rows in
`units.tsv` and `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)). The SPSD and
WAV readers share ADXB's handle, now declared once in `include/dw4/cri/adxb.h`.

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/adxspsd.c` | `cri_adxspsd` | `0x25e668` up to `0x25ea20` | the SPSD reader: its header check, header parse and decode step for ADXB | ADXB ends at `0x25e668`; the check compares with `SPSD` at `0x4ed850`, the first string after ADXB's |
| `src/cri/adxwav.c` | `cri_adxwav` | `0x25ea20` up to `0x25f2c0` | the WAV reader: the `RIFF`/`WAVE` check, the chunk search, and decode steps for 16-bit, 8-bit and byte-assembled 16-bit samples | its strings (`fmt `, `data`, `RIFF`, `WAVE`) follow `SPSD`; its two chunk-name pointers at `0x499cc0` start the data after ADXB's handle table |
| `src/cri/adxcrs.c` | `cri_adxcrs` | `0x25f2c0` up to `0x25f300` | ADXCRS: the critical section ADX takes around shared state, and its init | its word `0x499cc8` follows the WAV reader's data; the decode file (`0x25f300`) starts with its own data at `0x499cd0` |
| `src/cri/adxfssvr.c` | `cri_adxfssvr` | `0x262950` up to `0x262a30` | the file-system server pass the ADXM file-system thread runs: SRD, cvFs, the stream layer and ADXF, twice, guarded against re-entry | ADXF ends at `0x262950` and the header file starts at `0x262a30`; its step word `0x49c8c0` comes before ADXT init's data at `0x49c8d8` |
| `src/cri/cricfg.c` | `cri_cricfg` | `0x26f2b8` up to `0x26f500` | CRI CFG (`CRI CFG/PS2EE Ver.1.002`): a table of named integer settings in a 256-byte work area, written by name and read by name | the init stores the build string's address; its words at `0x56dfd0` and the 256-byte work area at `0x56dfe0` precede cvFs's handles at `0x56e0e0`; cvFs starts at `0x26f500` |

The decode steps hand ADXB's output buffer the samples of the current block and report the count through
the handle's callbacks, one step per state, as ADXB's own step does. The WAV reader dispatches on the sample
format the header parse stored in the handle.

## Open questions

- Names come from what the functions do, in the ADXB and ADXCRS API styles; the 16-bit step that assembles
  each sample from two bytes serves WAV headers that declare 4-bit samples, which the parse turns into 16-bit
  ones.
- The SPSD parse writes the block, sample and format values from the codec byte and then overwrites all but
  the format with the 16-bit values; retail keeps both sets of stores.
- No source yet: the SPSD and WAV header decoders (`0x25e788`, `0x25ec50`: their drafts store two pairs of
  handle fields in the opposite order) and the WAV header parse (`0x25ea20`: one register choice, and
  retail reuses the `-1` already in the return register for the last check).
- ADXCRS's lock and unlock (`0x25f2d0`, `0x25f2e8`) keep their address names: renaming them rewrites callers
  across the ADX, LSC and Sofdec files.
- The file-system server's activity check (`0x262a18`) matches only with the step word declared `volatile`
  (it reads it in the `lui`, `addiu`, `0(reg)` form); the word is shared with the ADXM threads. It has no
  source until the owner rules on it.
- CRI CFG's init (`0x26f2b8`) stores the build string's address in the `lui`, `addiu`, `0(reg)` form, the
  shape of the approved build-string stores ([source approvals](source-approvals.md#build-string-stores)); it
  has no row, so it has no source. `0x26f4b0` reads a setting by name (`CRICFG_Read`); its rename waits on
  its Sofdec caller.
