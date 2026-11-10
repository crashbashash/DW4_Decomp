int cvFsAddDev();
int cvFsEntryErrFunc();
extern int DAT_004ee4c0[4];
int FUN_0026b1d8();
int FUN_00277dd0();

void FUN_0026b1f0(void) {
    cvFsEntryErrFunc(&FUN_0026b1d8, 0);
    cvFsAddDev(&DAT_004ee4c0[0], &FUN_00277dd0, 0);
}
