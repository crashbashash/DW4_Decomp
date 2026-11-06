#include "dw4/reflected.h"
extern "C" {
int FUN_0014b980(void);
int FUN_002d3890(void *, int);
int FUN_002e3810(void *, float);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c8260[4];
extern int DAT_004c8290[4];
extern int DAT_004c82c0[4];
extern int DAT_004c82f0[4];
extern int DAT_0058a040[4];
void ParticleArray_InitFields(void);
}
void ParticleArray_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058a040[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c8260[0], 0xB);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1.0f);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 0.0f);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014b980();
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0014b980();
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xA))->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c8290[0], &DAT_004c82c0[0], &DAT_004c82f0[0], temp_s2);
}
