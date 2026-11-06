extern char DAT_004bb108[];
int FUN_00281a00();

int FUN_00280f10(void) {
    int temp_v0;
    int var_a0;

    var_a0 = -1;
    if (*(int *)DAT_004bb108 != 0) {
        temp_v0 = FUN_00281a00(0x200, 0, 0, 4);
        *(int *)DAT_004bb108 = 0;
        var_a0 = temp_v0;
    }
    return var_a0;
}
