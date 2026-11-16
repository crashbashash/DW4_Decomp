/* MPV header decoding: walks a video elementary stream through a stream joint, start code by start code,
 * and decodes the sequence, group and picture headers and the user data in front of a picture. */
#include "dw4/cri/mpv.h"

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

void MPV_SetUsrSj(MpvHn *mpv, int index, int addr, int f4, int f8) {
    MpvBufEnt *ent = &mpv->bufEnt[index];

    ent->addr = addr;
    ent->f4 = f4;
    ent->f8 = f8;
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

int MPV_DecodePicAtrSj(MpvHn *mpv, SfdSj *sj);

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

int mpvhdec_AnalyUd(MpvHn *mpv, char *data, int len);
int MPV_GoNextDelimSj(SfdSj *sj);

/* Decodes the user data at the head of the stream joint and moves past it. */
int mpvhdec_DecUdscSj(MpvHn *mpv, SfdSj *sj) {
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

int MPV_MoveChunk(SfdSj *sj, int id, int n);

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
