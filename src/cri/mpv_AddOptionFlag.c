extern int mpv_option_flag;

int mpv_AddOptionFlag(int flags) {
    if (mpv_option_flag != 0) {
        flags |= 0x02000000;
    }
    return flags;
}
