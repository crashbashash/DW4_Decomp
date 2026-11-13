/* CRI ADXB AU reader: plays PCM from a Sun/NeXT audio (".snd") file through an ADXB decoder handle: 16-bit,
 * 8-bit scaled to 16 bits, or 8-bit u-law expanded through a table. */
#include "dw4/cri/adxb.h"

/* AdxbObj.pcmfmt for an AU stream */
enum AdxbAuFmt {
    ADXB_AU_PCM_16 = 0,
    ADXB_AU_PCM_8 = 1,
    ADXB_AU_ULAW = 2
};

/* AU header encodings */
enum AuEncoding {
    AU_ENC_ULAW_8 = 1,
    AU_ENC_LINEAR_8 = 2,
    AU_ENC_LINEAR_16 = 3
};

#define GET32(p) ((p)[0] | ((p)[1] << 8) | ((p)[2] << 16) | ((p)[3] << 24))
#define SWAP32(x) ((((x) >> 24) & 0xFF) | (((x) >> 8) & 0xFF00) | (((x) << 8) & 0xFF0000) | ((x) << 24))

int memcmp(const void *a, const void *b, unsigned int size);

extern char _snd[];
extern char _sd[];
/* u-law byte -> 16-bit sample */
extern short adxb_ulaw_tbl[256];

/* Reads the big-endian header words, sets the sample format and returns the start of the sample data. */
unsigned char *adxb_GetAuInfo(unsigned char *buf, int len, int *sfreq, int *nch, int *bits, int *nsmpl,
                              int *fmt)
{
    unsigned char *p;
    unsigned int magic;
    unsigned int ofst;
    unsigned int size;
    unsigned int enc;
    int word;
    int ch;

    p = buf;
    magic = GET32(p);
    p += 4;
    if (magic != 0x0064732E && magic != 0x646E732E) {
        return 0;
    }
    ofst = GET32(p);
    ofst = SWAP32(ofst);
    p += 4;
    if (len < (int)ofst) {
        return 0;
    }
    size = GET32(p);
    size = SWAP32(size);
    p += 4;
    enc = GET32(p);
    enc = SWAP32(enc);
    p += 4;
    switch (enc) {
    case AU_ENC_ULAW_8:
        *fmt = ADXB_AU_ULAW;
        *bits = 8;
        break;
    case AU_ENC_LINEAR_8:
        *fmt = ADXB_AU_PCM_8;
        *bits = 8;
        break;
    case AU_ENC_LINEAR_16:
        *fmt = ADXB_AU_PCM_16;
        *bits = 16;
        break;
    default:
        return 0;
    }
    *sfreq = GET32(p);
    p += 4;
    *sfreq = SWAP32(*sfreq);
    word = GET32(p);
    p += 4;
    ch = SWAP32(word);
    *nch = ch;
    if (*fmt == ADXB_AU_ULAW) {
        *nsmpl = (int)size / ch;
    } else if (*fmt == ADXB_AU_PCM_8) {
        *nsmpl = (int)size / ch;
    } else if (*fmt == ADXB_AU_PCM_16) {
        *nsmpl = (int)size / 2 / ch;
    } else {
        *nsmpl = 0x7FFF0000;
    }
    return buf + ofst;
}

int ADXB_CheckAu(unsigned char *hdr)
{
    if (memcmp(hdr, _snd, 4) == 0 || memcmp(hdr, _sd, 4) == 0) {
        return 1;
    }
    return 0;
}

/* Header fields in ADX_DecodeInfo's form, plus the sample format. */
int ADX_DecodeInfoAu(unsigned char *buf, int len, short *hdrlen, signed char *hdrtype, signed char *fmtbps,
                     signed char *blklen, signed char *nch, int *sfreq, int *nsmpl, int *blksmpl, int *fmt)
{
    int freq;
    int ch;
    int bits;
    int smpl;
    unsigned char *data;

    if (len < 8) {
        *hdrlen = 0;
        return -1;
    }
    data = adxb_GetAuInfo(buf, len, &freq, &ch, &bits, &smpl, fmt);
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

int ADXB_DecodeHeaderAu(AdxbObj *adxb, unsigned char *hdr, int size);
void ADXB_ExecOneAu16(AdxbObj *adxb);

void ADXB_ExecOneAu8(AdxbObj *adxb)
{
    AdxbBuf *buf;
    unsigned char *src;
    short *dst;
    short *dst2;
    int n;
    int i;

    buf = &adxb->buf;
    src = (unsigned char *)buf->ibuf;
    if (adxb->stat == 1) {
        if (ADXPD_GetStat(adxb->adxpd) == 0) {
            adxb->cb120(adxb->obj124, &buf->pos, &buf->lim, &buf->end);
            n = buf->pcmbsize - buf->pos;
            if (buf->lim < n) {
                n = buf->lim;
            }
            if (buf->len < n) {
                n = buf->len;
            }
            dst = buf->pcmbuf + buf->pos;
            if (adxb->nch == 2) {
                dst2 = buf->pcmbuf + (buf->pcmbdist + buf->pos);
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
            adxb->f144 = n;
            adxb->f148 = n * adxb->nch;
        }
    }
    if (adxb->stat == 2) {
        adxb->cb128(adxb->obj132, adxb->f148, adxb->f144);
        adxb->stat = 3;
    }
}

void ADXB_ExecOneAuUlaw(AdxbObj *adxb)
{
    AdxbBuf *buf;
    unsigned char *src;
    short *dst;
    short *dst2;
    int n;
    int i;

    buf = &adxb->buf;
    src = (unsigned char *)buf->ibuf;
    if (adxb->stat == 1) {
        if (ADXPD_GetStat(adxb->adxpd) == 0) {
            adxb->cb120(adxb->obj124, &buf->pos, &buf->lim, &buf->end);
            n = buf->pcmbsize - buf->pos;
            if (buf->lim < n) {
                n = buf->lim;
            }
            if (buf->len < n) {
                n = buf->len;
            }
            dst = buf->pcmbuf + buf->pos;
            if (adxb->nch == 2) {
                dst2 = buf->pcmbuf + (buf->pcmbdist + buf->pos);
                for (i = 0; i < n; i++) {
                    dst[i] = adxb_ulaw_tbl[src[i * 2]];
                    dst2[i] = adxb_ulaw_tbl[src[i * 2 + 1]];
                }
            } else {
                for (i = 0; i < n; i++) {
                    dst[i] = adxb_ulaw_tbl[src[i]];
                }
            }
            adxb->stat = 2;
            adxb->f144 = n;
            adxb->f148 = n * adxb->nch;
        }
    }
    if (adxb->stat == 2) {
        adxb->cb128(adxb->obj132, adxb->f148, adxb->f144);
        adxb->stat = 3;
    }
}

void ADXB_ExecOneAu(AdxbObj *adxb)
{
    if (adxb->pcmfmt == ADXB_AU_ULAW) {
        ADXB_ExecOneAuUlaw(adxb);
    } else if (adxb->pcmfmt == ADXB_AU_PCM_8) {
        ADXB_ExecOneAu8(adxb);
    } else {
        ADXB_ExecOneAu16(adxb);
    }
}
