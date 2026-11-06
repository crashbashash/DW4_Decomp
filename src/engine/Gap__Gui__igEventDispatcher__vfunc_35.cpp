#include "dw4/reflected.h"
extern "C" void FUN_002ed5c0(void *);
struct K { int p; K(int x) { p = x; } ~K() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
class Lis { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual unsigned char v112(int, int, float);  };
struct IList { char pad[8]; int count; char pad2[4]; int *data; };
struct List { char pad[8]; int n; char pad2[4]; Lis **data; };
struct Hold { char pad[8]; IList *l; };
struct Hold2 { char pad[8]; List *l; };
struct Finder {
    static int Find(IList *l, K &key) {
        int n = l->count;
        int i = 0;
        for (; i < n; i++) {
            if (key.p == l->data[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" {
void Gap__Gui__igEventDispatcher__vfunc_35(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f);
}
void Gap__Gui__igEventDispatcher__vfunc_35(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f) {
    IList *l1 = ((Hold *)arg0->_controllerManager)->l;
    K key(arg2);
    int idx = Finder::Find(l1, key);
    int n2 = ((Hold2 *)arg0->_receivers)->l->n;
    int j = 0;
    for (; j < n2; j++) {
        Lis *o = ((Hold2 *)arg0->_receivers)->l->data[j];
        if (o->v112(idx, arg3, f) & 0xFF) break;
    }
}
