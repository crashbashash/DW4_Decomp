#include "dw4/reflected.h"
extern "C" {
void beBaseInfoRamList_EnsureRegistered(void);
extern igMetaObject *DAT_00589d20[4];
void *beBaseInfoRamList_GetReadyMetaObject(void);
}
void *beBaseInfoRamList_GetReadyMetaObject(void) {
    igMetaObject *g = DAT_00589d20[0];
    int ready;
    if (g) {
        /* matching construct: the readiness test materialised as an int (`sltu`) before
         * the branch; a bool or a direct `if` folds it into the branch under -O3,p */
        ready = (g->_validity & 4) != 0;
        if (ready) goto end;
        asm { nop }  /* matching construct: scheduler pad retail leaves in the branch delay slot */
    }
    beBaseInfoRamList_EnsureRegistered();
end:
    return DAT_00589d20[0];
}
