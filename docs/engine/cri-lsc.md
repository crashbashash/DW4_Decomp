# CRI LSC: the link stream controller

LSC (`LSC/PS2EE Ver.2.18` at `0x4f0bc8`) plays a queue of up to 16 file ranges into one SJ stream, one after
another, through the ADX stream layer. ADXT's seamless-play functions and the Sofdec player queue files on it;
its server step reads the current entry, moves to the next when the read completes, and re-queues the entry
when looping is on. The source is `src/cri/lsc.c`. It builds with Sony EE GCC 2.96 at `-O2 -G0` as one whole
file (`cri_lsc` in `units.tsv`, its rows in `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)); every function in the range has source.

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x276e50` up to `0x277da0` | HTCI ends before it; MFCI (`MFCI/PS2EE Ver.1.09`) starts at `0x277da0`; every function in the range reads LSC's object table or reports through LSC's error function |
| strings | `0x4f0aa8` up to `0x4f0c50` | the `E0001`..`E0012` messages in code order, the build string, then the two server messages (`E0013`, `E0007`); MFCI's build string follows |
| data | `0x4abb38` up to `0x4b0370` | the status callback and its two words, the error callback, its object and 256-byte message buffer, the build-string pointer, the init count, then the 32 objects of 568 bytes |

The strings run in the order the file first uses them, init's build string between the API messages and the
server's, which is what one file compiled in retail order gives.

## Layout

An object (`LscObj`, 568 bytes) holds the in-use byte, the state (`LscStat`: stop, waiting for an entry,
executing, error), a reading flag, the loop flag, the pause flag, the SJ it feeds, the flow limits (the
minimum starts at 80% of the SJ's capacity), the queue's write and read positions and count, the stream
handle with the current entry's size, and the 16 entries. An entry (`LscStm`, 32 bytes) holds its id (one
more than the previous entry's, wrapping at `0x7FFFFFFF`), the file name and the byte sum of the name (the
server refuses an entry whose name changed after it was queued), the directory, offset and sector count, its
state (`LscStmStat`: waiting, reading, done) and the sectors read so far.

## Open questions

- Only `LSC_Create` and `LSC_ExecServer` are named by the messages; the rest are named from what they do in
  the API's style. The two empty functions init and finish call are named as hooks.
- The lock wrapper keeps its call out of tail position with an empty statement found by hand; the unlock
  wrapper, written the same way without it, tail-calls.
- `LSC_Init` reads its build-string pointer and discards it (an approved `volatile` read).
- Pending renames, held back because they rewrite callers in many Sofdec files: `0x276fb8` LSC_Destroy,
  `0x277010` LSC_EntryFname, `0x277038` LSC_EntryFileRange, `0x277210` LSC_Start, `0x277278` LSC_Stop,
  `0x2773a0` LSC_GetStat, `0x2773d0` LSC_GetNumStm, `0x277400` LSC_GetStmId, `0x277490` LSC_GetStmFname,
  `0x277528` LSC_GetStmStat, `0x2775c0` LSC_GetStmRdSct, `0x277658` LSC_SetFlowLimit, `0x2776c0`
  LSC_GetFlowLimit, `0x277768` LSC_SetLpFlg, `0x277918` LSC_Finish.
