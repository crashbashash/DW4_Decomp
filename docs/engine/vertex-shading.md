# Vertex shading from a GS dump — the barrel's light model, recovered

A light rig fitted against **pixels** is confounded by the texture, the geometry
and whatever sits behind the object. A PCSX2 `.gs` dump removes that: it
carries the **per-vertex colour the VU1 lighting produced**, before the texture is applied, and the
pack mesh carries the normals it was computed from. Pairing the two makes the shading an exact,
camera-free linear problem.

The result for Goblin Pass's barrel (`NDMW.AFS:614`, geometry attr `35750`,
`M_BK17v1_barrelsShape`, `_vertexArray` `36087`; dump draw TEX0 `0x4007950555307ca4`) is:

    rgb8 = floor( 255 * 0.5 * clamp( ambient + diffuse * max(0, N·L), 0, 1 ) )

one-sided `max(0, N·L)`, with the live-read rig — ambient `(0.25, 0.20, 0.35)`, one directional
light `(1.20, 1.15, 1.20)` along `igLightAttr._direction = (0.3214, -0.8660, 0.3830)` (the
direction the light *travels*; `L` is its negation). The fit is `0.139/255` mean absolute on all
**84 distinct normals**, with 70 % bit-exact and the rest off by one unit; two-sided `|N·L|` gives
`27.0`, and dropping the `0.5` gives `60.4`.

## Pairing the dump to the mesh without a camera

Neither projection nor UV gives the pairing reliably:

* The barrel has only **20 distinct UV values** for 527 vertices, so `(u, v)` is ambiguous by
  construction (a hoop's ring and a stave's end share a coordinate).
* Projecting needs the exact dump camera, which is a second unknown to get wrong.

The robust key is the **primitive structure**. `igGeometryAttr1_5._stripLengths` gives the mesh's
132 strip lengths (`58×3`, `73×4`, one `61`), and the GS draws **one packet per strip, in order**:
133 `STQRGBAXYZF2` packets per barrel draw (the one long strip is the only one the GS splits, into
packets of 40 and 23 vertices overlapping by 2). So packet `p`, vertex `k` is mesh vertex
`base[p] + k`. That maps all 529 dump vertices onto all 527 mesh vertices, and the screen
positions then agree to under `0.09 px` (the GS's 12.4 fixed-point rounding).

Two facts that fall straight out of the aligned data:

* **The colour is exactly constant per normal** — standard deviation `0` on every one of the 84
  distinct normals — so the shading is a function of `N` alone and the mesh is flat-shaded by
  design. That is why 82–84 samples are enough to solve it exactly.
* The barrel is drawn **four times per frame with byte-identical vertices, ST and RGBA**. The four
  passes are coincident copies of the same state (opaque, `ABE=0`), so a renderer that draws the
  barrel once produces the same pixels; nothing is missing.

## The `127` ceiling is the GS's modulate convention

Every vertex colour the GS receives tops out at `127/255`, and the darkest is `(31, 25, 44)`, which
is exactly `0.5 × (0.25, 0.20, 0.35)`. The same floor and ceiling appear on the **world**
(`P11G00n`) and **floor** (`P11G00s`) draws, so this is a property of the shading, not of one
material or of the props.

The `0.5` is **not** a dimmed capture. The GS modulates with `(Cv * Ct) >> 7`, i.e.
`2 · Cv · Ct / 255`, so a `0.5` vertex colour times a full-brightness texel is the full-brightness
result — exactly the port's own `tex * clamp(amb + dif · max(0, N·L)) / 255`. The frames confirm it:
the dump's own embedded framebuffer (raw RGBA in the `.gs` header) and the reference screenshot
differ by only `1.17` mean absolute, and their frame means (`53.8` vs `53.9`) and floor means
(`68.3` vs `68.5`) match. A second dump captured from the same state is identical in brightness. So
the `0.5` is the GS's half-scale vertex-colour convention and a renderer uses the model at scale
`1.0` — which is what the port already does.

(Reading the `0.5` as a capture-time fade, because `127` looks too small against the
reference's `164`, is refuted as: the `2×` in the modulate is where the missing factor
lives.)

## The frame's per-draw GS state

Walking the dump's draw packets (`scripts/gs_draw_state.py`) gives the whole frame's state, and it
is uniform where it matters:

* **Every lit draw shares one rig.** The world (`TEX0 0x40060805e1312fc0`, 256×128 PSMT8, drawn as a
  7008-vertex fan plus a 3772-vertex strip), the terrain (`0x40071806213137c0`, 256×256), the barrel
  and the crate all carry per-vertex colours in **`R31..127 G25..127 B44..127`** — the barrel's own
  fit range. So the world is lit by the live rig too, and the *props use the same rig as the world*.
  No per-material rig is warranted by this data.
* **The filter is linear.** `TEX1` is `MMAG 1 MMIN 1` for every draw. It is never rewritten in the
  record stream, so an analyser that reads only `A_D` writes reports `MMAG 0` — read `TEX1` from the
  **freeze state**. This confirms the port's linear default.
* **The opaque lit draws** are `PRIM` with `TME 1 ABE 0 IIP 1`, `ALPHA A0 B1 C0 D1` (the GS's
  `(Cs−Cd)·C + Cd`), `TEST ATE 1 ATST 6` (GREATER) `AREF 0xc ZTE 1 ZTST 2`, `TEXCLUT 1`.
* **The world's enabled blend is effectively opaque.** The ground palettes (`P11G00n`, `P10G00n`,
  `P11G00s`, `TA01GM02`) are constant alpha `0x80`, which the GS treats as 1.0, so with
  `igBlendStateAttr._enabled` 1 and `_src` 4, `_dst` 5 the blend reduces to a copy. It does not explain
  the wall's colour, and the port needs no blending for this geometry.
* **The unlit overlays** (HUD, shadows, the wall's blue light dash) carry a **constant** RGBA of
  `127` (full) or `0` (black) with `ABE 1` — these are the draws a renderer must *not* shade.

The state reaches the GS **through VU1 transfers**, not through EE register writes
([`p2-renderer.md`](p2-renderer.md) finds only two GS accessors in the whole `p2` layer), so the
material → register mapping itself is VU1-microcode-side; the EE-side surface is texture upload, GS
readback, swap and lighting.

## What this means for a renderer

* The **model form** is recovered: `clamp(ambient + diffuse · max(0, N·L), 0, 1)`, one-sided, with
  `L` the negation of the light's travel direction, at scale `1.0`. The port's `shade()` is already
  this (equivalently `2 · 0.5 · clamp(...)`).
* The **constants** are the *captured* frame's. Using the dump's live rig against the reference
  screenshot scores worse than the port's baked rig (`17.66 → 18.88` on the whole frame with the
  textures correct), and a re-fit inside the one-sided form is no better than the existing fit. So
  the reference frame's constants remain a **fit**; the model is decoded, the numbers are not.
* The metal trim's residual is **not** a rig value and not the light model. It is the **texture
  orientation** — inline pack textures sampled vertically mirrored make the metal
  sample the wrong texel ([`inline-textures.md`](inline-textures.md)). With the
  orientation correct the barrel box scores `15.43` instead of `20.77` and the crate `22.58` instead of `24.93`.

## Separating shade from texel: the GS's own maps

A `.gs` dump can be rasterised back into the frame's three halves, which is what makes a per-pixel
shade claim measurable instead of inferred. `scripts/gs_shade_raster.py` depth-buffers one `TEX0`
set (the GS's own Z, `ZTST 2 GEQUAL`, so the nearer fragment wins) and writes three maps for the
same pixels: the per-vertex **RGBA** Gouraud-interpolated **affinely** at on-screen scale `Cv/128`
(the **shade**), the GS's own **VRAM texture** sampled through the GS's own **STQ** (the **texel**),
and the dump's **framebuffer** decoded out of VRAM (the **output**).

Two results, measured on the maps:

* The **texel** map reproduces the port's unlit world render essentially exactly — region ratio
  `1.000/1.000/0.999` over the whole frame, mean `|Δ|` `1.07`. The world's UV / filter / texture
  path carries no remaining error, wall included.
* The floor's **shade** is exact under the game's own per-vertex (Gouraud) path: the port's
  live-Gouraud floor shade is `224.3, 211.1, 230.0` against the map's `224.2, 214.1, 231.0` —
  ratio `1.001/0.986/0.996`, with **no** region excluded. The per-pixel path instead carries a
  `+4 %R / +7 %B` hue bias, which is why a fitted rig can out-score the decoded one on the whole
  frame even though the decoded path is the game's own.

**A barycentric trap worth recording.** The cross-product form
`w0 = ((b−a) × (P−a)) / ((b−a) × (c−a))` is the weight of the **third** vertex, not the first;
an implementation that pairs `w0` with the first vertex swaps the first and third corners and
mirrors every interpolated attribute (shade, `S`/`T`/`Q` and `Z` alike). It is invisible in a
*region mean* and shows up only as a spurious feature in the
map: on Goblin Pass it produces a bright chevron over the floor at `x 378–402, y 345–412` that the
GS's own framebuffer does not contain (`57.2, 38.9, 24.6` inside the chevron against `57.2, 38.9,
25.0` over the floor box — identical). There is no crease in the game.

## Decoding a GS dump

The front-end's PACKED vertices use descriptor `[2,1,4]` = ST, RGBAQ, XYZF2, 16 bytes per entry. RGBAQ
holds one 8-bit channel in the low byte of each 32-bit dword (R, G, B, A).

| form | layout |
| --- | --- |
| PACKED XYZF2/3 | X low-qword bits 0-15, Y bits 32-47, Z high-qword bits 4-27, F bits 36-43 |
| PACKED XYZ2/3 | as XYZF2/3, with a 32-bit Z in high-qword bits 0-31 |
| A+D entry | register address in the low byte of its second qword |
| A+D vertex write | register value: X bits 0-15, Y 16-31, Z 32-63 |

Addresses: TEX1_1 `0x14`, XYOFFSET_1 `0x18`, TEXCLUT `0x1c`, FOGCOL `0x3d`, TEXFLUSH `0x3f`, SCISSOR_1
`0x40`, TEST_1 `0x47`. In TEST, ZTE is bit 16 and ZTST bits 17-18. FRAME's FBP is in units of 8192 bytes
and FBW (bits 16-21) is width/64.

The title uses XYOFFSET (1728,1824), so screen = raw/16 minus those; SCISSOR (0,639)x(0,447); FRAME_1
`0x000a0000` (byte 0), `0x000a008c` (byte `0x118000`), `0x000401a3` (byte `0x346000`, 256 px wide); ZBUF
ZBP 280 (byte `0x230000`).

PCSX2's GS-dump replay is the authority for frame conclusions: Vulkan and software replays of a
trace-phase dump both give the blue ring on black with no bright tunnel, while a custom per-run raster
predicted a bright annulus. An ordered replay that keeps primitive boundaries and draw order agrees
closely (`scripts/gs_ordered_score.py`: MAE 1.21 against the software replay, 167.29 all-additive, 11.85
all-black) but is not pixel-exact. A dump holds several geometry sections, so score against the right
one: the runner showed one four-section dump in the order 5, 8, 11, 2, and its sidecar matches section
2.

Vulkan and software replays of the same dump agree to a mean abs diff of 0.09-0.19 of 255, but sections of
one dump need not. Geometry sections can have identical vertex positions, UVs, colours and draw state (only
FRAME_1/2 and FINISH/LABEL differ) and still replay differently in PCSX2, by a few short radial trace
segments (mean abs diff 0.12-0.25, 0.33-0.54 % of pixels). The ordered diagnostic uses one texture dump and
cannot show this. The cause is unproven; texture or palette uploads between frames are the likely one, not
checked.

## Reproducing

The offline pairer and fitter is `scripts/gs_barrel_shading.py` (workspace tooling; it reads the
pack through this repo's `scripts/igb_models.py`):

```sh
python3 scripts/gs_barrel_shading.py \
    --dump dumps/goblin_pass_frame.gs.zst --tex0 0x4007950555307ca4 \
    --afs ../local/extracted/NDMW.AFS --entry 614 --vertex-array 36087
```

It reports the census, including the live-model residual under both `max(0,N·L)` and `|N·L|`.

`scripts/gs_draw_pair.py` does the same pairing but keeps the whole vertex record, so it can also
compare the mesh's UVs against the ST the GS sampled (identity here — no texture matrix) and the
positions. `scripts/gs_shade_raster.py` writes the depth-buffered **shade** / **texel** /
**framebuffer** maps described above:

```sh
python3 scripts/gs_shade_raster.py --dump dumps/goblin_pass_ref.gs.zst \
    --tex0 0x40060805e1312fc0 --tex0 0x40063405dd30b160 --out-dir /tmp/raster
```

`scripts/gs_draw_state.py` groups a dump's draws by `(TEX0, PRIM)` and prints each
group's RGBA census and `ALPHA`/`TEST`/`TEX1`/`ZBUF`, which is what the "per-draw state" section
above is read from. The `gsdump` reader they build on (`scripts/gsdump.py`) walks the dump's packed
register cycle; its `--draws` prints each draw's TEX0/PRIM/ALPHA and `--tex` extracts the texture the
GS actually sampled out of VRAM.

The model and the before/after evidence are drawn in the port's live-camera capture set as
`barrel-shading-gs-model.png` and `inline-texture-vflip-fix.png`.

### The 2D half of the frame

The dump also carries the **2D overlays** -- the HUD and the other screen-space elements -- which the
3D scene path knows nothing about because the engine draws them straight to the GS.  They are the
draws that are **alpha-blended** (`PRIM.ABE`), **unlit** (one constant per-vertex RGBA; every lit
draw's colour varies across its vertices) and whose vertices stay inside the framebuffer; those three
properties separate them from the lit 3D draws without a texture list.  `scripts/gs_ui.py` exports
them as screen-space triangles with the GS's own UV (`STQ / Q`), each TEX0's texture decoded out of
the dump's VRAM, and the port's `--ui` replays them over the scene with the GS's `(Cs-Cd)*As+Cd`
blend and `(Ct*Cv)>>7` modulate:

```sh
python3 scripts/gs_ui.py --dump dumps/goblin_pass_ref.gs.zst --out /tmp/ui
# then, in the port:  dw4asset render <the scene> --ui /tmp/ui/ui.tsv --out-dir DIR
```

In the Goblin Pass frame that is the HUD atlas (`0x40071a05553078cc`, the ring/portrait/orb arc), the
`LV` glyphs and the HP/MP number strips: 516 draws, 2920 triangles, 8 textures, and replaying them
halves the frame's largest remaining error region.  The overlay's *content* is per-frame state, so
this is a reproduction path and not the native UI a port needs -- but it pins the 2D blend and the
screen-space mapping by measurement, which is what the UI implementation will be checked against.

### The HUD digits have no hidden per-glyph UV

The number strip's 40 triangles carry only **two distinct first-vertex UVs** (`u` 0.84375/0.9375).
That is not a missing per-digit choice: each digit cell is a **2-triangle quad** (triangle 1 starts
at the quad's first UV, triangle 2 at its second), so both UVs belong to **one glyph window** —
and the frame's displayed number *is* **99999** (the MP strips' 99), so every cell legitimately
samples glyph 9's window.  The strip textures decode as 0-9 palettes (ten glyphs per 256x16 strip,
**mirrored when read left-to-right** — the drawn digit order runs right-to-left), and the dump's
own embedded screenshot plus the live savestate screenshot both show the clean digits.

Two measured facts about the *reference*, worth knowing before trusting the HUD metric:

* The port's replay matches the native framebuffer's digit **placement** (column peaks align) and
  **ink level** (158 vs 154 G).  The dump screenshot's digits sit ~3.5 px right of the fb's and are
  brighter (185 G) — a display-path offset.
* The native fb's digit rows alternate bright (~248 G) and dim (~125 G) rows that the displayed
  image does not carry — identical in both FBP twins and byte-identically in a second dump, so a
  deterministic fb-HUD artifact a progressive render cannot and should not reproduce (drawing the
  UI twice regresses: strips 54.9 → 81.8 against the screenshot).

So the HUD box's remaining 16.4 is that artifact plus the world background error, not a glyph
defect.


## The framebuffer excess is not a global response curve

The framebuffer reader follows GS columnTable32 for the words inside a block; the
decode has the page's block map right but reads inner words row-major, which is incorrect.
4,108 address cases and actual STATUS savestate images establish this.
The framebuffer-dependent per-pixel maps/numbers below come from that row-major decode and must be
regenerated before reuse. The packet/texture evidence is independent of that decoder.

The game's framebuffer is warmer-and-bluer than `texel x Cv/128`.  One reading is that a **single
global response curve** — some shared per-channel nonlinearity — sits after the modulate.  That reading
is refuted by measurement.

Over the whole covered frame of the same-instant combat dump (pred `= Cv*texel/128` per channel, fb from that decode):

* The best global per-channel **affine** is `g = (0.591, 0.635, 0.580)`, `lift = (29.5, 23.5, 25.4)`
  with per-pixel mean `|d|` `(18.9, 16.8, 17.6)`.
* The best global **isotonic monotone LUT** through 5-wide bucket means (45-51 knots — the most
  general single curve the data allows) is no better, `(18.8, 16.6, 17.3)`.
* That one curve still leaves per-surface biases from `+12.3` (crate) to `-5.7` (floor), against
  a ~2-3 success bar.

The reason is that the relation is not a function of `pred` at all: at matched `pred` (4-wide bins,
`n >= 60`) the world and floor surfaces, which carry different textures and vertex colours, differ
by `+8.7..+22.5` (R), `+11.3..+23.6` (G), `+15.4..+27.5` (B).  And the decisive case is the crate's
dark face, which has a **constant** vertex colour `(31,25,44)` on all four vertices — so every
interpolation convention (affine or perspective-correct) yields the same `pred` — yet reads
`fb = (55.2, 45.3, 45.8)` against `pred = (26.4, 18.6, 18.2)`.  A constant colour cannot diverge
under any shared curve or interpolation rule, so the term is **per-draw**, in the combine, not a
global grade.

The origin is pinned: the dump's embedded raw screenshot **equals** the decoded
framebuffer per box to `<0.25/255` (whole means `53.77` vs `53.78`), so PCSX2's presentation applies
no transform — the excess is already in the framebuffer; and the record stream carries **zero**
IMAGE (`flg2`) packets, never writes `BITBLTBUF`/`TRXPOS`/`TRXREG`, and has no full-screen draw, so
there is no VRAM copy / BBPASS / full-screen post pass.

### The per-draw term is the GS fog stage

The per-draw combine term is **fog**.  The dump stores each packed `XYZF2` vertex as
four dwords — `X`, `Y`, `Z`, `F` (vertex bytes 32/36/40/44) — and PCSX2 extracts the fog value as
`F = (dword44 >> 4) & 0xff` (`GIFPackedRegHandlerSTQRGBAXYZF2`: `zf = (raw >> 4) &
(0x00ffffff | 0xff<<32)`).  `PRIM.FGE` is set on **99.96%** of the covered frame and `F` is nonzero
(`0..255`, median 236), so the fog blend is live:

> `fb = pred * (F/255) + FOGCOL * (1 - F/255)`,  `FOGCOL = 0xE5CCE5`

That reproduces the frame to the mean, per channel and per region:

| region | pred | fb | fog |
| --- | --- | --- | --- |
| whole | (41.6, 31.9, 24.8) | (53.8, 43.4, 39.5) | (54.4, 43.4, 38.4) |
| world (TBP `0x2fc000`) | (36.6, 34.9, 28.7) | (56.9, 52.4, 49.7) | (56.9, 52.7, 49.8) |
| wall box | (16.5, 15.2, 18.1) | (39.9, 35.7, 41.2) | (39.9, 36.0, 41.3) |
| barrel box | (52.3, 38.7, 24.2) | (66.9, 52.5, 41.6) | (67.5, 53.0, 41.8) |

Under a 5x5 blur — the regime the port's metric uses — the whole-frame mean `|d|` falls from
`(17.4, 15.2, 17.3)` to `(8.2, 7.0, 6.9)`, and the wall box reaches the ~2-3 bar (`23.5 -> 2.4`).
This also explains the crate's constant-colour dark face that motivated the "combine, not a curve"
reading: fog `F` varies per vertex, so the face diverges from `Cv*texel/128` even though its vertex
colour does not.

Reading fog as dead (`F = 0`) is an **extraction artifact**: `F = (XYZ[2] >> 24)` reads the top byte of
the 24-bit `Z` dword, which is structurally 0.  The deviation is baked into the framebuffer, not applied
by a display or post pass.

**Consequence for the renderer:** implement the GS fog stage against the per-vertex `F`; do not
implement a response curve and do not un-fit the light rig on this basis.  Two region-mean residuals
are left to chase: the floor box reads *below* `pred` (it is overlay-covered, not a clean floor
sample), and the bright character group (TBP `0x37c000`) is over-predicted.  The per-pixel scatter
around the correct mean is pred/sampler (winner-raster + bilinear) noise, not a second combine.

## Open questions

* **Whether the GS alpha test matters on the lit draws.** Unproven, from one Goblin Pass census: `ATE 1
  ATST 6 AREF 0xc` looks inert on the opaque lit draws, because the barrel, crate, world, floor-sized and
  terrain textures each read alpha 128 on every texel, so it would only bite on the unlit `ABE` overlays
  (the 32x32 HUD draw `0x40071a05553078cc` has 34.9 % of texels at alpha 12 or below). Check other stages
  before leaving the cutout out of the scene renderer.
* **The 128x128 draw `0x40063405dd30b160`.** It matched neither pack's `P11G00s` in that comparison
  (palette intact, indices scrambled), which looks like a TBW or swizzle mismatch in the extractor.
* **Whether a dump's embedded screenshot renders its own command stream during fast transitions.**
  Dumps taken around the white flash pair near-identical ring geometry with no full-screen draw against
  images of a line-art ring and a 97 % white frame, so at least one side is offset in time. Early
  trace-phase dumps are aligned; later transition dumps are unresolved.

## What didn't work

* **Crediting the rig for a better frame score.** Comparing a fitted rig with per-pixel shading against the
  live rig with Gouraud changes two things at once. A 2x2 comparison shows the gain is the per-vertex
  Gouraud path, and the fitted rig stays better or tied nearly everywhere. The fit's apparent win on the
  crate came from the resampled 640x480 reference plus the retail framebuffer's ordered dither of about
  +-4 per channel: against the native 640x448 framebuffer with a 1.2 px blur, the crate mask is rig- and
  path-independent (all four cells 18.38-18.44). At blur 0 the dither inflates every per-pixel score against
  the dither-free port render.
