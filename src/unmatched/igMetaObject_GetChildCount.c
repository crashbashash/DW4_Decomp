#include "dw4/reflected.h"
int igMetaObject_GetChildCount(igMetaObject *arg0) {
    void *temp_v0;

    temp_v0 = (void *)(arg0->_children);
    if (temp_v0 == 0) {
        return 0;
    }
    return *(int *)((char *)(temp_v0) + 12);
}
