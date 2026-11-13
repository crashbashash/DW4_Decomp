# Save card API (`src/game/beSaveApi.cpp`)

The Bec save layer talks to the PS2 memory card through a family of request objects. Each is an
igObject subclass of `beSaveApi` (`beSvStartApi`, `beSvEndApi`, `beSvGetFreeSizeApi`,
`beSvUseCheckApi`, `beSvFormatApi`, `beSvFileFindApi`, `beSvFileMakeApi`, `beSvReadMediaApi`,
`beSvWriteMediaApi`) driven through three virtual slots:

| Slot | Role |
| --- | --- |
| 21 | start: copy the target connection (`beSvDeliver::_targetConnect`) and platform data, clear the state words `_st0`..`_st3`, set `_result = 1` and raise `g_svCardBusy` |
| 22 | poll once per frame; returns 1 when finished, 0 while a card request is in flight |
| 23 | report: copy `_result` into the `beSvDeliver` and set `_isEndOperat` |

Slot 7 of `beSaveApi` (`Gap__Bec__beSaveApi__vfunc_07`) is shared by the UseCheck, Format and
FileFind requests, which do not override it.

## Requests and libmc

Every request keeps a retry counter in the word at +60 that the registered metadata leaves out. A
poll issues one asynchronous libmc call (`sceMcGetInfo`, `sceMcOpen`, `sceMcSeek`, `sceMcWrite`,
`sceMcFlush`, `sceMcClose`, `sceMcFormat`), marks `g_svMcRequestState[n]` as issued for that
call's request number `n`, and on later frames waits for `beSvConnectCheck_Poll` to store the
`sceMcSync` result in `g_svMcRequestResult[n]`. A failed call is retried three times before the
request ends with an error result (3 card unusable, 5 no card, 7 unformatted, 9 not enough space,
12 other).

`beSvStartApi` loads `mcman.irx` and `mcserv.irx` once and runs `sceMcInit`, opens multitap port 2
and records the save version. `beSvWriteMediaApi` opens `/<dir>/<dir>` from the PS2 platform data
(`beSvPlatDataPS2::_dirName`), then for each of its two image passes seeks to
`_dataOffSet[pass]`, writes the `beSaveMemoryObj` buffer and flushes, and finally closes the file.

## Connection check

`beSvConnectCheck` runs between requests. `beSvConnectCheck_Poll` either collects the result of an
outstanding probe (`g_svConnectCheckPending`), forwards `sceMcSync` completions to the request
tables while a request owns the card (`g_svCardBusy`), or probes the next slot that has no card.
`beSvConnectCheck_ProbeSlots` refreshes `g_svSlotPresent` for the 2 direct ports or 5
multitap slots (`g_svCardSlots` maps a connection index to port/slot), and
`beSvConnectCheck_PollMultitap` debounces the multitap state over three polls into
`beSvDeliver::_useMtap`/`_chgUseMtap`. `beSvConnectCheck_FillDeliver` copies the per-slot presence,
free size and format into the deliver's `_actConnect`, `_freeSizeList` and `_formatList`.

## Buffers

`beSaveDataDeliver_AllocateData` / `beSaveDataDeliver_FreeData` manage `beSaveDataDeliver::_data`
and `_size`; `beSaveMemoryObj_Allocate` (optionally aligned, zero-filled) and
`beSaveMemoryObj_Free` manage `beSaveMemoryObj::_mem`. Both use the object's own allocator when
`g_useOwnerAllocator` is set.

## Open questions

- `g_svMultitapPollSuspended` only lets a debounce that is already counting continue; what sets it
  is not identified.
- `g_svSlotAbsent` is the value written for every connection before presence flags are copied;
  it is 0 in the image and nothing in this unit writes it.
- `igPsx2_LoadIopModule` loads an IOP module (`mcman.irx`, `mcserv.irx`).
