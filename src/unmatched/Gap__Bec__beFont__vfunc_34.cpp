#include "dw4/reflected.h"

class VObj;
extern "C" {
int FUN_00361df0();
int FUN_00361d30();
int FUN_00361d90();
int beMessenger_ResolveEnumValue(int, int, int);
void beMessenger_SelectGroup(int, void *);
void beMessenger_AppendString(int, void *);
void beMessenger_DispatchSelected(int, void *);
int beMessenger_GetBoolCount(int);
int beMessenger_GetStringCount(int);
int beMessenger_GetIntCount(int);
int beMessenger_GetObjectCount(int);
int beMessenger_GetInt(int, int);
void *beMessenger_GetObject(int, int);
int beMessenger_GetString(int, int);
void beMessenger_GetVec3(void *, int, int);
int FUN_00383350(void *, const char *);
void ObjectList_AppendRetainedList(void *, void *);
void ObjectList_AppendRetained(void *, void *);
int igObject_IsKindOf(void *, int);
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorBySelector(int);
void *FUN_003624f0(void *);
void *FUN_00137810(void *);
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, const char *);
void StringChunk_ReleaseHeader(int, void *);
void igObject_Destroy(void *);
void FUN_0030b3c0(void *, void *);
int FUN_003840a0(void *, void *, int, int);
int FUN_003841d0(void *, void *);
void FUN_00383420(void *, void *, void *, int);
void FUN_001dc820(void *, int);
void FUN_001dc880(void *, int);
void FUN_00193540(void *, int, int);
void Matrix44_SetTranslation(void *, void *);
unsigned int Memory_GetBufferSize(void *);
extern int DAT_004e0858[4];
extern int DAT_0050e730[4];
extern int DAT_0050e740[4];
extern int DAT_0050e748[4];
extern int DAT_0050e758[4];
extern int DAT_0055f2e0[4];
extern int DAT_005619f8[4];
extern int DAT_00562078[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_00589640[4];
extern unsigned char GPR_00554c14;
}

class N;
/* element array of an igObjectList (_data is a 4-byte arena handle) */
#define LD(l) ((N **)(l)->_data)
class F {
public:
    virtual int v00(); virtual int v01(); virtual int v02(); virtual int v03();
    virtual int v04(); virtual int v05(); virtual int v06(); virtual int v07();
    virtual int v08(); virtual int v09(); virtual int v10(); virtual int v11();
    virtual int v12(); virtual int v13(); virtual int v14(); virtual int v15();
    virtual int v16(); virtual int v17(); virtual int v18(); virtual int v19();
    virtual int v20(); virtual int v21(); virtual int v22(); virtual int Q(int);
};
class N {
public:
    virtual int v00(); virtual int v01(); virtual int v02(); virtual int v03();
    virtual int v04(); virtual int v05(); virtual int v06(); virtual int v07();
    virtual int v08(); virtual int v09(); virtual int v10(); virtual int v11();
    virtual int v12(); virtual int v13(); virtual int v14(); virtual int v15();
    virtual int v16(); virtual int v17(); virtual int v18(); virtual int v19();
    virtual int Meta(); virtual int v21(); virtual int v22(); virtual int v23();
    virtual int v24(); virtual int v25(); virtual int v26(); virtual int v27();
    virtual int v28(); virtual int v29(); virtual int Apply(void *);
    unsigned int ref; int f8; int f12; igObjectList *f16; int f20; int f24; igObjectList *f28; igObjectList *f32; int f36;
};
struct Vec { float x; float y; float z; float w; };
/* Scope holder whose destructor releases the reference. Retail keeps one out-of-line destructor per holder
 * (kind 0..3 = 0x382d70, 0x1353b0, 0x1363f0, 0x1489a0), which is why the holder is a template on the kind. */
template <int kind> struct RP {
    N *p;
    RP(N *x) { p = x; }
    ~RP() { N *o = p; if (o != 0) { o->ref = o->ref - 1; if ((o->ref & 0x7FFFFF) == 0) igObject_Destroy(o); } }
};

#define RETAIN(p) if (p) (p)->ref = (p)->ref + 1;
#define REL(p) if (p) { (p)->ref = (p)->ref - 1; if (((p)->ref & 0x7FFFFF) == 0) igObject_Destroy(p); }
#define RELH(h) { N *r_ = (h).p; REL(r_) }
#define FAIL(m) { (m)->f24 = 10000; (m)->f36 = 0; (m)->f32 = 0; (m)->f28 = 0; { ret = 1; goto end; } }
struct H { static int cnt(igObjectList *l) { if (l != 0) return l->_count; return 0; }
  static N *castit(N *s) { if (s != 0 && igObject_IsKindOf(s, DAT_00562078[0]) != 0) return s; else return 0; } };
#define CNT(l) H::cnt(l)
#define SETSTR(o, fld, srcnm) { const char *nm_ = (srcnm) ? (const char *)(srcnm) : (const char *)DAT_004e0858; int nw_; mem = (o); int old_; int *hd_; int rf_; if (DAT_00586f20[0] == 0) { int pl_ = FUN_002eb010(16); if (pl_) pl_ = StringPool_Construct(pl_); DAT_00586f20[0] = pl_; } nw_ = StringPool_Intern(DAT_00586f20[0], nm_); old_ = mem->fld; if (old_) { hd_ = (int *)(old_ - 8); rf_ = *(int *)(old_ - 4) - 1; *(int *)(old_ - 4) = rf_; if (rf_ == 0) StringChunk_ReleaseHeader(*hd_, hd_); } mem->fld = nw_; }

extern "C" int Gap__Bec__beFont__vfunc_34(beFont *arg0, N *arg1, N *arg2) {
    N *ent;
    int t;
    N *o;
    N *grp;
    N *mem;
    int cc;
    igObjectList *lst;
    int i;
    int j;
    N *e1;
    N *e2;
    N *e3;
    int idx;
    int s1v;
    int s0v;
    int flag;
    unsigned int n;
    int st;
    int ret;
    int nc;
    int li;

    if (((beFontImageList *)arg0->_fonts)->_count <= 0) { ret = 1; goto end; }
    ent = (N *)arg1->f12;
    t = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_00361df0(), arg2->f20);
    st = arg1->f24;
    switch (st) {
    case 0:
        switch (t) { case 0:
        {
        if (((beFontImageList *)arg0->_fonts)->_count <= 0) FAIL(arg1)
        beMessenger_SelectGroup(arg0->_messenger, DAT_0050e730);
        beMessenger_AppendString(arg0->_messenger, DAT_0050e740);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_0050e748);
        if (beMessenger_GetBoolCount(arg0->_messenger) <= 0) FAIL(arg1)
        o = (N *)beMessenger_GetObject(arg0->_messenger, 0);
        if (DAT_005619f8[0] != o->Meta()) FAIL(arg1)
        lst = o->f28;
        cc = 0;
        if (lst != 0) cc = lst->_count;
        if (cc <= 0) FAIL(arg1)
        mem = LD(lst)[0];
        if (DAT_00562078[0] != mem->Meta()) FAIL(arg1)
        RETAIN(mem)
        {
            N *old = (N *)arg0->_root;
            REL(old)
        }
        arg0->_root = (int)mem;
        grp = LD(((N *)arg0->_root)->f28)[0];
        i = 0;
        goto otest;
        do {
            e1 = LD((igObjectList *)li)[i];
            e2 = LD(e1->f28)[0];
            ObjectList_AppendRetainedList(e1->f32, (void *)((beFontImage *)((int *)((beFontImageList *)arg0->_fonts)->_data)[FUN_00383350(arg0, e2->f8 ? (const char *)e2->f8 : (const char *)DAT_004e0858)])->_attrList);
            j = 0;
            while (j < CNT(e2->f28)) {
                e3 = H::castit(LD(e2->f28)[j]);
                {
                    void *ga = igObject_GetAllocator(arg0);
                    void *al;
                    if (GPR_00554c14 != 0) al = ga; else al = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    RP<0> po((N *)FUN_003624f0(al));
                    SETSTR(po.p, f8, e1->f8)
                    SETSTR(po.p, f12, e3->f8)
                    ga = igObject_GetAllocator(arg0);
                    if (GPR_00554c14 != 0) al = ga; else al = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    RP<1> pq((N *)FUN_00137810(al));
                    ObjectList_AppendRetained(po.p->f16, pq.p);
                    ObjectList_AppendRetained((void *)arg0->_gaPairList, po.p);
                }
                j++;
            }
            i++;
        otest:
            lst = grp->f28;
            if (lst != 0) nc = lst->_count; else nc = 0;
            li = (int)lst;
        } while (i < nc);
        arg1->f24 = arg1->f24 + 1;
        arg1->f36 = 0;
        arg1->f32 = 0;
        arg1->f28 = 0;
        { ret = 1; goto end; }
        }
        }
        goto zero;
    }
    ret = 1;
    switch (st) {
    case 1:
        switch (t) {
        case 1: {
            int s1 = beMessenger_GetString(arg0->_messenger, 0);
            int s0 = beMessenger_GetString(arg0->_messenger, 1);
            RP<2> ra(0);
            RETAIN(ra.p)
            RP<3> rb((N *)((beSystem *)arg0->_system)->_globalStrObj);
            RETAIN(rb.p)
            if (beMessenger_GetStringCount(arg0->_messenger) > 2) {
                N *x;
                if (beMessenger_GetString(arg0->_messenger, 2) != 0) { N *rq = rb.p; FUN_0030b3c0(rq, (void *)beMessenger_GetString(arg0->_messenger, 2)); }
                else FUN_0030b3c0(rb.p, DAT_0050e758);
                x = rb.p;
                RETAIN(x)
                RELH(ra)
                ra.p = x;
            } else if (beMessenger_GetIntCount(arg0->_messenger) > 0) {
                int k = beMessenger_GetInt(arg0->_messenger, 0);
                igObjectList *l = ent->f28;
                if (l != 0 && k < l->_count) {
                    N *x = LD(l)[k];
                    RETAIN(x)
                    RELH(ra)
                    ra.p = x;
                }
            } else if (beMessenger_GetObjectCount(arg0->_messenger) > 0) {
                N *x = (N *)beMessenger_GetObject(arg0->_messenger, 0);
                x->Meta();
                if (DAT_00589640[0] == x->Meta()) {
                    RETAIN(x)
                    RELH(ra)
                    ra.p = x;
                } else {
                    N *y;
                    FUN_0030b3c0(rb.p, DAT_0050e758);
                    y = rb.p;
                    RETAIN(y)
                    RELH(ra)
                    ra.p = y;
                }
            }
            if (ra.p != 0) {
                idx = FUN_003840a0(arg0, arg1, s1, s0);
                if (idx != -1) {
                    do {
                        FUN_00383420(arg0, arg1, ra.p, idx);
                        idx = FUN_003841d0(arg0, arg1);
                    } while (idx != -1);
                }
            }
            return 1;
        }
        case 2: {
            int s2 = beMessenger_GetString(arg0->_messenger, 0);
            int s1 = beMessenger_GetString(arg0->_messenger, 1);
            int s0 = beMessenger_GetString(arg0->_messenger, 2);
            s0 = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_00361d30(), s0);
            idx = FUN_003840a0(arg0, arg1, s2, s1);
            if (idx != -1) {
                do {
                    LD((igObjectList *)ent->f20)[idx]->f36 = s0;
                    idx = FUN_003841d0(arg0, arg1);
                } while (idx != -1);
            }
            { ret = 1; goto end; }
        }
        case 3: {
            int s2 = beMessenger_GetString(arg0->_messenger, 0);
            int s1 = beMessenger_GetString(arg0->_messenger, 1);
            igObjectList *l3;
            N *g;
            N *g2;
            igBitMask *bm;
            int k;
            if (beMessenger_GetStringCount(arg0->_messenger) > 2) {
                n = beMessenger_GetString(arg0->_messenger, 2);
                switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_00361d90(), n)) {
                case 1:
                    flag = 1;
                    break;
                case 0:
                    flag = 0;
                    break;
                }
            } else if (beMessenger_GetIntCount(arg0->_messenger) > 0) {
                flag = beMessenger_GetInt(arg0->_messenger, 0);
            }
            l3 = (igObjectList *)ent->f20;
            idx = FUN_003840a0(arg0, arg1, s2, s1);
            if (idx != -1) {
                do {
                    N *el = LD(l3)[idx];
                    int a20 = el->f20;
                    int a24 = el->f24;
                    N *s6 = LD(((N *)arg0->_root)->f28)[0];
                    if (flag != 0) FUN_001dc820(s6, a20);
                    {
                        N *c = LD(LD(s6->f28)[a20]->f28)[0];
                        if (flag != 0) FUN_001dc820(c, a24); else FUN_001dc880(c, a24);
                    }
                    idx = FUN_003841d0(arg0, arg1);
                } while (idx != -1);
            }
            k = 0;
            g = LD(((N *)arg0->_root)->f28)[0];
            bm = (igBitMask *)g->f32;
            while (k < CNT(g->f28)) {
                igBitMask *bits2 = (igBitMask *)LD((LD(g->f28)[k])->f28)[0]->f32;
                if ((1 << (k & 31)) & ((int *)bm->_data)[(unsigned int)k >> 5]) {
                    unsigned char any = 0;
                    unsigned int q;
                    n = bits2->_bitCount;
                    for (q = 0; q < n; q++) {
                        if ((1 << (q & 31)) & ((int *)bits2->_data)[q >> 5]) any = 1;
                    }
                    if (!any) FUN_001dc880(g, k);
                } else {
                    unsigned char any = 0;
                    unsigned int q;
                    n = bits2->_bitCount;
                    for (q = 0; q < n; q++) {
                        if ((1 << (q & 31)) & ((int *)bits2->_data)[q >> 5]) any = 1;
                    }
                    if (any) FUN_001dc820(g, k);
                }
                k++;
            }
            { ret = 1; goto end; }
        }
        case 4: {
            int s1 = beMessenger_GetString(arg0->_messenger, 0);
            int s0 = beMessenger_GetString(arg0->_messenger, 1);
            Vec v;
            beMessenger_GetVec3(&v, arg0->_messenger, 0);
            idx = FUN_003840a0(arg0, arg1, s1, s0);
            if (idx != -1) {
                do {
                    Matrix44_SetTranslation((char *)LD(((N *)(LD((igObjectList *)ent->f20)[idx]->f16))->f28)[0] + 32, &v);
                    idx = FUN_003841d0(arg0, arg1);
                } while (idx != -1);
            }
            { ret = 1; goto end; }
        }
        case 5:
        case 6:
        case 7: {
            int s2 = beMessenger_GetString(arg0->_messenger, 0);
            int s0 = beMessenger_GetString(arg0->_messenger, 1);
            float f22;
            float f21;
            float f20;
            Vec vv;
            if (t == 6) {
                f20 = f21 = f22 = 0.9f;
            } else if (t == 7) {
                f20 = f21 = f22 = 0.5f;
            } else {
                beMessenger_GetVec3(&vv, arg0->_messenger, 0);
                f22 = vv.x;
                f21 = vv.y;
                f20 = vv.z;
            }
            idx = FUN_003840a0(arg0, arg1, s2, s0);
            if (idx != -1) {
                do {
                    int q;
                    N *w;
                    igObjectList *ll = ((N *)(LD((igObjectList *)ent->f20)[idx]->f16))->f32;
                    q = 0;
                    if (0 < ll->_count) {
                        do {
                        w = LD(ll)[q];
                        if (DAT_0055f2e0[0] == w->Meta()) {
                            Vec cc;
                            FUN_00193540(&cc, 1, (int)w->f28);
                            cc.x = f22;
                            cc.y = f21;
                            cc.z = f20;
                            w->Apply(&cc);
                        }
                        q++;
                        } while (q < ll->_count);
                    }
                    idx = FUN_003841d0(arg0, arg1);
                } while (idx != -1);
            }
            { ret = 1; goto end; }
        }
        case 8: {
            if (beMessenger_GetObjectCount(arg0->_messenger) <= 0) { ret = 1; goto end; }
            if (beMessenger_GetIntCount(arg0->_messenger) <= 0) { ret = 1; goto end; }
            {
                N *ob = (N *)beMessenger_GetObject(arg0->_messenger, 0);
                int v = beMessenger_GetInt(arg0->_messenger, 0);
                F *fnt = (F *)LD((beFontImageList *)arg0->_fonts)[0];
                unsigned short *p = (unsigned short *)ob->f12;
                unsigned int cnt = Memory_GetBufferSize(p) >> 1;
                int q;
                for (q = 0; q < (int)cnt; q++, p++) {
                    unsigned short ch = *p;
                    if (ch == 0) break;
                    if (!(0 < fnt->Q(ch))) *p = v;
                }
            }
            { ret = 1; goto end; }
        }
        default:
            goto zero;
        }
    }
    goto end;
zero:
    ret = 0;
end:
    return ret;
}
