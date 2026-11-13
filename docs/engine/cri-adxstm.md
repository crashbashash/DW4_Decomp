# CRI ADXSTM and the PS2 file-system setup files

Four CRI ADX files between the encoder and ADXT's play-control file, each compiled as one whole file with
Sony EE GCC 2.96 at `-O2 -G0` (their rows in `units.tsv` and `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)).

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/adxstm.c` | `cri_adxstm` | `0x269c30` up to `0x26ac38` | ADXSTM: 40 file streams that read sectors of one file through cvFs into an SJ, served from the file-system thread | ADXENC's data ends at `0x4a7ef0`, where the handle counts, the server word, the retry count and the 40-handle table (`0x4a7f10` up to `0x4a8e10`) start; its one message, `adxstmf_stat_exec: can't open`, follows ADXENC's `(c)CRI` at `0x4ee460`; every function from `0x269c30` up to `0x26ac38` takes a stream handle or its data |
| `src/cri/adxdvd.c` | `cri_adxdvd` | `0x26ac38` up to `0x26aff0` | the disc setup: the `MFS` and `CDV` devices, DVCI's read mode, root folder, layer and file cache, and memory files named by address (`%08x.%08x`) | it opens with its own cvFs error callback, as the two files after it do; its strings `MFS`, `CDV`, `%08x.%08x` follow ADXSTM's message; its data, the `ADXRT  Ver.2810` build string (`0x4a8e10`) and the SRD read-mode switch (`0x4a8e40`), follow ADXSTM's table |
| `src/cri/adxhst.c` | `cri_adxhst` | `0x26aff0` up to `0x26b1d8` | the host setup: the `MFS` and `HST` devices, HTCI's open mode, root folder and file cache, and SRD's host switches | its own error callback; its own `MFS` and `HST` strings at `0x4ee4b0` (GCC merges equal strings only within a file) |
| `src/cri/adxmfs.c` | `cri_adxmfs` | `0x26b1d8` up to `0x26b248` | the memory-only setup (the `MFS` device), and ADXT's end-of-stream margin | its own error callback and `MFS` string at `0x4ee4c0`; `adxt_stm_eos` (`0x4a8e48`); ADXT's file starts at `0x26b248` with `ADXT_DumpBufStat` and the strings after `0x4ee4c8` |

## ADXSTM

A stream (`AdxStmObj`, 96 bytes, `include/dw4/cri/adxstm.h`) holds its cvFs handle, the file range in
sectors, the SJ it fills, the chunk of the read in flight, the end-of-stream sector and callback, and one
request byte each for open, close, start and stop. The API sets the request bytes under the SVM lock;
`adxstmf_stat_exec`, run on every used stream by `ADXSTM_ExecServer` from the file-system server, acts on
them, opens the bound file (measuring it when it was bound with an unknown length) and runs the read step
`adxstmf_rd_exec` on a reading stream. A read step completes the read in flight (its sectors go to the SJ's
data line, the rest of the chunk back to the free line) and starts the next one while the SJ holds less
than `minrdsz` bytes, limited by the free chunk, the end-of-stream sector, the file, `reqrdsct` and the
start's sector limit. A failed read is retried up to `adxstm_max_retry` times (negative: forever) before
the stream reports an error.

The table is split between normal handles at its start (`ADXSTMF_SetNrmlNum`) and real-time handles at
its end (`ADXSTMF_SetRtimNum`); `ADXSTM_Create` takes a normal handle for a stream whose SJ holds fewer than
256 sectors. With `adxt_srd_rmode_sw` set, a read tells SRD to run the spindle at full speed for a normal
stream and at nominal speed for a real-time one.

## The setup files

The three setup files register the cvFs devices ADX reads through and pass the setup parameters on to the
device modules: `AdxDvdFsPrm` (root folder, read mode, try count, spindle control, data pattern),
`AdxHstFsPrm` (root folder, open mode, the 64-bit host and host-lock switches) and `AdxFcachePrm` (file
list, longest name, buffer and its size), declared in `include/dw4/cri/adxfs.h`. Each file registers its
own error callback, which passes cvFs's message to `ADXERR_CallErrFunc1`.

## Open questions

- Names: `adxstmf_stat_exec` is named by its message and `ADXSTM_*`, `ADXT_SetSrdRmodeSw`/`GetStmEos`
  by earlier evidence; the rest follow CRI's API style from what each function does. The setup functions'
  `ADXPS2_*` names and the three files' names are guesses; nothing in the image names them.
- `ADXSTM_ExecServer` (`0x26a908`) has source: retail re-forms the address of `adxstmf_svr_busy` for the
  closing store, which a `volatile int` cast on that one store reproduces; the word stays plain, so
  `ADXSTM_OpenFile`, the other user of the word, is unchanged. The word is shared with the ADXM threads
  through `SVM_TestAndSet`.
- `ADXPS2_SetupDvdFs` (`0x26ac50`) has no source: it calls `memcmp` twice on a datum with itself (128 bytes
  at the ADXRT build string, 232 bytes 16 bytes into it) and drops the results, a shape with no reading yet.
- `0x4a8e44`, between the read-mode switch and `adxt_stm_eos`, is read by no function; which file owns it is
  unknown, and with it whether `ADXT_GetStmEos`/`ADXT_SetStmEos` close the memory-setup file or are a file
  of their own.
- `adxstmf_rd_exec` gives a real-time stream's spindle setting as the read-mode switch's own value (1), and
  compares the bytes read with the start's sector limit unsigned.
