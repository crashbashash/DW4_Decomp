int igMetaEnum_Create();
extern int DAT_004bf408[4];
extern int DAT_004bf410[4];
extern int DAT_004f5ca8[4];
extern int DAT_005857c0[4];
int FUN_002b7ee0(void) {
    if (DAT_005857c0[0] == 0) {
        DAT_005857c0[0] = igMetaEnum_Create(&DAT_004f5ca8[0], &DAT_004bf408[0], &DAT_004bf410[0], 2);
    }
    return DAT_005857c0[0];
}
