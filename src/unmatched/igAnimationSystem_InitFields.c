/* 0x001a6730 — igAnimationSystem_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_001a7100();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048cee0[4];
extern int DAT_0048cee8[4];
extern int DAT_0048cef0[4];
extern int DAT_0048cef8[4];
extern int DAT_005620c8[4];
void igAnimationSystem_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_005620c8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048cee0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001a7100();
    igMetaObject_NameFields(temp_s0, &DAT_0048cee8[0], &DAT_0048cef0[0], &DAT_0048cef8[0], temp_s2);
}
