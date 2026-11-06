#include "dw4/reflected.h"
extern "C" {
int FUN_0014dfb0(void);
int FUN_0019fae0(void);
int FUN_002dc7a0(void *, int *);
int FUN_002e3810(int, float);
int FUN_002ea4b0(void *, int);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
int FUN_0036e880(void);
int FUN_0036e8e0(void);
int FUN_0036e940(void);
int FUN_0036e9a0(void);
extern int DAT_004c8400[4];
extern int DAT_004c8450[4];
extern int DAT_004c84a0[4];
extern int DAT_004c84f0[4];
extern int DAT_004c8538[4];
extern int DAT_004c8540[4];
extern int DAT_004c8548[4];
extern int DAT_004c8550[4];
extern int DAT_0058a0e0[4];
void ParticleInfo_InitFields(void);
}
void ParticleInfo_InitFields(void) {
    void *temp_s0;
    int temp_s1;
    void *f;

    temp_s0 = (void *)DAT_0058a0e0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c8400[0], 0x12);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    ((igFloatArrayMetaField *)f)->_num = 0xC0;
    ((igFloatArrayMetaField *)f)->_resetMethod = 3;
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    ((igIntArrayMetaField *)f)->_num = 0x20;
    ((igIntArrayMetaField *)f)->_resetMethod = 3;
    FUN_002e3810((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 10.0f);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 0xA);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4);
    ((igObjectRefMetaField *)f)->_metaObject = FUN_0014dfb0();
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5);
    FUN_002dc7a0(f, &DAT_004c8538[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)&FUN_0036e940;
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6);
    FUN_002dc7a0(f, &DAT_004c8540[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)&FUN_0036e8e0;
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9);
    FUN_002dc7a0(f, &DAT_004c8548[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)&FUN_0036e880;
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB);
    FUN_002dc7a0(f, &DAT_004c8550[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)&FUN_0036e9a0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE), 1);
    FUN_002e3810((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10), 0.0f);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11);
    ((igObjectRefMetaField *)f)->_metaObject = FUN_0019fae0();
    igMetaObject_NameFields(temp_s0, &DAT_004c8450[0], &DAT_004c84a0[0], &DAT_004c84f0[0], temp_s1);
}
