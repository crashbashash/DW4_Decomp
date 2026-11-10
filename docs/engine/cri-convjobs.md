# CRI conversion-job table

A small CRI file between the ADXT code and the CRI CFG module (`CRI CFG/PS2EE Ver.1.002`). It keeps a
table of 16 jobs of 60 bytes, hands out free entries, stores each job's parameters, and runs every
queued job from one server step. The source is `src/cri/convjobs.c`. It builds with Sony EE GCC 2.96
at `-O2 -G0` like the rest of the CRI blocks, as one whole file (`cri_convjobs` in `units.tsv`, its
rows in `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x26ee48` up to `0x26f2b8` | the CFG module starts at `0x26f2b8` with the function that reads its build string; no function in the range calls code, or reads data, from the ADXT functions before `0x26ee48` |
| data | `0x4a8eb0` up to `0x4a9278` | a flag word, then the job table (16 × 60 bytes); cvFs's data starts at `0x4a9278` |

Compiling the file whole matters: the server step's job runner (`0x26f160`) calls the flag setter at
`0x26f150`, and only with that function compiled earlier in the same file does GCC treat the call as
unable to throw, which decides how the runner's delay slots are filled.

## Layout

A job (`ConvJob`) holds: an in-use word, its table index, a word set by `0x26f048`, a state word
(0 idle, 1 queued, 2 running, 3 done), the result, a kind (1 or 2, choosing which of two ADX-side
routines runs), four parameters, an 8-byte block cleared on reset, and five 16-bit values passed to the
routine. The runner moves a queued job to running, calls the routine for its kind and marks it done;
for kind 2, an odd result also sets the flag word.

## Open questions

- Which CRI library the file belongs to, and so the names of the table, its fields and its functions.
  The two routines it calls sit in the ADX decoder code, and creating a job passes 500 and 44100, which
  look like a time and a sampling rate.
- Whether the file starts at `0x26ee48`. The ADXT functions before it reach nothing in it and it reaches
  nothing in them, so the bytes do not show where the boundary is; `0x26ee48` is where the table's code
  begins.
