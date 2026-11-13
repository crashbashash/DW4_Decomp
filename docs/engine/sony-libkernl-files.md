# Sony libkernl: klib, glue, cache, intr, thread, deci2, tty

The first run of Sony's libkernl (`0x10aac0..0x10c7ac`) is seven archive members laid out in the order
the SDK's `libkernl.a` holds them. The SDK 3.0.3 archive (later than DW4's 2.8 release) gives each
member's function names, their order and offsets, and its local data; every C member below starts
where the previous one's `.text` ends, rounded to 8 bytes.

| file | extent | what it holds |
| --- | --- | --- |
| `src/sony/libkernl/klib.S` | `0x10aac0..0x10b360` | the system-call stubs ([assembly sources](assembly-sources.md)) |
| `src/sony/libkernl/glue.c` | `0x10b360..0x10b730` | newlib's system-call glue and `VSync` |
| `src/sony/libkernl/cache.c` | `0x10b730..0x10b9ac` | data-cache write-back and invalidation by range |
| `src/sony/libkernl/intr.c` | `0x10b9b0..0x10bbe0` | INTC and DMAC mask calls |
| `src/sony/libkernl/thread.c` | `0x10bbe0..0x10c030` | handler-side thread requests and `DelayThread` |
| `src/sony/libkernl/deci2.c` | `0x10c030..0x10c264` | the DECI2 calls |
| `src/sony/libkernl/tty.c` | `0x10c268..0x10c7ac` | the DECI2 console behind `write` and `read` |

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

## thread.c

`topThread` (static), `InitThread`, `iWakeupThread`, `iRotateThreadReadyQueue`, `iSuspendThread`,
`DelayThread`, `_DelayThreadHandler` (static). An interrupt handler cannot wake, suspend or rotate
the thread it interrupted through the kernel, so it puts the request in a 512-entry ring (`topArg`)
and signals `topSema`; `topThread`, created by `InitThread` at top priority on its own 1 KB stack,
carries the requests out. `DelayThread` waits on a semaphore a timer alarm signals. The member's
`.data` `topId` is `0x481e58`; its `.bss` (`stack`, `topSema`, `topArg`) is `0x555280..0x555a8c`;
its strings (the internal-error message and the `"DelayThread"` semaphore tag) are `0x4d2410`.
DW4's release has no `StartThread`, which the 3.0.3 member adds after `DelayThread`.

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
polls, is volatile for the same reason. The file ends at `0x10c7ac`; the module-map block row after
it starts at `0x10c7b0`.

## Open questions

* `QueryIntrContext` (`0x10b9b0`) has no source: it is one `mfc0` of the Status register, which
  C cannot write without inline assembly. It links from retail inside `intr.c`'s extent.
* `userarea`'s size is not known from DW4; nothing else of the file follows it.
* `kill` calls `Exit` and `topThread` calls `kprintf`, outside these files: by the
  member's undefined symbols they are the archive's exit and kernel printf.
