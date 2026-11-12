# CRI MFCI: the memory-file device

MFCI (`MFCI/PS2EE Ver.1.09` at `0x4f0c50`) is a cvFs device whose files are blocks already in memory. A
file name is the block's address and size in hexadecimal, `AAAAAAAA.SSSSSSSS` (17 characters, a dot at
offset 8). Opening takes one of 40 handles, and a read copies whole sectors from the block, zero-filling
past its end. The source is `src/cri/mfci.c`. It builds with Sony EE GCC 2.96 at `-O2 -G0` as one whole
file (`cri_mfci` in `units.tsv`, its rows in `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)).

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x277da0` up to `0x278610` | the LSC module's code ends before it; the PL2ENC module starts at `0x278610` with its own lock wrappers |
| strings | `0x4f0c50` up to `0x4f0f08` | the version string, then the `mfCi` messages in code order |
| data | `0x4b0370` to the message buffer at `0x4b0ca8` | the build-string pointer, the error callback and its context, the 40 handles (56 bytes each, at `0x4b03e8`) and the message buffer |

The function at `0x277dd0` reads the build-string pointer and discards it, the shape of an approved
`volatile` read ([source approvals](source-approvals.md#build-string-reads)). It has no row, so it has no
source and links from the retail image between the file's members.

## Layout

A handle (`MfCiFile`) holds an in-use byte, a state byte (0 idle, 1 done, 2 reading), the sector size
(2048 at open), the file size, the size in sectors, the position in sectors, the bytes moved by the last
read, the sectors it requested, the name (20 bytes), and the byte offset and length of the read in
progress.

## Open questions

- The functions have no names from strings beyond the `mfCi` names the messages give (`mfCiOpen`,
  `mfCiOpenEntry`, `mfCiReqRd`). The handle fields are named from use.
- Opening by entry number (`mfCiOpenEntry`) checks the number and the mode but never stores the entry, so
  the handle's name is whatever the previous user left.
