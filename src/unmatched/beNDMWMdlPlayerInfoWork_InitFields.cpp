#include "dw4/reflected.h"
extern "C" {
int igIntList_GetOrCreateMetaObject(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004ca8c0[4];
extern int DAT_004ca8e0[4];
extern int DAT_004ca900[4];
extern int DAT_004ca920[4];
extern int DAT_0058b3c8[4];
void beNDMWMdlPlayerInfoWork_InitFields(void);
}
void beNDMWMdlPlayerInfoWork_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0058b3c8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca8c0[0], 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, &DAT_004ca8e0[0], &DAT_004ca900[0], &DAT_004ca920[0], temp_s2);
}
