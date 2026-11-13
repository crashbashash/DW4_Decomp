int FUN_002968c0(void *ply);
void FUN_00296788(void *ply, int *info);
void mwsfd_Error(const char *message);

extern char DAT_004f3e98[];

int FUN_002970e8(void *ply) {
    int info[40];

    if (FUN_002968c0(ply) == 0) {
        mwsfd_Error(DAT_004f3e98);
        return 0;
    }
    FUN_00296788(ply, info);
    return info[4];
}
