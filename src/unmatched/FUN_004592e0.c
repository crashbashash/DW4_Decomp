int igMetaEnum_Create();
extern int DAT_004d0ae0[4];
extern int DAT_004d0af0[4];
extern int DAT_0051eaf0[4];
extern int DAT_0058c788[4];
int FUN_004592e0(void) {
    if (DAT_0058c788[0] == 0) {
        DAT_0058c788[0] = igMetaEnum_Create(&DAT_0051eaf0[0], &DAT_004d0ae0[0], &DAT_004d0af0[0], 3);
    }
    return DAT_0058c788[0];
}
