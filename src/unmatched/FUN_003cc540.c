#include "dw4/reflected.h"
/* 0x003cc540 — FUN_003cc540. Receiver is beNDMWPanelWazaInfoWork (both callers,
 * Gap__Bec__beNDMWPanelWazaInfoWork__vfunc_16 and beNDMWPanelWaza__vfunc_31, pass it);
 * +40 is _textSetList (an arena/object ref, 4-byte handle). */
int FUN_003cc540(beNDMWPanelWazaInfoWork *p)
{
    return p->_textSetList;
}
