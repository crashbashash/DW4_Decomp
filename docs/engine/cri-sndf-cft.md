# CRI SNDF and CFT

The first two files of the Sofdec block, each compiled as one whole file with Sony EE GCC 2.96 at `-O2 -G0`
(their rows in `units.tsv` and `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/sndf.c` | `cri_sndf` | `0x280b98` up to `0x283018` | SNDF (`SNDF Ver.2.09c`), the sound driver's EE side: SIF RPC to the IOP, voices, programs, streams and pan tables | its first function reads the build-string pointer at `0x4bb10c`; every function uses its context at `0x572a00`, its RPC buffers or its status block at `0x5717c0`; its data `0x4bb100` up to `0x4bb3e8` |
| `src/cri/cft.c` | `cri_cft` | `0x283018` up to `0x285118` | CFT (`CRI CFT/PS2EE Ver.1.57`): colour-format and alpha-plane conversion tables | its data starts at `0x4bb3e8` (the name-message pointer) with the 0x1800-byte table block at `0x4bb3f8`; the next module's data starts at `0x4bcbf8` |

## Open questions

- SNDF's init (`0x280b98`) passes the build-string pointer as a third argument to `sceSifInitRpc`, with no
  value in the second; no C spelling found reproduces that, so it has no source. Its message switch at
  `0x281bb8` is a balanced compare tree no case spelling tried gives.
- CFT's init stores its version string in a `volatile` word and is `unapproved`
  ([build-string stores](source-approvals.md#build-string-stores)). Two table builders and two alpha-plane loops have no source (store order; a multiply retail
  recomputes on each pass).
