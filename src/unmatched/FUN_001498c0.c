int igMetaEnum_Create();
extern int DAT_004879b0[4];
extern int DAT_004879d0[4];
extern int DAT_004d7cf0[4];
extern int DAT_0055f890[4];
int FUN_001498c0(void) {
    if (DAT_0055f890[0] == 0) {
        DAT_0055f890[0] = igMetaEnum_Create(&DAT_004d7cf0[0], &DAT_004879b0[0], &DAT_004879d0[0], 5);
    }
    return DAT_0055f890[0];
}
