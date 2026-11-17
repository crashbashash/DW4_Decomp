/* MPV header decoding: walks a video elementary stream through a stream joint, start code by start code,
 * and decodes the sequence, group and picture headers and the user data in front of a picture. */
#include "dw4/cri/mpv.h"
#include "dw4/cri/mpvbits.h"

int MPVLIB_CheckHn(MpvHn *mpv);
int mpv_ReportError(MpvHn *mpv, int code);
SfdSj *SJMEM_Create(void *buf, int size);
void SJ_SplitChunk(SfdSjChunk *ck, int len, SfdSjChunk *head, SfdSjChunk *rest);
int MPV_CheckDelim(const unsigned char *p);
char *MPV_SearchDelim(char *buf, int len, int mask);
int atoi(const char *s);
int strncmp(const char *a, const char *b, unsigned int n);

extern char mpv_tag_idcprec[];  /* "IDCPREC" */
extern char mpv_tag_stccode[];  /* "STCCODE" */

void MPV_SetUsrSj(MpvHn *mpv, int index, SfdSj *sj, MpvUsrDatFn fn, void *obj) {
    MpvBufEnt *ent = &mpv->bufEnt[index];

    ent->sj = sj;
    ent->fn = fn;
    ent->obj = obj;
}

void MPV_SetPicUsrBuf(MpvHn *mpv, int width, int height) {
    MpvLowSize *low = &mpv->low;

    low->width = width;
    low->height = height;
    low->flag = 0;
}

void MPV_GetPicUsr(MpvHn *mpv, int *width, int *flag) {
    MpvLowSize *low = &mpv->low;

    if (width != 0) {
        *width = low->width;
    }
    if (flag != 0) {
        *flag = low->flag;
    }
}

int mpv_StartLower(MpvHn *mpv, SfdSj *sj);
int mpvhdec_GetCodec(MpvHn *mpv, SfdSjChunk *buf);
int mpvhdec_GetCurDelim(SfdSj *sj);
int mpvhdec_RecoverSj(MpvHn *mpv, int mask, SfdSj *sj);
int mpv_DecSeqHdr(MpvHn *mpv, SfdSj *sj);
int mpvhdec_DecGscSj(MpvHn *mpv, SfdSj *sj);
int mpv_DecPicHdr(MpvHn *mpv, SfdSj *sj);
int mpvhdec_DecEscSj(MpvHn *mpv, SfdSj *sj, int type);
int mpvhdec_DecUdscSj(MpvHn *mpv, SfdSj *sj, int type);

/* Decodes the headers at the head of the stream joint, start code by start code, up to the first slice. */
int MPV_DecodePicAtrSj(MpvHn *mpv, SfdSj *sj) {
    SfdSjChunk ck;
    SfdSjChunk head;
    int type;
    int kind;
    int err;

    if (MPVLIB_CheckHn(mpv) != 0) {
        return mpv_ReportError(0, 0xFF03020C);
    }
    mpv->low.flag = 0;
    sj->vtbl->getChunk(sj, 1, 0x7FFFFFFF, &ck);
    sj->vtbl->ungetChunk(sj, 1, &ck);
    head.data = ck.data;
    head.len = ck.len;
    if (mpvhdec_GetCodec(mpv, &head) == 2) {
        return mpv_StartLower(mpv, sj);
    }
    type = 0;
    for (;;) {
        err = mpvhdec_RecoverSj(mpv, -1, sj);
        if (err != 0) {
            return mpv_ReportError(mpv, err);
        }
        kind = mpvhdec_GetCurDelim(sj);
        if (kind == 0 || (kind & 3) != 0) {
            break;
        }
        switch (kind) {
        case 64:
            type = 64;
            mpv_DecSeqHdr(mpv, sj);
            break;
        case 8:
            type = 8;
            mpvhdec_DecGscSj(mpv, sj);
            break;
        case 4:
            type = 4;
            mpv_DecPicHdr(mpv, sj);
            break;
        case 16:
            mpvhdec_DecEscSj(mpv, sj, type);
            break;
        case 32:
            mpvhdec_DecUdscSj(mpv, sj, type);
            break;
        }
    }
    return 0;
}
/* Classifies the start code at the head of the stream joint without taking any data. */
int mpvhdec_GetCurDelim(SfdSj *sj) {
    SfdSjChunk ck;

    sj->vtbl->getChunk(sj, 1, 0x7FFFFFFF, &ck);
    sj->vtbl->ungetChunk(sj, 1, &ck);
    if (ck.len < 4) {
        return 0;
    }
    return MPV_CheckDelim((unsigned char *)ck.data);
}

/* MPV_DecodePicAtrSj on a buffer, through a temporary memory stream joint; *used gets the bytes taken. */
int MPV_DecodePicAtr(MpvHn *mpv, SfdSjChunk *buf, int *used) {
    SfdSj *sj;
    int result;

    sj = SJMEM_Create(buf->data, buf->len);
    if (sj == 0) {
        return -1;
    }
    result = MPV_DecodePicAtrSj(mpv, sj);
    *used = buf->len - sj->vtbl->getNumData(sj, 1);
    sj->vtbl->destroy(sj);
    return result;
}

/* Decides once whether the stream is MPEG-1 (1) or MPEG-2 (2): MPEG-2 when the sequence header is
 * followed by an extension. */
int mpvhdec_GetCodec(MpvHn *mpv, SfdSjChunk *buf) {
    char *p;
    int kind;

    if (mpv->strmType != 0) {
        return mpv->strmType;
    }
    p = MPV_SearchDelim(buf->data, buf->len, 64);
    if (p == 0) {
        return mpv->strmType;
    }
    p += 4;
    p = MPV_SearchDelim(p, buf->len - (p - buf->data), -1);
    if (p == 0) {
        return mpv->strmType;
    }
    kind = MPV_CheckDelim((unsigned char *)p);
    if (kind & 0x10) {
        mpv->strmType = 2;
    } else if (kind != 0) {
        mpv->strmType = 1;
    }
    return mpv->strmType;
}

/* The sequence header: picture size, rate, buffer size and the optional quantiser matrices (skipped). */
int mpv_DecSeqHdr(MpvHn *mpv, SfdSj *sj) {
    MpvPicInf *inf = &mpv->picInf;
    SfdSjChunk *ck = &mpv->chunk;
    SfdSjChunk rest;
    unsigned int cur, nxt;
    unsigned int val;
    int bit;
    char *rp;
    char *end;
    int i;

    mpv->usrDatLevel = MPV_UDLVL_SEQ;
    inf->seqCount++;
    sj->vtbl->getChunk(sj, 1, 0x7FFFFFFF, ck);
    BITS_INIT(ck->data, cur, nxt, bit, rp);
    BITS_GET32(val, cur, nxt, bit, rp);
    BITS_GET(inf->horizontalSize, 12, cur, nxt, bit, rp);
    BITS_GET(inf->verticalSize, 12, cur, nxt, bit, rp);
    BITS_GET(mpv->pelAspectRatio, 4, cur, nxt, bit, rp);
    BITS_GET(val, 4, cur, nxt, bit, rp);
    inf->frameRateCode = val;
    BITS_GET(mpv->bitRate, 18, cur, nxt, bit, rp);
    BITS_SKIP(1, cur, nxt, bit, rp);
    BITS_GET(mpv->vbvBufferSize, 10, cur, nxt, bit, rp);
    BITS_GET1(mpv->constrainedParams, cur, nxt, bit, rp);
    BITS_GET1(val, cur, nxt, bit, rp);
    if (val != 0) {
        for (i = 0; i < 64; i++) {
            BITS_GET(val, 8, cur, nxt, bit, rp);
        }
    }
    BITS_GET1(val, cur, nxt, bit, rp);
    if (val != 0) {
        for (i = 0; i < 64; i++) {
            BITS_GET(val, 8, cur, nxt, bit, rp);
        }
    }
    inf->mbWidth = (inf->horizontalSize + 15) >> 4;
    inf->mbHeight = (inf->verticalSize + 15) >> 4;
    mpv->lastMbAddr = inf->mbHeight * inf->mbWidth - 1;
    inf->bitRate = mpv->bitRate;
    inf->vbvBufferSize = mpv->vbvBufferSize;
    inf->pelAspectRatio = mpv->pelAspectRatio;
    inf->constrainedParams = mpv->constrainedParams;
    end = rp + ((bit + 7) >> 3);
    end -= 8;
    SJ_SplitChunk(ck, end - mpv->chunk.data, ck, &rest);
    sj->vtbl->putChunk(sj, 0, ck);
    sj->vtbl->ungetChunk(sj, 1, &rest);
    return 0;
}

/* Decodes the group of pictures header at the head of the stream joint: its time code and flags. */
int mpvhdec_DecGscSj(MpvHn *mpv, SfdSj *sj) {
    MpvPicInf *inf = &mpv->picInf;
    SfdSjChunk *ck = &mpv->chunk;
    SfdSjChunk rest;
    unsigned int cur, nxt;
    unsigned int val;
    int bit;
    char *rp;
    char *end;

    mpv->usrDatLevel = MPV_UDLVL_GOP;
    inf->gopCount++;
    sj->vtbl->getChunk(sj, 1, 0x7FFFFFFF, ck);
    BITS_INIT(ck->data, cur, nxt, bit, rp);
    BITS_GET32(val, cur, nxt, bit, rp);
    BITS_GET(val, 25, cur, nxt, bit, rp);
    inf->pictures = val & 0x3F;
    val >>= 6;
    inf->seconds = val & 0x3F;
    val >>= 7;
    inf->minutes = val & 0x3F;
    val >>= 6;
    inf->hours = val & 0x1F;
    inf->dropFrameFlag = val >> 5;
    BITS_GET1(mpv->closedGop, cur, nxt, bit, rp);
    BITS_GET1(mpv->brokenLink, cur, nxt, bit, rp);
    end = rp + ((bit + 7) >> 3) - 8;
    SJ_SplitChunk(ck, end - mpv->chunk.data, ck, &rest);
    sj->vtbl->putChunk(sj, 0, ck);
    sj->vtbl->ungetChunk(sj, 1, &rest);
    return 0;
}

/* The picture header: temporal reference, coding type, VBV delay and the motion vector ranges of a P or B
 * picture; the extra picture bytes are skipped. -3 when the header runs past the chunk. */
int mpv_DecPicHdr(MpvHn *mpv, SfdSj *sj) {
    MpvPicInf *inf = &mpv->picInf;
    SfdSjChunk *ck = &mpv->chunk;
    SfdSjChunk rest;
    unsigned int cur, nxt;
    unsigned int val;
    int bit;
    char *rp;
    int type;
    int rSize;
    MpvMotionRange *range;
    char *q;
    char *end;

    mpv->usrDatLevel = MPV_UDLVL_PIC;
    sj->vtbl->getChunk(sj, 1, 0x7FFFFFFF, ck);
    BITS_INIT(ck->data, cur, nxt, bit, rp);
    BITS_GET32(val, cur, nxt, bit, rp);
    BITS_GET(inf->temporalReference, 10, cur, nxt, bit, rp);
    BITS_GET(val, 3, cur, nxt, bit, rp);
    inf->pictureCodingType = val;
    BITS_GET(mpv->vbvDelay, 16, cur, nxt, bit, rp);
    type = inf->pictureCodingType;
    if (type == 2 || type == 3) {
        range = &mpv->fwd;
        BITS_GET1(range->fullPel, cur, nxt, bit, rp);
        BITS_GET(rSize, 3, cur, nxt, bit, rp);
        range->rSize = --rSize;
        range->shift = 27 - rSize;
        range->f = 1 << rSize;
    }
    if (type == 3) {
        range = &mpv->bwd;
        BITS_GET1(range->fullPel, cur, nxt, bit, rp);
        BITS_GET(rSize, 3, cur, nxt, bit, rp);
        range->rSize = --rSize;
        range->shift = 27 - rSize;
        range->f = 1 << rSize;
    }
    mpv->f724 = mpv->f732;
    for (;;) {
        val = cur >> 31;
        if (val == 0) {
            BITS_SKIP(1, cur, nxt, bit, rp);
            break;
        }
        BITS_SKIP(9, cur, nxt, bit, rp);
        q = rp + ((bit + 7) >> 3) - 8;
        if (mpv->chunk.len <= q - mpv->chunk.data) {
            return -3;
        }
    }
    end = rp + ((bit + 7) >> 3) - 8;
    SJ_SplitChunk(ck, end - mpv->chunk.data, ck, &rest);
    sj->vtbl->putChunk(sj, 0, ck);
    sj->vtbl->ungetChunk(sj, 1, &rest);
    return 0;
}

/* the extension data after a header is skipped */
int mpvhdec_DecEscSj(MpvHn *mpv, SfdSj *sj, int type) {
    SfdSjChunk *ck = &mpv->chunk;
    SfdSjChunk rest;
    char *base;
    int bits;

    sj->vtbl->getChunk(sj, 1, 0x7FFFFFFF, ck);
    base = (char *)((int)ck->data & ~3);
    bits = (ck->data - base) * 8;
    base += bits >> 3;
    base += 4;
    SJ_SplitChunk(ck, base - ck->data, ck, &rest);
    sj->vtbl->putChunk(sj, 0, ck);
    sj->vtbl->ungetChunk(sj, 1, &rest);
    MPV_GoNextDelimSj(sj);
    return 0;
}

int mpv_ScanUsrTags(MpvHn *mpv, char *buf, int size);
int mpvhdec_AnalyUd(MpvHn *mpv, char *data, int len);
extern void *memcpy(void *dst, const void *src, unsigned int n);

/* Decodes the user data at the head of the stream joint and moves past it. */
int mpvhdec_DecUdscSj(MpvHn *mpv, SfdSj *sj, int type) {
    SfdSjChunk *ck = &mpv->chunk;
    SfdSjChunk rest;
    char *base;
    int bits;
    int ret;

    sj->vtbl->getChunk(sj, 1, 0x7FFFFFFF, ck);
    base = (char *)((int)ck->data & ~3);
    bits = (ck->data - base) * 8;
    ret = mpvhdec_AnalyUd(mpv, ck->data, mpv->chunk.len);
    base += 8;
    base += bits >> 3;
    base -= 4;
    SJ_SplitChunk(ck, base - ck->data, ck, &rest);

    sj->vtbl->putChunk(sj, 0, ck);
    sj->vtbl->ungetChunk(sj, 1, &rest);
    MPV_GoNextDelimSj(sj);
    return ret;
}

/* Copies the user data in data[0..len) into the stream joint registered for the current level, calls
 * that level's callback, and keeps the CRI tags. Returns the tag scan's result, or -1 when the data holds no
 * complete start-code-terminated block. */
int mpvhdec_AnalyUd(MpvHn *mpv, char *data, int len) {
    int result = 0;
    MpvUdLevel level = mpv->usrDatLevel;
    int i;
    int incomplete;
    SfdSjChunk ck;
    SfdSjChunk ck2;
    SfdSj *sj;
    int n;

    for (i = 4; i < len - 3; i++) {
        if (MPV_CheckDelim((unsigned char *)(data + i)) != 0) {
            break;
        }
    }
    incomplete = -1;
    if (i != len - 3) {
        incomplete = 0;
    }
    if (level == MPV_UDLVL_SEQ) {
        result = mpv_ScanUsrTags(mpv, data, i);
    }
    sj = mpv->bufEnt[level].sj;
    if (sj != 0) {
        sj->vtbl->getChunk(sj, 0, i, &ck);
        memcpy(ck.data, data, ck.len);
        sj->vtbl->putChunk(sj, 1, &ck);
        if (ck.len < i) {
            sj->vtbl->getChunk(sj, 0, i - ck.len, &ck2);
            memcpy(ck2.data, data + ck.len, ck2.len);
            sj->vtbl->putChunk(sj, 1, &ck2);
        }
        if (mpv->bufEnt[level].fn != 0) {
            mpv->bufEnt[level].fn(mpv->bufEnt[level].obj, level);
        }
    }
    if (level == 3) {
        if (mpv->low.width != 0) {
            n = mpv->low.height;
            if (i < n) {
                n = i;
            }
            mpv->low.flag = n;
            memcpy((void *)mpv->low.width, data, n);
        }
    }
    if (result != 0) {
        return result;
    }
    return incomplete;
}

/* Reads the CRI tags in user data: "IDCPREC" sets the IDCT precision, "STCCODE" the time code. */
int mpv_ScanUsrTags(MpvHn *mpv, char *buf, int size) {
    int n = size - 4;
    char *base = buf + 4;
    int i;
    char *p;

    for (i = 0; i < n; ) {
        p = base + i;
        i++;
        if (strncmp(p, mpv_tag_idcprec, 7) == 0)
            mpv->idcPrec = atoi(p + 16) != 0 ? 3 : 0;
        if (strncmp(p, mpv_tag_stccode, 7) == 0) {
            mpv->f860 = atoi(p + 16);
            mpv->f864 = atoi(p + 24);
            mpv->f868 = atoi(p + 32);
        }
        if (MPV_CheckDelim((unsigned char *)p) != 0)
            break;
    }
    return 0;
}

/* Moves a (data, remaining, offset) cursor to the next start code and returns its class; with none the
 * whole remainder is skipped and 0 returned. */
int MPVHDEC_GoNextDelim(char **data, int *remaining, int *offset) {
    char *found;
    int skip;
    int kind;

    found = MPV_SearchDelim(*data, *remaining, -1);
    kind = 0;
    if (found == 0) {
        skip = *remaining;
    } else {
        kind = MPV_CheckDelim((unsigned char *)found);
        skip = found - *data;
    }
    *remaining -= skip;
    *data += skip;
    *offset += skip;
    return kind;
}

/* Consumes the stream joint up to its next start code and returns that code's class (0 when the data
 * runs out; the last three bytes are kept for a start code split across chunks). */
int MPV_GoNextDelimSj(SfdSj *sj) {
    SfdSjChunk ck;
    SfdSjChunk rest;
    char *p;
    int kind;

    for (;;) {
        sj->vtbl->getChunk(sj, 1, 0x7FFFFFFF, &ck);
        if (ck.len < 4) {
            sj->vtbl->ungetChunk(sj, 1, &ck);
            kind = 0;
            break;
        }
        p = MPV_SearchDelim(ck.data, ck.len, -1);
        if (p == 0) {
            SJ_SplitChunk(&ck, ck.len - 3, &ck, &rest);
            sj->vtbl->putChunk(sj, 0, &ck);
            sj->vtbl->ungetChunk(sj, 1, &rest);
        } else {
            kind = MPV_CheckDelim((unsigned char *)p);
            SJ_SplitChunk(&ck, p - ck.data, &ck, &rest);
            sj->vtbl->putChunk(sj, 0, &ck);
            sj->vtbl->ungetChunk(sj, 1, &rest);
            break;
        }
    }
    return kind;
}

/* Skips to the next start code in mask; a pending skip request drops one picture first. Returns 0, or
 * -2 / -3 when none is found. */
int mpvhdec_RecoverSj(MpvHn *mpv, int mask, SfdSj *sj) {
    MpvErrObj *err = &mpv->err;
    int has = mpv->cond[1];
    int result;
    int kind;

    if (mpv->skipReq != 0) {
        mpv->skipReq = 0;
        mpv->skipCnt += 1;
        err->skipReqCnt += 1;
        if (has == 0) {
            return -2;
        }
        err->skipPicCnt += 1;
    }
    result = (has == 0) ? -2 : -3;
    do {
        kind = MPV_GoNextDelimSj(sj);
        if (kind == 0) {
            break;
        }
        if (kind & mask) {
            result = 0;
            break;
        }
    } while (MPV_MoveChunk(sj, 1, 4) == 4);
    return result;
}

/* Moves n bytes from one side of the stream joint to the other; returns how many moved. */
int MPV_MoveChunk(SfdSj *sj, int id, int n) {
    SfdSjChunk ck;
    int other = id == 0;

    sj->vtbl->getChunk(sj, id, n, &ck);
    sj->vtbl->putChunk(sj, other, &ck);
    return ck.len;
}

int MPV_GetIqmAdr(void) {
    return 0;
}

int MPV_GetNqmAdr(void) {
    return 0;
}
