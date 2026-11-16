#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
#include "dw4/listSet.h"
#include "dw4/igRandomNumberDispatch.h"
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
extern "C" void beNDMWGameRam_UpdateRam(void);
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
extern "C" int beNDMWGameRam_beDataObjStringList_GetData(int *p);
extern "C" int ObjectRef_Get_00406dc0(int *p);
extern "C" int ObjectRef_Get_00406df0(int *p);
extern "C" int ObjectRef_Get_00406e00(int *p);
extern "C" int beBaseInfoDataList_Create(int);
extern "C" int *beNDMWGameRam_CreateDataListRef(int *ref, int *allocator);
extern "C" int beNDMWGameRam_beDataObjIntList_GetData(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_igRandomNumber_Get(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_beDataBase_Get(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_igIntList_Get(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_igBoolList_Get(int *p);
extern "C" void List_RemoveWordAt(void *list, int index);
extern "C" void beNDMWGameRam_igObjectList_Remove(void *list, int index);
/* matching construct: copy-constructed struct return reproduces the retail hidden-return calling shape */ struct AllocatorValue { int v; AllocatorValue(int value):v(value) {} AllocatorValue(const AllocatorValue &o):v(o.v) {} };
extern "C" AllocatorValue beNDMWGameRam_beNDMWItemAbilityChip_MakeAllocatorValue(int value);
extern "C" AllocatorValue beNDMWGameRam_beNDMWItemYellowArmor_MakeAllocatorValue(int value);
extern "C" AllocatorValue beNDMWGameRam_beNDMWItemBlueArmor_MakeAllocatorValue(int value);
extern "C" AllocatorValue beNDMWGameRam_beNDMWItemWeapon_MakeAllocatorValue(int value);
extern "C" int beNDMWGameRam_igSmartPointer_igObjectList_Get(int *p);
extern "C" int StringPool_GetInstance(void);
extern "C" int beNDMWGameRam_igSmartPointer_beDataObjListList_Get(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_beDataObjList_Get(int *p);
extern "C" int beNDMWGameRam_igStringRef_Get(int *p);
extern "C" int kIGMemoryPoolHandleUser0[4];
extern "C" unsigned char g_useOwnerAllocator;
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
#pragma push
#pragma readonly_strings on

extern "C" {
DataLayoutEntry g_commonDataLayout[] = {
    {DATA_INT, 0, "NINZU"},
    {DATA_INT, 0, "DIFFICULTY"},
    {DATA_INT, 0, "CAMERAMODE"},
    {DATA_INT, 0, "LIGHTMODE"},
    {DATA_BOOL_LIST, 1024, "FLAG"},
    {DATA_BOOL_LIST, 12, "FLAGFOLDER"},
    {DATA_INT_LIST, 16, "COUNTER"},
    {DATA_STRING_LIST, 4, "BKCHIPSTAGE"},
    {DATA_FLOAT_LIST, 12, "BKCHIPPOS"},
    {DATA_INT_LIST, 8, "BKCHIPDATA"},
    {DATA_STRING_LIST, 4, "BKCHIPNAME"},
    {DATA_STRING, 0, "GATESTAGENAME"},
    {DATA_INT, 0, "GATESTAGENO"},
    {DATA_END, 0, ""}
};
DataLayoutEntry g_playerDataLayout[] = {
    {DATA_INT, 0, "UNIQUE"},
    {DATA_OBJECT_LIST, 0, "PLAYERNAME"},
    {DATA_INT, 0, "XDATA"},
    {DATA_INT, 0, "BIT"},
    {DATA_INT, 0, "DIGIMONNO"},
    {DATA_INT, 0, "LEVEL"},
    {DATA_INT_LIST, 9, "SKILL"},
    {DATA_INT_LIST, 11, "UPCNT"},
    {DATA_STRING, 0, "DIGIMONNAME"},
    {DATA_INT, 0, "EXP"},
    {DATA_BOOL, 0, "ISUSE"},
    {DATA_INT, 0, "HP"},
    {DATA_INT, 0, "MHP"},
    {DATA_INT, 0, "MP"},
    {DATA_INT, 0, "MMP"},
    {DATA_INT, 0, "TSUYOSA"},
    {DATA_INT, 0, "MAMORI"},
    {DATA_INT, 0, "KASHIKOSA"},
    {DATA_INT, 0, "SEISHIN"},
    {DATA_INT, 0, "SUBAYASA"},
    {DATA_INT, 0, "HONOOTEIKO"},
    {DATA_INT, 0, "KOORITEIKO"},
    {DATA_INT, 0, "KAMINARITEIKO"},
    {DATA_INT, 0, "YAMITEIKO"},
    {DATA_OBJECT_LIST, 0, "WAZALIST"},
    {DATA_INT, 0, "NEXTEXP"},
    {DATA_INT, 0, "ATTACKDELAY"},
    {DATA_INT, 0, "MEICHURITSU"},
    {DATA_INT, 0, "CHIMEIRITSU"},
    {DATA_INT, 0, "MAHIRITSU"},
    {DATA_INT, 0, "KAIHIRITSU"},
    {DATA_INT, 0, "BOUGYORITSU"},
    {DATA_INT, 0, "MAHITEIKOU"},
    {DATA_INT, 0, "DOKUTEIKOU"},
    {DATA_INT, 0, "BITRITSU"},
    {DATA_INT, 0, "EXPRITSU"},
    {DATA_INT, 0, "LUCKRITSU"},
    {DATA_INT, 0, "ATTACKZOKUSEI"},
    {DATA_INT, 0, "HPDRAIN"},
    {DATA_INT, 0, "MPDRAIN"},
    {DATA_INT, 0, "CHOHATURITSU"},
    {DATA_INT, 0, "WEAPONRECNO"},
    {DATA_INT, 0, "WEAPONSKILLNO"},
    {DATA_OBJECT_LIST, 0, "DEVICEFOLDER"},
    {DATA_OBJECT_LIST, 0, "DISKFOLDER"},
    {DATA_BOOL_LIST, 50, "CARDLIST"},
    {DATA_OBJECT_LIST, 0, "BANKDEVICE"},
    {DATA_INT, 0, "BANKBIT"},
    {DATA_OBJECT_LIST, 3, "POWERSOCKET"},
    {DATA_STRING_LIST, 0, "POWERSOCKETNAME"},
    {DATA_OBJECT_LIST, 5, "POWERPOCKET"},
    {DATA_OBJECT_LIST, 1, "MAINSLOT"},
    {DATA_OBJECT_LIST, 5, "MAINPOCKET"},
    {DATA_OBJECT_LIST, 1, "SUBSLOT"},
    {DATA_BOOL_LIST, 1024, "BASE_FLAG"},
    {DATA_BOOL_LIST, 12, "BASE_FLAGFOLDER"},
    {DATA_INT_LIST, 16, "BASE_COUNTER"},
    {DATA_BOOL_LIST, 16, "BASE_ISUSE"},
    {DATA_INT_LIST, 16, "BASE_LEVEL"},
    {DATA_INT_LIST, 16, "BASE_EXP"},
    {DATA_INT_LIST, 144, "BASE_SKILL"},
    {DATA_INT_LIST, 176, "BASE_UPCNT"},
    {DATA_INT_LIST, 11, "UPDATA"},
    {DATA_INT_LIST, 7, "DOWNDATA"},
    {DATA_END, 0, ""}
};
int g_initialBaseLevel = 1;
int g_initialBaseSkill = 1;
const char *g_initialWeaponFields[3] = { "INI_WEAPON1", "INI_WEAPON2", "INI_WEAPON3" };
int g_growthBandMaxLevel[10] = { 5, 10, 20, 30, 50, 70, 110, 150, 230, 999 };
int g_pointGrowthBandBase[10] = { 0, 40, 140, 640, 1440, 3840, 7440, 17840, 25040, 34640 };
int g_growthBandStartLevel[10] = { 1, 5, 10, 20, 30, 50, 70, 110, 150, 230 };
int g_pointGrowthBandRate[10] = { 10, 20, 50, 80, 120, 180, 260, 180, 120, 80 };
int g_attributeGrowthBandBase[10] = { 0, 40, 85, 165, 235, 355, 455, 615, 735, 895 };
int g_attributeGrowthBandRate[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
const char *g_attributeInitialFields[5] = { "STR_INI", "AC_INI", "INT_INI", "MND_INI", "DEX_INI" };
const char *g_attributeGrowthFields[5] = { "STR_GROW", "AC_GROW", "INT_GROW", "MND_GROW", "DEX_GROW" };
const char *g_techniqueFields[6] = { "TECH1", "TECH2", "TECH3", "TECH4", "TECH5", "TECH6" };
const char *g_techniqueLevelFields[6] = { "TECH1_LEVEL", "TECH2_LEVEL", "TECH3_LEVEL", "TECH4_LEVEL", "TECH5_LEVEL", "TECH6_LEVEL" };
const char *g_techniqueSkillFields[6][5] = {
    {"TECH1_SKILL1", "TECH1_SKILL2", "TECH1_SKILL3", "TECH1_SKILL4", "TECH1_SKILL5"},
    {"TECH2_SKILL1", "TECH2_SKILL2", "TECH2_SKILL3", "TECH2_SKILL4", "TECH2_SKILL5"},
    {"TECH3_SKILL1", "TECH3_SKILL2", "TECH3_SKILL3", "TECH3_SKILL4", "TECH3_SKILL5"},
    {"TECH4_SKILL1", "TECH4_SKILL2", "TECH4_SKILL3", "TECH4_SKILL4", "TECH4_SKILL5"},
    {"TECH5_SKILL1", "TECH5_SKILL2", "TECH5_SKILL3", "TECH5_SKILL4", "TECH5_SKILL5"},
    {"TECH6_SKILL1", "TECH6_SKILL2", "TECH6_SKILL3", "TECH6_SKILL4", "TECH6_SKILL5"}
};
const char *g_elementNames[4] = { "fire", "ice", "thunder", "dark" };
const char *g_resistanceFields[5] = { "RES_FIRE", "RES_ICE", "RES_THUNDER", "RES_DARK", "RES_POISON" };
const char *g_elementResistanceFields[4] = { "RES_FIRE", "RES_ICE", "RES_THUNDER", "RES_DARK" };
short g_skillGainTable[4][21][3] = {
    {
        {10, 5, 12}, {13, 7, 16}, {16, 9, 21}, {21, 12, 27}, {28, 15, 35}, {37, 20, 46}, {48, 26, 60},
        {62, 34, 78}, {81, 44, 101}, {106, 58, 132}, {132, 72, 165}, {165, 91, 207}, {207, 113, 258}, {258, 142, 323},
        {323, 177, 404}, {404, 222, 505}, {505, 278, 632}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}
    },
    {
        {5, 2, 6}, {6, 3, 8}, {8, 4, 10}, {10, 6, 13}, {14, 7, 17}, {18, 10, 23}, {24, 13, 30},
        {31, 17, 39}, {40, 22, 50}, {53, 29, 66}, {66, 36, 82}, {82, 45, 103}, {103, 56, 129}, {129, 71, 161},
        {161, 88, 202}, {202, 111, 252}, {252, 139, 316}, {316, 173, 395}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}
    },
    {
        {2, 1, 3}, {3, 1, 4}, {4, 2, 5}, {5, 3, 6}, {7, 4, 8}, {9, 5, 11}, {12, 7, 15},
        {15, 9, 19}, {20, 12, 25}, {26, 15, 33}, {33, 19, 41}, {41, 24, 51}, {51, 31, 64}, {64, 38, 80},
        {80, 48, 101}, {101, 60, 126}, {126, 75, 158}, {158, 94, 197}, {205, 123, 256}, {0, 0, 0}, {0, 0, 0}
    },
    {
        {1, 0, 1}, {1, 0, 2}, {2, 1, 2}, {2, 1, 3}, {3, 2, 4}, {4, 2, 5}, {6, 3, 7},
        {7, 4, 9}, {10, 6, 12}, {13, 7, 16}, {16, 9, 20}, {20, 12, 25}, {25, 15, 32}, {32, 19, 40},
        {40, 24, 50}, {50, 30, 63}, {63, 37, 79}, {79, 47, 98}, {102, 61, 128}, {128, 77, 160}, {160, 96, 200}
    }
};
short g_skillGainThresholds[21] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 100, 300, 500, 1000, 2000, 3000, 4000, 6000, 10000 };
const char *g_weaponGrowFields[6] = { "BLUNT_GROW", "SLASH_GROW", "STAB_GROW", "BASH_GROW", "SHOT_GROW", "CRUSH_GROW" };
int g_raiseFirstValue[5] = { 59, 68, 77, 86, 95 };
int g_raiseSecondValue[5] = { 100, 400, 1600, 3200, 6400 };
unsigned char g_initialBaseFlag960 = 1;
unsigned char g_speciesUsedMark = 1;
unsigned char g_boolListSetValue = 1;
}
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
extern "C" void beNDMWGameRam_BuildDataList(beNDMWGameRam *self, igObjectList *out, const DataLayoutEntry *layout);
/* Owning stack reference to one new item record, released at the end of each loop pass. */
class ItemRef {
public:
    igObject *p;
    ItemRef(igObject *o) : p(o) {}
    ~ItemRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void beNDMWGameRam_ResetPlayer(beNDMWGameRam *self, int player);
extern "C" igObject *beDataObjListList_Create(int);
extern "C" int beBaseInfoManager_Start(beNDMWGameRam *);
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
extern "C" void beNDMWGameRam_Start(beNDMWGameRam *self);
/* reference-counted engine object header: refcount word at +4 */
typedef struct RefCountedHeader { int p0; unsigned refs; } RefCountedHeader;
/* Object-reference list header: count at +8, capacity at +12, buffer at +16. */
typedef struct ObjectRefList { char p[8]; int count; int cap; RefCountedHeader **data; } ObjectRefList;
extern "C" void beNDMWGameRam_Stop(beNDMWGameRam *self);
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
extern "C" void beNDMWGameRam_Prepare(beNDMWGameRam *self);
extern "C" beNDMWGameRamInfo *beNDMWGameRamInfo_Create(int);
extern "C" beNDMWGameRamInfoRam *beNDMWGameRamInfoRam_Create(int);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, beNDMWGameRamInfoRam *, const void *);
extern "C" int kIGMemoryPoolHandleUser1[4];
/* Owning stack reference to the info's ram object created here, released on scope exit. */
class RamRef {
public:
    beNDMWGameRamInfoRam *p;
    RamRef(beNDMWGameRamInfoRam *o) : p(o) {}
    ~RamRef() { beNDMWGameRamInfoRam *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" int beNDMWGameRam_AddInfo(beNDMWGameRam *self);
extern "C" int g_beNDMWGameRam_metaObject[4];
extern "C" int GETDATABASE_3[4];
extern "C" int shinka_2[4];
extern "C" int DATABASE_3[4];
extern "C" int g_stringPool[4];
extern "C" int beNDMWGameRam_FindSpecies(beNDMWGameRam *self, const char *modelName);
typedef struct PropertyRecord { char header[12]; void *value; } PropertyRecord;
extern "C" PropertyRecord *igProperty_GetRecordString(void *, const void *);
extern "C" igObject * beMessenger_GetObject(...);
extern "C" void beNDMWGameRam_SelectSpecies(beNDMWGameRam *self, int index, int species);
extern "C" void beNDMWGameRam_StoreSpecies(beNDMWGameRam *self, int player_index);
struct RecoveryTarget { int word0; int references;
 static void release(RecoveryTarget *object) {
  if(object) {
   --object->references;
   if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
    igObject_Destroy(object);
  }
 }
};
extern "C" void beNDMWLoadIntf2_igObject_Retain(void *);
template<int I> class RecoveryRef { public:
 void *value;
 RecoveryRef(void *p, bool retain):value(p) { if(retain) beNDMWLoadIntf2_igObject_Retain(value); }
 RecoveryRef(const RecoveryRef &other):value(other.value) { beNDMWLoadIntf2_igObject_Retain(value); }
 ~RecoveryRef() { RecoveryTarget::release((RecoveryTarget *)value); }
};
extern "C" void beNDMWGameRam_GiveInitialWeapons(beNDMWGameRam *self, int index);
extern "C" IntProperty * igProperty_GetRecord(...);
extern "C" StringListProperty *igProperty_GetRecordStringList(void *, const char *);
extern "C" int StringList_AppendRetained(int, const StringRef &);
extern "C" void beNDMWGameRam_EquipWeapon(beNDMWGameRam *self, int index, int apply);
extern "C" unsigned char beNDMWGameRam_HasUsableWeapon(beNDMWGameRam *self, int index, int species);
extern "C" BoolProperty *igProperty_GetRecordByte(int, const void *);
extern "C" void beNDMWGameRam_JoinPlayer(beNDMWGameRam *self, int index, const char *modelName);
extern "C" int beFont_ConvertToUnicode(beUnicodeObj **, int, int);
extern "C" int beUnicodeObj_AllocateBuffer(beUnicodeObj *, int);
extern "C" beUnicodeObj *beUnicodeObj_Create(int);
extern "C" int g_beFont_metaObject[4];
extern "C" void beNDMWGameRam_JoinPlayerWithName(beNDMWGameRam *self, int index, void *modelName, StringRef name);
extern "C" void beNDMWGameRam_JoinPlayerWithUnicodeName(beNDMWGameRam *self, int index, void *modelName, RecoveryRef<0> name);
extern "C" void beNDMWGameRam_LeavePlayer(beNDMWGameRam *self, int index);
extern "C" int beNDMWGameRam_ChangeHp(beNDMWGameRam *self, int player_index, int delta, int absolute);
extern "C" void beNDMWGameRam_ChangeMp(beNDMWGameRam *self, int player_index, int delta);
/* The flat field is const: its read is created before the *out reload so the register colouring puts
 * the field in a0 and the running total in v1. */
struct BonusItem { char pad[20]; const int flat; };
extern "C" void beNDMWGameRam_AddMainSlotBonus(beNDMWGameRam *self, void *player, int *total, const char *name, int withFlat);
struct beNDMWItemCountView { beNDMWItemBase base; unsigned int _count; };
typedef igObject Ref;
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
 * modifiers are applied on top of the database/UPDATA/DOWNDATA base values. "MHP"/MMP are clamped to
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
extern "C" char GETDATABASE_4[];
extern "C" char pcTech_2[];
extern "C" char DATABASE_4[];
extern "C" void beNDMWItemWaza_Set(igObject *, int, int);
extern "C" igObject *beNDMWItemWaza_Create(int);
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
extern "C" int beNDMWGameRam_igStringRefList_GetData(igDataList *p);
extern "C" int DataList_GetWordAt_00406dd0(igDataList *list, int index);
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
extern "C" ObjectRefTarget **beNDMWGameRam_igSmartPointer_beDataBase_Assign(ObjectRefTarget **destination,ObjectRefTarget *incoming);
extern "C" int beNDMWGameRam_igBoolList_GetData(igUnsignedCharList *p);
extern "C" int beNDMWGameRam_beDataObjInt_GetData(beDataObjInt *p);
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
                for (i1 = 0; i1 < n1; i1++) ListStoreAt(d1, i1, 0);
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
                for (int i3 = 0; i3 < n3; i3++) ListStoreAt(d3, i3, (unsigned char)0);
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
                for (int i7 = 0; i7 < n7; i7++) ListStoreAt(d7, i7, 0.0f);
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
        levels = (igObjectList *)((igObject **)((void *)igProperty_GetRecordIntList(data.p, "BASE_LEVEL")))[3];
        if (levels->_count != 0 && species >= 0 && species < levels->_count)
            ((int *)levels->_data)[species] = g_initialBaseLevel;
    }
    for (skillSpecies = 0; skillSpecies < 16; skillSpecies++) {
        for (skill = 0; skill < 9; skill++) {
            skills = (igObjectList *)((igObject **)((void *)igProperty_GetRecordIntList(data.p, "BASE_SKILL")))[3];
            index = skill + skillSpecies * 9;
            if (skills->_count != 0 && index >= 0 && index < skills->_count)
                ((int *)skills->_data)[index] = g_initialBaseSkill;
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
        igObject **folder = (igObject **)igProperty_GetRecordFolder(playerData, "DISKFOLDER");
        ObjectList_AppendRetained(folder[3], diskItem);
    }
    flags = (igObjectList *)((igObject **)igProperty_GetRecordArray(data.p, "BASE_FLAG"))[3];
    if (flags->_count != 0) {
        if (flags->_count > 960)
            ((unsigned char *)flags->_data)[960] = g_initialBaseFlag960;
    }
    storePlayerData(self, player, data);
}

void beNDMWGameRam_Start(beNDMWGameRam *self) {
    int player;
    int allocator;
    int playersAllocator;
    igObject *created;

    beBaseInfoManager_Start(self);
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

void beNDMWGameRam_Stop(beNDMWGameRam *self) {
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

void beNDMWGameRam_Prepare(beNDMWGameRam *self) {
    RefRelease::rel(self->_dBShinka);
    RefRelease::rel(self->_dBPcTech);
    RefRelease::rel(self->_dBWeapon);
    RefRelease::rel(self->_dBArmor1);
    RefRelease::rel(self->_dBArmor2);
    RefRelease::rel(self->_dBAbChip);
    RefRelease::rel(self->_dBEnemy);
    RefRelease::rel(self->_dBEneatk);
}

int beNDMWGameRam_AddInfo(beNDMWGameRam *self) {
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
        igNamedObject_SetName(info.p, "gameram");
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
        beMessenger_RegisterReceiverFromInfo(self->_messenger, ram.p, "GAMERAM");
    }
    return 0;
}

void beNDMWGameRam_UpdateRam(void)
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
        if (beDataBase_GetRecordString(StatHelpers::shinka(self), species, "MODEL_NAME") == interned) {
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
    igProperty_GetRecord(player, "LEVEL");
    ((PropertyRecord *)igProperty_GetRecord(player, "DIGIMONNO"))->value = (void *)species;
    modelName = ((int)beDataBase_GetRecordString(StatHelpers::shinka(self), species, "MODEL_NAME"));
    nameRecord = igProperty_GetRecordString((void *)player, "DIGIMONNAME");
    interned = ((int)StringPool_Intern(SharedStringPool::get(), modelName));
    oldName = (int)nameRecord->value;
    if (oldName != 0) {
        int *p = (int *)(oldName - 8);
        int c = *(int *)(oldName - 4) - 1;
        *(int *)(oldName - 4) = c;
        if (c == 0) StringChunk_ReleaseHeader(*p, p);
    }
    nameRecord->value = (void *)interned;
    baseLevels = (igIntList *)((PropertyRecord *)igProperty_GetRecordIntList(player, "BASE_LEVEL"))->value;
    level = ((int *)baseLevels->_data)[species];
    ((PropertyRecord *)igProperty_GetRecord(player, "LEVEL"))->value = (void *)level;
    baseExps = (igIntList *)((PropertyRecord *)igProperty_GetRecordIntList(player, "BASE_EXP"))->value;
    value = ((int *)baseExps->_data)[species];
    ((PropertyRecord *)igProperty_GetRecord(player, "EXP"))->value = (void *)value;
    /* matching construct: skillBase/upcntBase hoisted into locals, else MWCC strength-reduces the index */
    skillBase = species * 9;
    skill = 0;
    skillOffset = 0;
    do {
        baseSkills = (igIntList *)((PropertyRecord *)igProperty_GetRecordIntList(player, "BASE_SKILL"))->value;
        skillValue = ((int *)baseSkills->_data)[skillBase + skill];
        skills = (igIntList *)((PropertyRecord *)igProperty_GetRecordIntList(player, "SKILL", baseSkills))->value;
        skillCount = skills->_count;
        if (skillCount != 0 && skill >= 0 && skill < skillCount) ((int *)(skills->_data + skillOffset))[0] = skillValue;
        skill += 1;
        skillOffset += 4;
    } while (skill < 9);
    upcntBase = species * 11;
    upcnt = 0;
    upcntOffset = 0;
    do {
        baseUpcnts = (igIntList *)((PropertyRecord *)igProperty_GetRecordIntList(player, "BASE_UPCNT"))->value;
        value = ((int *)baseUpcnts->_data)[upcntBase + upcnt];
        upcnts = (igIntList *)((PropertyRecord *)igProperty_GetRecordIntList(player, "UPCNT", baseUpcnts))->value;
        upcntCount = upcnts->_count;
        if (upcntCount != 0 && upcnt >= 0 && upcnt < upcntCount) ((int *)(upcnts->_data + upcntOffset))[0] = value;
        upcnt += 1;
        upcntOffset += 4;
    } while (upcnt < 11);
    if (index == 0) {
        flags = (igObject *)((PropertyRecord *)igProperty_GetRecordArray(player, "BASE_FLAG"))->value;
        commonFlags = ((PropertyRecord *)igProperty_GetRecordArray(self->_commonDataList, "FLAG"));
        if (flags != 0) flags->_refCount = flags->_refCount + 1;
        released = (igObject *)commonFlags->value;
        RELO(released)
        commonFlags->value = flags;
        flagFolder = (igObject *)((PropertyRecord *)igProperty_GetRecordArray(player, "BASE_FLAGFOLDER"))->value;
        commonFlagFolder = ((PropertyRecord *)igProperty_GetRecordArray(self->_commonDataList, "FLAGFOLDER"));
        if (flagFolder != 0) flagFolder->_refCount = flagFolder->_refCount + 1;
        released = (igObject *)commonFlagFolder->value;
        RELO(released)
        commonFlagFolder->value = flagFolder;
        counter = (igObject *)((PropertyRecord *)igProperty_GetRecordIntList(player, "BASE_COUNTER"))->value;
        commonCounter = ((PropertyRecord *)igProperty_GetRecordIntList(self->_commonDataList, "COUNTER"));
        if (counter != 0) counter->_refCount = counter->_refCount + 1;
        released = (igObject *)commonCounter->value;
        RELO(released)
        commonCounter->value = counter;
    }
}

/* Current player record -> BASE_* save arrays, the mirror of beNDMWGameRam_SelectSpecies: LEVEL
 * and EXP go to the species' slot of "BASE_LEVEL" / "BASE_EXP", SKILL[9] and UPCNT[11] to
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
    species = ((IntProperty *)igProperty_GetRecord(player, "DIGIMONNO"))->value;
    value = ((IntProperty *)igProperty_GetRecord(player, "LEVEL"))->value;
    level_list = ((IntListProperty *)igProperty_GetRecordIntList(player, "BASE_LEVEL"))->list;
    if (level_list->_count != 0 && species >= 0 && species < level_list->_count)
        ((int *)level_list->_data)[species] = value;
    value = ((IntProperty *)igProperty_GetRecord(player, "EXP"))->value;
    exp_list = ((IntListProperty *)igProperty_GetRecordIntList(player, "BASE_EXP"))->list;
    if (exp_list->_count != 0 && species >= 0 && species < exp_list->_count)
        ((int *)exp_list->_data)[species] = value;
    skill_base = species * 9;
    for (skill_index = 0; skill_index < 9; ++skill_index) {
        skill = ((int *)((IntListProperty *)igProperty_GetRecordIntList(player, "SKILL"))->list->_data)[skill_index];
        base_array = ((IntListProperty *)igProperty_GetRecordIntList(player, "BASE_SKILL"));
        if (base_array->list->_count != 0 && skill_base + skill_index >= 0 &&
            skill_base + skill_index < base_array->list->_count)
            ((int *)base_array->list->_data)[skill_base + skill_index] = skill;
    }
    upcnt_base = species * 11;
    for (upcnt_index = 0; upcnt_index < 11; ++upcnt_index) {
        upcnt = ((int *)((IntListProperty *)igProperty_GetRecordIntList(player, "UPCNT"))->list->_data)[upcnt_index];
        base_array = ((IntListProperty *)igProperty_GetRecordIntList(player, "BASE_UPCNT"));
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
    const char **field;
    int c;
    int player;
    int species;
    player = ((int *)((igObjectList *)self->_playerDataListList)->_data)[index];
    devices = ((ObjectListProperty *)igProperty_GetRecordFolder(player, "DEVICEFOLDER"))->list;
    species = ((IntProperty *)((void *)igProperty_GetRecord(player, "DIGIMONNO")))->value;
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
    igObjectList *pocket = ((ObjectListProperty *)igProperty_GetRecordFolder(player, "DEVICEFOLDER"))->list;

    if ((apply & 0xff) == 0) {
        igObjectList *sockets = ((ObjectListProperty *)igProperty_GetRecordFolder(player, "POWERSOCKET"))->list;
        igStringRefList *names = igProperty_GetRecordStringList(player, "POWERSOCKETNAME")->list;
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
                const char *model = beNDMWItemBase_GetRecordString(item, self, "MODEL");
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
        int species = igProperty_GetRecord(player, "DIGIMONNO")->value;
        int bit;
        igIntList *skills;
        igStringRefList *names;
        int fits, skillNo;
        igObjectList *sockets;
        skills = ((IntListProperty *)igProperty_GetRecordIntList(player, "SKILL"))->list;
        sockets = ((ObjectListProperty *)igProperty_GetRecordFolder(player, "POWERSOCKET"))->list;
        names = igProperty_GetRecordStringList(player, "POWERSOCKETNAME")->list;
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
                fits = bit & beNDMWItemBase_GetRecordInt(item, self, "SOUBI");
                skillNo = beNDMWItemBase_GetRecordInt(item, self, "SKILL");
                int need = beNDMWItemBase_GetRecordInt(item, self, "SKILLPOINT");
                if (fits != 0 && ((int *)skills->_data)[skillNo] >= need &&
                    (best < 0 || bestValue < beNDMWItemBase_GetRecordInt(item, self, "TSUYOSA"))) {
                    bestValue = beNDMWItemBase_GetRecordInt(item, self, "TSUYOSA");
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
            const char *model = beNDMWItemBase_GetRecordString(chosen, self, "MODEL");
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
    devices = ((ObjectListProperty *)igProperty_GetRecordFolder(player, "DEVICEFOLDER"))->list;
    {
    int current = ((IntProperty *)igProperty_GetRecord(player, "DIGIMONNO"))->value;
    if (current == species) {
        skills = ((IntListProperty *)igProperty_GetRecordIntList(player, "SKILL"))->list;
        base = 0;
    } else {
        skills = ((IntListProperty *)igProperty_GetRecordIntList(player, "BASE_SKILL"))->list;
        base = species * 9;
    }
    }
    mask = 1 << species;
    count = devices->_count;
    for (i = 0; i < count; i++) {
        beNDMWItemBase *item = ((beNDMWItemBase **)devices->_data)[i];
        if (item->_kindNo == 0) {
            int fits = mask & beNDMWItemBase_GetRecordInt(item, self, "SOUBI");
            int skillNo = beNDMWItemBase_GetRecordInt(item, self, "SKILL");
            int need = beNDMWItemBase_GetRecordInt(item, self, "SKILLPOINT");
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
    isUse = igProperty_GetRecordByte(player, "ISUSE");
    isUse->value = 1;
    used = ((DataListProperty *)igProperty_GetRecordArray(player, "BASE_ISUSE"))->list;
    if (used->_count != 0 && species >= 0 && species < used->_count) {
        *(char *)(species + used->_data) = g_speciesUsedMark;
    }
    joined = 0;
    i = 0;
    offset = 0;
    do {
        if (igProperty_GetRecordByte(*(int *)(((igObjectListList *)self->_playerDataListList)->_data + offset), "ISUSE")->value != 0) {
            joined += 1;
        }
        i += 1;
        offset += 4;
    } while (i < 4);
    ((IntProperty *)igProperty_GetRecord(common, "NINZU"))->value = joined;
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
    names = ((ObjectListProperty *)igProperty_GetRecordFolder(player, "PLAYERNAME"))->list;
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
    nameFolder = (ObjectListProperty *)igProperty_GetRecordFolder(((int *)(((igObjectList *)self->_playerDataListList)->_data))[index], "PLAYERNAME");
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
    igProperty_GetRecordByte(((int *)((igObjectList *)self->_playerDataListList)->_data)[index], "ISUSE")->value = 0;
    joined = 0;
    i = 0;
    offset = 0;
    do {
        if (igProperty_GetRecordByte(((int *)(((igObjectList *)self->_playerDataListList)->_data + offset))[0], "ISUSE")->value != 0) {
            joined += 1;
        }
        i += 1;
        offset += 4;
    } while (i < 4);
    ((IntProperty *)igProperty_GetRecord(common, "NINZU"))->value = joined;
}

/* HP update. Returns 0 when a delta is applied to a dead player (HP 0), else 1. */
int beNDMWGameRam_ChangeHp(beNDMWGameRam *self, int player_index, int delta, int absolute)
{
    int hp;
    int player;
    int max_hp;

    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[player_index];
    max_hp = ((IntProperty *)igProperty_GetRecord(player, "MHP"))->value;
    hp = ((IntProperty *)igProperty_GetRecord(player, "HP"))->value;
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
    ((IntProperty *)igProperty_GetRecord(player, "HP"))->value = hp;
    beMessenger_SelectReceivers(self->_messenger, "METERCTRL", "hpmt", player_index);
    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)hp / (float)max_hp);
    beMessenger_DispatchSelected(self->_messenger, "SETPERCENT");
    beMessenger_SelectReceivers(self->_messenger, "NUMBERCTRL", "hpnm", player_index);
    beMessenger_AppendInt(self->_messenger, hp);
    beMessenger_DispatchSelected(self->_messenger, "SETVALUE");
    return 1;
}

/* MP update by delta. */
void beNDMWGameRam_ChangeMp(beNDMWGameRam *self, int player_index, int delta)
{
    int mp;
    int player;
    int max_mp;

    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[player_index];
    max_mp = ((IntProperty *)igProperty_GetRecord(player, "MMP"))->value;
    mp = ((IntProperty *)igProperty_GetRecord(player, "MP"))->value;
    mp += delta;
    if (mp < 0)
        mp = 0;
    if (mp > max_mp)
        mp = max_mp;
    ((IntProperty *)igProperty_GetRecord(player, "MP"))->value = mp;
    beMessenger_SelectReceivers(self->_messenger, "METERCTRL", "mpmt", player_index);
    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)mp / (float)max_mp);
    beMessenger_DispatchSelected(self->_messenger, "SETPERCENT");
    beMessenger_SelectReceivers(self->_messenger, "NUMBERCTRL", "mpnm", player_index);
    beMessenger_AppendInt(self->_messenger, mp);
    beMessenger_DispatchSelected(self->_messenger, "SETVALUE");
}

void beNDMWGameRam_AddPowerSocketBonus(int self, int player, int *total, const char *name, int withRevision) {
    beNDMWItemRevisionBase *item;
    if (((igObjectList *)((beDataObjObjectList *)igProperty_GetRecordFolder(player, "POWERSOCKET"))->_data)->_count != 0) {
        item = ((beNDMWItemRevisionBase **)((igObjectList *)((beDataObjObjectList *)igProperty_GetRecordFolder(player, "POWERSOCKET"))->_data)->_data)[0];
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
    count = ((ObjectListProperty *)igProperty_GetRecordFolder(player, "POWERPOCKET"))->list->_count;
    i = 0;
    if (0 < count) {
        do {
            item = ((int *)((ObjectListProperty *)igProperty_GetRecordFolder(player, "POWERPOCKET"))->list->_data)[i];
            if (item != 0) {
                *total += beNDMWItemBase_GetRecordInt(item, self, name);
            }
            i += 1;
        } while (i < count);
    }
}

void beNDMWGameRam_AddMainSlotBonus(beNDMWGameRam *self, void *player, int *total, const char *name, int withFlat) {
    beNDMWItemBase *item;
    if (((ObjectListProperty *)igProperty_GetRecordFolder(player, (const char *)"MAINSLOT"))->list->_count != 0) {
        item = ((beNDMWItemBase **)((ObjectListProperty *)igProperty_GetRecordFolder(player, (const char *)"MAINSLOT"))->list->_data)[0];
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
    count = ((ObjectListProperty *)igProperty_GetRecordFolder(player, "MAINPOCKET"))->list->_count;
    for (i = 0; i < count; i++) {
        item = ((int *)((ObjectListProperty *)igProperty_GetRecordFolder(player, "MAINPOCKET"))->list->_data)[i];
        if (item != 0) {
            *total += beNDMWItemBase_GetRecordInt(item, self, name);
        }
    }
}

void beNDMWGameRam_AddSubSlotBonus(int self, int player, int *total, const char *name, int withAbility) {
    beNDMWItemBase *item; int bonus;
    if (((ObjectListProperty *)igProperty_GetRecordFolder(player, "SUBSLOT"))->list->_count != 0) {
        item = *(beNDMWItemBase **)((ObjectListProperty *)igProperty_GetRecordFolder(player, "SUBSLOT"))->list->_data;
        if (item != 0) {
            bonus = beNDMWItemBase_GetRecordInt(item, self, name); *total += bonus;
            if (withAbility != 0 && strcmp(((char *)beNDMWItemBase_GetRecordString(item, self, "SHUSEINOURYOKU")), name) == 0) {
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
        record = igProperty_GetRecord(player, ("DIGIMONNO"))->value;
        upcnts = igProperty_GetRecordIntList(player, "UPCNT")->list;
        base = 0;
        level = igProperty_GetRecord(player, "LEVEL")->value;
    } else {
        upcnts = igProperty_GetRecordIntList(player, "BASE_UPCNT")->list;
        base = record * 11;
        level = igProperty_GetRecordIntList(player, ("BASE_LEVEL"))->list->values[record];
    }
    if (isHp != 0) {
        initial = beDataBase_GetRecordInt(StatHelpers::shinka(self), record, "MHP_INI");
        growth = beDataBase_GetRecordInt(StatHelpers::shinka(self), record, "MHP_GROW");
        bonus = upcnts->values[base];
    } else {
        initial = beDataBase_GetRecordInt(StatHelpers::shinka(self), record, "MMP_INI");
        growth = beDataBase_GetRecordInt(StatHelpers::shinka(self), record, "MMP_GROW");
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
        record = igProperty_GetRecord(player, ("DIGIMONNO"))->value;
        upcnts = igProperty_GetRecordIntList(player, "UPCNT")->list;
        base = 0;
        level = igProperty_GetRecord(player, "LEVEL")->value;
    } else {
        upcnts = igProperty_GetRecordIntList(player, "BASE_UPCNT")->list;
        base = record * 11;
        level = igProperty_GetRecordIntList(player, ("BASE_LEVEL"))->list->values[record];
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
    int species = RecomputeHelpers::GetProp(player, "DIGIMONNO");
    int level = RecomputeHelpers::GetProp(player, "LEVEL");
    unsigned char first = 0;

    /* "MHP" / "HP" */
    int mhp = beNDMWGameRam_CalcMaxPoints(self, index, -1, 1);
    mhp += igProperty_GetRecordIntList(player, "UPDATA")->list->values[6];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &mhp, "MAXHP", 0);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &mhp, "MAXHP", 0);
    }
    if (mhp > 99999) mhp = 99999;
    igProperty_GetRecord(player, "MHP")->value = mhp;
    int curHp = igProperty_GetRecord(player, "HP")->value;
    if (curHp == 0) first = 1;
    if (curHp == 0 || mhp < curHp) igProperty_GetRecord(player, "HP")->value = mhp;

    int mmp = beNDMWGameRam_CalcMaxPoints(self, index, -1, 0);
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &mmp, "MAXMP", 0);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &mmp, "MAXMP", 0);
    }
    if (mmp > 99999) mmp = 99999;
    igProperty_GetRecord(player, "MMP")->value = mmp;
    int curMp = igProperty_GetRecord(player, "MP")->value;
    if (first || mmp < curMp) igProperty_GetRecord(player, "MP")->value = mmp;

    int tsuyosa = beNDMWGameRam_CalcAttribute(self, index, -1, 0);
    tsuyosa += igProperty_GetRecordIntList(player, "UPDATA")->list->values[4];
    tsuyosa -= igProperty_GetRecordIntList(player, "DOWNDATA")->list->values[4];
    if (apply) {
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &tsuyosa, "TSUYOSA", 1);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &tsuyosa, "TSUYOSA");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &tsuyosa, "TSUYOSA", 1);
    }
    CLAMP_ATTR(tsuyosa)
    igProperty_GetRecord(player, "TSUYOSA")->value = tsuyosa;

    int mamori = beNDMWGameRam_CalcAttribute(self, index, -1, 1);
    mamori += igProperty_GetRecordIntList(player, "UPDATA")->list->values[5];
    mamori -= igProperty_GetRecordIntList(player, "DOWNDATA")->list->values[5];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &mamori, "MAMORI", 1);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &mamori, "MAMORI", 1);
    }
    CLAMP_ATTR(mamori)
    igProperty_GetRecord(player, "MAMORI")->value = mamori;

    int kashikosa = beNDMWGameRam_CalcAttribute(self, index, -1, 2);
    if (apply) {
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &kashikosa, "KASHIKOSA", 0);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &kashikosa, "KASHIKOSA");
        beNDMWGameRam_AddMainSlotBonus(self, player, &kashikosa, "KASHIKOSA", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &kashikosa, "KASHIKOSA");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &kashikosa, "KASHIKOSA", 1);
    }
    CLAMP_ATTR(kashikosa)
    igProperty_GetRecord(player, "KASHIKOSA")->value = kashikosa;

    int seishin = beNDMWGameRam_CalcAttribute(self, index, -1, 3);
    if (apply) {
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &seishin, "SEISHIN", 0);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &seishin, "SEISHIN");
        beNDMWGameRam_AddMainSlotBonus(self, player, &seishin, "SEISHIN", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &seishin, "SEISHIN");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &seishin, "SEISHIN", 0);
    }
    CLAMP_ATTR(seishin)
    igProperty_GetRecord(player, "SEISHIN")->value = seishin;

    int subayasa = beNDMWGameRam_CalcAttribute(self, index, -1, 4);
    subayasa += igProperty_GetRecordIntList(player, "UPDATA")->list->values[0];
    subayasa -= igProperty_GetRecordIntList(player, "DOWNDATA")->list->values[0];
    if (apply) {
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &subayasa, "SUBAYASA", 0);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &subayasa, "SUBAYASA");
        beNDMWGameRam_AddMainSlotBonus(self, player, &subayasa, "SUBAYASA", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &subayasa, "SUBAYASA");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &subayasa, "SUBAYASA", 1);
    }
    CLAMP_ATTR(subayasa)
    igProperty_GetRecord(player, "SUBAYASA")->value = subayasa;

    int fire = beDataBase_GetRecordInt(RecomputeHelpers::shinka(self), species, "RES_FIRE");
    fire += igProperty_GetRecordIntList(player, "UPCNT")->list->values[7];
    fire += igProperty_GetRecordIntList(player, "UPDATA")->list->values[7];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &fire, "RES_FIRE", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &fire, "RES_FIRE");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &fire, "RES_FIRE", 1);
    }
    CLAMP_ATTR(fire)
    igProperty_GetRecord(player, "HONOOTEIKO")->value = fire;
    int ice = beDataBase_GetRecordInt(RecomputeHelpers::shinka(self), species, "RES_ICE");
    ice += igProperty_GetRecordIntList(player, "UPCNT")->list->values[8];
    ice += igProperty_GetRecordIntList(player, "UPDATA")->list->values[8];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &ice, "RES_ICE", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &ice, "RES_ICE");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &ice, "RES_ICE", 1);
    }
    CLAMP_ATTR(ice)
    igProperty_GetRecord(player, "KOORITEIKO")->value = ice;
    int thunder = beDataBase_GetRecordInt(RecomputeHelpers::shinka(self), species, "RES_THUNDER");
    thunder += igProperty_GetRecordIntList(player, "UPCNT")->list->values[9];
    thunder += igProperty_GetRecordIntList(player, "UPDATA")->list->values[9];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &thunder, "RES_THUNDER", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &thunder, "RES_THUNDER");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &thunder, "RES_THUNDER", 1);
    }
    CLAMP_ATTR(thunder)
    igProperty_GetRecord(player, "KAMINARITEIKO")->value = thunder;
    int dark = beDataBase_GetRecordInt(RecomputeHelpers::shinka(self), species, "RES_DARK");
    dark += igProperty_GetRecordIntList(player, "UPCNT")->list->values[10];
    dark += igProperty_GetRecordIntList(player, "UPDATA")->list->values[10];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &dark, "RES_DARK", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &dark, "RES_DARK");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &dark, "RES_DARK", 1);
    }
    CLAMP_ATTR(dark)
    igProperty_GetRecord(player, "YAMITEIKO")->value = dark;

    {
        igObjectList *list = ((ObjectListProperty *)igProperty_GetRecordFolder(player, "WAZALIST"))->list;
        int oldCount = list->_count;
        for (int r = 0; r < oldCount; r++) RecomputeHelpers::release_ref(((igObject **)list->_data)[r]);
        int clearCount = list->_count;
        for (int c = 0; c < clearCount; c++) ((int *)list->_data)[c] = 0;
        list->_count = 0;

        for (int slot = 0; slot < 6; slot++) {
            int tech = beDataBase_GetRecordInt(RecomputeHelpers::shinka(self), species, g_techniqueFields[slot]);
            int skillNo = beDataBase_GetRecordInt(RecomputeHelpers::pctech(self), tech, "SKILL");
            int skillVal = igProperty_GetRecordIntList(player, "SKILL")->list->values[skillNo];
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
    igProperty_GetRecord(player, "NEXTEXP")->value =
        level == 999 ? 0 : level * 200 + (level + 140) * (level * level);

    if (apply) {
        int delay, hitRate, critRate, paralysisRate, evadeRate, guardRate;
        int paralysisResist, poisonResist, bitRate, expRate;
        unsigned char found;
        int luckRate;
        delay = igProperty_GetRecordIntList(player, "DOWNDATA")->list->values[6];
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &delay, "DELAY", 0);
        if (delay > 70) delay = 70;
        igProperty_GetRecord(player, "ATTACKDELAY")->value = delay;
        hitRate = 0;
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &hitRate, "MEICHURITSU", 0);
        igProperty_GetRecord(player, "MEICHURITSU")->value = hitRate;
        critRate = 0;
        critRate += igProperty_GetRecordIntList(player, "UPDATA")->list->values[1];
        critRate -= igProperty_GetRecordIntList(player, "DOWNDATA")->list->values[1];
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &critRate, "CHIMEIRITSU", 0);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &critRate, "CHIMEIRITSU");
        if (critRate <= 0) critRate = 1;
        igProperty_GetRecord(player, "CHIMEIRITSU")->value = critRate;
        paralysisRate = 0;
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &paralysisRate, "MAHIRITSU", 0);
        igProperty_GetRecord(player, "MAHIRITSU")->value = paralysisRate;
        evadeRate = 0;
        evadeRate += igProperty_GetRecordIntList(player, "UPDATA")->list->values[3];
        evadeRate -= igProperty_GetRecordIntList(player, "DOWNDATA")->list->values[3];
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &evadeRate, "CHOHATURITSU");
        if (evadeRate <= 0) evadeRate = 1;
        igProperty_GetRecord(player, "KAIHIRITSU")->value = evadeRate;
        guardRate = 0;
        beNDMWGameRam_AddMainSlotBonus(self, player, &guardRate, "BOUGYORITSU", 0);
        igProperty_GetRecord(player, "BOUGYORITSU")->value = guardRate;
        paralysisResist = 0;
        paralysisResist += igProperty_GetRecordIntList(player, "UPDATA")->list->values[2];
        paralysisResist -= igProperty_GetRecordIntList(player, "DOWNDATA")->list->values[2];
        beNDMWGameRam_AddMainSlotBonus(self, player, &paralysisResist, "MAHITEIKOU", 0);
        if (paralysisResist <= 0) paralysisResist = 1;
        igProperty_GetRecord(player, "MAHITEIKOU")->value = paralysisResist;
        poisonResist = 0;
        beNDMWGameRam_AddMainSlotBonus(self, player, &poisonResist, "DOKUTEIKOU", 0);
        igProperty_GetRecord(player, "DOKUTEIKOU")->value = poisonResist;
        bitRate = 0;
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &bitRate, "BITRITSU", 0);
        igProperty_GetRecord(player, "BITRITSU")->value = bitRate;
        expRate = 0;
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &expRate, "EXPRITSU", 0);
        igProperty_GetRecord(player, "EXPRITSU")->value = expRate;
        luckRate = 0;
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &luckRate, "LUCKRITSU", 0);
        igProperty_GetRecord(player, "LUCKRITSU")->value = luckRate;

        { IntProperty *zokusei = igProperty_GetRecord(player, "ATTACKZOKUSEI"); zokusei->value = -1; }
        found = 0;
        int pocketCount = ((ObjectListProperty *)igProperty_GetRecordFolder(player, "POWERPOCKET"))->list->_count;
        for (int p = 0; p < pocketCount; p++) {
            beNDMWItemBase *pocketItem = ((beNDMWItemBase **)((ObjectListProperty *)igProperty_GetRecordFolder(player, "POWERPOCKET"))->list->_data)[p];
            if (pocketItem) {
                const char *zokuseiName = beNDMWItemBase_GetRecordString(pocketItem, self, "ZOKUSEI");
                for (int element = 0; element < 4; element++) {
                    if (strcmp(zokuseiName, g_elementNames[element]) == 0) {
                        igProperty_GetRecord(player, "ATTACKZOKUSEI")->value = element;
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
            beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &hpDrain, "HPDRAIN");
            igProperty_GetRecord(player, "HPDRAIN")->value = hpDrain;
            mpDrain = 0;
            beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &mpDrain, "MPDRAIN");
            igProperty_GetRecord(player, "MPDRAIN")->value = mpDrain;
        }
        igProperty_GetRecord(player, "CHOHATURITSU")->value =
            igProperty_GetRecord(player, "KAIHIRITSU")->value;
    }

    if (apply) {
        int weaponRec, weaponSkill;
        beNDMWItemBase *firstSocket;
        igObjectList *sockets;
        igStringRefList *names;
        firstSocket = ((beNDMWItemBase **)((ObjectListProperty *)igProperty_GetRecordFolder(player, "POWERSOCKET"))->list->_data)[0];
        weaponRec = 0;
        weaponSkill = 0;
        if (firstSocket) {
            weaponRec = firstSocket->_recNo;
            weaponSkill = beNDMWItemBase_GetRecordInt(firstSocket, self, "SKILL");
        }
        igProperty_GetRecord(player, "WEAPONRECNO")->value = weaponRec;
        igProperty_GetRecord(player, "WEAPONSKILLNO")->value = weaponSkill;

        sockets = ((ObjectListProperty *)igProperty_GetRecordFolder(player, "POWERSOCKET"))->list;
        names = igProperty_GetRecordStringList(player, "POWERSOCKETNAME")->list;
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
                const char *model = beNDMWItemBase_GetRecordString(item, self, "MODEL");
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

    list = ((ObjectListProperty *)igProperty_GetRecordFolder(player, "WAZALIST"))->list;
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
void beNDMWLoadIntf2_igObject_Release(...);
void *igSmartPointer_beNDMWDegiData_Destruct(...);
void beNDMWLoadIntf2_igObjectList_Set(...);
void Vec3f_Copy(...);
int beNDMWLoadIntf2_igObjectList_Get(...);
int beNDMWLoadIntf2_igIntList_GetData(...);
int beNDMWLoadIntf2_Memory_SelectAllocator(...);
void igMatrix44f_Copy(...);
void igMatrix44f_SetIdentity(...);
void *FightCom_GetMetaEnum(...);
void *GameRamMessage_GetMetaEnum(...);
int FUN_0033e9c0(...);
void *beNDMWItemAbilityChip_Create(...);
void *beNDMWItemYellowArmor_Create(...);
void *beNDMWItemBlueArmor_Create(...);
int beNDMWLoadIntf2_beBaseInfoDataList_FindProperty(...);
int ObjectRef_Get_003e92a0(...);
AllocatorValue beNDMWLoadIntf2_beBaseInfoDataList_MakeAllocatorValue(...);
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
extern Vector3 g_vec3Zero[4];
extern char GETMATRIX[];
extern char GETHP[];
extern char GETDATABASE_5[];
extern char DATABASE_5[];
extern char GETDATABASE_6[];
extern char DATABASE_6[];
extern int g_propertyNameField[4];
extern unsigned char g_boolListClearValue;
int beNDMWGameRam_OnMessage(beNDMWGameRam *self, int ram, beMessengerWork *message);
}
extern "C" int igStringRef_Assign(void *, const StringRef &);
/* Experience needed to reach a level: 200 per level below plus a quadratic term. The extra named step
 * (g/f) keeps the retail arithmetic shape (matching construct). */
struct LevelExpCurve { static int g(int d, int x) { return d * 0xC8 + (x + 0x8B) * (d * d); } static int f(int x) { int d = x - 1; return d * 0xC8 + (x + 0x8B) * (d * d); } };
/* matching construct: RAII copied-reference local reproduces the retail unwind table */ class RecoveryCopiedRef { public: void *value; RecoveryCopiedRef(const AllocatorValue &source); ~RecoveryCopiedRef(); };
extern "C" int *beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Assign(void *, const RecoveryCopiedRef &);
/* Gives `obj` a fresh object from the allocator; kept out of line as retail calls it (matching construct). */
struct ObjectRefAssigner { static int *Assign(void *obj, int alloc) { RecoveryCopiedRef c(beNDMWLoadIntf2_beBaseInfoDataList_MakeAllocatorValue(beNDMWLoadIntf2_Memory_SelectAllocator(kIGMemoryPoolHandleUser1, alloc))); return beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Assign(obj, c); } };
/* matching construct: out-of-line helper that reproduces the retail call shape of the BKCHIPNAME string-list store */
struct StringListStore { static void SetAt(igStringRefList *list, int idx, const StringRef &v) { if (list->_count != 0 && idx >= 0 && idx < list->_count) igStringRef_Assign((void *)((char *)beNDMWGameRam_igStringRefList_GetData((igDataList *)list) + idx * 4), v); } };
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
  ((int *)beNDMWLoadIntf2_igIntList_GetData(list))[index] = value;
 }
};
/* The database tables the message handler reads. Each is requested from the database object the first
 * time it is needed and kept in the receiver; the fetched reference goes in through the out-of-line
 * assign call. */
struct MessageDatabases {
    static inline void *PcTech(beNDMWGameRam *self)
    {
        if (beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBPcTech) == 0) {
            beMessenger_SendNamed(self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
            beNDMWGameRam_igSmartPointer_beDataBase_Assign((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)beMessenger_GetObject(self->_messenger, 0));
        }
        return (void *)beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBPcTech);
    }
    /* The table names are passed in so the literals stay in the handler's own string pool. */
    static inline void *Enemy(beNDMWGameRam *self, const char *name)
    {
        if (beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBEnemy) == 0) {
            beMessenger_SendNamed(self->_messenger, &DATABASE_5[0], name, 0, &GETDATABASE_5[0]);
            beNDMWGameRam_igSmartPointer_beDataBase_Assign((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)beMessenger_GetObject(self->_messenger, 0));
        }
        return (void *)beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBEnemy);
    }
    static inline void *Eneatk(beNDMWGameRam *self, const char *name)
    {
        if (beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBEneatk) == 0) {
            beMessenger_SendNamed(self->_messenger, &DATABASE_6[0], name, 0, &GETDATABASE_6[0]);
            beNDMWGameRam_igSmartPointer_beDataBase_Assign((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)beMessenger_GetObject(self->_messenger, 0));
        }
        return (void *)beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBEneatk);
    }
};
/* Reads the message handler repeats: a player's data record and the system's random source. */
struct MessageAccess {
    static inline int Player(beNDMWGameRam *self, int index)
    {
        return beNDMWLoadIntf2_igObjectList_Get(beNDMWGameRam_igSmartPointer_beDataObjListList_Get(&self->_playerDataListList), index);
    }
    static inline RandomNumberDispatch *Random(beNDMWGameRam *self)
    {
        return (RandomNumberDispatch *)beNDMWGameRam_igSmartPointer_igRandomNumber_Get(&((beSystem *)self->_system)->_random);
    }
};
/* The command names of the FIGHTCOM message (g_FightCom_commandNames), by value. */
enum FightComId {
    FIGHTCOM_E2PISHITCHECK,
    FIGHTCOM_P2EISHITCHECK,
    FIGHTCOM_P2EISCRITICAL,
    FIGHTCOM_E2PDAMAGE,
    FIGHTCOM_E2PDAMAGERANK,
    FIGHTCOM_P2EDAMAGE,
    FIGHTCOM_P2EEXPUP,
    FIGHTCOM_E2PSTUNTIME,
    FIGHTCOM_E2PPOISONTIME,
    FIGHTCOM_E2PSLEEPTIME,
    FIGHTCOM_E2PBINDTIME,
    FIGHTCOM_E2PATKDWNTIME,
    FIGHTCOM_E2PPOWDWNTIME,
    FIGHTCOM_P2ESKILLUP,
    FIGHTCOM_P2ESTUNTIME,
    FIGHTCOM_P2EPOISONTIME,
    FIGHTCOM_P2ESLEEPTIME,
    FIGHTCOM_P2EBINDTIME,
    FIGHTCOM_P2EATKDWNTIME,
    FIGHTCOM_P2EPOWDWNTIME,
    FIGHTCOM_P2PKOUKAMAGIC,
    FIGHTCOM_GETPATKZOKUSEI
};
/* The operation word of a CTRLITEM message, and the equipment slots its item names address. */
enum ItemOperation { ITEMOP_SET, ITEMOP_CLR, ITEMOP_IS, ITEMOP_ISMAX, ITEMOP_ISEQUIP, ITEMOP_GET, ITEMOP_ADD };
enum ItemSlot { ITEMSLOT_WEAPON, ITEMSLOT_ARMOR1, ITEMSLOT_ARMOR2, ITEMSLOT_ABCHIP };
/* The command names of the GAMERAM message (g_GameRamMessage_commandNames), by value. */
enum GameRamMessageId {
    GAMERAM_GETCOMMON,
    GAMERAM_GETPLAYER,
    GAMERAM_GETPLAYER1,
    GAMERAM_GETPLAYER2,
    GAMERAM_GETPLAYER3,
    GAMERAM_GETPLAYER4,
    GAMERAM_GAMEDATAINIT,
    GAMERAM_GAMESTART,
    GAMERAM_GAMEREMOVE,
    GAMERAM_ADDHP,
    GAMERAM_ADDMP,
    GAMERAM_RECALCPLAYER,
    GAMERAM_BASE2CURRENT,
    GAMERAM_CURRENT2BASE,
    GAMERAM_WEAPONEQUIPCHECK,
    GAMERAM_WEAPONEQUIPSTRONG,
    GAMERAM_DEADRESTART,
    GAMERAM_CTRLITEM,
    GAMERAM_FIGHTCALC,
    GAMERAM_DISPFIGHTDATA,
    GAMERAM_BKCHIPBITEXP,
    GAMERAM_CTRLPLAYER
};
int beNDMWGameRam_OnMessage(beNDMWGameRam *self, int ram, beMessengerWork *message) {
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
    int hitEnemyRecNo;
    int hitAgility;
    int hitPlayerIndex;
    int hitAccuracy;
    int hitAttackId;
    int hitDownEvasion;
    int hitEnemyAgility;
    beNDMWMdlPEBaseInfoWork *hitEnemy;
    int hitWeaponSkill;
    void *temp_v0_34;
    int var_s2;
    char *temp_v0_19;
    char *temp_v0_10;

    void *temp_v0_47;

    Vector3 sp3D8;
    Vector3 sp3C8;
    Vector3 sp3B8;
    Vector3 sp3A8;
    Vector3 sp398;
    Vector3 sp388;
    Vector3 hpEffectOffset;
    Vector3 mpEffectOffset;
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
    int temp_ret_135;
    int temp_ret_136;
    int temp_ret_141;
    int temp_ret_142;
    int temp_ret_147;
    int temp_ret_148;
    int temp_ret_153;
    int temp_ret_154;
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
    int temp_ret_66;
    int temp_ret_67;
    int temp_ret_77;
    int temp_ret_78;
    beDataObjBool *temp_ret_366;
    beDataObjBool *temp_ret_48;
    int temp_s1_3;
    int *temp_ret_347;
    int *temp_ret_786;
    int temp_a0_10;
    int temp_a0_4;
    int temp_a0_5;
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
    int temp_ret_103;
    int temp_ret_1042;
    int temp_ret_1047;
    int temp_ret_1048;
    int temp_ret_1049;
    int temp_ret_104;
    int temp_ret_1050;
    int temp_ret_1051;
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
    int temp_ret_1163;
    int temp_ret_1164;
    int temp_ret_1168;
    int temp_ret_1170;
    int temp_ret_1175;
    int temp_ret_1180;
    int temp_ret_1185;
    int temp_ret_1186;
    int temp_ret_1189;
    int temp_ret_1193;
    int temp_ret_1198;
    int temp_ret_11;
    int temp_ret_1203;
    int temp_ret_1204;
    int temp_ret_1206;
    int temp_ret_1211;
    int temp_ret_1216;
    int temp_ret_1221;
    int temp_ret_1222;
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
    int temp_ret_1265;
    int temp_ret_1267;
    int temp_ret_1268;
    int temp_ret_1271;
    int temp_ret_1280;
    int temp_ret_1289;
    int temp_ret_1290;
    int temp_ret_1292;
    int temp_ret_1293;
    int temp_ret_1294;
    int temp_ret_1295;
    int temp_ret_1296;
    int temp_ret_1298;
    int temp_ret_1299;
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
    int temp_ret_580;
    int temp_ret_582;
    int temp_ret_587;
    int temp_ret_589;
    int temp_ret_594;
    int temp_ret_595;
    int temp_ret_5;
    int temp_ret_600;
    int temp_ret_601;
    int temp_ret_603;
    int temp_ret_608;
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
    int temp_ret_96;
    int temp_ret_975;
    int temp_ret_97;
    int temp_ret_980;
    int temp_ret_981;
    int temp_ret_982;
    int temp_ret_983;
    int temp_ret_984;
    int temp_ret_98;
    int temp_ret_992;
    int temp_ret_997;
    int temp_ret_998;
    int temp_ret_999;
    int temp_ret_99;
    int temp_ret_9;
    int temp_s0_10;
    int temp_s0_12;
    int temp_s0_13;
    int temp_s0_14;
    int temp_s0_15;
    unsigned int temp_s1_6;
    int temp_s0_16;
    int temp_s0_17;
    int temp_s0_18;
    int temp_s0_19;
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
    int temp_s0_8;
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
    int temp_v1_14;
    int temp_v1_2;
    int temp_v1_3;
    int temp_v1_6;
    int temp_v1_7;
    int temp_v1_9;
    int var_a2;
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
    int var_s3_2;
    int var_s3_4;
    int var_s2_8;
    int var_s3_6;
    int var_s3_7;
    int temp_s4;
    int var_s3_8;
    int var_s5;
    int var_s5_10;
    int var_s5_3;
    int var_s5_8;
    int var_s5_9;
    int var_s7;
    int var_s7_2;
    int var_s8;
    int var_s8_2;
    int var_v0_13;
    int var_v0_15;
    int var_v0_18;
    int var_v0_2;
    int var_v0_3;
    int var_v0_5;
    int var_v0_9;
    int var_v1_11;
    int var_v1_12;
    int var_v1_13;
    int var_v1_14;
    int var_v1_15;
    int var_v1_16;
    int var_v1_7;
    int var_v1_8;
    int var_v1_9;
    const char *temp_ret;
    char *temp_ret_1001;
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
    const char *temp_ret_187;
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
    char *temp_ret_499;
    char *temp_ret_566;
    const char *temp_ret_65;
    char *temp_ret_688;
    char *temp_ret_727;
    char *temp_ret_752;
    const char *temp_ret_76;
    const char *temp_ret_79;
    const char *temp_ret_81;
    char *temp_ret_822;
    char *temp_ret_834;
    char *temp_ret_871;
    char *temp_ret_899;
    const char *temp_ret_91;
    char *temp_ret_934;
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
    char *var_v0_20;
    char *var_v0_21;
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
    unsigned int temp_v1_8;
    unsigned int var_s1_12;
    unsigned char *temp_ret_174;
    unsigned char *temp_ret_175;
    unsigned char *temp_ret_176;
    unsigned char *temp_ret_177;
    unsigned char *temp_ret_178;
    unsigned char temp_ret_186;
    unsigned char temp_ret_18;
    unsigned char temp_s0;
    unsigned char temp_s0_2;
    unsigned char var_a1;
    unsigned char var_a1_2;
    unsigned char var_a1_3;
    void *temp_ret_1035;
    void *temp_ret_1052;
    void *temp_ret_1079;
    void *temp_ret_1082;
    void *temp_ret_1085;
    void *temp_ret_1110;
    void *temp_ret_1113;
    void *temp_ret_1116;
    void *temp_ret_1120;
    void *temp_ret_1121;
    void *temp_ret_1132;
    void *temp_ret_1133;
    void *temp_ret_1157;
    void *temp_ret_1166;
    int temp_s2_6;
    int temp_s3_15;
    int temp_s3_16;
    int temp_s3_17;
    int temp_s6_3;
    int temp_s8_2;
    void *temp_ret_1205;
    void *temp_ret_1210;
    void *temp_ret_1224;
    void *temp_ret_1263;
    void *temp_ret_126;
    void *temp_ret_1278;
    void *temp_ret_1291;
    void *temp_ret_1297;
    void *temp_ret_134;
    void *temp_ret_140;
    void *temp_ret_146;
    void *temp_ret_152;
    void *temp_ret_161;
    void *temp_ret_171;
    void *temp_ret_173;
    void *temp_ret_190;
    void *temp_ret_196;
    void *temp_ret_202;
    void *temp_ret_210;
    void *temp_ret_211;
    void *temp_ret_247;
    void *temp_ret_253;
    void *temp_ret_255;
    void *temp_ret_256;
    void *temp_ret_281;
    void *temp_ret_2;
    void *temp_ret_334;
    void *temp_ret_342;
    void *temp_ret_345;
    void *temp_ret_346;
    void *temp_ret_348;
    void *temp_ret_352;
    void *temp_ret_362;
    void *temp_ret_36;
    void *temp_ret_429;
    void *temp_ret_460;
    void *temp_ret_485;
    void *temp_ret_4;
    void *temp_ret_514;
    void *temp_ret_535;
    void *temp_ret_581;
    void *temp_ret_602;
    void *temp_ret_621;
    void *temp_ret_662;
    void *temp_ret_671;
    void *temp_ret_672;
    void *temp_ret_698;
    void *temp_ret_699;
    void *temp_ret_767;
    void *temp_ret_791;
    void *temp_ret_792;
    void *temp_ret_798;
    void *temp_ret_806;
    void *temp_ret_807;
    void *temp_ret_865;
    void *temp_ret_968;
    void *temp_ret_985;
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
    void *temp_v0_67;
    void *temp_v0_6;
    void *temp_v0_78;
    void *temp_v0_82;
    void *temp_v0_86;
    void *temp_v0_93;

    const char *messageName = (const char *)beNDMWGameRam_igStringRef_Get(&message->_message);
    void *messageEnum = GameRamMessage_GetMetaEnum();
    unsigned int messageId = beMessenger_ResolveEnumValue(self->_messenger, messageEnum, messageName);
    switch (messageId) {
    case GAMERAM_GETCOMMON: {
        void *commonData = (void *)(beNDMWGameRam_igSmartPointer_beDataObjList_Get(&self->_commonDataList));
        beMessenger_AppendObject(self->_messenger, commonData);
        return 1;
    }
    case GAMERAM_GETPLAYER: {
        int playerIndex = beMessenger_GetInt(self->_messenger, 0);
        int player = MessageAccess::Player(self, playerIndex);
        beMessenger_AppendObject(self->_messenger, player);
        return 1;
    }
    case GAMERAM_GETPLAYER1: {
        int player = MessageAccess::Player(self, 0);
        beMessenger_AppendObject(self->_messenger, player);
        return 1;
    }
    case GAMERAM_GETPLAYER2: {
        int player = MessageAccess::Player(self, 1);
        beMessenger_AppendObject(self->_messenger, player);
        return 1;
    }
    case GAMERAM_GETPLAYER3: {
        int player = MessageAccess::Player(self, 2);
        beMessenger_AppendObject(self->_messenger, player);
        return 1;
    }
    case GAMERAM_GETPLAYER4: {
        int player = MessageAccess::Player(self, 3);
        beMessenger_AppendObject(self->_messenger, player);
        return 1;
    }
    case GAMERAM_RECALCPLAYER: {
        int playerIndex = beMessenger_GetInt(self->_messenger, 0);
        unsigned char apply = 1;
        if (beMessenger_GetBoolCount(self->_messenger) != 0) {
            apply = beMessenger_GetBool(self->_messenger, 0);
        }
        beNDMWGameRam_RecomputeStats(self, playerIndex, apply);
        return 1;
    }
    case GAMERAM_BASE2CURRENT: {
        int playerIndex = beMessenger_GetInt(self->_messenger, 0);
        const char *speciesName = beMessenger_GetString(self->_messenger, 0);
        int species = beNDMWGameRam_FindSpecies(self, speciesName);
        beNDMWGameRam_SelectSpecies(self, playerIndex, species);
        return 1;
    }
    case GAMERAM_CURRENT2BASE: {
        int playerIndex = beMessenger_GetInt(self->_messenger, 0);
        beNDMWGameRam_StoreSpecies(self, playerIndex);
        return 1;
    }
    case GAMERAM_WEAPONEQUIPCHECK: {
        int playerIndex = beMessenger_GetInt(self->_messenger, 0);
        int weaponIndex = beMessenger_GetInt(self->_messenger, 1);
        beMessenger_AppendBool(self->_messenger, beNDMWGameRam_HasUsableWeapon(self, playerIndex, weaponIndex));
        return 1;
    }
    case GAMERAM_WEAPONEQUIPSTRONG: {
        int playerIndex = beMessenger_GetInt(self->_messenger, 0);
        beNDMWGameRam_EquipWeapon(self, playerIndex, 1);
        return 1;
    }
    case GAMERAM_GAMEDATAINIT: {
        int playerIndex = beMessenger_GetInt(self->_messenger, 0);
        beNDMWGameRam_ResetPlayer(self, playerIndex);
        return 1;
    }
    case GAMERAM_GAMESTART: {
        int playerIndex = beMessenger_GetInt(self->_messenger, 0);
        const char *playerName = beMessenger_GetString(self->_messenger, 0);
        if (beMessenger_GetObjectCount(self->_messenger) == 1) {
            void *unicodeName = (void *)(beMessenger_GetObject(self->_messenger, 0));
            { RecoveryRef<0> unicodeNameRef((void *)(unicodeName), true);
            beNDMWGameRam_JoinPlayerWithUnicodeName(self, playerIndex, (char *)playerName, unicodeNameRef);
            }
        } else {
            if (beMessenger_GetStringCount(self->_messenger) == 2) {
                char *displayName = (char *)beMessenger_GetString(self->_messenger, 1);
                beNDMWGameRam_JoinPlayerWithName(self, playerIndex, (char *)playerName, StringRef(displayName == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), displayName)));
            }
        }
        return 1;
    }
    case GAMERAM_GAMEREMOVE: {
        int playerIndex = beMessenger_GetInt(self->_messenger, 0);
        beNDMWGameRam_LeavePlayer(self, playerIndex);
        return 1;
    }
    case GAMERAM_DEADRESTART: {
        int playerIndex = 0;
        do {
            int player = MessageAccess::Player(self, playerIndex);
            if (igProperty_GetRecordByte(player, "ISUSE")->value != 0) {
                int maxHp = beNDMWGameRam_beDataObjInt_GetData((beDataObjInt *)igProperty_GetRecord((void *)player, "MHP"));
                igProperty_GetRecord((void *)player, "HP")->value = maxHp;
                int maxMp = beNDMWGameRam_beDataObjInt_GetData((beDataObjInt *)igProperty_GetRecord((void *)player, "MMP"));
                igProperty_GetRecord((void *)player, "MP")->value = maxMp;
            }
            playerIndex += 1;
        } while (playerIndex < 4);
        return 1;
    }
    case GAMERAM_ADDHP: {
        int playerIndex = beMessenger_GetInt(self->_messenger, 0);
        int delta = beMessenger_GetInt(self->_messenger, 1);
        int showEffect = beMessenger_GetIntCount(self->_messenger) < 3 ? 0 : beMessenger_GetInt(self->_messenger, 2);
        int absoluteHp = beMessenger_GetIntCount(self->_messenger) < 4 ? -1 : beMessenger_GetInt(self->_messenger, 3);
        int changed = beNDMWGameRam_ChangeHp(self, playerIndex, delta, absoluteHp);
        if ((changed != 0) && (showEffect != 0)) {
            int player = MessageAccess::Player(self, playerIndex);
            const char *digimonName = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((void *)player, "DIGIMONNAME"))->_data);
            beMessenger_PrepareDelayedSelection(self->_messenger, "PLAYER", digimonName, playerIndex);
            beMessenger_AppendString(self->_messenger, "x_250healhit00");
            beMessenger_AppendString(self->_messenger, "SQ_HEALEFONLY");
            beMessenger_AppendFloat(self->_messenger, 1.0f);
            Vec3f_Copy(&hpEffectOffset, &g_vec3Zero[0]);
            beMessenger_AppendVec3(self->_messenger, &hpEffectOffset);
            beMessenger_AppendBool(self->_messenger, 0U);
            beMessenger_AppendBool(self->_messenger, 1U);
            beMessenger_EnqueueSelected(self->_messenger, "SETEFFECT", 1);
        }
        return 1;
    }
    case GAMERAM_ADDMP: {
        int playerIndex = beMessenger_GetInt(self->_messenger, 0);
        int delta = beMessenger_GetInt(self->_messenger, 1);
        int showEffect = 0;
        if (beMessenger_GetIntCount(self->_messenger) == 3) {
            showEffect = beMessenger_GetInt(self->_messenger, 2);
        }
        beNDMWGameRam_ChangeMp(self, playerIndex, delta);
        if (showEffect != 0) {
            int player = MessageAccess::Player(self, playerIndex);
            const char *digimonName = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((void *)player, "DIGIMONNAME"))->_data);
            beMessenger_PrepareDelayedSelection(self->_messenger, "PLAYER", digimonName, playerIndex);
            beMessenger_AppendString(self->_messenger, "x_250healhit00");
            beMessenger_AppendString(self->_messenger, "SQ_HEALEFONLY");
            beMessenger_AppendFloat(self->_messenger, 1.0f);
            Vec3f_Copy(&mpEffectOffset, &g_vec3Zero[0]);
            beMessenger_AppendVec3(self->_messenger, &mpEffectOffset);
            beMessenger_AppendBool(self->_messenger, 0U);
            beMessenger_AppendBool(self->_messenger, 1U);
            beMessenger_EnqueueSelected(self->_messenger, "SETEFFECT", 1);
        }
        return 1;
    }
    case GAMERAM_CTRLPLAYER: {
        const char *field = beMessenger_GetString(self->_messenger, 0);
        int result = 0;
        if (strcmp(field, "EXP") == 0) {
            const char *operation = beMessenger_GetString(self->_messenger, 1);
            int playerIndex = beMessenger_GetInt(self->_messenger, 0);
            int value = beMessenger_GetInt(self->_messenger, 1);
            IntProperty *exp = igProperty_GetRecord((void *)MessageAccess::Player(self, playerIndex), "EXP");
            if (strcmp(operation, "SET") == 0) {
                exp->value = value;
            } else {
                if (strcmp(operation, "ADD") == 0) {
                    exp->value = (int)((int) (value + beNDMWGameRam_beDataObjInt_GetData((beDataObjInt *)((int) exp))));
                }
            }
        } else {
            if (strcmp(field, "HP") == 0) {
                const char *query = beMessenger_GetString(self->_messenger, 1);
                int playerIndex = beMessenger_GetInt(self->_messenger, 0);
                int player = MessageAccess::Player(self, playerIndex);
                if (strcmp(query, GETHP) == 0) {
                    result = igProperty_GetRecord((void *)player, "HP")->value;
                } else {
                    if (strcmp(query, "GETMHP") == 0) {
                        result = igProperty_GetRecord((void *)player, "MHP")->value;
                    }
                }
            } else {
                if (strcmp(field, "MP") == 0) {
                    const char *query = beMessenger_GetString(self->_messenger, 1);
                    int playerIndex = beMessenger_GetInt(self->_messenger, 0);
                    int player = MessageAccess::Player(self, playerIndex);
                    if (strcmp(query, "GETMP") == 0) {
                        result = igProperty_GetRecord((void *)player, "MP")->value;
                    } else {
                        if (strcmp(query, "GETMMP") == 0) {
                            result = igProperty_GetRecord((void *)player, "MMP")->value;
                        }
                    }
                }
            }
        }
        beMessenger_ClearInt(self->_messenger);
        beMessenger_AppendInt(self->_messenger, result);
        return 1;
    }
    case GAMERAM_CTRLITEM: {
        char *category = (char *)beMessenger_GetString(self->_messenger, 0);
        const char *operationName = beMessenger_GetString(self->_messenger, 1);
        char *slotName = (char *)beMessenger_GetString(self->_messenger, 2);
        int playerIndex = beMessenger_GetInt(self->_messenger, 0);
        int recNo = beMessenger_GetInt(self->_messenger, 1);
        int revision = beMessenger_GetInt(self->_messenger, 2);
        int pocketOrAmount = beMessenger_GetInt(self->_messenger, 3);
        /* matching construct: the loop counters and flags are separate case-level variables, declared
         * before the block locals, as the register allocation requires */
        unsigned char removed;
        unsigned char equipped;
        int findIndex;
        int equipIndex;
        int operation;
        int clearIndex;
        int bit;
        int slotKind;
        if (strcmp(operationName, "SET") == 0) {
            operation = ITEMOP_SET;
        } else if (strcmp(operationName, "CLR") == 0) {
            operation = ITEMOP_CLR;
        } else if (strcmp(operationName, "IS") == 0) {
            operation = ITEMOP_IS;
        } else if (strcmp(operationName, "ISMAX") == 0) {
            operation = ITEMOP_ISMAX;
        } else if (strcmp(operationName, "ISEQUIP") == 0) {
            operation = ITEMOP_ISEQUIP;
        } else if (strcmp(operationName, "GET") == 0) {
            operation = ITEMOP_GET;
        } else if (strcmp(operationName, "ADD") == 0) {
            operation = ITEMOP_ADD;
        } else {
            return 1;
        }
        {
            if (strcmp(category, "DEVICE") == 0) {
                int player = MessageAccess::Player(self, playerIndex);
                int deviceFolder = (int)igProperty_GetRecordFolder(player, "DEVICEFOLDER");
                igObjectList *items = (igObjectList *)(void *)(beNDMWGameRam_igSmartPointer_igObjectList_Get(&((beDataObjObjectList *)deviceFolder)->_data));
                slotKind = ITEMSLOT_WEAPON;
                if (operation != ITEMOP_ISMAX) {
                    if (strcmp(slotName, "weapon") == 0) {
                        slotKind = ITEMSLOT_WEAPON;
                    } else if (strcmp(slotName, "armor1") == 0) {
                        slotKind = ITEMSLOT_ARMOR1;
                    } else if (strcmp(slotName, "armor2") == 0) {
                        slotKind = ITEMSLOT_ARMOR2;
                    } else if (strcmp(slotName, "abChip") == 0) {
                        slotKind = ITEMSLOT_ABCHIP;
                    } else {
                        return 1;
                    }
                }
                switch (operation) {
                case ITEMOP_SET:
                    if (items->_count == 0x24) {
                        beMessenger_AppendBool(self->_messenger, 0U);
                    } else {
                        switch (slotKind) {
                        case ITEMSLOT_WEAPON: {
                            int allocator = igObject_GetAllocator(self);
                            int pooledAllocator = beNDMWLoadIntf2_Memory_SelectAllocator(kIGMemoryPoolHandleUser0, allocator);
                            void *created = (void *)(beNDMWItemWeapon_Create(beNDMWGameRam_beNDMWItemWeapon_MakeAllocatorValue(pooledAllocator).v));
                            { RecoveryRef<1> item(created, false);
                            beNDMWItemWeapon_Set(item.value, recNo, pocketOrAmount, revision);
                            ObjectList_AppendRetained(items, item.value);
                            }
                            break;
                        }
                        case ITEMSLOT_ARMOR1: {
                            int allocator = igObject_GetAllocator(self);
                            int pooledAllocator = beNDMWLoadIntf2_Memory_SelectAllocator(kIGMemoryPoolHandleUser0, allocator);
                            void *created = (void *)(beNDMWItemBlueArmor_Create(beNDMWGameRam_beNDMWItemBlueArmor_MakeAllocatorValue(pooledAllocator).v));
                            { RecoveryRef<2> item(created, false);
                            beNDMWItemBlueArmor_Set(item.value, recNo, pocketOrAmount, revision);
                            ObjectList_AppendRetained(items, item.value);
                            }
                            break;
                        }
                        case ITEMSLOT_ARMOR2: {
                            int allocator = igObject_GetAllocator(self);
                            int pooledAllocator = beNDMWLoadIntf2_Memory_SelectAllocator(kIGMemoryPoolHandleUser0, allocator);
                            void *created = (void *)(beNDMWItemYellowArmor_Create(beNDMWGameRam_beNDMWItemYellowArmor_MakeAllocatorValue(pooledAllocator).v));
                            { RecoveryRef<3> item(created, false);
                            beNDMWItemYellowArmor_Set(item.value, recNo, revision);
                            ObjectList_AppendRetained(items, item.value);
                            }
                            break;
                        }
                        case ITEMSLOT_ABCHIP: {
                            int allocator = igObject_GetAllocator(self);
                            int pooledAllocator = beNDMWLoadIntf2_Memory_SelectAllocator(kIGMemoryPoolHandleUser0, allocator);
                            void *created = (void *)(beNDMWItemAbilityChip_Create(beNDMWGameRam_beNDMWItemAbilityChip_MakeAllocatorValue(pooledAllocator).v));
                            { RecoveryRef<4> item(created, false);
                            beNDMWItemAbilityChip_Set(item.value, recNo);
                            ObjectList_AppendRetained(items, item.value);
                            }
                            break;
                        }
                        }
                        beMessenger_AppendBool(self->_messenger, 1U);
                    }
                    goto done;
                case ITEMOP_CLR:
                    {
                    beNDMWItemBase *item;
                    int itemCount = items->_count;
                    removed = 0;
                    for (clearIndex = 0; clearIndex < itemCount; ++clearIndex) {
                        item = (beNDMWItemBase *)((void **)items->_data)[clearIndex]; /* matching construct: _data is a 4-byte int reference, indexed as the pointer array the pre-typing struct declared */
                        if ((slotKind == item->_kindNo) && (recNo == item->_recNo) && (item->_isEquip == 0)) {

                            beNDMWLoadIntf2_igObject_Release(beNDMWLoadIntf2_igObjectList_Get(items, clearIndex));
                            beNDMWGameRam_igObjectList_Remove(items, clearIndex);
                            removed = 1;
                            ((void **)items->_data)[items->_count] = 0; /* matching construct: _data is a 4-byte int reference, indexed as the pointer array the pre-typing struct declared */
                            break;
                        }
                    }
                    beMessenger_AppendBool(self->_messenger, removed);
                    }
                    goto done;
                case ITEMOP_IS:
                    {
                    beNDMWItemBase *item;
                    int itemCount = items->_count;
                    for (findIndex = 0; findIndex < itemCount; ++findIndex) {
                        item = (beNDMWItemBase *)((void **)items->_data)[findIndex]; /* matching construct: _data is a 4-byte int reference, indexed as the pointer array the pre-typing struct declared */
                        if ((slotKind == item->_kindNo) && (recNo == item->_recNo)) {

                            beMessenger_AppendBool(self->_messenger, 1U);
                            return 1;
                        }
                    }
                    }
                    beMessenger_AppendBool(self->_messenger, 0U);
                    goto done;
                case ITEMOP_ISMAX:
                    if (items->_count == 0x24) {
                        beMessenger_AppendBool(self->_messenger, 1U);
                    } else {
                        beMessenger_AppendBool(self->_messenger, 0U);
                    }
                    goto done;
                case ITEMOP_ISEQUIP:
                    {
                    beNDMWItemBase *item;
                    int itemCount = items->_count;
                    equipped = 0;
                    for (equipIndex = 0; equipIndex < itemCount; ++equipIndex) {
                        item = (beNDMWItemBase *)((void **)items->_data)[equipIndex]; /* matching construct: _data is a 4-byte int reference, indexed as the pointer array the pre-typing struct declared */
                        if ((slotKind == item->_kindNo) && (recNo == item->_recNo) && (item->_isEquip != 0)) {

                            equipped = 1;
                            break;
                        }
                    }
                    beMessenger_AppendBool(self->_messenger, equipped);
                    }
                    goto done;
                }
            } else {
                if (strcmp(category, "DISK") == 0) {
                    int player = MessageAccess::Player(self, playerIndex);
                    int diskFolder = (int)igProperty_GetRecordFolder(player, "DISKFOLDER");
                    void *disks = (void *)(beNDMWGameRam_igSmartPointer_igObjectList_Get(&((beDataObjObjectList *)diskFolder)->_data));
                    switch (operation) {
                    case ITEMOP_SET: {
                        beNDMWItemDisk *disk = (beNDMWItemDisk *)beNDMWLoadIntf2_igObjectList_Get(disks, beNDMWItemBase_IndexOfRecNo(disks, recNo));
                        int owned = disk->_kazu;
                        if (owned == 9) {
                            beMessenger_AppendBool(self->_messenger, 0U);
                        } else {
                            int total = owned + pocketOrAmount;
                            if (total < 0xA) {
                                disk->_kazu = total;
                            } else {
                                disk->_kazu = 9;
                            }
                            beMessenger_AppendBool(self->_messenger, 1U);
                        }
                        break;
                    }
                    case ITEMOP_CLR: {
                        beNDMWItemDisk *disk = (beNDMWItemDisk *)beNDMWLoadIntf2_igObjectList_Get(disks, beNDMWItemBase_IndexOfRecNo(disks, recNo));
                        int owned = disk->_kazu;
                        if (owned == 0) {
                            beMessenger_AppendBool(self->_messenger, 0U);
                        } else {
                            int remaining = owned - pocketOrAmount;
                            if (remaining >= 0) {
                                disk->_kazu = remaining;
                            } else {
                                disk->_kazu = 0;
                            }
                            beMessenger_AppendBool(self->_messenger, 1U);
                        }
                        break;
                    }
                    case ITEMOP_IS:
                        if (((beNDMWItemDisk *)beNDMWLoadIntf2_igObjectList_Get(disks, beNDMWItemBase_IndexOfRecNo(disks, recNo)))->_kazu != 0) {
                            beMessenger_AppendBool(self->_messenger, 1U);
                        } else {
                            beMessenger_AppendBool(self->_messenger, 0U);
                        }
                        break;
                    case ITEMOP_ISMAX:
                        if (((beNDMWItemDisk *)beNDMWLoadIntf2_igObjectList_Get(disks, beNDMWItemBase_IndexOfRecNo(disks, recNo)))->_kazu == 9) {
                            beMessenger_AppendBool(self->_messenger, 1U);
                        } else {
                            beMessenger_AppendBool(self->_messenger, 0U);
                        }
                        break;
                    }
                    goto done;
                }
                if (strcmp(category, "FLAG") == 0) {
                    void *commonData = (void *)(beNDMWGameRam_igSmartPointer_beDataObjList_Get(&self->_commonDataList));
                    int flagFolder = (int)igProperty_GetRecordArray(commonData, "FLAGFOLDER");
                    void *flags = (void *)(beNDMWGameRam_igSmartPointer_igBoolList_Get(&((beDataObjBoolList *)flagFolder)->_data));
                    unsigned char *flagBytes;
                    switch (operation) {
                    case ITEMOP_SET:
                        flagBytes = (unsigned char *)beNDMWGameRam_igBoolList_GetData((igUnsignedCharList *)flags);
                        if (*(flagBytes + recNo) != 0) {
                            beMessenger_AppendBool(self->_messenger, 0U);
                        } else {
                            int flagCount = ((igBoolList *)flags)->_count;
                            if ((flagCount != 0) && (recNo >= 0) && (recNo < flagCount)) {
                                unsigned char setValue = g_boolListSetValue;
                                *(unsigned char *)(recNo + (int)beNDMWGameRam_igBoolList_GetData((igUnsignedCharList *)flags)) = setValue;
                            }
                            beMessenger_AppendBool(self->_messenger, 1U);
                        }
                        break;
                    case ITEMOP_CLR:
                        flagBytes = (unsigned char *)beNDMWGameRam_igBoolList_GetData((igUnsignedCharList *)flags);
                        if (*(flagBytes + recNo) == 0) {
                            beMessenger_AppendBool(self->_messenger, 0U);
                        } else {
                            int flagCount = ((igBoolList *)flags)->_count;
                            if ((flagCount != 0) && (recNo >= 0) && (recNo < flagCount)) {
                                unsigned char clearValue = g_boolListClearValue;
                                *(unsigned char *)(recNo + (int)beNDMWGameRam_igBoolList_GetData((igUnsignedCharList *)flags)) = clearValue;
                            }
                            beMessenger_AppendBool(self->_messenger, 1U);
                        }
                        break;
                    case ITEMOP_IS:
                        flagBytes = (unsigned char *)beNDMWGameRam_igBoolList_GetData((igUnsignedCharList *)flags);
                        beMessenger_AppendBool(self->_messenger, *(flagBytes + recNo));
                        break;
                    }
                    goto done;
                }
                if (strcmp(category, "BIT") == 0) {
                    void *player = (void *)MessageAccess::Player(self, playerIndex);
                    switch (operation) {
                    case ITEMOP_SET:
                        igProperty_GetRecord(player, "BIT")->value = recNo;
                        break;
                    case ITEMOP_GET:
                        beMessenger_ClearInt(self->_messenger);
                        beMessenger_AppendInt(self->_messenger, igProperty_GetRecord(player, "BIT")->value);
                        break;
                    case ITEMOP_ADD: {
                        bit = recNo + igProperty_GetRecord(player, "BIT")->value;
                        if (bit < 0) {
                            bit = 0;
                        } else if (bit > 0x98967F) {
                            bit = 0x98967F;
                        }
                        igProperty_GetRecord(player, "BIT")->value = bit;
                        break;
                    }
                    }
                } else {
                    return 1;
                }
            }
        }
done:
        return 1;
    }
    case GAMERAM_DISPFIGHTDATA:
        self->_isDispFightData = beMessenger_GetBool(self->_messenger, 0);
        return 1;
    case GAMERAM_FIGHTCALC: {
        const char *commandText = beMessenger_GetString(self->_messenger, 0);
        { StringRef commandName(commandText == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), commandText));
        void *fightComEnum = (void *)(FightCom_GetMetaEnum());
        const char *commandString = (const char *)beNDMWGameRam_igStringRef_Get((int *)&commandName.p);
        unsigned int fightCommand;
        igMetaEnum_GetValueByName(fightComEnum, commandString, &fightCommand);
        switch (fightCommand) {
        case FIGHTCOM_P2EISHITCHECK: {
            hitPlayerIndex = beMessenger_GetInt(self->_messenger, 0);
            hitEnemyRecNo = beMessenger_GetInt(self->_messenger, 1);
            hitAttackId = beMessenger_GetInt(self->_messenger, 2);
            hitEnemy = (beNDMWMdlPEBaseInfoWork *)(void *)(beMessenger_GetObject(self->_messenger, 0));
            switch (hitAttackId / 10000) {
            case 4:
                beMessenger_AppendBool(self->_messenger, 1U);
                            break;
            default: {
                void *player = (void *)MessageAccess::Player(self, hitPlayerIndex);
                hitWeaponSkill = igProperty_GetRecord(player, "WEAPONSKILLNO")->value;
                hitAgility = igProperty_GetRecord(player, "SUBAYASA")->value;
                int skillList = (int)igProperty_GetRecordIntList(player, "SKILL");
                void *skillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)skillList)->_data));
                int skillData = beNDMWLoadIntf2_igIntList_GetData(skillValues);
                hitWeaponSkill = *(int *)(skillData + (hitWeaponSkill * 4));
                hitAccuracy = igProperty_GetRecord(player, "MEICHURITSU")->value;
                hitEnemyAgility = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), hitEnemyRecNo, "SUBAYASA");
                if (beNDMWGameRam_igSmartPointer_igIntList_Get(&hitEnemy->_downDataList) == 0) {
                    hitDownEvasion = 0;
                } else {
                    void *downData = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&hitEnemy->_downDataList));
                    hitDownEvasion = ((int *)beNDMWLoadIntf2_igIntList_GetData(downData))[3];
                }
                unsigned int roll = MessageAccess::Random(self)->genrand() % 10000U;
                if ((int) roll < ((int) (hitAccuracy * ((hitAgility * 0x1E) + (hitWeaponSkill * 0x14) + 0x1770)) / (int) ((int) (hitEnemyAgility * (0x64 - hitDownEvasion)) / 100))) {
                    beMessenger_AppendBool(self->_messenger, 1U);
                } else {
                    beMessenger_AppendBool(self->_messenger, 0U);
                }
                            break;
            }
            }
            break;
        }
        case FIGHTCOM_P2EISCRITICAL: {
            int playerIndex = beMessenger_GetInt(self->_messenger, 0);
            int enemyRecNo = beMessenger_GetInt(self->_messenger, 1);
            int attackId = beMessenger_GetInt(self->_messenger, 2);
            void *player = (void *)MessageAccess::Player(self, playerIndex);
            unsigned char isCritical;
            if ((attackId / 10000) != 4) {
                int critRate = igProperty_GetRecord(player, "CHIMEIRITSU")->value;
                unsigned int roll = MessageAccess::Random(self)->genrand() % 200U;
                if ((int) roll < critRate) {
                    isCritical = 1;
                } else {
                    isCritical = 0;
                }
            } else {
                int techniqueNo = (int)((int) attackId % 1000);
                int techniqueRow;
                beNDMWGameRam_FindTechniqueRow(self, player, techniqueNo, &techniqueRow);
                char *element = (char *)(beDataBase_GetRecordString(MessageDatabases::PcTech(self), techniqueRow, "ZOKUSEI"));
                int elementIndex;
                if (strcmp(element, "fire") == 0) {
                    elementIndex = 0;
                } else {
                    if (strcmp(element, "ice") == 0) {
                        elementIndex = 1;
                    } else {
                        if (strcmp(element, "thunder") == 0) {
                            elementIndex = 2;
                        } else {
                            if (strcmp(element, "dark") == 0) {
                                elementIndex = 3;
                            } else {
                                if (strcmp(element, "poison") == 0) {
                                    elementIndex = 4;
                                } else {
                                    elementIndex = -1;
                                }
                            }
                        }
                    }
                }
                int techCritRate = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), techniqueRow, "CHIMEIRITSU");
                if (elementIndex >= 0) {
                    int resistance;
                    if (elementIndex >= 0) {
                        resistance = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), enemyRecNo, g_resistanceFields[elementIndex]);
                    } else {
                        resistance = 0;
                    }
                    unsigned int roll = MessageAccess::Random(self)->genrand() % 1000U;
                    if ((int) roll < ((int) ((techCritRate + 0x64) * (0x2710 / (int) (((int) (resistance * 0xC) / 10) + 0x32))) / 100)) {
                        isCritical = 1;
                    } else {
                        isCritical = 0;
                    }
                } else {
                    unsigned int roll = MessageAccess::Random(self)->genrand() % 100U;
                    if ((int) roll < techCritRate) {
                        isCritical = 1;
                    } else {
                        isCritical = 0;
                    }
                }
            }
            beMessenger_AppendBool(self->_messenger, isCritical);
            break;
        }
        case 5:
            temp_ret_243 = beMessenger_GetInt(self->_messenger, 0);
            temp_v0_44 = temp_ret_243;
            temp_ret_244 = beMessenger_GetInt(self->_messenger, 1);
            temp_v0_45 = temp_ret_244;
            temp_ret_245 = beMessenger_GetInt(self->_messenger, 2);
            sp12C = beMessenger_GetInt(self->_messenger, 3);
            temp_ret_247 = (void *)(beMessenger_GetObject(self->_messenger, 0));
            temp_v0_46 = (beNDMWMdlPEBaseInfoWork *)(temp_ret_247);
            temp_ret_249 = MessageAccess::Player(self, temp_v0_44);
            temp_v0_47 = (void *)(temp_ret_249);
            var_s1 = -1;
            switch (temp_ret_245 / 10000) {
            default: {
                temp_ret_250 = (int)igProperty_GetRecord(temp_v0_47, "WEAPONSKILLNO");
                temp_s0_5 = ((beDataObjInt *)temp_ret_250)->_data;
                temp_ret_251 = (int)igProperty_GetRecord(temp_v0_47, "TSUYOSA");
                temp_s2 = ((beDataObjInt *)temp_ret_251)->_data;
                temp_ret_252 = (int)igProperty_GetRecordIntList(temp_v0_47, "SKILL");
                temp_ret_253 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)temp_ret_252)->_data));
                temp_ret_254 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_253);
                var_s0 = *(int *)(temp_ret_254 + (temp_s0_5 * 4));
                temp_ret_255 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&temp_v0_46->_downDataList));
                if (temp_ret_255 == 0) {
                    var_s7 = 0;
                } else {
                    temp_ret_256 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&temp_v0_46->_downDataList));
                    temp_ret_257 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_256);
                    var_s7 = ((int *)temp_ret_257)[5];
                }
                temp_ret_262 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_45, "MAMORI");
                var_s7 = temp_ret_262 - var_s7;
                var_s2_2 = (int)((int) ((temp_s2 * 6) + (var_s0 * 4)) / var_s7);
                if (var_s2_2 < 0) {
                    var_s2_2 = 0;
                } else if (var_s2_2 > 0x1869F) {
                    var_s2_2 = 0x1869F;
                }
                if (var_s2_2 != 0) {
                    temp_ret_263 = (int)igProperty_GetRecord(temp_v0_47, "ATTACKZOKUSEI");
                    var_s1 = ((beDataObjInt *)temp_ret_263)->_data;
                    if (var_s1 != -1) {
                        temp_ret_268 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_45, g_elementResistanceFields[var_s1]);
                        temp_v0_48 = temp_ret_268;
                        temp_v0_50 = MessageAccess::Random(self)->genrand() % 1000U;
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
                temp_ret_274 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp48C, "HP");
                temp_v0_51 = (int)(0U - (unsigned int)temp_ret_274);
                if (temp_v0_51 != 0) {
                    temp_ret_279 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp48C, "SKILL");
                    temp_ret_280 = (int)igProperty_GetRecordIntList(temp_v0_47, "SKILL");
                    temp_ret_281 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)temp_ret_280)->_data));
                    temp_ret_282 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_281);
                    var_s0 = *(int *)(temp_ret_282 + (temp_ret_279 * 4));
                    temp_ret_287 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_45, "SEISHIN");
                    temp_ret_288 = (int)igProperty_GetRecord(temp_v0_47, "KASHIKOSA");
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
                    temp_ret_293 = (char *)(beDataBase_GetRecordString(MessageDatabases::PcTech(self), sp48C, "ZOKUSEI"));
                    temp_v0_52 = (char *)(temp_ret_293);
                    temp_ret_294 = strcmp(temp_v0_52, "fire");
                    if (temp_ret_294 == 0) {
                        var_s1 = 0;
                    } else {
                        temp_ret_295 = strcmp(temp_v0_52, "ice");
                        if (temp_ret_295 == 0) {
                            var_s1 = 1;
                        } else {
                            temp_ret_296 = strcmp(temp_v0_52, "thunder");
                            if (temp_ret_296 == 0) {
                                var_s1 = 2;
                            } else {
                                temp_ret_297 = strcmp(temp_v0_52, "dark");
                                if (temp_ret_297 == 0) {
                                    var_s1 = 3;
                                } else {
                                    temp_ret_298 = strcmp(temp_v0_52, "poison");
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
                        temp_ret_303 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_45, g_resistanceFields[var_s1]);
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
                    temp_s0_6 = MessageAccess::Random(self)->genrand() & 3;
                    temp_v0_55 = MessageAccess::Random(self)->genrand() % (unsigned int) (var_s2_2 * 0x19);
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
                    temp_ret_306 = (int)igProperty_GetRecord(temp_v0_47, "HPDRAIN");
                    temp_v0_59 = ((beDataObjInt *)temp_ret_306)->_data;
                    if (temp_v0_59 != 0) {
                        temp_ret_307 = beNDMWGameRam_ChangeHp(self, temp_v0_44, (int) (var_s2_2 * temp_v0_59) / 100, -1);
                    }
                    temp_ret_308 = (int)igProperty_GetRecord(temp_v0_47, "MPDRAIN");
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
            temp_ret_313 = MessageAccess::Player(self, temp_ret_310);
            temp_v0_61 = (void *)(temp_ret_313);
            switch (temp_ret_311 / 10000) {
            default: {
                temp_ret_314 = (int)igProperty_GetRecord(temp_v0_61, "ATTACKZOKUSEI");
                var_s0_10 = ((beDataObjInt *)temp_ret_314)->_data;
            break; }
            case 4: {
                temp_a2_6 = (int)((int) temp_ret_311 % 10000);
                int sp488;
                beNDMWGameRam_FindTechniqueRow(self, temp_v0_61, temp_a2_6, &sp488);
                temp_ret_319 = (char *)(beDataBase_GetRecordString(MessageDatabases::PcTech(self), sp488, "ZOKUSEI"));
                temp_v0_62 = (char *)(temp_ret_319);
                temp_ret_320 = strcmp(temp_v0_62, "fire");
                if (temp_ret_320 == 0) {
                    var_s0_10 = 0;
                } else {
                    temp_ret_321 = strcmp(temp_v0_62, "ice");
                    if (temp_ret_321 == 0) {
                        var_s0_10 = 1;
                    } else {
                        temp_ret_322 = strcmp(temp_v0_62, "thunder");
                        if (temp_ret_322 == 0) {
                            var_s0_10 = 2;
                        } else {
                            temp_ret_323 = strcmp(temp_v0_62, "dark");
                            if (temp_ret_323 == 0) {
                                var_s0_10 = 3;
                            } else {
                                temp_ret_324 = strcmp(temp_v0_62, "poison");
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
            temp_ret_330 = MessageAccess::Player(self, temp_v0_63);
            skp = (void *)(temp_ret_330);
            temp_ret_331 = (int)igProperty_GetRecord(skp, "LEVEL");
            sklv = ((beDataObjInt *)temp_ret_331)->_data;
            /* Ternary chain rather than if/else: only this form copies each next compare into the
             * beqz delay slot. */
            var_s8 = (sklv < 0x25) ? sklv * 0x1E
                   : (sklv < 0x6C) ? (sklv * 0x14) + 0x168
                   : (sklv < 0xE4) ? (sklv * 0xA) + 0x596
                   : (sklv * 8) + 0x75C;
            skcls = temp_ret_326 / 10000;
            if ((skcls != 9) && (skcls != 8) && (skcls != 4)) {
                temp_ret_332 = (int)igProperty_GetRecord(skp, "WEAPONSKILLNO");
                var_s5_3 = ((beDataObjInt *)temp_ret_332)->_data;
                temp_ret_333 = (int)igProperty_GetRecordIntList(skp, "SKILL");
                temp_ret_334 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)temp_ret_333)->_data));
                temp_ret_335 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_334);
                var_s7_2 = *(int *)(temp_ret_335 + (var_s5_3 * 4));
            } else {
                temp_a2_7 = (int)((int) temp_ret_326 % 10000);
                int sp484;
                beNDMWGameRam_FindTechniqueRow(self, skp, temp_a2_7, &sp484);
                temp_ret_340 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp484, "SKILL");
                var_s5_3 = temp_ret_340;
                temp_ret_341 = (int)igProperty_GetRecordIntList(skp, "SKILL");
                temp_ret_342 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)temp_ret_341)->_data));
                temp_ret_343 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_342);
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
                    temp_ret_344 = (int)igProperty_GetRecord(skp, "DIGIMONNO");
                    temp_s0_8 = ((beDataObjInt *)temp_ret_344)->_data;
                    temp_ret_345 = (void *)(beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBShinka));
                    if (temp_ret_345 == 0) {
                        beMessenger_SendNamed(self->_messenger, DATABASE_3, shinka_2, 0, GETDATABASE_3);
                        temp_ret_346 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                        temp_ret_347 = (int *)(beNDMWGameRam_igSmartPointer_beDataBase_Assign((ObjectRefTarget **)&self->_dBShinka, (ObjectRefTarget *)temp_ret_346));
                    }
                    temp_ret_348 = (void *)(beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBShinka));
                    temp_ret_349 = beDataBase_GetRecordInt(temp_ret_348, temp_s0_8, g_weaponGrowFields[var_s5_3]);
                    var_s0_11 = (int)((int) (temp_s1_3 * temp_ret_349 * 0x1F4) / 1000);
                break; }
                case 4: case 8: case 9:
                    var_s0_11 = temp_s1_3 * 0x64;
                    break;
                }
                temp_v0_66 = MessageAccess::Random(self)->genrand() % 100000U;
                if ((int) temp_v0_66 < var_s0_11) {
                    int skill_next = var_s7_2 + 1;
                    temp_ret_351 = (int)igProperty_GetRecordIntList(skp, "SKILL");
                    temp_ret_352 = (void *)(beNDMWGameRam_beDataObjIntList_GetData((int *)temp_ret_351));
                    temp_v0_67 = (void *)(temp_ret_352);
                    temp_v1_3 = ((igIntList *)temp_v0_67)->_count;
                    if ((temp_v1_3 != 0) && (var_s5_3 >= 0) && (var_s5_3 < temp_v1_3)) {
                        temp_ret_353 = beNDMWLoadIntf2_igIntList_GetData(temp_v0_67);
                        *(int *)(temp_ret_353 + (var_s5_3 * 4)) = skill_next;
                    }
                    beNDMWGameRam_RecomputeStats(self, temp_v0_63, 1);
                    beNDMWGameRam_StoreSpecies(self, temp_v0_63);
                    temp_ret_356 = (int)igProperty_GetRecordString(skp, "DIGIMONNAME");
                    temp_ret_357 = (char *)(beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_356)->_data));
                    temp_ret_358 = beMessenger_PrepareDelayedSelection(self->_messenger, "MODELCTRL", temp_ret_357, temp_v0_63);
                    beMessenger_AppendString(self->_messenger, "i_getitempnl01");
                    beMessenger_AppendString(self->_messenger, "SQ_TECUP");
                    beMessenger_AppendFloat(self->_messenger, 1.0f);
                    Vec3f_Copy(&sp358, &g_vec3Zero[0]);
                    beMessenger_AppendVec3(self->_messenger, &sp358);
                    beMessenger_AppendBool(self->_messenger, 0U);
                    beMessenger_AppendBool(self->_messenger, 1U);
                    temp_ret_359 = beMessenger_EnqueueSelected(self->_messenger, "SETEFFECT", 1);
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
            temp_ret_362 = (void *)(beNDMWGameRam_igSmartPointer_beDataObjList_Get(&self->_commonDataList));
            temp_ret_363 = (int)igProperty_GetRecord(temp_ret_362, "NINZU");
            temp_s6 = ((beDataObjInt *)temp_ret_363)->_data;
            expup_idx = 0;
            sp124 = 0;
            do {
                temp_ret_365 = MessageAccess::Player(self, expup_idx);
                expup_player = (void *)(temp_ret_365);
                temp_ret_366 = (beDataObjBool *)(igProperty_GetRecordByte((int)expup_player, "ISUSE"));
                if (temp_ret_366->_data != 0) {
                    temp_ret_367 = (int)igProperty_GetRecord(expup_player, "HP");
                    if (((beDataObjInt *)temp_ret_367)->_data != 0) {
                        temp_ret_368 = (int)igProperty_GetRecord(expup_player, "LEVEL");
                        expup_level = ((beDataObjInt *)temp_ret_368)->_data;
                        if (expup_level != 0x3E7) {
                            temp_ret_373 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_ret_361, "EXP");
                            var_s0_12 = temp_ret_373;
                            temp_ret_374 = (int)igProperty_GetRecord(expup_player, "EXPRITSU");
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
                            temp_ret_375 = (int)igProperty_GetRecord(expup_player, "EXP");
                            /* The old value is read before the second record lookup (it lives
                             * across that call); the add is in place. */
                            expup_exp = ((beDataObjInt *)temp_ret_375)->_data;
                            expup_exp = expup_exp + split;
                            temp_ret_376 = (int)igProperty_GetRecord(expup_player, "EXP");
                            ((beDataObjInt *)temp_ret_376)->_data = expup_exp;
                            bool leveled_up = false;
                            temp_ret_377 = (int)igProperty_GetRecord(expup_player, "NEXTEXP");
                            if (((beDataObjInt *)temp_ret_377)->_data <= expup_exp) {
loop_449:
                                expup_level += 1;
                                temp_ret_378 = (int)igProperty_GetRecord(expup_player, "LEVEL");
                                ((beDataObjInt *)temp_ret_378)->_data = expup_level;
                                beNDMWGameRam_RecomputeStats(self, expup_idx, 1);
                                beNDMWGameRam_StoreSpecies(self, expup_idx);
                                leveled_up = true;
                                if (expup_level != 0x3E7) {
                                    temp_ret_381 = (int)igProperty_GetRecord(expup_player, "NEXTEXP");
                                    if (expup_exp >= ((beDataObjInt *)temp_ret_381)->_data) {
                                        goto loop_449;
                                    }
                                }
                            }
                            if (leveled_up) {
                                temp_ret_382 = (int)igProperty_GetRecord(expup_player, "MHP");
                                temp_s0_10 = ((beDataObjInt *)temp_ret_382)->_data;
                                temp_ret_383 = (int)igProperty_GetRecord(expup_player, "MMP");
                                temp_s5 = ((beDataObjInt *)temp_ret_383)->_data;
                                temp_ret_384 = (int)igProperty_GetRecordString(expup_player, "DIGIMONNAME");
                                temp_ret_385 = (char *)(beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_384)->_data));
                                temp_ret_386 = beMessenger_PrepareDelayedSelection(self->_messenger, "MODELCTRL", temp_ret_385, expup_idx);
                                beMessenger_AppendString(self->_messenger, "i_getitempnl01");
                                beMessenger_AppendString(self->_messenger, "SQ_LVUP");
                                beMessenger_AppendFloat(self->_messenger, 1.0f);
                                Vec3f_Copy(&sp348, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(self->_messenger, &sp348);
                                beMessenger_AppendBool(self->_messenger, 0U);
                                beMessenger_AppendBool(self->_messenger, 1U);
                                temp_ret_387 = beMessenger_EnqueueSelected(self->_messenger, "SETEFFECT", 1);
                                temp_ret_388 = (int)igProperty_GetRecord(expup_player, "HP");
                                ((beDataObjInt *)temp_ret_388)->_data = temp_s0_10;
                                temp_ret_389 = (int)igProperty_GetRecord(expup_player, "MP");
                                ((beDataObjInt *)temp_ret_389)->_data = temp_s5;
                                temp_ret_390 = beMessenger_PrepareDelayedSelection(self->_messenger, "NUMBERCTRL", "lvnm", expup_idx);
                                beMessenger_AppendInt(self->_messenger, expup_level);
                                temp_ret_391 = beMessenger_EnqueueSelected(self->_messenger, "SETVALUE", 1);
                                temp_ret_392 = beMessenger_PrepareDelayedSelection(self->_messenger, "METERCTRL", "hpmt", expup_idx);
                                beMessenger_AppendFloat(self->_messenger, 100.0f);
                                temp_ret_393 = beMessenger_EnqueueSelected(self->_messenger, "SETPERCENT", 1);
                                temp_ret_394 = beMessenger_PrepareDelayedSelection(self->_messenger, "NUMBERCTRL", "hpnm", expup_idx);
                                beMessenger_AppendInt(self->_messenger, temp_s0_10);
                                temp_ret_395 = beMessenger_EnqueueSelected(self->_messenger, "SETVALUE", 1);
                                temp_ret_396 = beMessenger_PrepareDelayedSelection(self->_messenger, "METERCTRL", "mpmt", expup_idx);
                                beMessenger_AppendFloat(self->_messenger, 100.0f);
                                temp_ret_397 = beMessenger_EnqueueSelected(self->_messenger, "SETPERCENT", 1);
                                temp_ret_398 = beMessenger_PrepareDelayedSelection(self->_messenger, "NUMBERCTRL", "mpnm", expup_idx);
                                beMessenger_AppendInt(self->_messenger, temp_s5);
                                temp_ret_399 = beMessenger_EnqueueSelected(self->_messenger, "SETVALUE", 1);
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
            temp_ret_406 = MessageAccess::Player(self, temp_ret_400);
            temp_ret_407 = (int)igProperty_GetRecord(temp_ret_406, "MAHIRITSU");
            int stun_base = ((beDataObjInt *)temp_ret_407)->_data;
            temp_ret_412 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_ret_401, "RES_STUN");
            temp_v0_74 = temp_ret_412;
            temp_a0_7 = MessageAccess::Random(self)->genrand() % 100U;
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
            temp_ret_421 = MessageAccess::Player(self, temp_ret_417);
            temp_v0_78 = (void *)(temp_ret_421);
            temp_ret_422 = strcmp(sp480.p, "TIME");
            if (temp_ret_422 == 0) {
                int sp47C;
                sp47C = 0;
                temp_a2_8 = temp_v0_77 % 10000;
                var_s2_3 = 0;
                beNDMWGameRam_FindTechniqueRow(self, temp_v0_78, temp_a2_8, &sp47C);
                temp_ret_427 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp47C, "SKILL");
                temp_ret_428 = (int)igProperty_GetRecordIntList(temp_v0_78, "SKILL");
                temp_ret_429 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get((int *)(temp_ret_428 + 0xC)));
                temp_ret_430 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_429);
                temp_s1_4 = ((int *)temp_ret_430)[temp_ret_427];
                temp_ret_435 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_ret_418, "RES_POISON");
                temp_v0_79 = temp_ret_435;
                if (temp_s1_4 < 0x3E9) {
                    var_v1_7 = temp_s1_4 / 4;
                    var_s1_4 = (int)((int) ((var_v1_7 + 0x2EE) * (0x3E8 - temp_v0_79)) / 1000);
                } else if (temp_s1_4 < 0x7D1) {
                    var_s1_4 = (int)((int) ((((int) (temp_s1_4 - 0x3E8) / 5) + 0x3E8) * (0x3E8 - temp_v0_79)) / 1000);
                } else {
                    var_s1_4 = (int)((int) ((((int) (temp_s1_4 - 0x7D0) / 10) + 0x4B0) * (0x3E8 - temp_v0_79)) / 1000);
                }
                temp_v0_81 = MessageAccess::Random(self)->genrand() % 1000U;
                if ((int) temp_v0_81 < var_s1_4) {
                    var_s2_3 = 1;
                }
                if (var_s2_3 != 0) {
                    temp_ret_437 = (int)igProperty_GetRecord(temp_v0_78, "KASHIKOSA");
                    temp_s0_12 = ((beDataObjInt *)temp_ret_437)->_data;
                    temp_ret_442 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp47C, "TIME");
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
                var_s0_13 = -(beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp478, "HP") / 5);

                beMessenger_ClearInt(self->_messenger);
                beMessenger_AppendInt(self->_messenger, var_s0_13);
            }
            }
            break;
        case 16:
            temp_ret_449 = beMessenger_GetInt(self->_messenger, 0);
            temp_ret_450 = beMessenger_GetInt(self->_messenger, 1);
            temp_ret_451 = beMessenger_GetInt(self->_messenger, 2);
            temp_ret_453 = MessageAccess::Player(self, temp_ret_449);
            temp_v0_82 = (void *)(temp_ret_453);
            int sp474;
            sp474 = 0;
            temp_a2_10 = temp_ret_451 % 10000;
            var_s2_4 = 0;
            beNDMWGameRam_FindTechniqueRow(self, temp_v0_82, temp_a2_10, &sp474);
            temp_ret_458 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp474, "SKILL");
            temp_ret_459 = (int)igProperty_GetRecordIntList(temp_v0_82, "SKILL");
            temp_ret_460 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get((int *)(temp_ret_459 + 0xC)));
            temp_ret_461 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_460);
            temp_s3_3 = ((int *)temp_ret_461)[temp_ret_458];
            temp_ret_466 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_ret_450, "SEISHIN");
            temp_v0_83 = temp_ret_466;
            if (temp_s3_3 < 0x3E9) {
                var_v1_9 = temp_s3_3 / 4;
                var_s1_5 = (int)((int) ((var_v1_9 + 0x226) * 0x64) / temp_v0_83);
            } else if (temp_s3_3 < 0x7D1) {
                var_s1_5 = (int)((int) ((((int) (temp_s3_3 - 0x3E8) / 5) + 0x320) * 0x64) / temp_v0_83);
            } else {
                var_s1_5 = (int)((int) ((((int) (temp_s3_3 - 0x7D0) / 10) + 0x3E8) * 0x64) / temp_v0_83);
            }
            temp_v0_85 = MessageAccess::Random(self)->genrand() % 1000U;
            if ((int) temp_v0_85 < var_s1_5) {
                var_s2_4 = 1;
            }
            if (var_s2_4 != 0) {
                temp_ret_468 = (int)igProperty_GetRecord(temp_v0_82, "KASHIKOSA");
                temp_s0_13 = ((beDataObjInt *)temp_ret_468)->_data;
                temp_ret_473 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp474, "TIME");
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
            temp_ret_478 = MessageAccess::Player(self, temp_ret_474);
            temp_v0_86 = (void *)(temp_ret_478);
            int sp470;
            sp470 = 0;
            temp_a2_11 = temp_ret_476 % 10000;
            var_s2_5 = 0;
            beNDMWGameRam_FindTechniqueRow(self, temp_v0_86, temp_a2_11, &sp470);
            temp_ret_483 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp470, "SKILL");
            temp_ret_484 = (int)igProperty_GetRecordIntList(temp_v0_86, "SKILL");
            temp_ret_485 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get((int *)(temp_ret_484 + 0xC)));
            temp_ret_486 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_485);
            temp_s3_4 = ((int *)temp_ret_486)[temp_ret_483];
            temp_ret_491 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_ret_475, "SEISHIN");
            temp_v0_87 = temp_ret_491;
            if (temp_s3_4 < 0x3E9) {
                var_v1_11 = temp_s3_4 / 4;
                var_s1_6 = (int)((int) ((var_v1_11 + 0x226) * 0x64) / temp_v0_87);
            } else if (temp_s3_4 < 0x7D1) {
                var_s1_6 = (int)((int) ((((int) (temp_s3_4 - 0x3E8) / 5) + 0x320) * 0x64) / temp_v0_87);
            } else {
                var_s1_6 = (int)((int) ((((int) (temp_s3_4 - 0x7D0) / 10) + 0x3E8) * 0x64) / temp_v0_87);
            }
            temp_v0_89 = MessageAccess::Random(self)->genrand() % 1000U;
            if ((int) temp_v0_89 < var_s1_6) {
                var_s2_5 = 1;
            }
            if (var_s2_5 != 0) {
                temp_ret_493 = (int)igProperty_GetRecord(temp_v0_86, "KASHIKOSA");
                temp_s0_14 = ((beDataObjInt *)temp_ret_493)->_data;
                temp_ret_498 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp470, "TIME");
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
            temp_ret_506 = MessageAccess::Player(self, temp_ret_502);
            temp_v0_93 = (void *)(temp_ret_506);
            temp_ret_507 = strcmp(sp46C.p, "TIME");
            if (temp_ret_507 == 0) {
                int sp468;
                sp468 = 0;
                temp_a2_12 = temp_v0_92 % 10000;
                var_s2_6 = 0;
                beNDMWGameRam_FindTechniqueRow(self, temp_v0_93, temp_a2_12, &sp468);
                temp_ret_512 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp468, "SKILL");
                temp_ret_513 = (int)igProperty_GetRecordIntList(temp_v0_93, "SKILL");
                temp_ret_514 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get((int *)(temp_ret_513 + 0xC)));
                temp_ret_515 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_514);
                temp_s1_5 = ((int *)temp_ret_515)[temp_ret_512];
                temp_ret_520 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_91, "SEISHIN");
                temp_v0_94 = temp_ret_520;
                if (temp_s1_5 < 0x3E9) {
                    var_v1_13 = temp_s1_5 / 4;
                    var_s1_7 = (int)((int) ((var_v1_13 + 0x226) * 0x64) / temp_v0_94);
                } else if (temp_s1_5 < 0x7D1) {
                    var_s1_7 = (int)((int) ((((int) (temp_s1_5 - 0x3E8) / 5) + 0x320) * 0x64) / temp_v0_94);
                } else {
                    var_s1_7 = (int)((int) ((((int) (temp_s1_5 - 0x7D0) / 10) + 0x3E8) * 0x64) / temp_v0_94);
                }
                temp_v0_96 = MessageAccess::Random(self)->genrand() % 1000U;
                if ((int) temp_v0_96 < var_s1_7) {
                    var_s2_6 = 1;
                }
                if (var_s2_6 != 0) {
                    temp_ret_522 = (int)igProperty_GetRecord(temp_v0_93, "KASHIKOSA");
                    temp_s0_15 = ((beDataObjInt *)temp_ret_522)->_data;
                    temp_ret_527 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp468, "TIME");
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
                temp_ret_528 = strcmp(sp46C.p, "SUBAYASA");
                if (temp_ret_528 == 0) {
                    temp_a2_13 = temp_v0_92 % 10000;
                    int sp464;
                    sp464 = 0;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_93, temp_a2_13, &sp464);
                    temp_ret_533 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp464, "SKILL");
                    temp_ret_534 = (int)igProperty_GetRecordIntList(temp_v0_93, "SKILL");
                    temp_ret_535 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get((int *)(temp_ret_534 + 0xC)));
                    temp_ret_536 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_535);
                    temp_s1_6 = ((int *)temp_ret_536)[temp_ret_533];
                    temp_ret_541 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_91, "SUBAYASA");
                    temp_s0_16 = (int)((int) (-temp_ret_541 * 0x50) / 100);
                    temp_ret_546 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp464, "SUBAYASA");
                    var_s1_8 = temp_ret_546 - ((int) temp_s1_6 / 20);
                    if (var_s1_8 < temp_s0_16) {
                        var_s1_8 = temp_s0_16;
                    }
                    beMessenger_ClearInt(self->_messenger);
                    beMessenger_AppendInt(self->_messenger, -var_s1_8);
                } else {
                    temp_ret_547 = strcmp(sp46C.p, "CHIMEIRITSU");
                    if (temp_ret_547 == 0) {
                        temp_a2_14 = temp_v0_92 % 10000;
                        int sp460;
                        beNDMWGameRam_FindTechniqueRow(self, temp_v0_93, temp_a2_14, &sp460);
                        temp_ret_552 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp460, "CHIMEIRITSU");
                        beMessenger_ClearInt(self->_messenger);
                        beMessenger_AppendInt(self->_messenger, -temp_ret_552);
                    } else {
                        temp_ret_553 = strcmp(sp46C.p, "MAHIRITSU");
                        if (temp_ret_553 == 0) {
                            temp_a2_15 = temp_v0_92 % 10000;
                            int sp45C;
                            beNDMWGameRam_FindTechniqueRow(self, temp_v0_93, temp_a2_15, &sp45C);
                            temp_ret_558 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp45C, "MHIRITSU");
                            beMessenger_ClearInt(self->_messenger);
                            beMessenger_AppendInt(self->_messenger, -temp_ret_558);
                        } else {
                            temp_ret_559 = strcmp(sp46C.p, "KAIHIRITSU");
                            if (temp_ret_559 == 0) {
                                temp_a2_16 = temp_v0_92 % 10000;
                                int sp458;
                                beNDMWGameRam_FindTechniqueRow(self, temp_v0_93, temp_a2_16, &sp458);
                                temp_ret_564 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp458, "KAIHIRITSU");
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
            temp_ret_573 = MessageAccess::Player(self, temp_ret_569);
            temp_v0_100 = (void *)(temp_ret_573);
            temp_ret_574 = strcmp(sp454.p, "TIME");
            if (temp_ret_574 == 0) {
                int sp450;
                sp450 = 0;
                temp_a2_17 = temp_v0_99 % 10000;
                var_s2_7 = 0;
                beNDMWGameRam_FindTechniqueRow(self, temp_v0_100, temp_a2_17, &sp450);
                temp_ret_579 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp450, "SKILL");
                temp_ret_580 = (int)igProperty_GetRecordIntList(temp_v0_100, "SKILL");
                temp_ret_581 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get((int *)(temp_ret_580 + 0xC)));
                temp_ret_582 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_581);
                temp_s3_5 = ((int *)temp_ret_582)[temp_ret_579];
                temp_ret_587 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_98, "SEISHIN");
                temp_v0_101 = temp_ret_587;
                if (temp_s3_5 < 0x3E9) {
                    var_v1_15 = temp_s3_5 / 4;
                    var_s0_17 = (int)((int) ((var_v1_15 + 0x226) * 0x64) / temp_v0_101);
                } else if (temp_s3_5 < 0x7D1) {
                    var_s0_17 = (int)((int) ((((int) (temp_s3_5 - 0x3E8) / 5) + 0x320) * 0x64) / temp_v0_101);
                } else {
                    var_s0_17 = (int)((int) ((((int) (temp_s3_5 - 0x7D0) / 10) + 0x3E8) * 0x64) / temp_v0_101);
                }
                temp_v0_103 = MessageAccess::Random(self)->genrand() % 1000U;
                if ((int) temp_v0_103 < var_s0_17) {
                    var_s2_7 = 1;
                }
                if (var_s2_7 != 0) {
                    temp_ret_589 = (int)igProperty_GetRecord(temp_v0_100, "KASHIKOSA");
                    temp_s0_17 = ((beDataObjInt *)temp_ret_589)->_data;
                    temp_ret_594 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp450, "TIME");
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
                temp_ret_595 = strcmp(sp454.p, "TSUYOSA");
                if (temp_ret_595 == 0) {
                    temp_a2_18 = temp_v0_99 % 10000;
                    int sp44C;
                    sp44C = 0;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_100, temp_a2_18, &sp44C);
                    temp_ret_600 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp44C, "SKILL");
                    temp_ret_601 = (int)igProperty_GetRecordIntList(temp_v0_100, "SKILL");
                    temp_ret_602 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get((int *)(temp_ret_601 + 0xC)));
                    temp_ret_603 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_602);
                    temp_s1_7 = ((int *)temp_ret_603)[temp_ret_600];
                    temp_ret_608 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_98, "TSUYOSA");
                    temp_s0_18 = (int)((int) (-temp_ret_608 * 0x50) / 100);
                    temp_ret_613 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp44C, "TSUYOSA");
                    var_s1_9 = temp_ret_613 - ((int) temp_s1_7 / 20);
                    if (var_s1_9 < temp_s0_18) {
                        var_s1_9 = temp_s0_18;
                    }
                    beMessenger_ClearInt(self->_messenger);
                    beMessenger_AppendInt(self->_messenger, -var_s1_9);
                } else {
                    temp_ret_614 = strcmp(sp454.p, "MAMORI");
                    if (temp_ret_614 == 0) {
                        temp_a2_19 = temp_v0_99 % 10000;
                        int sp448;
                        sp448 = 0;
                        beNDMWGameRam_FindTechniqueRow(self, temp_v0_100, temp_a2_19, &sp448);
                        temp_ret_619 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp448, "SKILL");
                        temp_ret_620 = (int)igProperty_GetRecordIntList(temp_v0_100, "SKILL");
                        temp_ret_621 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get((int *)(temp_ret_620 + 0xC)));
                        temp_ret_622 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_621);
                        temp_s1_8 = ((int *)temp_ret_622)[temp_ret_619];
                        temp_ret_627 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_98, "MAMORI");
                        temp_s0_19 = (int)((int) (-temp_ret_627 * 0x50) / 100);
                        temp_ret_632 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp448, "MAMORI");
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
            temp_ret_638 = MessageAccess::Player(self, temp_ret_634);
            temp_v0_104 = (void *)(temp_ret_638);
            temp_s3_6 = temp_ret_636 % 10000;
            var_s5_7 = 0;
            temp_ret_643 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s3_6, "TYPE");
            switch (temp_ret_643) {
            case 0:
                temp_ret_644 = (int)igProperty_GetRecord(temp_v0_104, "BOUGYORITSU");
                temp_s0_20 = ((beDataObjInt *)temp_ret_644)->_data;
                temp_v0_106 = MessageAccess::Random(self)->genrand() % 100U;
                if (temp_s0_20 <= (int) temp_v0_106) {
                    temp_ret_646 = (int)igProperty_GetRecord(temp_v0_104, "SUBAYASA");
                    temp_s1_9 = ((beDataObjInt *)temp_ret_646)->_data;
                    temp_ret_647 = (int)igProperty_GetRecord(temp_v0_104, "KAIHIRITSU");
                    temp_s0_21 = ((beDataObjInt *)temp_ret_647)->_data;
                    temp_ret_652 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_ret_635, "SUBAYASA");
                    temp_ret_657 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s3_6, "MEICHURITSU");
                    temp_a2_20 = MessageAccess::Random(self)->genrand() % 100U;
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
            temp_ret_664 = MessageAccess::Player(self, temp_ret_659);
            temp_v0_110 = (void *)(temp_ret_664);
            temp_s5_2 = temp_ret_661 % 10000;
            temp_ret_669 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s5_2, "TYPE");
            temp_v0_111 = temp_ret_669;
            var_s3_4 = 0;
            var_s2_8 = -1;
            switch (temp_v0_111) {
            case 0:
                temp_ret_670 = (int)igProperty_GetRecord(temp_v0_110, "MAMORI");
                temp_s3_7 = ((beDataObjInt *)temp_ret_670)->_data;
                temp_ret_671 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&temp_v0_109->_downDataList));
                if (temp_ret_671 == 0) {
                    var_s1_11 = 0;
                } else {
                    temp_ret_672 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&temp_v0_109->_downDataList));
                    temp_ret_673 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_672);
                    var_s1_11 = ((int *)temp_ret_673)[4];
                }
                temp_ret_678 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_108, "TSUYOSA");
                int e2p_diff_678; e2p_diff_678 = temp_ret_678 - var_s1_11;
                temp_ret_683 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s5_2, "TSUYOSA");
                var_s3_4 = (int)((int) (e2p_diff_678 * temp_ret_683) / temp_s3_7);
                if (var_s3_4 < 0) {
                    var_s3_4 = 0;
                } else if (var_s3_4 > 0x1869F) {
                    var_s3_4 = 0x1869F;
                }
                temp_ret_688 = (char *)(beDataBase_GetRecordString(MessageDatabases::Eneatk(self, "eneatk"), temp_s5_2, "ZOKUSEI"));
                temp_v0_112 = (char *)(temp_ret_688);
                var_s1_12 = 0;
                temp_ret_689 = strcmp(temp_v0_112, "fire");
                if (temp_ret_689 == 0) {
                    temp_ret_690 = (int)igProperty_GetRecord(temp_v0_110, "HONOOTEIKO");
                    var_s1_12 = ((beDataObjInt *)temp_ret_690)->_data;
                    var_s2_8 = 0;
                } else {
                    temp_ret_691 = strcmp(temp_v0_112, "ice");
                    if (temp_ret_691 == 0) {
                        temp_ret_692 = (int)igProperty_GetRecord(temp_v0_110, "KOORITEIKO");
                        var_s1_12 = ((beDataObjInt *)temp_ret_692)->_data;
                        var_s2_8 = 1;
                    } else {
                        temp_ret_693 = strcmp(temp_v0_112, "thunder");
                        if (temp_ret_693 == 0) {
                            temp_ret_694 = (int)igProperty_GetRecord(temp_v0_110, "KAMINARITEIKO");
                            var_s1_12 = ((beDataObjInt *)temp_ret_694)->_data;
                            var_s2_8 = 2;
                        } else {
                            temp_ret_695 = strcmp(temp_v0_112, "dark");
                            if (temp_ret_695 == 0) {
                                temp_ret_696 = (int)igProperty_GetRecord(temp_v0_110, "YAMITEIKO");
                                var_s1_12 = ((beDataObjInt *)temp_ret_696)->_data;
                                var_s2_8 = 3;
                            }
                        }
                    }
                }
                if (var_s1_12 != 0) {
                    temp_a2_21 = MessageAccess::Random(self)->genrand() % 1000U;
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
                    temp_ret_698 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&temp_v0_109->_downDataList));
                    if (temp_ret_698 == 0) {
                        var_s0_19 = 0;
                    } else {
                        temp_ret_699 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&temp_v0_109->_downDataList));
                        temp_ret_700 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_699);
                        var_s0_19 = ((int *)temp_ret_700)[1];
                    }
                    temp_ret_705 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_108, "CHIMEIRITSU");
                    e2p_diff_705 = temp_ret_705 - var_s0_19;
                    temp_ret_710 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s5_2, "CHIMEIRITSU");
                    temp_v0_114 = temp_ret_710;
                    temp_a0_8 = MessageAccess::Random(self)->genrand() % 10000U;
                    if (((0x64 - e2p_diff_705) * (0x64 - temp_v0_114)) <= (int) temp_a0_8) {
                        var_v0_15 = (int)((int) (var_s3_4 * (temp_v0_114 / 2 + 0x5A)) / 100);
                        var_s3_4 += var_v0_15;
                    }
                }
                break;
            case 1:
                temp_ret_716 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s5_2, "TSUYOSA");
                temp_v0_116 = temp_ret_716;
                if (temp_v0_116 != 0) {
                    temp_ret_721 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_108, "KASHIKOSA");
                    temp_ret_722 = (int)igProperty_GetRecord(temp_v0_110, "SEISHIN");
                    var_s3_4 = (int)((int) (temp_ret_721 * temp_v0_116) / (int) ((beDataObjInt *)temp_ret_722)->_data);
                    if (var_s3_4 < 0) {
                        var_s3_4 = 0;
                    } else if (var_s3_4 > 0x1869F) {
                        var_s3_4 = 0x1869F;
                    }
                    var_s1_13 = 0;
                    temp_ret_727 = (char *)(beDataBase_GetRecordString(MessageDatabases::Eneatk(self, "eneatk"), temp_s5_2, "ZOKUSEI"));
                    temp_v0_117 = (char *)(temp_ret_727);
                    temp_ret_728 = strcmp(temp_v0_117, "fire");
                    if (temp_ret_728 == 0) {
                        temp_ret_729 = (int)igProperty_GetRecord(temp_v0_110, "HONOOTEIKO");
                        var_s1_13 = ((beDataObjInt *)temp_ret_729)->_data;
                        var_s2_8 = 0;
                    } else {
                        temp_ret_730 = strcmp(temp_v0_117, "ice");
                        if (temp_ret_730 == 0) {
                            temp_ret_731 = (int)igProperty_GetRecord(temp_v0_110, "KOORITEIKO");
                            var_s1_13 = ((beDataObjInt *)temp_ret_731)->_data;
                            var_s2_8 = 1;
                        } else {
                            temp_ret_732 = strcmp(temp_v0_117, "thunder");
                            if (temp_ret_732 == 0) {
                                temp_ret_733 = (int)igProperty_GetRecord(temp_v0_110, "KAMINARITEIKO");
                                var_s1_13 = ((beDataObjInt *)temp_ret_733)->_data;
                                var_s2_8 = 2;
                            } else {
                                temp_ret_734 = strcmp(temp_v0_117, "dark");
                                if (temp_ret_734 == 0) {
                                    temp_ret_735 = (int)igProperty_GetRecord(temp_v0_110, "YAMITEIKO");
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
                        temp_ret_740 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s5_2, "CHIMEIRITSU");
                        temp_v0_118 = temp_ret_740;
                        if (temp_v0_118 != 0) {
                            if (var_s1_13 < 0x3E9) {
                                var_s0_20 = (0x3E8 - var_s1_13) + (temp_v0_118 * 0x64);
                            } else {
                                var_s0_20 = (temp_v0_118 * 0x64) - ((int) (var_s1_13 - 0x3E8) / 10);
                            }
                            temp_v0_120 = MessageAccess::Random(self)->genrand() % 10000U;
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
                temp_ret_746 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s5_2, "TSUYOSA");
                temp_ret_747 = (int)igProperty_GetRecord(temp_v0_110, "MHP");
                var_s3_4 = (int)((int) (((beDataObjInt *)temp_ret_747)->_data * temp_ret_746) / 100);
                if (var_s3_4 < 0) {
                    var_s3_4 = 0;
                } else if (var_s3_4 > 0x1869F) {
                    var_s3_4 = 0x1869F;
                }
                var_s1_14 = 0;
                temp_ret_752 = (char *)(beDataBase_GetRecordString(MessageDatabases::Eneatk(self, "eneatk"), temp_s5_2, "ZOKUSEI"));
                temp_v0_121 = (char *)(temp_ret_752);
                temp_ret_753 = strcmp(temp_v0_121, "fire");
                if (temp_ret_753 == 0) {
                    temp_ret_754 = (int)igProperty_GetRecord(temp_v0_110, "HONOOTEIKO");
                    var_s1_14 = ((beDataObjInt *)temp_ret_754)->_data;
                    var_s2_8 = 0;
                } else {
                    temp_ret_755 = strcmp(temp_v0_121, "ice");
                    if (temp_ret_755 == 0) {
                        temp_ret_756 = (int)igProperty_GetRecord(temp_v0_110, "KOORITEIKO");
                        var_s1_14 = ((beDataObjInt *)temp_ret_756)->_data;
                        var_s2_8 = 1;
                    } else {
                        temp_ret_757 = strcmp(temp_v0_121, "thunder");
                        if (temp_ret_757 == 0) {
                            temp_ret_758 = (int)igProperty_GetRecord(temp_v0_110, "KAMINARITEIKO");
                            var_s1_14 = ((beDataObjInt *)temp_ret_758)->_data;
                            var_s2_8 = 2;
                        } else {
                            temp_ret_759 = strcmp(temp_v0_121, "dark");
                            if (temp_ret_759 == 0) {
                                temp_ret_760 = (int)igProperty_GetRecord(temp_v0_110, "YAMITEIKO");
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
                int e2p_rng = MessageAccess::Random(self)->genrand() & 3;
                temp_v0_124 = MessageAccess::Random(self)->genrand() % (unsigned int) (var_s3_4 * 0x19);
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
                temp_ret_769 = MessageAccess::Player(self, temp_ret_763);
                temp_s5_3 = temp_ret_764 % 10000;
                int temp_ret_774 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s5_3, "TSUYOSA");
                temp_ret_779 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s5_3, "SEQUENCE");
                temp_v0_129 = temp_ret_779;
                temp_ret_780 = (int)igProperty_GetRecord(temp_ret_769, "MHP");
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
                    temp_ret_786 = ObjectRefAssigner::Assign((char *)temp_v0_128 + 0x28, temp_ret_782);
                }
                temp_ret_788 = ObjectRef_Get_003e92a0((char *)temp_v0_128 + 0x28);
                temp_ret_789 = beNDMWLoadIntf2_beBaseInfoDataList_FindProperty(temp_ret_788, g_propertyNameField[0], "ONE");
                temp_ret_790 = ObjectRef_Get_00406e00(&((beModelCtrlInfoRamData *)temp_ret_789)->_work);
                temp_ret_791 = (void *)(ObjectRef_Get_00406df0(&((beNDMWMdlPEBaseInfoWork *)temp_ret_790)->_moveObjectList));
                temp_v0_130 = (void *)(temp_ret_791);
                if (((beModelCtrlMoveObjectList *)temp_v0_130)->_count != 0) {
                    temp_ret_792 = (void *)(DataList_GetWordAt_00406dd0((igDataList *)temp_v0_130, 1));
                    if (((beModelCtrlMoveObject *)temp_ret_792)->_isRun != 0) {
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
            temp_ret_800 = MessageAccess::Player(self, temp_ret_793);
            temp_v0_133 = (void *)(temp_ret_800);
            temp_s6_2 = temp_ret_795 % 10000;
            temp_ret_805 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s6_2, "TYPE");
            temp_v0_134 = temp_ret_805;
            var_s8_2 = 0;
            var_s1_16 = 0;
            var_s0_22 = 0;
            switch (temp_v0_134) {
            case 0:
                switch (temp_v0_131) { case 1: case 2: {
                    temp_ret_806 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&temp_v0_132->_downDataList));
                    if (temp_ret_806 == 0) {
                        var_s0_23 = 0;
                    } else {
                        temp_ret_807 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&temp_v0_132->_downDataList));
                        temp_ret_808 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_807);
                        var_s0_23 = ((int *)temp_ret_808)[2];
                    }
                    temp_ret_813 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), sp120, "MAHIRITSU");
                    var_s8_2 = temp_ret_813 - var_s0_23;
                    var_s0_22 = 1;
                } }
                break;
            case 1:
                var_s1_16 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s6_2, "MAHIRITSU");
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
                temp_ret_819 = (int)igProperty_GetRecord(temp_v0_133, "MHP");
                temp_s3_8 = ((beDataObjInt *)temp_ret_819)->_data;
                temp_ret_820 = (int)igProperty_GetRecord(temp_v0_133, "MAHITEIKOU");
                temp_s0_23 = ((beDataObjInt *)temp_ret_820)->_data;
                temp_a2_22 = MessageAccess::Random(self)->genrand() % 100U;
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
            temp_ret_828 = MessageAccess::Player(self, temp_ret_825);
            temp_v0_138 = (void *)(temp_ret_828);
            temp_s3_9 = temp_ret_826 % 10000;
            temp_ret_829 = strcmp(sp444.p, "TIME");
            if (temp_ret_829 == 0) {
                var_s2_10 = 0;
                temp_ret_834 = (char *)(beDataBase_GetRecordString(MessageDatabases::Eneatk(self, "eneatk"), temp_s3_9, "KOUKA"));
                temp_ret_835 = strcmp(temp_ret_834, "doku");
                if (temp_ret_835 == 0) {
                    int temp_ret_840 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s3_9, "KOUKARANK");
                    temp_ret_841 = (int)igProperty_GetRecord(temp_v0_138, "DOKUTEIKOU");
                    int temp_s0_24 = ((beDataObjInt *)temp_ret_841)->_data;
                    temp_v1_8 = MessageAccess::Random(self)->genrand() % 100U;
                    if ((int) temp_v1_8 < (temp_s0_24 + ((temp_ret_840 * 0xF) + 0x1E))) {
                        temp_ret_847 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s3_9, "KOUKATIME");
                        var_s2_10 = temp_s0_24 / 2 + temp_ret_847;
                    }
                    if (var_s2_10 == 0) {
                        var_s2_10 = -1;
                    }
                }
                beMessenger_ClearInt(self->_messenger);
                beMessenger_AppendInt(self->_messenger, var_s2_10);
            } else {
                temp_ret_848 = strcmp(sp444.p, "DAMAGE");
                if (temp_ret_848 == 0) {
                    temp_ret_849 = (int)igProperty_GetRecord(temp_v0_138, "MHP");
                    temp_s0_25 = ((beDataObjInt *)temp_ret_849)->_data;
                    temp_ret_854 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s3_9, "KOUKARANK");
                    beMessenger_ClearInt(self->_messenger);
                    beMessenger_AppendInt(self->_messenger, (int) (temp_s0_25 * temp_ret_854) / 100);
                } else {
                    temp_ret_855 = strcmp(sp444.p, "GEDOKU");
                    if (temp_ret_855 == 0) {
                        temp_ret_860 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s3_9, "GEDOKU");
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
            /* matching construct: this lookup stays written out (and its result declared here); through
             * MessageAccess::Player the player and the modulo result swap callee-saved registers */
            temp_ret_865 = (void *)(beNDMWGameRam_igSmartPointer_beDataObjListList_Get(&self->_playerDataListList));
            int temp_ret_866 = beNDMWLoadIntf2_igObjectList_Get(temp_ret_865, temp_ret_862);
            int temp_s2_2 = temp_ret_864 % 10000;
            temp_ret_871 = (char *)(beDataBase_GetRecordString(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_2, "KOUKA"));
            int var_s1_17 = 0;
            temp_ret_872 = strcmp(temp_ret_871, "sleep");
            if (temp_ret_872 == 0) {
                temp_ret_877 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_2, "KOUKARANK");
                temp_ret_882 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_ret_863, "KASHIKOSA");
                temp_ret_883 = (int)igProperty_GetRecord(temp_ret_866, "SEISHIN");
                temp_s3_10 = ((beDataObjInt *)temp_ret_883)->_data;
                temp_a2_23 = MessageAccess::Random(self)->genrand() % 10000U;
                temp_s0_26 = (((int) (temp_ret_882 * 3) / (int) temp_s3_10) + 0x64) - ((int) temp_s3_10 / 40);
                int hit_base = temp_ret_877 * 5;
                if ((int) temp_a2_23 < (hit_base * temp_s0_26)) {
                    temp_ret_889 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_2, "KOUKATIME");
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
            temp_ret_894 = MessageAccess::Player(self, temp_ret_890);
            temp_v0_142 = (void *)(temp_ret_894);
            temp_s3_11 = temp_ret_892 % 10000;
            temp_ret_899 = (char *)(beDataBase_GetRecordString(MessageDatabases::Eneatk(self, "eneatk"), temp_s3_11, "KOUKA"));
            var_s2_11 = 0;
            temp_ret_900 = strcmp(temp_ret_899, "ashidome");
            if (temp_ret_900 == 0) {
                temp_ret_905 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s3_11, "KOUKARANK");
                temp_ret_910 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s3_11, "TYPE");
                temp_v0_143 = temp_ret_910;
                sp110 = 1;
                if (temp_v0_143 != 2) {
                    temp_ret_915 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_141, "KASHIKOSA");
                    temp_ret_916 = (int)igProperty_GetRecord(temp_v0_142, "SEISHIN");
                    unsigned int temp_s0_27 = ((beDataObjInt *)temp_ret_916)->_data;
                    temp_a2_24 = MessageAccess::Random(self)->genrand() % 10000U;
                    if ((temp_ret_905 * 5 * ((((int) (temp_ret_915 * 3) / (int) temp_s0_27) + 0x64) - ((int) temp_s0_27 / 40))) <= (int) temp_a2_24) {
                        sp110 = 0;
                    }
                }
                if (sp110) {
                    if (temp_v0_143 == 2) {
                        temp_ret_922 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s3_11, "KOUKATIME");
                        var_s2_11 = temp_ret_922;
                    } else {
                        temp_ret_927 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s3_11, "KOUKATIME");
                        temp_ret_932 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_141, "KASHIKOSA");
                        temp_ret_933 = (int)igProperty_GetRecord(temp_v0_142, "SEISHIN");
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
            temp_ret_941 = MessageAccess::Player(self, temp_v0_147);
            temp_v0_149 = (void *)(temp_ret_941);
            temp_s2_3 = temp_ret_939 % 10000;
            temp_ret_942 = strcmp(sp440.p, "TIME");
            if (temp_ret_942 == 0) {
                temp_ret_947 = (char *)(beDataBase_GetRecordString(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_3, "KOUKA"));
                var_s1_18 = 0;
                temp_ret_948 = strcmp(temp_ret_947, "freeze");
                if (temp_ret_948 == 0) {
                    temp_ret_953 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_3, "KOUKARANK");
                    temp_ret_958 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_148, "KASHIKOSA");
                    temp_ret_959 = (int)igProperty_GetRecord(temp_v0_149, "SEISHIN");
                    temp_s3_12 = ((beDataObjInt *)temp_ret_959)->_data;
                    temp_a4_2 = MessageAccess::Random(self)->genrand() % 10000U;
                    temp_s0_28 = (((int) (temp_ret_958 * 3) / (int) temp_s3_12) + 0x64) - ((int) temp_s3_12 / 40);
                    int rec_scaled = (int) (temp_ret_953 * 0xA0) / 100;
                    if ((int) temp_a4_2 < (rec_scaled * temp_s0_28)) {
                        temp_ret_965 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_3, "KOUKATIME");
                        var_s1_18 = (int)((int) (temp_ret_965 * temp_s0_28) / 100);
                    }
                    if (var_s1_18 == 0) {
                        var_s1_18 = -1;
                    }
                }
                beMessenger_ClearInt(self->_messenger);
                beMessenger_AppendInt(self->_messenger, var_s1_18);
            } else {
                temp_ret_966 = strcmp(sp440.p, "SUBAYASA");
                if (temp_ret_966 == 0) {
                    temp_ret_967 = (int)igProperty_GetRecordIntList(temp_v0_149, "DOWNDATA");
                    temp_ret_968 = (void *)(beNDMWGameRam_beDataObjIntList_GetData((int *)temp_ret_967));
                    temp_v0_151 = (void *)(temp_ret_968);
                    temp_v1_9 = ((igIntList *)temp_v0_151)->_count;
                    IntListSet((igIntList *)temp_v0_151, 0, 0);
                    beNDMWGameRam_RecomputeStats(self, temp_v0_147, 1);
                    temp_ret_975 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_3, "KOUKARANK");
                    temp_ret_980 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_148, "KASHIKOSA");
                    temp_ret_981 = (int)igProperty_GetRecord(temp_v0_149, "SEISHIN");
                    temp_v0_152 = (void *)(temp_ret_981);
                    var_s1_19 = (temp_ret_975 + ((int) ((int) (temp_ret_980 * 0x96) / (int) ((beDataObjInt *)temp_v0_152)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_152)->_data / 80);
                    if (var_s1_19 < 0x14) {
                        var_s1_19 = 0x14;
                    }
                    if (var_s1_19 > 0x50) {
                        var_s1_19 = 0x50;
                    }
                    temp_ret_982 = (int)igProperty_GetRecord(temp_v0_149, "SUBAYASA");
                    int temp_s0_29 = ((beDataObjInt *)temp_ret_982)->_data;
                    beMessenger_ClearInt(self->_messenger);
                    beMessenger_AppendInt(self->_messenger, (int) (temp_s0_29 * var_s1_19) / 100);
                } else {
                    temp_ret_983 = strcmp(sp440.p, "MEICHURITSU");
                    if (temp_ret_983 == 0) {
                        temp_ret_984 = (int)igProperty_GetRecordIntList(temp_v0_149, "DOWNDATA");
                        temp_ret_985 = (void *)(beNDMWGameRam_beDataObjIntList_GetData((int *)temp_ret_984));
                        temp_v0_153 = (void *)(temp_ret_985);
                        temp_v1_10 = ((igIntList *)temp_v0_153)->_count;
                        IntListSet((igIntList *)temp_v0_153, 1, 0);
                        beNDMWGameRam_RecomputeStats(self, temp_v0_147, 1);
                        temp_ret_992 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_3, "KOUKARANK");
                        temp_ret_997 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_148, "KASHIKOSA");
                        temp_ret_998 = (int)igProperty_GetRecord(temp_v0_149, "SEISHIN");
                        temp_v0_154 = (void *)(temp_ret_998);
                        var_s1_20 = (temp_ret_992 + ((int) ((int) (temp_ret_997 * 0x96) / (int) ((beDataObjInt *)temp_v0_154)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_154)->_data / 80);
                        if (var_s1_20 < 0x14) {
                            var_s1_20 = 0x14;
                        }
                        if (var_s1_20 > 0x50) {
                            var_s1_20 = 0x50;
                        }
                        temp_ret_999 = (int)igProperty_GetRecord(temp_v0_149, "MEICHURITSU");
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
            temp_ret_1008 = MessageAccess::Player(self, temp_v0_156);
            temp_v0_158 = (void *)(temp_ret_1008);
            temp_s2_4 = temp_ret_1006 % 10000;
            temp_ret_1009 = strcmp(sp43C.p, "TIME");
            if (temp_ret_1009 == 0) {
                temp_ret_1014 = (char *)(beDataBase_GetRecordString(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_4, "KOUKA"));
                var_s1_21 = 0;
                temp_ret_1015 = strcmp(temp_ret_1014, "powerdown");
                if (temp_ret_1015 == 0) {
                    temp_ret_1020 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_4, "KOUKARANK");
                    temp_ret_1025 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_157, "KASHIKOSA");
                    temp_ret_1026 = (int)igProperty_GetRecord(temp_v0_158, "SEISHIN");
                    temp_s3_13 = ((beDataObjInt *)temp_ret_1026)->_data;
                    temp_a4_3 = MessageAccess::Random(self)->genrand() % 10000U;
                    temp_s0_31 = (((int) (temp_ret_1025 * 3) / (int) temp_s3_13) + 0x64) - ((int) temp_s3_13 / 40);
                    int rec_scaled = (int) (temp_ret_1020 * 0xA0) / 100;
                    if ((int) temp_a4_3 < (rec_scaled * temp_s0_31)) {
                        temp_ret_1032 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_4, "KOUKATIME");
                        var_s1_21 = (int)((int) (temp_ret_1032 * temp_s0_31) / 100);
                    }
                    if (var_s1_21 == 0) {
                        var_s1_21 = -1;
                    }
                }
                beMessenger_ClearInt(self->_messenger);
                beMessenger_AppendInt(self->_messenger, var_s1_21);
            } else {
                temp_ret_1033 = strcmp(sp43C.p, "TSUYOSA");
                if (temp_ret_1033 == 0) {
                    temp_ret_1034 = (int)igProperty_GetRecordIntList(temp_v0_158, "DOWNDATA");
                    temp_ret_1035 = (void *)(beNDMWGameRam_beDataObjIntList_GetData((int *)temp_ret_1034));
                    temp_v0_160 = (void *)(temp_ret_1035);
                    temp_v1_11 = ((igIntList *)temp_v0_160)->_count;
                    IntListSet((igIntList *)temp_v0_160, 4, 0);
                    beNDMWGameRam_RecomputeStats(self, temp_v0_156, 1);
                    temp_ret_1042 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_4, "KOUKARANK");
                    temp_ret_1047 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_157, "KASHIKOSA");
                    temp_ret_1048 = (int)igProperty_GetRecord(temp_v0_158, "SEISHIN");
                    temp_v0_161 = (void *)(temp_ret_1048);
                    var_s1_22 = (temp_ret_1042 + ((int) ((int) (temp_ret_1047 * 0x96) / (int) ((beDataObjInt *)temp_v0_161)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_161)->_data / 80);
                    if (var_s1_22 < 0x14) {
                        var_s1_22 = 0x14;
                    }
                    if (var_s1_22 > 0x50) {
                        var_s1_22 = 0x50;
                    }
                    temp_ret_1049 = (int)igProperty_GetRecord(temp_v0_158, "TSUYOSA");
                    int temp_s0_32 = ((beDataObjInt *)temp_ret_1049)->_data;
                    beMessenger_ClearInt(self->_messenger);
                    beMessenger_AppendInt(self->_messenger, (int) (temp_s0_32 * var_s1_22) / 100);
                } else {
                    temp_ret_1050 = strcmp(sp43C.p, "MAMORI");
                    if (temp_ret_1050 == 0) {
                        temp_ret_1051 = (int)igProperty_GetRecordIntList(temp_v0_158, "DOWNDATA");
                        temp_ret_1052 = (void *)(beNDMWGameRam_beDataObjIntList_GetData((int *)temp_ret_1051));
                        temp_v0_162 = (void *)(temp_ret_1052);
                        temp_v1_12 = ((igIntList *)temp_v0_162)->_count;
                        IntListSet((igIntList *)temp_v0_162, 5, 0);
                        beNDMWGameRam_RecomputeStats(self, temp_v0_156, 1);
                        temp_ret_1059 = beDataBase_GetRecordInt(MessageDatabases::Eneatk(self, "eneatk"), temp_s2_4, "KOUKARANK");
                        temp_ret_1064 = beDataBase_GetRecordInt(MessageDatabases::Enemy(self, "enemy"), temp_v0_157, "KASHIKOSA");
                        temp_ret_1065 = (int)igProperty_GetRecord(temp_v0_158, "SEISHIN");
                        temp_v0_163 = (void *)(temp_ret_1065);
                        var_s1_23 = (temp_ret_1059 + ((int) ((int) (temp_ret_1064 * 0x96) / (int) ((beDataObjInt *)temp_v0_163)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_163)->_data / 80);
                        var_s1_23 = (temp_ret_1059 + ((int) ((int) (temp_ret_1064 * 0x96) / (int) ((beDataObjInt *)temp_v0_163)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_163)->_data / 80);
                        if (var_s1_23 < 0x14) {
                            var_s1_23 = 0x14;
                        }
                        if (var_s1_23 > 0x50) {
                            var_s1_23 = 0x50;
                        }
                        temp_ret_1066 = (int)igProperty_GetRecord(temp_v0_158, "MAMORI");
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
            temp_ret_1072 = MessageAccess::Player(self, temp_v0_164);
            temp_v0_165 = (void *)(temp_ret_1072);
            if (temp_v0_164 == temp_ret_1069) {
                temp_s5_4 = temp_ret_1070 % 10000;
                if (temp_s5_4 == 40 || temp_s5_4 == 45) {
                    int sp438;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_165, temp_s5_4, &sp438);
                    temp_ret_1077 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp438, "SKILL");
                    temp_v0_166 = temp_ret_1077;
                    if (temp_v0_166 != 8) {
                        if (temp_v0_166 != 7) {
                            temp_ret_1078 = (int)igProperty_GetRecordIntList(temp_v0_165, "SKILL");
                            temp_ret_1079 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)temp_ret_1078)->_data));
                            temp_ret_1080 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_1079);
                            var_s3_5 = *(int *)(temp_ret_1080 + (temp_v0_166 * 4));
                        } else {
                            temp_ret_1081 = (int)igProperty_GetRecordIntList(temp_v0_165, "SKILL");
                            temp_ret_1082 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)temp_ret_1081)->_data));
                            temp_ret_1083 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_1082);
                            var_s3_5 = ((int *)temp_ret_1083)[7];
                        }
                    } else {
                        temp_ret_1084 = (int)igProperty_GetRecordIntList(temp_v0_165, "SKILL");
                        temp_ret_1085 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)temp_ret_1084)->_data));
                        temp_ret_1086 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_1085);
                        var_s3_5 = ((int *)temp_ret_1086)[8];
                    }
                    temp_ret_1091 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp438, "HP");
                    temp_ret_1092 = (int)igProperty_GetRecord(temp_v0_165, "KASHIKOSA");
                    int pre_sum = temp_ret_1091 + var_s3_5;
                    temp_s2_5 = pre_sum + ((beDataObjInt *)temp_ret_1092)->_data;
                    temp_ret_1093 = beNDMWGameRam_ChangeHp(self, temp_v0_164, temp_s2_5, -1);
                    if (temp_s5_4 == 0x2D) {
                        temp_ret_1094 = (int)igProperty_GetRecordString(temp_v0_165, "DIGIMONNAME");
                        temp_ret_1095 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1094)->_data);
                        beMessenger_SendNamed(self->_messenger, "PLAYER", temp_ret_1095, temp_v0_164, GETMATRIX);
                        beMessenger_GetMatrix(&sp270, self->_messenger, 0);
                        igMatrix44f_GetTranslation(&sp270, &sp3D8);
                        { NearbyListRef sp434 = beNDMWGameRam_CollectNearbyNonzeroHp(self, "PLAYER", temp_v0_164, &sp3D8);
                        temp_s3_14 = ((igIntList *)sp434.value)->_count;
                        for (var_s1_24 = 0; var_s1_24 < temp_s3_14; ++var_s1_24) {
                                temp_ret_1096 = beNDMWLoadIntf2_igIntList_GetData(sp434.value);
                                temp_s5_5 = ((int *)temp_ret_1096)[var_s1_24];
                                temp_ret_1097 = beNDMWGameRam_ChangeHp(self, temp_s5_5, temp_s2_5, -1);
                                temp_ret_1099 = MessageAccess::Player(self, temp_s5_5);
                                temp_ret_1100 = (int)igProperty_GetRecordString((void *)temp_ret_1099, "DIGIMONNAME");
                                temp_ret_1101 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1100)->_data);
                                temp_ret_1102 = beMessenger_PrepareDelayedSelection(self->_messenger, "PLAYER", temp_ret_1101, temp_s5_5);
                                beMessenger_AppendString(self->_messenger, "x_250healhit00");
                                beMessenger_AppendString(self->_messenger, "SQ_HEALEFONLY");
                                beMessenger_AppendFloat(self->_messenger, 1.0f);
                                Vec3f_Copy(&sp338, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(self->_messenger, &sp338);
                                beMessenger_AppendBool(self->_messenger, 0U);
                                beMessenger_AppendBool(self->_messenger, 1U);
                                temp_ret_1103 = beMessenger_EnqueueSelected(self->_messenger, "SETEFFECT", 1);
                        }
                        }
                    }
                } else if (temp_s5_4 == 55 || temp_s5_4 == 60) {
                    int sp430;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_165, temp_s5_4, &sp430);
                    temp_ret_1108 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp430, "SKILL");
                    temp_v0_167 = temp_ret_1108;
                    switch (temp_v0_167) { default: temp_ret_1109 = (int)igProperty_GetRecordIntList(temp_v0_165, "SKILL");
 temp_ret_1110 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)temp_ret_1109)->_data));
 temp_ret_1111 = (int)beNDMWLoadIntf2_igIntList_GetData(temp_ret_1110); break; case 7: temp_ret_1112 = (int)igProperty_GetRecordIntList(temp_v0_165, "SKILL");
 temp_ret_1113 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)temp_ret_1112)->_data));
 temp_ret_1114 = (int)beNDMWLoadIntf2_igIntList_GetData(temp_ret_1113); break; case 8: temp_ret_1115 = (int)igProperty_GetRecordIntList(temp_v0_165, "SKILL");
 temp_ret_1116 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)temp_ret_1115)->_data));
 temp_ret_1117 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_1116); break; }
temp_ret_1118 = (int)igProperty_GetRecordString(temp_v0_165, "DIGIMONNAME");
                    temp_ret_1119 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1118)->_data);
                    beMessenger_SendNamed(self->_messenger, "PLAYER", temp_ret_1119, temp_v0_164, "GETPEBASEWORK");
                    temp_ret_1120 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                    temp_ret_1121 = (void *)(beMessenger_GetObject(self->_messenger, 1));
                    temp_v0_168 = (void *)(temp_ret_1121);
                    temp_ret_1122 = beNDMWMdlPEBaseInfoWork_IsPoisoned(temp_v0_168);
                    if (temp_ret_1122 != 0) {
                        temp_s6_3 = ((sp430 - temp_s5_4) + 5) - ((beNDMWMdlPEBaseInfoWork *)temp_v0_168)->_poisonEndurance;
                        temp_v0_170 = MessageAccess::Random(self)->genrand() % 10U;
                        if (temp_s6_3 >= (int) temp_v0_170) {
                            temp_ret_1124 = beNDMWMdlPEBaseInfoWork_CurePoison(temp_v0_168, temp_ret_1120);
                        }
                    }
                    if (temp_s5_4 == 0x3C) {
                        temp_ret_1125 = (int)igProperty_GetRecordString(temp_v0_165, "DIGIMONNAME");
                        temp_ret_1126 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1125)->_data);
                        beMessenger_SendNamed(self->_messenger, "PLAYER", temp_ret_1126, temp_v0_164, GETMATRIX);
                        beMessenger_GetMatrix(&sp230, self->_messenger, 0);
                        igMatrix44f_GetTranslation(&sp230, &sp3C8);
                        { NearbyListRef sp42C = beNDMWGameRam_CollectNearbyNonzeroHp(self, "PLAYER", temp_v0_164, &sp3C8);
                        temp_v0_171 = ((igIntList *)sp42C.value)->_count;
                        int sp100 = temp_v0_171;
                        for (var_s3_6 = 0; var_s3_6 < sp100; ++var_s3_6) {
                                temp_ret_1127 = beNDMWLoadIntf2_igIntList_GetData(sp42C.value);
                                temp_s2_6 = ((int *)temp_ret_1127)[var_s3_6];
                                temp_ret_1129 = MessageAccess::Player(self, temp_s2_6);
                                temp_v0_172 = (void *)(temp_ret_1129);
                                temp_ret_1130 = (int)igProperty_GetRecordString(temp_v0_172, "DIGIMONNAME");
                                temp_ret_1131 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1130)->_data);
                                beMessenger_SendNamed(self->_messenger, "PLAYER", temp_ret_1131, temp_s2_6, "GETPEBASEWORK");
                                temp_ret_1132 = (void *)(beMessenger_GetObject(self->_messenger, 0));
                                temp_ret_1133 = (void *)(beMessenger_GetObject(self->_messenger, 1));
                                temp_v0_173 = (void *)(temp_ret_1133);
                                temp_ret_1134 = beNDMWMdlPEBaseInfoWork_IsPoisoned(temp_v0_173);
                                if (temp_ret_1134 != 0) {
                                    temp_s8_2 = ((sp430 - temp_s5_4) + 5) - ((beNDMWMdlPEBaseInfoWork *)temp_v0_173)->_poisonEndurance;
                                    temp_v0_175 = MessageAccess::Random(self)->genrand() % 10U;
                                    if (temp_s8_2 >= (int) temp_v0_175) {
                                        temp_ret_1136 = beNDMWMdlPEBaseInfoWork_CurePoison(temp_v0_173, temp_ret_1132);
                                    }
                                }
                                temp_ret_1137 = (int)igProperty_GetRecordString(temp_v0_172, "DIGIMONNAME");
                                temp_ret_1138 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1137)->_data);
                                temp_ret_1139 = beMessenger_PrepareDelayedSelection(self->_messenger, "PLAYER", temp_ret_1138, temp_s2_6);
                                beMessenger_AppendString(self->_messenger, "x_250curehit00");
                                beMessenger_AppendString(self->_messenger, "SQ_CUREEFONLY");
                                beMessenger_AppendFloat(self->_messenger, 1.0f);
                                Vec3f_Copy(&sp328, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(self->_messenger, &sp328);
                                beMessenger_AppendBool(self->_messenger, 0U);
                                beMessenger_AppendBool(self->_messenger, 1U);
                                temp_ret_1140 = beMessenger_EnqueueSelected(self->_messenger, "SETEFFECT", 1);
                        }
                        }
                    }
                } else if (temp_s5_4 == 50 || temp_s5_4 == -50) {
                    if (temp_s5_4 >= 0) {
                        int sp428;
                        beNDMWGameRam_FindTechniqueRow(self, temp_v0_165, temp_s5_4, &sp428);
                        temp_a0_10 = sp428 * 4;
                        var_s3_7 = ((const int *)((const char *)g_skillGainTable + 424))[sp428];
                        var_s2_12 = ((const int *)((const char *)g_skillGainTable + 456))[sp428];
                    } else {
                        var_s3_7 = g_raiseFirstValue[0];
                        var_s2_12 = g_raiseSecondValue[0];
                    }
                    igMatrix44f_SetIdentity(&sp2B0);
                    temp_ret_1141 = (int)igProperty_GetRecordString(temp_v0_165, "DIGIMONNAME");
                    temp_ret_1142 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1141)->_data);
                    beMessenger_SendNamed(self->_messenger, "PLAYER", temp_ret_1142, temp_v0_164, GETMATRIX);
                    beMessenger_GetMatrix(&sp1F0, self->_messenger, 0);
                    igMatrix44f_Copy(&sp2B0, &sp1F0);
                    igMatrix44f_GetTranslation(&sp2B0, &sp3B8);
                    { NearbyListRef sp424 = beNDMWGameRam_CollectNearbyNonzeroHp(self, "PLAYER2", -1, &sp3B8);
                    temp_s5_6 = ((igIntList *)sp424.value)->_count;
                    for (var_s1_25 = 0; var_s1_25 < temp_s5_6; ++var_s1_25) {
                            temp_ret_1143 = beNDMWLoadIntf2_igIntList_GetData(sp424.value);
                            beMessenger_SelectReceivers(self->_messenger, "PLAYER2", 0, ((int *)temp_ret_1143)[var_s1_25]);
                            beMessenger_AppendMatrix(self->_messenger, &sp2B0);
                            beMessenger_AppendInt(self->_messenger, var_s3_7);
                            beMessenger_AppendInt(self->_messenger, var_s2_12);
                            beMessenger_DispatchSelected(self->_messenger, (const char *)"RAISE");
                    }
                    }
                } else if (temp_s5_4 == 65) {
                    int sp420;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_165, temp_s5_4, &sp420);
                    temp_ret_1149 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp420, "SKILL");
                    temp_ret_1150 = (int)igProperty_GetRecord(temp_v0_165, "KASHIKOSA");
                    temp_s2_7 = ((beDataObjInt *)temp_ret_1150)->_data;
                    temp_ret_1155 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp420, "TIME");
                    int spF0 = temp_ret_1155 + temp_s2_7;
                    temp_ret_1156 = (int)igProperty_GetRecordIntList(temp_v0_165, "SKILL");
                    temp_ret_1157 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)temp_ret_1156)->_data));
                    temp_ret_1158 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_1157);
                    temp_s2_8 = *(int *)(temp_ret_1158 + (temp_ret_1149 * 4));
                    temp_ret_1163 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp420, "SUBAYASA");
                    int spE0 = ((int) temp_s2_8 / 5) + temp_ret_1163;
                    temp_ret_1164 = (int)igProperty_GetRecordString(temp_v0_165, "DIGIMONNAME");
                    temp_ret_1165 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1164)->_data);
                    beMessenger_SendNamed(self->_messenger, "PLAYER", temp_ret_1165, temp_v0_164, GETMATRIX);
                    beMessenger_GetMatrix(&sp1B0, self->_messenger, 0);
                    igMatrix44f_GetTranslation(&sp1B0, &sp3A8);
                    { NearbyListRef sp41C = beNDMWGameRam_CollectNearbyNonzeroHp(self, "PLAYER", temp_v0_164, &sp3A8);
                    temp_ret_1166 = (void *)(ObjectRef_Get_00406dc0((int *)&sp41C.value));
                    temp_v0_176 = (void *)(temp_ret_1166);
                    RecoveryList::append(temp_v0_176, temp_v0_164);
                    temp_v0_177 = ((igIntList *)sp41C.value)->_count;
                    int spD0 = temp_v0_177;
                    for (var_s5_8 = 0; var_s5_8 < spD0; ++var_s5_8) {
                            temp_ret_1168 = beNDMWLoadIntf2_igIntList_GetData(sp41C.value);
                            temp_s3_15 = ((int *)temp_ret_1168)[var_s5_8];
                            temp_ret_1170 = MessageAccess::Player(self, temp_s3_15);
                            temp_v0_178 = (void *)(temp_ret_1170);
                            temp_ret_1175 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp420, "CHIMEIRITSU");
                            temp_ret_1180 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp420, "MHIRITSU");
                            temp_ret_1185 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp420, "KAIHIRITSU");
                            beMessenger_PushArgContext(self->_messenger);
                            temp_ret_1186 = (int)igProperty_GetRecordString(temp_v0_178, "DIGIMONNAME");
                            temp_ret_1187 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1186)->_data);
                            beMessenger_SelectReceivers(self->_messenger, "PLAYER", temp_ret_1187, temp_s3_15);
                            beMessenger_AppendInt(self->_messenger, spF0);
                            beMessenger_AppendInt(self->_messenger, spE0);
                            beMessenger_AppendInt(self->_messenger, temp_ret_1175);
                            beMessenger_AppendInt(self->_messenger, temp_ret_1180);
                            beMessenger_AppendInt(self->_messenger, temp_ret_1185);
                            beMessenger_DispatchSelected(self->_messenger, (const char *)"SETSPEEDUP");
                            if (temp_s3_15 != temp_v0_164) {
                                temp_ret_1189 = (int)igProperty_GetRecordString(temp_v0_178, "DIGIMONNAME");
                                temp_ret_1190 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1189)->_data);
                                temp_ret_1191 = beMessenger_PrepareDelayedSelection(self->_messenger, "PLAYER", temp_ret_1190, temp_s3_15);
                                beMessenger_AppendString(self->_messenger, "x_250uphit00");
                                beMessenger_AppendString(self->_messenger, "SQ_UPEFONLY");
                                beMessenger_AppendFloat(self->_messenger, 1.0f);
                                Vec3f_Copy(&sp318, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(self->_messenger, &sp318);
                                beMessenger_AppendBool(self->_messenger, 0U);
                                beMessenger_AppendBool(self->_messenger, 1U);
                                temp_ret_1192 = beMessenger_EnqueueSelected(self->_messenger, "SETEFFECT", 1);
                            }
                            beMessenger_PopArgContext(self->_messenger);
                    }
                    }
                } else if (temp_s5_4 == 80) {
                    int sp418;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_165, temp_s5_4, &sp418);
                    temp_ret_1193 = (int)igProperty_GetRecord(temp_v0_165, "KASHIKOSA");
                    temp_s2_9 = ((beDataObjInt *)temp_ret_1193)->_data;
                    temp_ret_1198 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp418, "TIME");
                    int sum80a = temp_ret_1198 + temp_s2_9;
                    temp_ret_1203 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp418, "SKILL");
                    temp_ret_1204 = (int)igProperty_GetRecordIntList(temp_v0_165, "SKILL");
                    temp_ret_1205 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)temp_ret_1204)->_data));
                    temp_ret_1206 = beNDMWLoadIntf2_igIntList_GetData(temp_ret_1205);
                    temp_s2_10 = *(int *)(temp_ret_1206 + (temp_ret_1203 * 4));
                    temp_ret_1210 = MessageDatabases::PcTech(self);
                    temp_s2_11 = (int)((int) temp_s2_10 / 5);
                    temp_ret_1211 = beDataBase_GetRecordInt(temp_ret_1210, sp418, "MAXHP");
                    int sum80d = temp_s2_11 + temp_ret_1211;
                    temp_ret_1216 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp418, "TSUYOSA");
                    int spC0 = temp_s2_11 + temp_ret_1216;
                    temp_ret_1221 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp418, "MAMORI");
                    int spB0 = temp_s2_11 + temp_ret_1221;
                    temp_ret_1222 = (int)igProperty_GetRecordString(temp_v0_165, "DIGIMONNAME");
                    temp_ret_1223 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1222)->_data);
                    beMessenger_SendNamed(self->_messenger, "PLAYER", temp_ret_1223, temp_v0_164, GETMATRIX);
                    beMessenger_GetMatrix(&sp170, self->_messenger, 0);
                    igMatrix44f_GetTranslation(&sp170, &sp398);
                    { NearbyListRef sp414 = beNDMWGameRam_CollectNearbyNonzeroHp(self, "PLAYER", temp_v0_164, &sp398);
                    temp_ret_1224 = (void *)(ObjectRef_Get_00406dc0((int *)&sp414.value));
                    temp_v0_179 = (void *)(temp_ret_1224);
                    RecoveryList::append(temp_v0_179, temp_v0_164);
                    temp_s6_4 = ((igIntList *)sp414.value)->_count;
                    for (var_s5_9 = 0; var_s5_9 < temp_s6_4; ++var_s5_9) {
                            temp_ret_1226 = beNDMWLoadIntf2_igIntList_GetData(sp414.value);
                            temp_s3_16 = ((int *)temp_ret_1226)[var_s5_9];
                            temp_ret_1228 = MessageAccess::Player(self, temp_s3_16);
                            temp_v0_180 = (void *)(temp_ret_1228);
                            beMessenger_PushArgContext(self->_messenger);
                            temp_ret_1229 = (int)igProperty_GetRecordString(temp_v0_180, "DIGIMONNAME");
                            temp_ret_1230 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1229)->_data);
                            beMessenger_SelectReceivers(self->_messenger, "PLAYER", temp_ret_1230, temp_s3_16);
                            beMessenger_AppendInt(self->_messenger, sum80a);
                            beMessenger_AppendInt(self->_messenger, spC0);
                            beMessenger_AppendInt(self->_messenger, spB0);
                            beMessenger_AppendInt(self->_messenger, sum80d);
                            beMessenger_DispatchSelected(self->_messenger, (const char *)"SETPOWERUP");
                            if (temp_s3_16 != temp_v0_164) {
                                temp_ret_1232 = (int)igProperty_GetRecordString(temp_v0_180, "DIGIMONNAME");
                                temp_ret_1233 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1232)->_data);
                                temp_ret_1234 = beMessenger_PrepareDelayedSelection(self->_messenger, "PLAYER", temp_ret_1233, temp_s3_16);
                                beMessenger_AppendString(self->_messenger, "x_250uphit00");
                                beMessenger_AppendString(self->_messenger, "SQ_UPEFONLY");
                                beMessenger_AppendFloat(self->_messenger, 1.0f);
                                Vec3f_Copy(&sp308, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(self->_messenger, &sp308);
                                beMessenger_AppendBool(self->_messenger, 0U);
                                beMessenger_AppendBool(self->_messenger, 1U);
                                temp_ret_1235 = beMessenger_EnqueueSelected(self->_messenger, "SETEFFECT", 1);
                            }
                            beMessenger_PopArgContext(self->_messenger);
                    }
                    }
                } else if (temp_s5_4 == 75) {
                    int sp410;
                    beNDMWGameRam_FindTechniqueRow(self, temp_v0_165, temp_s5_4, &sp410);
                    temp_ret_1240 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp410, "TIME");
                    temp_ret_1245 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp410, "FIRE");
                    int spAC = temp_ret_1245;
                    temp_ret_1250 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp410, "ICE");
                    int spA8 = temp_ret_1250;
                    temp_ret_1255 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp410, "THUNDER");
                    int spA4 = temp_ret_1255;
                    temp_ret_1260 = beDataBase_GetRecordInt(MessageDatabases::PcTech(self), sp410, "DARK");
                    temp_ret_1261 = (int)igProperty_GetRecordString(temp_v0_165, "DIGIMONNAME");
                    temp_ret_1262 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1261)->_data);
                    beMessenger_SendNamed(self->_messenger, "PLAYER", temp_ret_1262, temp_v0_164, GETMATRIX);
                    beMessenger_GetMatrix(&sp130, self->_messenger, 0);
                    igMatrix44f_GetTranslation(&sp130, &sp388);
                    { NearbyListRef sp40C = beNDMWGameRam_CollectNearbyNonzeroHp(self, "PLAYER", temp_v0_164, &sp388);
                    temp_ret_1263 = (void *)(ObjectRef_Get_00406dc0((int *)&sp40C.value));
                    temp_v0_181 = (void *)(temp_ret_1263);
                    RecoveryList::append(temp_v0_181, temp_v0_164);
                    temp_s6_5 = ((igIntList *)sp40C.value)->_count;
                    for (var_s5_10 = 0; var_s5_10 < temp_s6_5; ++var_s5_10) {
                            temp_ret_1265 = beNDMWLoadIntf2_igIntList_GetData(sp40C.value);
                            temp_s3_17 = ((int *)temp_ret_1265)[var_s5_10];
                            temp_ret_1267 = MessageAccess::Player(self, temp_s3_17);
                            temp_v0_182 = (void *)(temp_ret_1267);
                            beMessenger_PushArgContext(self->_messenger);
                            temp_ret_1268 = (int)igProperty_GetRecordString(temp_v0_182, "DIGIMONNAME");
                            temp_ret_1269 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1268)->_data);
                            beMessenger_SelectReceivers(self->_messenger, "PLAYER", temp_ret_1269, temp_s3_17);
                            beMessenger_AppendInt(self->_messenger, temp_ret_1240);
                            beMessenger_AppendInt(self->_messenger, spAC);
                            beMessenger_AppendInt(self->_messenger, spA8);
                            beMessenger_AppendInt(self->_messenger, spA4);
                            beMessenger_AppendInt(self->_messenger, temp_ret_1260);
                            beMessenger_DispatchSelected(self->_messenger, (const char *)"SETREFRACT");
                            if (temp_s3_17 != temp_v0_164) {
                                temp_ret_1271 = (int)igProperty_GetRecordString(temp_v0_182, "DIGIMONNAME");
                                temp_ret_1272 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1271)->_data);
                                temp_ret_1273 = beMessenger_PrepareDelayedSelection(self->_messenger, "PLAYER", temp_ret_1272, temp_s3_17);
                                beMessenger_AppendString(self->_messenger, "x_250uphit00");
                                beMessenger_AppendString(self->_messenger, "SQ_UPEFONLY");
                                beMessenger_AppendFloat(self->_messenger, 1.0f);
                                Vec3f_Copy(&sp2F8, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(self->_messenger, &sp2F8);
                                beMessenger_AppendBool(self->_messenger, 0U);
                                beMessenger_AppendBool(self->_messenger, 1U);
                                temp_ret_1274 = beMessenger_EnqueueSelected(self->_messenger, "SETEFFECT", 1);
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
    }
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
                tail_common = (void *)(beNDMWGameRam_igSmartPointer_beDataObjList_Get(&self->_commonDataList));
                temp_ret_1278 = (void *)(beNDMWGameRam_igSmartPointer_beDataObjListList_Get(&self->_playerDataListList));
        tail_player = (void *)beNDMWLoadIntf2_igObjectList_Get(temp_ret_1278, tail_idx);
                temp_ret_1280 = (int)igProperty_GetRecordString(tail_player, "DIGIMONNAME");
        temp_ret_1281 = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)temp_ret_1280)->_data);
        temp_v0_186 = temp_ret_1281;
        StringListStore::SetAt((igStringRefList *)beNDMWGameRam_beDataObjStringList_GetData((int *)(igProperty_GetRecordStringList(tail_common, "BKCHIPNAME"))), tail_idx, StringRef(temp_v0_186 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_186)));
        temp_s0_34 = tail_idx * 2;
        temp_ret_1289 = (int)igProperty_GetRecord(tail_player, "BIT");
        temp_s3_18 = ((beDataObjInt *)temp_ret_1289)->_data;
        temp_ret_1290 = (int)igProperty_GetRecordIntList(tail_common, "BKCHIPDATA");
        temp_ret_1291 = (void *)(beNDMWGameRam_beDataObjIntList_GetData((int *)temp_ret_1290));
        temp_v0_188 = (void *)(temp_ret_1291);
        temp_v1_14 = ((igIntList *)temp_v0_188)->_count;
        if ((temp_v1_14 != 0) && (temp_s0_34 >= 0) && (temp_s0_34 < temp_v1_14)) {
            temp_ret_1292 = beNDMWLoadIntf2_igIntList_GetData(temp_v0_188);
            *(int *)(temp_ret_1292 + (temp_s0_34 * 4)) = temp_s3_18;
        }
        temp_ret_1293 = (int)igProperty_GetRecord(tail_player, "BIT");
        ((beDataObjInt *)temp_ret_1293)->_data = 0;
        temp_s4 = temp_s0_34 + 1;
        temp_ret_1294 = (int)igProperty_GetRecord(tail_player, "LEVEL");
        temp_s0_35 = ((beDataObjInt *)temp_ret_1294)->_data;
        if ((temp_s0_35 != 0x3E7) && (temp_s0_35 != 1)) {
            temp_ret_1295 = (int)igProperty_GetRecord(tail_player, "EXP");
            temp_v0_189 = ((beDataObjInt *)temp_ret_1295)->_data;
            temp_a4_4 = LevelExpCurve::g(temp_s0_35 - 1, temp_s0_35);
            var_s3_8 = temp_v0_189 - ((temp_a4_4 - LevelExpCurve::g(temp_s0_35 - 2, temp_s0_35 - 1)) * 2) / 10;
            if (var_s3_8 < temp_a4_4) {
                var_s3_8 = temp_a4_4;
            }
            int new_value = temp_v0_189 - var_s3_8;
            temp_ret_1296 = (int)igProperty_GetRecordIntList(tail_common, "BKCHIPDATA");
            temp_ret_1297 = (void *)(beNDMWGameRam_beDataObjIntList_GetData((int *)temp_ret_1296));
            temp_v0_190 = (void *)(temp_ret_1297);
            int temp_v1_15 = ((igIntList *)temp_v0_190)->_count;
            if ((temp_v1_15 != 0) && (temp_s4 >= 0) && (temp_s4 < temp_v1_15)) {
                temp_ret_1298 = beNDMWLoadIntf2_igIntList_GetData(temp_v0_190);
                *(int *)(temp_ret_1298 + (temp_s4 * 4)) = new_value;
            }
            temp_ret_1299 = (int)igProperty_GetRecord(tail_player, "EXP");
            ((beDataObjInt *)temp_ret_1299)->_data = var_s3_8;
        }
        return 1;
    default:
        return 0;
    }
    return 1;
}


/* igDataList, the base of every typed list, holds the igMemoryRef _data at +16. */


int beNDMWGameRam_igStringRefList_GetData(igDataList *p)
{
    return p->_data;
}

int beNDMWGameRam_beDataObjStringList_GetData(int *p)
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

int *beNDMWGameRam_CreateDataListRef(int *ref, int *allocator) {
    *ref = beBaseInfoDataList_Create(*allocator);
    return ref;
}

int beNDMWGameRam_beDataObjIntList_GetData(int *p)
{
    return ((IntProperty *)p)->value;
}

int beNDMWGameRam_igSmartPointer_igRandomNumber_Get(int *p)
{
    return *p;
}

ObjectRefTarget **beNDMWGameRam_igSmartPointer_beDataBase_Assign(ObjectRefTarget **destination,ObjectRefTarget *incoming) {
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

int beNDMWGameRam_igSmartPointer_beDataBase_Get(int *p)
{
    return *p;
}

int beNDMWGameRam_igSmartPointer_igIntList_Get(int *p)
{
    return *p;
}

int beNDMWGameRam_igBoolList_GetData(igUnsignedCharList *p)
{
    return p->_data;
}

int beNDMWGameRam_igSmartPointer_igBoolList_Get(int *p)
{
    return *p;
}

void beNDMWGameRam_igObjectList_Remove(void *list, int index)
{
    List_RemoveWordAt(list, index);
}

AllocatorValue beNDMWGameRam_beNDMWItemAbilityChip_MakeAllocatorValue(int value)
{
    return AllocatorValue(value);
}

AllocatorValue beNDMWGameRam_beNDMWItemYellowArmor_MakeAllocatorValue(int value)
{
    return AllocatorValue(value);
}

AllocatorValue beNDMWGameRam_beNDMWItemBlueArmor_MakeAllocatorValue(int value)
{
    return AllocatorValue(value);
}

AllocatorValue beNDMWGameRam_beNDMWItemWeapon_MakeAllocatorValue(int value)
{
    return AllocatorValue(value);
}

int beNDMWGameRam_igSmartPointer_igObjectList_Get(int *p)
{
    return *p;
}

int beNDMWGameRam_beDataObjInt_GetData(beDataObjInt *p)
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

int beNDMWGameRam_igSmartPointer_beDataObjListList_Get(int *p)
{
    return *p;
}

int beNDMWGameRam_igSmartPointer_beDataObjList_Get(int *p)
{
    return *p;
}

int beNDMWGameRam_igStringRef_Get(int *p)
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

#pragma pop
