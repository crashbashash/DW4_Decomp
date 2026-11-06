extern int DAT_00560728[4];
extern int DAT_005610b8[4];
extern char GPR_00554b3c;

int *FUN_00164ca0(void) {
    if (GPR_00554b3c == 0) {
        DAT_00560728[0] = DAT_005610b8[0];
        GPR_00554b3c = 1;
    }
    return &DAT_00560728[0];
}
