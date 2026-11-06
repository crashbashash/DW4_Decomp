# Prepared native scene objects

Title and Main Lobby preparation route their stage directory and prepared
packs through `src/stageobjects.c`, then bind the authored layer graph before
publishing native receivers. Normal created-card Main Lobby login executes
original live start/first scripts through their owning services, with scene-owned actor/player movement, collision,
motion/opacity publication and restoration. See [the lobby contract](lobby-gameplay.md)
for evidence and scope. General controller/stage coverage, general gameplay and whole-frame parity are outstanding.

## Collection and native ownership

The file-list callback visits the retained stage-directory pack first, followed
by first-use resources, supporting packs, scene packs and original boot queues.
Each pack's `igInfoList` reference array selects native infos in authored order.
Unreferenced records and nested model/action data are not independently registered.
Repeated rows remain repeated entries and share one mutable typed native object
for the same pack-local id. Equal ids from different packs have separate owners.
The registry supports exact class/name lookup with an occurrence index, preserving
collection order and duplicate names for subsystem consumers.

Each owner retains its own parsed descriptor, typed `dw4_object` instances and
renderer-ready `dw4_scene` arena. The callback's borrowed `dw4_igb` descriptor can
be released afterward. Original bytes remain borrowed from the mounted archives;
the mount must outlive these owners. Object reference fields retain pack-local ids;
`dw4_scene_handle` resolves them into four-byte arena handles. No host pointer is
written into a recovered reference field.

`dw4_scene_load` (`src/scene.c`) places every id's payload at a 32-bit arena handle in
id order, then reads geometry back through those handles. The arena packs ids at
`DW4_SCENE_ALIGN` (16), so the file's pool padding is not reproduced and nothing in the
loader path depends on a file offset. The stage's pack is reached the way the game
does it: manifest, stage `.igb`, then its own `[0.621]` entry reference.
`dw4asset scene --check` asserts that every id is placed once in order, that each
payload is byte-identical to the file, and that every mesh handle resolves (NDMW.AFS
entry 621: 50,497 ids, 549 meshes, 82,134 vertices).

The live title MODELCTRL receivers select their names from routed native
`beModelCtrlInfo` objects and require the authored `entry` camera info. The five
lobby window receivers likewise require and use their routed controller records.
Title handlers retain their bounded behavior. Window commands select authored programs in the owning UI; queries retain the greeting adapter until that model receives a command. The scene owns independent RAM-slot controllers for the other prepared MODELCTRL infos; [controller services](controller-services.md) describes supported object programs, queries and teardown. Other
collected info classes are available to their future native command systems;
collecting a typed record does not implement its commands or all Lua overloads.

Prepared `beDBManagerInfo` records feed an independent copied
[string database owner](databases.md), including the real STATUS shinka NAME
lookup. This supplies typed native data access; general Lua object returns remain
pending.

First-use archive residency remains owned by the file-list loader. Native object
arenas currently belong to the prepared scene; general persistent manager/cache
ownership across arbitrary stages remains a later lifecycle task.

## Layer binding

The referenced `beLayerInfo._groups` → `beLayerGroupList` array supplies the layer
order, followed by the original `NONE` fallback. Title and Main Lobby both bind:

`BG01 BG02 GM01 GM02 EM01 NP01 PC01 EF01 EF02 EF03 BG03 GM03 WN00 WN01 WN02 WN03 WN04 FONT LOADING NONE`

The binding identifies the authored `ROOTATTR` scene and its descendant
`LAYERPARENT`. A synthetic ordered layer switch attaches at that parent; external
scene roots remain edges containing their native info owner, pack-local root id
and layer index. This preserves cross-pack ownership without copying host pointers
into arena records. Scene roots attach to the first equal layer name; unknown
or empty names attach to `NONE`. Graph-path inputs retain the first ancestor of
each authored path rather than treating every path element as a separate root.
Camera-path lists are not independently added to the layer graph.

The production title prepares 162 referenced infos and 14 root attachments;
Main Lobby with Dorumon and its starter axe prepares 211 infos and 16 attachments.
Both light packs retain the same layer order. Multiple layer-info definitions
are rejected explicitly until repeated ORDER ownership is recovered and tested.
Multiple root records/names otherwise retain their authored collection order.

New layer-mask bits begin clear; the loading phase enables `LOADING`. The native
LAYERCTL receiver implements `SWITCH` with slash-separated `name/action` values:
`CLR`/`DISPOFF`, `SET`/`DISPON` and `FLIP`. Named changes target the first equal
layer; missing names do nothing. `ALL` clears/sets every bit; `ALL/FLIP` does
nothing, matching retail dispatch. SD owns positive-delay delivery and scoped
cancellation. Other layer commands and result-array/receiver-context operations
remain unsupported and report an error.

Current presentation adapters continue selecting their own draw instances and
visibility. The prepared layer graph and masks are the native resource boundary
for their replacement by original script/model orchestration; no general renderer
traversal or full retail visual parity is claimed.

## Startup gate and failure handling

The required loader sequence is `begin` → `shared` → `route_assets` →
`bind_layers` → `start` → `first`. Routing alone cannot advance to `start`.
Routing or binding failures latch preparation failure and block subsequent
milestones until a coordinated scene reset.

The session constructs this owner privately, validates every info reference and
layer edge, then publishes its layer receiver. A failed scene never publishes
these objects. Title/lobby replacement and shutdown cancel SD, release Lua/DM,
unregister borrowed controller receivers, then release the native registry.
Existing loading Retry/Back restores a fresh title scene after failed destination
publication. General gameplay Retry/Back and arbitrary stage transitions remain
outstanding.

## Evidence and validation

The central retail collector `0x00237030` visits manager acceptance slots at
vtable `+0x6c` in order, stops at the first nonzero result, then retains the object
in the coordinator list even if no manager accepts it. Archive completion
`0x003810c0` consumes the completed archive's info list. Layer ordering and root
attachment come from `beLayerCtl::vfunc_34` (`0x00389170`), with file-list phase 6
supplying ORDER and `LOADING/SET` before layer-node attachment. Read-only Ghidra
exports from the existing analysed project were checked against retail objdump.
The action enum table at `0x004c63b0` maps `CLR`, `SET`, `DISPOFF`, `DISPON`,
`FLIP` to 0, 1, 0, 1, 2. `igSwitch` child insertion calls bit-mask growth
`0x001b1e50`, which initializes new bits from the zero word at `0x0048d8d0`.

`make check-stageobjects` checks original title/lobby collections, both light
packs, exact layer order, root/parent handles, font/player/weapon attachments,
controller lookup, delayed mask publication/cancellation and 128 scene reloads.
Copied private input fixtures exercise malformed info references, wrong layer
list types, missing ROOTATTR, shared object identity, orphan exclusion, released
callback descriptors and `NONE` fallback without modifying original assets.
`make check-filelist` additionally checks startup blocked before binding and
failed binding blocking both later script milestones.

`make check-script-retail` includes `tools/verify_stageobjects_retail.py`:
34 original-instruction layer-mask scenarios compare against the native fixture;
six central-collector cases check ordered acceptance and retained ownership.
String/enum parsing, receiver selection, mask mutation and manager acceptors are
controlled leaves. These establish dispatch contracts, not complete scene outcomes.

The focused original-asset checks also pass ASan/UBSan with `detect_leaks=0` and
`halt_on_error=1`. Integrated platform/device validation remains outstanding.

## Static hub collision roots

The explicit gameplay-world scene load retains beHitLandModelInfo kind1/floor
and kind2/wall switchgraph roots outside drawable igSceneInfo graphs. A missing
root blocks that load instead of publishing only part of the static roster.
The bounded lobby collision consumer combines each graph's transformed
vertices and rebased triangle indices; Shop's two floor infos both survive.
Ordinary analysis/actor-preview loads keep their own graph coverage.
See [destination preparation](hub-travel.md#destination-environment-preparation)
for counts, headless checks and the remaining native publication boundary.
