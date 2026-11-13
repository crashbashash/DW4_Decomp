typedef struct {
    int valid;
    char pad4[20];
    long long f24;
    long long f32;
    int f40;
    int f44;
} Src2a2d80;

typedef struct {
    char pad0[16];
    long long f16;
    char pad24[20];
    int f44;
    int f48;
} Dst2a2d80;

Src2a2d80 *FUN_002a2ed0(void);
void FUN_002a0220(void *);
void FUN_002a2e28(void *);
int sfd_DecodePicTexts(void *, Dst2a2d80 *, Src2a2d80 *);

int FUN_002a2d80(char *obj) {
    Src2a2d80 *src = FUN_002a2ed0();
    Dst2a2d80 *dst;
    char *sub;
    int r;

    if (src == 0) {
        return 0;
    }
    if (src->valid == 0) {
        return 0;
    }
    dst = *(Dst2a2d80 **)(obj + 8052);
    FUN_002a0220(obj);
    FUN_002a2e28(obj);
    sub = obj + 3368;
    r = sfd_DecodePicTexts(obj, dst, src);
    if (r == 0) {
        dst->f44 = src->f40;
        *(long long *)(sub + 336) = src->f24;
        dst->f48 = src->f44;
        dst->f16 = src->f32;
    }
    return r;
}
