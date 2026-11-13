/* CRI ADXB WAV reader: plays PCM from a RIFF WAVE file through an ADXB decoder handle. */
#include "dw4/cri/adxb.h"

enum AdxbPcmFmt {
    ADXB_PCM_16 = 0,
    ADXB_PCM_8 = 1,
    ADXB_PCM_4 = 2
};

int memcmp(const void *a, const void *b, unsigned int size);

extern char RIFF[];
extern char WAVE[];

void ADXB_ExecOneWav16(AdxbObj *obj)
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

void ADXB_ExecOneWav8(AdxbObj *obj)
{
    AdxbBuf *buf;
    unsigned char *src;
    short *dst;
    short *dst2;
    int n;
    int i;

    buf = &obj->buf;
    src = (unsigned char *)buf->ibuf;
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
                    dst[i] = (src[i * 2] - 128) << 8;
                    dst2[i] = (src[i * 2 + 1] - 128) << 8;
                }
            } else {
                for (i = 0; i < n; i++) {
                    dst[i] = (src[i] - 128) << 8;
                }
            }
            obj->stat = 2;
            obj->f144 = n;
            obj->f148 = n * obj->nch;
        }
    }
    if (obj->stat == 2) {
        obj->cb128(obj->obj132, obj->f148, obj->f144);
        obj->stat = 3;
    }
}

/* 16-bit samples assembled from little-endian byte pairs. */
void ADXB_ExecOneWav16Le(AdxbObj *obj)
{
    AdxbBuf *buf;
    unsigned char *src;
    short *dst;
    short *dst2;
    int n;
    int i;

    buf = &obj->buf;
    src = (unsigned char *)buf->ibuf;
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
                    dst[i] = src[i * 4] | (src[i * 4 + 2] << 8);
                    dst2[i] = src[i * 4 + 1] | (src[i * 4 + 3] << 8);
                }
            } else {
                for (i = 0; i < n; i++) {
                    dst[i] = src[i * 2] | (src[i * 2 + 1] << 8);
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

int ADXB_CheckWav(unsigned char *hdr)
{
    if (memcmp(hdr, RIFF, 4) == 0 && memcmp(hdr + 8, WAVE, 4) == 0) {
        return 1;
    }
    return 0;
}

void ADXB_ExecOneWav(AdxbObj *obj)
{
    if (obj->f156 == ADXB_PCM_4) {
        ADXB_ExecOneWav16Le(obj);
    } else if (obj->f156 == ADXB_PCM_8) {
        ADXB_ExecOneWav8(obj);
    } else if (obj->f156 == ADXB_PCM_16) {
        ADXB_ExecOneWav16(obj);
    }
}
