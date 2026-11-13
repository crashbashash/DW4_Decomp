int FUN_002968c0(void *ply);
void FUN_002967a0(void *ply, int *info);
void mwsfd_Error(const char *message);

extern char DAT_004f3bd8[];

int FUN_00296730(void *ply) {
    int info[16];

    if (FUN_002968c0(ply) == 0) {
        mwsfd_Error(DAT_004f3bd8);
        return -1;
    }
    FUN_002967a0(ply, info);
    return info[10];
}
