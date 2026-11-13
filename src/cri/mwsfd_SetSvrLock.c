void *mwsfd_GetWork();

void mwsfd_SetSvrLock(int arg0) {
    *(int *)((char *)(mwsfd_GetWork()) + 88) = arg0;
}
