int DIntr();
int EIntr();
int iStartTimerCounter();

int FUN_00115438(int arg0) {
    int temp_s0;
    int temp_s1;

    temp_s1 = DIntr();
    temp_s0 = iStartTimerCounter(arg0);
    if (temp_s1 != 0) {
        EIntr();
    }
    return temp_s0;
}
