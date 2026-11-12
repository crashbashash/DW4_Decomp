float sqrtf(float);
float cosf(float);

extern int DAT_00499cd0;

#define SWAP16(x) (((x) >> 8) | (((x) << 8) & 0xFF00))

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

int FUN_0025f460(unsigned char *buf, int size, short *pos)
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

int FUN_0025f588(unsigned char *hdr, int len, short *ofst, signed char *type, signed char *bsize,
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

int FUN_0025f708(unsigned char *hdr, int size, unsigned char *ver, unsigned char *flag)
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

    if (FUN_0025f708(hdr, size, &ver, &flag) != 0) {
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

int FUN_0025fd38(unsigned char *hdr, int size, short *ofst)
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
