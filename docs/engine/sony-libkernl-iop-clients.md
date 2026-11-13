# libkernl's IOP service clients: filestub, iopheap, eeloadfile

Three whole files of Sony's libkernl (release 2.8.0, `PsIIlibkernl2800`) hold the EE side of three IOP
services: the file system (`src/sony/libkernl/filestub.c`), the IOP heap (`iopheap.c`) and the module and
ELF loader (`eeloadfile.c`). Each call packs its arguments into the file's one send buffer and makes a SIF
RPC to the service's server; the reply comes back in a receive buffer. They build with the Sony library
compiler (`ee-gcc-2.9`, `-O2 -G0 -ffunction-sections`, see [sd-prologue](sd-prologue.md)) and include the
SIF types from `include/dw4/sony/sif.h`.

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
  `"all"` follow.

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
  with the right `$gp`.
* `eeloadfile`'s requests share one 512-byte buffer (`LfSendData`): a path and an argument block for
  the module and ELF calls, an address and word width for `sceSifGetIopAddr`/`sceSifSetIopAddr`.
  Reading it through a typed local pointer instead of the global moves the address into a saved
  register and changes those two functions.

## Open questions

* Functions still without source, linking from retail: `_sceFs_Rcv_Intr`, `_sceFs_Poff_Intr`,
  `sceFsInit`, `sceOpen`, `sceLseek`, `sceRead`, `sceWrite`, `sceIoctl`, `sceLseek64` and
  `sceSifInitIopHeap`. `_sceFs_Rcv_Intr`'s switch table means the file's `.rodata` is not yet the
  file's own.
* The data is still referenced as externs, not the files' own statics; the layout above says they are
  the files' own `.data` and `.bss`.
* The request structures' field names follow what each call stores; Sony's own names for them are
  not known.
