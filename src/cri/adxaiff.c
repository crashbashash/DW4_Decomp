/* CRI ADXB AIFF reader: plays big-endian PCM from an AIFF ("FORM" ... "AIFF") file through an ADXB decoder
 * handle. The samples reach the output as they are, the 8-bit ones scaled to 16 bits. */
#include "dw4/cri/adxb.h"
#include <string.h>

/* AdxbObj.cdctype for an AIFF stream */
enum AdxbAiffFmt {
    ADXB_AIFF_PCM_16 = 0,
    ADXB_AIFF_PCM_8 = 1
};

#define BSWAP16(x) (((x) >> 8) | (((x) << 8) & 0xFF00))

extern char FORM[];
extern char AIFF[];

/* AIFF chunk ids read as little-endian words */
enum AiffChunk {
    AIFF_FORM = 0x4D524F46,
    AIFF_AIFF = 0x46464941,
    AIFF_COMM = 0x4D4D4F43,
    AIFF_SSND = 0x444E5353
};

#define GET16(p) ((p)[0] | ((p)[1] << 8))
#define GET32(p) ((p)[0] | ((p)[1] << 8) | ((p)[2] << 16) | ((p)[3] << 24))
#define SWAP32(x) ((((x) >> 24) & 0xFF) | (((x) >> 8) & 0xFF00) | (((x) << 8) & 0xFF0000) | ((x) << 24))
/* matching construct: the chunk lengths and the SSND offset swap with an unsigned top byte, which keeps the
 * ORs in source order */
#define SWAP32_LEN(x) ((((x) >> 24) & 0xFF) | (((x) >> 8) & 0xFF00) | (((x) << 8) & 0xFF0000) | ((unsigned int)(x) << 24))

/* Walks the chunks: COMM gives the channel count, sample count, bit depth and the 80-bit sample rate, SSND the
 * start of the samples. */
unsigned char *AIFF_GetInfo(unsigned char *buf, int *sfreq, int *nch, int *bits, int *nsmpl)
{
    unsigned char *p;
    unsigned char *end;
    unsigned char *data;
    unsigned int id;
    int size;
    int word;
    unsigned short w16;
    unsigned int ofs;
    unsigned short exp;
    unsigned short mant;
    int nsmp;
    int have_ssnd;
    int have_comm;

    p = buf;
    id = GET32(p);
    p += 4;
    size = GET32(p);
    size = SWAP32_LEN(size);
    p += 4;
    word = GET32(p);
    p += 4;
    data = 0;
    have_ssnd = 0;
    have_comm = 0;
    if (id != AIFF_FORM) {
        return 0;
    }
    if (word != AIFF_AIFF) {
        return 0;
    }
    end = p + size - 4;
    while (p < end) {
        id = GET32(p);
        p += 4;
        size = GET32(p);
        size = SWAP32_LEN(size);
        p += 4;
        switch (id) {
        case AIFF_COMM:
            if (!have_comm) {
                if (size < 18) {
                    return 0;
                }
                have_comm = 1;
                w16 = GET16(p);
                p += 2;
                *nch = BSWAP16(w16);
                nsmp = GET32(p);
                p += 4;
                *nsmpl = SWAP32(nsmp);
                w16 = GET16(p);
                p += 2;
                *bits = BSWAP16(w16);
                exp = GET16(p);
                p += 2;
                mant = GET16(p);
                p += 8;
                *sfreq = (unsigned short)BSWAP16(mant) >> (0x400E - (unsigned short)BSWAP16(exp));
                if (have_ssnd) {
                    return data;
                }
            }
            break;
        case AIFF_SSND:
            if (!have_ssnd) {
                have_ssnd = 1;
                ofs = GET32(p);
                p += 4;
                ofs = SWAP32_LEN(ofs);
                data = p + ofs;
                if (have_comm) {
                    return data;
                }
            }
            break;
        default:
            p += (size + 1) & ~1;
            break;
        }
    }
    return data;
}

int ADXB_CheckAiff(unsigned char *hdr)
{
    if (memcmp(hdr, FORM, 4) == 0 && memcmp(hdr + 8, AIFF, 4) == 0) {
        return 1;
    }
    return 0;
}

/* Header fields in ADX_DecodeInfo's form; the header is at least 4096 bytes. */
int ADX_DecodeInfoAiff(unsigned char *buf, int len, short *hdrlen, signed char *hdrtype, signed char *fmtbps,
                       signed char *blklen, signed char *nch, int *sfreq, int *nsmpl, int *blksmpl)
{
    int freq;
    int ch;
    int bits;
    int smpl;
    unsigned char *data;

    if (len < 4096) {
        *hdrlen = 0;
        return -1;
    }
    data = AIFF_GetInfo(buf, &freq, &ch, &bits, &smpl);
    if (data == 0) {
        return -1;
    }
    *hdrlen = data - buf;
    if (*hdrlen <= 0) {
        return -1;
    }
    *sfreq = freq;
    *nch = ch;
    *fmtbps = bits;
    *nsmpl = smpl;
    *hdrtype = -1;
    *blklen = *nch * *fmtbps / 8;
    *blksmpl = 1;
    return 0;
}

/* matching construct: 150-step hill climb over the order of the copies after the call */
int ADXB_DecodeHeaderAiff(AdxbObj *adxb, unsigned char *hdr, int size)
{
    short hdrlen;

    adxb->hdcdflag = 1;
    if (ADX_DecodeInfoAiff(hdr, size, &hdrlen, &adxb->code, &adxb->bps, &adxb->blklen, &adxb->nch,
                           &adxb->sfreq, &adxb->total_nsmpl, &adxb->blknsmpl) < 0) {
        return 0;
    }
    adxb->lp_eofst = 0;
    adxb->lp_epos = 0;
    adxb->lp_sofst = 0;
    adxb->lp_spos = 0;
    adxb->lp_ins_nsmpl = 0;
    adxb->cof = 0;
    adxb->lp_type = 0;
    adxb->nloop = 0;
    adxb->dp.nch = adxb->nch;
    adxb->dp.blksize = adxb->blklen;
    adxb->dp.pcmbuf = adxb->pcmbuf;
    adxb->fmttype = ADXB_FORMAT_AIFF;
    adxb->dp.blknsmpl = adxb->blknsmpl;
    adxb->curwpos = 0;
    adxb->dp.pcmbsize = adxb->pcmbsize;
    adxb->total_ndecsmpl = 0;
    adxb->dp.pcmbdist = adxb->pcmbdist;
    if (adxb->bps == 8) {
        adxb->cdctype = ADXB_AIFF_PCM_8;
    } else {
        adxb->cdctype = ADXB_AIFF_PCM_16;
    }
    return hdrlen;
}

/* 16-bit samples, byte-swapped from big-endian. */
void ADXB_ExecOneAiff16(AdxbObj *adxb)
{
    AdxDecPara *buf;
    unsigned short *src;
    short *dst;
    short *dst2;
    unsigned int sample;
    int n;
    int i;

    buf = &adxb->dp;
    src = (unsigned short *)buf->ibuf;
    if (adxb->stat == 1) {
        if (ADXPD_GetStat(adxb->xpd) == 0) {
            adxb->getwrfunc(adxb->getwrobj, &buf->wpos, &buf->nroom, &buf->lp_nsmpl);
            n = buf->pcmbsize - buf->wpos;
            if (buf->nroom < n) {
                n = buf->nroom;
            }
            if (buf->niblk < n) {
                n = buf->niblk;
            }
            dst = buf->pcmbuf + buf->wpos;
            if (adxb->nch == 2) {
                dst2 = buf->pcmbuf + (buf->pcmbdist + buf->wpos);
                for (i = 0; i < n; i++) {
                    sample = src[i * 2];
                    dst[i] = (sample >> 8) | (sample << 8);
                    sample = src[i * 2 + 1];
                    dst2[i] = (sample >> 8) | (sample << 8);
                }
            } else {
                for (i = 0; i < n; i++) {
                    sample = src[i];
                    dst[i] = (sample >> 8) | (sample << 8);
                }
            }
            adxb->stat = 2;
            adxb->ndecsmpl = n;
            adxb->ndeclen = n * adxb->nch * 2;
        }
    }
    if (adxb->stat == 2) {
        adxb->addwrfunc(adxb->addwrobj, adxb->ndeclen, adxb->ndecsmpl);
        adxb->stat = 3;
    }
}

void ADXB_ExecOneAiff8(AdxbObj *adxb)
{
    AdxDecPara *buf;
    unsigned char *src;
    short *dst;
    short *dst2;
    int n;
    int i;

    buf = &adxb->dp;
    src = (unsigned char *)buf->ibuf;
    if (adxb->stat == 1) {
        if (ADXPD_GetStat(adxb->xpd) == 0) {
            adxb->getwrfunc(adxb->getwrobj, &buf->wpos, &buf->nroom, &buf->lp_nsmpl);
            n = buf->pcmbsize - buf->wpos;
            if (buf->nroom < n) {
                n = buf->nroom;
            }
            if (buf->niblk < n) {
                n = buf->niblk;
            }
            dst = buf->pcmbuf + buf->wpos;
            if (adxb->nch == 2) {
                dst2 = buf->pcmbuf + (buf->pcmbdist + buf->wpos);
                for (i = 0; i < n; i++) {
                    dst[i] = src[i * 2] << 8;
                    dst2[i] = src[i * 2 + 1] << 8;
                }
            } else {
                for (i = 0; i < n; i++) {
                    dst[i] = src[i] << 8;
                }
            }
            adxb->stat = 2;
            adxb->ndecsmpl = n;
            adxb->ndeclen = n * adxb->nch;
        }
    }
    if (adxb->stat == 2) {
        adxb->addwrfunc(adxb->addwrobj, adxb->ndeclen, adxb->ndecsmpl);
        adxb->stat = 3;
    }
}

void ADXB_ExecOneAiff(AdxbObj *adxb)
{
    if (adxb->cdctype == ADXB_AIFF_PCM_8) {
        ADXB_ExecOneAiff8(adxb);
        return;
    }
    ADXB_ExecOneAiff16(adxb);
}
