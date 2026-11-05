#include "dw4/reflected.h"
int FUN_0014b1c0();
int FUN_002dc7a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_0014ad00(void);  /* code at 0x14ad00, passed by address (was DAT_14ad00; docs/engine/function-inventory.md) */
extern int DAT_004885b0[4];
extern int DAT_004885d0[4];
extern int DAT_004885f0[4];
extern int DAT_00488610[4];
extern int DAT_00488628[4];
extern int DAT_00488630[4];
extern int DAT_00488638[4];
extern void * DAT_0055fa10[4];
int FUN_00149aa0();
int FUN_0014ad60();
extern void thunk_igPsx2VertexStream_GetMetaObject(void);

void igVertexStream_InitFields(void) {
    int temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_s1 = (void *)(DAT_0055fa10[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004885b0[0], 6);
    ((igRawRefMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0))->_persistent = 0;
    ((igBoolMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1))->_persistent = 0;
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0014b1c0();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    FUN_002dc7a0(temp_v0, &DAT_00488628[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_0014ad60);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    FUN_002dc7a0(temp_v0_2, &DAT_00488630[0]);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_00149aa0);
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    FUN_002dc7a0(temp_v0_3, &DAT_00488638[0]);
    ((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (int)(FUN_0014ad00);
    igMetaObject_NameFields(temp_s1, &DAT_004885d0[0], &DAT_004885f0[0], &DAT_00488610[0], temp_s0);
    ((igMetaObject *)DAT_0055fa10[0])->_abstractProxy = (int)thunk_igPsx2VertexStream_GetMetaObject;
}
