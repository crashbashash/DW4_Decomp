#include "dw4/reflected.h"
int igObject_InitHeader(igFilterMessageDispatcher *);
int igObject_Destroy();
extern int DAT_0052c8b0[4];
extern void * DAT_00586dc8[4];
int igFilterMessageDispatcher_GetVTable(void) {
    igFilterMessageDispatcher obj;
    igObject *o;
    int t;
    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &DAT_0052c8b0[0];
    obj._defaultFilters = 0;
    obj._filters = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    *(int **)&obj._vtable = &DAT_0052c8b0[0];
    if (&obj._filters != 0) {
        o = (igObject *)obj._filters;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (&obj._defaultFilters != 0) {
        o = (igObject *)obj._defaultFilters;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}
