/* 0x004577f0 - FUN_004577f0. Same stack key object as igVisualContextCapabilityManager::vfunc_38 (destructor copy at 0x002e2300); the count is re-read through a volatile access. */
#include "dw4/reflected.h"
class OV { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(void *); };
extern "C" void FUN_002ed5c0(void *);
struct K { void *p; K(void *x) { p = x; } ~K() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
struct Flags { int a; int b; int c; int d[4]; };
struct Finder {
    static int Find(igObjectList *l, K &key) {
        int n = l->_count;
        int i = 0;
        for (; i < n; i++) {
            if (key.p == ((void **)l->_data)[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" {
void FUN_004577f0(igModel *arg0, OV *arg1) {
    Flags f;
    igObjectList *l;
    int i;
    int n;
    f.b = 0;
    f.c = 0;
    f.a = 1;
    arg1->vX(&f);
    K key(arg1);
    l = (igObjectList *)arg0->_views;
    i = Finder::Find(l, key);
    if (i >= 0) {
        n = *(volatile int *)&l->_count;
        if (n != 0 && i >= 0 && i < n) {
            ((void **)l->_data)[i] = 0;
        }
    }
}
}
