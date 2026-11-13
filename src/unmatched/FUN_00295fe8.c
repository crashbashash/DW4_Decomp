int FUN_00295fc8();
extern int (*mwsfd_create_cb)(int, int);

void FUN_00295fe8(int arg0) {
    int temp_a1;

    temp_a1 = FUN_00295fc8();
    if (mwsfd_create_cb != 0) {
        mwsfd_create_cb(arg0, temp_a1);
    }
}
