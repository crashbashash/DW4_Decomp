extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cc0e8[4];
extern int DAT_004cc0f0[4];
extern int DAT_004cc0f8[4];
extern int DAT_004cc100[4];
extern int DAT_0058bf68[4];
void beNDMWItemRevisionPocketBase_InitFields(void);
}
void beNDMWItemRevisionPocketBase_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0058bf68[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc0e8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cc0f0[0], &DAT_004cc0f8[0], &DAT_004cc100[0], temp_s1);
}
