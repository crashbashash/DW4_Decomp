#include "dw4/reflected.h"
extern "C" void FUN_002ed5c0(void *);
struct K { int p; K(int x) { p = x; } ~K() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
class Elem { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual int vX(int, int, float, float);
};
struct Finder {
    static int Find(igDataList *l, K &key) {
        int n = l->_count;
        int i = 0;
        for (; i < n; i++) {
            if (key.p == ((int *)l->_data)[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" {
void Gap__Gui__igEventDispatcher__vfunc_32(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f0, float f1);
}
/* matching construct: _receivers/_controllerManager/_objectList/_controllers/_data are 4-byte reference fields in the reflected structs; the casts give the typed views (no layout effect) */
void Gap__Gui__igEventDispatcher__vfunc_32(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f0, float f1) {
    igDataList *l1 = (igDataList *)((igControllerManager *)arg0->_controllerManager)->_controllers;
    K key(arg2);
    int idx = Finder::Find(l1, key);
    int n2 = ((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_count;
    int j = 0;
    for (; j < n2; j++) {
        Elem *o = ((Elem **)((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_data)[j];
        if (o->vX(idx, arg3, f0, f1) & 0xFF) break;
    }
}
