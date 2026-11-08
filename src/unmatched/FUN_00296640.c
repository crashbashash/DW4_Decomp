int FUN_002968c0(void *ply);
void FUN_002967a0(void *ply, int *info);
void FUN_0029a320(const char *message);

extern char DAT_004f3b48[];

int FUN_00296640(void *ply) {
    int info[16];

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f3b48);
        return -1;
    }
    FUN_002967a0(ply, info);
    return info[9];
}
