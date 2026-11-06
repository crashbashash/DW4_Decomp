/* BeNDMWPanelWazaInfoWork accessor, returns _textColorList (+44). Receiver evidence: both callers
 * (beNDMWPanelWaza::vfunc_31, beNDMWPanelWazaInfoWork::vfunc_16) pass the Work object, and
 * reflection has _textColorList (igObjectRefMetaField, 4 bytes) at +44. */
#include "dw4/reflected.h"

int FUN_003cc480(beNDMWPanelWazaInfoWork *p)
{
    return p->_textColorList;
}
