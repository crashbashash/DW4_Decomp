#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
#define RELEASE_REF(T, q) { T *rr = (q); if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }
#define ALLOC(var) { void *got = ((void *)igObject_GetAllocator(arg0)); if (GPR_00554c14) var = got; else var = ((void *)Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0])); }
#define RESERVE(LT, h, SZ) { LT *l = (LT *)(h)->_data; if (!(e->count < l->_count)) List_Reserve(l, e->count, SZ); }
#define RESIZE(LT, h, SZ) { int n = e->count; LT *l = (LT *)(h)->_data; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize(l, n, SZ); } }
#define A_(x) (x)
#define RELO(X) { igObject *q = (X); if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7fffff) == 0) igObject_Destroy(q); } }
#define PROP_DIGIMONNO       ((char *)DIGIMONNO_2)
#define PROP_SKILL           ((char *)SKILL)
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
#define PROP_LEVEL           LEVEL_2
#define PROP_UPCNT           UPCNT
#define PROP_HP              HP
#define PROP_MHP             MHP
#define PROP_MP              MP
#define PROP_MMP             MMP
#define PROP_MAMORI          DAT_005188b8
#define PROP_KASHIKOSA       DAT_005188c0
#define PROP_SEISHIN         DAT_005188d0
#define PROP_SUBAYASA        DAT_005188d8
#define PROP_HONOOTEIKO      DAT_005188e8
#define PROP_KOORITEIKO      DAT_005188f8
#define PROP_KAMINARITEIKO   DAT_00518908
#define PROP_YAMITEIKO       DAT_00518918
#define PROP_WAZALIST        WAZALIST
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
extern "C" void List_RemoveWordAt(void *list, int index);
extern "C" void FUN_00406f20(void *list, int index);
/* matching construct: copy-constructed struct return reproduces the retail hidden-return calling shape */ struct DW4Sret4 { int v; DW4Sret4(int value):v(value) {} DW4Sret4(const DW4Sret4 &o):v(o.v) {} };
extern "C" DW4Sret4 FUN_00406f40(int value);
extern "C" DW4Sret4 FUN_00406f50(int value);
extern "C" DW4Sret4 FUN_00406f60(int value);
extern "C" DW4Sret4 FUN_00406f70(int value);
extern "C" int FUN_00406f80(int *p);
extern "C" int StringPool_GetInstance(void);
extern "C" int FUN_00407030(int *p);
extern "C" int FUN_00407040(int *p);
extern "C" int FUN_00407050(int *p);
extern "C" int g_ndmwAllocatorSelector[4];
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
extern "C" igObject *FUN_00364050(int);
extern "C" igObject *FUN_003c85b0(int);
extern "C" int FUN_00448710(igObject *, int);
extern "C" int DAT_004ced40[4];
extern "C" int DAT_004cedf0[4];
extern "C" int DAT_004cf110[4];
extern "C" int DAT_004cf118[4];
extern "C" int DAT_00518a50[4];
extern "C" int DAT_00518ae8[4];
extern "C" const char BASE_LEVEL[];
extern "C" const char BASE_SKILL[];
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
extern "C" int g_defaultAllocatorSelector[4];
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
extern "C" int g_stringPool[4];
struct R { int w0; int rc; };
extern "C" int FUN_003f80e0(beNDMWGameRam *arg0, int arg1);
typedef struct PropertyRecord { char header[12]; void *value; } PropertyRecord;
extern "C" PropertyRecord *FUN_003a92e0(void *, void *);
extern "C" igObject * beMessenger_GetObject(...);
extern "C" int DAT_00518798[4];
extern "C" int DAT_005187a0[4];
extern "C" int DAT_005187b0[4];
extern "C" const char DIGIMONNO_2[];
extern "C" const char LEVEL_2[];
extern "C" const char SKILL[];
extern "C" const char UPCNT[];
extern "C" int DAT_00518870[4];
extern "C" const char EXP[];
extern "C" int DAT_00518b00[4];
extern "C" int DAT_00518b10[4];
extern "C" const char BASE_EXP[];
extern "C" const char BASE_UPCNT[];
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
extern "C" void ObjectRef_Retain_003e90d0(void *);
template<int I> class RecoveryRef { public:
 void *value;
 RecoveryRef(void *p, bool retain):value(p) { if(retain) ObjectRef_Retain_003e90d0(value); }
 RecoveryRef(const RecoveryRef &other):value(other.value) { ObjectRef_Retain_003e90d0(value); }
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
extern "C" unsigned char FUN_003f93c0(beNDMWGameRam *arg0, int arg1, int arg2);
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
extern "C" int g_beFont_metaObject[4];
extern "C" void FUN_003f96e0(beNDMWGameRam *arg0, int arg1, void *arg2, StringRef arg3);
extern "C" void FUN_003f99f0(beNDMWGameRam *arg0, int arg1, void *arg2, RecoveryRef<0> arg3);
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
extern "C" NearbyListRef beNDMWGameRam_CollectNearbyNonzeroHp(beNDMWGameRam *self,const char *group,int excluded,const Vec3 *center);
extern "C" char DAT_005188b8[];
extern "C" char DAT_005188c0[];
extern "C" char DAT_005188d0[];
extern "C" char DAT_005188d8[];
extern "C" char DAT_005188e8[];
extern "C" char DAT_005188f8[];
extern "C" char DAT_00518908[];
extern "C" char DAT_00518918[];
extern "C" const char WAZALIST[];
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
        else return Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
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
        a0 = Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
    }
    igSmartPointer<igObject> data(FUN_00364050(a0));
    FUN_003f6620((void *)arg0, data.p, (void *)(&DAT_004cedf0[0]));
    for (c = 0; c < 16; c++) {
        recs = (igObjectList *)((igObject **)((void *)FUN_003a9250(data.p, BASE_LEVEL)))[3];
        if (recs->_count != 0 && c >= 0 && c < recs->_count)
            ((int *)recs->_data)[c] = DAT_004cf110[0];
    }
    for (d = 0; d < 16; d++) {
        for (e = 0; e < 9; e++) {
            arr = (igObjectList *)((igObject **)((void *)FUN_003a9250(data.p, BASE_SKILL)))[3];
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
            a1 = Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
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
        var_v0 = Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
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
        var_v0_2 = Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
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
        var_v0 = GPR_00554c14 ? var_v0 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<beNDMWGameRamInfo> info(FUN_003ca380(var_v0));
        var_v0 = igObject_GetAllocator(arg0);
        var_v0 = GPR_00554c14 ? var_v0 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
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
        if (g_stringPool[0] == 0) {
            var_v0_2 = FUN_002eb010(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            g_stringPool[0] = var_v0_2;
        }
        var_v0 = StringPool_Intern(g_stringPool[0], arg1);
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
    igProperty_GetRecord(s4, &((int *)LEVEL_2)[0]);
    ((PropertyRecord *)igProperty_GetRecord(s4, DIGIMONNO_2))->value = (void *)arg2;
    if (arg0->_dBShinka == 0) {
        beMessenger_SendNamed(arg0->_messenger, &DAT_00519438[0], &DAT_00519430[0], 0, &DAT_00519420[0]);
        o = beMessenger_GetObject(arg0->_messenger, 0);
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)arg0->_dBShinka;
        RELO(old)
        arg0->_dBShinka = (int)o;
    }
    s0 = ((int)beDataBase_GetRecordString(arg0->_dBShinka, arg2, &DAT_00518bc8[0]));
    s1 = FUN_003a92e0((void *)s4, &DAT_00518870[0]);
    if (g_stringPool[0] == 0) {
        v0 = FUN_002eb010(16);
        if (v0 != 0) v0 = StringPool_Construct(v0);
        g_stringPool[0] = v0;
    }
    s1i = ((int)StringPool_Intern(g_stringPool[0], s0));
    hd = (int)s1->value;
    if (hd != 0) {
        int *p = (int *)(hd - 8);
        int c = *(int *)(hd - 4) - 1;
        *(int *)(hd - 4) = c;
        if (c == 0) StringChunk_ReleaseHeader(*p, p);
    }
    s1->value = (void *)s1i;
    l1 = (igIntList *)((PropertyRecord *)FUN_003a9250(s4, BASE_LEVEL))->value;
    s0 = arg2 * 4;
    e1 = ((int *)l1->_data)[arg2];
    ((PropertyRecord *)igProperty_GetRecord(s4, &((int *)LEVEL_2)[0]))->value = (void *)e1;
    l2 = (igIntList *)((PropertyRecord *)FUN_003a9250(s4, BASE_EXP))->value;
    e2 = ((int *)l2->_data)[arg2];
    ((PropertyRecord *)igProperty_GetRecord(s4, EXP))->value = (void *)e2;
    /* matching construct: base9/base11 hoisted into locals, else MWCC strength-reduces the index */
    base9 = arg2 * 9;
    var_s2 = 0;
    var_s0 = 0;
    do {
        a2 = (igIntList *)((PropertyRecord *)FUN_003a9250(s4, BASE_SKILL))->value;
        e1L = ((int *)a2->_data)[base9 + var_s2];
        a0 = (igIntList *)((PropertyRecord *)FUN_003a9250(s4, SKILL, a2))->value;
        cnt1 = a0->_count;
        if (cnt1 != 0 && var_s2 >= 0 && var_s2 < cnt1) ((int *)(a0->_data + var_s0))[0] = e1L;
        var_s2 += 1;
        var_s0 += 4;
    } while (var_s2 < 9);
    base11 = arg2 * 11;
    var_s2b = 0;
    var_s0b = 0;
    do {
        a2b = (igIntList *)((PropertyRecord *)FUN_003a9250(s4, &((int *)BASE_UPCNT)[0]))->value;
        e2 = ((int *)a2b->_data)[base11 + var_s2b];
        a0b = (igIntList *)((PropertyRecord *)FUN_003a9250(s4, &((int *)UPCNT)[0], a2b))->value;
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
    s6 = ((Rec *)((void *)igProperty_GetRecord(obj, DIGIMONNO_2)))->f12;
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
        al = (GPR_00554c14 != 0) ? al : Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
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
            if (!g_stringPool[0]) {
                int pool = FUN_002eb010(16);
                if (pool) pool = StringPool_Construct(pool);
                g_stringPool[0] = pool;
            }
            fresh = StringPool_Intern(g_stringPool[0], 0);
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
                    if (!g_stringPool[0]) {
                        int pool = FUN_002eb010(16);
                        if (pool) pool = StringPool_Construct(pool);
                        g_stringPool[0] = pool;
                    }
                    interned = StringPool_Intern(g_stringPool[0], model);
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
            if (!g_stringPool[0]) {
                int pool = FUN_002eb010(16);
                if (pool) pool = StringPool_Construct(pool);
                g_stringPool[0] = pool;
            }
            fresh = StringPool_Intern(g_stringPool[0], 0);
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
                if (!g_stringPool[0]) {
                    int pool = FUN_002eb010(16);
                    if (pool) pool = StringPool_Construct(pool);
                    g_stringPool[0] = pool;
                }
                interned = StringPool_Intern(g_stringPool[0], model);
            }
            StringList_AppendRetained((int)names, StringRef(interned));
            chosen->_isEquip = 1;
        }
    }
}

unsigned char FUN_003f93c0(beNDMWGameRam *arg0, int arg1, int arg2) {
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
    int t = ((Rec_3f93c0 *)igProperty_GetRecord(obj, DIGIMONNO_2))->w12;
    if (t == arg2) {
        tbl = (igIntList *)((Rec_3f93c0 *)FUN_003a9250(obj, SKILL))->w12;
        base = 0;
    } else {
        tbl = (igIntList *)((Rec_3f93c0 *)FUN_003a9250(obj, BASE_SKILL))->w12;
        base = arg2 * 9;
    }
    }
    mask = 1 << arg2;
    n = folder->_count;
    for (i = 0; i < n; i++) {
        Rec_3f93c0 *r = (Rec_3f93c0 *)((int *)folder->_data)[i];
        if (r->w8 == 0) {
            int f = mask & beNDMWItemBase_GetRecordInt(r, arg0, ((int *)DAT_00518c10));
            int idx = beNDMWItemBase_GetRecordInt(r, arg0, SKILL);
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

void FUN_003f96e0(beNDMWGameRam *arg0, int arg1, void *arg2, StringRef arg3) {
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
    al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
    igSmartPointer<beUnicodeObj> rb(FUN_003614f0(al));
    beUnicodeObj_AllocateBuffer(rb.p, 8);
    {
        /* The looked-up name is an out-parameter the lookup retains; it is released by hand rather
         * than by a destructor. */
        beUnicodeObj *ra;
        int sel = (int)arg3.p;
        int table = FUN_00236f80(arg0->_insight, g_beFont_metaObject[0]);
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

void FUN_003f99f0(beNDMWGameRam *arg0, int arg1, void *arg2, RecoveryRef<0> arg3) {
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
    ObjectList_AppendRetained(l, arg3.value);
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
        rec = igProperty_GetRecord(player, ((char *)DIGIMONNO_2))->value;
        tbl = FUN_003a9250(player, UPCNT)->obj;
        base = 0;
        lvl = igProperty_GetRecord(player, LEVEL_2)->value;
    } else {
        tbl = FUN_003a9250(player, BASE_UPCNT)->obj;
        base = rec * 11;
        lvl = FUN_003a9250(player, ((char *)BASE_LEVEL))->obj->v[rec];
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
        rec = igProperty_GetRecord(player, ((char *)DIGIMONNO_2))->value;
        tbl = FUN_003a9250(player, UPCNT)->obj;
        base = 0;
        lvl = igProperty_GetRecord(player, LEVEL_2)->value;
    } else {
        tbl = FUN_003a9250(player, BASE_UPCNT)->obj;
        base = rec * 11;
        lvl = FUN_003a9250(player, ((char *)BASE_LEVEL))->obj->v[rec];
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
            if (!g_stringPool[0]) {
                int pool = FUN_002eb010(16);
                if (pool) pool = StringPool_Construct(pool);
                g_stringPool[0] = pool;
            }
            fresh = StringPool_Intern(g_stringPool[0], 0);
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
                    if (!g_stringPool[0]) {
                        int pool = FUN_002eb010(16);
                        if (pool) pool = StringPool_Construct(pool);
                        g_stringPool[0] = pool;
                    }
                    interned = StringPool_Intern(g_stringPool[0], model);
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

/* Collects the ids of the members of messenger group `group` that are within 30 units of `center`
 * (compared on GETMATRIX translations), skips `excluded`, and keeps those whose GETHP reply is
 * nonzero. The result list comes from the object's own allocator when the global byte flag is set,
 * otherwise from the allocator selected by g_defaultAllocatorSelector[0]. */
NearbyListRef beNDMWGameRam_CollectNearbyNonzeroHp(beNDMWGameRam *self,const char *group,int excluded,const Vec3 *center) {
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

extern "C" {
#define MULT_HI(a,b) ((int)(((long long)(int)(a)*(long long)(int)(b))>>32))

typedef struct DW4CountedListView { char _pad0[8]; int count; } DW4CountedListView; /* matching construct: class of the FUN_00406df0 result not determined, only the +8 count is read */
typedef struct DW4ByteFlag8 { char _pad0[8]; unsigned char value; } DW4ByteFlag8; /* matching construct: class of the FUN_00406dd0 result not determined; byte flag at +8 */
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
void FUN_003e9220(...);
int ObjectList_GetAt_003e9260(...);
int DataList_GetData_003e9090(...);
int Memory_SelectAllocator_003e9370(...);
void Matrix44_Copy(...);
void igMatrix44f_SetIdentity(...);
void *FightCom_GetMetaEnum(...);
void *GameRamMessage_GetMetaEnum(...);
extern const short DAT_004cf390[4][21][3];
extern const short DAT_004cf590[21];
extern const char *const DAT_004cf360[5];
extern const char *const DAT_004cf380[4];
extern const char *const DAT_004cf5c0[6];
int FUN_0033e9c0(...);
void *FUN_003c87f0(...);
void *FUN_003c8970(...);
void *FUN_003c8b00(...);
int FUN_003e9280(...);
int FUN_003e92a0(...);
DW4Sret4 FUN_003e9360(...);
int FUN_003e93b0(...);
int FUN_00447b00(...);
int FUN_00447b40(...);
int FUN_00448050(...);
int FUN_00448410(...);
int FUN_00448560(...);
int FUN_00448660(...);
int beMessenger_EnqueueSelected(...);
int beMessenger_PrepareDelayedSelection(...);
DW4Sret4 igMetaEnum_GetValueByName(...);
extern int DAT_004cf538[4];
extern int DAT_004cf558[4];
extern int DAT_004cf5d8[4];
extern int DAT_004cf5e0[4];
extern int DAT_004cf5e8[4];
extern int DAT_004cf5f0[4];
extern int DAT_004cf600[4];
extern int DAT_004cf620[4];
extern Vec3 g_vec3Zero[4];
extern char DAT_005187d8[];
extern char DAT_005187e8[];
extern char DAT_00518840[];
extern char DAT_00518fa8[];
extern char DAT_00518fb0[];
extern char DAT_00518fb8[];
extern char DAT_00518fc0[];
extern char DAT_00519020[];
extern char GETMATRIX[];
extern char GETHP[];
extern char DAT_005190a8[];
extern char DAT_005190b0[];
extern char DAT_005190c0[];
extern int DAT_005190d0[4];
extern char DAT_005190e0[];
extern char DAT_005190e8[];
extern char DAT_005190f0[];
extern char DAT_005190f8[];
extern char DAT_00519100[];
extern char DAT_00519108[];
extern char DAT_00519110[];
extern char DAT_00519118[];
extern char DAT_00519120[];
extern char DAT_00519128[];
extern char DAT_00519130[];
extern char DAT_00519138[];
extern char DAT_00519140[];
extern char DAT_00519148[];
extern char DAT_00519150[];
extern char DAT_00519158[];
extern char DAT_00519160[];
extern char DAT_00519168[];
extern char DAT_00519178[];
extern char DAT_00519188[];
extern char DAT_00519198[];
extern char DAT_005191a0[];
extern char DAT_005191a8[];
extern char DAT_005191b8[];
extern char DAT_005191c0[];
extern char DAT_005191d0[];
extern char DAT_005191d8[];
extern int DAT_005191e8[4];
extern char DAT_005191f0[];
extern char DAT_005191f8[];
extern char DAT_00519200[];
extern char DAT_00519210[];
extern char DAT_00519220[];
extern char DAT_00519228[];
extern char DAT_00519230[];
extern char DAT_00519238[];
extern char DAT_00519248[];
extern char DAT_00519250[];
extern char DAT_00519260[];
extern char DAT_00519270[];
extern char DAT_00519280[];
extern char DAT_00519290[];
extern int DAT_00519298[4];
extern int DAT_005192a0[4];
extern char DAT_005192b0[];
extern char DAT_005192c0[];
extern int DAT_005192d0[4];
extern char DAT_005192e0[];
extern char DAT_005192e8[];
extern char DAT_005192f0[];
extern char DAT_005192f8[];
extern int DAT_00519300[4];
extern char DAT_00519470[];
extern char DAT_00519480[];
extern char DAT_00519488[];
extern char DAT_00519498[];
extern char DAT_005194a8[];
extern char DAT_005194b0[];
extern int g_propertyNameField[4];
extern unsigned char GPR_005549f0;
extern unsigned char GPR_005549f4;
int Gap__Bec__beNDMWGameRam__vfunc_34(beNDMWGameRam *arg0, int arg1, void *arg2);
}
/* matching construct: dummy-virtual class so vX() compiles to the retail vtable call */ class DW4VC_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
extern "C" int FUN_00229fb0(void *, const StringRef &);
/* matching construct: inline helper reproduces the retail arithmetic shape */ struct DW4Curve { static int g(int d, int x) { return d * 0xC8 + (x + 0x8B) * (d * d); } static int f(int x) { int d = x - 1; return d * 0xC8 + (x + 0x8B) * (d * d); } };
/* matching construct: RAII copied-reference local reproduces the retail unwind table */ class RecoveryCopiedRef { public: void *value; RecoveryCopiedRef(const DW4Sret4 &source); ~RecoveryCopiedRef(); };
extern "C" int *ObjectRef_Assign_003e92b0(void *, const RecoveryCopiedRef &);
/* matching construct: out-of-line helper reproduces the retail call shape */ struct DW4Fresh { static int *Assign(void *obj, int alloc) { RecoveryCopiedRef c(FUN_003e9360(Memory_SelectAllocator_003e9370(&g_defaultAllocatorSelector[0], alloc))); return ObjectRef_Assign_003e92b0(obj, c); } };
/* matching construct: out-of-line helper that reproduces the retail call shape of the BKCHIPNAME string-list store */
struct DW4StrListOps { static void SetAt(igStringRefList *list, int idx, const StringRef &v) { if (list->_count != 0 && idx >= 0 && idx < list->_count) FUN_00229fb0((void *)((char *)FUN_00406da0((igDataList *)list) + idx * 4), v); } };
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
int Gap__Bec__beNDMWGameRam__vfunc_34(beNDMWGameRam *arg0, int arg1, void *arg2) {
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
    Vec3 sp3D8;
    Vec3 sp3C8;
    Vec3 sp3B8;
    Vec3 sp3A8;
    Vec3 sp398;
    Vec3 sp388;
    Vec3 sp378;
    Vec3 sp368;
    Vec3 sp358;
    Vec3 sp348;
    Vec3 sp338;
    Vec3 sp328;
    Vec3 sp318;
    Vec3 sp308;
    Vec3 sp2F8;
    Mat44 sp2B0;
    Mat44 sp270;
    Mat44 sp230;
    Mat44 sp1F0;
    Mat44 sp1B0;
    Mat44 sp170;
    Mat44 sp130;
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

    temp_ret = (const char *)FUN_00407050((int *)((char *)arg2 + 0x14));
    temp_ret_2 = (void *)(GameRamMessage_GetMetaEnum());
    temp_ret_3 = beMessenger_ResolveEnumValue(arg0->_messenger, temp_ret_2, temp_ret);
    temp_v0 = temp_ret_3;
    switch (temp_v0) {
    case 0:
        temp_ret_4 = (void *)(FUN_00407040(&arg0->_commonDataList));
        beMessenger_AppendObject(arg0->_messenger, temp_ret_4);
        return 1;
    case 1:
        temp_ret_5 = beMessenger_GetInt(arg0->_messenger, 0);
        temp_ret_6 = (void *)(FUN_00407030(&arg0->_playerDataListList));
        temp_ret_7 = ObjectList_GetAt_003e9260(temp_ret_6, temp_ret_5);
        beMessenger_AppendObject(arg0->_messenger, temp_ret_7);
        return 1;
    case 2:
        temp_ret_8 = (void *)(FUN_00407030(&arg0->_playerDataListList));
        temp_ret_9 = ObjectList_GetAt_003e9260(temp_ret_8, 0);
        beMessenger_AppendObject(arg0->_messenger, temp_ret_9);
        return 1;
    case 3:
        temp_ret_10 = (void *)(FUN_00407030(&arg0->_playerDataListList));
        temp_ret_11 = ObjectList_GetAt_003e9260(temp_ret_10, 1);
        beMessenger_AppendObject(arg0->_messenger, temp_ret_11);
        return 1;
    case 4:
        temp_ret_12 = (void *)(FUN_00407030(&arg0->_playerDataListList));
        temp_ret_13 = ObjectList_GetAt_003e9260(temp_ret_12, 2);
        beMessenger_AppendObject(arg0->_messenger, temp_ret_13);
        return 1;
    case 5:
        temp_ret_14 = (void *)(FUN_00407030(&arg0->_playerDataListList));
        temp_ret_15 = ObjectList_GetAt_003e9260(temp_ret_14, 3);
        beMessenger_AppendObject(arg0->_messenger, temp_ret_15);
        return 1;
    case 11: {
        unsigned char var_s0_2;
        temp_ret_16 = beMessenger_GetInt(arg0->_messenger, 0);
        var_s0_2 = 1;
        temp_ret_17 = beMessenger_GetBoolCount(arg0->_messenger);
        if (temp_ret_17 != 0) {
            temp_ret_18 = beMessenger_GetBool(arg0->_messenger, 0);
            var_s0_2 = temp_ret_18;
        }
        FUN_003fab90(arg0, temp_ret_16, var_s0_2);
        return 1;
    }
    case 12:
        temp_ret_20 = beMessenger_GetInt(arg0->_messenger, 0);
        temp_ret_21 = beMessenger_GetString(arg0->_messenger, 0);
        temp_ret_22 = FUN_003f80e0(arg0, (int)temp_ret_21);
        FUN_003f82a0(arg0, temp_ret_20, temp_ret_22);
        return 1;
    case 13:
        temp_ret_24 = beMessenger_GetInt(arg0->_messenger, 0);
        FUN_003f8760(arg0, temp_ret_24);
        return 1;
    case 14:
        temp_ret_26 = beMessenger_GetInt(arg0->_messenger, 0);
        temp_ret_27 = beMessenger_GetInt(arg0->_messenger, 1);
        beMessenger_AppendBool(arg0->_messenger, FUN_003f93c0(arg0, temp_ret_26, temp_ret_27));
        return 1;
    case 15:
        temp_ret_29 = beMessenger_GetInt(arg0->_messenger, 0);
        FUN_003f8c90(arg0, temp_ret_29, 1);
        return 1;
    case 6:
        temp_ret_31 = beMessenger_GetInt(arg0->_messenger, 0);
        FUN_003f7310(arg0, temp_ret_31);
        return 1;
    case 7:
        temp_ret_33 = beMessenger_GetInt(arg0->_messenger, 0);
        temp_v0_2 = temp_ret_33;
        temp_ret_34 = beMessenger_GetString(arg0->_messenger, 0);
        temp_v0_3 = (char *)(temp_ret_34);
        temp_ret_35 = beMessenger_GetObjectCount(arg0->_messenger);
        if (temp_ret_35 == 1) {
            temp_ret_36 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
            temp_v0_4 = (void *)(temp_ret_36);
            { RecoveryRef<0> sp4AC((void *)(temp_v0_4), true);
            FUN_003f99f0(arg0, temp_v0_2, temp_v0_3, sp4AC);
            }
        } else {
            temp_ret_38 = beMessenger_GetStringCount(arg0->_messenger);
            if (temp_ret_38 == 2) {
                temp_ret_39 = beMessenger_GetString(arg0->_messenger, 1);
                temp_v0_5 = (char *)(temp_ret_39);
                FUN_003f96e0(arg0, temp_v0_2, temp_v0_3, StringRef(temp_v0_5 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_5)));
            }
        }
        return 1;
    case 8:
        temp_ret_44 = beMessenger_GetInt(arg0->_messenger, 0);
        FUN_003f9bb0(arg0, temp_ret_44);
        return 1;
    case 16:
        var_s2 = 0;
        do {
            temp_ret_46 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_47 = ObjectList_GetAt_003e9260(temp_ret_46, var_s2);
            temp_v0_6 = (void *)(temp_ret_47);
            temp_ret_48 = (beDataObjBool *)(igProperty_GetRecordByte((int)temp_v0_6, &DAT_00518888[0]));
            if (temp_ret_48->_data != 0) {
                temp_ret_49 = (int)igProperty_GetRecord(temp_v0_6, MHP);
                temp_ret_50 = FUN_00406f90((beDataObjInt *)temp_ret_49);
                temp_ret_51 = (int)igProperty_GetRecord(temp_v0_6, HP);
                ((beDataObjInt *)temp_ret_51)->_data = temp_ret_50;
                temp_ret_52 = (int)igProperty_GetRecord(temp_v0_6, MMP);
                temp_ret_53 = FUN_00406f90((beDataObjInt *)temp_ret_52);
                temp_ret_54 = (int)igProperty_GetRecord(temp_v0_6, MP);
                ((beDataObjInt *)temp_ret_54)->_data = temp_ret_53;
            }
            var_s2 += 1;
        } while (var_s2 < 4);
        return 1;
    case 9:
        temp_ret_55 = beMessenger_GetInt(arg0->_messenger, 0);
        temp_v0_7 = temp_ret_55;
        temp_ret_56 = beMessenger_GetInt(arg0->_messenger, 1);
        var_v0_2 = beMessenger_GetIntCount(arg0->_messenger) < 3 ? 0 : beMessenger_GetInt(arg0->_messenger, 2);
        var_v0_3 = beMessenger_GetIntCount(arg0->_messenger) < 4 ? -1 : beMessenger_GetInt(arg0->_messenger, 3);
        temp_ret_61 = FUN_003f9c80(arg0, temp_v0_7, temp_ret_56, var_v0_3);
        if ((temp_ret_61 != 0) && (var_v0_2 != 0)) {
            temp_ret_62 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_63 = ObjectList_GetAt_003e9260(temp_ret_62, temp_v0_7);
            temp_ret_64 = (int)FUN_003a92e0((void *)temp_ret_63, &DAT_00518870[0]);
            temp_ret_65 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_64)->_data);
            temp_ret_66 = beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_005190a8[0], temp_ret_65, temp_v0_7);
            beMessenger_AppendString(arg0->_messenger, &DAT_005190b0[0]);
            beMessenger_AppendString(arg0->_messenger, &DAT_005190c0[0]);
            beMessenger_AppendFloat(arg0->_messenger, 1.0f);
            FUN_003e9220(&sp378, &g_vec3Zero[0]);
            beMessenger_AppendVec3(arg0->_messenger, &sp378);
            beMessenger_AppendBool(arg0->_messenger, 0U);
            beMessenger_AppendBool(arg0->_messenger, 1U);
            temp_ret_67 = beMessenger_EnqueueSelected(arg0->_messenger, &DAT_005190d0[0], 1);
        }
        return 1;
    case 10:
        temp_ret_68 = beMessenger_GetInt(arg0->_messenger, 0);
        temp_v0_8 = temp_ret_68;
        temp_ret_69 = beMessenger_GetInt(arg0->_messenger, 1);
        var_s0_3 = 0;
        temp_ret_70 = beMessenger_GetIntCount(arg0->_messenger);
        if (temp_ret_70 == 3) {
            temp_ret_71 = beMessenger_GetInt(arg0->_messenger, 2);
            var_s0_3 = temp_ret_71;
        }
        FUN_003f9e20(arg0, temp_v0_8, temp_ret_69);
        if (var_s0_3 != 0) {
            temp_ret_73 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_74 = ObjectList_GetAt_003e9260(temp_ret_73, temp_v0_8);
            temp_ret_75 = (int)FUN_003a92e0((void *)temp_ret_74, &DAT_00518870[0]);
            temp_ret_76 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_75)->_data);
            temp_ret_77 = beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_005190a8[0], temp_ret_76, temp_v0_8);
            beMessenger_AppendString(arg0->_messenger, &DAT_005190b0[0]);
            beMessenger_AppendString(arg0->_messenger, &DAT_005190c0[0]);
            beMessenger_AppendFloat(arg0->_messenger, 1.0f);
            FUN_003e9220(&sp368, &g_vec3Zero[0]);
            beMessenger_AppendVec3(arg0->_messenger, &sp368);
            beMessenger_AppendBool(arg0->_messenger, 0U);
            beMessenger_AppendBool(arg0->_messenger, 1U);
            temp_ret_78 = beMessenger_EnqueueSelected(arg0->_messenger, &DAT_005190d0[0], 1);
        }
        return 1;
    case 21:
        temp_ret_79 = beMessenger_GetString(arg0->_messenger, 0);
        temp_v0_9 = temp_ret_79;
        var_s0_4 = 0;
        temp_ret_80 = strcmp(temp_v0_9, EXP);
        if (temp_ret_80 == 0) {
            temp_ret_81 = beMessenger_GetString(arg0->_messenger, 1);
            temp_v0_10 = (char *)(temp_ret_81);
            temp_ret_82 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_83 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_v0_11 = temp_ret_83;
            temp_ret_84 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_85 = ObjectList_GetAt_003e9260(temp_ret_84, temp_ret_82);
            temp_ret_86 = (int)igProperty_GetRecord(temp_ret_85, EXP);
            temp_v0_12 = (void *)(temp_ret_86);
            temp_ret_87 = strcmp(temp_v0_10, &DAT_005190e0[0]);
            if (temp_ret_87 == 0) {
                ((beDataObjInt *)temp_v0_12)->_data = temp_v0_11;
            } else {
                temp_ret_88 = strcmp(temp_v0_10, &DAT_005190e8[0]);
                if (temp_ret_88 == 0) {
                    temp_ret_89 = FUN_00406f90((beDataObjInt *)((int) temp_v0_12));
                    ((beDataObjInt *)temp_v0_12)->_data = (int)((int) (temp_v0_11 + temp_ret_89));
                }
            }
        } else {
            temp_ret_90 = strcmp(temp_v0_9, HP);
            if (temp_ret_90 == 0) {
                temp_ret_91 = beMessenger_GetString(arg0->_messenger, 1);
                temp_v0_13 = temp_ret_91;
                temp_ret_92 = beMessenger_GetInt(arg0->_messenger, 0);
                temp_ret_93 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                temp_ret_94 = ObjectList_GetAt_003e9260(temp_ret_93, temp_ret_92);
                temp_v0_14 = (void *)(temp_ret_94);
                temp_ret_95 = strcmp(temp_v0_13, &GETHP[0]);
                if (temp_ret_95 == 0) {
                    temp_ret_96 = (int)igProperty_GetRecord(temp_v0_14, HP);
                    var_s0_4 = ((beDataObjInt *)temp_ret_96)->_data;
                } else {
                    temp_ret_97 = strcmp(temp_v0_13, &DAT_005190f0[0]);
                    if (temp_ret_97 == 0) {
                        temp_ret_98 = (int)igProperty_GetRecord(temp_v0_14, MHP);
                        var_s0_4 = ((beDataObjInt *)temp_ret_98)->_data;
                    }
                }
            } else {
                temp_ret_99 = strcmp(temp_v0_9, MP);
                if (temp_ret_99 == 0) {
                    temp_ret_100 = beMessenger_GetString(arg0->_messenger, 1);
                    temp_v0_15 = temp_ret_100;
                    temp_ret_101 = beMessenger_GetInt(arg0->_messenger, 0);
                    temp_ret_102 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                    temp_ret_103 = ObjectList_GetAt_003e9260(temp_ret_102, temp_ret_101);
                    temp_v0_16 = (void *)(temp_ret_103);
                    temp_ret_104 = strcmp(temp_v0_15, &DAT_005190f8[0]);
                    if (temp_ret_104 == 0) {
                        temp_ret_105 = (int)igProperty_GetRecord(temp_v0_16, MP);
                        var_s0_4 = ((beDataObjInt *)temp_ret_105)->_data;
                    } else {
                        temp_ret_106 = strcmp(temp_v0_15, &DAT_00519100[0]);
                        if (temp_ret_106 == 0) {
                            temp_ret_107 = (int)igProperty_GetRecord(temp_v0_16, MMP);
                            var_s0_4 = ((beDataObjInt *)temp_ret_107)->_data;
                        }
                    }
                }
            }
        }
        beMessenger_ClearInt(arg0->_messenger);
        beMessenger_AppendInt(arg0->_messenger, var_s0_4);
        return 1;
    case 17:
        temp_ret_108 = beMessenger_GetString(arg0->_messenger, 0);
        temp_v0_17 = (char *)(temp_ret_108);
        temp_ret_109 = beMessenger_GetString(arg0->_messenger, 1);
        temp_v0_18 = temp_ret_109;
        temp_ret_110 = beMessenger_GetString(arg0->_messenger, 2);
        temp_v0_19 = (char *)(temp_ret_110);
        temp_ret_111 = beMessenger_GetInt(arg0->_messenger, 0);
        temp_v0_20 = temp_ret_111;
        temp_ret_112 = beMessenger_GetInt(arg0->_messenger, 1);
        temp_v0_21 = temp_ret_112;
        temp_ret_113 = beMessenger_GetInt(arg0->_messenger, 2);
        temp_v0_22 = temp_ret_113;
        temp_ret_114 = beMessenger_GetInt(arg0->_messenger, 3);
        temp_v0_23 = temp_ret_114;
        if (strcmp(temp_v0_18, &DAT_005190e0[0]) == 0) {
            var_s0_5 = 0;
        } else if (strcmp(temp_v0_18, &DAT_00519108[0]) == 0) {
            var_s0_5 = 1;
        } else if (strcmp(temp_v0_18, &DAT_00519110[0]) == 0) {
            var_s0_5 = 2;
        } else if (strcmp(temp_v0_18, &DAT_00519118[0]) == 0) {
            var_s0_5 = 3;
        } else if (strcmp(temp_v0_18, &DAT_00519120[0]) == 0) {
            var_s0_5 = 4;
        } else if (strcmp(temp_v0_18, &DAT_00519128[0]) == 0) {
            var_s0_5 = 5;
        } else if (strcmp(temp_v0_18, &DAT_005190e8[0]) == 0) {
            var_s0_5 = 6;
        } else {
            return 1;
        }
        {
            temp_ret_122 = strcmp(temp_v0_17, &DAT_00519130[0]);
            if (temp_ret_122 == 0) {
                temp_ret_123 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                temp_ret_124 = ObjectList_GetAt_003e9260(temp_ret_123, temp_v0_20);
                temp_ret_125 = (int)igProperty_GetRecordFolder(temp_ret_124, &DAT_00518a40[0]);
                temp_ret_126 = (void *)(FUN_00406f80(&((beDataObjObjectList *)temp_ret_125)->_data));
                temp_v0_24 = (igObjectList *)(temp_ret_126);
                var_s5 = 0;
                if (var_s0_5 != 3) {
                    if (strcmp(temp_v0_19, &DAT_00519138[0]) == 0) {
                        var_s5 = 0;
                    } else if (strcmp(temp_v0_19, &DAT_00519140[0]) == 0) {
                        var_s5 = 1;
                    } else if (strcmp(temp_v0_19, &DAT_00519148[0]) == 0) {
                        var_s5 = 2;
                    } else if (strcmp(temp_v0_19, &DAT_00519150[0]) == 0) {
                        var_s5 = 3;
                    } else {
                        return 1;
                    }
                }
                switch (var_s0_5) {
                case 0:
                    if (temp_v0_24->_count == 0x24) {
                        beMessenger_AppendBool(arg0->_messenger, 0U);
                    } else {
                        switch (var_s5) {
                        case 0:
                            temp_ret_131 = igObject_GetAllocator(arg0);
                            temp_ret_132 = Memory_SelectAllocator_003e9370(&g_ndmwAllocatorSelector[0], temp_ret_131);
                            temp_ret_134 = (void *)(FUN_003c8c90(FUN_00406f70(temp_ret_132).v));
                            { RecoveryRef<1> sp4A8((void *)(temp_ret_134), false);
                            temp_ret_135 = FUN_004482c0(sp4A8.value, temp_v0_21, temp_v0_23, temp_v0_22);
                            temp_ret_136 = ObjectList_AppendRetained(temp_v0_24, sp4A8.value);
                            }
                            break;
                        case 1:
                            temp_ret_137 = igObject_GetAllocator(arg0);
                            temp_ret_138 = Memory_SelectAllocator_003e9370(&g_ndmwAllocatorSelector[0], temp_ret_137);
                            temp_ret_140 = (void *)(FUN_003c8b00(FUN_00406f60(temp_ret_138).v));
                            { RecoveryRef<2> sp4A4((void *)(temp_ret_140), false);
                            temp_ret_141 = FUN_00448410(sp4A4.value, temp_v0_21, temp_v0_23, temp_v0_22);
                            temp_ret_142 = ObjectList_AppendRetained(temp_v0_24, sp4A4.value);
                            }
                            break;
                        case 2:
                            temp_ret_143 = igObject_GetAllocator(arg0);
                            temp_ret_144 = Memory_SelectAllocator_003e9370(&g_ndmwAllocatorSelector[0], temp_ret_143);
                            temp_ret_146 = (void *)(FUN_003c8970(FUN_00406f50(temp_ret_144).v));
                            { RecoveryRef<3> sp4A0((void *)(temp_ret_146), false);
                            temp_ret_147 = FUN_00448560(sp4A0.value, temp_v0_21, temp_v0_22);
                            temp_ret_148 = ObjectList_AppendRetained(temp_v0_24, sp4A0.value);
                            }
                            break;
                        case 3:
                            temp_ret_149 = igObject_GetAllocator(arg0);
                            temp_ret_150 = Memory_SelectAllocator_003e9370(&g_ndmwAllocatorSelector[0], temp_ret_149);
                            temp_ret_152 = (void *)(FUN_003c87f0(FUN_00406f40(temp_ret_150).v));
                            { RecoveryRef<4> sp49C((void *)(temp_ret_152), false);
                            temp_ret_153 = FUN_00448660(sp49C.value, temp_v0_21);
                            temp_ret_154 = ObjectList_AppendRetained(temp_v0_24, sp49C.value);
                            }
                            break;
                        }
                        beMessenger_AppendBool(arg0->_messenger, 1U);
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
                            FUN_00406f20(temp_v0_24, var_s0_6);
                            var_a1 = 1;
                            ((void **)temp_v0_24->_data)[temp_v0_24->_count] = 0; /* matching construct: _data is a 4-byte int reference, indexed as the pointer array the pre-typing struct declared */
                            break;
                        }
                    }
                    beMessenger_AppendBool(arg0->_messenger, var_a1);
                    }
                    goto block_215;
                case 2:
                    {
                    beNDMWItemBase *elem;
                    int cnt = temp_v0_24->_count;
                    for (var_a2 = 0; var_a2 < cnt; ++var_a2) {
                        elem = (beNDMWItemBase *)((void **)temp_v0_24->_data)[var_a2]; /* matching construct: _data is a 4-byte int reference, indexed as the pointer array the pre-typing struct declared */
                        if ((var_s5 == elem->_kindNo) && (temp_v0_21 == elem->_recNo)) {

                            beMessenger_AppendBool(arg0->_messenger, 1U);
                            return 1;
                        }
                    }
                    }
block_129:
                    beMessenger_AppendBool(arg0->_messenger, 0U);
                    goto block_215;
                case 3:
                    if (temp_v0_24->_count == 0x24) {
                        beMessenger_AppendBool(arg0->_messenger, 1U);
                    } else {
                        beMessenger_AppendBool(arg0->_messenger, 0U);
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
                    beMessenger_AppendBool(arg0->_messenger, var_a1_2);
                    }
                    goto block_215;
                }
            } else {
                temp_ret_157 = strcmp(temp_v0_17, &DAT_00519158[0]);
                if (temp_ret_157 == 0) {
                    temp_ret_158 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                    temp_ret_159 = ObjectList_GetAt_003e9260(temp_ret_158, temp_v0_20);
                    temp_ret_160 = (int)igProperty_GetRecordFolder(temp_ret_159, &DAT_00518a50[0]);
                    temp_ret_161 = (void *)(FUN_00406f80(&((beDataObjObjectList *)temp_ret_160)->_data));
                    temp_v0_25 = (void *)(temp_ret_161);
                    switch (var_s0_5) {
                    case 0:
                        temp_ret_162 = FUN_00448050(temp_v0_25, temp_v0_21);
                        temp_ret_163 = ObjectList_GetAt_003e9260(temp_v0_25, temp_ret_162);
                        temp_v0_26 = (beNDMWItemDisk *)(temp_ret_163);
                        temp_a0_4 = temp_v0_26->_kazu;
                        if (temp_a0_4 == 9) {
                            beMessenger_AppendBool(arg0->_messenger, 0U);
                        } else {
                            temp_a0_5 = temp_a0_4 + temp_v0_23;
                            if (temp_a0_5 < 0xA) {
                                temp_v0_26->_kazu = temp_a0_5;
                            } else {
                                temp_v0_26->_kazu = 9;
                            }
                            beMessenger_AppendBool(arg0->_messenger, 1U);
                        }
                        break;
                    case 1:
                        temp_ret_164 = FUN_00448050(temp_v0_25, temp_v0_21);
                        temp_ret_165 = ObjectList_GetAt_003e9260(temp_v0_25, temp_ret_164);
                        temp_v0_27 = (beNDMWItemDisk *)(temp_ret_165);
                        temp_v1 = temp_v0_27->_kazu;
                        if (temp_v1 == 0) {
                            beMessenger_AppendBool(arg0->_messenger, 0U);
                        } else {
                            temp_v1_2 = temp_v1 - temp_v0_23;
                            if (temp_v1_2 >= 0) {
                                temp_v0_27->_kazu = temp_v1_2;
                            } else {
                                temp_v0_27->_kazu = 0;
                            }
                            beMessenger_AppendBool(arg0->_messenger, 1U);
                        }
                        break;
                    case 2:
                        temp_ret_166 = FUN_00448050(temp_v0_25, temp_v0_21);
                        temp_ret_167 = ObjectList_GetAt_003e9260(temp_v0_25, temp_ret_166);
                        if (((beNDMWItemDisk *)temp_ret_167)->_kazu != 0) {
                            beMessenger_AppendBool(arg0->_messenger, 1U);
                        } else {
                            beMessenger_AppendBool(arg0->_messenger, 0U);
                        }
                        break;
                    case 3:
                        temp_ret_168 = FUN_00448050(temp_v0_25, temp_v0_21);
                        temp_ret_169 = ObjectList_GetAt_003e9260(temp_v0_25, temp_ret_168);
                        if (((beNDMWItemDisk *)temp_ret_169)->_kazu == 9) {
                            beMessenger_AppendBool(arg0->_messenger, 1U);
                        } else {
                            beMessenger_AppendBool(arg0->_messenger, 0U);
                        }
                        break;
                    }
                    goto block_215;
                }
                temp_ret_170 = strcmp(temp_v0_17, &DAT_00518798[0]);
                if (temp_ret_170 == 0) {
                    temp_ret_171 = (void *)(FUN_00407040(&arg0->_commonDataList));
                    temp_ret_172 = (int)igProperty_GetRecordArray(temp_ret_171, &DAT_005187a0[0]);
                    temp_ret_173 = (void *)(FUN_00406f10(&((beDataObjBoolList *)temp_ret_172)->_data));
                    temp_v0_28 = (void *)(temp_ret_173);
                    switch (var_s0_5) {
                    case 0:
                        temp_ret_174 = (unsigned char *)(FUN_00406f00((igUnsignedCharList *)temp_v0_28));
                        if (*(unsigned char *)(temp_ret_174 + temp_v0_21) != 0) {
                            beMessenger_AppendBool(arg0->_messenger, 0U);
                        } else {
                            temp_v0_29 = ((igBoolList *)temp_v0_28)->_count;
                            if ((temp_v0_29 != 0) && (temp_v0_21 >= 0) && (temp_v0_21 < temp_v0_29)) {
                                temp_s0 = GPR_005549f0;
                                temp_ret_175 = (unsigned char *)(FUN_00406f00((igUnsignedCharList *)temp_v0_28));
                                *(unsigned char *)(temp_v0_21 + (int)temp_ret_175) = temp_s0;
                            }
                            beMessenger_AppendBool(arg0->_messenger, 1U);
                        }
                        break;
                    case 1:
                        temp_ret_176 = (unsigned char *)(FUN_00406f00((igUnsignedCharList *)temp_v0_28));
                        if (*(unsigned char *)(temp_ret_176 + temp_v0_21) == 0) {
                            beMessenger_AppendBool(arg0->_messenger, 0U);
                        } else {
                            temp_v0_30 = ((igBoolList *)temp_v0_28)->_count;
                            if ((temp_v0_30 != 0) && (temp_v0_21 >= 0) && (temp_v0_21 < temp_v0_30)) {
                                temp_s0_2 = GPR_005549f4;
                                temp_ret_177 = (unsigned char *)(FUN_00406f00((igUnsignedCharList *)temp_v0_28));
                                *(unsigned char *)(temp_v0_21 + (int)temp_ret_177) = temp_s0_2;
                            }
                            beMessenger_AppendBool(arg0->_messenger, 1U);
                        }
                        break;
                    case 2:
                        temp_ret_178 = (unsigned char *)(FUN_00406f00((igUnsignedCharList *)temp_v0_28));
                        beMessenger_AppendBool(arg0->_messenger, *(unsigned char *)(temp_ret_178 + temp_v0_21));
                        break;
                    }
                    goto block_215;
                }
                temp_ret_179 = strcmp(temp_v0_17, &DAT_00518840[0]);
                if (temp_ret_179 == 0) {
                    temp_ret_180 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                    temp_ret_181 = ObjectList_GetAt_003e9260(temp_ret_180, temp_v0_20);
                    temp_v0_31 = (void *)(temp_ret_181);
                    switch (var_s0_5) {
                    case 0:
                        temp_ret_182 = (int)igProperty_GetRecord(temp_v0_31, &DAT_00518840[0]);
                        ((beDataObjInt *)temp_ret_182)->_data = temp_v0_21;
                        break;
                    case 5:
                        beMessenger_ClearInt(arg0->_messenger);
                        temp_ret_183 = (int)igProperty_GetRecord(temp_v0_31, &DAT_00518840[0]);
                        beMessenger_AppendInt(arg0->_messenger, ((beDataObjInt *)temp_ret_183)->_data);
                        break;
                    case 6:
                        temp_ret_184 = (int)igProperty_GetRecord(temp_v0_31, &DAT_00518840[0]);
                        var_s0_7 = temp_v0_21 + ((beDataObjInt *)temp_ret_184)->_data;
                        if (var_s0_7 < 0) {
                            var_s0_7 = 0;
                        } else if (var_s0_7 > 0x98967F) {
                            var_s0_7 = 0x98967F;
                        }
                        temp_ret_185 = (int)igProperty_GetRecord(temp_v0_31, &DAT_00518840[0]);
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
        temp_ret_186 = beMessenger_GetBool(arg0->_messenger, 0);
        arg0->_isDispFightData = temp_ret_186;
        return 1;
    case 18:
        temp_ret_187 = beMessenger_GetString(arg0->_messenger, 0);
        temp_v0_32 = temp_ret_187;
        { StringRef sp498(temp_v0_32 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_32));
        temp_ret_190 = (void *)(FightCom_GetMetaEnum());
        temp_ret_191 = (const char *)FUN_00407050((int *)&sp498.p);
        unsigned int sp494;
        igMetaEnum_GetValueByName(temp_ret_190, temp_ret_191, &sp494);
        switch (sp494) {
        case 1:
            temp_ret_193 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_194 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_195 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_196 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
            temp_v0_33 = (beNDMWMdlPEBaseInfoWork *)(temp_ret_196);
            switch (temp_ret_195 / 10000) {
            case 4:
                beMessenger_AppendBool(arg0->_messenger, 1U);
                            break;
            default:
                temp_ret_197 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                temp_ret_198 = ObjectList_GetAt_003e9260(temp_ret_197, temp_ret_193);
                temp_v0_34 = (void *)(temp_ret_198);
                temp_ret_199 = (int)igProperty_GetRecord(temp_v0_34, &DAT_00518a30[0]);
                temp_s3 = ((beDataObjInt *)temp_ret_199)->_data;
                temp_ret_200 = (int)igProperty_GetRecord(temp_v0_34, &DAT_005188d8[0]);
                temp_s1 = ((beDataObjInt *)temp_ret_200)->_data;
                temp_ret_201 = (int)FUN_003a9250(temp_v0_34, SKILL);
                temp_ret_202 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_201)->_data));
                temp_ret_203 = DataList_GetData_003e9090(temp_ret_202);
                temp_s3 = *(int *)(temp_ret_203 + (temp_s3 * 4));
                temp_ret_204 = (int)igProperty_GetRecord(temp_v0_34, &DAT_00518950[0]);
                temp_s0_3 = ((beDataObjInt *)temp_ret_204)->_data;
                temp_ret_205 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                if (temp_ret_205 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                    temp_ret_206 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_207 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_206));
                }
                temp_ret_208 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                temp_ret_209 = beDataBase_GetRecordInt(temp_ret_208, temp_ret_194, &DAT_005188d8[0]);
                temp_ret_210 = (void *)(FUN_00406ef0(&temp_v0_33->_downDataList));
                if (temp_ret_210 == 0) {
                    var_s5_2 = 0;
                } else {
                    temp_ret_211 = (void *)(FUN_00406ef0(&temp_v0_33->_downDataList));
                    temp_ret_212 = DataList_GetData_003e9090(temp_ret_211);
                    var_s5_2 = ((int *)temp_ret_212)[3];
                }
                temp_ret_213 = (void **)(FUN_00406e50(&((beSystem *)arg0->_system)->_random));
                temp_v0_35 = (void **)(temp_ret_213);
                temp_a2_3 = ((DW4VC_96_0 *)(temp_v0_35))->vX() % 10000U;
                if ((int) temp_a2_3 < ((int) (temp_s0_3 * ((temp_s1 * 0x1E) + (temp_s3 * 0x14) + 0x1770)) / (int) ((int) (temp_ret_209 * (0x64 - var_s5_2)) / 100))) {
                    beMessenger_AppendBool(arg0->_messenger, 1U);
                } else {
                    beMessenger_AppendBool(arg0->_messenger, 0U);
                }
                            break;
            }
            break;
        case 2:
            temp_ret_214 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_215 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_216 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_217 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_218 = ObjectList_GetAt_003e9260(temp_ret_217, temp_ret_214);
            temp_v0_36 = (void *)(temp_ret_218);
            if ((temp_ret_216 / 10000) != 4) {
                temp_ret_219 = (int)igProperty_GetRecord(temp_v0_36, &DAT_00518960[0]);
                temp_s0_4 = ((beDataObjInt *)temp_ret_219)->_data;
                temp_ret_220 = (void **)(FUN_00406e50(&((beSystem *)arg0->_system)->_random));
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
                beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_36, temp_a2_4, &sp490);
                temp_ret_221 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                if (temp_ret_221 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                    temp_ret_222 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_223 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_222));
                }
                temp_ret_224 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                temp_ret_225 = (char *)(beDataBase_GetRecordString(temp_ret_224, sp490, &DAT_00519018[0]));
                temp_v0_39 = (char *)(temp_ret_225);
                temp_ret_226 = strcmp(temp_v0_39, &DAT_00518fa8[0]);
                if (temp_ret_226 == 0) {
                    var_s0_8 = 0;
                } else {
                    temp_ret_227 = strcmp(temp_v0_39, &DAT_00518fb0[0]);
                    if (temp_ret_227 == 0) {
                        var_s0_8 = 1;
                    } else {
                        temp_ret_228 = strcmp(temp_v0_39, &DAT_00518fb8[0]);
                        if (temp_ret_228 == 0) {
                            var_s0_8 = 2;
                        } else {
                            temp_ret_229 = strcmp(temp_v0_39, &DAT_00518fc0[0]);
                            if (temp_ret_229 == 0) {
                                var_s0_8 = 3;
                            } else {
                                temp_ret_230 = strcmp(temp_v0_39, &DAT_00519160[0]);
                                if (temp_ret_230 == 0) {
                                    var_s0_8 = 4;
                                } else {
                                    var_s0_8 = -1;
                                }
                            }
                        }
                    }
                }
                temp_ret_231 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                if (temp_ret_231 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                    temp_ret_232 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_233 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_232));
                }
                temp_ret_234 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                temp_ret_235 = beDataBase_GetRecordInt(temp_ret_234, sp490, &DAT_00518960[0]);
                temp_v0_40 = temp_ret_235;
                if (var_s0_8 >= 0) {
                    if (var_s0_8 >= 0) {
                        temp_ret_236 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        if (temp_ret_236 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                            temp_ret_237 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_238 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_237));
                        }
                        temp_ret_239 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        temp_ret_240 = beDataBase_GetRecordInt(temp_ret_239, temp_ret_215, DAT_004cf360[var_s0_8]);
                        var_s0_9 = temp_ret_240;
                    } else {
                        var_s0_9 = 0;
                    }
                    temp_ret_241 = (void **)(FUN_00406e50(&((beSystem *)arg0->_system)->_random));
                    temp_v0_41 = (void **)(temp_ret_241);
                    temp_a4 = ((DW4VC_96_0 *)(temp_v0_41))->vX() % 1000U;
                    if ((int) temp_a4 < ((int) ((temp_v0_40 + 0x64) * (0x2710 / (int) (((int) (var_s0_9 * 0xC) / 10) + 0x32))) / 100)) {
                        var_a1_3 = 1;
                    } else {
                        var_a1_3 = 0;
                    }
                } else {
                    temp_ret_242 = (void **)(FUN_00406e50(&((beSystem *)arg0->_system)->_random));
                    temp_v0_42 = (void **)(temp_ret_242);
                    temp_v0_43 = ((DW4VC_96_0 *)(temp_v0_42))->vX() % 100U;
                    if ((int) temp_v0_43 < temp_v0_40) {
                        var_a1_3 = 1;
                    } else {
                        var_a1_3 = 0;
                    }
                }
            }
            beMessenger_AppendBool(arg0->_messenger, var_a1_3);
            break;
        case 5:
            temp_ret_243 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_v0_44 = temp_ret_243;
            temp_ret_244 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_v0_45 = temp_ret_244;
            temp_ret_245 = beMessenger_GetInt(arg0->_messenger, 2);
            sp12C = beMessenger_GetInt(arg0->_messenger, 3);
            temp_ret_247 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
            temp_v0_46 = (beNDMWMdlPEBaseInfoWork *)(temp_ret_247);
            temp_ret_248 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_249 = ObjectList_GetAt_003e9260(temp_ret_248, temp_v0_44);
            temp_v0_47 = (void *)(temp_ret_249);
            var_s1 = -1;
            switch (temp_ret_245 / 10000) {
            default: {
                temp_ret_250 = (int)igProperty_GetRecord(temp_v0_47, &DAT_00518a30[0]);
                temp_s0_5 = ((beDataObjInt *)temp_ret_250)->_data;
                temp_ret_251 = (int)igProperty_GetRecord(temp_v0_47, &DAT_005188b0[0]);
                temp_s2 = ((beDataObjInt *)temp_ret_251)->_data;
                temp_ret_252 = (int)FUN_003a9250(temp_v0_47, SKILL);
                temp_ret_253 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_252)->_data));
                temp_ret_254 = DataList_GetData_003e9090(temp_ret_253);
                var_s0 = *(int *)(temp_ret_254 + (temp_s0_5 * 4));
                temp_ret_255 = (void *)(FUN_00406ef0(&temp_v0_46->_downDataList));
                if (temp_ret_255 == 0) {
                    var_s7 = 0;
                } else {
                    temp_ret_256 = (void *)(FUN_00406ef0(&temp_v0_46->_downDataList));
                    temp_ret_257 = DataList_GetData_003e9090(temp_ret_256);
                    var_s7 = ((int *)temp_ret_257)[5];
                }
                temp_ret_258 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                if (temp_ret_258 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                    temp_ret_259 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_260 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_259));
                }
                temp_ret_261 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                temp_ret_262 = beDataBase_GetRecordInt(temp_ret_261, temp_v0_45, &DAT_005188b8[0]);
                var_s7 = temp_ret_262 - var_s7;
                var_s2_2 = (int)((int) ((temp_s2 * 6) + (var_s0 * 4)) / var_s7);
                if (var_s2_2 < 0) {
                    var_s2_2 = 0;
                } else if (var_s2_2 > 0x1869F) {
                    var_s2_2 = 0x1869F;
                }
                if (var_s2_2 != 0) {
                    temp_ret_263 = (int)igProperty_GetRecord(temp_v0_47, &DAT_005189f0[0]);
                    var_s1 = ((beDataObjInt *)temp_ret_263)->_data;
                    if (var_s1 != -1) {
                        temp_ret_264 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        if (temp_ret_264 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                            temp_ret_265 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_266 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_265));
                        }
                        temp_ret_267 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        temp_ret_268 = beDataBase_GetRecordInt(temp_ret_267, temp_v0_45, DAT_004cf380[var_s1]);
                        temp_v0_48 = temp_ret_268;
                        temp_ret_269 = (void **)(FUN_00406e50(&((beSystem *)arg0->_system)->_random));
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
                beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_47, temp_a2_5, &sp48C);
                temp_ret_270 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                if (temp_ret_270 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                    temp_ret_271 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_272 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_271));
                }
                temp_ret_273 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                temp_ret_274 = beDataBase_GetRecordInt(temp_ret_273, sp48C, HP);
                temp_v0_51 = (int)(0U - (unsigned int)temp_ret_274);
                if (temp_v0_51 != 0) {
                    temp_ret_275 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_275 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_276 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_277 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_276));
                    }
                    temp_ret_278 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_279 = beDataBase_GetRecordInt(temp_ret_278, sp48C, SKILL);
                    temp_ret_280 = (int)FUN_003a9250(temp_v0_47, SKILL);
                    temp_ret_281 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_280)->_data));
                    temp_ret_282 = DataList_GetData_003e9090(temp_ret_281);
                    var_s0 = *(int *)(temp_ret_282 + (temp_ret_279 * 4));
                    temp_ret_283 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    if (temp_ret_283 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                        temp_ret_284 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_285 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_284));
                    }
                    temp_ret_286 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    temp_ret_287 = beDataBase_GetRecordInt(temp_ret_286, temp_v0_45, &DAT_005188d0[0]);
                    temp_ret_288 = (int)igProperty_GetRecord(temp_v0_47, &DAT_005188c0[0]);
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
                    temp_ret_289 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_289 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_290 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_291 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_290));
                    }
                    temp_ret_292 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_293 = (char *)(beDataBase_GetRecordString(temp_ret_292, sp48C, &DAT_00519018[0]));
                    temp_v0_52 = (char *)(temp_ret_293);
                    temp_ret_294 = strcmp(temp_v0_52, &DAT_00518fa8[0]);
                    if (temp_ret_294 == 0) {
                        var_s1 = 0;
                    } else {
                        temp_ret_295 = strcmp(temp_v0_52, &DAT_00518fb0[0]);
                        if (temp_ret_295 == 0) {
                            var_s1 = 1;
                        } else {
                            temp_ret_296 = strcmp(temp_v0_52, &DAT_00518fb8[0]);
                            if (temp_ret_296 == 0) {
                                var_s1 = 2;
                            } else {
                                temp_ret_297 = strcmp(temp_v0_52, &DAT_00518fc0[0]);
                                if (temp_ret_297 == 0) {
                                    var_s1 = 3;
                                } else {
                                    temp_ret_298 = strcmp(temp_v0_52, &DAT_00519160[0]);
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
                        temp_ret_299 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        if (temp_ret_299 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                            temp_ret_300 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_301 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_300));
                        }
                        temp_ret_302 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        temp_ret_303 = beDataBase_GetRecordInt(temp_ret_302, temp_v0_45, DAT_004cf360[var_s1]);
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
                    temp_ret_304 = (void **)(FUN_00406e50(&((beSystem *)arg0->_system)->_random));
                    temp_v0_53 = (void **)(temp_ret_304);
                    temp_s0_6 = ((DW4VC_96_0 *)(temp_v0_53))->vX() & 3;
                    temp_ret_305 = (void **)(FUN_00406e50(&((beSystem *)arg0->_system)->_random));
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
                    temp_ret_306 = (int)igProperty_GetRecord(temp_v0_47, &DAT_00518a00[0]);
                    temp_v0_59 = ((beDataObjInt *)temp_ret_306)->_data;
                    if (temp_v0_59 != 0) {
                        temp_ret_307 = FUN_003f9c80(arg0, temp_v0_44, (int) (var_s2_2 * temp_v0_59) / 100, -1);
                    }
                    temp_ret_308 = (int)igProperty_GetRecord(temp_v0_47, &DAT_00518a08[0]);
                    temp_v0_60 = ((beDataObjInt *)temp_ret_308)->_data;
                    if (temp_v0_60 != 0) {
                        FUN_003f9e20(arg0, temp_v0_44, (int) (var_s2_2 * temp_v0_60) / 100);
                    }
                break; }
                case 4: break;
                }
            }
            beMessenger_ClearInt(arg0->_messenger);
            beMessenger_AppendInt(arg0->_messenger, var_s2_2);
            beMessenger_AppendInt(arg0->_messenger, var_s1);
            beMessenger_AppendInt(arg0->_messenger, var_s3_2);
            break;
        case 21:
            temp_ret_310 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_311 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_312 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_313 = ObjectList_GetAt_003e9260(temp_ret_312, temp_ret_310);
            temp_v0_61 = (void *)(temp_ret_313);
            switch (temp_ret_311 / 10000) {
            default: {
                temp_ret_314 = (int)igProperty_GetRecord(temp_v0_61, &DAT_005189f0[0]);
                var_s0_10 = ((beDataObjInt *)temp_ret_314)->_data;
            break; }
            case 4: {
                temp_a2_6 = (int)((int) temp_ret_311 % 10000);
                int sp488;
                beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_61, temp_a2_6, &sp488);
                temp_ret_315 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                if (temp_ret_315 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                    temp_ret_316 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_317 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_316));
                }
                temp_ret_318 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                temp_ret_319 = (char *)(beDataBase_GetRecordString(temp_ret_318, sp488, &DAT_00519018[0]));
                temp_v0_62 = (char *)(temp_ret_319);
                temp_ret_320 = strcmp(temp_v0_62, &DAT_00518fa8[0]);
                if (temp_ret_320 == 0) {
                    var_s0_10 = 0;
                } else {
                    temp_ret_321 = strcmp(temp_v0_62, &DAT_00518fb0[0]);
                    if (temp_ret_321 == 0) {
                        var_s0_10 = 1;
                    } else {
                        temp_ret_322 = strcmp(temp_v0_62, &DAT_00518fb8[0]);
                        if (temp_ret_322 == 0) {
                            var_s0_10 = 2;
                        } else {
                            temp_ret_323 = strcmp(temp_v0_62, &DAT_00518fc0[0]);
                            if (temp_ret_323 == 0) {
                                var_s0_10 = 3;
                            } else {
                                temp_ret_324 = strcmp(temp_v0_62, &DAT_00519160[0]);
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
            beMessenger_ClearInt(arg0->_messenger);
            beMessenger_AppendInt(arg0->_messenger, var_s0_10);
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
            temp_ret_325 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_v0_63 = temp_ret_325;
            temp_ret_326 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_327 = beMessenger_GetInt(arg0->_messenger, 2);
            sp128 = beMessenger_GetInt(arg0->_messenger, 3);
            temp_ret_329 = (void *)(FUN_00407030(&arg0->_playerDataListList));
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
                temp_ret_332 = (int)igProperty_GetRecord(skp, &DAT_00518a30[0]);
                var_s5_3 = ((beDataObjInt *)temp_ret_332)->_data;
                temp_ret_333 = (int)FUN_003a9250(skp, SKILL);
                temp_ret_334 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_333)->_data));
                temp_ret_335 = DataList_GetData_003e9090(temp_ret_334);
                var_s7_2 = *(int *)(temp_ret_335 + (var_s5_3 * 4));
            } else {
                temp_a2_7 = (int)((int) temp_ret_326 % 10000);
                int sp484;
                beNDMWGameRam_FindTechniqueRow(arg0, skp, temp_a2_7, &sp484);
                temp_ret_336 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                if (temp_ret_336 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                    temp_ret_337 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_338 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_337));
                }
                temp_ret_339 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                temp_ret_340 = beDataBase_GetRecordInt(temp_ret_339, sp484, SKILL);
                var_s5_3 = temp_ret_340;
                temp_ret_341 = (int)FUN_003a9250(skp, SKILL);
                temp_ret_342 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_341)->_data));
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
                skptr = (short *)(DAT_004cf590);
                /* `value <= *p` (not `*p >= value`) keeps the compare as slt at / bnez at. */
                for (skcnt = 0; skcnt < 0x15; skcnt++, skptr++) {
                    if (var_s7_2 <= *skptr) {
                        skband = skcnt;
                        break;
                    }
                }
                temp_s1_3 = DAT_004cf390[skgrp][skband][skhard];
                /* A switch with the default arm first, rather than a != chain, places the nop
                 * after the third beq. */
                switch (skcls) {
                default: {
                    temp_ret_344 = (int)igProperty_GetRecord(skp, DIGIMONNO_2);
                    temp_s0_8 = ((beDataObjInt *)temp_ret_344)->_data;
                    temp_ret_345 = (void *)(FUN_00406ee0(&arg0->_dBShinka));
                    if (temp_ret_345 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519438[0], &DAT_00519430[0], 0, &DAT_00519420[0]);
                        temp_ret_346 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_347 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBShinka, (ObjectRefTarget *)temp_ret_346));
                    }
                    temp_ret_348 = (void *)(FUN_00406ee0(&arg0->_dBShinka));
                    temp_ret_349 = beDataBase_GetRecordInt(temp_ret_348, temp_s0_8, DAT_004cf5c0[var_s5_3]);
                    var_s0_11 = (int)((int) (temp_s1_3 * temp_ret_349 * 0x1F4) / 1000);
                break; }
                case 4: case 8: case 9:
                    var_s0_11 = temp_s1_3 * 0x64;
                    break;
                }
                temp_ret_350 = (void **)(FUN_00406e50(&((beSystem *)arg0->_system)->_random));
                temp_v0_65 = (void **)(temp_ret_350);
                temp_v0_66 = ((DW4VC_96_0 *)(temp_v0_65))->vX() % 100000U;
                if ((int) temp_v0_66 < var_s0_11) {
                    int skill_next = var_s7_2 + 1;
                    temp_ret_351 = (int)FUN_003a9250(skp, SKILL);
                    temp_ret_352 = (void *)(FUN_00406e40((int *)temp_ret_351));
                    temp_v0_67 = (void *)(temp_ret_352);
                    temp_v1_3 = ((igIntList *)temp_v0_67)->_count;
                    if ((temp_v1_3 != 0) && (var_s5_3 >= 0) && (var_s5_3 < temp_v1_3)) {
                        temp_ret_353 = DataList_GetData_003e9090(temp_v0_67);
                        *(int *)(temp_ret_353 + (var_s5_3 * 4)) = skill_next;
                    }
                    FUN_003fab90(arg0, temp_v0_63, 1);
                    FUN_003f8760(arg0, temp_v0_63);
                    temp_ret_356 = (int)FUN_003a92e0(skp, &DAT_00518870[0]);
                    temp_ret_357 = (char *)(FUN_00407050(&((beDataObjString *)temp_ret_356)->_data));
                    temp_ret_358 = beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_00519168[0], temp_ret_357, temp_v0_63);
                    beMessenger_AppendString(arg0->_messenger, &DAT_00519178[0]);
                    beMessenger_AppendString(arg0->_messenger, &DAT_00519188[0]);
                    beMessenger_AppendFloat(arg0->_messenger, 1.0f);
                    FUN_003e9220(&sp358, &g_vec3Zero[0]);
                    beMessenger_AppendVec3(arg0->_messenger, &sp358);
                    beMessenger_AppendBool(arg0->_messenger, 0U);
                    beMessenger_AppendBool(arg0->_messenger, 1U);
                    temp_ret_359 = beMessenger_EnqueueSelected(arg0->_messenger, &DAT_005190d0[0], 1);
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
            temp_ret_360 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_361 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_362 = (void *)(FUN_00407040(&arg0->_commonDataList));
            temp_ret_363 = (int)igProperty_GetRecord(temp_ret_362, &DAT_00518760[0]);
            temp_s6 = ((beDataObjInt *)temp_ret_363)->_data;
            expup_idx = 0;
            sp124 = 0;
            do {
                temp_ret_364 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                temp_ret_365 = ObjectList_GetAt_003e9260(temp_ret_364, expup_idx);
                expup_player = (void *)(temp_ret_365);
                temp_ret_366 = (beDataObjBool *)(igProperty_GetRecordByte((int)expup_player, &DAT_00518888[0]));
                if (temp_ret_366->_data != 0) {
                    temp_ret_367 = (int)igProperty_GetRecord(expup_player, HP);
                    if (((beDataObjInt *)temp_ret_367)->_data != 0) {
                        temp_ret_368 = (int)igProperty_GetRecord(expup_player, LEVEL_2);
                        expup_level = ((beDataObjInt *)temp_ret_368)->_data;
                        if (expup_level != 0x3E7) {
                            temp_ret_369 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                            if (temp_ret_369 == 0) {
                                beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                                temp_ret_370 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                                temp_ret_371 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_370));
                            }
                            temp_ret_372 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                            temp_ret_373 = beDataBase_GetRecordInt(temp_ret_372, temp_ret_361, EXP);
                            var_s0_12 = temp_ret_373;
                            temp_ret_374 = (int)igProperty_GetRecord(expup_player, &DAT_005189d0[0]);
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
                            temp_ret_377 = (int)igProperty_GetRecord(expup_player, &DAT_00518938[0]);
                            if (((beDataObjInt *)temp_ret_377)->_data <= expup_exp) {
loop_449:
                                expup_level += 1;
                                temp_ret_378 = (int)igProperty_GetRecord(expup_player, LEVEL_2);
                                ((beDataObjInt *)temp_ret_378)->_data = expup_level;
                                FUN_003fab90(arg0, expup_idx, 1);
                                FUN_003f8760(arg0, expup_idx);
                                leveled_up = true;
                                if (expup_level != 0x3E7) {
                                    temp_ret_381 = (int)igProperty_GetRecord(expup_player, &DAT_00518938[0]);
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
                                temp_ret_384 = (int)FUN_003a92e0(expup_player, &DAT_00518870[0]);
                                temp_ret_385 = (char *)(FUN_00407050(&((beDataObjString *)temp_ret_384)->_data));
                                temp_ret_386 = beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_00519168[0], temp_ret_385, expup_idx);
                                beMessenger_AppendString(arg0->_messenger, &DAT_00519178[0]);
                                beMessenger_AppendString(arg0->_messenger, &DAT_00519198[0]);
                                beMessenger_AppendFloat(arg0->_messenger, 1.0f);
                                FUN_003e9220(&sp348, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(arg0->_messenger, &sp348);
                                beMessenger_AppendBool(arg0->_messenger, 0U);
                                beMessenger_AppendBool(arg0->_messenger, 1U);
                                temp_ret_387 = beMessenger_EnqueueSelected(arg0->_messenger, &DAT_005190d0[0], 1);
                                temp_ret_388 = (int)igProperty_GetRecord(expup_player, HP);
                                ((beDataObjInt *)temp_ret_388)->_data = temp_s0_10;
                                temp_ret_389 = (int)igProperty_GetRecord(expup_player, MP);
                                ((beDataObjInt *)temp_ret_389)->_data = temp_s5;
                                temp_ret_390 = beMessenger_PrepareDelayedSelection(arg0->_messenger, NUMBERCTRL, &DAT_005191a0[0], expup_idx);
                                beMessenger_AppendInt(arg0->_messenger, expup_level);
                                temp_ret_391 = beMessenger_EnqueueSelected(arg0->_messenger, SETVALUE, 1);
                                temp_ret_392 = beMessenger_PrepareDelayedSelection(arg0->_messenger, METERCTRL, hpmt, expup_idx);
                                beMessenger_AppendFloat(arg0->_messenger, 100.0f);
                                temp_ret_393 = beMessenger_EnqueueSelected(arg0->_messenger, SETPERCENT, 1);
                                temp_ret_394 = beMessenger_PrepareDelayedSelection(arg0->_messenger, NUMBERCTRL, hpnm, expup_idx);
                                beMessenger_AppendInt(arg0->_messenger, temp_s0_10);
                                temp_ret_395 = beMessenger_EnqueueSelected(arg0->_messenger, SETVALUE, 1);
                                temp_ret_396 = beMessenger_PrepareDelayedSelection(arg0->_messenger, METERCTRL, mpmt, expup_idx);
                                beMessenger_AppendFloat(arg0->_messenger, 100.0f);
                                temp_ret_397 = beMessenger_EnqueueSelected(arg0->_messenger, SETPERCENT, 1);
                                temp_ret_398 = beMessenger_PrepareDelayedSelection(arg0->_messenger, NUMBERCTRL, mpnm, expup_idx);
                                beMessenger_AppendInt(arg0->_messenger, temp_s5);
                                temp_ret_399 = beMessenger_EnqueueSelected(arg0->_messenger, SETVALUE, 1);
                            }
                        }
                    }
                }
                expup_idx += 1;
            } while (expup_idx < 4);
            beMessenger_ClearInt(arg0->_messenger);
            beMessenger_AppendInt(arg0->_messenger, sp124);
            break;
        case 14: {
            temp_ret_400 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_401 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_402 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_v0_72 = temp_ret_402;
            temp_ret_403 = beMessenger_GetInt(arg0->_messenger, 3);
            temp_v0_73 = temp_ret_403;
            temp_ret_404 = beMessenger_GetInt(arg0->_messenger, 4);
            temp_ret_405 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_406 = ObjectList_GetAt_003e9260(temp_ret_405, temp_ret_400);
            temp_ret_407 = (int)igProperty_GetRecord(temp_ret_406, &DAT_00518970[0]);
            int stun_base = ((beDataObjInt *)temp_ret_407)->_data;
            temp_ret_408 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
            if (temp_ret_408 == 0) {
                beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                temp_ret_409 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                temp_ret_410 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_409));
            }
            temp_ret_411 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
            temp_ret_412 = beDataBase_GetRecordInt(temp_ret_411, temp_ret_401, &DAT_005191a8[0]);
            temp_v0_74 = temp_ret_412;
            temp_ret_413 = (void **)(FUN_00406e50(&((beSystem *)arg0->_system)->_random));
            temp_v0_75 = (void **)(temp_ret_413);
            temp_a0_7 = ((DW4VC_96_0 *)(temp_v0_75))->vX() % 100U;
            var_s1_3 = 0;
            temp_v1_6 = (stun_base + ((int) (temp_v0_73 * 0x32) / temp_v0_72) + 0x64) - temp_v0_74;
            var_v0_9 = temp_v1_6 / 2;
            if ((int) temp_a0_7 < var_v0_9) {
                var_s1_3 = (int)((int) ((0xC8 - temp_v0_74) * (((int) (temp_v0_73 * 0x1E) / temp_v0_72) + (stun_base * 3))) / 400);
            }
            beMessenger_ClearInt(arg0->_messenger);
            beMessenger_AppendInt(arg0->_messenger, var_s1_3);
            break; }
        case 15:
            temp_ret_414 = (char *)(beMessenger_GetString(arg0->_messenger, 1));
            temp_v0_76 = (char *)(temp_ret_414);
            { StringRef sp480(temp_v0_76 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_76));
            temp_ret_417 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_418 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_419 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_v0_77 = temp_ret_419;
            temp_ret_420 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_421 = ObjectList_GetAt_003e9260(temp_ret_420, temp_ret_417);
            temp_v0_78 = (void *)(temp_ret_421);
            temp_ret_422 = strcmp(sp480.p, &DAT_005191b8[0]);
            if (temp_ret_422 == 0) {
                int sp47C;
                sp47C = 0;
                temp_a2_8 = temp_v0_77 % 10000;
                var_s2_3 = 0;
                beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_78, temp_a2_8, &sp47C);
                temp_ret_423 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                if (temp_ret_423 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                    temp_ret_424 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_425 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_424));
                }
                temp_ret_426 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                temp_ret_427 = beDataBase_GetRecordInt(temp_ret_426, sp47C, SKILL);
                temp_ret_428 = (int)FUN_003a9250(temp_v0_78, SKILL);
                temp_ret_429 = (void *)(FUN_00406ef0((int *)(temp_ret_428 + 0xC)));
                temp_ret_430 = DataList_GetData_003e9090(temp_ret_429);
                temp_s1_4 = ((int *)temp_ret_430)[temp_ret_427];
                temp_ret_431 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                if (temp_ret_431 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                    temp_ret_432 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_433 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_432));
                }
                temp_ret_434 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                temp_ret_435 = beDataBase_GetRecordInt(temp_ret_434, temp_ret_418, &DAT_00519020[0]);
                temp_v0_79 = temp_ret_435;
                if (temp_s1_4 < 0x3E9) {
                    var_v1_7 = temp_s1_4 / 4;
                    var_s1_4 = (int)((int) ((var_v1_7 + 0x2EE) * (0x3E8 - temp_v0_79)) / 1000);
                } else if (temp_s1_4 < 0x7D1) {
                    var_s1_4 = (int)((int) ((((int) (temp_s1_4 - 0x3E8) / 5) + 0x3E8) * (0x3E8 - temp_v0_79)) / 1000);
                } else {
                    var_s1_4 = (int)((int) ((((int) (temp_s1_4 - 0x7D0) / 10) + 0x4B0) * (0x3E8 - temp_v0_79)) / 1000);
                }
                temp_ret_436 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                temp_v0_80 = (void **)(temp_ret_436);
                temp_v0_81 = ((DW4VC_96_0 *)(temp_v0_80))->vX() % 1000U;
                if ((int) temp_v0_81 < var_s1_4) {
                    var_s2_3 = 1;
                }
                if (var_s2_3 != 0) {
                    temp_ret_437 = (int)igProperty_GetRecord(temp_v0_78, &DAT_005188c0[0]);
                    temp_s0_12 = ((beDataObjInt *)temp_ret_437)->_data;
                    temp_ret_438 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_438 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_439 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_440 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_439));
                    }
                    temp_ret_441 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_442 = beDataBase_GetRecordInt(temp_ret_441, sp47C, &DAT_005191b8[0]);
                    var_v1_8 = temp_s0_12 / 2;
                    var_s0_13 = temp_ret_442 + var_v1_8;
                } else {
                    var_s0_13 = 0;
                }
                if (var_s0_13 == 0) {
                    var_s0_13 = -1;
                }
                beMessenger_ClearInt(arg0->_messenger);
                beMessenger_AppendInt(arg0->_messenger, var_s0_13);
            } else {
                temp_a2_9 = temp_v0_77 % 10000;
                int sp478;
                beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_78, temp_a2_9, &sp478);
                temp_ret_443 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                if (temp_ret_443 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                    temp_ret_444 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_445 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_444));
                }
                temp_ret_446 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                var_s0_13 = -(beDataBase_GetRecordInt(temp_ret_446, sp478, HP) / 5);

                beMessenger_ClearInt(arg0->_messenger);
                beMessenger_AppendInt(arg0->_messenger, var_s0_13);
            }
            }
            break;
        case 16:
            temp_ret_449 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_450 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_451 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_452 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_453 = ObjectList_GetAt_003e9260(temp_ret_452, temp_ret_449);
            temp_v0_82 = (void *)(temp_ret_453);
            int sp474;
            sp474 = 0;
            temp_a2_10 = temp_ret_451 % 10000;
            var_s2_4 = 0;
            beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_82, temp_a2_10, &sp474);
            temp_ret_454 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
            if (temp_ret_454 == 0) {
                beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                temp_ret_455 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                temp_ret_456 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_455));
            }
            temp_ret_457 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
            temp_ret_458 = beDataBase_GetRecordInt(temp_ret_457, sp474, SKILL);
            temp_ret_459 = (int)FUN_003a9250(temp_v0_82, SKILL);
            temp_ret_460 = (void *)(FUN_00406ef0((int *)(temp_ret_459 + 0xC)));
            temp_ret_461 = DataList_GetData_003e9090(temp_ret_460);
            temp_s3_3 = ((int *)temp_ret_461)[temp_ret_458];
            temp_ret_462 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
            if (temp_ret_462 == 0) {
                beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                temp_ret_463 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                temp_ret_464 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_463));
            }
            temp_ret_465 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
            temp_ret_466 = beDataBase_GetRecordInt(temp_ret_465, temp_ret_450, &DAT_005188d0[0]);
            temp_v0_83 = temp_ret_466;
            if (temp_s3_3 < 0x3E9) {
                var_v1_9 = temp_s3_3 / 4;
                var_s1_5 = (int)((int) ((var_v1_9 + 0x226) * 0x64) / temp_v0_83);
            } else if (temp_s3_3 < 0x7D1) {
                var_s1_5 = (int)((int) ((((int) (temp_s3_3 - 0x3E8) / 5) + 0x320) * 0x64) / temp_v0_83);
            } else {
                var_s1_5 = (int)((int) ((((int) (temp_s3_3 - 0x7D0) / 10) + 0x3E8) * 0x64) / temp_v0_83);
            }
            temp_ret_467 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
            temp_v0_84 = (void **)(temp_ret_467);
            temp_v0_85 = ((DW4VC_96_0 *)(temp_v0_84))->vX() % 1000U;
            if ((int) temp_v0_85 < var_s1_5) {
                var_s2_4 = 1;
            }
            if (var_s2_4 != 0) {
                temp_ret_468 = (int)igProperty_GetRecord(temp_v0_82, &DAT_005188c0[0]);
                temp_s0_13 = ((beDataObjInt *)temp_ret_468)->_data;
                temp_ret_469 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                if (temp_ret_469 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                    temp_ret_470 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_471 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_470));
                }
                temp_ret_472 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                temp_ret_473 = beDataBase_GetRecordInt(temp_ret_472, sp474, &DAT_005191b8[0]);
                var_s0_14 = temp_ret_473 + temp_s0_13 / 2;
            } else {
                var_s0_14 = 0;
            }
            if (var_s0_14 == 0) {
                var_s0_14 = -1;
            }
            beMessenger_ClearInt(arg0->_messenger);
            beMessenger_AppendInt(arg0->_messenger, var_s0_14);
            break;
        case 17:
            temp_ret_474 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_475 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_476 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_477 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_478 = ObjectList_GetAt_003e9260(temp_ret_477, temp_ret_474);
            temp_v0_86 = (void *)(temp_ret_478);
            int sp470;
            sp470 = 0;
            temp_a2_11 = temp_ret_476 % 10000;
            var_s2_5 = 0;
            beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_86, temp_a2_11, &sp470);
            temp_ret_479 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
            if (temp_ret_479 == 0) {
                beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                temp_ret_480 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                temp_ret_481 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_480));
            }
            temp_ret_482 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
            temp_ret_483 = beDataBase_GetRecordInt(temp_ret_482, sp470, SKILL);
            temp_ret_484 = (int)FUN_003a9250(temp_v0_86, SKILL);
            temp_ret_485 = (void *)(FUN_00406ef0((int *)(temp_ret_484 + 0xC)));
            temp_ret_486 = DataList_GetData_003e9090(temp_ret_485);
            temp_s3_4 = ((int *)temp_ret_486)[temp_ret_483];
            temp_ret_487 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
            if (temp_ret_487 == 0) {
                beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                temp_ret_488 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                temp_ret_489 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_488));
            }
            temp_ret_490 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
            temp_ret_491 = beDataBase_GetRecordInt(temp_ret_490, temp_ret_475, &DAT_005188d0[0]);
            temp_v0_87 = temp_ret_491;
            if (temp_s3_4 < 0x3E9) {
                var_v1_11 = temp_s3_4 / 4;
                var_s1_6 = (int)((int) ((var_v1_11 + 0x226) * 0x64) / temp_v0_87);
            } else if (temp_s3_4 < 0x7D1) {
                var_s1_6 = (int)((int) ((((int) (temp_s3_4 - 0x3E8) / 5) + 0x320) * 0x64) / temp_v0_87);
            } else {
                var_s1_6 = (int)((int) ((((int) (temp_s3_4 - 0x7D0) / 10) + 0x3E8) * 0x64) / temp_v0_87);
            }
            temp_ret_492 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
            temp_v0_88 = (void **)(temp_ret_492);
            temp_v0_89 = ((DW4VC_96_0 *)(temp_v0_88))->vX() % 1000U;
            if ((int) temp_v0_89 < var_s1_6) {
                var_s2_5 = 1;
            }
            if (var_s2_5 != 0) {
                temp_ret_493 = (int)igProperty_GetRecord(temp_v0_86, &DAT_005188c0[0]);
                temp_s0_14 = ((beDataObjInt *)temp_ret_493)->_data;
                temp_ret_494 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                if (temp_ret_494 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                    temp_ret_495 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_496 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_495));
                }
                temp_ret_497 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                temp_ret_498 = beDataBase_GetRecordInt(temp_ret_497, sp470, &DAT_005191b8[0]);
                var_v1_12 = temp_s0_14 / 2;
                var_s0_15 = temp_ret_498 + var_v1_12;
            } else {
                var_s0_15 = 0;
            }
            if (var_s0_15 == 0) {
                var_s0_15 = -1;
            }
            beMessenger_ClearInt(arg0->_messenger);
            beMessenger_AppendInt(arg0->_messenger, var_s0_15);
            break;
        case 18:
            temp_ret_499 = (char *)(beMessenger_GetString(arg0->_messenger, 1));
            temp_v0_90 = (char *)(temp_ret_499);
            { StringRef sp46C(temp_v0_90 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_90));
            temp_ret_502 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_503 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_v0_91 = temp_ret_503;
            temp_ret_504 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_v0_92 = temp_ret_504;
            temp_ret_505 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_506 = ObjectList_GetAt_003e9260(temp_ret_505, temp_ret_502);
            temp_v0_93 = (void *)(temp_ret_506);
            temp_ret_507 = strcmp(sp46C.p, &DAT_005191b8[0]);
            if (temp_ret_507 == 0) {
                int sp468;
                sp468 = 0;
                temp_a2_12 = temp_v0_92 % 10000;
                var_s2_6 = 0;
                beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_93, temp_a2_12, &sp468);
                temp_ret_508 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                if (temp_ret_508 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                    temp_ret_509 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_510 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_509));
                }
                temp_ret_511 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                temp_ret_512 = beDataBase_GetRecordInt(temp_ret_511, sp468, SKILL);
                temp_ret_513 = (int)FUN_003a9250(temp_v0_93, SKILL);
                temp_ret_514 = (void *)(FUN_00406ef0((int *)(temp_ret_513 + 0xC)));
                temp_ret_515 = DataList_GetData_003e9090(temp_ret_514);
                temp_s1_5 = ((int *)temp_ret_515)[temp_ret_512];
                temp_ret_516 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                if (temp_ret_516 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                    temp_ret_517 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_518 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_517));
                }
                temp_ret_519 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                temp_ret_520 = beDataBase_GetRecordInt(temp_ret_519, temp_v0_91, &DAT_005188d0[0]);
                temp_v0_94 = temp_ret_520;
                if (temp_s1_5 < 0x3E9) {
                    var_v1_13 = temp_s1_5 / 4;
                    var_s1_7 = (int)((int) ((var_v1_13 + 0x226) * 0x64) / temp_v0_94);
                } else if (temp_s1_5 < 0x7D1) {
                    var_s1_7 = (int)((int) ((((int) (temp_s1_5 - 0x3E8) / 5) + 0x320) * 0x64) / temp_v0_94);
                } else {
                    var_s1_7 = (int)((int) ((((int) (temp_s1_5 - 0x7D0) / 10) + 0x3E8) * 0x64) / temp_v0_94);
                }
                temp_ret_521 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                temp_v0_95 = (void **)(temp_ret_521);
                temp_v0_96 = ((DW4VC_96_0 *)(temp_v0_95))->vX() % 1000U;
                if ((int) temp_v0_96 < var_s1_7) {
                    var_s2_6 = 1;
                }
                if (var_s2_6 != 0) {
                    temp_ret_522 = (int)igProperty_GetRecord(temp_v0_93, &DAT_005188c0[0]);
                    temp_s0_15 = ((beDataObjInt *)temp_ret_522)->_data;
                    temp_ret_523 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_523 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_524 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_525 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_524));
                    }
                    temp_ret_526 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_527 = beDataBase_GetRecordInt(temp_ret_526, sp468, &DAT_005191b8[0]);
                    var_v1_14 = temp_s0_15 / 2;
                    var_s0_16 = temp_ret_527 + var_v1_14;
                } else {
                    var_s0_16 = 0;
                }
                if (var_s0_16 == 0) {
                    var_s0_16 = -1;
                }
                beMessenger_ClearInt(arg0->_messenger);
                beMessenger_AppendInt(arg0->_messenger, var_s0_16);
            } else {
                temp_ret_528 = strcmp(sp46C.p, &DAT_005188d8[0]);
                if (temp_ret_528 == 0) {
                    temp_a2_13 = temp_v0_92 % 10000;
                    int sp464;
                    sp464 = 0;
                    beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_93, temp_a2_13, &sp464);
                    temp_ret_529 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_529 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_530 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_531 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_530));
                    }
                    temp_ret_532 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_533 = beDataBase_GetRecordInt(temp_ret_532, sp464, SKILL);
                    temp_ret_534 = (int)FUN_003a9250(temp_v0_93, SKILL);
                    temp_ret_535 = (void *)(FUN_00406ef0((int *)(temp_ret_534 + 0xC)));
                    temp_ret_536 = DataList_GetData_003e9090(temp_ret_535);
                    temp_s1_6 = ((int *)temp_ret_536)[temp_ret_533];
                    temp_ret_537 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    if (temp_ret_537 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                        temp_ret_538 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_539 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_538));
                    }
                    temp_ret_540 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    temp_ret_541 = beDataBase_GetRecordInt(temp_ret_540, temp_v0_91, &DAT_005188d8[0]);
                    temp_s0_16 = (int)((int) (-temp_ret_541 * 0x50) / 100);
                    temp_ret_542 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_542 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_543 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_544 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_543));
                    }
                    temp_ret_545 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_546 = beDataBase_GetRecordInt(temp_ret_545, sp464, &DAT_005188d8[0]);
                    var_s1_8 = temp_ret_546 - ((int) temp_s1_6 / 20);
                    if (var_s1_8 < temp_s0_16) {
                        var_s1_8 = temp_s0_16;
                    }
                    beMessenger_ClearInt(arg0->_messenger);
                    beMessenger_AppendInt(arg0->_messenger, -var_s1_8);
                } else {
                    temp_ret_547 = strcmp(sp46C.p, &DAT_00518960[0]);
                    if (temp_ret_547 == 0) {
                        temp_a2_14 = temp_v0_92 % 10000;
                        int sp460;
                        beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_93, temp_a2_14, &sp460);
                        temp_ret_548 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                        if (temp_ret_548 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                            temp_ret_549 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_550 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_549));
                        }
                        temp_ret_551 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                        temp_ret_552 = beDataBase_GetRecordInt(temp_ret_551, sp460, &DAT_00518960[0]);
                        beMessenger_ClearInt(arg0->_messenger);
                        beMessenger_AppendInt(arg0->_messenger, -temp_ret_552);
                    } else {
                        temp_ret_553 = strcmp(sp46C.p, &DAT_00518970[0]);
                        if (temp_ret_553 == 0) {
                            temp_a2_15 = temp_v0_92 % 10000;
                            int sp45C;
                            beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_93, temp_a2_15, &sp45C);
                            temp_ret_554 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                            if (temp_ret_554 == 0) {
                                beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                                temp_ret_555 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                                temp_ret_556 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_555));
                            }
                            temp_ret_557 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                            temp_ret_558 = beDataBase_GetRecordInt(temp_ret_557, sp45C, &DAT_005191c0[0]);
                            beMessenger_ClearInt(arg0->_messenger);
                            beMessenger_AppendInt(arg0->_messenger, -temp_ret_558);
                        } else {
                            temp_ret_559 = strcmp(sp46C.p, &DAT_00518980[0]);
                            if (temp_ret_559 == 0) {
                                temp_a2_16 = temp_v0_92 % 10000;
                                int sp458;
                                beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_93, temp_a2_16, &sp458);
                                temp_ret_560 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                                if (temp_ret_560 == 0) {
                                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                                    temp_ret_561 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                                    temp_ret_562 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_561));
                                }
                                temp_ret_563 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                                temp_ret_564 = beDataBase_GetRecordInt(temp_ret_563, sp458, &DAT_00518980[0]);
                                beMessenger_ClearInt(arg0->_messenger);
                                beMessenger_AppendInt(arg0->_messenger, -temp_ret_564);
                            }
                        }
                    }
                }
            }
            }
            break;
        case 19:
            temp_ret_566 = (char *)(beMessenger_GetString(arg0->_messenger, 1));
            temp_v0_97 = (char *)(temp_ret_566);
            { StringRef sp454(temp_v0_97 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_97));
            temp_ret_569 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_570 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_v0_98 = temp_ret_570;
            temp_ret_571 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_v0_99 = temp_ret_571;
            temp_ret_572 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_573 = ObjectList_GetAt_003e9260(temp_ret_572, temp_ret_569);
            temp_v0_100 = (void *)(temp_ret_573);
            temp_ret_574 = strcmp(sp454.p, &DAT_005191b8[0]);
            if (temp_ret_574 == 0) {
                int sp450;
                sp450 = 0;
                temp_a2_17 = temp_v0_99 % 10000;
                var_s2_7 = 0;
                beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_100, temp_a2_17, &sp450);
                temp_ret_575 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                if (temp_ret_575 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                    temp_ret_576 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_577 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_576));
                }
                temp_ret_578 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                temp_ret_579 = beDataBase_GetRecordInt(temp_ret_578, sp450, SKILL);
                temp_ret_580 = (int)FUN_003a9250(temp_v0_100, SKILL);
                temp_ret_581 = (void *)(FUN_00406ef0((int *)(temp_ret_580 + 0xC)));
                temp_ret_582 = DataList_GetData_003e9090(temp_ret_581);
                temp_s3_5 = ((int *)temp_ret_582)[temp_ret_579];
                temp_ret_583 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                if (temp_ret_583 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                    temp_ret_584 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_585 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_584));
                }
                temp_ret_586 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                temp_ret_587 = beDataBase_GetRecordInt(temp_ret_586, temp_v0_98, &DAT_005188d0[0]);
                temp_v0_101 = temp_ret_587;
                if (temp_s3_5 < 0x3E9) {
                    var_v1_15 = temp_s3_5 / 4;
                    var_s0_17 = (int)((int) ((var_v1_15 + 0x226) * 0x64) / temp_v0_101);
                } else if (temp_s3_5 < 0x7D1) {
                    var_s0_17 = (int)((int) ((((int) (temp_s3_5 - 0x3E8) / 5) + 0x320) * 0x64) / temp_v0_101);
                } else {
                    var_s0_17 = (int)((int) ((((int) (temp_s3_5 - 0x7D0) / 10) + 0x3E8) * 0x64) / temp_v0_101);
                }
                temp_ret_588 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                temp_v0_102 = (void **)(temp_ret_588);
                temp_v0_103 = ((DW4VC_96_0 *)(temp_v0_102))->vX() % 1000U;
                if ((int) temp_v0_103 < var_s0_17) {
                    var_s2_7 = 1;
                }
                if (var_s2_7 != 0) {
                    temp_ret_589 = (int)igProperty_GetRecord(temp_v0_100, &DAT_005188c0[0]);
                    temp_s0_17 = ((beDataObjInt *)temp_ret_589)->_data;
                    temp_ret_590 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_590 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_591 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_592 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_591));
                    }
                    temp_ret_593 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_594 = beDataBase_GetRecordInt(temp_ret_593, sp450, &DAT_005191b8[0]);
                    var_v1_16 = temp_s0_17 / 2;
                    var_s0_18 = temp_ret_594 + var_v1_16;
                } else {
                    var_s0_18 = 0;
                }
                if (var_s0_18 == 0) {
                    var_s0_18 = -1;
                }
                beMessenger_ClearInt(arg0->_messenger);
                beMessenger_AppendInt(arg0->_messenger, var_s0_18);
            } else {
                temp_ret_595 = strcmp(sp454.p, &DAT_005188b0[0]);
                if (temp_ret_595 == 0) {
                    temp_a2_18 = temp_v0_99 % 10000;
                    int sp44C;
                    sp44C = 0;
                    beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_100, temp_a2_18, &sp44C);
                    temp_ret_596 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_596 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_597 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_598 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_597));
                    }
                    temp_ret_599 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_600 = beDataBase_GetRecordInt(temp_ret_599, sp44C, SKILL);
                    temp_ret_601 = (int)FUN_003a9250(temp_v0_100, SKILL);
                    temp_ret_602 = (void *)(FUN_00406ef0((int *)(temp_ret_601 + 0xC)));
                    temp_ret_603 = DataList_GetData_003e9090(temp_ret_602);
                    temp_s1_7 = ((int *)temp_ret_603)[temp_ret_600];
                    temp_ret_604 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    if (temp_ret_604 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                        temp_ret_605 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_606 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_605));
                    }
                    temp_ret_607 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    temp_ret_608 = beDataBase_GetRecordInt(temp_ret_607, temp_v0_98, &DAT_005188b0[0]);
                    temp_s0_18 = (int)((int) (-temp_ret_608 * 0x50) / 100);
                    temp_ret_609 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_609 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_610 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_611 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_610));
                    }
                    temp_ret_612 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_613 = beDataBase_GetRecordInt(temp_ret_612, sp44C, &DAT_005188b0[0]);
                    var_s1_9 = temp_ret_613 - ((int) temp_s1_7 / 20);
                    if (var_s1_9 < temp_s0_18) {
                        var_s1_9 = temp_s0_18;
                    }
                    beMessenger_ClearInt(arg0->_messenger);
                    beMessenger_AppendInt(arg0->_messenger, -var_s1_9);
                } else {
                    temp_ret_614 = strcmp(sp454.p, &DAT_005188b8[0]);
                    if (temp_ret_614 == 0) {
                        temp_a2_19 = temp_v0_99 % 10000;
                        int sp448;
                        sp448 = 0;
                        beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_100, temp_a2_19, &sp448);
                        temp_ret_615 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                        if (temp_ret_615 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                            temp_ret_616 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_617 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_616));
                        }
                        temp_ret_618 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                        temp_ret_619 = beDataBase_GetRecordInt(temp_ret_618, sp448, SKILL);
                        temp_ret_620 = (int)FUN_003a9250(temp_v0_100, SKILL);
                        temp_ret_621 = (void *)(FUN_00406ef0((int *)(temp_ret_620 + 0xC)));
                        temp_ret_622 = DataList_GetData_003e9090(temp_ret_621);
                        temp_s1_8 = ((int *)temp_ret_622)[temp_ret_619];
                        temp_ret_623 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        if (temp_ret_623 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                            temp_ret_624 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_625 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_624));
                        }
                        temp_ret_626 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        temp_ret_627 = beDataBase_GetRecordInt(temp_ret_626, temp_v0_98, &DAT_005188b8[0]);
                        temp_s0_19 = (int)((int) (-temp_ret_627 * 0x50) / 100);
                        temp_ret_628 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                        if (temp_ret_628 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                            temp_ret_629 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_630 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_629));
                        }
                        temp_ret_631 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                        temp_ret_632 = beDataBase_GetRecordInt(temp_ret_631, sp448, &DAT_005188b8[0]);
                        var_s1_10 = temp_ret_632 - ((int) temp_s1_8 / 20);
                        if (var_s1_10 < temp_s0_19) {
                            var_s1_10 = temp_s0_19;
                        }
                        beMessenger_ClearInt(arg0->_messenger);
                        beMessenger_AppendInt(arg0->_messenger, -var_s1_10);
                    }
                }
            }
            }
            break;
        case 0:
            temp_ret_634 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_635 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_636 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_637 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_638 = ObjectList_GetAt_003e9260(temp_ret_637, temp_ret_634);
            temp_v0_104 = (void *)(temp_ret_638);
            temp_s3_6 = temp_ret_636 % 10000;
            var_s5_7 = 0;
            temp_ret_639 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
            if (temp_ret_639 == 0) {
                beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                temp_ret_640 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                temp_ret_641 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_640));
            }
            temp_ret_642 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
            temp_ret_643 = beDataBase_GetRecordInt(temp_ret_642, temp_s3_6, &DAT_005191d0[0]);
            switch (temp_ret_643) {
            case 0:
                temp_ret_644 = (int)igProperty_GetRecord(temp_v0_104, &DAT_00518990[0]);
                temp_s0_20 = ((beDataObjInt *)temp_ret_644)->_data;
                temp_ret_645 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                temp_v0_105 = (void **)(temp_ret_645);
                temp_v0_106 = ((DW4VC_96_0 *)(temp_v0_105))->vX() % 100U;
                if (temp_s0_20 <= (int) temp_v0_106) {
                    temp_ret_646 = (int)igProperty_GetRecord(temp_v0_104, &DAT_005188d8[0]);
                    temp_s1_9 = ((beDataObjInt *)temp_ret_646)->_data;
                    temp_ret_647 = (int)igProperty_GetRecord(temp_v0_104, &DAT_00518980[0]);
                    temp_s0_21 = ((beDataObjInt *)temp_ret_647)->_data;
                    temp_ret_648 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    if (temp_ret_648 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                        temp_ret_649 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_650 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_649));
                    }
                    temp_ret_651 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    temp_ret_652 = beDataBase_GetRecordInt(temp_ret_651, temp_ret_635, &DAT_005188d8[0]);
                    temp_ret_653 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    if (temp_ret_653 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                        temp_ret_654 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_655 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_654));
                    }
                    temp_ret_656 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    temp_ret_657 = beDataBase_GetRecordInt(temp_ret_656, temp_s3_6, &DAT_00518950[0]);
                    temp_ret_658 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
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
            beMessenger_ClearBool(arg0->_messenger);
            beMessenger_AppendBool(arg0->_messenger, var_s5_7);
            break;
        case 3:
            temp_ret_659 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_660 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_v0_108 = temp_ret_660;
            temp_ret_661 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_662 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
            temp_v0_109 = (beNDMWMdlPEBaseInfoWork *)(temp_ret_662);
            temp_ret_663 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_664 = ObjectList_GetAt_003e9260(temp_ret_663, temp_ret_659);
            temp_v0_110 = (void *)(temp_ret_664);
            temp_s5_2 = temp_ret_661 % 10000;
            temp_ret_665 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
            if (temp_ret_665 == 0) {
                beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                temp_ret_666 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                temp_ret_667 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_666));
            }
            temp_ret_668 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
            temp_ret_669 = beDataBase_GetRecordInt(temp_ret_668, temp_s5_2, &DAT_005191d0[0]);
            temp_v0_111 = temp_ret_669;
            var_s3_4 = 0;
            var_s2_8 = -1;
            switch (temp_v0_111) {
            case 0:
                temp_ret_670 = (int)igProperty_GetRecord(temp_v0_110, &DAT_005188b8[0]);
                temp_s3_7 = ((beDataObjInt *)temp_ret_670)->_data;
                temp_ret_671 = (void *)(FUN_00406ef0(&temp_v0_109->_downDataList));
                if (temp_ret_671 == 0) {
                    var_s1_11 = 0;
                } else {
                    temp_ret_672 = (void *)(FUN_00406ef0(&temp_v0_109->_downDataList));
                    temp_ret_673 = DataList_GetData_003e9090(temp_ret_672);
                    var_s1_11 = ((int *)temp_ret_673)[4];
                }
                temp_ret_674 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                if (temp_ret_674 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                    temp_ret_675 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_676 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_675));
                }
                temp_ret_677 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                temp_ret_678 = beDataBase_GetRecordInt(temp_ret_677, temp_v0_108, &DAT_005188b0[0]);
                int e2p_diff_678; e2p_diff_678 = temp_ret_678 - var_s1_11;
                temp_ret_679 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_679 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_680 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_681 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_680));
                }
                temp_ret_682 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                temp_ret_683 = beDataBase_GetRecordInt(temp_ret_682, temp_s5_2, &DAT_005188b0[0]);
                var_s3_4 = (int)((int) (e2p_diff_678 * temp_ret_683) / temp_s3_7);
                if (var_s3_4 < 0) {
                    var_s3_4 = 0;
                } else if (var_s3_4 > 0x1869F) {
                    var_s3_4 = 0x1869F;
                }
                temp_ret_684 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_684 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_685 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_686 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_685));
                }
                temp_ret_687 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                temp_ret_688 = (char *)(beDataBase_GetRecordString(temp_ret_687, temp_s5_2, &DAT_00519018[0]));
                temp_v0_112 = (char *)(temp_ret_688);
                var_s1_12 = 0;
                temp_ret_689 = strcmp(temp_v0_112, &DAT_00518fa8[0]);
                if (temp_ret_689 == 0) {
                    temp_ret_690 = (int)igProperty_GetRecord(temp_v0_110, &DAT_005188e8[0]);
                    var_s1_12 = ((beDataObjInt *)temp_ret_690)->_data;
                    var_s2_8 = 0;
                } else {
                    temp_ret_691 = strcmp(temp_v0_112, &DAT_00518fb0[0]);
                    if (temp_ret_691 == 0) {
                        temp_ret_692 = (int)igProperty_GetRecord(temp_v0_110, &DAT_005188f8[0]);
                        var_s1_12 = ((beDataObjInt *)temp_ret_692)->_data;
                        var_s2_8 = 1;
                    } else {
                        temp_ret_693 = strcmp(temp_v0_112, &DAT_00518fb8[0]);
                        if (temp_ret_693 == 0) {
                            temp_ret_694 = (int)igProperty_GetRecord(temp_v0_110, &DAT_00518908[0]);
                            var_s1_12 = ((beDataObjInt *)temp_ret_694)->_data;
                            var_s2_8 = 2;
                        } else {
                            temp_ret_695 = strcmp(temp_v0_112, &DAT_00518fc0[0]);
                            if (temp_ret_695 == 0) {
                                temp_ret_696 = (int)igProperty_GetRecord(temp_v0_110, &DAT_00518918[0]);
                                var_s1_12 = ((beDataObjInt *)temp_ret_696)->_data;
                                var_s2_8 = 3;
                            }
                        }
                    }
                }
                if (var_s1_12 != 0) {
                    temp_ret_697 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
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
                    temp_ret_698 = (void *)(FUN_00406ef0(&temp_v0_109->_downDataList));
                    if (temp_ret_698 == 0) {
                        var_s0_19 = 0;
                    } else {
                        temp_ret_699 = (void *)(FUN_00406ef0(&temp_v0_109->_downDataList));
                        temp_ret_700 = DataList_GetData_003e9090(temp_ret_699);
                        var_s0_19 = ((int *)temp_ret_700)[1];
                    }
                    temp_ret_701 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    if (temp_ret_701 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                        temp_ret_702 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_703 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_702));
                    }
                    temp_ret_704 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    temp_ret_705 = beDataBase_GetRecordInt(temp_ret_704, temp_v0_108, &DAT_00518960[0]);
                    e2p_diff_705 = temp_ret_705 - var_s0_19;
                    temp_ret_706 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    if (temp_ret_706 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                        temp_ret_707 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_708 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_707));
                    }
                    temp_ret_709 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    temp_ret_710 = beDataBase_GetRecordInt(temp_ret_709, temp_s5_2, &DAT_00518960[0]);
                    temp_v0_114 = temp_ret_710;
                    temp_ret_711 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                    temp_v0_115 = (void **)(temp_ret_711);
                    temp_a0_8 = ((DW4VC_96_0 *)(temp_v0_115))->vX() % 10000U;
                    if (((0x64 - e2p_diff_705) * (0x64 - temp_v0_114)) <= (int) temp_a0_8) {
                        var_v0_15 = (int)((int) (var_s3_4 * (temp_v0_114 / 2 + 0x5A)) / 100);
                        var_s3_4 += var_v0_15;
                    }
                }
                break;
            case 1:
                temp_ret_712 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_712 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_713 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_714 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_713));
                }
                temp_ret_715 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                temp_ret_716 = beDataBase_GetRecordInt(temp_ret_715, temp_s5_2, &DAT_005188b0[0]);
                temp_v0_116 = temp_ret_716;
                if (temp_v0_116 != 0) {
                    temp_ret_717 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    if (temp_ret_717 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                        temp_ret_718 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_719 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_718));
                    }
                    temp_ret_720 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    temp_ret_721 = beDataBase_GetRecordInt(temp_ret_720, temp_v0_108, &DAT_005188c0[0]);
                    temp_ret_722 = (int)igProperty_GetRecord(temp_v0_110, &DAT_005188d0[0]);
                    var_s3_4 = (int)((int) (temp_ret_721 * temp_v0_116) / (int) ((beDataObjInt *)temp_ret_722)->_data);
                    if (var_s3_4 < 0) {
                        var_s3_4 = 0;
                    } else if (var_s3_4 > 0x1869F) {
                        var_s3_4 = 0x1869F;
                    }
                    var_s1_13 = 0;
                    temp_ret_723 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    if (temp_ret_723 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                        temp_ret_724 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_725 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_724));
                    }
                    temp_ret_726 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    temp_ret_727 = (char *)(beDataBase_GetRecordString(temp_ret_726, temp_s5_2, &DAT_00519018[0]));
                    temp_v0_117 = (char *)(temp_ret_727);
                    temp_ret_728 = strcmp(temp_v0_117, &DAT_00518fa8[0]);
                    if (temp_ret_728 == 0) {
                        temp_ret_729 = (int)igProperty_GetRecord(temp_v0_110, &DAT_005188e8[0]);
                        var_s1_13 = ((beDataObjInt *)temp_ret_729)->_data;
                        var_s2_8 = 0;
                    } else {
                        temp_ret_730 = strcmp(temp_v0_117, &DAT_00518fb0[0]);
                        if (temp_ret_730 == 0) {
                            temp_ret_731 = (int)igProperty_GetRecord(temp_v0_110, &DAT_005188f8[0]);
                            var_s1_13 = ((beDataObjInt *)temp_ret_731)->_data;
                            var_s2_8 = 1;
                        } else {
                            temp_ret_732 = strcmp(temp_v0_117, &DAT_00518fb8[0]);
                            if (temp_ret_732 == 0) {
                                temp_ret_733 = (int)igProperty_GetRecord(temp_v0_110, &DAT_00518908[0]);
                                var_s1_13 = ((beDataObjInt *)temp_ret_733)->_data;
                                var_s2_8 = 2;
                            } else {
                                temp_ret_734 = strcmp(temp_v0_117, &DAT_00518fc0[0]);
                                if (temp_ret_734 == 0) {
                                    temp_ret_735 = (int)igProperty_GetRecord(temp_v0_110, &DAT_00518918[0]);
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
                        temp_ret_736 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        if (temp_ret_736 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                            temp_ret_737 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_738 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_737));
                        }
                        temp_ret_739 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        temp_ret_740 = beDataBase_GetRecordInt(temp_ret_739, temp_s5_2, &DAT_00518960[0]);
                        temp_v0_118 = temp_ret_740;
                        if (temp_v0_118 != 0) {
                            if (var_s1_13 < 0x3E9) {
                                var_s0_20 = (0x3E8 - var_s1_13) + (temp_v0_118 * 0x64);
                            } else {
                                var_s0_20 = (temp_v0_118 * 0x64) - ((int) (var_s1_13 - 0x3E8) / 10);
                            }
                            temp_ret_741 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
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
                temp_ret_742 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_742 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_743 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_744 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_743));
                }
                temp_ret_745 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                temp_ret_746 = beDataBase_GetRecordInt(temp_ret_745, temp_s5_2, &DAT_005188b0[0]);
                temp_ret_747 = (int)igProperty_GetRecord(temp_v0_110, MHP);
                var_s3_4 = (int)((int) (((beDataObjInt *)temp_ret_747)->_data * temp_ret_746) / 100);
                if (var_s3_4 < 0) {
                    var_s3_4 = 0;
                } else if (var_s3_4 > 0x1869F) {
                    var_s3_4 = 0x1869F;
                }
                var_s1_14 = 0;
                temp_ret_748 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_748 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_749 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_750 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_749));
                }
                temp_ret_751 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                temp_ret_752 = (char *)(beDataBase_GetRecordString(temp_ret_751, temp_s5_2, &DAT_00519018[0]));
                temp_v0_121 = (char *)(temp_ret_752);
                temp_ret_753 = strcmp(temp_v0_121, &DAT_00518fa8[0]);
                if (temp_ret_753 == 0) {
                    temp_ret_754 = (int)igProperty_GetRecord(temp_v0_110, &DAT_005188e8[0]);
                    var_s1_14 = ((beDataObjInt *)temp_ret_754)->_data;
                    var_s2_8 = 0;
                } else {
                    temp_ret_755 = strcmp(temp_v0_121, &DAT_00518fb0[0]);
                    if (temp_ret_755 == 0) {
                        temp_ret_756 = (int)igProperty_GetRecord(temp_v0_110, &DAT_005188f8[0]);
                        var_s1_14 = ((beDataObjInt *)temp_ret_756)->_data;
                        var_s2_8 = 1;
                    } else {
                        temp_ret_757 = strcmp(temp_v0_121, &DAT_00518fb8[0]);
                        if (temp_ret_757 == 0) {
                            temp_ret_758 = (int)igProperty_GetRecord(temp_v0_110, &DAT_00518908[0]);
                            var_s1_14 = ((beDataObjInt *)temp_ret_758)->_data;
                            var_s2_8 = 2;
                        } else {
                            temp_ret_759 = strcmp(temp_v0_121, &DAT_00518fc0[0]);
                            if (temp_ret_759 == 0) {
                                temp_ret_760 = (int)igProperty_GetRecord(temp_v0_110, &DAT_00518918[0]);
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
                temp_ret_761 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                temp_v0_122 = (void **)(temp_ret_761);
                int e2p_rng = ((DW4VC_96_0 *)(temp_v0_122))->vX() & 3;
                temp_ret_762 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
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
            beMessenger_ClearInt(arg0->_messenger);
            beMessenger_AppendInt(arg0->_messenger, var_s3_4);
            beMessenger_AppendInt(arg0->_messenger, var_s2_8);
            beMessenger_AppendInt(arg0->_messenger, var_s1_15);
            break;
        case 4:
            int var_s0_21;
            temp_ret_763 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_764 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_765 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_766 = beMessenger_GetInt(arg0->_messenger, 3);
            temp_ret_767 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
            temp_v0_128 = (void *)(temp_ret_767);
            var_s0_21 = 0;
            if (temp_ret_765 <= 0) {
                var_s0_21 = 3;
            } else {
                temp_ret_768 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                temp_ret_769 = ObjectList_GetAt_003e9260(temp_ret_768, temp_ret_763);
                temp_s5_3 = temp_ret_764 % 10000;
                temp_ret_770 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_770 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_771 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_772 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_771));
                }
                temp_ret_773 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                int temp_ret_774 = beDataBase_GetRecordInt(temp_ret_773, temp_s5_3, &DAT_005188b0[0]);
                temp_ret_775 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_775 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_776 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_777 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_776));
                }
                temp_ret_778 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                temp_ret_779 = beDataBase_GetRecordInt(temp_ret_778, temp_s5_3, &DAT_005191d8[0]);
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
                temp_ret_781 = FUN_003e93b0((void *)((int)temp_v0_128 + 0x28));
                if (temp_ret_781 == 0) {
                    temp_ret_782 = igObject_GetAllocator(temp_v0_128);
                    temp_ret_786 = DW4Fresh::Assign((char *)temp_v0_128 + 0x28, temp_ret_782);
                }
                temp_ret_788 = FUN_003e92a0((char *)temp_v0_128 + 0x28);
                temp_ret_789 = FUN_003e9280(temp_ret_788, g_propertyNameField[0], &DAT_005191e8[0]);
                temp_ret_790 = FUN_00406e00((int *)(temp_ret_789 + 0x14));
                temp_ret_791 = (void *)(FUN_00406df0((int *)(temp_ret_790 + 0xC8)));
                temp_v0_130 = (void *)(temp_ret_791);
                if (((DW4CountedListView *)temp_v0_130)->count != 0) {
                    temp_ret_792 = (void *)(FUN_00406dd0((beNDMWGameRam *)temp_v0_130, 1));
                    if (((DW4ByteFlag8 *)temp_ret_792)->value != 0) {
                        var_s0_21 = 1;
                    }
                }
            }
            beMessenger_ClearInt(arg0->_messenger);
            beMessenger_AppendInt(arg0->_messenger, var_s0_21);
            break;
        case 7: {
            temp_ret_793 = beMessenger_GetInt(arg0->_messenger, 0);
            sp120 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_795 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_796 = beMessenger_GetInt(arg0->_messenger, 3);
            temp_ret_797 = beMessenger_GetInt(arg0->_messenger, 4);
            temp_v0_131 = temp_ret_797;
            temp_ret_798 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
            temp_v0_132 = (beNDMWMdlPEBaseInfoWork *)(temp_ret_798);
            temp_ret_799 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_800 = ObjectList_GetAt_003e9260(temp_ret_799, temp_ret_793);
            temp_v0_133 = (void *)(temp_ret_800);
            temp_s6_2 = temp_ret_795 % 10000;
            temp_ret_801 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
            if (temp_ret_801 == 0) {
                beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                temp_ret_802 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                temp_ret_803 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_802));
            }
            temp_ret_804 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
            temp_ret_805 = beDataBase_GetRecordInt(temp_ret_804, temp_s6_2, &DAT_005191d0[0]);
            temp_v0_134 = temp_ret_805;
            var_s8_2 = 0;
            var_s1_16 = 0;
            var_s0_22 = 0;
            switch (temp_v0_134) {
            case 0:
                switch (temp_v0_131) { case 1: case 2: {
                    temp_ret_806 = (void *)(FUN_00406ef0(&temp_v0_132->_downDataList));
                    if (temp_ret_806 == 0) {
                        var_s0_23 = 0;
                    } else {
                        temp_ret_807 = (void *)(FUN_00406ef0(&temp_v0_132->_downDataList));
                        temp_ret_808 = DataList_GetData_003e9090(temp_ret_807);
                        var_s0_23 = ((int *)temp_ret_808)[2];
                    }
                    temp_ret_809 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    if (temp_ret_809 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                        temp_ret_810 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_811 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_810));
                    }
                    temp_ret_812 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    temp_ret_813 = beDataBase_GetRecordInt(temp_ret_812, sp120, &DAT_00518970[0]);
                    var_s8_2 = temp_ret_813 - var_s0_23;
                    var_s0_22 = 1;
                } }
                break;
            case 1:
                temp_ret_814 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_814 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_815 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_816 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_815));
                }
                temp_ret_817 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                var_s1_16 = beDataBase_GetRecordInt(temp_ret_817, temp_s6_2, &DAT_00518970[0]);
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
                temp_ret_820 = (int)igProperty_GetRecord(temp_v0_133, &DAT_005189a0[0]);
                temp_s0_23 = ((beDataObjInt *)temp_ret_820)->_data;
                temp_ret_821 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
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
            beMessenger_ClearInt(arg0->_messenger);
            beMessenger_AppendInt(arg0->_messenger, var_s2_9);
            break; }
        case 8:
            temp_ret_822 = (char *)(beMessenger_GetString(arg0->_messenger, 1));
            temp_v0_137 = (char *)(temp_ret_822);
            { StringRef sp444((char *)(temp_v0_137 == 0 ? (char *)0 : (char *)StringPool_Intern((void *)StringPool_GetInstance(), temp_v0_137)));
            temp_ret_825 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_826 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_827 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_828 = ObjectList_GetAt_003e9260(temp_ret_827, temp_ret_825);
            temp_v0_138 = (void *)(temp_ret_828);
            temp_s3_9 = temp_ret_826 % 10000;
            temp_ret_829 = strcmp(sp444.p, &DAT_005191b8[0]);
            if (temp_ret_829 == 0) {
                var_s2_10 = 0;
                temp_ret_830 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_830 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_831 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_832 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_831));
                }
                temp_ret_833 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                temp_ret_834 = (char *)(beDataBase_GetRecordString(temp_ret_833, temp_s3_9, &DAT_005191f0[0]));
                temp_ret_835 = strcmp(temp_ret_834, &DAT_005191f8[0]);
                if (temp_ret_835 == 0) {
                    temp_ret_836 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    if (temp_ret_836 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                        temp_ret_837 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_838 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_837));
                    }
                    temp_ret_839 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    int temp_ret_840 = beDataBase_GetRecordInt(temp_ret_839, temp_s3_9, &DAT_00519200[0]);
                    temp_ret_841 = (int)igProperty_GetRecord(temp_v0_138, &DAT_005189b0[0]);
                    int temp_s0_24 = ((beDataObjInt *)temp_ret_841)->_data;
                    temp_ret_842 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                    temp_v0_139 = (void **)(temp_ret_842);
                    temp_v1_8 = ((DW4VC_96_0 *)(temp_v0_139))->vX() % 100U;
                    if ((int) temp_v1_8 < (temp_s0_24 + ((temp_ret_840 * 0xF) + 0x1E))) {
                        temp_ret_843 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        if (temp_ret_843 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                            temp_ret_844 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_845 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_844));
                        }
                        temp_ret_846 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        temp_ret_847 = beDataBase_GetRecordInt(temp_ret_846, temp_s3_9, &DAT_00519210[0]);
                        var_s2_10 = temp_s0_24 / 2 + temp_ret_847;
                    }
                    if (var_s2_10 == 0) {
                        var_s2_10 = -1;
                    }
                }
                beMessenger_ClearInt(arg0->_messenger);
                beMessenger_AppendInt(arg0->_messenger, var_s2_10);
            } else {
                temp_ret_848 = strcmp(sp444.p, &DAT_00519220[0]);
                if (temp_ret_848 == 0) {
                    temp_ret_849 = (int)igProperty_GetRecord(temp_v0_138, MHP);
                    temp_s0_25 = ((beDataObjInt *)temp_ret_849)->_data;
                    temp_ret_850 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    if (temp_ret_850 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                        temp_ret_851 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_852 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_851));
                    }
                    temp_ret_853 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    temp_ret_854 = beDataBase_GetRecordInt(temp_ret_853, temp_s3_9, &DAT_00519200[0]);
                    beMessenger_ClearInt(arg0->_messenger);
                    beMessenger_AppendInt(arg0->_messenger, (int) (temp_s0_25 * temp_ret_854) / 100);
                } else {
                    temp_ret_855 = strcmp(sp444.p, &DAT_00519228[0]);
                    if (temp_ret_855 == 0) {
                        temp_ret_856 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        if (temp_ret_856 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                            temp_ret_857 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_858 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_857));
                        }
                        temp_ret_859 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        temp_ret_860 = beDataBase_GetRecordInt(temp_ret_859, temp_s3_9, &DAT_00519228[0]);
                        beMessenger_ClearInt(arg0->_messenger);
                        beMessenger_AppendInt(arg0->_messenger, temp_ret_860);
                    }
                }
            }
            }
            break;
        case 9: {
            temp_ret_862 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_863 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_864 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_865 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            int temp_ret_866 = ObjectList_GetAt_003e9260(temp_ret_865, temp_ret_862);
            int temp_s2_2 = temp_ret_864 % 10000;
            temp_ret_867 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
            if (temp_ret_867 == 0) {
                beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                temp_ret_868 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                temp_ret_869 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_868));
            }
            temp_ret_870 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
            temp_ret_871 = (char *)(beDataBase_GetRecordString(temp_ret_870, temp_s2_2, &DAT_005191f0[0]));
            int var_s1_17 = 0;
            temp_ret_872 = strcmp(temp_ret_871, &DAT_00519230[0]);
            if (temp_ret_872 == 0) {
                temp_ret_873 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_873 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_874 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_875 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_874));
                }
                temp_ret_876 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                temp_ret_877 = beDataBase_GetRecordInt(temp_ret_876, temp_s2_2, &DAT_00519200[0]);
                temp_ret_878 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                if (temp_ret_878 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                    temp_ret_879 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_880 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_879));
                }
                temp_ret_881 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                temp_ret_882 = beDataBase_GetRecordInt(temp_ret_881, temp_ret_863, &DAT_005188c0[0]);
                temp_ret_883 = (int)igProperty_GetRecord(temp_ret_866, &DAT_005188d0[0]);
                temp_s3_10 = ((beDataObjInt *)temp_ret_883)->_data;
                temp_ret_884 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                temp_v0_140 = (void **)(temp_ret_884);
                temp_a2_23 = ((DW4VC_96_0 *)(temp_v0_140))->vX() % 10000U;
                temp_s0_26 = (((int) (temp_ret_882 * 3) / (int) temp_s3_10) + 0x64) - ((int) temp_s3_10 / 40);
                int hit_base = temp_ret_877 * 5;
                if ((int) temp_a2_23 < (hit_base * temp_s0_26)) {
                    temp_ret_885 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    if (temp_ret_885 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                        temp_ret_886 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_887 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_886));
                    }
                    temp_ret_888 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    temp_ret_889 = beDataBase_GetRecordInt(temp_ret_888, temp_s2_2, &DAT_00519210[0]);
                    var_s1_17 = (int)((int) (temp_ret_889 * temp_s0_26) / 100);
                }
                if (var_s1_17 == 0) {
                    var_s1_17 = -1;
                }
            }
            beMessenger_ClearInt(arg0->_messenger);
            beMessenger_AppendInt(arg0->_messenger, var_s1_17);
            break; }
        case 10: {
            temp_ret_890 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_ret_891 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_v0_141 = temp_ret_891;
            temp_ret_892 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_893 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_894 = ObjectList_GetAt_003e9260(temp_ret_893, temp_ret_890);
            temp_v0_142 = (void *)(temp_ret_894);
            temp_s3_11 = temp_ret_892 % 10000;
            temp_ret_895 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
            if (temp_ret_895 == 0) {
                beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                temp_ret_896 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                temp_ret_897 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_896));
            }
            temp_ret_898 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
            temp_ret_899 = (char *)(beDataBase_GetRecordString(temp_ret_898, temp_s3_11, &DAT_005191f0[0]));
            var_s2_11 = 0;
            temp_ret_900 = strcmp(temp_ret_899, &DAT_00519238[0]);
            if (temp_ret_900 == 0) {
                temp_ret_901 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_901 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_902 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_903 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_902));
                }
                temp_ret_904 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                temp_ret_905 = beDataBase_GetRecordInt(temp_ret_904, temp_s3_11, &DAT_00519200[0]);
                temp_ret_906 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_906 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_907 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_908 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_907));
                }
                temp_ret_909 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                temp_ret_910 = beDataBase_GetRecordInt(temp_ret_909, temp_s3_11, &DAT_005191d0[0]);
                temp_v0_143 = temp_ret_910;
                sp110 = 1;
                if (temp_v0_143 != 2) {
                    temp_ret_911 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    if (temp_ret_911 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                        temp_ret_912 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_913 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_912));
                    }
                    temp_ret_914 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    temp_ret_915 = beDataBase_GetRecordInt(temp_ret_914, temp_v0_141, &DAT_005188c0[0]);
                    temp_ret_916 = (int)igProperty_GetRecord(temp_v0_142, &DAT_005188d0[0]);
                    unsigned int temp_s0_27 = ((beDataObjInt *)temp_ret_916)->_data;
                    temp_ret_917 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                    temp_v0_144 = (void **)(temp_ret_917);
                    temp_a2_24 = ((DW4VC_96_0 *)(temp_v0_144))->vX() % 10000U;
                    if ((temp_ret_905 * 5 * ((((int) (temp_ret_915 * 3) / (int) temp_s0_27) + 0x64) - ((int) temp_s0_27 / 40))) <= (int) temp_a2_24) {
                        sp110 = 0;
                    }
                }
                if (sp110) {
                    if (temp_v0_143 == 2) {
                        temp_ret_918 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        if (temp_ret_918 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                            temp_ret_919 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_920 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_919));
                        }
                        temp_ret_921 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        temp_ret_922 = beDataBase_GetRecordInt(temp_ret_921, temp_s3_11, &DAT_00519210[0]);
                        var_s2_11 = temp_ret_922;
                    } else {
                        temp_ret_923 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        if (temp_ret_923 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                            temp_ret_924 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_925 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_924));
                        }
                        temp_ret_926 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        temp_ret_927 = beDataBase_GetRecordInt(temp_ret_926, temp_s3_11, &DAT_00519210[0]);
                        temp_ret_928 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        if (temp_ret_928 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                            temp_ret_929 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_930 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_929));
                        }
                        temp_ret_931 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        temp_ret_932 = beDataBase_GetRecordInt(temp_ret_931, temp_v0_141, &DAT_005188c0[0]);
                        temp_ret_933 = (int)igProperty_GetRecord(temp_v0_142, &DAT_005188d0[0]);
                        temp_v0_145 = (void *)(temp_ret_933);
                        var_s2_11 = (int)((int) (temp_ret_927 * ((((int) (temp_ret_932 * 3) / (int) ((beDataObjInt *)temp_v0_145)->_data) + 0x64) - ((int) ((beDataObjInt *)temp_v0_145)->_data / 40))) / 100);
                    }
                }
                if (var_s2_11 == 0) {
                    var_s2_11 = -1;
                }
            }
            beMessenger_ClearInt(arg0->_messenger);
            beMessenger_AppendInt(arg0->_messenger, var_s2_11);
            break; }
        case 11: {
            temp_ret_934 = (char *)(beMessenger_GetString(arg0->_messenger, 1));
            temp_v0_146 = (char *)(temp_ret_934);
            if (temp_v0_146 == 0) {
                var_v0_20 = (char *)(0);
            } else {
                var_v0_20 = (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_146);
            }
            { StringRef sp440((char *)(var_v0_20));
            temp_ret_937 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_v0_147 = temp_ret_937;
            temp_ret_938 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_v0_148 = temp_ret_938;
            temp_ret_939 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_940 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_941 = ObjectList_GetAt_003e9260(temp_ret_940, temp_v0_147);
            temp_v0_149 = (void *)(temp_ret_941);
            temp_s2_3 = temp_ret_939 % 10000;
            temp_ret_942 = strcmp(sp440.p, &DAT_005191b8[0]);
            if (temp_ret_942 == 0) {
                temp_ret_943 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_943 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_944 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_945 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_944));
                }
                temp_ret_946 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                temp_ret_947 = (char *)(beDataBase_GetRecordString(temp_ret_946, temp_s2_3, &DAT_005191f0[0]));
                var_s1_18 = 0;
                temp_ret_948 = strcmp(temp_ret_947, &DAT_00519248[0]);
                if (temp_ret_948 == 0) {
                    temp_ret_949 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    if (temp_ret_949 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                        temp_ret_950 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_951 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_950));
                    }
                    temp_ret_952 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    temp_ret_953 = beDataBase_GetRecordInt(temp_ret_952, temp_s2_3, &DAT_00519200[0]);
                    temp_ret_954 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    if (temp_ret_954 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                        temp_ret_955 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_956 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_955));
                    }
                    temp_ret_957 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    temp_ret_958 = beDataBase_GetRecordInt(temp_ret_957, temp_v0_148, &DAT_005188c0[0]);
                    temp_ret_959 = (int)igProperty_GetRecord(temp_v0_149, &DAT_005188d0[0]);
                    temp_s3_12 = ((beDataObjInt *)temp_ret_959)->_data;
                    temp_ret_960 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                    temp_v0_150 = (void **)(temp_ret_960);
                    temp_a4_2 = ((DW4VC_96_0 *)(temp_v0_150))->vX() % 10000U;
                    temp_s0_28 = (((int) (temp_ret_958 * 3) / (int) temp_s3_12) + 0x64) - ((int) temp_s3_12 / 40);
                    int rec_scaled = (int) (temp_ret_953 * 0xA0) / 100;
                    if ((int) temp_a4_2 < (rec_scaled * temp_s0_28)) {
                        temp_ret_961 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        if (temp_ret_961 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                            temp_ret_962 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_963 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_962));
                        }
                        temp_ret_964 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        temp_ret_965 = beDataBase_GetRecordInt(temp_ret_964, temp_s2_3, &DAT_00519210[0]);
                        var_s1_18 = (int)((int) (temp_ret_965 * temp_s0_28) / 100);
                    }
                    if (var_s1_18 == 0) {
                        var_s1_18 = -1;
                    }
                }
                beMessenger_ClearInt(arg0->_messenger);
                beMessenger_AppendInt(arg0->_messenger, var_s1_18);
            } else {
                temp_ret_966 = strcmp(sp440.p, &DAT_005188d8[0]);
                if (temp_ret_966 == 0) {
                    temp_ret_967 = (int)FUN_003a9250(temp_v0_149, &DAT_00518b78[0]);
                    temp_ret_968 = (void *)(FUN_00406e40((int *)temp_ret_967));
                    temp_v0_151 = (void *)(temp_ret_968);
                    temp_v1_9 = ((igIntList *)temp_v0_151)->_count;
                    if ((temp_v1_9 != 0) && (0 < temp_v1_9)) {
                        temp_s1_10 = DAT_004cf5d8[0];
                        temp_ret_969 = DataList_GetData_003e9090(temp_v0_151);
                        *(int *)temp_ret_969 = temp_s1_10;
                    }
                    FUN_003fab90(arg0, temp_v0_147, 1);
                    temp_ret_971 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    if (temp_ret_971 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                        temp_ret_972 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_973 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_972));
                    }
                    temp_ret_974 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    temp_ret_975 = beDataBase_GetRecordInt(temp_ret_974, temp_s2_3, &DAT_00519200[0]);
                    temp_ret_976 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    if (temp_ret_976 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                        temp_ret_977 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_978 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_977));
                    }
                    temp_ret_979 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    temp_ret_980 = beDataBase_GetRecordInt(temp_ret_979, temp_v0_148, &DAT_005188c0[0]);
                    temp_ret_981 = (int)igProperty_GetRecord(temp_v0_149, &DAT_005188d0[0]);
                    temp_v0_152 = (void *)(temp_ret_981);
                    var_s1_19 = (temp_ret_975 + ((int) ((int) (temp_ret_980 * 0x96) / (int) ((beDataObjInt *)temp_v0_152)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_152)->_data / 80);
                    if (var_s1_19 < 0x14) {
                        var_s1_19 = 0x14;
                    }
                    if (var_s1_19 > 0x50) {
                        var_s1_19 = 0x50;
                    }
                    temp_ret_982 = (int)igProperty_GetRecord(temp_v0_149, &DAT_005188d8[0]);
                    int temp_s0_29 = ((beDataObjInt *)temp_ret_982)->_data;
                    beMessenger_ClearInt(arg0->_messenger);
                    beMessenger_AppendInt(arg0->_messenger, (int) (temp_s0_29 * var_s1_19) / 100);
                } else {
                    temp_ret_983 = strcmp(sp440.p, &DAT_00518950[0]);
                    if (temp_ret_983 == 0) {
                        temp_ret_984 = (int)FUN_003a9250(temp_v0_149, &DAT_00518b78[0]);
                        temp_ret_985 = (void *)(FUN_00406e40((int *)temp_ret_984));
                        temp_v0_153 = (void *)(temp_ret_985);
                        temp_v1_10 = ((igIntList *)temp_v0_153)->_count;
                        if ((temp_v1_10 != 0) && (temp_v1_10 > 1)) {
                            temp_s1_11 = DAT_004cf5e0[0];
                            temp_ret_986 = DataList_GetData_003e9090(temp_v0_153);
                            ((int *)temp_ret_986)[1] = temp_s1_11;
                        }
                        FUN_003fab90(arg0, temp_v0_147, 1);
                        temp_ret_988 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        if (temp_ret_988 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                            temp_ret_989 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_990 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_989));
                        }
                        temp_ret_991 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        temp_ret_992 = beDataBase_GetRecordInt(temp_ret_991, temp_s2_3, &DAT_00519200[0]);
                        temp_ret_993 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        if (temp_ret_993 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                            temp_ret_994 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_995 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_994));
                        }
                        temp_ret_996 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        temp_ret_997 = beDataBase_GetRecordInt(temp_ret_996, temp_v0_148, &DAT_005188c0[0]);
                        temp_ret_998 = (int)igProperty_GetRecord(temp_v0_149, &DAT_005188d0[0]);
                        temp_v0_154 = (void *)(temp_ret_998);
                        var_s1_20 = (temp_ret_992 + ((int) ((int) (temp_ret_997 * 0x96) / (int) ((beDataObjInt *)temp_v0_154)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_154)->_data / 80);
                        if (var_s1_20 < 0x14) {
                            var_s1_20 = 0x14;
                        }
                        if (var_s1_20 > 0x50) {
                            var_s1_20 = 0x50;
                        }
                        temp_ret_999 = (int)igProperty_GetRecord(temp_v0_149, &DAT_00518950[0]);
                        int temp_s0_30 = ((beDataObjInt *)temp_ret_999)->_data;
                        beMessenger_ClearInt(arg0->_messenger);
                        beMessenger_AppendInt(arg0->_messenger, (int) (temp_s0_30 * var_s1_20) / 100);
                    }
                }
            }
            }
            break; }
        case 12: {
            temp_ret_1001 = (char *)(beMessenger_GetString(arg0->_messenger, 1));
            temp_v0_155 = (char *)(temp_ret_1001);
            if (temp_v0_155 == 0) {
                var_v0_21 = (char *)(0);
            } else {
                var_v0_21 = (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_155);
            }
            { StringRef sp43C((char *)(var_v0_21));
            temp_ret_1004 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_v0_156 = temp_ret_1004;
            temp_ret_1005 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_v0_157 = temp_ret_1005;
            temp_ret_1006 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_1007 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_1008 = ObjectList_GetAt_003e9260(temp_ret_1007, temp_v0_156);
            temp_v0_158 = (void *)(temp_ret_1008);
            temp_s2_4 = temp_ret_1006 % 10000;
            temp_ret_1009 = strcmp(sp43C.p, &DAT_005191b8[0]);
            if (temp_ret_1009 == 0) {
                temp_ret_1010 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                if (temp_ret_1010 == 0) {
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                    temp_ret_1011 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_1012 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_1011));
                }
                temp_ret_1013 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                temp_ret_1014 = (char *)(beDataBase_GetRecordString(temp_ret_1013, temp_s2_4, &DAT_005191f0[0]));
                var_s1_21 = 0;
                temp_ret_1015 = strcmp(temp_ret_1014, &DAT_00519250[0]);
                if (temp_ret_1015 == 0) {
                    temp_ret_1016 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    if (temp_ret_1016 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                        temp_ret_1017 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1018 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_1017));
                    }
                    temp_ret_1019 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    temp_ret_1020 = beDataBase_GetRecordInt(temp_ret_1019, temp_s2_4, &DAT_00519200[0]);
                    temp_ret_1021 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    if (temp_ret_1021 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                        temp_ret_1022 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1023 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_1022));
                    }
                    temp_ret_1024 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    temp_ret_1025 = beDataBase_GetRecordInt(temp_ret_1024, temp_v0_157, &DAT_005188c0[0]);
                    temp_ret_1026 = (int)igProperty_GetRecord(temp_v0_158, &DAT_005188d0[0]);
                    temp_s3_13 = ((beDataObjInt *)temp_ret_1026)->_data;
                    temp_ret_1027 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                    temp_v0_159 = (void **)(temp_ret_1027);
                    temp_a4_3 = ((DW4VC_96_0 *)(temp_v0_159))->vX() % 10000U;
                    temp_s0_31 = (((int) (temp_ret_1025 * 3) / (int) temp_s3_13) + 0x64) - ((int) temp_s3_13 / 40);
                    int rec_scaled = (int) (temp_ret_1020 * 0xA0) / 100;
                    if ((int) temp_a4_3 < (rec_scaled * temp_s0_31)) {
                        temp_ret_1028 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        if (temp_ret_1028 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                            temp_ret_1029 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_1030 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_1029));
                        }
                        temp_ret_1031 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        temp_ret_1032 = beDataBase_GetRecordInt(temp_ret_1031, temp_s2_4, &DAT_00519210[0]);
                        var_s1_21 = (int)((int) (temp_ret_1032 * temp_s0_31) / 100);
                    }
                    if (var_s1_21 == 0) {
                        var_s1_21 = -1;
                    }
                }
                beMessenger_ClearInt(arg0->_messenger);
                beMessenger_AppendInt(arg0->_messenger, var_s1_21);
            } else {
                temp_ret_1033 = strcmp(sp43C.p, &DAT_005188b0[0]);
                if (temp_ret_1033 == 0) {
                    temp_ret_1034 = (int)FUN_003a9250(temp_v0_158, &DAT_00518b78[0]);
                    temp_ret_1035 = (void *)(FUN_00406e40((int *)temp_ret_1034));
                    temp_v0_160 = (void *)(temp_ret_1035);
                    temp_v1_11 = ((igIntList *)temp_v0_160)->_count;
                    if ((temp_v1_11 != 0) && (temp_v1_11 > 4)) {
                        temp_s1_12 = DAT_004cf5e8[0];
                        temp_ret_1036 = DataList_GetData_003e9090(temp_v0_160);
                        ((int *)temp_ret_1036)[4] = temp_s1_12;
                    }
                    FUN_003fab90(arg0, temp_v0_156, 1);
                    temp_ret_1038 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    if (temp_ret_1038 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                        temp_ret_1039 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1040 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_1039));
                    }
                    temp_ret_1041 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                    temp_ret_1042 = beDataBase_GetRecordInt(temp_ret_1041, temp_s2_4, &DAT_00519200[0]);
                    temp_ret_1043 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    if (temp_ret_1043 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                        temp_ret_1044 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1045 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_1044));
                    }
                    temp_ret_1046 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                    temp_ret_1047 = beDataBase_GetRecordInt(temp_ret_1046, temp_v0_157, &DAT_005188c0[0]);
                    temp_ret_1048 = (int)igProperty_GetRecord(temp_v0_158, &DAT_005188d0[0]);
                    temp_v0_161 = (void *)(temp_ret_1048);
                    var_s1_22 = (temp_ret_1042 + ((int) ((int) (temp_ret_1047 * 0x96) / (int) ((beDataObjInt *)temp_v0_161)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_161)->_data / 80);
                    if (var_s1_22 < 0x14) {
                        var_s1_22 = 0x14;
                    }
                    if (var_s1_22 > 0x50) {
                        var_s1_22 = 0x50;
                    }
                    temp_ret_1049 = (int)igProperty_GetRecord(temp_v0_158, &DAT_005188b0[0]);
                    int temp_s0_32 = ((beDataObjInt *)temp_ret_1049)->_data;
                    beMessenger_ClearInt(arg0->_messenger);
                    beMessenger_AppendInt(arg0->_messenger, (int) (temp_s0_32 * var_s1_22) / 100);
                } else {
                    temp_ret_1050 = strcmp(sp43C.p, &DAT_005188b8[0]);
                    if (temp_ret_1050 == 0) {
                        temp_ret_1051 = (int)FUN_003a9250(temp_v0_158, &DAT_00518b78[0]);
                        temp_ret_1052 = (void *)(FUN_00406e40((int *)temp_ret_1051));
                        temp_v0_162 = (void *)(temp_ret_1052);
                        temp_v1_12 = ((igIntList *)temp_v0_162)->_count;
                        if ((temp_v1_12 != 0) && (temp_v1_12 > 5)) {
                            temp_s1_13 = DAT_004cf5f0[0];
                            temp_ret_1053 = DataList_GetData_003e9090(temp_v0_162);
                            ((int *)temp_ret_1053)[5] = temp_s1_13;
                        }
                        FUN_003fab90(arg0, temp_v0_156, 1);
                        temp_ret_1055 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        if (temp_ret_1055 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_005194b0[0], &DAT_005194a8[0], 0, &DAT_00519498[0]);
                            temp_ret_1056 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_1057 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEneatk, (ObjectRefTarget *)temp_ret_1056));
                        }
                        temp_ret_1058 = (void *)(FUN_00406ee0(&arg0->_dBEneatk));
                        temp_ret_1059 = beDataBase_GetRecordInt(temp_ret_1058, temp_s2_4, &DAT_00519200[0]);
                        temp_ret_1060 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        if (temp_ret_1060 == 0) {
                            beMessenger_SendNamed(arg0->_messenger, &DAT_00519488[0], &DAT_00519480[0], 0, &DAT_00519470[0]);
                            temp_ret_1061 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                            temp_ret_1062 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBEnemy, (ObjectRefTarget *)temp_ret_1061));
                        }
                        temp_ret_1063 = (void *)(FUN_00406ee0(&arg0->_dBEnemy));
                        temp_ret_1064 = beDataBase_GetRecordInt(temp_ret_1063, temp_v0_157, &DAT_005188c0[0]);
                        temp_ret_1065 = (int)igProperty_GetRecord(temp_v0_158, &DAT_005188d0[0]);
                        temp_v0_163 = (void *)(temp_ret_1065);
                        var_s1_23 = (temp_ret_1059 + ((int) ((int) (temp_ret_1064 * 0x96) / (int) ((beDataObjInt *)temp_v0_163)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_163)->_data / 80);
                        var_s1_23 = (temp_ret_1059 + ((int) ((int) (temp_ret_1064 * 0x96) / (int) ((beDataObjInt *)temp_v0_163)->_data) / 100)) - ((int) ((beDataObjInt *)temp_v0_163)->_data / 80);
                        if (var_s1_23 < 0x14) {
                            var_s1_23 = 0x14;
                        }
                        if (var_s1_23 > 0x50) {
                            var_s1_23 = 0x50;
                        }
                        temp_ret_1066 = (int)igProperty_GetRecord(temp_v0_158, &DAT_005188b8[0]);
                        int temp_s0_33 = ((beDataObjInt *)temp_ret_1066)->_data;
                        beMessenger_ClearInt(arg0->_messenger);
                        beMessenger_AppendInt(arg0->_messenger, (int) (temp_s0_33 * var_s1_23) / 100);
                    }
                }
            }
            }
            break; }
        case 20:
            temp_ret_1068 = beMessenger_GetInt(arg0->_messenger, 0);
            temp_v0_164 = temp_ret_1068;
            temp_ret_1069 = beMessenger_GetInt(arg0->_messenger, 1);
            temp_ret_1070 = beMessenger_GetInt(arg0->_messenger, 2);
            temp_ret_1071 = (void *)(FUN_00407030(&arg0->_playerDataListList));
            temp_ret_1072 = ObjectList_GetAt_003e9260(temp_ret_1071, temp_v0_164);
            temp_v0_165 = (void *)(temp_ret_1072);
            if (temp_v0_164 == temp_ret_1069) {
                temp_s5_4 = temp_ret_1070 % 10000;
                if (temp_s5_4 == 40 || temp_s5_4 == 45) {
                    int sp438;
                    beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_165, temp_s5_4, &sp438);
                    temp_ret_1073 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1073 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1074 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1075 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1074));
                    }
                    temp_ret_1076 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1077 = beDataBase_GetRecordInt(temp_ret_1076, sp438, SKILL);
                    temp_v0_166 = temp_ret_1077;
                    if (temp_v0_166 != 8) {
                        if (temp_v0_166 != 7) {
                            temp_ret_1078 = (int)FUN_003a9250(temp_v0_165, SKILL);
                            temp_ret_1079 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_1078)->_data));
                            temp_ret_1080 = DataList_GetData_003e9090(temp_ret_1079);
                            var_s3_5 = *(int *)(temp_ret_1080 + (temp_v0_166 * 4));
                        } else {
                            temp_ret_1081 = (int)FUN_003a9250(temp_v0_165, SKILL);
                            temp_ret_1082 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_1081)->_data));
                            temp_ret_1083 = DataList_GetData_003e9090(temp_ret_1082);
                            var_s3_5 = ((int *)temp_ret_1083)[7];
                        }
                    } else {
                        temp_ret_1084 = (int)FUN_003a9250(temp_v0_165, SKILL);
                        temp_ret_1085 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_1084)->_data));
                        temp_ret_1086 = DataList_GetData_003e9090(temp_ret_1085);
                        var_s3_5 = ((int *)temp_ret_1086)[8];
                    }
                    temp_ret_1087 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1087 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1088 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1089 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1088));
                    }
                    temp_ret_1090 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1091 = beDataBase_GetRecordInt(temp_ret_1090, sp438, HP);
                    temp_ret_1092 = (int)igProperty_GetRecord(temp_v0_165, &DAT_005188c0[0]);
                    int pre_sum = temp_ret_1091 + var_s3_5;
                    temp_s2_5 = pre_sum + ((beDataObjInt *)temp_ret_1092)->_data;
                    temp_ret_1093 = FUN_003f9c80(arg0, temp_v0_164, temp_s2_5, -1);
                    if (temp_s5_4 == 0x2D) {
                        temp_ret_1094 = (int)FUN_003a92e0(temp_v0_165, &DAT_00518870[0]);
                        temp_ret_1095 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1094)->_data);
                        beMessenger_SendNamed(arg0->_messenger, &DAT_005190a8[0], temp_ret_1095, temp_v0_164, &GETMATRIX[0]);
                        beMessenger_GetMatrix(&sp270, arg0->_messenger, 0);
                        Matrix44_GetTranslation(&sp270, &sp3D8);
                        { NearbyListRef sp434 = beNDMWGameRam_CollectNearbyNonzeroHp(arg0, &DAT_005190a8[0], temp_v0_164, &sp3D8);
                        temp_s3_14 = ((igIntList *)sp434.value)->_count;
                        for (var_s1_24 = 0; var_s1_24 < temp_s3_14; ++var_s1_24) {
                                temp_ret_1096 = DataList_GetData_003e9090(sp434.value);
                                temp_s5_5 = ((int *)temp_ret_1096)[var_s1_24];
                                temp_ret_1097 = FUN_003f9c80(arg0, temp_s5_5, temp_s2_5, -1);
                                temp_ret_1098 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                                temp_ret_1099 = ObjectList_GetAt_003e9260(temp_ret_1098, temp_s5_5);
                                temp_ret_1100 = (int)FUN_003a92e0((void *)temp_ret_1099, &DAT_00518870[0]);
                                temp_ret_1101 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1100)->_data);
                                temp_ret_1102 = beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_005190a8[0], temp_ret_1101, temp_s5_5);
                                beMessenger_AppendString(arg0->_messenger, &DAT_005190b0[0]);
                                beMessenger_AppendString(arg0->_messenger, &DAT_005190c0[0]);
                                beMessenger_AppendFloat(arg0->_messenger, 1.0f);
                                FUN_003e9220(&sp338, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(arg0->_messenger, &sp338);
                                beMessenger_AppendBool(arg0->_messenger, 0U);
                                beMessenger_AppendBool(arg0->_messenger, 1U);
                                temp_ret_1103 = beMessenger_EnqueueSelected(arg0->_messenger, &DAT_005190d0[0], 1);
                        }
                        }
                    }
                } else if (temp_s5_4 == 55 || temp_s5_4 == 60) {
                    int sp430;
                    beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_165, temp_s5_4, &sp430);
                    temp_ret_1104 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1104 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1105 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1106 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1105));
                    }
                    temp_ret_1107 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1108 = beDataBase_GetRecordInt(temp_ret_1107, sp430, SKILL);
                    temp_v0_167 = temp_ret_1108;
                    switch (temp_v0_167) { default: temp_ret_1109 = (int)FUN_003a9250(temp_v0_165, SKILL);
 temp_ret_1110 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_1109)->_data));
 temp_ret_1111 = (int)DataList_GetData_003e9090(temp_ret_1110); break; case 7: temp_ret_1112 = (int)FUN_003a9250(temp_v0_165, SKILL);
 temp_ret_1113 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_1112)->_data));
 temp_ret_1114 = (int)DataList_GetData_003e9090(temp_ret_1113); break; case 8: temp_ret_1115 = (int)FUN_003a9250(temp_v0_165, SKILL);
 temp_ret_1116 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_1115)->_data));
 temp_ret_1117 = DataList_GetData_003e9090(temp_ret_1116); break; }
temp_ret_1118 = (int)FUN_003a92e0(temp_v0_165, &DAT_00518870[0]);
                    temp_ret_1119 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1118)->_data);
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005190a8[0], temp_ret_1119, temp_v0_164, &DAT_00519260[0]);
                    temp_ret_1120 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                    temp_ret_1121 = (void *)(beMessenger_GetObject(arg0->_messenger, 1));
                    temp_v0_168 = (void *)(temp_ret_1121);
                    temp_ret_1122 = FUN_00447b00(temp_v0_168);
                    if (temp_ret_1122 != 0) {
                        temp_s6_3 = ((sp430 - temp_s5_4) + 5) - ((beNDMWMdlPEBaseInfoWork *)temp_v0_168)->_poisonEndurance;
                        temp_ret_1123 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                        temp_v0_169 = (void **)(temp_ret_1123);
                        temp_v0_170 = ((DW4VC_96_0 *)(temp_v0_169))->vX() % 10U;
                        if (temp_s6_3 >= (int) temp_v0_170) {
                            temp_ret_1124 = FUN_00447b40(temp_v0_168, temp_ret_1120);
                        }
                    }
                    if (temp_s5_4 == 0x3C) {
                        temp_ret_1125 = (int)FUN_003a92e0(temp_v0_165, &DAT_00518870[0]);
                        temp_ret_1126 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1125)->_data);
                        beMessenger_SendNamed(arg0->_messenger, &DAT_005190a8[0], temp_ret_1126, temp_v0_164, &GETMATRIX[0]);
                        beMessenger_GetMatrix(&sp230, arg0->_messenger, 0);
                        Matrix44_GetTranslation(&sp230, &sp3C8);
                        { NearbyListRef sp42C = beNDMWGameRam_CollectNearbyNonzeroHp(arg0, &DAT_005190a8[0], temp_v0_164, &sp3C8);
                        temp_v0_171 = ((igIntList *)sp42C.value)->_count;
                        int sp100 = temp_v0_171;
                        for (var_s3_6 = 0; var_s3_6 < sp100; ++var_s3_6) {
                                temp_ret_1127 = DataList_GetData_003e9090(sp42C.value);
                                temp_s2_6 = ((int *)temp_ret_1127)[var_s3_6];
                                temp_ret_1128 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                                temp_ret_1129 = ObjectList_GetAt_003e9260(temp_ret_1128, temp_s2_6);
                                temp_v0_172 = (void *)(temp_ret_1129);
                                temp_ret_1130 = (int)FUN_003a92e0(temp_v0_172, &DAT_00518870[0]);
                                temp_ret_1131 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1130)->_data);
                                beMessenger_SendNamed(arg0->_messenger, &DAT_005190a8[0], temp_ret_1131, temp_s2_6, &DAT_00519260[0]);
                                temp_ret_1132 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                                temp_ret_1133 = (void *)(beMessenger_GetObject(arg0->_messenger, 1));
                                temp_v0_173 = (void *)(temp_ret_1133);
                                temp_ret_1134 = FUN_00447b00(temp_v0_173);
                                if (temp_ret_1134 != 0) {
                                    temp_s8_2 = ((sp430 - temp_s5_4) + 5) - ((beNDMWMdlPEBaseInfoWork *)temp_v0_173)->_poisonEndurance;
                                    temp_ret_1135 = (void **)(FUN_00406e50((int *)(arg0->_system + 0x30)));
                                    temp_v0_174 = (void **)(temp_ret_1135);
                                    temp_v0_175 = ((DW4VC_96_0 *)(temp_v0_174))->vX() % 10U;
                                    if (temp_s8_2 >= (int) temp_v0_175) {
                                        temp_ret_1136 = FUN_00447b40(temp_v0_173, temp_ret_1132);
                                    }
                                }
                                temp_ret_1137 = (int)FUN_003a92e0(temp_v0_172, &DAT_00518870[0]);
                                temp_ret_1138 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1137)->_data);
                                temp_ret_1139 = beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_005190a8[0], temp_ret_1138, temp_s2_6);
                                beMessenger_AppendString(arg0->_messenger, &DAT_00519270[0]);
                                beMessenger_AppendString(arg0->_messenger, &DAT_00519280[0]);
                                beMessenger_AppendFloat(arg0->_messenger, 1.0f);
                                FUN_003e9220(&sp328, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(arg0->_messenger, &sp328);
                                beMessenger_AppendBool(arg0->_messenger, 0U);
                                beMessenger_AppendBool(arg0->_messenger, 1U);
                                temp_ret_1140 = beMessenger_EnqueueSelected(arg0->_messenger, &DAT_005190d0[0], 1);
                        }
                        }
                    }
                } else if (temp_s5_4 == 50 || temp_s5_4 == -50) {
                    if (temp_s5_4 >= 0) {
                        int sp428;
                        beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_165, temp_s5_4, &sp428);
                        temp_a0_10 = sp428 * 4;
                        var_s3_7 = DAT_004cf538[sp428];
                        var_s2_12 = DAT_004cf558[sp428];
                    } else {
                        var_s3_7 = DAT_004cf600[0];
                        var_s2_12 = DAT_004cf620[0];
                    }
                    igMatrix44f_SetIdentity(&sp2B0);
                    temp_ret_1141 = (int)FUN_003a92e0(temp_v0_165, &DAT_00518870[0]);
                    temp_ret_1142 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1141)->_data);
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005190a8[0], temp_ret_1142, temp_v0_164, &GETMATRIX[0]);
                    beMessenger_GetMatrix(&sp1F0, arg0->_messenger, 0);
                    Matrix44_Copy(&sp2B0, &sp1F0);
                    Matrix44_GetTranslation(&sp2B0, &sp3B8);
                    { NearbyListRef sp424 = beNDMWGameRam_CollectNearbyNonzeroHp(arg0, &DAT_00519290[0], -1, &sp3B8);
                    temp_s5_6 = ((igIntList *)sp424.value)->_count;
                    for (var_s1_25 = 0; var_s1_25 < temp_s5_6; ++var_s1_25) {
                            temp_ret_1143 = DataList_GetData_003e9090(sp424.value);
                            beMessenger_SelectReceivers(arg0->_messenger, &DAT_00519290[0], 0, ((int *)temp_ret_1143)[var_s1_25]);
                            beMessenger_AppendMatrix(arg0->_messenger, &sp2B0);
                            beMessenger_AppendInt(arg0->_messenger, var_s3_7);
                            beMessenger_AppendInt(arg0->_messenger, var_s2_12);
                            beMessenger_DispatchSelected(arg0->_messenger, (const char *)&DAT_00519298[0]);
                    }
                    }
                } else if (temp_s5_4 == 65) {
                    int sp420;
                    beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_165, temp_s5_4, &sp420);
                    temp_ret_1145 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1145 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1146 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1147 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1146));
                    }
                    temp_ret_1148 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1149 = beDataBase_GetRecordInt(temp_ret_1148, sp420, SKILL);
                    temp_ret_1150 = (int)igProperty_GetRecord(temp_v0_165, &DAT_005188c0[0]);
                    temp_s2_7 = ((beDataObjInt *)temp_ret_1150)->_data;
                    temp_ret_1151 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1151 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1152 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1153 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1152));
                    }
                    temp_ret_1154 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1155 = beDataBase_GetRecordInt(temp_ret_1154, sp420, &DAT_005191b8[0]);
                    int spF0 = temp_ret_1155 + temp_s2_7;
                    temp_ret_1156 = (int)FUN_003a9250(temp_v0_165, SKILL);
                    temp_ret_1157 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_1156)->_data));
                    temp_ret_1158 = DataList_GetData_003e9090(temp_ret_1157);
                    temp_s2_8 = *(int *)(temp_ret_1158 + (temp_ret_1149 * 4));
                    temp_ret_1159 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1159 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1160 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1161 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1160));
                    }
                    temp_ret_1162 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1163 = beDataBase_GetRecordInt(temp_ret_1162, sp420, &DAT_005188d8[0]);
                    int spE0 = ((int) temp_s2_8 / 5) + temp_ret_1163;
                    temp_ret_1164 = (int)FUN_003a92e0(temp_v0_165, &DAT_00518870[0]);
                    temp_ret_1165 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1164)->_data);
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005190a8[0], temp_ret_1165, temp_v0_164, &GETMATRIX[0]);
                    beMessenger_GetMatrix(&sp1B0, arg0->_messenger, 0);
                    Matrix44_GetTranslation(&sp1B0, &sp3A8);
                    { NearbyListRef sp41C = beNDMWGameRam_CollectNearbyNonzeroHp(arg0, &DAT_005190a8[0], temp_v0_164, &sp3A8);
                    temp_ret_1166 = (void *)(FUN_00406dc0((int *)&sp41C.value));
                    temp_v0_176 = (void *)(temp_ret_1166);
                    RecoveryList::append(temp_v0_176, temp_v0_164);
                    temp_v0_177 = ((igIntList *)sp41C.value)->_count;
                    int spD0 = temp_v0_177;
                    for (var_s5_8 = 0; var_s5_8 < spD0; ++var_s5_8) {
                            temp_ret_1168 = DataList_GetData_003e9090(sp41C.value);
                            temp_s3_15 = ((int *)temp_ret_1168)[var_s5_8];
                            temp_ret_1169 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                            temp_ret_1170 = ObjectList_GetAt_003e9260(temp_ret_1169, temp_s3_15);
                            temp_v0_178 = (void *)(temp_ret_1170);
                            temp_ret_1171 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                            if (temp_ret_1171 == 0) {
                                beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                                temp_ret_1172 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                                temp_ret_1173 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1172));
                            }
                            temp_ret_1174 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                            temp_ret_1175 = beDataBase_GetRecordInt(temp_ret_1174, sp420, &DAT_00518960[0]);
                            temp_ret_1176 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                            if (temp_ret_1176 == 0) {
                                beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                                temp_ret_1177 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                                temp_ret_1178 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1177));
                            }
                            temp_ret_1179 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                            temp_ret_1180 = beDataBase_GetRecordInt(temp_ret_1179, sp420, &DAT_005191c0[0]);
                            temp_ret_1181 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                            if (temp_ret_1181 == 0) {
                                beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                                temp_ret_1182 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                                temp_ret_1183 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1182));
                            }
                            temp_ret_1184 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                            temp_ret_1185 = beDataBase_GetRecordInt(temp_ret_1184, sp420, &DAT_00518980[0]);
                            beMessenger_PushArgContext(arg0->_messenger);
                            temp_ret_1186 = (int)FUN_003a92e0(temp_v0_178, &DAT_00518870[0]);
                            temp_ret_1187 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1186)->_data);
                            beMessenger_SelectReceivers(arg0->_messenger, &DAT_005190a8[0], temp_ret_1187, temp_s3_15);
                            beMessenger_AppendInt(arg0->_messenger, spF0);
                            beMessenger_AppendInt(arg0->_messenger, spE0);
                            beMessenger_AppendInt(arg0->_messenger, temp_ret_1175);
                            beMessenger_AppendInt(arg0->_messenger, temp_ret_1180);
                            beMessenger_AppendInt(arg0->_messenger, temp_ret_1185);
                            beMessenger_DispatchSelected(arg0->_messenger, (const char *)&DAT_005192a0[0]);
                            if (temp_s3_15 != temp_v0_164) {
                                temp_ret_1189 = (int)FUN_003a92e0(temp_v0_178, &DAT_00518870[0]);
                                temp_ret_1190 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1189)->_data);
                                temp_ret_1191 = beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_005190a8[0], temp_ret_1190, temp_s3_15);
                                beMessenger_AppendString(arg0->_messenger, &DAT_005192b0[0]);
                                beMessenger_AppendString(arg0->_messenger, &DAT_005192c0[0]);
                                beMessenger_AppendFloat(arg0->_messenger, 1.0f);
                                FUN_003e9220(&sp318, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(arg0->_messenger, &sp318);
                                beMessenger_AppendBool(arg0->_messenger, 0U);
                                beMessenger_AppendBool(arg0->_messenger, 1U);
                                temp_ret_1192 = beMessenger_EnqueueSelected(arg0->_messenger, &DAT_005190d0[0], 1);
                            }
                            beMessenger_PopArgContext(arg0->_messenger);
                    }
                    }
                } else if (temp_s5_4 == 80) {
                    int sp418;
                    beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_165, temp_s5_4, &sp418);
                    temp_ret_1193 = (int)igProperty_GetRecord(temp_v0_165, &DAT_005188c0[0]);
                    temp_s2_9 = ((beDataObjInt *)temp_ret_1193)->_data;
                    temp_ret_1194 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1194 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1195 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1196 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1195));
                    }
                    temp_ret_1197 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1198 = beDataBase_GetRecordInt(temp_ret_1197, sp418, &DAT_005191b8[0]);
                    int sum80a = temp_ret_1198 + temp_s2_9;
                    temp_ret_1199 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1199 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1200 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1201 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1200));
                    }
                    temp_ret_1202 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1203 = beDataBase_GetRecordInt(temp_ret_1202, sp418, SKILL);
                    temp_ret_1204 = (int)FUN_003a9250(temp_v0_165, SKILL);
                    temp_ret_1205 = (void *)(FUN_00406ef0(&((beDataObjIntList *)temp_ret_1204)->_data));
                    temp_ret_1206 = DataList_GetData_003e9090(temp_ret_1205);
                    temp_s2_10 = *(int *)(temp_ret_1206 + (temp_ret_1203 * 4));
                    temp_ret_1207 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1207 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1208 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1209 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1208));
                    }
                    temp_ret_1210 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_s2_11 = (int)((int) temp_s2_10 / 5);
                    temp_ret_1211 = beDataBase_GetRecordInt(temp_ret_1210, sp418, &DAT_00518fc8[0]);
                    int sum80d = temp_s2_11 + temp_ret_1211;
                    temp_ret_1212 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1212 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1213 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1214 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1213));
                    }
                    temp_ret_1215 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1216 = beDataBase_GetRecordInt(temp_ret_1215, sp418, &DAT_005188b0[0]);
                    int spC0 = temp_s2_11 + temp_ret_1216;
                    temp_ret_1217 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1217 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1218 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1219 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1218));
                    }
                    temp_ret_1220 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1221 = beDataBase_GetRecordInt(temp_ret_1220, sp418, &DAT_005188b8[0]);
                    int spB0 = temp_s2_11 + temp_ret_1221;
                    temp_ret_1222 = (int)FUN_003a92e0(temp_v0_165, &DAT_00518870[0]);
                    temp_ret_1223 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1222)->_data);
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005190a8[0], temp_ret_1223, temp_v0_164, &GETMATRIX[0]);
                    beMessenger_GetMatrix(&sp170, arg0->_messenger, 0);
                    Matrix44_GetTranslation(&sp170, &sp398);
                    { NearbyListRef sp414 = beNDMWGameRam_CollectNearbyNonzeroHp(arg0, &DAT_005190a8[0], temp_v0_164, &sp398);
                    temp_ret_1224 = (void *)(FUN_00406dc0((int *)&sp414.value));
                    temp_v0_179 = (void *)(temp_ret_1224);
                    RecoveryList::append(temp_v0_179, temp_v0_164);
                    temp_s6_4 = ((igIntList *)sp414.value)->_count;
                    for (var_s5_9 = 0; var_s5_9 < temp_s6_4; ++var_s5_9) {
                            temp_ret_1226 = DataList_GetData_003e9090(sp414.value);
                            temp_s3_16 = ((int *)temp_ret_1226)[var_s5_9];
                            temp_ret_1227 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                            temp_ret_1228 = ObjectList_GetAt_003e9260(temp_ret_1227, temp_s3_16);
                            temp_v0_180 = (void *)(temp_ret_1228);
                            beMessenger_PushArgContext(arg0->_messenger);
                            temp_ret_1229 = (int)FUN_003a92e0(temp_v0_180, &DAT_00518870[0]);
                            temp_ret_1230 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1229)->_data);
                            beMessenger_SelectReceivers(arg0->_messenger, &DAT_005190a8[0], temp_ret_1230, temp_s3_16);
                            beMessenger_AppendInt(arg0->_messenger, sum80a);
                            beMessenger_AppendInt(arg0->_messenger, spC0);
                            beMessenger_AppendInt(arg0->_messenger, spB0);
                            beMessenger_AppendInt(arg0->_messenger, sum80d);
                            beMessenger_DispatchSelected(arg0->_messenger, (const char *)&DAT_005192d0[0]);
                            if (temp_s3_16 != temp_v0_164) {
                                temp_ret_1232 = (int)FUN_003a92e0(temp_v0_180, &DAT_00518870[0]);
                                temp_ret_1233 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1232)->_data);
                                temp_ret_1234 = beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_005190a8[0], temp_ret_1233, temp_s3_16);
                                beMessenger_AppendString(arg0->_messenger, &DAT_005192b0[0]);
                                beMessenger_AppendString(arg0->_messenger, &DAT_005192c0[0]);
                                beMessenger_AppendFloat(arg0->_messenger, 1.0f);
                                FUN_003e9220(&sp308, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(arg0->_messenger, &sp308);
                                beMessenger_AppendBool(arg0->_messenger, 0U);
                                beMessenger_AppendBool(arg0->_messenger, 1U);
                                temp_ret_1235 = beMessenger_EnqueueSelected(arg0->_messenger, &DAT_005190d0[0], 1);
                            }
                            beMessenger_PopArgContext(arg0->_messenger);
                    }
                    }
                } else if (temp_s5_4 == 75) {
                    int sp410;
                    beNDMWGameRam_FindTechniqueRow(arg0, temp_v0_165, temp_s5_4, &sp410);
                    temp_ret_1236 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1236 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1237 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1238 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1237));
                    }
                    temp_ret_1239 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1240 = beDataBase_GetRecordInt(temp_ret_1239, sp410, &DAT_005191b8[0]);
                    temp_ret_1241 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1241 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1242 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1243 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1242));
                    }
                    temp_ret_1244 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1245 = beDataBase_GetRecordInt(temp_ret_1244, sp410, &DAT_005192e0[0]);
                    int spAC = temp_ret_1245;
                    temp_ret_1246 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1246 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1247 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1248 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1247));
                    }
                    temp_ret_1249 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1250 = beDataBase_GetRecordInt(temp_ret_1249, sp410, &DAT_005192e8[0]);
                    int spA8 = temp_ret_1250;
                    temp_ret_1251 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1251 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1252 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1253 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1252));
                    }
                    temp_ret_1254 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1255 = beDataBase_GetRecordInt(temp_ret_1254, sp410, &DAT_005192f0[0]);
                    int spA4 = temp_ret_1255;
                    temp_ret_1256 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    if (temp_ret_1256 == 0) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00519460[0], &DAT_00519458[0], 0, &DAT_00519448[0]);
                        temp_ret_1257 = (void *)(beMessenger_GetObject(arg0->_messenger, 0));
                        temp_ret_1258 = (int *)(ObjectRef_AssignObject_00406e60((ObjectRefTarget **)&arg0->_dBPcTech, (ObjectRefTarget *)temp_ret_1257));
                    }
                    temp_ret_1259 = (void *)(FUN_00406ee0(&arg0->_dBPcTech));
                    temp_ret_1260 = beDataBase_GetRecordInt(temp_ret_1259, sp410, &DAT_005192f8[0]);
                    temp_ret_1261 = (int)FUN_003a92e0(temp_v0_165, &DAT_00518870[0]);
                    temp_ret_1262 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1261)->_data);
                    beMessenger_SendNamed(arg0->_messenger, &DAT_005190a8[0], temp_ret_1262, temp_v0_164, &GETMATRIX[0]);
                    beMessenger_GetMatrix(&sp130, arg0->_messenger, 0);
                    Matrix44_GetTranslation(&sp130, &sp388);
                    { NearbyListRef sp40C = beNDMWGameRam_CollectNearbyNonzeroHp(arg0, &DAT_005190a8[0], temp_v0_164, &sp388);
                    temp_ret_1263 = (void *)(FUN_00406dc0((int *)&sp40C.value));
                    temp_v0_181 = (void *)(temp_ret_1263);
                    RecoveryList::append(temp_v0_181, temp_v0_164);
                    temp_s6_5 = ((igIntList *)sp40C.value)->_count;
                    for (var_s5_10 = 0; var_s5_10 < temp_s6_5; ++var_s5_10) {
                            temp_ret_1265 = DataList_GetData_003e9090(sp40C.value);
                            temp_s3_17 = ((int *)temp_ret_1265)[var_s5_10];
                            temp_ret_1266 = (void *)(FUN_00407030(&arg0->_playerDataListList));
                            temp_ret_1267 = ObjectList_GetAt_003e9260(temp_ret_1266, temp_s3_17);
                            temp_v0_182 = (void *)(temp_ret_1267);
                            beMessenger_PushArgContext(arg0->_messenger);
                            temp_ret_1268 = (int)FUN_003a92e0(temp_v0_182, &DAT_00518870[0]);
                            temp_ret_1269 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1268)->_data);
                            beMessenger_SelectReceivers(arg0->_messenger, &DAT_005190a8[0], temp_ret_1269, temp_s3_17);
                            beMessenger_AppendInt(arg0->_messenger, temp_ret_1240);
                            beMessenger_AppendInt(arg0->_messenger, spAC);
                            beMessenger_AppendInt(arg0->_messenger, spA8);
                            beMessenger_AppendInt(arg0->_messenger, spA4);
                            beMessenger_AppendInt(arg0->_messenger, temp_ret_1260);
                            beMessenger_DispatchSelected(arg0->_messenger, (const char *)&DAT_00519300[0]);
                            if (temp_s3_17 != temp_v0_164) {
                                temp_ret_1271 = (int)FUN_003a92e0(temp_v0_182, &DAT_00518870[0]);
                                temp_ret_1272 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1271)->_data);
                                temp_ret_1273 = beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_005190a8[0], temp_ret_1272, temp_s3_17);
                                beMessenger_AppendString(arg0->_messenger, &DAT_005192b0[0]);
                                beMessenger_AppendString(arg0->_messenger, &DAT_005192c0[0]);
                                beMessenger_AppendFloat(arg0->_messenger, 1.0f);
                                FUN_003e9220(&sp2F8, &g_vec3Zero[0]);
                                beMessenger_AppendVec3(arg0->_messenger, &sp2F8);
                                beMessenger_AppendBool(arg0->_messenger, 0U);
                                beMessenger_AppendBool(arg0->_messenger, 1U);
                                temp_ret_1274 = beMessenger_EnqueueSelected(arg0->_messenger, &DAT_005190d0[0], 1);
                            }
                            beMessenger_PopArgContext(arg0->_messenger);
                    }
                    }
                }
                beMessenger_ClearInt(arg0->_messenger);
                beMessenger_AppendInt(arg0->_messenger, 1);
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
        tail_idx = beMessenger_GetInt(arg0->_messenger, 0);
                tail_common = (void *)(FUN_00407040(&arg0->_commonDataList));
                temp_ret_1278 = (void *)(FUN_00407030(&arg0->_playerDataListList));
        tail_player = (void *)ObjectList_GetAt_003e9260(temp_ret_1278, tail_idx);
                temp_ret_1280 = (int)FUN_003a92e0(tail_player, &DAT_00518870[0]);
        temp_ret_1281 = (const char *)FUN_00407050(&((beDataObjString *)temp_ret_1280)->_data);
        temp_v0_186 = temp_ret_1281;
        DW4StrListOps::SetAt((igStringRefList *)FUN_00406db0((int *)(FUN_003a9310(tail_common, &DAT_005187e8[0]))), tail_idx, StringRef(temp_v0_186 == 0 ? (char *)0 : (char *)StringPool_Intern(StringPool_GetInstance(), temp_v0_186)));
        temp_s0_34 = tail_idx * 2;
        temp_ret_1289 = (int)igProperty_GetRecord(tail_player, &DAT_00518840[0]);
        temp_s3_18 = ((beDataObjInt *)temp_ret_1289)->_data;
        temp_ret_1290 = (int)FUN_003a9250(tail_common, &DAT_005187d8[0]);
        temp_ret_1291 = (void *)(FUN_00406e40((int *)temp_ret_1290));
        temp_v0_188 = (void *)(temp_ret_1291);
        temp_v1_14 = ((igIntList *)temp_v0_188)->_count;
        if ((temp_v1_14 != 0) && (temp_s0_34 >= 0) && (temp_s0_34 < temp_v1_14)) {
            temp_ret_1292 = DataList_GetData_003e9090(temp_v0_188);
            *(int *)(temp_ret_1292 + (temp_s0_34 * 4)) = temp_s3_18;
        }
        temp_ret_1293 = (int)igProperty_GetRecord(tail_player, &DAT_00518840[0]);
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
            temp_ret_1296 = (int)FUN_003a9250(tail_common, &DAT_005187d8[0]);
            temp_ret_1297 = (void *)(FUN_00406e40((int *)temp_ret_1296));
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

void FUN_00406f20(void *list, int index)
{
    List_RemoveWordAt(list, index);
}

DW4Sret4 FUN_00406f40(int value)
{
    return DW4Sret4(value);
}

DW4Sret4 FUN_00406f50(int value)
{
    return DW4Sret4(value);
}

DW4Sret4 FUN_00406f60(int value)
{
    return DW4Sret4(value);
}

DW4Sret4 FUN_00406f70(int value)
{
    return DW4Sret4(value);
}

int FUN_00406f80(int *p)
{
    return *(int *)((char *)p + 0);
}

int FUN_00406f90(beDataObjInt *p)
{
    return p->_data;
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

