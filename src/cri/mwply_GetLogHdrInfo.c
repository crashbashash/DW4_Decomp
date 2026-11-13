int mwply_GetLogHdrInfo(int arg0, int arg1) {
    return *(int *)((char *)(((arg1 * 0x14) + arg0)) + 208);
}
