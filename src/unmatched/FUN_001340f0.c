int igMetaEnum_Create();
extern int DAT_00485f88[4];
extern int DAT_00485f90[4];
extern int DAT_004d5080[4];
extern int DAT_0055eec8[4];
int FUN_001340f0(void) {
    if (DAT_0055eec8[0] == 0) {
        DAT_0055eec8[0] = igMetaEnum_Create(&DAT_004d5080[0], &DAT_00485f88[0], &DAT_00485f90[0], 2);
    }
    return DAT_0055eec8[0];
}
