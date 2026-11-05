/* 0x0045ce60 — igCameraMode_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_0019f670(void);
int FUN_001a4560(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004d1660[4];
extern int DAT_004d1668[4];
extern int DAT_004d1670[4];
extern int DAT_004d1678[4];
extern int DAT_0058cce0[4];
void igCameraMode_InitFields(void);
void igCameraMode_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058cce0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1660[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019f670();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_001a4560();
    igMetaObject_NameFields(temp_s0, &DAT_004d1668[0], &DAT_004d1670[0], &DAT_004d1678[0], temp_s2);
}
