# Sony libpad

libpad (`src/sony/libpad/libpad.c`, `0x117b60..0x118fe0`) is a whole-file unit, built like libmtap
(`sd-prologue.md`, "libmtap is one file") with EE GCC 2.9-ee `-O2 -G0 -ffunction-sections`. It is the EE
side of padman.irx: two SIF RPC clients, a per-port/slot state table, and the pad areas padman DMAs into.

## Extent and evidence

* Every function of the range reaches the same `.bss` block, `0x55d240..0x55d500`, laid out in
  declaration order: the two `sceSifClientData` clients (`padClient`, servers `0x80000100`/`0x80000101`),
  `padState[2][4]`, the 64-byte aligned `padCommand[2][4]` command buffers and the 64-byte aligned
  128-byte RPC buffer `padRpcBuffer`.
* `.data` is one run from the `PsIIlibpad  2800` descriptor at `0x4850f8`: the descriptor, the
  `padInitialised` flag, the `padDebugPrint` switch that gates every `libpad:` message, and the
  `padStateString` / `padReqStateString` tables. libsdr's descriptor follows at `0x485148`.
* The `libpad:` strings run in code order from `0x4d2950`, then the status names; the status-name strings
  follow the functions that print, which places the two tables just before `scePadStateIntToStr`, and they
  share one `""` with `scePadStateIntToStr` / `scePadReqIntToStr` (whose `strcpy(str, "")` GCC expands
  into a load of that string's byte). The file's own `.rodata` starts at `scePadPortOpen`'s two messages
  (`0x4d29e8`); the strings ahead of them are named data (see the open questions).
* `scePadInit` (first in the file after `_send_to_iop`) calls `scePadGetModVersion`, the second to last
  function, and the commands' RPC numbers run through the whole range.
* The range ends where libsdr's `sceSdRemoteInit` starts.

## Types

`PadDmaData` is one of the two 128-byte frames padman writes into the caller's 64-byte aligned pad area;
`padGetDmaStr` returns the one with the higher `frame` count after a `SyncDCache` of both.
`PadIopCommand` is a 32-byte command `_send_to_iop` DMAs into padman's pair of command buffers.
`PadPortState` holds per port/slot the pad area, the EE's command buffer (`command`), padman's pair
(`iopCommand`) and the last DMA id. `iopCommand` has `command`'s type: `_send_to_iop` indexes it with the
counter's low bit (the `<< 5` is the element size), and `scePadPortOpen` reads it out of word 5 of the open
reply as that pointer. Every type is local to the file.

## The stores after the open RPC

`scePadPortOpen` ends in six stores (`open`, `padData`, `iopCommand`, `command`, the command's `count`,
`dmaId`) and two reads of the reply. Their order in the object is the scheduler's, and it follows from the
types, because EE GCC orders two memory accesses only when they may alias:

* Before register allocation the bases are known (`padState`, `padCommand` and `padRpcBuffer` are different
  symbols), so only two stores into `padState` of one type are ordered: `open` before `dmaId` (both `int`),
  and `iopCommand` before `command` (one pointer type). With an integer `iopCommand` that second order is
  gone: the block is scheduled differently before allocation and comes out with other registers.
* After reload every base is a hard register set more than once, so any two accesses of one alias set are
  ordered. The `int` accesses (`open`, `count`, `dmaId`, the result read) make one chain; the reply's
  pointer read belongs to the pointer stores' set, so no `int` store waits on it, its priority is low and
  it is issued just before the first store. Read as an `int` (`(PadIopCommand *)padRpcBuffer[5]`) it heads
  the `int` chain and is issued four instructions earlier.
* `count` is cleared through the pointer just stored (`padState[port][slot].command->count`): GCC forwards
  the stored value, so one address computation serves both. `padCommand[port][slot].count` computes the
  element's address again in another association, one instruction more.
* Each store names `padState[port][slot]` itself. The five address sums survive combine as five registers;
  after reload three of them become copies of the first, and the `padData` one, whose sum has its operands
  the other way round because its offset is 0, stays an `addu`.

The first three stores compile to the same bytes in three orders (`open`, `padData`, `iopCommand`; `open`,
`iopCommand`, `padData`; `padData`, `open`, `iopCommand`).

The scheduler's own account is in its dump: `-da -fsched-verbose-5` writes, for each block, the dependence
table with priorities and the ready list of every cycle, to `<file>.sched` (before reload) and
`<file>.sched2` (after).

## Open questions

* The strings ahead of `scePadPortOpen`'s messages (`sifSetDmaFailedMessage`, `versionMismatchMessage`,
  `versionReportFormat`) are named data the file references rather than literals, as in `mpc.c`, because
  the next entry sits among them.
* `"libpad: tPadDma Structure Invalid\n"` (`0x4d2970`), between `_send_to_iop`'s and `scePadInit`'s
  strings, is printed by no linked function: a function compiled there was not linked, and its body is
  unknown.
* `PadDmaData` bytes `108..111`, `115..120` and the `PadPortState` words at `20`/`24` (cleared by
  `padPortInit`) are not read on the EE side.
* The open reply's pointer could as well be read through a reply structure laid over `padRpcBuffer`; the
  bytes are the same, and nothing tells the two spellings apart.
