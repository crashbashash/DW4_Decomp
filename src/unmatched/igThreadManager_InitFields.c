#include "dw4/reflected.h"
int FUN_002b8220();
int FUN_002ba690();
int FUN_002fe480();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004bf378[4];
extern int DAT_004bf380[4];
extern int DAT_004bf388[4];
extern int DAT_004bf390[4];
extern void * DAT_00585790[4];
extern void thunk_FUN_0030e540(void);
extern void thunk_igPsx2ThreadManager_GetMetaObject(void);

void igThreadManager_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    ((igMetaObject *)(DAT_00585790[0]))->_volatile = 1;
    temp_s0 = (void *)(DAT_00585790[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004bf378[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002b8220();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002ba690();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004bf380[0], &DAT_004bf388[0], &DAT_004bf390[0], temp_s2);
    ((igMetaObject *)(DAT_00585790[0]))->_abstractProxy = (int)thunk_igPsx2ThreadManager_GetMetaObject;
    FUN_002fe480((int)thunk_FUN_0030e540);
}
