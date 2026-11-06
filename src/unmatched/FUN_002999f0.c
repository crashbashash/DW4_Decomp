void *FUN_00299f68();

void FUN_002999f0(int arg0) {
    int (*temp_v0_2)(int);
    void *temp_v0;

    temp_v0 = (void *)(FUN_00299f68());
    if ((arg0 != 0) && (temp_v0 != 0)) {
        temp_v0_2 = (int (*)(int))(*(int *)((char *)(temp_v0) + 16));
        if (temp_v0_2 != 0) {
            temp_v0_2(arg0);
        }
    }
}
