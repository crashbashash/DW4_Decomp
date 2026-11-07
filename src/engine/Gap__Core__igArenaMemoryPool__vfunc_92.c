void Gap__Core__igArenaMemoryPool__vfunc_92(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 180) = arg1;
    if (*(int *)((char *)(arg0) + 180) >= 0x40) {
        *(int *)((char *)(arg0) + 200) = 0x18;
    } else {
        *(int *)((char *)(arg0) + 200) = 0x10;
    }
}
