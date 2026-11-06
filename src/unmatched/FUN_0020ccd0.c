int FUN_0020cc50();
extern int DAT_0056c2a0[4];
void FUN_0020ccd0(void) {
    int temp_v1;

    temp_v1 = DAT_0056c2a0[0] - 1;
    DAT_0056c2a0[0] = temp_v1;
    if (temp_v1 == 0) {
        FUN_0020cc50();
    }
}
