# Live Game State (BSS globals)

All addresses are in the ELF's BSS (`0x00554b00`–`0x0058d280`) and are stable.

## The Game singleton (`0x0058a1b8` …)
`Gap__Bec__be__vfunc_23` is the constructor. It allocates sub-objects with
`0x236f80(allocator, typeinfo)` and stores the pointers in adjacent globals:

| Global | Type | Meaning | Class typeinfo |
| --- | --- | --- | --- |
| `0x0058a1b8` | ptr | object #1 | `0x00587d08` |
| `0x0058a1c0` | ptr | **main game / GAMERAM object** (property root) — the instance it points at is a `Gap::Bec::beMessenger` (its `+0` vtable is `0x0053ab70`) | `0x00588f38` |
| `0x0058a1c8` | ptr | object #3 | `0x00589160` |
| `0x0058a1d0` | ptr | object #4 | `0x00589790` |
| `0x0058a1d8` | ptr | the Game `this` pointer | — |

Disassembly:
```
371a44: lw    a0,12(a0)          ; allocator
371a4c: lw    a1,32008(at)       ; class 0x00587d08
371a48: jal   0x236f80
371a54: sw    v0,-24136(at)      ; *(0x0058a1b8)
...
371a6c: sw    v0,-24128(at)      ; *(0x0058a1c0) = main object
...
371a84: sw    v0,-24120(at)      ; *(0x0058a1c8)
371a9c: sw    s0,-24104(at)      ; *(0x0058a1d8) = this
371aa4: sw    v0,-24112(at)      ; *(0x0058a1d0)
```

## The "MDL" block (`0x0058a1e0` … `0x0058a220`)
"MDL" = the currently-focused **Digimon model/entity** (usually the player's
character). The block mixes one object pointer with cached scalar fields read by
the `MDL*`/`BLT*`/`BLP*` script functions.

| Address | Type | Field | Evidence (function) |
| --- | --- | --- | --- |
| `0x0058a1e0` | ptr | MDL model-entity object (deref `+40`) | `MDLisSeqName` (`lw s0,-24096(at)`) |
| `0x0058a1e4` | u32 | MDL **RamNo** | `MDLgetRamNo` (0x00373b20) |
| `0x0058a1e8` | ptr | **MDL transform** (position!) | `MDLgetPosStr/RotStr/KyoriSquare` |
| `0x0058a1ec` | u32 | MDL **max HP** | `MDLgetMHp` (0x00373d00) |
| `0x0058a1f0` | u32 | MDL **current HP** | `MDLgetHp` (0x00373d10); `MDLaddHp` r/w |
| `0x0058a1f4` | u32 | MDL **RecNo** | `MDLgetRecNo` (0x003742d0) |
| `0x0058a1f8` | u32 | MDL **InfoName** | `MDLgetInfoName` (0x00373b30) |
| `0x0058a1fc` | u32 | MDL **BulletKind** | `MDLgetBulletKind` (0x00373e80) |
| `0x0058a200` | u32 | MDL **BulletBoxNo** | `MDLgetBulletBoxNo` (0x00373ee0) |
| `0x0058a204` | u32 | BLP status field | `BLPgetDamageValue`, `BLPgetStunTime` |
| `0x0058a208` | u32 | BLT/BLP status field | many BLT/BLP; read by `BLTcalcEXPUp` as arg |
| `0x0058a20c` | u32 | BLP status field | `BLPisHitCheck` etc. |
| `0x0058a210` | u8 | MDL **DMGTurn** flag | `MDLsetDMGTurn` (`sb v1,-24048(at)`) |
| `0x0058a214` | ptr | MDL call-name object ptr | `MDLisCallName` (loaded as `a0`) |
| `0x0058a218` | u32 | world-pos target | `MDLsetWorldPosTarget` (0x003741d0/0x00374200) |
| `0x0058a220` | u32 | TXT call number | `TXTgetCallNo` (0x003747f0) |

### Direct-read examples
```asm
; MDLgetMHp  (0x00373d00)
373d00: lui at,0x59
373d08: lw  v0,-24084(at)     ; v0 = *(0x0058a1ec)  -> max HP

; MDLgetHp   (0x00373d10)
373d14: lw  v0,-24080(at)     ; v0 = *(0x0058a1f0)  -> HP

; MDLaddHp   (0x00373d20)
373d24: lw  v1,-24080(at)     ; load HP
373d28: addu v1,v1,a0         ; + arg
373d30: sw  v1,-24080(at)     ; store HP
```

### **There is no direct MP or EXP global.**
Only HP/max-HP live in the MDL block. MP/EXP/LEVEL/NINZU live in the GAMERAM
property system (`docs/engine/property-system.md`).

> **The MP field.** MP is a property *field*, not a
> global: the player status container at `0x8803E4` holds 24-byte records
> `[hdr][def_ptr][value u32][pad][flags][handler]` and each def record embeds the field name,
> so `def 0x69A4E4` = `"MP"` and its live value is **`0x88041C`** (HP `0x8803EC`, MMP
> `0x880434` in the same array). The records run in the order `EXP`, `ISUSE`, `HP`, `MHP`, `MP`,
> `MMP`, `TSUYOSA`, `MAMORI`, `LUCKRITSU`, `ATTACKZOKUSEI`. These values are live and writable:
> with `TSUYOSA` and its copies set to 1 the player's attacks did no damage. A second copy of the
> numbers sits in a `VList` data array just before the records (11 entries in the measured save),
> with further copies elsewhere in the heap, so change every copy when testing a stat.
> Two mirrors of MP sit at `0x1227730`/`0x1227734`.
> **The container address is save-dependent** (LV-999 saves: MP `0x88041C`; level-1 save: MP
> `0x87E3A4`, container moved -0x2044) — locate it per save by scanning for the MP def pointer
> `u32 == 0x69A4E4`, whose value is at `hit+4`. A Heal Circle refill
> moves all of them (60 -> 99999), and a pnach pinning them at 9999 keeps the VM there while
> R1 techniques still cast against the field (HUD showed `9999 - 960 = 9039` after `Heal Lt`,
> whose 960 MP the save's real 60 MP could not have paid).

## Position (world coordinates)
`PLAYERgetPos` (0x003744a0) routes through the object-method system:
```
3744b0: lw    a0,-24128(at)      ; a0 = main_obj
3744bc: jal   0x38e670           ; invoke(main_obj, "PLAYERPOINT", "GETGENERATEPOS")
3744cc: jal   0x38f320           ; read result slot: *(*(*(obj+16)+20)+16+0*4)
```
But the **concrete transform** is at `*(0x0058a1e8)`. `0x190a30` extracts the
position:
```asm
190a30: lwc1 f0,48(a0)   ; x
190a34: swc1 f0,0(a1)
190a38: lwc1 f0,52(a0)   ; y
190a40: lwc1 f0,56(a0)   ; z
```
→ **x = `*(f32*)(transform+48)`, y = `+52`, z = `+56`**; 3×3 rotation at
`+0..+40`. Used by `MDLgetPosStr`, `MDLgetRotStr`, `MDLgetKyoriSquare`
(squared distance).

> **Reading works, writing does not teleport.** `transform+48`
> is the 4th row of a 4×4 matrix at `transform+0x00` (rotation in rows 1–3, the
> translation in the row starting at `+0x30`/`0x01173158` for the 1P object). It is a
> **placement record**, not the live position, in two measurable ways:
>
> * it does **not track walking** — after 2 s of movement input that visibly moves the
>   character, `transform+48/52/56` is unchanged, to the bit. It **is** rewritten on a
>   *placement* event, though (a knockdown/knockback re-place moved it from
>   `(120.74, 62.54, 327.63)` to `(147.85, 56.48, 325.24)` across one interval in a live
>   test), which is why it can look like it tracks;
> * writing it **does not move the character on screen**. Writes round-trip and persist
>   (nothing else rewrites the field), and were tested at three targets, one of them a
>   spot with no scenery of the kind on screen, so the unchanged view is conclusive.
>
> It does read correctly **immediately after a stage load** (it is set when the
> character is placed), which is why it is usable as "the player position" right
> after a load — read it early, and treat it as where the character was *placed*.
> The value the movement systems use is the scene node's translation row (below). Writes to
> this field *can* wedge the character: after writing it, movement input produced no
> change at all until the save state was reloaded.
>
> The stage's **entry-point table** (the `PLAYERPOINT`/`SETGENERATEPOS` targets) is a
> flat array of 12-byte xyz triples at `0x00dca7d4` in `stag0101` — e.g.
> `(417.01, 72.02, −106.22)`, `(417.18, 72.00, −119.96)`, `(427.45, 72.00, −117.33)`,
> `(402.37, 53.53, −10.06)`. Those are the positions the game itself teleports to.

### The live player position

The player's model owner is `o = *(*(0x56df40)+0x84)`; the scene node (a `beModelCtrlNode2`) is `*(o+0xe0)`
and the player info object is `*(o+0xe4)`. This path does not depend on the message-argument object, which is
populated only intermittently. It is not available in the Terminal gate-menu state.

The authoritative world position is the translation row at node+0x50. Four other copies exist: AI data +0x70
in a `beModelCtrlAIData`, a `beBaseInfoRamList` record, the message-argument matrix and a `beCopyModelCtrl2`.

`*(*(*(0x58a1c0)+0x10)+0xc0)+0x30` is the world position (x, y, z, 1.0) of the model the engine is currently
processing; the middle object is a `beMessengerArgData`. It follows the player under free control in Central
and the Terminal, but it is not a registry lookup: in a scripted stage with no message context (`stag0001`)
the object is null.

Player facing lives in `beNDMWMdlPlayerInfoWork`: yaw in radians at +0x84 (0 faces +z, positive towards +x)
and the last applied yaw, normalised to 0..2pi, at +0x9c. When the two differ the engine re-derives the node's
rotation rows (right = (cos, 0, -sin), forward = (sin, 0, cos), 4x4 row-major from node+0x20) and updates
+0x9c. Writing both with equal values is ignored, and writing only the node rows is unreliable.

### Teleporting: write the scene node

Writing the translation row at node+0x50 propagates to all the copies and moves the character on screen with
stick control intact. Writes to the AI data, message matrix or render copy are reverted by the engine, and a
write to the base-info record stays isolated. Writing the `*(0x0058a1e8)` matrix does nothing. To turn the
player, write yaw at +0x84 with a different value from +0x9c.

**One limit:** teleporting to a point whose *section* is not loaded makes the game try
to stream it and can hang the load (observed: a 300-unit jump put up the area-loading
tip and stayed there). Teleport inside the loaded section, walk across a boundary, then
teleport again; otherwise reload the state.

### Locating position copies in RAM

Where the owner path is not available, the position can still be located through its heap copies: in
`stag0101` it is repeated in ~8 identical 12-byte xyz triples, plus a 4-corner collision footprint (16 triples
in total). Read them; write the scene node.

They are not discoverable by value: `pine find` returns "no
match" for u32 values that provably exist (it missed a float read back from a known
address even with `--start/--end` around it), so scan a RAM window in Python instead —
or use the differential method:

1. pause the game and read 16 MB at `0x800000` (≈60 s),
2. **walk the character one step in an OPEN direction** (into a wall gives zero
   candidates — this is the trap),
3. pause and read the window again, so the diff is exact,
4. keep the triples that moved, and among them those sharing the *dominant
   displacement* — that set is the player's copies.

Ignore the static program image (the ELF loads at `0x100000..0x554b00`; it never changes as the world moves)
and keep only translation rows (x, y, z, 1.0): unfiltered three-float diffs are dominated by rotation-matrix
rows of unit vectors.

Addresses are stable across reloads of the **same savestate** — but not across different
states, and not even across two states of the same stage: the allocator decides.
`pre-leomon` and `normal_lvl1_before_crown_enemy` share **no** copy
address, and a `stag0102` calibration was dead in a later
`stag0102` load (its first slot held `nan`). So a set of addresses is per-*state*, and a
stale one points at other objects. **Never hard-code or reuse
these across loads.** To avoid hunting each time, derive them from a stable route: read
the placement record at `*(0x0058a1e8)+48` (accurate right after a load) and keep every
copy of that triple in RAM — no walking, ~2 min; the walk-based differential
is the fallback for when the record has gone stale. `stag0101`'s set (found by this
method):
`0x0111ee50 0x012fecc0 0x01383e50 0x0165135c 0x01651368 0x016b9720 0x016de1c0 0x017bdf10`,
with a footprint at `0x017c25e8`/`0x017c2648`/`0x017c26a8`/`0x017c2708` (±3 units).

## Story-flag table

The retail story-flag table is a 1,024-byte array of 0/1 bytes in the heap, indexed by flag id:
`t = *(*(*(0x5875e0)+0xdc)+0x10)`. The table address differs between states (`0x7deef8`, `0x86b228`,
`0x880a10`, `0x7e66e8` seen) but the chain holds. Flag 1 is 0 on a fresh save and 1 on progressed saves; flag
25 goes from 0 to 1 at the Data Keeper's first conversation.

## Pointer-chain cheat sheet (for dynamic testing)
| Want | Expression |
| --- | --- |
| Main game object | `*(0x0058a1c0)` |
| Player struct *i* | `*( *( *(main+16) + 40 ) + 16 + i*4 )` |
| Result slot *i* | `*( *( *(main+16) + 20 ) + 16 + i*4 )` |
| Current HP | `*(u32*)0x0058a1f0` |
| Max HP | `*(u32*)0x0058a1ec` |
| Current model transform | `*(0x0058a1e8)` |
| Model placement position | `f32 @ transform+48/+52/+56` |
| MDL entity object | `*(0x0058a1e0)` |
| Player model owner `o` | `*( *(0x56df40) + 0x84 )` |
| Player scene node | `*(o+0xe0)` |
| Player live position | `f32 @ node+0x50` (x, y, z) |
| Player info object | `*(o+0xe4)` |
| Processed model position | `*(*(*(0x58a1c0)+0x10)+0xc0)+0x30` |
| Story-flag table | `*(*(*(0x5875e0)+0xdc)+0x10)` |

## Hot engine globals (not game state)
Very-high-reference-count BSS words — engine/runtime, not gameplay:
| Global | Refs | Likely |
| --- | --- | --- |
| `0x00586dc8` | 1151 | engine/allocator |
| `0x00586f20` | 2146 | engine (most-referenced global) |
| `0x00587040` | 580 | engine |
| `0x00587110` | 537 | engine |

## Combat display-number tables
Floating combat popups (damage / exp / heal / bit) use text-sequence name tables
at `0x004c8770`–`0x004c87f8`:
- damage: `i_dmgnum`, `dmgnm0`, `SQ_DMGNM01..05`
- exp:    `i_expnum`, `expnm0`, `SQ_EXPNM01..04`
- heal:   `i_healnum`, `healnm0`, `SQ_HEALNM01..05`
- bit:    `i_bitnum`, `bitnum0`, `SQ_BITNM01..04`
- player damage: `i_pcdmgnum`, `dmgnm1`

`MDLdspExp` (0x00374140) → `0x373ef0` indexes these tables (stride 28) and calls
the `GAMERAM` object method to display the number.

## Open questions

- Unproven: the table at `0x21000` looks like a model display list, a hash map from RamNo to pointer with
  chained 0x10-byte entries `{key, value, 0, 0}`.
- Unproven: the MDL block may not be usable as a player handle. Idle reads of `*(0x0058a1e8)` alternated between
  two entities from sample to sample (`0x012cba38` 28 times, `0x0125a408` 12 times in 40 samples), and
  `0x0058a1f0`/`0x0058a1ec` read 3/100 while the HUD showed HP 170. Check which entity the block holds before
  reading player values from it.

## What didn't work

- **Writing the HUD's HP.** The HP shown on the HUD is a display copy. In one measured state it sat at
  `0x013F2FBC`, with a second copy at `0x013F2FB8` tracking it each frame. Writing either only fakes the
  number: the fake survives until something refreshes the stat block, and using an HP Disk α then rewrites it
  from the real HP (real HP rose by 450 per disk). Neither address is the real or the maximum HP; use the
  status container above.
