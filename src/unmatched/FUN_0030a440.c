int igMetaField_Construct();
int FUN_0030a480(int **);
extern int DAT_00533080[4];
int **FUN_0030a440(int **arg0) {
    igMetaField_Construct();
    *arg0 = &DAT_00533080[0];
    if (arg0 != 0) {
        FUN_0030a480(arg0);
    }
    return arg0;
}
