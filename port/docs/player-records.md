# Session player records

`src/playerrecords.c` owns one common property folder and four independent player
folders for the lifetime of a native session. Scene teardown and Lua VM recreation
do not destroy them. Named scalar integers, strings, integer arrays, string arrays,
Unicode object arrays and nested folders copy their inputs; record replacement
preserves the original host type. Nested folder addresses remain stable when their
parent's record table grows. Borrowed strings/arrays survive until that record is
replaced or the session is destroyed. Host references stay outside recovered
four-byte fields.

Retargeted game code can borrow `dw4_property_reference(folder, key, type)`,
which performs the same name/alias/type lookup and returns an arena plus a
four-byte record handle. It returns an empty reference on failure. Resolve the
authoritative `beDataObj*` fields through arena accessors, and reacquire after
mutation, publication or recalculation; the reference does not retain ownership
or allow concurrent mutation. Its consumers are the [fight status and
calculation record readers](combat.md#fight-records).

## Recovered access boundary

GAMERAM `0x003fca10` selects GETCOMMON and GETPLAYER/GETPLAYER1–4 at
`0x003fca88..0x003fcb78`. GETPLAYER takes a zero-based integer; fixed suffixes
select slots zero through three. `dw4_playerrecords_get` exposes this to native
owners. Invalid indices fail. The GAMERAM receiver supplies typed folder results to
native receiver queries. The Lua bridge can carry those results as opaque tagged
userdata through host arguments/globals/native returns, retaining identity and
ownership. Retail Lua `sd` commands discard receiver results; no extra Lua
query API is introduced. No host pointer is encoded as a number.

Native folder identities remain stable across property publication.
`dw4_script_objects_invalidate(vm,players)` rejects old Lua references before
session record storage is destroyed; scene/VM recreation clears only the VM's
identity cache. The live session registers GAMERAM in its global service scope
and restores that registration after scene reset.

The session binding implements the actual SYS field selections:

| Method | Retail entry | Record | Result |
| --- | --- | --- | --- |
| SYSisJoinPlayer | `0x00371c70` | ISUSE | Low byte |
| SYSgetPlayerName | `0x00371ca0` | DIGIMONNAME | Asset-name string |
| SYSgetPlayerLevel | `0x00372590` | LEVEL | Signed integer |
| SYSgetPlayerDigimon | `0x003725c0` | DIGIMONNO | Signed integer |
| SYSgetWeaponName | `0x00371cd0` | POWERSOCKETNAME | Indexed string or nil |

The wrappers call GetStruct(player+1), then the appropriate typed property lookup.
Weapon indices beyond the array or null sockets return nil. Native malformed,
fractional and out-of-range player/socket arguments fail explicitly. Missing
records also fail; they do not supply invented character levels or stats.

Each slot starts with ISUSE zero. The created-card loader uses the fresh
name/stat initializer below before preparing lobby scripts. Rejected inputs or
missing dependencies leave the previous slot untouched. Failed lobby preparation
clears ISUSE and recomputes common NINZU. Scene reset retains the copied records.

## Fresh character name and stats

`src/playerinit.c` implements the four original starters through
`dw4_playerrecords_create(players,databases,slot,model,name,...)`. Its `p_*` model
name selects the authored shinka MODEL_NAME row; UI order is Dorumon, Agumon,
Veemon, Guilmon, whereas database indices are 3, 0, 1, 2. DIGIMONNAME holds that
`p_*` player-controller name, not the `m_*` model filename.

The owner constructs a private replacement slot, then publishes it atomically
and recomputes NINZU from the four ISUSE values. The slot folder's host address
stays stable; its old borrowed payloads expire on successful replacement. Chosen
names, base/current arrays, socket names and item values are copied and survive
database/scene teardown. Invalid player/model/name/dependencies publish nothing.

Fresh BASE_LEVEL[16] and BASE_SKILL[144] are one; BASE_EXP[16],
BASE_UPCNT[176], UPCNT[11], UPDATA[11] and DOWNDATA[7] are zero. LEVEL is one,
EXP/BIT/XDATA/UNIQUE/BANKBIT are zero, SKILL[9] is one, and only the selected
BASE_ISUSE entry is one. Native BASE_ISUSE uses integer-array storage for these
logical byte values; this is not a serialized retail byte array.

All three authored INI_WEAPON1–3 records populate copied DEVICEFOLDER and
POWERSOCKET item arrays and POWERSOCKETNAME strings. Each has kind 0, equipped 1,
pocket/revision 0. Only socket zero contributes to the initial stat calculation.
At fresh level one the recovered growth tables have origin one and zero offset,
so HP/MP and five attributes use their shinka *_INI values. The first weapon adds
strength, wisdom, spirit and speed; defense and four resistances retain their
species values. Retail caps, minimums and secondary scalar fields are preserved.
HP/MP fill MHP/MMP, NEXTEXP is 341, weapon DELAY supplies ATTACKDELAY (cap 70),
WEAPONRECNO/SKILLNO identify socket zero, and ATTACKZOKUSEI is -1.

Equipment arrays and host identity refs accompany the fresh starter records; see
[transaction ownership and remaining boundaries](player-transactions.md). The
staged equipment/inventory and CURRENT2BASE primitives are there too.
[General recalculation and WAZALIST](player-stats.md) share the production
creation/equipment path.

PLAYERNAME holds one present eight-code Unicode object. The US converter's
ASCII table filters unsupported punctuation before copy/padding. The native
keyboard includes `* / = ; [ ]`, which the converter drops; all other keyboard
codes remain ASCII. For example `&!?+-*/=` becomes five codes followed by three
zeroes. This matches the original converter and does not change the keyboard
presentation. The narrow input accepts 1–8 printable ASCII characters.

## Common aliases and remaining fresh records

The native common owner materializes the thirteen entries in template `4ced40`,
including 1,024 FLAG bytes, twelve FLAGFOLDER bytes, sixteen COUNTER integers,
four nullable BKCHIPSTAGE/BKCHIPNAME strings, twelve BKCHIPPOS floats and eight
BKCHIPDATA integers. Nullable strings retain a present property distinct from a
missing key. Byte and float payloads copy without numeric conversion.

Player creation materializes BASE_FLAG[1024] (byte 960 starts at one),
BASE_FLAGFOLDER[12], BASE_COUNTER[16], CARDLIST[50], an empty BANKDEVICE and twelve
DISKFOLDER records. The disk initializer `448710` writes kind four, record index,
equipped zero and quantity zero; the native item record's revision field stores
that quantity word. These are in-memory records, not an implemented save schema.

Retail BASE2CURRENT `3f82a0` aliases common FLAG/FLAGFOLDER/COUNTER to player zero's
BASE_* records. Native publication binds those aliases by stable folder and key,
so replacing a private payload cannot leave an old buffer referenced. Reads,
setters, describe/copy and commits resolve that alias; creating another player
never retargets it. Finding [#804](../../docs/findings/findings-0751-1000.md#f804) records these records and aliases.

## Template evidence and record types

Retail initializer `0x003f7310` passes template **`0x004cedf0`** to `0x003f6620`.
Each 12-byte entry is `{type,count,name}`, with its name at +8. The first entry's
name pointer is therefore at `0x004cedf8`; that address is not the template base.
Finding [#297](../../docs/findings/findings-0251-0500.md#f297), which places the template at `0x4cedf8`, is refuted; finding [#795](../../docs/findings/findings-0751-1000.md#f795)
records the initializer evidence.

The constructor dispatch at `0x00518b90` distinguishes scalar integer (0), integer
array (1), scalar byte (2), byte array (3), string (4), string array (5), object
array (6) and float array (7). LEVEL is a scalar initialized by a zeroing
constructor, not a default level-one template entry. The initialization routine
separately fills BASE_LEVEL and BASE_SKILL with ones. PLAYERNAME is an object
array (type 6); it must not be replaced by a native narrow string. DIGIMONNAME
is type 4 and POWERSOCKETNAME type 5.

Native PLAYERNAME owns an array of Unicode objects with copied 16-bit font
codes. A null entry differs from a present empty object. Replacement preserves
its type and borrowed buffers last until replacement/session destruction. This
is the type-6 Unicode payload needed by [STATUS UPDATE](status-views.md); it
does not supply arbitrary engine-object references or Lua object returns.

Prepared shinka string data and its native typed GETDATABASE result are owned
separately; see [databases](databases.md).

The fresh name/stat path does not materialize the entire retail template or
save schema. Beyond the starter records it carries the common flag aliases,
byte/float arrays, CARDLIST, the twelve DISKFOLDER objects and the empty
BANKDEVICE described above.

## Live health restoration boundary

`playerhealth.c` implements the ADDHP-zero/ADDMP-zero contract used when STATUS
closes (the order of that restoration is in the
[STATUS scene lifecycle](status-submenus.md#status-scene-lifecycle)). HP zero skips
ADDHP publication; other HP and all MP values clamp to zero/the recorded maximum.
Percentage words use EE binary32 multiply/divide. Invalid/missing maxima and level
fail before record mutation. Existing scalar slots make accepted HP/MP publication
nonallocating; this does not recalculate stats or advance gameplay.

The normal loading path publishes the created player's actual health/level into
its lobby HUD owner. The STATUS factory's health/HUD restoration is described in
[live factory wiring](status-menu.md#live-factory-wiring). Finding [#810](../../docs/findings/findings-0751-1000.md#f810) records
these boundaries.

## Private stage-transition snapshots

`dw4_playerrecords_snapshot` copies all raw property kinds and nested/empty
folders into independent owners, then reconnects the common aliases to the copied
player-zero folders. It preserves absent versus present-empty Unicode, exact float
bits and all four player payloads; Lua identity views are rebuilt lazily. The
source and copy share no owned property buffers. This differs from the
value-copy helper, which deliberately skips folder properties and follows aliases.
The isolated [hub runtime](hub-travel.md) uses this snapshot before destination
preparation; it does not establish a persistent save format or live co-op
ownership.

## Retained payload references

`dw4_property_list_acquire` / `folder_acquire` retain actual typed payloads;
`list_release` recursively releases the final holder. Replacing a property,
publishing a folder or closing its owner cannot invalidate such a lease.
Ordinary borrowed reads keep their lifetime and mutation contract.
Item-list creation/view/slot-replacement APIs also serve stock without inventing
save fields or private stock arrays.

## Verification

- `make check-statusctrl` verifies four independent slots, copied payloads, type
  preservation, stable nested ownership, empty/out-of-range sockets and malformed
  arguments. A separate native integration test runs 128 actual Lua/SD scene
  resets, proving that record-backed SYS queries persist while VM globals clear.
- `make check-statusctrl-retail` compares 112 SYS query results against
  retail instructions, including signed extrema and low-byte truncation. Folder and
  list lookup/allocation are controlled leaves; the check validates wrappers and
  field selections, not the full retail property implementation or save format.
- `make check-playerinit` compares 22,425 authored signed numeric cells directly
  with their raw IGB lists, exercises all four starters in all four slots, and
  checks copy ownership, stable slot addresses, rejected-input atomicity and join
  count rollback.
- Native checks cover common alias replacement, copied effective values, nullable
  strings and float signed-zero bit preservation.
- `make check-playerinit-retail` executes sixteen original retail creation paths
  and compares 624 scalar results, base arrays, name codes and three starter
  sockets, plus all the byte arrays and twelve disk objects of the common/fresh
  records across the sixteen starter/slot paths. The actual US converter executes
  for every keyboard key; the oracle retains LQ/SQ's upper 64-bit lane when
  copying its conversion table. Generic property/template allocation, lists, DB
  lookups and unused scratch byte buffers are controlled leaves. Original stat
  code also constructs technique objects; those side effects are not claimed by
  the native numeric projection.
- `make check-statusviews` projects all four production starter records into
  Title01's authored font rows through the real shinka owner. Its later comparison
  preview cases use controlled mutated records.
- 324 original `3f9c80/3f9e20` cases compare signed clamp inputs, dead HP, result
  flags and exact percentage words for the health contract. Property and
  meter/number dispatch are controlled leaves. Native ownership checks cover
  rejected-maxima atomicity.
- `make -C port check-session-snapshot` verifies every property kind, alias
  rebinding, mutation/destruction isolation and empty/null payload boundaries.
- The retained-reference tests retain arrays/strings/items/folders through
  replacement and owner teardown, retain an item after slot replacement, and
  check the arena block baseline for 128 lifetimes.
- The full native run
  `SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a make -C port all check check-retail -j8`
  includes the scripted created-card boot-to-lobby flow.
- Sanitizer runs (ASan/UBSan, halt on error) cover the ownership/tree test and
  the database, initializer and STATUS integration tests with leak detection
  enabled, and the headless player and controller tests with `detect_leaks=0`.

## Open items

- The remainder of BASE2CURRENT is not integrated; only the common
  FLAG/FLAGFOLDER/COUNTER aliases are.
- General object arrays, progression and save loading are missing; the records
  are in memory only and no save schema is implemented.
- Meter/number controller retargeting is missing; `playerhealth.c` is not the
  complete health/HUD engine.
- Multibyte naming and full retail keyboard acceptance are frontend work that
  is not done.
- Windows and physical Steam Deck validation have not been run.
