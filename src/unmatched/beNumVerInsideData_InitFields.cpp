extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4a00[4];
extern int DAT_004c4a08[4];
extern int DAT_004c4a10[4];
extern int DAT_004c4a18[4];
extern int DAT_005886b0[4];
void beNumVerInsideData_InitFields(void);
}
void beNumVerInsideData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005886b0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4a00[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c4a08[0], &DAT_004c4a10[0], &DAT_004c4a18[0], temp_s1);
}
