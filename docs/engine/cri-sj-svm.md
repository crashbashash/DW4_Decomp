# CRI SJ and SVM: stream joints, their IOP side, and the server manager

Six CRI files that end the ADX block, each compiled as one whole file with Sony EE GCC 2.96 at `-O2 -G0`
(their rows in `units.tsv` and `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).
An SJ (stream joint) is the CRI libraries' byte pipe: an object whose first word is the interface table
`SfdSjVtbl` (`include/dw4/cri/sfdsj.h`), with a free line (0) and a data line (1) from which chunks are got and
to which they are put or given back. SJRBF and SJUNI are two SJ kinds on the EE; SJRMT drives SJs on the IOP;
SJX links an EE SJ line to an IOP SJ; SVM is the critical section and the server table the CRI threads run.

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/sjrbf.c` | `cri_sjrbf` | `0x27bc38` up to `0x27c778` | SJRBF: a ring buffer whose extra area past the end mirrors the start, 256 objects of 64 bytes | SJMEM ends with `SJMEM_GetBufSize` at `0x27bc30`, whose string `E2004090248` at `0x4f1d48` is followed by SJRBF's UUID (`0x4f1d78`), `SJRBF Error` and `E2004090201` to `E2004090220` in function order; its table, count and objects run from `0x4b5630` to `0x4b9668` |
| `src/cri/sjuni.c` | `cri_sjuni` | `0x27c778` up to `0x27d470` | SJUNI: four lines that are lists of chunks, the list nodes drawn from the caller's work area, 64 objects of 48 bytes | its UUID at `0x4f2028`, `SJUNI Error` and `E2004090261` to `E2004090282` in function order; its table, count and objects run from `0x4b9668` to `0x4ba2a0` |
| `src/cri/sjutl.c` | `cri_sjutl` | `0x27d470` up to `0x27d780` | `SJ_SplitChunk` and the tags (a 7-character id, a 7-digit hex length, the content from byte 16) that `SJ_MakeTag`, `SJ_GetTagContent` and `SJ_SearchTag` write and read | no strings; its hex digit and digit-value tables at `0x4ba2a0` and `0x4ba2b8` follow SJUNI's objects, and SJRMT's build-string word at `0x4ba478` follows them |
| `src/cri/sjrmt.c` | `cri_sjrmt` | `0x27d780` up to `0x27dba8` | SJRMT: create, destroy and the SJ calls for SJs on the IOP, one DTX remote call each (numbers 32 to 42) | `SJRMT Ver.1.03` at `0x4f2468`, its pointer at `0x4ba478` read by `SJRMT_Init`, the init count at `0x4ba47c`; the send, receive and UUID buffers at `0x5707c0`, `0x5708c0`, `0x570780` |
| `src/cri/sjx.c` | `cri_sjx` | `0x27dba8` up to `0x27e0d0` | SJX: 32 joins of an EE SJ line to an IOP SJ; DTX's send callback gathers each join's waiting chunks for the IOP (at most 128 per exchange) and its receive callback puts back the chunks the IOP returns | `SJX Ver.1.08` at `0x4f2498` (pointer `0x4ba480`), then `E0100301`, `E0100302` (`SJX_Init`) and `E0100401` (`SJX_Create`); its data runs from `0x4ba484` to the 2256-byte DTX work area ending at `0x4baff0` |
| `src/cri/svm.c` | `cri_svm` | `0x27e0d0` up to `0x27ede0` | SVM (`SVM/PS2EE Ver.1.54`): the lock and unlock callbacks with a lock type per caller, error reporting, the per-type server table (8 types, 6 functions each), the border callbacks, the test-and-set hook and the callbacks around a vsync frame | its build-string pointer at `0x4baff0` follows SJX's work area; its messages `2103102:SVM:svm_unlock` to `1071302:SVM_ExecSvrFuncId` run in function order; `svm_reset` (`0x27eb68`) clears the vsync-frame callbacks the last functions (`0x27ed50` to `0x27edb0`) set and run, which ends the file at `0x27ede0`, where Enbaya's MWCC file starts |

Each SJRBF and SJUNI entry point takes the SJ critical section (`SJCRS_Lock`, `SJCRS_Unlock`) around a
lower-case body that checks the handle and reports through `SJERR_CallErr`; the body's errors on a bad line
go to the object's own error callback, which defaults to `sjrbf_Error` / `sjuni_Error`. A chunk put on SJRBF's
data line is copied into the extra area when it starts inside the mirrored region, and its part past the end
is copied to the start. SJUNI in join mode merges a chunk that continues a line's end chunk, and a GetChunk
shorter than the first chunk splits it.

`SVM_SetCbSvr` reproduces only as a member of this file, compiled after `SVM_Lock`, `SVM_Unlock` and
`SVM_CallErr1`, which it calls.

## Open questions

- Lock types 4, 5 and 1000 are named `Dev`, `Etc` and `Usr` from their users (SRD's device access takes type
  4); the CRI names are unknown. Server type 3 is named `FsVsync` by its place between the vsync and the file
  system types.
- `svm_reset` clears the execution counts of only the first six server types, and `SVM_GetExecCnt` reads
  only the first seven.
- `SVM_DelCbTestAndSet` calls `SVM_SetCbTestAndSet` with no function, which only sets one when none is set,
  so it changes nothing; the name is the intent.
- `SVM_ItoA` stores the digit values themselves into the caller's buffer and then copies out, reversed,
  whatever `svm_itoa_work` holds; retail does the same.
- No source yet:
  - `sjuni_IsGetChunk` (`0x27d248`): retail computes `len < nbyte` in join mode and `len ^ nbyte` otherwise and
    tests both with one shared `== 0`; every spelling tried merges or reorders the branches.
  - `SVM_GetLockType` (`0x27e2e0`), `SVM_Init` (`0x27ec10`) and `SVM_Finish` (`0x27ec50`) reproduce only
    with the lock type and the init count `volatile` (the finish re-reads the count after its store), the same
    mechanism the lock counts already have an approval for; they need the owner's approval first.
  - `SVM_GetExecCnt` (`0x27eb40`): the bounds test and the scaled index land in each other's registers.
