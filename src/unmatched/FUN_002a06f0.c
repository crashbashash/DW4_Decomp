typedef struct PicExtItem {
    int w[4];
} PicExtItem;

typedef struct PicExtInfo {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int f28;
    int f32;
    int f36;
    int f40;
    int f44;
    int f48;
} PicExtInfo;

typedef int (*Getter)();

int FUN_002a08c0(PicExtItem *h, int id, Getter get);
int FUN_002b1b50(PicExtItem *h, int id, int *ok);
int FUN_002b27d0();
int FUN_002b2840();
int FUN_002b28b8(PicExtItem *h, int id, int *a, int *b);
int FUN_002b2968();
int FUN_002b29d8();
int FUN_002b2a48();
int FUN_002b2ab8();
int FUN_002b2b28();
int FUN_002b2ba0();
int FUN_002b2c10();
int FUN_002b2c98();

void FUN_002a06f0(PicExtItem *h, int id, PicExtInfo *info)
{
    int ok;

    info->f0 = FUN_002a08c0(h, id, FUN_002b27d0);
    info->f4 = FUN_002a08c0(h, id, FUN_002b2840);
    if (FUN_002b28b8(h, id & 0xFF, &info->f8, &info->f12) == 0) {
        info->f8 = -1;
        info->f12 = -1;
    }
    info->f16 = FUN_002a08c0(h, id, FUN_002b2968);
    if (FUN_002b1b50(h, id & 0xFF, &ok) == 0)
        ok = 0;
    info->f20 = ok != 0;
    if (ok == 0)
        return;
    info->f24 = FUN_002a08c0(h, id, FUN_002b29d8);
    info->f28 = FUN_002a08c0(h, id, FUN_002b2a48);
    info->f32 = FUN_002a08c0(h, id, FUN_002b2ab8);
    info->f36 = FUN_002a08c0(h, id, FUN_002b2b28);
    info->f40 = FUN_002a08c0(h, id, FUN_002b2ba0);
    info->f44 = FUN_002a08c0(h, id, FUN_002b2c10);
    info->f48 = FUN_002a08c0(h, id, FUN_002b2c98);
}
