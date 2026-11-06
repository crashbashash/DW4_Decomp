extern "C" {
int FUN_002d3890(void *, int);
int FUN_002ebc00(void *, int);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c8320[4];
extern int DAT_004c8330[4];
extern int DAT_004c8340[4];
extern int DAT_004c8350[4];
extern int DAT_0058a0a0[4];
void ParticleTimer_InitFields(void);
}
void ParticleTimer_InitFields(void) {
    int temp_s2;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058a0a0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c8320[0], 3);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2), 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002ebc00(temp_v0, 0);
    *(char *)((char *)(temp_v0) + 38) = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    FUN_002ebc00(temp_v0_2, 0);
    *(char *)((char *)(temp_v0_2) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c8330[0], &DAT_004c8340[0], &DAT_004c8350[0], temp_s2);
}
