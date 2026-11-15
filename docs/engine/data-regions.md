# The data regions: what is in the 1.4 MB that is not code

`tools/datamap.py` divides the image into code and data. Its headline is the data the source defines and
`make check` compared with retail; the rest it classifies from the recovered metadata (see
[`progress-metrics.md`](progress-metrics.md)). This page is the identification step behind that
classification: what the regions actually are, and so which units their data belongs to.

The starting fact is that the unclassified data is **highly concentrated**: 20 regions hold
880,360 of the 1,162,652 unclassified bytes (76 %), and three of them hold 642 KB between them
(the "one 644 KB block" `tools/layout.py`'s docstring mentions, which is really three regions).

The method is three cheap measurements over each region, all reproducible:

* **composition**: each 32-bit word classified as a small integer, a plausible IEEE-754 float, a
  pointer into the image, or zero;
* **pointer targets**: where a pointer's value lands: code, another data region, the string dump
  (`data/strings.json`), or `.bss`;
* **printable runs**: ASCII sequences of six characters or more, which name most of these regions
  outright.

## Which library owns what

The linker lays data out by section and, inside a section, in the same object order as the code, so
the library whose code forms an address most is that data's owner, and owners run in link order.
A class's RTTI record, its name, its base list and the copies of its base classes' records beside
it are reached only from its vtable, so they count for the library whose code fills the vtable's
metaobject slot (20); without that, a unit whose data opens with RTTI starts at its first
code-formed address instead.
`scripts/data_owners.py` measures this into `config/SLUS-20836/data-owners.tsv`, with `make rules`
checking it is current. Each section opens with the first object of the link, the Metrowerks runtime:

| Section | Starts | Note |
| --- | --- | --- |
| 0 | `0x481c00` | |
| 1 | `0x4d1c18` | the first datum the code names; the read-only sequence itself opens at `0x4d1c00` with `"std::exception"`, which New emits |
| 2 | `0x522440` | holds the vtables |
| 3 | `0x554f00` | `.bss`, past the end of the file image at `0x554b00` |

The table is in link order by construction: the heaviest in-order chain stands, and each section's
comment counts the references left out. They are about 13 % of the total, mostly widely shared
globals, such as the object system at `0x586dc8`, that one library defines and others reach more.
An owner is who reaches the data, so for those it can be the wrong library.

## The five that are identified

| region | bytes | composition | what it is |
| --- | ---: | --- | --- |
| `0x521750` | 209,840 | 79 % code pointers | **the vtable region.** 6,613 runs of code pointers, most 21–23 long, each preceded by a `[rtti, 0]` header, the layout the 478 vtables in `data/vtables.json` have. That dump came from the RTTI records, so this region holds the vtables of the classes with **no** RTTI (980 class vtables are extracted in total). Its first 828 words are code, not data (§below) |
| `0x4833c8` | 321,816 | 44 % pointers, 33 % zero | **Sony SDK library metadata + embedded VU1 microcode.** Strings: `PsIIlibcdvd 2800`, `PsIIlibpad 2800`, `PsIIlibsdr 2800`, `PsIIlibmc 2810`, plus VU program metadata (`EXECUTE_PATH;1073741824;;131077;;;;.EXECUTE_RENDERLIST;…`, `vu1_entry_UCODE_BEGIN;0;vu1_entry_EXECUTE_PATH;16;vu1_end_EXECUTE_PATH`) and `Error decoding compressed text` |
| `0x467108` | 110,536 | packed records: 4,465 words of `0x2ff`, 3,515 of `0x8000033c` | **the VU1 microcode** from `0x467178` to `0x481bf8`, the 109,184 bytes `UCODE_END` gives; those two words are the VU's upper and lower nops. The Sony library descriptors follow it: `PsIIlibgraph2800`, `PsIIlibdma  2800`, `PsIIlibipu  2800`, `PsIIlibkernl2800` |
| `0x50005c` | 54,724 | 11 % pointers, 1,688 ASCII runs | **reflection metadata**: the class and field name/descriptor arrays behind the MetaObject field tables (`Gap::igAdxFile`, `Gap::Core::igNamedObject`, `_ptNumber`, `_fileNumber`) |
| `0x4d7020` | 30,720 | 31 % floats, 893 ASCII runs | **the engine string table plus IOP module names**: `sio2man.irx`, `padman.irx`, `mtapman.irx`, `supportMultitap`, `IG_GFX_INDEX_SIZE_16_BIT`, `error creating visual context` |

Two consequences worth stating:

* **The IOP modules are not stored here.** The SDK strings suggest otherwise, but an IRX image
  would carry the `0x7fELF` magic and the whole image contains exactly one such word, outside these
  regions. What is here is the *library version strings* the SDK registers, relevant to
  [`binary.md`](binary.md).
* **`0x4833c8` is not one object.** Its 321,816 bytes are the whole initialised-data sequence of the
  link from there, every library's tables and strings in link order; the SDK version strings and the VU
  program metadata are only what names its first stretch. `tools/datamap.py` therefore classifies it
  datum by datum, like every other region: strings, pointer tables and vtables by their extents, the
  rest from the addresses code and pointers name (`data/data-layout.tsv`, `scripts/data_layout.py`).
  The microcode, the descriptors and the kernel patch arrays are `config/SLUS-20836/regions.tsv` rows
  and count as whole regions. Identifying a region does not decompile it: its bytes count as matched
  only once the unit that owns them defines them.

## The bytes between identified data

At commit `1a005257b` the classification left 277 spans, 6,742 bytes, as `?`. They fall into a handful of
patterns, each now a rule of `scripts/data_layout.py` or `tools/datamap.py`; 451 bytes in 13 spans stay
`?` because no rule reaches them.

* **The vtable section holds only vtables.** MWCC compiles each class's vtable into its own section, and
  retail's runs from the static-initializer table at `0x522440` to the exception metadata at `0x542ae0`.
  A pure virtual function's slot is zero, so an abstract class's vtable is mostly zeros with a function
  or two among them (`beSaveApi`: slots 21-23 zero, `vfunc_24` at `0x53c0d8`; 26 `vfunc_N` symbols sit
  past a zero slot at their own slot number). Every one of the 977 dumped vtables starts 16-aligned, as
  every matched MWCC datum of 16 bytes or more does, so zeros of 16 bytes or more before the next vtable
  are slots, not padding. Outside the section a `[0, 0]` pair before a function table is padding, not a
  vtable header: 197 such guesses in `.data` cut a matched table's padding into `?`.
* **Pointer tables hold nulls and records.** CRI's device interfaces (DVCI, HTCI, MFCI) are 26 function
  slots with the unimplemented ones null; MWCC's RTTI base lists are `{type_info *, offset}` records
  ending in a zero record, and the type_info records they name are `{name, bases}` pairs; game tables
  are `{name, value}` and `{font, column, row}` records. A run that stops at the first zero cuts all of
  them. A table's end is not the end of the datum it sits in: newlib's `impure_data` (`struct _reent` at
  `0x4851b0`, `_rand_next = 1` at `+0xa8`, the three `FILE`s from `+0x1e4`) holds a run of three `FILE`
  pointers that used to split it.
* **Alignment is not always 8.** `.sdata` starts at every multiple of 4 like `.sbss`; inside a GCC unit's
  block a word starts at 4 (29 % of code references into GCC-owned `.data` are 4 mod 8, against 3 % for
  MWCC); before a function the assembler pads with zero words to the function's alignment (Sony
  libkernl's `_kTLBException` at `0x113bc0` and `_kExitTLBHandler` at `0x113d00`, the static initialisers
  at `0x51fd00`). An unaligned reference is not a start: `luaX_token2str` forms `token2string - 0x404`
  and `Memory_GetCurrentContext` forms `g_memoryContextStack - 4`.
* **Short strings.** `data/strings.json` leaves out strings of a few characters (`"C"`, `"add"`,
  `"host0"`, `"fmt "`, Shift-JIS names); a pointer table naming text up to a zero byte identifies them.

What stays `?`: the unreferenced file-scope constants of fdlibm units (`e_atan2.c`'s `tiny … pi_lo`,
`k_cos.c`'s `one, C1 … C6`, `k_sin.c`'s, `k_tan.c`'s, `e_fmod.c`'s `one`, `s_ceil.c`'s `huge`), which
Sony EE GCC emits at the head of each unit's read-only block before the literal copies the code loads;
CRI Sofdec's blank-padded version string and the M2V decoder's default-condition and build-info records
(`0x4f2850`, `0x4f2948`); the tail of `mpv_build_inf` behind a misread string; an MPEG frame-rate table at
`0x4f5060`; the high byte of `g_byteOrderProbe` (retail's datum is the short `0x1234`); and two 16-byte
`.bss` datums in Gfx's block that its source does not define.

## Unclaimed code hiding inside the "data" regions

Two of the biggest regions **start with code**. `0x521750` disassembles cleanly (a
`lui at,0x59 / sw zero,-14736(at)` guard, then a tail `j 0x100c20` with its arguments set, the
static-initialiser idiom) and is `__sinit_GuiLibrary.cpp` in `config/SLUS-20836/symbols.txt`, directly after
`__sinit_beTargetObj.cpp`.

Ghidra's labels miss verified leaf functions in the same way:

| address | body | what it is |
| --- | --- | --- |
| `0x1006c0` | `lui v0,0x4d; jr ra; addiu v0,v0,0x1c18` | `return &DAT_004d1c18;` |
| `0x1024d0` | `lui v0,0x4d; jr ra; addiu v0,v0,0x1e60` | `return &DAT_004d1e60;` |
| `0x13c410` | `jr ra; sw a1,12(a0)` | a one-instruction setter, `obj->unkC = v` |

`0x1024d0` appears as a 4-byte word in the image once, at `0x5224ac` inside the vtable region,
so this is not dead code. **The two label rules cannot see such a function, because both iterate
Ghidra's gap `LAB_` labels**: `promote_gap_labels` wants a frame prologue and `promote_data_labels`
wants a data reference, but for an address Ghidra never disassembled there is no label to iterate at
all. A function reachable only through a pointer table is therefore invisible to both.

`promote_referenced_starts` in `tools/split.py` closes that gap: it is keyed on table-context data words
and code literals rather than on Ghidra's labels, and the body may be a leaf or open a frame. The
reference is the signal instead of the label, and all the functions above now have symbols. The 80
known SDK syscall stubs are a separate case: they are deliberately excluded from the split.

Promoting a function *lowers* the published coverage percentage until it is decompiled, so the matched
count is the number that matters.
