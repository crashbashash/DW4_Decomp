int memcpy();
void FUN_002fc9d0(void *arg0, int arg1, int arg2) {
    memcpy(arg1 + *(int *)((char *)(arg0) + 8), arg2 + *(int *)((char *)(arg0) + 8), *(unsigned short *)((char *)(arg0) + 20));
}
