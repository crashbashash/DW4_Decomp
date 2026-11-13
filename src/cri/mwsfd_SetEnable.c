extern int mwsfd_enable;

void mwsfd_SetEnable(int enable) {
    if (enable == 0) {
        mwsfd_enable = 0;
        return;
    }
    mwsfd_enable = 1;
}
