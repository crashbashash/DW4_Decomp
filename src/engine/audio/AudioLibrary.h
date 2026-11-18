#ifndef DW4_AUDIO_LIBRARY_H
#define DW4_AUDIO_LIBRARY_H

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/audio/igAudioContext.h"

union AudioContextProbe { int vt; char b[64]; };
struct SourceListProbe { int *vt; char pad[28]; };
struct DW4SR4 { int w0; };

struct ContextView { char pad[8]; unsigned char f8; char pad9[3]; int f12; };


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
    unsigned char a4 : 2;
    unsigned char b6 : 1;
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

struct InitRef { int p0; int rc; };
struct VoiceList { char p[8]; int count; int cap; int data; };
struct InitContext { char p[12]; struct InitRef *conn; char q[8]; int f24; char r[4]; int f32; int f36; int f40; };

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
class DW4VC_132_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual unsigned short vX(); };
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


extern igSmartPointer<igPsx2AudioSourceList> g_audioTableOwner;

#include "dw4/core/igObject.h"
#include "dw4/core/igDataLists.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObjectSystem.h"
#include "dw4/core/igMetaObject.h"
#include "dw4/core/igThread.h"
#include "dw4/sony/libkernl.h"
#include <string.h>
extern "C" {
#include "dw4/sony/sif.h"
}
#include <math.h>
#include "dw4/core/igResult.h"
extern "C" {
class igMemoryPoolView;
#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/core/igMemoryRefMetaField.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igRawRefMetaField.h"
#include "dw4/core/igUnsignedIntMetaField.h"
#include "dw4/core/igPsx2File.h"
#include "dw4/core/igSemaphore.h"
#include "dw4/sony/sifdev.h"
#include "dw4/core/igPsx2IopRpcConnection.h"
void igWindow_EnsureRegistered(void);
igMetaObject *igAudioContext_GetPublishedMetaObject(void);
extern int g_igPsx2AudioContext_vtable[4];
extern int g_igPsx2AudioSourceList_vtable[4];

int igWindow_GetOrCreateMetaObject(...);
int FUN_00301000(InitContext *);
void *igPsx2AudioSourceList_Create(igMemoryPoolView *pool);
unsigned FUN_00145960(void *context, void *voice);
int FUN_00145a10(void *arg0, void *voice);

CallbackArray *igAudioContext_Register(void);
void igAudioContext_GetMetaObjectFunction(void);
void igAudioContext_InitFields(void);
void igPsx2AudioContext_GetMetaObjectFunction(void);
igMetaObject *igPsx2AudioContext_GetMetaObject(void);
void **FUN_00143250(void **arg0, short arg1);
void **igSmartPointer_igWindow_Destruct(void **arg0, long long arg1);
void igPsx2AudioContext_EnsureRegistered(void);
CallbackArray *igPsx2AudioContext_Register(void);
void igPsx2AudioContext_InitFields(void);
void igPsx2AudioSourceList_EnsureRegistered(void);
CallbackArray *igPsx2AudioSourceList_Register(void);
void igPsx2AudioSourceList_GetMetaObjectFunction(void);
void FUN_00144030(int *arg0, UploadContext *arg1, int arg2, int arg3, int arg4, int arg5, unsigned char arg6, int arg7, unsigned char arg8);

#endif
