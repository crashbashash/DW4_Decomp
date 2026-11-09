typedef struct PsHdrInfo {
    int f0;
    void *codec;
    void *f8;
    int f12;
    int stride;
    int width;
    int height;
    int duration;
    int rate;
} PsHdrInfo;

typedef struct PsHdrHeader {
    int valid;
    int f4;
    int f8;
    int duration;
    char pad16[84];
    int width;
    int height;
    int rate;
} PsHdrHeader;

extern PsHdrHeader DAT_005802b8;
extern char DAT_004f4dd0[];
int FUN_0029fff0(char *p, int n);
void FUN_0029f640(char *p, int n, PsHdrHeader *hdr);

void FUN_0029f550(char *p, int n, PsHdrInfo *info)
{
    int stride = info->stride;
    int i;
    PsHdrHeader *hdr;

    for (i = 0; ; i++) {
        if (FUN_0029fff0(p, n) != 0)
            break;
        n -= stride;
        p += stride;
        if (i >= 3 || n <= 0)
            return;
    }
    hdr = &DAT_005802b8;
    hdr->valid = 0;
    FUN_0029f640(p, n, hdr);
    if (hdr->valid == 0)
        return;
    if (hdr->duration > 0)
        info->duration = hdr->duration;
    if (hdr->width > 0)
        info->width = hdr->width;
    if (hdr->height > 0)
        info->height = hdr->height;
    if (hdr->rate > 0) {
        info->rate = hdr->rate;
        info->f8 = DAT_004f4dd0;
    }
}
