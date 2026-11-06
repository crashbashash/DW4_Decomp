int igMetaEnum_Create();
extern int DAT_004bf3e8[4];
extern int DAT_004bf3f8[4];
extern int DAT_004f5c90[4];
extern int DAT_005857b8[4];
int FUN_002b7e80(void) {
    if (DAT_005857b8[0] == 0) {
        DAT_005857b8[0] = igMetaEnum_Create(&DAT_004f5c90[0], &DAT_004bf3e8[0], &DAT_004bf3f8[0], 3);
    }
    return DAT_005857b8[0];
}
