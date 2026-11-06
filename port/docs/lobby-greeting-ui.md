# Main Lobby greeting UI

The first-arrival adapter draws the game's own message windows and portrait from
NDMW 820 and reads the English text layouts from AREA 674 (`usa_pack.igb`).
`src/lobbyui.c` owns this bounded greeting controller; it does not execute the
full messenger or SELECTCTRL runtime.

Lua `MODELCTRL ISRUN` and `ISSEQNAME` read the five greeting models from
this controller's current phase. `SQ_OPENL` becomes `SQ_WAITL` when the talk
window finishes opening; `SQ_CLOSEL` covers its closing range. The announcement
uses `SQ_OPEN`, `SQ_WAIT` and `SQ_CLOSE`; `LOOP01`/`LOOPL` are action names,
not sequence names. Continue models report `SQ_LINESL00` while visible. Queries
never tick the UI. The session registers named receivers on lobby publication
and removes them before teardown. These are queries over the bounded adapter,
not the complete retail model dispatcher. Authored creation/close commands,
SELECTCTRL results and fonts have native services; active status/menu SUBWND
remains pending. See [dialogue services](dialogue-services.md). A Lua DM wait checks the actual
16-update opening transition; it does not prove retail dispatcher latency.

## Models and typography

| Use | Asset | Action windows, in 60 Hz frames |
|---|---|---|
| Digi-Elf dialogue | `i_talkwn` and `n_digilffic` | OPENL 10..26, LOOPL 30..60, CLOSEL 70..86 |
| Terminal announcement | `i_messwn` | OPEN01 10..26, LOOP01 26..26, CLOSE01 70..86 |
| Continue indicator | `i_talkky` / `i_messky`, first selector branch | LINESL00 10..50 |

The adapter follows `beAction2Info._switch` to the flattened graph and
`_dataList` through the named action's `_comList` to its JOINTSET. Window geometry,
UVs and inline textures are used directly. Painter order follows transformed Z.
The portrait is `n_digilffic.png`; the common window atlas is 128x32. Both retain
stored row order and convert palette alpha with `(A+1)/2`. Material RGB is 127,
alpha 128; sampling is linear/repeating with AREF 12.

AREA 674's `beFontInfoData` selects the following `font00` layouts. Positions
come from the linked `igAttrSet`'s child transform, at 100 pixels per font unit.

| Font group | Baseline origin at 640x448 | Width / height in font units | Face |
|---|---|---|---|
| TALKFONT01 | 24,344 | 5.80 / 1.14 | NORMAL |
| TALKFONT02 | 108,344 | 4.96 / 1.14 | NORMAL |
| TALKFONT03 | 40,305 | 2.28 / 0.20 | MINIMUM |

`bectext.igb` (NDMW 79) names the two `beFontImage` faces. Each points to its own
484-entry metrics list and shares `font00.png`. `_code` occupies the low u16 of
the 40-byte metric; the MINIMUM records retain `0xcccc` in the padding halfword.
Reading a u32 code makes the smaller face inaccessible by its actual character.

The bounded greeting adapter uses metric width/height and `ceil(100*advance)`, not the atlas
rectangle's texel dimensions. NORMAL has a 0.28-unit line height and zero
baseline offset; MINIMUM has height 0.18 and baseline -0.01. A negative glyph Y
bearing lowers a descender. The font's own baseline offset also participates.
Adapter text retains the disc's CRLF line breaks and falls back to width wrapping.
The scene-owned TEXTCTL path instead uses original raw advances and line rebasing,
without width wrapping; its geometry is verified against retail instructions.
Body RGBA is (114,114,114,121). The helper's `TALKFONT03` colour command supplies
(0.9,0.9,0.47), which becomes (114,114,60,121). The speaker string is read from
`mswkNPC001`, rather than hard-coded.

## Page groups and transitions

The flag-500 script calls `funcOpenMessage`, `funcOneMessage` and
`funcCloseMessage` for five groups: 39..41, 42..46, 47..48, 49..50, and 51..53.
The helper bodies are nested Lua prototypes in the stage's layer-setup chunk;
the cleaned top-level stub declarations do not describe their behavior.

The window starts opening when the guide's WALK02 action completes; see [arrival choreography](lobby-choreography.md). Text and selector
appear after its 16-frame JOINTSET window finishes. Cross advances within a group.
At a group boundary, text and speaker clear immediately and the old window and
portrait play their closing range before the next group opens. Cross during
opening, closing or the terminal wait is ignored. Window and selector loop clocks
remain separate; changing a page restarts the selector without restarting the
window loop.

The 90-tick beep wait starts after closing page 48. Pages 49/50 use the wider
TALKFONT01 layout without the portrait or speaker. After page 53's window closes,
the existing 120-tick restoration delay starts. The owning lobby plays the original
terminal beep when this wait begins; see [audio playback](audio-playback.md).
Gameplay control restoration remains outside this UI implementation.

These timings implement the pack's windows and the script's group ordering.
They do not prove the original messenger/model dispatcher overhead or selector
completion latency. Exact full-sequence timing and the bottom decoration's phase
still need an arrival recording; no typewriter reveal has been inferred.

## Verification and previews

Run from the repository root:

```sh
make -C port build/lobby_ui_frame build/lobby_frame
port/build/lobby_ui_frame ../local/extracted 39 /tmp/greeting.png /tmp/greeting.tsv
port/build/lobby_ui_frame ../local/extracted 49 /tmp/announcement.png /tmp/announcement.tsv
port/build/lobby_frame ../local/extracted 339 /tmp/arrival.png /tmp/arrival.tsv --ui
python3 port/tools/verify_lobby_ui.py \
  --dump /path/to/lobby_now.gs.zst --json /tmp/greeting-report.json
make -C port check
```

`lobby_ui_frame` advances to the requested page and draws it over a uniform gray
background. An optional final directory receives the three decoded texture PNGs
for verification. `lobby_frame --ui` composes the first greeting over the native
arrival; its TSV remains the environment vertex export.

The held first-greeting retail capture agrees with all **316 unique body glyph
vertices**, **32 speaker vertices**, **4 portrait corners** and **42 fixed window
vertices**, in position (maximum error 0.062515 pixels), UV and vertex RGBA.
All three textures are **RGBA byte-identical** to retail VRAM. The verifier
excludes window-atlas vertices at Y >= 430 before reading retail positions and
reports them separately: 40 bottom-decoration vertices differ by up to 1.0625
pixels because their LOOPL phase is not synchronized with this held capture.
Vertices generated by GS clipping at the screen boundary are not claimed as
original asset vertices. This is vertex/texture evidence, not a pixel-identical
full-frame claim.

`test_lobbyui` exercises all 15 pages, both font faces, speaker/portrait visibility,
text bounds, suppressed input throughout transitions, the 90-tick gap and final
close. It also checks the specialized window ACTION sink delivers authored
OPEN/CLOSE events and stops after detach; see [window audio](audio-playback.md).
The integrated four-species lobby test also checks the 120-tick completion
delay. Retail input captures remain private optional inputs.

After final closure and its 120-tick wait, the owning lobby restores the bounded
single-player status panels through the same UI submission backend. Their shared
language-library textures and remaining HUD limits are documented in
[Control handoff](lobby-choreography.md#control-handoff).

## Script-owned text

The UI borrows the scene's [dialogue owner](dialogue-services.md) and samples
scene-owned TEXTCTL triangles with authored ancestor transforms, scene switches
and layer masks. Faces and geometry are owned by the dialogue service. Text queries
and rendering never advance SELECTCTRL or models. Accepted font mutations transfer
text ownership from the greeting adapter. Normal boot still uses the arrival/
greeting adapter until collision, renderer publication and original first.lua
ordering are integrated. The adapter rendering checks apply;
the text path traverses its font parents and layers, while whole-scene
composition/pixel parity remains unverified.

## Record-backed HUD meters

The lobby HUD binds its first-player HP/MP meter nodes through the original
`hpmt1`/`mpmt1` beMeterCtrlOneData records. Maximum, notch mode and nonzero/nonmax
limits come from the stage pack. SETPERCENT uses the record health/maxima with
EE arithmetic. Initialization derives the step as `max(maximum/60,1)` and the
animation ratio as `2000000000/maximum`. Each world update approaches the target;
HP notch mode truncates the displayed value and preserves a nonzero sample.
Meter animation samples span 1000000000 (zero) to 3000000000 (full), with authored
interior endpoint limits. Drawing samples the current value without advancing it.
STATUS holds the world updates, so these meters hold with the gameplay HUD.

The retail check executes 10400 display/time updates at `0x0038fa50`, eight
initializations at `0x0038f9b0` and 80 SETPERCENT commands at `0x0038ff40`. Command
lookup, argument retrieval and float-to-integer conversion are controlled leaves;
the meter state transitions execute original instructions. Native HUD checks
cover all four portraits, partial/zero values, authored descendant animation
samples, repeated draw independence and rejected zero maxima. ASan/UBSan passes
with leak detection disabled. This connects meter presentation; numeric HUD
geometry is described in the next section.

## Authored HUD number geometry

The HUD renders the original `lvnm1`/`hpnm1`/`mpnm1` geometry in
`i_stpnl04`; these numbers are not font digits. Number RAM records supply
the geometry, maximum, zero-suppression mode, digit order, atlas step and six
vertex index/kind mappings per digit. Health publication sets these numbers
immediately, as original NUMBERCTRL SETVALUE does. Drawing derives UVs from
the record tuple with EE arithmetic and does not modify the shared pack data.
The separate disc-font player name remains.

The retail check executes `0x003a4b20` for 40 digit arrays and compares all
1440 vertex UV pairs, including negative/zero values, leading zero suppression,
multiple digits and both tested atlas steps. Vertex lock/unlock leaves are
controlled. Native tests require all three meshes and validate every mapped
vertex index against its mesh; record changes alter submitted UVs for all four
portraits. This verifies the number projection and its HUD connection, not
retail full-frame parity or normal-boot STATUS admission.

HUD restoration consumes the player-health publication flag. A dead player's
ADDHP-zero early return leaves the existing HP meter target/display/sample and
numeric HP unchanged; MP and level publication still use the current tuple.
All four portrait fixtures check the suppressed-HP state independently of MP.
The ordinary health setter remains available for actual HP changes, including
a newly published zero.
