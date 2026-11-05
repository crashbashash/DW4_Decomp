# The platform boundary

Which functions talk to the EE's hardware, which are the statically linked Sony SDK, and how
much of the game depends on either. This is the map a port needs: every function on it must be
*replaced* rather than recompiled, and nothing else in the image has to be.

It is also the only handle we have on the SDK. The image ships an **empty `.symtab`** (0
entries), so SDK code cannot be identified by name — it has to be identified by what it does.

## Method

`tools/platform_map.py` resolves the addresses the code forms and classifies them against the
EE's register blocks. A `lui rt, hi` is followed for up to eight instructions looking for how
`rt` is used:

* `addiu`/`ori rt, rt, lo` or a load/store with `rs == rt` → the address is known exactly;
* `addu`/`or` with a second register → only the `hi << 16` page is known, which still names the
  block when the whole page lies inside one;
* a call, a `jr`, or any instruction that *writes* `rt` ends the search.

KSEG0/KSEG1 aliases are normalised first, because the SDK reaches some registers cached
(`0x1000F200`) and some uncached (`0xB000F200`). The address-forming rules themselves live in
`tools/mips_literals.py`, shared with the SDK string miner, because both tools need them.
Three measurement traps are worth recording; the first two make a register map see a quarter of the
truth, and all three are the same kind of mistake —
assuming the compiler emits the literal form the manual describes:

* **the window matters** — `lui` is often separated from its use by unrelated instructions
  (including the `nop`s and `lui at,0x57` delay slots the compiler emits in a branch chain). A
  four-instruction window that breaks on a second `lui` and on any SPECIAL opcode resolves ~60
  addresses; an eight-instruction window with a proper "does this write `rt`?" predicate resolves
  **329 of the 402** hardware `lui`s in the image;
* **the page is not the address** — MWCC reaches `0x1000F180` as `lui 0x1001` + a negative
  offset, and `0x10010000` is not a register. Requiring the *page* to be MMIO discards every
  one of those sites;
* **the low half usually lands in a call's delay slot** — `lui a0, 0x4e` / `jal f` /
  `addiu a0, a0, ...` is how every SDK error string is materialised, because the delay slot always
  executes. A scan that treats a call as "control flow leaves" sees the `lui` and none of its uses:
  the string miner's **6** self-named SDK functions and the platform map are
  unaffected (hardware bases are formed inline), but such a scan finds 8 of the 12 library attributions.

## What it finds

**56 functions touch a memory-mapped register** — 19,956 bytes, 0.59 % of the code, and *all 56
are anonymous `FUN_`*. By block:

| block | addresses | functions | registers |
| --- | --- | --- | --- |
| `ipu` | 0x10002000 | 23 | 5 |
| `timer` | 0x10000000 | 21 | 15 |
| `gs` | 0x12000000 | 4 | 15 |
| `dma_spr` | 0x10003000 | 3 | 12 |
| `vif1` | 0x10003C00 | 3 | 11 |
| `vu1_regs` | 0x10005000 | 3 | 14 |
| `dmac_ctrl` | 0x1000E000 | 3 | 9 |
| `dmac` | 0x10008000 | 2 | 15 |
| `intc` | 0x1000F000 | 1 | 1 |

Cross-checked by hand (`objdump`), because the tool's word is not evidence: `FUN_001f8190` is a
switch over a register id whose arms are 14 `lui at,0x1200` GS accesses — a GS register writer;
`FUN_001f00e0` forms `0x10008000`/`0x10009000`/`0x1000a000` — DMA channel registers; the prefix
functions below call the SDK's lazy-init and list-insert helpers.

## The SDK's own code block

Reading the image from the front — the order a static link lays down — the first **177 functions are
anonymous and contiguous**: `0x100008`..`0x10aaa8`, 41,432 bytes (1.2 % of the code). 24 of the 56
MMIO-touching functions are inside it and nothing inside it has a recovered name; **756 `jal` sites
from 633 functions outside** enter it, reaching **33 entry points** (the other 99 distinct targets are
only reached from *inside* the block). One entry alone — `FUN_00100610`, a lock-guarded list walk —
is called from 548 places.

The block is not the whole SDK, and its end is not a boundary with game code: the very next function
is **`SetGsCrt`**, and what follows is the **EE kernel library, already named** — `_Exit`,
`_LoadExecPS2`, `AddIntcHandler`, `AddDmacHandler`, `CreateThread`, `WaitSema`, `SignalSema`,
`FlushCache`, `sceSifSetDma`, `_InitTLB`, `GetMemorySize` (65 functions, `0x10aae0`..`0x10b360`) —
then **168 more anonymous functions** (`0x10b360`..`0x1137a8`, 33,864 bytes) which are the same
library's unnamed body, immediately followed by the platform timer cluster at `0x1146a8`. The first
name that is *not* platform code is `igStrCmp`, at `0x12a4a4`.

So the region `[0x100008, 0x1137a8)` — 75,268 bytes, 410 functions — is the EE's own runtime, and
the call surface into it is the port's shim list:

| region | entry points called from outside | sites | calling functions |
| --- | --- | --- | --- |
| the anonymous head, `0x100008..0x10aae8` | 33 | 756 | 633 |
| head + kernel + unnamed body, `0x100008..0x1137a8` | **127** | **1,364** | **866** |

**41 of those 127 entry points are kernel syscall stubs** — `config/SLUS-20836/syscalls.txt` already lists them,
because they are the `li $v1, N; syscall` wrappers — and 39 carry a recovered name, most of them the
OS API (`CreateThread`, `WaitSema`, `SignalSema`, `CreateSema`, `AddIntcHandler`, `AddDmacHandler`,
`ChangeThreadPriority`, `EnableCache`, `ExitDeleteThread`, …). That named subset is the part of the
surface a port must *implement*; the rest is the C runtime below it.

**The region's extent is not a guess.** `tools/syscalls.py` finds the kernel stubs at
`0x100008..0x114698` — spread across the whole front of the image, the first one being the entry
point itself — so the front region *is* kernel/runtime code, and the platform timer cluster that
starts at `0x1146a8` continues it. The stretch after the named kernel
(`0x10b360..0x1137a8`, 168 functions) is the C runtime too: `FUN_0010d108`, its busiest entry with
60 external call sites, saves `a1,a2,a3,t0,t1,t2` into a stack buffer and installs the buffer in a
global — the `va_list` prologue of the **printf family**.

The named half of that list is what a port replaces first, and it is named for us: `SignalSema`
(56 sites), `ChangeThreadPriority` (28), `WaitSema` (24), `sceSifSetDma`, `FlushCache`,
`AddIntcHandler`, `CreateThread` — the OS API surface.

**Not all of the block is platform code**, which matters for the port's accounting:
`FUN_001007e0` and `FUN_00101380` materialise the typeinfo names `std::bad_alloc` and
`std::bad_exception`, i.e. the block also holds the **C++ runtime**, which a port replaces wholesale
with the host's rather than shimming. 150 of the 177 head functions have no string evidence at all,
so the rest is unmeasured by this method.

## Naming the SDK

The image has no symbol table (`.symtab` is empty), so SDK names can only be *recovered*. One
source produces names that are evidence rather than shape; a second, the library descriptors,
supplies none:

* **a function's own name in a string it references.** The SDK reports errors as `sceXxx: ...` from
  inside `sceXxx`, so a function whose only string is its own name *is* that function.
  `scripts/seed_names_sdk_strings.py` finds them and writes `config/SLUS-20836/names/Sdk.tsv`; it recovered six
  (`sceMcUdCheckNewCard`, `sceMtapPortOpen`, `sceMtapPortClose`, `sceMtapGetConnection`,
  `sceMtapChangeThreadPriority`, `sceMtapGetModVersion`). The same generator reports a second class —
  functions that name a *library* (`libpad:`, `libmc:`, `*.irx`) without naming themselves — which
  attributes a function to an SDK library but is not a name, so those are findings, not symbols:
  `libpad` 0x117b60/0x117c78/0x117ed8, `libmc` 0x1194c0, `libmtap` 0x225300, `libdma`
  0x102c98/0x102d08, the IOP-module loaders at 0x1485c0/0x32dd80/0x332860 and the CRI file layers.
* **the library descriptors** at 0x481000+ (findings [#375](../findings/findings-0251-0500.md#f375)/#382), which hold each library's name
  and version — `libdma`'s block even carries the EE DMA channel
  bases (`0x10008000`, `0x10009000`, …, `0x1000d400`). They are decoded
  ([below](#the-eight-library-descriptors-decoded)): each holds library data and only `libdma`
  carries a function table, so they supply no function names.

## Platform code outside the block

The SDK is not one contiguous region — the link order interleaves it with game code — and the
same map finds it again in clusters:

| address | bytes | blocks | what it looks like |
| --- | --- | --- | --- |
| 0x1146a8..0x1150b0 | 4,300 | timer | a timer/profiling cluster (9 functions) |
| 0x1efb40..0x1f8350 | 4,700 | dmac, dma_spr, dmac_ctrl, vif1, vu1_regs, gs | the DMA/VIF/GS driver (5 functions) |
| 0x20cd10..0x20e080 | 3,200 | timer, vif1 | a second timer cluster (7 functions) |
| 0x2a9210 | 500 | ipu | IPU helpers |
| 0x482ec0..0x4831e8 | 900 | timer | **inside a data region** — see [`data-regions.md`](data-regions.md), [#374](../findings/findings-0251-0500.md#f374): unclaimed code hides in data |

## The platform-side inventory

What a port replaces, with the evidence for each — nothing here is inferred from shape.

| component | evidence | measured size |
| --- | --- | --- |
| **EE runtime**: CRT, C++ runtime, libc, libkernel | syscall stubs span `0x100008..0x114698`; `std::bad_alloc`/`std::bad_exception` typeinfo; the printf `va_list` prologue at `0x10d108`; 39 named OS functions | 410 functions / 75,268 B, `0x100008..0x1137a8` |
| **Sony EE SDK libraries** — libgraph, libdma, libipu, libkernl, libcdvd, libpad, libsdr, libmc | eight descriptors at `0x481000+` holding a name and an ASCII version, **decoded** ([#382](../findings/findings-0251-0500.md#f382)): each holds library *data*, and only `libdma` carries a function table (15 entries at `0x104478..0x105050`) | 12 functions attributed by strings + 6 named + libdma's 15; extents for the other seven unmeasurable this way |
| **CRI middleware** — SRD (file/stream), HTCI, DVCI, PS2RNA, ADXM (ADX sound) | 51 `SRD:`, 48 `HTCI:`, 36 `DVCI:`, 9 `PS2RNA:`, 6 `ADXM:` error strings; the 41 functions referencing them cluster at `0x2716f8` (39 of them, spanning ~39 KB to `0x27b188`), the sound layer at `0x37e070` | 41 functions at `0x2644d8..0x27b188` |
| **The IOP side** — 11 `.irx` modules + `IOPRP280.IMG` | the loader functions name the modules they load: `sio2man`/`padman`/`mtapman` (0x1485c0), `libsd`/`igFileIO` (0x32dd80), `cri_adxi`/`sdrdrv`/`sndfi` (0x332860), `mcman`/`mcserv` (0x3ad5b0), `igAudio` (0x1439d0) | the modules themselves are on the disc, not in the image |
| **Hardware** | the 56 MMIO-touching functions, all anonymous | 19,956 B |
| **The game** | `Gap::` RTTI names (1,744 `Gap::` strings) and the recovered `ig*`/`be*` names | the decompilation target |

**A limit worth stating plainly:** the *extent* of any single SDK library cannot be delimited from
outside. Anonymity is not a boundary signal — 13,249 of the image's 18,661 functions are anonymous
`FUN_` — and strings mark a library only where it happens to report errors. This is a **proof**,
not a suspicion: the eight descriptors are decoded ([#382](../findings/findings-0251-0500.md#f382)) and only
`libdma` contains a function list, so no other library's extent can be read off them. The counts in
this table are *floors* over evidence, not totals.

## The eight library descriptors, decoded

`0x481000+` holds eight records ([#382](../findings/findings-0251-0500.md#f382)), each a 16-byte header: a 12-byte space-padded library name
and a 4-byte **ASCII version**.

| descriptor | version | payload |
| --- | --- | --- |
| `PsIIlibgraph` `0x481c20` | 2800 | two u16 pair tables, no pointers |
| `PsIIlibdma` `0x481c60` | 2800 | the ten EE DMA channel register bases `0x10008000`..`0x1000d400`, then a **15-entry function table** |
| `PsIIlibipu` `0x481dc0` | 2800 | the MPEG-2 DCT quantisation tables — an intra zig-zag matrix and the all-16 non-intra default |
| `PsIIlibkernl` `0x481e40` | 2800 | the C heap base `0x0058d280` (the same value the CRT passes to syscall 61), one code pointer, a long `0xffffffff` run |
| `PsIIlibcdvd` `0x483540` | 2800 | no pointers |
| `PsIIlibpad` `0x4850f8` | 2800 | eleven string pointers — the status names ERROR / STABLE / EXECCMD / FINDCTP1 / DISCONNECT / BUSY / FAILED / COMPLETE |
| `PsIIlibsdr` `0x485148` | 2800 | no pointers |
| `PsIIlibmc` `0x485180` | **2810** | driver structures on an 88-byte stride |

The version is real and per-library: `mc` is SDK 2.8.1 against everyone else's 2.8.0 — the same
`280` as the disc's `IOPRP280.IMG`. The records are unreferenced (no word in the image holds any of
the eight addresses), so they are linker metadata the game never reads. `tools/sdk_bindings.py`
decodes them into `data/sdk-bindings.json`.

**One table is still worth having.** libdma's fifteen entries are real entry points, and **three of
them are boundaries a function tiling without the table misses**: `0x104478` and `0x1044f0` sit inside
the 728 bytes that otherwise read as one `FUN_00104258` and are actually three functions — every
boundary lands exactly where the
next begins — and `0x105050` begins exactly at `FUN_00104f30`'s end, with MMI ops rather than a
prologue. The descriptor is therefore a **split oracle**, and the tiling carries those three
boundaries: `FUN_00104258`, `FUN_00104478` and `FUN_001044f0` are separate functions and `0x105050`
is `FUN_00105050`.


### How that table is reached (a method warning)

Nothing points at libdma's table and nothing calls its entries: each of the sixteen has exactly one
reference — its own word in the table — and a scan of every `jal` in the image finds **zero** call
sites into them. It is still live. At `0x1041d8` the code does

```
lui   a1,0x48
addiu a1,a1,0x1cb8     ; 0x481cb8 -- the table's NINTH entry, not its start
sll   v0,v0,0x2
addu  v0,v0,a1
lw    a2,0(v0)         ; dispatch through table[index]
```

so the table is indexed through a base anchored *mid-table*, and its own start address (`0x481c98`)
is formed nowhere. **Stored-pointer, computed-base and direct-call xrefs each miss all or most of
it**, which is how a live dispatch table reads as dead code ([#387](../findings/findings-0251-0500.md#f387)). Resolve `lui`/`addiu` pairs
before concluding a table is unreachable.

Disassembly also confirms what the pointer alone suggested: `0x104478` follows
`FUN_00104258`'s stack restore and begins with `a0`-relative descriptor loads plus `mtsab`/`lq`
(unaligned quad access — the MMI idiom for a block move), and `0x105050` follows a `jr ra; nop`
with an MMI mask idiom (`pnor`/`psrlh`/`psllh`). Both are argument-taking MMI block-copy kernels of
the kind a DMA driver has, not data tables.

Two further things live in the same window and are recorded because the port needs them, not the
decompilation: the **VU1 microcode's own symbol table** at `0x491910` ([#383](../findings/findings-0251-0500.md#f383)) — about 150
`vu1_entry_*`/`vu1_end_*` pairs with byte offsets, the complete map of the renderer's microcode from
`UCODE_BEGIN;0` to `UCODE_END;109184` — and the middleware's build strings ([#384](../findings/findings-0251-0500.md#f384): `SJ/PS2EE
Ver.6.28`, `ADXRT Ver.2810`, `PL2ENC Ver.1.01`, all built 2004-10-06).

## The engine's own platform seam

The SDK is not what the game calls. The engine — a cross-platform middleware family (`ig*`) — is
written against **generic** platform classes, and the PS2 implementations sit underneath them:
**32 classes named `igPsx2*`, and 32 of 32 derive from a non-PS2 base** (recovered from the
registrar's `fn2` base, `data/class-hierarchy.tsv`).

| area | the engine calls | the PS2 class | so a port implements |
| --- | --- | --- | --- |
| threads, sync | `igThread`, `igSemaphore`, `igThreadManager` | `igPsx2*` | pthreads |
| time | `igLongTimer` | `igPsx2LongTimer` | a monotonic clock |
| files, media | `igFile`, `igFolder`, `igMedia` | `igPsx2File`, `igPsx2Folder`, `igPsx2Media` | POSIX + an ISO reader |
| input | `igController`, `igControllerManager` | `igPsx2*` | SDL2 gamepads |
| audio | `igAudioContext` | `igPsx2AudioContext` | SDL2 / OpenAL |
| graphics | `igVisualContext`, `igWindow`, `igImage`, `igClut`, `igImageConvert`, `igIndexArray`, `igVertexArray1_1`, `igVertexArray2`, `igVertexStream`, + the `*Ext` shader family | `igPsx2*` | the new renderer |
| EE ↔ IOP RPC | — (`igPsx2IopRpcConnection`'s base is `igObject`, so it *is* the seam, not an implementation) | `igPsx2IopRpcConnection` | *deleted*: the IOP modules become native code |

**This is the port's real boundary, and it is narrow.** The game and the engine talk to the generic
bases, so implementing those 32 interfaces for the host is what a port does — the engine's own logic
then runs unchanged. The seam is ~32 classes wide, *not* 18,661 functions and *not* the 127 SDK entry
points this page measures elsewhere.

It also answers the two questions a port actually asks:

* **What is the SDK used for?** Threading and synchronisation, timers, files and CD media, controller
  input, audio, and graphics — the areas in the table. The hardware driver functions (libdma,
  libgraph, libipu) are reached *from* these classes rather than from game code.
* **What replaces libdma?** Nothing Linux-native, because it is not a Linux-shaped dependency. libdma
  drives the EE's DMA controller: it moves chain lists to VIF1/GIF (rendering), SIF0–2 (the EE↔IOP
  path that carries pad, file, audio and memory-card traffic), IPU (MPEG FMV) and the scratchpad. A
  port has no bus to move data across, so the "transfer" becomes an ordinary call that consumes the
  same chain data out of RAM and dispatches to the sink — a new renderer for VIF1/GIF, native code
  where the IOP modules were, `ffmpeg` for the IPU path, and no sync semantics at all (`libdma: sync
  timeout` has no counterpart when the call is synchronous).

The correlated consequence is stated plainly in the naming section above: the *names* of SDK
functions are largely irrelevant to a port, because a port replaces the classes that call them.

## Open questions

* **How much of the surface is libc rather than kernel?** The extent is settled (the syscall stubs
  span it) and 41 of the 127 entries are syscall stubs, but the remaining ~86 are split between libc
  / the C++ runtime — which a port replaces with the host's and never shims — and SDK library
  internals it must. Separating them needs the printf/string/math families identified by shape, not
  by address.
* **Who calls the runtime?** Of the 1,364 call sites into the region, only **2 come from functions
  with a recovered engine name** (the `ig*`/`Gap*`/`be*` names); the rest come from functions that are
  still anonymous. So this surface measures *the game's dependency* but does not yet separate the
  engine's own calls from the SDK libraries' internal ones (CRI's file and audio layers, for
  instance, are themselves callers).
* **The GS is mostly programmed elsewhere.** Only four EE functions touch GS registers, while the
  VIF/DMA blocks are busy: this game, like most PS2 titles, sends its rendering through DMA chains
  into the VU1 microcode. A port's renderer therefore depends on the *VU1 program and the packet
  formats*, not on EE register code — the EE-side work is the smaller half.
* **Timer functions may be game code.** The `timer` block is the largest by function count, and
  the game plausibly reads the timers itself (profiling, frame timing). Splitting SDK timing from
  game timing needs a call-graph look, not a register look.
* **Most entry points are still unnamed, and the names are not in the shipped data.** Measured
  ([#385](../findings/findings-0251-0500.md#f385)): `game.elf` names 6 SDK functions in their own error strings, `IOPRP280.IMG` keeps 16
  `sceCd*` names — in `cdvdman`, the only one of its sixteen embedded modules with a name table — and
  all eleven extracted `MODULES/*.IRX` are stripped (`readelf -s` finds 0 function symbols). Beyond
  those 22, SDK function names exist only in Sony's headers, so naming them would be documentation
  rather than recovery; the descriptors cannot supply them either ([#382](../findings/findings-0251-0500.md#f382)). What *is* recoverable is
  **attribution**, and the one bounded naming route left is the cdvd join: those 16 names are
  `cdvdman`'s exports by number, and the EE-side `libcdvd` wrappers call them by RPC command number,
  so the two match up by number (T12).
