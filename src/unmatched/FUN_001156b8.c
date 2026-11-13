int DIntr();
int EIntr();
int isceTimerGetBaseTime();

int FUN_001156b8(int arg0) {
    int temp_s0;
    int temp_s1;

    temp_s1 = DIntr();
    temp_s0 = isceTimerGetBaseTime(arg0);
    if (temp_s1 != 0) {
        EIntr();
    }
    return temp_s0;
}
