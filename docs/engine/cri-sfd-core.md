# CRI SFD core files: sync queues, stream analysis, header, library core, supply and MPS handlers

These six files sit in front of the [CRI SFD player files](cri-sfd-files.md), from `0x29ece8` (after
`sfdbuf.c`) up to `0x2a2f30` (where `sfmpv.c` starts). Like the rest of the library they build with Sony EE GCC
2.96 at `-O2 -G0 -ffunction-sections`, one whole file each (`cri_<name>` in `units.tsv`, their rows in
`unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)). The file names are best guesses
from what each file does. Every SFD file starts with its own entry points, so a file's init and finish hooks, or
its public API, begin it.

| file | range | what it is | evidence |
| --- | --- | --- | --- |
| `src/cri/sfdsync.c` | `0x29ece8` up to `0x29f160` | the link-stream switch (`SFD_SetLnkStm`, condition 49) and the queues on the time block the audio and video handlers share: the running total with its 32 past values (`sfsync_AddTotal`, `SFD_GetSyncTime`) and the 32-entry time-stamp queue (`sfsync_PushPts`, `sfsync_PopPts`) | codes `0x161` and `0x162`; no data of its own; every function after the switch works on handle +3368 +352 up to +636 |
| `src/cri/sfdana.c` | `0x29f160` up to `0x29fe80` | stream analysis for the MWSFD header query (`SFD_GetHdrInf`): system stream (pack spacing and mux rate), CRI header, ADX, MPEG audio and MPEG video detection | its read-only data runs from `0x4f4ba8` (the video frame rates) through the MPEG audio tables to `0x4f4d00`, right after `sfdusr.c`'s handler table and up to the SFD build string; its bss `0x57fab8` (the 2048-byte copy buffer) and `0x5802b8` (one header record); its data word `0x4be8c0` (the last MPEG audio header) |
| `src/cri/sfdhdr.c` | `0x29fe80` up to `0x2a0988` | the CRI header in private stream 2: the SFH init and finish hooks, reading a header through SFH into the handle's header record at +120, copying it to and from the work record, the stream-version query | starts with its init and finish hooks, called from the library's module init and finish (`sfd_InitModules`, `sfd_FinishModules`); its bss `0x580b50` (the SFH handle pool) follows `sfdana.c`'s header record; every function works on the 2196-byte header record |
| `src/cri/sfdlib.c` | `0x2a0988` up to `0x2a0ea0` | the library core: version string, init and finish, the error blocks (`sfd_ReportError`, `SFD_SetErrFn`, `SFD_GetErrInf`), the handle check, the lock | starts with `SFD_GetVersionStr`; the SFD build string `0x4f4d00` is its read-only data; codes `0x101`, `0x102`; the library state `0x4be8d8` (548 bytes, `sfd_lib`) and the current handle `0x4be8d0` |
| `src/cri/sfdsup.c` | `0x2a0ea0` up to `0x2a0f98` | the supply module's handler: the application writes the stream into the module's output channel itself, so the handler answers the write requests and refuses the read ones | its 14 functions are the 14 entries of the handler table at `0x4f4d50`, in table order; code `0x501` |
| `src/cri/sfmps.c` | `0x2a0f98` up to `0x2a2f30` | the MPS (system stream) handler: the stream-object API, demultiplexing the input channel into the video, audio and user-data channels, the picture record, and the 14 handler entries | its handler table at `0x4f4d88` and the PES packet table at `0x4f4dc0` (the next table, `0x4f4dd0`, is `sfmpv.c`'s); codes `0x171` and `0xD01` up to `0xD0E`; its parameter block at handle +8592, reached through the MPS slot of the stream graph (+8052) |

`src/cri/sfdana.c` and `src/cri/sfdhdr.c` share the header record (`SfdHdrInf`), and `src/cri/sfdhdr.c` and
`src/cri/sfmps.c` share the work record (`SfdWork`): those types, the error block, the stream-graph slots and the
handle as these six files see it are in `include/dw4/cri/sfdhn.h`. The MPS types come from `include/dw4/cri/mps.h`.

## Types

- `SfdHandle` declares only the fields these files use; the other files of the library declare their own views
  of the same handle (`SfdPly`, `SfdHn`, `SfdBufHn`, `SfdPlayer`), as [CRI SFD files](cri-sfd-files.md#open-questions)
  notes.
- The library state `sfd_lib` (`SfdLibInf`) holds the default conditions, the init parameters, the system status
  (`sfply_sys_stat` is its field at +408), the library error block, the time, buffer and stream-graph blocks of
  `sftim.c`, `sfdbuf.c` and `sfdtrn.c`, and the handle table (`sfply_handles`, +516).
- Conditions 75 and 76 hold the application's header callback and its object, 85 and 86 the system-header
  callback and its object: `SFD_GetCond` returns them as `int` and the files cast them back.
- The demultiplexer's system-header bounds (`MpsSysHd.audioBound`, `.videoBound`) decide when an output's play
  condition is cleared and whether a split video packet is passed on.

## Open questions

- Functions without source, linking from retail: `SFD_GetSyncTime` and `SFD_Init` (a value kept in a register
  before the store that no spelling tried reproduces), `sfana_ChkMpsAudio` (the loop's test placed after its body),
  `sfana_ChkM2v` (register choice for the unpacked sequence-header bytes), `sfhdr_ChkPrv2` and `sfhdr_SetHdr`
  (register choice), `sfmps_IsInFull` (the condition array's address is kept in a register), and
  `sfmps_DemuxChunk`, `sfmps_PutPes`, `sfmps_PutAudio`, `sfmps_PutVideo`, `sfmps_ChkEnd`, which have no draft yet.
- `SFH_IsExistStmId` returns nothing in `sfh.c`, yet `sfhdr_FindStm` tests its result; this file declares it `int`.
- The supply and MPS handlers' entries 5 to 8 are named after the ADX handler's (prepare, start, stop, pause) and
  entry 13 (`*_LoadRec`) after what the MPS handler does there; the other handlers have not been checked against
  that reading.
- `sfbuf_GetWriteStat`, `sfbuf_GetReadStat` and `sfbuf_AddWriteLen` return the buffer call's result and the last
  takes the tail length: `sfdbuf.c` declares them `void` with three parameters.
- What the MPS parameter block's words at +36 up to +48 and +344, and the video settings' word at +28, hold.
- Whether the supply handler shares `sfdlib.c`'s file: nothing in the code tells; its own error code and its own
  table put it in a file of its own here.
