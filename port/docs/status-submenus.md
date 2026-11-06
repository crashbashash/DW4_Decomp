# Equipment, folder and skill controller orchestration

`src/statussubmenu.c` supplies native callbacks for retail equipment controller
`0x0040ee60`, folder controller `0x004196c0` and skill controller `0x0041f190`.
`src/statusscene.c` supplies the STATUS manager's accepted-GENERATE freeze,
first-update entry and root-completion restoration ordering. These are concrete
controller boundaries with required view/player/scene sinks. The concrete
authored STATUS tree is assembled and connected to the normal-boot lobby
factory, drawing and scene restoration; see
[live ownership](status-menu.md#live-factory-wiring). The SUBWND manager, the
window update boundary and the root/title/selector state machines are in
[status/menu ownership](status-menu.md).

## Source ownership

| Source | Retail routines | Owns |
| --- | --- | --- |
| `statussubmenu.c` | `0x0040ee60`, `0x004196c0`, `0x0041f190` | Scalar callbacks of the equipment, folder and skill controllers |
| `statusscene.c` | manager freeze/entry/restoration, `3d8740` | STATUS scene lifecycle ordering and currency clamps |
| `statusmenu.c` | `40de80` | Root composed with its real children |
| `statusequipmentmenu.c` | `40ee60` | Equipment menu window: title, menu, descriptions and the three gear children |
| `statusview.c` | Select01 `0x00423bf0`, SelectE0 `0x00423f00`, SelectE1 `0x00424070` | Authored selectors |
| `statusequip.c` | `0x0040f720` | Shared equipment-base scalar update |
| `statusequiprecords.c` | Power/Main/Sub virtual methods | Action routing, eligibility and record transactions |
| `statusgear.c` | blank helper `411750` | Owned Power/Main/Sub models, selectors and DEVICE children |
| `statusui.c` | `3f5c90` | Resource and SD operations shared by the concrete owners |
| `statuscontent.c` | `0x418ac0`, `0x4432a0`, `0x420230`, `41aaa0`, number renderer `4402e0` | Item, DEVICE, skill and important-item content projection; number rendering |
| `statusskill.c` | `41f190` | Owned skill controller |
| `statuspage.c` | `40dbf0`/`40dd30` | Page input |
| `statusdevice.c` | `418090`, `4191f0`, `412600` | DEVICE controller state, row decisions and new-hover gate |
| `statusdeviceview.c` | | Owned DEVICE window |
| `statusdetail.c`, `statusdetailctrl.c` | `4207a0` | DEVICE detail (discard/arrange/give) owner and outer update |
| `statusflag.c` | `41a400` | Important-item (Key Folder) page |
| `statusfolder.c` | `4196c0` | FOLDER window and its children |
| `statusdisk.c`, `statusdiskctrl.c` | `41acf0` | DISK page owner and outer update |
| `statusbit.c`, `statusbitctrl.c` | CtrlBit `41d810`, SendBit `41de40` | Currency windows and outer controllers |

## Window ownership and selection

Each controller runs as an exclusively owned `dw4_menu_window`. COUNT reads the
actual compacted child list. Successful CREATE and SKILL_SETUP must append an
owned child before returning; an empty successful sink is rejected. Child
selectors publish their result into the owner's arena `_retCode`. Closing
keeps the parent's active flag until tracked models finish and children are
actually pruned. Query and rendering calls cannot advance a window.

Equipment opens title text call 30, waits for `i_sttitle/SQ_OPEN` or
`i_messwn/SQ_STOPEN`, and creates menu call 31. With entry code one it creates
the StatusTitle02 band `3b3900` with call 0 instead of the title; this is the
Digi-Lab weapon check ([Digi-Lab](labo-shop.md)). Highlight
changes run `txt_status.lua` calls 35–37. Accepted rows route to PowerSocket,
MainSlot and SubSlot; PowerSocket receives count three. Completed children
restore the retained selection. Cancellation closes the controller's models,
texts and child tree through separate state-two/state-three updates.

Folder initializes title call 60 and menu call 61 in the same update. Highlight
calls start at 81. Its rows route to DEVICE, FLAG (Key Folder), DISK and BANK
(the BITS Folder, currency). DEVICE has a separate five-stage selector/detail
loop: call 43, selection-ready detection, detail creation, count-change
detection, tracked-resource reset and selector restart. Cancel clears
`STWINFONT29/font100`, closes the device selector and waits until that selector
is absent. It does not infer completion from elapsed time.

Skill opens `i_sttitle` and call 90, then creates menu call 91. Highlight calls
start at 98. Rows zero through two choose weapon techniques, numeric skill
thresholds and WAZALIST. Weapon-list acquisition determines one page below nine
entries, otherwise two. Page exit resets owned model/text resources;
threshold exit resets nine font colors. Controller close separately closes
`i_sttitle` and hides `STWINFONT12/font000`. This controller presents existing
records; it does not buy skill levels or replace CURRENT2BASE persistence.

`dw4_submenu_io` exposes these mandatory services to an owning factory. The
concrete owners below supply them: the shared `0x0040f720` controller and its
accepted-selection transaction adapter, the Power/Main/Sub views, the scrolling
DEVICE owner with its candidate/preview gate and detail actions, the skill view
and the disk/flag/currency children. The [equipment transactions](player-transactions.md)
and [stat recalculation](player-stats.md) serve those owners. No dummy
view factory or successful fallback service is installed.

## Arena controller records and retained references

The equipment/FOLDER/skill and Power/Main/Sub owners allocate their actual
`beNDMWStatusCtrl*`/`beNDMWStatusPowerSocket/MainSlot/SubSlot` classes. Common
counters/return/count snapshots and retained menu, page/offset and slot/pocket
fields are authoritative arena state. DEVICE uses `beNDMWStatusCtrlD0`, with
kind/decision list handles, bank/restriction/auto-close flags and page/cursor
fields. Detail uses `beNDMWStatusSubMenu` (`_selectDevice`, `_receipt`, recipient
and inventory-count lists); disk uses `beNDMWStatusCtrlDisk` (`_cursor`,
`_receipt`, `_sendMax` and recipient list); currency uses
`beNDMWStatusCtrlBit/SendBit` (recipient lists and edit amount/limit/recipient).
FLAG owns `beNDMWStatusCtrlFlag` common lifecycle state.

The original scalar rule entry points are unchanged. Each owner reads a
per-call projection and writes it back; no selector retains that stack address.
Children publish directly to their parent window's `_retCode`. Diagnostic state
queries return snapshots by value, with separate `*_window_is` owner probes.
Derived render projections remain host services.
See [arena scope and validation](arena-object-model.md#concrete-shop-and-status-records).

Power/Main/Sub reference fields retain the actual player folder and six item
lists. Payload leases survive property replacement and are refreshed at update
boundaries. Detail's `_deviceFolderList` is the retained D0 window (not an item
list); parent pruning detaches it, and detail completion releases the final
hold. Disk giving retains sender/recipient disk objects rather than quantity
copies. FLAG indices use `_impItems`, and Skill owns a typed Shinka snapshot.
The recovered close lists and retained item/window closures are complete; pure
rule arithmetic and service ordering are the same as in the scalar rules. See
[lifetime and limits](arena-object-model.md#menu-resources-stock-and-retained-references).

## Submenu factory identities and FOLDER routing

Factory identities follow the classes their metadata registers. Eleven original
registration/factory traces verify the classes behind the equipment/FOLDER
creation leaves: `3b9db0` is CtrlFlag and `3b9a50` is CtrlDisk (not the reverse).
Native FOLDER routes Device Folder → Key Folder → Disk Folder → BITS Folder in the
original order. The mode-one equipment leaf (create key `BAND`) is original
Title02 (message window), not Title03 (account/help). The remaining classes
resolve to Title04, Select01, PowerSocket, MainSlot, SubSlot, CtrlD0, SubMenu and
CtrlBit. Normal STATUS's BANK folder child is CtrlBit, the currency transfer; it
is not the NPC bank-inventory selector.

The comparator checks metadata class strings/globals before testing the 42,336
equipment/FOLDER/skill state/effect cases and 32 paging/restart cases (see
[validation](#validation)). Prepared FOLDER checks assert the actual returned
owner types; the SDL route enters Key Folder first, then the empty-DISK
give/refusal and no-recipient currency message, with its two message OPEN/CLOSE
cue lookups and two actual restores ([SDL controller acceptance](status-menu.md#sdl-controller-acceptance)).

## STATUS scene lifecycle

The original manager freezes at accepted GENERATE, before its first update:
MODELCTRL ONFREEZE, GENERATER ONFREEZE, SD world-disable one, SOUND ONFREEZE.
The optional `dw4_subwindow_factory.activate` callback runs at that boundary,
following successful private-tree preparation and active publication. It runs
once; repeated GENERATE cannot freeze again. Failure retains active completion
state and latches the scene, preventing factory replacement or further updates.
Activation cannot recursively tick the owner.

The first manager update clamps joined players' BIT to 9,999,999 and XDATA to
9,999, validates all four slots first, sends STAGECTL PADINPUT ENABLE and hides
WN01 then WN00. ISUSE uses the low byte; inactive slots need no BIT/XDATA fields.
STATUS does not stop lobby music or play the shop loop.

Actual root completion sends SOUND, GENERATER and MODELCTRL OFFREEZE, releases
SD world-disable, then invokes each joined player's ADDHP zero / ADDMP zero
publication in player order. WN01 and WN00 become visible afterward. The health
sink receives current HP/MP and their maxima and must implement the real
GAMERAM/player/HUD publication
([health boundary](player-records.md#live-health-restoration-boundary)). It is not
an actor-state guess. All health records are preflighted before sending
restoration commands. Failed sinks latch the lifecycle; the SUBWND owner must
retain Lua completion and stop scene work. Partial external service writes are
not rolled back or reported as success.

These lifecycle functions support STATUS mode zero. HOLD refers to world
eligibility, not the whole simulation pump: menu, model-close and script-service
clocks must keep advancing.

## Complete STATUS root assembly

`statusmenu.c` composes the verified `40de80` root
([concrete STATUS controllers](status-menu.md#concrete-status-controllers)) with
actual Title00–03, Select00, equipment, FOLDER and skill children. Title00 owns
i_stback/i_bgclear as the root's first child. The root's own resource owner tracks
its text commands, and preserves the actual count/pruning contract. The root uses
actual model sequence/run queries, native layer masks, retained main-menu choice
and close waits. Title01 refreshes through production player records, Unicode
names, database strings and status stats. There is no Title04 border on the root.

`statusequipmentmenu.c` connects `40ee60` to the original title call 30, menu
call 31, selection descriptions and all three owned gear children for normal
mode zero; the Digi-Lab opens the same window with entry code one.
Power/Main/Sub run their concrete selectors and transaction/preview owners.

Prepared tests open the full root separately for every player slot using
production SYS record queries and actual authored assets/Lua/models/fonts. They
enter every root choice, open/cancel Power/Main/Sub, retain equipment/main-menu
choices, close normally and handle external removal. All counts refer to real
owned children.

## Authored selectors and shared equipment base

`statusview.c` owns Select01 (`0x00423bf0`), SelectE0 (`0x00423f00`)
and SelectE1 (`0x00424070`). Select01 opens i_stmenu01 with
SQ_3LINEDOWNOPEN for equipment/skill text calls 31/91 or SQ_4LINEOPEN for
folder call 61. It owns STWINFONT09/font000–003 and STWINFONT29/font100,
executes original txt_status.lua and starts i_stcursor02 at (-83,172,0).
E0 owns STWINFONT29/font100 and font000–002 and uses i_stmesscr;
E1 uses i_stcursor01. Row count, selected row, position and copied enable flags
belong to each E0/E1 caller. Selection and close completion use the real native
SELECTCTRL/model owners. These selectors do not supply scrolling inventory,
item descriptions or skill-page contents.

`statusequip.c` implements the shared equipment-base scalar update (`0x0040f720`)
with owned child-list counts and mandatory virtual view operations. Its branches
cover slot/action selection, pocket selector/confirmation/inventory return, socket
swap preview/acceptance, inventory readiness, eligibility-error child/restart,
resource reset and asynchronous closing. A successful child-creation operation
must append an exclusively owned child. Failure retains the active completion
hold. Queries cannot advance these windows.

The base preserves v32's remove-action argument: `40fd68` leaves a1=-1 before
`40fd94` dispatches the virtual method. Main/Sub privately preview an empty slot;
Power ignores -1. That path never queries an absent inventory selector. Pocket
removal likewise preserves v39's -1 argument and privately clears the selected
pocket without asking an absent inventory view for a candidate.

`statusequiprecords.c` connects Power/Main/Sub action routing and accepted
inventory identities to production database eligibility, recalculation and
atomic record publication. Filtered-kind rows retain DEVICEFOLDER indices;
identical values remain distinct identities. Action row count/text-call/enable
flags follow each retail virtual method. Power uses species/skill eligibility;
Main/Sub use signed item `LVPOINT` <= player `LEVEL`. The item column is
`LVPOINT`: a numeric `LEVEL` item lookup returns the missing-column fallback.
WU/BLUEAB use the separate database boolean table (validated in
[databases](databases.md)). Accepted first Power/Main slots clear their
corresponding pocket refs, projections and equipped flags in the same private
transaction. A first-socket swap also clears POWERPOCKET.

Preview callbacks receive private recalculated records and never publish them;
suppressed same-slot/empty-first-socket comparisons restore baseline text.
Transaction staging projects through `dw4_statusstats_compare_folder`, so
preview text/colors never require temporary publication into live records.
Native staging does not model reentrant observation of retail temporary lists.

The transaction IO adapter requires a view sink, a real inventory-row resolver
and a private-stat preview sink. It implements action routing, eligibility,
accepted equipment/chip changes and socket transactions, forwarding authored
model/font/list projection operations to their required owner. No default view
or inventory resolver is installed. Missing dependencies fail explicitly.

Validation: 20,160 shared-base scalar states and virtual/service-helper traces
match retail instructions, including v32's argument as well as its call and v39's
argument; 672 Power/Main/Sub action-row count, text-call and enable-flag cases
also execute their actual virtual methods, and 98 signed Main/Sub LEVEL/LVPOINT
cases are compared. The oracle controls virtual methods, allocation, property
lookup and selector readiness; inline font writes/socket identity results are
outside that scalar trace comparison. Native tests cover 128 player/species
cycles, row identity, signed eligibility, rejected commits, private/failed
previews, socket swaps, atomic pocket clearing, accepted IO routing, window
close/failure holds, and clearing the private projection of an actually equipped
Main/Sub item while retaining every live record/reference. Expanded view
initialization compares 200 traces; original submenu text, real cursor selection
and close waits pass prepared-asset integration tests.

## Owned equipment views

`statusgear.c` connects the shared equipment controller and production record
adapter to owned Power/Main/Sub models, slot/action/pocket selectors and DEVICE
children. The resource owner supplies original text calls, pocket counts,
descriptions, action colors, socket-swap restrictions, accepted identities,
private stat comparison and asynchronous close waits. The required appearance
callback receives first-weapon swap publication; the live factory connects it to
the owner's lobby model ([owner by player slot](status-menu.md#owner-by-player-slot)).
`statusui.c` shares resource and SD operations across these concrete owners.
Constructors preflight the owning stat snapshot and do not initialize models or
run scripts.

The real ShopSelect00 error selector uses i_stmessky and the inherited
WindowSelect lifecycle. Ineligible acceptance displays original status text,
holds the DEVICE child and restarts its retained row after real popup close.

The original blank helper `411750` initializes twelve entries:
STWINFONT29/font100, both STWINFONT10 fields, eight STWINFONT11 fields
(`000..002`, `100..104`), then STWINFONT29/font100 again. The native BLANK
operation follows that order; base/message setup tracks owned fields without
displaying unused blanks, and action/description fields initialize when their
real text is supplied. Enabling the five unused STWINFONT11 `font200..204` fields
and the two STWINFONT29 action fields before use adds seven blank glyphs (42 text
vertices) to each equipment page.

Validation: the retail verifier executes the complete original blank helper with
the TEXT service controlled and checks all twelve calls. Prepared
original-Lua/font/controller tests cover weapon swaps, Main/Sub
acceptance/removal, chip insertion/removal, ineligible-item popup/retry, private
preview isolation, appearance publication, actual model/cursor close waits and
the seven unused fields staying hidden. UI/player-renderer publication in these
prepared tests is a controlled boundary.

## Item and skill content projection

`statuscontent.c` supplies the authored projection leaves required by the
view owners. Power/Main/Sub virtual 24/26/22 paths select real NAME/TXT strings,
revision colors, empty-slot visibility and Power/Main pocket names/count-driven
`i_stpocket` sequences. Descriptions append the original single pocket-count
character. DEVICE helper `0x418ac0` projects twelve rows per page, the exact
retail equipped/unequipped byte prefixes, eligibility cancel colors, bank/device
page counters and selected descriptions. Weapon record 276 and Main record 31
suppress the DEVICE pocket suffix; equipment virtual 26 still appends it.
Unsupported item database kinds fail. The important-item refresh is
[`statuscontent_flag`](#important-item-key-folder-page); DISK and currency
contents come from their own owners.

Skill list helper `0x4432a0` reads the low byte of each BASE_ISUSE entry and
BASE_LEVEL, inserts species 3 first, and preserves ascending order for the other
species. Helper `0x420230` projects eight rows per page into STWINFONT14/42/18,
page counters into STWINFONT24, shinka EXPLANATION into STWINFONT29 and WAZALIST
TXT through pcTech. Threshold selections execute original txt_status.lua calls
111–119. Page setup opens the authored BWIN/WAZA sequence, executes calls
95–97/101, projects SKILL values with the recovered level-dependent cap color,
and returns the actual selector row count, including the empty-list cases.
The nine threshold label colors have an explicit reset leaf for submenu exit.

`DW4_STATUS_CONTENT` reuses the native view resource tracker. Initialization only
runs during a window update. Repeated projection deduplicates font/model ownership,
keeps complete description strings instead of truncating at 256 bytes, and
retains actual close waits. A failed initialization or native refresh latches
completion until scene reset. CONTENT refresh does not advance menu/model clocks.
The borrowed initializer/context must outlive the window. SET_TEXT/COLOR/SWITCH
refreshes require their authored resources to have been initialized and tracked.

These are content/resource leaves; scrolling, selection and actions belong to the
controllers below. The DEVICE marker bytes match the retail helper's service
output; that trace check does not establish Unicode/icon conversion or rendered
marker parity, which the [byte-to-Unicode decoder](#shared-model-and-text-services)
and the [rendered comparison](#rendered-menu-comparison-against-retail) cover.

Validation: `check-statuscontent-retail` compares 1,470 skill refresh/description
traces, 288 DEVICE page/description traces and 520 item-color cases against actual
retail instructions. String/database/property services, formatting and list
storage are controlled leaves. The helper loops, page addressing, visibility,
suffix exceptions and color branches execute original instructions. Native
`check-statusviews` uses original STATUS Lua, copied production databases and
authored fonts for all three skill modes, equipment projections, second-page
species ordering, DEVICE short final pages, repeated resource refresh and actual
model close waits. Invalid database identities and failed-refresh holds are tested.
These checks do not establish scrolling input, detail actions or full-scene parity.

## Owned skill controller and page restart

`statusskill.c` connects the retail `41f190` scalar controller to
production player/database content and authored Select01/SelectE1 windows.
The owner opens the original skill menu and all three page modes, refreshes
selection descriptions through original STATUS Lua, retains the selected mode
on return and resets threshold colors on exit. Its menu selector also owns the
caller-added blank `STWINFONT29/font000`, so closing the menu clears its final
description. Constructors do not run Lua, sample input or initialize resources.

Title and page CONTENT windows are separately owned resources; the scalar
controller counts only its actual selector children. Page exit closes/hides
tracked resources in the parent callback. The next menu waits for the retired
page's real model completion before reopening shared models/fonts. External
REMOVE closes page, selector and title and retains completion until all finish.
Failed input, initialization or refresh latches the owner until scene reset.
The SD scope must be cancelled before destroying a live tree and its services.

`statuspage.c` implements `40dbf0`/`40dd30` using separately sampled horizontal
analog edges/repeats, analog state and digital edges/repeats. Vertical analog
input inhibits paging. The skill controller tries previous before next;
successful changes send the authored left/right MOVEEND/MOVENEXT/SELECT
sequences. The page owner initializes arrow positions (-146,65,0)/(127,65,0),
including their hidden/single-page state. Native sequence commands use the SD
command interface; the retail oracle compares their model/sequence output.

Repage sets the existing selector window to state four, updates its actual row
count (eight or the short second-page remainder) and invokes FO2TOP with that
count. `423700` returns the inverse of raw ISFO2TOP; the native view applies
that inversion before restarting. Busy selectors reject repage, and queries
never update clocks. Page completion still follows actual SELECTCTRL/model
completion, including confirm and cancel; no new selector replaces an active one.

Validation: `verify_statuspage_retail.py` executes 1,152 page/input/boundary
states against original instructions, with pad acquisition and SD dispatch
controlled. The submenu oracle adds 32 page/restart states with controlled
virtual input leaves, including previous-before-next and short-page row counts.
`test_statusviews` runs all three modes through original Lua,
production records/databases, authored fonts, real SELECTCTRL and model owners.
It covers two-way paging, short-page bounds, simultaneous direction priority,
vertical inhibition, player-slot isolation, empty/single species lists,
retained mode, confirm/cancel, external close, busy restart rejection and failure
holds.

## Owned DEVICE selector and inventory preview gate

`statusdevice.c` implements retail `418090` controller state, `4191f0` row
decisions and the `412600` new-hover gate. `statusdeviceview.c` supplies an owned
DEVICE window with original `txt_status.lua` call 70, authored fonts, the
AWINON folder, page arrows at (-146,25,0)/(85,25,0) and real SelectE1 children.
The owner reads current DEVICEFOLDER records and copies item values for rendering;
the absolute inventory index remains the identity passed to transactions.

Restrictions keep every inventory row in its original position. Kind lists,
chip WU/BLUEAB byte-one tests and equipped/special-record flags produce copied
selector decisions and row colors. Unknown-enable takes precedence over both
unknown-disable and equipped-disable. Empty inventory has the original one-row
cursor and blank contents; it supplies no valid item identity. Bank mode requires
an actual BANKDEVICE property and uses its original text/page groups;
unavailable records fail explicitly. `51a0c8` and the `4cedf0` template name that
record **BANKDEVICE**, not BANKFOLDER; the
[fresh records](player-records.md#common-aliases-and-remaining-fresh-records)
create it empty. This owner has a 36-record DEVICE bound; the NPC bank's
capacity, storage and controller are in [NPC bank](bank-shop.md).

Paging uses the same previous-before-next and vertical-inhibition services as
skill pages. FO2TOP replaces row count and copied enable flags. Child completion
publishes the absolute page/row index, then either auto-closes or retains state
1/sub 2 for the caller's real detail/acceptance operation. Query APIs never tick.
Explicit restart rebuilds the selector and decisions from current inventory,
following the original single-removal row/page adjustment and boundary-arrow
updates. Close waits retain active completion until the content models and real
children finish; failures latch until scene reset. Cancel the SD scope before
destroying the tree and its borrowed services.

`dw4_statusdevice_equipment_candidate` supplies the accepted identity and the
original preview gate to `statusequiprecords.c`: a new disabled hover restores
baseline, an unchanged hover does nothing and an enabled hover reaches private
stat recalculation. Accepted held selections resolve independently of the
preview latch. Equipment transactions still publish only after confirmation;
hover previews do not replace live record buffers. The compacted candidate
list utility is separate from this retail ordered DEVICE view.

Validation: `check-statusdevice-retail` executes 4,096 row-decision cases,
6,016 scalar states/publication/restart traces and 486 inventory-preview gates
against original instructions. Property/attribute lookup, generic allocations,
selector/resource operations and stat recalculation are controlled leaves;
the row decisions, controller branches and preview admission execute retail.
Prepared view checks use original Lua, production databases/player records,
actual cursor/model waits and production transaction IO. They cover three pages,
disabled confirm, short final pages, per-player/vertical input, repeated queries,
retained acceptance, removal/restart, duplicate identities, private/unchanged/
disabled previews, accepted equipment publication, cancellation, real close and
missing-bank failure holds. The item removal itself is a controlled detail leaf
in those checks.

## DEVICE detail and its retained owner

`statusdetail.c` owns the original `4207a0` discard/arrange/give menu, its
SelectE1/E0 and ShopSelect00 children, model/text resources and close waits;
`statusdetailctrl.c` supplies the complete `4207a0` outer update through that
record/view owner. Discard reads weapon ISHAKAI and refuses equipped identities;
give reads ISJYOUDO, collects joined recipients in slot order and publishes their
actual Unicode names. Accepted transactions use the exact DEVICEFOLDER index and
the atomic
[inventory primitives](player-transactions.md#detail-actions-and-atomic-giving).
Original success text is call 131 and refused/full text is 149.

The original folder constructor stores the DEVICE sibling at `419d88`: detail +88
retains it. The native FOLDER context provides that dependency
through close and read-only completion callbacks. It resolves the current sibling
rather than keeping a tree pointer after pruning. An admitted give with no
supplied owner follows retail's close exit and leaves inventories unchanged.

Accepted giving closes the actual DEVICE owner and cursor, hides the detail's
tracked action text, and holds at delay one until DEVICE completion. Recipient
models/names/counts publish at delay two; the recipient selector is constructed
on the following update. The FOLDER parent observes DEVICE pruning, waits for
the detail acknowledgement to complete, then recreates DEVICE. It cannot restart
the outgoing owner or reuse it for the recipient view.

Error/acknowledgement text belongs to its real ShopSelect00 child, with original
construction and close ordering. Initial detail resources track only the authored
action rows; recipient resources join the tracker when that phase is published.
Final transfer/full-recipient acknowledgement preserves the original negative
latch and restores `STWINFONT14/font000` DEFAULTCOLOR during close. Actual model
and child completion still gate final deactivation; no elapsed-frame estimate
replaces either completion query.

Validation: `make check-statusdetail-retail` executes 9,861 outer states against
the private retail instructions, comparing scalar state, filtered
resource/script/cursor/color effects, retained-owner close/wait, byte-truncated
refusal flags, capacity decisions and record-list transfers. Constructors,
properties, model programs, selectors and sort helpers are controlled leaves; the
inventory primitives keep their separate signed/identity/atomic checks. Prepared
tests exercise discard confirmation, arrange, a successful recipient transfer,
full-recipient/no-recipient holds and an equipped-item error acknowledgement
through actual Lua/fonts/model waits. Native authored-view tests verify a held
completion leaf, separate recipient publication/selection updates, Bob's Unicode
name, default-color restoration and the absent-owner no-transfer exit. The
complete FOLDER give/ack/recreation route uses the real DEVICE, actual
model/selector close and sibling pruning with production records; its completion
dependency is not controlled. This verifies the dependency and outer timing,
not live multi-player ownership or full-frame retail parity.

## Important-item (Key Folder) page

`statusflag.c` owns the important-item page `41a400`, collecting every nonzero
common FLAGFOLDER byte in ascending index order (the common record is the
[alias](player-records.md#common-aliases-and-remaining-fresh-records) onto player
zero's records). It uses the actual impItem NAME/TXT columns, original call 71/135, twelve
STWINFONT14 rows, page counters, SelectE1 and i_stfolder SQ_FLAGOPEN. Both
STWINFONT23 fields initialize with RIGHT alignment and a space, as the original
does (not visible zeroes).

Validation: `statuscontent_flag` matches 316 original `41aaa0` refresh command
traces, with database/property lookup controlled. The view retail verifier
executes the original inline Key `41a64c..41a704` and DISK `41af04..41afac`
initialization segments: all forty service calls match the literal font names,
alignment and blank text. Prepared owner checks use the production common alias,
authored assets and real selectors for empty/two/full lists, selection changes,
cancellation, external close and malformed-record failure holds, and check both
blank Key fields.

## Complete FOLDER ownership

`statusfolder.c` connects the verified `4196c0` scalar orchestration to an
actual title/menu, retained DEVICE owner and detail child, DISK, important-item
FLAG and currency BANK windows, in the
[routing order above](#submenu-factory-identities-and-folder-routing). Child
counts are read from the owned tree; DEVICE restarts only after the detail child
has closed and been pruned. The children are described in
[DEVICE](#owned-device-selector-and-inventory-preview-gate),
[detail](#device-detail-and-its-retained-owner),
[Key Folder](#important-item-key-folder-page),
[DISK](#disk-outer-lifecycle-and-resource-ownership) and
[currency](#currency-composition-and-outer-update).

Prepared checks enter every choice, arrange an inventory identity, restart/cancel
the retained DEVICE, return from each remaining page and close the complete tree.
FOLDER reuse checks positive panel alpha on the reopened `i_stfolder`
([model REMOVE](#shared-model-and-text-services)).

## DISK outer lifecycle and resource ownership

`statusdisk.c` owns the original `41acf0` paths for ordering and quantity giving;
`statusdiskctrl.c` supplies the complete `41acf0` outer update through mandatory
native resource/record sinks in `statusdisk.c`.

The page displays all twelve DISKFOLDER records but both its main and reorder
selectors address the first ten; the currently selected reorder row is disabled.
The twelve STWINFONT15 quantities initialize with RIGHT alignment and a space.
Item strings use the actual `conItem` database (virtual getter `4486f0`, literal
`51d5a0`). Giving finds the recipient's first matching record across all twelve
positions. Quantity is stored in the native item's revision word (retail +20),
and each recipient caps at nine. ShopSelect52/i_stcursor05 chooses `limit - row`,
starting at one. Original calls 141/142/143 cover empty source/no recipient/full
recipient, and call 132 acknowledges a successful transfer. Transfers use the
atomic identity-preserving record owner.

The recipient-entry delays are 0 → 1 → 2 → 4 across three updates: retirement
sends model/text close and releases its tracking, then the recipient panel and
selector publish at delay two. The outgoing `i_stfolder` close can still be
running; the controller does not wait for retired resource windows at this
boundary. Final controller closure still waits for actual model completion and
child pruning.

Recipient confirmation opens the row cursor first, then constructs the quantity
selector on the next update. Quantity text refresh and its changed-row latch
follow the original six/seven phases. Full recipients enter delay ten before
creating the error popup; empty/no-recipient giving retains the original popup
snapshot update. Acknowledgement, cancellation and main-page restoration keep
their original fallthrough behavior.

Construction-issued action-menu models, blank rows, input prompts and popup
text belong to the actual selector children. Explicit
`dw4_statusview_window_prepare` records those resources before the first
recursive selector update without advancing its clock. It lets the parent's
original text call populate the rows after their blank setup, and makes their
real close programs and text cleanup part of child completion.

Validation: `make check-statusdisk-retail` executes 10,051 outer states against
the private retail ELF, comparing scalar state, selected rows, limit, filtered
script/cursor/refresh/quantity effects, reordered record identities and
source/recipient quantity writes. It covers all outer sub/delay branches,
empty/no-recipient/full-recipient cases and legal cap/quantity positions.
Constructors, property/record selection, fonts and model programs are controlled
leaves; the ownership adapter has separate real-asset checks. `test_statusviews`
verifies the precise native recipient-entry updates while the outgoing authored
model still runs, checks Bob's name at publication, checks all twelve quantity
alignments, and covers original content, swapping, capped giving,
reorder/transfer/error/cancel, full/empty messages, cancellation/restoration and
all four complete-root slots. Transaction tests also preserve joined flags, the
last two records and receiver identity after donor reordering. This establishes
DISK update timing, not retail full-frame parity.

## Currency composition and outer update

`statusbitctrl.c` implements CtrlBit `41d810` and SendBit `41de40` as separate
outer controllers. `statusbit.c` binds them to the real window tree: CtrlBit
collects other joined players in slot order and creates either a SendBit child
with that retained list or the original no-recipient ShopSelect00 popup (call
88). The wrapper remains at its child wait while SendBit owns recipient selection,
seven-digit editing, transfer and acknowledgement. Child pruning and final
completion close the wrapper; its state is not the amount editor's state.

SendBit owns the authored resources, Unicode names, balances, seven-digit
selector, edit sound, transfer acknowledgement and return/cancel paths. It uses
original i_stcursor03 ShopSelect34 with seven positions, starting on the units
position (six), and STWINFONT28 digits. It follows the original
creation/fallthrough boundaries and command order:

- Reset clears digits, updates its displayed balances/names and creates the
  recipient selector; it sends neither SUBWND UPDATE nor an extra cursor-close
  command.
- The amount phase uses a shared recovered edit primitive for place-width
  refresh, selector readiness and value edits. A changed digit position redraws
  only and updates the previous-position latch. A ready value change redraws and
  emits CURSOR_MOVE; unchanged/clamped values remain silent. Up wins simultaneous
  up/down. Each edit clamps to sender balance and recipient headroom below
  9,999,999. The controller fetches pad input only after its real selector is
  ready; selector readiness uses the original low byte, so 256 does not admit an
  amount edit.
- Transfer hides the input prompt before publishing both balances atomically;
  accepted giving preserves ISUSE.
- Acknowledgement hides the message, refreshes the owning STATUS stats (Title01,
  through the actual view callback, as the original SUBWND UPDATE does) and closes
  the cursor, then resets on the next update. The root BIT label therefore changes
  at acknowledgement.
- The seven-digit shutdown and final model/child completion keep their separate
  phases. The close/wait metadata transition is shared with its oracle.

Missing stat refresh ownership is rejected at controller construction. Popup text
belongs to its actual ShopSelect00 child. SendBit tracks the authored panel,
labels, balances and names, while the number renderer controls its seven digit
displays explicitly. The number renderer `4402e0` hides all seven digits before
displaying right-to-left characters with the selected minimum width. The three
recipients, signed field/byte admission, amount/headroom cap, zero/cancel path
and the atomic transfer primitive keep their recorded contracts
([player transactions](player-transactions.md)).

Validation:

- `make check-statusbit-outer-retail` executes 11,520 CtrlBit states across all
  sixteen joined masks/four owner slots, plus 9,936 SendBit states/effect traces
  and balance writes. Property, constructor, resource, number and selector leaves
  are controlled; the full outer branches execute original instructions.
- 2,688 amount/digit/input/cap/readiness edits execute original `41de40`, with
  2,688 amount/previous-position/redraw/sound traces. Selector queries, number
  rendering and sound are controlled leaves for that edit comparison.
- 216 original `41de40` state/latch/delay/active cases cover the close/wait
  metadata transition. Resource and child close/completion are controlled leaves
  there; the prepared owner supplies real model and selector waits.
- 352 number-renderer command traces match original instructions; ShopSelect34/52
  initializer comparisons cover their authored alignment and cursor setup.
- Authored native tests inspect the actual wrapper and SendBit child, exercise all
  three recipients, another player's input isolation, digit/place-value changes,
  cap/zero, the clamp to recipient headroom, transfer, the header BIT label before
  acknowledgement and the new sender balance afterward, zero/full amount cancel,
  recipient restart and external close. Standalone view checks explicitly
  initialize the parent Title01 header before opening currency.

This establishes currency ownership and timing, not retail full-frame parity.

## Shared model and text services

Positioned model commands: the recovered `3f5c90` helper queries ISRUN: an active
model receives its direct sequence; only an inactive model generates with the
supplied position. A NULL close key adds no model tracking.
`dw4_statusui_positioned` supplies that branch to STATUS's positioned resources
and DISK/detail/currency cursors; an unconditional GENERATE would replace an
active model's position. Twelve original helper command traces cover
inactive/active/256 results and two slots/positions. A real authored cursor test
checks inactive position publication and unchanged position when selecting
another sequence while active. This command check does not advance a model clock
or establish pixel parity.

Model REMOVE clears the retained fade state (`fade_present`): original Action2
`377990` releases Work and clears node default attributes on REMOVE. Keeping the
previous OUT opacity makes reopened Key/DISK panels invisible. Capture
regressions require the reopened `i_stfolder` slot to be drawable with positive
alpha.

Text: retail string conversion `382eb0` uses 424 custom Unicode/encoded-byte
pairs at retail table `4c8880`. The mapping is not standard CP932 or UTF-8:
marker `81ba` maps to `2286`, and `8a71` to `8d6b`. Native text uses that
424-pair decoder rather than copying TEXTSET bytes individually; all 816 original
code-output cases pass. See
[byte-to-Unicode boundary](dialogue-services.md#original-byte-to-unicode-boundary).

## Validation

`make check-statussubmenu-retail` executes the private retail ELF. The submenu
oracle compares 42,336 equipment/folder/skill scalar states and controlled service
traces, including model-query low-byte behavior, menu fallthrough, selection
retention, detail restart and close boundaries, plus the 32 page/restart states;
it checks the metadata class strings/globals first. Constructors, list allocation,
selector type/ready state, text/model services and skill-page projection are
controlled leaves. Skill page setup and navigation are not covered by that
retail comparison; it exercises refresh/exit states with those leaves bounded.
The scene oracle compares accepted GENERATE and manager entry/restoration traces
for eighty cap-boundary cases across all sixteen joined-player masks, and
executes original `3d8740` currency clamps. Inventory preparation and health
commands are controlled leaves; this establishes ordering, not rendered/HUD
behavior.

`make check-statussubmenu` runs 384 native owned-tree lifetimes, 128 four-player
restoration cycles and failed-sink holds. `make check-dialogue` additionally
checks accepted-GENERATE activation, repeated-GENERATE idempotence, activation
failure, retained DM completion and teardown of the pending tree.

The per-owner comparisons are listed with each owner above. The normal-boot and
SDL controller routes through these menus are in
[status/menu verification](status-menu.md#verification). The full native run is
`all check check-retail` with the virtual-pad ignore override
`SDL_GAMECONTROLLER_IGNORE_DEVICES=<vendor>/<product>`; optional live-input, display
and live-dump checks skip. Sanitizer runs of the headless view, equipment,
record/detail/FLAG and transaction tests use ASan/UBSan with `detect_leaks=0` and
`halt_on_error=1`; the focused submenu/scene tests also pass with leak detection
enabled.

## Rendered-menu comparison against retail

Native menu exports are enabled with `DW4_STATUS_CAPTURE_MENUS=1` and
`test_statusviews ROMS PNG EXISTING_DIR --root-only`. `frames.tsv` identifies each
actual player/view; `verify_status_render.py --frame N` selects that submission.
The exports cover the root, equipment selector, three equipment slots,
FOLDER selector and skill selector for all four players; a second `frames.tsv`
identifies the exported FOLDER pages.

Retail PNG/GS captures cover DEVICE list/actions, empty Key Folder, DISK
list/actions and no-disk refusal, no-recipient currency, the skill selector and
all three real fresh-player skill pages.

Text vertices, compared as retained vertices across multi-vsync dump candidates:

| View | Text vertices matched |
| --- | --- |
| Weapon slot | 1,752/1,752 |
| Armor slot | 1,170/1,170 |
| Sub slot | 1,170/1,170 |
| Key Folder | 1,200/1,200 |
| DISK list | 1,908/1,908 |
| DISK actions | 1,866/1,866 |
| DISK refusal | 1,776/1,776 |
| Skill page, species | 1,590/1,590 |
| Skill page, thresholds | 1,614/1,614 |
| Skill page, techniques | 1,344/1,344 |

Each of these pages also matches twelve vertices in the other font atlas. All
DEVICE list/action text, currency refusal text and skill-selector text vertices
match their retail candidates. The five compressed skill-page dumps validate and the
three page PNGs were visually inspected. These text checks do not establish
animated model timing or full-frame parity.

Phase comparison: the captures cover seventeen visually identified
menus, each with a twelve-frame GS dump request and paused EE node-clock reads
after six emulated vsyncs; the VM resumes to complete and validate the compressed
file. The clock reads supply 215 page-specific model/slot/time samples, and a
diagnostic native route exports the corresponding pages.
The sampler changes only pose evaluation, retaining native eligibility, alpha,
ownership and live clocks. Actor/scene/clock immutability and repeat-draw checks
pass, as does the legacy three-column clock fixture.

Original `1df040` quantizes both elapsed and key-duration differences to 2^18 ns
ticks before its unsigned conversions/division, and native scene evaluation uses
that fraction; all 876 original queries pass, and independent paused background
matrix reads converge closely. Without the quantization four background vertices
(armor slot one, FOLDER selector two, species skill one; 128,348/128,352 matched)
fail reciprocal Q with relative errors of 2.58–2.88e-5 against the
`1e-8 + 2e-5*abs(Q)` allowance while their position errors stay below 0.073 px;
the allowance is not widened.

The complete seventeen-page comparison matches 128,352/128,352 vertices
(geometry, UV, RGBA and reciprocal Q), including all 26,136 text vertices, with
unchanged position/UV/RGBA/Q allowances. Restricting each comparison to dump
vsync interval five also passes all seventeen; every other tested root interval
fails. The parser's interval/record/packet metadata and `--retail-vsync` prevent
combining different frames. PRIM.TME is checked independently of ABE. The phase
comparison is a multi-vsync candidate comparison and the single-interval gate
restricts it to one dump interval; neither is a live scheduling proof.

## Open items

- Scene lifecycle: pre-root REMOVE's world-disable release and full native
  generator/audio freezes are not implemented; the lifecycle functions cover
  STATUS mode zero only, not the shop/card modes.
- Recipient quantity alignment on the DISK giving panel has no contract audit.
- Pixel comparison is a separate gate from the vertex comparisons; it exposes a
  WN depth omission.
- Full-frame and reverse draw-set comparison, live phase, live joined-player
  ownership and physical input/audio devices are not validated. No emulator,
  Windows or physical Steam Deck parity is established for these menus.
- Native staging does not model reentrant observation of retail temporary lists.
