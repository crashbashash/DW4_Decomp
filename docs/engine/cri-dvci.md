# CRI DVCI: the disc-file device

DVCI (`DVCI/PS2EE Ver.2.71` at `0x4f0180`) is the cvFs device for files on the disc: the twin of
[HTCI](cri-htci.md), reading through `sceCd` and SRD, with a cache of files located in advance from a file
list. The source is `src/cri/dvci.c`. It builds with Sony EE GCC 2.96 at `-O2 -G0` as one whole file
(`cri_dvci` in `units.tsv`, its rows in `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)).

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x273988` up to `0x2752f8` | the file opens with the function that reads the build-string pointer; DTX ends before it; five small SRD wrappers of unknown file follow, then HTCI |
| read-only data | `0x4f01c0` up to `0x4f0590` | a jump table, then the module's messages in code order; HTCI's build string follows |
| data | `0x4aa740` up to `0x4ab5d8` | the build-string pointer, the handles and the file-list table at `0x4ab430`; HTCI's data follows |

Like HTCI, the source writes its messages as string literals: one function copies the literal `"\\"` inline,
which only a literal gives, so the whole pool is written that way and links from the one object.

## Integer-typed list pointer

The file-list table's pointer to its entries is declared `int` and cast to the entry type at each use, as the
owner approved for HTCI and then for DVCI on the same condition ([CRI cvFs](cri-cvfs.md#integer-typed-slots)):
one declaration, every function that touches it matching, none needing the pointer form. With a pointer type
one function's load and test come out in another order.

## Open questions

- The functions are named from use beyond the `dvCi` names the messages give, and from the Street Fighter III
  3rd Strike libadxe ([3s-decomp](https://github.com/crowded-street/3s-decomp)) and the 2002 SDK's `dvci_sub.o`
  ([recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)). `dvCiLoadFcache` is both sources'
  name; its message still says `dvCiLoadDirInfo`, as the 3rd Strike body's does, so the text is older than the
  name. Medium: `dvCiSetFcache` (the in-memory list twin, also in the CRI names the Persona 4 decompilation
  matched in unstripped PS2 builds, [Raikaru/Persona4-Decompilation](https://github.com/Raikaru/Persona4-Decompilation)),
  `dvci_get_fstate` (3rd Strike's body plus a branch for sector names) and `dvci_analysis_flist` (3rd Strike's
  `analysis_flist`, prefixed like `dvci_conv_cmp` because HTCI has its own). Medium from behaviour:
  `dvci_is_lsn_fname` (a 17-character name with a dot at 8; alternative `dvci_is_sector_fname`) and
  `dvci_get_lsn_fname`, which reads the LSN and sector count from such a name.
- Four helpers that `0x2744f8` calls are defined old-style and called without arguments, as in HTCI: retail
  never loads their argument register at those calls.
- The five 20-byte SRD wrappers at `0x2752f8` up to `0x27536c` are called from game code and reference
  nothing that places them. 3rd Strike's order makes the first, `dvCiSetSeekPos`, the end of `dvci_sub` and
  the other four (`htCiSetFileSystem64`, `htCiGetFileSystem64`, `htCiSetLockHost`, `htCiGetLockHost`, medium
  by that order and their SRD callees) the start of `htci`.
