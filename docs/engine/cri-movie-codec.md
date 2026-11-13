# igCriMovieCodec: the Sofdec codec

`igCriMovieCodec` is the `igMovieCodec` the movie manager creates for FMV: it plays a Sofdec stream
through CRI MWSFD (`MWSFD/PS2EE Ver.3.33s281`) or, for an ADX-only movie, an audio stream through CRI
ADXT, and copies each decoded frame into the GS frame buffer. Each open movie keeps its handles in an
`igCriMovieData` object held in `igMovieInfo::_userdata`: the MWPLY handle (`_mwply`) and its work area
(`_cprmbuf`), the ADXT handle (`_adxt`) and its work area (`_adxwork`). The source is
`src/movie/igCriMovieCodec.cpp`, one whole-file unit (`movie_igCriMovieCodec` in `units.tsv`, `0x337410` up to
`0x338ed0`; its members in `unit-objects.json`). The visual context frames are sent through is held in
`g_criMovieVisualContext`, an `igSmartPointer<igPsx2VisualContext>` the file defines: its static initialiser
(`0x5216a0`) registers the pointer's destructor (`0x338e50`, the last function of the unit) to release it at exit.

## Slots

The `igMovieCodec` base returns 0 from every slot from 21 to 29; the codec overrides them.

| slot | function | what it does |
| --- | --- | --- |
| 1 | `Gap__igCriMovieCodec__vfunc_01` | after the `igObject` step, installs `CriMovie_Allocate` / `CriMovie_Free` with the codec as context through `MWSFD_SetMallocFunc`, so MWSFD's work areas come from the codec's pool |
| 21 | `Gap__igCriMovieCodec__vfunc_21` | returns 1; the manager keeps a codec in its list only when this slot says so |
| 22 | `Gap__igCriMovieCodec__vfunc_22` | not matched; calls `mwPlyInitSfdFx` |
| 23 | `Gap__igCriMovieCodec__vfunc_23` | not matched; opens a movie: creates the ADXT or MWPLY handle and its `igCriMovieData` |
| 24 | `Gap__igCriMovieCodec__vfunc_24` | closes a movie: stops and destroys the ADXT handle if there is one, destroys the MWPLY handle, frees both work areas through `CriMovie_Free` and clears the fields |
| 25 | `Gap__igCriMovieCodec__vfunc_25` | resumes: sets `_state` to 0, then releases the ADXT pause (`ADXT_GetStatPause` / `ADXT_Pause`) or the MWPLY pause (`mwPlyIsPause`, then the handle's pause entry) |
| 26 | `Gap__igCriMovieCodec__vfunc_26` | pauses: stores the requested `_state`, then pauses whichever player is running |
| 27 | `igCriMovieCodec_Update` | per-frame update (`mwPlyGetCurFrm` / `mwPlyRelCurFrm`) |
| 28 | `Gap__igCriMovieCodec__vfunc_28` | allocates the upload packet for the movie's size and takes a reference to the `igPsx2VisualContext` it is sent through |
| 29 | `Gap__igCriMovieCodec__vfunc_29` | frees the upload packet |
| 30 | `Gap__igCriMovieCodec__vfunc_30` | reconciles the player with `_state`: a movie marked paused whose player runs goes through slot 26, a movie marked playing whose player is paused through slot 25 |

`igMovieInfo::_type` 2 selects the ADXT path; `_state` 1 is paused and 0 playing. Both pools (the packet's and
the work areas') are the codec's own when `g_useOwnerAllocator` is set and the `g_ndmwAllocatorSelector` pool
otherwise.

## Frame upload

`g_criMovieUploadPacket` is one DMA chain, sized by slot 28 as six quadwords per 16x16 macroblock tile plus
ten, rounded up to 256 bytes and aligned to 64. `CriMovie_SubmitFrame` fills it through
`CriMovie_BuildFrameUpload`, records its size in `g_criMovieUploadPacketSize` and hands it to the visual
context with `igPsx2VisualContext_CallDmaChain`. The frame goes to y 448 while
`igPsx2VisualContext_IsDisplayingFirstBuffer` holds and to y 0 otherwise. With no packet allocated it warns
once (`g_criMovieDmaWarningMuted`) that the DMA transfer was never opened.

`CriMovie_BuildTileUpload` writes the chain: a `cnt` tag and a GIF A+D block setting
`BITBLTBUF` and `TRXREG` to a 16x16 PSMCT32 transfer, then for every tile, column by column, a `cnt` tag, a GIF tag, `TRXPOS` for the
tile and `TRXDIR`, an image GIF tag of 64 quadwords and a `ref` tag to the tile's 1024 bytes of decoded image,
and finally a `ret` tag when the chain is called (as `CriMovie_SubmitFrame` calls it) or an `end` tag when it is not. Wider than 640 pixels it sends 40
columns; taller than 448 lines it sends 28 rows from the middle. The packet helpers are `Dma_SetTag`
(QWC, PCE, ID, IRQ, ADDR, SPR), `Gif_SetTag` (NLOOP, EOP, PRE, PRIM, FLG, NREG, REGS), `Gif_SetAd` and the
four register writers `Gif_SetBitbltbuf`, `Gif_SetTrxpos`, `Gif_SetTrxreg` and `Gif_SetTrxdir`.

## Callees

The ADXT names (`ADXT_Destroy`, `ADXT_Stop`, `ADXT_Pause`, `ADXT_GetStatPause`) are each function's own
parameter-error message. `mwPlyIsPause` sits among the `mwSfd*` entry points and reports an invalid
`SFD_GetPaStat` value. `MWSFD_SetMallocFunc` stores the allocate and free callbacks and their context in the
MWSFD work area that `MWSFD_Malloc` reads. `Memory_AllocateAlignedWithAllocator` is the aligned counterpart
of `Memory_FreeBufferWithAllocator`: it calls the pool's slot 53. `CriMovie_DestroyObjectRef` is the deleting
destructor of a held `igObject` reference that slot 23 uses.

## Open questions

- `mwPlyIsPause` and `MWSFD_SetMallocFunc` are named from behaviour; the library's own spellings are unknown.
- `igPsx2VisualContext_IsDisplayingFirstBuffer` returns whether the GS buffer index the flip toggles is 0;
  whether that index is the displayed or the drawn buffer is not settled.
- The meaning of `igMovieInfo::_type` 2 beyond "uses ADXT" is not confirmed by a movie table.
- The MWPLY handle is declared here as a view of its function table; `src/cri/mwsfsfx.c` declares the full
  handle privately, and one shared declaration would serve both.
