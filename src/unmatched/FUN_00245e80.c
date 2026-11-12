int ThreadLocalTable_Insert();

void *FUN_00245e80(void *arg0, int arg1, int arg2, int arg3) {
    *(int *)((char *)arg0 + 0) = (int) (arg1 ^ arg2);
    *(int *)((char *)arg0 + 4) = 0;
    *(int *)((char *)arg0 + 8) = 0;
    ThreadLocalTable_Insert();
    *(int *)((char *)arg0 + 12) = arg2;
    *(int *)((char *)arg0 + 16) = arg3;
    *(int *)((char *)arg0 + 20) = arg1;
    return arg0;
}
