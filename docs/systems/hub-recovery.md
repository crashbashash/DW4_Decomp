# Main Lobby hub recovery

Objective: readable, evidence-backed and byte-verified recovery
of the Terminal Area, Central Areas, Shop Area and Commander Room, including
their original scripts and native game-code dependencies. Native port operation
is a separate milestone; a bounded working lobby does not close this recovery.

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
Finding [#901](../findings/findings-0751-1000.md#f901) records the static snapshot and its limits.
Regenerate the base graph first:

```sh
python3 scripts/lua_engine_dependencies.py --write
python3 scripts/hub_recovery_inventory.py --write
python3 scripts/hub_recovery_inventory.py --check
python3 testing/test_hub_recovery_inventory.py
```

The inventory observes 49 bound APIs and reaches 508 native functions /
117,120 bytes; 94 functions / 48,540 bytes have no C source yet (of the other 414,
409 are `match` and 5 `foreign-profile` in `data/check-categories.tsv`; sizes from
`config/SLUS-20836/symbols.txt`), with 110 unresolved
register transfers. This is a **lower bound**, not a completion percentage or a
remaining function estimate. The shared closure is 985 functions / 240,640 bytes
([#924](../findings/findings-0751-1000.md#f924)); 868 of them have C source (851 `match`, 16 `foreign-profile`, 1 `code-only`)
and 117 / 61,900 bytes have no C source yet. Direct APIs do not reveal SD receiver implementations,
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

## Save Keeper named-script edge ([#906](../findings/findings-0751-1000.md#f906))

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
| Shared Lua/SD/DM engine | Complete producers/receivers, object lifetime and callback paths, matching C for game bodies | Substantial behavioral recovery; direct and indirect frontier still open |
| Actors, collision, camera and materials | Complete relevant controller bodies and retail state comparisons | Terminal port supports bounded movement, jumps, arrival, gates/heal and box camera; complete recovery open |
| Portals and stage lifecycle | Every hub transition, travel selection, return point, cancellation, preparation failure and unload | General portal services/transitions open |
| Shop services | WPU/APU/CHIP/DISK/JUNK controller trees, stock, price, eligibility, buy/sell, results, preview, close and errors | Scripts and stock-selection preparation recovered; transactions/controllers remain open |
| Central services | BANK/CNOS/LABO/XDATA, card/album, NPC interaction and associated record transactions | Partial shared records/menu foundations; dedicated service recovery open |
| Saving | Save Keeper control flow, persistent payload/results, cancellation/error and reload evidence | Save format, save library and the hosted `stagIS12` save scene implemented and headless-tested; `stagIS11` (CARD) / `stagIS13` (LOADCTRL2) interface scenes and a retail post-save trace open |
| Matching verification | Zero mismatches, recovered-access baseline retained, byte-identical retail section | Required at each recovery checkpoint |
| Behavioral coverage | Controlled fresh/return/progression/difficulty and one-to-four-player hub cases | Exhaustive hub matrix open; multiplayer stock and ownership must be included |

Recovery closure requires all reachable relevant game-code bodies to be readable
and matched, all unresolved dispatch sites classified or resolved, and the
documented platform substitutions explicitly bounded. A passing narrow oracle,
source definition, decompiler output or native playable demonstration alone does
not establish completion. Preserve original behavior; do not introduce a
replacement hub or modernize the original scripts to satisfy this goal.

## Current work queue

1. The alias-pool dependency beneath the Lua object/message path is matched.
   The complete54-body method run plus factory has readable recovery and286
   original-instruction cases, including factory/initialization, locks, event
   tracker, accounting, ownership, diagnostics and allocation backend ([#902](../findings/findings-0751-1000.md#f902)).
   All1,040 instructions are exercised; backing/base/lock/file services remain
   explicit leaves. All 54 bodies /4,160 bytes have exact source (39 in `src/engine/`,
   15 in `src/unmatched/`). Exact matches include [#900](../findings/findings-0751-1000.md#f900)'s 152-byte setter, [#902](../findings/findings-0751-1000.md#f902)'s 108-byte
   teardown and 160 tail bytes from the [#903](../findings/findings-0751-1000.md#f903) compiler follow-up.
   See [runtime evidence](../engine/alias-pool-runtime.md).
2. Resolve the inventory's SD receivers and named-chunk ownership, starting with
   SUBWND's controller factory at 3d59b0 and commands at 3d60e0. The
   [lifecycle prefix](../engine/subwindow-lifecycle.md) has full11-mode
   behavioral recovery and1,072 retail cases ([#905](../findings/findings-0751-1000.md#f905)), including CARD's central-area
   return and non-STATUS shopexit.lua. The complete5,264-byte [preparation body](../engine/subwindow-preparation.md)
   has843 retail cases, including lifecycle composition, stock tiers,
   multiplayer/species selection and reference callbacks ([#907](../findings/findings-0751-1000.md#f907)). The9,820-byte
   [command receiver](../engine/subwindow-command.md) has272 retail cases ([#908](../findings/findings-0751-1000.md#f908)), including status/preview snapshots and full all-mode
   lifecycle composition. All11 manager bodies /17,616 bytes are behaviorally
   recovered and all 11 match. Concrete
   service outcomes remain open; no new native menu functionality is implied.
   CARD has a literal front-end caller in entry808; its name does not by itself
   identify Booster Pack/album or Save Keeper behavior. Track all ten
   non-STATUS modes, including CARD and saved/card-return paths, rather than
   treating the STATUS parent as their implementation.
3. The [generic shop-root metadata block](../engine/shop-root-metadata.md)
   has complete seven-body behavioral recovery /416 bytes and117 retail cases
   ([#909](../findings/findings-0751-1000.md#f909)); all seven bodies /416 bytes match: 212 bytes that include 84 under anonymous
   factory/ensure names, 12 bytes of classification/matching from [#909](../findings/findings-0751-1000.md#f909), the 76-byte
   accessor ([#913](../findings/findings-0751-1000.md#f913)) and the 116-byte vtable getter
   (`src/unmatched/beNDMWShopCtrl00_GetVTable.cpp`).
   The concrete class vtable53feb0 raw92 identifies update4267b0, also selected
   by the tree updater. The [root runtime/window tree](../engine/window-tree-and-shop-root.md)
   has six complete behavioral bodies /2,980 bytes and1,057 retail cases
   ([#910](../findings/findings-0751-1000.md#f910)), including all mode factories, child binding/update/removal and the
   actual child-close helper. All six bodies match in `src/unmatched/`
   (`beNDMWWindow_RequestChildrenClose.c`, `beNDMWWindow_BindContext.cpp`,
   `beNDMWWindow_UpdateTree.cpp`, `Gap__Bec__beNDMWShopCtrl00__vfunc_21.cpp`,
   `FUN_00426fa0.cpp` and `FUN_00427020.cpp`); concrete selected
   service controllers and transaction/result producers remain open. The
   [presentation/title module](../engine/window-presentation.md) has223 retail
   cases with actual root/tree/title close composition and all eight bodies /2,628 bytes
   matched ([#911](../findings/findings-0751-1000.md#f911)); concrete text/model receivers remain dependencies. Recover the
   five remaining primary service updates /16,260 reviewed bytes in hub execution
   order. The [XDATA controller](../engine/xdata-controller.md) has complete
   behavioral update/cleanup recovery,2,501 retail cases and a verified txt_shop.lua
   binding in both core packs ([#912](../findings/findings-0751-1000.md#f912)). Its five bodies match; its widget/chip/recalculation dependencies
   remain open. The [selector widgets](../engine/shop-selectors.md)
   have six complete behavioral bodies /7,916 bytes and576 composed/isolated
   retail cases ([#913](../findings/findings-0751-1000.md#f913)), with five bodies /7,144 bytes matched and the 772-byte shared
   update at 4233f0 `foreign-profile` (code bytes identical only under a provisional compiler override;
   `src/unmatched/Gap__Bec__beNDMWWindowSelect__vfunc_21.cpp`), plus the 76 exact metadata bytes. Their SELECTCTRL
   input/receiver and chip dependencies have behavioral recovery (sections below); the
   recalculation contract remains open. Review the corresponding script branches.
4. Close every hub transition, progression state and multiplayer-dependent branch;
   retain a separate native integration queue in the port's owning docs.

This work adds recovery and evidence; it does not expand native gameplay
acceptance.

### SELECTCTRL manager, handler and pad selection ([#914](../findings/findings-0751-1000.md#f914)–[#916](../findings/findings-0751-1000.md#f916))

[Receiver/pad-manager entry methods](../engine/selectctrl.md) are two exact
bodies / 100 bytes. Raw 136 is lazy pad-manager acquisition, not cleanup. The
metadata getter and inherited dispatch check also match. The occupied handler's
complete body is 1,960 bytes in the generated extents; a 1,932-byte extent
truncates its return.

The [complete manager update/general handler](../engine/selectctrl.md) have
readable behavioral source / 4,824 bytes (the 2,864-byte update and the
1,960-byte handler) and 4,089 original-instruction cases.
All 1,187 non-padding words execute, including input/confirmation/cancel/FO2TOP,
registry/work/list/string ownership and full generate/close lifecycles. Both
bodies match (`src/unmatched/Gap__Bec__beSelectCtrl__vfunc_31.cpp` and
`src/unmatched/Gap__Bec__beSelectCtrl__vfunc_33.cpp`).

The [original pad-record lookup](../engine/selectctrl.md#original-pad-record-selection-916)
executes beneath SELECTCTRL in 216 composed cases, with 201 direct cases;
manager coverage is 4,089, for 4,506 total. Its 88-byte body is fully recovered
behaviorally and named from original callers/reflection; it matches as
`src/unmatched/bePadManager_GetPadForPlayer.c`.

Actual pad acquisition and sampling, model execution, message services and the
combined manager/widget/XDATA suite remain open boundaries. A read-only matching
audit over 347 direct hub functions without source ([#916](../findings/findings-0751-1000.md#f916)) returned zero
automatic matches, with eleven candidates within three instruction words.

### Shared destruction matching ([#917](../findings/findings-0751-1000.md#f917))

Two complete dependency bodies match, **460 exact bytes**: generic object teardown
268 and base window-controller cleanup 192. Each retains a single explicit
four-byte register copy within readable C/C++ logic; window cleanup also retains
its original NOP. Exact source and the byte-identical relink separately verify
the original bodies. Existing portable adapter boundaries and native acceptance
are unaffected.

### Owner/manager protocol composition ([#918](../findings/findings-0751-1000.md#f918))

The [joint oracle](../engine/selector-manager-composition.md) routes common
shop-selector requests through the real SELECTCTRL handler/update and pad lookup,
then the real empty-queue close helpers: 144 lifecycles / 3,146 checkpoints across
four players and all returned indices 0..6. It verifies actual result/completion
publication, pending waits, cancellation, rejection recovery and FO2TOP busy/
ready behavior. Immediate delivery and primitive/model/device services remain
controlled; actual ShopSelect initialization, XDATA transactions, nonempty close
queues and complete script/dispatch closure remain open. It adds no matching bytes.

### Shared ListCtrl paging and chip-view helpers ([#919](../findings/findings-0751-1000.md#f919), [#922](../findings/findings-0751-1000.md#f922), [#923](../findings/findings-0751-1000.md#f923))

All five [paging/view helper bodies](../engine/list-controller-chip-view.md)
match / 2,196 bytes, with 3,149 original-instruction cases: previous/next page and
chip page counting 864 bytes, the arrow initializer 260 and chip RefreshText
1,072. The contiguous three-method ListCtrl block is 916 bytes and the full chip
count/text block is 1,280 bytes. Register bindings and a small explicit scheduling
projection preserve the original RefreshText body; source does not imply an
assembly-free or original-declaration claim. The reviewed extents include the
helpers' full return spans (8 bytes), without changing the retail image.

This closes utility dependencies, not chip pricing/recalculation/debit outcomes,
native UI or native rendering acceptance, and it does not close the full lobby
goal. Chip transaction matching under its unit profile (the update is
`foreign-profile`), actual item/status/recalculation/receiver/script
execution and other lobby services remain open; native acceptance is separate.

### Chip transaction controller ([#921](../findings/findings-0751-1000.md#f921))

The [complete chip update](../engine/chip-controller.md) has behavioral
source for 7,232 bytes and 1,076 original-instruction comparisons. All 1,761 reachable
non-padding words execute; 47 padding/static-dead words are checked. Actual page
count and context binding compose in 18 cases. Inventory rebuilding, equipped
preview restoration, notice/confirmation, current-record increment and fresh
XDATA debit are recovered. Item/status/recalculation/message/script and selector
execution remain controlled dependencies; full hub/native acceptance remains open.
The update is `foreign-profile` in `data/check-categories.tsv`
(`src/unmatched/Gap__Bec__beNDMWShopCtrlXdataChip__vfunc_21.cpp`): its code bytes
are identical to retail only under a provisional compiler override, not under its unit profile.

### Item/database lookup and return ABI ([#924](../findings/findings-0751-1000.md#f924))

The [ten-body lookup chain](../engine/item-database.md) is exact / 1,168 bytes:
952 bytes beside three 72-byte wrappers whose explicit return/status contracts
are part of the match. The 474-case oracle composes concrete chip
selection, database readers and existing property-name lookup. Delivery through
the DATABASE receiver remains controlled. The index finder's extent includes its
full 192-byte return span.
