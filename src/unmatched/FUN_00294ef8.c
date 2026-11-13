void *mwsfd_GetWork();

int FUN_00294ef8(int arg0) {
    *(int *)((char *)(mwsfd_GetWork()) + 104) = arg0;
    return arg0;
}
