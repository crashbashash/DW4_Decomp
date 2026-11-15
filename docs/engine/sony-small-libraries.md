# The smaller Sony libraries: libgraph, libipu, libsdr and libmc

Four of the Sony runtime libraries are a few functions each, one whole-file unit per SDK 3.0.3 object, with the
unit named after the object's main function (libipu's `libipu.c` after its object, since it holds five).
libmtap, the fifth, is described in [the Sony compiler](sd-prologue.md#libmtap-is-one-file). The libraries
are release 2.8.0 (`PsIIlibgraph2800`, `PsIIlibipu  2800`, `PsIIlibsdr  2800`) except libmc, which is 2.8.1
(`PsIIlibmc   2810`). Each file defines its own data.

## libgraph (`0x1029f8..0x102c94`)

| File | Extent | SDK object | Contents |
|---|---|---|---|
| `src/sony/libgraph/sceGsResetGraph.c` | `0x1029f8..0x102b94` | `graph001.o` | `sceGsResetGraph`, `sceGsGetGParam`, the `gp` state and the descriptor (`.data` `0x481c20`) |
| `src/sony/libgraph/sceGsResetPath.c` | `0x102b98..0x102c00` | `graph002.o` | `sceGsResetPath` and its VIF register table `init_vif_regs` (`.data` `0x481c40`) |
| `src/sony/libgraph/sceGsSyncV.c` | `0x102c00..0x102c94` | `graph011.o` | `sceGsSyncV` |

All three build with `ee-gcc-2.9-as210` (`-O2 -G0 -ffunction-sections`).

* `gp` is the library's one state block, `{inter, omode, ffmode, version, vsync_set, vsync_id}`, initialised
  `{1, 2, 1, 3, 0, 0}`; `sceGsGetGParam` returns its address (the function `sceGsSyncV` calls).
* `sceGsResetGraph(mode, ...)` has three modes: 0 resets the GS (`GS_CSR` reset bit), stores the
  interlace, output mode and frame-field mode, reads the GS version from `GS_CSR`, masks the GS interrupts
  with `GsPutIMR`, removes the vblank handler if `sceGsSyncV` installed one, and sets the CRT; 1 flushes
  (`GS_CSR` flush bit); 5 stores the parameters and sets the CRT without resetting.
* `sceGsResetPath` resets VIF1 (`VIF1_FBRST`, `VIF1_ERR`), sets the VU0 control register `vi28` bit 9 and
  loads the VIF's initial register values through its FIFO, then starts the GIF (`GIF_CTRL`). The `cfc2` and
  `ctc2` have no C spelling, so they are `asm`; the register accesses are `volatile`
  ([source approvals](source-approvals.md#sony-vu-and-gp-asm),
  [hardware registers](source-approvals.md#sony-hardware-registers)).
* `sceGsSyncV` waits for the next vertical sync (`VSync` when no vblank handler is set, `VSync2` when one is)
  and returns the field bit of `GS_CSR` in interlace mode, 1 otherwise.

## libipu (`0x10a468..0x10aaa8`)

| File | Extent | SDK object | Contents |
|---|---|---|---|
| `src/sony/libipu/libipu.c` | `0x10a468..0x10a7f8` | `libipu.o` | `setD3_CHCR`, `setD4_CHCR`, `sceIpuStopDMA`, `sceIpuRestartDMA`, `sceIpuSync` |
| `src/sony/libipu/sceIpuInit.c` | `0x10a7f8..0x10aaa8` | `ipuinit.o` | `sceIpuInit`, its own `setD4_CHCR`, the descriptor `PsIIlibipu  2800` (`0x481dc0`), `iqval` and `vqval` |

Both build with `ee-gcc-2.9`. The static `setD4_CHCR` exists twice, once in each object; the second copy takes
the suffix `_ipuinit` in the symbol table and `setD4_CHCR` as its unit symbol.

* `setD3_CHCR` and `setD4_CHCR` write a DMA channel's control register with interrupts off and the DMA
  controller's CPND enable bit set around the store.
* `sceIpuStopDMA` stops channel 4, saves the channel and IPU registers into a `sceIpuDmaEnv`, waits for the
  IPU's input FIFO to empty and stops channel 3; `sceIpuRestartDMA` gives them back, adjusting the channel-4
  address by the quadwords still in the FIFO. `sceIpuSync` waits for the IPU (mode 0) or returns its busy bit
  (mode 1); it must be a `switch` (an if/else chain emits a different branch order).
* `sceIpuInit` resets the IPU, loads the intra quantisation matrix (`iqval`, four quadwords) and the
  non-intra default (one quadword of 16s, sent four times) and the 16-colour VQ palette (`vqval`, RGB555)
  through the input FIFO, and runs the commands that set them. The pointer to the matrix is assigned twice
  (first 0): that keeps alias analysis from folding it to the array, so the fifth quadword is reissued before
  each of its four stores, as retail does. The FIFO and command registers are `volatile`
  ([source approvals](source-approvals.md#sony-hardware-registers)).
* `sceIpuDmaEnv` and the register names are Sony's SDK names.

## libsdr (`0x118fe0..0x1194c0`)

`src/sony/libsdr/sdr_main.c` is the whole of the object `sdr_main.o` that the image keeps: `sceSdRemoteInit`,
`sceSdTransToIOP`, `sceSdCallBack` and `sceSdRemote`, built with `ee-gcc-2.9`. It is the EE client of the IOP's
`sdr.irx` (RPC server `0x80000701`).

* `sceSdRemoteInit` binds the server, retrying until it answers. `sceSdTransToIOP` sends a block to the IOP by
  SIF DMA and optionally waits. `sceSdCallBack` records the end function and its `$gp`. `sceSdRemote` is the
  variadic call: it packs the command and six arguments into a 64-byte-aligned buffer, makes the RPC, and for the
  two handler-setting commands (`rSdSetTransIntrHandler`, `rSdSetSpu2IntrHandler`) stores the caller's handler,
  argument and `$gp` in the library's tables and returns the previous handler.
* The file's own data in retail order: `sceSdEndFunc` and `sceSdEndGp` (`0x485140`) and the descriptor
  `PsIIlibsdr  2800` (`0x485148`), then the client block and the transfer buffer (`.bss` `0x55d500`); the one
  string, the bind error message, is a literal in the code. The handler pointers, arguments and `$gp`s that
  follow the descriptor in `.data` (`0x485158`) belong to the callback file, and `sdr_main.c` reaches them as
  externs.
* `src/sony/libsdr/sdr_cb.c` is that callback file (`sdr_cb.o`: `sceSdRemoteCallbackInit` and `Quit`, the
  callback thread) as the image keeps it, a [data-only unit](emitted-functions.md#data-only-units): the linker
  dropped its text, strings and `.bss` but kept its `.data`, nine zero words
  (`_sce_sdr_transIntr0Hdr`..`_sce_sdr_spu2IntrGp`) and the thread id `_sce_sdr_cb_thid` (`-1`, at `0x48517c`).
  The file holds those definitions only; code for the dropped functions could not be checked against anything.
* `sceSdCallBack` reads `$gp` with the library's inline `asm` (`GetGp`); the rows are under
  [#sony-vu-and-gp-asm](source-approvals.md#sony-vu-and-gp-asm).

## libmc (`0x1194c0..0x11acc0`)

`src/sony/libmc/libmc.c` is the object `libmc.o`: the EE client of the memory-card servers `mcserv.irx` and
`mcman.irx` (RPC server `0x80000400`), built with `ee-gcc-2.9`. Its 27 functions are in the object's order from
`sceMcInit` to `sceMcGetEntSpace`.

* A call fails with `sceMcErrUnbind` when the client is not bound and `sceMcErrSemapho` when the library's
  semaphore is taken; otherwise it fills one of two parameter blocks (`McCommand` for calls that name no path,
  `McPathCommand` for those that do), makes the RPC, and either waits (`sceMcSync` collects the result) or hands
  the end function `mceSifRpcEndFunc` to the RPC. The words of a `McCommand` are reused with a different meaning
  per call (the seek origin, the write's head length and the new priority are all `count`).
* `sceMcInit` creates the two semaphores, binds the server, calls function 254 and checks the servers'
  versions (it refuses `mcserv` below 522 and `mcman` below 526 with `sceMcIniOldMcserv` and
  `sceMcIniOldMcman`); `sceMcEnd` deletes the semaphores.
* `sceMcRead` hands the IOP a 64-byte head and tail block (`McReadApdx`) for the unaligned ends of the
  transfer, and `mceIntrReadFixAlign` copies them into the caller's buffer from the end function; `sceMcWrite`
  sends the unaligned head (up to 16 bytes) inside the command itself and the aligned rest by address.
  `sceMcGetInfo` takes its type, free-block and format results from the `McInfoApdx` the IOP fills.
* The data is the file's own: `.data` `0x485180` (the descriptor `PsIIlibmc   2810`, the running-command number and the two semaphore ids),
  `.bss` `0x55d5c0` (the client block, the two parameter blocks, `buffFileInfo`, `currentDir`, `retval`) and
  `.rodata` `0x4d2ad0`. `sceMcTblGetDir` carries `aligned(64)` in the SDK; on the type it changes the struct
  copy of `sceMcSetFileInfo`, so the alignment sits on `buffFileInfo`.
* The function and constant names come from the 3.0.3 object's symbols and the SDK's `libmc.h`. The file has
  no `asm` and no `volatile`.

## Open questions

* `mceGetClientState` (`0x1196e0`) returns the client block and hands out the result buffer and the
  running-command number, storing the semaphore in `retval[15]`. It has no caller and 3.0.3 has nothing like
  it, so its name says what it does (medium confidence) and its purpose is not known.
* `currentDir` (4096 bytes) and `retval` (16 words) are sized from the next object's address, not from a
  symbol size; the libmc and libsdr boundary at `0x485190` in the data owners is probably 16 bytes off, since
  libmc's version string sits at `0x485180`.
* Which assembler built libipu, libsdr and libmc is open ([the Sony compiler](sd-prologue.md#open-questions)):
  every matched function builds identically with either.
