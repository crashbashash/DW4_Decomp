extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cc0c8[4];
extern int DAT_004cc0d0[4];
extern int DAT_004cc0d8[4];
extern int DAT_004cc0e0[4];
extern int DAT_0058bf38[4];
void beNDMWItemDisk_InitFields(void);
}
void beNDMWItemDisk_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058bf38[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc0c8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cc0d0[0], &DAT_004cc0d8[0], &DAT_004cc0e0[0], temp_s1);
}
