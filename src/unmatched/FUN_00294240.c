int FUN_002968c0(void *ply);
int FUN_002963a8(void *ply);
void FUN_002a87a0(int stream, int *addr, int *size);
void FUN_0029a320(const char *message);

extern char DAT_004f3240[];

void FUN_00294240(void *ply, int *addr, int *size) {
    int n, a;

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f3240);
        *addr = 0;
        *size = 0;
    } else {
        FUN_002a87a0(FUN_002963a8(ply), addr, size);
        n = *size;
        if (n >= 4) {
            a = *addr;
            *size = n - 4;
            *addr = a + 4;
        }
    }
}
