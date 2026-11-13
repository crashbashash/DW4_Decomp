#include "dw4/reflected.h"
#define LD(l) ((N **)(l)->_data)
#define RETAIN(p) if (p) (p)->ref = (p)->ref + 1;
#define REL(p) if (p) { (p)->ref = (p)->ref - 1; if (((p)->ref & 0x7FFFFF) == 0) igObject_Destroy(p); }
#define RELH(h) { N *r_ = (h).p; REL(r_) }
#define FAIL(m) { (m)->f24 = 10000; (m)->f36 = 0; (m)->f32 = 0; (m)->f28 = 0; { ret = 1; goto end; } }
#define CNT(l) H::cnt(l)
#define SETSTR(o, fld, srcnm) { const char *nm_ = (srcnm) ? (const char *)(srcnm) : (const char *)emptyString; int nw_; mem = (o); int old_; int *hd_; int rf_; if (g_stringPool[0] == 0) { int pl_ = FUN_002eb010(16); if (pl_) pl_ = StringPool_Construct(pl_); g_stringPool[0] = pl_; } nw_ = StringPool_Intern(g_stringPool[0], nm_); old_ = mem->fld; if (old_) { hd_ = (int *)(old_ - 8); rf_ = *(int *)(old_ - 4) - 1; *(int *)(old_ - 4) = rf_; if (rf_ == 0) StringChunk_ReleaseHeader(*hd_, hd_); } mem->fld = nw_; }
#include "dw4/igSmartPointer.h"

extern "C" void Gap__Core__igObject__vfunc_23(void);
extern "C" int beMessenger_RegisterReceiver(int, int, int *, int, int);
extern "C" void Gap__Bec__beFont__vfunc_23(void);
extern "C" int FUN_0030b420(...);
extern "C" int List_Reserve(int, int, int);
extern "C" int Gap__Bec__beFont__vfunc_30(void);
extern "C" void Gap__Bec__beFont__vfunc_31(void);
extern "C" int Gap__Bec__beFont__vfunc_20(void);
extern "C" int FUN_00361df0(...);
extern "C" int FUN_00361d30(...);
extern "C" int FUN_00361d90(...);
extern "C" int beMessenger_ResolveEnumValue(int, int, int);
extern "C" void beMessenger_SelectGroup(int, void *);
extern "C" void beMessenger_AppendString(int, void *);
extern "C" void beMessenger_DispatchSelected(int, void *);
extern "C" int beMessenger_GetBoolCount(int);
extern "C" int beMessenger_GetStringCount(int);
extern "C" int beMessenger_GetIntCount(int);
extern "C" int beMessenger_GetObjectCount(int);
extern "C" int beMessenger_GetInt(int, int);
extern "C" void *beMessenger_GetObject(int, int);
extern "C" int beMessenger_GetString(int, int);
extern "C" void beMessenger_GetVec3(void *, int, int);
extern "C" void ObjectList_AppendRetainedList(void *, void *);
extern "C" void ObjectList_AppendRetained(void *, void *);
extern "C" int igObject_IsKindOf(void *, int);
extern "C" void * igObject_GetAllocator(...);
extern "C" void * Memory_GetAllocatorBySelector(...);
extern "C" void *FUN_003624f0(void *);
extern "C" void *FUN_00137810(void *);
extern "C" int FUN_002eb010(int);
extern "C" int StringPool_Construct(int);
extern "C" int StringPool_Intern(...);
extern "C" void StringChunk_ReleaseHeader(...);
extern "C" void FUN_0030b3c0(void *, void *);
class N;
struct FontLayout;
extern "C" void FUN_00383420(beFont *self, FontLayout *layout, N *src, int idx);
extern "C" void FUN_001dc820(void *, int);
extern "C" void FUN_001dc880(void *, int);
extern "C" void FUN_00193540(void *, int, int);
extern "C" void Matrix44_SetTranslation(void *, void *);
extern "C" unsigned int Memory_GetBufferSize(...);
extern "C" int FUN_00301e30(int, void *);
extern "C" int strlen(const char *);
extern "C" int strcmp(...);
extern "C" int FUN_00455370(int, int);
extern "C" int FUN_004553e0(int, int);
extern "C" void List_Resize(void *, int, int);
extern "C" void FUN_00384010(int arg0, int *arg1, int *arg2, int *arg3);
extern "C" int Memory_FreeBufferWithAllocator(int, int);
extern "C" int memset(int, int, unsigned int);
extern "C" int Memory_AllocateAlignedWithAllocator(unsigned int, int, int);
extern "C" int Gap__Bec__beUnicodeObj__vfunc_20(void);
extern "C" int TEXTCTL[4];
extern "C" void Gap__Bec__beFont__vfunc_29(beFont *self, int receiver);
extern "C" int Gap__Core__igObject__vfunc_24(beFont *);
extern "C" void Gap__Bec__beFont__vfunc_24(beFont *arg0);
extern "C" void Gap__Bec__beFont__vfunc_32(beFont *arg0);
extern "C" int g_beFontInfo_metaObject[4];
extern "C" int g_beFont_metaObject[4];
class VObj;
extern "C" int emptyString[4];
extern "C" int DAT_0050e730[4];
extern "C" int DAT_0050e740[4];
extern "C" int DAT_0050e748[4];
extern "C" int DAT_0050e758[4];
extern "C" int g_igColorAttr_metaObject[4];
extern "C" int g_igGroup_metaObject[4];
extern "C" int g_igAttrSet_metaObject[4];
extern "C" int g_stringPool[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" int g_beUnicodeObj_metaObject[4];
extern "C" unsigned char GPR_00554c14;
class N;
/* element array of an igObjectList (_data is a 4-byte arena handle) */

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
/* Scope holder whose destructor releases the reference; it is a template on the kind because each
 * kind needs its own out-of-line destructor. */
template <int kind> struct RP {
    N *p;
    RP(N *x) { p = x; }
    ~RP() { N *o = p; if (o != 0) { o->ref = o->ref - 1; if ((o->ref & 0x7FFFFF) == 0) igObject_Destroy(o); } }
};
struct H { static int cnt(igObjectList *l) { if (l != 0) return l->_count; return 0; }
  static N *castit(N *s) { if (s != 0 && igObject_IsKindOf(s, g_igAttrSet_metaObject[0]) != 0) return s; else return 0; } };
extern "C" int Gap__Bec__beFont__vfunc_34(beFont *arg0, N *arg1, N *arg2);
struct KindMatchObject {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual int v20();
};
struct KindMatchList { char p[8]; int n; char q[4]; KindMatchObject **arr; };
struct KindMatchSource { char p[20]; KindMatchList * list; KindMatchList *getList() const { return list; } };
struct KindMatchTarget { char p[36]; int f36; };
extern "C" int g_beFontImage_metaObject[4];
extern "C" void FUN_00382df0(KindMatchTarget *arg0, KindMatchSource *arg1);
struct Pair { unsigned short out; unsigned short key; };
struct Table { Pair e[425]; };
extern "C" beUnicodeObj *FUN_003614f0(int);
extern "C" int FUN_0030b460(igStringObj *, char *, int, int);
extern "C" const Table DAT_004c8880;
extern "C" igSmartPointer<beUnicodeObj> FUN_00382eb0(beFont *self, const char *str);
extern "C" int FUN_00383350(beFont *arg0, int arg1);
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset of the
   vertex-array configure method (an igVertexArray subclass instance; the reflected igVertexArray has no vtable type) */

class Sink { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(unsigned &, int, int, int); virtual void d23(); virtual void d24(); virtual void d25(); virtual void drop(void *, int); };
extern "C" Sink *FUN_0014b940(...);
extern "C" void FUN_00383910(beFont *arg0, igGeometryAttr *arg1, int arg2, int arg3);
/* matching construct: dummy-virtual class supplies the retail vtable slot offset for igGeometryAttr's configure virtual (vtable slot 39) */

class GeomAttrVirtual {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();
    virtual void Configure(int, int, int);
};
extern "C" void FUN_00383ab0(beFont *arg0, igGeometryAttr *arg1, int arg2, int arg3);
/* arg0 is the beFont: +36 _fonts (glyph list), +40 _fontIdx, +48 _lineFeedList, +52 _alignList. */

typedef union U { float f; struct { unsigned char p0, p1, p2; unsigned char lo : 7; unsigned char sign : 1; } b; } U;
typedef struct IntList { char p0[8]; int count; int cap; int *data; int getCount() const { return count; } } IntList;
typedef struct FloatList { char p0[8]; int count; int cap; float *data; int getCount() const { return count; } } FloatList;
typedef struct Glyph { char p0[12]; float f12; } Glyph;
typedef struct GlyphList { char p0[16]; Glyph **data; } GlyphList;
typedef struct Mesh { char p0[12]; unsigned count; char *verts; int stride; } Mesh;
extern "C" void FUN_00383bf0(beFont *arg0, unsigned short *arg1, int arg2, Mesh *arg3);
class V108 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int); };
extern "C" int FUN_003840a0(beFont *p0, int p1, int p2, int p3);
extern "C" char DAT_0050e7b8[];
/* Second argument: messenger node whose +12 holds the beFontInfo. */
struct P { char p[12]; int f12; };
extern "C" int FUN_003841d0(beFont *arg0, struct P *arg1);
extern "C" int Gap__Core__igObject__vfunc_08__002ff0f0(beUnicodeObj *);
extern "C" void Gap__Bec__beUnicodeObj__vfunc_08(beUnicodeObj *arg0);
extern "C" void beUnicodeObj_AllocateBuffer(beUnicodeObj *arg0, int arg1);
extern "C" int g_beUnicodeObj_metaObject[4];

/* Tail call to the base-class slot 23 (igObject::vfunc_23). The receiver stays in the argument
 * register, which is why the declaration takes no parameters. */
void Gap__Bec__beFont__vfunc_23(void)
{
    Gap__Core__igObject__vfunc_23();
}

void Gap__Bec__beFont__vfunc_24(beFont *arg0) {
    beFontImageList *l;
    int n;
    int n2;
    int i;
    int j;
    igObject *p;

    l = (beFontImageList *)arg0->_fonts;
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
    Gap__Core__igObject__vfunc_24(arg0);
}

/* Registers `receiver` with the font's messenger under the "TEXTCTL" group string, with a null
 * text argument and -1 as the last argument. */
void Gap__Bec__beFont__vfunc_29(beFont *self, int receiver)
{
    beMessenger_RegisterReceiver(self->_messenger, receiver, &TEXTCTL[0], 0, -1);
}

static inline int count(const beFontGeomAttrPairList *list) { return list->_count; }

void Gap__Bec__beFont__vfunc_32(beFont *arg0) {
    beFontGeomAttrPairList *l;
    int n;
    int n2;
    int i;
    int j;
    igObject *p;
    igObject *q;

    q = (igObject *)arg0->_root;
    if (q != 0) {
        q->_refCount = q->_refCount - 1;
        if ((q->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(q);
        }
    }
    arg0->_root = 0;
    l = (beFontGeomAttrPairList *)arg0->_gaPairList;
    if (count(l) > 0) {
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
        if (!(0 < ((beFontGeomAttrPairList *)arg0->_gaPairList)->_count)) {
            List_Reserve(arg0->_gaPairList, 0, 4);
        }
    }
    FUN_0030b420(arg0->_convertData);
}

int Gap__Bec__beFont__vfunc_30(void)
{
    return g_beFontInfo_metaObject[0];
}

void Gap__Bec__beFont__vfunc_31(void)
{
}

int Gap__Bec__beFont__vfunc_34(beFont *arg0, N *arg1, N *arg2) {
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
        if (g_igGroup_metaObject[0] != o->Meta()) FAIL(arg1)
        lst = o->f28;
        cc = 0;
        if (lst != 0) cc = lst->_count;
        if (cc <= 0) FAIL(arg1)
        mem = LD(lst)[0];
        if (g_igAttrSet_metaObject[0] != mem->Meta()) FAIL(arg1)
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
            ObjectList_AppendRetainedList(e1->f32, (void *)((beFontImage *)((int *)((beFontImageList *)arg0->_fonts)->_data)[FUN_00383350((beFont *)arg0, (int)(e2->f8 ? (const char *)e2->f8 : (const char *)emptyString))])->_attrList);
            j = 0;
            while (j < CNT(e2->f28)) {
                e3 = H::castit(LD(e2->f28)[j]);
                {
                    void *ga = igObject_GetAllocator(arg0);
                    void *al;
                    if (GPR_00554c14 != 0) al = ga; else al = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                    RP<0> po((N *)FUN_003624f0(al));
                    SETSTR(po.p, f8, e1->f8)
                    SETSTR(po.p, f12, e3->f8)
                    ga = igObject_GetAllocator(arg0);
                    if (GPR_00554c14 != 0) al = ga; else al = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
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
                if (g_beUnicodeObj_metaObject[0] == x->Meta()) {
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
                idx = FUN_003840a0((beFont *)arg0, (int)arg1, s1, s0);
                if (idx != -1) {
                    do {
                        FUN_00383420(arg0, (FontLayout *)arg1, ra.p, idx);
                        idx = FUN_003841d0((beFont *)arg0, (struct P *)arg1);
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
            idx = FUN_003840a0((beFont *)arg0, (int)arg1, s2, s1);
            if (idx != -1) {
                do {
                    LD((igObjectList *)ent->f20)[idx]->f36 = s0;
                    idx = FUN_003841d0((beFont *)arg0, (struct P *)arg1);
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
            idx = FUN_003840a0((beFont *)arg0, (int)arg1, s2, s1);
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
                    idx = FUN_003841d0((beFont *)arg0, (struct P *)arg1);
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
            idx = FUN_003840a0((beFont *)arg0, (int)arg1, s1, s0);
            if (idx != -1) {
                do {
                    Matrix44_SetTranslation((char *)LD(((N *)(LD((igObjectList *)ent->f20)[idx]->f16))->f28)[0] + 32, &v);
                    idx = FUN_003841d0((beFont *)arg0, (struct P *)arg1);
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
            idx = FUN_003840a0((beFont *)arg0, (int)arg1, s2, s0);
            if (idx != -1) {
                do {
                    int q;
                    N *w;
                    igObjectList *ll = ((N *)(LD((igObjectList *)ent->f20)[idx]->f16))->f32;
                    q = 0;
                    if (0 < ll->_count) {
                        do {
                        w = LD(ll)[q];
                        if (g_igColorAttr_metaObject[0] == w->Meta()) {
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
                    idx = FUN_003841d0((beFont *)arg0, (struct P *)arg1);
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

static inline int count_382df0(KindMatchList *l) { return l->n; }

static inline KindMatchObject *at(KindMatchList *l, int i) { return l->arr[i]; }

void FUN_00382df0(KindMatchTarget *arg0, KindMatchSource *arg1) {
    int i;
    for (i = 0; i < count_382df0(arg1->getList()); i++) {
        KindMatchObject *o = at(arg1->list, i);
        int g = g_beFontImage_metaObject[0];
        if (g == o->v20()) {
            FUN_00301e30(arg0->f36, o);
        }
    }
}

igSmartPointer<beUnicodeObj> FUN_00382eb0(beFont *self, const char *str) {
    Table t = DAT_004c8880;
    char c0;
    char c1;
    char c2;
    int n = 0;
    unsigned i = 0;
    int a;
    while (i < (unsigned)strlen(str)) {
        const char *p = str + i;
        unsigned c = (unsigned char)*p;
        if (c == 10) {
            if (n > 0) n++;
            i++;
        } else if (c == 13) {
            i++;
        } else if (c & 0x80) {
            unsigned short hi = (unsigned char)c << 8;
            unsigned short key = hi | (unsigned char)p[1];
            const char *sec = p + 1;
            Pair *q = t.e;
            if (q->out != 0xffff) {
                do {
                    if (key == q->key) { n++; break; }
                    q++;
                } while (q->out != 0xffff);
            }
            FUN_0030b420((igStringObj *)self->_convertData);
            c0 = *p;
            FUN_0030b460((igStringObj *)self->_convertData, &c0, ((igStringObj *)self->_convertData)->_length, 1);
            c1 = *sec;
            FUN_0030b460((igStringObj *)self->_convertData, &c1, ((igStringObj *)self->_convertData)->_length, 1);
            i += 2;
        } else {
            unsigned char ch = c;
            unsigned short cc = ch;
            Pair *q = t.e;
            if (q->out != 0xffff) {
                do {
                    if (cc == q->key) { n++; break; }
                    q++;
                } while (q->out != 0xffff);
            }
            FUN_0030b420((igStringObj *)self->_convertData);
            c2 = *p;
            FUN_0030b460((igStringObj *)self->_convertData, &c2, ((igStringObj *)self->_convertData)->_length, 1);
            i++;
        }
    }
    a = ((int)igObject_GetAllocator(self));
    a = GPR_00554c14 ? a : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<beUnicodeObj> r(FUN_003614f0(a));
    beUnicodeObj_AllocateBuffer(r.p, n);
    unsigned short *buf = (unsigned short *)r.p->_buffer;
    int m = 0;
    unsigned j = 0;
    while (j < (unsigned)strlen(str)) {
        const char *p = str + j;
        unsigned c = (unsigned char)*p;
        if (c == 10) {
            if (m > 1) buf[m++] = c;
            j++;
        } else if (c == 13) {
            j++;
        } else if (c & 0x80) {
            unsigned short hi = (unsigned char)c << 8;
            unsigned short key = hi | (unsigned char)p[1];
            int k = 0;
            Pair *q = t.e;
            if (q->out != 0xffff) {
                do {
                    if (key == q->key) { buf[m++] = t.e[k].out; break; }
                    q++;
                    k++;
                } while (q->out != 0xffff);
            }
            j += 2;
        } else {
            unsigned char ch = c;
            unsigned short cc = ch;
            Pair *q = t.e;
            if (q->out != 0xffff) {
                do {
                    if (cc == q->key) { buf[m++] = ch; break; }
                    q++;
                } while (q->out != 0xffff);
            }
            j++;
        }
    }
    buf[m] = 0;
    return r;
}

int FUN_00383350(beFont *arg0, int arg1) {
    int s1;
    int *a1;
    if (arg1 == 0) {
        return 0;
    }
    s1 = 0;
    if (0 < ((beFontImageList *)arg0->_fonts)->_count) {
        do {
            a1 = (int *)(((beFontImage **)((beFontImageList *)arg0->_fonts)->_data)[s1])->_name;
            a1 = a1 ? a1 : &emptyString[0];
            if (strcmp(arg1, a1) == 0) {
                return s1;
            }
            s1 += 1;
        } while (s1 < ((beFontImageList *)arg0->_fonts)->_count);
    }
    return 0;
}

extern "C" int FUN_0015db90(void *);
extern "C" void FUN_00383ed0(beFont *, int, void *, void *);
extern "C" void List_RemoveWordAt(void *, int);
extern "C" const char *DAT_004c22f0[4];
extern "C" char DAT_0050e798[16];
extern "C" char DAT_0050e7a8[16];
class FontSlot {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void apply(Sink *, int);
};
struct FontLayoutEntry { char p0[8]; const int *name1; int p12; int names; char p20[16]; int kind; int key; };
struct FontLayoutTable { char p0[20]; igObjectList *entries; };
struct FontLayout { char p0[12]; FontLayoutTable *table; };

void FUN_00383420(beFont *self, FontLayout *layout, N *src, int idx) {
    FontLayoutEntry *ent = (FontLayoutEntry *)((int *)layout->table->entries->_data)[idx];
    igAttrSet *out = (igAttrSet *)((int *)((igObjectList *)((igAttrSet *)((int *)((igObjectList *)((igAttrSet *)ent->names)->_childList)->_data)[0])->_childList)->_data)[0];
    void *keep = (void *)((int *)((igObjectList *)out->_attributes)->_data)[0];
    igSmartPointer<beUnicodeObj> cur(0);
    igMetaObject *info;
    if (cur.p != 0) ++cur.p->_refCount;
    info = (igMetaObject *)src->Meta();
    if (strcmp((const char *)info->_name, DAT_0050e798) == 0) {
        const char *s0 = (const char *)((igStringObj *)src)->_buffer;
        const char *s;
        if (s0 == 0) s = DAT_004c22f0[0]; else s = s0;
        igSmartPointer<beUnicodeObj> tmp(FUN_00382eb0(self, s));
        beUnicodeObj *n = tmp.get();
        if (n != 0) ++n->_refCount;
        beUnicodeObj *o = cur.p;
        if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); }
        cur.p = n;
    } else if (strcmp((const char *)info->_name, DAT_0050e7a8) == 0) {
        if (src != 0) ++((beUnicodeObj *)src)->_refCount;
        beUnicodeObj *o = cur.p;
        if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); }
        cur.p = (beUnicodeObj *)src;
    } else {
        return;
    }
    /* matching construct: declaration-order search — the order of these locals sets which argument registers the search loop uses */
    beFontGeomAttrPair *g = 0;
    int i;
    beFontGeomAttrPair *e;
    int off;
    beFontGeomAttrPairList *gl = (beFontGeomAttrPairList *)self->_gaPairList;
    beFontGeomAttrPairList *l = gl;
    if (l->_count > 0) {
        i = 0;
        if (i < l->_count) {
            off = 0;
            do {
                e = (beFontGeomAttrPair *)((int *)((char *)l->_data + off))[0];
                const int *a = ent->name1;
                const int *a2;
                if (a != 0) a2 = a; else a2 = emptyString;
                if ((int)a2 == e->_category) {
                    const int *b = (const int *)((igAttrSet *)ent->names)->_name;
                    const int *b2;
                    if (b != 0) b2 = b; else b2 = emptyString;
                    if ((int)b2 == e->_panel) { g = e; break; }
                }
                l = gl;
                i++;
                off += 4;
            } while (i < *(int *)&l->_count);
        }
    }
    int fid = cur.p->_buffer;
    self->_fontIdx = FUN_00383350(self, ent->key);
    igGeometryAttr *fr = (igGeometryAttr *)((int *)((igObjectList *)g->_geomAttrs)->_data)[0];
    FUN_00383ab0(self, fr, fid, 1);
    Sink *sk = (Sink *)fr->_vertexArray;
    ((FontSlot *)((int *)((beFontImageList *)self->_fonts)->_data)[self->_fontIdx])->apply(sk, fid);
    char bufB[32];
    char buf9[32];
    FUN_0015db90(bufB);
    FUN_0015db90(buf9);
    FUN_00384010((int)self, (int *)sk, (int *)bufB, (int *)buf9);
    FUN_00383bf0(self, (unsigned short *)fid, (int)ent, (Mesh *)bufB);
    if (ent->kind == 1 || ent->kind == 2) FUN_00383ed0(self, fid, ent, bufB);
    sk->drop(buf9, 0);
    sk->drop(bufB, 0);
    ObjectList_AppendRetained((void *)g->_geomAttrs, keep);
    igObjectList *fl = (igObjectList *)out->_attributes;
    if (fr != 0) ++fr->_refCount;
    igGeometryAttr *old = (igGeometryAttr *)((int *)fl->_data)[0];
    if (old != 0) { --old->_refCount; if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old); }
    int k = 0;
    if (fl->_count != 0 && k >= 0 && k < fl->_count) ((int *)fl->_data)[0] = (int)fr;
    igObjectList *fl2 = (igObjectList *)g->_geomAttrs;
    igGeometryAttr *old2 = (igGeometryAttr *)((int *)fl2->_data)[0];
    if (old2 != 0) { --old2->_refCount; if ((old2->_refCount & 0x7fffff) == 0) igObject_Destroy(old2); }
    List_RemoveWordAt(fl2, 0);
    ((int *)fl2->_data)[fl2->_count] = 0;
}

/* Owning stack reference to a vertex array: first the attribute's current array, then the newly
 * created one (reference count in the low 23 bits of _refCount); released on scope exit. */

void FUN_00383910(beFont *arg0, igGeometryAttr *arg1, int arg2, int arg3) {
    igSmartPointer<igVertexArray> va((igVertexArray *)arg1->_vertexArray); /* matching construct: declared first so it takes the retail slot above sp68 */
    unsigned sp68;
    void *al;
    igVertexArray *t;
    igVertexArray *p;
    t = va.p;
    if (t != 0) {
        t->_refCount = t->_refCount + 1;
    }
    al = igObject_GetAllocator(arg0);
    al = (GPR_00554c14 != 0) ? al : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    t = va.p;
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if (((unsigned long long)(long long)(int)t->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
    va.p = (igVertexArray *)FUN_0014b940(al);
    sp68 = ((beFontImage **)((beFontImageList *)arg0->_fonts)->_data)[arg2]->_vertexFlags;
    sp68 = sp68 & ~4u;
    ((Sink *)va.p)->vX(sp68, arg3, 0, 0);
    p = va.p;
    if (p != 0) {
        p->_refCount = p->_refCount + 1;
    }
    t = (igVertexArray *)arg1->_vertexArray;
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if (((unsigned long long)(long long)(int)t->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
    arg1->_vertexArray = (int)p;
}

/* Owning stack reference to the attribute's vertex array (reference count in the low 23 bits of
 * _refCount); released on scope exit. */

void FUN_00383ab0(beFont *arg0, igGeometryAttr *arg1, int arg2, int arg3) {
    int v;
    unsigned s0;
    igVertexArray *t;
    if (arg3 != 0) {
        v = FUN_004553e0(((int *)((igObjectList *)arg0->_fonts)->_data)[arg0->_fontIdx], arg2);
        s0 = (v + 2) * 3;
    } else {
        v = FUN_00455370(((int *)((igObjectList *)arg0->_fonts)->_data)[arg0->_fontIdx], arg2);
        s0 = v * 3;
    }
    ((GeomAttrVirtual *)arg1)->Configure(3, v, 0);
    {
        igSmartPointer<igVertexArray> va((igVertexArray *)arg1->_vertexArray);
        t = va.p;
        if (t != 0) {
            t->_refCount = t->_refCount + 1;
        }
        t = va.p;
        if (t != 0) {
            if (t->_numVerts < s0) {
                goto b8;
            }
        } else {
b8:
            FUN_00383910(arg0, arg1, arg0->_fontIdx, (int)s0);
        }
    }
}

void FUN_00383bf0(beFont *arg0, unsigned short *arg1, int arg2, Mesh *arg3) {
    float zo;
    unsigned short ch;
    int c;
    unsigned i;
    U u;
    int d;
    char *base;
    float *v;
    float yo;
    unsigned end;
    int a;
    unsigned n;
    IntList *li;
    float xo;
    int b;
    FloatList *lf;
    int sw;
    n = 0;
    xo = 0.0f;
    zo = 0.0f;
    ((IntList *)arg0->_lineFeedList)->count = 0;
    ((FloatList *)arg0->_alignList)->count = 0;
    ch = *arg1;
    base = arg3->verts;
    yo = xo;
    if (ch != 0) {
        do {
            sw = ch;
            switch (sw) {
            case 13:
                break;
            case 10:
                if (n != 0) {
                    li = ((IntList *)arg0->_lineFeedList);
                    a = li->count;
                    v = (float *)(base + arg3->stride * n);
                    if (a < li->cap) li->count = li->getCount() + 1; else List_Resize(li, a + 1, 4);
                    li->data[a] = n;
                    u.f = xo;
                    u.b.sign = 0;
                    lf = ((FloatList *)arg0->_alignList);
                    b = lf->count;
                    xo = *v - u.f;
                    if (b < lf->cap) lf->count = lf->getCount() + 1; else List_Resize(lf, b + 1, 4);
                    lf->data[b] = xo;
                    xo = -*v;
                    yo = yo - ((GlyphList *)arg0->_fonts)->data[arg0->_fontIdx]->f12;
                }
                break;
            default:
                end = n + 6;
                i = n;
                if (n < end) {
                  if (i < end) {
                    do {
                        v = (float *)(base + arg3->stride * i);
                        i++;
                        v[0] = v[0] + xo;
                        v[1] = v[1] + yo;
                        v[2] = v[2] + zo;
                    } while (i < end);
                  }
                }
                n += 6;
                break;
            }
            arg1++;
            ch = *arg1;
        } while (ch != 0);
    }
    arg3->count = n;
    li = ((IntList *)arg0->_lineFeedList);
    c = li->count;
    if (c < li->cap) li->count = li->getCount() + 1; else List_Resize(li, c + 1, 4);
    li->data[c] = n;
    lf = ((FloatList *)arg0->_alignList);
    d = lf->count;
    if (d < lf->cap) lf->count = lf->getCount() + 1; else List_Resize(lf, d + 1, 4);
    lf->data[d] = *v;
}

void FUN_00384010(int arg0, int *arg1, int *arg2, int *arg3) {
    int temp_v0;

    arg2[1] = 0;
    arg2[0] = 0;
    arg2[2] = 0;
    arg3[1] = 3;
    arg3[0] = 0;
    arg3[2] = 0;
    temp_v0 = arg1[3];
    arg3[3] = temp_v0;
    arg2[3] = temp_v0;
    ((V108 *)arg1)->vX((int)arg2, 1);
    ((V108 *)arg1)->vX((int)arg3, 1);
}

int FUN_003840a0(beFont *p0, int p1, int p2, int p3) {
    int arg2 = p2;
    beFont *arg0 = p0;
    int arg1 = p1;
    int arg3 = p3;
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0;
    int temp_v0_2;
    int var_v0;
    int var_v0_2;
    int temp_v1;
    int temp_v1_2;

    if (g_stringPool[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        g_stringPool[0] = var_v0;
    }
    arg2 = StringPool_Intern(g_stringPool[0], arg2);
    temp_v1 = arg0->_condition00;
    if (temp_v1 != 0) {
        temp_a1 = (int *)(temp_v1 - 8);
        temp_v0 = *(int *)(temp_v1 - 4) - 1;
        *(int *)(temp_v1 - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_condition00 = arg2;
    if (g_stringPool[0] == 0) {
        var_v0_2 = FUN_002eb010(0x10);
        if (var_v0_2 != 0) {
            var_v0_2 = StringPool_Construct(var_v0_2);
        }
        g_stringPool[0] = var_v0_2;
    }
    arg3 = StringPool_Intern(g_stringPool[0], arg3);
    temp_v1_2 = arg0->_condition01;
    if (temp_v1_2 != 0) {
        temp_a1_2 = (int *)(temp_v1_2 - 8);
        temp_v0_2 = *(int *)(temp_v1_2 - 4) - 1;
        *(int *)(temp_v1_2 - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
        }
    }
    arg0->_condition01 = arg3;
    arg0->_history = 0;
    return FUN_003841d0(arg0, (P *)arg1);
}

int FUN_003841d0(beFont *arg0, struct P *arg1) {
    int j;
    const char *p;
    int res;
    int i;
    igAttrSet *y;
    const char *q;
    beFontInfoData *it;
    int off;
    beBaseInfoDataList *l;
    int off2;

    res = -1;
    l = (beBaseInfoDataList *)((beFontInfo *)arg1->f12)->_dataList;
    if (strcmp((const char *)arg0->_condition00, DAT_0050e7b8) == 0) {
        i = arg0->_history;
        off = i * 4;
        if (i < l->_count) {
            do {
                q = (const char *)arg0->_condition01;
                p = (const char *)((igAttrSet *)((beFontInfoData *)*(int *)(l->_data + off))->_attrSet)->_name;
                if (strcmp(p != 0 ? p : ((char *)emptyString), q) == 0) {
                    res = i;
                    break;
                }
                i += 1;
                off += 4;
            } while (i < l->_count);
        }
    } else {
        j = arg0->_history;
        off2 = j * 4;
        if (j < l->_count) {
            do {
                it = (beFontInfoData *)*(int *)(l->_data + off2);
                p = (const char *)it->_name;
                y = (igAttrSet *)it->_attrSet;
                q = (const char *)arg0->_condition00;
                if (strcmp(p != 0 ? p : ((char *)emptyString), q) == 0) {
                    p = (const char *)y->_name;
                    q = (const char *)arg0->_condition01;
                    if (strcmp(p != 0 ? p : ((char *)emptyString), q) == 0) {
                        res = j;
                        break;
                    }
                }
                j += 1;
                off2 += 4;
            } while (j < l->_count);
        }
    }
    if (res != -1) {
        arg0->_history = res + 1;
    }
    return res;
}

void Gap__Bec__beUnicodeObj__vfunc_08(beUnicodeObj *arg0) {
    if (arg0->_buffer != 0) {
        Memory_FreeBufferWithAllocator(arg0->_buffer, ((int)igObject_GetAllocator()));
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

void beUnicodeObj_AllocateBuffer(beUnicodeObj *arg0, int arg1) {
    unsigned int need;
    if (arg0->_buffer != 0) {
        need = (arg1 + 1) * 2;
        if (Memory_GetBufferSize(arg0->_buffer) < need) {
            Memory_FreeBufferWithAllocator(arg0->_buffer, ((int)igObject_GetAllocator(arg0)));
            arg0->_buffer = Memory_AllocateAlignedWithAllocator(need, 0x10, ((int)igObject_GetAllocator(arg0)));
        }
    } else {
        arg0->_buffer = Memory_AllocateAlignedWithAllocator((arg1 + 1) * 2, 0x10, ((int)igObject_GetAllocator(arg0)));
    }
    memset(arg0->_buffer, 0, Memory_GetBufferSize(arg0->_buffer));
}

int Gap__Bec__beUnicodeObj__vfunc_20(void)
{
    return g_beUnicodeObj_metaObject[0];
}

int Gap__Bec__beFont__vfunc_20(void)
{
    return g_beFont_metaObject[0];
}

