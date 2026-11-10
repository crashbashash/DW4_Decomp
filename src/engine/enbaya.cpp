extern "C" {

struct TripleVectorState;
void *FUN_00280240(unsigned int sz, void *p);
void FUN_0027eed0(struct TripleVectorState *o);
int FUN_0027f1c0(int *arg0);
int FUN_0027f200(void *arg0);
int FUN_0027f240(void *arg0);
int FUN_0027f280(int *a);
int FUN_0027f2d0(int *sizes);
int FUN_0027f310(void *arg0);
struct S;
void FUN_002800e0(struct S *s);
int FUN_00280a00();
struct S;
void FUN_0027f5c0(struct S *s, float t);
void FUN_0027f410(struct S *s, int count, float scale, int forward, float time);
void FUN_0027f510(struct S *s, int count, int keys, float scale);

typedef struct EnbayaSlot { unsigned char data[32]; } EnbayaSlot;
typedef struct EnbayaSlotGroup { EnbayaSlot slots[3]; } EnbayaSlotGroup;

typedef struct EnbayaContext {
    int f0;
    float end;                   /* +4 */
    float start;                 /* +8 */
    char pad12[4];
    EnbayaSlotGroup *groups;     /* +16 */
    char pad20[149];
    unsigned char slot;          /* +169 */
    unsigned char pad170;
    unsigned char external;      /* +171 */
    char pad172[4];
    EnbayaSlotGroup local[1];    /* +176 */
} EnbayaContext;

typedef struct EnbayaReader {
    signed char *codes;
    signed char *bytes;
    short *shorts;
    int *words;
    signed char shift;
} EnbayaReader;
typedef struct EnbayaKey { char _pad0[64]; float values[7]; char _pad92[4]; } EnbayaKey;
typedef struct EnbayaTrack { char _pad0[16]; EnbayaKey *keys; } EnbayaTrack;

typedef struct EnbayaDeltaReader {
    signed char *codes;
    signed char *nibbles;
    signed char *bytes;
    short *shorts;
    int *words;
    signed char shift;
    signed char nibbleShift;
} EnbayaDeltaReader;
typedef struct EnbayaDeltaKey { char _pad0[64]; float values[7]; unsigned char mask; char _pad93[3]; } EnbayaDeltaKey;
typedef struct EnbayaDeltaTrack { char _pad0[16]; EnbayaDeltaKey *keys; } EnbayaDeltaTrack;

typedef struct EnbayaMaskReader {
    signed char *codes;
    unsigned char *bytes;
    unsigned short *shorts;
    unsigned int *words;
    signed char shift;
} EnbayaMaskReader;
typedef struct EnbayaMaskKey { char _pad0[92]; unsigned char mask; char _pad93[3]; } EnbayaMaskKey;
typedef struct EnbayaMaskRun { int remaining; int consumed; } EnbayaMaskRun;

extern int DAT_004bb0c0[4];
extern int DAT_004bb0d0[2];
extern int DAT_004bb0e0[4];
extern int DAT_004bb0f0[4];
extern int DAT_004f2740[4];
extern int DAT_004f2750[16];

}

extern "C" int FUN_0027ede0(int arg0) {
    return ((arg0 - 1) * 0x60) + 0x110;
}

struct E { char pad[0x60]; E() {} };
struct O {
    int f0, f4, f8, f12; void *f16; int f20, f24, f28, f32, f36, f40, f44, f48;
    int f52, f56, f60; int f64; char f68; char p69[3]; int f72, f76, f80, f84, f88;
    char f92, f93; char p94[2]; int f96, f100, f104; int f108; char f112; char p113[55];
    char f168, f169, f170, f171; int f172; E e[1];
    static void *operator new(unsigned sz, void *p) { return FUN_00280240(sz, p); }
    O() : f40(-1), f44(-1), f52(0), f56(0), f60(0), f68(0), f72(0), f76(0), f80(0), f84(0), f92(0), f93(0), f96(0), f100(0), f104(0), f112(0) {
        f12 = 0; f32 = 0; f36 = 0;
    }
};
extern "C" void FUN_0027ee00(void *pool, int n) {
    O *o = new (pool) O;
    o->f169 = 0; o->f16 = &o->e; o->f170 = 0; o->f171 = 0;
    o->f28 = n * 0x60;
}

struct TripleVectorState {
  char pad[52];
  int v52[4]; char f68; char pad2[3];
  int v72[5]; char f92; char f93; char pad3[2];
  int v96[4]; char f112; char pad4[3];
  int s116[4]; int s132[5]; int s152[4];
};
void FUN_0027eed0(struct TripleVectorState *o){
{ int a, b, c, d;
 d=o->s116[3];
 c=o->s116[2];
 b=o->s116[1];
 a=o->s116[0];
 o->v52[0]=a;
 o->v52[1]=b;
 o->v52[2]=c;
 o->v52[3]=d;
 o->f68=0; }
{ int a, b, c, d, e;
 e=o->s132[4];
 d=o->s132[3];
 c=o->s132[2];
 b=o->s132[1];
 a=o->s132[0];
 o->v72[0]=a;
 o->v72[1]=b;
 o->v72[2]=c;
 o->v72[3]=d;
 o->v72[4]=e;
 o->f92=0; o->f93=0; }
{ int a, b, c, d;
 d=o->s152[3];
 c=o->s152[2];
 b=o->s152[1];
 a=o->s152[0];
 o->v96[0]=a;
 o->v96[1]=b;
 o->v96[2]=c;
 o->v96[3]=d;
 o->f112=0; }
}

struct P {
  virtual void d0();
  virtual int v1();
  int p4; float f8, f12; int f16, f20, f24, f28, f32, f36, f40, f44, f48, f52, f56, f60, f64, f68, f72, f76;
};
struct S {
  int f0; float f4; float f8; P *f12; int f16; int f20; int f24; int f28; float f32; float f36;
  EnbayaMaskRun run; int f48; EnbayaReader reader; EnbayaDeltaReader delta; EnbayaMaskReader mask; int f116, f120, f124, f128, f132, f136, f140, f144, f148, f152, f156, f160, f164; unsigned char f168; char f169; char f170; unsigned char f171;
};
extern "C" void FUN_0027ef50(S *s, P *p, unsigned char c)
{
  P *q;
  s->f32 = -1.0f;
  s->f0 = -1;
  s->f4 = -1.0f;
  s->f8 = -1.0f;
  s->f12 = p;
  s->f36 = 1.0f / (float)s->f12->f16;
  s->f169 = 0;
  s->f20 = s->f12->v1();
  q = s->f12;
  s->f48 = FUN_0027f310(q) - -q->f60;
  s->f116 = s->f12->f76 - -s->f12->f32 - -s->f12->f52 - -s->f12->f68 - -s->f12->f28 - -s->f12->f48 - -s->f12->f64;
  s->f120 = s->f12->f76 - -s->f12->f32 - -s->f12->f52 - -s->f12->f68 - -s->f12->f28 - -s->f12->f48 - -s->f12->f64 - -s->f12->f20;
  s->f124 = s->f12->f76 - -s->f12->f32 - -s->f12->f52 - -s->f12->f68;
  s->f128 = s->f12->f76;
  q = s->f12;
  s->f132 = FUN_0027f2d0((int *)q) - -q->f24;
  q = s->f12;
  s->f136 = FUN_0027f280((int *)q) - -q->f36;
  q = s->f12;
  s->f140 = FUN_0027f240(q) - -q->f40;
  s->f144 = s->f12->f76 - -s->f12->f32 - -s->f12->f52 - -s->f12->f68 - -s->f12->f28;
  s->f148 = s->f12->f76 - -s->f12->f32;
  q = s->f12;
  s->f152 = FUN_0027f200(q) - -q->f44;
  q = s->f12;
  s->f156 = FUN_0027f1c0((int *)q) - -q->f56;
  s->f160 = s->f12->f76 - -s->f12->f32 - -s->f12->f52 - -s->f12->f68 - -s->f12->f28 - -s->f12->f48;
  s->f164 = s->f12->f76 - -s->f12->f32 - -s->f12->f52;
  s->f24 = c;
  FUN_002800e0(s);
  FUN_0027eed0((struct TripleVectorState *)s);
}

extern "C" {

int FUN_0027f1c0(int *arg0) {
    int r = FUN_0027f240(arg0);
    int a = arg0[10];
    int b = arg0[11];
    r = r + a;
    r = r + b;
    return r;
}

int FUN_0027f200(void *arg0) {
    int r = FUN_0027f280((int *)arg0);
    r += *(int *)((char *)(arg0) + 36);
    r += *(int *)((char *)(arg0) + 40);
    return r;
}

int FUN_0027f240(void *arg0)
{
  unsigned int new_var3;
  int new_var2;
  int new_var5;
  char *new_var;
  char *new_var4;
  new_var5 = FUN_0027f2d0((int *)arg0);
  new_var4 = (char *) arg0;
  new_var = new_var4;
  new_var3 = new_var5 + (*((int *) (new_var + 24)));
  ;
  return new_var3 + (*((int *) (new_var4 + 36)));
}

int FUN_0027f280(int *a) { return a[19] - -a[8] - -a[13] - -a[17] - -a[7] - -a[12] - -a[16] - -a[5] - -a[6]; }

int FUN_0027f2d0(int *sizes) {
    int a = sizes[19] + sizes[8];
    int b = a + sizes[13];
    int c = b + sizes[17];
    int d = c + sizes[7];
    int e = d + sizes[12];
    int f = e + sizes[16];
    return f + sizes[5];
}

int FUN_0027f310(void *arg0)
{
  int new_var2;
  int *new_var;
  new_var = (int *) (((char *) arg0) + (44 & 0xFFFFFFFFFFFFFFFF));
  new_var2 = FUN_0027f200(arg0);
  new_var2 = new_var2 + (*new_var);
  return new_var2 + (*((int *) (((char *) arg0) + 56)));
}

EnbayaSlot *FUN_0027f350(EnbayaContext *ctx, int group) {
    if (ctx->external) {
        return &ctx->groups[group].slots[ctx->slot];
    }
    return &ctx->local[group].slots[ctx->slot];
}

EnbayaSlot *FUN_0027f3b0(EnbayaContext *ctx, int group) {
    if (ctx->external) {
        return &ctx->groups[group].slots[ctx->slot ^ 1];
    }
    return &ctx->local[group].slots[ctx->slot ^ 1];
}

void FUN_0027fb50(EnbayaTrack *track, int count, EnbayaReader *reader);
void FUN_0027fc70(EnbayaDeltaTrack *track, int count, EnbayaDeltaReader *reader);
void FUN_0027fe90(EnbayaDeltaTrack *track, int count, EnbayaDeltaReader *reader);
void FUN_002800c0(void);
void FUN_002800d0(S *s);
void FUN_00280260(EnbayaMaskRun *run, EnbayaMaskReader *reader);
void FUN_00280330(EnbayaMaskRun *run, EnbayaMaskKey *keys, int count, EnbayaMaskReader *reader);
void FUN_002805a0(EnbayaMaskRun *run, EnbayaMaskKey *keys, int count, EnbayaMaskReader *reader);
static inline int readRunLength(EnbayaMaskReader *r) {
    signed char code;
    int value;
    if (r->shift == 4) {
        r->shift = 0;
        r->codes++;
    }
    code = (*r->codes >> DAT_004bb0f0[r->shift]) & 3;
    r->shift++;
    if (code == 0) {
        value = code;
    } else {
        switch (code) {
        case 1:
            value = *r->bytes;
            r->bytes++;
            break;
        case 2:
            value = *r->shorts;
            r->shorts++;
            break;
        case 3:
            value = *r->words;
            r->words++;
            break;
        default:
            value = 0;
            break;
        }
    }
    return value;
}
static inline int readRunLengthBackward(EnbayaMaskReader *r) {
    signed char code;
    int value;
    r->shift--;
    if (r->shift == -1) {
        r->shift = 3;
        r->codes--;
    }
    code = (*r->codes >> DAT_004bb0f0[r->shift]) & 3;
    if (code == 0) {
        value = code;
    } else {
        switch (code) {
        case 1:
            r->bytes--;
            value = *r->bytes;
            break;
        case 2:
            r->shorts--;
            value = *r->shorts;
            break;
        case 3:
            r->words--;
            value = *r->words;
            break;
        default:
            value = 0;
            break;
        }
    }
    return value;
}
void FUN_0027f5c0(S *s, float t) {
    bool reset;
    bool rewind;
    bool restart;
    P *p;
    int count;
    float scale;
    float end;
    FUN_002800c0();
    p = s->f12;
    count = p->p4;
    scale = p->f8;
    reset = true;
    rewind = true;
    restart = true;
    if (s->f32 != -1.0f && !(t < 1e-06f)) restart = false;
    if (!restart && s->f32 - t <= t) rewind = false;
    if (!rewind) {
        bool late = false;
        if (!(s->f32 < s->f36) && t < s->f36) late = true;
        if (!late) reset = false;
    }
    if (reset) {
        s->f0 = 0;
        s->f4 = 0.0f;
        s->f8 = 0.0f;
        FUN_0027eed0((struct TripleVectorState *)s);
        s->f168 = 0;
        FUN_00280260(&s->run, &s->mask);
        FUN_0027fb50((EnbayaTrack *)s, count, &s->reader);
        FUN_0027f510(s, count, s->f48, scale);
    }
    if (!(t < 1e-06f)) {
        end = s->f12->f12;
        while (t > s->f4 && end - s->f4 > 1e-05f) {
            if (s->f168 == 2) {
                readRunLength(&s->mask);
                s->f168 = 1;
            } else if (s->f0 > 0) {
                FUN_00280330(&s->run, (EnbayaMaskKey *)s->f16, count, &s->mask);
                s->f168 = 1;
            }
            s->f0++;
            FUN_0027fc70((EnbayaDeltaTrack *)s, count, &s->delta);
            float time = (float)s->f0 * s->f36;
            FUN_0027f410(s, count, scale, 1, time < end ? time : end);
            s->f4 = (float)s->f0 * s->f36;
            s->f8 = (float)(s->f0 - 1) * s->f36;
        }
        while (t < s->f8) {
            if (s->f168 == 1) {
                readRunLengthBackward(&s->mask);
                s->f168 = 2;
            } else {
                FUN_002805a0(&s->run, (EnbayaMaskKey *)s->f16, count, &s->mask);
            }
            s->f0--;
            FUN_0027fe90((EnbayaDeltaTrack *)s, count, &s->delta);
            float prev = (float)(s->f0 - 1) * s->f36;
            FUN_0027f410(s, count, -scale, 0, prev);
            s->f4 = (float)s->f0 * s->f36;
            s->f8 = prev;
        }
    }
    s->f32 = t;
    if (s->f171) {
        FUN_002800d0(s);
    }
}
static inline bool isZero(float x) { return !x; }
void FUN_0027fa60(EnbayaContext *ctx, float t, int track, EnbayaSlot **a, EnbayaSlot **b) {
    unsigned int in = 0;
    float x;
    if (t <= ctx->end && t >= ctx->start) in = 1;
    x = in;
    if (isZero(x)) {
        FUN_0027f5c0((S *)ctx, t);
    }
    *b = FUN_0027f350(ctx, track);
    *a = FUN_0027f3b0(ctx, track);
}
static inline int readValue(EnbayaReader *r) {
    signed char code;
    int value;

    if (r->shift == 4) {
        r->shift = 0;
        r->codes++;
    }
    /* matching construct: template sweep — zero code kept as its own branch before the switch */
    code = (*r->codes >> DAT_004bb0e0[r->shift]) & 3;
    r->shift++;
    if (code == 0) {
        value = code;
    } else {
        switch (code) {
        case 1:
            value = *r->bytes;
            r->bytes++;
            break;
        case 2:
            value = *r->shorts;
            r->shorts++;
            break;
        case 3:
            value = *r->words;
            r->words++;
            break;
        default:
            value = 0;
            break;
        }
    }
    return value;
}
void FUN_0027fb50(EnbayaTrack *track, int count, EnbayaReader *reader) {
    int i;
    int j;
    for (i = 0; i < count; i++) {
        for (j = 0; j < 7; j++) {
            track->keys[i].values[j] = readValue(reader);
        }
    }
}

static inline int readDelta(EnbayaDeltaReader *r) {
    signed char code;
    int value;
    if (r->shift == 4) {
        r->shift = 0;
        r->codes++;
    }
    code = (*r->codes >> DAT_004bb0c0[r->shift]) & 3;
    r->shift++;
    if (code != 2) {
        return DAT_004f2740[code];
    }
    if (r->nibbleShift == 2) {
        r->nibbleShift = 0;
        r->nibbles++;
    }
    code = (*r->nibbles >> DAT_004bb0d0[r->nibbleShift]) & 15;
    r->nibbleShift++;
    if (code != 0) {
        return DAT_004f2750[code];
    }
    value = *r->bytes++;
    if (value != 0) {
        if (value > 0 && value < 9) {
            return value + 127;
        }
        if (value > -9 && value < 0) {
            return value - 128;
        }
        return (signed char)value;
    }
    value = *r->shorts;
    r->shorts++;
    if (value != 0) {
        return value;
    }
    value = *r->words;
    r->words++;
    return value;
}
/* matching construct: a small sweep of spellings */
void FUN_0027fc70(EnbayaDeltaTrack *track, int count, EnbayaDeltaReader *reader) {
    int i;
    int j;
    for (i = 0; i < count; i++) {
        if (track->keys[i].mask) {
            for (j = 0; j < 7; j++) {
                if ((1 << j) & track->keys[i].mask) {
                    track->keys[i].values[j] += readDelta(reader);
                }
            }
        }
    }
}

static inline int readDeltaBackward(EnbayaDeltaReader *r) {
    signed char code;
    int value;
    r->shift--;
    if (r->shift == -1) {
        r->shift = 3;
        r->codes--;
    }
    code = (*r->codes >> DAT_004bb0c0[r->shift]) & 3;
    if (code != 2) {
        return DAT_004f2740[code];
    }
    r->nibbleShift--;
    if (r->nibbleShift == -1) {
        r->nibbleShift = 1;
        r->nibbles--;
    }
    code = (*r->nibbles >> DAT_004bb0d0[r->nibbleShift]) & 15;
    if (code != 0) {
        return DAT_004f2750[code];
    }
    r->bytes--;
    value = *r->bytes;
    if (value != 0) {
        if (value > 0 && value < 9) {
            return value + 127;
        }
        if (value > -9 && value < 0) {
            return value - 128;
        }
        return (signed char)value;
    }
    r->shorts--;
    value = *r->shorts;
    if (value != 0) {
        return value;
    }
    r->words--;
    value = *r->words;
    return value;
}
void FUN_0027fe90(EnbayaDeltaTrack *track, int count, EnbayaDeltaReader *reader) {
    int i;
    int j;
    for (i = count - 1; i > 0; i--) {
        if (track->keys[i].mask) {
            for (j = 6; j >= 0; j--) {
                if ((1 << j) & track->keys[i].mask) {
                    track->keys[i].values[j] -= readDeltaBackward(reader);
                }
            }
        }
    }
}

void FUN_002800c0(void)
{
}

void FUN_002800d0(S *s)
{
}

void FUN_002800e0(S *s) {
    if (s->f24) {
        if (s->f20 < 0x4000) {
            unsigned int localPad = (unsigned int)((char *)s + 176) - ((unsigned int)((char *)s + 176) & ~15);
            int base = s->f12->f76;
            int basePad = base - (base & ~15);
            unsigned int room;
            s->f116 = s->f116 - base - -(basePad + 0x70000000);
            s->f120 = s->f120 - base - -(basePad + 0x70000000);
            s->f124 = s->f124 - base - -(basePad + 0x70000000);
            s->f128 = s->f128 - base - -(basePad + 0x70000000);
            s->f132 = s->f132 - base - -(basePad + 0x70000000);
            s->f136 = s->f136 - base - -(basePad + 0x70000000);
            s->f140 = s->f140 - base - -(basePad + 0x70000000);
            s->f144 = s->f144 - base - -(basePad + 0x70000000);
            s->f148 = s->f148 - base - -(basePad + 0x70000000);
            s->f152 = s->f152 - base - -(basePad + 0x70000000);
            s->f156 = s->f156 - base - -(basePad + 0x70000000);
            s->f160 = s->f160 - base - -(basePad + 0x70000000);
            s->f164 = s->f164 - base - -(basePad + 0x70000000);
            room = 0x4000 - ((s->f20 + basePad + 15) & ~15);
            if ((unsigned int)(s->f28 + localPad) < room) {
                s->f170 = 1;
                s->f16 = 0x70004000 - room;
            }
        } else {
            s->f24 = 0;
        }
    }
}
void *FUN_00280240(unsigned int sz, void *p)
{
    return p;
}

void thunk_FUN_00280a00(void) {
    FUN_00280a00();
}

void FUN_00280260(EnbayaMaskRun *run, EnbayaMaskReader *reader) {
    run->remaining = readRunLength(reader);
    run->consumed = 0;
}
void FUN_00280330(EnbayaMaskRun *run, EnbayaMaskKey *keys, int count, EnbayaMaskReader *reader) {
    int total = count * 7;
    int i = 0;
    while (i < total) {
        if (run->remaining == 0) {
            int key = i / 7;
            switch (i % 7) {
            case 0:
                keys[key].mask ^= 1;
                break;
            case 1:
                keys[key].mask ^= 2;
                break;
            case 2:
                keys[key].mask ^= 4;
                break;
            case 3:
                keys[key].mask ^= 8;
                break;
            case 4:
                keys[key].mask ^= 0x10;
                break;
            case 5:
                keys[key].mask ^= 0x20;
                break;
            case 6:
                keys[key].mask ^= 0x40;
                break;
            case 7:
                break;
            }
            run->remaining = readRunLength(reader);
            i++;
            run->consumed = 0;
        } else {
            int left = total - i;
            int n = run->remaining < left ? run->remaining : left;
            i += n;
            run->remaining -= n;
            run->consumed += n;
        }
    }
}

void FUN_002805a0(EnbayaMaskRun *run, EnbayaMaskKey *keys, int count, EnbayaMaskReader *reader) {
    int i = count * 7 - 1;
    while (i >= 0) {
        if (run->consumed == 0) {
            int key = i / 7;
            switch (i % 7) {
            case 0:
                keys[key].mask ^= 1;
                break;
            case 1:
                keys[key].mask ^= 2;
                break;
            case 2:
                keys[key].mask ^= 4;
                break;
            case 3:
                keys[key].mask ^= 8;
                break;
            case 4:
                keys[key].mask ^= 0x10;
                break;
            case 5:
                keys[key].mask ^= 0x20;
                break;
            case 6:
                keys[key].mask ^= 0x40;
                break;
            case 7:
                break;
            }
            run->consumed = readRunLengthBackward(reader);
            i--;
            run->remaining = 0;
        } else {
            int left = i + 1;
            int n = run->consumed < left ? run->consumed : left;
            i -= n;
            run->remaining += n;
            run->consumed -= n;
        }
    }
}

}
