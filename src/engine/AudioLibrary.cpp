#include "dw4/reflected.h"

union AudioContextProbe { int vt; char b[64]; };
struct RefCountBits { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct SourceListProbe { int *vt; char pad[28]; };
struct DW4SR4 { int w0; };

struct ContextView { char pad[8]; unsigned char f8; char pad9[3]; int f12; };

struct RefCountedList { int vt; unsigned int rc; };
struct SignedRefList { int w0; int refs; };

typedef struct AudioVoiceEntry {
    char pad0[8];
    unsigned char low : 5;
    unsigned char active : 1;
    unsigned char high : 2;
    char pad9[27];
} AudioVoiceEntry;

typedef struct AudioVoiceTable {
    char pad0[16];
    AudioVoiceEntry *entries;
} AudioVoiceTable;

typedef struct AudioVoiceHandle {
    char pad0[12];
    int voice;
} AudioVoiceHandle;

struct ThreadResult { int v; ThreadResult() {} };
struct ThreadRef { int word0; int references; };
class AudioThread { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual ThreadResult a92(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual ThreadResult a120(); virtual void d29(); virtual void d30(); virtual ThreadResult a132(void *); virtual void d32(); virtual ThreadResult a140(int); };

class DW4VC_184_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual int vX(); };
class DW4VCSR_128_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual DW4SR4 vX(); };
class DW4VCSR_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual DW4SR4 vX(int); };
class DW4VC_100_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(); };
class AllocatorAllocateSlot {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44();
    virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
    virtual void d50(); virtual void d51(); virtual void d52();
    virtual int Allocate(int size, int alignment);
};

struct VoiceFlags61 {
    char p[8];
    unsigned char a0:1; unsigned char a1:1; unsigned char a2:1; unsigned char a3:1; unsigned char a4:1; unsigned char a5:1; unsigned char a6:1; unsigned char a7:1;
    unsigned char b0:1; unsigned char b1:1; unsigned char b2:1; unsigned char b3:1; unsigned char b4:1; unsigned char b5:1; unsigned char b6:1; unsigned char b7:1;
    char rest[26];
};
struct VoiceTable61 { char p[16]; struct VoiceFlags61 *e; };

struct VoiceSlot { int f0; int f4; unsigned char used : 1; unsigned char rest : 7; char pad[3]; int f12; float f16; float f20; float f24; int pad2; int f32; };
struct VoiceSlotTable { char pad[8]; int cnt; int pad2; struct VoiceSlot *items; };

typedef struct { char p[8]; unsigned char b0 : 1; } VoiceUsedFlag;

struct Voice {
    unsigned int position;
    int f4;
    unsigned char used : 1;
    unsigned char stereo : 1;
    unsigned char seek : 1;
    unsigned char loop : 1;
    unsigned char reserved4 : 1;
    unsigned char reserved5 : 1;
    unsigned char playing : 1;
    unsigned char paused : 1;
    unsigned char reserved8 : 4;
    unsigned char dirty : 1;
    char pad[26];
};
struct VoiceTable { char pad[16]; struct Voice *items; };
struct PlayRequest { char pad[8]; float start; int channels; int pad16; int mode; };

typedef struct UploadEntry {
    int f0;
    int f4;
    unsigned char a0 : 2;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char a4 : 3;
    unsigned char b7 : 1;
    unsigned char c0 : 1;
    unsigned char c1 : 3;
    unsigned char c4 : 1;
    unsigned char c5 : 3;
    char pad[22];
} UploadEntry;
typedef struct UploadTable { char pad[16]; UploadEntry *tab; } UploadTable;
typedef struct UploadContext { char pad[12]; int h; } UploadContext;

typedef struct { char p[11]; unsigned char f:1; } B11;

typedef struct { char p[9]; unsigned char b0 : 1; unsigned char b1 : 1; unsigned char b2 : 1; unsigned char b3 : 1; unsigned char b4 : 1; unsigned char b5 : 1; unsigned char b6 : 1; unsigned char b7 : 1; unsigned char v : 5; } VoiceFlags42;

typedef struct VoiceFlags41 {
    char pad0[9];
    unsigned char a9 : 4;
    unsigned char f9 : 1;
    unsigned char c9 : 3;
    char pad10;
    unsigned char a11 : 4;
    unsigned char f11 : 1;
    unsigned char c11 : 3;
    char pad12[24];
} VoiceFlags41;
typedef struct VoiceTable41 { char pad[16]; VoiceFlags41 *arr; } VoiceTable41;

typedef struct VoiceFlags40 {
    char pad0[8];
    unsigned char a0 : 1;
    unsigned char a1 : 1;
    unsigned char a2 : 1;
    unsigned char a3 : 1;
    unsigned char a4 : 1;
    unsigned char a5 : 1;
    unsigned char a6 : 1;
    unsigned char a7 : 1;
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
    char pad10;
    unsigned char c0 : 1;
    unsigned char c1 : 1;
    unsigned char c2 : 1;
    unsigned char c3 : 1;
    unsigned char c4 : 1;
    unsigned char c5 : 1;
    unsigned char c6 : 1;
    unsigned char c7 : 1;
    int f12;
    char pad16[16];
    int next;
} VoiceFlags40;
typedef struct VoiceTable40 { char pad[16]; VoiceFlags40 *arr; } VoiceTable40;

typedef struct VoiceFlags43 {
    char pad0[8];
    unsigned char a8 : 5;
    unsigned char f8 : 1;
    unsigned char c8 : 2;
    char pad9[2];
    unsigned char a11 : 3;
    unsigned char f11 : 1;
    unsigned char c11 : 4;
    char pad12[20];
    int next;
} VoiceFlags43;
typedef struct VoiceTable43 { char pad[16]; VoiceFlags43 *arr; } VoiceTable43;

typedef struct AudioTableEntry {
    int word0;
    int word1;
    char unknown8[28];
} AudioTableEntry;

/* The entry base stays a byte pointer: the load-base-then-scale order needs byte-offset arithmetic. */
typedef struct AudioTableOwner {
    char unknown0[16];
    char *entries;
} AudioTableOwner;

struct RpcStatus { int value; bool operator!=(const RpcStatus &o) const { return value != o.value; } };
struct InitRef { int p0; int rc; };
struct VoiceList { char p[8]; int count; int cap; int data; };
struct InitContext { char p[12]; struct InitRef *conn; char q[8]; int f24; char r[4]; int f32; int f36; int f40; };

struct PanResult { int v; PanResult(int x) { v = x; } PanResult() {} };
struct VoiceFlags35 {
    char p[11];
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
    int w12;
    float g16;
    float g20;
    char tail[12];
};
struct VoiceTable35 { char p[16]; VoiceFlags35 *arr; };

class DW4VC_128_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(); };
class DW4VC_132_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(); };
class igPsx2AudioContextView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
    virtual void vfunc_44();
};

struct VoiceFlags57 { char p[9]; unsigned char bitA : 1; unsigned char bitB : 1; unsigned char bitC : 1; unsigned char bitD : 1; unsigned char bitE : 1; unsigned char bitF : 1; unsigned char bitG : 1; unsigned char bitH : 1; char q[26]; };
struct VoiceTable57 { char p[16]; struct VoiceFlags57 *arr; };
struct VoiceFlags58 { char p[9]; unsigned char b0 : 1; unsigned char b1 : 1; unsigned char b2 : 1; unsigned char b3 : 1; unsigned char b4 : 1; unsigned char b5 : 1; unsigned char b6 : 1; unsigned char b7 : 1; char q[26]; };
struct VoiceTable58 { char p[16]; struct VoiceFlags58 *arr; };
typedef struct { char p[9]; unsigned char b0 : 1; unsigned char b1 : 1; unsigned char b2 : 1; unsigned char b3 : 1; unsigned char b4 : 1; unsigned char b5 : 1; unsigned char b6 : 1; unsigned char b7 : 1; unsigned char v; unsigned char c0 : 1; unsigned char c1 : 1; unsigned char c2 : 1; } VoiceFlags37;
struct VoiceGain { char pad[16]; float f16; float f20; float f24; };
typedef struct VoiceState {
    char pad[8];
    unsigned char a0 : 1, a1 : 1, a2 : 1, a3 : 1, a4 : 1, a5 : 1, a6 : 1, a7 : 1;
    unsigned char b0 : 1, b1 : 1, b2 : 1, b3 : 1, b4 : 1, b5 : 1, b6 : 1, b7 : 1;
    unsigned char c;
} VoiceState;
typedef struct VoiceStateBits {
    unsigned char d0 : 1, d1 : 1, d2 : 1, d3 : 1, d4 : 1, d5 : 1, d6 : 1, d7 : 1;
    unsigned char e : 5, g : 3;
    short pad;
} VoiceStateBits;
typedef union VoiceStateWord { VoiceStateBits r; int i; } VoiceStateWord;
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };

extern "C" {
extern unsigned char g_AudioLibrary_registered;
extern igMetaObject *g_igAudioContext_metaObject[4];
extern igMetaObject *g_igPsx2AudioContext_metaObject[4];
extern igMetaObject *g_igPsx2AudioSourceList_metaObject[4];
extern int g_igDataList_metaObject[4];
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igAudioContext_className[];
extern char igAudioContext_GetPublishedMetaObject[];
extern char g_igPsx2AudioContext_callbackList[];
extern char igPsx2AudioContext_className[];
extern char igDataList_Register[];
extern char igPsx2AudioSourceList_className[];
extern int DAT_0055f540[4];
extern void *DAT_0055f550[4];
extern int DAT_00587040[4];
extern int DAT_00486cd8[4];
extern int DAT_00486ce0[4];
extern int DAT_00486ce8[4];
extern int DAT_00486cf0[4];
extern int DAT_00486d10[4];
extern int DAT_00486d40[4];
extern int DAT_00486d70[4];
extern int DAT_00486da0[4];
extern int DAT_00524a80[4];
extern int DAT_00524b80[4];
extern void *DAT_00586dc8[4];
extern void *DAT_0055f5d0[4];

int igMetaObject_CreateInstance(int, int);
int igMetaObject_Create(...);
int Memory_GetAllocatorBySelector(...);
void igMetaObject_RunStaticInit(void (*)(void));
int igMetaObject_RegisterClass(...);
int igMetaObject_CreateFields(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
int igObject_InitHeader(...);
int FUN_00100610(...);
int FUN_002d3890(...);
int FUN_00145d40(...);
int igUnsignedIntMetaField_GetDefaultDescriptor(...);
int FUN_002b7f80(...);
int FUN_002cfe50(...);
int FUN_0030e9b0(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int Gap__Core__igObject__vfunc_10(...);
void FUN_00300f50(...);
int *FUN_00300db0(...);
int FUN_0032d9b0(...);
int FUN_0032d6d0(...);
int FUN_0032d850(...);
void *FUN_002ba650(...);
ThreadRef *FUN_002b7f40(...);
int FUN_00113f20(...);
int sceSifAddCmdHandler(...);
int FUN_00113f78(...);
void FUN_0010b7d8(int, int);
void *memset(void *, int, unsigned int);
double floor(double);
int sceSifSearchModuleByName(int *);
RpcStatus FUN_0032cf50(int *, int, int, int);
int FUN_00301000(InitContext *);
int FUN_002cfe10(int);
RpcStatus FUN_0032d640(InitRef *, int);
void List_Resize(VoiceList *, int, int);
extern int DAT_004d5f80[4];
extern int DAT_004d5f98[4];
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int DAT_0055f5b0[4];
extern AudioThread * DAT_0055f5b8[4];
void List_Reserve(...);
void *FUN_001435c0(int arg0);
unsigned FUN_00145960(void *context, void *voice);
int FUN_00145a10(void *arg0, void *voice);

void FUN_00143010(void);
void igAudioContext_Register(void);
void thunk_igAudioContext_GetMetaObject(void);
void igAudioContext_InitFields(void);
void thunk_FUN_00143150(void);
igMetaObject *FUN_00143150(void);
void **FUN_00143250(void **arg0, short arg1);
void **FUN_001432d0(struct RefCountBits **self, short flag);
void **FUN_00143350(void **arg0, long long arg1);
void FUN_001433d0(void);
void igPsx2AudioContext_Register(void);
void igPsx2AudioContext_InitFields(void);
void FUN_00143690(void);
void igPsx2AudioSourceList_Register(void);
void thunk_igPsx2AudioSourceList_GetMetaObject(void);
int igDataList_GetPublishedMetaObject(void);
void FUN_00144030(int *arg0, UploadContext *arg1, int arg2, int arg3, int arg4, int arg5, unsigned char arg6, int arg7, unsigned char arg8);

void AudioLibrary_MarkRegistered(void) {
    if (g_AudioLibrary_registered == 0) {
        g_AudioLibrary_registered = 1;
    }
}

void FUN_00142f30(int arg0) {
    FUN_00143010();
    igMetaObject_CreateInstance(*(int *)0x55F540, arg0);
}

int FUN_00142f70(void) {
    if (DAT_0055f540[0] == 0) {
        DAT_0055f540[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f540[0];
}

igMetaObject *igAudioContext_GetMetaObject(void)
{
    igMetaObject *g = g_igAudioContext_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00143010();
    return g_igAudioContext_metaObject[0];
}

void FUN_00143010(void)
{
    igMetaObject_RunStaticInit(igAudioContext_Register);
}

void igAudioContext_Register(void) {
    AudioLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAudioContext_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAudioContext_GetMetaObject,
        igAudioContext_className,
        0xC, /* instance size */
        0,
        &igAudioContext_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAudioContext_GetMetaObject(void) {
    igAudioContext_GetMetaObject();
}

void igAudioContext_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055f540[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486cd8[0], 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486ce0[0], &DAT_00486ce8[0], &DAT_00486cf0[0], temp_s1);
    *(int *)((char *)(DAT_0055f540[0]) + 60) = (int)(thunk_FUN_00143150);
}

void thunk_FUN_00143150(void) {
    FUN_00143150();
}

igMetaObject *FUN_00143150(void)
{
    igMetaObject *meta = g_igPsx2AudioContext_metaObject[0];
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_001433d0();
end:
    return g_igPsx2AudioContext_metaObject[0];
}

int igPsx2AudioContext_GetVTable(void) {
    union AudioContextProbe u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00524a80[0];
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[48] = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00524a80[0];
    FUN_00143350((void **)&u.b[48], -1);
    FUN_00143350((void **)&u.b[20], -1);
    FUN_001432d0((struct RefCountBits **)&u.b[16], -1);
    FUN_00143250((void **)&u.b[12], -1);
    return t;
}

void **FUN_00143250(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_001432d0(struct RefCountBits **self, short flag) {
    struct RefCountBits *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) FUN_00100610(self);
    }
    return (void **)self;
}

void **FUN_00143350(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_001433d0(void)
{
    igMetaObject_RunStaticInit(igPsx2AudioContext_Register);
}

void igPsx2AudioContext_Register(void) {
    AudioLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2AudioContext_metaObject,
        igAudioContext_Register,
        igAudioContext_GetPublishedMetaObject,
        thunk_FUN_00143150,
        igPsx2AudioContext_className,
        sizeof(igPsx2AudioContext),                     /* Instance size. */
        igPsx2AudioContext_GetVTable,
        &igPsx2AudioContext_InitFields,
        0, /* extra callback item */
        g_igPsx2AudioContext_callbackList /* callback list */
    );
}

int FUN_00143460(void) {
    return DAT_0055f540[0];
}

void igPsx2AudioContext_InitFields(void) {
    /* matching construct: declaration-order sweep — this order sets the saved registers */
    void *temp_s1;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1_5;
    int temp_s2;
    void *temp_s1_4;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055f550[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486d10[0], 0xA);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002cfe50();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002b7f80();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00145d40();
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 0);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 2);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 0x30);
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igMemoryRefMetaField *)temp_s1_4)->_memType = igUnsignedIntMetaField_GetDefaultDescriptor();
    temp_s1_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    ((igObjectRefMetaField *)temp_s1_5)->_metaObject = FUN_00145d40();
    igMetaObject_NameFields(temp_s0, &DAT_00486d40[0], &DAT_00486d70[0], &DAT_00486da0[0], temp_s2);
    *(int *)((char *)(DAT_0055f550[0]) + 64) = (int)thunk_igAudioContext_GetMetaObject;
}

void *FUN_001435c0(int arg0) {
    FUN_00143690();
    return (void *)igMetaObject_CreateInstance(*(int *)0x55F5A8, arg0);
}

igMetaObject *igPsx2AudioSourceList_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2AudioSourceList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00143690();
    return g_igPsx2AudioSourceList_metaObject[0];
}

int igPsx2AudioSourceList_GetVTable(void) {
    struct SourceListProbe obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524b80[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00143690(void)
{
    igMetaObject_RunStaticInit(igPsx2AudioSourceList_Register);
}

void igPsx2AudioSourceList_Register(void) {
    AudioLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2AudioSourceList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igPsx2AudioSourceList_GetMetaObject,
        igPsx2AudioSourceList_className,
        0x14, /* instance size */
        igPsx2AudioSourceList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igPsx2AudioSourceList_GetMetaObject(void) {
    igPsx2AudioSourceList_GetMetaObject();
}

int igDataList_GetPublishedMetaObject(void){return g_igDataList_metaObject[0];}

void Gap__igPsx2AudioContext__vfunc_23(ContextView *arg0, int arg1) {
    if (arg0->f8 == 0 && arg1 == 1) {
        ((DW4VC_184_0 *)(arg0))->vX();
    }
    arg0->f8 = (unsigned char) (arg1 == 1);
}

void Gap__igPsx2AudioContext__vfunc_11(void) {
    extern struct RefCountedList * g_audioTableOwner[4];
    int temp_s0;
    struct RefCountedList *old;

    temp_s0 = igObject_GetAllocator();
    old = g_audioTableOwner[0];
    if (old != 0) {
        old->rc = old->rc - 1;
        if ((old->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    g_audioTableOwner[0] = (struct RefCountedList *)FUN_001435c0(temp_s0);
}

void FUN_00143800(AudioVoiceHandle *h)
{
    extern AudioVoiceTable *g_audioTableOwner;
    g_audioTableOwner->entries[h->voice].active = 0;
}

void FUN_00143840(void *arg0) {
    DW4SR4 sp1C;

    DAT_0055f5b0[0] = *(int *)((char *)(arg0) + 12) | 0x20000000;
    sp1C = ((DW4VCSR_128_0 *)(DAT_0055f5b8[0]))->vX();
}

void FUN_00143880(int (*arg0)(int)) {
    DW4SR4 sp2C;

loop_1:
    sp2C = ((DW4VCSR_132_1 *)(DAT_0055f5b8[0]))->vX((int)(1));
    arg0(DAT_0055f5b0[0]);
    goto loop_1;
}

void Gap__igPsx2AudioContext__vfunc_25(igPsx2AudioContext *context) {
    igObject *connection;
    int result;

    if (context->_connection != 0) {
        FUN_0032d9b0(&result, (igObject *)context->_connection, 0x30000, 1);
        connection = (igObject *)context->_connection;
        if (connection != 0) {
            connection->_refCount = connection->_refCount - 1;
            if ((connection->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(connection);
            }
        }
        context->_connection = 0;
    }
    if (context->_batchMemory != 0) {
        FUN_00300f50(context, context->_batchMemory);
        context->_batchMemory = 0;
    }
}

void Gap__igPsx2AudioContext__vfunc_12(void **arg0) {
    extern SignedRefList * g_audioTableOwner[4];
    SignedRefList *p;
    ((DW4VC_100_0 *)(arg0))->vX();
    p = g_audioTableOwner[0];
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long) ((long long) p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    g_audioTableOwner[0] = 0;
    Gap__Core__igObject__vfunc_10(arg0);
}
}

extern "C" {
static inline RpcStatus SendRpc(InitRef *conn, int command, int send, int sendSize, int reply, int replySize, int callback) {
    RpcStatus status;
    FUN_0032d6d0(&status, conn, command, send, sendSize, reply, replySize, callback);
    return status;
}

static inline RpcStatus CallRpc(InitRef *conn, int command, unsigned int value, int a, int b) {
    RpcStatus status;
    FUN_0032d850(&status, conn, command, value, a, b);
    return status;
}

void Gap__igPsx2AudioContext__vfunc_24(int *arg0, struct InitContext *arg1) {
    extern struct VoiceList *g_audioTableOwner[4];
    struct InitRef *o;
    int s0; int *buf; int n; struct VoiceList *l;
    if (sceSifSearchModuleByName(DAT_004d5f80) < 0) {
        if (FUN_0032cf50(DAT_004d5f98, 2, 0, 0) != *(RpcStatus *)DAT_004fb410) {
            *arg0 = DAT_004fb418[0];
            return;
        }
    }
    s0 = FUN_00301000(arg1);
    o = arg1->conn;
    if (o != 0) {
        o->rc = o->rc - 1;
        if (((unsigned long long)((long long)o->rc << 41) >> 41) == 0)
            igObject_Destroy(o);
    }
    arg1->conn = (struct InitRef *)FUN_002cfe10(s0);
    FUN_0032d640(arg1->conn, 0x12111);
    s0 = (int)FUN_00300db0(arg1, 0x10, 0x10);
    buf = (int *)s0;
    buf[0] = arg1->f24;
    buf[1] = arg1->f32;
    buf[2] = arg1->f36;
    n = arg1->f32 + arg1->f36;
    if (n >= g_audioTableOwner[0]->count) List_Reserve(g_audioTableOwner[0], n, 0x24);
    n = arg1->f32 + arg1->f36;
    l = g_audioTableOwner[0];
    if (n >= 0) {
        if (n <= l->cap) l->count = n;
        else List_Resize(l, n, 0x24);
    }
    n = g_audioTableOwner[0]->count;
    if (n != 0) memset((void *)g_audioTableOwner[0]->data, 0, n * 0x24);
    SendRpc(arg1->conn, 0x20000, s0, 0x10, 0, 0, 0);
    FUN_00300f50(arg1, s0);
    CallRpc(arg1->conn, 0x40000, 0x3FFF3FFFu, 0, 0);
    CallRpc(arg1->conn, 0x40001, 0x3FFF3FFF, 0, 0);
    arg1->f40 = (int)FUN_00300db0(arg1, 0x2000, 0x10);
    FUN_00113f20();
    sceSifAddCmdHandler(3, FUN_00143800, 0);
    FUN_00113f78();
    *arg0 = DAT_004fb410[0];
}
}

extern "C" {
void Gap__igPsx2AudioContext__vfunc_61(void *arg0, int arg1, int arg2) {
    extern struct VoiceTable61 *g_audioTableOwner[4];
    g_audioTableOwner[0]->e[arg1].a4 = arg2;
    g_audioTableOwner[0]->e[arg1].b4 = 1;
}

int Gap__igPsx2AudioContext__vfunc_28(void) {
    extern struct VoiceSlotTable *g_audioTableOwner[4];
    int cnt;
    struct VoiceSlotTable *t;
    int i;
    struct VoiceSlot *e;
    t = g_audioTableOwner[0];
    cnt = t->cnt;
    i = 0;
    for (; i < cnt; i++) {
        if (!t->items[i].used) {
            break;
        }
    }
    if (i == cnt) {
        return -1;
    }
    e = &t->items[i];
    memset(e, 0, 0x24);
    e->used = 1;
    e->f24 = 1.0f;
    e->f16 = 1.0f;
    e->f20 = 1.0f;
    e->f4 = 0x4000;
    e->f12 = 0x10000;
    e->f32 = -1;
    return i;
}

void Gap__igPsx2AudioContext__vfunc_29(int *arg0, void *arg1, int arg2) {
    extern void * g_audioTableOwner[4];
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    void *temp_s0;
    int temp_a3;
    int temp_a0;
    int sp3C;

    temp_a0 = *(int *)((char *)(g_audioTableOwner[0]) + 16);
    temp_s0 = (void *)(temp_a0 + (arg2 * 0x24));
    temp_a3 = *(int *)((char *)(temp_s0) + 32);
    if (temp_a3 >= 0) {
        *(int *)((char *)((temp_a0 + (temp_a3 * 0x24))) + 32) = -1;
    }
    FUN_0032d9b0(&sp3C, *(int *)((char *)(arg1) + 12), arg2 | 0x90000, 0);
    ((VoiceUsedFlag *)temp_s0)->b0 = 0;
    *arg0 = DAT_004fb410[0];
}

/* matching construct: a small sweep of spellings */
void Gap__igPsx2AudioContext__vfunc_30(void *self, int index, struct PlayRequest *req) {
    extern struct VoiceTable *g_audioTableOwner[4];
    struct Voice *v = &g_audioTableOwner[0]->items[index];
    if (req->channels > 1) {
        v->stereo = 1;
    }
    switch (req->mode) {
    case 1:
        v->paused = 1;
        v->loop = 1;
        break;
    case 2:
        v->loop = 1;
        v->playing = 1;
        break;
    case 3:
        v->seek = 1;
        v->paused = 1;
        break;
    case 4:
        v->seek = 1;
        v->position = (unsigned int)floor(req->start);
        v->playing = 1;
        break;
    case 0:
        return;
    default:
        return;
    }
    v->dirty = 1;
}

void Gap__igPsx2AudioContext__vfunc_47(int *a0, UploadContext *a1, int a2, int a3, int a4, int a5, int a6) {
    FUN_00144030(a0, a1, a2, a3, a4, a5, 1, a6, 1);
}

void Gap__igPsx2AudioContext__vfunc_31(int *a0, UploadContext *a1, int a2, int a3, int a4, int a5) {
    FUN_00144030(a0, a1, a2, a3, a4, a5, 0, 0, 1);
}

void FUN_00144030(int *arg0, UploadContext *arg1, int arg2, int arg3, int arg4, int arg5, unsigned char arg6, int arg7, unsigned char arg8) {
    extern UploadTable *g_audioTableOwner[4];
    unsigned char k;
    int v;
    int spAC;
    int *p;
    unsigned char s3;
    int *q;
    int spA8;
    UploadEntry *e;
    int spA4;

    s3 = arg6;
    if (arg3 & 0xF) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    e = (UploadEntry *)((char *)g_audioTableOwner[0]->tab + arg2 * 36);
    if (e->c0) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    p = FUN_00300db0(arg1, 16, 16);
    q = FUN_00300db0(arg1, 16, 16);
    if (e->b2) {
        k = 4;
    } else if (e->b3) {
        k = 2;
    } else {
        k = 24;
    }
    if (e->b7) {
        k |= 0x10;
    }
    p[0] = (e->f4 << 8) | (k & 0xFF);
    p[1] = arg5;
    p[2] = arg4;
    p[3] = arg3 & 0xDFFFFFFF;
    FUN_0010b7d8(arg3, arg3 + arg5);
    if (s3) {
        FUN_0032d6d0(&spAC, arg1->h, arg2 | 0x70000, p, 16, 0, 0, 0);
        if (arg8 != 0) {
            *q = 2;
        } else {
            *q = 1;
        }
    } else {
        FUN_0032d6d0(&spA8, arg1->h, arg2 | 0x70000, p, 16, q, 16, 0);
    }
    FUN_00300f50(arg1, p);
    e->c4 = 1;
    v = *q;
    if (v != -1) {
        if (v == 2) {
            e->b2 = 1;
            if (e->f0 != 0) {
                FUN_0032d850(&spA4, arg1->h, arg2 | 0x240000, e->f0, 0, 0);
            }
        } else {
            e->b3 = 1;
        }
        FUN_00300f50(arg1, q);
        *arg0 = DAT_004fb410[0];
    } else {
        FUN_00300f50(arg1, q);
        *arg0 = DAT_004fb418[0];
    }
}

void Gap__igPsx2AudioContext__vfunc_48(int *arg0, void *arg1, int arg2, int arg3) {
    /* matching construct: variant search — decl order [1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots in declaration order, the reverse of the 2001 default */
    int sp2C;
    int sp28;

    FUN_0032d850(&sp28, *(int *)((char *)(arg1) + 12), arg2 | 0x80000, arg3, &sp2C, 1);
    if (sp2C == 2) {
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb418[0];
    }
}

int Gap__igPsx2AudioContext__vfunc_51(igPsx2AudioContext *self) {
    int rpcStatus;
    int replyBuffer;
    void **allocator;

    allocator = (void **)(igObject_GetAllocator());
    replyBuffer = ((AllocatorAllocateSlot *)(allocator))->Allocate((int)(0x20), (int)(0x10));
    FUN_0032d6d0(&rpcStatus, self->_connection, 0x10000, 0, 0, replyBuffer, 0x20, 0);
    return replyBuffer;
}

void Gap__igPsx2AudioContext__vfunc_52(igPsx2AudioContext *arg0, int *arg1, int *arg2, int *arg3, int *arg4) {
    int a[4];
    int r;
    FUN_0032d6d0(&r, arg0->_connection, 0xE0000, 0, 0, a, 0x20, 0);
    if (arg1 != 0) {
        *arg1 = a[0];
    }
    if (arg2 != 0) {
        *arg2 = a[1];
    }
    if (arg3 != 0) {
        *arg3 = a[2];
    }
    if (arg4 != 0) {
        *arg4 = a[3];
    }
}

void Gap__igPsx2AudioContext__vfunc_34(int *arg0, void *arg1, int arg2, float fparg0) {
    extern void * g_audioTableOwner[4];
    int sp4C;
    int temp_s2;
    void *temp_a2;
    void *g;

    g = g_audioTableOwner[0];
    temp_a2 = (void *)(*(int *)((char *)(g) + 16) + (arg2 * 0x24));
    *(float *)((char *)(temp_a2) + 24) = fparg0;
    if (*(unsigned char *)((char *)(arg1) + 8) != 0) {
        temp_s2 = *(int *)((char *)(arg1) + 12);
        FUN_0032d850(&sp4C, temp_s2, arg2 | 0x270000, FUN_00145960(arg1, temp_a2), 0, 0);
    } else {
        ((B11 *)temp_a2)->f = 1;
    }
    *arg0 = DAT_004fb410[0];
}
}

extern "C" {
PanResult Gap__igPsx2AudioContext__vfunc_35(char *arg1, int arg2, float fparg0) {
    extern VoiceTable35 *g_audioTableOwner[4];
    PanResult status;
    VoiceFlags35 *e;
    int s2;

    e = g_audioTableOwner[0]->arr + arg2;
    if (fparg0 == 0.0f) {
        e->g16 = 1.0f;
        e->g20 = 1.0f;
    } else if (fparg0 < 0.0f) {
        e->g16 = 1.0f;
        e->g20 = 1.0f + fparg0;
    } else {
        e->g20 = 1.0f;
        e->g16 = 1.0f - fparg0;
    }
    if (*(unsigned char *)(arg1 + 8) != 0) {
        s2 = *(int *)(arg1 + 12);
        FUN_0032d850(&status, s2, arg2 | 0x270000, FUN_00145960(arg1, e), 0, 0);
    } else {
        e->b0 = 1;
    }
    return PanResult(DAT_004fb410[0]);
}
}

extern "C" {
void Gap__igPsx2AudioContext__vfunc_36(int *arg0, ContextView *arg1, int arg2, float arg3) {
    extern VoiceTable40 *g_audioTableOwner[4];
    int sp8C;
    VoiceFlags40 *e;
    int whole;
    int packed;

    e = &g_audioTableOwner[0]->arr[arg2];
    if (e->a3) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    whole = (int)floor(arg3);
    arg3 = arg3 - (float)floor(arg3);
    packed = (whole << 16) | (int)((double)0xffff * arg3);
    e->f12 = packed;
    if (arg1->f8 != 0) {
        FUN_0032d850(&sp8C, arg1->f12, arg2 | 0x250000, packed, 0, 0);
    } else {
        e->c1 = 1;
    }
    *arg0 = DAT_004fb410[0];
}

void Gap__igPsx2AudioContext__vfunc_42(int arg0, int arg1, unsigned char arg2) {
    extern void * g_audioTableOwner[4];
    VoiceFlags42 *p;
    p = (VoiceFlags42 *)(*(int *)((char *)(g_audioTableOwner[0]) + 16) + arg1 * 0x24);
    if ((p->b3 != arg2) && ((p->b1 == 0) || (p->b4 != 0))) {
        p->b3 = arg2;
        p->b4 = 1;
    }
}

void Gap__igPsx2AudioContext__vfunc_49(igPsx2AudioContext *arg0, int arg1, int arg2) {
    extern void * g_audioTableOwner[4];
    int sp1C;
    *(int *)((char *)((*(int *)((char *)(g_audioTableOwner[0]) + 16) + (arg1 * 0x24))) + 32) = arg2;
    *(int *)((char *)((*(int *)((char *)(g_audioTableOwner[0]) + 16) + (arg2 * 0x24))) + 32) = arg1;
    FUN_0032d850(&sp1C, arg0->_connection, arg1 | 0x2B0000, arg2, 0, 1);
}

void Gap__igPsx2AudioContext__vfunc_41(ContextView *arg0, int arg1) {
    extern VoiceTable41 *g_audioTableOwner[4];
    int sp4C;
    int temp_s2;
    VoiceFlags41 *temp_s0;

    temp_s0 = &g_audioTableOwner[0]->arr[arg1];
    if (arg0->f8 == 0) {
        temp_s0->f11 = 1;
        return;
    }
    temp_s2 = arg0->f12;
    FUN_0032d850(&sp4C, temp_s2, arg1 | 0xD0000, FUN_00145a10(arg0, temp_s0), 0, 1);
    temp_s0->f9 = 0 & 1;
}

void Gap__igPsx2AudioContext__vfunc_40(ContextView *arg0, int arg1) {
    extern VoiceTable40 *g_audioTableOwner[4];
    int sp40[5];
    int sp5C; /* matching construct: declaration order — the two status words are declared high slot first so the unit compiler (combat build) assigns sp+0x5c/sp+0x58 as retail does */
    int sp58;
    VoiceFlags40 *e;
    VoiceFlags40 *e2;
    int idx;

    e = &g_audioTableOwner[0]->arr[arg1];
    if (e->a5 == 0 || e->b6 != 0) {
        e->a5 = 1;
        e->b6 = 0 & 1;
        idx = e->next;
        if (idx >= 0) {
            e2 = &g_audioTableOwner[0]->arr[idx];
            e2->a5 = 1;
            e2->b6 = 0 & 1;
        }
        if (arg0->f8 == 0) {
            e->c3 = 1;
            return;
        }
        sp40[0] = FUN_00145960(arg0, e);
        sp40[1] = e->f12;
        if (e->b4 != 0) {
            sp40[2] = FUN_00145a10(arg0, e);
            FUN_0032d6d0(&sp5C, arg0->f12, arg1 | 0x200000, sp40, 0x10, 0, 0, 0);
            e->b4 = 0 & 1;
            return;
        }
        FUN_0032d6d0(&sp58, arg0->f12, arg1 | 0x2a0000, sp40, 0x10, 0, 0, 0);
    }
}

void Gap__igPsx2AudioContext__vfunc_43(ContextView *arg0, int arg1) {
    extern VoiceTable43 *g_audioTableOwner[4];
    int sp1C;
    VoiceFlags43 *e;
    VoiceFlags43 *e2;
    int idx;

    e = &g_audioTableOwner[0]->arr[arg1];
    e->f8 = 0 & 1;
    idx = e->next;
    if (idx >= 0) {
        e2 = &g_audioTableOwner[0]->arr[idx];
        e2->f8 = 0 & 1;
    }
    if (arg0->f8 != 0) {
        FUN_0032d9b0(&sp1C, arg0->f12, arg1 | 0x210000, 0);
        return;
    }
    e->f11 = 1;
}

void Gap__igPsx2AudioContext__vfunc_50(ContextView *arg0, int arg1) {
    extern VoiceTable40 *g_audioTableOwner[4];
    int sp1C;
    VoiceFlags40 *e;
    VoiceFlags40 *e2;
    int idx;

    e = &g_audioTableOwner[0]->arr[arg1];
    /* matching construct: spelling sweep — the redundant !e->a5 test keeps retail's second branch on the same flag */
    if (!(e->a5 || (!e->a5 && e->c3))) {
        return;
    }
    e->b6 = 1;
    idx = e->next;
    if (idx >= 0) {
        e2 = &g_audioTableOwner[0]->arr[idx];
        e2->b6 = 1;
    }
    if (arg0->f8 != 0) {
        FUN_0032d9b0(&sp1C, arg0->f12, arg1 | 0x2d0000, 0);
    } else {
        e->c5 = 1;
    }
}

void Gap__igPsx2AudioContext__vfunc_53(int unusedReceiver, int entryIndex, int value) {
    extern AudioTableOwner *g_audioTableOwner[4];
    if (!(value & 0x3F)) {
        ((AudioTableEntry *)(g_audioTableOwner[0]->entries + entryIndex * 0x24))->word1 = value & ~0x3F;
    }
}

void Gap__igPsx2AudioContext__vfunc_54(igPsx2AudioContext *arg0, int arg1) {
    ThreadRef *s0;
    ThreadRef *a0;
    AudioThread *p;
    if (arg0->_streamingThread == 0) {
        p = (AudioThread *)FUN_002ba650(0);
        DAT_0055f5b8[0] = p;
        p->a92();
        DAT_0055f5b8[0]->a132((void *)1);
        s0 = FUN_002b7f40(0);
        if (s0 != 0) {
            s0->references = s0->references + 1;
        }
        a0 = (ThreadRef *)arg0->_streamingThread;
        if (a0 != 0) {
            --a0->references;
            if (((unsigned long long)(long long)a0->references & 0x7fffffULL) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->_streamingThread = (int)s0;
        ((AudioThread *)arg0->_streamingThread)->a132((void *)&FUN_00143880);
        ((AudioThread *)arg0->_streamingThread)->a140(arg1);
        ((AudioThread *)arg0->_streamingThread)->a120();
        FUN_00113f20();
        sceSifAddCmdHandler(0, &FUN_00143840, &DAT_0055f5b0[0]);
        FUN_00113f78();
    }
}
}

extern "C" {
void Gap__Core__igPsx2Thread__vfunc_35(int *arg0, void *arg1, int arg2) {
    if (((DW4VC_128_0 *)(((char *)(arg1) + 0)))->vX() == 0) {
        *(int *)((char *)(arg1) + 28) = arg2;
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb418[0];
    }
}

void Gap__Core__igPsx2Thread__vfunc_33(int *arg0, void *arg1, int arg2) {

    if (((DW4VC_128_0 *)(((char *)(arg1) + 0)))->vX() == 0) {
        *(int *)((char *)(arg1) + 40) = arg2;
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb418[0];
    }
}

int Gap__igPsx2AudioContext__vfunc_55(void **self, int value) {
    return (int)FUN_00300db0(self, value, ((DW4VC_132_0 *)(self))->vX()) | 0x20000000;
}

int Gap__igPsx2AudioContext__vfunc_33(igPsx2AudioContext *self) {
    return 0x10;
}

void Gap__igPsx2AudioContext__vfunc_56(int arg0, int arg1) {
    FUN_00300f50(arg0, (arg1 & 0xDFFFFFFF));
}

void Gap__igPsx2AudioContext__vfunc_57(int arg0, int arg1) {
    ((struct VoiceTable57 *)DAT_0055f5d0[0])->arr[arg1].bitA = 1;
    ((struct VoiceTable57 *)DAT_0055f5d0[0])->arr[arg1].bitE = 1;
}

void Gap__igPsx2AudioContext__vfunc_58(int arg0, int arg1) {
    ((struct VoiceTable58 *)DAT_0055f5d0[0])->arr[arg1].b1 = 1;
    ((struct VoiceTable58 *)DAT_0055f5d0[0])->arr[arg1].b4 = 1;
}

void Gap__igPsx2AudioContext__vfunc_59(void *arg0, int arg1, int arg2) {
    ((struct VoiceTable61 *)DAT_0055f5d0[0])->e[arg1].b2 = arg2;
    ((struct VoiceTable61 *)DAT_0055f5d0[0])->e[arg1].b4 = 1;
    ((struct VoiceTable61 *)DAT_0055f5d0[0])->e[arg1].b5 = 1;
}

void Gap__igPsx2AudioContext__vfunc_60(int arg0, int arg1, int arg2, int arg3) {
    int temp_v1;

    temp_v1 = arg1 * 0x24;
    ((VoiceFlags42 *)(*(int *)((char *)(DAT_0055f5d0[0]) + 16) + temp_v1))->b2 = arg2;
    ((VoiceFlags42 *)(*(int *)((char *)(DAT_0055f5d0[0]) + 16) + temp_v1))->v = arg3;
    ((VoiceFlags42 *)(*(int *)((char *)(DAT_0055f5d0[0]) + 16) + temp_v1))->b5 = 1;
    ((VoiceFlags42 *)(*(int *)((char *)(DAT_0055f5d0[0]) + 16) + temp_v1))->b4 = 1;
}

void Gap__igPsx2AudioContext__vfunc_37(int *arg0, void *arg1, int arg2, int arg3) {
    int sp;
    VoiceFlags37 *p;
    p = (VoiceFlags37 *)(*(int *)((char *)(DAT_0055f5d0[0]) + 16) + (arg2 * 0x24));
    if (p->b1 != 0) {
        *arg0 = DAT_004fb410[0];
        return;
    }
    if (*(unsigned char *)((char *)arg1 + 8) != 0) {
        FUN_0032d850(&sp, *(int *)((char *)(arg1) + 12), arg2 | 0x260000, arg3, 0, 0);
    } else {
        *(int *)((char *)p + 28) = arg3;
        p->c2 = 1;
    }
    *arg0 = DAT_004fb410[0];
}

void Gap__igPsx2AudioContext__vfunc_44(igPsx2AudioContext *self) {
}

void Gap__igPsx2AudioContext__vfunc_45(igPsx2AudioContextView *self)
{
    self->vfunc_44();
}

int Gap__igPsx2AudioContext__vfunc_38(igPsx2AudioContext *arg0, int arg1) {
    int sp1C;
    int sp18;

    FUN_0032d850(&sp18, arg0->_connection, arg1 | 0xB0000, 0, &sp1C, 0);
    return sp1C;
}

int Gap__igPsx2AudioContext__vfunc_39(void *arg0, int arg1) {
    return ((unsigned long long) ((long long) *(unsigned char *)((char *)((*(int *)((char *)(DAT_0055f5d0[0]) + 16) + (arg1 * 0x24))) + 8) << 0x3A) >> 0x3F) != 0;
}

unsigned FUN_00145960(void *context, void *voice) {
    struct VoiceGain *arg1 = (struct VoiceGain *)voice;
    int k = 0x3FFF;
    float s = (float)k * arg1->f24;
    unsigned x = (unsigned)(s * arg1->f16);
    unsigned y = (unsigned)(s * arg1->f20);
    return (x << 16) | y;
}

int FUN_00145a10(void *arg0, void *voice) {
    VoiceState *a = (VoiceState *)voice;
    VoiceStateWord u;
    u.r.d0 = a->a6;
    u.r.d1 = a->a1;
    u.r.d2 = a->b3;
    u.r.d3 = a->a4;
    u.r.d4 = a->b0;
    u.r.d5 = a->b1;
    u.r.d6 = a->b5;
    u.r.d7 = a->b2;
    u.r.e = a->c;
    return u.i;
}

igMetaObject *Gap__igPsx2AudioContext__vfunc_22(void)
{
    return g_igPsx2AudioContext_metaObject[0];
}

void Gap__igPsx2AudioContext__vfunc_26(igPsx2AudioContext *self, igObject *window) {
    igObject *previousWindow;
    if (window != 0) {
        window->_refCount = window->_refCount + 1;
    }
    previousWindow = (igObject *)(self->_window);
    if (previousWindow != 0) {
        previousWindow->_refCount = previousWindow->_refCount - 1;
        if ((previousWindow->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previousWindow);
        }
    }
    self->_window = (int)window;
}

int Gap__igPsx2AudioContext__vfunc_27(igPsx2AudioContext *self) {
    return self->_window;
}

igMetaObject *Gap__igPsx2AudioSourceList__vfunc_22(void)
{
    return g_igPsx2AudioSourceList_metaObject[0];
}

#define AUDIO_SOURCE_ENTRY_SIZE 0x24
int Gap__igPsx2AudioSourceList__vfunc_23(igPsx2AudioSourceList *self) {
    return AUDIO_SOURCE_ENTRY_SIZE;
}

void Gap__igPsx2AudioSourceList__vfunc_18(igPsx2AudioSourceList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve(self, count, 0x24);
    }
}

O *FUN_00145c60(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}
}
