# Equipment, inventory and skill record transactions

`src/playertransactions.c` is the record mutation boundary of the
STATUS equipment/folder/skill menus. The fresh character initializer
materializes the three weapon identities and empty POWERPOCKET[5], MAINSLOT[1],
MAINPOCKET[5] and SUBSLOT[1] arrays from the retail template. These are native
record APIs; normal-boot STATUS and its submenu factories remain disabled.

## XDATA and recalculation transactions

`dw4_playertransactions_recalculate` publishes a private-copy recalculation (GAMERAM
`RECALCPLAYER`) atomically. `dw4_playertransactions_xdata_upgrade` is the ShopCtrl10 confirmation:
it re-reads the current stat, charges `dw4_xdata_price` with 32-bit wrap, increments the
stat's UPCNT slot, recalculates with equipment and copies MHP/MMP to HP/MP, publishing all
three together or none; undefined selectors are refused. See [XDATA shop](xdata-shop.md).

`dw4_playertransactions_cnos_convert` is the NPC appraiser's conversion (ShopCtrl40, see
[NPC appraiser](cnos-shop.md)): it validates the item kind (weapon, armor1 or armor2) and the 300 BIT
price, draws the replacement record from the `dw4_cnos_tier`/`dw4_cnos_roll` table rows and publishes
the debit, the record and the equipment re-projections together; below the price it is a normal refusal
(`*result == 0`) that changes nothing and invalid indices, kinds or tables fail.

`dw4_playertransactions_weapon_check` and `dw4_playertransactions_evolve` are the Digi-Lab's WEAPONEQUIPCHECK and
evolution commit (see [Digi-Lab](labo-shop.md)): the species is resolved from its `MODEL_NAME`, the current form is saved
to the base arrays, the target's saved form becomes current, the best eligible weapon is the only equipped one, the other
equipment lists are emptied and the record is recalculated twice, all published together; an empty inventory is allowed.

`dw4_playertransactions_disk_buy`, `disk_sell` and `sell_item` are the Digi-Disk shop's atomic buy and
shop purchases (`dw4_playertransactions_shop_buy`: `BIT` debited and the item appended to `DEVICEFOLDER`, at most 36),
the junk donation (`junk_donate`: `BIT` and the common `COUNTER[1]` together), the equip-candidate preview and the
retail price rule (`dw4_playerstats_item_price`), see [equipment shops](equipment-shops.md); sell commits (ShopCtrl50/Sell, see [Digi-Disk shop](disk-shop.md)): quantity 1..9, at most nine held, `BIT`
debited or credited (credits cap at 9,999,999) and the DISKFOLDER or DEVICEFOLDER record (with equipment
references re-projected) published together; insufficient `BIT`, more than held, or an equipped item
is a normal refusal and invalid indices fail.

`dw4_playertransactions_bank_item` and `dw4_playertransactions_bank_bit` are the NPC bank
transfers (ShopCtrl30, see [NPC bank](bank-shop.md)). A deposit moves an unequipped, unreferenced
`DEVICEFOLDER[index]` to the end of `BANKDEVICE` (96 records) and re-projects the equipment
references; a withdrawal moves `BANKDEVICE[index]` to the end of `DEVICEFOLDER` (36 records). A full
destination or an equipped/referenced deposit is a normal refusal (`*result == 0`) that changes
nothing; invalid indices, flags and records fail. The money variant moves an amount between `BIT` and
`BANKBIT`, both bounded to 0..9,999,999, atomically.

## Identity and publication

DEVICEFOLDER owns item values. Each equipment list has a parallel host-only
integer `<key>REF` array referring to DEVICEFOLDER indices; -1 means a null
socket. These arrays model retail shared object identity without storing host
pointers in guest fields. Identical kind/record/revision/pocket values can still
be separate items. Null equipment projections use kind -1; that sentinel and
REF arrays are native metadata, not additional PS2 save fields.

Inventory compaction adjusts every equipment reference above the removed index.
Equipped items cannot be removed by CTRLITEM CLR. Fresh starter refs are 0,1,2.
Existing item-value accessors continue to return copied projections, while the
reference arrays are authoritative for identity. Save/import translation must
reconstruct these references from actual serialized indices, rather than
comparing item values.

Equipment operations copy all non-folder player values into a private owner.
They mutate private item flags/references/projections, then invoke a **required**
recalculation callback. The callback must supply the complete affected stats,
technique and socket-name projection; missing/failed callbacks publish nothing.
The callback must not mutate the live session or retain private buffers.
The production [stat/technique owner](player-stats.md) supplies this callback
and database item attributes; `equip_database` connects accepted selections.
Accepted controller selections are the input contract: eligibility and menu
selection gates precede this API. Cross-list ownership and bounds are checked.

`dw4_property_commit_values` checks every property type and allocates the complete
expanded record table before swapping any payload. Rejected commits leave all
existing payloads untouched. Successful commits expire old borrowed value buffers;
child folders retain their addresses and contents. Copying/committing values
excludes nested-folder transactions. `preview` exposes the candidate to the same
callback and releases it without publishing any player values. Native preview
is private; retail temporarily changes shared lists and restores them after the
synchronous stat/preview commands. Reentrant observation during retail temporary
mutation is not claimed equivalent.

## Recovered rules ([#796](../../docs/findings/findings-0751-1000.md#f796))

- Equipment helper `0x00411950` toggles an identical item identity off, clears the
  previous equipped flag, removes duplicate references to the candidate within
  that equipment list and installs it with equipped byte one. Empty candidate
  clears the slot. Duplicate item values do not imply duplicate identity.
- Chips use the first positive attribute in this order: TSUYOSA, KASHIKOSA,
  SEISHIN, SUBAYASA, RES_FIRE, RES_ICE, RES_THUNDER, RES_DARK, CHIMEIRITSU,
  HPDRAIN, MPDRAIN, CHOHATURITSU. Other positive entries in that family are
  cleared. This checks the recovered attribute callback, not a guessed chip ID
  family. Malformed chips with no family fail before mutation; retail otherwise
  accesses a negative index.
- `0x004144a0` checks SOUBI with the EE species shift masked to five bits and
  compares the selected signed SKILL value with signed SKILLPOINT. Invalid host
  skill indices fail eligibility instead of reading outside the nine-value array.
- GAMERAM `0x003fca10` CTRLITEM DEVICE handles SET, CLR, IS, ISMAX and ISEQUIP.
  Capacity is 36. CLR removes the first matching unequipped kind/record; IS
  includes equipped matches; ISEQUIP uses the low equipped byte. SET initializes
  kind 0/1 with revision and pocket, kind 2 with revision only, kind 3 with neither.
  Successful additions start unequipped. Queries and unsuccessful mutations do
  not replace borrowed payloads. Native rejects malformed inventories above 36.
- CURRENT2BASE `0x003f8760` copies LEVEL, EXP, SKILL[9] and UPCNT[11] into the
  active species' BASE_LEVEL[16], BASE_EXP[16], BASE_SKILL[144] and
  BASE_UPCNT[176] slices. Signed bit patterns survive; other species remain intact.
  Native publishes these arrays together. This is an in-memory persistence step,
  not a save write. BASE2CURRENT, including its common flag alias, is implemented (the evolution commit above uses it).

## Validation

`make check-playertransactions-retail` executes the private retail ELF for
800 equipment assignments (including duplicate values, null slots, toggles and
chip-family conflicts), 500 signed eligibility cases, 360 CTRLITEM inventory
states and all 64 player/species persistence combinations. Comparisons cover
item flags, identities/list order, result values, initializer fields and complete
base arrays. Allocation, property/list lookup, item attribute lookup and message
sinks are controlled leaves. This does not establish general derived stat math,
menu command ordering, preview text, save interoperability or full scene behavior.
Read-only Ghidra exports reuse the analyzed project with no analysis; objdump
checks instruction shape. Private exports remain under `../scratch/`.

`make check-playertransactions` covers all four player slots across 128 owner
lifetimes, failed recalculation after partial staged writes, successful preview
without publication, duplicate identity handling, compaction, cross-list ownership,
chip lookup failure, full-inventory holds, signed persistence and atomic type
conflicts. Existing child folder addresses survive publication. Fresh character
checks verify the empty equipment arrays alongside the retail stats.

`SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a
make -C port all check check-retail -j8` passes, including scripted created-card
boot and SDL/Vulkan presentation equality. Optional live-input/capture checks
retain their documented skips. The focused transaction/initializer checks pass.
The transaction ownership test passes ASan/UBSan with leak detection enabled and
halt-on-error.

## Connected owners and open items

The production general recalculation/technique owner and item attributes
exist ([#797](../../docs/findings/findings-0751-1000.md#f797)); fresh creation and accepted equipment commits share them.
[Production recalculation](player-stats.md) compares 1,760 cases,
54,560 scalar results, 9,158 technique records and socket-name lists.
Shared equipment-base selection/action routing and accepted transaction IO
exist in statusequip.c/statusequiprecords.c; see [submenu contracts](status-submenus.md).
PowerSocket/MainSlot/SubSlot description/pocket leaves exist, and the
[owned DEVICE selector](status-submenus.md#owned-device-selector-and-inventory-preview-gate)
supplies scrolling identities and preview admission. Concrete equipment
views run real action/pocket/slot and error/retry controllers. The original
skill controller primarily presents technique data;
CURRENT2BASE must not be mistaken for a menu action that purchases skill levels.

Open items: live factory integration; flag inventories; CTRLITEM GET/result
objects and Lua typed returns; and the concrete folder/skill view owners.

Enable the normal STATUS factory only after original submenu selection/close
traces, model/audio/world gating and player HP/MP publication/restoration pass.
The arrival adapter remains in place. No playable-menu, visual, Windows,
physical-controller or Steam Deck parity is claimed.


## Detail actions and atomic giving

`inventorydetail.c` supplies exact-index removal for the DEVICE detail menu.
Unlike CTRLITEM CLR's first matching value, this removes the accepted identity;
equipped/referenced items refuse publication. Compaction remaps every equipment
reference. Giving copies both player folders and preflights both commits before
either payload changes; full recipients and malformed destinations leave both
players unchanged. Recipient capacity is 36 and joined status uses ISUSE's low
byte. Item policy booleans and confirmation remain controller responsibilities.

Arrange prepends the retail equipment order (first Power, its pockets, remaining
Power sockets, Main, its pockets, Sub), then sorts the remaining kinds. Retail
`422c00` uses stable descending signed revision and moves unknown records
276/31/44 to the tail by reverse traversal. Chips `423000` use stable ascending
signed record. Identity order and equipment references survive publication.

`check-inventorydetail` covers 128 owner lifetimes with equal-valued distinct
items, guards, full-recipient holds, remapping and two-destination preflight
rollback. `check-inventorydetail-retail` compares 448 signed/tied/special-record
sort permutations against original instructions with allocation/list leaves
controlled. The full detail controller's frame/state trace oracle remains to
be added; prepared menu checks do not establish live-scene parity.


## Currency and disk transfers

`give_bit` and `give_disk` preflight the joined sender/recipient, available amount
and recipient cap before publishing both folders with the same two-destination
commit. BIT caps at 9,999,999; disks cap at nine and transfer into the first
matching record, preserving recipient order. Disk swaps exchange actual records
among the first ten positions and leave the final two untouched. Native record
validation requires the complete twelve-disk list and valid quantity words.

Sparse staging owners start with an ISUSE record, so these transactions explicitly
retain each player's original ISUSE value; a transfer that does not would clear
that field. Regression checks, including prepared repeat transfers, preserve
joined flags across both currency and disk publication. The
128-lifetime primitive checks include caps, zero/negative/self refusal,
donor reorder versus recipient record identity and joined-flag retention.
