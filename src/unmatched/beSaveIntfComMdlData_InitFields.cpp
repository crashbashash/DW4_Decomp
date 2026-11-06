extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004ca1b8[4];
extern int DAT_004ca1c8[4];
extern int DAT_004ca1d8[4];
extern int DAT_004ca1e8[4];
extern int DAT_0058b0b0[4];
void beSaveIntfComMdlData_InitFields(void);
}
void beSaveIntfComMdlData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058b0b0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca1b8[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004ca1c8[0], &DAT_004ca1d8[0], &DAT_004ca1e8[0], temp_s1);
}
