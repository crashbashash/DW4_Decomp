extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cc130[4];
extern int DAT_004cc140[4];
extern int DAT_004cc150[4];
extern int DAT_004cc160[4];
extern int DAT_0058bf90[4];
void beNDMWItemBase_InitFields(void);
}
void beNDMWItemBase_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058bf90[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc130[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004cc140[0], &DAT_004cc150[0], &DAT_004cc160[0], temp_s1);
}
