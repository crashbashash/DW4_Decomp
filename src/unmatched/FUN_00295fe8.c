int FUN_00295fc8();
extern int (*DAT_004be894)(int, int);

void FUN_00295fe8(int arg0) {
    int temp_a1;

    temp_a1 = FUN_00295fc8();
    if (DAT_004be894 != 0) {
        DAT_004be894(arg0, temp_a1);
    }
}
