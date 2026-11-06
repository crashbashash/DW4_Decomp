void *FUN_00299f68();

int FUN_00299998(int arg0, int arg1) {
    int (*temp_v0_2)(int, int);
    int var_v1;
    void *temp_v0;

    temp_v0 = (void *)(FUN_00299f68());
    var_v1 = 0;
    if (temp_v0 != 0) {
        temp_v0_2 = (int (*)(int, int))(*(int *)((char *)(temp_v0) + 12));
        if (temp_v0_2 != 0) {
            var_v1 = (int)(temp_v0_2(arg0, arg1));
        }
    }
    return var_v1;
}
