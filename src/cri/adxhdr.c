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

typedef struct AdxtHdrInfo {
    int fmt;
    int sfreq;
    int nch;
    int bps;
    int nsmpl;
    int lpcnt;
    int lpStart;
    int lpEnd;
} AdxtHdrInfo;

extern unsigned char DAT_004edfc8[];
extern char DAT_004edfd0[];
extern char DAT_004ee008[];
extern char DAT_004ee048[];

void FUN_002607e8(const char *message);
void *memset(void *dst, int value, unsigned int size);

void FUN_00262a30(unsigned char *bytes, short value) {
    bytes[1] = value;
    bytes[0] = (unsigned short)value >> 8;
}

void FUN_00262a48(unsigned char *bytes, short value) {
    bytes[0] = value;
    bytes[1] = (unsigned short)value >> 8;
}

void FUN_00262a60(unsigned char *bytes, unsigned int value) {
    bytes[0] = value >> 24;
    bytes[1] = value >> 16;
    bytes[2] = value >> 8;
    bytes[3] = value;
}

void FUN_00262a80(unsigned char *bytes, unsigned int value) {
    bytes[0] = value;
    bytes[1] = value >> 8;
    bytes[2] = value >> 16;
    bytes[3] = value >> 24;
}

void FUN_00262aa0(unsigned char *src, AdxHeader *h)
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

void FUN_00262b60(unsigned char *src, AdxHeader *h) {
    unsigned char *field = src + 2;
    h->nloop = field[1] | (field[0] << 8);
}

void FUN_00262b80(unsigned char *src, AdxLoopInfo *dst)
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

void FUN_00262c70(unsigned char *src, AdxChannelInfo *dst)
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
    FUN_00262aa0(buf, hdr);
    buf += 16;
    len -= 16;
    if (hdr->version == 4) {
        buf += 12;
        len -= 12;
    }
    if (len < 4) {
        return 0;
    }
    FUN_00262b60(buf, hdr);
    buf += 4;
    if (len < hdr->nloop * 20) {
        return 0;
    }
    for (i = 0; i < hdr->nloop; i++) {
        FUN_00262b80(buf, &hdr->loop[i]);
    }
    len -= hdr->nloop * 20;
    for (i = 0; i < hdr->channels; i++) {
        if (len < 12) {
            return 0;
        }
        len -= 12;
        FUN_00262c70(buf, &hdr->channel[i]);
        buf += 12;
    }
    return 0;
}

void FUN_00262ee8(unsigned char *dst, AdxHeader *h)
{
    unsigned char *p;
    int i;
    p = DAT_004edfc8;
    *dst++ = h->encoding;
    *dst++ = h->blockSize;
    *dst++ = h->bitsPerSample;
    *dst++ = h->channels;
    FUN_00262a60(dst, h->sfreq);
    dst += 4;
    FUN_00262a60(dst, h->nsmpl);
    dst += 4;
    FUN_00262a30(dst, h->cutoff);
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

int FUN_00262fe0(unsigned char *buffer, int size, int *written, AdxHeader *h) {
    if (written != 0) {
        *written = 0;
    }
    if (size < 36) {
        return -1;
    }
    buffer[1] = 0;
    buffer[0] = 0x80;
    FUN_00262a30(buffer + 2, 32);
    FUN_00262ee8(buffer + 4, h);
    *written = 36;
    return 0;
}

void FUN_00263060(void *buf, int size, AdxtHdrInfo *out)
{
    AdxtHdrInfo info;
    AdxHeader hdr;
    int work[4];
    int ret;
    if (buf == 0 || out == 0) {
        FUN_002607e8(DAT_004edfd0);
        return;
    }
    memset(&info, 0, sizeof(info));
    memset(&hdr, 0, sizeof(hdr));
    ret = FUN_00262d30(buf, size, work, &hdr);
    if (ret == -4) {
        FUN_002607e8(DAT_004ee008);
        return;
    }
    if (ret < 0) {
        FUN_002607e8(DAT_004ee048);
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
