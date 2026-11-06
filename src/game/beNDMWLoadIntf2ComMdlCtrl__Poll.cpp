#include "dw4/reflected.h"
extern "C" {
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsSequence(beNDMWLoadIntf2ComMdlCtrl *, int, int, int);
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsRunning(beNDMWLoadIntf2ComMdlCtrl *, int, int);
int List_RemoveWordAt(beLoadIntf2ComMdlDataList *, int);
int igObject_Destroy(beLoadIntf2ComMdlData *);

void beNDMWLoadIntf2ComMdlCtrl__Poll(beNDMWLoadIntf2ComMdlCtrl *self) {
    int i;
    int n;
    beLoadIntf2ComMdlDataList *l;
    beLoadIntf2ComMdlData *e;
    beLoadIntf2ComMdlData *t;
    int i2;
    int n2;
    beLoadIntf2ComMdlDataList *l2;
    beLoadIntf2ComMdlData *e2;
    beLoadIntf2ComMdlData *t2;
    n = ((beLoadIntf2ComMdlDataList *)self->_openDataList)->_count;
    if (n > 0) {
        for (i = n - 1; i >= 0; i--) {
            e = ((beLoadIntf2ComMdlData **)((beLoadIntf2ComMdlDataList *)self->_openDataList)->_data)[i];
            if (beNDMWLoadIntf2ComMdlCtrl__IsSequence(self, e->_ramNo, e->_infoName, e->_openSQ) == 1) break;
            l = (beLoadIntf2ComMdlDataList *)self->_openDataList;
            t = ((beLoadIntf2ComMdlData **)l->_data)[i];
            if (t != 0) {
                t->_refCount = (int)t->_refCount - 1;
                if (((unsigned long long)(long long)(int)t->_refCount & 0x7fffffULL) == 0)
                    igObject_Destroy(t);
            }
            List_RemoveWordAt(l, i);
            ((beLoadIntf2ComMdlData **)l->_data)[l->_count] = 0;
        }
    }
    n2 = ((beLoadIntf2ComMdlDataList *)self->_closeDataList)->_count;
    if (n2 > 0) {
        for (i2 = n2 - 1; i2 >= 0; i2--) {
            e2 = ((beLoadIntf2ComMdlData **)((beLoadIntf2ComMdlDataList *)self->_closeDataList)->_data)[i2];
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(self, e2->_ramNo, e2->_infoName) == 1) break;
            l2 = (beLoadIntf2ComMdlDataList *)self->_closeDataList;
            t2 = ((beLoadIntf2ComMdlData **)l2->_data)[i2];
            if (t2 != 0) {
                t2->_refCount = (int)t2->_refCount - 1;
                if (((unsigned long long)(long long)(int)t2->_refCount & 0x7fffffULL) == 0)
                    igObject_Destroy(t2);
            }
            List_RemoveWordAt(l2, i2);
            ((beLoadIntf2ComMdlData **)l2->_data)[l2->_count] = 0;
        }
    }
}
}
