#include <math.h>
#include <string.h>

extern int DAT_00499cd0;

/* Clamp a 32-bit sample to the 16-bit range. A bare if, not do { } while (0): the loop wrapper changes the decoders'
 * code. */
#define ADX_CLAMP16(v) \
    if ((v) > 32767 || (v) < -32768) { \
        if ((v) < -32768) { \
            (v) = -32768; \
        } else if ((v) > 32767) { \
            (v) = 32767; \
        } \
    }

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
int ADX_IsAdxFmt(unsigned char *hdr, int size, short *ofst)
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

int ADX_DecodeInfo(unsigned char *hdr, int len, short *ofst, signed char *type, signed char *bsize,
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

int ADX_DecodeInfoExADPCM2(unsigned char *hdr, int size, short *out) {
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

int ADX_DecodeInfoExIdly(unsigned char *hdr, int size, short *start, short *end)
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

int ADX_CalcHdrInfoLen(int type, int len, int ofst, unsigned int blk)
{
    if (type == 0) {
        return ((len + (ofst + blk) + 33) / blk) * blk - ofst;
    }
    return ((len + (ofst + blk) + 57) / blk) * blk - ofst;
}

/* Signed value of a 4-bit ADX nibble. Defined here, after the "(c)CRI" literal, to keep retail's .rodata order. */
static const int adx_nibble_tbl[16] = {0, 1, 2, 3, 4, 5, 6, 7, -8, -7, -6, -5, -4, -3, -2, -1};

/* Decodes nblk 18-byte blocks of 4-bit ADX into obuf; dly holds the two previous samples, and the scale is scrambled with
 * the key stream in *seed (mul, add). Stops early at the first end block (scale top bit set) and returns the blocks done. */
int ADX_DecodeMono4(unsigned char *ibuf, int nblk, short *obuf, short *dly, short k0, short k1,
                    unsigned short *seed, short mul, short add)
{
    unsigned char *p;
    int i;
    int j;
    int hdr;
    int scale;
    int key;
    int b;
    int nib;
    int v;
    int d1;
    int d2;

    p = ibuf;
    d1 = dly[0];
    d2 = dly[1];
    for (i = 0; i < nblk; i++) {
        hdr = (short)(((*(short *)p & 0xFF00) >> 8) | ((*(short *)p << 8) & 0xFF00));
        if (hdr & 0x8000) {
            return i;
        }
        scale = ((hdr ^ *seed) & 0x1FFF) + 1;
        key = *seed * mul + add;
        *seed = key & 0x7FFF;
        p += 2;
        for (j = 0; j < 32; j += 2) {
            b = (signed char)*p;
            nib = b >> 4;
            p++;
            v = ((k0 * d1 + k1 * d2) >> 12) + nib * scale;
            ADX_CLAMP16(v);
            d2 = d1;
            d1 = v;
            *obuf++ = d1;
            b = adx_nibble_tbl[b & 0xF];
            v = ((k0 * d1 + k1 * d2) >> 12) + b * scale;
            ADX_CLAMP16(v);
            d2 = d1;
            d1 = v;
            *obuf++ = d1;
        }
    }
    dly[0] = d1;
    dly[1] = d2;
    return nblk;
}

/* Stereo 4-bit ADX mixed down to mono: decodes both channels like ADX_DecodeSte4 does and writes (l + r) * 0.7 to
 * both outputs. */
int ADX_DecodeSte4AsMono(unsigned char *ibuf, int nblk, short *obufl, short *dlyl, short *obufr, short *dlyr,
                 short k0, short k1, unsigned short *seed, short mul, short add)
{
    unsigned char *p;
    int i;
    int j;
    int n;
    int hdr;
    int scale_l;
    int scale_r;
    int key;
    int bl;
    int br;
    int nibl;
    int nibr;
    int v;
    int l1;
    int l2;
    int r1;
    int r2;

    p = ibuf;
    l1 = dlyl[0];
    l2 = dlyl[1];
    r1 = dlyr[0];
    r2 = dlyr[1];
    n = nblk / 2;
    for (i = 0; i < n; i++) {
        hdr = (short)(((*(short *)p & 0xFF00) >> 8) | ((*(short *)p << 8) & 0xFF00));
        if (hdr & 0x8000) {
            return i * 2;
        }
        scale_l = ((hdr ^ *seed) & 0x1FFF) + 1;
        key = (*seed * mul + add) & 0x7FFF;
        *seed = key;
        hdr = (short)(((*(short *)(p + 18) & 0xFF00) >> 8) | ((*(short *)(p + 18) << 8) & 0xFF00));
        if (hdr & 0x8000) {
            return i * 2;
        }
        scale_r = ((hdr ^ key) & 0x1FFF) + 1;
        *seed = (mul * key + add) & 0x7FFF;
        p += 2;
        for (j = 0; j < 32; j += 2) {
            bl = (signed char)p[0];
            nibl = bl >> 4;
            br = (signed char)p[18];
            nibr = br >> 4;
            p++;
            v = ((k0 * l1 + k1 * l2) >> 12) + nibl * scale_l;
            ADX_CLAMP16(v);
            l2 = l1;
            l1 = v;
            v = ((k0 * r1 + k1 * r2) >> 12) + nibr * scale_r;
            ADX_CLAMP16(v);
            r2 = r1;
            r1 = v;
            v = (l1 + r1) * 7 / 10;
            ADX_CLAMP16(v);
            *obufl++ = *obufr++ = v;
            bl = adx_nibble_tbl[bl & 0xF];
            br = adx_nibble_tbl[br & 0xF];
            v = ((k0 * l1 + k1 * l2) >> 12) + bl * scale_l;
            ADX_CLAMP16(v);
            l2 = l1;
            l1 = v;
            v = ((k0 * r1 + k1 * r2) >> 12) + br * scale_r;
            ADX_CLAMP16(v);
            r2 = r1;
            r1 = v;
            v = (l1 + r1) * 7 / 10;
            ADX_CLAMP16(v);
            *obufl++ = *obufr++ = v;
        }
        p += 18;
    }
    dlyl[0] = l1;
    dlyl[1] = l2;
    dlyr[0] = r1;
    dlyr[1] = r2;
    return nblk;
}

/* Stereo 4-bit ADX: each block pair is a left block followed by a right block, both scales scrambled with the key
 * stream in *seed. Writes the two channels to obufl and obufr; returns early (with the blocks done) at an end block. */
int ADX_DecodeSte4AsSte(unsigned char *ibuf, int nblk, short *obufl, short *dlyl, short *obufr, short *dlyr,
                 short k0, short k1, unsigned short *seed, short mul, short add)
{
    unsigned char *p;
    int i;
    int j;
    int n;
    int hdr;
    int scale_l;
    int scale_r;
    int key;
    int bl;
    int br;
    int nibl;
    int nibr;
    int v;
    int l1;
    int l2;
    int r1;
    int r2;

    p = ibuf;
    l1 = dlyl[0];
    l2 = dlyl[1];
    r1 = dlyr[0];
    r2 = dlyr[1];
    n = nblk / 2;
    for (i = 0; i < n; i++) {
        hdr = (short)(((*(short *)p & 0xFF00) >> 8) | ((*(short *)p << 8) & 0xFF00));
        if (hdr & 0x8000) {
            return i * 2;
        }
        scale_l = ((hdr ^ *seed) & 0x1FFF) + 1;
        key = (*seed * mul + add) & 0x7FFF;
        *seed = key;
        hdr = (short)(((*(short *)(p + 18) & 0xFF00) >> 8) | ((*(short *)(p + 18) << 8) & 0xFF00));
        if (hdr & 0x8000) {
            return i * 2;
        }
        scale_r = ((hdr ^ key) & 0x1FFF) + 1;
        *seed = (mul * key + add) & 0x7FFF;
        p += 2;
        for (j = 0; j < 32; j += 2) {
            bl = (signed char)p[0];
            nibl = bl >> 4;
            br = (signed char)p[18];
            nibr = br >> 4;
            p++;
            v = ((k0 * l1 + k1 * l2) >> 12) + nibl * scale_l;
            ADX_CLAMP16(v);
            l2 = l1;
            l1 = v;
            v = ((k0 * r1 + k1 * r2) >> 12) + nibr * scale_r;
            ADX_CLAMP16(v);
            r2 = r1;
            r1 = v;
            *obufl++ = l1;
            *obufr++ = r1;
            bl = adx_nibble_tbl[bl & 0xF];
            br = adx_nibble_tbl[br & 0xF];
            v = ((k0 * l1 + k1 * l2) >> 12) + bl * scale_l;
            ADX_CLAMP16(v);
            l2 = l1;
            l1 = v;
            v = ((k0 * r1 + k1 * r2) >> 12) + br * scale_r;
            ADX_CLAMP16(v);
            r2 = r1;
            r1 = v;
            *obufl++ = l1;
            *obufr++ = r1;
        }
        p += 18;
    }
    dlyl[0] = l1;
    dlyl[1] = l2;
    dlyr[0] = r1;
    dlyr[1] = r2;
    return nblk;
}

int ADX_DecodeSte4(unsigned char *ibuf, int nblk, short *obufl, short *dlyl, short *obufr, short *dlyr,
                 short k0, short k1, unsigned short *seed, short mul, short add)
{
    if (DAT_00499cd0 == 0) {
        return ADX_DecodeSte4AsSte(ibuf, nblk, obufl, dlyl, obufr, dlyr, k0, k1, seed, mul, add);
    }
    return ADX_DecodeSte4AsMono(ibuf, nblk, obufl, dlyl, obufr, dlyr, k0, k1, seed, mul, add);
}
