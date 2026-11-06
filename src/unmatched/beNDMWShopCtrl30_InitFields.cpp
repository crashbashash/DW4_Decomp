extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c9c08[4];
extern int DAT_004c9c10[4];
extern int DAT_004c9c18[4];
extern int DAT_004c9c20[4];
extern int DAT_0058adf8[4];
void beNDMWShopCtrl30_InitFields(void);
}
void beNDMWShopCtrl30_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0058adf8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9c08[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c9c10[0], &DAT_004c9c18[0], &DAT_004c9c20[0], temp_s1);
}
