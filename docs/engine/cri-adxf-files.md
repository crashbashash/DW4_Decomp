# CRI ADX decode, ADXERR and ADXF files

Three CRI ADX files after the SPSD and WAV readers, each compiled as one whole file with Sony EE GCC 2.96 at
`-O2 -G0` (their rows in `units.tsv` and `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/adxdcd.c` | `cri_adxdcd` | `0x25f300` up to `0x260750` | ADX header checks and the ADPCM block decoders | its read-only data is `(c)CRI` and the 16-entry nibble table at `0x4ed880`, after the WAV reader's strings; its data word `0x499cd0` (the decoder select) follows the stream lock's `0x499cc8` |
| `src/cri/adxerrs.c` | `cri_adxerrs` | `0x260750` up to `0x260a40` | ADXERR: the error callback, its object, the message buffer and an integer-to-text helper | its data `0x499cd8` up to `0x499de0`; ADXF's build-string pointer follows |
| `src/cri/adxf.c` | `cri_adxf` | `0x260a40` up to `0x262950` | ADXF (`ADXF/PS2EE Ver.7.18`): AFS partitions and file handles | its init is the first function to touch ADXF's data (`0x499de0` up to the 2048-byte buffer at `0x49a800`); its messages run from the build string at `0x4ed8c8` to `ADXF_SetReqRdSct` |

## Open questions

- The cutoff-coefficient function at `0x25f300` (called from ADXT and the encoder) has no data of its own; it
  is placed in the decode file rather than with the stream-lock helpers before it.
- The cache-sync wrapper at `0x260a40` is placed in ADXF; its callers match either way.
- The sync-code search at `0x25f460` compares through a local holding the code, which keeps the constant
  out of the loop; the spelling was found by trial.
- ADXF's init (`0x260a60`) reads its build-string pointer and discards it, the shape of an approved
  `volatile` read ([source approvals](source-approvals.md#build-string-reads)); it has no row, so it has no
  source. The three ADPCM block decoders (`0x25fdf0`, `0x25ffd0`, `0x260398`) have drafts whose control flow
  is right but whose register allocation is not.
