#include "dw4/reflected.h"
class R {
public:
    int v;
    R(const R &o) : v(o.v) {}
    bool operator==(const R &o) const { return v == o.v; }
};
extern "C" {
void *igFile_Create(int);
int FUN_002e30b0(void *, const char *);
int StringPool_Allocate(int);
int FUN_00304430(...);
int FUN_00304680(...);
int StringChunk_ReleaseHeader(int, void *);
int StringPool_Construct(int);
int StringPool_Intern(int, void *);
int igObject_Destroy(void *);
int igObject_GetAllocator(void *);
int igObject_AllocateStorage(...);
int memset(...);
extern R g_statusSucceeded;
extern R g_allocatorFailureStatus;
extern int DAT_004fdda0[4];
extern int DAT_004ff4f0[4];
extern int DAT_004ff510[4];
extern int DAT_004ff540[4];
extern int g_stringPool[4];

typedef struct T { int word0; int references; } T;
void Gap__Core__igProgramFile__vfunc_23(igProgramFile *arg0);

class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual R vX(int); };
struct Rc { int w0; int refs; };
struct PF { char pad[8]; const char *f8; Rc *f12; };
R Gap__Core__igProgramFile__vfunc_24(void *arg1, void *arg2) {
    PF *p = (PF *)arg1;
    int var_v0;
    int s0;
    int *old;
    int *hdr;
    int tok;
    Rc *r;
    int temp_v0;
    ((VA *)arg1)->vX();
    if (g_stringPool[0] == 0) {
        var_v0 = StringPool_Allocate(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        g_stringPool[0] = var_v0;
    }
    tok = StringPool_Intern(g_stringPool[0], arg2);
    old = (int *)p->f8;
    if (old != 0) {
        hdr = old - 2;
        temp_v0 = old[-1] - 1;
        old[-1] = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*hdr, hdr);
        }
    }
    p->f8 = (const char *)tok;
    s0 = igObject_GetAllocator(arg1);
    r = p->f12;
    if (r != 0) {
        r->refs = r->refs - 1;
        if (((unsigned long long)(long long)r->refs & 0x7fffffULL) == 0) {
            igObject_Destroy(r);
        }
    }
    p->f12 = (Rc *)igFile_Create(s0);
    FUN_002e30b0(p->f12, p->f8);
    if (((VB *)p->f12)->vX(4) == g_allocatorFailureStatus) {
        FUN_00304430(&DAT_004ff4f0[0], (int)p->f8);
        FUN_00304680();
        return g_allocatorFailureStatus;
    }
    return g_statusSucceeded;
}

class DW4VC_92_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); };
class DW4VC_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
void Gap__Core__igProgramFile__vfunc_25(int *arg0, void *arg1);

struct SR4 { int w0; };
class Strm { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v27(int, int, int); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int v38(int, int); };
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual SR4 v25(); };
struct OF { int vt; int p4; int f8; Strm *f12; };
void Gap__Core__igProgramFile__vfunc_26(int *arg0, OF *arg1, int arg2, int arg3, int *arg4);

/* igProgramFile vtable slot 27: status leaf. Ignores the object and writes the engine's current
 * failure-status word (the one an allocation failure publishes) through the output-first argument;
 * the same leaf as igPsx2Window slot 40. */
void Gap__Core__igProgramFile__vfunc_27(int *status_out);

/* igProgramFile vtable slot 28: status leaf, the same body as slot 27. */
void Gap__Core__igProgramFile__vfunc_28(int *status_out);

/* igProgramFile vtable slot 29: status leaf, the same body as slot 27. */
void Gap__Core__igProgramFile__vfunc_29(int *status_out);

void Gap__Core__igProgramFile__vfunc_30(igProgramFile *self);

void Gap__Core__igProgramFile__vfunc_31(igProgramFile *self);

void Gap__Core__igProgramFile__vfunc_32(igProgramFile *self);
}
