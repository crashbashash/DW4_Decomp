extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cc108[4];
extern int DAT_004cc110[4];
extern int DAT_004cc118[4];
extern int DAT_004cc120[4];
extern int DAT_0058bf78[4];
void beNDMWItemRevisionBase_InitFields(void);
}
void beNDMWItemRevisionBase_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058bf78[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc108[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cc110[0], &DAT_004cc118[0], &DAT_004cc120[0], temp_s1);
}
