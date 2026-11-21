/* beSound: the sound controller. It answers the SOUND messages (play, stop and fade a cue of the stage's
 * beSoundInfo, ask whether a stream is ready, hand the sound banks to the sound IOP module), keeps the
 * name of the BGM it started, and keeps a bePlaySE row per recently played effect so that the same
 * effect does not start again within 50 ms. The voices themselves belong to beCri. See
 * docs/engine/sound-format.md. */
#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/StringPool.h"
#include "dw4/core/igStringRef.h"
#include "dw4/game/beCri.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/bePlaySE.h"
#include "dw4/game/beSound.h"
#include "dw4/game/beSoundInfo.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igStringObj.h"
#include <string.h>
#pragma push
#pragma readonly_strings on

/* beMessenger_ResolveEnumValue values of the handler's command names. */
enum SoundMessage {
    MESSAGE_MODENONE, MESSAGE_STOP, MESSAGE_PLAY, MESSAGE_PLAYatPAUSE, MESSAGE_PAUSEOFF, MESSAGE_VOLUMECTL,
    MESSAGE_BGMSTOP, MESSAGE_ENVSTOP, MESSAGE_SESTOP, MESSAGE_GETWORDLIST, MESSAGE_VOLUMECTL2, MESSAGE_FXCTL,
    MESSAGE_ISREADY, MESSAGE_ISBGMREADY, MESSAGE_ISENVREADY, MESSAGE_ISALLREADY, MESSAGE_GETCURRENTBGM,
    MESSAGE_SNDFVOLUME, MESSAGE_OFFREEZE, MESSAGE_ONFREEZE, MESSAGE_MAKEBINLIST, MESSAGE_ISDONETRANS,
    MESSAGE_FREESFPDATA
};

/* beSoundData::_type: music and ambience stream; every other type is a resident effect. */
enum SoundType { SOUND_BGM = 1, SOUND_ENV = 2 };

/* beBaseInfoRam::_st0 of the controller: the first update drops the stage's static infos, later ones
 * drop the expired play rows. */
enum SoundState { STATE_START = 0, STATE_RUN = 1 };

/* beCri_StopGroup groups. */
enum CriGroup { CRI_GROUP_BGM = 1, CRI_GROUP_ENV = 2, CRI_GROUP_EFFECTS = 4 };

/* beCri::_dataType: every cue streams from the AFS archives, or the effects sit in sound banks. */
enum CriDataType { CRI_DATA_ADX = 0, CRI_DATA_SFP = 1 };

/* igInsightCore::_worldTime nanoseconds an effect is held back after it starts. */
#define EFFECT_REPEAT_HOLD 49999998
/* Frames of the UP and DOWN fades of VOLUMECTL. */
#define VOLUMECTL_FADE_FRAMES 10.0f
/* beMessenger_EnqueueSelected delay of the PLAY retried while a stream fades out. */
#define PLAY_RETRY_DELAY 0xB

#include "dw4/support/emptyString.h"
#include "dw4/support/list-services.h"
extern "C" {
void beSound_Prepare(beSound *self);
void beSound_OnAddRam(beSound *self, beBaseInfoRam *ram);
igMetaObject *beSound_GetInfoMeta(void);
void beSound_UpdateRam(beSound *self, beBaseInfoRam *ram);
int beSound_OnMessage(beSound *self, beBaseInfoRam *ram, beMessengerWork *message);
int beSound_FindData(beSound *self, beBaseInfoRam *ram, const char *name);
igMetaObject *beSound_GetMeta(void);

}

/* An IEEE single split into its magnitude and sign bit. */
struct FloatBits { unsigned mantissa : 31; unsigned sign : 1; };

static inline float Abs(float value) {
    ((FloatBits *)&value)->sign = 0;
    return value;
}

/* The text of a string object; an empty one has no buffer. */
static inline char *TextOf(igStringObj *string) {
    char *text = (char *)string->_buffer;
    if (text == 0) return g_stringObjEmptyText;
    return text;
}

/* An object's name; an unnamed object reads as the empty string. */
static inline char *NameOf(int name) { return name ? (char *)name : emptyString; }

static inline char *HandleName(int handle) { return NameOf(((beCriHandle *)handle)->_name); }

/* Drops a share of a pooled string; the reference count is the word before the text. */
static inline void ReleaseString(char *text) {
    if (text != 0) {
        int *header = (int *)text - 2;
        int count = ((int *)text)[-1] - 1;
        ((int *)text)[-1] = count;
        if (count == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
    }
}

/* The allocator for an object the owner creates: its own, or the default one. */
static inline void *AllocatorFor(void *owner) {
    void *allocator = ((Gap::Core::igObject *)owner)->getMemoryPool();
    return g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
}

/* The pooled copy of `text`, creating the string pool on first use. */
static inline char *InternString(char *text) {
    if (g_stringPool == 0) {
        int pool = (int)StringPool_Allocate(0x10);
        if (pool != 0) pool = (int)(StringPool_Construct((StringPool *)pool));
        g_stringPool = (StringPool *)pool;
    }
    return StringPool_Intern(g_stringPool, text);
}

/* Stores the pooled copy of `text` in a string field, dropping the field's previous string. */
static inline void SetString(int *field, char *text) {
    char *pooled = InternString(text);
    ReleaseString((char *)*field);
    *field = (int)pooled;
}

/* Owning stack reference to the list of bank names MAKEBINLIST collects, released on scope exit. */
struct NameListRef {
    igStringRefList *p;
    NameListRef(igStringRefList *o) : p(o) {}
    ~NameListRef() { igRelease(p); }
};
/* Shared stack reference to the system's scratch string object, released on scope exit. */
struct GlobalStrRef {
    igStringObj *p;
    GlobalStrRef(igStringObj *o) : p(o) { if (p != 0) p->_refCount = p->_refCount + 1; }
    ~GlobalStrRef() { igRelease(p); }
};

/* Drops the list's share of every object it holds and empties it. */
static inline void ReleaseAll(igObjectList *list) {
    int count = list->_count;
    int i;
    for (i = 0; i < count; i++) {
        igRelease(((igObject **)list->_data)[i]);
    }
    {
        int size = list->_count;
        int j;
        for (j = 0; j < size; j++) {
            ((igObject **)list->_data)[j] = 0;
        }
    }
    list->_count = 0;
}

/* Gives an emptied list its first block again. */
static inline void ReserveIfEmpty(igObjectList *list) {
    bool hasEntries = list->_count > 0;
    if (hasEntries == false) {
        ((Gap::Core::igDataList *)list)->setCapacity(0, 4);
    }
}

/* The play rows as the object list they are, with the list's inline accessors. */
struct PlaySEList : igObjectList {
    int getCount() const { return _count; }
    bePlaySE *get(int index) const { return ((bePlaySE **)_data)[index]; }
};

/* beSound::_playSEs as the class holds it: a smart pointer to that list. */
typedef igSmartPointer<PlaySEList> PlaySEListRef;

void beSound_Prepare(beSound *self) {
    if (self->_cri == 0) {
        igObject *cri = (igObject *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beCri_metaObject);
        if (cri != 0) {
            cri->_refCount = cri->_refCount + 1;
        }
        igRelease((igObject *)self->_cri);
        self->_cri = (int)cri;
    }
    ReleaseAll((igObjectList *)self->_playSEs);
    ReserveIfEmpty((igObjectList *)self->_playSEs);
}

void beSound_OnAddRam(beSound *self, beBaseInfoRam *ram) {
    beSoundInfo *info;
    beMessenger_RegisterReceiver((beMessenger *)self->_messenger, ram, "SOUND", 0, -1);
    info = (beSoundInfo *)ram->_parentInfo;
    ((beCri *)self->_cri)->_baseVolume = info->_baseVolume;
    beCri_SetSndfVolume((beCri *)self->_cri, info->_sndfVolume);
    if (info->_dataType == 0) {
        SetString(&info->_dataType, "acx");
    }
    if (strcmp((char *)info->_dataType, "acx") == 0) {
        ((beCri *)self->_cri)->_dataType = CRI_DATA_ADX;
    } else {
        ((beCri *)self->_cri)->_dataType = CRI_DATA_SFP;
    }
}

igMetaObject *beSound_GetInfoMeta(void)
{
    return g_beSoundInfo_metaObject;
}

void beSound_UpdateRam(beSound *self, beBaseInfoRam *ram) {
    igObjectList *infos;
    long long now;
    beBaseInfo *info;
    int infoIndex;
    switch (ram->_st0) {
    case STATE_START:
        beMessenger_SendGroup((beMessenger *)self->_messenger, "STATICINFO", "GETINFOLIST");
        if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) <= 0) break;
        infos = (igObjectList *)(beMessenger_GetObject((beMessenger *)self->_messenger, 0));
        infoIndex = 0;
        if (0 < infos->_count) do {
            info = ((beBaseInfo **)infos->_data)[infoIndex];
            if (NameOf(info->_name) == 0) {
                infoIndex++;
                continue;
            }
            if (strcmp(NameOf(info->_name), "_common") == 0) {
                infoIndex++;
                continue;
            }
            ReleaseAll((igObjectList *)info->_dataList);
            ReserveIfEmpty((igObjectList *)info->_dataList);
            igRelease(((igObject **)infos->_data)[infoIndex]);
            List_RemoveWordAt((igDataList *)infos, infoIndex);
            ((igObject **)infos->_data)[infos->_count] = 0;
        } while (infoIndex < infos->_count);
        beCri_SetFx((beCri *)self->_cri, "REVERB");
        ram->_st0++;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
    case STATE_RUN:
        now = ((igInsightCore *)self->_insight)->_worldTime;
        for (int i = 0; i < ((PlaySEListRef &)self->_playSEs)->getCount(); i++) {
            bePlaySE *playSE = ((PlaySEListRef &)self->_playSEs)->get(i);
            if (playSE->_time < now) {
                ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)((PlaySEListRef &)self->_playSEs).p))->removeByValue((Gap::Core::igObject *)playSE, i);
                i--;
            }
        }
    }
}

int beSound_OnMessage(beSound *self, beBaseInfoRam *ram, beMessengerWork *message) {
    igObjectList *infos;
    beSoundInfo *info;
    igNamedObject *object;
    igObjectList *fileNames;
    char *direction;
    char *name;
    float from, to, frames, span;
    int index;
    beCri *cri;
    long long handle;
    int fileIndex;
    int nameIndex;
    char *bankName;
    bool bankFound;
    int infoIndex;
    bool known;
    int knownIndex;
    int objectIndex;
    beSoundData *data;
    void *allocator;
    igObjectList *dataList;
    int dataCount;
    int dataIndex;
    long long now;

    info = (beSoundInfo *)ram->_parentInfo;
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beSound_GetMessageEnum(), (const char *)message->_message)) {
    case MESSAGE_STOP:
        if (beMessenger_GetLongCount((beMessenger *)self->_messenger) == 0) return 0;
        beCri_StopByID((beCri *)self->_cri, beMessenger_GetLong((beMessenger *)self->_messenger, 0));
        break;
    case MESSAGE_PLAYatPAUSE:
        ((beCri *)self->_cri)->_pauseOnetime = 1;
    case MESSAGE_PLAY:
        if ((index = beSound_FindData(self, ram, beMessenger_GetString((beMessenger *)self->_messenger, 0))) == -1) return 0;
        data = ((beSoundData **)((igObjectList *)info->_dataList)->_data)[index];
        switch (data->_type) {
        case SOUND_BGM:
            if (self->_currentBGM != 0 && strcmp(NameOf(data->_name), (char *)self->_currentBGM) == 0) return 1;
            if (beCri_PlayStream((beCri *)self->_cri, (igObjectList *)info->_fnameList, data) == 0) {
                beMessenger_PrepareDelayedGroup((beMessenger *)self->_messenger, "SOUND");
                beMessenger_AppendString((beMessenger *)self->_messenger, NameOf(data->_name));
                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "PLAY", PLAY_RETRY_DELAY);
            } else {
                SetString(&self->_currentBGM, NameOf(data->_name));
            }
            break;
        case SOUND_ENV:
            if (beCri_PlayStream((beCri *)self->_cri, (igObjectList *)info->_fnameList, data) == 0) {
                beMessenger_PrepareDelayedGroup((beMessenger *)self->_messenger, "SOUND");
                beMessenger_AppendString((beMessenger *)self->_messenger, NameOf(data->_name));
                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "PLAY", PLAY_RETRY_DELAY);
            }
            break;
        default:
            now = ((igInsightCore *)self->_insight)->_worldTime;
            for (int i = 0; i < ((PlaySEListRef &)self->_playSEs)->getCount(); i++) {
                bePlaySE *playSE = ((PlaySEListRef &)self->_playSEs)->get(i);
                if (playSE->_id == index && playSE->_time > now) {
                    beMessenger_AppendInt((beMessenger *)self->_messenger, 0);
                    beMessenger_AppendLong((beMessenger *)self->_messenger, 0);
                    return 1;
                }
            }
            handle = beCri_PlayEffect((beCri *)self->_cri, (igObjectList *)info->_fnameList, data);
            beMessenger_AppendInt((beMessenger *)self->_messenger, data->_type);
            beMessenger_AppendLong((beMessenger *)self->_messenger, handle);
            if (handle > 0) {
                allocator = AllocatorFor(self);
                igSmartPointer<bePlaySE> row(bePlaySE_CreateInstance((int)allocator));
                row->_id = index;
                row->_time = now + EFFECT_REPEAT_HOLD;
                ((Gap::Core::igObjectList *)self->_playSEs)->append((Gap::Core::igObject *)row.p);
            }
            break;
        }
        break;
    case MESSAGE_PAUSEOFF:
        cri = (beCri *)self->_cri;
        beCri_UnpauseByName(cri, beMessenger_GetString((beMessenger *)self->_messenger, 0));
        break;
    case MESSAGE_VOLUMECTL:
        direction = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
        if (beMessenger_GetLongCount((beMessenger *)self->_messenger) > 0) {
            if (strcmp(direction, "UP") == 0) {
                cri = (beCri *)self->_cri;
                beCri_FadeByID(cri, beMessenger_GetLong((beMessenger *)self->_messenger, 0), 0.0f, 1.0f, VOLUMECTL_FADE_FRAMES);
            } else if (strcmp(direction, "DOWN") == 0) {
                cri = (beCri *)self->_cri;
                beCri_FadeByID(cri, beMessenger_GetLong((beMessenger *)self->_messenger, 0), 1.0f, 0.0f, VOLUMECTL_FADE_FRAMES);
            }
            break;
        }
        if (beMessenger_GetStringCount((beMessenger *)self->_messenger) <= 1) break;
        name = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
        if (strcmp(direction, "UP") == 0) {
            beCri_FadeByName((beCri *)self->_cri, name, 0.0f, 1.0f, VOLUMECTL_FADE_FRAMES);
        } else if (strcmp(direction, "DOWN") == 0) {
            beCri_FadeByName((beCri *)self->_cri, name, 1.0f, 0.0f, VOLUMECTL_FADE_FRAMES);
        }
        if (self->_currentBGM != 0 && strcmp(name, (char *)self->_currentBGM) == 0) {
            SetString(&self->_currentBGM, 0);
        }
        break;
    case MESSAGE_VOLUMECTL2:
        if (beMessenger_GetStringCount((beMessenger *)self->_messenger) <= 0) return 0;
        if (beMessenger_GetFloatCount((beMessenger *)self->_messenger) < 3) return 0;
        name = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
        from = beMessenger_GetFloat((beMessenger *)self->_messenger, 0);
        to = beMessenger_GetFloat((beMessenger *)self->_messenger, 1);
        frames = beMessenger_GetFloat((beMessenger *)self->_messenger, 2);
        span = Abs(from - to); /* retail computes the size of the change and never uses it */
        beCri_FadeByName((beCri *)self->_cri, name, from, to, frames);
        break;
    case MESSAGE_BGMSTOP:
        beCri_StopGroup((beCri *)self->_cri, CRI_GROUP_BGM);
        SetString(&self->_currentBGM, 0);
        break;
    case MESSAGE_ENVSTOP:
        beCri_StopGroup((beCri *)self->_cri, CRI_GROUP_ENV);
        break;
    case MESSAGE_SESTOP:
        beCri_StopGroup((beCri *)self->_cri, CRI_GROUP_EFFECTS);
        break;
    case MESSAGE_FXCTL:
        beCri_SetFx((beCri *)self->_cri, beMessenger_GetString((beMessenger *)self->_messenger, 0));
        break;
    case MESSAGE_GETWORDLIST:
        dataList = (igObjectList *)info->_dataList;
        dataCount = dataList->_count;
        for (dataIndex = 0; dataIndex < dataCount; dataIndex++) {
            beMessenger_AppendString((beMessenger *)self->_messenger, NameOf(((beSoundData **)dataList->_data)[dataIndex]->_name));
        }
        break;
    case MESSAGE_ISREADY:
    case MESSAGE_ISALLREADY:
        if (beMessenger_GetStringCount((beMessenger *)self->_messenger) <= 0) {
            name = "ALL";
        } else {
            name = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
        }
        /* matching construct: retail widens the one-byte answer (andi) before passing it on */
        beMessenger_AppendBool((beMessenger *)self->_messenger, (int)beCri_IsReady((beCri *)self->_cri, name));
        break;
    case MESSAGE_ISBGMREADY:
        beMessenger_AppendBool((beMessenger *)self->_messenger, (int)beCri_IsReady((beCri *)self->_cri, HandleName(((beCri *)self->_cri)->_hdBGM)));
        break;
    case MESSAGE_ISENVREADY:
        beMessenger_AppendBool((beMessenger *)self->_messenger, (int)beCri_IsReady((beCri *)self->_cri, HandleName(((beCri *)self->_cri)->_hdENV)));
        break;
    case MESSAGE_SNDFVOLUME:
        beCri_SetSndfVolume((beCri *)self->_cri, beMessenger_GetInt((beMessenger *)self->_messenger, 0));
        break;
    case MESSAGE_ONFREEZE:
        beCri_SetFreezeAudible((beCri *)self->_cri, 0);
        break;
    case MESSAGE_OFFREEZE:
        beCri_SetFreezeAudible((beCri *)self->_cri, 1);
        break;
    case MESSAGE_MAKEBINLIST:
        if (info->_dataType == 0) return 0;
        beMessenger_SendGroup((beMessenger *)self->_messenger, "STATICINFO", "GETINFOLIST");
        if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) <= 0) return 0;
        infos = (igObjectList *)(beMessenger_GetObject((beMessenger *)self->_messenger, 0));
        fileNames = (igObjectList *)info->_fnameList;
        allocator = AllocatorFor(self);
        {
            NameListRef banks(igStringRefList_Create((int)allocator));
            GlobalStrRef scratch((igStringObj *)((beSystem *)self->_system)->_globalStrObj);
            for (fileIndex = 0; fileIndex < fileNames->_count; fileIndex++) {
                igStringObj_Set(scratch.p, NameOf(((igNamedObject **)fileNames->_data)[fileIndex]->_name));
                igStringObj_KeepExtension(scratch.p);
                igStringObj_Erase(scratch.p, 0, 1);
                char *dataType = (char *)info->_dataType;
                if (strcmp(dataType, TextOf(scratch.p)) == 0) {
                    igStringObj_Set(scratch.p, NameOf(((igNamedObject **)fileNames->_data)[fileIndex]->_name));
                    igStringObj_StripDirectory(scratch.p);
                    igStringObj_ToLower(scratch.p);
                    known = false;
                    igStringRef bank(TextOf(scratch.p));
                    for (knownIndex = 0; knownIndex < banks.p->_count; knownIndex++) {
                        if (strcmp(bank.p, StringList_CopyRetained(banks.p, knownIndex).p) == 0) {
                            known = true;
                            break;
                        }
                    }
                    if (known == false) {
                        StringList_AppendRetained(banks.p, igStringRef(bank).ref());
                    }
                }
            }
            for (nameIndex = 0; nameIndex < banks.p->_count; nameIndex++) {
                bankName = StringList_CopyRetained(banks.p, nameIndex).p;
                bankFound = false;
                for (infoIndex = 0; infoIndex < infos->_count; infoIndex++) {
                    igObjectList *objects = (igObjectList *)((beBaseInfo **)infos->_data)[infoIndex]->_dataList;
                    for (objectIndex = 0; objectIndex < objects->_count; objectIndex++) {
                        object = ((igNamedObject **)objects->_data)[objectIndex];
                        if (strcmp(NameOf(object->_name), bankName) == 0) {
                            ((Gap::Core::igObjectList *)(((beCri *)self->_cri)->_lsBinObjs))->append((Gap::Core::igObject *)object);
                            bankFound = true;
                            break;
                        }
                    }
                    if (bankFound) break;
                }
            }
        }
        beCri_StartSfpTransfers((beCri *)self->_cri);
        break;
    case MESSAGE_ISDONETRANS:
        beMessenger_AppendBool((beMessenger *)self->_messenger, (int)beCri_IsTransferDone((beCri *)self->_cri));
        break;
    case MESSAGE_FREESFPDATA:
        if (((beCri *)self->_cri)->_dataType == CRI_DATA_SFP) {
            beCri_FreeSfpData((beCri *)self->_cri, 1);
        }
        break;
    default:
        return 0;
    }
    return 1;
}

int beSound_FindData(beSound *self, beBaseInfoRam *ram, const char *name) {
    int i;
    igObjectList *list;
    int count;

    list = (igObjectList *)((beSoundInfo *)ram->_parentInfo)->_dataList;
    count = list->_count;
    for (i = 0; i < count; i++) {
        if (strcmp(name, NameOf(((beSoundData **)list->_data)[i]->_name)) == 0) {
            return i;
        }
    }
    return -1;
}

igMetaObject *beSound_GetMeta(void)
{
    return g_beSound_metaObject;
}

#pragma pop
