float sqrtf(float);
float cosf(float);
int memcmp(const void *a, const void *b, unsigned int size);
void *memcpy(void *dst, const void *src, unsigned int size);

extern int DAT_00499cd0;

#define SWAP16(x) (((x) >> 8) | (((x) << 8) & 0xFF00))
/* big-endian 16- and 32-bit header fields at byte offset o of b; the 32-bit tag is read byte by byte */
#define RD16(b, o) (((*(short *)((b) + (o)) >> 8) & 0xFF) | ((*(short *)((b) + (o)) << 8) & 0xFF00))
#define SWAP32(x) (((unsigned int)(x) >> 24) | ((x) << 24) | ((((x) << 8) & 0xFF0000) | (((x) >> 8) & 0xFF00)))
#define RD32(b, o) SWAP32(*(int *)((b) + (o)))
#define RDB32(b, o) (((b)[o] << 24) | ((b)[(o) + 1] << 16) | ((b)[(o) + 2] << 8) | (b)[(o) + 3])

void ADX_GetCoefficient(int arg0, int arg1, short *arg2, short *arg3) {
    float a, b, r, s, c;
s = sqrtf(2.0f);
c = cosf(((float) arg0 * 6.2831851f) / (float) arg1);
a = s - c;
b = sqrtf(2.0f) - 1.0f;
    r = (a - sqrtf((a + b) * (a - b))) / b;
    *arg2 = (short) (int) (2.0f * r * 4096.0f);
    *arg3 = (short) (int) (-r * r * 4096.0f);
}

int ADX_ScanInfoCode(unsigned char *buf, int size, short *pos)
{
    int i;
    int found;
    int code;

    found = 0x7FFFFFFF;
    /* matching construct: hand search — the sync code compared through a local, which keeps it out of the loop */
    code = 0x80;
    for (i = 0; i < size - 1; i += 2) {
        if (*(short *)(buf + i) == code) {
            if (i < found) {
                found = i;
            }
            break;
        }
    }
    if (found != 0x7FFFFFFF) {
        *pos = found;
        return 0;
    }
    *pos = 0;
    return -1;
}

/* Is the buffer an ADX header that ends with the (c)CRI copyright? Returns 1 and the data offset if so. */
int ADX_IsCopyrightHeader(unsigned char *hdr, int size, short *ofst)
{
    int hdrlen;
    int copyright;

    if (size < 16) {
        return 0;
    }
    if ((hdr[1] | (hdr[0] << 8)) != 0x8000) {
        return 0;
    }
    hdrlen = ((hdr[2] << 8) | hdr[3]) + 4;
    /* the six copyright bytes end the header, just before the data */
    copyright = hdrlen - 6;
    if (size < 0x8000) {
        return 0;
    }
    if (memcmp(hdr + copyright, "(c)CRI", 6) != 0) {
        return 0;
    }
    if (ofst != 0) {
        *ofst = hdrlen;
    }
    return 1;
}

int ADX_DecodeHeader(unsigned char *hdr, int len, short *ofst, signed char *type, signed char *bsize,
                 signed char *bits, signed char *nch, int *sfreq, int *nsmpl, int *blksmpl)
{
    if (len < 16) {
        return -1;
    }
    if ((hdr[1] | (hdr[0] << 8)) != 0x8000) {
        return -2;
    }
    *ofst = ((hdr[2] << 8) | hdr[3]) + 4;
    *type = hdr[4];
    *bits = hdr[5];
    *bsize = hdr[6];
    *nch = hdr[7];
    *sfreq = (hdr[8] << 24) | (hdr[9] << 16) | (hdr[10] << 8) | hdr[11];
    *nsmpl = (hdr[12] << 24) | (hdr[13] << 16) | (hdr[14] << 8) | hdr[15];
    if (*bsize == 0) {
        *blksmpl = 0;
    } else {
        *blksmpl = (*bits * 8 - 16) / *bsize;
    }
    return 0;
}

int FUN_0025f688(unsigned char *hdr, int size, short *out) {
    const unsigned short *words = (const unsigned short *)hdr;
    if (size < 18) {
        return -1;
    }
    if ((unsigned short)SWAP16(words[0]) != 0x8000) {
        return -2;
    }
    if ((short)((words[1] << 8) & 0xFF00 | hdr[3]) < 14) {
        return -1;
    }
    *out = SWAP16(words[8]);
    return 0;
}

int ADX_DecodeInfoExVer(unsigned char *hdr, int size, unsigned char *ver, unsigned char *flag)
{
    const unsigned short *words = (const unsigned short *)hdr;
    if (size < 20) {
        return -1;
    }
    if ((unsigned short)SWAP16(words[0]) != 0x8000) {
        return -2;
    }
    if ((short)((words[1] << 8) & 0xFF00 | hdr[3]) < 16) {
        return -1;
    }
    *ver = hdr[18];
    *flag = hdr[19];
    return 0;
}

int FUN_0025f780(unsigned char *hdr, int size, short *start, short *end)
{
    const unsigned short *words = (const unsigned short *)hdr;
    unsigned char ver;
    unsigned char flag;

    if (ADX_DecodeInfoExVer(hdr, size, &ver, &flag) != 0) {
        return -1;
    }
    if (ver >= 4) {
        if (size < 32) {
            return -1;
        }
        if ((unsigned short)SWAP16(words[0]) != 0x8000) {
            return -2;
        }
        if ((short)((words[1] << 8) & 0xFF00 | hdr[3]) < 28) {
            return -1;
        }
        start[0] = SWAP16(words[12]);
        end[0] = SWAP16(words[13]);
        start[1] = SWAP16(words[14]);
        end[1] = SWAP16(words[15]);
    } else {
        end[1] = 0;
        start[1] = 0;
        end[0] = 0;
        start[0] = 0;
    }
    return 0;
}

/* ADX_DecodeInfoExLoop: the loop block of a version 3 (at 0x14) or version 4 (at 0x20) header: the
 * loop type, the loop count (only a single loop is accepted, else -2), the loop flag and the loop's
 * start and end in samples and in bytes. The fields are big-endian. */
int ADX_DecodeInfoExLoop(unsigned char *hdr, int size, int *lptype, short *nloop, short *lpflg, int *lpstart,
                 int *lpstartofst, int *lpend, int *lpendofst)
{
    const unsigned short *words = (const unsigned short *)hdr;
    unsigned char ver;
    unsigned char flag;
    int ret;
    int need;
    int pos;

    *nloop = 0;
    ret = ADX_DecodeInfoExVer(hdr, size, &ver, &flag);
    if (ret != 0) {
        return ret;
    }
    need = 48;
    if (ver == 4) {
        need = 60;
    }
    if (size < need) {
        return -1;
    }
    if ((unsigned short)SWAP16(words[0]) != 0x8000) {
        return -2;
    }
    if ((short)((words[1] << 8) & 0xFF00 | hdr[3]) < need - 4) {
        return -1;
    }
    pos = 20;
    if (ver == 4) {
        pos = 32;
    }
    *lptype = (short)RD16(hdr, pos);
    pos += 2;
    *nloop = RD16(hdr, pos);
    pos += 2;
    if (*nloop != 1) {
        return -2;
    }
    pos += 2;
    *lpflg = RD16(hdr, pos);
    pos += 2;
    *lpstart = RD32(hdr, pos);
    pos += 4;
    *lpstartofst = RD32(hdr, pos);
    pos += 4;
    *lpend = RD32(hdr, pos);
    pos += 4;
    *lpendofst = RD32(hdr, pos);
    return 0;
}

/* ADX_DecodeInfoAinf: the AINF chunk after the loop block (skipped when the header has no loop): its
 * size, the 16-byte data id, the default output volume and the two pans. */
int ADX_DecodeInfoAinf(unsigned char *hdr, int size, int *ainfsiz, char *ainf, short *volume, short *pan)
{
    const unsigned short *words = (const unsigned short *)hdr;
    unsigned char ver;
    unsigned char flag;
    int ret;
    int need;
    int pos;
    short nloop;
    int magic;

    *ainfsiz = 0;
    ret = ADX_DecodeInfoExVer(hdr, size, &ver, &flag);
    if (ret != 0) {
        return ret;
    }
    need = 60;
    if (ver == 4) {
        need = 72;
    }
    if (size < need) {
        return -1;
    }
    if ((unsigned short)SWAP16(words[0]) != 0x8000) {
        return -2;
    }
    if ((short)((words[1] << 8) & 0xFF00 | hdr[3]) < need - 4) {
        return -1;
    }
    pos = 20;
    if (ver == 4) {
        pos = 32;
    }
    pos += 2;
    nloop = RD16(hdr, pos);
    pos += 2;
    if (nloop != 0) {
        pos += 20;
    }
    magic = RDB32(hdr, pos);
    pos += 4;
    if (magic != 0x41494E46) { /* "AINF" */
        return -2;
    }
    *ainfsiz = RD32(hdr, pos);
    pos += 4;
    memcpy(ainf, hdr + pos, 16);
    pos += 16;
    *volume = RD16(hdr, pos);
    pos += 4;
    pan[0] = RD16(hdr, pos);
    pos += 2;
    pan[1] = RD16(hdr, pos);
    return 0;
}

int ADX_DecodeFooter(unsigned char *hdr, int size, short *ofst)
{
    const unsigned short *words = (const unsigned short *)hdr;
    if (size < 16) {
        return -1;
    }
    if ((unsigned short)SWAP16(words[0]) != 0x8001) {
        return -2;
    }
    *ofst = ((words[1] << 8) & 0xFF00 | hdr[3]) + 4;
    return 0;
}

int FUN_0025fd98(int type, int len, int ofst, unsigned int blk)
{
    if (type == 0) {
        return ((len + (ofst + blk) + 33) / blk) * blk - ofst;
    }
    return ((len + (ofst + blk) + 57) / blk) * blk - ofst;
}

int FUN_0025ffd0(unsigned char *ibuf, int nblk, short *obufr, short *dlyl, short *obufl, short *dlyr,
                 short k0, short k1, unsigned short *seed, short mul, short add);
int FUN_00260398(unsigned char *ibuf, int nblk, short *obufl, short *dlyl, short *obufr, short *dlyr,
                 short k0, short k1, unsigned short *seed, short mul, short add);

int ADX_DecodeSte4(unsigned char *ibuf, int nblk, short *obufl, short *dlyl, short *obufr, short *dlyr,
                 short k0, short k1, unsigned short *seed, short mul, short add)
{
    if (DAT_00499cd0 == 0) {
        return FUN_00260398(ibuf, nblk, obufl, dlyl, obufr, dlyr, k0, k1, seed, mul, add);
    }
    return FUN_0025ffd0(ibuf, nblk, obufl, dlyl, obufr, dlyr, k0, k1, seed, mul, add);
}
