# Main Lobby arrival rendering

The first arrival loads `stagml11.igb`, NDMW 820, BG02 and `camsp0101`. The renderer uses the
stage's own geometry and materials, not a frame replay.

Normal created-card Main Lobby login runs the original start/first scripts with scene-owned
actor/player movement, collision, motion/opacity publication and restoration; that contract is in
[Main Lobby movement and original startup](lobby-gameplay.md). Explicitly selected standalone
reference fixtures, such as `lobby_frame`, use the bounded first-arrival adapter described in the
[boot contract](boot-contract.md). The greeting windows are in [greeting UI](lobby-greeting-ui.md).

The measurements on this page verify the bounded arrival. They do not establish synchronized
whole-frame, full-game or all-stage parity with retail.

## Textures, lighting, materials and fog

The named world atlases are sampled in their **stored row order** by the GS STQ path.
`ML01GR00_n.png` from NDMW 821 is RGB-for-RGB identical to the texture sampled in the retail
capture. Flipping the rows selects cyan floor and blue trim texels instead of the original blue
floor and metal trim. Inline and named palettes both convert alpha with `(A+1)/2` to the GS's
0..128 range. Sampling is bilinear with repeating UVs.

For Hard lighting, the stage's original Lua chunk 009 changes the two world lights: ambient
`(0.2,0.2,0.35)`, directional diffuse `(1.1,1.1,1.1)`. Direction comes from pack 820's
`igLightAttr` at +0x491cc, `(0.2717,-0.766,-0.5826)`. Soft keeps authored ambient
`(0.5,0.5,0.55)` and diffuse `(1.2,1.2,1.08)`, and selects NDMW 822 instead of 821 for named
world atlases. The adapter applies the saved mode to both choices (see
[Hard/Soft option](#hardsoft-option)).

Lighting is one-sided Lambert per vertex. Normals are transformed with the inverse transpose, the
result is clamped before quantizing RGB to `floor(127.5*C)`, and colours are interpolated in
screen space. The GS texture modulation divides by 128. Posed actor normals come from the
animation backend. Unlit materials bypass the light rig.

`igMaterialAttr` supplies diffuse, ambient and emission. BG02's values are white diffuse/ambient
and zero emission/specular with zero shininess; it needs no specular pass. Colour, lighting
enable, blend enable/function and depth-write state inherit independently through each
geometry's ancestry. Additive glows use source-alpha/one, ordinary translucency uses
source-alpha/one-minus-source-alpha. Opaque textured RGB ignores alpha after the alpha test.
Alpha remains available for GREATER/AREF and for blending. The renderer submits opaque surfaces
before blended overlays; a depth-masked glow tests the completed depth buffer without writing it.
Frontend callers keep their own raster contract.

The stage `igFogAttr` supplies linear fog from depth **150 to 400**, colour `(0,0.1,0.25)`.
Retail FOGCOL is `0x3f1900` (RGB 0,25,63). The per-vertex factor is
`floor(255*clamp((400-z)/250))`, interpolated affinely and applied after texture modulation. Fog
enable inherits from material state; the lobby's root default is enabled.

## Hard/Soft option

The engine snapshots the confirmed `options.light` before preparing the arrival on its loading
worker. `dw4_lobby_set_light` selects the rig and named atlas pointers before publication.
Diagnostic lobbies default to Hard; `lobby_frame --soft` selects Soft. Both CPU and GPU paths use
the same recovered mode state, and changing it updates the GPU texture cache. Inline actor
textures keep their own material bindings.

The [retail recovery](../../docs/engine/light-modes.md) establishes Soft = 0, Hard = 1 and the
separate authored texture packs. The loaded shadow shader, shadow factor, lightness, blur state
and receiver projection are the same in both held retail arrivals. No mode-dependent blur is
added.

Run these commands from `port/` with a retail GS dump and screenshot of each mode:

```sh
for mode in soft hard; do
  python3 tools/verify_lobby_render.py --held-world --light "$mode" --frame 339 \
    --dump "<capture-dir>/retail-$mode.gs.zst" \
    --reference "<capture-dir>/retail-$mode.png" \
    --out "<out-dir>/compare-$mode.png" \
    --json "<out-dir>/$mode-report.json"
  python3 tools/verify_lobby_shadows.py --light "$mode" --frame 339 \
    --dump "<capture-dir>/retail-$mode.gs.zst" \
    --json "<out-dir>/$mode-shadow-report.json"
done
```

| Oracle | Soft | Hard |
| --- | --- | --- |
| Unambiguous world vertices | 12,976 | 12,776 |
| Vertex RGB within 1/255 | 100% | 100% |
| Paired texture RGB hashes exact | 100% | 100% |
| Fog exact | 100% | 100% |
| Environment image MAE /255 | 1.119 | 1.340 |
| Shadow receiver instances | 1,936 | 1,936 |
| Receiver screen maximum error (pixels) | 0.088389 | 0.088389 |

`--held-world` excludes the same actor/UI screen regions used by the environment pixel metric
(see [Environment comparison against retail](#environment-comparison-against-retail)); actor
animation clocks are not synchronized. Seam ambiguity is excluded using primitive structure, not
desired colours. Texture hashes come from the actual GS texture image independently of native
mode selection.

`test_lobby` verifies that toggling Soft changes presentation without changing the shadow map and
that toggling Hard restores the exact frame. `test_lobby_gpu` alternates modes through arrival,
greeting, portal and HUD frames for all four species, including the GPU failure fallback.
`verify_options_menu.py` boots fresh processes with each saved mode and checks a static lobby
floor pixel against the retail-verified mode colours.

## Layers and the STATUS underlay

STATUS disables BG01/BG02/BG03/GM01/GM03, while the player/weapon PC01 and actor NP01 remain
eligible. BG02 eligibility must not suppress the entire lobby draw: that hides the retained
instances beneath STATUS's translucent backdrop. `dw4_lobby_draw_layers` accepts a read-only
layer callback; the older draw entry point keeps its complete adapter draw. Environment/effect
meshes resolve authored ancestor layer names. Runtime player/weapon instances use PC01 and elves
NP01, taking precedence over library prototype names. Particle eligibility follows its authored
layer too. No draw advances simulation.

The weapon graph's PC01 switch starts hidden, so loading a valid nonempty graph does not prove
that the weapon is submitted. Native weapon preparation publishes every part branch selected by
`beWeaponInfo` through mutable switch state (see
[Paired weapon visibility](#paired-weapon-visibility)). `weapon_submitted_triangles` reports the
last draw after eligibility and clipping; appearance replacement clears that diagnostic until a
fresh draw. All seven families across four species require nonzero actual submissions during held
world tests, with atomic graph replacement and texture-cache invalidation.

Layer tests check that all-visible callbacks reproduce the complete adapter image, STATUS layer
masks retain actors/weapon, all-hidden masks suppress geometry including particles, and repeated
draws preserve presentation state. Private native underlay captures contain the three retail
actor/weapon texture hashes of the underlay, including the 64×64 weapon atlas.

## Simulation and arrival timing

Presentation samples the latest completed 60 Hz simulation tick. Repeated or skipped
presentations do not advance camera, actor, portal or fade state. Hidden instances continue
simulating. The original Lua 4 bytecode initializes its player-entry delay local to **180**, then
adds 20 for each joined player. The generator reads that initializer directly: the cleaned prose
decompiler misassigns the local. The selected player and its caster remain hidden before entry.
The screen's `BLIN60` starts after **five** ticks; the cleaned Lua's four is a signed-constant
decoding error.

The selected player's `TRNSS1` supplies `FADESET IN 50`. FADESET executes the recovered EE
arithmetic: the first update adds 1/50, subsequent updates use the 2^18-nanosecond timer delta
divided by 16,666,667, capped at three. IN retains its final overshoot internally; presentation
clamps alpha to one. Retained retail checkpoints reproduce the exact float bits, including
`0x3f8025b7` at completion. A frame/50 approximation of the fade is not the retail rule.

The entry `waitS` plays once, then `WAITS1` starts a new node clock with an eight-frame blend.
The outgoing source continues cycling during the blend. Original int64 animation durations and
quantized node clocks determine phase; the animation library's rounded float duration does not
determine the boundary. The final `SQ_WAIT` restarts the equipped idle. Retail RAM palette
comparisons cover entry, the transition and idle: ordinary posed-vertex maximum error is about
3.34e-6 units, with a maximum 1.36e-4 during the blended checkpoint.

`beActionStarterInfo x_100trnsin01` supplies three ring starts at delays **0, 6, 12**, offsets
`(0,0,0)`, `(0,5,0)`, `(0,9,0)`, and Y rotations 0°, 90°, 180°. The matching model bank supplies
IN 6, JOINT 0..42 OS, WAIT Frame 36, OUT 6, WAIT Frame 6, then hides the instance. Recovered
Action2 executes the joint and wait boundaries. The subcommand dispatcher accumulates EE frame
deltas before comparing delay, so retail jitter can shift a nominal start by a tick.

Each ring action schedules `y_100trnsin01` six frames later, with a further `(0,5,0)` offset. The
particle manager starts its timer on the following traversal. Eight authored particles per
instance use the original position, colour, size and UV polynomial coefficients, texture,
authored additive blend/alpha test and one-second lifetime. ParticleTimer uses raw world
nanoseconds; model nodes use quantized clocks. Particle RGB is rounded in the full 0..255 range
and alpha converts to GS 0..128. A retained retail particle buffer matches **32/32 colour
bytes**, with position/half-size maximum error **4.77e-7** units at its recorded clock.

The first-arrival camera keeps its own 0..240 frame clock: an independent four-second sequence,
then a hold. Its recovered update caps an individual world-clock gap at 50 ms; emulator stalls
therefore need not preserve the nominal relationship between camera frame and effect frame. No
screenshot-specific phase offset is applied to the fixed-step host.

## Background and portal animation

The stage setup pauses **MATCTRL**, whose data describes material membership and spatial
searches. That is not a reason to advance every exported animation or to freeze generated model
controllers. BG02 (111 meshes / 18 textures) has independent compressed spatial and UV sequences,
sampled from the simulation clock; see
[stage portal background animation](lobby-gameplay.md#stage-portal-commander-instances-and-walking-falls).

The four generated portal controllers have independent Action2 clocks. Their programs are decoded
from NDMW 820's `beAction2Info._dataList`; the adapter follows each `beAction2Info`'s
`_dataList`, `WAIT01`, `_comList` and `beAction2JOINTSET` to read its default/off animation
range. JOINTSET and WAITCHECK execute through the recovered Action2 host, including EE
comparisons and strict boundaries; FADESET uses the same source timer rules as the player fade.

| Model | Arrival placement | OFF / WAIT joint window (WAIT01 / OFSW01 loop) | ON window | OFF2ON | ON2OFF |
| --- | --- | --- | --- | --- | --- |
| `g_cyexit` | 155,57,55 | 10..20 | 40..60 | 30..38, IN 3, wait Joint | 70..78, OUT 8, wait Joint |
| `g_cyheal` | 115,10,-95 | 11..21 | 50..90 | 50..90 loop, IN 40, wait Frame 40 | OUT 30, wait Frame 30 |
| `g_cytelep1` | 5,27,-95 | 11..21 | 50..140 | 30..38, IN 8, wait Joint | 150..158, OUT 8, wait Joint |
| `g_cytrerp2` | 5,27,15 | 11..21 | 50..140 | 30..38, IN 8, wait Joint | 150..158, OUT 8, wait Joint |

The four models contain 17 template meshes and four named textures. Their spatial and
texture-target sequences run within those windows at 60 Hz. Main Lobby generates only the first
commander RAM branch of `g_cytrerp2`, leaving its two extra copies hidden; see
[commander-room effect instances](lobby-gameplay.md#stage-portal-commander-instances-and-walking-falls).

The adapter implements ready/off, rise, active and fall states. `SQ_POWERON` arms OFF; powered
`SQ_SWON` starts RISE, completion selects ON. `SQ_SWOF` runs FALL and returns to OFF;
`SQ_POWEROF` selects WAIT. The created-card quest gate starts powered but inactive; exit and
teleport start unpowered.

### Conditional visibility

Scene traversal checks every ancestor's authored `igSwitch` child bit and `igLod` half-open
distance interval. Switch mutations belong to the instance, even when exported templates share
one bitmask. Joining P1 enables its own body and Shadow branches. The visible body uses the
authored near LOD, whose upper boundary is 10,000; the Shadow branch selects the low skin
independently. LOD selection follows these authored intervals, not shape names. Visibility
suppresses attached weapons and casters together with their actor.

## Player starter appearance

The created-card arrival uses the first equipped starter weapon and its motion branch. None of
the four created starters uses the dual-weapon `waitD` branch.

| Species | `INI_WEAPON1` code | Stored device ID | Weapon model | Arrival/idle label and motion |
| --- | --- | --- | --- | --- |
| Agumon | `0x010a` | `0x050a` Blunt Axe | `w_common05.igb` | `slash`, `waitS` |
| Veemon | `0x010b` | `0x050b` Slash Sword | `w_common01.igb` | `slash`, `waitS` |
| Guilmon | `0x010c` | `0x050c` Stab Dagger | `w_common06.igb` | `slash`, `waitS` |
| Dorumon | `0x010d` | `0x050d` Bash Katana | `w_common07.igb` | `slash`, `waitS` |

`slash` here is a **model-controller pose branch**, not the weapon's attack skill. A Bash Katana
therefore uses `slash`/`waitS`; selecting `waitD` from the weapon's name or skill would be
incorrect. The character-select preview keeps `waitC`.

Each of the sixteen player forms (`shinka` rows 0..15) has an actor pack `m_<name>.igb` (`MODEL_NAME`
without its `p_`) in `NDMW.AFS`, a model-controller info `p_<name>` in the hub packs and a HUD portrait
range in `WAIT01..WAIT16`. The lobby needs nothing else per form but the equipped weapon asset.

### Evidence and native lookup

Read-only retail recovery traces the creation caller at `0x003e4750` through GAMERAM
`GAMEDATAINIT` and `GAMESTART`. The message dispatcher at `0x003fca10` calls `0x003f7310` to
initialize the player and `0x003f99f0` for the named creation result. Both GAMESTART paths call
`0x003f9570`, which calls `0x003f8990`. That helper reads `INI_WEAPON1`, `INI_WEAPON2`,
`INI_WEAPON3` from the species database and initializes three weapon objects through
`0x004482c0`. These calls and stores were sanity-checked with `mipsel-linux-gnu-objdump`; the
Ghidra output alone is not the evidence.

The original `usa_pack.igb` (AREA 674) contains the species and weapon databases. Its species
`beDataBase` id 1663 has a 53-column short table: the four first rows are Agumon, Veemon, Guilmon
and Dorumon; `INI_WEAPON1` is column zero. The retail player-property template at `0x004cefe4`
initializes `WEAPONRECNO` to zero before stat recalculation. Recalculation stores the first
weapon's database row there; this is not a socket index. Appearance uses the first
`POWERSOCKETNAME` entry. Its weapon database id 1427 has 256 graded rows followed by styled rows;
rows 266..269 supply the four MODEL names above. These ids document the specimen; the native
lookup identifies databases and columns by their original field names and species `MODEL_NAME`,
rather than using those ids or an asset choice table. The starter lookup supports the
created-card styled starter codes; replacing the weapon afterwards is covered by
[Equipment appearance publication](#equipment-appearance-publication).

Each selected weapon's `beWeaponSeqData` gives `SQ_WAIT` and `SQ_ENTR` the `slash` label. The
player's `SQ_WAIT` label selects `WAITS1`; that Action2 data's MOTIONSET names `waitS`. The
`SQ_ENTR` branch selects `TRNSS1`, whose MOTIONSET also names `waitS` alongside the 50-tick fade.
The loader resolves the idle motion from these pack records.

The weapon's `beWeaponInfo._nodeList` and `_boneNameList` pair its `right` attribute-set graph
with **`RArm04`**. The native renderer submits that graph's original mesh, material and inline
texture using:

```
weapon graph local transform × animated actor bone × player spawn transform
```

`RArm04` is an attachment bone without a skinning matrix index. The animation backend therefore
evaluates named skeleton bones, including non-skinning bones, using the original hierarchy/rest
translations and Enbaya tracks. It does not use the inverse-bind skin matrix to place the weapon.
Weapon alpha participates in the player's entry fade on both CPU and GPU paths.

The offline RAM inputs are two dumps from a power-on character-creation session.
Dorumon's created card at `0x0137c298` points
to a payload at `0x0138fa58`: its first folder entry (`+0x64`, payload offsets exclude the save's
eight-byte header) is `0x050d`, and its three equipment indices at `+0x2dc..+0x2e4` are 0/1/2. In
the lobby, player work `0x01227130` names `SQ_WAIT` and has `slash` label entries; Action2 work
`0x012278f8` names `WAITS1` through `+8`. The active `beWeaponAttachData` at `0x01489e50`
contains a bone select at `0x0111db78` with skeleton index **18** (Dorumon's `RArm04`). Its child
graph is the loaded `w_common07` `right` node. These are offline running-game reads.

### Validation against retail

`test_lobby` checks all four database-selected models, `slash`, `waitS`, `RArm04` and nonempty
weapon triangles. `test_actoranim` checks that each player's named hand matrix is finite and
moves, and rejects missing bones and non-finite times. The four-species CPU/GPU check covers the
body and attached weapon during the entry fade, moving camera and greeting, including CPU
fallback after a failed GPU draw.

The optional retail comparison uses the held-camera Dorumon greeting capture. Run from the
repository root:

```sh
make -C port build/lobby_frame
python3 port/tools/verify_player_appearance.py \
  --dump <capture>.gs.zst \
  --reference <capture>.png \
  --json /tmp/player-appearance.json
```

`lobby_frame` exports an RGB texture hash with each projected vertex. The check identifies the
original Dorumon body and katana textures independently in GS VRAM, pairs vertices by UV within
0.001, and measures the closest screen-space candidate at repeated UV seams. Counts include
repeated GS submissions. It reports every paired instance, including outliers.

At native diagnostic frame 339:

| Part | Retail vertex instances paired | Median error | 95th percentile | Maximum |
| --- | ---: | ---: | ---: | ---: |
| Dorumon body | 10,048 / 10,048 | 0.197 px | 1.847 px | 5.888 px |
| Bash Katana | 672 / 672 | 0.193 px | 0.525 px | 0.785 px |

The fixed player region `(280,165)..(355,240)` has RGB MAE **19.22/255** against the retained
screenshot; a build with the `waitD` body and no weapon measures 39.61 at the same native frame
and camera. The environment oracle reports the phase-dependent player colour separately: at frame
339, 6,721 matched player instances have MAE 0.246/255 and maximum channel error 6. The actor
classification uses texture identity before consulting colour; the player outliers remain in its
report.

This verifies the initial equipment/motion selection and attached rendering. The retained GS dump
is not synchronized to native skeletal phase, so the fixed player screenshot region is not a
synchronized skeletal-phase oracle.

## Equipment appearance publication

`dw4_lobby_weapon` prepares the requested database MODEL asset, its complete `beWeaponInfo`
node/bone pairs and the player's authored SQ_WAIT label/motion branch before replacing the live
appearance. Both visible and shadow player poses use that motion. Each attachment graph follows
its own named bone. Publication preserves the world, NPCs, camera and gameplay clock; preparation
failure leaves the previous graph and pose available. Obsolete textures and triangle storage are
released on success, and GPU image caches are invalidated before old backing storage is freed;
the rendering context, shader programs and framebuffer remain selected.

On the GPU path a successful swap clears uploaded texture identities without closing the
rendering context. The next draw uploads the replacement images, which prevents stale
pixel-pointer cache hits while preserving GPU selection. Context or cache-reset failure follows
the failure policy in
[GPU execution](#gpu-execution-and-remaining-performance-work).

The live appearance callback looks up socket zero by its derived name; `WEAPONRECNO` is a
database row, not an array index. Live SDL acceptance swaps the first Dorumon weapon to
`w_common04.igb` and its authored `waitG` pose through the real equipment transaction and that
callback. The windowed route verifies a changed nonempty weapon graph and two root
close/restores.

`test_lobby` exercises 21 swaps per species through all seven authored
`w_common01`–`w_common07` assets, rendering every publication, then verifies missing-asset
recovery and an unchanged world tick/control handoff. This appearance-owner check also passes
ASan/UBSan with leak detection disabled. The real-asset GPU test performs four repeated gun/sword
replacements for every species, verifies GPU retention before/after drawing and compares CPU/GPU
pixels with the lobby image tolerance. The explicit failed-draw fallback test passes. None of
this establishes retail pixel parity.

## Paired weapon visibility

The original `beWeaponInfo._nodeList` and `_boneNameList` specify separate right/left model roots
and RArm04/LArm04 attachments. NDMW 912 (`w_common02`, dual), 913 (`w_common03`, arm) and 914
(`w_common04`, gun) list two roots, which are also PC01's two children. Enabling only child zero
loads both models and bone attachments but leaves the left branch hidden.

Preparation clears PC01 and enables every branch containing an authored weapon root. This applies
to initial equipped appearance, replacement and hub return preparation. It preserves single-part
weapons and does not create a second inventory item. Each part keeps its own original geometry
and attachment bone. The read-only part diagnostics report prepared and actually submitted
triangles separately for each attachment; the total remains available.

The four-character native lobby test exercises all seven common weapon families through repeated
swaps and requires nonzero submissions from each expected hand. The headless CPU/GPU test checks
paired-gun/sword replacement for all four characters, retains the GPU and compares composed
pixels. The 640×448 GPU paired-gun capture was inspected. These checks verify native authored
attachment publication; they do not establish retail full-frame pixel parity.

## Projective shadows

The original `beShadow01Info` receiver graphs are retained outside ordinary BG02. The shader's
registered caster roots are the three visible lobby NPCs, **P01** (the player's visible graph,
including the equipped weapon hanging under it) and the player's **Shadow** low-skin copy. A live
retail read of the shader's `_shadowCasters` list (fresh Lv1 Guilmon and Lv99 save, Terminal)
shows exactly these five roots, and the shader's light is orthographic straight down
(`_lightDir` (0,-1,0), position 200 units above the player). Registering only the low skin leaves
the weapon and near-LOD body without a shadow; retail shows the weapon's streak below-left of the
player (shadow-region MAD against the retail frame 2.24 with the low skin alone, 1.08 with the
five roots). The low skin shares the player's animated pose but does not depend on the entry
material fade.

Opaque caster coverage renders into the mutable 256×256 map without repeatedly darkening
overlaps. Receiver projection uses the pack's ±100 bounds and factor 0.4, with the retail
player-centred orientation and nine-texel inset (238×238). Alpha peaks at **77**. GS bilinear
sampling filters the edge. The retained shader `0x0126e110` has **blurState=0**: no additional
blur pass applies to this scene. GPU texture caches upload changed shadow pixels each
presentation.

The independent receiver oracle pairs **1,936** retained retail instances without consulting
their UV values: UV MAE **2.48e-7**, maximum **6.43e-7**, median screen error **0.0625 px**,
maximum **0.0884 px**. This verifies projection rather than synchronized caster silhouettes; the
retained RAM and GS captures are not simultaneous.

## Clipping and GS raster arithmetic

The camera's authored **10..2000** depth interval clips both near and far planes before
perspective division. Triangles crossing the near plane are clipped, not discarded whole.
Viewport clipping preserves affine XY, STQ, depth, fog and colour; XY truncates to the GS
1/16-pixel grid. GS triangle samples are at **integer pixel positions**, with integer top-left
edge coverage; half-pixel coverage is not the GS rule. The GPU offsets these vertices by half a
pixel to map them to GL sample centres. Frontend submissions keep their own convention.

GS bilinear fractions have four bits, with truncation after each axis. Texture modulation divides
by 128 and truncates; fog uses its /256 signed integer rule; CPU alpha blending applies the
signed integer GS expression. Depth truncates. These rules are separate from the frontend's
legacy floating-point sampler.

## Environment comparison against retail

Run from the repository root:

```sh
make -C port build/lobby_frame
port/build/lobby_frame ../local/extracted 339 /tmp/lobby.png /tmp/lobby-vertices.tsv
python3 port/tools/verify_lobby_render.py \
  --dump <capture>.gs.zst \
  --reference <capture>.png \
  --out /tmp/lobby-comparison.png --json /tmp/lobby-report.json
```

The capture and game assets are private local inputs; the GS comparison is optional because the
captures are not redistributed. Other hosts can supply `--roms`, `--dump` and `--reference`. Use
the native 640x448 GS screenshot, not a scaled desktop screenshot. `lobby_frame` takes an
explicit frame number, runs the arrival choreography without dismissing messages, suppresses the
UI for the render comparison and exports projected vertices, UVs, colours, depth, fog,
blend/depth-write state and an RGB texture hash per vertex. It accepts any camera frame for other
captures.

On the retained held-camera first greeting:

| Check | Result |
| --- | --- |
| Fixed environment image region, RGB MAE /255 | **1.2044** |
| Unambiguous vertex fog | **24,372 byte-exact instances** |
| Environment vertex colour | **16,013 instances; MAE 0.1266/255; 99.9001% within one level** |

Counts include repeated submissions in the GS dump. Matching uses position within 0.25 pixels and
UV within 0.001. Colour-ambiguous seam instances are excluded before consulting retail RGB, and
candidates with conflicting fog values are excluded before consulting retail F. The check does
not fit lighting or fog to the screenshot. The environment metric uses rows 0..279, excluding the
actor rectangles (190,150)..(390,280) and (575,180)..(640,280); the message window is checked
separately in [greeting UI](lobby-greeting-ui.md). The comparison image also includes an unmasked
difference panel, so actor, UI, shadow and remaining geometry/raster differences remain visible.
Actor colour populations and whole-frame differences are reported separately and are not treated
as proof of a matched retail frame.

## GPU execution and remaining performance work

Windowed boot enables the lobby's GLES3 layer backend by default, following its title/menu
policy. `--software` keeps the CPU oracle; headless runs opt in with `--gl`.
`dw4_lobby_enable_gpu` creates a lobby-owned context shared by the world and greeting UI.
Immutable textures are cached in GPU memory, consecutive triangles with matching material state
are batched, and fragment sampling, modulation, fog, alpha/depth testing and blending execute on
the GPU. The context is destroyed before the textures it caches.

The GPU lobby also owns a persistent 256x256 caster target in addition to its visible-frame
renderer. Shadow coverage, red-to-alpha conversion, the fog-colour clear and the final screen
fade execute on the GPU. Registered caster roots, original projection/factor, submitted geometry
and simulation clocks are the same as on the CPU path. Mutable shadow images are uploaded to the
receiving world texture cache. The shader pixel transforms match the CPU equations byte-for-byte
in `check-gl-post`.

Normal hardware policy stops on clear/draw/transform/cache failures without CPU fallback. In
explicit reference mode a setup or draw failure regenerates the complete CPU shadow and visible
frame, and a failed draw leaves the input framebuffer untouched. The live route guards every
lobby draw against CPU audit calls. The policy and the front-end and host presentation paths are
in [GPU rendering](gpu-rendering.md#gpu-offscreen-and-pixel-composites).

This is an offscreen backend. Camera/node evaluation, skeletal posing, world/view transforms,
vertex lighting, near-plane clipping and submission construction execute on the CPU. Each world
and visible UI pass uploads the CPU framebuffer and synchronously reads its result back. The
window then uploads that framebuffer again for presentation. The GPU path therefore reduces
rasterisation cost without establishing the final scene/presentation architecture.

### CPU/GPU frame comparison

Reproduce frame comparisons and warm draw timings from the repository root:

```sh
make -C port build/test_lobby_gpu
mkdir -p /tmp/lobby-gpu
port/build/test_lobby_gpu ../local/extracted /tmp/lobby-gpu 1280 960 60
```

The optional arguments are output directory, width, height and sample count. The check compares
all four player assets at frames 24, 63, 180, 350 and 600, including the entry fade, moving
camera, portals and greeting. It checks identical world submissions independently of texture
allocation addresses, image differences against the CPU oracle, and exact CPU fallback after
forcing a GPU draw failure. `make check` includes this check at 640x448. Image tolerances allow
RGB MAE at most 1/255 and at most 1% of pixels differing by more than four levels in any channel;
these are CPU/GPU raster checks, not a retail-fidelity acceptance threshold. GPU fixed-function
blending can round a channel differently from GS integer blending; the tolerances stay at these
values.

Across the four species and five frames, RGB MAE stays below 0.024/255 and fewer than 0.002% of
pixels differ by more than four levels in any channel. Forced draw failure restores the CPU frame
byte-for-byte.

### Hub service windows on the GPU backend

`tools/hubtest.h` `draw_frame` renders each drawn hub frame on the CPU oracle and again on the
lobby's GLES3 backend (`gpu_compare`), with the same tolerances (RGB MAE at most 1/255, at most
1% of pixels off by more than four levels). Run headless, `check-hubtalk`, `check-hubbank`,
`check-hublabo`, `check-hubdisk`, `check-hubcnos` and `check-hubshops` compare 29 frames covering
the XDATA stat and chip lists and quotes, bank editor and item list, labo, disk, appraiser, and
the WPU/APU/chip/junk shops; all pass on a hardware GPU (offscreen EGL). Without a GPU context
the comparison is skipped and the test says so. The capture-gated tests are given
`build/hub-captures` by the Makefile so these frames are drawn in `make check`. This verifies
raster agreement of the service windows, not retail fidelity, and not the windowed Vulkan
swapchain present (`--vulkan`).

### Windowed Vulkan present

A surface can offer more than the 32 formats `vk_pick_format` reads, so the second
`vkGetPhysicalDeviceSurfaceFormatsKHR` answers `VK_INCOMPLETE`. `VK_INCOMPLETE` is accepted;
treating it as a failure produces "vulkan: unavailable, falling back to SDL". The swapchain
failure points report their reason. A bounded windowed run
(`build/dw4 --roms ../../local/extracted --vulkan --skip-logos --mute` under `timeout`) creates a
1280x960, four-image swapchain (format 37, R8G8B8A8 UNORM) and presents with no fallback or
errors, with or without a third-party Vulkan implicit layer installed (a layer that fails to load
only produces loader messages).

### Draw timings

Timings exclude loading, simulation tick, window presentation and frame pacing. They include
pose/submission preparation, world/UI rendering and synchronous readback, use five warm-up draws,
and report mean, p50, p95 and maximum. A separate prepared-world replay measures GPU
submission/rasterisation and upload/readback without CPU scene/vertex preparation or the UI. Run
benchmarks without competing builds or analysis tasks.

A desktop run on a hardware GPU with the default `-O2` build, species 0 and 120 warm samples
starting after held-camera frame 600, with the first greeting visible:

| Output | CPU mean / p95 | GPU mean / p95 | Prepared GPU world replay mean |
| --- | --- | --- | --- |
| 640x448 | 13.97 / 14.53 ms | 7.65 / 8.11 ms | 0.89 ms |
| 1280x960 | 33.41 / 35.40 ms | 10.94 / 11.71 ms | 2.19 ms |

These are sequential runs with the normal desktop session active. They are draw-cost
measurements, not achieved display FPS or a controlled hardware acceptance test, and desktop
results do not establish Steam Deck acceptance. A warm 640x448 benchmark that includes the GPU
shadow and fade passes is recorded in
[GPU rendering](gpu-rendering.md#gpu-offscreen-and-pixel-composites).

### Remaining performance work

In this order:

1. Keep the world and UI in one GPU render target through presentation. Remove the world/UI
   framebuffer round trips; retain explicit readback for diagnostics. This requires integrating
   context/resource ownership with the window backend.
2. Upload static stage vertex/index buffers once and submit per-mesh transforms and material
   state. Move vertex transforms, inverse-transpose normal lighting, fog-factor generation and
   clipping to shaders while preserving GS affine colour/fog interpolation, STQ texture sampling
   and quantisation. Preserve the diagnostic CPU vertex exporter and compare matched arrival
   frames.
3. Evaluate actor bone matrices on the CPU and upload palettes for GPU skinning. Retain the
   recovered blend/palette mapping and normal handling; verify all four players and both Digi-Elf
   models before extending gameplay coverage.
4. Measure preparation, GPU execution, transfer and presentation separately, including spikes, on
   desktop and physical Steam Deck before setting budgets for multi-player gameplay.

## Hub instances and window rendering

The isolated [hub runtime](hub-travel.md) prepares Terminal/Central/Shop world models by authored
instance node and Action2 animation database, with independent RAM-slot transforms, pose caches
and eligible collision/NEAR bindings. Draws copy node state and do not tick controllers or
consume RNG. Shared greeting windows remain in `lobbyui`, while a prepared WN view supplies travel
models/selectors. During STATUS a full WN roster and original text overlay replace that split
view. The original fade geometry samples JOINTSET colour as well as FADESET opacity; the legacy
final whole-frame multiplier is omitted when this WN view is present, because otherwise half-dim
travel sequences black out the confirmation window. Normal created-card boot admits the split
travel view while keeping its STATUS renderer; transferred scenes use the generic runtime.
Standalone fixtures keep their own path. Native confirmation/STATUS captures were inspected.

### Action-less UI panels

The single-player bottom panel `i_stpnl06` (slot 4) is generated into an empty `SQ_WAIT`; scripts
only send `SQ_OPEN`/`SQ_CLOSE` around dialogue and menus. With no `ACTION` running its nodes keep
their authored pose. `dw4_modelctrl_time` reports zero until an Action2 action has started,
instead of the raw clock. Clamping the embedded animations to their end in the generic WN view
draws an extra upper line and the `»`/`«` chevron meshes (`polySurfaceShape16/17`) that retail
frames do not show. `check-hubtalk` asserts the idle panel's node time is zero while a running
NPC action advances. Evidence is the sequence data, first.lua and two retail frames; there is no
instruction trace of the retail draw path, so this is unconfirmed.

`dw4_modelview_open` skips the five `i_stpnl00..04` controller instances; the lobby HUD, which
`lobbyui` draws from the real records, is their single owner. Drawing them in the hub's generic
WN modelview stacks a placeholder HUD (empty ring, zero-padded digits, a second dark band) under
the lobby HUD. This was checked visually against a retail frame (clean `170`/`60`/`1` digits,
lighter band), not by a pixel diff, and has no automated assertion.

## Lobby HUD

The HUD publishes the species, authored panels, level, HP/MP numbers and meters. Its behaviour
while an NPC message is open is in
[HUD and label during NPC messages](lobby-gameplay.md#hud-and-label-during-npc-messages).

### No player-name line

Retail does not display a player-name line at the bottom left, so the HUD does not accept a name:
a reconstructed row drawn with MINIMUM glyphs at an explicit `(110,387)` anchor is not retail
behaviour. The character name remains in session/player records and the original STATUS text
owners. `test_lobbyui` checks all four species' actual HUD submissions for absence of the glyph
atlas, together with the portrait, numeric UV, meter and health-publication checks. Normal boot
with either Cross or Circle dialogue prompts covers the same HUD.

Native/retail checks that use a virtual pad set `SDL_GAMECONTROLLER_IGNORE_DEVICES` for a
connected physical pad, which otherwise interferes with the virtual-pad disconnect check. The
setting is local to tests, not a persisted game/controller configuration.

### MP dots

HUD items keep scene order, with the portrait last. The greeting windows keep their transform-Z
sort. In `i_stpnl03` the `mpmetr01..10` transforms carry Z −135 while their `mpparts` vertices
sit at 0. Every other HUD item has transform Z 0 and keeps its depth in its vertices, for example
the lit HP ring at −135 and its dark base `hpmetrwk0Shape2` at −127. Retail draws the dots over
the sockets, which matches both scene order (the sockets come first) and the depth used by the HP
ring (−135 over −127). Sorting HUD items by transform world Z moves the lit dots ahead of
`hpmetrwk0Shape2`, whose −127 socket ring then blends over them: the dots render dark purple
(about 0.45 of the `mpparts` texel `(156,24,231)`) where retail shows them at full texture
brightness.

`test_lobbyui` counts lit-dot pixels for each of the four starters. A full gauge must have at
least 100 bright pink pixels (the transform-Z order produces 1), and an empty gauge must have
none. Native renders at 40/80 MP light the lower half of the dots and leave the upper sockets
dark. At 0 MP every dot is dark.

### Five-digit numbers

A native HUD with level 99 and 99999/99999 was compared with retail max-stat captures. After
scaling to the same 640×480, the HP, MP and LV digit masks align within ±1 pixel (mask overlap
0.89, 0.76 and 0.83). `test_lobbyui` checks that 99/99999/99999 shows the same digit (9) in every
HP/MP place and leaves only the third level place blank. Level 999 fills all three places; it is
checked only against the authored 3-place `lvnm1` geometry.

### Portrait tiles of the evolved forms

The portrait window's `WAIT01..WAIT16` ranges are not in shinka row order. Each
evolved form's retail arrival HUD (after a Digi-Lab evolution of a controlled card character) was
matched to its atlas tile: shinka rows 4..15 show tiles 8, 7, 9, 4, 6, 5, 15, 10, 11, 14, 12, 13
(zero-based; rows 0..3 are the starters in order). `lobbyui.c` applies that table; `test_lobbyui`
draws all sixteen portraits and requires them to differ.

## Automated checks

`make -C port check` includes focused opaque/alpha/additive/depth-mask/coloured-fog checks and
verifies that all four player assets enter the textured lobby. It covers all four species, entry
delay, fades, rings and particles, portal transitions, authored switch/LOD boundaries, hidden
casters, repeated presentation, both triangle windings, shared edges, extreme clipping and
preserved interpolants. CPU/GPU checks include the moving camera, entry/blend, active/falling
portals, mutable shadows and exact software fallback after GPU failure, within the image
tolerances given under [CPU/GPU frame comparison](#cpugpu-frame-comparison).

The frontend initializes every triangle's optional renderer state before submission. Without that
initialization the lobby flags read arbitrary heap bytes and regress the blue trace and menu
background. With it, all 350 boot/menu frames are byte-for-byte those of the renderer without the
lobby state. `verify_frontend.py` also compares trace, flash, title and menu frames under two
allocation-poison patterns to catch that dependency without pinning the frontend to a fixed
reference image.

The optional live presentation, live-memory and supplied live-pose/live-fog checks are skipped
when their private inputs are absent.

## Open items

- Synchronized whole-frame comparison with retail: full-frame bit identity is not established,
  and broader synchronized retail captures, including other species' synchronized frame
  comparisons, are missing.
- Geometry/pose/pixel pairing of the STATUS underlay against retail.
- Saved-equipment appearance on arrival: imported equipment and inventory restoration are not
  covered by the starter lookup.
- Retail pixel parity of replaced and paired weapons.
- Exact retail UI composition and broader material parity of the hub windows.
- An instruction trace of the retail draw path for the action-less `i_stpnl06` panel, and an
  automated assertion for the skipped `i_stpnl00..04` instances.
- A retail capture of level 999 for the HUD digits.
- The GPU steps under
  [Remaining performance work](#remaining-performance-work), including Steam Deck measurements.
