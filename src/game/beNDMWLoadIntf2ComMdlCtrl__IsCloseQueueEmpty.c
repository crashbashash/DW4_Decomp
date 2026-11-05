/* 0x003e44d0
 * True when the close queue is empty (cm_close_empty): the COMMDLCTRL record's
 * _closeDataList (an igObjectList) has no entries.
 * Shared by the LoadIntf2 and SaveIntf screens (identical ComMdlCtrl layout). */
#include "dw4/reflected.h"
int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *self) {
    return ((igObjectList *)self->_closeDataList)->_count <= 0;
}
