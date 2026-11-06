extern "C" {
int igStringMetaField_SetDefaultText(int, int);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c9798[4];
extern int DAT_004c97a0[4];
extern int DAT_004c97a8[4];
extern int DAT_004c97b0[4];
extern int DAT_0058abc8[4];
void beNDMWShopSelect00_InitFields(void);
}
void beNDMWShopSelect00_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0058abc8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9798[0], 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1), 0);
    igMetaObject_NameFields(temp_s0, &DAT_004c97a0[0], &DAT_004c97a8[0], &DAT_004c97b0[0], temp_s1);
}
