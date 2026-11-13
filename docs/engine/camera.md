# Stage cameras

How a stage's camera is read from its pack, the stage projection, and the runtime camera controller's layout.

## Composing a stage's camera

A stage's camera is found by composing a camera node's ancestor chain and inverting the result.
The order is child x parent, leaf leftmost, in the row-vector convention.

stag0102's chain, root first:

| Node | Transform |
| --- | --- |
| `igSwitch` | identity |
| `igTransform` | translation (0, 1, 0) |
| `igTransform` | translation (0, -5, 0), rotation about X with rows (1, 0, 0), (0, 0.57358, -0.81915), (0, 0.81915, 0.57358) |
| `igTransform` | translation (0, 0, 130) |
| `igCamera` | `cameraShape00` |

This composes to (0, 102.490, 74.565). Parent x child gives (0, -4.43, 129.18) and frames 3 of 702 live placements, where
child x parent frames 389. Summing the translations, (0, -4, 130), is wrong because the hierarchy rotates the later offset.
All geometry lying on one side of the camera plane proves nothing, since that holds trivially for a camera above the stage.

## The stage projection

The stage projection is a row-major perspective matrix with m[0]=1.9444, m[5]=2.7778, m[10]=-1.0690, m[11]=-1,
m[14]=-20.6897: a vertical field of view of 39.60 degrees (2*atan(1/m[5]), 0.6912 rad) and m[0]/m[5] = 448/640, the 640x448
framebuffer.

To find one in a RAM dump, scan for a 4x4 with m[3]=m[7]=m[15]=0, m[1]=m[2]=m[4]=m[6]=m[8]=m[9]=m[12]=m[13]=0, m[11]=-1,
m[0]>0, m[5]>0, m[14]<0. That gives 48 candidates over four parameter sets, and the aspect picks the game's.

w = -z, so the camera looks down -Z and a point in front has negative view-space z. Getting that sign wrong makes almost
nothing appear on screen.

Framing alone does not identify a camera: any sufficiently distant camera with a narrow field of view frames everything, so
only the combination with a projection of the framebuffer's aspect discriminates. stag0102's pack camera with this projection
puts 389 of 702 live placements on screen.

## The authored stage camera

The stage camera is the first `igCamera` in node order whose composed world is not the identity: a graph-path-root camera has
no ancestors, so its world is the identity and it must be skipped. The view is the inverse of that world, fov 0.6912 rad,
aspect 0.7 * width / height.

That is the pack's authored camera, not the gameplay view: on stag0101 it does not reproduce the live frame, and the gameplay
view is the inverse of the live eye world matrix. Passing an identity world as the view gives a smear.

## The runtime controller

`beCameraCtrl` (vtable `0x53a210`) fields:

| Offset | Field |
| --- | --- |
| +0x20 | `_viewerMang` |
| +0x24 | `_viewerPara` |
| +0x28 | `_cameraMode` |
| +0x2c | `_avgPos` |
| +0x38 | `_savePos` |
| +0x44 | `_isPosChange` |
| +0x48 | `_cameraNowFrame` |
| +0x4c | `_cameraNow` |
| +0x50 | `_cameraOld` |
| +0x54 | `_eyeMatrix` |
| +0x94 | `_intMatrix` |

`src/game/beCameraCtrl.cpp` (unit `bec_beCameraCtrl`, `0x378d80`-`0x37a7b0`) holds it. `beCameraCtrl::vfunc_31`
(`0x379c40`) is the per-frame update: `beCameraCtrl_UpdateBoxCamera` when the info's data is a `beCameraBoxData`
(`beCameraCtrl_IsBoxCamera`), else `beCameraCtrl_UpdateDemoCamera` (`beCameraCtrl_IsDemoCamera`).

The box camera sends GETMATRIX to the PLAYER group and averages the player positions. When the average moves, it looks
for the first box (`_geometryList` entries 1..n, the bound's corners from `igAABox_GetCorner`) holding it; a new box
starts a `beCameraMode` on the viewer (`beCameraMode_Create`, `beCameraMode_SetCameraPath`,
`igViewManager_SetViewMode`) and the eye and interest transforms (entry 0 of `_eyePosList`/`_intPosList`) blend from
the saved matrices to the new box's entry over 120 frames under the CAMHOKAN timer: translations by `Vec3_Lerp`,
rotations through `Matrix44_GetQuaternion`, `Quaternion_Lerp` and `Matrix44_SetQuaternion`. The demo camera starts its
`_cameraPath` once and plays it for `_endTime`.

A shake is a `beCameraCtrlInfoRamShake` (`SHK`) in the ram's data list. Each frame offsets the eye and interest
positions by `_value` times the entries of `g_cameraShakeOffsetX`/`g_cameraShakeOffsetY` picked by the current digit
of `_moveCode`; the SHAKEONE timer (`_oneTime` seconds) steps `_movePoint`, and the SHAKEALL timer (`_endTime`) restores
the saved positions and removes the shake.

`beCameraCtrl_GetMessageEnum` names the 15 messages `beCameraCtrl::vfunc_33` answers (SHOWPOLYGON ... DBGZOOMOUT,
enum `beCameraCtrlMessage` in the source). SHOWPOLYGON and HIDEPOLYGON set or clear the box switch's child mask
(`igBitMask_SetAll`, `igBitMask_ClearAll`); SETBOXCAMERA and SETDEMOCAMERA pick which info runs (the box camera stops
while a demo camera of the given name exists); SHAKE creates the shake; ONFREEZE/OFFREEZE set the mode's `_isFreeze`.
The DBGZOOM messages step `_debugZoom` by 0.2.

`beCameraCtrlInfo._data` (+0x1c) is a `beCameraBoxData` (`_switch` +8, `_geometryList` +0xc, `_transformList` +0x10,
`_eyePosList` +0x14, `_intPosList` +0x18) or a `beCameraDemoData`.

`beCameraMode` has `_cameraPath` +0x4c, `_camera` +0x50, `_insight` +0x54, `_svWorldTimeL` +0x58, `_nowTimeL` +0x60,
`_timeLength` +0x68, `_isEnd` +0x70, `_isFreeze` +0x71. `vfunc_29` (`0x37a7f0`) copies `_camera`'s position
(+0x2c/+0x30/+0x34) into the Insight object (`beCameraMode`+8) at +0x50/+0x58/+0x54 and sets fov, near and far. `vfunc_28`
(`0x37a900`) advances the camera path by `_nowTimeL`/`_timeLength` and pushes transforms. `beCameraMode_SetCameraPath`
stores an `igGraphPath` as `_cameraPath` and its last node (`igGraphPath_GetTail`), when an `igCamera`, as `_camera`.

## Open questions

- `beCameraCtrl_EnableDebugZoom` and `igViewerSceneInfoManager_DebugZoomOut` are empty in retail; their names come from
  the DBGZOOM messages that call them.
- `igViewerSceneInfoManager_ResetOperationMode` sets the viewer parameters' `_operationMode` to 1 and posts a change;
  what mode 1 is has not been traced.
- `Quaternion_Lerp` has no square root or trigonometry; whether it normalises its result is not checked.
