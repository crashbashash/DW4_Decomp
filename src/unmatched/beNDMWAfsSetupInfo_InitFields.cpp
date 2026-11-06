#include "dw4/reflected.h"
extern "C" {
int FUN_00334610(void);
int FUN_003ca800(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cc5b0[4];
extern int DAT_004cc5b8[4];
extern int DAT_004cc5c0[4];
extern int DAT_004cc5c8[4];
extern int DAT_0058c110[4];
void beNDMWAfsSetupInfo_InitFields(void);
}
void beNDMWAfsSetupInfo_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;

    temp_s0 = (void *)DAT_0058c110[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc5b0[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00334610();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_003ca800();
    igMetaObject_NameFields(temp_s0, &DAT_004cc5b8[0], &DAT_004cc5c0[0], &DAT_004cc5c8[0], temp_s2);
}
