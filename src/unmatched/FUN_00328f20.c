int malloc();
int FUN_00304430();
int FUN_00304680();
extern int DAT_004ff590[4];
extern int DAT_00587328[4];
int FUN_00328f20(int arg0, int arg1) {
    int temp_v0;

    temp_v0 = malloc(arg1);
    if (temp_v0 == DAT_00587328[0]) {
        FUN_00304430(&DAT_004ff590[0], DAT_00587328[0]);
        FUN_00304680();
    }
    return temp_v0;
}
