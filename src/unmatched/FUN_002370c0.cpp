#include "dw4/reflected.h"
extern "C" {
int List_Reserve(...);
int igObject_Destroy(...);
void FUN_002370c0(igInsightCore *arg0);
}
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 112 */
class VC112 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(); };
void FUN_002370c0(igInsightCore *arg0) {
    igObjectList *l;
    int n2;
    int j;
    int n;
    igObjectList *a;
    igObject *p;
    unsigned int k;
    int i;

    for (k = 0; k < (unsigned int)((igObjectList *)((igInfoManagerOrderedList *)arg0->_managerList)->_objectList)->_count; k++) {
        a = (igObjectList *)((igInfoManagerOrderedList *)arg0->_managerList)->_objectList;
        (*(VC112 ***)&a->_data)[k]->vX();
    }
    l = (igObjectList *)arg0->_infoList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        p = (*(igObject ***)&l->_data)[i];
        if (p != 0) {
            *(int *)&p->_refCount = *(int *)&p->_refCount - 1;
            if (((unsigned long long)((long long)*(int *)&p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    n2 = l->_count;
    for (j = 0; j < n2; j++) {
        (*(igObject ***)&l->_data)[j] = 0;
    }
    l->_count = 0;
    if (!(0 < ((igObjectList *)arg0->_infoList)->_count)) {
        List_Reserve(arg0->_infoList, 0, 4);
    }
}
