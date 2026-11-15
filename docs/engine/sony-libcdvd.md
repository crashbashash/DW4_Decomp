# Sony libcdvd: the EE side of cdvdman

libcdvd (`0x116138..0x117b60`) is the EE client of the IOP's `cdvdman` and its RPC servers: it sends each disc
and drive command as a SIF RPC on a channel, guards the channel with a semaphore, and reports a finished
command to the game from a callback thread. DW4's release is 2.8.0 (the descriptor `PsIIlibcdvd 2800` at
`0x483540`). It is six whole-file units of `include/dw4/sony/libcdvd.h`, built with EE GCC 2.9-ee and the 2.10
assembler (`ee-gcc-2.9-as210`, `-O2 -G0 -ffunction-sections`). Each unit defines its own data.

## Files and evidence

| File | Extent | Contents |
|---|---|---|
| `src/sony/libcdvd/cdvd000.c` | `0x116138..0x117690` | the callbacks and their thread, the channel set-up and exit, search, the prechecks, sync, `sceCdInit` and the two disk-ready calls |
| `src/sony/libcdvd/sceCdRead.c` | `0x117690..0x117870` | `sceCdRead` |
| `src/sony/libcdvd/sceCdSeek.c` | `0x117870..0x117940` | `sceCdSeek` |
| `src/sony/libcdvd/sceCdGetError.c` | `0x117940..0x1179d8` | `sceCdGetError` |
| `src/sony/libcdvd/sceCdBreak.c` | `0x1179d8..0x117a90` | `sceCdBreak` |
| `src/sony/libcdvd/sceCdMmode.c` | `0x117a90..0x117b60` | `sceCdMmode` |

* SDK 3.0.3's `libcdvd.a` names the units: `cdvd000.o` is one source file (`eecdvd.c`) holding the whole of
  `cdvd000.c`'s range, and `cdvd005.o`, `cdvd010.o`, `cdvd015.o`, `cdvd018.o` and `cdvd036.o` hold one command
  each. The functions of `cdvd000.o` are in retail's order, with the static ones named from the member's symbol
  table (`cmd_sem_init`, `cdvd_exit`, `PowerOffCB`, `_sceCd_cbLoop`, `_sceCd_Poff_Intr`, `_sceCd_ncmd_prechk`,
  `_sceCd_scmd_prechk`, `_sceCdSC`, `sceCdDiskReady_old`, `sceCdDiskReady`, `sceCdInitEeCB`,
  `sceCdLayerSearchFile`, `sceCdSearchFile`). Several of the functions are byte-identical to 3.0.3's with the
  linker-filled words masked. The member's `.mdebug` has local symbols but no type information.
* `cdvd000.c`'s `.data` (`0x483540`), `.bss` (`0x55cf80`) and `.rodata` (`0x4d2758`) are the file's own, as are
  `sceCdRead.c`'s `.rodata` (`0x4d2928`) and `sceCdMmode.c`'s `.data` (`0x4850e8`: the RPC number and the two
  buffer sizes `rpc_mmode`, `outcnt_mmode` and `incnt_mmode`, named as `cdvd036.o` names them).

## How the library works

* Two RPC channels to cdvdman: the N-command channel (disc commands: search, read, seek, disk-ready) and the
  S-command channel (drive commands: error, break, media mode), each with its own send buffer, receive buffer,
  client block and semaphore, plus a search channel, an initialisation channel and a disk-ready channel. The
  semaphore ids, the command in flight (`sceCdCbfunc_num`), the callback reason (`sceCdCbfunc_number`), the busy
  flag (`_sceCd_c_cb_sem`) and the read mode are shared words. `_sceCdSC` hands a channel's semaphore, buffers
  and client to other libraries by command code (`0x8001..0x8004` the N channel, `0x8011..0x8014` the S
  channel).
* A command takes its channel with `_sceCd_ncmd_prechk` or `_sceCd_scmd_prechk`, which polls the semaphore
  (`PollSema` returns the id on success, so the test is `sem != PollSema(sem)`), reports the command that holds
  the channel when a debug print is on, and refuses a second command; the command number it is called with
  only identifies the caller in that report.
* Completion: cdvdman calls `_sceCd_cd_callback` at interrupt time (a read ends through `_sceCd_cd_read_intr`,
  which first copies the unaligned head and tail of the transfer from the buffers the IOP filled to the
  caller's buffer, cached and uncached), which signals the channel's semaphore and wakes `_sceCd_cbLoop`. That
  thread, created by `sceCdInitEeCB`, calls the game's callback (`sceCdCallback`) with the finished command's
  number on the `$gp` `sceCdCallback` recorded. The callback reasons are the SDK's (`SCECdFuncRead`,
  `SCECdFuncSeek`, `SCECdFuncBreak`) and an exit code with no SDK name (`CD_FUNC_EXIT`, 11).
* A power-off command from the IOP (SIF command `0x80000012`) runs the game's `sceCdPOffCallback` handler
  through `_sceCd_Poff_Intr`, again on the `$gp` recorded when the handler was set.
* `sceCdInit` takes a mode (`SCECdINIT`, `SCECdINoD`, `SCECdEXIT`): it resets the six bind flags, calls
  the initialisation server, reads the two IOP versions and a status word (a version below 2.00 returns 2,
  a status of 254 turns the debug print on), then either shuts the channels down (`SCECdEXIT`) or creates the
  semaphores and installs the power-off handler.
* `sceCdRead` writes back the cache for the buffer (unless the read-mode bit says not to), fills the
  command block (`lbn`, sector count, buffer, `sceCdRMode`, the head-and-tail block and a position word) and
  makes the RPC without waiting; the buffer size comes from the data pattern (2048, 2328 or 2340 bytes a
  sector).

## Shapes the bytes require

* The shared words are `volatile`. The reason is two-fold and spelled out under
  [#sony-libcdvd-shared-state](source-approvals.md#sony-libcdvd-shared-state): `sceCdCbfunc_num` and
  `sceCdCbfunc_number` keep real reloads (retail stores the value and reads it back with no call between),
  and the semaphore ids and `_sceCd_c_cb_sem` and `Init_seq` decide whether an access may stand in a delay
  slot, which is the signature in retail's `lw a0,_sceCd_ncmd_semid; jal PollSema; nop`.
* The six units build with the 2.10 assembler: when a load or store is `volatile`, EE GCC 2.9 leaves the delay
  slot of the following `jal` to the assembler, 2.10 moves the access before the call into the slot and the
  release's own assembler leaves a `nop`. Retail shows both on the same variable (`PollSema`'s unfilled slot
  and `sceCdSeek`'s filled one). With every `volatile` removed the two assemblers give identical code, so the
  assembler matters only for these accesses.
* The two `$gp` swaps (`_sceCd_cbLoop`, `_sceCd_Poff_Intr`) are one `asm` statement: `move %0,$28; lw $28,%1`,
  with the restore a second statement. Retail has `move s0,gp; lw gp,X` with no register move into `gp`, so
  `SetGp()` does not give it.
* `sceCdInit`'s switch has the exit case first and the other modes sharing one tail that falls to a shared
  `return ret`; that gives retail's compare tree and keeps the `move v0,s0` out of the exit block. The six
  bind resets are written in the one order that matches (found by trying all 720 orders of the binds with
  six placements of the other stores): the scheduler issues the last of a run of independent stores first,
  so `_icmd_bind` comes out first, and `_it_bind`'s store comes last because its base register stays for the
  loop's reset. The line carries a note.
* `scePrintf` is declared `void`, as Sony's `eekernel.h` has it, which leaves the three debug prints of the
  search call as plain sequential `if`s. The uncached reads use `UNCACHED` and `UNCACHED_WORD`.

## Open questions

* The `volatile` on the semaphore ids, the read mode, `Init_seq` and `sceCdPoffCbfunc_num` is fixed by the
  bytes but changes no value the program reads (only slot filling or store order); the case for the keyword is
  the signature above and the approved timer and `VSync2` words that behave the same way. `_sceCd_rcmd_semid`
  and `_sceCd_ee_read_mode`, which interrupt code never touches, are the weakest members.
* No plain-C spelling of the `$gp` swap matches: the library's `GetGp()` with a clobber reloads the callback
  pointer and comes out four bytes long, and in `_sceCd_Poff_Intr` the `lui` of the saved-`gp` address moves
  after the `$gp` save even with a helper local.
* The callback reason `CD_FUNC_EXIT` and the command numbers of `_sceCd_*_prechk` are named from their use;
  Sony's names are not known.
* `sceCdDiskReady_old` and `sceCdDiskReady` differ by RPC server (`0x8000059a` and `0x8000059c`); which
  release of cdvdman each belongs to is not known.
