extern void * DAT_00555048[4];
int FUN_00100c20(int arg0, int arg1, void *arg2) {
    *(int *)((char *)arg2 + 0) = (int) DAT_00555048[0];
    *(int *)((char *)arg2 + 4) = arg1;
    *(int *)((char *)arg2 + 8) = arg0;
    DAT_00555048[0] = arg2;
    return arg0;
}
