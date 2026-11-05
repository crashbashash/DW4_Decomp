/* 0x00130270 — igVisualContextAttrDefaultManager_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_0014a040();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00485918[4];
extern int DAT_00485920[4];
extern int DAT_00485928[4];
extern int DAT_00485930[4];
extern int DAT_0055ebc0[4];
void igVisualContextAttrDefaultManager_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0055ebc0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485918[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014a040();
    ((igMetaField *)temp_s1)->_persistent = 0;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 1;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00485920[0], &DAT_00485928[0], &DAT_00485930[0], temp_s2);
}
