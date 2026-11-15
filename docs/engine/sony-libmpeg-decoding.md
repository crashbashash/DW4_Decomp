# Sony libmpeg: macroblock, header and picture decoding

The first three libmpeg files (`0x1034e0..0x107ba4`) are whole-file units built with EE GCC 2.9-ee and the
2.10 assembler (`ee-gcc-2.9-as210`, `-O2 -G0 -ffunction-sections`). They share the decoder state
`_sceMpegDecoder` of `include/dw4/sony/libmpeg.h`. DW4's libmpeg is release 2.8.0, organised differently
from SDK 3.0.3's members (`mpc.o`, `ext.o`, `mpeg.o`, `output.o`, ...), so the files are placed by their
data and strings; 3.0.3's members only name the functions and confirm some groupings. Each file defines its
own data and strings.

## `src/sony/libmpeg/mpc.c` (`0x1034e0..0x106df4`)

Slice and macroblock decoding and the IPU bit reader. `_pictureData` decodes a picture's slices through
`_slice0`, which reads each slice header (`_sliceA0`), the macroblock address increments, the
macroblock modes and motion vectors (`_decMB0`, `_skipMB0`, `_motionVectors`, `_motionVector`,
`_dualPrimeVector`), starts the IPU's BDEC of the coefficients (`_waitBdec` waits for it), and places the
macroblock (`_motionCompensation`) while the previous one is colour-converted (`_doMC`). The bit reader
(`_ipuVdec`, `_ipuShowBits`, `_ipuFlushBits`, `_ipuGetBits`) issues VDEC/FDEC commands and caches
IPU_TOP; `_invalidatesBits` says which IPU commands make the cache stale. Every IPU wait polls the abort
flag and hands control to the stream's no-data callback every 5000 polls.

* Extent: its `.data` (`0x481c98..0x481d00`) follows libdma's directly: the two motion-compensation
  handler tables (`0x40` bytes, as 3.0.3 `mpc.o`'s `_rix`/`_ri0`) and `_invalidatesBits`; its strings run
  from `0x4d1ee0` ("Invalid modion type") to `0x4d20af` ("Invalid macroblock_type code: 0") in code
  order, as literals in the functions that print them. 3.0.3's `mpc.o` holds the same functions
  (`_motionVectors`, `_sceMpegWaitIpuIdle`, the bit reader's successors). The file ends where `ext.c`'s
  rodata table begins.
* `_getAllRefs` (with the helper `_getRef0`, 3.0.3's names) fetches the reference blocks of a macroblock into
  the scratchpad and `_doMC` runs the kernels over them. `_getRef0` fills the macroblock's luma fetch
  (`_sceMpegMcFetch`: the destination row in the work area, the starting column, the row count, the rows taken
  from the macroblock row below, the pitch, and the two quadword addresses the row is extracted from) and then
  its chroma fetch from the same coordinates halved.
* The kernels are the sixteen `_rix_*`/`_ri0_*` routines the `.data` tables point at (3.0.3's names, entry for
  entry: `_rix_` is the first table, `_ri0_` the second, and the three bits are the half-sample flags and
  the average flag) and the two reference-image copies (`_copyAddRefImage`, `_copyRefImage`) that `_doMC`
  tail-calls. DW4's 2.8.0 kernels have 3.0.3's instructions with the header loads reordered and registers
  renamed (fourteen pairs hold the same instructions in a different order, the two `_000` pairs also differ in
  registers), and its copies are an older, shorter version: sixteen bytes a loop where 3.0.3 does sixty-four,
  with the same `_maxval` clamp (four words of `0x00ff00ff` ending `_copyRefImage`, which the routine's own
  `jr ra` follows).
* These eighteen are C functions whose body is one `asm` statement, because Sony's `mpc.o` records them as
  compiled procedures (static, frame register 29, return register 31, no line records, in an included
  `mm.c`); the compiler supplies each one's return. They use `addi`, `qfsrv`, `mtsab`, `pextlb`/`pextub` and
  `pcpyld`, which no C spelling of this compiler reaches, and name their argument register directly. A
  routine that closes with a return of its own gets two (eight bytes more). `_copyRefImage` pads its
  `_maxval` to sixteen bytes with two `nop`s: under `-ffunction-sections` an `.align` counts from the
  function's own section and pads nothing. The anchor is
  [source approvals](source-approvals.md#sony-libmpeg-motion-compensation); the file's `_ipuWait*` and DMA
  registers are `volatile` as in Sony's `eeregs.h`, `_waitBdec`'s eight included, each of which changes the
  function when removed (a dropped enable store, hoisted poll reads, merged read-modify-writes).
* `_getRef0`'s chroma set-up is the one place the statement order was found by search: the half-vector, the
  row count, the column and the row each go through their own statement in an order that fixes which values
  the allocator spills (retail keeps seven values on the stack and `dec` in `t8`). The note is at the source.

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
  in `sequence.c` ([output to default handlers](sony-libmpeg-files.md)).

## `src/sony/libmpeg/picture.c` (`0x107790..0x107ba4`)

`_decPicture` decodes a picture into its frame or field slot, `_sceMpegOutputFrame` hands the due
picture to output, and `_updateRefImage` rotates the reference pictures.

* Extent: its strings ("odd number of field pictures", "unknown picture sutructure") follow
  `ext.c`'s at `0x4d2138`; output's file begins at `0x107ba8` with its own string at `0x4d2178`. The
  three functions are byte-identical to 3.0.3's `_decPicture`, `_sceMpegOutputFrame` and
  `_updateRefImage`, which 3.0.3 spreads over `mpeg.o` and `output.o`; only `0x1095c8`/`0x109730`
  call them.
* `_updateRefImage` (called with the picture type already set) clears the picture it will fill before it
  clears `ready`; in a B picture it points the decode slots at the output images and decides from the
  reference pictures' decoded flags whether the references are usable, in a reference picture it rotates
  the reference and previous images. The two clears fall in that order and the allocator's choice of
  register for the `picture` local follows from it.
* `_sceMpegPicture` has the coding type at offset 44 and the picture structure at 48; retail's stores in
  `_updateRefImage` fix the order.

## Open questions

* Whether `picture.c`'s three functions were their own file or the end of `ext.c` in 2.8.0: the
  strings run on without a gap either way. They are kept apart because no `ext` function calls them
  and 3.0.3 puts none of them in `ext.o`.
* The kernels' argument structure `_sceMpegMcFetch` and its member names are inferred from the offsets the
  kernels and `_getRef0` use (0 to 24); the asm names the argument register only, so Sony's type is not
  known. The two copy routines' parameter types are likewise read from their loads.
* Why `_getRef0`'s statement order is the one that matches: the chroma statements are written in the order a
  search found, and the source reason for that order, if there was one, is not known.
* Whether DW4's 2.8.0 kernels were edited by hand from 3.0.3's or 3.0.3's are the later edit of the same
  source cannot be told from the bytes; the register renames and header-load order are the only difference.
