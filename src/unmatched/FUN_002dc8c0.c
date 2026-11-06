int FUN_002dc900(int **);
int igMetaField_Construct();
extern int DAT_00532430[4];
int **FUN_002dc8c0(int **arg0) {
    igMetaField_Construct();
    *arg0 = &DAT_00532430[0];
    if (arg0 != 0) {
        FUN_002dc900(arg0);
    }
    return arg0;
}
