/* True when the open queue is empty. _openDataList (+0x14) is a beLoadIntf2ComMdlDataList whose
 * _count (+8) is tested. */
#include "dw4/reflected.h"
int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *self) {
    return ((beLoadIntf2ComMdlDataList *)self->_openDataList)->_count <= 0;
}
