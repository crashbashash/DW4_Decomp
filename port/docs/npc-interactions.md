# Native hub NPC interactions

Live Cross interaction is connected in the normal prepared hub runtime. Pressing Cross near
an awake NPC runs the original probe, receiver, `hit_<info>.lua`, dialogue, choices and any
service the NPC's script starts, then restores control. Verified headlessly for Central's
mission/save Digi-Elf, the XDATA service Digi-Elf ([XDATA shop](xdata-shop.md)) the bank Digi-Elf ([NPC bank](bank-shop.md)) the appraiser Digi-Elf ([NPC appraiser](cnos-shop.md)) the lab Digi-Elf ([Digi-Lab](labo-shop.md)) and the Shop's disk Digi-Elf ([Digi-Disk shop](disk-shop.md)). Every awake
talker of the three hubs is classified by `check-hubnpcs`; see the coverage and boundaries below.

## Recovered path and ownership

The original lobby player update (`3d22f0`) admits Cross (`0x4000`) and constructs
a `beModelCtrlDataSC` hit request: kind60000, start1, length1, local offset
`(0,4,7)` and size `(3,3,3)`. `39a500` creates its subcommand; `3993e0` transforms
the offset by the source node matrix, constructs a world-axis box and queries
`HITPLAYERTALK` with `CHKBULLET`. The authored first `HIT` data controls membership
(`390e80`). Registration runs from info acceptance (`3787a0`, virtual call at
`378858`), once per RAM slot in order, before gameplay generation. `390e80` registers the
RAM in `MODELCTRL`, then in `HITPLAYERBULLET`, `HITPLAYERTALK` and `HITENEMYBULLET` by the
first HIT row's bytes +16, +24 and +17. Removing Work does not imply removing that prepared
RAM registration. The group names, order and flags are read from the instructions and
implemented natively (below); no executed-instruction oracle of `390e80` exists yet, and
the existing slot oracle checks acceptance/slot order with this initializer as a controlled
leaf. Preserve accepted-info/RAM order and active Work gating, not nearest-NPC selection.

The native model decoder retains that first `beModelCtrlInfoDataHit` row's talk
byte and ordered AABox list. Instances share the immutable local boxes and own
independent projected-box caches. `dw4_modelctrl_talk_hit` implements the NPC,
player-source branch of `396a80` case6: active/control/invulnerability gates,
first intersecting authored box, original `hit_<info>.lua` with call name `Hit`,
native HP precedence and optional turn toward the source. It does not implement
the player/player invulnerability exception or general combat contacts.

Body projection follows `3908e0`: transform the box, retain its transformed
centre, then restore the original world-axis half extents. Results cache at the
world timestamp, including repeated queries after a same-frame transform change.
`dw4_hitbox_*` implements original AABox transform/centre/inclusive intersection
and the player talk probe geometry. The native actor matrix is shared with
world rendering; complete retail actor-matrix construction remains separate.

The synchronous script context snapshots target matrix, kind, box and source RAM.
It implements `MDLgetPosStr`, `MDLgetRotStr`, `MDLgetBulletKind`,
`MDLgetBulletBoxNo`, `BLTgetShootRamNo` and `MDLsetDMGTurn`. Nested callbacks retain
independent contexts. Successful uncancelled calls commit HP and damage-turn;
cancelled callbacks do not commit either. Native HP changes during the callback
take precedence over snapshot HP, following `394400`. No host pointer is stored
in an original four-byte field or exposed as Lua userdata.

The positive MUTEKI counter decrements after Action2/wait dispatch and before
floor response (`3951e0`, called by `395b50`). Negative counters remain permanent;
underflow clamps to positive zero. Scale-one Frame deltas use the original
quantized clock, software integer conversion, EE division and three-frame cap
(`3a8140`). Frozen/repeated samples do not decrement. Sequence replacement retains
the count; removal invalidates cached geometry and clears the released Work count.
This comparison does not establish all original timer creation/initialization or
non-unit timer-scale behavior.

## Headless verification

- `make -C port check-hubdisk`: the Shop's disk shop reached by the real probe ([Digi-Disk shop](disk-shop.md)).
- `make -C port check-hubshops`: the Shop's weapon, armor, chip and junk shops reached by the real probe ([equipment shops](equipment-shops.md)).
- `make -C port check-hublabo`: Central's Digi-Lab reached by the real probe ([Digi-Lab](labo-shop.md)).
- `make -C port check-modelcontact`: nested/cancelled callback lifetimes; an
  original Central `n_digilfm` hit through its actual authored boxes and controller
  selects `SQ_TALK`, captures NPC/player RAM and queues original dialogue. Miss,
  disabled and invulnerable targets do not execute it. A controlled script also
  checks native HP precedence, same-frame cache/next-frame reprojection, damage
  turn and removal. The input probe and PLAYER control receiver remain fixtures.
- `make -C port check-modelcontact-retail`: 345 helper return/string comparisons
  and 802 original AABox/body/probe comparisons. Matrix/atan/conversion/geometry
  instructions execute; allocation, property lookup, message dispatch and platform
  formatting are controlled leaves. Four existing offline EE dumps confirm the
  startup-initialized +Z vector used by the rotation helper; startup is not
  executed by this oracle.
- `python3 port/tools/verify_modelai_retail.py`: additionally compares 96 complete
  scale-one Frame results and 63 complete MUTEKI updates, including wrap,
  quantization, cap, signed-zero and permanent-counter boundaries. Property/context
  lookup and the countdown's Frame query are controlled leaves respectively.
- `make -C port check-hubtalk`: normal Central runtime — registered receivers, a Cross that finds nothing, stick-walk to an NPC, the real probe, original dialogue and choice (both branches), close and restored control, the `stagIS12` request, and the XDATA service ([XDATA shop](xdata-shop.md)).
- `make -C port check-hubbank`: the bank service reached by the real probe ([NPC bank](bank-shop.md)).
- `make -C port check-hubcnos`: the appraiser service reached by the real probe ([NPC appraiser](cnos-shop.md)).
- `make -C port check-modelcontact`: also covers the registry (acceptance-time registration, ungenerated Work ineligible, per-receiver geometry dispatch).
- `make -C port check-actorctrl`: talk counter expiry, repeated/frozen samples,
  long-gap cap, sequence retention and removal, alongside existing actor tests.

The full headless native `make -C port check` passes,
including connected application travel and STATUS regressions. Optional pose/fog
checks explicitly skip without live dumps. Focused contact/actor ASan/UBSan checks
pass with leak detection disabled.

## Live path (implemented)

- **Registration** (`3787a0` → `390e80`): `dw4_controllers_open` registers every receiver whose
  first authored `HIT` row has the talk byte (+24) into one ordered list, in accepted
  info/RAM-slot order, before any Work is generated (Central: 44 registered, 11 awake at
  arrival). Eligibility is evaluated at dispatch from the live Work state; removal does not
  unregister. The list lives and dies with the scene's `dw4_controllers` owner.
- **Dispatch** (`3993e0` → `beMessenger_DispatchSelected`, selector −1): `dw4_controllers_talk`
  visits *every* active registered receiver in list order and each tests its own authored boxes,
  so there is no nearest-NPC choice and overlapping NPCs all fire. The source `BHit` callback
  (`394400`) is not implemented: no original Lua defines `BHit`.
- **Probe** (`3d22f0`): `dw4_lobby_talk` latches the Cross pressed edge (`0x4000`, forwarded by
  `dw4_hubruntime_input`, suppressed while STATUS is active, travel is pending, input is
  disabled, or the stage input slot is blocked). It is consumed on the next player update that
  has `finished`, player control, native models and a sequence that is not `SQ_JUMP`/`SQ_FALL`,
  and not on the same update as a Circle jump. The probe (kind 60000, start 1, length 1,
  offset (0,4,7), size (3,3,3)) runs once after that tick's movement, using the post-movement
  player matrix, shooter RAM 0 (the single hub player's slot).
  The one-frame sub-command clock (`399d90`, Frame delta) is modelled as same-tick execution;
  non-unit Frame deltas are not modelled.
- **Wake**: the `n_*` NPC models carry a NEAR `MAP00` (far zone `SQ_SILENT`, which sets
  `MUTEKI -1`). A name-based sequence set clears negative MUTEKI (`396a80` `398358`), so an NPC
  that wakes to `SQ_WAIT` becomes talkable; positive counts (the 120-frame talk guard) persist.
  `select_sequence` mirrors that reset.
- **Walkability**: NPCs and walls block movement; the XDATA Digi-Elf's route is a waypoint list
  derived by breadth-first search over the real movement code (`test_hubtalk.c`).

## Remaining integration

- Every SUBWND mode reachable from a Terminal, Central or Shop NPC (XDATA, LABO, BANK, CNOS, DISK, WPU, APU, CHIP, JUNK) is
  implemented; mode 10 (CARD) is requested only by the front-end pack, not by any hub NPC. The
  screen behind the Save Keeper's `saveshop.lua` choice (`stagIS12`) is hosted natively ([Save Keeper](save-keeper.md)):
  talk, accept, the save scene, a saved slot-0 character on the host card and the return to Central are driven
  headlessly (`check-hubsave`, and as a service case in `check-hubnpcs`). The Terminal's join screen (`stagIS13`,
  `LOADCTRL2`) is hosted the same way ([load scene](load-scene.md)): talk, accept, the load scene (player 0's panel, START), the
  record untouched and the return to the Terminal at position 4 are driven headlessly (`check-hubload`, and as a service case in
  `check-hubnpcs`). The card album (`stagIS11`, SUBWND CARD) is hosted as well ([card album](card-album.md)): talk, accept, the chooser, a Booster Pack opening, the album and the return to Central position 4 (`check-hubcard`, and as a service case in `check-hubnpcs`).
- The `stagIS11/12/13` requests (card album, save, load) are interface scenes, not mission stages; all six hub portal
  destinations prepare and run.
- Player/player invulnerability exceptions and general combat contacts remain unimplemented; hub
  worlds have combat disabled, so every NPC is invulnerable and only talk contacts are live.
- Frame-delta ≠ 1, co-op shooter numbering and full retail frame parity are not claimed.

## Destination NPC coverage (`make -C port check-hubnpcs`)

`tools/test_hubnpcs.c` boots a fresh prepared hub for each awake `n_*` talker in `stagML11`,
`stagML12` and `stagML13`, teleports the player beside it (trying eight directions at two radii and
keeping spots where the player lands at the NPC's height; the NPCs stand on raised platforms),
closes in with real stick movement, presses Cross and drives the original script with both prompt
choices (Cross is pressed only while control is withheld). Every case is classified; only a real
runtime error fails the test. A run has 38 cases and takes about four minutes:

- **10 plain dialogues** that close with control restored, **4 stage requests** (e.g. `stagIS11`,
  `stagIS13`) and **24 implemented services** (XDATA, the Save Keeper's hosted save scene, the bank in Central and Shop, the appraiser, the Digi-Lab,
  the Shop's disk shop and its weapon, armor, chip and junk shops, and the disk-collector Prmame: [XDATA shop](xdata-shop.md), [NPC bank](bank-shop.md),
  [NPC appraiser](cnos-shop.md), [Digi-Lab](labo-shop.md), [Digi-Disk shop](disk-shop.md), [equipment shops](equipment-shops.md), [Prmame](prmame-npc.md)).
- **0 unimplemented cases.** The two `n_prmame` cases depend on the `SYSctlDiskFolder` engine service; the folder
  services are native ([Prmame](prmame-npc.md)), and `n_prmame` is the disk collector, not the Save Keeper.
  That NPC has no window, so the coverage test classes it as a service by name and
  `check-hubprmame` asserts its effects. No replacement scripts are substituted.
- No NPC is left without a Cross hit or stuck. `DW4_NPC_ONLY=stage:name:slot` and `DW4_NPC_TRACE=1`
  select and trace a single case. A conversation that closes without a service is repeated once before an NPC is
  classed as a plain dialogue (the junk clerk's first conversation is an introduction).
