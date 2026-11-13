#include "dw4/igSmartPointer.h"
struct Obj : public igObject { };
struct Res : public igObject {
    char p0[12]; int *f20; char p1[8]; void *f32; unsigned char f36; char p2[11]; unsigned char f48; unsigned char f49;
    char p3[15]; unsigned char f65; char p4[98]; int f164; char p5[109]; unsigned char f277; char p6[2]; Obj *f280; Obj *f284; Obj *f288;
};
struct W {
    int w0; int w4; unsigned char f8; char p1[19]; unsigned char f28; char p2[23]; unsigned char f52; char p3[3];
    Obj *f56; Obj *f60; Obj *f64; unsigned char f68; char p4[3]; int f72;
};
extern "C" {
int FUN_002d9130(void *);
void *FUN_002c37e0(void *);
int FUN_00308850(W *, void *);
void *FUN_00309640(W *, void *);
void *igObject_GetAllocator(W *);
int StringPool_Allocate(int);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_00586f20[4];
}

extern "C" igSmartPointer<Obj> FUN_003087a0(W *, int);
extern "C" void *FUN_00308fb0(W *arg0, int arg1) {
    Res *r;
    Obj *a;
    int *old;
    int pool;
    void *res;

    r = (Res *)FUN_003087a0(arg0, arg1).p;
    if (r != 0) {
        FUN_002d9130(r);
        return r;
    }
    igSmartPointer<Res> created((Res *)FUN_002c37e0(arg0->f56 != 0 ? (void *)arg0->f56 : igObject_GetAllocator(arg0)));
    created.get()->f36 = arg0->f68;
    created.get()->f164 = arg0->f72;
    created.get()->f65 = arg0->f8;
    a = arg0->f56 != 0 ? arg0->f56 : (Obj *)igObject_GetAllocator(arg0);
    r = created.get();
    if (a != 0) a->_refCount = a->_refCount + 1;
    {
        Obj *o = r->f280;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
    r->f280 = a;
    a = arg0->f60 != 0 ? arg0->f60 : (Obj *)igObject_GetAllocator(arg0);
    r = created.get();
    if (a != 0) a->_refCount = a->_refCount + 1;
    {
        Obj *o = r->f284;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
    r->f284 = a;
    a = arg0->f64 != 0 ? arg0->f64 : (Obj *)igObject_GetAllocator(arg0);
    r = created.get();
    if (a != 0) a->_refCount = a->_refCount + 1;
    {
        Obj *o = r->f288;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
    r->f288 = a;
    if (arg0->f28 == 1) {
        created.get()->f277 = arg0->f52;
    }
    created.get()->f49 = 0;
    created.get()->f48 = 1;
    r = created.get();
    if (DAT_00586f20[0] == 0) {
        pool = StringPool_Allocate(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    pool = StringPool_Intern(DAT_00586f20[0], arg1);
    old = r->f20;
    if (old != 0) {
        int *hd = old - 2;
        int c = old[-1] - 1;
        old[-1] = c;
        if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    r->f20 = (int *)pool;
    created.get()->f32 = arg0;
    FUN_002d9130(created.get());
    FUN_00308850(arg0, created.get());
    return FUN_00309640(arg0, created.get());
}
