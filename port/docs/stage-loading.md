# Stage loading

Created-card login presents the character screen's final black CLOSE frame, then
shows a loading screen before preparing Main Lobby. The original loading node's
reveal/play-limit wait is preserved (about 1.67 seconds at 60 Hz); normal runs add
no extra inspection hold. For inspection, launch with
`--loading-min-seconds 10` to keep each lobby loading screen visible for at least
10 wall-clock seconds from its first presented frame. Fractional seconds are
accepted (0 disables the hold; maximum 86400). Asset preparation still begins
immediately; a completed lobby stays unpublished until the minimum expires.
Slower loads can take longer. Failures show Retry/Back immediately, and closing
the window during the hold frees the prepared destination. Lobby arrival clocks
start only after the complete destination is ready; confirm presses held during loading cannot
skip greeting pages.

## Presentation and assets

The retail stage loader constructs `loadingUSA/ldagML11.igb` from the bare
`stagML11` destination. Directory-qualified manifest lookup selects USA AREA
entry **1321**. Basename lookup alone would select `loadingeng` entry **831**,
the wrong region.

The full `LOADING` graph contains seventeen drawable instances using one inline
256×256 atlas. It supplies the original hub preview, “Home Server” and
“Main Lobby: Terminal Area” lettering, scrolling green “Now Loading” bands,
hexagonal background, triangular cover panels and edge highlights. Geometry
and text come from the stage asset. Other destination cards resolve through
the same stage-name transformation, rather than reusing the lobby image.

The imported complete nine-body node/loading runtime drives the authored clock,
stall compensation, first-time rebase, loop and strict play-limit predicate.
`igCompressedAnimationSequenceQS` sources drive the cover/effect transforms;
target-9 transforms animate UVs, including the original hexagon trace.
Compressed time keys use the original sign-magnitude 2^23-ns encoding, so the
trace remains animated rather than ending in the first few frames. The card
inherits its authored additive blends for hexagons, scrolling bands and lights;
preview/name and covers retain ordinary alpha. The card renderer sorts transformed mesh depth,
including Z stored in vertices.

When destination preparation, the original play-limit wait and the optional
inspection hold have all completed, the loader locks the original node at its
authored lock time and presents that sample before publishing the lobby.
An extended hold keeps animating; it does not repeat the opening reveal.
See the [decompilation contracts and evidence](../../docs/engine/stage-loading.md).
Exact retail GS blending, compressed-sampler EE rounding and frame-for-frame
visual comparison remain unverified. Missing loading artwork falls back to
“Now Loading” using the already-loaded game font.

Normal boot enables the loading artwork's GPU owner under the hardware
policy. GPU initialization/draw errors remain explicit. Normal loading framebuffer clears and fallback/error font strings use GPU
operations too. Explicit reference mode retains the CPU oracle. See the active
[GPU rendering goal](gpu-rendering.md).

**Card textures on the shared GPU layer ([#3089](../../docs/findings/findings-3001-3250.md#f3089), [#3090](../../docs/findings/findings-3001-3250.md#f3090)).** The GPU layer caches uploaded textures by pixel pointer and size. A hub card is
closed when the next load begins, and the next card's atlas (also 256x256) is allocated at the freed address, so `dw4_frontui_close` forgets its
textures on the layer (`dw4_gl_layer_texture_forget`) before freeing them. Without that a later load draws the previous
destination's atlas: after a Central visit, the Terminal gate's practice stage shows "Main Lobby: Terminal Area". `make -C port check-loadingstale` renders the Terminal and practice cards
in turn on one layer and requires the second to match its own CPU render (with a stale atlas it is identical to the first, 0.05 against 16.8 mean level difference).

**Plain cards and the save scene ([#3092](../../docs/findings/findings-3001-3250.md#f3092), [#3093](../../docs/findings/findings-3001-3250.md#f3093)).** Five destinations (`stagML14`, `stagIS07/09/10/20`) have a 9,639-byte card with no `beLoadingNode`: one opaque black 32x32 quad. Retail shows a black screen there. The card opens as a still card, ready at once (`dw4_frontui_open_loading` does not return NULL for it, so the "Now Loading" text fallback is not drawn). `make -C port check-loadingcards` opens and draws all 98 `loadingUSA` cards. The save/slot scene (`dw4_savescene_close`) forgets its image and font-atlas textures on the shared layer and releases its layer reference (a reference kept per visit leaks the layer, and for a hub's own layer a whole GL context); `check-savescene` asserts the layer's cache is empty and its owner count back to 1.

## Preparation and ownership

`src/loadjob.c` owns one pthread worker with a mutex-protected completion/result.
The boot loop draws and pumps window events while `prepare_lobby` checks the
front-end Game Start handoff and builds the CPU lobby scene, actors, textures,
collision, greeting UI and immutable arrival audio clips. The worker receives a copied name/species record,
a borrowed mounted archive and a private destination-name buffer. It does not
open an audio device or call window, renderer or GPU services. Audio decoding
uses the CPU media/resampling helpers; device playback starts on publication.

The loading subtree is decoded before the worker begins. The scene graph loader
has shared walk state and is not generally safe for concurrent scene loads:
only the worker loads scenes during this transition; the presentation thread
samples resident loading geometry. GPU initialization remains on the presentation
thread after successful preparation. General parallel asset streaming and async
GPU uploads are outside this implementation.

Completion is observed under the mutex and joined before the lobby and stage
name become active. Failure never activates a partial destination. The error
screen offers Cross to Retry or Circle to Back. Back restores the created card
with name/species intact. Window close and bounded-run exit join outstanding
work, free any unpublished destination, then release the archive and context.
Shutdown currently waits for an in-flight CPU load to finish; cancellation within
asset decoders remains unimplemented.

Loading samples are always presented, including while the live 60 Hz pump has
catch-up ticks queued: catch-up updates do not consume loading samples offscreen. They gate the first worker start and the reveal/lock wait;
advancing that sample count without presenting it can hide the loading card.
Title/lobby catch-up frames retain their separate presentation policy. The live
catch-up fixture, `make check-loading` and `tools/verify_frontend.py` cover this;
no physical display or every-stage transition claim is made.

Headless probes present the same first loading frame, then run preparation synchronously
on the next tick. This keeps scripted arrival times deterministic. Windowed runs
use the worker. The arrival handoff rebases frame pacing after GPU setup so a
loading stall does not cause a burst of arrival updates.

## Validation

`make check` includes:

- `scripts/verify_loadingnode.py` in the decomp repository: 2,631 original
  instruction/C comparisons, covering all nine runtime bodies and their
  reachable instructions, ordered calls/stores and defined return values.

- `tools/test_loading.c`: a deliberately blocked worker permits 150 animated loading
  draws and nonblocking polls; real lobby preparation then runs concurrently with
  resident-art drawing. USA/other-region lookup, a second destination card,
  the original ready threshold and locked-frame stability are checked. Trace key
times, inherited additive material and visible outline brightening are checked. Completed NULL results and shutdown before polling are
  checked, including ownership of the unpublished lobby.
- `tools/test_loading_live.c`: the actual SDL windowed boot loop with deterministic
  pad/clock leaves and a ten-tick stall during loading. Every loading sample must
  reach SDL presentation (a loop that lets catch-up consume loading samples presents only 75 of 85).
  Startup FMV/cards are bypassed in this test;
  original database/title preparation and threaded lobby preparation still run.
  SDL dummy drivers verify the live scheduling branch, not a physical display.
- `tools/verify_frontend.py`: the final black CLOSE frame, the revealed original loading card, then normal textured lobby arrival and greeting.
- `tools/verify_loading.py`: a private modified manifest makes the player lookup
  fail while retaining the entry-based selector preview. Retry repeats the load;
  Back restores the created card; another Start retains the character. No partial
  lobby activates. Original archives are read through symlinks and remain untouched.
  It also checks a ten-second wall-clock hold followed by arrival, exit while a
  prepared lobby is held, and invalid duration arguments.

A scripted windowed boot through SDL's dummy video/audio drivers reached
Main Lobby through the threaded production path, presenting 103 original-card
loading frames and 152 arrival frames in a 700-frame run. This verifies the
windowed handoff without establishing physical display/controller behavior or
retail visual parity.

The full USA loading card was visually inspected at 640x448. Physical older hardware
performance, retail loading-screen frame comparison and Steam Deck validation
remain outstanding.

## Script ownership at publication

CPU preparation does not publish Lua or receiver state. When the destination is
ready, the simulation thread performs the coordinated SD → Lua → DM boundary,
then releases title receivers and prepares the authored lobby file list. Supporting
sound entry 819 precedes script entry 820; its ordered 64-row Lua-info library
runs original `func.lua` and `boot.lua`. The boot filename queue then loads actor,
weapon, regional and light packs. The retained stage directory and prepared packs route into native info
objects and authored layer bindings before layer/window receivers publish. Failed
binding blocks script startup and destination publication. Original live
start/first choreography and general controller commands remain pending; see
[native scene objects](stage-objects.md).
Native flags and RNG survive the fresh VM. A failed script publication discards
the destination and restores a fresh title library before Retry/Back; worker
shutdown still joins before releasing borrowed mount/context data. See
[Lua ownership](lua-integration.md#recovered-retail-loading-and-ownership-790793).

## Hub-to-hub application transitions

Original hub exit/choice requests and authored destination spawn matrices
have native owners and headless checks; see [hub travel](hub-travel.md).
Private CPU preparation accepts the three authored hub scenes
and their arrival groups.

Normal created-card gameplay registers the deferred stage-travel owner and
prepares original Terminal/Central/Shop destinations through `hubruntime.c`.
Stage-specific USA loading art is decoded before the worker begins. While loading,
the application pumps input/presentation but consumes no session simulation ticks;
source and destination script/controller clocks remain held. Publication rebases
host pacing credit and begins destination arrival on the next admitted tick.

The source scene and records survive until graphics/audio publication succeeds.
The existing mixer transfers on commit, stopping old clip references before source
release; original destination PLAY requests collected during preparation are then
published. Retry preserves the request. Back restores the retained source using
original fade/control/input sequences, without returning to character creation.
Shutdown joins the worker before changing borrowed source owners. Detailed policy,
fixtures and current validation boundaries are in [hub travel](hub-travel.md).
Initial-source Retry/Back then Central publication and the existing initial-login
loading/STATUS regressions pass. All six application routes/choices/STATUS and 3263/3263 loading samples pass.
A headless desktop GPU two-transfer run retains GPU drawing, and closing during a
confirmed blocked worker safely joins before source teardown. Later-source
ASan/UBSan failure recovery passes. The full headless native suite also passes.
