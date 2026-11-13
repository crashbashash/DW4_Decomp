# libmpeg's files from the output path to the default handlers

libmpeg 2.8.0 (`0x1034e0..0x10a468`) is not public, but SDK 3.0.3's `libmpeg.a` is, and many of its functions are
byte-identical to DW4's. The 3.0.3 members (`alalc.o`, `csc.o`, `defhandler.o`, `error.o`, `ext.o`, `mpeg.o`,
`output.o`) name the functions; the 2.8.0 file boundaries come from DW4's own strings and data, since 2.8.0 groups
some functions differently (its `_decPicture` and `_updateRefImage` sit next to the output code, its `_sendDataToIPU`
after the error functions). The shared types are in `include/dw4/sony/libmpeg.h`: the public `sceMpeg`, the callback
records, and `_sceMpegDecoder`, the state `sceMpeg.sys` points at.

## Files

| File | Extent | Evidence |
|---|---|---|
| `output.c` | `0x107ba8..0x108340` | its string `Too small buffer size for %dx%d picture` follows `_decPicture`'s strings; `_outputFrame` reads its `.data` table `_fieldCounts` (`0x481d00`, the 64 bytes of 3.0.3 `output.o`'s `.data`); `_cpr8` is 3.0.3 `output.o`'s |
| `csc.c` | `0x108340..0x108cc8` | `_doCSC2`'s `CSC handler error` is 3.0.3 `csc.o`'s only string; `_ch3dmaCSC`, `_doCSC2` and `_ch4dma` are byte-identical to that member |
| `mpeg.c` | `0x108cc8..0x109ac8` | its `.rodata` (`0x4d21c0..0x4d22e4`) runs from `The size of work area is too small` through `the second field is missing` in code order, with `_getpic`'s jump table at `0x4d22b0`; the jump table makes the section 16-byte aligned, which puts its start at `0x4d21c0` with `sceMpegCreate`'s string first, so the allocator (3.0.3's separate `alalc.o`) and the decode loop are in the same file as the public calls |
| `error.c` | `0x109ac8..0x109b68` | `_ErrMessage` and `_sceMpegError` are 3.0.3 `error.o`'s, `_ErrMessage` first; its string `[MPEG ERROR]%s\n` |
| `sequence.c` | `0x109c68..0x10a418` | its strings, `vertical size > 2800` through `_pictureTemporalScalableExtension is not supported`, in code order; the default quantiser matrices at `0x481d40`; the four one-line extension handlers are 3.0.3 `ext.o`'s |
| `defhandler.c` | `0x10a418..0x10a468` | both functions are 3.0.3 `defhandler.o`'s, the whole member |

* `output.c` turns a decoded picture into the stream's output: `_pictureTimeStamp` works out the picture's pts
  (from the stream, or the last pts plus the default gap for each displayed field, or once the pts set by
  `_sceMpegSetPtm`) and its flags word, `_outputFrame` and `_outputFieldPair` fill `sceMpeg`'s pts/dts/flags (a
  field pair fills the `2nd` set too), and the picture goes to the image buffer through `_cscStoreImage` (RGB32,
  through the IPU) or `_cpr8` (raw 8-bit, copied a macroblock column at a time through the scratchpad).
  `_fieldCounts` is indexed by the flags' repeat_first_field, top_field_first, progressive_frame and
  progressive_sequence bits.
* `csc.c` holds the IPU-to-memory transfers: `_sprClear`, `_doCSC` (one conversion, running the background
  callback while it waits) and the channel-3 and channel-4 interrupt handlers that feed long conversions in chunks.
* `mpeg.c` is the public interface. `sceMpegCreate` lays `_sceMpegDecoder` out at the start of the work area,
  hands the rest to the bump allocator (`_sceMpegAlalc*`), sets the default DMA callbacks and points each picture
  structure's slots at the nine pictures that follow the decoder. `_getpic`, behind the `sceMpegGetPicture*` calls,
  reads headers until a picture and decodes or skips it through `_decodeOrSkipFrame`/`_decodeOrSkipField`
  against the per-type limits `sceMpegSetDecodeMode` sets, until a picture is output, the stream ends or the abort
  flag `sceMpegGetPictureAbort` sets is seen. `sceMpegAddCallback` stores the caller's `$gp` with the callback
  (`GetGp()` from `include/dw4/eekernel_gp.h`), and the dispatch restores it around the call.
* `error.c` sends an error to the stream's `sceMpegCbError` callback when one is registered, else prints it.
* `sequence.c` parses sequence_header and the sequence extensions, and loads the quantiser matrices into the IPU.
  `sequence_extension` marks the stream MPEG-2 and takes the IPU out of MPEG-1 mode.

## Open questions

* `_dmaRefImage`, `_doCSC2` and `_cscStoreImage` (`csc.c`), `_initSeq` and `_setFieldPointers` (`sequence.c`)
  have no C yet and link from retail.
* `_sceMpegDispatchMpegCallback` (`mpeg.c`) has no source: it sets the callback's `$gp` with `SetGp()`, whose
  `"memory"` clobber explains its second read of the record's type, but it restores the caller's `$gp` with a
  single `move`, which `SetGp()` (two moves) cannot give and C cannot write.
* `sceMpegDispCenterOffY` returns the same address as `sceMpegDispCenterOffX`, the start of the six center offsets.
* `sceMpegCreate` allocates 2048 bytes of the work area into `_sceMpegDecoder`'s `spare_buffer` and clears the word
  after it (`spare`); no libmpeg function reads either, so their purpose is unknown.
* `_sendDataToIPU` (`0x109b68`) has no C; nothing places it in `error.c` or `sequence.c`, so it keeps its own row.
* `_dmaRefImage` and `_sprClear` are called from the macroblock decoder; they sit with the conversion code, but
  nothing but their DMA work places them in `csc.c` rather than at the end of `output.c`.
