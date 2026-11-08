int FUN_002968c0(void *ply);
int FUN_002a33b8(int stream, int *out);
void FUN_0029a320(const char *message);

extern char DAT_004f3cf0[];
extern char DAT_004f3d28[];

int FUN_00296c38(char *ply) {
    int value[4];

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f3cf0);
        return 0;
    }
    if (FUN_002a33b8(*(int *)(ply + 64), value) != 0) {
        FUN_0029a320(DAT_004f3d28);
    }
    return value[0];
}
