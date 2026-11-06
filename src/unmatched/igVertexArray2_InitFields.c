#include "dw4/reflected.h"
int FUN_0014ae00();
int igObjectList_GetOrCreateMetaObject();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void thunk_FUN_00152200(void);
extern int DAT_00488520[4];
extern int DAT_00488530[4];
extern int DAT_00488540[4];
extern int DAT_00488550[4];
extern void * DAT_0055f9e0[4];
extern int DAT_00587198[4];
void igVertexArray2_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)(DAT_0055f9e0[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00488520[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0014ae00();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_v0)->_metaObject = (int)((int) DAT_00587198[0]);
    ((igMetaField *)temp_v0)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00488530[0], &DAT_00488540[0], &DAT_00488550[0], temp_s2);
    *(int *)((char *)(DAT_0055f9e0[0]) + 60) = (int)(thunk_FUN_00152200);
}
