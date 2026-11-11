#include "dw4/reflected.h"
class R {
public:
    int v;
    R(const R &o) : v(o.v) {}
    bool operator==(const R &o) const { return v == o.v; }
};
extern "C" {
void *FUN_002c4ca0(int);
int FUN_002e30b0(void *, const char *);
int FUN_002eb010(int);
int FUN_00304430(...);
int FUN_00304680(...);
int StringChunk_ReleaseHeader(int, void *);
int StringPool_Construct(int);
int StringPool_Intern(int, void *);
int igObject_Destroy(void *);
int igObject_GetAllocator(void *);
int igObject_AllocateStorage(...);
int memset(...);
extern R DAT_004fb410;
extern R DAT_004fb418;
extern int g_allocatorFailureStatus[4];
extern int DAT_004fdda0[4];
extern int DAT_004ff4f0[4];
extern int DAT_004ff510[4];
extern int DAT_004ff540[4];
extern int DAT_00586f20[4];

typedef struct T { int word0; int references; } T;
void Gap__Core__igProgramFile__vfunc_23(igProgramFile *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    char *temp_a0;
    T *temp_a0_2;
    char *temp_s1;

    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s1 = (char *)StringPool_Intern(DAT_00586f20[0], 0);
    temp_a0 = (char *)arg0->_fileName;
    if (temp_a0 != 0) {
        temp_a1 = (int *)(temp_a0 - 8);
        temp_v1 = *(int *)(temp_a0 - 4) - 1;
        *(int *)(temp_a0 - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_fileName = (int)temp_s1;
    temp_a0_2 = (T *)arg0->_file;
    if (temp_a0_2 != 0) {
        --temp_a0_2->references;
        if (((unsigned long long)(long long)temp_a0_2->references & 0x7fffffULL) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    arg0->_file = 0;
}

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
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    tok = StringPool_Intern(DAT_00586f20[0], arg2);
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
    p->f12 = (Rc *)FUN_002c4ca0(s0);
    FUN_002e30b0(p->f12, p->f8);
    if (((VB *)p->f12)->vX(4) == DAT_004fb418) {
        FUN_00304430(&DAT_004ff4f0[0], (int)p->f8);
        FUN_00304680();
        return DAT_004fb418;
    }
    return DAT_004fb410;
}

class DW4VC_92_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); };
class DW4VC_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
void Gap__Core__igProgramFile__vfunc_25(int *arg0, void *arg1) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg1) + 12));
    ((DW4VC_96_0 *)(temp_a0))->vX();
    ((DW4VC_92_0 *)(((char *)(arg1) + 0)))->vX();
    *arg0 = DAT_004fb410.v;
}

struct SR4 { int w0; };
class Strm { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v27(int, int, int); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int v38(int, int); };
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual SR4 v25(); };
struct OF { int vt; int p4; int f8; Strm *f12; };
void Gap__Core__igProgramFile__vfunc_26(int *arg0, OF *arg1, int arg2, int arg3, int *arg4) {
    SR4 sp6C;
    SR4 sp68;
    SR4 sp64;
    Strm *s;
    s = arg1->f12;
    if (s->v38(arg2, 0) == -1) {
        FUN_00304430(&DAT_004ff510[0], arg2, arg1->f8);
        FUN_00304680();
        sp6C = ((Obj *)arg1)->v25();
        *arg0 = DAT_004fb418.v;
        return;
    }
    if (*arg4 == 0) {
        *arg4 = igObject_AllocateStorage(arg1, arg3);
        if (*arg4 == 0) {
            FUN_00304430(&DAT_004ff540[0], arg3, arg1->f8);
            FUN_00304680();
            sp68 = ((Obj *)arg1)->v25();
            *arg0 = DAT_004fb418.v;
            return;
        }
    }
    memset(*arg4, 0, arg3);
    s = arg1->f12;
    if (s->v27(*arg4, arg3, 1) != 1) {
        FUN_00304430(&DAT_004fdda0[0], arg1->f8);
        FUN_00304680();
        sp64 = ((Obj *)arg1)->v25();
        *arg0 = DAT_004fb418.v;
        return;
    }
    *arg0 = DAT_004fb410.v;
}

/* igProgramFile vtable slot 27: status leaf. Ignores the object and writes the engine's current
 * failure-status word (the one an allocation failure publishes) through the output-first argument;
 * the same leaf as igPsx2Window slot 40. */
void Gap__Core__igProgramFile__vfunc_27(int *status_out) {
    *status_out = g_allocatorFailureStatus[0];
}

/* igProgramFile vtable slot 28: status leaf, the same body as slot 27. */
void Gap__Core__igProgramFile__vfunc_28(int *status_out) {
    *status_out = g_allocatorFailureStatus[0];
}

/* igProgramFile vtable slot 29: status leaf, the same body as slot 27. */
void Gap__Core__igProgramFile__vfunc_29(int *status_out) {
    *status_out = g_allocatorFailureStatus[0];
}

void Gap__Core__igProgramFile__vfunc_30(igProgramFile *self) {
}

void Gap__Core__igProgramFile__vfunc_31(igProgramFile *self) {
}

void Gap__Core__igProgramFile__vfunc_32(igProgramFile *self) {
}
}
