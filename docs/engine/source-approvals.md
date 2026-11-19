# Approved inline `asm` and `volatile`

An `asm` statement or a `volatile` passes the byte check whether or not plain C could produce the same
bytes, so either can force a match the original source did not have. A C or C++ function that uses one
counts as matched only once the project owner has approved that use. This is the same rule
[hand-written `.S` sources](assembly-sources.md) follow.

## The approval rule

Each approved use has a row in `config/source-approvals.tsv`: `kind` (`asm`, `volatile`, `asm-function` or
`local-decl`),
`symbol`, `count` and the anchor of its evidence below. An `asm-function` row approves a whole MWCC `asm`
function, one written in assembly in the original source; its count is 1. Without it, such a function is
an asm body ([asm-body matches](asm-body-matches.md)), which counts in no matched figure.

In a Sony EE GCC whole-file unit the same row approves a function written as a file-scope `__asm__("...");`
block: the block starts a line, sits in the unit's file in address order among its C functions, and defines
exactly one function (the `.globl` name its text also labels; a block defining none or several stops every tool
that reads `src/`). The unit keeps its compiler and flags. With the row the function counts like an approved MWCC
`asm` function, as `assembly` (matched, not C, readable once named); without it the function is `unapproved`
and its block counts in `inline_asm.other`. The owner approves these only for a function whose retail code
comes from a later build tool than the project's ee-gcc 2.96, proven against CRI's 2002 SDK object: the SDK object
is what the function's plain C compiles to under the unit's profile, and retail differs from it only in what the
tool chain does (delay-slot filling, alignment padding). The plain C stays beside the block in a comment, with the
measured difference ([sofdec-build-tool-asm-functions](#sofdec-build-tool-asm-functions)). Only the owner approves a row. An agent may write one only
when the owner has explicitly told it to add that function, after reviewing its evidence. It never adds
one on its own initiative or as part of a broader request. The table is one of the oracle's own files
(`.githooks/oracle-files.txt`).

### Kept local declarations

A symbol is declared once, in a header, and the header's form is what every includer sees
([declarations](debt-ratchet.md#declarations)). A few declarations stay in the unit that uses the symbol because
the header's form changes the unit's bytes. A `local-decl` row
approves them. Its `symbol` is the declared symbol, not a function, and its `count` is the number of local
declarations of that symbol outside its home that the owner approved, over the whole tree (a symbol kept in three
files has count 3). The approval holds only while the tree has exactly that many: another copy, or an approved
one removed, voids the row. `--stale` then reports it (`the row covers N, the source has M`, or `no local
declaration left`), and the copies count as declaration debt again. While it holds, the approved copies are not
`decl.local_externs`, are no `decl.varargs` or `decl.type_conflicts` debt (what the copy states differently from the
definition is the reason it is kept), and do not fail the readable `declarations` check of the functions that use the symbol;
`python3 tools/declarations.py --list local` still prints them, marked `[approved #anchor]`. Each row's anchor
below states the measured reason the header form is not an option. A row needs the owner's approval, like the
other kinds.

A function using either without a row is filed by `make check` as **`unapproved`**. Its source stays and
links byte-identically, and its code bytes count in the code-bytes-identical figure, but it is not
`match`, so it is in no matched figure and not in the readable count. A byte match is not approval.

```sh
python3 tools/sourceapprovals.py --list    # the functions awaiting approval, with what each one uses
python3 tools/sourceapprovals.py --stale   # rows that no longer describe their function or symbol
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

`__divdi3`, `__moddi3`, `__udivdi3`, `__umoddi3` and `__muldi3` reach one `multu` through `umul_ppmm` in
`include/dw4/support/libgcc_longlong.h`. `__muldi3` is the low-by-low product of gcc's `libgcc2.c` (`umul_ppmm` into a
double word plus the two cross products added to the high word); its retail code sits at `0x22e440`, the first
member of the libgcc region.

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
* Three of the ids are also read by `ADXPS2_ExecVint`, the vertical-blank interrupt path, which is the reader in
  another context.

### svm-lock-counts

The SVM lock's nesting count (`0x4baff8`) and type (`0x4baffc`) are globals changed around the lock and unlock
callbacks, in the lock (the function at `0x27e0d0`) and the unlock (the function at `0x27e130`).

* Retail reloads the count: the unlock stores it and immediately loads it back, which a plain spelling forwards from
  the register (8 bytes shorter stripped), and the lock loads it for the test and again for its increment, with
  only a store to the type word between.
* The unlock reads the type word twice with no call between; stripped, the reads merge (4 bytes shorter).
* The init count (`0x4baff4`) is `volatile` too: `SVM_Finish` stores it and loads it straight back, which a plain
  spelling forwards (84 bytes against 88). The 3rd Strike decompilation declares all three SVM words `volatile` and
  matches `SVM_Init` and `SVM_Finish` in C, and the GameCube build's SVM 1.54 reloads the same count in its finish
  where the plain init counts of the same library (the ADX and AXRNA shutdowns) do not. `SVM_Init`'s keyword rests on
  the declaration (stripped, four words differ in register choice only), and `SVM_GetLockType`'s single read of the
  type word on the declaration already approved above (through a plain cast it is 12 bytes against 16).

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
* The create count (`0x4a92e8`) is touched only by its own increment in the function at `0x271670`, and its keyword
  changes only how a delay slot is filled (stripped, that function is 128 bytes against 132). The owner approved
  the row on a second build: the 3rd Strike decompilation declares `Sint32 volatile srd_create_cnt`, with the
  destroy count plain, as here, and matches its `SRD_Create` in C. The source takes that build's statement order
  (`used`, `stat`, `mode`, `abort_request`, then the count); in it the function matches only with the keyword.

### sud-timer

CRI SUD's EE-timer words: the tick count (`0x4bf290`), the clock and its saved copy (`utytmr_main`, `utytmr_sub`), the
clock pointer (`utytmr_ptr`), the nesting count (`utytmr_lock`), and the two tables of timer-register addresses
(`utytmr_t_mode`, `utytmr_t_count`, retail `0x4f5a70` and `0x4f5a80`) whose targets are declared `volatile`.

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
clears it when it destroys a player (`mwSfdDestroy`). The server pass runs as an SVM server callback, and the
read is the server half of the destroy handshake, so it reads the word where the other side's change must be seen.
Written as a `volatile` cast at the read, as the DMA channels' shared words are ([dma-channel-shared-words](#dma-channel-shared-words)). The
keyword keeps no extra load (stripped, the read moves into a branch delay slot), so the row rests on the shared
state alone.

`mwPlyCreateSofdec` (`0x292ba8`) is the application side of the same word, approved by the owner on the evidence
below. Its search for a free entry reads each player's in-use word through the same cast, and its last statement
sets the word, which is what hands the player to the server: `mwsfsvr_ExecServer`, the SVM server callback, calls
`mwPlyExecSvrHndl` for all eight entries on every pass, and that function and `mwsfd_ExecSvrHndl` act on the word.
The writers are this function and `mwSfdDestroy`. Here the keyword changes more than a slot, and one keyword gives
all of it:

* Without it the search, `for (i = 0; i < 8; i++) { ply = &work->ply[i]; if (ply->used == 0) break; }`, compiles
  to the loop of the 2002 SDK's `mwsfdcre.o` (`libmwsfde.a`,
  [SkeletonPicture/recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)), constants apart: the
  work pointer copied to `v1`, a second strength-reduced pointer for `&ply->used` (`lw v0,0(a0)`), and the copy to
  the handle register in the loop branch's delay slot.
* With it the loop pass cannot rewrite the address inside the `volatile` load, so only the handle pointer is
  strength-reduced and the load stays `lw v0,4(s0)`; the work pointer is not needed past the first block; and the
  delay-slot pass takes nothing from above the first test across the `volatile` load, so the slot gets the copy of
  the branch target's `li v0,8` and the loop head its pad. Those are retail's 229 words.
* Plain C reaches the loop body (two handle variables, the first used again at the end of the function) but not
  the slot: the delay-slot pass then takes the count's `move a0,zero` from above the first test.

### mwsfsvr-vsync-count

MWSFD's second V-sync count (`0x4be8ac`), cleared by the player init and incremented by the V-sync server, which
`adxm_vsync_proc` runs and which MWPLY also exposes as its `VsyncHndl` slot ("called by user while v-sync
interrupt"). On PS2 the keyword only keeps one store out of a delay slot. The Xbox build's same function (`0x270550`)
compiles to its exact bytes under MSVC 7.1 only with this count `volatile` and the first count plain, the PS2
declarations; every other combination differs by 39 to 41 bytes. The owner approved the row on that second build.

### build-string-stores

A module's init stores the address of its version string in a word that nothing else reads or points to, in the
`lui`, `addiu`, `0(reg)` form, ahead of the code a plain spelling would let it sink into. Ten inits do it: ADXT
(`0x56dfa8`), SUD (`0x5856a8`), SFX (`0x5856a0`), CFT (`0x573ea8`), SFD (`0x580d58`), MPS (`0x573f08`), MPV
(`0x573f10`), M2V (`0x573eb0`), MWSFD (`0x577820`) and CFG (`0x56dfd0`). In each the store is the word's only access in the
executable, and stripping changes only the address form and where the store sits, never whether it happens. The
owner approved the stores in the CFG init and in the functions at `0x283058` (CFT), `0x2b3788` (SFX) and `0x2b50e8`
(SUD), the same kind of store as `ADXT_Init`'s approved `0x56dfa8` word, and later those of `SFD_Init`, `MPS_Init`,
`MPV_Init`, `M2V_Init` and `mwPlyInitSfdFx`, on the evidence below. The SDK's own `M2V_Init` (`m2v_lib.o`) stores its
`cri_verstr_ptr` in the same unfolded form.

* CRI's own 2002 SDK objects (`libmwsfde.a` in [SkeletonPicture/recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri))
  keep a file-local `.bss` word in sixteen files (`*_version_dummy`, `*_dummy`, `cri_verstr_ptr`), and each is stored
  in the same unfolded single-use form. Compiled with this project's ee-gcc 2.96, the SDK's `MPS_Init` (`mps_lib.o`)
  and `DCT_GetVerStr` (`dct_ver.o`, the same shape as DW4's: a constant string address, a lone store, a leaf) are
  reproduced byte for byte only by `static char *volatile`; plain C and five other spellings fold the address into
  `%lo`. The SDK is one build that matches the retail form; it does not decide every file, since its `CFT_Init`
  is also matched by a plain pointer local, and ee-gcc 2.96 drops the qualifier from its stabs.
* The declaration is `char *volatile` on the word, as for [build-string-reads](#build-string-reads).
* `mwPlyInitSfdFx` has two keywords: the version word `mwsfd_version_ptr` and `mwsfsvr_vsync_cnt2`, the V-sync
  count already approved under [mwsfsvr-vsync-count](#mwsfsvr-vsync-count); stripped, the function differs by 15
  and 10 words. The table holds one row per kind and function, so its row cites this anchor and counts both.

### sfd-play-pending

The SFD player's `pending` word (`+68`), a request flag. The API calls (`SFD_Start`, `SFD_Stop`, `SFD_Pause`,
`SFD_TermSupply`) set it on the game thread, and the per-handle execution step `sfply_ExecOne` clears it. That step
runs from `SFD_ExecOne` inside the MWSFD server pass, which the player registers as server callbacks that ADXM runs
on its own threads, so the word is written from two threads. The keyword is on the clearing store only: stripped, the
delay-slot filler moves the store into the call's delay slot where retail has a `nop`. The owner approved the row.

### sfd-time-counts

The SFD timer's stream position (`+680`), tick count (`+716`), decoded position (`+732`), external clock's last
reading (`+728`), rate (`+736`) and wrap value (`+740`), shared between the V-sync callback chain and the game thread. The V-sync server
reaches them through `sftim_HnVbIn`, which calls `sftim_CntupHnVbIn` (adds the step to both of the first two) and
`sftim_IsVbinStIncre` (reads the count); the timer adjustment at `0x2af488` changes both from the game thread,
between the library's lock and unlock calls, while the V-sync path writes them too. Stripped,
`sftim_IsVbinStIncre` differs by five words, the count update in `sftim_CntupHnVbIn` by one and either store in
the adjustment by nine. The stream position's store in `sftim_CntupHnVbIn` is plain: a `volatile` there changes
no byte, so only the count's cast stays. They are written as `volatile` casts at the access, so the other functions that touch the
words keep their plain accesses. The rows are approved under the owner's standing rule for words a vsync callback
and another thread share.

The decoded position, last reading and rate belong to the same rule through the external-clock getter. The V-sync
path is `mwsfsvr_VsyncProc`, `SFD_VsyncSvr`, the step at `0x2ae398`, `sftim_HnVbIn` and `sftim_UpdateTime`, which calls
`sftim_ResetVtimeTmr` (reads the decoded position) and `SFTIM_GetNowTime`; that one calls the getter in slot 5 of the
timer's table, `sftim_GetTimeExtClock`, which writes all three words. The game thread reaches the same getter from
`mwSfdGetTime`, `SFD_GetTime` and `SFTIM_GetTimeSub`, and from `SFD_UpdateTime`; the ADXM server thread reaches it
from `sfply_IsPlayTimeAutoStop`; and `sfply_ChkBpa` and `SFD_Pause` add to the decoded position through
the pause helpers at `0x2af428` and `0x2af4f0`. Five functions read or write the words:

* `SFTIM_InitHn` has six, the stores that set the count, the last reading, the decoded position, the rate and the
  external clock's wrap value (`+740`), and the read of the stream position back after its store. The wrap value
  is written by `SFD_SetExtClockFn` on the game thread (`0x2aee78` and `0x2aeec4`, and again from the reset after
  a stop at `0x2ac2a4`) and read by `sftim_GetTimeExtClock` (`0x2aebf8`), which adds it when the clock's delta goes
  negative, on the V-sync chain above. No second build has the field: the 2002 SDK's `sfd_tim.o` predates it (its
  `SFD_SetExtClockFn` takes no wrap and its timer ends at `+668`). DW4 never installs an external clock, the same
  limitation as the last reading, decoded position and rate. The callback context beside it (`+744`) is plain: a
  `volatile` there moves four words. Stripped of the wrap value's keyword, the function differs by five words.
* `sftim_ResetVtimeTmr` has two keywords, the stream position and the decoded position; stripped it comes out three
  words short.
* `sftim_GetVtimeTmr` has two, the decoded position and the rate in the branch that reads them; stripped it is one
  word short.
* `sftim_GetTimeExtClock` has four, the first read of the last reading, the decoded position's add and read and the
  rate's store; stripped it is one word short.
* `sftim_IsTakeOffExecTime` has one, the first read of the count; stripped it is two words short (the guarded load
  fills a delay slot that retail leaves a `nop`).

Each row cites this anchor and counts the keywords in its function.

### adxt-ready-count

ADXT's tick count at `0x49c8f0`, which some ADXT files declare `volatile` and others plain.

* ADXT's init clears it, the server entry and `ADXPS2_ExecVint` increment it, and the handle code copies it into a
  handle as a start time. `ADXPS2_ExecVint` is the vertical-blank interrupt path, reached from `ADXM_ExecVint`
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
  `ADXSTM_OpenCvfs`'s wait loop on the main thread. The keyword is on the server's clearing store: stripped, the
  function is 4 bytes short. The 3rd Strike decompilation declares the same word `volatile`.
* ADXT's server phase word is the entry guard of `ADXT_ExecServer`, which runs on the V-sync server thread and on
  the main thread (through `ADXT_DiscardSmpl`). Only the last store's keyword matters, and stripped it changes one
  delay slot (`beq` with a `nop` against `beql` with the store); every access is under `ADXCRS_Lock`, so this row
  rests on the two threads alone.
* `ADXT_IsActiveFsSvr` reads ADXT's file-system server step word (`0x49c8c0`), which is `ADXT_ExecFsSvr`'s re-entry
  guard, once. The server runs on the file-system thread (registered with the server manager as a server type) and
  the main thread enters it from the blocking stream calls (`ADXSTM_BindFile`, `ADXSTM_ReleaseFile`,
  `ADXSTM_Stop`) and from `ADXPS2_ExecServerEx`. The keyword, a cast at the read, decides only the address form
  (`lui; addiu; lw 0` against `lui; lw %lo`, 5 words against 4), which is the form a `volatile`-qualified access
  gives; fourteen plain spellings all give the folded form. No other build tells the two apart, and the 3rd Strike
  decompilation declares the word plain but leaves the function and its caller unwritten. The word is defined in the
  unit, with the cast kept at the read and no `volatile` declaration, which `ADXT_ExecFsSvr` would also reach.

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
* `mfCiGetInterface` reads the MFCI word and discards it in all three builds (GameCube from `.rodata` after its
  string, Xbox from `.rdata` before it), the ADXF pattern; stripped or `const`, the read goes. The owner approved
  its row on that. `cvFsInit` has the same PS2 shape and the GameCube and Xbox builds read the CVFS word only in
  `cvFsAddDev`, never in `cvFsInit`; CRI's own 2002 SDK object `cri_cvfs.o` (in the SDK archives of
  [SkeletonPicture/recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)) is the second build that
  reads the word inside `cvFsInit`: its `cvFsInit` equals DW4's apart from relocated fields (13 words differ, all
  immediates), including the discarded `lw` of `cvfs_build`. Plain, DW4's function is 180 bytes against retail's 196.
  The owner approved the row on that.
* `PS2RNA_Init` reads the word holding its version string (`ps2rna_ver_ptr`, `"PS2RNA Ver 1.30"`) as its first
  statement and `ADXM_SetupThrd` reads the word of its own (`adxps2_build`, `"ADXPS2 Ver.2.57 Build:..."`), and
  neither uses the value. Stripped or `const`, the read goes and the functions are 700 bytes against 716 and 392
  against 400; `const volatile` matches. The 3rd Strike decompilation builds the same functions with ee-gcc 2.96 (its
  ADXPS2 is 2.46 and its PS2RNA 1.22) and matches them in C with exactly this read: `Char8* volatile ps2rna_build`
  read as `*ps2rna_build;` first in its `PS2RNA_Init`, and `Char8* volatile adxps2_build` read as `adxps2_build;`
  first in its `ADXM_SetupThrd`. The GameCube build's counterpart of `ADXM_SetupThrd` starts with a discarded `lwz`
  of the word that follows its `"ADXGC Ver.1.21"` string, and its AXRNA init does the same with the `"AXRNA Ver.1.04"`
  word before its first-use block; the Xbox RNA init reads its word, which sits before its string, and discards it
  twice. The Xbox ADX manager has no build word at all (its string is read only by its version getter), which is an
  absence, not a read in another function. So the other builds put the read in the same function, the standard
  `mfCiGetInterface` met.
* `ADXM_SetupThrd`'s count of three is the build word and two declarations approved elsewhere: `adxm_vsync_waiting`
  ([adxm-thread-flags](#adxm-thread-flags); stripped, its store folds into `%lo` and moves into the delay slot) and
  `adxm_main_thid` ([adxm-thread-ids](#adxm-thread-ids); stripped, the load after the store is forwarded). The table
  holds one row per kind and function, so the row cites this anchor and counts all three.
* **A char array read.** `pl2enc_Init`, `pl2enc_Create` and `ADXPS2_SetupDvdFs` read a version string held as an array
  (`pl2enc_ver_str`, `adxrt_build`, `adxrt_build_ver`) with an expression statement that discards the value, declared
  `extern volatile char name[N];`. ee-gcc compiles a read of a `volatile` char array as `memcmp(x, x, n)`, comparing
  the array with itself, where `n` is the array's size in bits: 360 bits for the 45-byte `PL2ENC` string, and 128 and
  232 bits for the 16-byte and 29-byte `ADXRT` words. No other construct emits a `memcmp` of a buffer with itself.
  Stripped, the read goes: `pl2enc_Init` is 24 bytes against 60, `pl2enc_Create` 224 against 256 and
  `ADXPS2_SetupDvdFs` 208 against 256. The 3rd Strike decompilation writes the same reads in its `ADXPS2_SetupDvdFs`
  (`Char8 volatile adxps2_rt_ver0[12]` and so on). The owner approved the three rows; `ADXPS2_SetupDvdFs` counts
  two, one per array.
* `ADXM_SetupThrdEx` reads the same build word (`adxps2_build`) and sets `adxm_main_thid`, so its count of two is the
  build word and that declaration, approved under [adxm-thread-ids](#adxm-thread-ids). Its set-up count and
  thread parameters are plain.
* `SNDF_Init` reads `sndf_version`, the word holding `"SNDF Ver.2.09c"`'s address (its only reference), and never
  uses the value. Stripped, the read goes and the function is 376 bytes against 392. No other build has SNDF (not
  in the 2002 SDK archives or the Persona 4 tree), so the owner approved the row on the mechanism alone. Here the
  word is declared `char *const volatile`, the ADXF spelling: with `char *volatile` the read is kept but scheduled
  before `sceSifInitRpc`'s call instead of in its delay slot, and the first RPC client's address is formed late
  (nine words off).

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
  holds the `DI()` and `EI()` macros `sbrk` uses; `include/dw4/support/eekernel_intr.h` carries that text exactly.
* The system calls in these files are functions of C members, not part of the assembled stub file. The
  `.mdebug` procedure records of SDK `alarm.o`, `tlbfunc.o` and `initsys.o` give `setup`, `Copy`, `GetEntryAddress`,
  `FindAddress` and `_SetTLBEntry`, and `tlbfunc.o` also the eight global TLB calls listed below, frame register 29
  and return register 31, as for their C neighbours, while the stubs of `klib.o` have 0 and 0 and carry line
  numbers. In retail each sits among its member's functions in that member's order. So each is a C function holding
  one `syscall`.
* `di` appears in `sbrk`, through `DI()`, and in `DIntr`, whose loop holds `DI()`'s three instructions as one
  statement; the cache and interrupt functions disable interrupts by calling `DIntr`.
* A `volatile` in a function's own text stays only where stripping it changes the bytes: on the nine
  `mfc0 %0, $12` Status reads, which it keeps below the register saves and out of a delay slot. `sbrk` also counts
  the five of `DI()` and `EI()`, which `eekernel_intr.h` carries as Sony's header text (only the loop's `mfc0` one
  changes the bytes). The others (the syscall locals, the `mtc0` and `cache` statements, `sync`, `ei` and the
  write-back block) were inert and are left out.
* `SetT2` writes a timer-2 register, which user mode cannot reach: it reads Status, turns interrupts off in a `di`
  loop written as one statement (as in `DIntr`), sets EXL and ERL and keeps the old EIE, writes Status back, stores
  the value, then runs `mtc0 $31, $30; sync.p; eret` in one `.set noreorder` region, returning to its caller through
  ErrorEPC. The SDK 3.0.3 `timer.o` member is byte-identical to it. No C spells the COP0 accesses or `eret`. Of its
  five `asm` statements only two keep `volatile`: the `di` loop and the Status read with `sync.p`; stripped from
  the others, and from the store's cast, the bytes are unchanged. Without `.set noreorder`, `ee-as` moves `eret`
  into the delay slot of the closing `jr ra` (25 words against 28), and the `eekernel_intr.h` four-statement `DI()`
  gives one padding `nop` where retail has three.
* One TLB function keeps a counter in a fixed register across calls, which only a register variable gives.
* The SIF's data-cache write-back is one `asm` block: a loop of `cache 0x18` with `sync`, carrying its own return. It
  sets `.set noreorder` and leaves it on, so the compiler's closing `jr ra` gets no delay-slot `nop`, as in Sony's
  member and the executable.
* The eight TLB calls `PutTLBEntry`, `iPutTLBEntry`, `iSetTLBEntry`, `GetTLBEntry`, `iGetTLBEntry`, `ProbeTLBEntry`,
  `iProbeTLBEntry` and `ExpandScratchPad` are global functions of `tlbfunc.o` (frame register 29, return register 31,
  no line records), each one `li $3, N; syscall` with the compiler's `jr ra; nop`; the `klib.s` stubs have 0 and 0
  and line tables. Likewise `QueryIntrContext`, the first function of `intr.o`: `mfc0 Status; xori 1; jr ra; andi
  1`, with no `volatile` (it changes nothing).
* `src/sony/libkernl/kpatch/tlbsrc.c` is the kernel code `tlbfunc.c` copies to `0x80075000`, built from C and
  embedded in its `.data`. Its COP0 and TLB instructions (`tlbwi`, `tlbr`, `tlbp`, `mfc0`, `mtc0`) have no C spelling;
  of its `volatile`s only the ones that change the bytes when removed stay.

### sony-gp-and-syscall-asm

Sony library functions in C that read, store or swap `$gp`, make a system call, or read the hardware timer through an
inline `asm` statement: the callback and handler registration of libmpeg, libcdvd, libkernl's SIF and timer code, two
thread calls and `GetTimerSystemTime`.

* Sony's own build shows they are C: each sits in an SDK 3.0.3 member that carries the compiler's markers and records
  a `.c` source, and eleven are byte-identical to that member with relocated words masked. The exception is
  the function at `0x10ef70`, whose member (`filestub.o` `scePowerOffHandler`) is a version four bytes shorter, with the same `$gp`
  store.
* Sony's source text exists. `eekernel.h` (SDK 3.0.3 source text `r03616`) writes `GetGp()` and `SetGp()` as
  `__asm__ volatile` with a `"memory"` clobber; `include/dw4/support/eekernel_gp.h` carries that text exactly and the six
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
* `cbTimerHandler` holds two statements: `__asm__("lw $28, %0\n" : : "m"(alarm->gp) : "memory")`, which is
  `libtimer.c`'s statement (`r03285`) for loading the `$gp` an alarm was set with, and `__asm__("sync.l; ei")`,
  `ExitHandler()` of `eekernel.h` (`r03616:77`). Neither statement has an output, so the keyword Sony writes on both is
  inert (stripped, the file still matches) and is left out; `sync.l` encodes as `sync`.
* libcdvd's `_sceCd_cbLoop` and `_sceCd_Poff_Intr` swap `$gp` around the callback they call with one statement,
  `__asm__ volatile("move %0, $28\n\tlw $28, %1" : "=&r"(gp) : "m"(sceCdCb_Gp))`, and restore it with `move $28, %0`.
  `filestub`'s `_sceFs_Poff_Intr` has the same swap (with `"memory"`) and `sync.l; ei`. Sony's own IOP samples write
  the save-and-reload as one statement (`asm volatile ("move %0,$gp; la $gp,_gp" : "=r"(gp) : : "memory")` in
  `ping.c`, `tracert.c`, `mylib.c`). The header's `GetGp()` plus a separate load comes out four bytes longer in both
  functions (the `"memory"` clobber reloads the callback pointer), and `SetGp()` adds a word. Stripping the
  `volatile` or the clobber reorders the swap; `sync` and `ei` need no row. Retail's `_sceCd_Poff_Intr` and
  `_sceFs_Poff_Intr` share the shape `lui; move s0,gp; lw gp`.
* `iGetThreadId` is the inline `li v1,-47; syscall` of 3.0.3's `thread.o`, with no relocation to `GetThreadId`; calling
  `GetThreadId()` makes `iWakeupThread` 156 bytes against 148. `readSystemTime` is Sony's `ReferHardCounter` as
  `iGetTimerSystemTime` has it: the equivalent C is 88 bytes against 76.
* srcfile (the alarm kernel patch) holds four `$gp` statements: `move %0,$28` in `AddAlarm` and, in
  `kAlarmInterrupt`, `move %0,$28`, `move $28,%0` for the handler's `$gp` and the restore. C has no spelling for
  `$gp`, and a `register ... asm("$28")` variable is the same extension. The `volatile` on the two `move %0,$28`
  reads stays: stripped, `AddAlarm` changes 57 words and `kAlarmInterrupt` 110. `sync` and `ei` need no row.
* `sifcmd.c`'s `_sceSifCmdIntrHdlr` swaps `$gp` around each handler it dispatches with the header's `SetGp()`, and
  `sifrpc.c`'s `sceSifCallRpc` records the caller's `$gp` with `GetGp()`; both are byte-identical to SDK 3.0.3's
  members. The handler's second `volatile` is its `sceSifCmdHdr` pointer, which first reads the packet the IOP wrote
  into the receive buffer by DMA (`lbu` then `andi` for the size) and then the local copy, three reads of `cid`;
  stripped, the function is 79 words against 82.

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
* `_doCSC2` is the waiter of the channel-3 handler `_ch3dmaCSC`: its seven register keywords (`IPU_CTRL` twice,
  `D_STAT`, `D3_MADR`, `D3_QWC`, `D3_CHCR`, `IPU_CMD`) rest on #sony-hardware-registers, and the shared `count` it polls on the
  existing one.
* filestub's `_sceFs_q`, the table of calls made with `SCE_NOWAIT`, is freed by `_sceFs_Rcv_Intr` from interrupt
  context while the callers scan it for a free slot, and is `volatile` in Sony's source for that reason. Only a
  `volatile` first-slot load keeps `move a2,zero` out of the `bne` delay slot, as retail has it (the compiler's
  reorg treats a `volatile` reference as conflicting with everything); without it `sceLseek` and `sceLseek64` are
  143 words with 18 differing, `sceRead` 153 with 19 and `sceWrite` has 14 differing. No plain
  spelling gives that slot filling. The rows of `sceLseek`, `sceRead`, `sceWrite` and `sceLseek64` count the one use.

### adxm-thread-flags

The ADX manager's server threads and its border wait. Each server thread loops until a 64-bit exit request is set,
then records that it has exited, and the border wait spins on a flag the server thread clears. Other threads set
the requests and wait on the exit words, so the state really is shared between threads.

* The rows also cover the border flag (set by the border wait, cleared by the idle threads), the MW-idle thread's
  slept flag (set by that thread, read and cleared by the V-sync thread), the V-sync waiting flag (set by
  `ADXPS2_SleepMainThrd`, read and cleared by the V-sync thread), the busy flags `adxm_usrvsync_busy`, `adxm_fs_busy` and
  `adxm_vsync_busy` (read by `ADXPS2_ExecVint`, the vertical-blank interrupt path), and thread-id words whose
  evidence is under [ADXM thread ids](#adxm-thread-ids).
* The loops contain calls, so they reload the flags with or without the keyword, and the strip test loses no load.
  It does not leave the functions unchanged: stripping an exit request or exited word shortens the thread bodies,
  `adxm_ShutdownPreProcedure` and the delete functions by 4 to 20 bytes, through the address form and hoisting. The case
  rests on the shared state, approved on that basis.
* Retail reads every one of these words through a full address in a register. Under ee-gcc 2.96 a single plain access
  is never written that way, which supports a `volatile`-qualified access in the source.
* One server thread also writes the GS background colour register at its fixed address, a hardware access.
* `ADXPS2_ExecVint` is that interrupt path, registered through `AddIntcHandler` behind its wrapper `ADXM_ExecVint`.
  It reads the three busy flags and three thread ids, increments ADXT's tick count
  ([adxt-ready-count](#adxt-ready-count)) and guards itself with a re-entry flag. Each of its eight keywords is
  needed: stripped, it comes out 8 bytes short. The busy flags are single reads in the full-address form, beside a
  plain read of the set-up count folded into `%lo` in the same function.
* `adxm_vsync_proc` and `adxm_fs_proc` have rows on a second build: the 3rd Strike decompilation (ADXPS2 2.46)
  declares the V-sync, file-system and MW-idle tick counts `Sint64 volatile` and matches its V-sync and
  file-system procs in C; those bodies compiled with this project's ee-gcc 2.96 schedule the count's `daddu`/`sd`
  differently when the counts are plain, so that retail has the volatile shape too.
* `adxm_usrvsync_proc` has a row too, on the owner's standing rule for words shared between threads. Its three
  keywords are the exit request and the exited word (other threads set and wait on them) and the busy flag
  `adxm_usrvsync_busy`, which `ADXPS2_ExecVint` reads. Its tick count (`0x49da08`) is plain: the busy store is
  written through `ADXM_SET_BUSY`, a statement macro whose loop notes keep the count's `ld`/`daddu`/`sd` ahead of
  the flag store and the call, as `do { } while (0)` does in `sftim.c`. 3rd Strike declares that count plain too.
  `adxm_usridle_thrd` has a row too (four keywords), on CRI's own build: see the vendor-object evidence below. Its
  tick count is plain in source through `ADXM_SET_BUSY`, as above.
* CRI's own 2002 SDK object `adx_mps2.o` in `libadxe.a` (the SDK archives of
  [SkeletonPicture/recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)) holds
  `adxm_usridle_proc`, the earlier form of `adxm_usridle_thrd`: `li s1,1; nop; ld cnt; daddiu; sd cnt; sw s1,busy;
  jal; nop; sw zero,busy; move s0,v0; lw border; ...`. Compiled with this project's ee-gcc 2.96 (`-O2 -G8`) it is
  byte-equal to that object only when the busy flag `adxm_usridleproc_exec_flag` is `volatile`: plain, the clearing
  store moves into a delay slot. So the busy flag the keyword guards is `volatile` in CRI's own build, although only
  that thread touches it, and the same object has `volatile` tick counts. The other `adx_mps2.o` members back the
  remaining rows: the `adxm_*_proc` thread bodies match only with their tick counts, busy flags and thread ids
  `volatile`, and `adxm_ShutdownSafeThrd` (and its Vsync, MwIdle, UsrIdle and UsrVsync siblings, the same code on
  their own words) only with the exit request, exited word and id `volatile`. Objects cannot show the spelling
  (stabs drop the qualifier), only the code the qualifier gives.
* `adxm_mwidle_thrd` has a row too, on the owner's instruction. Five of its seven keywords are on shared words (the
  exit request, the exited word, the border request, the user-idle thread id and the slept flag). The other two are
  the tick count (`0x49da00`) and the busy flag (`0x49d9d4`), which only this thread touches (`ADXPS2_ExecVint`
  reads the other busy flags). Strip either and the busy store is scheduled ahead of the count's `ld`/`sd`;
  ee-gcc keeps the two in order only when both are `volatile`. The 3rd Strike decompilation declares the count and
  the busy flag (`adxm_mwidle_cnt`, `adxm_mwidleproc_exec_flag`) `volatile`, but it left this function as assembly,
  so those declarations were never tested by a match.

### dtx-server-flag

The DTX RPC server's thread function (`0x273128`, `dtx_svr_proc`) stores 1 to its ready flag (`0x4a9b18`,
`dtx_proc_init_flag`) and then calls `sceSifRpcLoop`. The store is the word's only access in the function. Written
plain, the store moves into the call's delay slot; retail keeps it ahead of the call with a `nop` in the slot, and
only a `volatile` flag gives that. The row has one keyword, approved by the owner on vendor evidence:

* CRI's own 2002 SDK object `dtx.o` in `libadxe.a` (the SDK archives of
  [SkeletonPicture/recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)) holds `dtx_svr_proc`:
  `li v0,1; move a0,sp; sw v0,dtx_proc_init_flag(gp); jal sceSifRpcLoop; nop`. Compiled with this project's
  ee-gcc 2.96 the function is byte-equal to it with a `volatile` flag, and plain puts the store into the `jal`
  slot. The flag is `volatile` in CRI's own build, although it guards no other access in the function.
* The second builds disagree: the 2001 decompilation of an earlier library declares `Sint32 volatile
  dtx_proc_init_flag`, and the 3rd Strike decompilation declares it plain. The original compiler output decides.
* Stabs drop the qualifier, so the object shows the code the qualifier gives, not the spelling.

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
* `viBufReset`, `viBufAddDMA` and `viBufRestartDMA` (CRI's copy of Sony's `vibuf.c` in sfmpvps2.c) rest on the same rule as
  `viBufDelete` and `viBufStopDMA`: standing owner rule, hardware register access.
* The serial port registers and the interrupt status register I_STAT at `0x1000F000` are absent from the header and
  identified from the open-source ps2sdk.
* `sceSifInitCmd` clears and acknowledges the SIF0 interrupt through `eeregs.h`'s `D_STAT` and starts the channel
  after reading `D5_CHCR`. Each access changes the bytes when stripped: the status read (35 words differ), its
  store (28) and the `CHCR` read (29); all three plain give 158 words against 160. The row counts the two macros.
  Under ee-gcc 2.9 a `volatile` store to a constant address comes out folded (`lui at; sw -8176(at)`), which is not
  the 2.96 combiner behaviour described under "Testing a `volatile`".
* `_cscStoreImage` polls and resets `IPU_CTRL` and sets up channel 4 through `D_STAT` and the `D4` registers; its
  keywords are the registers' own, and its row counts the five macros it names.
* `_sendDataToIPU`, `_dmaRefImage` and `_waitBdec` use channel 3, 4 and 9 and IPU registers through the header's
  macros. `_waitBdec` is 165 words in retail; stripping one macro's `volatile` at a time changes it to 158-164 words
  with 86-148 words differing (`D_ENABLEW` loses its enable store as dead, the polled `D3_QWC`, `D4_QWC`, `D4_CHCR`
  and `IPU_CTRL` reads merge, `IPU_BP` folds into the `IPU_TOP` loads, the reset stores of `D3_CHCR` and
  `D_ENABLER` collapse); all eight plain give 138 words.
* srcfile's timer-3 registers (`T3_COUNT`, `T3_MODE`, `T3_COMP`) and `I_STAT`, `volatile` as in `eeregs.h`: with the
  keyword GCC keeps the constant address inside the access (`lui at` plus offset, as retail), without it builds the
  address with `lui`/`ori` first. Stripped, `T3_COUNT` changes 54 words of the patch, `T3_MODE` 186, `T3_COMP` 199 and
  `I_STAT` 25. `StartCompare` and `kReleaseAlarm` rest on this anchor; `AddAlarm` and `kAlarmInterrupt` count these
  with the `$gp` read under [sony-gp-and-syscall-asm](#sony-gp-and-syscall-asm).

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
* The record's `overflows` member, the high part of the system time that the timer interrupt counts, is `volatile`
  as `libtimer.c` declares it (`volatile u_long ulHighCount`, `r03285:123`). Without the keyword the handler's
  increment is stored in the delay slot of its call to the compare-register write (166 words against 168, 114
  differing); with it the handler and all 35 other functions of the file match. It is a fourth `volatile` member of
  `TimerState`, so every function that names the record counts it, and each row of this anchor whose function names
  the record rose by one.
* `cbTimerHandler`, the timer-2 interrupt handler, is `libtimer.c`'s handler (`r03285:536-596`) for timer 2. Its
  `applyOverflow` is the commented-out C `ApplyOverflow` of that file (`r03285:350-367`), which DW4's libkernl copy
  matches exactly. Unlike SDK 3.0.3 it never decrements the used-counter count when it frees an alarm. Its
  `volatile` row counts the record's four members, the `T2_COUNT` and `T2_MODE` macros and the counter's `key`; its
  `asm` row is under [sony-gp-and-syscall-asm](#sony-gp-and-syscall-asm).
* `readSystemTime` reaches the record's five `volatile` members through `g_Timer`; the statement itself does not
  depend on them. `applyOverflow` counts its own seven: stripped, `T2_COUNT` takes `cbTimerHandler` from 672 to 652
  bytes, `T2_MODE` to 668 and `overflows` to 648 (Sony's own asm `ApplyOverflow` gives 644, so DW4's 2.8.0 used the
  C form).

### sony-vu-and-gp-asm

`sceGsResetPath`, `sceSdRemote` and `sceSdCallBack` hold statements C has no spelling for.

* Sony's `libgraph` source in SDK 3.0.3 (`graphdev.c`, source text `r03376`) writes `sceGsResetPath`'s statements
  as `__asm__`: it orders the VIF1 reset with `sync.l`, then sets a bit of VU control register `$vi28` with `cfc2`,
  `ori`, `ctc2` and `sync.p`. Its `libsdr` source (`sdr_main.c`, `r03289`) holds no `__asm__`: `sceSdRemote` calls
  `GetGp()` to record `$gp` beside a registered handler and `SetGp()` to swap it around an RPC call that has an end
  function, and those statements are `eekernel.h`'s (`r03616`), carried exactly by `include/dw4/support/eekernel_gp.h`.
* Compiled from Sony's text, with the header's `GetGp`/`SetGp` and only retail symbols and constants mapped, both
  functions are byte-identical to retail. `sceGsResetPath` needs the assembler of its [compiler note](sd-prologue.md).
* C reaches neither a VU control register nor a move of `$gp`.
* `sceSdRemote`'s two `volatile` keywords are the header's. Neither can go: without the one on the read the registers
  differ, and without the one on the swap the function comes out 164 bytes short. `sceGsResetPath`'s statements have
  no outputs, so its `__volatile__` changes nothing and is left out, by the rule in "Testing a `volatile`".
* `sceSdCallBack` records `$gp` beside the end function it registers with the same `GetGp()` (`r03289:101-110`),
  and is byte-identical to SDK 3.0.3 `sdr_main.o`. Without the header's `volatile` its two stores trade places;
  `register void *gp asm("$28")` is asm too and drops the `move`.

### sony-libmpeg-motion-compensation

libmpeg's motion-compensation kernels (`_rix_*`, `_ri0_*`) and its two reference-image copies (`_copyAddRefImage`,
`_copyRefImage`) are C functions whose body is one `asm` statement.

* Sony's SDK 3.0.3 `mpc.o` records them as compiled procedures: frame register 29 and return register 31, no line
  records, static procedures in an included `mm.c` and in `mpc.c`. Its assembled files (`klib.s`, `tlbtrap.s`) have
  0 and 0 and line tables. Each kernel starts on the compiler's 8-byte boundary and ends with the compiler's
  `jr ra; nop`; in `_copyRefImage` that return follows the `_maxval` data the asm ends with, which hand-written
  assembly would not do. A C function whose only statement is an `asm` gives exactly that: the asm text followed by
  the compiler's own return (an asm text with a return of its own gives two, eight bytes more).
* No C spells them. `addi` appears in no other function of the library (the compiler adds with `addu` and `addiu`);
  `qfsrv`, `mtsab`, `pextlb`/`pextub` and `pcpyld` have no spelling in this compiler, and the registers are fixed,
  with the argument read as `$4` directly.
* The table at `0x481c98` is 3.0.3's `_rix` and `_ri0`, entry for entry, so the names are Sony's. DW4's 2.8.0 kernels
  are 3.0.3's with the header loads reordered and registers renamed by hand (14 have the same instructions in another
  order, two differ in registers); the two copies are an older version that handles 16 bytes a loop where 3.0.3
  handles 64, with the same `_maxval` clamp.
* `.align 4` before `_maxval` cannot be used under the unit's `-ffunction-sections`, where it counts from the
  function's own section and pads nothing; two `nop`s pad the constant to the 16 bytes `lq` needs. The statements
  carry no `volatile`: with outputs absent it changes nothing.

### sony-libcdvd-shared-state

libcdvd's channel state: the semaphore ids, the command in flight, the busy flag and the read mode, declared
`volatile` (`include/dw4/sony/libcdvd.h`). `_sceCd_cd_callback` is the commands' end function, which runs at interrupt
time (it calls `iSignalSema`), and the callers read what it writes. The `volatile` rows of the file count each
function's uses of these words, and the `$gp` swaps of `_sceCd_cbLoop` and `_sceCd_Poff_Intr`.

* Two keywords keep real reloads. Without `sceCdCbfunc_num`, `_sceCd_cd_callback` is 148 bytes instead of 160, since
  retail stores the value and reads it back twice with no call between; `sceCdBreak` is 180 against 184. Without
  `sceCdCbfunc_number`, `_sceCd_cbLoop` loses the reload for the call argument.
* The others decide only whether a load or store may stand in a delay slot, or the order of a run of stores. The
  compiler will not fill a delay slot with a `volatile` access, so retail's `lw a0,_sceCd_ncmd_semid; jal PollSema;
  nop` is the signature of a `volatile` semaphore id, and `sceCdSeek`'s `jal SignalSema; lw a0,_sceCd_ncmd_semid`
  shows the 2.10 assembler moving one into a slot the compiler left empty. Stripped, `_sceCd_ncmd_prechk` is two
  words short and `sceCdLayerSearchFile` three; the `_sceCd_scmd_semid` rows change `_sceCd_scmd_prechk` (360 against
  368 bytes) and `sceCdBreak`; `_sceCd_rcmd_semid` changes `cdvd_exit` and `sceCdDiskReady`; `_sceCd_c_cb_sem` and
  `cb_semid` move stores into a branch slot of `_sceCd_cd_callback`; `_sceCd_ee_read_mode` copies `sceCdRead`'s second
  load into the default case's slot; `sceCdPoffCbfunc_num` reorders three stores of `_sceCd_cbLoop`; `Init_seq`
  drops one `lui` per store in `sceCdInit` (728 bytes against 736). With every `volatile` removed the two assemblers
  give identical code: the assembler only matters for these accesses, which is why the six files build with
  `ee-gcc-2.9-as210`. No plain spelling reproduces them: every keyword stripped, `-fvolatile-global`, a local copy of
  a semaphore id and the comparison written the other way round were all tried.
* The rows count these like the approved `VSync2` and timer words, which also decide only a slot. Without them there
  is no matching source for the six files.
* SDK 3.0.3 `cdvd000.o` is one source file (`../eecdvd.c`) whose `.mdebug` has no type information, so it records
  nothing about `volatile`. 15 of the 32 functions are byte-identical to it with relocated words masked.

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
  register by number, which explains the varying register of the five copies less well than `%0` does. (In the
  two semaphore copies the operand form gives `v1` where retail has `a1`: #psx2-semaphore-interrupt-status.)
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
work there; the files match with every declaration `volatile`. The flag words' declaration is their home,
`dw4/p2/p2watchdog.h`, which `p2watchdog.c` includes beside its definition, so the watchdog's functions count the
keyword of both.

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
* The swap flags at `0x56bf58` (a swap is pending at the next vertical blank) and `0x56bf60` (the GS has drawn the
  frame) are shared between the vertical-blank handler, reached from the GS interrupt handler, and thread code:
  `p2VsyncHandler` tests the drawn flag and sets the pending flag and clears the drawn one on every flip path;
  `p2SwapBuffers` and `p2InitSwap` write both from the game thread; `p2RecordFrameTime`, a finish function the
  GS FINISH handler (`p2FinishHandler`) runs, sets the drawn flag. The vertical-blank handler reads the drawn flag
  again on each path where retail reloads it. Both words are declared `volatile` once in the file, so `p2InitSwap`
  counts 5, `p2SwapBuffers` 4, `p2VsyncHandler` 4 and `p2RecordFrameTime` 1.

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
  `opt_dead_assignments`, `opt_lifetimes`, `opt_dead_code`, `global_optimizer` and `peephole` off,
  `optimization_level` 0 to 3 all differ; `schedule off` makes the function 612 bytes against retail's 560).
  `scheduling off` is not a b52 pragma (`warn_illpragma` reports it) and compiles as if it were absent.
* The second counted keyword is the file's `volatile` declaration of the watchdog's flag word at `0x56d670`,
  where the busy bits it sets live ([dma-channel-shared-words](#dma-channel-shared-words)). It is inert in this
  function, which matches without it, and counts only because the function names the declaration.

### gs-interrupt-sync-ei

The GS interrupt handler in `src/engine/p2gs.c` and the two timer interrupt handlers in `src/engine/p2timer.c`, MWCC
files whose handlers are registered with `AddIntcHandler`, end with `sync` and `ei` in one
`__asm__ __volatile__("sync\nei\n")`, the statement of ps2sdk's `ExitHandler()` macro
(`local/ps2sdk-ref/ee/kernel/include/kernel.h:29`) and of Sony's own `eekernel.h` in SDK 3.0.3 (source text
`r03616:77`), which defines `#define ExitHandler() __asm__ volatile("sync.l; ei")`: `sync.l` encodes as `sync`. Sony's
Timer Library ends its timer interrupt handler with it (`libtimer.c`, `r03285:608`), and so do `r03287:88` and
`r03320:27`. A statement of only `sync` and `ei` needs no `asm` row; the row is for its keyword.

* The upstream macro writes the statement and its one keyword.
* Retail has a branch for each status bit with the test recomputed from the saved status each time. With no
  keyword on either instruction, the three tests become `sltu` results kept in saved registers, the frame
  doubles and the body is 12 instructions shorter (352 bytes against 400). One keyword is enough: on either of
  two separate statements, or on the one statement, the function matches.
* No pragma gives the retail shape without the keyword: nine variants, all a different size.
* The timer handlers need it the same way. Stripped, `p2Timer1Handler` is 164 bytes against 160: it computes `sp+13`
  once and does both read-modify-writes of the local mode word through it, where retail forms `13(sp)` on each
  access. `p2Timer0Handler` is 536 bytes against 548, losing the `lui` that re-materialises each global access. Each
  handler needs its own keyword; on the `sync` alone it is enough for both, and on the `ei` alone the second
  breaks. Making the `Tn_*` register macros `volatile` does not replace it, and no pragma does either
  (`opt_common_subs off` comes closest, 5 words off on the first handler and wrong on the second). Every spelling
  that keeps the keyword matches, Sony's `sync.l; ei` among them; every one without it, and `__I_sync(); __I_ei();`,
  does not.

### psx2-semaphore-interrupt-status

The signal and wait functions of the PS2 semaphore class (0x32ef20 and 0x32f060) in the core whole file reach one
`__asm__ volatile` statement through the inline `interruptEnableStatus` in
`src/engine/core/igPsx2Semaphore_tail2.inc`: the COP0 Status read of #dma-channel-cop0, here with both registers
named and the keyword kept. Each function has an `asm` row and a `volatile` row.

* The owner approved, for these two functions, the status check written in assembly, and chose the `volatile`
  statement over the equivalent pragma form below (2026-11-14). A COP0 register read has no C spelling, and each
  function needs the test: outside an interrupt handler it makes the thread's kernel call (`SignalSema`,
  `WaitSema` or `PollSema`), inside one the interrupt-safe call (`iReferSemaStatus`, then `iSignalSema` or
  `iPollSema`).
* The three instructions are those of the engine's other three copies of the test (#dma-channel-cop0): the read,
  the shift into `a2`, the `and` back into the read's register. In both semaphore functions that register is
  `a1`. With it left to the compiler (the `"=r"` operand of the statement in `src/engine/dmaChannel.c`) it is
  `v1` and the mask lands in `a1`, two instructions off in each function; with `$5` named the bytes match. So
  this copy names both registers and copies the result to its operand (`move %0, $5`), a copy the register
  allocator removes: `mfc0 $5, $12; srl $6, $5, 16; and $5, $5, $6; move %0, $5`. It needs no clobber list: the
  functions match with and without `: : "$5", "$6"`, so the list went.
* The keyword changes the bytes. The compiler skips its peephole pass for the block that holds an
  `__asm__ volatile` statement (a plain `__asm__`, an `asm { }` block and an `asm` function do not stop it), and
  three things in each function need the pass off: the two `xori 1` of the conversion to `bool`, the `andi 0xff`
  after them, and the receiver read through its saved copy. Stripped, the conversion folds to one `sltu` and
  signal is 12 bytes short. Sony writes its Status reads the same way,
  `__asm__ volatile("mfc0 %0, $12" : "=r"(status))` (#sony-libkernl-cop0-and-syscall).
* It is an inline C function holding the statement, not an `asm` function: b52 never expands an `asm` function
  (`static inline asm`, `inline asm`, `asm inline`, `#pragma always_inline on`, with or without its `jr ra`: the
  caller gets a `jal`), and retail has the three instructions inside both callers.
* Nothing after the `and` is assembly. Retail's `andi; sltu; xori; xori; andi 0xff` is the compiled conversion
  `bool interruptsEnabled = interruptEnableStatus() & 1;`. Written in assembly instead, the same five
  instructions come out in another order: an instruction that names a hard register (`zero` in `sltu`) is a
  barrier for the scheduler, and the next statement's `lw a0,12(s1)` then follows the `sltu` where retail has
  it right after the `and`.
* An equivalent spelling exists and retail cannot tell the two apart: the same three instructions in an
  `asm { }` block (`mfc0 a1, $12; srl a2, a1, 16; and a1, a1, a2; move status, a1`) with each function inside
  `#pragma push` / `#pragma peephole off` / `#pragma pop`. It gives the same bytes for both functions and would
  cost two optimiser pragmas in the [debt ratchet](debt-ratchet.md) in place of the keyword's rows.
  [Understanding shapes](understanding-shapes.md#types-and-values) has the compiler's side.

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

### alchemy-vu0-macro

The four fixed-count software vertex-blend functions of the engine's `p2` renderer in `src/engine/p2core.c`, an MWCC
file: `p2SoftwareBlendFourWeights`, `p2SoftwareBlendThreeWeights`, `p2SoftwareBlendTwoWeights` and
`p2SoftwareBlendOneWeight`. Each is a C loop around one MWCC `asm { }` block of VU0 macro-mode code.

* The loop is C: the global setup, the matrix address `matrices + indices[k] * 16` (`lbu; sll 6; addu`) and the
  pointer steps `position += 3; out += 3; weights += stride; indices += stride`. The block holds `lqc2` of four
  matrix rows per weight, the unaligned loads of the position and weight triples (`mtsab; lq; lq; qfsrv; qmtc2`
  into `$vf17` and `$vf20`), the `vmulaw`/`vmaddax`/`vmadday`/`vmaddz` transforms, the weighted sum, and the
  store (`qmfc2; sw; prot3w; sw; prot3w; sw`). It uses `a2` and `a3` as fixed scratch registers and names the C
  locals as operands. Removing it deletes 26 to 46 instructions.
* No C spells these instructions. No MWCC version in `local/mwcps2` emits a COP2 macro instruction, `qfsrv`,
  `mtsab` or `prot3w` from C: its `__I_` builtins stop at `cfc2`/`ctc2` (see [enbaya-vu0-macro](#enbaya-vu0-macro)).
* Alchemy writes VU0 code this way throughout: the Gfx, Maths, SceneGraph and psx2Lighting libraries and Enbaya
  hold COP2 macro code that b52 built, and a Maths function has the same unaligned-load sequence into `$vf17` with
  `a2` and `a3` as scratch inside a C loop. Enbaya's two functions are the only other VU0 code approved.
* The block form, not GCC-style `__asm__`, is the better supported spelling. The unmatched
  `p2SoftwareBlendWeights` reads a float weight with `lwc1` and moves it with `mfc1 a2` inside its inner loop;
  b52 loads a float `"r"` operand with `lw` (a plain local, a direct element, an inline helper's parameter, union
  and pointer punning and `* 1.0f` all tried) and rejects an `"f"` operand of `mfc1`, while an `asm { }` block
  that writes `mfc1 a2, weight` against a float local gives retail's `lwc1`, the `andi`/`sll`/`sll`/`addu` and the
  `mfc1`. Retail cannot tell the two spellings apart for the four fixed-count functions, which match as GCC-style
  statements too, so they use the block form of the function that needs it. CodeWarrior's manual, as quoted under
  [enbaya-vu0-macro](#enbaya-vu0-macro), recommends the GCC-style form.
* Each block is one `asm` use, so each function has one row.

The same anchor covers the product of two aligned matrices (0x190470) in the Maths whole file
(`src/engine/maths/igMatrix44f.inc`): a C function around one `asm { }` block holding only COP2 instructions (`lqc2`
of both matrices, the `vmulax`/`vmadday`/`vmaddaz`/`vmaddw` row products, `sqc2` of the result). One `asm` use, one
row.

`igMatrix44f_Multiply` and `igMatrix44f_PreMultiply` have no source: an MWCC `asm` function reproduces each, but the
owner held that form out (2026-11-17). A SceneGraph function (0x1be190) inlines Multiply's body (C alignment test, then
the instructions), so the original is likely an inline C function with `asm` blocks; that form is still 4 rows short.
`igMatrix44f_Copy` has no source either: its `lq`/`sq`/`lwc1`/`swc1` all have C spellings, so this anchor does not
cover it.

The frustum test of a box (0x1c47f0, SceneGraph whole file, `src/engine/scenegraph/igFrustCullTraversal_tail.inc`) is
C around three `asm volatile { }` blocks: the unaligned loads of the matrix and the two corners (`mtsab; lq; qfsrv;
qmtc2`), the eight corner transforms with `vclipw` and the `cfc2` clip-flag reads, and the narrow and full guard-band
re-tests with the I register loaded through `mfc1`, `nop`, `ctc2 $vi21`. The return codes, the flag masks and the
scale choice are C. Three `asm` uses and three `volatile` keywords, one row each.

* Without `volatile` on the narrow re-test block, MWCC's PCode peephole folds the C `lwc1` of the second I value and
  the block's `mfc1` into one `lw` (2 of 180 words differ); a block that opens with a volatile asm statement is not
  scanned. Every plain `asm { }` spelling tried (the load inside the block, a second block, address operands, a
  pointer, a function-scope or `register` local, an `int` destination) folds; the tries are in the function's attempt
  file. This `volatile` is not a scheduling pin of a C load: it keeps retail's `lwc1`/`mfc1` pair intact.
* With all three blocks written `asm volatile` the function still matches, so the qualifier reads as the PS2 VU0
  inline-asm idiom's uniform form rather than a one-block hack, and the source writes every block that way
  (owner's conditional standing rule, 2026-11-17).

The VU0 vertex morph (0x18ea90, `igVectorMorphing_MorphVu0`, Maths whole file,
`src/engine/maths/igVectorMorphing_tail.inc`), installed beside the scalar `igVectorMorphing_Morph` by
`igVectorMorphing_InstallFunctions`, is C around three `asm volatile { }` blocks: `lqc2` of four packed base vertices
(three quadwords), per target `qmtc2` of the weight's bits, `lqc2` of the target's three quadwords, three `vmulx.xyzw`
by the weight and three `vadd.xyzw` into the sum, and `sqc2` of the sum. The group count, the loops, the target address
(`targets[t]` plus a running 48-byte offset), the weight read (`lw`), the pointer steps and the scalar tail for the last
`count & 3` vertices are C. Three `asm` uses and three `volatile` keywords, one row each.

* No C spells `lqc2`, `qmtc2`, `vmulx` (vector by broadcast field), `vadd` or `sqc2`. The function written as plain C
  (the three-quadword sum as float loops) is 364 bytes of FPU code against retail's 372, with no COP2 instruction; 74
  of 93 words differ.
* The `volatile` is what gives retail's scalar tail, not a scheduling pin. Retail keeps the tail's weighted triple in a
  stack slot (`swc1` to `0..8(sp)` after each `mul.s`, `lwc1` back for each `add.s`, a 16-byte frame). With every block
  written plain `asm { }` MWCC keeps the triple in registers and the function is 344 bytes; with any one, two or all
  three blocks written `asm volatile` the triple stays in memory and the function matches. No plain spelling of
  the tail gives the folded slot offsets: a `float[3]`, an `igVec3f` (fields, `operator[]`, `add`, `scale`,
  `operator*`), pointer-taking and returning inline helpers, an array-member class, a function-scope array, a pointer
  or index variable into the array and loops over the components all scalarize, hoist `sp + 4`/`sp + 8` into registers,
  or add a block copy (the tries are in the function's attempt file).
* With all three blocks `asm volatile` the function matches, so the source writes every block that way (owner's
  conditional standing rule, 2026-11-17).
* The GameCube build (USA `main.dol`) installs the same pair at 0x80127270: the scalar morph (0x80127078) and a
  paired-single form (0x80127128) with this function's structure: a group loop to `(count >> 1) * 3` stepped by 3
  (`psq_l` and paired multiply-adds, left as raw words by the disassembly dump), then the same scalar tail for the
  remainder, there with the products in registers. The Xbox morph pair was not found; the Xbox blending selector
  (0xb28f0) reads `useSimdBlending` and `forceOneWeightSimd` and installs a weighted and a one-weight blend, the PS2
  file's `igVectorBlending_BlendWeighted` and `igVectorBlending_BlendOneWeight`.

### scratchpad-traversal-stack

The hit-land model traversal's traverse hook (SceneGraph whole file, `src/engine/scenegraph/igTraversal_tail.inc`)
runs the outermost traversal on a stack at the top of the scratchpad when `useScratchPadForTraversal` is set: on the
first nesting level it saves `sp` to 0x562a48 and moves the scratchpad top (0x70003fe0) into `sp`, and when the level
count returns to zero it reloads `sp` from 0x562a48.

* Neither MWCC nor ee-gcc writes `sp` from C, so the two GCC-style statements (`sd $sp, 0(%0); move $sp, %1` and
  `ld $sp, 0(%0)`) have no C spelling; their operands (the save slot and the scratchpad top) come from C, and the
  nesting count, the hook calls and the traversal stay C. Two `asm` uses, one row.

### p2-debug-breakpoint

Two routines of the engine's `p2` renderer in `src/engine/p2core.c` (0x1eba30, 0x1eba74) arm the EE's instruction
breakpoint: the first reads the breakpoint control register (`mfbpc`), clears its enable bit when it is set and writes
it back (`mtbpc`, `sync.p`), then calls the second, which points the instruction address register at its own return
address plus 92 (`mtiab`, mask `mtiabm`) and sets the control bits (`mfbpc`, `and`, `or`, `mtbpc`, `sync.p`). Both
are MWCC `asm` functions (`asm-function` rows, one each).

* The COP0 debug registers have no C spelling: neither MWCC nor ee-gcc emits `mfbpc`, `mtbpc`, `mtiab`, `mtiabm` or
  `sync.p` from C, and the MWCC builtins stop short of them.
* They are `asm` functions rather than C around blocks: the first builds its own frame and the second restores it
  (`ld ra` and the frame pop in the second's epilogue), the 64-bit constants are the assembler's `dli` expansion
  (`ori`/`dsll` chains) written out by hand, and the delay slots are filled by hand under `.set noreorder`.

### sfx-handle-used-flag

The in-use word of the SFX handles (`SfxHn`, `SfxaHn`, `SfxZHn`): the free-handle searches of `sfx.c`, `sfxa.c`
and `sfxz.c` read it and the alpha and Z frees clear it, through a `volatile` pointer. The keyword adds or drops no
access; it decides only delay-slot filling (stripped, the searches take the loop head's load into a `bnezl` slot
where retail has `bnez; nop`, and the frees move the `lui` into the `beqz` slot). The owner approved it on this
evidence:

* DW4's Sofdec is a later build than CRI's public SDK: `CRI SFX/PS2EE Ver.2.08` and `MWSFD/PS2EE Ver.3.33s281`
  (Oct 6 2004) against `Ver.1.09` and `Ver.2.27` (Sep 26 2002) in the SDK's `libmwsfde.a`
  ([SkeletonPicture/recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)). Plain C compiles to the
  2002 objects (`sfx_lib.o`, `sfx_alp.o`, `sfx_zmv.o`) exactly, filled slots included, while DW4 leaves the slots
  empty, the shape only a `volatile` access gives under ee-gcc 2.96
  ([understanding shapes](understanding-shapes.md#delay-slots-b52)).
* The Persona 4 decompilation ([Raikaru/Persona4-Decompilation](https://github.com/Raikaru/Persona4-Decompilation)),
  built with the same ee-gcc 2.96 at `-O2 -G0` from SFX 2.08-generation sources, needs a non-C construct for the
  same empty slot in its alpha free (`src/cri/re4/sfx_alp.c`, lines 57-68: an empty `asm` memory barrier).

### sofdec-build-tool-asm-functions

`sfxzmv_GetZfrmInf` (`0x2b45b0`, 128 bytes), a file-scope `__asm__` function in `src/cri/sfxz.c` (owner's ruling
of 2026-11-18 on build-tool differences: an `asm-function` row once the function is proven against its 2002 SDK
object). It returns the Z-frame chunk's entry between two tags, or 0 and 0 when the chunk is missing.

* Its plain C, kept in the comment above the block, compiles under the unit's profile (ee-gcc 2.96, `-O2 -G0
  -ffunction-sections`) to the code of `sfxzmv_GetZfrmInf` in the 2002 SDK's `sfx_zmv.o` (`libmwsfde.a`,
  [SkeletonPicture/recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)): all 30 words equal,
  relocated fields unrelocated in both.
* Retail is the same function built by a later tool chain. The differing region, from the prologue to the
  failure path's branch (SDK = our C, then retail):

  | SDK `sfx_zmv.o` and our C | retail |
  |---|---|
  | `sd s1,40(sp)` | `sd s1,40(sp)` |
  | `sd ra,48(sp)` | `move s1,t0` |
  | `li v1,1` | `sd ra,48(sp)` |
  | `lw v0,0(a0)` | `li v1,1` |
  | `bne v0,v1,fail` | `lw v0,0(a0)` |
  | `move s1,t0` (slot) | `bnel v0,v1,fail+4` |
  | `lw v1,4(a0)` | `sw zero,0(s0)` (slot, the target's first store) |
  | `bnel v1,zero,search` | `lw v1,4(a0)` |
  | `lw v0,8(a0)` | `bnel v1,zero,search` |
  | `fail: sw zero,0(s0)` | `lw v0,8(a0)` |
  | `b done` | `fail: sw zero,0(s0)` |
  | `sw zero,0(s1)` | `b done` |
  | `search:` | `sw zero,0(s1)` |
  | | `nop` (alignment of `search`, never executed) |
  | | `search:` |

  Retail keeps the copy of `size` ahead of `sd ra`, fills the first branch's slot from its target and moves the
  branch past the copied store, and pads the next label to 8 bytes. ee-gcc 2.96's delay-slot pass takes the copy
  into the slot whatever the C says: it scans back from the branch over `lw`, `li` and `sd ra`, none of which
  conflicts with it. Only a `volatile` access stops that scan, and the owner did not approve one here.
* `MWSFLIB_SfdErrFunc` and `mwPlyCreateSofdec`, the other candidates of the ruling, are no tool-chain cases: the
  2002 `mwsfdlib.o` allocates the error callback's registers as retail does, and the C that does so was found (it
  matches); `mwPlyCreateSofdec` matches with its free-entry search reading the in-use word `volatile`
  ([mwsfd-handle-used](#mwsfd-handle-used)).

### local-decl-vsync-counts

ADXT's tick count `adxt_vsync_cnt` (3 copies: `adxps2.c`, `adxt.c`, `adxtsvr.c`) and MWSFD's second V-sync count
`mwsfsvr_vsync_cnt2` (2 copies: `mwsfd.c`, `mwsfsvr.c`). Each is defined once and declared with different
qualifiers in different files, which one header declaration cannot give.

* `adxt_vsync_cnt` is defined in `adxtinit.c`. `adxps2.c` and `adxtsvr.c` declare it `volatile` where they read it
  (the V-sync interrupt path and the server), and `adxt.c` declares it plain. Each keyword decides the address
  form of the files' statements and nothing else ([adxt-ready-count](#adxt-ready-count)), so a header
  declaration, volatile or plain, gives one of the forms to all of them.
* `mwsfsvr_vsync_cnt2` is `volatile` in `mwsfd.c` and `mwsfsvr.c`, the files with the approved rows
  ([mwsfsvr-vsync-count](#mwsfsvr-vsync-count)). Declared in a header, the keyword would apply to every unit that
  includes it.

### local-decl-sfd-header-codegen

`sfadxt_stat` (2 copies: `sfadx.c`, `sfdtst.c`) and `MEM_Copy` (`sfmpv.c`). The header declaration changes the
code of `sfmpv.c`.

* `sfadxt_stat`: with the declaration in `sfd.h`, which `sfmpv.c` includes, `sfmpv_SetDecTtu` is scheduled
  differently from retail. The two units that use the word declare it themselves.
* `MEM_Copy`: `mcp.h` declares it returning `void`. `sfmpv.c` declares it returning `int`; with the `void`
  prototype `sfmpv_SetMpvHd` allocates its registers differently from retail.

### local-decl-sfx-unprototyped

`SFXA_Destroy` and `SFXZ_Destroy` (`sfx.c`). Their definitions take `volatile` pointers
([sfx-handle-used-flag](#sfx-handle-used-flag)), which a prototype in `sfx.h` would show to every unit that
includes it, so `sfx.c` declares both unprototyped and `SFX_Destroy` calls them that way.

### local-decl-libc-types

Three symbols whose libc header form differs from what the code was compiled against.

* `_ctype_` (2 copies: `strtol.c`, `strtoul.c`): `const unsigned char _ctype_[]`, not the libc header's `char`; the
  character-class lookups stay unsigned (bytes).
* `_lseek_r` (`stdio.c`): its definition takes and returns `int`, but `__swrite` and `__sseek` are compiled against
  the `long` form; an `int` prototype adds the 64-bit conversions to them.
* `fprintf` (`p2timer.c`): the unit uses newlib's `struct __sFILE` and `_reent` through `_impure_ptr`, and libc's
  `stdio.h` redefines `FILE` and `_reent`, so the unit declares the one prototype itself.

## Open questions

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

* **`_sceFs_Poff_Intr`.** Written with Sony's header statements, `GetGp()` and a separate `__asm__ volatile("lw $28,
  %0")`, it is one word off: the `lui` is scheduled after `move s0, gp`, because a volatile `asm` is a scheduling
  barrier. It matches as one statement, `__asm__("move %0, $28\n\tlw $28, %1" : "=r"(gp) : "m"(sceCbPoff_Gp) :
  "memory")`, then the call, `__asm__("move $28, %0" : : "r"(gp))`, `sync` and `ei`, which is text nobody has shown
  Sony wrote; the SDK's `filestub.o` only shows the function is C. It stays out of `src/sony/libkernl/filestub.c`
  until a form that Sony's header and `libtimer.c` support matches.
