# libkernl's SIF command and RPC files

libkernl's SIF layer is two whole files, `src/sony/libkernl/sifcmd.c` (`0x10d168..0x10d940`) and
`src/sony/libkernl/sifrpc.c` (`0x10d940..0x10e9d0`), compiled by ee-gcc 2.9 at `-O2 -G0 -ffunction-sections`.
They share `include/dw4/sony/sif.h`, which holds the packets, the handler tables and the RPC client, server
and queue blocks. Each file defines its own `.data` and `.bss`.

## Extents

The SDK 3.0.3 `libkernl.a` (docs/engine/sd-prologue.md) has the same two members. `sifcmd.o`'s `.text` is
`0x7d8` bytes and starts with `_set_sreg`, which lands at `0x10d168` and runs to `0x10d940`; its functions
are retail's in the same order (`_set_sreg`, `_change_addr`, `sceSifGetSreg`, ..., `isceSifSendCmd`,
`_sceSifCmdIntrHdlr`, `sceSifWriteBackDCache`). `sifrpc.o` follows it with `sceSifInitRpc` and ends with
`sceSifRpcLoop`; DW4's copy is shorter than 3.0.3's (`sceSifBindRpc` and `sceSifCallRpc` are a few words
smaller), and the next object, `filestub.o`, begins at `_sceFsIobSemaMK` (`0x10e9d0`).

The data agree. `sifcmd.o`'s `.bss` is `0x300` bytes with `sif0_handleid` at `0xd4`, the state block at
`0xd8` and the software registers at `0x280`: retail `0x555fd4`, `_sif_cmd_data` `0x555fd8` and `sifSregs`
`0x556180` from a base of `0x555f00`. `sifrpc.o`'s `.bss` holds the client packets, the two reply pools and
the state block at `0x0`, `0x800`, `0x1000` and `0x1800`: retail `0x556200`, `0x556a00`, `0x557200` and
`_sif_rpc_data` `0x557a00`. Each file's `.data` is its init flag: `_cmd_init_check` (`0x481e68`) and
`_sceSifInitCheck` (`0x481e70`).

## Behaviour

* sifcmd keeps a system and a user handler table; a command id with the top bit set indexes the system
  table. `sceSifAddCmdHandler` stores the caller's `$gp` with the handler. `_set_sreg` and `_change_addr`
  are the handlers `sceSifInitCmd` installs for the IOP's software-register writes and its new receive
  address. `sceSifSendCmd` and `isceSifSendCmd` are `_sceSifSendCmd` with mode 0 and 1.
* `_sceSifCmdIntrHdlr`, the SIF0 DMA-completion handler (`static`, as in Sony's object), copies the command
  the IOP left in the receive buffer into a local packet, clears the buffer's size word, re-arms the channel
  and runs the command's handler on the `$gp` it was registered with.
* `sceSifWriteBackDCache` is Sony's own assembly in the C file (its local labels are in `sifcmd.o`'s symbol
  table) and is carried as it was.
* sifrpc's client packets carry `rec_id = index << 16 | 5` while in use; a reply goes to the matching
  client-table packet when bit 2 is set (`_sceRpcGetFPacket2`), otherwise to the next reply-pool packet in
  turn (`_sceRpcGetFPacket`). Replies the IOP cannot take yet are retried from a timer alarm
  (`_alarm_bind`, `_alarm_rdata`). An IOP call to an EE server is queued by `_request_call` and run by
  `sceSifExecRequest`, which sends the result and the reply in one DMA chain unless the caller asked for
  `rmode`.

## Types and shapes

Retail's scheduling pins several field types, through type-based aliasing:

* the reply packet (`sceSifRpcRendPkt`) holds the echoed packet address and client as `unsigned int`, and
  so do the other-data addresses (`src`, `dest`) on both sides;
* `sceSifServeData` keeps the IOP's packet and receive buffer as `unsigned int`, `buff`/`cbuff` as
  `char *`, and its `link`/`next` chains (and the queue's `link` and `end`) as `void *`;
* a packet of the client pool (`sceSifRpcPacket`) is the RPC header and a union of the three requests
  (bind, call, other-data) and a raw body, since a pool packet carries whichever request its client
  sends. The three request layouts are `sceSifRpcBindReq`, `sceSifRpcCallReq` and
  `sceSifRpcOtherDataReq`; the per-command packets the server-side handlers take are the header and one
  request. `sceSifGetOtherData`, `sceSifBindRpc` and `sceSifCallRpc` write through the union.
* `isceSifSetDChain` and `sceSifSetDChain` are declared returning `int`, which fixes the register of
  the command-id test in `_sceSifCmdIntrHdlr`.

Other spellings move loads above stores in `_request_bind`, `_request_rdata`, `_request_call`,
`sceSifRegisterRpc` and `sceSifExecRequest`.

`_sceSifCmdIntrHdlr` reads the packet header through a `volatile sceSifCmdHdr *` that first points at the
IOP's receive buffer and is then re-pointed at the local copy. The buffer is DMA memory the IOP writes,
and the keyword keeps the size read (`lbu`, then `andi`) and the three reads of the command id; without it
the function is three words shorter. One `int` holds the packet size, its quadword count and the command
index, and the `$gp` each handler call swaps in is declared inside its own branch: with one `$gp` variable
shared by both branches the block has three local values, and gcc's local allocator's three-value case
orders them by quantity number, which gives the new `$gp` the register retail gives the table base.

## Open questions

* `sceSifCallRpc` matches only with the pool packet's body as a union. Retail needs the packet stores in
  alias set 0 (what any union access gets in this compiler) and the `rpc_id` read outside it; the statement
  order is `pkt_addr`, `serve`, `client`. That the pool packet is a union is Sony's type or a spelling of
  it is not known: the same effect with plain per-command packets needs the two client loads in set 0,
  and none of 144 combinations of field types, `volatile` on those accesses or `-fno-strict-aliasing`
  (which breaks twelve other functions) reproduces it. The handlers (`_request_rdata`, `_request_bind`,
  `_request_call`) keep plain per-command packets; giving them the union costs words.
* `_request_end`'s switch keeps an empty `0x8000000b` case that only orders its compares; the note is in
  the source.
* The `volatile` on `_sceSifCmdIntrHdlr`'s header pointer and the `__asm__("sync.l; ei")` of its tail are
  approved rows ([source approvals](source-approvals.md#sony-gp-and-syscall-asm)); Sony's own spelling of
  the buffer read is not known.
