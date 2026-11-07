extern "C" {
int igObject_IsKindOf(int, int);
int FUN_00308860(int, int *, int);
int igMemoryRefMetaField_SetAlignmentType(int, int *);
int igMetaObject_FindFieldByName(int, int *);
extern int DAT_0050e490[4];
extern int DAT_0050e4a0[4];
extern int DAT_00585d80[4];
extern int DAT_00586dd0[4];
extern int DAT_00589998[4];
void FUN_0037e070(void);
}

static inline int cast0(int o) { if (o != 0 && igObject_IsKindOf(o, DAT_00585d80[0]) != 0) { return o; } return 0; }
void FUN_0037e070(void) {
    int var_s0;

    FUN_00308860(DAT_00586dd0[0], &DAT_0050e490[0], 0x20);
    var_s0 = igMetaObject_FindFieldByName(DAT_00589998[0], &DAT_0050e4a0[0]);
    var_s0 = cast0(var_s0);
    igMemoryRefMetaField_SetAlignmentType(var_s0, &DAT_0050e490[0]);
}
