#include "dw4/igSmartPointer.h"
extern "C" {
igObject *beBaseInfoDataList_Create(int);
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, char *);
int StringChunk_ReleaseHeader(...);
int FUN_003a7e90(void *, void *);
int FUN_003a6750(void *, void *);
int FUN_003a65f0(void *, void *, void *);
float FUN_003a68d0();
float FUN_003a68e0(int, int, int, float);
int FUN_003a7a20(void *, void *, int);
int __fixsfdi(float);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(void *);
int strcmp(char *, void *);
extern int DAT_004e0858[4];
extern int DAT_0050ef60[4];
extern int DAT_0050ef68[4];
extern int DAT_0050ef70[4];
extern int DAT_0050ef78[4];
extern int DAT_0050ef80[4];
extern int DAT_0050ef88[4];
extern int DAT_00585be0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
class Ctl { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
/* Owning stack reference to the freshly created property list; released on scope exit once the ram
 * holds its own reference. */

/* Owning stack reference to a pooled string token (count at p[-1], chunk header at p[-2]). */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
struct DataListInstall { static inline void go(beBaseInfoRam *ram, const igSmartPointer<igObject> &fresh) {
    igObject *o = fresh.p;
    igObject *old;
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
    old = (igObject *)ram->_dataList;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    ram->_dataList = (int)o;
}
static inline void make(beBaseInfoRam *ram, int v) { igSmartPointer<igObject> fresh(beBaseInfoDataList_Create(v)); go(ram, fresh); }
};
extern "C" beModelCtrlInfoRamData *igProperty_FindByName(igObject *, int, void *);
extern "C" void FUN_00390f80(beModelCtrl *arg0, void *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3, beModelCtrlInfoDataAIM *arg4);
void FUN_00390f80(beModelCtrl *arg0, void *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3, beModelCtrlInfoDataAIM *arg4) {
    float vec[3];
    igObject *o;
    igObject *old;
    beModelCtrlInfoRamData *prop;
    beModelCtrlAIData *seg;
    beModelCtrlInfoAI *cur;
    beModelCtrlAIMap *e;
    beModelCtrlAIDataList *lst;
    beModelCtrlAIData **pp;
    int v;
    int i;
    int cnt;
    int sel;
    char *nm;
    char *nm2;
    char *newv;
    char *oldv;
    float fv;
    if (arg2->_dataList == 0) {
        v = igObject_GetAllocator(arg2);
        v = (GPR_00554c14 != 0) ? v : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        DataListInstall::make(arg2, v);
    }
    prop = igProperty_FindByName((igObject *)arg2->_dataList, DAT_00585be0[0], &DAT_0050ef60[0]);
    cur = (beModelCtrlInfoAI *)arg3->_aI;
    StringRef str(0);
    if (FUN_003a7e90(arg2, &DAT_0050ef68[0]) != 0) {
        e = ((beModelCtrlAIMap **)((beModelCtrlAIMapList *)arg4->_aIMapList)->_data)[cur->_mapNo];
        if ((char *)e->_targetType == 0) {
            if (DAT_00586f20[0] == 0) {
                v = FUN_002eb010(16);
                if (v != 0) {
                    v = StringPool_Construct(v);
                }
                DAT_00586f20[0] = v;
            }
            newv = (char *)StringPool_Intern(DAT_00586f20[0], (char *)&DAT_0050ef70[0]);
            oldv = (char *)e->_targetType;
            if (oldv != 0) {
                int *a1 = (int *)oldv - 2;
                int v0 = ((int *)oldv)[-1] - 1;
                ((int *)oldv)[-1] = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
            e->_targetType = (int)newv;
        }
        if (strcmp((char *)e->_targetType, &DAT_0050ef78[0]) == 0) {
            beModelCtrlInfoAI *c2 = (beModelCtrlInfoAI *)arg3->_aI;
            vec[0] = ((float *)c2->_worldPos)[0];
            vec[1] = ((float *)c2->_worldPos)[1];
            vec[2] = ((float *)c2->_worldPos)[2];
            if ((FUN_003a6750((char *)prop->_node + 32, vec) & 0xff) == 0) {
                return;
            }
        } else {
            if ((FUN_003a65f0((char *)prop->_node + 32, &DAT_0050ef80[0], (char *)e->_targetType) & 0xff) == 0) {
                return;
            }
        }
        fv = FUN_003a68d0();
        ((float *)arg3->_directionLimiter)[1] = e->_rotLimiter;
        if (!(e->_x1Square <= fv)) {
            lst = (beModelCtrlAIDataList *)e->_zoneA;
        } else if (!(e->_x2Square <= fv)) {
            lst = (beModelCtrlAIDataList *)e->_zoneB;
        } else if (!(e->_x3Square <= fv)) {
            lst = (beModelCtrlAIDataList *)e->_zoneC;
        } else {
            lst = (beModelCtrlAIDataList *)e->_zoneD;
        }
        sel = ((Ctl *)((beSystem *)arg0->_system)->_random)->vX() & 0xf;
        cnt = lst->_count;
        i = 0;
        if (i < cnt) {
            pp = (beModelCtrlAIData **)lst->_data;
            do {
                seg = *pp;
                if (sel < seg->_limit) break;
                pp = pp + 1;
            } while (++i < cnt);
        }
        ((float *)arg3->_targetDirection)[1] = FUN_003a68e0(cnt, i, sel, seg->_dirRadian);
        nm2 = (char *)seg->_name;
        if (nm2 != 0) {
            nm = nm2;
        } else {
            nm = (char *)&DAT_004e0858[0];
        }
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(16);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        newv = (char *)StringPool_Intern(DAT_00586f20[0], nm);
        oldv = str.p;
        if (oldv != 0) {
            int *a1 = (int *)oldv - 2;
            int v0 = ((int *)oldv)[-1] - 1;
            ((int *)oldv)[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        str.p = newv;
        fv = seg->_time; fv = fv; FUN_003a7a20(arg2, &DAT_0050ef68[0], __fixsfdi((1e9f * fv) / 60.0f));
    } else {
        nm = (char *)cur->_seqName;
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(16);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        newv = (char *)StringPool_Intern(DAT_00586f20[0], nm);
        oldv = str.p;
        if (oldv != 0) {
            int *a1 = (int *)oldv - 2;
            int v0 = ((int *)oldv)[-1] - 1;
            ((int *)oldv)[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        str.p = newv;
    }
    arg3->_keyInput = strcmp(str.p, &DAT_0050ef88[0]) == 0;
    nm = str.p;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    newv = (char *)StringPool_Intern(DAT_00586f20[0], nm);
    oldv = (char *)arg3->_keyEventName;
    if (oldv != 0) {
        int *a1 = (int *)oldv - 2;
        int v0 = ((int *)oldv)[-1] - 1;
        ((int *)oldv)[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg3->_keyEventName = (int)newv;
    nm = str.p;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    newv = (char *)StringPool_Intern(DAT_00586f20[0], nm);
    oldv = (char *)cur->_seqName;
    if (oldv != 0) {
        int *a1 = (int *)oldv - 2;
        int v0 = ((int *)oldv)[-1] - 1;
        ((int *)oldv)[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    cur->_seqName = (int)newv;
}
