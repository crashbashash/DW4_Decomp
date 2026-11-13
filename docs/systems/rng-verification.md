# RNG verification: evidence

Raw, reproducible evidence for the claims in [`rng.md`](rng.md). Everything here
was produced by `scripts/dw4_rng.py`, `scripts/p2s_ram.py`,
`pine`, and `mipsel-linux-gnu-objdump`.

- **Generator / seed:** §1
- **No reseed / single sequence:** §7
- **Consumer inventory:** §5, §7
- **New-game timeline + hub drain:** §2, §3

---

## 1. The seed: MT19937 `sgenrand(5150)` matches every snapshot

`python3 scripts/dw4_rng.py check snapshots/*.bin`

```text
pre_load.bin             RNG @ 0x6ff180 mti= 318 state0=2b8d2459  twist#5   draws_since_boot=2814
pre_load2.bin            RNG @ 0x6ff180 mti= 318 state0=2b8d2459  twist#5   draws_since_boot=2814
crown6.bin               RNG @ 0x6ff180 mti= 155 state0=6eb16ca3  twist#4   draws_since_boot=2027
pink_ram.bin             RNG @ 0x6ff180 mti= 533 state0=a8a088ad  twist#19  draws_since_boot=11765
before_spawn.bin         RNG @ 0x6ff180 mti= 196 state0=a8a088ad  twist#19  draws_since_boot=11428
after_spawn.bin          RNG @ 0x6ff180 mti= 256 state0=a8a088ad  twist#19  draws_since_boot=11488
nc_ram.bin               RNG @ 0x6ff180 mti= 280 state0=a8a088ad  twist#19  draws_since_boot=11512
pk_ram2.bin              RNG @ 0x6ff180 mti= 212 state0=a8a088ad  twist#19  draws_since_boot=11444
```

All eight states match the **full 624-word** array of one MT19937 sequence
seeded by `sgenrand(5150)`, at three different points (twist #4, #5, #19).
A 2496-byte match cannot occur by chance, so the seed is fixed and the states
share one stream.

### First outputs of the sequence

`python3 scripts/dw4_rng.py seq 4`

```text
     0  cdb83dd3  -> %2=1 %6=1 %20=11 %100=31 %122=63 %300=31
     1  d10604d7  -> %2=1 %6=5 %20=19 %100=99 %122=61 %300=299
     2  f11df354  -> %2=0 %6=0 %20=12 %100=92 %122=40 %300=192
     3  cd1139a9  -> %2=1 %6=1 %20=13 %100=53 %122=81 %300=253
```

Statics backing the seed (`sgenrand` multiplier 69069, `Reset()` hard-codes
5150, single object):

```sh
mipsel-linux-gnu-objdump -d --start-address=0x1e6b20 --stop-address=0x1e6bd0 \
    orig/SLUS-20836/SLUS_208.36          # sgenrand(69069) + Reset() = 5150
grep -n "li.*5150" /tmp/dw4.dis        # one hit: 0x1e6ba4
grep -n "jal.*371f10" /tmp/dw4.dis     # one hit: the Lua stub 0x370888
grep -n -- '-24136' /tmp/dw4.dis       # 10 reads of *(0x58A1B8); only 0x371f28 uses +0x30
```

---

## 2. New-game path timeline

RNG object extracted offline from the curated states with `p2s_ram.py`; draws =
number of `genrand` calls since boot.

| state | `_mti` | twist # | draws since boot |
|---|---|---|---|
| `smoke-title` | 624 | 0 | **0** |
| `dw4-create-menu` | 624 | 0 | **0** |
| `op-load-in` | 16 | 1 | 16 |
| `op-ready` | 279 | 1 | 279 |
| `fresh_save_before_enter_world_1` | 334 | 7 | **4078** |
| `fresh_save_before_finish_practice_stage` | 266 | 9 | **5258** |

```text
smoke-title.bin                          mti=624 state0=00001533 twist#0  draws=0
dw4-create-menu.bin                      mti=624 state0=00001533 twist#0  draws=0
op-load-in.bin                           mti= 16 state0=53f86731 twist#1  draws=16
op-ready.bin                             mti=279 state0=53f86731 twist#1  draws=279
fresh_save_before_enter_world_1.bin      mti=334 state0=7a909ee3 twist#7  draws=4078
fresh_save_before_finish_practice_stage  mti=266 state0=91738063 twist#9  draws=5258
```

---

## 3. The hub drains the RNG (~26 draws/s)

Loaded `fresh_save_before_enter_world_1` (lobby, at the World-1 gate) and did
nothing; `_mti` read over PINE:

```text
$ pine read 0x6FF188 --type u32
330
$ sleep 5 ; pine read 0x6FF188 --type u32
458          (+128 in 5 s)
$ sleep 5 ; pine read 0x6FF188 --type u32
590          (+132 in 5 s)
```

The source is AFS entry **816** (`lobby-ofanimon-seraphimon`) chunk **c100**,
whose model `WPos` handler runs `funcRandom`, which draws `SYSgetRandom(2)`, a
coin flip that steps the model's path index and stamps `_mti`. A full live read-back (vtable `0x52b8e0`, `mti` 323,
`state0` `91738063`, twist #9, 5315 draws) was still exactly on the
`sgenrand(5150)` sequence, confirming no reseed.

In the practice stage the only resident draw chunk is AFS entry **607** chunk
**18** (`SYSgetRandom(7)`, damage-reaction tier), firing on taking damage.

Measured idle drift elsewhere: **~6 draws/s** in a Goblin Pass field state
whose only resident Lua draw chunk is flag-gated.

---

## 4. Main menu does **not** use the RNG (fresh boot)

Fresh boot of the pristine ISO, no statefile; emulator left on the title screen.

| sample | `_mti` |
|---|---|
| T+0 s | 624 |
| T+5 s | 624 |
| T+10 s | 624 |
| T+15 s | 624 |

The RNG object exists (vtable `0x52b8e0`) and sits at twist #0 / **0 draws**:
the raw `sgenrand(5150)` array. A screenshot
confirms the title screen.

---

## 5. Native consumers exist

`SYSgetRandom` is the only Lua-facing binding, not the only consumer. The RNG object `0x6FF180` has **exactly one** incoming pointer in all of RAM,
at `manager+0x30` (`0x6FF140`). The manager pointer `0x6FF110` occurs **60
times** in RAM, and **53 of those sit at `object+0x10` with a vtable at
`object+0x00`**. Native code therefore reaches the RNG by loading the manager from
`object+0x10`, the RNG object from `manager+0x30`, and calling vtable slot 24 (`genrand`).

**11** such sites (exactly 11 by the strict scan in §7), each immediately followed by a
roll-shaped modulus:

| site | modulus | site | modulus |
|---|---|---|---|
| `0x3849AC` (`FUN_00384800`, item drop) | `%10000` | `0x429EA0` | `%10000` |
| `0x39BDB0` | `%6144` | `0x4480C8` | `%6000` |
| `0x4481B0` | `%620` | `0x42F288` | `%1000` |
| `0x4489A8` | `%10` | `0x39129C` | `& 0xf` |
| `0x376594`, `0x4480F0`, `0x448CEC` | variable | | |

`0x330158` / `0x3301B8` call vtable slots 23/24/25 on `*(s0+0x30)`, and
`0x3300F8` calls slot 24 on `*(0x5871D0)`. Neither is a reseed path: both are the
thread subsystem (§7), and the single-sequence snapshot evidence shows no
reseed in normal play.

---

## 6. Crown roll timing

Question: is the crown/elite variant rolled once at area load (so time-to-reach
is irrelevant), or re-rolled when the enemy spawns?

**Gate → load, `before_load_area.p2s`** (dialogue "Abyss of Grief / Go to the
destination"):

| moment | `_mti` | twist # | draws since boot |
|---|---|---|---|
| at the gate dialogue | 318 | 5 | 2814 |
| after Cross, area loaded | 321 | 5 | 2817 |

→ the load consumed **exactly 3 draws** = the a/b/c crown-group
`SYSgetRandom` calls. Nothing is drawn at the gate before the load.

**`before_crown_spawn.p2s` then walk left**

| moment | `_mti` |
|---|---|
| on load | 196 |
| +25 s idle | **196** (no draws) |
| after walking left | 202 |

Live generator `beGeneraterInfoWork` (vtable `0x536050`) after the walk:

```text
0x1737948  row=386  HPMAX=3200   <- RARITY 3 (pink) e_goburi
0x14ddba0  row=383  HPMAX=3100   <- RARITY 2
0x16e19d8 / 0x17ff7a0 ... row=5  HPMAX=649   (ordinary)
```

→ the crown rank is fixed by the 3 draws at load, and **idling in normal play
costs no draws at all**, so how long you take to reach the spawn cannot change
it. The force-roll mod was not active (that would make the load consume 0
draws, not 3).

Note: the two states are far apart on the sequence (`before_load_area` 2814
draws, `before_crown_spawn` 11428), i.e. they are not consecutive saves.

---

## 7. Native consumer identification + no reseed

Strict scan for the RNG-chain idiom (`lw rX,16(obj)` … `lw rY,48(rX)` …
`lw t9,96(t9); jalr`) found **exactly 11** sites, all `genrand`:

| function / site | operation |
|---|---|
| `FUN_00384800` `0x3849AC` | `genrand()%10000`: item-drop roll |
| `beNDMWShopCtrl40_Update` `0x429EA0` | `%10000 <= t`: probability check |
| `FUN_0039BCA0` `0x39BDB0` | `%6144 / 1000.0`: random float ≤ 6.144 |
| `FUN_003764C0` `0x376594` | `%range`: random duration/timing |
| `beNDMWItemRevisionBase_RollRevision` `0x4480C8`, `0x4480F0` | `%6000+1`, `%level`: item revision roll |
| `beNDMWItemRevisionPocketBase_RollPocket` `0x4481B0` | `%620`: pocket count 0-5 |
| `FUN_0042EB80` `0x42F288` | `(%1000)*1000`: random step |
| `Gap__Bec__beNDMWItemDisk__vfunc_22` `0x4489A8` | `%10 <= 8-k`: poison-cure disk check |
| `Gap__Bec__beNDMWItemInstant__vfunc_22` `0x448CEC` | `%range` scaled: bits paid by item 0 |
| `FUN_00390F80` `0x39129C` | `& 0xf`: small variant index |

**No reseed.** The same strict scan for a slot‑23 (`sgenrand`) or slot‑22 call on
the RNG chain returns **0** sites. The look-alike calls of §5 are false positives:
`Gap__Core__igPsx2Thread__vfunc_30` (`0x330158`/`0x3301B8`, slots 23/24/25 on `*(s0+0x30)`) is
`CreateThread`/`_StartThread` (the thread subsystem), and the `*(0x5871D0)`
slot‑24 call at `0x3300F8` is the same thread manager. The 116-function Lua API
has no set-seed either. So `sgenrand` runs only from `Reset()` (hard-coded
5150): the seed never changes after boot.
