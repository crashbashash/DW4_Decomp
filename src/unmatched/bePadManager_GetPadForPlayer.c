#include "dw4/reflected.h"
/* _padList is a bePadDataList whose backing array (_data) holds the pad record pointers (docs/engine/selectctrl.md) */
int bePadManager_GetPadForPlayer(bePadManager *arg0, int arg1) {
    if (arg0->_isPadDisable != 0) {
        return *(int *)(((bePadDataList *)arg0->_padList)->_data + 16);
    }
    if (arg1 < 4) {
        return *(int *)(((bePadDataList *)arg0->_padList)->_data + (arg1 * 4));
    }
    return *(int *)(((bePadDataList *)arg0->_padList)->_data + 16);
}
