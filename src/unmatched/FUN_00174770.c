int FUN_001747f0();
extern int DAT_00560998[4];
void FUN_00174770(int *arg0, int arg1) {
    if (arg0[256] == arg1) {
        DAT_00560998[0] += 1;
    }
    arg0[256] = arg1;
    FUN_001747f0();
}
