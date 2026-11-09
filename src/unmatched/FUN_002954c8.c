typedef struct SfdStart2Ply {
    char pad[8];
    int stat;
    char pad12[52];
    int handle;
    char pad68[49];
    signed char f117;
    signed char f118;
    char pad119[17];
    int f136;
    char pad140[520];
    char sub[4];
} SfdStart2Ply;

extern char DAT_004f36f8[];
extern char DAT_004f3728[];
int FUN_00292af0(SfdStart2Ply *ply);
void FUN_002945c8(SfdStart2Ply *ply);
void FUN_00294a30(SfdStart2Ply *ply);
void FUN_00295358(SfdStart2Ply *ply);
void FUN_002955c0(SfdStart2Ply *ply);
void FUN_00295908(SfdStart2Ply *ply, int mode);
int FUN_00298318(SfdStart2Ply *ply);
void FUN_00298378(SfdStart2Ply *ply);
void FUN_00298398(SfdStart2Ply *ply);
void FUN_00299a38(void *sub);
void FUN_00299bc0(void *sub, int on);
void FUN_00299e08(SfdStart2Ply *ply);
void FUN_0029a320(const char *format, ...);

/* matching construct: permuter, reduced by hand: the sub-handle read just before its use */
void FUN_002954c8(SfdStart2Ply *ply)
{
    void *sub;

    FUN_00294a30(ply);
    if (ply->handle != 0) {
        if (FUN_00292af0(ply) != 0) {
            FUN_0029a320(DAT_004f36f8);
            return;
        }
        FUN_00299e08(ply);
        FUN_00298398(ply);
        if (FUN_00298318(ply) != 0) {
            FUN_0029a320(DAT_004f3728);
            return;
        }
        FUN_00298378(ply);
        FUN_002945c8(ply);
    }
    FUN_002955c0(ply);
    FUN_00295358(ply);
    FUN_00295908(ply, ply->f118);
    sub = ply->sub;
    FUN_00299bc0(sub, 1);
    FUN_00299a38(sub);
    ply->f136 = 0;
    ply->f117 = 0;
    ply->stat = 1;
}
