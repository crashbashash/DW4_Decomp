int igMetaEnum_Create();
extern int DAT_0048d190[4];
extern int DAT_0048d1a0[4];
extern int DAT_004e3c78[4];
extern int DAT_005621f8[4];
int FUN_001a7440(void) {
    if (DAT_005621f8[0] == 0) {
        DAT_005621f8[0] = igMetaEnum_Create(&DAT_004e3c78[0], &DAT_0048d190[0], &DAT_0048d1a0[0], 4);
    }
    return DAT_005621f8[0];
}
