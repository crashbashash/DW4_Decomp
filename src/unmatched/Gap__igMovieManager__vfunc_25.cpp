#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int Memory_GetAllocatorBySelector(...);
int igObject_IsKindOf(...);
int strcmp(...);
void *igObjectSystem_FindMetaByNameDefault(...);
void *igMetaObject_CreateInstance(...);
int ObjectList_AppendRetained(...);
int FUN_00308320(...);
void *FUN_00335400(...);
void *FUN_00335da0(...);
void *FUN_00142f30(...);
void *FUN_0044c490(...);
int FUN_00236be0(...);
int FUN_00236ee0(...);
int FUN_002d6f50(...);
int FUN_002d7690(...);
extern int DAT_004e0858[4];
extern int DAT_005010f0[4];
extern int DAT_00501120[4];
extern int DAT_00501140[4];
extern int DAT_00501170[4];
extern int DAT_00587110[4];
extern int DAT_00587738[4];
extern int DAT_005877b0[4];
extern unsigned char GPR_00554c14;
extern unsigned char GPR_00554e30;
extern unsigned char GPR_00554e34;
extern unsigned char GPR_00554e38;
extern unsigned char GPR_00554e3c;
int Gap__igMovieManager__vfunc_25(igMovieManager *self, void *arg1);
}

/* matching construct: dummy virtual slots; vK() dispatches through the retail vtable offset 8 + 4*K */
class VC {
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
struct RC { int vt; int rc; };
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
template <class T> struct igSmartPointer { T *p; ~igSmartPointer() { T *o = p; if (o != 0) { o->rc = o->rc - 1; if ((o->rc & 0x7fffff) == 0) igObject_Destroy(o); } } };
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
struct MovieInfo { int vt; int rc; const char *name; int pad[3]; int mode; int pad2[10]; const char *codecName; int codec; };

#define REL(x) { RC *q = (x); if (q != 0) { q->rc = q->rc - 1; if (((unsigned long long)((long long)q->rc << 0x29) >> 0x29) == 0) igObject_Destroy(q); } }
#define ALLOC(a, self) { int base_ = igObject_GetAllocator(self); if (GPR_00554c14 != 0) { a = base_; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); } }

int Gap__igMovieManager__vfunc_25(igMovieManager *self, void *arg1) {
    int i;
    MovieInfo *movie;
    int a;
    if (arg1 != 0 && igObject_IsKindOf(arg1, DAT_005877b0[0]) != 0) { movie = (MovieInfo *)arg1; } else { movie = 0; }
    if (movie != 0) {
    const char *codecName = movie->codecName;
    if (codecName != 0) {
    ListHead *movies = (ListHead *)self->_movieList;
    if (movies != 0) {
        if (movies->indexOf((RC *)movie) != -1) return 0;
    }
    igSmartPointer<RC> codec;
    codec.p = 0;
    if (codec.p != 0) codec.p->rc = codec.p->rc + 1;
    if (self->_codecList != 0) {
        i = 0;
        if (0 < ((ListHead *)self->_codecList)->count) {
            do {
                RC *c = ((RC **)((ListHead *)self->_codecList)->data)[i];
                const char *n = (const char *)((int *)((VC *)c)->v20())[7];
                if (strcmp(n, codecName) == 0) {
                    if (c != 0) c->rc = c->rc + 1;
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
        if (created != 0 && igObject_IsKindOf(created, DAT_00587738[0]) != 0) { c = created; } else { c = 0; }
        if (c != 0) c->rc = c->rc + 1;
        REL(codec.p)
        codec.p = c;
        { RC *q = codec.p; q->rc = q->rc - 1; if (((unsigned long long)((long long)q->rc << 0x29) >> 0x29) == 0) igObject_Destroy(q); }
        if (((VC *)codec.p)->v21() != 0) {
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
        if (c != 0) c->rc = c->rc + 1;
        REL((RC *)movie->codec)
        movie->codec = (int)c;
    }
    if (self->_audioDisabled == 0 && self->_audio == 0) {
        ALLOC(a, self);
        REL((RC *)self->_audio)
        self->_audio = (int)FUN_00142f30(a);
        ((VC *)self->_audio)->v24(((int *)self->_insight)[5]);
        ((VS *)self->_audio)->s22();
    }
    {
        RC *held = codec.p;
        ((VC *)held)->v22(((VC *)((int *)self->_insight)[5])->v36(), self->_audio);
    }
    if (((VC *)codec.p)->v23(movie) != 0) {
        if (movie->mode == 2 || ((VC *)self)->v29(movie) != 0) {
            if (((VC *)codec.p)->v25(movie) == 0) {
                if (GPR_00554e34 == 0) {
                    const char *nm = movie->name;
                    const char *shown;
                    if (nm != 0) { shown = nm; } else { shown = (const char *)&DAT_004e0858[0]; }
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
            FUN_00236be0(self->_insight, self);
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
            if (nm != 0) { shown = nm; } else { shown = (const char *)&DAT_004e0858[0]; }
            int r = FUN_00308320(&DAT_00501140[0], shown);
            if (r != 1) { if (r == 2) GPR_00554e38 = 1; }
        }
        return 0;
    }
    if (GPR_00554e3c == 0) {
        const char *nm = movie->name;
        const char *shown;
        if (nm != 0) { shown = nm; } else { shown = (const char *)&DAT_004e0858[0]; }
        int r = FUN_00308320(&DAT_00501170[0], shown);
        if (r != 1) { if (r == 2) GPR_00554e3c = 1; }
    }
    return 0;
    }
    }
    return 0;
}
