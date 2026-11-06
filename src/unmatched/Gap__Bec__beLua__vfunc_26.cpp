#include "dw4/reflected.h"
/* Reference count at +4 of an igObject. */
typedef struct RefCountedObject { char pad[4]; int f4; } RefCountedObject;
extern "C" {
int igObject_Destroy(RefCountedObject *);
void Gap__Bec__beLua__vfunc_26(beLua *arg0);
}
void Gap__Bec__beLua__vfunc_26(beLua *arg0) {
    igInfoList *temp_s3;
    int temp_s2;
    int i;
    int n;
    RefCountedObject *t;
    temp_s3 = (igInfoList *)arg0->_infoList;
    temp_s2 = temp_s3->_count;
    for (i = 0; i < temp_s2; i++) {
        t = ((RefCountedObject **)temp_s3->_data)[i];
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    n = temp_s3->_count;
    for (i = 0; i < n; i++) {
        ((int *)temp_s3->_data)[i] = 0;
    }
    temp_s3->_count = 0;
    t = (RefCountedObject *)arg0->_luaState;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_luaState = 0;
}
