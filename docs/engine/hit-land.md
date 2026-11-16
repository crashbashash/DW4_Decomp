# Hit and land checks (`beHitLandDeliv`, `beHitLandModel`)

Two controllers answer a model's wall and floor checks. `beHitLandDeliv` (`src/game/beHitLandDeliv.cpp`, unit
`bec_beHitLandDeliv`) is the per-model side: it reads the model's transform and its ray settings and talks to the
shared `beHitLandModel` (`src/game/beHitLandModel.cpp`, unit `bec_beHitLandModel`, `0x386030`-`0x389020`), which
traces rays through the check switches of the stage's hit-land models and posts the result back. The model controller
sends the first controller its wall and floor messages ([model controller](model-controller.md)).

## `beHitLandDeliv`

`beHitLandDeliv_OnAddRam` registers each ram under the name `HITLANDDELIVER`. `beHitLandDeliv_OnMessageText` resolves
the five messages of the info's message enum, `HITWALL`, `HITWALLFULL`, `HITFLOORCHECK`, `HITFLOORADJUST` and
`HITFLOOR`, and forwards them to the group `HITLANDMODEL` as `CHECKWALL`, `CHECKWALLFULL` and `CHECKLAND`.

- **`HITWALL`** runs only when the transform's x or z differs from `_oldPos`. It sends the position, the unit
  direction of the move in the XZ plane, the ray settings (`_halfWidth`, `_upRange`, `_downRange`, `_checkFlag`) and a
  flag saying whether the last check touched a wall, which is kept as 1 or 0 in `_pos.x`.
- **`HITWALLFULL`** sends the position twice (the second where `HITWALL` sends the direction), the same settings and
  the same flag.
- **`HITFLOORCHECK`** and **`HITFLOOR`** send the position and the settings as `CHECKLAND`. A reply with fewer than
  three bools or no vector is replaced by the vector `(0, -1, 0)`. When the vector's y is below 1: with the
  transform's y below 0, the vector's x and z (y 0) become `_landPos` and `_oldPos`, `_landPosOK` is set and the
  answer is landed with a floor hit; otherwise `_landPosOK` is cleared and the answer is landed without one. When the
  y is 1 or more the vector is stored as `_landPos` and `_oldPos` and `_landPosOK` takes the reply's third bool.
  `HITFLOOR` then falls into `HITFLOORADJUST`.
- **`HITFLOORADJUST`** moves the transform to `_landPos` when `_landPosOK` is set.

Every message that touches the wall or the floor answers with a bool list: moved, wall hit and 0 for a wall check,
landed and floor hit for a floor check.

## `beHitLandModel`

`beHitLandModel_OnMessage` creates the model's order (`beHitLandModelOrder`), hit traversal and `igProbe` on first
use. Its messages are `CHECKWALL`, `CHECKWALLFULL`, `CHECKLAND`, `ONHIT` and `OFFHIT`; an unknown message answers
false and returns 0. The two wall checks run only while `_isHitWall` is set and answer false otherwise. `ONHIT` and
`OFFHIT` switch on or off the child of the sent info's check switch whose name equals the sent info name, looked up in
the info's name list (a string-object list or a named-object list).

- **`beHitLandModel_CheckWall`** probes a segment of 1.42 radii either side of the position along the direction, with
  two more segments a radius to either side. On a hit it moves the position back along the direction to the nearest
  wall the closer side probes find, then probes sideways three quarters of the reach ahead and pushes the position off
  the nearest wall along the wall's normal. It posts the hit's ram number and info name, the position and whether a wall
  was hit. An int of 1 in the message skips that check.
- **`beHitLandModel_CheckWallFull`** casts eight horizontal rays 45 degrees apart, 3.5 radii long from the position
  (2.15 radii when none hits), takes the nearest wall hit and pushes the position out of the wall along its normal,
  posting the same results.
- **`beHitLandModel_FindLand`** casts four vertical rays at the corners of the square of half-width radius around the
  position, picks the landing hit (the highest one inside the up/down window, else the highest below, else the lowest)
  and posts the result back.
- **`beHitLandModel_TraceOrder`** runs the order's rays through the check switch of every info whose kind the order
  asks for, visiting only the children whose bounds overlap the rays' XZ extent; `beHitLandModel_HitProc` is the
  traversal's hit callback, and `beHitLandModelOrder_AddHitResult` records each hit into the order.
  `beHitLandModel_UpdateBound` and `beHitLandModel_BoundsOverlapXZ` keep the larger or smaller bound of a pair and test
  the XZ overlap.

The order's `_kind` and each info's `_kind` are bit sets. An info is visited when `order kind & 0x1FF & info kind` is
nonzero, unless both carry `0x800`, and an order carrying `0x1000` visits only infos that carry it. An info carrying
`0x400` has `beCopyTransform` parts: each part's matrix is copied from its source transform and the part's bound is
translated by it before the overlap test.

## Open questions

- `beHitLandModel_OnMessage` queries the meta object of each info's name list while the order does not yet exist and
  discards the result; retail does exactly this and the source keeps it.
- The wall push of every wall check is `(reach - distance) * cos(angle between the normal and itself)`. The angle is
  zero, so the factor is 1; why retail computes it is not known.
- What the kind bits `0x400`, `0x800` and `0x1000` stand for beyond the handling above, and why the order's mask is
  `0x1FF`, is not known.
- `beHitLandModel_UpdateBound`, `_BoundsOverlapXZ` and `_HitProc` are named from what they do (medium confidence);
  `_CheckWall` and `_CheckWallFull` follow the messages that call them.
