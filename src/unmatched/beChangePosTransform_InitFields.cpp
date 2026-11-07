extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7798[4];
extern int DAT_004c77a0[4];
extern int DAT_004c77a8[4];
extern int DAT_004c77b0[4];
extern int DAT_00589b80[4];
void beChangePosTransform_InitFields(void);
}
void beChangePosTransform_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589b80[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7798[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c77a0[0], &DAT_004c77a8[0], &DAT_004c77b0[0], temp_s1);
}
