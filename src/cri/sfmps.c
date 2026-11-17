#include "dw4/cri/sfdhn.h"
#include "dw4/cri/mps.h"
#include "dw4/cri/mcp.h"
#include "dw4/cri/sfd.h"

enum {
    SFD_COND_DEMUX_SPLIT = 59,
    SFD_COND_SYSHD_FN = 85,
    SFD_COND_SYSHD_FN_OBJ = 86,
    SFD_COND_VIDEO = 5,
    SFD_COND_AUDIO = 6,
    SFD_COND_VIDEO_AUTO_OFF = 79,
    SFD_COND_AUDIO_AUTO_OFF = 80
};

enum {
    SFD_STAT_PLAYING = 2
};

/* The video stream's packets go to output 0, the audio's to output 1 and the user data to output 2. */
enum {
    SFMPS_OUT_VIDEO = 0,
    SFMPS_OUT_AUDIO = 1,
    SFMPS_OUT_USER = 2,
    SFMPS_NO_CH = 8
};

/* A time stamp queued with the video data it belongs to. */
typedef struct SfmpsPts {
    long pts;
    unsigned char *addr;
    int len;
} SfmpsPts;

/* What the application's audio-data callback is told about a write. */
typedef struct SfmpsWrInf {
    long pts;
    int len;
} SfmpsWrInf;

extern MpsWork sfmps_mps_work;
extern int sfmps_short_writes;
extern int (*sfmps_audio_fn)(void *obj, SfmpsWrInf *inf);


int sfmps_ChkFatal(void);
int sfmps_ExecServerSub(SfdHandle *hn);
void sfmps_SetSysHdFn(SfdHandle *hn);
int sfmps_Demux(SfdHandle *hn);
int sfmps_RingGetRead(SfdHandle *hn, unsigned char **addr, int *len, int limit, int *total);
int sfmps_RingAddRead(SfdHandle *hn, int len);
int sfmps_DemuxChunk(SfdHandle *hn, unsigned char *addr, int len, int *used, int *skip, int total);
int sfmps_IsZero(unsigned char *p, int n);
int sfmps_IsEndOfRingBuf(SfdHandle *hn, unsigned char *pos);
SfdChanInf *sfmps_GetSupSj(SfdHandle *hn);
int sfmps_CopySj(SfdSj *sj, unsigned char *data, int len);
int sfmps_AutoVchPlay(SfdHandle *hn, int dflt);
int sfmps_PutUoch(SfdHandle *hn, int id, unsigned char *data, int len);
int sfmps_ExecCopySj(SfdSj *sj, unsigned char *data, int len);
void sfmps_SetOutEnd(SfdHandle *hn, int value);
int sfmps_GetTermDst(SfdHandle *hn);
void sfmps_ProcPrep(SfdHandle *hn);
void sfmps_ChkPrepFlg(SfdHandle *hn);
int sfmps_GetPrepDst(SfdHandle *hn);
void sfmps_SetPrepDst(SfdHandle *hn, int value);
int sfmps_IsPrepEnd(SfdHandle *hn, int ch);
void sfmps_AdjustAvPlay(SfdHandle *hn);
void sfmps_GetStmNum(SfdHandle *hn, int *audio, int *video);
void sfmps_SetMvInf(SfdHandle *hn);
void sfmps_SetPicRec(SfdHandle *hn);
void sfmps_UpdateOther(SfdHandle *hn);
void sfmps_AddTotals(SfdHandle *hn, int bytes, int packs);
void sfmps_ResetPrm(SfdMpsPrm *prm);
void sfmps_ErrFn(void *hn, int code);
int sfmps_DestroySub(MpsHn *mps);
void sfmps_SetCustomPketLen(SfdHandle *hn);
int sfmps_ReprocessHdr(SfdHandle *hn, SfdMpsPrm *prm, SfdPicRec *rec);
SfdPicRec *sfmps_GetHd(SfdHandle *hn);
int sfmps_IsEffectiveEndcode(SfdHandle *hn, int kind);
void sfmps_ChkInEnd(SfdHandle *hn, int *done);
int sfmps_PutEs(SfdHandle *hn, int ch, unsigned char *data, int len, long pts);
int sfmps_ChkEnd(SfdHandle *hn, unsigned char *addr, int len, int total);
void sfmps_SkipNext(SfdHandle *hn, unsigned char *buf, int size, int *skip);
int sfmps_PutPes(SfdHandle *hn, unsigned char *data, int len, int *used, int *result);
void sfmps_Concat(SfdHandle *hn);
void sfmps_SetMpsRaw(SfdHandle *hn, MpsHn *mps, unsigned char *data, int len);

/* Attaches an object to stream id 0xBC..0xFF in the handle's stream table, with the callback run
 * on its data. */
int SFD_SetStmObject(SfdHandle *hn, int id, void *object, int (*cb)(void *obj, int arg), void *cbObj) {
    SfdMpsPrm *prm;

    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000171);
    }
    if ((unsigned int)(id - 0xBC) < 68) {
        prm = hn->mps.hn.prm;
        prm->object[id - 0xBC] = object;
        prm->stmCbObj = cbObj;
        prm->stmCb = cb;
    }
    return 0;
}

int SFD_GetVideoCh(void *sfd) {
    SfdHandle *hn = sfd;
    if (hn == 0) {
        return -1;
    }
    return hn->mps.hn.prm->videoCh;
}

int SFD_GetAudioCh(void *sfd) {
    SfdHandle *hn = sfd;
    if (hn == 0) {
        return -1;
    }
    return hn->mps.hn.prm->audioCh;
}

int SFMPS_Init(void) {
    int ret;

    if (sfmps_ChkFatal() != 0) {
        /* The EE short-loop workaround pads this empty loop with nops. */
        for (;;) {
        }
    }
    ret = MPS_Init(8, &sfmps_mps_work);
    if (ret != 0) {
        return sfd_ReportError(0, 0xFF000D01);
    }
    sfmps_short_writes = 0;
    return ret;
}

int sfmps_ChkFatal(void) {
    return 0;
}

int SFMPS_Finish(void) {
    MPS_Finish();
    return 0;
}

int SFMPS_ExecServer(SfdHandle *hn) {
    return sfmps_ExecServerSub(hn);
}

int sfmps_ExecServerSub(SfdHandle *hn) {
    int ret;

    if (sfmps_GetTermDst(hn) == 1) {
        return 0;
    }
    sfmps_SetSysHdFn(hn);
    ret = sfmps_Demux(hn);
    if (hn->stat == SFD_STAT_PLAYING) {
        sfmps_ProcPrep(hn);
    }
    return ret;
}

void sfmps_SetSysHdFn(SfdHandle *hn) {
    MpsHn *mps = hn->mps.hn.prm->mps;
    MpsSysHdFn fn = (MpsSysHdFn)SFSET_GetCond(hn, SFD_COND_SYSHD_FN);

    MPS_SetSysHdFn(mps, fn, (void *)SFSET_GetCond(hn, SFD_COND_SYSHD_FN_OBJ));
}

/* Demultiplexes what the input channel holds, chunk by chunk. */
int sfmps_Demux(SfdHandle *hn) {
    int ret = 0;
    int total = 0;
    int packs = 0;
    int limit = hn->zeroPad;
    unsigned char *addr;
    int len;
    int avail;
    int used;
    int n;

    while (total < 0x7FFFFFFF) {
        ret = sfmps_RingGetRead(hn, &addr, &len, limit, &avail);
        if (ret != 0) {
            break;
        }
        ret = sfmps_DemuxChunk(hn, addr, len, &used, &n, avail);
        if (ret != 0 || used == 0) {
            break;
        }
        ret = sfmps_RingAddRead(hn, used);
        if (ret != 0) {
            break;
        }
        packs += n;
        total += used;
    }
    sfmps_AddTotals(hn, total, packs);
    return ret;
}

int sfmps_RingGetRead(SfdHandle *hn, unsigned char **addr, int *len, int limit, int *total) {
    SfdBufStat stat;
    int ret;

    ret = SFBUF_RingGetRead(hn, hn->mps.from, &stat);
    if (ret == 0) {
        *len = stat.ck0.len;
        *addr = (unsigned char *)stat.ck0.data;
        *total = stat.ck0.len + stat.ck1.len;
    }
    return ret;
}

/* matching construct: hand search — declared int with no return statement, and the call wrapped in a
 * do-while(0) block, which keeps it from being a tail call */
int sfmps_RingAddRead(SfdHandle *hn, int len) {
    do {
        SFBUF_RingAddRead(hn, hn->mps.from, len);
    } while (0);
}

/* Demultiplexes the pack, system header or packet at addr: *used bytes are consumed, *skip of them
 * skipped as padding. */
int sfmps_DemuxChunk(SfdHandle *hn, unsigned char *addr, int len, int *used, int *skip, int total) {
    SfdMpsPrm *prm;
    MpsHn *mps;
    int ret;
    int kind;
    int hdrLen;
    int flags;
    int term;
    int copied;
    int result;

    *used = 0;
    *skip = 0;
    prm = hn->mps.hn.prm;
    mps = prm->mps;
    ret = 0;
    if (sfmps_ChkEnd(hn, addr, len, total) == 0) {
        return ret;
    }
    if (len >= 4) {
        kind = MPS_GetStartCodeKind(addr);
    } else {
        kind = 0;
    }
    MPS_SetAuxFn(mps, (MpsCbFn)SFSET_GetCond(hn, 87), (void *)SFSET_GetCond(hn, 88));
    MPS_SetPesFn(mps, (MpsCbFn)SFSET_GetCond(hn, 91), (void *)SFSET_GetCond(hn, 92));
    if (MPS_DecodeChunk(mps, addr, len, &hdrLen, &flags) != 0) {
        ret = sfd_ReportError(hn, 0xFF000D03);
    }
    if (flags & MPS_SC_SYSHDR) {
        sfmps_SetMpsRaw(hn, mps, addr, len);
    }
    if (flags == MPS_SC_END && SFCON_IsEndcodeSkip(hn) != 0) {
        sfmps_Concat(hn);
        *used = 4;
        prm->f344 = 4;
    } else if (flags == MPS_SC_END && SFCON_IsSystemEndcodeSkip(hn) != 0) {
        *used = 4;
        prm->f344 = 4;
    } else if (kind == 0) {
        sfmps_SkipNext(hn, addr, len, skip);
        *used = *skip;
        if (*skip > 0 && prm->f344 >= 0) {
            if (prm->f344 >= hn->zeroPad) {
                prm->f344 += *skip;
            } else if (prm->f344 + *skip > hn->zeroPad) {
                *skip = *skip - (hn->zeroPad - prm->f344);
                prm->f344 = hn->zeroPad + *skip;
            } else {
                prm->f344 += *skip;
                *skip = 0;
            }
        }
    } else if (!(flags & MPS_SC_PES)) {
        sfmps_ChkInEnd(hn, &term);
        if (term == 0 && len > hn->zeroPad) {
            if (hdrLen > 0) {
                *used = hdrLen;
                *skip = hdrLen;
            } else {
                *used = 1;
                *skip = 1;
            }
        }
    } else {
        ret = sfmps_PutPes(hn, addr + hdrLen, len - hdrLen, &copied, &result);
        if (result == 1) {
            *used = hdrLen + copied;
        }
        prm->f344 = -1;
    }
    return ret;
}

/* How many bytes to skip before the next start code: the zero padding, or up to the first start code. */
void sfmps_SkipNext(SfdHandle *hn, unsigned char *buf, int size, int *skip) {
    int n;
    int count;

    *skip = 0;
    n = hn->zeroPad;
    if (size >= n + 3 && sfmps_IsZero(buf, n) != 0) {
        *skip = n;
        return;
    }
    count = 0;
    while (size >= 4) {
        if (MPS_GetStartCodeKind(buf++) & (MPS_SC_END | MPS_SC_PES | MPS_SC_PACK)) {
            *skip = count;
            return;
        }
        size--;
        count++;
    }
    if (size >= 1 && size <= 3 && sfmps_IsEndOfRingBuf(hn, buf + size) != 0) {
        count += size;
    }
    *skip = count;
}

int sfmps_IsZero(unsigned char *p, int n) {
    int i;

    for (i = 0; i < n; i++) {
        if (*p++ != 0) {
            return 0;
        }
    }
    return 1;
}

/* Whether pos is the end of the input channel's buffer, once the channel has stopped filling. */
int sfmps_IsEndOfRingBuf(SfdHandle *hn, unsigned char *pos) {
    SfdChanInf *in = sfmps_GetSupSj(hn);

    if (in->data == 0 && (in->xsize != 0 || in->f20 != 0)) {
        return 0;
    }
    return pos == in->buf + in->size;
}

SfdChanInf *sfmps_GetSupSj(SfdHandle *hn) {
    return &hn->chan[hn->mps.from].inf;
}

/* Puts data into a ring and, when it went in, runs the callback. */
int sfmps_PutAndNotify(SfdSj *sj, int (*cb)(void *obj, int arg), void *obj, int arg, unsigned char *data, int len) {
    int ret = sfmps_CopySj(sj, data, len);

    if (ret == 1 && cb != 0) {
        cb(obj, arg);
    }
    return ret;
}

/* An audio packet: remembers which audio stream is played and the earliest time stamp, then writes it. */
int sfmps_CopyAudio(SfdHandle *hn, int stm, unsigned char *data, int len, long pts) {
    SfdMpsSlot *mps;
    SfdMpsPrm *prm;
    int sel;

    if (SFSET_GetCond(hn, SFD_COND_AUDIO) == 0) {
        return 1;
    }
    mps = &hn->mps;
    prm = mps->hn.prm;
    if (prm->audioCh == -1) {
        prm->audioCh = stm;
    }
    if (prm->f48 == -1) {
        prm->f48 = stm;
    }
    sel = SFSET_GetCond(hn, 30);
    if (sel != -1) {
        if (SFSET_GetCond(hn, 55) != 0 ? stm < prm->f40 : stm == prm->f48) {
            prm->audioCh = sel;
        }
    }
    prm->f40 = stm;
    if (prm->audioCh != stm) {
        return 1;
    }
    if (pts >= 0) {
        prm->startPts = pts < prm->startPts ? pts : prm->startPts;
        prm->firstPts = pts < prm->firstPts ? pts : prm->firstPts;
    }
    return sfmps_PutEs(hn, mps->outputs[SFMPS_OUT_AUDIO], data, len, pts);
}

/* A video packet: remembers which video stream is played (switching only at a sequence or group header),
 * then writes what the picture layer keeps of it. */
int sfmps_CopyVideo(SfdHandle *hn, int stm, unsigned char *data, int len, long pts) {
    SfdMpsSlot *mps;
    SfdMpsPrm *prm;
    int sel;
    int ret;
    signed char *head = (signed char *)data;

    if (SFSET_GetCond(hn, SFD_COND_VIDEO) == 0) {
        return 1;
    }
    mps = &hn->mps;
    prm = mps->hn.prm;
    if (prm->videoCh == -1) {
        prm->videoCh = sfmps_AutoVchPlay(hn, stm);
    }
    if (prm->f44 == -1) {
        prm->f44 = stm;
    }
    sel = SFSET_GetCond(hn, 29);
    if (sel != -1) {
        if (SFSET_GetCond(hn, 55) != 0 ? stm < prm->f36 : stm == prm->f44) {
            if (prm->videoCh != sel && len >= 4 && head[0] == 0 && head[1] == 0
                && (unsigned char)head[2] == 1 && ((unsigned char)head[3] == 0xB3 || (unsigned char)head[3] == 0xB8)) {
                prm->videoCh = sel;
            }
        }
    }
    prm->f36 = stm;
    if (prm->videoCh != stm) {
        return 1;
    }
    len = SFMPVP_Put(hn, data, len);
    if (len <= 0) {
        return 0;
    }
    ret = sfmps_PutEs(hn, mps->outputs[SFMPS_OUT_VIDEO], data, len, pts);
    if (ret != 1) {
        SFMPVP_Unput(hn, len);
    } else {
        SFMPVP_SearchPsc(hn, data, len);
    }
    return ret;
}

/* Whether a packet split across a pack may be passed on as it is. */
int sfmps_AutoVchPlay(SfdHandle *hn, int dflt) {
    int mode = SFSET_GetCond(hn, SFD_COND_DEMUX_SPLIT);
    int audio;
    int video;

    if (mode == 1) {
        return dflt;
    }
    if (mode < 2) {
        return dflt;
    }
    if (mode == 2) {
        sfmps_GetStmNum(hn, &audio, &video);
        return video >= 2 ? mode : dflt;
    }
    return dflt;
}

/* The packet handler for private stream 2: a CRI header is taken in, the rest is user data. */
int sfmps_CopyPrvate(SfdHandle *hn, int id, unsigned char *data, int len) {
    int found;

    if (SFHDS_SetHdr(hn, id, data, len, &found) != 0) {
        sfmps_SetCustomPketLen(hn);
        if (found != 0) {
            sfmps_PutUoch(hn, 0, data - 18, len + 18);
        }
        return 1;
    }
    return sfmps_PutUoch(hn, id, data, len);
}

int sfmps_PutUoch(SfdHandle *hn, int id, unsigned char *data, int len) {
    SfdUoch uoch;
    int ret;
    void (*begin)(void *hn, int id);
    void (*end)(void *arg, int id);
    void *arg;

    if (hn->mps.outputs[SFMPS_OUT_USER] == SFMPS_NO_CH) {
        return 1;
    }
    SFBUF_GetUoch(hn, hn->mps.outputs[SFMPS_OUT_USER], id, &uoch);
    begin = uoch.begin;
    end = uoch.end;
    arg = uoch.arg;
    if (uoch.sj == 0) {
        return 1;
    }
    ret = sfmps_CopySj(uoch.sj, data, len);
    if (ret == 1) {
        if (begin != 0) {
            begin(hn, id);
        }
        if (end != 0) {
            end(arg, id);
        }
    }
    return ret;
}

/* Writes data into a ring in up to two pieces when it has room for all of it. */
int sfmps_CopySj(SfdSj *sj, unsigned char *data, int len) {
    int n;

    if (sj->vtbl->getNumData(sj, 0) < len) {
        return 0;
    }
    n = sfmps_ExecCopySj(sj, data, len);
    if (n == 0) {
        return 0;
    }
    len -= n;
    data += n;
    if (len > 0 && sfmps_ExecCopySj(sj, data, len) != len) {
        sfmps_short_writes++;
    }
    return 1;
}

int sfmps_ExecCopySj(SfdSj *sj, unsigned char *data, int len) {
    SfdSjChunk ck;

    sj->vtbl->getChunk(sj, 0, len, &ck);
    MEM_Copy(ck.data, (char *)data, ck.len);
    sj->vtbl->putChunk(sj, 1, &ck);
    return ck.len;
}

int sfmps_CopyPadding(void) {
    return 1;
}

/* Writes an elementary-stream packet into an output channel: a video packet's time stamp is
 * queued first, and an audio packet is offered to the application's callback. */
int sfmps_PutEs(SfdHandle *hn, int ch, unsigned char *data, int len, long pts) {
    SfdBufStat area;
    SfmpsPts e;
    SfmpsWrInf inf;
    int full;
    int ret;
    char *addr0;
    char *addr1;
    int len0;
    int tail;

    ret = SFBUF_RingGetWrite(hn, ch, &area);
    if (ret != 0) {
        return ret;
    }
    len0 = area.ck0.len;
    addr0 = area.ck0.data;
    addr1 = area.ck1.data;
    tail = area.tailLen;
    if (len0 + area.ck1.len < len) {
        return 0;
    }
    if (ch == 1) {
        if (pts >= 0) {
            if (SFPTS_IsPtsQueFull(hn, 1) != 0) {
                return 0;
            }
            e.pts = pts;
            e.addr = (unsigned char *)addr0;
            e.len = len;
            ret = SFPTS_WritePtsQue(hn, 1, &e, &full);
            if (ret != 0) {
                return ret;
            }
        }
    } else if (ch == 2) {
        if (sfmps_audio_fn != 0) {
            inf.pts = pts;
            inf.len = len;
            if (sfmps_audio_fn(&hn->tim.ptsm, &inf) == -1) {
                return 0;
            }
        }
    }
    if (len0 >= len) {
        MEM_Copy(addr0, (char *)data, len);
    } else {
        MEM_Copy(addr0, (char *)data, len0);
        MEM_Copy(addr1, (char *)data + len0, len - len0);
    }
    ret = SFBUF_RingAddWrite(hn, ch, len, tail);
    if (ret == 0) {
        ret = 1;
    }
    return ret;
}

void sfmps_SetOutEnd(SfdHandle *hn, int value) {
    SfdMpsSlot *mps = &hn->mps;

    SFBUF_SetTermFlg(hn, mps->outputs[1], 1);
    SFBUF_SetTermFlg(hn, mps->outputs[0], 1);
    SFBUF_SetTermFlg(hn, mps->outputs[2], 1);
    sfmpvps2_StopIpu(hn, value);
}

int sfmps_GetTermDst(SfdHandle *hn) {
    SfdMpsSlot *mps = &hn->mps;
    int a;
    int b;
    int c;

    a = SFBUF_GetTermFlg(hn, mps->outputs[1]);
    b = SFBUF_GetTermFlg(hn, mps->outputs[0]);
    c = SFBUF_GetTermFlg(hn, mps->outputs[2]);
    return a & b & c;
}

void sfmps_Concat(SfdHandle *hn) {
    SfdMpsPrm *prm = hn->mps.hn.prm;

    prm->nPics++;
}

int sfmps_ChkEnd(SfdHandle *hn, unsigned char *addr, int len, int total) {
    SfdMpsSlot *mps = &hn->mps;
    SfdMpsPrm *prm = mps->hn.prm;
    int from = mps->from;
    int kind;
    int done;

    if (len >= 4) {
        kind = MPS_GetStartCodeKind(addr);
        if (kind == MPS_SC_END) {
            if (mps->f32 < 0) {
                mps->f32 = SFBUF_GetRTot(hn, from) + 4;
            }
            prm->f60 = 1;
        } else if (kind != 0) {
            prm->f60 = 0;
        }
    } else {
        kind = 0;
    }
    if (sfmps_IsEffectiveEndcode(hn, kind) != 0) {
        sfmps_SetOutEnd(hn, 1);
        return 0;
    }
    if (total < 4) {
        sfmps_ChkInEnd(hn, &done);
        if (done != 0) {
            return 0;
        }
    }
    if (len >= 64) {
        return 1;
    }
    if (kind != MPS_SC_PACK && kind != MPS_SC_PES) {
        return 1;
    }
    sfmps_ChkInEnd(hn, 0);
    return 0;
}

/* An end code ends the stream unless the next stream is linked or the supply is still open. */
int sfmps_IsEffectiveEndcode(SfdHandle *hn, int kind) {
    if (kind != MPS_SC_END) {
        return 0;
    }
    if (SFCON_IsEndcodeSkip(hn) || SFCON_IsSystemEndcodeSkip(hn)) {
        return 0;
    }
    return 1;
}

void sfmps_ChkInEnd(SfdHandle *hn, int *done) {
    SfdMpsSlot *mps = &hn->mps;
    SfdMpsPrm *prm = mps->hn.prm;
    int end;

    if (SFBUF_GetTermFlg(hn, mps->from) == 1) {
        sfmps_SetOutEnd(hn, prm->f60);
        end = 1;
    } else {
        end = 0;
    }
    if (done != 0) {
        *done = end;
    }
}

void sfmps_ProcPrep(SfdHandle *hn) {
    int audio;
    int video;

    sfmps_GetStmNum(hn, &audio, &video);
    sfmps_ChkPrepFlg(hn);
    sfmps_SetMvInf(hn);
    sfmps_AdjustAvPlay(hn);
    sfmps_SetPicRec(hn);
    sfmps_UpdateOther(hn);
}

void sfmps_ChkPrepFlg(SfdHandle *hn) {
    int in;

    if (sfmps_GetPrepDst(hn) != 1) {
        in = hn->mps.from;
        if (SFBUF_GetPrepFlg(hn, in) == 1 && sfmps_IsPrepEnd(hn, in) != 0) {
            sfmps_SetPrepDst(hn, 1);
        }
    }
}

int sfmps_GetPrepDst(SfdHandle *hn) {
    SfdMpsSlot *mps = &hn->mps;
    int a;
    int b;
    int c;

    a = SFBUF_GetPrepFlg(hn, mps->outputs[1]);
    b = SFBUF_GetPrepFlg(hn, mps->outputs[0]);
    c = SFBUF_GetPrepFlg(hn, mps->outputs[2]);
    return a | b | c;
}

void sfmps_SetPrepDst(SfdHandle *hn, int value) {
    SfdMpsSlot *mps = &hn->mps;

    SFBUF_SetPrepFlg(hn, mps->outputs[1], value);
    SFBUF_SetPrepFlg(hn, mps->outputs[0], value);
    SFBUF_SetPrepFlg(hn, mps->outputs[2], value);
}

/* Once a stream's output is drained and the transport says so, its play condition is cleared. */
void sfmps_AdjustAvPlay(SfdHandle *hn) {
    SfdMpsPrm *prm = hn->mps.hn.prm;

    if (SFSET_GetCond(hn, SFD_COND_AUDIO) != 0 && SFSET_GetCond(hn, SFD_COND_AUDIO_AUTO_OFF) != 0) {
        if (SFBUF_GetWTot(hn, 2) == 0 && prm->audioBound == 0) {
            if (SFTRN_GetPrepFlg(hn, 6) != 0) {
                SFSET_SetCond(hn, SFD_COND_AUDIO, 0);
            }
        }
    }
    if (SFSET_GetCond(hn, SFD_COND_VIDEO) != 0 && SFSET_GetCond(hn, SFD_COND_VIDEO_AUTO_OFF) != 0
        && SFBUF_GetWTot(hn, 1) == 0 && prm->videoBound == 0 && SFTRN_GetPrepFlg(hn, 7) != 0) {
        SFSET_SetCond(hn, SFD_COND_VIDEO, 0);
    }
}

/* The largest audio and video bounds over the three kinds of system header seen so far. */
void sfmps_GetStmNum(SfdHandle *hn, int *audio, int *video) {
    MpsSysHd hd;
    int i = 0;
    int maxAudio = 0;
    int maxVideo = 0;
    SfdMpsPrm *prm = hn->mps.hn.prm;
    MpsHn *mps = prm->mps;

    do {
        MPS_GetSysHdOfKind(mps, &hd, i++);
        if (hd.audioBound >= maxAudio) {
            maxAudio = hd.audioBound;
        }
        if (hd.videoBound >= maxVideo) {
            maxVideo = hd.videoBound;
        }
    } while (i < 3);
    prm->videoBound = maxVideo;
    prm->audioBound = maxAudio;
    *audio = maxAudio;
    *video = prm->videoBound;
}

void sfmps_SetMvInf(SfdHandle *hn) {
    SfdMvInf *video = &hn->mvInf;
    SfdMpsPrm *prm = hn->mps.hn.prm;
    MpsHn *mps = prm->mps;
    MpsPackHd pack;
    MpsSysHd sys;

    MPS_GetPackHd(mps, &pack);
    if (pack.muxRate > 0) {
        video->muxRate = pack.muxRate;
    }
    MPS_GetSysHdOfKind(mps, &sys, 1);
    if (sys.fixedFlag != -1) {
        video->fixedFlag = sys.fixedFlag;
    }
    if (video->audioBound == -1) {
        video->audioBound = prm->audioBound;
    }
    if (video->videoBound == -1) {
        video->videoBound = prm->videoBound;
    }
}

/* Keeps the time offset of the first picture and, in a fresh record, the stream's parameters. */
void sfmps_SetPicRec(SfdHandle *hn) {
    SfdPicRec *rec = sfmps_GetHd(hn);
    SfdTim *tim = &hn->tim;
    SfdMpsPrm *prm;
    SfdMvInf *video;
    long first;

    if (rec != 0) {
        prm = hn->mps.hn.prm;
        first = prm->firstPts;
        if (first != 0x7FFFFFFFFFFFFFFF) {
            video = &hn->mvInf;
            tim->ofsTime = first - rec->startPts;
            if (rec->valid == 0) {
                rec->baseTime = tim->baseTime;
                rec->bps = video->muxRate * 50;
                rec->startPts = prm->startPts;
                rec->f8 = video->fixedFlag;
                rec->videoBound = prm->videoBound;
                rec->audioBound = prm->audioBound;
                rec->f40 = prm->f44;
                rec->f44 = prm->f48;
            }
        }
    }
}

void sfmps_UpdateOther(SfdHandle *hn) {
}

/* Keeps a picture's user text (the first or the second of the system header's two) in the record. */
void sfmps_SetMpsRaw(SfdHandle *hn, MpsHn *mps, unsigned char *data, int len) {
    SfdPicRec *rec;
    SfdPicTxt *txt;
    char *dst;
    MpsSysHd sys;
    int n;

    rec = sfmps_GetHd(hn);
    if (rec == 0 || rec->valid != 0) {
        return;
    }
    MPS_GetSysHd(mps, &sys);
    n = len > 176 ? 176 : len;
    txt = &rec->txt;
    if (sys.videoBound > 0) {
        txt->len[0] = n;
        dst = txt->text[0];
    } else if (sys.audioBound > 0) {
        txt->len[1] = n;
        dst = txt->text[1];
    } else {
        return;
    }
    MEM_Copy(dst, (char *)data, n);
}

void sfmps_AddTotals(SfdHandle *hn, int bytes, int packs) {
    SfdSj *sj = hn->chan[0].inf.sj;
    int total;
    int rest;

    if (sj != 0) {
        sfbuf_GetSjPos(sj, &total, &rest);
        hn->plyInf.sysFlow = sfbuf_MergeTotal(hn->plyInf.sysFlow, total);
        hn->plyInf.sysByte += bytes;
        hn->plyInf.sysSkip += packs;
    }
}

void SFMPS_Create(SfdHandle *hn) {
    SfdMpsPrm *prm = &hn->mpsPrm;
    MpsHn *mps;

    hn->mps.hn.prm = prm;
    sfmps_ResetPrm(prm);
    mps = MPS_Create();
    if (mps == 0) {
        sfd_ReportError(0, 0xFF000D08);
    } else if (MPS_SetErrFn(mps, (MpsErrFn)sfmps_ErrFn, hn) != 0) {
        sfmps_DestroySub(mps);
        sfd_ReportError(0, 0xFF000D09);
    } else {
        prm->mps = mps;
    }
}

void sfmps_ResetPrm(SfdMpsPrm *prm) {
    int i;

    prm->mps = 0;
    prm->videoBound = 0;
    prm->audioBound = 0;
    prm->startPts = 0x7FFFFFFFFFFFFFFF;
    prm->firstPts = 0x7FFFFFFFFFFFFFFF;
    prm->nPics = 0;
    prm->f36 = 0x7FFFFFFF;
    prm->f40 = 0x7FFFFFFF;
    prm->f44 = -1;
    prm->f48 = -1;
    prm->videoCh = -1;
    prm->audioCh = -1;
    prm->f60 = 0;
    for (i = 67; i >= 0; i--) {
        prm->object[i] = 0;
    }
    prm->stmCb = 0;
    prm->stmCbObj = 0;
    prm->f344 = -1;
}

void sfmps_ErrFn(void *hn, int code) {
    sfd_ReportError(hn, code);
}

void SFMPS_Destroy(SfdHandle *hn) {
    if (sfmps_DestroySub(hn->mps.hn.prm->mps) != 0) {
        sfd_ReportError(hn, 0xFF000D0A);
    }
}

int sfmps_DestroySub(MpsHn *mps) {
    return MPS_Destroy(mps);
}

int SFMPS_Standby(void) {
    return 0;
}

int SFMPS_Start(void) {
    return 0;
}

int SFMPS_Stop(void) {
    return 0;
}

int SFMPS_Pause(void) {
    return 0;
}

void SFMPS_GetWrite(SfdHandle *hn) {
    sfd_ReportError(hn, 0xFF000D0B);
}

void SFMPS_AddWrite(SfdHandle *hn) {
    sfd_ReportError(hn, 0xFF000D0B);
}

void SFMPS_GetRead(SfdHandle *hn) {
    sfd_ReportError(hn, 0xFF000D0B);
}

void SFMPS_AddRead(SfdHandle *hn) {
    sfd_ReportError(hn, 0xFF000D0B);
}

/* Restores the header and the first picture's texts and times from the work record. */
int SFMPS_Seek(SfdHandle *hn) {
    SfdPicRec *rec = sfmps_GetHd(hn);
    SfdMpsPrm *prm;
    SfdTim *tim;
    int ret;

    if (rec == 0) {
        return 0;
    }
    if (rec->valid == 0) {
        return 0;
    }
    prm = hn->mps.hn.prm;
    SFHDS_ReprocessHdr(hn);
    sfmps_SetCustomPketLen(hn);
    tim = &hn->tim;
    ret = sfmps_ReprocessHdr(hn, prm, rec);
    if (ret == 0) {
        prm->f44 = rec->f40;
        tim->baseTime = rec->baseTime;
        prm->f48 = rec->f44;
        prm->startPts = rec->startPts;
    }
    return ret;
}

void sfmps_SetCustomPketLen(SfdHandle *hn) {
}

/* Decodes the two user texts of a picture record with the handle's demultiplexer. */
int sfmps_ReprocessHdr(SfdHandle *hn, SfdMpsPrm *prm, SfdPicRec *rec) {
    int consumed;
    int flags;
    SfdPicTxt *txt = &rec->txt;
    MpsHn *mps = prm->mps;
    int r0 = MPS_DecodeChunk(mps, (unsigned char *)txt->text[0], txt->len[0], &consumed, &flags);
    int r1 = MPS_DecodeChunk(mps, (unsigned char *)txt->text[1], txt->len[1], &consumed, &flags);

    if (r0 != 0 || r1 != 0) {
        return sfd_ReportError(hn, 0xFF000D0D);
    }
    return r1;
}

/* The picture record in the work record, until the stream has delivered its first picture. */
SfdPicRec *sfmps_GetHd(SfdHandle *hn) {
    if (hn->work == 0) {
        return 0;
    }
    if (SFMPS_GetConcatCnt(hn) > 0) {
        return 0;
    }
    return &hn->work->pic;
}

int SFMPS_GetConcatCnt(void *sfd) {
    SfdHandle *hn = sfd;
    return hn->mps.hn.prm->nPics;
}
int sfmps_IsPrepEnd(SfdHandle *hn, int ch) {
    int *cond = hn->cond;
    SfdChanInf *in = sfmps_GetSupSj(hn);
    int size = hn->f8;
    int need = cond[22];
    int prep;
    if (size <= 0) size = in->size;
    if (size <= 0) size = need;
    prep = (size < need) ? size : need;
    if (SFBUF_GetWTot(hn, 0) >= prep) return 1;
    return 0;
}
