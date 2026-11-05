#include "dw4/reflected.h"
/* 0x003ecb70 — beNDMWLoadIntf2MesWin__GetIsCtrl. MESWIN accessor: reads the _isCtrl flag (+34), the byte
 * FUN_003ecae0/FUN_003ecb00 set to 1 when a choice/continue message opens. */
unsigned char beNDMWLoadIntf2MesWin__GetIsCtrl(beNDMWLoadIntf2MesWin *p)
{
    return p->_isCtrl;
}
