/* 0x00164cd0 — FUN_00164cd0. Matched with tools/dispatcher/regalloc.py: the replay wanted the first loaded
 * value to get a lower node id than the constant 1 stored to the init flag, which the flag store placed
 * after the first data store gives (retail: li v0,1 / lw a3,... / sb v0,flag). */
extern int DAT_00560730[4];
extern int DAT_00560734[4];
extern int DAT_00560738[4];
extern int DAT_0056073c[4];
extern int DAT_00560740[4];
extern int DAT_00560744[4];
extern int DAT_005610c8[4];
extern int DAT_00586808[4];
extern int DAT_00586818[4];
extern int DAT_00586830[4];
extern int DAT_00586840[4];
extern int DAT_00586898[4];
extern char GPR_00554b40;

int *FUN_00164cd0(void) {
    if (GPR_00554b40 == 0) {
        DAT_00560730[0] = DAT_00586808[0];
        GPR_00554b40 = 1;
        DAT_00560734[0] = DAT_005610c8[0];
        DAT_00560738[0] = DAT_00586898[0];
        DAT_0056073c[0] = DAT_00586818[0];
        DAT_00560740[0] = DAT_00586830[0];
        DAT_00560744[0] = DAT_00586840[0];
    }
    return &DAT_00560730[0];
}
