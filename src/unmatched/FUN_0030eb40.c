int igMetaField_Construct();
int FUN_0030eb80(int **);
extern int DAT_00533530[4];
int **FUN_0030eb40(int **arg0) {
    igMetaField_Construct();
    *arg0 = &DAT_00533530[0];
    if (arg0 != 0) {
        FUN_0030eb80(arg0);
    }
    return arg0;
}
