# The data regions: what is in the 1.4 MB that is not code

`tools/datamap.py` divides the image into code and data and reports how much of the data is
*identified* (see [`progress-metrics.md`](progress-metrics.md) for why that number is published).
This page is the identification step above that accounting: what the regions actually are.

The starting fact is that the unclassified data is **extremely concentrated** — 20 regions hold
880,360 of the 1,162,652 unclassified bytes (76 %), and three of them hold 642 KB between them
(the "one 644 KB block" `tools/layout.py`'s docstring mentions, which is really three regions).

The method is three cheap measurements over each region, all reproducible:

* **composition** — each 32-bit word classified as a small integer, a plausible IEEE-754 float, a
  pointer into the image, or zero;
* **pointer targets** — where a pointer's value lands: code, another data region, the string dump
  (`data/strings.json`), or `.bss`;
* **printable runs** — ASCII sequences of six characters or more, which name most of these regions
  outright.

## The five that are identified

| region | bytes | composition | what it is |
| --- | ---: | --- | --- |
| `0x521750` | 209,840 | 79 % code pointers | **the vtable region.** 6,613 runs of code pointers, most 21–23 long, each preceded by a `[rtti, 0]` header — the layout the 478 vtables in `data/vtables.json` have. That dump came from the RTTI records, so this region holds the vtables of the classes with **no** RTTI (finding [#368](../findings/findings-0251-0500.md#f368) extracted 980 class vtables in total). Its first 828 words are code, not data (§below) |
| `0x4833c8` | 321,816 | 44 % pointers, 33 % zero | **Sony SDK library metadata + embedded VU1 microcode.** Strings: `PsIIlibcdvd 2800`, `PsIIlibpad 2800`, `PsIIlibsdr 2800`, `PsIIlibmc 2810`, plus VU program metadata (`EXECUTE_PATH;1073741824;;131077;;;;.EXECUTE_RENDERLIST;…`, `vu1_entry_UCODE_BEGIN;0;vu1_entry_EXECUTE_PATH;16;vu1_end_EXECUTE_PATH`) and `Error decoding compressed text` |
| `0x467108` | 110,536 | packed records: 4,465 words of `0x2ff`, 3,515 of `0x8000033c` | **more SDK metadata** — `PsIIlibgraph 2800`, `PsIIlibdma 2800`, `PsIIlibipu 2800`, `PsIIlibkernl 2800` — with the word shape of SDK library-descriptor / relocation entries |
| `0x50005c` | 54,724 | 11 % pointers, 1,688 ASCII runs | **reflection metadata** — the class and field name/descriptor arrays behind the MetaObject field tables (`Gap::igAdxFile`, `Gap::Core::igNamedObject`, `_ptNumber`, `_fileNumber`) |
| `0x4d7020` | 30,720 | 31 % floats, 893 ASCII runs | **the engine string table plus IOP module names** — `sio2man.irx`, `padman.irx`, `mtapman.irx`, `supportMultitap`, `IG_GFX_INDEX_SIZE_16_BIT`, `error creating visual context` |

Two consequences worth stating:

* **The IOP modules are not stored here.** The SDK strings suggest otherwise, but an IRX image
  would carry the `0x7fELF` magic and the whole image contains exactly one such word, outside these
  regions. What is here is the *library version strings* the SDK registers — relevant to
  [`binary.md`](binary.md) and to the IOP question in the tracker (T5).
* **The data percentage is a floor set by the dumps, not by what is known.** Three of these five
  are mechanically recoverable: the vtable region by enumerating `[rtti|0, 0, codeptr…]` runs (which
  would extend `data/vtables.json` well beyond its RTTI-only 478), the reflection metadata from
  `data/reflection.json`'s own tables, and the strings from `data/strings.json`.

## Unclaimed code hiding inside the "data" regions

Two of the biggest regions **start with code**. `0x521750` disassembles cleanly — a
`lui at,0x59 / sw zero,-14736(at)` guard, then a tail `j 0x100c20` with its arguments set, the
static-initialiser idiom — and `config/SLUS-20836/symbols.txt` jumps from `FUN_00521730` (ends `0x521750`)
straight to `data_00521750`.

The same search finds verified leaf functions that were never claimed:

| address | body | what it is |
| --- | --- | --- |
| `0x1006c0` | `lui v0,0x4d; jr ra; addiu v0,v0,0x1c18` | `return &DAT_004d1c18;` |
| `0x1024d0` | `lui v0,0x4d; jr ra; addiu v0,v0,0x1e60` | `return &DAT_004d1e60;` |
| `0x13c410` | `jr ra; sw a1,12(a0)` | a one-instruction setter, `obj->unkC = v` |

`0x1024d0` appears as a 4-byte word in the image — once, at `0x5224ac` inside the vtable region —
so this is not dead code. It survived because **both promotion passes iterate Ghidra's gap `LAB_`
labels**: `promote_gap_labels` wants a frame prologue (finding [#346](../findings/findings-0251-0500.md#f346)) and `promote_data_labels`
wants a data reference (finding [#365](../findings/findings-0251-0500.md#f365)), but for an address Ghidra never disassembled there is no
label to iterate at all. A function reachable only through a pointer table is therefore invisible
to both.

Measured over the whole image: 8,679 distinct 4-byte words point into a data region, of which
**43 are leaf-shaped** (a `jr ra` in the first 16 bytes, no prologue) and **145 are
prologue-shaped** — about 188 unclaimed functions. 1,143 data regions contain a `jr ra` at all
(503 of them ≤24 bytes; some of those are the 80 known SDK syscall stubs, which sit in data regions
because they are deliberately excluded from the split).

The fix is a **third promotion pass keyed on the data words rather than on Ghidra's labels**: for
every 4-byte word landing in an unclaimed region whose target decodes to a plausible body, promote
it. The reference is the signal instead of the label. Note that adding ~188 unmatched functions
*lowers* the published coverage percentage until they are decompiled — the matched count is the
number that matters (the same point [#365](../findings/findings-0251-0500.md#f365) made when the leaf promotion grew the denominator), and
these are trivial functions that the m2c pipeline handles well.
