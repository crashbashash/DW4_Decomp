extern char DAT_00554b20[4];
extern int DAT_00560670[4];
extern int DAT_00560674[4];
extern int DAT_00560678[4];
extern int DAT_0056067c[4];
extern int DAT_00560680[4];
extern int DAT_005610b8[4];
extern int DAT_00586818[4];
extern int DAT_00586830[4];
extern int DAT_00586840[4];
extern int DAT_00586898[4];
int *FUN_001649f0(void) {
    if (DAT_00554b20[0] == 0) {
        DAT_00554b20[0] = 1;
        DAT_00560670[0] = DAT_005610b8[0];
        DAT_00560674[0] = DAT_00586898[0];
        DAT_00560678[0] = DAT_00586818[0];
        DAT_0056067c[0] = DAT_00586830[0];
        DAT_00560680[0] = DAT_00586840[0];
    }
    return &DAT_00560670[0];
}
