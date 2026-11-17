/* CRI ADXB SPSD reader: plays raw PCM from an SPSD header through an ADXB decoder handle. */
#include "dw4/cri/adxb.h"
#include <string.h>

typedef struct AdxbSpsdHeader {
    char pad0[7];
    unsigned char hdr_units;
    unsigned char codec;
    unsigned char chmask;
    char pad10[2];
    int data_size;
    char pad16[26];
    unsigned short sfreq;
} AdxbSpsdHeader;

int ADX_DecodeInfoSpsd(AdxbSpsdHeader *hdr, int size, short *hdrlen, signed char *type, signed char *bits,
                     signed char *blklen, signed char *nch, int *sfreq, int *nsmpl, int *blksmpl,
                     short *pcm_fmt)
{
    *hdrlen = hdr->hdr_units << 4;
    *nch = (hdr->chmask & 3) + 1;
    *sfreq = hdr->sfreq;
    switch (hdr->codec) {
    case 0:
        *bits = 16;
        *blklen = *nch * 2;
        *blksmpl = 1;
        *pcm_fmt = 0;
        *nsmpl = hdr->data_size / 2;
        break;
    case 1:
        *bits = 8;
        {
            int ch = *nch;

            *blklen = ch;
        }
        *blksmpl = 1;
        *pcm_fmt = 1;
        *nsmpl = hdr->data_size;
        break;
    case 2:
    case 3:
        *bits = 4;
        {
            int ch = *nch;

            *blklen = ch;
        }
        *blksmpl = 2;
        *pcm_fmt = 2;
        *nsmpl = hdr->data_size * 2;
        break;
    }
    *blklen = 2;
    *blksmpl = 1;
    *nsmpl = hdr->data_size / 2;
    *bits = 16;
    *type = -1;
    return 0;
}

/* matching construct: hill climb — the order of the copies after the call */
int ADXB_DecodeHeaderSpsd(AdxbObj *adxb, unsigned char *hdr, int size)
{
    short hdrlen;

    adxb->hdr_set = 1;
    /* the header is read through its layout */
    if (ADX_DecodeInfoSpsd((AdxbSpsdHeader *)hdr, size, &hdrlen, &adxb->hdrtype, &adxb->fmtbps, &adxb->blklen,
                           &adxb->nch, &adxb->sfreq, &adxb->total_nsmpl, &adxb->blksmpl, &adxb->pcmfmt) < 0) {
        return 0;
    }
    adxb->cof = 0;
    adxb->lptype = 0;
    adxb->lp_end_ofst = 0;
    adxb->lp_end_pos = 0;
    adxb->lp_start_ofst = 0;
    adxb->lp_start_pos = 0;
    adxb->nloop = 0;
    adxb->lpins_nsmpl = 0;
    adxb->buf.nch = adxb->nch;
    adxb->buf.blklen = adxb->blklen;
    adxb->buf.blksmpl = adxb->blksmpl;
    adxb->format = ADXB_FORMAT_SPSD;
    adxb->buf.pcmbuf = adxb->pcmbuf;
    adxb->buf.pcmbsize = adxb->pcmbsize;
    adxb->dec_nsmpl = 0;
    adxb->buf.pcmbdist = adxb->pcmbdist;
    adxb->wpos = 0;
    return hdrlen;
}

void ADXB_ExecOneSpsd(AdxbObj *obj)
{
    AdxbBuf *buf;
    short *src;
    short *dst;
    short *dst2;
    int n;
    int i;

    buf = &obj->buf;
    src = (short *)buf->ibuf;
    if (obj->stat == 1) {
        if (ADXPD_GetStat(obj->adxpd) == 0) {
            obj->cb120(obj->obj124, &buf->pos, &buf->lim, &buf->end);
            n = buf->pcmbsize - buf->pos;
            if (buf->lim < n) {
                n = buf->lim;
            }
            if (buf->len < n) {
                n = buf->len;
            }
            dst = buf->pcmbuf + buf->pos;
            if (obj->nch == 2) {
                dst2 = buf->pcmbuf + (buf->pcmbdist + buf->pos);
                for (i = 0; i < n; i++) {
                    dst[i] = src[i * 2];
                    dst2[i] = src[i * 2 + 1];
                }
            } else {
                for (i = 0; i < n; i++) {
                    dst[i] = src[i];
                }
            }
            obj->stat = 2;
            obj->f144 = n;
            obj->f148 = n * obj->nch * 2;
        }
    }
    if (obj->stat == 2) {
        obj->cb128(obj->obj132, obj->f148, obj->f144);
        obj->stat = 3;
    }
}

int ADXB_CheckSpsd(unsigned char *hdr)
{
    return memcmp(hdr, "SPSD", 4) == 0;
}
