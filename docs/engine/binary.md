# Binary & Toolchain

## Disc / product identity
| Field | Value |
| --- | --- |
| Title | Digimon World 4 (USA) |
| Product code | `SLUS-20836` (executable), save dir `BASLUS-20836savedata` |
| `SYSTEM.CNF` | `BOOT2 = cdrom0:\SLUS_208.36;1`, `VER = 1.01`, `VMODE = NTSC` |
| Region | NTSC-U (USA) |
| Platform | PlayStation 2 (Emotion Engine / IOP) |

### Extracted ISO contents (reference)
```
SYSTEM.CNF            boot config
SLUS_208.36           main EE executable (ELF)
NDMW.AFS              727 MB  CRI AFS archive (game data + Lua scripts)
AREA.AFS              511 MB  CRI AFS archive (FMV + level data)
OUTER.DAT             204 MB  (unexplored)
NDMW.IGB              106 KB  igBinary serialized data
CDVD.FIC              lists ndmw.igb / area.afs / ndmw.afs
MODULES/              IOP modules + IOPRP280.IMG
  CRI_ADXI.IRX, IGFILEIO.IRX, LIBSD.IRX, MCMAN.IRX, MCSERV.IRX,
  MTAPMAN.IRX, PADMAN.IRX, SDRDRV.IRX, SIO2MAN.IRX, SNDFI.IRX, USBD.IRX
```

## Main executable (`SLUS_208.36` = `game.elf`)
| Field | Value |
| --- | --- |
| Format | ELF32, little-endian (`elf32-tradlittlemips`) |
| Machine | MIPS R3000 (readelf) → actually **R5900 (Emotion Engine)** |
| `e_flags` | `0x20924000` → `5900`, `eabi64`, `mips3` |
| Entry point | `0x00100008` |
| Type | `EXEC` |
| Section headers | 8 (`.shstrtab`, `.strtab`(0), `.symtab`(0), code, bss, `.comment`, `.reginfo`) |
| Symbols | **stripped** (`.symtab` size 0); game code is `FUN_*` |

### Program headers
| # | Type | VirtAddr | FileSz | MemSz | Flags |
| --- | --- | --- | --- | --- | --- |
| 0 | LOAD | `0x00100000` | `0x454b00` | `0x48d280` | RWE |
| 1 | LOAD | `0x0058d280` | 0 | 0 | RW (end marker) |

- Loaded image: `0x00100000` … `0x00554b00` (file-backed).
- **BSS**: `0x00554b00` … `0x0058d280` (zero-initialised; all runtime globals live here).
- Single code/data section at `0x00100000`, size `0x454b00`, flags **WAX** (self-modifying-capable, typical for PS2).

### Memory map at runtime (measured)

The C runtime sets memory up from two EE kernel calls in its startup code
(`0x100198`..`0x1001e8`), and both take their arguments as **immediates in the code**:

| call | arguments | meaning |
| --- | --- | --- |
| syscall 60, `SetupThread` | `gp = 0x0055C870`, stack `0x01F00000`, size `0x00100000` | the main thread's stack is the **last megabyte of RAM**, `0x01F00000`–`0x02000000`; the call's result is moved straight into `sp` |
| syscall 61, `SetupHeap` | `heap_start = 0x0058D280` (the byte after BSS), `heap_size = -1` | **the C heap starts at the image's end and runs to the top of memory**; `-1` means "everything left" |

The syscall numbers are pinned by the repo's own table, which lists `EndOfHeap` as 62
(`config/SLUS-20836/syscalls.txt`); 60 and 61 are the two immediately before it. Measured live from an in-world
save state:

- `0x0058D280` holds allocator structures (a few small words, then zeros);
- the **first 8 MB above the image is 57.8 % non-zero**, with live data reaching `0x00D77D31`: about
  **8.3 MB of heap in use**, so the heap is used from its first byte;
- the stack's live frames sit just below `0x02000000` (`0x01FFF000` holds words that are return
  addresses into the loaded section), and `0x01E00000`–`0x01F00000` is untouched.

**So the space above the BSS is not free: it is the game's working memory.** It is nevertheless
*movable*: `heap_start` is an argument to a call that this repo **re-links**, so a mod region can be
placed at `0x0058D280`…`0x0058D280+N` with `SetupHeap` given `0x0058D280+N`, and segment 0's
`FileSz`/`MemSz` grown by `N` so the region is file-backed. The cost is `N` bytes off the game's
heap (≈8.3 MB live against ≈26 MB of address space; the game's *peak* is unmeasured). Taking this
route means the CRT startup has to be built from source rather than linked as the committed
disassembly, which is ordinary decompilation work.

Two addresses in that range recur as code immediates (`0x008BA000`, `0x00979680`) and are **not**
anywhere as data; whether they are hardcoded pool bases or bit patterns is unresolved, and it only
matters if a mod region is megabytes deep.

### Rebuilding the image with a mod

The loadable image is one flat blob, and the build reproduces it **only while every unit keeps its
size**, which the generated linker script now enforces a unit at a time.

- `tools/linkgen.py` emits `. = <offset>;` before every unit, pinning it to its retail address
  (`. ` is an offset from the section start inside an output section, so an absolute VA would prefix
  1 MB of zeros; measured). For a matched build this changes nothing and the byte-for-byte
  comparison still holds; what it buys is that a **modified** unit may compile smaller or larger than
  its retail slot without shifting any neighbour, so every absolute address baked into the committed
  disassembly stays valid. A unit that outgrows its slot is a loud ld error, not a silent
  misplacement.
- **`make link`'s own output boots.** Measured: `build/game.elf` goes onto a disc and the game plays
  (one LOAD at `0x00100000`, entry `0x100008`, and the CRT clears BSS itself, so the segment's
  `MemSiz == FileSz` is fine).
- A later step splices the linked section back into a copy of the retail ELF.
  That is not needed to boot; it is what makes a mod *small*: the linked file is 7.3 MB because ld
  pads its segment and adds a separately named `.exceptix` section. Retail retains exception-index
  data within its flat image ([combat example](../systems/combat-reference-helpers.md#retail-unwind-identities)). A retail-shaped file
  of 4,541,744 bytes lets the disc be patched **in place**, so the ISO keeps its exact size and a mod
  is the bytes it actually changes.
- The file is then written into the disc image (see below).

**Measured end to end** (a patch that forces Very Hard by ignoring
the difficulty argument): the patch compiles, `linkcheck` reports **15 differing bytes**, all inside
`SYSsetDifficulty` (`0x371dd4`–`0x371de7`); the spliced ELF is retail-sized with those same
15 bytes; the repacked ISO is **the same 1,448,902,656 bytes as the master and differs in exactly 15
bytes**; and that disc boots and plays.

What that means for how much a mod can change today:

- **Any function can be replaced**, not only the 7,462 decompiled ones. The decompilation is what
  makes a change readable, not what makes it possible. The constraint is space, not coverage: a
  unit may grow only into slack a shrunk unit left, and retail's tiling is gap-free.
- **Additions beyond the section** need the two things the memory map implies: the ELF container
  grown (`FileSz`/`MemSz`) and the heap moved up, because the heap starts at the image's end.

### Memory map at runtime (measured)

The C runtime sets memory up from two EE kernel calls in its startup code
(`0x100198`..`0x1001e8`), and both take their arguments as **immediates in the code**:

| call | arguments | meaning |
| --- | --- | --- |
| syscall 60, `SetupThread` | `gp = 0x0055C870`, stack `0x01F00000`, size `0x00100000` | the main thread's stack is the **last megabyte of RAM**, `0x01F00000`–`0x02000000`; the call's result is moved straight into `sp` |
| syscall 61, `SetupHeap` | `heap_start = 0x0058D280` (the byte after BSS), `heap_size = -1` | **the C heap starts at the image's end and runs to the top of memory**; `-1` means "everything left" |

The syscall numbers are pinned by the repo's own table, which lists `EndOfHeap` as 62
(`config/SLUS-20836/syscalls.txt`); 60 and 61 are the two immediately before it. Measured live from an in-world
save state:

- `0x0058D280` holds allocator structures (a few small words, then zeros);
- the **first 8 MB above the image is 57.8 % non-zero**, with live data reaching `0x00D77D31`: about
  **8.3 MB of heap in use**, so the heap is used from its first byte;
- the stack's live frames sit just below `0x02000000` (`0x01FFF000` holds words that are return
  addresses into the loaded section), and `0x01E00000`–`0x01F00000` is untouched.

**So the space above the BSS is not free: it is the game's working memory.** It is nevertheless
*movable*: `heap_start` is an argument to a call that this repo **re-links**, so a mod region can be
placed at `0x0058D280`…`0x0058D280+N` with `SetupHeap` given `0x0058D280+N`, and segment 0's
`FileSz`/`MemSz` grown by `N` so the region is file-backed. The cost is `N` bytes off the game's
heap (≈8.3 MB live against ≈26 MB of address space; the game's *peak* is unmeasured). Taking this
route means the CRT startup has to be built from source rather than linked as the committed
disassembly, which is ordinary decompilation work.

Two addresses in that range recur as code immediates (`0x008BA000`, `0x00979680`) and are **not**
anywhere as data; whether they are hardcoded pool bases or bit patterns is unresolved, and it only
matters if a mod region is megabytes deep.

### Rebuilding the image with a mod

The loadable image is one flat blob, and the build reproduces it **only while every unit keeps its
size**: `build/link.ld` lists the 33,085 units in address order and contains **no `. = addr`
directives**, so a unit that compiles to a different length shifts every unit after it. Two facts
make such a shift fatal rather than merely inconvenient:

- the generated remainder (`asm/`) is raw `.word`s (an address inside it is a literal, not a
  relocation), so anything that moves invalidates the addresses baked into it;
- retail's tiling is **gap-free**: every byte of `0x00100000`–`0x00554b00` belongs to some unit, so
  there is no slack for a function to grow into.

So:

- **Same-size edits work today and need nothing else.** The rebuilt section is byte-identical
  everywhere else, so the mod is written into the disc in place. That is what
  `dw4_yellowcrown/patch_iso.py` and `set_disc_serial.py` do, and why both refuse a length change.
  Keeping the mod's new code inside the modified unit's own bytes (padding to the original length)
  keeps this true, and covers any edit whose compiled form fits the slot it replaces.
- **A size-growing mod needs a home for its code, and there is no proven one.** The candidate is
  above the BSS, past `0x0058d280`, reached by growing segment 0's `FileSz` and `MemSz` together so
  that the BSS hole (`0x00554b00`–`0x0058d280`, 231,296 bytes) becomes file-backed zeros. But that
  address is also where the SDK's heap is likely to start, and whether it does has not been measured,
  so this is a hypothesis. The alternatives are both real work: pin every unit with `. = addr` in the
  generated script, so a modded unit may grow into slack a shrunk one left (retail has none, so this
  needs a second generation), or make the remainder's addresses relocatable so units may move at all.
- On the disc the boot ELF sits at **LBA 289** with 17 files behind it (down to `OUTER.DAT` at
  607458) and only **14 free sectors** at the end of the volume, so a section that *does* grow cannot
  be written in place: the file is appended and its ISO9660 directory record re-pointed (a record
  holds its extent and length as 8-byte both-endian fields, and the volume space size likewise). This
  was verified by booting a grown image.

### Entry point (`0x00100008`)
Disassembles to `padduw`-based register zeroing, an **EE MMI** instruction, which
confirms the `r5900` language is required (plain MIPS would mis-decode it):
```
100008: 70000c28  padduw  at,zero,zero
10000c: 70001428  padduw  v0,zero,zero
...                                (all 32 GPRs)
10007c: 00000011  mthi    zero
100080: 70000011  mthi1   zero
```

### Ghidra import
- Language: **`r5900:LE:32:default`** (correct; the ELF's `5900` flag lets the
  opinion system select it automatically; no `EF_MIPS_MACH_5900` patch needed).
- Dumps produced: **15,167 functions**, **28,784 strings**.

## Compiler & middleware
| Item | Evidence |
| --- | --- |
| Compiler | `"MW MIPS C Compiler (2.4.1.01)"` @ `0x00000000`-adjacent `.comment` → Metrowerks CodeWarrior for PS2 |
| CRI audio | `ADXRT  Ver.2810 Build:Oct  6 2004`, `PL2ENC Ver.1.01` |
| CRI libraries | `CRI_ADXI.IRX`, `SNDFI.IRX` IOP modules |
| Sony SDK | 80 kernel syscall stubs, 16 bytes each (`CreateThread`, `AddIntcHandler`, `SetGsCrt`, `sceSifSetDma`, …); see [Kernel syscall stubs](#kernel-syscall-stubs-80) and `config/SLUS-20836/syscalls.txt` |
| C++ runtime | `std::exception`, `std::bad_alloc`, `std::bad_exception`, RTTI |
| Video | MPEG-2 decoder strings (`slice_start_code`, `macroblock_address_increment`) |
| Graphics data | PNG decoder (zlib), full CRC32 impl at `0x00221a20` |
| Engine | `ig*` object system (see `docs/engine/reflection-metadata.md`) |

## Kernel syscall stubs (80)

All 80 are the PS2 SDK's `libkernel` stubs, and they are the only SDK names in the
binary. Each is exactly 16 bytes:

```
li    $v1, <number>      # 24030000 | number  (addiu v1, zero, N)
syscall                  # 0000000c
jr    $ra
nop
```

**80 stubs / 1,280 bytes / 68 distinct numbers**, at `0x0010aae0..0x00114070`. Fifteen use
the `0xFF80..0xFFFF` range (`i*`, `_i*`, `isceSif*` variants, the interrupt-control
entry points), e.g. `iResumeThread` = 65478, `_iEnableIntc` = 65510; the rest are 2..131
(`SetGsCrt` 2, `_Exit` 4, `SleepThread` 50, `FlushCache` 100). The number is read from the
bytes; the *name* comes from the SDK's published syscall table. The ELF has no symbol
table, so the names are inferred, the numbers are not.

Five copies of syscall 90, five of 116 (`RFU116_SetSyscall`) and three of 91 exist at
different addresses (`0x001137b8`, `0x001141b8`, `0x00114220`, …): the game links the same
stub in more than once, which is also why `tools/split.py` suffixes duplicate names with
`__<va>`.

`config/SLUS-20836/syscalls.txt` is the generated table (`tools/syscalls.py`). The m2c pipeline
**skips** these (worklist status `sdk`) because there is no game C to recover and none
can be written: MWCC's integrated assembler rejects the `syscall` mnemonic in an inline
`asm` block (`unexpected end of line`), so the bytes cannot be reproduced from `src/`
either. They stay in `asm/`, and `make link` rebuilds them from the retail bytes.

Three functions *use* a syscall inline but are real game code, recorded with number `-`
and **not** skipped: `entry` (`0x00100008`), `iWakeupThread`, `iSuspendThread`.

Sample of the non-`i` stubs:
```
0x0010aae0 SetGsCrt   2     0x0010ace0 CreateThread      32
0x0010ab00 _Exit      4     0x0010ad20 ExitDeleteThread  36
0x0010ab20 _LoadExecPS2  6  0x0010ade0 ReferThreadStatus 48
0x0010abc0 AddIntcHandler 16   0x0010aee0 CreateSema   64
0x0010abf0 AddDmacHandler 18   0x0010b1b0 sceSifStopDma 107
0x0010b2a0 sceSifSetDma 119   0x0010b2e0 sceSifSetReg  121
```
**No game-specific *symbol* survives.** Every gameplay function name in `data/functions.json`
is a later recovery (RTTI/vtables, reflection), not an original symbol.

## Notes for re-analysis
- Never re-import into a new Ghidra project: reuse `ghidra-projects/dw4/dw4`.
- Run a PyGhidra script with the project's own launcher (the `pyghidra-run` and `ghidra-post` wrapper names used on
  other pages are the same thing; they are not installed commands):
  `GHIDRA_INSTALL_DIR=<ghidra> local/pyghidra312-venv/bin/pyghidra --project-path ghidra-projects/dw4 --project-name dw4 --skip-analysis orig/SLUS-20836/SLUS_208.36 scripts/<script>.py <script args>`.
  The options go before the binary and the script path comes right after it. `--project-path` is the folder that
  holds `dw4.gpr`; passing the project folder itself creates a stray nested project. Run one Ghidra process at a time.
  For a one-off decompile, `<ghidra>/support/analyzeHeadless ghidra-projects/dw4 dw4 -readOnly -noanalysis -process
  -postScript <script>` also works.
- The ELF's BSS region (`0x00554b00`+) holds every runtime global referenced in
  these docs; addresses are stable across loads (no PIE/ASLR on PS2).
