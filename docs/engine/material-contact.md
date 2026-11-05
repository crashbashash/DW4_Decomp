# Lua material-contact engine helpers

The contiguous helper group at `0x0038aca0..0x0038af70` implements the seven Lua MAT bindings on
the material controller `beMatCtrl`. The binding wrappers at `0x00373160..0x00373274` are matching
C++ in [`src/lua/material.cpp`](../../src/lua/material.cpp), and all seven engine helpers have
matching source. The adjacent controller methods at `0x0038af70..0x0038bed0` (initialization,
receiver registration, recursive contact search, message dispatch and two metadata getters) and the
box-membership leaf at `0x0018b630` also match. The per-instance update at `0x0038b1f0` is the one
function of the module without matching source; see [Open items](#open-items).

Two behavioral references sit beside the matched source:
[`recovered/engine/material-contact.c`](../../recovered/engine/material-contact.c) for the seven
helpers and [`recovered/engine/material-runtime.c`](../../recovered/engine/material-runtime.c) for
the controller lifecycle. They are readable behavioral C checked against the original instructions.
Behavioral recovery is not matched-code coverage, and it does not establish whole-frame or general
portal acceptance.

## Receiver and module boundary

All seven wrappers load global `0x0058a1c8`. Constructor `0x00371a30` builds that object using
class handle `0x00589160`, which reflection identifies as `beMatCtrl`. Its field metadata agrees
with the helper loads and stores below. The seven helpers occur consecutively between the last
`beLuaState` methods and the material controller's constructor/method family. The final helper
symbol contains eight trailing padding bytes after its return.

Names are semantic recoveries from the Lua API and the verified receiver, not claims about the
original C++ spelling. Generate them with
`python3 scripts/seed_names_material_contact.py > config/SLUS-20836/names/MaterialContact.tsv`,
then use the dry run and `--apply --check` naming workflow. Findings [#858](../findings/findings-0751-1000.md#f858)–[#859](../findings/findings-0751-1000.md#f859) record the
dependency inventory and module evidence; finding [#860](../findings/findings-0751-1000.md#f860) records the lifecycle recovery and [#861](../findings/findings-0751-1000.md#f861) the
dispatcher extent and box-membership evidence.

## Matching status and source

| Address | Symbol | Role | Source |
| --- | --- | --- | --- |
| `0x00373160..0x00373274` | `MATisPlayer`, `MATisAllPlayer`, `MATgetPlayerNo`, `MATisRidePlayer`, `MATisRideOffPlayer`, `MATgetPlayerMatStat`, `MATsetRun` | Lua binding wrappers | matched, [`src/lua/material.cpp`](../../src/lua/material.cpp) |
| `0x0038aca0` | `beMatCtrl_IsPlayer` | query helper | matched, `src/unmatched/beMatCtrl_IsPlayer.cpp` |
| `0x0038acd0` | `beMatCtrl_IsAllPlayer` | query helper | matched, `src/unmatched/beMatCtrl_IsAllPlayer.cpp` |
| `0x0038ad40` | `beMatCtrl_GetPlayerNo` | query helper | matched, `src/unmatched/beMatCtrl_GetPlayerNo.cpp` |
| `0x0038add0` | `beMatCtrl_IsRidePlayer` | query helper | matched, `src/unmatched/beMatCtrl_IsRidePlayer.c` |
| `0x0038ae30` | `beMatCtrl_IsRideOffPlayer` | query helper | matched, `src/unmatched/beMatCtrl_IsRideOffPlayer.c` |
| `0x0038ae90` | `beMatCtrl_SetRun` | activation request (16 bytes) | matched, `src/game/beMatCtrl_SetRun.c` |
| `0x0038aea0` | `beMatCtrl_GetPlayerMatStat` | query helper | matched, `src/unmatched/beMatCtrl_GetPlayerMatStat.c` |
| `0x0038af70` | `Gap__Bec__beMatCtrl__vfunc_32` | initialization | matched, `src/unmatched/Gap__Bec__beMatCtrl__vfunc_32.cpp` |
| `0x0038b040` | `Gap__Bec__beMatCtrl__vfunc_30` | metadata getter | matched, `src/game/beMatCtrl.c` |
| `0x0038b050` | `Gap__Bec__beMatCtrl__vfunc_29` | receiver registration (44 bytes) | matched, `src/game/beMatCtrl.cpp` |
| `0x0038b080` | `FUN_0038b080` | recursive contact search | matched, `src/unmatched/FUN_0038b080.cpp` |
| `0x0038b1f0` | `Gap__Bec__beMatCtrl__vfunc_31` | per-instance update (3,064 bytes) | **no source**; links from the retail image |
| `0x0038bdf0` | `Gap__Bec__beMatCtrl__vfunc_34` | message dispatch (220 bytes) | matched, `src/unmatched/Gap__Bec__beMatCtrl__vfunc_34.cpp` |
| `0x0038bed0` | `Gap__Bec__beMatCtrl__vfunc_20` | metadata getter | matched, `src/game/beMatCtrl.c` |
| `0x0018b630` | `FUN_0018b630` | box membership | matched, `src/unmatched/FUN_0018b630.c` |

The match category of each function is recorded in the generated `data/check-categories.tsv`.

The seven Lua wrappers total **240 matched code bytes** and each passes `tools/verify.py` in C++
mode. C mode produces tail jumps rather than the original stack frames.

Private compiler candidates, the exporter bootstrap, original Ghidra and objdump evidence,
verification reports and logs are in repository-relative `../scratch/lua-engine-recovery/`.

## Fields

| beMatCtrl offset | Recovered meaning |
| --- | --- |
| +32..+35 `_wkPlExist` | Four inline player-existence bytes; any nonzero byte is true |
| +40 `_wkChkMat` | Material index for the active callback |
| +48 `_wkChgFlagNO` | Material index for the deferred activation request |
| +52 `_wkChgFlag` | Requested activation byte |
| +56 `_wkMatOnList` | Current per-material player-bit masks |
| +60 `_wkMatOldOnList` | Previous per-material player-bit masks |

Both lists expose their element buffer at +16. The +32 existence bytes are read with `lbu` and a
stride of one; treating them as four integer elements would read unrelated fields. The generated
reflection header declares them as `unsigned char _wkPlExist[4]` (an `igBoolArrayMetaField`). The
matched `beMatCtrl_IsAllPlayer` and `beMatCtrl_GetPlayerNo` read the bytes through a local byte
view of the receiver, and the behavioral reference preserves the same byte accesses.

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

## Material producer and receiver lifecycle

The [material runtime reference](../../recovered/engine/material-runtime.c) recovers the five
nontrivial bodies of the method group `0x0038af70..0x0038bed0`: initialization, receiver
registration, recursive contact accumulation, per-instance update and message dispatch, plus the
box-membership leaf. The [Lua dependency inventory](lua-dependencies.md) includes the five as
evidenced runtime roots, without inventing edges from virtual dispatchers to those functions; the
closure's totals are stated there.

### Initialization and registration

Initialization (`0x38af70`) constructs a `beLua` owner using handle `0x589208`, clears each
published mask list's count, releases it and nulls the field.

Registration (`0x38b050`) registers the incoming receiver selector under `MATCTRL`, with null name
and index -1. The selector arrives in a1 and is a parameter of the method: a draft that omits it
shifts every later argument register. The matching C++ method passes all five messenger arguments
in the original EE registers.

### Per-instance update

Each RAM instance's `_isRun` byte (+20) gates its update (`0x38b1f0`). Any `_st0` (+24) other than
1 recreates Work, allocates two zeroed integer mask lists and an enabled run-flag byte list sized
to the material data count, clears the player-existence bytes and publishes `_st0=1` plus zero
`_st1/_st2/_st3`. This initialization does not also run contact callbacks in that tick. The
allocator fallback is controlled by the byte at `0x554c14`.

Active update clears the write mask buffer, selects PLAYER/GETMATRIX results, reconstructs the four
existence bytes and converts each selected matrix to a point, then runs the recursive search for
each.

The current and previous buffers are retained and published on the manager before Lua executes.
For each enabled material with any changed player bit, update sets the callback material index,
resets the requested activation index to -1 and the activation byte to 1, formats its authored
name as `%s.lua`, clears global MDL object `0x58a1e0`, and invokes Lua once. The first differing
player ends the search, so simultaneous changes do not multiply callbacks. Debug formatting runs
only when `_isLuaCallDisp` is exactly 1.

After each callback, an in-range requested index changes its run-flag byte; noncanonical values are
retained. Disabling a later material affects that same tick's remaining traversal. The work's two
list references then swap, with retains before releases and the low-23-bit destruction rule
preserved.

### Recursive contact search

Recursive search (`0x38b080`) admits inclusive X ranges, requires the box query to return exactly 2
before setting a material/player bit, and visits children even when a parent's box fails. A range
miss skips its whole subtree. Index -1 is a search-only node. The original reads material/mask
cells before the mask-store range guard; the reference preserves that order rather than adding a
bounds policy absent from retail.

### Box membership

The leaf at `0x18b630` (`dw4_material_box_contains` in the runtime reference) checks point X/Y/Z
against the box's min vector at +8/+12/+16 and max vector at +20/+24/+28, inclusively and in axis
order. It returns only 0 (outside) or 2 (inside). The reference uses the established EE
float-comparison model; signed zeros and denormals compare as zero, and exponent-255 inputs retain
the documented model's finite interpretation. This is an original-instruction comparison, not a
hardware measurement.

### Message dispatch

The six enum rows at `0x4c6130/0x4c6150`, loaded by `0x35a6b0`, establish the message order:
SHOWMAT, HIDEMAT, SHOW_LUACALL, HIDE_LUACALL, PAUSE, RESTART. The first two call the info's
switchgraph; the next two set the manager debug byte; PAUSE/RESTART change the RAM run byte.
Recognized commands return 1 and unknown commands return 0.

The handler spans `0x38bdf0..0x38becc` (220 bytes). Ghidra's address set for it contains 212
occupied bytes; the span also includes the shared return at `0x38bec4` and its delay slot at
`0x38bec8`, so those eight bytes are code of this function. `data/function-extents.json` records
the extent; it is generated by `scripts/dump_function_extents.py` with analysis disabled, and
`tools/split.py` and the layout generator consume it. `tools/test_function_extents.py` protects
this reviewed return and the title-message handler's, and rejects shrinking, overlap, duplicates
and misalignment.

## Update ownership and call contracts

Finding [#2749](../findings/findings-2501-2750.md#f2749) establishes five automatic reference-owner lifetimes in the update at `0x0038b1f0`.
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

Confirmed finding **[#2750](../findings/findings-2501-2750.md#f2750)** identifies the corresponding update at `0x0038b480` in Europe and
`0x0038c8c0` in Japan. All three releases have the same critical bit-test loop. Address-shaped
operand differences in the rest of the body do not establish equivalent behavior of the referenced
callees or data, and comparing the releases does not resolve the USA mismatch.

A comparison with the GameCube and Xbox updates (finding [#2752](../findings/findings-2751-3000.md#f2752)) shows different load placement
there; it does not close the USA boundary either. The regional and platform targets are retired
and their comparison tooling is not in the repository.

## Verification

`python3 testing/test_material_contact_retail.py` compiles the behavioral C with host warnings as
errors, executes the original seven helper functions through the EE instruction interpreter and
compares returns and all RAM writes. There are **61,549 cases**: every four-player
current/previous contact mask and existence roster, three selected material indices with
distracting neighboring masks, noncanonical true bytes, high masks, wrapped variable shifts and
activation byte truncation. No callee is stubbed: these seven functions only access RAM. The
interpreter is an offline instruction oracle, not a running-game capture.

`python3 testing/test_material_runtime_retail.py` passes **3,055 cases**:

- **1,047 whole-function cases** comparing the five original lifecycle bodies with the reference,
  including integrated update-to-recursive-search execution. Each checks returned values, every
  runtime RAM byte and ordered meaningful callee arguments; compiler stack/scratch storage is
  excluded. The matrix covers initialization states, growth and unrolled-fill boundaries,
  noncanonical run/debug bytes, all four-player contact transitions, persistent buffer swaps with
  reordered/duplicate selector results, activation bounds and byte values, allocator branches,
  low-23-bit reference destruction, recursive X boundaries, wrapped shift 31 and all message arms.
  In these cases platform allocation/list services, matrix queries, box membership, formatting and
  Lua execution are explicit controlled leaves.
- **2,000 direct box comparisons** with no callees.
- **Eight full update/search runs** through the original box instructions versus the recovered C
  box function, which remove the controlled box-result boundary for that route.

The float comparison uses the documented EE arithmetic model, whose hardware-validation limit
still applies.

## Open items

- **The update main body (`0x0038b1f0`, 3,064 bytes) has no matching source.** The C++ candidate
  reproduces the five owner lifetimes, both destructor variants, the exception index and the
  complete table extent, but its main body has ten differing instructions in the bit-test loop of
  the changed-bit scan. The register gap is that retail holds the previous word in `a0` and the
  current compare temporary in `a1`. The candidate stays outside `src/`; no instruction difference
  is patched away.
- **Natural loop forms do not close the gap (refuted finding [#2756](../findings/findings-2751-3000.md#f2756)).** Retail leaves the four-bit
  scan after the first changed bit: the changed path ends with an unconditional branch to the
  outer-loop increment (`0x38bc58`), and the unchanged path increments the bit and branches back to
  the shift at `0x38ba58`. The current and previous list words are loaded once before that loop.
  Five natural spellings of this shape (a `for` with `break` using the hoisted words and the shared
  constant, the same with a literal `1`, a `do`/`while` with `break`, both word reads inline, and
  the previous-word compare first), compiled with the five-scope owner frame and the pinned
  alternate compiler, leave 13, 13, 13, 15 and 13 main-body words different, against the
  goto-shaped candidate's ten, with the same register gap.
- **Controlled leaves in the runtime oracle.** Matrix queries, allocator and list services,
  formatting, Lua execution and receiver registration are controlled leaves rather than recovered
  contracts, and the remaining constructor/framework services are not recovered. The full engine
  dependency chain is not complete until they are.
