# The `p2` layer: the EE-side renderer

`p2` is Intrinsic Alchemy's PS2/EE backend: the code that turns a render list into VU1 programs and GS
packets. It occupies `0x1e74b0`-`0x20e750` in [`module-map.md`](module-map.md)'s region table; the census
below covers its 169 functions from `0x1f0000` to `0x20d000`.

## The hardware boundary is six functions

`tools/platform_map.py --code-lo 0x1f0000 --code-hi 0x20d000` finds only **6 of the 169** touching a
memory-mapped register:

| function | size | blocks (the tool's own names) |
| --- | --- | --- |
| `p2StoreImage` | 924 | `dma_spr`, `dmac`, `dmac_ctrl`, `vif1`, `vu1_regs` |
| `p2StartDmaPacket` | 560 | `dmac` |
| `FUN_001f8190` | 400 | `gs` |
| `p2readGSPrivRegister` | 320 | `gs` |
| `p2StartTimers` | 656 | `timer` |
| `FUN_001f8350` | 308 | `dma_spr` |

So the whole backend is register-free except for the DMA kicks, one GS-to-memory transfer and two GS
accessors; the rest of the layer is ordinary code building data for those. The tool's `vu1_regs` block
at `0x10005000` is the VIF1 FIFO, and `dma_spr` at `0x10003020` is `GIF_STAT`.

## The DMA channels

`src/engine/dmaChannel.c` holds the channel code; the types are in `include/dw4/p2dma.h`. The layer
drives three DMA channels, 0 (VIF0), 1 (VIF1) and 2 (GIF): the shutdown path prints "VIF0/VIF1/GIF already
disabled" and "Error removing VIF0/VIF1/GIF dmac handler" for channels 0, 1 and 2, and one DMAC handler is
registered per channel (`p2Vif0DmaHandler`, `p2Vif1DmaHandler`, `p2GifDmaHandler`, ids in `p2DmaHandlerIds`).

* **Setup.** `p2InitDmaChannels` creates the wait semaphore from `p2DmaWaitSemaParam`, sets the pool sizes,
  initialises the predicate pool (`p2InitDmaPredicatePool`) and the completion pool, then brings up VIF1,
  GIF and, when it has packets, VIF0 with `p2InitDmaChannel`, and enables the DMAC (`D_CTRL = 1`).
  `p2InitDmaChannel` grows the channel's packet ring (each packet set up by `p2InitDmaPacket`), resets its
  sequences and installs its handler.
* **Packets.** Each channel owns a ring of packets, `p2DmaCurrentPacket[ch]` is the one being filled,
  `p2DmaLastPacket[ch]` the one submitted last and `p2DmaActivePacket[ch]` the next to transfer or the
  one transferring. A packet is a DMA chain buffer (`chain` is the first tag, `cursor` the write
  position) with a 64-bit `sequence`, one higher than the previous packet of its channel. Submitting
  (`p2SubmitDmaPacket`) writes the end tag, marks the packet `ready` and makes the next packet current.
* **Starting.** `p2TryStartDmaPacket` starts the active packet when the channel is idle, the packet is
  ready, every predicate on it holds and no GS-to-memory transfer is pending. `p2StartDmaPacket` records
  `p2DmaStartedSequence[ch]`, sets the channel's bit in the watchdog word (`0x20`/`0x40`/`0x80`), stamps
  the VIF1 or GIF start time and writes `QWC = 0`, `TADR = chain` and `CHCR = 0x185` (chain mode, from
  memory, tag interrupt, start). The submit path, the DMAC handlers and the GS FINISH handler all call
  it.
* **Completion.** The channel's DMAC handler clears its watchdog bit and calls `p2CompleteDmaPacket`, which copies the started sequence to
  `p2DmaCompletedSequence[ch]`, runs the packet's completion callbacks (`p2AddDmaCompletion`), signals
  a waiting thread, moves `p2DmaActivePacket[ch]` to the next packet and starts it if it can.
* **Predicates.** `p2AddDmaPredicate` attaches `test(arg)` to the current packet; the packet does not start
  until every test returns nonzero. `p2RegisterPredicateName` records a name for a predicate in a
  ten-entry table, and its callers name three: `p2PreviousFinishFuncDonePredicate` (the GS FINISH
  handler has run the finish functions queued before this packet), `textureLoadedPredicate` (GIF
  sequence reached) and `textureDeferredPredicate` (VIF1 sequence reached).
* **Waiting.** Callers keep the sequence of the packet that carries their data (a vertex array keeps it in
  `_lSequence`, from `p2GetVif1WaitSequence`) and later call `p2WaitDmaSequence(channel, sequence)`, which
  submits the current VIF1 packet and sleeps on a semaphore until the channel's completed sequence
  reaches it, adding the time slept to `p2DmaWaitTime`, which the statistics getter reports.

### Reading a GS buffer back

`Gap__Gfx__igPsx2VisualContext__vfunc_172` copies a VRAM buffer into an image through `FUN_00203c50` (a
palettised buffer) or `FUN_00203580`. Both write a GS local-to-host transfer into the current VIF1
packet (`BITBLTBUF`, `TRXPOS`, `TRXREG`, then `TRXDIR = 1`), store the destination and its size in
quadwords in the packet's `storeImageTarget` and set its `storeImage` flag. Without a
completion handle they flush and call `p2StoreImage` at once; with one they queue `p2StoreImage` as the
packet's completion callback. Starting such a packet sets `p2StoreImagePending`, which holds every channel
until the read is done.

`p2StoreImage` waits for `GIF_STAT` to go idle, sets `BUSDIR` to 1 and turns VIF1's FIFO around
(`VIF1_STAT.FDR`), then reads the data with up to three VIF1 DMA transfers into memory (`CHCR = 0x100`), each
at most `0xffff` quadwords rounded down to a multiple of 8, waiting for each through the COP0 condition
(`D_PCR = 2`, `p2WaitDmaCondition`). The CPU reads the remainder from the FIFO at `0x10005000`. In
interrupt context it also clears `p2StoreImagePending` and the packet's flag.

### The linked-in microcode is what runs

Nothing in the code references the microcode image at `0x467178`, and a
running game settles it. **PINE cannot read VU memory** (`0x11000000` is outside EE main RAM and
reads back as zeros), but a **PCSX2 savestate carries `vu1MicroMem.bin`, the 16 KiB VU1 micro
memory**, so `scripts/p2s_ram.py` gives it without the emulator running:

* a word unique in the whole 109,184-byte image (`0x10af05ed`, blob offset 16) occurs **exactly once
  in 32 MiB of live EE RAM**, at its linked address, so there is **no heap copy**, and an upload
  must read the image *in place* from rodata;
* **80.7 % of the resident instruction pairs are in the blob** (1,635 of 2,026), and 42.4 % of the
  blob's pairs are resident: the resident code **is** this microcode, not a different build;
* and the mapping is **not identity**: VU1 offset `0` holds image offset **24**, while a second
  resident window maps image offset ~`0x11ac0` to VU1 ~`0x5a8` (a per-program delta). So the engine
  copies each program to a **VU1 address of its choosing**: a program cache, which is what VU1's
  16 KiB against a 109 KB image forces, and the reason the symbol table exists at all.

The 24-byte shift at the start is consistent with `0x467178` being 8 mod 16 and the transfer needing
16-byte alignment. Read this as the explanation of the delta, not as a proven step.

The microcode does not locate itself. No word in the image holds the address `0x467178` or the constant
109184, so the upload does not build the address inline. `B`/`BAL` targets inside the microcode do not
land on the `vu1_entry_*` offsets (0-5 % over 252 branches, against about 2.7 % by chance), so the 237
programs are not entered by branches from inside the image: the EE sets the VU1 program counter. Ghidra
offers no help here, as the extension provides only `r5900:LE:32:default` and no VU language.

## The rest of the layer names itself

Six functions in the region carry a string that identifies them. These are Alchemy's own trace and
error messages, so the identification is recovered rather than guessed:

| address | size | its own string |
| --- | --- | --- |
| `0x001f8050` | 320 | `p2readGSPrivRegister(%d)`, and it does touch the `gs` block |
| `0x0020c270` | 1324 | `Unsupported texture format in p2LoadTexture: %d` |
| `0x001fb710` | 980 | `p2lighting` |
| `0x001f7490` | 72 | `GS csr.id = %d, csr.rev = %d` |
| `0x00207210` | 428 | `swapbuffersPredicate`, `swapbuffersDrawPredicate` (it is `p2InitSwap`) |
| `0x002082f0` | 312 | `textureLoadedPredicate`, `textureDeferredPredicate` |

`p2LoadTexture` is the GS-side texture upload, `p2readGSPrivRegister` the privileged GS readback, and
the two predicate pairs belong to the swap-buffers and deferred-texture paths, i.e. the layer's
outside face. The names in the first column are the *addresses*; the strings are the evidence for
what they are.

### Binding a VRAM buffer as a texture

`igPsx2VisualContext::vfunc_49` (`0x169840`) takes a VRAM buffer index and reads the 0x30-byte
`_pBufList` record at `*(ctx+0x364)+0x10+index*0x30`:

| offset | field |
| --- | --- |
| `+0x00` | px |
| `+0x04` | py |
| `+0x08` | format (8, 7, 0x18, 0xf or 0x10) |
| `+0x0c` | secondary format (0x20 or 0x18) |
| `+0x24` | descriptor index |
| `+0x28` | primary descriptor |
| `+0x2c` | secondary descriptor |

`FUN_0017aa20` pops a free index from the `_pTexList` pool (`+0x144`) and fills a 0x88-byte record: the
primary descriptor goes to `+0x48`, the secondary to `+0x4c`, and `+0x84` = 2. `p2LoadTexture`
(`0x20c270`) allocates from the `FUN_00208210` pool (global `0x56c0c8`) and writes image argument
`+0x30`, px `+0x3c`, py `+0x3e`, format `+0x42`, TBW (`(px+0x3f)>>6`) in word 2 bits 14-19, a size at
`+0x40` and size-1 clamped to 0x1f at `+0x44`. On this path its image argument is 0, because the pixels
are already in VRAM.

## Lighting

The layer's lighting is one function, **`p2lighting` (`0x001fb710`, 980 bytes)**, plus the two it
tails into: it packs the engine's light list into the VU1's 16-byte constant records, and the LIGHT
microcode does the arithmetic. The record stream, the runtime state and light tables, the light
matrix and the call chain are decoded on their own page: [`p2-lighting.md`](p2-lighting.md)
: the pair (LIGHT family,
capability bits) states *what* each program computes, and `p2lighting` states *what it is handed*.

The packs carry serialised `igLightAttr` records (`scripts/pack_lights.py`), but they are prototypes
rather than the running values: the runtime list reads empty at a frame boundary and in every saved
state, and the live rig's colours differ from the records. The shading *model* is the one
above; [`vertex-shading.md`](vertex-shading.md) has the rig read from a live frame.

## Vertex-array draws

`src/engine/p2draw.c` (`0x1f0d10`-`0x1f6f50`) is the layer's vertex-array draw file. The visual
context binds its arrays with `p2SetVertexArrays` (positions, normals, colours, texture coordinates
set 0), `p2SetTexCoordArray` (any of the 16 texture-coordinate sets) and `p2SetSpriteByteArray`, then
calls one draw per primitive. The primitive numbers are the GS `PRIM` types: points 0, lines 1, line
strip 2, triangles 3, triangle strip 4, triangle fan 5 and sprites 6; `p2DrawIndexed*` take a
`unsigned short` index list, and `p2DrawTriangleStrips` draws a list of strip lengths.

Every draw starts the same way:

* a change of primitive marks the render state dirty (`|= 9`) and counts in `p2PrimitiveChanges`;
* whether a colour array is bound decides `p2ConstantColour`, and a change marks `|= 0x11` and counts
  in `p2ColourModeChanges`;
* while a display list is recorded (`p2VertexFormat & 0x20`) the format bits follow the bound arrays
  (normals 1, colours 2, texture coordinates 4; for sprites the sprite-size kind 0x40 or 0x80 and the
  byte array 0x100), the recording render state is rebuilt, and the submit function is
  `p2SubmitRecordedVertices`. Otherwise the bits follow the arrays only when the current program's
  flag bit 22 is set, a dirty render state is flushed with mask `0x1ff`, and the submit function is
  `p2SubmitVertices`;
* a program with flag bit 27 set gets its component scales uploaded first. They come from the
  vertex-data fraction bits, so the bit marks fixed-point components.

Each draw then hands its vertices to the submit function in batches of at most `batchVertexLimit`
(the short at `+22` of the VU buffer layout at `0x491490`). For lines the limit is rounded down to
an even count and for triangles to a multiple of three. Strips repeat one shared vertex (line strip)
or two (triangle strip) at each batch boundary. Fans submit a single batch. `p2DrawIndexedSprites`
passes the same index list to every batch. Each batch also counts in the vertex, primitive and
indexed-vertex statistics that `0x1f6f50` copies out, and in the five counters that `p2StatMask`
selects.

`p2SubmitVertices` and `p2SubmitIndexedVertices` build the VIF packets. They write byte-vector
components with `p2UnpackByteTriples`, `p2UnpackBytePairs` and `p2UnpackBytes`. Each of these copies
an `UNPACK` code and a DMA-tag template from the file's own data, writes the elements, pads with
zeros and VIF no-ops to a quadword, and writes the tag's quadword count last. The packet cursor they
advance is also read as an address to test its alignment. Retail reads it again after every store
through it, so the cursor is a pointer/address union rather than a plain pointer.

The file's data (the `UNPACK`/tag templates from `0x490d40` to `0x490f28`, the no-op words from
`0x4e5010` to `0x4e5100`, the state from `0x569228` to `0x56931c`) runs as one block between
dmaChannel's and p2gs's. Within it, the templates of the three unpack writers lie between templates
that the submit functions use, which is what puts those writers in this file.

Open questions:

* `p2SpriteBytes` (`0x569308`) is a byte-per-vertex array that only sprites unpack. While it is
  bound, the render state draws sprites as triangles. Its meaning is not known; it might be a
  rotation.
* The meanings of the sprite-size kinds that `p2SpriteSizeMode` (`0x569220`) selects are not known.
  Nor are those of the categories behind `p2StatMask` (`0x56bad8`, written only by display-list
  playback) and its five counters.
* `p2SubmitRecordedVertices` passes no index list to `p2SubmitIndexedVertices` when the display-list
  mode is 1. What that mode means is not known.

## State, VU programs, display and display lists

`src/engine/p2core.c` (`0x1e74b0`-`0x1eef70`, types in `include/dw4/p2core.h`) is the layer's front:

* **Capabilities.** `p2EnableCapability`/`p2DisableCapability` set bit `1 << capability` of the current
  program's `p2ProgramFlags` entry and, on a change, run the switch `p2SetCapability`. Capability 9 is
  vertex blending and 27 fixed-point vertex data.
* **GS register images.** `p2GsRegisterSets` holds 15 images of the GS drawing registers, 64-bit each,
  in GS register order (`SCISSOR_1` is register 32, `ZBUF_2` 47, `SIGNAL` 53); program 0 and 1 share
  set 0 and program n above 1 uses set n - 1. A setter writes the field of the current program's context
  (program 0 draws in context 1, the others in context 2), sets bit `0x40` of `p2DirtyFlags` and bit n of
  `p2GsDirtyRegisters` for register n. With multipass rendering (`p2ExtraPassCount`) context 2 follows
  what program 0 sets.
* **VU programs.** `p2VuPrograms` is a 384-entry table read from the built-in program list (lines
  separated by `.`) and the VU1 symbol table: a key, a size, an address once loaded, flags and a name.
  `p2LoadVuPrograms` loads what a draw needs and, when VU1 is full, unloads everything not resident and
  tries once more.
* **Display.** `p2OpenDisplay` and `p2CloseDisplay` set up and take down the GS, the handlers, the
  watchdog thread and the pools; `p2Display` keeps the display and antialias buffer sizes.
* **Display lists.** `p2BeginDisplayList` points the current VIF1 packet at `p2DisplayListPacket`, a
  packet over a 32 KiB heap block; a full block grows the list by a block ended with a DMA next tag,
  and `p2EndDisplayList` closes it with a return tag and shrinks the last block. `p2CallDisplayList`
  calls it with a call tag after `p2PatchDisplayListTextures` fills in the TEX0 writes it left open.

No retail evidence splits the range into several files: its `.data`, `.rodata` and `.bss` each run in
code order with no other object's data between them, and `scripts/same_file_calls.py` finds no static
callee in it. So it is one file.

Open questions:

* Register 30 of a register set is marked with every texture or palette change; which GS register it
  holds is not known (`P2_GS_TEXTURE_30`).
* `p2Clear` with `p2ClearPasses` set draws three passes whose red channel is the pass number times 32;
  what those passes are for is not known.
* `p2ImagePoolSize` (`0x562d80`) is written once and never read.

## Swapping, pools, timers and the small files

From `0x1fc310` to `0x20e750` the layer is a run of whole files. Each file's `.bss` block is used
by its own functions and by nothing else, which is where the cuts come from:

| range | file | what it holds |
| --- | --- | --- |
| `0x1fc310`-`0x1fd5a0` | `p2multipass.c` | multipass stage queries and the pass packet |
| `0x204100`-`0x204e30` | `p2pool.c` | the typed record pools (`include/dw4/p2pool.h`) |
| `0x204e30`-`0x206570` | `p2stateCache.c` | the render-state cache (`include/dw4/p2stateCache.h`) |
| `0x206570`-`0x208170` | `p2swap.c` | frame swap, the FINISH queue and finish sequences (`include/dw4/p2swap.h`) |
| `0x208170`-`0x20cc10` | `p2texture.c` | texture binding and upload |
| `0x20cc10`-`0x20d790` | `p2timer.c` | the clock, sleeping and alarms (`include/dw4/p2timer.h`) |
| `0x20d790`-`0x20d900` | `p2vu1Symbols.c` | lookups in the VU1 symbol table |
| `0x20d900`-`0x20df00` | `p2viewport.c` | the viewport, its scale and the depth bias |
| `0x20df00`-`0x20e080` | `p2vu0.c` | the VU0 lock and request records |
| `0x20e080`-`0x20e400` | `p2vif.c` | VIF row and mask registers |
| `0x20e400`-`0x20e750` | `p2watchdog.c` | the watchdog thread |

* **Swap file before texture.** Every function from `0x206570` to `0x208120` uses only `.bss`
  `0x56bf38`-`0x56c010`, and every function from `0x208170` on uses only `0x56c020`-`0x56c138`.
  `p2InitSwap` creates the finish queue, the finish semaphore and the sequence words that the FINISH
  handler, `p2AddFinishFunc`, `p2NewFinishSequence`, `p2WaitFinishSequence` and `p2GsSignalHandler`
  use, so those five belong to the swap file and not to `p2texture.c`.
* **Timer.** Its `.bss` (`0x56c150`-`0x56c2a0`) runs downward in the order the code first uses it,
  which is how MWCC places one file's file-scope `.bss`. Its `.data` alarm free-list pointer
  (`0x4918c0`) comes before `p2StartTimers`'s template. Both point to one file. The blocks after it
  run upward, so each is a file of its own.
* **Viewport, VU0 and VIF.** These cuts have the least evidence. The viewport's `.bss`
  (`0x56c2c0`-`0x56c318`) and `.data` (`0x4964e0`-`0x4964f8`) are used only by `0x20d900`-`0x20dba0`.
  The VU0 file's (`0x56c320`-`0x56c648`, `0x496500`-`0x496538`) are used only by
  `0x20df00`-`0x20e060`, and the VIF file's (`0x56c650`-`0x56c660`, `0x496540`-`0x4965b0`) only by
  `0x20e080`-`0x20e3f0`. A clean partition is consistent with one file per block, but it does not
  prove that the blocks are separate files.

**Swap and finish.** `p2SwapBuffers` waits while the frames drawn run more than `p2SwapLatency`
ahead of those shown, then either leaves the flip to the vertical-blank handler or shows the new
frame at once. A new frame's VIF1 packet waits on `swapbuffersDrawPredicate` until the buffer it
draws into is off the screen. `p2AddFinishFunc` queues a function behind the packets submitted so far,
and the GS FINISH handler (`p2FinishHandler`) calls it once the GS has drawn them. A finish sequence
is a GS `SIGNAL` id written behind the work: `p2GsSignalHandler` records each id the GS reaches, and
`p2WaitFinishSequence` blocks until a given id has been reached.

**Pools.** Every kind of renderer record (the visual context's `IG_GFX_INTERNAL_STRUCT_*_PSX2`
settings) comes from its own free list. `p2GrowPool` allocates a block when a list runs dry, and the
first record of the block keeps the allocation so that `p2FreePool` can release every block of a
kind. The kinds are numbered: DMA buffers VIF0/VIF1/GIF 0-2, image 3, DMA buffer sizes 4-6, DMA
predicate 7, DMA completion 8, finish 9, texture 10, state cache 11, multipass 12 and display list 13.

**Timer.** Timer 1 counts at BUSCLK/16, and its overflow interrupt extends the count to the 64-bit
clock (`p2ReadClock`). Timer 0 drives the alarms: `p2Sleep`/`p2SleepMilliseconds` queue an alarm
whose delay counts from the alarm before it, and the timer 0 compare interrupt signals the alarms as
their delays run out. Waiting code adds the clock time it spends blocked to `p2DmaWaitTime`,
`p2SwapWaitTime`, `p2FinishWaitTime`, `p2SleepTime` and `p2Vu0LockWaitTime`.

**VU0.** `p2LockVu0` (`0x20dfd0`) waits for the VU0 lock and records an owner tag. The
`"p2lighting"` string that `p2lighting` passes it is that tag. `p2LockVu0` reproduces only as C++, so
it stays a function of its own (`src/engine/p2LockVu0.cpp`) outside `p2vu0.c`.

**Watchdog.** Code that waits on the hardware or another thread sets its bit in
`p2DmaWatchFlags.busy`. The bits are PacketBuffer 0, DMAFinishSequence 1, Swapbuffers 2,
FinishSequence 3, TextureUnbind 4, DMAVIF0 5, DMAVIF1 6, DMAGIF 7, VSync 8, VU0UcodeLoad 9 and VU0Lock
10. Every four seconds the watchdog thread copies `busy` into `seen`. If a bit it copied the previous
time is still set, it prints the VU program tables and the timed-out waits, then aborts. It also gives
up when `p2WatchdogTicks`, which is reset every frame, reaches 60. `p2WatchdogDisabled`
(`0x4965c0`) starts at 1 and nothing clears it.

**Multipass.** With capability 23 on, each texture stage beyond the first draws as a pass of its
own in GS context 2. `p2WritePassPacket` writes a pass's ALPHA/TEX0/TEX1 (from stage pass-1's
register set) and a TEXFLUSH, and `p2GetPassMasks` gives the FRAME/ZBUF masks a pass draws with.

Open questions:

* `FUN_001fcc10` and `FUN_001fd160` are called by `FUN_001762d0` together with
  psx2ParticleFormat's first six functions, in address order, so they might be the head of that
  file. The `.bss` at `0x56b068`, used only by `0x1fd160`, lies below particleFormat's `0x56b070`,
  which argues for keeping them in `p2multipass.c`.
* Nothing writes `p2Vu0Program` (`0x56c320`); it is a 4-bit field of the state-cache key.
* The names `p2SetDepthBias`, `p2SetVifMask`, `p2VsyncSwapPending` and `p2VsyncsWaited` are read from
  behaviour, not from strings.

## What the engine asks for

At the seam, what the engine asks for and in what units:

* the **unit of work is a 48-byte program record** addressed by an index, with a type at `+28` that
  decides code vs data and a size at `+40`, so "which VU program runs" is a table index, and the
  237 names in [`vu1-microcode.md`](vu1-microcode.md) are what those indices select;
* **state reaches the VU1 as a transfer**, not as calls;
* the layer's outside face is small and named: texture upload, GS readback, swap, and lighting.

## Reproducing the measurements

```sh
python3 tools/platform_map.py --elf game.elf --code-lo 0x1f0000 --code-hi 0x20d000
mipsel-linux-gnu-objdump -d --start-address=0x1f0960 --stop-address=0x1f0d04 game.elf
mipsel-linux-gnu-objdump -d --start-address=0x169e30 --stop-address=0x169f80 game.elf
```
