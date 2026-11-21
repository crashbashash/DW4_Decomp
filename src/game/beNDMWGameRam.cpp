#include "dw4/core/igSmartPointer.h"
#include "dw4/support/reflected.h"
#include "dw4/game/ndmw/beNDMWGameRam.h"
#include "dw4/game/ndmw/listSet.h"
#include "dw4/datapump/igRandomNumberDispatchView.h"
#include "dw4/game/ndmw/NdmwSharedStrings.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beBaseInfoManager.h"
#include "dw4/game/beDBManager.h"
#include "dw4/game/beDataBase.h"
#include "dw4/game/beFont.h"
#include "dw4/game/beDataObjBool.h"
#include "dw4/game/beDataObjBoolList.h"
#include "dw4/game/beDataObjFloatList.h"
#include "dw4/game/beDataObjInt.h"
#include "dw4/game/beDataObjIntList.h"
#include "dw4/game/beDataObjList.h"
#include "dw4/game/beDataObjListList.h"
#include "dw4/game/beDataObjObjectList.h"
#include "dw4/game/beDataObjString.h"
#include "dw4/game/beDataObjStringList.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/ndmw/beNDMWGameRamInfo.h"
#include "dw4/game/ndmw/beNDMWGameRamInfoRam.h"
#include "dw4/game/ndmw/beNDMWItemAbilityChip.h"
#include "dw4/game/ndmw/beNDMWItemBase.h"
#include "dw4/game/ndmw/beNDMWItemBlueArmor.h"
#include "dw4/game/ndmw/beNDMWItemDisk.h"
#include "dw4/game/ndmw/beNDMWItemWaza.h"
#include "dw4/game/ndmw/beNDMWItemWeapon.h"
#include "dw4/game/ndmw/beNDMWItemYellowArmor.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2.h"
#include "dw4/game/ndmw/beNDMWMdlPEBaseInfoWork.h"
#include "dw4/game/beUnicodeObj.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/maths/igMathConstants.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igResult.h"
#include "dw4/core/igTDataList.h"
#include <string.h>
#include "dw4/core/igStringRef.h"
#include "dw4/core/igStringRefList.h"
#include "dw4/support/list-services.h"
#include "dw4/core/igMetaEnum.h"
#define RELEASE_REF(T, q) { T *rr = (q); if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }
#define ALLOC(owner, var) { void *got = ((void *)((Gap::Core::igObject *)(owner))->getMemoryPool()); if (g_useOwnerAllocator) var = got; else var = ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0)); }
#define RESERVE(LT, h, SZ) { LT *l = (LT *)(h)->_data; if (!(entry->count < l->_count)) ((Gap::Core::igDataList *)l)->setCapacity(entry->count, SZ); }
#define RESIZE(LT, h, SZ) { int n = entry->count; LT *l = (LT *)(h)->_data; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else ((Gap::Core::igDataList *)l)->resizeAndSetCount(n, SZ); } }
/* Sentinel for the `absolute` argument of the HP update: apply `delta` instead. */
#define NO_ABSOLUTE_HP (-1)
#define NEARBY_RADIUS_SQUARED 900.0f
#define REFERENCE_COUNT_MASK 0x7fffffULL
#define CLAMP_ATTR(v) if ((v) <= 0) (v) = 1; if ((v) > 9999) (v) = 9999;

class StringRef;
/* The property records Gap::Core::igObjectList::search returns: the value sits after a 12-byte header. */
struct IntListProperty { char header[12]; igIntList *list; };
struct DataListProperty { char header[12]; igDataList *list; };
struct ObjectListProperty { char header[12]; igObjectList *list; };
struct StringListProperty { char header[12]; igStringRefList *list; };
/* An int list as the stat code reads it: the element buffer after the 16-byte list header. */
struct IntValues { char header[16]; int *values; };
struct IntValuesProperty { char header[12]; IntValues *list; };
/* kept local: no include/dw4 home (only CoreLibrary.h declares these). */

extern "C" void beNDMWGameRam_UpdateRam(void);
extern "C" int beNDMWGameRam_GetMeta(void);
extern "C" int beNDMWGameRam_GetInfoMeta(void);
/* The shared string pool, created on first use. */
struct SharedStringPool {
    static inline int get()
    {
        if (g_stringPool == 0) {
            int pool = (int)StringPool_Allocate(16);
            if (pool != 0) pool = (int)StringPool_Construct((StringPool *)pool);
            g_stringPool = (StringPool *)pool;
        }
        return (int)g_stringPool;
    }
};
extern "C" void beNDMWGameRam_AddPowerSocketBonus(int self, int player, int *total, const char *name, int withRevision);
extern "C" void beNDMWGameRam_AddPowerPocketBonus(int self, int player, int *total, const char *name);
extern "C" void beNDMWGameRam_AddMainPocketBonus(int self, int player, int *total, const char *name);
extern "C" void beNDMWGameRam_AddSubSlotBonus(int self, int player, int *total, const char *name, int withAbility);
extern "C" int beNDMWGameRam_beDataObjStringList_GetData(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_igIntList_Deref(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_beModelCtrlMoveObjectList_Get(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_beModelCtrlInfoWork_Get(int *p);
extern "C" int *beNDMWGameRam_CreateDataListRef(int *ref, int *allocator);
extern "C" int beNDMWGameRam_beDataObjIntList_GetData(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_igRandomNumber_Get(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_beDataBase_Get(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_igIntList_Get(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_igBoolList_Get(int *p);
/* What the allocator helpers return by value: a class with a copy constructor, so it comes back through a hidden return slot. */ struct AllocatorValue { int v; AllocatorValue(int value):v(value) {} AllocatorValue(const AllocatorValue &o):v(o.v) {} };
extern "C" AllocatorValue beNDMWGameRam_beNDMWItemAbilityChip_MakeAllocatorValue(int value);
extern "C" AllocatorValue beNDMWGameRam_beNDMWItemYellowArmor_MakeAllocatorValue(int value);
extern "C" AllocatorValue beNDMWGameRam_beNDMWItemBlueArmor_MakeAllocatorValue(int value);
extern "C" AllocatorValue beNDMWGameRam_beNDMWItemWeapon_MakeAllocatorValue(int value);
extern "C" int beNDMWGameRam_igSmartPointer_igObjectList_Get(int *p);
extern "C" int StringPool_GetInstance(void);
extern "C" int beNDMWGameRam_igSmartPointer_beDataObjListList_Get(int *p);
extern "C" int beNDMWGameRam_igSmartPointer_beDataObjList_Get(int *p);
extern "C" int beNDMWGameRam_igStringRef_Get(int *p);
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
    char *const *ref() const { return &p; }
    StringRef(int s) : p((char *)s) {}
    StringRef(const char *s) : p((char *)s) {}
    StringRef(void *s) : p((char *)s) {}
    static void release(char **slot) {
        char *token = *slot;
        if (token) {
            int *header = (int *)(token - 8);
            if (--header[1] == 0) StringChunk_ReleaseHeader((StringChunk *)header[0], (StringTokenHeader *)header);
        }
    }
    ~StringRef() { release(&p); }
};
struct Fill {
    /* Clears every slot of the string list to the empty token.
     * matching construct: the empty-token holder is a temporary of the call statement (passed by const reference), which
     * takes the lowest frame slot (retail slot 140) below the case holders, and the loop counters stay the caller's
     * variables. Written in place in the case the function is 12 bytes long; with the counters local to this inline
     * the registers differ. */
    static inline void emptyStrings(beDataObjStringList *h5, const StringRef &str, int &n5, int **&d5, int &i5) {
        igStringRefList *l5 = (igStringRefList *)h5->_data;
        n5 = l5->_count;
        d5 = (int **)l5->_data;
        for (i5 = 0; i5 < n5; i5++) {
            int *cur = (int *)str.p;
            if (cur) ++cur[-1];
            int *old = *d5;
            if (old) { int *hd = old - 2; int rc = old[-1] - 1; old[-1] = rc; if (rc == 0) StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd); }
            *d5 = (int *)str.p;
            d5++;
        }
    }
};
extern "C" void beNDMWGameRam_BuildDataList(beNDMWGameRam *self, igObjectList *out, const DataLayoutEntry *layout);
/* Owning stack reference to one new item record, released at the end of each loop pass. */
class ItemRef {
public:
    igObject *p;
    ItemRef(igObject *o) : p(o) {}
    ~ItemRef() { igObject *o = p; igObject::release(o); }
};
extern "C" void beNDMWGameRam_ResetPlayer(beNDMWGameRam *self, int player);
/* Owning stack reference to the new per-player data-list list, released the same way. */
class PlayerDataListListRef {
public:
    igObject *p;
    PlayerDataListListRef(igObject *o) : p(o) {}
    ~PlayerDataListListRef() { igObject *o = p; igObject::release(o); }
};
extern "C" void beNDMWGameRam_Start(beNDMWGameRam *self);
/* reference-counted engine object header: refcount word at +4 */
typedef struct RefCountedHeader { int p0; unsigned refs; } RefCountedHeader;
/* Object-reference list header: count at +8, capacity at +12, buffer at +16. */
typedef struct ObjectRefList { char p[8]; int count; int cap; RefCountedHeader **data; } ObjectRefList;
extern "C" void beNDMWGameRam_Stop(beNDMWGameRam *self);
extern "C" void beNDMWGameRam_Prepare(beNDMWGameRam *self);
/* Owning stack reference to the info's ram object created here, released on scope exit. */
class RamRef {
public:
    beNDMWGameRamInfoRam *p;
    RamRef(beNDMWGameRamInfoRam *o) : p(o) {}
    ~RamRef() { beNDMWGameRamInfoRam *o = p; igObject::release(o); }
};
extern "C" int beNDMWGameRam_AddInfo(beNDMWGameRam *self);
extern "C" int beNDMWGameRam_FindSpecies(beNDMWGameRam *self, const char *modelName);
extern "C" void beNDMWGameRam_SelectSpecies(beNDMWGameRam *self, int index, int species);
extern "C" void beNDMWGameRam_StoreSpecies(beNDMWGameRam *self, int player_index);
struct RecoveryTarget { int word0; int references;
 static void release(RecoveryTarget *object) {
  if(object) {
   --object->references;
   if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
    igObject_Destroy((igObject *)object);
  }
 }
};
template<int I> class RecoveryRef { public:
 void *value;
 RecoveryRef(void *p, bool retain):value(p) { if(retain) beNDMWLoadIntf2_igObject_Retain((ObjectRefTarget *)value); }
 RecoveryRef(const RecoveryRef &other):value(other.value) { beNDMWLoadIntf2_igObject_Retain((ObjectRefTarget *)value); }
 ~RecoveryRef() { RecoveryTarget::release((RecoveryTarget *)value); }
};
extern "C" void beNDMWGameRam_GiveInitialWeapons(beNDMWGameRam *self, int index);
extern "C" void beNDMWGameRam_EquipWeapon(beNDMWGameRam *self, int index, int apply);
extern "C" unsigned char beNDMWGameRam_HasUsableWeapon(beNDMWGameRam *self, int index, int species);
extern "C" void beNDMWGameRam_JoinPlayer(beNDMWGameRam *self, int index, const char *modelName);
extern "C" void beNDMWGameRam_JoinPlayerWithName(beNDMWGameRam *self, int index, void *modelName, StringRef name);
extern "C" void beNDMWGameRam_JoinPlayerWithUnicodeName(beNDMWGameRam *self, int index, void *modelName, RecoveryRef<0> name);
extern "C" void beNDMWGameRam_LeavePlayer(beNDMWGameRam *self, int index);
/* The flat field is const: its read is created before the *out reload so the register colouring puts
 * the field in a0 and the running total in v1. */
struct BonusItem { char pad[20]; const int flat; };
extern "C" void beNDMWGameRam_AddMainSlotBonus(beNDMWGameRam *self, void *player, int *total, const char *name, int withFlat);
struct beNDMWItemCountView { beNDMWItemBase base; unsigned int _count; };
typedef igObject Ref;
struct StatHelpers {
    static inline void release_ref(Ref *object)
    {
        igObject::release(object);
    }
    static inline Ref *shinka(beNDMWGameRam *g)
    {
        if (!g->_dBShinka) {
            Ref *fetched;
            beMessenger_SendNamed((beMessenger *)g->_messenger, ((char *)DATABASE_3), ((char *)shinka_2), 0, ((char *)GETDATABASE_3));
            fetched = ((Ref *)beMessenger_GetObject((beMessenger *)g->_messenger, 0));
            if (fetched) ++fetched->_refCount;
            release_ref((Ref *)g->_dBShinka);
            g->_dBShinka = (int)fetched;
        }
        return (Ref *)g->_dBShinka;
    }
};
struct AttributeHelpers {
    static inline void release_ref(igObject *object)
    {
        igObject::release(object);
    }
    static inline igObject *shinka(beNDMWGameRam *g)
    {
        if (!g->_dBShinka) {
            igObject *fetched;
            beMessenger_SendNamed((beMessenger *)g->_messenger, ((char *)DATABASE_3), ((char *)shinka_2), 0, ((char *)GETDATABASE_3));
            fetched = beMessenger_GetObject((beMessenger *)g->_messenger, 0);
            if (fetched) ++fetched->_refCount;
            release_ref((igObject *)g->_dBShinka);
            g->_dBShinka = (int)fetched;
        }
        return (igObject *)g->_dBShinka;
    }
};
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
extern "C" char GETMATRIX[];
extern "C" char GETHP[];
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
                igObject_Destroy((igObject *)object);
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
/* The helpers are static members so a split of the unit at its top-level definitions keeps them. */
struct RecomputeHelpers {
    static inline void release_ref(igObject *object)
    {
        igObject::release(object);
    }

    static inline igObject *shinka(beNDMWGameRam *g)
    {
        if (!g->_dBShinka) {
            igObject *fetched;
            beMessenger_SendNamed((beMessenger *)g->_messenger, ((char *)DATABASE_3), ((char *)shinka_2), 0, ((char *)GETDATABASE_3));
            fetched = beMessenger_GetObject((beMessenger *)g->_messenger, 0);
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
            beMessenger_SendNamed((beMessenger *)g->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
            fetched = beMessenger_GetObject((beMessenger *)g->_messenger, 0);
            if (fetched) ++fetched->_refCount;
            release_ref((igObject *)g->_dBPcTech);
            g->_dBPcTech = (int)fetched;
        }
        return (igObject *)g->_dBPcTech;
    }

    static inline int select_allocator(int fallback)
    {
        if (g_useOwnerAllocator) return fallback;
        else return (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
    }

    static inline void *GetPlayer(beNDMWGameRam *g, int idx)
    {
        return ((igObject **)((igObjectList *)g->_playerDataListList)->_data)[idx];
    }

    static inline int GetProp(void *player, const char *name)
    {
        return (igProperty_GetRecord((igObject *)player, name))->_data;
    }
};
extern "C" void beNDMWGameRam_RecomputeStats(beNDMWGameRam *self, int index, unsigned char apply);
extern "C" void beNDMWGameRam_FindTechniqueRow(beNDMWGameRam *receiver, void *player, int base_no, int *output);
extern "C" int beNDMWGameRam_igStringRefList_GetData(igDataList *p);
extern "C" int beNDMWGameRam_beModelCtrlMoveObjectList_Get(igDataList *list, int index);
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
extern "C" ObjectRefTarget **beNDMWGameRam_igSmartPointer_beDataBase_Assign(ObjectRefTarget **destination,ObjectRefTarget *incoming);
extern "C" int beNDMWGameRam_igBoolList_GetData(igUnsignedCharList *p);
extern "C" int beNDMWGameRam_beDataObjInt_GetData(beDataObjInt *p);

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
            igSmartPointer<beDataObjInt> s0((beDataObjInt *)beDataObjInt_Create((int)alloc));
            igNamedObject_SetName((igNamedObject *)s0.p, (const char *)entry->name);
            ((Gap::Core::igObjectList *)out)->append((Gap::Core::igObject *)s0.p);
            break;
        }
        case DATA_INT_LIST: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjIntList> s1((beDataObjIntList *)beDataObjIntList_Create((int)alloc));
            igNamedObject_SetName((igNamedObject *)s1.p, (const char *)entry->name);
            RESERVE(igIntList, s1.p, 4)
            RESIZE(igIntList, s1.p, 4)
            {
                igIntList *l1 = (igIntList *)s1.p->_data;
                n1 = l1->_count;
                int *d1 = (int *)l1->_data;
                for (i1 = 0; i1 < n1; i1++) ListStoreAt(d1, i1, 0);
            }
            ((Gap::Core::igObjectList *)out)->append((Gap::Core::igObject *)s1.p);
            break;
        }
        case DATA_BOOL: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjBool> s2((beDataObjBool *)beDataObjBool_Create((int)alloc));
            igNamedObject_SetName((igNamedObject *)s2.p, (const char *)entry->name);
            ((Gap::Core::igObjectList *)out)->append((Gap::Core::igObject *)s2.p);
            break;
        }
        case DATA_BOOL_LIST: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjBoolList> s3((beDataObjBoolList *)beDataObjBoolList_Create((int)alloc));
            igNamedObject_SetName((igNamedObject *)s3.p, (const char *)entry->name);
            RESERVE(igBoolList, s3.p, 1)
            RESIZE(igBoolList, s3.p, 1)
            {
                igBoolList *l3 = (igBoolList *)s3.p->_data;
                int n3 = l3->_count;
                unsigned char *d3 = (unsigned char *)l3->_data;
                for (int i3 = 0; i3 < n3; i3++) ListStoreAt(d3, i3, (unsigned char)0);
            }
            ((Gap::Core::igObjectList *)out)->append((Gap::Core::igObject *)s3.p);
            break;
        }
        case DATA_STRING: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjString> s4((beDataObjString *)beDataObjString_Create((int)alloc));
            igNamedObject_SetName((igNamedObject *)s4.p, (const char *)entry->name);
            ((Gap::Core::igObjectList *)out)->append((Gap::Core::igObject *)s4.p);
            break;
        }
        case DATA_STRING_LIST: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjStringList> s5((beDataObjStringList *)beDataObjStringList_Create((int)alloc));
            igNamedObject_SetName((igNamedObject *)s5.p, (const char *)entry->name);
            RESERVE(igStringRefList, s5.p, 4)
            StringList_Resize((igTDataList<char *> *)(void *)s5.p->_data, entry->count);
            Fill::emptyStrings(s5.p, StringRef(0), n5, d5, i5);
            ((Gap::Core::igObjectList *)out)->append((Gap::Core::igObject *)s5.p);
            break;
        }
        case DATA_OBJECT_LIST: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjObjectList> s6((beDataObjObjectList *)beDataObjObjectList_Create((int)alloc));
            igNamedObject_SetName((igNamedObject *)s6.p, (const char *)entry->name);
            RESERVE(igObjectList, s6.p, 4)
            ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)(void *)s6.p->_data))->setCount(entry->count);
            ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)(void *)s6.p->_data))->setAll(0);
            ((Gap::Core::igObjectList *)out)->append((Gap::Core::igObject *)s6.p);
            break;
        }
        case DATA_FLOAT_LIST: {
            ALLOC(self, alloc)
            igSmartPointer<beDataObjFloatList> s7((beDataObjFloatList *)beDataObjFloatList_Create((int)alloc));
            igNamedObject_SetName((igNamedObject *)s7.p, (const char *)entry->name);
            RESERVE(igFloatList, s7.p, 4)
            RESIZE(igFloatList, s7.p, 4)
            {
                igFloatList *l7 = (igFloatList *)s7.p->_data;
                int n7 = l7->_count;
                float *d7 = (float *)l7->_data;
                for (int i7 = 0; i7 < n7; i7++) ListStoreAt(d7, i7, 0.0f);
            }
            ((Gap::Core::igObjectList *)out)->append((Gap::Core::igObject *)s7.p);
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
        if (!(n < countOf(out))) ((Gap::Core::igDataList *)out)->setCapacity(n, 4);
    }
}

static inline int count(const igObjectList *list) { return list->_count; }

static inline void storePlayerData(beNDMWGameRam *self, int index, const igSmartPointer<igObject> &value) {
    igObject *s2 = value.p;
    igObjectList *pl = (igObjectList *)self->_playerDataListList;
    igObject *o;
    if (s2 != 0) s2->_refCount = s2->_refCount + 1;
    o = ((igObject **)pl->_data)[index];
    igObject::release(o);
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
            igObject::release(o);
        }
        clearCount = common->_count;
        for (j = 0; j < clearCount; j++) ((int *)common->_data)[j] = 0;
        common->_count = 0;
        beNDMWGameRam_BuildDataList(self, (igObjectList *)self->_commonDataList, g_commonDataLayout);
    }
    players = (igObjectList *)self->_playerDataListList;
    if (players->_count != 4) {
        if (count(players) < 5) ((Gap::Core::igDataList *)players)->setCapacity(4, 4);
        ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)self->_playerDataListList))->setCount(4);
    }
    allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
    if (g_useOwnerAllocator != 0) {
        allocator = (int)allocator;
    } else {
        allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
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
        diskAllocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        if (g_useOwnerAllocator != 0) {
            diskAllocator = (int)diskAllocator;
        } else {
            diskAllocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
        }
        ItemRef item(beNDMWItemDisk_Create(diskAllocator));
        beNDMWItemDisk_Set((beNDMWItemDisk *)item.p, disk);
        playerData = data.p;
        diskItem = item.p;
        igObject **folder = (igObject **)igProperty_GetRecordFolder(playerData, "DISKFOLDER");
        ((Gap::Core::igObjectList *)folder[3])->append((Gap::Core::igObject *)diskItem);
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

    beBaseInfoManager_Start((beBaseInfoManager *)self);
    allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
    if (g_useOwnerAllocator != 0) {
        allocator = (int)allocator;
    } else {
        allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
    }
    {
        /* The new list is owned by the stack reference while it is retained into the field and the old
         * list is released; the reference's own release runs at the block end. */
        igSmartPointer<igObject> common(beDataObjList_Create(allocator));
        (igSmartPointer<igObject> &)self->_commonDataList = common;
    }
    playersAllocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
    if (g_useOwnerAllocator != 0) {
        playersAllocator = (int)playersAllocator;
    } else {
        playersAllocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
    }
    {
        PlayerDataListListRef players(beDataObjListList_Create(playersAllocator));
        (igSmartPointer<igObject> &)self->_playerDataListList = players.p;
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
                if (!(data->refs & 0x7fffff)) igObject_Destroy((igObject *)data);
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
    if (!(0 < ((ObjectRefList *)self->_commonDataList)->count)) ((Gap::Core::igDataList *)self->_commonDataList)->setCapacity(0, 4);
    players = (ObjectRefList *)self->_playerDataListList;
    playerCount = players->count;
    j = 0;
    if (0 < playerCount) {
        playerOffset = 0;
        do {
            playerData = *(RefCountedHeader **)((char *)players->data + playerOffset);
            if (playerData != 0) {
                playerData->refs--;
                if (!(playerData->refs & 0x7fffff)) igObject_Destroy((igObject *)playerData);
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
    if (!(0 < ((ObjectRefList *)self->_playerDataListList)->count)) ((Gap::Core::igDataList *)self->_playerDataListList)->setCapacity(0, 4);
}

void beNDMWGameRam_Prepare(beNDMWGameRam *self) {
    ((igSmartPointer<igObject> &)self->_dBShinka).clear();
    ((igSmartPointer<igObject> &)self->_dBPcTech).clear();
    ((igSmartPointer<igObject> &)self->_dBWeapon).clear();
    ((igSmartPointer<igObject> &)self->_dBArmor1).clear();
    ((igSmartPointer<igObject> &)self->_dBArmor2).clear();
    ((igSmartPointer<igObject> &)self->_dBAbChip).clear();
    ((igSmartPointer<igObject> &)self->_dBEnemy).clear();
    ((igSmartPointer<igObject> &)self->_dBEneatk).clear();
}

int beNDMWGameRam_AddInfo(beNDMWGameRam *self) {
    beBaseInfoList *infos;
    beBaseInfoRamList *rams;
    int allocator;
    beNDMWGameRamInfoRam *created;
    infos = (beBaseInfoList *)self->_infoList;
    if (infos->_count == 0) {
        allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igSmartPointer<beNDMWGameRamInfo> info(beNDMWGameRamInfo_Create(allocator));
        allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        RamRef ram(beNDMWGameRamInfoRam_Create(allocator));
        igNamedObject_SetName((igNamedObject *)info.p, "gameram");
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
        ((Gap::Core::igObjectList *)((unsigned)rams))->append((Gap::Core::igObject *)ram.p);
        ((Gap::Core::igObjectList *)((unsigned)self->_infoList))->append((Gap::Core::igObject *)info.p);
        beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)ram.p, "GAMERAM");
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
        pooled = StringPool_Intern((StringPool *)(SharedStringPool::get()), modelName);
    }
    StringRef name(pooled);
    species = 0;
    for (;;) {
        interned = name.p;
        if (beDataBase_GetRecordString((beDataBase *)(StatHelpers::shinka(self)), species, "MODEL_NAME") == interned) {
            return species;
        }
        species += 1;
        if (species >= 16) {
            return 0;
        }
    }
}

void beNDMWGameRam_SelectSpecies(beNDMWGameRam *self, int index, int species) {
/* matching construct: local declaration order fixes register allocation; declared where first set, or in the
 * order first set (with for loops and a bounds-checked setter), the function differs in registers only */
    int upcntOffset;
    igIntList *skills;
    int player;
    igIntList *baseUpcnts;
    igIntList *upcnts;
    beDataObjIntList *commonCounter;
    int skillBase;
    int oldName;
    int upcntCount;
    beDataObjBoolList *commonFlagFolder;
    int level;
    int skillCount;
    igIntList *baseLevels;
    igObject *flagFolder;
    igIntList *baseExps;
    int value;
    beDataObjBoolList *commonFlags;
    beDataObjString *nameRecord;
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
    (igProperty_GetRecord((igObject *)player, "LEVEL"));
    (igProperty_GetRecord((igObject *)player, "DIGIMONNO"))->_data = species;
    modelName = ((int)beDataBase_GetRecordString((beDataBase *)(StatHelpers::shinka(self)), species, "MODEL_NAME"));
    nameRecord = (igProperty_GetRecordString((igObject *)player, "DIGIMONNAME"));
    interned = ((int)StringPool_Intern((StringPool *)(SharedStringPool::get()), (const char *)modelName));
    oldName = nameRecord->_data;
    if (oldName != 0) {
        int *p = (int *)(oldName - 8);
        int c = *(int *)(oldName - 4) - 1;
        *(int *)(oldName - 4) = c;
        if (c == 0) StringChunk_ReleaseHeader((StringChunk *)*p, (StringTokenHeader *)p);
    }
    nameRecord->_data = interned;
    baseLevels = (igIntList *)(igProperty_GetRecordIntList((igObject *)player, "BASE_LEVEL"))->_data;
    level = ((int *)baseLevels->_data)[species];
    (igProperty_GetRecord((igObject *)player, "LEVEL"))->_data = level;
    baseExps = (igIntList *)(igProperty_GetRecordIntList((igObject *)player, "BASE_EXP"))->_data;
    value = ((int *)baseExps->_data)[species];
    (igProperty_GetRecord((igObject *)player, "EXP"))->_data = value;
    /* matching construct: skillBase/upcntBase hoisted into locals; indexed as species * 9 + skill the function is 8 bytes short */
    skillBase = species * 9;
    skill = 0;
    skillOffset = 0;
    do {
        baseSkills = (igIntList *)(igProperty_GetRecordIntList((igObject *)player, "BASE_SKILL"))->_data;
        skillValue = ((int *)baseSkills->_data)[skillBase + skill];
        skills = (igIntList *)(igProperty_GetRecordIntList((igObject *)player, "SKILL"))->_data;
        skillCount = skills->_count;
        if (skillCount != 0 && skill >= 0 && skill < skillCount) ((int *)(skills->_data + skillOffset))[0] = skillValue;
        skill += 1;
        skillOffset += 4;
    } while (skill < 9);
    upcntBase = species * 11;
    upcnt = 0;
    upcntOffset = 0;
    do {
        baseUpcnts = (igIntList *)(igProperty_GetRecordIntList((igObject *)player, "BASE_UPCNT"))->_data;
        value = ((int *)baseUpcnts->_data)[upcntBase + upcnt];
        upcnts = (igIntList *)(igProperty_GetRecordIntList((igObject *)player, "UPCNT"))->_data;
        upcntCount = upcnts->_count;
        if (upcntCount != 0 && upcnt >= 0 && upcnt < upcntCount) ((int *)(upcnts->_data + upcntOffset))[0] = value;
        upcnt += 1;
        upcntOffset += 4;
    } while (upcnt < 11);
    if (index == 0) {
        flags = (igObject *)(igProperty_GetRecordArray((igObject *)player, "BASE_FLAG"))->_data;
        commonFlags = (igProperty_GetRecordArray((igObject *)self->_commonDataList, "FLAG"));
        (igSmartPointer<igObject> &)commonFlags->_data = flags;
        flagFolder = (igObject *)(igProperty_GetRecordArray((igObject *)player, "BASE_FLAGFOLDER"))->_data;
        commonFlagFolder = (igProperty_GetRecordArray((igObject *)self->_commonDataList, "FLAGFOLDER"));
        (igSmartPointer<igObject> &)commonFlagFolder->_data = flagFolder;
        counter = (igObject *)(igProperty_GetRecordIntList((igObject *)player, "BASE_COUNTER"))->_data;
        commonCounter = (igProperty_GetRecordIntList((igObject *)self->_commonDataList, "COUNTER"));
        (igSmartPointer<igObject> &)commonCounter->_data = counter;
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
    species = (igProperty_GetRecord((igObject *)player, "DIGIMONNO"))->_data;
    value = (igProperty_GetRecord((igObject *)player, "LEVEL"))->_data;
    level_list = ((IntListProperty *)igProperty_GetRecordIntList((igObject *)player, "BASE_LEVEL"))->list;
    if (level_list->_count != 0 && species >= 0 && species < level_list->_count)
        ((int *)level_list->_data)[species] = value;
    value = (igProperty_GetRecord((igObject *)player, "EXP"))->_data;
    exp_list = ((IntListProperty *)igProperty_GetRecordIntList((igObject *)player, "BASE_EXP"))->list;
    if (exp_list->_count != 0 && species >= 0 && species < exp_list->_count)
        ((int *)exp_list->_data)[species] = value;
    skill_base = species * 9;
    for (skill_index = 0; skill_index < 9; ++skill_index) {
        skill = ((int *)((IntListProperty *)igProperty_GetRecordIntList((igObject *)player, "SKILL"))->list->_data)[skill_index];
        base_array = ((IntListProperty *)igProperty_GetRecordIntList((igObject *)player, "BASE_SKILL"));
        if (base_array->list->_count != 0 && skill_base + skill_index >= 0 &&
            skill_base + skill_index < base_array->list->_count)
            ((int *)base_array->list->_data)[skill_base + skill_index] = skill;
    }
    upcnt_base = species * 11;
    for (upcnt_index = 0; upcnt_index < 11; ++upcnt_index) {
        upcnt = ((int *)((IntListProperty *)igProperty_GetRecordIntList((igObject *)player, "UPCNT"))->list->_data)[upcnt_index];
        base_array = ((IntListProperty *)igProperty_GetRecordIntList((igObject *)player, "BASE_UPCNT"));
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
    devices = ((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "DEVICEFOLDER"))->list;
    species = ((igProperty_GetRecord((igObject *)player, "DIGIMONNO")))->_data;
    count = devices->_count;
    i = 0;
    if (0 < count) {
        do {
            released = ((RefCountedHeader **)devices->_data)[i];
            if (released != 0) {
                released->refs--;
                if (!(released->refs & 0x7fffff)) igObject_Destroy((igObject *)released);
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
        allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        allocator = (g_useOwnerAllocator != 0) ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
        {
        RecoveryRef<1> weaponRef(beNDMWItemWeapon_Create(allocator), false);
        weapon = weaponRef.value;
        if (self->_dBShinka == 0) {
            beMessenger_SendNamed((beMessenger *)self->_messenger, DATABASE_3, shinka_2, 0, GETDATABASE_3);
            fetched = (RefCountedHeader *)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
            if (fetched != 0) {
                fetched->refs++;
            }
            released = (RefCountedHeader *)self->_dBShinka;
            if (released != 0) {
                released->refs--;
                if (!(released->refs & 0x7fffff)) igObject_Destroy((igObject *)released);
            }
            self->_dBShinka = (int)fetched;
        }
        beNDMWItemWeapon_Set((beNDMWItemWeapon *)weapon, beDataBase_GetRecordInt((beDataBase *)(void *)self->_dBShinka, species, *field), 0, 0);
        ((Gap::Core::igObjectList *)devices)->append((Gap::Core::igObject *)weaponRef.value);
        }
        slot += 1;
        field += 1;
    } while (slot < 3);
}

void beNDMWGameRam_EquipWeapon(beNDMWGameRam *self, int index, int apply)
{
    void *player = ((void **)((igObjectList *)self->_playerDataListList)->_data)[index];
    igObjectList *pocket = ((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "DEVICEFOLDER"))->list;

    if ((apply & 0xff) == 0) {
        igObjectList *sockets = ((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "POWERSOCKET"))->list;
        igStringRefList *names = ((StringListProperty *)igProperty_GetRecordStringList((igObject *)player, "POWERSOCKETNAME"))->list;
        int oldCount = sockets->_count;
        for (int r = 0; r < oldCount; r++) {
            beNDMWItemBase *prev = ((beNDMWItemBase **)sockets->_data)[r];
            igObject::release(prev);
        }
        int clearCount = sockets->_count;
        for (int c = 0; c < clearCount; c++) ((beNDMWItemBase **)sockets->_data)[c] = 0;
        sockets->_count = 0;
        int nameCount = names->_count;
        for (int i = 0; i < nameCount; i++) {
            char **entry = &((char **)names->_data)[i];
            char *old, *fresh;
            fresh = StringPool_Intern((StringPool *)(SharedStringPool::get()), 0);
            old = *entry;
            if (old) {
                int *header = (int *)(old - 8);
                if (--header[1] == 0) StringChunk_ReleaseHeader((StringChunk *)header[0], (StringTokenHeader *)header);
            }
            *entry = fresh;
        }
        names->_count = 0;
        int pocketCount = pocket->_count;
        for (int p = 0; p < pocketCount; p++) {
            if (sockets->_count == 3) break;
            beNDMWItemBase *item = ((beNDMWItemBase **)pocket->_data)[p];
            if (item->_kindNo == 0) {
                ((Gap::Core::igObjectList *)sockets)->append((Gap::Core::igObject *)item);
                const char *model = beNDMWItemBase_GetRecordString(item, (beNDMWStatus *)self, "MODEL");
                char *interned;
                if (!model) {
                    interned = 0;
                } else {
                    interned = StringPool_Intern((StringPool *)(SharedStringPool::get()), model);
                }
                StringList_AppendRetained((igStringRefList *)names, StringRef(interned).ref());
                item->_isEquip = 1;
            }
        }
    } else {
        int species = (igProperty_GetRecord((igObject *)player, "DIGIMONNO"))->_data;
        int bit;
        igIntList *skills;
        igStringRefList *names;
        int fits, skillNo;
        igObjectList *sockets;
        skills = ((IntListProperty *)igProperty_GetRecordIntList((igObject *)player, "SKILL"))->list;
        sockets = ((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "POWERSOCKET"))->list;
        names = ((StringListProperty *)igProperty_GetRecordStringList((igObject *)player, "POWERSOCKETNAME"))->list;
        int pocketCount = pocket->_count;
        for (int u = 0; u < pocketCount; u++) {
            beNDMWItemBase *item = ((beNDMWItemBase **)pocket->_data)[u];
            if (item->_kindNo == 0) item->_isEquip = 0;
        }
        ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)sockets))->setAll(0);
        int nameCount = names->_count;
        for (int i = 0; i < nameCount; i++) {
            char **entry = &((char **)names->_data)[i];
            char *old, *fresh;
            fresh = StringPool_Intern((StringPool *)(SharedStringPool::get()), 0);
            old = *entry;
            if (old) {
                int *header = (int *)(old - 8);
                if (--header[1] == 0) StringChunk_ReleaseHeader((StringChunk *)header[0], (StringTokenHeader *)header);
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
                fits = bit & beNDMWItemBase_GetRecordInt(item, (beNDMWStatus *)self, "SOUBI");
                skillNo = beNDMWItemBase_GetRecordInt(item, (beNDMWStatus *)self, "SKILL");
                int need = beNDMWItemBase_GetRecordInt(item, (beNDMWStatus *)self, "SKILLPOINT");
                if (fits != 0 && ((int *)skills->_data)[skillNo] >= need &&
                    (best < 0 || bestValue < beNDMWItemBase_GetRecordInt(item, (beNDMWStatus *)self, "TSUYOSA"))) {
                    bestValue = beNDMWItemBase_GetRecordInt(item, (beNDMWStatus *)self, "TSUYOSA");
                    best = k;
                }
            }
        }
        if (best >= 0) {
            beNDMWItemBase *chosen = ((beNDMWItemBase **)pocket->_data)[best];
            if (chosen) ++chosen->_refCount;
            beNDMWItemBase *first = ((beNDMWItemBase **)sockets->_data)[0];
            igObject::release(first);
            int sc = sockets->_count;
            int zero = 0;
            if (sc != 0 && zero < sc) ((beNDMWItemBase **)sockets->_data)[0] = chosen;
            const char *model = beNDMWItemBase_GetRecordString(chosen, (beNDMWStatus *)self, "MODEL");
            char *interned;
            if (!model) {
                interned = 0;
            } else {
                interned = StringPool_Intern((StringPool *)(SharedStringPool::get()), model);
            }
            StringList_AppendRetained((igStringRefList *)names, StringRef(interned).ref());
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
    devices = ((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "DEVICEFOLDER"))->list;
    {
    int current = (igProperty_GetRecord((igObject *)player, "DIGIMONNO"))->_data;
    if (current == species) {
        skills = ((IntListProperty *)igProperty_GetRecordIntList((igObject *)player, "SKILL"))->list;
        base = 0;
    } else {
        skills = ((IntListProperty *)igProperty_GetRecordIntList((igObject *)player, "BASE_SKILL"))->list;
        base = species * 9;
    }
    }
    mask = 1 << species;
    count = devices->_count;
    for (i = 0; i < count; i++) {
        beNDMWItemBase *item = ((beNDMWItemBase **)devices->_data)[i];
        if (item->_kindNo == 0) {
            int fits = mask & beNDMWItemBase_GetRecordInt(item, (beNDMWStatus *)self, "SOUBI");
            int skillNo = beNDMWItemBase_GetRecordInt(item, (beNDMWStatus *)self, "SKILL");
            int need = beNDMWItemBase_GetRecordInt(item, (beNDMWStatus *)self, "SKILLPOINT");
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
    beDataObjBool *isUse;

    common = self->_commonDataList;
    player = ((int *)((igObjectListList *)self->_playerDataListList)->_data)[index];
    species = beNDMWGameRam_FindSpecies(self, modelName);
    beNDMWGameRam_SelectSpecies(self, index, species);
    beNDMWGameRam_GiveInitialWeapons(self, index);
    beNDMWGameRam_EquipWeapon(self, index, 0);
    beNDMWGameRam_RecomputeStats(self, index, (unsigned char)1);
    isUse = (igProperty_GetRecordByte((igObject *)player, "ISUSE"));
    isUse->_data = 1;
    used = ((DataListProperty *)igProperty_GetRecordArray((igObject *)player, "BASE_ISUSE"))->list;
    if (used->_count != 0 && species >= 0 && species < used->_count) {
        *(char *)(species + used->_data) = g_speciesUsedMark;
    }
    joined = 0;
    i = 0;
    offset = 0;
    do {
        if ((igProperty_GetRecordByte((igObject *)*(int *)(((igObjectListList *)self->_playerDataListList)->_data + offset), "ISUSE"))->_data != 0) {
            joined += 1;
        }
        i += 1;
        offset += 4;
    } while (i < 4);
    (igProperty_GetRecord((igObject *)common, "NINZU"))->_data = joined;
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
    allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
    allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
    igSmartPointer<beUnicodeObj> unicodeName(beUnicodeObj_Create(allocator));
    beUnicodeObj_AllocateBuffer(unicodeName.p, 8);
    {
        const char *text = (const char *)name.p;
        beFont *font = (beFont *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beFont_metaObject);
        igSmartPointer<beUnicodeObj> converted(beFont_ConvertToUnicode(font, text));
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
    }
    names = ((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "PLAYERNAME"))->list;
    if (countOf(names) != 0) {
        n = names->_count;
        for (i = 0; i < n; i++) {
            released = ((igObject **)names->_data)[i];
            igObject::release(released);
        }
        n2 = names->_count;
        for (j = 0; j < n2; j++) ((igObject **)names->_data)[j] = 0;
        names->_count = 0;
    }
    ((Gap::Core::igObjectList *)names)->append((Gap::Core::igObject *)unicodeName.p);
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
    nameFolder = (ObjectListProperty *)igProperty_GetRecordFolder((igObject *)((int *)(((igObjectList *)self->_playerDataListList)->_data))[index], "PLAYERNAME");
    names = nameFolder->list;
    if (countOf(names) != 0) {
        n = names->_count;
        for (i = 0; i < n; i++) {
            released = ((igObject **)names->_data)[i];
            igObject::release(released);
        }
        n2 = names->_count;
        for (j = 0; j < n2; j++) {
            ((igObject **)names->_data)[j] = 0;
        }
        names->_count = 0;
    }
    ((Gap::Core::igObjectList *)names)->append((Gap::Core::igObject *)name.value);
}

void beNDMWGameRam_LeavePlayer(beNDMWGameRam *self, int index) {
    int joined;
    int i;
    int common;
    int offset;

    common = self->_commonDataList;
    (igProperty_GetRecordByte((igObject *)((int *)((igObjectList *)self->_playerDataListList)->_data)[index], "ISUSE"))->_data = 0;
    joined = 0;
    i = 0;
    offset = 0;
    do {
        if ((igProperty_GetRecordByte((igObject *)((int *)(((igObjectList *)self->_playerDataListList)->_data + offset))[0], "ISUSE"))->_data != 0) {
            joined += 1;
        }
        i += 1;
        offset += 4;
    } while (i < 4);
    (igProperty_GetRecord((igObject *)common, "NINZU"))->_data = joined;
}

/* HP update. Returns 0 when a delta is applied to a dead player (HP 0), else 1. */
int beNDMWGameRam_ChangeHp(beNDMWGameRam *self, int player_index, int delta, int absolute)
{
    int hp;
    int player;
    int max_hp;

    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[player_index];
    max_hp = (igProperty_GetRecord((igObject *)player, "MHP"))->_data;
    hp = (igProperty_GetRecord((igObject *)player, "HP"))->_data;
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
    (igProperty_GetRecord((igObject *)player, "HP"))->_data = hp;
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "METERCTRL", "hpmt", player_index);
    beMessenger_AppendFloat((beMessenger *)self->_messenger, 100.0f * (float)hp / (float)max_hp);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETPERCENT");
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "NUMBERCTRL", "hpnm", player_index);
    beMessenger_AppendInt((beMessenger *)self->_messenger, hp);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETVALUE");
    return 1;
}

/* MP update by delta. */
void beNDMWGameRam_ChangeMp(beNDMWGameRam *self, int player_index, int delta)
{
    int mp;
    int player;
    int max_mp;

    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[player_index];
    max_mp = (igProperty_GetRecord((igObject *)player, "MMP"))->_data;
    mp = (igProperty_GetRecord((igObject *)player, "MP"))->_data;
    mp += delta;
    if (mp < 0)
        mp = 0;
    if (mp > max_mp)
        mp = max_mp;
    (igProperty_GetRecord((igObject *)player, "MP"))->_data = mp;
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "METERCTRL", "mpmt", player_index);
    beMessenger_AppendFloat((beMessenger *)self->_messenger, 100.0f * (float)mp / (float)max_mp);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETPERCENT");
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "NUMBERCTRL", "mpnm", player_index);
    beMessenger_AppendInt((beMessenger *)self->_messenger, mp);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETVALUE");
}

void beNDMWGameRam_AddPowerSocketBonus(int self, int player, int *total, const char *name, int withRevision) {
    beNDMWItemRevisionBase *item;
    if (((igObjectList *)((beDataObjObjectList *)igProperty_GetRecordFolder((igObject *)player, "POWERSOCKET"))->_data)->_count != 0) {
        item = ((beNDMWItemRevisionBase **)((igObjectList *)((beDataObjObjectList *)igProperty_GetRecordFolder((igObject *)player, "POWERSOCKET"))->_data)->_data)[0];
        if (item != 0) {
            *total += beNDMWItemBase_GetRecordInt((beNDMWItemBase *)item, (beNDMWStatus *)self, name);
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
    count = ((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "POWERPOCKET"))->list->_count;
    i = 0;
    if (0 < count) {
        do {
            item = ((int *)((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "POWERPOCKET"))->list->_data)[i];
            if (item != 0) {
                *total += beNDMWItemBase_GetRecordInt((beNDMWItemBase *)item, (beNDMWStatus *)self, name);
            }
            i += 1;
        } while (i < count);
    }
}

void beNDMWGameRam_AddMainSlotBonus(beNDMWGameRam *self, void *player, int *total, const char *name, int withFlat) {
    beNDMWItemBase *item;
    if (((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, (const char *)"MAINSLOT"))->list->_count != 0) {
        item = ((beNDMWItemBase **)((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, (const char *)"MAINSLOT"))->list->_data)[0];
        if (item != 0) {
            *total += beNDMWItemBase_GetRecordInt(item, (beNDMWStatus *)self, name);
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
    count = ((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "MAINPOCKET"))->list->_count;
    for (i = 0; i < count; i++) {
        item = ((int *)((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "MAINPOCKET"))->list->_data)[i];
        if (item != 0) {
            *total += beNDMWItemBase_GetRecordInt((beNDMWItemBase *)item, (beNDMWStatus *)self, name);
        }
    }
}

void beNDMWGameRam_AddSubSlotBonus(int self, int player, int *total, const char *name, int withAbility) {
    beNDMWItemBase *item; int bonus;
    if (((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "SUBSLOT"))->list->_count != 0) {
        item = *(beNDMWItemBase **)((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "SUBSLOT"))->list->_data;
        if (item != 0) {
            bonus = beNDMWItemBase_GetRecordInt(item, (beNDMWStatus *)self, name); *total += bonus;
            if (withAbility != 0 && strcmp(((char *)beNDMWItemBase_GetRecordString(item, (beNDMWStatus *)self, "SHUSEINOURYOKU")), name) == 0) {
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
        record = (igProperty_GetRecord((igObject *)player, ("DIGIMONNO")))->_data;
        upcnts = ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPCNT"))->list;
        base = 0;
        level = (igProperty_GetRecord((igObject *)player, "LEVEL"))->_data;
    } else {
        upcnts = ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "BASE_UPCNT"))->list;
        base = record * 11;
        level = ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, ("BASE_LEVEL")))->list->values[record];
    }
    if (isHp != 0) {
        initial = beDataBase_GetRecordInt((beDataBase *)(StatHelpers::shinka(self)), record, "MHP_INI");
        growth = beDataBase_GetRecordInt((beDataBase *)(StatHelpers::shinka(self)), record, "MHP_GROW");
        bonus = upcnts->values[base];
    } else {
        initial = beDataBase_GetRecordInt((beDataBase *)(StatHelpers::shinka(self)), record, "MMP_INI");
        growth = beDataBase_GetRecordInt((beDataBase *)(StatHelpers::shinka(self)), record, "MMP_GROW");
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
        record = (igProperty_GetRecord((igObject *)player, ("DIGIMONNO")))->_data;
        upcnts = ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPCNT"))->list;
        base = 0;
        level = (igProperty_GetRecord((igObject *)player, "LEVEL"))->_data;
    } else {
        upcnts = ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "BASE_UPCNT"))->list;
        base = record * 11;
        level = ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, ("BASE_LEVEL")))->list->values[record];
    }
    initial = beDataBase_GetRecordInt((beDataBase *)(AttributeHelpers::shinka(self)), record, g_attributeInitialFields[attribute]);
    growth = beDataBase_GetRecordInt((beDataBase *)(AttributeHelpers::shinka(self)), record, g_attributeGrowthFields[attribute]);
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
    mhp += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPDATA"))->list->values[6];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &mhp, "MAXHP", 0);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &mhp, "MAXHP", 0);
    }
    if (mhp > 99999) mhp = 99999;
    (igProperty_GetRecord((igObject *)player, "MHP"))->_data = mhp;
    int curHp = (igProperty_GetRecord((igObject *)player, "HP"))->_data;
    if (curHp == 0) first = 1;
    if (curHp == 0 || mhp < curHp) (igProperty_GetRecord((igObject *)player, "HP"))->_data = mhp;

    int mmp = beNDMWGameRam_CalcMaxPoints(self, index, -1, 0);
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &mmp, "MAXMP", 0);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &mmp, "MAXMP", 0);
    }
    if (mmp > 99999) mmp = 99999;
    (igProperty_GetRecord((igObject *)player, "MMP"))->_data = mmp;
    int curMp = (igProperty_GetRecord((igObject *)player, "MP"))->_data;
    if (first || mmp < curMp) (igProperty_GetRecord((igObject *)player, "MP"))->_data = mmp;

    int tsuyosa = beNDMWGameRam_CalcAttribute(self, index, -1, 0);
    tsuyosa += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPDATA"))->list->values[4];
    tsuyosa -= ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "DOWNDATA"))->list->values[4];
    if (apply) {
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &tsuyosa, "TSUYOSA", 1);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &tsuyosa, "TSUYOSA");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &tsuyosa, "TSUYOSA", 1);
    }
    CLAMP_ATTR(tsuyosa)
    (igProperty_GetRecord((igObject *)player, "TSUYOSA"))->_data = tsuyosa;

    int mamori = beNDMWGameRam_CalcAttribute(self, index, -1, 1);
    mamori += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPDATA"))->list->values[5];
    mamori -= ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "DOWNDATA"))->list->values[5];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &mamori, "MAMORI", 1);
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &mamori, "MAMORI", 1);
    }
    CLAMP_ATTR(mamori)
    (igProperty_GetRecord((igObject *)player, "MAMORI"))->_data = mamori;

    int kashikosa = beNDMWGameRam_CalcAttribute(self, index, -1, 2);
    if (apply) {
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &kashikosa, "KASHIKOSA", 0);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &kashikosa, "KASHIKOSA");
        beNDMWGameRam_AddMainSlotBonus(self, player, &kashikosa, "KASHIKOSA", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &kashikosa, "KASHIKOSA");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &kashikosa, "KASHIKOSA", 1);
    }
    CLAMP_ATTR(kashikosa)
    (igProperty_GetRecord((igObject *)player, "KASHIKOSA"))->_data = kashikosa;

    int seishin = beNDMWGameRam_CalcAttribute(self, index, -1, 3);
    if (apply) {
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &seishin, "SEISHIN", 0);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &seishin, "SEISHIN");
        beNDMWGameRam_AddMainSlotBonus(self, player, &seishin, "SEISHIN", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &seishin, "SEISHIN");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &seishin, "SEISHIN", 0);
    }
    CLAMP_ATTR(seishin)
    (igProperty_GetRecord((igObject *)player, "SEISHIN"))->_data = seishin;

    int subayasa = beNDMWGameRam_CalcAttribute(self, index, -1, 4);
    subayasa += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPDATA"))->list->values[0];
    subayasa -= ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "DOWNDATA"))->list->values[0];
    if (apply) {
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &subayasa, "SUBAYASA", 0);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &subayasa, "SUBAYASA");
        beNDMWGameRam_AddMainSlotBonus(self, player, &subayasa, "SUBAYASA", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &subayasa, "SUBAYASA");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &subayasa, "SUBAYASA", 1);
    }
    CLAMP_ATTR(subayasa)
    (igProperty_GetRecord((igObject *)player, "SUBAYASA"))->_data = subayasa;

    int fire = beDataBase_GetRecordInt((beDataBase *)(RecomputeHelpers::shinka(self)), species, "RES_FIRE");
    fire += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPCNT"))->list->values[7];
    fire += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPDATA"))->list->values[7];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &fire, "RES_FIRE", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &fire, "RES_FIRE");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &fire, "RES_FIRE", 1);
    }
    CLAMP_ATTR(fire)
    (igProperty_GetRecord((igObject *)player, "HONOOTEIKO"))->_data = fire;
    int ice = beDataBase_GetRecordInt((beDataBase *)(RecomputeHelpers::shinka(self)), species, "RES_ICE");
    ice += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPCNT"))->list->values[8];
    ice += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPDATA"))->list->values[8];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &ice, "RES_ICE", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &ice, "RES_ICE");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &ice, "RES_ICE", 1);
    }
    CLAMP_ATTR(ice)
    (igProperty_GetRecord((igObject *)player, "KOORITEIKO"))->_data = ice;
    int thunder = beDataBase_GetRecordInt((beDataBase *)(RecomputeHelpers::shinka(self)), species, "RES_THUNDER");
    thunder += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPCNT"))->list->values[9];
    thunder += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPDATA"))->list->values[9];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &thunder, "RES_THUNDER", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &thunder, "RES_THUNDER");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &thunder, "RES_THUNDER", 1);
    }
    CLAMP_ATTR(thunder)
    (igProperty_GetRecord((igObject *)player, "KAMINARITEIKO"))->_data = thunder;
    int dark = beDataBase_GetRecordInt((beDataBase *)(RecomputeHelpers::shinka(self)), species, "RES_DARK");
    dark += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPCNT"))->list->values[10];
    dark += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPDATA"))->list->values[10];
    if (apply) {
        beNDMWGameRam_AddMainSlotBonus(self, player, &dark, "RES_DARK", 0);
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &dark, "RES_DARK");
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &dark, "RES_DARK", 1);
    }
    CLAMP_ATTR(dark)
    (igProperty_GetRecord((igObject *)player, "YAMITEIKO"))->_data = dark;

    {
        igObjectList *list = ((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "WAZALIST"))->list;
        int oldCount = list->_count;
        for (int r = 0; r < oldCount; r++) RecomputeHelpers::release_ref(((igObject **)list->_data)[r]);
        int clearCount = list->_count;
        for (int c = 0; c < clearCount; c++) ((int *)list->_data)[c] = 0;
        list->_count = 0;

        for (int slot = 0; slot < 6; slot++) {
            int tech = beDataBase_GetRecordInt((beDataBase *)(RecomputeHelpers::shinka(self)), species, g_techniqueFields[slot]);
            int skillNo = beDataBase_GetRecordInt((beDataBase *)(RecomputeHelpers::pctech(self)), tech, "SKILL");
            int skillVal = ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "SKILL"))->list->values[skillNo];
            if (beDataBase_GetRecordInt((beDataBase *)(RecomputeHelpers::shinka(self)), species, g_techniqueLevelFields[slot]) <= level) {
                for (int rank = 4; rank >= 0; rank--) {
                    if (beDataBase_GetRecordInt((beDataBase *)(RecomputeHelpers::shinka(self)), species, g_techniqueSkillFields[slot][rank]) <= skillVal) {
                        IntListRef waza((IntList *)beNDMWItemWaza_Create(RecomputeHelpers::select_allocator((int)((Gap::Core::igObject *)self)->getMemoryPool())));
                        beNDMWItemWaza_Set((beNDMWItemWaza *)(igObject *)waza.value, tech + rank, tech);
                        ((Gap::Core::igObjectList *)list)->append((Gap::Core::igObject *)waza.value);
                        break;
                    }
                }
            }
        }
    }
    (igProperty_GetRecord((igObject *)player, "NEXTEXP"))->_data =
        level == 999 ? 0 : level * 200 + (level + 140) * (level * level);

    if (apply) {
        int delay, hitRate, critRate, paralysisRate, evadeRate, guardRate;
        int paralysisResist, poisonResist, bitRate, expRate;
        unsigned char found;
        int luckRate;
        delay = ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "DOWNDATA"))->list->values[6];
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &delay, "DELAY", 0);
        if (delay > 70) delay = 70;
        (igProperty_GetRecord((igObject *)player, "ATTACKDELAY"))->_data = delay;
        hitRate = 0;
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &hitRate, "MEICHURITSU", 0);
        (igProperty_GetRecord((igObject *)player, "MEICHURITSU"))->_data = hitRate;
        critRate = 0;
        critRate += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPDATA"))->list->values[1];
        critRate -= ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "DOWNDATA"))->list->values[1];
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &critRate, "CHIMEIRITSU", 0);
        beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &critRate, "CHIMEIRITSU");
        if (critRate <= 0) critRate = 1;
        (igProperty_GetRecord((igObject *)player, "CHIMEIRITSU"))->_data = critRate;
        paralysisRate = 0;
        beNDMWGameRam_AddPowerSocketBonus((int)self, (int)player, &paralysisRate, "MAHIRITSU", 0);
        (igProperty_GetRecord((igObject *)player, "MAHIRITSU"))->_data = paralysisRate;
        evadeRate = 0;
        evadeRate += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPDATA"))->list->values[3];
        evadeRate -= ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "DOWNDATA"))->list->values[3];
        beNDMWGameRam_AddMainPocketBonus((int)self, (int)player, &evadeRate, "CHOHATURITSU");
        if (evadeRate <= 0) evadeRate = 1;
        (igProperty_GetRecord((igObject *)player, "KAIHIRITSU"))->_data = evadeRate;
        guardRate = 0;
        beNDMWGameRam_AddMainSlotBonus(self, player, &guardRate, "BOUGYORITSU", 0);
        (igProperty_GetRecord((igObject *)player, "BOUGYORITSU"))->_data = guardRate;
        paralysisResist = 0;
        paralysisResist += ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "UPDATA"))->list->values[2];
        paralysisResist -= ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "DOWNDATA"))->list->values[2];
        beNDMWGameRam_AddMainSlotBonus(self, player, &paralysisResist, "MAHITEIKOU", 0);
        if (paralysisResist <= 0) paralysisResist = 1;
        (igProperty_GetRecord((igObject *)player, "MAHITEIKOU"))->_data = paralysisResist;
        poisonResist = 0;
        beNDMWGameRam_AddMainSlotBonus(self, player, &poisonResist, "DOKUTEIKOU", 0);
        (igProperty_GetRecord((igObject *)player, "DOKUTEIKOU"))->_data = poisonResist;
        bitRate = 0;
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &bitRate, "BITRITSU", 0);
        (igProperty_GetRecord((igObject *)player, "BITRITSU"))->_data = bitRate;
        expRate = 0;
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &expRate, "EXPRITSU", 0);
        (igProperty_GetRecord((igObject *)player, "EXPRITSU"))->_data = expRate;
        luckRate = 0;
        beNDMWGameRam_AddSubSlotBonus((int)self, (int)player, &luckRate, "LUCKRITSU", 0);
        (igProperty_GetRecord((igObject *)player, "LUCKRITSU"))->_data = luckRate;

        { beDataObjInt *zokusei = (igProperty_GetRecord((igObject *)player, "ATTACKZOKUSEI")); zokusei->_data = -1; }
        found = 0;
        int pocketCount = ((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "POWERPOCKET"))->list->_count;
        for (int p = 0; p < pocketCount; p++) {
            beNDMWItemBase *pocketItem = ((beNDMWItemBase **)((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "POWERPOCKET"))->list->_data)[p];
            if (pocketItem) {
                const char *zokuseiName = beNDMWItemBase_GetRecordString(pocketItem, (beNDMWStatus *)self, "ZOKUSEI");
                for (int element = 0; element < 4; element++) {
                    if (strcmp(zokuseiName, g_elementNames[element]) == 0) {
                        (igProperty_GetRecord((igObject *)player, "ATTACKZOKUSEI"))->_data = element;
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
            (igProperty_GetRecord((igObject *)player, "HPDRAIN"))->_data = hpDrain;
            mpDrain = 0;
            beNDMWGameRam_AddPowerPocketBonus((int)self, (int)player, &mpDrain, "MPDRAIN");
            (igProperty_GetRecord((igObject *)player, "MPDRAIN"))->_data = mpDrain;
        }
        (igProperty_GetRecord((igObject *)player, "CHOHATURITSU"))->_data =
            (igProperty_GetRecord((igObject *)player, "KAIHIRITSU"))->_data;
    }

    if (apply) {
        int weaponRec, weaponSkill;
        beNDMWItemBase *firstSocket;
        igObjectList *sockets;
        igStringRefList *names;
        firstSocket = ((beNDMWItemBase **)((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "POWERSOCKET"))->list->_data)[0];
        weaponRec = 0;
        weaponSkill = 0;
        if (firstSocket) {
            weaponRec = firstSocket->_recNo;
            weaponSkill = beNDMWItemBase_GetRecordInt(firstSocket, (beNDMWStatus *)self, "SKILL");
        }
        (igProperty_GetRecord((igObject *)player, "WEAPONRECNO"))->_data = weaponRec;
        (igProperty_GetRecord((igObject *)player, "WEAPONSKILLNO"))->_data = weaponSkill;

        sockets = ((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "POWERSOCKET"))->list;
        names = ((StringListProperty *)igProperty_GetRecordStringList((igObject *)player, "POWERSOCKETNAME"))->list;
        int nameCount = names->_count;
        for (int i = 0; i < nameCount; i++) {
            char **entry = &((char **)names->_data)[i];
            char *old, *fresh;
            fresh = StringPool_Intern((StringPool *)(SharedStringPool::get()), 0);
            old = *entry;
            if (old) {
                int *header = (int *)(old - 8);
                if (--header[1] == 0) StringChunk_ReleaseHeader((StringChunk *)header[0], (StringTokenHeader *)header);
            }
            *entry = fresh;
        }
        names->_count = 0;
        int socketCount = sockets->_count;
        for (int i = 0; i < socketCount; i++) {
            beNDMWItemBase *item = ((beNDMWItemBase **)sockets->_data)[i];
            if (item) {
                const char *model = beNDMWItemBase_GetRecordString(item, (beNDMWStatus *)self, "MODEL");
                char *interned;
                if (!model) {
                    interned = 0;
                } else {
                    interned = StringPool_Intern((StringPool *)(SharedStringPool::get()), model);
                }
                StringRef token(interned);
                StringList_AppendRetained((igStringRefList *)names, &token.p);
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

    list = ((ObjectListProperty *)igProperty_GetRecordFolder((igObject *)player, "WAZALIST"))->list;
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
 * otherwise from the allocator selected by kIGMemoryPoolHandleUser1. */
NearbyListRef beNDMWGameRam_CollectNearbyNonzeroHp(beNDMWGameRam *self,const char *group,int excluded,const Vector3 *center) {
    int entry_index;
    int member_id;
    int append_index;
    IntList *list;
    int selfAllocator=(int)((Gap::Core::igObject *)self)->getMemoryPool();
    NearbyListRef result(((IntList *)igIntList_Create((int)(g_useOwnerAllocator ? selfAllocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1)))));
    beMessenger_SendGroup((beMessenger *)self->_messenger,group,GETMATRIX);
    int count=beMessenger_GetIntCount((beMessenger *)self->_messenger);
    Vector3 delta;
    Matrix44 matrix;
    for(entry_index=0;entry_index<count;++entry_index) {
        member_id=beMessenger_GetInt((beMessenger *)self->_messenger,entry_index);
        if(member_id!=excluded) {
            beMessenger_GetMatrix(&matrix,(beMessenger *)self->_messenger,entry_index);
            igMatrix44f_GetTranslation((const float *)&matrix,(float *)&delta);
            delta.x-=center->x;
            delta.y-=center->y;
            delta.z-=center->z;
            if((delta.x*delta.x+delta.y*delta.y+delta.z*delta.z)<NEARBY_RADIUS_SQUARED) {
                beMessenger_PushArgContext((beMessenger *)self->_messenger);
                beMessenger_SelectReceivers((beMessenger *)self->_messenger,group,0,member_id);
                beMessenger_SetRunCheck((beMessenger *)self->_messenger,1);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger,GETHP);
                if(beMessenger_GetInt((beMessenger *)self->_messenger,0)) {
                    list=result.value;
                    append_index=list->getCount();
                    if(append_index<list->capacity) ++list->count;
                    else ((Gap::Core::igDataList *)list)->resizeAndSetCount(append_index+1,4);
                    list->data[append_index]=member_id;
                }
                beMessenger_PopArgContext((beMessenger *)self->_messenger);
            }
        }
    }
    return result;
}

extern "C" {
#define MULT_HI(a,b) ((int)(((long long)(int)(a)*(long long)(int)(b))>>32))

extern char GETMATRIX[];
extern char GETHP[];
extern char GETDATABASE_5[];
extern char DATABASE_5[];
extern char GETDATABASE_6[];
extern char DATABASE_6[];
extern unsigned char g_boolListClearValue;
int beNDMWGameRam_OnMessage(beNDMWGameRam *self, int ram, beMessengerWork *message);
}
/* The data-list reference made from an allocator value: constructed by beNDMWGameRam_CreateDataListRef and released by the shared igSmartPointer destructor, both out of line. */ class RecoveryCopiedRef { public: void *value; RecoveryCopiedRef(const AllocatorValue &source); ~RecoveryCopiedRef(); };
/* Gives `obj` a fresh object from the allocator.
 * matching construct: written in place, the copied reference takes the frame slot below retail's (1028 for 1032);
 * in this inline's own scope it lies where retail has it. */
struct ObjectRefAssigner { static int *Assign(void *obj, int alloc) { RecoveryCopiedRef c(beNDMWLoadIntf2_beBaseInfoDataList_MakeAllocatorValue(beNDMWLoadIntf2_Memory_SelectAllocator(&kIGMemoryPoolHandleUser1, alloc))); return (int *)beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Assign((ObjectRefTarget **)obj, (ObjectRefTarget **)&c); } };
/* Stores a retained copy of `v` at list[idx] when idx is in range: the bounds-checked setter of a string list. */
struct StringListStore { static void SetAt(igStringRefList *list, int idx, const StringRef &v) { if (list->_count != 0 && idx >= 0 && idx < list->_count) igStringRef_Assign((igStringRef *)((char *)beNDMWGameRam_igStringRefList_GetData((igDataList *)list) + idx * 4), (const igStringRef &)v); } };
/* Appends to an int list, growing it when full; the element buffer is read through the out-of-line accessor. */
class IntListAppend { public:
 struct Header { int word0; int word1; int count; int capacity; };
 static void append(void *list, int value) {
  Header *h = (Header *)list;
  /* matching construct: the count is re-read through a const view of the header; read plainly or through a const
   * accessor, the message handler's size changes (41856 or 41880 for 41864) */
  const Header *view = h;
  int index = h->count;
  if (index < h->capacity) {
   h->count = view->count + 1;
  } else {
   ((Gap::Core::igDataList *)list)->resizeAndSetCount(index + 1, 4);
  }
  ((int *)beNDMWLoadIntf2_igIntList_GetData((igDataList *)list))[index] = value;
 }
};
/* The database tables the message handler reads. Each is requested from the database object the first
 * time it is needed and kept in the receiver; the fetched reference goes in through the out-of-line
 * assign call. */
struct MessageDatabases {
    static inline void *PcTech(beNDMWGameRam *self)
    {
        if (beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBPcTech) == 0) {
            beMessenger_SendNamed((beMessenger *)self->_messenger, DATABASE_4, pcTech_2, 0, GETDATABASE_4);
            beNDMWGameRam_igSmartPointer_beDataBase_Assign((ObjectRefTarget **)&self->_dBPcTech, (ObjectRefTarget *)beMessenger_GetObject((beMessenger *)self->_messenger, 0));
        }
        return (void *)beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBPcTech);
    }
    /* The table names are passed in so the literals stay in the handler's own string pool. */
    static inline void *Enemy(beNDMWGameRam *self, const char *name)
    {
        if (beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBEnemy) == 0) {
            beMessenger_SendNamed((beMessenger *)self->_messenger, &DATABASE_5[0], name, 0, &GETDATABASE_5[0]);
            beNDMWGameRam_igSmartPointer_beDataBase_Assign((ObjectRefTarget **)&self->_dBEnemy, (ObjectRefTarget *)beMessenger_GetObject((beMessenger *)self->_messenger, 0));
        }
        return (void *)beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBEnemy);
    }
    static inline void *Eneatk(beNDMWGameRam *self, const char *name)
    {
        if (beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBEneatk) == 0) {
            beMessenger_SendNamed((beMessenger *)self->_messenger, &DATABASE_6[0], name, 0, &GETDATABASE_6[0]);
            beNDMWGameRam_igSmartPointer_beDataBase_Assign((ObjectRefTarget **)&self->_dBEneatk, (ObjectRefTarget *)beMessenger_GetObject((beMessenger *)self->_messenger, 0));
        }
        return (void *)beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBEneatk);
    }
    static inline void *Shinka(beNDMWGameRam *self)
    {
        if (beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBShinka) == 0) {
            beMessenger_SendNamed((beMessenger *)self->_messenger, DATABASE_3, shinka_2, 0, GETDATABASE_3);
            beNDMWGameRam_igSmartPointer_beDataBase_Assign((ObjectRefTarget **)&self->_dBShinka, (ObjectRefTarget *)beMessenger_GetObject((beMessenger *)self->_messenger, 0));
        }
        return (void *)beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBShinka);
    }
};
/* Reads the message handler repeats: a player's data record and the system's random source. */
struct MessageAccess {
    static inline int Player(beNDMWGameRam *self, int index)
    {
        return beNDMWLoadIntf2_igObjectList_Get((igDataList *)beNDMWGameRam_igSmartPointer_beDataObjListList_Get(&self->_playerDataListList), index);
    }
    static inline igRandomNumberDispatchView *Random(beNDMWGameRam *self)
    {
        return (igRandomNumberDispatchView *)beNDMWGameRam_igSmartPointer_igRandomNumber_Get(&((beSystem *)self->_system)->_random);
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
/* How an enemy attack record (the eneatk table's TYPE) computes its damage. */
enum EnemyAttackType { ENEATK_PHYSICAL, ENEATK_MAGIC, ENEATK_MAXHPRATIO };
int beNDMWGameRam_OnMessage(beNDMWGameRam *self, int ram, beMessengerWork *message) {
    int e2pDmgNetCrit;
    int e2pHitPlayerIndex;
    int e2pHitAccuracy;
    unsigned char e2pHit;
    int e2pHitAttackNo;
    int e2pHitEnemyRecNo;
    int e2pHitAttackId;
    int e2pHitPlayerSpeed;
    void *e2pHitPlayer;
    int e2pHitGuardRate;
    int e2pHitEvasion;
    int e2pHitEnemySpeed;
    int hitEnemyRecNo;
    int hitAgility;
    int hitPlayerIndex;
    int hitAccuracy;
    int hitAttackId;
    int hitDownEvasion;
    int hitEnemyAgility;
    beNDMWMdlPEBaseInfoWork *hitEnemy;
    int hitWeaponSkill;
    void *player;
    Vector3 healCenter;
    Vector3 cureCenter;
    Vector3 raiseCenter;
    Vector3 speedCenter;
    Vector3 powerCenter;
    Vector3 refractCenter;
    Vector3 hpEffectOffset;
    Vector3 mpEffectOffset;
    Vector3 skillEffectOffset;
    Vector3 levelUpEffectOffset;
    Vector3 healEffectOffset;
    Vector3 cureEffectOffset;
    Vector3 speedEffectOffset;
    Vector3 powerEffectOffset;
    Vector3 refractEffectOffset;
    Matrix44 raiseMatrix;
    Matrix44 healMatrix;
    Matrix44 cureMatrix;
    Matrix44 raiseSourceMatrix;
    Matrix44 speedMatrix;
    Matrix44 powerMatrix;
    Matrix44 refractMatrix;
    int isCritical;
    int skillGainMode;
    int killerExp;
    int e2pStunEnemyRecNo;
    unsigned char eBindApplies;
    int raiseSecondValue;
    int healSkill;
    int refractDark;
    int gainRate;
    int sleepTechniqueNo;
    int bindTechniqueNo;
    int atkDownTimeTechNo;
    int atkDownSpeedTechNo;
    int atkDownCritTechNo;
    int atkDownParalysisTechNo;
    int atkDownEvadeTechNo;
    int powDownTimeTechNo;
    int powDownStrengthTechNo;
    int powDownDefTechNo;
    int techniqueNo;
    int patkTechniqueNo;
    int skillTechniqueNo;
    int poisonTechniqueNo;
    int poisonDamageTechniqueNo;
    int levelBaseExp;
    int rankDamagePercent;
    int ePowPlayerIndex;
    int ePowEnemyRecNo;
    int ePowAttackId;
    int ePowEnemyIntelligence;
    int ePowBaseTime;
    int ePowStrRank;
    int ePowStrEnemyIntelligence;
    int ePowDefRank;
    int ePowDefEnemyIntelligence;
    int targetIndex;
    int healListDefault;
    int healDataDefault;
    int healList7;
    int healData7;
    int healList8;
    int healData8;
    int healBaseHp;
    int healListData;
    int cureListData;
    int raiseListData;
    int speedSkillNo;
    int speedTimeBase;
    int speedSkillList;
    int speedSkillData;
    int speedTechSpeed;
    int speedListData;
    int speedCrit;
    int speedParalysis;
    int speedEvade;
    int powerTimeBase;
    int powerSkillNo;
    int powerSkillList;
    int powerSkillData;
    int powerMaxHp;
    int powerStrength;
    int powerDefense;
    int powerListData;
    int refractTime;
    int refractListData;
    beDataObjString *digimonNameProp;
    beDataObjInt *bitProp;
    IntValuesProperty *chipDataProp;
    int *chipDataBuffer;
    beDataObjInt *bitResetProp;
    beDataObjInt *levelProp;
    beDataObjInt *expProp;
    IntValuesProperty *chipDataExpProp;
    int *chipDataExpBuffer;
    beDataObjInt *expWriteProp;
    int playerIndex;
    int enemyRecNo;
    int attackId;
    int patkPlayerIndex;
    int patkAttackId;
    int skillPlayerIndex;
    int skillAttackId;
    int weaponSkillList;
    int weaponSkillData;
    int techniqueSkillNo;
    int techSkillList;
    int techSkillData;
    int skillRecord;
    int skillData;
    int growRate;
    int killerIndex;
    int expEnemyRecNo;
    int stunPlayerIndex;
    int stunEnemyRecNo;
    int stunScale;
    int stunPower;
    int stunResist;
    int poisonPlayerIndex;
    int poisonEnemyRecNo;
    int poisonAttackId;
    int poisonSkillNo;
    int poisonSkillList;
    int poisonSkillData;
    int poisonResist;
    int poisonBaseTime;
    int sleepPlayerIndex;
    int sleepEnemyRecNo;
    int sleepAttackId;
    int sleepSkillNo;
    int sleepSkillList;
    int sleepSkillData;
    int sleepSpirit;
    int sleepBaseTime;
    int bindPlayerIndex;
    int bindEnemyRecNo;
    int bindAttackId;
    int bindSkillNo;
    int bindSkillList;
    int bindSkillData;
    int bindSpirit;
    int bindBaseTime;
    int atkDownPlayerIndex;
    int atkDownEnemyRecNo;
    int atkDownAttackId;
    int atkDownSkillNo;
    int atkDownSkillList;
    int atkDownSkillData;
    int atkDownSpirit;
    int atkDownBaseTime;
    int atkDownSpeedSkillNo;
    int atkDownSpeedSkillList;
    int atkDownSpeedSkillData;
    int atkDownEnemySpeed;
    int atkDownTechSpeed;
    int atkDownCritRate;
    int atkDownParalysisRate;
    int atkDownEvadeRate;
    int powDownPlayerIndex;
    int powDownEnemyRecNo;
    int powDownAttackId;
    int powDownSkillNo;
    int powDownSkillList;
    int powDownSkillData;
    int powDownSpirit;
    int powDownBaseTime;
    int powDownStrSkillNo;
    int powDownStrSkillList;
    int powDownStrSkillData;
    int powDownEnemyStrength;
    int powDownTechStrength;
    int powDownDefSkillNo;
    int powDownDefSkillList;
    int powDownDefSkillData;
    int powDownEnemyDefense;
    int powDownTechDefense;
    int e2pHitAttackType;
    int e2pDmgPlayerIndex;
    int e2pDmgEnemyRecNo;
    int e2pDmgAttackId;
    int e2pDmgDownValues;
    int e2pDmgEnemyStrength;
    int e2pDmgAttackStrength;
    int e2pDmgDown2Values;
    int e2pDmgEnemyCrit;
    int e2pDmgEnemyIntelligence;
    int e2pDmgRatioPower;
    beDataObjInt *e2pDmgMaxHpProperty;
    int rankPlayerIndex;
    int rankAttackId;
    int rankHitCount;
    int rankDamage;
    int rankPlayer;
    int e2pStunPlayerIndex;
    int e2pStunAttackId;
    int e2pStunDamage;
    int e2pStunHitKind;
    int e2pStunDownValues;
    int e2pStunEnemyParalysisRate;
    int ePoisonPlayerIndex;
    int ePoisonAttackId;
    int ePoisonBaseTime;
    int ePoisonRate;
    int ePoisonCure;
    int eSleepPlayerIndex;
    int eSleepEnemyRecNo;
    int eSleepAttackId;
    int eSleepRank;
    int eSleepEnemyIntelligence;
    int eSleepBaseTime;
    int eBindPlayerIndex;
    int eBindEnemyRecNo;
    int eBindAttackId;
    int eBindAttackNo;
    int eBindTime;
    int eBindRank;
    int eBindAttackType;
    int eBindEnemyIntelligence;
    int eBindFixedTime;
    int eBindBaseTime;
    int eBindTimeEnemyIntelligence;
    int eAtkPlayerIndex;
    int eAtkEnemyRecNo;
    int eAtkAttackId;
    int eAtkEnemyIntelligence;
    int eAtkBaseTime;
    int eAtkSpeedRank;
    int eAtkSpeedEnemyIntelligence;
    int eAtkAccRank;
    int eAtkAccEnemyIntelligence;
    int maxHp;
    int intelligence;
    int sleepIntelligence;
    int bindIntelligence;
    int atkDownIntelligence;
    unsigned int atkDownSpeedSkill;
    int atkDownSpeedFloor;
    int powDownIntelligence;
    int powDownStrFloor;
    int powDownDefFloor;
    int e2pStunResist;
    int ePoisonMaxHp;
    int eSleepChanceBase;
    int eAtkChanceBase;
    int ePowChanceBase;
    int damage;
    int element;
    int weaponSkillNo;
    int rollKind;
    int digimonNo;
    int poisonSkill;
    int atkDownSkill;
    int strength;
    int powerSkillBonus;
    int eAtkAttackNo;
    int ePowAttackNo;
    int healAmount;
    int speedIntelligence;
    int powerIntelligence;
    int healCount;
    int sleepSkill;
    int bindSkill;
    int powDownSkill;
    int e2pDmgDefense;
    int e2pStunMaxHp;
    int ePoisonAttackNo;
    int maxMp;
    int e2pDmgAttackNo;
    int rankAttackNo;
    int healTarget;
    int raiseCount;
    int partySize;
    beNDMWMdlPEBaseInfoWork *e2pStunEnemy;
    int e2pStunAttackNo;
    int powerCount;
    int refractCount;
    int e2pDmgAttackType;
    int e2pDmgAttackCrit;
    int e2pDmgMagicPower;
    int e2pDmgMagicCrit;
    int rankSequence;
    int e2pStunAttackType;
    int e2pStunTimeSum;
    int casterIndex;
    int healSkillNo;
    int cureSkillNo;
    int cureCount;
    int speedCount;
    int currentExp;
    int elementResistance;
    int techPower;
    int hpDrain;
    int mpDrain;
    int expBonus;
    int eAtkAccCount;
    int ePowStrCount;
    int ePowDefCount;
    int chipDataCount;
    int skillCount;
    int stunChanceSum;
    int e2pStunChanceSum;
    int eAtkDownCount;
    int skillValue;
    int patkElement;
    int gainChance;
    int baseExp;
    int poisonResult;
    int sleepResult;
    int bindResult;
    int atkDownTime;
    int powDownChance;
    int powDownTime;
    int e2pDmgDownCrit;
    int e2pDmgMagicCritThreshold;
    int e2pStunAttackParalysis;
    bool e2pStunApplies;
    int e2pStunDownValue;
    int powDownDefPenalty;
    int e2pDmgDownDefense;
    int e2pDmgMagicResist;
    int e2pDmgRatioResist;
    int e2pDmgIsHighRoll;
    int eAtkTime;
    int eAtkSpeedPenalty;
    int eAtkAccPenalty;
    int eAtkRank;
    int ePowTime;
    int ePowStrPenalty;
    int ePowDefPenalty;
    int healLoop;
    int raiseLoop;
    int stunTime;
    int ePowRank;
    int poisonHit;
    int poisonChance;
    int sleepHit;
    int sleepChance;
    int bindHit;
    int bindChance;
    int atkDownHit;
    int atkDownChance;
    int atkDownSpeedPenalty;
    int powDownStrPenalty;
    int ePoisonTime;
    int powDownHit;
    int e2pStunTime;
    int isHighRoll;
    int e2pDmgDamage;
    int e2pDmgElement;
    int cureLoop;
    int raiseFirst;
    int expSlot;
    int newExp;
    int refractLoop;
    int skillNo;
    int speedLoop;
    int powerLoop;
    int defense;
    int currentSkill;
    int skillCap;
    int e2pStunEnemyParalysis;
    int e2pDmgResistBonus;
    int e2pDmgCritBonus;
    int e2pStunChance;
    int techResistance;
    int stunChance;
    int bindSkillTerm;
    int bindIntelligenceBonus;
    int atkDownSkillTerm;
    int atkDownIntelligenceBonus;
    int powDownSkillTerm;
    int powDownIntelligenceBonus;
    int skillTerm;
    int intelligenceBonus;
    int sleepSkillTerm;
    char *ePowMode;
    char *ePowEffectName;
    char *patkElementName;
    char *digimonName;
    char *levelUpName;
    char *poisonMode;
    char *atkDownMode;
    char *powDownMode;
    char *ePoisonMode;
    char *ePoisonEffectName;
    char *eSleepEffectName;
    char *eBindEffectName;
    char *eAtkMode;
    char *eAtkEffectName;
    beNDMWMdlPEBaseInfoWork *e2pDmgEnemy;
    char *e2pDmgPhysElementName;
    char *e2pDmgMagicElementName;
    char *e2pDmgRatioElementName;
    const char *chipName;
    char *elementName;
    char *eAtkInternedMode;
    char *ePowInternedMode;
    unsigned int stunRoll;
    unsigned int e2pDmgCritRoll;
    unsigned int e2pHitRoll;
    unsigned int e2pDmgResistRoll;
    unsigned int e2pStunRoll;
    int chance_sum;
    unsigned int eSleepRoll;
    unsigned int eBindRoll;
    unsigned int eAtkRoll;
    unsigned int ePowRoll;
    unsigned int powDownStrSkill;
    unsigned int powDownDefSkill;
    unsigned int powerSkill;
    unsigned int speedSkill;
    unsigned int eSleepSpirit;
    unsigned int eAtkSpirit;
    unsigned int ePowSpirit;
    unsigned int powDownRoll;
    unsigned int e2pHitGuardRoll;
    unsigned int e2pDmgMagicCritRoll;
    unsigned int e2pDmgSpread;
    unsigned int cureRoll;
    unsigned int cureLoopRoll;
    unsigned int resistanceRoll;
    unsigned int rollSpread;
    unsigned int gainRoll;
    unsigned int poisonRoll;
    unsigned int sleepRoll;
    unsigned int bindRoll;
    unsigned int atkDownRoll;
    unsigned int ePoisonRoll;
    unsigned int e2pDmgPhysResist;
    void *healValuesDefault;
    void *healValues7;
    void *healValues8;
    void *cureOwner;
    void *cureLoopOwner;
    void *speedSkillValues;
    int cureTarget;
    int speedTarget;
    int powerTarget;
    int refractTarget;
    int cureChance;
    int cureLoopChance;
    void *powerSkillValues;
    void *powerTechTable;
    void *playerList;
    igIntList *chipDataList;
    igIntList *chipDataExpList;
    void *weaponSkillValues;
    void *techSkillValues;
    igIntList *skillValueList;
    void *commonData;
    void *poisonSkillValues;
    void *sleepSkillValues;
    void *bindSkillValues;
    void *atkDownSkillValues;
    void *atkDownSpeedSkillValues;
    void *powDownSkillValues;
    void *powDownStrSkillValues;
    void *powDownDefSkillValues;
    void *e2pDmgDownCheck;
    void *e2pDmgDownList;
    void *e2pDmgDown2Check;
    void *e2pDmgDown2List;
    void *rankMoveObject;
    void *e2pStunDownCheck;
    void *e2pStunDownList;
    void *eSleepPlayerList;
    void *powDownPlayer;
    void *e2pDmgPlayer;
    beBaseInfoRam *rankEnemy;
    void *rankMoveList;
    void *e2pStunPlayer;
    void *ePoisonPlayer;
    void *eBindPlayer;
    beDataObjInt *eBindSpiritProperty;
    void *eAtkPlayer;
    void *eAtkDownList;
    beDataObjInt *eAtkSpeedSpirit;
    void *eAtkAccList;
    beDataObjInt *eAtkAccSpirit;
    void *ePowPlayer;
    void *ePowStrList;
    beDataObjInt *ePowStrSpirit;
    void *ePowDefList;
    beDataObjInt *ePowDefSpirit;
    void *magicPlayer;
    void *cureWork;
    void *cureLoopPlayer;
    void *cureLoopWork;
    void *speedTargetList;
    void *speedTargetPlayer;
    void *powerTargetList;
    void *powerTargetPlayer;
    void *refractTargetList;
    void *refractTargetPlayer;
    beNDMWMdlPEBaseInfoWork *enemy;
    void *patkPlayer;
    void *poisonPlayer;
    void *sleepPlayer;
    void *bindPlayer;
    void *atkDownPlayer;
    const char *messageName = (const char *)beNDMWGameRam_igStringRef_Get(&message->_message);
    void *messageEnum = GameRamMessage_GetMetaEnum();
    unsigned int messageId = beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, (igMetaEnum *)messageEnum, messageName);
    switch (messageId) {
    case GAMERAM_GETCOMMON: {
        void *commonData = (void *)(beNDMWGameRam_igSmartPointer_beDataObjList_Get(&self->_commonDataList));
        beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)commonData);
        return 1;
    }
    case GAMERAM_GETPLAYER: {
        int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        int player = MessageAccess::Player(self, playerIndex);
        beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)player);
        return 1;
    }
    case GAMERAM_GETPLAYER1: {
        int player = MessageAccess::Player(self, 0);
        beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)player);
        return 1;
    }
    case GAMERAM_GETPLAYER2: {
        int player = MessageAccess::Player(self, 1);
        beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)player);
        return 1;
    }
    case GAMERAM_GETPLAYER3: {
        int player = MessageAccess::Player(self, 2);
        beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)player);
        return 1;
    }
    case GAMERAM_GETPLAYER4: {
        int player = MessageAccess::Player(self, 3);
        beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)player);
        return 1;
    }
    case GAMERAM_RECALCPLAYER: {
        int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        unsigned char apply = 1;
        if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) != 0) {
            apply = beMessenger_GetBool((beMessenger *)self->_messenger, 0);
        }
        beNDMWGameRam_RecomputeStats(self, playerIndex, apply);
        return 1;
    }
    case GAMERAM_BASE2CURRENT: {
        int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        const char *speciesName = beMessenger_GetString((beMessenger *)self->_messenger, 0);
        int species = beNDMWGameRam_FindSpecies(self, speciesName);
        beNDMWGameRam_SelectSpecies(self, playerIndex, species);
        return 1;
    }
    case GAMERAM_CURRENT2BASE: {
        int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        beNDMWGameRam_StoreSpecies(self, playerIndex);
        return 1;
    }
    case GAMERAM_WEAPONEQUIPCHECK: {
        int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        int weaponIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
        beMessenger_AppendBool((beMessenger *)self->_messenger, beNDMWGameRam_HasUsableWeapon(self, playerIndex, weaponIndex));
        return 1;
    }
    case GAMERAM_WEAPONEQUIPSTRONG: {
        int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        beNDMWGameRam_EquipWeapon(self, playerIndex, 1);
        return 1;
    }
    case GAMERAM_GAMEDATAINIT: {
        int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        beNDMWGameRam_ResetPlayer(self, playerIndex);
        return 1;
    }
    case GAMERAM_GAMESTART: {
        int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        const char *playerName = beMessenger_GetString((beMessenger *)self->_messenger, 0);
        if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) == 1) {
            void *unicodeName = (void *)(beMessenger_GetObject((beMessenger *)self->_messenger, 0));
            { RecoveryRef<0> unicodeNameRef((void *)(unicodeName), true);
            beNDMWGameRam_JoinPlayerWithUnicodeName(self, playerIndex, (char *)playerName, unicodeNameRef);
            }
        } else {
            if (beMessenger_GetStringCount((beMessenger *)self->_messenger) == 2) {
                char *displayName = (char *)beMessenger_GetString((beMessenger *)self->_messenger, 1);
                beNDMWGameRam_JoinPlayerWithName(self, playerIndex, (char *)playerName, StringRef(displayName == 0 ? (char *)0 : (char *)StringPool_Intern((StringPool *)StringPool_GetInstance(), displayName)));
            }
        }
        return 1;
    }
    case GAMERAM_GAMEREMOVE: {
        int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        beNDMWGameRam_LeavePlayer(self, playerIndex);
        return 1;
    }
    case GAMERAM_DEADRESTART: {
        int playerIndex = 0;
        do {
            int player = MessageAccess::Player(self, playerIndex);
            if ((igProperty_GetRecordByte((igObject *)player, "ISUSE"))->_data != 0) {
                int maxHp = beNDMWGameRam_beDataObjInt_GetData((beDataObjInt *)igProperty_GetRecord((igObject *)player, "MHP"));
                (igProperty_GetRecord((igObject *)player, "HP"))->_data = maxHp;
                int maxMp = beNDMWGameRam_beDataObjInt_GetData((beDataObjInt *)igProperty_GetRecord((igObject *)player, "MMP"));
                (igProperty_GetRecord((igObject *)player, "MP"))->_data = maxMp;
            }
            playerIndex += 1;
        } while (playerIndex < 4);
        return 1;
    }
    case GAMERAM_ADDHP: {
        int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        int delta = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
        int showEffect = beMessenger_GetIntCount((beMessenger *)self->_messenger) < 3 ? 0 : beMessenger_GetInt((beMessenger *)self->_messenger, 2);
        int absoluteHp = beMessenger_GetIntCount((beMessenger *)self->_messenger) < 4 ? -1 : beMessenger_GetInt((beMessenger *)self->_messenger, 3);
        int changed = beNDMWGameRam_ChangeHp(self, playerIndex, delta, absoluteHp);
        if ((changed != 0) && (showEffect != 0)) {
            int player = MessageAccess::Player(self, playerIndex);
            const char *digimonName = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)player, "DIGIMONNAME"))->_data);
            beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "PLAYER", digimonName, playerIndex);
            beMessenger_AppendString((beMessenger *)self->_messenger, "x_250healhit00");
            beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_HEALEFONLY");
            beMessenger_AppendFloat((beMessenger *)self->_messenger, 1.0f);
            Vec3f_Copy(&hpEffectOffset, &g_vec3Zero);
            beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&hpEffectOffset);
            beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
            beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
            beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETEFFECT", 1);
        }
        return 1;
    }
    case GAMERAM_ADDMP: {
        int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        int delta = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
        int showEffect = 0;
        if (beMessenger_GetIntCount((beMessenger *)self->_messenger) == 3) {
            showEffect = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
        }
        beNDMWGameRam_ChangeMp(self, playerIndex, delta);
        if (showEffect != 0) {
            int player = MessageAccess::Player(self, playerIndex);
            const char *digimonName = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)player, "DIGIMONNAME"))->_data);
            beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "PLAYER", digimonName, playerIndex);
            beMessenger_AppendString((beMessenger *)self->_messenger, "x_250healhit00");
            beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_HEALEFONLY");
            beMessenger_AppendFloat((beMessenger *)self->_messenger, 1.0f);
            Vec3f_Copy(&mpEffectOffset, &g_vec3Zero);
            beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&mpEffectOffset);
            beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
            beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
            beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETEFFECT", 1);
        }
        return 1;
    }
    case GAMERAM_CTRLPLAYER: {
        const char *field = beMessenger_GetString((beMessenger *)self->_messenger, 0);
        int result = 0;
        if (strcmp(field, "EXP") == 0) {
            const char *operation = beMessenger_GetString((beMessenger *)self->_messenger, 1);
            int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            int value = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            beDataObjInt *exp = (igProperty_GetRecord((igObject *)((void *)MessageAccess::Player(self, playerIndex)), "EXP"));
            if (strcmp(operation, "SET") == 0) {
                exp->_data = value;
            } else {
                if (strcmp(operation, "ADD") == 0) {
                    exp->_data = (int)((int) (value + beNDMWGameRam_beDataObjInt_GetData((beDataObjInt *)((int) exp))));
                }
            }
        } else {
            if (strcmp(field, "HP") == 0) {
                const char *query = beMessenger_GetString((beMessenger *)self->_messenger, 1);
                int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
                int player = MessageAccess::Player(self, playerIndex);
                if (strcmp(query, GETHP) == 0) {
                    result = (igProperty_GetRecord((igObject *)player, "HP"))->_data;
                } else {
                    if (strcmp(query, "GETMHP") == 0) {
                        result = (igProperty_GetRecord((igObject *)player, "MHP"))->_data;
                    }
                }
            } else {
                if (strcmp(field, "MP") == 0) {
                    const char *query = beMessenger_GetString((beMessenger *)self->_messenger, 1);
                    int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
                    int player = MessageAccess::Player(self, playerIndex);
                    if (strcmp(query, "GETMP") == 0) {
                        result = (igProperty_GetRecord((igObject *)player, "MP"))->_data;
                    } else {
                        if (strcmp(query, "GETMMP") == 0) {
                            result = (igProperty_GetRecord((igObject *)player, "MMP"))->_data;
                        }
                    }
                }
            }
        }
        beMessenger_ClearInt((beMessenger *)self->_messenger);
        beMessenger_AppendInt((beMessenger *)self->_messenger, result);
        return 1;
    }
    case GAMERAM_CTRLITEM: {
        char *category = (char *)beMessenger_GetString((beMessenger *)self->_messenger, 0);
        const char *operationName = beMessenger_GetString((beMessenger *)self->_messenger, 1);
        char *slotName = (char *)beMessenger_GetString((beMessenger *)self->_messenger, 2);
        int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        int recNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
        int revision = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
        int pocketOrAmount = beMessenger_GetInt((beMessenger *)self->_messenger, 3);
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
                int deviceFolder = (int)igProperty_GetRecordFolder((igObject *)player, "DEVICEFOLDER");
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
                        beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                    } else {
                        switch (slotKind) {
                        case ITEMSLOT_WEAPON: {
                            int allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
                            int pooledAllocator = beNDMWLoadIntf2_Memory_SelectAllocator(&kIGMemoryPoolHandleUser0, allocator);
                            void *created = (void *)(beNDMWItemWeapon_Create(beNDMWGameRam_beNDMWItemWeapon_MakeAllocatorValue(pooledAllocator).v));
                            { RecoveryRef<1> item(created, false);
                            beNDMWItemWeapon_Set((beNDMWItemWeapon *)item.value, recNo, pocketOrAmount, revision);
                            ((Gap::Core::igObjectList *)items)->append((Gap::Core::igObject *)item.value);
                            }
                            break;
                        }
                        case ITEMSLOT_ARMOR1: {
                            int allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
                            int pooledAllocator = beNDMWLoadIntf2_Memory_SelectAllocator(&kIGMemoryPoolHandleUser0, allocator);
                            void *created = (void *)(beNDMWItemBlueArmor_Create(beNDMWGameRam_beNDMWItemBlueArmor_MakeAllocatorValue(pooledAllocator).v));
                            { RecoveryRef<2> item(created, false);
                            beNDMWItemBlueArmor_Set((beNDMWItemBlueArmor *)item.value, recNo, pocketOrAmount, revision);
                            ((Gap::Core::igObjectList *)items)->append((Gap::Core::igObject *)item.value);
                            }
                            break;
                        }
                        case ITEMSLOT_ARMOR2: {
                            int allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
                            int pooledAllocator = beNDMWLoadIntf2_Memory_SelectAllocator(&kIGMemoryPoolHandleUser0, allocator);
                            void *created = (void *)(beNDMWItemYellowArmor_Create(beNDMWGameRam_beNDMWItemYellowArmor_MakeAllocatorValue(pooledAllocator).v));
                            { RecoveryRef<3> item(created, false);
                            beNDMWItemYellowArmor_Set((beNDMWItemYellowArmor *)item.value, recNo, revision);
                            ((Gap::Core::igObjectList *)items)->append((Gap::Core::igObject *)item.value);
                            }
                            break;
                        }
                        case ITEMSLOT_ABCHIP: {
                            int allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
                            int pooledAllocator = beNDMWLoadIntf2_Memory_SelectAllocator(&kIGMemoryPoolHandleUser0, allocator);
                            void *created = (void *)(beNDMWItemAbilityChip_Create(beNDMWGameRam_beNDMWItemAbilityChip_MakeAllocatorValue(pooledAllocator).v));
                            { RecoveryRef<4> item(created, false);
                            beNDMWItemAbilityChip_Set((beNDMWItemAbilityChip *)item.value, recNo);
                            ((Gap::Core::igObjectList *)items)->append((Gap::Core::igObject *)item.value);
                            }
                            break;
                        }
                        }
                        beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                    }
                    goto done;
                case ITEMOP_CLR:
                    {
                    beNDMWItemBase *item;
                    int itemCount = items->_count;
                    removed = 0;
                    for (clearIndex = 0; clearIndex < itemCount; ++clearIndex) {
                        item = ((beNDMWItemBase **)items->_data)[clearIndex];
                        if ((slotKind == item->_kindNo) && (recNo == item->_recNo) && (item->_isEquip == 0)) {

                            beNDMWLoadIntf2_igObject_Release((igObject *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)items, clearIndex));
                            beNDMWGameRam_igObjectList_Remove(items, clearIndex);
                            removed = 1;
                            ((igObject **)items->_data)[items->_count] = 0;
                            break;
                        }
                    }
                    beMessenger_AppendBool((beMessenger *)self->_messenger, removed);
                    }
                    goto done;
                case ITEMOP_IS:
                    {
                    beNDMWItemBase *item;
                    int itemCount = items->_count;
                    for (findIndex = 0; findIndex < itemCount; ++findIndex) {
                        item = ((beNDMWItemBase **)items->_data)[findIndex];
                        if ((slotKind == item->_kindNo) && (recNo == item->_recNo)) {

                            beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                            return 1;
                        }
                    }
                    }
                    beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                    goto done;
                case ITEMOP_ISMAX:
                    if (items->_count == 0x24) {
                        beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                    } else {
                        beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                    }
                    goto done;
                case ITEMOP_ISEQUIP:
                    {
                    beNDMWItemBase *item;
                    int itemCount = items->_count;
                    equipped = 0;
                    for (equipIndex = 0; equipIndex < itemCount; ++equipIndex) {
                        item = ((beNDMWItemBase **)items->_data)[equipIndex];
                        if ((slotKind == item->_kindNo) && (recNo == item->_recNo) && (item->_isEquip != 0)) {

                            equipped = 1;
                            break;
                        }
                    }
                    beMessenger_AppendBool((beMessenger *)self->_messenger, equipped);
                    }
                    goto done;
                }
            } else {
                if (strcmp(category, "DISK") == 0) {
                    int player = MessageAccess::Player(self, playerIndex);
                    int diskFolder = (int)igProperty_GetRecordFolder((igObject *)player, "DISKFOLDER");
                    void *disks = (void *)(beNDMWGameRam_igSmartPointer_igObjectList_Get(&((beDataObjObjectList *)diskFolder)->_data));
                    switch (operation) {
                    case ITEMOP_SET: {
                        beNDMWItemDisk *disk = (beNDMWItemDisk *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)disks, beNDMWItemBase_IndexOfRecNo((igObjectList *)disks, recNo));
                        int owned = disk->_kazu;
                        if (owned == 9) {
                            beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                        } else {
                            int total = owned + pocketOrAmount;
                            if (total < 0xA) {
                                disk->_kazu = total;
                            } else {
                                disk->_kazu = 9;
                            }
                            beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                        }
                        break;
                    }
                    case ITEMOP_CLR: {
                        beNDMWItemDisk *disk = (beNDMWItemDisk *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)disks, beNDMWItemBase_IndexOfRecNo((igObjectList *)disks, recNo));
                        int owned = disk->_kazu;
                        if (owned == 0) {
                            beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                        } else {
                            int remaining = owned - pocketOrAmount;
                            if (remaining >= 0) {
                                disk->_kazu = remaining;
                            } else {
                                disk->_kazu = 0;
                            }
                            beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                        }
                        break;
                    }
                    case ITEMOP_IS:
                        if (((beNDMWItemDisk *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)disks, beNDMWItemBase_IndexOfRecNo((igObjectList *)disks, recNo)))->_kazu != 0) {
                            beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                        } else {
                            beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                        }
                        break;
                    case ITEMOP_ISMAX:
                        if (((beNDMWItemDisk *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)disks, beNDMWItemBase_IndexOfRecNo((igObjectList *)disks, recNo)))->_kazu == 9) {
                            beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                        } else {
                            beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                        }
                        break;
                    }
                    goto done;
                }
                if (strcmp(category, "FLAG") == 0) {
                    void *commonData = (void *)(beNDMWGameRam_igSmartPointer_beDataObjList_Get(&self->_commonDataList));
                    int flagFolder = (int)igProperty_GetRecordArray((igObject *)commonData, "FLAGFOLDER");
                    void *flags = (void *)(beNDMWGameRam_igSmartPointer_igBoolList_Get(&((beDataObjBoolList *)flagFolder)->_data));
                    unsigned char *flagBytes;
                    switch (operation) {
                    case ITEMOP_SET:
                        flagBytes = (unsigned char *)beNDMWGameRam_igBoolList_GetData((igUnsignedCharList *)flags);
                        if (*(flagBytes + recNo) != 0) {
                            beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                        } else {
                            int flagCount = ((igBoolList *)flags)->_count;
                            if ((flagCount != 0) && (recNo >= 0) && (recNo < flagCount)) {
                                unsigned char setValue = g_boolListSetValue;
                                *(unsigned char *)(recNo + (int)beNDMWGameRam_igBoolList_GetData((igUnsignedCharList *)flags)) = setValue;
                            }
                            beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                        }
                        break;
                    case ITEMOP_CLR:
                        flagBytes = (unsigned char *)beNDMWGameRam_igBoolList_GetData((igUnsignedCharList *)flags);
                        if (*(flagBytes + recNo) == 0) {
                            beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                        } else {
                            int flagCount = ((igBoolList *)flags)->_count;
                            if ((flagCount != 0) && (recNo >= 0) && (recNo < flagCount)) {
                                unsigned char clearValue = g_boolListClearValue;
                                *(unsigned char *)(recNo + (int)beNDMWGameRam_igBoolList_GetData((igUnsignedCharList *)flags)) = clearValue;
                            }
                            beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                        }
                        break;
                    case ITEMOP_IS:
                        flagBytes = (unsigned char *)beNDMWGameRam_igBoolList_GetData((igUnsignedCharList *)flags);
                        beMessenger_AppendBool((beMessenger *)self->_messenger, *(flagBytes + recNo));
                        break;
                    }
                    goto done;
                }
                if (strcmp(category, "BIT") == 0) {
                    void *player = (void *)MessageAccess::Player(self, playerIndex);
                    switch (operation) {
                    case ITEMOP_SET:
                        (igProperty_GetRecord((igObject *)player, "BIT"))->_data = recNo;
                        break;
                    case ITEMOP_GET:
                        beMessenger_ClearInt((beMessenger *)self->_messenger);
                        beMessenger_AppendInt((beMessenger *)self->_messenger, (igProperty_GetRecord((igObject *)player, "BIT"))->_data);
                        break;
                    case ITEMOP_ADD: {
                        bit = recNo + (igProperty_GetRecord((igObject *)player, "BIT"))->_data;
                        if (bit < 0) {
                            bit = 0;
                        } else if (bit > 0x98967F) {
                            bit = 0x98967F;
                        }
                        (igProperty_GetRecord((igObject *)player, "BIT"))->_data = bit;
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
        self->_isDispFightData = beMessenger_GetBool((beMessenger *)self->_messenger, 0);
        return 1;
    case GAMERAM_FIGHTCALC: {
        const char *commandText = beMessenger_GetString((beMessenger *)self->_messenger, 0);
        { StringRef commandName(commandText == 0 ? (char *)0 : (char *)StringPool_Intern((StringPool *)StringPool_GetInstance(), commandText));
        void *fightComEnum = (void *)(FightCom_GetMetaEnum());
        const char *commandString = (const char *)beNDMWGameRam_igStringRef_Get((int *)&commandName.p);
        unsigned int fightCommand;
        igMetaEnum_GetValueByName((igMetaEnum *)fightComEnum, commandString, (int *)&fightCommand);
        switch (fightCommand) {
        case FIGHTCOM_P2EISHITCHECK: {
            hitPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            hitEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            hitAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            hitEnemy = (beNDMWMdlPEBaseInfoWork *)(void *)(beMessenger_GetObject((beMessenger *)self->_messenger, 0));
            switch (hitAttackId / 10000) {
            case 4:
                beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                            break;
            default: {
                void *player = (void *)MessageAccess::Player(self, hitPlayerIndex);
                hitWeaponSkill = (igProperty_GetRecord((igObject *)player, "WEAPONSKILLNO"))->_data;
                hitAgility = (igProperty_GetRecord((igObject *)player, "SUBAYASA"))->_data;
                int skillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "SKILL"));
                void *skillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)skillList)->_data));
                int skillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)skillValues);
                hitWeaponSkill = *(int *)(skillData + (hitWeaponSkill * 4));
                hitAccuracy = (igProperty_GetRecord((igObject *)player, "MEICHURITSU"))->_data;
                hitEnemyAgility = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), hitEnemyRecNo, "SUBAYASA");
                if (beNDMWGameRam_igSmartPointer_igIntList_Get(&hitEnemy->_downDataList) == 0) {
                    hitDownEvasion = 0;
                } else {
                    void *downData = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&hitEnemy->_downDataList));
                    hitDownEvasion = ((int *)beNDMWLoadIntf2_igIntList_GetData((igDataList *)downData))[3];
                }
                unsigned int roll = MessageAccess::Random(self)->genrand() % 10000U;
                if ((int) roll < ((int) (hitAccuracy * ((hitAgility * 0x1E) + (hitWeaponSkill * 0x14) + 0x1770)) / (int) ((int) (hitEnemyAgility * (0x64 - hitDownEvasion)) / 100))) {
                    beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                } else {
                    beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                }
                            break;
            }
            }
            break;
        }
        case FIGHTCOM_P2EISCRITICAL: {
            int playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            int enemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            int attackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            void *player = (void *)MessageAccess::Player(self, playerIndex);
            unsigned char isCritical;
            if ((attackId / 10000) != 4) {
                int critRate = (igProperty_GetRecord((igObject *)player, "CHIMEIRITSU"))->_data;
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
                char *element = (char *)(beDataBase_GetRecordString((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "ZOKUSEI"));
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
                int techCritRate = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "CHIMEIRITSU");
                if (elementIndex >= 0) {
                    int resistance;
                    if (elementIndex >= 0) {
                        resistance = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), enemyRecNo, g_resistanceFields[elementIndex]);
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
            beMessenger_AppendBool((beMessenger *)self->_messenger, isCritical);
            break;
        }
        case FIGHTCOM_P2EDAMAGE: {
            playerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            enemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            attackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            isCritical = beMessenger_GetInt((beMessenger *)self->_messenger, 3);
            enemy = (beNDMWMdlPEBaseInfoWork *)(void *)(beMessenger_GetObject((beMessenger *)self->_messenger, 0));
            player = (void *)MessageAccess::Player(self, playerIndex);
            element = -1;
            switch (attackId / 10000) {
            default: {
                weaponSkillNo = (igProperty_GetRecord((igObject *)player, "WEAPONSKILLNO"))->_data;
                strength = (igProperty_GetRecord((igObject *)player, "TSUYOSA"))->_data;
                int skillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "SKILL"));
                void *skillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)skillList)->_data));
                int skillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)skillValues);
                skillValue = *(int *)(skillData + (weaponSkillNo * 4));
                if (beNDMWGameRam_igSmartPointer_igIntList_Get(&enemy->_downDataList) == 0) {
                    defense = 0;
                } else {
                    void *downData = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&enemy->_downDataList));
                    defense = ((int *)beNDMWLoadIntf2_igIntList_GetData((igDataList *)downData))[5];
                }
                defense = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), enemyRecNo, "MAMORI") - defense;
                damage = (int)((int) ((strength * 6) + (skillValue * 4)) / defense);
                if (damage < 0) {
                    damage = 0;
                } else if (damage > 0x1869F) {
                    damage = 0x1869F;
                }
                if (damage != 0) {
                    element = (igProperty_GetRecord((igObject *)player, "ATTACKZOKUSEI"))->_data;
                    if (element != -1) {
                        elementResistance = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), enemyRecNo, g_elementResistanceFields[element]);
                        resistanceRoll = MessageAccess::Random(self)->genrand() % 1000U;
                        if (elementResistance < (int) resistanceRoll) {
                            damage += (int) (damage * (0x3E8 - elementResistance)) / 1000;
                        }
                    }
                }
            break; }
            case 4: {
                techniqueNo = (int)((int) attackId % 1000);
                int techniqueRow;
                beNDMWGameRam_FindTechniqueRow(self, player, techniqueNo, &techniqueRow);
                techPower = (int)(0U - (unsigned int)beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "HP"));
                if (techPower != 0) {
                    int techSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SKILL");
                    int skillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)player, "SKILL"));
                    void *skillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)skillList)->_data));
                    int skillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)skillValues);
                    skillValue = *(int *)(skillData + (techSkillNo * 4));
                    int enemySpirit = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), enemyRecNo, "SEISHIN");
                    int techDmg = (int)((int) ((skillValue * 5) + ((techPower * 0x14) + ((igProperty_GetRecord((igObject *)player, "KASHIKOSA"))->_data * 0xA))) / enemySpirit);
                    if (techDmg < 0) {
                        techDmg = 0;
                    } else if (techDmg > 0x1869F) {
                        techDmg = 0x1869F;
                    }
                    damage = techDmg;
                } else {
                    damage = 0;
                }
                if (damage != 0) {
                    elementName = (char *)(beDataBase_GetRecordString((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "ZOKUSEI"));
                    if (strcmp(elementName, "fire") == 0) {
                        element = 0;
                    } else {
                        if (strcmp(elementName, "ice") == 0) {
                            element = 1;
                        } else {
                            if (strcmp(elementName, "thunder") == 0) {
                                element = 2;
                            } else {
                                if (strcmp(elementName, "dark") == 0) {
                                    element = 3;
                                } else {
                                    if (strcmp(elementName, "poison") == 0) {
                                        element = 4;
                                    } else {
                                        element = -1;
                                    }
                                }
                            }
                        }
                    }
                    if (element >= 0) {
                        techResistance = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), enemyRecNo, g_resistanceFields[element]);
                    } else {
                        techResistance = 0;
                    }
                    damage = (int)((int) (damage * (0x3E8 - techResistance)) / 1000);
                }
            break; }
            }
            if (damage < 0) {
                damage = 0;
            } else if (damage > 0x1869F) {
                damage = 0x1869F;
            }
            isHighRoll = 0;
            if (damage != 0) {
                if (isCritical != 0) {
                    if (skillValue < 0x3E9) {
                        damage += (int)((int) (damage * ((skillValue / 20) + 0x1E)) / 100);
                    } else if (skillValue < 0x7D1) {
                        damage += (int)((int) (damage * (((int) (skillValue - 0x3E8) / 50) + 0x50)) / 100);
                    } else {
                        damage += (int)((int) (damage * (((int) (skillValue - 0x7D0) / 100) + 0x64)) / 100);
                    }
                }
                if (damage != 0) {
                    rollKind = MessageAccess::Random(self)->genrand() & 3;
                    rollSpread = MessageAccess::Random(self)->genrand() % (unsigned int) (damage * 0x19);
                    switch (rollKind) {

                    case 0:
                        damage = (int)(rollSpread + (damage * 950)) / 1000;
                        break;

                    case 1:
                        damage = (int)(rollSpread + (damage * 975)) / 1000;
                        break;

                    case 2:
                        damage = (int)(rollSpread + (damage * 1000)) / 1000;
                        break;

                    case 3:
                        damage = (int)(rollSpread + (damage * 1025)) / 1000;
                        isHighRoll = 1;
                        break;
                    }
                }
                if (damage < 0) {
                    damage = 0;
                } else if (damage > 0x1869F) {
                    damage = 0x1869F;
                }
                switch (attackId / 10000) {
                default: {
                    hpDrain = (igProperty_GetRecord((igObject *)player, "HPDRAIN"))->_data;
                    if (hpDrain != 0) {
                        beNDMWGameRam_ChangeHp(self, playerIndex, (int) (damage * hpDrain) / 100, -1);
                    }
                    mpDrain = (igProperty_GetRecord((igObject *)player, "MPDRAIN"))->_data;
                    if (mpDrain != 0) {
                        beNDMWGameRam_ChangeMp(self, playerIndex, (int) (damage * mpDrain) / 100);
                    }
                break; }
                case 4: break;
                }
            }
            beMessenger_ClearInt((beMessenger *)self->_messenger);
            beMessenger_AppendInt((beMessenger *)self->_messenger, damage);
            beMessenger_AppendInt((beMessenger *)self->_messenger, element);
            beMessenger_AppendInt((beMessenger *)self->_messenger, isHighRoll);
            break;
        }
        case FIGHTCOM_GETPATKZOKUSEI:
            patkPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            patkAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            patkPlayer = (void *)MessageAccess::Player(self, patkPlayerIndex);
            switch (patkAttackId / 10000) {
            default: {
                patkElement = (igProperty_GetRecord((igObject *)patkPlayer, "ATTACKZOKUSEI"))->_data;
            break; }
            case 4: {
                patkTechniqueNo = (int)((int) patkAttackId % 10000);
                int techniqueRow;
                beNDMWGameRam_FindTechniqueRow(self, patkPlayer, patkTechniqueNo, &techniqueRow);
                patkElementName = (char *)(beDataBase_GetRecordString((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "ZOKUSEI"));
                if (strcmp(patkElementName, "fire") == 0) {
                    patkElement = 0;
                } else {
                    if (strcmp(patkElementName, "ice") == 0) {
                        patkElement = 1;
                    } else {
                        if (strcmp(patkElementName, "thunder") == 0) {
                            patkElement = 2;
                        } else {
                            if (strcmp(patkElementName, "dark") == 0) {
                                patkElement = 3;
                            } else {
                                if (strcmp(patkElementName, "poison") == 0) {
                                    patkElement = 4;
                                } else {
                                    patkElement = -1;
                                }
                            }
                        }
                    }
                }
            break; }
            }
            beMessenger_ClearInt((beMessenger *)self->_messenger);
            beMessenger_AppendInt((beMessenger *)self->_messenger, patkElement);
            break;
        case FIGHTCOM_P2ESKILLUP:
            int levelBand;
            void *skillPlayer;
            int level;
            int attackClass;
            int bandIndex;
            int levelGroup;
            int gainMode;
            short *bandThreshold;
            skillPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            skillAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            skillGainMode = beMessenger_GetInt((beMessenger *)self->_messenger, 3);
            skillPlayer = (void *)MessageAccess::Player(self, skillPlayerIndex);
            level = (igProperty_GetRecord((igObject *)skillPlayer, "LEVEL"))->_data;
            /* Ternary chain rather than if/else: only this form copies each next compare into the
             * beqz delay slot. */
            skillCap = (level < 0x25) ? level * 0x1E
                   : (level < 0x6C) ? (level * 0x14) + 0x168
                   : (level < 0xE4) ? (level * 0xA) + 0x596
                   : (level * 8) + 0x75C;
            attackClass = skillAttackId / 10000;
            if ((attackClass != 9) && (attackClass != 8) && (attackClass != 4)) {
                skillNo = (igProperty_GetRecord((igObject *)skillPlayer, "WEAPONSKILLNO"))->_data;
                weaponSkillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)skillPlayer, "SKILL"));
                weaponSkillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)weaponSkillList)->_data));
                weaponSkillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)weaponSkillValues);
                currentSkill = *(int *)(weaponSkillData + (skillNo * 4));
            } else {
                skillTechniqueNo = (int)((int) skillAttackId % 10000);
                int techniqueRow;
                beNDMWGameRam_FindTechniqueRow(self, skillPlayer, skillTechniqueNo, &techniqueRow);
                /* matching construct: the technique's skill number passes through its own local before it becomes
                 * skillNo; assigned to skillNo directly, the case needs another spill slot and the frame grows by 16 */
                techniqueSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SKILL");
                skillNo = techniqueSkillNo;
                techSkillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)skillPlayer, "SKILL"));
                techSkillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)techSkillList)->_data));
                techSkillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)techSkillValues);
                currentSkill = *(int *)(techSkillData + (skillNo * 4));
            }
            if (currentSkill < skillCap) {
                /* Same ternary form for the level band; the 0/2 pick below stays an if/else. */
                levelGroup = (level < 0x25) ? 0 : (level < 0x6C) ? 1 : (level < 0xE4) ? 2 : 3;
                if (skillGainMode == 1) {
                    gainMode = 2;
                } else {
                    gainMode = 0;
                }
                bandThreshold = (short *)(g_skillGainThresholds);
                /* `value <= *p` (not `*p >= value`) keeps the compare as slt at / bnez at. */
                for (bandIndex = 0; bandIndex < 0x15; bandIndex++, bandThreshold++) {
                    if (currentSkill <= *bandThreshold) {
                        levelBand = bandIndex;
                        break;
                    }
                }
                gainRate = g_skillGainTable[levelGroup][levelBand][gainMode];
                /* A switch with the default arm first, rather than a != chain, places the nop
                 * after the third beq. */
                switch (attackClass) {
                default: {
                    digimonNo = (igProperty_GetRecord((igObject *)skillPlayer, "DIGIMONNO"))->_data;
                    if (beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBShinka) == 0) {
                        beMessenger_SendNamed((beMessenger *)self->_messenger, DATABASE_3, shinka_2, 0, GETDATABASE_3);
                        beNDMWGameRam_igSmartPointer_beDataBase_Assign((ObjectRefTarget **)&self->_dBShinka, (ObjectRefTarget *)beMessenger_GetObject((beMessenger *)self->_messenger, 0));
                    }
                    growRate = beDataBase_GetRecordInt((beDataBase *)(void *)beNDMWGameRam_igSmartPointer_beDataBase_Get(&self->_dBShinka), digimonNo, g_weaponGrowFields[skillNo]);
                    gainChance = (int)((int) (gainRate * growRate * 0x1F4) / 1000);
                break; }
                case 4: case 8: case 9:
                    gainChance = gainRate * 0x64;
                    break;
                }
                gainRoll = MessageAccess::Random(self)->genrand() % 100000U;
                if ((int) gainRoll < gainChance) {
                    int newSkill = currentSkill + 1;
                    skillRecord = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)skillPlayer, "SKILL"));
                    skillValueList = (igIntList *)beNDMWGameRam_beDataObjIntList_GetData((int *)skillRecord);
                    skillCount = skillValueList->_count;
                    if ((skillCount != 0) && (skillNo >= 0) && (skillNo < skillCount)) {
                        skillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)skillValueList);
                        *(int *)(skillData + (skillNo * 4)) = newSkill;
                    }
                    beNDMWGameRam_RecomputeStats(self, skillPlayerIndex, 1);
                    beNDMWGameRam_StoreSpecies(self, skillPlayerIndex);
                    digimonName = (char *)(beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)skillPlayer, "DIGIMONNAME"))->_data));
                    beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "MODELCTRL", digimonName, skillPlayerIndex);
                    beMessenger_AppendString((beMessenger *)self->_messenger, "i_getitempnl01");
                    beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_TECUP");
                    beMessenger_AppendFloat((beMessenger *)self->_messenger, 1.0f);
                    Vec3f_Copy(&skillEffectOffset, &g_vec3Zero);
                    beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&skillEffectOffset);
                    beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                    beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                    beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETEFFECT", 1);
                }
            }
            break;
        case FIGHTCOM_P2EEXPUP:
            /* Block-local webs are declared in the order expup_idx, expup_player, expup_level,
             * expup_exp; their register ids fix the allocator push order. */
            int expup_idx;
            void *expup_player;
            int expup_level;
            int expup_exp;
            killerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            expEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            commonData = (void *)(beNDMWGameRam_igSmartPointer_beDataObjList_Get(&self->_commonDataList));
            partySize = (igProperty_GetRecord((igObject *)commonData, "NINZU"))->_data;
            expup_idx = 0;
            killerExp = 0;
            do {
                expup_player = (void *)MessageAccess::Player(self, expup_idx);
                if ((igProperty_GetRecordByte((igObject *)expup_player, "ISUSE"))->_data != 0) {
                    if ((igProperty_GetRecord((igObject *)expup_player, "HP"))->_data != 0) {
                        expup_level = (igProperty_GetRecord((igObject *)expup_player, "LEVEL"))->_data;
                        if (expup_level != 0x3E7) {
                            baseExp = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), expEnemyRecNo, "EXP");
                            expBonus = (igProperty_GetRecord((igObject *)expup_player, "EXPRITSU"))->_data;
                            if (expBonus != 0) {
                                baseExp = (int)((int) (baseExp * (expBonus + 0x64)) / 100);
                            }
                            int split;  /* Declared here: a late register id lets the allocator push the receiver before the four hot loop webs. */
                            switch (partySize) {
                            case 1:  /* Case 1 shares the default body, which keeps a dead `li v0,1` compare. */
                            default:
                                split = (baseExp * 100) / 2;
                                break;
                            case 2:
                                split = (baseExp * 140) / 3;
                                break;
                            case 3:
                                split = (baseExp * 160) / 4;
                                break;
                            case 4:
                                split = (baseExp * 200) / 5;
                                break;
                            }
                            if (expup_idx == killerIndex) {
                                split /= 50;
                                killerExp = split;
                            } else {
                                split /= 100;
                            }
                            /* The old value is read before the second record lookup (it lives
                             * across that call); the add is in place. */
                            expup_exp = (igProperty_GetRecord((igObject *)expup_player, "EXP"))->_data;
                            expup_exp = expup_exp + split;
                            (igProperty_GetRecord((igObject *)expup_player, "EXP"))->_data = expup_exp;
                            bool leveled_up = false;
                            if ((igProperty_GetRecord((igObject *)expup_player, "NEXTEXP"))->_data <= expup_exp) {
loop_449:
                                expup_level += 1;
                                (igProperty_GetRecord((igObject *)expup_player, "LEVEL"))->_data = expup_level;
                                beNDMWGameRam_RecomputeStats(self, expup_idx, 1);
                                beNDMWGameRam_StoreSpecies(self, expup_idx);
                                leveled_up = true;
                                if (expup_level != 0x3E7) {
                                    if (expup_exp >= (igProperty_GetRecord((igObject *)expup_player, "NEXTEXP"))->_data) {
                                        goto loop_449;
                                    }
                                }
                            }
                            if (leveled_up) {
                                maxHp = (igProperty_GetRecord((igObject *)expup_player, "MHP"))->_data;
                                maxMp = (igProperty_GetRecord((igObject *)expup_player, "MMP"))->_data;
                                levelUpName = (char *)(beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)expup_player, "DIGIMONNAME"))->_data));
                                beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "MODELCTRL", levelUpName, expup_idx);
                                beMessenger_AppendString((beMessenger *)self->_messenger, "i_getitempnl01");
                                beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_LVUP");
                                beMessenger_AppendFloat((beMessenger *)self->_messenger, 1.0f);
                                Vec3f_Copy(&levelUpEffectOffset, &g_vec3Zero);
                                beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&levelUpEffectOffset);
                                beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                                beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETEFFECT", 1);
                                (igProperty_GetRecord((igObject *)expup_player, "HP"))->_data = maxHp;
                                (igProperty_GetRecord((igObject *)expup_player, "MP"))->_data = maxMp;
                                beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "NUMBERCTRL", "lvnm", expup_idx);
                                beMessenger_AppendInt((beMessenger *)self->_messenger, expup_level);
                                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETVALUE", 1);
                                beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "METERCTRL", "hpmt", expup_idx);
                                beMessenger_AppendFloat((beMessenger *)self->_messenger, 100.0f);
                                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETPERCENT", 1);
                                beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "NUMBERCTRL", "hpnm", expup_idx);
                                beMessenger_AppendInt((beMessenger *)self->_messenger, maxHp);
                                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETVALUE", 1);
                                beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "METERCTRL", "mpmt", expup_idx);
                                beMessenger_AppendFloat((beMessenger *)self->_messenger, 100.0f);
                                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETPERCENT", 1);
                                beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "NUMBERCTRL", "mpnm", expup_idx);
                                beMessenger_AppendInt((beMessenger *)self->_messenger, maxMp);
                                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETVALUE", 1);
                            }
                        }
                    }
                }
                expup_idx += 1;
            } while (expup_idx < 4);
            beMessenger_ClearInt((beMessenger *)self->_messenger);
            beMessenger_AppendInt((beMessenger *)self->_messenger, killerExp);
            break;
        case FIGHTCOM_P2ESTUNTIME: {
            stunPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            stunEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            stunScale = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            stunPower = beMessenger_GetInt((beMessenger *)self->_messenger, 3);
            beMessenger_GetInt((beMessenger *)self->_messenger, 4);
            int stunBase = (igProperty_GetRecord((igObject *)((void *)MessageAccess::Player(self, stunPlayerIndex)), "MAHIRITSU"))->_data;
            stunResist = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), stunEnemyRecNo, "RES_STUN");
            stunRoll = MessageAccess::Random(self)->genrand() % 100U;
            stunTime = 0;
            stunChanceSum = (stunBase + ((int) (stunPower * 0x32) / stunScale) + 0x64) - stunResist;
            stunChance = stunChanceSum / 2;
            if ((int) stunRoll < stunChance) {
                stunTime = (int)((int) ((0xC8 - stunResist) * (((int) (stunPower * 0x1E) / stunScale) + (stunBase * 3))) / 400);
            }
            beMessenger_ClearInt((beMessenger *)self->_messenger);
            beMessenger_AppendInt((beMessenger *)self->_messenger, stunTime);
            break; }
        case FIGHTCOM_P2EPOISONTIME:
            poisonMode = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
            { StringRef mode(poisonMode == 0 ? (char *)0 : (char *)StringPool_Intern((StringPool *)StringPool_GetInstance(), poisonMode));
            poisonPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            poisonEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            poisonAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            poisonPlayer = (void *)MessageAccess::Player(self, poisonPlayerIndex);
            if (strcmp(mode.p, "TIME") == 0) {
                int techniqueRow;
                techniqueRow = 0;
                poisonTechniqueNo = poisonAttackId % 10000;
                poisonHit = 0;
                beNDMWGameRam_FindTechniqueRow(self, poisonPlayer, poisonTechniqueNo, &techniqueRow);
                poisonSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SKILL");
                poisonSkillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)poisonPlayer, "SKILL"));
                poisonSkillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)poisonSkillList)->_data));
                poisonSkillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)poisonSkillValues);
                poisonSkill = ((int *)poisonSkillData)[poisonSkillNo];
                poisonResist = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), poisonEnemyRecNo, "RES_POISON");
                if (poisonSkill < 0x3E9) {
                    skillTerm = poisonSkill / 4;
                    poisonChance = (int)((int) ((skillTerm + 0x2EE) * (0x3E8 - poisonResist)) / 1000);
                } else if (poisonSkill < 0x7D1) {
                    poisonChance = (int)((int) ((((int) (poisonSkill - 0x3E8) / 5) + 0x3E8) * (0x3E8 - poisonResist)) / 1000);
                } else {
                    poisonChance = (int)((int) ((((int) (poisonSkill - 0x7D0) / 10) + 0x4B0) * (0x3E8 - poisonResist)) / 1000);
                }
                poisonRoll = MessageAccess::Random(self)->genrand() % 1000U;
                if ((int) poisonRoll < poisonChance) {
                    poisonHit = 1;
                }
                if (poisonHit != 0) {
                    intelligence = (igProperty_GetRecord((igObject *)poisonPlayer, "KASHIKOSA"))->_data;
                    poisonBaseTime = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "TIME");
                    intelligenceBonus = intelligence / 2;
                    poisonResult = poisonBaseTime + intelligenceBonus;
                } else {
                    poisonResult = 0;
                }
                if (poisonResult == 0) {
                    poisonResult = -1;
                }
                beMessenger_ClearInt((beMessenger *)self->_messenger);
                beMessenger_AppendInt((beMessenger *)self->_messenger, poisonResult);
            } else {
                poisonDamageTechniqueNo = poisonAttackId % 10000;
                int techniqueRow;
                beNDMWGameRam_FindTechniqueRow(self, poisonPlayer, poisonDamageTechniqueNo, &techniqueRow);
                poisonResult = -(beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "HP") / 5);

                beMessenger_ClearInt((beMessenger *)self->_messenger);
                beMessenger_AppendInt((beMessenger *)self->_messenger, poisonResult);
            }
            }
            break;
        case FIGHTCOM_P2ESLEEPTIME:
            sleepPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            sleepEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            sleepAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            sleepPlayer = (void *)MessageAccess::Player(self, sleepPlayerIndex);
            int sleepTechniqueRow;
            sleepTechniqueRow = 0;
            sleepTechniqueNo = sleepAttackId % 10000;
            sleepHit = 0;
            beNDMWGameRam_FindTechniqueRow(self, sleepPlayer, sleepTechniqueNo, &sleepTechniqueRow);
            sleepSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), sleepTechniqueRow, "SKILL");
            sleepSkillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)sleepPlayer, "SKILL"));
            sleepSkillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)sleepSkillList)->_data));
            sleepSkillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)sleepSkillValues);
            sleepSkill = ((int *)sleepSkillData)[sleepSkillNo];
            sleepSpirit = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), sleepEnemyRecNo, "SEISHIN");
            if (sleepSkill < 0x3E9) {
                sleepSkillTerm = sleepSkill / 4;
                sleepChance = (int)((int) ((sleepSkillTerm + 0x226) * 0x64) / sleepSpirit);
            } else if (sleepSkill < 0x7D1) {
                sleepChance = (int)((int) ((((int) (sleepSkill - 0x3E8) / 5) + 0x320) * 0x64) / sleepSpirit);
            } else {
                sleepChance = (int)((int) ((((int) (sleepSkill - 0x7D0) / 10) + 0x3E8) * 0x64) / sleepSpirit);
            }
            sleepRoll = MessageAccess::Random(self)->genrand() % 1000U;
            if ((int) sleepRoll < sleepChance) {
                sleepHit = 1;
            }
            if (sleepHit != 0) {
                sleepIntelligence = (igProperty_GetRecord((igObject *)sleepPlayer, "KASHIKOSA"))->_data;
                sleepBaseTime = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), sleepTechniqueRow, "TIME");
                sleepResult = sleepBaseTime + sleepIntelligence / 2;
            } else {
                sleepResult = 0;
            }
            if (sleepResult == 0) {
                sleepResult = -1;
            }
            beMessenger_ClearInt((beMessenger *)self->_messenger);
            beMessenger_AppendInt((beMessenger *)self->_messenger, sleepResult);
            break;
        case FIGHTCOM_P2EBINDTIME:
            bindPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            bindEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            bindAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            bindPlayer = (void *)MessageAccess::Player(self, bindPlayerIndex);
            int bindTechniqueRow;
            bindTechniqueRow = 0;
            bindTechniqueNo = bindAttackId % 10000;
            bindHit = 0;
            beNDMWGameRam_FindTechniqueRow(self, bindPlayer, bindTechniqueNo, &bindTechniqueRow);
            bindSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), bindTechniqueRow, "SKILL");
            bindSkillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)bindPlayer, "SKILL"));
            bindSkillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)bindSkillList)->_data));
            bindSkillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)bindSkillValues);
            bindSkill = ((int *)bindSkillData)[bindSkillNo];
            bindSpirit = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), bindEnemyRecNo, "SEISHIN");
            if (bindSkill < 0x3E9) {
                bindSkillTerm = bindSkill / 4;
                bindChance = (int)((int) ((bindSkillTerm + 0x226) * 0x64) / bindSpirit);
            } else if (bindSkill < 0x7D1) {
                bindChance = (int)((int) ((((int) (bindSkill - 0x3E8) / 5) + 0x320) * 0x64) / bindSpirit);
            } else {
                bindChance = (int)((int) ((((int) (bindSkill - 0x7D0) / 10) + 0x3E8) * 0x64) / bindSpirit);
            }
            bindRoll = MessageAccess::Random(self)->genrand() % 1000U;
            if ((int) bindRoll < bindChance) {
                bindHit = 1;
            }
            if (bindHit != 0) {
                bindIntelligence = (igProperty_GetRecord((igObject *)bindPlayer, "KASHIKOSA"))->_data;
                bindBaseTime = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), bindTechniqueRow, "TIME");
                bindIntelligenceBonus = bindIntelligence / 2;
                bindResult = bindBaseTime + bindIntelligenceBonus;
            } else {
                bindResult = 0;
            }
            if (bindResult == 0) {
                bindResult = -1;
            }
            beMessenger_ClearInt((beMessenger *)self->_messenger);
            beMessenger_AppendInt((beMessenger *)self->_messenger, bindResult);
            break;
        case FIGHTCOM_P2EATKDWNTIME:
            atkDownMode = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
            { StringRef mode(atkDownMode == 0 ? (char *)0 : (char *)StringPool_Intern((StringPool *)StringPool_GetInstance(), atkDownMode));
            atkDownPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            atkDownEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            atkDownAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            atkDownPlayer = (void *)MessageAccess::Player(self, atkDownPlayerIndex);
            if (strcmp(mode.p, "TIME") == 0) {
                int techniqueRow;
                techniqueRow = 0;
                atkDownTimeTechNo = atkDownAttackId % 10000;
                atkDownHit = 0;
                beNDMWGameRam_FindTechniqueRow(self, atkDownPlayer, atkDownTimeTechNo, &techniqueRow);
                atkDownSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SKILL");
                atkDownSkillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)atkDownPlayer, "SKILL"));
                atkDownSkillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)atkDownSkillList)->_data));
                atkDownSkillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)atkDownSkillValues);
                atkDownSkill = ((int *)atkDownSkillData)[atkDownSkillNo];
                atkDownSpirit = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), atkDownEnemyRecNo, "SEISHIN");
                if (atkDownSkill < 0x3E9) {
                    atkDownSkillTerm = atkDownSkill / 4;
                    atkDownChance = (int)((int) ((atkDownSkillTerm + 0x226) * 0x64) / atkDownSpirit);
                } else if (atkDownSkill < 0x7D1) {
                    atkDownChance = (int)((int) ((((int) (atkDownSkill - 0x3E8) / 5) + 0x320) * 0x64) / atkDownSpirit);
                } else {
                    atkDownChance = (int)((int) ((((int) (atkDownSkill - 0x7D0) / 10) + 0x3E8) * 0x64) / atkDownSpirit);
                }
                atkDownRoll = MessageAccess::Random(self)->genrand() % 1000U;
                if ((int) atkDownRoll < atkDownChance) {
                    atkDownHit = 1;
                }
                if (atkDownHit != 0) {
                    atkDownIntelligence = (igProperty_GetRecord((igObject *)atkDownPlayer, "KASHIKOSA"))->_data;
                    atkDownBaseTime = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "TIME");
                    atkDownIntelligenceBonus = atkDownIntelligence / 2;
                    atkDownTime = atkDownBaseTime + atkDownIntelligenceBonus;
                } else {
                    atkDownTime = 0;
                }
                if (atkDownTime == 0) {
                    atkDownTime = -1;
                }
                beMessenger_ClearInt((beMessenger *)self->_messenger);
                beMessenger_AppendInt((beMessenger *)self->_messenger, atkDownTime);
            } else {
                if (strcmp(mode.p, "SUBAYASA") == 0) {
                    atkDownSpeedTechNo = atkDownAttackId % 10000;
                    int techniqueRow;
                    techniqueRow = 0;
                    beNDMWGameRam_FindTechniqueRow(self, atkDownPlayer, atkDownSpeedTechNo, &techniqueRow);
                    atkDownSpeedSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SKILL");
                    atkDownSpeedSkillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)atkDownPlayer, "SKILL"));
                    atkDownSpeedSkillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)atkDownSpeedSkillList)->_data));
                    atkDownSpeedSkillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)atkDownSpeedSkillValues);
                    atkDownSpeedSkill = ((int *)atkDownSpeedSkillData)[atkDownSpeedSkillNo];
                    atkDownEnemySpeed = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), atkDownEnemyRecNo, "SUBAYASA");
                    atkDownSpeedFloor = (int)((int) (-atkDownEnemySpeed * 0x50) / 100);
                    atkDownTechSpeed = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SUBAYASA");
                    atkDownSpeedPenalty = atkDownTechSpeed - ((int) atkDownSpeedSkill / 20);
                    if (atkDownSpeedPenalty < atkDownSpeedFloor) {
                        atkDownSpeedPenalty = atkDownSpeedFloor;
                    }
                    beMessenger_ClearInt((beMessenger *)self->_messenger);
                    beMessenger_AppendInt((beMessenger *)self->_messenger, -atkDownSpeedPenalty);
                } else {
                    if (strcmp(mode.p, "CHIMEIRITSU") == 0) {
                        atkDownCritTechNo = atkDownAttackId % 10000;
                        int techniqueRow;
                        beNDMWGameRam_FindTechniqueRow(self, atkDownPlayer, atkDownCritTechNo, &techniqueRow);
                        atkDownCritRate = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "CHIMEIRITSU");
                        beMessenger_ClearInt((beMessenger *)self->_messenger);
                        beMessenger_AppendInt((beMessenger *)self->_messenger, -atkDownCritRate);
                    } else {
                        if (strcmp(mode.p, "MAHIRITSU") == 0) {
                            atkDownParalysisTechNo = atkDownAttackId % 10000;
                            int techniqueRow;
                            beNDMWGameRam_FindTechniqueRow(self, atkDownPlayer, atkDownParalysisTechNo, &techniqueRow);
                            atkDownParalysisRate = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "MHIRITSU");
                            beMessenger_ClearInt((beMessenger *)self->_messenger);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, -atkDownParalysisRate);
                        } else {
                            if (strcmp(mode.p, "KAIHIRITSU") == 0) {
                                atkDownEvadeTechNo = atkDownAttackId % 10000;
                                int techniqueRow;
                                beNDMWGameRam_FindTechniqueRow(self, atkDownPlayer, atkDownEvadeTechNo, &techniqueRow);
                                atkDownEvadeRate = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "KAIHIRITSU");
                                beMessenger_ClearInt((beMessenger *)self->_messenger);
                                beMessenger_AppendInt((beMessenger *)self->_messenger, -atkDownEvadeRate);
                            }
                        }
                    }
                }
            }
            }
            break;
        case FIGHTCOM_P2EPOWDWNTIME:
            powDownMode = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
            { StringRef mode(powDownMode == 0 ? (char *)0 : (char *)StringPool_Intern((StringPool *)StringPool_GetInstance(), powDownMode));
            powDownPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            powDownEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            powDownAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            powDownPlayer = (void *)MessageAccess::Player(self, powDownPlayerIndex);
            if (strcmp(mode.p, "TIME") == 0) {
                int techniqueRow;
                techniqueRow = 0;
                powDownTimeTechNo = powDownAttackId % 10000;
                powDownHit = 0;
                beNDMWGameRam_FindTechniqueRow(self, powDownPlayer, powDownTimeTechNo, &techniqueRow);
                powDownSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SKILL");
                powDownSkillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)powDownPlayer, "SKILL"));
                powDownSkillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)powDownSkillList)->_data));
                powDownSkillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)powDownSkillValues);
                powDownSkill = ((int *)powDownSkillData)[powDownSkillNo];
                powDownSpirit = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), powDownEnemyRecNo, "SEISHIN");
                if (powDownSkill < 0x3E9) {
                    powDownSkillTerm = powDownSkill / 4;
                    powDownChance = (int)((int) ((powDownSkillTerm + 0x226) * 0x64) / powDownSpirit);
                } else if (powDownSkill < 0x7D1) {
                    powDownChance = (int)((int) ((((int) (powDownSkill - 0x3E8) / 5) + 0x320) * 0x64) / powDownSpirit);
                } else {
                    powDownChance = (int)((int) ((((int) (powDownSkill - 0x7D0) / 10) + 0x3E8) * 0x64) / powDownSpirit);
                }
                powDownRoll = MessageAccess::Random(self)->genrand() % 1000U;
                if ((int) powDownRoll < powDownChance) {
                    powDownHit = 1;
                }
                if (powDownHit != 0) {
                    powDownIntelligence = (igProperty_GetRecord((igObject *)powDownPlayer, "KASHIKOSA"))->_data;
                    powDownBaseTime = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "TIME");
                    powDownIntelligenceBonus = powDownIntelligence / 2;
                    powDownTime = powDownBaseTime + powDownIntelligenceBonus;
                } else {
                    powDownTime = 0;
                }
                if (powDownTime == 0) {
                    powDownTime = -1;
                }
                beMessenger_ClearInt((beMessenger *)self->_messenger);
                beMessenger_AppendInt((beMessenger *)self->_messenger, powDownTime);
            } else {
                if (strcmp(mode.p, "TSUYOSA") == 0) {
                    powDownStrengthTechNo = powDownAttackId % 10000;
                    int techniqueRow;
                    techniqueRow = 0;
                    beNDMWGameRam_FindTechniqueRow(self, powDownPlayer, powDownStrengthTechNo, &techniqueRow);
                    powDownStrSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SKILL");
                    powDownStrSkillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)powDownPlayer, "SKILL"));
                    powDownStrSkillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)powDownStrSkillList)->_data));
                    powDownStrSkillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)powDownStrSkillValues);
                    powDownStrSkill = ((int *)powDownStrSkillData)[powDownStrSkillNo];
                    powDownEnemyStrength = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), powDownEnemyRecNo, "TSUYOSA");
                    powDownStrFloor = (int)((int) (-powDownEnemyStrength * 0x50) / 100);
                    powDownTechStrength = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "TSUYOSA");
                    powDownStrPenalty = powDownTechStrength - ((int) powDownStrSkill / 20);
                    if (powDownStrPenalty < powDownStrFloor) {
                        powDownStrPenalty = powDownStrFloor;
                    }
                    beMessenger_ClearInt((beMessenger *)self->_messenger);
                    beMessenger_AppendInt((beMessenger *)self->_messenger, -powDownStrPenalty);
                } else {
                    if (strcmp(mode.p, "MAMORI") == 0) {
                        powDownDefTechNo = powDownAttackId % 10000;
                        int techniqueRow;
                        techniqueRow = 0;
                        beNDMWGameRam_FindTechniqueRow(self, powDownPlayer, powDownDefTechNo, &techniqueRow);
                        powDownDefSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SKILL");
                        powDownDefSkillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)powDownPlayer, "SKILL"));
                        powDownDefSkillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)powDownDefSkillList)->_data));
                        powDownDefSkillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)powDownDefSkillValues);
                        powDownDefSkill = ((int *)powDownDefSkillData)[powDownDefSkillNo];
                        powDownEnemyDefense = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), powDownEnemyRecNo, "MAMORI");
                        powDownDefFloor = (int)((int) (-powDownEnemyDefense * 0x50) / 100);
                        powDownTechDefense = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "MAMORI");
                        powDownDefPenalty = powDownTechDefense - ((int) powDownDefSkill / 20);
                        if (powDownDefPenalty < powDownDefFloor) {
                            powDownDefPenalty = powDownDefFloor;
                        }
                        beMessenger_ClearInt((beMessenger *)self->_messenger);
                        beMessenger_AppendInt((beMessenger *)self->_messenger, -powDownDefPenalty);
                    }
                }
            }
            }
            break;
        case FIGHTCOM_E2PISHITCHECK:
            e2pHitPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            e2pHitEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            e2pHitAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            e2pHitPlayer = (void *)MessageAccess::Player(self, e2pHitPlayerIndex);
            e2pHitAttackNo = e2pHitAttackId % 10000;
            e2pHit = 0;
            e2pHitAttackType = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pHitAttackNo, "TYPE");
            switch (e2pHitAttackType) {
            case ENEATK_PHYSICAL:
                e2pHitGuardRate = (igProperty_GetRecord((igObject *)e2pHitPlayer, "BOUGYORITSU"))->_data;
                e2pHitGuardRoll = MessageAccess::Random(self)->genrand() % 100U;
                if (e2pHitGuardRate <= (int) e2pHitGuardRoll) {
                    e2pHitPlayerSpeed = (igProperty_GetRecord((igObject *)e2pHitPlayer, "SUBAYASA"))->_data;
                    e2pHitEvasion = (igProperty_GetRecord((igObject *)e2pHitPlayer, "KAIHIRITSU"))->_data;
                    e2pHitEnemySpeed = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), e2pHitEnemyRecNo, "SUBAYASA");
                    e2pHitAccuracy = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pHitAttackNo, "MEICHURITSU");
                    e2pHitRoll = MessageAccess::Random(self)->genrand() % 100U;
                    if ((int) e2pHitRoll < ((int) (e2pHitAccuracy * e2pHitEnemySpeed) / (int) ((int) (e2pHitPlayerSpeed * (e2pHitEvasion + 0x64)) / 100))) {
                        e2pHit = 1;
                    }
                }
                break;
            default:
                e2pHit = 1;
                break;
            }
            beMessenger_ClearBool((beMessenger *)self->_messenger);
            beMessenger_AppendBool((beMessenger *)self->_messenger, e2pHit);
            break;
        case FIGHTCOM_E2PDAMAGE:
            e2pDmgPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            e2pDmgEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            e2pDmgAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            e2pDmgEnemy = (beNDMWMdlPEBaseInfoWork *)(void *)(beMessenger_GetObject((beMessenger *)self->_messenger, 0));
            e2pDmgPlayer = (void *)MessageAccess::Player(self, e2pDmgPlayerIndex);
            e2pDmgAttackNo = e2pDmgAttackId % 10000;
            e2pDmgAttackType = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pDmgAttackNo, "TYPE");
            e2pDmgDamage = 0;
            e2pDmgElement = -1;
            switch (e2pDmgAttackType) {
            case ENEATK_PHYSICAL:
                e2pDmgDefense = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "MAMORI"))->_data;
                e2pDmgDownCheck = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&e2pDmgEnemy->_downDataList));
                if (e2pDmgDownCheck == 0) {
                    e2pDmgDownDefense = 0;
                } else {
                    e2pDmgDownList = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&e2pDmgEnemy->_downDataList));
                    e2pDmgDownValues = beNDMWLoadIntf2_igIntList_GetData((igDataList *)e2pDmgDownList);
                    e2pDmgDownDefense = ((int *)e2pDmgDownValues)[4];
                }
                e2pDmgEnemyStrength = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), e2pDmgEnemyRecNo, "TSUYOSA");
                int e2pDmgNetStrength; e2pDmgNetStrength = e2pDmgEnemyStrength - e2pDmgDownDefense;
                e2pDmgAttackStrength = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pDmgAttackNo, "TSUYOSA");
                e2pDmgDamage = (int)((int) (e2pDmgNetStrength * e2pDmgAttackStrength) / e2pDmgDefense);
                if (e2pDmgDamage < 0) {
                    e2pDmgDamage = 0;
                } else if (e2pDmgDamage > 0x1869F) {
                    e2pDmgDamage = 0x1869F;
                }
                e2pDmgPhysElementName = (char *)(beDataBase_GetRecordString((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pDmgAttackNo, "ZOKUSEI"));
                e2pDmgPhysResist = 0;
                if (strcmp(e2pDmgPhysElementName, "fire") == 0) {
                    e2pDmgPhysResist = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "HONOOTEIKO"))->_data;
                    e2pDmgElement = 0;
                } else {
                    if (strcmp(e2pDmgPhysElementName, "ice") == 0) {
                        e2pDmgPhysResist = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "KOORITEIKO"))->_data;
                        e2pDmgElement = 1;
                    } else {
                        if (strcmp(e2pDmgPhysElementName, "thunder") == 0) {
                            e2pDmgPhysResist = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "KAMINARITEIKO"))->_data;
                            e2pDmgElement = 2;
                        } else {
                            if (strcmp(e2pDmgPhysElementName, "dark") == 0) {
                                e2pDmgPhysResist = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "YAMITEIKO"))->_data;
                                e2pDmgElement = 3;
                            }
                        }
                    }
                }
                if (e2pDmgPhysResist != 0) {
                    e2pDmgResistRoll = MessageAccess::Random(self)->genrand() % 1000U;
                    if (((int) e2pDmgPhysResist / 5) <= (int) e2pDmgResistRoll) {
                        if ((int) e2pDmgPhysResist < 0x3E9) {
                            e2pDmgResistBonus = (int)((int) (e2pDmgDamage * (((int) (0x3E8 - e2pDmgPhysResist) / 20) + 0x32)) / 100);
                        } else if ((int) e2pDmgPhysResist < 0x1389) {
                            e2pDmgResistBonus = (int)((int) (e2pDmgDamage * ((int) (0x1388 - e2pDmgPhysResist) / 80)) / 100);
                        } else {
                            e2pDmgResistBonus = 0;
                        }
                        e2pDmgDamage += e2pDmgResistBonus;
                    }
                }
                if (e2pDmgDamage != 0) {
                    e2pDmgDown2Check = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&e2pDmgEnemy->_downDataList));
                    if (e2pDmgDown2Check == 0) {
                        e2pDmgDownCrit = 0;
                    } else {
                        e2pDmgDown2List = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&e2pDmgEnemy->_downDataList));
                        e2pDmgDown2Values = beNDMWLoadIntf2_igIntList_GetData((igDataList *)e2pDmgDown2List);
                        e2pDmgDownCrit = ((int *)e2pDmgDown2Values)[1];
                    }
                    e2pDmgEnemyCrit = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), e2pDmgEnemyRecNo, "CHIMEIRITSU");
                    e2pDmgNetCrit = e2pDmgEnemyCrit - e2pDmgDownCrit;
                    e2pDmgAttackCrit = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pDmgAttackNo, "CHIMEIRITSU");
                    e2pDmgCritRoll = MessageAccess::Random(self)->genrand() % 10000U;
                    if (((0x64 - e2pDmgNetCrit) * (0x64 - e2pDmgAttackCrit)) <= (int) e2pDmgCritRoll) {
                        e2pDmgCritBonus = (int)((int) (e2pDmgDamage * (e2pDmgAttackCrit / 2 + 0x5A)) / 100);
                        e2pDmgDamage += e2pDmgCritBonus;
                    }
                }
                break;
            case ENEATK_MAGIC:
                e2pDmgMagicPower = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pDmgAttackNo, "TSUYOSA");
                if (e2pDmgMagicPower != 0) {
                    e2pDmgEnemyIntelligence = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), e2pDmgEnemyRecNo, "KASHIKOSA");
                    e2pDmgDamage = (int)((int) (e2pDmgEnemyIntelligence * e2pDmgMagicPower) / (int) (igProperty_GetRecord((igObject *)e2pDmgPlayer, "SEISHIN"))->_data);
                    if (e2pDmgDamage < 0) {
                        e2pDmgDamage = 0;
                    } else if (e2pDmgDamage > 0x1869F) {
                        e2pDmgDamage = 0x1869F;
                    }
                    e2pDmgMagicResist = 0;
                    e2pDmgMagicElementName = (char *)(beDataBase_GetRecordString((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pDmgAttackNo, "ZOKUSEI"));
                    if (strcmp(e2pDmgMagicElementName, "fire") == 0) {
                        e2pDmgMagicResist = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "HONOOTEIKO"))->_data;
                        e2pDmgElement = 0;
                    } else {
                        if (strcmp(e2pDmgMagicElementName, "ice") == 0) {
                            e2pDmgMagicResist = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "KOORITEIKO"))->_data;
                            e2pDmgElement = 1;
                        } else {
                            if (strcmp(e2pDmgMagicElementName, "thunder") == 0) {
                                e2pDmgMagicResist = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "KAMINARITEIKO"))->_data;
                                e2pDmgElement = 2;
                            } else {
                                if (strcmp(e2pDmgMagicElementName, "dark") == 0) {
                                    e2pDmgMagicResist = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "YAMITEIKO"))->_data;
                                    e2pDmgElement = 3;
                                }
                            }
                        }
                    }
                    if (e2pDmgMagicResist != 0) {
                        if (e2pDmgMagicResist < 0x3E9) {
                            e2pDmgDamage = (int)((int) (e2pDmgDamage * (((int) (0x3E8 - e2pDmgMagicResist) / 20) + 0x32)) / 100);
                        } else if (e2pDmgMagicResist < 0x1069) {
                            e2pDmgDamage = (int)((int) (e2pDmgDamage * ((int) (0x1388 - e2pDmgMagicResist) / 80)) / 100);
                        } else {
                            e2pDmgDamage = e2pDmgDamage / 10;
                        }
                    }
                    if (e2pDmgDamage != 0) {
                        e2pDmgMagicCrit = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pDmgAttackNo, "CHIMEIRITSU");
                        if (e2pDmgMagicCrit != 0) {
                            if (e2pDmgMagicResist < 0x3E9) {
                                e2pDmgMagicCritThreshold = (0x3E8 - e2pDmgMagicResist) + (e2pDmgMagicCrit * 0x64);
                            } else {
                                e2pDmgMagicCritThreshold = (e2pDmgMagicCrit * 0x64) - ((int) (e2pDmgMagicResist - 0x3E8) / 10);
                            }
                            e2pDmgMagicCritRoll = MessageAccess::Random(self)->genrand() % 10000U;
                            if (e2pDmgMagicCritThreshold <= (int) e2pDmgMagicCritRoll) {
                                e2pDmgCritBonus = (int)((int) (e2pDmgDamage + (e2pDmgMagicCrit / 2 + 0x5A)) / 100);
                                e2pDmgDamage += e2pDmgCritBonus;
                                break;
                            }
                        }
                    }
                }
                break;
            case ENEATK_MAXHPRATIO:
                e2pDmgRatioPower = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pDmgAttackNo, "TSUYOSA");
                e2pDmgMaxHpProperty = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "MHP"));
                e2pDmgDamage = (int)((int) (e2pDmgMaxHpProperty->_data * e2pDmgRatioPower) / 100);
                if (e2pDmgDamage < 0) {
                    e2pDmgDamage = 0;
                } else if (e2pDmgDamage > 0x1869F) {
                    e2pDmgDamage = 0x1869F;
                }
                e2pDmgRatioResist = 0;
                e2pDmgRatioElementName = (char *)(beDataBase_GetRecordString((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pDmgAttackNo, "ZOKUSEI"));
                if (strcmp(e2pDmgRatioElementName, "fire") == 0) {
                    e2pDmgRatioResist = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "HONOOTEIKO"))->_data;
                    e2pDmgElement = 0;
                } else {
                    if (strcmp(e2pDmgRatioElementName, "ice") == 0) {
                        e2pDmgRatioResist = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "KOORITEIKO"))->_data;
                        e2pDmgElement = 1;
                    } else {
                        if (strcmp(e2pDmgRatioElementName, "thunder") == 0) {
                            e2pDmgRatioResist = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "KAMINARITEIKO"))->_data;
                            e2pDmgElement = 2;
                        } else {
                            if (strcmp(e2pDmgRatioElementName, "dark") == 0) {
                                e2pDmgRatioResist = (igProperty_GetRecord((igObject *)e2pDmgPlayer, "YAMITEIKO"))->_data;
                                e2pDmgElement = 3;
                            }
                        }
                    }
                }
                if (e2pDmgRatioResist != 0) {
                    if (e2pDmgRatioResist < 0x3E9) {
                        e2pDmgCritBonus = (int)((int) (e2pDmgDamage * (((int) (0x3E8 - e2pDmgRatioResist) / 20) + 0x32)) / 100);
                        e2pDmgDamage += e2pDmgCritBonus;
                                break;
                    }
                    if (e2pDmgRatioResist < 0x1389) {
                        e2pDmgCritBonus = (int)((int) (e2pDmgDamage * ((int) (0x1388 - e2pDmgRatioResist) / 80)) / 100);
                        e2pDmgDamage += e2pDmgCritBonus;
                                break;
                    }
                }
                break;
            }
            if (e2pDmgDamage < 0) {
                e2pDmgDamage = 0;
            } else if (e2pDmgDamage > 0x1869F) {
                e2pDmgDamage = 0x1869F;
            }
            e2pDmgIsHighRoll = 0;
            if (e2pDmgDamage != 0) {
                int e2pDmgRollKind = MessageAccess::Random(self)->genrand() & 3;
                e2pDmgSpread = MessageAccess::Random(self)->genrand() % (unsigned int) (e2pDmgDamage * 0x19);
                switch (e2pDmgRollKind) {

                    case 0:
                        e2pDmgDamage = (int)(e2pDmgSpread + (e2pDmgDamage * 950)) / 1000;
                        break;

                    case 1:
                        e2pDmgDamage = (int)(e2pDmgSpread + (e2pDmgDamage * 975)) / 1000;
                        break;

                    case 2:
                        e2pDmgDamage = (int)(e2pDmgSpread + (e2pDmgDamage * 1000)) / 1000;
                        break;

                    case 3:
                        e2pDmgDamage = (int)(e2pDmgSpread + (e2pDmgDamage * 1025)) / 1000;
                        e2pDmgIsHighRoll = 1;
                        break;
                    }
            }
            if (e2pDmgDamage < 0) {
                e2pDmgDamage = 0;
            } else if (e2pDmgDamage > 0x1869F) {
                e2pDmgDamage = 0x1869F;
            }
            beMessenger_ClearInt((beMessenger *)self->_messenger);
            beMessenger_AppendInt((beMessenger *)self->_messenger, e2pDmgDamage);
            beMessenger_AppendInt((beMessenger *)self->_messenger, e2pDmgElement);
            beMessenger_AppendInt((beMessenger *)self->_messenger, e2pDmgIsHighRoll);
            break;
        case FIGHTCOM_E2PDAMAGERANK:
            int rank;
            rankPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            rankAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            rankHitCount = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            rankDamage = beMessenger_GetInt((beMessenger *)self->_messenger, 3);
            rankEnemy = (beBaseInfoRam *)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
            rank = 0;
            if (rankHitCount <= 0) {
                rank = 3;
            } else {
                rankPlayer = MessageAccess::Player(self, rankPlayerIndex);
                rankAttackNo = rankAttackId % 10000;
                int rankPower = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), rankAttackNo, "TSUYOSA");
                rankSequence = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), rankAttackNo, "SEQUENCE");
                int rankMaxHp; rankMaxHp = (igProperty_GetRecord((igObject *)rankPlayer, "MHP"))->_data;
                switch (rankSequence) {
                case 0:
                    if (rankPower == 0) {
                        rank = -1;
                    } else {
                        rankDamagePercent = (int)((int) (rankDamage * 0x64) / rankMaxHp);
                        if (rankDamagePercent < 0xA) {
                            rank = 0;
                        } else if (rankDamagePercent < 0x28) {
                            rank = 1;
                        } else {
                            rank = 2;
                        }
                    }
                    break;
                case 1:
                    rank = -1;
                    break;
                case 2:
                    rank = 0;
                    break;
                case 3:
                    rank = 2;
                    break;
                case 4:
                    rank = 1;
                    break;
                }
            }
            if (rank == 2) {
                if (beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(&rankEnemy->_dataList) == 0) {
                    ObjectRefAssigner::Assign(&rankEnemy->_dataList, (int)((Gap::Core::igObject *)rankEnemy)->getMemoryPool());
                }
                rankMoveList = (void *)(beNDMWGameRam_igSmartPointer_beModelCtrlMoveObjectList_Get(&((beNDMWMdlPEBaseInfoWork *)beNDMWGameRam_igSmartPointer_beModelCtrlInfoWork_Get(&((beModelCtrlInfoRamData *)beNDMWLoadIntf2_beBaseInfoDataList_FindProperty(beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Deref(&rankEnemy->_dataList), (int)g_propertyNameField, "ONE"))->_work))->_moveObjectList));
                if (((beModelCtrlMoveObjectList *)rankMoveList)->_count != 0) {
                    rankMoveObject = (void *)(beNDMWGameRam_beModelCtrlMoveObjectList_Get((igDataList *)rankMoveList, 1));
                    if (((beModelCtrlMoveObject *)rankMoveObject)->_isRun != 0) {
                        rank = 1;
                    }
                }
            }
            beMessenger_ClearInt((beMessenger *)self->_messenger);
            beMessenger_AppendInt((beMessenger *)self->_messenger, rank);
            break;
        case FIGHTCOM_E2PSTUNTIME: {
            e2pStunPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            e2pStunEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            e2pStunAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            e2pStunDamage = beMessenger_GetInt((beMessenger *)self->_messenger, 3);
            e2pStunHitKind = beMessenger_GetInt((beMessenger *)self->_messenger, 4);
            e2pStunEnemy = (beNDMWMdlPEBaseInfoWork *)(void *)(beMessenger_GetObject((beMessenger *)self->_messenger, 0));
            e2pStunPlayer = (void *)MessageAccess::Player(self, e2pStunPlayerIndex);
            e2pStunAttackNo = e2pStunAttackId % 10000;
            e2pStunAttackType = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pStunAttackNo, "TYPE");
            e2pStunEnemyParalysis = 0;
            e2pStunAttackParalysis = 0;
            e2pStunApplies = 0;
            switch (e2pStunAttackType) {
            case ENEATK_PHYSICAL:
                switch (e2pStunHitKind) { case 1: case 2: {
                    e2pStunDownCheck = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&e2pStunEnemy->_downDataList));
                    if (e2pStunDownCheck == 0) {
                        e2pStunDownValue = 0;
                    } else {
                        e2pStunDownList = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&e2pStunEnemy->_downDataList));
                        e2pStunDownValues = beNDMWLoadIntf2_igIntList_GetData((igDataList *)e2pStunDownList);
                        e2pStunDownValue = ((int *)e2pStunDownValues)[2];
                    }
                    e2pStunEnemyParalysisRate = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), e2pStunEnemyRecNo, "MAHIRITSU");
                    e2pStunEnemyParalysis = e2pStunEnemyParalysisRate - e2pStunDownValue;
                    e2pStunApplies = 1;
                } }
                break;
            case ENEATK_MAGIC:
                e2pStunAttackParalysis = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), e2pStunAttackNo, "MAHIRITSU");
                if (e2pStunAttackParalysis > 0) {
                    e2pStunApplies = 1;
                }
                break;
            case ENEATK_MAXHPRATIO:
                switch (e2pStunHitKind) { case 1: case 2: {
                    e2pStunApplies = 1;
                } }
                break;
            }
            e2pStunTime = 0;
            if (e2pStunApplies) {
                e2pStunMaxHp = (igProperty_GetRecord((igObject *)e2pStunPlayer, "MHP"))->_data;
                e2pStunResist = (igProperty_GetRecord((igObject *)e2pStunPlayer, "MAHITEIKOU"))->_data;
                e2pStunRoll = MessageAccess::Random(self)->genrand() % 100U;
                chance_sum = e2pStunAttackParalysis + e2pStunEnemyParalysis;
                int e2pStunDamagePercent = (int)((int) (e2pStunDamage * 0x32) / e2pStunMaxHp);
                e2pStunChanceSum = e2pStunResist + (e2pStunDamagePercent + 0x64 + chance_sum);
                e2pStunChance = e2pStunChanceSum / 2;
                if ((int) e2pStunRoll < e2pStunChance) {
                    e2pStunTimeSum = e2pStunResist + (e2pStunDamagePercent + 0x1E + chance_sum);
                    e2pStunTime = e2pStunTimeSum / 4;
                }
                if (e2pStunTime == 0) {
                    e2pStunTime = -1;
                }
            }
            beMessenger_ClearInt((beMessenger *)self->_messenger);
            beMessenger_AppendInt((beMessenger *)self->_messenger, e2pStunTime);
            break; }
        case FIGHTCOM_E2PPOISONTIME:
            ePoisonMode = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
            { StringRef mode((char *)(ePoisonMode == 0 ? (char *)0 : (char *)StringPool_Intern((StringPool *)(void *)StringPool_GetInstance(), ePoisonMode)));
            ePoisonPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            ePoisonAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            ePoisonPlayer = (void *)MessageAccess::Player(self, ePoisonPlayerIndex);
            ePoisonAttackNo = ePoisonAttackId % 10000;
            if (strcmp(mode.p, "TIME") == 0) {
                ePoisonTime = 0;
                ePoisonEffectName = (char *)(beDataBase_GetRecordString((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), ePoisonAttackNo, "KOUKA"));
                if (strcmp(ePoisonEffectName, "doku") == 0) {
                    int effectRank = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), ePoisonAttackNo, "KOUKARANK");
                    int poisonResist = (igProperty_GetRecord((igObject *)ePoisonPlayer, "DOKUTEIKOU"))->_data;
                    ePoisonRoll = MessageAccess::Random(self)->genrand() % 100U;
                    if ((int) ePoisonRoll < (poisonResist + ((effectRank * 0xF) + 0x1E))) {
                        ePoisonBaseTime = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), ePoisonAttackNo, "KOUKATIME");
                        ePoisonTime = poisonResist / 2 + ePoisonBaseTime;
                    }
                    if (ePoisonTime == 0) {
                        ePoisonTime = -1;
                    }
                }
                beMessenger_ClearInt((beMessenger *)self->_messenger);
                beMessenger_AppendInt((beMessenger *)self->_messenger, ePoisonTime);
            } else {
                if (strcmp(mode.p, "DAMAGE") == 0) {
                    ePoisonMaxHp = (igProperty_GetRecord((igObject *)ePoisonPlayer, "MHP"))->_data;
                    ePoisonRate = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), ePoisonAttackNo, "KOUKARANK");
                    beMessenger_ClearInt((beMessenger *)self->_messenger);
                    beMessenger_AppendInt((beMessenger *)self->_messenger, (int) (ePoisonMaxHp * ePoisonRate) / 100);
                } else {
                    if (strcmp(mode.p, "GEDOKU") == 0) {
                        ePoisonCure = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), ePoisonAttackNo, "GEDOKU");
                        beMessenger_ClearInt((beMessenger *)self->_messenger);
                        beMessenger_AppendInt((beMessenger *)self->_messenger, ePoisonCure);
                    }
                }
            }
            }
            break;
        case FIGHTCOM_E2PSLEEPTIME: {
            eSleepPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            eSleepEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            eSleepAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            /* matching construct: this lookup stays written out (and its result declared here); through
             * MessageAccess::Player the player and the modulo result swap callee-saved registers */
            eSleepPlayerList = (void *)(beNDMWGameRam_igSmartPointer_beDataObjListList_Get(&self->_playerDataListList));
            int eSleepPlayer = beNDMWLoadIntf2_igObjectList_Get((igDataList *)eSleepPlayerList, eSleepPlayerIndex);
            int eSleepAttackNo = eSleepAttackId % 10000;
            eSleepEffectName = (char *)(beDataBase_GetRecordString((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eSleepAttackNo, "KOUKA"));
            int eSleepTime = 0;
            if (strcmp(eSleepEffectName, "sleep") == 0) {
                eSleepRank = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eSleepAttackNo, "KOUKARANK");
                eSleepEnemyIntelligence = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), eSleepEnemyRecNo, "KASHIKOSA");
                eSleepSpirit = (igProperty_GetRecord((igObject *)eSleepPlayer, "SEISHIN"))->_data;
                eSleepRoll = MessageAccess::Random(self)->genrand() % 10000U;
                eSleepChanceBase = (((int) (eSleepEnemyIntelligence * 3) / (int) eSleepSpirit) + 0x64) - ((int) eSleepSpirit / 40);
                int hit_base = eSleepRank * 5;
                if ((int) eSleepRoll < (hit_base * eSleepChanceBase)) {
                    eSleepBaseTime = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eSleepAttackNo, "KOUKATIME");
                    eSleepTime = (int)((int) (eSleepBaseTime * eSleepChanceBase) / 100);
                }
                if (eSleepTime == 0) {
                    eSleepTime = -1;
                }
            }
            beMessenger_ClearInt((beMessenger *)self->_messenger);
            beMessenger_AppendInt((beMessenger *)self->_messenger, eSleepTime);
            break; }
        case FIGHTCOM_E2PBINDTIME: {
            eBindPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            eBindEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            eBindAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            eBindPlayer = (void *)MessageAccess::Player(self, eBindPlayerIndex);
            eBindAttackNo = eBindAttackId % 10000;
            eBindEffectName = (char *)(beDataBase_GetRecordString((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eBindAttackNo, "KOUKA"));
            eBindTime = 0;
            if (strcmp(eBindEffectName, "ashidome") == 0) {
                eBindRank = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eBindAttackNo, "KOUKARANK");
                eBindAttackType = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eBindAttackNo, "TYPE");
                eBindApplies = 1;
                if (eBindAttackType != ENEATK_MAXHPRATIO) {
                    eBindEnemyIntelligence = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), eBindEnemyRecNo, "KASHIKOSA");
                    unsigned int eBindSpirit = (igProperty_GetRecord((igObject *)eBindPlayer, "SEISHIN"))->_data;
                    eBindRoll = MessageAccess::Random(self)->genrand() % 10000U;
                    if ((eBindRank * 5 * ((((int) (eBindEnemyIntelligence * 3) / (int) eBindSpirit) + 0x64) - ((int) eBindSpirit / 40))) <= (int) eBindRoll) {
                        eBindApplies = 0;
                    }
                }
                if (eBindApplies) {
                    if (eBindAttackType == ENEATK_MAXHPRATIO) {
                        eBindFixedTime = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eBindAttackNo, "KOUKATIME");
                        eBindTime = eBindFixedTime;
                    } else {
                        eBindBaseTime = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eBindAttackNo, "KOUKATIME");
                        eBindTimeEnemyIntelligence = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), eBindEnemyRecNo, "KASHIKOSA");
                        eBindSpiritProperty = (igProperty_GetRecord((igObject *)eBindPlayer, "SEISHIN"));
                        eBindTime = (int)((int) (eBindBaseTime * ((((int) (eBindTimeEnemyIntelligence * 3) / (int) eBindSpiritProperty->_data) + 0x64) - ((int) eBindSpiritProperty->_data / 40))) / 100);
                    }
                }
                if (eBindTime == 0) {
                    eBindTime = -1;
                }
            }
            beMessenger_ClearInt((beMessenger *)self->_messenger);
            beMessenger_AppendInt((beMessenger *)self->_messenger, eBindTime);
            break; }
        case FIGHTCOM_E2PATKDWNTIME: {
            eAtkMode = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
            if (eAtkMode == 0) {
                eAtkInternedMode = (char *)(0);
            } else {
                eAtkInternedMode = (char *)StringPool_Intern((StringPool *)StringPool_GetInstance(), eAtkMode);
            }
            { StringRef mode((char *)(eAtkInternedMode));
            eAtkPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            eAtkEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            eAtkAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            eAtkPlayer = (void *)MessageAccess::Player(self, eAtkPlayerIndex);
            eAtkAttackNo = eAtkAttackId % 10000;
            if (strcmp(mode.p, "TIME") == 0) {
                eAtkEffectName = (char *)(beDataBase_GetRecordString((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eAtkAttackNo, "KOUKA"));
                eAtkTime = 0;
                if (strcmp(eAtkEffectName, "freeze") == 0) {
                    eAtkRank = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eAtkAttackNo, "KOUKARANK");
                    eAtkEnemyIntelligence = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), eAtkEnemyRecNo, "KASHIKOSA");
                    eAtkSpirit = (igProperty_GetRecord((igObject *)eAtkPlayer, "SEISHIN"))->_data;
                    eAtkRoll = MessageAccess::Random(self)->genrand() % 10000U;
                    eAtkChanceBase = (((int) (eAtkEnemyIntelligence * 3) / (int) eAtkSpirit) + 0x64) - ((int) eAtkSpirit / 40);
                    int rec_scaled = (int) (eAtkRank * 0xA0) / 100;
                    if ((int) eAtkRoll < (rec_scaled * eAtkChanceBase)) {
                        eAtkBaseTime = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eAtkAttackNo, "KOUKATIME");
                        eAtkTime = (int)((int) (eAtkBaseTime * eAtkChanceBase) / 100);
                    }
                    if (eAtkTime == 0) {
                        eAtkTime = -1;
                    }
                }
                beMessenger_ClearInt((beMessenger *)self->_messenger);
                beMessenger_AppendInt((beMessenger *)self->_messenger, eAtkTime);
            } else {
                if (strcmp(mode.p, "SUBAYASA") == 0) {
                    eAtkDownList = (void *)(beNDMWGameRam_beDataObjIntList_GetData((int *)igProperty_GetRecordIntList((igObject *)eAtkPlayer, "DOWNDATA")));
                    eAtkDownCount = ((igIntList *)eAtkDownList)->_count;
                    IntListSet((igIntList *)eAtkDownList, 0, 0);
                    beNDMWGameRam_RecomputeStats(self, eAtkPlayerIndex, 1);
                    eAtkSpeedRank = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eAtkAttackNo, "KOUKARANK");
                    eAtkSpeedEnemyIntelligence = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), eAtkEnemyRecNo, "KASHIKOSA");
                    eAtkSpeedSpirit = (igProperty_GetRecord((igObject *)eAtkPlayer, "SEISHIN"));
                    eAtkSpeedPenalty = (eAtkSpeedRank + ((int) ((int) (eAtkSpeedEnemyIntelligence * 0x96) / (int) eAtkSpeedSpirit->_data) / 100)) - ((int) eAtkSpeedSpirit->_data / 80);
                    if (eAtkSpeedPenalty < 0x14) {
                        eAtkSpeedPenalty = 0x14;
                    }
                    if (eAtkSpeedPenalty > 0x50) {
                        eAtkSpeedPenalty = 0x50;
                    }
                    int eAtkSpeed = (igProperty_GetRecord((igObject *)eAtkPlayer, "SUBAYASA"))->_data;
                    beMessenger_ClearInt((beMessenger *)self->_messenger);
                    beMessenger_AppendInt((beMessenger *)self->_messenger, (int) (eAtkSpeed * eAtkSpeedPenalty) / 100);
                } else {
                    if (strcmp(mode.p, "MEICHURITSU") == 0) {
                        eAtkAccList = (void *)(beNDMWGameRam_beDataObjIntList_GetData((int *)igProperty_GetRecordIntList((igObject *)eAtkPlayer, "DOWNDATA")));
                        eAtkAccCount = ((igIntList *)eAtkAccList)->_count;
                        IntListSet((igIntList *)eAtkAccList, 1, 0);
                        beNDMWGameRam_RecomputeStats(self, eAtkPlayerIndex, 1);
                        eAtkAccRank = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), eAtkAttackNo, "KOUKARANK");
                        eAtkAccEnemyIntelligence = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), eAtkEnemyRecNo, "KASHIKOSA");
                        eAtkAccSpirit = (igProperty_GetRecord((igObject *)eAtkPlayer, "SEISHIN"));
                        eAtkAccPenalty = (eAtkAccRank + ((int) ((int) (eAtkAccEnemyIntelligence * 0x96) / (int) eAtkAccSpirit->_data) / 100)) - ((int) eAtkAccSpirit->_data / 80);
                        if (eAtkAccPenalty < 0x14) {
                            eAtkAccPenalty = 0x14;
                        }
                        if (eAtkAccPenalty > 0x50) {
                            eAtkAccPenalty = 0x50;
                        }
                        int eAtkAccuracy = (igProperty_GetRecord((igObject *)eAtkPlayer, "MEICHURITSU"))->_data;
                        beMessenger_ClearInt((beMessenger *)self->_messenger);
                        beMessenger_AppendInt((beMessenger *)self->_messenger, (int) (eAtkAccuracy * eAtkAccPenalty) / 100);
                    }
                }
            }
            }
            break; }
        case FIGHTCOM_E2PPOWDWNTIME: {
            ePowMode = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
            if (ePowMode == 0) {
                ePowInternedMode = (char *)(0);
            } else {
                ePowInternedMode = (char *)StringPool_Intern((StringPool *)StringPool_GetInstance(), ePowMode);
            }
            { StringRef mode((char *)(ePowInternedMode));
            ePowPlayerIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            ePowEnemyRecNo = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            ePowAttackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            ePowPlayer = (void *)MessageAccess::Player(self, ePowPlayerIndex);
            ePowAttackNo = ePowAttackId % 10000;
            if (strcmp(mode.p, "TIME") == 0) {
                ePowEffectName = (char *)(beDataBase_GetRecordString((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), ePowAttackNo, "KOUKA"));
                ePowTime = 0;
                if (strcmp(ePowEffectName, "powerdown") == 0) {
                    ePowRank = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), ePowAttackNo, "KOUKARANK");
                    ePowEnemyIntelligence = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), ePowEnemyRecNo, "KASHIKOSA");
                    ePowSpirit = (igProperty_GetRecord((igObject *)ePowPlayer, "SEISHIN"))->_data;
                    ePowRoll = MessageAccess::Random(self)->genrand() % 10000U;
                    ePowChanceBase = (((int) (ePowEnemyIntelligence * 3) / (int) ePowSpirit) + 0x64) - ((int) ePowSpirit / 40);
                    int rec_scaled = (int) (ePowRank * 0xA0) / 100;
                    if ((int) ePowRoll < (rec_scaled * ePowChanceBase)) {
                        ePowBaseTime = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), ePowAttackNo, "KOUKATIME");
                        ePowTime = (int)((int) (ePowBaseTime * ePowChanceBase) / 100);
                    }
                    if (ePowTime == 0) {
                        ePowTime = -1;
                    }
                }
                beMessenger_ClearInt((beMessenger *)self->_messenger);
                beMessenger_AppendInt((beMessenger *)self->_messenger, ePowTime);
            } else {
                if (strcmp(mode.p, "TSUYOSA") == 0) {
                    ePowStrList = (void *)(beNDMWGameRam_beDataObjIntList_GetData((int *)igProperty_GetRecordIntList((igObject *)ePowPlayer, "DOWNDATA")));
                    ePowStrCount = ((igIntList *)ePowStrList)->_count;
                    IntListSet((igIntList *)ePowStrList, 4, 0);
                    beNDMWGameRam_RecomputeStats(self, ePowPlayerIndex, 1);
                    ePowStrRank = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), ePowAttackNo, "KOUKARANK");
                    ePowStrEnemyIntelligence = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), ePowEnemyRecNo, "KASHIKOSA");
                    ePowStrSpirit = (igProperty_GetRecord((igObject *)ePowPlayer, "SEISHIN"));
                    ePowStrPenalty = (ePowStrRank + ((int) ((int) (ePowStrEnemyIntelligence * 0x96) / (int) ePowStrSpirit->_data) / 100)) - ((int) ePowStrSpirit->_data / 80);
                    if (ePowStrPenalty < 0x14) {
                        ePowStrPenalty = 0x14;
                    }
                    if (ePowStrPenalty > 0x50) {
                        ePowStrPenalty = 0x50;
                    }
                    int ePowStrength = (igProperty_GetRecord((igObject *)ePowPlayer, "TSUYOSA"))->_data;
                    beMessenger_ClearInt((beMessenger *)self->_messenger);
                    beMessenger_AppendInt((beMessenger *)self->_messenger, (int) (ePowStrength * ePowStrPenalty) / 100);
                } else {
                    if (strcmp(mode.p, "MAMORI") == 0) {
                        ePowDefList = (void *)(beNDMWGameRam_beDataObjIntList_GetData((int *)igProperty_GetRecordIntList((igObject *)ePowPlayer, "DOWNDATA")));
                        ePowDefCount = ((igIntList *)ePowDefList)->_count;
                        IntListSet((igIntList *)ePowDefList, 5, 0);
                        beNDMWGameRam_RecomputeStats(self, ePowPlayerIndex, 1);
                        ePowDefRank = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Eneatk(self, "eneatk")), ePowAttackNo, "KOUKARANK");
                        ePowDefEnemyIntelligence = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::Enemy(self, "enemy")), ePowEnemyRecNo, "KASHIKOSA");
                        ePowDefSpirit = (igProperty_GetRecord((igObject *)ePowPlayer, "SEISHIN"));
                        ePowDefPenalty = (ePowDefRank + ((int) ((int) (ePowDefEnemyIntelligence * 0x96) / (int) ePowDefSpirit->_data) / 100)) - ((int) ePowDefSpirit->_data / 80);
                        if (ePowDefPenalty < 0x14) {
                            ePowDefPenalty = 0x14;
                        }
                        if (ePowDefPenalty > 0x50) {
                            ePowDefPenalty = 0x50;
                        }
                        int ePowDefense = (igProperty_GetRecord((igObject *)ePowPlayer, "MAMORI"))->_data;
                        beMessenger_ClearInt((beMessenger *)self->_messenger);
                        beMessenger_AppendInt((beMessenger *)self->_messenger, (int) (ePowDefense * ePowDefPenalty) / 100);
                    }
                }
            }
            }
            break; }
        case FIGHTCOM_P2PKOUKAMAGIC:
            casterIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            targetIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            attackId = beMessenger_GetInt((beMessenger *)self->_messenger, 2);
            magicPlayer = (void *)MessageAccess::Player(self, casterIndex);
            if (casterIndex == targetIndex) {
                techniqueNo = attackId % 10000;
                if (techniqueNo == 40 || techniqueNo == 45) {
                    int techniqueRow;
                    beNDMWGameRam_FindTechniqueRow(self, magicPlayer, techniqueNo, &techniqueRow);
                    healSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SKILL");
                    if (healSkillNo != 8) {
                        if (healSkillNo != 7) {
                            healListDefault = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)magicPlayer, "SKILL"));
                            healValuesDefault = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)healListDefault)->_data));
                            healDataDefault = beNDMWLoadIntf2_igIntList_GetData((igDataList *)healValuesDefault);
                            healSkill = *(int *)(healDataDefault + (healSkillNo * 4));
                        } else {
                            healList7 = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)magicPlayer, "SKILL"));
                            healValues7 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)healList7)->_data));
                            healData7 = beNDMWLoadIntf2_igIntList_GetData((igDataList *)healValues7);
                            healSkill = ((int *)healData7)[7];
                        }
                    } else {
                        healList8 = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)magicPlayer, "SKILL"));
                        healValues8 = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)healList8)->_data));
                        healData8 = beNDMWLoadIntf2_igIntList_GetData((igDataList *)healValues8);
                        healSkill = ((int *)healData8)[8];
                    }
                    healBaseHp = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "HP");
                    int pre_sum = healBaseHp + healSkill;
                    healAmount = pre_sum + (igProperty_GetRecord((igObject *)magicPlayer, "KASHIKOSA"))->_data;
                    beNDMWGameRam_ChangeHp(self, casterIndex, healAmount, -1);
                    if (techniqueNo == 0x2D) {
                        beMessenger_SendNamed((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)magicPlayer, "DIGIMONNAME"))->_data), casterIndex, GETMATRIX);
                        beMessenger_GetMatrix(&healMatrix, (beMessenger *)self->_messenger, 0);
                        igMatrix44f_GetTranslation((const float *)&healMatrix, (float *)&healCenter);
                        { NearbyListRef nearby = beNDMWGameRam_CollectNearbyNonzeroHp(self, "PLAYER", casterIndex, &healCenter);
                        healCount = ((igIntList *)nearby.value)->_count;
                        for (healLoop = 0; healLoop < healCount; ++healLoop) {
                                healListData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)nearby.value);
                                healTarget = ((int *)healListData)[healLoop];
                                beNDMWGameRam_ChangeHp(self, healTarget, healAmount, -1);
                                beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)((void *)MessageAccess::Player(self, healTarget)), "DIGIMONNAME"))->_data), healTarget);
                                beMessenger_AppendString((beMessenger *)self->_messenger, "x_250healhit00");
                                beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_HEALEFONLY");
                                beMessenger_AppendFloat((beMessenger *)self->_messenger, 1.0f);
                                Vec3f_Copy(&healEffectOffset, &g_vec3Zero);
                                beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&healEffectOffset);
                                beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                                beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETEFFECT", 1);
                        }
                        }
                    }
                } else if (techniqueNo == 55 || techniqueNo == 60) {
                    int techniqueRow;
                    beNDMWGameRam_FindTechniqueRow(self, magicPlayer, techniqueNo, &techniqueRow);
                    cureSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SKILL");
                    switch (cureSkillNo) { default: beNDMWLoadIntf2_igIntList_GetData((igDataList *)(void *)beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)igProperty_GetRecordIntList((igObject *)magicPlayer, "SKILL"))->_data)); break; case 7: beNDMWLoadIntf2_igIntList_GetData((igDataList *)(void *)beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)igProperty_GetRecordIntList((igObject *)magicPlayer, "SKILL"))->_data)); break; case 8: beNDMWLoadIntf2_igIntList_GetData((igDataList *)(void *)beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)igProperty_GetRecordIntList((igObject *)magicPlayer, "SKILL"))->_data)); break; }
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)magicPlayer, "DIGIMONNAME"))->_data), casterIndex, "GETPEBASEWORK");
                    cureOwner = (void *)(beMessenger_GetObject((beMessenger *)self->_messenger, 0));
                    cureWork = (void *)(beMessenger_GetObject((beMessenger *)self->_messenger, 1));
                    if (beNDMWMdlPEBaseInfoWork_IsPoisoned((beNDMWMdlPEBaseInfoWork *)cureWork) != 0) {
                        cureChance = ((techniqueRow - techniqueNo) + 5) - ((beNDMWMdlPEBaseInfoWork *)cureWork)->_poisonEndurance;
                        cureRoll = MessageAccess::Random(self)->genrand() % 10U;
                        if (cureChance >= (int) cureRoll) {
                            beNDMWMdlPEBaseInfoWork_CurePoison((beNDMWMdlPEBaseInfoWork *)cureWork, (beBaseInfoRam *)cureOwner);
                        }
                    }
                    if (techniqueNo == 0x3C) {
                        beMessenger_SendNamed((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)magicPlayer, "DIGIMONNAME"))->_data), casterIndex, GETMATRIX);
                        beMessenger_GetMatrix(&cureMatrix, (beMessenger *)self->_messenger, 0);
                        igMatrix44f_GetTranslation((const float *)&cureMatrix, (float *)&cureCenter);
                        { NearbyListRef nearby = beNDMWGameRam_CollectNearbyNonzeroHp(self, "PLAYER", casterIndex, &cureCenter);
                        cureCount = ((igIntList *)nearby.value)->_count;
                        int cureCountCopy = cureCount;
                        for (cureLoop = 0; cureLoop < cureCountCopy; ++cureLoop) {
                                cureListData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)nearby.value);
                                cureTarget = ((int *)cureListData)[cureLoop];
                                cureLoopPlayer = (void *)MessageAccess::Player(self, cureTarget);
                                beMessenger_SendNamed((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)cureLoopPlayer, "DIGIMONNAME"))->_data), cureTarget, "GETPEBASEWORK");
                                cureLoopOwner = (void *)(beMessenger_GetObject((beMessenger *)self->_messenger, 0));
                                cureLoopWork = (void *)(beMessenger_GetObject((beMessenger *)self->_messenger, 1));
                                if (beNDMWMdlPEBaseInfoWork_IsPoisoned((beNDMWMdlPEBaseInfoWork *)cureLoopWork) != 0) {
                                    cureLoopChance = ((techniqueRow - techniqueNo) + 5) - ((beNDMWMdlPEBaseInfoWork *)cureLoopWork)->_poisonEndurance;
                                    cureLoopRoll = MessageAccess::Random(self)->genrand() % 10U;
                                    if (cureLoopChance >= (int) cureLoopRoll) {
                                        beNDMWMdlPEBaseInfoWork_CurePoison((beNDMWMdlPEBaseInfoWork *)cureLoopWork, (beBaseInfoRam *)cureLoopOwner);
                                    }
                                }
                                beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)cureLoopPlayer, "DIGIMONNAME"))->_data), cureTarget);
                                beMessenger_AppendString((beMessenger *)self->_messenger, "x_250curehit00");
                                beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_CUREEFONLY");
                                beMessenger_AppendFloat((beMessenger *)self->_messenger, 1.0f);
                                Vec3f_Copy(&cureEffectOffset, &g_vec3Zero);
                                beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&cureEffectOffset);
                                beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                                beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETEFFECT", 1);
                        }
                        }
                    }
                } else if (techniqueNo == 50 || techniqueNo == -50) {
                    if (techniqueNo >= 0) {
                        int techniqueRow;
                        beNDMWGameRam_FindTechniqueRow(self, magicPlayer, techniqueNo, &techniqueRow);
                        /* the raise techniques' rows start at 50 */
                        raiseFirst = g_raiseFirstValue[techniqueRow - 50];
                        raiseSecondValue = g_raiseSecondValue[techniqueRow - 50];
                    } else {
                        raiseFirst = g_raiseFirstValue[0];
                        raiseSecondValue = g_raiseSecondValue[0];
                    }
                    igMatrix44f_SetIdentity((float *)&raiseMatrix);
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)magicPlayer, "DIGIMONNAME"))->_data), casterIndex, GETMATRIX);
                    beMessenger_GetMatrix(&raiseSourceMatrix, (beMessenger *)self->_messenger, 0);
                    igMatrix44f_Copy((float *)&raiseMatrix, (const float *)&raiseSourceMatrix);
                    igMatrix44f_GetTranslation((const float *)&raiseMatrix, (float *)&raiseCenter);
                    { NearbyListRef nearby = beNDMWGameRam_CollectNearbyNonzeroHp(self, "PLAYER2", -1, &raiseCenter);
                    raiseCount = ((igIntList *)nearby.value)->_count;
                    for (raiseLoop = 0; raiseLoop < raiseCount; ++raiseLoop) {
                            raiseListData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)nearby.value);
                            beMessenger_SelectReceivers((beMessenger *)self->_messenger, "PLAYER2", 0, ((int *)raiseListData)[raiseLoop]);
                            beMessenger_AppendMatrix((beMessenger *)self->_messenger, &raiseMatrix);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, raiseFirst);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, raiseSecondValue);
                            beMessenger_DispatchSelected((beMessenger *)self->_messenger, (const char *)"RAISE");
                    }
                    }
                } else if (techniqueNo == 65) {
                    int techniqueRow;
                    beNDMWGameRam_FindTechniqueRow(self, magicPlayer, techniqueNo, &techniqueRow);
                    speedSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SKILL");
                    speedIntelligence = (igProperty_GetRecord((igObject *)magicPlayer, "KASHIKOSA"))->_data;
                    speedTimeBase = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "TIME");
                    int speedDuration = speedTimeBase + speedIntelligence;
                    speedSkillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)magicPlayer, "SKILL"));
                    speedSkillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)speedSkillList)->_data));
                    speedSkillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)speedSkillValues);
                    speedSkill = *(int *)(speedSkillData + (speedSkillNo * 4));
                    speedTechSpeed = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SUBAYASA");
                    int speedBoost = ((int) speedSkill / 5) + speedTechSpeed;
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)magicPlayer, "DIGIMONNAME"))->_data), casterIndex, GETMATRIX);
                    beMessenger_GetMatrix(&speedMatrix, (beMessenger *)self->_messenger, 0);
                    igMatrix44f_GetTranslation((const float *)&speedMatrix, (float *)&speedCenter);
                    { NearbyListRef nearby = beNDMWGameRam_CollectNearbyNonzeroHp(self, "PLAYER", casterIndex, &speedCenter);
                    speedTargetList = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Deref((int *)&nearby.value));
                    IntListAppend::append(speedTargetList, casterIndex);
                    speedCount = ((igIntList *)nearby.value)->_count;
                    int speedCountCopy = speedCount;
                    for (speedLoop = 0; speedLoop < speedCountCopy; ++speedLoop) {
                            speedListData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)nearby.value);
                            speedTarget = ((int *)speedListData)[speedLoop];
                            speedTargetPlayer = (void *)MessageAccess::Player(self, speedTarget);
                            speedCrit = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "CHIMEIRITSU");
                            speedParalysis = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "MHIRITSU");
                            speedEvade = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "KAIHIRITSU");
                            beMessenger_PushArgContext((beMessenger *)self->_messenger);
                            beMessenger_SelectReceivers((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)speedTargetPlayer, "DIGIMONNAME"))->_data), speedTarget);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, speedDuration);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, speedBoost);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, speedCrit);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, speedParalysis);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, speedEvade);
                            beMessenger_DispatchSelected((beMessenger *)self->_messenger, (const char *)"SETSPEEDUP");
                            if (speedTarget != casterIndex) {
                                beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)speedTargetPlayer, "DIGIMONNAME"))->_data), speedTarget);
                                beMessenger_AppendString((beMessenger *)self->_messenger, "x_250uphit00");
                                beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_UPEFONLY");
                                beMessenger_AppendFloat((beMessenger *)self->_messenger, 1.0f);
                                Vec3f_Copy(&speedEffectOffset, &g_vec3Zero);
                                beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&speedEffectOffset);
                                beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                                beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETEFFECT", 1);
                            }
                            beMessenger_PopArgContext((beMessenger *)self->_messenger);
                    }
                    }
                } else if (techniqueNo == 80) {
                    int techniqueRow;
                    beNDMWGameRam_FindTechniqueRow(self, magicPlayer, techniqueNo, &techniqueRow);
                    powerIntelligence = (igProperty_GetRecord((igObject *)magicPlayer, "KASHIKOSA"))->_data;
                    powerTimeBase = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "TIME");
                    int powerDuration = powerTimeBase + powerIntelligence;
                    powerSkillNo = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "SKILL");
                    powerSkillList = (int)((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)magicPlayer, "SKILL"));
                    powerSkillValues = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Get(&((beDataObjIntList *)powerSkillList)->_data));
                    powerSkillData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)powerSkillValues);
                    powerSkill = *(int *)(powerSkillData + (powerSkillNo * 4));
                    powerTechTable = MessageDatabases::PcTech(self);
                    powerSkillBonus = (int)((int) powerSkill / 5);
                    powerMaxHp = beDataBase_GetRecordInt((beDataBase *)powerTechTable, techniqueRow, "MAXHP");
                    int powerMaxHpBonus = powerSkillBonus + powerMaxHp;
                    powerStrength = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "TSUYOSA");
                    int powerStrengthBonus = powerSkillBonus + powerStrength;
                    powerDefense = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "MAMORI");
                    int powerDefenseBonus = powerSkillBonus + powerDefense;
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)magicPlayer, "DIGIMONNAME"))->_data), casterIndex, GETMATRIX);
                    beMessenger_GetMatrix(&powerMatrix, (beMessenger *)self->_messenger, 0);
                    igMatrix44f_GetTranslation((const float *)&powerMatrix, (float *)&powerCenter);
                    { NearbyListRef nearby = beNDMWGameRam_CollectNearbyNonzeroHp(self, "PLAYER", casterIndex, &powerCenter);
                    powerTargetList = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Deref((int *)&nearby.value));
                    IntListAppend::append(powerTargetList, casterIndex);
                    powerCount = ((igIntList *)nearby.value)->_count;
                    for (powerLoop = 0; powerLoop < powerCount; ++powerLoop) {
                            powerListData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)nearby.value);
                            powerTarget = ((int *)powerListData)[powerLoop];
                            powerTargetPlayer = (void *)MessageAccess::Player(self, powerTarget);
                            beMessenger_PushArgContext((beMessenger *)self->_messenger);
                            beMessenger_SelectReceivers((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)powerTargetPlayer, "DIGIMONNAME"))->_data), powerTarget);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, powerDuration);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, powerStrengthBonus);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, powerDefenseBonus);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, powerMaxHpBonus);
                            beMessenger_DispatchSelected((beMessenger *)self->_messenger, (const char *)"SETPOWERUP");
                            if (powerTarget != casterIndex) {
                                beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)powerTargetPlayer, "DIGIMONNAME"))->_data), powerTarget);
                                beMessenger_AppendString((beMessenger *)self->_messenger, "x_250uphit00");
                                beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_UPEFONLY");
                                beMessenger_AppendFloat((beMessenger *)self->_messenger, 1.0f);
                                Vec3f_Copy(&powerEffectOffset, &g_vec3Zero);
                                beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&powerEffectOffset);
                                beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                                beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETEFFECT", 1);
                            }
                            beMessenger_PopArgContext((beMessenger *)self->_messenger);
                    }
                    }
                } else if (techniqueNo == 75) {
                    int techniqueRow;
                    beNDMWGameRam_FindTechniqueRow(self, magicPlayer, techniqueNo, &techniqueRow);
                    refractTime = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "TIME");
                    int refractFire = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "FIRE");
                    int refractIce = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "ICE");
                    int refractThunder = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "THUNDER");
                    refractDark = beDataBase_GetRecordInt((beDataBase *)(MessageDatabases::PcTech(self)), techniqueRow, "DARK");
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)magicPlayer, "DIGIMONNAME"))->_data), casterIndex, GETMATRIX);
                    beMessenger_GetMatrix(&refractMatrix, (beMessenger *)self->_messenger, 0);
                    igMatrix44f_GetTranslation((const float *)&refractMatrix, (float *)&refractCenter);
                    { NearbyListRef nearby = beNDMWGameRam_CollectNearbyNonzeroHp(self, "PLAYER", casterIndex, &refractCenter);
                    refractTargetList = (void *)(beNDMWGameRam_igSmartPointer_igIntList_Deref((int *)&nearby.value));
                    IntListAppend::append(refractTargetList, casterIndex);
                    refractCount = ((igIntList *)nearby.value)->_count;
                    for (refractLoop = 0; refractLoop < refractCount; ++refractLoop) {
                            refractListData = beNDMWLoadIntf2_igIntList_GetData((igDataList *)nearby.value);
                            refractTarget = ((int *)refractListData)[refractLoop];
                            refractTargetPlayer = (void *)MessageAccess::Player(self, refractTarget);
                            beMessenger_PushArgContext((beMessenger *)self->_messenger);
                            beMessenger_SelectReceivers((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)refractTargetPlayer, "DIGIMONNAME"))->_data), refractTarget);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, refractTime);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, refractFire);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, refractIce);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, refractThunder);
                            beMessenger_AppendInt((beMessenger *)self->_messenger, refractDark);
                            beMessenger_DispatchSelected((beMessenger *)self->_messenger, (const char *)"SETREFRACT");
                            if (refractTarget != casterIndex) {
                                beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "PLAYER", (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)igProperty_GetRecordString((igObject *)refractTargetPlayer, "DIGIMONNAME"))->_data), refractTarget);
                                beMessenger_AppendString((beMessenger *)self->_messenger, "x_250uphit00");
                                beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_UPEFONLY");
                                beMessenger_AppendFloat((beMessenger *)self->_messenger, 1.0f);
                                Vec3f_Copy(&refractEffectOffset, &g_vec3Zero);
                                beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&refractEffectOffset);
                                beMessenger_AppendBool((beMessenger *)self->_messenger, 0U);
                                beMessenger_AppendBool((beMessenger *)self->_messenger, 1U);
                                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETEFFECT", 1);
                            }
                            beMessenger_PopArgContext((beMessenger *)self->_messenger);
                    }
                    }
                }
                beMessenger_ClearInt((beMessenger *)self->_messenger);
                beMessenger_AppendInt((beMessenger *)self->_messenger, 1);
            }
            break;
        }
        }
        return 1;
    }
    case GAMERAM_BKCHIPBITEXP:
        /* Block-local webs are declared in the order player, common, idx; their register ids fix
         * the allocator push order. */
        int chipIndex;
        int savedBit;
        int bitSlot;
        void *bkCommon;
        void *bkPlayer;
        int bkLevel;
        chipIndex = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
                bkCommon = (void *)(beNDMWGameRam_igSmartPointer_beDataObjList_Get(&self->_commonDataList));
                playerList = (void *)(beNDMWGameRam_igSmartPointer_beDataObjListList_Get(&self->_playerDataListList));
        bkPlayer = (void *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)playerList, chipIndex);
                digimonNameProp = (igProperty_GetRecordString((igObject *)bkPlayer, "DIGIMONNAME"));
        chipName = (const char *)beNDMWGameRam_igStringRef_Get(&((beDataObjString *)digimonNameProp)->_data);
        StringListStore::SetAt((igStringRefList *)beNDMWGameRam_beDataObjStringList_GetData((int *)(igProperty_GetRecordStringList((igObject *)bkCommon, "BKCHIPNAME"))), chipIndex, StringRef(chipName == 0 ? (char *)0 : (char *)StringPool_Intern((StringPool *)StringPool_GetInstance(), chipName)));
        bitSlot = chipIndex * 2;
        bitProp = (igProperty_GetRecord((igObject *)bkPlayer, "BIT"));
        savedBit = bitProp->_data;
        chipDataProp = ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)bkCommon, "BKCHIPDATA"));
        chipDataList = (igIntList *)beNDMWGameRam_beDataObjIntList_GetData((int *)chipDataProp);
        chipDataCount = chipDataList->_count;
        if ((chipDataCount != 0) && (bitSlot >= 0) && (bitSlot < chipDataCount)) {
            chipDataBuffer = (int *)beNDMWLoadIntf2_igIntList_GetData((igDataList *)chipDataList);
            chipDataBuffer[bitSlot] = savedBit;
        }
        bitResetProp = (igProperty_GetRecord((igObject *)bkPlayer, "BIT"));
        bitResetProp->_data = 0;
        expSlot = bitSlot + 1;
        levelProp = (igProperty_GetRecord((igObject *)bkPlayer, "LEVEL"));
        bkLevel = levelProp->_data;
        if ((bkLevel != 0x3E7) && (bkLevel != 1)) {
            expProp = (igProperty_GetRecord((igObject *)bkPlayer, "EXP"));
            currentExp = expProp->_data;
            /* experience at the start of a level: 200 per level below it plus (level + 139) per square of those levels */
            levelBaseExp = (bkLevel - 1) * 200 + (bkLevel + 139) * ((bkLevel - 1) * (bkLevel - 1));
            newExp = currentExp - ((levelBaseExp - ((bkLevel - 2) * 200 + (bkLevel - 1 + 139) * ((bkLevel - 2) * (bkLevel - 2)))) * 2) / 10;
            if (newExp < levelBaseExp) {
                newExp = levelBaseExp;
            }
            int expLost = currentExp - newExp;
            chipDataExpProp = ((IntValuesProperty *)igProperty_GetRecordIntList((igObject *)bkCommon, "BKCHIPDATA"));
            chipDataExpList = (igIntList *)beNDMWGameRam_beDataObjIntList_GetData((int *)chipDataExpProp);
            int chipDataExpCount = chipDataExpList->_count;
            if ((chipDataExpCount != 0) && (expSlot >= 0) && (expSlot < chipDataExpCount)) {
                chipDataExpBuffer = (int *)beNDMWLoadIntf2_igIntList_GetData((igDataList *)chipDataExpList);
                chipDataExpBuffer[expSlot] = expLost;
            }
            expWriteProp = (igProperty_GetRecord((igObject *)bkPlayer, "EXP"));
            expWriteProp->_data = newExp;
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
    return ((beDataObjInt *)p)->_data;
}

int beNDMWGameRam_igSmartPointer_igIntList_Deref(int *p)
{
    return *p;
}

int beNDMWGameRam_beModelCtrlMoveObjectList_Get(igDataList *list, int index) {
    return *(int *)(list->_data + (index * 4));
}

int beNDMWGameRam_igSmartPointer_beModelCtrlMoveObjectList_Get(int *p)
{
    return *p;
}

int beNDMWGameRam_igSmartPointer_beModelCtrlInfoWork_Get(int *p)
{
    return *p;
}

int *beNDMWGameRam_CreateDataListRef(int *ref, int *allocator) {
    *ref = (int)beBaseInfoDataList_Create(*allocator);
    return ref;
}

int beNDMWGameRam_beDataObjIntList_GetData(int *p)
{
    return ((beDataObjInt *)p)->_data;
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
            igObject_Destroy((igObject *)outgoing);
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
    List_RemoveWordAt((igDataList *)list, index);
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

    if (g_stringPool == 0) {
        pool = (int)StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = (int)StringPool_Construct((StringPool *)pool);
        }
        g_stringPool = (StringPool *)pool;
    }
    return (int)g_stringPool;
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
    return (int)g_beNDMWGameRam_metaObject;
}

int beNDMWGameRam_GetInfoMeta(void) {
    return 0;
}

#pragma pop
