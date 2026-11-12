# Main Lobby hub recovery

Objective: readable, evidence-backed and byte-verified recovery
of the Terminal Area, Central Areas, Shop Area and Commander Room, including
their original scripts and native game-code dependencies.

## Scope and accounting

The core script packs are NDMW entries 816, 820, 824 and 828: **393 chunks**.
The existing [Lua tree index](../engine/lua-tree-layout.md) identifies their
content; retail warp observations
identify stagML11 as Terminal, ML12/ML14 as Central, ML13 as Shop and ML02 as
Commander Room. These labels do not establish that each scene's complete asset
and script ownership is recovered. Entry 824 references both Central variants;
their preparation/selection needs explicit native-controller evidence.

The [generated inventory](hub-inventory.md) records source call sites, queued
named chunks, literal SD messages and the known direct native dependency graph.
Regenerate the base graph first:

```sh
python3 scripts/lua_engine_dependencies.py --write
python3 scripts/hub_recovery_inventory.py --write
python3 scripts/hub_recovery_inventory.py --check
python3 testing/test_hub_recovery_inventory.py
```

The inventory observes 49 bound APIs and reaches 508 native functions /
117,120 bytes (sizes from `config/SLUS-20836/symbols.txt`), with 110 unresolved
register transfers. This is a **lower bound**, not a completion percentage or a
remaining function estimate. The shared closure is 985 functions / 240,640 bytes.
Direct APIs do not reveal SD receiver implementations,
data-held callbacks, model programs or arbitrary named-chunk ownership. Shared
SDK and middleware bodies also need classification at the platform boundary.
The current generated inventory is authoritative when these counts change.

All game Lua chunks have readable text, including the shop entry's bank, disk,
weapon, armor, chip and junk dispatches. This is not verified source equivalence:
the [numeric audit](../engine/lua-numeric-audit.md) and
[decompiler limitations](../engine/lua-decompilation.md) remain applicable.
Original bytecode is the execution authority. City/item-change entries 534, 536
and 538 are related candidates in the cleaned hub folder; resolve their stage
ownership and any hub references before including or excluding them at closure.
Shared libraries and referenced chunks outside the four core packs also remain
part of the objective wherever the hub actually depends on them.

## Save Keeper named-script edge

The Central Area's `entry0824/chunk0073` queues **saveshop.lua** from its choice
branch. An offline read of the private pack's validated object/remap/pool graph
resolves that name through **beLuaInfo3100 → beLuaDataList9257, position112 →
beLuaData9523 → beLuaDataObject9524 → memory9546**. The655-byte payload begins at
pack offset2,482,480 and is decompiled as
[`entry0824/chunk0108`](../../lua/01-lobby-hub/06-lobby-quest-board_e824/108-dm-run-6.lua).

Its original bytecode contains the exact call
`DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagIS12", 90)` followed by DMrun.
The final90 is the DM scheduling delay, not a service-mode identifier. The
script closes the dialogue/portrait, clears the talk font, returns the NPC to
WAIT, disables player control and starts the change fade before queueing the
destination. Actual destination preparation, save controllers, success/error
return and persistent payload handling remain dependencies to recover.

This pack-local info has **123 distinct script names referring to114 data
objects**. Named bindings and decompiled chunk counts are not interchangeable.
The ownership result does not establish runtime collection order, lookup winners
across other infos, or filesystem fallback closure. In particular, the separate
SUBWND CARD caller in the character-select pack must not stand in for this save
route or for Booster Pack/album behavior.

Reproduce without modifying the archive:

```sh
python3 testing/test_savekeeper_script_retail.py
```

The test checks the actual reference graph, aligned pool extent, unique names /
shared payloads, consumed Lua size, chunk position and exact instruction/constant
sequence for the delayed stage request. It skips explicitly if the private archive
is unavailable; with the real input it passes. Existing
retail route observations in the game reference remain separate evidence.

## Completion contract

| Requirement | Evidence needed | Current boundary |
| --- | --- | --- |
| Scene and script ownership | Authored pack/manager roster, named-chunk resolution, startup/update/unload and both Central variants | Four core packs inventoried; full scene/receiver closure open |
| Scripts and progression | Reviewed original-bytecode control flow for conversations, flags, quests, difficulty and return visits | Readable corpus available; exhaustive hub branch validation open |
| Shared Lua/SD/DM engine | Complete producers/receivers, object lifetime and callback paths, matching C for game bodies | Substantial recovery; direct and indirect frontier still open |
| Actors, collision, camera and materials | Complete relevant controller bodies and retail state comparisons | Complete recovery open |
| Portals and stage lifecycle | Every hub transition, travel selection, return point, cancellation, preparation failure and unload | General portal services/transitions open |
| Shop services | WPU/APU/CHIP/DISK/JUNK controller trees, stock, price, eligibility, buy/sell, results, preview, close and errors | Scripts and stock-selection preparation recovered; transactions/controllers remain open |
| Central services | BANK/CNOS/LABO/XDATA, card/album, NPC interaction and associated record transactions | Partial shared records/menu foundations; dedicated service recovery open |
| Saving | Save Keeper control flow, persistent payload/results, cancellation/error and reload evidence | Save format recovered; `stagIS12` save scene, `stagIS11` (CARD) / `stagIS13` (LOADCTRL2) interface scenes and a retail post-save trace open |
| Matching verification | Zero mismatches, recovered-access baseline retained, byte-identical retail section | Required at each recovery checkpoint |
| Hub case coverage | Controlled fresh/return/progression/difficulty and one-to-four-player hub cases | Exhaustive hub matrix open; multiplayer stock and ownership must be included |

Recovery closure requires all reachable relevant game-code bodies to be readable
and matched and all unresolved dispatch sites classified or resolved. A source
definition or decompiler output alone does not establish
completion. Preserve original behavior; do not introduce a
replacement hub or modernize the original scripts to satisfy this goal.

## Current work queue

1. The alias-pool dependency beneath the Lua object/message path:
   the complete54-body method run plus factory covers factory/initialization, locks,
   event tracker, accounting, ownership, diagnostics and allocation backend, in
   1,040 instructions; backing/base/lock/file services are separate.
   See [runtime evidence](../engine/alias-pool-runtime.md).
2. Resolve the inventory's SD receivers and named-chunk ownership, starting with
   SUBWND's controller factory at 3d59b0 and commands at 3d60e0. The
   [lifecycle prefix](../engine/subwindow-lifecycle.md) covers all11 modes,
   including CARD's central-area
   return and non-STATUS shopexit.lua. The complete5,264-byte [preparation body](../engine/subwindow-preparation.md)
   covers stock tiers,
   multiplayer/species selection and reference callbacks. The9,820-byte
   [command receiver](../engine/subwindow-command.md) covers status/preview snapshots.
   All11 manager bodies total 17,616 bytes. Concrete
   service outcomes remain open.
   CARD has a literal front-end caller in entry808; its name does not by itself
   identify Booster Pack/album or Save Keeper behavior. Track all ten
   non-STATUS modes, including CARD and saved/card-return paths, rather than
   treating the STATUS parent as their implementation.
3. The [generic shop-root metadata block](../engine/shop-root-metadata.md)
   is seven bodies /416 bytes:
   212 bytes that include 84 under anonymous
   factory/ensure names, 12 bytes of classification/matching, the 76-byte
   accessor and the 116-byte vtable getter
   (`src/game/ndmw/beNDMWShopCtrl00.inc`).
   The concrete class vtable53feb0 raw92 identifies update4267b0, also selected
   by the tree updater. The [root runtime/window tree](../engine/window-tree-and-shop-root.md)
   is six complete bodies /2,980 bytes,
   including all mode factories, child binding/update/removal and the
   actual child-close helper, in `src/unmatched/`
   (`beNDMWWindow_RequestChildrenClose.c`, `beNDMWWindow_BindContext.cpp`,
   `beNDMWWindow_UpdateTree.cpp`, `Gap__Bec__beNDMWShopCtrl00__vfunc_21.cpp`,
   `FUN_00426fa0.cpp` and `FUN_00427020.cpp`); concrete selected
   service controllers and transaction/result producers remain open. The
   [presentation/title module](../engine/window-presentation.md) is
   eight bodies /2,628 bytes;
   concrete text/model receivers remain dependencies. Recover the
   five remaining primary service updates /16,260 reviewed bytes in hub execution
   order. The [XDATA controller](../engine/xdata-controller.md) has complete
   update/cleanup recovery and a verified txt_shop.lua
   binding in both core packs. Its widget/chip/recalculation dependencies
   remain open. The [selector widgets](../engine/shop-selectors.md)
   have six complete bodies /7,916 bytes (the 772-byte shared update at 4233f0 is in
   `src/unmatched/Gap__Bec__beNDMWWindowSelect__vfunc_21.cpp`), plus 76 metadata bytes. Their SELECTCTRL
   input/receiver and chip dependencies are in the sections below; the
   recalculation contract remains open. Review the corresponding script branches.
4. Close every hub transition, progression state and multiplayer-dependent branch.

### SELECTCTRL manager, handler and pad selection

[Receiver/pad-manager entry methods](../engine/selectctrl.md) are two
bodies / 100 bytes. Raw 136 is lazy pad-manager acquisition, not cleanup. The occupied handler's
complete body is 1,960 bytes in the generated extents; a 1,932-byte extent
truncates its return.

The [complete manager update/general handler](../engine/selectctrl.md) are
4,824 bytes (the 2,864-byte update and the
1,960-byte handler) with 1,187 non-padding words, covering input/confirmation/cancel/FO2TOP,
registry/work/list/string ownership and full generate/close lifecycles
(`src/game/beSelectCtrl.cpp`).

The [original pad-record lookup](../engine/selectctrl.md#original-pad-record-selection)
executes beneath SELECTCTRL. Its 88-byte body is
named from original callers/reflection; see
`src/game/bePadManager.cpp`.

Actual pad acquisition and sampling, model execution and message services
remain open boundaries.

### Shared destruction

Two complete dependency bodies total **460 bytes**: generic object teardown
268 and base window-controller cleanup 192. Each retains a single explicit
four-byte register copy within readable C/C++ logic; window cleanup also retains
its original NOP.

### Owner/manager protocol composition

The [owner/manager protocol](../engine/shop-selectors.md#owner-and-selectctrl-protocol) routes common
shop-selector requests through the SELECTCTRL handler/update and pad lookup, then
the close helpers, across four players and all returned indices 0..6. It describes
result/completion publication, pending waits, cancellation, rejection recovery and
FO2TOP busy/ready behavior. Actual ShopSelect initialization, XDATA transactions
and complete script/dispatch closure remain open.

### Shared ListCtrl paging and chip-view helpers

The five [paging/view helper bodies](../engine/list-controller-chip-view.md)
are 2,196 bytes: previous/next page and
chip page counting 864 bytes, the arrow initializer 260 and chip RefreshText
1,072. The contiguous three-method ListCtrl block is 916 bytes and the full chip
count/text block is 1,280 bytes. Register bindings and a small explicit scheduling
projection preserve the original RefreshText body; source does not imply an
assembly-free or original-declaration claim. The reviewed extents include the
helpers' full return spans (8 bytes), without changing the retail image.

These are utility dependencies, not chip pricing/recalculation/debit outcomes.
Actual item/status/recalculation/receiver/script
execution and other lobby services remain open.

### Chip transaction controller

The [complete chip update](../engine/chip-controller.md) is 7,232 bytes: 1,761 reachable
non-padding words and 47 padding/static-dead words. Inventory rebuilding, equipped
preview restoration, notice/confirmation, current-record increment and fresh
XDATA debit are recovered. Item/status/recalculation/message/script and selector
execution remain dependencies; full hub acceptance remains open.
The update is in `src/unmatched/Gap__Bec__beNDMWShopCtrlXdataChip__vfunc_21.cpp`.

### Item/database lookup and return ABI

The [ten-body lookup chain](../engine/item-database.md) is 1,168 bytes:
952 bytes beside three 72-byte wrappers with explicit return/status contracts.
The chain composes concrete chip
selection, database readers and existing property-name lookup. Delivery through
the DATABASE receiver remains open. The index finder's extent includes its
full 192-byte return span.
