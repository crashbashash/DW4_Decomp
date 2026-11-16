/* MPS demultiplexing: splits a program stream into pack headers, system headers and PES packets. */
#include "dw4/cri/mps.h"
#include "dw4/cri/mpsbits.h"

/* matching construct: hand search — int return type with no return value (implicit-int style); with void
   the epilogue restores are scheduled differently */
int MPS_SetPesSw(MpsHn *mps, int sw) {
    if (MPSLIB_CheckHn(mps) != 0) {
        MPSLIB_SetErr(0, 0xFF020302);
        return;
    }
    mps->pesSw = sw;
}

void MPS_SetSysHdFn(MpsHn *mps, MpsSysHdFn fn, void *obj) {
    if (MPSLIB_CheckHn(mps) == 0) {
        mps->sysHdFn = fn;
        mps->sysHdObj = obj;
    }
}

void MPS_SetAuxFn(MpsHn *mps, MpsCbFn fn, void *obj) {
    if (MPSLIB_CheckHn(mps) == 0) {
        mps->auxFn = fn;
        mps->auxObj = obj;
    }
}

void MPS_SetPesFn(MpsHn *mps, MpsCbFn fn, void *obj) {
    if (MPSLIB_CheckHn(mps) == 0) {
        mps->pesFn = fn;
        mps->pesObj = obj;
    }
}

/* Parses one chunk of a system stream through the handle's decoder. */
int MPS_DecodeChunk(MpsHn *mps, unsigned char *pos, int n, int *len, int *flags) {
    *len = 0;
    *flags = 0;
    if (MPSLIB_CheckHn(mps) != 0) {
        return MPSLIB_SetErr(0, 0xFF020301);
    }
    return mps->decode(mps, pos, n, len, flags);
}

int mpsdmx_DecodeUnit(MpsHn *mps, unsigned char *pos, int n, int *len, int *flags);

int mpsdmx_Decode(MpsHn *mps, unsigned char *pos, int n, int *len, int *flags) {
    int unit[2];
    int more;
    int found;
    int kind;
    MpsSysHd *sysHd;

    while (n >= 4) {
        more = mpsdmx_DecodeUnit(mps, pos, n, &unit[0], &unit[1]);
        found = *flags | unit[1];
        pos += unit[0];
        n -= unit[0];
        *len += unit[0];
        *flags = found;
        if (more == 0) break;
    }
    if (*flags & MPS_SC_SYSHDR) {
        sysHd = &mps->sysHd;
        kind = 0;
        if (sysHd->audioBound == 0) {
            kind = (sysHd->videoBound != 0) ? 1 : 2;
        }
        mps->sysHdKind[kind] = *sysHd;
    }
    return 0;
}

void mpsdmx_ParsePack(MpsHn *mps, unsigned char *pos, int *len);
void mpsdmx_ParseSysHd(MpsHn *mps, unsigned char *pos, int *len);
void mpsdmx_ParsePes(MpsHn *mps, unsigned char *pos, int *len, int pesSw);

/* Parses the unit at pos; returns non-zero when decoding may go on past it (a pack or system header). */
int mpsdmx_DecodeUnit(MpsHn *mps, unsigned char *pos, int n, int *len, int *flags) {
    int more;
    int kind;

    *len = 0;
    kind = MPS_GetStartCodeKind(pos);
    *flags = kind;
    more = 0;
    switch (kind) {
    case MPS_SC_PACK:
        more = 1;
        mpsdmx_ParsePack(mps, pos, len);
        break;
    case MPS_SC_SYSHDR:
        more = 1;
        mpsdmx_ParseSysHd(mps, pos, len);
        break;
    case MPS_SC_PES:
        mpsdmx_ParsePes(mps, pos, len, mps->pesSw);
        if (mps->pesFn != 0) {
            mps->pesFn(mps->pesObj, (unsigned char)mps->pes.streamId);
        }
        break;
    }
    return more;
}

/* The pack header of an MPEG-1 system stream: a 33-bit system clock reference and the mux rate. */
void mpsdmx_ParsePack(MpsHn *mps, unsigned char *pos, int *len) {
    MpsPackHd *pack = &mps->pack;
    unsigned int cur, nxt;
    int bit;
    char *rp;
    unsigned int prefix, scrHi, scrMid, scrLo, muxRate;

    BITS_INIT(pos + 4, cur, nxt, bit, rp);
    BITS_GET2(prefix, cur, nxt, bit, rp);
    BITS_SKIP(2, cur, nxt, bit, rp);
    BITS_GET(scrHi, 3, cur, nxt, bit, rp);
    BITS_SKIP(1, cur, nxt, bit, rp);
    BITS_GET(scrMid, 15, cur, nxt, bit, rp);
    BITS_SKIP(1, cur, nxt, bit, rp);
    BITS_GET(scrLo, 15, cur, nxt, bit, rp);
    BITS_SKIP(1, cur, nxt, bit, rp);
    BITS_SKIP(1, cur, nxt, bit, rp);
    BITS_GET(muxRate, 22, cur, nxt, bit, rp);
    pack->scr = ((long long)(scrHi & 7) << 30) | ((long long)(scrMid & 0x7fff) << 15) | (scrLo & 0x7fff);
    pack->isMpeg1 = prefix == 0;
    pack->muxRate = muxRate;
    *len = 12;
}

/* The system header: bounds and flags, then one P-STD buffer bound per stream; the system-header callback
 * gets them all. */
void mpsdmx_ParseSysHd(MpsHn *mps, unsigned char *pos, int *len) {
    MpsSysHd *sysHd = &mps->sysHd;
    MpsSysHdInf inf;
    unsigned int cur, nxt;
    int bit;
    char *rp;
    unsigned int streamId, bufferBoundScale, bufferSizeBound, reserved;
    unsigned char *end;
    unsigned char *next;

    BITS_INIT(pos + 4, cur, nxt, bit, rp);
    BITS_GET(sysHd->headerLength, 16, cur, nxt, bit, rp);
    BITS_SKIP(1, cur, nxt, bit, rp);
    BITS_GET(sysHd->rateBound, 22, cur, nxt, bit, rp);
    BITS_SKIP(1, cur, nxt, bit, rp);
    BITS_GET(sysHd->audioBound, 6, cur, nxt, bit, rp);
    BITS_GET1(sysHd->fixedFlag, cur, nxt, bit, rp);
    BITS_GET1(sysHd->cspsFlag, cur, nxt, bit, rp);
    BITS_GET1(sysHd->audioLockFlag, cur, nxt, bit, rp);
    BITS_GET1(sysHd->videoLockFlag, cur, nxt, bit, rp);
    BITS_SKIP(1, cur, nxt, bit, rp);
    BITS_GET(sysHd->videoBound, 5, cur, nxt, bit, rp);
    BITS_GET(reserved, 8, cur, nxt, bit, rp);
    inf.streamCount = 0;
    while ((int)cur < 0) {
        BITS_GET(streamId, 8, cur, nxt, bit, rp);
        BITS_SKIP(2, cur, nxt, bit, rp);
        BITS_GET1(bufferBoundScale, cur, nxt, bit, rp);
        BITS_GET(bufferSizeBound, 13, cur, nxt, bit, rp);
        inf.stream[inf.streamCount].streamId = streamId;
        inf.stream[inf.streamCount].bufferBoundScale = bufferBoundScale;
        inf.stream[inf.streamCount].bufferSizeBound = bufferSizeBound;
        inf.streamCount++;
    }
    end = (unsigned char *)rp + ((bit + 7) >> 3);
    next = end - 8;
    *len = next - pos;
    if (MPS_GetStartCodeKind(next) == 0 && MPS_GetStartCodeKind(end - 7) == MPS_SC_PES) {
        *len += 1;
    }
    if (mps->sysHdFn != 0) {
        inf.rateBound = sysHd->rateBound;
        inf.audioBound = sysHd->audioBound;
        inf.fixedFlag = sysHd->fixedFlag;
        inf.cspsFlag = sysHd->cspsFlag;
        inf.audioLockFlag = sysHd->audioLockFlag;
        inf.videoLockFlag = sysHd->videoLockFlag;
        inf.videoBound = sysHd->videoBound;
        inf.packetRateRestrictionFlag = reserved >> 7;
        inf.reserved = reserved & 0x7F;
        mps->sysHdFn(mps->sysHdObj, &inf);
    }
}

/* The packet header of an MPEG-1 PES packet: stream id, length, the optional P-STD buffer size and the
 * time stamps. pesSw 2 reads a 16-bit length, any other value a 32-bit one. */
void mpsdmx_ParsePes(MpsHn *mps, unsigned char *pos, int *len, int pesSw) {
    MpsPesInf *pes = &mps->pes;
    unsigned int cur, nxt;
    int bit;
    char *rp;
    unsigned int streamId, bufferBoundScale, bufferSizeBound, tsHi, tsMid, tsLo, peek;
    int streamKind, streamNo;
    int headerBase;
    unsigned char *end;

    BITS_INIT(pos + 3, cur, nxt, bit, rp);
    BITS_GET(streamId, 8, cur, nxt, bit, rp);
    pes->streamId = streamId;
    if (streamId - 0xE0 < 16) {
        streamKind = MPS_PES_VIDEO;
        streamNo = streamId - 0xE0;
    } else if (streamId - 0xC0 < 32) {
        streamKind = MPS_PES_AUDIO;
        streamNo = streamId - 0xC0;
    } else if (streamId == 0xBD) {
        streamKind = MPS_PES_PRIVATE;
        streamNo = 1;
    } else if (streamId == 0xBF) {
        streamKind = MPS_PES_PRIVATE;
        streamNo = 2;
    } else if (streamId == 0xBE) {
        streamKind = MPS_PES_PADDING;
        streamNo = 0;
    } else {
        streamKind = MPS_PES_OTHER;
        streamNo = 0;
    }
    pes->streamKind = streamKind;
    pes->streamNo = streamNo;
    if (pesSw == 2) {
        BITS_GET(pes->packetLength, 16, cur, nxt, bit, rp);
        headerBase = 6;
    } else {
        BITS_GET32(pes->packetLength, cur, nxt, bit, rp);
        headerBase = 8;
    }
    if (streamId - 0xBE < 2) {
        *len = headerBase;
        pes->dataSize = pes->packetLength;
        return;
    }
    for (;;) {
        BITS_PEEK(peek, 8, cur, nxt, bit);
        if (peek != 0xFF) {
            break;
        }
        BITS_SKIP(8, cur, nxt, bit, rp);
    }
    BITS_PEEK(peek, 2, cur, nxt, bit);
    if (peek == 1) {
        BITS_SKIP(2, cur, nxt, bit, rp);
        BITS_GET1(bufferBoundScale, cur, nxt, bit, rp);
        BITS_GET(bufferSizeBound, 13, cur, nxt, bit, rp);
        bufferSizeBound <<= 7;
        if (bufferBoundScale != 0) {
            bufferSizeBound <<= 3;
        }
        pes->stdBufferSize = bufferSizeBound;
    }
    BITS_PEEK(peek, 4, cur, nxt, bit);
    if (peek == 2) {
        BITS_SKIP(4, cur, nxt, bit, rp);
        BITS_GET(tsHi, 3, cur, nxt, bit, rp);
        BITS_SKIP(1, cur, nxt, bit, rp);
        BITS_GET(tsMid, 15, cur, nxt, bit, rp);
        BITS_SKIP(1, cur, nxt, bit, rp);
        BITS_GET(tsLo, 15, cur, nxt, bit, rp);
        BITS_SKIP(1, cur, nxt, bit, rp);
        pes->pts = ((long long)(tsHi & 7) << 30) | ((long long)(tsMid & 0x7fff) << 15) | (tsLo & 0x7fff);
        pes->dts = -1;
    } else if (peek == 3) {
        BITS_SKIP(4, cur, nxt, bit, rp);
        BITS_GET(tsHi, 3, cur, nxt, bit, rp);
        BITS_SKIP(1, cur, nxt, bit, rp);
        BITS_GET(tsMid, 15, cur, nxt, bit, rp);
        BITS_SKIP(1, cur, nxt, bit, rp);
        BITS_GET(tsLo, 15, cur, nxt, bit, rp);
        BITS_SKIP(1, cur, nxt, bit, rp);
        pes->pts = ((long long)(tsHi & 7) << 30) | ((long long)(tsMid & 0x7fff) << 15) | (tsLo & 0x7fff);
        BITS_SKIP(4, cur, nxt, bit, rp);
        BITS_GET(tsHi, 3, cur, nxt, bit, rp);
        BITS_SKIP(1, cur, nxt, bit, rp);
        BITS_GET(tsMid, 15, cur, nxt, bit, rp);
        BITS_SKIP(1, cur, nxt, bit, rp);
        BITS_GET(tsLo, 15, cur, nxt, bit, rp);
        BITS_SKIP(1, cur, nxt, bit, rp);
        pes->dts = ((long long)(tsHi & 7) << 30) | ((long long)(tsMid & 0x7fff) << 15) | (tsLo & 0x7fff);
    } else {
        BITS_SKIP(8, cur, nxt, bit, rp);
        pes->pts = -1;
        pes->dts = -1;
    }
    end = (unsigned char *)rp + ((bit + 7) >> 3) - 8;
    *len = end - pos;
    pes->dataSize = pes->packetLength + headerBase - *len;
}

int MPS_GetStartCodeKind(unsigned char *p) {
    unsigned char code;

    if (p[0] == 0 && p[1] == 0 && p[2] == 1) {
        code = p[3];
        switch (code) {
        case 0xBA: return MPS_SC_PACK;
        case 0xBB: return MPS_SC_SYSHDR;
        case 0xB9: return MPS_SC_END;
        }
        if (code >= 0xBC) return MPS_SC_PES;
    }
    return 0;
}

unsigned char *mpsdmx_SearchStartCode(unsigned char *p, int size, unsigned char code);

/* Whether the first pack header in buf is an MPEG-1 one (its SCR field starts with the bits 00). */
int MPS_IsMpeg1(unsigned char *buf, int size) {
    unsigned char *p = mpsdmx_SearchStartCode(buf, size, 0xBA);

    if (p == 0) {
        return 0;
    }
    p += 4;
    size -= p - buf;
    if (size <= 0) {
        return 0;
    }
    return (*p >> 6) == 0;
}

/* Returns the first start code 00 00 01 <code> in the size bytes at p, or 0. */
unsigned char *mpsdmx_SearchStartCode(unsigned char *p, int size, unsigned char code) {
    int i;

    for (i = 0; i + 3 < size; i++, p++) {
        if (p[0] == 0 && p[1] == 0 && p[2] == 1 && p[3] == code) {
            return p;
        }
    }
    return 0;
}

void mpsdmx_Init(void) {
}

void mpsdmx_Finish(void) {
}
