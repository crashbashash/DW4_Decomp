int WatchDma();

int FUN_001033f8(void *arg0, unsigned int arg1, int arg2, int arg3) {
    if (arg2 == 1) {
        return (unsigned int) *(int *)((char *)arg0 + 16) < arg1;
    }
    WatchDma(arg0, arg1, arg3);
    return 0;
}
