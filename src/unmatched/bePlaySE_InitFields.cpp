extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c39c8[4];
extern int DAT_004c39d0[4];
extern int DAT_004c39d8[4];
extern int DAT_004c39e0[4];
extern int DAT_00587ed0[4];
void bePlaySE_InitFields(void);
}
void bePlaySE_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00587ed0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c39c8[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c39d0[0], &DAT_004c39d8[0], &DAT_004c39e0[0], temp_s1);
}
