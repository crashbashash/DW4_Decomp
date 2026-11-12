#include "dw4/reflected.h"

extern "C" int Memory_AllocateBufferDirect(int, int);
extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" int igObject_GetAllocator(...);
extern "C" void FUN_003a9810(void *arg0, int arg1);
extern "C" int Memory_FreeBufferWithAllocator(int, int);
extern "C" int memset(void *, int, int);
extern "C" int FUN_002ed2b0(int, int, int);
extern "C" int igMetaObject_CountInstances(...);
extern "C" void Gap__Bec__beSaveMemoryObj__vfunc_08(void **arg0);
extern "C" int Gap__Bec__beSaveMemoryObj__vfunc_20(void);
extern "C" int FUN_0011a500(int, int);
extern "C" int FUN_00119ff0(...);
extern "C" int sprintf(char *, const char *, ...);
extern "C" int FUN_001198a8(int, int, char *, int);
extern "C" int FUN_00119a08(int);
extern "C" int FUN_00119ac8(int, int, int);
extern "C" int FUN_00119d58(int, int, int);
extern "C" int FUN_0011a6f0(int);
extern "C" int FUN_001194c0(...);
extern "C" int FUN_0032cf50(int *, int *, int, int, int);
extern "C" int sceMtapGetConnection(int);
extern "C" int sceMtapPortOpen(int);
extern "C" int sceMtapPortClose(int);
extern "C" int sceMcSync(...);
extern "C" int FUN_003ad7a0(int arg0, int arg1);
extern "C" int FUN_003ad850(int port, int onlyPresent);
extern "C" void FUN_003ad950(int arg0, void *arg1);
extern "C" void Gap__Bec__beSvConnectCheck__vfunc_21(void);
extern "C" int Gap__Bec__beSvConnectCheck__vfunc_22(void);
extern "C" void Gap__Bec__beSvConnectCheck__vfunc_23(void);
extern "C" int Gap__Bec__beSvConnectCheck__vfunc_20(void);
extern "C" int Gap__Core__igObject__vfunc_07(...);
extern "C" void Gap__Bec__beSvConnectCheck__vfunc_07(void **arg0);
extern "C" int Gap__Bec__beSaveApi__vfunc_20(void);
extern "C" void Gap__Core__igObject__vfunc_08__002ff0f0(...);
extern "C" void Gap__Bec__beSvConnectCheck__vfunc_08(void);
extern "C" int Gap__Bec__beSvEndApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvEndApi__vfunc_07(void **arg0);
extern "C" void Gap__Bec__beSvEndApi__vfunc_08(void);
extern "C" int Gap__Bec__beSvStartApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvStartApi__vfunc_07(void **arg0);
extern "C" void Gap__Bec__beSvStartApi__vfunc_08(void);
extern "C" int Gap__Bec__beSvGetFreeSizeApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvGetFreeSizeApi__vfunc_07(void **arg0);
extern "C" void Gap__Bec__beSvGetFreeSizeApi__vfunc_08(void);
extern "C" int Gap__Bec__beSvWriteMediaApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvWriteMediaApi__vfunc_07(void **arg0);
extern "C" int igObject_Destroy(...);
extern "C" int Gap__Bec__beSvReadMediaApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvReadMediaApi__vfunc_07(void **arg0);
extern "C" int Gap__Bec__beSvUseCheckApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvUseCheckApi__vfunc_08(void);
extern "C" void FUN_003ae4a0(void **arg0);
extern "C" int Gap__Bec__beSvFormatApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvFormatApi__vfunc_08(void);
extern "C" int Gap__Bec__beSvFileFindApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvFileFindApi__vfunc_08(void);
extern "C" int Gap__Bec__beSvFileMakeApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvFileMakeApi__vfunc_07(void **arg0);
extern "C" void Gap__Bec__beSaveApi__vfunc_08(void);
extern "C" void Gap__Bec__beSaveMemoryObj__vfunc_07(void **arg0);
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
struct S { char pad[8]; int f8; int fc; };
extern "C" void FUN_003a9870(struct S *arg0);
struct O {
    char pad[8];
    void *buf;
};
extern "C" void FUN_003a98d0(struct O *arg0, int arg1, int arg2);
struct S_3a9990 { int pad[2]; int f8; };
extern "C" void FUN_003a9990(struct S_3a9990 *arg0);
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" int g_beSaveMemoryObj_metaObject[4];
extern "C" void Gap__Bec__beSvFileMakeApi__vfunc_23(beSvFileMakeApi *arg0, beSvDeliver *arg1);
extern "C" char GPR_00554e60;
extern "C" void Gap__Bec__beSvFileFindApi__vfunc_21(beSvFileFindApi *arg0, beSvDeliver *arg1);
extern "C" void Gap__Bec__beSvFileFindApi__vfunc_23(beSvFileFindApi *arg0, beSvDeliver *arg1);
extern "C" void Gap__Bec__beSvFormatApi__vfunc_21(beSvFormatApi *arg0, void *arg1);
extern "C" int DAT_004c91b4[4];
extern "C" int DAT_0058a870[4];
extern "C" int DAT_0058a8d0[4];
extern "C" unsigned char GPR_00554e64;
extern "C" unsigned char Gap__Bec__beSvFormatApi__vfunc_22(beSvFormatApi *arg0);
extern "C" void Gap__Bec__beSvFormatApi__vfunc_23(beSvFormatApi *arg0, void *arg1);
extern "C" void Gap__Bec__beSvUseCheckApi__vfunc_21(beSvUseCheckApi *arg0, beSvDeliver *arg1);
extern "C" int DAT_0058a834[4];
extern "C" int DAT_0058a894[4];
typedef struct beSvUseCheckApiTail { char pad0[60]; int f60; int f64; char p68[4]; int f72; } beSvUseCheckApiTail;
extern "C" unsigned char Gap__Bec__beSvUseCheckApi__vfunc_22(beSvUseCheckApi *arg0);
extern "C" void Gap__Bec__beSvUseCheckApi__vfunc_23(beSvUseCheckApi *arg0, beSvDeliver *arg1);
extern "C" void Gap__Bec__beSvReadMediaApi__vfunc_23(beSvReadMediaApi *arg0, void *arg1);
/* Memory-card write state machine, polled once per frame by the save-data pipeline. _phase (_st0)
 * selects the phase and _step (_st1) the step inside it. Every phase runs three steps: 0 clears
 * the retry counter, 1 issues one asynchronous memory-card request and raises its in-flight flag,
 * 2 polls the flag (returning 0 while it is set) and reads the result code. A failed request is
 * retried up to three times, then the machine ends with _isEnd = 1 and _result = 3 for the card-
 * unusable codes (-2, -4, -5, ...) or 12 for anything else. Phases: 0 opens the save directory, 1
 * resets the image pass, 2 selects the image offset for the pass, 3 writes the save buffer and
 * flushes it, 4 commits and closes (_result = 2, saved). Returns 1 when already finished, 0 while
 * a request is pending, else _isEnd. getPhase and getStep are const because retail reloads the fields at
 * those uses; the retry test goes through a local because retail does not fold the comparison into
 * the branch. */
struct SvSaveWork;
typedef struct SvCardContext {
    char pad0[0x10];
    int dataSize;            /* +0x10 */
    char pad14[4];
    int volumeNumber;        /* +0x18 */
    char pad1c[0xa8];
    int imageOffsets[2];     /* +0xc4 */
} SvCardContext;
typedef struct SvSaveWork {
    char pad0[8];
    int buffer;              /* +8 */
} SvSaveWork;
/* beSvWriteMediaApi plus the two members the registered metadata does not list (+60 retry count,
 * +72 image pass). */
typedef struct beSvWriteMediaApiRun {
    int _vtable;
    unsigned int _refCount;
    int _dummyCount;
    int _orderType;
    unsigned char _isConAllChk;
    char _pad17[3];
    int _connect;
    int _result;
    unsigned char _isEnd;
    char _pad29[3];
    int _phase;             /* +32 (_st0) */
    int _step;              /* +36 (_st1) */
    int getPhase() const { return _phase; }
    int getStep() const { return _step; }
    int _st2;
    int _st3;
    int _imageWork;
    int _mountWork;
    int _iconWork;
    int _retryCount;         /* +60 */
    int _nowGamedata;
    SvSaveWork *_saveWork;   /* +68 */
    int _imagePass;          /* +72 */
} beSvWriteMediaApiRun;
struct CardSlot { int port; int slot; };
extern "C" SvCardContext *DAT_0058a600[4];
extern "C" CardSlot DAT_004c91b0[];
extern "C" char DAT_00510310[];
extern "C" int DAT_0058a808[4];
extern "C" int DAT_0058a838[4];
extern "C" int DAT_0058a83c[4];
extern "C" int DAT_0058a840[4];
extern "C" int DAT_0058a848[4];
extern "C" int DAT_0058a858[4];
extern "C" int DAT_0058a898[4];
extern "C" int DAT_0058a89c[4];
extern "C" int DAT_0058a8a0[4];
extern "C" int DAT_0058a8a8[4];
extern "C" int DAT_0058a8b8[4];
extern "C" int Gap__Bec__beSvWriteMediaApi__vfunc_22(beSvWriteMediaApiRun *self);
extern "C" void Gap__Bec__beSvWriteMediaApi__vfunc_23(beSvWriteMediaApi *arg0, void *arg1);
extern "C" void Gap__Bec__beSvGetFreeSizeApi__vfunc_21(beSvGetFreeSizeApi *arg0, void *arg1);
extern "C" unsigned char Gap__Bec__beSvGetFreeSizeApi__vfunc_22(beSvGetFreeSizeApi *arg0);
struct UnidentifiedFreeSizeGlobal { char pad[20]; unsigned int f20; };
struct beSvGetFreeSizeApiTail { char pad[84]; int f84; };
/* word past the reflected beSvGetFreeSizeApi layout */
struct UnidentifiedResultObject {  /* arg1; class not identified */
  char pad[24]; int f24; char pad2[4]; unsigned int f32; int f36; unsigned char b40; unsigned char b41; unsigned char b42; unsigned char b43; unsigned char b44; };
extern "C" void Gap__Bec__beSvGetFreeSizeApi__vfunc_23(beSvGetFreeSizeApi *arg0, UnidentifiedResultObject *arg1);
extern "C" int DAT_004c91a0[4];
extern "C" int DAT_00510428[4];
extern "C" int DAT_00510438[4];
extern "C" int DAT_0058a608[4];
extern "C" char GPR_005549dc;
extern "C" unsigned char GPR_00554e58;
extern "C" char GPR_00554e5c;
extern "C" void Gap__Bec__beSvStartApi__vfunc_21(beSvStartApi *arg0, void *arg1);
extern "C" int Gap__Bec__beSvStartApi__vfunc_22(beSvStartApi *arg0);
extern "C" void Gap__Bec__beSvStartApi__vfunc_23(beSvStartApi *arg0, void *arg1);
extern "C" void Gap__Bec__beSvEndApi__vfunc_21(beSvEndApi *arg0);
extern "C" int Gap__Bec__beSvEndApi__vfunc_22(beSvEndApi *arg0);
extern "C" void Gap__Bec__beSvEndApi__vfunc_23(beSvEndApi *arg0, void *arg1);
extern "C" int DAT_0058a810[8];
extern "C" int DAT_0058a800[4];
extern "C" int DAT_0058a8f0[4];
typedef struct ConnectCheckState {
    char header[64];
    int types[8];            /* +64 */
    int frees[8];            /* +96 */
    int slot;                /* +128 */
    int pad132;
    int type;                /* +136 */
    int free;                /* +140 */
} ConnectCheckState;
extern "C" int DAT_0058a830[];
extern "C" int DAT_0058a890[];
extern "C" void FUN_003ada60(ConnectCheckState *check);
extern "C" int DAT_004c91f0[4];
typedef struct L { char p8[8]; int n; int p12; int *d; } L;
typedef struct A { char p0[12]; L *l12; char p16[32]; L *l48; char p52[4]; L *l56; } A;
typedef struct B { int w[64]; } B;
extern "C" int FUN_003add40(int *arg0, A *arg1);
extern "C" int g_beSvConnectCheck_metaObject[4];
extern "C" int g_beSaveApi_metaObject[4];
extern "C" int g_beSvEndApi_metaObject[4];
extern "C" int g_beSvStartApi_metaObject[4];
extern "C" int g_beSvGetFreeSizeApi_metaObject[4];
extern "C" int g_beSvWriteMediaApi_metaObject[4];
extern "C" void Gap__Bec__beSvWriteMediaApi__vfunc_08(beSvWriteMediaApi *arg0);
extern "C" int g_beSvReadMediaApi_metaObject[4];
extern "C" void Gap__Bec__beSvReadMediaApi__vfunc_08(beSvReadMediaApi *arg0);
extern "C" int g_beSvUseCheckApi_metaObject[4];
extern "C" int g_beSvFormatApi_metaObject[4];
extern "C" int g_beSvFileFindApi_metaObject[4];
extern "C" int g_beSvFileMakeApi_metaObject[4];
/* igObject header: the reference count at +4 is not a reflected field */
typedef struct RefCountedHeader { char pad4[4]; int references; } RefCountedHeader;
extern "C" void Gap__Bec__beSvFileMakeApi__vfunc_08(beSvFileMakeApi *arg0);

void FUN_003a9810(void *arg0, int arg1) {
    int t;
    int a;
    *(int *)((char *)(arg0) + 12) = arg1;
    t = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        a = t;
    } else {
        a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    }
    *(int *)((char *)(arg0) + 8) = Memory_AllocateBufferDirect(arg1, a);
}

void FUN_003a9870(struct S *arg0) {
    int var_v0;

    if (arg0->f8 != 0) {
        var_v0 = igObject_GetAllocator(arg0);
        var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        Memory_FreeBufferWithAllocator(arg0->f8, var_v0);
    }
    arg0->f8 = 0;
    arg0->fc = 0;
}

void FUN_003a98d0(struct O *arg0, int arg1, int arg2) {
    int a, b;

    if (arg2 == 0) {
        a = igObject_GetAllocator(arg0);
        b = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        arg0->buf = (void *)Memory_AllocateBufferDirect(arg1, b);
    } else {
        a = igObject_GetAllocator(arg0);
        b = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        arg0->buf = (void *)FUN_002ed2b0(arg1, arg2 & 0xFFFF, b);
    }
    memset(arg0->buf, 0, arg1);
}

void FUN_003a9990(struct S_3a9990 *arg0) {
    int var_v0;

    if (arg0->f8 != 0) {
        var_v0 = igObject_GetAllocator();
        var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        Memory_FreeBufferWithAllocator(arg0->f8, var_v0);
    }
    arg0->f8 = 0;
}

void Gap__Bec__beSaveMemoryObj__vfunc_08(void **arg0) {
    FUN_003a9990((S_3a9990 *)arg0);
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

int Gap__Bec__beSaveMemoryObj__vfunc_20(void)
{
    return g_beSaveMemoryObj_metaObject[0];
}

void Gap__Bec__beSvFileMakeApi__vfunc_23(beSvFileMakeApi *arg0, beSvDeliver *arg1) {
    arg1->_result = (int)((int) arg0->_result);
    arg1->_isEndOperat = 1;
}

void Gap__Bec__beSvFileFindApi__vfunc_21(beSvFileFindApi *arg0, beSvDeliver *arg1) {
    int temp_a2;

    temp_a2 = arg1->_targetConnect;
    if (temp_a2 == -1) {
        arg0->_connect = 0;
        arg0->_isConAllChk = 1;
    } else {
        arg0->_connect = temp_a2;
        arg0->_isConAllChk = 0;
    }
    arg0->_isEnd = 0;
    arg0->_result = 1;
    ((int *)DAT_0058a600)[0] = arg1->_platformData;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
    GPR_00554e60 = 1;
    *(int *)((char *)(arg0) + 60) = 0;
}

void Gap__Bec__beSvFileFindApi__vfunc_23(beSvFileFindApi *arg0, beSvDeliver *arg1) {
    arg1->_result = (int)((int) arg0->_result);
    arg1->_isEndOperat = 1;
}

void Gap__Bec__beSvFormatApi__vfunc_21(beSvFormatApi *arg0, void *arg1) {
    arg0->_isEnd = 0;
    arg0->_connect = (int)((int) *(int *)((char *)(arg1) + 16));
    arg0->_result = 1;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
    GPR_00554e60 = 1;
    *(int *)((char *)(arg0) + 60) = 0;
}

unsigned char Gap__Bec__beSvFormatApi__vfunc_22(beSvFormatApi *arg0) {
    int a0;
    int v;
    int t;
    unsigned char tc;
    if (arg0->_isEnd != 0) return 1;
    if (GPR_00554e64 == 1) return 0;
    switch (arg0->_st0) {
    case 0:
        *(int *)((char *)arg0 + 60) /* unreflected field past the last reflected member */ = 0;
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        a0 = arg0->_connect * 8;
        if (FUN_0011a500(*(int *)((char *)((int *)DAT_004c91b0) + a0), *(int *)((char *)DAT_004c91b4 + a0)) >= 0) {
            DAT_0058a870[0] = 1;
            arg0->_st0 = arg0->_st0 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            arg0->_st1 = 0;
        }
        break;
    case 2:
        if (DAT_0058a870[0] == 1) return 0;
        v = DAT_0058a8d0[0];
        if (v >= 0) {
            arg0->_isEnd = 1;
            arg0->_result = 2;
        } else {
            *(int *)((char *)arg0 + 60) /* unreflected field past the last reflected member */ = *(int *)((char *)arg0 + 60) /* unreflected field past the last reflected member */ + 1;
            tc = *(int *)((char *)arg0 + 60) /* unreflected field past the last reflected member */ < 3;
            if (tc == 1) {
                arg0->_st0 = 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
            } else {
                switch (v) {
                case -5:
                    arg0->_result = 12;
                    arg0->_isEnd = 1;
                    break;
                default:
                    arg0->_result = 12;
                    arg0->_isEnd = 1;
                    break;
                }
            }
        }
        break;
    default:
        break;
    }
    if (arg0->_isEnd != 0) GPR_00554e60 = 0;
    return arg0->_isEnd;
}

void Gap__Bec__beSvFormatApi__vfunc_23(beSvFormatApi *arg0, void *arg1) {
    *(int *)((char *)(arg1) + 24) = (int)((int) arg0->_result);
    *(char *)((char *)(arg1) + 44) = 1;
}

void Gap__Bec__beSvUseCheckApi__vfunc_21(beSvUseCheckApi *arg0, beSvDeliver *arg1) {
    arg0->_connect = (int)((int) arg1->_targetConnect);
    arg0->_isEnd = 0;
    arg0->_result = 1;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
    GPR_00554e60 = 1;
    *(int *)((char *)(arg0) + 60) = 0;
}

unsigned char Gap__Bec__beSvUseCheckApi__vfunc_22(beSvUseCheckApi *arg0) {
    /* fields past the reflected beSvUseCheckApi layout (+60 retry count, +64/+72 out words) */
    beSvUseCheckApiTail *x = (beSvUseCheckApiTail *)arg0;
    int a0;
    int v;
    unsigned char tc;
    if (arg0->_isEnd != 0) return 1;
    if (GPR_00554e64 == 1) return 0;
    switch (arg0->_st0) {
    case 0:
        x->f60 = 0;
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        a0 = arg0->_connect * 8;
        if (FUN_00119ff0(*(int *)((char *)((int *)DAT_004c91b0) + a0), *(int *)((char *)DAT_004c91b4 + a0), &x->f64, 0, &x->f72) >= 0) {
            DAT_0058a834[0] = 1;
            arg0->_st0 = arg0->_st0 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            arg0->_st1 = 0;
        }
        break;
    case 2:
        if (DAT_0058a834[0] == 1) return 0;
        v = DAT_0058a894[0];
        if (v >= 0) {
            switch (x->f64) {
            case 2:
                if (x->f72 == 1) {
                    arg0->_result = 2;
                } else {
                    arg0->_result = 7;
                }
                break;
            case 0:
            case 1:
            case 3:
                arg0->_result = 12;
                break;
            }
            arg0->_isEnd = 1;
        } else {
            x->f60 = x->f60 + 1;
            tc = x->f60 < 3;
            if (tc == 1) {
                arg0->_st0 = 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
            } else {
                switch (v) {
                case -5:
                    arg0->_result = 5;
                    break;
                case -1:
                case -2:
                default:
                    arg0->_result = 12;
                    break;
                }
                arg0->_isEnd = 1;
            }
        }
        break;
    default:
        break;
    }
    if (arg0->_isEnd != 0) GPR_00554e60 = 0;
    return arg0->_isEnd;
}

void Gap__Bec__beSvUseCheckApi__vfunc_23(beSvUseCheckApi *arg0, beSvDeliver *arg1) {
    arg1->_result = (int)((int) arg0->_result);
    arg1->_isEndOperat = 1;
}

void Gap__Bec__beSvReadMediaApi__vfunc_23(beSvReadMediaApi *arg0, void *arg1) {
    *(int *)((char *)(arg1) + 24) = (int)((int) arg0->_result);
    *(char *)((char *)(arg1) + 44) = 1;
}

#define SV_NEXT_STEP(self)  ((self)->_step = (self)->getStep() + 1, (self)->_st3 = 0, (self)->_st2 = 0)
#define SV_FIRST_STEP(self) ((self)->_st3 = 0, (self)->_st2 = 0, (self)->_step = 0)
#define SV_RETRY_STEP(self) ((self)->_step = 1, (self)->_st3 = 0, (self)->_st2 = 0)
int Gap__Bec__beSvWriteMediaApi__vfunc_22(beSvWriteMediaApiRun *self)
{
    char path[256];
    int ok;
    int res;
    SvCardContext *ctx;

    if (self->_isEnd != 0) {
        return 1;
    }
    if (GPR_00554e64 == 1) {
        return 0;
    }
    ctx = DAT_0058a600[0];
    switch (self->getPhase()) {
    case 0:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            sprintf(path, DAT_00510310, ctx->volumeNumber, ctx->volumeNumber);
            if (FUN_001198a8(DAT_004c91b0[self->_connect].port, DAT_004c91b0[self->_connect].slot, path, 3) >= 0) {
                DAT_0058a838[0] = 1;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (DAT_0058a838[0] == 1) {
                return 0;
            }
            res = DAT_0058a898[0];
            if (res >= 0) {
                DAT_0058a808[0] = res;
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                ok = self->_retryCount < 3; if (ok == 1) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -3:
                    case -4:
                    case -5:
                    case -7:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 1:
        self->_imagePass = 0;
        self->_phase = self->_phase + 1;
        SV_FIRST_STEP(self);
        /* fall through */
    case 2:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (FUN_00119ac8(DAT_0058a808[0], ctx->imageOffsets[self->_imagePass], 0) >= 0) {
                DAT_0058a840[0] = 1;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (DAT_0058a840[0] == 1) {
                return 0;
            }
            res = DAT_0058a8a0[0];
            if (res >= 0) {
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                ok = self->_retryCount < 3; if (ok == 1) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 3:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (FUN_00119d58(DAT_0058a808[0], self->_saveWork->buffer, ctx->dataSize) >= 0) {
                DAT_0058a848[0] = 1;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (DAT_0058a848[0] == 1) {
                return 0;
            }
            res = DAT_0058a8a8[0];
            if (res >= 0) {
                SV_NEXT_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                ok = self->_retryCount < 3; if (ok == 1) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                    case -8:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        case 3:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 4:
            if (FUN_0011a6f0(DAT_0058a808[0]) >= 0) {
                DAT_0058a858[0] = 1;
                SV_NEXT_STEP(self);
            }
            break;
        case 5:
            if (DAT_0058a858[0] == 1) {
                return 0;
            }
            res = DAT_0058a8b8[0];
            if (res >= 0) {
                if (self->_imagePass == 0) {
                    self->_imagePass = 1;
                    self->_phase = self->_phase - 1;
                    SV_FIRST_STEP(self);
                } else {
                    self->_phase = self->_phase + 1;
                    SV_FIRST_STEP(self);
                }
            } else {
                self->_retryCount = self->_retryCount + 1;
                ok = self->_retryCount < 3; if (ok == 1) {
                    SV_RETRY_STEP(self);
                } else switch (res) {
 case -2:
     self->_result = 3;
     self->_isEnd = 1;
     break;
 default:
     self->_result = 12;
     self->_isEnd = 1;
     break;
 }
            }
            break;
        }
        break;
    case 4:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (FUN_00119a08(DAT_0058a808[0]) >= 0) {
                DAT_0058a83c[0] = 1;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (DAT_0058a83c[0] == 1) {
                return 0;
            }
            res = DAT_0058a89c[0];
            if (res >= 0) {
                self->_isEnd = 1;
                self->_result = 2;
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                ok = self->_retryCount < 3; if (ok == 1) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                    case -8:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 5:
        break;
    }
    if (self->_isEnd != 0) {
        FUN_003a9990((struct S_3a9990 *)self->_saveWork);
        (*(unsigned char *)&GPR_00554e60) = 0;
    }
    return self->_isEnd;
}

#undef SV_RETRY_STEP
#undef SV_FIRST_STEP
#undef SV_NEXT_STEP

void Gap__Bec__beSvWriteMediaApi__vfunc_23(beSvWriteMediaApi *arg0, void *arg1) {
    *(int *)((char *)(arg1) + 24) = (int)((int) arg0->_result);
    *(char *)((char *)(arg1) + 44) = 1;
}

void Gap__Bec__beSvGetFreeSizeApi__vfunc_21(beSvGetFreeSizeApi *arg0, void *arg1) {
    arg0->_connect = (int)((int) *(int *)((char *)(arg1) + 16));
    arg0->_isEnd = 0;
    arg0->_result = 1;
    ((int *)DAT_0058a600)[0] = *(int *)((char *)(arg1) + 64);
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
    GPR_00554e60 = 1;
    *(int *)((char *)(arg0) + 60) = 0;
}

unsigned char Gap__Bec__beSvGetFreeSizeApi__vfunc_22(beSvGetFreeSizeApi *arg0) {
    int temp_a0;
    int v;
    beSvPlatBaseData *q;
    int e;

    if (arg0->_isEnd != 0) {
        return 1U;
    }
    if (GPR_00554e64 == 1) {
        return 0U;
    }
    q = ((beSvPlatBaseData * *)DAT_0058a600)[0];
    switch (arg0->_st0) {
    case 0:
        *(int *)((char *)arg0 + 60) = 0;
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        temp_a0 = arg0->_connect * 8;
        if (FUN_00119ff0(*(int *)((char *)((int *)DAT_004c91b0) + temp_a0), *(int *)((char *)DAT_004c91b4 + temp_a0), (int *)((char *)arg0 + 76), (int *)((char *)arg0 + 80), (int *)((char *)arg0 + 84)) >= 0) {
            DAT_0058a834[0] = 1;
            arg0->_st0 = arg0->_st0 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            arg0->_st1 = 0;
        }
        break;
    case 2:
        if (DAT_0058a834[0] == 1) {
            return 0U;
        }
        e = DAT_0058a894[0];
        if (e >= 0) {
            switch (*(int *)((char *)arg0 + 76)) {
            case 2:
                arg0->_result = 2;
                arg0->_fileCapa = 0x80;
                arg0->_isEnd = 1U;
                switch (*(int *)((char *)arg0 + 84)) {
                case 0:
                    arg0->_memCapa = 0x04E00000U;
                    break;
                case 1:
                    arg0->_memCapa = *(int *)((char *)arg0 + 80) << 0xA;
                    break;
                }
                if (!(q->_memNeed > (unsigned int) arg0->_memCapa)) {
                    arg0->_result = 2;
                } else {
                    arg0->_result = 9;
                }
                break;
            case 0:
            case 3:
            case 1:
                arg0->_result = 0xC;
                break;
            }
            arg0->_isEnd = 1U;
            break;
        }
        *(int *)((char *)arg0 + 60) = *(int *)((char *)arg0 + 60) + 1;
        if ((unsigned char)(*(int *)((char *)arg0 + 60) < 3) == 1) {
            arg0->_st0 = 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            arg0->_st1 = 0;
        } else {
            switch (e) {
            case -2:
                arg0->_memCapa = 0x04E00000U;
                arg0->_fileCapa = 0x80;
                arg0->_result = 2;
                arg0->_isEnd = 1U;
                break;
            case -5:
                arg0->_result = 5;
                arg0->_isEnd = 1U;
                break;
            default:
            case -1:
                arg0->_result = 0xC;
                arg0->_isEnd = 1U;
                break;
            }
        }
        break;
    }
    if (arg0->_isEnd == 1) {
        GPR_00554e60 = 0;
    }
    return arg0->_isEnd;
}

void Gap__Bec__beSvGetFreeSizeApi__vfunc_23(beSvGetFreeSizeApi *arg0, UnidentifiedResultObject *arg1) {
    UnidentifiedFreeSizeGlobal *g = ((UnidentifiedFreeSizeGlobal * *)DAT_0058a600)[0];

    arg1->f24 = arg0->_result;
    arg1->b44 = 1;
    if (((beSvGetFreeSizeApiTail *)arg0)->f84 == 1) {
        arg1->f32 = (unsigned int)arg0->_memCapa;
    } else {
        arg1->f32 = 0x04E00000;
    }
    arg1->f36 = arg0->_fileCapa;
    if (!(g->f20 > (unsigned int)arg0->_memCapa)) {
        arg1->b42 = 1;
    } else {
        arg1->b42 = 0;
    }
    arg1->b43 = 1;
}

void Gap__Bec__beSvStartApi__vfunc_21(beSvStartApi *arg0, void *arg1) {
    int sp3C;
    int sp38;

    arg0->_isEnd = 0;
    if (GPR_00554e58 == 0) {
        FUN_0032cf50(&sp3C, &DAT_00510428[0], 1, 0, 0);
        FUN_0032cf50(&sp38, &DAT_00510438[0], 1, 0, 0);
        FUN_001194c0();
        GPR_00554e58 = 1;
    }
    sceMtapPortOpen(2);
    DAT_004c91a0[0] = 5;
    DAT_0058a608[0] = *(int *)((char *)(arg1) + 20);
    if (sceMtapGetConnection(2) == 1) {
        GPR_005549dc = 1;
        GPR_00554e5c = 0;
    } else {
        GPR_00554e5c = 0;
        GPR_005549dc = -1;
    }
    GPR_00554e60 = 0;
    (*(char *)&GPR_00554e64) = 0;
    *(int *)((char *)(arg0) + 60) = 0;
    arg0->_result = 1;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}

int Gap__Bec__beSvStartApi__vfunc_22(beSvStartApi *arg0) {
    if (arg0->_isEnd != 0) {
        return 1;
    }
    arg0->_isEnd = 1;
    return 1;
}

void Gap__Bec__beSvStartApi__vfunc_23(beSvStartApi *arg0, void *arg1) {
    *(int *)((char *)(arg1) + 24) = (int)((int) arg0->_result);
    *(char *)((char *)(arg1) + 44) = 1;
}

void Gap__Bec__beSvEndApi__vfunc_21(beSvEndApi *arg0) {
    arg0->_isEnd = 0;
    arg0->_result = 1;
    sceMtapPortClose(2);
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}

int Gap__Bec__beSvEndApi__vfunc_22(beSvEndApi *arg0) {
    if (arg0->_isEnd != 0) {
        return 1;
    }
    arg0->_isEnd = 1;
    arg0->_result = 2;
    return 1;
}

void Gap__Bec__beSvEndApi__vfunc_23(beSvEndApi *arg0, void *arg1) {
    *(int *)((char *)(arg1) + 24) = (int)((int) arg0->_result);
    *(char *)((char *)(arg1) + 44) = 1;
}

int FUN_003ad7a0(int arg0, int arg1) {
    int sp2C;

    sp2C = 0;
    FUN_00119ff0(DAT_004c91b0[arg1].port, DAT_004c91b0[arg1].slot, &sp2C, 0, 0);
    sceMcSync(0, 0, 0);
    if (sp2C == 2) {
        DAT_0058a810[arg1] = 1;
        return 1;
    }
    DAT_0058a810[arg1] = 0;
    return 0;
}

int FUN_003ad850(int port, int onlyPresent) {
    int count;
    int i;
    count = 5;
    if (GPR_005549dc == -1)
        count = 2;
    else if (GPR_005549dc == 1)
        count = 5;
    for (i = 0; i < count; i++) {
        if (!onlyPresent || DAT_0058a810[i] == 1)
            FUN_003ad7a0(port, i);
    }
    for (i = count; i < 8; i++)
        DAT_0058a810[i] = 0;
    return count;
}

void FUN_003ad950(int arg0, void *arg1) {
    if (DAT_0058a8f0[0] != 0) {
        if (DAT_0058a800[0] > 0) {
            goto block_3;
        }
    } else {
block_3:
        if (sceMtapGetConnection(2) == 1) {
            if (GPR_005549dc == 1) {
                GPR_00554e5c = 0;
                DAT_0058a800[0] = 0;
            } else {
                DAT_0058a800[0] += 1;
                if (DAT_0058a800[0] >= 3) {
                    DAT_0058a800[0] = 0;
                    GPR_00554e5c = 1;
                    GPR_005549dc = 1;
                }
            }
        } else if (GPR_005549dc == -1) {
            GPR_00554e5c = 0;
            DAT_0058a800[0] = 0;
        } else {
            DAT_0058a800[0] += 1;
            if (DAT_0058a800[0] >= 3) {
                DAT_0058a800[0] = 0;
                GPR_00554e5c = -1;
                GPR_005549dc = -1;
            }
        }
        *(char *)((char *)(arg1) + 40) = (char) GPR_005549dc;
        *(char *)((char *)(arg1) + 41) = (char) GPR_00554e5c;
    }
}

void FUN_003ada60(ConnectCheckState *check) {
    if (GPR_00554e64 == 1) {
        int result;
        int cmd;
        result = 0;
        cmd = 0;
        int done = sceMcSync(1, &cmd, &result);
        if (done != 0 && done == 1) {
            switch (result) {
            case 0:
            case -2:
            case -1:
                DAT_0058a810[check->slot] = 1;
                check->types[check->slot] = check->type;
                check->frees[check->slot] = check->free;
                break;
            default:
                DAT_0058a810[check->slot] = 0;
                break;
            }
            GPR_00554e64 = 0;
            if (!(*(unsigned char *)&GPR_00554e60)) {
                int count = FUN_003ad850((int)check, 1);
                bool found = false;
                int tries;
                for (tries = 1; tries < count + 1; tries++) {
                    int s = (check->slot + tries) % count;
                    if (DAT_0058a810[s] == 0) {
                        check->slot = s;
                        found = true;
                        break;
                    }
                }
                if (found == true) {
                    FUN_00119ff0(DAT_004c91b0[check->slot].port, DAT_004c91b0[check->slot].slot, 0, &check->type, &check->free);
                    GPR_00554e64 = 1;
                }
            }
        }
    } else if ((*(unsigned char *)&GPR_00554e60) == 1) {
        int result;
        int cmd;
        result = 0;
        cmd = 0;
        int done = sceMcSync(1, &cmd, &result);
        if (done != 0 && done == 1) {
            if (cmd > 0 && cmd < 22 && DAT_0058a830[cmd] == 1) {
                DAT_0058a890[cmd] = result;
                DAT_0058a830[cmd] = 2;
            }
        }
    } else {
        int count = FUN_003ad850((int)check, 0);
        check->slot = 0;
        bool found = false;
        int s;
        for (s = 0; s < count; s++) {
            if (DAT_0058a810[s] == 0) {
                check->slot = s;
                found = true;
                break;
            }
        }
        if (found == true) {
            FUN_00119ff0(DAT_004c91b0[check->slot].port, DAT_004c91b0[check->slot].slot, 0, &check->type, &check->free);
            GPR_00554e64 = 1;
        }
    }
}

int FUN_003add40(int *arg0, A *arg1) {
    L *a4;
    L *a3;
    L *a2;
    int i;
    int n;
    int *d;
    int *p;
    int cnt;
    int j;
    int c;
    int off;
    a4 = arg1->l12;
    a3 = arg1->l48;
    a2 = arg1->l56;
    cnt = 0;
    if (DAT_0058a800[0] == 0) {
        *(char *)((char *)arg1 + 40) = GPR_005549dc;
    }
    n = a4->n;
    d = a4->d;
    for (j = 0; j < n; j++) {
        d[j] = DAT_004c91f0[0];
    }
    i = 0;
    if (0 < a4->n) {
        off = 0;
        p = &DAT_0058a810[0];
        do {
            c = *(int *)&a4->n;
            if (c != 0 && i >= 0 && i < c) {
                *(int *)((char *)a4->d + off) = *p;
            }
            if (*p == 1) {
                c = a3->n;
                if (c != 0 && i >= 0 && i < c) {
                    *(int *)((char *)a3->d + off) = arg0[16];
                }
                c = a2->n;
                if (c != 0 && i >= 0 && i < c) {
                    *(int *)((char *)a2->d + off) = arg0[24];
                }
                cnt++;
            }
            i++;
            p++;
            off += 4;
            arg0++;
        } while (i < a4->n);
    }
    return cnt;
}

void Gap__Bec__beSvConnectCheck__vfunc_21(void)
{
}

int Gap__Bec__beSvConnectCheck__vfunc_22(void) {
    return 0;
}

void Gap__Bec__beSvConnectCheck__vfunc_23(void)
{
}

int Gap__Bec__beSvConnectCheck__vfunc_20(void)
{
    return g_beSvConnectCheck_metaObject[0];
}

void Gap__Bec__beSvConnectCheck__vfunc_07(void **arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

int Gap__Bec__beSaveApi__vfunc_20(void)
{
    return g_beSaveApi_metaObject[0];
}

void Gap__Bec__beSvConnectCheck__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

int Gap__Bec__beSvEndApi__vfunc_20(void)
{
    return g_beSvEndApi_metaObject[0];
}

void Gap__Bec__beSvEndApi__vfunc_07(void **arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

void Gap__Bec__beSvEndApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

int Gap__Bec__beSvStartApi__vfunc_20(void)
{
    return g_beSvStartApi_metaObject[0];
}

void Gap__Bec__beSvStartApi__vfunc_07(void **arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

void Gap__Bec__beSvStartApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

int Gap__Bec__beSvGetFreeSizeApi__vfunc_20(void)
{
    return g_beSvGetFreeSizeApi_metaObject[0];
}

void Gap__Bec__beSvGetFreeSizeApi__vfunc_07(void **arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

void Gap__Bec__beSvGetFreeSizeApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

int Gap__Bec__beSvWriteMediaApi__vfunc_20(void)
{
    return g_beSvWriteMediaApi_metaObject[0];
}

void Gap__Bec__beSvWriteMediaApi__vfunc_07(void **arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

void Gap__Bec__beSvWriteMediaApi__vfunc_08(beSvWriteMediaApi *arg0) {
    igObject *temp_a0;

    temp_a0 = (igObject *)arg0->_saveWork;
    if (temp_a0 != 0) {
        if (temp_a0 != 0) {
            temp_a0->_refCount = (int)temp_a0->_refCount - 1;
            if (((unsigned long long) ((long long) (int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_saveWork = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

int Gap__Bec__beSvReadMediaApi__vfunc_20(void)
{
    return g_beSvReadMediaApi_metaObject[0];
}

void Gap__Bec__beSvReadMediaApi__vfunc_07(void **arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

/* igObject header: the reference count at +4 is not a reflected field */

static inline int countOf(const igObjectList *l) { return l->_count; }

void Gap__Bec__beSvReadMediaApi__vfunc_08(beSvReadMediaApi *arg0) {
    igObjectList *l = (igObjectList *)arg0->_loadWorkList;
    if (countOf(l) != 0) {
        int n = l->_count;
        int i;
        igObject *t;
        for (i = 0; i < n; i++) {
            t = ((igObject **)l->_data)[i];
            if (t != 0) {
                t->_refCount = (int)t->_refCount - 1;
                if (((unsigned long long) ((long long) (int)t->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(t);
                }
            }
        }
        {
            int m = l->_count;
            int j;
            for (j = 0; j < m; j++) {
                ((igObject **)l->_data)[j] = 0;
            }
        }
        l->_count = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

int Gap__Bec__beSvUseCheckApi__vfunc_20(void)
{
    return g_beSvUseCheckApi_metaObject[0];
}

void Gap__Bec__beSvUseCheckApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

void FUN_003ae4a0(void **arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

int Gap__Bec__beSvFormatApi__vfunc_20(void)
{
    return g_beSvFormatApi_metaObject[0];
}

void Gap__Bec__beSvFormatApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

int Gap__Bec__beSvFileFindApi__vfunc_20(void)
{
    return g_beSvFileFindApi_metaObject[0];
}

void Gap__Bec__beSvFileFindApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

int Gap__Bec__beSvFileMakeApi__vfunc_20(void)
{
    return g_beSvFileMakeApi_metaObject[0];
}

void Gap__Bec__beSvFileMakeApi__vfunc_07(void **arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

void Gap__Bec__beSvFileMakeApi__vfunc_08(beSvFileMakeApi *arg0) {
    RefCountedHeader *temp_a0;

    temp_a0 = (RefCountedHeader *)arg0->_saveWork;
    if (temp_a0 != 0) {
        if (temp_a0 != 0) {
            temp_a0->references = temp_a0->references - 1;
            if (((unsigned long long) ((long long) temp_a0->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_saveWork = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

void Gap__Bec__beSaveApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

void Gap__Bec__beSaveMemoryObj__vfunc_07(void **arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}
