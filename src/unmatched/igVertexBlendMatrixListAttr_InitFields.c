#include "dw4/reflected.h"
int FUN_001e4ae0();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004859f0[4];
extern int DAT_00485a10[4];
extern int DAT_00485a30[4];
extern int DAT_00485a50[4];
extern int DAT_0055ec28[4];
void igVertexBlendMatrixListAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055ec28[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004859f0[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001e4ae0();
    ((igObjectRefMetaField *)temp_s1)->_construct = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igMetaField *)temp_v0)->_isAlikeShallowMethod = 3;
    ((igMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4)))->_persistent = 0;
    ((igMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5)))->_persistent = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    FUN_002ea4b0(temp_v0_2, -1);
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00485a10[0], &DAT_00485a30[0], &DAT_00485a50[0], temp_s2);
}
