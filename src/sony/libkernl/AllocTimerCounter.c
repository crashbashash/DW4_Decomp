int DIntr();
int EIntr();
int iAllocTimerCounter();

int AllocTimerCounter(void) {
    int temp_s0;
    int temp_s1;

    temp_s0 = DIntr();
    temp_s1 = iAllocTimerCounter();
    if (temp_s0 != 0) {
        EIntr();
    }
    return temp_s1;
}
