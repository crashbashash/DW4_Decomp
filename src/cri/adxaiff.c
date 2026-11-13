/* CRI ADXB AIFF reader: plays big-endian PCM from an AIFF ("FORM" ... "AIFF") file through an ADXB decoder
 * handle. The samples reach the output as they are, the 8-bit ones scaled to 16 bits. */
#include "dw4/cri/adxb.h"

/* AdxbObj.pcmfmt for an AIFF stream */
enum AdxbAiffFmt {
    ADXB_AIFF_PCM_16 = 0,
    ADXB_AIFF_PCM_8 = 1
};

int memcmp(const void *a, const void *b, unsigned int size);

extern char FORM[];
extern char AIFF[];

unsigned char *adxb_GetAiffInfo(unsigned char *buf, int *sfreq, int *nch, int *bits, int *nsmpl);

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
    data = adxb_GetAiffInfo(buf, &freq, &ch, &bits, &smpl);
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

    adxb->hdr_set = 1;
    if (ADX_DecodeInfoAiff(hdr, size, &hdrlen, &adxb->hdrtype, &adxb->fmtbps, &adxb->blklen, &adxb->nch,
                           &adxb->sfreq, &adxb->total_nsmpl, &adxb->blksmpl) < 0) {
        return 0;
    }
    adxb->lp_end_ofst = 0;
    adxb->lp_end_pos = 0;
    adxb->lp_start_ofst = 0;
    adxb->lp_start_pos = 0;
    adxb->lpins_nsmpl = 0;
    adxb->cof = 0;
    adxb->lptype = 0;
    adxb->nloop = 0;
    adxb->buf.nch = adxb->nch;
    adxb->buf.blklen = adxb->blklen;
    adxb->buf.pcmbuf = adxb->pcmbuf;
    adxb->format = ADXB_FORMAT_AIFF;
    adxb->buf.blksmpl = adxb->blksmpl;
    adxb->wpos = 0;
    adxb->buf.pcmbsize = adxb->pcmbsize;
    adxb->dec_nsmpl = 0;
    adxb->buf.pcmbdist = adxb->pcmbdist;
    if (adxb->fmtbps == 8) {
        adxb->pcmfmt = ADXB_AIFF_PCM_8;
    } else {
        adxb->pcmfmt = ADXB_AIFF_PCM_16;
    }
    return hdrlen;
}

void ADXB_ExecOneAiff16(AdxbObj *adxb);

void ADXB_ExecOneAiff8(AdxbObj *adxb)
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

void ADXB_ExecOneAiff(AdxbObj *adxb)
{
    if (adxb->pcmfmt == ADXB_AIFF_PCM_8) {
        ADXB_ExecOneAiff8(adxb);
        return;
    }
    ADXB_ExecOneAiff16(adxb);
}
