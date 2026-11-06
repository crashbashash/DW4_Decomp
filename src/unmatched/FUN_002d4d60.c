int FUN_002d4da0(int **);
int igMetaField_Construct();
extern int DAT_00531640[4];
int **FUN_002d4d60(int **arg0) {
    igMetaField_Construct();
    *arg0 = &DAT_00531640[0];
    if (arg0 != 0) {
        FUN_002d4da0(arg0);
    }
    return arg0;
}
