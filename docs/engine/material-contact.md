# Material controller and Lua material contact

The material controller `beMatCtrl` marks, per material, which players stand inside one of the
material's boxes and runs the material's Lua script when a player enters or leaves. Its source is
`src/game/beMatCtrl.cpp`. The helper group at `0x0038aca0..0x0038af70` implements the seven Lua MAT
bindings; the binding wrappers at `0x00373160..0x00373274` are C++ in
[`src/game/be.cpp`](../../src/game/be.cpp). The controller methods at `0x0038af70..0x0038bed0`
(prepare, receiver registration, recursive contact search, the per-instance update, message
dispatch and two metadata getters) follow them; the box-membership leaf `igAABox_IntersectPoint`
and the message enum getter `beMatCtrl_GetMessageEnum` live in the maths and Bec libraries. For the
update see [Open items](#open-items).

None of this establishes whole-frame or general portal acceptance.

## Receiver and module boundary

All seven wrappers load global `0x0058a1c8`. Constructor `0x00371a30` builds that object using
class handle `0x00589160`, which reflection identifies as `beMatCtrl`. Its field metadata agrees
with the helper loads and stores below. The seven helpers occur consecutively between the last
`beLuaState` methods and the material controller's constructor/method family. The final helper
symbol contains eight trailing padding bytes after its return.

Names are semantic recoveries, not claims about the original C++ spelling: the helper names come
from the Lua API and the verified receiver, the controller's virtual slots take the names their
sibling controllers use (`beSound`, `beNDMWStatus`: GetMeta, RegisterReceiver, GetInfoMeta, Update,
Prepare, OnMessage). Generate them with
`python3 scripts/seed_names_material_contact.py > config/SLUS-20836/names/MaterialContact.tsv`,
then use the dry run and `--apply --check` naming workflow.

## Functions and source

| Address | Symbol | Role | Source |
| --- | --- | --- | --- |
| `0x00373160..0x00373274` | `MATisPlayer`, `MATisAllPlayer`, `MATgetPlayerNo`, `MATisRidePlayer`, `MATisRideOffPlayer`, `MATgetPlayerMatStat`, `MATsetRun` | Lua binding wrappers | [`src/game/be.cpp`](../../src/game/be.cpp) |
| `0x0035a6b0` | `beMatCtrl_GetMessageEnum` | MATCTRL message enum | `src/game/bec/beMatCtrlData.inc` |
| `0x0038aca0` | `beMatCtrl_IsPlayer` | query helper | `src/game/beMatCtrl.cpp` |
| `0x0038acd0` | `beMatCtrl_IsAllPlayer` | query helper | `src/game/beMatCtrl.cpp` |
| `0x0038ad40` | `beMatCtrl_GetPlayerNo` | query helper | `src/game/beMatCtrl.cpp` |
| `0x0038add0` | `beMatCtrl_IsRidePlayer` | query helper | `src/game/beMatCtrl.cpp` |
| `0x0038ae30` | `beMatCtrl_IsRideOffPlayer` | query helper | `src/game/beMatCtrl.cpp` |
| `0x0038ae90` | `beMatCtrl_SetRun` | activation request (16 bytes) | `src/game/beMatCtrl.cpp` |
| `0x0038aea0` | `beMatCtrl_GetPlayerMatStat` | query helper | `src/game/beMatCtrl.cpp` |
| `0x0038af70` | `beMatCtrl_Prepare` | Lua owner lookup, mask lists dropped | `src/game/beMatCtrl.cpp` |
| `0x0038b040` | `beMatCtrl_GetInfoMeta` | metadata getter | `src/game/beMatCtrl.cpp` |
| `0x0038b050` | `beMatCtrl_RegisterReceiver` | receiver registration (44 bytes) | `src/game/beMatCtrl.cpp` |
| `0x0038b080` | `beMatCtrl_MarkContacts` | recursive contact search | `src/game/beMatCtrl.cpp` |
| `0x0038b1f0` | `beMatCtrl_Update` | per-instance update (3,064 bytes) | `asm/` |
| `0x0038bdf0` | `beMatCtrl_OnMessage` | message dispatch (220 bytes) | `src/game/beMatCtrl.cpp` |
| `0x0038bed0` | `beMatCtrl_GetMeta` | metadata getter | `src/game/beMatCtrl.cpp` |
| `0x0018b630` | `igAABox_IntersectPoint` | box membership | `src/engine/maths/igAABox.inc` |

The seven Lua wrappers total 240 code bytes and need C++
mode. C mode produces tail jumps rather than the original stack frames.

## Fields

| beMatCtrl offset | Recovered meaning |
| --- | --- |
| +32..+35 `_wkPlExist` | Four inline player-existence bytes; any nonzero byte is true |
| +40 `_wkChkMat` | Material index for the active callback |
| +48 `_wkChgFlagNO` | Material index for the deferred activation request |
| +52 `_wkChgFlag` | Requested activation byte |
| +56 `_wkMatOnList` | Current per-material player-bit masks |
| +60 `_wkMatOldOnList` | Previous per-material player-bit masks |

Both lists expose their element buffer at +16, and the queries address it by byte offset: each
scales `_wkChkMat` by four once and reads the current and previous list at that offset. The +32
existence bytes are read with `lbu` and a stride of one; treating them as four integer elements
would read unrelated fields. The generated reflection header declares them as
`unsigned char _wkPlExist[4]` (an `igBoolArrayMetaField`).

The manager's `_isLuaCallDisp` byte enables debug formatting of Lua calls. Each RAM instance has an
`_isRun` byte at +20 and a state word `_st0` at +24, followed by `_st1`, `_st2` and `_st3`.

## Query helpers

| Address | Engine helper / Lua binding | Behavior |
| --- | --- | --- |
| `0x0038aca0` | `beMatCtrl_IsPlayer` / MATisPlayer | Current mask is nonzero, even if only a bit above player three is set |
| `0x0038acd0` | `beMatCtrl_IsAllPlayer` / MATisAllPlayer | Every existing player has its current-mask bit; no existing players returns true |
| `0x0038ad40` | `beMatCtrl_GetPlayerNo` / MATgetPlayerNo | First existing player whose bit is current but not previous; zero also means no result |
| `0x0038add0` | `beMatCtrl_IsRidePlayer` / MATisRidePlayer | Selected bit is current but not previous |
| `0x0038ae30` | `beMatCtrl_IsRideOffPlayer` / MATisRideOffPlayer | Selected bit is previous but not current |
| `0x0038ae90` | `beMatCtrl_SetRun` / MATsetRun | Copy current material index to request index, then store the argument's low byte |
| `0x0038aea0` | `beMatCtrl_GetPlayerMatStat` / MATgetPlayerMatStat | Outside 0, leaving 1, entering 2, staying 3 |

Ride queries operate on mask transitions; they do not themselves implement platform movement or
collision. Their variable shifts use the EE's low five shift-count bits. These helpers perform no
null, index or player-range checks. SetRun records a request; it does not immediately mutate the
callback's mask.

`beMatCtrl_GetPlayerMatStat` keeps the previous-mask result as a byte and the current one as an
int, so only the previous result is masked with `andi 0xff` before each compare. Retail scales the
loaded `_wkChkMat` into a separate register for the offset. The source declares the locals before
assigning them, `bit` ahead of the offset; the same statements written as initialised declarations
scale the index in place and colour the bit, the offset and the previous list differently.

## Material producer and receiver lifecycle

The sections below cover the five
nontrivial bodies of the method group `0x0038af70..0x0038bed0`: prepare, receiver
registration, recursive contact accumulation, per-instance update and message dispatch, plus the
box-membership leaf. The [Lua dependency inventory](lua-dependencies.md) includes the five as
evidenced runtime roots, without inventing edges from virtual dispatchers to those functions; the
closure's totals are stated there.

### Prepare and registration

`beMatCtrl_Prepare` (`0x38af70`) looks up the `beLua` manager (handle `0x589208`) through the
insight core and stores it at +36, then for each published mask list clears its count, releases
it and nulls the field.

`beMatCtrl_RegisterReceiver` (`0x38b050`) registers the incoming RAM as a receiver under
`MATCTRL`, with null text and index -1. The RAM arrives in a1 and is a parameter of the method: a
draft that omits it shifts every later argument register.

### Per-instance update

Each RAM instance's `_isRun` byte (+20) gates its update (`0x38b1f0`). Any `_st0` (+24) other than
1 recreates Work at instance +44 (`0x359480`), allocates two integer mask lists sized to the material
data count at info +32 and appends them to Work's list at +12, filled from the zero words at
`0x4c8f70` and `0x4c8f78`. It sizes Work's run-flag byte list at +8 to the same count and fills it from
the enabled byte at `0x5549d0`, clears the player-existence bytes and publishes `_st0=1` plus zero
`_st1/_st2/_st3`. This initialization does not also run contact callbacks in that tick. The
allocator fallback is controlled by the byte at `0x554c14`.

Active update retains slot 0 of Work's mask list as the current buffer and slot 1 as the previous one,
and clears the current buffer from the word at `0x4c8f80`. It selects PLAYER/GETMATRIX results
(`0x38e670`), reconstructs the four existence bytes (a byte is set when any result's player id equals
that player) and, for each result whose player exists, converts the selected matrix to a point
(`0x38f630`, `0x190a30`) and runs the recursive search with the root node at info +36.

The current and previous buffers are retained and published on the manager before Lua executes.
For each enabled material, in order, update tests players 0 to 3 with `(word & bit) == bit` on both
buffers. On the first player whose result differs it sets the callback material index,
resets the requested activation index to -1 and the activation byte to 1, formats its authored
name as `%s.lua` (a null name uses the empty string at `0x4e0858`), clears global MDL object `0x58a1e0`, and invokes Lua once
(`0x389ff0`, with the manager's owner at +36). The first differing
player ends the search, so simultaneous changes do not multiply callbacks. Debug formatting runs
only when `_isLuaCallDisp` is exactly 1.

After each callback, a requested index other than -1 that is within the run-flag list changes its
run-flag byte; noncanonical values are
retained. Disabling a later material affects that same tick's remaining traversal. The work's two
list references then swap (slot 0 receives the previous buffer, slot 1 the current one, each store
guarded by the list's count), with retains before releases and the low-23-bit destruction rule
preserved.

### Recursive contact search

`beMatCtrl_MarkContacts` (`0x38b080`) admits inclusive X ranges, requires the box query to return
exactly 2 before setting a material/player bit, and visits children even when a parent's box
fails. A range miss skips its whole subtree. Index -1 is a search-only node. The original reads
material/mask cells before the mask-store range guard, with no other bounds policy. Its first
argument, the controller, is passed down the recursion but never read.

### Box membership

`igAABox_IntersectPoint` (`0x18b630`) checks point X/Y/Z
against the box's min vector at +8/+12/+16 and max vector at +20/+24/+28, inclusively and in axis
order. It returns only 0 (outside) or 2 (inside). The comparison follows the
[EE float rules](action2-timing.md#floating-point-is-not-host-floating-point): signed zeros and
denormals compare as zero, and exponent-255 inputs are finite values. That model is not a
hardware measurement.

### Message dispatch

The six enum rows at `0x4c6130/0x4c6150`, which `beMatCtrl_GetMessageEnum` builds into the enum
named `Message`, establish the message order:
SHOWMAT, HIDEMAT, SHOW_LUACALL, HIDE_LUACALL, PAUSE, RESTART. The first two enable or disable all
children of the info's switchgraph; the next two set the manager debug byte; PAUSE/RESTART change
the RAM run byte. Recognized commands return 1 and unknown commands return 0.

The handler spans `0x38bdf0..0x38becc` (220 bytes). Ghidra's address set for it contains 212
occupied bytes; the span also includes the shared return at `0x38bec4` and its delay slot at
`0x38bec8`, so those eight bytes are code of this function. `data/function-extents.json` records
the extent; it is generated by `scripts/dump_function_extents.py` with analysis disabled, and
`tools/split.py` and the layout generator consume it. `tools/test_function_extents.py` protects
this reviewed return and the title-message handler's, and rejects shrinking, overlap, duplicates
and misalignment.

## Update ownership and call contracts

The update at `0x0038b1f0` has five automatic reference-owner lifetimes.
Its exception index at `0x0054eba0` records function size `0xbf8` and table `0x00543890`. The
independently checked next full index at `0x0054ebb8` identifies `0x0038bee0`, size `0x4ac`, table
`0x005438d0`. This bounds the material table to **64 bytes: 62 payload bytes and two zero pads**.
The decoded frame is 480 bytes with nine saved general registers.

| Protected return-PC range | Owner stack offset | Cleanup identity |
|---|---|---|
| `0x38b304` | `+0x1dc` | work ref, `0x359900` |
| `0x38b3ac..0x38b48c` | `+0x1d8` | first fresh integer-list ref, `0x150eb0` |
| `0x38b524..0x38b604` | `+0x1d4` | second fresh integer-list ref, `0x150eb0` |
| `0x38b870..0x38bd28` | `+0x1cc`, then `+0x1d0` | retained previous/current list refs, both `0x150eb0` |
| `0x38bd7c` | `+0x1d0` | surviving current-list ref, `0x150eb0` |

The factory results are adopted; runtime list references increment their counts inside
construction, before their cleanup lifetimes activate. Destruction follows reverse construction
order and the low-23-bit reference-count rule. The two 128-byte destructor bodies implement the
same operation but have different instruction scheduling. Their addresses and compiler profiles
remain distinct. The decoder in `scripts/combat_unwind_inventory.py` handles this table format; the
index anchors above bound the material instance independently.

Two call contracts follow from a callee and format-string audit:

- The `sprintf` call (`0x00129e60`) formats `%s.lua` with **destination, format and name**.
- The grouped messenger call takes **receiver, group and event**.

Further argument-register values at those call sites (three at the formatting call, two at the
messenger call) are stale register contents, not inputs.

These contracts are recovered independently of a matching main-body claim.

### Regional and platform counterparts

The corresponding update is at `0x0038b480` in Europe and
`0x0038c8c0` in Japan. All three releases have the same critical bit-test loop. Address-shaped
operand differences in the rest of the body do not establish equivalent behavior of the referenced
callees or data, and comparing the releases does not resolve the USA mismatch.

A comparison with the GameCube and Xbox updates shows different load placement
there; it does not close the USA boundary either. The regional and platform targets are retired
and their comparison tooling is not in the repository.

## Open items

- **The update main body (`0x0038b1f0`, 3,064 bytes).** A C++ spelling
  reproduces the five owner lifetimes, both destructor variants, the exception index and the
  complete table extent, but its main body has ten differing instructions in the bit-test loop of
  the changed-bit scan. The register gap is that retail holds the previous word in `a0` and the
  current compare temporary in `a1`.
- **Natural loop forms do not close the gap.** Retail leaves the four-bit
  scan after the first changed bit: the changed path ends with an unconditional branch to the
  outer-loop increment (`0x38bc58`), and the unchanged path increments the bit and branches back to
  the shift at `0x38ba58`. The current and previous list words are loaded once before that loop.
  Five natural spellings of this shape (a `for` with `break` using the hoisted words and the shared
  constant, the same with a literal `1`, a `do`/`while` with `break`, both word reads inline, and
  the previous-word compare first), compiled with the five-scope owner frame and the pinned
  alternate compiler, leave 13, 13, 13, 15 and 13 main-body words different, against the
  goto-shaped candidate's ten, with the same register gap.
- **Engine services.** Matrix queries, allocator and list services, formatting, Lua execution,
  receiver registration and the constructor/framework services are not described here.
- **Names.** `igAABox_IntersectPoint` is named from its 0/2 result, the pattern of the other
  igAABox intersection tests it is registered beside; `beMatCtrl_Prepare` takes the slot name
  `beSound` and `beAction2` use for the same virtual slot.
