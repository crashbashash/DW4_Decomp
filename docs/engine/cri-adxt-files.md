# CRI ADXT-side files

Six CRI ADX files between ADXF and the ADX-to-PS2RNA wrappers, ADXPS2 among them, each compiled as one whole file
with Sony EE GCC 2.96 at `-O2 -G0` (their rows in `units.tsv` and `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)).

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/adxhdr.c` | `cri_adxhdr` | `0x262a30` up to `0x2631c8` | ADX header encode and decode (`ADXT_GetHdrInfo` messages) | ADXF's data and strings end before it; its pool is `(c)CRI` and the three `ADXT_GetHdrInfo` messages, up to `0x4ee080` |
| `src/cri/adxtinit.c` | `cri_adxtinit` | `0x2631c8` up to `0x263748` | ADXT init and finish, the object table at `0x49c8f8` | the `ADXT/PS2EE Ver.9.31s281` build string at `0x4ee080`; its data `0x49c8d8` up to `0x49d978` |
| `src/cri/adxtsml.c` | `cri_adxtsml` | `0x263748` up to `0x263b80` | file entries and seamless playback (`ADXT_EntryFnameRange`, `ADXT_EntryAfs`, `ADXT_StartSeamless`, ...) | its messages `0x4ee0d0` up to `0x4ee2a0`; ADXPS2's build string follows |
| `src/cri/adxps2.c` | `cri_adxps2` | `0x263b80` up to `0x265868` | ADXPS2: the ADX manager threads (ADXM), their locks, V-sync and server callbacks | its build-string pointer at `0x49d980` points to `ADXPS2 Ver.2.57`; its messages run to `0x4ee378`; its data `0x49d980` up to `0x4a52bc` with the thread stacks |
| `src/cri/adxmsg.c` | `cri_adxmsg` | `0x265868` up to `0x265a20` | the message level and print helpers | its own word at `0x4a52c0`; no strings |
| `src/cri/adxrna.c` | `cri_adxrna` | `0x265a20` up to `0x265f28` | ADX wrappers onto PS2RNA | every function calls PS2RNA; its one message, `ADXRNA_GetStat: not implemented`, follows ADXPS2's pool |

## Open questions

- `0x263548`, whose buffers (`0x49d538`, `0x49d938`) lie between the ADXT table and ADXPS2's data, is placed
  in the init file on that layout alone.
- The message helpers could belong to ADXPS2 or ADXRNA: they have no strings or pool of their own to place
  them.
- `ADXT_EntryAfs` (`0x2637d8`) has no source: the best draft differs only in which of two saved registers
  holds the AFS handle and which the file id. `ADXT_Init` (`0x2632c0`) declares its build-string word
  and its tick count `volatile`, as the owner approved ([build-string stores](source-approvals.md#build-string-stores),
  [ADXT tick count](source-approvals.md#adxt-ready-count)); the stream file reads the count plain.
- ADXPS2 declares its thread words `volatile` at file scope. The functions that use them either have owner
  approval ([source approvals](source-approvals.md#adxm-thread-ids)) or stay `unapproved`; its init and V-sync
  functions (`0x264910`, `0x2650a8`, `0x2654d8`) need words `volatile` that matched functions read plain, so
  they have no source and link from the retail image.
