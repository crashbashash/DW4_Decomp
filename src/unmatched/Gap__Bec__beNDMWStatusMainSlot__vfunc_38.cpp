#include "dw4/reflected.h"
extern "C" {
int ObjectList_FillRetained(void *, int);
void Gap__Bec__beNDMWStatusMainSlot__vfunc_38(beNDMWStatusMainSlot *arg0);
}
/* matching construct: every read of _apuPocket is a volatile load (retail reloads the list pointer each time) */
void Gap__Bec__beNDMWStatusMainSlot__vfunc_38(beNDMWStatusMainSlot *arg0) {
    int i;
    beNDMWItemBase *e;
    i = 0;
    if (0 < ((beNDMWItemBaseList *)(*(volatile int *)&arg0->_apuPocket))->_count) {
        do {
            e = ((beNDMWItemBase **)((beNDMWItemBaseList *)(*(volatile int *)&arg0->_apuPocket))->_data)[i];
            if (e != 0) {
                e->_isEquip = 0;
            }
            i += 1;
        } while (i < ((beNDMWItemBaseList *)(*(volatile int *)&arg0->_apuPocket))->_count);
    }
    ObjectList_FillRetained((void *)(*(volatile int *)&arg0->_apuPocket), 0);
}
