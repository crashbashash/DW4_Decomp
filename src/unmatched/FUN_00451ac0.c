int igMetaEnum_Create();
extern int DAT_004d0790[4];
extern int DAT_004d07a0[4];
extern int DAT_0051e648[4];
extern int DAT_0058c5a8[4];
int FUN_00451ac0(void) {
    if (DAT_0058c5a8[0] == 0) {
        DAT_0058c5a8[0] = igMetaEnum_Create(&DAT_0051e648[0], &DAT_004d0790[0], &DAT_004d07a0[0], 4);
    }
    return DAT_0058c5a8[0];
}
