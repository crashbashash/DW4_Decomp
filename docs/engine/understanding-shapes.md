# Understanding a resisting shape

How to find out why a function compiles to bytes other than retail's, and what source the original had. A shape is
understood when the cause is known in the compiler's terms and the spelling that gives it has a reason in the code's
own terms. A search that only finds bytes is not understanding: it is the last resort, and its result carries a
`matching construct` comment.

The procedure comes first, then the instruments, then the causes found so far, each with the unit where it turned up.
[Source idioms](matching-decomp.md#source-idioms) is the short list of shape and spelling; this document is the
method and the reasons.

## The procedure

1. **State the difference exactly.** Compile the candidate under the unit's profile and read the instruction diff:
   `python3 tools/check.py --no-cache --function 0xVA --cand <file>`, and for a whole listing
   `python3 tools/project.py cc --version SLUS-20836 <symbol> <file> <out>.o` then
   `mipsel-linux-gnu-objdump -dr <out>.o`. Write it down in machine terms: "the body reloads `52(s0)` where ours
   reuses the guard's load", "the count gets `a0`, retail's `a0` is the list", "four bytes short, the delay slot is
   filled". A size difference, an order difference and a register difference have different causes.
2. **Read the function and its unit.** Real types from `include/dw4/reflected.h`, what each value is for, how the
   same class does the same thing elsewhere, and the GameCube and Xbox builds of the function (below). Most
   resisting shapes are an idiom of the original code base (an accessor, a smart pointer, a helper) that the draft
   wrote out by hand.
3. **Form a hypothesis about the source**, not about the bytes: "the original reads the list through a `const`
   accessor", "the original used the class's inline `next()`". A hypothesis names a construct a programmer would
   write.
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

### The register-allocator tracer

**When:** the instructions are right and only registers differ. `tools/dispatcher/regalloc.py` ties each register to
its allocator node and searches the id orders that give retail's colours
([usage](../../tools/dispatcher/README.md), [model](register-allocation.md)). It has no profile for b52; the combat
build follows the same rules on the shapes tried so far, so run it as a proxy with the unit's flags:

```sh
python3 tools/dispatcher/regalloc.py 0xVA <file> --compiler local/mwcps2/combat/mwccps2.exe \
    --flags "-O4,p -sdatathreshold 2 -inline level=8,bottomup -Iinclude"
```

Ids are what decide colours: select pops nodes in reverse id order, so a later id colours first. Declared locals
take ids in declaration order (parameters first). The locals and temporaries of inlined functions take theirs after
all of the caller's locals, mid-block C++ declarations included, and a second web of one variable takes a late id.
Compiler-made values (a strength-reduced offset, a hoisted invariant, a CSE temporary) take ids when the phase that
makes them runs. So registers follow the order values come into existence, and a value that has to colour early is
the caller's declared variable, not an inline's local. A whole-file unit with code outside the function is refused;
copy the function into a test file.

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
Units are named by their source file.

### Loads shared or kept apart (b52)

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
- **A conversion on an operand makes it evaluate first.** A float compare whose limit operand carries any conversion
  (a `const` getter's implicit `T *` to `const T *`) loads that operand later, into the later FP register.
  *Spelling:* `static inline float fadeLimit(const Work *w) { return w->_fadeLimit; }`. *Unit:*
  `src/game/beAction2.cpp`.
- **A `const` reference getter reloads.** `const int &getCount() const { return _count; }` loads through the
  returned reference, so a later `_count + 1` reads memory again, and the value lands in the caller's declared
  variable with its early id. It replaced a `volatile` count. The getter is `igTDataList<T>::getCount` in
  `include/dw4/igTDataList.h`. *Units:* `src/game/beNodeAnim_Traverse.cpp`,
  `src/engine/scenegraph/SceneGraphLibrary.cpp`.
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
  `case 0: break;` and the cases in that order; without `case 0` the function is 8 bytes short, with
  `case 0: return;` 8 long. *Unit:* `src/game/beAction2.cpp`.
- **A constant on the left keeps `slt`.** `if (capacity >= list->_count)` with `capacity` 0 gives `slt zero,count`
  and `bnez`, where `count <= 0` folds to `blez`; a `bool` local compared `== false` keeps the materialised test.
  *Units:* `src/game/beDemoManager.cpp`, `src/game/beSound.cpp`.

### Types and values

- **Byte-returning callees make `& 0xFF` natural.** b52 emits `andi v,v0,0xff` after a call only when the result
  of a byte-returning function is compared (`f() == 0`, `== 1`), never for a truth test (`if (f())`). Each retail
  `andi 0xff` before a branch is the compare of a function declared `unsigned char` or `bool`; an explicit mask is
  not the source, and an `int` declaration of a byte function drops it. *Unit:* `src/game/beNDMWLoadCtrl2.cpp`.
- **`const bool &` and `const int &` literal temporaries become data.** A literal passed by `const &` to an inline
  becomes an anonymous `@N` object per call: a one-byte `.sdata` constant for a `bool`, a `.rodata` word for an
  `int`. Retail data that looks like a named flag table can be these. *Units:* `src/game/beNDMWMdlPEBase.cpp`
  (58 int and 34 bool constants), `src/game/beNDMWShopCtrl00.cpp`, `src/game/beNDMWListCtrl.cpp`.
- **An inlined `operator+=` gives a frameless function an exception record.** Retail keeps an exception record
  for a leaf with no frame. `*vertex += shift;` through an inline
  `igVec3f &operator+=(const igVec3f &o) { x += o.x; y += o.y; z += o.z; return *this; }` keeps it and explains the
  odd register use; `x = x + o.x` in the operator, a by-value parameter or plain float adds do not. The internal
  rule is not known. *Unit:* `src/game/beFont.cpp`.
- **A local whose address goes to a pointer parameter gets a stack slot.** A value stored to the stack and loaded
  back for a store, with no `volatile`: `pushed = item; ... set(count, &pushed);` with
  `void set(int i, T *const *v) { _data[i] = *v; }`. A reference parameter, a by-value parameter with an internal
  `&value`, or a one-field struct are scalarised and lose the slot. The setter is `igTDataList<T>::set` in
  `include/dw4/igTDataList.h`. *Units:* `src/game/beNodeAnim_Traverse.cpp`,
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

### Scheduling (EE GCC)

- **EE GCC orders stores only within one alias set; a field's or read's type decides the schedule.** Two memory
  accesses are kept in order when they may alias, and the alias set comes from the lvalue's type. Before register
  allocation only same-type accesses through the same base are ordered; after it the base registers are set more
  than once, so every pair in one alias set is ordered, and an access of another type (a pointer read among integer
  stores) is outside that chain, gets low priority and is issued ahead of the first store. Giving a field the same
  pointer type as another, or reading a reply through its true type, changes the order of the instructions around
  it. *Unit:* `src/sony/libpad/libpad.c`.
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

### Declaration order and evaluation order

- **Declaration order, getters and helper argument order decide ids.**
  - A count declared before a cast list pointer (`int count; List *list = (List *)target; count = list->_count;`)
    gives the list the lower saved register; the natural order swaps them. *Unit:* `src/game/beNDMWShopCtrl00.cpp`.
  - A value an inline helper returns, and a helper's own locals, are numbered with the inline's values; using the
    getter (`work = buildData(self)`) and the setter inline together gives retail's order where hand-ordered locals
    stood before. *Unit:* `src/game/beDemoManager.cpp`.
  - An inline's arguments are evaluated before its body: `AppendRecordString(self->_messenger, db, record, key)`
    loads the messenger into a saved register before the call inside it. *Unit:* `src/game/beNDMWShopCtrl00.cpp`.
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

### `asm` and `volatile`

- **An `asm` statement without outputs is volatile already.** Its keyword does nothing; strip it. A review of the
  Sony kernel rows found 47 of their 63 keywords removable.
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
