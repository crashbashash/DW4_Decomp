# The `p2` layer — the EE-side renderer

`p2` is Intrinsic Alchemy's PS2/EE backend: the code that turns a render list into VU1 programs and GS
packets. It occupies **`0x1f0000`-`0x20d000` (169 functions, every one of them still named `FUN_*`)**
in [`module-map.md`](module-map.md)'s region table, and it is the interface a native renderer has to
stand in for — which is why the port's settled strategy is to reimplement it rather than emulate the
GS (see `port/docs/project/README.md`).

## The hardware boundary is six functions

`tools/platform_map.py --code-lo 0x1f0000 --code-hi 0x20d000` finds only **6 of the 169** touching a
memory-mapped register, and one of them is the uploader:

| function | size | blocks (the tool's own names) |
| --- | --- | --- |
| `FUN_001f0960` | 924 | `dma_spr`, `dmac`, `dmac_ctrl`, `vif1`, `vu1_regs` |
| `FUN_001f00e0` | 560 | `dmac` |
| `FUN_001f8190` | 400 | `gs` |
| `FUN_001f8050` | 320 | `gs` |
| `FUN_0020cd10` | 656 | `timer` |
| `FUN_001f8350` | 308 | `dma_spr` |

So the whole backend is register-free except for a DMA/VIF/VU1 path and two GS accessors — the rest of
the layer is ordinary code building data for those.

## The VU1 upload path, end to end

This is the answer to "how does the engine get a program onto the VU1", traced with `objdump`:

```
FUN_00169e30(a0, a1, ...)                        the dispatcher (Alchemy core, not p2)
    s0 = *(a0 + 868) -> +16  +  a1 * 48          a1 indexes a table of 48-byte program records
    type = *(s0 + 28)
    if (type == 2)  FUN_00203c50(...)            "Buffer not aligned" -- the code transfer
    else            FUN_00203580(...)            the data transfer
    both are handed the record's +40 and the caller's alignment value

FUN_00203c50 / FUN_00203580                      the two transfer functions
    g = *(0x568F04)                              a single global transfer descriptor
    g->+48 = cursor (advances by 16)
    g->+56 = source
    g->+60 = size
    g->+64 bit 5 = a flag
    FUN_001f0960(g)                              and hand it to the uploader

FUN_001f0960(g)                                  the uploader
    wait for the DMA pointer page  (0x10003020 & 0x1F001FE6 == 6, 100,000-iteration timeout)
    DMA controller: 0x1000E020 = 2               (the dmac_ctrl page)
    VIF1:           0x10003C00 = 0x00800000
    VU1 registers:  0x10005000
    size = g->+60, masked with 0xFFF8            **8-byte units** -- one VU instruction pair
    FUN_001f8190(68)                             the GS accessor
```

Two things in that are worth reading twice. `& 0xFFF8` is the 8-byte unit: a VU micro instruction is
a 64-bit pair, so the transfer is measured in *instructions*, which is what microcode upload looks
like. And the destination is not an argument — the uploader writes the **VU1 registers** and hands the
buffer to the **scratchpad DMA**, so "where it lands" is VU1-relative, not EE-relative.

### The linked-in microcode is what runs

The static trace above leaves one thing open — nothing references `0x467178` — and a
running game settles it. **PINE cannot read VU memory** (`0x11000000` is outside EE main RAM and
reads back as zeros), but a **PCSX2 savestate carries `vu1MicroMem.bin`, the 16 KiB VU1 micro
memory**, so `scripts/p2s_ram.py` gives it without the emulator running:

* a word unique in the whole 109,184-byte image (`0x10af05ed`, blob offset 16) occurs **exactly once
  in 32 MiB of live EE RAM**, at its linked address — so there is **no heap copy**, and an upload
  must read the image *in place* from rodata;
* **80.7 % of the resident instruction pairs are in the blob** (1,635 of 2,026), and 42.4 % of the
  blob's pairs are resident — the resident code **is** this microcode, not a different build;
* and the mapping is **not identity**: VU1 offset `0` holds image offset **24**, while a second
  resident window maps image offset ~`0x11ac0` to VU1 ~`0x5a8` (a per-program delta). So the engine
  copies each program to a **VU1 address of its choosing** — a program cache, which is what VU1's
  16 KiB against a 109 KB image forces, and the reason the symbol table exists at all.

The 24-byte shift at the start is consistent with `0x467178` being 8 mod 16 and the transfer needing
16-byte alignment (the "Buffer not aligned" path in the chain above) — read as the explanation of the
delta, not as a proven step.

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
| `0x001f8050` | 320 | `p2readGSPrivRegister(%d)` — and it does touch the `gs` block |
| `0x0020c270` | 1324 | `Unsupported texture format in p2LoadTexture: %d` |
| `0x001fb710` | 980 | `p2lighting` |
| `0x001f7490` | 72 | `GS csr.id = %d, csr.rev = %d` |
| `0x00207210` | 428 | `swapbuffersPredicate`, `swapbuffersDrawPredicate` |
| `0x002082f0` | 312 | `textureLoadedPredicate`, `textureDeferredPredicate` |

`p2LoadTexture` is the GS-side texture upload, `p2readGSPrivRegister` the privileged GS readback, and
the two predicate pairs belong to the swap-buffers and deferred-texture paths — i.e. the layer's
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
matrix and the call chain are decoded on their own page — [`p2-lighting.md`](p2-lighting.md)
 — and that page is what a reimplemented renderer consumes: the pair (LIGHT family,
capability bits) states *what* each program computes, and `p2lighting` states *what it is handed*.

The packs carry serialised `igLightAttr` records (`scripts/pack_lights.py`), but they are prototypes
rather than the running values: the runtime list reads empty at a frame boundary and in every saved
state, and the live rig's colours differ from the records. The shading *model* to implement is the one
above; [`vertex-shading.md`](vertex-shading.md) has the rig read from a live frame.

## What this gives the port

For a reimplemented renderer the questions are "what does the engine ask for, and in what units", and
this answers them at the seam:

* the **unit of work is a 48-byte program record** addressed by an index, with a type at `+28` that
  decides code vs data and a size at `+40` — so "which VU program runs" is a table index, and the
  237 names in [`vu1-microcode.md`](vu1-microcode.md) are what those indices select;
* **state reaches the VU1 as a transfer**, not as calls — so a port replaces the uploader with a
  "here is program N and its constants" entry point and never needs VIF1 or SPR DMA;
* the layer's outside face is small and named: texture upload, GS readback, swap, and lighting.

## Reproducing the measurements

```sh
python3 tools/platform_map.py --elf game.elf --code-lo 0x1f0000 --code-hi 0x20d000
mipsel-linux-gnu-objdump -d --start-address=0x1f0960 --stop-address=0x1f0d04 game.elf
mipsel-linux-gnu-objdump -d --start-address=0x169e30 --stop-address=0x169f80 game.elf
```
