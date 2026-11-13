/* MPS demultiplexing: splits a program stream into pack headers, system headers and PES packets. */
#include "dw4/cri/mps.h"

/* matching construct: hand search — int return type with no return value (implicit-int style); with void
   the epilogue restores are scheduled differently */
int MPS_SetPesSw(MpsHn *mps, int sw) {
    if (mps_CheckHn(mps) != 0) {
        mps_ReportError(0, 0xFF020302);
        return;
    }
    mps->pesSw = sw;
}

void MPS_SetSysHdFn(MpsHn *mps, MpsCbFn fn, void *obj) {
    if (mps_CheckHn(mps) == 0) {
        mps->sysHdFn = fn;
        mps->sysHdObj = obj;
    }
}

void MPS_SetAuxFn(MpsHn *mps, MpsCbFn fn, void *obj) {
    if (mps_CheckHn(mps) == 0) {
        mps->auxFn = fn;
        mps->auxObj = obj;
    }
}

void MPS_SetPesFn(MpsHn *mps, MpsCbFn fn, void *obj) {
    if (mps_CheckHn(mps) == 0) {
        mps->pesFn = fn;
        mps->pesObj = obj;
    }
}

/* Parses one chunk of a system stream through the handle's decoder. */
int MPS_DecodeChunk(MpsHn *mps, unsigned char *pos, int n, int *len, int *flags) {
    *len = 0;
    *flags = 0;
    if (mps_CheckHn(mps) != 0) {
        return mps_ReportError(0, 0xFF020301);
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
