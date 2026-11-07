#include "dw4/reflected.h"
extern "C" {
int FUN_00342ce0(void);
int FUN_0034c8e0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cb760[4];
extern int DAT_004cb770[4];
extern int DAT_004cb780[4];
extern int DAT_004cb790[4];
extern int DAT_0058bac8[4];
void beNDMWLoadIntf2_InitFields(void);
}
void beNDMWLoadIntf2_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058bac8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cb760[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004cb770[0], &DAT_004cb780[0], &DAT_004cb790[0], temp_s2);
}
