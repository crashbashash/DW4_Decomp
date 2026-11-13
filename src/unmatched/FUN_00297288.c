int FUN_002968c0(void *ply);
int FUN_002963a8(void *ply);
void FUN_002add28(int stream, long long *info);
void mwsfd_Error(const char *message);

extern char DAT_004f3f68[];

void FUN_00297288(void *ply, long long *out) {
    long long info[20];

    if (FUN_002968c0(ply) == 0) {
        mwsfd_Error(DAT_004f3f68);
        return;
    }
    FUN_002add28(FUN_002963a8(ply), info);
    out[0] = info[6];
    out[1] = info[7];
    out[2] = info[8];
    out[3] = info[9];
    out[4] = info[10];
    out[5] = info[11];
    out[6] = info[12];
    out[7] = info[13];
    out[8] = info[14];
    out[9] = info[15];
    out[10] = info[16];
    out[11] = info[17];
}
