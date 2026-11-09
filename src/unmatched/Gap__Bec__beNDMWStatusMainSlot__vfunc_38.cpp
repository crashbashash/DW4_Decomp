#include "dw4/reflected.h"
extern "C" {
int ObjectList_FillRetained(void *, int);
void Gap__Bec__beNDMWStatusMainSlot__vfunc_38(beNDMWStatusMainSlot *arg0);
}
void Gap__Bec__beNDMWStatusMainSlot__vfunc_38(beNDMWStatusMainSlot *arg0) {
    int i;
    beNDMWItemBase *e;
    i = 0;
    if (0 < ((beNDMWItemBaseList *)(*(int *)&arg0->_apuPocket))->_count) {
        do {
            e = ((beNDMWItemBase **)((beNDMWItemBaseList *)(arg0->_apuPocket))->_data)[i];
            if (e != 0) {
                e->_isEquip = 0;
            }
            i += 1;
        } while (i < ((beNDMWItemBaseList *)(arg0->_apuPocket))->_count);
    }
    ObjectList_FillRetained((void *)(arg0->_apuPocket), 0);
}
