/* FUN_003fab90 (0x003fab90, 6,872 bytes): recompute one player's derived stats.
 *
 * `self` is the GAMERAM object; `index` selects the player record out of its
 * player list and `apply` says whether the equipment/chip/skill modifiers are
 * applied on top of the database/UPDATA/DOWNDATA base values.  The function
 *   - rewrites MHP/MMP (clamped to 99999) and initialises or clamps HP and MP,
 *   - rewrites the five attributes (TSUYOSA, MAMORI, KASHIKOSA, SEISHIN,
 *     SUBAYASA) and the four element resistances, each clamped to 1..9999,
 *   - rebuilds WAZALIST from the six TECHn level/skill thresholds of the
 *     species' database row and rewrites NEXTEXP from the level,
 *   - when `apply` is set also rewrites ATTACKDELAY, the hit, critical,
 *     paralysis, evade, guard, bit, experience and luck rates, the
 *     paralysis/poison resistances, the weapon element, HP/MP drain and the
 *     weapon record/skill numbers, and refreshes POWERSOCKETNAME from the
 *     MODEL string of every power socket.
 *
 * The property record names (DAT_0051xxxx) are read from the retail image;
 * the PROP_* aliases below give them their literal text.  The callees whose
 * behaviour is not recovered yet keep their FUN_ names.
 *
 * Matching notes.  Everything here is a compiler-pinned spelling (see
 * docs/engine/unit-compilers.md); the choices that matter for the register
 * colouring and stack layout are:
 *   - the player pointer and the DIGIMONNO / LEVEL reads go through the tiny
 *     inline accessors StatHelpers::GetPlayer() and GetProp(); their result
 *     temporaries are created late, so the register colouring orders the player
 *     pointer, index and spill slots as in retail;
 *   - the helpers are static members of a struct because tools/units.py splits
 *     a unit at its top-level definitions and would drop free helper functions;
 *   - locals are declared where they are first set, one variable per loop;
 *   - the two threshold tests are written as `record <= value` and the delay
 *     clamp as `> 70`, the forms that keep the compare in `at`;
 *   - the new WAZALIST object is an IntListRef (a stack-resident reference
 *     whose destructor is the emitted body at 0x003fc670, shared with the
 *     nearby query that is compiled in the same unit);
 *   - the interned MODEL string handed to StringList_AppendRetained is a StringRef whose
 *     destructor is the retail copy at 0x00130720 (a duplicate in config/SLUS-20836/unit-objects.json).
 * The unit also owns that query (0x003fc780) and the reference destructor
 * (0x003fc670) through config/SLUS-20836/unit-objects.json; the query lives in the
 * included .inc so that one object holds all three bodies.  The include path
 * is relative to the repository root (the compiler's working directory).
 */
#include "src/game/beNDMWGameRam_CollectNearbyNonzeroHp.inc"

#define PROP_DIGIMONNO       DAT_00518848
#define PROP_LEVEL           DAT_00518858
#define PROP_SKILL           DAT_00518860
#define PROP_UPCNT           DAT_00518868
#define PROP_HP              DAT_00518890
#define PROP_MHP             DAT_00518898
#define PROP_MP              DAT_005188a0
#define PROP_MMP             DAT_005188a8
#define PROP_TSUYOSA         DAT_005188b0
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
#define PROP_POWERSOCKET     DAT_00518a88
#define PROP_POWERSOCKETNAME DAT_00518aa0
#define PROP_POWERPOCKET     DAT_00518ab0
#define PROP_UPDATA          DAT_00518b70
#define PROP_DOWNDATA        DAT_00518b78
#define PROP_MODEL           DAT_00518c08
#define PROP_MAXHP           DAT_00518fc8
#define PROP_MAXMP           DAT_00518fd0
#define PROP_RES_FIRE        DAT_00518fd8
#define PROP_RES_ICE         DAT_00518fe8
#define PROP_RES_THUNDER     DAT_00518ff0
#define PROP_RES_DARK        DAT_00519000
#define PROP_DELAY           DAT_00519010
#define PROP_ZOKUSEI         DAT_00519018

extern "C" {
extern char DAT_00518848[], DAT_00518858[], DAT_00518860[], DAT_00518868[];
extern char DAT_00518890[], DAT_00518898[], DAT_005188a0[], DAT_005188a8[];
extern char DAT_005188b0[], DAT_005188b8[], DAT_005188c0[], DAT_005188d0[], DAT_005188d8[];
extern char DAT_005188e8[], DAT_005188f8[], DAT_00518908[], DAT_00518918[];
extern char DAT_00518928[], DAT_00518938[], DAT_00518940[];
extern char DAT_00518950[], DAT_00518960[], DAT_00518970[], DAT_00518980[], DAT_00518990[];
extern char DAT_005189a0[], DAT_005189b0[], DAT_005189c0[], DAT_005189d0[], DAT_005189e0[];
extern char DAT_005189f0[], DAT_00518a00[], DAT_00518a08[], DAT_00518a10[];
extern char DAT_00518a20[], DAT_00518a30[], DAT_00518a88[], DAT_00518aa0[], DAT_00518ab0[];
extern char DAT_00518b70[], DAT_00518b78[], DAT_00518c08[];
extern char DAT_00518fc8[], DAT_00518fd0[], DAT_00518fd8[], DAT_00518fe8[], DAT_00518ff0[], DAT_00519000[];
extern char DAT_00519010[], DAT_00519018[];
extern char DAT_00519420[], DAT_00519430[], DAT_00519438[], DAT_00519448[], DAT_00519458[], DAT_00519460[];
}

struct IntRec { char pad[12]; int value; };
struct BonusObj { char pad[16]; int *v; };
struct BonusRec { char pad[12]; BonusObj *obj; };
struct ListHolder { char pad[12]; igObjectList *list; };
struct StrListHolder { char pad[12]; igStringRefList *list; };

extern "C" {
extern void beMessenger_SendNamed(int, const char *, const char *, int, const char *);
extern igObject *beMessenger_GetObject(int, int);
extern int beDataBase_GetRecordInt(igObject *, int, const char *);
extern IntRec *igProperty_GetRecord(void *, const char *);
extern ListHolder *igProperty_GetRecordFolder(void *, const char *);
extern BonusRec *FUN_003a9250(void *, const char *);
extern StrListHolder *FUN_003a9310(void *, const char *);
extern void StringList_AppendRetained(igStringRefList *, char **);
extern int FUN_003fa3b0(beNDMWGameRam *, int, int, int);
extern int FUN_003fa850(beNDMWGameRam *, int, int, int);
extern void FUN_003f9f80(beNDMWGameRam *, void *, int *, const char *, int);
extern void FUN_003fa040(beNDMWGameRam *, void *, int *, const char *);
extern void FUN_003fa120(beNDMWGameRam *, void *, int *, const char *, int);
extern void FUN_003fa1e0(beNDMWGameRam *, void *, int *, const char *);
extern void FUN_003fa2c0(beNDMWGameRam *, void *, int *, const char *, int);
extern void FUN_00448f30(igObject *, int, int);
extern igObject *FUN_003c8040(int);
extern void ObjectList_AppendRetained(igObjectList *, igObject *);
extern int FUN_002eb010(int);
extern int StringPool_Construct(int);
extern char *StringPool_Intern(int, const char *);
extern void StringChunk_ReleaseHeader(int, int *);
extern int igStrCmp(const char *, const char *);
extern int beNDMWItemBase_GetRecordInt(beNDMWItemBase *, beNDMWGameRam *, const char *);
extern const char *beNDMWItemBase_GetRecordString(beNDMWItemBase *, beNDMWGameRam *, const char *);
extern int DAT_00586f20[4];   /* interned-string pool */
extern int DAT_00587108[4];   /* allocator selector */
extern const char *DAT_004cf290[6];     /* "TECH1".."TECH6" */
extern const char *DAT_004cf2b0[6];     /* "TECH1_LEVEL".. */
extern const char *DAT_004cf2d0[6][5];  /* "TECH1_SKILL1".. */
extern const char *DAT_004cf350[4];     /* "fire", "ice", "thunder", "dark" */
}
/* Interned-string reference (count at p[-1], header at p[-2]); its destructor copy is the retail StringRef at 0x00130720. */
struct StringRef {
    char *p;
    StringRef(char *s) { p = s; }
    ~StringRef() {
        if (p) {
            int *header = (int *)(p - 8);
            if (--header[1] == 0) StringChunk_ReleaseHeader(header[0], header);
        }
    }
};

/* The helpers are static members so the one-function unit split keeps them. */
struct StatHelpers {
    static inline void release_ref(igObject *object)
    {
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }

    /* Lazily fetched database handles, cached on the GAMERAM object. */
    static inline igObject *shinka(beNDMWGameRam *g)
    {
        if (!g->_dBShinka) {
            igObject *fetched;
            beMessenger_SendNamed(g->_messenger, DAT_00519438, DAT_00519430, 0, DAT_00519420);
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

#define SHINKA(g) StatHelpers::shinka(g)
#define PCTECH(g) StatHelpers::pctech(g)
#define RELEASE(o) StatHelpers::release_ref(o)
/* An attribute is clamped to 1..9999. */
#define CLAMP_ATTR(v) if ((v) <= 0) (v) = 1; if ((v) > 9999) (v) = 9999;

extern "C" void FUN_003fab90(beNDMWGameRam *self, int index, unsigned char apply)
{
    void *player = StatHelpers::GetPlayer(self, index);
    int species = StatHelpers::GetProp(player, PROP_DIGIMONNO);
    int level = StatHelpers::GetProp(player, PROP_LEVEL);
    unsigned char first = 0;

    /* MHP / HP */
    int mhp = FUN_003fa3b0(self, index, -1, 1);
    mhp += FUN_003a9250(player, PROP_UPDATA)->obj->v[6];
    if (apply) {
        FUN_003fa120(self, player, &mhp, PROP_MAXHP, 0);
        FUN_003fa2c0(self, player, &mhp, PROP_MAXHP, 0);
    }
    if (mhp > 99999) mhp = 99999;
    igProperty_GetRecord(player, PROP_MHP)->value = mhp;
    int curHp = igProperty_GetRecord(player, PROP_HP)->value;
    if (curHp == 0) first = 1;
    if (curHp == 0 || mhp < curHp) igProperty_GetRecord(player, PROP_HP)->value = mhp;

    /* MMP / MP: a fresh player (HP was unset) also gets full MP */
    int mmp = FUN_003fa3b0(self, index, -1, 0);
    if (apply) {
        FUN_003fa120(self, player, &mmp, PROP_MAXMP, 0);
        FUN_003fa2c0(self, player, &mmp, PROP_MAXMP, 0);
    }
    if (mmp > 99999) mmp = 99999;
    igProperty_GetRecord(player, PROP_MMP)->value = mmp;
    int curMp = igProperty_GetRecord(player, PROP_MP)->value;
    if (first || mmp < curMp) igProperty_GetRecord(player, PROP_MP)->value = mmp;

    /* attributes: database value (+ UPDATA - DOWNDATA) then the modifiers */
    int tsuyosa = FUN_003fa850(self, index, -1, 0);
    tsuyosa += FUN_003a9250(player, PROP_UPDATA)->obj->v[4];
    tsuyosa -= FUN_003a9250(player, PROP_DOWNDATA)->obj->v[4];
    if (apply) {
        FUN_003f9f80(self, player, &tsuyosa, PROP_TSUYOSA, 1);
        FUN_003fa040(self, player, &tsuyosa, PROP_TSUYOSA);
        FUN_003fa2c0(self, player, &tsuyosa, PROP_TSUYOSA, 1);
    }
    CLAMP_ATTR(tsuyosa)
    igProperty_GetRecord(player, PROP_TSUYOSA)->value = tsuyosa;

    int mamori = FUN_003fa850(self, index, -1, 1);
    mamori += FUN_003a9250(player, PROP_UPDATA)->obj->v[5];
    mamori -= FUN_003a9250(player, PROP_DOWNDATA)->obj->v[5];
    if (apply) {
        FUN_003fa120(self, player, &mamori, PROP_MAMORI, 1);
        FUN_003fa2c0(self, player, &mamori, PROP_MAMORI, 1);
    }
    CLAMP_ATTR(mamori)
    igProperty_GetRecord(player, PROP_MAMORI)->value = mamori;

    int kashikosa = FUN_003fa850(self, index, -1, 2);
    if (apply) {
        FUN_003f9f80(self, player, &kashikosa, PROP_KASHIKOSA, 0);
        FUN_003fa040(self, player, &kashikosa, PROP_KASHIKOSA);
        FUN_003fa120(self, player, &kashikosa, PROP_KASHIKOSA, 0);
        FUN_003fa1e0(self, player, &kashikosa, PROP_KASHIKOSA);
        FUN_003fa2c0(self, player, &kashikosa, PROP_KASHIKOSA, 1);
    }
    CLAMP_ATTR(kashikosa)
    igProperty_GetRecord(player, PROP_KASHIKOSA)->value = kashikosa;

    int seishin = FUN_003fa850(self, index, -1, 3);
    if (apply) {
        FUN_003f9f80(self, player, &seishin, PROP_SEISHIN, 0);
        FUN_003fa040(self, player, &seishin, PROP_SEISHIN);
        FUN_003fa120(self, player, &seishin, PROP_SEISHIN, 0);
        FUN_003fa1e0(self, player, &seishin, PROP_SEISHIN);
        FUN_003fa2c0(self, player, &seishin, PROP_SEISHIN, 0);
    }
    CLAMP_ATTR(seishin)
    igProperty_GetRecord(player, PROP_SEISHIN)->value = seishin;

    int subayasa = FUN_003fa850(self, index, -1, 4);
    subayasa += FUN_003a9250(player, PROP_UPDATA)->obj->v[0];
    subayasa -= FUN_003a9250(player, PROP_DOWNDATA)->obj->v[0];
    if (apply) {
        FUN_003f9f80(self, player, &subayasa, PROP_SUBAYASA, 0);
        FUN_003fa040(self, player, &subayasa, PROP_SUBAYASA);
        FUN_003fa120(self, player, &subayasa, PROP_SUBAYASA, 0);
        FUN_003fa1e0(self, player, &subayasa, PROP_SUBAYASA);
        FUN_003fa2c0(self, player, &subayasa, PROP_SUBAYASA, 1);
    }
    CLAMP_ATTR(subayasa)
    igProperty_GetRecord(player, PROP_SUBAYASA)->value = subayasa;

    /* element resistances: species row + UPCNT + UPDATA, then the modifiers */
    int fire = beDataBase_GetRecordInt(SHINKA(self), species, PROP_RES_FIRE);
    fire += FUN_003a9250(player, PROP_UPCNT)->obj->v[7];
    fire += FUN_003a9250(player, PROP_UPDATA)->obj->v[7];
    if (apply) {
        FUN_003fa120(self, player, &fire, PROP_RES_FIRE, 0);
        FUN_003fa1e0(self, player, &fire, PROP_RES_FIRE);
        FUN_003fa2c0(self, player, &fire, PROP_RES_FIRE, 1);
    }
    CLAMP_ATTR(fire)
    igProperty_GetRecord(player, PROP_HONOOTEIKO)->value = fire;
    int ice = beDataBase_GetRecordInt(SHINKA(self), species, PROP_RES_ICE);
    ice += FUN_003a9250(player, PROP_UPCNT)->obj->v[8];
    ice += FUN_003a9250(player, PROP_UPDATA)->obj->v[8];
    if (apply) {
        FUN_003fa120(self, player, &ice, PROP_RES_ICE, 0);
        FUN_003fa1e0(self, player, &ice, PROP_RES_ICE);
        FUN_003fa2c0(self, player, &ice, PROP_RES_ICE, 1);
    }
    CLAMP_ATTR(ice)
    igProperty_GetRecord(player, PROP_KOORITEIKO)->value = ice;
    int thunder = beDataBase_GetRecordInt(SHINKA(self), species, PROP_RES_THUNDER);
    thunder += FUN_003a9250(player, PROP_UPCNT)->obj->v[9];
    thunder += FUN_003a9250(player, PROP_UPDATA)->obj->v[9];
    if (apply) {
        FUN_003fa120(self, player, &thunder, PROP_RES_THUNDER, 0);
        FUN_003fa1e0(self, player, &thunder, PROP_RES_THUNDER);
        FUN_003fa2c0(self, player, &thunder, PROP_RES_THUNDER, 1);
    }
    CLAMP_ATTR(thunder)
    igProperty_GetRecord(player, PROP_KAMINARITEIKO)->value = thunder;
    int dark = beDataBase_GetRecordInt(SHINKA(self), species, PROP_RES_DARK);
    dark += FUN_003a9250(player, PROP_UPCNT)->obj->v[10];
    dark += FUN_003a9250(player, PROP_UPDATA)->obj->v[10];
    if (apply) {
        FUN_003fa120(self, player, &dark, PROP_RES_DARK, 0);
        FUN_003fa1e0(self, player, &dark, PROP_RES_DARK);
        FUN_003fa2c0(self, player, &dark, PROP_RES_DARK, 1);
    }
    CLAMP_ATTR(dark)
    igProperty_GetRecord(player, PROP_YAMITEIKO)->value = dark;

    /* WAZALIST: drop the old technique objects, then add the highest unlocked
     * rank of every technique whose level threshold is reached. */
    {
        igObjectList *list = igProperty_GetRecordFolder(player, PROP_WAZALIST)->list;
        int oldCount = list->_count;
        for (int r = 0; r < oldCount; r++) RELEASE(((igObject **)list->_data)[r]);
        int clearCount = list->_count;
        for (int c = 0; c < clearCount; c++) ((int *)list->_data)[c] = 0;
        list->_count = 0;

        for (int slot = 0; slot < 6; slot++) {
            int tech = beDataBase_GetRecordInt(SHINKA(self), species, DAT_004cf290[slot]);
            int skillNo = beDataBase_GetRecordInt(PCTECH(self), tech, PROP_SKILL);
            int skillVal = FUN_003a9250(player, PROP_SKILL)->obj->v[skillNo];
            if (beDataBase_GetRecordInt(SHINKA(self), species, DAT_004cf2b0[slot]) <= level) {
                for (int rank = 4; rank >= 0; rank--) {
                    if (beDataBase_GetRecordInt(SHINKA(self), species, DAT_004cf2d0[slot][rank]) <= skillVal) {
                        IntListRef waza((IntList *)FUN_003c8040(StatHelpers::select_allocator(igObject_GetAllocator(self))));
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
        FUN_003f9f80(self, player, &delay, PROP_DELAY, 0);
        if (delay > 70) delay = 70;
        igProperty_GetRecord(player, PROP_ATTACKDELAY)->value = delay;
        hitRate = 0;
        FUN_003f9f80(self, player, &hitRate, PROP_MEICHURITSU, 0);
        igProperty_GetRecord(player, PROP_MEICHURITSU)->value = hitRate;
        critRate = 0;
        critRate += FUN_003a9250(player, PROP_UPDATA)->obj->v[1];
        critRate -= FUN_003a9250(player, PROP_DOWNDATA)->obj->v[1];
        FUN_003f9f80(self, player, &critRate, PROP_CHIMEIRITSU, 0);
        FUN_003fa040(self, player, &critRate, PROP_CHIMEIRITSU);
        if (critRate <= 0) critRate = 1;
        igProperty_GetRecord(player, PROP_CHIMEIRITSU)->value = critRate;
        paralysisRate = 0;
        FUN_003f9f80(self, player, &paralysisRate, PROP_MAHIRITSU, 0);
        igProperty_GetRecord(player, PROP_MAHIRITSU)->value = paralysisRate;
        evadeRate = 0;
        evadeRate += FUN_003a9250(player, PROP_UPDATA)->obj->v[3];
        evadeRate -= FUN_003a9250(player, PROP_DOWNDATA)->obj->v[3];
        FUN_003fa1e0(self, player, &evadeRate, PROP_CHOHATURITSU);
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
        FUN_003fa2c0(self, player, &bitRate, PROP_BITRITSU, 0);
        igProperty_GetRecord(player, PROP_BITRITSU)->value = bitRate;
        expRate = 0;
        FUN_003fa2c0(self, player, &expRate, PROP_EXPRITSU, 0);
        igProperty_GetRecord(player, PROP_EXPRITSU)->value = expRate;
        luckRate = 0;
        FUN_003fa2c0(self, player, &luckRate, PROP_LUCKRITSU, 0);
        igProperty_GetRecord(player, PROP_LUCKRITSU)->value = luckRate;

        /* weapon element: index of the first equipped power pocket item whose
         * ZOKUSEI names one of fire/ice/thunder/dark, otherwise -1 */
        { IntRec *zokusei = igProperty_GetRecord(player, PROP_ATTACKZOKUSEI); zokusei->value = -1; }
        found = 0;
        int pocketCount = igProperty_GetRecordFolder(player, PROP_POWERPOCKET)->list->_count;
        for (int p = 0; p < pocketCount; p++) {
            beNDMWItemBase *pocketItem = ((beNDMWItemBase **)igProperty_GetRecordFolder(player, PROP_POWERPOCKET)->list->_data)[p];
            if (pocketItem) {
                const char *zokuseiName = beNDMWItemBase_GetRecordString(pocketItem, self, PROP_ZOKUSEI);
                for (int element = 0; element < 4; element++) {
                    if (igStrCmp(zokuseiName, DAT_004cf350[element]) == 0) {
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
            FUN_003fa040(self, player, &hpDrain, PROP_HPDRAIN);
            igProperty_GetRecord(player, PROP_HPDRAIN)->value = hpDrain;
            mpDrain = 0;
            FUN_003fa040(self, player, &mpDrain, PROP_MPDRAIN);
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
        firstSocket = ((beNDMWItemBase **)igProperty_GetRecordFolder(player, PROP_POWERSOCKET)->list->_data)[0];
        weaponRec = 0;
        weaponSkill = 0;
        if (firstSocket) {
            weaponRec = firstSocket->_recNo;
            weaponSkill = beNDMWItemBase_GetRecordInt(firstSocket, self, PROP_SKILL);
        }
        igProperty_GetRecord(player, PROP_WEAPONRECNO)->value = weaponRec;
        igProperty_GetRecord(player, PROP_WEAPONSKILLNO)->value = weaponSkill;

        /* POWERSOCKETNAME: replace every old name with an empty interned
         * string, then store the MODEL string of each socket item. */
        sockets = igProperty_GetRecordFolder(player, PROP_POWERSOCKET)->list;
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
                StringList_AppendRetained(names, &token.p);
            }
        }
    }
}
