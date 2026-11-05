#include "dw4/reflected.h"
struct IntRec { char pad[12]; int value; };
struct BonusObj { char pad[16]; int *v; };
struct BonusRec { char pad[12]; BonusObj *obj; };
extern "C" {
extern char DAT_00518848[], DAT_00518858[], DAT_00518868[], DAT_00518b30[], DAT_00518b60[];

extern char DAT_00519420[], DAT_00519430[], DAT_00519438[];
extern int DAT_004cf130[], DAT_004cf190[], DAT_004cf1f0[], DAT_004cf220[];
extern const char *DAT_004cf250[], *DAT_004cf270[];
extern void beMessenger_SendNamed(int, const char *, const char *, int, const char *);
extern igObject *beMessenger_GetObject(int, int);
extern int beDataBase_GetRecordInt(igObject *, int, const char *);
extern IntRec *igProperty_GetRecord(void *, const char *);
extern BonusRec *FUN_003a9250(void *, const char *);
extern void igObject_Destroy(igObject *);
extern int FUN_003fa850(beNDMWGameRam *, int, int, int);
}
struct StatHelpers {
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
            beMessenger_SendNamed(g->_messenger, DAT_00519438, DAT_00519430, 0, DAT_00519420);
            fetched = beMessenger_GetObject(g->_messenger, 0);
            if (fetched) ++fetched->_refCount;
            release_ref((igObject *)g->_dBShinka);
            g->_dBShinka = (int)fetched;
        }
        return (igObject *)g->_dBShinka;
    }
};
#define SHINKA(g) StatHelpers::shinka(g)
extern "C" int FUN_003fa850(beNDMWGameRam *arg0, int arg1, int arg2, int arg3) {
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
        rec = igProperty_GetRecord(player, DAT_00518848)->value;
        tbl = FUN_003a9250(player, DAT_00518868)->obj;
        base = 0;
        lvl = igProperty_GetRecord(player, DAT_00518858)->value;
    } else {
        tbl = FUN_003a9250(player, DAT_00518b60)->obj;
        base = rec * 11;
        lvl = FUN_003a9250(player, DAT_00518b30)->obj->v[rec];
    }
    s0 = beDataBase_GetRecordInt(SHINKA(arg0), rec, DAT_004cf250[arg3]);
    mul = beDataBase_GetRecordInt(SHINKA(arg0), rec, DAT_004cf270[arg3]);
    p = tbl->v[base + 2 + arg3];
    i = 0;
    q = DAT_004cf130;
    loop: if (*q < lvl) { q++; i++; goto loop; }
    r = p + (s0 + mul * (DAT_004cf1f0[i] + DAT_004cf220[i] * (lvl - DAT_004cf190[i])) / 100);
    if (r > 9999) r = 9999;
    return r;
}
