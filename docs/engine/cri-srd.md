# CRI SRD: the sector read driver

SRD (`SRD/PS2EE Ver.2.22` at `0x4efb90`) is the layer under cvFs's devices that reads the disc and the
host file system. It keeps one request object, queues a read on it (DVD sectors through `sceCdRead`, or
a seek and read on a host file through the IOP file calls), and a server step advances the request
until it completes or fails. The source is `src/cri/srd.c`. It builds with Sony EE GCC 2.96 at
`-O2 -G0` as one whole file (`cri_srd` in `units.tsv`, its rows in `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)).

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x271640` up to `0x2729e8` | cvFs ends at `0x271640`; the function at `0x2729e8` uses the DTR strings |
| strings | `0x4efb60` up to `0x4eff20` | the version string, then the module's messages in code order |
| data | `0x4a9288` up to `0x4a9308` | the request object, the build-string pointer, then the module's words in declaration order |

## Layout

The request object (`SrdObj`, 56 bytes at `0x4a9288`) holds an in-use byte, the device type (1 DVD,
2 host), the state (0 idle, 1 queued, 2 reading, 3 done, 9 failed), a mode byte, an abort request,
the DVD request (sector, count, buffer, `sceCdRMode`), the host request (buffer, size, sector, file
descriptor) and the last error.

The words after it, in declaration order: the build-string pointer, the server's enter flag, the
DVD, host and error-query lock switches, the error-check switch, the wait counter, the error-query
flag, the read, completion, create and destroy counts, the previous and current trace markers, the
host flag, the host-lock mirror, and two DVD read-mode overrides. The server words from the lock
switches to the trace markers are declared `volatile`, except the destroy count
([source approvals](source-approvals.md#srd-module-words)).

## Open questions

- The module's functions and words have no names from strings except those its debug summary prints
  (`srd_enter_fg`, `srd_debug_geterror`, `srd_obj.stat`, `srd_obj.devtype`) and its wait-loop
  message (`SRD_WaitForExecServer`). The words from `srd_obj` to `srd_destroy_cnt` take the names of the
  2002 SDK's `cri_srd.o` ([recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)), whose data
  lies in the same order (`srd_geterror_locked`, `srd_geterror_call`, `srd_wait_svr_cnt`, `srd_debug_geterror`,
  `srd_debug_rdbg_cnt`, `srd_debug_rded_cnt`, `srd_create_cnt`); `srd_filesystem64` is the Street Fighter III
  3rd Strike libadxe's ([3s-decomp](https://github.com/crowded-street/3s-decomp)). Medium by 3rd Strike's order and
  size: `SRD_WaitComplete`, `SRD_WaitCompleteVoid`, `SRD_IsExecute`, `SRD_SetFilesystem64`, `SRD_GetFilesystem64`,
  `SRD_SetLockHost`, `SRD_GetLockHost`, `SRD_SetDvdSeekPos`. Medium from behaviour: the four spindle-control
  accessors after `srd_check_dvd_error` (`SRD_SetSpindlCtrl`, `SRD_SetSpindlCtrlSw`, `SRD_GetSpindlCtrl`,
  `SRD_GetSpindlCtrlSw`, after the `sceCdRMode` member; alternative `SRD_SetSpindleCtrl`), which 3rd Strike lacks.
- The seek wrapper at `0x272780` hoists the 32-bit offset conversion of its second branch above the
  branch and keeps the mode word in `a3`; no spelling tried reproduces that.
