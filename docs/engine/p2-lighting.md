# `p2lighting`: what the EE packs for the VU1 light programs

`p2lighting` (`0x001fb710`, 980 bytes) is the one lighting function in the `p2` backend that
**builds the constant block the LIGHT microcode reads**. It is named in its own trace string (the
pointer `0x004e5150` is passed to the logger at `0x0020dfd0`); this
page is the static decode of its body and of the runtime state it reads.

Every source the function reads is a runtime global in the EE's bss, and the per-light descriptors
are built by the scene-load hooks around `0x00170ed0`/`0x001709d0`. The record stream is fully
recovered. The packs carry serialised `igLightAttr` records, but those are prototypes, not the running
**parameters**; see *Light records in the packs* and *What is not recovered*.

## The call chain

| function | size | role |
| --- | --- | --- |
| `FUN_001fb0e0` | 900 | the **program selector**: tests the capability bits of the current VU1 program record, chooses a lit or unlit path |
| `p2lighting` `0x001fb710` | 980 | the **lit** path: emits the light constant block and returns the advanced cursor |
| `p2WriteDirectionalLights` | 660 | the **unlit** path: writes the first four directional lights' directions as x, y and z rows, plus three rows of half vectors toward a viewer on +z when specular lighting is on (also used from `FUN_001fbaf0`) |
| `FUN_001fbaf0` | 484 | the tail `p2lighting` calls when the `0x56AFAE` mode is on; appends a 48-byte block and an optional 16-byte record |
| `FUN_001f9430` | 6684 | the per-frame light updater (calls `FUN_001fb0e0`); also the ambient accumulation in `0x1f9f20` |
| `FUN_001f8b50` | 2260 | the light-state refresh: fills the index tables `0x56AF30`/`0x56AF38`, the count `0x56AF94` and the enable flags from the pointer table `0x56AF40` |
| `FUN_001f8490` | 660 | initialises the light-type → program-index table at `0x56AE50` (`0,1,…,10,12,13,20,…,127`) |
| `p2SetLight` / `p2SetMaterial` | 108 / 108 | store a light into `p2Lights` (`0x56AF40`) or the material into `p2Materials` (`0x56AF60`) at a caller-supplied slot |
| `p2SetLightingColor` | 60 | copies a 16-byte colour (the visual context passes its material's `+0x58` vector) into `0x56AEE0`, the block `p2lighting` emits as record 3 |
| `p2EnableLight` / `p2DisableLight` | 156 / 156 | switch a slot's light on or off, keeping the active-light counts; disabling also empties the slot |
| `p2EnableLighting` / `p2DisableLighting` | 72 / 100 | the lighting case of the renderer's enable switch `FUN_001e7930`; disabling also drops the normal-array bits from the vertex-array mask |
| `p2InitLighting` | 148 | empties the light and material slots and turns lighting off (called from the renderer's initialisation) |
| `p2InvertMatrix` / `p2AdjointMatrix` | 96 / 640 | the light-matrix inverse `p2lighting` uses: the adjoint scaled by one over the value `p2AdjointMatrix` returns |

`FUN_001fb0e0` reads the current program record's flags through `0x562C70 + 4*(*(0x569330))` (the
runtime program table, the same flags decoded in [VU1 microcode](vu1-microcode.md)) and branches on four bits: `0x1000`
(texgen), `0x100000` (scale), `0x200000`, and the mode global `0x56AED0` (1 or 5). It then copies
the program's 48-byte record into the transfer descriptor's cursor, appends either `p2lighting`'s
block (lit) or `p2WriteDirectionalLights`'s (unlit), and hands the cursor on. That is the whole "lighting" step:
`p2lighting` never touches a register, it only writes a constant buffer.

## The record stream

`p2lighting(out, flag)` returns the advanced `out`. The cursor advances in 16-byte records, in this
order:

| # | bytes | source | condition |
| --- | --- | --- | --- |
| 0 | 16 | `{state[48..59] (vec3), lightCount}` | always; the ambient pass accumulates into it |
| 1 | 16 | `state[0..15]` | always |
| 2 | 16 | `state[16..31]` | always |
| 3 | 16 | `0x56AEE0` (set by `p2SetLightingColor`) | always |
| A | 16 | `{L[0x50..0x5b] (vec3), state[64]}` | per light, only when `flag == 0` |
| B | 16 | `L[0x70..0x7f]`, or the same vector transformed by the light matrix and divided by `w` with `.w = 1.0` | per light |
| C | 16 | `L[0x10..0x1f]` | per light, only when `flag == 0` |
| D | 16 | `L[0x20..0x2f]`, with `.w` replaced by `L[0x54]` when `flag != 0` (unchanged `L[0x2c]` when `flag == 0`) | per light, always |

`state` is `p2Materials[0]` (`*(void **)0x56AF60`), the visual context's current material: ambient
at `+0`, diffuse `+16`, specular `+32`, emission `+48`, shininess `+64`, flags `+68`, its slot at `+80`
(the layout `Gap__Gfx__igPsx2VisualContext__vfunc_112` fills from an `igMaterialAttr`). So record 0
carries the emission, records 1 and 2 the ambient and diffuse colours, and record A's `w` the
shininess. `L` is the light descriptor for this iteration:
`idx = ((uint8_t *)0x56AF38)[i]`, `L = ((void **)0x56AF40)[idx]`; a NULL `L` is skipped. The loop
runs `i = 0 .. lightCount-1`, where **`lightCount = *(int *)0x56AF94`** and is also the fourth word
of record 0. Before the loop, when `*(uint8_t *)0x56AFAE` is on and `(texgen == 0 || mode51)`:

```
for i in 0 .. *(int*)0x56AF00 - 1:
    L = ((void**)0x56AF40)[ ((uint8_t*)0x56AF30)[i] ]
    if L: record0.xyz += L[0x10..0x1c].xyz * state[0..].xyz      /* MMI vmulaw/vmadd */
```

so record 0 is `state[48]` plus a weighted sum of the lights' `+0x10` vectors. The light **matrix**
is `0x56AFD0` (a 4×4, identity in every state observed); when it is needed (`scale == 0 && bit21 &&
count != 0`) `p2lighting` calls `p2InvertMatrix(0x56AFD0, sp+160)` to invert it, and uses the inverse to
homogeneous-transform `L[0x70]` (divide by `w`, then normalize through `0x0020e060`). The divisor
`p2AdjointMatrix` returns is `m[0]·adj[0] − m[1]·adj[4] + m[2]·adj[8] − m[3]·adj[12]`, which is the
determinant only when `m[1]·adj[4] + m[3]·adj[12] = 0` (for instance when `m[1]` and `m[3]` are zero,
as in the identity). When the matrix is not needed, record B is the plain `L[0x70]`. Finally, if
`0x56AFAE` is set, it calls `FUN_001fbaf0(&cursor, mode51)` to append the unlit tail.

### What the records are, semantically

The names of the LIGHT programs and the object model agree on the vocabulary: `AMBIENT`,
`DIRECTIONAL` (infinite), `POSITIONAL`/`LOCAL`, `SPOTLIGHT`, `LINEAR_ATT`, `_SPEC`/`_NOSPEC`, and the
per-material multipass suffixes. `igLightAttr` is the serialised light
(reflection, `data/reflection.json`), and its declared layout is the semantic key:

```
+0x0c _lightType      +0x10 _lightId      +0x14 _position (vec3)
+0x20 _ambient (v4)   +0x30 _diffuse(v4)  +0x40 _specular (v4)
+0x50 _direction(v3)  +0x5c _falloff      +0x60 _cutoff
+0x64 _attenuation(v3)+0x70 _shininess    +0x74 _cachedPosition (vec3)
```

Three of the emitted records land on those offsets: record C on `+0x10` (`_lightId` + `_position`),
record D on `+0x20` (`_ambient`), record B on `+0x70` (`_shininess` + `_cachedPosition`), and
`p2WriteDirectionalLights` reads the descriptor at `+0x60..0x68` (the serialised `_cutoff`/`_attenuation` slots)
as a **direction**.

That last point is the honest limit of the mapping: **the runtime descriptor is not the serialised
`igLightAttr`.** Its array stride is **160 bytes** (`0x00a0`, `Gap__Gfx__igPsx2VisualContext__vfunc_79`), it has no `igObject`
vtable at `+0` and no reflection record, and its fields carry measured roles rather than declared
names:

| offset | measured role |
| --- | --- |
| `+0x10` | 4 words, accumulated by the ambient pass and emitted as record C |
| `+0x20` | 4 words, emitted as record D; `+0x2c` is the "no-flag" `w` |
| `+0x40..0x48` | vec3 copied from the scene source (`Gap__Gfx__igPsx2VisualContext__vfunc_90`) |
| `+0x50` | an index (used by `FUN_001f72330`) and `+0x54` a `w` for record D |
| `+0x60..0x68` | a **normalised direction** (`Gap__Gfx__igPsx2VisualContext__vfunc_90` negates the source, transforms and normalises) |
| `+0x6c` | capability/flag word (`& 8` clears a bit and marks the state dirty) |
| `+0x70` | 4 words: the light position for the matrix path / record B |
| `+0x84`, `+0x90`, `+0x94`, `+0x98` | `w`, registration index, enabled bool, direction mode (0 or 2) |

So the *stream* is recovered to the byte, and the *field roles* are recovered from how the code uses
them; the running *values* are not.

## Light records in the packs

Packs carry serialised `igLightAttr` records (fields `_lightType` +0xc, `_ambient` +0x20, `_diffuse` +0x30,
`_specular` +0x40, `_direction` +0x50, `_falloff` +0x5c, `_cutoff` +0x60, `_attenuation` +0x64), decoded offline by
`scripts/pack_lights.py`:

| pack | ambient | directional | spot |
| --- | --- | --- | --- |
| common packs (179, 187, 195, 203, 210, 218 and others) | (0.4, 0.4, 0.45) | diffuse/specular (0.8, 0.8, 1.1) along (0.2424, -0.8192, -0.5198) | white at (0, 90, 0), 30 degree cone |
| stage pack `NDMW.AFS:614` | (0.5, 0.5, 0.55) | diffuse (1.3, 1.3, 1.17) along (0.3214, -0.866, 0.383) | the same; it does not reach the Goblin Pass arena |

The `0x56AF40`/`0x56AF94` globals read empty at a frame boundary, and the live rig's colours differ from these records,
so the records are prototypes, not the running values.

## The runtime globals

| address | name | type | role |
| --- | --- | --- | --- |
| `0x56AF00` | `p2DirectionalLightCount` | int | count of the directional-light table (`0x56AF30`) |
| `0x56AF30` | `p2DirectionalLights` | u8[8] | slots of the active type-0 lights, at most four; the ambient pass and `p2WriteDirectionalLights` read them |
| `0x56AF38` | | u8[8] | slots of the active type-1 and type-2 lights (the per-light pass) |
| `0x56AF40` | `p2Lights` | void*[8] | the light in each slot |
| `0x56AF60` | `p2Materials` | void*[2] | the material in each slot; slot 0 is `p2lighting`'s `state` |
| `0x56AEF0` / `0x56AEF8` | `p2ActiveLightCount` / `p2ActivePointLightCount` | int | lights switched on, and those of type 1 |
| `0x56AF94` | | int | **the light count**: the loop bound and record 0's `w` |
| `0x56AF9C` | `p2LightSpecular` | int | enables the three half-vector rows (`+0x30/+0x40/+0x50`) in the unlit path |
| `0x56AFA0/…/A8` | | int | per-class light counts (`FUN_001f8b50`) |
| `0x56AFAC`…`B0` | | bool | mode flags; `0x56AFAE` gates the ambient pass and the `FUN_001fbaf0` tail |
| `0x56AFD0` | `p2LightMatrix` | mat4 | the **light matrix** (identity in every state observed) |
| `0x56AEE0` | `p2LightingColor` | 16 B | the colour emitted as record 3 (`p2SetLightingColor`) |
| `0x56AED0` | `p2LightingMode` | int | lighting mode 1/5 (`p2SetLightingMode`) |
| `0x56AE50` | | u8[?] | light-type → program-index table (`FUN_001f8490`) |
| `0x554BC0` | `p2LightingEnabled` | bool | lighting on (`p2EnableLighting`) |
| `0x554BC4` | `p2LightsNeedTransform` | bool | set by `FUN_001f9430`; the unlit path then rotates the lights (object-space programs) or raises `p2LightCalcPending` |
| `0x491270` | `p2LightsChanged` | int | any light, material or mode changed; the refresh rebuilds the tables |

Measured from an offline RAM dump (stag0102 loaded): `0x56AF00 = 2`,
`0x56AF94 = 0`, `0x56AF60 = 0x006e9820`, `0x56AFD0` is the identity, and `0x56AF40` is **all NULL**.
The same is true of **every** saved state (17 checked): the per-light pointer table is populated only
during the render pass and is empty in a savestate taken outside it.

## The VU1 rotates the light block in place

A lit draw's colour depends on **how many hardware matrix uploads came since the EE last sent the light block**, not only on the
light and the normal. Recovered from the asm, a retail savestate (stag0001 practice stage) and a retail GS dump (confirmed for the
stag0001 values; the generalisation and the event model are unconfirmed):

1. **Eye-space light, once per light apply.** `igLightAttr::apply` (`0x0013eb10`) calls `Gap__Gfx__igPsx2VisualContext__vfunc_90`, which stores descriptor `+0x60 =
   normalise(-src_dir x getMatrix(1))`, the source direction times the model-view top. The `igLightAttr` itself keeps its authored
   `_direction`; nothing on the EE accumulates. In the practice stage the descriptor reads `(0, 0.98499, 0.17261)` while the attribute
   still holds `(0.3214, -0.866, 0.383)`.
2. **Upload.** `FUN_001fb0e0` -> `p2WriteDirectionalLights` writes the raw `+0x60` vectors transposed as three quadwords (x row, y row, z row for
   four lights) in a VIF UNPACK to VU1 address `0x5a`.
3. **Pending flag.** `FUN_001fbce0` is the single hardware matrix upload (type 0 model-view, 3 projection, 4 texture, 5, 2); every
   type leaves through `0x1fc010..0x1fc018` with `p2LightCalcPending` (`0x56B5F8`) `= 1`. Only the model-view type also calls `FUN_001fb0e0(-1)`, which
   re-emits a **fresh** light block (returning early when `p2DirtyFlags & 4`, the lighting-dirty bit, is set).
4. **Draw submit.** `FUN_001ee750` (clones `p2SubmitVertices`, `p2SubmitIndexedVertices`, `FUN_001fe390`) tests `p2LightCalcPending == 1`; if set it appends
   a 32-byte record (VIF `6001002b`, one word `DAT_0056b604` = `0x3a` to VU1 `mem[43]`), clears `DAT_0056afc8` and the flag. The flag
   is a boolean consumed by the next draw: two uploads before one draw count once.
5. **VU1.** `EXECUTE_RENDERLIST` reads `mem[43]`, zeroes it and jumps to `0x3a` (the `EXECUTE_PRE_PATH` chain that runs the `CALC_*`
   programs). `CALC_INFINITE_4` (ucode `+65904`, 160 B) loads the matrix rows from `mem[0..2]` and the light rows from `mem[mem[75].z]`,
   computes `l <- M3x3 * l` and **stores it back over the same rows**. `CALC_NORMAL_MATRIX` writes a separate cofactor matrix, so
   only the lights accumulate. (`mem[75].z = 0x5a` is inferred from the UNPACK address and the numbers; the savestate's VU1 memory
   holds a different buffer half and was not read at that address.)

So after a fresh upload `l0 = -L x V` (eye space); the first `CALC` turns it into the object-space light `-L` (the usual, correct
result, k = 0), and every further `CALC` without a re-upload multiplies by `V^T` again: `l_k = -L (V^T)^k`. Folded into the world
normal, a draw seen k extra times lights with `n_eff = n_world . (V3 . R)^k` (row-vector form, `V3` the view's
upper-left 3x3, `R` the node's world 3x3), `ndl = max(0, -L_world . n_eff)`, ambient and diffuse unchanged.

**What stag0001 shows** (BG02 floor, depth-first draw order 2174, 2176, 2179, 2180, 2184, 2186, 2189, 2191): the retail packet stream
has the flag record before the first BG02 draw (fresh block), before node 2184 (texture matrix of transform 2183, k = 1), before 2186
(transform 2185, k = 2) and before 2189 (the restore to identity on leaving the texture-matrix scope, k = 3), and none before 2176,
2179, 2180 (k stays 0) or 2191 (k stays 3). With the retail floats `ndl` is 0.4181, 0.0354 and 0.0545, i.e. vertex colours
(95/96, 86/87, 108/109), (37, 30, 50) and (40, 33, 52/53) against the dump's (96,87,109), (37,30,50), (40,33,53). The rule has no
free parameter; the 1-count residuals are quantiser rounding.

**The rule.** Per `BG02` root, depth first,
a boolean `pending`, a `fresh` bit and a counter; root start and the enter and leave of a target-0 `igTransform` set pending and
fresh, a target-9 (texture) `igTransform` and a texture-matrix scope (`igTextureMatrixStateAttr`) set pending; at a mesh, if pending
then `k = fresh ? 0 : k + 1` and pending clears.

**Other stages.** No stage beyond the
practice stage with stag0001's BG02 overlay pattern has been found.

**Not established (unconfirmed):** a second retail dump with k > 0 (the three practice-stage dumps are the only constant dim additive draws in
about 1,300 parsed dumps; the Main Lobby frames contain no lit k > 0 mesh, so they neither confirm nor contradict the hub half);
which events re-emit a fresh block in the draw-begin path `FUN_001f9430` (`p2DirtyFlags` bit 2 and the lighting-dirty state); whether
leaving a texture-matrix transform uploads on its own (the stream shows only the entry uploads plus one restore on leaving the scope);
the `sel`/object-space program variants (`p2WriteDirectionalLights` transforms the lights on the EE there), the `p2lighting` path and positional
or spot lights; a rotating or scaled ancestor, where `(V3 . R)^k` is an extrapolation; and a hidden switch branch (a draw skipped
skips its upload).

## What is not recovered

* **The running light values.** They are written into the runtime descriptors from the scene at
  load/update time; the pack records are prototypes whose colours differ from the live rig, the
  savestates are empty of them, and VU1 data memory is too dense in float patterns to identify them by shape. What is needed is
  a breakpoint/readback **while the light list is non-empty** (`p2SetLight`/`p2SetMaterial` fill
  `0x56AF40`/`0x56AF60`), or a `--statefile` taken mid-render.
* **The runtime descriptor's class.** It is a 160-byte bss structure, not the reflected
  `igLightAttr`; the reflection layout is used only as the semantic vocabulary.
* **The VU1 arithmetic** (beyond `CALC_INFINITE_4`'s in-place light rotation, decoded above). The programs are the specification (LIGHT 91 programs, 82 % of the
  pipeline); this page records what the EE *hands them*, not what they compute.

## Reproducing the static decode

```sh
mipsel-linux-gnu-objdump -d --start-address=0x001fb710 --stop-address=0x001fbae4 game.elf   # p2lighting
mipsel-linux-gnu-objdump -d --start-address=0x001fb0e0 --stop-address=0x001fb470 game.elf   # selector
mipsel-linux-gnu-objdump -d --start-address=0x001f8b50 --stop-address=0x001f9430 game.elf   # state refresh
```

## What didn't work

Two routes to the light parameter values fail.

* **A savestate.** `0x56AF40` is all NULL and the count `0x56AF94` is 0 in all 17 saved states, because the list is
  populated only during the render pass.
* **Scanning class directories for a name containing `Light`.** This finds nothing and wrongly suggests the parameters are
  not on the disc. The source objects are `igLightAttr` records in the common packs, which `scripts/pack_lights.py`
  decodes offline.
