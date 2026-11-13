/* SFH (CRI SFH/PS2EE Ver.1.19): reads the header sector of a Sofdec stream. A handle points at the
 * header in memory; the getters return its file information and, per stream id, the audio and video
 * stream descriptors. */

void *memset(void *dst, int value, unsigned int size);
int memcmp(const void *a, const void *b, unsigned int size);
char *strstr(const char *text, const char *pattern);

typedef struct SfhStr12 {
    char text[12];
} SfhStr12;

typedef struct SfhStr32 {
    char text[32];
} SfhStr32;

typedef struct SfhStr64 {
    char text[64];
} SfhStr64;

/* The magic and the header version: "SofdecStream" padded to 24 characters. */
typedef struct SfhMagic {
    char text[24];
    unsigned char major;
    unsigned char minor;
} SfhMagic;

typedef struct SfhSysInf {
    int bitRate;
    unsigned char sysType;
    char pad5[3];
    short nStm;
    char pad10[2];
    int totalSize;
} SfhSysInf;

typedef struct SfhMuxInf {
    unsigned char kind[4];
    int muxRate;      /* bytes per second; from header version 1.10 */
    int nFrm;
    int totalTime;
    int timeUnit;
    int extFirst;     /* from header version 2.25 */
    int extSecond;
} SfhMuxInf;

/* One 64-byte stream descriptor; `id` is the MPEG stream id it describes. */
typedef struct SfhStm {
    SfhStr12 name;
    SfhStr12 codecName;
    unsigned char id;
    char pad25[64 - 25];
} SfhStm;

typedef struct SfhAudioStm {
    SfhStr12 name;
    SfhStr12 codecName;
    unsigned char id;
    unsigned char codec;
    unsigned char layer;     /* MPEG audio layer; valid when codec is 1 */
    unsigned char chNum;     /* channel count */
    int smpHz;
    unsigned char avail;
} SfhAudioStm;

typedef struct SfhVideoStm {
    SfhStr12 name;
    SfhStr12 codecName;
    unsigned char id;
    unsigned char codec;
    unsigned short bitRate;  /* 0xFFFF: unknown */
    unsigned char size[3];   /* 12-bit width, 12-bit height */
    unsigned char frmRateCode;
    unsigned char avail;
    unsigned char picType;
    unsigned char profile;
    unsigned char flags;     /* bit 0, bit 4 */
    unsigned char chroma;
    unsigned char zFirst;    /* 64 and up: none */
    unsigned char zSecond;   /* 64 and up: none */
    unsigned char alpha;     /* from header version 2.10 */
} SfhVideoStm;

typedef struct SfhHdr {
    char pad0[32];
    SfhMagic magic;
    char pad58[6];
    SfhStr12 date;
    SfhStr12 time;
    char pad88[8];
    SfhStr32 creator;     /* "<tool> Ver.<major>.<minor>" */
    SfhSysInf sys;
    char pad144[32];
    SfhMuxInf mux;
    char pad204[20];
    SfhStr64 comment;
    char pad288[96];
    SfhStm stm[26];
} SfhHdr;

enum {
    SFH_STAT_FREE = 0,
    SFH_STAT_INVALID = -1,
    SFH_STAT_ANALYSED = 2
};

typedef struct SfhHn {
    int stat;
    SfhHdr *hdr;
    unsigned int size;
    int version;          /* major * 100 + minor */
} SfhHn;

typedef struct SfhPool {
    int maxHn;
    int nHn;
    SfhHn *hns;
} SfhPool;

enum {
    SFH_STM_AUDIO = 0xC0,
    SFH_STM_VIDEO = 0xE0,
    SFH_STM_PRIVATE = 0xBD
};

extern char sfh_ver_str[];
extern char sfh_magic[];
extern char sfh_ver_tag[];
extern char *sfh_verstr_ptr;
extern SfhPool sfh_pool;
extern int sfh_init_cnt;

void clearObjInf(SfhPool *pool);
void initObjInf(SfhPool *pool, int maxHn, SfhHn *hns);
void initSfhObj(SfhHn *hn);
void setHnCreate(SfhHn *hn, SfhHdr *hdr, unsigned int size);
void initLibWork(int count, SfhHn *hns);
int isFreeObj(SfhHn *hn);
int isEffectiveVer(SfhHn *hn);
int isEffectiveObj(SfhHn *hn);
SfhStm *searchStmId(SfhHdr *hdr, int id);
int SFH_AnlyHdrToolInf(SfhHn *hn, char *out);
int SFH_AnlyHdrToolVer(SfhHn *hn, int *major, int *minor);
int getToolVer(char *text, int *major, int *minor);
char *convAsciiToDigit(char *text, int *value);
void *getElemInfPtr(SfhHn *hn, int id);
int sfh_FrmRateCodeToRate(int code);
int isEnableAudFtr(int id, SfhAudioStm *stm);
int isEnableVidFtr(int id, SfhVideoStm *stm);
int chkStmId(int id);

char *SFH_GetVersionStr(void) {
    return sfh_ver_str;
}

int sfh_IsStatAnalysed(int stat) {
    return stat == SFH_STAT_ANALYSED;
}

void SFH_Init(int maxHn, SfhHn *hns) {
    char **verstr;

    if (sfh_init_cnt > 0) {
        return;
    }
    sfh_init_cnt++;
    /* matching construct: the result address is taken into a local before the call */
    verstr = &sfh_verstr_ptr;
    *verstr = SFH_GetVersionStr();
    initLibWork(maxHn, hns);
    initObjInf(&sfh_pool, maxHn, hns);
}

void SFH_Finish(void) {
    if (--sfh_init_cnt <= 0) {
        clearObjInf(&sfh_pool);
    }
}

SfhHn *SFH_Create(SfhHdr *hdr, unsigned int size) {
    SfhHn *hn = 0;
    int maxHn = sfh_pool.maxHn;
    int nHn = sfh_pool.nHn;
    SfhHn *hns = sfh_pool.hns;
    int i;

    if (nHn >= maxHn) {
        return 0;
    }
    for (i = 0; i < maxHn; i++) {
        hn = &hns[i];
        if (isFreeObj(hn)) {
            break;
        }
    }
    setHnCreate(hn, hdr, size);
    sfh_pool.nHn++;
    return hn;
}

void SFH_Destroy(SfhHn *hn) {
    initSfhObj(hn);
    sfh_pool.nHn--;
}

void clearObjInf(SfhPool *pool) {
    pool->maxHn = 0;
    pool->nHn = 0;
    pool->hns = 0;
}

void initObjInf(SfhPool *pool, int maxHn, SfhHn *hns) {
    pool->hns = hns;
    pool->maxHn = maxHn;
    pool->nHn = 0;
}

void initSfhObj(SfhHn *hn) {
    hn->stat = SFH_STAT_FREE;
    hn->hdr = 0;
    hn->size = 0;
    hn->version = 0;
}

void setHnCreate(SfhHn *hn, SfhHdr *hdr, unsigned int size) {
    hn->stat = 1;
    hn->hdr = hdr;
    hn->size = size;
}

void initLibWork(int count, SfhHn *hns) {
    int i;

    for (i = 0; i < count; i++) {
        initSfhObj(&hns[i]);
    }
}

int isFreeObj(SfhHn *hn) {
    return hn->stat == SFH_STAT_FREE;
}

/* Analysed, and a header version this library reads (1.07, or 1.10 and later). */
int isEffectiveVer(SfhHn *hn) {
    int ok = isEffectiveObj(hn);

    if (ok != 0) {
        if (hn->version == 107 || hn->version >= 110) {
            ok = 1;
        } else {
            ok = 0;
        }
    }
    return ok;
}

int isEffectiveObj(SfhHn *hn) {
    switch (hn->stat) {
    case SFH_STAT_INVALID:
    case SFH_STAT_FREE:
    case 1:
        return 0;
    }
    return 1;
}

int SFH_IsSfdHeader(SfhHn *hn, int *ok) {
    char *magic;
    int version[2];

    *ok = 0;
    magic = hn->hdr->magic.text;
    if (isFreeObj(hn) == 1) {
        return 0;
    }
    if (hn->size < 2048) {
        hn->stat = SFH_STAT_INVALID;
        return 0;
    }
    if (memcmp(magic, sfh_magic, 24) != 0) {
        hn->stat = SFH_STAT_INVALID;
        return 0;
    }
    hn->stat = SFH_STAT_ANALYSED;
    if (SFH_AnlyHdrToolVer(hn, &version[0], &version[1]) == 0) {
        return 0;
    }
    hn->version = version[0] * 100 + version[1];
    *ok = 1;
    return 1;
}

void SFH_IsExistStmId(SfhHn *hn, unsigned char id, int *exist) {
    SfhHdr *hdr;

    *exist = 0;
    hdr = hn->hdr;
    if (isEffectiveVer(hn) == 0) {
        return;
    }
    if (searchStmId(hdr, id) != 0) {
        *exist = 1;
    } else {
        *exist = 0;
    }
}

int SFH_IsEffFtrInf(SfhHn *hn, unsigned char id, int *avail) {
    void *stm;

    if (hn->version < 110) {
        return 0;
    }
    switch (chkStmId(id)) {
    case SFH_STM_AUDIO:
        stm = getElemInfPtr(hn, id);
        if (stm == 0) {
            return 0;
        }
        *avail = isEnableAudFtr(id, stm);
        return 1;
    case SFH_STM_VIDEO:
        stm = getElemInfPtr(hn, id);
        if (stm == 0) {
            return 0;
        }
        *avail = isEnableVidFtr(id, stm);
        return 1;
    }
    return 0;
}

SfhStm *searchStmId(SfhHdr *hdr, int id) {
    SfhStm *stm = &hdr->stm[0];
    SfhStm *found = 0;
    int stmId = stm->id;
    int i = 0;

    /* matching construct: manual — a goto loop: retail recomputes &stm[i] each pass (no
     * loop strength reduction) and loads the id at the end of the body, which a for/while loop does not give */
    goto test;
next:
    i++;
    if (i >= 26) {
        goto done;
    }
    stm = &hdr->stm[i];
    stmId = stm->id;
test:
    if (stmId != id) {
        goto next;
    }
    found = stm;
done:
    return found;
}

int SFH_AnlySfdFname(SfhHn *hn, char *out) {
    SfhStr12 *date = &hn->hdr->date;

    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    memset(out, 0, sizeof(SfhStr12) + 1);
    *(SfhStr12 *)out = *date;
    return 1;
}

int SFH_AnlySfdTimStmp(SfhHn *hn, char *out) {
    SfhHdr *hdr;

    *out = '\0';
    hdr = hn->hdr;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    memset(out, 0, sizeof(SfhStr12) + 1);
    *(SfhStr12 *)out = hdr->time;
    return 1;
}

int SFH_AnlyHdrToolInf(SfhHn *hn, char *out) {
    SfhStr32 *creator;

    *out = '\0';
    creator = &hn->hdr->creator;
    if (isEffectiveObj(hn) == 0) {
        return 0;
    }
    memset(out, 0, sizeof(SfhStr32) + 1);
    *(SfhStr32 *)out = *creator;
    return 1;
}

/* The later of the header's own version and the version in the creator string. */
int SFH_AnlyHdrToolVer(SfhHn *hn, int *major, int *minor) {
    char creator[48];
    int toolMajor, toolMinor;
    SfhMagic *magic;
    int hdrMajor, hdrMinor, ok;

    *major = 0;
    *minor = 0;
    magic = &hn->hdr->magic;
    ok = SFH_AnlyHdrToolInf(hn, creator);
    if (ok == 0) {
        return ok;
    }
    hdrMajor = magic->major;
    hdrMinor = magic->minor;
    ok = getToolVer(creator, &toolMajor, &toolMinor);
    if (ok == 0) {
        return ok;
    }
    if (hdrMajor * 100 + hdrMinor >= toolMajor * 100 + toolMinor) {
        *major = hdrMajor;
        *minor = hdrMinor;
    } else {
        *major = toolMajor;
        *minor = toolMinor;
    }
    return 1;
}

int SFH_AnalyHdrComment(SfhHn *hn, char *out) {
    SfhStr64 *comment;

    *out = '\0';
    comment = &hn->hdr->comment;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    memset(out, 0, sizeof(SfhStr64) + 1);
    *(SfhStr64 *)out = *comment;
    return 1;
}

int SFH_AnlyHdrSiz(SfhHn *hn, int *value) {
    SfhSysInf *sys;

    *value = 0;
    sys = &hn->hdr->sys;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    *value = sys->bitRate;
    return 1;
}

int SFH_AnlyPackType(SfhHn *hn, int *value) {
    SfhSysInf *sys;

    *value = -1;
    sys = &hn->hdr->sys;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    *value = sys->sysType;
    return 1;
}

int SFH_AnlyPketSizLen(SfhHn *hn, int *value) {
    SfhSysInf *sys;

    *value = 0;
    sys = &hn->hdr->sys;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    *value = sys->nStm;
    return 1;
}

int SFH_AnlyPackSiz(SfhHn *hn, int *value) {
    SfhSysInf *sys;

    *value = 0;
    sys = &hn->hdr->sys;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    *value = sys->totalSize;
    return 1;
}

/* Finds the sfh_ver_tag marker ("Ver.") in `text` and reads the "major.minor" after it. */
int getToolVer(char *text, int *major, int *minor) {
    char *found = strstr(text, sfh_ver_tag);

    if (found == 0) {
        return 0;
    }
    convAsciiToDigit(convAsciiToDigit(found + 4, major) + 1, minor);
    return 1;
}

/* Reads a run of decimal digits and returns the position after them. */
char *convAsciiToDigit(char *text, int *value) {
    char c = *text;
    int number = 0;

    while (c != '.' && c != ' ' && c != '\0' && (unsigned int)(c - '0') < 10) {
        text++;
        number = number * 10 + c - '0';
        c = *text;
    }
    *value = number;
    return text;
}

int SFH_AnlyNumElemTot(SfhHn *hn, int *value) {
    SfhMuxInf *mux;

    *value = 0;
    mux = &hn->hdr->mux;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    *value = mux->kind[0];
    return 1;
}

int SFH_AnlyNumElemAud(SfhHn *hn, int *value) {
    SfhMuxInf *mux;

    *value = 0;
    mux = &hn->hdr->mux;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    *value = mux->kind[1];
    return 1;
}

int SFH_AnlyNumElemVid(SfhHn *hn, int *value) {
    SfhMuxInf *mux;

    *value = 0;
    mux = &hn->hdr->mux;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    *value = mux->kind[2];
    return 1;
}

int SFH_AnlyNumElemPrv(SfhHn *hn, int *value) {
    SfhMuxInf *mux;

    *value = 0;
    mux = &hn->hdr->mux;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    *value = mux->kind[3];
    return 1;
}

int SFH_AnlyByteRate(SfhHn *hn, int *value) {
    SfhMuxInf *mux;

    *value = 0;
    mux = &hn->hdr->mux;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    if (hn->version < 110) {
        return 0;
    }
    *value = mux->muxRate;
    return 1;
}

int SFH_AnlyMaxPlyLenAud(SfhHn *hn, int *value) {
    SfhMuxInf *mux;

    *value = 0;
    mux = &hn->hdr->mux;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    *value = mux->nFrm;
    return 1;
}

int SFH_AnlyMaxPlyLenVid(SfhHn *hn, int *value) {
    SfhMuxInf *mux;

    *value = 0;
    mux = &hn->hdr->mux;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    *value = mux->totalTime;
    return 1;
}

int SFH_AnlyMaxFrmNum(SfhHn *hn, int *value) {
    SfhMuxInf *mux;

    *value = 0;
    mux = &hn->hdr->mux;
    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    *value = mux->timeUnit;
    return 1;
}

int SFH_AnlyMaxPicSiz(SfhHn *hn, int *value) {
    SfhMuxInf *mux;

    *value = 0;
    mux = &hn->hdr->mux;
    if (hn->version < 225) {
        return 0;
    }
    *value = mux->extFirst;
    return 1;
}

int SFH_AnlyAvrPicSiz(SfhHn *hn, int *value) {
    SfhMuxInf *mux;

    *value = 0;
    mux = &hn->hdr->mux;
    if (hn->version < 225) {
        return 0;
    }
    *value = mux->extSecond;
    return 1;
}

int SFH_AnlyElemFname(SfhHn *hn, unsigned char id, char *out) {
    SfhStm *stm;

    *out = '\0';
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    memset(out, 0, sizeof(SfhStr12) + 1);
    *(SfhStr12 *)out = stm->name;
    return 1;
}

int SFH_AnlyElemTimStmp(SfhHn *hn, unsigned char id, char *out) {
    SfhStm *stm;

    *out = '\0';
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    memset(out, 0, sizeof(SfhStr12) + 1);
    *(SfhStr12 *)out = stm->codecName;
    return 1;
}

void *getElemInfPtr(SfhHn *hn, int id) {
    SfhHdr *hdr = hn->hdr;

    if (isEffectiveVer(hn) == 0) {
        return 0;
    }
    return searchStmId(hdr, id);
}

int SFH_AnlyElemCodecAud(SfhHn *hn, unsigned char id, int *value) {
    SfhAudioStm *stm;

    *value = -1;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (chkStmId(id) != SFH_STM_AUDIO) {
        return 0;
    }
    *value = stm->codec;
    return 1;
}

int SFH_AnlyElemLayer(SfhHn *hn, unsigned char id, int *value) {
    SfhAudioStm *stm;

    *value = 0;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (chkStmId(id) != SFH_STM_AUDIO) {
        return 0;
    }
    if (stm->codec != 1) {
        return 0;
    }
    *value = stm->layer;
    return 1;
}

int SFH_AnlyElemChNum(SfhHn *hn, unsigned char id, int *value) {
    SfhAudioStm *stm;

    *value = 0;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (chkStmId(id) != SFH_STM_AUDIO) {
        return 0;
    }
    *value = stm->chNum;
    return 1;
}

int SFH_AnlyElemSmpHz(SfhHn *hn, unsigned char id, int *value) {
    SfhAudioStm *stm;

    *value = 0;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (chkStmId(id) != SFH_STM_AUDIO) {
        return 0;
    }
    *value = stm->smpHz;
    return 1;
}

int SFH_AnlyElemCodecVid(SfhHn *hn, unsigned char id, int *value) {
    SfhVideoStm *stm;

    *value = -1;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (chkStmId(id) != SFH_STM_VIDEO) {
        return 0;
    }
    *value = stm->codec;
    return 1;
}

int SFH_AnlyElemBitRate(SfhHn *hn, unsigned char id, int *value) {
    SfhVideoStm *stm;
    unsigned short bitRate;

    *value = 0;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (chkStmId(id) != SFH_STM_VIDEO) {
        return 0;
    }
    bitRate = stm->bitRate;
    *value = bitRate == 0xFFFF ? 0 : bitRate;
    return 1;
}

int SFH_AnlyElemPicSz(SfhHn *hn, unsigned char id, int *width, int *height) {
    SfhVideoStm *stm;
    unsigned char *size;

    *width = 0;
    *height = 0;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (chkStmId(id) != SFH_STM_VIDEO) {
        return 0;
    }
    size = stm->size;
    *width = size[0];
    *width = (*width << 4) | (size[1] >> 4);
    *height = size[1];
    *height = ((*height << 8) | size[2]) & 0xFFF;
    return 1;
}

int SFH_AnlyElemPicRate(SfhHn *hn, unsigned char id, int *value) {
    SfhVideoStm *stm;

    *value = 0;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (chkStmId(id) != SFH_STM_VIDEO) {
        return 0;
    }
    *value = sfh_FrmRateCodeToRate(stm->frmRateCode);
    return 1;
}

int SFH_AnlyFtrColType(SfhHn *hn, unsigned char id, int *value) {
    SfhVideoStm *stm;

    *value = -1;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (isEnableVidFtr(id, stm) == 0) {
        return 0;
    }
    *value = stm->picType;
    return 1;
}

int SFH_AnlyFtrPicType(SfhHn *hn, unsigned char id, int *value) {
    SfhVideoStm *stm;

    *value = -1;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (isEnableVidFtr(id, stm) == 0) {
        return 0;
    }
    *value = stm->profile;
    return 1;
}

int SFH_AnlyFtrFixFlg(SfhHn *hn, unsigned char id, int *value) {
    SfhVideoStm *stm;

    *value = 0;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (isEnableVidFtr(id, stm) == 0) {
        return 0;
    }
    *value = stm->flags & 1;
    return 1;
}

int SFH_AnlyFtrShcFixFlg(SfhHn *hn, unsigned char id, int *value) {
    SfhVideoStm *stm;
    int flags;

    *value = 0;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (isEnableVidFtr(id, stm) == 0) {
        return 0;
    }
    flags = stm->flags & 0x10;
    *value = flags != 0;
    return 1;
}

int SFH_AnlyFtrExpand(SfhHn *hn, unsigned char id, int *value) {
    SfhVideoStm *stm;

    *value = 0;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (isEnableVidFtr(id, stm) == 0) {
        return 0;
    }
    *value = stm->chroma;
    return 1;
}

int SFH_AnlyFtrGopN(SfhHn *hn, unsigned char id, int *value) {
    SfhVideoStm *stm;
    int z;

    *value = -1;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (isEnableVidFtr(id, stm) == 0) {
        return 0;
    }
    z = stm->zFirst;
    *value = z;
    if (z >= 64) {
        *value = -1;
    }
    return 1;
}

int SFH_AnlyFtrGopM(SfhHn *hn, unsigned char id, int *value) {
    SfhVideoStm *stm;
    int z;

    *value = -1;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (isEnableVidFtr(id, stm) == 0) {
        return 0;
    }
    z = stm->zSecond;
    *value = z;
    if (z >= 64) {
        *value = -1;
    }
    return 1;
}

int SFH_AnlyFtrFxType(SfhHn *hn, unsigned char id, int *value) {
    SfhVideoStm *stm;

    *value = -1;
    stm = getElemInfPtr(hn, id);
    if (stm == 0) {
        return 0;
    }
    if (isEnableVidFtr(id, stm) == 0) {
        return 0;
    }
    if (hn->version < 210) {
        return 0;
    }
    *value = stm->alpha;
    return 1;
}

/* MPEG-2 frame_rate_code to frames per 1000 seconds. */
int sfh_FrmRateCodeToRate(int code) {
    switch (code) {
    case 1: return 23976;
    case 2: return 24000;
    case 3: return 25000;
    case 4: return 29970;
    case 5: return 30000;
    case 6: return 50000;
    case 7: return 59940;
    case 8: return 60000;
    }
    return 0;
}

int isEnableAudFtr(int id, SfhAudioStm *stm) {
    unsigned char avail;

    if (chkStmId(id) != SFH_STM_AUDIO) {
        return 0;
    }
    avail = stm->avail;
    /* matching construct: manual — the range-then-nonzero ternary (avail == 1) is the shape that gives retail's sltu/sltiu/movz */
    return (avail < 2) ? (avail != 0) : 0;
}

int isEnableVidFtr(int id, SfhVideoStm *stm) {
    unsigned char avail;

    if (chkStmId(id) != SFH_STM_VIDEO) {
        return 0;
    }
    avail = stm->avail;
    /* matching construct: manual — the range-then-nonzero ternary (avail == 1) is the shape that gives retail's sltu/sltiu/movz */
    return (avail < 2) ? (avail != 0) : 0;
}

/* Audio streams 0xC0-0xDF, video streams 0xE0-0xEF, private streams 0xBD and 0xBF. */
int chkStmId(int id) {
    if ((unsigned int)(id - 0xC0) < 32) {
        return SFH_STM_AUDIO;
    }
    if ((unsigned int)(id - 0xE0) < 16) {
        return SFH_STM_VIDEO;
    }
    if (id == 0xBD || id == 0xBF) {
        return SFH_STM_PRIVATE;
    }
    return 0;
}
