int DIntr();
int EIntr();
int iSetTimerHandler();

int SetTimerHandler(int arg0, int arg1, int arg2, int arg3) {
    int temp_s0;
    int temp_s4;

    temp_s4 = DIntr();
    temp_s0 = iSetTimerHandler(arg0, arg1, arg2, arg3);
    if (temp_s4 != 0) {
        EIntr();
    }
    return temp_s0;
}
