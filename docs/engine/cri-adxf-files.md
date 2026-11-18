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
- `ADXF_Ocbi` (`0x260a40`, the cache invalidate) is placed in ADXF; its callers match either way. 3rd Strike
  keeps it in a file of its own (`adx_fcch`), and `ADXF_Init`/`ADXF_Finish` in another (`adx_fini`).
- Names of the 2004 additions, medium: `ADXF_Ocbi`, `ADXF_Init`, `ADXF_Finish`, `ADXF_LoadPartition`,
  `ADXF_LoadPartitionEx`, `ADXF_LoadPtFromAfsNwEx`, `ADXF_GetFsizeByte` and `ADXF_GetFileSize` by order and size in
  the Street Fighter III 3rd Strike libadxe ([3s-decomp](https://github.com/crowded-street/3s-decomp)), the first
  three also in the CRI names the Persona 4 decompilation matched in unstripped PS2 builds
  ([Raikaru/Persona4-Decompilation](https://github.com/Raikaru/Persona4-Decompilation), `docs/cri/proven_names.json`);
  `adxf_SetFileInfoRange` and `ADXF_OpenRange` from that list alone (it spells the open `adxf_OpenRange`, an
  internal function behind a public one in that later version; here it is the public entry, written like
  `ADXF_Open`). `ADXF_GetFsizeByte` keeps the `ADXF_GetFsizeSct` error text of the body it was split from.
- The sync-code search at `0x25f460` compares through a local holding the code, which keeps the constant
  out of the loop; the spelling was found by trial.
- `ADX_DecodeSte4` chooses its mono or stereo decoder by `adx_decode_output_mono_flag`, the 2002 SDK's name
  for the word (`adx_dcd3.o` defines it, `adx_dcd5.o` reads it the same way;
  [recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)).
- ADXF's init (`0x260a60`) reads its build-string pointer through a `const volatile`-compatible word and discards
  it: retail performs the discarded read in the PS2, GameCube and Xbox builds alike, and the keyword is approved
  ([source approvals](source-approvals.md#build-string-reads)). Its six stores follow retail's order, which is
  also the GameCube build's. The three ADPCM block decoders (`0x25fdf0`, `0x25ffd0`, `0x260398`) have drafts
  whose control flow is right but whose register allocation is not.
- The partition information's fields take the 2002 SDK's `ADXF_PTINFO` names (`cri_adxf.h` and the STABS of
  `adx_fini.o` in `libadxe.a`, [recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)):
  `nentry` at 12, `type` at 14 (original or appended partition), `rev` at 15 (reserved), `curdir` at 272. The
  SDK's `ADXF_LoadPtNwEx` stores only `type`, as 0, before its read, and the partition loader here stores 0 at
  14 the same way. This version adds `base` (the AFS offset) at 276, moving `top` to 280, and keeps the file
  table's width in `rev`: the long-format loaders (`ADXF_LoadPtFmgLongNwEx`, `ADXF_LoadPtFromAfsFmgLongNwEx`)
  set it to 1 for a table of 32-bit sector counts, the others to 0 for 16-bit ones. Whether the 2004 header
  renamed `rev` is not known.
