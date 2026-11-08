int FUN_00113f20();
int FUN_00113f78();
int iSetTimerHandler();

int SetTimerHandler(int arg0, int arg1, int arg2, int arg3) {
    int temp_s0;
    int temp_s4;

    temp_s4 = FUN_00113f20();
    temp_s0 = iSetTimerHandler(arg0, arg1, arg2, arg3);
    if (temp_s4 != 0) {
        FUN_00113f78();
    }
    return temp_s0;
}
