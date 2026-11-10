#include "dw4/reflected.h"

extern "C" {
void igObject_Destroy(void *);
int Memory_FreeBuffer(...);
int FUN_001e74b0(...);
int FUN_001e7500(...);
int FUN_001edbc0(...);
int p2LoadTexture(int, int, int, int, int);
void FUN_0020c9f0(int buffer);
extern int DAT_0048ac40[];
extern int DAT_0048acb0[];
extern int DAT_0048ac70[4];
extern int DAT_0048acf0[];
extern int DAT_00560a5c[8];
extern int DAT_00569330[4];
}

typedef struct StageState { int w[112]; } StageState;

extern "C" {
extern StageState DAT_00569340[];
extern StageState *DAT_0056ad80[4];
}

class igPsx2VisualContextSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124();
    virtual void vfunc_125(int value, int option);
    virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130();
    virtual void vfunc_131(int value, int index, int option);
};


extern "C" void FUN_0017a070(int *a) {
    igObject *temp_a0;
    igObject *temp_a0_2;

    a[0] = 7;
    a[1] = 1;
    a[2] = 1;
    a[3] = 1;
    a[4] = 1;
    a[21] = 0;
    a[22] = 0x20;
    a[23] = 0;
    a[24] = 0x20;
    a[5] = 0;
    a[8] = -1;
    a[9] = -1;
    a[10] = -1;
    temp_a0 = (igObject *)(a[12]);
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int)temp_a0->_refCount - 1;
        if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    a[12] = 0;
    temp_a0_2 = (igObject *)(a[13]);
    if (temp_a0_2 != 0) {
        temp_a0_2->_refCount = (int)temp_a0_2->_refCount - 1;
        if ((temp_a0_2->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    a[13] = 0;
    a[14] = 0;
    a[15] = 0;
    a[25] = -1;
    a[27] = 0;
    a[26] = -1;
    a[18] = 0;
    a[19] = 0;
    a[33] = 0;
    *(char *)((char *)a + 80) = 1;
    *(char *)((char *)a + 81) = 1;
    a[7] = -1;
}

typedef struct BufferEntryRef { int w0; int references; } BufferEntryRef;
typedef struct BufferSetView { char p0[48]; BufferEntryRef *f48; BufferEntryRef *f52; BufferEntryRef **f56; unsigned int f60; char p64[8]; void *f72; } BufferSetView;

extern "C" void FUN_0017a180(void *self) {
    int r;
    BufferEntryRef *o;
    BufferEntryRef **slot;
    BufferSetView *arg0;
    unsigned int i;
    arg0 = (BufferSetView *)self;
    o = arg0->f52;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->f52 = 0;
    o = arg0->f48;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->f48 = 0;
    i = 0;
    if (arg0->f56 != 0) {
        for (; i < arg0->f60; i++) {
            slot = arg0->f56 + i;
            o = *slot;
            if (o != 0) {
                r = o->references - 1;
                o->references = r;
                r = o->references;
                if (((unsigned long long)((long long)r << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
            *slot = 0;
        }
        Memory_FreeBuffer(arg0->f56);
    }
    if (arg0->f72 != 0) {
        Memory_FreeBuffer(arg0->f72);
    }
    arg0->f60 = 0;
}

extern "C" int FUN_0017a2b0(int arg0) {
    if (arg0 & 0x10000) {
        return DAT_0048acb0[arg0 & 0xFFFF];
    }
    return DAT_0048ac40[arg0];
}

extern "C" {
int thunk_FUN_003065f0(int, int, void *, int *, int, int);
int FUN_00165d10(void *);
struct Buf;
Buf *Memory_AllocateBufferDirect(int, int);
void *Memory_FindBufferOwner(void *);
int FUN_002caa70(int);
int FUN_002eb010(int);
int StringPool_Construct(int);
int *StringPool_Intern(int, const char *);
void StringChunk_ReleaseHeader(int, int *);
extern char DAT_004e0800[];
extern int DAT_00586f20[4];
extern int *DAT_00586dc8[4];
}
struct T { int word0; int references; };
class Owner {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void *v224(int, int);
    virtual void *v228(int, int, int);
};
struct Buf { short s0, s2, s4; short pad6; int f8; short *f12; void *f16; };
struct Self { char p[324]; Buf *f324; int pad328; T *f332; int f336, f340; char p344[220]; char a564[16]; };
extern "C" void FUN_0017a300(Self *self) {
    int sp5C;
    int bi;
    Buf *b;
    T *o;
    int i;
    sp5C = 0x40;
    thunk_FUN_003065f0(*(int *)((char *)DAT_00586dc8[0] + 56), 4, DAT_004e0800, &sp5C, 0x40, 0);
    Buf *r = (Buf *)Memory_AllocateBufferDirect(0x14, FUN_00165d10(self));
    if (r != 0) {
        bi = (int)r;
        b = (Buf *)bi;
        int n = sp5C;
        Owner *ow;
        int k;
        int *old;
        int *tok;
        b->f8 = 0;
        if (DAT_00586f20[0] == 0) {
            int pool = FUN_002eb010(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        tok = StringPool_Intern(DAT_00586f20[0], DAT_004e0800);
        old = (int *)b->f8;
        if (old != 0) {
            int *h = old - 2;
            int c = old[-1] - 1;
            old[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*h, h);
        }
        b->f8 = (int)tok;
        if (n == 0) n = 1;
        ow = (Owner *)Memory_FindBufferOwner(b);
        b->f16 = ow->v228(n, 0x88, 0x10);
        b->f12 = (short *)ow->v224(n, 2);
        b->s2 = n;
        b->s0 = n;
        b->s4 = n;
        for (k = 0; k < n; k++) b->f12[k] = (short)k;
        r = (Buf *)bi;
    }
    self->f324 = r;
    self->f336 = -1;
    self->f340 = 1;
    i = 0;
    do {
        self->a564[i] = 0;
        i++;
    } while (i < 16);
    o = (T *)FUN_002caa70(FUN_00165d10(self));
    if (o != 0) o->references = o->references + 1;
    {
        T *old2 = self->f332;
        if (old2 != 0) {
            --old2->references;
            if (((unsigned long long)(long long)old2->references & 0x7fffffULL) == 0) igObject_Destroy(old2);
        }
    }
    self->f332 = o;
    {
        T *c = self->f332;
        --c->references;
        if (((unsigned long long)(long long)c->references & 0x7fffffULL) == 0) igObject_Destroy(c);
    }
}

typedef struct S0 { char pad1524[1524]; int f5F4; int f5F8; int f5FC; } S0;
extern "C" void FUN_0017a870(S0 *arg0, int arg1);


extern "C" void FUN_0017a7e0(S0 *arg0) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int sp2C;
    int sp28;
    int sp24;
    int sp20;

    FUN_0017a870(arg0, 0);
    FUN_001edbc0(&sp2C, &sp28, &sp24, &sp20);
    *(int *)((char *)(arg0) + 1524) = p2LoadTexture(0, sp2C, sp28, sp24, 1);
    *(int *)((char *)(arg0) + 1528) = p2LoadTexture(0, sp2C, sp28, sp24, 2);
    *(int *)((char *)(arg0) + 1532) = p2LoadTexture(0, sp2C, sp28, sp20, 3);
}


extern "C" void FUN_0017a870(S0 *arg0, int arg1) {
    int temp_a0;
    int temp_a0_2;
    int temp_a0_3;

    if (arg1 == 0) {
        temp_a0 = arg0->f5F4;
        if (temp_a0 != 0) {
            FUN_0020c9f0(temp_a0);
            arg0->f5F4 = 0;
        }
        temp_a0_2 = arg0->f5F8;
        if (temp_a0_2 != 0) {
            FUN_0020c9f0(temp_a0_2);
            arg0->f5F8 = 0;
        }
        temp_a0_3 = arg0->f5FC;
        if (temp_a0_3 != 0) {
            FUN_0020c9f0(temp_a0_3);
            arg0->f5FC = 0;
        }
    }
}

extern "C" int Gap__Gfx__igPsx2VisualContext__vfunc_142(void) {
    return 0;
}

struct TextureStateView117 { char pad[564]; unsigned char a[16]; };
extern "C" int DAT_00560a08[8];
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_117(struct TextureStateView117 *arg0, int arg1, int arg2) {
    int n;
    int j;
    if (arg1 < 15) {
        n = arg1;
    } else {
        n = 15;
    }
    if (n < 8) {
        if (arg0->a[n] == (arg2 & 0xFF)) {
            DAT_00560a08[n] += 1;
        }
    }
    arg0->a[n] = arg2;
    if (n > 1) {
        j = n - 1;
    } else {
        j = 0;
    }
    DAT_00569330[0] = n;
    DAT_0056ad80[0] = &DAT_00569340[j];
    if (arg2 != 0) {
        FUN_001e74b0(1, n);
    } else {
        FUN_001e7500(1, n);
    }
    DAT_00569330[0] = 0;
    DAT_0056ad80[0] = DAT_00569340;
}

extern "C" unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_118(int arg0, int arg1) { int i = (arg1 < 15 ? arg1 : 15); return *(unsigned char *)(i + arg0 + 564); }

#include "dw4/igSmartPointer.h"

struct ClutObject {
    char pad0[32];
    int handle;
    int locked;
};

class MipImage : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void reduceFrom(MipImage *source);
    virtual void allocate(int size, int flags);
    virtual void setWidth(int width);
    virtual void setHeight(int height);
    virtual void setFormat(int format);
    unsigned int width;
    unsigned int height;
    char pad16[36];
    int pixels;
    char pad56[12];
    ClutObject *clut;
};

struct ClutData {
    char pad0[28];
    unsigned char dirty;
};

struct ClutEntry {
    int pad0;
    ClutData *data;
    int handle;
    char pad12[8];
    int state;
};

struct TexEntry {
    int format;
    int minFilter;
    int magFilter;
    int wrapU;
    int wrapV;
    int kind;
    unsigned int flags;
    int stage;
    int width;
    int height;
    int depth;
    char pad44[4];
    igObject *palette;
    MipImage *image;
    igSmartPointer<MipImage> *mipImages;
    unsigned int mipCount;
    char pad64[8];
    int *buffers;
    int buffer;
    char pad80;
    unsigned char reload;
    char pad82[2];
    int lodParams[4];
    int altClut;
    int clut;
    int bufferIndex;
    char pad112[24];
};

class ListAllocator {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
    virtual unsigned short *reallocate(unsigned short *block, int size);
};

struct TexList {
    unsigned short count;
    unsigned short freeCapacity;
    unsigned short freeCount;
    char pad6[6];
    unsigned short *freeIndices;
    TexEntry *data;
};

struct ClutList {
    int pad0[4];
    ClutEntry *data;
};

class TexContext {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127();
    virtual void unloadTexture(int index);
    char pad4[320];
    TexList *texList;
    ClutList *clutList;
    char pad332[4];
    int currentTex;
    char pad340[216];
    unsigned char texPageEnable;
};

extern "C" {
extern unsigned char DAT_00554b78;
extern unsigned int DAT_0048aca0[];
extern long long DAT_00560ef8;
void FUN_0020c880(int);
void FUN_0020c840(int, int);
int FUN_0020bb20(int *, int, int);
int FUN_00159f70(int);
int FUN_00165cf0(void *);
MipImage *FUN_0014df70(int);
void FUN_0020c7b0(int, int);
void FUN_0016ab80(TexContext *, int);
ListAllocator *FUN_002ed520(TexList *);
void FUN_0017b400(TexContext *, TexEntry *, int, ClutEntry *, int);
void FUN_0017b5f0(TexContext *, TexEntry *);
}



extern "C" int FUN_0017aa20(TexContext *context, int width, int height, int format, int kind, unsigned int flags, unsigned int levels);


extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_120(TexContext *a0, int a1, int a2, int a3, int a4, int a5, int a6) {
    FUN_0017aa20(a0, a1, a2, a3, a4, a5, 1);
}

extern "C" int thunk_FUN_0017aa20(TexContext *context, int width, int height, int format, int kind, unsigned int flags, unsigned int levels)
{
    return FUN_0017aa20(context, width, height, format, kind, flags, levels);
}

class TexMemoryPool {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
    virtual int *allocate(int size);
    virtual void d53();
    virtual igSmartPointer<MipImage> *allocateArray(int elementSize, int count);
};

struct ClutContextCB80;

extern "C" {
TexEntry *thunk_FUN_002ed3b0(TexEntry *, int, int);
void *memset(void *, int, unsigned int);
TexMemoryPool *FUN_00165ce0(TexContext *);
int FUN_0017cb80(ClutContextCB80 *, int, int *);
}

inline void adoptNewImage(MipImage *&image, AdoptReference)
{
    igRelease(image);
    image = FUN_0014df70(0);
}

extern "C" int FUN_0017aa20(TexContext *context, int width, int height, int format, int kind, unsigned int flags,
                                       unsigned int levels)
{
    TexList *list = context->texList;
    int index;
    unsigned int mipLevels;
    TexEntry *entry;
    int i;

    if (list->freeCount <= 0) {
        list->data = thunk_FUN_002ed3b0(list->data, (list->count + 4) * sizeof(TexEntry), 16);
        memset(&list->data[list->count], 0, 4 * sizeof(TexEntry));
        if (list->freeCapacity < 4) {
            list->freeIndices = FUN_002ed520(list)->reallocate(list->freeIndices, 8);
            list->freeCapacity = 4;
        }
        for (i = 0; i < 4; i++) {
            list->freeIndices[i] = list->count + i;
        }
        list->freeCount = 4;
        list->count += 4;
    }
    index = list->freeIndices[list->freeCount - 1];
    list->freeCount--;
    if (levels == 0) {
        levels = 1;
    }
    entry = &context->texList->data[index];
    mipLevels = levels - 1;
    FUN_0017a070((int *)entry);
    entry->width = width;
    entry->height = height;
    entry->format = format;
    entry->kind = kind;
    entry->flags = flags;
    igRelease(entry->palette);
    entry->palette = 0;
    igRelease(entry->image);
    entry->image = 0;
    entry->depth = -1;
    entry->mipCount = mipLevels > 6 ? 6 : mipLevels;
    entry->mipImages = 0;
    entry->buffers = FUN_00165ce0(context)->allocate(32);
    for (i = 0; i < 8; i++) {
        entry->buffers[i] = 0;
    }
    if (format < 0x10000) {
        DAT_00560ef8 += (unsigned int)(DAT_0048ac70[format] * (width * height));
    }
    if (format >= 0x10000) {
        DAT_00560ef8 += (DAT_0048aca0[format - 0x10000] * (width * height)) >> 1;
    }
    if (entry->kind == 2) {
        adoptNewImage(entry->image, AdoptReference());
        entry->image->setWidth(entry->width);
        entry->image->setHeight(entry->height);
        entry->image->setFormat(entry->format);
        entry->image->allocate(0, 0);
    }
    if (flags == 1 && mipLevels == 0) {
        int size = width < height ? width : height;
        int count = 0;

        while (size >>= 1) {
            count++;
        }
        entry->mipCount = count < 6 ? count : 6;
    }
    if (entry->mipCount != 0) {
        unsigned int mip;

        entry->mipImages = FUN_00165ce0(context)->allocateArray(4, 6);
        for (mip = 0; mip < 6; mip++) {
            entry->mipImages[mip].clear();
        }
    }
    entry->altClut = FUN_0017cb80((ClutContextCB80 *)context, format, (int *)entry);
    if (entry->width < 128 && entry->width < entry->height) {
        if ((unsigned int)entry->format <= 2 || entry->format == 4 || entry->format == 6 || entry->format == 0x10000 ||
            entry->format == 0x10001) {
            entry->width = 128;
        }
    }
    return index;
}

extern "C" int Gap__Gfx__igPsx2VisualContext__vfunc_124(void) {
    return 0;
}

extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_126(void) {

}

extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_125(igPsx2VisualContext *arg0, int arg1, int *arg2, int *arg3, int *arg4, int *arg5, char *arg6) {
    void *temp_a0;

    temp_a0 = (void *)(*(int *)((char *)(arg0->_pTexList) + 16) + (arg1 * 0x88));
    *arg2 = *(int *)((char *)(temp_a0) + 116);
    *arg3 = *(int *)((char *)(temp_a0) + 120);
    *arg4 = *(int *)((char *)(temp_a0) + 124);
    *arg5 = *(int *)((char *)(temp_a0) + 128);
    *arg6 = 0;
}

extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_128(igPsx2VisualContextSlots *self, int value, int option)
{
    self->vfunc_125(value, 0);
}

extern "C" bool Gap__Gfx__igPsx2VisualContext__vfunc_127(TexContext *context, int index, int stage)
{
    bool result;
    bool clutDirty;
    ClutEntry *clut;
    int clutIndex = -1;
    TexEntry *entry;
    bool enabled;
    bool reload;
    int isTarget;

    if (index == -1) {
        FUN_0020c880(stage);
        return false;
    }
    entry = &context->texList->data[index];
    result = true;
    clutDirty = false;
    clut = 0;
    enabled = result;
    if (DAT_00554b78) {
        enabled = false;
    }
    if (!enabled) {
        return true;
    }
    if (entry->buffers[0] == 0) {
        FUN_0017b5f0(context, entry);
    }
    if (entry->clut >= 0 || entry->altClut >= 0) {
        if (entry->clut >= 0) {
            clut = &context->clutList->data[entry->clut];
            clutIndex = entry->clut;
        } else if (entry->altClut >= 0) {
            clut = &context->clutList->data[entry->altClut];
            clutIndex = entry->altClut;
        }
        if (clut->data->dirty) {
            clutDirty = true;
        }
    }
    isTarget = entry != 0;
    if (isTarget) {
        isTarget = entry->kind == 2;
    }
    reload = false;
    if (isTarget && entry->reload) {
        reload = true;
    }
    if (context->currentTex != index || entry->stage != stage || clutDirty || reload) {
        if (reload) {
            entry->reload = false;
            FUN_0020c840(entry->buffers[0], entry->image->pixels);
        }
        FUN_0017b400(context, entry, stage, clut, clutIndex);
        entry->stage = stage;
        context->currentTex = index;
        result = FUN_0020bb20(entry->buffers, stage, (unsigned char)!context->texPageEnable) != 0;
    }
    return result;
}

extern "C" void FUN_0017b5f0(TexContext *context, TexEntry *entry)
{
    int level = 0;
    int format;
    int count;

    if (FUN_00159f70(entry->format)) {
        format = DAT_0048acb0[entry->format - 0x10000];
    } else {
        format = DAT_0048ac40[entry->format];
    }
    entry->buffers[0] = p2LoadTexture(entry->image ? entry->image->pixels : 0, entry->width, entry->height, format, 0);
    level++;
    count = entry->mipCount;
    if (count != 0) {
        if (entry->flags & 1) {
            int width = entry->width;
            int height = entry->height;
            igSmartPointer<MipImage> previous(entry->image, kRetainReference);
            int i;

            for (i = 0; i < count; i++) {
                igSmartPointer<MipImage> mip(FUN_0014df70(FUN_00165cf0(context)));
                int mipFormat;

                mip->reduceFrom(previous);
                entry->mipImages[i] = mip;
                if (FUN_00159f70(entry->format)) {
                    mipFormat = DAT_0048acb0[entry->format - 0x10000];
                } else {
                    mipFormat = DAT_0048ac40[entry->format];
                }
                entry->buffers[level] = p2LoadTexture(mip->pixels, mip->width, mip->height, mipFormat, 0);
                FUN_0020c7b0(entry->buffers[0], entry->buffers[level]);
                level++;
                width >>= 1;
                height >>= 1;
                previous = mip;
                if (width <= 0) {
                    width = 1;
                }
                if (height <= 0) {
                    height = 1;
                }
            }
            entry->flags &= ~1;
        } else {
            unsigned int i;

            for (i = 0; i < entry->mipCount; i++) {
                int mipFormat;
                MipImage *mip;

                if (FUN_00159f70(entry->format)) {
                    mipFormat = DAT_0048acb0[entry->format - 0x10000];
                } else {
                    mipFormat = DAT_0048ac40[entry->format];
                }
                mip = entry->mipImages[i];
                entry->buffers[level] = p2LoadTexture(mip->pixels, mip->width, mip->height, mipFormat, 0);
                FUN_0020c7b0(entry->buffers[0], entry->buffers[level]);
                level++;
            }
        }
    }
    if (entry->clut >= 0 || entry->altClut >= 0) {
        entry->bufferIndex = level;
    }
}

extern "C" int Gap__Gfx__igPsx2VisualContext__vfunc_129(void *arg0) {
    return *(int *)((char *)(arg0) + 336);
}


typedef struct UCodeProgram {
    char pad0[68];
    int resident;
} UCodeProgram;

typedef struct UCodeSlot {
    char pad0[20];
    int kind;
    char pad24[28];
    UCodeProgram *program;
    char pad56[16];
    int *buffers;
    int buffer;
    char pad80[20];
    int altHandle;
    int handle;
    int bufferIndex;
    char pad112[24];
} UCodeSlot;

typedef struct UCodeSlotList {
    int _pad0[4];
    UCodeSlot *_data;
} UCodeSlotList;

typedef struct UCodeContextView {
    char pad0[324];
    UCodeSlotList *slots;
    char pad328[8];
    int current;
} UCodeContextView;

extern "C" {
void FUN_0016b1d0(UCodeContextView *context, int handle);
void FUN_0020c8b0(int buffer);
int FUN_0020b270(int buffer);
void FUN_001f05a0(int channel, int size);
}

extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_130(UCodeContextView *context, int index) {
    UCodeSlot *slot = &context->slots->_data[index];
    int i;

    context->current = -1;
    if (slot->handle >= 0) {
        if (slot->program->resident != 0) {
            FUN_0016b1d0(context, slot->handle);
        }
        slot->buffers[slot->bufferIndex] = 0;
    } else if (slot->altHandle >= 0) {
        FUN_0016b1d0(context, slot->altHandle);
        slot->buffers[slot->bufferIndex] = 0;
    }
    if (slot->kind == 3) {
        if (slot->buffers[0] != 0) {
            FUN_0020c8b0(slot->buffers[0]);
            if (slot->buffer != 0) {
                FUN_0020c8b0(slot->buffer);
            }
        }
    } else if (slot->buffers != 0) {
        for (i = 0; i < 8; i++) {
            if (slot->buffers[i] != 0) {
                FUN_001f05a0(2, FUN_0020b270(slot->buffers[i]));
                FUN_0020c9f0(slot->buffers[i]);
                slot->buffers[i] = 0;
            }
        }
    }
}

extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_131(TexContext *context, int index)
{
    TexEntry *entry = &context->texList->data[index];
    TexList *list;

    context->unloadTexture(index);
    if (entry->clut >= 0) {
        ClutObject *clut = entry->image->clut;
        if (clut != 0 && clut->locked == 0) {
            FUN_0016ab80(context, entry->clut);
            clut->handle = -1;
        }
    }
    if (entry->kind == 3 && entry->buffers[0] != 0) {
        FUN_0020c9f0(entry->buffers[0]);
        if (entry->buffer != 0) {
            FUN_0020c9f0(entry->buffer);
        }
    }
    if (entry->format < 0x10000) {
        DAT_00560ef8 += -(DAT_0048ac70[entry->format] * (entry->width * entry->height));
    }
    if (entry->format >= 0x10000) {
        DAT_00560ef8 += (int)-((DAT_0048aca0[entry->format - 0x10000] * (entry->width * entry->height)) >> 1);
    }
    FUN_0017a180(entry);
    list = context->texList;
    if (index < list->count && index >= 0) {
        if (list->freeCount >= list->freeCapacity) {
            ListAllocator *allocator = FUN_002ed520(list);
            list->freeCapacity += 8;
            list->freeIndices = allocator->reallocate(list->freeIndices, list->freeCapacity * 2);
        }
        list->freeIndices[list->freeCount] = index;
        list->freeCount++;
    }
}

extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_132(igPsx2VisualContextSlots *self, int value, int index, int option)
{
    self->vfunc_131(value, index, 0);
}

class TextureImageView260 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int, int); };
extern "C" {
int Gap__Gfx__igPsx2VisualContext__vfunc_260(igPsx2VisualContext *arg0, int arg1, int arg2);
}
int Gap__Gfx__igPsx2VisualContext__vfunc_260(igPsx2VisualContext *arg0, int arg1, int arg2) {
    int a0;
    int var_a3;
    int var_a4;
    char *s0;

    s0 = (char *)(*(int *)((char *)(arg0->_pTexList) + 16) + (arg1 * 0x88));
    if (*(int *)(s0 + 20) != 2 || *(int *)(s0 + 72) == 0) {
        return 0;
    }
    a0 = *(int *)(s0 + 0);
    var_a4 = 1;
    var_a3 = 1;
    if (a0 < 0x10000) {
        var_a4 = DAT_0048ac70[a0];
    } else if (a0 == 0x10001) {
        var_a3 = 2;
    }
    TextureImageView260 *c = *(TextureImageView260 **)(s0 + 52);
    c->vX(arg2, (var_a4 * (*(int *)(s0 + 32) * *(int *)(s0 + 36))) / var_a3, var_a3, var_a4);
    *(char *)(s0 + 81) = 1;
    return 1;
}

extern "C" int Gap__Gfx__igPsx2VisualContext__vfunc_135(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + (arg1 * 0x88))) + 48);
}

extern "C" int Gap__Gfx__igPsx2VisualContext__vfunc_134(void) {
    return 0;
}

typedef struct TextureEntry138 { char pad4[4]; int f4; char pad8[72]; unsigned char f80; char pad81[55]; } TextureEntry138;
typedef struct TextureList138 { char pad16[16]; TextureEntry138 *f16; } TextureList138;
typedef struct TextureContext138 { char pad324[324]; TextureList138 *f324; } TextureContext138;
extern "C" int DAT_00560a28[4];
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_138(TextureContext138 *arg0, int arg1, int arg2) {
    int temp_a3;

    temp_a3 = arg1 * 0x88;
    if (arg2 == *(int *)((char *)arg0->f324->f16 + temp_a3 + 4)) {
        DAT_00560a28[0] += 1;
    }
    *(int *)((char *)arg0->f324->f16 + temp_a3 + 4) = arg2;
    *(char *)((char *)arg0->f324->f16 + temp_a3 + 80) = 1;
}

extern "C" int DAT_00560a2c[4];
struct TextureEntry140 { char pad[8]; int v; char pad2[68]; char flag; char pad3[55]; };
struct TextureList140 { char pad[16]; struct TextureEntry140 *arr; };
struct TextureContext140 { char pad[324]; struct TextureList140 *tab; };
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_140(struct TextureContext140 *arg0, int arg1, int arg2) {
    struct TextureEntry140 *e = arg0->tab->arr + arg1; if (arg2 == e->v) { DAT_00560a2c[0] += 1; } e = arg0->tab->arr + arg1; e->v = arg2; e = arg0->tab->arr + arg1; e->flag = 1;
}

extern "C" int Gap__Gfx__igPsx2VisualContext__vfunc_139(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + (arg1 * 0x88))) + 4);
}

extern "C" int Gap__Gfx__igPsx2VisualContext__vfunc_141(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + (arg1 * 0x88))) + 8);
}

extern "C" {
extern int DAT_00560a34[4];
extern int DAT_00560a38[4];
}
struct TextureList136 { char pad[16]; char *e; };
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_136(struct igPsx2VisualContext *arg0, int arg1, int arg2, int arg3) {
    int temp_v1;
    temp_v1 = arg1 * 0x88;
    if (arg2 == *(int *)(((struct TextureList136 *)arg0->_pTexList)->e + temp_v1 + 12)) {
        DAT_00560a34[0] += 1;
    }
    if (arg3 == *(int *)(((struct TextureList136 *)arg0->_pTexList)->e + temp_v1 + 16)) {
        DAT_00560a38[0] += 1;
    }
    *(int *)(((struct TextureList136 *)arg0->_pTexList)->e + temp_v1 + 12) = arg2;
    *(int *)(((struct TextureList136 *)arg0->_pTexList)->e + temp_v1 + 16) = arg3;
    *(char *)(((struct TextureList136 *)arg0->_pTexList)->e + temp_v1 + 80) = 1;
}

extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_137(void *arg0, int arg1, int *arg2, int *arg3) {
    int temp_a1;

    temp_a1 = arg1 * 0x88;
    *arg2 = *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + temp_a1)) + 12);
    *arg3 = *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + temp_a1)) + 16);
}

extern "C" void FUN_0017c6e0(int arg0) {
    /* matching construct: variant search — decl order [1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int var_a3;
    void *temp_a2;

    var_a3 = 0;
    do {
        temp_a2 = (void *)(arg0 + (var_a3 * 4));
        var_a3 += 1;
        *(int *)((char *)(temp_a2) + 580) = 1;
        *(int *)((char *)(temp_a2) + 644) = 0;
    } while (var_a3 < 0x10);
}

extern "C" int DAT_00560a3c[4];
extern "C" void FUN_0017c710(int arg0, int arg1, int arg2, unsigned char arg3) {
    if (arg1 < 8) {
        unsigned char v = *(unsigned char *)(arg1 + arg0 + 540); if (v == (arg2 & 0xFF)) {
            DAT_00560a3c[arg1] = DAT_00560a3c[arg1] + 1;
        }
    }
    *(char *)(arg1 + arg0 + 540) = arg2;
    if (arg1 == 0) {
        if (arg2 != 0) {
            FUN_001e74b0(0x1A, arg1);
            return;
        }
        FUN_001e7500(0x1A, arg1);
    }
}

extern "C" unsigned char FUN_0017c790(int arg0, int arg1) {
    return *(int *)((char *)((arg1 + arg0)) + 540);
}

typedef struct VisualContextSlots { char pad[580]; int slot[16]; } VisualContextSlots;
extern "C" int FUN_00208f70(int);
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_148(VisualContextSlots *arg0, int arg1, int arg2) {
    int a3;
    arg1 = arg1 < 15 ? arg1 : 15;
    if (arg1 < 8) {
        if (arg0->slot[arg1] == arg2) {
            DAT_00560a5c[arg1] += 1;
        }
    }
    arg0->slot[arg1] = arg2;
    a3 = arg1 > 1 ? arg1 - 1 : 0;
DAT_00569330[0] = arg1; DAT_0056ad80[0] = &DAT_00569340[a3]; FUN_00208f70(DAT_0048acf0[arg2]);
    DAT_00569330[0] = 0;
    DAT_0056ad80[0] = DAT_00569340;
}

extern "C" void FUN_0017c8a0(igPsx2VisualContext *context, int stage, int function, unsigned char colorComponent);
extern "C" void FUN_0017c880(igPsx2VisualContext *arg0, int arg1, unsigned char arg2) {
    FUN_0017c8a0(arg0, 0, arg1, arg2);
}

extern "C" void FUN_00209090(int function, int colorComponent);
extern "C" void FUN_0017c8a0(igPsx2VisualContext *context, int stage, int function, unsigned char colorComponent) {
    int n;
    int j;

    if (stage < 15) {
        n = stage;
    } else {
        n = 15;
    }
    if (n < 8) {
        if (context->_texStageFunc[n] == function) {
            DAT_00560a5c[n] += 1;
        }
    }
    context->_texStageFunc[n] = function;
    if (n > 1) {
        j = n - 1;
    } else {
        j = 0;
    }
    DAT_00569330[0] = n;
    DAT_0056ad80[0] = &DAT_00569340[j];
    context->_bTextureColorComponent = colorComponent;
    FUN_00209090(DAT_0048acf0[function], colorComponent);
    DAT_00569330[0] = 0;
    DAT_0056ad80[0] = DAT_00569340;
}

extern "C" int Gap__Gfx__igPsx2VisualContext__vfunc_149(int arg0, int a1) {
 int i = a1 < 15 ? a1 : 15; int off = i * 4; int *p = (int *)(off + (int)arg0); return p[145];
}

extern "C" int FUN_00208170(int);
struct TextureStageView150 { char pad[644]; int a[16]; int b[16]; };
extern "C" {
extern int DAT_00560a7c[8];
extern int DAT_00560a9c[8];
}
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_150(struct TextureStageView150 *p, int n, int x, int y) {
    int i;
    n = n < 15 ? n : 15;
    if (n < 8) {
        if (p->a[n] == x) {
            DAT_00560a7c[n] += 1;
        }
        if (p->b[n] == y) {
            DAT_00560a9c[n] += 1;
        }
    }
    p->a[n] = x;
    p->b[n] = y;
    if (n > 1) {
        i = n - 1;
    } else {
        i = 0;
    }
    DAT_00569330[0] = n;
    DAT_0056ad80[0] = &DAT_00569340[i];
    switch (x) {
    case 0:
        FUN_001e7500(10);
        break;
    case 2:
        FUN_001e74b0(10);
        FUN_00208170(1);
        break;
    case 1:
        FUN_001e74b0(10);
        FUN_00208170(0);
        break;
    case 3:
        FUN_001e74b0(10);
        FUN_00208170(3);
        break;
    case 5:
        FUN_001e74b0(10);
        FUN_00208170(2);
        break;
    }
    DAT_00569330[0] = 0;
    DAT_0056ad80[0] = &DAT_00569340[0];
}

/* The base is kept in its own local rather than written back into the parameter; otherwise the add
 * is emitted with the operands swapped. */
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_151(int arg0, int arg1, int *arg2, int *arg3) {
    int i = arg1 < 15 ? arg1 : 15;
    int off = i * 4;
    int p = off + arg0;
    *arg2 = *(int *)(p + 644);
    *arg3 = *(int *)(p + 708);
}

struct ClutContextCB80 { char pad[836]; int f836; int f840; int f844; int f848; int f852; int f856; int f860; };
extern "C" int FUN_0017ccb0(struct ClutContextCB80 *, int, int, int *);

extern "C" int FUN_0017cb80(struct ClutContextCB80 *arg0, int arg1, int *arg2) {
    int sp3C = 0;
    int r = -1;
    switch (arg1) {
    case 0:
        if (arg0->f836 == -1) {
            arg0->f836 = FUN_0017ccb0(arg0, 0, 8, &sp3C);
            arg0->f852 = sp3C;
        }
        r = arg0->f836;
        *arg2 = 0x10000;
        break;
    case 1:
        if (arg0->f840 == -1) {
            arg0->f840 = FUN_0017ccb0(arg0, 8, 0, &sp3C);
            arg0->f856 = sp3C;
        }
        r = arg0->f840;
        *arg2 = 0x10000;
        break;
    case 3:
    case 2:
        if (arg0->f844 == -1) {
            arg0->f844 = FUN_0017ccb0(arg0, 4, 4, &sp3C);
            arg0->f860 = sp3C;
        }
        *arg2 = 0x10000;
        r = arg0->f844;
        break;
    case 9:
        *arg2 = 7;
        break;
    case 10:
        *arg2 = 8;
        break;
    }
    return r;
}

extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_122(void) {

}
