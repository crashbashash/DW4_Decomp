# Shared ListCtrl paging and chip-list presentation

Two complete helper groups: the three shared ListCtrl
methods at `40dae0..40de80` (916 bytes), and the contiguous XDATA-chip page/text
helpers at `43c720..43cc20` (1,280 bytes). Five bodies total **2,196 bytes**, with
**544 non-padding addresses /549 span words**; the other five words are zero padding.

The five bodies are initialization 260, previous
page 320, next page 336, chip page-count 208 and chip text 1,072. Source
lives in the
[C-mode initializer](../../src/game/beNDMWListCtrl.cpp),
[C++ page methods](../../src/game/beNDMWListCtrl.cpp),
[chip count](../../src/game/beNDMWShopCtrlXdataChip_UpdatePageCount.c) and
[chip text](../../src/game/beNDMWShopCtrlXdataChip_RefreshText.cpp).
The primary7,232-byte chip transaction update is documented
[separately](chip-controller.md).

## Fields and inherited interface

Reflection identifies ListCtrl's own `_nowPage`84, `_maxPage`88 and `_cursor`92.
It inherits messenger12, pad manager16, player20 and return code48 from Window.
The chip class adds `_itemBaseList`96. Its concrete table `53f870` selects these
ListCtrl methods through raw byte offsets96/100/104. The chip update calls those
slots and the two direct chip helpers; the existing dependency proof records
the original sites. The shared virtual-slot names retain their existing owner
overlay; the two body-derived chip helper names come from the owning generator.
No original C++ declaration spelling is claimed.

## Arrow initialization and page requests

Initialization copies the supplied left vector and presents `i_stcursorleft`
with `SQ_HIDE` and queued `SQ_CLOSE`. It then reads the **current** maximum page
count after that callback. Right coordinates are copied afterward, preserving
callback changes. It presents `i_stcursorright` with `SQ_SELECT` when maximum>=2,
otherwise `SQ_HIDE`, also queuing `SQ_CLOSE`. Only the three supplied float words
are copied; the unused fourth local word is not initialized. It does not reset
page or cursor state itself.

The page helpers obtain the actual player pad record. Their horizontal tests are:

| Request | Input words28/32, ORed | Input words72/76, ORed |
| --- | --- | --- |
| Previous | bit8 | bit0x80 |
| Next | bit2 | bit0x20 |

Either source can request the direction. Both helpers reject it when input word36
has bit1 or bit4. Previous requires page>0; next requires page<the original wrapped
`maxPage-1`. They change page by one and return true when that branch runs.
There is no active-state test, cursor reset or animation wait in these bodies.

The moving arrow receives `SQ_MOVEEND` at its new end boundary, otherwise
`SQ_MOVENEXT`; the opposite arrow receives `SQ_SELECT`. The messenger is reloaded
for each request. Callback changes to page/messenger do not undo the already
captured true return or suppress the opposite-arrow request. The caller controls
when these helpers run; their masks do not by themselves establish physical-pad
or disabled-input behavior.

## Chip page count and twelve text rows

UpdatePageCount reads the item-list count, sets maximum pages to signed
`count/12 + (count%12 != 0)`, then **re-reads** the list count after that store.
It computes wrapped remaining=`count-page*12`, uses12 when remaining>=12 or the
signed remainder otherwise, and clamps that result to at least1. Thus the helper
returns1 even for an empty page. The main controller's empty-list policy is a
separate branch, not an extra guard added here.

RefreshText first looks up the status context, even when both refresh flags are
zero. Its flags use the full incoming register value. Row refresh iterates twelve
fonts from table `4cf8a0`, recomputing the live page/list/count for every row.
A non-null in-range item is queried for `NAME` and numeric `NEXTX`, then sent to
TEXTCTL: name in STWINFONT14, next-X-data value in STWINFONT17, both switched on.
A NEXTX value below1 displays `----`; otherwise the original `%d` formatter
receives that value. The threshold uses the full64-bit result while formatting
uses its low32-bit integer.

Out-of-range rows switch both fields off. **An in-range null item leaves both
old fields unchanged**, including their visibility. Page labels in STWINFONT30
are single characters: current page+'1' and maximum pages+'0'. This preserves
character wrapping and punctuation above9, rather than introducing decimal
formatting.

Description refresh uses `page*12 + returnCode48`, not `_cursor`92. A non-null
in-range item is queried for `TXT`, written to STWINFONT29/font000 and switched
on. Invalid/null selections leave the old description. The body has no independent
negative-index guard. Status context is captured once; font cells and messenger
are reloaded around callbacks. Item/property/model/text services remain explicit
boundaries; this code displays values and does not compute costs or debit XDATA.

## Source shapes and extent

The two page methods use C++ `bool`, and the source of all these helpers is C and C++ with no `asm`.
The chip text helper uses full-width flags, status and NEXTX results, reflected fields and a four-byte
font-pointer stride. Unspecified callee argument lists keep the retail call setup, and fully prototyped
candidates change argument and delay-slot ordering. These are call-site projections, not recovered
callee types. Subtracting a negation in the description index keeps the retail `addu` operand order. No
new stale-field clearing or index guards were added.

The [item/database lookup](item-database.md) covers the adjacent wrappers'
value returns and status forwarding. Database delivery/loading and full transaction
acceptance remain separate boundaries.

The text helper's full span is1,072 bytes, through43cc20. Ghidra's occupied-byte
sum gives1,064 and cuts off `jr ra` at43cc18 and its delay slot at43cc1c; the
reviewed extents hold the full span. A regression checks the final instructions
and rejects losing the return.

```sh
python3 -m unittest discover -s tools -p test_function_extents.py
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

Next: connect the item
lookup chain to actual child/pricing/stat/XDATA outcomes, then close remaining
selector/window/service boundaries. The [full hub goal](../systems/hub-recovery.md)
remains unfinished.
