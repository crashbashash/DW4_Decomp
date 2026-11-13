# Sony libmpeg: macroblock, header and picture decoding

The first three libmpeg files (`0x1034e0..0x107ba4`) are whole-file units built with EE GCC 2.9-ee and the
2.10 assembler (`ee-gcc-2.9-as210`, `-O2 -G0 -ffunction-sections`). They share the decoder state
`_sceMpegDecoder` of `include/dw4/sony/libmpeg.h`. DW4's libmpeg is release 2.8.0, organised differently
from SDK 3.0.3's members (`mpc.o`, `ext.o`, `mpeg.o`, `output.o`, ...), so the files are placed by their
data and strings; 3.0.3's members only name the functions and confirm some groupings.

## `src/sony/libmpeg/mpc.c` (`0x1034e0..0x106df4`)

Slice and macroblock decoding and the IPU bit reader. `_pictureData` decodes a picture's slices through
`_slice0`, which reads each slice header (`_sliceA0`), the macroblock address increments, the
macroblock modes and motion vectors (`_decMB0`, `_skipMB0`, `_motionVectors`, `_motionVector`,
`_dualPrimeVector`), starts the IPU's BDEC of the coefficients, and places the macroblock
(`_motionCompensation`) while the previous one is colour-converted (`_cscMacroblock`). The bit reader
(`_ipuVdec`, `_ipuShowBits`, `_ipuFlushBits`, `_ipuGetBits`) issues VDEC/FDEC commands and caches
IPU_TOP; `_invalidatesBits` says which IPU commands make the cache stale. Every IPU wait polls the abort
flag and hands control to the stream's no-data callback every 5000 polls.

* Extent: its `.data` (`0x481c98..0x481d00`) follows libdma's directly: the two motion-compensation
  handler tables (`0x40` bytes, as 3.0.3 `mpc.o`'s `_rix`/`_ri0`) and `_invalidatesBits`; its strings run
  from `0x4d1ee0` ("Invalid modion type") to `0x4d20af` ("Invalid macroblock_type code: 0") in code
  order. 3.0.3's `mpc.o` holds the same functions (`_motionVectors`, `_sceMpegWaitIpuIdle`, the bit
  reader's successors). The file ends where `ext.c`'s rodata table begins.
* `"Invalid modion type -- ignored(%d)"` is named (`invalidMotionTypeMessage`) rather than written as
  a literal: it is the file's first string, and the strings of the functions without source come
  between it and the rest.
* Without source, linking from retail: `_formPredictions` (`0x103730`), `FUN_00103e38`,
  `_cscMacroblock` (`0x104258`), `_waitBdec` (`0x105250`), and `FUN_00104478..FUN_001051c8`. The last
  group are the motion-compensation kernels the `.data` tables point at; they use 128-bit GPR
  `lq`/`sq`, `pnor`, `qfsrv` and `mtsab`, which this compiler does not emit: they look hand-written
  assembly.

## `src/sony/libmpeg/ext.c` (`0x106df8..0x107790`)

Start codes and the picture-level syntax: `_nextStartCode`, `_sliceHeader`, `_sceMpegNextHeader` (which
asks the stream's callback for the picture's time stamps), `_pictureHeader`, `_extensionAndUserData`,
`_groupOfPicturesHeader`, `_temporalOrder` and the picture extensions (`_quantMatrixExtension`, which
lets the IPU load the matrices with SETIQ, `_pictureDisplayExtension`, `_copyrightExtension`,
`_pictureCodingExtension`).

* Extent: its `.rodata` starts at `0x4d20b0` with `_extensionAndUserData`'s handler array (an
  initialised local, copied from the file's rodata), the same eleven handlers in the same order as
  3.0.3 `ext.o`'s; then the two "load_chroma" strings. The sequence-level handlers it names
  (`_sequenceExtension`, `_sequenceDisplayExtension`, `_sequenceScalableExtension`, `_unknownExtension`,
  `_pictureSpatialScalableExtension`, `_pictureTemporalScalableExtension`) sit at `0x10a218..0x10a414`,
  in a later file.

## `src/sony/libmpeg/picture.c` (`0x107790..0x107ba4`)

`_decPicture` decodes a picture into its frame or field slot, `_sceMpegOutputFrame` hands the due
picture to output, and `_updateRefImage` (no source yet) rotates the reference pictures.

* Extent: its strings ("odd number of field pictures", "unknown picture sutructure") follow
  `ext.c`'s at `0x4d2138`; output's file begins at `0x107ba8` with its own string at `0x4d2178`. The
  three functions are byte-identical to 3.0.3's `_decPicture`, `_sceMpegOutputFrame` and
  `_updateRefImage`, which 3.0.3 spreads over `mpeg.o` and `output.o`; only `0x1095c8`/`0x109730`
  call them.

## Open questions

* Whether `picture.c`'s three functions were their own file or the end of `ext.c` in 2.8.0: the
  strings run on without a gap either way. They are kept apart because no `ext` function calls them
  and 3.0.3 puts none of them in `ext.o`.
* `_formPredictions`, `FUN_00103e38`, `_cscMacroblock`, `_waitBdec` and `_updateRefImage` still lack C.
