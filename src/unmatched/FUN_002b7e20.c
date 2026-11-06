int igMetaEnum_Create();
extern int DAT_004bf3d8[4];
extern int DAT_004bf3e0[4];
extern int DAT_004f5c68[4];
extern int DAT_005857b0[4];
int FUN_002b7e20(void) {
    if (DAT_005857b0[0] == 0) {
        DAT_005857b0[0] = igMetaEnum_Create(&DAT_004f5c68[0], &DAT_004bf3d8[0], &DAT_004bf3e0[0], 2);
    }
    return DAT_005857b0[0];
}
