typedef struct VidCfg {
    int w[9];
} VidCfg;

typedef struct VidBuf2 {
    int w[2];
} VidBuf2;

typedef struct VidBuf16 {
    int w[16];
} VidBuf16;

typedef struct VidWork {
    int dec;
    VidCfg cfg;
    VidBuf2 work;
    VidBuf16 bufs;
    char pad112[3984];
    char *base;
    int count;
    int size;
} VidWork;

typedef struct VidObj {
    char pad[8120];
    VidWork *work;
} VidObj;

extern VidCfg DAT_005855b0;
extern VidBuf2 DAT_005855d8;
extern VidBuf16 DAT_005855e0;
extern char *DAT_00585620;
extern int DAT_00585624;
extern int DAT_00585628;
int FUN_002a0bb8(VidObj *obj, int code);
int FUN_002a7d18(int dec);
void FUN_002a9bc8(VidObj *obj);

int FUN_002a7b88(VidObj *obj)
{
    VidWork *work = obj->work;
    int dec = work->dec;

    if (dec == 0)
        return 0;
    DAT_005855b0 = work->cfg;
    DAT_005855d8 = work->work;
    DAT_005855e0 = work->bufs;
    DAT_00585620 = work->base;
    DAT_00585624 = work->count;
    DAT_00585628 = work->size;
    FUN_002a9bc8(obj);
    if (FUN_002a7d18(dec) != 0)
        return FUN_002a0bb8(obj, 0xFF000F0C);
    work->dec = 0;
    return 0;
}
