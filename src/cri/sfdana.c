#include "dw4/cri/sfdhn.h"
#include "dw4/cri/mps.h"
#include "dw4/cri/mcp.h"
#include <string.h>
#include "dw4/cri/mpv.h"
#include "dw4/cri/sfd.h"

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
extern int sfana_frame_rates[];
extern int sfana_mpa_nch[4];
extern int sfana_mpa_sfreqs[4];
extern int sfana_mpa_bitrates[4][16];
extern int sfana_mpa_frame_samples[4];
extern SfdMpaHdr sfana_mpa_hdr;
extern unsigned char sfana_adx_buf[2048];
extern SfdHdrInf sfana_hdr;


int sfcre_AnalyCreInf(unsigned char *buf, int size, SfdAnaInf *inf);
void sfcre_SetDflCreInf(SfdAnaInf *inf);
int sfana_ChkReserved(unsigned char *buf, int size, SfdAnaInf *inf);
int sfcre_AnalyMps(unsigned char *buf, int size, SfdAnaInf *inf);
int sfcre_AnalyPackSiz(unsigned char *buf, int size, int *muxRate);
void sfcre_AnalyMuxRate(unsigned char *pack, int size, int *muxRate);
void sfcre_AnalySfh(unsigned char *buf, int size, SfdAnaInf *inf);
void sfcre_ProcessHdr(unsigned char *p, int size, SfdHdrInf *hdr);
void sfcre_AnalyAudio(unsigned char *buf, int size, SfdAnaInf *inf);
unsigned char *sfcre_SearchMpsDelim(unsigned char *p, int size, int kind);
unsigned char *sfcre_GetPketData(unsigned char *pes, int size);
int sfcre_AnalyAdx(unsigned char *buf, int size, SfdAnaInf *inf);
int sfcre_AnalyAdxAlign4(unsigned char *buf, int size, SfdAnaInf *inf);
int sfana_ChkMpa(unsigned char *buf, int size, SfdAnaInf *inf);
unsigned char *sfcre_SerachMpaAau(SfdMpaHdr *hdr, unsigned char *p, int size);
void sfcre_ReadAauHdr(SfdMpaHdr *hdr, unsigned char *p);
int sfcre_AnalyMpv(unsigned char *buf, int size, SfdAnaInf *inf);

/* matching construct: manual — declared int with no return statement (implicit-int style), which keeps the final call a jal */
void SFD_AnalyCreInf(unsigned char *buf, int size, SfdAnaInf *inf) {
    char guard[16];

    sfd_Lock(guard);
    sfcre_AnalyCreInf(buf, size, inf);
    if (inf->video != 0 || inf->audio != 0 || inf->packSize == -1) {
        inf->found = 1;
    }
    if (inf->video != 0 || inf->audio != 0) {
        inf->isAv = 1;
    }
    sfd_Unlock(guard);
}

/* matching construct: manual — declared int with no return statement (implicit-int style), which keeps the final call a jal */
int sfcre_AnalyCreInf(unsigned char *buf, int size, SfdAnaInf *inf) {
    sfcre_SetDflCreInf(inf);
    if (sfana_ChkReserved(buf, size, inf) == 0 && sfcre_AnalyMps(buf, size, inf) == 0
        && sfcre_AnalyMpv(buf, size, inf) == 0 && sfcre_AnalyAdx(buf, size, inf) == 0) {
        sfana_ChkMpa(buf, size, inf);
    }
}

void sfcre_SetDflCreInf(SfdAnaInf *inf) {
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

int sfcre_AnalyMps(unsigned char *buf, int size, SfdAnaInf *inf) {
    int muxRate;
    int packSize;

    packSize = sfcre_AnalyPackSiz(buf, size, &muxRate);
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
    sfcre_AnalySfh(buf, size, inf);
    sfcre_AnalyAudio(buf, size, inf);
    sfcre_AnalyMpv(buf, size, inf);
    return 1;
}

/* The distance between the first three pack headers when it is the same twice, else -1. */
int sfcre_AnalyPackSiz(unsigned char *buf, int size, int *muxRate) {
    unsigned char *first;
    unsigned char *second;
    unsigned char *third;
    int offset;
    int rest;
    int gap;

    *muxRate = 0;
    first = sfcre_SearchMpsDelim(buf, size, MPS_SC_PACK);
    offset = first - buf;
    rest = size - offset;
    if (first == 0) {
        return 0;
    }
    second = sfcre_SearchMpsDelim(first + 1, rest - 1, MPS_SC_PACK);
    if (second == 0) {
        return 0;
    }
    third = sfcre_SearchMpsDelim(second + 1, size - (second - buf) - 1, MPS_SC_PACK);
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
    sfcre_AnalyMuxRate(first, rest, muxRate);
    return gap;
}

void sfcre_AnalyMuxRate(unsigned char *pack, int size, int *muxRate) {
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
void sfcre_AnalySfh(unsigned char *buf, int size, SfdAnaInf *inf) {
    int packSize = inf->packSize;
    int i;
    SfdHdrInf *hdr;

    for (i = 0; ; i++) {
        if (SFHDS_IsSfdHeader(buf, size) != 0) {
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
    sfcre_ProcessHdr(buf, size, hdr);
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

void sfcre_ProcessHdr(unsigned char *p, int size, SfdHdrInf *hdr) {
    int n = size < 2049 ? size : 2048;

    MEM_Copy(hdr->data, p, n);
    hdr->size = n;
    SFHDS_ProcessHdr(hdr);
}

void sfcre_AnalyAudio(unsigned char *buf, int size, SfdAnaInf *inf) {
    unsigned char *end = buf + size;
    int packSize = inf->packSize;
    unsigned char *pes;
    unsigned char *data;
    int n;
    int skip;

    while (size > 0) {
        pes = sfcre_SearchMpsDelim(buf, size, MPS_SC_PES);
        if (pes == 0) {
            break;
        }
        if ((unsigned char)(pes[3] + 64) < 32) {
            data = sfcre_GetPketData(pes, end - pes);
            n = packSize;
            if (end - data < n) {
                n = end - data;
            }
            if (sfcre_AnalyAdx(data, n, inf) != 0) {
                break;
            }
            if (sfana_ChkMpa(data, n, inf) != 0) {
                break;
            }
        }
        skip = pes - buf + 1;
        buf += skip;
        size -= skip;
    }
}

unsigned char *sfcre_SearchMpsDelim(unsigned char *p, int size, int kind) {
    while (size >= 4) {
        if (MPS_GetStartCodeKind(p) == kind) {
            return p;
        }
        size--;
        p++;
    }
    return 0;
}

unsigned char *sfcre_GetPketData(unsigned char *pes, int size) {
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

int sfcre_AnalyAdx(unsigned char *buf, int size, SfdAnaInf *inf) {
    if (sfcre_AnalyAdxAlign4(buf, size, inf) != 0) {
        return 1;
    }
    if (sfcre_AnalyAdxAlign4(buf + 2, size - 2, inf) != 0) {
        return 1;
    }
    if (sfcre_AnalyAdxAlign4(buf + 1, size - 1, inf) != 0) {
        return 1;
    }
    return sfcre_AnalyAdxAlign4(buf + 3, size - 3, inf) != 0;
}

int sfcre_AnalyAdxAlign4(unsigned char *buf, int size, SfdAnaInf *inf) {
    unsigned char *p;
    int hdrSize;

    if (size > 2048) {
        size = 2048;
    }
    memcpy(sfana_adx_buf, buf, size);
    p = sfana_adx_buf;
    for (; size > 0; size -= 4, p += 4) {
        if (SFADXT_IsHeader(p, size, &hdrSize) != 0) {
            inf->audio = sfadx_handler;
            inf->nch = p[7];
            inf->sfreq = (p[8] << 24) | (p[9] << 16) | (p[10] << 8) | p[11];
            return 1;
        }
    }
    return 0;
}

int SFCRE_AnalyMpaBitrate(unsigned char *p, int size) {
    SfdMpaHdr hdr;
    int kbps;

    if (sfcre_SerachMpaAau(&hdr, p, size) == 0) {
        return -1;
    }
    kbps = sfana_mpa_bitrates[hdr.layer][hdr.bitrate];
    if (kbps == -1) {
        return -1;
    }
    return kbps * 1000;
}

int SFCRE_AnalyAauSiz(unsigned char *p, int size) {
    SfdMpaHdr hdr;
    int kbps;

    if (sfcre_SerachMpaAau(&hdr, p, size) == 0) {
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

    if (sfcre_SerachMpaAau(&hdr, buf, size) == 0) {
        return 0;
    }
    inf->audio = 0;
    inf->nch = sfana_mpa_nch[hdr.mode];
    inf->sfreq = sfana_mpa_sfreqs[hdr.sfreq];
    sfana_mpa_hdr = hdr;
    return 1;
}

unsigned char *sfcre_SerachMpaAau(SfdMpaHdr *hdr, unsigned char *p, int size) {
    for (; size >= 4; size--, p++) {
        if (p[0] == 0xFF && (p[1] & 0xF8) == 0xF8) {
            sfcre_ReadAauHdr(hdr, p);
            if (hdr->layer != 0 && hdr->bitrate != 15 && hdr->sfreq != 3) {
                return p;
            }
        }
    }
    return 0;
}

void sfcre_ReadAauHdr(SfdMpaHdr *hdr, unsigned char *p) {
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

/* The first sequence header with a valid frame rate gives the picture size, bit rate and VBV size. */
int sfcre_AnalyMpv(unsigned char *buf, int size, SfdAnaInf *inf) {
    unsigned char *seq;
    unsigned char b4, b5, b6, b7, b8, b9, b10, b11;
    int used;

    while (size > 0) {
        seq = MPV_SearchDelim(buf, size, 64);
        if (seq == 0) {
            return 0;
        }
        used = seq - buf;
        used++;
        size -= used;
        buf += used;
        b4 = seq[4];
        b5 = seq[5];
        b6 = seq[6];
        b7 = seq[7];
        b8 = seq[8];
        b9 = seq[9];
        b10 = seq[10];
        b11 = seq[11];
        if ((b7 >> 4) == 0) {
            continue;
        }
        b7 &= 0xF;
        if (b7 < 1 || b7 > 8) {
            continue;
        }
        if ((b10 >> 5) & 1) {
            inf->width = (b4 << 4) | (b5 >> 4);
            inf->height = ((b5 & 0xF) << 8) | b6;
            if (inf->bps == 0) {
                inf->bps = ((b8 << 10) | (b9 << 2) | (b10 >> 6)) * 50;
            }
            inf->frameRate = sfana_frame_rates[b7];
            inf->video = sfmpv_handler;
            inf->vbvSize = (((b10 & 0x1F) << 5) | (b11 >> 3)) << 11;
            break;
        }
    }
    return 1;
}
