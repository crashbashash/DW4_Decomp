#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
#define RELEASE_REF(T, q) { T *rr = (q); if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }
#define ALLOC(owner, var) { void *got = ((void *)igObject_GetAllocator(owner)); if (g_useOwnerAllocator) var = got; else var = ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0])); }
#define RESERVE(LT, h, SZ) { LT *l = (LT *)(h)->_data; if (!(entry->count < l->_count)) List_Reserve(l, entry->count, SZ); }
#define RESIZE(LT, h, SZ) { int n = entry->count; LT *l = (LT *)(h)->_data; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize(l, n, SZ); } }
/* matching construct: inline release macro with block-local q */
#define RELO(X) { igObject *q = (X); if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7fffff) == 0) igObject_Destroy(q); } }
/* Sentinel for the `absolute` argument of the HP update: apply `delta` instead. */
#define NO_ABSOLUTE_HP (-1)
#define NEARBY_RADIUS_SQUARED 900.0f
#define REFERENCE_COUNT_MASK 0x7fffffULL
#define CLAMP_ATTR(v) if ((v) <= 0) (v) = 1; if ((v) > 9999) (v) = 9999;

class StringRef;
/* The property records igProperty_FindByName returns: the value sits after a 12-byte header. */
struct IntProperty { char header[12]; int value; };
struct BoolProperty { char header[12]; unsigned char value; };
struct IntListProperty { char header[12]; igIntList *list; };
struct DataListProperty { char header[12]; igDataList *list; };
struct ObjectListProperty { char header[12]; igObjectList *list; };
struct StringListProperty { char header[12]; igStringRefList *list; };
/* An int list as the stat code reads it: the element buffer after the 16-byte list header. */
struct IntValues { char header[16]; int *values; };
struct IntValuesProperty { char header[12]; IntValues *list; };
extern "C" int List_Reserve(...);
extern "C" int List_Resize(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int ObjectList_FillRetained(...);
extern "C" int ObjectList_ResizeRetained(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringList_Resize(void *, int);
extern "C" int igNamedObject_SetName(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void *beDataObjFloatList_Create(void *);
extern "C" void *beDataObjObjectList_Create(void *);
extern "C" void *beDataObjStringList_Create(void *);
extern "C" void *beDataObjString_Create(void *);
extern "C" void *beDataObjBoolList_Create(void *);
extern "C" void *beDataObjBool_Create(void *);
extern "C" void *beDataObjIntList_Create(void *);
extern "C" void *beDataObjInt_Create(void *);

extern "C" void * igProperty_GetRecordFolder(...);
extern "C" void * igProperty_GetRecordArray(...);
extern "C" void beNDMWGameRam_Update(void);
extern "C" int beNDMWGameRam_GetMeta(void);
extern "C" int beNDMWGameRam_GetInfoMeta(void);
extern "C" int StringPool_Allocate(int);
extern "C" int StringPool_Construct(int);
extern "C" char * StringPool_Intern(...);
extern "C" int g_stringPool[4];
/* The shared string pool, created on first use. */
struct SharedStringPool {
    static inline int get()
    {
        if (g_stringPool[0] == 0) {
            int pool = StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        return g_stringPool[0];
    }
};
extern "C" char * beDataBase_GetRecordString(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" void *beNDMWItemWeapon_Create(int);
extern "C" int beNDMWItemWeapon_Set(void *, int, int, int);
extern "C" int beDataBase_GetRecordInt(...);
extern "C" int beNDMWItemBase_GetRecordInt(...);
extern "C" const char * beNDMWItemBase_GetRecordString(...);
extern "C" int igInsightCore_FindManager(int, int);
extern "C" void beMessenger_SelectReceivers(int, const char *, const char *, int);
extern "C" void beMessenger_AppendFloat(int, float);
extern "C" void beMessenger_AppendInt(int, int);
extern "C" void beMessenger_DispatchSelected(int, const char *);
extern "C" void beNDMWGameRam_AddPowerSocketBonus(int self, int player, int *total, const char *name, int withRevision);
extern "C" void beNDMWGameRam_AddPowerPocketBonus(int self, int player, int *total, const char *name);
extern "C" void beNDMWGameRam_AddMainPocketBonus(int self, int player, int *total, const char *name);
extern "C" int strcmp(...);
extern "C" void beNDMWGameRam_AddSubSlotBonus(int self, int player, int *total, const char *name, int withAbility);
extern "C" void beMessenger_SendGroup(int,const char *,const char *);
extern "C" int beMessenger_GetIntCount(int);
extern "C" int beMessenger_GetInt(int,int);
extern "C" void beMessenger_PushArgContext(int);
extern "C" void beMessenger_SetRunCheck(int,unsigned char);
extern "C" void beMessenger_PopArgContext(int);
extern "C" int PropertyRecord_GetValue_00406db0(int *p);
extern "C" int ObjectRef_Get_00406dc0(int *p);
extern "C" int ObjectRef_Get_00406df0(int *p);
extern "C" int ObjectRef_Get_00406e00(int *p);
extern "C" int beBaseInfoDataList_Create(int);
extern "C" int *DataListRef_Construct_00406e10(int *ref, int *allocator);
extern "C" int PropertyRecord_GetValue_00406e40(int *p);
extern "C" int ObjectRef_Get_00406e50(int *p);
extern "C" int ObjectRef_Get_00406ee0(int *p);
extern "C" int ObjectRef_Get_00406ef0(int *p);
extern "C" int ObjectRef_Get_00406f10(int *p);
extern "C" void List_RemoveWordAt(void *list, int index);
extern "C" void ObjectList_RemoveAt_00406f20(void *list, int index);
/* matching construct: copy-constructed struct return reproduces the retail hidden-return calling shape */ struct AllocatorValue { int v; AllocatorValue(int value):v(value) {} AllocatorValue(const AllocatorValue &o):v(o.v) {} };
extern "C" AllocatorValue AllocatorValue_Make_00406f40(int value);
extern "C" AllocatorValue AllocatorValue_Make_00406f50(int value);
extern "C" AllocatorValue AllocatorValue_Make_00406f60(int value);
extern "C" AllocatorValue AllocatorValue_Make_00406f70(int value);
extern "C" int ObjectRef_Get_00406f80(int *p);
extern "C" int StringPool_GetInstance(void);
extern "C" int ObjectRef_Get_00407030(int *p);
extern "C" int ObjectRef_Get_00407040(int *p);
extern "C" int ObjectRef_Get_00407050(int *p);
extern "C" int kIGMemoryPoolHandleUser0[4];
extern "C" int g_dataObjDefaults[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" unsigned char g_dataObjDefaultBool;
/* One row of a data-list layout: the value type, the element count of a list and the name. */
enum DataObjType {
    DATA_END = -1,
    DATA_INT,
    DATA_INT_LIST,
    DATA_BOOL,
    DATA_BOOL_LIST,
    DATA_STRING,
    DATA_STRING_LIST,
    DATA_OBJECT_LIST,
    DATA_FLOAT_LIST
};
struct DataLayoutEntry { int type; int count; const char *name; };
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(int s) : p((char *)s) {}
    StringRef(const char *s) : p((char *)s) {}
    StringRef(void *s) : p((char *)s) {}
    static void release(char **slot) {
        char *token = *slot;
        if (token) {
            int *header = (int *)(token - 8);
            if (--header[1] == 0) StringChunk_ReleaseHeader((void *)header[0], (int)header);
        }
    }
    ~StringRef() { release(&p); }
};
struct Fill {
    /* clear every slot of the string list to the empty token. matching construct: the empty-token holder is a temporary of the call statement (passed by const reference), which takes the lowest frame slot (retail slot 140) below the case holders; the loop counters stay the caller's variables so the register assignment matches */
    static inline void emptyStrings(beDataObjStringList *h5, const StringRef &str, int &n5, int **&d5, int &i5) {
        igStringRefList *l5 = (igStringRefList *)h5->_data;
        n5 = l5->_count;
        d5 = (int **)l5->_data;
        for (i5 = 0; i5 < n5; i5++) {
            int *cur = (int *)str.p;
            if (cur) ++cur[-1];
            int *old = *d5;
            if (old) { int *hd = old - 2; int rc = old[-1] - 1; old[-1] = rc; if (rc == 0) StringChunk_ReleaseHeader(*hd, hd); }
            *d5 = (int *)str.p;
            d5++;
        }
    }
};
extern "C" igObject *beDataObjList_Create(int);
extern "C" igObject *beNDMWItemDisk_Create(int);
extern "C" int beNDMWItemDisk_Set(igObject *, int);
extern "C" const DataLayoutEntry g_commonDataLayout[];
extern "C" const DataLayoutEntry g_playerDataLayout[];
extern "C" void beNDMWGameRam_BuildDataList(beNDMWGameRam *self, igObjectList *out, const DataLayoutEntry *layout);
extern "C" int g_initialBaseLevel[4];
extern "C" int g_initialBaseSkill[4];
extern "C" int DISKFOLDER[4];
extern "C" int BASE_FLAG[4];
extern "C" const char BASE_LEVEL[];
extern "C" const char BASE_SKILL[];
extern "C" unsigned char g_initialBaseFlag960;
/* Owning stack reference to one new item record, released at the end of each loop pass. */
class ItemRef {
public:
    igObject *p;
    ItemRef(igObject *o) : p(o) {}
    ~ItemRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void beNDMWGameRam_ResetPlayer(beNDMWGameRam *self, int player);
extern "C" igObject *beDataObjListList_Create(int);
extern "C" int Gap__Core__igObject__vfunc_23(beNDMWGameRam *);
/* matching construct: inline release helper reproduces the retail release sequence */
struct ReleaseRef { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* Owning stack reference to the new per-player data-list list, released the same way. */
class PlayerDataListListRef {
public:
    igObject *p;
    PlayerDataListListRef(igObject *o) : p(o) {}
    ~PlayerDataListListRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void beNDMWGameRam_Initialize(beNDMWGameRam *self);
/* reference-counted engine object header: refcount word at +4 */
typedef struct RefCountedHeader { int p0; unsigned refs; } RefCountedHeader;
/* Object-reference list header: count at +8, capacity at +12, buffer at +16. */
typedef struct ObjectRefList { char p[8]; int count; int cap; RefCountedHeader **data; } ObjectRefList;
extern "C" void beNDMWGameRam_ClearLists(beNDMWGameRam *self);
/* matching construct: inline release helper reproduces the retail inlined refcount release (release then clear) */
struct RefRelease {
    static inline void rel(int &r) {
        igObject *object = (igObject *)r;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
        r = 0;
    }
};
extern "C" void beNDMWGameRam_ReleaseDataBases(beNDMWGameRam *self);
extern "C" beNDMWGameRamInfo *beNDMWGameRamInfo_Create(int);
extern "C" beNDMWGameRamInfoRam *beNDMWGameRamInfoRam_Create(int);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, beNDMWGameRamInfoRam *, int *);
extern "C" int gameram[4];
extern "C" int GAMERAM_6[4];
extern "C" int kIGMemoryPoolHandleUser1[4];
/* Owning stack reference to the info's ram object created here, released on scope exit. */
class RamRef {
public:
    beNDMWGameRamInfoRam *p;
    RamRef(beNDMWGameRamInfoRam *o) : p(o) {}
    ~RamRef() { beNDMWGameRamInfoRam *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" int beNDMWGameRam_CreateInfo(beNDMWGameRam *self);
extern "C" int g_beNDMWGameRam_metaObject[4];
extern "C" int MODEL_NAME[4];
extern "C" int GETDATABASE_3[4];
extern "C" int shinka_2[4];
extern "C" int DATABASE_3[4];
extern "C" int g_stringPool[4];
extern "C" int beNDMWGameRam_FindSpecies(beNDMWGameRam *self, const char *modelName);
typedef struct PropertyRecord { char header[12]; void *value; } PropertyRecord;
extern "C" PropertyRecord *igProperty_GetRecordString(void *, void *);
extern "C" igObject * beMessenger_GetObject(...);
extern "C" int FLAG_2[4];
extern "C" int FLAGFOLDER[4];
extern "C" int COUNTER[4];
extern "C" const char DIGIMONNO_2[];
extern "C" const char LEVEL_2[];
extern "C" const char SKILL[];
extern "C" const char UPCNT[];
extern "C" int DIGIMONNAME_2[4];
extern "C" const char EXP[];
extern "C" int BASE_FLAGFOLDER[4];
extern "C" int BASE_COUNTER[4];
extern "C" const char BASE_EXP[];
extern "C" const char BASE_UPCNT[];
extern "C" void beNDMWGameRam_SelectSpecies(beNDMWGameRam *self, int index, int species);
extern "C" void beNDMWGameRam_StoreSpecies(beNDMWGameRam *self, int player_index);
extern "C" int g_initialWeaponFields[4];
extern "C" int DEVICEFOLDER[4];
struct RecoveryTarget { int word0; int references;
 static void release(RecoveryTarget *object) {
  if(object) {
   --object->references;
   if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
    igObject_Destroy(object);
  }
 }
};
extern "C" void ObjectRef_Retain_003e90d0(void *);
template<int I> class RecoveryRef { public:
 void *value;
 RecoveryRef(void *p, bool retain):value(p) { if(retain) ObjectRef_Retain_003e90d0(value); }
 RecoveryRef(const RecoveryRef &other):value(other.value) { ObjectRef_Retain_003e90d0(value); }
 ~RecoveryRef() { RecoveryTarget::release((RecoveryTarget *)value); }
};
extern "C" void beNDMWGameRam_GiveInitialWeapons(beNDMWGameRam *self, int index);
extern "C" char TSUYOSA[];
extern "C" int POWERSOCKET[4];
extern "C" char POWERSOCKETNAME[];
extern "C" char MODEL[];
extern "C" char SOUBI[];
extern "C" char SKILLPOINT[];
extern "C" IntProperty * igProperty_GetRecord(...);
extern "C" StringListProperty *igProperty_GetRecordStringList(void *, const char *);
extern "C" int StringList_AppendRetained(int, const StringRef &);
extern "C" void beNDMWGameRam_EquipWeapon(beNDMWGameRam *self, int index, int apply);
extern "C" unsigned char beNDMWGameRam_HasUsableWeapon(beNDMWGameRam *self, int index, int species);
extern "C" BoolProperty *igProperty_GetRecordByte(int, int *);
extern "C" int NINZU_2[4];
extern "C" int ISUSE_4[4];
extern "C" int BASE_ISUSE[4];
extern "C" unsigned char g_speciesUsedMark;
extern "C" void beNDMWGameRam_JoinPlayer(beNDMWGameRam *self, int index, const char *modelName);
extern "C" int beFont_ConvertToUnicode(beUnicodeObj **, int, int);
extern "C" int beUnicodeObj_AllocateBuffer(beUnicodeObj *, int);
extern "C" beUnicodeObj *beUnicodeObj_Create(int);
extern "C" char PLAYERNAME[];
extern "C" int g_beFont_metaObject[4];
extern "C" void beNDMWGameRam_JoinPlayerWithName(beNDMWGameRam *self, int index, void *modelName, StringRef name);
extern "C" void beNDMWGameRam_JoinPlayerWithUnicodeName(beNDMWGameRam *self, int index, void *modelName, RecoveryRef<0> name);
extern "C" void beNDMWGameRam_LeavePlayer(beNDMWGameRam *self, int index);
extern "C" const char HP[];
extern "C" const char MHP[];
extern "C" const char MP[];
extern "C" const char MMP[];
extern "C" const char METERCTRL[];
extern "C" const char hpmt[];
extern "C" const char SETPERCENT[];
extern "C" const char NUMBERCTRL[];
extern "C" const char hpnm[];
extern "C" const char SETVALUE[];
extern "C" const char mpmt[];
extern "C" const char mpnm[];
extern "C" int beNDMWGameRam_ChangeHp(beNDMWGameRam *self, int player_index, int delta, int absolute);
extern "C" void beNDMWGameRam_ChangeMp(beNDMWGameRam *self, int player_index, int delta);
extern "C" int POWERPOCKET[4];
/* The flat field is const: its read is created before the *out reload so the register colouring puts
 * the field in a0 and the running total in v1. */
struct BonusItem { char pad[20]; const int flat; };
extern "C" int MAINSLOT[4];
extern "C" void beNDMWGameRam_AddMainSlotBonus(beNDMWGameRam *self, void *player, int *total, const char *name, int withFlat);
extern "C" int MAINPOCKET[4];
extern "C" int SUBSLOT[4];
extern "C" int SHUSEINOURYOKU[4];
struct beNDMWItemCountView { beNDMWItemBase base; unsigned int _count; };
typedef igObject Ref;
extern "C" char MHP_INI[];
extern "C" char MHP_GROW[];
extern "C" char MMP_INI[];
extern "C" char MMP_GROW[];
extern "C" int g_growthBandMaxLevel[];
extern "C" int g_pointGrowthBandBase[];
extern "C" int g_growthBandStartLevel[];
extern "C" int g_pointGrowthBandRate[];
extern "C" IntValuesProperty * igProperty_GetRecordIntList(...);
struct StatHelpers {
    static inline void release_ref(Ref *object)
    {
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
    static inline Ref *shinka(beNDMWGameRam *g)
    {
        if (!g->_dBShinka) {
            Ref *fetched;
            beMessenger_SendNamed(g->_messenger, ((char *)DATABASE_3), ((char *)shinka_2), 0, ((char *)GETDATABASE_3));
            fetched = ((Ref *)beMessenger_GetObject(g->_messenger, 0));
            if (fetched) ++fetched->_refCount;
            release_ref((Ref *)g->_dBShinka);
            g->_dBShinka = (int)fetched;
        }
        return (Ref *)g->_dBShinka;
    }
};
extern "C" int beNDMWGameRam_CalcMaxPoints(beNDMWGameRam *self, int index, int species, int isHp);
extern "C" int g_attributeGrowthBandBase[];
extern "C" int g_attributeGrowthBandRate[];
extern "C" const char *g_attributeInitialFields[];
extern "C" const char *g_attributeGrowthFields[];
struct AttributeHelpers {
    static inline void release_ref(igObject *object)
    {
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
    static inline igObject *shinka(beNDMWGameRam *g)
    {
        if (!g->_dBShinka) {
            igObject *fetched;
            beMessenger_SendNamed(g->_messenger, ((char *)DATABASE_3), ((char *)shinka_2), 0, ((char *)GETDATABASE_3));
            fetched = beMessenger_GetObject(g->_messenger, 0);
            if (fetched) ++fetched->_refCount;
            release_ref((igObject *)g->_dBShinka);
            g->_dBShinka = (int)fetched;
        }
        return (igObject *)g->_dBShinka;
    }
};
extern "C" int beNDMWGameRam_CalcAttribute(beNDMWGameRam *self, int index, int species, int attribute);
/* Recomputes one player's derived stats; `apply` says whether the equipment, chip and skill
 * modifiers are applied on top of the database/UPDATA/DOWNDATA base values. MHP/MMP are clamped to
 * 99999 and the attributes and element resistances to 1..9999. The player pointer and the
 * DIGIMONNO / LEVEL reads go through the tiny inline accessors StatHelpers::GetPlayer() and
 * GetProp(), whose result temporaries are created late so the register colouring comes out right;
 * locals are declared where they are first set, one variable per loop; the two threshold tests are
 * written `record <= value` and the delay clamp as `> 70` to keep the compare in `at`. */
struct Vector3 { float x,y,z; };
struct Matrix44 { float m[16]; };
struct IntList { int vtable_word, reference_word; int count; int capacity; int *data;
    int getCount() const { return count; } };
extern "C" IntList *igIntList_Create(int);
extern "C" void beMessenger_GetMatrix(Matrix44 *,int,int);
extern "C" void igMatrix44f_GetTranslation(const Matrix44 *,Vector3 *);
extern "C" char GETMATRIX[];
extern "C" char GETHP[];
extern "C" int kIGMemoryPoolHandleUser1[4];
/* Stack-resident counted reference to an IntList (the low 23 bits of the reference
 * word are the count; the object is destroyed when the last reference goes). */
class NearbyListRef;
class IntListRef {
public:
    IntList *value;
    IntListRef(IntList *p):value(p) {}
    IntListRef(const IntListRef &p):value(p.value) { if(value) ++value->reference_word; }
    ~IntListRef() {
        IntList *object=value;
        if(object) {
            --object->reference_word;
            if (((unsigned long long)(long long)object->reference_word & REFERENCE_COUNT_MASK)==0)
                igObject_Destroy(object);
        }
    }
};
/* The nearby-member query result. Its destructor is a separate copy from that of IntListRef; the
 * query's working reference and the by-value result it hands back to the caller share it. */
class NearbyListRef {
public:
    IntList *value;
    NearbyListRef(IntList *p):value(p) {}
    NearbyListRef(const NearbyListRef &p):value(p.value) { if(value) ++value->reference_word; }
    ~NearbyListRef() { RecoveryTarget::release((RecoveryTarget *)value); }
};
extern "C" NearbyListRef beNDMWGameRam_CollectNearbyNonzeroHp(beNDMWGameRam *self,const char *group,int excluded,const Vector3 *center);
extern "C" char MAMORI[];
extern "C" char KASHIKOSA[];
extern "C" char SEISHIN[];
extern "C" char SUBAYASA[];
extern "C" char HONOOTEIKO[];
extern "C" char KOORITEIKO[];
extern "C" char KAMINARITEIKO[];
extern "C" char YAMITEIKO[];
extern "C" const char WAZALIST[];
extern "C" char NEXTEXP[];
extern "C" char ATTACKDELAY[];
extern "C" char MEICHURITSU[];
extern "C" char CHIMEIRITSU[];
extern "C" char MAHIRITSU[];
extern "C" char KAIHIRITSU[];
extern "C" char BOUGYORITSU[];
extern "C" char MAHITEIKOU[];
extern "C" char DOKUTEIKOU[];
extern "C" char BITRITSU_2[];
extern "C" char EXPRITSU[];
extern "C" char LUCKRITSU[];
extern "C" char ATTACKZOKUSEI[];
extern "C" char HPDRAIN[];
extern "C" char MPDRAIN[];
extern "C" char CHOHATURITSU[];
extern "C" char WEAPONRECNO[];
extern "C" char WEAPONSKILLNO[];
extern "C" char UPDATA[];
extern "C" char DOWNDATA[];
extern "C" char MAXHP[];
extern "C" char MAXMP[];
extern "C" char RES_FIRE[];
extern "C" char RES_ICE[];
extern "C" char RES_THUNDER[];
extern "C" char RES_DARK[];
extern "C" char DELAY[];
extern "C" char ZOKUSEI[];
extern "C" char GETDATABASE_4[];
extern "C" char pcTech_2[];
extern "C" char DATABASE_4[];
extern "C" void beNDMWItemWaza_Set(igObject *, int, int);
extern "C" igObject *beNDMWItemWaza_Create(int);
extern "C" const char *g_techniqueFields[6];
extern "C" const char *g_techniqueLevelFields[6];
extern "C" const char *g_techniqueSkillFields[6][5];
extern "C" const char *g_elementNames[4];
/* The helpers are static members so a split of the unit at its top-level definitions keeps them. */
struct RecomputeHelpers {
    static inline void release_ref(igObject *object)
    {
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }

    static inline igObject *shinka(beNDMWGameRam *g)
    {
        if (!g->_dBShinka) {
            igObject *fetched;
            beMessenger_SendNamed(g->_messenger, ((char *)DATABASE_3), ((char *)shinka_2), 0, ((char *)GETDATABASE_3));
            fetched = beMessenger_GetObject(g->_messenger, 0);
            if (fetched) ++fetched->_refCount;
            release_ref((igObject *)g->_dBShinka);
            g->_dBShinka = (int)fetched;
        }
        return (igObject *)g->_dBShinka;
    }

    static inline igObject *pctech(beNDMWGameRam *g)
    {
        if (!g->_dBPcTech) {
            igObject *fetched;
            beMessenger_SendNamed(g->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
            fetched = beMessenger_GetObject(g->_messenger, 0);
            if (fetched) ++fetched->_refCount;
            release_ref((igObject *)g->_dBPcTech);
            g->_dBPcTech = (int)fetched;
        }
        return (igObject *)g->_dBPcTech;
    }

    static inline int select_allocator(int fallback)
    {
        if (g_useOwnerAllocator) return fallback;
        else return Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
    }

    static inline void *GetPlayer(beNDMWGameRam *g, int idx)
    {
        return ((igObject **)((igObjectList *)g->_playerDataListList)->_data)[idx];
    }

    static inline int GetProp(void *player, const char *name)
    {
        return igProperty_GetRecord(player, name)->value;
    }
};
extern "C" void beNDMWGameRam_RecomputeStats(beNDMWGameRam *self, int index, unsigned char apply);
extern "C" void beNDMWGameRam_FindTechniqueRow(beNDMWGameRam *receiver, void *player, int base_no, int *output);
extern "C" int DataList_GetData_00406da0(igDataList *p);
extern "C" int DataList_GetWordAt_00406dd0(igDataList *list, int index);
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
extern "C" ObjectRefTarget **ObjectRef_AssignObject_00406e60(ObjectRefTarget **destination,ObjectRefTarget *incoming);
extern "C" int DataList_GetData_00406f00(igUnsignedCharList *p);
extern "C" int DataObjInt_GetValue_00406f90(beDataObjInt *p);
extern "C" int g_stringPool[4];

static inline int countOf(const igObjectList *l) { return l->_count; }

void beNDMWGameRam_BuildDataList(beNDMWGameRam *self, igObjectList *out, const DataLayoutEntry *layout)
{
    int n1;
    int i1;
    int n5;
    int **d5;
    int i5;
    const DataLayoutEntry *entry = layout;
    unsigned char done = 0;
    void *alloc;

    do {
        switch (entry->type) {
        case DATA_INT: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjInt> s0((beDataObjInt *)beDataObjInt_Create(alloc));
            igNamedObject_SetName(s0.p, entry->name);
            ObjectList_AppendRetained(out, s0.p);
            break;
        }
        case DATA_INT_LIST: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjIntList> s1((beDataObjIntList *)beDataObjIntList_Create(alloc));
            igNamedObject_SetName(s1.p, entry->name);
            RESERVE(igIntList, s1.p, 4)
            RESIZE(igIntList, s1.p, 4)
            {
                igIntList *l1 = (igIntList *)s1.p->_data;
                n1 = l1->_count;
                int *d1 = (int *)l1->_data;
                for (i1 = 0; i1 < n1; i1++) d1[i1] = g_dataObjDefaults[0];
            }
            ObjectList_AppendRetained(out, s1.p);
            break;
        }
        case DATA_BOOL: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjBool> s2((beDataObjBool *)beDataObjBool_Create(alloc));
            igNamedObject_SetName(s2.p, entry->name);
            ObjectList_AppendRetained(out, s2.p);
            break;
        }
        case DATA_BOOL_LIST: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjBoolList> s3((beDataObjBoolList *)beDataObjBoolList_Create(alloc));
            igNamedObject_SetName(s3.p, entry->name);
            RESERVE(igBoolList, s3.p, 1)
            RESIZE(igBoolList, s3.p, 1)
            {
                igBoolList *l3 = (igBoolList *)s3.p->_data;
                int n3 = l3->_count;
                unsigned char *d3 = (unsigned char *)l3->_data;
                for (int i3 = 0; i3 < n3; i3++) d3[i3] = g_dataObjDefaultBool;
            }
            ObjectList_AppendRetained(out, s3.p);
            break;
        }
        case DATA_STRING: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjString> s4((beDataObjString *)beDataObjString_Create(alloc));
            igNamedObject_SetName(s4.p, entry->name);
            ObjectList_AppendRetained(out, s4.p);
            break;
        }
        case DATA_STRING_LIST: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjStringList> s5((beDataObjStringList *)beDataObjStringList_Create(alloc));
            igNamedObject_SetName(s5.p, entry->name);
            RESERVE(igStringRefList, s5.p, 4)
            StringList_Resize((void *)s5.p->_data, entry->count);
            Fill::emptyStrings(s5.p, StringRef(0), n5, d5, i5);
            ObjectList_AppendRetained(out, s5.p);
            break;
        }
        case DATA_OBJECT_LIST: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjObjectList> s6((beDataObjObjectList *)beDataObjObjectList_Create(alloc));
            igNamedObject_SetName(s6.p, entry->name);
            RESERVE(igObjectList, s6.p, 4)
            ObjectList_ResizeRetained((void *)s6.p->_data, entry->count);
            ObjectList_FillRetained((void *)s6.p->_data, 0);
            ObjectList_AppendRetained(out, s6.p);
            break;
        }
        case DATA_FLOAT_LIST: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjFloatList> s7((beDataObjFloatList *)beDataObjFloatList_Create(alloc));
            igNamedObject_SetName(s7.p, entry->name);
            RESERVE(igFloatList, s7.p, 4)
            RESIZE(igFloatList, s7.p, 4)
            {
                igFloatList *l7 = (igFloatList *)s7.p->_data;
                int n7 = l7->_count;
                float *d7 = (float *)l7->_data;
                for (int i7 = 0; i7 < n7; i7++) d7[i7] = *(float *)&g_dataObjDefaults[2];
            }
            ObjectList_AppendRetained(out, s7.p);
            break;
        }
        case DATA_END:
            done = 1;
            break;
        }
        entry++;
    } while (done == 0);
    {
        int n = out->_count;
        if (!(n < countOf(out))) List_Reserve(out, n, 4);
    }
}

static inline int count(const igObjectList *list) { return list->_count; }

static inline void storePlayerData(beNDMWGameRam *self, int index, const igSmartPointer<igObject> &value) {
    igObject *s2 = value.p;
    igObjectList *pl = (igObjectList *)self->_playerDataListList;
    igObject *o;
    if (s2 != 0) s2->_refCount = s2->_refCount + 1;
    o = ((igObject **)pl->_data)[index];
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
    }
    if (pl->_count != 0 && index >= 0 && index < pl->_count)
        ((igObject **)pl->_data)[index] = s2;
}

void beNDMWGameRam_ResetPlayer(beNDMWGameRam *self, int player) {
    igObjectList *common;
    igObjectList *flags;
    igObjectList *players;
    igObjectList *levels;
    igObjectList *skills;
    igObject *o;
    igObject *diskItem;
    int oldCount, i, clearCount, j, species, skillSpecies, skill, disk, index; igObject *playerData;
    int allocator, diskAllocator;
    if (player == 0) {
        common = (igObjectList *)self->_commonDataList;
        oldCount = common->_count;
        for (i = 0; i < oldCount; i++) {
            o = ((igObject **)common->_data)[i];
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
            }
        }
        clearCount = common->_count;
        for (j = 0; j < clearCount; j++) ((int *)common->_data)[j] = 0;
        common->_count = 0;
        beNDMWGameRam_BuildDataList(self, (igObjectList *)self->_commonDataList, g_commonDataLayout);
    }
    players = (igObjectList *)self->_playerDataListList;
    if (players->_count != 4) {
        if (count(players) < 5) List_Reserve(players, 4, 4);
        ObjectList_ResizeRetained(self->_playerDataListList, 4);
    }
    allocator = igObject_GetAllocator(self);
    if (g_useOwnerAllocator != 0) {
        allocator = (int)allocator;
    } else {
        allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
    }
    igSmartPointer<igObject> data(beDataObjList_Create(allocator));
    beNDMWGameRam_BuildDataList(self, (igObjectList *)data.p, g_playerDataLayout);
    for (species = 0; species < 16; species++) {
        levels = (igObjectList *)((igObject **)((void *)igProperty_GetRecordIntList(data.p, BASE_LEVEL)))[3];
        if (levels->_count != 0 && species >= 0 && species < levels->_count)
            ((int *)levels->_data)[species] = g_initialBaseLevel[0];
    }
    for (skillSpecies = 0; skillSpecies < 16; skillSpecies++) {
        for (skill = 0; skill < 9; skill++) {
            skills = (igObjectList *)((igObject **)((void *)igProperty_GetRecordIntList(data.p, BASE_SKILL)))[3];
            index = skill + skillSpecies * 9;
            if (skills->_count != 0 && index >= 0 && index < skills->_count)
                ((int *)skills->_data)[index] = g_initialBaseSkill[0];
        }
    }
    for (disk = 0; disk < 12; disk++) {
        diskAllocator = igObject_GetAllocator(self);
        if (g_useOwnerAllocator != 0) {
            diskAllocator = (int)diskAllocator;
        } else {
            diskAllocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
        }
        ItemRef item(beNDMWItemDisk_Create(diskAllocator));
        beNDMWItemDisk_Set(item.p, disk);
        playerData = data.p;
        diskItem = item.p;
        igObject **folder = (igObject **)igProperty_GetRecordFolder(playerData, DISKFOLDER);
        ObjectList_AppendRetained(folder[3], diskItem);
    }
    flags = (igObjectList *)((igObject **)igProperty_GetRecordArray(data.p, BASE_FLAG))[3];
    if (flags->_count != 0) {
        if (flags->_count > 960)
            ((unsigned char *)flags->_data)[960] = g_initialBaseFlag960;
    }
    storePlayerData(self, player, data);
}

void beNDMWGameRam_Initialize(beNDMWGameRam *self) {
    int player;
    int allocator;
    int playersAllocator;
    igObject *created;

    Gap__Core__igObject__vfunc_23(self);
    allocator = igObject_GetAllocator(self);
    if (g_useOwnerAllocator != 0) {
        allocator = (int)allocator;
    } else {
        allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
    }
    {
        /* The new list is owned by the stack reference while it is retained into the field and the old
         * list is released; the reference's own release runs at the block end. */
        igSmartPointer<igObject> common(beDataObjList_Create(allocator));
        created = common.p;
        if (created != 0) {
            created->_refCount = created->_refCount + 1;
        }
        ReleaseRef::go((igObject *)self->_commonDataList);
        self->_commonDataList = (int)created;
    }
    playersAllocator = igObject_GetAllocator(self);
    if (g_useOwnerAllocator != 0) {
        playersAllocator = (int)playersAllocator;
    } else {
        playersAllocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
    }
    {
        PlayerDataListListRef players(beDataObjListList_Create(playersAllocator));
        created = players.p;
        if (created != 0) {
            created->_refCount = created->_refCount + 1;
        }
        ReleaseRef::go((igObject *)self->_playerDataListList);
        self->_playerDataListList = (int)created;
    }
    player = 0;
    do {
        beNDMWGameRam_ResetPlayer(self, player);
        player += 1;
    } while (player < 4);
}

void beNDMWGameRam_ClearLists(beNDMWGameRam *self) {
    RefCountedHeader *data;
    ObjectRefList *common;
    int count;
    int i;
    int offset;
    int clearCount;
    int c;
    RefCountedHeader *playerData;
    ObjectRefList *players;
    int playerCount;
    int j;
    int playerOffset;
    int playerClearCount;
    int k;
    i = 0;
    common = (ObjectRefList *)self->_commonDataList;
    count = common->count;
    if (0 < count) {
        offset = 0;
        do {
            data = *(RefCountedHeader **)((char *)common->data + offset);
            if (data != 0) {
                data->refs--;
                if (!(data->refs & 0x7fffff)) igObject_Destroy(data);
            }
            i += 1;
            offset += 4;
        } while (i < count);
    }
    clearCount = common->count;
    for (c = 0; c < clearCount; c++) {
        common->data[c] = 0;
    }
    common->count = 0;
    if (!(0 < ((ObjectRefList *)self->_commonDataList)->count)) List_Reserve(self->_commonDataList, 0, 4);
    players = (ObjectRefList *)self->_playerDataListList;
    playerCount = players->count;
    j = 0;
    if (0 < playerCount) {
        playerOffset = 0;
        do {
            playerData = *(RefCountedHeader **)((char *)players->data + playerOffset);
            if (playerData != 0) {
                playerData->refs--;
                if (!(playerData->refs & 0x7fffff)) igObject_Destroy(playerData);
            }
            j += 1;
            playerOffset += 4;
        } while (j < playerCount);
    }
    playerClearCount = players->count;
    for (k = 0; k < playerClearCount; k++) {
        players->data[k] = 0;
    }
    players->count = 0;
    if (!(0 < ((ObjectRefList *)self->_playerDataListList)->count)) List_Reserve(self->_playerDataListList, 0, 4);
}

void beNDMWGameRam_ReleaseDataBases(beNDMWGameRam *self) {
    RefRelease::rel(self->_dBShinka);
    RefRelease::rel(self->_dBPcTech);
    RefRelease::rel(self->_dBWeapon);
    RefRelease::rel(self->_dBArmor1);
    RefRelease::rel(self->_dBArmor2);
    RefRelease::rel(self->_dBAbChip);
    RefRelease::rel(self->_dBEnemy);
    RefRelease::rel(self->_dBEneatk);
}

int beNDMWGameRam_CreateInfo(beNDMWGameRam *self) {
    beBaseInfoList *infos;
    beBaseInfoRamList *rams;
    int allocator;
    beNDMWGameRamInfoRam *created;
    infos = (beBaseInfoList *)self->_infoList;
    if (infos->_count == 0) {
        allocator = igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        igSmartPointer<beNDMWGameRamInfo> info(beNDMWGameRamInfo_Create(allocator));
        allocator = igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        RamRef ram(beNDMWGameRamInfoRam_Create(allocator));
        igNamedObject_SetName(info.p, gameram);
        ram.p->_parentInfo = (int)info.p;
        ram.p->_parentManager = (int)self;
        created = ram.p;
        created->_st0 = 0;
        created->_st3 = 0;
        created->_st2 = 0;
        created->_st1 = 0;
        ram.p->_ramNo = 0;
        ram.p->_isRun = 1;
        rams = (beBaseInfoRamList *)info.p->_ramList;
        ObjectList_AppendRetained((unsigned)rams, ram.p);
        ObjectList_AppendRetained((unsigned)self->_infoList, info.p);
        beMessenger_RegisterReceiverFromInfo(self->_messenger, ram.p, GAMERAM_6);
    }
    return 0;
}

void beNDMWGameRam_Update(void)
{
}

int beNDMWGameRam_FindSpecies(beNDMWGameRam *self, const char *modelName) {
    int species;
    char *interned;
    char *pooled;
    if (modelName == 0) {
        pooled = 0;
    } else {
        pooled = StringPool_Intern(SharedStringPool::get(), modelName);
    }
    StringRef name(pooled);
    species = 0;
    for (;;) {
        interned = name.p;
        if (beDataBase_GetRecordString(StatHelpers::shinka(self), species, MODEL_NAME) == interned) {
            return species;
        }
        species += 1;
        if (species >= 16) {
            return 0;
        }
    }
}

void beNDMWGameRam_SelectSpecies(beNDMWGameRam *self, int index, int species) {
/* matching construct: local declaration order fixes register allocation */
    int upcntOffset;
    igIntList *skills;
    int player;
    igIntList *baseUpcnts;
    igIntList *upcnts;
    PropertyRecord *commonCounter;
    int skillBase;
    int oldName;
    int upcntCount;
    PropertyRecord *commonFlagFolder;
    int level;
    int skillCount;
    igIntList *baseLevels;
    igObject *flagFolder;
    igIntList *baseExps;
    int value;
    PropertyRecord *commonFlags;
    PropertyRecord *nameRecord;
    igObject *released;
    int upcntBase;
    igObject *flags;
    igObject *counter;
    int skill;
    int skillValue;
    int modelName;
    int skillOffset;
    igIntList *baseSkills;
    int upcnt;
    int interned;
    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[index];
    igProperty_GetRecord(player, LEVEL_2);
    ((PropertyRecord *)igProperty_GetRecord(player, DIGIMONNO_2))->value = (void *)species;
    modelName = ((int)beDataBase_GetRecordString(StatHelpers::shinka(self), species, MODEL_NAME));
    nameRecord = igProperty_GetRecordString((void *)player, DIGIMONNAME_2);
    interned = ((int)StringPool_Intern(SharedStringPool::get(), modelName));
    oldName = (int)nameRecord->value;
    if (oldName != 0) {
        int *p = (int *)(oldName - 8);
        int c = *(int *)(oldName - 4) - 1;
        *(int *)(oldName - 4) = c;
        if (c == 0) StringChunk_ReleaseHeader(*p, p);
    }
    nameRecord->value = (void *)interned;
    baseLevels = (igIntList *)((PropertyRecord *)igProperty_GetRecordIntList(player, BASE_LEVEL))->value;
    level = ((int *)baseLevels->_data)[species];
    ((PropertyRecord *)igProperty_GetRecord(player, LEVEL_2))->value = (void *)level;
    baseExps = (igIntList *)((PropertyRecord *)igProperty_GetRecordIntList(player, BASE_EXP))->value;
    value = ((int *)baseExps->_data)[species];
    ((PropertyRecord *)igProperty_GetRecord(player, EXP))->value = (void *)value;
    /* matching construct: skillBase/upcntBase hoisted into locals, else MWCC strength-reduces the index */
    skillBase = species * 9;
    skill = 0;
    skillOffset = 0;
    do {
        baseSkills = (igIntList *)((PropertyRecord *)igProperty_GetRecordIntList(player, BASE_SKILL))->value;
        skillValue = ((int *)baseSkills->_data)[skillBase + skill];
        skills = (igIntList *)((PropertyRecord *)igProperty_GetRecordIntList(player, SKILL, baseSkills))->value;
        skillCount = skills->_count;
        if (skillCount != 0 && skill >= 0 && skill < skillCount) ((int *)(skills->_data + skillOffset))[0] = skillValue;
        skill += 1;
        skillOffset += 4;
    } while (skill < 9);
    upcntBase = species * 11;
    upcnt = 0;
    upcntOffset = 0;
    do {
        baseUpcnts = (igIntList *)((PropertyRecord *)igProperty_GetRecordIntList(player, BASE_UPCNT))->value;
        value = ((int *)baseUpcnts->_data)[upcntBase + upcnt];
        upcnts = (igIntList *)((PropertyRecord *)igProperty_GetRecordIntList(player, UPCNT, baseUpcnts))->value;
        upcntCount = upcnts->_count;
        if (upcntCount != 0 && upcnt >= 0 && upcnt < upcntCount) ((int *)(upcnts->_data + upcntOffset))[0] = value;
        upcnt += 1;
        upcntOffset += 4;
    } while (upcnt < 11);
    if (index == 0) {
        flags = (igObject *)((PropertyRecord *)igProperty_GetRecordArray(player, BASE_FLAG))->value;
        commonFlags = ((PropertyRecord *)igProperty_GetRecordArray(self->_commonDataList, FLAG_2));
        if (flags != 0) flags->_refCount = flags->_refCount + 1;
        released = (igObject *)commonFlags->value;
        RELO(released)
        commonFlags->value = flags;
        flagFolder = (igObject *)((PropertyRecord *)igProperty_GetRecordArray(player, BASE_FLAGFOLDER))->value;
        commonFlagFolder = ((PropertyRecord *)igProperty_GetRecordArray(self->_commonDataList, FLAGFOLDER));
        if (flagFolder != 0) flagFolder->_refCount = flagFolder->_refCount + 1;
        released = (igObject *)commonFlagFolder->value;
        RELO(released)
        commonFlagFolder->value = flagFolder;
        counter = (igObject *)((PropertyRecord *)igProperty_GetRecordIntList(player, BASE_COUNTER))->value;
        commonCounter = ((PropertyRecord *)igProperty_GetRecordIntList(self->_commonDataList, COUNTER));
        if (counter != 0) counter->_refCount = counter->_refCount + 1;
        released = (igObject *)commonCounter->value;
        RELO(released)
        commonCounter->value = counter;
    }
}

/* Current player record -> BASE_* save arrays, the mirror of beNDMWGameRam_SelectSpecies: LEVEL
 * and EXP go to the species' slot of BASE_LEVEL / BASE_EXP, SKILL[9] and UPCNT[11] to
 * BASE_SKILL[species * 9 + i] / BASE_UPCNT[species * 11 + i], each store bounds-checked against
 * the destination list's count. */

void beNDMWGameRam_StoreSpecies(beNDMWGameRam *self, int player_index)
{
    int upcnt_base;
    igIntList *exp_list;
    int player;
    int upcnt;
    int skill_base;
    int skill_index;
    int skill;
    int upcnt_index;
    int species;
    int value;
    igIntList *level_list;
    igIntList *player_list;
    IntListProperty *base_array;

    player_list = (igIntList *)self->_playerDataListList;
    player = ((int *)player_list->_data)[player_index];
    species = ((IntProperty *)igProperty_GetRecord(player, DIGIMONNO_2))->value;
    value = ((IntProperty *)igProperty_GetRecord(player, LEVEL_2))->value;
    level_list = ((IntListProperty *)igProperty_GetRecordIntList(player, BASE_LEVEL))->list;
    if (level_list->_count != 0 && species >= 0 && species < level_list->_count)
        ((int *)level_list->_data)[species] = value;
    value = ((IntProperty *)igProperty_GetRecord(player, EXP))->value;
    exp_list = ((IntListProperty *)igProperty_GetRecordIntList(player, BASE_EXP))->list;
    if (exp_list->_count != 0 && species >= 0 && species < exp_list->_count)
        ((int *)exp_list->_data)[species] = value;
    skill_base = species * 9;
    for (skill_index = 0; skill_index < 9; ++skill_index) {
        skill = ((int *)((IntListProperty *)igProperty_GetRecordIntList(player, SKILL))->list->_data)[skill_index];
        base_array = ((IntListProperty *)igProperty_GetRecordIntList(player, BASE_SKILL));
        if (base_array->list->_count != 0 && skill_base + skill_index >= 0 &&
            skill_base + skill_index < base_array->list->_count)
            ((int *)base_array->list->_data)[skill_base + skill_index] = skill;
    }
    upcnt_base = species * 11;
    for (upcnt_index = 0; upcnt_index < 11; ++upcnt_index) {
        upcnt = ((int *)((IntListProperty *)igProperty_GetRecordIntList(player, UPCNT))->list->_data)[upcnt_index];
        base_array = ((IntListProperty *)igProperty_GetRecordIntList(player, BASE_UPCNT));
        if (base_array->list->_count != 0 && upcnt_base + upcnt_index >= 0 &&
            upcnt_base + upcnt_index < base_array->list->_count)
            ((int *)base_array->list->_data)[upcnt_base + upcnt_index] = upcnt;
    }
}

void beNDMWGameRam_GiveInitialWeapons(beNDMWGameRam *self, int index) {
    igObjectList *devices;
    int count;
    int allocator;
    void *weapon;
    int slot;
    RefCountedHeader *released;
    int i;
    int clearCount;
    RefCountedHeader *fetched;
    int *field;
    int c;
    int player;
    int species;
    player = ((int *)((igObjectList *)self->_playerDataListList)->_data)[index];
    devices = ((ObjectListProperty *)igProperty_GetRecordFolder(player, DEVICEFOLDER))->list;
    species = ((IntProperty *)((void *)igProperty_GetRecord(player, DIGIMONNO_2)))->value;
    count = devices->_count;
    i = 0;
    if (0 < count) {
        do {
            released = ((RefCountedHeader **)devices->_data)[i];
            if (released != 0) {
                released->refs--;
                if (!(released->refs & 0x7fffff)) igObject_Destroy(released);
            }
            i += 1;
        } while (i < count);
    }
    clearCount = devices->_count;
    for (c = 0; c < clearCount; c++) {
        ((int *)devices->_data)[c] = 0;
    }
    devices->_count = 0;
    slot = 0;
    field = g_initialWeaponFields;
    do {
        allocator = igObject_GetAllocator(self);
        allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
        {
        RecoveryRef<1> weaponRef(beNDMWItemWeapon_Create(allocator), false);
        weapon = weaponRef.value;
        if (self->_dBShinka == 0) {
            beMessenger_SendNamed(self->_messenger, DATABASE_3, shinka_2, 0, GETDATABASE_3);
            fetched = (RefCountedHeader *)beMessenger_GetObject(self->_messenger, 0);
            if (fetched != 0) {
                fetched->refs++;
            }
            released = (RefCountedHeader *)self->_dBShinka;
            if (released != 0) {
                released->refs--;
                if (!(released->refs & 0x7fffff)) igObject_Destroy(released);
            }
            self->_dBShinka = (int)fetched;
        }
        beNDMWItemWeapon_Set(weapon, beDataBase_GetRecordInt((void *)self->_dBShinka, species, *field), 0, 0);
        ObjectList_AppendRetained(devices, weaponRef.value);
        }
        slot += 1;
        field += 1;
    } while (slot < 3);
}

void beNDMWGameRam_EquipWeapon(beNDMWGameRam *self, int index, int apply)
{
    void *player = ((void **)((igObjectList *)self->_playerDataListList)->_data)[index];
    igObjectList *pocket = ((ObjectListProperty *)igProperty_GetRecordFolder(player, (char *)DEVICEFOLDER))->list;

    if ((apply & 0xff) == 0) {
        igObjectList *sockets = ((ObjectListProperty *)igProperty_GetRecordFolder(player, (char *)POWERSOCKET))->list;
        igStringRefList *names = igProperty_GetRecordStringList(player, POWERSOCKETNAME)->list;
        int oldCount = sockets->_count;
        for (int r = 0; r < oldCount; r++) {
            beNDMWItemBase *prev = ((beNDMWItemBase **)sockets->_data)[r];
            if (prev) {
                --prev->_refCount;
                if (((unsigned long long)(long long)(int)prev->_refCount & 0x7fffffULL) == 0)
                    igObject_Destroy(prev);
            }
        }
        int clearCount = sockets->_count;
        for (int c = 0; c < clearCount; c++) ((beNDMWItemBase **)sockets->_data)[c] = 0;
        sockets->_count = 0;
        int nameCount = names->_count;
        for (int i = 0; i < nameCount; i++) {
            char **entry = &((char **)names->_data)[i];
            char *old, *fresh;
            fresh = StringPool_Intern(SharedStringPool::get(), 0);
            old = *entry;
            if (old) {
                int *header = (int *)(old - 8);
                if (--header[1] == 0) StringChunk_ReleaseHeader(header[0], header);
            }
            *entry = fresh;
        }
        names->_count = 0;
        int pocketCount = pocket->_count;
        for (int p = 0; p < pocketCount; p++) {
            if (sockets->_count == 3) break;
            beNDMWItemBase *item = ((beNDMWItemBase **)pocket->_data)[p];
            if (item->_kindNo == 0) {
                ObjectList_AppendRetained(sockets, item);
                const char *model = beNDMWItemBase_GetRecordString(item, self, MODEL);
                char *interned;
                if (!model) {
                    interned = 0;
                } else {
                    interned = StringPool_Intern(SharedStringPool::get(), model);
                }
                StringList_AppendRetained((int)names, StringRef(interned));
                item->_isEquip = 1;
            }
        }
    } else {
        int species = igProperty_GetRecord(player, (char *)DIGIMONNO_2)->value;
        int bit;
        igIntList *skills;
        igStringRefList *names;
        int fits, skillNo;
        igObjectList *sockets;
        skills = ((IntListProperty *)igProperty_GetRecordIntList(player, (char *)SKILL))->list;
        sockets = ((ObjectListProperty *)igProperty_GetRecordFolder(player, (char *)POWERSOCKET))->list;
        names = igProperty_GetRecordStringList(player, POWERSOCKETNAME)->list;
        int pocketCount = pocket->_count;
        for (int u = 0; u < pocketCount; u++) {
            beNDMWItemBase *item = ((beNDMWItemBase **)pocket->_data)[u];
            if (item->_kindNo == 0) item->_isEquip = 0;
        }
        ObjectList_FillRetained(sockets, 0, pocketCount);
        int nameCount = names->_count;
        for (int i = 0; i < nameCount; i++) {
            char **entry = &((char **)names->_data)[i];
            char *old, *fresh;
            fresh = StringPool_Intern(SharedStringPool::get(), 0);
            old = *entry;
            if (old) {
                int *header = (int *)(old - 8);
                if (--header[1] == 0) StringChunk_ReleaseHeader(header[0], header);
            }
            *entry = fresh;
        }
        int bestValue = 0;
        int best = -1;
        names->_count = 0;
        int count2 = pocket->_count;
        int k = 0;
        bit = 1 << species;
        for (; k < count2; k++) {
            beNDMWItemBase *item = ((beNDMWItemBase **)pocket->_data)[k];
            if (item->_kindNo == 0) {
                fits = bit & beNDMWItemBase_GetRecordInt(item, self, SOUBI);
                skillNo = beNDMWItemBase_GetRecordInt(item, self, (char *)SKILL);
                int need = beNDMWItemBase_GetRecordInt(item, self, SKILLPOINT);
                if (fits != 0 && ((int *)skills->_data)[skillNo] >= need &&
                    (best < 0 || bestValue < beNDMWItemBase_GetRecordInt(item, self, TSUYOSA))) {
                    bestValue = beNDMWItemBase_GetRecordInt(item, self, TSUYOSA);
                    best = k;
                }
            }
        }
        if (best >= 0) {
            beNDMWItemBase *chosen = ((beNDMWItemBase **)pocket->_data)[best];
            if (chosen) ++chosen->_refCount;
            beNDMWItemBase *first = ((beNDMWItemBase **)sockets->_data)[0];
            if (first) {
                --first->_refCount;
                if (((unsigned long long)(long long)(int)first->_refCount & 0x7fffffULL) == 0)
                    igObject_Destroy(first);
            }
            int sc = sockets->_count;
            int zero = 0;
            if (sc != 0 && zero < sc) ((beNDMWItemBase **)sockets->_data)[0] = chosen;
            const char *model = beNDMWItemBase_GetRecordString(chosen, self, MODEL);
            char *interned;
            if (!model) {
                interned = 0;
            } else {
                interned = StringPool_Intern(SharedStringPool::get(), model);
            }
            StringList_AppendRetained((int)names, StringRef(interned));
            chosen->_isEquip = 1;
        }
    }
}

unsigned char beNDMWGameRam_HasUsableWeapon(beNDMWGameRam *self, int index, int species) {
    int player;
    igObjectList *devices;
    igIntList *skills;
    int base;
    int mask;
    int count;
    int i;
    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[index];
    devices = ((ObjectListProperty *)igProperty_GetRecordFolder(player, DEVICEFOLDER))->list;
    {
    int current = ((IntProperty *)igProperty_GetRecord(player, DIGIMONNO_2))->value;
    if (current == species) {
        skills = ((IntListProperty *)igProperty_GetRecordIntList(player, SKILL))->list;
        base = 0;
    } else {
        skills = ((IntListProperty *)igProperty_GetRecordIntList(player, BASE_SKILL))->list;
        base = species * 9;
    }
    }
    mask = 1 << species;
    count = devices->_count;
    for (i = 0; i < count; i++) {
        beNDMWItemBase *item = ((beNDMWItemBase **)devices->_data)[i];
        if (item->_kindNo == 0) {
            int fits = mask & beNDMWItemBase_GetRecordInt(item, self, SOUBI);
            int skillNo = beNDMWItemBase_GetRecordInt(item, self, SKILL);
            int need = beNDMWItemBase_GetRecordInt(item, self, SKILLPOINT);
            if (fits != 0 && ((int *)skills->_data)[base + skillNo] >= need) return 1;
        }
    }
    return 0;
}

void beNDMWGameRam_JoinPlayer(beNDMWGameRam *self, int index, const char *modelName) {
    int joined;
    int i;
    int common;
    int offset;
    int player;
    int species;
    igDataList *used;
    BoolProperty *isUse;

    common = self->_commonDataList;
    player = ((int *)((igObjectListList *)self->_playerDataListList)->_data)[index];
    species = beNDMWGameRam_FindSpecies(self, modelName);
    beNDMWGameRam_SelectSpecies(self, index, species);
    beNDMWGameRam_GiveInitialWeapons(self, index);
    beNDMWGameRam_EquipWeapon(self, index, 0);
    beNDMWGameRam_RecomputeStats(self, index, (unsigned char)1);
    isUse = igProperty_GetRecordByte(player, ISUSE_4);
    isUse->value = 1;
    used = ((DataListProperty *)igProperty_GetRecordArray(player, BASE_ISUSE))->list;
    if (used->_count != 0 && species >= 0 && species < used->_count) {
        *(char *)(species + used->_data) = g_speciesUsedMark;
    }
    joined = 0;
    i = 0;
    offset = 0;
    do {
        if (igProperty_GetRecordByte(*(int *)(((igObjectListList *)self->_playerDataListList)->_data + offset), ISUSE_4)->value != 0) {
            joined += 1;
        }
        i += 1;
        offset += 4;
    } while (i < 4);
    ((IntProperty *)igProperty_GetRecord(common, NINZU_2))->value = joined;
}

void beNDMWGameRam_JoinPlayerWithName(beNDMWGameRam *self, int index, void *modelName, StringRef name) {
    int player;
    int allocator;
    igObjectList *names;
    int n, n2, i, j;
    unsigned short *src;
    unsigned short *base;
    int k;
    unsigned short *dst;
    igObject *released;
    beNDMWGameRam_JoinPlayer(self, index, (const char *)modelName);
    player = ((int *)(((igObjectList *)self->_playerDataListList)->_data))[index];
    allocator = igObject_GetAllocator(self);
    allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
    igSmartPointer<beUnicodeObj> unicodeName(beUnicodeObj_Create(allocator));
    beUnicodeObj_AllocateBuffer(unicodeName.p, 8);
    {
        /* The looked-up name is an out-parameter the lookup retains; it is released by hand rather
         * than by a destructor. */
        beUnicodeObj *converted;
        int text = (int)name.p;
        int font = igInsightCore_FindManager(self->_insight, g_beFont_metaObject[0]);
        beFont_ConvertToUnicode(&converted, font, text);
        k = 0;
        src = (unsigned short *)converted->_buffer;
        base = (unsigned short *)unicodeName.p->_buffer;
        dst = base;
        for (;;) {
            *dst = *src;
            if (*src == 0) break;
            k++; src++; dst++;
            if (k >= 8) break;
        }
        for (; k < 8; k++) base[k] = 0;
        {
            beUnicodeObj *convertedRef;
            if ((convertedRef = converted) != 0) {
                --convertedRef->_refCount;
                if ((convertedRef->_refCount & 0x7fffff) == 0) igObject_Destroy(convertedRef);
            }
        }
    }
    names = ((ObjectListProperty *)igProperty_GetRecordFolder(player, PLAYERNAME))->list;
    if (countOf(names) != 0) {
        n = names->_count;
        for (i = 0; i < n; i++) {
            released = ((igObject **)names->_data)[i];
            if (released != 0) {
                released->_refCount = released->_refCount - 1;
                if ((released->_refCount & 0x7FFFFF) == 0) igObject_Destroy(released);
            }
        }
        n2 = names->_count;
        for (j = 0; j < n2; j++) ((igObject **)names->_data)[j] = 0;
        names->_count = 0;
    }
    ObjectList_AppendRetained(names, unicodeName.p);
}

void beNDMWGameRam_JoinPlayerWithUnicodeName(beNDMWGameRam *self, int index, void *modelName, RecoveryRef<0> name) {
    igObjectList *names;
    ObjectListProperty *nameFolder;
    int n;
    int n2;
    int i;
    int j;
    igObject *released;

    beNDMWGameRam_JoinPlayer(self, index, (const char *)modelName);
    nameFolder = (ObjectListProperty *)igProperty_GetRecordFolder(((int *)(((igObjectList *)self->_playerDataListList)->_data))[index], PLAYERNAME);
    names = nameFolder->list;
    if (countOf(names) != 0) {
        n = names->_count;
        for (i = 0; i < n; i++) {
            released = ((igObject **)names->_data)[i];
            if (released != 0) {
                released->_refCount = released->_refCount - 1;
                if ((released->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(released);
                }
            }
        }
        n2 = names->_count;
        for (j = 0; j < n2; j++) {
            ((igObject **)names->_data)[j] = 0;
        }
        names->_count = 0;
    }
    ObjectList_AppendRetained(names, name.value);
}

void beNDMWGameRam_LeavePlayer(beNDMWGameRam *self, int index) {
    int joined;
    int i;
    int common;
    int offset;

    common = self->_commonDataList;
    igProperty_GetRecordByte(((int *)((igObjectList *)self->_playerDataListList)->_data)[index], ISUSE_4)->value = 0;
    joined = 0;
    i = 0;
    offset = 0;
    do {
        if (igProperty_GetRecordByte(((int *)(((igObjectList *)self->_playerDataListList)->_data + offset))[0], ISUSE_4)->value != 0) {
            joined += 1;
        }
        i += 1;
        offset += 4;
    } while (i < 4);
    ((IntProperty *)igProperty_GetRecord(common, NINZU_2))->value = joined;
}

/* HP update. Returns 0 when a delta is applied to a dead player (HP 0), else 1. */
int beNDMWGameRam_ChangeHp(beNDMWGameRam *self, int player_index, int delta, int absolute)
{
    int hp;
    int player;
    int max_hp;

    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[player_index];
    max_hp = ((IntProperty *)igProperty_GetRecord(player, MHP))->value;
    hp = ((IntProperty *)igProperty_GetRecord(player, HP))->value;
    if (absolute == NO_ABSOLUTE_HP) {
        if (hp == 0)
            return 0;
        hp += delta;
    } else {
        hp = absolute;
    }
    if (hp < 0)
        hp = 0;
    if (hp > max_hp)
        hp = max_hp;
    ((IntProperty *)igProperty_GetRecord(player, HP))->value = hp;
    beMessenger_SelectReceivers(self->_messenger, METERCTRL, hpmt, player_index);
    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)hp / (float)max_hp);
    beMessenger_DispatchSelected(self->_messenger, SETPERCENT);
    beMessenger_SelectReceivers(self->_messenger, NUMBERCTRL, hpnm, player_index);
    beMessenger_AppendInt(self->_messenger, hp);
    beMessenger_DispatchSelected(self->_messenger, SETVALUE);
    return 1;
}

/* MP update by delta. */
void beNDMWGameRam_ChangeMp(beNDMWGameRam *self, int player_index, int delta)
{
    int mp;
    int player;
    int max_mp;

    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[player_index];
    max_mp = ((IntProperty *)igProperty_GetRecord(player, MMP))->value;
    mp = ((IntProperty *)igProperty_GetRecord(player, MP))->value;
    mp += delta;
    if (mp < 0)
        mp = 0;
    if (mp > max_mp)
        mp = max_mp;
    ((IntProperty *)igProperty_GetRecord(player, MP))->value = mp;
    beMessenger_SelectReceivers(self->_messenger, METERCTRL, mpmt, player_index);
    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)mp / (float)max_mp);
    beMessenger_DispatchSelected(self->_messenger, SETPERCENT);
    beMessenger_SelectReceivers(self->_messenger, NUMBERCTRL, mpnm, player_index);
    beMessenger_AppendInt(self->_messenger, mp);
    beMessenger_DispatchSelected(self->_messenger, SETVALUE);
}

void beNDMWGameRam_AddPowerSocketBonus(int self, int player, int *total, const char *name, int withRevision) {
    beNDMWItemRevisionBase *item;
    if (((igObjectList *)((beDataObjObjectList *)igProperty_GetRecordFolder(player, POWERSOCKET))->_data)->_count != 0) {
        item = ((beNDMWItemRevisionBase **)((igObjectList *)((beDataObjObjectList *)igProperty_GetRecordFolder(player, POWERSOCKET))->_data)->_data)[0];
        if (item != 0) {
            *total += beNDMWItemBase_GetRecordInt(item, self, name);
            if (withRevision != 0) {
                *total += (int)item->_revision;
            }
        }
    }
}

void beNDMWGameRam_AddPowerPocketBonus(int self, int player, int *total, const char *name) {
    int count;
    int item;
    int i;
    count = ((ObjectListProperty *)igProperty_GetRecordFolder(player, POWERPOCKET))->list->_count;
    i = 0;
    if (0 < count) {
        do {
            item = ((int *)((ObjectListProperty *)igProperty_GetRecordFolder(player, POWERPOCKET))->list->_data)[i];
            if (item != 0) {
                *total += beNDMWItemBase_GetRecordInt(item, self, name);
            }
            i += 1;
        } while (i < count);
    }
}

void beNDMWGameRam_AddMainSlotBonus(beNDMWGameRam *self, void *player, int *total, const char *name, int withFlat) {
    beNDMWItemBase *item;
    if (((ObjectListProperty *)igProperty_GetRecordFolder(player, (const char *)MAINSLOT))->list->_count != 0) {
        item = ((beNDMWItemBase **)((ObjectListProperty *)igProperty_GetRecordFolder(player, (const char *)MAINSLOT))->list->_data)[0];
        if (item != 0) {
            *total += beNDMWItemBase_GetRecordInt(item, self, name);
            if (withFlat != 0) {
                *total += ((BonusItem *)item)->flat;
            }
        }
    }
}

void beNDMWGameRam_AddMainPocketBonus(int self, int player, int *total, const char *name) {
    int item;
    int count;
    int i;
    count = ((ObjectListProperty *)igProperty_GetRecordFolder(player, MAINPOCKET))->list->_count;
    for (i = 0; i < count; i++) {
        item = ((int *)((ObjectListProperty *)igProperty_GetRecordFolder(player, MAINPOCKET))->list->_data)[i];
        if (item != 0) {
            *total += beNDMWItemBase_GetRecordInt(item, self, name);
        }
    }
}

void beNDMWGameRam_AddSubSlotBonus(int self, int player, int *total, const char *name, int withAbility) {
    beNDMWItemBase *item; int bonus;
    if (((ObjectListProperty *)igProperty_GetRecordFolder(player, SUBSLOT))->list->_count != 0) {
        item = *(beNDMWItemBase **)((ObjectListProperty *)igProperty_GetRecordFolder(player, SUBSLOT))->list->_data;
        if (item != 0) {
            bonus = beNDMWItemBase_GetRecordInt(item, self, name); *total += bonus;
            if (withAbility != 0 && strcmp(((char *)beNDMWItemBase_GetRecordString(item, self, SHUSEINOURYOKU)), name) == 0) {
                *total += ((beNDMWItemCountView *)item)->_count;
            }
        }
    }
}

int beNDMWGameRam_CalcMaxPoints(beNDMWGameRam *self, int index, int species, int isHp) {
    void *player;
    int record;
    IntValues *upcnts;
    int base;
    int level;
    int initial;
    int growth;
    int bonus;
    int band;
    int *bandMax;
    int result;
    player = (void *)((int *)((igObjectListList *)self->_playerDataListList)->_data)[index];
    record = species;
    if (record < 0) {
        record = igProperty_GetRecord(player, ((char *)DIGIMONNO_2))->value;
        upcnts = igProperty_GetRecordIntList(player, UPCNT)->list;
        base = 0;
        level = igProperty_GetRecord(player, LEVEL_2)->value;
    } else {
        upcnts = igProperty_GetRecordIntList(player, BASE_UPCNT)->list;
        base = record * 11;
        level = igProperty_GetRecordIntList(player, ((char *)BASE_LEVEL))->list->values[record];
    }
    if (isHp != 0) {
        initial = beDataBase_GetRecordInt(StatHelpers::shinka(self), record, MHP_INI);
        growth = beDataBase_GetRecordInt(StatHelpers::shinka(self), record, MHP_GROW);
        bonus = upcnts->values[base];
    } else {
        initial = beDataBase_GetRecordInt(StatHelpers::shinka(self), record, MMP_INI);
        growth = beDataBase_GetRecordInt(StatHelpers::shinka(self), record, MMP_GROW);
        { char *d = (char *)upcnts->values; bonus = *(int *)(d + (base + 1) * 4); }
    }
    band = 0;
    bandMax = g_growthBandMaxLevel;
    loop: if (*bandMax < level) { bandMax++; band++; goto loop; }
    result = bonus + (initial + growth * (g_pointGrowthBandBase[band] + g_pointGrowthBandRate[band] * (level - g_growthBandStartLevel[band])) / 100);
    if (result > 99999) result = 99999;
    return result;
}

int beNDMWGameRam_CalcAttribute(beNDMWGameRam *self, int index, int species, int attribute) {
    void *player;
    int record;
    IntValues *upcnts;
    int base;
    int level;
    int initial;
    int growth;
    int bonus;
    int band;
    int *bandMax;
    int result;
    player = (void *)((int *)((igDataList *)self->_playerDataListList)->_data)[index];
    record = species;
    if (record < 0) {
        record = igProperty_GetRecord(player, ((char *)DIGIMONNO_2))->value;
        upcnts = igProperty_GetRecordIntList(player, UPCNT)->list;
        base = 0;
        level = igProperty_GetRecord(player, LEVEL_2)->value;
    } else {
        upcnts = igProperty_GetRecordIntList(player, BASE_UPCNT)->list;
        base = record * 11;
        level = igProperty_GetRecordIntList(player, ((char *)BASE_LEVEL))->list->values[record];
    }
    initial = beDataBase_GetRecordInt(AttributeHelpers::shinka(self), record, g_attributeInitialFields[attribute]);
    growth = beDataBase_GetRecordInt(AttributeHelpers::shinka(self), record, g_attributeGrowthFields[attribute]);
    bonus = upcnts->values[base + 2 + attribute];
    band = 0;
    bandMax = g_growthBandMaxLevel;
    loop: if (*bandMax < level) { bandMax++; band++; goto loop; }
    result = bonus + (initial + growth * (g_attributeGrowthBandBase[band] + g_attributeGrowthBandRate[band] * (level - g_growthBandStartLevel[band])) / 100);
    if (result > 9999) result = 9999;
    return result;
}

void beNDMWGameRam_RecomputeStats(beNDMWGameRam *self, int index, unsigned char apply)
{
    void *player = RecomputeHelpers::GetPlayer(self, index);
    int species = RecomputeHelpers::GetProp(player, (char *)DIGIMONNO_2);
    int level = RecomputeHelpers::GetProp(player, LEVEL_2);
    unsigned char first = 0;

    /* MHP / HP */
    int mhp = beNDMWGameRam_CalcMaxPoints(self, index, -1, 1);
    mhp += igProperty_GetRecordIntList(player, UPDATA)->list->values[6];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &mhp, MAXHP, 0);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &mhp, MAXHP, 0);
    }
    if (mhp > 99999) mhp = 99999;
    igProperty_GetRecord(player, MHP)->value = mhp;
    int curHp = igProperty_GetRecord(player, HP)->value;
    if (curHp == 0) first = 1;
    if (curHp == 0 || mhp < curHp) igProperty_GetRecord(player, HP)->value = mhp;

    int mmp = beNDMWGameRam_CalcMaxPoints(self, index, -1, 0);
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &mmp, MAXMP, 0);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &mmp, MAXMP, 0);
    }
    if (mmp > 99999) mmp = 99999;
    igProperty_GetRecord(player, MMP)->value = mmp;
    int curMp = igProperty_GetRecord(player, MP)->value;
    if (first || mmp < curMp) igProperty_GetRecord(player, MP)->value = mmp;

    int tsuyosa = beNDMWGameRam_CalcAttribute(self, index, -1, 0);
    tsuyosa += igProperty_GetRecordIntList(player, UPDATA)->list->values[4];
    tsuyosa -= igProperty_GetRecordIntList(player, DOWNDATA)->list->values[4];
    if (apply) {
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &tsuyosa, TSUYOSA, 1);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &tsuyosa, TSUYOSA);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &tsuyosa, TSUYOSA, 1);
    }
    CLAMP_ATTR(tsuyosa)
    igProperty_GetRecord(player, TSUYOSA)->value = tsuyosa;

    int mamori = beNDMWGameRam_CalcAttribute(self, index, -1, 1);
    mamori += igProperty_GetRecordIntList(player, UPDATA)->list->values[5];
    mamori -= igProperty_GetRecordIntList(player, DOWNDATA)->list->values[5];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &mamori, MAMORI, 1);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &mamori, MAMORI, 1);
    }
    CLAMP_ATTR(mamori)
    igProperty_GetRecord(player, MAMORI)->value = mamori;

    int kashikosa = beNDMWGameRam_CalcAttribute(self, index, -1, 2);
    if (apply) {
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &kashikosa, KASHIKOSA, 0);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &kashikosa, KASHIKOSA);
        beNDMWGameRam_AddMainSlotBonus(self, player, &kashikosa, KASHIKOSA, 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &kashikosa, KASHIKOSA);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &kashikosa, KASHIKOSA, 1);
    }
    CLAMP_ATTR(kashikosa)
    igProperty_GetRecord(player, KASHIKOSA)->value = kashikosa;

    int seishin = beNDMWGameRam_CalcAttribute(self, index, -1, 3);
    if (apply) {
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &seishin, SEISHIN, 0);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &seishin, SEISHIN);
        beNDMWGameRam_AddMainSlotBonus(self, player, &seishin, SEISHIN, 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &seishin, SEISHIN);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &seishin, SEISHIN, 0);
    }
    CLAMP_ATTR(seishin)
    igProperty_GetRecord(player, SEISHIN)->value = seishin;

    int subayasa = beNDMWGameRam_CalcAttribute(self, index, -1, 4);
    subayasa += igProperty_GetRecordIntList(player, UPDATA)->list->values[0];
    subayasa -= igProperty_GetRecordIntList(player, DOWNDATA)->list->values[0];
    if (apply) {
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &subayasa, SUBAYASA, 0);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &subayasa, SUBAYASA);
        beNDMWGameRam_AddMainSlotBonus(self, player, &subayasa, SUBAYASA, 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &subayasa, SUBAYASA);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &subayasa, SUBAYASA, 1);
    }
    CLAMP_ATTR(subayasa)
    igProperty_GetRecord(player, SUBAYASA)->value = subayasa;

    int fire = beDataBase_GetRecordInt(RecomputeHelpers::shinka(self), species, RES_FIRE);
    fire += igProperty_GetRecordIntList(player, UPCNT)->list->values[7];
    fire += igProperty_GetRecordIntList(player, UPDATA)->list->values[7];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &fire, RES_FIRE, 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &fire, RES_FIRE);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &fire, RES_FIRE, 1);
    }
    CLAMP_ATTR(fire)
    igProperty_GetRecord(player, HONOOTEIKO)->value = fire;
    int ice = beDataBase_GetRecordInt(RecomputeHelpers::shinka(self), species, RES_ICE);
    ice += igProperty_GetRecordIntList(player, UPCNT)->list->values[8];
    ice += igProperty_GetRecordIntList(player, UPDATA)->list->values[8];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &ice, RES_ICE, 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &ice, RES_ICE);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &ice, RES_ICE, 1);
    }
    CLAMP_ATTR(ice)
    igProperty_GetRecord(player, KOORITEIKO)->value = ice;
    int thunder = beDataBase_GetRecordInt(RecomputeHelpers::shinka(self), species, RES_THUNDER);
    thunder += igProperty_GetRecordIntList(player, UPCNT)->list->values[9];
    thunder += igProperty_GetRecordIntList(player, UPDATA)->list->values[9];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &thunder, RES_THUNDER, 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &thunder, RES_THUNDER);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &thunder, RES_THUNDER, 1);
    }
    CLAMP_ATTR(thunder)
    igProperty_GetRecord(player, KAMINARITEIKO)->value = thunder;
    int dark = beDataBase_GetRecordInt(RecomputeHelpers::shinka(self), species, RES_DARK);
    dark += igProperty_GetRecordIntList(player, UPCNT)->list->values[10];
    dark += igProperty_GetRecordIntList(player, UPDATA)->list->values[10];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &dark, RES_DARK, 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &dark, RES_DARK);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &dark, RES_DARK, 1);
    }
    CLAMP_ATTR(dark)
    igProperty_GetRecord(player, YAMITEIKO)->value = dark;

    {
        igObjectList *list = ((ObjectListProperty *)igProperty_GetRecordFolder(player, WAZALIST))->list;
        int oldCount = list->_count;
        for (int r = 0; r < oldCount; r++) RecomputeHelpers::release_ref(((igObject **)list->_data)[r]);
        int clearCount = list->_count;
        for (int c = 0; c < clearCount; c++) ((int *)list->_data)[c] = 0;
        list->_count = 0;

        for (int slot = 0; slot < 6; slot++) {
            int tech = beDataBase_GetRecordInt(RecomputeHelpers::shinka(self), species, g_techniqueFields[slot]);
            int skillNo = beDataBase_GetRecordInt(RecomputeHelpers::pctech(self), tech, (char *)SKILL);
            int skillVal = igProperty_GetRecordIntList(player, (char *)SKILL)->list->values[skillNo];
            if (beDataBase_GetRecordInt(RecomputeHelpers::shinka(self), species, g_techniqueLevelFields[slot]) <= level) {
                for (int rank = 4; rank >= 0; rank--) {
                    if (beDataBase_GetRecordInt(RecomputeHelpers::shinka(self), species, g_techniqueSkillFields[slot][rank]) <= skillVal) {
                        IntListRef waza((IntList *)beNDMWItemWaza_Create(RecomputeHelpers::select_allocator(igObject_GetAllocator(self))));
                        beNDMWItemWaza_Set((igObject *)waza.value, tech + rank, tech);
                        ObjectList_AppendRetained(list, (igObject *)waza.value);
                        break;
                    }
                }
            }
        }
    }
    igProperty_GetRecord(player, NEXTEXP)->value =
        level == 999 ? 0 : level * 200 + (level + 140) * (level * level);

    if (apply) {
        int delay, hitRate, critRate, paralysisRate, evadeRate, guardRate;
        int paralysisResist, poisonResist, bitRate, expRate;
        unsigned char found;
        int luckRate;
        delay = igProperty_GetRecordIntList(player, DOWNDATA)->list->values[6];
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &delay, DELAY, 0);
        if (delay > 70) delay = 70;
        igProperty_GetRecord(player, ATTACKDELAY)->value = delay;
        hitRate = 0;
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &hitRate, MEICHURITSU, 0);
        igProperty_GetRecord(player, MEICHURITSU)->value = hitRate;
        critRate = 0;
        critRate += igProperty_GetRecordIntList(player, UPDATA)->list->values[1];
        critRate -= igProperty_GetRecordIntList(player, DOWNDATA)->list->values[1];
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &critRate, CHIMEIRITSU, 0);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &critRate, CHIMEIRITSU);
        if (critRate <= 0) critRate = 1;
        igProperty_GetRecord(player, CHIMEIRITSU)->value = critRate;
        paralysisRate = 0;
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &paralysisRate, MAHIRITSU, 0);
        igProperty_GetRecord(player, MAHIRITSU)->value = paralysisRate;
        evadeRate = 0;
        evadeRate += igProperty_GetRecordIntList(player, UPDATA)->list->values[3];
        evadeRate -= igProperty_GetRecordIntList(player, DOWNDATA)->list->values[3];
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &evadeRate, CHOHATURITSU);
        if (evadeRate <= 0) evadeRate = 1;
        igProperty_GetRecord(player, KAIHIRITSU)->value = evadeRate;
        guardRate = 0;
        beNDMWGameRam_AddMainSlotBonus(self, player, &guardRate, BOUGYORITSU, 0);
        igProperty_GetRecord(player, BOUGYORITSU)->value = guardRate;
        paralysisResist = 0;
        paralysisResist += igProperty_GetRecordIntList(player, UPDATA)->list->values[2];
        paralysisResist -= igProperty_GetRecordIntList(player, DOWNDATA)->list->values[2];
        beNDMWGameRam_AddMainSlotBonus(self, player, &paralysisResist, MAHITEIKOU, 0);
        if (paralysisResist <= 0) paralysisResist = 1;
        igProperty_GetRecord(player, MAHITEIKOU)->value = paralysisResist;
        poisonResist = 0;
        beNDMWGameRam_AddMainSlotBonus(self, player, &poisonResist, DOKUTEIKOU, 0);
        igProperty_GetRecord(player, DOKUTEIKOU)->value = poisonResist;
        bitRate = 0;
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &bitRate, BITRITSU_2, 0);
        igProperty_GetRecord(player, BITRITSU_2)->value = bitRate;
        expRate = 0;
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &expRate, EXPRITSU, 0);
        igProperty_GetRecord(player, EXPRITSU)->value = expRate;
        luckRate = 0;
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &luckRate, LUCKRITSU, 0);
        igProperty_GetRecord(player, LUCKRITSU)->value = luckRate;

        { IntProperty *zokusei = igProperty_GetRecord(player, ATTACKZOKUSEI); zokusei->value = -1; }
        found = 0;
        int pocketCount = ((ObjectListProperty *)igProperty_GetRecordFolder(player, (char *)POWERPOCKET))->list->_count;
        for (int p = 0; p < pocketCount; p++) {
            beNDMWItemBase *pocketItem = ((beNDMWItemBase **)((ObjectListProperty *)igProperty_GetRecordFolder(player, (char *)POWERPOCKET))->list->_data)[p];
            if (pocketItem) {
                const char *zokuseiName = beNDMWItemBase_GetRecordString(pocketItem, self, ZOKUSEI);
                for (int element = 0; element < 4; element++) {
                    if (strcmp(zokuseiName, g_elementNames[element]) == 0) {
                        igProperty_GetRecord(player, ATTACKZOKUSEI)->value = element;
                        found = 1;
                        break;
                    }
                }
                if (found) break;
            }
        }
        {
            int hpDrain, mpDrain;
            hpDrain = 0;
            beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &hpDrain, HPDRAIN);
            igProperty_GetRecord(player, HPDRAIN)->value = hpDrain;
            mpDrain = 0;
            beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &mpDrain, MPDRAIN);
            igProperty_GetRecord(player, MPDRAIN)->value = mpDrain;
        }
        igProperty_GetRecord(player, CHOHATURITSU)->value =
            igProperty_GetRecord(player, KAIHIRITSU)->value;
    }

    if (apply) {
        int weaponRec, weaponSkill;
        beNDMWItemBase *firstSocket;
        igObjectList *sockets;
        igStringRefList *names;
        firstSocket = ((beNDMWItemBase **)((ObjectListProperty *)igProperty_GetRecordFolder(player, (char *)POWERSOCKET))->list->_data)[0];
        weaponRec = 0;
        weaponSkill = 0;
        if (firstSocket) {
            weaponRec = firstSocket->_recNo;
            weaponSkill = beNDMWItemBase_GetRecordInt(firstSocket, self, (char *)SKILL);
        }
        igProperty_GetRecord(player, WEAPONRECNO)->value = weaponRec;
        igProperty_GetRecord(player, WEAPONSKILLNO)->value = weaponSkill;

        sockets = ((ObjectListProperty *)igProperty_GetRecordFolder(player, (char *)POWERSOCKET))->list;
        names = igProperty_GetRecordStringList(player, POWERSOCKETNAME)->list;
        int nameCount = names->_count;
        for (int i = 0; i < nameCount; i++) {
            char **entry = &((char **)names->_data)[i];
            char *old, *fresh;
            fresh = StringPool_Intern(SharedStringPool::get(), 0);
            old = *entry;
            if (old) {
                int *header = (int *)(old - 8);
                if (--header[1] == 0) StringChunk_ReleaseHeader(header[0], header);
            }
            *entry = fresh;
        }
        names->_count = 0;
        int socketCount = sockets->_count;
        for (int i = 0; i < socketCount; i++) {
            beNDMWItemBase *item = ((beNDMWItemBase **)sockets->_data)[i];
            if (item) {
                const char *model = beNDMWItemBase_GetRecordString(item, self, MODEL);
                char *interned;
                if (!model) {
                    interned = 0;
                } else {
                    interned = StringPool_Intern(SharedStringPool::get(), model);
                }
                StringRef token(interned);
                StringList_AppendRetained((int)names, (const StringRef &)token);
            }
        }
    }
}

/* WAZALIST base number -> current database row; a miss leaves output unchanged. Declaration
 * order preserves the loop register allocation. */

void beNDMWGameRam_FindTechniqueRow(beNDMWGameRam *receiver, void *player,
                                   int base_no, int *output)
{
    igObjectList *list;
    int index;
    beNDMWItemWaza *item;
    int count;

    list = ((ObjectListProperty *)igProperty_GetRecordFolder(player, WAZALIST))->list;
    count = list->_count;
    index = 0;
    for (; index < count; ++index) {
        item = ((beNDMWItemWaza **)list->_data)[index];
        if (base_no == item->_baseNo) {
            *output = item->_recNo;
            return;
        }
    }
}

/* Collects the ids of the members of messenger group `group` that are within 30 units of `center`
 * (compared on GETMATRIX translations), skips `excluded`, and keeps those whose GETHP reply is
 * nonzero. The result list comes from the object's own allocator when the global byte flag is set,
 * otherwise from the allocator selected by kIGMemoryPoolHandleUser1[0]. */
NearbyListRef beNDMWGameRam_CollectNearbyNonzeroHp(beNDMWGameRam *self,const char *group,int excluded,const Vector3 *center) {
    int entry_index;
    int member_id;
    int append_index;
    IntList *list;
    int selfAllocator=igObject_GetAllocator(self);
    NearbyListRef result(igIntList_Create(g_useOwnerAllocator ? selfAllocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0])));
    beMessenger_SendGroup(self->_messenger,group,GETMATRIX);
    int count=beMessenger_GetIntCount(self->_messenger);
    Vector3 delta;
    Matrix44 matrix;
    for(entry_index=0;entry_index<count;++entry_index) {
        member_id=beMessenger_GetInt(self->_messenger,entry_index);
        if(member_id!=excluded) {
            beMessenger_GetMatrix(&matrix,self->_messenger,entry_index);
            igMatrix44f_GetTranslation(&matrix,&delta);
            delta.x-=center->x;
            delta.y-=center->y;
            delta.z-=center->z;
            if((delta.x*delta.x+delta.y*delta.y+delta.z*delta.z)<NEARBY_RADIUS_SQUARED) {
                beMessenger_PushArgContext(self->_messenger);
                beMessenger_SelectReceivers(self->_messenger,group,0,member_id);
                beMessenger_SetRunCheck(self->_messenger,1);
                beMessenger_DispatchSelected(self->_messenger,GETHP);
                if(beMessenger_GetInt(self->_messenger,0)) {
                    list=result.value;
                    append_index=list->getCount();
                    if(append_index<list->capacity) ++list->count;
                    else List_Resize(list,append_index+1,4);
                    list->data[append_index]=member_id;
                }
                beMessenger_PopArgContext(self->_messenger);
            }
        }
    }
    return result;
}

extern "C" {
#define MULT_HI(a,b) ((int)(((long long)(int)(a)*(long long)(int)(b))>>32))

typedef struct DW4CountedListView { char _pad0[8]; int count; } DW4CountedListView; /* matching construct: class of the ObjectRef_Get_00406df0 result not determined, only the +8 count is read */
typedef struct DW4ByteFlag8 { char _pad0[8]; unsigned char value; } DW4ByteFlag8; /* matching construct: class of the DataList_GetWordAt_00406dd0 result not determined; byte flag at +8 */
const char *beMessenger_GetString(int,int);
unsigned char beMessenger_GetBool(int,int);
int beMessenger_GetBoolCount(int);
int beMessenger_GetObjectCount(int);
int beMessenger_GetStringCount(int);
int beMessenger_ResolveEnumValue(int,void *,const char *);
void beMessenger_ClearBool(int);
void beMessenger_ClearInt(int);
void beMessenger_AppendBool(int,unsigned char);
void beMessenger_AppendObject(...);
void beMessenger_AppendString(...);
void beMessenger_AppendMatrix(...);
void beMessenger_AppendVec3(...);
void beMessenger_SelectGroup(...);
void ObjectRef_Release_003e9110(...);
void *ObjectRef_Destruct_003e9010(...);
void ObjectList_SetAtRetained_003e9160(...);
void Vec3f_Copy(...);
int ObjectList_GetAt_003e9260(...);
int DataList_GetData_003e9090(...);
int Memory_SelectAllocator_003e9370(...);
void igMatrix44f_Copy(...);
void igMatrix44f_SetIdentity(...);
void *FightCom_GetMetaEnum(...);
void *GameRamMessage_GetMetaEnum(...);
extern const short g_skillGainTable[4][21][3];
extern const short g_skillGainThresholds[21];
extern const char *const g_resistanceFields[5];
extern const char *const g_elementResistanceFields[4];
extern const char *const g_weaponGrowFields[6];
int FUN_0033e9c0(...);
void *beNDMWItemAbilityChip_Create(...);
void *beNDMWItemYellowArmor_Create(...);
void *beNDMWItemBlueArmor_Create(...);
int DataList_FindProperty_003e9280(...);
int ObjectRef_Get_003e92a0(...);
AllocatorValue AllocatorValue_Make_003e9360(...);
int ObjectRef_Get_003e93b0(...);
int beNDMWMdlPEBaseInfoWork_IsPoisoned(...);
int beNDMWMdlPEBaseInfoWork_CurePoison(...);
int beNDMWItemBase_IndexOfRecNo(...);
int beNDMWItemBlueArmor_Set(...);
int beNDMWItemYellowArmor_Set(...);
int beNDMWItemAbilityChip_Set(...);
int beMessenger_EnqueueSelected(...);
int beMessenger_PrepareDelayedSelection(...);
AllocatorValue igMetaEnum_GetValueByName(...);
extern int DAT_004cf538[4];
extern int DAT_004cf558[4];
extern int DAT_004cf5d8[4];
extern int DAT_004cf5e0[4];
extern int DAT_004cf5e8[4];
extern int DAT_004cf5f0[4];
extern int DAT_004cf600[4];
extern int DAT_004cf620[4];
extern Vector3 g_vec3Zero[4];
extern char BKCHIPDATA[];
extern char BKCHIPNAME[];
extern char BIT_3[];
extern char fire[];
extern char ice[];
extern char thunder[];
extern char dark[];
extern char RES_POISON[];
extern char GETMATRIX[];
extern char GETHP[];
extern char PLAYER_2[];
extern char x_250healhit00[];
extern char SQ_HEALEFONLY[];
extern int SETEFFECT[4];
extern char SET[];
extern char ADD[];
extern char GETMHP[];
extern char GETMP[];
extern char GETMMP[];
extern char CLR_2[];
extern char IS[];
extern char ISMAX[];
extern char ISEQUIP[];
extern char GET[];
extern char DEVICE_2[];
extern char weapon_2[];
extern char armor1_2[];
extern char armor2_2[];
extern char abChip_2[];
extern char DISK_2[];
extern char poison[];
extern char MODELCTRL_5[];
extern char i_getitempnl01[];
extern char SQ_TECUP[];
extern char SQ_LVUP[];
extern char lvnm[];
extern char RES_STUN[];
extern char TIME[];
extern char MHIRITSU[];
extern char TYPE[];
extern char SEQUENCE[];
extern int ONE_2[4];
extern char KOUKA[];
extern char doku[];
extern char KOUKARANK[];
extern char KOUKATIME[];
extern char DAMAGE[];
extern char GEDOKU[];
extern char sleep[];
extern char ashidome[];
extern char freeze[];
extern char powerdown[];
extern char GETPEBASEWORK_3[];
extern char x_250curehit00[];
extern char SQ_CUREEFONLY[];
extern char PLAYER2[];
extern int RAISE[4];
extern int SETSPEEDUP[4];
extern char x_250uphit00[];
extern char SQ_UPEFONLY[];
extern int SETPOWERUP[4];
extern char FIRE[];
extern char ICE[];
extern char THUNDER[];
extern char DARK[];
extern int SETREFRACT[4];
extern char GETDATABASE_5[];
extern char enemy[];
extern char DATABASE_5[];
extern char GETDATABASE_6[];
extern char eneatk[];
extern char DATABASE_6[];
extern int g_propertyNameField[4];
extern unsigned char GPR_005549f0;
extern unsigned char GPR_005549f4;
int beNDMWGameRam_OnMessage(beNDMWGameRam *self, int ram, void *message);
}
/* matching construct: dummy-virtual class so vX() compiles to the retail vtable call */ class DW4VC_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
extern "C" int FUN_00229fb0(void *, const StringRef &);
/* matching construct: inline helper reproduces the retail arithmetic shape */ struct DW4Curve { static int g(int d, int x) { return d * 0xC8 + (x + 0x8B) * (d * d); } static int f(int x) { int d = x - 1; return d * 0xC8 + (x + 0x8B) * (d * d); } };
/* matching construct: RAII copied-reference local reproduces the retail unwind table */ class RecoveryCopiedRef { public: void *value; RecoveryCopiedRef(const AllocatorValue &source); ~RecoveryCopiedRef(); };
extern "C" int *ObjectRef_Assign_003e92b0(void *, const RecoveryCopiedRef &);
/* matching construct: out-of-line helper reproduces the retail call shape */ struct DW4Fresh { static int *Assign(void *obj, int alloc) { RecoveryCopiedRef c(AllocatorValue_Make_003e9360(Memory_SelectAllocator_003e9370(kIGMemoryPoolHandleUser1, alloc))); return ObjectRef_Assign_003e92b0(obj, c); } };
/* matching construct: out-of-line helper that reproduces the retail call shape of the BKCHIPNAME string-list store */
struct DW4StrListOps { static void SetAt(igStringRefList *list, int idx, const StringRef &v) { if (list->_count != 0 && idx >= 0 && idx < list->_count) FUN_00229fb0((void *)((char *)DataList_GetData_00406da0((igDataList *)list) + idx * 4), v); } };
/* matching construct: RAII list local reproduces the retail unwind table */ class RecoveryList { public:
 struct Header { int word0; int word1; int count; int capacity; };
 static void append(void *list, int value) {
  Header *h = (Header *)list;
  const Header *view = h;
  int index = h->count;
  if (index < h->capacity) {
   h->count = view->count + 1;
  } else {
   List_Resize(list, index + 1, 4);
  }
  ((int *)DataList_GetData_003e9090(list))[index] = value;
 }
};
int beNDMWGameRam_OnMessage(beNDMWGameRam *self, int ram, void *message) {
    int e2p_diff_705;
    int temp_ret_634;
    int temp_ret_657;
    unsigned char var_s5_7;
    int temp_s3_6;
    int temp_ret_635;
    int temp_ret_636;
    int temp_s1_9;
    void *temp_v0_104;
    int temp_s0_20;
    int temp_s0_21;
    int temp_ret_652;
    int temp_ret_194;
    int temp_s1;
    int temp_ret_193;
    int temp_s0_3;
    int temp_ret_195;
    int var_s5_2;
    int temp_ret_209;
    beNDMWMdlPEBaseInfoWork *temp_v0_33;
    int temp_s3;
    void *temp_v0_34;
    int var_s2;
    char *temp_v0_19;
    char *temp_v0_10;

    void *temp_v0_47;
    int sp400;
    int sp3FC;
    int sp3F8;
    int sp3F4;
    int sp3F0;

    int sp3E4;
    Vector3 sp3D8;
    Vector3 sp3C8;
    Vector3 sp3B8;
    Vector3 sp3A8;
    Vector3 sp398;
    Vector3 sp388;
    Vector3 sp378;
    Vector3 sp368;
    Vector3 sp358;
    Vector3 sp348;
    Vector3 sp338;
    Vector3 sp328;
    Vector3 sp318;
    Vector3 sp308;
    Vector3 sp2F8;
    Matrix44 sp2B0;
    Matrix44 sp270;
    Matrix44 sp230;
    Matrix44 sp1F0;
    Matrix44 sp1B0;
    Matrix44 sp170;
    Matrix44 sp130;
    int sp12C;
    int sp128;
    int sp124;
    int sp120;
    unsigned char sp110;
    int temp_s5_4;
    int var_s2_12;
    int var_s3_5;
    int temp_ret_1260;
    int temp_ret_1000;
    int temp_ret_1067;
    int temp_ret_1102;
    int temp_ret_1103;
    int temp_ret_1124;
    int temp_ret_1136;
    int temp_ret_1139;
    int temp_ret_1140;
    int temp_ret_1191;
    int temp_ret_1192;
    int temp_ret_1234;
    int temp_ret_1235;
    int temp_ret_1273;
    int temp_ret_1274;
    int temp_ret_1275;
    int temp_ret_1287;
    int temp_ret_1288;
    int temp_ret_133;
    int temp_ret_135;
    int temp_ret_136;
    int temp_ret_139;
    int temp_ret_141;
    int temp_ret_142;
    int temp_ret_145;
    int temp_ret_147;
    int temp_ret_148;
    int temp_ret_151;
    int temp_ret_153;
    int temp_ret_154;
    int temp_ret_192;
    int temp_ret_358;
    int temp_ret_359;
    int temp_ret_386;
    int temp_ret_387;
    int temp_ret_390;
    int temp_ret_391;
    int temp_ret_392;
    int temp_ret_393;
    int temp_ret_394;
    int temp_ret_395;
    int temp_ret_396;
    int temp_ret_397;
    int temp_ret_398;
    int temp_ret_399;
    int temp_ret_43;
    int temp_ret_448;
    int temp_ret_565;
    int temp_ret_633;
    int temp_ret_66;
    int temp_ret_67;
    int temp_ret_77;
    int temp_ret_784;
    int temp_ret_785;
    int temp_ret_787;
    int temp_ret_78;
    int temp_ret_861;
    beDataObjBool *temp_ret_366;
    beDataObjBool *temp_ret_48;
    short *var_v1_5;
    int temp_s1_3;
    int *temp_ret_1012;
    int *temp_ret_1018;
    int *temp_ret_1023;
    int *temp_ret_1030;
    int *temp_ret_1040;
    int *temp_ret_1045;
    int *temp_ret_1057;
    int *temp_ret_1062;
    int *temp_ret_1075;
    int *temp_ret_1089;
    int *temp_ret_1106;
    int *temp_ret_1147;
    int *temp_ret_1153;
    int *temp_ret_1161;
    int *temp_ret_1173;
    int *temp_ret_1178;
    int *temp_ret_1183;
    int *temp_ret_1196;
    int *temp_ret_1201;
    int *temp_ret_1209;
    int *temp_ret_1214;
    int *temp_ret_1219;
    int *temp_ret_1238;
    int *temp_ret_1243;
    int *temp_ret_1248;
    int *temp_ret_1253;
    int *temp_ret_1258;
    int *temp_ret_207;
    int *temp_ret_223;
    int *temp_ret_233;
    int *temp_ret_238;
    int *temp_ret_260;
    int *temp_ret_266;
    int *temp_ret_272;
    int *temp_ret_277;
    int *temp_ret_285;
    int *temp_ret_291;
    int *temp_ret_301;
    int *temp_ret_317;
    int *temp_ret_338;
    int *temp_ret_347;
    int *temp_ret_371;
    int *temp_ret_410;
    int *temp_ret_425;
    int *temp_ret_433;
    int *temp_ret_440;
    int *temp_ret_445;
    int *temp_ret_456;
    int *temp_ret_464;
    int *temp_ret_471;
    int *temp_ret_481;
    int *temp_ret_489;
    int *temp_ret_496;
    int *temp_ret_510;
    int *temp_ret_518;
    int *temp_ret_525;
    int *temp_ret_531;
    int *temp_ret_539;
    int *temp_ret_544;
    int *temp_ret_550;
    int *temp_ret_556;
    int *temp_ret_562;
    int *temp_ret_577;
    int *temp_ret_585;
    int *temp_ret_592;
    int *temp_ret_598;
    int *temp_ret_606;
    int *temp_ret_611;
    int *temp_ret_617;
    int *temp_ret_625;
    int *temp_ret_630;
    int *temp_ret_641;
    int *temp_ret_650;
    int *temp_ret_655;
    int *temp_ret_667;
    int *temp_ret_676;
    int *temp_ret_681;
    int *temp_ret_686;
    int *temp_ret_703;
    int *temp_ret_708;
    int *temp_ret_714;
    int *temp_ret_719;
    int *temp_ret_725;
    int *temp_ret_738;
    int *temp_ret_744;
    int *temp_ret_750;
    int *temp_ret_772;
    int *temp_ret_777;
    int *temp_ret_786;
    int *temp_ret_803;
    int *temp_ret_811;
    int *temp_ret_816;
    int *temp_ret_832;
    int *temp_ret_838;
    int *temp_ret_845;
    int *temp_ret_852;
    int *temp_ret_858;
    int *temp_ret_869;
    int *temp_ret_875;
    int *temp_ret_880;
    int *temp_ret_887;
    int *temp_ret_897;
    int *temp_ret_903;
    int *temp_ret_908;
    int *temp_ret_913;
    int *temp_ret_920;
    int *temp_ret_925;
    int *temp_ret_930;
    int *temp_ret_945;
    int *temp_ret_951;
    int *temp_ret_956;
    int *temp_ret_963;
    int *temp_ret_973;
    int *temp_ret_978;
    int *temp_ret_990;
    int *temp_ret_995;
    int temp_a0;
    int temp_a0_10;
    int temp_a0_11;
    int temp_a0_2;
    int temp_a0_3;
    int temp_a0_4;
    int temp_a0_5;
    int temp_a1_2;
    int temp_a1_3;
    int temp_a2_10;
    int temp_a2_11;
    int temp_a2_12;
    int temp_a2_13;
    int temp_a2_14;
    int temp_a2_15;
    int temp_a2_16;
    int temp_a2_17;
    int temp_a2_18;
    int temp_a2_19;
    int temp_a2_4;
    int temp_a2_5;
    int temp_a2_6;
    int temp_a2_7;
    int temp_a2_8;
    int temp_a2_9;
    int temp_a4_4;
    int temp_lo;
    int temp_ret_1004;
    int temp_ret_1005;
    int temp_ret_1006;
    int temp_ret_1008;
    int temp_ret_1009;
    int temp_ret_1015;
    int temp_ret_101;
    int temp_ret_1025;
    int temp_ret_1026;
    int temp_ret_1032;
    int temp_ret_1033;
    int temp_ret_1034;
    int temp_ret_1036;
    int temp_ret_103;
    int temp_ret_1042;
    int temp_ret_1047;
    int temp_ret_1048;
    int temp_ret_1049;
    int temp_ret_104;
    int temp_ret_1050;
    int temp_ret_1051;
    int temp_ret_1053;
    int temp_ret_1059;
    int temp_ret_105;
    int temp_ret_1064;
    int temp_ret_1065;
    int temp_ret_1066;
    int temp_ret_1068;
    int temp_ret_1069;
    int temp_ret_106;
    int temp_ret_1070;
    int temp_ret_1072;
    int temp_ret_1077;
    int temp_ret_1078;
    int temp_ret_107;
    int temp_ret_1080;
    int temp_ret_1081;
    int temp_ret_1083;
    int temp_ret_1084;
    int temp_ret_1086;
    int temp_ret_1091;
    int temp_ret_1092;
    int temp_ret_1093;
    int temp_ret_1094;
    int temp_ret_1096;
    int temp_ret_1097;
    int temp_ret_1099;
    int temp_ret_1100;
    int temp_ret_1108;
    int temp_ret_1109;
    int temp_ret_1111;
    int temp_ret_1112;
    int temp_ret_1114;
    int temp_ret_1115;
    int temp_ret_1117;
    int temp_ret_1118;
    int temp_ret_111;
    int temp_ret_1122;
    int temp_ret_1125;
    int temp_ret_1127;
    int temp_ret_1129;
    int temp_ret_112;
    int temp_ret_1130;
    int temp_ret_1134;
    int temp_ret_1137;
    int temp_ret_113;
    int temp_ret_1141;
    int temp_ret_1143;
    int temp_ret_1149;
    int temp_ret_114;
    int temp_ret_1150;
    int temp_ret_1155;
    int temp_ret_1156;
    int temp_ret_1158;
    int temp_ret_115;
    int temp_ret_1163;
    int temp_ret_1164;
    int temp_ret_1167;
    int temp_ret_1168;
    int temp_ret_116;
    int temp_ret_1170;
    int temp_ret_1175;
    int temp_ret_117;
    int temp_ret_1180;
    int temp_ret_1185;
    int temp_ret_1186;
    int temp_ret_1189;
    int temp_ret_118;
    int temp_ret_1193;
    int temp_ret_1198;
    int temp_ret_119;
    int temp_ret_11;
    int temp_ret_1203;
    int temp_ret_1204;
    int temp_ret_1206;
    int temp_ret_120;
    int temp_ret_1211;
    int temp_ret_1216;
    int temp_ret_121;
    int temp_ret_1221;
    int temp_ret_1222;
    int temp_ret_1225;
    int temp_ret_1226;
    int temp_ret_1228;
    int temp_ret_1229;
    int temp_ret_122;
    int temp_ret_1232;
    int temp_ret_1240;
    int temp_ret_1245;
    int temp_ret_124;
    int temp_ret_1250;
    int temp_ret_1255;
    int temp_ret_125;
    int temp_ret_1261;
    int temp_ret_1264;
    int temp_ret_1265;
    int temp_ret_1267;
    int temp_ret_1268;
    int temp_ret_1271;
    int temp_ret_127;
    int temp_ret_1280;
    int temp_ret_1284;
    int temp_ret_1286;
    int temp_ret_1289;
    int temp_ret_128;
    int temp_ret_1290;
    int temp_ret_1292;
    int temp_ret_1293;
    int temp_ret_1294;
    int temp_ret_1295;
    int temp_ret_1296;
    int temp_ret_1298;
    int temp_ret_1299;
    int temp_ret_129;
    int temp_ret_130;
    int temp_ret_131;
    int temp_ret_132;
    int temp_ret_137;
    int temp_ret_138;
    int temp_ret_13;
    int temp_ret_143;
    int temp_ret_144;
    int temp_ret_149;
    int temp_ret_150;
    int temp_ret_155;
    int temp_ret_157;
    int temp_ret_159;
    int temp_ret_15;
    int temp_ret_160;
    int temp_ret_162;
    int temp_ret_163;
    int temp_ret_164;
    int temp_ret_165;
    int temp_ret_166;
    int temp_ret_167;
    int temp_ret_168;
    int temp_ret_169;
    int temp_ret_16;
    int temp_ret_170;
    int temp_ret_172;
    int temp_ret_179;
    int temp_ret_17;
    int temp_ret_181;
    int temp_ret_182;
    int temp_ret_183;
    int temp_ret_184;
    int temp_ret_185;
    int temp_ret_198;
    int temp_ret_199;
    int temp_ret_200;
    int temp_ret_201;
    int temp_ret_203;
    int temp_ret_204;
    int temp_ret_20;
    int temp_ret_212;
    int temp_ret_214;
    int temp_ret_215;
    int temp_ret_216;
    int temp_ret_218;
    int temp_ret_219;
    int temp_ret_226;
    int temp_ret_227;
    int temp_ret_228;
    int temp_ret_229;
    int temp_ret_22;
    int temp_ret_230;
    int temp_ret_235;
    int temp_ret_240;
    int temp_ret_243;
    int temp_ret_244;
    int temp_ret_245;

    int temp_ret_249;
    int temp_ret_24;
    int temp_ret_250;
    int temp_ret_251;
    int temp_ret_252;
    int temp_ret_254;
    int temp_ret_257;
    int temp_ret_262;
    int temp_ret_263;
    int temp_ret_268;
    int temp_ret_26;
    int temp_ret_274;
    int temp_ret_279;
    int temp_ret_27;
    int temp_ret_280;
    int temp_ret_282;
    int temp_ret_287;
    int temp_ret_288;
    int temp_ret_294;
    int temp_ret_295;
    int temp_ret_296;
    int temp_ret_297;
    int temp_ret_298;
    int temp_ret_29;
    int temp_ret_303;
    int temp_ret_306;
    int temp_ret_307;
    int temp_ret_308;
    int temp_ret_310;
    int temp_ret_311;
    int temp_ret_313;
    int temp_ret_314;
    int temp_ret_31;
    int temp_ret_320;
    int temp_ret_321;
    int temp_ret_322;
    int temp_ret_323;
    int temp_ret_324;
    int temp_ret_325;
    int temp_ret_326;
    int temp_ret_327;

    int temp_ret_330;
    int temp_ret_331;
    int temp_ret_332;
    int temp_ret_333;
    int temp_ret_335;
    int temp_ret_33;
    int temp_ret_340;
    int temp_ret_341;
    int temp_ret_343;
    int temp_ret_344;
    int temp_ret_349;
    int temp_ret_351;
    int temp_ret_353;
    int temp_ret_356;
    int temp_ret_35;
    int temp_ret_360;
    int temp_ret_361;
    int temp_ret_363;
    int temp_ret_365;
    int temp_ret_367;
    int temp_ret_368;
    int temp_ret_373;
    int temp_ret_374;
    int temp_ret_375;
    int temp_ret_376;
    int temp_ret_377;
    int temp_ret_378;
    int temp_ret_381;
    int temp_ret_382;
    int temp_ret_383;
    int temp_ret_384;
    int temp_ret_388;
    int temp_ret_389;
    int temp_ret_38;
    int temp_ret_3;
    int temp_ret_400;
    int temp_ret_401;
    int temp_ret_402;
    int temp_ret_403;
    int temp_ret_404;
    int temp_ret_406;
    int temp_ret_407;
    int temp_ret_412;
    int temp_ret_417;
    int temp_ret_418;
    int temp_ret_419;
    int temp_ret_421;
    int temp_ret_422;
    int temp_ret_427;
    int temp_ret_428;
    int temp_ret_430;
    int temp_ret_435;
    int temp_ret_437;
    int temp_ret_442;
    int temp_ret_447;
    int temp_ret_449;
    int temp_ret_44;
    int temp_ret_450;
    int temp_ret_451;
    int temp_ret_453;
    int temp_ret_458;
    int temp_ret_459;
    int temp_ret_461;
    int temp_ret_466;
    int temp_ret_468;
    int temp_ret_473;
    int temp_ret_474;
    int temp_ret_475;
    int temp_ret_476;
    int temp_ret_478;
    int temp_ret_47;
    int temp_ret_483;
    int temp_ret_484;
    int temp_ret_486;
    int temp_ret_491;
    int temp_ret_493;
    int temp_ret_498;
    int temp_ret_49;
    int temp_ret_502;
    int temp_ret_503;
    int temp_ret_504;
    int temp_ret_506;
    int temp_ret_507;
    int temp_ret_50;
    int temp_ret_512;
    int temp_ret_513;
    int temp_ret_515;
    int temp_ret_51;
    int temp_ret_520;
    int temp_ret_522;
    int temp_ret_527;
    int temp_ret_528;
    int temp_ret_52;
    int temp_ret_533;
    int temp_ret_534;
    int temp_ret_536;
    int temp_ret_53;
    int temp_ret_541;
    int temp_ret_546;
    int temp_ret_547;
    int temp_ret_54;
    int temp_ret_552;
    int temp_ret_553;
    int temp_ret_558;
    int temp_ret_559;
    int temp_ret_55;
    int temp_ret_564;
    int temp_ret_569;
    int temp_ret_56;
    int temp_ret_570;
    int temp_ret_571;
    int temp_ret_573;
    int temp_ret_574;
    int temp_ret_579;
    int temp_ret_57;
    int temp_ret_580;
    int temp_ret_582;
    int temp_ret_587;
    int temp_ret_589;
    int temp_ret_58;
    int temp_ret_594;
    int temp_ret_595;
    int temp_ret_59;
    int temp_ret_5;
    int temp_ret_600;
    int temp_ret_601;
    int temp_ret_603;
    int temp_ret_608;
    int temp_ret_60;
    int temp_ret_613;
    int temp_ret_614;
    int temp_ret_619;
    int temp_ret_61;
    int temp_ret_620;
    int temp_ret_622;
    int temp_ret_627;
    int temp_ret_632;
    int temp_ret_638;
    int temp_ret_63;
    int temp_ret_643;
    int temp_ret_644;
    int temp_ret_646;
    int temp_ret_647;
    int temp_ret_64;
    int temp_ret_659;
    int temp_ret_660;
    int temp_ret_661;
    int temp_ret_664;
    int temp_ret_669;
    int temp_ret_670;
    int temp_ret_673;
    int temp_ret_678;
    int temp_ret_683;
    int temp_ret_689;
    int temp_ret_68;
    int temp_ret_690;
    int temp_ret_691;
    int temp_ret_692;
    int temp_ret_693;
    int temp_ret_694;
    int temp_ret_695;
    int temp_ret_696;
    int temp_ret_69;
    int temp_ret_700;
    int temp_ret_705;
    int temp_ret_70;
    int temp_ret_710;
    int temp_ret_716;
    int temp_ret_71;
    int temp_ret_721;
    int temp_ret_722;
    int temp_ret_728;
    int temp_ret_729;
    int temp_ret_730;
    int temp_ret_731;
    int temp_ret_732;
    int temp_ret_733;
    int temp_ret_734;
    int temp_ret_735;
    int temp_ret_740;
    int temp_ret_746;
    int temp_ret_747;
    int temp_ret_74;
    int temp_ret_753;
    int temp_ret_754;
    int temp_ret_755;
    int temp_ret_756;
    int temp_ret_757;
    int temp_ret_758;
    int temp_ret_759;
    int temp_ret_75;
    int temp_ret_760;
    int temp_ret_763;
    int temp_ret_764;
    int temp_ret_765;
    int temp_ret_766;
    int temp_ret_769;
    int temp_ret_779;
    int temp_ret_780;
    int temp_ret_781;
    int temp_ret_782;
    int temp_ret_783;
    int temp_ret_788;
    int temp_ret_789;
    int temp_ret_790;
    int temp_ret_793;

    int temp_ret_795;
    int temp_ret_796;
    int temp_ret_797;
    int temp_ret_7;
    int temp_ret_800;
    int temp_ret_805;
    int temp_ret_808;
    int temp_ret_80;
    int temp_ret_813;
    int temp_ret_818;
    int temp_ret_819;
    int temp_ret_820;
    int temp_ret_825;
    int temp_ret_826;
    int temp_ret_828;
    int temp_ret_829;
    int temp_ret_82;
    int temp_ret_835;
    int temp_ret_83;
    int temp_ret_841;
    int temp_ret_847;
    int temp_ret_848;
    int temp_ret_849;
    int temp_ret_854;
    int temp_ret_855;
    int temp_ret_85;
    int temp_ret_860;
    int temp_ret_862;
    int temp_ret_863;
    int temp_ret_864;
    int temp_ret_86;
    int temp_ret_872;
    int temp_ret_877;
    int temp_ret_87;
    int temp_ret_882;
    int temp_ret_883;
    int temp_ret_889;
    int temp_ret_88;
    int temp_ret_890;
    int temp_ret_891;
    int temp_ret_892;
    int temp_ret_894;
    int temp_ret_89;
    int temp_ret_900;
    int temp_s3_11;
    int var_s2_11;
    int temp_ret_905;
    int temp_ret_90;
    int temp_ret_910;
    int temp_ret_915;
    int temp_ret_916;
    int temp_ret_922;
    int temp_ret_927;
    int temp_ret_92;
    int temp_ret_932;
    int temp_ret_933;
    int temp_ret_937;
    int temp_ret_938;
    int temp_ret_939;
    int temp_ret_941;
    int temp_ret_942;
    int temp_ret_948;
    int temp_ret_94;
    int temp_ret_958;
    int temp_ret_959;
    int temp_ret_95;
    int temp_ret_965;
    int temp_ret_966;
    int temp_ret_967;
    int temp_ret_969;
    int temp_ret_96;
    int temp_ret_975;
    int temp_ret_97;
    int temp_ret_980;
    int temp_ret_981;
    int temp_ret_982;
    int temp_ret_983;
    int temp_ret_984;
    int temp_ret_986;
    int temp_ret_98;
    int temp_ret_992;
    int temp_ret_997;
    int temp_ret_998;
    int temp_ret_999;
    int temp_ret_99;
    int temp_ret_9;
    int temp_s0_10;
    int temp_s0_11;
    int temp_s0_12;
    int temp_s0_13;
    int temp_s0_14;
    int temp_s0_15;
    unsigned int temp_s1_6;
    int temp_s0_16;
    int temp_s0_17;
    int temp_s0_18;
    int temp_s0_19;
    int temp_s0_22;
    int temp_s0_23;
    int temp_s0_25;
    int temp_s0_26;
    int temp_s0_28;
    int temp_s0_31;
    int temp_s0_4;
    int var_s2_2;
    int var_s1;
    int temp_s0_5;
    int temp_s0_6;
    int temp_s0_7;
    int temp_s0_8;
    int temp_s0_9;
    void *temp_v0_68;
    int temp_s1_10;
    int temp_s1_11;
    int temp_s1_12;
    int temp_s1_13;
    int temp_s1_14;
    int temp_s1_15;
    int temp_s1_16;
    int temp_s1_2;
    int temp_s1_4;
    int temp_s1_5;
    int temp_s2;
    int temp_s2_11;
    int temp_s2_3;
    int temp_s2_4;
    int temp_s2_5;
    int temp_s2_7;
    int temp_s2_9;
    int temp_s3_14;
    int temp_s3_3;
    int temp_s3_4;
    int temp_s3_5;
    int temp_s3_7;
    int temp_s3_8;
    int temp_s3_9;
    int temp_s5;
    int temp_s5_2;
    int temp_s5_3;
    int temp_s5_5;
    int temp_s5_6;
    int temp_s6;
    beNDMWMdlPEBaseInfoWork *temp_v0_132;
    int temp_s6_2;
    int temp_s6_4;
    int temp_s6_5;
    int temp_s8;
    int temp_v0_101;
    int temp_v0_108;
    int temp_v0_111;
    int temp_v0_114;
    int temp_v0_116;
    int temp_v0_118;
    int temp_v0_11;
    int temp_v0_129;
    int temp_v0_131;
    int temp_v0_134;
    int temp_v0_136;
    int temp_v0_141;
    int temp_v0_143;
    int temp_v0_147;
    int temp_v0_148;
    int temp_v0_156;
    int temp_v0_157;
    int temp_v0_164;
    int temp_v0_166;
    int temp_v0_167;
    int temp_v0_171;
    int temp_v0_177;
    int temp_v0_189;
    int temp_v0_20;
    int temp_v0_21;
    int temp_v0_22;
    int temp_v0_23;
    int temp_v0_29;
    int temp_v0_2;
    int temp_v0_30;
    int temp_v0_40;
    int temp_v0_44;
    int temp_v0_45;
    int temp_v0_48;
    int temp_v0_51;
    int temp_v0_59;
    int temp_v0_60;
    int temp_v0_63;
    int temp_v0_69;
    int temp_v0_70;
    int temp_v0_71;
    int temp_v0_72;
    int temp_v0_73;
    int temp_v0_74;
    int temp_v0_77;
    int temp_v0_79;
    int temp_v0_7;
    int temp_v0_83;
    int temp_v0_87;
    int temp_v0_8;
    int temp_v0_91;
    int temp_v0_92;
    int temp_v0_94;
    int temp_v0_98;
    int temp_v0_99;
    int temp_v1;
    int temp_v1_10;
    int temp_v1_11;
    int temp_v1_12;
    int temp_v1_13;
    int temp_v1_14;
    int temp_v1_2;
    int temp_v1_3;
    int temp_v1_6;
    int temp_v1_7;
    int temp_v1_9;
    int var_a0;
    int var_a1_4;
    int var_a2;
    int var_a2_2;
    int var_a3;
    int var_s0;
    int var_s0_10;
    int var_s0_11;
    int var_s0_12;
    int var_s0_13;
    int var_s0_14;
    int var_s0_15;
    int var_s0_16;
    int var_s0_17;
    int var_s0_18;
    int var_s0_19;
    int var_s0_20;
    int var_s0_21;
    int var_s1_16;
    bool var_s0_22;
    int var_s0_23;
    int var_s0_24;
    int var_s0_25;
    int var_s0_26;
    int var_s0_2;
    int var_s0_3;
    int var_s0_4;
    int var_s0_5;
    int var_s0_6;
    int var_s0_7;
    int var_s0_8;
    int var_s0_9;
    int var_s1_10;
    int var_s1_11;
    int var_s1_13;
    int var_s1_14;
    int var_s1_15;
    int var_s1_18;
    int var_s1_19;
    int var_s1_20;
    int temp_ret_953;
    int var_s1_21;
    int var_s1_22;
    int var_s1_23;
    int var_s1_24;
    int var_s1_25;
    int var_s1_26;
    int var_s1_27;
    int var_s1_28;
    int var_s1_2;
    int var_s1_3;
    int temp_ret_1020;
    int var_s2_3;
    int var_s1_4;
    int var_s2_4;
    int var_s1_5;
    int var_s2_5;
    int var_s1_6;
    int var_s2_6;
    int var_s1_7;
    int var_s1_8;
    int var_s1_9;
    int var_s2_10;
    int var_s2_7;
    int var_s2_9;
    int var_s3;
    int var_s3_2;
    int var_s3_3;
    int var_s3_4;
    int var_s2_8;
    int var_s3_6;
    int var_s3_7;
    int temp_s4;
    int var_s3_8;
    int var_s5;
    int var_s5_10;
    int var_s5_3;
    int var_s5_4;
    int var_s5_5;
    int var_s5_6;
    int var_s5_8;
    int var_s5_9;
    int var_s7;
    int var_s7_2;
    int var_s8;
    int var_s8_2;
    int var_v0_13;
    int var_v0_14;
    int var_v0_15;
    int var_v0_16;
    int var_v0_17;
    int var_v0_18;
    int var_v0_2;
    int var_v0_3;
    int var_v0_5;
    int var_v0_6;
    int var_v0_7;
    int var_v0_8;
    int var_v0_9;
    int var_v1_10;
    int var_v1_11;
    int var_v1_12;
    int var_v1_13;
    int var_v1_14;
    int var_v1_15;
    int var_v1_16;
    int var_v1_18;
    int var_v1_7;
    int var_v1_8;
    int var_v1_9;
    const char *temp_ret;
    char *temp_ret_1001;
    char *temp_ret_1003;
    const char *temp_ret_100;
    char *temp_ret_1014;
    const char *temp_ret_108;
    const char *temp_ret_109;
    const char *temp_ret_110;
    const char *temp_ret_1095;
    const char *temp_ret_1101;
    const char *temp_ret_1119;
    const char *temp_ret_1126;
    const char *temp_ret_1131;
    const char *temp_ret_1138;
    const char *temp_ret_1142;
    const char *temp_ret_1165;
    const char *temp_ret_1187;
    const char *temp_ret_1190;
    const char *temp_ret_1223;
    const char *temp_ret_1230;
    const char *temp_ret_1233;
    const char *temp_ret_1262;
    const char *temp_ret_1269;
    const char *temp_ret_1272;
    const char *temp_ret_1281;
    char *temp_ret_1283;
    const char *temp_ret_187;
    char *temp_ret_189;
    const char *temp_ret_191;
    const char *temp_ret_21;
    char *temp_ret_225;
    char *temp_ret_293;
    char *temp_ret_319;
    const char *temp_ret_34;
    char *temp_ret_357;
    char *temp_ret_385;
    const char *temp_ret_39;
    char *temp_ret_414;
    char *temp_ret_416;
    char *temp_ret_41;
    char *temp_ret_499;
    char *temp_ret_501;
    char *temp_ret_566;
    char *temp_ret_568;
    const char *temp_ret_65;
    char *temp_ret_688;
    char *temp_ret_727;
    char *temp_ret_752;
    const char *temp_ret_76;
    const char *temp_ret_79;
    const char *temp_ret_81;
    char *temp_ret_822;
    char *temp_ret_824;
    char *temp_ret_834;
    char *temp_ret_871;
    char *temp_ret_899;
    const char *temp_ret_91;
    char *temp_ret_934;
    char *temp_ret_936;
    char *temp_ret_947;
    beNDMWMdlPEBaseInfoWork *temp_v0_109;
    char *temp_v0_112;
    char *temp_v0_117;
    char *temp_v0_121;
    char *temp_v0_137;
    const char *temp_v0_13;
    char *temp_v0_146;
    char *temp_v0_155;
    const char *temp_v0_15;
    const char *temp_v0_18;
    const char *temp_v0_186;
    char *temp_v0_17;
    const char *temp_v0_32;
    char *temp_v0_39;
    char *temp_v0_3;
    char *temp_v0_52;
    char *temp_v0_5;
    char *temp_v0_62;
    char *temp_v0_76;
    char *temp_v0_90;
    char *temp_v0_97;
    const char *temp_v0_9;
    char *var_v0;
    char *var_v0_10;
    char *var_v0_11;
    char *var_v0_12;
    char *var_v0_19;
    char *var_v0_20;
    char *var_v0_21;
    char *var_v0_22;
    char *var_v0_4;
    unsigned int temp_a0_6;
    unsigned int temp_a0_7;
    unsigned int temp_a0_8;
    unsigned int temp_a0_9;
    unsigned int temp_a2_20;
    unsigned int temp_a2_21;
    unsigned int temp_a2_22;
    int chance_sum;
    unsigned int temp_a2_23;
    unsigned int temp_a2_24;
    unsigned int temp_a2_3;
    unsigned int temp_a4;
    unsigned int temp_a4_2;
    unsigned int temp_a4_3;
    unsigned int temp_s1_7;
    unsigned int temp_s1_8;
    unsigned int temp_s2_10;
    unsigned int temp_s2_8;
    unsigned int temp_s3_10;
    unsigned int temp_s3_12;
    unsigned int temp_s3_13;
    unsigned int temp_v0;
    unsigned int temp_v0_103;
    unsigned int temp_v0_106;
    unsigned int temp_v0_120;
    unsigned int temp_v0_124;
    unsigned int temp_v0_125;
    unsigned int temp_v0_126;
    unsigned int temp_v0_127;
    unsigned int temp_v0_170;
    unsigned int temp_v0_175;
    unsigned int temp_v0_38;
    unsigned int temp_v0_43;
    unsigned int temp_v0_50;
    unsigned int temp_v0_55;
    unsigned int temp_v0_56;
    unsigned int temp_v0_57;
    unsigned int temp_v0_58;
    unsigned int temp_v0_66;
    unsigned int temp_v0_81;
    unsigned int temp_v0_85;
    unsigned int temp_v0_89;
    unsigned int temp_v0_96;
    unsigned int temp_v1_4;
    unsigned int temp_v1_5;
    unsigned int temp_v1_8;
    unsigned int var_s1_12;
    unsigned int var_v1_17;
    unsigned int var_v1_4;
    unsigned int var_v1_6;
    unsigned char *temp_ret_174;
    unsigned char *temp_ret_175;
    unsigned char *temp_ret_176;
    unsigned char *temp_ret_177;
    unsigned char *temp_ret_178;
    unsigned char temp_ret_186;
    unsigned char temp_ret_18;
    unsigned char temp_ret_28;
    unsigned char temp_s0;
    unsigned char temp_s0_2;
    unsigned char var_a1;
    unsigned char var_a1_2;
    unsigned char var_a1_3;
    void **temp_ret_1027;
    void **temp_ret_1123;
    void **temp_ret_1135;
    void **temp_ret_213;
    void **temp_ret_220;
    void **temp_ret_241;
    void **temp_ret_242;
    void **temp_ret_269;
    void **temp_ret_304;
    void **temp_ret_305;
    void **temp_ret_350;
    void **temp_ret_413;
    void **temp_ret_436;
    void **temp_ret_467;
    void **temp_ret_492;
    void **temp_ret_521;
    void **temp_ret_588;
    void **temp_ret_645;
    void **temp_ret_658;
    void **temp_ret_697;
    void **temp_ret_711;
    void **temp_ret_741;
    void **temp_ret_761;
    void **temp_ret_762;
    void **temp_ret_821;
    void **temp_ret_842;
    void **temp_ret_884;
    void **temp_ret_917;
    void **temp_ret_960;
    void **temp_v0_102;
    void **temp_v0_105;
    void **temp_v0_107;
    void **temp_v0_113;
    void **temp_v0_115;
    void **temp_v0_119;
    void **temp_v0_122;
    void **temp_v0_123;
    void **temp_v0_135;
    void **temp_v0_139;
    void **temp_v0_140;
    void **temp_v0_144;
    void **temp_v0_150;
    void **temp_v0_159;
    void **temp_v0_169;
    void **temp_v0_174;
    void **temp_v0_35;
    void **temp_v0_37;
    void **temp_v0_41;
    void **temp_v0_42;
    void **temp_v0_49;
    void **temp_v0_53;
    void **temp_v0_54;
    void **temp_v0_65;
    void **temp_v0_75;
    void **temp_v0_80;
    void **temp_v0_84;
    void **temp_v0_88;
    void **temp_v0_95;
    void **var_v1;
    void **var_v1_2;
    void **var_v1_3;
    void *temp_a1;
    void *temp_a2;
    void *temp_a2_2;
    void *temp_ret_1002;
    void *temp_ret_1007;
    void *temp_ret_1010;
    void *temp_ret_1011;
    void *temp_ret_1013;
    void *temp_ret_1016;
    void *temp_ret_1017;
    void *temp_ret_1019;
    void *temp_ret_1021;
    void *temp_ret_1022;
    void *temp_ret_1024;
    void *temp_ret_1028;
    void *temp_ret_1029;
    void *temp_ret_102;
    void *temp_ret_1031;
    void *temp_ret_1035;
    void *temp_ret_1038;
    void *temp_ret_1039;
    void *temp_ret_1041;
    void *temp_ret_1043;
    void *temp_ret_1044;
    void *temp_ret_1046;
    void *temp_ret_1052;
    void *temp_ret_1055;
    void *temp_ret_1056;
    void *temp_ret_1058;
    void *temp_ret_1060;
    void *temp_ret_1061;
    void *temp_ret_1063;
    void *temp_ret_1071;
    void *temp_ret_1073;
    void *temp_ret_1074;
    void *temp_ret_1076;
    void *temp_ret_1079;
    void *temp_ret_1082;
    void *temp_ret_1085;
    void *temp_ret_1087;
    void *temp_ret_1088;
    void *temp_ret_1090;
    void *temp_ret_1098;
    void *temp_ret_10;
    void *temp_ret_1104;
    void *temp_ret_1105;
    void *temp_ret_1107;
    void *temp_ret_1110;
    void *temp_ret_1113;
    void *temp_ret_1116;
    void *temp_ret_1120;
    void *temp_ret_1121;
    void *temp_ret_1128;
    void *temp_ret_1132;
    void *temp_ret_1133;
    void *temp_ret_1145;
    void *temp_ret_1146;
    void *temp_ret_1148;
    void *temp_ret_1151;
    void *temp_ret_1152;
    void *temp_ret_1154;
    void *temp_ret_1157;
    void *temp_ret_1159;
    void *temp_ret_1160;
    void *temp_ret_1162;
    void *temp_ret_1166;
    void *temp_ret_1169;
    void *temp_ret_1171;
    void *temp_ret_1172;
    void *temp_ret_1174;
    void *temp_ret_1176;
    void *temp_ret_1177;
    void *temp_ret_1179;
    void *temp_ret_1181;
    void *temp_ret_1182;
    void *temp_ret_1184;
    void *temp_ret_1194;
    void *temp_ret_1195;
    void *temp_ret_1197;
    int temp_s2_6;
    int temp_s3_15;
    int temp_s3_16;
    int temp_s3_17;
    int temp_s6_3;
    int temp_s8_2;
    void *temp_ret_1199;
    void *temp_ret_1200;
    void *temp_ret_1202;
    void *temp_ret_1205;
    void *temp_ret_1207;
    void *temp_ret_1208;
    void *temp_ret_1210;
    void *temp_ret_1212;
    void *temp_ret_1213;
    void *temp_ret_1215;
    void *temp_ret_1217;
    void *temp_ret_1218;
    void *temp_ret_1220;
    void *temp_ret_1224;
    void *temp_ret_1227;
    void *temp_ret_1236;
    void *temp_ret_1237;
    void *temp_ret_1239;
    void *temp_ret_123;
    void *temp_ret_1241;
    void *temp_ret_1242;
    void *temp_ret_1244;
    void *temp_ret_1246;
    void *temp_ret_1247;
    void *temp_ret_1249;
    void *temp_ret_1251;
    void *temp_ret_1252;
    void *temp_ret_1254;
    void *temp_ret_1256;
    void *temp_ret_1257;
    void *temp_ret_1259;
    void *temp_ret_1263;
    void *temp_ret_1266;
    void *temp_ret_126;
    void *temp_ret_1277;
    void *temp_ret_1278;
    void *temp_ret_1282;
    void *temp_ret_1285;
    void *temp_ret_1291;
    void *temp_ret_1297;
    void *temp_ret_12;
    void *temp_ret_134;
    void *temp_ret_140;
    void *temp_ret_146;
    void *temp_ret_14;
    void *temp_ret_152;
    void *temp_ret_158;
    void *temp_ret_161;
    void *temp_ret_171;
    void *temp_ret_173;
    void *temp_ret_180;
    void *temp_ret_188;
    void *temp_ret_190;
    void *temp_ret_196;
    void *temp_ret_197;
    void *temp_ret_202;
    void *temp_ret_205;
    void *temp_ret_206;
    void *temp_ret_208;
    void *temp_ret_210;
    void *temp_ret_211;
    void *temp_ret_217;
    void *temp_ret_221;
    void *temp_ret_222;
    void *temp_ret_224;
    void *temp_ret_231;
    void *temp_ret_232;
    void *temp_ret_234;
    void *temp_ret_236;
    void *temp_ret_237;
    void *temp_ret_239;
    void *temp_ret_247;
    void *temp_ret_248;
    void *temp_ret_253;
    void *temp_ret_255;
    void *temp_ret_256;
    void *temp_ret_258;
    void *temp_ret_259;
    void *temp_ret_261;
    void *temp_ret_264;
    void *temp_ret_265;
    void *temp_ret_267;
    void *temp_ret_270;
    void *temp_ret_271;
    void *temp_ret_273;
    void *temp_ret_275;
    void *temp_ret_276;
    void *temp_ret_278;
    void *temp_ret_281;
    void *temp_ret_283;
    void *temp_ret_284;
    void *temp_ret_286;
    void *temp_ret_289;
    void *temp_ret_290;
    void *temp_ret_292;
    void *temp_ret_299;
    void *temp_ret_2;
    void *temp_ret_300;
    void *temp_ret_302;
    void *temp_ret_312;
    void *temp_ret_315;
    void *temp_ret_316;
    void *temp_ret_318;
    void *temp_ret_329;
    void *temp_ret_334;
    void *temp_ret_336;
    void *temp_ret_337;
    void *temp_ret_339;
    void *temp_ret_342;
    void *temp_ret_345;
    void *temp_ret_346;
    void *temp_ret_348;
    void *temp_ret_352;
    void *temp_ret_362;
    void *temp_ret_364;
    void *temp_ret_369;
    void *temp_ret_36;
    void *temp_ret_370;
    void *temp_ret_372;
    void *temp_ret_405;
    void *temp_ret_408;
    void *temp_ret_409;
    void *temp_ret_40;
    void *temp_ret_411;
    void *temp_ret_415;
    void *temp_ret_420;
    void *temp_ret_423;
    void *temp_ret_424;
    void *temp_ret_426;
    void *temp_ret_429;
    void *temp_ret_431;
    void *temp_ret_432;
    void *temp_ret_434;
    void *temp_ret_438;
    void *temp_ret_439;
    void *temp_ret_441;
    void *temp_ret_443;
    void *temp_ret_444;
    void *temp_ret_446;
    void *temp_ret_452;
    void *temp_ret_454;
    void *temp_ret_455;
    void *temp_ret_457;
    void *temp_ret_460;
    void *temp_ret_462;
    void *temp_ret_463;
    void *temp_ret_465;
    void *temp_ret_469;
    void *temp_ret_46;
    void *temp_ret_470;
    void *temp_ret_472;
    void *temp_ret_477;
    void *temp_ret_479;
    void *temp_ret_480;
    void *temp_ret_482;
    void *temp_ret_485;
    void *temp_ret_487;
    void *temp_ret_488;
    void *temp_ret_490;
    void *temp_ret_494;
    void *temp_ret_495;
    void *temp_ret_497;
    void *temp_ret_4;
    void *temp_ret_500;
    void *temp_ret_505;
    void *temp_ret_508;
    void *temp_ret_509;
    void *temp_ret_511;
    void *temp_ret_514;
    void *temp_ret_516;
    void *temp_ret_517;
    void *temp_ret_519;
    void *temp_ret_523;
    void *temp_ret_524;
    void *temp_ret_526;
    void *temp_ret_529;
    void *temp_ret_530;
    void *temp_ret_532;
    void *temp_ret_535;
    void *temp_ret_537;
    void *temp_ret_538;
    void *temp_ret_540;
    void *temp_ret_542;
    void *temp_ret_543;
    void *temp_ret_545;
    void *temp_ret_548;
    void *temp_ret_549;
    void *temp_ret_551;
    void *temp_ret_554;
    void *temp_ret_555;
    void *temp_ret_557;
    void *temp_ret_560;
    void *temp_ret_561;
    void *temp_ret_563;
    void *temp_ret_567;
    void *temp_ret_572;
    void *temp_ret_575;
    void *temp_ret_576;
    void *temp_ret_578;
    void *temp_ret_581;
    void *temp_ret_583;
    void *temp_ret_584;
    void *temp_ret_586;
    void *temp_ret_590;
    void *temp_ret_591;
    void *temp_ret_593;
    void *temp_ret_596;
    void *temp_ret_597;
    void *temp_ret_599;
    void *temp_ret_602;
    void *temp_ret_604;
    void *temp_ret_605;
    void *temp_ret_607;
    void *temp_ret_609;
    void *temp_ret_610;
    void *temp_ret_612;
    void *temp_ret_615;
    void *temp_ret_616;
    void *temp_ret_618;
    void *temp_ret_621;
    void *temp_ret_623;
    void *temp_ret_624;
    void *temp_ret_626;
    void *temp_ret_628;
    void *temp_ret_629;
    void *temp_ret_62;
    void *temp_ret_631;
    void *temp_ret_637;
    void *temp_ret_639;
    void *temp_ret_640;
    void *temp_ret_642;
    void *temp_ret_648;
    void *temp_ret_649;
    void *temp_ret_651;
    void *temp_ret_653;
    void *temp_ret_654;
    void *temp_ret_656;
    void *temp_ret_662;
    void *temp_ret_663;
    void *temp_ret_665;
    void *temp_ret_666;
    void *temp_ret_668;
    void *temp_ret_671;
    void *temp_ret_672;
    void *temp_ret_674;
    void *temp_ret_675;
    void *temp_ret_677;
    void *temp_ret_679;
    void *temp_ret_680;
    void *temp_ret_682;
    void *temp_ret_684;
    void *temp_ret_685;
    void *temp_ret_687;
    void *temp_ret_698;
    void *temp_ret_699;
    void *temp_ret_6;
    void *temp_ret_701;
    void *temp_ret_702;
    void *temp_ret_704;
    void *temp_ret_706;
    void *temp_ret_707;
    void *temp_ret_709;
    void *temp_ret_712;
    void *temp_ret_713;
    void *temp_ret_715;
    void *temp_ret_717;
    void *temp_ret_718;
    void *temp_ret_720;
    void *temp_ret_723;
    void *temp_ret_724;
    void *temp_ret_726;
    void *temp_ret_736;
    void *temp_ret_737;
    void *temp_ret_739;
    void *temp_ret_73;
    void *temp_ret_742;
    void *temp_ret_743;
    void *temp_ret_745;
    void *temp_ret_748;
    void *temp_ret_749;
    void *temp_ret_751;
    void *temp_ret_767;
    void *temp_ret_768;
    void *temp_ret_770;
    void *temp_ret_771;
    void *temp_ret_773;
    void *temp_ret_775;
    void *temp_ret_776;
    void *temp_ret_778;
    void *temp_ret_791;
    void *temp_ret_792;
    void *temp_ret_798;
    void *temp_ret_799;
    void *temp_ret_801;
    void *temp_ret_802;
    void *temp_ret_804;
    void *temp_ret_806;
    void *temp_ret_807;
    void *temp_ret_809;
    void *temp_ret_810;
    void *temp_ret_812;
    void *temp_ret_814;
    void *temp_ret_815;
    void *temp_ret_817;
    void *temp_ret_823;
    void *temp_ret_827;
    void *temp_ret_830;
    void *temp_ret_831;
    void *temp_ret_833;
    void *temp_ret_836;
    void *temp_ret_837;
    void *temp_ret_839;
    void *temp_ret_843;
    void *temp_ret_844;
    void *temp_ret_846;
    void *temp_ret_84;
    void *temp_ret_850;
    void *temp_ret_851;
    void *temp_ret_853;
    void *temp_ret_856;
    void *temp_ret_857;
    void *temp_ret_859;
    void *temp_ret_865;
    void *temp_ret_867;
    void *temp_ret_868;
    void *temp_ret_870;
    void *temp_ret_873;
    void *temp_ret_874;
    void *temp_ret_876;
    void *temp_ret_878;
    void *temp_ret_879;
    void *temp_ret_881;
    void *temp_ret_885;
    void *temp_ret_886;
    void *temp_ret_888;
    void *temp_ret_893;
    void *temp_ret_895;
    void *temp_ret_896;
    void *temp_ret_898;
    void *temp_ret_8;
    void *temp_ret_901;
    void *temp_ret_902;
    void *temp_ret_904;
    void *temp_ret_906;
    void *temp_ret_907;
    void *temp_ret_909;
    void *temp_ret_911;
    void *temp_ret_912;
    void *temp_ret_914;
    void *temp_ret_918;
    void *temp_ret_919;
    void *temp_ret_921;
    void *temp_ret_923;
    void *temp_ret_924;
    void *temp_ret_926;
    void *temp_ret_928;
    void *temp_ret_929;
    void *temp_ret_931;
    void *temp_ret_935;
    void *temp_ret_93;
    void *temp_ret_940;
    void *temp_ret_943;
    void *temp_ret_944;
    void *temp_ret_946;
    void *temp_ret_949;
    void *temp_ret_950;
    void *temp_ret_952;
    void *temp_ret_954;
    void *temp_ret_955;
    void *temp_ret_957;
    void *temp_ret_961;
    void *temp_ret_962;
    void *temp_ret_964;
    void *temp_ret_968;
    void *temp_ret_971;
    void *temp_ret_972;
    void *temp_ret_974;
    void *temp_ret_976;
    void *temp_ret_977;
    void *temp_ret_979;
    void *temp_ret_985;
    void *temp_ret_988;
    void *temp_ret_989;
    void *temp_ret_991;
    void *temp_ret_993;
    void *temp_ret_994;
    void *temp_ret_996;
    void *temp_v0_100;
    void *temp_v0_110;
    void *temp_v0_128;
    void *temp_v0_12;
    void *temp_v0_130;
    void *temp_v0_133;
    void *temp_v0_138;
    void *temp_v0_142;
    void *temp_v0_145;
    void *temp_v0_149;
    void *temp_v0_14;
    void *temp_v0_151;
    void *temp_v0_152;
    void *temp_v0_153;
    void *temp_v0_154;
    void *temp_v0_158;
    void *temp_v0_160;
    void *temp_v0_161;
    void *temp_v0_162;
    void *temp_v0_163;
    void *temp_v0_165;
    void *temp_v0_168;
    void *temp_v0_16;
    void *temp_v0_172;
    void *temp_v0_173;
    void *temp_v0_176;
    void *temp_v0_178;
    void *temp_v0_179;
    void *temp_v0_180;
    void *temp_v0_181;
    void *temp_v0_182;
    void *temp_v0_187;
    void *temp_v0_188;
    void *temp_v0_190;
    igObjectList *temp_v0_24;
    void *temp_v0_25;
    beNDMWItemDisk *temp_v0_26;
    beNDMWItemDisk *temp_v0_27;
    void *temp_v0_28;
    void *temp_v0_31;
    void *temp_v0_36;
    beNDMWMdlPEBaseInfoWork *temp_v0_46;
    void *temp_v0_4;
    void *temp_v0_61;
    void *temp_v0_64;
    void *temp_v0_67;
    void *temp_v0_6;
    void *temp_v0_78;
    void *temp_v0_82;
    void *temp_v0_86;
    void *temp_v0_93;

    temp_ret = (const char *)ObjectRef_Get_00407050((int *)((char *)message + 0x14));
    temp_ret_2 = (void *)(GameRamMessage_GetMetaEnum());
    temp_ret_3 = beMessenger_ResolveEnumValue(self->_messenger, temp_ret_2, temp_ret);
    temp_v0 = temp_ret_3;
    switch (temp_v0) {
    case 0:
        temp_ret_4 = (void *)(ObjectRef_Get_00407040(&self->_commonDataList));
        beMessenger_AppendObject(self->_messenger, temp_ret_4);
        return 1;
    case 1:
        temp_ret_5 = beMessenger_GetInt(self->_messenger, 0);
        temp_ret_6 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
        temp_ret_7 = ObjectList_GetAt_003e9260(temp_ret_6, temp_ret_5);
        beMessenger_AppendObject(self->_messenger, temp_ret_7);
        return 1;
    case 2:
        temp_ret_8 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
        temp_ret_9 = ObjectList_GetAt_003e9260(temp_ret_8, 0);
        beMessenger_AppendObject(self->_messenger, temp_ret_9);
        return 1;
    case 3:
        temp_ret_10 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
        temp_ret_11 = ObjectList_GetAt_003e9260(temp_ret_10, 1);
        beMessenger_AppendObject(self->_messenger, temp_ret_11);
        return 1;
    case 4:
        temp_ret_12 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
        temp_ret_13 = ObjectList_GetAt_003e9260(temp_ret_12, 2);
        beMessenger_AppendObject(self->_messenger, temp_ret_13);
        return 1;
    case 5:
        temp_ret_14 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
        temp_ret_15 = ObjectList_GetAt_003e9260(temp_ret_14, 3);
        beMessenger_AppendObject(self->_messenger, temp_ret_15);
        return 1;
    case 11: {
        unsigned char var_s0_2;
        temp_ret_16 = beMessenger_GetInt(self->_messenger, 0);
        var_s0_2 = 1;
        temp_ret_17 = beMessenger_GetBoolCount(self->_messenger);
        if (temp_ret_17 != 0) {
            temp_ret_18 = beMessenger_GetBool(self->_messenger, 0);
            var_s0_2 = temp_ret_18;
        }
        beNDMWGameRam_RecomputeStats(self, temp_ret_16, var_s0_2);
        return 1;
    }
    case 12:
        temp_ret_20 = beMessenger_GetInt(self->_messenger, 0);
        temp_ret_21 = beMessenger_GetString(self->_messenger, 0);
        temp_ret_22 = beNDMWGameRam_FindSpecies(self, (const char *)temp_ret_21);
        beNDMWGameRam_SelectSpecies(self, temp_ret_20, temp_ret_22);
        return 1;
    case 13:
        temp_ret_24 = beMessenger_GetInt(self->_messenger, 0);
        beNDMWGameRam_StoreSpecies(self, temp_ret_24);
        return 1;
    case 14:
        temp_ret_26 = beMessenger_GetInt(self->_messenger, 0);
        temp_ret_27 = beMessenger_GetInt(self->_messenger, 1);
        beMessenger_AppendBool(self->_messenger, beNDMWGameRam_HasUsableWeapon(self, temp_ret_26, temp_ret_27));
        return 1;
    case 15:
        temp_ret_29 = beMessenger_GetInt(self->_messenger, 0);
        beNDMWGameRam_EquipWeapon(self, temp_ret_29, 1);
        return 1;
    case 6:
        temp_ret_31 = beMessenger_GetInt(self->_messenger, 0);
        beNDMWGameRam_ResetPlayer(self, temp_ret_31);
        return 1;
    case 7:
        temp_ret_33 = beMessenger_GetInt(self->_messenger, 0);
        temp_v0_2 = temp_ret_33;
        temp_ret_34 = beMessenger_GetString(self->_messenger, 0);
        temp_v0_3 = (char *)(temp_ret_34);
        temp_ret_35 = beMessenger_GetObjectCount(self->_messenger);
        if (temp_ret_35 == 1) {
            temp_ret_36 = (void *)(beMessenger_GetObject(self->_messenger, 0));
            temp_v0_4 = (void *)(temp_ret_36);
            { RecoveryRef<0> sp4AC((void *)(temp_v0_4), true);
            beNDMWGameRam_JoinPlayerWithUnicodeName(self, temp_v0_2, temp_v0_3, sp4AC);
            }
        } else {
            temp_ret_38 = beMessenger_GetStringCount(self->_messenger);
            if (temp_ret_38 == 2) {
                temp_ret_39 = beMessenger_GetString(self->_messenger, 1);
                temp_v0_5 = (char *)(temp_ret_39);
                beNDMWGameRam_JoinPlayerWithName(self, temp_v0_2, temp_v0_3, StringRef(temp_v0_5 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_5)));
            }
        }
        return 1;
    case 8:
        temp_ret_44 = beMessenger_GetInt(self->_messenger, 0);
        beNDMWGameRam_LeavePlayer(self, temp_ret_44);
        return 1;
    case 16:
        var_s2 = 0;
        do {
            temp_ret_46 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_47 = ObjectList_GetAt_003e9260(temp_ret_46, var_s2);
            temp_v0_6 = (void *)(temp_ret_47);
            temp_ret_48 = (beDataObjBool *)(igProperty_GetRecordByte((int)temp_v0_6, ISUSE_4));
            if (temp_ret_48->_data != 0) {
                temp_ret_49 = (int)igProperty_GetRecord(temp_v0_6, MHP);
                temp_ret_50 = DataObjInt_GetValue_00406f90((beDataObjInt *)temp_ret_49);
                temp_ret_51 = (int)igProperty_GetRecord(temp_v0_6, HP);
                ((beDataObjInt *)temp_ret_51)->_data = temp_ret_50;
                temp_ret_52 = (int)igProperty_GetRecord(temp_v0_6, MMP);
                temp_ret_53 = DataObjInt_GetValue_00406f90((beDataObjInt *)temp_ret_52);
                temp_ret_54 = (int)igProperty_GetRecord(temp_v0_6, MP);
                ((beDataObjInt *)temp_ret_54)->_data = temp_ret_53;
            }
            var_s2 += 1;
        } while (var_s2 < 4);
        return 1;
    case 9:
        temp_ret_55 = beMessenger_GetInt(self->_messenger, 0);
        temp_v0_7 = temp_ret_55;
        temp_ret_56 = beMessenger_GetInt(self->_messenger, 1);
        var_v0_2 = beMessenger_GetIntCount(self->_messenger) < 3 ? 0 : beMessenger_GetInt(self->_messenger, 2);
        var_v0_3 = beMessenger_GetIntCount(self->_messenger) < 4 ? -1 : beMessenger_GetInt(self->_messenger, 3);
        temp_ret_61 = beNDMWGameRam_ChangeHp(self, temp_v0_7, temp_ret_56, var_v0_3);
        if ((temp_ret_61 != 0) && (var_v0_2 != 0)) {
            temp_ret_62 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_63 = ObjectList_GetAt_003e9260(temp_ret_62, temp_v0_7);
            temp_ret_64 = (int)igProperty_GetRecordString((void *)temp_ret_63, DIGIMONNAME_2);
            temp_ret_65 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_64)->_data);
            temp_ret_66 = beMessenger_PrepareDelayedSelection(self->_messenger, &PLAYER_2[0], temp_ret_65, temp_v0_7);
            beMessenger_AppendString(self->_messenger, &x_250healhit00[0]);
            beMessenger_AppendString(self->_messenger, &SQ_HEALEFONLY[0]);
            beMessenger_AppendFloat(self->_messenger, 1.0f);
            Vec3f_Copy(&sp378, &g_vec3Zero[0]);
            beMessenger_AppendVec3(self->_messenger, &sp378);
            beMessenger_AppendBool(self->_messenger, 0U);
            beMessenger_AppendBool(self->_messenger, 1U);
            temp_ret_67 = beMessenger_EnqueueSelected(self->_messenger, &SETEFFECT[0], 1);
        }
        return 1;
    case 10:
        temp_ret_68 = beMessenger_GetInt(self->_messenger, 0);
        temp_v0_8 = temp_ret_68;
        temp_ret_69 = beMessenger_GetInt(self->_messenger, 1);
        var_s0_3 = 0;
        temp_ret_70 = beMessenger_GetIntCount(self->_messenger);
        if (temp_ret_70 == 3) {
            temp_ret_71 = beMessenger_GetInt(self->_messenger, 2);
            var_s0_3 = temp_ret_71;
        }
        beNDMWGameRam_ChangeMp(self, temp_v0_8, temp_ret_69);
        if (var_s0_3 != 0) {
            temp_ret_73 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_74 = ObjectList_GetAt_003e9260(temp_ret_73, temp_v0_8);
            temp_ret_75 = (int)igProperty_GetRecordString((void *)temp_ret_74, DIGIMONNAME_2);
            temp_ret_76 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_75)->_data);
            temp_ret_77 = beMessenger_PrepareDelayedSelection(self->_messenger, &PLAYER_2[0], temp_ret_76, temp_v0_8);
            beMessenger_AppendString(self->_messenger, &x_250healhit00[0]);
            beMessenger_AppendString(self->_messenger, &SQ_HEALEFONLY[0]);
            beMessenger_AppendFloat(self->_messenger, 1.0f);
            Vec3f_Copy(&sp368, &g_vec3Zero[0]);
            beMessenger_AppendVec3(self->_messenger, &sp368);
            beMessenger_AppendBool(self->_messenger, 0U);
            beMessenger_AppendBool(self->_messenger, 1U);
            temp_ret_78 = beMessenger_EnqueueSelected(self->_messenger, &SETEFFECT[0], 1);
        }
        return 1;
    case 21:
        temp_ret_79 = beMessenger_GetString(self->_messenger, 0);
        temp_v0_9 = temp_ret_79;
        var_s0_4 = 0;
        temp_ret_80 = strcmp(temp_v0_9, EXP);
        if (temp_ret_80 == 0) {
            temp_ret_81 = beMessenger_GetString(self->_messenger, 1);
            temp_v0_10 = (char *)(temp_ret_81);
            temp_ret_82 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_83 = beMessenger_GetInt(self->_messenger, 1);
            temp_v0_11 = temp_ret_83;
            temp_ret_84 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_85 = ObjectList_GetAt_003e9260(temp_ret_84, temp_ret_82);
            temp_ret_86 = (int)igProperty_GetRecord(temp_ret_85, EXP);
            temp_v0_12 = (void *)(temp_ret_86);
            temp_ret_87 = strcmp(temp_v0_10, &SET[0]);
            if (temp_ret_87 == 0) {
                ((beDataObjInt *)temp_v0_12)->_data = temp_v0_11;
            } else {
                temp_ret_88 = strcmp(temp_v0_10, &ADD[0]);
                if (temp_ret_88 == 0) {
                    temp_ret_89 = DataObjInt_GetValue_00406f90((beDataObjInt *)((int) temp_v0_12));
                    ((beDataObjInt *)temp_v0_12)->_data = (int)((int) (temp_v0_11 + temp_ret_89));
                }
            }
        } else {
            temp_ret_90 = strcmp(temp_v0_9, HP);
            if (temp_ret_90 == 0) {
                temp_ret_91 = beMessenger_GetString(self->_messenger, 1);
                temp_v0_13 = temp_ret_91;
                temp_ret_92 = beMessenger_GetInt(self->_messenger, 0);
                temp_ret_93 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                temp_ret_94 = ObjectList_GetAt_003e9260(temp_ret_93, temp_ret_92);
                temp_v0_14 = (void *)(temp_ret_94);
                temp_ret_95 = strcmp(temp_v0_13, GETHP);
                if (temp_ret_95 == 0) {
                    temp_ret_96 = (int)igProperty_GetRecord(temp_v0_14, HP);
                    var_s0_4 = ((beDataObjInt *)temp_ret_96)->_data;
                } else {
                    temp_ret_97 = strcmp(temp_v0_13, &GETMHP[0]);
                    if (temp_ret_97 == 0) {
                        temp_ret_98 = (int)igProperty_GetRecord(temp_v0_14, MHP);
                        var_s0_4 = ((beDataObjInt *)temp_ret_98)->_data;
                    }
                }
            } else {
                temp_ret_99 = strcmp(temp_v0_9, MP);
                if (temp_ret_99 == 0) {
                    temp_ret_100 = beMessenger_GetString(self->_messenger, 1);
                    temp_v0_15 = temp_ret_100;
                    temp_ret_101 = beMessenger_GetInt(self->_messenger, 0);
                    temp_ret_102 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                    temp_ret_103 = ObjectList_GetAt_003e9260(temp_ret_102, temp_ret_101);
                    temp_v0_16 = (void *)(temp_ret_103);
                    temp_ret_104 = strcmp(temp_v0_15, &GETMP[0]);
                    if (temp_ret_104 == 0) {
                        temp_ret_105 = (int)igProperty_GetRecord(temp_v0_16, MP);
                        var_s0_4 = ((beDataObjInt *)temp_ret_105)->_data;
                    } else {
                        temp_ret_106 = strcmp(temp_v0_15, &GETMMP[0]);
                        if (temp_ret_106 == 0) {
                            temp_ret_107 = (int)igProperty_GetRecord(temp_v0_16, MMP);
                            var_s0_4 = ((beDataObjInt *)temp_ret_107)->_data;
                        }
                    }
                }
            }
        }
        beMessenger_ClearInt(self->_messenger);
        beMessenger_AppendInt(self->_messenger, var_s0_4);
        return 1;
    case 17:
        temp_ret_108 = beMessenger_GetString(self->_messenger, 0);
        temp_v0_17 = (char *)(temp_ret_108);
        temp_ret_109 = beMessenger_GetString(self->_messenger, 1);
        temp_v0_18 = temp_ret_109;
        temp_ret_110 = beMessenger_GetString(self->_messenger, 2);
        temp_v0_19 = (char *)(temp_ret_110);
        temp_ret_111 = beMessenger_GetInt(self->_messenger, 0);
        temp_v0_20 = temp_ret_111;
        temp_ret_112 = beMessenger_GetInt(self->_messenger, 1);
        temp_v0_21 = temp_ret_112;
        temp_ret_113 = beMessenger_GetInt(self->_messenger, 2);
        temp_v0_22 = temp_ret_113;
        temp_ret_114 = beMessenger_GetInt(self->_messenger, 3);
        temp_v0_23 = temp_ret_114;
        if (strcmp(temp_v0_18, &SET[0]) == 0) {
            var_s0_5 = 0;
        } else if (strcmp(temp_v0_18, &CLR_2[0]) == 0) {
            var_s0_5 = 1;
        } else if (strcmp(temp_v0_18, &IS[0]) == 0) {
            var_s0_5 = 2;
        } else if (strcmp(temp_v0_18, &ISMAX[0]) == 0) {
            var_s0_5 = 3;
        } else if (strcmp(temp_v0_18, &ISEQUIP[0]) == 0) {
            var_s0_5 = 4;
        } else if (strcmp(temp_v0_18, &GET[0]) == 0) {
            var_s0_5 = 5;
        } else if (strcmp(temp_v0_18, &ADD[0]) == 0) {
            var_s0_5 = 6;
        } else {
            return 1;
        }
        {
            temp_ret_122 = strcmp(temp_v0_17, &DEVICE_2[0]);
            if (temp_ret_122 == 0) {
                temp_ret_123 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                temp_ret_124 = ObjectList_GetAt_003e9260(temp_ret_123, temp_v0_20);
                temp_ret_125 = (int)igProperty_GetRecordFolder(temp_ret_124, DEVICEFOLDER);
                temp_ret_126 = (void *)(ObjectRef_Get_00406f80(&((beDataObjObjectList *)temp_ret_125)->_data));
                temp_v0_24 = (igObjectList *)(temp_ret_126);
                var_s5 = 0;
                if (var_s0_5 != 3) {
                    if (strcmp(temp_v0_19, &weapon_2[0]) == 0) {
                        var_s5 = 0;
                    } else if (strcmp(temp_v0_19, &armor1_2[0]) == 0) {
                        var_s5 = 1;
                    } else if (strcmp(temp_v0_19, &armor2_2[0]) == 0) {
                        var_s5 = 2;
                    } else if (strcmp(temp_v0_19, &abChip_2[0]) == 0) {
                        var_s5 = 3;
                    } else {
                        return 1;
                    }
                }
                switch (var_s0_5) {
                case 0:
                    if (temp_v0_24->_count == 0x24) {
                        beMessenger_AppendBool(self->_messenger, 0U);
                    } else {
                        switch (var_s5) {
                        case 0:
                            temp_ret_131 = igObject_GetAllocator(self);
                            temp_ret_132 = Memory_SelectAllocator_003e9370(kIGMemoryPoolHandleUser0, temp_ret_131);
                            temp_ret_134 = (void *)(beNDMWItemWeapon_Create(AllocatorValue_Make_00406f70(temp_ret_132).v));
                            { RecoveryRef<1> sp4A8((void *)(temp_ret_134), false);
                            temp_ret_135 = beNDMWItemWeapon_Set(sp4A8.value, temp_v0_21, temp_v0_23, temp_v0_22);
                            temp_ret_136 = ObjectList_AppendRetained(temp_v0_24, sp4A8.value);
                            }
                            break;
                        case 1:
                            temp_ret_137 = igObject_GetAllocator(self);
                            temp_ret_138 = Memory_SelectAllocator_003e9370(kIGMemoryPoolHandleUser0, temp_ret_137);
                            temp_ret_140 = (void *)(beNDMWItemBlueArmor_Create(AllocatorValue_Make_00406f60(temp_ret_138).v));
                            { RecoveryRef<2> sp4A4((void *)(temp_ret_140), false);
                            temp_ret_141 = beNDMWItemBlueArmor_Set(sp4A4.value, temp_v0_21, temp_v0_23, temp_v0_22);
                            temp_ret_142 = ObjectList_AppendRetained(temp_v0_24, sp4A4.value);
                            }
                            break;
                        case 2:
                            temp_ret_143 = igObject_GetAllocator(self);
                            temp_ret_144 = Memory_SelectAllocator_003e9370(kIGMemoryPoolHandleUser0, temp_ret_143);
                            temp_ret_146 = (void *)(beNDMWItemYellowArmor_Create(AllocatorValue_Make_00406f50(temp_ret_144).v));
                            { RecoveryRef<3> sp4A0((void *)(temp_ret_146), false);
                            temp_ret_147 = beNDMWItemYellowArmor_Set(sp4A0.value, temp_v0_21, temp_v0_22);
                            temp_ret_148 = ObjectList_AppendRetained(temp_v0_24, sp4A0.value);
                            }
                            break;
                        case 3:
                            temp_ret_149 = igObject_GetAllocator(self);
                            temp_ret_150 = Memory_SelectAllocator_003e9370(kIGMemoryPoolHandleUser0, temp_ret_149);
                            temp_ret_152 = (void *)(beNDMWItemAbilityChip_Create(AllocatorValue_Make_00406f40(temp_ret_150).v));
                            { RecoveryRef<4> sp49C((void *)(temp_ret_152), false);
                            temp_ret_153 = beNDMWItemAbilityChip_Set(sp49C.value, temp_v0_21);
                            temp_ret_154 = ObjectList_AppendRetained(temp_v0_24, sp49C.value);
                            }
                            break;
                        }
                        beMessenger_AppendBool(self->_messenger, 1U);
                    }
                    goto block_215;
                case 1:
                    {
                    beNDMWItemBase *elem;
                    int cnt = temp_v0_24->_count;
                    var_a1 = 0;
                    for (var_s0_6 = 0; var_s0_6 < cnt; ++var_s0_6) {
                        elem = (beNDMWItemBase *)((void **)temp_v0_24->_data)[var_s0_6]; /* matching construct: _data is a 4-byte int reference, indexed as the pointer array the pre-typing struct declared */
                        if ((var_s5 == elem->_kindNo) && (temp_v0_21 == elem->_recNo) && (elem->_isEquip == 0)) {

                            temp_ret_155 = ObjectList_GetAt_003e9260(temp_v0_24, var_s0_6);
                            ObjectRef_Release_003e9110(temp_ret_155);
                            ObjectList_RemoveAt_00406f20(temp_v0_24, var_s0_6);
                            var_a1 = 1;
                            ((void **)temp_v0_24->_data)[temp_v0_24->_count] = 0; /* matching construct: _data is a 4-byte int reference, indexed as the pointer array the pre-typing struct declared */
                            break;
                        }
                    }
                    beMessenger_AppendBool(self->_messenger, var_a1);
                    }
                    goto block_215;
                case 2:
                    {
                    beNDMWItemBase *elem;
                    int cnt = temp_v0_24->_count;
                    for (var_a2 = 0; var_a2 < cnt; ++var_a2) {
                        elem = (beNDMWItemBase *)((void **)temp_v0_24->_data)[var_a2]; /* matching construct: _data is a 4-byte int reference, indexed as the pointer array the pre-typing struct declared */
                        if ((var_s5 == elem->_kindNo) && (temp_v0_21 == elem->_recNo)) {

                            beMessenger_AppendBool(self->_messenger, 1U);
                            return 1;
                        }
                    }
                    }
block_129:
                    beMessenger_AppendBool(self->_messenger, 0U);
                    goto block_215;
                case 3:
                    if (temp_v0_24->_count == 0x24) {
                        beMessenger_AppendBool(self->_messenger, 1U);
                    } else {
                        beMessenger_AppendBool(self->_messenger, 0U);
                    }
                    goto block_215;
                case 4:
                    {
                    beNDMWItemBase *elem;
                    int cnt = temp_v0_24->_count;
                    var_a1_2 = 0;
                    for (var_a3 = 0; var_a3 < cnt; ++var_a3) {
                        elem = (beNDMWItemBase *)((void **)temp_v0_24->_data)[var_a3]; /* matching construct: _data is a 4-byte int reference, indexed as the pointer array the pre-typing struct declared */
                        if ((var_s5 == elem->_kindNo) && (temp_v0_21 == elem->_recNo) && (elem->_isEquip != 0)) {

                            var_a1_2 = 1;
                                                    break;
                        }
                    }
                    beMessenger_AppendBool(self->_messenger, var_a1_2);
                    }
                    goto block_215;
                }
            } else {
                temp_ret_157 = strcmp(temp_v0_17, &DISK_2[0]);
                if (temp_ret_157 == 0) {
                    temp_ret_158 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                    temp_ret_159 = ObjectList_GetAt_003e9260(temp_ret_158, temp_v0_20);
                    temp_ret_160 = (int)igProperty_GetRecordFolder(temp_ret_159, DISKFOLDER);
                    temp_ret_161 = (void *)(ObjectRef_Get_00406f80(&((beDataObjObjectList *)temp_ret_160)->_data));
                    temp_v0_25 = (void *)(temp_ret_161);
                    switch (var_s0_5) {
                    case 0:
                        temp_ret_162 = beNDMWItemBase_IndexOfRecNo(temp_v0_25, temp_v0_21);
                        temp_ret_163 = ObjectList_GetAt_003e9260(temp_v0_25, temp_ret_162);
                        temp_v0_26 = (beNDMWItemDisk *)(temp_ret_163);
                        temp_a0_4 = temp_v0_26->_kazu;
                        if (temp_a0_4 == 9) {
                            beMessenger_AppendBool(self->_messenger, 0U);
                        } else {
                            temp_a0_5 = temp_a0_4 + temp_v0_23;
                            if (temp_a0_5 < 0xA) {
                                temp_v0_26->_kazu = temp_a0_5;
                            } else {
                                temp_v0_26->_kazu = 9;
                            }
                            beMessenger_AppendBool(self->_messenger, 1U);
                        }
                        break;
                    case 1:
                        temp_ret_164 = beNDMWItemBase_IndexOfRecNo(temp_v0_25, temp_v0_21);
                        temp_ret_165 = ObjectList_GetAt_003e9260(temp_v0_25, temp_ret_164);
                        temp_v0_27 = (beNDMWItemDisk *)(temp_ret_165);
                        temp_v1 = temp_v0_27->_kazu;
                        if (temp_v1 == 0) {
                            beMessenger_AppendBool(self->_messenger, 0U);
                        } else {
                            temp_v1_2 = temp_v1 - temp_v0_23;
                            if (temp_v1_2 >= 0) {
                                temp_v0_27->_kazu = temp_v1_2;
                            } else {
                                temp_v0_27->_kazu = 0;
                            }
                            beMessenger_AppendBool(self->_messenger, 1U);
                        }
                        break;
                    case 2:
                        temp_ret_166 = beNDMWItemBase_IndexOfRecNo(temp_v0_25, temp_v0_21);
                        temp_ret_167 = ObjectList_GetAt_003e9260(temp_v0_25, temp_ret_166);
                        if (((beNDMWItemDisk *)temp_ret_167)->_kazu != 0) {
                            beMessenger_AppendBool(self->_messenger, 1U);
                        } else {
                            beMessenger_AppendBool(self->_messenger, 0U);
                        }
                        break;
                    case 3:
                        temp_ret_168 = beNDMWItemBase_IndexOfRecNo(temp_v0_25, temp_v0_21);
                        temp_ret_169 = ObjectList_GetAt_003e9260(temp_v0_25, temp_ret_168);
                        if (((beNDMWItemDisk *)temp_ret_169)->_kazu == 9) {
                            beMessenger_AppendBool(self->_messenger, 1U);
                        } else {
                            beMessenger_AppendBool(self->_messenger, 0U);
                        }
                        break;
                    }
                    goto block_215;
                }
                temp_ret_170 = strcmp(temp_v0_17, FLAG_2);
                if (temp_ret_170 == 0) {
                    temp_ret_171 = (void *)(ObjectRef_Get_00407040(&self->_commonDataList));
                    temp_ret_172 = (int)igProperty_GetRecordArray(temp_ret_171, FLAGFOLDER);
                    temp_ret_173 = (void *)(ObjectRef_Get_00406f10(&((beDataObjBoolList *)temp_ret_172)->_data));
                    temp_v0_28 = (void *)(temp_ret_173);
                    switch (var_s0_5) {
                    case 0:
                        temp_ret_174 = (unsigned char *)(DataList_GetData_00406f00((igUnsignedCharList *)temp_v0_28));
                        if (*(unsigned char *)(temp_ret_174 + temp_v0_21) != 0) {
                            beMessenger_AppendBool(self->_messenger, 0U);
                        } else {
                            temp_v0_29 = ((igBoolList *)temp_v0_28)->_count;
                            if ((temp_v0_29 != 0) && (temp_v0_21 >= 0) && (temp_v0_21 < temp_v0_29)) {
                                temp_s0 = GPR_005549f0;
                                temp_ret_175 = (unsigned char *)(DataList_GetData_00406f00((igUnsignedCharList *)temp_v0_28));
                                *(unsigned char *)(temp_v0_21 + (int)temp_ret_175) = temp_s0;
                            }
                            beMessenger_AppendBool(self->_messenger, 1U);
                        }
                        break;
                    case 1:
                        temp_ret_176 = (unsigned char *)(DataList_GetData_00406f00((igUnsignedCharList *)temp_v0_28));
                        if (*(unsigned char *)(temp_ret_176 + temp_v0_21) == 0) {
                            beMessenger_AppendBool(self->_messenger, 0U);
                        } else {
                            temp_v0_30 = ((igBoolList *)temp_v0_28)->_count;
                            if ((temp_v0_30 != 0) && (temp_v0_21 >= 0) && (temp_v0_21 < temp_v0_30)) {
                                temp_s0_2 = GPR_005549f4;
                                temp_ret_177 = (unsigned char *)(DataList_GetData_00406f00((igUnsignedCharList *)temp_v0_28));
                                *(unsigned char *)(temp_v0_21 + (int)temp_ret_177) = temp_s0_2;
                            }
                            beMessenger_AppendBool(self->_messenger, 1U);
                        }
                        break;
                    case 2:
                        temp_ret_178 = (unsigned char *)(DataList_GetData_00406f00((igUnsignedCharList *)temp_v0_28));
                        beMessenger_AppendBool(self->_messenger, *(unsigned char *)(temp_ret_178 + temp_v0_21));
                        break;
                    }
                    goto block_215;
                }
                temp_ret_179 = strcmp(temp_v0_17, &BIT_3[0]);
                if (temp_ret_179 == 0) {
                    temp_ret_180 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                    temp_ret_181 = ObjectList_GetAt_003e9260(temp_ret_180, temp_v0_20);
                    temp_v0_31 = (void *)(temp_ret_181);
                    switch (var_s0_5) {
                    case 0:
                        temp_ret_182 = (int)igProperty_GetRecord(temp_v0_31, &BIT_3[0]);
                        ((beDataObjInt *)temp_ret_182)->_data = temp_v0_21;
                        break;
                    case 5:
                        beMessenger_ClearInt(self->_messenger);
                        temp_ret_183 = (int)igProperty_GetRecord(temp_v0_31, &BIT_3[0]);
                        beMessenger_AppendInt(self->_messenger, ((beDataObjInt *)temp_ret_183)->_data);
                        break;
                    case 6:
                        temp_ret_184 = (int)igProperty_GetRecord(temp_v0_31, &BIT_3[0]);
                        var_s0_7 = temp_v0_21 + ((beDataObjInt *)temp_ret_184)->_data;
                        if (var_s0_7 < 0) {
                            var_s0_7 = 0;
                        } else if (var_s0_7 > 0x98967F) {
                            var_s0_7 = 0x98967F;
                        }
                        temp_ret_185 = (int)igProperty_GetRecord(temp_v0_31, &BIT_3[0]);
                        ((beDataObjInt *)temp_ret_185)->_data = var_s0_7;
                        break;
                    }
                } else {
                    return 1;
                }
            }
        }
block_215:
        return 1;
    case 19:
        temp_ret_186 = beMessenger_GetBool(self->_messenger, 0);
        self->_isDispFightData = temp_ret_186;
        return 1;
    case 18:
        temp_ret_187 = beMessenger_GetString(self->_messenger, 0);
        temp_v0_32 = temp_ret_187;
        { StringRef sp498(temp_v0_32 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_32));
        temp_ret_190 = (void *)(FightCom_GetMetaEnum());
        temp_ret_191 = (const char *)ObjectRef_Get_00407050((int *)&sp498.p);
        unsigned int sp494;
        igMetaEnum_GetValueByName(temp_ret_190, temp_ret_191, &sp494);
        switch (sp494) {
        case 1:
            temp_ret_193 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_194 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_195 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_196 = (void *)(beMessenger_GetObject(self->_messenger, 0));
            temp_v0_33 = (beNDMWMdlPEBaseInfoWork *)(temp_ret_196);
            switch (temp_ret_195 / 10000) {
            case 4:
                beMessenger_AppendBool(self->_messenger, 1U);
                            break;
            default:
                temp_ret_197 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                temp_ret_198 = ObjectList_GetAt_003e9260(temp_ret_197, temp_ret_193);
                temp_v0_34 = (void *)(temp_ret_198);
                temp_ret_199 = (int)igProperty_GetRecord(temp_v0_34, WEAPONSKILLNO);
                temp_s3 = ((beDataObjInt *)temp_ret_199)->_data;
                temp_ret_200 = (int)igProperty_GetRecord(temp_v0_34, SUBAYASA);
                temp_s1 = ((beDataObjInt *)temp_ret_200)->_data;
                temp_ret_201 = (int)igProperty_GetRecordIntList(temp_v0_34, SKILL);
                temp_ret_202 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_201)->_data));
                temp_ret_203 = DataList_GetData_003e9090(temp_ret_202);
                temp_s3 = *(int *)(temp_ret_203 + (temp_s3 * 4));
                temp_ret_204 = (int)igProperty_GetRecord(temp_v0_34, MEICHURITSU);
                temp_s0_3 = ((beDataObjInt *)temp_ret_204)->_data;
                temp_ret_205 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                if (temp_ret_205 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                    temp_ret_206 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_207 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_206));
                }
                temp_ret_208 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                temp_ret_209 = beDataBase_GetRecordInt(temp_ret_208, temp_ret_194, SUBAYASA);
                temp_ret_210 = (void *)(ObjectRef_Get_00406ef0(&temp_v0_33->_downDataList));
                if (temp_ret_210 == 0) {
                    var_s5_2 = 0;
                } else {
                    temp_ret_211 = (void *)(ObjectRef_Get_00406ef0(&temp_v0_33->_downDataList));
                    temp_ret_212 = DataList_GetData_003e9090(temp_ret_211);
                    var_s5_2 = ((int *)temp_ret_212)[3];
                }
                temp_ret_213 = (void **)(ObjectRef_Get_00406e50(&((beSystem *)self->_system)->_random));
                temp_v0_35 = (void **)(temp_ret_213);
                temp_a2_3 = ((DW4VC_96_0 *)(temp_v0_35))->vX() % 10000U;
                if ((int) temp_a2_3 < ((int) (temp_s0_3 * ((temp_s1 * 0x1E) + (temp_s3 * 0x14) + 0x1770)) / (int) ((int) (temp_ret_209 * (0x64 - var_s5_2)) / 100))) {
                    beMessenger_AppendBool(self->_messenger, 1U);
                } else {
                    beMessenger_AppendBool(self->_messenger, 0U);
                }
                            break;
            }
            break;
        case 2:
            temp_ret_214 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_215 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_216 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_217 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_218 = ObjectList_GetAt_003e9260(temp_ret_217, temp_ret_214);
            temp_v0_36 = (void *)(temp_ret_218);
            if ((temp_ret_216 / 10000) != 4) {
                temp_ret_219 = (int)igProperty_GetRecord(temp_v0_36, CHIMEIRITSU);
                temp_s0_4 = ((beDataObjInt *)temp_ret_219)->_data;
                temp_ret_220 = (void **)(ObjectRef_Get_00406e50(&((beSystem *)self->_system)->_random));
                temp_v0_37 = (void **)(temp_ret_220);
                temp_v0_38 = ((DW4VC_96_0 *)(temp_v0_37))->vX() % 200U;
                if ((int) temp_v0_38 < temp_s0_4) {
                    var_a1_3 = 1;
                } else {
                    var_a1_3 = 0;
                }
            } else {
                temp_a2_4 = (int)((int) temp_ret_216 % 1000);
                int sp490;
                beNDMWGameRam_FindTechniqueRow(self, temp_v0_36, temp_a2_4, &sp490);
                temp_ret_221 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                if (temp_ret_221 == 0) {
                    beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                    temp_ret_222 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_223 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_222));
                }
                temp_ret_224 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                temp_ret_225 = (char *)(beDataBase_GetRecordString(temp_ret_224, sp490, ZOKUSEI));
                temp_v0_39 = (char *)(temp_ret_225);
                temp_ret_226 = strcmp(temp_v0_39, &fire[0]);
                if (temp_ret_226 == 0) {
                    var_s0_8 = 0;
                } else {
                    temp_ret_227 = strcmp(temp_v0_39, &ice[0]);
                    if (temp_ret_227 == 0) {
                        var_s0_8 = 1;
                    } else {
                        temp_ret_228 = strcmp(temp_v0_39, &thunder[0]);
                        if (temp_ret_228 == 0) {
                            var_s0_8 = 2;
                        } else {
                            temp_ret_229 = strcmp(temp_v0_39, &dark[0]);
                            if (temp_ret_229 == 0) {
                                var_s0_8 = 3;
                            } else {
                                temp_ret_230 = strcmp(temp_v0_39, &poison[0]);
                                if (temp_ret_230 == 0) {
                                    var_s0_8 = 4;
                                } else {
                                    var_s0_8 = -1;
                                }
                            }
                        }
                    }
                }
                temp_ret_231 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                if (temp_ret_231 == 0) {
                    beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                    temp_ret_232 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_233 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_232));
                }
                temp_ret_234 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                temp_ret_235 = beDataBase_GetRecordInt(temp_ret_234, sp490, CHIMEIRITSU);
                temp_v0_40 = temp_ret_235;
                if (var_s0_8 >= 0) {
                    if (var_s0_8 >= 0) {
                        temp_ret_236 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        if (temp_ret_236 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                            temp_ret_237 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_238 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_237));
                        }
                        temp_ret_239 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        temp_ret_240 = beDataBase_GetRecordInt(temp_ret_239, temp_ret_215, g_resistanceFields[var_s0_8]);
                        var_s0_9 = temp_ret_240;
                    } else {
                        var_s0_9 = 0;
                    }
                    temp_ret_241 = (void **)(ObjectRef_Get_00406e50(&((beSystem *)self->_system)->_random));
                    temp_v0_41 = (void **)(temp_ret_241);
                    temp_a4 = ((DW4VC_96_0 *)(temp_v0_41))->vX() % 1000U;
                    if ((int) temp_a4 < ((int) ((temp_v0_40 + 0x64) * (0x2710 / (int) (((int) (var_s0_9 * 0xC) / 10) + 0x32))) / 100)) {
                        var_a1_3 = 1;
                    } else {
                        var_a1_3 = 0;
                    }
                } else {
                    temp_ret_242 = (void **)(ObjectRef_Get_00406e50(&((beSystem *)self->_system)->_random));
                    temp_v0_42 = (void **)(temp_ret_242);
                    temp_v0_43 = ((DW4VC_96_0 *)(temp_v0_42))->vX() % 100U;
                    if ((int) temp_v0_43 < temp_v0_40) {
                        var_a1_3 = 1;
                    } else {
                        var_a1_3 = 0;
                    }
                }
            }
            beMessenger_AppendBool(self->_messenger, var_a1_3);
            break;
        case 5:
            temp_ret_243 = beMessenger_GetInt(self->_messenger, 0);
            temp_v0_44 = temp_ret_243;
            temp_ret_244 = beMessenger_GetInt(self->_messenger, 1);
            temp_v0_45 = temp_ret_244;
            temp_ret_245 = beMessenger_GetInt(self->_messenger, 2);
            sp12C = beMessenger_GetInt(self->_messenger, 3);
            temp_ret_247 = (void *)(beMessenger_GetObject(self->_messenger, 0));
            temp_v0_46 = (beNDMWMdlPEBaseInfoWork *)(temp_ret_247);
            temp_ret_248 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_249 = ObjectList_GetAt_003e9260(temp_ret_248, temp_v0_44);
            temp_v0_47 = (void *)(temp_ret_249);
            var_s1 = -1;
            switch (temp_ret_245 / 10000) {
            default: {
                temp_ret_250 = (int)igProperty_GetRecord(temp_v0_47, WEAPONSKILLNO);
                temp_s0_5 = ((beDataObjInt *)temp_ret_250)->_data;
                temp_ret_251 = (int)igProperty_GetRecord(temp_v0_47, TSUYOSA);
                temp_s2 = ((beDataObjInt *)temp_ret_251)->_data;
                temp_ret_252 = (int)igProperty_GetRecordIntList(temp_v0_47, SKILL);
                temp_ret_253 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_252)->_data));
                temp_ret_254 = DataList_GetData_003e9090(temp_ret_253);
                var_s0 = *(int *)(temp_ret_254 + (temp_s0_5 * 4));
                temp_ret_255 = (void *)(ObjectRef_Get_00406ef0(&temp_v0_46->_downDataList));
                if (temp_ret_255 == 0) {
                    var_s7 = 0;
                } else {
                    temp_ret_256 = (void *)(ObjectRef_Get_00406ef0(&temp_v0_46->_downDataList));
                    temp_ret_257 = DataList_GetData_003e9090(temp_ret_256);
                    var_s7 = ((int *)temp_ret_257)[5];
                }
                temp_ret_258 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                if (temp_ret_258 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                    temp_ret_259 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_260 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_259));
                }
                temp_ret_261 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                temp_ret_262 = beDataBase_GetRecordInt(temp_ret_261, temp_v0_45, MAMORI);
                var_s7 = temp_ret_262 - var_s7;
                var_s2_2 = (int)((int) ((temp_s2 * 6) + (var_s0 * 4)) / var_s7);
                if (var_s2_2 < 0) {
                    var_s2_2 = 0;
                } else if (var_s2_2 > 0x1869F) {
                    var_s2_2 = 0x1869F;
                }
                if (var_s2_2 != 0) {
                    temp_ret_263 = (int)igProperty_GetRecord(temp_v0_47, ATTACKZOKUSEI);
                    var_s1 = ((beDataObjInt *)temp_ret_263)->_data;
                    if (var_s1 != -1) {
                        temp_ret_264 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        if (temp_ret_264 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                            temp_ret_265 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_266 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_265));
                        }
                        temp_ret_267 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        temp_ret_268 = beDataBase_GetRecordInt(temp_ret_267, temp_v0_45, g_elementResistanceFields[var_s1]);
                        temp_v0_48 = temp_ret_268;
                        temp_ret_269 = (void **)(ObjectRef_Get_00406e50(&((beSystem *)self->_system)->_random));
                        temp_v0_49 = (void **)(temp_ret_269);
                        temp_v0_50 = ((DW4VC_96_0 *)(temp_v0_49))->vX() % 1000U;
                        if (temp_v0_48 < (int) temp_v0_50) {
                            var_s2_2 += (int) (var_s2_2 * (0x3E8 - temp_v0_48)) / 1000;
                        }
                    }
                }
            break; }
            case 4: {
                temp_a2_5 = (int)((int) temp_ret_245 % 1000);
                int sp48C;
                beNDMWGameRam_FindTechniqueRow(self, temp_v0_47, temp_a2_5, &sp48C);
                temp_ret_270 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                if (temp_ret_270 == 0) {
                    beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                    temp_ret_271 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_272 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_271));
                }
                temp_ret_273 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                temp_ret_274 = beDataBase_GetRecordInt(temp_ret_273, sp48C, HP);
                temp_v0_51 = (int)(0U - (unsigned int)temp_ret_274);
                if (temp_v0_51 != 0) {
                    temp_ret_275 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_275 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_276 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_277 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_276));
                    }
                    temp_ret_278 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_279 = beDataBase_GetRecordInt(temp_ret_278, sp48C, SKILL);
                    temp_ret_280 = (int)igProperty_GetRecordIntList(temp_v0_47, SKILL);
                    temp_ret_281 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_280)->_data));
                    temp_ret_282 = DataList_GetData_003e9090(temp_ret_281);
                    var_s0 = *(int *)(temp_ret_282 + (temp_ret_279 * 4));
                    temp_ret_283 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    if (temp_ret_283 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                        temp_ret_284 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_285 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_284));
                    }
                    temp_ret_286 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    temp_ret_287 = beDataBase_GetRecordInt(temp_ret_286, temp_v0_45, SEISHIN);
                    temp_ret_288 = (int)igProperty_GetRecord(temp_v0_47, KASHIKOSA);
                    int techDmg = (int)((int) ((var_s0 * 5) + ((temp_v0_51 * 0x14) + (((beDataObjInt *)temp_ret_288)->_data * 0xA))) / temp_ret_287);
                    if (techDmg < 0) {
                        techDmg = 0;
                    } else if (techDmg > 0x1869F) {
                        techDmg = 0x1869F;
                    }
                    var_s2_2 = techDmg;
                } else {
                    var_s2_2 = 0;
                }
                if (var_s2_2 != 0) {
                    temp_ret_289 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_289 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_290 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_291 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_290));
                    }
                    temp_ret_292 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_293 = (char *)(beDataBase_GetRecordString(temp_ret_292, sp48C, ZOKUSEI));
                    temp_v0_52 = (char *)(temp_ret_293);
                    temp_ret_294 = strcmp(temp_v0_52, &fire[0]);
                    if (temp_ret_294 == 0) {
                        var_s1 = 0;
                    } else {
                        temp_ret_295 = strcmp(temp_v0_52, &ice[0]);
                        if (temp_ret_295 == 0) {
                            var_s1 = 1;
                        } else {
                            temp_ret_296 = strcmp(temp_v0_52, &thunder[0]);
                            if (temp_ret_296 == 0) {
                                var_s1 = 2;
                            } else {
                                temp_ret_297 = strcmp(temp_v0_52, &dark[0]);
                                if (temp_ret_297 == 0) {
                                    var_s1 = 3;
                                } else {
                                    temp_ret_298 = strcmp(temp_v0_52, &poison[0]);
                                    if (temp_ret_298 == 0) {
                                        var_s1 = 4;
                                    } else {
                                        var_s1 = -1;
                                    }
                                }
                            }
                        }
                    }
                    if (var_s1 >= 0) {
                        temp_ret_299 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        if (temp_ret_299 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                            temp_ret_300 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_301 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_300));
                        }
                        temp_ret_302 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        temp_ret_303 = beDataBase_GetRecordInt(temp_ret_302, temp_v0_45, g_resistanceFields[var_s1]);
                        var_v0_5 = temp_ret_303;
                    } else {
                        var_v0_5 = 0;
                    }
                    var_s2_2 = (int)((int) (var_s2_2 * (0x3E8 - var_v0_5)) / 1000);
                }
            break; }
            }
            if (var_s2_2 < 0) {
                var_s2_2 = 0;
            } else if (var_s2_2 > 0x1869F) {
                var_s2_2 = 0x1869F;
            }
            var_s3_2 = 0;
            if (var_s2_2 != 0) {
                if (sp12C != 0) {
                    if (var_s0 < 0x3E9) {
                        var_s2_2 += (int)((int) (var_s2_2 * ((var_s0 / 20) + 0x1E)) / 100);
                    } else if (var_s0 < 0x7D1) {
                        var_s2_2 += (int)((int) (var_s2_2 * (((int) (var_s0 - 0x3E8) / 50) + 0x50)) / 100);
                    } else {
                        var_s2_2 += (int)((int) (var_s2_2 * (((int) (var_s0 - 0x7D0) / 100) + 0x64)) / 100);
                    }
                }
                if (var_s2_2 != 0) {
                    temp_ret_304 = (void **)(ObjectRef_Get_00406e50(&((beSystem *)self->_system)->_random));
                    temp_v0_53 = (void **)(temp_ret_304);
                    temp_s0_6 = ((DW4VC_96_0 *)(temp_v0_53))->vX() & 3;
                    temp_ret_305 = (void **)(ObjectRef_Get_00406e50(&((beSystem *)self->_system)->_random));
                    temp_v0_54 = (void **)(temp_ret_305);
                    temp_v0_55 = ((DW4VC_96_0 *)(temp_v0_54))->vX() % (unsigned int) (var_s2_2 * 0x19);
                    switch (temp_s0_6) {

                    case 0:
                        temp_v0_56 = temp_v0_55 + (var_s2_2 * 950);
                        var_s2_2 = (int)temp_v0_56 / 1000;
                        break;

                    case 1:
                        temp_v0_57 = temp_v0_55 + (var_s2_2 * 975);
                        var_s2_2 = (int)temp_v0_57 / 1000;
                        break;

                    case 2:
                        temp_v0_58 = temp_v0_55 + (var_s2_2 * 1000);
                        var_s2_2 = (int)temp_v0_58 / 1000;
                        break;

                    case 3:
                        temp_a0_6 = temp_v0_55 + (var_s2_2 * 1025);
                        var_s2_2 = (int)temp_a0_6 / 1000;
                        var_s3_2 = 1;
                        break;
                    }
                }
                if (var_s2_2 < 0) {
                    var_s2_2 = 0;
                } else if (var_s2_2 > 0x1869F) {
                    var_s2_2 = 0x1869F;
                }
                switch (temp_ret_245 / 10000) {
                default: {
                    temp_ret_306 = (int)igProperty_GetRecord(temp_v0_47, HPDRAIN);
                    temp_v0_59 = ((beDataObjInt *)temp_ret_306)->_data;
                    if (temp_v0_59 != 0) {
                        temp_ret_307 = beNDMWGameRam_ChangeHp(self, temp_v0_44, (int) (var_s2_2 * temp_v0_59) / 100, -1);
                    }
                    temp_ret_308 = (int)igProperty_GetRecord(temp_v0_47, MPDRAIN);
                    temp_v0_60 = ((beDataObjInt *)temp_ret_308)->_data;
                    if (temp_v0_60 != 0) {
                        beNDMWGameRam_ChangeMp(self, temp_v0_44, (int) (var_s2_2 * temp_v0_60) / 100);
                    }
                break; }
                case 4: break;
                }
            }
            beMessenger_ClearInt(self->_messenger);
            beMessenger_AppendInt(self->_messenger, var_s2_2);
            beMessenger_AppendInt(self->_messenger, var_s1);
            beMessenger_AppendInt(self->_messenger, var_s3_2);
            break;
        case 21:
            temp_ret_310 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_311 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_312 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_313 = ObjectList_GetAt_003e9260(temp_ret_312, temp_ret_310);
            temp_v0_61 = (void *)(temp_ret_313);
            switch (temp_ret_311 / 10000) {
            default: {
                temp_ret_314 = (int)igProperty_GetRecord(temp_v0_61, ATTACKZOKUSEI);
                var_s0_10 = ((beDataObjInt *)temp_ret_314)->_data;
            break; }
            case 4: {
                temp_a2_6 = (int)((int) temp_ret_311 % 10000);
                int sp488;
                beNDMWGameRam_FindTechniqueRow(self, temp_v0_61, temp_a2_6, &sp488);
                temp_ret_315 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                if (temp_ret_315 == 0) {
                    beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                    temp_ret_316 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_317 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_316));
                }
                temp_ret_318 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                temp_ret_319 = (char *)(beDataBase_GetRecordString(temp_ret_318, sp488, ZOKUSEI));
                temp_v0_62 = (char *)(temp_ret_319);
                temp_ret_320 = strcmp(temp_v0_62, &fire[0]);
                if (temp_ret_320 == 0) {
                    var_s0_10 = 0;
                } else {
                    temp_ret_321 = strcmp(temp_v0_62, &ice[0]);
                    if (temp_ret_321 == 0) {
                        var_s0_10 = 1;
                    } else {
                        temp_ret_322 = strcmp(temp_v0_62, &thunder[0]);
                        if (temp_ret_322 == 0) {
                            var_s0_10 = 2;
                        } else {
                            temp_ret_323 = strcmp(temp_v0_62, &dark[0]);
                            if (temp_ret_323 == 0) {
                                var_s0_10 = 3;
                            } else {
                                temp_ret_324 = strcmp(temp_v0_62, &poison[0]);
                                if (temp_ret_324 == 0) {
                                    var_s0_10 = 4;
                                } else {
                                    var_s0_10 = -1;
                                }
                            }
                        }
                    }
                }
            break; }
            }
            beMessenger_ClearInt(self->_messenger);
            beMessenger_AppendInt(self->_messenger, var_s0_10);
            break;
        case 13:
            int skband;
            void *skp;
            int sklv;
            int skcls;
            int skcnt;
            int skgrp;
            int skhard;
            short *skptr;
            temp_ret_325 = beMessenger_GetInt(self->_messenger, 0);
            temp_v0_63 = temp_ret_325;
            temp_ret_326 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_327 = beMessenger_GetInt(self->_messenger, 2);
            sp128 = beMessenger_GetInt(self->_messenger, 3);
            temp_ret_329 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_330 = ObjectList_GetAt_003e9260(temp_ret_329, temp_v0_63);
            skp = (void *)(temp_ret_330);
            temp_ret_331 = (int)igProperty_GetRecord(skp, LEVEL_2);
            sklv = ((beDataObjInt *)temp_ret_331)->_data;
            /* Ternary chain rather than if/else: only this form copies each next compare into the
             * beqz delay slot. */
            var_s8 = (sklv < 0x25) ? sklv * 0x1E
                   : (sklv < 0x6C) ? (sklv * 0x14) + 0x168
                   : (sklv < 0xE4) ? (sklv * 0xA) + 0x596
                   : (sklv * 8) + 0x75C;
            skcls = temp_ret_326 / 10000;
            if ((skcls != 9) && (skcls != 8) && (skcls != 4)) {
                temp_ret_332 = (int)igProperty_GetRecord(skp, WEAPONSKILLNO);
                var_s5_3 = ((beDataObjInt *)temp_ret_332)->_data;
                temp_ret_333 = (int)igProperty_GetRecordIntList(skp, SKILL);
                temp_ret_334 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_333)->_data));
                temp_ret_335 = DataList_GetData_003e9090(temp_ret_334);
                var_s7_2 = *(int *)(temp_ret_335 + (var_s5_3 * 4));
            } else {
                temp_a2_7 = (int)((int) temp_ret_326 % 10000);
                int sp484;
                beNDMWGameRam_FindTechniqueRow(self, skp, temp_a2_7, &sp484);
                temp_ret_336 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                if (temp_ret_336 == 0) {
                    beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                    temp_ret_337 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_338 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_337));
                }
                temp_ret_339 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                temp_ret_340 = beDataBase_GetRecordInt(temp_ret_339, sp484, SKILL);
                var_s5_3 = temp_ret_340;
                temp_ret_341 = (int)igProperty_GetRecordIntList(skp, SKILL);
                temp_ret_342 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_341)->_data));
                temp_ret_343 = DataList_GetData_003e9090(temp_ret_342);
                var_s7_2 = *(int *)(temp_ret_343 + (var_s5_3 * 4));
            }
            if (var_s7_2 < var_s8) {
                /* Same ternary form for the level band; the 0/2 pick below stays an if/else. */
                skgrp = (sklv < 0x25) ? 0 : (sklv < 0x6C) ? 1 : (sklv < 0xE4) ? 2 : 3;
                if (sp128 == 1) {
                    skhard = 2;
                } else {
                    skhard = 0;
                }
                skptr = (short *)(g_skillGainThresholds);
                /* `value <= *p` (not `*p >= value`) keeps the compare as slt at / bnez at. */
                for (skcnt = 0; skcnt < 0x15; skcnt++, skptr++) {
                    if (var_s7_2 <= *skptr) {
                        skband = skcnt;
                        break;
                    }
                }
                temp_s1_3 = g_skillGainTable[skgrp][skband][skhard];
                /* A switch with the default arm first, rather than a != chain, places the nop
                 * after the third beq. */
                switch (skcls) {
                default: {
                    temp_ret_344 = (int)igProperty_GetRecord(skp, DIGIMONNO_2);
                    temp_s0_8 = ((beDataObjInt *)temp_ret_344)->_data;
                    temp_ret_345 = (void *)(ObjectRef_Get_00406ee0(&self->_dBShinka));
                    if (temp_ret_345 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_3, shinka_2, 0, GETDATABASE_3);
                        temp_ret_346 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_347 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBShinka, (ObjectRefTarget *)temp_ret_346));
                    }
                    temp_ret_348 = (void *)(ObjectRef_Get_00406ee0(&self->_dBShinka));
                    temp_ret_349 = beDataBase_GetRecordInt(temp_ret_348, temp_s0_8, g_weaponGrowFields[var_s5_3]);
                    var_s0_11 = (int)((int) (temp_s1_3 * temp_ret_349 * 0x1F4) / 1000);
                break; }
                case 4: case 8: case 9:
                    var_s0_11 = temp_s1_3 * 0x64;
                    break;
                }
                temp_ret_350 = (void **)(ObjectRef_Get_00406e50(&((beSystem *)self->_system)->_random));
                temp_v0_65 = (void **)(temp_ret_350);
                temp_v0_66 = ((DW4VC_96_0 *)(temp_v0_65))->vX() % 100000U;
                if ((int) temp_v0_66 < var_s0_11) {
                    int skill_next = var_s7_2 + 1;
                    temp_ret_351 = (int)igProperty_GetRecordIntList(skp, SKILL);
                    temp_ret_352 = (void *)(PropertyRecord_GetValue_00406e40((int *)temp_ret_351));
                    temp_v0_67 = (void *)(temp_ret_352);
                    temp_v1_3 = ((igIntList *)temp_v0_67)->_count;
                    if ((temp_v1_3 != 0) && (var_s5_3 >= 0) && (var_s5_3 < temp_v1_3)) {
                        temp_ret_353 = DataList_GetData_003e9090(temp_v0_67);
                        *(int *)(temp_ret_353 + (var_s5_3 * 4)) = skill_next;
                    }
                    beNDMWGameRam_RecomputeStats(self, temp_v0_63, 1);
                    beNDMWGameRam_StoreSpecies(self, temp_v0_63);
                    temp_ret_356 = (int)igProperty_GetRecordString(skp, DIGIMONNAME_2);
                    temp_ret_357 = (char *)(ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_356)->_data));
                    temp_ret_358 = beMessenger_PrepareDelayedSelection(self->_messenger, &MODELCTRL_5[0], temp_ret_357, temp_v0_63);
                    beMessenger_AppendString(self->_messenger, &i_getitempnl01[0]);
                    beMessenger_AppendString(self->_messenger, &SQ_TECUP[0]);
                    beMessenger_AppendFloat(self->_messenger, 1.0f);
                    Vec3f_Copy(&sp358, &g_vec3Zero[0]);
                    beMessenger_AppendVec3(self->_messenger, &sp358);
                    beMessenger_AppendBool(self->_messenger, 0U);
                    beMessenger_AppendBool(self->_messenger, 1U);
                    temp_ret_359 = beMessenger_EnqueueSelected(self->_messenger, &SETEFFECT[0], 1);
                }
            }
            break;
        case 6:
            /* Block-local webs are declared in the order expup_idx, expup_player, expup_level,
             * expup_exp; their register ids fix the allocator push order. */
            int expup_idx;
            void *expup_player;
            int expup_level;
            int expup_exp;
            temp_ret_360 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_361 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_362 = (void *)(ObjectRef_Get_00407040(&self->_commonDataList));
            temp_ret_363 = (int)igProperty_GetRecord(temp_ret_362, NINZU_2);
            temp_s6 = ((beDataObjInt *)temp_ret_363)->_data;
            expup_idx = 0;
            sp124 = 0;
            do {
                temp_ret_364 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                temp_ret_365 = ObjectList_GetAt_003e9260(temp_ret_364, expup_idx);
                expup_player = (void *)(temp_ret_365);
                temp_ret_366 = (beDataObjBool *)(igProperty_GetRecordByte((int)expup_player, ISUSE_4));
                if (temp_ret_366->_data != 0) {
                    temp_ret_367 = (int)igProperty_GetRecord(expup_player, HP);
                    if (((beDataObjInt *)temp_ret_367)->_data != 0) {
                        temp_ret_368 = (int)igProperty_GetRecord(expup_player, LEVEL_2);
                        expup_level = ((beDataObjInt *)temp_ret_368)->_data;
                        if (expup_level != 0x3E7) {
                            temp_ret_369 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                            if (temp_ret_369 == 0) {
                                beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                                temp_ret_370 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                                temp_ret_371 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_370));
                            }
                            temp_ret_372 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                            temp_ret_373 = beDataBase_GetRecordInt(temp_ret_372, temp_ret_361, EXP);
                            var_s0_12 = temp_ret_373;
                            temp_ret_374 = (int)igProperty_GetRecord(expup_player, EXPRITSU);
                            temp_v0_69 = ((beDataObjInt *)temp_ret_374)->_data;
                            if (temp_v0_69 != 0) {
                                var_s0_12 = (int)((int) (var_s0_12 * (temp_v0_69 + 0x64)) / 100);
                            }
                            int split;  /* Declared here: a late register id lets the allocator push the receiver before the four hot loop webs. */
                            switch (temp_s6) {
                            case 1:  /* Case 1 shares the default body, which keeps a dead `li v0,1` compare. */
                            default:
                                split = (var_s0_12 * 100) / 2;
                                break;
                            case 2:
                                split = (var_s0_12 * 140) / 3;
                                break;
                            case 3:
                                split = (var_s0_12 * 160) / 4;
                                break;
                            case 4:
                                split = (var_s0_12 * 200) / 5;
                                break;
                            }
                            if (expup_idx == temp_ret_360) {
                                split /= 50;
                                sp124 = split;
                            } else {
                                split /= 100;
                            }
                            temp_ret_375 = (int)igProperty_GetRecord(expup_player, EXP);
                            /* The old value is read before the second record lookup (it lives
                             * across that call); the add is in place. */
                            expup_exp = ((beDataObjInt *)temp_ret_375)->_data;
                            expup_exp = expup_exp + split;
                            temp_ret_376 = (int)igProperty_GetRecord(expup_player, EXP);
                            ((beDataObjInt *)temp_ret_376)->_data = expup_exp;
                            bool leveled_up = false;
                            temp_ret_377 = (int)igProperty_GetRecord(expup_player, NEXTEXP);
                            if (((beDataObjInt *)temp_ret_377)->_data <= expup_exp) {
loop_449:
                                expup_level += 1;
                                temp_ret_378 = (int)igProperty_GetRecord(expup_player, LEVEL_2);
                                ((beDataObjInt *)temp_ret_378)->_data = expup_level;
                                beNDMWGameRam_RecomputeStats(self, expup_idx, 1);
                                beNDMWGameRam_StoreSpecies(self, expup_idx);
                                leveled_up = true;
                                if (expup_level != 0x3E7) {
                                    temp_ret_381 = (int)igProperty_GetRecord(expup_player, NEXTEXP);
                                    if (expup_exp >= ((beDataObjInt *)temp_ret_381)->_data) {
                                        goto loop_449;
                                    }
                                }
                            }
                            if (leveled_up) {
                                temp_ret_382 = (int)igProperty_GetRecord(expup_player, MHP);
                                temp_s0_10 = ((beDataObjInt *)temp_ret_382)->_data;
                                temp_ret_383 = (int)igProperty_GetRecord(expup_player, MMP);
                                temp_s5 = ((beDataObjInt *)temp_ret_383)->_data;
                                temp_ret_384 = (int)igProperty_GetRecordString(expup_player, DIGIMONNAME_2);
                                temp_ret_385 = (char *)(ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_384)->_data));
                                temp_ret_386 = beMessenger_PrepareDelayedSelection(self->_messenger, &MODELCTRL_5[0], temp_ret_385, expup_idx);
                                beMessenger_AppendString(self->_messenger, &i_getitempnl01[0]);
                                beMessenger_AppendString(self->_messenger, &SQ_LVUP[0]);
                                beMessenger_AppendFloat(self->_messenger, 1.0f);
                                Vec3f_Copy(&sp348, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(self->_messenger, &sp348);
                                beMessenger_AppendBool(self->_messenger, 0U);
                                beMessenger_AppendBool(self->_messenger, 1U);
                                temp_ret_387 = beMessenger_EnqueueSelected(self->_messenger, &SETEFFECT[0], 1);
                                temp_ret_388 = (int)igProperty_GetRecord(expup_player, HP);
                                ((beDataObjInt *)temp_ret_388)->_data = temp_s0_10;
                                temp_ret_389 = (int)igProperty_GetRecord(expup_player, MP);
                                ((beDataObjInt *)temp_ret_389)->_data = temp_s5;
                                temp_ret_390 = beMessenger_PrepareDelayedSelection(self->_messenger, NUMBERCTRL, &lvnm[0], expup_idx);
                                beMessenger_AppendInt(self->_messenger, expup_level);
                                temp_ret_391 = beMessenger_EnqueueSelected(self->_messenger, SETVALUE, 1);
                                temp_ret_392 = beMessenger_PrepareDelayedSelection(self->_messenger, METERCTRL, hpmt, expup_idx);
                                beMessenger_AppendFloat(self->_messenger, 100.0f);
                                temp_ret_393 = beMessenger_EnqueueSelected(self->_messenger, SETPERCENT, 1);
                                temp_ret_394 = beMessenger_PrepareDelayedSelection(self->_messenger, NUMBERCTRL, hpnm, expup_idx);
                                beMessenger_AppendInt(self->_messenger, temp_s0_10);
                                temp_ret_395 = beMessenger_EnqueueSelected(self->_messenger, SETVALUE, 1);
                                temp_ret_396 = beMessenger_PrepareDelayedSelection(self->_messenger, METERCTRL, mpmt, expup_idx);
                                beMessenger_AppendFloat(self->_messenger, 100.0f);
                                temp_ret_397 = beMessenger_EnqueueSelected(self->_messenger, SETPERCENT, 1);
                                temp_ret_398 = beMessenger_PrepareDelayedSelection(self->_messenger, NUMBERCTRL, mpnm, expup_idx);
                                beMessenger_AppendInt(self->_messenger, temp_s5);
                                temp_ret_399 = beMessenger_EnqueueSelected(self->_messenger, SETVALUE, 1);
                            }
                        }
                    }
                }
                expup_idx += 1;
            } while (expup_idx < 4);
            beMessenger_ClearInt(self->_messenger);
            beMessenger_AppendInt(self->_messenger, sp124);
            break;
        case 14: {
            temp_ret_400 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_401 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_402 = beMessenger_GetInt(self->_messenger, 2);
            temp_v0_72 = temp_ret_402;
            temp_ret_403 = beMessenger_GetInt(self->_messenger, 3);
            temp_v0_73 = temp_ret_403;
            temp_ret_404 = beMessenger_GetInt(self->_messenger, 4);
            temp_ret_405 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_406 = ObjectList_GetAt_003e9260(temp_ret_405, temp_ret_400);
            temp_ret_407 = (int)igProperty_GetRecord(temp_ret_406, MAHIRITSU);
            int stun_base = ((beDataObjInt *)temp_ret_407)->_data;
            temp_ret_408 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
            if (temp_ret_408 == 0) {
                beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                temp_ret_409 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                temp_ret_410 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_409));
            }
            temp_ret_411 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
            temp_ret_412 = beDataBase_GetRecordInt(temp_ret_411, temp_ret_401, &RES_STUN[0]);
            temp_v0_74 = temp_ret_412;
            temp_ret_413 = (void **)(ObjectRef_Get_00406e50(&((beSystem *)self->_system)->_random));
            temp_v0_75 = (void **)(temp_ret_413);
            temp_a0_7 = ((DW4VC_96_0 *)(temp_v0_75))->vX() % 100U;
            var_s1_3 = 0;
            temp_v1_6 = (stun_base + ((int) (temp_v0_73 * 0x32) / temp_v0_72) + 0x64) - temp_v0_74;
            var_v0_9 = temp_v1_6 / 2;
            if ((int) temp_a0_7 < var_v0_9) {
                var_s1_3 = (int)((int) ((0xC8 - temp_v0_74) * (((int) (temp_v0_73 * 0x1E) / temp_v0_72) + (stun_base * 3))) / 400);
            }
            beMessenger_ClearInt(self->_messenger);
            beMessenger_AppendInt(self->_messenger, var_s1_3);
            break; }
        case 15:
            temp_ret_414 = (char *)(beMessenger_GetString(self->_messenger, 1));
            temp_v0_76 = (char *)(temp_ret_414);
            { StringRef sp480(temp_v0_76 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_76));
            temp_ret_417 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_418 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_419 = beMessenger_GetInt(self->_messenger, 2);
            temp_v0_77 = temp_ret_419;
            temp_ret_420 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_421 = ObjectList_GetAt_003e9260(temp_ret_420, temp_ret_417);
            temp_v0_78 = (void *)(temp_ret_421);
            temp_ret_422 = strcmp(sp480.p, &TIME[0]);
            if (temp_ret_422 == 0) {
                int sp47C;
                sp47C = 0;
                temp_a2_8 = temp_v0_77 % 10000;
                var_s2_3 = 0;
                beNDMWGameRam_FindTechniqueRow(self, temp_v0_78, temp_a2_8, &sp47C);
                temp_ret_423 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                if (temp_ret_423 == 0) {
                    beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                    temp_ret_424 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_425 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_424));
                }
                temp_ret_426 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                temp_ret_427 = beDataBase_GetRecordInt(temp_ret_426, sp47C, SKILL);
                temp_ret_428 = (int)igProperty_GetRecordIntList(temp_v0_78, SKILL);
                temp_ret_429 = (void *)(ObjectRef_Get_00406ef0((int *)(temp_ret_428 + 0xC)));
                temp_ret_430 = DataList_GetData_003e9090(temp_ret_429);
                temp_s1_4 = ((int *)temp_ret_430)[temp_ret_427];
                temp_ret_431 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                if (temp_ret_431 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                    temp_ret_432 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_433 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_432));
                }
                temp_ret_434 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                temp_ret_435 = beDataBase_GetRecordInt(temp_ret_434, temp_ret_418, &RES_POISON[0]);
                temp_v0_79 = temp_ret_435;
                if (temp_s1_4 < 0x3E9) {
                    var_v1_7 = temp_s1_4 / 4;
                    var_s1_4 = (int)((int) ((var_v1_7 + 0x2EE) * (0x3E8 - temp_v0_79)) / 1000);
                } else if (temp_s1_4 < 0x7D1) {
                    var_s1_4 = (int)((int) ((((int) (temp_s1_4 - 0x3E8) / 5) + 0x3E8) * (0x3E8 - temp_v0_79)) / 1000);
                } else {
                    var_s1_4 = (int)((int) ((((int) (temp_s1_4 - 0x7D0) / 10) + 0x4B0) * (0x3E8 - temp_v0_79)) / 1000);
                }
                temp_ret_436 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                temp_v0_80 = (void **)(temp_ret_436);
                temp_v0_81 = ((DW4VC_96_0 *)(temp_v0_80))->vX() % 1000U;
                if ((int) temp_v0_81 < var_s1_4) {
                    var_s2_3 = 1;
                }
                if (var_s2_3 != 0) {
                    temp_ret_437 = (int)igProperty_GetRecord(temp_v0_78, KASHIKOSA);
                    temp_s0_12 = ((beDataObjInt *)temp_ret_437)->_data;
                    temp_ret_438 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_438 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_439 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_440 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_439));
                    }
                    temp_ret_441 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_442 = beDataBase_GetRecordInt(temp_ret_441, sp47C, &TIME[0]);
                    var_v1_8 = temp_s0_12 / 2;
                    var_s0_13 = temp_ret_442 + var_v1_8;
                } else {
                    var_s0_13 = 0;
                }
                if (var_s0_13 == 0) {
                    var_s0_13 = -1;
                }
                beMessenger_ClearInt(self->_messenger);
                beMessenger_AppendInt(self->_messenger, var_s0_13);
            } else {
                temp_a2_9 = temp_v0_77 % 10000;
                int sp478;
                beNDMWGameRam_FindTechniqueRow(self, temp_v0_78, temp_a2_9, &sp478);
                temp_ret_443 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                if (temp_ret_443 == 0) {
                    beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                    temp_ret_444 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_445 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_444));
                }
                temp_ret_446 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                var_s0_13 = -(beDataBase_GetRecordInt(temp_ret_446, sp478, HP) / 5);

                beMessenger_ClearInt(self->_messenger);
                beMessenger_AppendInt(self->_messenger, var_s0_13);
            }
            }
            break;
        case 16:
            temp_ret_449 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_450 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_451 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_452 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_453 = ObjectList_GetAt_003e9260(temp_ret_452, temp_ret_449);
            temp_v0_82 = (void *)(temp_ret_453);
            int sp474;
            sp474 = 0;
            temp_a2_10 = temp_ret_451 % 10000;
            var_s2_4 = 0;
            beNDMWGameRam_FindTechniqueRow(self, temp_v0_82, temp_a2_10, &sp474);
            temp_ret_454 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
            if (temp_ret_454 == 0) {
                beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                temp_ret_455 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                temp_ret_456 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_455));
            }
            temp_ret_457 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
            temp_ret_458 = beDataBase_GetRecordInt(temp_ret_457, sp474, SKILL);
            temp_ret_459 = (int)igProperty_GetRecordIntList(temp_v0_82, SKILL);
            temp_ret_460 = (void *)(ObjectRef_Get_00406ef0((int *)(temp_ret_459 + 0xC)));
            temp_ret_461 = DataList_GetData_003e9090(temp_ret_460);
            temp_s3_3 = ((int *)temp_ret_461)[temp_ret_458];
            temp_ret_462 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
            if (temp_ret_462 == 0) {
                beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                temp_ret_463 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                temp_ret_464 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_463));
            }
            temp_ret_465 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
            temp_ret_466 = beDataBase_GetRecordInt(temp_ret_465, temp_ret_450, SEISHIN);
            temp_v0_83 = temp_ret_466;
            if (temp_s3_3 < 0x3E9) {
                var_v1_9 = temp_s3_3 / 4;
                var_s1_5 = (int)((int) ((var_v1_9 + 0x226) * 0x64) / temp_v0_83);
            } else if (temp_s3_3 < 0x7D1) {
                var_s1_5 = (int)((int) ((((int) (temp_s3_3 - 0x3E8) / 5) + 0x320) * 0x64) / temp_v0_83);
            } else {
                var_s1_5 = (int)((int) ((((int) (temp_s3_3 - 0x7D0) / 10) + 0x3E8) * 0x64) / temp_v0_83);
            }
            temp_ret_467 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
            temp_v0_84 = (void **)(temp_ret_467);
            temp_v0_85 = ((DW4VC_96_0 *)(temp_v0_84))->vX() % 1000U;
            if ((int) temp_v0_85 < var_s1_5) {
                var_s2_4 = 1;
            }
            if (var_s2_4 != 0) {
                temp_ret_468 = (int)igProperty_GetRecord(temp_v0_82, KASHIKOSA);
                temp_s0_13 = ((beDataObjInt *)temp_ret_468)->_data;
                temp_ret_469 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                if (temp_ret_469 == 0) {
                    beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                    temp_ret_470 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_471 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_470));
                }
                temp_ret_472 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                temp_ret_473 = beDataBase_GetRecordInt(temp_ret_472, sp474, &TIME[0]);
                var_s0_14 = temp_ret_473 + temp_s0_13 / 2;
            } else {
                var_s0_14 = 0;
            }
            if (var_s0_14 == 0) {
                var_s0_14 = -1;
            }
            beMessenger_ClearInt(self->_messenger);
            beMessenger_AppendInt(self->_messenger, var_s0_14);
            break;
        case 17:
            temp_ret_474 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_475 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_476 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_477 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_478 = ObjectList_GetAt_003e9260(temp_ret_477, temp_ret_474);
            temp_v0_86 = (void *)(temp_ret_478);
            int sp470;
            sp470 = 0;
            temp_a2_11 = temp_ret_476 % 10000;
            var_s2_5 = 0;
            beNDMWGameRam_FindTechniqueRow(self, temp_v0_86, temp_a2_11, &sp470);
            temp_ret_479 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
            if (temp_ret_479 == 0) {
                beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                temp_ret_480 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                temp_ret_481 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_480));
            }
            temp_ret_482 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
            temp_ret_483 = beDataBase_GetRecordInt(temp_ret_482, sp470, SKILL);
            temp_ret_484 = (int)igProperty_GetRecordIntList(temp_v0_86, SKILL);
            temp_ret_485 = (void *)(ObjectRef_Get_00406ef0((int *)(temp_ret_484 + 0xC)));
            temp_ret_486 = DataList_GetData_003e9090(temp_ret_485);
            temp_s3_4 = ((int *)temp_ret_486)[temp_ret_483];
            temp_ret_487 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
            if (temp_ret_487 == 0) {
                beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                temp_ret_488 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                temp_ret_489 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_488));
            }
            temp_ret_490 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
            temp_ret_491 = beDataBase_GetRecordInt(temp_ret_490, temp_ret_475, SEISHIN);
            temp_v0_87 = temp_ret_491;
            if (temp_s3_4 < 0x3E9) {
                var_v1_11 = temp_s3_4 / 4;
                var_s1_6 = (int)((int) ((var_v1_11 + 0x226) * 0x64) / temp_v0_87);
            } else if (temp_s3_4 < 0x7D1) {
                var_s1_6 = (int)((int) ((((int) (temp_s3_4 - 0x3E8) / 5) + 0x320) * 0x64) / temp_v0_87);
            } else {
                var_s1_6 = (int)((int) ((((int) (temp_s3_4 - 0x7D0) / 10) + 0x3E8) * 0x64) / temp_v0_87);
            }
            temp_ret_492 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
            temp_v0_88 = (void **)(temp_ret_492);
            temp_v0_89 = ((DW4VC_96_0 *)(temp_v0_88))->vX() % 1000U;
            if ((int) temp_v0_89 < var_s1_6) {
                var_s2_5 = 1;
            }
            if (var_s2_5 != 0) {
                temp_ret_493 = (int)igProperty_GetRecord(temp_v0_86, KASHIKOSA);
                temp_s0_14 = ((beDataObjInt *)temp_ret_493)->_data;
                temp_ret_494 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                if (temp_ret_494 == 0) {
                    beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                    temp_ret_495 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_496 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_495));
                }
                temp_ret_497 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                temp_ret_498 = beDataBase_GetRecordInt(temp_ret_497, sp470, &TIME[0]);
                var_v1_12 = temp_s0_14 / 2;
                var_s0_15 = temp_ret_498 + var_v1_12;
            } else {
                var_s0_15 = 0;
            }
            if (var_s0_15 == 0) {
                var_s0_15 = -1;
            }
            beMessenger_ClearInt(self->_messenger);
            beMessenger_AppendInt(self->_messenger, var_s0_15);
            break;
        case 18:
            temp_ret_499 = (char *)(beMessenger_GetString(self->_messenger, 1));
            temp_v0_90 = (char *)(temp_ret_499);
            { StringRef sp46C(temp_v0_90 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_90));
            temp_ret_502 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_503 = beMessenger_GetInt(self->_messenger, 1);
            temp_v0_91 = temp_ret_503;
            temp_ret_504 = beMessenger_GetInt(self->_messenger, 2);
            temp_v0_92 = temp_ret_504;
            temp_ret_505 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_506 = ObjectList_GetAt_003e9260(temp_ret_505, temp_ret_502);
            temp_v0_93 = (void *)(temp_ret_506);
            temp_ret_507 = strcmp(sp46C.p, &TIME[0]);
            if (temp_ret_507 == 0) {
                int sp468;
                sp468 = 0;
                temp_a2_12 = temp_v0_92 % 10000;
                var_s2_6 = 0;
                beNDMWGameRam_FindTechniqueRow(self, temp_v0_93, temp_a2_12, &sp468);
                temp_ret_508 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                if (temp_ret_508 == 0) {
                    beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                    temp_ret_509 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_510 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_509));
                }
                temp_ret_511 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                temp_ret_512 = beDataBase_GetRecordInt(temp_ret_511, sp468, SKILL);
                temp_ret_513 = (int)igProperty_GetRecordIntList(temp_v0_93, SKILL);
                temp_ret_514 = (void *)(ObjectRef_Get_00406ef0((int *)(temp_ret_513 + 0xC)));
                temp_ret_515 = DataList_GetData_003e9090(temp_ret_514);
                temp_s1_5 = ((int *)temp_ret_515)[temp_ret_512];
                temp_ret_516 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                if (temp_ret_516 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                    temp_ret_517 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_518 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_517));
                }
                temp_ret_519 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                temp_ret_520 = beDataBase_GetRecordInt(temp_ret_519, temp_v0_91, SEISHIN);
                temp_v0_94 = temp_ret_520;
                if (temp_s1_5 < 0x3E9) {
                    var_v1_13 = temp_s1_5 / 4;
                    var_s1_7 = (int)((int) ((var_v1_13 + 0x226) * 0x64) / temp_v0_94);
                } else if (temp_s1_5 < 0x7D1) {
                    var_s1_7 = (int)((int) ((((int) (temp_s1_5 - 0x3E8) / 5) + 0x320) * 0x64) / temp_v0_94);
                } else {
                    var_s1_7 = (int)((int) ((((int) (temp_s1_5 - 0x7D0) / 10) + 0x3E8) * 0x64) / temp_v0_94);
                }
                temp_ret_521 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                temp_v0_95 = (void **)(temp_ret_521);
                temp_v0_96 = ((DW4VC_96_0 *)(temp_v0_95))->vX() % 1000U;
                if ((int) temp_v0_96 < var_s1_7) {
                    var_s2_6 = 1;
                }
                if (var_s2_6 != 0) {
                    temp_ret_522 = (int)igProperty_GetRecord(temp_v0_93, KASHIKOSA);
                    temp_s0_15 = ((beDataObjInt *)temp_ret_522)->_data;
                    temp_ret_523 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_523 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_524 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_525 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_524));
                    }
                    temp_ret_526 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_527 = beDataBase_GetRecordInt(temp_ret_526, sp468, &TIME[0]);
                    var_v1_14 = temp_s0_15 / 2;
                    var_s0_16 = temp_ret_527 + var_v1_14;
                } else {
                    var_s0_16 = 0;
                }
                if (var_s0_16 == 0) {
                    var_s0_16 = -1;
                }
                beMessenger_ClearInt(self->_messenger);
                beMessenger_AppendInt(self->_messenger, var_s0_16);
            } else {
                temp_ret_528 = strcmp(sp46C.p, SUBAYASA);
                if (temp_ret_528 == 0) {
                    temp_a2_13 = temp_v0_92 % 10000;
                    int sp464;
                    sp464 = 0;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_93, temp_a2_13, &sp464);
                    temp_ret_529 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_529 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_530 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_531 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_530));
                    }
                    temp_ret_532 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_533 = beDataBase_GetRecordInt(temp_ret_532, sp464, SKILL);
                    temp_ret_534 = (int)igProperty_GetRecordIntList(temp_v0_93, SKILL);
                    temp_ret_535 = (void *)(ObjectRef_Get_00406ef0((int *)(temp_ret_534 + 0xC)));
                    temp_ret_536 = DataList_GetData_003e9090(temp_ret_535);
                    temp_s1_6 = ((int *)temp_ret_536)[temp_ret_533];
                    temp_ret_537 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    if (temp_ret_537 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                        temp_ret_538 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_539 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_538));
                    }
                    temp_ret_540 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    temp_ret_541 = beDataBase_GetRecordInt(temp_ret_540, temp_v0_91, SUBAYASA);
                    temp_s0_16 = (int)((int) (-temp_ret_541 * 0x50) / 100);
                    temp_ret_542 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_542 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_543 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_544 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_543));
                    }
                    temp_ret_545 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_546 = beDataBase_GetRecordInt(temp_ret_545, sp464, SUBAYASA);
                    var_s1_8 = temp_ret_546 - ((int) temp_s1_6 / 20);
                    if (var_s1_8 < temp_s0_16) {
                        var_s1_8 = temp_s0_16;
                    }
                    beMessenger_ClearInt(self->_messenger);
                    beMessenger_AppendInt(self->_messenger, -var_s1_8);
                } else {
                    temp_ret_547 = strcmp(sp46C.p, CHIMEIRITSU);
                    if (temp_ret_547 == 0) {
                        temp_a2_14 = temp_v0_92 % 10000;
                        int sp460;
                        beNDMWGameRam_FindTechniqueRow(self, temp_v0_93, temp_a2_14, &sp460);
                        temp_ret_548 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                        if (temp_ret_548 == 0) {
                            beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                            temp_ret_549 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_550 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_549));
                        }
                        temp_ret_551 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                        temp_ret_552 = beDataBase_GetRecordInt(temp_ret_551, sp460, CHIMEIRITSU);
                        beMessenger_ClearInt(self->_messenger);
                        beMessenger_AppendInt(self->_messenger, -temp_ret_552);
                    } else {
                        temp_ret_553 = strcmp(sp46C.p, MAHIRITSU);
                        if (temp_ret_553 == 0) {
                            temp_a2_15 = temp_v0_92 % 10000;
                            int sp45C;
                            beNDMWGameRam_FindTechniqueRow(self, temp_v0_93, temp_a2_15, &sp45C);
                            temp_ret_554 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                            if (temp_ret_554 == 0) {
                                beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                                temp_ret_555 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                                temp_ret_556 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_555));
                            }
                            temp_ret_557 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                            temp_ret_558 = beDataBase_GetRecordInt(temp_ret_557, sp45C, &MHIRITSU[0]);
                            beMessenger_ClearInt(self->_messenger);
                            beMessenger_AppendInt(self->_messenger, -temp_ret_558);
                        } else {
                            temp_ret_559 = strcmp(sp46C.p, KAIHIRITSU);
                            if (temp_ret_559 == 0) {
                                temp_a2_16 = temp_v0_92 % 10000;
                                int sp458;
                                beNDMWGameRam_FindTechniqueRow(self, temp_v0_93, temp_a2_16, &sp458);
                                temp_ret_560 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                                if (temp_ret_560 == 0) {
                                    beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                                    temp_ret_561 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                                    temp_ret_562 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_561));
                                }
                                temp_ret_563 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                                temp_ret_564 = beDataBase_GetRecordInt(temp_ret_563, sp458, KAIHIRITSU);
                                beMessenger_ClearInt(self->_messenger);
                                beMessenger_AppendInt(self->_messenger, -temp_ret_564);
                            }
                        }
                    }
                }
            }
            }
            break;
        case 19:
            temp_ret_566 = (char *)(beMessenger_GetString(self->_messenger, 1));
            temp_v0_97 = (char *)(temp_ret_566);
            { StringRef sp454(temp_v0_97 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_97));
            temp_ret_569 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_570 = beMessenger_GetInt(self->_messenger, 1);
            temp_v0_98 = temp_ret_570;
            temp_ret_571 = beMessenger_GetInt(self->_messenger, 2);
            temp_v0_99 = temp_ret_571;
            temp_ret_572 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_573 = ObjectList_GetAt_003e9260(temp_ret_572, temp_ret_569);
            temp_v0_100 = (void *)(temp_ret_573);
            temp_ret_574 = strcmp(sp454.p, &TIME[0]);
            if (temp_ret_574 == 0) {
                int sp450;
                sp450 = 0;
                temp_a2_17 = temp_v0_99 % 10000;
                var_s2_7 = 0;
                beNDMWGameRam_FindTechniqueRow(self, temp_v0_100, temp_a2_17, &sp450);
                temp_ret_575 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                if (temp_ret_575 == 0) {
                    beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                    temp_ret_576 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_577 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_576));
                }
                temp_ret_578 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                temp_ret_579 = beDataBase_GetRecordInt(temp_ret_578, sp450, SKILL);
                temp_ret_580 = (int)igProperty_GetRecordIntList(temp_v0_100, SKILL);
                temp_ret_581 = (void *)(ObjectRef_Get_00406ef0((int *)(temp_ret_580 + 0xC)));
                temp_ret_582 = DataList_GetData_003e9090(temp_ret_581);
                temp_s3_5 = ((int *)temp_ret_582)[temp_ret_579];
                temp_ret_583 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                if (temp_ret_583 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                    temp_ret_584 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_585 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_584));
                }
                temp_ret_586 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                temp_ret_587 = beDataBase_GetRecordInt(temp_ret_586, temp_v0_98, SEISHIN);
                temp_v0_101 = temp_ret_587;
                if (temp_s3_5 < 0x3E9) {
                    var_v1_15 = temp_s3_5 / 4;
                    var_s0_17 = (int)((int) ((var_v1_15 + 0x226) * 0x64) / temp_v0_101);
                } else if (temp_s3_5 < 0x7D1) {
                    var_s0_17 = (int)((int) ((((int) (temp_s3_5 - 0x3E8) / 5) + 0x320) * 0x64) / temp_v0_101);
                } else {
                    var_s0_17 = (int)((int) ((((int) (temp_s3_5 - 0x7D0) / 10) + 0x3E8) * 0x64) / temp_v0_101);
                }
                temp_ret_588 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                temp_v0_102 = (void **)(temp_ret_588);
                temp_v0_103 = ((DW4VC_96_0 *)(temp_v0_102))->vX() % 1000U;
                if ((int) temp_v0_103 < var_s0_17) {
                    var_s2_7 = 1;
                }
                if (var_s2_7 != 0) {
                    temp_ret_589 = (int)igProperty_GetRecord(temp_v0_100, KASHIKOSA);
                    temp_s0_17 = ((beDataObjInt *)temp_ret_589)->_data;
                    temp_ret_590 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_590 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_591 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_592 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_591));
                    }
                    temp_ret_593 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_594 = beDataBase_GetRecordInt(temp_ret_593, sp450, &TIME[0]);
                    var_v1_16 = temp_s0_17 / 2;
                    var_s0_18 = temp_ret_594 + var_v1_16;
                } else {
                    var_s0_18 = 0;
                }
                if (var_s0_18 == 0) {
                    var_s0_18 = -1;
                }
                beMessenger_ClearInt(self->_messenger);
                beMessenger_AppendInt(self->_messenger, var_s0_18);
            } else {
                temp_ret_595 = strcmp(sp454.p, TSUYOSA);
                if (temp_ret_595 == 0) {
                    temp_a2_18 = temp_v0_99 % 10000;
                    int sp44C;
                    sp44C = 0;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_100, temp_a2_18, &sp44C);
                    temp_ret_596 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_596 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_597 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_598 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_597));
                    }
                    temp_ret_599 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_600 = beDataBase_GetRecordInt(temp_ret_599, sp44C, SKILL);
                    temp_ret_601 = (int)igProperty_GetRecordIntList(temp_v0_100, SKILL);
                    temp_ret_602 = (void *)(ObjectRef_Get_00406ef0((int *)(temp_ret_601 + 0xC)));
                    temp_ret_603 = DataList_GetData_003e9090(temp_ret_602);
                    temp_s1_7 = ((int *)temp_ret_603)[temp_ret_600];
                    temp_ret_604 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    if (temp_ret_604 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                        temp_ret_605 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_606 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_605));
                    }
                    temp_ret_607 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    temp_ret_608 = beDataBase_GetRecordInt(temp_ret_607, temp_v0_98, TSUYOSA);
                    temp_s0_18 = (int)((int) (-temp_ret_608 * 0x50) / 100);
                    temp_ret_609 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_609 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_610 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_611 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_610));
                    }
                    temp_ret_612 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_613 = beDataBase_GetRecordInt(temp_ret_612, sp44C, TSUYOSA);
                    var_s1_9 = temp_ret_613 - ((int) temp_s1_7 / 20);
                    if (var_s1_9 < temp_s0_18) {
                        var_s1_9 = temp_s0_18;
                    }
                    beMessenger_ClearInt(self->_messenger);
                    beMessenger_AppendInt(self->_messenger, -var_s1_9);
                } else {
                    temp_ret_614 = strcmp(sp454.p, MAMORI);
                    if (temp_ret_614 == 0) {
                        temp_a2_19 = temp_v0_99 % 10000;
                        int sp448;
                        sp448 = 0;
                        beNDMWGameRam_FindTechniqueRow(self, temp_v0_100, temp_a2_19, &sp448);
                        temp_ret_615 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                        if (temp_ret_615 == 0) {
                            beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                            temp_ret_616 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_617 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_616));
                        }
                        temp_ret_618 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                        temp_ret_619 = beDataBase_GetRecordInt(temp_ret_618, sp448, SKILL);
                        temp_ret_620 = (int)igProperty_GetRecordIntList(temp_v0_100, SKILL);
                        temp_ret_621 = (void *)(ObjectRef_Get_00406ef0((int *)(temp_ret_620 + 0xC)));
                        temp_ret_622 = DataList_GetData_003e9090(temp_ret_621);
                        temp_s1_8 = ((int *)temp_ret_622)[temp_ret_619];
                        temp_ret_623 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        if (temp_ret_623 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                            temp_ret_624 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_625 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_624));
                        }
                        temp_ret_626 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        temp_ret_627 = beDataBase_GetRecordInt(temp_ret_626, temp_v0_98, MAMORI);
                        temp_s0_19 = (int)((int) (-temp_ret_627 * 0x50) / 100);
                        temp_ret_628 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                        if (temp_ret_628 == 0) {
                            beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                            temp_ret_629 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_630 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_629));
                        }
                        temp_ret_631 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                        temp_ret_632 = beDataBase_GetRecordInt(temp_ret_631, sp448, MAMORI);
                        var_s1_10 = temp_ret_632 - ((int) temp_s1_8 / 20);
                        if (var_s1_10 < temp_s0_19) {
                            var_s1_10 = temp_s0_19;
                        }
                        beMessenger_ClearInt(self->_messenger);
                        beMessenger_AppendInt(self->_messenger, -var_s1_10);
                    }
                }
            }
            }
            break;
        case 0:
            temp_ret_634 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_635 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_636 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_637 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_638 = ObjectList_GetAt_003e9260(temp_ret_637, temp_ret_634);
            temp_v0_104 = (void *)(temp_ret_638);
            temp_s3_6 = temp_ret_636 % 10000;
            var_s5_7 = 0;
            temp_ret_639 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
            if (temp_ret_639 == 0) {
                beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                temp_ret_640 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                temp_ret_641 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_640));
            }
            temp_ret_642 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
            temp_ret_643 = beDataBase_GetRecordInt(temp_ret_642, temp_s3_6, &TYPE[0]);
            switch (temp_ret_643) {
            case 0:
                temp_ret_644 = (int)igProperty_GetRecord(temp_v0_104, BOUGYORITSU);
                temp_s0_20 = ((beDataObjInt *)temp_ret_644)->_data;
                temp_ret_645 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                temp_v0_105 = (void **)(temp_ret_645);
                temp_v0_106 = ((DW4VC_96_0 *)(temp_v0_105))->vX() % 100U;
                if (temp_s0_20 <= (int) temp_v0_106) {
                    temp_ret_646 = (int)igProperty_GetRecord(temp_v0_104, SUBAYASA);
                    temp_s1_9 = ((beDataObjInt *)temp_ret_646)->_data;
                    temp_ret_647 = (int)igProperty_GetRecord(temp_v0_104, KAIHIRITSU);
                    temp_s0_21 = ((beDataObjInt *)temp_ret_647)->_data;
                    temp_ret_648 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    if (temp_ret_648 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                        temp_ret_649 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_650 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_649));
                    }
                    temp_ret_651 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    temp_ret_652 = beDataBase_GetRecordInt(temp_ret_651, temp_ret_635, SUBAYASA);
                    temp_ret_653 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    if (temp_ret_653 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                        temp_ret_654 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_655 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_654));
                    }
                    temp_ret_656 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    temp_ret_657 = beDataBase_GetRecordInt(temp_ret_656, temp_s3_6, MEICHURITSU);
                    temp_ret_658 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                    temp_v0_107 = (void **)(temp_ret_658);
                    temp_a2_20 = ((DW4VC_96_0 *)(temp_v0_107))->vX() % 100U;
                    if ((int) temp_a2_20 < ((int) (temp_ret_657 * temp_ret_652) / (int) ((int) (temp_s1_9 * (temp_s0_21 + 0x64)) / 100))) {
                        var_s5_7 = 1;
                    }
                }
                break;
            default:
                var_s5_7 = 1;
                break;
            }
            beMessenger_ClearBool(self->_messenger);
            beMessenger_AppendBool(self->_messenger, var_s5_7);
            break;
        case 3:
            temp_ret_659 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_660 = beMessenger_GetInt(self->_messenger, 1);
            temp_v0_108 = temp_ret_660;
            temp_ret_661 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_662 = (void *)(beMessenger_GetObject(self->_messenger, 0));
            temp_v0_109 = (beNDMWMdlPEBaseInfoWork *)(temp_ret_662);
            temp_ret_663 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_664 = ObjectList_GetAt_003e9260(temp_ret_663, temp_ret_659);
            temp_v0_110 = (void *)(temp_ret_664);
            temp_s5_2 = temp_ret_661 % 10000;
            temp_ret_665 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
            if (temp_ret_665 == 0) {
                beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                temp_ret_666 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                temp_ret_667 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_666));
            }
            temp_ret_668 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
            temp_ret_669 = beDataBase_GetRecordInt(temp_ret_668, temp_s5_2, &TYPE[0]);
            temp_v0_111 = temp_ret_669;
            var_s3_4 = 0;
            var_s2_8 = -1;
            switch (temp_v0_111) {
            case 0:
                temp_ret_670 = (int)igProperty_GetRecord(temp_v0_110, MAMORI);
                temp_s3_7 = ((beDataObjInt *)temp_ret_670)->_data;
                temp_ret_671 = (void *)(ObjectRef_Get_00406ef0(&temp_v0_109->_downDataList));
                if (temp_ret_671 == 0) {
                    var_s1_11 = 0;
                } else {
                    temp_ret_672 = (void *)(ObjectRef_Get_00406ef0(&temp_v0_109->_downDataList));
                    temp_ret_673 = DataList_GetData_003e9090(temp_ret_672);
                    var_s1_11 = ((int *)temp_ret_673)[4];
                }
                temp_ret_674 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                if (temp_ret_674 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                    temp_ret_675 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_676 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_675));
                }
                temp_ret_677 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                temp_ret_678 = beDataBase_GetRecordInt(temp_ret_677, temp_v0_108, TSUYOSA);
                int e2p_diff_678; e2p_diff_678 = temp_ret_678 - var_s1_11;
                temp_ret_679 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_679 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_680 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_681 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_680));
                }
                temp_ret_682 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                temp_ret_683 = beDataBase_GetRecordInt(temp_ret_682, temp_s5_2, TSUYOSA);
                var_s3_4 = (int)((int) (e2p_diff_678 * temp_ret_683) / temp_s3_7);
                if (var_s3_4 < 0) {
                    var_s3_4 = 0;
                } else if (var_s3_4 > 0x1869F) {
                    var_s3_4 = 0x1869F;
                }
                temp_ret_684 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_684 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_685 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_686 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_685));
                }
                temp_ret_687 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                temp_ret_688 = (char *)(beDataBase_GetRecordString(temp_ret_687, temp_s5_2, ZOKUSEI));
                temp_v0_112 = (char *)(temp_ret_688);
                var_s1_12 = 0;
                temp_ret_689 = strcmp(temp_v0_112, &fire[0]);
                if (temp_ret_689 == 0) {
                    temp_ret_690 = (int)igProperty_GetRecord(temp_v0_110, HONOOTEIKO);
                    var_s1_12 = ((beDataObjInt *)temp_ret_690)->_data;
                    var_s2_8 = 0;
                } else {
                    temp_ret_691 = strcmp(temp_v0_112, &ice[0]);
                    if (temp_ret_691 == 0) {
                        temp_ret_692 = (int)igProperty_GetRecord(temp_v0_110, KOORITEIKO);
                        var_s1_12 = ((beDataObjInt *)temp_ret_692)->_data;
                        var_s2_8 = 1;
                    } else {
                        temp_ret_693 = strcmp(temp_v0_112, &thunder[0]);
                        if (temp_ret_693 == 0) {
                            temp_ret_694 = (int)igProperty_GetRecord(temp_v0_110, KAMINARITEIKO);
                            var_s1_12 = ((beDataObjInt *)temp_ret_694)->_data;
                            var_s2_8 = 2;
                        } else {
                            temp_ret_695 = strcmp(temp_v0_112, &dark[0]);
                            if (temp_ret_695 == 0) {
                                temp_ret_696 = (int)igProperty_GetRecord(temp_v0_110, YAMITEIKO);
                                var_s1_12 = ((beDataObjInt *)temp_ret_696)->_data;
                                var_s2_8 = 3;
                            }
                        }
                    }
                }
                if (var_s1_12 != 0) {
                    temp_ret_697 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                    temp_v0_113 = (void **)(temp_ret_697);
                    temp_a2_21 = ((DW4VC_96_0 *)(temp_v0_113))->vX() % 1000U;
                    if (((int) var_s1_12 / 5) <= (int) temp_a2_21) {
                        if ((int) var_s1_12 < 0x3E9) {
                            var_v0_13 = (int)((int) (var_s3_4 * (((int) (0x3E8 - var_s1_12) / 20) + 0x32)) / 100);
                        } else if ((int) var_s1_12 < 0x1389) {
                            var_v0_13 = (int)((int) (var_s3_4 * ((int) (0x1388 - var_s1_12) / 80)) / 100);
                        } else {
                            var_v0_13 = 0;
                        }
                        var_s3_4 += var_v0_13;
                    }
                }
                if (var_s3_4 != 0) {
                    temp_ret_698 = (void *)(ObjectRef_Get_00406ef0(&temp_v0_109->_downDataList));
                    if (temp_ret_698 == 0) {
                        var_s0_19 = 0;
                    } else {
                        temp_ret_699 = (void *)(ObjectRef_Get_00406ef0(&temp_v0_109->_downDataList));
                        temp_ret_700 = DataList_GetData_003e9090(temp_ret_699);
                        var_s0_19 = ((int *)temp_ret_700)[1];
                    }
                    temp_ret_701 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    if (temp_ret_701 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                        temp_ret_702 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_703 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_702));
                    }
                    temp_ret_704 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    temp_ret_705 = beDataBase_GetRecordInt(temp_ret_704, temp_v0_108, CHIMEIRITSU);
                    e2p_diff_705 = temp_ret_705 - var_s0_19;
                    temp_ret_706 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    if (temp_ret_706 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                        temp_ret_707 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_708 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_707));
                    }
                    temp_ret_709 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    temp_ret_710 = beDataBase_GetRecordInt(temp_ret_709, temp_s5_2, CHIMEIRITSU);
                    temp_v0_114 = temp_ret_710;
                    temp_ret_711 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                    temp_v0_115 = (void **)(temp_ret_711);
                    temp_a0_8 = ((DW4VC_96_0 *)(temp_v0_115))->vX() % 10000U;
                    if (((0x64 - e2p_diff_705) * (0x64 - temp_v0_114)) <= (int) temp_a0_8) {
                        var_v0_15 = (int)((int) (var_s3_4 * (temp_v0_114 / 2 + 0x5A)) / 100);
                        var_s3_4 += var_v0_15;
                    }
                }
                break;
            case 1:
                temp_ret_712 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_712 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_713 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_714 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_713));
                }
                temp_ret_715 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                temp_ret_716 = beDataBase_GetRecordInt(temp_ret_715, temp_s5_2, TSUYOSA);
                temp_v0_116 = temp_ret_716;
                if (temp_v0_116 != 0) {
                    temp_ret_717 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    if (temp_ret_717 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                        temp_ret_718 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_719 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_718));
                    }
                    temp_ret_720 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    temp_ret_721 = beDataBase_GetRecordInt(temp_ret_720, temp_v0_108, KASHIKOSA);
                    temp_ret_722 = (int)igProperty_GetRecord(temp_v0_110, SEISHIN);
                    var_s3_4 = (int)((int) (temp_ret_721 * temp_v0_116) / (int) ((beDataObjInt *)temp_ret_722)->_data);
                    if (var_s3_4 < 0) {
                        var_s3_4 = 0;
                    } else if (var_s3_4 > 0x1869F) {
                        var_s3_4 = 0x1869F;
                    }
                    var_s1_13 = 0;
                    temp_ret_723 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    if (temp_ret_723 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                        temp_ret_724 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_725 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_724));
                    }
                    temp_ret_726 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    temp_ret_727 = (char *)(beDataBase_GetRecordString(temp_ret_726, temp_s5_2, ZOKUSEI));
                    temp_v0_117 = (char *)(temp_ret_727);
                    temp_ret_728 = strcmp(temp_v0_117, &fire[0]);
                    if (temp_ret_728 == 0) {
                        temp_ret_729 = (int)igProperty_GetRecord(temp_v0_110, HONOOTEIKO);
                        var_s1_13 = ((beDataObjInt *)temp_ret_729)->_data;
                        var_s2_8 = 0;
                    } else {
                        temp_ret_730 = strcmp(temp_v0_117, &ice[0]);
                        if (temp_ret_730 == 0) {
                            temp_ret_731 = (int)igProperty_GetRecord(temp_v0_110, KOORITEIKO);
                            var_s1_13 = ((beDataObjInt *)temp_ret_731)->_data;
                            var_s2_8 = 1;
                        } else {
                            temp_ret_732 = strcmp(temp_v0_117, &thunder[0]);
                            if (temp_ret_732 == 0) {
                                temp_ret_733 = (int)igProperty_GetRecord(temp_v0_110, KAMINARITEIKO);
                                var_s1_13 = ((beDataObjInt *)temp_ret_733)->_data;
                                var_s2_8 = 2;
                            } else {
                                temp_ret_734 = strcmp(temp_v0_117, &dark[0]);
                                if (temp_ret_734 == 0) {
                                    temp_ret_735 = (int)igProperty_GetRecord(temp_v0_110, YAMITEIKO);
                                    var_s1_13 = ((beDataObjInt *)temp_ret_735)->_data;
                                    var_s2_8 = 3;
                                }
                            }
                        }
                    }
                    if (var_s1_13 != 0) {
                        if (var_s1_13 < 0x3E9) {
                            var_s3_4 = (int)((int) (var_s3_4 * (((int) (0x3E8 - var_s1_13) / 20) + 0x32)) / 100);
                        } else if (var_s1_13 < 0x1069) {
                            var_s3_4 = (int)((int) (var_s3_4 * ((int) (0x1388 - var_s1_13) / 80)) / 100);
                        } else {
                            var_s3_4 = var_s3_4 / 10;
                        }
                    }
                    if (var_s3_4 != 0) {
                        temp_ret_736 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        if (temp_ret_736 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                            temp_ret_737 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_738 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_737));
                        }
                        temp_ret_739 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        temp_ret_740 = beDataBase_GetRecordInt(temp_ret_739, temp_s5_2, CHIMEIRITSU);
                        temp_v0_118 = temp_ret_740;
                        if (temp_v0_118 != 0) {
                            if (var_s1_13 < 0x3E9) {
                                var_s0_20 = (0x3E8 - var_s1_13) + (temp_v0_118 * 0x64);
                            } else {
                                var_s0_20 = (temp_v0_118 * 0x64) - ((int) (var_s1_13 - 0x3E8) / 10);
                            }
                            temp_ret_741 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                            temp_v0_119 = (void **)(temp_ret_741);
                            temp_v0_120 = ((DW4VC_96_0 *)(temp_v0_119))->vX() % 10000U;
                            if (var_s0_20 <= (int) temp_v0_120) {
                                var_v0_15 = (int)((int) (var_s3_4 + (temp_v0_118 / 2 + 0x5A)) / 100);
                                var_s3_4 += var_v0_15;
                                break;
                            }
                        }
                    }
                }
                break;
            case 2:
                temp_ret_742 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_742 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_743 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_744 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_743));
                }
                temp_ret_745 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                temp_ret_746 = beDataBase_GetRecordInt(temp_ret_745, temp_s5_2, TSUYOSA);
                temp_ret_747 = (int)igProperty_GetRecord(temp_v0_110, MHP);
                var_s3_4 = (int)((int) (((beDataObjInt *)temp_ret_747)->_data * temp_ret_746) / 100);
                if (var_s3_4 < 0) {
                    var_s3_4 = 0;
                } else if (var_s3_4 > 0x1869F) {
                    var_s3_4 = 0x1869F;
                }
                var_s1_14 = 0;
                temp_ret_748 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_748 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_749 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_750 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_749));
                }
                temp_ret_751 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                temp_ret_752 = (char *)(beDataBase_GetRecordString(temp_ret_751, temp_s5_2, ZOKUSEI));
                temp_v0_121 = (char *)(temp_ret_752);
                temp_ret_753 = strcmp(temp_v0_121, &fire[0]);
                if (temp_ret_753 == 0) {
                    temp_ret_754 = (int)igProperty_GetRecord(temp_v0_110, HONOOTEIKO);
                    var_s1_14 = ((beDataObjInt *)temp_ret_754)->_data;
                    var_s2_8 = 0;
                } else {
                    temp_ret_755 = strcmp(temp_v0_121, &ice[0]);
                    if (temp_ret_755 == 0) {
                        temp_ret_756 = (int)igProperty_GetRecord(temp_v0_110, KOORITEIKO);
                        var_s1_14 = ((beDataObjInt *)temp_ret_756)->_data;
                        var_s2_8 = 1;
                    } else {
                        temp_ret_757 = strcmp(temp_v0_121, &thunder[0]);
                        if (temp_ret_757 == 0) {
                            temp_ret_758 = (int)igProperty_GetRecord(temp_v0_110, KAMINARITEIKO);
                            var_s1_14 = ((beDataObjInt *)temp_ret_758)->_data;
                            var_s2_8 = 2;
                        } else {
                            temp_ret_759 = strcmp(temp_v0_121, &dark[0]);
                            if (temp_ret_759 == 0) {
                                temp_ret_760 = (int)igProperty_GetRecord(temp_v0_110, YAMITEIKO);
                                var_s1_14 = ((beDataObjInt *)temp_ret_760)->_data;
                                var_s2_8 = 3;
                            }
                        }
                    }
                }
                if (var_s1_14 != 0) {
                    if (var_s1_14 < 0x3E9) {
                        var_v0_15 = (int)((int) (var_s3_4 * (((int) (0x3E8 - var_s1_14) / 20) + 0x32)) / 100);
                        var_s3_4 += var_v0_15;
                                break;
                    }
                    if (var_s1_14 < 0x1389) {
                        var_v0_15 = (int)((int) (var_s3_4 * ((int) (0x1388 - var_s1_14) / 80)) / 100);
                        var_s3_4 += var_v0_15;
                                break;
                    }
                }
                break;
            }
            if (var_s3_4 < 0) {
                var_s3_4 = 0;
            } else if (var_s3_4 > 0x1869F) {
                var_s3_4 = 0x1869F;
            }
            var_s1_15 = 0;
            if (var_s3_4 != 0) {
                temp_ret_761 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                temp_v0_122 = (void **)(temp_ret_761);
                int e2p_rng = ((DW4VC_96_0 *)(temp_v0_122))->vX() & 3;
                temp_ret_762 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                temp_v0_123 = (void **)(temp_ret_762);
                temp_v0_124 = ((DW4VC_96_0 *)(temp_v0_123))->vX() % (unsigned int) (var_s3_4 * 0x19);
                switch (e2p_rng) {

                    case 0:
                        temp_v0_125 = temp_v0_124 + (var_s3_4 * 950);
                        var_s3_4 = (int)temp_v0_125 / 1000;
                        break;

                    case 1:
                        temp_v0_126 = temp_v0_124 + (var_s3_4 * 975);
                        var_s3_4 = (int)temp_v0_126 / 1000;
                        break;

                    case 2:
                        temp_v0_127 = temp_v0_124 + (var_s3_4 * 1000);
                        var_s3_4 = (int)temp_v0_127 / 1000;
                        break;

                    case 3:
                        temp_a0_9 = temp_v0_124 + (var_s3_4 * 1025);
                        var_s3_4 = (int)temp_a0_9 / 1000;
                        var_s1_15 = 1;
                        break;
                    }
            }
            if (var_s3_4 < 0) {
                var_s3_4 = 0;
            } else if (var_s3_4 > 0x1869F) {
                var_s3_4 = 0x1869F;
            }
            beMessenger_ClearInt(self->_messenger);
            beMessenger_AppendInt(self->_messenger, var_s3_4);
            beMessenger_AppendInt(self->_messenger, var_s2_8);
            beMessenger_AppendInt(self->_messenger, var_s1_15);
            break;
        case 4:
            int var_s0_21;
            temp_ret_763 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_764 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_765 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_766 = beMessenger_GetInt(self->_messenger, 3);
            temp_ret_767 = (void *)(beMessenger_GetObject(self->_messenger, 0));
            temp_v0_128 = (void *)(temp_ret_767);
            var_s0_21 = 0;
            if (temp_ret_765 <= 0) {
                var_s0_21 = 3;
            } else {
                temp_ret_768 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                temp_ret_769 = ObjectList_GetAt_003e9260(temp_ret_768, temp_ret_763);
                temp_s5_3 = temp_ret_764 % 10000;
                temp_ret_770 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_770 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_771 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_772 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_771));
                }
                temp_ret_773 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                int temp_ret_774 = beDataBase_GetRecordInt(temp_ret_773, temp_s5_3, TSUYOSA);
                temp_ret_775 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_775 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_776 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_777 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_776));
                }
                temp_ret_778 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                temp_ret_779 = beDataBase_GetRecordInt(temp_ret_778, temp_s5_3, &SEQUENCE[0]);
                temp_v0_129 = temp_ret_779;
                temp_ret_780 = (int)igProperty_GetRecord(temp_ret_769, MHP);
                int e2p_rec_780; e2p_rec_780 = ((beDataObjInt *)temp_ret_780)->_data;
                switch (temp_v0_129) {
                case 0:
                    if (temp_ret_774 == 0) {
                        var_s0_21 = -1;
                    } else {
                        temp_lo = (int)((int) (temp_ret_766 * 0x64) / e2p_rec_780);
                        if (temp_lo < 0xA) {
                            var_s0_21 = 0;
                        } else if (temp_lo < 0x28) {
                            var_s0_21 = 1;
                        } else {
                            var_s0_21 = 2;
                        }
                    }
                    break;
                case 1:
                    var_s0_21 = -1;
                    break;
                case 2:
                    var_s0_21 = 0;
                    break;
                case 3:
                    var_s0_21 = 2;
                    break;
                case 4:
                    var_s0_21 = 1;
                    break;
                }
            }
            if (var_s0_21 == 2) {
                /* obj+0x28 is recomputed at each of the three uses (no common subexpression); the
                 * integer-sum form of the first use, and a plain byte-offset form for the others,
                 * keeps the compiler from hoisting it into a saved register. */
                temp_ret_781 = ObjectRef_Get_003e93b0((void *)((int)temp_v0_128 + 0x28));
                if (temp_ret_781 == 0) {
                    temp_ret_782 = igObject_GetAllocator(temp_v0_128);
                    temp_ret_786 = DW4Fresh::Assign((char *)temp_v0_128 + 0x28, temp_ret_782);
                }
                temp_ret_788 = ObjectRef_Get_003e92a0((char *)temp_v0_128 + 0x28);
                temp_ret_789 = DataList_FindProperty_003e9280(temp_ret_788, g_propertyNameField[0], &ONE_2[0]);
                temp_ret_790 = ObjectRef_Get_00406e00((int *)(temp_ret_789 + 0x14));
                temp_ret_791 = (void *)(ObjectRef_Get_00406df0((int *)(temp_ret_790 + 0xC8)));
                temp_v0_130 = (void *)(temp_ret_791);
                if (((DW4CountedListView *)temp_v0_130)->count != 0) {
                    temp_ret_792 = (void *)(DataList_GetWordAt_00406dd0((igDataList *)temp_v0_130, 1));
                    if (((DW4ByteFlag8 *)temp_ret_792)->value != 0) {
                        var_s0_21 = 1;
                    }
                }
            }
            beMessenger_ClearInt(self->_messenger);
            beMessenger_AppendInt(self->_messenger, var_s0_21);
            break;
        case 7: {
            temp_ret_793 = beMessenger_GetInt(self->_messenger, 0);
            sp120 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_795 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_796 = beMessenger_GetInt(self->_messenger, 3);
            temp_ret_797 = beMessenger_GetInt(self->_messenger, 4);
            temp_v0_131 = temp_ret_797;
            temp_ret_798 = (void *)(beMessenger_GetObject(self->_messenger, 0));
            temp_v0_132 = (beNDMWMdlPEBaseInfoWork *)(temp_ret_798);
            temp_ret_799 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_800 = ObjectList_GetAt_003e9260(temp_ret_799, temp_ret_793);
            temp_v0_133 = (void *)(temp_ret_800);
            temp_s6_2 = temp_ret_795 % 10000;
            temp_ret_801 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
            if (temp_ret_801 == 0) {
                beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                temp_ret_802 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                temp_ret_803 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_802));
            }
            temp_ret_804 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
            temp_ret_805 = beDataBase_GetRecordInt(temp_ret_804, temp_s6_2, &TYPE[0]);
            temp_v0_134 = temp_ret_805;
            var_s8_2 = 0;
            var_s1_16 = 0;
            var_s0_22 = 0;
            switch (temp_v0_134) {
            case 0:
                switch (temp_v0_131) { case 1: case 2: {
                    temp_ret_806 = (void *)(ObjectRef_Get_00406ef0(&temp_v0_132->_downDataList));
                    if (temp_ret_806 == 0) {
                        var_s0_23 = 0;
                    } else {
                        temp_ret_807 = (void *)(ObjectRef_Get_00406ef0(&temp_v0_132->_downDataList));
                        temp_ret_808 = DataList_GetData_003e9090(temp_ret_807);
                        var_s0_23 = ((int *)temp_ret_808)[2];
                    }
                    temp_ret_809 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    if (temp_ret_809 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                        temp_ret_810 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_811 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_810));
                    }
                    temp_ret_812 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    temp_ret_813 = beDataBase_GetRecordInt(temp_ret_812, sp120, MAHIRITSU);
                    var_s8_2 = temp_ret_813 - var_s0_23;
                    var_s0_22 = 1;
                } }
                break;
            case 1:
                temp_ret_814 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_814 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_815 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_816 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_815));
                }
                temp_ret_817 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                var_s1_16 = beDataBase_GetRecordInt(temp_ret_817, temp_s6_2, MAHIRITSU);
                if (var_s1_16 > 0) {
                    var_s0_22 = 1;
                }
                break;
            case 2:
                switch (temp_v0_131) { case 1: case 2: {
                    var_s0_22 = 1;
                } }
                break;
            }
            var_s2_9 = 0;
            if (var_s0_22) {
                temp_ret_819 = (int)igProperty_GetRecord(temp_v0_133, MHP);
                temp_s3_8 = ((beDataObjInt *)temp_ret_819)->_data;
                temp_ret_820 = (int)igProperty_GetRecord(temp_v0_133, MAHITEIKOU);
                temp_s0_23 = ((beDataObjInt *)temp_ret_820)->_data;
                temp_ret_821 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                temp_v0_135 = (void **)(temp_ret_821);
                temp_a2_22 = ((DW4VC_96_0 *)(temp_v0_135))->vX() % 100U;
                chance_sum = var_s1_16 + var_s8_2;
                int temp_lo_2 = (int)((int) (temp_ret_796 * 0x32) / temp_s3_8);
                temp_v1_7 = temp_s0_23 + (temp_lo_2 + 0x64 + chance_sum);
                var_v0_18 = temp_v1_7 / 2;
                if ((int) temp_a2_22 < var_v0_18) {
                    temp_v0_136 = temp_s0_23 + (temp_lo_2 + 0x1E + chance_sum);
                    var_s2_9 = temp_v0_136 / 4;
                }
                if (var_s2_9 == 0) {
                    var_s2_9 = -1;
                }
            }
            beMessenger_ClearInt(self->_messenger);
            beMessenger_AppendInt(self->_messenger, var_s2_9);
            break; }
        case 8:
            temp_ret_822 = (char *)(beMessenger_GetString(self->_messenger, 1));
            temp_v0_137 = (char *)(temp_ret_822);
            { StringRef sp444((char *)(temp_v0_137 == 0 ? (char *)0 : (char *)StringPool_Intern((void *)StringPool_GetInstance(), temp_v0_137)));
            temp_ret_825 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_826 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_827 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_828 = ObjectList_GetAt_003e9260(temp_ret_827, temp_ret_825);
            temp_v0_138 = (void *)(temp_ret_828);
            temp_s3_9 = temp_ret_826 % 10000;
            temp_ret_829 = strcmp(sp444.p, &TIME[0]);
            if (temp_ret_829 == 0) {
                var_s2_10 = 0;
                temp_ret_830 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_830 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_831 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_832 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_831));
                }
                temp_ret_833 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                temp_ret_834 = (char *)(beDataBase_GetRecordString(temp_ret_833, temp_s3_9, &KOUKA[0]));
                temp_ret_835 = strcmp(temp_ret_834, &doku[0]);
                if (temp_ret_835 == 0) {
                    temp_ret_836 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    if (temp_ret_836 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                        temp_ret_837 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_838 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_837));
                    }
                    temp_ret_839 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    int temp_ret_840 = beDataBase_GetRecordInt(temp_ret_839, temp_s3_9, &KOUKARANK[0]);
                    temp_ret_841 = (int)igProperty_GetRecord(temp_v0_138, DOKUTEIKOU);
                    int temp_s0_24 = ((beDataObjInt *)temp_ret_841)->_data;
                    temp_ret_842 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                    temp_v0_139 = (void **)(temp_ret_842);
                    temp_v1_8 = ((DW4VC_96_0 *)(temp_v0_139))->vX() % 100U;
                    if ((int) temp_v1_8 < (temp_s0_24 + ((temp_ret_840 * 0xF) + 0x1E))) {
                        temp_ret_843 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        if (temp_ret_843 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                            temp_ret_844 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_845 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_844));
                        }
                        temp_ret_846 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        temp_ret_847 = beDataBase_GetRecordInt(temp_ret_846, temp_s3_9, &KOUKATIME[0]);
                        var_s2_10 = temp_s0_24 / 2 + temp_ret_847;
                    }
                    if (var_s2_10 == 0) {
                        var_s2_10 = -1;
                    }
                }
                beMessenger_ClearInt(self->_messenger);
                beMessenger_AppendInt(self->_messenger, var_s2_10);
            } else {
                temp_ret_848 = strcmp(sp444.p, &DAMAGE[0]);
                if (temp_ret_848 == 0) {
                    temp_ret_849 = (int)igProperty_GetRecord(temp_v0_138, MHP);
                    temp_s0_25 = ((beDataObjInt *)temp_ret_849)->_data;
                    temp_ret_850 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    if (temp_ret_850 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                        temp_ret_851 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_852 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_851));
                    }
                    temp_ret_853 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    temp_ret_854 = beDataBase_GetRecordInt(temp_ret_853, temp_s3_9, &KOUKARANK[0]);
                    beMessenger_ClearInt(self->_messenger);
                    beMessenger_AppendInt(self->_messenger, (int) (temp_s0_25 * temp_ret_854) / 100);
                } else {
                    temp_ret_855 = strcmp(sp444.p, &GEDOKU[0]);
                    if (temp_ret_855 == 0) {
                        temp_ret_856 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        if (temp_ret_856 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                            temp_ret_857 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_858 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_857));
                        }
                        temp_ret_859 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        temp_ret_860 = beDataBase_GetRecordInt(temp_ret_859, temp_s3_9, &GEDOKU[0]);
                        beMessenger_ClearInt(self->_messenger);
                        beMessenger_AppendInt(self->_messenger, temp_ret_860);
                    }
                }
            }
            }
            break;
        case 9: {
            temp_ret_862 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_863 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_864 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_865 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            int temp_ret_866 = ObjectList_GetAt_003e9260(temp_ret_865, temp_ret_862);
            int temp_s2_2 = temp_ret_864 % 10000;
            temp_ret_867 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
            if (temp_ret_867 == 0) {
                beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                temp_ret_868 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                temp_ret_869 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_868));
            }
            temp_ret_870 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
            temp_ret_871 = (char *)(beDataBase_GetRecordString(temp_ret_870, temp_s2_2, &KOUKA[0]));
            int var_s1_17 = 0;
            temp_ret_872 = strcmp(temp_ret_871, &sleep[0]);
            if (temp_ret_872 == 0) {
                temp_ret_873 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_873 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_874 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_875 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_874));
                }
                temp_ret_876 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                temp_ret_877 = beDataBase_GetRecordInt(temp_ret_876, temp_s2_2, &KOUKARANK[0]);
                temp_ret_878 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                if (temp_ret_878 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                    temp_ret_879 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_880 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_879));
                }
                temp_ret_881 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                temp_ret_882 = beDataBase_GetRecordInt(temp_ret_881, temp_ret_863, KASHIKOSA);
                temp_ret_883 = (int)igProperty_GetRecord(temp_ret_866, SEISHIN);
                temp_s3_10 = ((beDataObjInt *)temp_ret_883)->_data;
                temp_ret_884 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                temp_v0_140 = (void **)(temp_ret_884);
                temp_a2_23 = ((DW4VC_96_0 *)(temp_v0_140))->vX() % 10000U;
                temp_s0_26 = (((int) (temp_ret_882 * 3) / (int) temp_s3_10) + 0x64) - ((int) temp_s3_10 / 40);
                int hit_base = temp_ret_877 * 5;
                if ((int) temp_a2_23 < (hit_base * temp_s0_26)) {
                    temp_ret_885 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    if (temp_ret_885 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                        temp_ret_886 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_887 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_886));
                    }
                    temp_ret_888 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    temp_ret_889 = beDataBase_GetRecordInt(temp_ret_888, temp_s2_2, &KOUKATIME[0]);
                    var_s1_17 = (int)((int) (temp_ret_889 * temp_s0_26) / 100);
                }
                if (var_s1_17 == 0) {
                    var_s1_17 = -1;
                }
            }
            beMessenger_ClearInt(self->_messenger);
            beMessenger_AppendInt(self->_messenger, var_s1_17);
            break; }
        case 10: {
            temp_ret_890 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_891 = beMessenger_GetInt(self->_messenger, 1);
            temp_v0_141 = temp_ret_891;
            temp_ret_892 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_893 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_894 = ObjectList_GetAt_003e9260(temp_ret_893, temp_ret_890);
            temp_v0_142 = (void *)(temp_ret_894);
            temp_s3_11 = temp_ret_892 % 10000;
            temp_ret_895 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
            if (temp_ret_895 == 0) {
                beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                temp_ret_896 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                temp_ret_897 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_896));
            }
            temp_ret_898 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
            temp_ret_899 = (char *)(beDataBase_GetRecordString(temp_ret_898, temp_s3_11, &KOUKA[0]));
            var_s2_11 = 0;
            temp_ret_900 = strcmp(temp_ret_899, &ashidome[0]);
            if (temp_ret_900 == 0) {
                temp_ret_901 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_901 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_902 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_903 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_902));
                }
                temp_ret_904 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                temp_ret_905 = beDataBase_GetRecordInt(temp_ret_904, temp_s3_11, &KOUKARANK[0]);
                temp_ret_906 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_906 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_907 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_908 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_907));
                }
                temp_ret_909 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                temp_ret_910 = beDataBase_GetRecordInt(temp_ret_909, temp_s3_11, &TYPE[0]);
                temp_v0_143 = temp_ret_910;
                sp110 = 1;
                if (temp_v0_143 != 2) {
                    temp_ret_911 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    if (temp_ret_911 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                        temp_ret_912 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_913 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_912));
                    }
                    temp_ret_914 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    temp_ret_915 = beDataBase_GetRecordInt(temp_ret_914, temp_v0_141, KASHIKOSA);
                    temp_ret_916 = (int)igProperty_GetRecord(temp_v0_142, SEISHIN);
                    unsigned int temp_s0_27 = ((beDataObjInt *)temp_ret_916)->_data;
                    temp_ret_917 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                    temp_v0_144 = (void **)(temp_ret_917);
                    temp_a2_24 = ((DW4VC_96_0 *)(temp_v0_144))->vX() % 10000U;
                    if ((temp_ret_905 * 5 * ((((int) (temp_ret_915 * 3) / (int) temp_s0_27) + 0x64) - ((int) temp_s0_27 / 40))) <= (int) temp_a2_24) {
                        sp110 = 0;
                    }
                }
                if (sp110) {
                    if (temp_v0_143 == 2) {
                        temp_ret_918 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        if (temp_ret_918 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                            temp_ret_919 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_920 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_919));
                        }
                        temp_ret_921 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        temp_ret_922 = beDataBase_GetRecordInt(temp_ret_921, temp_s3_11, &KOUKATIME[0]);
                        var_s2_11 = temp_ret_922;
                    } else {
                        temp_ret_923 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        if (temp_ret_923 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                            temp_ret_924 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_925 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_924));
                        }
                        temp_ret_926 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        temp_ret_927 = beDataBase_GetRecordInt(temp_ret_926, temp_s3_11, &KOUKATIME[0]);
                        temp_ret_928 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        if (temp_ret_928 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                            temp_ret_929 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_930 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_929));
                        }
                        temp_ret_931 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        temp_ret_932 = beDataBase_GetRecordInt(temp_ret_931, temp_v0_141, KASHIKOSA);
                        temp_ret_933 = (int)igProperty_GetRecord(temp_v0_142, SEISHIN);
                        temp_v0_145 = (void *)(temp_ret_933);
                        var_s2_11 = (int)((int) (temp_ret_927 * ((((int) (temp_ret_932 * 3) / (int) ((beDataObjInt *)temp_v0_145)->_data) + 0x64) - ((int) ((beDataObjInt *)temp_v0_145)->_data / 40))) / 100);
                    }
                }
                if (var_s2_11 == 0) {
                    var_s2_11 = -1;
                }
            }
            beMessenger_ClearInt(self->_messenger);
            beMessenger_AppendInt(self->_messenger, var_s2_11);
            break; }
        case 11: {
            temp_ret_934 = (char *)(beMessenger_GetString(self->_messenger, 1));
            temp_v0_146 = (char *)(temp_ret_934);
            if (temp_v0_146 == 0) {
                var_v0_20 = (char *)(0);
            } else {
                var_v0_20 = (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_146);
            }
            { StringRef sp440((char *)(var_v0_20));
            temp_ret_937 = beMessenger_GetInt(self->_messenger, 0);
            temp_v0_147 = temp_ret_937;
            temp_ret_938 = beMessenger_GetInt(self->_messenger, 1);
            temp_v0_148 = temp_ret_938;
            temp_ret_939 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_940 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_941 = ObjectList_GetAt_003e9260(temp_ret_940, temp_v0_147);
            temp_v0_149 = (void *)(temp_ret_941);
            temp_s2_3 = temp_ret_939 % 10000;
            temp_ret_942 = strcmp(sp440.p, &TIME[0]);
            if (temp_ret_942 == 0) {
                temp_ret_943 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_943 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_944 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_945 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_944));
                }
                temp_ret_946 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                temp_ret_947 = (char *)(beDataBase_GetRecordString(temp_ret_946, temp_s2_3, &KOUKA[0]));
                var_s1_18 = 0;
                temp_ret_948 = strcmp(temp_ret_947, &freeze[0]);
                if (temp_ret_948 == 0) {
                    temp_ret_949 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    if (temp_ret_949 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                        temp_ret_950 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_951 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_950));
                    }
                    temp_ret_952 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    temp_ret_953 = beDataBase_GetRecordInt(temp_ret_952, temp_s2_3, &KOUKARANK[0]);
                    temp_ret_954 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    if (temp_ret_954 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                        temp_ret_955 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_956 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_955));
                    }
                    temp_ret_957 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    temp_ret_958 = beDataBase_GetRecordInt(temp_ret_957, temp_v0_148, KASHIKOSA);
                    temp_ret_959 = (int)igProperty_GetRecord(temp_v0_149, SEISHIN);
                    temp_s3_12 = ((beDataObjInt *)temp_ret_959)->_data;
                    temp_ret_960 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                    temp_v0_150 = (void **)(temp_ret_960);
                    temp_a4_2 = ((DW4VC_96_0 *)(temp_v0_150))->vX() % 10000U;
                    temp_s0_28 = (((int) (temp_ret_958 * 3) / (int) temp_s3_12) + 0x64) - ((int) temp_s3_12 / 40);
                    int rec_scaled = (int) (temp_ret_953 * 0xA0) / 100;
                    if ((int) temp_a4_2 < (rec_scaled * temp_s0_28)) {
                        temp_ret_961 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        if (temp_ret_961 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                            temp_ret_962 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_963 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_962));
                        }
                        temp_ret_964 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        temp_ret_965 = beDataBase_GetRecordInt(temp_ret_964, temp_s2_3, &KOUKATIME[0]);
                        var_s1_18 = (int)((int) (temp_ret_965 * temp_s0_28) / 100);
                    }
                    if (var_s1_18 == 0) {
                        var_s1_18 = -1;
                    }
                }
                beMessenger_ClearInt(self->_messenger);
                beMessenger_AppendInt(self->_messenger, var_s1_18);
            } else {
                temp_ret_966 = strcmp(sp440.p, SUBAYASA);
                if (temp_ret_966 == 0) {
                    temp_ret_967 = (int)igProperty_GetRecordIntList(temp_v0_149, DOWNDATA);
                    temp_ret_968 = (void *)(PropertyRecord_GetValue_00406e40((int *)temp_ret_967));
                    temp_v0_151 = (void *)(temp_ret_968);
                    temp_v1_9 = ((igIntList *)temp_v0_151)->_count;
                    if ((temp_v1_9 != 0) && (0 < temp_v1_9)) {
                        temp_s1_10 = DAT_004cf5d8[0];
                        temp_ret_969 = DataList_GetData_003e9090(temp_v0_151);
                        *(int *)temp_ret_969 = temp_s1_10;
                    }
                    beNDMWGameRam_RecomputeStats(self, temp_v0_147, 1);
                    temp_ret_971 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    if (temp_ret_971 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                        temp_ret_972 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_973 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_972));
                    }
                    temp_ret_974 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    temp_ret_975 = beDataBase_GetRecordInt(temp_ret_974, temp_s2_3, &KOUKARANK[0]);
                    temp_ret_976 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    if (temp_ret_976 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                        temp_ret_977 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_978 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_977));
                    }
                    temp_ret_979 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    temp_ret_980 = beDataBase_GetRecordInt(temp_ret_979, temp_v0_148, KASHIKOSA);
                    temp_ret_981 = (int)igProperty_GetRecord(temp_v0_149, SEISHIN);
                    temp_v0_152 = (void *)(temp_ret_981);
                    var_s1_19 = (temp_ret_975 + ((int) ((int) (temp_ret_980 * 0x96) / (int) ((beDataObjInt *)temp_v0_152)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_152)->_data / 80);
                    if (var_s1_19 < 0x14) {
                        var_s1_19 = 0x14;
                    }
                    if (var_s1_19 > 0x50) {
                        var_s1_19 = 0x50;
                    }
                    temp_ret_982 = (int)igProperty_GetRecord(temp_v0_149, SUBAYASA);
                    int temp_s0_29 = ((beDataObjInt *)temp_ret_982)->_data;
                    beMessenger_ClearInt(self->_messenger);
                    beMessenger_AppendInt(self->_messenger, (int) (temp_s0_29 * var_s1_19) / 100);
                } else {
                    temp_ret_983 = strcmp(sp440.p, MEICHURITSU);
                    if (temp_ret_983 == 0) {
                        temp_ret_984 = (int)igProperty_GetRecordIntList(temp_v0_149, DOWNDATA);
                        temp_ret_985 = (void *)(PropertyRecord_GetValue_00406e40((int *)temp_ret_984));
                        temp_v0_153 = (void *)(temp_ret_985);
                        temp_v1_10 = ((igIntList *)temp_v0_153)->_count;
                        if ((temp_v1_10 != 0) && (temp_v1_10 > 1)) {
                            temp_s1_11 = DAT_004cf5e0[0];
                            temp_ret_986 = DataList_GetData_003e9090(temp_v0_153);
                            ((int *)temp_ret_986)[1] = temp_s1_11;
                        }
                        beNDMWGameRam_RecomputeStats(self, temp_v0_147, 1);
                        temp_ret_988 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        if (temp_ret_988 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                            temp_ret_989 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_990 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_989));
                        }
                        temp_ret_991 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        temp_ret_992 = beDataBase_GetRecordInt(temp_ret_991, temp_s2_3, &KOUKARANK[0]);
                        temp_ret_993 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        if (temp_ret_993 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                            temp_ret_994 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_995 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_994));
                        }
                        temp_ret_996 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        temp_ret_997 = beDataBase_GetRecordInt(temp_ret_996, temp_v0_148, KASHIKOSA);
                        temp_ret_998 = (int)igProperty_GetRecord(temp_v0_149, SEISHIN);
                        temp_v0_154 = (void *)(temp_ret_998);
                        var_s1_20 = (temp_ret_992 + ((int) ((int) (temp_ret_997 * 0x96) / (int) ((beDataObjInt *)temp_v0_154)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_154)->_data / 80);
                        if (var_s1_20 < 0x14) {
                            var_s1_20 = 0x14;
                        }
                        if (var_s1_20 > 0x50) {
                            var_s1_20 = 0x50;
                        }
                        temp_ret_999 = (int)igProperty_GetRecord(temp_v0_149, MEICHURITSU);
                        int temp_s0_30 = ((beDataObjInt *)temp_ret_999)->_data;
                        beMessenger_ClearInt(self->_messenger);
                        beMessenger_AppendInt(self->_messenger, (int) (temp_s0_30 * var_s1_20) / 100);
                    }
                }
            }
            }
            break; }
        case 12: {
            temp_ret_1001 = (char *)(beMessenger_GetString(self->_messenger, 1));
            temp_v0_155 = (char *)(temp_ret_1001);
            if (temp_v0_155 == 0) {
                var_v0_21 = (char *)(0);
            } else {
                var_v0_21 = (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_155);
            }
            { StringRef sp43C((char *)(var_v0_21));
            temp_ret_1004 = beMessenger_GetInt(self->_messenger, 0);
            temp_v0_156 = temp_ret_1004;
            temp_ret_1005 = beMessenger_GetInt(self->_messenger, 1);
            temp_v0_157 = temp_ret_1005;
            temp_ret_1006 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_1007 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_1008 = ObjectList_GetAt_003e9260(temp_ret_1007, temp_v0_156);
            temp_v0_158 = (void *)(temp_ret_1008);
            temp_s2_4 = temp_ret_1006 % 10000;
            temp_ret_1009 = strcmp(sp43C.p, &TIME[0]);
            if (temp_ret_1009 == 0) {
                temp_ret_1010 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                if (temp_ret_1010 == 0) {
                    beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                    temp_ret_1011 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_1012 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_1011));
                }
                temp_ret_1013 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                temp_ret_1014 = (char *)(beDataBase_GetRecordString(temp_ret_1013, temp_s2_4, &KOUKA[0]));
                var_s1_21 = 0;
                temp_ret_1015 = strcmp(temp_ret_1014, &powerdown[0]);
                if (temp_ret_1015 == 0) {
                    temp_ret_1016 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    if (temp_ret_1016 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                        temp_ret_1017 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1018 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_1017));
                    }
                    temp_ret_1019 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    temp_ret_1020 = beDataBase_GetRecordInt(temp_ret_1019, temp_s2_4, &KOUKARANK[0]);
                    temp_ret_1021 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    if (temp_ret_1021 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                        temp_ret_1022 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1023 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_1022));
                    }
                    temp_ret_1024 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    temp_ret_1025 = beDataBase_GetRecordInt(temp_ret_1024, temp_v0_157, KASHIKOSA);
                    temp_ret_1026 = (int)igProperty_GetRecord(temp_v0_158, SEISHIN);
                    temp_s3_13 = ((beDataObjInt *)temp_ret_1026)->_data;
                    temp_ret_1027 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                    temp_v0_159 = (void **)(temp_ret_1027);
                    temp_a4_3 = ((DW4VC_96_0 *)(temp_v0_159))->vX() % 10000U;
                    temp_s0_31 = (((int) (temp_ret_1025 * 3) / (int) temp_s3_13) + 0x64) - ((int) temp_s3_13 / 40);
                    int rec_scaled = (int) (temp_ret_1020 * 0xA0) / 100;
                    if ((int) temp_a4_3 < (rec_scaled * temp_s0_31)) {
                        temp_ret_1028 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        if (temp_ret_1028 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                            temp_ret_1029 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_1030 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_1029));
                        }
                        temp_ret_1031 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        temp_ret_1032 = beDataBase_GetRecordInt(temp_ret_1031, temp_s2_4, &KOUKATIME[0]);
                        var_s1_21 = (int)((int) (temp_ret_1032 * temp_s0_31) / 100);
                    }
                    if (var_s1_21 == 0) {
                        var_s1_21 = -1;
                    }
                }
                beMessenger_ClearInt(self->_messenger);
                beMessenger_AppendInt(self->_messenger, var_s1_21);
            } else {
                temp_ret_1033 = strcmp(sp43C.p, TSUYOSA);
                if (temp_ret_1033 == 0) {
                    temp_ret_1034 = (int)igProperty_GetRecordIntList(temp_v0_158, DOWNDATA);
                    temp_ret_1035 = (void *)(PropertyRecord_GetValue_00406e40((int *)temp_ret_1034));
                    temp_v0_160 = (void *)(temp_ret_1035);
                    temp_v1_11 = ((igIntList *)temp_v0_160)->_count;
                    if ((temp_v1_11 != 0) && (temp_v1_11 > 4)) {
                        temp_s1_12 = DAT_004cf5e8[0];
                        temp_ret_1036 = DataList_GetData_003e9090(temp_v0_160);
                        ((int *)temp_ret_1036)[4] = temp_s1_12;
                    }
                    beNDMWGameRam_RecomputeStats(self, temp_v0_156, 1);
                    temp_ret_1038 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    if (temp_ret_1038 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                        temp_ret_1039 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1040 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_1039));
                    }
                    temp_ret_1041 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                    temp_ret_1042 = beDataBase_GetRecordInt(temp_ret_1041, temp_s2_4, &KOUKARANK[0]);
                    temp_ret_1043 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    if (temp_ret_1043 == 0) {
                        beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                        temp_ret_1044 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1045 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_1044));
                    }
                    temp_ret_1046 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                    temp_ret_1047 = beDataBase_GetRecordInt(temp_ret_1046, temp_v0_157, KASHIKOSA);
                    temp_ret_1048 = (int)igProperty_GetRecord(temp_v0_158, SEISHIN);
                    temp_v0_161 = (void *)(temp_ret_1048);
                    var_s1_22 = (temp_ret_1042 + ((int) ((int) (temp_ret_1047 * 0x96) / (int) ((beDataObjInt *)temp_v0_161)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_161)->_data / 80);
                    if (var_s1_22 < 0x14) {
                        var_s1_22 = 0x14;
                    }
                    if (var_s1_22 > 0x50) {
                        var_s1_22 = 0x50;
                    }
                    temp_ret_1049 = (int)igProperty_GetRecord(temp_v0_158, TSUYOSA);
                    int temp_s0_32 = ((beDataObjInt *)temp_ret_1049)->_data;
                    beMessenger_ClearInt(self->_messenger);
                    beMessenger_AppendInt(self->_messenger, (int) (temp_s0_32 * var_s1_22) / 100);
                } else {
                    temp_ret_1050 = strcmp(sp43C.p, MAMORI);
                    if (temp_ret_1050 == 0) {
                        temp_ret_1051 = (int)igProperty_GetRecordIntList(temp_v0_158, DOWNDATA);
                        temp_ret_1052 = (void *)(PropertyRecord_GetValue_00406e40((int *)temp_ret_1051));
                        temp_v0_162 = (void *)(temp_ret_1052);
                        temp_v1_12 = ((igIntList *)temp_v0_162)->_count;
                        if ((temp_v1_12 != 0) && (temp_v1_12 > 5)) {
                            temp_s1_13 = DAT_004cf5f0[0];
                            temp_ret_1053 = DataList_GetData_003e9090(temp_v0_162);
                            ((int *)temp_ret_1053)[5] = temp_s1_13;
                        }
                        beNDMWGameRam_RecomputeStats(self, temp_v0_156, 1);
                        temp_ret_1055 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        if (temp_ret_1055 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], &eneatk[0], 0, &GETDATABASE_6[0]);
                            temp_ret_1056 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_1057 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)temp_ret_1056));
                        }
                        temp_ret_1058 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEneatk));
                        temp_ret_1059 = beDataBase_GetRecordInt(temp_ret_1058, temp_s2_4, &KOUKARANK[0]);
                        temp_ret_1060 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        if (temp_ret_1060 == 0) {
                            beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], &enemy[0], 0, &GETDATABASE_5[0]);
                            temp_ret_1061 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                            temp_ret_1062 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)temp_ret_1061));
                        }
                        temp_ret_1063 = (void *)(ObjectRef_Get_00406ee0(&self->_dBEnemy));
                        temp_ret_1064 = beDataBase_GetRecordInt(temp_ret_1063, temp_v0_157, KASHIKOSA);
                        temp_ret_1065 = (int)igProperty_GetRecord(temp_v0_158, SEISHIN);
                        temp_v0_163 = (void *)(temp_ret_1065);
                        var_s1_23 = (temp_ret_1059 + ((int) ((int) (temp_ret_1064 * 0x96) / (int) ((beDataObjInt *)temp_v0_163)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_163)->_data / 80);
                        var_s1_23 = (temp_ret_1059 + ((int) ((int) (temp_ret_1064 * 0x96) / (int) ((beDataObjInt *)temp_v0_163)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_163)->_data / 80);
                        if (var_s1_23 < 0x14) {
                            var_s1_23 = 0x14;
                        }
                        if (var_s1_23 > 0x50) {
                            var_s1_23 = 0x50;
                        }
                        temp_ret_1066 = (int)igProperty_GetRecord(temp_v0_158, MAMORI);
                        int temp_s0_33 = ((beDataObjInt *)temp_ret_1066)->_data;
                        beMessenger_ClearInt(self->_messenger);
                        beMessenger_AppendInt(self->_messenger, (int) (temp_s0_33 * var_s1_23) / 100);
                    }
                }
            }
            }
            break; }
        case 20:
            temp_ret_1068 = beMessenger_GetInt(self->_messenger, 0);
            temp_v0_164 = temp_ret_1068;
            temp_ret_1069 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_1070 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_1071 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
            temp_ret_1072 = ObjectList_GetAt_003e9260(temp_ret_1071, temp_v0_164);
            temp_v0_165 = (void *)(temp_ret_1072);
            if (temp_v0_164 == temp_ret_1069) {
                temp_s5_4 = temp_ret_1070 % 10000;
                if (temp_s5_4 == 40 || temp_s5_4 == 45) {
                    int sp438;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_165, temp_s5_4, &sp438);
                    temp_ret_1073 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1073 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1074 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1075 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1074));
                    }
                    temp_ret_1076 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1077 = beDataBase_GetRecordInt(temp_ret_1076, sp438, SKILL);
                    temp_v0_166 = temp_ret_1077;
                    if (temp_v0_166 != 8) {
                        if (temp_v0_166 != 7) {
                            temp_ret_1078 = (int)igProperty_GetRecordIntList(temp_v0_165, SKILL);
                            temp_ret_1079 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_1078)->_data));
                            temp_ret_1080 = DataList_GetData_003e9090(temp_ret_1079);
                            var_s3_5 = *(int *)(temp_ret_1080 + (temp_v0_166 * 4));
                        } else {
                            temp_ret_1081 = (int)igProperty_GetRecordIntList(temp_v0_165, SKILL);
                            temp_ret_1082 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_1081)->_data));
                            temp_ret_1083 = DataList_GetData_003e9090(temp_ret_1082);
                            var_s3_5 = ((int *)temp_ret_1083)[7];
                        }
                    } else {
                        temp_ret_1084 = (int)igProperty_GetRecordIntList(temp_v0_165, SKILL);
                        temp_ret_1085 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_1084)->_data));
                        temp_ret_1086 = DataList_GetData_003e9090(temp_ret_1085);
                        var_s3_5 = ((int *)temp_ret_1086)[8];
                    }
                    temp_ret_1087 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1087 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1088 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1089 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1088));
                    }
                    temp_ret_1090 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1091 = beDataBase_GetRecordInt(temp_ret_1090, sp438, HP);
                    temp_ret_1092 = (int)igProperty_GetRecord(temp_v0_165, KASHIKOSA);
                    int pre_sum = temp_ret_1091 + var_s3_5;
                    temp_s2_5 = pre_sum + ((beDataObjInt *)temp_ret_1092)->_data;
                    temp_ret_1093 = beNDMWGameRam_ChangeHp(self, temp_v0_164, temp_s2_5, -1);
                    if (temp_s5_4 == 0x2D) {
                        temp_ret_1094 = (int)igProperty_GetRecordString(temp_v0_165, DIGIMONNAME_2);
                        temp_ret_1095 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1094)->_data);
                        beMessenger_SendNamed(self->_messenger, &PLAYER_2[0], temp_ret_1095, temp_v0_164, GETMATRIX);
                        beMessenger_GetMatrix(&sp270, self->_messenger, 0);
                        igMatrix44f_GetTranslation(&sp270, &sp3D8);
                        { NearbyListRef sp434 = beNDMWGameRam_CollectNearbyNonzeroHp(self, &PLAYER_2[0], temp_v0_164, &sp3D8);
                        temp_s3_14 = ((igIntList *)sp434.value)->_count;
                        for (var_s1_24 = 0; var_s1_24 < temp_s3_14; ++var_s1_24) {
                                temp_ret_1096 = DataList_GetData_003e9090(sp434.value);
                                temp_s5_5 = ((int *)temp_ret_1096)[var_s1_24];
                                temp_ret_1097 = beNDMWGameRam_ChangeHp(self, temp_s5_5, temp_s2_5, -1);
                                temp_ret_1098 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                                temp_ret_1099 = ObjectList_GetAt_003e9260(temp_ret_1098, temp_s5_5);
                                temp_ret_1100 = (int)igProperty_GetRecordString((void *)temp_ret_1099, DIGIMONNAME_2);
                                temp_ret_1101 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1100)->_data);
                                temp_ret_1102 = beMessenger_PrepareDelayedSelection(self->_messenger, &PLAYER_2[0], temp_ret_1101, temp_s5_5);
                                beMessenger_AppendString(self->_messenger, &x_250healhit00[0]);
                                beMessenger_AppendString(self->_messenger, &SQ_HEALEFONLY[0]);
                                beMessenger_AppendFloat(self->_messenger, 1.0f);
                                Vec3f_Copy(&sp338, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(self->_messenger, &sp338);
                                beMessenger_AppendBool(self->_messenger, 0U);
                                beMessenger_AppendBool(self->_messenger, 1U);
                                temp_ret_1103 = beMessenger_EnqueueSelected(self->_messenger, &SETEFFECT[0], 1);
                        }
                        }
                    }
                } else if (temp_s5_4 == 55 || temp_s5_4 == 60) {
                    int sp430;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_165, temp_s5_4, &sp430);
                    temp_ret_1104 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1104 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1105 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1106 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1105));
                    }
                    temp_ret_1107 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1108 = beDataBase_GetRecordInt(temp_ret_1107, sp430, SKILL);
                    temp_v0_167 = temp_ret_1108;
                    switch (temp_v0_167) { default: temp_ret_1109 = (int)igProperty_GetRecordIntList(temp_v0_165, SKILL);
 temp_ret_1110 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_1109)->_data));
 temp_ret_1111 = (int)DataList_GetData_003e9090(temp_ret_1110); break; case 7: temp_ret_1112 = (int)igProperty_GetRecordIntList(temp_v0_165, SKILL);
 temp_ret_1113 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_1112)->_data));
 temp_ret_1114 = (int)DataList_GetData_003e9090(temp_ret_1113); break; case 8: temp_ret_1115 = (int)igProperty_GetRecordIntList(temp_v0_165, SKILL);
 temp_ret_1116 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_1115)->_data));
 temp_ret_1117 = DataList_GetData_003e9090(temp_ret_1116); break; }
temp_ret_1118 = (int)igProperty_GetRecordString(temp_v0_165, DIGIMONNAME_2);
                    temp_ret_1119 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1118)->_data);
                    beMessenger_SendNamed(self->_messenger, &PLAYER_2[0], temp_ret_1119, temp_v0_164, &GETPEBASEWORK_3[0]);
                    temp_ret_1120 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_1121 = (void *)(beMessenger_GetObject(self->_messenger, 1));
                    temp_v0_168 = (void *)(temp_ret_1121);
                    temp_ret_1122 = beNDMWMdlPEBaseInfoWork_IsPoisoned(temp_v0_168);
                    if (temp_ret_1122 != 0) {
                        temp_s6_3 = ((sp430 - temp_s5_4) + 5) - ((beNDMWMdlPEBaseInfoWork *)temp_v0_168)->_poisonEndurance;
                        temp_ret_1123 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                        temp_v0_169 = (void **)(temp_ret_1123);
                        temp_v0_170 = ((DW4VC_96_0 *)(temp_v0_169))->vX() % 10U;
                        if (temp_s6_3 >= (int) temp_v0_170) {
                            temp_ret_1124 = beNDMWMdlPEBaseInfoWork_CurePoison(temp_v0_168, temp_ret_1120);
                        }
                    }
                    if (temp_s5_4 == 0x3C) {
                        temp_ret_1125 = (int)igProperty_GetRecordString(temp_v0_165, DIGIMONNAME_2);
                        temp_ret_1126 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1125)->_data);
                        beMessenger_SendNamed(self->_messenger, &PLAYER_2[0], temp_ret_1126, temp_v0_164, GETMATRIX);
                        beMessenger_GetMatrix(&sp230, self->_messenger, 0);
                        igMatrix44f_GetTranslation(&sp230, &sp3C8);
                        { NearbyListRef sp42C = beNDMWGameRam_CollectNearbyNonzeroHp(self, &PLAYER_2[0], temp_v0_164, &sp3C8);
                        temp_v0_171 = ((igIntList *)sp42C.value)->_count;
                        int sp100 = temp_v0_171;
                        for (var_s3_6 = 0; var_s3_6 < sp100; ++var_s3_6) {
                                temp_ret_1127 = DataList_GetData_003e9090(sp42C.value);
                                temp_s2_6 = ((int *)temp_ret_1127)[var_s3_6];
                                temp_ret_1128 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                                temp_ret_1129 = ObjectList_GetAt_003e9260(temp_ret_1128, temp_s2_6);
                                temp_v0_172 = (void *)(temp_ret_1129);
                                temp_ret_1130 = (int)igProperty_GetRecordString(temp_v0_172, DIGIMONNAME_2);
                                temp_ret_1131 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1130)->_data);
                                beMessenger_SendNamed(self->_messenger, &PLAYER_2[0], temp_ret_1131, temp_s2_6, &GETPEBASEWORK_3[0]);
                                temp_ret_1132 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                                temp_ret_1133 = (void *)(beMessenger_GetObject(self->_messenger, 1));
                                temp_v0_173 = (void *)(temp_ret_1133);
                                temp_ret_1134 = beNDMWMdlPEBaseInfoWork_IsPoisoned(temp_v0_173);
                                if (temp_ret_1134 != 0) {
                                    temp_s8_2 = ((sp430 - temp_s5_4) + 5) - ((beNDMWMdlPEBaseInfoWork *)temp_v0_173)->_poisonEndurance;
                                    temp_ret_1135 = (void **)(ObjectRef_Get_00406e50((int *)(self->_system + 0x30)));
                                    temp_v0_174 = (void **)(temp_ret_1135);
                                    temp_v0_175 = ((DW4VC_96_0 *)(temp_v0_174))->vX() % 10U;
                                    if (temp_s8_2 >= (int) temp_v0_175) {
                                        temp_ret_1136 = beNDMWMdlPEBaseInfoWork_CurePoison(temp_v0_173, temp_ret_1132);
                                    }
                                }
                                temp_ret_1137 = (int)igProperty_GetRecordString(temp_v0_172, DIGIMONNAME_2);
                                temp_ret_1138 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1137)->_data);
                                temp_ret_1139 = beMessenger_PrepareDelayedSelection(self->_messenger, &PLAYER_2[0], temp_ret_1138, temp_s2_6);
                                beMessenger_AppendString(self->_messenger, &x_250curehit00[0]);
                                beMessenger_AppendString(self->_messenger, &SQ_CUREEFONLY[0]);
                                beMessenger_AppendFloat(self->_messenger, 1.0f);
                                Vec3f_Copy(&sp328, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(self->_messenger, &sp328);
                                beMessenger_AppendBool(self->_messenger, 0U);
                                beMessenger_AppendBool(self->_messenger, 1U);
                                temp_ret_1140 = beMessenger_EnqueueSelected(self->_messenger, &SETEFFECT[0], 1);
                        }
                        }
                    }
                } else if (temp_s5_4 == 50 || temp_s5_4 == -50) {
                    if (temp_s5_4 >= 0) {
                        int sp428;
                        beNDMWGameRam_FindTechniqueRow(self, temp_v0_165, temp_s5_4, &sp428);
                        temp_a0_10 = sp428 * 4;
                        var_s3_7 = DAT_004cf538[sp428];
                        var_s2_12 = DAT_004cf558[sp428];
                    } else {
                        var_s3_7 = DAT_004cf600[0];
                        var_s2_12 = DAT_004cf620[0];
                    }
                    igMatrix44f_SetIdentity(&sp2B0);
                    temp_ret_1141 = (int)igProperty_GetRecordString(temp_v0_165, DIGIMONNAME_2);
                    temp_ret_1142 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1141)->_data);
                    beMessenger_SendNamed(self->_messenger, &PLAYER_2[0], temp_ret_1142, temp_v0_164, GETMATRIX);
                    beMessenger_GetMatrix(&sp1F0, self->_messenger, 0);
                    igMatrix44f_Copy(&sp2B0, &sp1F0);
                    igMatrix44f_GetTranslation(&sp2B0, &sp3B8);
                    { NearbyListRef sp424 = beNDMWGameRam_CollectNearbyNonzeroHp(self, &PLAYER2[0], -1, &sp3B8);
                    temp_s5_6 = ((igIntList *)sp424.value)->_count;
                    for (var_s1_25 = 0; var_s1_25 < temp_s5_6; ++var_s1_25) {
                            temp_ret_1143 = DataList_GetData_003e9090(sp424.value);
                            beMessenger_SelectReceivers(self->_messenger, &PLAYER2[0], 0, ((int *)temp_ret_1143)[var_s1_25]);
                            beMessenger_AppendMatrix(self->_messenger, &sp2B0);
                            beMessenger_AppendInt(self->_messenger, var_s3_7);
                            beMessenger_AppendInt(self->_messenger, var_s2_12);
                            beMessenger_DispatchSelected(self->_messenger, (const char *)&RAISE[0]);
                    }
                    }
                } else if (temp_s5_4 == 65) {
                    int sp420;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_165, temp_s5_4, &sp420);
                    temp_ret_1145 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1145 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1146 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1147 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1146));
                    }
                    temp_ret_1148 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1149 = beDataBase_GetRecordInt(temp_ret_1148, sp420, SKILL);
                    temp_ret_1150 = (int)igProperty_GetRecord(temp_v0_165, KASHIKOSA);
                    temp_s2_7 = ((beDataObjInt *)temp_ret_1150)->_data;
                    temp_ret_1151 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1151 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1152 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1153 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1152));
                    }
                    temp_ret_1154 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1155 = beDataBase_GetRecordInt(temp_ret_1154, sp420, &TIME[0]);
                    int spF0 = temp_ret_1155 + temp_s2_7;
                    temp_ret_1156 = (int)igProperty_GetRecordIntList(temp_v0_165, SKILL);
                    temp_ret_1157 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_1156)->_data));
                    temp_ret_1158 = DataList_GetData_003e9090(temp_ret_1157);
                    temp_s2_8 = *(int *)(temp_ret_1158 + (temp_ret_1149 * 4));
                    temp_ret_1159 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1159 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1160 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1161 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1160));
                    }
                    temp_ret_1162 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1163 = beDataBase_GetRecordInt(temp_ret_1162, sp420, SUBAYASA);
                    int spE0 = ((int) temp_s2_8 / 5) + temp_ret_1163;
                    temp_ret_1164 = (int)igProperty_GetRecordString(temp_v0_165, DIGIMONNAME_2);
                    temp_ret_1165 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1164)->_data);
                    beMessenger_SendNamed(self->_messenger, &PLAYER_2[0], temp_ret_1165, temp_v0_164, GETMATRIX);
                    beMessenger_GetMatrix(&sp1B0, self->_messenger, 0);
                    igMatrix44f_GetTranslation(&sp1B0, &sp3A8);
                    { NearbyListRef sp41C = beNDMWGameRam_CollectNearbyNonzeroHp(self, &PLAYER_2[0], temp_v0_164, &sp3A8);
                    temp_ret_1166 = (void *)(ObjectRef_Get_00406dc0((int *)&sp41C.value));
                    temp_v0_176 = (void *)(temp_ret_1166);
                    RecoveryList::append(temp_v0_176, temp_v0_164);
                    temp_v0_177 = ((igIntList *)sp41C.value)->_count;
                    int spD0 = temp_v0_177;
                    for (var_s5_8 = 0; var_s5_8 < spD0; ++var_s5_8) {
                            temp_ret_1168 = DataList_GetData_003e9090(sp41C.value);
                            temp_s3_15 = ((int *)temp_ret_1168)[var_s5_8];
                            temp_ret_1169 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                            temp_ret_1170 = ObjectList_GetAt_003e9260(temp_ret_1169, temp_s3_15);
                            temp_v0_178 = (void *)(temp_ret_1170);
                            temp_ret_1171 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                            if (temp_ret_1171 == 0) {
                                beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                                temp_ret_1172 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                                temp_ret_1173 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1172));
                            }
                            temp_ret_1174 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                            temp_ret_1175 = beDataBase_GetRecordInt(temp_ret_1174, sp420, CHIMEIRITSU);
                            temp_ret_1176 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                            if (temp_ret_1176 == 0) {
                                beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                                temp_ret_1177 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                                temp_ret_1178 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1177));
                            }
                            temp_ret_1179 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                            temp_ret_1180 = beDataBase_GetRecordInt(temp_ret_1179, sp420, &MHIRITSU[0]);
                            temp_ret_1181 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                            if (temp_ret_1181 == 0) {
                                beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                                temp_ret_1182 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                                temp_ret_1183 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1182));
                            }
                            temp_ret_1184 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                            temp_ret_1185 = beDataBase_GetRecordInt(temp_ret_1184, sp420, KAIHIRITSU);
                            beMessenger_PushArgContext(self->_messenger);
                            temp_ret_1186 = (int)igProperty_GetRecordString(temp_v0_178, DIGIMONNAME_2);
                            temp_ret_1187 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1186)->_data);
                            beMessenger_SelectReceivers(self->_messenger, &PLAYER_2[0], temp_ret_1187, temp_s3_15);
                            beMessenger_AppendInt(self->_messenger, spF0);
                            beMessenger_AppendInt(self->_messenger, spE0);
                            beMessenger_AppendInt(self->_messenger, temp_ret_1175);
                            beMessenger_AppendInt(self->_messenger, temp_ret_1180);
                            beMessenger_AppendInt(self->_messenger, temp_ret_1185);
                            beMessenger_DispatchSelected(self->_messenger, (const char *)&SETSPEEDUP[0]);
                            if (temp_s3_15 != temp_v0_164) {
                                temp_ret_1189 = (int)igProperty_GetRecordString(temp_v0_178, DIGIMONNAME_2);
                                temp_ret_1190 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1189)->_data);
                                temp_ret_1191 = beMessenger_PrepareDelayedSelection(self->_messenger, &PLAYER_2[0], temp_ret_1190, temp_s3_15);
                                beMessenger_AppendString(self->_messenger, &x_250uphit00[0]);
                                beMessenger_AppendString(self->_messenger, &SQ_UPEFONLY[0]);
                                beMessenger_AppendFloat(self->_messenger, 1.0f);
                                Vec3f_Copy(&sp318, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(self->_messenger, &sp318);
                                beMessenger_AppendBool(self->_messenger, 0U);
                                beMessenger_AppendBool(self->_messenger, 1U);
                                temp_ret_1192 = beMessenger_EnqueueSelected(self->_messenger, &SETEFFECT[0], 1);
                            }
                            beMessenger_PopArgContext(self->_messenger);
                    }
                    }
                } else if (temp_s5_4 == 80) {
                    int sp418;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_165, temp_s5_4, &sp418);
                    temp_ret_1193 = (int)igProperty_GetRecord(temp_v0_165, KASHIKOSA);
                    temp_s2_9 = ((beDataObjInt *)temp_ret_1193)->_data;
                    temp_ret_1194 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1194 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1195 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1196 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1195));
                    }
                    temp_ret_1197 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1198 = beDataBase_GetRecordInt(temp_ret_1197, sp418, &TIME[0]);
                    int sum80a = temp_ret_1198 + temp_s2_9;
                    temp_ret_1199 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1199 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1200 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1201 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1200));
                    }
                    temp_ret_1202 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1203 = beDataBase_GetRecordInt(temp_ret_1202, sp418, SKILL);
                    temp_ret_1204 = (int)igProperty_GetRecordIntList(temp_v0_165, SKILL);
                    temp_ret_1205 = (void *)(ObjectRef_Get_00406ef0(&((beDataObjIntList *)temp_ret_1204)->_data));
                    temp_ret_1206 = DataList_GetData_003e9090(temp_ret_1205);
                    temp_s2_10 = *(int *)(temp_ret_1206 + (temp_ret_1203 * 4));
                    temp_ret_1207 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1207 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1208 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1209 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1208));
                    }
                    temp_ret_1210 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_s2_11 = (int)((int) temp_s2_10 / 5);
                    temp_ret_1211 = beDataBase_GetRecordInt(temp_ret_1210, sp418, MAXHP);
                    int sum80d = temp_s2_11 + temp_ret_1211;
                    temp_ret_1212 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1212 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1213 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1214 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1213));
                    }
                    temp_ret_1215 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1216 = beDataBase_GetRecordInt(temp_ret_1215, sp418, TSUYOSA);
                    int spC0 = temp_s2_11 + temp_ret_1216;
                    temp_ret_1217 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1217 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1218 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1219 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1218));
                    }
                    temp_ret_1220 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1221 = beDataBase_GetRecordInt(temp_ret_1220, sp418, MAMORI);
                    int spB0 = temp_s2_11 + temp_ret_1221;
                    temp_ret_1222 = (int)igProperty_GetRecordString(temp_v0_165, DIGIMONNAME_2);
                    temp_ret_1223 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1222)->_data);
                    beMessenger_SendNamed(self->_messenger, &PLAYER_2[0], temp_ret_1223, temp_v0_164, GETMATRIX);
                    beMessenger_GetMatrix(&sp170, self->_messenger, 0);
                    igMatrix44f_GetTranslation(&sp170, &sp398);
                    { NearbyListRef sp414 = beNDMWGameRam_CollectNearbyNonzeroHp(self, &PLAYER_2[0], temp_v0_164, &sp398);
                    temp_ret_1224 = (void *)(ObjectRef_Get_00406dc0((int *)&sp414.value));
                    temp_v0_179 = (void *)(temp_ret_1224);
                    RecoveryList::append(temp_v0_179, temp_v0_164);
                    temp_s6_4 = ((igIntList *)sp414.value)->_count;
                    for (var_s5_9 = 0; var_s5_9 < temp_s6_4; ++var_s5_9) {
                            temp_ret_1226 = DataList_GetData_003e9090(sp414.value);
                            temp_s3_16 = ((int *)temp_ret_1226)[var_s5_9];
                            temp_ret_1227 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                            temp_ret_1228 = ObjectList_GetAt_003e9260(temp_ret_1227, temp_s3_16);
                            temp_v0_180 = (void *)(temp_ret_1228);
                            beMessenger_PushArgContext(self->_messenger);
                            temp_ret_1229 = (int)igProperty_GetRecordString(temp_v0_180, DIGIMONNAME_2);
                            temp_ret_1230 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1229)->_data);
                            beMessenger_SelectReceivers(self->_messenger, &PLAYER_2[0], temp_ret_1230, temp_s3_16);
                            beMessenger_AppendInt(self->_messenger, sum80a);
                            beMessenger_AppendInt(self->_messenger, spC0);
                            beMessenger_AppendInt(self->_messenger, spB0);
                            beMessenger_AppendInt(self->_messenger, sum80d);
                            beMessenger_DispatchSelected(self->_messenger, (const char *)&SETPOWERUP[0]);
                            if (temp_s3_16 != temp_v0_164) {
                                temp_ret_1232 = (int)igProperty_GetRecordString(temp_v0_180, DIGIMONNAME_2);
                                temp_ret_1233 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1232)->_data);
                                temp_ret_1234 = beMessenger_PrepareDelayedSelection(self->_messenger, &PLAYER_2[0], temp_ret_1233, temp_s3_16);
                                beMessenger_AppendString(self->_messenger, &x_250uphit00[0]);
                                beMessenger_AppendString(self->_messenger, &SQ_UPEFONLY[0]);
                                beMessenger_AppendFloat(self->_messenger, 1.0f);
                                Vec3f_Copy(&sp308, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(self->_messenger, &sp308);
                                beMessenger_AppendBool(self->_messenger, 0U);
                                beMessenger_AppendBool(self->_messenger, 1U);
                                temp_ret_1235 = beMessenger_EnqueueSelected(self->_messenger, &SETEFFECT[0], 1);
                            }
                            beMessenger_PopArgContext(self->_messenger);
                    }
                    }
                } else if (temp_s5_4 == 75) {
                    int sp410;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_165, temp_s5_4, &sp410);
                    temp_ret_1236 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1236 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1237 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1238 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1237));
                    }
                    temp_ret_1239 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1240 = beDataBase_GetRecordInt(temp_ret_1239, sp410, &TIME[0]);
                    temp_ret_1241 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1241 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1242 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1243 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1242));
                    }
                    temp_ret_1244 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1245 = beDataBase_GetRecordInt(temp_ret_1244, sp410, &FIRE[0]);
                    int spAC = temp_ret_1245;
                    temp_ret_1246 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1246 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1247 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1248 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1247));
                    }
                    temp_ret_1249 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1250 = beDataBase_GetRecordInt(temp_ret_1249, sp410, &ICE[0]);
                    int spA8 = temp_ret_1250;
                    temp_ret_1251 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1251 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1252 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1253 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1252));
                    }
                    temp_ret_1254 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1255 = beDataBase_GetRecordInt(temp_ret_1254, sp410, &THUNDER[0]);
                    int spA4 = temp_ret_1255;
                    temp_ret_1256 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    if (temp_ret_1256 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
                        temp_ret_1257 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_1258 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)temp_ret_1257));
                    }
                    temp_ret_1259 = (void *)(ObjectRef_Get_00406ee0(&self->_dBPcTech));
                    temp_ret_1260 = beDataBase_GetRecordInt(temp_ret_1259, sp410, &DARK[0]);
                    temp_ret_1261 = (int)igProperty_GetRecordString(temp_v0_165, DIGIMONNAME_2);
                    temp_ret_1262 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1261)->_data);
                    beMessenger_SendNamed(self->_messenger, &PLAYER_2[0], temp_ret_1262, temp_v0_164, GETMATRIX);
                    beMessenger_GetMatrix(&sp130, self->_messenger, 0);
                    igMatrix44f_GetTranslation(&sp130, &sp388);
                    { NearbyListRef sp40C = beNDMWGameRam_CollectNearbyNonzeroHp(self, &PLAYER_2[0], temp_v0_164, &sp388);
                    temp_ret_1263 = (void *)(ObjectRef_Get_00406dc0((int *)&sp40C.value));
                    temp_v0_181 = (void *)(temp_ret_1263);
                    RecoveryList::append(temp_v0_181, temp_v0_164);
                    temp_s6_5 = ((igIntList *)sp40C.value)->_count;
                    for (var_s5_10 = 0; var_s5_10 < temp_s6_5; ++var_s5_10) {
                            temp_ret_1265 = DataList_GetData_003e9090(sp40C.value);
                            temp_s3_17 = ((int *)temp_ret_1265)[var_s5_10];
                            temp_ret_1266 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
                            temp_ret_1267 = ObjectList_GetAt_003e9260(temp_ret_1266, temp_s3_17);
                            temp_v0_182 = (void *)(temp_ret_1267);
                            beMessenger_PushArgContext(self->_messenger);
                            temp_ret_1268 = (int)igProperty_GetRecordString(temp_v0_182, DIGIMONNAME_2);
                            temp_ret_1269 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1268)->_data);
                            beMessenger_SelectReceivers(self->_messenger, &PLAYER_2[0], temp_ret_1269, temp_s3_17);
                            beMessenger_AppendInt(self->_messenger, temp_ret_1240);
                            beMessenger_AppendInt(self->_messenger, spAC);
                            beMessenger_AppendInt(self->_messenger, spA8);
                            beMessenger_AppendInt(self->_messenger, spA4);
                            beMessenger_AppendInt(self->_messenger, temp_ret_1260);
                            beMessenger_DispatchSelected(self->_messenger, (const char *)&SETREFRACT[0]);
                            if (temp_s3_17 != temp_v0_164) {
                                temp_ret_1271 = (int)igProperty_GetRecordString(temp_v0_182, DIGIMONNAME_2);
                                temp_ret_1272 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1271)->_data);
                                temp_ret_1273 = beMessenger_PrepareDelayedSelection(self->_messenger, &PLAYER_2[0], temp_ret_1272, temp_s3_17);
                                beMessenger_AppendString(self->_messenger, &x_250uphit00[0]);
                                beMessenger_AppendString(self->_messenger, &SQ_UPEFONLY[0]);
                                beMessenger_AppendFloat(self->_messenger, 1.0f);
                                Vec3f_Copy(&sp2F8, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(self->_messenger, &sp2F8);
                                beMessenger_AppendBool(self->_messenger, 0U);
                                beMessenger_AppendBool(self->_messenger, 1U);
                                temp_ret_1274 = beMessenger_EnqueueSelected(self->_messenger, &SETEFFECT[0], 1);
                            }
                            beMessenger_PopArgContext(self->_messenger);
                    }
                    }
                }
                beMessenger_ClearInt(self->_messenger);
                beMessenger_AppendInt(self->_messenger, 1);
            }
            break;
        }
        }
        return 1;
    case 20:
        /* Block-local webs are declared in the order player, common, idx; their register ids fix
         * the allocator push order. */
        int tail_idx;
        int temp_s3_18;
        int temp_s0_34;
        void *tail_common;
        void *tail_player;
        int temp_s0_35;
        tail_idx = beMessenger_GetInt(self->_messenger, 0);
                tail_common = (void *)(ObjectRef_Get_00407040(&self->_commonDataList));
                temp_ret_1278 = (void *)(ObjectRef_Get_00407030(&self->_playerDataListList));
        tail_player = (void *)ObjectList_GetAt_003e9260(temp_ret_1278, tail_idx);
                temp_ret_1280 = (int)igProperty_GetRecordString(tail_player, DIGIMONNAME_2);
        temp_ret_1281 = (const char *)ObjectRef_Get_00407050(&((beDataObjString *)temp_ret_1280)->_data);
        temp_v0_186 = temp_ret_1281;
        DW4StrListOps::SetAt((igStringRefList *)PropertyRecord_GetValue_00406db0((int *)(igProperty_GetRecordStringList(tail_common, &BKCHIPNAME[0]))), tail_idx, StringRef(temp_v0_186 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_186)));
        temp_s0_34 = tail_idx * 2;
        temp_ret_1289 = (int)igProperty_GetRecord(tail_player, &BIT_3[0]);
        temp_s3_18 = ((beDataObjInt *)temp_ret_1289)->_data;
        temp_ret_1290 = (int)igProperty_GetRecordIntList(tail_common, &BKCHIPDATA[0]);
        temp_ret_1291 = (void *)(PropertyRecord_GetValue_00406e40((int *)temp_ret_1290));
        temp_v0_188 = (void *)(temp_ret_1291);
        temp_v1_14 = ((igIntList *)temp_v0_188)->_count;
        if ((temp_v1_14 != 0) && (temp_s0_34 >= 0) && (temp_s0_34 < temp_v1_14)) {
            temp_ret_1292 = DataList_GetData_003e9090(temp_v0_188);
            *(int *)(temp_ret_1292 + (temp_s0_34 * 4)) = temp_s3_18;
        }
        temp_ret_1293 = (int)igProperty_GetRecord(tail_player, &BIT_3[0]);
        ((beDataObjInt *)temp_ret_1293)->_data = 0;
        temp_s4 = temp_s0_34 + 1;
        temp_ret_1294 = (int)igProperty_GetRecord(tail_player, LEVEL_2);
        temp_s0_35 = ((beDataObjInt *)temp_ret_1294)->_data;
        if ((temp_s0_35 != 0x3E7) && (temp_s0_35 != 1)) {
            temp_ret_1295 = (int)igProperty_GetRecord(tail_player, EXP);
            temp_v0_189 = ((beDataObjInt *)temp_ret_1295)->_data;
            temp_a4_4 = DW4Curve::g(temp_s0_35 - 1, temp_s0_35);
            var_s3_8 = temp_v0_189 - ((temp_a4_4 - DW4Curve::g(temp_s0_35 - 2, temp_s0_35 - 1)) * 2) / 10;
            if (var_s3_8 < temp_a4_4) {
                var_s3_8 = temp_a4_4;
            }
            int new_value = temp_v0_189 - var_s3_8;
            temp_ret_1296 = (int)igProperty_GetRecordIntList(tail_common, &BKCHIPDATA[0]);
            temp_ret_1297 = (void *)(PropertyRecord_GetValue_00406e40((int *)temp_ret_1296));
            temp_v0_190 = (void *)(temp_ret_1297);
            int temp_v1_15 = ((igIntList *)temp_v0_190)->_count;
            if ((temp_v1_15 != 0) && (temp_s4 >= 0) && (temp_s4 < temp_v1_15)) {
                temp_ret_1298 = DataList_GetData_003e9090(temp_v0_190);
                *(int *)(temp_ret_1298 + (temp_s4 * 4)) = new_value;
            }
            temp_ret_1299 = (int)igProperty_GetRecord(tail_player, EXP);
            ((beDataObjInt *)temp_ret_1299)->_data = var_s3_8;
        }
        return 1;
    default:
        return 0;
    }
    return 1;
}


/* igDataList, the base of every typed list, holds the igMemoryRef _data at +16. */


int DataList_GetData_00406da0(igDataList *p)
{
    return p->_data;
}

int PropertyRecord_GetValue_00406db0(int *p)
{
    return ((IntProperty *)p)->value;
}

int ObjectRef_Get_00406dc0(int *p)
{
    return *p;
}

int DataList_GetWordAt_00406dd0(igDataList *list, int index) {
    return *(int *)(list->_data + (index * 4));
}

int ObjectRef_Get_00406df0(int *p)
{
    return *p;
}

int ObjectRef_Get_00406e00(int *p)
{
    return *p;
}

int *DataListRef_Construct_00406e10(int *ref, int *allocator) {
    *ref = beBaseInfoDataList_Create(*allocator);
    return ref;
}

int PropertyRecord_GetValue_00406e40(int *p)
{
    return ((IntProperty *)p)->value;
}

int ObjectRef_Get_00406e50(int *p)
{
    return *p;
}

ObjectRefTarget **ObjectRef_AssignObject_00406e60(ObjectRefTarget **destination,ObjectRefTarget *incoming) {
    ObjectRefTarget *outgoing;
    if(incoming) ++incoming->references;
    outgoing=*destination;
    if(outgoing) {
        --outgoing->references;
        if(((unsigned long long)(long long)outgoing->references & 0x7fffffULL)==0)
            igObject_Destroy(outgoing);
    }
    *destination=incoming;
    return destination;
}

int ObjectRef_Get_00406ee0(int *p)
{
    return *p;
}

int ObjectRef_Get_00406ef0(int *p)
{
    return *p;
}

int DataList_GetData_00406f00(igUnsignedCharList *p)
{
    return p->_data;
}

int ObjectRef_Get_00406f10(int *p)
{
    return *p;
}

void ObjectList_RemoveAt_00406f20(void *list, int index)
{
    List_RemoveWordAt(list, index);
}

AllocatorValue AllocatorValue_Make_00406f40(int value)
{
    return AllocatorValue(value);
}

AllocatorValue AllocatorValue_Make_00406f50(int value)
{
    return AllocatorValue(value);
}

AllocatorValue AllocatorValue_Make_00406f60(int value)
{
    return AllocatorValue(value);
}

AllocatorValue AllocatorValue_Make_00406f70(int value)
{
    return AllocatorValue(value);
}

int ObjectRef_Get_00406f80(int *p)
{
    return *p;
}

int DataObjInt_GetValue_00406f90(beDataObjInt *p)
{
    return p->_data;
}

int StringPool_GetInstance(void) {
    int pool;

    if (g_stringPool[0] == 0) {
        pool = StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    return g_stringPool[0];
}

int ObjectRef_Get_00407030(int *p)
{
    return *p;
}

int ObjectRef_Get_00407040(int *p)
{
    return *p;
}

int ObjectRef_Get_00407050(int *p)
{
    return *p;
}

int beNDMWGameRam_GetMeta(void)
{
    return g_beNDMWGameRam_metaObject[0];
}

int beNDMWGameRam_GetInfoMeta(void) {
    return 0;
}

