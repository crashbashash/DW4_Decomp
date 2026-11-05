#include "dw4/reflected.h"
int FUN_001331a0();
int FUN_001351d0();
int FUN_00139f10();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048d880[4];
extern int DAT_0048d890[4];
extern int DAT_0048d8a0[4];
extern int DAT_0048d8b0[4];
extern void * DAT_005624f8[4];
extern void thunk_igEnvironmentMapShader2_GetMetaObject(void);

void igPsx2EnvironmentMapShader_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    int temp_s2;

    temp_s0 = (void *)(DAT_005624f8[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048d880[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00139f10();
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_001331a0();
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_001351d0();
    ((igMetaField *)temp_s1_3)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048d890[0], &DAT_0048d8a0[0], &DAT_0048d8b0[0], temp_s2);
    ((igMetaObject *)(DAT_005624f8[0]))->_writeProxy = (int)thunk_igEnvironmentMapShader2_GetMetaObject;
}
