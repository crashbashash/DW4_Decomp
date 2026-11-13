
extern "C" int igObject_GetAllocator(...);
extern "C" int Memory_AllocateAlignedWithAllocator(...);
extern "C" int FUN_0026b348(int, int, int);
extern "C" int FUN_0026d8b8(int, int, int);
extern "C" int FUN_0026d5f0(int, short, short);
extern "C" int FUN_0026d7a0(int, int);
extern "C" int ADXT_Stop(int);
extern "C" void igAdxAudio_Stop(void *arg0);
extern "C" int ADXT_Pause(int);
extern "C" void igAdxAudio_Pause(void *arg0);
extern "C" int ADXT_GetStatPause(int);
extern "C" int igAdxAudio_GetPauseState(void *arg0);
extern "C" int ADXT_Destroy(...);
extern "C" int Memory_FreeBufferWithAllocator(...);
extern "C" int FUN_0026c660(int);
extern "C" void igAdxAudio_SetOutVolume(void *arg0);
extern "C" int FUN_0026c6c8(int);
extern "C" int igAdxAudio_GetOutVolume(void *arg0);
extern "C" int FUN_0026bd20(int);
extern "C" int igAdxAudio_GetStatus(void *arg0);
extern "C" void *FUN_002b9500(int);
extern "C" int Memory_GetAllocatorByName(...);
extern "C" int igObject_Destroy(...);
extern "C" void FUN_003324c0(void);
extern "C" int FUN_0010b9c0(int);
extern "C" int ADXM_ShutdownThrd(...);
extern "C" int FUN_00280d20(...);
extern "C" int FUN_00294df8(...);
extern "C" int RemoveIntcHandler(int, int);
extern "C" void FUN_00332530(void);
extern "C" void Gap__Core__igObject__vfunc_01(void);
extern "C" void Gap__igAdx__vfunc_01(void);
extern "C" int memset(...);
extern "C" int Gap__Core__igObject__vfunc_11(...);
extern "C" void Gap__igAdx__vfunc_11(void);
extern "C" int Gap__Core__igObject__vfunc_07(...);
extern "C" int igMetaObject_CountInstances(...);
extern "C" void Gap__igAdx__vfunc_07(void **arg0);
extern "C" int Gap__igAdx__vfunc_20(void);
extern "C" void Gap__igAdx__vfunc_02(void);
extern "C" int Gap__Core__igObject__vfunc_08__002ff0f0(...);
extern "C" void Gap__igAdx__vfunc_08(void **arg0);
extern "C" void FUN_003327b0(void);
extern "C" int strcpy(...);
extern "C" void igAdx_SetModulePath(int arg0);
extern "C" void FUN_00332810(int arg0);
extern "C" int AddIntcHandler(int, int (*)(), int);
extern "C" int ADXM_ExecVint(void);
extern "C" int FUN_0010ba28(int);
extern "C" int sceSifInitRpc(int);
extern "C" int sceSifInitIopHeap(...);
extern "C" int FUN_00116fb0(int);
extern "C" int sceCdMmode(int);
extern "C" int sceSdRemoteInit(...);
extern "C" int sceSdRemote(...);
extern "C" int sprintf(...);
extern "C" int FUN_0026ac50(int);
extern "C" int FUN_0026ad50(int *);
extern "C" int FUN_0026b008(int *);
extern "C" int FUN_0026b120(int *);
extern "C" int FUN_0026b1f0(int);
extern "C" int FUN_0032cf50(...);
extern "C" int strcmp(...);
extern "C" int FUN_00332860(void);
extern "C" int FUN_00332c40(void);
extern "C" int FUN_002632c0(...);
extern "C" int ADXM_SetCbErr(void (*)(void), int);
extern "C" int ADXM_SetupThrd(int);
extern "C" int FUN_00280d48(...);
extern "C" int FUN_00332c50(int arg0);
extern "C" void ADXM_ExecVsyncFrame(void);
extern "C" void FUN_00332cd0(void);
extern "C" int ADXM_ExecMain(...);
extern "C" int FUN_00282038(...);
extern "C" void igAdx_ExecServer(int);
extern "C" void *igStringRefList_Create(int);
extern "C" void igAdx_SetPartitionCount(int arg0);
extern "C" int StringPool_Allocate(int);
extern "C" int List_Reserve(void *, int, int);
extern "C" int StringChunk_ReleaseHeader(int, int *);
extern "C" int StringPool_Construct(int);
extern "C" char *StringPool_Intern(int, char *);
extern "C" void igAdx_AddPartitionName(int arg0, char *arg1);
extern "C" void FUN_00260de8(int stream, const char *name, int mode, void *buffer);
extern "C" int FUN_002612c0(int stream);
extern "C" int igAdx_LoadPartition(int stream, const char *path, int mode, int length);
extern "C" unsigned int strlen(const char *);
extern "C" char *strncpy(char *, const char *, unsigned int);
extern "C" int FUN_00333440(const char *name);
extern "C" int strcat(char *, void *);
extern "C" void __dl__FPv(void *);
extern "C" void FUN_003337e0(void);
extern "C" void FUN_003337f0(void);
struct S { char pad[8]; int f8; int f12; int pad2; int f20; int f24; int f28; int f32; unsigned char f36; };
extern "C" int igAdxAudio_Initialize(struct S *s, int a, int b, int c, int d);
typedef struct T_3320d0 { char pad0[8]; int f8; int fc; char pad1[4]; int f14; char pad2[12]; unsigned char f24; char pad3[7]; int f2c; } T_3320d0;
extern "C" int igAdxAudio_CreateHandle(T_3320d0 *arg0, int a1, int a2, int a3, int a4, int a5);
typedef struct S_332160 { char pad0[20]; int f20; int f24; int f28; int f32; char pad36[8]; int f44; } S_332160;
extern "C" int igAdxAudio_StartMemory(S_332160 *arg0, int arg1, int arg2);
struct Q { char pad[16]; short f16; short f18; };
struct T_3321f0 { char pad[16]; struct Q **f16; };
struct S_3321f0 { char pad[44]; int f44; };
extern "C" int FUN_003321f0(struct S_3321f0 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
struct A { char pad[20]; int f20; int f24; int f28; int f32; char pad2[8]; int f44; };
struct L { char pad[16]; int *tab; };
struct E { char pad[16]; short s16; short s18; };
extern "C" int igAdxAudio_StartFile(struct A *arg0, int arg1);
struct S_3323d0 { char pad[8]; int f8; char pad2[32]; int f44; };
extern "C" void igAdxAudio_Shutdown(S_3323d0 *arg0);
typedef struct R { char pad4[4]; int f4; } R;
extern "C" int DAT_004ffe68[4];
typedef struct Obj { int w0; unsigned refs; } Obj;
extern "C" int DAT_005873a8[4];
extern "C" int DAT_005873b8[4];
extern "C" int DAT_005873c0[4];
extern "C" int g_adxMediaMode[4];
extern "C" int DAT_005874d0[4];
extern "C" int g_adxPartitionCount[4];
typedef struct T_332670 { int w0; int refs; } T_332670;
extern "C" char g_adxUseFileInfoCache;
extern "C" unsigned char GPR_00554de8;
extern "C" char GPR_00554dec;
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" int g_igAdx_metaObject[4];
extern "C" char DAT_005873d0[16];
extern "C" int FUN_00280b98(struct Q_332860 *);
extern "C" int DAT_004ffe70[4];
extern "C" int DAT_004ffe80[4];
extern "C" int DAT_004ffe90[4];
extern "C" int DAT_004ffea0[4];
extern "C" int DAT_004ffeb0[4];
extern "C" int DAT_004ffee0[4];
extern "C" int DAT_004fff10[4];
extern "C" int DAT_004fff28[4];
extern "C" int DAT_004fff40[4];
extern "C" char DAT_004fff60[16];
extern "C" int DAT_00587390[4];
extern "C" int DAT_005873a0[4];
extern "C" int DAT_005873a4[4];
extern "C" int DAT_005873ac[4];
extern "C" int DAT_005873b0[4];
extern "C" int DAT_005873b4[4];
extern "C" int DAT_005873bc[4];
extern "C" char GPR_005549b8;
struct Q_332860 { int a; int b; int c; int d; };
/* `0 < n` on the inner guards, `n > 0` on the outer, and the reference is released through a local
 * object pointer. */
typedef struct T_332d20 { int w0; int references; } T_332d20;
extern "C" void **DAT_005875f0[4];
typedef struct Obj_332e90 { int w0; int references; } Obj_332e90;
typedef struct OList { int pad0[2]; int count; int pad1; Obj_332e90 **data; } OList;
typedef struct SList { int pad0; int references; int count; int pad1; int **data; } SList;
extern "C" int g_stringPool[4];
extern "C" SList *DAT_00587608[4];
extern "C" OList *DAT_00587620[4];
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
    operator char *() const { return p; }
};
extern "C" int StringList_AppendRetained(void *, StringRef *);
struct R_333230 { int vt; unsigned int rc; };
extern "C" void igAdx_SetInsideFiles(R_333230 *arg0);
extern "C" StringRef StringList_CopyRetained(int list, int index);
struct WaitResult { int code; };
class AdxThread {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual WaitResult sleep(int microseconds);
};
struct ThreadList { char pad[16]; AdxThread **data; };
struct ThreadManager { char pad[8]; ThreadList *threads; };
extern "C" ThreadManager *g_threadManager[4];
struct TextBuffer { int vtable; unsigned int refCount; char *text; };
struct PathEntry { int vtable; unsigned int refCount; char *name; int f12; short left; short right; };
struct PathEntryList { int vtable; unsigned int refCount; int count; int capacity; PathEntry **data; };
extern "C" void igStringObj_Set(TextBuffer *buffer, const char *text);
extern "C" void igStringObj_ToLower(TextBuffer *buffer);
extern "C" void FUN_0030b5f0(TextBuffer *buffer, int *value);
extern "C" void igNamedObject_SetName(PathEntry *object, const char *name);
extern "C" char *g_stringObjEmptyText[4];
extern "C" TextBuffer *DAT_005875e0[4];
typedef struct N { int p0; int p4; char *name; } N;
typedef struct L_333630 { int p0; int p4; int count; int pc; N **data; } L_333630;
typedef struct S_333630 { int p0; int p4; char *name; L_333630 *parents; } S_333630;
extern "C" int emptyString[4];
extern "C" int DAT_004fff70[4];
extern "C" void FUN_00333630(S_333630 *arg0, char *arg1);
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" ObjectRefWord *FUN_00333760(ObjectRefWord *self,int delete_storage);

int igAdxAudio_Initialize(struct S *s, int a, int b, int c, int d) {
    if (s->f36 == 0) {
        int t, q, w;
        s->f20 = a;
        s->f24 = b;
        s->f28 = c;
        s->f32 = d;
        t = s->f32 / 1000 * (s->f20 * 25000) / 44;
        q = ((s->f28 + 1) * t + 0x800) / 0x800;
        w = (q << 11) + 0x24;
        { int m = s->f20 * 0x40C0; s->f12 = m + w + 0x40; }
        s->f8 = Memory_AllocateAlignedWithAllocator(s->f12, 16, igObject_GetAllocator(s));
        if (s->f8 == 0) return 0;
        s->f36 = 1;
    }
    return 1;
}

int igAdxAudio_CreateHandle(T_3320d0 *arg0, int a1, int a2, int a3, int a4, int a5) {
    if (arg0->f24 == 0) {
        if (a5 != 0) {
            igAdxAudio_Initialize((S *)arg0, a1, a2, a3, a4);
            arg0->f24 = 1;
        } else {
            return 0;
        }
    }
    if (arg0->f2c == 0) {
        arg0->f2c = FUN_0026b348(arg0->f14, arg0->f8, arg0->fc);
        if (arg0->f2c == 0) {
            return 0;
        }
    }
    return arg0->f2c;
}

int igAdxAudio_StartMemory(S_332160 *arg0, int arg1, int arg2) {
    if (arg0->f44 == 0) {
        arg0->f44 = igAdxAudio_CreateHandle((T_3320d0 *)arg0, arg0->f20, arg0->f24, arg0->f28, arg0->f32, 0);
        if (arg0->f44 == 0) {
            return 0;
        }
    }
    FUN_0026d8b8(arg0->f44, arg1, arg2);
    return 1;
}

int FUN_003321f0(struct S_3321f0 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    int temp_v0;
    struct Q *temp_v0_2;

    arg0->f44 = igAdxAudio_CreateHandle((T_3320d0 *)arg0, arg2, arg3, arg4, arg5, 1);
    temp_v0 = FUN_00333440((const char *)arg1);
    if (temp_v0 != -1) {
        temp_v0_2 = ((struct T_3321f0 * *)DAT_00587620)[0]->f16[temp_v0];
        FUN_0026d5f0(arg0->f44, temp_v0_2->f16, temp_v0_2->f18);
    } else {
        FUN_0026d7a0(arg0->f44, arg1);
    }
    return 1;
}

int igAdxAudio_StartFile(struct A *arg0, int arg1) {
    int temp_v0;
    struct E *e;

    if (arg0->f44 != 0) {
        temp_v0 = FUN_00333440((const char *)arg1);
        if (temp_v0 != -1) {
            e = (struct E *)((struct L *)((void * *)DAT_00587620)[0])->tab[temp_v0];
            FUN_0026d5f0(arg0->f44, e->s16, e->s18);
        } else {
            FUN_0026d7a0(arg0->f44, arg1);
        }
        return 1;
    }
    return FUN_003321f0((struct S_3321f0 *)arg0, arg1, arg0->f20, arg0->f24, arg0->f28, arg0->f32);
}

void igAdxAudio_Stop(void *arg0) {
    int temp_a0;

    temp_a0 = *(int *)((char *)(arg0) + 44);
    if (temp_a0 != 0) {
        ADXT_Stop(temp_a0);
    }
}

void igAdxAudio_Pause(void *arg0) {
    int temp_a0 = *(int *)((char *)(arg0) + 44);
    if (temp_a0 != 0) {
        ADXT_Pause(temp_a0);
    }
}

int igAdxAudio_GetPauseState(void *arg0) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 44);
    if (temp_a0 == 0) {
        return -1;
    }
    return ADXT_GetStatPause(temp_a0);
}

void igAdxAudio_Shutdown(S_3323d0 *arg0) {
    if (arg0->f44 != 0) {
        ADXT_Destroy(arg0->f44);
    }
    if (arg0->f8 != 0) {
        Memory_FreeBufferWithAllocator(arg0->f8, igObject_GetAllocator(arg0));
    }
}

void igAdxAudio_SetOutVolume(void *arg0) {
    int temp_a0;

    temp_a0 = *(int *)((char *)(arg0) + 44);
    if (temp_a0 != 0) {
        FUN_0026c660(temp_a0);
    }
}

int igAdxAudio_GetOutVolume(void *arg0) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 44);
    if (temp_a0 == 0) {
        return 0;
    }
    return FUN_0026c6c8(temp_a0);
}

int igAdxAudio_GetStatus(void *arg0) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 44);
    if (temp_a0 == 0) {
        return -1;
    }
    return FUN_0026bd20(temp_a0);
}

void FUN_003324c0(void) {
    int temp_s0;
    R *old;

    temp_s0 = Memory_GetAllocatorByName(&DAT_004ffe68[0]);
    old = ((R * *)DAT_005875e0)[0];
    if (old != 0) {
        old->f4 = old->f4 - 1;
        if ((old->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    ((R * *)DAT_005875e0)[0] = (R *)FUN_002b9500(temp_s0);
}

void FUN_00332530(void) {
    int temp_s0;
    Obj *o;

    igAdx_SetPartitionCount(0);
    o = ((Obj * *)DAT_00587620)[0];
    if (o != 0) {
        o->refs = o->refs - 1;
        if ((o->refs & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
    ((Obj * *)DAT_00587620)[0] = 0;
    o = ((Obj * *)DAT_005875e0)[0];
    if (o != 0) {
        o->refs = o->refs - 1;
        if ((o->refs & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
    ((Obj * *)DAT_005875e0)[0] = 0;
    FUN_00294df8();
    FUN_00280d20();
    FUN_0010b9c0(2);
    RemoveIntcHandler(2, DAT_005873c0[0]);
    temp_s0 = Memory_GetAllocatorByName(&DAT_004ffe68[0]);
    if (DAT_005873a8[0] != 0) {
        Memory_FreeBufferWithAllocator(DAT_005873a8[0], temp_s0);
        DAT_005873a8[0] = 0;
    }
    if (DAT_005873b8[0] != 0) {
        Memory_FreeBufferWithAllocator(DAT_005873b8[0], temp_s0);
        DAT_005873b8[0] = 0;
    }
    ADXM_ShutdownThrd();
}

void Gap__igAdx__vfunc_01(void)
{
    Gap__Core__igObject__vfunc_01();
}

void Gap__igAdx__vfunc_11(void) {
    T_332670 *p;
    Gap__Core__igObject__vfunc_11();
    DAT_005873c0[0] = 0;
    (*(char *)&GPR_00554de8) = 0;
    GPR_00554dec = 0;
    g_adxMediaMode[0] = 0;
    g_adxUseFileInfoCache = 0;
    memset(&DAT_005874d0[0], 0, 0x100);
    p = ((T_332670 * *)DAT_00587620)[0];
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long) ((long long) p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    ((T_332670 * *)DAT_00587620)[0] = 0;
    g_adxPartitionCount[0] = 0;
}

void Gap__igAdx__vfunc_07(void **arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

int Gap__igAdx__vfunc_20(void)
{
    return g_igAdx_metaObject[0];
}

void Gap__igAdx__vfunc_02(void)
{
}

void Gap__igAdx__vfunc_08(void **arg0) {
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

void FUN_003327b0(void) {

}

void igAdx_SetModulePath(int arg0) {
    if (arg0 != 0) {
        strcpy(&((int *)DAT_005873d0)[0], arg0);
        return;
    }
    memset(&((int *)DAT_005873d0)[0], 0, 0x100);
}

void FUN_00332810(int arg0) {
    if (arg0 != 0) {
        strcpy(&DAT_005874d0[0], arg0);
        return;
    }
    memset(&DAT_005874d0[0], 0, 0x100);
}

int FUN_00332860(void) {
    int sp23C;
    int sp238;
    int sp234;
    char sp30[512];
    struct Q_332860 sp20;
    int temp_s0;

    if (GPR_00554de8 != 0) {
        return 1;
    }
    sceSifInitRpc(0);
    sceSifInitIopHeap();
    FUN_00116fb0(0);
    switch (g_adxMediaMode[0]) {
    case 1:
        sceCdMmode(1);
        break;
    case 2:
        sceCdMmode(2);
        break;
    }
    GPR_005549b8 = 0;
    FUN_0032cf50(&sp23C, &DAT_004ffe70[0], 1, 0, 0);
    sceSdRemoteInit();
    sceSdRemote(1, 0x8000, 0);
    sceSdRemote(1, 0x8010, 0x980, 0x3FFF);
    sceSdRemote(1, 0x8010, 0xA80, 0x3FFF);
    sceSdRemote(1, 0x8010, 0x981, 0x3FFF);
    sceSdRemote(1, 0x8010, 0xA81, 0x3FFF);
    if (DAT_005873d0[0] != 0) {
        sprintf(sp30, &DAT_004ffe80[0], &DAT_005873d0[0]);
    } else if (strcmp(&DAT_004ffe90[0], &DAT_004ffea0[0]) == 0) {
        sprintf(sp30, &DAT_004ffeb0[0]);
    } else {
        sprintf(sp30, &DAT_004ffee0[0]);
    }
    FUN_0032cf50(&sp238, sp30, 0, 0x13, &DAT_004fff10[0]);
    if (DAT_005873d0[0] != 0) {
        sprintf(sp30, &DAT_004fff28[0], &DAT_005873d0[0]);
    } else {
        sprintf(sp30, &DAT_004fff40[0]);
    }
    FUN_0032cf50(&sp234, sp30, 0, 0, 0);
    memset(&sp20, 0, 0x10);
    sp20.a = 0x30000;
    sp20.b = 0;
    sp20.c = 0;
    sp20.d = 0;
    FUN_00280b98(&sp20);
    FUN_0026b1f0(0);
    if (((char *)DAT_005874d0)[0] != 0) {
        memset(&DAT_00587390[0], 0, 0x10);
        DAT_00587390[0] = (int)&((char *)DAT_005874d0)[0];
        FUN_0026b008(&DAT_00587390[0]);
    } else {
        FUN_0026b008(0);
    }
    temp_s0 = Memory_GetAllocatorByName(&DAT_004ffe68[0]);
    if ((*(unsigned char *)&g_adxUseFileInfoCache) != 0) {
        memset(&DAT_005873a0[0], 0, 0x10);
        DAT_005873a0[0] = (int)&DAT_004fff60[0];
        DAT_005873a4[0] = 0x20;
        DAT_005873ac[0] = ((DAT_005873a4[0] + 1) * 0xD) + 0x68;
        DAT_005873a8[0] = Memory_AllocateAlignedWithAllocator(DAT_005873ac[0], 0x10, temp_s0);
        FUN_0026b120(&DAT_005873a0[0]);
    }
    if (g_adxMediaMode[0] != 0) {
        FUN_0026ac50(0);
        if ((*(unsigned char *)&g_adxUseFileInfoCache) != 0) {
            memset(&DAT_005873b0[0], 0, 0x10);
            DAT_005873b0[0] = (int)&DAT_004fff60[0];
            DAT_005873b4[0] = 0x20;
            DAT_005873bc[0] = ((DAT_005873b4[0] + 1) * 0xD) + 0x68;
            DAT_005873b8[0] = Memory_AllocateAlignedWithAllocator(DAT_005873bc[0], 0x10, temp_s0);
            FUN_0026ad50(&DAT_005873b0[0]);
        }
    }
    FUN_0010b9c0(2);
    DAT_005873c0[0] = AddIntcHandler(2, &ADXM_ExecVint, 0);
    FUN_0010ba28(2);
    GPR_00554de8 = 1;
    return 1;
}

int FUN_00332c40(void)
{
    return 1;
}

int FUN_00332c50(int arg0) {
    int var_s0;

    var_s0 = FUN_00332860() & 0xFF;
    if ((var_s0 != 0) && (arg0 != 0)) {
        var_s0 = FUN_00332c40() & 0xFF;
    }
    ADXM_SetupThrd(0);
    ADXM_SetCbErr(FUN_003327b0, 0);
    FUN_002632c0();
    FUN_00280d48();
    return var_s0;
}

void FUN_00332cd0(void)
{
    ADXM_ExecVsyncFrame();
}

void igAdx_ExecServer(int) {
    ADXM_ExecMain();
    FUN_00282038();
}

void igAdx_SetPartitionCount(int arg0) {
    int temp_a0;
    int temp_s2;
    int var_a0;
    int var_s1;
    int var_s0;
    int var_v1;
    T_332d20 *object;

    temp_s2 = Memory_GetAllocatorByName(&DAT_004ffe68[0]);
    if (((int *)DAT_005875f0)[0] != 0) {
        if (g_adxPartitionCount[0] > 0) {
            var_s1 = 0;
            if (0 < g_adxPartitionCount[0]) {
                var_s0 = 0;
                do {
                    temp_a0 = *(int *)(((int *)DAT_005875f0)[0] + var_s0);
                    if (temp_a0 != 0) {
                        Memory_FreeBufferWithAllocator(temp_a0, temp_s2);
                    }
                    var_s1 += 1;
                    var_s0 += 4;
                } while (var_s1 < g_adxPartitionCount[0]);
            }
        }
        Memory_FreeBufferWithAllocator(((int *)DAT_005875f0)[0], temp_s2);
    }
    g_adxPartitionCount[0] = arg0;
    if (arg0 > 0) {
        ((int *)DAT_005875f0)[0] = Memory_AllocateAlignedWithAllocator(arg0 * 4, 0x10, temp_s2);
        var_v1 = 0;
        if (0 < g_adxPartitionCount[0]) {
            var_a0 = 0;
            do {
                var_v1 += 1;
                *(int *)(((int *)DAT_005875f0)[0] + var_a0) = 0;
                var_a0 += 4;
            } while (var_v1 < g_adxPartitionCount[0]);
        }
        object = ((T_332d20 * *)DAT_00587608)[0];
        if (object != 0) {
            --object->references;
            if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0) {
                igObject_Destroy(object);
            }
        }
        ((T_332d20 * *)DAT_00587608)[0] = (T_332d20 *)igStringRefList_Create(temp_s2);
    }
}

void igAdx_AddPartitionName(int arg0, char *arg1) {
    int v;
    int ok;
    SList *t;
    OList *t2;
    if (arg1 != 0) {
        char *r;
        if (arg1 == 0) {
            r = 0;
        } else {
            if (g_stringPool[0] == 0) {
                v = StringPool_Allocate(16);
                if (v != 0) v = StringPool_Construct(v);
                g_stringPool[0] = v;
            }
            r = StringPool_Intern(g_stringPool[0], arg1);
        }
        {
            StringRef name(r);
            StringList_AppendRetained(DAT_00587608[0], &name);
        }
    } else {
        SList *l;
        int n;
        int i;
        int *old;
        int **p;
        int *np;
        l = DAT_00587608[0];
        n = l->count;
        i = 0;
        if (0 < n) {
            do {
                p = &l->data[i];
                if (g_stringPool[0] == 0) {
                    v = StringPool_Allocate(16);
                    if (v != 0) v = StringPool_Construct(v);
                    g_stringPool[0] = v;
                }
                np = (int *)StringPool_Intern(g_stringPool[0], 0);
                old = *p;
                if (old != 0) {
                    int *hd = old - 2;
                    v = old[-1] - 1;
                    old[-1] = v;
                    if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
                }
                i++;
                *p = np;
            } while (i < n);
        }
        l->count = 0;
        ok = DAT_00587608[0]->count > 0;
        if (ok == 0) List_Reserve(DAT_00587608[0], 0, 4);
        t = DAT_00587608[0];
        if (t != 0) {
            t->references = t->references - 1;
            if (((unsigned long long)((long long)t->references << 0x29) >> 0x29) == 0)
                igObject_Destroy(t);
        }
        DAT_00587608[0] = 0;
        {
            OList *l2 = DAT_00587620[0];
            if (l2 != 0) {
                int n2 = l2->count;
                int i2;
                int m, j;
                for (i2 = 0; i2 < n2; i2++) {
                    Obj_332e90 *o = l2->data[i2];
                    if (o != 0) {
                        o->references = o->references - 1;
                        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0)
                            igObject_Destroy(o);
                    }
                }
                m = l2->count;
                for (j = 0; j < m; j++) l2->data[j] = 0;
                l2->count = 0;
                ok = DAT_00587620[0]->count > 0;
                if (ok == 0) List_Reserve(DAT_00587620[0], 0, 4);
                t2 = DAT_00587620[0];
                if (t2 != 0) {
                    t2->pad0[1] = t2->pad0[1] - 1;
                    if (((unsigned long long)((long long)t2->pad0[1] << 0x29) >> 0x29) == 0)
                        igObject_Destroy(t2);
                }
                DAT_00587620[0] = 0;
            }
        }
    }
}

void igAdx_SetInsideFiles(R_333230 *arg0) {
    R_333230 *old;
    if (arg0 != 0) {
        if (arg0 != 0) {
            arg0->rc = arg0->rc + 1;
        }
        old = ((R_333230 * *)DAT_00587620)[0];
        if (old != 0) {
            old->rc = old->rc - 1;
            if ((old->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        ((R_333230 * *)DAT_00587620)[0] = arg0;
    }
}

int igAdx_LoadPartition(int stream, const char *path, int mode, int length)
{
    int size;
    char *name;
    bool waiting;

    if (!GPR_00554de8) return 0;
    size = ((length + 1) * 2 + 282) & ~3;
    if (size > 0) {
        DAT_005875f0[0][stream] = ((void *)Memory_AllocateAlignedWithAllocator(size, 16, ((void *)Memory_GetAllocatorByName(((char *)DAT_004ffe68)))));
    }
    igAdx_AddPartitionName(stream, (char *)path);
    name = StringList_CopyRetained(((int *)DAT_00587608)[0], stream).p;
    FUN_00260de8(stream, name, mode, DAT_005875f0[0][stream]);
    waiting = true;
    do {
        switch (FUN_002612c0(stream)) {
        case 3:
            waiting = false;
            break;
        case 4:
            return 0;
        default:
            igAdx_ExecServer(0);
            break;
        }
        g_threadManager[0]->threads->data[0]->sleep(3333333);
    } while (waiting);
    return 1;
}

int FUN_00333440(const char *name) {
    int left;
    int right;
    char digits[16];
    char path[256];
    int close;
    unsigned int i;
    int k;
    int n;
    if (((PathEntryList * *)DAT_00587620)[0]) {
        close = -1;
        if (name[0] == '[') {
            for (i = 1; i < strlen(name); i++) {
                if (name[i] == ']') {
                    close = i + 1;
                    break;
                }
            }
            if (close != -1 && close >= 3) {
                PathEntry *entry;
                memset(digits, 0, 16);
                strncpy(digits, name + 1, 1);
                igStringObj_Set(DAT_005875e0[0], digits);
                FUN_0030b5f0(DAT_005875e0[0], &left);
                strncpy(digits, name + 3, close - 4);
                igStringObj_Set(DAT_005875e0[0], digits);
                FUN_0030b5f0(DAT_005875e0[0], &right);
                entry = ((PathEntryList * *)DAT_00587620)[0]->data[0];
                igNamedObject_SetName(entry, name);
                entry->left = left;
                entry->right = right;
                return 0;
            }
        }
        n = ((PathEntryList * *)DAT_00587620)[0]->count;
        igStringObj_Set(DAT_005875e0[0], name);
        igStringObj_ToLower(DAT_005875e0[0]);
        for (k = 1; k < n; k++) {
            FUN_00333630((S_333630 *)(((PathEntryList * *)DAT_00587620)[0]->data[k]), path);
            const char *text = DAT_005875e0[0]->text;
            text = (text == 0) ? g_stringObjEmptyText[0] : text;
            if (strcmp(text, path) == 0) {
                return k;
            }
        }
    }
    return -1;
}

void FUN_00333630(S_333630 *arg0, char *arg1) {
    int i;
    int off;
    if (arg1 != 0) {
        if (arg0->parents == 0) {
            strcpy(arg1, arg0->name ? arg0->name : (char *)&emptyString[0]);
            return;
        }
        *arg1 = 0;
        i = 0;
        if (0 < arg0->parents->count) {
            off = 0;
            do {
                N *nd = *(N **)((char *)arg0->parents->data + off);
                strcat(arg1, nd->name ? nd->name : (char *)&emptyString[0]);
                strcat(arg1, &DAT_004fff70[0]);
                i += 1;
                off += 4;
            } while (i < arg0->parents->count);
        }
        strcat(arg1, arg0->name ? arg0->name : (char *)&emptyString[0]);
    }
}

ObjectRefWord *FUN_00333760(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void FUN_003337e0(void)
{
}

void FUN_003337f0(void)
{
}
