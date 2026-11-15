# libkernl's IOP service clients: filestub, iopheap, eeloadfile

Three whole files of Sony's libkernl (release 2.8.0, `PsIIlibkernl2800`) hold the EE side of three IOP
services: the file system (`src/sony/libkernl/filestub.c`), the IOP heap (`iopheap.c`) and the module and
ELF loader (`eeloadfile.c`). Each call packs its arguments into the file's one send buffer and makes a SIF
RPC to the service's server; the reply comes back in a receive buffer. They build with the Sony library
compiler (`ee-gcc-2.9`, `-O2 -G0 -ffunction-sections`, see [sd-prologue](sd-prologue.md)) and include the
SIF types from `include/dw4/sony/sif.h`. Each file defines its own `.data`, `.bss` and `.rodata`.

## Extents and evidence

| File | Range | First function |
|------|-------|----------------|
| `filestub.c` | `0x10e9d0..0x1120e8` | `_sceFsIobSemaMK` |
| `iopheap.c` | `0x1120e8..0x112638` | `sceSifInitIopHeap` |
| `eeloadfile.c` | `0x112638..0x113398` | `_lf_bind` |

* The SDK 3.0.3 `libkernl.a` has the members `filestub.o`, `iopheap.o` and `eeloadfile.o` with these
  functions in this order. DW4's 2.8 copies lack a few of 3.0.3's (`use_iob_cnt`, `sceFsSifCallRpc`,
  `sceFsSetIopBuf`, `sceFsSetIopPrio`), and their sizes differ by a few words, but the order is the same,
  which names the short wrappers no byte match reaches (`sceRemove`, `sceSifFreeIopHeap`,
  `sceSifLoadModule`, ...).
* `filestub.c` starts after `sceSifRpcLoop`, the end of `sifrpc.o`, and `eeloadfile.c` ends before
  `sceSifResetIop`, the start of `iopreset.o`.
* The data runs in the same order and with the same offsets as the 3.0.3 members: `filestub`'s `.data`
  from `_sceFs_q` (`0x481e78`) to `_fswildcard` (`0x481f10`), then `iopheap`'s `_ih_bind` (`0x481f18`),
  then `eeloadfile`'s `_bind_check` and `_lfwildcard` (`0x481f20`); `.bss` from `rcv_adr`
  (`0x557a40`) through `sceCbPoff_Gp` (`0x559240`), `_ih_cd` (`0x559280`) through `_lih_data`, and
  `_lf_senddata` (`0x559440`) through `_lfversion` (`0x559668`). `.rodata`: `filestub`'s
  `_sceFs_Rcv_Intr` switch table and wildcard `"...."` end at `0x4d2690`, `eeloadfile`'s wildcard and
  `"all"` follow. Every one of these is the file's own definition: the switch table is the file's
  `.rodata` because `_sceFs_Rcv_Intr`'s `switch` is compiled in it.

## Shapes

* Every file-system call takes the send buffer with `_sceFsWaitS`, starts `sceFsInit` if the system is
  not up, sends, and reads the first reply word through the uncached segment, since the IOP writes it by
  DMA. A zero there means the request was not taken; otherwise the caller waits on a semaphore the reply
  handler signals and returns the result the handler wrote.
* `_sceCallCode` serves every call that sends only a path (remove, rmdir, dopen, deldrv, chdir, umount).
* `sceSymlink` and `sceReadlink` take the send buffer under rename's command number, and `sceReadlink`
  sends a rename-sized request; retail does this, so the source does too.
* `_fs_version` and `_lf_version` compare the server's four version characters with libkernl's own
  (`"2800"` inside `__ps2_klibinfo__`) and accept a `"...."` wildcard.
* `scePowerOffHandler` records `$gp` beside the handler with an approved `sw $28`
  ([source-approvals](source-approvals.md#sony-gp-and-syscall-asm)), so `_sceFs_Poff_Intr` can call it
  with the right `$gp`. `_sceFs_q`, the table of in-flight requests the reply handler and the callers
  share, is `volatile`.
* The calls that take an `SCE_NOWAIT` flag in the mode word (`sceRead`, `sceWrite`, `sceLseek` and the
  other request calls that can return before the reply) test it a second time after the reply is checked;
  that test is spelled `(short)mode & SCE_NOWAIT`, which keeps gcse from reusing the first test's result,
  as retail's two separate `andi`s show. `sceIoctl` has no such form: it always waits for the reply, and
  the local that holds the constant 1 for that wait is the register the switch compares the request
  against.
* `_sceFs_Rcv_Intr` stores the selected receive buffer index straight into `ee_retbuf_sel` and indexes
  the buffer table by reading it back; a separate local for the index changes the prologue's register
  use and the data-read loop's end pointer.
* `eeloadfile`'s requests share one 512-byte buffer (`LfSendData`): a path and an argument block for
  the module and ELF calls, an address and word width for `sceSifGetIopAddr`/`sceSifSetIopAddr`.
  Reading it through a typed local pointer instead of the global moves the address into a saved
  register and changes those two functions.
* `sceSifInitIopHeap` clears `_ih_bind` inside the branch that found the server, before the `break`;
  with the store in a block of its own the scheduler places the `move v0,zero` between the `lui` and the
  `sw`.

## Open questions

* The constant-1 variable of `sceIoctl` is a byte-only spelling: 3.0.3 has the same `li s5,1` and
  `beql s1,s5`, so Sony's source had a variable there with exactly two references, but which one it
  was cannot be recovered. A plain `sent = 1`, `sema = 1`, `i = 1` and real uses of the flag
  (`*ip0 = 1`, `param.maxCount = 1`) all land in other registers. The flag is written as a wait flag
  with a note at its declaration.
* The `(short)mode` second flag test of `sceRead`, `sceWrite` and `sceLseek` is likewise a spelling the
  bytes require; Sony's reason for a short-typed test is not known.
* The request structures' field names follow what each call stores; Sony's own names for them are
  not known.
