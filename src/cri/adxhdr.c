#include "dw4/cri/cri_adxt.h"
#include <string.h>
#include "dw4/cri/adxerrs.h"

typedef struct AdxLoopInfo {
    short f0;
    short f2;
    int start;
    int f8;
    int end;
    int f16;
} AdxLoopInfo;

typedef struct AdxChannelInfo {
    short f0;
    short f2;
    signed char f4;
    signed char f5;
    signed char f6;
    signed char f7;
    signed char f8;
    signed char f9;
    signed char f10;
    signed char f11;
} AdxChannelInfo;

typedef struct AdxHeader {
    signed char encoding;
    signed char blockSize;
    signed char bitsPerSample;
    signed char channels;
    int sfreq;
    int nsmpl;
    short cutoff;
    short nloop;
    AdxLoopInfo loop[1];
    AdxChannelInfo channel[2];
    signed char version;
    signed char flags;
    char pad62[2];
} AdxHeader;

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

void adxhdr_get_base_info(unsigned char *src, AdxHeader *h)
{
    h->encoding = *src++;
    h->blockSize = *src++;
    h->bitsPerSample = *src++;
    h->channels = *src++;
    h->sfreq = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    h->nsmpl = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    h->cutoff = (src[0] << 8) | src[1];
    src += 2;
    h->version = src[0];
    h->flags = src[1];
}

void adxhdr_get_ext_info(unsigned char *src, AdxHeader *h) {
    unsigned char *field = src + 2;
    h->nloop = field[1] | (field[0] << 8);
}

void adxhdr_get_loop_prm(unsigned char *src, AdxLoopInfo *dst)
{
    dst->f0 = (src[0] << 8) | src[1];
    src += 2;
    dst->f2 = (src[0] << 8) | src[1];
    src += 2;
    dst->start = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    dst->f8 = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    dst->end = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    dst->f16 = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
}

void adxhdr_get_ply_prm(unsigned char *src, AdxChannelInfo *dst)
{
    dst->f0 = (src[0] << 8) | src[1];
    src += 2;
    if (dst->f0 > 0) {
        dst->f2 = (src[0] << 8) | src[1];
    }
    src += 2;
    dst->f4 = *src++;
    if (dst->f4 > 0) {
        dst->f5 = *src;
    }
    src++;
    dst->f6 = *src++;
    if (dst->f6 > 0) {
        dst->f7 = *src;
    }
    src++;
    dst->f8 = *src++;
    if (dst->f8 > 0) {
        dst->f9 = *src;
    }
    src++;
    dst->f10 = *src++;
    if (dst->f10 > 0) {
        dst->f11 = *src;
    }
}

int FUN_00262d30(void *data, int size, int *hdrSize, AdxHeader *hdr)
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
    if (hdr->version == 4) {
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
        adxhdr_get_loop_prm(buf, &hdr->loop[i]);
    }
    len -= hdr->nloop * 20;
    for (i = 0; i < hdr->channels; i++) {
        if (len < 12) {
            return 0;
        }
        len -= 12;
        adxhdr_get_ply_prm(buf, &hdr->channel[i]);
        buf += 12;
    }
    return 0;
}

void adxhdr_set_base_info(unsigned char *dst, AdxHeader *h)
{
    unsigned char *p;
    int i;
    p = (unsigned char *)"(c)CRI";
    *dst++ = h->encoding;
    *dst++ = h->blockSize;
    *dst++ = h->bitsPerSample;
    *dst++ = h->channels;
    ADXHDR_WriteBeLong(dst, h->sfreq);
    dst += 4;
    ADXHDR_WriteBeLong(dst, h->nsmpl);
    dst += 4;
    ADXHDR_WriteBeShort(dst, h->cutoff);
    dst += 2;
    *dst++ = h->version;
    *dst++ = h->flags;
    for (i = 9; i >= 0; i--) {
        *dst++ = 0;
    }
    for (i = 6; i >= 0; i--) {
        *dst++ = *p++;
    }
}

int ADX_EncodeHeader(unsigned char *buffer, int size, int *written, AdxHeader *h) {
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
    AdxHeader hdr;
    int work[4];
    int ret;
    if (buf == 0 || out == 0) {
        ADXERR_CallErrFunc1("E02041201: NULL pointer is specified.(ADXT_GetHdrInfo)");
        return;
    }
    memset(&info, 0, sizeof(info));
    memset(&hdr, 0, sizeof(hdr));
    ret = FUN_00262d30(buf, size, work, &hdr);
    if (ret == -4) {
        ADXERR_CallErrFunc1("E02041201: Can not get header information.(ADXT_GetHdrInfo)");
        return;
    }
    if (ret < 0) {
        ADXERR_CallErrFunc1("E02041201: Buffer size is too short.(ADXT_GetHdrInfo)");
        return;
    }
    if (hdr.version == 6) {
        info.fmt = 2;
    } else {
        info.fmt = 1;
    }
    info.sfreq = hdr.sfreq;
    info.nch = hdr.channels;
    info.bps = hdr.bitsPerSample;
    info.nsmpl = hdr.nsmpl;
    info.lpcnt = hdr.nloop;
    info.lpStart = hdr.loop[0].start;
    info.lpEnd = hdr.loop[0].end;
    *out = info;
}
