#include "dw4/igSmartPointer.h"
extern "C" {
igObject *beBaseInfoDataList_Create(...);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
beModelCtrlInfoRamData *igProperty_FindByName(...);
int strcmp(const char *, const char *);
extern beBaseInfoRam *DAT_0058a1e0[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern int DAT_0050dd40[4];
extern unsigned char GPR_00554c14;
int MDLisSeqName(char *arg0);
}
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

int MDLisSeqName(char *arg0) {
    beBaseInfoRam *h = DAT_0058a1e0[0];
    if (h->_dataList == 0) {
        int al;
        igObject *o;
        al = igObject_GetAllocator(h);
        al = GPR_00554c14 != 0 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igSmartPointer<igObject> ref(beBaseInfoDataList_Create(al));
        igObject *s0 = ref.get();
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        o = (igObject *)h->_dataList;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        h->_dataList = (int)s0;
    }
    beModelCtrlInfoRamData *p = igProperty_FindByName(h->_dataList, DAT_00585be0[0], &DAT_0050dd40[0]);
    return strcmp((const char *)((beModelCtrlInfoWork *)p->_work)->_seqCodeName, arg0) == 0;
}
