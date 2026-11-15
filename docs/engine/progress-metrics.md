# Progress: the code number and the data number

Decompilations are read on **two** numbers, code and data, and
a README that gives only the code figure silently hides a quarter of the image. This page
defines both numbers for this repo, and where each comes from.

Both are computed by committed tools from committed files, so they can be regenerated and
published on every push without the retail ELF or the proprietary compiler:

```sh
make progress          # PROGRESS.md, docs/progress.json, the block at the top of README.md
python3 tools/progress.py --report    # the code number alone
python3 tools/datamap.py              # the data breakdown
```

## Code

A function counts as decompiled when a definition for it exists in `src/`. Every such file was
written only after `tools/verify.py` proved its compiled bytes identical to retail, so the
number is a *record* of verification rather than a re-verification; `make check` re-proves it.

* denominator: the sum of the function sizes in `config/SLUS-20836/symbols.txt` (the retail split);
* numerator: those functions whose name is defined in `src/` (which is why a filename count
  is wrong: a folded translation unit is one file for many functions; `tools/units.py` reads
  the definitions).

Coverage is quoted in bytes rather than functions, because the function count is flattered by
small functions: the matched ones have a median size of ~28 bytes against ~128 for the rest.

## Data

There are **no data sections to divide** here: retail is a single merged section
(`0x100000..0x554b00`, plus a zero-initialised tail to `0x58d280`), so "data" is what
`tools/layout.py` tiles between the functions: 1.30 MB with the `.bss` tail.

**The data headline is data matched from source**, the counterpart of matched code: the bytes a
unit defines and `make check` compared byte for byte with retail, relocations applied. A whole-file
unit gives each datum it defines a retail address (its `data` and `anon` rows,
[emitted functions](emitted-functions.md)); `tools/verify.py` compares every such section, `tools/check.py`
writes the compared spans to `data/check-data.tsv` with the owning unit's category, and
`tools/linkgen.py` places them from the object, so `make link` proves them too. A datum the source only
declares `extern` at a retail address counts nothing, however well its type is known: data progress is
moving a definition into the unit. Fully matched has the code headline's meaning, units classified
`match` or `assembly`; the jump tables of fully matched code count as well, since the compiler
regenerates them.

`tools/datamap.py` labels each data byte, the first kind that claims it winning:

| kind | source | extent |
| --- | --- | --- |
| `code` | `config/SLUS-20836/layout.txt` | the function extents from `config/SLUS-20836/symbols.txt` |
| `source` | `data/check-data.tsv` (fully matched units) and the `jtbl` units of fully matched owners | the compared sections |
| `jtbl` | the other `jtbl` units of `config/SLUS-20836/layout.txt` | `config/SLUS-20836/jumptables.txt` |
| `exc` | `config/SLUS-20836/exceptions.txt` and the static-initializer table | 12-byte index records, the recorded table sizes |
| `literal` | the float and double pool reached through `gp` | `0x554880`–`0x554974` |
| `vtable` | `data/vtables.json` (RTTI), `data/vtables-getvtable.json` (each class's `GetVTable`) and the `vtable` rows of `data/data-layout.tsv` (the vtable section only: from a recorded vtable, a referenced `[0 or pointer, 0]` header or a 16-aligned header before two function starts, to the next) | `8 + 4 × len(vfuncs)`; the rows run over zero slots to the next vtable |
| `str` | `data/strings.json`, and the `str` rows of `data/data-layout.tsv`: short ASCII or Shift-JIS strings a pointer table names | `length + 1`, for strings actually in the image |
| `handle` | `data/reflection.json` | 4 bytes per class handle (they live in the `.bss` tail) |
| `table` | `table` rows of `data/data-layout.tsv`: two or more words, each the start of a function, string or referenced datum, null words between them, no known start inside; or records of two to four words each led by such a pointer | the run, to its last pointer (a zero after it is padding more often than a terminator: 863 to 225 in matched units) |
| `region` | the `data` rows of `config/SLUS-20836/regions.tsv` that say what they hold: VU1 microcode, Sony library descriptors, kernel patch arrays | the row |
| `pad` | after a datum of known size, functions included | zero bytes up to the next aligned start (8; 4 in `.sdata`, `.sbss` and GCC-owned data), fewer than 16, or before a function up to its alignment (at most 256) |
| `named` | the data rows of `config/SLUS-20836/data-names.tsv` | to the next start or the end of a sized datum |
| `ref` | `ref` rows of `data/data-layout.tsv`: an address retail code forms (`lui` pairs, `gp`-relative) | to the next start or the end of a sized datum |
| `ptr` | `ptr` rows: an address only a pointer word in the data holds | to the next start or the end of a sized datum |
| `?` | the remainder | what no evidence reaches |

Two numbers are published: **data bytes** (`source` / all data) and **data identified** (every kind
but `?` / all data). The second says how much of the data is understood; it does not move with
decompilation and is not progress.

`named`, `ref` and `ptr` record where a datum starts, not where it ends. Such a datum, with its padding,
runs to the next start any source records or to the end of a datum of known size, never past its
section, so a datum nothing references that sits inside the span is counted with it. A pointer table
does not end it: a run stops at the first word that is not a pointer, which can be a member of the same
datum. The identified line gives these bytes' share apart from the data whose extent is recorded. The
facts that need the retail executable (code references, pointer runs, vtables, short strings, the zero
runs) are generated into `data/data-layout.tsv` by `scripts/data_layout.py`. Padding follows the retail
linker's placement rule: a datum starts at the previous one's end raised to `max(its alignment, 8)` (4 in
`.sdata` and `.sbss`, where 63 and 176 matched rows start at every multiple of 4), and MWCC aligns 16 at
most, so fewer than 16 zero bytes before an aligned start are alignment; every matched MWCC datum of 16
bytes or more starts 16-aligned, as do all 977 dumped vtables. A reference or pointer at an address the
rule forbids is not a start: the compiler forms biased array bases (`luaX_token2str` reads
`token2string[token - 257]` through 0x4eb22c), and text can read as a pointer. Inside a GCC unit's block
(`config/SLUS-20836/data-owners.tsv` owner built `gcc` in `regions.tsv`) a datum starts at its own
alignment, 4 for a word. Functions are aligned the same way, and the assembler's `.align` can pad further
before one: zero words (nops) up to the function's alignment.

A `.bss` datum is compared with the zeros the loader fills, which proves its address and size but
not its contents, and it is never linked (the link emits only the file image).

A matched datum must also be compiled into the section kind retail's region holds (`.data` from
`0x481c00`, `.rodata` from `0x4d1c00` as `config/SLUS-20836/regions.tsv` records it, `.vtables` from
`0x522440`, `.sdata` from `0x554880`, `.sbss` from `0x554b00`, `.bss` from `0x554f00`;
[data regions](data-regions.md)). A literal compiled into `.data` at a
read-only address (the unit lacks read-only strings) or a zero global in `.bss` at a `.data` address
compares equal and links, since the link places by address, but its source still differs from the
original. Such bytes are published apart and not counted.

### The third number: typed coverage

**Typed coverage is the share of field accesses that use a recovered type**, measured by
`tools/typed_coverage.py` and carried into `PROGRESS.md` and `docs/progress.json` beside the other
two. It counts accesses written as a member of a recovered class (`igMetaObject *g; g->_validity`)
against accesses written as an offset cast (`*(int *)((char *)p + 36)`), and it is the *inward*
metric: matched bytes say how much of the binary is verified, this says how much of it is
**typed**. m2c's C matches retail while encoding 4-byte pointers and hand-computed offsets, which
is exactly what another compiler cannot use (see [`typed-coverage.md`](typed-coverage.md)).

It was measured **neutral for matching**: it buys nothing in the matched-byte percentage. The number also has a ceiling:
only a small share of accesses is typeable from the receiver class alone, because most
matched C is address-named, so **typed coverage advances with naming**: the two loops are the same
work seen from two sides.

## Fully linked

Two headlines matter, *decompiled* and *fully linked*, and for a
translation-unit build they differ: Twilight Princess reports 12.07 % decompiled against
8.12 % fully linked, and was announced as *"100 % decompiled, but not fully linked yet"*. The
reason is granularity: such a build links either the unit's C or the unit's asm stub, so the
stub can only be dropped once the **whole translation unit** is decompiled, and a matched
function inside a half-finished unit does not move the linked figure.

**Here the two numbers coincide for code, by construction.** `tools/layout.py` tiles the
section **per function**, and `tools/linkgen.py` decides per unit, so a matched function's C
replaces those retail bytes immediately and the rest of its original translation unit stays
in `asm/`. `make link` proves the result (the whole section compares byte-identical), and it
prints the accounting from the link itself:

```
linkgen: linked from C        N units     B bytes    P % of the section
linkgen: asm bodies           N units     B bytes    P %  (not counted)
linkgen: linked from asm      N units     B bytes    P %
linkgen: compiler tables                  B bytes    P %
linkgen: data from C          N sections  B bytes placed at their retail addresses from U units (…)
```

The headline is the same accounting against the **whole image**
(code + data): the matched code plus the data the link places from C, the units' verified data
sections and the jump tables the compiler regenerates. That is the number `PROGRESS.md` shows as the
`fully linked` bar, with the code-only reading (equal to matched) explained next to it.

Because nothing decompiled is ever *waiting* to be
linked, "matched" and "fully linked" cannot drift apart later. The risk a TU-based project
carries (a large backlog of matched-but-unlinked code) is structurally absent here.

## Publishing

`tools/progress.py` writes three things, all generated and never hand-edited:

* `PROGRESS.md`: the detailed page (code bands, where in the binary, the data table, the
  recovered-metadata table);
* `docs/progress.json`: the same numbers, machine-readable;
* the block between `<!-- progress:start -->` and `<!-- progress:end -->` at the top of
  `README.md`.

The outputs are a pure function of the committed tree, so a push that changes no C produces no
diff and publishes nothing. `python3 tools/progress.py --check` fails if the committed outputs
are stale.
