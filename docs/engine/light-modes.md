# Hard/Soft lighting in the Main Lobby

Finding **[#784](../findings/findings-0751-1000.md#f784)** connects the menu's LIGHTMODE value to retail stage presentation.
The observed contract is **0 = Soft, 1 = Hard**. This recovery covers the bounded
Main Lobby arrival (NDMW 820, `stagml11.igb`, BG02 and `camsp0101`). It does not
establish mode behavior for every stage.

## Setting and light rigs

`SYSgetLightMode` at `0x00371e70` reads GAMERAM's common `LIGHTMODE` property.
The load-controller handoff loads its confirmed option at +0x28 at
`0x003f2284`, identifies the `LIGHTMODE` key at `0x00518208`, and stores the
value at property +12 at `0x003f2294`. These instructions were checked with
`mipsel-linux-gnu-objdump` as well as the analyzed Ghidra project.

The original NDMW 820 Lua chunk 009 calls `funcStartLayerSet`, then conditionally
sets LIGHTCTRL colors when `be:SYSgetLightMode() ~= 0`. The cleaned Lua listing
is insufficient evidence: its signed PUSHINT decoding is one off and it loses
nested statements. Decode the original Lua 4 instruction with signed bias
`((1 << 26) - 1) >> 1` to read the condition and constants correctly.

| Mode | Ambient RGB | Directional diffuse RGB | Named texture pack |
| --- | --- | --- | --- |
| Soft (0) | `(0.5, 0.5, 0.55)` | `(1.2, 1.2, 1.08)` | NDMW 822 |
| Hard (1) | `(0.2, 0.2, 0.35)` | `(1.1, 1.1, 1.1)` | NDMW 821 |

Soft preserves the authored `igLightAttr` records: ambient at pack +0x49254,
directional at +0x491cc. Hard overrides their colors through LIGHTCTRL.
Both retain the authored direction
`(0.2716537714, -0.7660444379, -0.5825634003)`.
The directional light's ambient is zero and the ambient light's diffuse is zero.
The separate spotlight at +0x3f43c belongs to the shadow path.

The two texture packs contain the same 18 logical names, with mode-specific
index grids and palettes. Changing only the light colors is insufficient:
that produced a Soft environment error of 18.88/255. Selecting pack 822 as well
reduces it to 1.12/255. Offline loaded palettes for `ML01GR00_n` match the
respective pack RGB byte-for-byte; the GS alpha conversion is documented in
[the native rendering record](../../port/docs/lobby-rendering.md).

## Shadows

The coherent held-arrival states have the same shadow shader at `0x0126e110`
(vptr `0x00528950`). Its 256-byte region is byte-identical between modes,
including the light position. Relevant fields are:

| Offset | Field | Both modes |
| --- | --- | --- |
| +68 | `_shadowFactor` | 0.4 |
| +72 / +76 | dimensions | 256 × 256 |
| +80 | `_shadowLightness` | 0.5 |
| +120 | `_blurState` | 0 |
| +212..224 | bounds | ±100 |

Retail receiver draws use GS PRIM 93 and ALPHA 0x46 in both captures. Each
mode matches 1,936 receiver instances in the native projection oracle: UV
mean absolute error `2.482729e-7`, screen maximum error `0.088389` pixels.
These observations establish no mode-dependent shadow blur or projection in
this arrival. They do not cover later action poses or other shadow controllers.

## Retail verification

Private evidence is retained under workspace
`../local/captures/dw4-port/light-modes`: the two pre-login states, two loaded
states, complete GS captures, 640×448 screenshots, extracted atlases and reports.
Only the confirmed load-controller option (+0x28) was changed in copies of the
pre-login state. Retail then performed its login/stage load for each mode;
loaded lighting was never patched. The pristine disc was read without modification.

Unambiguous world vertices are paired by primitive structure before consulting
colors. All 12,976 Soft and 12,776 Hard paired vertex colors agree within 1/255;
all paired named texture RGB hashes agree exactly. Fog agrees exactly in both.
Environment screenshot MAE is **1.119/255 Soft** and **1.340/255 Hard**.
Actor animation and greeting clocks are not synchronized, so the environment
metric and held-world vertex oracle exclude actor/UI regions. This is bounded
visual verification, not whole-frame identity. Commands and the native option
handoff are in [lobby rendering](../../port/docs/lobby-rendering.md#hardsoft-option).
