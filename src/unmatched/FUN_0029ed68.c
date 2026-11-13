/* True when option 49 or option 56 is set. */
extern int SFD_GetCond(void *handle, int option);

int FUN_0029ed68(void *handle) {
    if (SFD_GetCond(handle, 49) != 0 || SFD_GetCond(handle, 56) != 0) {
        return 1;
    }
    return 0;
}
