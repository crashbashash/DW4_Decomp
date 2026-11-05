#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(...);
extern int DAT_00588800[4];
void FUN_00399f20(beModelCtrlSubCom *arg0, int arg1);
}
class DW4VC_88 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
class DW4VC_100 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
struct E { char pad[56]; unsigned char f56; };
void FUN_00399f20(beModelCtrlSubCom *arg0, int arg1) {
    igObjectList *l;
    int i;
    int n2;
    int n3;
    DW4VC_88 *o;
    int j;
    int q;
    int n;
    int s1;
    igObject *p;

    n = ((igObjectList *)arg0->_comList)->_count;
    i = 0;
    if (0 < n) {
        do {
            s1 = DAT_00588800[0];
            o = ((DW4VC_88 **)((igObjectList *)arg0->_comList)->_data)[i];
            if (s1 != o->vX() || ((E *)o)->f56 != 0) {
                ((DW4VC_100 *)o)->vX(arg1);
            }
            i += 1;
        } while (i < n);
    }
    l = (igObjectList *)arg0->_comList;
    n2 = l->_count;
    j = 0;
    if (0 < n2) {
        do {
            p = ((igObject **)l->_data)[j];
            if (p != 0) {
                p->_refCount = p->_refCount - 1;
                if ((p->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
            j += 1;
        } while (j < n2);
    }
    n3 = l->_count;
    for (q = 0; q < n3; q++) {
        ((int *)l->_data)[q] = 0;
    }
    l->_count = 0;
}
