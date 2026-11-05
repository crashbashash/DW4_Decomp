# GPU rendering in normal play

Normal native-port play performs no CPU rasterization or pixel compositing, including offscreen
render targets, in the implemented native entry points. The agreed
[specification](technical-spec.md#agreed-gpu-rendering-requirement) reserves CPU rendering for
explicitly selected diagnostic/reference runs. CPU simulation, asset decoding and preparation of
draw submissions remain ordinary host work. Framebuffer upload, readback and byte copies are
transfers, not shader work; removing those transfers is a separate performance optimization.

Boot, windowed stage inspection and standalone windowed movies select the hardware-required
policy. `--software` and explicit headless/reference use remain independent diagnostic paths.
SDL's dummy video driver is an explicitly selected no-display test transport; its results are not
hardware-presentation evidence. Physical-display tests separately cover accelerated SDL and
Vulkan swapchains.

## Paths and owners

Source paths are relative to `port/`.

| Path | Execution in normal play | Owner |
| --- | --- | --- |
| Startup cards | GPU clear/draw; complete normal card sequence and movie handoff validated on hardware SDL and Vulkan. | `src/frontend.c`, `present_boot_cards` |
| Loading card and error text | Normal loading clear/artwork and fallback/error labels use GPU clear and batched font draws. | `src/engine.c`, `draw_loading`; `src/frontui.c` |
| Front-end primitive overlays | Normal title flashes/fades and panel/cursor primitives use ordered GPU batches. | `src/engine.c`, `ui_quad`, `ui_tri` |
| Character portrait | Persistent viewport renderer clears/rasterizes on GPU and composites using an integer GPU blit; explicit reference mode keeps the CPU oracle. | `src/frontchr.c`, `chr_actor` |
| Lobby shadows | Persistent 256-square GPU target handles caster rasterization, clear and alpha conversion. | `src/lobby.c`, `dw4_lobby_draw_layers` |
| Lobby fade | GPU pixel transform applies the original RGB truncation and preserves alpha. | `src/lobby.c`, `dw4_lobby_draw_layers` |
| Legacy text and FPS | Batched GPU legacy glyphs and GPU bitmap/FPS plates cover boot, movie and stage entry points. | `src/fefont.c`, `src/render.c` |
| Background fills | Normal title requires its essential graph assets and uses GPU black clear/backdrop. Placeholder CPU gradients are reference-only. | `src/engine.c`, background helpers |
| Framebuffer clears | Normal boot/card/loading/offscreen and stage render targets use GPU clears. | `src/render.c`, framebuffer callers |
| GPU-error fallbacks | Normal entry points fail explicitly; only selected diagnostic/reference paths may use CPU fallback. | `src/gl_layer.c`, `src/frontlayer.c`, `src/frontchr.c`, `src/lobby.c` |
| Software GL drivers | Normal boot/stage/movie policy rejects software/unsupported GLES labels; explicit reference mode accepts them. | `src/gl_render.c`, `src/gl_layer.c` |
| Host presentation | Normal SDL requires acceleration and validates GL renderer metadata; normal Vulkan rejects CPU/unknown device types. Explicit headless/dummy display diagnostics remain separate. | `src/window.c`, `src/vk_present.c` |
| Stage viewer | Normal windowed stage inspection automatically uses GPU mesh/FPS rendering, with no silent CPU fallback. | `src/engine.c`, stage rendering |

STATUS owns a persistent GPU renderer. Startup and loading-card GPU owners are enabled in normal
boot.

## Hardware and error policy

`gpupolicy.c` supplies the scoped required/diagnostic mode, case-insensitive renderer
classification, first-error retention and five CPU audit counters (UI, layer, mesh, fill,
composite). Normal boot selects the hardware-required policy before window/startup work, probes
and validates a GLES context before starting presentation, and retains the first GPU error
through frame completion. Rejected drivers fail explicitly and use the normal resource cleanup
path. Layer/mesh initialization rejects known software or unsupported renderer labels in that
mode. Recognized AMD/Radeon, Intel and NVIDIA/Nouveau labels are accepted, with known software
labels checked first. Unknown/virtual labels require backend validation.

The CPU kernel/composite counters are an enforcement gate: hardware-required mode rejects a CPU
call before writing pixels and preserves the first error. The audit counts CPU depth-buffer
clears as well as colour fills. The common UI, title-trail, character-background and lobby
GPU-error branches do not select CPU fallback in normal boot. Explicit software/headless
reference runs keep the original CPU oracle and fallback behaviour. Use
`DW4_GPU_POLICY_TRACE=1` for the per-session counters. They are printed before policy
restoration; library reference mode remains isolated.

`dw4_gl_layer_clear` supplies GPU RGBA/depth clears with context restoration and unchanged host
output on failure. Tests cover exact RGBA bytes, including transparent and alpha-128 targets.

Normal SDL initialization does not choose its software renderer when hardware acceleration
fails, and rejects an explicitly forced software renderer. GL-based SDL rendering additionally
checks hardware renderer metadata. Normal Vulkan selects discrete/integrated device types only.
Dummy/headless test presentation is explicitly labelled.

`check-gpu-policy` covers controlled family/negative labels, actual GLES context behaviour, real
backend failures and CPU-call rejection without writes; CPU reference mode is restored
independently. A hardware context with a deliberately mismatched framebuffer rejects the draw;
the UI bridge retains its GPU owner, leaves image bytes unchanged and records no CPU UI call.
Forced `LIBGL_ALWAYS_SOFTWARE=1` selects llvmpipe: normal mode rejects it, and a subsequent
explicit reference context still opens. The normal boot command with forced llvmpipe exits with a
driver error and all CPU counters zero. The host test uses a real hardware GPU, not simulated
hardware metadata.

The live GPU route passes three cycles, ten keyboard events, weapon swap and FOLDER owners on a
one-tick input route. Its fixture initializes each synthetic `SDL_Event` with `SDL_zero` and
explicit press/release state: an uninitialized union keeps a nonzero repeat byte, which the
consumer correctly ignores, and the route then fails its third keyboard/FOLDER checkpoint. This
is a fixture rule, not native input behaviour.

Logs are workspace `scratch/gpu-policy-{clean-build,software-backend,
software-boot,hardware-boot,material,reference-boot,live-fixed,input}.log`. The failing
uninitialized-event routes and their focused reproducer are in `gpu-policy-live.log`,
`gpu-policy-live-1280.log`, `gpu-policy-input-trace.log` and `gpu-input-probe{,-zero}.log`.

## GPU offscreen and pixel composites

`gl_layer.c` provides GPU pixel transforms and conventional RGBA image blits. The fade pass
computes `floor(RGB*factor)` and preserves alpha. The shadow pass converts caster red to
black/alpha using the original factor and rounding. The portrait blit uses integer
`(src*alpha + dst*(255-alpha) + 127)/255`, with the original opacity-to-alpha rounding, clipping
and covered-pixel alpha behaviour. Separate input textures avoid framebuffer feedback.
Upload/readback and row copies remain transfers; the pixel arithmetic runs in shaders. The
caller's EGL/SDL context is restored and rejected inputs leave the host framebuffer unchanged.

`test_gl_post` verifies 160 fade/shadow cases across all 256 byte values and 40 conventional RGBA
blits, including transparent/partly opaque source pixels, clipped negative origins, opacity
zero/one and nonuniform row orientation. All output bytes match the CPU equations. The
material/mask/depth checks pass alongside.

The lobby owns a separate persistent 256x256 shadow renderer. Caster coverage, alpha conversion,
main fog-colour clear, world/HUD and final fade use GPU passes. Required-mode failures stop
explicitly; diagnostic failures regenerate both shadow and visible frame through the original CPU
path, and the exact whole-frame diagnostic fallback check passes. A required-mode failed clear
records no CPU kernel/composite calls. All four species, entry/portal phases and repeated weapon
swaps keep unchanged submission bytes and the image tolerances (mean <1, fewer than 1% differing
by >4/channel). The lobby side is described in
[lobby rendering](lobby-rendering.md#gpu-execution-and-remaining-performance-work).

Character previews own a persistent portrait renderer, resized with the viewport. Their
transparent clear, original prepared mesh rasterization and opacity blit use GPU passes. The CPU
branch remains the selected reference oracle. The menu CPU/GPU comparisons keep their tolerances
and require zero CPU audit calls during every hardware menu draw, including outgoing species and
options redraws. GPU character/title paths perform no CPU depth clears.

The three-cycle live GPU lobby route passes with a per-draw zero-CPU guard. No
simulation/controller clock is changed by these passes.

At 640x448 the retained warm lobby benchmark measures CPU mean 24.294 ms versus GPU 10.974 ms,
including scene/pose work and readback, not presentation, on a desktop hardware GPU; this is not
a Steam Deck guarantee.

Evidence is workspace `scratch/gpu-{post,blit}-build.log`,
`gpu-shadow-{lobby-final,lobby-cpu,cpu,live}.log`,
`gpu-offscreen-{api-final,menus-final,menus-1280,material,live-final,
reference-boot}.log` and `gpu-portrait-cpu.log`.

## GPU mesh, main clears and text/FPS

`glcontext.h` supplies the shared EGL/SDL context save/activate/restore seam. Mesh construction,
split-frame begin/end/abort and teardown preserve the caller's context and leave the
process-shared EGL display alive. Readback storage and VAO belong to each renderer; there is no
process-static readback buffer. Failed frames restore context and preserve the host image. Normal
GPU readback also avoids writing an unused software depth buffer. Custom clear colours preserve
the title's black composition.

Mesh shaders honour Gouraud mode: vertex lighting is quantized like the CPU reference, then
interpolated affinely in screen space despite differing clip W. Per-pixel lighting remains
separately selectable. Uniform precision is explicit in both stages, and inactive specular fields
are not applied. `test_gl_mesh` verifies nested mesh/layer contexts, different target sizes, peer
destruction, invalid-frame recovery and custom clears. Its variable-depth Gouraud comparison
matches 1,391 interior CPU pixels with maximum channel delta zero.

Normal boot uses a GPU mesh owner for the original title backdrop, a frame-sized GPU owner for
main/loading clears and primitive batches, and a single GPU batch for each legacy font string.
Normal card clears use the card's own GPU owner. Missing essential title graphs stop explicitly
instead of selecting the CPU placeholder. Reference runs keep their original CPU paths. Actor,
script, input and simulation clock behaviour is the same on both paths.

`dw4_render_fps_gpu` uploads an immutable bitmap-font asset and draws its ordered
shadow/foreground quads on GPU. Its background plate uses the original integer percent-dimming
equation in a pixel shader, preserving alpha. Six FPS values match the CPU bitmap/plate output
byte-for-byte; transform/blit tests pass. The real legacy-font test verifies equal glyph counts,
visible output and zero CPU calls at four scales, while reporting image differences
diagnostically.

`check-title-mesh-gpu` compares all 300 title opening/flash/UI frames against the CPU reference
under the established mean <=1 and <=1% >4/channel allowances. The maximum mean is 0.4975/255 and
maximum outlier fraction 0.343%; no allowance is relaxed. Its GPU route reports all five CPU counters zero. The comparison
is CPU reference composition, not retail pixel parity.

The complete live SDL route reports `0/0/0/0/0` (UI/layer/mesh/fill/composite), with and without
FPS, through three STATUS cycles, a weapon swap, keyboard/focus/input gates and the four FOLDER
owners. These routes use SDL dummy presentation for automation and bypass startup FMV/cards; zero
counters for a tested route do not prove other paths GPU-only, which is why startup cards,
movies, stage rendering and SDL/Vulkan presentation have their own gate in the
[normal-path audit](#normal-path-audit).

Logs are workspace
`scratch/gpu-title-{api-final,kernels-final,composition-check,live,live-fps,
reference-boot,font-check,fps}.log`, `gpu-mesh-render-regression.log` and
`gpu-mesh-gouraud-check.log`. The title pair and diagnostic JSON are under
`scratch/gpu-title-{native,reference}/` and `gpu-title-final-comparison.json`.

## RGBA8 byte recovery before GS truncation

`texelFetch` returns normalized RGBA8 floats; multiplying by 255 can fall just below the source
byte, so a following GS floor reduces that byte by one. In `test_gl_layer`'s original
GS-raster/depth sample this produces CPU red 240 and llvmpipe GPU red 239 with the correct texel
selected. Changing the interpolation base does not fix it.

The layer shader reconstructs fetched RGBA8 channels with `floor(sample*255+0.5)` before the
filtering/modulation/alpha arithmetic. This recovers the input bytes; the GS arithmetic still
truncates at its original boundaries. Tolerances, vertex interpolation, draw order, material
batching, depth rule, CPU oracle and normal GPU-selection policy are unaffected.

An independent census renders all 256 values in each RGB channel, sampling texel centres across a
quad extending outside the viewport to avoid testing UV or coverage boundaries. Every output RGB
byte equals its original source byte on both CPU and GPU (768 exact channel checks). The GS UI
bridge's depth/filter/colour-mask checks also pass, including the 240-vs-239 case. A shader
without the reconstruction fails the census while the two-byte material allowance reports max
delta 1 for it; the reconstructing shader passes at delta 0. The allowance is kept, and the
census adds exact source-byte assertions.

A hardware GPU passes the exact RGBA8 byte census, full layer/UI contract and GPU post checks.
Normal STATUS drawing and forced failure, hardware SDL/Vulkan startup/movie/stage entries,
software-backend rejection and the 300-frame composed title route pass with zero CPU drawing.
Main-menu 1280×960 hardware fixtures also pass their retail submission comparisons with zero CPU
graphics calls. Original title integration matches 3,497 retail ticks. Under llvmpipe, selected
explicitly as a diagnostic reference backend, the census, `test_gl_layer`, the menu CPU/GL
comparisons and the GPU post tests pass, while
`verify_host.py` fails its hardware GL context requirement and the live `check-status-gpu` route
rejects llvmpipe before submitting any GPU passes; an llvmpipe run is not hardware-required
acceptance. No matching-recovery source is involved.

Private logs are `texel-byte-*.log`, `closure-hardware.log` and `terminal-native-retail.log` in
repository-relative `../scratch/main-menu-fidelity/`. This validates normal graphics execution
and scoped retail geometry, not complete-game or whole-frame retail parity.

## Normal-path audit

| Objective requirement | Proof |
| --- | --- |
| Front-end/loading/HUD/text/FPS GPU execution | Normal GPU owners, clears, batches, integer FPS plate and character-close `keep/30` shader; three-cycle live route with FPS reports all five CPU counters zero. |
| Offscreen and scene raster/compositing | GPU portrait, shadow/caster, alpha conversion, world clear and fades; per-draw zero-CPU guards, unchanged submitted data, four-species tests and image allowances pass. |
| Movie and stage entry points | `check-gpu-entries` runs automatic-GPU stage rendering on SDL/Vulkan, complete startup cards followed by six presented/skipped movie frames, and standalone movie FPS; every route reports zero CPU calls. |
| GPU resizing instead of CPU pixels | Normal Vulkan size changes use a GPU nearest-index shader. Unequal up/down tests match the source-pixel mapping of the CPU resize byte-for-byte; hardware swapchain receives resized frames. |
| No silent CPU fallback | Normal GPU failures propagate to failed entry/loop exits. CPU kernel/fill/composite/wire entry points reject before writes in required mode. Negative backend tests preserve image bytes and use no CPU fallback. |
| Software-backend rejection | Actual forced llvmpipe and forced SDL software renderer fail. Controlled CPU-only Vulkan properties are rejected before `vkCreateDevice`; actual hardware Vulkan selection/swapchain passes. |
| Reference and timing contracts | Selected CPU oracle passes native and retail regression checks. Actor/input/simulation and movie audio/video timing rules are the same on both paths; integer close-fade, dimming, alpha and pixel-copy equations are tested independently. |
| Shared tools/docs and matching oracle | GPU entry acceptance is indexed with the shared tools/docs; no matching-recovery source is changed, and `make check typed-check link` passes with a byte-identical relink. |

The audit's source scan includes direct framebuffer writes rather than relying only on public
raster counters: the character closing fade is a direct write that the public counters did not
cover. It executes the exact integer ratio on GPU, with all 31 factors and 256 byte inputs
tested. Remaining raw byte loops in
normal paths decode assets or pack/copy transport data (RGB24-to-RGBA and swapchain channel
order). They do not select resized pixels, shade or composite the framebuffer. CPU raster loops
remain in explicitly selected reference/analysis tools and are blocked under normal hardware
policy. Decoder/asset work and byte transfers remain on the CPU, as allowed by the agreed
boundary.

`check-gpu-entries` is an opt-in hardware/display gate, not part of display-free CI. It fails
rather than silently skipping missing required presentation paths. Physical SDL/Vulkan pixel
comparison reports 99.985% identical and mean RGB delta 0.017 under its allowance.

Logs are workspace `scratch/gpu-entry-acceptance.log`,
`gpu-present-{sdl-hardware,sdl-reject,vk-hardware,vk-reject}.log`,
`gpu-startup-physical-{sdl,vk}.log`, `gpu-stage-{headless,physical-sdl}.log`,
`gpu-strict-{final-build,live,menus}.log`, `gpu-final-status-gpu.log`,
`gpu-final-boot-gates.log`, `gpu-final-native-retail.log` and `gpu-final-matching.log`. The
validated host is a Linux desktop with a hardware GPU.

## Rules for rendering changes

- Preserve painter order, alpha conventions, depth policy, dimensions and image lifetime. Batch
  glyphs rather than uploading/reading an entire framebuffer for each triangle.
- Preserve source input, animation, simulation and controller timing; audit renderer ownership
  and context restoration before introducing shared GPU operations.
- A GPU error reaches the normal engine loop. Normal play has no GPU-to-CPU fallback, including
  initialization failure and software-driver selection; the independently selected CPU oracle is
  preserved.
- Instrument actual CPU raster entry points and direct pixel composites so a normal GPU route
  cannot pass by silently doing CPU work. Exercise failures and teardown as well as positive
  routes across boot, title/options/character flows, loading, greeting/HUD, STATUS and stage
  inspection.
- CPU/retail instruction and vertex checks are separate oracles. Keep their tolerances and
  recorded full-frame limits; diagnostic image differences are not retail fidelity passes.
- Benchmark simulation, draw preparation, rasterization and presentation separately, and retain
  host/backend details with the private results.

The [task list](project/tasks.md) holds the current tasks. STATUS GPU performance evidence and
its limits are in the acceptance audit, archived outside the repository.

## Open items

- Windows and physical Steam Deck release acceptance.
- Speaker output, complete game progression and retail whole-frame pixel parity are broader
  project limits, not claimed by this graphics-path closure.
- Removing framebuffer upload/readback transfers is a separate performance optimization (see
  [lobby rendering](lobby-rendering.md#remaining-performance-work)).
