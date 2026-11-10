# CRI cvFs — the middleware file-system layer

cvFs is CRI's device-independent file layer (`CVFS/PS2EE Ver.2.37 Build:Oct 6 2004` at `0x4eeed8`). ADX
and the other CRI libraries open, read and query files only through its API; a device (the CD/DVD
driver, the host file system, a volume image) registers a table of entry points under a name, and every
cvFs call looks the device up by the name prefix of a path (`dev:file`) or uses the default device.
The source is `src/cri/cvfs.c` with the shared types in `include/dw4/cri/cvfs.h`. It builds with Sony
EE GCC 2.96 at `-O2 -G0` like the rest of the CRI blocks, as one whole file ([sd-prologue](sd-prologue.md)).

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x26f500` up to `0x271640` | the CRI CFG module (`CRI CFG/PS2EE Ver.1.002`, its table at `0x56dfd4`) ends before it; SRD (`SRD/PS2EE Ver.2.22`, the object at `0x4a9288`) starts at `0x271640` |
| strings | `0x4eeed8` up to `0x4efb60` | the version string, then each API function's numbered error messages in code order |
| data | `0x4a9278..0x4a9287`, `0x56e0e0` up to `0x56e580` | referenced only by module functions: the build-string pointer, the error callback and its object, the init count; the 40 handles, the 32 device entries, the default device name and the path work buffer |

Code outside the module calls only the API functions, never the helpers. The module is one
whole-file unit (`cri_cvfs` in `units.tsv`, its rows in `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)): the file compiles as one object with
`-ffunction-sections`, and each function is checked and placed at its retail address. The functions it
does not define yet link from the retail image between its members. Compiling the file whole matters
here: `splitPath` matches only with `toUpperStr` compiled before it, because a call to a function GCC
has already compiled is known not to throw and that changes how its delay slots are filled, and
`cvFsGetFreeSize` matches only when the file is compiled whole (alone, one branch takes the likely form).

## Layout

The device table is what CRI's messages call the **vtbl** (`#2:vtbl error`). A handle is
`{ CvFsVtbl *vtbl; int fd; }`: the device's table and the device's own file value. A registered device is
`{ CvFsVtbl *vtbl; char name[12]; }`.

| offset | slot | offset | slot | offset | slot |
| --- | --- | --- | --- | --- | --- |
| `0x00` | `exec_server` | `0x24` | `req_wr` | `0x48` | `load_dir_info` |
| `0x04` | `entry_err_func` | `0x28` | `stop_tr` | `0x4c` | `get_max_byte_rate` |
| `0x08` | `get_file_size` | `0x2c` | `get_stat` | `0x50` | `make_dir` |
| `0x0c` | `get_free_size` | `0x30` | `get_sct_len` | `0x54` | `remove_dir` |
| `0x10` | `open` | `0x34` | `set_sct_len` | `0x58` | `delete_file` |
| `0x14` | `close` | `0x38` | `get_num_tr` | `0x5c` | `get_file_size_ex` |
| `0x18` | `seek` | `0x3c` | `change_dir` | `0x60` | `opt_fn1` |
| `0x1c` | `tell` | `0x40` | `is_exist_file` | `0x64` | `opt_fn2` |
| `0x20` | `req_rd` | `0x44` | `get_num_files` | | |

Each slot is named after the API function that calls it. `opt_fn1` is a general request entry: its
second argument is a code (`CvFsOptCode`): 1–6 for the volume requests (`cvFsSetCurVolume`,
`cvFsAddVolumeEx`, `cvFsDelVolume`, `cvFsGetNumFiles`, `cvFsGetVolumeInfo`, `cvFsSetDefVol`), 100 to ask
whether the device takes full `dev:file` paths, 200–205 for the 64-bit sizes and track counts, 299 and 300.

## Integer-typed slots

Every vtbl slot is declared `int` and cast to its function type at the call, and the block the volume
requests pass to `opt_fn1` (`CvFsVolumeArg`) holds its image handle and volume name as `int` too. This is
how the original declared them, as far as the code can show, and it decides the instructions: GCC's
alias analysis treats an `int` store and a pointer load as independent, so with pointer-typed slots the
first scheduling pass moves the slot load above the store into the argument block, the live ranges change,
and two values swap saved registers. Retail keeps the load after the store (or reloads the slot after it),
which happens only when both accesses are `int`.

The owner approved this typing on the condition that it describes the types rather than one call site: one
declaration, used by every function that touches the table or the block, with every one of them matching
and none needing the pointer form. That holds for every function of the module that has source.

## Open questions

- `cvFsGetNumFiles` (`0x2708a8`) and `cvFsLoadDirInfo` (`0x2709b8`) are named by no string. They call slots
  `0x44` (no arguments) and `0x48` (path, work area, file count), which sit where other CRI builds order
  `GetNumFiles` and `LoadDirInfo`; that ordering is not shown by this binary. `cvFsLoadDirInfo` reports
  `cvFsIsExistFile #2:illegal device name`, apparently a message copied from `cvFsIsExistFile` in the
  original source.
- The helpers have names from what they do, in CRI's spelling: `cvFsCallUsrErrFn`, `cvFsError`, `addDevice`,
  `getDevice`, `toUpperStr`, `allocCvFsHdl`, `releaseCvFsHdl`, `getDefDev`, `splitPath`, `getPathDevice`,
  `isExistDevName`, `isFullPathDev`, `makeFullPath`, `cvFsIsExistDev`.
- A device that answers 1 to code 100 gets its file names rewritten as `dev:file`, and `cvFsGetNumFiles`
  then uses code 4. Whether this marks a volume device is unknown.
- The third argument of the error callback (`cvFsError` passes 0), the meaning of `CvFsVolumeArg`'s `option`
  field (a flag for `cvFsAddVolumeEx`, an information pointer for `cvFsGetVolumeInfo`), and why the default
  device name is cleared over 9 bytes while device names take 12 are unknown.
- Retail behaviour the source keeps: `cvFsIsExistFile` reads the vtbl after reporting "device not found";
  `cvFsGetDevName` returns the entry past the table when no device matches; `cvFsGetFileSizeEx64` looks the
  device up before splitting the path, so it reads the device-name buffer uninitialised; `allocCvFsHdl`
  treats a handle as free when its `fd` is 0.
