# CRI MPS and MPV front files

The Sofdec player demultiplexes a movie with CRI MPS (`CRI MPS/PS2EE Ver.1.924`, string at `0x4f2998`) and
decodes its video headers with CRI MPV (`CRI MPV/PS2EE Ver.1.933`, string at `0x4f2a00`). The code from
`0x28b180` up to `0x290b28` is six whole files, each built with Sony EE GCC 2.96 at `-O2 -G0 -ffunction-sections`
(`cri_<name>` in `units.tsv`, rows in `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).
The file names are best guesses from what each file does; the MPV main file (`MPV_GetVersionStr` and `MPV_Init`
onwards, from `0x290b28`) is described with the rest of the MPV library.

| file | range | what it is | evidence |
| --- | --- | --- | --- |
| `src/cri/mpsutl.c` | `0x28b180` up to `0x28b608` | unrolled byte and word copies and fills, and an empty init/finish pair | `MPS_Init` calls `mpsutl_Init` and `MPS_Finish` calls `mpsutl_Finish`, as with the demultiplexer's pair; no MPS handle use |
| `src/cri/mpsdmx.c` | `0x28b608` up to `0x28d4a8` | the demultiplexer: callback setters, `MPS_DecodeChunk`, the pack, system-header and PES parsers, start-code classification and search | codes `0xFF0203xx`; ends with the empty pair `mpsdmx_Init`/`mpsdmx_Finish` that `MPS_Init` calls |
| `src/cri/mps.c` | `0x28d4a8` up to `0x28dc78` | the library: header queries, version, init and finish, error callbacks, handle create and destroy | codes `0xFF0201xx` and `0xFF0202xx`; the only users of the version string, the work pointer `mps_work` (`.data` `0x4bcc68`) and `mps_curhn` (`.bss` `0x573f0c`); the getters have no init hook of their own, so they sit with the library rather than in a file of their own |
| `src/cri/startcode.c` | `0x28dc78` up to `0x28ea10` | MPEG video start-code classifier and scanners | [CRI MPEG start-code scanner](cri-startcode.md) |
| `src/cri/mpvapi.c` | `0x28ea10` up to `0x28f098` | MPV error object and callbacks, delimiter searches over a buffer or a stream joint, the picture and VBV queries | the library error object `mpv_err_global` (`.data` `0x4bccb8`, right after the start-code table); ends with the empty `mpvapi_Init` that `MPV_Init` calls next to `mpv_InitLibErr` |
| `src/cri/mpvhdr.c` | `0x28f098` up to `0x290b28` | header decoding through a stream joint: sequence, group and picture headers, user data with the CRI `IDCPREC`/`STCCODE` tags, start-code skipping | its `.rodata` tags `0x4f29f0`/`0x4f29f8` come before the MPV version string, so the file ends before the version file; ends with the two `return 0` stubs, as `mpsdmx.c` ends with its hooks |

`mpsutl.c`, `mpsdmx.c` and `mps.c` share `include/dw4/cri/mps.h` (the 256-byte `MpsHn`, the `MpsWork` area
`MPS_Init` is given, and the header records). The MPV files use `include/dw4/cri/mpv.h`.

## Open questions

- The split of the MPS getters (`MPS_GetPackHd` up to `MPS_GetPesInf`) from the demultiplexer and the split
  between `mpvapi.c` and `mpvhdr.c` rest on the init hooks and the error-code groups, not on data.
- `mpsdmx_ParsePack`, `mpsdmx_ParseSysHd` and `mpsdmx_ParsePes` have no source: large bit-field parsers that
  read the stream a byte at a time through an expanded bit reader.
- `MPS_Init` stores the version pointer through a `volatile`-looking store that has no approval; it links from
  retail. `mps_ResetSysHd` matches only under MWCC (its stores come out in another order under EE GCC) and also
  links from retail.
- `MPV_DecHdrSj`, `mpv_DecSeqHdr`, `mpv_DecSeqExt`, `mpv_DecPicHdr`, `mpv_DecGop` and `mpv_DecUsrDat` have no
  source; their names are guesses from their size and the start codes `MPV_DecHdrSj` dispatches on.
- The handle field pair at `MpsHn` +236 is set by `MPS_SetAuxFn` but no MPS code with source calls it.
