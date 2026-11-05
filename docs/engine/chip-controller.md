# XDATA chip transaction controller

The complete 7,232-byte update at `43aae0..43c720` is recovered as
[guest-address C](../../recovered/engine/chip-controller.c). Its adjacent
[count/text and inherited paging helpers](list-controller-chip-view.md) were
recovered separately and now have exact matching source for all2,196 bytes.
The update itself still uses retail assembly: its behavioral recovery adds
**zero exact code bytes**. A corrected private full-body probe compiles but still
has a different frame/register layout and does not match; it was not banked.

The suite passes **1,076 RAM/ordered-call comparisons**, executing all1,761
reachable non-padding controller words out of1,808. Fifteen padding words and
32 words in sixteen statically dead literal-null branches are checked separately.
Run `python3 testing/test_chip_controller_retail.py`. The oracle executes original
EE instructions against synthetic memory, comparing persistent RAM and ordered
service calls with argument/state snapshots. It covers controller states,
allocator variants, reference cleanup, selection/paging, both errors, previews,
confirmation/decline, four players, fresh commit prices/balances, wrapped record
writes, and callback timing. Selected cases run actual page-count and parent
binding bodies beneath the controller. Item factories/getters, recalculation,
messages, strings/lists, selectors, rendering and script execution remain
controlled services. This is neither native-port acceptance nor a live-game test.

## Retained data and selection

The inherited Window state is primary28, phase32, subphase36 and counter/error40.
Child result48 is live; list52 owns children and count80 captures its length.
ListCtrl page84/cursor92 select `page * 12 + cursor` with word wrapping. Its
maximum page count is88 and the controller's own retained item list is96.

Every entry into phase0 resolves the selected player's DEVICEFOLDER, releases
and clears the old retained item list, and appends non-null inventory entries
whose reflected `_kindNo` at8 equals3. The old list/count are captured during
release; data pointers are reloaded. The inventory count and destination list
remain live during scanning. An empty result selects error `491` in phase10.
Subphase1 still rebuilds the inventory; it suppresses only the initial model,
script `txt_shop` entry `456`, and arrow setup. The list selector receives the
captured row count, position `(-121,128,0)` and current cursor.

Phase1 refreshes text then falls into phase2 in the same call. During phase2,
changed highlights refresh the description. A stable highlight permits previous
then next page requests only when the first child passes its type/readiness
checks. A successful page request restarts that child at primary4 and refreshes
its row count. Child-count change with result-1 closes the controller; another
result becomes cursor92 and advances to quote eligibility.

## Quote, preview and confirmation

Phase3 captures XDATA, then page/cursor before the status lookup, and dereferences
the current item list after that callback. `NEXTX` return-1 selects error `492`;
insufficient funds selects `489`. Both the sentinel and affordability comparison
use the **full64 return**, against the sign-extended32 wallet. Errors in phase11
return to phase0/subphase1 after their dialog completes.

Phase4/subphase0 constructs a notice. For an equipped item it temporarily adds1
to `_recNo` at12, sends GAMERAM RECALCPLAYER and PLAYER ONPREVIEW, restores the
captured original record, and recalculates again. This field is the catalogue
record number, not a separately inferred level or upgrade counter.

A temporary ability-chip object receives `recNo+1`. Its name uses the first
status context. A second status lookup supplies the twelve stat queries:
TSUYOSA, KASHIKOSA, SEISHIN, SUBAYASA, four resistances, CHIMEIRITSU, HPDRAIN,
MPDRAIN and CHOHATURITSU. The first positive signed64 result is displayed;
indices8..11 use dialog entry7 from the eight-entry table. Formatting consumes
its low32 signed value. The otherwise unused temporary integer list is still
allocated and released. Remaining-XDATA text uses the original selected item
and first context, with word subtraction. Quoting does not spend currency.

After the notice child count changes, subphase1 creates confirmation `493`.
Subphase2 waits for its completion and **always** sends PLAYER OFPREVIEW before
reading the live result. Result0 performs a fresh status/item lookup, resolves
the selected player again and fetches current XDATA/NEXTX. It re-fetches the
wallet property before writing the wrapped balance-minus-cost, increments the
item's current record, sends RECALCPLAYER and PLAYER UPDATE, then restarts
selection. A decline also restarts selection. The eligibility check is not
repeated at commit; no extra clamp or rejection has been introduced.

## Lifecycle and remaining work

Primary0 publishes the text/close queues and falls through to selection;
primary2 closes models, text and children; primary3 clears active byte24 only
after the full-width close-poll result is nonzero. Empty-list phase10 installs
its special dialog text and advances to closure on completion. Error entry40 is
read after allocation, and private reference cells are reloaded around callbacks.

Exact matching of this update, its real item/pricing/status/recalculation
services, selector/message/script composition, and retail/native behavior remain
open. Other lobby services and their script outcomes retain the scope in the
[hub inventory](../systems/hub-recovery.md).

The [item/database block](item-database.md) now has complete exact source and
explicit status/value-return contracts ([#924](../findings/findings-0751-1000.md#f924)). Its standalone composed oracle
validates the lookup chain; this controller's existing oracle still treats
lookups as services. Live database delivery, recalculation and full transaction
composition remain open.
