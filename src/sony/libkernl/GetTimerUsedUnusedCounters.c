int FUN_00113f20();
int FUN_00113f78();
int iGetTimerUsedUnusedCounters();

int GetTimerUsedUnusedCounters(int arg0, int arg1) {
    int temp_s0;
    int temp_s2;

    temp_s2 = FUN_00113f20();
    temp_s0 = iGetTimerUsedUnusedCounters(arg0, arg1);
    if (temp_s2 != 0) {
        FUN_00113f78();
    }
    return temp_s0;
}
