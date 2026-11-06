#include "dw4/reflected.h"
extern "C" {
void FUN_0036afa0(void);
extern igMetaObject *DAT_00589e00[4];
void *FUN_0036af10(void);
}
void *FUN_0036af10(void) {
    igMetaObject *g = DAT_00589e00[0];
    int ready;
    if (g) {
        /* matching construct: the readiness test materialised as an int (`sltu`) before
         * the branch; a bool or a direct `if` folds it into the branch under -O3,p */
        ready = (g->_validity & 4) != 0;
        if (ready) goto end;
        asm { nop }  /* matching construct: scheduler pad retail leaves in the branch delay slot */
    }
    FUN_0036afa0();
end:
    return DAT_00589e00[0];
}
