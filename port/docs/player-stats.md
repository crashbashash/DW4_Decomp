# Player stat and technique recalculation

`src/playerstats.c` implements GAMERAM `0x003fab90` with equipment enabled,
using the copied `shinka`, `pcTech`, `weapon`, `armor1`, `armor2` and `abChip`
databases. Fresh character creation and accepted equipment transactions
share this production calculator. It changes private record staging; it does
not publish actor health, meters, models or scene state. Normal-boot STATUS
remains disabled until concrete submenu and restoration integration is verified.

## Ownership and inputs

The `GAMERAM RECALCPLAYER` bool is optional and defaults to true: case 11 of
`beNDMWGameRam::vfunc_34` (`0x3fcb80`) passes `beMessenger_GetInt(0)` as the player and
`beMessenger_GetBoolCount > 0 ? beMessenger_GetBool(0) : TRUE` as `FUN_003fab90`'s third argument. That
argument gates thirteen blocks: the eleven per-stat equipment-bonus sites and two tail sections. Every
other caller passes true.

`dw4_playerstats_recalculate_base` is retail `3fab90` with its third argument clear
(`GAMERAM RECALCPLAYER` with an explicit false): no equipment bonus is applied and the
delay/accuracy/element/extras and weapon/model sections are skipped, leaving the stats,
HP/MP, `WAZALIST` and `NEXTEXP`. It matches retail on 440 authored cases; the XDATA shop uses it
to price stats (see [XDATA shop](xdata-shop.md)).

`dw4_playerstats_recalculate` is the transaction callback, with a borrowed
`dw4_databases` receiver. It requires species 0..15, level 1..999, current HP/MP,
UPCNT[11], UPDATA[11], DOWNDATA[7], SKILL[9] and the five equipment projections.
Malformed sizes/kinds, invalid technique skill selectors and unavailable database
owners fail. Call only on private staging: failure may leave partial staged
writes. The transaction owner discards that staging on error and publishes all
values together on success. `dw4_playertransactions_equip_database` supplies
production attributes and recalculation to the existing accepted-selection API.
Eligibility/controller gates still precede that API.

Numeric item lookup follows retail `0x00447c10` through each concrete item's
virtual getter: kind 0 -> weapon, 1 -> armor1, 2 -> armor2, 3 -> abChip.
Missing numeric columns yield zero; invalid native rows fail. String lookup uses
`0x00447cb0`. Only the first weapon, first main slot and first subslot contribute
single-item bonuses; all non-null entries in each chip list contribute.

WAZALIST is a copied native ITEMS property: kind 9, record = selected pcTech row,
revision = technique base row, equipped = pocket = 0. The revision member carries
the retail technique object's +20 base-row field, not an equipment bonus or a
technique level. There are at most six entries, in TECH1..TECH6 order. Empty lists
are valid. These records do not yet supply Lua typed-object results or save I/O.
POWERSOCKETNAME contains only non-null weapon models, in socket order, matching
retail's compact string list rather than inserting empty placeholders.

## Recovered arithmetic

Growth helpers `0x003fa3b0` and `0x003fa850` use the first level ceiling at least
the current level. Growth is `initial + UPCNT + grow * factor / 100`, with signed
32-bit wrapping at each add/multiply and signed division toward zero. The tables
at `0x004cf130..0x004cf220` define `factor = offset + rate * (level - origin)`:

| Ceiling | Origin | HP/MP offset | HP/MP rate | Main-stat offset | Main-stat rate |
| --- | --- | --- | --- | --- | --- |
| 5 | 1 | 0 | 10 | 0 | 10 |
| 10 | 5 | 40 | 20 | 40 | 9 |
| 20 | 10 | 140 | 50 | 85 | 8 |
| 30 | 20 | 640 | 80 | 165 | 7 |
| 50 | 30 | 1440 | 120 | 235 | 6 |
| 70 | 50 | 3840 | 180 | 355 | 5 |
| 110 | 70 | 7440 | 260 | 455 | 4 |
| 150 | 110 | 17840 | 180 | 615 | 3 |
| 230 | 150 | 25040 | 120 | 735 | 2 |
| 999 | 230 | 34640 | 80 | 895 | 1 |

The base growth helpers cap HP/MP at 99999 and the five main stats at 9999
before equipment additions. The final pass caps HP/MP above at 99999 without a
lower clamp; main stats and four resistances clamp to 1..9999. UPDATA/DOWNDATA
have field-specific consumers rather than uniformly modifying every stat.
Weapon revision adds to strength, main-slot revision to defense. Subslot revision
adds only for the matching SHUSEINOURYOKU field in calls that enable it. Spirit
explicitly disables that subslot revision addition.

HP is set to MHP when old HP is zero or above the new maximum. MP is set to MMP
when **old HP is zero**, or old MP is above its maximum. This preserves the retail
cross-field condition, including MP zero with nonzero HP remaining zero.
NEXTEXP is zero at level 999; otherwise the wrapped word expression is
`level * 200 + (level + 140) * level * level`; retail gives 341 at level 1 and
968 at level 2. Attack delay caps above at 70.
Critical/evasion/stun-resistance minima are one. Evasion and CHOHATURITSU share
the same computed value. Attack element is the first recognized power-pocket
ZOKUSEI (`fire`, `ice`, `thunder`, `dark`), otherwise -1.

For each TECHn base row, pcTech SKILL selects the current skill counter.
TECHn_LEVEL gates availability. The routine checks TECHn_SKILL5 down through
TECHn_SKILL1 and selects the first satisfied threshold, creating row `base+tier`
where tier is 4..0. All comparisons are signed. No entry is created if no
threshold passes. This derives available techniques; it does not purchase or
increment skill levels.

## Verification and open items

`make -C port check-playerstats check-playerstats-retail` covers all sixteen
species at level ceilings and the next level, plus every technique tier threshold
minus one, equal and plus one. The 1,760 fixtures compare 54,560 scalar results,
9,158 complete technique records and socket-name lists against retail instructions.
Equipment includes null slots, all four item kinds, negative revisions and signed
extreme UP/DOWN/UPCNT inputs. The oracle executes growth helpers, equipment bonus
helpers, attribute wrappers and concrete virtual database selectors. Database
manager dispatch, DB cells, generic property/list operations and allocation are
controlled leaves. These fixtures are record comparisons, not running-game claims.

Native checks also exercise production equipment commit, preview isolation and
failed database dependency rollback. Fresh initialization retains its sixteen
retail paths and 624 scalar comparisons. ASan/UBSan with leak detection and
halt-on-error passes all 1,760 native fixtures and the transaction integration
checks. The full `SDL_GAMECONTROLLER_IGNORE_DEVICES=<vendor>/<product>
make -C port all check check-retail -j8` and focused transaction/creation/stat
checks pass. SDL/Vulkan presentation is 100% identical; optional live-input/
capture checks retain their documented skips.

Open items: concrete PowerSocket/MainSlot/SubSlot, folder and skill view owners;
remaining disk/flag/bank records and BASE2CURRENT/common aliases; Lua typed-object
returns; scene/audio/player restoration. Keep normal STATUS disabled until
original submenu input/close traces and restoration contracts pass.
