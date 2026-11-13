# Viewer scene-info manager

`src/engine/igViewerSceneInfoManager.cpp` (unit `viewer_igViewerSceneInfoManager`, `0x460f90` up to `0x463560`, MWCC
`b52` `-O4,p -sdatathreshold 2 -inline level=8,bottomup`, exceptions off) is the Alchemy viewer's
`igViewerSceneInfoManager`, its controller, `igViewerAction`'s call, the stubs of `igViewerStatisticsManager` and
`igStatisticsItem`, and `g_viewerDisableFeatures`, which its static initialiser constructs.

The manager is an `igInfoManager`: Insight hands it each `igSceneInfo` it loads (`AddInfo`), it appends the scene graph
to `igViewerParameters._scene` and takes the scene's cameras, animation range and up vector, and every frame
(`Update`) it advances `_drawTime` through the parameters' loop mode and passes the frame time to its `igViewManager`.
`resetFields` (the slot `igObject_ResetFields` calls) copies the shared viewer options into the parameters, hands the
parameters to the view manager and renderers, and binds the hot keys:

| key or button | handler |
| --- | --- |
| `F` | `FitSelection`: `igViewManager_FitSelection` |
| `D` | `PrintViewMatrix`: prints the view matrix |
| `C` + `0xF` | `CenterSelection`: looks at the selection from where the eye is |
| `H` + `0xC` | `CycleGuiVisibility` |
| button 3 / 0 | `Play` / `Pause`: `_timeOperation` 1 / 0 |
| `R` + `0xA` | `ResetOperationMode` |
| `M`, `W`, `T` + `0xB`, `P`, buttons 1 and 2 | empty in retail |

Each binding is an `igViewerAction` holding the manager and a member-function pointer; the pointers are constants in
`.data` (`g_fitSelectionHandler` and its neighbours, `0x4d1ac8` up to `0x4d1b98`, 16 bytes each, the last being the
renderer's `g_viewerRendererResizeHandler`).

`igViewerSceneInfoManagerController::OnModelChange` is the view the manager installs on `igViewerParameters`: a change
names its field by the `igMetaField` handle `igViewerParameters_InitFields` fills (`g_igViewerParameters_<field>MetaField`,
`0x58c9f0` up to `0x58cb20`, one 8-byte slot per field, from the `igMetaObject_NameFields` handle table at `0x4d1180`),
and the controller dispatches it to the renderer (projection, view matrix, sorting, lighting, render states) or the
manager (operation mode, GUI, the optional renderers, playback).

`_operationMode` selects the view mode `ApplyOperationMode` installs: 0 `igPickMode`, 1 `igRotateMode`, 2 `igFlyMode`
on the Insight window, 3 `igRotateMode` with `_maya` set, and from `_firstCameraMode` on an `igCameraMode` following
the scene's camera of that index.

`g_sharedViewerOptions` (`0x56dc50`) is the 240-byte viewer options object every viewer object shares, created by
`ViewerOptions_Construct` on first use and freed when its count at `+232` drops to zero. Its members up to `+229` are
the `INSIGHT` properties `ViewerOptions_Construct` reads (`extraCommandLine`, `showBBox`, `autoSelectCamera`,
`upVector`, `showUI`, ...).

## Open questions

- The `igInfoManager` slot names `Deactivate`, `AddInfo`, `RemoveAllInfo` and `Update` are read from what the
  manager's overrides do; Alchemy's own names are not in the image. Slots 25 and 26 are empty and stay numbered.
- `OnModelChange` (igView slot 24), `igViewerAction::Execute` (igAction slot 23) and the empty handlers
  (`OnPlaybackChanged`, `OnSelectionChanged`, `OnDisablesChanged`, `OnCamerasChanged`, `OnSceneClipped`,
  `OnGuiShown`, `OnHotKey<key>`, `OnButton<n>`) are named from their caller or binding only.
- The slot-22 accessors (each class's metaobject) and the igView slot 23 overrides (an `igObject_IsKindOf` test of
  the model whose result is returned) keep their numbers.
- The member at `+236` of the shared viewer options is an interned string released with the object; what it holds
  is not traced. The options type duplicates `ViewerOptions_2382e0` in `src/engine/insight/InsightLibrary.h` and
  belongs in one shared header.
- The second word of a model change record is always 0 in this file; `flags` is a placeholder name.
