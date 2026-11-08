# Shared ListCtrl paging and chip-list presentation

Two complete helper groups: the three shared ListCtrl
methods at `40dae0..40de80` (916 bytes), and the contiguous XDATA-chip page/text
helpers at `43c720..43cc20` (1,280 bytes). Five bodies total **2,196 bytes**, with
**544 non-padding addresses /549 span words**; the other five words are zero padding.

All five bodies have **2,196 exact bytes**: initialization 260, previous
page 320, next page 336, chip page-count 208 and chip text 1,072. Matching source
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

## Matching source and restored extent

The two matched page methods use C++ `bool`, which reproduces the retail true
constants; C integer/long alternatives did not. Their input captures and page
logic remain C++. Original delay/padding NOPs and a local assembler-controlled
unconditional join preserve the unreachable alignment word between message
branches. Next-page return also retains the original-width register copy.
The count helper uses two original NOPs and balanced assembler scheduling
directives. Its per-unit `-O3,p` speed setting reproduces the retail combination
of ordinary remainder and constant-division multiplication.

Across the three matched bodies, explicit target instructions are two local join
branches, one return-register copy and14 original NOPs:68 bytes. The remaining
796 bytes are generated from C/C++ logic. This records the target-specific
projection without claiming an assembly-free or original-source spelling.
No opaque assembly replacement body is used.

The initializer follow-up also retains the original join and two
NOPs. Its single-page path needs the `i_stcursorright` address-high instruction
before the first coordinate load; ordinary C schedules those two words in the
opposite order. One explicit `lui a1,0x52` plus a compiler-coalesced `dmove`
connects the high address to the C name local. The copy emits no extra word;
C forms the low half (`0x520000 - 26000 = 0x519a70`). Vector copies, page test
and calls remain C. No post-compile byte edits or custom compiler flags are used.
Relocation-aware verification matches all65 words; object disassembly confirms
the two original instruction positions. Source presence was checked through
`units.scan`, including merged definitions, before assigning new credit.

The initializer adds four explicit target words /16 bytes (one LUI, one join,
two NOPs), with244 bytes generated from C. Across all four matched helper bodies,
explicit instructions total84 bytes and C/C++-generated code totals1,040 bytes.
The three-body accounting above covers the two page methods and the chip count only.

The text matching follow-up uses full-width flags/status/NEXTX results,
reflected fields and a four-byte font-pointer stride. Explicit binding pseudos
keep the original saved-register allocation; twelve `dmove` bindings coalesce
without introducing extra instructions. This is a code-generation projection,
not a recovered original declaration. Unspecified callee argument lists retain
the retail call setup; fully prototyped candidates changed argument/delay-slot
ordering and were not banked. Observed result widths remain explicit.

Its five-byte `----` copy preserves FPU-word/byte loads and stores through ordered
C accesses. One fallback-address LUI and two TEXTCTL-address LUIs retain the
original positions. Page-label arithmetic consumes full words before the byte
stores. Unsigned grouped subtraction preserves wrapped description indexing and
the original ADDU operand order. No new stale-field clearing or index guards
were added. Padding is placed inside the relevant branch so false branches skip
it at the original destination.

The text body retains two original joins, eleven NOPs and three LUIs:64 explicit
target bytes, with1,008 bytes generated from C. Across all five helpers the total
is148 explicit target bytes and2,048 C/C++-generated bytes. Relocation-aware
verification checks all268 text words /115 relocations. No post-compile patching,
custom flag or opaque assembly replacement is used.

The [item/database lookup checkpoint](item-database.md) now explicitly
recovers the adjacent wrappers' value returns and status forwarding, preserving
their matched bytes. Database delivery/loading and full transaction
acceptance remain separate boundaries.

The text helper's previous1,064-byte split used Ghidra's occupied-byte sum and
cut off `jr ra` at43cc18 and its delay slot at43cc1c. Generated reviewed extents
restore the full1,072-byte span through43cc20. This adds **8 classified code
bytes**, with no image change. The other four reviewed spans were already full.
The new regression checks the final instructions and rejects losing the return.

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
