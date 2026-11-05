/* 0x001a9b20 — igAnimationTransitionPoint_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_001a9bb0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048d600[4];
extern int DAT_0048d608[4];
extern int DAT_0048d610[4];
extern int DAT_0048d618[4];
extern int DAT_005623e8[4];
void igAnimationTransitionPoint_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_005623e8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048d600[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001a9bb0();
    igMetaObject_NameFields(temp_s0, &DAT_0048d608[0], &DAT_0048d610[0], &DAT_0048d618[0], temp_s2);
}
