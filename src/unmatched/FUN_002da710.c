int FUN_002dab80(void *, int);
int FUN_0030b3c0(int, int);

int FUN_002da710(void *arg0, int arg1, int arg2) {
    if (arg1 == 0) {
        return 0;
    }
    FUN_0030b3c0(*(int *)((char *)arg0 + 36), arg2);
    FUN_002dab80(arg0, arg1);
    return 1;
}
