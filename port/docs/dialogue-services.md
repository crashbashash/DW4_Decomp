# Native dialogue services

The prepared scene owns TEXTCTL fonts and SELECTCTRL RAM slots through
`src/dialogue.c`; `src/selectctrl.c` implements the selection update. Production
registers them after prepared model owners and releases them before the immutable
packs. Original shared func/boot bytecode remains the source of message queues.

## Selection and completion

Each `beSelectCtrlInfo` RAM-list index is an independent selector and pad slot;
serialized `_ramNo` is not the accepted index. The RAM's ordinal-10 `_dataList`
supplies its ONE config, orientation, maximum rows and initial selection.
GENERATE initializes opening state; `NOCANCEL/I<count[,selected]>/V<x,y,z>`
selects the original optional arguments. The first vector places the model.
FO2TOP retains row enablement without replacements. Malformed payloads leave the
existing owner intact.

The state machine sends original MODELCTRL OPEN, line-selection/navigation,
confirmation, CLOSE/CANCEL and FO2TOP sequences and polls numeric ISSEQNAME.
ISEND becomes true only after the terminal update; ISSELECTNOW and ISFO2TOP read
state without advancing it. Circle takes priority over Cross. Disabled rows and
forbidden cancellation play CURSOR_NG and wait 16 updates before resetting.
Input edges are consumed once per simulation tick, never by queries or drawing.
Production currently supplies player zero; the service API preserves four
independent slots for future participating-device ownership.

The model service accepts positioned GENERATE and original FADESET HIDE. HIDE
records cleared visibility without gating Action2 completion; general renderer
publication of that state remains separate work. Specialized greeting owners
replace only slot zero, leaving the remaining prepared slots independently owned.
Reentrant selection/removal invalidates the outer selector snapshot, preventing
it from overwriting the newer state or reading freed enablement arrays.

## Fonts

Prepared `beFontInfo` supplies font group/name, kind, width/height, alignment,
transform origin and Unicode list. The lobby collection contains 286 rows.
The scene collects `beFontImage` objects through authored `igNamedObjectInfo`
lists in collection order. Each face resolves its own metrics, texture binding,
texture, image and palette references; no first-image scan or NORMAL/MINIMUM
name special case selects the atlas. An unmatched or absent kind uses the first
collected face, as retail `0x383350` does. A missing or malformed face fails
preparation rather than publishing a partial text owner.

TEXTSET copies an indexed UTF-16 Unicode entry or decodes direct game bytes into owned
text and six-vertex glyph geometry. `dw4_dialogue_set_unicode` supplies the native
`beUnicodeObj` overload using a bounded 16-bit buffer, including original icon
codes. No geometry borrows the caller's buffer. All selected rows are prepared
before replacement, so an invalid index or allocation failure preserves previous
text and geometry. ALL selects the named font across groups. Native
`dw4_dialogue_replace_unknown` implements REPLACEUNKNOWN in place against the
first collected face, stopping at the first zero code. Replacement codes need
not themselves have metrics, matching retail `0x382c68..0x382d24`. These native
interfaces are for owning engine services; they do not expose arbitrary host
pointers or add a Lua userdata syntax to the original scalar API.

### Original byte-to-Unicode boundary

Direct TEXTSET uses `textcodec.c`, recovering original `382eb0` rather than
treating each byte as a glyph code. The game's table at `4c8880` has 424
Unicode/encoded-byte pairs. High-bit bytes consume a pair; recognized pairs emit
the table's Unicode value. Recognized ASCII emits its original byte, unknown
codes are omitted, CR is ignored, and LF emits only after more than one output
code. This is the retail output rule, including the one-character/leading-LF
case; indexed UTF-16 and the native Unicode overload remain separate paths.
It is neither UTF-8 nor standard CP932. DEVICE marker `81ba` maps to `2286`, and
`8a71` maps to `8d6b`. Item NAME cells also carry encoded icon characters.

The factual mapping pairs are generated in `src/textcodec_table.inc` by
`tools/gen_textcodec_table.py` from the private retail ELF. Regenerate with the
script and verify with `--check`; do not hand-edit the include. No extracted game
binary is committed or executed. `check-textcodec-retail` verifies that table and
executes 816 original decoder inputs, including every mapping, all single bytes,
icons, CR/LF and seeded mixed strings. Allocation and the temporary string builder
are controlled leaves; the output codes run original instructions. Native
insufficient capacity preserves the caller's output/count, and truncated pairs
are safely omitted. Those bounded policies do not reproduce retail unsafe reads.

Weapon-slot render comparison matches 1,752 text vertices,
with real icons and name advances. Forty-two text vertices remain
unmatched, alongside unsynchronized cursor/background phases. The first unmatched
glyph samples a completely transparent atlas region including the inspected filter
border; this observation does not waive the remaining geometric comparison.
See [submenu validation](status-submenus.md#submenu-factory-identities-and-folder-routing).
Evidence: workspace `scratch/status-string-to-unicode.txt`,
`scratch/status-codec-*.log`, and capture-directory
`weapon-coded-comparison.json` / `native-coded-menus/` under
`local/captures/dw4-port/status-validation-20261012/`.

Equipment-selector text also matches all 1,506 submitted vertices in
`equipment-coded-comparison.json`. Full native/retail, normal boot, expanded SDL
and prepared ASan/UBSan checks pass. Submenu full-frame and live-phase parity
remain open.

Glyphs use their metric bearings, width, height and raw advance in authored
units. `fontlayout.c` uses EE float arithmetic and original triangle/UV order.
CR is ignored; LF rebases following glyphs and lowers the line by face height.
The width controls RIGHT/CENTER alignment; retail does not add width wrapping
or clip geometry to the authored height. ALIGN changes the layout used by the
next TEXTSET, retaining existing geometry until then. Missing glyphs produce no
geometry; the native implementation bounds that case instead of reproducing
retail's unsafe line-buffer assumptions. This host memory policy is not a claim
of retail malformed-text parity.

SWITCH accepts SET/CLR, DISPON/DISPOFF and encoded integers, updates authored
text/category switch bits and preserves other visible rows. SETPOSITION updates
the linked transform's three translation channels. COLOR, DEFAULTCOLOR and
CANCELCOLOR change RGB independently of geometry. Draw calls sample current
ancestor transforms, scene switches and the prepared layer attachment/mask.
An unattached or disabled font graph emits no draws. `dw4_dialogue_draw` returns
renderer-neutral text triangles with scene-owned atlas lifetimes; the lobby UI
submits them to its existing CPU/GPU UI backend. Queries and draws never advance
models, selectors or script clocks.

Adapter text yields after the first accepted font mutation. Normal boot retains
the greeting adapter until complete original first.lua orchestration is ready.
The bounded adapter's established typography and retail frame checks remain
separate from this scene-owned path. Full-scene composition/pixel parity and
status/inventory/equipment text producers still need their owning systems.
INITIALIZE is satisfied by native preparation; this implementation builds native
glyph geometry rather than reproducing the middleware's geometry allocation.

## Subwindows

Prepared status slots have a scene-owned native SUBWND service through
`subwindow.c`, with per-slot inactive initialization, active eligibility,
GENERATE/REMOVE/ISRUN state and recursive owned window trees. REMOVE before root
creation retries through the real one-frame SD queue; completion waits on the
root's active flag. Failed preparation preserves inactive state. A concrete
factory must supply the menu and gameplay-record owners before opening.
Borrowed external completion routing remains available through
`dw4_dialogue_subwindow` for isolated services/tests.

The production factory is still absent: status/inventory/equipment/shop/card
stat/inventory controllers and scene/player restoration remain required before
claiming playable menus. Concrete [STATUS title/selection views](status-views.md)
execute original text setup through these native services.
See [status/menu contract, evidence and resume point](status-menu.md).

## Verification

From `port/`:

```sh
make check-dialogue check-actorctrl
make check-dialogue-retail
make check check-retail -j8
```

`verify_selectctrl_retail.py` executes retail update `0x0039cbf0` across 19,200
state/input cases and compares native state and command traces. Pad, model query,
sequence dispatch and sound calls are controlled leaves; the update instructions
are original. This proves the selection update boundary, not model animation or
full retail message dispatch.

`test_dialogue` loads the original shared library and prepared ML11 assets, runs
original funcOneMessage bytecode for all 15 greeting entries and funcChoiceMessage
with two rows. Real native MODELCTRL completion gates the DM waits. It checks
navigation, font ownership/visibility, software draw alignment/color, invalid replacement preservation,
independent player slots and Circle-over-Cross cancellation. SUBWND tests attach
a controlled asynchronous owner to verify DMgetCount waits through closing;
they do not execute retail status gameplay. Scene reset checks owner teardown.
No full-scene visual, emulator, Windows or physical Steam Deck parity is claimed.

`verify_font_retail.py` executes original glyph generation, multiline processing
and alignment instructions (`0x4534f0`, `0x4535d0`, `0x383bf0`, `0x383ed0`).
Metric lookup and vertex-buffer storage are controlled leaves. It compares 1,080
geometry states including bearings, both line heights/baselines, empty/CR/LF
runs, all alignments and widths smaller than the text. REPLACEUNKNOWN dispatch
uses `0x381d70` with controlled message-context and metric lookup leaves.
All 1,080 geometry states match exactly, including every vertex/UV float bit;
48 REPLACEUNKNOWN states match, including terminators and unsupported replacement
codes.

The native dialogue check additionally covers layer hides, authored ancestor
translation, three-channel SETPOSITION, high-resolution scaling, native Unicode
buffer independence, both prepared faces, repeated text replacement and 32
owner reopen cycles.

Full `make check check-retail -j8` passes on Linux
with `SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a`. The focused actor,
controller, dialogue and SELECTCTRL-oracle checks pass. Separate headless
actor/dialogue ASan/UBSan checks pass with `detect_leaks=0` and
`halt_on_error=1`, including repeated text changes and owner teardown;
optional private live-input checks retain their skips.
The negative-delay reentrant SD discrepancy is outside these checks.
