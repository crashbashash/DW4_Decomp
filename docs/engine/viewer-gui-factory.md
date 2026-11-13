# Viewer GUI factory

`src/engine/igViewerGuiFactory.cpp` (unit `viewer_igViewerGuiFactory`, `0x45ec90` up to `0x45f200`, MWCC `b52`
`-O4,p -sdatathreshold 2 -inline level=8,bottomup`, exceptions off) is the Alchemy viewer's `igViewerGuiFactory`: the object the scene-info
manager asks for its menu actions and widgets, and the default colours of the colour changers it holds.

| function | what it does |
| --- | --- |
| `igViewerGuiFactory_CreateAction` | a new `igViewerAction` bound to an object and the member function to call on it |
| `igViewerGuiFactory_CreateEmpty` | the factory's answer for a widget kind it does not build: an empty reference |
| `Gap::Viewer::igViewerGuiFactory::resetFields` | the slot igObject calls after its fields are constructed or reset: gives each colour changer (menu back, menu item text, menu mark, icon back, big icon, big icon highlight, small on/off icon) its colour for every state, through `igBasicColorChanger_SetColor` or `igOnOffColorChanger_SetColor` |
| `igViewerGuiFactory_GetMeta` | slot 20: the class's metaobject |
| `igVec2f::set`, `ViewerRect::ViewerRect` | out-of-line copies of the inline setter of `igVec2f` (`dw4/igMath.h`) and the inline constructor of the file's two-`igVec2f` cell; only the file's static initialiser calls them |
| `__sinit_igViewerGuiFactory.cpp` | constructs `g_viewerGuiStyle` (`0x58ced0`, 692 bytes): 28 `ViewerRect` cells, three `igVec3f`, twelve floats and ten `igVec4f` colours, in member order, then runs the constructor body that sets them |

A colour changer keeps one colour per (highlighted, on) pair and one for disabled; `SetColor` takes the two flags,
the disabled flag and the colour. The colours are members of `g_viewerGuiStyle` (`clearColor`, `textColor`,
`disabledTextColor`, `highlightTextColor`, `selectedColor`, `backColor`, `highlightBackColor`); the static
initialiser gives them their values. Members no retail code reads keep their offset as name (`f612`, `f628`,
`f676` for the other three colours, `fNN` for the cells, vectors and floats); a `ViewerRect` is a `corner` and an
`extent`.

The `ViewerGuiStyle` constructor is expanded into the initialiser, with its 110 inline member constructors and setters
left as calls ([build profiles](build-profiles.md), "Alchemy builds bottom-up"). The copies of the `igVec3f`
and `igVec4f` constructors and setters the linker kept are in other units: `0x19ace0`, `0x1ae1a0` and `0x1ae1b0`
in `SceneGraphLibrary`, and `0x151090` in `GfxLibrary`. The row lists them under `duplicates`.

## Evidence

The range was already one unit; the file now holds `igViewerGuiFactory_CreateAction` too, which was compiled on its
own. It starts after `igViewerDataPumpManager` (`0x45ec90`) and the renderer's file follows at `0x45f200`.

## Open questions

- The colour names are guesses from which state each is given (the clear colour for marks and highlights
  that are off, text colours for item text and icons).
- `ViewerGuiStyle`, `g_viewerGuiStyle` and `ViewerRect` (with its `corner` and `extent`) are descriptive names. The
  cell values look like (corner, extent) rectangles of a 128×128 icon sheet: every corner plus extent is at most
  128. Neither the PS2 nor the Xbox build (`0x3bae50`, built by `0x18fc20`) reads a cell: their only readers of
  the style are the static initialiser and `resetFields`, which reads colours.
- `resetFields` is the slot `igObject_ResetFields` and `igObject_ResetUnconstructedFields` call with one
  argument after resetting the fields; its Alchemy name is unknown.
