#include "dw4/reflected.h"
struct R { int v; R() {} };
class Ctx;
extern "C" {
int strstr(...);
void *FUN_002c5780(...);
int FUN_002dcc40(...);
int igObject_Destroy(...);
extern int DAT_004fa530[4];
extern int DAT_004fa550[4];
void MemoryContext_BuildAndAttachEventTracker(struct R *arg0, class Ctx *arg1, int arg2);
}

class Trk { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void v360(void *); };
class Evt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void *v356(); };
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void v92(); int rc; };
class Ctx { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual Evt *v92(int); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual R v204(int, int); int p4; int p8; int flags; };
struct Gl { char p[124]; void *f124; };
extern "C" { extern Gl *DAT_00586dc8[4]; }
struct Slot { char p[20]; Trk *trk; char q[128]; igMemoryPoolInfo *sub; };
#define RC(o) ((unsigned long long)(long long)((igObject *)(o))->_refCount & 0x7fffffULL)
void MemoryContext_BuildAndAttachEventTracker(R *out, Ctx *self, int idx) {
    void *ty;
    Trk *trk;
    Obj *o2;
    igMemoryPoolInfo **ps2;
    Obj *o;
    int tv;
    igMemoryPoolInfo **ps;
    R t = self->v204(idx, 1); tv = t.v;
    int off = idx * 0x90; Slot *slot = (Slot *)(off + (int)self);
    trk = slot->trk;
    /* +12 of the context is igInfo::_directory in reflection but is read here as a flag word. The second flag test below stays on Ctx::flags: typing both makes MWCC hoist the member address into a saved register. */
    int h1 = (((igMemoryPoolContextInfo *)self)->_directory & 1) != 0;
    if (h1) {
        ty = 0;
        ps = &slot->sub; igMemoryPoolInfo *sub = *ps;
        if (sub != 0) ty = (void *)sub->_releaseOptions;
        if (ty == 0 || strstr(ty, &DAT_004fa530[0]) == 0) {
            int h2 = (self->flags & 2) != 0;
            if ((h2 && idx != 1) || (ty != 0 && strstr(ty, &DAT_004fa550[0]) != 0)) {
                o = (Obj *)FUN_002c5780(self->v92(3));
                void *b = DAT_00586dc8[0]->f124;
                void *f = (void *)(*ps)->_eventTrackerCapacity;
                if (f != 0) b = f;
                FUN_002dcc40(o, b);
                o->v92();
                trk->v360(o);
                ((igObject *)o)->_refCount = ((igObject *)o)->_refCount - 1;
                if (RC(o) == 0) igObject_Destroy(o);
            } else {
                void *x = self->v92(1)->v356();
                if (x != 0) trk->v360(x);
            }
        }
    } else {
        void *ty2 = 0;
        ps2 = &slot->sub; igMemoryPoolInfo *sub2 = *ps2;
        if (sub2 != 0) ty2 = (void *)sub2->_releaseOptions;
        if (ty2 != 0 && strstr(ty2, &DAT_004fa550[0]) != 0) {
            o2 = (Obj *)FUN_002c5780(self->v92(3));
            void *b2 = DAT_00586dc8[0]->f124;
            void *f2 = (void *)(*ps2)->_eventTrackerCapacity;
            if (f2 != 0) b2 = f2;
            FUN_002dcc40(o2, b2);
            o2->v92();
            trk->v360(o2);
            ((igObject *)o2)->_refCount = ((igObject *)o2)->_refCount - 1;
            if (RC(o2) == 0) igObject_Destroy(o2);
        }
    }
    out->v = tv;
}
