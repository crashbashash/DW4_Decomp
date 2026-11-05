# Authored box-camera transitions

The Main Lobby follows the original `beCameraCtrl` box-camera update
(`0x00378ed0`). Its eye and interest transforms remain separate until publication.
Changing regions retains the currently displayed pair and blends toward the new
authored pair, instead of replacing the camera world matrix immediately.

## Selection and transition

NDMW 820 supplies seventeen list entries. Entry zero is the mutable rig; selectable
volumes start at one. Inclusive minimum/maximum tests choose the first containing
volume in authored order. No containing volume retains the current selection.
The single joined player's corrected position supplies the rig's parent translation.
Retail averages joined player positions before this query; live native co-op
ownership is still outside the current lobby boundary.

On a region change, retail copies the current eye and interest matrices to retained
start matrices and clears `_cameraNowFrame`. An interrupted blend therefore starts
from its actual intermediate pose. Each matrix's translation uses linear
interpolation. Rotation uses matrix-to-quaternion conversion (`1925f0`),
shortest-sign **normalized linear quaternion interpolation** (`192cc0`), and
normalized quaternion-to-matrix conversion (`191770`). This is not spherical
interpolation or linear matrix interpolation.

The sampled fraction is `cameraNowFrame / 120`, before advancing the timer.
`CAMHOKAN` supplies the elapsed frame delta, capped at three. Moving adds that
delta; unchanged average position adds `delta * 1.5`. Creating the timer contributes
zero on its first sample. The transition finishes on the next update whose stored
frame is at least 120, copies the exact authored targets and removes the timer.
At 60 Hz this is approximately two seconds while moving, or 1.33 seconds while
stationary, with the original first-sample/completion boundaries.

The initial selection has old region zero and copies its target directly, matching
retail's first `SETBOXCAMERA` after the demo. It is subsequent region changes that
blend. The box camera follows player translation during that blend. Publication
composes eye times interest, then adds the player translation.

## Native ownership and verification

`src/boxcamera.c` owns this retained state; `src/lobby.c` selects authored volumes
and updates it once after player movement/collision on each world tick. Material
sampling does not call the camera a second time. Camera timing uses the original
100 ns clock quantization and EE division by 16666667 at the host's agreed 60 Hz
cadence. Rendering only reads its published matrix. STATUS/manual/disconnect holds
stop the world update without catch-up. Options modes, shaking and live co-op
framing remain separate work.

`make -C port check-boxcamera check-lobbywalk` covers first acquisition, smooth
rotation, interruption, stopped completion, capped delta, read-only rendering,
four original starter routes and STATUS holds. The walking route rejects an abrupt
orientation change and requires actual region changes and multiple blend samples.
`check-boxcamera-retail` executes original `378ed0` transition branches and the
quaternion/translation instructions for 4,200 states. Lookup, allocation, volume
corner extraction and timer-service leaves are controlled. State/timer results
match exactly; matrix differences are below 0.000001 (the test ceiling is 0.00003).
The interpreter's square root and accumulated FPU operations retain the existing
documented EE arithmetic model; this is not a PS2 hardware float-bit proof.

Live pristine-disc reads from fresh-Dorumon slot 44 verify region `16 → 14 → 8`,
an interrupted transition, continuing movement and faster completion after stopping.
The settled region-16 eye/interest composition agrees with the measured inverse
view within 0.000006.
These checks establish the camera contract, not frame-identical whole-scene
latency or complete pixel parity. Finding [#850](../../docs/findings/findings-0751-1000.md#f850) records the recovery.

Validation covers the full native `check check-retail`, both Cross/Circle
normal creation/login/STATUS routes, the extended SDL region-crossing route with
three STATUS restores and keyboard events, hardware-GPU STATUS rendering and
explicit draw failure, the focused camera ASan/UBSan check and the root
`check typed-check link` gate. Optional native
pose/fog checks retain their explicit missing-input skips.

## Other hub preparation

Camera region storage allocates from the authored parallel lists rather
than a fixed 32-entry buffer. Central supplies 37 entries
and Shop 24 (including their mutable entry zero). The same camera updater
serves every hub. Headless CPU preparation/diagnostic views pass; original destination
startup and live transition acceptance remain open. See [hub travel](hub-travel.md).
