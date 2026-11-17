/* MPV error reporting and the handle queries: error callbacks, start-code searches over a buffer or a
 * stream joint, and the picture and VBV values of the last sequence header. */
#include "dw4/cri/mpv.h"
#include "dw4/cri/sj.h"



MpvErrObj mpv_err_global = {0};

void mpv_InitLibErr(void) {
    mpv_ResetErr(&mpv_err_global);
}

/* matching construct: variant search — statement order; the unit compiler schedules the last independent
   store into the return delay slot and keeps the rest in source order */
void mpv_ResetErr(MpvErrObj *err) {
    err->fn = 0;
    err->arg = 0;
    err->code = 0;
    err->skipReqCnt = 0;
    err->skipPicCnt = 0;
}


void MPV_EntryErrFunc(MpvHn *mpv, int (*fn)(void *arg), void *arg) {
    MpvErrObj *err;

    if (MPVLIB_CheckHn(mpv) != 0) {
        mpv_ReportError(0, 0xFF030203);
        return;
    }
    err = &mpv->err;
    err->fn = fn;
    err->arg = arg;
}

int MPV_GetErrInf(MpvHn *mpv, MpvErrObj *out) {
    int status = MPVLIB_CheckHn(mpv);

    if (status != 0) {
        return mpv_ReportError(0, 0xFF030204);
    }
    *out = mpv->err;
    return status;
}

int mpv_CallErrFn(MpvErrObj *err, int code);

int mpv_ReportError(MpvHn *mpv, int code) {
    if (mpv == 0) {
        mpv_CallErrFn(&mpv_err_global, code);
    } else {
        mpv_CallErrFn(&mpv->err, code);
    }
    return code;
}

/* Records code and, when it is an error, calls the error callback; returns the callback's result. */
int mpv_CallErrFn(MpvErrObj *err, int code) {
    err->code = code;
    if (code != 0) {
        code = (int)err->fn;
        if (code != 0) {
            code = err->fn(err->arg);
        }
    }
    return code;
}


/* Decodes a picture from memory through a temporary memory stream joint; *used gets the bytes taken. */
int MPV_DecodeFrm(MpvHn *mpv, SfdSjChunk *buf, int *used, int arg) {
    SfdSj *sj = SJMEM_Create(buf->data, buf->len);
    int result;

    if (sj == 0) {
        return -1;
    }
    result = MPV_DecPicSj(mpv, sj, arg);
    *used = buf->len - sj->vtbl->getNumData(sj, 1);
    sj->vtbl->destroy(sj);
    return result;
}

/* Finds the next picture, group, sequence header or sequence end in a buffer; *ofst gets its offset,
 * or the buffer's length when there is none. */
int MPV_SkipFrm(MpvHn *mpv, SfdSjChunk *buf, int *ofst) {
    char *data;
    int len;
    char *hit;
    int code;

    if (MPVLIB_CheckHn(mpv) != 0) {
        return mpv_ReportError(0, 0xFF03020A);
    }
    data = buf->data;
    len = buf->len;
    hit = MPV_SearchDelim(data, len, 0xCC);
    code = 0xFF030305;
    if (hit == 0) {
        *ofst = len;
    } else {
        *ofst = hit - data;
        code = 0;
    }
    return mpv_ReportError(mpv, code);
}

void MPVFRM_Init(void) {
}

int MPV_DecPicSj(MpvHn *mpv, SfdSj *sj, int arg) {
    return -1;
}

/* As MPV_SkipFrm, skipping through a stream joint up to the delimiter. */
int MPV_SkipFrmSj(MpvHn *mpv, SfdSj *sj) {
    int code;
    int kind;

    if (MPVLIB_CheckHn(mpv) != 0) {
        return mpv_ReportError(0, 0xFF03020A);
    }
    code = 0xFF030305;
    for (;;) {
        kind = MPV_GoNextDelimSj(sj);
        if (kind == 0) {
            break;
        }
        if (kind & 0xCC) {
            code = 0;
            break;
        }
        if (MPV_MoveChunk(sj, 1, 4) != 4) {
            break;
        }
    }
    return mpv_ReportError(mpv, code);
}

int MPV_GetPicInf(MpvHn *mpv, MpvPicInf *out) {
    if (MPVLIB_CheckHn(mpv) != 0)
        return mpv_ReportError(0, 0xFF03020C);
    *out = mpv->picInf;
    return 0;
}

int MPV_GetBitRate(MpvHn *mpv, int *bitRate) {
    if (MPVLIB_CheckHn(mpv) != 0) {
        return mpv_ReportError(0, 0xFF03020D);
    }
    *bitRate = mpv->bitRate;
    return 0;
}

/* The VBV buffer size in bytes, the VBV delay, and the bytes that delay holds at the bit rate
 * (-1 for a variable bit rate). */
int MPV_GetVbvBufSiz(MpvHn *mpv, int *size, int *delay, int *bytes) {
    if (MPVLIB_CheckHn(mpv) != 0) {
        return mpv_ReportError(0, 0xFF03020F);
    }
    *size = mpv->vbvBufferSize << 11;
    *delay = mpv->vbvDelay;
    if (mpv->bitRate == 0x3FFFF) {
        *bytes = -1;
    } else {
        *bytes = mpv->vbvDelay * mpv->bitRate / 1800;
    }
    return 0;
}

int MPV_GetLinkFlg(MpvHn *mpv, int *inf3, int *inf4) {
    if (MPVLIB_CheckHn(mpv) != 0) {
        return mpv_ReportError(0, 0xFF03020E);
    }
    *inf3 = mpv->closedGop;
    *inf4 = mpv->brokenLink;
    return 0;
}

void mpvapi_Init(void) {
}
