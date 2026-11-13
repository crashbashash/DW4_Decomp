#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
#define REL(x) { RC *q = (x); if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7FFFFF) == 0) igObject_Destroy(q); } }
#define ALLOC(a, self) { int base_ = igObject_GetAllocator(self); if (GPR_00554c14 != 0) { a = base_; } else { a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); } }

typedef struct O { char p[32]; int w; int h; char q[20]; int cw; int ch; } O;
extern "C" int DAT_004c2c50[4];
extern "C" int DAT_004c2c58[4];
extern "C" int FUN_00338f70(O *o, int *a1, int *a2, int *a3, int *a4);
extern "C" int g_igMovieManager_metaObject[4];
extern "C" void Gap__igMovieManager__vfunc_21(void);
extern "C" void Gap__igMovieManager__vfunc_23(void);
extern "C" void Gap__igMovieManager__vfunc_24(void);
extern "C" void Gap__igMovieManager__vfunc_27(void);
extern "C" int Gap__igMovieManager__vfunc_20(void);
class DW4VC_112_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(); };
extern "C" void Gap__igMovieManager__vfunc_22(void **arg0);
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 128 */

class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();  virtual int vX(void *, igSmartPointer<igObject>); };
extern "C" void FUN_00339110(igMovieManager *arg0, igSmartPointer<igObject> arg1);
class VC_339200 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void vX(void *); };
struct O_339200 { char pad[72]; VC_339200 *vc; };
struct B { char pad[8]; int cnt; char pad2[4]; O_339200 **arr; };
struct A { char pad[16]; struct B *b; };
extern "C" void FUN_00339200(A *a);
extern "C" int igObject_GetAllocator(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_IsKindOf(...);
extern "C" int strcmp(...);
extern "C" void *igObjectSystem_FindMetaByNameDefault(...);
extern "C" void *igMetaObject_CreateInstance(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int FUN_00308320(...);
extern "C" void *FUN_00335400(...);
extern "C" void *FUN_00335da0(...);
extern "C" void *FUN_00142f30(...);
extern "C" void *FUN_0044c490(...);
extern "C" int igInsightCore_AddToScheduler(...);
extern "C" int FUN_00236ee0(...);
extern "C" int FUN_002d6f50(...);
extern "C" int FUN_002d7690(...);
extern "C" int emptyString[4];
extern "C" int DAT_005010f0[4];
extern "C" int DAT_00501120[4];
extern "C" int DAT_00501140[4];
extern "C" int DAT_00501170[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" int g_igMovieCodec_metaObject[4];
extern "C" int g_igMovieInfo_metaObject[4];
extern "C" unsigned char GPR_00554c14;
extern "C" unsigned char GPR_00554e30;
extern "C" unsigned char GPR_00554e34;
extern "C" unsigned char GPR_00554e38;
extern "C" unsigned char GPR_00554e3c;
/* matching construct: dummy virtual slots; vK() dispatches through the retail vtable offset 8 + 4*K */
class VC_3392a0 {
public:
    virtual int v0(...); virtual int v1(...); virtual int v2(...); virtual int v3(...); virtual int v4(...);
    virtual int v5(...); virtual int v6(...); virtual int v7(...); virtual int v8(...); virtual int v9(...);
    virtual int v10(...); virtual int v11(...); virtual int v12(...); virtual int v13(...); virtual int v14(...);
    virtual int v15(...); virtual int v16(...); virtual int v17(...); virtual int v18(...); virtual int v19(...);
    virtual int v20(...); virtual int v21(...); virtual int v22(...); virtual int v23(...); virtual int v24(...);
    virtual int v25(...); virtual int v26(...); virtual int v27(...); virtual int v28(...); virtual int v29(...);
    virtual int v30(...); virtual int v31(...); virtual int v32(...); virtual int v33(...); virtual int v34(...);
    virtual int v35(...); virtual int v36(...);
};
/* reference-counted engine object header: refcount word at +4 (low 23 bits) */
struct RC : public igObject { };
/* 4-byte struct returned through a hidden pointer by vtable slot 22 of the audio object */
struct R4 { int x; };
/* igMovieManager._movieRenderer: only the owner back-reference at +12 is used here */
struct MovieRenderer { int pad[3]; int owner; };
/* Same vtable layout; slot 22 returns a 4-byte struct through a hidden pointer (the buffer is
 * passed in a0). */
class VS {
public:
    virtual int v0(...); virtual int v1(...); virtual int v2(...); virtual int v3(...); virtual int v4(...);
    virtual int v5(...); virtual int v6(...); virtual int v7(...); virtual int v8(...); virtual int v9(...);
    virtual int v10(...); virtual int v11(...); virtual int v12(...); virtual int v13(...); virtual int v14(...);
    virtual int v15(...); virtual int v16(...); virtual int v17(...); virtual int v18(...); virtual int v19(...);
    virtual int v20(...); virtual int v21(...); virtual R4 s22();
};
struct ListHead {
    int a; int b; int count; int cap; int *data;
    /* matching construct: reading the search key through a pointer keeps it in a stack slot, as retail does */
    static RC *cur(RC *const *a) { return *a; }
    /* inlined igObjectList::indexOf(item): linear search, -1 when absent */
    int indexOf(RC *item) {
        int n = count;
        int i = 0;
        if (0 < n) {
            int *p = data;
            do {
                if (cur(&item) == (RC *)*p) return i;
                i++; p++;
            } while (i < n);
        }
        return -1;
    }
};
/* igMovieInfo: name +8, mode +24 (2 = no manager check), codec name +68, codec ref +72. */
struct MovieInfo : public igObject { const char *name; int pad[3]; int mode; int pad2[10]; const char *codecName; int codec; };
extern "C" int Gap__igMovieManager__vfunc_25(igMovieManager *self, void *arg1);
struct Lst { int a; int b; int n; int c; int *d; };
struct M {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    
    virtual int v30(int);
    int f1, f2, f3; Lst *l;
};
extern "C" void Gap__igMovieManager__vfunc_26(M *m);
class V116 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(void *); };
struct E { char pad72[72]; V116 *f72; };
struct L { char pad8[8]; int cnt; char pad12[4]; E **arr; };
struct S { char pad16[16]; L *l; };
extern "C" void FUN_0033bbd0(S *arg0);
typedef struct E_33bc60 { char pad[20]; int f14; char pad2[52]; int f4c; } E_33bc60;
typedef struct L_33bc60 { char pad[8]; int f8; char pad2[4]; E_33bc60 **f10; } L_33bc60;
typedef struct O_33bc60 { char pad[16]; L_33bc60 *f10; } O_33bc60;
extern "C" int Gap__igMovieManager__vfunc_30(O_33bc60 *arg0, int arg1);
extern "C" int DAT_005012f0[4];
extern "C" unsigned char GPR_00554e4c;
extern "C" void igMovieRenderer_InitializeDrawing(igMovieRenderer *arg0);
extern "C" int g_igMovieRenderer_metaObject[4];
extern "C" void Gap__igMovieRenderer__vfunc_23(void);
extern "C" int Gap__igMovieRenderer__vfunc_20(void);
extern "C" void Gap__igMovieRenderer__vfunc_24(igMovieRenderer *self);
extern "C" void Gap__igMovieRenderer__vfunc_22(igMovieRenderer *self);

int FUN_00338f70(O *o, int *a1, int *a2, int *a3, int *a4) {
    int v;
    v = o->cw;
    *a1 = (v != -1) ? v : DAT_004c2c50[0];
    v = o->ch;
    *a2 = (v != -1) ? v : DAT_004c2c58[0];
    if (*a1 == -1) {
        *a1 = o->w;
        *a3 = 1;
    } else {
        if (o->w < *a1) *a1 = o->w;
        *a3 = o->w / *a1;
        if (o->w % *a1 != 0) *a3 = *a3 + 1;
    }
    if (*a2 == -1) {
        *a2 = o->h;
        *a4 = 1;
    } else {
        if (o->h < *a2) *a2 = o->h;
        *a4 = o->h / *a2;
        if (o->h % *a2 != 0) *a4 = *a4 + 1;
    }
    return 1;
}

void Gap__igMovieManager__vfunc_21(void)
{
}

void Gap__igMovieManager__vfunc_22(void **arg0) {
    ((DW4VC_112_0 *)(arg0))->vX();
}

/* Retained share of an engine object held across the codec call. */

void FUN_00339110(igMovieManager *arg0, igSmartPointer<igObject> arg1) {
    int var_s1; int var_s0; igMovieInfoList *var_a0; igMovieInfo *temp_a1;

    var_a0 = (igMovieInfoList *)arg0->_movieList;
    var_s1 = 0;
    if (0 < var_a0->_count) {
        var_s0 = 0;
        do {
            temp_a1 = *(igMovieInfo **)(var_a0->_data + var_s0);
            {
            ((VC *)temp_a1->_codec)->vX(temp_a1, igSmartPointer<igObject>(arg1.p, kRetainReference));
            }
            var_a0 = (igMovieInfoList *)arg0->_movieList;
            var_s1 += 1;
            var_s0 += 4;
        } while (var_s1 < var_a0->_count);
    }
}

void FUN_00339200(A *a) {
    int i;
    for (i = 0; i < a->b->cnt; i++) {
        O_339200 *o = a->b->arr[i];
        o->vc->vX(o);
    }
}

void Gap__igMovieManager__vfunc_23(void)
{
}

void Gap__igMovieManager__vfunc_24(void)
{
}

int Gap__igMovieManager__vfunc_25(igMovieManager *self, void *arg1) {
    int i;
    MovieInfo *movie;
    int a;
    if (arg1 != 0 && igObject_IsKindOf(arg1, g_igMovieInfo_metaObject[0]) != 0) { movie = (MovieInfo *)arg1; } else { movie = 0; }
    if (movie != 0) {
    const char *codecName = movie->codecName;
    if (codecName != 0) {
    ListHead *movies = (ListHead *)self->_movieList;
    if (movies != 0) {
        if (movies->indexOf((RC *)movie) != -1) return 0;
    }
    igSmartPointer<RC> codec;
    codec.p = 0;
    if (codec.p != 0) codec.p->_refCount = codec.p->_refCount + 1;
    if (self->_codecList != 0) {
        i = 0;
        if (0 < ((ListHead *)self->_codecList)->count) {
            do {
                RC *c = ((RC **)((ListHead *)self->_codecList)->data)[i];
                const char *n = (const char *)((int *)((VC_3392a0 *)c)->v20())[7];
                if (strcmp(n, codecName) == 0) {
                    if (c != 0) c->_refCount = c->_refCount + 1;
                    REL(codec.p)
                    codec.p = c;
                    break;
                }
                i++;
            } while (i < ((ListHead *)self->_codecList)->count);
        }
    }
    if (codec.p == 0) {
        void *meta = igObjectSystem_FindMetaByNameDefault(codecName);
        if (meta == 0) {
            if (GPR_00554e30 == 0) {
                int r = FUN_00308320(&DAT_005010f0[0], codecName);
                if (r != 1) { if (r == 2) GPR_00554e30 = 1; }
            }
            return 0;
        }
        ALLOC(a, self);
        RC *created = (RC *)igMetaObject_CreateInstance(meta, a);
        RC *c;
        if (created != 0 && igObject_IsKindOf(created, g_igMovieCodec_metaObject[0]) != 0) { c = created; } else { c = 0; }
        if (c != 0) c->_refCount = c->_refCount + 1;
        REL(codec.p)
        codec.p = c;
        { RC *q = codec.p; q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7FFFFF) == 0) igObject_Destroy(q); }
        if (((VC_3392a0 *)codec.p)->v21() != 0) {
            if (self->_codecList == 0) {
                ALLOC(a, self);
                REL((RC *)self->_codecList)
                self->_codecList = (int)FUN_00335400(a);
            }
            ObjectList_AppendRetained(self->_codecList, codec.p);
        }
    }
    {
        RC *c = codec.p;
        if (c != 0) c->_refCount = c->_refCount + 1;
        REL((RC *)movie->codec)
        movie->codec = (int)c;
    }
    if (self->_audioDisabled == 0 && self->_audio == 0) {
        ALLOC(a, self);
        REL((RC *)self->_audio)
        self->_audio = (int)FUN_00142f30(a);
        ((VC_3392a0 *)self->_audio)->v24(((int *)self->_insight)[5]);
        ((VS *)self->_audio)->s22();
    }
    {
        RC *held = codec.p;
        ((VC_3392a0 *)held)->v22(((VC_3392a0 *)((int *)self->_insight)[5])->v36(), self->_audio);
    }
    if (((VC_3392a0 *)codec.p)->v23(movie) != 0) {
        if (movie->mode == 2 || ((VC_3392a0 *)self)->v29(movie) != 0) {
            if (((VC_3392a0 *)codec.p)->v25(movie) == 0) {
                if (GPR_00554e34 == 0) {
                    const char *nm = movie->name;
                    const char *shown;
                    if (nm != 0) { shown = nm; } else { shown = (const char *)&emptyString[0]; }
                    int r = FUN_00308320(&DAT_00501120[0], shown);
                    if (r != 1) { if (r == 2) GPR_00554e34 = 1; }
                }
                return 0;
            }
            if (self->_movieList == 0) {
                ALLOC(a, self);
                REL((RC *)self->_movieList)
                self->_movieList = (int)FUN_00335da0(a);
            }
            ObjectList_AppendRetained(self->_movieList, movie);
            igInsightCore_AddToScheduler(self->_insight, self);
            {
                MovieRenderer *rend = (MovieRenderer *)self->_movieRenderer;
                if (self != 0) self->_refCount = self->_refCount + 1;
                REL((RC *)rend->owner)
                rend->owner = (int)self;
            }
            if (self->_rendererList == 0) {
                ALLOC(a, self);
                REL((RC *)self->_rendererList)
                self->_rendererList = (int)FUN_0044c490(a);
            }
            {
                ListHead *lst = (ListHead *)((int *)((int *)self->_insight)[7])[2];
                int n = lst->count;
                int i;
                for (i = 0; i < n; i++) {
                    FUN_002d6f50(self->_rendererList, ((ListHead *)((int *)((int *)self->_insight)[7])[2])->data[(unsigned)i] /* matching construct: unsigned index keeps the scale inside the loop */, 0);
                }
            }
            FUN_002d7690(((int *)self->_insight)[7]);
            FUN_00236ee0(self->_insight, self->_movieRenderer);
            return 1;
        }
        if (GPR_00554e38 == 0) {
            const char *nm = movie->name;
            const char *shown;
            if (nm != 0) { shown = nm; } else { shown = (const char *)&emptyString[0]; }
            int r = FUN_00308320(&DAT_00501140[0], shown);
            if (r != 1) { if (r == 2) GPR_00554e38 = 1; }
        }
        return 0;
    }
    if (GPR_00554e3c == 0) {
        const char *nm = movie->name;
        const char *shown;
        if (nm != 0) { shown = nm; } else { shown = (const char *)&emptyString[0]; }
        int r = FUN_00308320(&DAT_00501170[0], shown);
        if (r != 1) { if (r == 2) GPR_00554e3c = 1; }
    }
    return 0;
    }
    }
    return 0;
}

void Gap__igMovieManager__vfunc_26(M *m) {
Lst *l; while ((l = m->l, (bool)l) && l->n != 0) { if (m->v30(*l->d) == 0) break; }
}

void Gap__igMovieManager__vfunc_27(void)
{
}

void FUN_0033bbd0(S *arg0) {
    int i;

    if (arg0->l != 0) {
        for (i = 0; i < arg0->l->cnt; i++) {
            E *e = arg0->l->arr[i];
            e->f72->vX(e);
        }
    }
}

int Gap__igMovieManager__vfunc_30(O_33bc60 *arg0, int arg1) {
    L_33bc60 *var_v1;
    int temp_v0;
    int var_s1;
    int var_s0;
    E_33bc60 *temp_s4;

    var_v1 = arg0->f10;
    if (var_v1 == 0) {
        return 2;
    }
    temp_v0 = var_v1->f8;
    if (temp_v0 <= 0) {
        return 2;
    }
    var_s1 = 0;
    if (0 < temp_v0) {
        var_s0 = 0;
        do {
            temp_s4 = *(E_33bc60 **)((char *)var_v1->f10 + var_s0);
            if (strcmp(temp_s4->f14, arg1) == 0) {
                return temp_s4->f4c;
            }
            var_v1 = arg0->f10;
            var_s1 += 1;
            var_s0 += 4;
        } while (var_s1 < var_v1->f8);
    }
    return 2;
}

void igMovieRenderer_InitializeDrawing(igMovieRenderer *arg0) {
    int temp_v0;

    if ((arg0->_movieManager == 0) && (GPR_00554e4c == 0)) {
        temp_v0 = FUN_00308320(&DAT_005012f0[0]);
        if ((temp_v0 != 1) && (temp_v0 == 2)) {
            GPR_00554e4c = 1;
        }
    }
    FUN_00339110((igMovieManager *)arg0->_movieManager, igSmartPointer<igObject>((igObject *)arg0->_visualContext, kRetainReference));
}

void Gap__igMovieRenderer__vfunc_23(void)
{
}

/* Forwards to FUN_0033bbd0 with the renderer's movie manager (_movieManager, +12). The helper
 * walks the manager's movie list (+16) and calls virtual slot 29 on the object held at +72 of each
 * entry. */
void Gap__igMovieRenderer__vfunc_24(igMovieRenderer *self)
{
    FUN_0033bbd0((S *)self->_movieManager);
}

/* The same walk as slot 24 through FUN_00339200, which calls virtual slot 31 instead of slot 29 on
 * each entry's +72 object. */
void Gap__igMovieRenderer__vfunc_22(igMovieRenderer *self)
{
    FUN_00339200((A *)self->_movieManager);
}

int Gap__igMovieRenderer__vfunc_20(void)
{
    return g_igMovieRenderer_metaObject[0];
}

int Gap__igMovieManager__vfunc_20(void)
{
    return g_igMovieManager_metaObject[0];
}

