# Sony libkernl: IOP reset, kernel patches, timer and alarms

`0x113398..0x116138` is ten files of Sony's libkernl, in the order of the members of the SDK `libkernl.a`
(release 3.0.3 shown in [the Sony compiler](sd-prologue.md#sonys-prebuilt-libraries); DW4's 2.8.0 keeps the same
members and function order). Each C file is a whole-file unit under `ee-gcc-2.9` `-O2 -G0 -ffunction-sections`.
The member's symbol table gives the file's functions, its `static` ones and its data; the data addresses come
from the retail relocations.

| file | range | contents |
|---|---|---|
| `src/sony/libkernl/iopreset.c` | `0x113398..0x113678` | `sceSifResetIop`, `sceSifIsAliveIop`, `sceSifSyncIop`, `sceSifRebootIop`; strings `"rom0:UDNL "` and the too-long message at `0x4d26a0`, `resetPacket` in `.bss` |
| `src/sony/libkernl/tlbfunc.c` | `0x113678..0x113bc0` | TLB refill/debug hooks, the TLB patch (`tlbsrc`, `SysEntry_tlbfunc`), the TLB system calls, `InitTLB`, `InitTLB32MB` (static); the `# TLB` strings at `0x4d26d0` |
| tlbtrap (assembly) | `0x113bc0..0x113f20` | `_kTLBException`, `_kExitTLBHandler`, `_kDebugException`: kernel-mode exception entries, no C |
| `src/sony/libkernl/diei.c` | `0x113f20..0x113f90` | `DIntr`, `EIntr` |
| `src/sony/libkernl/initsys.c` | `0x113f90..0x114220` | `_InitSys` and the start-up it runs: the two semaphores, finding the kernel's system call table |
| `src/sony/libkernl/libosd.c` | `0x114220..0x1143a0` | the ExecPS2 kernel patch (`osdsrc`, `SysExecPS2Entry`), applied when `PatchIsNeeded` |
| `src/sony/libkernl/exit.c` | `0x1143a0..0x114640` | `ExecPS2`, `LoadExecPS2`, `Exit`, `ExecOSD` and `SetArg`; its one `.rodata` byte is the empty filename at `0x4d2750` |
| `src/sony/libkernl/alarm.c` | `0x114640..0x114780` | the alarm kernel patch (`srcfile`, `eenull`, `SysEntry_alarm`) |
| `src/sony/libkernl/timer.c` | `0x114780..0x115ae8` | timer 2: system time, 128 counters with handlers, the alarm list (`g_Timer`, `timerCounters`) |
| `src/sony/libkernl/timeralarm.c` | `0x115ae8..0x115ed8` | 64 one-shot alarms over the counters (`timerAlarms`, `freeAlarms`) |
| `src/sony/libkernl/iopnotify.c` | `0x115ed8..0x116138` | the IOP reboot notify handlers |

## The kernel patches

`tlbfunc.c`, `initsys.c`, `libosd.c`, `alarm.c` and `exit.c` each carry their own `static` copies of the
same helpers: `setup` (system call 116, SetSyscall), `Copy` (system call 90), `kCopy` (the copy loop that
`setup` installs as call 90, so `Copy` runs it in kernel mode) and `GetEntryAddress` (system call 91, the
kernel's current handler). A patch file installs `kCopy`, copies its kernel code into kernel memory, flushes the
caches, and installs or restores the calls of its `SysEntry` table (`SyscallEntry` in `include/dw4/libkernl.h`).
Their symbols carry the file as a suffix (`Copy_tlbfunc`, `setup_libosd`); the unit row of a file that begins
with one names it in `symbol`. `exit.c`'s `kCopy` copies bytes; the others copy words.

The kernel code each file copies is a byte array it declares `extern`: `tlbsrc` (`TLB_PATCH_SIZE`, copied to
`0x80075000`), `osdsrc` (`OSD_PATCH_SIZE`, `0x80074000`) and `srcfile` (`ALARM_PATCH_SIZE`, `0x80076000`), and
`alarm.c` also copies `eenull` (`EENULL_SIZE`) to `0x82000`. Their calls and literals point at the addresses
they run at and nothing in the image calls into them, so the function inventory keeps the three patches as
data through `data` rows in `config/SLUS-20836/extent-overrides.tsv`.

`initsys.c` installs `kFindAddress` (call 131) and `kCopy` (call 90), then searches kernel memory for the two
handler addresses: the table is where both sit at their own slots (`0x20c` and `0x168` above its start).
`GetSystemCallEntry` reads a slot of it.

`alarm.c` patches only when timer 3's compare interrupt is off, the sign of a kernel without built-in alarms.

## The timer

A counter's id is its 64-byte-aligned address shifted up by 4 with a 10-bit key below it, so a stale id is
refused. `SetNextComp` sets the compare register for the first alarm due and folds alarms due within 200 us of
it into the same interrupt. `iGetTimerSystemTime` and `GetTimerSystemTime` read the system time with the same
inline sequence, which counts a pending overflow before the interrupt does. `timer.c`'s counter and state
fields that other code changes behind the compiler (`key`, `uniqueKey`, `usedCounters`, `current`) are
`volatile`, which the reloads after each store show. An alarm of `timeralarm.c` returns its id as its own
16-byte-aligned address shifted up by 4 with the counter id's low byte.

`DIntr`'s disable loop is one `asm` statement holding `di`, `sync.p` and `mfc0`, Sony's `DI()` text joined into
one. EE GCC pads a loop whose backward branch closes fewer than five counted instructions with `nop`s before the
branch, and counts an `asm` statement as one instruction however many lines it holds: retail's two pad `nop`s
fix the loop as one statement, `li` and `and`. The statement's `volatile` keeps it in the loop; the first
`mfc0` needs none. Built with the 2.10 assembler and without `-ffunction-sections`, the same source gives SDK
3.0.3's `diei.o` byte for byte; the 2.9 assembler leaves `jr`'s delay slot empty, which makes retail's 84 bytes.

## Open questions

* The TLB system-call stubs (`PutTLBEntry`, `iPutTLBEntry`, `iSetTLBEntry`, `GetTLBEntry`, `iGetTLBEntry`,
  `ProbeTLBEntry`, `iProbeTLBEntry`, `ExpandScratchPad`) are `li $3,N; syscall` pairs like the other helpers but
  have no source: writing them would add inline assembly. They link from retail.
* `SetT2` writes the timer from kernel mode through `eret`, and `cbTimerHandler`, the timer interrupt, has no
  source yet.
* tlbtrap's three exception entries are assembly with no approved `.S` row.
