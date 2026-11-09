# RNG — Mersenne Twister, seed 5150, and every draw site

**Status: solved.** The game has exactly **one** pseudo-random generator, seeded
with a **hard-coded constant 5150 (0x141E)** at boot, and it is advanced by the
Lua binding `be:SYSgetRandom(M)` **and by ~11 native `genrand` callers** (drop
rolls, damage/AI rolls — see §4). There is **no reseed anywhere in the code**
— the whole run is a single deterministic MT19937 sequence.

Tool: `scripts/dw4_rng.py`. Generated site table: [`rng-sites.tsv`](rng-sites.tsv).

---

## 1. TL;DR

| Question | Answer |
|---|---|
| Algorithm | **MT19937** (624-word state), original **1997 `sgenrand()` seeding** (multiplier **69069**), not `init_genrand()` |
| **Start seed** | **5150** = `0x141E` — the only seed constant in the ELF; applied once at object construction |
| Reseed during play | **None — no reseed code exists.** Every snapshot of the game anywhere in play lies on the seed-5150 sequence |
| What advances the state | Every `genrand` call — the 112 Lua `be:SYSgetRandom(M)` sites **and** the ~11 native callers (one `_mti` increment each; a full twist every 624 stamps) |
| Native consumers | The Lua binding `SYSgetRandom` (`0x00371F10`) **plus ~11 native `genrand` callers** (item-drop `%10000`, etc.) that reach the same object via `*(obj+0x10)+0x30` |
| Lua draw sites | **112** calls in **44 chunks** across **21 AFS entries** (see §5 / [`rng-sites.tsv`](rng-sites.tsv)) |
| Manipulable? | Yes, trivially — the state is a plain global: read `_mti` to know the exact position, or write `_mt[]` to force any next value |

---

## 2. The generator

The class is `igMersenneTwisterRandomNumber` (a subclass of `igRandomNumber`;
both class names, plus the member names `_mti`/`_mt`, are in the reflection name
pool at `0x4E48D0` / `0x4E4900`). The class registration (`0x001E4630`, property
setup `0x001E46B0`) declares `_mt` as a **624-element array** (it stores the
literal 624) with `_mti` alongside it; nothing serialises or writes them —
see §6).

| Symbol | Address | Notes |
|---|---|---|
| vtable | `0x0052B8E0` | slot 24 = `genrand` |
| `sgenrand(seed)` | `0x001E6B20` | vtable slot 23; MT seeding loop |
| `genrand()` | `0x001E6BC0` | vtable slot 24; twist + temper |
| `Reset()` = seed(5150) | `0x001E6B80` | vtable slot 13; **hard-codes `0x141E`** (bytes `24 05 14 1E`) |
| genrand trampoline | `0x001E7350` | `j 0x1E6BC0` |
| `SYSgetRandom` | `0x00371F10` | Lua API id 4; `genrand() % a0` |

**Seeding is the old MT19937 scheme**, not the modern one: the multiplier
`1812433253` never appears in the ELF, but `69069` (`0x10DCD`) does, at
`0x001E6B2C`:

```c
for (i = 0; i < 624; i++) {
    mt[i]  = seed & 0xffff0000;
    seed   = 69069 * seed + 1;
    mt[i] |= (seed & 0xffff0000) >> 16;
    seed   = 69069 * seed + 1;
}
mti = 624;
```

`Reset()` seeds with the constant:

```asm
001e6b80  addiu sp,sp,-32
001e6b8c  jal   0x2ff130          ; base-class no-op
001e6b94  lw    t9,0(s0)          ; vtable
001e6b9c  lw    t9,92(t9)         ; slot 23 = sgenrand
001e6ba0  jalr  t9
001e6ba4  li    a1,5150           ; <-- THE SEED (0x141E)
```

`Reset()` is a virtual, called through the engine's generic object-init path
(`0x002FF3A0` invokes vtable slots 3, 13, 9, … on every constructed object), so
the generator is seeded once when the singleton is built at boot.

### Why the seed is 5150 and never changes (proof)

`dw4_rng.py check` reconstructs MT19937 from seed 5150 and matches the live
624-word state (all 624 words, not a prefix) in **every** captured RAM image.
The states in the available snapshots all fall on that *one* sequence:

| snapshot | `_mti` | state[0] | twist # | draws since boot |
|---|---|---|---|---|
| `crown6.bin` | 155 | `6eb16ca3` | 4 | 2027 |
| `pre_load.bin` / `pre_load2.bin` | 318 | `2b8d2459` | 5 | 2814 |
| `pink_ram.bin` | 533 | `a8a088ad` | 19 | 11765 |
| `before_spawn.bin` | 196 | `a8a088ad` | 19 | 11428 |
| `after_spawn.bin` | 256 | `a8a088ad` | 19 | 11488 |
| `nc_ram.bin` | 280 | `a8a088ad` | 19 | 11512 |
| `pk_ram2.bin` | 212 | `a8a088ad` | 19 | 11444 |

Different snapshot moments, wildly different draw counts, one seed. An area
load does **not** reseed: a load measures as `_mti 318 → 321`
(3 draws) with the state words unchanged. There is no second MT state anywhere
in the 32 MB, and there are exactly two `0x52B8E0` words in RAM:
the live object and the class descriptor's vtable pointer.

---

## 3. Live layout (stable, non-ASLR)

| Address | Meaning |
|---|---|
| `*(0x0058A1B8)` | engine system manager (`0x6FF110` in practice) |
| `*(0x0058A1B8) + 0x30` | → the one `igMersenneTwisterRandomNumber` instance, **`0x006FF180`** |
| `0x006FF180` | vtable `0x0052B8E0` |
| `0x006FF184` | refcount/flags (`0x0A000001`) |
| `0x006FF188` | **`_mti`** — current index, `0..624` |
| `0x006FF18C` | **`_mt[0]`** — 624 × `u32` = 2496 bytes (object ends at `0x006FFB4C`) |

`genrand()` reads `mt[mti]`, tempers it, and posts `_mti = _mti + 1`. When
`_mti` reaches 624 the twist regenerates all 624 words in place and resets
`_mti` to 0. **Each `SYSgetRandom(M)` call advances `_mti` by exactly one**,
which is why the draw count in the table above is simply the number of
`SYSgetRandom` calls since boot.

---

## 4. Consumers: the Lua binding, and native callers

`SYSgetRandom` (`0x00371F10`) is the Lua-facing entry point (`genrand() % M`):

```asm
371f20  lw   v0,-24136(at)   ; *(0x58A1B8) = manager
371f28  lw   a0,48(v0)       ; manager+0x30 = RNG instance
371f2c  lw   t9,0(a0)
371f30  lw   t9,96(t9)       ; vtable slot 24 = genrand
371f34  jalr t9
371f3c  divu zero,v0,s0      ; genrand() % M
371f48  mfhi v0
```

- `jal 0x371F10` occurs **exactly once** in the whole ELF — from its Lua
  dispatch stub `0x00370888` (API id 4).

**But it is not the only consumer.** Native code reaches the *same* object
through a different chain:

1. The RNG object at `0x006FF180` has exactly **one** incoming pointer in all
   of RAM — at `manager+0x30` (`0x006FF140`). So anything that calls `genrand`
   must first read the manager.
2. The manager pointer `0x6FF110` occurs 60 times in RAM, and **53 of those sit
   at `object+0x10` with a vtable at `object+0x00`** — i.e. game objects carry
   the manager at `+0x10`.
3. At least **11 native functions** do `lw v0,16(obj); lw a0,48(v0); lw t9,0(a0);
   lw t9,96(t9); jalr` — load the manager, then the RNG, then call `genrand` —
   and immediately take a roll-shaped modulus. A strict scan for that exact
   shape finds exactly these 11 (no others):

   | function / site | what it does |
   |---|---|
   | `FUN_00384800` `0x3849AC` | `genrand()%10000` — **item-drop roll** (walks the `OneList`, subtracting `_rate`) |
   | `Gap__Bec__beNDMWShopCtrl40__vfunc_21` `0x429EA0` | `genrand()%10000 <= t` — **probability check** |
   | `FUN_0039BCA0` `0x39BDB0` | `genrand()%6144 / 1000.0` — random float ≤ 6.144 (effect/timer offset) |
   | `FUN_003764C0` `0x376594` | `genrand()%range` — random duration/animation timing |
   | `FUN_004480A0` `0x4480C8` `0x4480F0` | two rolls `%6000+1` and `%param` — **damage/score variance** |
   | `FUN_00448190` `0x4481B0` | `genrand()%620` → 6-tier rank (0–5) |
   | `FUN_0042EB80` `0x42F288` | `(genrand()%1000)*1000` — random step |
   | `FUN_004487A0` `0x4489A8` | `genrand()%10 <= 8-k` — probability check |
   | `FUN_00448AE0` `0x448CEC` | `genrand()%range` scaled by `(X+100)/100` — value variance |
   | `FUN_00390F80` `0x39129C` | `genrand() & 0xf` — small index/variant roll |

So combat, loot, AI and other systems advance the same stream — the Lua sites
in §5 are only part of the picture.

**No reseed exists in code.** A strict scan for a slot‑23 (`sgenrand`) or
slot‑22 call on that same `object+0x10 → +0x30` chain returns **zero** sites.
The `0x330158`/`0x3301B8` calls to slots 23/24/25 on `*(s0+0x30)` are the
**thread subsystem** (`Gap__Core__igPsx2Thread__vfunc_30` is `CreateThread`/`_StartThread`), and the
`*(0x5871D0)` slot‑24 call at `0x3300F8` is the same thread manager — neither is
the RNG. Likewise the 116-function Lua API has no `SYSsetRandom`. So `sgenrand`
is called only from `Reset()` (slot 13) via the generic object-init path, with
the hard-coded seed 5150.

> There is a second, unrelated generator: the embedded Lua's **`math.random`**
> (`0x0024FEE0`) / `math.randomseed` (`0x002500A0`) use the C library
> `rand()`/`srand()` (`0x00128FA0` / `0x00128F88`); `math.random` draws
> `rand() % 0x7FFFFFFF`. No game script calls
> `math.random` (0 occurrences in the 5291 decompiled chunks), so it is dead in
> practice. `AREA.AFS` contains no Lua at all.

---

## 5. Every **Lua** draw site (112 calls, 21 entries)

All 112 are `be:SYSgetRandom(M)` in the stage-pack Lua. Grouped by what they
control:

| Entry | Stage | n | M | What the draw controls |
|---|---|---|---|---|
| `e0614` | stag0101 Valley Entrance | 1 | 100 | first-visit intro-demo enemy (GENE-21 goburi vs GENE-22 nume) |
| `e0621` | stag0102 Valley Crossroads | 12 | 180/240/300/420 | **crown/elite enemy variant** (3 groups × 4 armor2 branches) |
| `e0635` | stag0104 Valley Cliff | 4 | 180/240/300/420 | crown/elite variant |
| `e0642` | stag0201 Desert Entrance | 5 | 100 + crown | crown/elite + first-visit demo enemy |
| `e0649` | stag0202 Desert Ruins | 9 | 122 + crown | crown/elite + miniboss (SkullGreymon) add-group `GENE-s01..s05` |
| `e0679` | stag0301 Forest Entrance | 9 | 100 + crown | crown/elite + first-visit demo enemy |
| `e0686` | stag0302 Forest Grove | 9 | 122 + crown | crown/elite + miniboss (Tonogeko) add-group |
| `e0702` | stag0304 Forest Deep | 4 | 180/240/300/420 | crown/elite variant |
| `e0709` | stag0403 City Quest Hub | 1 | 100 | first-visit intro-demo enemy (e_infermo vs e_megadra) |
| `e0417` | dng412b3 (Electro Mine) | 13 | 2, 20 | moving-rail/platform branch; rare-layout `rand%20==0`, else coin flip |
| `e0425` | dng412b4 (Electro Mine) | 24 | 2, 3, 20 | as above + station animation (`rand%3`) |
| `e0540` | quest 5-6 "rare six doors" | 1 | 4 | `g_linkPtnNum = rand%4 + SYSgetDifficulty()` → room/link pattern |
| `e0556` | dngq7b2e | 1 | 11 | adds `rand%11` to a quest counter (`COUNTERget(2)`, "questnm1") |
| `e0607` | stage-clear sequence | 1 | 7 | damage-reaction tier (`local = rand%7`: 0-3 SQ_SDMG, 4-5 SQ_MDMG, 6 SQ_LDMG) |
| `e0737` | boss02 BelialVamdemon | 3 | 3 | hit-reaction knockback ("DMGJUMP"), taken on `rand%3 == 0` |
| `e0744` | boss03 Lucemon | 2 | 2 | hit-reaction coin flips that set `g_dmgf` |
| `e0751` | boss04 Devimon-1 | 2 | 6, 4 | boss teleport position (`rand%6`, with a repeat check); UFO add spawn corner (`rand%4`) |
| `e0816`/`e0820`/`e0824`/`e0828` | lobby hub (4 entries) | 11 | 2 | `funcRandom()` in the `WPos` handler: a coin flip that steps the model's path index (`MDLaddHp(1)` or `MDLaddHp(-1)`) |

Notes:

- The **crown roll** moduli (`180/240/300/420`) are one per equipped `armor2`
  board (device folders 26/27/28/none); only the matching branch runs, so an
  area load costs **1 draw per enemy group (2–3 draws)**, which is exactly the
  `_mti 318 → 321` measurement.
- The moduli here are decoded with the signed bias of
  [the Lua numeric audit](../engine/lua-numeric-audit.md). Several draws store
  their result in a local that the decompiled `lua/` tree omits: the crown rolls
  show only their `local_0 >= N` branches, and `funcRandom` prints with an empty
  body. Read those sites from the bytecode.
- The per-entry table with every call (`entry/chunk/proto/pc/modulus`) is
  auto-generated to [`rng-sites.tsv`](rng-sites.tsv) by
  `dw4_rng.py sites --tsv`.

### The new-game path, measured

Extracting the RNG object from the curated save states on the character-creation
→ lobby → command-room → practice-stage path gives real draw counts (see
[`rng-verification.md`](rng-verification.md)):

| moment | `_mti` | twist # | draws since boot |
|---|---|---|---|
| title screen / character creation (`smoke-title`, `dw4-create-menu`) | 624 | 0 | **0** |
| intro `op-load-in` | 16 | 1 | 16 |
| intro `op-ready` | 279 | 1 | 279 |
| fresh save at the World-1 gate (before the practice-stage load) | 334 | 7 | **4078** |
| fresh save before finishing the practice stage | 266 | 9 | **5258** |

The jump from the title (0) to the World-1 gate (~4000) is **not** the big
rolls — those stages are not loaded yet. It is the hub's path draw: AFS entry
`816` (`lobby-ofanimon-seraphimon`) chunk `c100` runs
`funcRandom`, which draws `SYSgetRandom(2)`, from a model `WPos` handler, so it stamps `_mti`
**continuously while you are in the lobby**. Measured live: `_mti` 330 → 458 →
590 over 10 s of doing nothing — **~26 draws/second**, i.e. the hub position is
a function of how many frames you spend there. In the practice stage itself the
only resident draw chunk is `607/c18` (`SYSgetRandom(7)`, damage-reaction
tier), which fires when you take damage.

So after that trip the **seed is still 5150**, but the RNG has advanced by
several thousand draws (several full 624-word cycles) — the exact number
depends on real time spent in the hub.

---

## 6. Manipulation: what this buys you

Because the seed is fixed and the only mutation is a monotone counter, **the
entire run's randomness is a function of the number of `SYSgetRandom` calls
made so far**. Three practical consequences:

1. **Predict.** Read `_mti` at `0x006FF188` (plus the twist count) and you know
   exactly which outputs are coming; `dw4_rng.py seq` prints the sequence.
   A fresh boot always starts at the same place.
2. **Shift by spending draws.** Any roll can be moved to a chosen outcome by
   first consuming the right number of *other* draws. The cheapest knobs are the
   lobby `WPos` callbacks, Lucemon's hit reactions and
   re-entering an area (the crown/demo rolls). Because a savestate carries the
   RNG, you can save before a roll, spend draws, and compare — or pick the
   number of draws that gives the wanted result.
3. **Force directly.** Write `_mt[_mti]` (the word `genrand()` will temper next)
   or `_mti` itself, or the whole 624-word array, at `0x006FF18C` /
   `0x006FF188`. There is no checksum and nothing rewrites the object except
   `genrand`. Example — force the next star-aligned roll to `M-1` when
   `_mti=k`: set `_mt[k]` to a value whose temper ≡ `M-1 (mod M)`.

Caveats that keep this honest:

- Combat, boss AI, platform movement and **especially the lobby** produce draws,
  so the raw position depends on the exact route and on time: idling in the hub
  alone advances the RNG at **~26 draws/s** (measured), which is why a fresh
  boot does not hand you a fixed roll unless you reproduce the same frame
  timings. The exploit is deterministic, not *static* — count (or read `_mti`)
  from a known point.
- Loading the game's **memory-card save** does not reseed (no reseed exists), so
  the RNG just continues. Power-cycling restarts it at seed 5150. The MT state
  is not part of the 80 KB save file; a **PCSX2 savestate** does carry it.
- The reflection system registers `_mti`/`_mt` as properties of
  `igMersenneTwisterRandomNumber`, so a serialiser *could* capture the state —
  but no script or data path does, and the empirical single-sequence result
  rules out any restore in the states we have.

---

## 7. Reproducing / verifying

```sh
# locate + classify the RNG in any 32 MB EE-RAM dump or PCSX2 savestate
python3 scripts/dw4_rng.py check snapshots/*.bin

# the first outputs for seed 5150 (index, u32, and common moduli)
python3 scripts/dw4_rng.py seq 16

# regenerate the complete call-site table from the shipped NDMW.AFS
python3 scripts/dw4_rng.py sites --tsv docs/systems/rng-sites.tsv
```

Static cross-checks used here:

```sh
# the only seed constant, and the only seeding loop
mipsel-linux-gnu-objdump -d --start-address=0x1e6b20 --stop-address=0x1e6bd0 \
    orig/SLUS-20836/SLUS_208.36          # sgenrand(69069) + Reset() = 5150
grep -n "li.*5150" /tmp/dw4.dis        # one hit: 0x1e6ba4
grep -n "jal.*371f10" /tmp/dw4.dis     # one hit: the Lua stub 0x370888
grep -n -- '-24136' /tmp/dw4.dis       # 10 reads of *(0x58A1B8); only 0x371f28 uses +0x30
```

---

## 8. Open questions

_None of these block understanding or using the RNG; all are low priority and
recorded for completeness._

- Exact call frequency of the lobby `funcRandom` draws (per NPC update
  vs per frame) — measured ~26/s in the hub, but the trigger granularity is not
  pinned. Relevant to how fast `_mti` drifts while you are in the lobby.
- What caused the ~6 draws/s idle drift measured in the Goblin Pass state
  (`goblin_pass_crate_barrell`) — its only resident Lua draw chunk is
  flag-gated, so it is either a running scripted cutscene or a native periodic
  draw. Normal-play idling in `before_crown_spawn` was draw-free, so drift is
  state-dependent.
- The per-stage **group count** of crown rolls (2 vs 3) for every crown-capable
  stage, to make the per-load draw cost exact everywhere.
- Whether a route can be found where a specific desirable roll (e.g. pink
  crown, rare layout) is reachable from the fresh-boot seed within a small,
  practical number of draws.
