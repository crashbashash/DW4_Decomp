# CRI SFD files: the Sofdec player library

The CRI SFD library (`CRI SFD/PS2EE Ver.1.946` at `0x4f4d00`) is the core of the Sofdec movie player under
the MWSFD front end. Its functions check a handle with one routine and report numeric error codes
(`0xFF000xxx`) through another, so the files have almost no message strings; their boundaries come from the
error-code runs, the handle sub-objects each file works on, and their data and read-only data. Each builds with
Sony EE GCC 2.96 at `-O2 -G0` as one whole file each (`cri_<name>` in `units.tsv`, their rows in
`unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)). The file names are best
guesses from what each file does.

| file | range | what it is | evidence |
| --- | --- | --- | --- |
| `src/cri/sfadx.c` | `0x29b3a8` up to `0x29cee8` | the ADX audio handler: drives ADXT for a movie's audio | its handler table at `0x4f4b18` (14 entries in code order) and the data after it up to `(c)CRI` at `0x4f4b68`; codes `0xC03` to `0xC0A` |
| `src/cri/sfdusr.c` | `0x29cee8` up to `0x29d4a0` | the handler-interface wrappers and a second handler | codes `0x1A1` to `0x1A4`; the second handler table at `0x4f4b70` |
| `src/cri/sfdbuf.c` | `0x29d4a0` up to `0x29ece8` | the stream and buffer channels (116-byte entries at handle +4872) | its init and finish hooks are called from the library init and finish; codes `0x401` to `0x40c`; its bss at `0x57fab0` |
| `src/cri/sfmpv.c` | `0x2a2f30` up to `0x2a8b50` | the video (MPV) handler: plane layout, decode slots, picture and time-stamp handling, the handler entry points | its handler table follows the SFD build string; codes `0xF01` to `0xF31` and `0x181` to `0x189`; the bss block `0x5855b0` its init clears; the previous handler group ends with `0x2a2f20` |
| `src/cri/sfmpvps2.c` | `0x2a8b50` up to `0x2aa2f0` | the PS2 side of MPV: `sceMpeg`, IPU and DMA transfers, semaphores | its own data word `0x4beb10`, bss at `0x585630` and read-only data at `0x4f4e88`; code `0xF40`; called from the MPV handler |
| `src/cri/sfdply.c` | `0x2aa2f0` up to `0x2ac6d0` | the player handle: create, destroy, start, stop, pause, the server | codes `0x131` to `0x146` and `0x201` to `0x206`; the handle table at `0x4beadc` |
| `src/cri/sfdring.c` | `0x2ac6d0` up to `0x2acb30` | the 16-byte item rings of the stream table | every function works on the ring at entry +56 of the stream table; codes `0x165`, `0x421` |
| `src/cri/sfdrec.c` | `0x2acb30` up to `0x2ad8f8` | the 0xDD8-byte time record at handle +13864 | codes `0x151` to `0x15C` |
| `src/cri/sfdcond.c` | `0x2ad8f8` up to `0x2ae010` | the handle's condition arrays and their defaults | codes `0x111` to `0x11C`; the default table at `0x4be8d8` |
| `src/cri/sftim.c` | `0x2ae010` up to `0x2afc08` | the time block at handle +0xD28 and the time-code conversions | its init and finish are called from the library init; the frame-rate and converter tables at `0x4f5060` and `0x4f5090` |
| `src/cri/sfdtrn.c` | `0x2afc08` up to `0x2b0408` | the module table and the per-handle stream graph at handle +7976 | its first function is the library's second init; code `0x302` |
| `src/cri/sfdtst.c` | `0x2b0408` up to `0x2b0ed0` | the time-stamp debug object (`tst`) and its moving averages | its data `0x4beb40` up to `0x4beb54` and its read-only data `0x4f50d0` up to `0x4f5278` (the field-name header and its print format) |

`sfadx.c` and `sfdbuf.c` share `include/dw4/cri/sfdsj.h`; `sfmpv.c` and `sfmpvps2.c` share `include/dw4/cri/sfmpv.h`; `sfdply.c` and `sfdring.c` share
`include/dw4/cri/sfdply.h`. The other files declare their types themselves.

## Types

- The ADX handler's sub-context at handle +8188 is declared `int` and cast to its struct at each use, as the
  owner approved for the cvFs, HTCI, DVCI and SFX pointers on the same condition
  ([CRI cvFs](cri-cvfs.md#integer-typed-slots)).
- A buffer channel's field at +20 is typed as a stream pointer, and memory-kind channels keep a byte size
  there through a cast; its position is cast to and from `int`. The owner approved landing it this way.
  The original most likely declared the entry body as a union of channel kinds.
- The MPV link at player +8120 and the decoder handle are `void *`: the function that clears a slot's outputs
  matches only when its `void **` out-parameters and the link share an alias set.
- The record file's time block and the time file's block are the same handle memory seen by two files; each
  file declares the fields it uses.

## Open questions

- The same handle is declared separately in several files (`SfdPly`, `SfdAdxHn`, `SfdUsrHn`, `SfdBufHn`), and
  the interface at +8460 has different slot signatures in the ADX handler and the wrappers; one shared
  declaration is a readability task.
- Where the ADX handler file starts rests on the data order alone.
- Whether `0x2a8b50` up to `0x2a96d0` (the IPU and DMA helpers, called only from later functions) is a file of its
  own in front of the MPV PS2 file.
- The ring file's split from the player file, and the one-line wrapper at `0x2ad8f8` (record file or condition
  file), have no evidence in the code either way.
- Some time-block counters at handle +0xD28 +680 up to +744 are updated from the V-sync path, and several
  functions that use them read them as `volatile` accesses would, but a `volatile` on the whole block breaks
  other functions. Which fields the original declared `volatile` is open; those functions have no source and
  link from the retail image.
- The free-slot claim at `0x2a85a0` reads a slot's state and reference count in one 64-bit load. No plain C
  with the slot's shared `int` fields reproduces that, so it has no source.
- Medium confidence: `SFTIM_Init`, `SFTIM_Finish`, `SFTIM_InitHn`, `SFTIM_InitTtu` and `SFTIM_InitTcode` (`0x2ae010`, `0x2ae020`,
  `0x2ae028`, `0x2ae248`, `0x2ae290`) come from the order of the Persona 3 FES PlayStation 2 symbol list (provenance not stated) and the
  GameCube library's map (`sfd_tim.c`), which has the same five in the same sequence; the bodies of `SFTIM_Init` agree with the
  GameCube source. `SFD_SetUsrTimeFn`, `SFD_SetExtClockFn` and `SFD_UpdateTime` (`0x2aed78`, `0x2aee00`, `0x2aeef0`) come from the same
  list: eight consecutive function sizes from `0x2aed60` match.
