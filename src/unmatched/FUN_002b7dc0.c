int igMetaEnum_Create();
extern int DAT_004bf3a0[4];
extern int DAT_004bf3c0[4];
extern int DAT_004f5c38[4];
extern int DAT_005857a8[4];
int FUN_002b7dc0(void) {
    if (DAT_005857a8[0] == 0) {
        DAT_005857a8[0] = igMetaEnum_Create(&DAT_004f5c38[0], &DAT_004bf3a0[0], &DAT_004bf3c0[0], 6);
    }
    return DAT_005857a8[0];
}
