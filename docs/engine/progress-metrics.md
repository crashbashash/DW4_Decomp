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

* denominator — the sum of the function sizes in `config/SLUS-20836/symbols.txt` (the retail split);
* numerator — those functions whose name is defined in `src/` (which is why a filename count
  is wrong: a folded translation unit is one file for many functions — `tools/units.py` reads
  the definitions).

Coverage is quoted in bytes rather than functions, because the function count is flattered by
small functions: the matched ones have a median size of ~28 bytes against ~128 for the rest.

## Data

There are **no data sections to divide** here: retail is a single merged section
(`0x100000..0x554b00`, plus a zero-initialised tail to `0x58d280`), so "data" has to be
*classified* rather than read off the section headers.

`tools/layout.py` already tiles every byte of that section into `code` units (the functions)
and the data regions between them. `tools/datamap.py` then labels each data byte from the
metadata the repo has recovered:

| kind | source | extent |
| --- | --- | --- |
| `code` | `config/SLUS-20836/layout.txt` | the function extents from `config/SLUS-20836/symbols.txt` |
| `jtbl` | `config/SLUS-20836/layout.txt` | `config/SLUS-20836/jumptables.txt` |
| `vtable` | `data/vtables.json` | `8 + 4 × len(vfuncs)` — the words are `[rtti, offset, vfuncs…]` |
| `str` | `data/strings.json` | `length + 1`, for strings actually in the image |
| `handle` | `data/reflection.json` | 4 bytes per class handle (they live in the `.bss` tail) |
| `?` | the remainder | alignment, tables whose extent is not pinned yet, the rest of `.bss` |

The number reported is **identified data bytes / total data bytes**. `?` is the honest
remainder, not a failure: it is what has *not* been classified yet, and shrinking it is how
data progress advances.

### The third number: typed coverage

**24.25 % of field accesses use a recovered type** (550 of 2,268), measured by
`tools/typed_coverage.py` and carried into `PROGRESS.md` and `docs/progress.json` beside the other
two. It counts accesses written as a member of a recovered class (`igMetaObject *g; g->_validity`)
against accesses written as an offset cast (`*(int *)((char *)p + 36)`), and it is the *inward*
metric: matched bytes say how much of the binary is verified, this says how much of it is
**portable**. m2c's C matches retail while encoding 4-byte pointers and hand-computed offsets, which
is exactly what another compiler cannot use — the port's prerequisite (tracker T10, page
[`typed-coverage.md`](typed-coverage.md)).

It was measured **neutral for matching**, and that is not a contradiction: it buys nothing in
the matched-byte percentage and everything for the second goal. The number also has a *ceiling*
worth watching — only 1.4 % of accesses are typeable from the receiver class alone, because most
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
in `asm/`. `make link` proves the result — the whole section compares byte-identical — and it
prints the accounting from the link itself:

```
linkgen: linked from C        7462 units     332564 bytes    9.8 % of the section
linkgen: asm bodies              0 units          0 bytes    0.0 %  (not counted)
linkgen: linked from asm     11199 units    3034924 bytes   89.8 %
linkgen: compiler tables                      11044 bytes    0.3 %
```

The headline is the same accounting against the **whole image**
(code + data), because the data half is still linked from `asm/`: **7.2 %** — the matched code
plus the jump tables the compiler regenerates. That is the number `PROGRESS.md` shows as the
`fully linked` bar, with the code-only reading (9.9 %, equal to matched) explained next to it.

One consequence worth stating plainly: because nothing decompiled is ever *waiting* to be
linked, "matched" and "fully linked" cannot drift apart later — the risk a TU-based project
carries (a large backlog of matched-but-unlinked code) is structurally absent here.

## Publishing

`tools/progress.py` writes three things, all generated and never hand-edited:

* `PROGRESS.md` — the detailed page (code bands, where in the binary, the data table, the
  recovered-metadata table);
* `docs/progress.json` — the same numbers, machine-readable;
* the block between `<!-- progress:start -->` and `<!-- progress:end -->` at the top of
  `README.md`.

The outputs are a pure function of the committed tree, so a push that changes no C produces no
diff and publishes nothing. `python3 tools/progress.py --check` fails if the committed outputs
are stale.
