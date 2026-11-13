#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"

extern "C" int igObject_GetAllocator(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" igObject *beBaseInfoDataList_Create(...);
extern "C" beCriSndf *beCriSndf_Create(...);
extern "C" beBaseInfoRamTimer *beBaseInfoRamTimer_Create(...);
extern "C" igAdxAudio *igAdxAudio_Create(...);
extern "C" int igAdxAudio_Initialize(igAdxAudio *audio, int maxChannels, int type, int maxStreams, int maxFrequency);
extern "C" int igAdxAudio_CreateHandle(igAdxAudio *audio, int maxChannels, int type, int maxStreams, int maxFrequency,
                                       int initialize);
extern "C" int igAdxAudio_StartMemory(igAdxAudio *audio, int data, int size);
extern "C" int igAdxAudio_StartFile(igAdxAudio *audio, int name);
extern "C" int igAdxAudio_Stop(igAdxAudio *audio);
extern "C" void igAdxAudio_Pause(igAdxAudio *audio, int pause);
extern "C" int igAdxAudio_GetPauseState(igAdxAudio *audio);
extern "C" int igAdxAudio_Shutdown(igAdxAudio *audio);
extern "C" void igAdxAudio_SetOutVolume(igAdxAudio *audio, int volume);
/* Both read only the handle; retail calls them with the voice type and the ADX-file flag left in the
 * argument registers. */
extern "C" int igAdxAudio_GetOutVolume(igAdxAudio *audio, int, bool);
extern "C" unsigned int igAdxAudio_GetStatus(igAdxAudio *audio, bool);
extern "C" int SNDF_SeqCommand(int command, unsigned char requestId, int argument);
extern "C" long long __fixsfdi(float);
extern "C" float __floatdisf(long long);
extern "C" int igNamedObject_SetName(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" beBaseInfoRamTimer *igProperty_FindByName(...);
extern "C" void List_RemoveWordAt(...);
extern "C" int List_Reserve(...);
extern "C" void *igInsightCore_FindManager(...);
extern "C" void beMessenger_RegisterReceiver(int messenger, int receiver, char *name, int, int);
extern "C" bePadData *bePadManager_GetPadForPlayer(int padManager, int player);
extern "C" int igObject_IsKindOf(void *object, int metaObject);
extern "C" int beLua__RunNamedChunk(int lua, int name, int);
extern "C" int strcmp(int *, int *);
extern "C" int StringPool_Allocate(int);
extern "C" int StringPool_Construct(int);
extern "C" int StringPool_Intern(int, int);
extern "C" void StringChunk_ReleaseHeader(int owner, void *header);
extern "C" int kIGMemoryPoolHandleUser0[4];
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" int g_propertyNameField[4];
extern "C" int emptyString[4];
extern "C" int g_stringPool[4];
extern "C" int g_beBaseInfoRamTimer_metaObject[4];
extern "C" int g_igMovieManager_metaObject[4];
extern "C" int g_bePadManager_metaObject[4];
extern "C" int g_beMovieInfoData_metaObject[4];
extern "C" int g_beLua_metaObject[4];
extern "C" int g_beMovieInfo_metaObject[4];
extern "C" int g_beMovie_metaObject[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" char playSfp_REQUESTID[], playSfp_SNDF_SEQ_SET[], playSfp_SNDF_SEQ_PLAY[];
extern "C" char stop_REQUESTID[], stop_SNDF_SEQ_GETSTATUS[], stop_SNDF_SEQ_STOP[];
extern "C" char setVolume_REQUESTID[], setVolume_SNDF_SEQ_GETSTATUS[], setVolume_SNDF_SEQ_VOLUME[];
extern "C" char getStatus_REQUESTID[], getStatus_SNDF_SEQ_GETSTATUS[];
extern "C" char MOVIE[];
/* 60-step fade curves: the rising one starts at 0.04, the falling one at 0.96. */
extern "C" float g_fadeInCurve[];
extern "C" float g_fadeOutCurve[];

/* beCriAudio::_audioType: an ADX stream played from a file or from memory, or a sound-bank voice. */
enum beCriAudioType { kAudioAdxFile = 1, kAudioAdxMemory = 2, kAudioSndf = 3 };
/* The sound-bank sequence commands, named by the error strings of the calls that send them. */
enum SndfSeqCommand { kSeqSet = 1, kSeqPlay = 2, kSeqStop = 3, kSeqVolume = 4, kSeqGetStatus = 7 };
/* An ADX level in 0.1 dB that means silence, and "no level saved" in _errVolume. */
enum { kSilentVolume = -999 };

extern "C" int beCriAudio_Setup(beCriAudio *self, int channels);
extern "C" void beCriAudio_Release(beCriAudio *self);
extern "C" int beCriAudio_PlayFile(beCriAudio *self, int name);
extern "C" int beCriAudio_PlayMemory(beCriAudio *self, int data, int size);
extern "C" int beCriAudio_PlaySfp(beCriAudio *self, int requestId, long long sequence);
extern "C" void beCriAudio_Stop(beCriAudio *self);
extern "C" void beCriAudio_SetVolume(beCriAudio *self, int volume);
extern "C" int beCriAudio_GetStatus(beCriAudio *self);
extern "C" void beCriAudio_Pause(beCriAudio *self, unsigned char pause);
extern "C" int beCriAudio_IsPaused(beCriAudio *self);
extern "C" void beCriAudio_Suspend(beCriAudio *self, int);
extern "C" void beCriAudio_Resume(beCriAudio *self);
extern "C" void beCriAudio_ReportError(beCriAudio *self, int code, char *where);
extern "C" int beCriVolume_StartFade(beCriVolume *self, int baseVolume, float from, float to, float frames);
extern "C" float beCriVolume_StepFade(beCriVolume *self);
extern "C" int beCriVolume_StepAdxLevel(beCriVolume *self, int baseVolume);
extern "C" int beCriVolume_StepSndfLevel(beCriVolume *self);
extern "C" void beBaseInfoRam_StartTimer(beBaseInfoRam *self, int name, long long endTime);
extern "C" int beBaseInfoRam_HasTimer(beBaseInfoRam *self, int name);
extern "C" int beBaseInfoRam_IsTimerExpired(beBaseInfoRam *self, int name);
extern "C" long long beBaseInfoRam_GetTimerElapsed(beBaseInfoRam *self, int name);
extern "C" float beBaseInfoRam_GetTimerFrameDelta(beBaseInfoRam *self, int name);
extern "C" void beBaseInfoRam_SetTimerScale(beBaseInfoRam *self, int name, float scale);
extern "C" void beBaseInfoRam_SetAllTimerScales(beBaseInfoRam *self, float scale);
extern "C" void beBaseInfoRam_RemoveTimer(beBaseInfoRam *self, char *name);
extern "C" void beBaseInfoRam_RemoveAllTimers(beBaseInfoRam *self);
extern "C" void Gap__Bec__beMovie__vfunc_32(beMovie *self);
extern "C" void Gap__Bec__beMovie__vfunc_29(beMovie *self, int receiver, char *, int, int);
extern "C" int Gap__Bec__beMovie__vfunc_30(void);
extern "C" void Gap__Bec__beMovie__vfunc_31(beMovie *self, beBaseInfoRam *ram);
extern "C" int Gap__Bec__beMovie__vfunc_20(void);

static inline bool isSndfVoice(beCriAudio *s) { return s->_sndf != 0 && s->_audioType == kAudioSndf; }
static inline bool isAdxFileVoice(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == kAudioAdxFile; }
static inline bool isAdxMemoryVoice(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == kAudioAdxMemory; }

static inline igAdxAudio *adxOf(beCriAudio *s) { return (igAdxAudio *)s->_adxt; }
static inline beCriSndf *sndfOf(beCriAudio *s) { return (beCriSndf *)s->_sndf; }

int beCriAudio_Setup(beCriAudio *self, int channels) {
    if (channels < 0) {
        int allocator = igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
        igRelease((igObject *)self->_sndf);
        self->_sndf = (int)beCriSndf_Create(allocator);
        igRelease((igObject *)self->_adxt);
        self->_adxt = 0;
        self->_audioType = kAudioSndf;
    } else {
        int allocator = igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
        igRelease((igObject *)self->_adxt);
        self->_adxt = (int)igAdxAudio_Create(allocator);
        igRelease((igObject *)self->_sndf);
        self->_sndf = 0;
        self->_audioType = kAudioAdxFile;
        int frequency = (channels == 2) ? 48000 : 24000;
        if (igAdxAudio_Initialize(adxOf(self), channels, 1, 2, frequency) == 0) return 0;
        if (igAdxAudio_CreateHandle(adxOf(self), channels, 1, 2, frequency, 0) == 0) return 0;
    }
    self->_errVolume = kSilentVolume;
    return 1;
}

void beCriAudio_Release(beCriAudio *self) {
    igRelease((igObject *)self->_sndf);
    self->_sndf = 0;
    if (self->_adxt != 0) {
        igAdxAudio_Shutdown(adxOf(self));
    }
    igRelease((igObject *)self->_adxt);
    self->_adxt = 0;
}

int beCriAudio_PlayFile(beCriAudio *self, int name) {
    unsigned char ready = 0;
    igAdxAudio *adxt = adxOf(self);
    if (adxt != 0) {
        if (self->_audioType == kAudioAdxFile) ready = 1;
    }
    if (ready) {
        igAdxAudio_Stop(adxt);
        return igAdxAudio_StartFile(adxOf(self), name);
    }
    return 0;
}

int beCriAudio_PlayMemory(beCriAudio *self, int data, int size) {
    bool ready = false;
    igAdxAudio *adxt = (igAdxAudio *)self->_adxt;
    if (adxt != 0) {
        if (self->_audioType == kAudioAdxMemory) ready = true;
    }
    if (ready) {
        int started = igAdxAudio_StartMemory(adxt, data, size);
        return started;
    }
    return 0;
}

int beCriAudio_PlaySfp(beCriAudio *self, int requestId, long long sequence) {
    int ready = self->_sndf != 0;
    if (ready) ready = self->_audioType == kAudioSndf;
    if (ready) {
        if (requestId < 1 || requestId > 255) {
            beCriAudio_ReportError(self, requestId, playSfp_REQUESTID);
            return 0;
        }
        if (SNDF_SeqCommand(kSeqSet, requestId, (int)sequence)) {
            beCriAudio_ReportError(self, requestId, playSfp_SNDF_SEQ_SET);
            return 0;
        }
        if (SNDF_SeqCommand(kSeqPlay, requestId, 0)) {
            beCriAudio_ReportError(self, requestId, playSfp_SNDF_SEQ_PLAY);
            return 0;
        }
        sndfOf(self)->_req = requestId;
        sndfOf(self)->_seq = sequence;
        sndfOf(self)->_isPlaying = 0;
        return 1;
    }
    return 0;
}

void beCriAudio_Stop(beCriAudio *self) {
    if (isSndfVoice(self)) {
        int requestId = sndfOf(self)->_req;
        if (requestId != 0) {
            if (requestId <= 0 || requestId > 255) {
                beCriAudio_ReportError(self, requestId, stop_REQUESTID);
            } else {
                int status = SNDF_SeqCommand(kSeqGetStatus, requestId & 0xFF, 0);
                if (status < 0) {
                    beCriAudio_ReportError(self, status, stop_SNDF_SEQ_GETSTATUS);
                    return;
                }
                if (status > 0) {
                    status = SNDF_SeqCommand(kSeqStop, sndfOf(self)->_req & 0xFF, 0);
                    if (status < 0) beCriAudio_ReportError(self, status, stop_SNDF_SEQ_STOP);
                }
                sndfOf(self)->_req = 0;
                sndfOf(self)->_seq = 0;
            }
        }
    } else {
        bool adxFile = isAdxFileVoice(self);
        if (adxFile || isAdxMemoryVoice(self)) {
            igAdxAudio_SetOutVolume(adxOf(self), kSilentVolume);
            igAdxAudio_Pause(adxOf(self), 1);
            igAdxAudio_Stop(adxOf(self));
        }
    }
}

void beCriAudio_SetVolume(beCriAudio *self, int volume) {
    if (isSndfVoice(self)) {
        int requestId = sndfOf(self)->_req;
        if (requestId != 0) {
            if (requestId <= 0 || requestId > 255) {
                beCriAudio_ReportError(self, requestId, setVolume_REQUESTID);
            } else {
                int status = SNDF_SeqCommand(kSeqGetStatus, requestId & 0xFF, 0);
                if (status < 0) {
                    beCriAudio_ReportError(self, status, setVolume_SNDF_SEQ_GETSTATUS);
                    return;
                }
                status = SNDF_SeqCommand(kSeqVolume, sndfOf(self)->_req & 0xFF, volume);
                if (status < 0) beCriAudio_ReportError(self, status, setVolume_SNDF_SEQ_VOLUME);
            }
        }
    } else {
        bool adxFile = isAdxFileVoice(self);
        if (adxFile || isAdxMemoryVoice(self)) igAdxAudio_SetOutVolume(adxOf(self), volume);
    }
}

/* 1 while the voice plays, 0 once it has finished, -1 on an error. */
int beCriAudio_GetStatus(beCriAudio *self) {
    if (isSndfVoice(self)) {
        int requestId = sndfOf(self)->_req;
        if (requestId == 0) return 0;
        if (requestId < 1 || requestId > 255) {
            beCriAudio_ReportError(self, requestId, getStatus_REQUESTID);
            return -1;
        }
        int status = SNDF_SeqCommand(kSeqGetStatus, requestId & 0xff, 0);
        if (status < 0) {
            beCriAudio_ReportError(self, status, getStatus_SNDF_SEQ_GETSTATUS);
            return -1;
        }
        switch (status) {
        case 1: case 2:
            sndfOf(self)->_isPlaying = 1;
            return 1;
        default:
            return sndfOf(self)->_isPlaying == 0;
        }
    }
    bool adxFile = isAdxFileVoice(self);
    if (adxFile || isAdxMemoryVoice(self)) {
        switch (igAdxAudio_GetStatus(adxOf(self), adxFile)) {
        case 0: return 0;
        case 1: case 2: case 3: case 4: return 1;
        case 5: return 0;
        case 6: default: return -1;
        }
    }
    return -1;
}

void beCriAudio_Pause(beCriAudio *self, unsigned char pause) {
    if (!isSndfVoice(self)) {
        bool adxFile = isAdxFileVoice(self);
        if (adxFile || isAdxMemoryVoice(self)) igAdxAudio_Pause(adxOf(self), pause);
    }
}

int beCriAudio_IsPaused(beCriAudio *self) {
    bool adxFile;
    if (isSndfVoice(self)) {
        return 0;
    }
    adxFile = isAdxFileVoice(self);
    if (adxFile || isAdxMemoryVoice(self)) {
        return igAdxAudio_GetPauseState(adxOf(self));
    }
    return 0;
}

/* Mutes and pauses a playing ADX voice, saving its level in _errVolume for beCriAudio_Resume. */
void beCriAudio_Suspend(beCriAudio *self, int unused) {
    bool adxFile;
    int volume;
    int type;
    if (isSndfVoice(self)) {
        self->_errVolume = 127;
        return;
    }
    type = unused;
    adxFile = false;
    if (self->_adxt != 0) {
        type = self->_audioType;
        if (type == kAudioAdxFile) {
            adxFile = true;
        }
    }
    if (adxFile || isAdxMemoryVoice(self)) {
        volume = igAdxAudio_GetOutVolume(adxOf(self), type, adxFile);
        if (volume != kSilentVolume) {
            if (igAdxAudio_GetPauseState(adxOf(self)) == 0) {
                self->_errVolume = volume;
                igAdxAudio_SetOutVolume(adxOf(self), kSilentVolume);
                igAdxAudio_Pause(adxOf(self), 1);
            }
        } else {
            self->_errVolume = kSilentVolume;
        }
    }
}

void beCriAudio_Resume(beCriAudio *self) {
    bool adxFile;
    if (isSndfVoice(self)) {
        self->_errVolume = kSilentVolume;
        return;
    }
    adxFile = isAdxFileVoice(self);
    if (adxFile || isAdxMemoryVoice(self)) {
        if (self->_errVolume != kSilentVolume) {
            igAdxAudio_SetOutVolume(adxOf(self), self->_errVolume);
            igAdxAudio_Pause(adxOf(self), 0);
            self->_errVolume = kSilentVolume;
        }
    }
}

void beCriAudio_ReportError(beCriAudio *, int, char *)
{
}

/* A float's sign bit, cleared to take its magnitude. */
typedef union FloatBits { float f; struct { unsigned magnitude : 31; unsigned sign : 1; } bits; } FloatBits;

/* Arms a fade from `from` to `to` over `frames` frames along the matching curve and returns the
 * starting ADX level: the base volume plus the curve factor scaled to 0.1 dB below full level. */
int beCriVolume_StartFade(beCriVolume *self, int baseVolume, float from, float to, float frames) {
    FloatBits level;
    int first, last, i, j, first2, last2, m, k;
    self->_isExec = 3;
    self->_sta = from;
    self->_end = to;
    if (from < to) {
        first = -1; last = -1;
        for (i = 0; i < 60; i++) {
            if (from <= g_fadeInCurve[i]) { first = i; break; }
        }
        for (j = 59; j > -1; j--) {
            if (to >= g_fadeInCurve[j]) { last = j; break; }
        }
        self->_current = (float)first;
        self->_unit = (float)(last - first) / frames;
        level.f = -210.0f * g_fadeInCurve[(int)self->_current];
        level.bits.sign = 0;
        return baseVolume + ((int)level.f - 210 + self->_max);
    }
    first2 = -1; last2 = -1;
    for (m = 0; m < 60; m++) {
        if (from >= g_fadeOutCurve[m]) { first2 = m; break; }
    }
    for (k = 59; k > -1; k--) {
        if (to <= g_fadeOutCurve[k]) { last2 = k; break; }
    }
    self->_current = (float)first2;
    self->_unit = (float)(last2 - first2) / frames;
    level.f = -210.0f * g_fadeOutCurve[(int)self->_current];
    level.bits.sign = 0;
    return baseVolume + ((int)level.f - 210 + self->_max);
}

/* Advances the fade by one frame and returns its curve factor. */
float beCriVolume_StepFade(beCriVolume *self) {
    float position;
    if (self->_sta < self->_end) {
        position = self->_current + self->_unit;
        self->_current = position;
        return g_fadeInCurve[(int)position];
    }
    position = self->_current + self->_unit;
    self->_current = position;
    return g_fadeOutCurve[(int)position];
}

/* The sign bit of the two scaled factors is cleared through a byte bit-field union. */
typedef union FloatBytes { float f; struct { unsigned char b0, b1, b2; unsigned char high : 7; unsigned char sign : 1; } bytes; } FloatBytes;

/* The next fade level of an ADX voice in 0.1 dB; the fade ends on reaching its target, and a fade
 * to 0 ends in silence. */
int beCriVolume_StepAdxLevel(beCriVolume *self, int baseVolume) {
    float from = self->_sta;
    float to = self->_end;
    FloatBytes current, target;
    int level, targetLevel;
    current.f = -210.0f * beCriVolume_StepFade(self);
    current.bytes.sign = 0;
    level = baseVolume + ((int)current.f - 210 + *(int *)&self->_max);
    target.f = -210.0f * to;
    target.bytes.sign = 0;
    targetLevel = baseVolume + ((int)target.f - 210 + self->_max);
    if (!(from <= to)) {
        if (level <= targetLevel) {
            self->_isExec = 0;
            if (to == 0.0f) {
                return kSilentVolume;
            }
        }
    } else {
        if (level >= targetLevel) {
            self->_isExec = 0;
        }
    }
    return level;
}

/* The next fade level of a sound-bank voice on its 0..127 scale. */
int beCriVolume_StepSndfLevel(beCriVolume *self) {
    float to;
    int level;

    to = self->_end;
    level = (int)(127.0f * beCriVolume_StepFade(self));
    if (level <= (int)(127.0f * to)) {
        self->_isExec = 0;
        if (to == 0.0f) {
            level = 0;
        }
    }
    return level;
}

/* A timer is a beBaseInfoRamTimer named in the ram's _dataList. Its time is the world clock (ns)
 * with the bits above 18 scaled by _timeScale, plus _timeBias. */

/* The fresh timer, released when the start leaves its scope. */
struct TimerHolder {
    igObject *p;
    TimerHolder(void *timer) { p = (igObject *)timer; }
    ~TimerHolder() { igRelease(p); }
};

/* Creates the ram's timer list on first use. */
static inline void ensureTimerList(beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        int allocator = igObject_GetAllocator(ram);
        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(allocator));
        igObject *list = created.p;
        if (list != 0) list->_refCount = list->_refCount + 1;
        igRelease((igObject *)ram->_dataList);
        ram->_dataList = (int)list;
    }
}

static inline long long worldTimeOf(beBaseInfoRam *ram) {
    return ((igInsightCore *)((beBaseInfoManager *)ram->_parentManager)->_insight)->_worldTime;
}

void beBaseInfoRam_StartTimer(beBaseInfoRam *self, int name, long long endTime) {
    beBaseInfoRamTimer *timer;
    long long now;
    unsigned ticks;
    float scaled;

    ensureTimerList(self);
    timer = igProperty_FindByName(self->_dataList, g_propertyNameField[0], name);
    if (timer == 0) {
        int allocator = igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        TimerHolder created(beBaseInfoRamTimer_Create(allocator));
        igNamedObject_SetName(created.p, name);
        if (self->_dataList == 0) {
            int listAllocator = igObject_GetAllocator(self);
            listAllocator = g_useOwnerAllocator ? listAllocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
            igSmartPointer<igObject> list(beBaseInfoDataList_Create(listAllocator));
            igObject *retained = list.p;
            if (retained != 0) retained->_refCount = retained->_refCount + 1;
            igRelease((igObject *)self->_dataList);
            self->_dataList = (int)retained;
        }
        ObjectList_AppendRetained(self->_dataList, created.p);
        timer = (beBaseInfoRamTimer *)created.p;
    }
    now = worldTimeOf(self);
    ticks = (unsigned)(now >> 0x12);
    scaled = (float)ticks;
    scaled = scaled * timer->_timeScale;
    timer->_timeBias = -(__fixsfdi(scaled) << 0x12);
    timer->_svWorldTime = now;
    timer->_keikaFrame = 1.0f;
    timer->_endTime = endTime;
}

int beBaseInfoRam_HasTimer(beBaseInfoRam *self, int name) {
    ensureTimerList(self);
    return igProperty_FindByName(self->_dataList, g_propertyNameField[0], name) != 0;
}

int beBaseInfoRam_IsTimerExpired(beBaseInfoRam *self, int name) {
    beBaseInfoRamTimer *timer;
    long long endTime;
    ensureTimerList(self);
    timer = igProperty_FindByName(self->_dataList, g_propertyNameField[0], name);
    if (timer == 0) {
        return 1;
    }
    endTime = timer->_endTime;
    return endTime < beBaseInfoRam_GetTimerElapsed(self, name);
}

long long beBaseInfoRam_GetTimerElapsed(beBaseInfoRam *self, int name) {
    beBaseInfoRamTimer *timer;
    ensureTimerList(self);
    timer = igProperty_FindByName(self->_dataList, g_propertyNameField[0], name);
    int ticks = (int)(worldTimeOf(self) >> 0x12);
    float scaled = (float)(unsigned int)ticks;
    scaled = scaled * timer->_timeScale;
    long long scaledTicks = __fixsfdi(scaled);
    return (scaledTicks << 0x12) + timer->_timeBias;
}

/* Frames (1/60 s) the timer advanced since the previous world frame, at most 3; computed once per
 * world frame. */
float beBaseInfoRam_GetTimerFrameDelta(beBaseInfoRam *self, int name) {
    beBaseInfoRamTimer *timer;
    long long now;
    long long time;
    float frames;
    ensureTimerList(self);
    timer = igProperty_FindByName(self->_dataList, g_propertyNameField[0], name);
    now = worldTimeOf(self);
    if (now != timer->_svWorldTime) {
        time = beBaseInfoRam_GetTimerElapsed(self, name);
        long long elapsed = time - timer->_svBeforTime;
        if (elapsed != 0) {
            frames = __floatdisf(elapsed) / 1.6666667e7f;
            if (!(frames <= 3.0f)) {
                frames = 3.0f;
            }
            timer->_keikaFrame = frames;
            timer->_svBeforTime = time;
        } else {
            timer->_keikaFrame = 0.0f;
        }
        timer->_svWorldTime = now;
    }
    return timer->_keikaFrame;
}

/* Changes the timer's speed without moving its current time. */
void beBaseInfoRam_SetTimerScale(beBaseInfoRam *self, int name, float scale) {
    beBaseInfoRamTimer *timer;
    float ticks;
    float oldScale;
    long long bias;
    long long time;

    ensureTimerList(self);
    timer = igProperty_FindByName(self->_dataList, g_propertyNameField[0], name);
    oldScale = timer->_timeScale;
    if (scale != oldScale) {
        ticks = (float)(unsigned int)(int)(worldTimeOf(self) >> 0x12);
        time = __fixsfdi(ticks * oldScale);
        time <<= 0x12;
        time += timer->_timeBias;
        bias = time;
        bias -= __fixsfdi(ticks * scale) << 0x12;
        timer->_timeBias = bias;
        timer->_timeScale = scale;
        timer->_keikaFrame = 0.0f;
    }
}

/* An igObject with its vtable as a real vptr: slot 20 returns the object's meta object. */
class TypedObject {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
    virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual int getMetaObject();
};

void beBaseInfoRam_SetAllTimerScales(beBaseInfoRam *self, float scale) {
    int count;
    int i;
    int timerMeta;
    int *name;
    TypedObject *entry;
    if (self->_dataList != 0) {
        count = ((beBaseInfoDataList *)self->_dataList)->_count;
        for (i = 0; i < count; i++) {
            timerMeta = g_beBaseInfoRamTimer_metaObject[0];
            entry = ((TypedObject **)((beBaseInfoDataList *)self->_dataList)->_data)[i];
            if (timerMeta == entry->getMetaObject()) {
                name = (int *)((beBaseInfoData *)entry)->_name;
                name = name != 0 ? name : emptyString;
                beBaseInfoRam_SetTimerScale(self, (int)name, scale);
            }
        }
    }
}

void beBaseInfoRam_RemoveTimer(beBaseInfoRam *self, char *name) {
    igTDataList<igObject *> *list;
    int index;
    igObject *found;
    if (self->_dataList != 0) {
        ensureTimerList(self);
        found = (igObject *)igProperty_FindByName(self->_dataList, g_propertyNameField[0], name);
        if (found != 0) {
            list = (igTDataList<igObject *> *)self->_dataList;
            index = list->find(found);
            list = (igTDataList<igObject *> *)self->_dataList;
            igRelease(list->_data[index]);
            List_RemoveWordAt(list, index);
            list->_data[list->_count] = 0;
        }
    }
}

static inline int countOf(const igObjectList *l) { return l->_count; }

void beBaseInfoRam_RemoveAllTimers(beBaseInfoRam *self) {
    int timerMeta;
    int count;
    int i;
    igObjectList *list;
    int offset;
    int size;
    TypedObject *entry;
    igObjectList *first;

    first = ((igObjectList *)self->_dataList);
    if (first != 0) {
        count = first->_count;
        i = 0;
        if (count > 0) {
            do {
                offset = i * 4;
                entry = *(TypedObject **)(((igObjectList *)self->_dataList)->_data + offset);
                timerMeta = g_beBaseInfoRamTimer_metaObject[0];
                if (timerMeta == entry->getMetaObject()) {
                    list = ((igObjectList *)self->_dataList);
                    igRelease(*(igObject **)(list->_data + offset));
                    List_RemoveWordAt(list, i);
                    count -= 1;
                    i -= 1;
                    ((igObject **)list->_data)[list->_count] = 0;
                }
                i += 1;
            } while (i < count);
        }
        list = (igObjectList *)self->_dataList;
        size = list->_count;
        if (size >= countOf(list)) {
            List_Reserve(list, size, 4);
        }
    }
}

/* Takes a reference to the insight's movie manager. */
void Gap__Bec__beMovie__vfunc_32(beMovie *self) {
    igObject *manager = (igObject *)igInsightCore_FindManager(self->_insight, g_igMovieManager_metaObject[0]);
    if (manager != 0) {
        manager->_refCount = manager->_refCount + 1;
    }
    igRelease((igObject *)self->_movie);
    self->_movie = (int)manager;
}

void Gap__Bec__beMovie__vfunc_29(beMovie *self, int receiver, char *, int, int)
{
    beMessenger_RegisterReceiver(self->_messenger, receiver, MOVIE, 0, -1);
}

int Gap__Bec__beMovie__vfunc_30(void)
{
    return g_beMovieInfo_metaObject[0];
}

/* The igMovieManager virtuals the movie controller calls: slot 26 stops every movie, slot 30
 * returns a named movie's state (2 once it has finished or is not playing). */
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class MoviePlayer {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
    virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
    virtual void slot25();
    virtual void stopAll();
    virtual void slot27(); virtual void slot28(); virtual void slot29();
    virtual int getState(int *name);
};
enum MovieState { kMovieFinished = 2 };
/* Start or Cross in the pad's pressed word skips the movie. */
enum MovieSkipButton { kButtonStart = 0x0008, kButtonCross = 0x4000 };

struct StringHeader { int owner; int refCount; };

/* While a movie plays: Start or Cross stops it, and once it has finished the Lua chunk its
 * beMovieInfoData names runs and the playing name is cleared. */
void Gap__Bec__beMovie__vfunc_31(beMovie *self, beBaseInfoRam *ram) {
    bePadData *pad;
    int pressed;
    MoviePlayer *player;
    bool finished;
    int lua;
    beBaseInfoDataList *list;
    int i;
    igObject *entry;
    beMovieInfoData *data;
    int *name;
    int *playing;
    int empty;
    StringHeader *header;
    int refs;
    if (self->_playingName != 0) {
        pad = bePadManager_GetPadForPlayer((int)igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]), 0);
        pressed = pad->_trigger;
        if ((pressed & kButtonStart) || (pressed & kButtonCross)) {
            player = (MoviePlayer *)self->_movie;
            if (player != 0) player->stopAll();
        }
        player = (MoviePlayer *)self->_movie;
        finished = false;
        if (player != 0) {
            if (player->getState((int *)self->_playingName) == kMovieFinished) finished = true;
        } else finished = true;
        if (finished) {
            lua = (int)igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]);
            list = (beBaseInfoDataList *)((beMovieInfo *)ram->_parentInfo)->_dataList;
            for (i = 0; i < list->_count; i++) {
                entry = ((igObject **)list->_data)[i];
                if (entry != 0 && igObject_IsKindOf(entry, g_beMovieInfoData_metaObject[0]) != 0) data = (beMovieInfoData *)entry;
                else data = 0;
                if (data == 0) return;
                name = (int *)data->_name;
                name = name != 0 ? name : emptyString;
                if (strcmp((int *)self->_playingName, name) == 0) {
                    beLua__RunNamedChunk(lua, data->_callLuaName, 0);
                    break;
                }
            }
            if (g_stringPool[0] == 0) {
                empty = StringPool_Allocate(16);
                if (empty) empty = StringPool_Construct(empty);
                g_stringPool[0] = empty;
            }
            empty = StringPool_Intern(g_stringPool[0], 0);
            playing = (int *)self->_playingName;
            if (playing) {
                header = (StringHeader *)playing - 1;
                refs = header->refCount - 1;
                header->refCount = refs;
                if (refs == 0) StringChunk_ReleaseHeader(header->owner, header);
            }
            self->_playingName = empty;
        }
    }
}

/* A holder of one object reference; its deleting destructor is emitted after the controller. */
struct MovieObjectRef {
    igObject *object;
    ~MovieObjectRef();
};

MovieObjectRef::~MovieObjectRef() {
    igObject *held = object;
    if (held) { held->_refCount -= 1; if ((held->_refCount & 0x7fffff) == 0) igObject_Destroy(held); }
}

int Gap__Bec__beMovie__vfunc_20(void)
{
    return g_beMovie_metaObject[0];
}
