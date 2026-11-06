#include "dw4/reflected.h"
extern "C" {
int FUN_00335130(void);
int FUN_003674d0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c75c0[4];
extern int DAT_004c75d0[4];
extern int DAT_004c75e0[4];
extern int DAT_004c75f0[4];
extern int DAT_00589a88[4];
void beCriAudio_InitFields(void);
}
void beCriAudio_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;

    temp_s0 = (void *)DAT_00589a88[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c75c0[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00335130();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_003674d0();
    igMetaObject_NameFields(temp_s0, &DAT_004c75d0[0], &DAT_004c75e0[0], &DAT_004c75f0[0], temp_s2);
}
