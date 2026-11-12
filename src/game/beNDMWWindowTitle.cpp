#include "dw4/reflected.h"
#define ENSURE_POOL() if (((int *)g_stringPool)[0] == 0) { v = ((int)FUN_002eb010(0x10)); if (v != 0) { v = ((int)StringPool_Construct(v)); } ((int *)g_stringPool)[0] = v; }
#define INTERN_APPEND(field, text) { \
    const char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (g_stringPool[0] == 0) { \
            void *pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            g_stringPool[0] = pool; \
        } \
        tok = StringPool_Intern(g_stringPool[0], (const char *)(text)); \
    } \
    StringRef held((int *)tok); \
    StringList_AppendRetained(field, &held); }

extern "C" int beNDMWWindow_ClearQueuedText(...);
extern "C" int beNDMWWindow_PlayQueuedModelClose(...);
extern "C" int beNDMWWindow_PollCloseComplete(...);
extern "C" int beNDMWWindow_RequestChildrenClose(...);
extern "C" int beNDMWWindow_PresentModelAtOrigin(...);
extern "C" void Gap__Bec__beNDMWStatusTitle00__vfunc_22(int *arg0);
extern "C" void * FUN_002eb010(...);
extern "C" void StringChunk_ReleaseHeader(int, int *);
extern "C" void * StringPool_Construct(...);
extern "C" const char * StringPool_Intern(...);
extern "C" void beMessenger_AppendInt(int, int);
extern "C" void beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetObject(int, int);
extern "C" void beMessenger_SelectGroup(...);
extern "C" void *igProperty_GetRecord(int, int *);
extern "C" int beMessenger_AppendString(...);
extern "C" void FUN_00425e60(int *arg0);
extern "C" void Gap__Bec__beNDMWStatusTitle02__vfunc_22(int p0, char * p1, int p2, char * p3, char * p4);
extern "C" int beNDMWWindow_RunMessageScript(void *, int *, int);
extern "C" int Gap__Bec__beNDMWStatusTitle04__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWStatusTitle03__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWStatusTitle02__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWStatusTitle01__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWStatusTitle00__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWWindowTitle__vfunc_20(void);
class DW4VC_96 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
extern "C" void Gap__Bec__beNDMWWindowTitle__vfunc_21(beNDMWWindowTitle *arg0);
extern "C" int DAT_0051abf8[4];
extern "C" int DAT_0051ac08[4];
extern "C" int DAT_0051ac10[4];
extern "C" int DAT_0051ac20[4];
extern "C" int beNDMWWindow_PresentModel(beNDMWWindow *, int *, int, int *, int *, float *);
extern "C" int DAT_0051ad70[4];
extern "C" int DAT_0051ad78[4];
extern "C" int DAT_0051ad80[4];
extern "C" int DAT_0051ad88[4];
extern "C" int DAT_0051ad98[4];
extern "C" int DAT_0051aec0[4];
extern "C" int DAT_0051ada8[4];
extern "C" int DAT_0051adb8[4];
extern "C" int DAT_0051adc8[4];
extern "C" int DAT_0051add8[4];
extern "C" int DAT_0051adf0[4];
extern "C" int DAT_0051ae00[4];
extern "C" int DAT_0051ae10[4];
extern "C" int DAT_0051ae20[4];
extern "C" int DAT_0051ae30[4];
extern "C" int DAT_0051ae40[4];
extern "C" int DAT_0051ae50[4];
extern "C" int DAT_0051ae60[4];
extern "C" int DAT_0051ae70[4];
extern "C" int DAT_0051ae80[4];
extern "C" int DAT_0051aea0[4];
extern "C" int DAT_0051aeb0[4];
extern "C" void *g_stringPool[4];
struct Rec { char pad[12]; unsigned int sel; };
/* Creates the shared string pool on first use; open-coded in the two clear loops because the
 * inline Str::intern there would change their register allocation. */

struct Str {
    static inline int *intern(const char *s) {
        if (((int *)g_stringPool)[0] == 0) {
            int v = ((int)FUN_002eb010(0x10));
            if (v != 0) v = ((int)StringPool_Construct(v));
            ((int *)g_stringPool)[0] = v;
        }
        return (int *)StringPool_Intern(((int *)g_stringPool)[0], s);
    }
    static inline void release(int *p) {
        if (p != 0) {
            int *header = p - 2;
            int r = p[-1] - 1;
            p[-1] = r;
            if (r == 0) StringChunk_ReleaseHeader(*header, header);
        }
    }
};
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]): releases the token on scope exit; set() drops the held token for a new one. */
class StringRef {
public:
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
    void set(int *t) { int *cur = p; Str::release(cur); p = t; }
};
extern "C" void FUN_00425430(beNDMWWindow *arg0);
typedef struct Tbl { const char *s[29]; } Tbl;
extern "C" Tbl DAT_004cf7a0;
extern "C" char DAT_0051ac30[];
extern "C" char DAT_0051acc8[];
extern "C" int DAT_0051ace0[4];
extern "C" char DAT_0051af10[];
extern "C" char DAT_0051af20[];
extern "C" int DAT_0051af30[4];
extern "C" char DAT_0051af38[];
extern "C" char DAT_0051af40[];
typedef struct Tb { int p[29]; } Tb;
extern "C" Tb DAT_004cf820;
extern "C" int DAT_0051af48[4];
extern "C" int DAT_0051af58[4];
typedef struct W { int p0, p1, p2, f12, p4, f20; } W;
extern "C" void FUN_00425fb0(W *arg0);
extern "C" char DAT_0051af60[];
extern "C" char DAT_0051af70[];
extern "C" char DAT_0051af80[];
extern "C" int DAT_0051af90[4];
extern "C" int DAT_0051acb0[4];
extern "C" int DAT_0051ad60[4];
extern "C" int StringList_AppendRetained(int, StringRef *);
struct Sh { char p[44]; unsigned f44; char q[12]; int f60; int f64; };
extern "C" int DAT_0051afa0[4];
extern "C" int DAT_0051afb0[4];
extern "C" void Gap__Bec__beNDMWStatusTitle03__vfunc_22(Sh *arg0);
extern "C" int DAT_0051afb8[4];
extern "C" int DAT_0051afc8[4];
extern "C" void FUN_00426530(beNDMWStatusTitle03 *arg0, int arg1);
extern "C" int DAT_0051afd8[4];
extern "C" int DAT_0051afe8[4];
extern "C" void Gap__Bec__beNDMWStatusTitle04__vfunc_22(Sh *arg0);
extern "C" int g_beNDMWStatusTitle04_metaObject[4];
extern "C" int g_beNDMWStatusTitle03_metaObject[4];
extern "C" int g_beNDMWStatusTitle02_metaObject[4];
extern "C" int g_beNDMWStatusTitle01_metaObject[4];
extern "C" int g_beNDMWStatusTitle00_metaObject[4];
extern "C" int g_beNDMWWindowTitle_metaObject[4];

void Gap__Bec__beNDMWWindowTitle__vfunc_21(beNDMWWindowTitle *arg0) {
    switch (arg0->_st0) {
    case 0:
        ((DW4VC_96 *)(arg0))->vX();
        arg0->_st0 = (int)((int) (arg0->_st0 + 1));
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = (int)((int) (arg0->_st0 + 1));
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}

void Gap__Bec__beNDMWStatusTitle00__vfunc_22(int *arg0) {
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051abf8[0], 0, &DAT_0051ac08[0], &DAT_0051ac10[0]);
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051ac20[0], 0, &DAT_0051ac08[0], &DAT_0051ac10[0]);
}

void FUN_00425430(beNDMWWindow *arg0) {
    float sp80[3];
    igStringRefList *l1;
    igStringRefList *l3;
    int n1, n3, i3, v, off3;
    int *t, *a2;
    int i1;
    int **e1;
    int *a2b;
    int off1;
    int **e;
    unsigned int sel;
    int obj;

    beNDMWWindow_PlayQueuedModelClose(arg0);
    l1 = (igStringRefList *)arg0->_modelCloseInfoNameList;
    n1 = l1->_count;
    i1 = 0;
    if (i1 < n1) {
        off1 = 0;
        do {
            e1 = (int **)((char *)l1->_data + off1);
            ENSURE_POOL();
            a2b = (int *)StringPool_Intern(((int *)g_stringPool)[0], 0);
            t = *e1;
            Str::release(t);
            i1 += 1;
            *e1 = a2b;
            off1 += 4;
        } while (i1 < n1);
    }
    l1->_count = 0;
    ((igIntList *)arg0->_modelCloseRamNoList)->_count = 0;
    l3 = (igStringRefList *)arg0->_modelCloseSeqNameList;
    n3 = l3->_count;
    i3 = 0;
    if (i3 < n3) {
        off3 = 0;
        do {
            e = (int **)((char *)l3->_data + off3);
            ENSURE_POOL();
            a2 = (int *)StringPool_Intern(((int *)g_stringPool)[0], 0);
            t = *e;
            Str::release(t);
            i3 += 1;
            *e = a2;
            off3 += 4;
        } while (i3 < n3);
    }
    l3->_count = 0;
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051ad70[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051ad78[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051ad80[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051ad88[0]);
    obj = beMessenger_GetObject(arg0->_messenger, 0);
    {
        StringRef modelName(0);
        sel = ((struct Rec *)igProperty_GetRecord(obj, &DAT_0051ad98[0]))->sel;
        switch (sel) {
        default: modelName.set(Str::intern((const char *)&DAT_0051ada8[0])); break;
        case 1:  modelName.set(Str::intern((const char *)&DAT_0051adb8[0])); break;
        case 2:  modelName.set(Str::intern((const char *)&DAT_0051adc8[0])); break;
        case 3:  modelName.set(Str::intern((const char *)&DAT_0051add8[0])); break;
        case 4:  modelName.set(Str::intern((const char *)&DAT_0051adf0[0])); break;
        case 5:  modelName.set(Str::intern((const char *)&DAT_0051ae00[0])); break;
        case 6:  modelName.set(Str::intern((const char *)&DAT_0051ae10[0])); break;
        case 7:  modelName.set(Str::intern((const char *)&DAT_0051ae20[0])); break;
        case 8:  modelName.set(Str::intern((const char *)&DAT_0051ae30[0])); break;
        case 9:  modelName.set(Str::intern((const char *)&DAT_0051ae40[0])); break;
        case 10: modelName.set(Str::intern((const char *)&DAT_0051ae50[0])); break;
        case 11: modelName.set(Str::intern((const char *)&DAT_0051ae60[0])); break;
        case 12: modelName.set(Str::intern((const char *)&DAT_0051ae70[0])); break;
        case 13: modelName.set(Str::intern((const char *)&DAT_0051ae80[0])); break;
        case 14: modelName.set(Str::intern((const char *)&DAT_0051aea0[0])); break;
        case 15: modelName.set(Str::intern((const char *)&DAT_0051aeb0[0])); break;
        }
        sp80[2] = 0.0f;
        sp80[0] = -410.0f;
        sp80[1] = 240.0f;
        beNDMWWindow_PresentModel(arg0, &DAT_0051aec0[0], arg0->_playerNo, modelName.p, &DAT_0051ac10[0], &sp80[0]);
    }
}

void FUN_00425e60(int *arg0) {
    Tbl sp30;
    const char **p;
    FUN_00425430((beNDMWWindow *)arg0);
    beNDMWWindow_PresentModelAtOrigin(arg0, DAT_0051af10, arg0[5], DAT_0051af20, ((char *)DAT_0051ac10));
    sp30 = DAT_004cf7a0;
    p = sp30.s;
    if (*p != 0) {
        do {
            beMessenger_SelectGroup(arg0[3], ((char *)DAT_0051af30));
            beMessenger_AppendString(arg0[3], DAT_0051ac30);
            beMessenger_AppendString(arg0[3], *p);
            beMessenger_AppendString(arg0[3], DAT_0051af38);
            beMessenger_DispatchSelected(arg0[3], DAT_0051af40);
            p++;
        } while (*p != 0);
    }
    beMessenger_SelectGroup(arg0[3], ((char *)DAT_0051af30));
    beMessenger_AppendString(arg0[3], DAT_0051acc8);
    beMessenger_AppendString(arg0[3], ((char *)DAT_0051ace0));
    beMessenger_AppendString(arg0[3], DAT_0051af38);
    beMessenger_DispatchSelected(arg0[3], DAT_0051af40);
}

void FUN_00425fb0(W *arg0) {
    Tb sp30;
    int *s1;
    FUN_00425430((beNDMWWindow *)arg0);
    beNDMWWindow_PresentModelAtOrigin((int *)arg0, DAT_0051af48, arg0->f20, DAT_0051ac08, DAT_0051ac10);
    sp30 = DAT_004cf820;
    s1 = sp30.p;
    if (sp30.p[0] != 0) {
        do {
            beMessenger_SelectGroup(arg0->f12, DAT_0051af30);
            beMessenger_AppendString(arg0->f12, ((int *)DAT_0051ac30));
            beMessenger_AppendString(arg0->f12, (void *)*s1);
            beMessenger_AppendString(arg0->f12, DAT_0051af58);
            beMessenger_DispatchSelected(arg0->f12, ((int *)DAT_0051af40));
            s1 += 1;
        } while (*s1 != 0);
    }
    beMessenger_SelectGroup(arg0->f12, DAT_0051af30);
    beMessenger_AppendString(arg0->f12, ((int *)DAT_0051acc8));
    beMessenger_AppendString(arg0->f12, DAT_0051ace0);
    beMessenger_AppendString(arg0->f12, DAT_0051af58);
    beMessenger_DispatchSelected(arg0->f12, ((int *)DAT_0051af40));
}

void Gap__Bec__beNDMWStatusTitle02__vfunc_22(int p0, char * p1, int p2, char * p3, char * p4)
{
    beNDMWWindow_PresentModelAtOrigin(p0, DAT_0051af60, 0, DAT_0051af70, DAT_0051af80);
}

void Gap__Bec__beNDMWStatusTitle03__vfunc_22(Sh *arg0) {
    beNDMWWindow_PresentModelAtOrigin(arg0, DAT_0051af90, 0, DAT_0051ac08, DAT_0051ac10);
    INTERN_APPEND(arg0->f60, DAT_0051afa0)
    INTERN_APPEND(arg0->f64, DAT_0051acb0)
    INTERN_APPEND(arg0->f60, DAT_0051afa0)
    INTERN_APPEND(arg0->f64, DAT_0051ace0)
    INTERN_APPEND(arg0->f60, DAT_0051afa0)
    INTERN_APPEND(arg0->f64, DAT_0051afb0)
    beNDMWWindow_RunMessageScript(arg0, DAT_0051ad60, 0);
}

void FUN_00426530(beNDMWStatusTitle03 *arg0, int arg1) {
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051af30[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051afa0[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051afb0[0]);
    if (arg1 != 0) {
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051afb8[0]);
        return;
    }
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051afc8[0]);
}

void Gap__Bec__beNDMWStatusTitle04__vfunc_22(Sh *arg0) {
    beNDMWWindow_PresentModelAtOrigin(arg0, DAT_0051afd8, 0, DAT_0051ac08, DAT_0051ac10);
    INTERN_APPEND(arg0->f60, DAT_0051afe8)
    INTERN_APPEND(arg0->f64, DAT_0051acb0)
    beNDMWWindow_RunMessageScript(arg0, DAT_0051ad60, arg0->f44);
}

int Gap__Bec__beNDMWStatusTitle04__vfunc_20(void)
{
    return g_beNDMWStatusTitle04_metaObject[0];
}

int Gap__Bec__beNDMWStatusTitle03__vfunc_20(void)
{
    return g_beNDMWStatusTitle03_metaObject[0];
}

int Gap__Bec__beNDMWStatusTitle02__vfunc_20(void)
{
    return g_beNDMWStatusTitle02_metaObject[0];
}

int Gap__Bec__beNDMWStatusTitle01__vfunc_20(void)
{
    return g_beNDMWStatusTitle01_metaObject[0];
}

int Gap__Bec__beNDMWStatusTitle00__vfunc_20(void)
{
    return g_beNDMWStatusTitle00_metaObject[0];
}

int Gap__Bec__beNDMWWindowTitle__vfunc_20(void)
{
    return g_beNDMWWindowTitle_metaObject[0];
}

