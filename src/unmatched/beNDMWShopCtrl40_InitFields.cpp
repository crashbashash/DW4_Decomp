/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c9be8[4];
extern int DAT_004c9bf0[4];
extern int DAT_004c9bf8[4];
extern int DAT_004c9c00[4];
extern int DAT_0058ade8[4];
void beNDMWShopCtrl40_InitFields(void);
}
void beNDMWShopCtrl40_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0058ade8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9be8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c9bf0[0], &DAT_004c9bf8[0], &DAT_004c9c00[0], temp_s1);
}
