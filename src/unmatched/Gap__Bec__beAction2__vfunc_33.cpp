#include "dw4/reflected.h"
extern "C" {
int FUN_0036dcd0();
unsigned int beMessenger_ResolveEnumValue(int, int, void *);
int beMessenger_AppendBool(int, int);
int beMessenger_AppendObject(int, int);
int beMessenger_AppendMatrix(int, int);
int beMessenger_AppendString(int, void *);
int beMessenger_GetString(int, int);
int FUN_003a84a0(void *, float);
long long __fixsfdi(float);
int strcmp(void *, void *);
void igObject_Destroy(void *);
int List_Reserve(void *, int, int);
int FUN_003a8760(void *);
int FUN_001adf70(int);
void *igMetaObject_FindFieldByName(int, void *);
void Memory_FreeBuffer(int);
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorBySelector(int);
void *FUN_0036c2a0(void *);
int FUN_00239070(void *, void *);
int FUN_001ae750(void *, int, int, int, int);
void *igProperty_FindByName(int, int, void *);
int beAction2_StartComponents(void *, void *);
int beMessenger_SendNamed(int, void *, void *, int, void *);
extern int DAT_004e0858[4];
extern int DAT_0050dfe8[4];
extern int DAT_0050dff0[4];
extern int DAT_0050e010[4];
extern int DAT_0050e030[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
int Gap__Bec__beAction2__vfunc_33(beAction2 *arg0, beAction2InfoRam *arg1, void *arg2);
}

/* Owning reference held in the frame; its release is inlined at each return. */
struct Rc { int w0; int references; };
struct RP { Rc *p; inline ~RP(); };
#define REL(o) { Rc *rr = (o); if (rr != 0) { rr->references = rr->references - 1; if (((unsigned long long)((long long)rr->references << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
inline RP::~RP() { Rc *rr = p; if (rr != 0) { rr->references = rr->references - 1; if ((rr->references & 0x7FFFFF) == 0) { igObject_Destroy(rr); } } }

/* matching construct: dummy virtual slots so the calls dispatch through the retail vtable offsets */
struct V {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19();
    virtual int v22();
    virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26();
    virtual int v27(int);
    virtual int v28(int);
};

/* the object lists hold 4-byte arena handles: _data is a memory ref */
#define LDATA(l) ((int *)(l)->_data)

#define BITCLR(n) { unsigned int w = (n) >> 5; int bit = 1 << ((n) & 0x1F); int *pw = LDATA(sw) + w; int cnt = sw->_count; int cur = *pw; int nv = ~bit & cur; if (cnt != 0 && (int)w >= 0 && (int)w < cnt) { *pw = nv; } }
#define BITSET(n) { unsigned int w = (n) >> 5; int bit = 1 << ((n) & 0x1F); int *pw = LDATA(sw) + w; int cnt = sw->_count; int cur = *pw; int nv = bit | cur; if (cnt != 0 && (int)w >= 0 && (int)w < cnt) { *pw = nv; } }

int Gap__Bec__beAction2__vfunc_33(beAction2 *arg0, beAction2InfoRam *arg1, void *arg2)
{
    RP spBC;
    beAction2Info *info;
    unsigned int ramNo;
    igBitMask *sw;
    beAction2InfoWork *w;

    spBC.p = (Rc *)arg1->_work;
    if (spBC.p != 0) {
        spBC.p->references = spBC.p->references + 1;
    }
    info = (beAction2Info *)arg1->_parentInfo;
    ramNo = arg1->_ramNo;
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_0036dcd0(), arg2)) {
    case 1:
        { int r = arg1->_isRun; int m = *(volatile int *)&arg0->_messenger; beMessenger_AppendBool(m, r); }
        break;
    case 0: {
        beAction2InfoWork *ww = (beAction2InfoWork *)spBC.p;
        beAction2Data *cd = (beAction2Data *)ww->_comData;
        int ci = ww->_comIndex;
        if (ww->_waitSt0 == 0 && ci == ((igObjectList *)cd->_comList)->_count) {
            beMessenger_AppendBool(arg0->_messenger, 1);
        } else {
            beMessenger_AppendBool(arg0->_messenger, 0);
        }
        break;
    }
    case 3:
        if (arg1->_isRun != 0) {
            beMessenger_AppendObject(arg0->_messenger, arg1->_appearanceList);
            beMessenger_AppendObject(arg0->_messenger, LDATA((igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_skeletonList)[0]);
        }
        break;
    case 4:
        if (arg1->_isRun != 0) {
            int nm = beMessenger_GetString(arg0->_messenger, 0);
            igActor *a = (igActor *)LDATA((igObjectList *)arg1->_actorList)[0];
            int idx = ((V *)((int *)a->_animationSystem)[3])->v27(nm);
            int m;
            if (a->_actorCacheUsed != 0) {
                m = a->_boneMatrixCacheArray + (idx << 6);
            } else {
                m = ((V *)a->_animationSystem)->v28(idx);
            }
            beMessenger_AppendMatrix(arg0->_messenger, m);
        }
        break;
    case 2: {
        igObjectList *l = (igObjectList *)info->_dataList_;
        int n = l->_count;
        int i;
        for (i = 0; i < n; i++) {
            void *nm = (void *)((int *)LDATA(l)[i])[2];
            void *nm2;
            if (nm != 0) nm2 = nm; else nm2 = &DAT_004e0858[0];
            beMessenger_AppendString(arg0->_messenger, nm2);
        }
        break;
    }
    case 5:
        if (spBC.p != 0) {
            beModelCtrlNode2 *nd;
            float f20;
            int tt;
            float k = 0.0f;
            FUN_003a84a0(arg1, k);
            tt = (int)(((igInsightCore *)arg0->_insight)->_worldTime >> 0x12);
            nd = (beModelCtrlNode2 *)arg1->_node;
            f20 = (float)(unsigned int)tt;
            { long long r = __fixsfdi(f20 * nd->_timeScale); long long o = *(volatile long long *)&nd->_timeBias; nd->_timeBias = (r << 0x12) + o; }
            nd->_timeBias = nd->_timeBias - (__fixsfdi(f20 * k) << 0x12);
            nd->_timeScale = k;
            ((beAction2InfoWork *)spBC.p)->_isFreeze = 1;
        }
        break;
    case 6:
        if (spBC.p != 0) {
            beModelCtrlNode2 *nd;
            float f20;
            int tt;
            float k = 1.0f;
            FUN_003a84a0(arg1, k);
            tt = (int)(((igInsightCore *)arg0->_insight)->_worldTime >> 0x12);
            nd = (beModelCtrlNode2 *)arg1->_node;
            f20 = (float)(unsigned int)tt;
            { long long r = __fixsfdi(f20 * nd->_timeScale); float a2 = f20 * k; float a3 = a2; long long o = *(volatile long long *)&nd->_timeBias; nd->_timeBias = (r << 0x12) + o; nd->_timeBias = nd->_timeBias - (__fixsfdi(a3) << 0x12); }
            nd->_timeScale = k;
            ((beAction2InfoWork *)spBC.p)->_isFreeze = 0;
        }
        break;
    default:
        sw = (igBitMask *)((int *)info->_switch)[8];
        if (strcmp(arg2, &DAT_0050dfe8[0]) == 0) {
            igObjectList *l = (igObjectList *)((beModelCtrlNode2 *)arg1->_node)->_overrideAttrList;
            int n = l->_count;
            int i;
            int n2;
            int j;
            for (i = 0; i < n; i++) {
                Rc *o = (Rc *)LDATA(l)[i];
                REL(o)
            }
            j = 0;
            n2 = l->_count;
            for (; j < n2; j++) {
                LDATA(l)[j] = 0;
            }
            l->_count = 0;
            int pos = ((igObjectList *)((beModelCtrlNode2 *)arg1->_node)->_overrideAttrList)->_count > 0;
            if (!pos) {
                List_Reserve((void *)((beModelCtrlNode2 *)arg1->_node)->_overrideAttrList, 0, 4);
            }
            BITCLR(ramNo)
            { Rc *o = (Rc *)arg1->_work; REL(o) }
            arg1->_work = 0;
            FUN_003a8760(arg1);
            arg1->_isRun = 0;
            if (info->_animationDatabase != 0) {
                igObjectList *dl = (igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_combinerList;
                int an;
                int k;
                igMetaField *fl;
                igMetaField *fl2;
                V *ac;
                int pv;
                int pv2;
                if (dl != 0) {
                    FUN_001adf70(LDATA(dl)[arg1->_ramNo]);
                }
                an = ((igObjectList *)arg1->_actorList)->_count;
                for (k = 0; k < an; k++) {
                    ac = (V *)LDATA((igObjectList *)arg1->_actorList)[k];
                    fl = (igMetaField *)igMetaObject_FindFieldByName(ac->v22(), &DAT_0050dff0[0]);
                    pv = *(int *)((char *)ac + fl->_offset);
                    if (pv != 0) {
                        Memory_FreeBuffer(pv);
                        *(int *)((char *)ac + fl->_offset) = 0;
                    }
                    fl2 = (igMetaField *)igMetaObject_FindFieldByName(ac->v22(), &DAT_0050e010[0]);
                    pv2 = *(int *)((char *)ac + fl2->_offset);
                    if (pv2 != 0) {
                        Memory_FreeBuffer(pv2);
                        *(int *)((char *)ac + fl2->_offset) = 0;
                    }
                }
            }
            return 1;
        }
        if (spBC.p == 0) {
            void *alloc = igObject_GetAllocator(arg0);
            Rc *t;
            alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            { Rc *o = spBC.p; REL(o) }
            spBC.p = (Rc *)FUN_0036c2a0(alloc);
            t = spBC.p;
            if (t != 0) t->references = t->references + 1;
            { Rc *o = (Rc *)arg1->_work; REL(o) }
            arg1->_work = (int)t;
        }
        if (arg1->_isRun == 0) {
            beAction2InfoWork *ww;
            arg1->_isRun = 1;
            ww = (beAction2InfoWork *)spBC.p; ww->_motionSt0 = 0;
            ww = (beAction2InfoWork *)spBC.p; ww->_fadeSt0 = 0;
            ww = (beAction2InfoWork *)spBC.p; ww->_waitSt0 = 0;
            BITSET(ramNo)
            ((beAction2InfoWork *)spBC.p)->_isNoHokan = 1;
            if (info->_animationDatabase != 0) {
                igObjectList *dl = (igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_combinerList;
                if (dl != 0) {
                    igAnimationCombiner *s5 = (igAnimationCombiner *)LDATA(dl)[arg1->_ramNo];
                    int an;
                    int k;
                    s5->_animationStateTime = 0x05F5E100;
                    an = ((igObjectList *)arg1->_actorList)->_count;
                    for (k = 0; k < an; k++) {
                        igActor *ac = (igActor *)LDATA((igObjectList *)arg1->_actorList)[k];
                        int nz = ac->_boneMatrixCacheArray != 0;
                        if (nz) break;
                        FUN_00239070(ac, s5);
                    }
                    FUN_001ae750(s5, LDATA((igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_animationList)[0], 0, 4, 0);
                }
            }
        } else {
            BITSET(ramNo)
            ((beAction2InfoWork *)spBC.p)->_isNoHokan = 0;
        }
        {
            int prop = (int)igProperty_FindByName(info->_dataList_, DAT_00585be0[0], arg2);
            beAction2InfoWork *cur = (beAction2InfoWork *)spBC.p;
            if (cur->_comData != prop) {
                if (prop != 0) ((Rc *)prop)->references = ((Rc *)prop)->references + 1;
                { Rc *o = (Rc *)cur->_comData; REL(o) }
                cur->_comData = prop;
                ((beAction2InfoWork *)spBC.p)->_comIndex = 0;
                beAction2_StartComponents(arg0, arg1);
                int rn = arg1->_ramNo;
                void *pn;
                if (info->_name != 0) pn = (void *)info->_name; else pn = &DAT_004e0858[0];
                beMessenger_SendNamed(arg0->_messenger, &DAT_0050e030[0], pn, rn, arg2);
            }
        }
        break;
    }
    return 1;
}
