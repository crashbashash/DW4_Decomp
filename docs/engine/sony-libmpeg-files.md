# libmpeg's files from the output path to the default handlers

libmpeg 2.8.0 (`0x1034e0..0x10a468`) is not public, but SDK 3.0.3's `libmpeg.a` is, and many of its functions are
byte-identical to DW4's. The 3.0.3 members (`alalc.o`, `csc.o`, `defhandler.o`, `error.o`, `ext.o`, `mpeg.o`,
`output.o`) name the functions; the 2.8.0 file boundaries come from DW4's own strings and data, since 2.8.0 groups
some functions differently (its `_decPicture` and `_updateRefImage` sit next to the output code, its `_sendDataToIPU`
after the error functions). The shared types are in `include/dw4/sony/libmpeg.h`: the public `sceMpeg`, the callback
records, and `_sceMpegDecoder`, the state `sceMpeg.sys` points at. Every file is a whole-file unit built with
`ee-gcc-2.9-as210` (`-O2 -G0 -ffunction-sections`) that defines its own data and strings.

## Files

| File | Extent | Evidence |
|---|---|---|
| `output.c` | `0x107ba8..0x108340` | its string `Too small buffer size for %dx%d picture` follows `_decPicture`'s strings; `_outputFrame` reads its `.data` table `_fieldCounts` (`0x481d00`, the 64 bytes of 3.0.3 `output.o`'s `.data`); `_cpr8` is 3.0.3 `output.o`'s |
| `csc.c` | `0x108340..0x108cc8` | `_doCSC2`'s `CSC handler error` is 3.0.3 `csc.o`'s only string; `_ch3dmaCSC`, `_doCSC2` and `_ch4dma` are byte-identical to that member; `_dmaRefImage` and `_sprClear` share the file's scratchpad-and-DMA code and `.bss` (`0x555080`, 512 bytes) |
| `mpeg.c` | `0x108cc8..0x109ac8` | its `.rodata` (`0x4d21c0..0x4d22e4`) runs from `The size of work area is too small` through `the second field is missing` in code order, with `_getpic`'s jump table at `0x4d22b0`; the jump table makes the section 16-byte aligned, which puts its start at `0x4d21c0` with `sceMpegCreate`'s string first, so the allocator (3.0.3's separate `alalc.o`) and the decode loop are in the same file as the public calls |
| `error.c` | `0x109ac8..0x109b68` | `_ErrMessage` and `_sceMpegError` are 3.0.3 `error.o`'s, `_ErrMessage` first; its string `[MPEG ERROR]%s\n` |
| `sendipu.c` | `0x109b68..0x109c68` | `_sendDataToIPU`, which sits between `error.c` and `sequence.c` and no neighbour's strings or data place it in either; it is one function and its own file |
| `sequence.c` | `0x109c68..0x10a418` | its strings, `vertical size > 2800` through `_pictureTemporalScalableExtension is not supported`, in code order; the default quantiser matrices at `0x481d40`; the four one-line extension handlers are 3.0.3 `ext.o`'s; `_initSeq` and `_setFieldPointers` |
| `defhandler.c` | `0x10a418..0x10a468` | both functions are 3.0.3 `defhandler.o`'s, the whole member |

* `output.c` turns a decoded picture into the stream's output: `_pictureTimeStamp` works out the picture's pts
  (from the stream, or the last pts plus the default gap for each displayed field, or once the pts set by
  `_sceMpegSetPtm`) and its flags word, `_outputFrame` and `_outputFieldPair` fill `sceMpeg`'s pts/dts/flags (a
  field pair fills the `2nd` set too), and the picture goes to the image buffer through `_cscStoreImage` (RGB32,
  through the IPU) or `_cpr8` (raw 8-bit, copied a macroblock column at a time through the scratchpad). The
  flags word is `picture_structure << 3 | picture_coding_type`: the coding type in bits 0-2 and the structure in
  bits 3-4, as 3.0.3 has it. `_fieldCounts` is indexed by the flags' repeat_first_field, top_field_first,
  progressive_frame and progressive_sequence bits.
* `csc.c` holds the transfers around the IPU and the scratchpad: `_sprClear`, `_dmaRefImage` (a source-chain
  transfer that pulls each prediction's reference blocks into the scratchpad as two 48-quadword pieces; called
  from the macroblock decoder), `_doCSC` (one conversion, running the background callback while it waits),
  `_doCSC2` (the long conversion, whose first chunk's size is set up before the wait), the channel-3 and
  channel-4 interrupt handlers that feed long conversions in chunks, and `_cscStoreImage`.
* `mpeg.c` is the public interface. `sceMpegCreate` lays `_sceMpegDecoder` out at the start of the work area,
  hands the rest to the bump allocator (`_sceMpegAlalc*`), sets the default DMA callbacks and points each picture
  structure's slots at the nine pictures that follow the decoder. `_getpic`, behind the `sceMpegGetPicture*` calls,
  reads headers until a picture and decodes or skips it through `_decodeOrSkipFrame`/`_decodeOrSkipField`
  against the per-type limits `sceMpegSetDecodeMode` sets, until a picture is output, the stream ends or the abort
  flag `sceMpegGetPictureAbort` sets is seen. `sceMpegAddCallback` stores the caller's `$gp` with the callback
  (`GetGp()` from `include/dw4/support/eekernel_gp.h`), and `_sceMpegDispatchMpegCallback` sets it with `SetGp()` around
  the call and restores the caller's afterwards.
* `error.c` sends an error to the stream's `sceMpegCbError` callback when one is registered, else prints it.
* `sendipu.c` feeds a bitstream chunk to the IPU through channel 4 with a chain of tags in
  `_sceMpegDecoder`'s `ipu_tags` array (at offset 2176, 16-byte aligned inside it): one REF tag per transfer,
  at most `0xFFF40` bytes each, REFE on the last. The tag's address word is computed before its id.
* `sequence.c` parses sequence_header and the sequence extensions, and loads the quantiser matrices into the IPU.
  `sequence_extension` marks the stream MPEG-2 and takes the IPU out of MPEG-1 mode. `_initSeq` sets the
  MPEG-1 defaults (progressive sequence, 4:2:0, progressive frame, frame picture, frame-only prediction and DCT,
  matrix coefficients 5), works out the macroblock size, and when the picture size changes lays the three frame
  buffers out in the allocator and sizes the nine pictures; `_setFieldPointers` points each picture's base at
  its buffer through the uncached alias, the bottom-field pictures half a frame in.

## Shapes the bytes require

* `_sceMpegDispatchMpegCallback`'s `$gp` restore is a single `move $28`, which `SetGp()` (two moves) cannot give, so the restore
  is its own `asm` statement, without a `"memory"` clobber (the clobber is inert there).
* `_setFieldPointers` forms the uncached alias with an inline helper rather than a macro; with the macro the
  three `* 384` multiplies are merged, and retail has them separate.
* `_doCSC2`'s `qwc` local keeps the first chunk's size set up before `AddDmacHandler2`; `_dmaRefImage`
  computes the right-hand block's address before the REF/REFE test and initialises `intr` at its declaration,
  which fixes the tag pointer's register. Both carry a note at the line.
* The hardware-register macros in `csc.c` and `sendipu.c` are `volatile` as Sony's `eeregs.h` declares them
  ([source approvals](source-approvals.md#sony-hardware-registers)); a `sync` in `_sendDataToIPU` and
  `_dmaRefImage` needs no row.

## Open questions

* `sceMpegDispCenterOffY` returns the same address as `sceMpegDispCenterOffX`, the start of the six center offsets.
* `sceMpegCreate` allocates 2048 bytes of the work area into `_sceMpegDecoder`'s `spare_buffer` and clears the word
  after it (`spare`); no libmpeg function reads either, so their purpose is unknown.
* `_dmaRefImage` and `_sprClear` are called from the macroblock decoder in `mpc.c`; they sit with the conversion
  code in `csc.c` because of their DMA work, but nothing in the strings or data separates that from the end of
  `output.c`.
* `_sendDataToIPU` is the one function between `error.c` and `sequence.c`; no 3.0.3 member holds it next to
  either, so a separate file is a layout choice rather than an observed boundary.
