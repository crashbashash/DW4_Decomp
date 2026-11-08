int FUN_00113f20();
int FUN_00113f78();
int iStopTimerCounter();

int FUN_00115550(int arg0) {
    int temp_s0;
    int temp_s1;

    temp_s1 = FUN_00113f20();
    temp_s0 = iStopTimerCounter(arg0);
    if (temp_s1 != 0) {
        FUN_00113f78();
    }
    return temp_s0;
}
