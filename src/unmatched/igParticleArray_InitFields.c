#include "dw4/reflected.h"
int FUN_0014a040();
int FUN_0014b980();
int FUN_0014c030();
int FUN_0014c2f0();
int FUN_0014d0b0();
int FUN_002c4870();
int FUN_002dc7a0();
int FUN_002e3810(void *, float);
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_0014c920(void);  /* code at 0x14c920, passed by address (was DAT_14c920; docs/engine/function-inventory.md) */
extern int DAT_00488a00[4];
extern int DAT_00488a60[4];
extern int DAT_00488ac0[4];
extern int DAT_00488b20[4];
extern int DAT_00488b78[4];
extern void * DAT_0055fbe0[4];
extern void thunk_igPsx2ParticleArray_GetMetaObject(void);

void igParticleArray_InitFields(void) {
    int temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_v0;

    temp_s1 = (void *)(DAT_0055fbe0[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_00488a00[0], 0x16);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0014d0b0();
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), 1.0f);
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5))->_persistent = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igMemoryRefMetaField *)temp_s2_2)->_memType = FUN_002c4870();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0014b980();
    ((igMetaField *)temp_s2_3)->_persistent = 0;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0014a040();
    ((igMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0014c2f0();
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xF));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_0014c030();
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x10))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x11))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x12))->_persistent = 0;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x13));
    FUN_002dc7a0(temp_v0, &DAT_00488b78[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_0014c920);
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x15))->_persistent = 0;
    igMetaObject_NameFields(temp_s1, &DAT_00488a60[0], &DAT_00488ac0[0], &DAT_00488b20[0], temp_s0);
    ((igMetaObject *)DAT_0055fbe0[0])->_abstractProxy = (int)thunk_igPsx2ParticleArray_GetMetaObject;
}
