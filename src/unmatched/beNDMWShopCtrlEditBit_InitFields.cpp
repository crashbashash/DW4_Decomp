extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c9a60[4];
extern int DAT_004c9a68[4];
extern int DAT_004c9a70[4];
extern int DAT_004c9a78[4];
extern int DAT_0058ad28[4];
void beNDMWShopCtrlEditBit_InitFields(void);
}
void beNDMWShopCtrlEditBit_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058ad28[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9a60[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c9a68[0], &DAT_004c9a70[0], &DAT_004c9a78[0], temp_s1);
}
