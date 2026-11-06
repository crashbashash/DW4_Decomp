/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_002be100(void);
int igStringMetaField_SetDefaultText(void *, int);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6f58[4];
extern int DAT_004c6f60[4];
extern int DAT_004c6f68[4];
extern int DAT_004c6f70[4];
extern int DAT_00589760[4];
void beFileListInfo_InitFields(void);
}
void beFileListInfo_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00589760[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6f58[0], 2);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2), 0);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be100();
    igMetaObject_NameFields(temp_s0, &DAT_004c6f60[0], &DAT_004c6f68[0], &DAT_004c6f70[0], temp_s2);
}
