int iSignalSema();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void Gap__Core__igPsx2Semaphore__vfunc_32(int *arg0, void *arg1) {
    int *p;
    int temp_a0;

    temp_a0 = *(int *)((char *)(arg1) + 12);
    if (temp_a0 == -1) {
        *arg0 = DAT_004fb418[0];
    } else {
        if (iSignalSema(temp_a0) >= 0) {
            p = &DAT_004fb410[0];
        } else {
            p = &DAT_004fb418[0];
        }
        *arg0 = *p;
    }
}
