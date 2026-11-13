int DIntr();
int EIntr();
int iFreeTimerCounter();

int FUN_00115288(int arg0) {
    int temp_s0;
    int temp_s1;

    temp_s1 = DIntr();
    temp_s0 = iFreeTimerCounter(arg0);
    if (temp_s1 != 0) {
        EIntr();
    }
    return temp_s0;
}
