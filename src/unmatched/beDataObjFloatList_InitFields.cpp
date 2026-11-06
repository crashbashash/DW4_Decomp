#include "dw4/reflected.h"
extern "C" {
int FUN_002c9780(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7118[4];
extern int DAT_004c7120[4];
extern int DAT_004c7128[4];
extern int DAT_004c7130[4];
extern int DAT_00589848[4];
void beDataObjFloatList_InitFields(void);
}
void beDataObjFloatList_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00589848[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7118[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c9780();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c7120[0], &DAT_004c7128[0], &DAT_004c7130[0], temp_s2);
}
