/* 0x00150620 — igFileImagePng_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_002c4ce0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00489210[4];
extern int DAT_00489218[4];
extern int DAT_00489220[4];
extern int DAT_00489228[4];
extern int DAT_0055ff68[4];
void igFileImagePng_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0055ff68[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489210[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c4ce0();
    igMetaObject_NameFields(temp_s0, &DAT_00489218[0], &DAT_00489220[0], &DAT_00489228[0], temp_s2);
}
