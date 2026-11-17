# CRI SNDF and CFT

The first two files of the Sofdec block, each compiled as one whole file with Sony EE GCC 2.96 at `-O2 -G0`
(their rows in `units.tsv` and `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/sndf.c` | `cri_sndf` | `0x280b98` up to `0x283018` | SNDF (`SNDF Ver.2.09c`), the sound driver's EE side: SIF RPC to the IOP, voices, programs, streams and pan tables | its first function reads the build-string pointer at `0x4bb10c`; every function uses its context at `0x572a00`, its RPC buffers or its status block at `0x5717c0`; its data `0x4bb100` up to `0x4bb3e8` |
| `src/cri/cft.c` | `cri_cft` | `0x283018` up to `0x285118` | CFT (`CRI CFT/PS2EE Ver.1.57`): colour-format and alpha-plane conversion tables | its data starts at `0x4bb3e8` (the name-message pointer) with the 0x1800-byte table block at `0x4bb3f8`; the next module's data starts at `0x4bcbf8` |

## Open questions

- SNDF's init (`0x280b98`) reads the build-string pointer once and discards it, in the delay slot of the call to
  `sceSifInitRpc`; the owner approved that read as a `char *volatile` word under
  [build-string reads](source-approvals.md#build-string-reads), to land once the function matches. Its two
  bind-wait loops, zero words included, come from plain C (the compiler's loop alignment). The best C still
  differs in twelve words: retail computes the first RPC client's address into a saved register before the flag
  store and fills the call's delay slot with the read, where the C computes the address last; and two loads of
  the parameter copy at the end are swapped. Statement orders, a local client pointer, `do`/`for` loop shapes, an
  inline bind helper, the real `sceSifInitRpc` prototype and a permuter run left the prologue unchanged.
- CFT's init stores its version string in a `volatile` word and is `unapproved`
  ([build-string stores](source-approvals.md#build-string-stores)). Two table builders and two alpha-plane loops have no source (store order; a multiply retail
  recomputes on each pass).
- The SNDF entry points the game calls for its sound banks (port sizes, transfer start and status, freeing a
  port, the control and master-parameter messages) are named from what they do and how the game uses them;
  no string or other build carries the library's own names for them.
- `sndf_CallRpc` (medium; alternative `sndf_SendCommand`) is named from what it does: it copies the arguments into the
  shared buffer and sends one command under a busy flag. The rest of SNDF's internal functions (the one-command
  wrappers, the status-block getters, the port and channel helpers) stay unnamed: the command codes they send
  (`0x200`, `0x800`, `0xE00`, `0xF900`, `0xFB00` and others) are not named by any string or other build.
- `CFT_Init` (medium) holds the SDK `cft_lib.o` slot before `CFT_Finish` and stores the CFT build string.
  `CFT_SetMaxAlpha` and `CFT_GetMaxAlpha` (medium; alternative a `cft_` prefix) keep the word `CFT_Init` sets to 128
  and `SFX_SetMaxAlpha` forwards to. `CFT_MakeYcc422ColAdjTbl` and `CFT_MakeArgb8888ColAdjTbl` hold the SDK `cftfx.o`
  slots with the same sizes, and the SFX table makers call them as in the SDK.
- `CFT_GetVersionStr` (`0x283098`) returns the address of the word that holds the maximum alpha, not a string;
  `CFT_Init` writes the build string itself. Whether the slot kept the 2002 name is open, as are the four accessors of
  the name-message pointer and the word after it at the start of the file, and the three YCC-to-ARGB plane loops
  before `UTY_CmpTime`.
