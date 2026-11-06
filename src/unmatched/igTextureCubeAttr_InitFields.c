#include "dw4/reflected.h"
int FUN_0014dfb0();
int FUN_002dc7a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_00131f80(void);
extern int DAT_00485c18[4];
extern int DAT_00485c28[4];
extern int DAT_00485c38[4];
extern int DAT_00485c48[4];
extern int DAT_00485c58[4];
extern int DAT_0055ed48[4];
void igTextureCubeAttr_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_0055ed48[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485c18[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014dfb0();
    ((igObjectRefArrayMetaField *)temp_s1)->_num = 6;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002dc7a0(temp_v0, &DAT_00485c58[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_00131f80);
    igMetaObject_NameFields(temp_s0, &DAT_00485c28[0], &DAT_00485c38[0], &DAT_00485c48[0], temp_s2);
}
