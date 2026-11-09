# Approved inline `asm` and `volatile`

An `asm` statement or a `volatile` passes the byte check whether or not plain C could produce the same
bytes, so either can force a match the original source did not have. A C or C++ function that uses one
counts as matched only once the project owner has approved that use. This is the same rule
[hand-written `.S` sources](assembly-sources.md) follow.

## The approval rule

Each approved use has a row in `config/source-approvals.tsv`: `kind` (`asm` or `volatile`), `symbol`,
`count` and the anchor of its evidence below. Only the owner approves a row. An agent may write one only
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
by name, what the file declares outside any function, and the project headers the file includes. A struct
member declared `volatile` at file scope therefore reaches every function in that file. The count voids an
approval when another use appears, which files the function as `unapproved` again.

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

Hardware is the exception to the first case. A register access can match without the keyword when nothing would
merge or drop it, but the source would then misstate what the code addresses, so it keeps the keyword and goes
to the owner.

The `lui`, `addiu`, `lw 0` address form is no evidence for a `volatile` global under GCC. A `volatile` access
does compile that way, but so do many accesses in functions that match without one.

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

## Open questions

* **The stack slot `volatile` stands in for.** Some inlined list searches take a value that retail stores
  to the stack and reads back. Locals, structs, arrays,
  references and conversion temporaries all fold the slot away or load a wider value, so what keeps the
  slot in the original is not known.

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
