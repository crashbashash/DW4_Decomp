int DIntr();
int EIntr();
int iGetTimerUsedUnusedCounters();

int GetTimerUsedUnusedCounters(int arg0, int arg1) {
    int temp_s0;
    int temp_s2;

    temp_s2 = DIntr();
    temp_s0 = iGetTimerUsedUnusedCounters(arg0, arg1);
    if (temp_s2 != 0) {
        EIntr();
    }
    return temp_s0;
}
