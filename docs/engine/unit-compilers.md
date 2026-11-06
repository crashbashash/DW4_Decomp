# Per-unit matching compiler requirements

The complete [combat Lua API run](../systems/combat-lua-api.md) now rebuilds
exactly from readable C. Thirteen of its bodies, the 84-byte
`FightCom_GetMetaEnum` and the 76-byte `StringPool_GetInstance` use an alternate
compiler. Three [reference-ownership dependencies](../systems/combat-reference-helpers.md)
also require it, as does the 132-byte
[technique-row helper](../systems/combat-helpers.md). The nearby-query compiler
unit also supplies its deleting destructor through
[explicit emitted-function ownership](emitted-functions.md). The parent
`GameRamMessage_GetMetaEnum` adds another 84 bytes: twenty-one compiler units
cover twenty-two complete bodies / 4,848 code bytes in total.
Verification includes all instruction
words and relocations. This does not establish a single original compiler build,
prove that retail used multiple builds, or match the combat dispatcher.

The ordinary compiler emits a 60-byte attribute accessor. A content-pinned
alternate compiler emits the original 56 bytes from the same source. For the
enum builder, that compiler with `-O3,p` reproduces all 84 bytes, including the
branch-delay scheduling and interior zero word. The enum builder creates the
22-entry `FightCom` name/id enum once and returns the cached object. The accessor
uses the fallback string for signed indices at least four; negative indices
remain unchecked, as in retail.

The same compiler at `-O3` or `-O3,p` reproduces retail's delay-slot fill and
padding nops for families the default compiler cannot, from an unchanged m2c
draft: lazily created singleton getters of 68, 76 and 84 bytes, 60-byte
`*_GetVTable` stack-object accessors, `_GetMetaObject` accessors and
nop-before-join loops. Delay-slot fill and an extra nop in a small function are
therefore a symptom of compiler choice, not a wall: retry under this compiler
first.

## Reproduction

Provide the private executable at `local/mwcps2/combat/mwccps2.exe`, with SHA-256
`acf1088553362dddef7eee2d269848b03208e29fd26caa441848e57b6299786a`.
The compiler is available in the upstream
[decomp.me compiler distribution](https://github.com/decompme/compilers/releases/tag/compilers).
Keep the compiler and its runtime dependencies outside Git, under the existing
private tools link. These are build requirements, not host configuration facts.

`config/SLUS-20836/unit-compilers.tsv` maps stable retail addresses to executable paths and
SHA-256 requirements. Emitted members inherit their owner's settings. Other
unlisted functions keep the global compiler supplied by the existing build
settings. Listed functions take precedence over that global
setting. Missing or changed executables fail verification and linking; they
never silently use the default compiler. `config/SLUS-20836/unit-flags.tsv` independently
pins the enum builder's speed optimization.

`tools/unitcompilers.py` implements selection shared by `tools/verify.py` and
`tools/linkgen.py`. Consequently `make check` and `make link` apply the same
requirements. Diagnostic callers of `verify_one` can pass `unit_compilers` with
a different overlay path, just as `unit_flags` selects a flag overlay.

Run `python3 tools/test_unitcompilers.py` for default preservation, selection,
missing/changed executable rejection, malformed/duplicate entries and failure
before compilation. Whole-tree checking and the byte-identical relink are the
integration oracle. The existing relocation and multiple-table tests remain
applicable. No compiler binary or game extract is committed.
