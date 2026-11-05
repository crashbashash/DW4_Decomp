int WaitSema();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void Gap__Core__igPsx2Semaphore__vfunc_35(int *arg0, void *arg1) {
    int *p;
    int h = *(int *)((char *)(arg1) + 12);
    if (h == -1) {
        *arg0 = DAT_004fb418[0];
    } else {
        if (WaitSema(h) >= 0) {
            p = &DAT_004fb410[0];
        } else {
            p = &DAT_004fb418[0];
        }
        *arg0 = *p;
    }
}
