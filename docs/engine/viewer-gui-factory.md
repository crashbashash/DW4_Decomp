# Viewer GUI factory

`src/engine/igViewerGuiFactory.cpp` (unit `viewer_igViewerGuiFactory`, `0x45ec90` up to `0x45f200`, MWCC `b52`
`-O4,p -sdatathreshold 2`, exceptions off) is the Alchemy viewer's `igViewerGuiFactory`: the object the scene-info
manager asks for its menu actions and widgets, and the default colours of the colour changers it holds.

| function | what it does |
| --- | --- |
| `igViewerGuiFactory_CreateAction` | a new `igViewerAction` bound to an object and the member function to call on it |
| `igViewerGuiFactory_CreateEmpty` | the factory's answer for a widget kind it does not build: an empty reference |
| `Gap::Viewer::igViewerGuiFactory::resetFields` | the slot igObject calls after its fields are constructed or reset: gives each colour changer (menu back, menu item text, menu mark, icon back, big icon, big icon highlight, small on/off icon) its colour for every state, through `igBasicColorChanger_SetColor` or `igOnOffColorChanger_SetColor` |
| `Gap::Viewer::igViewerGuiFactory::vfunc_22` | the class's metaobject |
| `igVec2f_Set`, `igVec2f_Construct` | inline vector helpers the file emitted; nothing in retail calls them |

A colour changer keeps one colour per (highlighted, on) pair and one for disabled; `SetColor` takes the two flags,
the disabled flag and the colour. The seven colours are `.bss` vectors at `0x58d0e4` … `0x58d164`
(`g_viewerClearColor`, `g_viewerTextColor`, `g_viewerDisabledTextColor`, `g_viewerHighlightTextColor`,
`g_viewerSelectedColor`, `g_viewerBackColor`, `g_viewerHighlightBackColor`).

## Evidence

The range was already one unit; the file now holds `igViewerGuiFactory_CreateAction` too, which was compiled on its
own. It starts after `igViewerDataPumpManager` (`0x45ec90`) and the renderer's file follows at `0x45f200`.

## Open questions

- The colour names are guesses from which state each is given (the clear colour for marks and highlights
  that are off, text colours for item text and icons); nothing in the code writes the vectors, so their values
  come from elsewhere at run time.
- `resetFields` is the slot `igObject_ResetFields` and `igObject_ResetUnconstructedFields` call with one
  argument after resetting the fields; its Alchemy name is unknown.
