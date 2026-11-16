#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/beBaseInfoManagerDispatchView.h"
#include "dw4/listSet.h"

extern "C" int igInsightCore_FindManager(int, int);
extern "C" int beBaseInfoManager_Start(...);
extern "C" int beNDMWMdlPlayer2_GetMeta(void);
extern "C" int strcmp(const char *, const char *);
extern "C" int beNDMWMdlPlayer2_IsKind(int dummy0, int kind);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int beModelCtrl__OnGenerate(...);
extern "C" int beMessenger_SendGroup(...);
extern "C" int beMessenger_GetObject(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" int StringPool_Intern(...);
extern "C" int StringPool_Allocate(...);
extern "C" int igMatrix44f_GetTranslation(...);
extern "C" int bePadManager_GetPadForPlayer(int, int);
extern "C" int beTargetObj_SelectTarget(int, const char *, const char *);
extern "C" float beTargetObj_GetTargetDistanceSq(...);
extern "C" int beLua__RunNamedChunk(int, int *, int);
extern "C" int g_bePadManager_metaObject[4];
extern "C" int g_beNDMWMdlPlayer2_metaObject[4];
extern "C" void beNDMWMdlPlayer2_Start(beNDMWMdlPlayer2 *self);
extern "C" char KIND_PLAYER2[];
extern "C" char PLAYER2_2[];
extern "C" void beNDMWMdlPlayer2_RegisterReceiver(beNDMWMdlPlayer2 * p0, int p1, char * p2);
extern "C" igObject *beBaseInfoDataList_Create(int);
extern "C" igObject *beNDMWMdlPlayer2InfoWork_Create(int);
extern "C" beDataObjStringList *igProperty_GetRecordStringList(int record, const char *name);
extern "C" beDataObjFloatList *igProperty_GetRecordFloatList(...);
extern "C" beModelCtrlInfoRamData *igProperty_FindByName(...);
extern "C" char ONE_13[];
extern "C" char GAMERAM_15[];
extern "C" char GETCOMMON_7[];
extern "C" char BKCHIPSTAGE[];
extern "C" char BKCHIPPOS[];
extern "C" int g_propertyNameField[4];
extern "C" int g_stringPool[4];
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
struct Str { static inline int *intern(int s) {
    int *ref;
    if (s == 0) {
        ref = 0;
    } else {
        if (g_stringPool[0] == 0) {
            int pool = StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        ref = (int *)StringPool_Intern(g_stringPool[0], s);
    }
    return ref;
}
static inline void release(int *q) {
    if (q) { int *hd = q - 2; int c = q[-1] - 1; q[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*hd, hd); }
} };
struct Vec3Float { float x, y, z; };
/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */

/* Owning stack reference to the new property value object; released on scope exit. */
class ValueRef {
public:
    igObject *p;
    ValueRef(igObject *o) : p(o) {}
    ~ValueRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
/* Inlined helper shared by the model-controller "apply ram" methods: a ram without a data list gets a
 * fresh beBaseInfoDataList (allocator chosen by the global selector flag).  Being an inlined callee, its
 * list reference is laid out after the caller's own references (+0x74 below +0x7c/+0x78), as retail does. */

struct RamDataList { static inline void Ensure(beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        int alloc = igObject_GetAllocator(ram);
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(a));
        /* matching construct: retained, released and stored by hand; through igSmartPointer::operator= this
         * unit's profile leaves the operator an out-of-line call inside the inline */
        igObject *s0 = list.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        igRelease((igObject *)ram->_dataList);
        ram->_dataList = (int)s0;
    }
} };
extern "C" void beNDMWMdlPlayer2_OnGenerate(beNDMWMdlPlayer2 *self, beBaseInfoRam *ram);
extern "C" char PLAYER_8[];
extern "C" char NEAR_3[];
extern "C" char SQ_SWON[];
extern "C" char SQ_SWOF[];
extern "C" int text_end_g_000bcaps_lua[4];
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

extern "C" void beNDMWMdlPlayer2_UpdateControl(beNDMWMdlPlayer2 *self, beBaseInfoRam *ram);

/* After the shared igObject slot 23 body, caches the pad manager registered with the insight core
 * (_padManager), found by its class metaObject; the same binding step as the other managers' slot
 * 23. */
void beNDMWMdlPlayer2_Start(beNDMWMdlPlayer2 *self) {
    beBaseInfoManager_Start();
    self->_padManager = igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]);
}

int beNDMWMdlPlayer2_IsKind(int dummy0, int kind) {
    return strcmp((const char *)kind, KIND_PLAYER2) == 0;
}

void beNDMWMdlPlayer2_RegisterReceiver(beNDMWMdlPlayer2 * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, PLAYER2_2);
}

void beNDMWMdlPlayer2_OnGenerate(beNDMWMdlPlayer2 *self, beBaseInfoRam *ram) {
    Vec3Float t;
    beModelCtrlInfoRamData *r;
    beDataObjStringList *s4;
    beDataObjFloatList *s3;
    int s2;
    int *e;
    int s1;
    RamDataList::Ensure(ram);
    r = igProperty_FindByName((igObject *)ram->_dataList, g_propertyNameField[0], ONE_13);
    {
        int alloc = igObject_GetAllocator(self);
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        }
        ValueRef value(beNDMWMdlPlayer2InfoWork_Create(a));
        (igSmartPointer<igObject> &)r->_work = value.p;
    }
    beModelCtrl__OnGenerate(self, ram);
    beMessenger_SendGroup(self->_messenger, GAMERAM_15, GETCOMMON_7);
    {
        int o = beMessenger_GetObject(self->_messenger, 0);
        s4 = igProperty_GetRecordStringList(o, BKCHIPSTAGE);
        s3 = igProperty_GetRecordFloatList(o, BKCHIPPOS);
    }
    beSystem *cfg = (beSystem *)self->_system;
    s2 = cfg->_stageName;
    s1 = ram->_ramNo;
    {
        int *tok = Str::intern(s2);
        StringRef name(tok);
        igIntList *l = (igIntList *)s4->_data;
        int n = l->_count;
        if (n != 0 && s1 >= 0 && s1 < n) {
            e = &((int *)l->_data)[s1];
            int *nv = name.p;
            if (nv) nv[-1] = nv[-1] + 1;
            Str::release((int *)*e);
            *e = (int)name.p;
        }
    }
    igMatrix44f_GetTranslation((char *)r->_node + 32, &t);
    {
        float *v = &t.x;
        igFloatList *l = (igFloatList *)s3->_data;
        int n = l->_count;
        if (n != 0) {
            int i = s1 * 3 + 0;
            if (i >= 0 && i < n) { float *d = (float *)l->_data; d[s1 * 3 + 0] = *v; }
        }
    }
    {
        float *v = &t.y;
        igFloatList *l = (igFloatList *)s3->_data;
        int n = l->_count;
        if (n != 0) {
            int i = s1 * 3 + 1;
            if (i >= 0 && i < n) { float *d = (float *)l->_data; d[s1 * 3 + 1] = *v; }
        }
    }
    {
        float *v = &t.z;
        igFloatList *l = (igFloatList *)s3->_data;
        int n = l->_count;
        if (n != 0) {
            int i = s1 * 3 + 2;
            if (i >= 0 && i < n) { float *d = (float *)l->_data; d[s1 * 3 + 2] = *v; }
        }
    }
}

void beNDMWMdlPlayer2_UpdateControl(beNDMWMdlPlayer2 *self, beBaseInfoRam *ram) {
    beModelCtrlInfoRamData *prop;
    beNDMWMdlPlayer2InfoWork *q;
    float f;
    if (ram->_dataList == 0) {
        int alloc = igObject_GetAllocator(ram);
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(a));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        igObject *old = (igObject *)ram->_dataList;
        if (old != 0) {
            --old->_refCount;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        ram->_dataList = (int)s0;
    }
    prop = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ONE_13);
    q = (beNDMWMdlPlayer2InfoWork *)prop->_work;
    if (q->_timerCount < 10) {
        q->_timerCount = q->_timerCount + 1;
    }
    bePadManager_GetPadForPlayer(self->_padManager, ram->_ramNo);
    if (beTargetObj_SelectTarget(prop->_node + 32, PLAYER_8, NEAR_3) != 0) {
        f = beTargetObj_GetTargetDistanceSq();
        if (q->_isPowerOn == 0) {
            if (f < 900.0f) {
                q->_isPowerOn = 1;
                ((beBaseInfoManagerDispatchView *)self)->OnMessageText(ram, SQ_SWON);
            }
        } else if (!(f <= 900.0f)) {
            q->_isPowerOn = 0;
            ((beBaseInfoManagerDispatchView *)self)->OnMessageText(ram, SQ_SWOF);
        }
    } else {
        beLua__RunNamedChunk(self->_luaManager, text_end_g_000bcaps_lua, 0);
    }
}


extern "C" StringRef StringList_CopyRetained(igStringRefList *list, int index);
extern "C" beDataObjInt *igProperty_GetRecord(int record, const char *name);
extern "C" beDataObjIntList *igProperty_GetRecordIntList(int record, const char *name);
extern "C" beDataObjString *igProperty_GetRecordString(int record, const char *name);
extern "C" void beMessenger_PrepareDelayedSelection(int messenger, const char *group, const char *name, int ramNo);
extern "C" void beMessenger_AppendVec3(int messenger, float *value);
extern "C" void beMessenger_AppendString(int messenger, const char *value);
extern "C" void beMessenger_EnqueueSelected(int messenger, const char *message, int count);
extern "C" void beMessenger_GetMatrix(float *out, int messenger, int index);
extern "C" int beMessenger_GetInt(int messenger, int index);
extern "C" void beMessenger_SendNamed(int messenger, const char *group, int name, int ramNo, const char *message);
extern "C" int beMessenger_GetBoolCount(int messenger);
extern "C" bool beMessenger_GetBool(int messenger, int index);
extern "C" void beMessenger_SelectGroup(int messenger, const char *group);
extern "C" void beMessenger_AppendInt(int messenger, int value);
extern "C" void beMessenger_DispatchSelected(int messenger, const char *message);
extern "C" void beMessenger_SelectReceivers(int messenger, const char *group, const char *name, int ramNo);
extern "C" void beMessenger_AppendMatrix(int messenger, float *value);
extern "C" void beMessenger_SendDelayedNamed(int messenger, const char *group, int name, int ramNo, const char *message, int delay);
extern "C" int sprintf(char *out, const char *format, ...);
extern "C" char GENERATE_15[];
extern "C" char REMOVE_6[];
extern "C" char GENESTAGE[];
extern "C" char MODELCTRL_22[];
extern "C" char g_000bcaps_2[];
extern "C" char SQ_ENTR_dP[];
extern "C" char RAISE_2[];
extern "C" char ISRUN_11[];
extern "C" char GETPLAYER_15[];
extern "C" char HP_7[];
extern "C" char DIGIMONNAME_4[];
extern "C" char p_agumon[];
extern "C" char SQ_CMBK[];
extern "C" char BKCHIPDATA_2[];
extern "C" char BIT_8[];
extern "C" char BKCHIPNAME_2[];
extern "C" char EXP_3[];
extern "C" char SQ_EXIT_3[];

/* Element of a float list. */
static inline float floatAt(igFloatList *list, const int &index) { return ((float *)list->_data)[index]; }

/* Field accessors. */
static inline igStringRefList *getData(beDataObjStringList *record) { return (igStringRefList *)record->_data; }
static inline int getRamNo(beBaseInfoRam *ram) { return ram->_ramNo; }

/* Stores a retained copy of value at list[index] when the index is in range, releasing the token it
 * replaces. */
static inline void setStringAt(igStringRefList *list, int index, const StringRef &value) {
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        int *slot = (int *)list->_data + index;
        int *v = value.p;
        if (v) v[-1] = v[-1] + 1;
        Str::release((int *)*slot);
        *slot = (int)value.p;
    }
}

extern "C" int beNDMWMdlPlayer2_OnPreMessage(beNDMWMdlPlayer2 *self, beBaseInfoRam *ram, const char *command);
int beNDMWMdlPlayer2_OnPreMessage(beNDMWMdlPlayer2 *self, beBaseInfoRam *ram, const char *command)
{
    if (strcmp(command, GENERATE_15) == 0) {
        if (ram->_isRun != 0)
            ((beBaseInfoManagerDispatchView *)self)->OnMessageText(ram, REMOVE_6);
    } else if (strcmp(command, GENESTAGE) == 0) {
        beMessenger_SendGroup(self->_messenger, GAMERAM_15, GETCOMMON_7);
        int common = beMessenger_GetObject(self->_messenger, 0);
        igStringRefList *stages = getData(igProperty_GetRecordStringList(common, BKCHIPSTAGE));
        igFloatList *positions = (igFloatList *)igProperty_GetRecordFloatList(common, BKCHIPPOS)->_data;
        int ramNo = getRamNo(ram);
        if (StringList_CopyRetained(stages, ramNo).p != 0
            && strcmp((const char *)((beSystem *)self->_system)->_stageName, (const char *)StringList_CopyRetained(stages, ramNo).p) == 0) {
            float x = floatAt(positions, ramNo * 3);
            float y = floatAt(positions, ramNo * 3 + 1);
            float z = floatAt(positions, ramNo * 3 + 2);
            float pos[3];
            char sequence[16];
            beMessenger_PrepareDelayedSelection(self->_messenger, MODELCTRL_22, g_000bcaps_2, getRamNo(ram));
            pos[0] = x;
            pos[1] = y;
            pos[2] = z;
            beMessenger_AppendVec3(self->_messenger, pos);
            sprintf(sequence, SQ_ENTR_dP, getRamNo(ram) + 1);
            beMessenger_AppendString(self->_messenger, sequence);
            beMessenger_EnqueueSelected(self->_messenger, GENERATE_15, 1);
        }
        return 1;
    } else if (strcmp(command, RAISE_2) == 0) {
        RamDataList::Ensure(ram);
        beNDMWMdlPlayer2InfoWork *work = (beNDMWMdlPlayer2InfoWork *)igProperty_FindByName((igObject *)ram->_dataList, g_propertyNameField[0], ONE_13)->_work;
        if (work->_timerCount < 10)
            return 1;
        float matrix[16];
        beMessenger_GetMatrix(matrix, self->_messenger, 0);
        int percent = beMessenger_GetInt(self->_messenger, 0);
        int hp = beMessenger_GetInt(self->_messenger, 1);
        bool running = false;
        beMessenger_SendNamed(self->_messenger, PLAYER_8, 0, getRamNo(ram), ISRUN_11);
        int count = beMessenger_GetBoolCount(self->_messenger);
        for (int i = 0; i < count; i++) {
            if (beMessenger_GetBool(self->_messenger, i) == 1) {
                running = true;
                break;
            }
        }
        beMessenger_SelectGroup(self->_messenger, GAMERAM_15);
        beMessenger_AppendInt(self->_messenger, getRamNo(ram));
        beMessenger_DispatchSelected(self->_messenger, GETPLAYER_15);
        int player = beMessenger_GetObject(self->_messenger, 0);
        if (!running) {
            igProperty_GetRecord(player, HP_7)->_data = hp;
            const char *digimon = (const char *)igProperty_GetRecordString(player, DIGIMONNAME_4)->_data;
            if (*digimon == 0) digimon = p_agumon;
            beMessenger_SelectReceivers(self->_messenger, MODELCTRL_22, digimon, getRamNo(ram));
            beMessenger_AppendMatrix(self->_messenger, matrix);
            beMessenger_AppendString(self->_messenger, SQ_CMBK);
            beMessenger_DispatchSelected(self->_messenger, GENERATE_15);
        }
        beMessenger_SendGroup(self->_messenger, GAMERAM_15, GETCOMMON_7);
        int common = beMessenger_GetObject(self->_messenger, 0);
        int bitIndex = getRamNo(ram) * 2;
        int *chipData = (int *)((igIntList *)igProperty_GetRecordIntList(common, BKCHIPDATA_2)->_data)->_data;
        int bit = chipData[bitIndex];
        bit += igProperty_GetRecord(player, BIT_8)->_data;
        igProperty_GetRecord(player, BIT_8)->_data = bit;
        {
            igIntList *chips = (igIntList *)igProperty_GetRecordIntList(common, BKCHIPDATA_2)->_data;
            ListSet(chips, bitIndex, 0);
        }
        const char *digimon = (const char *)igProperty_GetRecordString(player, DIGIMONNAME_4)->_data;
        const char *chipName = (const char *)StringList_CopyRetained(getData(igProperty_GetRecordStringList(common, BKCHIPNAME_2)), getRamNo(ram)).p;
        if (strcmp(digimon, chipName) == 0) {
            int expIndex = getRamNo(ram) * 2 + 1;
            chipData = (int *)((igIntList *)igProperty_GetRecordIntList(common, BKCHIPDATA_2)->_data)->_data;
            int chipExp = chipData[expIndex];
            int exp = (chipExp * percent) / 100;
            exp += igProperty_GetRecord(player, EXP_3)->_data;
            igProperty_GetRecord(player, EXP_3)->_data = exp;
            igIntList *chips = (igIntList *)igProperty_GetRecordIntList(common, BKCHIPDATA_2)->_data;
            ListSet(chips, expIndex, 0);
        }
        beMessenger_SendDelayedNamed(self->_messenger, PLAYER2_2, 0, getRamNo(ram), SQ_EXIT_3, 0);
        beMessenger_SendGroup(self->_messenger, GAMERAM_15, GETCOMMON_7);
        common = beMessenger_GetObject(self->_messenger, 0);
        setStringAt(getData(igProperty_GetRecordStringList(common, BKCHIPSTAGE)), getRamNo(ram), StringRef(0));
        return 1;
    }
    return 0;
}

int beNDMWMdlPlayer2_GetMeta(void)
{
    return g_beNDMWMdlPlayer2_metaObject[0];
}
