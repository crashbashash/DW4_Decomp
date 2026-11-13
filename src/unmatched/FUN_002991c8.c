extern char DAT_004f47b8[];
extern char DAT_004f47e8[];
int ADXF_GetFnameRangeEx(int a, int b, int mode, int *x, int *y, int *z);
int ADXF_GetFnameFromPt(int a);
void LSC_EntryFileRange(int handle, int id, int x, int y, int z);
int FUN_002968c0(void *ply);
void mwsfd_Error(const char *format, ...);

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
        mwsfd_Error(DAT_004f47b8);
        return;
    }
    handle = ply->handle;
    if (ADXF_GetFnameRangeEx(a, b, ply->mode, &x, &y, &z) == 0)
        LSC_EntryFileRange(handle, ADXF_GetFnameFromPt(a), x, y, z);
    else
        mwsfd_Error(DAT_004f47e8, a, b);
}
