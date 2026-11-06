/* `apply` is tested as `apply & 0xff`, so it is an int here. The apply branch declares `bit`, the
 * SKILL table, the name list, the two item reads and the socket list at the top of the block in
 * that order (stack slots follow declaration order); the socket-0 store is guarded by `sc != 0 &&
 * zero < sc` so the compare is a slt, not a blez; `count2` is declared before `k`. With apply != 0
 * the chosen item must fit the species (1 << DIGIMONNO against the item's species mask). */
#include "dw4/reflected.h"

#define PROP_DIGIMONNO       DAT_00518848
#define PROP_SKILL           DAT_00518860
#define PROP_TSUYOSA         DAT_005188b0
#define PROP_POWERPOCKET     DAT_00518a40
#define PROP_POWERSOCKET     DAT_00518a88
#define PROP_POWERSOCKETNAME DAT_00518aa0
#define PROP_MODEL           DAT_00518c08
#define PROP_SPECIES_MASK    DAT_00518c10
#define PROP_NEEDSKILL       DAT_00518c18

extern "C" {
extern char DAT_00518848[], DAT_00518860[], DAT_005188b0[], DAT_00518a40[], DAT_00518a88[], DAT_00518aa0[];
extern char DAT_00518c08[], DAT_00518c10[], DAT_00518c18[];
}

struct IntRec { char pad[12]; int value; };
struct BonusRec { char pad[12]; igIntList *obj; };
struct ListHolder { char pad[12]; igObjectList *list; };
struct StrListHolder { char pad[12]; igStringRefList *list; };

extern "C" {
extern IntRec *igProperty_GetRecord(void *, const char *);
extern ListHolder *igProperty_GetRecordFolder(void *, const char *);
extern BonusRec *FUN_003a9250(void *, const char *);
extern StrListHolder *FUN_003a9310(void *, const char *);
extern void ObjectList_AppendRetained(igObjectList *, beNDMWItemBase *);
extern void ObjectList_FillRetained(igObjectList *, int, int);
extern void igObject_Destroy(void *);
extern int FUN_002eb010(int);
extern int StringPool_Construct(int);
extern char *StringPool_Intern(int, const char *);
extern void StringChunk_ReleaseHeader(int, int *);
extern int beNDMWItemBase_GetRecordInt(beNDMWItemBase *, beNDMWGameRam *, const char *);
extern const char *beNDMWItemBase_GetRecordString(beNDMWItemBase *, beNDMWGameRam *, const char *);
extern int DAT_00586f20[4];
}

/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
/* The list takes its own reference to the token it is handed. */
extern "C" void StringList_AppendRetained(igStringRefList *, const StringRef &);

extern "C" void FUN_003f8c90(beNDMWGameRam *self, int index, int apply)
{
    void *player = ((void **)((igObjectList *)self->_playerDataListList)->_data)[index];
    igObjectList *pocket = igProperty_GetRecordFolder(player, PROP_POWERPOCKET)->list;

    if ((apply & 0xff) == 0) {
        igObjectList *sockets = igProperty_GetRecordFolder(player, PROP_POWERSOCKET)->list;
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
                StringList_AppendRetained(names, StringRef(interned));
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
        skills = FUN_003a9250(player, PROP_SKILL)->obj;
        sockets = igProperty_GetRecordFolder(player, PROP_POWERSOCKET)->list;
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
            StringList_AppendRetained(names, StringRef(interned));
            chosen->_isEquip = 1;
        }
    }
}
