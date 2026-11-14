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
A local of class type is the exception: it has no id of its own. `IRO_ScalarizeClassDataMembers` replaces its
member with a temporary that takes its id after every declared local and every inline's parameter, wherever the
class local is declared (see [declaration order](#declaration-order-and-evaluation-order)).
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
  `include/dw4/igTDataList.h`. *Units:* `src/game/beNodeAnim_Traverse.cpp`,
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
  - *Unit:* `src/engine/core/CoreLibrary.cpp` (0x2fed50, 0x3064b0, 0x306510).
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
- **A conditional expression keeps both arms; an `if`/`else` that assigns a variable to itself loses one.**
  `beqz flag; b; move a0,v0` around a second call whose result is also moved to `a0` is
  `pool = g_useOwnerAllocator ? pool : Memory_GetAllocatorBySelector(...)`. Written as
  `if (flag) pool = pool; else pool = ...;` the self-assignment is deleted and the function is 8 bytes short;
  `pool = (int)pool;` kept it only because the cast hides the self-assignment. *Unit:* `src/game/beModelCtrl.cpp`.
- **A bare truth test that opens a loop condition is materialised.** `sltu v1,zero,a0; xori v1,v1,0x1; bnez`
  for the first operand of `while (*a && *b && *a == *b)`, and a plain `beqz` for the second: the strcmp shape
  written plainly. `*a != 0` there folds to `beqz`, and a `(bool)` cast is not needed. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x2d3d30).

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
    bad-chunk report) and the arena block check (0x312790, `igResult`). The page pool's memory operation (0x326410)
    shows the effect but has not been matched.
- **A commutative add takes the plain variable as its first operand.** The front end orders the operands of `+` so
  that a leaf comes first. An inline call counts as complex until it is expanded, and a conditional expression is
  always complex. To get retail's `addu v1,a0,v1` with the payload in `a0`, the payload has to be a variable. When
  the value is only computed after the guards of a check, that means splitting the `&&` chain into nested `if`s and
  assigning the variable between them: `if (level > 0 && ml > 0) { size = …; if (((Chunk *)((char *)h + (size +
  header)))->used && ml > 0) … }` compiles to the same branches as the flat chain. *Unit:*
  `src/engine/core/CoreLibrary.cpp` (0x30fa90).

### Declaration order and evaluation order

- **Declaration order, getters and helper argument order decide ids.**
  - A count declared before a cast list pointer (`int count; List *list = (List *)target; count = list->_count;`)
    gives the list the lower saved register; the natural order swaps them. *Unit:* `src/game/beNDMWShopCtrl00.cpp`.
  - A value an inline helper returns, and a helper's own locals, are numbered with the inline's values; using the
    getter (`work = buildData(self)`) and the setter inline together gives retail's order where hand-ordered locals
    stood before. *Unit:* `src/game/beDemoManager.cpp`.
  - An inline's arguments are evaluated before its body: `AppendRecordString(self->_messenger, db, record, key)`
    loads the messenger into a saved register before the call inside it. *Unit:* `src/game/beNDMWShopCtrl00.cpp`.
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
  - *Unit:* `src/engine/core/CoreLibrary.cpp`.
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
