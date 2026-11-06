int igMetaField_Construct();
int FUN_0030ee10(int **);
extern int DAT_00533630[4];
int **FUN_0030edd0(int **arg0) {
    igMetaField_Construct();
    *arg0 = &DAT_00533630[0];
    if (arg0 != 0) {
        FUN_0030ee10(arg0);
    }
    return arg0;
}
