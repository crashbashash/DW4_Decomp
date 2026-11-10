#include "dw4/reflected.h"

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

extern "C" {
void *FUN_001435c0(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int Gap__Core__igObject__vfunc_10(...);
void FUN_00300f50(...);
int *FUN_00300db0(...);
int FUN_0032d9b0(...);
int FUN_0032d6d0(...);
int FUN_0032d850(...);
int FUN_00145960(...);
int FUN_00145a10(...);
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
void List_Reserve(VoiceList *, int, int);
void List_Resize(VoiceList *, int, int);
extern int DAT_004d5f80[4];
extern int DAT_004d5f98[4];
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int DAT_0055f5b0[4];
extern AudioThread * DAT_0055f5b8[4];

void FUN_00144030(int *arg0, UploadContext *arg1, int arg2, int arg3, int arg4, int arg5, unsigned char arg6, int arg7, unsigned char arg8);

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
        FUN_0032d850(&sp4C, temp_s2, arg2 | 0x270000, FUN_00145960(arg1, temp_a2, temp_a2, g), 0, 0);
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
