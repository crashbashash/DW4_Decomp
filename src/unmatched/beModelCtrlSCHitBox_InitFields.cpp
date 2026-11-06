extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4c00[4];
extern int DAT_004c4c20[4];
extern int DAT_004c4c40[4];
extern int DAT_004c4c60[4];
extern int DAT_005887c8[4];
void beModelCtrlSCHitBox_InitFields(void);
}
void beModelCtrlSCHitBox_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_005887c8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4c00[0], 6);
    igMetaObject_NameFields(temp_s0, &DAT_004c4c20[0], &DAT_004c4c40[0], &DAT_004c4c60[0], temp_s1);
}
