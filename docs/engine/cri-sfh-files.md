# CRI SFD output handlers, SFH and SFX alpha

Four whole files between the SFD time-stamp file (`src/cri/sfdtst.c`) and the SFX conversion code, each compiled
with Sony EE GCC 2.96 at `-O2 -G0` (their rows in `units.tsv` and `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)). The file names and the function names outside SFH and the
SFX alpha code are best guesses from behaviour. SFH's version string names its library, and the SFH and
SFX alpha functions carry CRI's own names, taken from the CRI PS2 SDK archive `libmwsfde.a` (members `sfh_main.o` and
`sfx_alp.o`; [recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)) and from Resident Evil 4's
GameCube symbol table ([adonis-singh/re4](https://github.com/adonis-singh/re4), `config/G4BE08/sym_map.tsv`) and CRI
library (`src/cri/re4/` in [Raikaru/Persona4-Decompilation](https://github.com/Raikaru/Persona4-Decompilation)).

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/sfdainf.c` | `cri_sfdainf` | `0x2b0ed0` up to `0x2b1410` | the additional-information channel: the handler of stream graph slot 8, which passes the slot's buffer channel to up to three user outputs (`SFD_SetSystemUsrSj`, `SFD_SetUsrSj`) | errors `0xFF0006xx` only in this run; its 14-entry handler table at `0x4f5278` lists the functions in code order from `SFUO_Init` to `SFUO_Seek`; the setters reset the list the table's create entry builds |
| `src/cri/sfdout.c` | `cri_sfdout` | `0x2b1410` up to `0x2b16e0` | the output handler of stream graph slot 6: the application reads the slot's buffer channel through its GetRead and AddRead entries, gated by the time block | errors `0xFF0007xx`; its handler table at `0x4f52b0` follows the first and lists `SFVOM_Init` up to `SFVOM_Seek` in code order |
| `src/cri/sfh.c` | `cri_sfh` | `0x2b16e0` up to `0x2b2ee8` | SFH (`CRI SFH/PS2EE Ver.1.19`): the header sector of a Sofdec stream: handle pool, magic and version checks, file information and the per-stream audio and video descriptors | its read-only data `0x4f52f0` up to `0x4f53b0` (the `SFH Version` and copyright strings, the build string `SFH_GetSbverStr` returns, `SofdecStream`, `Ver.` and the jump table of `getPicRate`) follows the second handler table; its bss is `0x585688` up to `0x5856a0` |
| `src/cri/sfxa.c` | `cri_sfxa` | `0x2b2ee8` up to `0x2b31d8` | SFX alpha: the alpha handles an SFX handle keeps (`SfxHn.ahn`): the parameters of the CFT colour table and the three alpha levels of the CFT alpha tables, then three frame helpers | its data `sfxa_lib` (`0x4beb58`, 200 bytes) sits between the time-stamp file's data and SFX's library object at `0x4bec28`; `SFXA_Init` and `SFXA_Finish` are called from SFX's init and finish; the SFX conversion code at `0x2b31d8` starts with the next read-only data (`sfxcnv_` messages) |

The two handlers read the handle as `SfdPly` and the stream graph entry (`SfdTrnSlot`, `0x44` bytes at handle +7976)
and the user outputs (`SfainfList`) from `include/dw4/cri/sfd.h`; SFH and SFX alpha declare their own types. SFH's handle (`SfhHn`, 16 bytes)
points at the header in memory (`SfhHdr`); a stream descriptor (`SfhStm`, 64 bytes, 26 of them at +384) is read
as `SfhAudioStm` or `SfhVideoStm` by its MPEG stream id (`chkStmId`). The audio descriptor's bytes at `0x1A` and `0x1B` are the MPEG audio layer (`SfhAudioStm.layer`, read by
`SFH_AnlyElemLayer`) and the channel count (`SfhAudioStm.chNum`, `SFH_AnlyElemChNum`), followed by the sampling rate
(`smpHz`); the other descriptor field names are guesses from what the getters return. `SFXA_Destroy` writes the in-use
word through a `volatile` pointer, approved under [sfx-handle-used-flag](source-approvals.md#sfx-handle-used-flag).

`SFH_Create` reads the pool's three words (capacity, count, table) into locals of their own before its full-pool
test. That decides more than the loads: the pool's address then sits in `a0`, the table load fills the delay slot of
the full-pool branch, and from there the delay-slot filler counts `a0` as live at the search loop's head, so the
loop's closing branch takes the loop test into its slot rather than the argument move that follows it
([delay slots](understanding-shapes.md#delay-slots-ee-gcc)). With the count tested straight from the pool the
address sits in `v1` and the loop comes out with the move in the slot and a pad before the loop head.

## Open questions

- The handler tables at `0x4f5278` and `0x4f52b0` are not defined in C; nothing in the code references them, only
  the module lists in MWSFD's data.
- What the stream graph slots 6 and 8 carry: the file names `sfdout` and `sfdainf` rest on behaviour and on the
  MWSFD caller that sets the additional-information stream join through `SFD_SetUsrSj`.
- `SFX_SetClipping`, `SFX_SetBottomUpBuf` and `SFX_SetBottomUpPlnBuf` are called from nowhere in the image.
- Every SFH function but two holds the slot of the same name in the SDK `sfh_main.o`, in the same order, with the same
  body or a near one; the public getters are also in the RE4 GameCube `lib/sfh_main.c`. High, except the near SDK bodies
  the RE4 table lacks (`SFH_AnlySfdTimStmp`, `SFH_AnlyHdrToolInf`, `SFH_AnalyHdrComment`, `getToolVer`,
  `SFH_AnlyElemFname`, `SFH_AnlyElemTimStmp`) and `getPicRate`, which are medium. `SFH_AnlyHdrToolVer` grew since 2002 and
  keeps the SDK and RE4 slot (high). The two getters of the mux block's version-2.25 words, which nothing calls, are named
  from what they return, `SFH_AnlyExtFirst` and `SFH_AnlyExtSecond` (medium): no approved source says what the words hold.
- SFX alpha: `SFXA_Init`, `SFXA_Finish`, `SFXA_Create`, `SFXA_MakeAlpLumiTbl`, `SFXA_IsNeedUpdateLumiTbl`, `SFXA_SetLumiPrm`
  and `SFXA_GetLumiPrm` have the SDK `sfx_alp.o` bodies and `SFXA_Destroy` a near one (high); `sfxalp_InitLibWork`,
  `sfxalp_SearchFreeHn`, `sfxalp_InitHn` and `SFXA_MakeAlp3Tbl` hold the SDK order (medium). `SFXA_MakeAlp3110Tbl` is the RE4
  function after `SFXA_MakeAlpLumiTbl` (medium); the RE4 library follows it with `SFXA_MakeAlp3211Tbl` where DW4 has the
  SDK's `SFXA_MakeAlp3Tbl`. Named from what they do (medium): `SFXA_SetAlp3Prm` and `SFXA_GetAlp3Prm` (the three alpha
  levels the three-level tables are built from, which `SFX_SetAlp3Prm`/`SFX_GetAlp3Prm` forward, as `SFX_SetALumiPrm`
  forwards to `SFXA_SetLumiPrm`) and `SFX_SetClipping` (sets a frame to a clipping rectangle).
- `SFX_SetBottomUpBuf` and `SFX_SetBottomUpPlnBuf` have identical bodies (a line walk turned upside down). The RE4 library
  has one, `SFX_SetBottomUpPlnBuf`, at the end of its `sfx_cnv.c`; the second copy here takes that name (medium; the
  alternative is the first) and the first a name from what it does. The RE4 library keeps the function in `sfx_cnv.c`, not
  in the SFX alpha file.
