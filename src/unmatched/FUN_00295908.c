typedef struct PausePly {
    char pad[12];
    int f12;
    char pad16[48];
    int handle;
    char pad68[50];
    signed char paused;
    char pad119[541];
    char sub[4];
} PausePly;

extern char DAT_004f3860[];
extern char DAT_004f3888[];
extern char DAT_004f38b0[];
extern char DAT_004f38b8[];
int FUN_00294d70(void);
int FUN_00294ef8(int code);
int FUN_002968c0(PausePly *ply);
void FUN_00299bc0(void *sub, int sw);
void FUN_0029a320(const char *format, ...);
void FUN_0029b018(PausePly *ply);
int FUN_002aa340(int handle, int sw);
int FUN_002adba0(int handle, int id, int *value);

void FUN_00295908(PausePly *ply, int sw)
{
    int handle;
    int value;
    int r;

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f3860);
        return;
    }
    handle = ply->handle;
    if (ply->paused == 0 && sw == 0)
        return;
    if (FUN_00294d70() == 1 && ply->f12 == 1) {
        if (FUN_002adba0(handle, 6, &value) == 0) {
            if (value == 1)
                FUN_0029b018(ply);
        } else
            FUN_0029b018(ply);
    }
    if (FUN_002aa340(handle, sw) != 0) {
        FUN_00294ef8(-310);
        FUN_0029a320(DAT_004f3888, sw == 1 ? DAT_004f38b0 : DAT_004f38b8);
    }
    FUN_00299bc0(ply->sub, sw);
    ply->paused = sw;
}
