extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c9b70[4];
extern int DAT_004c9b90[4];
extern int DAT_004c9bb0[4];
extern int DAT_004c9bd0[4];
extern int DAT_0058adb8[4];
void beNDMWShopCtrl50_InitFields(void);
}
void beNDMWShopCtrl50_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058adb8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9b70[0], 5);
    igMetaObject_NameFields(temp_s0, &DAT_004c9b90[0], &DAT_004c9bb0[0], &DAT_004c9bd0[0], temp_s1);
}
