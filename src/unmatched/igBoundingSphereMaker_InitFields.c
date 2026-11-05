/* 0x0023ab90 — igBoundingSphereMaker_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_00187e50();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00498620[4];
extern int DAT_00498628[4];
extern int DAT_00498630[4];
extern int DAT_00498638[4];
extern int DAT_0056de00[4];
void igBoundingSphereMaker_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0056de00[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498620[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00187e50();
    igMetaObject_NameFields(temp_s0, &DAT_00498628[0], &DAT_00498630[0], &DAT_00498638[0], temp_s2);
}
