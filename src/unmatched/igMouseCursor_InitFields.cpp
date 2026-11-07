extern "C" {
int FUN_0018e2f0(void *, int *);
int FUN_004505b0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004d0238[4];
extern int DAT_004d0240[4];
extern int DAT_004d0248[4];
extern int DAT_004d0250[4];
extern int DAT_0058c320[4];
void igMouseCursor_InitFields(void);
}
void igMouseCursor_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;
    void *temp_a0;
    int buf[2];

    temp_s0 = (void *)DAT_0058c320[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0238[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_004505b0();
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    buf[0] = 0;
    buf[1] = 0;
    FUN_0018e2f0(temp_a0, buf);
    igMetaObject_NameFields(temp_s0, &DAT_004d0240[0], &DAT_004d0248[0], &DAT_004d0250[0], temp_s2);
}
