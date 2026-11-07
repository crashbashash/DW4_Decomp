extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7b78[4];
extern int DAT_004c7b80[4];
extern int DAT_004c7b88[4];
extern int DAT_004c7b90[4];
extern int DAT_00589d10[4];
void beBkColor_InitFields(void);
}
void beBkColor_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589d10[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7b78[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c7b80[0], &DAT_004c7b88[0], &DAT_004c7b90[0], temp_s1);
}
