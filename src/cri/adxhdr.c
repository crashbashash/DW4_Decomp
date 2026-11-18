#include "dw4/cri/cri_adxt.h"
#include <string.h>
#include "dw4/cri/adxerrs.h"

/* CRI's ADXLOOPPRM: one loop record of the header. */
typedef struct AdxLoopPrm {
    short no;
    short type;
    int spos;
    int sofst;
    int epos;
    int eofst;
} AdxLoopPrm;

/* CRI's ADXPLYPRM: one channel's playback record; each value is valid only when its flag is set. */
typedef struct AdxPlyPrm {
    short volflg;
    short vol;
    signed char dslvflg;
    signed char dslv;
    signed char fxchflg;
    signed char fxch;
    signed char fxlvflg;
    signed char fxlv;
    signed char panflg;
    signed char pan;
} AdxPlyPrm;

/* CRI's ADXHDR: the decoded ADX header. */
typedef struct AdxHdr {
    signed char code;
    signed char blksize;
    signed char bps;
    signed char nch;
    int sfreq;
    int total_nsmpl;
    short cof;
    short nloop;
    AdxLoopPrm loopprm[1];
    AdxPlyPrm plyprm[2];
    signed char ver;
    signed char rev;
    signed char rsv1;
    signed char rsv2;
} AdxHdr;

void ADXHDR_WriteBeShort(unsigned char *bytes, short value) {
    bytes[1] = value;
    bytes[0] = (unsigned short)value >> 8;
}

void ADXHDR_WriteLeShort(unsigned char *bytes, short value) {
    bytes[0] = value;
    bytes[1] = (unsigned short)value >> 8;
}

void ADXHDR_WriteBeLong(unsigned char *bytes, unsigned int value) {
    bytes[0] = value >> 24;
    bytes[1] = value >> 16;
    bytes[2] = value >> 8;
    bytes[3] = value;
}

void ADXHDR_WriteLeLong(unsigned char *bytes, unsigned int value) {
    bytes[0] = value;
    bytes[1] = value >> 8;
    bytes[2] = value >> 16;
    bytes[3] = value >> 24;
}

void adxhdr_get_base_info(unsigned char *src, AdxHdr *h)
{
    h->code = *src++;
    h->blksize = *src++;
    h->bps = *src++;
    h->nch = *src++;
    h->sfreq = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    h->total_nsmpl = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    h->cof = (src[0] << 8) | src[1];
    src += 2;
    h->ver = src[0];
    h->rev = src[1];
}

void adxhdr_get_ext_info(unsigned char *src, AdxHdr *h) {
    unsigned char *field = src + 2;
    h->nloop = field[1] | (field[0] << 8);
}

void adxhdr_get_loop_prm(unsigned char *src, AdxLoopPrm *dst)
{
    dst->no = (src[0] << 8) | src[1];
    src += 2;
    dst->type = (src[0] << 8) | src[1];
    src += 2;
    dst->spos = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    dst->sofst = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    dst->epos = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    dst->eofst = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
}

void adxhdr_get_ply_prm(unsigned char *src, AdxPlyPrm *dst)
{
    dst->volflg = (src[0] << 8) | src[1];
    src += 2;
    if (dst->volflg > 0) {
        dst->vol = (src[0] << 8) | src[1];
    }
    src += 2;
    dst->dslvflg = *src++;
    if (dst->dslvflg > 0) {
        dst->dslv = *src;
    }
    src++;
    dst->fxchflg = *src++;
    if (dst->fxchflg > 0) {
        dst->fxch = *src;
    }
    src++;
    dst->fxlvflg = *src++;
    if (dst->fxlvflg > 0) {
        dst->fxlv = *src;
    }
    src++;
    dst->panflg = *src++;
    if (dst->panflg > 0) {
        dst->pan = *src;
    }
}

int ADX_DecodeHeader(void *data, int size, int *hdrSize, AdxHdr *hdr)
{
    unsigned char *buf = data;
    int sig;
    int len;
    int i;
    if (hdrSize != 0) {
        *hdrSize = 0;
    }
    if (size < 4) {
        return -1;
    }
    sig = buf[1] | (buf[0] << 8);
    buf += 2;
    if (sig != 0x8000) {
        return -4;
    }
    len = (buf[0] << 8) | buf[1];
    buf += 2;
    if (hdrSize != 0) {
        *hdrSize = len;
    }
    if (hdr == 0) {
        return 0;
    }
    if (size < len + 4) {
        return -2;
    }
    len -= 6;
    if (len < 16) {
        return -2;
    }
    adxhdr_get_base_info(buf, hdr);
    buf += 16;
    len -= 16;
    if (hdr->ver == 4) {
        buf += 12;
        len -= 12;
    }
    if (len < 4) {
        return 0;
    }
    adxhdr_get_ext_info(buf, hdr);
    buf += 4;
    if (len < hdr->nloop * 20) {
        return 0;
    }
    for (i = 0; i < hdr->nloop; i++) {
        adxhdr_get_loop_prm(buf, &hdr->loopprm[i]);
    }
    len -= hdr->nloop * 20;
    for (i = 0; i < hdr->nch; i++) {
        if (len < 12) {
            return 0;
        }
        len -= 12;
        adxhdr_get_ply_prm(buf, &hdr->plyprm[i]);
        buf += 12;
    }
    return 0;
}

void adxhdr_set_base_info(unsigned char *dst, AdxHdr *h)
{
    unsigned char *p;
    int i;
    p = (unsigned char *)"(c)CRI";
    *dst++ = h->code;
    *dst++ = h->blksize;
    *dst++ = h->bps;
    *dst++ = h->nch;
    ADXHDR_WriteBeLong(dst, h->sfreq);
    dst += 4;
    ADXHDR_WriteBeLong(dst, h->total_nsmpl);
    dst += 4;
    ADXHDR_WriteBeShort(dst, h->cof);
    dst += 2;
    *dst++ = h->ver;
    *dst++ = h->rev;
    for (i = 9; i >= 0; i--) {
        *dst++ = 0;
    }
    for (i = 6; i >= 0; i--) {
        *dst++ = *p++;
    }
}

int ADX_EncodeHeader(unsigned char *buffer, int size, int *written, AdxHdr *h) {
    if (written != 0) {
        *written = 0;
    }
    if (size < 36) {
        return -1;
    }
    buffer[1] = 0;
    buffer[0] = 0x80;
    ADXHDR_WriteBeShort(buffer + 2, 32);
    adxhdr_set_base_info(buffer + 4, h);
    *written = 36;
    return 0;
}

void ADXT_GetHdrInfo(void *buf, int size, AdxtHdrInfo *out)
{
    AdxtHdrInfo info;
    AdxHdr hdr;
    int work[4];
    int ret;
    if (buf == 0 || out == 0) {
        ADXERR_CallErrFunc1("E02041201: NULL pointer is specified.(ADXT_GetHdrInfo)");
        return;
    }
    memset(&info, 0, sizeof(info));
    memset(&hdr, 0, sizeof(hdr));
    ret = ADX_DecodeHeader(buf, size, work, &hdr);
    if (ret == -4) {
        ADXERR_CallErrFunc1("E02041201: Can not get header information.(ADXT_GetHdrInfo)");
        return;
    }
    if (ret < 0) {
        ADXERR_CallErrFunc1("E02041201: Buffer size is too short.(ADXT_GetHdrInfo)");
        return;
    }
    if (hdr.ver == 6) {
        info.fmt = 2;
    } else {
        info.fmt = 1;
    }
    info.sfreq = hdr.sfreq;
    info.nch = hdr.nch;
    info.bps = hdr.bps;
    info.nsmpl = hdr.total_nsmpl;
    info.lptype = hdr.nloop;
    info.lpstart = hdr.loopprm[0].spos;
    info.lpend = hdr.loopprm[0].epos;
    *out = info;
}
