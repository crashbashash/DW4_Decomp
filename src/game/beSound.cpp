/* beSound: the sound controller. It answers the SOUND messages (play, stop and fade a cue of the stage's
 * beSoundInfo, ask whether a stream is ready, hand the sound banks to the sound IOP module), keeps the
 * name of the BGM it started, and keeps a bePlaySE row per recently played effect so that the same
 * effect does not start again within 50 ms. The voices themselves belong to beCri. See
 * docs/engine/sound-format.md. */
#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

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

extern "C" {
int igInsightCore_FindManager(int insight, int meta);
void *Memory_GetAllocatorBySelector(int selector);
void *igObject_GetAllocator(void *object);
int List_Reserve(igObjectList *list, int count, int elementSize);
int List_RemoveWordAt(igObjectList *list, int index);
int ObjectList_AppendRetained(igObjectList *list, igObject *object);
int StringPool_Allocate(int size);
int StringPool_Construct(int pool);
char *StringPool_Intern(int pool, const char *text);
int StringChunk_ReleaseHeader(int chunk, int *header);
int strcmp(const char *left, const char *right);
igStringRefList *igStringRefList_Create(void *allocator);
void igStringObj_Set(igStringObj *string, const char *text);
void igStringObj_ToLower(igStringObj *string);
void igStringObj_KeepExtension(igStringObj *string);
void igStringObj_StripDirectory(igStringObj *string);
int igStringObj_Erase(igStringObj *string, unsigned int position, unsigned int length);
int beSound_GetMessageEnum(void);
bePlaySE *bePlaySE_CreateInstance(void *allocator);

void beMessenger_RegisterReceiver(int messenger, void *receiver, const char *name, const char *text, int value);
void beMessenger_SendGroup(int messenger, const char *group, const char *message);
int beMessenger_GetObjectCount(int messenger);
igObjectList *beMessenger_GetObject(int messenger, int index);
unsigned int beMessenger_ResolveEnumValue(int messenger, int metaEnum, int name);
void beMessenger_PrepareDelayedGroup(int messenger, const char *group);
void beMessenger_EnqueueSelected(int messenger, const char *message, long long delay);
void beMessenger_AppendBool(int messenger, int value);
void beMessenger_AppendInt(int messenger, int value);
void beMessenger_AppendLong(int messenger, long long value);
void beMessenger_AppendString(int messenger, const char *text);
float beMessenger_GetFloat(int messenger, int index);
int beMessenger_GetFloatCount(int messenger);
int beMessenger_GetInt(int messenger, int index);
long long beMessenger_GetLong(int messenger, int index);
int beMessenger_GetLongCount(int messenger);
char *beMessenger_GetString(int messenger, int index);
int beMessenger_GetStringCount(int messenger);

long long beCri_PlayStream(beCri *self, igObjectList *names, beSoundData *cue);
long long beCri_PlayEffect(beCri *self, igObjectList *names, beSoundData *cue, int playing);
void beCri_StopByID(beCri *self, long long playID);
void beCri_StopGroup(beCri *self, int group);
void beCri_UnpauseByName(beCri *self, const char *name);
void beCri_FadeByName(beCri *self, char *name, float from, float to, float frames);
void beCri_FadeByID(beCri *self, long long playID, float from, float to, float frames);
void beCri_SetFreezeAudible(beCri *self, int audible);
void beCri_SetFx(beCri *self, char *name);
void beCri_SetSndfVolume(beCri *self, int volume);
bool beCri_StartSfpTransfers(beCri *self);
int beCri_FreeSfpData(beCri *self, int includeFirst);
bool beCri_IsTransferDone(beCri *self);
unsigned char beCri_IsReady(beCri *self, const char *name);

void beSound_Prepare(beSound *self);
void beSound_RegisterReceiver(beSound *self, beBaseInfoRam *ram);
int beSound_GetInfoMeta(void);
void beSound_Update(beSound *self, beBaseInfoRam *ram);
int beSound_OnMessage(beSound *self, beBaseInfoRam *ram, beMessengerWork *message);
int beSound_FindData(beSound *self, beBaseInfoRam *ram, char *name);
int beSound_GetMeta(void);

extern int g_beCri_metaObject[4];
extern int g_beSoundInfo_metaObject[4];
extern int g_beSound_metaObject[4];
extern int g_stringPool[4];
extern int g_defaultAllocatorSelector[4];
extern unsigned char g_useOwnerAllocator;
extern char *g_stringObjEmptyText[];
extern char emptyString[];
extern char SOUND_5[];
extern char acx[];
extern char STATICINFO[];
extern char GETINFOLIST[];
extern char common[];
extern char REVERB[];
extern char PLAY_4[];
extern char UP_2[];
extern char DOWN_2[];
extern char ALL_2[];
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
    if (text == 0) return g_stringObjEmptyText[0];
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
        if (count == 0) StringChunk_ReleaseHeader(*header, header);
    }
}

/* The allocator for an object the owner creates: its own, or the default one. */
static inline void *AllocatorFor(void *owner) {
    void *allocator = igObject_GetAllocator(owner);
    return g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
}

/* The pooled copy of `text`, creating the string pool on first use. */
static inline char *InternString(char *text) {
    if (g_stringPool[0] == 0) {
        int pool = StringPool_Allocate(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    return StringPool_Intern(g_stringPool[0], text);
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
/* A pooled string with a share taken on it; the reference count is the word before the text. */
struct StringRef {
    char *p;
    StringRef() {}
    StringRef(char *s) : p(s) { if (p != 0) ((int *)p)[-1] = ((int *)p)[-1] + 1; }
    ~StringRef() { ReleaseString(p); }
};
struct ListResult { int code; };
extern "C" ListResult ObjectList_RemoveFirstRetained(igObjectList *list, igObject *object, int start);
extern "C" int StringList_AppendRetained(igStringRefList *list, const StringRef &text);
extern "C" StringRef StringList_CopyRetained(igStringRefList *list, int index);

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

void beSound_Prepare(beSound *self) {
    igObjectList *playSEs;
    if (self->_cri == 0) {
        igObject *cri = (igObject *)igInsightCore_FindManager(self->_insight, g_beCri_metaObject[0]);
        if (cri != 0) {
            cri->_refCount = cri->_refCount + 1;
        }
        igRelease((igObject *)self->_cri);
        self->_cri = (int)cri;
    }
    ReleaseAll((igObjectList *)self->_playSEs);
    playSEs = (igObjectList *)self->_playSEs;
    if (!(0 < playSEs->_count)) {
        List_Reserve(playSEs, 0, 4);
    }
}

void beSound_RegisterReceiver(beSound *self, beBaseInfoRam *ram) {
    beSoundInfo *info;
    beMessenger_RegisterReceiver(self->_messenger, ram, SOUND_5, 0, -1);
    info = (beSoundInfo *)ram->_parentInfo;
    ((beCri *)self->_cri)->_baseVolume = info->_baseVolume;
    beCri_SetSndfVolume((beCri *)self->_cri, info->_sndfVolume);
    if (info->_dataType == 0) {
        SetString(&info->_dataType, acx);
    }
    if (strcmp((char *)info->_dataType, acx) == 0) {
        ((beCri *)self->_cri)->_dataType = CRI_DATA_ADX;
    } else {
        ((beCri *)self->_cri)->_dataType = CRI_DATA_SFP;
    }
}

int beSound_GetInfoMeta(void)
{
    return g_beSoundInfo_metaObject[0];
}

void beSound_Update(beSound *self, beBaseInfoRam *ram) {
    igObjectList *infos;
    long long now;
    beBaseInfo *info;
    igObjectList *playSEs;
    int infoIndex;
    int row;
    switch (ram->_st0) {
    case STATE_START:
        beMessenger_SendGroup(self->_messenger, STATICINFO, GETINFOLIST);
        if (beMessenger_GetObjectCount(self->_messenger) <= 0) break;
        infos = beMessenger_GetObject(self->_messenger, 0);
        infoIndex = 0;
        if (0 < infos->_count) do {
            info = ((beBaseInfo **)infos->_data)[infoIndex];
            if (NameOf(info->_name) == 0) {
                infoIndex++;
                continue;
            }
            if (strcmp(NameOf(info->_name), common) == 0) {
                infoIndex++;
                continue;
            }
            ReleaseAll((igObjectList *)info->_dataList);
            if (!(0 < ((igObjectList *)info->_dataList)->_count)) {
                List_Reserve((igObjectList *)info->_dataList, 0, 4);
            }
            igRelease(((igObject **)infos->_data)[infoIndex]);
            List_RemoveWordAt(infos, infoIndex);
            ((igObject **)infos->_data)[infos->_count] = 0;
        } while (infoIndex < infos->_count);
        beCri_SetFx((beCri *)self->_cri, REVERB);
        ram->_st0++;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
    case STATE_RUN:
        now = ((igInsightCore *)self->_insight)->_worldTime;
        playSEs = (igObjectList *)self->_playSEs;
        for (row = 0; row < playSEs->_count; row++) {
            bePlaySE *playSE = ((bePlaySE **)playSEs->_data)[row];
            if (playSE->_time < now) {
                ObjectList_RemoveFirstRetained(playSEs, (igObject *)playSE, row);
                row--;
            }
            playSEs = (igObjectList *)self->_playSEs;
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
    char *text;
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
    char *pooled;
    char *dataType;
    beSoundData *data;
    void *allocator;
    igObjectList *dataList;
    int dataCount;
    int dataIndex;
    bePlaySE *playSE;
    int offset;
    bePlaySEList *playSEs;
    bePlaySEList *rows;
    long long now;
    int playing;

    info = (beSoundInfo *)ram->_parentInfo;
    switch (beMessenger_ResolveEnumValue(self->_messenger, beSound_GetMessageEnum(), message->_message)) {
    case MESSAGE_STOP:
        if (beMessenger_GetLongCount(self->_messenger) == 0) return 0;
        beCri_StopByID((beCri *)self->_cri, beMessenger_GetLong(self->_messenger, 0));
        break;
    case MESSAGE_PLAYatPAUSE:
        ((beCri *)self->_cri)->_pauseOnetime = 1;
    case MESSAGE_PLAY:
        if ((index = beSound_FindData(self, ram, beMessenger_GetString(self->_messenger, 0))) == -1) return 0;
        data = ((beSoundData **)((igObjectList *)info->_dataList)->_data)[index];
        switch (data->_type) {
        case SOUND_BGM:
            if (self->_currentBGM != 0 && strcmp(NameOf(data->_name), (char *)self->_currentBGM) == 0) return 1;
            if (beCri_PlayStream((beCri *)self->_cri, (igObjectList *)info->_fnameList, data) == 0) {
                beMessenger_PrepareDelayedGroup(self->_messenger, SOUND_5);
                beMessenger_AppendString(self->_messenger, NameOf(data->_name));
                beMessenger_EnqueueSelected(self->_messenger, PLAY_4, PLAY_RETRY_DELAY);
            } else {
                SetString(&self->_currentBGM, NameOf(data->_name));
            }
            break;
        case SOUND_ENV:
            if (beCri_PlayStream((beCri *)self->_cri, (igObjectList *)info->_fnameList, data) == 0) {
                beMessenger_PrepareDelayedGroup(self->_messenger, SOUND_5);
                beMessenger_AppendString(self->_messenger, NameOf(data->_name));
                beMessenger_EnqueueSelected(self->_messenger, PLAY_4, PLAY_RETRY_DELAY);
            }
            break;
        default:
            now = ((igInsightCore *)self->_insight)->_worldTime;
            playSEs = (bePlaySEList *)self->_playSEs;
            /* matching construct: m2c — the list copy and the int view of _count keep the row and count loads inside the loop */
            playing = 0;
            rows = playSEs;
            if (0 < *(int *)&playSEs->_count) {
                offset = 0;
                do {
                    playSE = *(bePlaySE **)((char *)rows->_data + offset);
                    if (playSE->_id == index && now < playSE->_time) {
                        beMessenger_AppendInt(self->_messenger, 0);
                        beMessenger_AppendLong(self->_messenger, 0);
                        return 1;
                    }
                    playing += 1;
                    offset += 4;
                    rows = playSEs;
                } while (playing < playSEs->_count);
            }
            handle = beCri_PlayEffect((beCri *)self->_cri, (igObjectList *)info->_fnameList, data, playing);
            beMessenger_AppendInt(self->_messenger, data->_type);
            beMessenger_AppendLong(self->_messenger, handle);
            if (handle > 0) {
                allocator = AllocatorFor(self);
                igSmartPointer<bePlaySE> row(bePlaySE_CreateInstance(allocator));
                row->_id = index;
                row->_time = now + EFFECT_REPEAT_HOLD;
                ObjectList_AppendRetained((igObjectList *)self->_playSEs, row.p);
            }
            break;
        }
        break;
    case MESSAGE_PAUSEOFF:
        cri = (beCri *)self->_cri;
        beCri_UnpauseByName(cri, beMessenger_GetString(self->_messenger, 0));
        break;
    case MESSAGE_VOLUMECTL:
        direction = beMessenger_GetString(self->_messenger, 0);
        if (beMessenger_GetLongCount(self->_messenger) > 0) {
            if (strcmp(direction, UP_2) == 0) {
                cri = (beCri *)self->_cri;
                beCri_FadeByID(cri, beMessenger_GetLong(self->_messenger, 0), 0.0f, 1.0f, VOLUMECTL_FADE_FRAMES);
            } else if (strcmp(direction, DOWN_2) == 0) {
                cri = (beCri *)self->_cri;
                beCri_FadeByID(cri, beMessenger_GetLong(self->_messenger, 0), 1.0f, 0.0f, VOLUMECTL_FADE_FRAMES);
            }
            break;
        }
        if (beMessenger_GetStringCount(self->_messenger) <= 1) break;
        name = beMessenger_GetString(self->_messenger, 1);
        if (strcmp(direction, UP_2) == 0) {
            beCri_FadeByName((beCri *)self->_cri, name, 0.0f, 1.0f, VOLUMECTL_FADE_FRAMES);
        } else if (strcmp(direction, DOWN_2) == 0) {
            beCri_FadeByName((beCri *)self->_cri, name, 1.0f, 0.0f, VOLUMECTL_FADE_FRAMES);
        }
        if (self->_currentBGM != 0 && strcmp(name, (char *)self->_currentBGM) == 0) {
            SetString(&self->_currentBGM, 0);
        }
        break;
    case MESSAGE_VOLUMECTL2:
        if (beMessenger_GetStringCount(self->_messenger) <= 0) return 0;
        if (beMessenger_GetFloatCount(self->_messenger) < 3) return 0;
        name = beMessenger_GetString(self->_messenger, 0);
        from = beMessenger_GetFloat(self->_messenger, 0);
        to = beMessenger_GetFloat(self->_messenger, 1);
        frames = beMessenger_GetFloat(self->_messenger, 2);
        span = Abs(from - to);
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
        beCri_SetFx((beCri *)self->_cri, beMessenger_GetString(self->_messenger, 0));
        break;
    case MESSAGE_GETWORDLIST:
        dataList = (igObjectList *)info->_dataList;
        dataCount = dataList->_count;
        for (dataIndex = 0; dataIndex < dataCount; dataIndex++) {
            beMessenger_AppendString(self->_messenger, NameOf(((beSoundData **)dataList->_data)[dataIndex]->_name));
        }
        break;
    case MESSAGE_ISREADY:
    case MESSAGE_ISALLREADY:
        if (beMessenger_GetStringCount(self->_messenger) <= 0) {
            name = ALL_2;
        } else {
            name = beMessenger_GetString(self->_messenger, 0);
        }
        beMessenger_AppendBool(self->_messenger, beCri_IsReady((beCri *)self->_cri, name));
        break;
    case MESSAGE_ISBGMREADY:
        beMessenger_AppendBool(self->_messenger, beCri_IsReady((beCri *)self->_cri, HandleName(((beCri *)self->_cri)->_hdBGM)));
        break;
    case MESSAGE_ISENVREADY:
        beMessenger_AppendBool(self->_messenger, beCri_IsReady((beCri *)self->_cri, HandleName(((beCri *)self->_cri)->_hdENV)));
        break;
    case MESSAGE_SNDFVOLUME:
        beCri_SetSndfVolume((beCri *)self->_cri, beMessenger_GetInt(self->_messenger, 0));
        break;
    case MESSAGE_ONFREEZE:
        beCri_SetFreezeAudible((beCri *)self->_cri, 0);
        break;
    case MESSAGE_OFFREEZE:
        beCri_SetFreezeAudible((beCri *)self->_cri, 1);
        break;
    case MESSAGE_MAKEBINLIST:
        if (info->_dataType == 0) return 0;
        beMessenger_SendGroup(self->_messenger, STATICINFO, GETINFOLIST);
        if (beMessenger_GetObjectCount(self->_messenger) <= 0) return 0;
        infos = beMessenger_GetObject(self->_messenger, 0);
        fileNames = (igObjectList *)info->_fnameList;
        allocator = AllocatorFor(self);
        {
            NameListRef banks(igStringRefList_Create(allocator));
            GlobalStrRef scratch((igStringObj *)((beSystem *)self->_system)->_globalStrObj);
            for (fileIndex = 0; fileIndex < fileNames->_count; fileIndex++) {
                igStringObj_Set(scratch.p, NameOf(((igNamedObject **)fileNames->_data)[fileIndex]->_name));
                igStringObj_KeepExtension(scratch.p);
                igStringObj_Erase(scratch.p, 0, 1);
                dataType = (char *)info->_dataType;
                if (strcmp(dataType, TextOf(scratch.p)) == 0) {
                    igStringObj_Set(scratch.p, NameOf(((igNamedObject **)fileNames->_data)[fileIndex]->_name));
                    igStringObj_StripDirectory(scratch.p);
                    igStringObj_ToLower(scratch.p);
                    known = false;
                    text = TextOf(scratch.p);
                    if (text == 0) {
                        pooled = 0;
                    } else {
                        pooled = InternString(text);
                    }
                    StringRef bank;
                    bank.p = pooled;
                    for (knownIndex = 0; knownIndex < banks.p->_count; knownIndex++) {
                        if (strcmp(bank.p, StringList_CopyRetained(banks.p, knownIndex).p) == 0) {
                            known = true;
                            break;
                        }
                    }
                    if (known == false) {
                        StringList_AppendRetained(banks.p, StringRef(bank.p));
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
                            ObjectList_AppendRetained((igObjectList *)((beCri *)self->_cri)->_lsBinObjs, object);
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
        beMessenger_AppendBool(self->_messenger, beCri_IsTransferDone((beCri *)self->_cri));
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

int beSound_FindData(beSound *self, beBaseInfoRam *ram, char *name) {
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

int beSound_GetMeta(void)
{
    return g_beSound_metaObject[0];
}
