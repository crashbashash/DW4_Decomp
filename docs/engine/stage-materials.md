# Stage materials and world textures

How world stages carry their materials and bind textures to meshes, as read from the live scene graph and the packs.

## World material sets

World material sets are live-built attr sets and carry no material colour: `BGGround00n` and `BGObj00n` have no
`igMaterialAttr` or `igColorAttr`, and `BGGround00s`, `BGObj00s` and `wall01z01` hold only a texture bind. `BGGround00n` sets
blend enabled (`igBlendFunctionAttr` `_src` 4, `_dst` 5), culling off, depth write off and the texture matrix state on;
`BGObj00n` is the same with `_dst` 1. Per-mesh variation in the frame therefore has no material-colour source, so a renderer
has none to recover.

## Texture binding

A world material's texture is bound per shape, not per set. Each `beTextureCtrlAttr` carries one texture and one shape list,
resolved to pack attributes by `(primType, numPrims)`:

| Material | Texture | Shapes |
| --- | --- | --- |
| `BGGround00n` | `P11G00n` | 21835, 3190, 3194, 21732, 21833 |
| `BGGround00n` | `P10G00n` | 3192 |
| `BGGround00n` | `P10G02n` | 21721 |
| `BGGround00s` | `P11G00s` | 8533, 41789, 49587 |
| `BGGround00s` | `P10G00s` | 8391 |

`P11G00n` (green-grey rock) and `P10G00n` (dark grey rock) are separate atlases, not variants. A key shared by materials that
disagree on the texture, such as the UI and prop shapes on (4,1), (4,2), (4,24) and (4,25), is not resolved this way. The shape
list's addresses are not the geometry attrs; reach those through the shape's own attr list.

## Goblin Pass ground meshes

The large unnamed Goblin Pass ground meshes (`NDMW.AFS:614` ids 21721, 3190, 21833, 21732, 8533, 21835) have no live
`igGeometry` attr and no `igVertexArray`. Their vertex bytes appear only in the staged region `0x00ca0000-0x00d20000`, with no
object pointer to them, so a walk of the material graph never joins them to a texture. The staged records
(`6801800N... 30024000 fffff412`) are copies of a rodata template at `0x490e40`.

## Texture upload

`p2LoadTexture` (`0x20c270`) is called by `igSetRenderDestinationAttr` (`0x140060`), `FUN_0017a7e0`, `FUN_0017b5f0`,
`FUN_001ea430` (a GS bitfield builder writing `*(0x562D88)`) and `igPsx2VisualContext_vfunc_49` (`0x169840`).
`igPsx2VisualContext._pTexList` (+0x144) is a table of 0x88-byte VRAM descriptors, 47 entries in the measured frame, with
`igTextureAttr` at +0x30 and width/height at +0x20/+0x24.
