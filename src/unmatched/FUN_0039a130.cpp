#include "dw4/reflected.h"
/* The list elements are objects with virtual slots 88 and 100, so VC stays a vtable-only view. */
extern "C" {
int List_RemoveWordAt(...);
void igObject_Destroy(igObject *);
}
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int v88(); virtual void e0(); virtual void e1(); virtual void v100(int); };
extern "C" void FUN_0039a130(beModelCtrlSubCom *arg0, int arg1, int arg2);
void FUN_0039a130(beModelCtrlSubCom *arg0, int arg1, int arg2) {
    int n; int i; VC *o; igObjectList *l; igObject *t;
    n = ((igObjectList *)arg0->_comList)->_count;
    i = 0;
    if (n > 0) {
        do {
            o = ((VC **)((igObjectList *)arg0->_comList)->_data)[i];
            if (arg2 == o->v88()) {
                o->v100(arg1);
                l = (igObjectList *)arg0->_comList;
                t = ((igObject **)l->_data)[i];
                if (t != 0) {
                    --t->_refCount;
                    if (((unsigned long long)(long long)t->_refCount & 0x7fffffULL) == 0) {
                        igObject_Destroy(t);
                    }
                }
                List_RemoveWordAt(l, i);
                i--;
                n--;
                ((int *)l->_data)[l->_count] = 0;
            }
            i++;
        } while (i < n);
    }
}
