typedef struct GetHdrInfHdr {
    int valid;
    int type;
    int width;
    int height;
    int rate;
    int f20;
    int f24;
    int f28;
    int f32;
    int frames;
    int f40;
} GetHdrInfHdr;

typedef struct GetHdrInfInfo {
    signed char ok0;
    signed char ok1;
    char pad2[18];
    int width;
    int height;
    int f28;
    int rate;
    int f36;
    signed char f40;
    char pad41[3];
    int frames;
    int pad48[4];
} GetHdrInfInfo;

extern char DAT_004f3018[];
extern char DAT_004f3040[];
void *memset(void *s, int c, unsigned int n);
int FUN_002933f8(GetHdrInfInfo *info);
int FUN_00293448(GetHdrInfHdr *hdr);
void FUN_00294390(char *buf, int size, GetHdrInfHdr *hdr);
void FUN_0029a320(const char *format, ...);
void FUN_0029f160(char *buf, int size, GetHdrInfInfo *info);

/* matching construct: 120-order sweep of the field copies */
void FUN_00293230(char *buf, int size, GetHdrInfHdr *out)
{
    GetHdrInfHdr hdr;
    GetHdrInfInfo info;

    if (buf == 0 || out == 0) {
        FUN_0029a320(DAT_004f3018);
        return;
    }
    if (size <= 0) {
        FUN_0029a320(DAT_004f3040);
        return;
    }
    memset(&hdr, 0, sizeof(hdr));
    FUN_0029f160(buf, size, &info);
    if (info.ok0 == 0 || info.ok1 == 0) {
        *out = hdr;
        out->valid = 0;
        return;
    }
    hdr.type = FUN_002933f8(&info);
    hdr.width = info.width;
    hdr.height = info.height;
    hdr.rate = info.rate;
    hdr.frames = info.frames;
    hdr.f40 = info.f40;
    FUN_00294390(buf, size, &hdr);
    hdr.valid = FUN_00293448(&hdr);
    *out = hdr;
}
