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
to `HITLANDDELIVER` and handles ride-on floors (`beModelCtrlInfoRideOn_SetModel`, `_IsModel`).

## AI and Lua

`igObject::vfunc_38` runs `beModelCtrl_UpdateMapAI` (AIM property) or `beModelCtrl_UpdateHomingAI` (AIH,
`beModelCtrlInfoDataAIH`). `beModelCtrl_CallLua` fills the MDL globals (`g_mdlMatrix`, `g_mdlCallName`,
`g_mdlDmgTurn`, ...) and runs chunk `<function>_<info>.lua`.

## Messages

`beModelCtrl_GetMessageEnum` names the 33 messages (GENERATE ... GETSEQNAMELIST, enum `beModelCtrlMessage` in
the source). SETCONVEYOR, SETQUICKSAND and SETSLIPPEDFLOOR create ride-on records 2, 3 and 4.

## Open questions

- `beModelCtrl_UpdateHomingAI` and `beMeterCtrlNode_Traverse` are not decompiled; their names come from callers and strings.
- The shared constants at `0x4e0ef0` (identity matrix) and `0x4e1078/88/98` (unit axes) and `0x4c8fa0..0x4c8fb8` are still `DAT_`.
