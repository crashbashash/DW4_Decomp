typedef struct SeqScanInfo {
    char pad[12];
    void *codec;
    char pad16[24];
    unsigned char f40;
    char pad41[3];
    int f44;
} SeqScanInfo;

extern unsigned char DAT_0057fab8[];
extern char DAT_004f4b18[];
void *memcpy(void *dst, const void *src, unsigned int n);
int FUN_0029b3a8(unsigned char *p, int n, int *out);

int FUN_0029f918(void *src, int size, SeqScanInfo *info)
{
    unsigned char *p;
    int tmp[4];

    if (size > 2048)
        size = 2048;
    memcpy(DAT_0057fab8, src, size);
    p = DAT_0057fab8;
    for (; size > 0; size -= 4, p += 4) {
        if (FUN_0029b3a8(p, size, tmp) != 0) {
            info->codec = DAT_004f4b18;
            info->f40 = p[7];
            info->f44 = (p[8] << 24) | (p[9] << 16) | (p[10] << 8) | p[11];
            return 1;
        }
    }
    return 0;
}
