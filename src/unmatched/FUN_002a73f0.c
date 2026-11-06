int memcpy();

void FUN_002a73f0(void *arg0, void *arg1) {
    memcpy(*(int *)((char *)(arg0) + 0), *(int *)((char *)(arg1) + 0), *(int *)((char *)(arg1) + 4));
    *(int *)((char *)(arg0) + 4) = (int)((int) *(int *)((char *)(arg1) + 4));
}
