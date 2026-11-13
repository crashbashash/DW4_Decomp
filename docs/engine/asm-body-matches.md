# Asm-body matches

**Asm bodies are not kept in the repository (owner decision).** An asm body is a
function's retail instructions wrapped in an MWCC `asm` function. It recovers no source, no types and
no behaviour, and it is the retail code as text, which the repository does not publish
([assets rule](../../CLAUDE.md#hard-rules)). There is no `src/asmbody/` tree, and no matched or
decompiled figure counts an asm body.

What a function without C looks like:

* It has **no file in `src/`**. The relink places its bytes from the retail image
  (`tools/linkgen.py` builds that unit from the layout), so `make link` is unaffected.
* It reads from **`asm/<name>.s`**, the per-function split `tools/split.py` generates from your own
  executable. `asm/` is gitignored; `make check` and `make asm` write it when it is
  missing or stale.
* It is in the **work queue**: every symbol of `config/SLUS-20836/symbols.txt` without a definition in
  `src/`. `python3 tools/m2c_batch.py` drafts from that queue (gcc target for Sony EE GCC units).
* In `objdiff.json` it is a target-only unit, so it reads as unmatched.

C/C++ stays the goal. When a new compiler or compiler version is wired into the verifier (as the Sony
EE GCC was for the SDK/CRI blocks), the functions without source in the blocks that compiler plausibly
built are re-attempted as C first.

## An `asm` function the original was written as

Where the original source itself is an MWCC `asm` function, as some of the compiler's own runtime is, the
function is written that way and approved with an `asm-function` row in `config/source-approvals.tsv`
([source approvals](source-approvals.md)). The evidence has to show the original was written in
assembly, as for a [hand-written assembly source](assembly-sources.md). An approved one counts with the
hand-written assembly sources; one without a row is an asm body, as below.

## If an asm body appears in `src/`

It does not pass review. The tools still recognise one by its **content** (an
`asm void NAME(void) { … }` definition, with or without `#pragma optimization_level 0`, wherever the
file lives): `make check` files it under the `asm-body` category, `tools/progress.py` reports it on a
line of its own (`code_bytes.asm_body` / `functions_asm_body`), and no decompiled, verified or matched
figure counts it. An asm body reproduces whatever bytes its symbol extent covers, so it "matches" even
when the extent is wrong; that is one more reason it proves nothing.

An **inline `asm` statement inside a C/C++ function** (an `asm { sync }` fence, a `.word` for an
instruction the compiler rejects) is different: the function is recovered C. It needs a comment at the
statement saying why that instruction has no C spelling and what was tried.

## Generating one for local study

```sh
python3 tools/asm_body_gen.py FUN_XXXXXXXX -o <a scratch folder outside the repository>/FUN_XXXXXXXX.c
```

The generator reads the retail bytes, disassembles them with `objdump -M no-aliases` (canonical
mnemonics) and writes an `asm void NAME(void) { ... }` body with labels for in-function branch targets,
`extern` declarations and symbols for `jal`/`j` targets (so relocations are recorded), and
`#pragma optimization_level 0`. It is useful as a starting point for a C draft or to see how the pinned
assembler treats a sequence; the notes below were measured that way and stay as reference.


## What the pinned assembler does to an asm body (all measured)

* **Optimizer**: without `#pragma optimization_level 0` the compiler propagates constants across
  instructions (`addiu v1,v0,K; sw a3,4(v1)` becomes `sw a3,K+4(v0)`) and deletes a duplicated
  instruction; `peephole off` alone is not enough.
* **Pseudo-instructions** expand differently: `li`/`move` use `addi`/`addu`, so the body must use `addiu`,
  `daddu` and so on (the generator's `no-aliases` output does); `jalr rs` needs `jalr ra,rs`,
  `syscall` needs an operand.
* **Rejected or mis-encoded mnemonics** are emitted as `.word 0x........ /* mnemonic */`: `break` and the
  trap family, `div`/`divu`/`div1`/`divu1` (the assembler inserts a hazard `mflo zero`), `madd` family,
  `c1`, `dli`/`dla`, `cvt.*`/`trunc.*`/`round.*`/`floor.*`/`ceil.*`, and any `mfc0`/`mtc0` with a named
  coprocessor-0 register. The delay slot after a raw jump is also raw.
* **Jumps and branches** to an address that has no symbol, or to a label inside the same function with
  `j`, are raw words (a section-relative relocation would resolve to the function start). The layout is
  identical to retail, so the literal target is correct.
* **Jump tables** are supported. A function that owns a `switch` table gets one `const char *const NAME_jtblN[]`
  array per table in `config/SLUS-20836/jumptables.txt`, each entry `(const char *)NAME + offset`. The pinned compiler emits that as a
  `.rodata` section whose entries are relocations against the function symbol, which is the shape of a compiler-generated `switch`
  table, so `tools/verify.py` and `tools/linkgen.py` accept it. Two measured details: `(unsigned)NAME + k` is an "illegal constant
  expression" (only the pointer sum is accepted), and tables must be emitted in ascending address order (the checker pairs sections
  with recorded tables by order; `jumptables.txt` lists some functions' tables descending). A table entry that leaves the function
  is rejected by the generator.
* **Truncated extents**: 30 functions whose symbol extent overlaps the next function (`config/SLUS-20836/layout.txt`
  marks them `truncated`) stay retained assembly units until a reviewed
  row in `data/function-extents.json` corrects the extent.

## Large functions

The largest functions have jump tables: `beNDMWLoadIntf2::vfunc_31`, 18,616 bytes, two tables; `beNDMWSaveIntf::vfunc_31`, 16,352 bytes,
two tables.

### The rows they need

Each function is verified independently under its own build profile.

Functions with a reflected receiver class and no jump table nearly all need the alternate combat compiler and `-O3,p` (some with
`-Cpp_exceptions off`), and the C++ ones an entry in `config/SLUS-20836/unit-objects.json` for an empty-destructor duplicate; the rows are in
`config/SLUS-20836/unit-compilers.tsv`, `config/SLUS-20836/unit-flags.tsv` and `config/SLUS-20836/unit-objects.json`.

A unit that emits an
empty-destructor duplicate (`__dt__2RPFv` at 0x002e2300, `__dt__3RefFv` at 0x003d9bd0 or 0x00130140, `__dt__9LuaStrRefFv`) matches only
with that duplicate named in its unit-objects entry.

### Source shapes that fix near-misses

General shapes:

* a real `switch` instead of an if-chain (it changes where the delay-slot nops fall);
* a separate local per loop and per list element (saved-register colouring);
* local declaration order (stack slot and s-register order), and the declaration order and `&x->a; &x->b;` order of address locals;
* `if (a == 0) b = X; else b = a;` null fallbacks;
* a C++ class with enough dummy virtuals for `lw t9,0(s4); lw t9,N(t9); jalr t9`;
* an empty-destructor `struct RP` holder for stack smart-pointer slots;
* a pointer loop counter under the alternate compiler makes the materialised `slt` colour the counter v1 and the count v0: turn it into
  an `int` counter with the loop flag materialised in its own local (`r = a > i; } while (r);`) so the `slt` colours as retail. A plain
  `while (a > i)` gives the fused `slt at` form instead, so the flag needs its own local. When the pointer is still needed elsewhere, make
  the counter an `int` member of a union with it;
* a dummy `l2 = l;` re-read at the bottom of a loop, so strength reduction cannot make a pointer induction
  variable and the base load hoists late;
* explicit byte-offset variables (`jo += 4`) with `j = 0; if (j < n) { jo = 0; do { } while
  (j < n); }` replacing compiler offset webs whose vreg ids sit above anything a declaration can reach;
* the converse: an indexed loop (`list[i]`, `flags[page * 6 + i]`) in place of a draft's explicit byte offset and
  running row counter, so the optimiser creates both as induction variables numbered after an inlined helper's
  locals; the two inductions take s-registers in the order of their first uses in the loop body (`0x42e330`);
* `#pragma opt_strength_reduction off` (kept in the source file);
* a harmless `li = (int)lst;` between a diamond and its loop test;
* `tools/dispatcher/regalloc.py` to read off which node ids must sit below which.

Shapes found on one function:

* `beNDMWStatusCtrlSendBit::vfunc_21`: the dispatch needs `case 1: default:` as one arm.
* `beNDMWLoadCtrl2::vfunc_31`: a loop-carried base reload and a goto-form count loop with the preheader written after the return.
* `beNDMWShopCtrlDeviceSell::vfunc_21`: `default: return;` first in the outer switch. In `-O3,p` the scheduler stops hoisting
  successor instructions into delay slots for the whole function once the post-RA jump optimiser deletes a jump to the next block.
  The effect needs a default with a real body, laid out first so the compare chain falls into it: `default: return;` triggers it,
  `default: break;` does not. Nop-filled delay slots across the ShopCtrl/StatusCtrl `vfunc_21` family are its symptom.
* `beFileListInfoManager::vfunc_27`: when both arms of an if/else assign the same local the front end turns it into a high-numbered
  IR temp, which flips the v0/v1 colouring; any harmless statement such as `li = (int)lst;` between the diamond and the test that
  reads it keeps the declared variable.
* `beNDMWShopCtrlDiskSell::vfunc_21`: per-branch block-local copies of the list-append locals fix s-register swaps.

### The system update, the node-clock timer and the LoadIntf2 update

* The beSystem update (`0x003a0020`, 1,300 bytes): see
  [system update recovery](system-clock.md#complete-besystem-update-recovery).
* The node-clock timer is in `src/game/bePadData.cpp`.
  A `const` timestamp snapshot, a `const` play-count load before subtraction,
  and reuse of the incoming parameter for the elapsed delta preserve the original
  parameter web and operand order. No inline assembly, fake arguments or compiler modification is used.
  A draft whose elapsed delta occupies `a0` instead of retail's `a1`, with
  one addition also using the commutative operands in the opposite order, differs
  at four words, and around 400 spellings of that draft do not resolve it. The traced need for an invisible
  interference node describes that draft, not every possible source form, so it does not make the
  function impossible in source.
  See [the clock recovery](stage-loading.md#clock-update).
* `beNDMWLoadIntf2::vfunc_31`: the complete 18,616-byte update
  is in `src/game/beNDMWLoadIntf2.cpp`, including the out-of-line
  helper copies it emits, nine jump tables, exception index and sixteen cleanup
  ranges/actions. See [the full recovery](load-intf2.md#matched-source).

### `beMatCtrl::vfunc_31`

A C++ spelling of `beMatCtrl::vfunc_31` (3,064 bytes)
reproduces five owner lifetimes, both destructor profiles and the complete
exception index/table, with ten differences in its main body. The manual-reference draft's five stale call
arguments are corrected. See [ownership and ABI evidence](material-contact.md#update-ownership-and-call-contracts).

The manual-reference draft differs at 11
words after about 80 attempts. Its blocker, found with `tools/dispatcher/regalloc.py`: retail's registers need `mbc` to have a higher
virtual-register id than the compare-chain temporaries (order 380 < 381 < 67), and every source form leaves named variables and hoisted
IR vregs below the chain temps, since the compiler numbers temps in textual order; the shared `li a3,1` additionally forces a loop-carried
`one = 1` that costs a delay-slot `li` where retail has a `nop`. Tried and ruled out: declaration orders, block-local vs function-level
locals, load and operand order, nine compare spellings, pointer locals, empty-destructor holders, inline helpers, `#pragma opt_*`,
`-O4,p`, `-Cpp_exceptions off`, loop forms. Adding the mbc/mac chains as named function-level webs makes the `and`/`xor` of both chains colour as retail and leaves the `sltiu` result of the first chain as the one wrong node: every compare lowering creates a late temp (id about 386) and `regalloc.py` says 67 < 386 < 68 would be needed.
That single-node diagnosis describes the manual-reference draft; it does not prove
all source forms impossible.

## Counting and verifying

`extern "C" { }` wrappers: `definitions()` in `tools/units.py` treats `extern "C" { ... }` as transparent (its definitions are top-level
ones; the wrapper stays in place when `extract` blanks the others), so functions inside a linkage block are counted like any other.
Skipping a linkage block as a "bare block" leaves such functions matched under `verify.py`
yet counted as unmatched in every tool.

A verifier must use the unit's own build profile: forcing `-O3 -Iinclude` on a function that needs the alternate compiler reports
`DIFFER` for source that matches. A recovery's result is the source *and* the config rows it needs.
