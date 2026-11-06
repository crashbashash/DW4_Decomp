/* Matched with tools/dispatcher/regalloc.py: the replay wanted the first loaded value to get a
 * lower node id than the constant 1 stored to the init flag, which the flag store placed after the
 * first data store gives (retail: li v0,1 / lw a3,... / sb v0,flag). */
extern int DAT_00560720[4];
extern int DAT_005610b8[4];
extern char GPR_00554b38;

int *FUN_00164c70(void) {
    if (GPR_00554b38 == 0) {
        DAT_00560720[0] = DAT_005610b8[0];
        GPR_00554b38 = 1;
    }
    return &DAT_00560720[0];
}
