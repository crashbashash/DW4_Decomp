typedef struct {
    char pad0[7];
    unsigned char f7;
    unsigned char f8;
    unsigned char f9;
    char pad10[2];
    int f12;
    char pad16[26];
    unsigned short f42;
} AdxHeader;

int FUN_0025e668(AdxHeader *hdr, int size, short *hdrlen, char *f12, char *f13, signed char *f15,
                 signed char *f14, int *f20, int *f24, int *f16, short *f156)
{
    *hdrlen = hdr->f7 << 4;
    *f14 = (hdr->f9 & 3) + 1;
    *f20 = hdr->f42;
    switch (hdr->f8) {
    case 0:
        *f13 = 16;
        *f15 = *f14 * 2;
        *f16 = 1;
        *f156 = 0;
        *f24 = hdr->f12 / 2;
        break;
    case 1:
        *f13 = 8;
        {
            int ch = *f14;

            *f15 = ch;
        }
        *f16 = 1;
        *f156 = 1;
        *f24 = hdr->f12;
        break;
    case 2:
    case 3:
        *f13 = 4;
        {
            int ch = *f14;

            *f15 = ch;
        }
        *f16 = 2;
        *f156 = 2;
        *f24 = hdr->f12 * 2;
        break;
    }
    *f15 = 2;
    *f16 = 1;
    *f24 = hdr->f12 / 2;
    *f13 = 16;
    *f12 = -1;
    return 0;
}
