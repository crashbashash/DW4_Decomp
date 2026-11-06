int FUN_00305440(int **);
int igRefMetaField_Construct();
extern int DAT_00532eb0[4];
int **FUN_00305400(int **arg0) {
    igRefMetaField_Construct();
    *arg0 = &DAT_00532eb0[0];
    if (arg0 != 0) {
        FUN_00305440(arg0);
    }
    return arg0;
}
