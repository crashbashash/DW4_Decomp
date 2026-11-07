#include "dw4/reflected.h"
int FUN_00459380();
int FUN_0045aaf0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d0e68[4];
extern int DAT_004d0e70[4];
extern int DAT_004d0e78[4];
extern int DAT_004d0e80[4];
extern int DAT_0058c928[4];
void igViewerSceneInfoManagerController_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c928[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0e68[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00459380();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0045aaf0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004d0e70[0], &DAT_004d0e78[0], &DAT_004d0e80[0], temp_s2);
}
