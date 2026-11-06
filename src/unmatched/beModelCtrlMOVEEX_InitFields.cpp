extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c57e0[4];
extern int DAT_004c5800[4];
extern int DAT_004c5820[4];
extern int DAT_004c5840[4];
extern int DAT_00588da0[4];
void beModelCtrlMOVEEX_InitFields(void);
}
void beModelCtrlMOVEEX_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00588da0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c57e0[0], 6);
    igMetaObject_NameFields(temp_s0, &DAT_004c5800[0], &DAT_004c5820[0], &DAT_004c5840[0], temp_s1);
}
