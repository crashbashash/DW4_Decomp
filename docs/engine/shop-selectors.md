# Shared selector and shop widget initialization

**Six complete bodies /7,916 code bytes** are recovered: the shared
WindowSelect update4233f0 /772 bytes, FO2TOP predicate423700 /84 bytes,
ShopSelect00 initializer43d1d0 /636, ShopSelect01 initializer43d450 /1,976,
ShopSelect11 initializer43ecc0 /3,752 and its stat/cost display43fb70 /696.

The full1,979-word spans hold **1,909 reachable instruction addresses**, six
zero padding words and64 statically impossible
literal-null construction words. The84-byte
[FO2TOP predicate](../../src/game/beNDMWWindowSelect.cpp) is in `src/game/`;
the three shop initializers and the stat/cost display /7,060 bytes are one-function
files under `src/unmatched/`, and the shared update4233f0 /772 bytes is
[beNDMWWindowSelect.cpp](../../src/game/beNDMWWindowSelect.cpp). Receiver/input, pool/list,
lookup/recalculation, formatting, text/model and Lua services remain boundaries.

The76-byte lazy shop metadata
accessor uses the repository's explicit-padding convention.
Its null branch enters at the registration call while the non-null/not-ready path
executes the original no-op.

## Selector fields and generation

Reflection identifies the Window prefix and these selector fields:

| Offset | Field |
| --- | --- |
| 80 | `_infoName`, string receiver name |
| 84 | `_selectMax`, number of choices |
| 88/92/96 | `_offsetPos`, three float words |
| 100 | `_startPoint` |
| 104 | `_isNoCancel` byte |
| 108 | `_decideList`, nullable byte-list reference |

The owner uses messenger12/player20, active byte24, primary state28 and counters
32/36/40. Mother56 receives the selected return value in its word48.

In state0 the update calls the concrete initializer through raw virtual byte96.
It selects SELECTCTRL by current infoName/player, appends choice count and start
point, then copies/appends the current offset vector in its64-byte private frame.
A nonzero no-cancel byte appends NOCANCEL. A non-null decision list with positive
signed count appends each raw byte. That loop **reloads list, backing storage and
count around every callback**; it is not limited by a captured initial count.
Generation dispatches GENERATE, advances the current state and clears40/36/32.

## Result publication, close and top reset

State0 falls into state1 **in the same call**. State1 sends GETSELECT, reads integer
result0 and reloads mother56 before writing its return48. It then sends ISEND.
Only the returned low byte controls completion. Thus highlights reach the owner
before a selector finishes, allowing the XDATA description to update while the
child count is unchanged.

A nonzero end byte advances the current state and falls into state2 close work.
State2 executes queued model-close and text-clear helpers, advances again and
falls into state3 close polling. State3 clears active byte24 when the common
poll returns nonzero. These transitions can all finish in one call. Unlike the
shared title body, this selector body has no explicit child-close call; the
[tree updater](window-tree-and-shop-root.md) applies its own close-state rules.
Other primary states return, except state4.

State4 queries ISFO2TOP. CanRequestFO2TOP423700 negates the **full** returned register
and normalizes to0/1. When that query permits the request, state4 reselects the receiver, appends
current choice count and live decision bytes, dispatches FO2TOP, then queries and
publishes GETSELECT. The FO2TOP path omits the generation-only start/offset/cancel
arguments. Whether a request was sent or not, state4 writes state1 and clears counters.
The receiver enum maps FO2TOP/ISFO2TOP to4/5. Handler case5 returns0 for its
stable state/counter condition, and case4 accepts the reset under that same
condition. It resets the selected index to0 and enters state10. The exact
manager update/animation/input behavior remains future recovery. This window
helper queries SELECTCTRL directly.

The exact predicate needs logical `!GetBool(...)` in the original compiler.
Equality-to-zero produced two different words; an intermediate C++bool added a
second normalization. The direct logical form reproduces every84 retail bytes
with no assembler substitutions. Its receiver fields use recovered WindowSelect
layout; the typing metric counts one recovered access for this unit.

## One-choice message widget

ShopSelect00 initializes a one-choice `i_stmessky` receiver. With a signed positive
entry code44 it appends STWINFONT29 to the text-close types. A null `_fontName`112
queues font000; a provided font token is copied/retained into the corresponding
name list through a real private reference cell. It runs txt_shop.lua with the
current entry code. Nonpositive entry codes omit that text work.

It then interns/publishes its infoName, releasing the current old name before
publication, sets max1, zeroes the offset vector, resets start0 and clears the
no-cancel byte. Old owner names and private string cells remain live around calls.

## Two-/three-choice widget

ShopSelect01 classifies the incoming entry code once:

| Choices | Entry codes |
| --- | --- |
| 3 | 47e,546,60e,672,6d6,73a,79e (hex) |
| 2 | 48b,48e,493,4e7,4ea,4f8,54b,5ad,614,61a,678,6dc,740,7aa (hex) |
| Other | Preserve the incoming choice count |

Recognized cases append STWINFONT29 plus font000/font001 and, for triples,
font002 to the close queues. Each append has its original scoped cell and current
cell release. It runs txt_shop.lua using the current entry code, then sets the
classified choice count. The incoming start point is preserved, including the
main-menu default supplied by the XDATA owner. All cases publish `i_stmesscr`,
zero the vector and clear the no-cancel byte twice as emitted.

## Seven-stat widget and display

ShopSelect11 first requests model `j_shwin` /SQ_XDATASTATUSOPEN with queued
SQ_CLOSE through the actual common presentation routine. It appends ten text-close
pairs covering STWINFONT29/font100, STWINFONT13/font000, STWINFONT35/font001 and
STWINFONT14/font000..font006. The text script is called at the original points
with1153,1101 and1103. Seven cost fonts in STWINFONT19 and the STWINFONT29 header
are prepared through3f5410 using the original blank strings/alignment arguments.

It sends selected-player RECALCPLAYER with an explicit false argument, executes
the recovered stat/cost display, and dispatches the current parameter+1154 text
highlight. Finally it publishes `i_stcursor01`, max7, exact position bits
c2f20000/43000000/00000000, start=current entry44 and no-cancel0.

RefreshStatCosts43fb70 resolves the selected player's seven current stats. Its
copied key/cap/font tables at4cfad0/4cfaf0/4cfb10 select the five core stats with
cap9,999, then MHP/MMP with cap99,999. It uses the same wrapped signed cost formula
as the [XDATA controller](xdata-controller.md), preserving cost0.

Below the cap it formats `%d` into the288-byte frame's private text buffer256;
at/above cap the format is literal `----`. It publishes costs to STWINFONT19 and
resets corresponding STWINFONT14 value colors below cap. Capped values receive
exact RGB bits3f666666/3ecccccd/3e4ccccd. It re-reads the copied cap before color
selection after the text callbacks, preserving the original captured stat and
live table distinction.

## XDATA flow outcome, spans and verification

In the XDATA stat flow, quotes remain uncharged; cancellation preserves XDATA and
all UPCNT entries; acceptance charges the selected stat and increments its specific
slot. Rendering, actual input and recalculation formulas remain open dependencies.

Select00's636-byte span includes the return/delay that a628-byte split omits;
Select11's3752-byte span includes12 bytes its3740 occupied-byte sum omits. Generated
Ghidra ranges cover them, 20 classified code bytes of unchanged retail
contents. The common loop/predicate and refresh spans equal their occupied-byte counts.

Thirty-two string-construction blocks test an immediately loaded nonzero literal,
then contain an impossible null branch and delay word: those are the64 impossible
words. Six zero words are outside Ghidra's occupied ranges.

```sh
python3 testing/test_lua_engine_dependencies.py
python3 tools/test_function_extents.py
make check
make link
make typed-check
```

The concrete SELECTCTRL manager is identified independently: beSelectCtrl
at table53b290 registers literal50f7f0 through39cbc0. Raw132 selects update39cbf0;
raw140 selects general handler39d720. Its inherited raw144 check378410 is the
exact return-zero body, so the shared messenger uses the general raw140 path.
Pad-manager acquisition39cb70 (not cleanup) and
registration39cbc0 total 100 bytes. The complete
[SELECTCTRL manager review](selectctrl.md) records the2,864-byte update
and1,960-byte general handler. [Owner and SELECTCTRL protocol](#owner-and-selectctrl-protocol) describes the selector
running against the actual handler responses, pad lookup and close queues.

## Owner and SELECTCTRL protocol

The common shop selector owner runs on top of its concrete SELECTCTRL
handler/update, pad-record lookup and close queues. The owner obtains its
selected value and completion flag from the handler's append operations; it
holds no result or completion flag of its own. The old selected field has no
part in publication: the GENERATE handler establishes the requested start point.

### Bodies

| Original entry | Body | Span bytes |
| --- | --- | ---: |
| `0x004233f0` | Common WindowSelect owner update | 772 |
| `0x00423700` | CanRequestFO2TOP | 84 |
| `0x0039cbf0` | SELECTCTRL manager update | 2,864 |
| `0x0039d720` | General SELECTCTRL handler | 1,960 |
| `0x0039b810` | Pad manager record selection | 88 |
| `0x003f5a40` | Queued text close | 580 |
| `0x003f5f80` | Queued model close | 272 |
| `0x003f6090` | Close completion polling | 696 |

### Request and response protocol

The owner addresses the SELECTCTRL target by name and player and passes its
integer, vector, string and decision-byte arguments to the handler. GETSELECT
and ISEND responses come from that handler's append operations. FO2TOP readiness
likewise comes from its ISFO2TOP branch.

The owner publishes the current selection to its mother's return word while the
manager is active. It starts closing only after the manager has completed its
own close phases, cleared active and released its work reference. The three
owner close helpers then run over the window's close queues and child list.

### Protocol behaviour

The protocol applies to all four players and both orientations, with supplied
decision flags, normal and fallback pad records, and 1/2/3/7 choices:

- Generation publishes the start point, then pending opening waits, directional
  movement and result publication run while the owner remains active.
- Accepted selection is followed by pending confirmation/close waits.
- Cancellation wins over simultaneous confirmation.
- NOCANCEL and disabled-choice rejection go through the original 16-count wait,
  after which a valid choice is accepted.
- FO2TOP acceptance resets the selection to zero, busy rejection preserves the
  parent's existing result, and selection then returns to ordinary operation.
- Every returned index0..6 in a seven-choice cursor corresponds to the
  `i_stcursor01` receiver name. One-choice and ordinary dialogs use `i_stmessky`
  and `i_stmesscr`.
