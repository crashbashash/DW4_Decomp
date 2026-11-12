#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
#define RELEASE_REF(T, q) { T *rr = (q); if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }
#define ALLOC(var) { void *got = ((void *)igObject_GetAllocator(arg0)); if (GPR_00554c14) var = got; else var = ((void *)Memory_GetAllocatorBySelector(DAT_00587108[0])); }
#define RESERVE(LT, h, SZ) { LT *l = (LT *)(h)->_data; if (!(e->count < l->_count)) List_Reserve(l, e->count, SZ); }
#define RESIZE(LT, h, SZ) { int n = e->count; LT *l = (LT *)(h)->_data; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize(l, n, SZ); } }
#define A_(x) (x)
#define RELO(X) { igObject *q = (X); if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7fffff) == 0) igObject_Destroy(q); } }
#define PROP_DIGIMONNO       ((char *)DAT_00518848)
#define PROP_SKILL           ((char *)DAT_00518860)
#define PROP_TSUYOSA         DAT_005188b0
#define PROP_POWERPOCKET     ((char *)DAT_00518a40)
#define PROP_POWERSOCKET     ((char *)DAT_00518a88)
#define PROP_POWERSOCKETNAME DAT_00518aa0
#define PROP_MODEL           DAT_00518c08
#define PROP_SPECIES_MASK    DAT_00518c10
#define PROP_NEEDSKILL       DAT_00518c18
#define NO_ABSOLUTE_HP (-1)
#define SHINKA(g) StatHelpers::shinka(g)
#define SHINKA_3fa850(g) StatHelpers_3fa850::shinka(g)
#define NEARBY_RADIUS_SQUARED 900.0f
#define REFERENCE_COUNT_MASK 0x7fffffULL
#define PROP_LEVEL           DAT_00518858
#define PROP_UPCNT           DAT_00518868
#define PROP_HP              DAT_00518890
#define PROP_MHP             DAT_00518898
#define PROP_MP              DAT_005188a0
#define PROP_MMP             DAT_005188a8
#define PROP_MAMORI          DAT_005188b8
#define PROP_KASHIKOSA       DAT_005188c0
#define PROP_SEISHIN         DAT_005188d0
#define PROP_SUBAYASA        DAT_005188d8
#define PROP_HONOOTEIKO      DAT_005188e8
#define PROP_KOORITEIKO      DAT_005188f8
#define PROP_KAMINARITEIKO   DAT_00518908
#define PROP_YAMITEIKO       DAT_00518918
#define PROP_WAZALIST        DAT_00518928
#define PROP_NEXTEXP         DAT_00518938
#define PROP_ATTACKDELAY     DAT_00518940
#define PROP_MEICHURITSU     DAT_00518950
#define PROP_CHIMEIRITSU     DAT_00518960
#define PROP_MAHIRITSU       DAT_00518970
#define PROP_KAIHIRITSU      DAT_00518980
#define PROP_BOUGYORITSU     DAT_00518990
#define PROP_MAHITEIKOU      DAT_005189a0
#define PROP_DOKUTEIKOU      DAT_005189b0
#define PROP_BITRITSU        DAT_005189c0
#define PROP_EXPRITSU        DAT_005189d0
#define PROP_LUCKRITSU       DAT_005189e0
#define PROP_ATTACKZOKUSEI   DAT_005189f0
#define PROP_HPDRAIN         DAT_00518a00
#define PROP_MPDRAIN         DAT_00518a08
#define PROP_CHOHATURITSU    DAT_00518a10
#define PROP_WEAPONRECNO     DAT_00518a20
#define PROP_WEAPONSKILLNO   DAT_00518a30
#define PROP_POWERPOCKET_3fab90     ((char *)DAT_00518ab0)
#define PROP_UPDATA          DAT_00518b70
#define PROP_DOWNDATA        DAT_00518b78
#define PROP_MAXHP           DAT_00518fc8
#define PROP_MAXMP           DAT_00518fd0
#define PROP_RES_FIRE        DAT_00518fd8
#define PROP_RES_ICE         DAT_00518fe8
#define PROP_RES_THUNDER     DAT_00518ff0
#define PROP_RES_DARK        DAT_00519000
#define PROP_DELAY           DAT_00519010
#define PROP_ZOKUSEI         DAT_00519018
#define SHINKA_3fab90(g) StatHelpers_3fab90::shinka(g)
#define PCTECH(g) StatHelpers_3fab90::pctech(g)
#define RELEASE(o) StatHelpers_3fab90::release_ref(o)
#define CLAMP_ATTR(v) if ((v) <= 0) (v) = 1; if ((v) > 9999) (v) = 9999;

class StringRef;
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
extern "C" void *FUN_00364220(void *);
extern "C" void *FUN_003644f0(void *);
extern "C" void *FUN_003647c0(void *);
extern "C" void *FUN_00364a90(void *);
extern "C" void *FUN_00364d30(void *);
extern "C" void *FUN_00365000(void *);
extern "C" void *FUN_00365240(void *);
extern "C" void *FUN_00365510(void *);
extern "C" void FUN_003f6620(void *arg0, void *arg1, void *arg2);
extern "C" void * igProperty_GetRecordFolder(...);
extern "C" void * igProperty_GetRecordArray(...);
extern "C" void Gap__Bec__beNDMWGameRam__vfunc_31(void);
extern "C" int Gap__Bec__beNDMWGameRam__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWGameRam__vfunc_30(void);
extern "C" int FUN_002eb010(int);
extern "C" int StringPool_Construct(int);
extern "C" char * StringPool_Intern(...);
extern "C" char * beDataBase_GetRecordString(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" void *FUN_003c8c90(int);
extern "C" int FUN_004482c0(void *, int, int, int);
extern "C" int beDataBase_GetRecordInt(...);
extern "C" int beNDMWItemBase_GetRecordInt(...);
extern "C" const char * beNDMWItemBase_GetRecordString(...);
extern "C" int FUN_00236f80(int, int);
extern "C" int FUN_003a9340(int, char *);
extern "C" void beMessenger_SelectReceivers(int, const char *, const char *, int);
extern "C" void beMessenger_AppendFloat(int, float);
extern "C" void beMessenger_AppendInt(int, int);
extern "C" void beMessenger_DispatchSelected(int, const char *);
extern "C" void FUN_003f9f80(int arg0, int arg1, int *arg2, const char *arg3, int arg4);
extern "C" void FUN_003fa040(int arg0, int arg1, int *arg2, const char *arg3);
extern "C" void FUN_003fa1e0(int arg0, int arg1, int *arg2, const char *arg3);
extern "C" int strcmp(...);
extern "C" void FUN_003fa2c0(int arg0, int arg1, int *arg2, const char *arg3, int arg4);
extern "C" void beMessenger_SendGroup(int,const char *,const char *);
extern "C" int beMessenger_GetIntCount(int);
extern "C" int beMessenger_GetInt(int,int);
extern "C" void beMessenger_PushArgContext(int);
extern "C" void beMessenger_SetRunCheck(int,unsigned char);
extern "C" void beMessenger_PopArgContext(int);
extern "C" int FUN_00406db0(int *p);
extern "C" int FUN_00406dc0(int *p);
extern "C" int FUN_00406df0(int *p);
extern "C" int FUN_00406e00(int *p);
extern "C" int beBaseInfoDataList_Create(int);
extern "C" int *FUN_00406e10(int *arg0, int *arg1);
extern "C" int FUN_00406e40(int *p);
extern "C" int FUN_00406e50(int *p);
extern "C" int FUN_00406ee0(int *p);
extern "C" int FUN_00406ef0(int *p);
extern "C" int FUN_00406f10(int *p);
extern "C" void List_RemoveWordAt(void);
extern "C" void FUN_00406f20(void);
extern "C" void FUN_00406f40(int a0, int a1);
extern "C" void FUN_00406f50(int a0, int a1);
extern "C" void FUN_00406f60(int a0, int a1);
extern "C" void FUN_00406f70(int a0, int a1);
extern "C" int FUN_00406f80(int *p);
extern "C" void FUN_00406fa0(void **arg0);
extern "C" int StringPool_GetInstance(void);
extern "C" int FUN_00407030(int *p);
extern "C" int FUN_00407040(int *p);
extern "C" int FUN_00407050(int *p);
extern "C" int DAT_00587108[4];
extern "C" int DAT_004cf100[4];
extern "C" unsigned char GPR_00554c14;
extern "C" unsigned char GPR_005549e4;
struct Entry { unsigned type; int count; int name; };
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(int s) : p((char *)s) {}
    StringRef(const char *s) : p((char *)s) {}
    StringRef(void *s) : p((char *)s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
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
extern "C" igObject *FUN_00364050(int);
extern "C" igObject *FUN_003c85b0(int);
extern "C" int FUN_00448710(igObject *, int);
extern "C" int DAT_004ced40[4];
extern "C" int DAT_004cedf0[4];
extern "C" int DAT_004cf110[4];
extern "C" int DAT_004cf118[4];
extern "C" int DAT_00518a50[4];
extern "C" int DAT_00518ae8[4];
extern "C" int DAT_00518b30[4];
extern "C" int DAT_00518b50[4];
extern "C" unsigned char GPR_005549e8;
/* Owning stack reference to one new item record, released at the end of each loop pass. */
class ItemRef {
public:
    igObject *p;
    ItemRef(igObject *o) : p(o) {}
    ~ItemRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void FUN_003f7310(beNDMWGameRam *arg0, int arg1);
extern "C" igObject *FUN_00363e80(int);
extern "C" int Gap__Core__igObject__vfunc_23(beNDMWGameRam *);
/* matching construct: inline release helper reproduces the retail release sequence */
struct ReleaseRef { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* Owning stack reference to the new common data list, released on scope exit (reference count in
 * the low 23 bits of _refCount). */

/* Owning stack reference to the new per-player data-list list, released the same way. */
class PlayerDataListListRef {
public:
    igObject *p;
    PlayerDataListListRef(igObject *o) : p(o) {}
    ~PlayerDataListListRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void Gap__Bec__beNDMWGameRam__vfunc_23(beNDMWGameRam *arg0);
/* reference-counted engine object header: refcount word at +4 */
typedef struct RefCountedHeader { int p0; unsigned refs; } RefCountedHeader;
/* Object-reference list header: count at +8, capacity at +12, buffer at +16. */
typedef struct ObjectRefList { char p[8]; int count; int cap; RefCountedHeader **data; } ObjectRefList;
extern "C" void Gap__Bec__beNDMWGameRam__vfunc_24(beNDMWGameRam *arg0);
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
extern "C" void Gap__Bec__beNDMWGameRam__vfunc_32(beNDMWGameRam *arg0);
extern "C" beNDMWGameRamInfo *FUN_003ca380(int);
extern "C" beNDMWGameRamInfoRam *FUN_003ca1a0(int);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, beNDMWGameRamInfoRam *, int *);
extern "C" int DAT_00518bb8[4];
extern "C" int DAT_00518bc0[4];
extern "C" int DAT_00587110[4];
/* Owning stack reference to the game-ram info created here, released on scope exit (reference
 * count in the low 23 bits of _refCount). */

/* Owning stack reference to the info's ram object created here, released on scope exit. */
class RamRef {
public:
    beNDMWGameRamInfoRam *p;
    RamRef(beNDMWGameRamInfoRam *o) : p(o) {}
    ~RamRef() { beNDMWGameRamInfoRam *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" int Gap__Bec__beNDMWGameRam__vfunc_25(beNDMWGameRam *arg0);
extern "C" int g_beNDMWGameRam_metaObject[4];
extern "C" int DAT_00518bc8[4];
extern "C" int DAT_00519420[4];
extern "C" int DAT_00519430[4];
extern "C" int DAT_00519438[4];
extern "C" int DAT_00586f20[4];
struct R { int w0; int rc; };
extern "C" int FUN_003f80e0(beNDMWGameRam *arg0, int arg1);
typedef struct PropertyRecord { char header[12]; void *value; } PropertyRecord;
extern "C" PropertyRecord *FUN_003a92e0(int, void *);
extern "C" igObject * beMessenger_GetObject(...);
extern "C" int DAT_00518798[4];
extern "C" int DAT_005187a0[4];
extern "C" int DAT_005187b0[4];
extern "C" int DAT_00518848[4];
extern "C" char DAT_00518858[];
extern "C" int DAT_00518860[4];
extern "C" char DAT_00518868[];
extern "C" int DAT_00518870[4];
extern "C" int DAT_00518880[4];
extern "C" int DAT_00518b00[4];
extern "C" int DAT_00518b10[4];
extern "C" int DAT_00518b40[4];
extern "C" char DAT_00518b60[];
extern "C" void FUN_003f82a0(beNDMWGameRam *arg0, int arg1, int arg2);
/* Current player record -> BASE_* save arrays. Mirror of the post-load BASE -> current mapping:
 * LEVEL and EXP go to the species' slot of BASE_LEVEL / BASE_EXP, SKILL[9] and UPCNT[11] to
 * BASE_SKILL[species * 9 + i] / BASE_UPCNT[species * 11 + i]. Every store is bounds-checked
 * against the destination list's count, like an inlined igIntList set. The declaration order
 * preserves the original register allocation. */

/* Property record as returned by igProperty_GetRecord: scalar value at +12. */

typedef struct PropertyRecord_3f8760 {
    char pad[12];
    int value;
} PropertyRecord_3f8760;
/* Same record layout for list-valued properties: igIntList pointer at +12. */
typedef struct PropertyIntArray {
    char pad[12];
    igIntList *list;
} PropertyIntArray;
extern "C" const char DIGIMONNO_2[];
extern "C" const char LEVEL_2[];
extern "C" const char SKILL[];
extern "C" const char UPCNT[];
extern "C" const char EXP[];
extern "C" const char BASE_LEVEL[];
extern "C" const char BASE_EXP[];
extern "C" const char BASE_SKILL[];
extern "C" const char BASE_UPCNT[];
extern "C" void FUN_003f8760(beNDMWGameRam *self, int player_index);
extern "C" int DAT_004cf120[4];
extern "C" int DAT_00518a40[4];
struct RC { int p0; unsigned refs; };
struct Rec { char p[12]; int f12; };
struct RecL { char p[12]; igObjectList *f12; };
struct RecoveryTarget { int word0; int references;
 static void release(RecoveryTarget *object) {
  if(object) {
   --object->references;
   if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
    igObject_Destroy(object);
  }
 }
};
template<int I> class RecoveryRef { public:
 void *value;
 RecoveryRef(void *p, bool retain):value(p) { }
 ~RecoveryRef() { RecoveryTarget::release((RecoveryTarget *)value); }
};
extern "C" void FUN_003f8990(beNDMWGameRam *arg0, int arg1);
extern "C" char DAT_005188b0[];
extern "C" int DAT_00518a88[4];
extern "C" char DAT_00518aa0[];
extern "C" char DAT_00518c08[];
extern "C" char DAT_00518c10[];
extern "C" char DAT_00518c18[];
struct IntRec { char pad[12]; int value; };
struct BonusRec { char pad[12]; igIntList *obj; };
struct ListHolder { char pad[12]; igObjectList *list; };
struct StrListHolder { char pad[12]; igStringRefList *list; };
extern "C" IntRec * igProperty_GetRecord(...);
extern "C" StrListHolder *FUN_003a9310(void *, const char *);
extern "C" int StringList_AppendRetained(int, const StringRef &);
extern "C" void FUN_003f8c90(beNDMWGameRam *self, int index, int apply);
typedef struct Rec_3f93c0 { int w0; int w4; int w8; int w12; } Rec_3f93c0;
extern "C" int FUN_003f93c0(beNDMWGameRam *arg0, int arg1, int arg2);
struct Rb { char pad[12]; unsigned char b; };
struct Ri { char pad[12]; int n; };
struct Ra { char pad[12]; igDataList *a; };
extern "C" struct Rb *igProperty_GetRecordByte(int, int *);
extern "C" int DAT_00518760[4];
extern "C" int DAT_00518888[4];
extern "C" int DAT_00518b20[4];
extern "C" unsigned char GPR_005549ec;
extern "C" void FUN_003f9570(beNDMWGameRam *arg0, int arg1, int arg2);
struct W { char pad[12]; igObjectList *f12; };
extern "C" int FUN_00382eb0(beUnicodeObj **, int, int);
extern "C" int beUnicodeObj_AllocateBuffer(beUnicodeObj *, int);
extern "C" beUnicodeObj *FUN_003614f0(int);
extern "C" char DAT_00518828[];
extern "C" int DAT_00589678[4];
extern "C" void FUN_003f96e0(beNDMWGameRam *arg0, int arg1, void *arg2, int *arg3);
extern "C" void FUN_003f99f0(beNDMWGameRam *arg0, int arg1, void *arg2, int *arg3);
extern "C" void FUN_003f9bb0(beNDMWGameRam *arg0, int arg1);
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
extern "C" int FUN_003f9c80(beNDMWGameRam *self, int player_index, int delta, int absolute);
extern "C" void FUN_003f9e20(beNDMWGameRam *self, int player_index, int delta);
/* `0 < cnt` gives the slt/beqz head. */


struct R_3fa040 { char pad[12]; igObjectList *f12; };
extern "C" int DAT_00518ab0[4];
/* The flat field is const: its read is created before the *out reload so the register colouring puts
 * the field in a0 and the running total in v1. */


struct BonusItem { char pad[20]; const int flat; };
struct BonusFolder { char pad[12]; igObjectList *list; };
extern "C" int DAT_00518ac0[4];
extern "C" void FUN_003fa120(beNDMWGameRam *gameram, void *player, int *out, const char *name, int with_flat);
struct F { char pad[12]; igObjectList *list; };
extern "C" int DAT_00518ad0[4];
struct ListHolder_3fa2c0 { int pad[3]; igObjectList *list; };
extern "C" int DAT_00518ae0[4];
extern "C" int DAT_00518c88[4];
struct beNDMWItemCountView { beNDMWItemBase base; unsigned int _count; };
typedef igObject Ref;
struct BonusObj { char pad[16]; int *v; };
struct BonusRec_3fa3b0 { char pad[12]; BonusObj *obj; };
extern "C" char DAT_00518c98[];
extern "C" char DAT_00518ca0[];
extern "C" char DAT_00518cb0[];
extern "C" char DAT_00518cb8[];
extern "C" int DAT_004cf130[];
extern "C" int DAT_004cf160[];
extern "C" int DAT_004cf190[];
extern "C" int DAT_004cf1c0[];
extern "C" BonusRec_3fa3b0 * FUN_003a9250(...);
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
            beMessenger_SendNamed(g->_messenger, ((char *)DAT_00519438), ((char *)DAT_00519430), 0, ((char *)DAT_00519420));
            fetched = ((Ref *)beMessenger_GetObject(g->_messenger, 0));
            if (fetched) ++fetched->_refCount;
            release_ref((Ref *)g->_dBShinka);
            g->_dBShinka = (int)fetched;
        }
        return (Ref *)g->_dBShinka;
    }
};
extern "C" int FUN_003fa3b0(beNDMWGameRam *arg0, int arg1, int arg2, int arg3);
extern "C" int DAT_004cf1f0[];
extern "C" int DAT_004cf220[];
extern "C" const char *DAT_004cf250[];
extern "C" const char *DAT_004cf270[];
struct StatHelpers_3fa850 {
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
            beMessenger_SendNamed(g->_messenger, ((char *)DAT_00519438), ((char *)DAT_00519430), 0, ((char *)DAT_00519420));
            fetched = beMessenger_GetObject(g->_messenger, 0);
            if (fetched) ++fetched->_refCount;
            release_ref((igObject *)g->_dBShinka);
            g->_dBShinka = (int)fetched;
        }
        return (igObject *)g->_dBShinka;
    }
};
extern "C" int FUN_003fa850(beNDMWGameRam *arg0, int arg1, int arg2, int arg3);
/* Recomputes one player's derived stats; `apply` says whether the equipment, chip and skill
 * modifiers are applied on top of the database/UPDATA/DOWNDATA base values. MHP/MMP are clamped to
 * 99999 and the attributes and element resistances to 1..9999. The player pointer and the
 * DIGIMONNO / LEVEL reads go through the tiny inline accessors StatHelpers::GetPlayer() and
 * GetProp(), whose result temporaries are created late so the register colouring comes out right;
 * locals are declared where they are first set, one variable per loop; the two threshold tests are
 * written `record <= value` and the delay clamp as `> 70` to keep the compare in `at`. */
/* Nearby-query object and its emitted deleting destructor. The stat recompute uses the same stack-
 * resident reference class, so both functions share its single emitted destructor. */

struct Vec3 { float x,y,z; };
struct Mat44 { float m[16]; };
struct IntList { int vtable_word, reference_word; int count; int capacity; int *data;
    int getCount() const { return count; } };
extern "C" IntList *FUN_002caa70(int);
extern "C" void beMessenger_GetMatrix(Mat44 *,int,int);
extern "C" void Matrix44_GetTranslation(const Mat44 *,Vec3 *);
extern "C" char GETMATRIX[];
extern "C" char GETHP[];
extern "C" int g_defaultAllocatorSelector[4];
/* Stack-resident counted reference to an IntList (the low 23 bits of the reference
 * word are the count; the object is destroyed when the last reference goes). */
class NearbyListRef;
class IntListRef {
public:
    IntList *value;
    IntListRef(IntList *p):value(p) {}
    IntListRef(const NearbyListRef &p);
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
/* The query's own working reference. Its destructor is a separate copy from that of the by-value
 * IntListRef result handed back to the caller. */
class NearbyListRef {
public:
    IntList *value;
    NearbyListRef(IntList *p):value(p) {}
    ~NearbyListRef() {
        IntList *object=value;
        if(object) {
            --object->reference_word;
            if (((unsigned long long)(long long)object->reference_word & REFERENCE_COUNT_MASK)==0)
                igObject_Destroy(object);
        }
    }
};
extern "C" IntListRef beNDMWGameRam_CollectNearbyNonzeroHp(beNDMWGameRam *self,const char *group,int excluded,const Vec3 *center);
extern "C" char DAT_00518890[];
extern "C" char DAT_00518898[];
extern "C" char DAT_005188a0[];
extern "C" char DAT_005188a8[];
extern "C" char DAT_005188b8[];
extern "C" char DAT_005188c0[];
extern "C" char DAT_005188d0[];
extern "C" char DAT_005188d8[];
extern "C" char DAT_005188e8[];
extern "C" char DAT_005188f8[];
extern "C" char DAT_00518908[];
extern "C" char DAT_00518918[];
extern "C" char DAT_00518928[];
extern "C" char DAT_00518938[];
extern "C" char DAT_00518940[];
extern "C" char DAT_00518950[];
extern "C" char DAT_00518960[];
extern "C" char DAT_00518970[];
extern "C" char DAT_00518980[];
extern "C" char DAT_00518990[];
extern "C" char DAT_005189a0[];
extern "C" char DAT_005189b0[];
extern "C" char DAT_005189c0[];
extern "C" char DAT_005189d0[];
extern "C" char DAT_005189e0[];
extern "C" char DAT_005189f0[];
extern "C" char DAT_00518a00[];
extern "C" char DAT_00518a08[];
extern "C" char DAT_00518a10[];
extern "C" char DAT_00518a20[];
extern "C" char DAT_00518a30[];
extern "C" char DAT_00518b70[];
extern "C" char DAT_00518b78[];
extern "C" char DAT_00518fc8[];
extern "C" char DAT_00518fd0[];
extern "C" char DAT_00518fd8[];
extern "C" char DAT_00518fe8[];
extern "C" char DAT_00518ff0[];
extern "C" char DAT_00519000[];
extern "C" char DAT_00519010[];
extern "C" char DAT_00519018[];
extern "C" char DAT_00519448[];
extern "C" char DAT_00519458[];
extern "C" char DAT_00519460[];
extern "C" void FUN_00448f30(igObject *, int, int);
extern "C" igObject *FUN_003c8040(int);
extern "C" const char *DAT_004cf290[6];
extern "C" const char *DAT_004cf2b0[6];
extern "C" const char *DAT_004cf2d0[6][5];
extern "C" const char *DAT_004cf350[4];
/* The helpers are static members so a split of the unit at its top-level definitions keeps them. */
struct StatHelpers_3fab90 {
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
            beMessenger_SendNamed(g->_messenger, ((char *)DAT_00519438), ((char *)DAT_00519430), 0, ((char *)DAT_00519420));
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
            beMessenger_SendNamed(g->_messenger, DAT_00519460, DAT_00519458, 0, DAT_00519448);
            fetched = beMessenger_GetObject(g->_messenger, 0);
            if (fetched) ++fetched->_refCount;
            release_ref((igObject *)g->_dBPcTech);
            g->_dBPcTech = (int)fetched;
        }
        return (igObject *)g->_dBPcTech;
    }

    static inline int select_allocator(int fallback)
    {
        if (GPR_00554c14) return fallback;
        else return Memory_GetAllocatorBySelector(DAT_00587108[0]);
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
extern "C" void FUN_003fab90(beNDMWGameRam *self, int index, unsigned char apply);
/* WAZALIST base number -> current database row. Declaration order preserves the loop register
 * allocation. The unused receiver occupies a0. A miss leaves output unchanged. */


/* Only the property record's +12 value is declared here. */

typedef struct TechniqueListProperty {
    char pad[12];
    igObjectList *list;
} TechniqueListProperty;
extern "C" const char WAZALIST[16];
extern "C" void beNDMWGameRam_FindTechniqueRow(beNDMWGameRam *receiver, void *player, int base_no, int *output);
extern "C" int FUN_00406da0(igDataList *p);
extern "C" int FUN_00406dd0(beNDMWGameRam *arg0, int arg1);
/* Only the object prefix used here is declared. */

typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
extern "C" ObjectRefTarget **ObjectRef_AssignObject_00406e60(ObjectRefTarget **destination,ObjectRefTarget *incoming);
extern "C" int FUN_00406f00(igUnsignedCharList *p);
extern "C" int FUN_00406f90(beDataObjInt *p);
extern "C" int g_stringPool[4];

static inline int countOf(const igObjectList *l) { return l->_count; }

void FUN_003f6620(void *arg0, void *arg1, void *arg2)
{
    igObjectList *out = (igObjectList *)arg1;
    int n1;
    int i1;
    int n5;
    int **d5;
    int i5;
    Entry *e = (Entry *)arg2;
    unsigned char done = 0;
    void *alloc;

    do {
        switch (e->type + 1) {
        case 1: {
            ALLOC(alloc)
            igSmartPointer<beDataObjInt> s0((beDataObjInt *)FUN_00365510(alloc));
            igNamedObject_SetName(s0.p, e->name);
            ObjectList_AppendRetained(out, s0.p);
            break;
        }
        case 2: {
            ALLOC(alloc)
            igSmartPointer<beDataObjIntList> s1((beDataObjIntList *)FUN_00365240(alloc));
            igNamedObject_SetName(s1.p, e->name);
            RESERVE(igIntList, s1.p, 4)
            RESIZE(igIntList, s1.p, 4)
            {
                igIntList *l1 = (igIntList *)s1.p->_data;
                n1 = l1->_count;
                int *d1 = (int *)l1->_data;
                for (i1 = 0; i1 < n1; i1++) d1[i1] = DAT_004cf100[0];
            }
            ObjectList_AppendRetained(out, s1.p);
            break;
        }
        case 3: {
            ALLOC(alloc)
            igSmartPointer<beDataObjBool> s2((beDataObjBool *)FUN_00365000(alloc));
            igNamedObject_SetName(s2.p, e->name);
            ObjectList_AppendRetained(out, s2.p);
            break;
        }
        case 4: {
            ALLOC(alloc)
            igSmartPointer<beDataObjBoolList> s3((beDataObjBoolList *)FUN_00364d30(alloc));
            igNamedObject_SetName(s3.p, e->name);
            RESERVE(igBoolList, s3.p, 1)
            RESIZE(igBoolList, s3.p, 1)
            {
                igBoolList *l3 = (igBoolList *)s3.p->_data;
                int n3 = l3->_count;
                unsigned char *d3 = (unsigned char *)l3->_data;
                for (int i3 = 0; i3 < n3; i3++) d3[i3] = GPR_005549e4;
            }
            ObjectList_AppendRetained(out, s3.p);
            break;
        }
        case 5: {
            ALLOC(alloc)
            igSmartPointer<beDataObjString> s4((beDataObjString *)FUN_00364a90(alloc));
            igNamedObject_SetName(s4.p, e->name);
            ObjectList_AppendRetained(out, s4.p);
            break;
        }
        case 6: {
            ALLOC(alloc)
            igSmartPointer<beDataObjStringList> s5((beDataObjStringList *)FUN_003647c0(alloc));
            igNamedObject_SetName(s5.p, e->name);
            RESERVE(igStringRefList, s5.p, 4)
            StringList_Resize((void *)s5.p->_data, e->count);
            Fill::emptyStrings(s5.p, StringRef(0), n5, d5, i5);
            ObjectList_AppendRetained(out, s5.p);
            break;
        }
        case 7: {
            ALLOC(alloc)
            igSmartPointer<beDataObjObjectList> s6((beDataObjObjectList *)FUN_003644f0(alloc));
            igNamedObject_SetName(s6.p, e->name);
            RESERVE(igObjectList, s6.p, 4)
            ObjectList_ResizeRetained((void *)s6.p->_data, e->count);
            ObjectList_FillRetained((void *)s6.p->_data, 0);
            ObjectList_AppendRetained(out, s6.p);
            break;
        }
        case 8: {
            ALLOC(alloc)
            igSmartPointer<beDataObjFloatList> s7((beDataObjFloatList *)FUN_00364220(alloc));
            igNamedObject_SetName(s7.p, e->name);
            RESERVE(igFloatList, s7.p, 4)
            RESIZE(igFloatList, s7.p, 4)
            {
                igFloatList *l7 = (igFloatList *)s7.p->_data;
                int n7 = l7->_count;
                float *d7 = (float *)l7->_data;
                for (int i7 = 0; i7 < n7; i7++) d7[i7] = *(float *)&DAT_004cf100[2];
            }
            ObjectList_AppendRetained(out, s7.p);
            break;
        }
        case 0:
            done = 1;
            break;
        }
        e++;
    } while (done == 0);
    {
        int n = out->_count;
        if (!(n < countOf(out))) List_Reserve(out, n, 4);
    }
}

/* Owning stack reference to the new player data object, released on scope exit (reference count in
 * the low 23 bits of _refCount). */
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

void FUN_003f7310(beNDMWGameRam *arg0, int arg1) {
    igObjectList *common;
    igObjectList *ta;
    igObjectList *players;
    igObjectList *recs;
    igObjectList *arr;
    igObject *o;
    igObject *s1;
    igObject *s2;
    igObjectList *pl;
    int n, a, m, b, c, d, e, f, v; igObject *p7; int cn;
    int a0, a1;
    if (arg1 == 0) {
        common = (igObjectList *)arg0->_commonDataList;
        n = common->_count;
        for (a = 0; a < n; a++) {
            o = ((igObject **)common->_data)[a];
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
            }
        }
        m = common->_count;
        for (b = 0; b < m; b++) ((int *)common->_data)[b] = 0;
        common->_count = 0;
        FUN_003f6620((void *)arg0, (void *)arg0->_commonDataList, (void *)(&DAT_004ced40[0]));
    }
    players = (igObjectList *)arg0->_playerDataListList;
    if (players->_count != 4) {
        if (count(players) < 5) List_Reserve(players, 4, 4);
        ObjectList_ResizeRetained(arg0->_playerDataListList, 4);
    }
    a0 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        a0 = (int)a0;
    } else {
        a0 = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    igSmartPointer<igObject> data(FUN_00364050(a0));
    FUN_003f6620((void *)arg0, data.p, (void *)(&DAT_004cedf0[0]));
    for (c = 0; c < 16; c++) {
        recs = (igObjectList *)((igObject **)((void *)FUN_003a9250(data.p, &DAT_00518b30[0])))[3];
        if (recs->_count != 0 && c >= 0 && c < recs->_count)
            ((int *)recs->_data)[c] = DAT_004cf110[0];
    }
    for (d = 0; d < 16; d++) {
        for (e = 0; e < 9; e++) {
            arr = (igObjectList *)((igObject **)((void *)FUN_003a9250(data.p, &DAT_00518b50[0])))[3];
            v = e + d * 9;
            if (arr->_count != 0 && v >= 0 && v < arr->_count)
                ((int *)arr->_data)[v] = DAT_004cf118[0];
        }
    }
    for (f = 0; f < 12; f++) {
        a1 = igObject_GetAllocator(arg0);
        if (GPR_00554c14 != 0) {
            a1 = (int)a1;
        } else {
            a1 = Memory_GetAllocatorBySelector(DAT_00587108[0]);
        }
        ItemRef item(FUN_003c85b0(a1));
        FUN_00448710(item.p, f);
        p7 = data.p;
        s1 = item.p;
        igObject **folder = (igObject **)igProperty_GetRecordFolder(p7, &DAT_00518a50[0]);
        ObjectList_AppendRetained(folder[3], s1);
    }
    ta = (igObjectList *)((igObject **)igProperty_GetRecordArray(data.p, &DAT_00518ae8[0]))[3];
    if (ta->_count != 0) {
        if (ta->_count > 960)
            ((unsigned char *)ta->_data)[960] = GPR_005549e8;
    }
    storePlayerData(arg0, arg1, data);
}

void Gap__Bec__beNDMWGameRam__vfunc_23(beNDMWGameRam *arg0) {
    int var_s0;
    int var_v0;
    int var_v0_2;
    igObject *s0;

    Gap__Core__igObject__vfunc_23(arg0);
    var_v0 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0 = (int)var_v0;
    } else {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    {
        /* The new list is owned by the stack reference while it is retained into the field and the old
         * list is released; the reference's own release runs at the block end. */
        igSmartPointer<igObject> common(FUN_00364050(var_v0));
        s0 = common.p;
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        ReleaseRef::go((igObject *)arg0->_commonDataList);
        arg0->_commonDataList = (int)s0;
    }
    var_v0_2 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0_2 = (int)var_v0_2;
    } else {
        var_v0_2 = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    {
        PlayerDataListListRef players(FUN_00363e80(var_v0_2));
        s0 = players.p;
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        ReleaseRef::go((igObject *)arg0->_playerDataListList);
        arg0->_playerDataListList = (int)s0;
    }
    var_s0 = 0;
    do {
        FUN_003f7310(arg0, var_s0);
        var_s0 += 1;
    } while (var_s0 < 4);
}

void Gap__Bec__beNDMWGameRam__vfunc_24(beNDMWGameRam *arg0) {
    RefCountedHeader *r;
    ObjectRefList *l;
    int n;
    int i;
    int off;
    int n3;
    int i3;
    RefCountedHeader *r2;
    ObjectRefList *l2;
    int nb;
    int ib;
    int offb;
    int n3b;
    int i3b;
    i = 0;
    l = (ObjectRefList *)arg0->_commonDataList;
    n = l->count;
    if (0 < n) {
        off = 0;
        do {
            r = *(RefCountedHeader **)((char *)l->data + off);
            if (r != 0) {
                r->refs--;
                if (!(r->refs & 0x7fffff)) igObject_Destroy(r);
            }
            i += 1;
            off += 4;
        } while (i < n);
    }
    n3 = l->count;
    for (i3 = 0; i3 < n3; i3++) {
        l->data[i3] = 0;
    }
    l->count = 0;
    if (!(0 < ((ObjectRefList *)arg0->_commonDataList)->count)) List_Reserve(arg0->_commonDataList, 0, 4);
    l2 = (ObjectRefList *)arg0->_playerDataListList;
    nb = l2->count;
    ib = 0;
    if (0 < nb) {
        offb = 0;
        do {
            r2 = *(RefCountedHeader **)((char *)l2->data + offb);
            if (r2 != 0) {
                r2->refs--;
                if (!(r2->refs & 0x7fffff)) igObject_Destroy(r2);
            }
            ib += 1;
            offb += 4;
        } while (ib < nb);
    }
    n3b = l2->count;
    for (i3b = 0; i3b < n3b; i3b++) {
        l2->data[i3b] = 0;
    }
    l2->count = 0;
    if (!(0 < ((ObjectRefList *)arg0->_playerDataListList)->count)) List_Reserve(arg0->_playerDataListList, 0, 4);
}

void Gap__Bec__beNDMWGameRam__vfunc_32(beNDMWGameRam *arg0) {
    RefRelease::rel(arg0->_dBShinka);
    RefRelease::rel(arg0->_dBPcTech);
    RefRelease::rel(arg0->_dBWeapon);
    RefRelease::rel(arg0->_dBArmor1);
    RefRelease::rel(arg0->_dBArmor2);
    RefRelease::rel(arg0->_dBAbChip);
    RefRelease::rel(arg0->_dBEnemy);
    RefRelease::rel(arg0->_dBEneatk);
}

int Gap__Bec__beNDMWGameRam__vfunc_25(beNDMWGameRam *arg0) {
    beBaseInfoList *infos;
    beBaseInfoRamList *rams;
    int var_v0;
    beNDMWGameRamInfoRam *n;
    infos = (beBaseInfoList *)arg0->_infoList;
    if (infos->_count == 0) {
        var_v0 = igObject_GetAllocator(arg0);
        var_v0 = GPR_00554c14 ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igSmartPointer<beNDMWGameRamInfo> info(FUN_003ca380(var_v0));
        var_v0 = igObject_GetAllocator(arg0);
        var_v0 = GPR_00554c14 ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        RamRef ram(FUN_003ca1a0(var_v0));
        igNamedObject_SetName(info.p, &DAT_00518bb8[0]);
        ram.p->_parentInfo = (int)info.p;
        ram.p->_parentManager = (int)arg0;
        n = ram.p;
        n->_st0 = 0;
        n->_st3 = 0;
        n->_st2 = 0;
        n->_st1 = 0;
        ram.p->_ramNo = 0;
        ram.p->_isRun = 1;
        rams = (beBaseInfoRamList *)info.p->_ramList;
        ObjectList_AppendRetained((unsigned)rams, ram.p);
        ObjectList_AppendRetained((unsigned)arg0->_infoList, info.p);
        beMessenger_RegisterReceiverFromInfo(arg0->_messenger, ram.p, &DAT_00518bc0[0]);
    }
    return 0;
}

void Gap__Bec__beNDMWGameRam__vfunc_31(void)
{
}

int FUN_003f80e0(beNDMWGameRam *arg0, int arg1) {
    int s2;
    char *s1;
    int var_v0_2;
    struct R *t;
    struct R *a0;
    char *var_v0;
    if (arg1 == 0) {
        var_v0 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_2 = FUN_002eb010(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            DAT_00586f20[0] = var_v0_2;
        }
        var_v0 = StringPool_Intern(DAT_00586f20[0], arg1);
    }
    StringRef name(var_v0);
    s2 = 0;
    for (;;) {
        s1 = name.p;
        if (arg0->_dBShinka == 0) {
            beMessenger_SendNamed(arg0->_messenger, DAT_00519438, DAT_00519430, 0, DAT_00519420);
            t = (struct R *)beMessenger_GetObject(arg0->_messenger, 0);
            if (t != 0) {
                t->rc = t->rc + 1;
            }
            a0 = (struct R *)arg0->_dBShinka;
            if (a0 != 0) {
                a0->rc = a0->rc - 1;
                if ((a0->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(a0);
                }
            }
            arg0->_dBShinka = (int)t;
        }
        if (beDataBase_GetRecordString(arg0->_dBShinka, s2, DAT_00518bc8) == s1) {
            return s2;
        }
        s2 += 1;
        if (s2 >= 0x10) {
            return 0;
        }
    }
}

/* matching construct: inline release macro with block-local q */

void FUN_003f82a0(beNDMWGameRam *arg0, int arg1, int arg2) {
/* matching construct: local declaration order fixes register allocation */
    int var_s0b;
    igIntList *a0;
    int s4;
    igIntList *a2b;
    igIntList *a0b;
    PropertyRecord *s1c;
    int base9;
    igObject *o;
    int hd;
    int cnt2;
    PropertyRecord *s1b;
    int v0;
    int e1;
    int cnt1;
    igIntList *l1;
    igObject *s0b;
    igIntList *l2;
    int e2;
    PropertyRecord *s1a;
    PropertyRecord *s1;
    igObject *old;
    int base11;
    igObject *s0a;
    igObject *s0c;
    int var_s2;
    int e1L;
    int s0;
    int var_s0;
    igIntList *a2;
    int var_s2b;
    int s1i;
    s4 = A_(((int *)((igIntList *)arg0->_playerDataListList)->_data)[arg1]);
    igProperty_GetRecord(s4, &((int *)DAT_00518858)[0]);
    ((PropertyRecord *)igProperty_GetRecord(s4, &DAT_00518848[0]))->value = (void *)arg2;
    if (arg0->_dBShinka == 0) {
        beMessenger_SendNamed(arg0->_messenger, &DAT_00519438[0], &DAT_00519430[0], 0, &DAT_00519420[0]);
        o = beMessenger_GetObject(arg0->_messenger, 0);
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)arg0->_dBShinka;
        RELO(old)
        arg0->_dBShinka = (int)o;
    }
    s0 = ((int)beDataBase_GetRecordString(arg0->_dBShinka, arg2, &DAT_00518bc8[0]));
    s1 = FUN_003a92e0(s4, &DAT_00518870[0]);
    if (DAT_00586f20[0] == 0) {
        v0 = FUN_002eb010(16);
        if (v0 != 0) v0 = StringPool_Construct(v0);
        DAT_00586f20[0] = v0;
    }
    s1i = ((int)StringPool_Intern(DAT_00586f20[0], s0));
    hd = (int)s1->value;
    if (hd != 0) {
        int *p = (int *)(hd - 8);
        int c = *(int *)(hd - 4) - 1;
        *(int *)(hd - 4) = c;
        if (c == 0) StringChunk_ReleaseHeader(*p, p);
    }
    s1->value = (void *)s1i;
    l1 = (igIntList *)((PropertyRecord *)FUN_003a9250(s4, &DAT_00518b30[0]))->value;
    s0 = arg2 * 4;
    e1 = ((int *)l1->_data)[arg2];
    ((PropertyRecord *)igProperty_GetRecord(s4, &((int *)DAT_00518858)[0]))->value = (void *)e1;
    l2 = (igIntList *)((PropertyRecord *)FUN_003a9250(s4, &DAT_00518b40[0]))->value;
    e2 = ((int *)l2->_data)[arg2];
    ((PropertyRecord *)igProperty_GetRecord(s4, &DAT_00518880[0]))->value = (void *)e2;
    /* matching construct: base9/base11 hoisted into locals, else MWCC strength-reduces the index */
    base9 = arg2 * 9;
    var_s2 = 0;
    var_s0 = 0;
    do {
        a2 = (igIntList *)((PropertyRecord *)FUN_003a9250(s4, &DAT_00518b50[0]))->value;
        e1L = ((int *)a2->_data)[base9 + var_s2];
        a0 = (igIntList *)((PropertyRecord *)FUN_003a9250(s4, &DAT_00518860[0], a2))->value;
        cnt1 = a0->_count;
        if (cnt1 != 0 && var_s2 >= 0 && var_s2 < cnt1) ((int *)(a0->_data + var_s0))[0] = e1L;
        var_s2 += 1;
        var_s0 += 4;
    } while (var_s2 < 9);
    base11 = arg2 * 11;
    var_s2b = 0;
    var_s0b = 0;
    do {
        a2b = (igIntList *)((PropertyRecord *)FUN_003a9250(s4, &((int *)DAT_00518b60)[0]))->value;
        e2 = ((int *)a2b->_data)[base11 + var_s2b];
        a0b = (igIntList *)((PropertyRecord *)FUN_003a9250(s4, &((int *)DAT_00518868)[0], a2b))->value;
        cnt2 = a0b->_count;
        if (cnt2 != 0 && var_s2b >= 0 && var_s2b < cnt2) ((int *)(a0b->_data + var_s0b))[0] = e2;
        var_s2b += 1;
        var_s0b += 4;
    } while (var_s2b < 11);
    if (arg1 == 0) {
        s0a = (igObject *)((PropertyRecord *)igProperty_GetRecordArray(s4, &DAT_00518ae8[0]))->value;
        s1a = ((PropertyRecord *)igProperty_GetRecordArray(arg0->_commonDataList, &DAT_00518798[0]));
        if (s0a != 0) s0a->_refCount = s0a->_refCount + 1;
        old = (igObject *)s1a->value;
        RELO(old)
        s1a->value = s0a;
        s0b = (igObject *)((PropertyRecord *)igProperty_GetRecordArray(s4, &DAT_00518b00[0]))->value;
        s1b = ((PropertyRecord *)igProperty_GetRecordArray(arg0->_commonDataList, &DAT_005187a0[0]));
        if (s0b != 0) s0b->_refCount = s0b->_refCount + 1;
        old = (igObject *)s1b->value;
        RELO(old)
        s1b->value = s0b;
        s0c = (igObject *)((PropertyRecord *)FUN_003a9250(s4, &DAT_00518b10[0]))->value;
        s1c = ((PropertyRecord *)FUN_003a9250(arg0->_commonDataList, &DAT_005187b0[0]));
        if (s0c != 0) s0c->_refCount = s0c->_refCount + 1;
        old = (igObject *)s1c->value;
        RELO(old)
        s1c->value = s0c;
    }
}

/* BASE_UPCNT */

void FUN_003f8760(beNDMWGameRam *self, int player_index)
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
    PropertyIntArray *base_array;

    player_list = (igIntList *)self->_playerDataListList;
    player = ((int *)player_list->_data)[player_index];
    species = ((PropertyRecord_3f8760 *)igProperty_GetRecord(player, DIGIMONNO_2))->value;
    value = ((PropertyRecord_3f8760 *)igProperty_GetRecord(player, LEVEL_2))->value;
    level_list = ((PropertyIntArray *)FUN_003a9250(player, BASE_LEVEL))->list;
    if (level_list->_count != 0 && species >= 0 && species < level_list->_count)
        ((int *)level_list->_data)[species] = value;
    value = ((PropertyRecord_3f8760 *)igProperty_GetRecord(player, EXP))->value;
    exp_list = ((PropertyIntArray *)FUN_003a9250(player, BASE_EXP))->list;
    if (exp_list->_count != 0 && species >= 0 && species < exp_list->_count)
        ((int *)exp_list->_data)[species] = value;
    skill_base = species * 9;
    for (skill_index = 0; skill_index < 9; ++skill_index) {
        skill = ((int *)((PropertyIntArray *)FUN_003a9250(player, SKILL))->list->_data)[skill_index];
        base_array = ((PropertyIntArray *)FUN_003a9250(player, BASE_SKILL));
        if (base_array->list->_count != 0 && skill_base + skill_index >= 0 &&
            skill_base + skill_index < base_array->list->_count)
            ((int *)base_array->list->_data)[skill_base + skill_index] = skill;
    }
    upcnt_base = species * 11;
    for (upcnt_index = 0; upcnt_index < 11; ++upcnt_index) {
        upcnt = ((int *)((PropertyIntArray *)FUN_003a9250(player, UPCNT))->list->_data)[upcnt_index];
        base_array = ((PropertyIntArray *)FUN_003a9250(player, BASE_UPCNT));
        if (base_array->list->_count != 0 && upcnt_base + upcnt_index >= 0 &&
            upcnt_base + upcnt_index < base_array->list->_count)
            ((int *)base_array->list->_data)[upcnt_base + upcnt_index] = upcnt;
    }
}

void FUN_003f8990(beNDMWGameRam *arg0, int arg1) {
    igObjectList *l;
    int n;
    int al;
    void *hv;
    int j;
    RC *t;
    int i;
    int n3;
    RC *o;
    int *pt;
    int i3;
    int obj;
    int s6;
    obj = ((int *)((igObjectList *)arg0->_playerDataListList)->_data)[arg1];
    l = ((RecL *)igProperty_GetRecordFolder(obj, &DAT_00518a40[0]))->f12;
    s6 = ((Rec *)((void *)igProperty_GetRecord(obj, &DAT_00518848[0])))->f12;
    n = l->_count;
    i = 0;
    if (0 < n) {
        do {
            t = ((RC **)l->_data)[i];
            if (t != 0) {
                t->refs--;
                if (!(t->refs & 0x7fffff)) igObject_Destroy(t);
            }
            i += 1;
        } while (i < n);
    }
    n3 = l->_count;
    for (i3 = 0; i3 < n3; i3++) {
        ((int *)l->_data)[i3] = 0;
    }
    l->_count = 0;
    j = 0;
    pt = &DAT_004cf120[0];
    do {
        al = igObject_GetAllocator(arg0);
        al = (GPR_00554c14 != 0) ? al : Memory_GetAllocatorBySelector(DAT_00587108[0]);
        {
        RecoveryRef<1> sp8C(FUN_003c8c90(al), false);
        hv = sp8C.value;
        if (arg0->_dBShinka == 0) {
            beMessenger_SendNamed(arg0->_messenger, &DAT_00519438[0], &DAT_00519430[0], 0, &DAT_00519420[0]);
            o = (RC *)beMessenger_GetObject(arg0->_messenger, 0);
            if (o != 0) {
                o->refs++;
            }
            t = (RC *)arg0->_dBShinka;
            if (t != 0) {
                t->refs--;
                if (!(t->refs & 0x7fffff)) igObject_Destroy(t);
            }
            arg0->_dBShinka = (int)o;
        }
        FUN_004482c0(hv, beDataBase_GetRecordInt((void *)arg0->_dBShinka, s6, *pt), 0, 0);
        ObjectList_AppendRetained(l, sp8C.value);
        }
        j += 1;
        pt += 1;
    } while (j < 3);
}

void FUN_003f8c90(beNDMWGameRam *self, int index, int apply)
{
    void *player = ((void **)((igObjectList *)self->_playerDataListList)->_data)[index];
    igObjectList *pocket = ((ListHolder *)igProperty_GetRecordFolder(player, PROP_POWERPOCKET))->list;

    if ((apply & 0xff) == 0) {
        igObjectList *sockets = ((ListHolder *)igProperty_GetRecordFolder(player, PROP_POWERSOCKET))->list;
        igStringRefList *names = FUN_003a9310(player, PROP_POWERSOCKETNAME)->list;
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
            if (!DAT_00586f20[0]) {
                int pool = FUN_002eb010(16);
                if (pool) pool = StringPool_Construct(pool);
                DAT_00586f20[0] = pool;
            }
            fresh = StringPool_Intern(DAT_00586f20[0], 0);
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
                const char *model = beNDMWItemBase_GetRecordString(item, self, PROP_MODEL);
                char *interned;
                if (!model) {
                    interned = 0;
                } else {
                    if (!DAT_00586f20[0]) {
                        int pool = FUN_002eb010(16);
                        if (pool) pool = StringPool_Construct(pool);
                        DAT_00586f20[0] = pool;
                    }
                    interned = StringPool_Intern(DAT_00586f20[0], model);
                }
                StringList_AppendRetained((int)names, StringRef(interned));
                item->_isEquip = 1;
            }
        }
    } else {
        int species = igProperty_GetRecord(player, PROP_DIGIMONNO)->value;
        int bit;
        igIntList *skills;
        igStringRefList *names;
        int fits, skillNo;
        igObjectList *sockets;
        skills = ((BonusRec *)FUN_003a9250(player, PROP_SKILL))->obj;
        sockets = ((ListHolder *)igProperty_GetRecordFolder(player, PROP_POWERSOCKET))->list;
        names = FUN_003a9310(player, PROP_POWERSOCKETNAME)->list;
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
            if (!DAT_00586f20[0]) {
                int pool = FUN_002eb010(16);
                if (pool) pool = StringPool_Construct(pool);
                DAT_00586f20[0] = pool;
            }
            fresh = StringPool_Intern(DAT_00586f20[0], 0);
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
                fits = bit & beNDMWItemBase_GetRecordInt(item, self, PROP_SPECIES_MASK);
                skillNo = beNDMWItemBase_GetRecordInt(item, self, PROP_SKILL);
                int need = beNDMWItemBase_GetRecordInt(item, self, PROP_NEEDSKILL);
                if (fits != 0 && ((int *)skills->_data)[skillNo] >= need &&
                    (best < 0 || bestValue < beNDMWItemBase_GetRecordInt(item, self, PROP_TSUYOSA))) {
                    bestValue = beNDMWItemBase_GetRecordInt(item, self, PROP_TSUYOSA);
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
            const char *model = beNDMWItemBase_GetRecordString(chosen, self, PROP_MODEL);
            char *interned;
            if (!model) {
                interned = 0;
            } else {
                if (!DAT_00586f20[0]) {
                    int pool = FUN_002eb010(16);
                    if (pool) pool = StringPool_Construct(pool);
                    DAT_00586f20[0] = pool;
                }
                interned = StringPool_Intern(DAT_00586f20[0], model);
            }
            StringList_AppendRetained((int)names, StringRef(interned));
            chosen->_isEquip = 1;
        }
    }
}

int FUN_003f93c0(beNDMWGameRam *arg0, int arg1, int arg2) {
    int obj;
    igObjectList *folder;
    igIntList *tbl;
    int base;
    int mask;
    int n;
    int i;
    obj = ((int *)((igIntList *)arg0->_playerDataListList)->_data)[arg1];
    folder = (igObjectList *)((Rec_3f93c0 *)igProperty_GetRecordFolder(obj, DAT_00518a40))->w12;
    {
    int t = ((Rec_3f93c0 *)igProperty_GetRecord(obj, DAT_00518848))->w12;
    if (t == arg2) {
        tbl = (igIntList *)((Rec_3f93c0 *)FUN_003a9250(obj, DAT_00518860))->w12;
        base = 0;
    } else {
        tbl = (igIntList *)((Rec_3f93c0 *)FUN_003a9250(obj, DAT_00518b50))->w12;
        base = arg2 * 9;
    }
    }
    mask = 1 << arg2;
    n = folder->_count;
    for (i = 0; i < n; i++) {
        Rec_3f93c0 *r = (Rec_3f93c0 *)((int *)folder->_data)[i];
        if (r->w8 == 0) {
            int f = mask & beNDMWItemBase_GetRecordInt(r, arg0, ((int *)DAT_00518c10));
            int idx = beNDMWItemBase_GetRecordInt(r, arg0, DAT_00518860);
            int need = beNDMWItemBase_GetRecordInt(r, arg0, ((int *)DAT_00518c18));
            if (f != 0 && ((int *)tbl->_data)[base + idx] >= need) return 1;
        }
    }
    return 0;
}

void FUN_003f9570(beNDMWGameRam *arg0, int arg1, int arg2) {
    int cnt;
    int i;
    int s1;
    int off;
    int s4;
    int idx;
    igDataList *arr;
    struct Rb *rb;

    s1 = arg0->_commonDataList;
    s4 = ((int *)((igObjectListList *)arg0->_playerDataListList)->_data)[arg1];
    idx = FUN_003f80e0(arg0, arg2);
    FUN_003f82a0(arg0, arg1, idx);
    FUN_003f8990(arg0, arg1);
    FUN_003f8c90(arg0, arg1, 0);
    FUN_003fab90(arg0, arg1, (unsigned char)1);
    rb = igProperty_GetRecordByte(s4, &DAT_00518888[0]);
    rb->b = 1;
    arr = ((struct Ra *)igProperty_GetRecordArray(s4, &DAT_00518b20[0]))->a;
    if (arr->_count != 0 && idx >= 0 && idx < arr->_count) {
        *(char *)(idx + arr->_data) = GPR_005549ec;
    }
    cnt = 0;
    i = 0;
    off = 0;
    do {
        if (igProperty_GetRecordByte(*(int *)(((igObjectListList *)arg0->_playerDataListList)->_data + off), &DAT_00518888[0])->b != 0) {
            cnt += 1;
        }
        i += 1;
        off += 4;
    } while (i < 4);
    ((struct Ri *)igProperty_GetRecord(s1, &DAT_00518760[0]))->n = cnt;
}

/* Owning stack reference to the new name text; released on scope exit, after the name list has
 * retained it (reference count in the low 23 bits of _refCount). */

void FUN_003f96e0(beNDMWGameRam *arg0, int arg1, void *arg2, int *arg3) {
    int s0;
    int al;
    igObjectList *l;
    int n, n2, i, j;
    unsigned short *src;
    unsigned short *base;
    int k;
    unsigned short *dst;
    igObject *p;
    FUN_003f9570(arg0, arg1, (int)arg2);
    s0 = ((int *)(((igObjectList *)arg0->_playerDataListList)->_data))[arg1];
    al = igObject_GetAllocator(arg0);
    al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587108[0]);
    igSmartPointer<beUnicodeObj> rb(FUN_003614f0(al));
    beUnicodeObj_AllocateBuffer(rb.p, 8);
    {
        /* The looked-up name is an out-parameter the lookup retains; it is released by hand rather
         * than by a destructor. */
        beUnicodeObj *ra;
        int sel = *arg3;
        int table = FUN_00236f80(arg0->_insight, DAT_00589678[0]);
        FUN_00382eb0(&ra, table, sel);
        k = 0;
        src = (unsigned short *)ra->_buffer;
        base = (unsigned short *)rb.p->_buffer;
        dst = base;
        for (;;) {
            *dst = *src;
            if (*src == 0) break;
            k++; src++; dst++;
            if (k >= 8) break;
        }
        for (; k < 8; k++) base[k] = 0;
        {
            beUnicodeObj *o;
            if ((o = ra) != 0) {
                --o->_refCount;
                if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
            }
        }
    }
    l = ((W *)igProperty_GetRecordFolder(s0, DAT_00518828))->f12;
    if (countOf(l) != 0) {
        n = l->_count;
        for (i = 0; i < n; i++) {
            p = ((igObject **)l->_data)[i];
            if (p != 0) {
                p->_refCount = p->_refCount - 1;
                if ((p->_refCount & 0x7FFFFF) == 0) igObject_Destroy(p);
            }
        }
        n2 = l->_count;
        for (j = 0; j < n2; j++) ((igObject **)l->_data)[j] = 0;
        l->_count = 0;
    }
    ObjectList_AppendRetained(l, rb.p);
}

void FUN_003f99f0(beNDMWGameRam *arg0, int arg1, void *arg2, int *arg3) {
    igObjectList *l;
    struct W *w;
    int n;
    int n2;
    int i;
    int j;
    igObject *p;

    FUN_003f9570(arg0, arg1, (int)arg2);
    w = (struct W *)FUN_003a9340(((int *)(((igObjectList *)arg0->_playerDataListList)->_data))[arg1], DAT_00518828);
    l = w->f12;
    if (countOf(l) != 0) {
        n = l->_count;
        for (i = 0; i < n; i++) {
            p = ((igObject **)l->_data)[i];
            if (p != 0) {
                p->_refCount = p->_refCount - 1;
                if ((p->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        n2 = l->_count;
        for (j = 0; j < n2; j++) {
            ((igObject **)l->_data)[j] = 0;
        }
        l->_count = 0;
    }
    ObjectList_AppendRetained(l, *arg3);
}

void FUN_003f9bb0(beNDMWGameRam *arg0, int arg1) {
    int cnt;
    int i;
    int s1;
    int off;

    s1 = arg0->_commonDataList;
    igProperty_GetRecordByte(((int *)((igObjectList *)arg0->_playerDataListList)->_data)[arg1], &DAT_00518888[0])->b = 0;
    cnt = 0;
    i = 0;
    off = 0;
    do {
        if (igProperty_GetRecordByte(((int *)(((igObjectList *)arg0->_playerDataListList)->_data + off))[0], &DAT_00518888[0])->b != 0) {
            cnt += 1;
        }
        i += 1;
        off += 4;
    } while (i < 4);
    ((struct Ri *)igProperty_GetRecord(s1, &DAT_00518760[0]))->n = cnt;
}

/* mpnm */

/* Sentinel for the `absolute` argument of the HP update: apply `delta` instead. */


/* HP update. Returns 0 when a delta is applied to a dead player (HP 0), else 1. */
int FUN_003f9c80(beNDMWGameRam *self, int player_index, int delta, int absolute)
{
    int hp;
    int player;
    int max_hp;

    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[player_index];
    max_hp = ((PropertyRecord_3f8760 *)igProperty_GetRecord(player, MHP))->value;
    hp = ((PropertyRecord_3f8760 *)igProperty_GetRecord(player, HP))->value;
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
    ((PropertyRecord_3f8760 *)igProperty_GetRecord(player, HP))->value = hp;
    beMessenger_SelectReceivers(self->_messenger, METERCTRL, hpmt, player_index);
    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)hp / (float)max_hp);
    beMessenger_DispatchSelected(self->_messenger, SETPERCENT);
    beMessenger_SelectReceivers(self->_messenger, NUMBERCTRL, hpnm, player_index);
    beMessenger_AppendInt(self->_messenger, hp);
    beMessenger_DispatchSelected(self->_messenger, SETVALUE);
    return 1;
}

/* MP update by delta. */
void FUN_003f9e20(beNDMWGameRam *self, int player_index, int delta)
{
    int mp;
    int player;
    int max_mp;

    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[player_index];
    max_mp = ((PropertyRecord_3f8760 *)igProperty_GetRecord(player, MMP))->value;
    mp = ((PropertyRecord_3f8760 *)igProperty_GetRecord(player, MP))->value;
    mp += delta;
    if (mp < 0)
        mp = 0;
    if (mp > max_mp)
        mp = max_mp;
    ((PropertyRecord_3f8760 *)igProperty_GetRecord(player, MP))->value = mp;
    beMessenger_SelectReceivers(self->_messenger, METERCTRL, mpmt, player_index);
    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)mp / (float)max_mp);
    beMessenger_DispatchSelected(self->_messenger, SETPERCENT);
    beMessenger_SelectReceivers(self->_messenger, NUMBERCTRL, mpnm, player_index);
    beMessenger_AppendInt(self->_messenger, mp);
    beMessenger_DispatchSelected(self->_messenger, SETVALUE);
}

void FUN_003f9f80(int arg0, int arg1, int *arg2, const char *arg3, int arg4) {
    beNDMWItemRevisionBase *it;
    if (((igObjectList *)((beDataObjObjectList *)igProperty_GetRecordFolder(arg1, &DAT_00518a88[0]))->_data)->_count != 0) {
        it = ((beNDMWItemRevisionBase **)((igObjectList *)((beDataObjObjectList *)igProperty_GetRecordFolder(arg1, &DAT_00518a88[0]))->_data)->_data)[0];
        if (it != 0) {
            *arg2 += beNDMWItemBase_GetRecordInt(it, arg0, arg3);
            if (arg4 != 0) {
                *arg2 += (int)it->_revision;
            }
        }
    }
}

void FUN_003fa040(int arg0, int arg1, int *arg2, const char *arg3) {
    int cnt;
    int a0;
    int i;
    cnt = ((struct R_3fa040 *)igProperty_GetRecordFolder(arg1, &DAT_00518ab0[0]))->f12->_count;
    i = 0;
    if (0 < cnt) {
        do {
            a0 = ((int *)((struct R_3fa040 *)igProperty_GetRecordFolder(arg1, &DAT_00518ab0[0]))->f12->_data)[i];
            if (a0 != 0) {
                *arg2 += beNDMWItemBase_GetRecordInt(a0, arg0, arg3);
            }
            i += 1;
        } while (i < cnt);
    }
}

void FUN_003fa120(beNDMWGameRam *gameram, void *player, int *out, const char *name, int with_flat) {
    beNDMWItemBase *item;
    if (((struct BonusFolder *)igProperty_GetRecordFolder(player, (const char *)&DAT_00518ac0[0]))->list->_count != 0) {
        item = ((beNDMWItemBase **)((struct BonusFolder *)igProperty_GetRecordFolder(player, (const char *)&DAT_00518ac0[0]))->list->_data)[0];
        if (item != 0) {
            *out += beNDMWItemBase_GetRecordInt(item, gameram, name);
            if (with_flat != 0) {
                *out += ((BonusItem *)item)->flat;
            }
        }
    }
}

void FUN_003fa1e0(int arg0, int arg1, int *arg2, const char *arg3) {
    int temp_a0;
    int n;
    int i;
    n = ((struct F *)igProperty_GetRecordFolder(arg1, &DAT_00518ad0[0]))->list->_count;
    for (i = 0; i < n; i++) {
        temp_a0 = ((int *)((struct F *)igProperty_GetRecordFolder(arg1, &DAT_00518ad0[0]))->list->_data)[i];
        if (temp_a0 != 0) {
            *arg2 += beNDMWItemBase_GetRecordInt(temp_a0, arg0, arg3);
        }
    }
}

void FUN_003fa2c0(int arg0, int arg1, int *arg2, const char *arg3, int arg4) {
    beNDMWItemBase *it; int t;
    if (((struct ListHolder_3fa2c0 *)igProperty_GetRecordFolder(arg1, &DAT_00518ae0[0]))->list->_count != 0) {
        it = *(beNDMWItemBase **)((struct ListHolder_3fa2c0 *)igProperty_GetRecordFolder(arg1, &DAT_00518ae0[0]))->list->_data;
        if (it != 0) {
            t = beNDMWItemBase_GetRecordInt(it, arg0, arg3); *arg2 += t;
            if (arg4 != 0 && strcmp(((char *)beNDMWItemBase_GetRecordString(it, arg0, &DAT_00518c88[0])), arg3) == 0) {
                *arg2 += ((beNDMWItemCountView *)it)->_count;
            }
        }
    }
}

int FUN_003fa3b0(beNDMWGameRam *arg0, int arg1, int arg2, int arg3) {
    void *player;
    int rec;
    BonusObj *tbl;
    int base;
    int lvl;
    int s0;
    int mul;
    int p;
    int i;
    int *q;
    int r;
    player = (void *)((int *)((igObjectListList *)arg0->_playerDataListList)->_data)[arg1];
    rec = arg2;
    if (rec < 0) {
        rec = igProperty_GetRecord(player, ((char *)DAT_00518848))->value;
        tbl = FUN_003a9250(player, DAT_00518868)->obj;
        base = 0;
        lvl = igProperty_GetRecord(player, DAT_00518858)->value;
    } else {
        tbl = FUN_003a9250(player, DAT_00518b60)->obj;
        base = rec * 11;
        lvl = FUN_003a9250(player, ((char *)DAT_00518b30))->obj->v[rec];
    }
    if (arg3 != 0) {
        s0 = beDataBase_GetRecordInt(SHINKA(arg0), rec, DAT_00518c98);
        mul = beDataBase_GetRecordInt(SHINKA(arg0), rec, DAT_00518ca0);
        p = tbl->v[base];
    } else {
        s0 = beDataBase_GetRecordInt(SHINKA(arg0), rec, DAT_00518cb0);
        mul = beDataBase_GetRecordInt(SHINKA(arg0), rec, DAT_00518cb8);
        { char *d = (char *)tbl->v; p = *(int *)(d + (base + 1) * 4); }
    }
    i = 0;
    q = DAT_004cf130;
    loop: if (*q < lvl) { q++; i++; goto loop; }
    r = p + (s0 + mul * (DAT_004cf160[i] + DAT_004cf1c0[i] * (lvl - DAT_004cf190[i])) / 100);
    if (r > 99999) r = 99999;
    return r;
}

int FUN_003fa850(beNDMWGameRam *arg0, int arg1, int arg2, int arg3) {
    void *player;
    int rec;
    BonusObj *tbl;
    int base;
    int lvl;
    int s0;
    int mul;
    int p;
    int i;
    int *q;
    int r;
    player = (void *)((int *)((igDataList *)arg0->_playerDataListList)->_data)[arg1];
    rec = arg2;
    if (rec < 0) {
        rec = igProperty_GetRecord(player, ((char *)DAT_00518848))->value;
        tbl = FUN_003a9250(player, DAT_00518868)->obj;
        base = 0;
        lvl = igProperty_GetRecord(player, DAT_00518858)->value;
    } else {
        tbl = FUN_003a9250(player, DAT_00518b60)->obj;
        base = rec * 11;
        lvl = FUN_003a9250(player, ((char *)DAT_00518b30))->obj->v[rec];
    }
    s0 = beDataBase_GetRecordInt(SHINKA_3fa850(arg0), rec, DAT_004cf250[arg3]);
    mul = beDataBase_GetRecordInt(SHINKA_3fa850(arg0), rec, DAT_004cf270[arg3]);
    p = tbl->v[base + 2 + arg3];
    i = 0;
    q = DAT_004cf130;
    loop: if (*q < lvl) { q++; i++; goto loop; }
    r = p + (s0 + mul * (DAT_004cf1f0[i] + DAT_004cf220[i] * (lvl - DAT_004cf190[i])) / 100);
    if (r > 9999) r = 9999;
    return r;
}

/* An attribute is clamped to 1..9999. */


void FUN_003fab90(beNDMWGameRam *self, int index, unsigned char apply)
{
    void *player = StatHelpers_3fab90::GetPlayer(self, index);
    int species = StatHelpers_3fab90::GetProp(player, PROP_DIGIMONNO);
    int level = StatHelpers_3fab90::GetProp(player, PROP_LEVEL);
    unsigned char first = 0;

    /* MHP / HP */
    int mhp = FUN_003fa3b0(self, index, -1, 1);
    mhp += FUN_003a9250(player, PROP_UPDATA)->obj->v[6];
    if (apply) {
        FUN_003fa120(self, player, &mhp, PROP_MAXHP, 0);
        FUN_003fa2c0((int)self, (int)player, &mhp, PROP_MAXHP, 0);
    }
    if (mhp > 99999) mhp = 99999;
    igProperty_GetRecord(player, PROP_MHP)->value = mhp;
    int curHp = igProperty_GetRecord(player, PROP_HP)->value;
    if (curHp == 0) first = 1;
    if (curHp == 0 || mhp < curHp) igProperty_GetRecord(player, PROP_HP)->value = mhp;

    int mmp = FUN_003fa3b0(self, index, -1, 0);
    if (apply) {
        FUN_003fa120(self, player, &mmp, PROP_MAXMP, 0);
        FUN_003fa2c0((int)self, (int)player, &mmp, PROP_MAXMP, 0);
    }
    if (mmp > 99999) mmp = 99999;
    igProperty_GetRecord(player, PROP_MMP)->value = mmp;
    int curMp = igProperty_GetRecord(player, PROP_MP)->value;
    if (first || mmp < curMp) igProperty_GetRecord(player, PROP_MP)->value = mmp;

    int tsuyosa = FUN_003fa850(self, index, -1, 0);
    tsuyosa += FUN_003a9250(player, PROP_UPDATA)->obj->v[4];
    tsuyosa -= FUN_003a9250(player, PROP_DOWNDATA)->obj->v[4];
    if (apply) {
        FUN_003f9f80((int)self, (int)player, &tsuyosa, PROP_TSUYOSA, 1);
        FUN_003fa040((int)self, (int)player, &tsuyosa, PROP_TSUYOSA);
        FUN_003fa2c0((int)self, (int)player, &tsuyosa, PROP_TSUYOSA, 1);
    }
    CLAMP_ATTR(tsuyosa)
    igProperty_GetRecord(player, PROP_TSUYOSA)->value = tsuyosa;

    int mamori = FUN_003fa850(self, index, -1, 1);
    mamori += FUN_003a9250(player, PROP_UPDATA)->obj->v[5];
    mamori -= FUN_003a9250(player, PROP_DOWNDATA)->obj->v[5];
    if (apply) {
        FUN_003fa120(self, player, &mamori, PROP_MAMORI, 1);
        FUN_003fa2c0((int)self, (int)player, &mamori, PROP_MAMORI, 1);
    }
    CLAMP_ATTR(mamori)
    igProperty_GetRecord(player, PROP_MAMORI)->value = mamori;

    int kashikosa = FUN_003fa850(self, index, -1, 2);
    if (apply) {
        FUN_003f9f80((int)self, (int)player, &kashikosa, PROP_KASHIKOSA, 0);
        FUN_003fa040((int)self, (int)player, &kashikosa, PROP_KASHIKOSA);
        FUN_003fa120(self, player, &kashikosa, PROP_KASHIKOSA, 0);
        FUN_003fa1e0((int)self, (int)player, &kashikosa, PROP_KASHIKOSA);
        FUN_003fa2c0((int)self, (int)player, &kashikosa, PROP_KASHIKOSA, 1);
    }
    CLAMP_ATTR(kashikosa)
    igProperty_GetRecord(player, PROP_KASHIKOSA)->value = kashikosa;

    int seishin = FUN_003fa850(self, index, -1, 3);
    if (apply) {
        FUN_003f9f80((int)self, (int)player, &seishin, PROP_SEISHIN, 0);
        FUN_003fa040((int)self, (int)player, &seishin, PROP_SEISHIN);
        FUN_003fa120(self, player, &seishin, PROP_SEISHIN, 0);
        FUN_003fa1e0((int)self, (int)player, &seishin, PROP_SEISHIN);
        FUN_003fa2c0((int)self, (int)player, &seishin, PROP_SEISHIN, 0);
    }
    CLAMP_ATTR(seishin)
    igProperty_GetRecord(player, PROP_SEISHIN)->value = seishin;

    int subayasa = FUN_003fa850(self, index, -1, 4);
    subayasa += FUN_003a9250(player, PROP_UPDATA)->obj->v[0];
    subayasa -= FUN_003a9250(player, PROP_DOWNDATA)->obj->v[0];
    if (apply) {
        FUN_003f9f80((int)self, (int)player, &subayasa, PROP_SUBAYASA, 0);
        FUN_003fa040((int)self, (int)player, &subayasa, PROP_SUBAYASA);
        FUN_003fa120(self, player, &subayasa, PROP_SUBAYASA, 0);
        FUN_003fa1e0((int)self, (int)player, &subayasa, PROP_SUBAYASA);
        FUN_003fa2c0((int)self, (int)player, &subayasa, PROP_SUBAYASA, 1);
    }
    CLAMP_ATTR(subayasa)
    igProperty_GetRecord(player, PROP_SUBAYASA)->value = subayasa;

    int fire = beDataBase_GetRecordInt(SHINKA_3fab90(self), species, PROP_RES_FIRE);
    fire += FUN_003a9250(player, PROP_UPCNT)->obj->v[7];
    fire += FUN_003a9250(player, PROP_UPDATA)->obj->v[7];
    if (apply) {
        FUN_003fa120(self, player, &fire, PROP_RES_FIRE, 0);
        FUN_003fa1e0((int)self, (int)player, &fire, PROP_RES_FIRE);
        FUN_003fa2c0((int)self, (int)player, &fire, PROP_RES_FIRE, 1);
    }
    CLAMP_ATTR(fire)
    igProperty_GetRecord(player, PROP_HONOOTEIKO)->value = fire;
    int ice = beDataBase_GetRecordInt(SHINKA_3fab90(self), species, PROP_RES_ICE);
    ice += FUN_003a9250(player, PROP_UPCNT)->obj->v[8];
    ice += FUN_003a9250(player, PROP_UPDATA)->obj->v[8];
    if (apply) {
        FUN_003fa120(self, player, &ice, PROP_RES_ICE, 0);
        FUN_003fa1e0((int)self, (int)player, &ice, PROP_RES_ICE);
        FUN_003fa2c0((int)self, (int)player, &ice, PROP_RES_ICE, 1);
    }
    CLAMP_ATTR(ice)
    igProperty_GetRecord(player, PROP_KOORITEIKO)->value = ice;
    int thunder = beDataBase_GetRecordInt(SHINKA_3fab90(self), species, PROP_RES_THUNDER);
    thunder += FUN_003a9250(player, PROP_UPCNT)->obj->v[9];
    thunder += FUN_003a9250(player, PROP_UPDATA)->obj->v[9];
    if (apply) {
        FUN_003fa120(self, player, &thunder, PROP_RES_THUNDER, 0);
        FUN_003fa1e0((int)self, (int)player, &thunder, PROP_RES_THUNDER);
        FUN_003fa2c0((int)self, (int)player, &thunder, PROP_RES_THUNDER, 1);
    }
    CLAMP_ATTR(thunder)
    igProperty_GetRecord(player, PROP_KAMINARITEIKO)->value = thunder;
    int dark = beDataBase_GetRecordInt(SHINKA_3fab90(self), species, PROP_RES_DARK);
    dark += FUN_003a9250(player, PROP_UPCNT)->obj->v[10];
    dark += FUN_003a9250(player, PROP_UPDATA)->obj->v[10];
    if (apply) {
        FUN_003fa120(self, player, &dark, PROP_RES_DARK, 0);
        FUN_003fa1e0((int)self, (int)player, &dark, PROP_RES_DARK);
        FUN_003fa2c0((int)self, (int)player, &dark, PROP_RES_DARK, 1);
    }
    CLAMP_ATTR(dark)
    igProperty_GetRecord(player, PROP_YAMITEIKO)->value = dark;

    {
        igObjectList *list = ((ListHolder *)igProperty_GetRecordFolder(player, PROP_WAZALIST))->list;
        int oldCount = list->_count;
        for (int r = 0; r < oldCount; r++) RELEASE(((igObject **)list->_data)[r]);
        int clearCount = list->_count;
        for (int c = 0; c < clearCount; c++) ((int *)list->_data)[c] = 0;
        list->_count = 0;

        for (int slot = 0; slot < 6; slot++) {
            int tech = beDataBase_GetRecordInt(SHINKA_3fab90(self), species, DAT_004cf290[slot]);
            int skillNo = beDataBase_GetRecordInt(PCTECH(self), tech, PROP_SKILL);
            int skillVal = FUN_003a9250(player, PROP_SKILL)->obj->v[skillNo];
            if (beDataBase_GetRecordInt(SHINKA_3fab90(self), species, DAT_004cf2b0[slot]) <= level) {
                for (int rank = 4; rank >= 0; rank--) {
                    if (beDataBase_GetRecordInt(SHINKA_3fab90(self), species, DAT_004cf2d0[slot][rank]) <= skillVal) {
                        IntListRef waza((IntList *)FUN_003c8040(StatHelpers_3fab90::select_allocator(igObject_GetAllocator(self))));
                        FUN_00448f30((igObject *)waza.value, tech + rank, tech);
                        ObjectList_AppendRetained(list, (igObject *)waza.value);
                        break;
                    }
                }
            }
        }
    }
    igProperty_GetRecord(player, PROP_NEXTEXP)->value =
        level == 999 ? 0 : level * 200 + (level + 140) * (level * level);

    if (apply) {
        int delay, hitRate, critRate, paralysisRate, evadeRate, guardRate;
        int paralysisResist, poisonResist, bitRate, expRate;
        unsigned char found;
        int luckRate;
        delay = FUN_003a9250(player, PROP_DOWNDATA)->obj->v[6];
        FUN_003f9f80((int)self, (int)player, &delay, PROP_DELAY, 0);
        if (delay > 70) delay = 70;
        igProperty_GetRecord(player, PROP_ATTACKDELAY)->value = delay;
        hitRate = 0;
        FUN_003f9f80((int)self, (int)player, &hitRate, PROP_MEICHURITSU, 0);
        igProperty_GetRecord(player, PROP_MEICHURITSU)->value = hitRate;
        critRate = 0;
        critRate += FUN_003a9250(player, PROP_UPDATA)->obj->v[1];
        critRate -= FUN_003a9250(player, PROP_DOWNDATA)->obj->v[1];
        FUN_003f9f80((int)self, (int)player, &critRate, PROP_CHIMEIRITSU, 0);
        FUN_003fa040((int)self, (int)player, &critRate, PROP_CHIMEIRITSU);
        if (critRate <= 0) critRate = 1;
        igProperty_GetRecord(player, PROP_CHIMEIRITSU)->value = critRate;
        paralysisRate = 0;
        FUN_003f9f80((int)self, (int)player, &paralysisRate, PROP_MAHIRITSU, 0);
        igProperty_GetRecord(player, PROP_MAHIRITSU)->value = paralysisRate;
        evadeRate = 0;
        evadeRate += FUN_003a9250(player, PROP_UPDATA)->obj->v[3];
        evadeRate -= FUN_003a9250(player, PROP_DOWNDATA)->obj->v[3];
        FUN_003fa1e0((int)self, (int)player, &evadeRate, PROP_CHOHATURITSU);
        if (evadeRate <= 0) evadeRate = 1;
        igProperty_GetRecord(player, PROP_KAIHIRITSU)->value = evadeRate;
        guardRate = 0;
        FUN_003fa120(self, player, &guardRate, PROP_BOUGYORITSU, 0);
        igProperty_GetRecord(player, PROP_BOUGYORITSU)->value = guardRate;
        paralysisResist = 0;
        paralysisResist += FUN_003a9250(player, PROP_UPDATA)->obj->v[2];
        paralysisResist -= FUN_003a9250(player, PROP_DOWNDATA)->obj->v[2];
        FUN_003fa120(self, player, &paralysisResist, PROP_MAHITEIKOU, 0);
        if (paralysisResist <= 0) paralysisResist = 1;
        igProperty_GetRecord(player, PROP_MAHITEIKOU)->value = paralysisResist;
        poisonResist = 0;
        FUN_003fa120(self, player, &poisonResist, PROP_DOKUTEIKOU, 0);
        igProperty_GetRecord(player, PROP_DOKUTEIKOU)->value = poisonResist;
        bitRate = 0;
        FUN_003fa2c0((int)self, (int)player, &bitRate, PROP_BITRITSU, 0);
        igProperty_GetRecord(player, PROP_BITRITSU)->value = bitRate;
        expRate = 0;
        FUN_003fa2c0((int)self, (int)player, &expRate, PROP_EXPRITSU, 0);
        igProperty_GetRecord(player, PROP_EXPRITSU)->value = expRate;
        luckRate = 0;
        FUN_003fa2c0((int)self, (int)player, &luckRate, PROP_LUCKRITSU, 0);
        igProperty_GetRecord(player, PROP_LUCKRITSU)->value = luckRate;

        { IntRec *zokusei = igProperty_GetRecord(player, PROP_ATTACKZOKUSEI); zokusei->value = -1; }
        found = 0;
        int pocketCount = ((ListHolder *)igProperty_GetRecordFolder(player, PROP_POWERPOCKET_3fab90))->list->_count;
        for (int p = 0; p < pocketCount; p++) {
            beNDMWItemBase *pocketItem = ((beNDMWItemBase **)((ListHolder *)igProperty_GetRecordFolder(player, PROP_POWERPOCKET_3fab90))->list->_data)[p];
            if (pocketItem) {
                const char *zokuseiName = beNDMWItemBase_GetRecordString(pocketItem, self, PROP_ZOKUSEI);
                for (int element = 0; element < 4; element++) {
                    if (strcmp(zokuseiName, DAT_004cf350[element]) == 0) {
                        igProperty_GetRecord(player, PROP_ATTACKZOKUSEI)->value = element;
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
            FUN_003fa040((int)self, (int)player, &hpDrain, PROP_HPDRAIN);
            igProperty_GetRecord(player, PROP_HPDRAIN)->value = hpDrain;
            mpDrain = 0;
            FUN_003fa040((int)self, (int)player, &mpDrain, PROP_MPDRAIN);
            igProperty_GetRecord(player, PROP_MPDRAIN)->value = mpDrain;
        }
        igProperty_GetRecord(player, PROP_CHOHATURITSU)->value =
            igProperty_GetRecord(player, PROP_KAIHIRITSU)->value;
    }

    if (apply) {
        int weaponRec, weaponSkill;
        beNDMWItemBase *firstSocket;
        igObjectList *sockets;
        igStringRefList *names;
        firstSocket = ((beNDMWItemBase **)((ListHolder *)igProperty_GetRecordFolder(player, PROP_POWERSOCKET))->list->_data)[0];
        weaponRec = 0;
        weaponSkill = 0;
        if (firstSocket) {
            weaponRec = firstSocket->_recNo;
            weaponSkill = beNDMWItemBase_GetRecordInt(firstSocket, self, PROP_SKILL);
        }
        igProperty_GetRecord(player, PROP_WEAPONRECNO)->value = weaponRec;
        igProperty_GetRecord(player, PROP_WEAPONSKILLNO)->value = weaponSkill;

        sockets = ((ListHolder *)igProperty_GetRecordFolder(player, PROP_POWERSOCKET))->list;
        names = FUN_003a9310(player, PROP_POWERSOCKETNAME)->list;
        int nameCount = names->_count;
        for (int i = 0; i < nameCount; i++) {
            char **entry = &((char **)names->_data)[i];
            char *old, *fresh;
            if (!DAT_00586f20[0]) {
                int pool = FUN_002eb010(16);
                if (pool) pool = StringPool_Construct(pool);
                DAT_00586f20[0] = pool;
            }
            fresh = StringPool_Intern(DAT_00586f20[0], 0);
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
                const char *model = beNDMWItemBase_GetRecordString(item, self, PROP_MODEL);
                char *interned;
                if (!model) {
                    interned = 0;
                } else {
                    if (!DAT_00586f20[0]) {
                        int pool = FUN_002eb010(16);
                        if (pool) pool = StringPool_Construct(pool);
                        DAT_00586f20[0] = pool;
                    }
                    interned = StringPool_Intern(DAT_00586f20[0], model);
                }
                StringRef token(interned);
                StringList_AppendRetained((int)names, (const StringRef &)token);
            }
        }
    }
}

/* WAZALIST */

void beNDMWGameRam_FindTechniqueRow(beNDMWGameRam *receiver, void *player,
                                   int base_no, int *output)
{
    igObjectList *list;
    int index;
    beNDMWItemWaza *item;
    int count;

    list = ((TechniqueListProperty *)igProperty_GetRecordFolder(player, WAZALIST))->list;
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

inline IntListRef::IntListRef(const NearbyListRef &p):value(p.value) { if(value) ++value->reference_word; }

/* Collects the ids of the members of messenger group `group` that are within 30 units of `center`
 * (compared on GETMATRIX translations), skips `excluded`, and keeps those whose GETHP reply is
 * nonzero. The result list comes from the object's own allocator when the global byte flag is set,
 * otherwise from the allocator selected by g_defaultAllocatorSelector[0]. */
IntListRef beNDMWGameRam_CollectNearbyNonzeroHp(beNDMWGameRam *self,const char *group,int excluded,const Vec3 *center) {
    int entry_index;
    int member_id;
    int append_index;
    IntList *list;
    int selfAllocator=igObject_GetAllocator(self);
    NearbyListRef result(FUN_002caa70(GPR_00554c14 ? selfAllocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
    beMessenger_SendGroup(self->_messenger,group,GETMATRIX);
    int count=beMessenger_GetIntCount(self->_messenger);
    Vec3 delta;
    Mat44 matrix;
    for(entry_index=0;entry_index<count;++entry_index) {
        member_id=beMessenger_GetInt(self->_messenger,entry_index);
        if(member_id!=excluded) {
            beMessenger_GetMatrix(&matrix,self->_messenger,entry_index);
            Matrix44_GetTranslation(&matrix,&delta);
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

/* igDataList, the base of every typed list, holds the igMemoryRef _data at +16. */


int FUN_00406da0(igDataList *p)
{
    return p->_data;
}

int FUN_00406db0(int *p)
{
    return *(int *)((char *)p + 12);
}

int FUN_00406dc0(int *p)
{
    return *p;
}

int FUN_00406dd0(beNDMWGameRam *arg0, int arg1) {
    return *(int *)(arg0->_system + (arg1 * 4));
}

int FUN_00406df0(int *p)
{
    return *(int *)((char *)p + 0);
}

int FUN_00406e00(int *p)
{
    return *(int *)((char *)p + 0);
}

int *FUN_00406e10(int *arg0, int *arg1) {
    *arg0 = beBaseInfoDataList_Create(*arg1);
    return arg0;
}

int FUN_00406e40(int *p)
{
    return *(int *)((char *)p + 12);
}

int FUN_00406e50(int *p)
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

int FUN_00406ee0(int *p)
{
    return *p;
}

int FUN_00406ef0(int *p)
{
    return *(int *)((char *)p + 0);
}

int FUN_00406f00(igUnsignedCharList *p)
{
    return p->_data;
}

int FUN_00406f10(int *p)
{
    return *p;
}

void FUN_00406f20(void)
{
    List_RemoveWordAt();
}

void FUN_00406f40(int a0, int a1)
{
    *(int *)((char *)a0 + 0) = a1;
}

void FUN_00406f50(int a0, int a1)
{
    *(int *)((char *)a0 + 0) = a1;
}

void FUN_00406f60(int a0, int a1)
{
    *(int *)((char *)a0 + 0) = a1;
}

void FUN_00406f70(int a0, int a1)
{
    *(int *)((char *)a0 + 0) = a1;
}

int FUN_00406f80(int *p)
{
    return *(int *)((char *)p + 0);
}

int FUN_00406f90(beDataObjInt *p)
{
    return p->_data;
}

void FUN_00406fa0(void **arg0) {
    int *temp_a1;
    int temp_v1;
    void *temp_a0;

    temp_a0 = (void *)(*arg0);
    if (temp_a0 != 0) {
        temp_a1 = (int *)((char *)temp_a0 - 8);
        temp_v1 = *(int *)((char *)(temp_a0) - 4) - 1;
        *(int *)((char *)(temp_a0) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
}

int StringPool_GetInstance(void) {
    int pool;

    if (g_stringPool[0] == 0) {
        pool = FUN_002eb010(0x10);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    return g_stringPool[0];
}

int FUN_00407030(int *p)
{
    return *(int *)((char *)p + 0);
}

int FUN_00407040(int *p)
{
    return *(int *)((char *)p + 0);
}

int FUN_00407050(int *p)
{
    return *(int *)((char *)p + 0);
}

int Gap__Bec__beNDMWGameRam__vfunc_20(void)
{
    return g_beNDMWGameRam_metaObject[0];
}

int Gap__Bec__beNDMWGameRam__vfunc_30(void) {
    return 0;
}

