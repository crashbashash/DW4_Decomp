#include "dw4/reflected.h"
extern "C" {
int List_Reserve(igObjectList *, int, int);
int igObject_Destroy(igObject *);
}
#define CLEAR(src) { \
    igObjectList *l = (igObjectList *)(src); \
    int n = l->_count; \
    int i; \
    int m; \
    int j; \
    igObject *o; \
    for (i = 0; i < n; i++) { \
        o = ((igObject **)l->_data)[i]; \
        if (o != 0) { \
            o->_refCount = (int)o->_refCount - 1; \
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o); \
        } \
    } \
    m = l->_count; \
    for (j = 0; j < m; j++) { \
        ((igObject **)l->_data)[j] = 0; \
    } \
    l->_count = 0; }
extern "C" {
void beMessenger_ResetMemory(beMessenger *arg0);
}
void beMessenger_ResetMemory(beMessenger *arg0) {
    igObject *t = (igObject *)arg0->_argData;
    if (t != 0) {
        t->_refCount = (int)t->_refCount - 1;
        if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(t);
    }
    arg0->_argData = 0;
    CLEAR(arg0->_groupList)
    if (((igObjectList *)arg0->_groupList)->_count < 5) List_Reserve((igObjectList *)arg0->_groupList, 4, 4);
    CLEAR(arg0->_workStack)
    if (((igObjectList *)arg0->_workStack)->_count < 5) List_Reserve((igObjectList *)arg0->_workStack, 4, 4);
    CLEAR(arg0->_delayStack)
    if (((igObjectList *)arg0->_delayStack)->_count < 5) List_Reserve((igObjectList *)arg0->_delayStack, 4, 4);
    CLEAR(arg0->_pushPopStack)
    if (((igObjectList *)arg0->_pushPopStack)->_count < 5) List_Reserve((igObjectList *)arg0->_pushPopStack, 4, 4);
    arg0->_pushPopCount = 0;
    arg0->_freezeTime = 0;
    arg0->_isMemoryAssign = 0;
}
