typedef struct {
    int fmt;
    int sfreq;
    int nch;
    int bps;
    int nsmpl;
    int lpcnt;
    int f24;
    int f28;
} AdxtHdrInfo;

typedef struct {
    char pad0[2];
    signed char bps;
    signed char nch;
    int sfreq;
    int nsmpl;
    char pad12[2];
    short lpcnt;
    char pad16[4];
    int f20;
    char pad24[4];
    int f28;
    char pad32[28];
    signed char type;
    char pad61[3];
} AdxHdrFields;

extern char DAT_004edfd0[];
extern char DAT_004ee008[];
extern char DAT_004ee048[];
void FUN_002607e8(const char *message);
void *memset(void *dst, int value, unsigned int size);
int FUN_00262d30(void *buf, int size, void *work, AdxHdrFields *hdr);

void FUN_00263060(void *buf, int size, AdxtHdrInfo *out)
{
    AdxtHdrInfo info;
    AdxHdrFields hdr;
    char work[16];
    int ret;

    if (buf == 0 || out == 0) {
        FUN_002607e8(DAT_004edfd0);
        return;
    }
    memset(&info, 0, sizeof(info));
    memset(&hdr, 0, sizeof(hdr));
    ret = FUN_00262d30(buf, size, work, &hdr);
    if (ret == -4) {
        FUN_002607e8(DAT_004ee008);
        return;
    }
    if (ret < 0) {
        FUN_002607e8(DAT_004ee048);
        return;
    }
    if (hdr.type == 6) {
        info.fmt = 2;
    } else {
        info.fmt = 1;
    }
    info.sfreq = hdr.sfreq;
    info.nch = hdr.nch;
    info.bps = hdr.bps;
    info.nsmpl = hdr.nsmpl;
    info.lpcnt = hdr.lpcnt;
    info.f24 = hdr.f20;
    info.f28 = hdr.f28;
    *out = info;
}
