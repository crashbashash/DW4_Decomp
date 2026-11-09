typedef struct TagScanHdr {
    char pad[860];
    int x;
    int y;
    int z;
    char pad872[44];
    int mode;
} TagScanHdr;

extern char DAT_004f29f0[];
extern char DAT_004f29f8[];
int atoi(const char *s);
int strncmp(const char *a, const char *b, unsigned int n);
int FUN_0028dc78(char *p);

int FUN_002906e8(TagScanHdr *hdr, char *buf, int size)
{
    int n = size - 4;
    char *base = buf + 4;
    int i;
    char *p;

    for (i = 0; i < n; ) {
        p = base + i;
        i++;
        if (strncmp(p, DAT_004f29f0, 7) == 0)
            hdr->mode = atoi(p + 16) != 0 ? 3 : 0;
        if (strncmp(p, DAT_004f29f8, 7) == 0) {
            hdr->x = atoi(p + 16);
            hdr->y = atoi(p + 24);
            hdr->z = atoi(p + 32);
        }
        if (FUN_0028dc78(p) != 0)
            break;
    }
    return 0;
}
