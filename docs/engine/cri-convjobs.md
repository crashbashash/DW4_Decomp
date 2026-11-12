# CRI ADX packet decoder (ADXPD)

A small CRI file between the ADXT code and the CRI CFG module (`CRI CFG/PS2EE Ver.1.002`). It keeps a
table of 16 decode jobs of 60 bytes for the ADXB layer, hands out free entries, stores each job's
buffers and decoder state, and runs every queued job from one server step. The source is
`src/cri/convjobs.c`, the shared definitions `include/dw4/cri/adxpd.h`. It builds with Sony EE GCC 2.96
at `-O2 -G0` like the rest of the CRI blocks, as one whole file (`cri_convjobs` in `units.tsv`, its
rows in `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x26ee48` up to `0x26f2b8` | the CFG module starts at `0x26f2b8` with the function that reads its build string; no function in the range calls code, or reads data, from the ADXT functions before `0x26ee48` |
| data | `0x4a8eb0` up to `0x4a9278` | `adxpd_odd_block_error`, then the job table `adxpd_obj` (16 × 60 bytes); cvFs's data starts at `0x4a9278` |

Compiling the file whole matters: `ADXPD_ExecHndl` calls `adxpd_SetOddBlockError`, and only with that
function compiled earlier in the same file does GCC treat the call as unable to throw, which decides
how the delay slots of `ADXPD_ExecHndl` are filled.

## Names

No string in the file names anything. The functions take the names of the CRI ADX library's ADXPD
API, matched to what each one does and to how ADXB calls it (ADXB keeps the handle `ADXPD_Create`
returns and drives it through the rest). The decoders it calls are named from their signatures in
`src/cri/adxdcd.c`: `ADX_GetCoefficient` turns a cutoff and a sampling rate into the two filter
coefficients, `ADX_DecodeMono4` and `ADX_DecodeSte4` decode blocks for one and two channels.

## Layout

A job (`AdxPdObj`) holds: an in-use word, its table index, a mode word set by `ADXPD_SetMode`, a
state (`AdxPdStat`: stop, queued, decoding, done), the number of blocks the last decode returned, a
channel kind (`AdxPdChannels`, choosing the decoder), the input buffer, the block count, two output
buffers, the decoder history (two samples per channel, cleared on create and stop), the two filter
coefficients (`ADX_GetCoefficient(500, 44100)` on create) and three extended parameters, the first of
which the decoder updates through a pointer.

`ADXPD_Entry*` fill a stopped job; `ADXPD_Start` queues it; `ADXPD_ExecServer` runs `ADXPD_ExecHndl`
on every job in use, which moves a queued job to decoding, calls the decoder for its channel kind and
marks it done. For a stereo job, an odd block count sets `adxpd_odd_block_error`. `ADXPD_Reset` returns
a done job to stop.

## Open questions

- `ADXPD_EntryMono` and `ADXPD_EntryPl2` are byte-identical (both pick the mono decoder); which of the
  two is CRI's `EntryPl2` follows only the API's order. ADXB calls the second with two output buffers
  half a channel apart.
- What reads `adxpd_odd_block_error`: nothing in the matched code does, so its name says only when it
  is set.
- What `mode` selects: `ADXPD_SetMode` stores it and nothing in this file reads it.
- Whether the file starts at `0x26ee48`. The ADXT functions before it reach nothing in it and it reaches
  nothing in them, so the bytes do not show where the boundary is; `0x26ee48` is where the table's code
  begins.
