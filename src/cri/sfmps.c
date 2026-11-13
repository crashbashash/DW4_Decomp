#include "dw4/cri/sfdhn.h"
#include "dw4/cri/mps.h"

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

int sfd_ReportError(SfdHandle *hn, int code);
int SFLIB_CheckHn(SfdHandle *hn);
int sfd_IsLnkStm(SfdHandle *hn);
int sfd_IsSupplyEnd(SfdHandle *hn);
int SFD_GetCond(SfdHandle *hn, int index);
void sfd_SetCond(SfdHandle *hn, int index, int value);
void UTY_MemCpy(char *dst, char *src, unsigned int n);
int sfbuf_GetWriteStat(SfdHandle *hn, int ch, SfdBufStat *stat);
int sfbuf_GetReadStat(SfdHandle *hn, int ch, SfdBufStat *stat);
int sfbuf_AddWriteLen(SfdHandle *hn, int ch, int len, int tail);
void sfbuf_AddReadLen(SfdHandle *hn, int ch, int len);
void sfbuf_GetUoch(SfdHandle *hn, int ch, int id, SfdUoch *uoch);
int sfbuf_GetNumData(SfdHandle *hn, int ch);
void sfbuf_SetFlagA(SfdHandle *hn, int ch, int value);
int sfbuf_GetFlagA(SfdHandle *hn, int ch);
int sfbuf_SetFlagB(SfdHandle *hn, int ch, int value);
int sfbuf_GetFlagB(SfdHandle *hn, int ch);
void sfbuf_GetSjPos(SfdSj *sj, int *total, int *rest);
long sfbuf_MergeTotal(long total, unsigned int low);
int sftrn_GetFlagA(SfdHandle *hn, int flag);
int sfring_IsFull(SfdHandle *hn, int ch);
int sfring_PutItem(SfdHandle *hn, int ch, SfmpsPts *item, int *full);
void sfmpvps2_StopIpu(SfdHandle *hn, int value);
int sfhdr_ChkPrv2(SfdHandle *hn, int kind, unsigned char *data, int len, int *found);
void sfhdr_LoadRec(SfdHandle *hn);

int sfmps_ChkLib(void);
int sfmps_Exec(SfdHandle *hn);
void sfmps_SetSysHdFn(SfdHandle *hn);
int sfmps_Demux(SfdHandle *hn);
int sfmps_GetData(SfdHandle *hn, unsigned char **addr, int *len, int limit, int *total);
int sfmps_AddData(SfdHandle *hn, int len);
int sfmps_DemuxChunk(SfdHandle *hn, unsigned char *addr, int len, int *used, int *packs, int total);
int sfmps_IsZero(unsigned char *p, int n);
int sfmps_IsTail(SfdHandle *hn, unsigned char *pos);
SfdChanInf *sfmps_GetInChan(SfdHandle *hn);
int sfmps_PutSj(SfdSj *sj, unsigned char *data, int len);
int sfmps_GetSplitMode(SfdHandle *hn, int dflt);
int sfmps_PutUoch(SfdHandle *hn, int id, unsigned char *data, int len);
int sfmps_PutSjChunk(SfdSj *sj, unsigned char *data, int len);
void sfmps_SetOutEnd(SfdHandle *hn, int value);
int sfmps_IsOutEnd(SfdHandle *hn);
void sfmps_UpdateInf(SfdHandle *hn);
void sfmps_ChkTerm(SfdHandle *hn);
int sfmps_IsAnyOutFlagA(SfdHandle *hn);
void sfmps_SetOutFlagA(SfdHandle *hn, int value);
int sfmps_IsInFull(SfdHandle *hn, int ch);
void sfmps_ClearAvCond(SfdHandle *hn);
void sfmps_GetSysMax(SfdHandle *hn, int *audio, int *video);
void sfmps_UpdateVideoInf(SfdHandle *hn);
void sfmps_SetPicRec(SfdHandle *hn);
void sfmps_UpdateOther(SfdHandle *hn);
void sfmps_AddTotals(SfdHandle *hn, int bytes, int packs);
void sfmps_ResetPrm(SfdMpsPrm *prm);
void sfmps_ErrFn(void *hn, int code);
int sfmps_DestroyMps(MpsHn *mps);
void sfmps_NotifyHdr(SfdHandle *hn);
int sfd_DecodePicTexts(SfdHandle *hn, SfdMpsPrm *prm, SfdPicRec *rec);
SfdPicRec *sfmps_GetPicRec(SfdHandle *hn);
int sfmps_GetNumPics(SfdHandle *hn);

/* Attaches an object to stream id 0xBC..0xFF in the handle's stream table, with the callback run
 * on its data. */
int SFD_SetStmObject(SfdHandle *hn, int id, void *object, int (*cb)(void *obj, int arg), void *cbObj) {
    SfdMpsPrm *prm;

    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000171);
    }
    if ((unsigned int)(id - 0xBC) < 68) {
        prm = hn->mps.prm;
        prm->object[id - 0xBC] = object;
        prm->stmCbObj = cbObj;
        prm->stmCb = cb;
    }
    return 0;
}

int SFD_GetVideoCh(SfdHandle *hn) {
    if (hn == 0) {
        return -1;
    }
    return hn->mps.prm->videoCh;
}

int SFD_GetAudioCh(SfdHandle *hn) {
    if (hn == 0) {
        return -1;
    }
    return hn->mps.prm->audioCh;
}

int sfmps_Init(void) {
    int ret;

    if (sfmps_ChkLib() != 0) {
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

int sfmps_ChkLib(void) {
    return 0;
}

int sfmps_Finish(void) {
    MPS_Finish();
    return 0;
}

int sfmps_ExecServer(SfdHandle *hn) {
    return sfmps_Exec(hn);
}

int sfmps_Exec(SfdHandle *hn) {
    int ret;

    if (sfmps_IsOutEnd(hn) == 1) {
        return 0;
    }
    sfmps_SetSysHdFn(hn);
    ret = sfmps_Demux(hn);
    if (hn->stat == SFD_STAT_PLAYING) {
        sfmps_UpdateInf(hn);
    }
    return ret;
}

void sfmps_SetSysHdFn(SfdHandle *hn) {
    MpsHn *mps = hn->mps.prm->mps;
    MpsCbFn fn = (MpsCbFn)SFD_GetCond(hn, SFD_COND_SYSHD_FN);

    MPS_SetSysHdFn(mps, fn, (void *)SFD_GetCond(hn, SFD_COND_SYSHD_FN_OBJ));
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
        ret = sfmps_GetData(hn, &addr, &len, limit, &avail);
        if (ret != 0) {
            break;
        }
        ret = sfmps_DemuxChunk(hn, addr, len, &used, &n, avail);
        if (ret != 0 || used == 0) {
            break;
        }
        ret = sfmps_AddData(hn, used);
        if (ret != 0) {
            break;
        }
        packs += n;
        total += used;
    }
    sfmps_AddTotals(hn, total, packs);
    return ret;
}

int sfmps_GetData(SfdHandle *hn, unsigned char **addr, int *len, int limit, int *total) {
    SfdBufStat stat;
    int ret;

    ret = sfbuf_GetReadStat(hn, hn->mps.from, &stat);
    if (ret == 0) {
        *len = stat.ck0.len;
        *addr = (unsigned char *)stat.ck0.data;
        *total = stat.ck0.len + stat.ck1.len;
    }
    return ret;
}

/* matching construct: hand search — declared int with no return statement, and the call wrapped in a
 * do-while(0) block, which keeps it from being a tail call */
int sfmps_AddData(SfdHandle *hn, int len) {
    do {
        sfbuf_AddReadLen(hn, hn->mps.from, len);
    } while (0);
}

/* How many bytes to skip before the next start code: the zero padding, or up to the first start code. */
void sfmps_SkipPad(SfdHandle *hn, unsigned char *buf, int size, int *skip) {
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
    if (size >= 1 && size <= 3 && sfmps_IsTail(hn, buf + size) != 0) {
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
int sfmps_IsTail(SfdHandle *hn, unsigned char *pos) {
    SfdChanInf *in = sfmps_GetInChan(hn);

    if (in->data == 0 && (in->xsize != 0 || in->f20 != 0)) {
        return 0;
    }
    return pos == in->buf + in->size;
}

SfdChanInf *sfmps_GetInChan(SfdHandle *hn) {
    return &hn->chan[hn->mps.from].inf;
}

/* Puts data into a ring and, when it went in, runs the callback. */
int sfmps_PutAndNotify(SfdSj *sj, void (*cb)(int, int), int arg0, int arg1, unsigned char *data, int len) {
    int ret = sfmps_PutSj(sj, data, len);

    if (ret == 1 && cb != 0) {
        cb(arg0, arg1);
    }
    return ret;
}

/* Whether a packet split across a pack may be passed on as it is. */
int sfmps_GetSplitMode(SfdHandle *hn, int dflt) {
    int mode = SFD_GetCond(hn, SFD_COND_DEMUX_SPLIT);
    int audio;
    int video;

    if (mode == 1) {
        return dflt;
    }
    if (mode < 2) {
        return dflt;
    }
    if (mode == 2) {
        sfmps_GetSysMax(hn, &audio, &video);
        return video >= 2 ? mode : dflt;
    }
    return dflt;
}

/* The packet handler for private stream 2: a CRI header is taken in, the rest is user data. */
int sfmps_PutPrv2(SfdHandle *hn, int id, unsigned char *data, int len) {
    int found;

    if (sfhdr_ChkPrv2(hn, id, data, len, &found) != 0) {
        sfmps_NotifyHdr(hn);
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
    sfbuf_GetUoch(hn, hn->mps.outputs[SFMPS_OUT_USER], id, &uoch);
    begin = uoch.begin;
    end = uoch.end;
    arg = uoch.arg;
    if (uoch.sj == 0) {
        return 1;
    }
    ret = sfmps_PutSj(uoch.sj, data, len);
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
int sfmps_PutSj(SfdSj *sj, unsigned char *data, int len) {
    int n;

    if (sj->vtbl->getNumData(sj, 0) < len) {
        return 0;
    }
    n = sfmps_PutSjChunk(sj, data, len);
    if (n == 0) {
        return 0;
    }
    len -= n;
    data += n;
    if (len > 0 && sfmps_PutSjChunk(sj, data, len) != len) {
        sfmps_short_writes++;
    }
    return 1;
}

int sfmps_PutSjChunk(SfdSj *sj, unsigned char *data, int len) {
    SfdSjChunk ck;

    sj->vtbl->getChunk(sj, 0, len, &ck);
    UTY_MemCpy(ck.data, (char *)data, ck.len);
    sj->vtbl->putChunk(sj, 1, &ck);
    return ck.len;
}

int sfmps_PutPad(void) {
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

    ret = sfbuf_GetWriteStat(hn, ch, &area);
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
            if (sfring_IsFull(hn, 1) != 0) {
                return 0;
            }
            e.pts = pts;
            e.addr = (unsigned char *)addr0;
            e.len = len;
            ret = sfring_PutItem(hn, 1, &e, &full);
            if (ret != 0) {
                return ret;
            }
        }
    } else if (ch == 2) {
        if (sfmps_audio_fn != 0) {
            inf.pts = pts;
            inf.len = len;
            if (sfmps_audio_fn(hn->audioFnObj, &inf) == -1) {
                return 0;
            }
        }
    }
    if (len0 >= len) {
        UTY_MemCpy(addr0, (char *)data, len);
    } else {
        UTY_MemCpy(addr0, (char *)data, len0);
        UTY_MemCpy(addr1, (char *)data + len0, len - len0);
    }
    ret = sfbuf_AddWriteLen(hn, ch, len, tail);
    if (ret == 0) {
        ret = 1;
    }
    return ret;
}

void sfmps_SetOutEnd(SfdHandle *hn, int value) {
    SfdMpsSlot *mps = &hn->mps;

    sfbuf_SetFlagB(hn, mps->outputs[1], 1);
    sfbuf_SetFlagB(hn, mps->outputs[0], 1);
    sfbuf_SetFlagB(hn, mps->outputs[2], 1);
    sfmpvps2_StopIpu(hn, value);
}

int sfmps_IsOutEnd(SfdHandle *hn) {
    SfdMpsSlot *mps = &hn->mps;
    int a;
    int b;
    int c;

    a = sfbuf_GetFlagB(hn, mps->outputs[1]);
    b = sfbuf_GetFlagB(hn, mps->outputs[0]);
    c = sfbuf_GetFlagB(hn, mps->outputs[2]);
    return a & b & c;
}

int sfmps_IncPics(SfdHandle *hn) {
    SfdMpsPrm *prm = hn->mps.prm;

    return prm->nPics = prm->nPics + 1;
}

/* An end code ends the stream unless the next stream is linked or the supply is still open. */
int sfmps_IsEndCode(SfdHandle *hn, int kind) {
    if (kind != MPS_SC_END) {
        return 0;
    }
    if (sfd_IsLnkStm(hn) || sfd_IsSupplyEnd(hn)) {
        return 0;
    }
    return 1;
}

void sfmps_ChkInEnd(SfdHandle *hn, int *done) {
    SfdMpsSlot *mps = &hn->mps;
    SfdMpsPrm *prm = mps->prm;
    int end;

    if (sfbuf_GetFlagB(hn, mps->from) == 1) {
        sfmps_SetOutEnd(hn, prm->f60);
        end = 1;
    } else {
        end = 0;
    }
    if (done != 0) {
        *done = end;
    }
}

void sfmps_UpdateInf(SfdHandle *hn) {
    int audio;
    int video;

    sfmps_GetSysMax(hn, &audio, &video);
    sfmps_ChkTerm(hn);
    sfmps_UpdateVideoInf(hn);
    sfmps_ClearAvCond(hn);
    sfmps_SetPicRec(hn);
    sfmps_UpdateOther(hn);
}

void sfmps_ChkTerm(SfdHandle *hn) {
    int in;

    if (sfmps_IsAnyOutFlagA(hn) != 1) {
        in = hn->mps.from;
        if (sfbuf_GetFlagA(hn, in) == 1 && sfmps_IsInFull(hn, in) != 0) {
            sfmps_SetOutFlagA(hn, 1);
        }
    }
}

int sfmps_IsAnyOutFlagA(SfdHandle *hn) {
    SfdMpsSlot *mps = &hn->mps;
    int a;
    int b;
    int c;

    a = sfbuf_GetFlagA(hn, mps->outputs[1]);
    b = sfbuf_GetFlagA(hn, mps->outputs[0]);
    c = sfbuf_GetFlagA(hn, mps->outputs[2]);
    return a | b | c;
}

void sfmps_SetOutFlagA(SfdHandle *hn, int value) {
    SfdMpsSlot *mps = &hn->mps;

    sfbuf_SetFlagA(hn, mps->outputs[1], value);
    sfbuf_SetFlagA(hn, mps->outputs[0], value);
    sfbuf_SetFlagA(hn, mps->outputs[2], value);
}

/* Once a stream's output is drained and the transport says so, its play condition is cleared. */
void sfmps_ClearAvCond(SfdHandle *hn) {
    SfdMpsPrm *prm = hn->mps.prm;

    if (SFD_GetCond(hn, SFD_COND_AUDIO) != 0 && SFD_GetCond(hn, SFD_COND_AUDIO_AUTO_OFF) != 0) {
        if (sfbuf_GetNumData(hn, 2) == 0 && prm->audioBound == 0) {
            if (sftrn_GetFlagA(hn, 6) != 0) {
                sfd_SetCond(hn, SFD_COND_AUDIO, 0);
            }
        }
    }
    if (SFD_GetCond(hn, SFD_COND_VIDEO) != 0 && SFD_GetCond(hn, SFD_COND_VIDEO_AUTO_OFF) != 0
        && sfbuf_GetNumData(hn, 1) == 0 && prm->videoBound == 0 && sftrn_GetFlagA(hn, 7) != 0) {
        sfd_SetCond(hn, SFD_COND_VIDEO, 0);
    }
}

/* The largest audio and video bounds over the three kinds of system header seen so far. */
void sfmps_GetSysMax(SfdHandle *hn, int *audio, int *video) {
    MpsSysHd hd;
    int i = 0;
    int maxAudio = 0;
    int maxVideo = 0;
    SfdMpsPrm *prm = hn->mps.prm;
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

void sfmps_UpdateVideoInf(SfdHandle *hn) {
    SfdVideoInf *video = &hn->video;
    SfdMpsPrm *prm = hn->mps.prm;
    MpsHn *mps = prm->mps;
    MpsPackHd pack;
    MpsSysHd sys;

    MPS_GetPackHd(mps, &pack);
    if (pack.muxRate > 0) {
        video->muxRate = pack.muxRate;
    }
    MPS_GetSysHdOfKind(mps, &sys, 1);
    if (sys.f16 != -1) {
        video->f28 = sys.f16;
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
    SfdPicRec *rec = sfmps_GetPicRec(hn);
    SfdTimView *tim = &hn->tim;
    SfdMpsPrm *prm;
    SfdVideoInf *video;
    long first;

    if (rec != 0) {
        prm = hn->mps.prm;
        first = prm->firstPts;
        if (first != 0x7FFFFFFFFFFFFFFF) {
            video = &hn->video;
            tim->ofsTime = first - rec->startPts;
            if (rec->valid == 0) {
                rec->baseTime = tim->baseTime;
                rec->bps = video->muxRate * 50;
                rec->startPts = prm->startPts;
                rec->f8 = video->f28;
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
void sfmps_SetPicTxt(SfdHandle *hn, MpsHn *mps, unsigned char *data, int len) {
    SfdPicRec *rec;
    SfdPicTxt *txt;
    char *dst;
    MpsSysHd sys;
    int n;

    rec = sfmps_GetPicRec(hn);
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
    UTY_MemCpy(dst, (char *)data, n);
}

void sfmps_AddTotals(SfdHandle *hn, int bytes, int packs) {
    SfdSj *sj = hn->chan[0].inf.sj;
    int total;
    int rest;

    if (sj != 0) {
        sfbuf_GetSjPos(sj, &total, &rest);
        hn->readBytes = sfbuf_MergeTotal(hn->readBytes, total);
        hn->demuxBytes += bytes;
        hn->demuxPacks += packs;
    }
}

void sfmps_Create(SfdHandle *hn) {
    SfdMpsPrm *prm = &hn->mpsPrm;
    MpsHn *mps;

    hn->mps.prm = prm;
    sfmps_ResetPrm(prm);
    mps = MPS_Create();
    if (mps == 0) {
        sfd_ReportError(0, 0xFF000D08);
    } else if (MPS_EntryErrFunc(mps, (MpsErrFn)sfmps_ErrFn, hn) != 0) {
        sfmps_DestroyMps(mps);
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

void sfmps_Destroy(SfdHandle *hn) {
    if (sfmps_DestroyMps(hn->mps.prm->mps) != 0) {
        sfd_ReportError(hn, 0xFF000D0A);
    }
}

int sfmps_DestroyMps(MpsHn *mps) {
    return MPS_Destroy(mps);
}

int sfmps_Prep(void) {
    return 0;
}

int sfmps_Start(void) {
    return 0;
}

int sfmps_Stop(void) {
    return 0;
}

int sfmps_Pause(void) {
    return 0;
}

void sfmps_GetWrite(SfdHandle *hn) {
    sfd_ReportError(hn, 0xFF000D0B);
}

void sfmps_AddWrite(SfdHandle *hn) {
    sfd_ReportError(hn, 0xFF000D0B);
}

void sfmps_GetRead(SfdHandle *hn) {
    sfd_ReportError(hn, 0xFF000D0B);
}

void sfmps_AddRead(SfdHandle *hn) {
    sfd_ReportError(hn, 0xFF000D0B);
}

/* Restores the header and the first picture's texts and times from the work record. */
int sfmps_LoadRec(SfdHandle *hn) {
    SfdPicRec *rec = sfmps_GetPicRec(hn);
    SfdMpsPrm *prm;
    SfdTimView *tim;
    int ret;

    if (rec == 0) {
        return 0;
    }
    if (rec->valid == 0) {
        return 0;
    }
    prm = hn->mps.prm;
    sfhdr_LoadRec(hn);
    sfmps_NotifyHdr(hn);
    tim = &hn->tim;
    ret = sfd_DecodePicTexts(hn, prm, rec);
    if (ret == 0) {
        prm->f44 = rec->f40;
        tim->baseTime = rec->baseTime;
        prm->f48 = rec->f44;
        prm->startPts = rec->startPts;
    }
    return ret;
}

void sfmps_NotifyHdr(SfdHandle *hn) {
}

/* Decodes the two user texts of a picture record with the handle's demultiplexer. */
int sfd_DecodePicTexts(SfdHandle *hn, SfdMpsPrm *prm, SfdPicRec *rec) {
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
SfdPicRec *sfmps_GetPicRec(SfdHandle *hn) {
    if (hn->work == 0) {
        return 0;
    }
    if (sfmps_GetNumPics(hn) > 0) {
        return 0;
    }
    return &hn->work->pic;
}

int sfmps_GetNumPics(SfdHandle *hn) {
    return hn->mps.prm->nPics;
}
