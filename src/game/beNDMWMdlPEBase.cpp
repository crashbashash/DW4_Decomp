#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"
#include "dw4/igVec3f.h"
#include "dw4/igobject_release.h"

extern "C" int igInsightCore_FindManager(int, int);
extern "C" int igObject_GetAllocator(void *);
extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" int Gap__Core__igObject__vfunc_08__002ff0f0(beNDMWMdlPEBaseInfoWork *);
extern "C" int beMessenger_SendNamed(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendFloat(int, float);
extern "C" int beMessenger_AppendBool(int, bool);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_AppendVec3(...);
extern "C" int beMessenger_AppendObject(...);
extern "C" int beMessenger_ClearObjects(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" void *beMessenger_GetObject(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" int beMessenger_GetString(...);
extern "C" int beMessenger_PushArgContext(...);
extern "C" int beMessenger_PopArgContext(...);
extern "C" int beMessenger_ResolveEnumValue(...);
extern "C" int beBaseInfoRam_StartTimer(...);
extern "C" int beBaseInfoRam_IsTimerExpired(...);
extern "C" int beBaseInfoRam_RemoveTimer(...);
extern "C" beBaseInfoDataList *beBaseInfoDataList_Create(...);
extern "C" beModelCtrlInfoRamData *igProperty_FindByName(int list, int nameField, const char *name);
extern "C" beDataObjInt *igProperty_GetRecord(...);
extern "C" void *igProperty_GetRecordIntList(...);
extern "C" beDataObjBoolList *igProperty_GetRecordArray(...);
extern "C" const char *beDataBase_GetRecordString(int, int, const char *);
extern "C" int StringPool_Allocate(int);
extern "C" int StringPool_Construct(int);
extern "C" int StringPool_Intern(int, const char *);
extern "C" int StringChunk_ReleaseHeader(int, int *);
extern "C" void *igIntList_Create(...);
extern "C" void *igBoolList_Create(...);
extern "C" int List_Reserve(...);
extern "C" int List_InsertWords(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int Matrix44_GetTranslation(...);
extern "C" int strcmp(...);
extern "C" int beNDMWGameRam_CalcMaxPoints(beNDMWGameRam *, int, int, int);
extern "C" int beNDMWGameRam_CalcAttribute(beNDMWGameRam *, int, int, int);
extern "C" beNDMWShinkaObject *beNDMWShinkaObject_CreateInstance(int allocator);
extern "C" int DamageSeq_GetMetaEnum(...);
extern "C" int StatusName_GetMetaEnum(...);
extern "C" int MsgAction_GetMetaEnum(void);

extern "C" void beNDMWShinkaCtrl_Setup(beNDMWShinkaCtrl *self, int insight, int playerNo);
extern "C" void beNDMWShinkaCtrl_BuildFormList(beNDMWShinkaCtrl *self);
extern "C" void beNDMWShinkaObject_Load(beNDMWShinkaObject *self, beNDMWGameRam *gameRam, int playerNo, int form);
extern "C" int beNDMWMdlPEBase_ShowStatusIcon(beNDMWMdlPEBase *self, beBaseInfoRam *ram, const char *iconName, int iconRamNo, int slot, bool restart);
extern "C" void Gap__Bec__beNDMWMdlPEBase__vfunc_46(beNDMWMdlPEBase *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPEBase_OnSequenceChange(beNDMWMdlPEBase *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPEBase_LoadDownData(beNDMWMdlPEBase *self, beBaseInfoRam *ram, beNDMWMdlPEBaseInfoWork *work);
extern "C" void beNDMWMdlPEBase_LoadUpData(beNDMWMdlPEBase *self, beBaseInfoRam *ram, beNDMWMdlPEBaseInfoWork *work);
extern "C" void beNDMWMdlPEBase_RecalcPlayer(beNDMWMdlPEBase *self, beBaseInfoRam *ram, beNDMWMdlPEBaseInfoWork *work);
extern "C" int Gap__Bec__beNDMWMdlPEBase__vfunc_47(beNDMWMdlPEBase *self, beBaseInfoRam *ram, int message);
extern "C" void Gap__Bec__beNDMWMdlPEBaseInfoWork__vfunc_8(beNDMWMdlPEBaseInfoWork *self);
extern "C" int beNDMWMdlPEBaseInfoWork_IsPoisoned(beNDMWMdlPEBaseInfoWork *self);
extern "C" void beNDMWMdlPEBaseInfoWork_CurePoison(beNDMWMdlPEBaseInfoWork *self, beBaseInfoRam *ram);
extern "C" int beNDMWMdlPEBaseInfoWork__GetMeta(void);
extern "C" int beNDMWMdlPEBase__GetMeta(void);

extern "C" int g_beMessenger_metaObject[4];
extern "C" int g_beNDMWGameRam_metaObject[4];
extern "C" int g_beNDMWMdlPEBaseInfoWork_metaObject[4];
extern "C" int g_beNDMWMdlPEBase_metaObject[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" int g_stringPool[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" igVec3f g_vec3Zero;
/* Per status icon: its model, and the open and loop sequences by display slot. */
extern "C" const char *g_statusIconModelNames[];
extern "C" const char *g_statusIconOpenSequences[];
extern "C" const char *g_statusIconLoopSequences[];

extern "C" char DATABASE_12[];
extern "C" char shinka_6[];
extern "C" char GETDATABASE_11[];
extern "C" char GAMERAM_17[];
extern "C" char GETPLAYER_13[];
extern "C" char BASE_ISUSE_5[];
extern "C" char BASE_LEVEL_4[];
extern "C" char DATABASE_3[];
extern "C" char shinka_2[];
extern "C" char GETDATABASE_3[];
extern "C" char NAME_6[];
extern "C" char BASE_SKILL_3[];
extern "C" char ONE_15[];
extern "C" char MODELCTRL_20[];
extern "C" char FIND_SPACE_4[];
extern "C" char GENERATE_14[];
extern "C" char MOVETRANS_2[];
extern "C" char SQ_ERAS_4[];
extern "C" char POISON[];
extern "C" char METERCTRL_5[];
extern "C" char hpmt_3[];
extern "C" char SETPERCENT_4[];
extern "C" char NUMBERCTRL_6[];
extern "C" char hpnm_3[];
extern "C" char SETVALUE_5[];
extern "C" char SQ_DEAD[];
extern "C" char SLEEP[];
extern "C" char SQ_SLEP_2[];
extern "C" char SQ_WAIT_6[];
extern "C" char SQ_STUN[];
extern "C" char STUN[];
extern "C" char BIND[];
extern "C" char ATKDOWN[];
extern "C" char POWDOWN[];
extern "C" char SPEEDUP[];
extern "C" char POWERUP[];
extern "C" char REFRACT[];
extern "C" char METAL[];
extern "C" char GAMERAM_18[];
extern "C" char GETPLAYER_14[];
extern "C" char ATTACKDELAY_3[];
extern "C" char DOWNDATA_3[];
extern "C" char UPDATA_3[];
extern "C" char RECALCPLAYER_7[];
extern "C" char ADDHP_2[];

/* The sixteen species a player can digivolve into, in the order of the BASE_* arrays. */
enum { FORM_DORUMON = 3, FORM_COUNT = 16 };
/* Weapon-type skill levels stored per form in BASE_SKILL: blunt, slash, stab, bash, shot, crush,
 * blast, heal, force. */
enum { SKILL_COUNT = 9 };
/* The StatusName enum: one timer, first-tick flag and icon per status. STATUS_ANY is the icon shown
 * while any of the first eight runs. */
enum {
    STATUS_POISON, STATUS_ATTACKDOWN, STATUS_POWERDOWN, STATUS_BIND, STATUS_REFRACT, STATUS_SPEEDUP,
    STATUS_POWERUP, STATUS_METAL, STATUS_SLEEP, STATUS_STUN, STATUS_RARE, STATUS_ANY, STATUS_ICON_COUNT
};
/* The MsgAction enum: the messages the status handler answers. */
enum {
    MSG_SETPOISON, MSG_SETSLEEP, MSG_SETSTUN, MSG_SETBIND, MSG_SETATTACKDOWN, MSG_SETPOWERDOWN,
    MSG_SETRAREICON, MSG_SETSPEEDUP, MSG_SETPOWERUP, MSG_SETREFRACT, MSG_SETMETAL, MSG_CLEARMETAL,
    MSG_CHECKSTATUS, MSG_CLEARSTATUS, MSG_ALLCLEARSTATUS, MSG_GETPEBASEWORK
};
/* Ranges of the down and up data lists each status fills. */
enum { DOWN_ATTACK = 0, DOWN_POWER = 4, DOWN_METAL = 6, DOWN_DATA_COUNT = 6, UP_SPEED = 0, UP_POWER = 4, UP_REFRACT = 7, UP_DATA_COUNT = 7 };
/* SETPOISON gives a duration in frames; the poison then ticks every two seconds. */
enum { POISON_TICK_FRAMES = 120, POISON_TICK_TIME = 2000000000 };
/* METAL raises its down-data entry by four every ATTACKDELAY * 120 frames. */
enum { METAL_STEP = 4, METAL_DELAY_SCALE = 120 };

/* Timers run in nanoseconds; durations arrive in frames at 60 per second. */
static inline long long FramesToTime(int frames) { return (long long)frames * 1000000000 / 60; }

/* The result igMetaEnum_GetValueByName returns, compared with g_statusSucceeded. */
struct igResult { int value; bool operator==(const igResult &other) const { return value == other.value; } };
extern "C" igResult igMetaEnum_GetValueByName(...);
extern "C" igResult g_statusSucceeded;

/* beModelCtrl's vtable up to its message handler (slot 33). */
class beModelCtrlSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32();
    virtual int handleMessage(beBaseInfoRam *ram, const char *message);
};

/* Stores a new reference to `object` in an object-reference field, releasing the one it held. */
static inline void AssignReference(int &field, igObject *object) {
    igObject *old;
    if (object != 0) object->_refCount = object->_refCount + 1;
    old = (igObject *)field;
    igRelease(old);
    field = (int)object;
}

static inline int OwnAllocator(void *object) {
    int allocator = igObject_GetAllocator(object);
    return g_useOwnerAllocator != 0 ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
}

/* Creates the ram's data list when it has none. */
static inline void EnsureDataList(beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        int allocator = igObject_GetAllocator(ram);
        igSmartPointer<beBaseInfoDataList> created(beBaseInfoDataList_Create(g_useOwnerAllocator != 0 ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
        AssignReference(ram->_dataList, created.p);
    }
}

/* The int list of a player's data-list record `name`. */
static inline igIntList *PlayerIntList(beNDMWGameRam *gameRam, int playerNo, const char *name) {
    beDataObjIntList *record = (beDataObjIntList *)igProperty_GetRecordIntList(((int *)((igIntList *)gameRam->_playerDataListList)->_data)[playerNo], name);
    return (igIntList *)record->_data;
}

/* Element access to the work's int and bool lists, which it holds as object-reference fields. */
static inline int &IntAt(int list, int index) { return ((int *)((igIntList *)list)->_data)[index]; }
static inline unsigned char &BoolAt(int list, int index) { return ((unsigned char *)((igBoolList *)list)->_data)[index]; }
static inline void IntList_Set(igIntList *list, int index, const int &value) {
    if (list->_count != 0 && index >= 0 && index < list->_count) ((int *)list->_data)[index] = value;
}
static inline void BoolList_Set(igBoolList *list, int index, const bool &value) {
    if (list->_count != 0 && index >= 0 && index < list->_count) ((unsigned char *)list->_data)[index] = value;
}
static inline void IntList_Fill(igIntList *list, const int &value) {
    int count = list->_count;
    int *data = (int *)list->_data;
    int i;
    for (i = 0; i < count; i++) data[i] = value;
}
/* IntList_Fill on the list an object-reference field holds, reading the field at each use. */
static inline void IntList_FillField(const int &list, const int &value) {
    int count = ((igIntList *)list)->_count;
    int *data = (int *)((igIntList *)list)->_data;
    int i;
    for (i = 0; i < count; i++) data[i] = value;
}
static inline void BoolList_Fill(igBoolList *list, const bool &value) {
    int count = list->_count;
    unsigned char *data = (unsigned char *)list->_data;
    int i;
    for (i = 0; i < count; i++) data[i] = value;
}
/* Sets the count of the data list a field holds, growing its storage first. */
static inline void List_SetCount(const int &list, int count, int elementSize) {
    if (((igDataList *)list)->_count < count + 1) List_Reserve((igDataList *)list, count, elementSize);
    if (((igDataList *)list)->_capacity >= count) ((igDataList *)list)->_count = count;
    else List_Resize((igDataList *)list, count, elementSize);
}

/* Owning stack reference to each new int list of a work while it is sized and filled; releases the
 * last one on scope exit. */
class IntListRef {
public:
    igIntList *p;
    IntListRef(igIntList *list) : p(list) {}
    void release() { igIntList *held = p; if (held != 0) { --held->_refCount; if ((held->_refCount & 0x7fffff) == 0) igObject_Destroy(held); } }
    ~IntListRef() { igIntList *held = p; if (held != 0) { --held->_refCount; if ((held->_refCount & 0x7fffff) == 0) igObject_Destroy(held); } }
};
/* Same role for the work's bool list. */
class BoolListRef {
public:
    igBoolList *p;
    BoolListRef(igBoolList *list) : p(list) {}
    void release() { igBoolList *held = p; if (held != 0) { --held->_refCount; if ((held->_refCount & 0x7fffff) == 0) igObject_Destroy(held); } }
    ~BoolListRef() { igBoolList *held = p; if (held != 0) { --held->_refCount; if ((held->_refCount & 0x7fffff) == 0) igObject_Destroy(held); } }
};

void beNDMWShinkaCtrl_Setup(beNDMWShinkaCtrl *self, int insight, int playerNo) {
    self->_playerNo = playerNo;
    self->_messenger = igInsightCore_FindManager(insight, g_beMessenger_metaObject[0]);
    self->_gameRam = igInsightCore_FindManager(insight, g_beNDMWGameRam_metaObject[0]);
    beMessenger_SendNamed(self->_messenger, DATABASE_12, shinka_6, 0, GETDATABASE_11);
    AssignReference(self->_dBShinka, (igObject *)beMessenger_GetObject(self->_messenger, 0));
    beMessenger_SelectGroup(self->_messenger, GAMERAM_17);
    beMessenger_AppendInt(self->_messenger, playerNo);
    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_13);
    AssignReference(self->_playerParameter, (igObject *)beMessenger_GetObject(self->_messenger, 0));
    beNDMWShinkaCtrl_BuildFormList(self);
}

void beNDMWShinkaCtrl_BuildFormList(beNDMWShinkaCtrl *self) {
    igObject *object;
    igObjectList *list;
    igObject *retained;
    igTDataList<unsigned char> *isUse;
    igObjectList *forms;
    int count;
    int i;
    int cleared;
    int j;
    int form;

    forms = (igObjectList *)self->_list;
    count = forms->_count;
    for (i = 0; i < count; i++) {
        object = ((igObject **)forms->_data)[i];
        igRelease(object);
    }
    cleared = forms->_count;
    for (j = 0; j < cleared; j++) {
        ((igObject **)forms->_data)[j] = 0;
    }
    forms->_count = 0;
    isUse = (igTDataList<unsigned char> *)igProperty_GetRecordArray(self->_playerParameter, BASE_ISUSE_5)->_data;
    igProperty_GetRecordIntList(self->_playerParameter, BASE_LEVEL_4);
    for (form = 0; form < FORM_COUNT; form++) {
        if (isUse->_data[form] != 0) {
            igSmartPointer<beNDMWShinkaObject> entry(beNDMWShinkaObject_CreateInstance(OwnAllocator(self)));
            igObject *inserted[1];
            beNDMWShinkaObject_Load(entry.p, (beNDMWGameRam *)self->_gameRam, self->_playerNo, form);
            if (form == FORM_DORUMON) {
                list = (igObjectList *)self->_list;
                retained = (igObject *)inserted; /* matching construct: hand spelling — one-element array, the retained word is re-read through its address */
                inserted[0] = entry.p;
                retained = *(igObject **)retained;
                if (retained != 0) {
                    retained->_refCount = retained->_refCount + 1;
                }
                List_InsertWords(list, 0, 1, inserted);
            } else {
                ObjectList_AppendRetained((igObjectList *)self->_list, entry.p);
            }
        }
    }
}

void beNDMWShinkaObject_Load(beNDMWShinkaObject *self, beNDMWGameRam *gameRam, int playerNo, int form) {
    const char *name;
    int pool;
    int token;
    int old;
    int *header;
    int references;
    igIntList *skills;
    self->_id = form;
    if (gameRam->_dBShinka == 0) {
        beMessenger_SendNamed(gameRam->_messenger, DATABASE_3, shinka_2, 0, GETDATABASE_3);
        AssignReference(gameRam->_dBShinka, (igObject *)beMessenger_GetObject(gameRam->_messenger, 0));
    }
    name = beDataBase_GetRecordString(gameRam->_dBShinka, form, NAME_6);
    if (g_stringPool[0] == 0) {
        pool = StringPool_Allocate(16);
        if (pool != 0)
            pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    token = StringPool_Intern(g_stringPool[0], name);
    old = self->_name;
    if (old != 0) {
        header = (int *)(old - 8);
        references = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = references;
        if (references == 0)
            StringChunk_ReleaseHeader(*header, header);
    }
    self->_name = token;
    self->_level = ((int *)PlayerIntList(gameRam, playerNo, BASE_LEVEL_4)->_data)[form];
    self->_hpMax = beNDMWGameRam_CalcMaxPoints(gameRam, playerNo, form, 1);
    self->_mpMax = beNDMWGameRam_CalcMaxPoints(gameRam, playerNo, form, 0);
    self->_tsuyosa = beNDMWGameRam_CalcAttribute(gameRam, playerNo, form, 0);
    self->_mamori = beNDMWGameRam_CalcAttribute(gameRam, playerNo, form, 1);
    self->_kashikosa = beNDMWGameRam_CalcAttribute(gameRam, playerNo, form, 2);
    self->_seishin = beNDMWGameRam_CalcAttribute(gameRam, playerNo, form, 3);
    self->_subayasa = beNDMWGameRam_CalcAttribute(gameRam, playerNo, form, 4);
    skills = PlayerIntList(gameRam, playerNo, BASE_SKILL_3);
    self->_blunt = *(int *)(skills->_data + (form * SKILL_COUNT + 0) * 4);
    self->_slash = *(int *)(skills->_data + (form * SKILL_COUNT + 1) * 4);
    self->_stab = *(int *)(skills->_data + (form * SKILL_COUNT + 2) * 4);
    self->_bash = *(int *)(skills->_data + (form * SKILL_COUNT + 3) * 4);
    self->_shot = *(int *)(skills->_data + (form * SKILL_COUNT + 4) * 4);
    self->_crush = *(int *)(skills->_data + (form * SKILL_COUNT + 5) * 4);
    self->_blast = *(int *)(skills->_data + (form * SKILL_COUNT + 6) * 4);
    self->_heal = *(int *)(skills->_data + (form * SKILL_COUNT + 7) * 4);
    self->_force = *(int *)(skills->_data + (form * SKILL_COUNT + 8) * 4);
}

int beNDMWMdlPEBase_ShowStatusIcon(beNDMWMdlPEBase *self, beBaseInfoRam *ram, const char *iconName, int iconRamNo, int slot, bool restart) {
    beModelCtrlInfoRamData *data;
    beBaseInfoRam *icon;
    igVec3f position, openPosition, movePosition, moveOffset;
    EnsureDataList(ram);
    data = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ONE_15);
    Matrix44_GetTranslation(((igTransform *)data->_node)->_m, &position);
    if (iconRamNo == -1) {
        beMessenger_SendNamed(self->_messenger, MODELCTRL_20, iconName, -1, FIND_SPACE_4);
        if (beMessenger_GetObjectCount(self->_messenger) == 0) goto fail;
        icon = (beBaseInfoRam *)beMessenger_GetObject(self->_messenger, 0);
        beMessenger_SelectReceivers(self->_messenger, MODELCTRL_20, iconName, icon->_ramNo);
        beMessenger_AppendString(self->_messenger, g_statusIconOpenSequences[slot]);
        openPosition = position;
        beMessenger_AppendVec3(self->_messenger, &openPosition);
        beMessenger_DispatchSelected(self->_messenger, GENERATE_14);
        return icon->_ramNo;
    }
    if (restart) {
        beMessenger_SendNamed(self->_messenger, MODELCTRL_20, iconName, iconRamNo, g_statusIconLoopSequences[slot]);
    }
    beMessenger_SelectReceivers(self->_messenger, MODELCTRL_20, iconName, iconRamNo);
    movePosition = position;
    beMessenger_AppendVec3(self->_messenger, &movePosition);
    moveOffset = g_vec3Zero;
    beMessenger_AppendVec3(self->_messenger, &moveOffset);
    beMessenger_DispatchSelected(self->_messenger, MOVETRANS_2);
    return iconRamNo;
fail:
    return -1;
}

void Gap__Bec__beNDMWMdlPEBase__vfunc_46(beNDMWMdlPEBase *self, beBaseInfoRam *ram) {
    beNDMWMdlPEBaseInfoWork *work;
    int damageSeq;
    EnsureDataList(ram);
    work = (beNDMWMdlPEBaseInfoWork *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ONE_15)->_work;
    if (work->_timerList != 0) {
        if (((beDataObjInt *)work->_hp)->_data == 0) {
            int i;
            for (i = 0; i < STATUS_ICON_COUNT; i++) {
                int iconRamNo = IntAt(work->_dispRamNoList, i);
                if (iconRamNo != -1) beMessenger_SendNamed(self->_messenger, MODELCTRL_20, g_statusIconModelNames[i], iconRamNo, SQ_ERAS_4);
            }
            IntList_Fill((igIntList *)work->_timerList, 0);
            IntList_Fill((igIntList *)work->_dispRamNoList, -1);
            return;
        }
        if (work->_messenger == 0) work->_messenger = self->_messenger;
        if (work->_isOnCtrl != 0 && IntAt(work->_timerList, STATUS_POISON) != 0) {
            if (BoolAt(work->_isFirstList, STATUS_POISON) != 0) {
                beBaseInfoRam_StartTimer(ram, POISON, POISON_TICK_TIME);
                {
                    int ticks = IntAt(work->_timerList, STATUS_POISON) - 1;
                    IntList_Set((igIntList *)work->_timerList, STATUS_POISON, ticks);
                }
                BoolList_Set((igBoolList *)work->_isFirstList, STATUS_POISON, false);
            }
            if (beBaseInfoRam_IsTimerExpired(ram, POISON) != 0) {
                beDataObjInt *hp = (beDataObjInt *)work->_hp;
                int left = hp->_data - work->_poisonDamage;
                hp->_data = left >= 0 ? left : 0;
                if (work->_isPlayer != 0) {
                    beMessenger_SelectReceivers(self->_messenger, METERCTRL_5, hpmt_3, ram->_ramNo);
                    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)((beDataObjInt *)work->_hp)->_data / (float)((beDataObjInt *)work->_mHp)->_data);
                    beMessenger_DispatchSelected(self->_messenger, SETPERCENT_4);
                    beMessenger_SelectReceivers(self->_messenger, NUMBERCTRL_6, hpnm_3, ram->_ramNo);
                    beMessenger_AppendInt(self->_messenger, ((beDataObjInt *)work->_hp)->_data);
                    beMessenger_DispatchSelected(self->_messenger, SETVALUE_5);
                }
                hp = (beDataObjInt *)work->_hp;
                if (hp->_data <= 0) {
                    if (work->_isPlayer != 0) {
                        ((beModelCtrlSlots *)self)->handleMessage(ram, SQ_DEAD);
                        beBaseInfoRam_RemoveTimer(ram, POISON);
                        IntList_Set((igIntList *)work->_timerList, STATUS_POISON, 0);
                    } else {
                        hp->_data = 1;
                        beBaseInfoRam_RemoveTimer(ram, POISON);
                        IntList_Set((igIntList *)work->_timerList, STATUS_POISON, 0);
                    }
                } else {
                    {
                    int ticks = IntAt(work->_timerList, STATUS_POISON) - 1;
                    IntList_Set((igIntList *)work->_timerList, STATUS_POISON, ticks);
                }
                    if (IntAt(work->_timerList, STATUS_POISON) <= 0) {
                        beBaseInfoRam_RemoveTimer(ram, POISON);
                        IntList_Set((igIntList *)work->_timerList, STATUS_POISON, 0);
                    } else {
                        beBaseInfoRam_StartTimer(ram, POISON, POISON_TICK_TIME);
                    }
                }
            }
        }
        if (work->_isOnCtrl != 0 && IntAt(work->_timerList, STATUS_SLEEP) != 0) {
            if (BoolAt(work->_isFirstList, STATUS_SLEEP) != 0) {
                beBaseInfoRam_StartTimer(ram, SLEEP, FramesToTime(IntAt(work->_timerList, STATUS_SLEEP)));
                if (strcmp((const char *)work->_seqCodeName, SQ_SLEP_2) != 0) ((beModelCtrlSlots *)self)->handleMessage(ram, SQ_SLEP_2);
                BoolList_Set((igBoolList *)work->_isFirstList, STATUS_SLEEP, false);
            }
            if (beBaseInfoRam_IsTimerExpired(ram, SLEEP) != 0) {
                ((beModelCtrlSlots *)self)->handleMessage(ram, SQ_WAIT_6);
                beBaseInfoRam_RemoveTimer(ram, SLEEP);
                IntList_Set((igIntList *)work->_timerList, STATUS_SLEEP, 0);
            }
        }
        if (work->_isOnCtrl != 0 && IntAt(work->_timerList, STATUS_STUN) != 0 && strcmp((const char *)work->_seqCodeName, SQ_STUN) == 0) {
            if (BoolAt(work->_isFirstList, STATUS_STUN) != 0) {
                beBaseInfoRam_StartTimer(ram, STUN, FramesToTime(IntAt(work->_timerList, STATUS_STUN)));
                BoolList_Set((igBoolList *)work->_isFirstList, STATUS_STUN, false);
            }
            if (beBaseInfoRam_IsTimerExpired(ram, STUN) != 0) {
                IntList_Set((igIntList *)work->_timerList, STATUS_STUN, 0);
                beBaseInfoRam_RemoveTimer(ram, STUN);
                ((beModelCtrlSlots *)self)->handleMessage(ram, SQ_WAIT_6);
            }
        }
        if (work->_isOnCtrl != 0 && IntAt(work->_timerList, STATUS_BIND) != 0) {
            if (BoolAt(work->_isFirstList, STATUS_BIND) != 0) {
                beBaseInfoRam_StartTimer(ram, BIND, FramesToTime(IntAt(work->_timerList, STATUS_BIND)));
                BoolList_Set((igBoolList *)work->_isFirstList, STATUS_BIND, false);
            }
            if (beBaseInfoRam_IsTimerExpired(ram, BIND) != 0) {
                beBaseInfoRam_RemoveTimer(ram, BIND);
                IntList_Set((igIntList *)work->_timerList, STATUS_BIND, 0);
                ((beModelCtrlSlots *)self)->handleMessage(ram, SQ_WAIT_6);
            } else {
                if (!(igMetaEnum_GetValueByName(DamageSeq_GetMetaEnum(), (const char *)work->_seqCodeName, &damageSeq) == g_statusSucceeded)) {
                    igObjectList *moves = (igObjectList *)work->_moveObjectList;
                    int count = moves->_count;
                    int i;
                    for (i = 0; i < count; i++) {
                        if (i != 1) {
                            beModelCtrlMoveObject *move = ((beModelCtrlMoveObject **)moves->_data)[i];
                            move->_isRun = 0;
                            move->_speed = 0;
                        }
                    }
                }
            }
        }
        if (work->_isOnCtrl != 0 && IntAt(work->_timerList, STATUS_ATTACKDOWN) != 0) {
            if (BoolAt(work->_isFirstList, STATUS_ATTACKDOWN) != 0) {
                beBaseInfoRam_StartTimer(ram, ATKDOWN, FramesToTime(IntAt(work->_timerList, STATUS_ATTACKDOWN)));
                BoolList_Set((igBoolList *)work->_isFirstList, STATUS_ATTACKDOWN, false);
            }
            if (beBaseInfoRam_IsTimerExpired(ram, ATKDOWN) != 0) {
                beBaseInfoRam_RemoveTimer(ram, ATKDOWN);
                IntList_Set((igIntList *)work->_timerList, STATUS_ATTACKDOWN, 0);
                IntList_Set((igIntList *)work->_downDataList, DOWN_ATTACK + 0, 0);
                IntList_Set((igIntList *)work->_downDataList, DOWN_ATTACK + 1, 0);
                IntList_Set((igIntList *)work->_downDataList, DOWN_ATTACK + 2, 0);
                IntList_Set((igIntList *)work->_downDataList, DOWN_ATTACK + 3, 0);
                beNDMWMdlPEBase_RecalcPlayer(self, ram, work);
            }
        }
        if (work->_isOnCtrl != 0 && IntAt(work->_timerList, STATUS_POWERDOWN) != 0) {
            if (BoolAt(work->_isFirstList, STATUS_POWERDOWN) != 0) {
                beBaseInfoRam_StartTimer(ram, POWDOWN, FramesToTime(IntAt(work->_timerList, STATUS_POWERDOWN)));
                BoolList_Set((igBoolList *)work->_isFirstList, STATUS_POWERDOWN, false);
            }
            if (beBaseInfoRam_IsTimerExpired(ram, POWDOWN) != 0) {
                beBaseInfoRam_RemoveTimer(ram, POWDOWN);
                IntList_Set((igIntList *)work->_timerList, STATUS_POWERDOWN, 0);
                IntList_Set((igIntList *)work->_downDataList, DOWN_POWER + 0, 0);
                IntList_Set((igIntList *)work->_downDataList, DOWN_POWER + 1, 0);
                beNDMWMdlPEBase_RecalcPlayer(self, ram, work);
            }
        }
        if (work->_isOnCtrl != 0 && IntAt(work->_timerList, STATUS_SPEEDUP) != 0) {
            if (BoolAt(work->_isFirstList, STATUS_SPEEDUP) != 0) {
                beBaseInfoRam_StartTimer(ram, SPEEDUP, FramesToTime(IntAt(work->_timerList, STATUS_SPEEDUP)));
                BoolList_Set((igBoolList *)work->_isFirstList, STATUS_SPEEDUP, false);
            }
            if (beBaseInfoRam_IsTimerExpired(ram, SPEEDUP) != 0) {
                beBaseInfoRam_RemoveTimer(ram, SPEEDUP);
                IntList_Set((igIntList *)work->_timerList, STATUS_SPEEDUP, 0);
                IntList_Set((igIntList *)work->_upDataList, UP_SPEED + 0, 0);
                IntList_Set((igIntList *)work->_upDataList, UP_SPEED + 1, 0);
                IntList_Set((igIntList *)work->_upDataList, UP_SPEED + 2, 0);
                IntList_Set((igIntList *)work->_upDataList, UP_SPEED + 3, 0);
                beNDMWMdlPEBase_RecalcPlayer(self, ram, work);
            }
        }
        if (work->_isOnCtrl != 0 && IntAt(work->_timerList, STATUS_POWERUP) != 0) {
            if (BoolAt(work->_isFirstList, STATUS_POWERUP) != 0) {
                beBaseInfoRam_StartTimer(ram, POWERUP, FramesToTime(IntAt(work->_timerList, STATUS_POWERUP)));
                BoolList_Set((igBoolList *)work->_isFirstList, STATUS_POWERUP, false);
            }
            if (beBaseInfoRam_IsTimerExpired(ram, POWERUP) != 0) {
                beBaseInfoRam_RemoveTimer(ram, POWERUP);
                IntList_Set((igIntList *)work->_timerList, STATUS_POWERUP, 0);
                IntList_Set((igIntList *)work->_upDataList, UP_POWER + 0, 0);
                IntList_Set((igIntList *)work->_upDataList, UP_POWER + 1, 0);
                IntList_Set((igIntList *)work->_upDataList, UP_POWER + 2, 0);
                beNDMWMdlPEBase_RecalcPlayer(self, ram, work);
            }
        }
        if (work->_isOnCtrl != 0 && IntAt(work->_timerList, STATUS_REFRACT) != 0) {
            if (BoolAt(work->_isFirstList, STATUS_REFRACT) != 0) {
                beBaseInfoRam_StartTimer(ram, REFRACT, FramesToTime(IntAt(work->_timerList, STATUS_REFRACT)));
                BoolList_Set((igBoolList *)work->_isFirstList, STATUS_REFRACT, false);
            }
            if (beBaseInfoRam_IsTimerExpired(ram, REFRACT) != 0) {
                beBaseInfoRam_RemoveTimer(ram, REFRACT);
                IntList_Set((igIntList *)work->_timerList, STATUS_REFRACT, 0);
                IntList_Set((igIntList *)work->_upDataList, UP_REFRACT + 0, 0);
                IntList_Set((igIntList *)work->_upDataList, UP_REFRACT + 1, 0);
                IntList_Set((igIntList *)work->_upDataList, UP_REFRACT + 2, 0);
                IntList_Set((igIntList *)work->_upDataList, UP_REFRACT + 3, 0);
                beNDMWMdlPEBase_RecalcPlayer(self, ram, work);
            }
        }
        if (work->_isOnCtrl != 0 && IntAt(work->_timerList, STATUS_METAL) != 0) {
            if (BoolAt(work->_isFirstList, STATUS_METAL) != 0) {
                IntList_Set((igIntList *)work->_downDataList, DOWN_METAL, 0);
                beBaseInfoRam_StartTimer(ram, METAL, 0);
                BoolList_Set((igBoolList *)work->_isFirstList, STATUS_METAL, false);
            }
            if (beBaseInfoRam_IsTimerExpired(ram, METAL) != 0) {
                int delay;
                {
                    int metal = IntAt(work->_downDataList, DOWN_METAL) + METAL_STEP;
                    IntList_Set((igIntList *)work->_downDataList, DOWN_METAL, metal);
                }
                beMessenger_SelectGroup(self->_messenger, GAMERAM_18);
                beMessenger_AppendInt(self->_messenger, ram->_ramNo);
                beMessenger_DispatchSelected(self->_messenger, GETPLAYER_14);
                delay = ((beDataObjInt *)igProperty_GetRecord((int)beMessenger_GetObject(self->_messenger, 0), ATTACKDELAY_3))->_data * METAL_DELAY_SCALE;
                beBaseInfoRam_StartTimer(ram, METAL, FramesToTime(delay));
                beNDMWMdlPEBase_RecalcPlayer(self, ram, work);
            }
        }
        {
            bool anyShown = false;
            int slot = 0;
            int i = 0;
            do {
                int iconRamNo;
                if (i == STATUS_ANY) IntList_Set((igIntList *)work->_timerList, i, anyShown);
                if (IntAt(work->_timerList, i) != 0) {
                    if (i <= STATUS_METAL) {
                        bool moved = false;
                        if (slot != IntAt(work->_dispPosNoList, i)) {
                            IntList_Set((igIntList *)work->_dispPosNoList, i, slot);
                            moved = true;
                        }
                        iconRamNo = beNDMWMdlPEBase_ShowStatusIcon(self, ram, g_statusIconModelNames[i], IntAt(work->_dispRamNoList, i), slot, moved);
                        slot++;
                    } else if (i != STATUS_RARE) {
                        iconRamNo = beNDMWMdlPEBase_ShowStatusIcon(self, ram, g_statusIconModelNames[i], IntAt(work->_dispRamNoList, i), 0, 0);
                    } else {
                        iconRamNo = beNDMWMdlPEBase_ShowStatusIcon(self, ram, g_statusIconModelNames[i], IntAt(work->_dispRamNoList, i), IntAt(work->_timerList, STATUS_RARE) - 1, 0);
                    }
                    IntList_Set((igIntList *)work->_dispRamNoList, i, iconRamNo);
                    if (i <= STATUS_METAL) anyShown = true;
                } else {
                    int iconRamNo = IntAt(work->_dispRamNoList, i);
                    if (iconRamNo != -1) {
                        beMessenger_SendNamed(self->_messenger, MODELCTRL_20, g_statusIconModelNames[i], iconRamNo, SQ_ERAS_4);
                        IntList_Set((igIntList *)work->_dispRamNoList, i, -1);
                    }
                }
                i++;
            } while (i < STATUS_ICON_COUNT);
        }
    }
}

void beNDMWMdlPEBase_OnSequenceChange(beNDMWMdlPEBase *self, beBaseInfoRam *ram) {
    beNDMWMdlPEBaseInfoWork *work;
    EnsureDataList(ram);
    work = (beNDMWMdlPEBaseInfoWork *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ONE_15)->_work;
    if (work->_dispRamNoList != 0) {
        if (((igIntList *)work->_dispRamNoList)->_count != 0 && ((beDataObjInt *)work->_hp)->_data == 0) {
            int i;
            for (i = 0; i < STATUS_ICON_COUNT; i++) {
                int iconRamNo = IntAt(work->_dispRamNoList, i);
                if (iconRamNo != -1) beMessenger_SendNamed(self->_messenger, MODELCTRL_20, g_statusIconModelNames[i], iconRamNo, SQ_ERAS_4);
            }
            IntList_FillField(work->_timerList, 0);
            IntList_FillField(work->_dispRamNoList, -1);
            return;
        }
        if (((igIntList *)work->_timerList)->_count != 0) {
            if (IntAt(work->_timerList, STATUS_SLEEP) != 0 && strcmp((const char *)work->_seqCodeName, SQ_SLEP_2) != 0) {
                beBaseInfoRam_RemoveTimer(ram, SLEEP);
                BoolList_Set((igBoolList *)work->_isFirstList, STATUS_SLEEP, false);
                IntList_Set((igIntList *)work->_timerList, STATUS_SLEEP, 0);
            }
            if (IntAt(work->_timerList, STATUS_STUN) != 0) {
                if (strcmp((const char *)work->_seqCodeName, SQ_WAIT_6) == 0) {
                    ((beModelCtrlSlots *)self)->handleMessage(ram, SQ_STUN);
                    return;
                }
                if (strcmp((const char *)work->_seqCodeName, SQ_STUN) != 0) {
                    beBaseInfoRam_RemoveTimer(ram, STUN);
                    BoolList_Set((igBoolList *)work->_isFirstList, STATUS_STUN, false);
                    IntList_Set((igIntList *)work->_timerList, STATUS_STUN, 0);
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_20, g_statusIconModelNames[STATUS_STUN], IntAt(work->_dispRamNoList, STATUS_STUN), SQ_ERAS_4);
                }
            }
        }
    }
}

void beNDMWMdlPEBase_LoadDownData(beNDMWMdlPEBase *self, beBaseInfoRam *ram, beNDMWMdlPEBaseInfoWork *work) {
    if (work->_isPlayer != 0) {
        beMessenger_PushArgContext(self->_messenger);
        beMessenger_SelectGroup(self->_messenger, GAMERAM_18);
        beMessenger_AppendInt(self->_messenger, ram->_ramNo);
        beMessenger_DispatchSelected(self->_messenger, GETPLAYER_14);
        AssignReference(work->_downDataList, (igObject *)((beDataObjIntList *)igProperty_GetRecordIntList(beMessenger_GetObject(self->_messenger, 0), DOWNDATA_3))->_data);
        beMessenger_PopArgContext(self->_messenger);
        return;
    }
    {
        int ownAllocator;
        ownAllocator = igObject_GetAllocator(self);
        /* An enemy starts from zeroes, owned by the stack reference until the work holds its own. */
        IntListRef created((igIntList *)igIntList_Create(g_useOwnerAllocator != 0 ? ownAllocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
        if (created.p->_count < DOWN_DATA_COUNT + 1) List_Reserve(created.p, DOWN_DATA_COUNT, sizeof(int));
        if (created.p->_capacity >= DOWN_DATA_COUNT) created.p->_count = DOWN_DATA_COUNT;
        else List_Resize(created.p, DOWN_DATA_COUNT, sizeof(int));
        IntList_Fill(created.p, 0);
        AssignReference(work->_downDataList, created.p);
    }
}

void beNDMWMdlPEBase_LoadUpData(beNDMWMdlPEBase *self, beBaseInfoRam *ram, beNDMWMdlPEBaseInfoWork *work) {
    if (work->_isPlayer != 0) {
        beMessenger_PushArgContext(self->_messenger);
        beMessenger_SelectGroup(self->_messenger, GAMERAM_18);
        beMessenger_AppendInt(self->_messenger, ram->_ramNo);
        beMessenger_DispatchSelected(self->_messenger, GETPLAYER_14);
        AssignReference(work->_upDataList, (igObject *)((beDataObjIntList *)igProperty_GetRecordIntList(beMessenger_GetObject(self->_messenger, 0), UPDATA_3))->_data);
        beMessenger_PopArgContext(self->_messenger);
        return;
    }
    {
        int ownAllocator;
        ownAllocator = igObject_GetAllocator(self);
        /* An enemy starts from zeroes, owned by the stack reference until the work holds its own. */
        IntListRef created((igIntList *)igIntList_Create(g_useOwnerAllocator != 0 ? ownAllocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
        if (created.p->_count < UP_DATA_COUNT + 1) List_Reserve(created.p, UP_DATA_COUNT, sizeof(int));
        if (created.p->_capacity >= UP_DATA_COUNT) created.p->_count = UP_DATA_COUNT;
        else List_Resize(created.p, UP_DATA_COUNT, sizeof(int));
        IntList_Fill(created.p, 0);
        AssignReference(work->_upDataList, created.p);
    }
}

void beNDMWMdlPEBase_RecalcPlayer(beNDMWMdlPEBase *self, beBaseInfoRam *ram, beNDMWMdlPEBaseInfoWork *work) {
    if (work->_isPlayer != 0) {
        beMessenger_PushArgContext(self->_messenger);
        beMessenger_SelectGroup(self->_messenger, GAMERAM_18);
        beMessenger_AppendInt(self->_messenger, ram->_ramNo);
        beMessenger_DispatchSelected(self->_messenger, RECALCPLAYER_7);
        beMessenger_SelectGroup(self->_messenger, GAMERAM_18);
        beMessenger_AppendInt(self->_messenger, ram->_ramNo);
        beMessenger_AppendInt(self->_messenger, 0);
        beMessenger_DispatchSelected(self->_messenger, ADDHP_2);
        beMessenger_PopArgContext(self->_messenger);
    }
}

int Gap__Bec__beNDMWMdlPEBase__vfunc_47(beNDMWMdlPEBase *self, beBaseInfoRam *ram, int message) {
    beNDMWMdlPEBaseInfoWork *work;
    int action;
    EnsureDataList(ram);
    work = (beNDMWMdlPEBaseInfoWork *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ONE_15)->_work;
    action = beMessenger_ResolveEnumValue(self->_messenger, MsgAction_GetMetaEnum(), message);
    switch (action) {
    default:
        if (work != 0 && work->_dispRamNoList == 0) {
            IntListRef intList(0);
            BoolListRef boolList(0);
            int allocator;
            allocator = OwnAllocator(self);
            intList.release();
            intList.p = (igIntList *)igIntList_Create(allocator);
            AssignReference(work->_dispRamNoList, intList.p);
            List_SetCount(work->_dispRamNoList, STATUS_ICON_COUNT, sizeof(int));
            IntList_FillField(work->_dispRamNoList, -1);
            allocator = OwnAllocator(self);
            intList.release();
            intList.p = (igIntList *)igIntList_Create(allocator);
            AssignReference(work->_dispPosNoList, intList.p);
            List_SetCount(work->_dispPosNoList, STATUS_ICON_COUNT, sizeof(int));
            IntList_FillField(work->_dispPosNoList, -1);
            allocator = OwnAllocator(self);
            intList.release();
            intList.p = (igIntList *)igIntList_Create(allocator);
            AssignReference(work->_timerList, intList.p);
            List_SetCount(work->_timerList, STATUS_ICON_COUNT, sizeof(int));
            IntList_FillField(work->_timerList, 0);
            allocator = OwnAllocator(self);
            boolList.release();
            boolList.p = (igBoolList *)igBoolList_Create(allocator);
            AssignReference(work->_isFirstList, boolList.p);
            List_SetCount(work->_isFirstList, STATUS_ANY, sizeof(bool));
            BoolList_Fill((igBoolList *)work->_isFirstList, false);
        }
        break;
    case MSG_CHECKSTATUS:
    case MSG_CLEARSTATUS:
        break;
    case -1:
        return 0;
    }
    switch (action) {
    case MSG_GETPEBASEWORK:
        if (work != 0) {
            beMessenger_ClearObjects(self->_messenger);
            beMessenger_AppendObject(self->_messenger, ram);
            beMessenger_AppendObject(self->_messenger, work);
        }
        return 1;
    case MSG_SETPOISON:
        if (work != 0) {
            int ticks = beMessenger_GetInt(self->_messenger, 0) / POISON_TICK_FRAMES + 1;
            IntList_Set((igIntList *)work->_timerList, STATUS_POISON, ticks);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_POISON, true);
            work->_poisonDamage = beMessenger_GetInt(self->_messenger, 1);
            if (beMessenger_GetIntCount(self->_messenger) == 3) work->_poisonEndurance = beMessenger_GetInt(self->_messenger, 2);
        }
        return 1;
    case MSG_SETSLEEP:
        if (work != 0) {
            int frames = beMessenger_GetInt(self->_messenger, 0);
            IntList_Set((igIntList *)work->_timerList, STATUS_SLEEP, frames);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_SLEEP, true);
        }
        return 1;
    case MSG_SETSTUN:
        if (work != 0) {
            int frames = beMessenger_GetInt(self->_messenger, 0);
            IntList_Set((igIntList *)work->_timerList, STATUS_STUN, frames);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_STUN, true);
        }
        return 1;
    case MSG_SETBIND:
        if (work != 0) {
            int frames = beMessenger_GetInt(self->_messenger, 0);
            IntList_Set((igIntList *)work->_timerList, STATUS_BIND, frames);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_BIND, true);
        }
        return 1;
    case MSG_SETATTACKDOWN:
        if (work != 0) {
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_ATTACKDOWN, true);
            {
                int frames = beMessenger_GetInt(self->_messenger, 0);
                IntList_Set((igIntList *)work->_timerList, STATUS_ATTACKDOWN, frames);
            }
            int value0 = beMessenger_GetInt(self->_messenger, 1);
            int value1 = beMessenger_GetInt(self->_messenger, 2);
            int value2 = beMessenger_GetInt(self->_messenger, 3);
            int value3 = beMessenger_GetInt(self->_messenger, 4);
            if (work->_downDataList == 0) beNDMWMdlPEBase_LoadDownData(self, ram, work);
            IntList_Set((igIntList *)work->_downDataList, DOWN_ATTACK + 0, value0);
            IntList_Set((igIntList *)work->_downDataList, DOWN_ATTACK + 1, value1);
            IntList_Set((igIntList *)work->_downDataList, DOWN_ATTACK + 2, value2);
            IntList_Set((igIntList *)work->_downDataList, DOWN_ATTACK + 3, value3);
            beNDMWMdlPEBase_RecalcPlayer(self, ram, work);
        }
        return 1;
    case MSG_SETPOWERDOWN:
        if (work != 0) {
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_POWERDOWN, true);
            {
                int frames = beMessenger_GetInt(self->_messenger, 0);
                IntList_Set((igIntList *)work->_timerList, STATUS_POWERDOWN, frames);
            }
            int value0 = beMessenger_GetInt(self->_messenger, 1);
            int value1 = beMessenger_GetInt(self->_messenger, 2);
            if (work->_downDataList == 0) beNDMWMdlPEBase_LoadDownData(self, ram, work);
            IntList_Set((igIntList *)work->_downDataList, DOWN_POWER + 0, value0);
            IntList_Set((igIntList *)work->_downDataList, DOWN_POWER + 1, value1);
            beNDMWMdlPEBase_RecalcPlayer(self, ram, work);
        }
        return 1;
    case MSG_SETSPEEDUP:
        if (work != 0) {
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_SPEEDUP, true);
            {
                int frames = beMessenger_GetInt(self->_messenger, 0);
                IntList_Set((igIntList *)work->_timerList, STATUS_SPEEDUP, frames);
            }
            int value0 = beMessenger_GetInt(self->_messenger, 1);
            int value1 = beMessenger_GetInt(self->_messenger, 2);
            int value2 = beMessenger_GetInt(self->_messenger, 3);
            int value3 = beMessenger_GetInt(self->_messenger, 4);
            if (work->_upDataList == 0) beNDMWMdlPEBase_LoadUpData(self, ram, work);
            IntList_Set((igIntList *)work->_upDataList, UP_SPEED + 0, value0);
            IntList_Set((igIntList *)work->_upDataList, UP_SPEED + 1, value1);
            IntList_Set((igIntList *)work->_upDataList, UP_SPEED + 2, value2);
            IntList_Set((igIntList *)work->_upDataList, UP_SPEED + 3, value3);
            beNDMWMdlPEBase_RecalcPlayer(self, ram, work);
        }
        return 1;
    case MSG_SETPOWERUP:
        if (work != 0) {
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_POWERUP, true);
            {
                int frames = beMessenger_GetInt(self->_messenger, 0);
                IntList_Set((igIntList *)work->_timerList, STATUS_POWERUP, frames);
            }
            int value0 = beMessenger_GetInt(self->_messenger, 1);
            int value1 = beMessenger_GetInt(self->_messenger, 2);
            int value2 = beMessenger_GetInt(self->_messenger, 3);
            if (work->_upDataList == 0) beNDMWMdlPEBase_LoadUpData(self, ram, work);
            IntList_Set((igIntList *)work->_upDataList, UP_POWER + 0, value0);
            IntList_Set((igIntList *)work->_upDataList, UP_POWER + 1, value1);
            IntList_Set((igIntList *)work->_upDataList, UP_POWER + 2, value2);
            beNDMWMdlPEBase_RecalcPlayer(self, ram, work);
        }
        return 1;
    case MSG_SETREFRACT:
        if (work != 0) {
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_REFRACT, true);
            {
                int frames = beMessenger_GetInt(self->_messenger, 0);
                IntList_Set((igIntList *)work->_timerList, STATUS_REFRACT, frames);
            }
            int value0 = beMessenger_GetInt(self->_messenger, 1);
            int value1 = beMessenger_GetInt(self->_messenger, 2);
            int value2 = beMessenger_GetInt(self->_messenger, 3);
            int value3 = beMessenger_GetInt(self->_messenger, 4);
            if (work->_upDataList == 0) beNDMWMdlPEBase_LoadUpData(self, ram, work);
            IntList_Set((igIntList *)work->_upDataList, UP_REFRACT + 0, value0);
            IntList_Set((igIntList *)work->_upDataList, UP_REFRACT + 1, value1);
            IntList_Set((igIntList *)work->_upDataList, UP_REFRACT + 2, value2);
            IntList_Set((igIntList *)work->_upDataList, UP_REFRACT + 3, value3);
            beNDMWMdlPEBase_RecalcPlayer(self, ram, work);
        }
        return 1;
    case MSG_SETMETAL:
        if (work != 0) {
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_METAL, true);
            IntList_Set((igIntList *)work->_timerList, STATUS_METAL, 1);
            if (work->_downDataList == 0) beNDMWMdlPEBase_LoadDownData(self, ram, work);
        }
        return 1;
    case MSG_CLEARMETAL:
        if (work != 0) {
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_METAL, false);
            IntList_Set((igIntList *)work->_timerList, STATUS_METAL, 0);
            if (work->_downDataList != 0) {
                IntList_Set((igIntList *)work->_downDataList, DOWN_METAL, 0);
            }
        }
        return 1;
    case MSG_SETRAREICON:
        if (work != 0) {
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_RARE, true);
            {
                int frames = beMessenger_GetInt(self->_messenger, 0);
                IntList_Set((igIntList *)work->_timerList, STATUS_RARE, frames);
            }
        }
        return 1;
    case MSG_CHECKSTATUS: {
        int status;
        bool running = false;
        if (work != 0 && work->_dispRamNoList != 0 && work->_timerList != 0) {
            const char *name = (const char *)beMessenger_GetString(self->_messenger, 0);
            if (igMetaEnum_GetValueByName(StatusName_GetMetaEnum(), name, &status) == g_statusSucceeded && IntAt(work->_timerList, status) != 0) running = true;
        }
        beMessenger_AppendBool(self->_messenger, running);
        return 1;
    }
    case MSG_ALLCLEARSTATUS:
        if (work != 0 && work->_dispRamNoList != 0) {
            beBaseInfoRam_RemoveTimer(ram, POISON);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_POISON, false);
            IntList_Set((igIntList *)work->_timerList, STATUS_POISON, 0);
            beBaseInfoRam_RemoveTimer(ram, ATKDOWN);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_ATTACKDOWN, false);
            IntList_Set((igIntList *)work->_timerList, STATUS_ATTACKDOWN, 0);
            beBaseInfoRam_RemoveTimer(ram, POWDOWN);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_POWERDOWN, false);
            IntList_Set((igIntList *)work->_timerList, STATUS_POWERDOWN, 0);
            beBaseInfoRam_RemoveTimer(ram, SPEEDUP);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_SPEEDUP, false);
            IntList_Set((igIntList *)work->_timerList, STATUS_SPEEDUP, 0);
            beBaseInfoRam_RemoveTimer(ram, POWERUP);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_POWERUP, false);
            IntList_Set((igIntList *)work->_timerList, STATUS_POWERUP, 0);
            beBaseInfoRam_RemoveTimer(ram, REFRACT);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_REFRACT, false);
            IntList_Set((igIntList *)work->_timerList, STATUS_REFRACT, 0);
            if (work->_upDataList != 0) { IntList_Fill((igIntList *)work->_upDataList, 0); }
            if (work->_downDataList != 0) { IntList_Fill((igIntList *)work->_downDataList, 0); }
            if (work->_upDataList != 0 || work->_downDataList != 0) beNDMWMdlPEBase_RecalcPlayer(self, ram, work);
        }
        /* ALLCLEARSTATUS goes on to clear what CLEARSTATUS clears */
    case MSG_CLEARSTATUS:
        if (work != 0 && work->_dispRamNoList != 0) {
            beBaseInfoRam_RemoveTimer(ram, SLEEP);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_SLEEP, false);
            IntList_Set((igIntList *)work->_timerList, STATUS_SLEEP, 0);
            beBaseInfoRam_RemoveTimer(ram, STUN);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_STUN, false);
            IntList_Set((igIntList *)work->_timerList, STATUS_STUN, 0);
            beBaseInfoRam_RemoveTimer(ram, BIND);
            BoolList_Set((igBoolList *)work->_isFirstList, STATUS_BIND, false);
            IntList_Set((igIntList *)work->_timerList, STATUS_BIND, 0);
            ((beModelCtrlSlots *)self)->handleMessage(ram, SQ_WAIT_6);
        }
        return 1;
    default:
        return 0;
    }
}

void Gap__Bec__beNDMWMdlPEBaseInfoWork__vfunc_8(beNDMWMdlPEBaseInfoWork *self) {
    igIntList *up;
    igIntList *down;
    int i;
    igObject *list;

    if (self->_messenger != 0 && self->_dispRamNoList != 0) {
        if (self->_isPlayer != 0) {
            up = (igIntList *)self->_upDataList;
            if (up != 0) IntList_Fill(up, 0);
            down = (igIntList *)self->_downDataList;
            if (down != 0) IntList_Fill(down, 0);
        }
        for (i = 0; i < STATUS_ICON_COUNT; i++) {
            int iconRamNo = IntAt(self->_dispRamNoList, i);
            if (iconRamNo != -1) {
                beMessenger_SendNamed(self->_messenger, MODELCTRL_20, g_statusIconModelNames[i], iconRamNo, SQ_ERAS_4);
            }
        }
        list = (igObject *)self->_dispRamNoList;
        IG_OBJECT_RELEASE(list);
        self->_dispRamNoList = 0;
        list = (igObject *)self->_dispPosNoList;
        IG_OBJECT_RELEASE(list);
        self->_dispPosNoList = 0;
        list = (igObject *)self->_timerList;
        IG_OBJECT_RELEASE(list);
        self->_timerList = 0;
        list = (igObject *)self->_isFirstList;
        IG_OBJECT_RELEASE(list);
        self->_isFirstList = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(self);
}

int beNDMWMdlPEBaseInfoWork_IsPoisoned(beNDMWMdlPEBaseInfoWork *self)
{
    if (self->_timerList == 0 || IntAt(self->_timerList, STATUS_POISON) == 0) {
        return 0;
    }
    return 1;
}

void beNDMWMdlPEBaseInfoWork_CurePoison(beNDMWMdlPEBaseInfoWork *self, beBaseInfoRam *ram)
{
    beBaseInfoRam_RemoveTimer(ram, POISON);
    IntList_Set((igIntList *)self->_timerList, STATUS_POISON, 0);
}

int beNDMWMdlPEBaseInfoWork__GetMeta(void)
{
    return g_beNDMWMdlPEBaseInfoWork_metaObject[0];
}

int beNDMWMdlPEBase__GetMeta(void)
{
    return g_beNDMWMdlPEBase_metaObject[0];
}

