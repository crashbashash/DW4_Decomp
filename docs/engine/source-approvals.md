# Approved inline `asm` and `volatile`

An `asm` statement or a `volatile` passes the byte check whether or not plain C could produce the same
bytes, so either can force a match the original source did not have. A C or C++ function that uses one
counts as matched only once the project owner has approved that use. This is the same rule
[hand-written `.S` sources](assembly-sources.md) follow.

## The approval rule

Each approved use has a row in `config/source-approvals.tsv`: `kind` (`asm`, `volatile` or `asm-function`),
`symbol`, `count` and the anchor of its evidence below. An `asm-function` row approves a whole MWCC `asm`
function, one written in assembly in the original source; its count is 1. Without it, such a function is
an asm body ([asm-body matches](asm-body-matches.md)), which counts in no matched figure. Only the owner approves a row. An agent may write one only
when the owner has explicitly told it to add that function, after reviewing its evidence. It never adds
one on its own initiative or as part of a broader request. The table is one of the oracle's own files
(`.githooks/oracle-files.txt`).

A function using either without a row is filed by `make check` as **`unapproved`**. Its source stays and
links byte-identically, and its code bytes count in the code-bytes-identical figure, but it is not
`match`, so it is in no matched figure and not in the readable count. A byte match is not approval.

```sh
python3 tools/sourceapprovals.py --list    # the functions awaiting approval, with what each one uses
python3 tools/sourceapprovals.py --stale   # rows that no longer describe their function
```

## What reaches a function

`tools/sourceapprovals.py` counts the uses in the function's own definition, the inline helpers it reaches
by name, the file-scope declarations it reaches, and the project headers the file includes. A file-scope
declaration is reached when the function or one of those helpers names something it declares, directly or
through another declaration it reaches; C keywords are not names, but a type name is. So a `volatile` global
reaches the functions that use it, and a struct member declared `volatile` reaches the functions that name
the struct or a type built on it. A whole-file source declares its module's words once, and each function
answers only for the ones it touches. The count voids an approval when another use appears, which files the
function as `unapproved` again.

Three things need no row:

* `sync` and `ei`, which C cannot spell. The debt ratchet still counts them.
* Stock source under `src/third_party/`, which is never edited.
* `.S` sources, which have their own table.

## Testing a `volatile`

Remove the keyword and verify the function again. What the bytes do says what the keyword was doing:

* **They still match.** The keyword did nothing, so it goes. Remove keywords one at a time and repeat until
  none falls, as one can depend on another.
* **Same size, the same instructions in another order or other registers.** It only steers scheduling or
  colouring, which is never approved. Look for the spelling.
* **Fewer instructions.** It keeps a memory access that retail really has. That is the reload a case needs, but
  it does not show how the original source kept it.

Before taking either of the last two to the owner, read the value at another type, as under `b52` that is often
all the keyword was doing: [matching decomp](matching-decomp.md) has the shapes. Swap `volatile` for `const` first,
then try another same-sized type.

Hardware is the exception to the first case. A register access can match without the keyword when nothing would
merge or drop it, but the source would then misstate what the code addresses, so it keeps the keyword and goes
to the owner.

The `lui`, `addiu`, `lw 0` address form is not evidence for a `volatile` global by itself under GCC: functions that
match without one have it too, nearly always because the address register has a second use. Under ee-gcc 2.96 a
single-use access in that form, with no call or block boundary before it, has no plain spelling that has been found.
That points to a `volatile`-qualified access, not to state shared between contexts, so it does not make a case alone.

Confirmed shared state can make the case by itself when the evidence for it is good: a writer shown running in another
thread or an interrupt, and the variable read where that writer's change has to be seen, such as a wait or exit flag
polled in a loop. A loop containing a call reloads with or without the keyword, so there the strip test shows no lost
load, and the case rests on the shared state, with the address form or another sign of the qualifier in support. A
`volatile` that only steers scheduling, on state nothing else writes, is still never approved.

## What counts as evidence

The evidence has to show that **the original source used it**. Strongest first:

* **An upstream source** that writes the same statement.
* **Hardware the retail code really addresses:** a memory-mapped register read or written at its fixed
  address, where the compiler would otherwise merge or drop the access.
* **A real reload, for `volatile`:** retail reads the value from memory where the source says, and no
  ordinary spelling keeps that read. A reload is necessary here but not sufficient, because it shows
  what retail does, not how the source got there.

A `volatile` that only pins when a load is scheduled, where retail reads once, is never approved. A failed
C search can support a case but never makes it: it shows that C has not been found, not that the original
used the construct.

## Approved statements are not debt

`inline_asm.other` in the [debt ratchet](debt-ratchet.md) counts an `asm` statement until every function it reaches
has a row whose count is current. Adding a row needs the owner, so an approved statement needs no re-recorded
baseline. A new statement, a statement reaching one more function without a row, or a row its count has voided puts
the statement back in the counter. `python3 tools/inline_asm.py` prints the approved statements and `sync` and `ei` beside the debt.
`sync` and `ei` need no row and are not debt: C cannot spell them, and the owner has approved them all.

## Approved

### umul_ppmm

`__divdi3`, `__moddi3`, `__udivdi3` and `__umoddi3` reach one `multu` through `umul_ppmm` in
`include/dw4/libgcc_longlong.h`.

* Upstream GCC writes this statement for MIPS: the `longlong.h` of 2.95.3 and 3.0 both have
  `__asm__ ("multu %2,%3" : "=l" ... : "d" ... )`. The exact 2.96-ee source is not available to confirm it.
* C does not reproduce it. A `long long` multiply changes the size of all four routines. Splitting the
  low and high halves keeps the size but leaves 3 to 6 words different, because the compiler adds a
  three-operand multiply beside the `multu`.

### stream-slot-state

The 7-bit state field at +70 of a stream slot.

* Thread code sets the field and queues a callback. DMA interrupt handlers registered with `AddDmacHandler` walk that
  queue, and the callbacks write the field, so an interrupt changes it while thread code reads it.
* Retail reads it repeatedly in one condition with no call between. Without the keyword the reads merge and the
  function comes out shorter.

### adxm-thread-ids

The ADX manager's thread id words, written at thread creation and cleared at shutdown, and read by lock callbacks,
event callbacks and thread bodies.

* Retail keeps loads a plain spelling drops: a load right after the store with its result unused, or a second read
  with no call between. The functions come out shorter without the keyword.

### svm-lock-counts

The SVM lock's nesting count and type are globals changed around the lock and unlock callbacks. Retail stores the
count and immediately loads it back, which a plain spelling forwards from the register.

### srd-server-words

A word read by the SRD server thread. Retail stores it and loads it straight back for the next store, which a plain
spelling forwards.

### srd-spin-counter

A wait on a flag the SRD server writes, counting passes in a global with a timeout. Only the waiting function touches
the counter, so it is not shared state. Retail stores it and loads it back on every pass, which is what a `volatile` delay
counter does, and a plain spelling keeps it in a register.

### srd-module-words

The SRD module's server words at `0x4a92c8` up to `0x4a92f8`, which its whole-file source declares `volatile`:
the lock switches (`0x4a92c8`, `0x4a92cc`, `0x4a92d0`), the error-check switch (`0x4a92d4`), the wait counter
(`0x4a92d8`), the error-query flag (`0x4a92dc`), the read, completion and create counts (`0x4a92e0`, `0x4a92e4`,
`0x4a92e8`) and the previous and current trace markers (`0x4a92f0`, `0x4a92f4`). The destroy count at
`0x4a92ec` stays plain: nothing in the code tells the two spellings apart.

* Every retail access to these words, in every function, uses the `lui`, `addiu`, `0(reg)` form. The words
  either side (`0x4a92c4`, and `0x4a92f8` onward) use the folded `%lo` form at every single-use access. Within
  one function a single read of an error-query flag takes the first form and a single read of a configuration
  word the second.
* Compiled as one file with one word's `volatile` removed at a time, each word but the destroy count breaks a
  function that matches with it: a getter or setter whose single access folds, a store loaded straight back, or a
  counter reloaded on each pass.
* They are shared state: the module's server step runs under CRI's lock and test-and-set routines, and the words
  it writes are read by setters, getters and the module's debug summary.
* The create count is touched only by its own increment, and its keyword changes only how a delay slot is filled:
  without it, the delay-slot pass moves a later register copy into the slot of the call before the increment;
  with it, the pass stops at the count's load and leaves a `nop`, as retail does. Hand variants and a
  decomp-permuter search barred from adding qualifiers found no plain spelling. The owner approved it on the
  declaration context: the module declares its data in file order, and the count sits in a run of four counts of
  the same role whose read ones are proven `volatile`, followed by a proven `volatile` word.

### sud-timer

CRI SUD's EE-timer words: the tick count (`0x4bf290`), the clock and its saved copy (`0x5856b0`, `0x5856c0`), the
clock pointer (`0x5856d0`), the nesting count (`0x5856d4`), and the two tables of timer-register addresses
(`0x4f5a70`, `0x4f5a80`) whose targets are declared `volatile`.

* The tables hold the EE timers' MODE and COUNT registers (`0x10000010`, `0x10000000` and the other channels).
  Retail reads the count register full-width and masks it, where a plain spelling narrows the load.
* The tick decrements its count and loads it straight back after the store, then loads it again to clear it when
  negative; the read increments the nesting count and loads it straight back, and re-reads the clock after
  storing it. These are reloads a plain spelling forwards.
* Every access to the RAM words, in every function, uses the `lui`, `addiu`, `0(reg)` form, and nothing outside
  the timer functions touches them. Compiled as one file with any one `volatile` removed, the timer init or the
  timer read no longer matches.

### build-string-stores

A module's init stores the address of its version string in a word that nothing else reads or points to, in the
`lui`, `addiu`, `0(reg)` form, ahead of the code a plain spelling would let it sink into. It is the write-side
counterpart of a build-string read. The owner approved it for the four inits that do it: ADXT (`0x56dfa8`), SUD (`0x5856a8`), SFX
(`0x5856a0`) and CFT (`0x573ea8`). In each the store is the word's only access in the executable.

### adxt-ready-count

ADXT's tick count at `0x49c8f0`, which the init file declares `volatile`.

* It is shared with a thread: ADXT's init clears it, the server entry and ADXPS2's manager-thread callback
  increment it, and the handle code copies it into a handle as a start time.
* The same statement, a handle's start time set from the count, compiles in the `lui`, `addiu`, `0(reg)` form
  in one ADXT file and folded into `%lo` in another, which one declaration cannot give: the original declared
  the word `volatile` in some files and plain in others. The init's single store has the first form, and no
  plain spelling tried reproduces it.

### build-string-reads

A function reads a word holding the address of a build string, such as `"\nSRD/PS2EE Ver.2.22 Build:..."`, and never uses
the value.

* This is not shared state. The evidence is the mechanism: the word is the string's only reference, none of the GCC
  functions that match with no keyword has a load whose result goes unused, and every plain spelling tried drops it.
* That the source reads the word to keep the string linked is inference. The owner accepted these on that basis.

### metrowerks-runtime-asm-functions

`__ptmf_scall` and `__TransferControl`, from the Metrowerks C++ runtime: `src/runtime/__ptmf.c` and
`src/runtime/ExceptionHandlerTS.c`.

* Metrowerks' own runtime source, shipped with CodeWarrior for PlayStation 2 R3.04, writes both as MWCC `asm`
  functions: the pointer-to-member call in `__ptmf.c`, the restore of a catcher's registers in
  `ExceptionHandlerTS.cp`. The executable's instructions follow that source one for one.
* The sources here are written from the runtime's data layouts (`PTMF`, `ThrowContext`) and its instructions,
  with no comments or other text of Metrowerks' copied. `__TransferControl` starts with `.set reorder`, as the
  original does, so the assembler moves the final stack adjustment into the jump's delay slot.
* No C can write either: one takes its argument in `t9` and leaves through a jump on it, and the other loads
  another frame's saved registers and returns into it.

### sony-libkernl-cop0-and-syscall

Sony libkernl functions written in C with instructions C has no spelling for: reads and writes of COP0 registers
(`mfc0`, `mtc0`), `cache` operations, `di`, `sync.p`, and system calls made from inside a C file.

* Sony's own build shows they are C: each sits in an SDK 3.0.3 `libkernl.a` member that carries the compiler's
  markers and records a `.c` source, and the cache, interrupt, thread, heap and TLB functions are byte-identical to
  those members with relocated words masked.
* The system calls in these files are local functions of C members, not part of the assembled stub file, so each
  is a C function holding one `syscall`.
* The `volatile` on each `__asm__` keeps the statement from being moved or dropped, which it must not be.
* One TLB function keeps a counter in a fixed register across calls, which only a register variable gives.
* The SIF's data-cache write-back is one `asm` block: a loop of `cache 0x18` with `sync`, carrying its own return. It
  sets `.set noreorder` and leaves it on, so the compiler's closing `jr ra` gets no delay-slot `nop`, as in Sony's
  member and the executable.

### sony-gp-and-syscall-asm

Sony library functions in C that read or swap `$gp`, or make a system call, through an inline `asm` statement: the
callback and handler registration of libmpeg, libcdvd, libkernl's SIF and timer code, and two thread calls.

* Sony's own build shows they are C: each sits in an SDK 3.0.3 member that carries the compiler's markers and records
  a `.c` source, and each is byte-identical to that member with relocated words masked. One power-off handler's
  member is a version four bytes shorter, with the same `$gp` store.
* C reaches neither `$gp` nor a system call. A handler registered for another context records the caller's `$gp`,
  and a callback runs on the `$gp` its owner supplied.
* The `volatile` on each `__asm__` keeps the statement in place, and a `"memory"` clobber is what makes the values
  around a swap reload, as retail does.

### sony-interrupt-shared-state

Sony library state an interrupt handler writes while thread code waits on it: the vertical-blank flag and time
`VSync2` passes to its handler, the DMA state `_ch3dmaCSC` shares with its channel's handler, and the DECI2 state
`sceTtyInit` shares with `sceTtyHandler`. Retail reloads each where the waiter reads it, which a plain spelling merges.
Only the fields the handler writes are qualified.

### adxm-thread-flags

The ADX manager's server threads and its border wait. Each server thread loops until a 64-bit exit request is set,
then records that it has exited, and the border wait spins on a flag the server thread clears. Other threads set
the requests and wait on the exit words, so the state really is shared between threads.

* The loops contain calls, so they reload the flags with or without the keyword, and the strip test loses no load.
  The case rests on the shared state, approved on that basis.
* Retail reads every one of these words through a full address in a register. Under ee-gcc 2.96 a single plain access
  is never written that way, which supports a `volatile`-qualified access in the source.
* One server thread also writes the GS background colour register at its fixed address, a hardware access.

### sony-hardware-registers

Accesses to EE and GS registers in Sony's libraries, and in the CRI code that drives the same registers. Each
keyword is on a fixed register address, or for the DMA channels on a register reached through a channel pointer.

* Sony's `eeregs.h` in SDK 3.0.3 defines the registers as `volatile` pointers to their fixed addresses, and its
  access macros go through them, so code using the header is `volatile` without writing the word. The header's
  copyright begins in 1998, and a Release 1.6 sample uses the same macros.
* Sony's `libdma.c` in that SDK has the source of the DMA functions. Its bodies of the channel pause and the two
  channel waits compile to retail's bytes under the library's profile, given only declarations for what they call.
* Other functions in these libraries are byte-identical to objects in the SDK's archives. The remainder sit in the
  Sony code block under the same compiler.
* Most keywords change the bytes when removed, so the compiler would merge or drop the access. The others rest on
  the header.
* Adding `volatile` to the plain register accesses left in these functions keeps them matching, with one exception:
  a 64-bit read of a register the header declares as 32 bits. A cast to the wider type, which that read needs, drops
  the qualifier and matches retail.
* The serial port registers are the exception to the header: they are absent from it and identified from the
  open-source ps2sdk.

DW4's libraries are SDK release 2.8.0, which is not available, so the text compared is from a later release.

### sony-alarm-id

The timer alarm functions declare the id member of their alarm record `volatile`.

* The Timer Library's `alarm.c` in SDK 3.0.3 declares that member `volatile`. Its function bodies, given only
  retail's symbol names and the library's constants, compile to retail's bytes for all of these functions, and to
  different bytes once the qualifier is removed.
* The functions are also byte-identical to objects in the SDK's archives.

### sony-timer-state

The timer functions declare `volatile` the members of the timer state and counter records that its interrupt handler
also uses.

* The Timer Library's `libtimer.c` in SDK 3.0.3 declares those members `volatile`. Its function bodies, given only
  retail's symbol names, the library's constants and retail's helpers for the timer registers, compile to retail's
  bytes for these functions, and to different bytes once the qualifiers are removed.
* The functions are also byte-identical to objects in the SDK's archives.

### sony-vu-and-gp-asm

`sceGsResetPath` and `sceSdRemote` hold statements C has no spelling for.

* Sony's `libgraph` and `libsdr` sources in SDK 3.0.3 write these as `__asm__` statements. `sceGsResetPath` orders the
  VIF1 reset with `sync.l`, then sets a bit of VU control register `$vi28` with `cfc2`, `ori`, `ctc2` and `sync.p`.
  `sceSdRemote` reads `$gp` through one inline helper to record it beside a registered handler, and swaps it through
  another around an RPC call that has an end function.
* Compiled from Sony's text with only retail symbols, constants and helper names mapped, both functions are
  byte-identical to retail. `sceGsResetPath` needs the assembler of its [compiler note](sd-prologue.md).
* C reaches neither a VU control register nor a move of `$gp`.
* `sceSdRemote`'s two `volatile` keywords belong to these statements. Sony writes them, and neither can go: without the
  one on the read the registers differ, and without both the function comes out 164 bytes short.
  `sceGsResetPath`'s statements have no outputs, so its `__volatile__` changes nothing and is left out.

### dma-channel-cop0

The engine's DMA channel queues in `src/engine/dmaChannel.c`, an MWCC file. Two functions read the COP0 Status
register before taking a node from a shared pool, and one waits on the COP0 condition.

* C has no spelling for a COP0 register read or for a branch on the COP0 condition (`bc0f`).
* Both pool functions test the interrupt-enable bits (IE and EIE, bits 0 and 16) together, and disable interrupts
  around the pool update only when both are set. In every MWCC copy of this test in the executable, five
  functions in all, the shift goes into `a2` and the `and` writes back into whichever register the read used.
  The compiler picks that register and never picks `a2` by itself, so the shift and the `and` were text of the
  statement, with `a2` named and clobbered: `mfc0 %0,$12; srl $6,%0,16; and %0,%0,$6`. Reading the register alone
  and testing it in C gives the same instructions with other registers.
* The `volatile` on each `__asm__` keeps the read from being moved or merged.
* The wait is five `nop`s and a `bc0f` back to its start, then a return, with no frame: an MWCC `asm` function.
  The function after it keeps argument registers live across calls to it, which needs the callee to be a
  `static` defined earlier in the same file.

### dma-channel-shared-words

Words of the engine's DMA channel and frame code that thread code and an interrupt handler or another thread
both reach: the two flag words at `0x56d670` and `0x56d678`, the semaphore ids at `0x569030` and `0x56bf90`, the
frame count at `0x56bf70` and the watchdog's tick counter at `0x56d680`.

* The handler is registered with `AddDmacHandler` and ends with `sync` and `ei`. It clears a bit in both flag
  words, while thread code sets and clears another bit in them between disabling and enabling interrupts.
* Thread code clears its bit in the first word and then in the second, and retail stores the first before it
  loads the second. Through a plain array, a struct or two separate words the compiler knows the two cannot
  overlap and loads the second word first; only a `volatile` declaration keeps the order, which the interrupt
  sharing makes the source's own.
* The wait loop reads the semaphore id twice, once to record it and once to wait on it, with no write between;
  retail loads it twice. Without the keyword the two reads merge.
* The handler's two uses are the same flag words, declared `volatile` in its file.
* The frame-wait function that sets and clears another bit in the flag words also waits on a semaphore at
  `0x56bf90`, read twice as above (without the keyword it loses a load), and polls a 64-bit count at
  `0x56bf70` until it passes a target. A GS interrupt handler, registered with `AddIntcHandler`, advances that
  count. The loop calls a function, so it reloads with or without the keyword; the keyword keeps the order of
  the accesses, and the interrupt writer makes it the source's own.
* A watchdog thread, whose entry, 4 KB stack and `gp` sit in a thread parameter block at `0x4965d4`, copies the
  first flag word into the second on each tick and aborts if the bits it copied last time are still set: the
  DMA handler clears them when the work completes. It reads the second word twice, and retail loads it twice.
  It also counts ticks at `0x56d680`, which ordinary code resets from about forty places, and aborts after 60;
  that counter is shared with other threads and polled in the loop, where the keyword keeps the order of its
  accesses.

### gs-interrupt-sync-ei

The GS interrupt handler in `src/engine/p2gs.c`, an MWCC file registered with `AddIntcHandler`, ends with `sync`
and `ei`, each written `__asm__ volatile`. `sync` and `ei` need no row; the row is for the keyword on the statement.

* Under MWCC an `__asm__ volatile` statement turns the global optimiser off for the whole function. Retail has
  the unoptimised shape: a branch for each status bit with the test recomputed from the saved status each time.
  With the optimiser on, the three tests become `sltu` results kept in saved registers, the frame doubles and
  the body is 12 instructions shorter.
* The other spellings of the two instructions leave the optimiser on: an MWCC `asm { }` block and a plain
  `__asm__ ("sync")` both give the optimised shape.
* The keyword marks no datum, so there is no strip test of a load; what it changes is the compile of the
  function, and only it reproduces the retail code.

### enbaya-vu0-macro

The two key-blending functions of the Enbaya animation decoder in `src/engine/enbaya.cpp`, an MWCC file, each
hold one GCC-style `__asm__` statement of VU0 macro-mode code.

* The instructions are coprocessor-2 macro operations: `lqc2`/`sqc2`, `vaddax`/`vmaddi` blends, `vmul` and the
  `vadd` broadcasts of a squared length, `vrsqrt` and `vmulq`, with the I register loaded through `mfc1`, `nop`,
  `ctc2 $vi21`. No MWCC version in `local/mwcps2` emits a COP2 macro instruction from C: their 193 `__I_`
  instruction builtins stop at `cfc2`/`ctc2` with immediate operands, and a float multiply-add loop compiled
  under `#pragma opt_vectorize_loops on` gives none.
  CodeWarrior's *Targeting PlayStation 2* (R3.04) gives GCC-style inline assembly, with the `j` constraint for
  VU0 registers, as the way to write VU0 code, and states that its inline assembler has no intrinsic functions.
* The functions are C around the statement, not `asm` functions: one first toggles the slot byte at +169 and
  computes the two slot indices with the compiler's `sltu`, `xori`, `andi` form of `!` and a filled branch delay
  slot, and passes them in as operands; the other ends with the store that clears the slot byte, which the
  compiler moves into the `jr ra` delay slot.
* The statements read the arguments in their argument registers and use fixed scratch registers, as hand-written
  PS2 code does. The inline assembler works in reorder mode, so the loop branch is written last and the
  assembler fills its delay slot, as retail has it.

## Open questions

* **The stack slot `volatile` stands in for.** Some inlined list searches take a value that retail stores
  to the stack and reads back. Locals, structs, arrays,
  references and conversion temporaries all fold the slot away or load a wider value, so what keeps the
  slot in the original is not known.
