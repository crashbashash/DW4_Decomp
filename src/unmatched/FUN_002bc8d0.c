int igMetaEnum_Create();
extern int DAT_004bfa38[4];
extern int DAT_004bfa48[4];
extern int DAT_004f63a8[4];
extern int DAT_00585ae8[4];
int FUN_002bc8d0(void) {
    if (DAT_00585ae8[0] == 0) {
        DAT_00585ae8[0] = igMetaEnum_Create(&DAT_004f63a8[0], &DAT_004bfa38[0], &DAT_004bfa48[0], 3);
    }
    return DAT_00585ae8[0];
}
