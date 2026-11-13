# beFont: text nodes

`beFont` (`src/game/beFont.cpp`) draws message text into the layer scene graph. A stage's layer controller
owns the scene graph; each beFont is registered with the messenger under the `TEXTCTL` group
(`Gap__Bec__beFont__vfunc_29`) and is driven entirely by messages.

## State and messages

The font's work object is a `beBaseInfoRam`: `_parentInfo` is the `beFontInfo`, `_st0` the load state
(0 waiting for INITIALIZE, 1 ready, 10000 failed; `_st1`..`_st3` are cleared on every change). Messages
are resolved against the `Message` enum (`beFont_GetMessageEnum`), in this order:

| Value | Message | Arguments | Effect |
|---|---|---|---|
| 0 | INITIALIZE | none | Asks the layer controller (`LAYERCTL`, `FONT`, `GETLAYERNODE`) for the font's igGroup, keeps its first child attribute set as `_root`, and pairs every panel of every category with a new igGeometryAttr (`beFontGeomAttrPair`, in `_gaPairList`). Any missing piece sets the failed state. |
| 1 | TEXTSET | data, set, then a string, an index into `beFontInfo::_unicodeList`, or an object | Builds the text geometry of every selected layout entry. A null string or an object that is not a beUnicodeObj shows the placeholder `からっぽ` ("empty"). |
| 2 | ALIGN | data, set, `Align` enum name | Stores the alignment in each entry's `_align`. |
| 3 | SWITCH | data, set, `SwtCtl` name or integer | Shows or hides each entry's panel (`_tbitNo` in its category switch) and category (`_cbitNo` in the root switch), then hides every category with no visible panel and shows every category with one. |
| 4 | SETPOSITION | data, set, vector | Sets the translation of each entry's igTransform. |
| 5, 6, 7 | COLOR, DEFAULTCOLOR, CANCELCOLOR | data, set, colour for COLOR | Sets the RGB of every igColorAttr of each entry (DEFAULTCOLOR 0.9 grey, CANCELCOLOR 0.5 grey), keeping alpha. |
| 8 | REPLACEUNKNOWN | beUnicodeObj, character | Replaces every character the first font image has no glyph for. |

## Layout entries

`beFontInfo::_dataList` holds one `beFontInfoData` per text slot: `_name`, the attribute set it draws
into (`_attrSet`), its switch bits, `_width`, `_align` and `_kind` (the name of the font image to use).
`beFont_FindFirstLayoutEntry` interns the data and set names into `_condition00`/`_condition01` and
restarts `_history`; `beFont_FindNextLayoutEntry` returns the next entry whose name and attribute-set
name match, or every entry with that set name when the data name is `ALL`.

## Building text

`beFont_SetText` accepts an igStringObj, converted from Shift-JIS by `beFont_ConvertToUnicode`, or a
beUnicodeObj. The conversion keeps only characters found in the 425-row Shift-JIS to UTF-16 table
(`g_sjisToUnicodeTable`, ended by a 0xffff row), drops carriage returns and keeps a line feed once text
has started. The font image is chosen by name (`beFont_FindFontIndex`, the first image when none
matches). `beFont_PrepareGeometry` sizes the entry's igGeometryAttr as a triangle list from
`beFontImage_CountTrianglesWide` (two triangles per drawable character) and replaces a missing or short
vertex array (`beFont_ReplaceVertexArray`). The font image writes the glyph quads, and
`beFont_LockVertexArray` locks positions and texture coordinates. `beFont_LayoutLines` then moves each
quad onto its line, recording the vertex where each line ends in `_lineFeedList` and the line's width
in `_alignList`; for right (1) or centre (2) alignment `beFont_AlignLines` shifts each line against the
entry's `_width`. The new geometry replaces the one in the entry's attribute set, and the pair keeps
the previous one as its spare.

`beFont_AddFontImages` is how the file-list manager hands a loaded igNamedObjectInfo to the font: every
beFontImage among its objects is appended to `_fonts`.

## Open questions

- `igVertexArrayLock` (the seven-word record `igVertexArrayLock_Init` clears and the vertex array's lock
  slot fills) has guessed member names; only the component, count, data and stride words are confirmed by
  use.
- `beFontImage_CountTriangles` and `beFontImage_CountTrianglesWide` sum `beFontImage`'s slot 23 over a
  string, but sit in the GUI block of the image, away from the other beFontImage methods.
- `g_emptyTextPlaceholder` is named for its use; its text is the Shift-JIS `からっぽ`.
