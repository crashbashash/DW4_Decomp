void FUN_004666c0(void *arg0, int arg1, int arg2, float fparg0, float fparg1) {
    if (!(arg2 & 0xFFFF)) {
        *(float *)((char *)(arg0) + 180) = fparg0;
        *(float *)((char *)(arg0) + 184) = fparg1;
    }
}
