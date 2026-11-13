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
one on its own initiative or as part of a broader request. The owner's one standing instruction: a use a
Fable 5.2 check recommends approving with high confidence is written without a separate question, listed in
the report, and revocable by the owner. The table is one of the oracle's own files
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
by name, and the file-scope declarations it reaches, in the file and in the project headers it includes:
a header's helpers, macros and declarations reach a function the same way the file's own do, so a function
answers for a header's `asm` or `volatile` only when it uses the helper, macro or declaration holding it. A file-scope
declaration is reached when the function or one of those helpers names something it declares, directly or
through another declaration it reaches; C keywords are not names, but a type name is. So a `volatile` global
reaches the functions that use it, and a struct member declared `volatile` reaches the functions that name
the struct or a type built on it. A whole-file source declares its module's words once, and each function
answers only for the ones it touches. The count voids an approval when another use appears, which files the
function as `unapproved` again. A header statement is approved once every function reaching it has its row.
A call of one of MWCC's `__I_<mnemonic>` instruction builtins (`__I_mfc0(3, 12)`,
`__I_nop()`) emits the instruction it names from C, so it counts as an `asm` use.

Three things need no row:

* `sync` and `ei`, which C cannot spell, alone or as a statement holding nothing else. The debt ratchet still counts them.
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

On an `asm` statement the qualifier means something else: the statement is not deleted, moved or combined. A
statement with no output operand has that property already, so its `volatile` can do nothing, and one with outputs
is often inert too. Test it the same way: strip it and verify. An inert one is removed, even where an upstream text
writes it (Sony's `graphdev.c`, `libtimer.c` and `eekernel.h` do), and the row loses it. One kept must change the
bytes when stripped. Stripping a needed one usually gives the same instructions in another order, a statement
hoisted above the register saves or moved into a delay slot; that is approved only with the upstream text or
hardware evidence for the statement itself, as for Sony's `mfc0 %0, $12` Status reads. Try first the operand form
the upstream text uses: a store written with its word as an output (`"=m"`) can be moved and needs the keyword, while
Sony's `: : "m"(word)` input form is fixed already. An inline helper the upstream header supplies is used from a
project header holding its exact text, and its `volatile` counts there.

The `lui`, `addiu`, `lw 0` address form is not evidence for a `volatile` global by itself under GCC: functions that
match without one have it too, nearly always because the address register has a second use. Under ee-gcc 2.96 a
single-use access in that form, with no call or block boundary before it, has no plain spelling that has been found.
That points to a `volatile`-qualified access, not to state shared between contexts, so it does not make a case alone.

The form comes from the combiner. The address is expanded as a high part and a low part, and the combiner folds
the low part into the access, except in three cases: the access is `volatile` (it recognises no instruction with a
volatile memory operand), the address is computed in another basic block than the access, or the address register
is used a second time. Each plain spelling of the last two leaves the branch, the load or the second access in
the function, so a single-use access in this form with nothing of the kind around it was compiled as `volatile`,
through the object's declaration or through a cast on that one access: the two give the same bytes. The
compiler's `-fvolatile`, `-fvolatile-global` and `-fvolatile-static` options change nothing here.

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
event callbacks, thread bodies, the idle-border switches and the shutdown functions.

* Retail keeps loads a plain spelling drops: a load right after the store with its result unused, or a second read
  with no call between. This holds for the create functions, the lock and unlock callbacks and the idle-thread
  wakeup, which come out shorter without the keyword.
* Four rows have a single read of the word and differ from a plain spelling only by the address form: the two
  idle-border switches and the two shutdown functions. They rest on the file-scope declaration the functions above
  prove.
* Three of the ids are also read by `adxm_exec_vint`, the vertical-blank interrupt path, which is the reader in
  another context.

### svm-lock-counts

The SVM lock's nesting count (`0x4baff8`) and type (`0x4baffc`) are globals changed around the lock and unlock
callbacks, in the lock (the function at `0x27e0d0`) and the unlock (the function at `0x27e130`).

* Retail reloads the count: the unlock stores it and immediately loads it back, which a plain spelling forwards from
  the register (8 bytes shorter stripped), and the lock loads it for the test and again for its increment, with
  only a store to the type word between.
* The unlock reads the type word twice with no call between; stripped, the reads merge (4 bytes shorter).

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
* The create count (`0x4a92e8`) is touched only by its own increment in the function at `0x271670`, and its keyword changes only
  how a delay slot is filled. That function has no row (see [Open questions](#open-questions)).

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
  the timer functions touches them.
* The saved clock (`0x5856c0`) and the pointee qualifier of the clock pointer lose no access when stripped: the
  first only reorders the stores of the clock copy, the second drops one duplicated `addiu`. Neither is an
  independent pin. The pointee qualifier follows from the clock's own: the pointer is assigned the clock's address,
  and without the qualifier ee-gcc warns that each of the three assignments discards it. The saved clock is the
  word a nested call reads: the timer read's other path runs only when it is entered again between its increment
  and decrement of the nesting count, and then reads through the pointer the outer call has aimed at the saved
  copy. So the timer init (the function at `0x2b5848`), the timer read (the function at `0x2b5a10`) and the tick
  (the function at `0x2b59a0`) have rows. No interrupt-context caller is shown; the nested entry is read from the
  code's shape.

### mwsfd-handle-used

The MWSFD player handle's in-use word, which the server pass reads (`mwPlyExecSvrHndl`) while the application side
clears it when it destroys a player (`mwsfcre_DestroyPly`). The server pass runs as an SVM server callback, and the
read is the server half of the destroy handshake, so it reads the word where the other side's change must be seen.
Written as a `volatile` cast at the read, as the DMA channels' shared words are ([dma-channel-shared-words](#dma-channel-shared-words)). The
keyword keeps no extra load (stripped, the read moves into a branch delay slot), so the row rests on the shared
state alone.

### build-string-stores

A module's init stores the address of its version string in a word that nothing else reads or points to, in the
`lui`, `addiu`, `0(reg)` form, ahead of the code a plain spelling would let it sink into. Four inits do it: ADXT
(`0x56dfa8`), SUD (`0x5856a8`), SFX (`0x5856a0`) and CFT (`0x573ea8`). In each the store is the word's only access in
the executable, and stripping changes only the address form and where the store sits, never whether it happens.
These inits have no row (see [Open questions](#open-questions)).

### adxt-ready-count

ADXT's tick count at `0x49c8f0`, which some ADXT files declare `volatile` and others plain.

* ADXT's init clears it, the server entry and `adxm_exec_vint` increment it, and the handle code copies it into a
  handle as a start time. `adxm_exec_vint` is the vertical-blank interrupt path, reached from `ADXM_ExecVint`
  (registered through `AddIntcHandler`), and needs the keyword itself: stripped, it comes out 8 bytes short.
* The same statement, a handle's start time set from the count, compiles in the `lui`, `addiu`, `0(reg)` form
  in one ADXT file and folded into `%lo` in another, which one declaration cannot give. `adxtinit.c` declares the
  word plain and qualifies only the init's store with a cast; the server entry needs no keyword. `adxtsvr.c`
  redeclares the word `volatile` after the shared header's plain declaration, which ee-gcc accepts, so the
  functions after it keep the unfolded form `adxt_stat_prep` has: there combine folds the low part into the
  load for any plain spelling, and the registers rule out taking the address earlier.
* No matched function re-reads the word; each keyword decides the address form only. The second build is the
  Street Fighter III: 3rd Strike decompilation (CRI ADX built Sep 2003), which declares the count `volatile` in the
  same files and plain in another, and in `adxtinit` also declares the build string `volatile` and reads it once,
  the [build-string read](#build-string-reads) mechanism. On that, the owner approved the init's two keywords (the
  count and its build-string word `0x56dfa8`) and `adxt_stat_prep`'s one.

### adx-server-guards

Entry guards of ADX servers that run on one thread and are waited on or entered from another.

* ADXSTM's server busy word (`0x4a7f00`) is taken through `SVM_TestAndSet` on the file-system thread and polled in
  `ADXSTM_OpenFile`'s wait loop on the main thread. The keyword is on the server's clearing store: stripped, the
  function is 4 bytes short. The 3rd Strike decompilation declares the same word `volatile`.
* ADXT's server phase word is the entry guard of `ADXT_ExecServer`, which runs on the V-sync server thread and on
  the main thread (through `ADXT_DiscardSmpl`). Only the last store's keyword matters, and stripped it changes one
  delay slot (`beq` with a `nop` against `beql` with the store); every access is under `ADXCRS_Lock`, so this row
  rests on the two threads alone.

### build-string-reads

A function reads a word holding the address of a build string, such as `"\nSRD/PS2EE Ver.2.22 Build:..."`, and never uses
the value.

* Each word is declared `char *volatile`, since it holds the string's address.
* This is not shared state. The evidence is the mechanism: the word is the string's only reference, none of the GCC
  functions that match with no keyword has a load whose result goes unused, and every plain spelling tried drops it.
* That the source reads the word to keep the string linked is inference. The owner accepted these on that basis.
* ADXF 7.18 is in the PS2, GameCube and Xbox builds, and each performs the same discarded read of its build-string
  word. Compiled with a probe, only `const volatile` fits all three, by the read and by the section the word sits in:

  | declaration | ee-gcc 2.96 | MWCC GameCube 2.0 | MSVC 13.10 (Xbox) |
  |---|---|---|---|
  | plain | no read, `.data` | no read, `.data` | no read, `_DATA` |
  | `volatile` | read, `.data` | read, `.data` | read, `_DATA` |
  | `const` | no read, `.rdata` | no read, `.rodata` | no read, `CONST` |
  | `const volatile` | read, `.data` | read, `.rodata` | read, `CONST` |
  | retail | read, `.data` | read, `.rodata` (after its string) | read, `.rdata` (before its string) |

  The source keeps the `char *volatile` spelling of the other CRI files.

### metrowerks-runtime-asm-functions

`__ptmf_scall`, `__TransferControl` and `__throw`, from the Metrowerks C++ runtime: `src/runtime/__ptmf.c` and
`src/runtime/ExceptionHandlerTS.cpp`.

* Metrowerks' own runtime source, shipped with CodeWarrior for PlayStation 2 R3.04, writes all three as MWCC `asm`
  functions: the pointer-to-member call in `__ptmf.c`, the restore of a catcher's registers and the capture of a
  thrower's in `ExceptionHandlerTS.cp`. The executable's instructions follow that source one for one.
* The sources here are written from the runtime's data layouts (`PTMF`, `ThrowContext`) and its instructions,
  with no comments or other text of Metrowerks' copied. `__TransferControl` starts with `.set reorder`, as the
  original does, so the assembler moves the final stack adjustment into the jump's delay slot.
* `__throw` copies `sp` with `qmove` (the original's register-copy macro on a 128-bit CPU), which assembles to
  `paddub`; under `.set reorder` the last copy lands in the delay slot of the call to `__ThrowHandler`. The
  function is 124 bytes; the word after it is alignment before the next function.
* No C can write any of them: one takes its argument in `t9` and leaves through a jump on it, and the other two
  read or load another frame's registers: one captures its caller's `sp`, `ra` and saved registers before any
  prologue and never returns, the other returns into another frame.

### sony-libkernl-cop0-and-syscall

Sony libkernl functions written in C with instructions C has no spelling for: reads and writes of COP0 registers
(`mfc0`, `mtc0`), `cache` operations, `di`, `sync.p`, and system calls made from inside a C file.

* Sony's own build shows they are C: each sits in an SDK 3.0.3 `libkernl.a` member (`wise2/b03476.a`) that carries
  the compiler's markers and records a `.c` source, and the cache, interrupt, `diei`, thread, glue, heap and TLB
  functions are byte-identical to those members (`cache.o`, `intr.o`, `diei.o`, `thread.o`, `glue.o`, `tlbfunc.o`,
  `sifcmd.o`) with relocated words masked. The SDK match table records `_sceIDC` and `_sceSDC` as 160 bytes against
  retail's 164 only because its size stops before the final `jr`'s delay slot.
* Sony's source text exists for part of it. `delaythread.c` (SDK 3.0.3 source text `r03287`) is `DelayThread`
  statement for statement, including `__asm__ volatile("mfc0 %0, $12" : "=r"(status))`. `eekernel.h` (`r03616`)
  holds the `DI()` and `EI()` macros `sbrk` uses; `include/dw4/eekernel_intr.h` carries that text exactly.
* The system calls in these files are local functions of C members, not part of the assembled stub file. The
  `.mdebug` procedure records of SDK `alarm.o`, `tlbfunc.o` and `initsys.o` give `setup`, `Copy`, `GetEntryAddress`,
  `FindAddress` and `_SetTLBEntry` frame register 29 and return register 31, as for their C neighbours, while the
  stubs of `klib.o` have 0 and 0 and carry line numbers. In retail each sits among its member's functions in that
  member's order. So each is a C function holding one `syscall`.
* `di` appears in `sbrk`, through `DI()`, and in `DIntr`, whose loop holds `DI()`'s three instructions as one
  statement; the cache and interrupt functions disable interrupts by calling `DIntr`.
* A `volatile` in a function's own text stays only where stripping it changes the bytes: on the nine
  `mfc0 %0, $12` Status reads, which it keeps below the register saves and out of a delay slot. `sbrk` also counts
  the five of `DI()` and `EI()`, which `eekernel_intr.h` carries as Sony's header text (only the loop's `mfc0` one
  changes the bytes). The others (the syscall locals, the `mtc0` and `cache` statements, `sync`, `ei` and the
  write-back block) were inert and are left out.
* One TLB function keeps a counter in a fixed register across calls, which only a register variable gives.
* The SIF's data-cache write-back is one `asm` block: a loop of `cache 0x18` with `sync`, carrying its own return. It
  sets `.set noreorder` and leaves it on, so the compiler's closing `jr ra` gets no delay-slot `nop`, as in Sony's
  member and the executable.

### sony-gp-and-syscall-asm

Sony library functions in C that read, store or swap `$gp`, make a system call, or read the hardware timer through an
inline `asm` statement: the callback and handler registration of libmpeg, libcdvd, libkernl's SIF and timer code, two
thread calls and `GetTimerSystemTime`.

* Sony's own build shows they are C: each sits in an SDK 3.0.3 member that carries the compiler's markers and records
  a `.c` source, and eleven are byte-identical to that member with relocated words masked. The exception is
  the function at `0x10ef70`, whose member (`filestub.o` `scePowerOffHandler`) is a version four bytes shorter, with the same `$gp`
  store.
* Sony's source text exists. `eekernel.h` (SDK 3.0.3 source text `r03616`) writes `GetGp()` and `SetGp()` as
  `__asm__ volatile` with a `"memory"` clobber; `include/dw4/eekernel_gp.h` carries that text exactly and the six
  functions reading or swapping `$gp` use it. `libtimer.c` (`r03285`) writes the `$gp` store as
  `__asm__ volatile("sw $28, %0\n" : : "m"(pCounter->gp_value) : "memory")`, and its `ReferHardCounter` block is
  `GetTimerSystemTime`'s statement: two timer-register reads, the overflow count and the prescale shift.
* C reaches neither `$gp`, a system call nor that timer sequence. A handler registered for another context records the
  caller's `$gp`, and a callback runs on the `$gp` its owner supplied.
* The `sw $28` stores are written in Sony's input form, `: : "m"(word)`, which has no output and needs no `volatile`.
  The keyword on `GetTimerSystemTime`'s block and on the thread calls' inline syscall was inert and is left out; the
  thread calls carry a `"memory"` clobber, as every asm helper in Sony's `eekernel.h` does, which orders their two
  prologue saves. The `volatile` rows left are those of `eekernel_gp.h`'s `GetGp()` and `SetGp()`, counted against
  each function that reaches them.
* A `"memory"` clobber is what makes the values around a swap reload, as retail does: `_request_end` and
  `sceSifExecNotifyHandler` mismatch without it, and `sceSifAddCmdHandler`'s read needs it. `sceSdRemote`'s swap
  matches either way.
* libmpeg's callback dispatch swaps `$gp` with the header's `SetGp()` and restores it with one `move $28, %0`. SDK
  3.0.3's `mpeg.o` is this function with `SetGp()` for both and is one `move v0,gp` longer than DW4's 2.8.0. Sony's
  `tracert.c`, `ping.c` and `iopgcovout.c` write the one-move restore as `asm volatile ("move $gp,%0" : : "r" (gp) :
  "memory")`; its keyword and clobber are inert here and left out.

### sony-interrupt-shared-state

Sony library state shared between interrupt-time code and thread code. These rows also count register and
`__asm__ volatile` keywords, which rest on #sony-hardware-registers.

* `VSync2` passes its flag and time block to the EE kernel through `SetVSyncFlag` (syscall 115), as one `volatile`
  struct. The kernel's vertical-blank interrupt writes the block; no handler in the executable does. Retail reloads
  `flag` in a call-free poll loop, and the keyword gives that reload. `time` is read once: its keyword only keeps that
  load out of a branch delay slot, and no plain spelling of it alone matches; one qualified block gives both.
* `_ch3dmaCSC` is itself the channel-3 DMA handler. The waiter is the function at `0x1087a8`, which keeps the state on its stack,
  registers `_ch3dmaCSC` for channel 3 and polls `count` in a call-free loop. Retail loads `count` four times in the
  handler, and the keyword gives those reloads.
* `tty.c` keeps the DECI2 console's state in one block, `TtyInfo`, shared between the protocol handler
  (`sceTtyHandler`, registered through `sceDeci2Open`) and the callers that write and read. Sony's own DECI2
  protocol-driver samples in SDK 3.0.3 (`r04466:19-26`, `r04455:18-25`) declare the same block, `volatile int s;
  volatile u_int wlen; volatile u_int rlen; … volatile int rbytes;`, and use the same statements, including the
  empty wait loop. Stripping each keyword: `wlen` lets the handler merge two loads with no call between and
  narrow a `lw`+`andi` to `lhu`; `rlen` forwards the handler's second load from a register; `s` drops
  `sceTtyInit`'s store-and-load-back; the queue's `count` loses its reload in `sceTtyRead`'s empty poll loop, and
  `QueuePeekWriteDone`, called from the handler, raises it. `writing`, the busy flag the handler clears while
  `sceTtyWrite` polls it, only reorders stores. Each function reaching the block counts all five keywords; the
  three queue helpers count the queue's one.

### adxm-thread-flags

The ADX manager's server threads and its border wait. Each server thread loops until a 64-bit exit request is set,
then records that it has exited, and the border wait spins on a flag the server thread clears. Other threads set
the requests and wait on the exit words, so the state really is shared between threads.

* The rows also cover the border flag (set by the border wait, cleared by the idle threads), the MW-idle thread's
  slept flag (set by that thread, read and cleared by the V-sync thread), the V-sync waiting flag (set by
  `ADXM_WaitVsync`, read and cleared by the V-sync thread), the busy flags `adxm_usrvsync_busy`, `adxm_fs_busy` and
  `adxm_vsync_busy` (read by `adxm_exec_vint`, the vertical-blank interrupt path), and thread-id words whose
  evidence is under [ADXM thread ids](#adxm-thread-ids).
* The loops contain calls, so they reload the flags with or without the keyword, and the strip test loses no load.
  It does not leave the functions unchanged: stripping an exit request or exited word shortens the thread bodies,
  `adxm_request_thrd_exit` and the delete functions by 4 to 20 bytes, through the address form and hoisting. The case
  rests on the shared state, approved on that basis.
* Retail reads every one of these words through a full address in a register. Under ee-gcc 2.96 a single plain access
  is never written that way, which supports a `volatile`-qualified access in the source.
* One server thread also writes the GS background colour register at its fixed address, a hardware access.
* `adxm_exec_vint` is that interrupt path, registered through `AddIntcHandler` behind its wrapper `ADXM_ExecVint`.
  It reads the three busy flags and three thread ids, increments ADXT's tick count
  ([adxt-ready-count](#adxt-ready-count)) and guards itself with a re-entry flag. Each of its eight keywords is
  needed: stripped, it comes out 8 bytes short. The busy flags are single reads in the full-address form, beside a
  plain read of the set-up count folded into `%lo` in the same function.
* The server thread bodies (`adxm_vsync_thrd`, `adxm_fs_thrd`, `adxm_usridle_thrd`, `adxm_mwidle_thrd`,
  `adxm_usrvsync_thrd`) have no row: each also reaches its tick count, and the MW-idle and user-idle bodies their
  busy flags, which only their own thread touches and whose keywords only reorder a store (see
  [Open questions](#open-questions)).

### sony-hardware-registers

Accesses to EE and GS registers in Sony's libraries, and in the CRI code that drives the same registers. Each
keyword is on a fixed register address, or for the DMA channels on a register reached through a channel pointer.
The `sync` and `ei` statements in these functions are written without the qualifier, which changes no bytes there,
although SDK 3.0.3 `eekernel.h` writes `EI()` as `__asm__ volatile("ei")`, by the rule in "Testing a `volatile`".

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
  the 64-bit read of IPU_TOP, which the header declares as 32 bits. A cast to the wider type, which that read needs,
  drops the qualifier and matches retail. The 64-bit IPU_CMD reads in the function at `0x106660` and the function at `0x1067e8` keep the
  qualifier, which retail needs; the header has no macro for that read.
* The serial port registers and the interrupt status register I_STAT at `0x1000F000` are absent from the header and
  identified from the open-source ps2sdk.

DW4's libraries are SDK release 2.8.0, which is not available, so the text compared is from a later release.

### sony-alarm-id

The timer alarm functions declare the id member of their alarm record `volatile`.

* Retail's functions are libkernl's copies, `timeralarm.o` (`timeralarm.c`) in `libkernl.a`, driving Timer 2. That
  source is not in the SDK. Its sibling, the Timer Library's `alarm.c` in SDK 3.0.3 (`libtimer.a`, Timer 1), declares
  that member `volatile`. Its function bodies, given only retail's symbol names and the libkernl constants, compile to
  retail's bytes for all of these functions, and to different bytes once the qualifier is removed.
* The functions are also byte-identical to the `libkernl.a` member in the SDK's archives.

### sony-timer-state

The timer functions declare `volatile` the members of the timer state and counter records that its interrupt handler
also uses.

* Retail's functions are libkernl's copies, `timer.o` (`timer.c`) in `libkernl.a`, driving Timer 2. That source is
  not in the SDK. Its sibling, the Timer Library's `libtimer.c` in SDK 3.0.3 (`libtimer.a`, Timer 1, source text
  `r03285`), declares those members `volatile`, among them `volatile int cbcounterid`, the `current` member
  `iSetTimerHandler` reads. Its function bodies, given only retail's symbol names, the libkernl constants and retail's
  helpers for the timer registers, compile to retail's bytes for these functions, and to different bytes once the
  qualifiers are removed.
* The functions are also byte-identical to the `libkernl.a` member in the SDK's archives.
* The functions that program Timer 2 itself (its start-up, the pre-scale read and the compare update) also reach
  the `T2_COUNT` and `T2_MODE` register macros, `volatile` as in Sony's `eeregs.h` (`r03615:2811-2812`); their rows
  cite this anchor and count those keywords with the members.

### sony-vu-and-gp-asm

`sceGsResetPath` and `sceSdRemote` hold statements C has no spelling for.

* Sony's `libgraph` source in SDK 3.0.3 (`graphdev.c`, source text `r03376`) writes `sceGsResetPath`'s statements
  as `__asm__`: it orders the VIF1 reset with `sync.l`, then sets a bit of VU control register `$vi28` with `cfc2`,
  `ori`, `ctc2` and `sync.p`. Its `libsdr` source (`sdr_main.c`, `r03289`) holds no `__asm__`: `sceSdRemote` calls
  `GetGp()` to record `$gp` beside a registered handler and `SetGp()` to swap it around an RPC call that has an end
  function, and those statements are `eekernel.h`'s (`r03616`), carried exactly by `include/dw4/eekernel_gp.h`.
* Compiled from Sony's text, with the header's `GetGp`/`SetGp` and only retail symbols and constants mapped, both
  functions are byte-identical to retail. `sceGsResetPath` needs the assembler of its [compiler note](sd-prologue.md).
* C reaches neither a VU control register nor a move of `$gp`.
* `sceSdRemote`'s two `volatile` keywords are the header's. Neither can go: without the one on the read the registers
  differ, and without the one on the swap the function comes out 164 bytes short. `sceGsResetPath`'s statements have
  no outputs, so its `__volatile__` changes nothing and is left out, by the rule in "Testing a `volatile`".

### dma-channel-cop0

The engine's DMA channel queues in `src/engine/dmaChannel.c`, an MWCC file. Two functions read the COP0 Status
register before taking a node from a shared pool, and one waits on the COP0 condition.

* A COP0 register read has no C spelling except MWCC's `__I_` instruction builtins: `__I_mfc0(3, 12);
  __I_srl(6, 3, 16); status = __I_and(3, 3, 6);` matches too, and counts as `asm` here, as each builtin emits the
  instruction it names. No builtin spells a branch on the COP0 condition (`bc0f`).
* Both pool functions test the interrupt-enable bits (IE and EIE, bits 0 and 16) together, and disable interrupts
  around the pool update only when both are set. In every MWCC copy of this test in the executable, five
  functions in all, the shift goes into `a2` and the `and` writes back into whichever register the read used.
  The compiler picks that register and never picks `a2` by itself, so the shift and the `and` were text of the
  statement, with `a2` named and clobbered: `mfc0 %0,$12; srl $6,%0,16; and %0,%0,$6`. Reading the register alone
  and testing it in C gives the same instructions with other registers. The builtin form names the read's
  register by number, which explains the varying register of the five copies less well than `%0` does.
* The statement is written without `volatile`: both functions match with or without it, so the keyword went.
* The wait is five `nop`s, a `bc0f` back to its start and a `nop`, then a return with no frame: 36 bytes, the only
  `bc0f` in the executable. It is a `static` C function holding one `asm { }` block. Its only caller,
  `p2StoreImage`, keeps `a0` and `a1` live across its three calls to it; measured on a test caller, any `static`
  callee defined earlier whose body holds inline assembly gives that (an `asm` function, a C function with an
  `asm { }` block or an `__asm__` statement), while an `extern` callee makes the caller save `s0`-`s2`. Nothing
  shows the original wrote a whole `asm` function, so it is C with an `asm` row.

### dma-channel-shared-words

Words of the engine's DMA channel and frame code that thread code and an interrupt handler or another thread
both write: the two flag words at `0x56d670` and `0x56d678` (the three DMAC handlers, `p2StartDmaPacket`, the
three waits and the watchdog), the frame count at `0x56bf70` (`p2VsyncHandler`, reached from the GS interrupt
handler) and the watchdog's tick counter at `0x56d680` (`p2RunWatchdog` and `p2SubmitDmaPacket`). With them, the
semaphore ids at `0x569030`, `0x56bf90` and `0x56bf80`, which are written only at init (`p2InitDmaChannels`,
`p2InitSwap`): nothing writes them concurrently, so their keywords rest on the reload alone, retail loading each
twice back to back where a plain read loads it once.

Each file declares each of these words once, `volatile`, at file scope, so every function naming one counts it:
`p2InitSwap` (the two ids it creates and the frame count it zeroes), `swapbuffersPredicate` (the frame count),
`p2GsSignalHandler` (the finish semaphore id) and `p2PrintWatchdogReport` (the flag words). Their keywords do no
work there; the files match with every declaration `volatile`.

* The handler is registered with `AddDmacHandler` and ends with `sync` and `ei`. It clears a bit in both flag
  words, while thread code sets and clears another bit in them between disabling and enabling interrupts.
* Thread code clears its bit in the first word and then in the second, and retail stores the first before it
  loads the second. Through a plain array, a struct or two separate words the compiler knows the two cannot
  overlap and loads the second word first; only a `volatile` declaration keeps the order, which the interrupt
  sharing makes the source's own.
* `p2WaitDmaSequence` reads the semaphore id twice, once to record it and once to wait on it, with no write
  between; retail loads it twice, and with both reads plain they merge (356 bytes against 364). It spells the
  qualifier as a `*(volatile int *)` cast on the read it passes to `WaitSema`, where the other two waits use the
  declaration; one cast is enough, and either one alone keeps the load. `p2DmaWaitSema` is declared plain in
  its file; a `volatile` declaration there matches as well.
* The handler's two uses are the same flag words, declared `volatile` in its file.
* The frame-wait function that sets and clears another bit in the flag words also waits on a semaphore at
  `0x56bf90`, read twice as above (without the keyword it loses a load), and polls a 64-bit count at
  `0x56bf70` until it passes a target. A GS interrupt handler, registered with `AddIntcHandler`, advances that
  count. The loop calls a function, so it reloads with or without the keyword; the keyword keeps the order of
  the accesses, and the interrupt writer makes it the source's own.
* The finish-sequence wait sets and clears its own bit in the flag words the same way and waits on the finish
  semaphore at `0x56bf80`, whose id it reads twice (to record it and to wait on it); the GS SIGNAL handler
  signals that semaphore. Without the keyword the two reads merge.
* A watchdog thread, created from a thread parameter block at `0x4965d0` (entry `0x20e6a0` at `0x4965d4`, a 4 KB
  stack at `0x56c670`, `gp` `0x55c870`, priority 1), copies the first flag word into the second on each tick and
  aborts if the bits it copied last time are still set: the DMA handler clears them when the work completes. It
  reads the second word twice, and retail loads it twice. It also counts ticks at `0x56d680` and aborts after 60;
  one store in `p2SubmitDmaPacket` (`0x1ef050`, called from 40 sites in 32 functions, on other threads) resets
  the counter, and the watchdog polls it in its loop, where the keyword keeps the order of its accesses.

### dma-packet-kick

`p2StartDmaPacket` in `src/engine/dmaChannel.c` starts a channel's packet: it writes QWC, TADR and CHCR, then
branches to the function's end. Retail has `sw CHCR; b; nop` in the VIF0 and VIF1 cases.

* MWCC's delay-slot filler (traced in the compiler, `0x4c7690`) takes the first instruction before a branch that
  nothing later in the block depends on; in these cases that is the CHCR store, so plain C gives `b; sw CHCR`.
  The store stays put only when a later instruction in the block pins it, and the only one that leaves retail's
  bytes is a `nop`, which the filler then takes into the slot itself. An `__asm__("nop")` after each CHCR store
  is that instruction. Without one of them the function is 4 bytes short, without both 8.
* No C form has been found for the `nop`: `return` for `break`, a label, `goto` to the end, an empty `__asm__("")`
  or `asm { }`, `do { } while (0)`, a redundant `if`, `continue` in a wrapping loop, a direct `*D0_CHCR = 389` and
  `volatile` register pointers all give the 8-byte-short function. Only `__I_nop()` matches, and as an instruction
  builtin it counts as `asm`.
* The GIF case writes CHCR the same way and calls the same timer as the VIF1 case; it differs only in being the
  last case, which falls through to the end with no branch, so there is no delay slot after its store and no
  `nop` (a third one makes the function 4 bytes longer). What retail shows is a `nop` exactly where a branch
  follows the store, which an unfilled delay slot of unknown cause would also look like.
* The `sync` before the switch is written `__asm__ volatile`. Without the keyword, or as `asm { sync }`, the
  function is the same size with `li v1,389` loaded once before the switch. The match needs the keyword and the
  stores written `v = 389; *Dn_CHCR = v;` together: with the keyword and `*Dn_CHCR = 389;` the load is still
  hoisted. No pragma replaces the keyword (`opt_propagation`, `opt_common_subs`, `opt_loop_invariants`,
  `opt_dead_assignments`, `opt_lifetimes`, `opt_dead_code`, `global_optimizer`, `peephole` and `scheduling` off,
  `optimization_level` 0 to 3 all differ).
* The second counted keyword is the file's `volatile` declaration of the watchdog's flag word at `0x56d670`,
  where the busy bits it sets live ([dma-channel-shared-words](#dma-channel-shared-words)). It is inert in this
  function, which matches without it, and counts only because the function names the declaration.

### gs-interrupt-sync-ei

The GS interrupt handler in `src/engine/p2gs.c`, an MWCC file registered with `AddIntcHandler`, ends with `sync`
and `ei` in one `__asm__ __volatile__("sync\nei\n")`, the statement of ps2sdk's `ExitHandler()` macro
(`local/ps2sdk-ref/ee/kernel/include/kernel.h:29`, mirroring Sony's `eekernel.h`). A statement of only `sync` and `ei`
needs no `asm` row; the row is for its keyword.

* The upstream macro writes the statement and its one keyword.
* Retail has a branch for each status bit with the test recomputed from the saved status each time. With no
  keyword on either instruction, the three tests become `sltu` results kept in saved registers, the frame
  doubles and the body is 12 instructions shorter (352 bytes against 400). One keyword is enough: on either of
  two separate statements, or on the one statement, the function matches.
* No pragma gives the retail shape without the keyword: nine variants, all a different size.

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

* **Revoked CRI rows.** Eleven CRI functions match only with a `volatile` whose keyword keeps no memory access
  and guards no state another context touches. Their rows were revoked, and they stay `unapproved` until there is
  evidence that the original declared the words `volatile`, such as an upstream CRI source or a second build:
  * the ADXM server thread bodies `adxm_vsync_thrd`, `adxm_fs_thrd`, `adxm_usridle_thrd`, `adxm_mwidle_thrd` and
    `adxm_usrvsync_thrd`: the tick counts `0x49d9e8` to `0x49da08` and the busy flags `adxm_mwidle_busy` and
    `adxm_usridle_busy` are touched by their own thread only, and their keywords only reorder a store;
  * the function at `0x271670`, the SRD create count `0x4a92e8`: touched only by this increment; the keyword only leaves a
    delay slot unfilled;
  * the function at `0x273128`, a DTX word whose single store is its only access; the keyword moves it out of a
    call's delay slot;
  * the function at `0x2b50e8`, the function at `0x2b3788` and the function at `0x283058`, the build-string stores (`0x5856a8`,
    `0x5856a0`, `0x573ea8`): each store is its word's only access, and the keyword changes only its
    address form and position;
  * `CRICFG_Init`, its build-string word `0x56dfd0`: the same, and no other build can decide a store, as the
    GameCube and Xbox builds carry no CRI CFG string and their compilers emit the same store either way.

* **libcdvd's semaphore ids.** Two command pre-checks and `sceCdBreak` match only with a `volatile` on the command
  semaphore ids (`0x483568`, `0x48356c`), which keeps a load out of a call's delay slot and gains or loses no
  access; the ids are written only at start-up. A file-scope declaration cannot be what Sony wrote: SDK 3.0.3's
  `cdvd000.o`, one translation unit, reads the same words with the slot filled in some functions and empty in
  others, and declaring them `volatile` breaks the functions that fill it. Only a block-scope `extern volatile`
  reproduces both, so what made these functions see the words as `volatile` is not known, and they have no row.
  `sceCdBreak`'s other keyword, on the callback number (`0x483598`), which the CD interrupt callback writes, is
  genuinely shared, but cannot be approved apart from the first.

* **The stack slot `volatile` stands in for.** Some inlined list searches take a value that retail stores
  to the stack and reads back. Locals, structs, arrays,
  references and conversion temporaries all fold the slot away or load a wider value, so what keeps the
  slot in the original is not known.
