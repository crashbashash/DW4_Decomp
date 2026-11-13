#include "dw4/cri/sfdhn.h"
#include "dw4/cri/mps.h"

/* What the start of a stream says it is: which handlers would play it and the movie's parameters. */
typedef struct SfdAnaInf {
    char found;          /* 0 */
    char isAv;           /* 1 */
    char pad2[2];
    void *system;        /* 4: the MPS handler when the data is a system stream */
    void *video;         /* 8: the video handler */
    void *audio;         /* 12: the audio handler */
    int packSize;        /* 16; -1 when the packs are not evenly spaced */
    int width;           /* 20 */
    int height;          /* 24 */
    int bps;             /* 28 */
    int frameRate;       /* 32 */
    int vbvSize;         /* 36 */
    unsigned char nch;   /* 40 */
    char pad41[3];
    int sfreq;           /* 44 */
    char pad48[16];
} SfdAnaInf;

/* The fields of an MPEG audio frame header. */
typedef struct SfdMpaHdr {
    unsigned char layer;
    unsigned char protection;
    unsigned char bitrate;
    unsigned char sfreq;
    unsigned char padding;
    unsigned char priv;
    unsigned char mode;
    unsigned char modeExt;
    unsigned char copyright;
    unsigned char original;
    unsigned char emphasis;
} SfdMpaHdr;

extern char sfadx_handler[];
extern char sfmps_handler[];
extern char sfmpv_handler[];
extern int sfana_mpa_nch[4];
extern int sfana_mpa_sfreqs[4];
extern int sfana_mpa_bitrates[4][16];
extern int sfana_mpa_frame_samples[4];
extern SfdMpaHdr sfana_mpa_hdr;
extern unsigned char sfana_adx_buf[2048];
extern SfdHdrInf sfana_hdr;

void *memset(void *dst, int value, unsigned int size);
void *memcpy(void *dst, const void *src, unsigned int size);
void sfd_Lock(void *guard);
void sfd_Unlock(void *guard);
int sfadx_IsHdr(unsigned char *p, int size, int *hdrSize);
int sfhdr_IsHdr(unsigned char *p, int size);
void sfhdr_Analy(SfdHdrInf *hdr);

int sfana_Analy(unsigned char *buf, int size, SfdAnaInf *inf);
void sfana_ClearInf(SfdAnaInf *inf);
int sfana_ChkReserved(unsigned char *buf, int size, SfdAnaInf *inf);
int sfana_ChkMps(unsigned char *buf, int size, SfdAnaInf *inf);
int sfana_GetPackSize(unsigned char *buf, int size, int *muxRate);
void sfana_GetMuxRate(unsigned char *pack, int size, int *muxRate);
void sfana_ReadHdr(unsigned char *buf, int size, SfdAnaInf *inf);
void sfana_LoadHdr(unsigned char *p, int size, SfdHdrInf *hdr);
void sfana_ChkMpsAudio(unsigned char *buf, int size, SfdAnaInf *inf);
unsigned char *sfana_FindCode(unsigned char *p, int size, int kind);
unsigned char *sfana_SkipPesHdr(unsigned char *pes, int size);
int sfana_ChkAdx(unsigned char *buf, int size, SfdAnaInf *inf);
int sfana_ChkAdxAt(unsigned char *buf, int size, SfdAnaInf *inf);
int sfana_ChkMpa(unsigned char *buf, int size, SfdAnaInf *inf);
unsigned char *sfana_FindMpaHdr(SfdMpaHdr *hdr, unsigned char *p, int size);
void sfana_UnpackMpaHdr(SfdMpaHdr *hdr, unsigned char *p);
int sfana_ChkM2v(unsigned char *buf, int size, SfdAnaInf *inf);

/* matching construct: manual — declared int with no return statement (implicit-int style), which keeps the final call a jal */
int SFD_GetHdrInf(unsigned char *buf, int size, SfdAnaInf *inf) {
    char guard[16];

    sfd_Lock(guard);
    sfana_Analy(buf, size, inf);
    if (inf->video != 0 || inf->audio != 0 || inf->packSize == -1) {
        inf->found = 1;
    }
    if (inf->video != 0 || inf->audio != 0) {
        inf->isAv = 1;
    }
    sfd_Unlock(guard);
}

/* matching construct: manual — declared int with no return statement (implicit-int style), which keeps the final call a jal */
int sfana_Analy(unsigned char *buf, int size, SfdAnaInf *inf) {
    sfana_ClearInf(inf);
    if (sfana_ChkReserved(buf, size, inf) == 0 && sfana_ChkMps(buf, size, inf) == 0
        && sfana_ChkM2v(buf, size, inf) == 0 && sfana_ChkAdx(buf, size, inf) == 0) {
        sfana_ChkMpa(buf, size, inf);
    }
}

void sfana_ClearInf(SfdAnaInf *inf) {
    memset(inf, 0, sizeof(SfdAnaInf));
    inf->found = 0;
    inf->isAv = 0;
    inf->system = 0;
    inf->video = 0;
    inf->audio = 0;
    inf->packSize = 0;
    inf->width = 0;
    inf->height = 0;
    inf->bps = 0;
    inf->frameRate = 0;
    inf->vbvSize = 0;
    inf->nch = 0;
    inf->sfreq = 0;
}

int sfana_ChkReserved(unsigned char *buf, int size, SfdAnaInf *inf) {
    return 0;
}

int sfana_ChkMps(unsigned char *buf, int size, SfdAnaInf *inf) {
    int muxRate;
    int packSize;

    packSize = sfana_GetPackSize(buf, size, &muxRate);
    if (packSize == 0) {
        return 0;
    }
    inf->packSize = packSize;
    if (packSize == -1) {
        return 1;
    }
    if (muxRate > 0) {
        inf->bps = muxRate * 50;
    }
    inf->system = sfmps_handler;
    sfana_ReadHdr(buf, size, inf);
    sfana_ChkMpsAudio(buf, size, inf);
    sfana_ChkM2v(buf, size, inf);
    return 1;
}

/* The distance between the first three pack headers when it is the same twice, else -1. */
int sfana_GetPackSize(unsigned char *buf, int size, int *muxRate) {
    unsigned char *first;
    unsigned char *second;
    unsigned char *third;
    int offset;
    int rest;
    int gap;

    *muxRate = 0;
    first = sfana_FindCode(buf, size, MPS_SC_PACK);
    offset = first - buf;
    rest = size - offset;
    if (first == 0) {
        return 0;
    }
    second = sfana_FindCode(first + 1, rest - 1, MPS_SC_PACK);
    if (second == 0) {
        return 0;
    }
    third = sfana_FindCode(second + 1, size - (second - buf) - 1, MPS_SC_PACK);
    if (third == 0) {
        return 0;
    }
    gap = second - first;
    if (gap != third - second) {
        return -1;
    }
    if (offset % gap != 0) {
        return -1;
    }
    sfana_GetMuxRate(first, rest, muxRate);
    return gap;
}

void sfana_GetMuxRate(unsigned char *pack, int size, int *muxRate) {
    MpsPackHd hd;
    int consumed;
    int flags;
    MpsHn *mps;

    mps = MPS_Create();
    if (mps != 0) {
        MPS_DecodeChunk(mps, pack, size, &consumed, &flags);
        if (flags & MPS_SC_PACK) {
            MPS_GetPackHd(mps, &hd);
            MPS_Destroy(mps);
            *muxRate = hd.muxRate;
        }
    }
}

/* Reads the CRI header from one of the first four packs. */
void sfana_ReadHdr(unsigned char *buf, int size, SfdAnaInf *inf) {
    int packSize = inf->packSize;
    int i;
    SfdHdrInf *hdr;

    for (i = 0; ; i++) {
        if (sfhdr_IsHdr(buf, size) != 0) {
            break;
        }
        size -= packSize;
        buf += packSize;
        if (i >= 3 || size <= 0) {
            return;
        }
    }
    hdr = &sfana_hdr;
    hdr->valid = 0;
    sfana_LoadHdr(buf, size, hdr);
    if (hdr->valid == 0) {
        return;
    }
    if (hdr->muxRate > 0) {
        inf->bps = hdr->muxRate;
    }
    if (hdr->video.width > 0) {
        inf->width = hdr->video.width;
    }
    if (hdr->video.height > 0) {
        inf->height = hdr->video.height;
    }
    if (hdr->video.frameRate > 0) {
        inf->frameRate = hdr->video.frameRate;
        inf->video = sfmpv_handler;
    }
}

void sfana_LoadHdr(unsigned char *p, int size, SfdHdrInf *hdr) {
    int n = size < 2049 ? size : 2048;

    UTY_MemCpy(hdr->data, p, n);
    hdr->size = n;
    sfhdr_Analy(hdr);
}

unsigned char *sfana_FindCode(unsigned char *p, int size, int kind) {
    while (size >= 4) {
        if (MPS_GetStartCodeKind(p) == kind) {
            return p;
        }
        size--;
        p++;
    }
    return 0;
}

unsigned char *sfana_SkipPesHdr(unsigned char *pes, int size) {
    MpsHn *mps;
    int consumed;
    int flags;

    mps = MPS_Create();
    if (mps == 0) {
        return pes + (size < 7 ? size : 6);
    }
    MPS_DecodeChunk(mps, pes, size, &consumed, &flags);
    MPS_Destroy(mps);
    return pes + consumed;
}

int sfana_ChkAdx(unsigned char *buf, int size, SfdAnaInf *inf) {
    if (sfana_ChkAdxAt(buf, size, inf) != 0) {
        return 1;
    }
    if (sfana_ChkAdxAt(buf + 2, size - 2, inf) != 0) {
        return 1;
    }
    if (sfana_ChkAdxAt(buf + 1, size - 1, inf) != 0) {
        return 1;
    }
    return sfana_ChkAdxAt(buf + 3, size - 3, inf) != 0;
}

int sfana_ChkAdxAt(unsigned char *buf, int size, SfdAnaInf *inf) {
    unsigned char *p;
    int hdrSize;

    if (size > 2048) {
        size = 2048;
    }
    memcpy(sfana_adx_buf, buf, size);
    p = sfana_adx_buf;
    for (; size > 0; size -= 4, p += 4) {
        if (sfadx_IsHdr(p, size, &hdrSize) != 0) {
            inf->audio = sfadx_handler;
            inf->nch = p[7];
            inf->sfreq = (p[8] << 24) | (p[9] << 16) | (p[10] << 8) | p[11];
            return 1;
        }
    }
    return 0;
}

int sfana_GetMpaBitRate(unsigned char *p, int size) {
    SfdMpaHdr hdr;
    int kbps;

    if (sfana_FindMpaHdr(&hdr, p, size) == 0) {
        return -1;
    }
    kbps = sfana_mpa_bitrates[hdr.layer][hdr.bitrate];
    if (kbps == -1) {
        return -1;
    }
    return kbps * 1000;
}

int sfana_GetMpaFrmLen(unsigned char *p, int size) {
    SfdMpaHdr hdr;
    int kbps;

    if (sfana_FindMpaHdr(&hdr, p, size) == 0) {
        return -1;
    }
    kbps = sfana_mpa_bitrates[hdr.layer][hdr.bitrate];
    if (kbps == -1) {
        return -1;
    }
    return sfana_mpa_frame_samples[hdr.layer] * kbps * 1000 / (sfana_mpa_sfreqs[hdr.sfreq] * 8);
}

/* MPEG audio has no handler in this build: a match only records the header. */
int sfana_ChkMpa(unsigned char *buf, int size, SfdAnaInf *inf) {
    SfdMpaHdr hdr;

    if (sfana_FindMpaHdr(&hdr, buf, size) == 0) {
        return 0;
    }
    inf->audio = 0;
    inf->nch = sfana_mpa_nch[hdr.mode];
    inf->sfreq = sfana_mpa_sfreqs[hdr.sfreq];
    sfana_mpa_hdr = hdr;
    return 1;
}

unsigned char *sfana_FindMpaHdr(SfdMpaHdr *hdr, unsigned char *p, int size) {
    for (; size >= 4; size--, p++) {
        if (p[0] == 0xFF && (p[1] & 0xF8) == 0xF8) {
            sfana_UnpackMpaHdr(hdr, p);
            if (hdr->layer != 0 && hdr->bitrate != 15 && hdr->sfreq != 3) {
                return p;
            }
        }
    }
    return 0;
}

void sfana_UnpackMpaHdr(SfdMpaHdr *hdr, unsigned char *p) {
    unsigned char b1 = p[1];
    unsigned char b2 = p[2];
    unsigned char b3 = p[3];

    hdr->layer = (b1 >> 1) & 3;
    hdr->protection = b1 & 1;
    hdr->bitrate = b2 >> 4;
    hdr->sfreq = (b2 >> 2) & 3;
    hdr->padding = (b2 >> 1) & 1;
    hdr->priv = b2 & 1;
    hdr->mode = b3 >> 6;
    hdr->modeExt = (b3 >> 4) & 3;
    hdr->copyright = (b3 >> 3) & 1;
    hdr->original = (b3 >> 2) & 1;
    hdr->emphasis = b3 & 3;
}
