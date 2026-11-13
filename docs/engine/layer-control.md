# Layer control (`beLayerCtl`)

`beLayerCtl` ([`src/game/beLayerCtl.cpp`](../../src/game/beLayerCtl.cpp)) splits a stage's scene into named
layers that scripts and controllers show, hide and fetch by name. It registers with the messenger under the
`LAYERCTL` group (`beLayerCtl::RegisterReceiver`); its info class is `beLayerInfo`
(`beLayerCtl::GetInfoMeta`), whose `_groups` is a `beLayerGroupList` of `beLayerGroup` names. The per-frame
`beLayerCtl::Update` is empty: everything happens in `beLayerCtl::OnMessage`.

## Fields

| Field | Use |
| --- | --- |
| `_isOrdered` | set once ORDER has built the layer switch; cleared by `beLayerCtl::ReleaseLayerSwitch` |
| `_layerSwt` | the `igSwitch` named `LayerSwt` whose children are the layers |

`beLayerCtl::ReleaseLayerSwitch` removes the switch's children one at a time from index 0
(`igSwitch_RemoveChildAt`), releases the switch and clears both fields.

## Messages

The message is resolved against the `Message` enum (`beLayerCtl_GetMessageEnum`): ORDER, SWITCH, REMOVE,
GETNAMELIST, GETLAYERNODE, INFO (0..5). A layer is addressed by the name of a child of the layer switch.

- **ORDER.** The scene root is the `_scene` of the viewer parameters of the `igViewerSceneInfoManager`. On the
  first ORDER the controller creates `LayerSwt` (allocator from `g_ndmwAllocatorSelector` unless
  `g_useOwnerAllocator`) and attaches it under the root's `igLightStateSet` child, or under that child's
  `LAYERPARENT` child when one exists; with no light state set ORDER returns 0. Every ORDER then appends one
  `igGroup` per `beLayerGroup` of the info, named after it, and a final `NONE` group
  (`igGroup_CreateInstance`, `igSwitch_AppendChild`). Each root child other than `ROOTATTR` and the light
  state set (an unnamed child is first named `NONE`) moves into the layer of the same name, or into `NONE`,
  and is removed from the root (`igGroup_RemoveChild`). Replies true.
- **SWITCH** *layer*, *control*. *control* is resolved against the `SwtCtl` enum
  (`beLayerCtl_GetSwtCtlEnum`): `CLR`/`DISPOFF` 0 disables, `SET`/`DISPON` 1 enables, `FLIP` 2 toggles the
  layer's bit in the switch's `_childMask`. The layer name `ALL` applies 0 or 1 to every layer
  (`igSwitch_DisableAllChildren`, `igSwitch_EnableAllChildren`); FLIP does nothing there. Fewer than two
  strings return 0.
- **REMOVE** *layer*: removes that layer from the switch.
- **GETNAMELIST**: appends every layer name as a string.
- **GETLAYERNODE** *layer*: clears the reply objects, appends the layer's group and true.
- **INFO**: no action.

Every message but a failed ORDER or a short SWITCH, REMOVE or GETLAYERNODE returns 1.

## Open questions

- `FUN_001c5d10` appends a child to an `igGroup` (it calls the child list's append virtual); its name waits on
  a rename that touches the scene-graph library's callers.
