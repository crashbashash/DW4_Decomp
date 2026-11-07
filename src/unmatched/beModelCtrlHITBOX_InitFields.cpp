extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c5700[4];
extern int DAT_004c5720[4];
extern int DAT_004c5740[4];
extern int DAT_004c5760[4];
extern int DAT_00588d20[4];
void beModelCtrlHITBOX_InitFields(void);
}
void beModelCtrlHITBOX_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00588d20[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5700[0], 5);
    igMetaObject_NameFields(temp_s0, &DAT_004c5720[0], &DAT_004c5740[0], &DAT_004c5760[0], temp_s1);
}
