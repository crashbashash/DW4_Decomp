# Imported title controller

`title-menu.c` and `title-menu.h` are unchanged copies of the decompilation
repository's behavioral reconstruction of `beNDMWTitle2::vfunc_31` at
`0x003f2ef0`. `provenance.json` records their exact hashes. They are game-derived
material; see [LICENSE](../LICENSE) and [NOTICE](../NOTICE).

The upstream verifier compares the initialized controller with retail R5900
instructions across 55,264 cases, at a stubbed engine boundary. That evidence
covers the controller, not the native backend. The reference is not a
byte-matched translation unit.

`make check` checks the import hashes and compares with the canonical recovery
source when available. Update these files only by reviewing and re-importing
that source, then updating the provenance hashes and running its verifier.

The port adapter and its remaining limitations are described in
[title-controller.md](../../docs/title-controller.md). No game binary is included.

`loadingnode.c/h` import the complete nine-body loading/node runtime. The shared
EE float model is unchanged. Its canonical retail verifier and native presentation
boundary are described in [stage-loading.md](../../docs/stage-loading.md).
