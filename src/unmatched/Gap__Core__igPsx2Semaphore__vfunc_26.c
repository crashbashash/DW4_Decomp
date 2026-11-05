extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void Gap__Core__igPsx2Semaphore__vfunc_26(int *arg0, void *arg1, int arg2) {
    if (*(int *)((char *)(arg1) + 12) == -1) {
        *(int *)((char *)(arg1) + 16) = arg2;
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb418[0];
    }
}
