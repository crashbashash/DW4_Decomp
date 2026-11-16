#include "dw4/cri/sfdhn.h"
#include "dw4/cri/sfh.h"

typedef int (*SfhGetFn)(SfhHn *sfh, int *value);
typedef int (*SfhGetStmFn)(SfhHn *sfh, unsigned char id, int *value);

enum {
    MPS_STMID_PRV2 = 0x1BF
};

static SfhHn sfhdr_sfh_work[SFH_MAX_HN];

int SFMPS_GetConcatCnt(SfdHandle *hn);
void SFH_Init(int maxHn, SfhHn *hns);
void SFH_Finish(void);
SfhHn *SFH_Create(char *buf, int size);
void SFH_Destroy(SfhHn *sfh);
int SFH_IsSfdHeader(SfhHn *sfh, int *ok);
int SFH_IsExistStmId(SfhHn *sfh, unsigned char id, int *exist);
int SFH_IsEffFtrInf(SfhHn *sfh, int id, int *avail);
int SFH_AnlyHdrToolVer(SfhHn *sfh, int *major, int *minor);
int SFH_AnlyByteRate(SfhHn *sfh, int *value);
int SFH_AnlyHdrSiz(SfhHn *sfh, int *value);
int SFH_AnlyPackType(SfhHn *sfh, int *value);
int SFH_AnlyPketSizLen(SfhHn *sfh, int *value);
int SFH_AnlyPackSiz(SfhHn *sfh, int *value);
int SFH_AnlyNumElemTot(SfhHn *sfh, int *value);
int SFH_AnlyNumElemAud(SfhHn *sfh, int *value);
int SFH_AnlyNumElemVid(SfhHn *sfh, int *value);
int SFH_AnlyNumElemPrv(SfhHn *sfh, int *value);
int SFH_AnlyMaxPlyLenAud(SfhHn *sfh, int *value);
int SFH_AnlyMaxPlyLenVid(SfhHn *sfh, int *value);
int SFH_AnlyMaxFrmNum(SfhHn *sfh, int *value);
int SFH_AnlyElemCodecAud(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyElemLayer(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyElemChNum(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyElemSmpHz(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyElemCodecVid(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyElemBitRate(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyElemPicSz(SfhHn *sfh, int id, int *width, int *height);
int SFH_AnlyElemPicRate(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyFtrColType(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyFtrPicType(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyFtrFixFlg(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyFtrShcFixFlg(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyFtrExpand(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyFtrGopN(SfhHn *sfh, unsigned char id, int *value);
int SFH_AnlyFtrGopM(SfhHn *sfh, unsigned char id, int *value);

int sfhds_IsPrvate2PketStart(unsigned char *p);
int SFSET_GetCond(SfdHandle *hn, int id);
void M2VMC_MacroBlock(char *dst, char *src, unsigned int n);
int sfhdr_SetHdr(SfdHandle *hn, unsigned char *data, int size);
int sfhds_ReadLong(unsigned char *p);
void sfhds_SetHdrSeek(SfdHandle *hn);
void sfhds_CopyFhd(SfdHdrInf *dst, SfdHdrInf *src);
SfdHdrInf *sfhds_GetHd(SfdHandle *hn);
void SFHDS_ProcessHdr(SfdHdrInf *hdr);
void sfhds_DoProcessHdr(SfhHn *sfh, SfdHdrInf *hdr);
void sfhds_AnlyHead(SfhHn *sfh, SfdHdrInf *hdr);
void sfhds_AnlySys(SfhHn *sfh, SfdHdrMux *mux);
int sfhds_AnlyUsedStmid(SfhHn *sfh, int first, int last);
void sfhds_AnlyAudio(SfhHn *sfh, int id, SfdHdrAudio *audio);
void sfhds_AnlyVideo(SfhHn *sfh, int id, SfdHdrVideo *video);
int sfhds_CallN(SfhHn *sfh, SfhGetFn get);
int sfhds_CallS(SfhHn *sfh, int id, SfhGetStmFn get);
void sfhds_SetMvInf(SfdHandle *hn);

void SFHDS_Init(void) {
    SFH_Init(SFH_MAX_HN, sfhdr_sfh_work);
}

void SFHDS_Finish(void) {
    SFH_Finish();
}

/* matching construct: variant search — statement order; the unit compiler (Sony EE GCC 2.96 -O2 -G0) schedules the last independent store of the body into the return delay slot and keeps the rest in source order, so the stores are written in retail's emitted order */
void SFHDS_InitFhd(SfdHdrInf *hdr) {
    hdr->valid = 0;
    hdr->verMajor = 0;
    hdr->verMinor = 0;
    hdr->muxRate = 0;
    hdr->size = 0;
}

/* matching construct: variant search — stmt order [1, 2, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
void SFHDS_FinishFhd(SfdHdrInf *hdr) {
    hdr->valid = 0;
    hdr->muxRate = 0;
    hdr->size = 0;
}

int SFHDS_SetHdr(SfdHandle *hn, int type, unsigned char *p, int size, int *set) {
    *set = 0;
    if (type != 2) {
        return 0;
    }
    p -= 6;
    size += 6;
    if (!sfhds_IsPrvate2PketStart(p)) {
        p -= 2;
        size += 2;
        if (!sfhds_IsPrvate2PketStart(p)) {
            return 0;
        }
    }
    p -= 12;
    size += 12;
    if (!SFHDS_IsSfdHeader(p, size)) {
        return 0;
    }
    *set = sfhdr_SetHdr(hn, p, size);
    return 1;
}

int sfhds_IsPrvate2PketStart(unsigned char *p) {
    return sfhds_ReadLong(p) == MPS_STMID_PRV2;
}

int sfhds_ReadLong(unsigned char *p) {
    return (((((p[0] << 8) | p[1]) << 8) | p[2]) << 8) | p[3];
}

int SFHDS_IsSfdHeader(unsigned char *p, int size) {
    SfhHn *sfh;
    int ok;

    sfh = SFH_Create(p, size);
    if (sfh == 0) {
        return 0;
    }
    if (SFH_IsSfdHeader(sfh, &ok) == 0) {
        ok = 0;
    }
    SFH_Destroy(sfh);
    return ok;
}

int sfhdr_SetHdr(SfdHandle *hn, unsigned char *data, int size) {
    void (*callback)(int obj, unsigned char *data, int size);
    int obj;
    int len;
    SfdHdrInf *hdr;

    callback = (void (*)(int, unsigned char *, int))SFSET_GetCond(hn, 75);
    obj = SFSET_GetCond(hn, 76);
    if (callback != 0) {
        callback(obj, data, size);
    }
    hdr = &hn->hdr;
    if (hdr->valid != 0) {
        return 0;
    }
    len = size > 2048 ? 2048 : size;
    M2VMC_MacroBlock(hn->hdr.data, (char *)data, len);
    hdr->size = len;
    SFHDS_ProcessHdr(hdr);
    sfhds_SetMvInf(hn);
    sfhds_SetHdrSeek(hn);
    return 1;
}

void sfhds_SetHdrSeek(SfdHandle *hn) {
    SfdHdrInf *rec = sfhds_GetHd(hn);

    if (rec != 0) {
        sfhds_CopyFhd(rec, &hn->hdr);
    }
}

void sfhds_CopyFhd(SfdHdrInf *dst, SfdHdrInf *src) {
    *dst = *src;
}

void SFHDS_ReprocessHdr(SfdHandle *hn) {
    SfdHdrInf *hdr = &hn->hdr;
    SfdHdrInf *rec = sfhds_GetHd(hn);

    if (rec != 0) {
        sfhds_CopyFhd(hdr, rec);
        SFHDS_ProcessHdr(hdr);
        sfhds_SetMvInf(hn);
    }
}

/* The header copy in the work record, until the stream has delivered its first picture. */
SfdHdrInf *sfhds_GetHd(SfdHandle *hn) {
    if (hn->work == 0) {
        return 0;
    }
    if (SFMPS_GetConcatCnt(hn) > 0) {
        return 0;
    }
    return &hn->work->hdr;
}

void SFHDS_ProcessHdr(SfdHdrInf *hdr) {
    SfhHn *sfh;

    sfh = SFH_Create(hdr->data, hdr->size);
    if (sfh != 0) {
        sfhds_DoProcessHdr(sfh, hdr);
        SFH_Destroy(sfh);
    }
}

void sfhds_DoProcessHdr(SfhHn *sfh, SfdHdrInf *hdr) {
    int ok;
    int major;
    int minor;
    int muxRate;
    int version;

    if (SFH_IsSfdHeader(sfh, &ok) == 0) {
        ok = 0;
    }
    if (ok == 0) {
        return;
    }
    if (SFH_AnlyHdrToolVer(sfh, &major, &minor) == 0) {
        major = 0;
        minor = 0;
    }
    hdr->verMajor = major;
    hdr->verMinor = minor;
    version = major * 100 + minor;
    if (SFH_AnlyByteRate(sfh, &muxRate) == 0) {
        muxRate = 0;
    }
    if (version < 110) {
        muxRate = -muxRate;
    }
    hdr->muxRate = muxRate;
    sfhds_AnlyHead(sfh, hdr);
    sfhds_AnlySys(sfh, &hdr->mux);
    hdr->adxStm = sfhds_AnlyUsedStmid(sfh, 0xBD, 0xBD);
    hdr->prv2Stm = sfhds_AnlyUsedStmid(sfh, 0xBF, 0xBF);
    hdr->audioStm = sfhds_AnlyUsedStmid(sfh, 0xC0, 0xDF);
    hdr->videoStm = sfhds_AnlyUsedStmid(sfh, 0xE0, 0xEF);
    sfhds_AnlyAudio(sfh, hdr->audioStm, &hdr->audio);
    sfhds_AnlyVideo(sfh, hdr->videoStm, &hdr->video);
    hdr->valid = 1;
}

void sfhds_AnlyHead(SfhHn *sfh, SfdHdrInf *hdr) {
    hdr->bitRate = sfhds_CallN(sfh, SFH_AnlyHdrSiz);
    hdr->sysType = sfhds_CallN(sfh, SFH_AnlyPackType);
    hdr->numStm = sfhds_CallN(sfh, SFH_AnlyPketSizLen);
    if (hdr->numStm == -1) {
        hdr->numStm = 2;
    }
    hdr->totalSize = sfhds_CallN(sfh, SFH_AnlyPackSiz);
}

void sfhds_AnlySys(SfhHn *sfh, SfdHdrMux *mux) {
    mux->kind[0] = sfhds_CallN(sfh, SFH_AnlyNumElemTot);
    mux->kind[1] = sfhds_CallN(sfh, SFH_AnlyNumElemAud);
    mux->kind[2] = sfhds_CallN(sfh, SFH_AnlyNumElemVid);
    mux->kind[3] = sfhds_CallN(sfh, SFH_AnlyNumElemPrv);
    mux->numFrm = sfhds_CallN(sfh, SFH_AnlyMaxPlyLenAud);
    mux->totalTime = sfhds_CallN(sfh, SFH_AnlyMaxPlyLenVid);
    mux->timeUnit = sfhds_CallN(sfh, SFH_AnlyMaxFrmNum);
}

/* The first stream id in [first, last] the header lists, or 0. */
int sfhds_AnlyUsedStmid(SfhHn *sfh, int first, int last) {
    int exist;
    int id;

    for (id = first; id <= last; id++) {
        if (SFH_IsExistStmId(sfh, (unsigned char)id, &exist) != 0 && exist != 0) {
            return id;
        }
    }
    return 0;
}

void sfhds_AnlyAudio(SfhHn *sfh, int id, SfdHdrAudio *audio) {
    if (id != 0) {
        audio->codec = sfhds_CallS(sfh, id, SFH_AnlyElemCodecAud);
        audio->nch = sfhds_CallS(sfh, id, SFH_AnlyElemLayer);
        audio->bps = sfhds_CallS(sfh, id, SFH_AnlyElemChNum);
        audio->sfreq = sfhds_CallS(sfh, id, SFH_AnlyElemSmpHz);
    }
}

void sfhds_AnlyVideo(SfhHn *sfh, int id, SfdHdrVideo *video) {
    int avail;

    video->codec = sfhds_CallS(sfh, id, SFH_AnlyElemCodecVid);
    video->bitRate = sfhds_CallS(sfh, id, SFH_AnlyElemBitRate);
    if (SFH_AnlyElemPicSz(sfh, id & 0xFF, &video->width, &video->height) == 0) {
        video->width = -1;
        video->height = -1;
    }
    video->frameRate = sfhds_CallS(sfh, id, SFH_AnlyElemPicRate);
    if (SFH_IsEffFtrInf(sfh, id & 0xFF, &avail) == 0) {
        avail = 0;
    }
    video->avail = avail != 0;
    if (avail == 0) {
        return;
    }
    video->picType = sfhds_CallS(sfh, id, SFH_AnlyFtrColType);
    video->profile = sfhds_CallS(sfh, id, SFH_AnlyFtrPicType);
    video->flag0 = sfhds_CallS(sfh, id, SFH_AnlyFtrFixFlg);
    video->flag4 = sfhds_CallS(sfh, id, SFH_AnlyFtrShcFixFlg);
    video->chroma = sfhds_CallS(sfh, id, SFH_AnlyFtrExpand);
    video->zFirst = sfhds_CallS(sfh, id, SFH_AnlyFtrGopN);
    video->zSecond = sfhds_CallS(sfh, id, SFH_AnlyFtrGopM);
}

/* A header value, or -1 when the header does not give it. */
int sfhds_CallN(SfhHn *sfh, SfhGetFn get) {
    int value;

    if (get(sfh, &value) != 0) {
        return value;
    }
    return -1;
}

int sfhds_CallS(SfhHn *sfh, int id, SfhGetStmFn get) {
    int value;

    if (get(sfh, id, &value) == 0) {
        return -1;
    }
    return value;
}

void sfhds_SetMvInf(SfdHandle *hn) {
    SfdHdrMux *mux = &hn->hdr.mux;
    SfdVideoInf *video = &hn->video;

    video->audioBound = mux->kind[1];
    video->videoBound = mux->kind[2];
    video->f44 = mux->kind[3];
}

int SFHDS_GetPketLenField(void) {
    return 2;
}

/* The header's version times 100, or 0 before a header has been read. */
int SFHDS_GetMuxVerNum(SfdHandle *hn) {
    SfdHdrInf *hdr = &hn->hdr;

    if (hdr->valid == 0) {
        return 0;
    }
    return hdr->verMajor * 100 + hdr->verMinor;
}

int SFHDS_GetColType(SfdHandle *hn) {
    SfdHdrVideo *video = &hn->hdr.video;

    if (hn->hdr.valid == 0) {
        return -1;
    }
    if (video->avail == 0) {
        return -1;
    }
    return video->picType;
}
