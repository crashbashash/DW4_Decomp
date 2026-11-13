# CRI SFX and SUD

The last CRI files of the Sofdec block, each compiled as one whole file with Sony EE GCC 2.96 at `-O2 -G0`
(their rows in `units.tsv` and `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/sfx.c` | `cri_sfx` | `0x2b3788` up to `0x2b4210` | SFX (`CRI SFX/PS2EE Ver.2.08`), the frame-conversion library's handles and conversion entry points | its messages start with the version string at `0x4f57b8`; its library object at `0x4bec28` (1000 bytes) ends where the Z file's data begins |
| `src/cri/sfxz.c` | `cri_sfxz` | `0x2b4210` up to `0x2b50e8` | SFX's Z-buffer conversion | it repeats `SFXINFE` (GCC shares identical strings only within a file); its messages run to `sfxcnv_CnvZbitToCft`; its object at `0x4bf010` |
| `src/cri/sud.c` | `cri_sud` | `0x2b50e8` up to `0x2b5d50` | SUD (`CRI SUD/PS2EE Ver.0.05`): user-data headers and the EE timer | its init returns the version string at `0x4f59c0`; its messages and tables follow SFX's; its data at `0x4bf280` |

SUD's timer words and the timer-register tables are declared `volatile`
([source approvals](source-approvals.md#sud-timer)); the timer tick is approved, the timer init and read are
`unapproved`. SFX's and SUD's inits store their version strings in `volatile` words and are `unapproved`
([build-string stores](source-approvals.md#build-string-stores)). The two SFX files share `include/dw4/cri/sfx.h`. A plane's address (`SfxPlane.addr`) is declared `int` and
cast at use, as the owner approved for the cvFs, HTCI and DVCI pointers on the same condition
([CRI cvFs](cri-cvfs.md#integer-typed-slots)).

## Open questions

- Whether the function at `0x2b3780` (returns 17) starts the SFX file or ends the conversion file before it.
- The free-handle searches at `0x2b39e0` and `0x2b42c8` match with a `volatile`-qualified read of the in-use
  word. Retail leaves the loop branch's delay slot empty where the compiler fills it, plain C cannot fill the
  slot differently under this compiler, and both are `unapproved`; the same holds for the one in the SFH file
  ([CRI SFH](cri-sfh-files.md#open-questions)).
