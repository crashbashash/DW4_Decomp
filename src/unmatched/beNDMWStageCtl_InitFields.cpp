extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004ca138[4];
extern int DAT_004ca140[4];
extern int DAT_004ca148[4];
extern int DAT_004ca150[4];
extern int DAT_0058b060[4];
void beNDMWStageCtl_InitFields(void);
}
void beNDMWStageCtl_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0058b060[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca138[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004ca140[0], &DAT_004ca148[0], &DAT_004ca150[0], temp_s1);
}
