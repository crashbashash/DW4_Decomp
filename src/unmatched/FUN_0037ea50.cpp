#include "dw4/reflected.h"
extern "C" {
int ObjectList_AppendRetained(int, igObject *);
int igObject_Destroy(igObject *);
void FUN_0037ea50(beDemoManager *arg0);
}

void FUN_0037ea50(beDemoManager *arg0) {
    igObject *temp_a0;
    igObject *temp_a1;

    temp_a1 = (igObject *)arg0->_buildData;
    if ((temp_a1 != 0) && (arg0->_turningOK != 1)) {
        ObjectList_AppendRetained(arg0->_activeDataList, temp_a1);
        temp_a0 = (igObject *)arg0->_buildData;
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if (((unsigned long long)((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_buildData = 0;
        arg0->_turningOK = 0;
    }
}
