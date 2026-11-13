# Sony libdma: one file

libdma (`src/sony/libdma/libdma.c`, `0x102c98..0x1034dc`) is a whole-file unit built with EE GCC 2.9-ee and
the 2.10 assembler (`ee-gcc-2.9-as210`, `-O2 -G0 -ffunction-sections`). It drives the EE DMA controller:
it resets the channels and the controller's environment, starts transfers in normal, chain and interleave
mode, waits on them, and pauses and restarts a channel.

## Extent and evidence

* SDK 3.0.3's `libdma.a` is one object, `libdma.o`, with the same functions in the same order:
  `WaitDma`, `WatchDma`, `CheckAddress`, `memclr`, `sceDmaGetChan`, `sceDmaReset`, `sceDmaPutEnv`,
  `sceDmaGetEnv`, `sceDmaPutStallAddr`, `sceDmaSend`/`SendN`/`SendI`, `sceDmaRecv`/`RecvN`/`RecvI`,
  `sceDmaSync`, `sceDmaWatch`, `sceDmaPause`, `sceDmaRestart`. The first four are `static` there.
* `.data` starts at `0x481c60` with the library descriptor `"PsIIlibdma  2800"` and the ten channel
  base addresses (`dch`); `.rodata` starts at `0x4d1e70` with `"libdma: sync timeout\n"`, then the
  channel-clear table and the `D_CTRL` STS/STD/MFD code tables, at the offsets `libdma.o` puts them.
  `sceDmaCurrentEnv` (`0x555050`) is the file's `.bss`.
* The string is a literal in `WaitDma`/`WatchDma`, and GCC writes a literal when it compiles the
  function but a file-scope table where it is defined, so the tables are defined after those two
  functions to keep retail's order.

## Types

`sceDmaChan` is a channel's register block (`chcr`, `madr`, `qwc`, `tadr`, `as0`, `as1`, `sadr` at
16-byte spacing); `chcr` is a union of the `tD_CHCR` bit fields and the whole word, because the transfer
starts set fields while `sceDmaPause`/`sceDmaRestart` save and restore the word. `sceDmaEnv` is the
controller environment `sceDmaPutEnv` writes to `D_CTRL`, `D_PCR`, `D_SQWC`, `D_RBOR` and `D_RBSR`.

* `sceDmaReset` clears each channel through a local pointer: through `dch[i]` each time, GCC reloads the
  pointer after the word store to `chcr`.
* `WaitDma`, `WatchDma` and `sceDmaPause` read the channel through `volatile` word accesses: the
  structure itself is not `volatile`, since the start functions' bit-field stores must stay merged
  read-modify-writes.
