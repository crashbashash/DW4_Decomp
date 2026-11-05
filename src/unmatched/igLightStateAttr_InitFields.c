/* 0x00136510 — igLightStateAttr_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_00136750();
int FUN_002d3890();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486320[4];
extern int DAT_00486330[4];
extern int DAT_00486340[4];
extern int DAT_00486350[4];
extern int DAT_0055f060[4];
extern int DAT_00587198[4];
void igLightStateAttr_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_0055f060[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486320[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00136750();
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_v0)->_metaObject = (int)((int) DAT_00587198[0]);
    ((igMetaField *)temp_v0)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00486330[0], &DAT_00486340[0], &DAT_00486350[0], temp_s2);
}
