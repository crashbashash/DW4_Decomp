extern char DAT_004f47b8[];
extern char DAT_004f47e8[];
int FUN_00262748(int a, int b, int mode, int *x, int *y, int *z);
int FUN_002628a0(int a);
void FUN_00277038(int handle, int id, int x, int y, int z);
int FUN_002968c0(void *ply);
void FUN_0029a320(const char *format, ...);

typedef struct EntryAfsPly {
    char pad[76];
    int handle;
    char pad80[360];
    int mode;
} EntryAfsPly;

void FUN_002991c8(EntryAfsPly *ply, int a, int b)
{
    int x, y, z;
    int handle;

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f47b8);
        return;
    }
    handle = ply->handle;
    if (FUN_00262748(a, b, ply->mode, &x, &y, &z) == 0)
        FUN_00277038(handle, FUN_002628a0(a), x, y, z);
    else
        FUN_0029a320(DAT_004f47e8, a, b);
}
