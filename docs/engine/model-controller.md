# Model controller

`src/game/beModelCtrl.cpp` (unit `bec_beModelCtrl`, `0x3902f0`-`0x398e4c`) holds `beModelCtrl`: the per-frame
update of every model ram (`igObject::vfunc_31`), its command list and its message handler
(`beModelCtrl::vfunc_33`). The file also emits the `beMeterCtrlNode` traversal registration
(`beMeterCtrlNode_TraversalFunction`, `beMeterCtrlNode_RegisterTraversalFunction`).

## Command list

`beModelCtrl_RunCommands` walks the `beModelCtrlData` command list of the current sequence from `_comIndex`
and dispatches on each command's meta object: `beModelCtrl_RunCtrl` (CTRL), `beModelCtrl_RunAction` (ACTION),
`beModelCtrl_RunMove` (MOVE, MOVEEX, MOVERL), `beModelCtrl_RunPdMove`, `beModelCtrl_StartWaitCheck` (WCHECK),
`beModelCtrl_RunHitBox`, `beModelCtrl_RunMuteki`, `beModelCtrl_RunLabelCtrl`, `beModelCtrl_RunLuaCall`,
`beModelCtrl_RunAiMap`, `beModelCtrl_RunMsgBox`, LABEL (stops once per label) and `beModelCtrl_RunJump`.
A command returning 0 stops the walk; JUMP leaves `_comIndex` to the new sequence.

## Movement

Four `beModelCtrlMoveObject`s per work (`beModelCtrlMoveObject_Start`/`_Stop`/`_Step`); `beModelCtrl_ApplyMoves`
moves the node matrix by them, `beModelCtrl_UpdateDirection` steps `_direction` toward `_targetDirection`,
`beModelCtrl_QueryMove` answers the wait checks, `beModelCtrl_CheckWallAndFloor` sends HITWALL / HITFLOORCHECK
to `HITLANDDELIVER` ([hit and land checks](hit-land.md)) and handles ride-on floors
(`beModelCtrlInfoRideOn_SetModel`, `_IsModel`).

## AI and Lua

`igObject::vfunc_38` runs `beModelCtrl_UpdateMapAI` (AIM property) or `beModelCtrl_UpdateHomingAI` (AIH,
`beModelCtrlInfoDataAIH`). `beModelCtrl_CallLua` fills the MDL globals (`g_mdlMatrix`, `g_mdlCallName`,
`g_mdlDmgTurn`, ...) and runs chunk `<function>_<info>.lua`.

## Messages

`beModelCtrl_GetMessageEnum` names the 33 messages (GENERATE ... GETSEQNAMELIST, enum `beModelCtrlMessage` in
the source). SETCONVEYOR, SETQUICKSAND and SETSLIPPEDFLOOR create ride-on records 2, 3 and 4;
`beModelCtrlInfoRideOn4_Move` is record 4's move step. `beModelCtrl__OnGenerateFromParent` is the generate handler for
a model placed on a parent model, which the bullet and effect controllers call where other models call
`beModelCtrl__OnGenerate`: it reads the parent's name and ram number, an offset and an optional rotation in radians
from the message, asks the parent for its matrix (MODELCTRL / GETMATRIX) and sets the node matrix from them.

## Meter nodes

`beMeterCtrlNode_Traverse` is the meter node's traversal function: it runs the node's children once per entry of the
time list, each time with the matrix translated by the node's number offset; a plain node pushes the first time only.

## Open questions

- `beModelCtrl_UpdateHomingAI` selects
  the nearest `PLAYER` target when the info's `_kindString` is `KIND_EBULLET` and the nearest `ENEMY` otherwise, then
  reads the target's distance, origin and position; what each homing mode does with them is not read here.
- The shared constants at `0x4e0ef0` (identity matrix) and `0x4e1078/88/98` (unit axes) and `0x4c8fa0..0x4c8fb8` are still `DAT_`.
