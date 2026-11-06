#include "dw4/reflected.h"
extern "C" {
int FUN_0019aee0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4b30[4];
extern int DAT_004c4b40[4];
extern int DAT_004c4b50[4];
extern int DAT_004c4b60[4];
extern int DAT_00588760[4];
void beMovieInfoData_InitFields(void);
}
void beMovieInfoData_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00588760[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4b30[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019aee0();
    igMetaObject_NameFields(temp_s0, &DAT_004c4b40[0], &DAT_004c4b50[0], &DAT_004c4b60[0], temp_s2);
}
