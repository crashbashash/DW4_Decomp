# Base window-controller object cleanup

The complete 192-byte `beNDMWWindowCtrl_Destroy` body at `0x003b6430` is recovered and
byte-matched. It is used by shop-root and other
GetVTable temporary cleanup. [The typed source](../../src/game/beNDMWWindowCtrl_Destroy.cpp)
uses the reflected controller's inherited window reference cells. It is a
separate dependency of the [shop metadata block](shop-root-metadata.md);
the metadata block's 116-byte getter matches as
`src/unmatched/beNDMWShopCtrl00_GetVTable.cpp`.

## Identity and exact operations

The body publishes table `0x0053daa0`, whose retail RTTI identifies
`Gap::Bec::beNDMWWindowCtrl`, then table `0x0053dc30`, identified as
`Gap::Bec::beNDMWWindow`. The derived controller's sole own field is
`_nowProcKazu` at80; the seven destroyed cells come from its Window parent.
The descriptive Destroy name is generated from that evidence, not claimed as
an original C++ method spelling.

A null receiver bypasses all operations and returns null. For a non-null
receiver, the member-cell helper calls run in this order, each with flag-1:

| Offset | Reflected member | Helper |
| --- | --- | --- |
| 76 | `_modelCloseSeqNameList` | `0x001c6460` |
| 72 | `_modelCloseRamNoList` | `0x00150eb0` |
| 68 | `_modelCloseInfoNameList` | `0x001c6460` |
| 64 | `_textCloseNameList` | `0x001c6460` |
| 60 | `_textCloseTypeList` | `0x001c6460` |
| 56 | `_mother` | `0x003b2f30` |
| 52 | `_subWindow` | `0x003b2fb0` |

After those calls, only a positive **signed low16** deletion flag invokes the
existing deallocation thunk at `0x002ff810`. The function always returns its
original receiver address, including after that deallocation request. It adds
no field clearing, child traversal, model-close messages or other cleanup policy.
The cell helpers remain separate dependencies.

## Code generation and verification

The body is plain C with no `asm`: the inlined base destructor keeps its own `self` test, and the
receiver is returned through an ordinary `return self`.

```sh
python3 tools/verify.py 0x3b6430 src/game/beNDMWWindowCtrl_Destroy.cpp --verbose
make check
make link
make typed-check
```

The original helper/source and whole-section byte checks are the acceptance
for this PS2 matching body.
