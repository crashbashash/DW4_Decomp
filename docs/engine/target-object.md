# Target object (`beTargetObj`)

`Gap::Bec::beTargetObj` answers one question for model controllers: which actor should this model aim at.
Its source is `src/game/beTargetObj.cpp` (unit `bec_beTargetObj`, `0x3a59d0`–`0x3a694c`).

## State

The scene holds one target object. Slot 23 (`Gap::Bec::beTargetObj::vfunc_23`) finds it, and the scene's
`beMessenger`, through the insight and stores them in `g_targetObj` and `g_targetMessenger`.

The reflected fields hold three candidate lists:

| Field | Type | Holds |
|---|---|---|
| `_playerPosList` | `igVec3fList` | player positions |
| `_playerRamNoList` | `igIntList` | each player's RAM number, parallel to the positions |
| `_enemyPosList` | `igVec3fList` | enemy positions |

Slot 26 empties the three lists (reserving storage when they have none) and slot 27 empties them without
touching storage. The lists fill lazily: the first query after they are emptied calls
`beTargetObj_GatherPositions`, which sends a messenger group (`PLAYER` with `GETMATRIX`, or `ENEMY` with
`GETMATRIX_ACTIVE`) and appends the translation of every matrix the actors return, plus each player's
RAM number from `beMessenger_GetInt`.

The result of the last query lives in file-scope globals:

| Global | Meaning |
|---|---|
| `g_targetOrigin` | the asking model's position (translation of its matrix) |
| `g_targetOriginMatrix` | the asking model's matrix, an `igMatrix44f` the file defines and its static initialiser (`0x521730`) sets to the identity at start-up |
| `g_targetOriginHeading` | yaw of the matrix's forward axis; `-100` until first asked for |
| `g_targetPosition` | the chosen target's position |
| `g_targetDistanceSq` | squared distance from origin to target |
| `g_targetRamNo` | the chosen player's RAM number (0 for enemies and fixed points) |

## Queries

`beTargetObj_SelectTarget(matrix, group, mode)` records the origin, then targets the `PLAYER` or `ENEMY`
group (`beTargetObj_TargetPlayer`, `beTargetObj_TargetEnemy`). Mode `NEAR` picks the candidate with
the least squared distance (`beTargetObj_FindNearest`); any other mode picks the one whose bearing is
closest to the origin's heading (`beTargetObj_FindFacing`, angle difference folded into `[0, 2π]`). It
returns 0 when the group is unknown or has no members.

`beTargetObj_SetTarget(matrix, position)` sets the origin and a fixed target position directly.

The getters `beTargetObj_GetOrigin`, `beTargetObj_GetOriginHeading`, `beTargetObj_GetTargetPosition`,
`beTargetObj_GetTargetDistanceSq` and `beTargetObj_GetTargetRamNo` read that state;
`beTargetObj_GetTargetBearing(offset)` returns `offset + atan2(target.x - origin.x, target.z - origin.z)`.
`beTargetObj_GetPlayerCentre` averages up to four player positions; `Gap::Bec::beShadow01::vfunc_31` calls it.

The callers are the model controller's target-direction command (`beModelCtrl.cpp`, which passes the
entry's `_targetType` as the mode) and the player model (`beNDMWMdlPlayer2.cpp`).

## Open questions

- The heading uses the vector at `0x4e1098` as the forward axis; it is zero in the image and is filled at
  run time. It is likely the unit Z axis (the model controller also rotates about it by a Z angle) but is
  shared by seven units and stays a `DAT_` name until that is confirmed.
- `igInsightCore_AddToScheduler`, `igInsightCore_RemoveFromScheduler` (slots 21/22) and `igInsightCore_FindManager` (slot 23) are insight calls that
  register, unregister and look up an object by meta-object; they belong to the insight's own unit.
