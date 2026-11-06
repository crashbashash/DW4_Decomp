int igMemoryRefMetaField_SetAlignmentType();
int FUN_00308860();
extern int DAT_004df000[4];
extern int DAT_0055faa0[4];
extern int DAT_00586dd0[4];
void FUN_0015e010(void) {
    FUN_00308860(DAT_00586dd0[0], &DAT_004df000[0], 0x10);
    igMemoryRefMetaField_SetAlignmentType(DAT_0055faa0[0], &DAT_004df000[0]);
}
