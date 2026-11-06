#include "dw4/reflected.h"
int FUN_0014c030();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486558[4];
extern int DAT_00486560[4];
extern int DAT_00486568[4];
extern int DAT_00486570[4];
extern int DAT_0055f160[4];
void igGeometryAttr1_5_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0055f160[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486558[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014c030();
    igMetaObject_NameFields(temp_s0, &DAT_00486560[0], &DAT_00486568[0], &DAT_00486570[0], temp_s2);
}
