# XDATA controller and script publication

This page covers the complete **5,484-byte ShopCtrl10 update**
4270a0..42860c and its three adjacent128-byte scoped-reference cleanups
428610/428690/428710: **four bodies /5,868 bytes**. The common144-byte
message-script dispatcher3f5920 is also recovered in
[window-presentation.c](../../recovered/engine/window-presentation.c), giving
**five bodies /6,012 bytes** for this checkpoint.

The [guest-reference controller](../../recovered/engine/xdata-controller.c)
passes **2,501 original-instruction RAM/ordered-call cases**. It executes
**1,458/1,503 instruction addresses** across the five bodies. Thirty-three zero
words are padding; twelve nonzero words are statically unreachable literal-null
construction branches. These exclusions are checked independently. All five
bodies match (`src/unmatched/Gap__Bec__beNDMWShopCtrl10__vfunc_21.cpp`,
`src/unmatched/FUN_00428610.cpp`, `src/unmatched/FUN_00428690.cpp`,
`src/unmatched/FUN_00428710.cpp` and
`src/unmatched/beNDMWWindow_RunMessageScript.cpp`); no native UI functionality
is claimed. Widget/input, player recalculation, lookup, pool/list, formatting,
text/model receivers and Lua execution remain explicit services.

## Owner and primary state

Reflection identifies inherited Window fields plus `_nowProcKazu`80,
`_xdataMenu`84 and `_parameter`88. State/counters are28/32/36/40; selected child
result is `_retCode`48 and the retained child list is52. The update keeps its
original368-byte frame for scoped references, fonts, prompt IDs and formatting.

Primary state0 advances to1, clears counters and falls into the main menu in the
same call. Primary1 selects the secondary workflow. Primary2 sends GAMERAM
RECALCPLAYER, resolves the selected player, copies MHP to HP and MMP to MP through
separate property lookups, executes model/text/child-close helpers, then advances.
Primary3 clears active byte24 after the common close poll returns nonzero. Other
primary states return without work. No extra active-byte guard is inserted.

The selected player number20 is reloaded around messages; four-player cases verify
that only the selected record is charged and updated. Common context binding and
window-tree ownership run as original/recovered bodies in composed tests.

## Main, stat and chip menus

Secondary state32=0 creates **beNDMWShopSelect01** through3b4d90 with entry1150
(47e), then copies `_xdataMenu`84 into child100. It captures current child count80
and waits for any count change. Result0 selects stat upgrades and sets84=0;
result1 selects the chip branch and sets84=1; other results advance to primary
closure. Parameter88 resets to0 when the main menu child completes.

Secondary2 sends RECALCPLAYER and creates **beNDMWShopCtrlXdataChip** through3b6940.
When that child's count changes it returns to the main menu with flag40=1. The
chip controller's transactions are a separate dependency.

Secondary1 uses six substates36:

| Substate | Recovered behavior |
| --- | --- |
| 0 | Send RECALCPLAYER with an explicit false boolean, create beNDMWShopSelect11 through3b4790 with cached parameter88, then wait |
| 1 | While count matches, dispatch changed non--1 highlights to txt_shop.lua with id result+1154; on count change build a quote or return to main for an invalid result |
| 2 | After the quote closes, successful flag1 creates confirmation beNDMWShopSelect01 /1163; other flags restart stat selection |
| 3 | Confirmation result0 commits; other results restart stat selection |
| 4 | After the success notice closes, create a continue question /1166 |
| 5 | Continue result0 restarts stat selection; other results return to main |

Each factory first queries the object allocator, then uses selector587110 when
byte554c14 is zero. Scoped references are at364/360/356/352/348/344/340. Binding,
append and release reload the current private cell; child-list snapshots occur
at the original points. Retained widgets and their real selection/animation code
remain services in these tests.

## Quote, cost and limits

On completing stat selection, the controller copies seven font pointers from
4cf950 into private frame272 and sends DEFAULTCOLOR to STWINFONT14 for each.
It then resolves the selected player and maps results0..6:

| Result / parameter | Stat | Quote cap | UPCNT index |
| --- | --- | ---: | ---: |
| 0 | TSUYOSA | 9,999 | 2 |
| 1 | MAMORI | 9,999 | 3 |
| 2 | KASHIKOSA | 9,999 | 4 |
| 3 | SEISHIN | 9,999 | 5 |
| 4 | SUBAYASA | 9,999 | 6 |
| 5 | MHP | 99,999 | 0 |
| 6 | MMP | 99,999 | 1 |

The exact cost calculation first wraps `stat - 45` as32 bits. For signed `n`,
it computes `n / 5 + (n % 5 != 0)` using division toward zero, then replaces a
negative result with1 and caps above400. **Zero remains zero**. For example,
stat45 costs0,46 costs1,2045 costs400, and2046 also costs400. The unusual signed
boundary behavior is preserved rather than replaced with a host ceiling helper.

The current result is cached into parameter88 before allocation. The controller
creates **beNDMWShopSelect00** through3b4f50, increments substate and fetches XDATA.
At/above the signed stat cap it selects error1162; below the computed price it
selects error1161. Otherwise it requests `+1` and formatted remaining XDATA through3f5410 for
STWINFONT41, records the original seven type/font close pairs on that dialog,
and assigns the current result's prompt from the copied11730..11760 table at
4cf970. Quote construction spends no XDATA. Current result and temporary dialog
storage remain live around callbacks; no new array/result guards are inserted.

## Confirmation and actual record writes

On confirmation result0, the controller resolves the player again, fetches the
**current** selected stat and recomputes the price. It fetches XDATA, looks up the
write target a second time, and stores `balance - price` with32-bit wrapping.
It fetches UPCNT and reloads parameter88. The selected element is read before the
count guard, as in retail; the increment is written only when the count is nonzero
and its signed value exceeds the index above. Counter increments wrap32 bits.

The affordability/cap branch belongs to quotation. Confirmation debits the newly
computed price and applies the bounded counter increment, including when those
records changed while the dialog was open. Missing/short counter arrays do not
add a rollback of the debit. The reference does not introduce transaction guards.

It then sends RECALCPLAYER, resolves the player again, copies current MHP/MMP to
HP/MP, sends SUBWND UPDATE with the current player number and creates the success
notice /1165. Actual recalculation formulas are not implemented by this body.
Tests use a controlled recalculation response to verify the final HP/MP copies;
the recalculation receiver remains part of the full hub dependency frontier.

## Script call number and pack ownership

RunMessageScript3f5920 resolves the beLua class through the window insight8 and
handle589208. A null result or failed type check selects a null Lua receiver.
It publishes the low32-bit call number at58a220 and calls389ff0(receiver,script,0).
The exact existing Lua binding **TXTgetCallNo**3747f0 reads that same word. There
is no added early return before the execution call. Original routine/script
returns remain explicit callback boundaries.

An offline object/remap/aligned-pool read of the pristine private NDMW archive
resolves **txt_shop.lua** in both hub packs:

| Pack | LuaInfo / list / position | LuaData / data object / memory | Payload offset / chunk |
| --- | --- | --- | --- |
| 824 Central | 3100 /9257 /120 | 9561 /9562 /124 | 554,152 /chunk0000 |
| 828 Shop | 6808 /3151 /57 | 3119 /3120 /9657 | 1,634,452 /chunk0057 |

Each payload is31,147 bytes. Their prototype headers, instruction/number trees
and string constants compare equal after normalizing stage-local `I<n>` font
indices; each stage retains its own original font-index constants. The original
bytecode has the exact TXTgetCallNo comparison prefixes for highlights1154..1160,
main/dialog ids1150/1161..1163/1165/1166 and stat prompts11730..11760 in steps of5.
The readable [Central](../../lua/01-lobby-hub/06-lobby-quest-board_e824/000-msg-prg1000.lua) and
[Shop](../../lua/01-lobby-hub/07-lobby-shops_e828/057-msg-prg1000.lua) reconstructions agree with
those audited literals. Widget initialization still owns the later dispatch of
its assigned dialog IDs; that runtime path remains open.

This proves pack-local ownership and specific raw control-flow prefixes. Runtime
collection ordering, lookup winners across infos, filesystem fallback, all text
branches and real localized display remain dependencies to close.

## Coverage, undefined selector and remaining work

The controller's valid cached parameters0..6 select a stat key. The original
out-of-range confirmation path instead consumes the incoming saved s0 register.
The reference exposes that register explicitly as `incoming_s0` for those raw
state cases; it does not invent a fallback stat or guard. It is an oracle input,
not an extra argument to the original game method.

Six literal string constructors contain null branches even though their preceding
lui/addiu loads a fixed nonzero address immediately before bnez. The twelve
unexecuted words are checked against those exact instruction sequences. Thirty-two
Ghidra-excluded zero words in the controller and the script helper's independently
proven padding at3f5974 account for the remaining unexecuted addresses.

```sh
python3 testing/test_xdata_controller_retail.py
python3 testing/test_xdata_script_retail.py
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

The2,501 cases cover state/substate/allocator combinations; signed cost/cap/balance
boundaries; all seven counters, short/negative counts and overflow; four selected
players; callback changes, string ownership and null fonts; invalid cached selector
register behavior; and actual tree-driven quote/cancel/accept/continue/close flows.
The three adjacent scoped-reference cleanup helpers are byte-identical and tested
for returned wrapper, low23-bit release and signed low16-bit delete flags. Their
original template types are not guessed. Private input frames are translated
before execution, with no copied retail output.

The [shared selector and three initializers](shop-selectors.md), including stat
cost refresh, now have complete behavioral recovery and composed owner/widget
coverage. The actual SELECTCTRL receiver/input, XdataChip43aae0 and inherited
ListCtrl40dae0/40dbf0/40dd30 remain explicitly reviewed callback dependencies.
Recover them alongside RECALCPLAYER. The other five primary service updates total16,260 reviewed
bytes before their dependencies; BANK/CNOS/DISK/ShopDevice/JUNK, LABO/CARD, saving
and the [full hub script/dispatch closure](../systems/hub-recovery.md) remain open.

The complete inherited ListCtrl paging block and chip-specific page-count/text helpers are
recovered: [five bodies /2,196 bytes](list-controller-chip-view.md),
with all 2,196 bytes exact and3,149 original-instruction comparisons. The chip text
helper's full1,072-byte return span is restored. The primary chip transaction
update43aae0 /7,232 bytes still requires complete recovery; cost/stat/property
services and actual upgrade outcomes remain open. This adds helper recovery,
not acceptance of the chip service as a whole.
