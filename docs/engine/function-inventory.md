# The function inventory: what the denominator counts, and why it can be trusted

`config/SLUS-20836/symbols.txt` is the denominator of every progress number: a function that is not in it
cannot be decompiled, counted or missed. The relink proves every byte, but it proves bytes, not
the inventory: code with no symbol links as a `data` unit of `config/SLUS-20836/layout.txt` and is counted
by nobody. This page states the rules that put a function into the inventory, the reviewed extent
corrections, the scan that keeps unowned code from growing back, and the before/after numbers.

## 1. Where the inventory comes from

`tools/split.py --symbols` builds the table in a fixed order from committed inputs and the retail
image alone (no Ghidra session, no objdump), so a replay reproduces `config/SLUS-20836/symbols.txt` bit for bit:

1. **The Ghidra dump** (`data/functions.json`) with the reviewed spans of `data/function-extents.json`.
2. **Extent repairs**: the delay slot Ghidra cut off, the jump-table case bodies it never followed,
   then the reviewed rows of `config/SLUS-20836/extent-overrides.tsv` (section 3).
3. **Promotion rules** (section 2), each one byte-preserving (nothing moves, nothing is invented) and
   overlap-refusing (a candidate inside a function, or whose body would reach a referenced start it
   cannot end before, is left alone). The run prints every rule with its count.
4. **The name overlay** (`config/SLUS-20836/names/`), merged last so promoted functions are named too.

### The instruction model

The rules decide extents from the retail words. The model is three helpers in `tools/split.py`:

- `_code_shaped(word)`: the word is an instruction the EE has (R5900 opcode and function-code
  inventory: no `dmult`, no COP3, no `ll`/`sc`) and a compiler could emit (nothing but the zero
  word writes `$zero`; a `j`/`jal` lands inside the section). Rodata that happens to decode
  rarely survives a whole body of this test; the one shape that did, before the jump-target
  rule, was a string table: a tab or newline byte decodes as `j`, so `"...ect\n"` ended a
  "body" of `daddiu`/`ldr` words (twelve such promotions in `0x4d2448..0x510330`, caught by
  screening every new function for all-printable words).
- `_fresh_start(va)`: nothing falls into `va`: the word before it is padding (a zero that is not
  a conditional branch's or a call's delay slot), or the delay slot of `jr`/`j`/`b`. A `jr v0; nop`
  is a switch dispatch, so what follows it is a case body, never a function.
- `_sweep_extent(va, bound)`: walk forward; the body ends after the delay slot of the first
  transfer that is unconditional **and not jumped over** by an earlier branch of the body:
  `jr ra`, `jr t9`, a `j` that leaves the bound, goes backwards or lands on a frame prologue (a
  tail call). Internal `j`s (EE GCC's long forward jumps) and every PC-relative branch (`b`
  included) extend the body to their target; a body ending in a backward `b` (an idle loop) is
  not recognised, because `b` is also what string bytes most easily decode to. The walk fails (no promotion) when a word is not
  code-shaped, a branch leaves the bound, a fresh frame prologue appears (the walk ran into the
  next function) or no end comes before the bound.

Referenced starts bound every walk (`strong_reference_starts`): `jal`/`j` targets from inside known
functions, code addresses in a *table* of code addresses outside every function (the neighbouring
word is a code address too; a lone coincidence in rodata is not a table, an instruction word that
equals an address is not a reference), and literals the code forms (`lui`/`addiu`). The C++
exception index and tables (`config/SLUS-20836/exceptions.txt`) and the recorded jump tables
(`config/SLUS-20836/jumptables.txt`) hold code pointers that land *inside* bodies, so they are excluded. A
walk that reaches a referenced start is cut there only if it ends cleanly before it; a body with
a switch dispatch owns the data words that point into it (its own jump table).

## 2. The promotion rules

| rule | candidates | shape | evidence | count (this table) |
| --- | --- | --- | --- | --- |
| 2 | `LAB_` labels in gaps, referenced by a data word | leaf: exactly one `j`/`jr` end, no frame, every word code-shaped | Ghidra saw it and a table points at it | 1,781 |
| 1 | `LAB_` labels in gaps that open a frame (`addiu sp,sp,-N`) | `_sweep_extent` | Ghidra saw it; the frame | 1,113 |
| sdk | starts an SDK library descriptor declares (`data/sdk-bindings.json`) | `jr ra` extent; the last split piece takes the walk's extent | the descriptor's table | 3 |
| thunk | `j <function>; nop` stubs a data word or literal names | 8 bytes | the reference and the target | 636 |
| 3 | `jal`/`j` targets of known functions with no symbol | `_sweep_extent`, any shape | the call | 100 |
| 4 | table-context data words and literals in gaps | `_sweep_extent`, any shape | the table or literal | 493 |
| 5 | gap words that open a frame, referenced by nothing | `_sweep_extent`; the final transfer restores exactly the frame it opened | the symmetric frame | 111 |
| 6 | every non-zero gap word below `CODE_HI` (`0x467120`, where the VU1 microcode starts) | `_sweep_extent`, any shape | the code range: below it the image holds only functions, their padding and constants inside their bodies | 349 |

Rules 3–5 feed each other (a body rule 5 finds calls a stub only rule 3 can see), so they run to a
fixpoint; each round recomputes the reference set from every function known so far. Rule 6 runs
only when a round of rules 3–5 adds nothing, so it never takes a body those rules would bound or name
differently, and what it adds feeds another round. It needs no reference because the compiled code
holds no rodata: the decoded-rodata risk that rules 2–5 guard against lies above `CODE_HI`, where
rule 6 does not look. Its bodies are unreferenced static functions the linker kept, getters reached
only through tables the scan cannot form, and the syscall stubs between the named ones. The gap after
the last function (the global constructor at `0x521790`, 2.7 KB) is scanned like every other.

What changed against the earlier rules: rule 1 bounded a candidate at the next label *of any kind*
and only accepted `jr ra`, so a function with an internal branch-target label or a tail-call
ending was dropped (106 + 76 cases in the inventory audit); rule 2 never ran on the last gap;
nothing promoted an unreferenced `jal`/`j` target (47 tail-call and 11 call targets, the cause of
the 33 `inventory-gap` units); nothing promoted a vtable-referenced body with a frame (`0x3236a0`,
3.6 KB, 272-byte `sq` frame, 34 calls, sat in a gap). Rule 2 now also refuses a label right after
a switch dispatch (`jr v1; nop`): it had turned the first case body of four switch functions into
"functions" of their own, which cut the real function short (`Gap__Gfx__igPsx2VisualContext__vfunc_100`,
`igPsx2VisualContext::vfunc_37`, `igPsx2DisableExt::vfunc_30/31`).

## 3. Reviewed extents (`config/SLUS-20836/extent-overrides.tsv`)

A row sets a function's size. Plain rows grow to the next function or shrink over zero words only.
Two keywords go further, each reviewed against the bytes:

- `cut`: the shrink leaves code behind: the dump glued a second function onto this one. The head
  keeps the bytes up to its own return or tail call; the remainder must be claimed by a promotion
  rule, and `check_cuts` fails the run otherwise, so a cut never orphans code.
- `merge`: the function absorbs every dump function that starts inside its new extent and takes
  the row's name.
- `start`: a function no rule can walk, added at the row's address and size. The row must lie in a
  gap of the code below `CODE_HI`, start at a fresh start and not begin with padding.

The rows this pass added, by evidence class:

| class | rows | what the bytes show |
| --- | --- | --- |
| epilogue growth | 159 (all functions of the EE GCC blocks) + `SetT2` (`eret` then `jr ra; nop`) | the dump stopped 3–5 words before `ld ra; jr ra; addiu sp,+N`; the walk from the symbol start ends there |
| `cut`: tail-call wrapper + framed body | 20 (`_getpid_r`, `FUN_00269878`, `FUN_00297f30`, `FUN_002980c0`, `FUN_0017c880`, `FUN_00260d48`, `FUN_002a1110`, `FUN_00109c88`, `vfiprintf`, `Gap__Gfx__igPsx2VisualContext__vfunc_172`, `FUN_00299110`, `FUN_002997c0`, `FUN_0029b6d0`, `FUN_002a3730`, `FUN_002b2ee8`, `FUN_002b3300`, `FUN_002b4210`, …) | the head ends in `j <body>` to a fresh frame prologue under the same symbol (a function never jumps to its own frame-opening word) |
| `cut`: wrapper + leaf body | 12 (`FUN_002612c0`, `FUN_002854b0`, `FUN_0028abc0`, `FUN_00293788`, `mwply_IsCurPicItemTypeThree/8b8/938`, `FUN_002ad2e0`, `FUN_002ad3e0`, `FUN_002b3530`, `FUN_002b4630`, `Memory_AllocateBufferViaSharedTail`) | the head's walk ends at its `j` to a fresh start that follows after padding; the body is claimed by rule 3 |
| `cut`: span reached a referenced leaf | 5 (`Gap__Core__igCallStackTable__findCallStack`, `FUN_00155340`, `FUN_00159320`, `igMemoryFile::vfunc_23`, `FUN_004657b0`) | `data/function-extents.json` ran to a vtable-referenced leaf after the function's own `jr ra` |
| `cut`: verifier extent corrections | `FUN_001b4c40` (7296 → 7276: `DAT_001b68b0` is a 16-byte wrapper, `move a1,a0; lui; j 0x1b68c0; lw`, after the function's `jr ra` and a nop; `FUN_001a44d0` now passes it as a function pointer), `FUN_00267438` (96 → 88: `FUN_00267490` is the 8-byte getter `jr ra; lw v0,152(a0)` that `FUN_0026c3c8` calls), `FUN_00453a20` (8-byte `j` wrapper + referenced 12-byte leaf at `0x453a30`), `FUN_0018edb0` (1768 → 1576: twelve 8-byte default stubs at `0x18f3e0..0x18f490`, 16-byte aligned after its `jr ra`, whose addresses it builds with `lui`/`addiu` and stores into its tables; claimed by rule 4) | the inner address is a fresh start after the container's return |
| `merge` | `FUN_002fe290` (44 bytes) | `thunk_FUN_002fe2ac` (`b 0x2fe2ac; nop`) was the entry of a list-search loop whose other half Ghidra called `FUN_002fe2ac`; one leaf, its callers now name `FUN_002fe290` |
| `start` | `FUN_00100230` (8), `FUN_001051c8` (96), `FUN_00113bc0` (284), `FUN_00113d00` (244), `_debugHandlerEntry` (288), `FUN_001c5130` (36), `FUN_00265d30` (52) | bodies the sweep cannot end: a thread entry whose `syscall` (ExitThread) does not return; an MMI clamp loop that a `j` from `FUN_00104258` enters, with its 16-byte `lq` constant inline (each word writes `$zero`, so falling through is harmless) before `jr ra`; three kernel exception handlers ending in `eret`, `syscall` and `break` (the syscall table at `0x4822a8` installs `0x113d00` as call 0x54); a tail call through `jr v0`; an error call followed by an idle `b` loop |
| plain shrink | `_outputFrame` (312 → 272), `FUN_001e6130` (584 → 248) | the dump's extent ran into the next symbol; both now end at their own transfer. `FUN_001e6130` remains a block of an earlier function (its `j 0x1e5fe0` lands inside `FUN_001e5f00`), a matter for the EE GCC blocks |

`FUN_0029a210` (56 → 20) is not a row: it is a rule-1 promotion whose walk now stops at its tail
call; the framed body after it (`0x29a228`) is a rule-5 promotion. `FUN_001044f0` (64 → 148) is the
SDK-descriptor split piece that now takes the walk's extent. `abort` keeps its 24 bytes: it
ends in a call to a non-returning function and has no epilogue. `FUN_001eba30` and `__throw`
keep their extents.

A function whose extent changed and that has no C source links from the retail image at its
reviewed extent; the repository keeps no asm bodies ([asm-body matches](asm-body-matches.md)). Three units were renamed because the stub rule now reaches
them before the leaf rule (`thunk_FUN_001592c0`, `thunk_FUN_001592c0__0016e390`, `thunk_Gap__Core__igObject__vfunc_09__0022bbc0` → `thunk_…` after their
targets); ten units that called `thunk_FUN_002fe2ac` call `FUN_002fe290`.

## 4. The scan and the debt counter

`scripts/inventory_scan.py` walks every `data` unit of `config/SLUS-20836/layout.txt` for instruction-shaped
bodies (every non-zero word code-shaped, an unconditional end plus delay slot, and a frame
prologue, a `jal`/`j` to a symbol, or a `jr ra` return) and attributes each to the reason it has no
symbol: **A** continuation of the preceding symbol, **B** `jal` target, **C** data-word referenced,
**D** `j` target, **E** branch target from elsewhere, **G** unreferenced, **H** unreferenced 8-byte
`jr ra` stub. It writes `data/inventory-scan.tsv` (`--write`); the byte total is the debt counter
`inventory.unsymbolised_bytes` (`tools/progress.py --debt-check`), and `make inventory-check` fails
when the table is stale or the total exceeds `config/debt-baseline.json`.

Residual: **14 bodies, 1,020 bytes**, all class G and all in the Sony kernel-mode block
(`0x4820d0..0x4833c8`, `config/SLUS-20836/regions.tsv`). That code runs at another address, so its calls and
literals point outside the image and nothing in the image references its pieces; it lies above
`CODE_HI`, so rule 6 does not reach it. Below `CODE_HI` every non-zero word belongs to a symbol; the
`data` units left there are zero padding.

## 5. Before and after

| | before (`ed33b3b4d`) | after |
| --- | --- | --- |
| functions in `config/SLUS-20836/symbols.txt` | 19,293 | 20,584 |
| code bytes in `config/SLUS-20836/symbols.txt` | 3,377,884 | 3,475,412 |
| code bytes laid out (`config/SLUS-20836/layout.txt`) | 3,377,372 in 19,293 units | 3,475,412 in 20,584 units |
| truncated layout units (symbol overlapping the next) | 4 | 0 |
| symbols ending without a return (audit) | 167 | 1 (`abort`, non-returning callee) |
| symbols holding two functions (audit + the `j`-to-fresh-start scan) | 11 + 26 | 0 |
| unsymbolised instruction-shaped bytes (scan, same tool on both trees) | 88,352 in 1,348 bodies | 1,020 in 14 bodies |
| `inventory-gap` units | 33 | see the `make check` summary in the commit |

Net: 1,283 functions added (104,416 bytes), 6 removed (`FUN_002fe2ac` merged; `FUN_00172184`,
`FUN_0016c598`, `FUN_0016ce28`, `FUN_0016ceb4`, `FUN_00177918` were switch case bodies the leaf
rule had mistaken for functions; their switch functions now own them), 203 resized, 4 renamed.
The denominator grew by the code that was always there; no byte moved.

A side effect on matched units: 104 units pass the address of a promoted function as a `DAT_<va>`
(a callback, a field adder, a static-initializer item). The verifier flags a data name that points
into code (`name-defect`), so those units now declare the function and pass it by name (an `(int *)`
cast or a function-pointer parameter where the callee's prototype demanded it). Four units keep a
data alias on purpose: `DAT_`/`g_` spellings of one address next to its `FUN_` name defeat the
compiler's address CSE, a matching construct the m2c pass used (`igTextureFunctionAttr_InitFields`,
`igStencilFunctionAttr_InitFields`, `igBlendFunctionAttr_InitFields`, `igMovieInfo_InitFields`);
naming the function there changes the bytes. The
real reason the original did not keep the address live is unproven ([open questions](#open-questions)). `FUN_001c0f00` passes the function
by name (`src/engine/scenegraph/igEnbayaAnimationState_tail.inc`).

## 6. Replaying and checking

```
python3 tools/split.py --symbols --symbols-only     # prints every rule's count; reproduces config/SLUS-20836/symbols.txt
python3 tools/layout.py --report                    # truncated : 0
python3 scripts/inventory_scan.py --write           # refresh data/inventory-scan.tsv after a symbol change
make inventory-check                                # stale table or grown debt fails
```

## Open questions

- Unproven: `igTextureFunctionAttr_InitFields`, `igStencilFunctionAttr_InitFields` and
  `igBlendFunctionAttr_InitFields` materialise one function address through two symbols. `FUN_` naming for
  all uses merges the `lui`/`addiu` loads (relocations 41 to 39) and shrinks the frame. Identical-code folding
  of the callbacks by the retail linker is the likely reason.
