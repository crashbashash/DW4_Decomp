extern char DAT_004fb410[];
extern char DAT_004fb418[];
int WakeupThread(int);

void FUN_0032fba0(int *arg0, void *arg1) {
    int *var_v1;

    if (WakeupThread(*(int *)((char *)arg1 + 60)) < 0) {
        var_v1 = (int *)DAT_004fb418;
    } else {
        var_v1 = (int *)DAT_004fb410;
    }
    *arg0 = *var_v1;
}
