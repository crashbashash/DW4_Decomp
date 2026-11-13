#include "dw4/cri/sfdhn.h"

typedef struct SfhHn SfhHn;
typedef int (*SfhGetFn)(SfhHn *sfh, int *value);
typedef int (*SfhGetStmFn)(SfhHn *sfh, unsigned char id, int *value);

enum {
    MPS_STMID_PRV2 = 0x1BF
};

extern SfhHn sfhdr_sfh_work[];

int sfmps_GetNumPics(SfdHandle *hn);
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

int sfhdr_IsPrv2(unsigned char *p);
int sfhdr_GetCode(unsigned char *p);
int sfhdr_IsHdr(unsigned char *p, int size);
void sfhdr_SaveRec(SfdHandle *hn);
void sfhdr_CopyInf(SfdHdrInf *dst, SfdHdrInf *src);
SfdHdrInf *sfhdr_GetRecHdr(SfdHandle *hn);
void sfhdr_Analy(SfdHdrInf *hdr);
void sfhdr_ReadInf(SfhHn *sfh, SfdHdrInf *hdr);
void sfhdr_ReadSys(SfhHn *sfh, SfdHdrInf *hdr);
void sfhdr_ReadMux(SfhHn *sfh, SfdHdrMux *mux);
int sfhdr_FindStm(SfhHn *sfh, int first, int last);
void sfhdr_ReadAudio(SfhHn *sfh, int id, SfdHdrAudio *audio);
void sfhdr_ReadVideo(SfhHn *sfh, int id, SfdHdrVideo *video);
int sfhdr_Get(SfhHn *sfh, SfhGetFn get);
int sfhdr_GetStm(SfhHn *sfh, int id, SfhGetStmFn get);
void sfhdr_SetVideoInf(SfdHandle *hn);

void sfhdr_Init(void) {
    SFH_Init(32, sfhdr_sfh_work);
}

void sfhdr_Finish(void) {
    SFH_Finish();
}

/* matching construct: variant search — statement order; the unit compiler (Sony EE GCC 2.96 -O2 -G0) schedules the last independent store of the body into the return delay slot and keeps the rest in source order, so the stores are written in retail's emitted order */
void sfhdr_InitInf(SfdHdrInf *hdr) {
    hdr->valid = 0;
    hdr->verMajor = 0;
    hdr->verMinor = 0;
    hdr->muxRate = 0;
    hdr->size = 0;
}

/* matching construct: variant search — stmt order [1, 2, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
void sfhdr_ResetInf(SfdHdrInf *hdr) {
    hdr->valid = 0;
    hdr->muxRate = 0;
    hdr->size = 0;
}

int sfhdr_IsPrv2(unsigned char *p) {
    return sfhdr_GetCode(p) == MPS_STMID_PRV2;
}

int sfhdr_GetCode(unsigned char *p) {
    return (((((p[0] << 8) | p[1]) << 8) | p[2]) << 8) | p[3];
}

int sfhdr_IsHdr(unsigned char *p, int size) {
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

void sfhdr_SaveRec(SfdHandle *hn) {
    SfdHdrInf *rec = sfhdr_GetRecHdr(hn);

    if (rec != 0) {
        sfhdr_CopyInf(rec, &hn->hdr);
    }
}

void sfhdr_CopyInf(SfdHdrInf *dst, SfdHdrInf *src) {
    *dst = *src;
}

void sfhdr_LoadRec(SfdHandle *hn) {
    SfdHdrInf *hdr = &hn->hdr;
    SfdHdrInf *rec = sfhdr_GetRecHdr(hn);

    if (rec != 0) {
        sfhdr_CopyInf(hdr, rec);
        sfhdr_Analy(hdr);
        sfhdr_SetVideoInf(hn);
    }
}

/* The header copy in the work record, until the stream has delivered its first picture. */
SfdHdrInf *sfhdr_GetRecHdr(SfdHandle *hn) {
    if (hn->work == 0) {
        return 0;
    }
    if (sfmps_GetNumPics(hn) > 0) {
        return 0;
    }
    return &hn->work->hdr;
}

void sfhdr_Analy(SfdHdrInf *hdr) {
    SfhHn *sfh;

    sfh = SFH_Create(hdr->data, hdr->size);
    if (sfh != 0) {
        sfhdr_ReadInf(sfh, hdr);
        SFH_Destroy(sfh);
    }
}

void sfhdr_ReadInf(SfhHn *sfh, SfdHdrInf *hdr) {
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
    sfhdr_ReadSys(sfh, hdr);
    sfhdr_ReadMux(sfh, &hdr->mux);
    hdr->adxStm = sfhdr_FindStm(sfh, 0xBD, 0xBD);
    hdr->prv2Stm = sfhdr_FindStm(sfh, 0xBF, 0xBF);
    hdr->audioStm = sfhdr_FindStm(sfh, 0xC0, 0xDF);
    hdr->videoStm = sfhdr_FindStm(sfh, 0xE0, 0xEF);
    sfhdr_ReadAudio(sfh, hdr->audioStm, &hdr->audio);
    sfhdr_ReadVideo(sfh, hdr->videoStm, &hdr->video);
    hdr->valid = 1;
}

void sfhdr_ReadSys(SfhHn *sfh, SfdHdrInf *hdr) {
    hdr->bitRate = sfhdr_Get(sfh, SFH_AnlyHdrSiz);
    hdr->sysType = sfhdr_Get(sfh, SFH_AnlyPackType);
    hdr->numStm = sfhdr_Get(sfh, SFH_AnlyPketSizLen);
    if (hdr->numStm == -1) {
        hdr->numStm = 2;
    }
    hdr->totalSize = sfhdr_Get(sfh, SFH_AnlyPackSiz);
}

void sfhdr_ReadMux(SfhHn *sfh, SfdHdrMux *mux) {
    mux->kind[0] = sfhdr_Get(sfh, SFH_AnlyNumElemTot);
    mux->kind[1] = sfhdr_Get(sfh, SFH_AnlyNumElemAud);
    mux->kind[2] = sfhdr_Get(sfh, SFH_AnlyNumElemVid);
    mux->kind[3] = sfhdr_Get(sfh, SFH_AnlyNumElemPrv);
    mux->numFrm = sfhdr_Get(sfh, SFH_AnlyMaxPlyLenAud);
    mux->totalTime = sfhdr_Get(sfh, SFH_AnlyMaxPlyLenVid);
    mux->timeUnit = sfhdr_Get(sfh, SFH_AnlyMaxFrmNum);
}

/* The first stream id in [first, last] the header lists, or 0. */
int sfhdr_FindStm(SfhHn *sfh, int first, int last) {
    int exist;
    int id;

    for (id = first; id <= last; id++) {
        if (SFH_IsExistStmId(sfh, (unsigned char)id, &exist) != 0 && exist != 0) {
            return id;
        }
    }
    return 0;
}

void sfhdr_ReadAudio(SfhHn *sfh, int id, SfdHdrAudio *audio) {
    if (id != 0) {
        audio->codec = sfhdr_GetStm(sfh, id, SFH_AnlyElemCodecAud);
        audio->nch = sfhdr_GetStm(sfh, id, SFH_AnlyElemLayer);
        audio->bps = sfhdr_GetStm(sfh, id, SFH_AnlyElemChNum);
        audio->sfreq = sfhdr_GetStm(sfh, id, SFH_AnlyElemSmpHz);
    }
}

void sfhdr_ReadVideo(SfhHn *sfh, int id, SfdHdrVideo *video) {
    int avail;

    video->codec = sfhdr_GetStm(sfh, id, SFH_AnlyElemCodecVid);
    video->bitRate = sfhdr_GetStm(sfh, id, SFH_AnlyElemBitRate);
    if (SFH_AnlyElemPicSz(sfh, id & 0xFF, &video->width, &video->height) == 0) {
        video->width = -1;
        video->height = -1;
    }
    video->frameRate = sfhdr_GetStm(sfh, id, SFH_AnlyElemPicRate);
    if (SFH_IsEffFtrInf(sfh, id & 0xFF, &avail) == 0) {
        avail = 0;
    }
    video->avail = avail != 0;
    if (avail == 0) {
        return;
    }
    video->picType = sfhdr_GetStm(sfh, id, SFH_AnlyFtrColType);
    video->profile = sfhdr_GetStm(sfh, id, SFH_AnlyFtrPicType);
    video->flag0 = sfhdr_GetStm(sfh, id, SFH_AnlyFtrFixFlg);
    video->flag4 = sfhdr_GetStm(sfh, id, SFH_AnlyFtrShcFixFlg);
    video->chroma = sfhdr_GetStm(sfh, id, SFH_AnlyFtrExpand);
    video->zFirst = sfhdr_GetStm(sfh, id, SFH_AnlyFtrGopN);
    video->zSecond = sfhdr_GetStm(sfh, id, SFH_AnlyFtrGopM);
}

/* A header value, or -1 when the header does not give it. */
int sfhdr_Get(SfhHn *sfh, SfhGetFn get) {
    int value;

    if (get(sfh, &value) != 0) {
        return value;
    }
    return -1;
}

int sfhdr_GetStm(SfhHn *sfh, int id, SfhGetStmFn get) {
    int value;

    if (get(sfh, id, &value) == 0) {
        return -1;
    }
    return value;
}

void sfhdr_SetVideoInf(SfdHandle *hn) {
    SfdHdrMux *mux = &hn->hdr.mux;
    SfdVideoInf *video = &hn->video;

    video->audioBound = mux->kind[1];
    video->videoBound = mux->kind[2];
    video->f44 = mux->kind[3];
}

int sfd_GetKindTwo(void) {
    return 2;
}

/* The header's version times 100, or 0 before a header has been read. */
int sfd_GetStmVersion(SfdHandle *hn) {
    SfdHdrInf *hdr = &hn->hdr;

    if (hdr->valid == 0) {
        return 0;
    }
    return hdr->verMajor * 100 + hdr->verMinor;
}

int sfhdr_GetVideoPicType(SfdHandle *hn) {
    SfdHdrVideo *video = &hn->hdr.video;

    if (hn->hdr.valid == 0) {
        return -1;
    }
    if (video->avail == 0) {
        return -1;
    }
    return video->picType;
}
