# Sony libkernl: klib, glue, cache, intr, thread, deci2, tty, kprintf2

The first run of Sony's libkernl (`0x10aac0..0x10d168`) is eight archive members laid out in the order
the SDK's `libkernl.a` holds them. The SDK 3.0.3 archive (later than DW4's 2.8 release) gives each
member's function names, their order and offsets, and its local data; every C member below starts
where the previous one's `.text` ends, rounded to 8 bytes. Each C file is a whole-file unit that
defines its own `.data`, `.bss` and `.rodata`.

| file | extent | what it holds |
| --- | --- | --- |
| `src/sony/libkernl/klib.S` | `0x10aac0..0x10b360` | the system-call stubs ([assembly sources](assembly-sources.md)) |
| `src/sony/libkernl/glue.c` | `0x10b360..0x10b730` | newlib's system-call glue and `VSync` |
| `src/sony/libkernl/cache.c` | `0x10b730..0x10b9ac` | data-cache write-back and invalidation by range |
| `src/sony/libkernl/intr.c` | `0x10b9b0..0x10bbe0` | `QueryIntrContext` and the INTC and DMAC mask calls |
| `src/sony/libkernl/thread.c` | `0x10bbe0..0x10c030` | handler-side thread requests and `DelayThread` |
| `src/sony/libkernl/deci2.c` | `0x10c030..0x10c264` | the DECI2 calls |
| `src/sony/libkernl/tty.c` | `0x10c268..0x10c7ac` | the DECI2 console behind `write` and `read` |
| `src/sony/libkernl/kprintf2.c` | `0x10c7b0..0x10d168` | the kernel's formatted output: `kprintf`, `scePrintf` and their formatter |

The C files build with the libraries' compiler ([sd-prologue](sd-prologue.md)) at `-O2 -G0
-ffunction-sections`; the section flag leaves the code as it is and lets each function be placed.

## glue.c

`sceResetttyinit`, `VSync`, `VSync2`, `write`, `read`, `open`, `close`, `ioctl`, `lseek`, `sbrk`,
`isatty`, `fstat`, `getpid`, `kill`, `stat_glue`, `unlink`: the archive member's order, offset for
offset. Its `.data` is `ttyinit` and `sbrk`'s `heap_ptr` (`0x481e50`, `0x481e54`), the first words
of the run whose next word is `thread.c`'s. `write` and `read` serve only the console, through the
DECI2 tty, starting it on first use; `open`, `stat_glue` and `unlink` fail with `EIO`; `sbrk` moves
`heap_ptr` from `_end` up to `EndOfHeap`. `VSync` clears the INTC vblank-start bit and waits for it
to come back; `VSync2` also stops when the kernel's `SetVSyncFlag` flag is raised and returns the
time stored with it. `kill` of process 1 exits. The member names its sixteenth function `stat`; the
game has its own `stat`, so this copy takes the member's name as a suffix, as newlib copies do.

## cache.c

`_sceSDC`, `SyncDCache`, `iSyncDCache`, `_sceIDC`, `InvalidDCache`, `iInvalidDCache`. The walkers
read the tag of each line of both ways and write back (`_sceSDC`) or invalidate (`_sceIDC`) the
lines inside the range; the outer calls round to whole lines and mask interrupts unless called
from a handler. No data.

## intr.c

`QueryIntrContext`, `DisableIntc`, `EnableIntc`, `DisableDmac`, `EnableDmac`, `iEnableIntc`,
`iDisableIntc`, `iEnableDmac`, `iDisableDmac`, in member order. The kernel calls are made with
interrupts masked and followed by a `sync`.

`QueryIntrContext` is a C function whose body is one `asm` statement: `mfc0` of the Status register,
returning whether the interrupt-enable bit is clear. Sony's `intr.o` records it as a compiled procedure
(frame register 29, return register 31), and C has no spelling for a COP0 read. The statement needs
no `volatile`; `(stat ^ 1) & 1` and `(stat & 1) == 0` give the same bytes, while `(stat & 1) ^ 1` puts the
`andi` before the `xori`. The row is in [source approvals](source-approvals.md#sony-libkernl-cop0-and-syscall).

## thread.c

`topThread` (static), `InitThread`, `iWakeupThread`, `iRotateThreadReadyQueue`, `iSuspendThread`,
`DelayThread`, `_DelayThreadHandler` (static). An interrupt handler cannot wake, suspend or rotate
the thread it interrupted through the kernel, so it puts the request in a 512-entry ring (`topArg`)
and signals `topSema`; `topThread`, created by `InitThread` at top priority on its own 1 KB stack,
carries the requests out. `DelayThread` waits on a semaphore a timer alarm signals. The member's
`.data` `topId` is `0x481e58`; its `.bss` (`stack`, `topSema`, `topArg`) is `0x555280..0x555a8c`;
its strings (the internal-error message and the `"DelayThread"` semaphore tag) are `0x4d2410`.
DW4's release has no `StartThread`, which the 3.0.3 member adds after `DelayThread`.

The requests are queued with the interrupt-side `GetThreadId` system call, written as one `asm`
statement (`li $3,-47; syscall`) in `iGetThreadId`. Calling the library's `GetThreadId` instead
makes `iWakeupThread` eight bytes longer with a call in place of the inline pair, which is how
3.0.3's `thread.o` has it.

## deci2.c

`sceDeci2Open`, `sceDeci2Close`, `sceDeci2ReqSend`, `sceDeci2Poll`, `sceDeci2GrpOpen`,
`sceDeci2GrpClose`, `sceDeci2ExRecv`, `sceDeci2ExSend`, `sceDeci2ExReqSend`, `sceDeci2ExLock`,
`sceDeci2ExUnLock`, `kputs`: each packs its arguments and calls `Deci2Call` with its number.
`sceDeci2Open` also passes the uncached address of `userarea` (`.bss` `0x555a90`). The file ends at
`0x10c264`, where `tty.c` begins (`0x10c268`).

## tty.c

`QueueInit`, `QueuePeekWriteDone`, `QueuePeekReadDone` (all three static), `sceTtyHandler`,
`sceTtyWrite`, `sceTtyRead`, `sceTtyInit`, in member order. `sceTtyInit` opens a DECI2 socket on the
TTYP protocol (`0x210`), with `tinfo` as the block it shares with `sceTtyHandler`, and fills in the
header of the send buffer. `sceTtyWrite` copies up to 256 characters into that packet (a `\n` gains a
`\r` in front), asks to send, and polls the socket until the handler clears `writing`. The handler
receives each packet from the host into the receive buffer and, once it is complete, puts its text in
the 256-character ring that `sceTtyRead` drains up to the end of a line. The member's `.bss` (`q`,
`QueueInit`'s static ring, then `tinfo`, `wbuf` and `rbuf`, 320 bytes each and 64-byte aligned) is
`0x555ac0..0x555e80`; its four error strings are `0x4d2448`. The file's text is not in the SDK
sources, but Sony's DECI2 protocol-driver samples declare the block they share with their handler
the same way (`volatile int s; volatile u_int wlen; volatile u_int rlen; u_char *wptr; u_char *rptr;`)
and send and receive with the same statements; tty's block has a `writing` flag and the ring in place
of the samples' received-byte count. The ring's `count`, which the handler raises and `sceTtyRead`
polls, is volatile for the same reason. The file ends at `0x10c7ac`; `kprintf2.c` starts at `0x10c7b0`.

## kprintf2.c

`kputchar`, `deci2Putchar`, `serialPutchar` (static), `ftoi`, `printfloat`, `kvprintf`, `kprintf` and
`scePrintf`: the member `kprintf2.o`'s range. One formatter serves both entry points and sends every
character through the current output function (`putchar_hook`, which starts as `serialPutchar`).

* `kprintf` formats to the EE serial port: `kputchar` waits for room in the transmit FIFO and stores the
  character, and `serialPutchar` sends a `\r` before each `\n`.
* `scePrintf` points the hook at `deci2Putchar` for the call and restores it after. That function collects
  the characters in a 128-byte line buffer and sends the line to the host through `kputs` at each newline
  or when the buffer is nearly full.
* The formatter masks interrupts for the whole call. A conversion takes an optional `0` with a width of
  one or two digits (zero padding up to 31 characters), an `l` or `h`, then one of `o x d u e f s c`; any
  other character ends the conversion unprinted. `%e` and `%f` go through `printfloat`, which scales the
  value to `0.dddddd` with a decimal exponent. `ftoi` is handed the scaled value already converted to an
  integer rather than its bits, so the digits it prints are always 0; the code is as Sony's.
* `kprintf`, `scePrintf` and the formatter return `void`, as Sony's `eekernel.h` declares the first two.
* The file's own data: `.data` at `0x481e60` (eight bytes), `.bss` at `0x555e80` (128 bytes) and `.rodata`
  at `0x4d24c0` (340 bytes).
* `kputchar` reads the serial interrupt-status register and writes the FIFO through `volatile` accesses;
  its two rows are under `#sony-hardware-registers`.

## Open questions

* The formatter's name `kvprintf` is descriptive. No symbol of the 2.8 function survives: 3.0.3's
  `_sceSnprintf` takes a size and an output callback, while this one writes through the file-level hook, and
  Sony's change log dates the snprintf family after DW4's release. The name has low confidence.
* `userarea`'s size is not known from DW4; nothing else of the file follows it.
* `kill` calls `Exit` and `topThread` calls `kprintf`, outside these files: by the member's undefined
  symbols they are the archive's `exit` and the kernel printf of `kprintf2.c`.
* `thread.c` declares `kprintf` with an `int` result where `kprintf2.c` defines `void`; the bytes do not
  depend on it.
