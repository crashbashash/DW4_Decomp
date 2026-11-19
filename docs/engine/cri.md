# CRI middleware: what the game links and where it is documented

The game links CRI Middleware's PS2 libraries for audio and movie playback, all of them built by CRI with Sony
EE GCC 2.96 in October 2004. They sit in two blocks of the executable: **CRI ADX** (`0x25b248` up to `0x27ede0`:
ADX audio, the file-system layer under it, stream joints, the EE side of the IOP renderer) and **CRI Sofdec**
(`0x280b98` up to `0x2b5d50`: the sound driver's EE side, the MPEG-2 video and system-stream libraries, the SFD
player library and the MWSFD player on top). `config/SLUS-20836/regions.tsv` records both blocks; a few
Alchemy units sit in the gap between them ([module map](module-map.md)). The game reaches the middleware through
`igAdx` and `igCriMovieCodec` ([igCriMovieCodec](cri-movie-codec.md): the engine's movie codec over MWSFD and ADXT).
This page is the entry point; each topic below has its own document with extents, layouts, evidence and open
questions.

## What is linked

Every library stamps a build string (`<name>/PS2EE Ver.x.y Build:<date>`) into its data, and most carry
`Append: GCC2096 SCE2810`, the compiler stamp ([the compiler](#how-it-is-compiled)). The strings in the executable:

| library | role | version string | built |
| --- | --- | --- | --- |
| ADXT | ADX playback handle and server (ADXSJD, ADXB and ADXRNA underneath) | `ADXT/PS2EE Ver.9.31s281` | 6 Oct 2004 11:47:30 |
| ADXRT | the ADX runtime, read as a build string only | `ADXRT  Ver.2810` | 6 Oct 2004 11:47:31 |
| ADXPS2 | ADX manager threads (ADXM), V-sync and server callbacks | `ADXPS2 Ver.2.57` | 6 Oct 2004 11:47:32 |
| ADXF | AFS partitions and file handles | `ADXF/PS2EE Ver.7.18` | 6 Oct 2004 11:47:23 |
| ADXENC | the ADX encoder (also `ADXENC.DLL Ver.1.09`) | `ADXENC/PS2EE Ver.1.09` | 6 Oct 2004 11:47:27 |
| SKG | the ADX key generator | `SKG/PS2EE Ver.0.64` | 6 Oct 2004 11:47:26 |
| PL2ENC | Dolby Pro Logic II encoder | `PL2ENC Ver.1.01` | 6 Oct 2004 11:47:17 |
| PS2RNA | the ADX renderer whose voices play on the IOP | `PS2RNA Ver.1.30` | 6 Oct 2004 11:47:43 |
| SJ, SJRMT, SJX | stream joints, on the EE and across to the IOP | `SJ/PS2EE Ver.6.28`, `SJRMT Ver.1.03`, `SJX Ver.1.08` | 6 Oct 2004 11:47:20 to 11:47:21 |
| SVM | the server manager | `SVM/PS2EE Ver.1.54` | 6 Oct 2004 11:47:19 |
| cvFs | the device-independent file layer | `CVFS/PS2EE Ver.2.37` | 6 Oct 2004 11:47:39 |
| SRD, DVCI, HTCI, MFCI, LSC | the sector reader, the disc, host and memory file devices, the link stream controller | `SRD/PS2EE Ver.2.22`, `DVCI/PS2EE Ver.2.71`, `HTCI/PS2EE Ver.2.69`, `MFCI/PS2EE Ver.1.09`, `LSC/PS2EE Ver.2.18` | 6 Oct 2004 11:47:41 to 11:47:44 |
| DTR, DTX | EE and IOP data transfer between stream joints | `DTR Ver.1.06`, `DTX Ver.1.08` | 6 Oct 2004 11:47:40 |
| CRI CFG | a table of named integer settings | `CRI CFG/PS2EE Ver.1.002` | 6 Oct 2004 11:47:45 |
| SNDF | the sound driver's EE side (SIF RPC to the IOP) | `SNDF Ver.2.09c` | 4 Oct 2004 20:48:06 |
| CFT | colour-format and alpha-plane tables | `CRI CFT/PS2EE Ver.1.57` | 6 Oct 2004 11:36:30 |
| M2V, MPV | MPEG-2 video decoder (M2V is the lower layer under MPV) | `CRI M2V/PS2EE Ver.1.945`, `CRI MPV/PS2EE Ver.1.933` | 6 Oct 2004 11:36:22 to 11:36:26 |
| MPS | MPEG system-stream demultiplexer | `CRI MPS/PS2EE Ver.1.924` | 6 Oct 2004 11:36:19 |
| SFD | the Sofdec player library | `CRI SFD/PS2EE Ver.1.946` | 6 Oct 2004 11:36:10 |
| SFH, SFX, SUD | stream header sector, frame conversion, user data and timer | `CRI SFH/PS2EE Ver.1.19`, `CRI SFX/PS2EE Ver.2.08`, `CRI SUD/PS2EE Ver.0.05` | 6 Oct 2004 11:36:25 to 11:36:34 |
| MWSFD | the Sofdec player the game calls (`mwPly*`) | `MWSFD/PS2EE Ver.3.33s281` | 6 Oct 2004 11:36:36 |

These builds are newer than every public source for the middleware: the 2002 SDK archives and the 2003 Street
Fighter III 3rd Strike build are older, so a DW4 body can have grown past the one a name is taken from
([naming sources](#naming-sources-and-confidence)). Where the strings and the code leave a boundary open, the topic
documents say what each file's extent rests on.

## Address ranges and units

Each library is split into whole-file units, one `cri_<name>` row each in `config/SLUS-20836/units.tsv` (107 rows: 50
in the ADX block, 57 in the Sofdec block) and one source file each in `src/cri/`, with its headers in
`include/dw4/cri/`. The table groups the units by library and links the document that gives their extents.

| group | units | document |
| --- | --- | --- |
| ADXAMP, the AC-3 and AHX glue, the AIFF and AU readers, SKG (`0x25b248` up to `0x25d300`) | 6: `adxamp`, `adxac3`, `adxahx`, `adxaiff`, `adxau`, `skg` | [ADX before ADXB](cri-adxamp-readers-skg.md) |
| ADXB, the decoder core (`0x25d300` up to `0x25e668`) | 1: `adxb` | [ADXB](cri-adxb.md) |
| SPSD and WAV readers, ADXCRS, the file-system server pass, CRI CFG | 5: `adxspsd`, `adxwav`, `adxcrs`, `adxfssvr`, `cricfg` | [ADX small files](cri-adx-small-files.md) |
| ADPCM decode, ADXERR, ADXF | 3: `adxdcd`, `adxerrs`, `adxf` | [ADX decode, ADXERR and ADXF](cri-adxf-files.md) |
| ADX header, ADXT init and seamless entry, ADXPS2, messages, ADXRNA | 6: `adxhdr`, `adxtinit`, `adxtsml`, `adxps2`, `adxmsg`, `adxrna` | [ADXT-side files](cri-adxt-files.md) |
| ADXSJD, the stream-joint decoder | 1: `adxsjd` | [ADXSJD](cri-adxsjd.md) |
| ADXENC, the encoder | 1: `adxenc` | [ADXENC](cri-adxenc.md) |
| ADXSTM and the disc, host and memory setup files | 4: `adxstm`, `adxdvd`, `adxhst`, `adxmfs` | [ADXSTM](cri-adxstm.md) |
| ADXT, the playback handle and its server | 2: `adxt`, `adxtsvr` | [ADXT](cri-adxt.md) |
| the decode job table | 1: `convjobs` | [conversion jobs](cri-convjobs.md) |
| cvFs and the sector reader under it | 2: `cvfs`, `srd` | [cvFs](cri-cvfs.md), [SRD](cri-srd.md) |
| EE and IOP transfer | 2: `dtr`, `dtx` | [DTR and DTX](cri-dtr-dtx.md) |
| cvFs devices and the link stream controller | 4: `dvci`, `htci`, `mfci`, `lsc` | [DVCI](cri-dvci.md), [HTCI](cri-htci.md), [MFCI](cri-mfci.md), [LSC](cri-lsc.md) |
| Pro Logic II, PS2RNA, SJ critical section, error report and memory join | 6: `pl2enc`, `adxtpl2`, `ps2rna`, `sjcrs`, `sjerr`, `sjmem` | [PL2ENC, PS2RNA, SJCRS](cri-ps2rna-sj.md) |
| SJ ring, universal, tag utilities, remote and join, and SVM (to `0x27ede0`) | 6: `sjrbf`, `sjuni`, `sjutl`, `sjrmt`, `sjx`, `svm` | [SJ and SVM](cri-sj-svm.md) |
| SNDF and CFT (`0x280b98` up to `0x285118`) | 2: `sndf`, `cft` | [SNDF and CFT](cri-sndf-cft.md) |
| MPS and MPV front files, the start-code scanner | 6: `mpsutl`, `mpsdmx`, `mps`, `mpvapi`, `mpvhdr`, `startcode` | [MPS and MPV files](cri-mps-mpv-files.md), [start codes](cri-startcode.md) |
| MPV core and MWSFD player creation | 2: `mpv`, `mwsfcre` | [MPV core and creation](cri-mpv-mwsfcre.md) |
| MWSFD core, frame side and player control | 4: `mwsffrm`, `mwsfd`, `mwsfply`, `mwsfrna` | [MWSFD core](cri-mwsfd-core.md) |
| MWSFD settings and scratchpad swap | 2: `mwsfdrsc`, `mwplyprm` | [MWSFD settings](cri-mwsfd-settings.md) |
| MWSFD front end over SFX | 1: `mwsfsfx` | [MWSFD over SFX](cri-mwsfsfx.md) |
| MWSFD link controller, SST, server, stream | 4: `mwsflsc`, `mwsfsst`, `mwsfsvr`, `mwstm` | [MWSFD files](cri-mwsfd-files.md) |
| the SFD player library's twelve files: the ADX audio handler, the handler wrappers, buffers, video and its PS2 side, the player, the PTS ring, the time record, conditions, time and the stream graph | 12: `sfadx`, `sfdusr`, `sfdbuf`, `sfmpv`, `sfmpvps2`, `sfdply`, `sfdring`, `sfdrec`, `sfdcond`, `sftim`, `sfdtrn`, `sfdtst` | [SFD files](cri-sfd-files.md) ([MWSFD files](cri-mwsfd-files.md) ends at `sfadx`) |
| SFD core: sync queues, analysis, header, library core, supply, MPS handler | 6: `sfdsync`, `sfdana`, `sfdhdr`, `sfdlib`, `sfdsup`, `sfmps` | [SFD core](cri-sfd-core.md) |
| SFD output handlers, SFH, SFX alpha | 4: `sfdainf`, `sfdout`, `sfh`, `sfxa` | [SFD output, SFH, SFX alpha](cri-sfh-files.md) |
| SFX conversion, SFX, Z conversion, SUD (to `0x2b5d50`) | 4: `sfxcnv`, `sfx`, `sfxz`, `sud` | [SFX and SUD](cri-sfx-sud.md) |
| SNDF command senders, the time comparison, the M2V decoder and its hooks, memory copies | 10: `sndfcmd`, `cmptime`, `mpvhook`, `m2verr`, `m2vfrm`, `m2vget`, `m2vhdec`, `mpvinst`, `m2vlib`, `mcpnot` | no topic document of their own; [MPV core and creation](cri-mpv-mwsfcre.md) covers the M2V layer and its hooks, [SNDF and CFT](cri-sndf-cft.md) the command senders |

The engine side is [igCriMovieCodec](cri-movie-codec.md) (`movie_igCriMovieCodec`, outside the CRI blocks).
[Sd prologue](sd-prologue.md) explains why these blocks are Sony EE GCC code, and [cvFs](cri-cvfs.md) is the one
unit with its own flag.

## How it is compiled

- **Compiler.** Sony EE GCC 2.96 (`2.96-ee-001003-1`, the `GCC2096` stamp in the executable) at `-O2 -G0
  -ffunction-sections`, driven by `tools/cc.py` and `tools/eegcc_compile.py` and pinned per unit in `units.tsv`
  ([sd-prologue](sd-prologue.md#the-cri-and-newlib-compiler)). Its `sd` callee-saved prologue is what marks these
  blocks as vendor code, not MWCC.
- **Whole files.** Every unit compiles as one whole file, each function checked at its retail address and the unit
  verified as a whole, because a call to a function already compiled in the same file is known not to throw and
  that changes how delay slots are filled ([whole-file units](emitted-functions.md#whole-file-units)). The topic
  documents give, per file, what the extent rests on (strings, data order, error-code runs) and which functions
  only match when compiled after another.
- **One profile.** All CRI units share one flag string except `cvfs`, which builds with `-fno-strict-aliasing`: its
  SDK types (function-pointer slots, a `void *` argument block) sit in different alias sets, and only without strict
  aliasing does the first scheduling pass keep the slot load after the stores into the argument block
  ([cvFs](cri-cvfs.md#argument-block-and-aliasing)). On every CRI unit at once the flag breaks about fifty units, so it
  is a property of that unit, never a fix for one function.
- **Aliasing.** ee-gcc orders memory accesses only within one alias set, so a field's type (an enum, a pointer type,
  an address-taken local) decides the schedule; the causes found are in
  [understanding-shapes](understanding-shapes.md#scheduling-ee-gcc).
- **Headers.** One folder, `include/dw4/cri/`, mirrors the libraries; structure layouts come from the 2002 SDK's debug
  information and are documented per topic.

## Naming sources and confidence

Names are taken from evidence in this order: an exact body match,
then the closer build (3rd Strike of 2003 over the SDK of 2002), then both agreeing, then DW4's own string, then the
other public lists, then behaviour alone. High-confidence names are exact or agreed; a medium name is the
best reading with an alternative recorded; anything less stays an address name with an open question in its topic
document. Names are CRI's own spelling (`ADXT_*`, `mwPly*`, `SFD_*`); no address appears in a name.

| source | what it gives | confidence | cited by |
| --- | --- | --- | --- |
| the 2002 CRI SDK archives (`libadxe.a`, `libmwsfde.a`), through [SkeletonPicture/recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri) | member bodies (A exact, B or C near after address masking, O same position in order with equal size), the headers' type and member names, and the STABS debug records that give struct layouts and argument types | high where the body is exact or near; the 2002 builds are older than DW4's, so bodies that grew are medium | most ADX documents, [cvFs](cri-cvfs.md), [ADXENC](cri-adxenc.md), [SFD files](cri-sfd-files.md) |
| the Street Fighter III 3rd Strike decompilation, [crowded-street/3s-decomp](https://github.com/crowded-street/3s-decomp) | the 2003 libadxe (ADX, cvFs, devices, SRD, SJ and DTX names, order and sizes) | high where the body agrees with the SDK's, medium by order and size | the ADX documents, [cvFs](cri-cvfs.md), [DVCI](cri-dvci.md), [HTCI](cri-htci.md), [SRD](cri-srd.md) |
| the Resident Evil 4 CRI library in the [Persona 4 decompilation](https://github.com/Raikaru/Persona4-Decompilation) (`src/cri/re4`) and its proven names (`docs/cri/proven_names.json`, masked-exact against unstripped builds) | Sofdec C with its own member names and statement order; names proved in other builds, taken where DW4 holds the same slot at a near-equal size | medium only | [SFD core](cri-sfd-core.md), [SFD files](cri-sfd-files.md), [MPV core](cri-mpv-mwsfcre.md), [SFX and SUD](cri-sfx-sud.md) |
| the Resident Evil 4 GameCube symbol map, [adonis-singh/re4](https://github.com/adonis-singh/re4) (`config/G4BE08/sym_map.tsv`) | names and file order of the same library versions for Sofdec, SFX, SFD and SKG | medium | [SFD files](cri-sfd-files.md), [SFX and SUD](cri-sfx-sud.md), [ADX before ADXB](cri-adxamp-readers-skg.md) |
| DW4's own strings and messages | the numbered error messages name many functions outright | high | every topic document |

The overlay rows (`config/SLUS-20836/names/CriAdx.tsv`, `CriSofdec.tsv`, `CriDevices.tsv`, `CriMfci.tsv`,
`CriMovieCodec.tsv`) carry each name's tier and its evidence; a medium row names its alternative. The archives
themselves and the compiled objects are not part of the repository; they are cited by name and member.

## Current state

Match and readability figures live in [`PROGRESS.md`](../../PROGRESS.md) and `docs/progress.json`, and the
per-function state in `data/check-categories.tsv`; this page does not copy them. The rebuilt game links
byte-identical to retail.

### Owner-approved exceptions

`config/source-approvals.tsv` holds the owner's rows; CRI has no `asm` row and one `asm-function` row. What it does
hold, for the CRI units (the rows are listed by anchor in [source approvals](source-approvals.md)):

| category | rows | anchors |
| --- | ---: | --- |
| `volatile` on words shared between threads, V-sync and callback chains | 77 | [adxm-thread-ids](source-approvals.md#adxm-thread-ids), [adxm-thread-flags](source-approvals.md#adxm-thread-flags), [adx-server-guards](source-approvals.md#adx-server-guards), [adxt-ready-count](source-approvals.md#adxt-ready-count), [srd-module-words](source-approvals.md#srd-module-words), [srd-server-words](source-approvals.md#srd-server-words), [srd-spin-counter](source-approvals.md#srd-spin-counter), [svm-lock-counts](source-approvals.md#svm-lock-counts), [dtx-server-flag](source-approvals.md#dtx-server-flag), [mwsfd-handle-used](source-approvals.md#mwsfd-handle-used), [mwsfsvr-vsync-count](source-approvals.md#mwsfsvr-vsync-count), [sfd-play-pending](source-approvals.md#sfd-play-pending), [sfd-time-counts](source-approvals.md#sfd-time-counts), [sfx-handle-used-flag](source-approvals.md#sfx-handle-used-flag), [sud-timer](source-approvals.md#sud-timer) |
| `volatile` on the build-string pointer words each module reads or stores and never uses | 24 | [build-string-reads](source-approvals.md#build-string-reads), [build-string-stores](source-approvals.md#build-string-stores) |
| `volatile` on hardware registers (the MPV PS2 file's DMA channel registers) | 7 | [sony-hardware-registers](source-approvals.md#sony-hardware-registers) |
| `asm-function`: a function retail took from a later tool chain than ee-gcc 2.96, proven against the 2002 SDK object | 1 | [sofdec-build-tool-asm-functions](source-approvals.md#sofdec-build-tool-asm-functions) |

The 108 `volatile` rows count 210 `volatile` statements. The `sync` and `ei` pair in one SNDF function needs no row: C cannot
spell them ([source approvals](source-approvals.md#the-approval-rule)). The owner also approved integer-typed fields
that are cast at each use, on the condition that the typing describes the types rather than one call site (one
declaration, every function that touches it matching, none needing the pointer form): the HTCI and DVCI file-list
pointers ([HTCI](cri-htci.md#integer-typed-list-pointer)) and the SFX plane address ([SFX and SUD](cri-sfx-sud.md)).
The SFD buffer channel keeps a byte size and a position through casts, which the owner approved landing that way
([SFD files](cri-sfd-files.md)).

## Open

The CRI functions that do not match yet are listed in `data/check-categories.tsv`. All are scheduling or
register-allocation differences; each topic document's open questions give the recorded best C and what still
differs, and they link from the retail image.

**Compiler warnings.** Compiling the CRI units with ee-gcc gives 27 warnings, all pointer/integer mismatches left by
`int`-typed fields or untyped externs, plus one conflicting `memset` prototype in `sndf.h` that three units include:
`mwsffrm.c` 7, `mwsfd.c` 4, `sjx.c` 3, `mwsfsfx.c` 2, `mwsfsvr.c` 2, `sfxz.c` 2, `sndf.c` 2, and one each in
`m2vhdec.c`, `mfci.c`, `mwsfcre.c`, `mwsflsc.c` and `sndfcmd.c`.

**Struct reports** ([debt ratchet](debt-ratchet.md)). No CRI struct is in a struct report. The encoder's `IirFilt` and
`PredictFilt` keep the SDK's own `d0`/`d1` members, which the 2002 STABS name that way; they look offset-named, so
`config/sourced-member-names.tsv` lists them with that source and report (c) does not count them.

**Fields still named by offset.** About 190 declarations in the CRI headers and sources carry `fNN` or `bNN` names:
most in the SFD handle parts (`sfd.h`) and the SFX frame (`sfx.h`), then the MWSFD player (`mwply.h`), the SNDF
context (`sndf.h`), the MPV PS2 file (`sfmpv.h`), MPS, M2V and CFT. Each topic document's open questions say which
fields have no reader beyond a clear or a copy and which wait on a second source: for example the SFD handle's
`SfdPlyInf`, `SfdTim` and `SfdIpuStream` words ([SFD core](cri-sfd-core.md)), the MWSFD player's `src488` up to
`src496` ([MWSFD core](cri-mwsfd-core.md)), and the MPS parameter block's words ([SFD core](cri-sfd-core.md)).
About 87 functions still carry an address name (one in the ADX block, 86 in Sofdec, mostly the SNDF commands, the SFX
setter forwards and the SUD helpers); their evidence is in the topic documents' "still unnamed" lists.

**Gaps.** The M2V decoder units (`m2v*`, `mpvhook`, `mpvinst`, `mcpnot`), `cmptime` and `sndfcmd` have no topic
document of their own; their names and layouts are in the overlays and in the MPV and SNDF documents.

## Topic documents

[ADX before ADXB](cri-adxamp-readers-skg.md) · [ADXB](cri-adxb.md) · [ADX small files](cri-adx-small-files.md) ·
[ADXF files](cri-adxf-files.md) · [ADXT-side files](cri-adxt-files.md) · [ADXSJD](cri-adxsjd.md) ·
[ADXENC](cri-adxenc.md) · [ADXSTM](cri-adxstm.md) · [ADXT](cri-adxt.md) · [conversion jobs](cri-convjobs.md) ·
[cvFs](cri-cvfs.md) · [SRD](cri-srd.md) · [DTR and DTX](cri-dtr-dtx.md) · [DVCI](cri-dvci.md) · [HTCI](cri-htci.md) ·
[LSC](cri-lsc.md) · [MFCI](cri-mfci.md) · [PL2ENC, PS2RNA, SJ](cri-ps2rna-sj.md) · [SJ and SVM](cri-sj-svm.md) ·
[SNDF and CFT](cri-sndf-cft.md) · [MPS and MPV files](cri-mps-mpv-files.md) · [start codes](cri-startcode.md) ·
[MPV core and creation](cri-mpv-mwsfcre.md) · [MWSFD core](cri-mwsfd-core.md) · [MWSFD settings](cri-mwsfd-settings.md) ·
[MWSFD over SFX](cri-mwsfsfx.md) · [MWSFD files](cri-mwsfd-files.md) · [SFD core](cri-sfd-core.md) ·
[SFD files](cri-sfd-files.md) · [SFD output, SFH, SFX alpha](cri-sfh-files.md) · [SFX and SUD](cri-sfx-sud.md) ·
[igCriMovieCodec](cri-movie-codec.md)
