extern "C" {
int igStringMetaField_SetDefaultText(int, int *);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c42b0[4];
extern int DAT_004c42c0[4];
extern int DAT_004c42d0[4];
extern int DAT_004c42e0[4];
extern int DAT_00502a98[4];
extern int DAT_00588348[4];
void beSvSlotXbox_InitFields(void);
}
void beSvSlotXbox_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00588348[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c42b0[0], 4);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1), &DAT_00502a98[0]);
    igMetaObject_NameFields(temp_s0, &DAT_004c42c0[0], &DAT_004c42d0[0], &DAT_004c42e0[0], temp_s1);
}
