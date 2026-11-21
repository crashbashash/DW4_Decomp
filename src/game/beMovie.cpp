#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igTDataList.h"
#include "dw4/movie/igMovieManagerDispatchView.h"
#include "dw4/game/beBaseInfoRam.h"
#include "dw4/game/beCriAudio.h"
#include "dw4/game/beCriVolume.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beBaseInfoRamTimer.h"
#include "dw4/game/beCriSndf.h"
#include "dw4/game/beLua.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beMovie.h"
#include "dw4/game/beMovieInfo.h"
#include "dw4/game/beMovieInfoData.h"
#include "dw4/game/bePadManager.h"
#include "dw4/audio/igAdxAudio.h"
#include "dw4/core/igDataLists.h"
#include "dw4/scenegraph/igGroup.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/movie/igMovieInfo.h"
#include "dw4/movie/igMovieManager.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include "dw4/scenegraph/igPlanarShadowShader.h"
#include "dw4/viewer/igViewerSceneInfoManager.h"
#include "dw4/support/softfloat.h"
#include <string.h>
#include "dw4/support/emptyString.h"
#include "dw4/cri/cri_sndf.h"
#pragma push
#pragma readonly_strings on

extern "C" int beMovie_OnMessage(beMovie *self, beBaseInfoRam *ram, beMessengerWork *work);
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

extern "C" void beCriAudio_ReportError(beCriAudio *self, int code, char *where);
extern "C" float beCriVolume_StepFade(beCriVolume *self);
extern "C" long long beBaseInfoRam_GetTimerElapsed(beBaseInfoRam *self, const char *name);
extern "C" void beBaseInfoRam_SetTimerScale(beBaseInfoRam *self, int name, float scale);
extern "C" void beMovie_Prepare(beMovie *self);
extern "C" void beMovie_OnAddRam(beMovie *self, int receiver, char *, int, int);
extern "C" igMetaObject *beMovie_GetInfoMeta(void);
extern "C" void beMovie_UpdateRam(beMovie *self, beBaseInfoRam *ram);
extern "C" igMetaObject *beMovie_GetMeta(void);

static inline bool isSndfVoice(beCriAudio *s) { return s->_sndf != 0 && s->_audioType == kAudioSndf; }
static inline bool isAdxFileVoice(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == kAudioAdxFile; }
static inline bool isAdxMemoryVoice(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == kAudioAdxMemory; }

static inline igAdxAudio *adxOf(beCriAudio *s) { return (igAdxAudio *)s->_adxt; }
static inline beCriSndf *sndfOf(beCriAudio *s) { return (beCriSndf *)s->_sndf; }

int beCriAudio_Setup(beCriAudio *self, int channels) {
    if (channels < 0) {
        int allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
        igRelease((igObject *)self->_sndf);
        self->_sndf = (int)beCriSndf_Create(allocator);
        igRelease((igObject *)self->_adxt);
        self->_adxt = 0;
        self->_audioType = kAudioSndf;
    } else {
        int allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
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

unsigned char beCriAudio_PlayFile(beCriAudio *self, const char *name) {
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

int beCriAudio_PlayMemory(beCriAudio *self, void *data, int size) {
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
        switch (igAdxAudio_GetStatus(adxOf(self))) {
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
void beCriAudio_Suspend(beCriAudio *self) {
    bool adxFile;
    int volume;
    int type;
    if (isSndfVoice(self)) {
        self->_errVolume = 127;
        return;
    }
    adxFile = false;
    if (self->_adxt != 0) {
        type = self->_audioType;
        if (type == kAudioAdxFile) {
            adxFile = true;
        }
    }
    if (adxFile || isAdxMemoryVoice(self)) {
        volume = igAdxAudio_GetOutVolume(adxOf(self));
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
int beCriVolume_StepSndfLevel(beCriVolume *self, int baseVolume) {
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

/* The allocator new members come from: the owner's own, or the user pool. */
static inline int allocatorFor(void *owner) {
    int allocator = (int)((Gap::Core::igObject *)owner)->getMemoryPool();
    return g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
}

/* Creates the ram's timer list on first use. */
static inline void ensureTimerList(beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(allocatorFor(ram)));
        igObject *list = created.p;
        if (list != 0) list->_refCount = list->_refCount + 1;
        igRelease((igObject *)ram->_dataList);
        ram->_dataList = (int)list;
    }
}

static inline long long worldTimeOf(beBaseInfoRam *ram) {
    return ((igInsightCore *)((beBaseInfoManager *)ram->_parentManager)->_insight)->_worldTime;
}

void beBaseInfoRam_StartTimer(beBaseInfoRam *self, const char *name, long long endTime) {
    beBaseInfoRamTimer *timer;
    long long now;
    unsigned ticks;
    float scaled;

    ensureTimerList(self);
    timer = (beBaseInfoRamTimer *)((Gap::Core::igObjectList *)self->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, name);
    if (timer == 0) {
        TimerHolder created(beBaseInfoRamTimer_Create(allocatorFor(self)));
        igNamedObject_SetName((igNamedObject *)created.p, name);
        if (self->_dataList == 0) {
            igSmartPointer<igObject> list(beBaseInfoDataList_Create(allocatorFor(self)));
            igObject *retained = list.p;
            if (retained != 0) retained->_refCount = retained->_refCount + 1;
            igRelease((igObject *)self->_dataList);
            self->_dataList = (int)retained;
        }
        ((Gap::Core::igObjectList *)self->_dataList)->append((Gap::Core::igObject *)created.p);
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

unsigned char beBaseInfoRam_HasTimer(beBaseInfoRam *self, const char *name) {
    ensureTimerList(self);
    return ((Gap::Core::igObjectList *)self->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, name) != 0;
}

unsigned char beBaseInfoRam_IsTimerExpired(beBaseInfoRam *self, const char *name) {
    beBaseInfoRamTimer *timer;
    long long endTime;
    ensureTimerList(self);
    timer = (beBaseInfoRamTimer *)((Gap::Core::igObjectList *)self->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, name);
    if (timer == 0) {
        return 1;
    }
    endTime = timer->_endTime;
    return endTime < beBaseInfoRam_GetTimerElapsed(self, name);
}

long long beBaseInfoRam_GetTimerElapsed(beBaseInfoRam *self, const char *name) {
    beBaseInfoRamTimer *timer;
    ensureTimerList(self);
    timer = (beBaseInfoRamTimer *)((Gap::Core::igObjectList *)self->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, name);
    int ticks = (int)(worldTimeOf(self) >> 0x12);
    float scaled = (float)(unsigned int)ticks;
    scaled = scaled * timer->_timeScale;
    long long scaledTicks = __fixsfdi(scaled);
    return (scaledTicks << 0x12) + timer->_timeBias;
}

/* Frames (1/60 s) the timer advanced since the previous world frame, at most 3; computed once per
 * world frame. */
float beBaseInfoRam_GetTimerFrameDelta(beBaseInfoRam *self, const char *name) {
    beBaseInfoRamTimer *timer;
    long long now;
    long long time;
    float frames;
    ensureTimerList(self);
    timer = (beBaseInfoRamTimer *)((Gap::Core::igObjectList *)self->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, name);
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
    timer = (beBaseInfoRamTimer *)((Gap::Core::igObjectList *)self->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, (const char *)name);
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

void beBaseInfoRam_SetAllTimerScales(beBaseInfoRam *self, float scale) {
    int count;
    int i;
    igMetaObject *timerMeta;
    int *name;
    igObjectDispatchView *entry;
    if (self->_dataList != 0) {
        count = ((beBaseInfoDataList *)self->_dataList)->_count;
        for (i = 0; i < count; i++) {
            timerMeta = g_beBaseInfoRamTimer_metaObject;
            entry = ((igObjectDispatchView **)((beBaseInfoDataList *)self->_dataList)->_data)[i];
            if (timerMeta == entry->GetMeta()) {
                name = (int *)((beBaseInfoData *)entry)->_name;
                name = name != 0 ? name : (int *)emptyString;
                beBaseInfoRam_SetTimerScale(self, (int)name, scale);
            }
        }
    }
}

void beBaseInfoRam_RemoveTimer(beBaseInfoRam *self, const char *name) {
    igTDataList<igObject *> *list;
    int index;
    igObject *found;
    if (self->_dataList != 0) {
        ensureTimerList(self);
        found = (igObject *)((Gap::Core::igObjectList *)self->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, name);
        if (found != 0) {
            list = (igTDataList<igObject *> *)self->_dataList;
            index = list->find(found);
            list = (igTDataList<igObject *> *)self->_dataList;
            igRelease(list->_data[index]);
            List_RemoveWordAt((igDataList *)list, index);
            list->_data[list->_count] = 0;
        }
    }
}

static inline int countOf(const igObjectList *l) { return l->_count; }

void beBaseInfoRam_RemoveAllTimers(beBaseInfoRam *self) {
    igMetaObject *timerMeta;
    int count;
    int i;
    igObjectList *list;
    int offset;
    int size;
    igObjectDispatchView *entry;
    igObjectList *first;

    first = ((igObjectList *)self->_dataList);
    if (first != 0) {
        count = first->_count;
        i = 0;
        if (count > 0) {
            do {
                offset = i * 4;
                entry = *(igObjectDispatchView **)(((igObjectList *)self->_dataList)->_data + offset);
                timerMeta = g_beBaseInfoRamTimer_metaObject;
                if (timerMeta == entry->GetMeta()) {
                    list = ((igObjectList *)self->_dataList);
                    igRelease(*(igObject **)(list->_data + offset));
                    List_RemoveWordAt((igDataList *)list, i);
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
            ((Gap::Core::igDataList *)list)->setCapacity(size, 4);
        }
    }
}

/* Takes a reference to the insight's movie manager. */
void beMovie_Prepare(beMovie *self) {
    igObject *manager = igInsightCore_FindManager((igInsightCore *)self->_insight, g_igMovieManager_metaObject);
    igObject::ref(manager);
    igRelease((igObject *)self->_movie);
    self->_movie = (int)manager;
}

void beMovie_OnAddRam(beMovie *self, int receiver, char *, int, int)
{
    beMessenger_RegisterReceiver((beMessenger *)self->_messenger, (beBaseInfoRam *)receiver, MOVIE, 0, -1);
}

igMetaObject *beMovie_GetInfoMeta(void)
{
    return g_beMovieInfo_metaObject;
}

enum MovieState { kMovieFinished = 2 };
/* Start or Cross in the pad's pressed word skips the movie. */
enum MovieSkipButton { kButtonStart = 0x0008, kButtonCross = 0x4000 };

struct StringHeader { int owner; int refCount; };

/* The game's string pool, created on first use. */
static inline int stringPool(void) {
    if (g_stringPool == 0) {
        int pool = (int)StringPool_Allocate(16);
        if (pool) pool = (int)StringPool_Construct((StringPool *)pool);
        g_stringPool = (StringPool *)pool;
    }
    return (int)g_stringPool;
}

static inline void releaseString(int string) {
    if (string != 0) {
        StringHeader *header = (StringHeader *)string - 1;
        int refs = header->refCount - 1;
        header->refCount = refs;
        if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)header->owner, (StringTokenHeader *)header);
    }
}

/* Points a string field of the movie at the pooled copy of `text`, releasing the string it held. */
static inline void setMovieString(const igSmartPointer<igMovieInfo> &movie, int igMovieInfo::*field, const char *text) {
    /* matching construct: register-allocator tracer — the movie pointer, numbered after the token, colours first and takes s1 */
    int interned;
    igMovieInfo *info = movie.p;
    interned = (int)StringPool_Intern((StringPool *)stringPool(), (const char *)text);
    releaseString(info->*field);
    info->*field = interned;
}

static inline const char *nameOf(const beMovieInfoData *data) {
    return data->_name != 0 ? (const char *)data->_name : (const char *)emptyString;
}

/* While a movie plays: Start or Cross stops it, and once it has finished the Lua chunk its
 * beMovieInfoData names runs and the playing name is cleared. */
void beMovie_UpdateRam(beMovie *self, beBaseInfoRam *ram) {
    bePadData *pad;
    int pressed;
    igMovieManagerDispatchView *player;
    bool finished;
    int lua;
    beBaseInfoDataList *list;
    int i;
    igObject *entry;
    beMovieInfoData *data;
    const char *name;
    int empty;
    if (self->_playingName != 0) {
        pad = bePadManager_GetPadForPlayer((bePadManager *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject), 0);
        pressed = pad->_trigger;
        if ((pressed & kButtonStart) || (pressed & kButtonCross)) {
            player = (igMovieManagerDispatchView *)self->_movie;
            if (player != 0) player->stopAllMovies();
        }
        player = (igMovieManagerDispatchView *)self->_movie;
        finished = false;
        if (player != 0) {
            if (player->getMovieState((const char *)self->_playingName) == kMovieFinished) finished = true;
        } else finished = true;
        if (finished) {
            lua = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject);
            list = (beBaseInfoDataList *)((beMovieInfo *)ram->_parentInfo)->_dataList;
            for (i = 0; i < list->_count; i++) {
                entry = ((igObject **)list->_data)[i];
                if (entry != 0 && ((Gap::Core::igObject *)entry)->isOfType(g_beMovieInfoData_metaObject) != 0) data = (beMovieInfoData *)entry;
                else data = 0;
                if (data == 0) return;
                name = nameOf(data);
                if (strcmp((const char *)self->_playingName, name) == 0) {
                    beLua__RunNamedChunk((beLua *)lua, (const char *)data->_callLuaName, 0);
                    break;
                }
            }
            empty = (int)StringPool_Intern((StringPool *)stringPool(), 0);
            releaseString(self->_playingName);
            self->_playingName = empty;
        }
    }
}

/* A message to the movie controller: names a movie of its beMovieInfo and has it played in a layer. */
int beMovie_OnMessage(beMovie *self, beBaseInfoRam *ram, beMessengerWork *work) {
    beMovieInfo *info = (beMovieInfo *)ram->_parentInfo;
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beMovie_GetMessageEnum(), (const char *)work->_message)) {
    case 1: {
        int movieName = (int)beMessenger_GetString((beMessenger *)self->_messenger, 0);
        if (self->_playingName != 0) return 1;
        beBaseInfoDataList *list = (beBaseInfoDataList *)info->_dataList;
        for (int i = 0; i < list->_count; i++) {
            igObject *entry = ((igObject **)list->_data)[i];
            beMovieInfoData *data;
            if (entry != 0 && ((Gap::Core::igObject *)entry)->isOfType(g_beMovieInfoData_metaObject) != 0) data = (beMovieInfoData *)entry;
            else data = 0;
            if (data == 0) return 1;
            if (strcmp((const char *)movieName, nameOf(data)) != 0) continue;
            if (self->_movie != 0) {
                igSmartPointer<igMovieInfo> movie(igMovieInfo_Create(allocatorFor(self)));
                igNamedObject_SetName((igNamedObject *)movie.p, "Movie Player");
                setMovieString(movie, &igMovieInfo::_codecType, "igCriMovieCodec");
                setMovieString(movie, &igMovieInfo::_path, nameOf(data));
                igInsightCore_AddInfo((igInsightCore *)self->_insight, (igObject *)movie.p);
                beMessenger_SelectGroup((beMessenger *)self->_messenger, "LAYERCTL");
                beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)data->_parentLayer);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GETLAYERNODE");
                if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) <= 0) return 1;
                igObject *object = beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                igGroup *layer;
                if (object != 0 && ((Gap::Core::igObject *)object)->isOfType(g_igGroup_metaObject) != 0) layer = (igGroup *)object;
                else layer = 0;
                if (layer == 0) return 1;
                igObject *child = ((igObject **)((igObjectList *)layer->_childList)->_data)[0];
                igAttrSet *layerNode;
                if (child != 0 && ((Gap::Core::igObject *)child)->isOfType(g_igAttrSet_metaObject) != 0) layerNode = (igAttrSet *)child;
                else layerNode = 0;
                if (layerNode == 0) return 1;
                if (movie.p->_sceneInfo == 0) return 1;
                igObject *graph = (igObject *)((igSceneInfo *)movie.p->_sceneInfo)->_sceneGraph;
                igAttrSet *scene;
                if (graph != 0 && ((Gap::Core::igObject *)graph)->isOfType(g_igAttrSet_metaObject) != 0) scene = (igAttrSet *)graph;
                else scene = 0;
                if (scene == 0) return 1;
                igGroup_AppendChild((igGroup *)layerNode, (igNode *)scene);
                igViewerSceneInfoManager *viewer = (igViewerSceneInfoManager *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_igViewerSceneInfoManager_metaObject);
                igGroup_RemoveChild((igGroup *)((igViewerParameters *)viewer->_parameters)->_scene, (igNode *)scene);
            }
            int playing = (int)StringPool_Intern((StringPool *)stringPool(), (const char *)nameOf(data));
            releaseString(self->_playingName);
            self->_playingName = playing;
            break;
        }
        break;
    }
    case 0:
    case 2:
    case 3:
        break;
    default:
        return 0;
    }
    return 1;
}

igMetaObject *beMovie_GetMeta(void)
{
    return g_beMovie_metaObject;
}
#pragma pop
