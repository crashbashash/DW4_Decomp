int FUN_002968c0(void *ply);
int SFD_GetHnStat(int stream);
void FUN_00294ef8(int code);
void mwsfd_Error(const char *message);

extern char DAT_004f3c38[];

int FUN_00296960(char *ply) {
    int state;
    int status;

    if (FUN_002968c0(ply) == 0) {
        FUN_00294ef8(-12);
        mwsfd_Error(DAT_004f3c38);
        return 0;
    }
    state = *(int *)(ply + 8);
    if (state == 2) {
        status = SFD_GetHnStat(*(int *)(ply + 64));
        if (status == 4 || status == 6) {
            return 2;
        }
        return (status < 0) ? 4 : 1;
    }
    return state;
}
