# Model-controller node and sub-commands

`src/game/beModelCtrlSC.cpp` (unit `bec_beModelCtrlSC`, `0x398e50`-`0x39a930`) holds two things: the
traversal of a `beModelCtrlNode2`, and the timed sub-commands (`beModelCtrlSCHitBox`, `beModelCtrlSCEffect`,
`beModelCtrlSCSound`) a model command list queues on a `beModelCtrlSubCom`. Every function in it matches
under the unit profile.

## The node traversal

`beModelCtrlNode2_RegisterTraversalFunction` registers `beModelCtrlNode2_TraversalFunction` for the class
(meta object from `beModelCtrlNode2_ResolveMetaObject`), the same shape as `beNodeAnim` in `bePadData.cpp`.
`beModelCtrlNode2_Traverse`:

1. reads the traversal time (virtual slot 24) and converts it with `beModelCtrlNode2_LocalTime`:
   `(now >> 18) * _timeScale`, shifted back by 18, plus `_timeBias`; stores it in `_time`;
2. takes an `igModelViewMatrixAttr` from the traversal's `_matrixPool` set to the node's `_m` times the
   top of the model-view stack, and an `igTimeAttr` from `_timePool` holding the local time, and pushes
   both on their attribute stacks (slot = `_cachedUnitID` + index table[`_cachedAttrIndex`]);
3. pushes each attribute of `_overrideAttrList`, traverses the children, pops them in reverse;
4. pops the two attributes through each stack's `_popProc`, then ends the time (slot 31).

`beModelCtrlNode2_LocalTime` is also the node clock `beAction2` reads.

## Sub-commands

A `beModelCtrlSubCom` keeps its commands in `_comList`. Each command derives from
`beModelCtrlSubComBase` (`_isOneSet`, `_runFrame`, `_startFrame`); its virtual slots are 20 meta object,
21 start, 22 update, 23 stop.

| Function | Role |
|---|---|
| `beModelCtrlSubComBase_Update` | adds the system frame time to `_runFrame`; at `_startFrame` sets `_isOneSet` and calls start, afterwards update; returns 0 when the command is done |
| `beModelCtrlSubCom_Update` | updates every command, releasing and removing the finished ones |
| `beModelCtrlSubCom_StopAll` | calls stop on every command (an effect only when `_isSeqDead`), then releases and clears the list |
| `beModelCtrlSubCom_StopType` | stops and removes every command whose meta object is the one given (`beModelCtrl` passes `beModelCtrlSCHitBox`'s) |
| `beModelCtrlSubCom_AddEffect` | creates a `beModelCtrlSCEffect` (`beModelCtrlSCEffect_Create`), interns model and sequence names, copies offset, rotation, the two flags and the start frame |
| `beModelCtrlSubCom_AddHitBox` | creates a `beModelCtrlSCHitBox` from a `beModelCtrlHITBOX` command: start, end (`_start + _length`, or never for -1), offset, size, kind and bullet mode |
| `beModelCtrlSubCom_AddSound` | creates a `beModelCtrlSCSound` with an interned sound name and start frame |

The bullet mode comes from `_kind / 10000`: 6 is mode 1, 7 and 8 mode 2, 0 is mode 2 from kind 1000 on,
everything else mode 0.

### Hit box (`Gap::Bec::beModelCtrlSCHitBox`)

Start (`vfunc_21`) builds an `igAABox` of `_boxSize` around `_offset`, moves it into the owner node's
matrix (the `ONE` entry of the owner ram's data list, a `beModelCtrlInfoRamData`), draws it through
`beModelCtrl_DrawDebugHitBox` when `beModelCtrl._isDebugHitBox` is set (colour per bullet mode from
`g_hitBoxDebugColors`; the retail function is empty), and sends kind, box, node matrix and owner (or the
work's `_hitParentName`/`_hitParentRamNo`) to receiver group `HITPLAYERBULLET`, `HITPLAYERTALK` or
`HITENEMYBULLET` with message `CHKBULLET`. A hit reported back runs the owner's `_luaBHit` Lua function
(`BHit`). Update (`vfunc_22`) repeats start until `_endFrame`.

### Effect (`Gap::Bec::beModelCtrlSCEffect`)

Start asks `MODELCTRL`/`FIND_SPACE` for a free model named `_modelName`, keeps its ram number in
`_geneRamNo`, and sends it `GENERATE` with the owner, `_seqName`, the hit parent, offset, rotation and
`_isPositionLock`. A dead-by-itself sequence (`_isSeqDead`) finishes the command at once. Stop sends
`SQ_ERAS` to the gene model once started.

### Sound (`Gap::Bec::beModelCtrlSCSound`)

Start sends `SOUND`/`PLAY` with `_sndName` and keeps the returned handle in `_sndHandle` when it is valid
(not 0 or -1, type 4). Stop sends `SOUND`/`VOLUMECTL` `DOWN` with the handle.

## Open questions

- `beModelCtrlSCHitBox` start lays its blocks out with `goto`s (offset, node space, size, send); no
  structured spelling has reproduced the retail block order yet.
- `beModelCtrlNode2_Traverse` reads `_overrideAttrList` through an inline accessor only in the first
  loop test; spelling every read the same way moves one load and changes the register allocation.
- Mode 0 and mode 2 receiver groups are named for who is hit (`HITPLAYERBULLET`, `HITENEMYBULLET`); which
  side fires them is not confirmed in game.
