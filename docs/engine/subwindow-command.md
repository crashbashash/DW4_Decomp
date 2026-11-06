# SUBWND command receiver

The entire **3d60e0..3d873c / 9,820-byte** receiver is recovered.
The readable [guest-reference implementation](../../recovered/engine/subwindow-command.c)
passes **272 original-instruction RAM/return/ordered-call cases**. All **2,434
executable instruction addresses** run. Its21 internal alignment NOPs are excluded
from Ghidra's actual body ranges; a further zero word at3d873c separates the
function from [preparation](subwindow-preparation.md) at3d8740.

Together with the [lifecycle](subwindow-lifecycle.md) and preparation, this finishes
readable behavioral recovery of the11-body SUBWND manager region /17,616 code
bytes. All 11 bodies /17,616 bytes match (`src/game/beNDMWStatus.c`,
`src/unmatched/Gap__Bec__beNDMWStatus__vfunc_29.cpp`,
`src/unmatched/Gap__Bec__beNDMWStatus__vfunc_31.cpp`,
`src/unmatched/Gap__Bec__beNDMWStatus__vfunc_32.cpp`,
`src/unmatched/Gap__Bec__beNDMWStatus__vfunc_34.cpp` and
`src/unmatched/FUN_003d8740.cpp`). This checkpoint
adds no native menu functionality.

## Dispatch and command contract

The receiver obtains command enumeration3bb730, then resolves the message's word20
through38d4a0 using the current owner messenger20. The original name/value tables
at4ca090/4ca0b0 contain seven consecutive values0..6. The independent seven-entry
jump table516b30 maps those values to the following bodies. Unknown/full-width
out-of-range enum results return0; recognized commands return1 even when their
state condition performs no work.

| Value | Literal | Behavior |
| --- | --- | --- |
| 0 | GENERATE | Start only when RAM `_isRun` byte20 is zero; record owning player and service mode, clear state/counters and freeze the world |
| 1 | REMOVE | Only byte20 exactly1 requests root closure; without a root, release message hold and queue SUBWND REMOVE with argument1 |
| 2 | UPDATE | Ensure work, rebuild the parameter snapshot and publish player/status text |
| 3 | GETSHOPDATA | Return the requested WPU/APU/CHIP/JUNK list; JUNK also returns `_junkGift` |
| 4 | ONPREVIEW | Publish current stats colored against the saved parameter baseline |
| 5 | OFPREVIEW | Restore baseline text/default colors and write the saved HP/MP back to player records |
| 6 | ISRUN | Append the current run byte through38f150 |

`OFPREVIEW` is the shipped spelling. Generate reads integer argument0 for the
owning player, string argument0 for the service name and resolves mode enumeration
3b1d70. Its name/value tables4c9410/4c9440 bind STATUS,XDATA,LABO,BANK,CNOS,DISK,
WPU,APU,CHIP,JUNK,CARD to0..10. It writes active/state/counters first, then mode40
and player36, sends MODELCTRL and GENERATER ONFREEZE, enables the message hold
through38d470(1), then sends SOUND ONFREEZE. An already nonzero run byte leaves
these untouched. No extra mode-validity check is introduced after lookup.

Remove writes root state28=2 and clears40,36,32 in that order. With a null root
it sends the delayed/remove command through38ecf0; it does not directly clear the
run byte. Run values2..255 satisfy Generate's already-active condition but do not
satisfy Remove's exact1 condition.

GETSHOPDATA caches RAM work **before** fetching its argument; it never invokes
preparation. Mode6 returns work16,7 returns20,8 returns24 and9 returns28 followed
by the live word32. The gift word is fetched after the object-result callback.
Other requested modes produce no result but still return handled1.

## Status text and baseline capture

UPDATE similarly caches work before retrieving the selected player argument.
Only a null cached work invokes preparation and reloads RAM44. It resets the
current work `_parameter` list8 count, then asks GAMERAM GETPLAYER for the selected
slot. This differs from stock preparation's unconditional player-zero level.

PLAYERNAME is a reference object reached through the property/list/data graph.
It is placed in private frame word396, retained and appended to TEXTCTL's
STWINFONT02/font000. The temporary is reloaded **after** the text-prefix callbacks
and again for final release. Capturing its value before those callbacks changes
the original behavior. The adapter uses a400-byte private guest frame, preserving
all text buffers, reference cells and preview-vector addresses.

LEVEL is signed and capped above999 for display. The shinka database maps
DIGIMONNO / NAME to STWINFONT04/font001. Current HP/MP are displayed in
STWINFONT06/font000/font001. Eleven following stats are displayed, then appended
to the parameter snapshot in this order:

| Snapshot index | Property | STWINFONT06 font |
| --- | --- | --- |
| 0 | MHP | font010 |
| 1 | MMP | font011 |
| 2 | TSUYOSA | font040 |
| 3 | MAMORI | font041 |
| 4 | KASHIKOSA | font042 |
| 5 | SEISHIN | font043 |
| 6 | SUBAYASA | font044 |
| 7 | HONOOTEIKO | font045 |
| 8 | KOORITEIKO | font046 |
| 9 | KAMINARITEIKO | font047 |
| 10 | YAMITEIKO | font048 |

XDATA/font049 and BIT/font070 are displayed without adding snapshot entries.
NEXTEXP minus EXP wraps as a32-bit subtraction. At displayed level999, font071
shows `----`; otherwise a negative wrapped result displays `0`, or the signed
remaining number is formatted. It uses the original formatting service129e60
with literal `%d`. The independently captured HP and MP are appended at indices11
and12 after all text work. Each append reloads the work list; resize2d6790 can
relocate storage, so the backing pointer is loaded after that callback.

## Preview and restoration

ONPREVIEW obtains the selected player's live eleven stats and compares each
signed value with the corresponding saved baseline. It displays the live value,
then sends TEXTCTL COLOR using these exact RGB bit patterns:

| Comparison | Red | Green | Blue |
| --- | --- | --- | --- |
| Equal | 3f666666 | 3f666666 | 3f666666 |
| Lower | 3f70a3d7 | 3ecccccd | 3e800000 |
| Higher | 00000000 | 3f75c28f | 3f800000 |

No host floating-point arithmetic is needed to reproduce these constants. Their
private vector cells are384,368,...,224 in the400-byte frame. Values/colors are
captured before formatting callbacks; the baseline pointer is reloaded for each
stat. This receiver does not apply equipment or purchase anything.

OFPREVIEW displays the eleven saved baseline values with DEFAULTCOLOR, then
captures saved HP/MP from indices11/12, resolves the selected player and writes
those two properties. It does not restore the other eleven stat records here.
Both paths cache work before their first argument callback and keep reloading
the parameter list through that cached work.

## Evidence, matching and remaining work

```sh
python3 testing/test_subwindow_command_retail.py
python3 testing/test_subwindow_preparation_retail.py
python3 testing/test_subwindow_lifecycle_retail.py
python3 testing/test_lua_engine_dependencies.py
python3 tools/test_function_extents.py
make check
make link
make typed-check
```

The receiver cases cover all seven commands/defaults, all11 modes, all four
selected players, distinct run bytes, null/non-null roots, parameter capacities0
through13, signed level/experience/preview limits, reference boundaries and
callback-changed work/list/messenger/name/gift storage. Stateful sequences run
Generate → actual lifecycle/preparation → UPDATE → preview → restoration → data
results → removal → actual lifecycle finalization for every service mode.
Formatting, enum lookup, messages, records, list resizing and other concrete
controllers remain controlled services. Expected execution does not copy retail
output into the recovered result. Live/native UI, transactions and persistence
are not accepted by these tests.

The generated extent changes the previous dispatcher-grown9,824-byte split to
its actual9,820-byte return span. The final padding word becomes ordinary data:
**four fewer classified code bytes, zero matched-byte gain**, with retail image
contents unchanged. Existing RTTI/slot names are retained.

The 72-byte init at 3d5960 and the adjacent 92-byte scoped cleanup at 3d58f0 match
(`src/unmatched/Gap__Bec__beNDMWStatus__vfunc_29.cpp` and
`src/unmatched/Gap__Bec__beNDMWStatus__vfunc_32.cpp`). Continue
the concrete [hub service-controller and result dependencies](../systems/hub-recovery.md),
including price/stock services, transactions, bank/appraisal/lab/X Data and the
separate Save Keeper stagIS12 route.
