# The enemy spawn system (GENERATER / GENE-xx)

**Status:** pipeline mapped and live-confirmed, the **per-frame state
machine, fill modes and timer units are decoded from the code**,
and **the spawned enemy is swappable both live and from disc**:
the row knob, the init latch and the geometry-residency limit are confirmed
(§6b/§6c). Triggers, positions,
counts and enemy selection are all identified. Authored per-stage generator
tables are decoded for two stages: `stag0102` (sampled) and **`stagGF01` in full**
(§4b: all 24 generators, with rows, counts and drop lists).

The "MODELCTRL is the enemy spawner" reading
is **refuted** (§7).

---

## 1. The three layers

| Layer | Object / site | Notes |
|---|---|---|
| Lua script | `be:sd("GENERATER", nil, -1, "START", "GENE-xx")` | the **only** enemy-spawn entry point |
| Data (authored) | `Gap::Bec::beGeneraterData`, vtable `0x535EB0`, size 0x68 | one per `GENE-xx` in the stage pack's `separate/generatorH.igb` |
| Runtime | `beGeneraterInfoWork`, vtable `0x536050` | one per player per started GENE |

`beGenerater` (the subsystem) methods are
`START / STOP / STOPREVERS / RESET / RESTART / PERFECTDROP / ONFREEZE / OFFREEZE`
(name table at `0x4c6b50`). Lua calls them as
`sd("GENERATER", nil, -1, "<METHOD>", "<GENE-xx>")`.

## 2. `beGeneraterData`: the authored spawn record

Full field map, taken from the ELF reflection name arrays (fields listed at
`0x4c69f0`) and confirmed by a live read of 71 entries in stag0102:

| Off | Field | Meaning (live example) |
|---|---|---|
| `+0x08` | name | interned `GENE-00` |
| `+0x0c` | `_pos` | 3×f32 **world** position (GENE-00 = −117, 72, 609) |
| `+0x18` | `_genePosIsGlobal` | 1 = `_pos`/list are world coords |
| `+0x1c` | `_genePosList` | VList of 12-byte xyz positions |
| `+0x20` | `_geneRotYRadianList` | f32 facing per position (radians) |
| `+0x24` | `_geneEnemyId` | **the 649-row stat-table row** |
| `+0x28` | `_geneEnemySeq` | sequence id |
| `+0x2c` | `_startModeStr` | `direct` / `radar` / `timer` |
| `+0x30` | `_startData` | f32, meaning depends on start mode (§4) |
| `+0x34` | `_fillModeStr` | `wipeout` / `add` (+timer) |
| `+0x38` | `_fillData` | f32 |
| `+0x3c` | `_callLua` | callback script |
| `+0x40` | `_playerDataList` | → `beGeneraterPlayerData` per player |

`beGeneraterPlayerData` (`0x535DE0`): `+0x08 _geneCount`, `+0x0c _geneMaxCount`
(how many enemies this point maintains), `+0x10 _itemDataList`,
`+0x14 _itemLastDataList` (weighted drop table, `_rank`/`_rate`; see
**`docs/systems/drop-tables.md`**).

Example live entry, **GENE-00**, the end-of-bridge e_ogre demo:
`row=36`, `_pos=(−117,72,609)`, `global=1`, `start=direct/150.0`,
`fill=wipeout/0`, `_genePosList` count 1 (same triple), `rotY = 2.618 rad = 150°`,
`_geneCount/_geneMaxCount = 1/1`.

## 3. Triggers: two layers

**(a) Lua / script.** Stage chunks call `START/STOP/RESTART` behind ordinary
script conditions: `be:FLGisOn(n)` / `be:FLGset`, `be:PLAYERgetPos()` (entry
point, 0–4 in this stage), `be:SYSgetPlayerNinzu()` (1P vs 2P+), `be:SYSctlDeviceFolder(...)`
(difficulty / equipped device), and `be:DMsetSD(..., <frame time>)` + `DMrun()`
scheduling.

Worked example, `02-valley-overworld/02-stag0102-valley-crossroads_e621/022-layer-setup-msg-63024.lua`:

```lua
if be:FLGisOn(356) == 0 then               -- first visit only
    be:FLGset(356, 1)
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Sdc0102a")
    be:DMsetSD("GENERATER", nil, -1, "START", "GENE-00", 10)  -- the bridge e_ogre
    be:DMchkSD("MODELCTRL", "e_ogre", -1, "ISRUN", "==0")
    funcOpenDigimonInfoWin(...)            -- tutorial popup
    ...
end
...
if be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 1 then
    local random = be:SYSgetRandom(300)
    if     random >= 61 then be:sd("GENERATER", nil, -1, "START", "GENE-a00")   -- row 5
    elseif random >= 41 then ... GENE-a01 ...                                  -- row 380
    elseif random >= 25 then ... GENE-a02 ...                                  -- row 383
    elseif random >= 13 then ... GENE-a03 ...                                  -- row 386 pink
    ... end
end
```

The `random` compare chain is the crown roll (§5c).

`004-generator-gene-47-gene-48-gene-49.lua` starts `GENE-47/48/49/50` unconditionally; `012-enemy-blosso.lua`
starts `GENE-38` (row 78 `e_blosso`) behind a flag.

**(b) Engine, per-entry start mode `_startModeStr`.**

| mode | behaviour | `_startData` |
|---|---|---|
| `direct` | spawn as soon as the generator runs, no range gate | **unused**: the engine never reads it in this mode; the value just mirrors the authored facing angle in degrees (the facing itself comes from `_geneRotYRadianList`) |
| `radar` | spawn when the player comes within range | **squared radius**; live values 625=25², 1225=35², 2025=45², 3025=55², 4225=65² |
| `timer` | countdown, armed under the key **`BOOT_TIMER`** | **frames** at 60 fps; the code arms it as `f × 1e9 / 60` ns |

`_fillModeStr` decides what happens after the first wave (state 1 fills to `_geneMaxCount` at once in every mode, §5b; retail GENE-09, fill `add`, spawned all six within 18 ms), and the three modes are
exact:

| `_fillModeStr` | behaviour |
|---|---|
| `add` | spawn **one** each frame whenever the live count is below `_geneMaxCount` |
| `wipeout` | wait until the live count is **zero**, then spawn `min(remaining, _geneMaxCount)` in one batch |
| `timer` | spawn one each time the refill timer **`GENE_TIMER`** expires, re-armed with `_fillData` |

So `GENE_TIMER` is not a property but the *name of the refill timer entry*; the
start timer is a second entry under the key `BOOT_TIMER`. Both are armed with the
authored float converted from **frames**: `f × 1e9 / 60` nanoseconds, so `60` = one
second. In `direct` mode `_startData` is **not read at all** by the engine (the
facing comes from `_geneRotYRadianList`), which is why its value only mirrors the
angle.

**Confirmed live:** walked the pristine bridge and 3× `e_goburi` (row 5, HP 649)
spawned on entering radar range of the row-5 points.

## 4. Where the spawn goes

- Single point: `_pos` (+0x0c), world coords when `_genePosIsGlobal`.
- Multi point: `_genePosList` (+0x1c), an array of 12-byte xyz triples.
- Facing: `_geneRotYRadianList` (+0x20).
- The runtime instance tracks the current point (`_genePoint`) and remaining
  count (`_nokoriKazu`).

At spawn time **`FUN_00384540`** reads the position from
`_genePosList[_genePoint]` (entry `+0x1c`, count at `+0x08`, data at `+0x10`; 12-byte
xyz triples) and the facing from `_geneRotYRadianList[_genePoint]` (entry `+0x20`),
converts the rotation to degrees (`× 57.29578`) and pushes both into the model's
`GENERATE` call. When `_genePosIsGlobal == 0` the position is `_pos + list[i]`;
when it is 1 (every entry seen in stag0102) it is `list[i]` alone, so for global
rows `_pos` is only the **radar/range anchor**, not the spawn point. It then
advances the cursor: `_genePoint = (i + 1) % count`.

**This is read per spawn, not baked at `START`**, verified live:
injecting a unique `Y = 123.456` plus rotation 0 into every row-5 `_genePosList` /
`_geneRotYRadianList`, then reloading and walking, produced live model transforms
(vtable `0x537F40`) whose translation was exactly the entry's `(x, 123.456, z)` with
an identity rotation. **Practical consequence:** editing `_genePosList` moves the
next spawn and editing `_geneRotYRadianList` turns it, live, no reload needed.

## 4b. `stagGF01` generator inventory (live, complete)

All 24 authored generators, read out of a live fortress.
`_geneEnemyId` is row 0 or 2 for every one of them, both ordinary `e_goburi`
(Goburimon) rows of the 649-row table, i.e. **this stage contains no other enemy
type**. `_pos` is the radar anchor (`_genePosIsGlobal` = 1 on every entry); the
positions sit on a clean 20-unit grid, which is what makes them recognisable as one
stage's authored set.

| generator | row | fill | count/max | start | drop list |
|---|---|---|---|---|---|
| `GENE-00` | 2 | add | 12/9 | radar (5,10,15) | nZ1gobr3 |
| `GENE-01` | 0 | wipeout | 1/1 | radar (35,10,15) | nZ1gobr3 |
| `GENE-02` | 0 | wipeout | 1/1 | radar (55,10,-5) | nZ1gobr3 |
| `GENE-03` | 0 | wipeout | 1/1 | radar (75,10,15) | nZ1gobr3 |
| `GENE-04` | 0 | wipeout | 1/1 | radar (55,10,35) | nZ1gobr3 |
| `GENE-05` | 0 | wipeout | 1/1 | radar (55,10,15) | nZ1gobr3 |
| `GENE-06` | 0 | wipeout | 1/1 | radar (-15,10,65) | nZ1gobr3 |
| `GENE-07` | 0 | wipeout | 1/1 | radar (5,10,45) | nZ1gobr3 |
| `GENE-08` | 0 | wipeout | 1/1 | radar (25,10,65) | nZ1gobr3 |
| `GENE-09` | 0 | wipeout | 1/1 | radar (5,10,85) | nZ1gobr3 |
| `GENE-10` | 0 | wipeout | 1/1 | radar (5,10,65) | nZ1gobr3 |
| `GENE-11` | 0 | wipeout | 1/1 | radar (-15,10,-35) | nZ1gobr3 |
| `GENE-12` | 0 | wipeout | 1/1 | radar (5,10,-55) | nZ1gobr3 |
| `GENE-13` | 0 | wipeout | 1/1 | radar (25,10,-35) | nZ1gobr3 |
| `GENE-14` | 0 | wipeout | 1/1 | radar (5,10,-15) | nZ1gobr3 |
| `GENE-15` | 0 | wipeout | 1/1 | radar (5,10,-35) | nZ1gobr3 |
| `GENE-16` | 0 | wipeout | 1/1 | radar (-15,10,-145) | nZ1gobr3 |
| `GENE-17` | 0 | wipeout | 1/1 | radar (5,10,-165) | nZ1gobr3 |
| `GENE-18` | 0 | wipeout | 1/1 | radar (25,10,-145) | nZ1gobr3 |
| `GENE-19` | 2 | add | 14/4 | direct (-75,10,-135) | **`comonNOTG01` (empty, never drops)** |
| `GENE-20` | 0 | wipeout | 5/1 | direct (-25,10,-215) | nZ1gobr3 |
| `GENE-21` | 0 | wipeout | 5/1 | direct (35,10,-215) | nZ1gobr3 |
| `GENE-22` | 0 | wipeout | 5/1 | direct (85,10,-135) | nZ1gobr3 |
| `GENE-23` | 2 | add | 12/9 | radar (5,10,15) | nZ1gobr3 |

`GWCS-05` (row 378 = `g_woodencasez05`, count 9/9) is the stage's **destructible-case**
generator, not an enemy one: it is the only entry pointing at the object pool
`Z1obje1` (see `docs/systems/drop-tables.md` §5).

**The combat wiring** (`lua/12-goblimon-fortress/01-fortress-gate_e772/`):
`000-dm-run-sq-swof.lua` takes control off the player (`PLAYER`/`ENEMY` `OFCTRL`), switches the
breakable gates on and `START`s **GENE-23** (the room fight, 12 Goburimon);
`017-damage-calc-g-breakinggatez05.lua` fires when a gate is cracked, `STOP`s GENE-23 and `START`s
**GENE-00** (12 more Goburimon) and **GENE-19** (14 more, no drop list). The trailing
number in `START "GENE-xx", N` is a frame delay, not a count (the same slot is used
for `ONCTRL`, 60); the enemy total comes from `_geneCount`.

**Proven:** `_geneMaxCount` **is** the alive-at-once cap, read from the
code rather than inferred. `add` spawns only while the live count is below it, and
`wipeout` spawns `min(remaining, _geneMaxCount)` per batch; `_geneCount` is the total
for that player, and the remaining counter (`_nokoriKazu`, the state object's `+0x10`)
starts at `_geneCount − spawned` after the first wave. It fits every entry here
(single spawns are 1/1; the crate generator is 9/9 against 9 crates that are all
present), and 14/4 for the wave spawner.

---
## 5. Native chain

```
Lua sd("GENERATER",…,"START","GENE-xx")
  └─ beGenerater::START            (creates per-player beGeneraterInfoWork)
       └─ Gap__Bec__beGenerater__vfunc_31             per-frame state machine (state @ +0x1c)
            ├─ start modes: 'd' direct / 'r' radar (range vs +0x30) / 't' timer ('BOOT_TIMER')
            ├─ fill modes : 't' timer ('GENE_TIMER') / 'a' add / 'w' wipeout
            ├─ FUN_00384800        drop pass for the dead
            └─ FUN_00384540        spawn: position + facing + the MODELCTRL command
                 └─ beNDMWMdlEnemy__OnGenerate   enemy model GENERATE
                      message ints: row → _recNo, HPMAX → _mHp and _hp
                      DATABASE 'enemy' GETDATABASE → row RARITY
                      → RARITY ≠ 0: SETRAREICON(rarity) to the ENEMY info, delay 60
                      → beModelCtrl__OnGenerate (base generate: start position)
```

`beNDMWMdlEnemy` is the enemy's model controller. Besides `OnGenerate` it overrides
`IsKind` (slot 35, `KIND_ENEMY`), `RegisterReceiver` (slot 37, receiver group `ENEMY`),
`OnSequenceChange` (slot 44, straight to `beNDMWMdlPEBase_OnSequenceChange`) and
`GetMeta` (slot 20). `OnGenerate` (slot 36) creates the `beNDMWMdlEnemyInfoWork`
(`beNDMWMdlEnemyInfoWork_Create`) in the info RAM's `ONE` record, fills it from the
message when the message carries ints, and always finishes with the base
`beModelCtrl__OnGenerate`, which places the model from the message's position and
rotation (or matrix).
`beGeneraterInfoWork`'s **per-player state object** (pointer at `+0x2c`, created on
the generator's first frame) is where the live fields sit (they are
not on the InfoWork itself): `+0x0c` the 1-based
player index, `+0x10` `_nokoriKazu` (remaining to spawn), `+0x14` the live-enemy
list, `+0x18` the `_genePoint` cursor, `+0x1c` the **latched** `MODEL` name,
`+0x20` the row, `+0x24` `HPMAX`, `+0x28` a float timer speed, and `+0x08`/`+0x09`
two flags that bypass the state machine (drops keep being processed, nothing spawns).
The enemy-side InfoWork is `beNDMWMdlPEBaseInfoWork` (vtable `0x53D3E0`),
`+0x10` row, `[+0x0c]+0x0c` current HP.

`beGeneraterInfoWork` is the quickest way to read a spawn's rolled row: an enemy InfoWork
only populates `+0xF0` and `+0x110` about four seconds of unpaused play after spawn.
Several objects share the InfoWork vtable `0x0053D3E0` and live ones move between loads,
so keep those with `+0x110 == *(0x58A1C0)`, `+0xEC == 0` and `+0xF0 != 0`.

### 5b. The state machine

The state lives at `InfoWork+0x1c`; `InfoWork+0x14` is the active flag (cleared when
the generator finishes). Four states:

| state | meaning | does | advances when |
|---|---|---|---|
| 0 | **start condition** | `d` direct → fire now; `r` radar → fire when the player is within `_startData` (a squared distance); `t` timer → arm `BOOT_TIMER` with `_startData` and fire on expiry | the condition holds |
| 1 | **first wave** | spawn up to `_geneMaxCount` (`FUN_00384540` returns how many landed) and set `_nokoriKazu = _geneCount − spawned` | always → 2, or → 3 if `_nokoriKazu < 1` |
| 2 | **maintain** | run the drop pass for the dead, then the fill mode (§3) | `_nokoriKazu < 1` → 3 |
| 3 | **finish** | drop pass with `param = 1`, which selects `_itemLastDataList` (`+0x14`) instead of `_itemDataList` (`+0x10`) | the live list is empty → call `_callLua` (`+0x3c`), clear the active flag, release the state object, reset to 0 |

`FUN_00384540` is the spawn (not the drop pass): it reads
`_genePosList[_genePoint]` (the cursor wrapping modulo the list's count) and
`_geneRotYRadianList[_genePoint]`, adds `_pos` when `_genePosIsGlobal == 0`, converts
the facing `× 57.29578` to degrees, stamps the `MODELCTRL` command sequence
(`FIND_SPACE` → position/facing → sequence (`_geneEnemySeq`, default `SQ_ENTR`) →
`GENERATE`), and returns the number actually spawned: `0` when the model pool is
full, which stops the wave rather than overrunning it.

A wave is synchronous. GENE-11's list count reaches 1, 2, 3 within 2 ms and 4 one tick
later, with the state object's remaining count (`+0x10`) at 0 at once; GENE-10 reaches 4
within 17 ms. So the last one or two instances can go active one tick after the first
ones. No pooled-instance delay shows, in a small sample (GENE-11 twice, GENE-10 once).
GENE-10 getting 2 of 4 while GENE-06's four row-25 enemies are alive is consistent with a
shared instance pool.

### 5c. Crowns

The crown roll is Lua, not native. Seven stage chunks (for example
`lua/02-valley-overworld/02-stag0102-valley-crossroads_e621/022-layer-setup-msg-63024.lua`, §3)
draw one `SYSgetRandom` per enemy group at load, then pick a generator by a compare
chain, repeated per `armor2` branch (`ISEQUIP` 27, 28, 29 or none). Groups a and b use
`>= 61/41/25/13/5/0` and group c uses `>= 27/20/14/9/5/0`, selecting `GENE-x00` to
`GENE-x05`. In `stag0102` those carry rows 5, 380, 383, 386, 389 and 392: no crown, then
ranks 1 to 5 (pack 622; §6c gives the other tiers). A roll of 13 is the only value that
selects `GENE-x03` (row 386, pink) in both sets.

At most four enemies show a crown at once. The crown is drawn from `_dispRamNoList[10]`
(`i_rareicon`, status index 10), which holds a display id, not the rank. With six enemies
and four crowns, exactly four objects hold ids 0, 1, 2 and 3 and the others hold -1, so
nothing is culled at draw time: the draw loop at `0x443d00` walks a fixed 12 statuses and
the extra enemies have no crown data. A freed id is reused, so killing a crowned enemy can
crown another. The value comes from `beMessenger_GetObject(this->0x14, 0)` field `+8` and
`beMessenger_SelectReceivers` stores it in the icon object at `+0x10`. Where the 0..3 range is bounded is
open (§7).

## 6. What is modifiable, and how

| Want to change | Knob |
|---|---|
| which enemy a point spawns | `_geneEnemyId` (+0x24), a stat-table row; **proven live and from disc (§6c)** |
| how strong it is | the row in the ISO stat table (data patch, `patch_iso.py`) |
| where it spawns | `_genePosList` (+0x1c) per element; `_pos` (+0x0c) is the radar anchor when `_genePosIsGlobal` (+0x18); proven live |
| facing | `_geneRotYRadianList` (+0x20), radians; proven live |
| how many | `beGeneraterPlayerData._geneCount/_geneMaxCount` (+0x08/+0x0c) |
| when it spawns | Lua `START/STOP` per stage chunk; engine `_startModeStr`/`_startData` |
| whether it refills | `_fillModeStr`/`_fillData` (+0x34/+0x38) |
| crown icon | row RARITY (colour only); the row comes from the Lua roll (§5c) |

All of these are per-stage data inside the packs (generator igb), so a spawn edit is a
pack edit. That path is open (§6c): the row/position/rotation values read straight
out of the pack (`scripts/igb_inst.py`) **and** live (`beGeneraterInfoRam` →
`beGeneraterData`), and `_geneEnemyId` has been changed both ways and booted.

## 6b. Swapping the spawned **model**: pinned, not re-read per spawn

Unlike position and facing, the spawned **model name is latched at generator init**:
`Gap__Bec__beGenerater__vfunc_31` copies `MODEL` from the row into `beGeneraterInfoWork+0x1c` once when the
generator starts, so repointing that field alone has **no effect** on an already-running
generator. What was tried on the loaded `stag0102` bridge (row 5 = `e_goburi`):

| step | result |
|---|---|
| repoint live `InfoWork+0x1c` → `'n_leomon'` | no effect (no new spawn occurred, so the latched copy was never used) |
| repoint the **row's** `MODEL` string object (`[0x01749308+8]`) → `'n_leomon'` **and** force re-init (`InfoRam+0x2c := 0`) | **worked at the data level** (fresh InfoWorks read `model='n_leomon'`), but **no Leomon was created or rendered**: the name is in the stage manifest (pool `0x012bfac0`) but its **geometry is not resident** in stag0102 |
| same method with a **resident** model (`'e_ogre'`, string `0x69298c`; row 36 already uses it there) | fresh InfoWork read `model='e_ogre'`; the row-5 population went **3 → 7** and green club-wielding Ogremon appeared where Goburimon had been |

**Conclusion (confirmed):** model swapping works
for models whose geometry is loaded in the stage, and **fails silently for models that
are not**. Why: the generator resolves the row's `MODEL` **once, when its InfoWork is
created** (the generator's first frame after `START`), stores it at `InfoWork+0x1c`, and
every spawn re-sends that latched name into the `MODELCTRL` `GENERATE` command, so
repointing a running generator cannot change it; only a fresh InfoWork re-reads the row.
The decisive instance-count check is a controlled A/B on
one generator (`GENE-13`, stag0102, same session): the **resident** `e_ogre` row 36
latched (`model=e_ogre`, HP 662) and spawned (enemy count 1, rendered), while the
**non-resident** `e_mummy` row 114 latched correctly (`model=e_mummy`, HP 200) and
spawned **nothing**: enemy count 0, and a RAM scan for `beNDMWMdlPEBaseInfoWork`
(vtable `0x53D3E0`) found 4 live `row=36` objects and zero `row=114`. The stage's own
resource pool has `hit_e_ogre.lua` / `hit_e_blosso.lua` / `gobr_skinShape2` /
`E_goburi01.png` and **no mummy asset at all**. So **Mummymon cannot be put into Abyss of
Grief by any row edit**: a spawn row is only a name, and loading a model that the stage
does not carry is a *content* mod (its igb + textures + animation added to the stage
packs), not a spawn-table change.

Method notes: the table's `MODEL` column is `DB+0x34` → data → `[row]` → strObj (text
pointer at `strObj+8`), `DB = 0x1748840`; repeatedly zeroing `InfoRam+0x2c` **leaks**
InfoWork objects (the refcounted replacement is at `0x384d08..0x384d3c`), and killing via
HP=0 alone did not reliably free a slot. Re-init only helps an *active* generator: the
per-frame state machine reads the byte flag at `InfoRam+0x14` first (`0x384c68`) and
returns when it is 0.

## 6c. A spawn editor, both ways

The row knob is confirmed live and from disc; the recipe is small.

**Live (per loaded stage, any R5900 build):** enumerate the generator graph by vtable or,
better, resolve it from the InfoRams:

```
beGeneraterInfoRam (vt 0x535FF0) +0x08  data-list index
                                 +0x0c  -> beGeneraterInfo (+0x1c _dataList -> +0x10 array[idx])
                                        -> beGeneraterData  (the authored GENE record)
                                 +0x14  byte: generator active
                                 +0x2c  refcounted _work -> beGeneraterInfoWork (vt 0x536050)
beGeneraterInfoWork +0x1c latched model name (char*), +0x20 row, +0x24 HPMAX
```

Then write the new row to `beGeneraterData+0x24` and clear `InfoRam+0x2c` to force a
re-latch. This turned the stag0102 bridge's `e_goburi` (rows 4/5) into `e_ogre` (row 36); GENE-03
and GENE-13 both verified on screen.

**Durable (cold boot):** rewrite `_geneEnemyId` in the stage's generator pack and patch
the ISO. The pack is `NDMW.AFS` entry 622 (§7), the field's record offset is recomputed
by walking the record's own descriptors, and the write is a
same-size 4-byte edit: turning Goburimon into Ogremon changes **156 4-byte words** (52 per tier
pack × 3) in a copy of the disc and nothing else. A cold boot of that disc spawns
Ogremon where the vanilla disc spawned Goburimon.

**Tier packs:** entries **622/623/624** are the
same 72-generator stag0102 layout (identical `GENE` positions) at three **row tiers**:
622 = `e_goburi` 4/5 + `e_ogre` 36, 623 = 0/1 + 33, 624 = 8/9 + 39, i.e. the tier-1/0/2
bands of the `e_goburi` rows 0–11 and `e_ogre` rows 33–41. Which one loads depends on
the difficulty/setting (the live session here used 622). So a pack edit is a *set* of
edits, each pack mapped to its own e_ogre row.

The three packs differ only in `_geneEnemyId`: names, positions, timers, modes, `_callLua`
and the 772-row drop table are identical, and 69 of 72 generators change id. Relative to
622, each generator shifts by its own constant, down in 623 and up in 624: 4 for 37
generators, 3 for 16, 1 for 15, 2 for 1, 0 for 3. The ids therefore select consecutive
stat-row bands, for example `GENE-00` reads 36/33/39. The crown rows (§5c) shift the same
way: 380/383/386/389/392 in 622, 379/382/385/388/391 in 623, 381/384/387/390/393 in 624.

## 7. Refuted readings, settled points and open questions

- **Refuted:** `Gap__Bec__beNDMWMdlPlayer2__vfunc_47` is *not* the enemy spawner. It is the
  `g_000bcaps` **checkpoint-capsule** command handler (`GENERATE` / `GENESTAGE` /
  `RAISE`, using `GAMERAM::GETCOMMON`, `BKCHIPSTAGE`, `BKCHIPPOS`, `SQ_ENTR%dP`;
  sibling `Gap__Bec__beNDMWMdlPlayer2__vfunc_36` writes the checkpoint, `Gap__Bec__beNDMWMdlPlayer2__vfunc_38` is its proximity
  switch). Enemy generate is `beNDMWMdlEnemy__OnGenerate` (vtable slot `0x53e448`). (The *spawn*
  command **is** issued through the `MODELCTRL` interface (`FIND_SPACE` →
  position/facing → `GENERATE`), so "MODELCTRL is not involved" is too strong;
  what is refuted is only `Gap__Bec__beNDMWMdlPlayer2__vfunc_47` being the spawner.)
- **The generator rows AND their positions read offline.** `scripts/igb_inst.py --blob <pack> --lists` reads a stage's generator
  records (`_pos`, `_geneEnemyId`, `_startModeStr`/`_fillModeStr`, the `_startData` frame
  timer, `_callLua`) **and** every list's contents from the disc: a list reads
  `{count, count, _data}`, `_data` is an **ordering key**, and laying the lists out in
  ascending `_data` order reconstructs the pack's content pool exactly (entry 622: 7,112
  bytes needed and present, ending at the pack end). So the spawn **positions and
  rotations** are available for **every** stage with no emulator. Verified against the
  running game: live `GENE-00`'s position list holds `-117.0` and the file's authored
  `_pos` `(-117.0, 72.0, 609.0)` is that exact pool block. One caveat for matching file to
  live: **`_pos` is rewritten at runtime** (the live value reads 608.0 against the file's
  609.0), so it is not a fingerprint. **`stag0102`'s generator pack is `NDMW.AFS` entry
  622** (72 generators, matching the 72 live instances), found by a fingerprint that is
  unique across the archive. **The three same-size entries 622/623/624
  are the three row-tier variants of stag0102** (same
  generator layout and positions, different `e_goburi`/`e_ogre` rows: 4/5+36, 0/1+33,
  8/9+39); the tier the game loads depends on difficulty. An `igObjectRef` id indexes the
  pack's own remap table (`scripts/igb_ids.py`), so the **drop-list groupings** also
  resolve offline; see [`drop-tables.md`](drop-tables.md) §6.
- **Open:** decode the per-stage generator igb tables for every stage. The instance
  encoding is solved and entry 622 reads end to end, so this is a sweep of
  the 143 generator-bearing packs, not a format question. (`stagGF01` is also done in
  full; §4b, read live.)
- **Timer-mode semantics.** `_startData`/`_fillData`
  are in **frames at 60 fps** (armed as `f × 1e9 / 60` ns), under the timer keys
  `BOOT_TIMER` (start delay) and `GENE_TIMER` (refill period).
- **`_fillModeStr` vs `_geneMaxCount`/`_nokoriKazu`:** the
  three modes are decoded above (§3), and `_geneMaxCount` is the alive-at-once cap.
- **The drop-table path** (`beGeneraterItemDataOne._rank`/
  `_rate` + `PERFECTDROP`) is fully traced: structure, the `RNG%10000` subtractive
  roll, the difficulty index, the family→pool map and the `stagGF01` Guard Room
  box tables are in **`docs/systems/drop-tables.md`**, as is the
  pack-internal id/`X` encoding that reads a table's element array *without* a live
  reference.
- **`_isPerfectDrop` is not at `0x5050b8`**; that address
  holds the reflection *name string* `"_isPerfectDrop"` (followed by `beFontInfo`).
  The `PERFECTDROP` method (index 5 of the `0x4c6b50` name table) is never called by
  any Lua script in the game, so there is no reachable always-drop state.
- **Open:** where the 0..3 crown display id range (§5c) is bounded. A four-entry display
  table and the four per-player generators are the candidates; neither is proven.
- **Open:** whether spawn positions can be stage-local (`_genePosIsGlobal=0`) in
  any real entry; every stag0102 entry was global.
- **The model swap and its limit.** The row
  (`beGeneraterData._geneEnemyId`) is the knob; the model is latched into
  `beGeneraterInfoWork` at init, so a running generator must be re-latched by clearing
  `beGeneraterInfoRam._work` (+0x2c). Resident models swap (Goburimon → Ogremon in
  stag0102, live and in a patched ISO); **non-resident models spawn nothing** (the
  `e_mummy` A/B, with its instance-count check). §6b/§6c.
- **Terrain snapping of Y: player answered, enemy open.**
  Injecting a large Y into the model transform and
  re-reading it over time **cannot answer the question**: `*(0x0058a1e8)` is a *placement
  record*, not the live position (writing `Y = ground+200` to its six copies round-trips
  and **persists** while the character visibly stays on the ground). It has to be read from
  the live **mirror** triples, by a paused differential. One trap: `0x100000–0x300000` is the
  *static program image* and never changes however much the world moves. Measured that way, the **player
  does snap up**: writing `Y = floor−6` to its six authoritative copies returns them to the
  floor and holds, and writing `y+60` visibly lifts the character.

  **The enemy half is open.**
  A reading that an enemy displaced upward falls back (254.7 → 180.0 → 84.8) and one
  displaced downward stays underground is not valid: both were read from **derived** copies:
  writing `x+60, y+40` to all three of an enemy's copies produced no visible movement in
  24 captured frames, so those copies are refreshed values, not the source the renderer
  uses, and any behaviour measured by writing them is the refresh schedule. The suggestive
  live evidence (a 15-entity census with enemy Y tracking ground over 10–28 units of
  motion) is consistent with ground-following but is not proof.

  **The clean experiment, not yet run:** author a spawn Y **below** the floor in
  `_genePosList` (the engine's own placement path, read per spawn) and watch
  whether the spawned enemy appears on the floor. That writes the entity through the engine
  instead of poking derived copies. Also still open: terrain following *during motion*.
- **The generator rows are readable live.** Enumerating engine
  objects by their `+0` vtable pointer finds the whole `beGenerater*` graph for a loaded
  stage (72 `beGeneraterData` in stag0102, plus `beGeneraterInfoRam`,
  `beGeneraterPlayerData`, `beGeneraterItemDataOne` (772 drop rows, stride 32), and reading
  them at the reflection offsets gives the row's values: `_geneEnemyId`, `_startModeStr`
  (`"direct"`), `_startData` (150.0), `_fillModeStr` (`"wipeout"`). The live works resolve
  `_geneEnemyName` → `"e_goburi"` with `_geneEnemyRecNo` 5 and `_geneEnemyMHp` 649, exactly
  the stat-table values for `e_goburi` RecNo 5. So the generator rows can be read without
  the igBinary decode (**the values, not the format**) per loaded stage and with the
  emulator up, which makes it a cross-check for the decode rather than a replacement.
