int FUN_0010bcb8();
int InitTLBFunctions();
int FUN_00113f90();
int InitSystemCallTableAddress();
int InitExecPS2();
int InitAlarm();
int InitTimer();
int StartTimerSystemTime();
int FUN_00115ed8();

void _InitSys(void) {
    FUN_00113f90();
    InitSystemCallTableAddress();
    InitAlarm();
    InitTimer(2);
    StartTimerSystemTime();
    FUN_0010bcb8();
    InitExecPS2();
    InitTLBFunctions();
    FUN_00115ed8();
}
