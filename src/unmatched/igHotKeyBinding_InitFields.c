#include "dw4/reflected.h"
int FUN_002dc7a0();
int FUN_00453250();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_00145eb0(void);
void FUN_00146850(void);
extern int DAT_004d0138[4];
extern int DAT_004d0148[4];
extern int DAT_004d0158[4];
extern int DAT_004d0168[4];
extern int DAT_004d0178[4];
extern int DAT_004d0180[4];
extern int DAT_0058c2c0[4];
void igHotKeyBinding_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    void *temp_v0_2;
    int temp_s2;

    temp_s0 = (void *)DAT_0058c2c0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0138[0], 3);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_004d0178[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_00145eb0);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002dc7a0(temp_v0_2, &DAT_004d0180[0]);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(FUN_00146850);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00453250();
    igMetaObject_NameFields(temp_s0, &DAT_004d0148[0], &DAT_004d0158[0], &DAT_004d0168[0], temp_s2);
}
