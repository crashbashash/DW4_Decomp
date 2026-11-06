extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c5778[4];
extern int DAT_004c5780[4];
extern int DAT_004c5788[4];
extern int DAT_004c5790[4];
extern int DAT_00588d50[4];
void beModelCtrlMUTEKI_InitFields(void);
}
void beModelCtrlMUTEKI_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00588d50[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5778[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c5780[0], &DAT_004c5788[0], &DAT_004c5790[0], temp_s1);
}
