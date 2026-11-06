int FUN_0020cd10();
extern int DAT_0056c2a0[4];
void FUN_0020cc10(void) {
    int temp_a0;

    temp_a0 = DAT_0056c2a0[0];
    DAT_0056c2a0[0] = temp_a0 + 1;
    if (temp_a0 == 0) {
        FUN_0020cd10();
    }
}
