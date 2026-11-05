#include "dw4/reflected.h"
typedef igObject Ref;
struct IntRec { char pad[12]; int value; };
struct BonusObj { char pad[16]; int *v; };
struct BonusRec { char pad[12]; BonusObj *obj; };
extern "C" {
extern char DAT_00518848[], DAT_00518858[], DAT_00518868[], DAT_00518b30[], DAT_00518b60[];
extern char DAT_00518c98[], DAT_00518ca0[], DAT_00518cb0[], DAT_00518cb8[];
extern char DAT_00519420[], DAT_00519430[], DAT_00519438[];
extern int DAT_004cf130[], DAT_004cf160[], DAT_004cf190[], DAT_004cf1c0[];
extern void beMessenger_SendNamed(int, const char *, const char *, int, const char *);
extern Ref *beMessenger_GetObject(int, int);
extern int beDataBase_GetRecordInt(Ref *, int, const char *);
extern IntRec *igProperty_GetRecord(void *, const char *);
extern BonusRec *FUN_003a9250(void *, const char *);
extern void igObject_Destroy(Ref *);
extern int FUN_003fa3b0(beNDMWGameRam *, int, int, int);
}
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
            beMessenger_SendNamed(g->_messenger, DAT_00519438, DAT_00519430, 0, DAT_00519420);
            fetched = beMessenger_GetObject(g->_messenger, 0);
            if (fetched) ++fetched->_refCount;
            release_ref((Ref *)g->_dBShinka);
            g->_dBShinka = (int)fetched;
        }
        return (Ref *)g->_dBShinka;
    }
};
#define SHINKA(g) StatHelpers::shinka(g)
extern "C" int FUN_003fa3b0(beNDMWGameRam *arg0, int arg1, int arg2, int arg3) {
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
        rec = igProperty_GetRecord(player, DAT_00518848)->value;
        tbl = FUN_003a9250(player, DAT_00518868)->obj;
        base = 0;
        lvl = igProperty_GetRecord(player, DAT_00518858)->value;
    } else {
        tbl = FUN_003a9250(player, DAT_00518b60)->obj;
        base = rec * 11;
        lvl = FUN_003a9250(player, DAT_00518b30)->obj->v[rec];
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
