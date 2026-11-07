int igObject_IsKindOf();
int FUN_00308860();
int igMemoryRefMetaField_SetAlignmentType();
int igMetaObject_FindFieldByName();
extern int DAT_004ddf18[4];
extern int DAT_004e0848[4];
extern int DAT_00560420[4];
extern int DAT_00585d80[4];
extern int DAT_00586dd0[4];
static inline int cast0(int o) { if (o != 0 && igObject_IsKindOf(o, DAT_00585d80[0]) != 0) { return o; } return 0; }
void FUN_0017f5a0(void) {
    int var_s0;

    FUN_00308860(DAT_00586dd0[0], &DAT_004e0848[0], 0x10);
    var_s0 = igMetaObject_FindFieldByName(DAT_00560420[0], &DAT_004ddf18[0]);
    var_s0 = cast0(var_s0);
    igMemoryRefMetaField_SetAlignmentType(var_s0, &DAT_004e0848[0]);
}
