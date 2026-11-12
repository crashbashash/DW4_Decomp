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
| `FUN_0020cd10` | 656 | `timer` |
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
| `0x00207210` | 428 | `swapbuffersPredicate`, `swapbuffersDrawPredicate` |
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
