# Understanding a resisting shape

How to find out why a function compiles to bytes other than retail's, and what source the original had. A shape is
understood when the cause is known in the compiler's terms and the spelling that gives it has a reason in the code's
own terms. A search that only finds bytes is not understanding: it is the last resort, and its result carries a
`matching construct` comment.

The procedure comes first, then a last-mile checklist for drafts a few words off, then the instruments, then the
causes found so far, each with the unit where it turned up.
[Source idioms](matching-decomp.md#source-idioms) is the short list of shape and spelling; this document is the
method and the reasons.

## The procedure

1. **State the difference exactly.** First read what is already written about the function:
   `python3 tools/notes_for.py <symbol or 0xVA>` prints its status, profile and unit-objects row, the comments at its
   definition and every document line naming it, an earlier refutation or open note included. Then compile the
   candidate under the unit's profile and read the instruction diff:
   `python3 tools/check.py --no-cache --function 0xVA --cand <file>`, and for a whole listing
   `python3 tools/project.py cc --version SLUS-20836 <symbol> <file> <out>.o` then
   `mipsel-linux-gnu-objdump -dr -z <out>.o` (`-z` keeps runs of zero words: the three `nop`s MWCC pads a short
   loop with are otherwise printed as `...` and the listing looks 12 bytes short per loop). Write it down in
   machine terms: "the body reloads `52(s0)` where ours
   reuses the guard's load", "the count gets `a0`, retail's `a0` is the list", "four bytes short, the delay slot is
   filled". A size difference, an order difference and a register difference have different causes. A frame
   difference is stated slot by slot by [frame slots against retail](#frame-slots-against-retail).
2. **Read the function and its unit.** Real types from `include/dw4/support/reflected.h`, what each value is for, how the
   same class does the same thing elsewhere, and the GameCube and Xbox builds of the function (below). Most
   resisting shapes are an idiom of the original code base (an accessor, a smart pointer, a helper) that the draft
   wrote out by hand.
3. **Form a hypothesis about the source**, not about the bytes: "the original reads the list through a `const`
   accessor", "the original used the class's inline `next()`". A hypothesis names a construct a programmer would
   write. `python3 tools/levers.py --symptom "<the difference in machine terms>"` lists the causes below that share
   the symptom (`--format prompt` for a block to hand to an agent); each is a hypothesis until it reproduces here.
   The [signature census](#signature-census-of-a-residual) lists matched code with the shape retail has,
   which is where such a construct is found.
4. **Test one variable at a time, with controls.** Change one thing, compile, count the differing words. Include
   the controls that tell the hypothesis from its neighbours: the same accessor non-`const`, the same read through a
   pointer instead of a reference, the construct on the other side of the comparison, the construct in both places.
   Build the table: spelling against result. Small standalone test files with one function isolate the rule from the
   unit; run them under the unit's flags.
5. **Explain before landing.** The table says which construct does it; the instruments say why. Land a spelling
   when its reason is in the code's own terms and the controls agree with the explanation. If two spellings match,
   keep the more readable one. If the cause is known and the spelling is still a guess, say so in the topic
   document's open questions.

A delegated agent briefed on a resisting shape gets this document, the previous agent's report and its table of
spellings tried.

## Last mile

What to try first when a draft is a few words from retail. Each item names a cause below; `python3 tools/levers.py
--symptom "..."` finds the rest.

**First, write it the way the matched code around it is written.** Equivalent C is not identical C: `x > 0` and
`!(x <= 0)`, `if (f())` and `if (f() != 0)`, a `for` and a `while`, an early `return` and an `else` compile to
different branches, masks and blocks. Phrase comparisons, loops, switches, early returns and temporaries as the
function's matched neighbours in the same file do, and take an idiom from them before inventing one. The Gfx
library's metaobject tests are all `if (!g || ((g->_validity & 4) != 0) == false)` (`src/engine/gfx/*.inc`), a
flag test written `== false` throughout; `src/engine/p2draw.c` takes each element from its cursor as
`strip = header++;` and then stores through `strip`. A draft that spells the same test or walk another way starts
from bytes the original author never produced.

- **Two registers exchanged, instructions identical.** Declaration order and getters decide allocator ids
  ([declaration order](#declaration-order-and-evaluation-order)); a class local is numbered after every declared
  local; a parameter reached through a cast local or an inline cast, where the source used the real class as the
  parameter type ([casts of a parameter](#declaration-order-and-evaluation-order)); an enum-typed inline parameter
  ([types and values](#types-and-values)). Then the [register-allocator tracer](#the-register-allocator-tracer).
- **Operands or arguments in the other order.** A commutative add takes the plain variable first
  ([delay slots](#delay-slots-b52-1)); a conversion on an operand evaluates it first, an integer-typed argument is
  computed ahead of the others and a cast to `int` hoists loads ([scheduling](#scheduling-b52)); a typed prototype
  against a `(...)` one ([what a declaration changes at the call](#declaration-order-and-evaluation-order)); a
  sparse `switch` tests its cases in reverse source order ([control flow](#control-flow)).
- **One load or store in another place.** Under ee-gcc 2.96 an access moves past another only when their alias
  sets differ: an `int` against a pointer, two pointer types, an enum field or parameter, an address-taken local
  ([scheduling (EE GCC)](#scheduling-ee-gcc)). Under b52: an array element reloads after a store through it where a
  scalar pointer is reused, a `const float &` parameter reloads ([loads shared or kept apart](#loads-shared-or-kept-apart-b52)),
  a `const` reference getter reloads. Where the SDK has the object, its line table gives the statement order
  ([SDK and library archives](#sdk-and-library-archives)).
- **A delay slot filled where retail has `nop`, or the reverse.** b52: a deleted jump or a coalesced copy empties
  the predecessor lists, statement order around the branch ([delay slots (b52)](#delay-slots-b52)). ee-gcc 2.96:
  `bne`+`nop` against `bnel` is a `volatile` access at the target, a call's slot depends on whether the callee was
  compiled earlier in the same file, and a register whose last use filled an earlier slot
  ([delay slots (EE GCC)](#delay-slots-ee-gcc)). Then the `volatile`-only shapes ([`asm` and `volatile`](#asm-and-volatile)).
- **A few bytes long or short.** Narrow returns and parameters: a one-byte result is masked only where it is
  compared or widened, a one-byte parameter is narrowed at the call, a `float` behind `(...)` becomes a `double`,
  a `long long` parameter or result adds `dsll32`/`dsra32` ([types and values](#types-and-values),
  [what a declaration changes at the call](#declaration-order-and-evaluation-order)); a one- or two-byte global is
  `gp`-relative; a literal passed by `const &` becomes a data object; a `switch` with an empty case or a closing
  `return;`; a gcse-made jump around a loop entry ([loops (EE GCC)](#loops-ee-gcc)); MWCC's `asm` `li` encoding
  ([`asm` and `volatile`](#asm-and-volatile)).

## Instruments

### MWCC's optimizer IR dump

**When:** a load is shared or kept separate, hoisted or not, an induction variable appears or does not, and the
reason is not visible in the instructions. The dump shows what each optimizer phase did to the function.

The b52 compiler (`local/mwcps2/3.0b52-030722/mwccps2.exe`) still contains its IR dump code; its setup clears the two
switches. `tools/mwcc_irdump/` makes a copy with them set, outside the repository, and reads the log:

```sh
python3 tools/mwcc_irdump/make_dump_compiler.py local/mwcps2/3.0b52-030722/mwccps2.exe /tmp/irdump/mwdump.exe
python3 tools/mwcc_irdump/dump.py /tmp/irdump/mwdump.exe /tmp/irdump/t.cpp /tmp/irdump/out [--function 0xVA]
python3 tools/mwcc_irdump/ph.py /tmp/irdump/out/t.log --list
python3 tools/mwcc_irdump/ph.py /tmp/irdump/out/t.log "after IRO_CommonSubs"
python3 tools/mwcc_irdump/ph.py /tmp/irdump/out/t.log "" --fold --changes --all
```

The copy writes `<source>.log` beside the file it compiles, which is why `dump.py` compiles a copy of the source in
the output folder; its object is byte-identical to the retail compiler's. `--fold` prints each phase as statements,
`--changes` only the phases that changed the IR. The phases that decide loop shapes run in this order:
propagation, `IRO_PullOutInvariantAssignments`, `IRO_RotateLoop` (the `for` test copied in front of the loop as the
guard), `IRO_MoveInvariantsInAddressExpr`, `IRO_DoStrengthReduction`, `IRO_MoveInvariantExpressions`, the second
propagation round, `IRO_CommonSubs` (its "Replacing common sub at N" lines list what it shared), then propagation
again. `#pragma opt_dumptypes on` in the compiled file adds types.

The dump ends at the optimizer. What the code generator does afterwards (it hoists loads only out of the first block
of a loop) is read from the instructions.

### Tracing the compiler under gdb

**When:** the dump shows two expressions that look alike but are not merged, and the listing does not print the
property that differs. The scripts run the retail compiler (or the copy) under gdb and read the IR nodes in memory:

```sh
IRDUMP_OUT=/tmp/irdump/flags.txt MWCIncludes=src gdb -q -batch -x tools/mwcc_irdump/gdb_nodeflags.py \
    --args local/wibo local/mwcps2/3.0b52-030722/mwccps2.exe -c -O4,p -sdatathreshold 2 \
    -inline level=8,bottomup -Iinclude /tmp/irdump/t.cpp -o /tmp/irdump/t.o
```

- `gdb_nodeflags.py`: the `nodeflags` of every node after chosen phases (`IRDUMP_PHASES`). Bit `0x0001` marks a
  pointer-valued node whose target is `const`.
- `gdb_cse_compare.py`: each node pair `IRO_CommonSubs` compares and rejects, with the flags or types that differ
  (`node 384 vs 321: nodeflags 0000 vs 0001`). `IRDUMP_CALL` picks the function.
- `gdb_steptrace.py`: an instruction trace of one call of a compiler routine, to diff the path two spellings take.

Node numbers are the dump log's, so a node can be followed between the two.

### The code generator's blocks under gdb

**When:** instructions and registers are right and a branch's delay slot is filled where retail has a `nop` (or
the reverse), or to see the live sets the back end works with. The compiler's own dump of its code-generator
blocks is compiled out (its phase names remain: code selection, coalescing, CSE, loop invariants, scheduling
before allocation, register allocation, macro expansion, the block pass, scheduling after allocation, delay
slots), so `tools/mwcc_irdump/gdb_pcode.py` reads the blocks from memory around the delay-slot filler:

```sh
PCODE_OUT=/tmp/irdump/pcode.txt MWCIncludes=src gdb -q -batch -x tools/mwcc_irdump/gdb_pcode.py \
    --args local/wibo local/mwcps2/3.0b52-030722/mwccps2.exe -c -O4,s -sdatathreshold 2 \
    -inline level=8,bottomup -Iinclude /tmp/irdump/t.cpp -o /tmp/irdump/t.o
```

It writes every block with its predecessor and successor lists and its instructions on entry to the block pass
(0x4c6d60, the phase the compiler calls "block optimization") and before the filler runs, the use, def, live-in
and live-out sets of the general registers, and the blocks after filling. Between the first two dumps it writes
one line for every change the block pass makes, with the block and which of its three rules fired
(`== block pass: B79 retargeted the branch that ends it: the target began with an unconditional jump`), so the
construct behind a function's unfilled slots is the source of that block. Use a test file with one function.
The rules it lets you check are under [Delay slots (b52)](#delay-slots-b52).

### The register-allocator tracer

**When:** the instructions are right and only registers differ. `tools/dispatcher/regalloc.py` ties each register to
its allocator node and searches the id orders that give retail's colours
([usage](../../tools/dispatcher/README.md), [model](register-allocation.md)). It has a b52 profile and takes the
unit's compiler and flags from `units.tsv`; a whole-file candidate works (about a minute for `CoreLibrary.cpp`), and a test
file with the unit header, the inline helpers and the function traces in a second:

```sh
python3 tools/dispatcher/regalloc.py 0xVA src/engine/core/CoreLibrary.cpp
```

After the id permutations it tries single graph edits (renumber, merge, delete, interference, degree, un-coalesce) and pairs
of them, and names the nodes of the edits that give retail's colours
([graph edits](register-allocation.md#b52-coalescing-and-the-graph-edit-search)).

Coalescing on b52 (verified, [details](register-allocation.md#b52-coalescing-and-the-graph-edit-search)): every copy whose
two sides do not overlap is merged into the **lower** id before colouring, a copy between two declared locals included, and a
merged node adds no degree to its neighbours. So a local copy of a parameter keeps the parameter's id and cannot move its
colour.

Ids are what decide colours: select pops nodes in reverse id order, so a later id colours first. Declared locals
take ids in declaration order (parameters first). The locals and temporaries of inlined functions take theirs after
all of the caller's locals, mid-block C++ declarations included, and a second web of one variable takes a late id.
A local of class type is the exception: it has no id of its own. `IRO_ScalarizeClassDataMembers` replaces its
member with a temporary that takes its id after every declared local and every inline's parameter, wherever the
class local is declared (see [declaration order](#declaration-order-and-evaluation-order)).
Compiler-made values (a strength-reduced offset, a hoisted invariant, a CSE temporary) take ids when the phase that
makes them runs. So registers follow the order values come into existence, and a value that has to colour early is
the caller's declared variable, not an inline's local.

The order holds only for nodes simplify can push when its scan reaches them: a node whose degree is still at or
above the register count (32 for the float class on b52) is passed over and pushed on a later scan, so it pops
first and takes the lowest register. `regalloc.py` reports general registers only; `trace()` in
`tools/dispatcher/regalloc_trace.py` records the float passes too (`cls` 1: each node's id, colour, neighbours and
push order, and the IR that defines it).

### MWCC with its scheduler off

**When:** the instructions are right and a few sit in another order inside one block, or a branch delay slot holds
another instruction. `#pragma schedule off` at the top of a scratch copy (never in the unit) compiles the same code
without the scheduler, so the listing is in the order the code generator wrote it:

```sh
(echo '#pragma schedule off'; cat t.cpp) > t_natural.cpp
```

That order follows the source: statements in sequence, an inline's arguments from the last to the first, a bit-field
store as load, value, mask, merge, store. The scheduled listing hoists every constant and load that depends on
nothing ahead of the chain of stores, and puts off the user of a load until nothing else is ready. The compiler runs
the scheduler twice, before and after register allocation (its debug strings name "schedule before" and "schedule
after"), so the first run decides which temporaries overlap and with that their registers. The result is sensitive to
position: one more instruction at the head of a block exchanges a pair further down. Two spellings with the same
unscheduled listing and different scheduled ones differ in something the listing does not show, such as a register
copy that coalescing removes.

### The b52 scheduler trace

**When:** the scheduler-off listing is the same as retail's and the scheduled one is not, or two temporaries
share a register in retail and not in the candidate. `tools/mwcc_irdump/gdb_schedtrace.py` runs the compiler
under gdb and writes, for every basic block of both scheduling passes, the dependence nodes the scheduler built
and each pick it makes:

```sh
IRDUMP_OUT=/tmp/irdump/sched.txt MWCIncludes=src gdb -q -batch -x tools/mwcc_irdump/gdb_schedtrace.py \
    --args local/wibo local/mwcps2/3.0b52-030722/mwccps2.exe -c -O4,s -sdatathreshold 2 \
    -inline level=8,bottomup -Iinclude /tmp/irdump/t.cpp -o /tmp/irdump/t.o
```

What it shows about the scheduler (`Scheduler.c` in the compiler; the routine at 0x4c42f0 schedules one block):

- It is a forward list scheduler for a two-wide machine: each cycle it issues up to two instructions, then
  advances the clock. A node may be issued once all its predecessors are, and not before its `ready` cycle,
  which is the issue cycle of each predecessor plus the latency on the edge: 1 for arithmetic, 6 for a load, 0
  into the block's branch. So the user of a load waits six cycles and everything that depends on nothing is
  issued in the meantime, which is the "constants and loads first" look of scheduled code.
- The first pass (before register allocation) takes the first eligible node in list order, the order the code
  generator wrote, unless another eligible node scores better in its register-pressure function (0x4c3630; in
  the block traced, an `and` that ended two live values went ahead of an `andi` that ended none). Because the machine is two-wide and a result is not
  available in the cycle that makes it, one more instruction at the head of a block changes which pairs share
  a cycle further down: position matters, and so does the order in which an inline's arguments and body are
  written.
- The second pass (after allocation) prefers a node that has reached its `latest` cycle (it is on the block's
  longest path), then the node that frees more successors, then the longer path, then list order: the order
  the first pass left. Registers add edges (a redefinition waits for the earlier uses), and so does memory: a
  store ahead of a load in the list is a predecessor of the load, whatever the two addresses are, so a spill
  store ahead of an unrelated load puts that load on a longer path.
- Virtual register numbers in the first pass are the allocator's ids, so the trace also answers which of two
  temporaries was created first.

### EE GCC's scheduler trace

**When:** the instructions are right and only their order differs (a store or load issued earlier or later, a
move in place of a recomputed sum). Compile the unit with `-da -fsched-verbose-5`: the compiler writes the
dependence table, each instruction's priority and the ready list of every cycle to the `.sched` dump (before
register allocation) and `.sched2` (after it). Read the two together to see which dependence, or which missing
one, lets an instruction move.

### The strip test, for data and for `asm`

**When:** a `volatile`, a cast or an `asm` statement is in the source and the question is whether it does anything.
Copy the source, remove one keyword, verify the copy, and repeat keyword by keyword:

```sh
python3 tools/check.py --no-cache --function 0xVA --cand /tmp/strip/<file>
python3 tools/inline_asm.py --test <file>
```

What the result means is in [source approvals](source-approvals.md#testing-a-volatile): still matching means it did
nothing; same size in another order means it only steers scheduling; fewer instructions means it keeps a real access.
Then try the plain spellings that would keep the same access: `const` for `volatile`, another type of the same size,
an accessor. On an `asm` statement try the operand form the upstream text uses before concluding the keyword is
needed.

### Frame slots against retail

**When:** the diff shows stack offsets that do not agree, the frame size differs, or a slot is stored at another
point. `tools/frameslots.py` compiles the candidate the way `check.py` does and lists both frames: the size, the
saved registers by register, and every other slot with its widest access, whether its address is taken and the
instruction that first touches it. Slots are paired through the aligned instructions that use them, so a frame
16 bytes larger is compared from the top instead of marking every slot.

```sh
python3 tools/frameslots.py 0xVA --cand <file> [--registers]
```

The candidate's slots carry their source names. b52 writes DWARF 1 records under `-g`, one `.debug` and one
`.line` section per function, with each parameter's and local's location (a frame offset or a register, one per
variable) in declaration order, and `-g` does not change the code: every function body of the core unit and of two
game units (the `-O4,s` and `-O4,p` profiles) is the same with and without it (verified on b52). The tool still
compares the two bodies before using the records. `--registers` adds the register of every variable, which names
the parameter or local behind a register difference. A slot marked `early` is one the candidate writes before
retail does: a local initialised at the head of the function that retail initialises at its first assignment, for
example a smart pointer default-constructed at the top where retail constructs it from the call that fills it.

### Signature census of a residual

**When:** a hunk resists the obvious spellings, before calling it a floor or starting a permuter. If code that
already matches has the same retail shape, its source is a spelling that gives it (the idea is Persona 4's
"signature census before permuting"; the call-sequence form is dotr's `callsim`). `tools/residual_census.py` aligns
the candidate's masked listing with retail's, takes each hunk with a few instructions of context, masks registers
and immediates (keeping load and store widths, frame and small-data bases, branch directions and constant shift
amounts) and searches the retail code of every matched function that has source:

```sh
python3 tools/residual_census.py 0xVA --cand <file> [--registers] [--lines]
python3 tools/residual_census.py 0xVA --at 0xOFF:N        # a retail window, for a function with no draft
python3 tools/residual_census.py 0xVA --calls             # matched functions with the most similar calls
```

Hits are ranked by the same source file, then the same profile, and printed with the definition's `file:line`;
`--lines` compiles the hits with `-g` and prints the source lines behind the window (MWCC units only; a line outside
the definition is an inline's). When the full window has no hit the context narrows, and a long hunk is censused
again in pieces. A register-only hunk is censused only with `--registers`, which keeps each instruction's register
pattern (saved registers and temporaries renamed in order of appearance). Zero hits for a short window is a reason
to look at control flow and the parameters' types before spelling: a parameter zero-extended into a saved register
at entry (`dsll32 s0,a0,0; dsrl32 s0,s0,0` straight after the saves) has no hit in the matched corpus.

### The GameCube and Xbox builds

**When:** always, for a game function: the other two builds were compiled from the same source by other compilers,
so a shape all three share is in the source, and a shape only the PS2 build has is MWCC's. Read the function in the
GameCube `main.dol` and the Xbox `default.xbe` (find it by a constant or string it uses). Then compile the candidate
source with those compilers and compare loop for loop:

```sh
local/wibo local/mwcc-gc/extracted/GC/2.6/mwcceppc.exe -c -O4,p -proc gekko -Cpp_exceptions on -inline auto t.cpp -o t_gc.o
llvm-objdump -d --no-show-raw-insn t_gc.o
local/wibo local/xdk-5849/extracted/XDKSetup5849.17/XDK/xbox/bin/vc71/CL.Exe /nologo /c /O2 /EHa /FAs /Fat_xb.asm t.cpp
```

CodeWarrior for GameCube 1.3.2, 2.0, 2.6 and 2.7 gave the same loops; Visual C++ 7.1 from XDK 5849 matches the Xbox
build with `/O2 /EHa` (with `/GX` it reuses loads that retail reloads, so the Xbox build used asynchronous
exceptions). A source that reproduces the other two builds' loops as well as the PS2 bytes is strong evidence for
the original shape, and tells two spellings apart that are byte-identical on PS2. The other builds also settle
signatures: the Xbox `ret N` and the GameCube argument registers count a function's real parameters.

To find a class in the GameCube build, follow its name string to the registration call: that call also passes
the instance size and the vtable getter, whose last vtable store is the class vtable. GameCube vtables have the
PS2 build's two-word header and the same slot order, so a PS2 slot index finds the GameCube method directly;
Xbox vtables have no header. Reflected enumerations (the names and value arrays) and the per-class field-name
tables are platform-independent and name what the PS2 build's code reads by number, including fields and
classes the PS2 build dropped: a meta-object slot no code writes belongs to a class missing from the build, and
the PS2 `.bss` meta slots run in reverse alphabetical class order, which places it between its neighbours.

Xbox (Visual C++) tables group each overload set at its first declaration, so an Xbox slot index drifts from the
PS2 one around overloads (`createTexture`, `setTextureSource`, `setVertexArray`) and realigns after them; match the
slots by body and argument count (`ret N`) rather than by index. Alchemy 5.0 moved some 3.2 `igVisualContext`
methods into helper classes, so a slot the kit's `igVisualContext.h` lacks can still carry a kit name: the texture
component-size pair is `igDxTextureHelper::setTextureComponentSize`/`getTextureComponentSize` in the kit, with the
same arguments as the Xbox slots. The `igCommonTraversal` node-procedure table's metaobject slots are named from the
GameCube copy of the table, whose loads come from slots each registration call names (`addi r4, r13, <slot>` with
the class name in `r8`).

### SDK and library archives

**When:** a library function may be hand-written assembly, or a Sony routine may exist in the SDK. Extract the
members (`ar x LIB.a`) and compare:

- **Member bytes.** `mipsel-linux-gnu-objdump -d MEMBER.o` against `asm/`: a byte-identical member names the
  function and gives its source file.
- **Code alignment.** `mipsel-linux-gnu-readelf -S MEMBER.o` shows `.text`'s alignment. ee-gcc 2.96 at `-O2` aligns
  a C function's object to 8 and every loop top to 8 (`.p2align 3`); a 4-aligned object, or a loop top at 4 mod 8,
  was not compiled from C by it. C members also carry the `gcc2_compiled.` symbol.
- **`.mdebug` procedure records.** `python3 scripts/mdebug_procs.py MEMBER.o` prints each procedure's frame and
  return registers. The compiler writes `$29`/`$31` for every function it emits, leaves included; a routine
  assembled without `.frame` has `$0`/`$0`. Together with the procedure order this shows which functions of a
  member were C holding an `asm` statement and which were assembly.
- **`.mdebug` line numbers.** The same section holds a line table: each procedure's local symbols include gcc's
  `$LM<n>` labels, whose index field is a source line number and whose value is an address in the procedure.
  Mapped onto `mipsel-linux-gnu-objdump -d`, they give every instruction its source line, so a library function's
  statement order, the statement a stray load belongs to and where its locals were declared come from the SDK's own
  build. The ADX encoder's reference-signal setup (`src/cri/adxenc.c`, 0x2683e8) was laid out from it: the loop
  index declared first, the filter read after the period, the clamps as conditional expressions.
- **Source texts.** Where the SDK ships source or headers, the exact statement text (an `__asm__` with its
  operands and clobbers) is the strongest evidence there is.

### Retail RTTI records as names

**When:** a class, its base or a helper template has no name. Every polymorphic game class has an 8-byte
`__RTTI__` record, `{name, base list}`, whose base list holds every ancestor, root first. The names give the real
class (`Gap::Lua::igLuaGlue::Class`), its template bases (`Hashed<..., 7>`, whose argument is a real constant), and
which classes are game code. Destructor and template names in strings (`::~igSmartPointer<`,
`Gap::Core::igTDataList<...>`) name the helpers the original used. The census and layout are in
[RTTI and vtables](rtti-and-vtables.md).

## Causes found

Each entry: what the bytes show, why the compiler does it, the source spelling, and the unit where it was found.
Units are named by their source file. An entry is a `- **Title.**` bullet under a `###` heading with *Symptom:*,
*Cause:*, *Spelling:* and *Unit:* parts (or prose and a *Unit:*); `data/levers.jsonl` is generated from them by
`python3 tools/levers.py --write`, which is run after every edit here (`make hygiene` fails while it is stale).

### Loads shared or kept apart (b52)

- **A cast argument inside a loop is hoisted into a saved register.**
  - *Symptom:* one more saved register than retail, set to a stack array's address (`addiu s6,sp,N`) before a
    loop and copied into `a0` for a call inside it, and a frame 16 bytes larger; retail recomputes
    `addiu a0,sp,N` at the call like every other use of the array.
  - *Cause:* `f((int)path)` against a callee declared with an `int` parameter makes the argument a conversion
    node; the optimizer moves that loop-invariant expression out of the loop, while a bare array address is left
    in place.
  - *Spelling:* declare the callee with its real pointer parameter and pass `path`.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2ebde0 calling 0x2ebc40).
- **An array element reloads after a store through it; a scalar pointer global is reused.**
  - *Symptom:* `p->head = 0; p->tail = 0;` on a global packet pointer: retail loads the pointer again between the
    two stores (`lui; lw` twice) where the candidate stores both through one load, 8 bytes short.
  - *Cause:* the global is an element of an array; a store through an element read does not let b52 reuse the
    element for the next statement, while a scalar pointer global is loaded once. A `[4]` declaration of the same
    word matched only because it is an array; the real array with a constant index does the same.
  - *Spelling:* declare the real array and index it, `p2DmaCurrentPacket[P2_DMA_GIF]->head = 0;`.
  - *Unit:* `src/engine/p2texture.c` (0x2097f0).
- **A scalar passed by `const float &` is reloaded for every use.**
  - *Symptom:* a vector scaled by one value: retail loads the value again (`lwc1`) before each component's `mul.s`,
    where a by-value parameter keeps it in one FP register.
  - *Cause:* through the reference every use is a read of memory, and the component stores between them keep the
    reads apart, as for the `const` reference getter below.
  - *Spelling:* a vector member taking the factor by reference,
    `void scale(const float &s) { (*this)[0] *= s; (*this)[1] *= s; (*this)[2] *= s; }`, called `eye.scale(size)`.
  - *Unit:* `src/engine/igViewManager.cpp` (0x4643a0, 0x464760, 0x4648b0).
- **A release written through the field rereads it.** A macro that names `file->_media` at each use reloads the
  field after the count store; retail's single read comes from the form that takes one local copy
  (`RELEASE_REF`). *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2ebde0).
- **A field test through a pointer parameter shares the field's address across a store.**
  - *Symptom:* after `meta->_validity |= 8`, the next tests read the field through a computed address
    (`addiu v1,s2,36` ... `lw v1,0(v1)`) where retail reloads `lw v1,36(s2)`.
  - *Cause:* an inline test taking `const igMetaObject *` gives the common-subexpression pass the address
    `meta + 36` to share between the update and the test.
  - *Spelling:* the test takes the object by reference, `hasValidity(const igMetaObject &meta, int bit)`.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2fe9c0).

- **Two loads merge only when their types agree, `const` included.**
  - *Symptom:* a store reloads a pointer field the walk already loaded (`_data` loaded twice).
  - *Cause:* `IRO_CommonSubs` compares node types exactly. A getter taking `const List *` reads `_data` as a
    pointer to `const`, a setter taking `List *` as a plain pointer: two expressions.
  - *Spelling:* getter and setter take the same pointer type. Pointer-typed loads `T *` and `T *const` merge, as do
    two different pointer types; `int`/`const int`, `int`/`unsigned` and `int`/pointer do not.
  - *Unit:* `src/game/beNDMWShopCtrl00.cpp`.
- **A read through a `const` object is marked, and loop rotation keeps the mark.**
  - *Symptom:* a `for` loop's body reloads a field its own condition just loaded, while a neighbouring loop on a
    plain field shares the load.
  - *Cause:* every pointer-valued IR node carries the qualifier of its target; a field read through a `const`
    object (`this` of a `const` member, a `const T &`) has its address node marked. `IRO_RotateLoop` copies the
    condition in front of the loop with the mark; `IRO_MoveInvariantsInAddressExpr` rebuilds the address inside the
    loop without it. The node comparison requires equal flags, so the guard and the body are different expressions,
    and the body is a merge of two edges on which the value is not available. It needs the loop and something in it
    (a call, a store) that stops the read being hoisted.
  - *Spelling:* a `const` accessor taking the owner by reference, the way a `const` member function takes `this`:
    `static inline Util *utilOf(const Owner &o) { return (Util *)o._util; }`, used in the condition and the body
    alike.
  - *Unit:* `src/game/beNDMWLoadCtrl2.cpp`.
- **A `const` reference is not a pointer to `const`.**
  - *Symptom:* with a `const T *` accessor or cast the field's address is computed before the loop
    (`addiu a0,s0,52`) and loaded inside it; retail has no such instruction.
  - *Cause:* the qualification conversion `T *` to `const T *` is an IR node of its own, so `(const T *)p + 52` is a
    loop-invariant expression and is hoisted. Binding a reference, or `this` of a member function, makes no
    conversion node.
  - *Spelling:* take the object by `const T &`, or use a `const` member function.
  - *Units:* `src/game/beNDMWLoadCtrl2.cpp`, `src/game/beNDMWShopCtrl00.cpp`.
- **A cast that only retypes a read makes a different tree.** `*(int *)&o->f` or a smart-pointer view of an `int`
  field puts a conversion node between the address and the load, so that read never merges with a plain one. That is
  why one such read in exactly one of two places "works": it is a symptom of the two reads needing to differ, not
  the source. Look for the real reason the original's reads differ (the `const` mark above, an accessor).
  *Unit:* `src/game/beNDMWLoadCtrl2.cpp`; one such read is still open in `src/game/beNDMWShopCtrl00.cpp`.
- **Inline `const` accessors through a smart-pointer field keep a byte offset beside the index.**
  - *Symptom:* a search loop loads the list once, reloads the count every pass, hoists `_data` and keeps a byte
    offset in a register beside the index; plain field reads give a hoisted count and a walking pointer.
  - *Cause:* each inlined accessor leaves the pointer `operator->() const` returned in a temporary assigned where the
    call stands, behind a conversion. The body's temporary is assigned inside the loop, so `_data` is not an invariant
    base and `IRO_DoStrengthReduction` makes `i * 4` an offset stepped beside `i` instead of a walking pointer. The
    count read through `getCount() const` is `const int`; the guard's copy and the bottom test's are not merged, so it
    loads every pass. The code generator then hoists the `_data` load, because it hoists out of a loop's first block
    only. Registers follow creation order: index, row, offset, list, so the list colours first.
  - *Spelling:* the Alchemy idiom on the object-reference field held as a smart pointer:
    `for (int i = 0; i < ((ListRef &)self->_list)->getCount(); i++) { Row *row = ((ListRef &)self->_list)->get(i); }`
    with `getCount() const` and `get(int) const` on the list class. It reproduces the GameCube and Xbox loops as well,
    and needs no declaration order.
  - *Unit:* `src/game/beSound.cpp`.
- **A `const` parameter or local is bound before the expression.**
  - *Symptom:* a loaded value is the second operand of a multiply, or a load comes earlier than the plain spelling
    puts it.
  - *Cause:* b52 binds a `const` local, or the `const` parameter of an inlined function, to its argument before the
    body runs; a plain one is folded back into the expression.
  - *Spelling:* `static inline long long FramesToTime(const float frames)`. The older form `x = p->v; x = x;`
    gives the same code and has no reason.
  - *Unit:* `src/game/beCameraCtrl.cpp`.
- **An inlined getter's result is a value of its own.** `owned->_kazu = DiskCount(owned) + self->_kazu` gives
  retail's `addu` operand order where every plain spelling flips it; a getter for the selected row does the same
  for an index sum. *Unit:* `src/game/beNDMWShopCtrl00.cpp`.
- **A conversion on an operand makes it evaluate first.**
  - A float compare whose limit operand carries any conversion (a `const` getter's implicit `T *` to `const T *`)
    loads that operand later, into the later FP register.
    *Spelling:* `static inline float fadeLimit(const Work *w) { return w->_fadeLimit; }`. *Unit:*
    `src/game/beAction2.cpp`.
  - *Symptom, in a product:* three components of a local vector each times one float constant; retail has the first
    component in `$f3` and the constant in `$f2`, every plain spelling has them exchanged.
  - *Cause:* the optimizer puts the constant on the left of each product and the code generator makes the
    constant's temporary first, so it has the lowest allocator id and colours last (constant 32, x 33, traced).
    A component whose load carries two conversion nodes is evaluated before the constant (x 32, constant 33): a
    value conversion over the load, which a `const float` copied by value leaves behind when the copy is
    propagated into the product, and a pointer conversion under it, between the local's address and the load.
    Either one alone changes nothing: `const` and by value but indexed as `(&x)[i]` or `v[i]`, or the pointer cast
    with a reference return or without `const`, all give the exchanged registers.
  - *Spelling:* the vector's `const` element accessor returning by value,
    `float operator[](int i) const { return ((const float *)this)[i]; }`, and the call written out:
    `MakeEuler(matrix, 0.017453292f * rotation[0], 0.017453292f * rotation[1], 0.017453292f * rotation[2])`.
    An inline that copies only `x` into a local from a `const Vec3 &` bound to a `float[3]` gave the same bytes
    by making the same two nodes on one component; one is enough because the constant is shared.
  - *Unit:* `src/game/beModelCtrl.cpp`.
- **A `const` reference getter reloads.** `const int &getCount() const { return _count; }` loads through the
  returned reference, so a later `_count + 1` reads memory again, and the value lands in the caller's declared
  variable with its early id. It replaced a `volatile` count. The getter is `igTDataList<T>::getCount` in
  `include/dw4/core/igTDataList.h`. *Units:* `src/game/beNodeAnim_Traverse.cpp`,
  `src/engine/scenegraph/SceneGraphLibrary.cpp`.
- **A constant compared, then copied in the taken branch, is read twice.**
  - *Symptom:* after a call, `lw a1,<object>; lw a0,0(v1); lw v1,<object>; bne a0,v1`, and the taken path stores
    `a1`: one object loaded twice in a row, the first load used only after the branch.
  - *Cause:* the comparison and the copy both read the member through a `const T &` parameter (`operator==`, the
    copy constructor), as a `const int`. `IRO_CommonSubs` shares the two reads in a temporary assigned in front of
    the comparison. The next round's `IRO_ExpressionPropagation` puts the temporary's expression, a plain read of
    a named object, back into the uses in the temporary's own block. That is the comparison; the copy is in the
    next block and keeps the temporary. The read put back has lost the `const` mark and the temporary's own read
    keeps it, so the two are different expressions from then on and each is loaded. `const` on the object plays
    no part, since the mark comes from the parameters. Four spellings lose the second read: a `mutable` member (or
    `T &` parameters) makes every read a plain `int`, and one load then serves both; a read through a cast
    (`*(T *)&object`) is not put back; a helper that reads the value into an `int` before the comparison has both
    uses in one block, where they are put back and shared again (it gave two reads on a writable object only
    because `int` and `const int` reads never merge); and a store ahead of the copy in the branch drops the
    temporary, leaving one read before the branch and one after.
  - *Spelling:* `if (call() == g_resultFailure) return g_resultFailure;`, or `result = g_resultFailure;` as the
    branch's first statement, with the object declared as the result class (`igResult`).
  - *Unit:* `src/engine/core/CoreLibrary.cpp`.
- **A sorted search copies its key through a pointer.**
  - *Symptom:* before a binary search the key is stored to one stack slot, loaded, stored to a second slot, and the
    second slot is loaded again for the final equality test after the loop.
  - *Cause:* the caller's key is a local whose address is passed, and the search copies `*item` into a local of its
    own and reads that copy through a pointer, so both locals live in memory.
  - *Spelling:* `T key = light; index = list->sortedFind(&key);` with `igTDataList<T>::sortedFind(const T *item)`,
    whose body starts `value = *item; p = &value; key = *p;`. The order of its locals was found by a declaration-order
    search and is marked as such.
  - *Unit:* `src/engine/scenegraph/SceneGraphLibrary.cpp`.
- **An index passed on stays an `addiu`.** `addiu v1,v0,-1; sll; addu; lw 0(v0)` for the top of a stack, where
  `_data[_count - 1]` written in place folds the `- 1` into the load as `lw -4(v0)`. The index as an inline
  accessor's argument (`stack->get(stack->_count - 1)` with `T get(int index) const`) or as a named local
  (`int last = count - 1;`) keeps the subtraction. *Unit:* `src/engine/scenegraph/SceneGraphLibrary.cpp`.
- **In a loop built for size, an indexed read is loaded on every pass.**
  - *Symptom:* a scan loop reloads one table word each pass, through an address computed once before the loop,
    though nothing in the loop stores or calls and the word was already loaded for a test in front of the loop. A
    pointer local read as `*w` shares the load and is 20 bytes short; a cast on the pointer (`*(unsigned *)w`) keeps
    the read and is not the source.
  - *Cause:* written as `table[word]`, the read has an invariant address expression. `IRO_MoveInvariantExpressions`
    moves that address to a temporary in front of the loop and leaves the load of it inside: the unit builds
    `-O4,s`, which keeps the loop's test at the bottom behind a jump, so the read is not in the loop's first block.
    `IRO_CommonSubs` then makes the temporary a copy of the address the earlier read computed (one `addu`, one
    register), but a load through the temporary is not the expression loaded before the loop, so it stays. A
    pointer local leaves no address to move: `*w` in the loop is the expression read before it and takes its value.
    Under `-O4,p` the loop is rotated and the same source shares the load.
  - *Spelling:* index the table at every read (`if (mask & table[word])`), with no pointer or value local. The
    same source compiled by CodeWarrior for GameCube 2.6 with `-O4,s` gives the GameCube build's function word for
    word, which also settled the statement order, a `>= 1` comparison and the parameter's pointer type. The Xbox
    build shares the load, so the source has no `volatile`.
  - *Unit:* `src/engine/core/CoreLibrary.cpp`.
- **In a loop built for size the count is hoisted and `_data` is not: the list idiom again.**
  - *Symptom:* a list walk loads the list and its count once in front of the loop and `_data` on every pass
    (`lw a2,20(a0); lw v1,8(a2)` before, `lw v0,16(a2)` inside), with the count in `v1` and the scaled index in
    `a0`. A list local, plain field reads, a count local and `count()`/`get()` on a cast pointer all give the same
    instructions with the count and the scaled index exchanged, four bytes longer because the delay slot of the
    loop's branch stays empty.
  - *Cause:* under `-O4,s` the loop is entered at its test, so the test is the loop's first block and the code
    generator hoists the loads the test holds, the list and the count; the body's `_data` load stays. That needs
    the optimizer to have left the count in the test: the pointer `operator->() const` returns is a temporary
    assigned where the call stands, which keeps the read from being moved as an invariant (an assignment written
    in the condition does the same). A count the optimizer hoists takes the register after the scaled index; the
    allocator's numbering of the two was not traced.
  - *Spelling:* `for (int i = 0; i < ((ListRef &)self->_objects)->count(); i++) { T *o = ((ListRef &)self->_objects)->get(i); }`.
    An assignment inside the condition (`while (i < (list = self->_objects)->_count)`) and the pair count kept in
    the function's first parameter were stand-ins for it, and so were extra arguments passed to a variadic callee to
    hold the index and the object in `t0` and `t1`: with the idiom the callees take their real three and four
    arguments.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2fed50, 0x3064b0, 0x306510, 0x2d6f50).
- **Both list walks in one function.** A function that first searches one list and then walks another has the
  first count in the register after the scaled index and the second count in the register before it. The search
  is an inline helper with `list->_count` in its condition (the optimizer hoists that count); the walk is the
  smart-pointer idiom above. The list handed on after the loop goes through the holder's `get()`, a `const` read
  that shares the load hoisted for the walk (`move a0,t2`; the plain field read loads again). A named local for
  the searched list, which the walk's inner loop reads again, gave that node so many neighbours that it was
  coloured first and took the lowest register; with the field read in place every local is declared where it is
  first set and no declaration order is left to choose. *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2d6f50).
- **A second read of a field through a `const` getter is a second load.** `lw s1,60(s2); jal TerminateThread;
  lw a0,60(s2)`: the id saved for later and the id passed to the call are loaded separately with nothing between
  them. The saved copy is a plain read (`int id = self->_threadID;`), the argument goes through the class's `const`
  getter, a `const int` read. The getter on the saved copy instead gives the two loads too but numbers the copy
  after the call's result, and their saved registers are exchanged. *Unit:* `src/engine/core/CoreLibrary.cpp`
  (0x32fd50).
- **Calling a member of a smart-pointer local changes its destructor's release.**
  - *Symptom:* a function holds a returned smart pointer in a stack slot, reads it once into a register for its
    tests, reads it again for a call's argument, and its destructor's release, at the early return and at the end,
    reads the slot once. With every read spelled `.p` each release reads the slot again after storing the count
    (8 bytes more); with every read spelled `get()` the early return loads the slot twice (4 bytes more).
  - *Cause:* the inliner folds the release's parameter back into `found.p`, read wherever the parameter is used,
    as long as nothing takes the local's address. A member call does (`this`), and the parameter is then bound to
    a temporary once. The destructor's read is unmarked; a read through a `const` accessor is marked and is not
    shared with it. Retail's first read is shared with the early return's release, so it is unmarked, and the
    argument's read comes from a member call. With non-`const` accessors `entry = found.get()` and
    `call(found.get())` give retail's bytes; the shared class's accessors are `const` (184 uses outside this unit),
    so the first read is the member itself.
  - *Spelling:* `Entry *entry = (Entry *)found.p; ... remaining = unload((Handle *)found.get());`.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x309750).
- **A temporary smart pointer's release reloads the pointer.**
  - *Symptom:* a freshly created object is assigned to a field, then released with the slot read twice:
    `lw v1,104(sp); beqz v1; lw v0,4(v1); addiu v0,v0,-1; sw v0,4(v1); lw a0,104(sp); lw v0,4(a0); dsll32 ...`.
    The out-of-line destructor of the same template (0x130140, and five copies in this unit) reads the member
    once, so the reload looked like a second holder class with a re-reading destructor.
  - *Cause:* the holder is a temporary: built in an argument bound to a `const igSmartPointer<T> &` parameter of
    an inline, or returned by value and used in place. Its destructor runs at the end of the full expression
    with the release's parameter folded back into the temporary's member, as in the entry above. A named local
    passed to the same inline has its address taken and is released from one read (0x2e3a60: 580 bytes against
    retail's 588). The compiler pass was not traced.
  - *Spelling:* `assignReference(self->_file, igSmartPointer<igFileView>(create(pool)));` and
    `found = openPath(self, folder.p->vfunc_23(name));`, written in the function itself. The same call inside a
    second inline helper's `return` reads once (0x305d30: 1152 against 1160).
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2e3a60, 0x2e3f50, 0x2e82a0, 0x305d30, 0x2da1c0, 0x308860).
- **A returned pointer taken through the holder's conversion keeps its own copy for the release.** `lw s0,140(sp);
  move a0,s0; beqz a0; move v0,s0`, with the count updated through `a0`: `return holder;` (`operator T *`) or
  `return holder.get();`. `return holder.p;` shares the read with the destructor and updates the count through
  `s0` (856 bytes against 868). *Unit:* `src/engine/core/CoreLibrary.cpp` (0x307c10).
- **A base pointer the walk keeps is a field read, not the cursor.** `end = list->data + list->count` after
  `s = list->data` shares one load of `data` with the cursor's start and with the `s - list->data` the function
  returns, and that shared value keeps its own register; `end = s + list->count` makes the cursor the base and
  exchanges the base's register with the compared word's. The order of the two statements does not matter. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x2d3d30).
- **One address spelled two ways is computed twice.** A stack buffer's member address used by two calls in a
  loop (`entry.name` for a format and for an `igStringRef`) is common-subexpression-eliminated into a saved
  register; retail builds it at each use (`addiu a3,sp,208` and later `addiu s3,sp,208`). Spelling one use as
  pointer arithmetic (`(char *)(&entry.stat + 1)`, the byte after the stat) and the other as the member keeps them
  apart; casts or `&entry.name[0]` on the same member are folded together. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (`igPsx2Folder_ListFiles`).
- **A cast between a base and a field leaves an address to move, and reads that do not merge.**
  - *Symptom:* a function with loops has one more 16-byte stack slot than retail and loads a byte through a
    spilled pointer (`lw v0,176(sp); lbu v0,0(v0)`) where retail reads it off the base (`lbu v1,75(s2)`); and a
    validity check loads one header byte three times where retail loads it once and masks it (`andi v0,v0,0xff`).
  - *Cause:* the state record declared its bins as raw bytes and its top chunk as `char *`, so each use went
    through a cast to the chunk type. The cast is a node between the base and the field offset: inside a loop
    the cast address is an invariant expression, moved to a temporary in front of the loop, and the temporary
    is spilled. A cast pointer passed to three inline accessors gives three reads that are not shared; the
    member read in its own type is one expression, shared in a byte temporary.
  - *Spelling:* type the members: the top as a pointer to the chunk header, a bin as a struct whose first
    member is the header, and `&state->bins[i].header` for a bin. The other functions of the allocator matched
    with either typing; only the ones with loops tell them apart.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (the arena allocator, 0x315170).
- **What `IRO_CommonSubs` shares, and what stops it (probed).**
  - A load repeated with nothing between is shared whatever its base: a global field (`G.c`), a field through a
    pointer parameter (`p->c`), a member at offset 0 (`p->a`). The GameCube rules "a register-local base is never
    a candidate" and "offset 0 is never one" do not hold on b52.
  - A call or a store through a pointer kills the shared load; a store to a plain local does not.
  - Once the load is killed, a field address is not kept: `G + 8` and `p + 8` are reloaded as `lw 8(at)` and
    `lw 8(a0)`, never `addiu t,base,8; lw 0(t)`. An indexed address is kept across the store for a global array
    and a pointer parameter alike (`Garr + (i << 2)`, `p + (i << 2)`), and the index `i << 2` takes a temporary of
    its own beside it.
  - The temporary is created at the second occurrence. In `*q = i * 12; q[1] = j * 20; q[2] = j * 20;
    q[3] = i * 12;` the dump numbers the `j * 20` temporary first (`@9`, `@11`); with `q[2] = i * 12; q[3] = j * 20`
    the `i * 12` one is first (`@20`, `@22`).
  - *Probe:* `ph.py <log> "after IRO_CommonSubs" --fold --all` on
    `struct S { int a, b, c, d; }; S G; int Garr[16]; void h();` with
    `int k1(int *q) { int x = G.c; *q = 1; int y = G.c; return x + y; }`, the same through `S *p`, with `h()` in
    place of the store, with `int z = a; z = z * a;` in its place, and with `Garr[i]` / `p[i]`.
- **A load right after a store to the same base and offset becomes a register copy.**
  - *Symptom:* a squared-distance check against a local vector whose `y` was just set to 0 (`flat = centre;
    flat.y = 0.0f;`): retail has no load of `y`, the stored zero stands in for it; the plain spelling with `dx`, `dy`
    and `dz` locals loads it. In a ride-on move, retail has `mov.s $f1,$f3` where the plain spelling has a load.
  - *Cause:* a peephole (0x5153c0) turns a load into a register copy when the instruction immediately before it is a
    store to the same base and offset. It runs before register allocation, where the copy is merged away, and again
    after it, where the `mov.s` survives. A load of another member between the store and it ends the forwarding, and
    so does an index read through a separate address expression, which puts a temporary between store and load at
    the first pass. Standalone probes: the forwarding happens when the `y` load comes first and stops as soon as an
    `x` load sits between the store and it. The GameCube build has the same store and load, so the rule is b52's.
  - *Spelling:* the distance as one expression with no difference locals, `(a.x - b.x) * (a.x - b.x) + (a.y - b.y) *
    (a.y - b.y) + …`, which puts the `y` load first after the store. Locals declared in the order `dy`, `dx`, `dz`
    give the same bytes and are the less natural spelling. The ride-on move reads and stores its vector through the
    unit's `at(i)` accessor.
  - *Unit:* `src/game/beChangePosTransform.cpp` (0x37aae0), `src/game/beModelCtrl.cpp` (0x3923c0).
- **A pointer declared ahead of a branch gives one load and a shared delay slot.** A transform pointer
  (`float *transformMatrix = ((igTransform *)info->_transform)->_m;`) declared in front of the `if` that guards the
  arms of a `switch` is the single load before the branch, in a delay slot the branch shares, as in retail. *Unit:*
  `src/game/beChangePosTransform.cpp` (0x37aae0).
- **A test then a fetch through the list holder keeps the list read as its own statement.**
  - *Symptom:* in a loop that tests an element's flag and then fetches the same element in its body, the scaled
    index is computed before the list is loaded where retail loads the list first, which gives it `a0` (3 words).
  - *Cause:* the test's `operator->() const` read of the list and the body's are one common subexpression, a
    temporary used in a block other than its own, so the later `IRO_ExpressionPropagation` leaves it in place. The
    list load stays a statement ahead of the shared `index << 2`, and in the first scheduling pass the list is live
    across the shift. With a single read the temporary is folded back into its read and the shift goes first.
  - *Spelling:* both reads through the holder: `if (((EnemyRamListRef &)work->_enemyRamList)->get(index)->_isRun == 0)
    { beBaseInfoRam *enemyRam = ((EnemyRamListRef &)work->_enemyRamList)->get(index); … }` with `EnemyRamListRef` an
    `igSmartPointer` of the list class. The same test-then-fetch through a plain list pointer, a list local, plain
    field reads in the condition, pointer arithmetic and an `unsigned` index each leave the 3 words; a `const int &`
    accessor is far worse.
  - *Unit:* `src/game/beGenerater.cpp` (0x384800).

### Propagation (b52)

- **A local that only ever holds zero is added as the zero register.**
  - *Symptom:* `addu v0,v0,zero` after a call, in front of the add that sums the result (objdump prints it as
    `move v0,v0`; the compiler's own moves are `daddu`). No type of the sum or of the callee gives it.
  - *Cause:* the source adds a non-`const` local whose value is 0. `IRO_CopyAndConstantPropagation` replaces
    the local with 0 after the front end's folding has run, and `IRO_ConstantFolding` only moves the constant to
    the right: it does not remove `x + 0`. A literal `+ 0` and a `const int` are folded by the front end.
  - *Spelling:* `int padding = 0;` and `size += field->ioSize(object) + padding;`. Where the local is declared
    and which side of the sum it stands on make no difference. What the zero stood for in the original is not
    known; the name is a guess.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2d5960). The `x + 0` survives there because its left operand is a
    call: `DoTransformations11` (b52 0x5201b0) drops `x + 0` unless an operand has a side effect, is a float, or the
    zero is not a `TYPEINT` constant (`IRO_IsIntConstant`, 0x4f9a20, checks the operand's type).
- **`x == a || x == a + 1` keeps its `+ 0` when `x` is read through an inline getter returning an enum field.**
  - *Symptom:* `lw v1,N(s1); addu v1,v1,zero; sltiu at,v1,2` (objdump `move v1,v1`): a range test of a field.
  - *Cause:* pass 0's `IRO_CommonSubs` turns the twice-read field into a temporary, and pass 1's
    `IRO_SimplifyConditionals` merges the two compares into `(unsigned)(t + -a) <= 1`, typing the constant as the
    temporary's read. The front end retypes an enum operand of `==` to `int` in place, so a field or local read
    makes an `int` temporary and `DoTransformations11` drops the `+ 0`. An inline getter's inlined body keeps the
    field's enum type (the compare retyped the call node), so the temporary and the merged zero are `enum` and the
    zero is not an int constant. A getter returning `(Enum)intField`, a direct enum field or local, an enum
    parameter, `(int)` casts, a `switch` and `>= && <=` all lose it.
  - *Spelling:* the kit's `IG_VERTEX_ACCESS_MODE getAccessMode() { return _accessMode; }` over the enum-typed
    field, `s->getAccessMode() == IG_VERTEX_ACCESS_READ_WRITE || s->getAccessMode() == IG_VERTEX_ACCESS_READ`.
  - *Unit:* `src/engine/gfx/GfxLibrary.cpp` (0x17f080, the `addu` at 0x17f1bc).
- **An expression goes back into its use only when the variable has one use in its block and none in another.**
  Read from the compiler (`IRO_ExpressionPropagation`, 0x5263b0): for each assignment `v = expression` it counts
  the uses of `v` in the same flow node; a constant or a plain copy is always propagated, any other expression
  only when that count is 1 and no other flow node reads `v`. Flow nodes are not merged again once the pass loop
  has started. `v += constant` is merged into the later uses by `IRO_PropagateSelfAssignments`;
  `v += <a load>` stays as it is, even when `v` holds a known constant. What this means for registers: the
  optimizer's variables (declared locals, an inline's parameters and locals, the optimizer's temporaries, in the
  order they are made) take their allocator ids before every expression temporary of the code generator, so a
  value that stays a variable is coloured after the expression temporaries around it, and a value that is put
  back into its use is coloured before the variables.
- **The list reserve in front of an append: the capacity is shared by the code generator, not the optimizer.**
  - *Symptom:* five functions double a list's capacity when `count + n` no longer fits
    (`lw count; lw capacity; add; slt at,capacity,sum; beqz at; sll a1,capacity,1; lw count; slt; bnez; jal`),
    with the sum in the count's register `v1` and the capacity in `v0`. A helper or plain field reads give the
    same instructions with `v0`/`v1` exchanged.
  - *Cause:* with plain reads `IRO_CommonSubs` shares the capacity between the test and the doubling in a
    temporary of its own, which is numbered before the code generator's temporaries for the count and the sum,
    so the sum colours first and takes `v0`. In retail the optimizer shares nothing: each read goes through its
    own `operator->() const` temporary, the two capacity reads are still different expressions when
    `IRO_CommonSubs` runs, and the final IR has `count + n > capacity` as one expression in the first block and
    `capacity * 2` in the next. The code generator then evaluates count, sum, capacity in that order and reuses
    the capacity's load in the following block itself, so the capacity has the last number and colours first.
    The count is read again for the setter's own test because that read is not through the `const` accessor.
    What keeps a variable out of its use was read from `IRO_ExpressionPropagation` on the way: an assignment
    whose value is used, a right side holding a call, an assignment or a `volatile`, a second use in the block,
    a use in another block, or a store or call between the assignment and the use.
  - *Spelling:* the list idiom on the object-reference field, with `const` accessors for both members and the
    list's capacity setter:
    `if (((ListRef &)self->_list)->count() + n > ((ListRef &)self->_list)->capacity()) setCapacity(((ListRef &)self->_list).get(), ((ListRef &)self->_list)->capacity() * 2);`
    with `setCapacity(list, capacity) { if (capacity >= list->_count) List_Reserve(list, capacity, sizeof(T)); }`.
    A count kept for later is read through the same accessor first (`offset = ((ListRef &)…)->count();` then
    `length + offset > …capacity()`): the two functions that held the sum with an assignment inside a helper's
    argument (0x2d3be0, 0x30d230) give retail's bytes with it too.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x30e000, 0x2eb6d0, 0x2dd1c0).
- **A cast self-assignment is not merged, so the variable keeps its own register.**
  - *Symptom:* a checksum's prologue steps the size parameter in place (`addiu a2,a2,-4`); every plain spelling
    (`size -= 4`, `size -= sizeof(int)`, `(size - 4) >> 2`) builds `size - 4` in a fresh register that colours `v0`.
  - *Cause:* `size - sizeof(int)` is computed unsigned and converted back to `int`, so the statement is `size =
    (cast)((cast)size - 4)`. `IRO_PropagateSelfAssignments` only merges `v = v + constant`, so this one stays, and
    `size` keeps its register. A merged spelling puts `size - 4` in a temporary that interferes only with `zero` and
    `a1` (register tracer) and colours `v0`.
  - *Spelling:* `size = size - sizeof(int); int count = size / sizeof(int); data++; for (int i = 0; i < count; i++)
    sum += *data++;` with `size` an `int`, as the reflected `_dataSize` field is.
  - *Unit:* `src/game/beSaveApi.cpp` (0x3a9a50).
- **A second reaching assignment blocks the first constant-propagation pass.**
  - *Symptom:* a traversal loop that sets `result = 0` in one branch and tests `result == 1` and `result == 2` in
    the same pass: retail keeps both tests and the loop test inline at the top; every plain spelling loses the tests
    and has the loop test copied into a guard after the body.
  - *Cause:* the first constant-propagation pass replaces `result` with 0 in the tests when that is the only
    assignment reaching them, and deletes the tests. The loop then has one exit, and the compiler copies its test into
    a guard placed after the body; a loop with several exits keeps the guard inline. A second assignment to `result`
    that reaches the next iteration stops the propagation. An inline taking `int &result` does the same and keeps
    `result` in a register, but its return value turns the `== 2` test into `sltiu`, which retail does not have.
  - *Spelling:* the subtree's pop in a helper taking the result as a `const int` parameter and returning it,
    `result = PopSubtree(traversal, attrs, index, result);`: the copy assigned back is the second assignment, and the
    pop and the time pop stay in the helper. The attribute stack typed `igTDataList<igAttr *> *` (a cast makes the
    compiler share `stack + 8` inside the loop, where retail reloads `8(s0)`), the number branch's time attribute in
    a variable of its own (spill slot order) and a note on the x component of the translation carry over.
  - *Unit:* `src/game/beModelCtrl.cpp` (0x390320).

### Inlining (b52)

- **Trivial inline members are calls inside an expanded constructor or helper.**
  - *Symptom:* a constructor or helper is expanded into its caller, yet every inline it uses is a `jal`, down to
    empty constructors (`jr ra; move v0,a0`) and two-store setters; the same members cost nothing elsewhere.
  - *Cause:* the unit builds with `-inline bottomup`. Bottom-up inlining expands an inline function's callees
    first, and when that would take the function past `inline_max_size` (256) it keeps all of them as calls and
    still expands the function itself. Top-down inlining expands everything, and `-inline level=1` gives the
    same calls but also in every small helper of the unit.
  - *Spelling:* the members inline in their one shared header and the unit's row on `-inline level=8,bottomup`.
    An out-of-line declaration in a private copy of the class gives the same bytes and is not the source. The
    copies the linker dropped are `duplicates` of the unit, so the unit holding retail's copy is bottom-up too.
    The reverse case: a hand-made helper that calls inline helpers and is fully expanded in retail was not a
    function holding inline calls; write the statements in place.
  - *Units:* `src/engine/igViewerGuiFactory.cpp`; the reverse case in
    `src/engine/gfx/igVisualContextCapabilityManager_tail.inc`. The measurements are in
    [build profiles](build-profiles.md).

- **A scoped object with a constructor and a destructor keeps its member in memory.**
  - *Symptom:* a pointer the function already holds in a saved register is stored to the stack and loaded back
    before each of two calls (`sw s1,172(sp); lw a1,172(sp)`), and nothing else uses the slot.
  - *Cause:* a local of a class with a destructor is not scalarized; its inline constructor and destructor read
    the member through the object.
  - *Spelling:* the original's scoped helper: a struct holding the pointer whose constructor and destructor make
    the call, declared in the guarded block. Its out-of-line destructor copy is a `stripped` row.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (the arena allocator's entry points).
- **A check that cannot fail still shares its loads.**
  - *Symptom:* a field is loaded ahead of a guard and first used after it, with no reload, while every later use
    reloads it.
  - *Cause:* the source tests the field in a check whose condition is constant, ahead of the guard. Common
    subexpression elimination gives the dead check and the live one a shared temporary before the dead one is
    removed, and the temporary's load stays where the dead check stood. Two dead checks before the guard number
    the temporary differently from one.
  - *Spelling:* keep the original's constant checks, in place.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (the arena allocator's state checker).
- **A function past the bottom-up budget leaves its helpers' callees out of line, and their copies follow it.**
  - *Symptom:* after a very large function retail holds out-of-line copies of the helpers it calls (a clear loop, a
    release loop, a retained assignment), in the reverse order of their first use. Written as true inline helpers in
    that function they make it 256 bytes longer than retail's.
  - *Cause:* in bottom-up mode MWCC stops expanding the calls inside an inlined body once the caller passes
    `inline_max_total_size` (10000 expression nodes after inlining; [build profiles](build-profiles.md)). Retail's
    large function is over the limit, so the calls inside its inlined helpers stay out of line; the reverse order
    of the copies fits inline helpers whose out-of-line copies were emitted after the function that first used them.
    Bisecting `#pragma inline_max_total_size` puts the source's function at about 6245 nodes, and with the
    pragma at 6000 the whole unit matches with true inline helpers. The missing nodes were not reconstructed: turning
    allocator macros into inline calls adds none.
  - *Spelling:* the clear and release loops written once as `static inline` helpers and the out-of-line functions
    as one-line wrappers over them, the large function keeping its explicit calls. This reaches retail's bytes
    without its node count and carries a `matching construct` note.
  - *Unit:* `src/game/beNDMWListCtrl.cpp` (0x4165d0; the large function is 0x41acf0).

### Control flow

- **An inlined `void` helper's early `return` jumps to the caller's single return.**
  - *Symptom:* the fall-through branches to the function's one `return *this`, the other case goes straight to a
    loop test, and an early `return *this` written in place costs a second return sequence.
  - *Spelling:* the iterator's `next()` step as an inline with `if (node != 0) return;`, called from `operator++`.
  - *Unit:* `src/engine/lua/LuaScript.inc`.
- **A statement macro stops a tail call under GCC 2.96.** `j` where retail keeps `jal` and the frame: under 2.96 a
  loop statement around or after the call prevents the sibling call, and `do { ... } while (0)` is one.
  *Spelling:* `#define LOCK() do { lock(); } while (0)`. *Unit:* `src/cri/lsc.c`.
- **A statement macro also pins store order under GCC 2.96.** Independent stores stay in source order where the
  first scheduling pass would move the argument's store first: a loop statement's notes are a scheduling barrier,
  and an empty `do { } while (0)` at function entry is enough. An `if (0)` or an empty block is not.
  *Unit:* `src/cri/sftim.c`.
- **An `else if` chain with an empty first arm.** `beq x,1` past the arm then `bne x,2`: MWCC keeps the empty arm's
  compare. *Spelling:* `if (x == 1) { } else if (x == 2) { ... }`. *Unit:* `src/movie/igCriMovieCodec.cpp`.
- **A switch with an explicit empty case.** A compare chain `beq 2; beq 1; beqz end; b end` is a switch with
  `case 0: break;` written first and then cases 1 and 2 (the chain runs in reverse source order, next entry);
  without `case 0` the function is 8 bytes short, with `case 0: return;` 8 long. *Unit:* `src/game/beAction2.cpp`.
- **A switch that compiles to a compare chain tests its cases in reverse source order.**
  - *Symptom:* a run of `li v0,K; beq a0,v0,L` whose constants are neither sorted nor in the order the case bodies
    sit in.
  - *Cause:* b52 emits one `beq` per case label, the last label first, and lays the case bodies out in source
    order. It neither sorts the labels nor merges consecutive ones into a range test. Probe:
    `switch (x) { case 100: ...; case 3: ...; case 50: ...; case 7: ...; }` tests 7, 50, 3, 100 and places the bodies
    100, 3, 50, 7; labels `'u' 'x' 'c' 'd' 'e' 'f' 'g' 'n'` sharing one body give eight `beq`s from `'n'` back to
    `'u'`.
  - *Spelling:* the case labels in the reverse of retail's test order, the bodies in retail's layout order.
  - *Unit:* `src/engine/gfx/GfxLibrary.cpp` (0x1586d0).
- **A constant on the left keeps `slt`.** `if (capacity >= list->_count)` with `capacity` 0 gives `slt zero,count`
  and `bnez`, where `count <= 0` folds to `blez`; a `bool` local compared `== false` keeps the materialised test.
  *Units:* `src/game/beDemoManager.cpp`, `src/game/beSound.cpp`.
- **A conditional expression keeps both arms; an `if`/`else` that assigns a variable to itself loses one.**
  `beqz flag; b; move a0,v0` around a second call whose result is also moved to `a0` is
  `pool = g_useOwnerAllocator ? pool : Memory_GetAllocatorBySelector(...)`. Written as
  `if (flag) pool = pool; else pool = ...;` the self-assignment is deleted and the function is 8 bytes short;
  `pool = (int)pool;` kept it only because the cast hides the self-assignment. *Unit:* `src/game/beModelCtrl.cpp`.
- **A bare truth test that opens a loop condition is materialised.** `sltu v1,zero,a0; xori v1,v1,0x1; bnez`
  for the first operand of `while (*a && *b && *a == *b)`, and a plain `beqz` for the second: the strcmp shape
  written plainly. `*a != 0` there folds to `beqz`, and a `(bool)` cast is not needed. The remaining count of a
  bounded scan does the same in `while (remaining && *p)`, with the cursor declared before the count. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x2d3d30, 0x30ab20).

- **A `goto` into the tail keeps a loop's constants inside it.**
  - *Symptom:* a chunk walk loads `li v1,1` and `li v1,-4` on every pass in retail, and the `if (cur != top) {
    while … }` spelling hoists both in front of the loop (same length, other registers).
  - *Cause:* with the loop inside an `if` the optimizer has a place for a pre-header. Written flat, with the
    skip as a jump over the loop to a label in the function's last block, it hoists nothing.
  - *Spelling:* `if (cur == top) goto reset; while (walk < end) { … } … if (inUse == 0) { remove(); reset: …;
    return success; } return failure;`. The label sits inside the final `if`, which also puts the failure
    return last, as in retail.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x314b50).
- **A value computed on every pass is hoisted with a guard; one under `||` is not.**
  - *Symptom:* retail tests `0 < count` once (`sltu at,zero,n; beqz at`), loads `pool->_poolIndex >> 1 < 32` in
    that guarded block (placed at the end of the function) and still jumps to the loop test. With
    `if (size >= 0x80000 || (unsigned)pool->_poolIndex >> 1 >= 32)` in the body the load stays in the loop
    and there is no guard.
  - *Cause:* the second operand of `||` does not run on every pass, so it is not invariant code to move. As an
    inline's argument (or a body local) the shift runs unconditionally; the optimizer moves it, and because
    it is a load it guards the moved block with the loop test. The widened `unsigned short` count is moved
    the same way, which is why no count local may be declared: `i < count` on the parameter.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x322a70, 0x31d640).

- **An early return of a variable holding zero gets its own return block.** `list = 0; if (inProgress) return
  list;` is propagated to `return 0` and compiled as `b; move v0,zero` in the middle of the function; retail's
  test branches straight to the shared `move v0,s1` in front of the epilogue, which is the body enclosed in
  `if (!inProgress) { ... }` with one `return list;` after it. *Unit:* `src/engine/core/CoreLibrary.cpp`
  (0x2fe9c0).
- **An empty `if` is gone before register allocation.** A stripped assert spelled `if (c) {}` leaves nothing:
  `IRO_RemoveRedundantJumps`, the first optimizer phase, deletes the test, and `if (p->a) {}` after two calls
  gives the same bytes as `(void)0`, where a kept test would have needed `p` after both calls. On GameCube 1.2.5
  the dead compare is said to be deleted only after colouring; on b52 an empty `if` cannot explain a register
  difference.
  *Probe:* `int F(S *p, S *q) { int x = p->a + q->b; int y = h(x, 1); int z = h(y, x); ASSERT; return z; }` with
  `ASSERT` as `(void)0`, `if (x > 3) {}`, `if (p->a) {}`, `if (x != z) {}`, `if (x > 3) {} else {}` and a `?:` of
  two `(void)0`: one listing for all six.
- **A loop with an invariant assignment from a `const T &` setter is not rotated.**
  - *Symptom:* a clear loop keeps its entry in front of the body: an out-of-line `0 < count` block and a jump to the
    loop test, where a plain loop is rotated. The unit's restore loops, which pass a variable, are rotated.
  - *Cause (read from the compiler):* `IRO_RotateLoop` (0x538cd0) rotates a loop only when the block before its test
    ends in a goto and sits directly before the body. An invariant assignment in the loop is moved by
    `IRO_PullOutInvariantAssignments` into a new preheader block appended at the end of the function, and rotation is
    then refused. The assignment is the temporary made by binding the literal `0` to a `const` reference parameter.
  - *Spelling:* a setter taking the stored value by `const` reference, `setItem(ItemList *, int, Item *const &)`,
    called with `0`; called with a variable it leaves the loop rotated. Confirmed in a probe and in the IR dump.
  - *Unit:* `src/game/beNDMWListCtrl.cpp` (0x412600).
- **Only loop phases create IR nodes: an invariant pull's preheader plus the unrolled body give a block after the
  return path.**
  - *Symptom:* a vector offset helper (`point + by`) whose three adds sit in a block placed after the function's
    return path, with folded stack offsets (`208(sp)`, `224(sp)`) and the vector kept in memory.
  - *Cause (IR dump):* no `if`/`else`, `?:` or by-value return makes an end-of-function node (a `?:` on a struct is
    lowered to a pointer select, and the branches of an `if`/`else` expand to member-wise copies that are never single
    assignments). Only the loop phases add nodes: `IRO_PullOutInvariantAssignments` appends the preheader after the
    function's last node, and `IRO_LoopUnroller` places its copy of the body after that. The inner loop needs one
    assignment that is pulled out; expression propagation leaves `origin = data->_pos` alone because it is used several
    times and is not a plain address.
  - *Spelling:* a one-pass loop, `for (int i = 0; i < 1; i++) { ... }`, with the invariant local declared inside it. A
    known trip count of at least one leaves no guard. The loop is unrolled rather than removed, which matters for the
    next entry. The nearest natural reading is an inlined "offset `count` points" helper called with 1 (three words
    off); the one-pass loop carries a matching-construct comment.
  - *Unit:* `src/game/beGenerater.cpp` (`beGenerater_SpawnEnemies` 0x384540).
- **A removed empty loop leaves an orphan node that breaks the dominators.** When the pulled loop is removed instead of
  unrolled, its node stays behind with no predecessors; the dominator computation then fails and the enclosing loop is
  never processed, so the addresses the spawn loop would have lifted stay in the body. Keeping the pull loop alive
  (unrolled) is what leaves no orphan. *Unit:* `src/game/beGenerater.cpp` (`beGenerater_SpawnEnemies` 0x384540).
- **A const-reference read is never merged with non-const lifted addresses; an `sp`-based pointer variable is never
  folded into a load or store offset.**
  - *Symptom:* `lwc1` and `swc1` offsets that retail folds against `sp` (`224(sp)`) come out as `addiu v1,sp,224` with
    `0(v1)`.
  - *Cause:* in `IRO_MoveInvariantExpressions` the indexed stores `(&position)[i]` and the read through `(&relative)[i]`
    depend on `i`, so they are not lifted in pass 1; in pass 2 the read is flagged const (node flags `0x0001`, seen
    under gdb) and is not merged with the lifted `position + 4`. The code generator folds base plus offset only for
    registers, never for an `sp` address, so any spelling through a pointer variable stays unfolded.
  - *Spelling:* indexed access to the vectors themselves (no pointer variable, no `const` reference alias).
  - *Unit:* `src/game/beGenerater.cpp` (`beGenerater_SpawnEnemies` 0x384540).
- **The evaluation order of a commutative add decides its register colours.** The heavier operand is loaded first, which
  fixes which float register pair holds each term: `data->_pos[0] + relative[0]` gives retail's `f3`/`f2` and
  `add.s f2,f2,f3`, where reading `origin[0]` gives every other byte right and one register pair swapped. *Spelling:*
  the term read straight from the data first. *Unit:* `src/game/beGenerater.cpp` (`beGenerater_SpawnEnemies` 0x384540).
- **A `?:` that selects a default has no join label.** Rebuilt into a conditional expression it emits no label
  statement, so no alignment directive is written at the join; as an `if`/`else` the extra `nop` and ordering differ.
  *Unit:* `src/game/beGenerater.cpp` (`beGenerater_SpawnEnemies` 0x384540).
- **The code generator opens a new block in front of a loop whenever the block before it falls straight into the
  header.** The routine is at 0x4c5ad0 (calling 0x4ae730), found under gdb. Every loop of a function then has a
  block of its own to receive the values the code generator hoists, and retail's order of those preheaders follows
  from the split; no source construct is needed or available to ask for it. *Unit:* `src/game/beMatCtrl.cpp`
  (0x38b1f0).
- **An `if`/`else` is rebuilt into a `?:` only when each branch is a single assignment.**
  - *Symptom:* a join block that starts with a load where retail's starts with a different instruction (see the label
    entry under scheduling): retail's `if`/`else` has no label at the join.
  - *Cause:* the optimizer rebuilds an `if`/`else` into a conditional expression when each branch is one assignment,
    and the code it generates for it has no label statement. A branch that is a call plus an assignment is never
    rebuilt.
  - *Spelling:* the callee returns the vector by value (`Vec3 rotation = count == 2 ? GetVec3(msg, 1) : zero;`), so
    the call and its temporary are one expression; with an out-parameter the then-branch is a call and an
    assignment. The unit's vector class needs a copy constructor so the result is built in place.
  - *Unit:* `src/game/beModelCtrl.cpp` (0x396340).

### Types and values

- **An unsigned `-4` is one value for the header lookup and the rounding mask.**
  - *Symptom:* `li s0,-4` in each of three arms that find a block's header (`addiu s1,s4,-4` beside it uses the
    immediate), and the rounding after the join is `and a0,v0,s0`; in a sibling the value is stored to a
    stack slot in each arm. With `p - 4` the mask is loaded where it is used.
  - *Cause:* `p - sizeof(int)` subtracts an unsigned constant, which the optimizer keeps as the same typed
    value as the `~3` of `(size + 3) & ~3` on an unsigned size. Where every path to the rounding has looked a
    header up, common subexpression elimination gives the value one temporary, assigned in each arm; three
    assignments reach the join, so it is not propagated back as a constant. On the free path one arm skips
    the lookup and nothing is shared.
  - *Spelling:* the header lookup subtracts `sizeof(int)`.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x3236a0, 0x31f480).
- **An `unsigned short` held in a local is masked again where it is widened.** `lhu v0,0(s1); beqz v0,L; nop;
  andi v0,v0,0xffff; subu s1,s1,v0` is `unsigned short offset = record->offset; if (offset) first = (GangRecord
  *)((char *)record - offset);`. Tested as `offset != 0`, or read from the field both times, the `andi` is gone.
  A truth test of an `unsigned short` parameter reads the register unmasked (`beqz s2`), a comparison masks it
  first (`andi v0,s2,0xffff; beqz v0`). *Unit:* `src/engine/core/CoreLibrary.cpp` (0x3236a0).

- **Byte-returning callees make `& 0xFF` natural.** b52 emits `andi v,v0,0xff` after a call only when the result
  of a byte-returning function is compared (`f() == 0`, `== 1`) or widened (`int x = f();`), never for a truth test
  (`if (f())`, `!f()`, an `&&` operand), a byte store (`sb v0`) or a return of the same type. Each retail
  `andi 0xff` before a branch is the compare of a function declared `unsigned char` or `bool`; an explicit mask is
  not the source, and an `int` declaration of a byte function drops it. Moving a declaration from `int` to the
  narrow type moves its call sites with it: `f(a) != 0` becomes `f(a)`, `f(a) == 0` becomes `!f(a)`,
  `(f(a) & 0xFF) == 1` becomes `f(a) == 1`; a call left as `f(a) != 0` against the narrow type is 8 bytes long.
  *Units:* `src/game/beNDMWLoadCtrl2.cpp`, `src/game/beNDMWWindow.cpp` and the other callers of
  `beMessenger_GetBool` (0x38f220).
- **A `bool` compared `== false` keeps the `andi 0xff`.** `andi v,v,0xff` ahead of the branch on a flag held in a
  `bool` or `unsigned char`: `if (flag == false)` has it, `if (!flag)` branches on the register. The GameCube build
  also normalises the flag (`clrlwi.`). The comparison with `0` of a getter that returns `unsigned char` keeps it as
  well. The compiler pass was not traced. *Units:* `src/game/beChangePosTransform.cpp` (0x37aae0),
  `src/game/beNDMWShopCtrl00.cpp` (0x438160), `src/game/beNDMWSaveCtrl.cpp` (0x407120),
  `src/game/beNDMWLogo.cpp` (0x449030).
- **A `char` flag compared `!= 0` is sign-extended again at the test.** `dsll32 a0,t7,24; dsra32 a0,a0,24; beqz a0`
  where retail branches on the flag's own register (`beqz t7`), which the assignment already sign-extended:
  `char fastSpotLight = (flags >> 24) & 1;` tested as `if (fastSpotLight && ...)` gives retail's bytes, and
  `fastSpotLight != 0` adds the pair. *Unit:* `src/engine/psx2Lighting.c` (0x1f8b50).
- **A loop index under an `int`-to-`unsigned` conversion keeps its `mult`.** Retail multiplies `i * stride` on every
  pass of a vertex-array loop: the stride field is `unsigned int` and the local that holds it takes that type, so the
  index is converted (`(cast)i * stride` in the IR dump) and `IRO_DoStrengthReduction` leaves the multiplication. An
  `int` stride local and an `unsigned` index are both strength-reduced; reading the field directly reloads it on every
  pass. *Unit:* `src/game/beWaterPlain.cpp` (0x3a1290).
- **`const bool &`, `const int &` and `const float &` literal temporaries become data.** A literal passed by
  `const &` to an inline becomes an anonymous `@N` object per call: a one-byte `.sdata` constant for a `bool`, a
  four-byte `.data` word for an `int` (a probe under `-O4,p -sdatathreshold 2` puts one `.data` section per call;
  the words sit 8 bytes apart in retail), and a four-byte float loaded with `lwc1` for a `float`. Retail data that
  looks like a named flag table can be these: the five zero words of a save utility's slot lists were once a named
  empty slot. Separate `.data` words that each hold `0.5f` are literals bound to a `const float &` parameter (an
  `operator*(const igVec3f &, const float &)` or a scaling helper), not a named constant. *Units:*
  `src/game/beNDMWMdlPEBase.cpp` (58 int and 34 bool constants), `src/game/beNDMWShopCtrl00.cpp`,
  `src/game/beNDMWListCtrl.cpp`, `src/game/beSaveUtil.cpp` (0x4c91f8..0x4c9218), `src/game/beMatCtrl.cpp` (zero
  words 0x4c8f70..0x4c8f80, the `true` byte 0x5549d0), `src/engine/scenegraph/SceneGraphLibrary.cpp` (the floats at
  0x48d8d8 and 0x48d8e0 read by 0x1b1fa0, 0x48da10..0x48da20 by 0x1c4140).
- **An inlined `operator+=` gives a frameless function an exception record.** Retail keeps an exception record
  for a leaf with no frame. `*vertex += shift;` through an inline
  `igVec3f &operator+=(const igVec3f &o) { x += o.x; y += o.y; z += o.z; return *this; }` keeps it and explains the
  odd register use; `x = x + o.x` in the operator, a by-value parameter or plain float adds do not. The internal
  rule is not known. *Unit:* `src/game/beFont.cpp`.
- **A local whose address goes to a pointer parameter gets a stack slot.** A value stored to the stack and loaded
  back for a store, with no `volatile`: `pushed = item; ... set(count, &pushed);` with
  `void set(int i, T *const *v) { _data[i] = *v; }`. A reference parameter, a by-value parameter with an internal
  `&value`, or a one-field struct are scalarised and lose the slot. The setter is `igTDataList<T>::set` in
  `include/dw4/core/igTDataList.h`. *Units:* `src/game/beNodeAnim_Traverse.cpp`,
  `src/engine/scenegraph/SceneGraphLibrary.cpp`.
- **A negated flag passed to a `bool` parameter normalises first.** `sltu v0,zero,v0; xori a1,v0,0x1` before a
  call is `!attr->_enabled` passed to a virtual taking `bool`; with an `int` parameter `!x` compiles to a different
  sequence, and only the explicit `(x != 0) ^ 1` reproduces it. *Unit:* `src/engine/scenegraph/SceneGraphLibrary.cpp`.
- **A class-scope placement `delete` makes the constructor-throws cleanup.** `new (pool) T` with a matching
  `operator delete(void *, Pool *)` in the class gives the landing pad and exception table retail has around the
  constructor call. *Unit:* `src/game/be.cpp`.
- **An aggregate initializer copy gives a struct's real size.** A local initialised from a `.data` template is
  copied whole (`lq`/`sq` loop), and the template's size in retail is the struct's size; that settled a 48-byte
  Sony struct a 36-byte header had cut short. *Unit:* `src/cri/adxps2.c`.
- **An empty smart-pointer result built through the retaining constructor keeps its reference test.**
  - *Symptom:* an early-return path stores 0 into the returned holder and loads it straight back for a
    reference-count test (`sw zero,0(s1); lw a0,0(s1); beqz a0`) that can never pass.
  - *Cause:* a by-value class result lives in the caller's memory behind the hidden result pointer. The
    retaining constructor's `retain()` reads the member it just stored through that pointer, and the read is
    not folded to the constant.
  - *Spelling:* `return igSmartPointer<igObject>(0, kRetainReference);`. The default constructor leaves the test
    out (the function is 40 bytes short). For the holder that is returned on the other path, the adopting
    constructor `list(create(...))` is the source; a default-constructed `list` assigned afterwards keeps a dead
    `sw zero` in a delay slot.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (`igPsx2Folder::vfunc_26`).
- **Soft-float `double` arithmetic is written as `double`.** A run of `litodp`, `dpmul`, `dpdiv`, `dpadd`,
  `__floatdidf`, `__fixdfdi`, `__divdi3` and `__moddi3` calls with the same integer constant loaded before several
  of them is plain arithmetic on a `double` and a `long long`: the unit has no hardware doubles, so b52 calls a
  helper for every operation, and it converts an integer constant to `double` at run time
  (`litodp(1000000000)`) instead of folding it. `(long long)(1000000000 * seconds)` and
  `(double)(ns / 1000000000) + (double)(ns % 1000000000) / 1000000000` give the calls in retail's order, with the
  right operand of the sum evaluated first. Helper calls written out by hand with `int` arguments are not the
  source. *Unit:* `src/engine/core/CoreLibrary.cpp`.
- **The stack object of a vtable getter is an instance of the class.** The frame is the 16-byte save area plus
  the class's registered instance size, rounded up to 16, so a 20-byte class gives the 48-byte frame; a local
  padded by hand to the slot's apparent 32 bytes is not needed. *Unit:* `src/engine/core/CoreLibrary.cpp`.
- **The frame holds address-taken locals in declaration order, and a class local is built where it is declared.**
  Locals whose address is passed (out-parameters of a reader) lie from the top of the frame downwards in the
  order they are declared, one-byte ones packed, whatever order they are used in, so the slots give the original
  declaration block. A local of a class with a constructor is initialised at its declaration and destroyed in
  reverse order at the end: the position of its zero store among the surrounding statements shows where the
  block stands (after the first assignments, not at the top of the function), and the order of the releases at
  the end gives the construction order. Six interned strings released by hand in an odd order were six string
  holders declared in two groups around the integers. *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2f69b0).
- **A result copied from a base-class call is assigned, not initialised.** `jal base; lw s0,108(sp)` right after
  the call, the result kept in a saved register to the end: `igResult result; result = Base::configure(info);`
  leaves the returned temporary in its slot and copies it. `igResult result = base(...)` builds the call's value
  in the local's own slot, which stays in memory and is loaded at the return (4 bytes less); returning the call
  itself becomes a jump. The callee is declared with its `igResult` return, not an output pointer and an `int`.
  *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2f0880 and the five pools' configure functions).
- **Status results that take their slots in call order come from callees that return `igResult`.** The frame
  holds one 4-byte slot per call, assigned downwards in the order of the calls (a semaphore `wait`, the RPC call,
  the `signal`s on each return path), and a test of a result reloads it through its address
  (`addiu a0,sp,60; lw a0,0(a0)`). That is a by-value `igResult` return used in place. Declaring the callee with an
  output pointer and passing `&local.v` gives named locals, which take the top slots in declaration order ahead
  of every temporary, and a test reads the slot directly. The RPC connection's `Bind`, `Call` and
  `CallWithData` and `igPsx2_LoadIopModule(Ex)` return `igResult`; their bodies end in `return g_resultFailure;`
  and `return *result;`, which compile as the stores through the hidden pointer did. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (igPsx2Media resetFields, Write, Seek, Tell).
- **An argument cast to `int` for a variadic callee lets a loop hoist it.** In a loop calling
  `igStringObj_Format(path, "%s/%s", ...)`, retail rebuilds the format's address before every call; passed as
  `(int)DAT_004f9a78` to a callee declared `(int, int, ...)` the address moves into a saved register before the
  loop (one more `sq`, 12 bytes longer). With the callee declared `(igStringObj *, const char *, ...)` and the
  arguments passed as pointers, the address stays at the call. *Unit:* `src/engine/core/CoreLibrary.cpp`
  (`igPsx2Folder_ListFiles`, `igPsx2Folder_ListDirectories`).
- **A pointer argument cast to `int` takes a new allocator id.** `igStringObj_Trim` kept `self` in `s1` and the
  duplicated text in `s0`; with `igObject_DuplicateString(int self, int string)` called as `((int)self, ...)` the
  two swapped, whatever the declaration order or loop spelling. Declared `char *(void *self, const char *string)`
  and called with `self` itself, retail's registers follow. *Unit:* `src/engine/core/CoreLibrary.cpp` (0x30bee0).
- **A member release with a null test of the member's address is an explicit destructor call.** A class's
  hand-written destructor releases each reference field behind `addiu v0,s1,68; beqz v0; lw a0,68(s1)`. It is
  `((igSmartPointer<igObject> *)&p->_field)->~igSmartPointer();` (and `~igStringRef()` for a string field): the
  expanded destructor keeps its test of `this`. A helper spelling the test (`T **self = &field; if (self)`) is
  not the source. *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2c3b00).
- **A list's inserted pointer word is a class member.** `sw v0,104(sp); lw v1,104(sp); beqz v1` before the
  reference increment and `List_InsertWords(list, index, 1, &word)`: the word is the member of a one-word
  class with a retaining constructor (`RetainedWord<T>`), read back after the constructor's store. A pointer
  local or parameter whose address is passed is tested from the register and stored in the branch's delay slot
  (712 bytes against 716). A word built inside an inline helper is allocated after the caller's earlier inline
  parameters; where retail has it first, the word is declared in the function. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x2d87b0, 0x2e5110, 0x2fe600).
- **A class result read through a member function is read through its address.** After the `jalr`,
  `addiu v1,sp,332` and later `lw v1,0(v1)`: `tracker->vfunc_27(offset, &record).get()` on an `igResult`
  returned by value. Reading the member (`.v`) loads the slot directly (460 bytes against 464), and an `int`
  return has no result slot (452). A
  second result struct with its own accessor is not needed. *Unit:* `src/engine/core/CoreLibrary.cpp`
  (`igEventTracker::vfunc_33`).
- **An interned-string holder interns in its constructor.** A null test of the characters, the string pool
  created on first use, the intern call and a store to a stack slot, later released, is `igStringRef name(chars);`.
  The same sequence without the null test, followed by the release of the old token, is the assignment
  `name = chars;`. Holders with an adopting constructor fed by hand-written intern code were the same class.
  *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2da1c0, 0x2d1c40, 0x305d30, 0x2fca80, 0x32c240).
- **String literals are read-only, and a `strcpy` from one is a fixed-size copy.**
  - *Symptom:* a two-byte string (`"\n"`) is copied with `lui; addiu; lh 0(v0); sh 0(v1)` from `.rodata`, and a
    `strcat` in the same function points at the same object. Under the unit's flags a two-byte literal is small
    data (`-sdatathreshold 2` counts size 2), reached through `gp`, and `strcpy` stays a call; a `static const`
    array is copied byte by byte.
  - *Cause:* the original build made string constants read-only (`-str readonly`). A read-only literal goes to
    `.rodata` whatever its size, and because its bytes cannot change the compiler expands `strcpy(buffer, "\n")`
    into a copy of the literal's known size; the variadic `int strcpy(...)` declaration is expanded the same way.
    Every two-byte string of the library sits in `.rodata` in retail, which is why the unit could only name them
    through extern arrays.
  - *Spelling:* the literals written in the function, between `#pragma push`, `#pragma readonly_strings on` and
    `#pragma pop`: the pragma is the source form of the flag and leaves the unit's row alone. Each literal the
    function then emits is an `anon` row at its retail address. Equal literals are one object across the
    functions written this way: a later function's `"%s"` is the first one's, so the retail addresses a
    function reads show which earlier function's literals it shares.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2d45d0, 0x2e0200).
- **A size parameter's conversion leaves the loop's entry jump at the end of the function.**
  - *Symptom:* the code before a `while` loop jumps to a two-instruction block placed after the function's last
    statement, which jumps on to the loop's test (`b L; ... L: b test+4; <copy of the test's first instruction>`),
    and the final `return` branches over that block: 12 bytes more than the same loop entered directly.
  - *Cause:* the loop body passes an `int` to a callee whose parameter is unsigned (`strncat`'s `size_t`). The
    conversion is a loop-invariant expression, so the optimizer creates a preheader for the loop, and it appends
    new blocks at the end of the function. The moved value is a copy of the variable's register and vanishes in
    the code generator; the block stays. An empty preheader (nothing moved) is removed by jump chaining, so a
    callee declared with an `int` size has no such block.
  - *Spelling:* the callee's real prototype, `char *strncat(char *, const char *, unsigned int)`, the argument
    passed plain.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2d45d0).
- **A predicate that returns a byte is normalised before the branch.** `and v0,v0,v1; sltu v0,zero,v0; beqz v0`
  on a flag test: the test is an inline returning `unsigned char` whose body compares (`return (flags & mask)
  != 0;`). A `bool` return, or the mask test written in the `if`, folds to the plain branch. The object goes in by
  `const` reference: a pointer to `const` makes the field's address a value of its own (`addiu v0,s4,20`).
  *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2dd1c0).
- **A range test spelled as an unsigned difference keeps it.** `addiu t4,c,-99; sltiu at,t4,5; bnez at` inside a
  chain of `beq` tests is `(unsigned)(c - 'c') > 4` (with `<=` for the other sense). `c >= 'c' && c <= 'g'` gives two
  `slti` tests, a run of `c != 'c' && c != 'd' && ...` gives one `beq` each and is not merged, and a `switch` gives
  one `beq` per label in reverse source order (entry above), so a range test inside a chain in retail's own order
  (`u x i s S c-g C ] n-p`) is a flat `&&` chain. The spelling was found by a variant test. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x2ec980, 0x32b8d0).
- **A large buffer that receives a literal's own size is a `strcpy` under read-only strings.** A 256-byte frame
  slot filled by a 15-byte copy (`ld`, `lwc1`/`swc1`, `lh`, `lbu` from the literal) and then passed to `strcat` is
  `char name[256]; strcpy(name, "igMetaObject: ");` with the literal read-only (the readonly-strings entry above).
  `char name[] = "igMetaObject: ";` copies the same 15 bytes into a 15-byte slot (the frame 256 bytes short), a
  larger array with the initialiser copies a template of the array's full size (`lq` loop), `memcpy` stays a call,
  and an array declared and never used takes no frame space. *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2fe9c0).

- **A bit test returning `int` from `!= 0` is materialised before the branch.** Retail's `andi; sltu; bnez` comes
  from `static inline int hasValidity(...) { return (meta._validity & bit) != 0; }` tested as `if
  (!hasValidity(...))`; the same helper returning `bool` folds into `andi; bnez`, and `== true` compares with
  `1` (`bne v0,v1`). *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2fe9c0).
- **`sltu; xori; xori; andi 0xff` is an `int`-to-`bool` conversion compiled with the peephole pass off.**
  - *Symptom:* two functions (0x32ef20, 0x32f060) turn bit 0 of the COP0 status into a `bool` with that
    sequence; no other function in the executable has two `xori 1` on one register. The same two functions copy
    their receiver to a saved register and read `_semaID` through that copy (`move s1,a1` … `lw a0,12(s1)`)
    where every other function keeps reading through the incoming `a1`.
  - *Cause:* the code generator writes a conversion to `bool` as `x != 0` and two logical nots (`sne; xori 1;
    xori 1`, fresh temporaries each), and a store into a `bool` as `andi 0xff`. The block peephole pass then
    removes them. Its `xori` handler (0x512df0) turns the second `xori` into a copy of the first one's source
    when the value it reads was produced in the same block by an `xori` with the same immediate, that source
    is not written again in between (0x4bdf10), and the first `xori` does not write its own source
    (0x511f20); the first then dies, and the `andi 0xff` of a value known to be 0 or 1 becomes a copy as
    well. The same pass propagates copies (0x512050), which is what replaces a copied parameter by its
    argument register. Two things skip the pass, and all three effects then appear together (both `xori`, the
    `andi 0xff`, and the unpropagated copy of the receiver): an `__asm__ volatile(...)` statement, for the
    block that holds it (a plain `__asm__`, an `asm { }` block and an `asm` function do not stop the pass), and
    `#pragma peephole off` in force at the function's definition (it has to cover the function the conversion
    is expanded into; around an inline helper alone it does nothing).
  - *What does not give it:*
    - Plain C under the unit's profile: each `!` on a variable starts with its own `sltu`, a nested `!!` is one
      tree of fresh temporaries, and the pass folds it (some 60,000 generated spellings over three attempts).
    - An `asm` function: b52 never expands one (`static inline asm`, `inline asm`, `asm inline`,
      `#pragma always_inline on`, with or without the `jr ra`); the caller gets a `jal`.
    - The instructions written in an `asm { }` block on a local: a pair in one block survives (the first
      writes its own source), but an `asm` instruction that names a hard register is a barrier for the
      scheduler, `sltu x,zero,x` names `zero`, and the `lw a0,12(s1)` of the next statement then comes after
      the `sltu` where retail has it after the `and`. Retail's order is that of a three-instruction block
      followed by compiled code.
  - *The status read names `a1`:* with the read's register left to the compiler (the `"=r"` operand of the
    statement in `src/engine/dmaChannel.c`, or an `asm { }` block on a local) it is `v1`, with the mask in
    `a1`; retail has both in `a1`. `mfc0 $5, $12; srl $6, $5, 16; and $5, $5, $6; move %0, $5` gives it, and
    the `move` is coalesced away. The statement needs no clobber list.
  - *The receiver's two registers:* with the pass off a `const` copy of the parameter keeps its own register:
    `const igPsx2Semaphore *semaphore = self;` declared first, the first read through `self` (`lw s0,12(a1)`)
    and the later ones through the copy.
  - *Spelling:* the read as one `__asm__ volatile("mfc0 $5, $12\n\tsrl $6, $5, 16\n\tand $5, $5, $6\n\tmove
    %0, $5" : "=r"(status))` in an inline helper, and `bool interruptsEnabled = interruptEnableStatus() & 1;`
    in the function. Without the keyword the conversion folds to one `sltu`.
  - *The equivalent spelling:* the three instructions in an `asm { }` block (`mfc0 a1,$12; srl a2,a1,16; and
    a1,a1,a2; move status,a1`) with the function inside `#pragma push` / `#pragma peephole off` /
    `#pragma pop` gives the same bytes for both functions, and retail does not say which the original had.
    With the pass off for whole functions, the two before the pair (0x32ede0, 0x32eea0) differ and the ones
    after it, up to 0x32f380, are the same either way.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x32ef20, 0x32f060).
- **`daddiu` builds a constant whose type is a narrow unsigned one (probed).** `x = 7; if (c) x = 5;` with `x`
  an `unsigned char`, `unsigned short` or `bool` gives `daddiu v0,zero,7` and `daddiu v0,zero,5`, whether `x` is
  then returned, stored to a field of its type or passed on; so does a constant stored into a bit-field (signed or
  unsigned, the value already shifted into place). `signed char`, plain `char` (signed under MWCC), `short`,
  `int`, `unsigned` and `long` give `addiu`. A constant returned directly, stored through a pointer, passed as an
  argument, or assigned to the variable in both arms of an `if`/`else` is `addiu` whatever the type.
  *Probe:* `T W(int c) { T x = 7; if (c) x = 5; return x; }` and `void P(S *t, int c) { T x = 7; if (c) x = 5;
  t->f = x; }` for each type `T`, `struct B { unsigned u3 : 3; int s3 : 3; }` with `b->u3 = 5; b->s3 = 2;`.
- **Pooled literals are shared across the file.** A float constant that needs memory (`0.3f`, `0.7f`, loaded
  `lwc1 $f1,0(gp)` from `.lit4`) and a string literal are emitted once per file: a later function that uses the
  same value references the earlier function's literal. Compiled alone, the later function gets its own. Constants
  that fit `lui` (`3.5f`, `1.25f`) are built in place and are not shared. So a function's literal references
  depend on the functions before it, and the whole-file unit decides; a one-function `check.py --function`
  candidate can disagree with it there. *Probe:* `float fb(float x) { return x * 0.7f + 0.1f + 0.3f * x; }` and
  `const char *sc(void) { return "beta"; }`, with and without
  `float fa(float x) { return x * 0.3f + 0.7f; } const char *sa(void) { return "beta"; }` before them.
- **Open: a parameter that colours as an optimiser temporary.** `igDriverDatabase_SetSubPropertyValue`
  (0x2d9740): the draft is 361 instructions against 362, and every remaining difference is a register except one
  `nop`. The frame (160 bytes, six holder slots) matches with the two list holders and four string references
  declared in that order, and each new list is stored into its table slot in the order of the `setRetained`
  inline (retain, release the old element, then the bounds-checked store); with those the draft is 1444 bytes
  against 1448. Retail keeps the name in `s4`, the value in `s3` and the property in `s1`; the draft has property,
  name, value in `s4`, `s3`, `s2`. The allocator replay's graph-edit search finds no single edit that gives
  retail's colours; every two-edit solution gives `index` an id after the smart-pointer members are broken out
  into temporaries (between the `names` member's node and `index*4`), then swaps the second store's list and the
  `values` member. So retail holds `index` in a value the optimiser creates, not in the parameter's own web. A copy
  of the parameter cannot do it: b52's coalescer merges every non-interfering copy into the lower id. Tried
  without change: a one-member struct, a struct with a constructor, `index = index + 0`, a copy inside the `if`
  block; a volatile copy is worse.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2d9740, not matched).
- **Open: the topological sort's code, not its colouring.** `igDependencyOrderedList_TopologicalSort` (0x2d7280):
  the draft is 260 words against 259, with 46 register-only and 4 other differences. Retail builds each of the two
  list holders from its `igPointerList_Create` call where it is declared (no zero store at entry); with that the
  frame matches exactly. Neither single nor paired graph edits reach retail's colours (best 70 of 87 constrained
  nodes), so the register differences follow from a code difference; the call-sequence census finds no close
  donor (best ratio 0.38).
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2d7280, not matched).
- **Open: a lone zero-extension of the parameter used as the object.** `igPsx2Thread_ThreadEntry` (0x32f7f0)
  begins `dsll32 s0,a0,0; dsrl32 s0,s0,0` and then uses `s0` as the thread (`lw v0,40(s0); jalr v0; lw a0,28(s0)`,
  `sw v0,52(s0)`, `move a1,s0` into `igPsx2ThreadManager_FinishThread`). It is the only function in the executable
  that uses a zero-extended register as a base. What b52 does with the spellings tried:
  - A pointer or `unsigned` parameter used as the object gives `move s0,a0`.
  - Widening a 32-bit `unsigned` (or a pointer) to 64-bit `unsigned long` (`long` is 64-bit under MWCC) gives
    `dsll32/dsrl32`, and every conversion of a 64-bit value back to a pointer or to `unsigned int` adds
    `dsll32/dsra32`: `(T *)(unsigned long)arg`, an `unsigned long` local or parameter, an inline taking
    `unsigned long`, `(T *)((char *)0 + v)`, `(T *)(v & 0xFFFFFFFF)`, 64-bit address arithmetic, in C and C++.
  - A union or `*(T **)&v` reread of the widened value goes through the stack (`sd`; `lw`).
  - Passing the object to a callee declared with an `unsigned long` parameter puts the zero-extension on the
    argument (`dsll32 a1,s0,0; dsrl32 a1,a1,0`), with `move s0,a0` at entry.
  - A `long long` or `unsigned long long` parameter cast to the thread pointer gives retail's code except one
    word: `dsra32` where retail has `dsrl32`.
  - `#pragma peephole off` changes none of these, so no peephole removes the sign-extension after a widening;
    retail's pair is not a widening whose narrowing was cleaned up.
  - *Probe:* `struct Th { int pad[7]; int _arg; int a, b; int _function; int c, d; int _result; };` and
    `extern "C" void E(unsigned int arg) { Th *t = (Th *)(unsigned long)arg; t->_result =
    ((int (*)(int))t->_function)(t->_arg); igPsx2ThreadManager_FinishThread(g_threadManager[0], t); }`, with
    the parameter and the conversion varied as listed.
- **An enum-typed predicate parameter keeps its conversion and so its id.**
  - *Symptom:* two registers of a width/height test exchanged (`v0`/`v1`): the particle format pointer takes `v1`
    where retail has `v0`.
  - *Cause:* the inline's parameter is assigned from an `int` field with a `(cast)(cast)` conversion, which
    propagation does not fold into the `if`. It stays an inline variable with an id earlier than the common-subexpression
    temporary of the format read, so the format colours first and takes `v0`. A plain `int` parameter, the cast
    without the helper and an enum-typed view without the helper do not reproduce it; an enum view with an enum
    parameter, or an `int` field cast to the enum parameter, do.
  - *Spelling:* `static inline bool isAnimated(igGfxParticleCoord coord)` called with the field.
  - *Unit:* `src/game/ParticleArray.cpp` (0x3a3c10).
- **A 64-bit parameter or result adds `dsll32`/`dsra32` where its width changes.**
  - *Symptom:* `nor; dsll32; dsra32` before a callee returns and `dsll32 s5,v0,0; dsra32 s5,s5,0` after the call
    in its caller; or the pair with a shift of 16 at the use of a flag parameter.
  - *Cause:* b52 sign-extends wherever a parameter or a call result converts between 32 and 64 bits. In the
    callee `return ~m` narrows a `long long` work value to the `int` result; in the caller the `int` result widens
    into the `long long` it is stored to. A `short` read from a `long long` parameter (`(short)arg1`) gives the pair
    with 16.
  - *Spelling:* one prototype for both halves, `int f(long long arg)` with the work local `long long m`; a
    destructor's flag is its real `short deleteFlag`. Fixing only one of two wrong types (an `__divdi3` declared
    `int` feeding a `long long` parameter) adds 8 bytes; fixing both is neutral.
  - *Units:* `src/engine/renderState.c` (0x202fa0 and its caller), `src/engine/scenegraph/SceneGraphLibrary.cpp`
    (0x195970), `src/game/beNDMWMdlPlayer.cpp`.
- **A small vector passed by value needs a user copy constructor to be passed by pointer.** A callee taking an
  `igVec2f` by value is called with a pointer to a copy of the argument on PS2 (the Xbox build passes it on the
  stack); without a user-defined copy constructor MWCC passes the struct in a register (`ld a2`). The copy also
  decides the caller's frame slot for the local. *Unit:* `src/game/ParticleArray.cpp` (0x3a3c10).

### Scheduling (b52)

- **A value an inline reads for itself is evaluated after its arguments.**
  - *Symptom:* two expansions of one header-writing inline in one function; the one in a block that starts with
    an extra `addu` has `li a3,-1` and `move a2,s0` exchanged, two masks issued in the other order and one
    temporary in another register (5 instructions), and no declaration order or spelling of the surrounding
    statements moves it.
  - *Cause:* the candidate passed the pool index as an argument, so its load was written ahead of the copies
    of the other arguments (arguments are evaluated from the last to the first). The first scheduling pass
    issues in list order, two a cycle; with the load first and the extra `addu` at the head, the header byte's
    load fell one cycle later than the index's, its user became ready one cycle after the index's user instead
    of with it, and the two ended in the other order. The live ranges then overlapped and the allocator needed
    another register. With the index read inside the inline the copies come first and both blocks schedule as
    retail.
  - *Spelling:* the inline takes the object and reads the member itself, as a member function would.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (the arena allocator, 0x318110; traced with the scheduler
    trace).
- **A shared sum is computed where it is first used.**
  - *Symptom:* a block starts with a load in retail (`lw a0,200(s4)`) and with an `addu` in the candidate, and
    the branches into the block carry a copy of that `addu` in their delay slots where retail has `nop`.
  - *Cause:* the candidate assigned `newTop = oldTop + nb` and then used `newTop` in the next expression, so
    the `addu` and the store of the spilled `newTop` were written first. The store ahead of the load makes the
    load wait for it in the second pass, the sum's chain is then the longest, and the `addu` leads the block.
    Retail has the load first, so the sum was written inside the expression that uses it.
  - *Spelling:* `newEnd = (oldTop + nb + minimum + pageMask) & ~pageMask; newTop = oldTop + nb;`: the
    optimizer shares the sum, and its temporary is assigned where the first statement evaluates it. An
    assignment inside the expression gives the same bytes and is not needed.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x312ba0).
- **Statement order shows in a delay slot.** `beqz at,L; nop; lw a0,56(s4); li v1,1; subu v0,v0,a0;
  sw v1,196(s4)`: the size is computed first and the state flag stored after it. With the store first its
  `li` fills the branch's slot and the load follows. *Unit:* `src/engine/core/CoreLibrary.cpp` (0x312ba0).

- **An argument of integer type is evaluated ahead of the format string.**
  - *Symptom:* `lui a0; lui v0; addiu a1,s3,8; addiu a0,a0,lo` in retail and the two `addiu`s exchanged in the
    candidate, in two of three sibling reports; the third, whose address is `block + oldHeadBytes`, matches.
  - *Cause:* with the address passed as a pointer sum the argument registers are loaded in order, the format
    string first. Cast to an integer the sum is computed before the arguments are loaded, and the second
    scheduling pass, which falls back on list order between equal instructions, keeps it ahead.
  - *Spelling:* `igReportNotice(format, (unsigned)block + 8u, 0xBBBBBBBF, *tail)`: the format prints the address
    with `%x`.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x31f480).
  - *Also:* a pointer passed as `(int)obj->field` to an `int` parameter, or through an inline accessor returning
    `int`, hoists both of its loads above the computation of the arguments before it; passing the pointer itself
    to the callee's real `igRegistry *` parameter keeps retail's order. Why the conversion does this was not traced.
    *Unit:* `src/engine/core/CoreLibrary.cpp` (the callers of 0x306770).
- **Under `-O4,p` every label opens its block with an alignment directive that takes integer pipe 0.**
  - *Symptom:* a block that starts at a label begins with an integer load where retail's begins with an `lwc1`
    (two instructions exchanged, no register differences).
  - *Cause:* every IR label gets a `p2alignl` pcode, which the scheduler issues first in its block, and it occupies
    integer pipe 0. An `lwc1` needs pipe 0 and an `lw` uses the load/store unit, so an `lwc1` cannot lead a labelled
    block. Retail's `lwc1` first means its block had no label, which a rebuilt `?:` gives (see the control-flow entry).
  - *Unit:* `src/game/beModelCtrl.cpp` (0x396340).
- **Read-modify-writes of two globals show their statement order only in the registers.**
  - *Symptom:* `lw a2,dirty; ori a2,a2,1; ld a0,mask; and v1,a0,v1; sw a2,dirty; sd v1,mask; lw v1,dirty;
    and v1,v1,a1; sw v1,dirty` in retail and the same instructions in the candidate, with the mask constant, the
    `-5` and the 64-bit mask's load in other registers.
  - *Cause:* the scheduler moves the load and store of one named global past those of another, so the listing
    keeps neither statement order; the code generator numbers the temporaries in statement order, and that order
    decides the colours. With the second `p2DirtyFlags` update written last, its `-5` takes an id after the
    mask's and colours first; written ahead of the mask's update it colours after it, as in retail.
    `#pragma schedule off` shows the statement order directly.
  - *Spelling:* `p2DirtyFlags |= 1; p2DirtyFlags &= ~P2_DIRTY_LIGHTING; p2VertexArrayMask &= ~P2_NORMAL_ARRAYS;`.
  - *Unit:* `src/engine/psx2Lighting.c` (0x1f8b50).

### Scheduling (EE GCC)

- **EE GCC orders memory accesses only within one alias set; a field's or read's type decides the schedule.**
  - *Symptom:* a load issued above a store retail keeps it after, or a store ahead of one retail has first, with
    the registers of the values around it exchanged as a consequence; no statement order moves it.
  - *Cause:* two accesses are kept in order when they may alias, and the alias set comes from the lvalue's type.
    Before register allocation only same-type accesses through the same base are ordered; after it the base
    registers are set more than once, so every pair in one alias set is ordered, and an access of another type (a
    pointer read among integer stores) is outside that chain, gets low priority and is issued ahead of the first
    store. Every pointer type is a set of its own, apart from `int` and from the other pointer types: a `void *`
    store and a function-pointer load are independent.
  - *Spelling:* the field's real type. Giving a field the same pointer type as another, or reading a reply through
    its true type, changes the order of the instructions around it; an IOP buffer field typed `void *` instead of
    `int` gives retail's load and store order.
  - *Reading it:* compile the unit once with `-fno-strict-aliasing`. When the difference shrinks, the cause is a
    pair of accesses in different sets, and the types of those two lvalues are the ones to settle. The flag is a
    property of a whole unit, never a fix for one function: on every CRI unit at once it breaks about 50 of them.
    The CVFS unit keeps its SDK types (function-pointer slots, a `void *` argument block) and its row carries the
    flag ([CRI CVFS](cri-cvfs.md#argument-block-and-aliasing)).
  - *Units:* `src/sony/libpad/libpad.c`, `src/cri/sndf.c` (0x281df0), `src/cri/sfadx.c` (0x29c500, matched with the
    renderer pointer and its neighbours left untyped), `src/cri/cvfs.c`.
- **An enum field or parameter has an alias set of its own.**
  - *Symptom:* a load from a header or state struct issued above stores retail keeps it after, or stores out of
    retail's order, around a few fields that look like plain `int`s.
  - *Cause:* ee-gcc 2.96 gives an enum type its own alias set, apart from `int`. A store to an enum-typed field, or
    through an enum-typed pointer parameter, no longer conflicts with the `int` accesses around it, and the
    scheduler moves them across it. Every field involved has to be an enum (one left `int` leaves 2 to 22 words);
    one shared enum type works as well as four, `long` does not.
  - *Spelling:* the SDK's enum types: the coded-picture fields of the MPEG-2 picture attributes (`M2vFrameRate`,
    `M2vPicType`, `M2vPicStruct`), the luminance key `MwsfdLumiKey *` of the Sofdec effect getter, the user-data
    level of the MPV handle (`MpvUdLevel`, whose store otherwise holds back the header counter's increment) and
    the ring id a Sofdec transfer slot reads (`SfdBufId`, whose load retail issues past the out-parameter stores).
  - *Units:* `src/cri/m2vhdec.c` (0x285b10), `src/cri/mwsfsfx.c` (0x298880), `src/cri/mpvhdr.c` (0x28f098),
    `src/cri/sfmpv.c` (0x2a2f30).
- **A read through a union member conflicts with every store.**
  - *Symptom:* a pointer load retail keeps behind stores of every type: `int` out-parameters and pointer
    out-parameters alike, where a `void *` field is reordered past the `int` stores and an `int` field past the
    pointer ones, so no single field type fits all its readers.
  - *Cause:* ee-gcc 2.96 gives any access whose path passes through a union member alias set 0, which conflicts
    with every other set. A small test file under `-O2 -G0` shows it: a field read twice around an `int *` store
    is loaded once when the field is an enum, `short` or pointer, and twice when it is `int`, `unsigned`, `long`
    or a member of a union.
  - *Spelling:* the field as a union of the types it holds. The work handle of a Sofdec transfer slot is
    `union { void *obj; SfdMpv *mpv; } hn` (`SfdMpsPrm *prm` in the MPS slot), read as `streams.hn.mpv`. Retail's
    order then follows in three functions with no other change, and a fourth matches with its natural
    `SfdSlot **` out-parameters in place of `void **` ones. A *store* through a union conflicts the same way:
    where retail reloads `*out` before every store of a block, the destination fields sit in a union (the
    Sofdec frame information keeps its details from offset 72 in a union with the seven words the MWSFD
    player copies on unchanged), and the block's other loads stay behind each store. The fields before it
    are enums and pointers (`SfdPicType`, `SfdBufFmt`, `void *buf`, `SfdSjChunk *picUsr`), copied from the
    MPEG-2 picture attributes whose coded-picture fields are enums too (`M2vPicAtr`, one definition shared
    with the M2V decoder): a source field read once for a store and a test needs its enum type to differ
    from the destination's.
  - *Units:* `src/cri/sfmpv.c` (0x2a2f30), `src/cri/sfmps.c` (0x2a0f98).
- **An address-taken local's alias set depends on what the file compiled before it.**
  - *Symptom:* loads of address-taken locals (a local whose address went to a call, read afterwards) ordered against
    a store differently from retail with unchanged C, in a function that matches or stops matching when another
    function is added, removed or moved earlier in the file.
  - *Cause:* when a scalar local's address is taken, `gen_mem_addressof` turns its register rtx into a memory
    reference in place and sets only the low word of the alias set; the high word keeps whatever the
    garbage-collected heap held there. A zero word makes the read conflict with every store, a non-zero one with
    none. The value is fixed for a given file text, so a build is reproducible, but a change to any function
    compiled earlier can flip it. Forcing the word non-zero under gdb, with the C unchanged, makes such a function
    byte-identical to retail.
  - *Reading it:* draft the unit in address order, add each function in its place and re-run the whole unit after
    each; when a function differs only in such loads, the missing piece is an earlier function, not its own source.
    A function that matches in a small file can lose it in the full unit, and the reverse.
  - *Where the word comes from:* the register rtx is a 32-byte object of the collected heap, and the word is the
    stale +16 word of that slot's previous occupant. The heap is swept only a few times per unit (twice in
    `src/cri/sfmpv.c`), and after a sweep a function's declarations are expanded in order into the freed slots: a
    register and two or three list nodes for a plain local, a dozen or more objects for one with an initialiser. So
    the declaration order of the function itself moves each address-taken local onto a zero or a non-zero slot, and
    the main file's path string is part of the history: the same unit compiled as an absolute scratch path and as
    `src/cri/<file>.c` (what the checker and the link pass) can differ. Search with the file in place, compiled from
    the repository root; tracing `ggc_alloc` and `gen_mem_addressof` in cc1 under gdb gives each slot's stale word,
    from which a declaration order can be computed instead of searched.
  - *Unit:* `src/cri/sfmpv.c` (0x2a49b8 matched once the unit's later declarations and functions were in place, with
    its own C unchanged; 0x2a6f28 flips with the functions before it; 0x2a5c28 flips with the length of an
    identifier declared earlier in the file, so even a rename can move it: a helper's name of 15 characters or more
    there reorders its loads, one of 14 or fewer does not; in 0x2a4468
    a picture-attribute result is copied to a local, since read from the address-taken slot it reloads after
    the stores to the handle; 0x2a68e8 matched by declaring its frame pointer and the two error-count locals,
    in that order, right after the initialised pointers).
- **In a run of independent stores, the one that ends a register's life is issued first.** Before register
  allocation the scheduler breaks a tie between equally ready instructions in favour of the one that frees
  registers. Stores of one value through one pointer all become ready together, so the last statement, which holds
  the last use of the pointer and of the value, comes out first and the others follow in source order; a store
  that ends only one register's life (the second of two 64-bit fields among 32-bit ones, which has the last use of
  the 64-bit constant) comes right after it. Retail's `+28, +0, +4, ... +24` is therefore a struct reset written in
  field order, and a source transcribed in retail's order is rotated once more. MWCC emits stores in source order,
  so such a transcription matches under MWCC and reads as a function built by the other compiler. The `.sched`
  dump shows it: every store has the same priority and the one carrying the `REG_DEAD` notes heads the ready
  list. *Unit:* `src/cri/mps.c`.

### Delay slots (b52)

- **What the filler takes.** Read from the compiler (0x4c7690) and checked with the block dump. For a branch
  whose slot the instruction above cannot fill it tries, in order: the first instruction of the target, moved
  when the target has one predecessor and copied otherwise (an unconditional jump always may; a conditional
  branch only when the instruction's destination is in neither the live-in nor the live-out set of the block
  that ends with the branch); then the first instruction of the fall-through block, on the same liveness test
  and only when that block has **exactly one** predecessor. Loads, stores and calls are never taken. `v0` is
  live at the exit of every function that does not return a class, `void` ones included, so it is live from
  entry to the first call of a `void` function; a parameter still in its argument register is live-in to the
  entry block, so an instruction that reuses that register is not taken there.
- **Slots left empty across a whole function: the predecessor lists were emptied.**
  - *Symptom:* instructions and registers match, and three branches near the end of the function have a `nop`
    where the candidate fills the slot with the first instruction of the `if` body (12 bytes short). Nested
    `if`s and inline helpers change nothing.
  - *Cause:* the block pass that runs before the filler retargets a conditional branch whose target begins with
    an unconditional jump, deletes a jump to the next block and merges a block into its only predecessor. After
    any one of these it sets every block's predecessor list to empty and does not rebuild it. With no
    predecessors recorded the filler takes nothing from a fall-through block anywhere in the function; copies
    from targets still happen. The optimizer removes such jumps itself, so one reaches the block pass only when
    it appears in the code generator: a `return` that is not the function's last statement, or a block whose
    only statement is a copy the register allocator coalesces away.
  - *Spelling:* the walk of the free list is a `for` loop that reads the head again in its first clause,
    `else { for (next = self->freeHead; next < end; next += link * 4) { ... } }`, after
    `next = self->freeHead` was tested in the `if`. The second read is shared with the first, the copy into
    `next` is coalesced, and the `else` block is left holding only the jump to the loop's test, which the
    block pass retargets. With `for (; next < end; ...)` the three slots are filled. A `return;` closing the
    last `if` body gives retail's bytes too (the jump to the epilogue is deleted) and has no reason.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x30cb80).

### Delay slots (EE GCC)

- **A register whose last use fills a delay slot stays live for the filler until the next barrier.** A loop's closing
  branch carries the loop-head compare in its slot and leaves a `move a0,…` behind it, where another spelling of the
  same statements puts that move in the slot and pads the loop head. The filler asks what is live on a branch's
  other path before it takes an instruction that sets a register, and at a label with no barrier before it the
  answer is a scan from the start of the function in which a register dies only at a `REG_DEAD` note
  (`mark_target_live_regs`). An instruction moved into a slot loses those notes (`emit_delay_sequence`). So when a
  register's last use is the instruction that fills an earlier branch's slot, the register counts as live at every
  later label, an instruction that sets it cannot leave a branch's fall-through (MIPS has no annul-if-true slot),
  and the filler copies from the branch target instead, whatever the branch's predicted direction. Which register
  that is follows from the locals: in the unit below, three fields of one global read into three locals in field
  order put the global's address in `a0` and the second field in `v1`, and testing the second field straight from
  the global swaps the two.
  The compiler binary keeps its symbols, so gdb breakpoints on `fill_slots_from_thread`, `mostly_true_jump`,
  `own_thread_p` and `mark_target_live_regs` print each decision and the live set behind it. *Unit:*
  `src/cri/sfh.c`.
- **A call to a function compiled earlier in the same file fills its delay slot differently.**
  - *Symptom:* a call whose delay slot takes another instruction than retail's; the caller matches when the
    callee's body is not compiled before it.
  - *Cause:* without exceptions ee-gcc 2.96 marks every function whose body it has compiled as unable to throw
    (`TREE_NOTHROW`). Every later call to it in the same file gets a `REG_EH_REGION` note, and that note changes
    which instruction the delay-slot filler picks. A callee defined later, or in another file, is called without
    the note.
  - *Reading it:* retail's form without the note means the callee's body was not compiled before the caller; when
    both are in one unit, that places a file boundary or the function order. A call that needs the note needs the
    callee defined earlier.
  - *Units:* `src/cri/sndf.c` and `src/cri/sndfcmd.c` (0x2825e0 calling 0x281ac0 in the other file),
    `src/cri/m2vhdec.c` (0x286010, whose two callees come first).
- **`bne` with a `nop` where plain C gives `bnel`: the target starts with a `volatile` access.**
  - *Symptom:* retail `bne; nop` with a load at the branch target; every plain spelling gives `bnel` with that load
    in the annulled slot.
  - *Cause:* in `fill_eager_delay_slots`, when filling from the fall-through fails, reorg falls back to an annulled
    fill from the target, whatever the predicted direction. The slot stays empty only when the target's first
    instruction cannot move, and `resource_conflicts_p` makes a `volatile` memory reference conflict with
    everything. The same keyword stops jump2 from cross-jumping two identical stores.
  - *Spelling:* a `volatile` access, which only the owner approves ([source approvals](source-approvals.md)); six
    control-flow shapes, seven `do { } while (0)` placements and about 20 load orders do not reproduce it.
  - *Unit:* `src/cri/sftim.c` (0x2ae528, 0x2aeb60).

### Loops (EE GCC)

- **A jump around a loop's entry is a reload gcse put on the back edge.**
  - *Symptom:* a row loop entered by a jump to its own top over a block of reloads, and a `mult` left in the loop
    that strength reduction would have removed; `for`, `while` and `do`-`while` spellings of the loop all give the
    plain entry.
  - *Cause:* the source computes the row pointer before the loop and again at the top of each row. Partial
    redundancy elimination in gcse finds the base field and `cols * 2` available on entry and inserts their reload
    on the back edge; `split_edge` places that new block in front of the loop top, so the entry needs a jump around
    it. `loop.c` skips a loop whose first scanned insn is not a code label, so the row loop is not optimised and its
    `mult` stays.
  - *Spelling:* `s = plane->base + cols * 384;` both before a plain `for` row loop and at the top of its body.
  - *Unit:* `src/cri/cft.c` (0x284f30, 0x285040).
- **A second pointer stepping beside the indexed element pointer is the strength-reduced copy, not a variable.**
  - *Symptom:* a table search `for (i = 0; i < n; i++) { p = &table[i]; if (p->field == 0) break; }` whose first
    test is made on `p` straight from the table address, then `move v1,s0` after that branch, `addiu v1,v1,size`
    in the loop and `move s0,v1` before each later test, with the count kept. A source pointer stepped by hand
    (`q++`, `p = q`) gives the same loop body with the copy before the first branch, in its delay slot.
  - *Cause:* jump copies the loop's test in front of it, with `i` folded to 0. `loop.c` reduces
    `p = &table[i]` to a new register and sets it in the pre-header, behind the copied test; the second cse pass
    turns that into a copy of `p`. A variable initialised before the loop is set ahead of the copied test.
  - *The load's address:* `loop.c` also reduces the address `&p->field` to a register of its own (`lw v0,0(a0)`,
    the table base kept in a register to initialise it) when `p` has exactly one use in the loop: a giv used once
    takes no other giv in, and the address giv inherits its benefit. With no use of `p` in the loop
    (`table[i].field`, but the copied test then reads through the table base) or two (a copy to a second
    variable that the first cse pass keeps), `p`'s giv takes the address in and the load is `lw v0,4(s0)`. A
    `volatile` load keeps its address whatever the count: the pass runs with `volatile` operands unrecognised, so
    the rewritten load is rejected.
  - *Reading it:* `-dL` lists each giv with its benefit and prints `giv at N combined with giv at M`; the
    `Sorted combine statistics` line gives a giv that may not combine a 0.
  - *Unit:* `src/cri/mwsfcre.c` (0x292ba8).

### Registers (EE GCC)

- **A value set in two blocks is coloured by global allocation, never tied to its input.**
  - *Symptom:* registers only: retail puts an `and`/`addu` result in a fresh register (or one shared with another
    branch), where the plain spelling reuses the register of the operand that dies there; or two branches end in
    the same store and retail shares it (one `sw` reached by `b`) where ours repeats it.
  - *Cause:* local-alloc ties the output of an instruction to a dying input only when the output is a pseudo set
    and used in one block. A named local assigned in both arms of an `if`, or reused for a later step of the
    computation up to a store after a branch, is a global pseudo: global-alloc colours it, and when both arms then
    end in the same register, jump2 cross-jumps their identical stores.
  - *Spelling:* a local set in each arm and stored in each arm (`area = ALIGN(...); w[1] = area;`, the later reads
    still from memory: a single store after the join lets cse reuse the value), or one variable carried through
    (`fields %= 2; dst->field = fields;` in place of a second `field` local).
  - *Unit:* `src/cri/sfmpvps2.c` (0x2a97a0), `src/cri/sfmpv.c` (0x2a5a50).

- **A one-block copy across a call takes the first saved register before global allocation runs.**
  - *Symptom:* registers only: two values that live across a call sit in `s0`/`s1` the other way round (retail
    keeps the pointer parameter in `s0` and a much-used second parameter in `s1`), and an object built from SDK-exact
    C allocates like ours while the SDK object allocates like retail.
  - *Cause:* global-alloc colours by `floor_log2(refs) * refs / live length`, so the parameter with the most uses
    (a `switch` index) takes `s0` first. A pseudo used in one block is coloured earlier, by local-alloc, which gives
    a call-crossing one `s0`; the global pseudos live in that block then conflict with `s0`, and the parameter
    copied into it from `a0` gets `s0` by copy preference. A local copied from the parameter inside one arm stays a
    pseudo of its own only when cse cannot fold it into the parameter: a set of the same local in the other arm
    (dead later, and deleted) makes it the longer-lived register of the pair.
  - *Spelling:* `if (obj != 0) { ply = obj; ... use ply ... } else { ply = 0; ... }` in place of
    `ply = obj; if (ply != 0) ...`. Read the allocation order from `-dg` (`;; N regs to allocate:`) and the
    priorities from `-dl` (`Register N used R times across L insns`).
  - *Unit:* `src/cri/mwsfd.c` (0x295010).

### Delay slots (b52)

- **A deleted jump to the next block stops fall-through filling for the whole function.**
  - *Symptom:* most conditional branches keep a `nop` where another spelling fills the slot from the following
    instruction (`beq v0,a0,L; nop; li v1,2` where siblings have `beq v0,a0,L; li v1,2`). Copies from a branch target
    still fill slots, and the copied original stays in place as dead code (`bnez s4,L+4; slti at,…` with the same
    `slti` still at `L`). Every slot in the function changes together, whether the cause comes before or after it in
    the source. Small test files reproduce it.
  - *Cause:* when the code generator deletes an unconditional jump whose target is the next block, the scheduler stops
    filling slots from the fall-through for the whole function. The front end has already removed its own redundant
    jumps, so only jumps made later count. Three constructs produce one:
    - a `return;` closing the last `if` block of a function that returns `void`, or `igResult`, which comes back
      through a hidden pointer (`if (bad) { report(); return; }` as the final statement);
    - a conditional expression whose condition ends in a logical not as the last operand of `&&` or `||`
      (`f(x == -1 && !p ? a : b)`; the same condition in an `if` does not count, and neither does `p == 0`);
    - a `switch` with `default:` written before its cases.
  - *Reading it:* when retail has the `nop` slots, look for which of these the function used. One that also changes
    the branch it sits in (`!p` turns `beqz p,T; b F` into `bnez p,F`) is the wrong one. An `int` or pointer return
    has no `return;` form; there the trigger has to be one of the other two.
  - *Unit:* `src/engine/core/CoreLibrary.cpp`: the arena pool's block walks (0x311d10, a trailing `return;` after the
    bad-chunk report) and the arena block check (0x312790, `igResult`).
- **A copy the allocator coalesces away leaves a jump the block pass retargets.**
  - *Symptom:* a function has the unfilled slots of the entry above and none of its three constructs; its
    instructions match with every obvious spelling and only the slots differ (15 `nop`s in a 324-instruction
    function).
  - *Cause:* the block pass has three rules, read from the compiler (0x4c6b80) and reported per block by the
    block dump: it retargets a conditional branch whose target block begins with an unconditional jump, it
    deletes a jump to the next block, and it merges a block that ends with a jump or the return into its only
    predecessor when that predecessor falls into it. Any of them empties the predecessor lists. The first one
    fires when the last statement of an `if` body is a copy between two variables that the register allocator
    gives one register: `if (pages != 0) { …; if (self->updateStatistics) { …call… } result = pages; } else { …;
    result = 0; }`. The copy's block is then only the jump over the `else`, and the `updateStatistics` test
    branches to it. Assigning `result` straight from the calls gives the same instructions with filled slots.
  - *Evidence for the source:* the GameCube build of the same function keeps the two variables apart
    (`mr r29,r25` in front of the jump over the failure arm), and its allocator calls all write `r25`.
  - *Reading it:* when a function is in this mode and no jump-making construct fits, run the block dump on the
    candidate with a suspect spelling and look for the changed block; in the other builds look for a register
    copy that the PS2 build does not have.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x326410, 0x3236a0, 0x31f480).
- **A commutative add takes the plain variable as its first operand.** The front end orders the operands of `+` so
  that a leaf comes first. An inline call counts as complex until it is expanded, and a conditional expression is
  always complex. To get retail's `addu v1,a0,v1` with the payload in `a0`, the payload has to be a variable. When
  the value is only computed after the guards of a check, that means splitting the `&&` chain into nested `if`s and
  assigning the variable between them: `if (level > 0 && ml > 0) { size = …; if (((Chunk *)((char *)h + (size +
  header)))->used && ml > 0) … }` compiles to the same branches as the flat chain. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x30fa90).
- **A statement after an `if` that both arms reach is hoisted into the test's slot.**
  - *Symptom:* after a scan loop, `bnez t7,L; li s0,2` with the append in the fall-through, and the loop's first
    exit to that test keeps a `nop`. With the assignment written ahead of the `if` the `li` stays in front of the
    branch, the slot takes the fall-through's first instruction, and the loop exit copies the `li` from its target.
  - *Cause (not traced):* written after the `if`, the assignment is the first instruction of the join both paths
    reach, and it ends up in the test's slot; the test is then the first instruction at the loop exits' target, which
    leaves them nothing to copy. Written ahead, it stays in the test's own block and the slot takes the
    fall-through's first instruction. The two placements also number the temporaries differently.
  - *Spelling:* `if (!space) { piece[used++] = c; i++; } state = 2;`.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2ec980, 0x32b8d0).
- **An `else` that only copies keeps the join's first instruction out of the test's slot.**
  - *Symptom:* `beqz a2,L; nop; ori a3,a3,0x10; L: li v1,1` in retail, where `if (linearOnly) colorMode |= 0x10;`
    moves the `li` into the slot (`beqz a2,L; li v1,1; ori a3,a3,0x10`), the hoist of the entry above.
  - *Cause (block dump):* written `if (linearOnly) variant = colorMode | 0x10; else variant = colorMode;`, the
    `else` is a copy the allocator coalesces, and its block stays as the branch's target, empty, ahead of the join.
    The target has no instruction to give, and the fall-through's `ori` writes a register live across the
    branch, so the slot keeps its `nop`. The predecessor lists are not emptied, and the other slots are unchanged.
  - *Spelling:* the table index is its own local, assigned in both arms, as in the sibling path that selects
    `colorMode | 0x18` or `colorMode | 8`.
  - *Unit:* `src/engine/psx2Lighting.c` (0x1f8b50).

### MWCC builds compared (3.0, b38, b52)

- **Check the build before looking for a spelling of `movz` or of a slot fill.** The same probes compiled with
  `-O4,p -sdatathreshold 2` under 3.0 (011126, `default`), b38 (`combat`) and b52:
  - `movz` from a ternary whose arms are parameters or constants (`c ? a : b`, `c ? 5 : 7`, `c ? a : 0`,
    `c ? kOff : kOn` with enum constants) on all three. `int` arms `0` and `1` (`c ? 0 : 1`, `c ? 1 : 0`) give
    `movz` under 3.0 and `sltu` (with `xori` for `c ? 0 : 1`) under b38 and b52. Arms that load (`p->a`) branch on
    all three.
  - 3.0 fills slots that b38 and b52 leave empty: an `if`/`else if`/`else` of three calls followed by a store has
    the `b` to the join filled with a copy of the join's first instruction (`li v1,7`, three predecessors) under
    3.0 and a `nop` under b38 and b52; a `while (c--) { if (*p) break; p++; }` loop is two instructions shorter
    under 3.0, where b38 and b52 leave a `nop` between its load and the `bnez` that tests it and another in a slot.
  - A `for` loop summing `p[i]` keeps an index and an add under 3.0 and walks the pointer under b38 and b52.
  - b38 and b52 gave the same listing for every probe.
  - *Probe:* `int t1(int c, int a, int b) { return c ? a : b; }`, `int i1(int c) { return c ? 0 : 1; }`,
    `void u3(int *p, int c) { if (c > 3) g(1); else if (c > 1) g(2); else g(3); p[2] = 7; }`,
    `int u4(int *p, int c) { while (c--) { if (*p) break; p++; } return *p; }`.

### Declaration order and evaluation order

- **Declaration order, getters and helper argument order decide ids.**
  - A count declared before a cast list pointer (`int count; List *list = (List *)target; count = list->_count;`)
    gives the list the lower saved register; the natural order swaps them. *Unit:* `src/game/beNDMWShopCtrl00.cpp`.
  - A value an inline helper returns, and a helper's own locals, are numbered with the inline's values; using the
    getter (`work = buildData(self)`) and the setter inline together gives retail's order where hand-ordered locals
    stood before. *Unit:* `src/game/beDemoManager.cpp`.
  - An inline's arguments are evaluated before its body: `AppendRecordString(self->_messenger, db, record, key)`
    loads the messenger into a saved register before the call inside it. *Unit:* `src/game/beNDMWShopCtrl00.cpp`.
- **A parameter reached through a cast moves registers; the real class as the parameter type does not.**
  - *Symptom:* `self` and a flag parameter in exchanged saved registers (`s0`/`s1`), or a member read through a
    computed address (`lw a0,0(v1)` where retail has `lw a0,16(s1)`).
  - *Cause:* a cast local (`View *v = (View *)self;`) is a declared local with an id of its own, which changes the
    colouring order; an inline cast on each access (`((View *)self)->f16`) makes `&member` a value the
    common-subexpression pass shares with the load.
  - *Spelling:* declare the parameter with its real class and read the reflected fields through it; cast the
    loaded handle, not the object (`o = (struct Rc *)self->_parentList;`).
  - *Unit:* `src/engine/scenegraph/SceneGraphLibrary.cpp` (0x195970 and the other scene-graph destroy functions).
- **What a declaration changes at the call.** A `(...)` or K&R `()` declaration and a prototype give the same
  call when the arguments are word-sized `int`, pointer or enum values, or constants. They differ in these cases,
  so each is tested on every caller when a declaration moves to its home:
  - a `float` argument behind `(...)` (C++) or `()` (C) is promoted to `double` by a software conversion (8 to 72
    bytes more in each of five units tested);
  - a one- or two-byte parameter with a non-constant argument is narrowed by the caller, with `andi` for an
    unsigned type and `sll`/`sra` for a signed one, so only the real type reproduces retail;
  - a one- or two-byte return is masked at the callers that compare or widen it (the byte-returning entry);
  - a one- or two-byte global is small data under `-sdatathreshold 2`, reached through `gp`; declared as an array
    it is reached through `lui`/`addiu` (16 bytes more in one function), while larger globals are reached the same
    way as scalars or arrays;
  - a call that omits an argument: retail passed whatever was already in the register, and the real call names
    that variable;
  - a typed prototype can change the order in which a caller loads its arguments even with word-sized
    parameters: giving one image function of the Gfx library a prototype reordered the argument loads of two
    matched callers.
  - *Units:* `src/engine/igViewerRenderer.cpp`, `src/engine/p2viewport.c`, `src/game/ParticleArray.cpp` (floats),
    `src/game/beActionStarter.cpp` (a byte parameter), `src/game/GameMain.cpp` (a byte global),
    `src/engine/gfx/GfxLibrary.cpp` (0x157990 and 0x1566c0 calling 0x159320).
- **A `const` reference parameter takes its temporary where retail built it.** A callee taking `const igVec3f &`
  called with `igVec3f(0, 0, -1.2f)` builds the temporary in retail's frame slot; a named local declared for the
  call takes another one. A reference is a pointer in the ABI, so the callee's own bytes do not change. *Unit:*
  `src/movie/igMovieManager.cpp` (the caller of 0x1909b0).
- **A value read once into a local lets a later local colour in its declared order.**
  - *Symptom:* float registers shifted by one: a square root takes `f10` where retail has `f13`, and the three
    direction components it scales take `f13`..`f11` where retail has `f12`..`f10`. Declaring the root first gives
    it `f0` and shifts every other float.
  - *Cause:* the root needs the lowest id of the group, and declared first it has it, but it interferes with 32
    float values, so simplify passes over it and pushes it last ([the tracer](#the-register-allocator-tracer)): it
    colours first and takes `f0`. In retail the other sphere's radius is a declared local ahead of it, live across
    the root; pushed first, it brings the root's degree to 31, and the root is pushed in its declared order.
  - *Spelling:* `otherRadius = other->_radius`, read once for the containment tests and the far point, declared
    first; the root declared before the direction components.
  - *Unit:* `src/engine/maths/MathsLibrary.cpp` (0x18de10).
- **A value read through the same expression in every test is one temporary that colours first.**
  - *Symptom:* every long-lived value of a function one register off: the program's capability word in `t9`
    where retail has `t0`, and the bits taken from it, the loop counters and the hoisted loads each one up.
  - *Cause:* `IRO_CommonSubs` shares the repeated read of `p2ProgramFlags[p2CurrentProgram]` in a temporary whose
    id comes after every declared local, so it colours first and takes the lowest free register. Copied into a
    declared `flags` local it has the lowest id and colours last.
  - *Spelling:* each capability is read as `(p2ProgramFlags[p2CurrentProgram] >> n) & 1`, as the file's other
    functions read them, and the locals that hold the bits are declared in the order they are assigned.
  - *Unit:* `src/engine/psx2Lighting.c` (0x1f8b50).
- **A class local is numbered after every declared local, wherever it is declared.**
  - *Symptom:* instructions identical, two saved registers exchanged between a result object and a pointer local
    (`s2`/`s3`). The result declared `int` and read as `.v` matches; declared as its class it does not, and no
    declaration position of it or of the other locals changes anything.
  - *Cause:* a class local is not a register candidate. `IRO_ScalarizeClassDataMembers`, the first phase of the
    optimizer's loop, replaces its one member with a temporary (`*(result) = ...` becomes `*(@1793) = ...` in the
    dump), and the temporary takes its allocator id then: after all the function's declared locals, mid-block ones
    included, and after the parameters of the inlines already expanded (`operator==`'s `this`), but before the
    optimizer's later temporaries and before the second and later webs of a reused variable. Retail colours the
    pointer first, so the pointer has the later id. No declared pointer can have one; a later web of a variable
    the function reuses does. Traced: block-local pointer 42, result 49, result coloured first; pointer as a
    later web 62, result 48, retail's colours.
  - *Spelling:* `igResult result = g_resultSuccess;`, and the new pool kept in the function's one pool pointer,
    which the loops before and after it also use, not in a block-local of its own. With the pointer reused both
    `int` and `igResult` match, so the `int` only compensated for the block-local.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2f4a60).
- **An argument that carries an integer conversion is loaded before the plain ones.**
  - *Symptom:* a call passes two fields of one row as its third and fourth arguments and loads the fourth first,
    with the row pointer in the third's register (`lw a3,4(a2); lw a2,0(a2)`); the plain spelling loads them in
    order with the row in `a3`. A `(long long)` cast on the fourth argument gives retail's order although the
    parameter is 32-bit.
  - *Cause:* the two spellings differ in the IR by one conversion node on that argument. Any conversion to an
    integer type does it: an implicit one between `int` and `unsigned`, a byte field widened to an `int` or
    `unsigned` parameter, `(int)` written on an `int` or on a pointer. A cast to a pointer type does not (it is a
    node too, but it does not count). Of the four combinations (conversion on the third, the fourth, both,
    neither) the fourth is loaded first exactly when it carries one, and the row pointer takes the register of the
    argument loaded last. Where the base pointer is not in an argument register, two arguments that both carry a
    conversion, or neither, are loaded in order.
  - *Spelling:* the field and the parameter in their own types, which differ in sign: `unsigned size` in the row,
    `int size` in the callee, the argument passed plain. An `int` field with an `unsigned` parameter gives the same
    bytes, here and in the callee's other callers; the row's size is printed as `0x%08x` beside its addresses, so
    the field is the unsigned one.
  - *The reverse case:* retail loads a list handle before the byte flag passed after it
    (`lw a3,192(s1); lbu t0,168(s1)`), and with the flag parameter declared `unsigned int` the flag is loaded
    first, because the widening is a conversion; `(List *)(int)file->_list` then repairs the order by giving the
    list one too. The parameter has the field's type, `unsigned char endianSwap`, so neither argument carries a
    conversion. In the callees the flag is tested plain, `if (endianSwap)`: `endianSwap != 0` promotes the byte,
    and the promotion the tests share becomes an `andi` into a register of its own (4 bytes more).
  - *An enum parameter:* retail loads the source and destination factors and the `short` stage before the byte
    constant, the source into a temporary moved into `a1` in the call's delay slot (`lw v0,12(a0)` …
    `move a1,v0`); with `int` parameters the factors load after the context moves into `a0`, 4 bytes short. The
    callee takes the factors as the reflected enum (`IG_GFX_BLENDING_FUNCTION`) and the caller casts its `int`
    fields to it, as the texture attribute does for its wrap and filter modes. `(int)` written on the `int`
    field gives the plain bytes there, and the enum on the source alone leaves 2 words.
  - *Units:* `src/engine/core/CoreLibrary.cpp`; `src/engine/attrs/AttrsLibrary.cpp` (0x13c2c0 calling 0x174510).
- **An `int` copy of a parameter at the top of a function stands for something else.**
  - *A reassigned variable.* `m = m->_writeProxy ? proxy() : m` makes a second web of `m`, numbered after every
    declared local, so it colours before the count declared after it and takes its register (`s3`/`s4`
    exchanged; traced: list 35, `m` 37, count 39, second web of `m` 42). Copies of the list and flag parameters
    into `int` locals moved their ids instead. The source has two variables, each declared where it is first set:
    `meta`, `index`, `writeMeta`, `count`, `i`; of the declaration orders only those with `index` before
    `writeMeta` before `count` before `i` match.
  - *A cast at a call inside a loop.* `(int)file` on a pointer parameter passed to a callee declared with an `int`
    is a loop-invariant expression: `IRO_MoveInvariantExpressions` computes it into a temporary before the loop,
    and when that value is spilled the frame has one more 4-byte slot (192 bytes against 176). The callee takes
    the pointer type and the parameter is passed plain.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2ffe10, 0x2fff90).
- **A loop index started from a named value is declared last.**
  - *Symptom:* a walk over a list from a start count to an end count has the index and the end count in each
    other's saved register (`s0`/`s1`); the start count is loaded before the end count, so declaring the index
    first and assigning it there gives the wrong registers, and only an index declared after the count but
    assigned before it matched.
  - *Cause:* the source names the start: `int first = base->_count; int count = fields->_count;
    for (int i = first; i < count; i++)`. The copy `i = first` is propagated, `first` never reaches the allocator
    and takes no id, and `i`, declared in the `for`, is numbered after `count` (traced: list 33, count 34,
    index 35; with `int i = base->_count; int count = ...` index 34, count 35).
  - *Spelling:* as above, each local declared where it is first set. Four field walks of one class take this
    shape.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2ff930, 0x2ffa00, 0x2ffab0, 0x2ffb50).
- **A value read through an inline getter is numbered after the declared locals.**
  - *Symptom:* a function loads three fields of one global into saved registers and then makes a call; the
    registers fit no declaration order in which the locals are declared where they are assigned. A search found
    an order with the first and third of them declared after locals that are first set much later.
  - *Cause:* a local initialised from an inline function's return value takes the return temporary's id, which
    is made after all of the caller's declared locals (traced: the two values leave the declared range 33-47
    and become node 71 and a neighbour). Controls: both getters are needed; either one alone, or neither,
    differs; the second field read plainly or through a getter makes no difference.
  - *Spelling:* the two values through inline member getters of the object that holds them, the other field
    read directly, and every local declared at its first assignment, loop indices and block-locals in their
    blocks. No declaration order is left to choose.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2f69b0).
- **A typed view of a `void *` parameter is copied where it is declared.**
  - *Symptom:* `beqz system,end; nop; lbu mode; bnez mode; move s1,a0`: the parameter's copy to a saved register
    sits in the second branch's delay slot and the first slot is empty. Declared at the top of the function the
    copy fills the first slot.
  - *Cause:* the copy is an assignment and is emitted in the block that holds it; the delay-slot filler then
    moves it over the load into the next branch's slot.
  - *Spelling:* the view declared as the first statement inside the `if (system)` block, the other locals after
    it where they are first set. A separate local for the mode byte is not needed.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2ff820).
- **C-style declarations at the top keep their order; parameters need no copies.** A duplicate search over a
  record table (`i`, `j`, a found flag, the value) has the value in `s0` and the flag in `s1`, though the value is
  set first: the four are declared together at the top as `int i, j, found; T *value;` (traced ids 34-37). The
  value or the flag declared in its block exchanges two registers. Six sibling functions share the order.
  Copies of the output pointer and the remaining count into locals changed nothing: the parameters are
  stepped directly. The same class walks its records with a pointer declared before the index
  (`record++` beside `i++`) where retail keeps a stepped pointer, and indexes `records[i]` where retail
  multiplies on every pass; the unit builds for size and does not turn one into the other.
  *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2f4070, 0x2f7cc0, 0x2f7e00, 0x2f7f20).
- **A pointer an inline getter returns is numbered after the caller's block locals.**
  - *Symptom:* a configure function reads strings from its info record at the top and parses each in a block
    with a local of its own (a flags word, a level); retail gives the block local the higher saved register, the
    plain spelling gives it to the string, and the only declaration order that matches has the block locals
    declared at the top, ahead of the strings.
  - *Cause:* the string read through an inline getter that returns the pointer is the getter's result, numbered
    with the inline's values after every local the caller declares, block locals included, so it colours first.
    The getter's parameter may be `const` or not. An `int` getter with the cast at the call, an `int` local and
    a plain field read all keep the declared local's early number.
  - *Spelling:* `const char *messages = igMemoryPoolInfo_messages(info);` with
    `static inline const char *igMemoryPoolInfo_messages(const igMemoryPoolInfo *info)`, every local declared
    where it is first set, the result an `igResult` assigned from the base call.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x3223d0, 0x325940, the arena pool's).
  - *Also found:* a row pointer the loop reads (`DelayAt(self, i)` in a frozen-delay loop, which no declaration order
    could fix: the `a1`/`a2` swap), a send time read through `SendTimeOf(const Delay *)` (a plain read becomes `+=` and
    flips the `daddu` operands), and a list the loop appends to (`TimeListOf(node)` in a meter update: the list lands
    in `s0` and every saved register follows). *Unit:* `src/game/beMessenger.cpp` (0x38d0a0). In the generator's
    update the work, the data and the player data go through inline helpers too, and so does the enemy record number
    inside the setter: the id-order search could not find it because the ids come from where a value is created,
    with `database` < the model-name temporaries < `recNo` < the reload of `created`, and `ready` < `work` < `data` <
    `playerData`. The example is `beGenerater_UpdateRam` (0x384c40).
- **A decoder's helpers take the cursor and the result by reference, and the results are typed scratch locals.**
  - *Symptom:* a record decoder runs a variable-length-integer loop per field. Retail keeps the read pointer in
    one saved register throughout, the flags word in the next and the slot counter between them; the value and
    the shift of a field's loop sit in `a1` and `a0`. Helpers that return the advanced pointer, or that build
    the value in a local of their own and store it at the end, give the same instructions with the saved
    registers rotated and the value and shift exchanged; no declaration order of the caller's locals changes
    anything, because each is replaced by a helper's temporary.
  - *Cause:* a helper that works on `T &out` directly (`out = 0; out |= ...`) leaves the caller's declared
    variable as the accumulator, with the id of its declaration; the helper's own locals (shift, a copy of the
    cursor) are numbered after it. Only the first web of a declared variable has that id: a scratch variable
    used for a second field is a later web and is numbered after the helper's locals, which exchanges the two
    registers. Retail's pattern (declared-variable order at the type, at the first signed field and at the
    first unsigned field after it, later-web order everywhere else) is three variables: the type, one signed
    scratch and one unsigned scratch, each field assigned from the scratch of its own signedness.
  - *The cursor copy:* each helper reads through a local copy (`const char *q = p; ... p = q;`). The copy's
    last assignment back is then an expression the optimizer puts into the next use in the same block, so
    where two fields are decoded with a call between them and no branch, the cursor's increment comes after
    the call's result is stored (`jal; lw a0,68(s4); sw v0,68(s3); addiu s0,s0,1`), not in the call's delay
    slot.
  - *Spelling:* `static inline void decodeUnsigned(const char *&p, unsigned int &out)` and
    `decodeSigned(const char *&p, int &out)`, called as `decodeSigned(p, value); record->size = value;`.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2de480).
- **A character compared in place needs no local.** A scan `while (*s && *s != '\'' && n < 255)` whose body
  tests and stores `*s` again shares one load and one sign extension; copying the character to an `int` local
  in the condition (`(c = *s) != '\''`) gives the same instructions with eight temporaries permuted. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x2d45d0).
- **Stack slots rise as allocator ids fall, and a split lifetime has a late id.**
  - *Symptom:* instructions and registers match and two or three spilled values sit in each other's 16-byte
    slots (`sw zero,208(sp)` against `sw zero,256(sp)`), or the entry block zeroes two slots in the other order.
  - *Cause:* the slots are handed out upwards from the highest id to the lowest. Ids are: declared locals in
    declaration order, then the optimizer's temporaries in the order it makes them (a shared mask or a shared
    `unsigned short` to `int` conversion among them), then the temporaries of `IRO_SplitLifetimes`. That phase
    gives a variable with several separate lifetimes (zeroed at entry and set again on the reallocation path,
    and set and used on its own on the free path) a new temporary for every lifetime but the second it finds
    in statement order; so the lifetime that starts at the entry assignment has a late id, and the one on the
    free path keeps the declared one. It handles the variables in the order the function first refers to
    them, a dead initialiser included, and makes one variable's temporaries together. The scheduler trace
    prints the ids (`D:c0r90 U:c0r0` is `r90 = 0`), and the optimizer dump after `IRO_SplitLifetimes` shows
    the temporaries by name.
  - *Spelling:* declarations in the order the slots of the unsplit variables fall (`int newBytes; int total;
    bool moved; int oldHeadBytes;` for slots 256, 240, 224, 208), and the entry assignments as statements in
    the order of the stores. One function needs `int oldHeadBytes = 0;` ahead of `oldSize = 0; oldBytes = 0;
    oldHeadBytes = 0;`: the dead initialiser only makes it the first of the three the phase handles. What the
    original's earlier reference was is not known. The GameCube build zeroes exactly the split variables with
    register copies (`li r26,0; mr r19,r26; mr r24,r26`) and the others with `li`, which shows which
    variables the original reused across the free and reallocation paths.
  - *Open:* the malloc pool's sibling (0x3236a0) shows the same three copies on GameCube, yet matches on PS2
    only with the free path's sentinel offset in a local of its own: with the variable reused there its
    entry lifetime takes a late id and its slot falls below the shared alignment's. One source for both
    functions has not been found.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x3236a0, 0x31f480).
- **Spilled locals take their stack slots from the last declared to the first.** A function with more
  long-lived locals than saved registers keeps some in 16-byte frame slots; the slots rise in the reverse of
  declaration order, so their offsets give the declaration block. Where a value returned after a scoped
  block has a slot below the block's own locals, the locals are all declared at the top of the function,
  C style, and only the scoped object is in the block. The hidden result pointer of a function that returns a
  class is kept differently when registers run out: it goes to a 4-byte slot beside the address-taken locals
  (`sw a0,360(sp)` at entry, loaded at each `return`), not to a 16-byte slot. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x2dd1c0, 0x2e63e0).
- **Fields read where they are used leave no locals to order.**
  - A reader's `gets` compares, clamps and subtracts its position and length: `if (f->pos >= f->len) return 0;`
    and `if (n + f->pos >= f->len) n = f->len - f->pos;`. The shared reads are the optimizer's temporaries,
    numbered as it makes them; `int len = f->len; int pos = f->pos;` loads the same two words into exchanged
    registers, and matched only with the locals declared in the reverse of the order they are set. *Unit:* `src/engine/core/CoreLibrary.cpp`
    (0x2ecea0, 0x32bdd0).
  - A stack pool's free space is `(unsigned)(pool->end + 1) - pool->top` straight from the fields, and the
    running `end` and `low` are declared in the branch that walks them; the padding step reads `pool->top` in
    place (`mask & (align - (pool->top & mask))`, `out[i] = pool->top + pad`). Locals for the top, declared at
    the head of the function, exchanged registers and changed the order of the size arithmetic.
  - **A reused index is numbered late.** One `unsigned i` serving every loop of a function has a web per loop,
    and each web after the first is numbered after all the declared locals, so the index takes a lower register
    than the locals of the loop it runs. An index per loop takes the higher one. Seventeen locals whose order a
    search had found reduce to the function written this way, with the count an `unsigned short` parameter used
    directly (its widened copy is the compiler's and takes the lowest register, where a declared count local
    took a higher one).
    *Unit:* `src/engine/core/CoreLibrary.cpp` (0x327d40, 0x327ed0).
  - A scanf over a format string reads `format[i]` at each use in the outer dispatch (`if (format[i] != '%')`,
    `piece[used++] = format[i]`), and only the inner conversion scan keeps the character in a local, `c`, with the
    space test through a one-line inline (`static inline int isSpace(int c) { return _ctype_[c + 1] & 8; }`). A
    character local for the outer dispatch, declared anywhere, exchanged it with the hoisted copy of the format
    pointer (`t1`/`t2`); without the inline, ten temporaries took other registers. *Unit:*
    `src/engine/core/CoreLibrary.cpp` (0x2ec980, 0x32b8d0).
- **Where a pair of locals is all that is left of an order.**
  - `for (int i = 0, count = list->count; i < count; i++)` numbers the index before the count, which a count
    declared in front of the loop does not; an `int` getter for the count changes nothing. *Unit:*
    `src/engine/core/CoreLibrary.cpp` (0x2e8c40).
  - Two values that never cross a call share the argument registers, and the later-numbered takes `a0`: a
    heap walk's next-block pointer is declared with the function's other pointers, ahead of its `ok` flag, and
    every other local sits where it is first set. *Unit:* `src/engine/core/CoreLibrary.cpp` (0x312790).
  - An index declared at the head of the function (`int i; int seen = 0; bool found = false;`) is numbered
    before the counters zeroed beside it and takes the higher temporary register. *Unit:*
    `src/engine/core/CoreLibrary.cpp` (0x306510).
- **The front end orders the operands of a commutative operator.**
  - *Symptom:* `addu v1,v1,a0` where retail has `addu v1,a0,v1`, and exchanging the operands in the source changes
    nothing.
  - *Cause:* MWCC rewrites `a + b` before the optimizer runs; the first phase of the IR dump already shows the new
    order. A plain variable goes ahead of an expression, and the shorter of two expressions first. A call of an
    inline function is an expression at that point, even one that expands to a single temporary, so
    `size(p) + (p->words + 1) * 4` becomes `(p->words + 1) * 4 + @temp`.
  - *Spelling:* give the term retail adds first a local of its own (`payload = size(p); total = payload + ...`), or
    put the whole sum in the inline, where the left term is the inline's own local.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (the arena allocator).
- **An inline's return value replaces the variable it is assigned to.**
  - *Symptom:* two saved registers exchanged, and no declaration order of the locals moves them.
  - *Cause:* in `total = sum(p)` copy propagation replaces `total` with the inline's return temporary, which takes
    its allocator id after every declared local. A local assigned an expression that only contains the inline's
    result (`total = payload + ...`) keeps the id of its declaration.
  - *Spelling:* as above; the destination then colours by where it is declared.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (the arena allocator).
- **A value read through an accessor inline is numbered with the inline's values.** A saved flag
  (`used = usedBit(p)`), a link store whose value is loaded (`setForward(p, *bin)`) and a size kept in a named local
  rather than updated in place each gave retail's temporaries where the written-out expression exchanged two of
  them. *Unit:* `src/engine/core/CoreLibrary.cpp` (the arena allocator).
- **m2c offset variables steal saved registers.** A user `offset += 4` with `data + offset` is a source variable
  coloured before the slot pointer; an index loop over `&data[i]` lets the compiler make the offset itself, with
  retail's registers. Rewrite m2c's strength-reduced loops as index loops first. *Unit:*
  `src/game/beNDMWWindowTitle.cpp`.
- **A derived view of a base-class parameter keeps the argument register.** A traversal function that takes
  `igTraversal *traversal`, works through `igCompileTraversal *self = (igCompileTraversal *)traversal;` and passes
  `traversal` on to the next traversal function keeps the incoming `a0` live for that call: the code between avoids
  `a0` and the call has no `move a0,s0`. One pointer used for both gives the move and shifts every temporary.
  *Unit:* `src/engine/scenegraph/SceneGraphLibrary.cpp`.
- **Inline virtuals are emitted in reverse declaration order.** Declare them in the reverse of retail's address
  order. *Unit:* `src/engine/lua/LuaRegistration.cpp`.
- **A later web of a reused variable colours first; a block local is its own first web.**
  - *Symptom:* instructions identical, the temporaries of one path rotated (`v1`/`a0`, then every temporary
    after them), and no order of the declarations changes it.
  - *Cause:* `IRO_SplitLifetimes` gives each separate lifetime of a variable after the first a new temporary,
    numbered late, so it colours before the optimizer's shared values and takes the low register. The value
    retail colours late is a variable's first lifetime. In the dlmalloc code one `bck` holds the chunk before
    the victim in the small-bin path, in the unsorted loop, in binning and in the bin scan; retail's colours
    need the first two to be lifetimes of their own.
  - *Spelling:* the value declared in the block that uses it (`TaggedBlockHeader *previous = ...;` in the
    small-bin path and again in the unsorted loop), the function-level variable left to the paths that share
    it. The reverse case in the same allocator: the end and the new top of a separately placed system block
    are the function's `newEnd` and `newTop` assigned a second time, which is what gives them the first
    temporary registers; a local for the end exchanges three temporaries, and the sum written out at both uses
    is computed after the alignment test instead of before it.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x315170, 0x312ba0).
- **A named local keeps an argument out of the inline's arithmetic.** `addiu a2,s5,-8; addiu a0,a2,-4;
  ... addiu v0,a2,-12`: the argument is computed once and the inline subtracts from it. Passed as an
  expression (`resize(chunk, size - 8)`) the constants fold (`-12`, `-20` from the variable); a `const`
  parameter changes nothing, a cast on the argument stops the folding but numbers the value differently.
  *Spelling:* `unsigned int shortened = size - 8; resize(chunk, shortened);`. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x312ba0).
- **Locals declared in the order they are first assigned.** A search over the declaration order of fourteen
  locals found one that matched; testing every single move showed only five constraints, and the order of
  first assignment satisfies them all. Try that order before searching. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x312ba0).
- **A 64-bit member passed as `%u` is read through a getter.**
  - *Symptom:* a notice passes twelve 64-bit counters truncated to 32 bits. Retail loads the first five whole
    (`ld`) before the branch of a conditional argument and truncates them after it (`dsll32`/`dsra32`), loads
    the seven that go to the stack with `lw`, all of them ahead of the stores; the candidate loads and stores
    one by one and reads the first five with `lw` after the conditional.
  - *Cause:* a cast on the member is narrowed to a 32-bit load in the optimizer and is then a plain operand,
    loaded where its argument register is set. An inline getter returning `long long` leaves a 64-bit
    temporary assigned where the call stands, so every argument is evaluated before any is placed, and the
    truncation happens at placement; within one block the load and the truncation merge into `lw`.
  - *Spelling:* `(unsigned int)pool->getLocalAllocated()` with `long long getLocalAllocated()`.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x312ba0, 0x3194c0).
- **An `int` accessor materialises a flag test.** `andi v0,v0,0x40; sltu v0,zero,v0; beqz v0`: the option
  test goes through an inline returning `int` (`return (flags & option) != 0;`). Written in place, or through
  an inline returning `bool`, the `sltu` is folded into the branch. *Unit:* `src/engine/core/CoreLibrary.cpp`
  (0x312ba0, 0x315170).
- **A copy that coalescing removes leaves its block behind.** `beqz at,L730` to a block that is only
  `b L1138`: the source assigns `newp = oldp` at the end of the first arm, both variables take one register,
  and the jump is not threaded because the block was not empty when jumps were chained. The statements after
  the arms use `newp`. An assertion written ahead of `remainder_size = newsize - nb` likewise leaves the
  subtraction on both sides of the notice. *Unit:* `src/engine/core/CoreLibrary.cpp` (0x3194c0).
- **A read through a `const` getter and a store to the member do not share the member's address.**
  - *Symptom:* a local record's member is read, then stored to inside a loop, each time straight off the stack
    (`lw v0,244(sp)` … `sw v0,244(sp)`); plain reads and stores put the member's address in a saved register for
    the whole block (`addiu s5,sp,292; lw v0,0(s5)` … `sw v0,0(s5)`) and the frame grows by the slots that
    displaces. In the same function a member read three times around calls does keep its address in a register
    (`addiu s5,sp,244; lw a0,0(s5)`).
  - *Cause:* the address `&local + offset` is an expression `IRO_CommonSubs` shares when it is used twice on
    one path. A read through a `const` member function has its address node marked, the plain store's is not,
    so those two are different expressions; three plain reads are one.
  - *Spelling:* `if (event.getSourceFile() == 0 || …) { int *frame = event.getCallStack(); … event.callStack = frame; event.f68 = path; }`
    with `const` getters on the record, and the later fields read plainly.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2e0200).
- **A by-value getter in a variadic call is read before a conditional argument.** `lb v0,976(sp); beqz v0,L;
  lw a2,184(sp)`: the value passed after `spec[0] != 0 ? spec : "0x%08x"` is loaded ahead of the conditional's
  branch. An inline getter's result is a temporary assigned where the call stands, before the conditional is
  evaluated; the member written in place is loaded where its argument register is set, after it. Pointer
  members tested first (`if (event.group != 0 && …)`) are already in a register and need no getter. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x2e0200).
- **A pointer cast to `int` at several calls is one value in a saved register.** With the record's accessors
  declared `(int record, int slot)`, `(int)&event` at each call was shared as an expression and kept in `s5`
  from the top of the function, and every other saved register moved; declared with the record pointer, each
  call builds `addiu a0,sp,176` in place. *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2e0200).
- **A `switch` with one case keeps the branch pair.** `beq v1,v0,body; nop; b past` for a block run for a
  single event type is `switch (event.type) { case 8: …; break; }`; `if (event.type == 8)` gives `bne v1,v0,past`.
  A `case 15:` written in front of `default:` shows in the jump table's bound (`sltiu at,v0,16`, not 15).
  *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2e0200).
- **An element read through a reference accessor keeps `base + offset` when the index is hoisted.**
  - *Symptom:* `lw v1,16(v0); lw v0,176(sp); addu v0,v1,v0; lh v0,0(v0)`: the list's data plus a byte offset
    computed once in front of the loop. With `list->_data[index]` (or a by-value `get(index)`) the same two
    values are added the other way round, `addu v0,v0,v1`.
  - *Cause:* `IRO_MoveInvariantsInAddressExpr` rewrites the address under an indirection inside a loop with
    the invariant part first, `(index << 1) + data`, before `IRO_MoveInvariantExpressions` moves the shift out.
    An accessor that returns a reference leaves the address in its return temporary through the first round
    of loop phases, so it is not under an indirection when that rewrite runs: only the shift is moved, the
    order stays as written, and the temporary is put back into the read in the next round.
  - *Spelling:* `T &operator[](int index) { return _data[index]; }` on the list, `(*bases.p)[parentIndex]`.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2e63e0).
- **Statement order decides which temporaries share a register with a reloaded spill.** `lw v0,208(sp);
  addiu s6,s6,1; lw v1,8(s4); addu s5,s5,v0; lhu v0,20(s4); addu v0,v1,v0`: the reloaded step and the size
  share `v0`, so the cursor's step was written ahead of the statement that reads the size (`slot++; field +=
  step; meta->_sizeofSize = offset(field) + size(field);`). With the size update first, the reload overlaps
  both loads and takes a third register. The two members go through by-value getters: read in place, the
  widened `unsigned short` is evaluated ahead of the `int` on its left. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x2e63e0).
- **A `short` updated in place is sign-extended where it is computed.** `addu v0,s6,v0; dsll32 s6,v0,16;
  dsra32 s6,s6,16` ahead of a list append is `slot += bases[owner]; list->append(slot);` on a `short` local;
  the sum passed as the argument is truncated only by the store. The append is the list's own
  (`n = count(); if (n < _capacity) _count = _count + 1; else List_Resize(this, n + 1, sizeof(T));`): its
  count comes through the `const` accessor, so the increment reads the member again. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x2e63e0).

- **A local declared ahead of a spilled one colours after the scan that follows the spill.**
  - *Symptom:* a write position and the byte total it follows share `s5` where retail has `s0`, with the block
    pointer and the guard size one register low; no order of the function-level locals moves them.
  - *Cause:* the allocator pushes low-degree nodes in ascending id, scan after scan, and colours in reverse.
    The last scan pushed the header pointers and the position first and the long-lived locals after them
    (`45 46 81 | 33 36 37 38`), so the position coloured after them. A position declared before the spilled
    `first` record pointer has a lower id than the header pointers, is pushed in the same scan as the
    long-lived locals and after them, colours first and takes `s0`; the byte total, which does not overlap it,
    then takes `s0` too.
  - *Spelling:* in the block, `char *cursor; GangRecord *first; TaggedBlockHeader *h;`; at the top the guard
    before the block pointer.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x322a70, 0x31d640).
- **A node one neighbour over the limit waits a scan and takes `v0`.**
  - *Symptom:* a size loop's index is in `v0` and every temporary one register up (`v1`, `a0`, …) where retail
    has the index in `a3`. The sibling function with one fewer spilled value matches with the same source.
  - *Cause:* the index has 29 neighbours (traced with the proxy compiler); 25 or more keeps a node out of the
    scan until enough lower-numbered neighbours are pushed, and only four were (the loop's size, chunk and
    the inline's two values). Pushed in the second scan, it coloured before all the loop's temporaries. A fifth
    lower-numbered neighbour puts it in the first scan.
  - *Spelling:* the member's size with its record is a variable set twice, `entry = chunk + 12;
    entry = roundUp8(entry); total += entry;`. A variable set once is propagated away and gives no node.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x31d640; 0x322a70 takes the same source).
- **Mixed signedness keeps two additions, and two masks, apart.** `roundUp8(chunk + 12)` with an `int`
  parameter adds 12 and then 7 where two `unsigned` values fold to 19; a chunk size computed in `int` loads its
  own `-4` where an `unsigned` one reuses the mask already in a register. Each is a conversion node between
  the two operations. *Unit:* `src/engine/core/CoreLibrary.cpp` (0x322a70, 0x31d640).
- **A header written by the shared inline keeps the arithmetic its other callers need.**
  - *Symptom:* a function that always writes the 12-byte header computes the header word count at run time
    (`addiu a2,a1,12; subu a1,a2,a1; srl; addiu -1`), and with the statements written out the constant folds;
    with the fold prevented by a signed local the instructions are retail's but 79 sit elsewhere in the block,
    the `0 & 1` of the cleared flags in `t9` instead of `v0`.
  - *Cause:* the pool's blocks are stamped by one inline that takes the block's byte count or 0
    (`if (total == 0) total = ((size + 3) & ~3) + 12;` in the long branch, `+ 4` in the short one, then
    `words = ((total - ((size + 3) & ~3)) >> 2) - 1`) and a flag that forces the long form. The forced branch
    is removed after the subtraction has been built from two copies of the rounded size, so nothing folds,
    and the statements reach the scheduler in the inline's order.
  - *Spelling:* `initBlockHeader(self, h, size, 0, marked, external)`; the two gang allocators and the
    system-block allocator share it.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x31e0b0, 0x322a70, 0x31d640).
- **A compare written toward the larger side branches through `at`.** `total + used <= max` gives retail's
  `sltu at,max,sum; bnez at` and puts the refused path out of line; `max >= sum` makes a register of the
  compare. `alignment > 8` likewise for `slti at,v0,9`. *Unit:* `src/engine/core/CoreLibrary.cpp` (0x322a70).
- **A member call loads its argument before its object.**
  - *Symptom:* `lw a1,124(sp); jal; lw a0,64(s0)` where the candidate has `lw a0,64(s0); jal; lw a1,124(sp)`:
    the same two loads, the object's issued first. Casts, `get()` and an inline member wrapper change nothing.
  - *Cause (not traced):* MWCC writes a member function's arguments before its `this`; the plain call wrote the
    object pointer first here. An inline wrapper is expanded and its call is plain again.
  - *Spelling:* declare the out-of-line member on the class view (`int addDirectory(igObject *directory);`) and
    map its mangled name to the retail address in the unit's `externals`.
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2d1e40).
- **A virtual call's object read in its own statement is loaded ahead of a conditional argument.** Retail
  loads the object into `a1` in the slot of the branch that picks the text argument (`bnez a3,L; lw a1,148(sp)`);
  written in the call, the object is loaded at the join after the conditional expression. A local
  (`igInfoView *loader = (igInfoView *)poolInfo.p;`) before the call gives retail's order. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x2f8ff0).
- **Discarded `igResult` temporaries take frame slots in the order they are made.** The first made has the
  highest slot. Calls written in an inline helper make their temporaries when the helper is expanded, after the
  caller's own, so two allocator loops moved into a helper gave their results the two lowest slots where retail
  has them above the one the function body makes later. Written in place, the loops give retail's slots. A
  named result local (`int copied; f(&copied, ...)`) takes a slot ahead of every temporary; the call returning
  `igResult` makes a temporary where it is. *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2d2800, 0x2d1e40).
- **An inline's parameter is numbered before its locals.** A string setter inline that takes the object as a
  parameter gives the interned token the first saved register and the object the second; retail has them the
  other way in one of two call sites. The tracer asks for the object's id after the token's; taking the holder
  by reference and reading the object into a local declared after the token gives it. In the movie controller's
  message handler the setter's local takes the interned token directly from the call and is declared before the
  object pointer, and the setter reads the pointer from a smart pointer it takes by reference: the four values then
  get ids token 1 < object 1 < token 2 < object 2, all four are pushed in that order in the last scan, and object 2
  is coloured first (`s1`), token 2 second (`s2`). Each of these alone leaves 13 words: the object pointer declared
  first, a setter taking the raw pointer, the token returned through an inline instead of the setter's local. *Units:*
  `src/engine/core/CoreLibrary.cpp` (0x2d1e40), `src/game/beMovie.cpp` (0x3a8b80).
- **How a call's arguments are lowered (probed under `#pragma schedule off`).** Three steps, in this order:
  - An argument that contains a call, an inline with a statement body included, is evaluated first:
    `f3(p->x, q->y, g())` calls `g` before it loads either field.
  - Every other argument is made ready. One that carries a conversion is loaded here, ahead of the constants:
    `fi(5, 6, p->s)` with an `int` parameter and `fs3(5, 6, (short)p->x)` with a `short` one start with `lh a2`.
    A plain load only has its base kept (`move v0,a1` when the base's register is about to be filled), and a
    computed value is computed (`addiu a1,a2,1`).
  - The argument registers are then filled in parameter order, constants and deferred loads together:
    `f3(p->x, k + 1, q->y)` gives `addiu a1,a2,1; lw a0,0(a0); lw a2,4(v0)`, `fs3(5, 6, p->s)` gives
    `li a0,5; li a1,6; lh a2,8(v0)`. A ninth argument is stored to the stack before `a0` to `t3` are filled.
  - A constant both stored and passed is built once into a temporary and copied: `p->x = 10; f3(10, p->y, 3);`
    gives `li v0,10; sw v0,0(a0); move a0,v0`, not `li a0,10`.
  - "An argument that carries an integer conversion is loaded before the plain ones" (above) is the second step.
  - *Probe:* `struct S { int x; int y; short s; };` with the calls quoted, `void fs3(int, int, short);`,
    `void fi(int, int, int);`, and `static inline int inl(S *p) { int t = p->y; if (t) t++; return t; }` passed as
    `f3(p->x, inl(q), 7)`.
- **The left operand is evaluated first unless the right one is heavier (probed under `#pragma schedule
  off`).** In `(sum of n loads from p) - (sum of m loads from q)` the right side is evaluated first exactly when
  m > n, for n and m from 0 (a parameter) to 4; at equal weight the left goes first, so swapping the operands of a
  subtraction swaps the loads. `p[0] - (q[0] + qv)` loads `p` first and `p[0] - (q[0] + qv + qv)` loads `q` first,
  as with `^`. This fits the b210 rule read by the Persona 4 project, right first when its cost exceeds the left's
  by more than 2, with one load and its add worth at least 3; the costs themselves were not read from b52. To move
  the order, make one side heavier.
  *Probe:* `int M(int *p, int *q, int pv, int qv) { return (p[0] + p[1]) - (q[0] + q[1] + q[2]); }` and its
  variants, first instruction that reads `a0` or `a1` compared.
- **Values the code generator hoists take code-selection ids, after the compare temporaries.**
  - *Symptom:* in a changed-bit scan retail holds the previous word in `a0` and the current compare temporary in
    `a1`; every spelling has them the other way round (ten words), however its loop, declarations and compares are
    written.
  - *Cause:* a value the optimizer hoists is one of its variables and has an id before the compare temporaries. A
    value the code generator hoists (the data loads, the address adds, the words) takes its id in code selection,
    after them. Retail's registers need the second kind.
  - *Spelling:* the mask words read through the holder, `(*(MaskListRef &)current)[material]` with `MaskListRef` an
    `igSmartPointer<igTDataList<int> >`, using the holder's `operator T *() const` and the list's reference
    `operator[]` (the idiom of the sound controller): the optimizer then hoists only the two pointer reads, and the
    reference `operator[]` keeps the address as data first, then offset. A plain read differs by 14 lines, a by-value
    `get()` by 4. The scan is a plain `for` with `break`. The `li a3,1` shared by `1 << bit` and `_wkChgFlag = 1`
    comes from the code generator and needs no source.
  - *Unit:* `src/game/beMatCtrl.cpp` (0x38b1f0).
- **`!=` between two inline calls expands its right operand first.** `HasPlayer(current[m], bit) !=
  HasPlayer(previous[m], bit)` makes the right call's temporaries first. The two results as `bool` locals declared
  in order, `bool now = …; bool was = …; if (now != was)`, give retail's order; without them 4 lines differ. *Unit:*
  `src/game/beMatCtrl.cpp` (0x38b1f0).
- **An inlined callee's holders are laid out below the caller's own.**
  - *Symptom:* two `igSmartPointer<igObject>` holders at frame offsets 140 and 136 and a string reference below
    them, where retail has the holders at 136 and 132 and the string reference at 140; the exception table's
    actions (slot 136, slot 132 with the holder destructor, slot 140 with the string reference's) then differ.
  - *Spelling:* the data-list setup as `static inline ensureDataList(ram)`: its holders are laid out below the
    caller's own string reference. The same helper replaces the hand-written setup blocks of the unit's other
    message handler and still matches.
  - *Unit:* `src/game/beNDMWSaveCtrl.cpp` (0x407120).
- **A value that stays live across a loop is numbered late when it is read through a getter.**
  - *Symptom:* two saved registers exchanged (`s0`/`s1`) between an object's ram pointer and a vertex array, in a
    function with three loops.
  - *Cause:* the vertex array as a declared local has an id right after the parameters. In the scan before the last
    one its degree is 26 (19 physical registers, the ram, six values of the third loop) and it only falls below the
    limit in the final rescan, where the ram (id 32) goes first and is coloured second, so it gets `s1`. With at
    least two loop locals numbered below the array it is pushed a scan earlier, the ram is pushed last and coloured
    first (`s0`). Declaring `stride`, `i` and `k` at the top proves it, and only in that order: the order of `i` and
    `k` decides `a2`/`a1`, and `stride` after `i` moves `a3`.
  - *Spelling:* the array read through an inline getter, `VertexArray(ram)`, so the value takes the getter's return
    id after every declared local; every other local is declared where it is first set (`int stride = …`, `for (int
    i …)`, `for (int k …)`) and the virtual calls cast at the call. The code written out, the getter with a view cast
    on the initialiser and the getter copied into a view local leave 24 words. `int digit;` is declared before the
    loop index, at the head of the branch (inside the loop 8 words differ); that line carries a `matching construct`
    note.
  - *Unit:* `src/game/beNumberCtrl.cpp` (0x3a4b20).
- **A physical `a0` that is live across a block in retail and not in the source: the runtime-call register mask leaks from an earlier file.**
  - *Symptom:* in a meter update's hp block every temporary is one register higher in retail (`a1`-`a3` where the
    source has `a0`-`a2`, 15 words); in a generator update's fill switch retail has `lw a1,52(s3); li v1,116; lb
    a1,0(a1); beq a1,v1` where the source has `a0` (3 words; the switches of cases 0 and 2 use `a0` in both
    builds).
  - *Cause:* the helper that emits a runtime call (`0x4ba430`) takes the call's used registers from one global mask
    (general registers at `0x567280`, float bits at `0x567284`); the code that loads a runtime call's arguments
    (`0x4ba450`, `0x4ba580`) adds each argument register to it with `or`, and nothing in the executable writes it back
    to zero. Every runtime call compiled later in the same compiler process therefore also uses those registers,
    later files included. The `__fixsfdi` call in the meter's hp block uses only `f12` in a fresh process; after an
    earlier `(float)longlong` (`__floatdisf`, argument in `a0`) it uses `a0` too, so physical `a0` is live from the
    function's entry up to that call, which is the interference that reproduces retail's colours (replaying the
    allocator with `a0` made to interfere reproduces every one). In the generator the `__fixsfdi` on case 1's path reads
    `a0` with no write between `beGenerater_SpawnEnemies` and the call.
  - *Evidence:* compiling a one-line prelude, `extern "C" float LeakA0(long long x) { return (float)x; }`, ahead of the
    unit in the same compiler process makes both whole units match; a `(double)int` (`litodp`) prelude does as well,
    while `long long` division (`a0` and `a1`) and `(double)float` (`f12` only) do not. Retail's meter and generater
    units contain no runtime call with an integer argument; in link order `beLOA_Traverse` (`0x389bc0`, `__floatdisf`)
    and `LuaAPI_Dispatch` (`0x370780`, `litodp`) do. That the original build compiled several files in one compiler
    session is an inference; the leak does not reach every file (`beAction2_OnMessageText` puts a temporary in `a0`
    before its `__fixsfdi`), so which files carry it depends on the original build order, which is not known.
  - *No spelling:* no source text inside the unit produces the `a0` use. Meter: `int` locals for the hp values, an hp
    pointer local, a percent local, the percent as an inline helper (with and without an unused `self`), a shared
    `nonZero` flag, a variadic conversion call, the implicit conversion; `igTDataList::append` and `static` are worse
    (88 and 32 lines). Generator: the selector as an `if`, as `unsigned`, through an index, a local, an inline or a
    variable shared by the three switches; `default:` before or after the case; the timer start as `return`, `break`,
    an inline or with a time local; case 1 as one inline; `total` placed elsewhere; an explicit or variadic
    `__fixsfdi`; a variadic `StartTimer`; double constants. All 23 conversion and call spellings tried leave the call
    using `f12` only. A standalone test of the same shape also gives `a0`, and no matched function in the census has
    the pattern.
  - *Spelling:* none inside the unit; the unit's row in `config/SLUS-20836/units.tsv` names the session prelude
    `config/SLUS-20836/session-preludes/runtime_call_a0.cpp`, which compiles a `(float)longlong` conversion first in
    the same compiler process ([build system](../build-system.md#session-preludes)). An unused `static` function with
    that conversion in the file before the affected function also sets the bit, but retail does not emit it.
  - *Unit:* `beMeterCtrl_UpdateRam` (`0x38fa50`, `src/game/beMeterCtrl.cpp`) and `beGenerater_UpdateRam` (`0x384c40`,
    `src/game/beGenerater.cpp`) are matched through the session prelude. Without it neither matches.
- **Stack slots: address-taken named locals take the top slots, by-value temporaries the slots below.**
  - *Symptom:* spill and local slots of a function that builds vectors from calls sit in another order than retail's.
  - *Rule:* named locals whose address is taken take the top slots in source declaration order, whatever their scope;
    the temporaries of by-value results come below them in the order they were created. Declaring a vector where it
    is initialised, rather than at the top, moves its slot.
  - *Unit:* `src/game/beModelCtrl.cpp` (0x396340).
- **An argument that contains a call is evaluated with the calls, in order, before plain loads.** Inlines count: a
  work's sub-command pointer read through an inline accessor is loaded right after the rotation, as in retail, where
  the same field passed plainly is loaded only at the call. Arguments that contain calls are evaluated left to
  right, so the parameter order of a call whose float arguments travel in registers can be read from the order of
  the calls in front of it. *Unit:* `src/game/beModelCtrl.cpp` (0x396340).

### `asm` and `volatile`

- **An `asm` statement without outputs is volatile already.** Its keyword does not keep it or move it; strip it.
  A review of the Sony kernel rows found 47 of their 63 keywords removable. The keyword still changes the code
  around it when the block has a peephole candidate (next entry), so run the strip test on the whole function.
- **A `volatile` `asm` statement opens a basic block that the peephole skips (probed).** The code generator starts
  a block at an `__asm__ volatile(...)` statement, with or without outputs, and marks it (block flag `0x80` in
  `gdb_pcode.py`'s dump, `0x04` otherwise). The PCode peephole then leaves the rest of that block alone: `bool b =
  !!(s & 1);` after the statement keeps `sltu; xori 1; xori 1; andi 0xff`, as `#pragma peephole off` does, while
  a plain `__asm__` (with or without outputs), an MWCC `asm { }` block, an `asm` function earlier in the file or a
  `volatile` statement in an earlier block or function leaves the peephole on and folds the pair to `sltu`. The
  GameCube 1.2.5 rule that an `asm` function turns the peephole off for the rest of the file does not hold on b52.
  *Probe:* `int f(int *p, int s) { __asm__ volatile("sync"); bool b = !!(s & 1); if (*p == -1) return g; if (b)
  return SignalSema(*p); return iSignalSema(*p); }`, then without `volatile`, with `asm { mfc0 s, $12 }`, and with
  `if (q) g = 2;` between the statement and `b`.
- **Sony's input-operand form.** A `$gp` store spelled with its word as an output (`"=m"`) can be moved and needs
  the keyword; Sony's text passes it as an input, `__asm__("sw $28,%0" : : "m"(word))`, which is fixed already. A
  `"memory"` clobber, as every helper in Sony's `eekernel.h` has, does what a keyword on a syscall statement did.
  *Units:* `src/sony/`.
- **MWCC's `__I_<mnemonic>` builtins are inline assembly.** They emit one named instruction from C
  (`__I_mfc0(3, 12)`), and count as `asm` uses.
- **A `static` C function holding one `asm` block gives the same bytes and caller effect as an `asm` function.**
  The caller's argument registers stay live across a call to any `static` function defined earlier that contains
  inline assembly; that proves "static, earlier, contains asm", not "asm function". *Unit:*
  `src/engine/dmaChannel.c`.
- **Hand-written assembly shows in alignment and MMI.** A 4-aligned object or a loop top at 4 mod 8 under
  ee-gcc 2.96, `lui`/`ori` for -1 where 2.96 uses `addiu`, and MMI byte operations (`psubb`, `pcpyh`, `psubw`) with no
  C spelling: the R5900 string and memory routines. *Unit:* `src/newlib/`.
- **MWCC's assembler writes `li reg,0` as `addi`.** In an MWCC `asm` function `li a1,0` assembles to
  `addi a1,zero,0`; retail's constant builds have `ori a1,zero,0`, which the source writes out. *Unit:*
  `src/engine/p2core.c` (0x1eba30).
- **Three shapes only `volatile` gives under ee-gcc 2.96.** No type, alias set, pointer spelling or statement
  barrier has reproduced these, so a function that needs one of them was compiled with a `volatile` access (the
  owner still decides the row, [source approvals](source-approvals.md)):
  - a load or store kept out of a delay slot: a plain access before a `jal`, or at the head of a branch's target, is
    always taken into the slot (`bnel; lw` where retail has `bne; nop` and the load after it), and
    `do { } while (0)` does not stop it;
  - the single-use `lui`, `addiu`, `0(reg)` address form with no call or block boundary before it;
  - a store followed by a load of the same address, or two reads with nothing between them: no spelling makes the
    compiler forget a value at the same address.
  The alias-set causes (enum, pointer types, address-taken locals, `-fno-strict-aliasing`) only order accesses to
  different addresses and reach none of the three. *Units:* `src/cri/mwsfsvr.c` (0x29ad40, the slot),
  `src/cri/svm.c` (0x27ec50, `sw; lw` back to back: 88 bytes against 84 without the keyword).
