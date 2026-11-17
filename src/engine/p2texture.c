#pragma push
#pragma readonly_strings on
#include <stdio.h>
#include "dw4/sony/libkernl.h"
#include "dw4/p2/p2core.h"
#include "dw4/p2/p2pool.h"
#include "dw4/p2/p2texture.h"
#include "dw4/p2/p2multipass.h"
#include "dw4/p2/dmaChannel.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))
void FUN_001f76f0(int count, int *regs);
int FUN_001f74e0(long long t);
void FUN_001f7500(void *finish);

struct N_208210 *FUN_00208210(void);
void FUN_00208f20(int arg0);
void FUN_00209780(char arg0, unsigned char arg1, int arg2);
int FUN_0020b7f0(struct N_20b7f0 *arg0);

extern void *DAT_0056c0d0;
extern void *DAT_0056c0d8;
extern void *DAT_0056c0e0[17];
extern unsigned int DAT_0056c128;

extern long long DAT_0056b020[4];
extern long long DAT_0056c068;
extern short DAT_00568e08[8];
extern short DAT_00568e0a[8];
extern short DAT_00568e12[8];
extern short DAT_00568e1c[4];
extern short DAT_00568e22[8];
extern short DAT_00568e24[8];
extern const char text_textureLoadedPredicate[];
extern const char text_textureDeferredPredicate[];
extern int DAT_0056c060[4];
extern int DAT_0056c078[4];
extern int DAT_004917b0[4];
extern int DAT_00491860[4];
extern int DAT_004918a0[4];
extern int DAT_004918b0[4];
extern int DAT_00568e28[4];
extern int DAT_00568e30[4];
extern int DAT_0056c138[4];
extern int DAT_0056c140[4];
extern long long DAT_0056c148[4];
extern int DAT_0056c130[4];

void FUN_00208170(int arg0) {
    int idx;
    long long v;
    int bits;
    long long b64;

    idx = p2CurrentProgram * 4;
    *(int *)((char *)p2TextureCombineMode + idx) = arg0;
    v = DAT_0056b020[0] & ~((long long)0xF << idx);
    DAT_0056b020[0] = v;
    bits = ((arg0 * 2) | ((*(unsigned int *)((char *)p2ProgramFlags + idx) >> 0xA) & 1)) & 0xF;
    p2DirtyFlags |= 0x111;
    b64 = bits;
    DAT_0056b020[0] = v | (b64 << idx);
}

unsigned short FUN_00208200(int *p)
{
    return *(unsigned short *)((char *)p + 62);
}

struct N_208210 {
    long long q0; long long q8; char pad16[8]; struct N_208210 *next; char pad28[4]; int f32; int f36; char pad40[4]; int f44; char pad48[22];
    char lo:7; char flag:1; char f71; char f72;
};
struct N_208210 *FUN_00208210(void) {
    struct N_208210 *o;
    if (p2FreeTextures == 0) {
        p2GrowPool(0xA, &p2FreeTextures);
    }
    o = (struct N_208210 *)p2FreeTextures;
    p2FreeTextures = (struct p2TextureRecord *)o->next;
    o->lo = 0;
    o->q8 = 0;
    o->q0 = 0;
    o->flag = 0;
    o->f36 = 0;
    o->f32 = 0;
    o->f44 = 0;
    o->f72 = 0;
    o->f71 = 0;
    return o;
}

typedef struct O {
    long long f0;
    long long f8;
    int pad[2];
    void *f24;
    int f28;
    char pad2[38];
    signed char lo : 7;
    unsigned char hi : 1;
} O;
static void FUN_002082b0(O *arg0) {
    arg0->lo = 0;
    arg0->f8 = 0;
    arg0->f0 = 0;
    arg0->f24 = p2FreeTextures;
    arg0->f28 = 0;
    p2FreeTextures = (struct p2TextureRecord *)arg0;
}

struct B_2082f0 { char pad[24]; int f24; int f28; char pad2[24]; int f56; short s60; short s62; short f64; };
void FUN_002082f0(void) {
    unsigned int i;
    unsigned int j;
    struct B_2082f0 *temp_v0_2;

    i = 0;
    p2FreeTextures = 0;
    DAT_0056c060[0] = 0x4000;
    do {
        DAT_0056c0e0[i] = 0;
        i += 1;
    } while (i < 0x11U);
    DAT_0056c128 = 0;
    p2GrowPool(0xA, &p2FreeTextures);
    temp_v0_2 = (struct B_2082f0 *)FUN_00208210();
    DAT_0056c0d0 = temp_v0_2;
    temp_v0_2->f24 = 0;
    ((struct B_2082f0 *)DAT_0056c0d0)->f28 = 0;
    p2GetTextureBase(&temp_v0_2->f56);
    temp_v0_2->f64 = DAT_0056c060[0] - temp_v0_2->f56;
    DAT_0056c0d8 = DAT_0056c0d0;
    DAT_0056c078[0] = temp_v0_2->f56;
    if (p2FirstOpen != 0) {
        p2RegisterPredicateName(textureLoadedPredicate, text_textureLoadedPredicate);
        p2RegisterPredicateName(textureDeferredPredicate, text_textureDeferredPredicate);
    }
    j = 0;
    do {
        p2TextureFunction[j] = 0;
        j += 1;
    } while (j < 0x10U);
    FUN_00209780(0, 0x80, 0);
}

typedef struct { char p0[8]; long long f8; char p1[54]; signed char f : 7; } S_208430;

void FUN_00208430(void *arg) {
    S_208430 *arg0 = arg;
    if (arg0->f == 4 && p2DmaSequenceLastCompleted(1, arg0->f8) != 0) {
        arg0->f = 5;
    }
}

typedef struct P2ModeState {
    char pad0[70];
    signed char mode : 7;
    unsigned char top : 1;
} P2ModeState;

void FUN_002084a0(void *arg)
{
    P2ModeState *s = arg;
    const P2ModeState *view = s;

    if (view->mode == 2)
        s->mode = 3;
}

typedef struct GsTex0 {
    unsigned long long tbp0 : 14;
    unsigned long long tbw : 6;
    unsigned long long psm : 6;
    unsigned long long tw : 4;
    unsigned long long th : 4;
    unsigned long long tcc : 1;
    unsigned long long tfx : 2;
    unsigned long long cbp : 14;
    unsigned long long cpsm : 4;
    unsigned long long csm : 1;
    unsigned long long csa : 5;
    unsigned long long cld : 3;
} GsTex0;
typedef struct GsSyncState {
    char pad0[48];
    GsTex0 tex0_1;
    GsTex0 tex0_2;
    char pad64[152];
    signed char textureFunction;
} GsSyncState;
typedef struct Texture {
    char pad0[16];
    GsTex0 tex0;
    char pad24[20];
    void *clut;
    char pad48[4];
    int bufferMode;
    int address;
    char pad60[13];
    signed char function;
} Texture;

void FUN_002084e0(Texture *texture) {
    if (texture == 0) return;
    if (texture->clut != 0) {
        p2SetClut(texture->clut);
        return;
    }
    DAT_0056c068++;
    ((GsSyncState *)p2CurrentGsRegisters)->textureFunction = texture->function;
    if (texture->bufferMode != 0) {
        if (texture->bufferMode == 1) {
            texture->address = DAT_00568e12[0] ? 0 : DAT_00568e1c[0];
        }
        if (texture->bufferMode == 2) {
            texture->address = DAT_00568e12[0] ? DAT_00568e1c[0] : 0;
        }
        if (texture->bufferMode == 3) {
            texture->address = DAT_00568e1c[0] * 2;
        }
        texture->address = texture->address << 5;
    }
    if (p2CurrentProgram == 0) {
        ((GsSyncState *)p2CurrentGsRegisters)->tex0_1.tbp0 = texture->address;
        ((GsSyncState *)p2CurrentGsRegisters)->tex0_1.tbw = texture->tex0.tbw;
        ((GsSyncState *)p2CurrentGsRegisters)->tex0_1.psm = texture->tex0.psm;
        ((GsSyncState *)p2CurrentGsRegisters)->tex0_1.tw = texture->tex0.tw;
        ((GsSyncState *)p2CurrentGsRegisters)->tex0_1.th = texture->tex0.th;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x48000040LL;
    } else {
        ((GsSyncState *)p2CurrentGsRegisters)->tex0_2.tbp0 = texture->address;
        ((GsSyncState *)p2CurrentGsRegisters)->tex0_2.tbw = texture->tex0.tbw;
        ((GsSyncState *)p2CurrentGsRegisters)->tex0_2.psm = texture->tex0.psm;
        ((GsSyncState *)p2CurrentGsRegisters)->tex0_2.tw = texture->tex0.tw;
        ((GsSyncState *)p2CurrentGsRegisters)->tex0_2.th = texture->tex0.th;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x48000080LL;
        if (p2CurrentProgram == 1 && texture->bufferMode == 0) p2UploadTex0Context2();
    }
}

void FUN_00208f20(int arg0) {
    int temp_a3;

    temp_a3 = *(int *)0x569330 * 2;
    *(int *)0x56B028 = (int) (*(int *)0x56B028 & ~(3 << temp_a3));
    *(int *)0x56B028 = (int) (*(int *)0x56B028 | ((arg0 & 3) << temp_a3));
}

typedef struct P_208f70 { char pad[52]; unsigned char b0:3; unsigned char mode:2; unsigned char b5:3; char pad2[7]; unsigned char c0:3; unsigned char cmode:2; unsigned char c5:3; } P_208f70;
void FUN_00208f70(int arg0) {
    int temp_a2;
    long long temp_a1;

    FUN_00208f20(arg0);
    if (p2CurrentProgram == 0) {
        p2TextureFunction[p2CurrentProgram] = arg0;
        ((P_208f70 *)p2CurrentGsRegisters)->mode = arg0;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x40;
    } else {
        p2TextureFunction[p2CurrentProgram] = arg0;
        ((P_208f70 *)p2CurrentGsRegisters)->cmode = arg0;
        temp_a2 = p2DirtyFlags | 0x40;
        temp_a1 = p2GsDirtyRegisters | 0x80;
        p2DirtyFlags = temp_a2;
        p2GsDirtyRegisters = temp_a1;
        if (p2CurrentProgram == 1) {
            p2UploadTex0Context2();
        }
    }
    p2DirtyFlags |= 0x11;
}

typedef struct Obj_209090 { char pad[52]; unsigned char a52 : 2; unsigned char b52 : 1; unsigned char c52 : 2; unsigned char r52 : 3; char pad2[7]; unsigned char a60 : 2; unsigned char b60 : 1; unsigned char c60 : 2; unsigned char r60 : 3; } Obj_209090;
void FUN_00209090(int arg0, int arg1) {
    FUN_00208f20(arg0);
    if (p2CurrentProgram == 0) {
        *(int *)((char *)p2TextureFunction + p2CurrentProgram * 4) = arg0;
        ((Obj_209090 *)p2CurrentGsRegisters)->c52 = arg0;
        ((Obj_209090 *)p2CurrentGsRegisters)->b52 = arg1;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x40;
    } else {
        *(int *)((char *)p2TextureFunction + p2CurrentProgram * 4) = arg0;
        ((Obj_209090 *)p2CurrentGsRegisters)->c60 = arg0;
        ((Obj_209090 *)p2CurrentGsRegisters)->b60 = arg1;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x80;
        if (p2CurrentProgram == 1) {
            p2UploadTex0Context2();
        }
    }
    p2DirtyFlags |= 0x11;
}

typedef struct R { unsigned char a : 2; unsigned char b : 2; unsigned short c : 10; unsigned long long d : 10; unsigned long long e : 10; unsigned short f : 10; } R;
typedef struct P_209210 { char pad[52]; unsigned char x0 : 2; unsigned char fl : 1; unsigned char r : 5; char pad2[7]; unsigned char y0 : 2; unsigned char fl2 : 1; unsigned char r2 : 5; char pad3[3]; R r64; R r72; } P_209210;
void FUN_00209210(int arg0, int arg1, int arg2, long long arg3, long long arg4, int arg5, int arg6) {
    int temp_a2;
    R *q;
    long long temp_a1;
    if (p2CurrentProgram == 0) {
        ((P_209210 *)p2CurrentGsRegisters)->fl = arg6;
        ((P_209210 *)p2CurrentGsRegisters)->r64.a = arg0;
        ((P_209210 *)p2CurrentGsRegisters)->r64.b = arg1;
        ((P_209210 *)p2CurrentGsRegisters)->r64.c = arg2;
        q = &((P_209210 *)p2CurrentGsRegisters)->r64;
        q->d = (int)arg3;
        q->e = (int)arg4;
        q->f = arg5;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x140;
    } else {
        ((P_209210 *)p2CurrentGsRegisters)->fl2 = arg6;
        ((P_209210 *)p2CurrentGsRegisters)->r72.a = arg0;
        ((P_209210 *)p2CurrentGsRegisters)->r72.b = arg1;
        ((P_209210 *)p2CurrentGsRegisters)->r72.c = arg2;
        q = &((P_209210 *)p2CurrentGsRegisters)->r72;
        q->d = (int)arg3;
        q->e = (int)arg4;
        q->f = arg5;
        temp_a2 = p2DirtyFlags | 0x40;
        temp_a1 = p2GsDirtyRegisters | 0x280;
        p2DirtyFlags = temp_a2;
        p2GsDirtyRegisters = temp_a1;
        if (p2CurrentProgram == 1) {
            p2UploadTex0Context2();
        }
    }
}

typedef struct B_2094c0 {
    unsigned short r0 : 2;
    unsigned short m : 3;
    unsigned short f : 1;
    unsigned short c : 3;
    unsigned short r1 : 7;
} B_2094c0;
typedef struct P_2094c0 { char pad[104]; B_2094c0 b104; char pad2[6]; B_2094c0 b112; } P_2094c0;
void FUN_002094c0(int arg0, int arg1) {
    if (p2CurrentProgram == 0) {
        ((P_2094c0 *)p2CurrentGsRegisters)->b104.f = arg0;
        ((P_2094c0 *)p2CurrentGsRegisters)->b104.c = arg1;
        if (((P_2094c0 *)p2CurrentGsRegisters)->b104.c == 1 || ((P_2094c0 *)p2CurrentGsRegisters)->b104.c == 0) {
            ((P_2094c0 *)p2CurrentGsRegisters)->b104.m = 0;
        }
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x2000;
    } else {
        ((P_2094c0 *)p2CurrentGsRegisters)->b112.f = arg0;
        ((P_2094c0 *)p2CurrentGsRegisters)->b112.c = arg1;
        if (((P_2094c0 *)p2CurrentGsRegisters)->b112.c == 1 || ((P_2094c0 *)p2CurrentGsRegisters)->b112.c == 0) {
            ((P_2094c0 *)p2CurrentGsRegisters)->b112.m = 0;
        }
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x4000;
    }
}

typedef struct Obj_209650 {
    char pad[104];
    unsigned char a104 : 1; unsigned char r104 : 7;
    char pad105;
    unsigned char x106 : 3; unsigned char c106 : 2; unsigned char r106 : 3;
    char pad107;
    unsigned short d108 : 12; unsigned short r108 : 4;
    char pad110[2];
    unsigned char a112 : 1; unsigned char r112 : 7;
    char pad113;
    unsigned char x114 : 3; unsigned char c114 : 2; unsigned char r114 : 3;
    char pad115;
    unsigned short d116 : 12; unsigned short r116 : 4;
} Obj_209650;
void FUN_00209650(int arg0, int arg1, int arg2) {
    if (p2CurrentProgram == 0) {
        ((Obj_209650 *)p2CurrentGsRegisters)->a104 = arg0;
        ((Obj_209650 *)p2CurrentGsRegisters)->c106 = arg1;
        ((Obj_209650 *)p2CurrentGsRegisters)->d108 = arg2;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x2000;
    } else {
        ((Obj_209650 *)p2CurrentGsRegisters)->a112 = arg0;
        ((Obj_209650 *)p2CurrentGsRegisters)->c114 = arg1;
        ((Obj_209650 *)p2CurrentGsRegisters)->d116 = arg2;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x4000;
    }
}

struct S_209780 {
    char p[216];
    char f216;
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
    char p2[2];
    char f220;
};
void FUN_00209780(char arg0, unsigned char arg1, int arg2) {
    ((struct S_209780 *)p2CurrentGsRegisters)->f216 = arg0;
    ((struct S_209780 *)p2CurrentGsRegisters)->f220 = arg1;
    ((struct S_209780 *)p2CurrentGsRegisters)->b7 = arg2;
    p2DirtyFlags |= 0x40;
    p2GsDirtyRegisters |= 0x08000000;
}

struct G_20a590 {
    char p0[355]; unsigned char x355:6; char p1[12];
    unsigned short x368:9; char p2[14];
    unsigned short x384:14; unsigned char x386:6; unsigned char x387:6;
    unsigned short x388:14; unsigned char x390:6; unsigned char x391:6;
    unsigned short x392:11; unsigned short x394:11; unsigned short x396:11; unsigned short x398:11; unsigned char x399:2;
    unsigned short x400:12; char p4[2];
    unsigned short x404:12; char p5[2]; unsigned char x408:2;
};
typedef union { int w[4]; long long d[2]; } QW_2097f0;
typedef union { struct { unsigned short nloop : 15; unsigned short eop : 1; } b; long long d[2]; } GifTag_2097f0;
typedef union { struct { unsigned short qwc; short p2; unsigned int addr : 31; unsigned int last : 1; } b; int w[4]; } Img_2097f0;
struct Node_2097f0 { char p0[12]; struct Node_2097f0 *next; };
struct Ch_2097f0 {
    long long tag;
    long long seq;
    struct Node_2097f0 *head;
    struct Node_2097f0 *tail;
    char p24[16];
    unsigned int end;
    char p44[4];
    unsigned int cur;
    char p52[12];
    unsigned char busy : 1;
};
struct Tex_2097f0 { long long tag; char p8[40]; int addr; char p52[4]; int tbp; unsigned short width; unsigned short height; char p64[2]; unsigned short format; };
void FUN_002097f0(struct Tex_2097f0 **list, int count) {
    int p2DmaPacketQueued();
    int FUN_001f7e90();
    extern int DAT_00569128[4];
    extern long long DAT_00569168[4];
    extern unsigned int DAT_00491730[];
    extern unsigned int DAT_00491770[];
    extern int DAT_00491820[];
    extern QW_2097f0 DAT_004917f0;
    extern Img_2097f0 DAT_00491800;
    extern GifTag_2097f0 DAT_00491810;
    struct Tex_2097f0 *t;
    p2DmaPredicate *n;
    QW_2097f0 *q;
    int fmt;
    int w;
    long long seq;
    int rows;
    int y;
    int max;
    int h;
    int addr;
    unsigned int qwc;

    DIntr();
    if (p2DmaPacketQueued(2, p2DmaLastPacket[P2_DMA_GIF]) != 0) {
        seq = p2DmaCurrentPacket[P2_DMA_GIF]->f8;
        if (seq >= 0 && p2DmaLastPacket[P2_DMA_GIF]->f8 >= seq && p2DmaLastPacket[P2_DMA_GIF]->cursor < p2DmaLastPacket[P2_DMA_GIF]->limit) {
            n = p2DmaCurrentPacket[P2_DMA_GIF]->predicates;
            p2DmaLastPacket[P2_DMA_GIF]->ready = 0;
            p2DmaCurrentPacket[P2_DMA_GIF]->f8 = -1;
            if (n != 0) {
                p2DmaCurrentPacket[P2_DMA_GIF]->predicates = 0;
                p2DmaCurrentPacket[P2_DMA_GIF]->lastPredicate = 0;
                n->next = p2DmaLastPacket[P2_DMA_GIF]->predicates;
                if (p2DmaLastPacket[P2_DMA_GIF]->predicates == 0) {
                    p2DmaLastPacket[P2_DMA_GIF]->lastPredicate = n;
                }
                p2DmaLastPacket[P2_DMA_GIF]->predicates = n;
            }
            DAT_00569128[0]++;
            p2DmaCurrentPacket[P2_DMA_GIF] = p2DmaLastPacket[P2_DMA_GIF];
            DAT_00569168[0]--;
        }
    }
    EIntr();
    do {
        ((struct G_20a590 *)p2CurrentGsRegisters)->x391 = DAT_004917b0[(*list)->format];
        ((struct G_20a590 *)p2CurrentGsRegisters)->x390 = ((*list)->width + 63) / 64;
        ((struct G_20a590 *)p2CurrentGsRegisters)->x400 = (*list)->width;
        ((struct G_20a590 *)p2CurrentGsRegisters)->x408 = 0;
        t = *list;
        fmt = t->format;
        w = t->width;
        addr = t->addr;
        rows = t->height;
        max = 0xfffe0 / (w * DAT_00491730[fmt]);
        y = 0;
        while (rows > 0) {
            h = rows < max ? rows : max;
            /* matching construct: permuter — qwc computed before the transfer-register stores */
            qwc = (DAT_00491730[fmt] * (w * h) + 31) >> 5;
            ((struct G_20a590 *)p2CurrentGsRegisters)->x388 = t->tbp;
            ((struct G_20a590 *)p2CurrentGsRegisters)->x396 = 0;
            ((struct G_20a590 *)p2CurrentGsRegisters)->x398 = y;
            ((struct G_20a590 *)p2CurrentGsRegisters)->x404 = h;
            FUN_001f7e90(4, DAT_00491820, 0);
            /* matching construct: statement-order search — y += h placed before the GIF tag NLOOP store */
            y += h;
            DAT_00491810.b.nloop = qwc;
            rows -= h;
            DAT_00491800.b.qwc = DAT_00491810.b.nloop;
            q = (QW_2097f0 *)p2DmaCurrentPacket[P2_DMA_GIF]->cursor;
            DAT_00491800.b.addr = addr;
            q->w[0] = DAT_004917f0.w[0];
            q->w[1] = DAT_004917f0.w[1];
            q->w[2] = DAT_004917f0.w[2];
            q->w[3] = DAT_004917f0.w[3];
            q++;
            q->d[0] = DAT_00491810.d[0];
            q->d[1] = DAT_00491810.d[1];
            q++;
            q->w[0] = DAT_00491800.w[0];
            q->w[1] = DAT_00491800.w[1];
            q->w[2] = DAT_00491800.w[2];
            q->w[3] = DAT_00491800.w[3];
            q++;
            p2DmaCurrentPacket[P2_DMA_GIF]->cursor = (unsigned int)q;
            t = *list;
            fmt = t->format;
            w = t->width;
            addr += (DAT_00491770[fmt] * (w * h)) >> 1;
        }
        t->tag = p2DmaCurrentPacket[P2_DMA_GIF]->sequence;
        p2AddDmaCompletion(2, FUN_002084a0, *list);
        count--;
        list++;
        if (count != 0 && p2DmaCurrentPacket[P2_DMA_GIF]->cursor > p2DmaCurrentPacket[P2_DMA_GIF]->limit) {
            p2SubmitDmaPacket(2);
        }
    } while (count != 0);
    p2SubmitDmaPacket(2);
}

int FUN_00209cc0(int a) {
    int n;
    for (n = 0; (a >>= 1) != 0; n++) {}
    return n;
}

struct A0_20a590 { char p0[56]; int f56; unsigned short f60; char p1[4]; unsigned short f66; char p2[2]; signed char f70:7; char p3; char f72; };
void FUN_0020a590(struct A0_20a590 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    int sp0;
    int s0;
    int v;
    int w;
    short u;
    short m;
    int pr;
    int t;
    sp0 = ((struct G_20a590 *)p2CurrentGsRegisters)->x355;
    s0 = (p2GetDisplayFlags() & 2) != 0;
    arg0->f72 = 1;
    switch (arg0->f70) {
    case 1:
        if (FUN_0020b7f0((struct N_20b7f0 *)arg0) == 0) return;
        arg0->f70 = 3;
        break;
    case 4:
    case 3:
    case 5:
        arg0->f70 = 3;
        break;
    }
    ((struct G_20a590 *)p2CurrentGsRegisters)->x391 = DAT_004917b0[arg0->f66];
    ((struct G_20a590 *)p2CurrentGsRegisters)->x388 = arg0->f56;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x390 = (arg0->f60 + 63) / 64;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x387 = sp0;
    if (arg7 != 0) {
        ((struct G_20a590 *)p2CurrentGsRegisters)->x384 = ((struct G_20a590 *)p2CurrentGsRegisters)->x368 << 5;
    } else {
        ((struct G_20a590 *)p2CurrentGsRegisters)->x384 = (DAT_00568e12[0] != 0 && !s0) ? (DAT_00568e08[0] * DAT_00568e0a[0]) / 64 : 0;
    }
    if (s0 != 0) u = DAT_00568e22[0]; else u = DAT_00568e08[0];
    ((struct G_20a590 *)p2CurrentGsRegisters)->x386 = u / 64;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x396 = arg3;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x398 = arg4;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x392 = arg1;
    if (s0 != 0) m = DAT_00568e24[0]; else m = DAT_00568e0a[0];
    ((struct G_20a590 *)p2CurrentGsRegisters)->x394 = m - (arg6 + arg2);
    ((struct G_20a590 *)p2CurrentGsRegisters)->x399 = 0;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x400 = arg5;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x404 = arg6;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x408 = 2;
    FUN_001f76f0(4, &DAT_00491860[0]);
}

void FUN_0020a990(void *srcTexture, int srcX, int srcY, void *dstTexture, int dstX, int dstY, int width, int height) {
    extern int DAT_00491870[4];
    int xdir;
    int ydir;
    struct A0_20a590 *dst;
    struct A0_20a590 *src;
    xdir = srcX < dstX;
    ydir = srcY < dstY;
    dst = dstTexture;
    src = srcTexture;
    dst->f72 = 1;
    switch (dst->f70) {
    case 1:
        if (FUN_0020b7f0((struct N_20b7f0 *)dst) == 0) return;
        dst->f70 = 3;
        break;
    case 4:
    case 3:
    case 5:
        dst->f70 = 3;
        break;
    }
    src->f72 = 1;
    switch (src->f70) {
    case 1:
        if (FUN_0020b7f0((struct N_20b7f0 *)src) == 0) return;
        src->f70 = 3;
        break;
    case 4:
    case 3:
    case 5:
        src->f70 = 3;
        break;
    }
    ((struct G_20a590 *)p2CurrentGsRegisters)->x387 = DAT_004917b0[src->f66];
    ((struct G_20a590 *)p2CurrentGsRegisters)->x384 = src->f56;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x386 = (src->f60 + 63) / 64;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x391 = DAT_004917b0[dst->f66];
    ((struct G_20a590 *)p2CurrentGsRegisters)->x388 = dst->f56;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x390 = (dst->f60 + 63) / 64;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x396 = dstX;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x398 = dstY;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x392 = srcX;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x394 = srcY;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x399 = (xdir << 1) + ydir;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x400 = width;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x404 = height;
    ((struct G_20a590 *)p2CurrentGsRegisters)->x408 = 2;
    FUN_001f76f0(4, &DAT_00491870[0]);
}

typedef struct T_20ad60 {
    char p0[18];
    unsigned short r18 : 4;
    unsigned short psm18 : 6;
    unsigned short t18 : 6;
    char p20[36];
    int f56;
    unsigned short f60;
    unsigned short f62;
    char p64[2];
    unsigned short f66;
    char p68[2];
    signed char f70 : 7;
    char p71;
    char f72;
} T_20ad60;
typedef struct RT_20ad60 {
    char p0[136];
    union { struct { short a; short pad; short b; short c; } h; long long q; } u136;
    long long q144;
    char p152[24];
    union { long long q; struct { unsigned char x : 2; } b; } u176;
    char p184[168];
    union { long long q; int i; struct { unsigned short fbp : 9; unsigned short r : 7; unsigned char fbw : 6; unsigned char r2 : 2; unsigned char psm : 6; } f; } u352;
    long long q360;
    union { long long q; int i; struct { unsigned short zbp : 9; unsigned short r : 7; char pad; unsigned char zpsm : 4; } z; } u368;
    long long q376;
} RT_20ad60;
int FUN_0020ad60(T_20ad60 *color, T_20ad60 *depth) {
    extern int DAT_00491880[4];
    extern int DAT_00491890[4];
    int s0;
    RT_20ad60 *p;

    s0 = ((unsigned int) p2ProgramFlags[p2CurrentProgram] >> 0x17) & 1;
    color->f72 = 1;
    switch (color->f70) {
    case 1:
        if (FUN_0020b7f0((struct N_20b7f0 *)color) == 0) return 0;
        color->f70 = 3;
        if (depth != 0) {
            depth->f72 = 1;
            if (FUN_0020b7f0((struct N_20b7f0 *)depth) == 0) return 0;
            depth->f70 = 3;
        }
        break;
    case 4:
    case 3:
    case 5:
        color->f70 = 3;
        break;
    default:
        return 0;
    }
    ((RT_20ad60 *)p2CurrentGsRegisters)->u136.h.a = (0x800 - (color->f60 >> 1)) * 0x10;
    ((RT_20ad60 *)p2CurrentGsRegisters)->u136.h.b = (0x800 - (color->f62 >> 1)) * 0x10;
    if (DAT_00568e28[0] == -1) {
        DAT_00568e28[0] = (int)color;
        DAT_0056c138[0] = ((RT_20ad60 *)p2CurrentGsRegisters)->u352.i;
        DAT_0056c140[0] = ((RT_20ad60 *)p2CurrentGsRegisters)->u368.i;
        DAT_0056c148[0] = ((RT_20ad60 *)p2CurrentGsRegisters)->u176.q;
    }
    if (depth != 0) {
        DAT_00568e30[0] = (int)depth;
        ((RT_20ad60 *)p2CurrentGsRegisters)->u368.z.zbp = ((depth->f56 << 9) / 8) / 2048;
        if (depth->f66 == 12 && color->f66 == 3) {
            depth->f66 = 11;
            color->f66 = 2;
            color->psm18 = DAT_004917b0[2];
        }
        ((RT_20ad60 *)p2CurrentGsRegisters)->u368.z.zpsm = DAT_004917b0[depth->f66] & 0xF;
    } else {
        DAT_00568e30[0] = -1;
    }
    ((RT_20ad60 *)p2CurrentGsRegisters)->u352.f.fbp = ((color->f56 << 9) / 8) / 2048;
    ((RT_20ad60 *)p2CurrentGsRegisters)->u352.f.fbw = (unsigned int)color->f60 >> 6;
    ((RT_20ad60 *)p2CurrentGsRegisters)->u352.f.psm = DAT_004917b0[color->f66];
    ((RT_20ad60 *)p2CurrentGsRegisters)->u176.b.x = 0;
    if (s0 != 0) {
        p = (RT_20ad60 *)p2CurrentGsRegisters;
        p->q360 = p->u352.q;
        p->q144 = p->u136.q;
        p->q376 = p->u368.q;
        FUN_001f76f0(3, &DAT_00491890[0]);
    }
    FUN_001f76f0(4, &DAT_00491880[0]);
    return 1;
}

typedef struct S_20b110 {
    char p0[136]; union { struct { short a; short pad; short b; short c; } h; long long q; } u136; long long q144;
    char p152[24]; long long q176; char p184[168]; union { long long q; int i; } u352; long long q360; union { long long q; int i; } u368; long long q376;
} S_20b110;
void FUN_0020b110(void) {
    short v;
    int a1;
    int s0;
    S_20b110 *p;

    s0 = ((unsigned int) p2ProgramFlags[p2CurrentProgram] >> 0x17) & 1;
    a1 = (p2GetDisplayFlags() & 2) != 0;
    if (DAT_00568e28[0] != -1) {
        ((S_20b110 *)p2CurrentGsRegisters)->u352.i = DAT_0056c138[0];
        ((S_20b110 *)p2CurrentGsRegisters)->u368.i = DAT_0056c140[0];
        p = (S_20b110 *)p2CurrentGsRegisters;
        p->q176 = DAT_0056c148[0];
        if (a1 != 0) v = DAT_00568e22[0]; else v = DAT_00568e08[0];
        p->u136.h.a = (0x800 - (v >> 1)) * 0x10;
        if (a1 != 0) v = DAT_00568e24[0]; else v = DAT_00568e0a[0];
        ((S_20b110 *)p2CurrentGsRegisters)->u136.h.b = (0x800 - (v >> 1)) * 0x10;
        if (s0 != 0) {
            p = (S_20b110 *)p2CurrentGsRegisters;
            p->q360 = p->u352.q;
            p->q144 = p->u136.q;
            p->q376 = p->u368.q;
            FUN_001f76f0(3, &DAT_004918b0[0]);
        }
        FUN_001f76f0(4, &DAT_004918a0[0]);
        DAT_00568e28[0] = -1;
        DAT_00568e30[0] = -1;
    }
}

long long FUN_0020b270(long long *arg0) {
    return *arg0;
}

typedef struct N_20b280 {
    long long f0;
    long long f8;
    char p16[8];
    struct N_20b280 *f24;
    struct N_20b280 *f28;
    char p32[24];
    int f56;
    char p60[4];
    unsigned short f64;
    char p66[4];
    char m : 7;
    char hi : 1;
} N_20b280;

void FUN_0020b280(N_20b280 *arg0, N_20b280 *arg1, int arg2) {
    long long var_s5;
    unsigned short a0;
    int x;
    N_20b280 *s4;
    int s3;
    N_20b280 *v0;
    int var_s4;
    N_20b280 *s3n;
    long long old;
    int a0b;
    var_s5 = arg1->m;
    while (arg2 != arg1->f56) {
        a0 = arg1->f64;
        s4 = arg1->f28;
        s3 = arg2 >= arg1->f56 + a0;
        if (s4 != 0 && s4->m == 0) {
            if (s3 != 0) {
                s4->f64 += a0;
            } else {
                s4->f64 += ((arg2 - arg1->f56) & 0xFFFF);
            }
        } else {
            v0 = (N_20b280 *)FUN_00208210();
            v0->f56 = arg1->f56;
            v0->f24 = arg1;
            v0->f28 = arg1->f28;
            arg1->f28 = v0;
            if (s4 != 0) {
                s4->f24 = v0;
            } else {
                DAT_0056c0d0 = v0;
            }
            if (s3 != 0) {
                v0->f64 = arg1->f64;
            } else {
                { int d = arg2 - arg1->f56; v0->f64 = d; }
            }
        }
        if (s3 != 0) {
            N_20b280 *t1 = arg1->f28;
            N_20b280 *a3 = arg1->f24;
            if (t1 != 0) {
                t1->f24 = a3;
            }
            if (a3 != 0) {
                a3->f28 = arg1->f28;
            }
            arg1->f24 = 0;
            arg1->f28 = 0;
            old = arg1->m;
            arg1->m = 1;
            arg1->f56 = -1;
            if (var_s5 == 0) {
                FUN_002082b0((O *)arg1);
            } else {
                arg1->hi = 1;
            }
            arg1 = a3;
            var_s5 = a3->m;
        } else {
            arg1->f64 -= ((arg2 - arg1->f56) & 0xFFFF);
            arg1->f56 = arg2;
        }
    }
    var_s4 = arg1->f64;
    goto reload;
    while (((s3n != 0) ^ 1) == 0 && (arg2 + arg0->f64) > (arg1->f56 + var_s4)) {
        unsigned short t;
        old = s3n->m;
        t = s3n->f64;
        arg1->f24 = s3n->f24;
        var_s4 += t;
        if (s3n->f24 != 0) {
            s3n->f24->f28 = arg1;
        }
        s3n->f24 = 0;
        s3n->f28 = 0;
        s3n->m = 1;
        s3n->f56 = -1;
        if (old == 0) {
            FUN_002082b0((O *)s3n);
        } else {
            s3n->hi = 1;
        }
    reload:
        s3n = arg1->f24;
    }
    a0b = arg1->f56 + var_s4;
    x = arg2 + arg0->f64;
    if (x < a0b) {
        if (s3n != 0 && s3n->m == 0) {
            s3n->f64 += ((a0b - x) & 0xFFFF);
            s3n->f56 = arg2 + arg0->f64;
        } else {
            v0 = (N_20b280 *)FUN_00208210();
            v0->f56 = arg2 + arg0->f64;
            { int d = var_s4 - arg0->f64; v0->f64 = d; }
            v0->f24 = s3n;
            v0->f28 = arg1;
            arg1->f24 = v0;
            if (s3n != 0) {
                s3n->f28 = v0;
            }
        }
    }
    arg0->f56 = arg2;
    arg0->f24 = arg1->f24;
    arg0->f28 = arg1->f28;
    if (arg1->f28 != 0) {
        arg1->f28->f24 = arg0;
    }
    if (arg1->f24 != 0) {
        arg1->f24->f28 = arg0;
    }
    if (DAT_0056c0d0 == arg1) {
        DAT_0056c0d0 = arg0;
    }
    old = arg1->m;
    arg1->f24 = 0;
    arg1->f28 = 0;
    arg1->m = 1;
    arg1->f56 = -1;
    if (old == 0) {
        FUN_002082b0((O *)arg1);
        return;
    }
    arg1->hi = 1;
}

typedef struct N_20b650 {
    long long f0;
    long long f8;
    char p16[8];
    struct N_20b650 *f24;
    char p28[28];
    int f56;
    char p60[4];
    unsigned short f64;
    char p66[4];
    volatile char m : 7;
    char hi : 1;
    char p71;
    char f72;
} N_20b650;
typedef struct A_20b650 {
    char p0[64];
    unsigned short f64;
    char p66[2];
    unsigned short f68;
} A_20b650;

N_20b650 *FUN_0020b650(A_20b650 *arg0, int *arg1, int arg2, long long *arg3) {
    N_20b650 *sent;
    N_20b650 *v;
    int pass;
    long long best;
    N_20b650 *n;
    int lim;
    int a5;
    int mask;
    int base;

    sent = 0;
    v = DAT_0056c0d8;
    best = 0;
    pass = 0;
    while (pass < 2) {
        while (v != sent) {
            if (v->f72 == 0 && (v->m == 5 || v->m == 0 || (arg2 == 0 && v->m == 4))) {
                base = v->f56;
                a5 = base + v->f64;
                mask = arg0->f68;
                lim = (base + mask) & ~mask;
                n = v->f24;
                best = v->f8;
                while (((n != 0) ^ 1) == 0 && n->f72 == 0 && (n->m == 5 || n->m == 0 || (arg2 == 0 && n->m == 4)) && a5 < lim + arg0->f64) {
                    if (best < n->f8) {
                        best = n->f8;
                    }
                    a5 += n->f64;
                    n = n->f24;
                }
                if (a5 >= lim + arg0->f64) {
                    *arg1 = lim;
                    break;
                }
            }
            v = v->f24;
        }
        if (*arg1 != -1) {
            break;
        }
        pass++;
        v = DAT_0056c0d0;
        sent = DAT_0056c0d8;
    }
    if (arg3 != 0) {
        *arg3 = best;
    }
    return v;
}

struct W_20b7f0 { long long f0; char p8[24]; int f32; char p36[12]; int f48; char p52[12]; unsigned char b0:3; unsigned char b3:1; unsigned char b4:4; };
struct V_20b7f0 { long long f0; long long f8; };
struct N_20b7f0 { long long f0; long long f8; char p16[8]; int f24; char p28[42]; char m:7; char hi:1; };
int FUN_0020b7f0(struct N_20b7f0 *arg0) {
    int p2AddFinishFunc();
    int r;
    long long t;
    int s0;
    p2DmaPacket *p;
    long long *lp;
    r = -1;
    s0 = (int)FUN_0020b650((struct A_20b650 *)arg0, &r, 1, 0);
    if (r >= 0) {
        FUN_0020b280((N_20b280 *)arg0, (N_20b280 *)s0, r);
    } else {
        s0 = (int)FUN_0020b650((struct A_20b650 *)arg0, &r, 0, &t);
        if (r >= 0) {
            if (DAT_0056c130[0] == 1) {
                p2AddFinishFunc(FUN_001f7500, 0);
                t = p2DmaCurrentPacket[P2_DMA_VIF1]->sequence;
                p2SubmitDmaPacket(1);
                FUN_0020b280((N_20b280 *)arg0, (N_20b280 *)s0, r);
                p2AddDmaPredicate(2, FUN_001f74e0, t);
            } else {
                p = p2DmaCurrentPacket[P2_DMA_VIF1];
                if (p->sequence == t || p->chain == p->cursor) {
                    p->b3 = 1;
                }
                p2SubmitDmaPacket(1);
                FUN_0020b280((N_20b280 *)arg0, (N_20b280 *)s0, r);
                p2AddDmaPredicate(2, textureDeferredPredicate, t);
            }
            lp = &p2DmaCurrentPacket[P2_DMA_GIF]->f8;
            if (*lp < t) {
                *lp = t;
            }
        }
    }
    if (r >= 0) {
        arg0->m = 2;
        arg0->f0 = 0;
        arg0->f8 = 0;
        DAT_0056c0d8 = (void *)arg0->f24;
        if (DAT_0056c0d8 == 0) {
            DAT_0056c0d8 = DAT_0056c0d0;
        }
    }
    return (unsigned char)((~r == 0) ^ 1);
}

typedef struct N_20b9d0 {
    char pad0[8];
    long long f8;
    char pad1[16];
    struct N_20b9d0 *f32;
    struct N_20b9d0 *f36;
    char pad2[30];
    char m : 7;
    char hi : 1;
    char f71;
    char f72;
} N_20b9d0;

static inline int N_20b9d0_GetM(const N_20b9d0 *n) {
    return n->m;
}

static inline void N_20b9d0_Set(N_20b9d0 *n) {
    n->m = 4;
    n->f8 = p2DmaCurrentPacket[P2_DMA_VIF1]->sequence;
    p2AddDmaCompletion(1, &FUN_00208430, n);
}

void FUN_0020b9d0(void *arg0) {
    N_20b9d0 *n = (N_20b9d0 *)arg0;
    N_20b9d0 *var_s0;
    N_20b9d0 *c;
    int a1;
    int t;
    a1 = (n->f36 != 0) + 1;
    var_s0 = n->f32;
    t = n->f71 + a1;
    if (n->f72 == 0) {
        p2ReserveDmaCompletions(t);
        DIntr();
        N_20b9d0_Set(n);
        c = n->f36;
        if (c != 0) {
            c->m = 4;
            n->f36->f8 = p2DmaCurrentPacket[P2_DMA_VIF1]->sequence;
            p2AddDmaCompletion(1, &FUN_00208430, n->f36);
        }
        while (var_s0 != 0) {
            if (N_20b9d0_GetM(var_s0) != 1) {
                N_20b9d0_Set(var_s0);
            }
            var_s0 = var_s0->f32;
        }
        EIntr();
    }
}

typedef struct P2Texture {
    long long f0;
    char p8[8];
    GsTex0 tex0;
    int f24;
    char p28[20];
    void *image;
    int deferred;
    int f56;
    unsigned short width;
    unsigned short height;
    unsigned short f64;
    unsigned short format;
    unsigned short f68;
    signed char state : 7;
    signed char hi : 1;
    char p71[2];
    unsigned char f73;
} P2Texture;
P2Texture *p2LoadTexture(void *image, int width, int height, int format, int deferred) {
    extern int DAT_0056c0c0[4];
    extern unsigned int DAT_00491730[];
    P2Texture *t;
    int w;
    int h;

    t = (P2Texture *)FUN_00208210();
    if (t == 0) {
        DAT_0056c0c0[0]++;
        return 0;
    }
    t->deferred = deferred;
    t->hi = 0;
    t->f56 = -1;
    t->image = image;
    t->width = width;
    t->height = height;
    t->format = format;
    t->f24 = 0;
    t->f73 = (format == 1) ? 0x80 : 0;
    t->tex0.tbw = (t->width + 63) / 64;
    t->tex0.psm = DAT_004917b0[t->format];
    if (deferred == 0) {
        t->tex0.tw = FUN_00209cc0(t->width);
        t->tex0.th = FUN_00209cc0(t->height);
        t->state = 1;
    } else {
        h = w = 1;
        while (w < width) w <<= 1;
        while (h < height) h <<= 1;
        t->tex0.tw = FUN_00209cc0(w);
        t->tex0.th = FUN_00209cc0(h);
        t->state = 3;
        t->f0 = 0;
    }
    if (deferred == 0) {
        switch (format) {
        case 0: case 1: case 9: case 10: case 13: case 14:
            width = MAX(width, 8);
            height = MAX(height, 8);
            w = MIN(height, 64);
            w = MAX(width, w);
            width = MIN(width, 64);
            h = width / 2;
            h = MAX(height, h);
            break;
        case 2: case 3: case 11: case 12:
            width = MAX(width, 16);
            height = MAX(height, 8);
            h = width / 2;
            h = MIN(h, 64);
            h = MAX(height, h);
            height = MIN(height, 64);
            w = MAX(width, height);
            break;
        case 4:
            width = MAX(width, 16);
            height = MAX(height, 16);
            w = MIN(height, 128);
            w = MAX(width, w);
            width = MIN(width, 128);
            h = width / 2;
            h = MAX(height, h);
            break;
        case 5:
            width = MAX(width, 32);
            height = MAX(height, 16);
            h = MIN(width, 128);
            h = MAX(height, h);
            height = MIN(height, 128);
            w = height / 2;
            w = MAX(width, w);
            break;
        default:
            printf("Unsupported texture format in p2LoadTexture: %d\n", format);
            return (P2Texture *)-1;
        }
        t->f64 = (DAT_00491730[format] * (w * h)) >> 9;
        t->f64 = (t->f64 == 0) ? 1 : t->f64;
        t->f68 = t->f64 - 1;
        if (t->f68 >= 32 || image == 0) t->f68 = 31;
    }
    return t;
}

void FUN_0020c7b0(char *arg0, char *arg1) {
    char *p = arg0;
    while (*(char **)(p + 32) != 0) p = *(char **)(p + 32);
    *(char **)(p + 32) = arg1;
    *(int *)(arg1 + 32) = 0;
    arg0[71] = arg0[71] + 1;
}

void FUN_0020c7f0(int a0, int a1)
{
    *(int *)((char *)a0 + 36) = a1;
}

typedef struct StreamSlotState {
    char pad0[48];
    int value;
    char pad1[18];
    signed char state : 7;
    unsigned char flag : 1;
} StreamSlotState;

static inline int StreamSlotState_GetState(const StreamSlotState *s) {
    return s->state;
}

void FUN_0020c800(StreamSlotState *s) {
    if (StreamSlotState_GetState(s) != 1) {
        s->state = 6;
    }
}

void FUN_0020c840(StreamSlotState *s, int value) {
    if (StreamSlotState_GetState(s) != 1) {
        s->state = 6;
    }
    s->value = value;
}

void FUN_0020c880(int arg0) {
    if (arg0 > 0) {
        *(int *)0x56C128 = (int) (*(int *)0x56C128 | (1 << arg0));
    }
}

struct B_20c8b0 { volatile signed char m : 7; unsigned char x : 1; };
struct S_20c8b0 { char pad0[70]; volatile signed char f70 : 7; unsigned char x : 1; char f71; char f72; };
void FUN_0020c8b0(struct S_20c8b0 *arg0) {
    int s1;
    unsigned int s0;
    struct S_20c8b0 *o;
    if (arg0->f70 == 4 || arg0->f70 == 5 || arg0->f70 == 1) return;
    if (arg0->f72 != 0) {
        arg0->f72 = 0;
        FUN_0020b9d0(arg0);
        DAT_0056c128 &= ~1;
        s0 = DAT_0056c128;
        s1 = 0;
        while (s0 != 0) {
            s0 = s0 >> 1;
            s1 += 1;
            if (s0 & 1) {
                o = DAT_0056c0e0[s1];
                if (o != 0 && (((struct B_20c8b0 *)((char *)o + 70))->m == 3 || ((struct B_20c8b0 *)((char *)o + 70))->m == 2)) {
                    FUN_0020b9d0(o);
                }
            }
        }
        DAT_0056c128 = 0;
    }
}

void FUN_0020c9e0(int arg0) {
    *(int *)0x56C130 = arg0;
}

typedef struct N_20c9f0 {
    long long f0;
    long long f8;
    char p16[8];
    struct N_20c9f0 *f24;
    struct N_20c9f0 *f28;
    int f32;
    int f36;
    char p40[8];
    int f48;
    int f52;
    int f56;
    char p60[4];
    unsigned short f64;
    char p66[4];
    signed char m : 7;
    unsigned char hi : 1;
    char p71;
    char f72;
} N_20c9f0;
void FUN_0020c9f0(N_20c9f0 *arg0) {
    N_20c9f0 *s0;
    N_20c9f0 *a1;
    N_20c9f0 *p;

    arg0->f72 = 0;
    arg0->f36 = 0;
    arg0->f32 = 0;
    p = DAT_0056c0e0[0];
    s0 = arg0;
    if (p == arg0) {
        while (p != 0) p = 0;
        DAT_0056c0e0[0] = p;
    }
    if (arg0->f48 == 0 && arg0->f52 == 0) {
        p2WaitDmaSequence(1, arg0->f8);
    }
    DIntr();
    arg0->m = 0;
    EIntr();
    a1 = arg0->f28;
    if (a1 != 0 && a1->m == 0) {
        a1->f64 += arg0->f64;
        s0 = arg0->f28;
        s0->f24 = arg0->f24;
        if (arg0->f24 != 0) {
            arg0->f24->f28 = s0;
        }
        if (DAT_0056c0d8 != 0 && DAT_0056c0d8 == arg0) {
            DAT_0056c0d8 = ((N_20c9f0 *)DAT_0056c0d8)->f24;
        }
        FUN_002082b0((O *)arg0);
    }
    a1 = s0->f24;
    if (a1 != 0 && a1->m == 0) {
        a1->f64 += s0->f64;
        s0->f24->f56 = s0->f56;
        s0->f24->f28 = s0->f28;
        if (s0->f28 != 0) {
            s0->f28->f24 = s0->f24;
        }
        if (s0 == DAT_0056c0d0) {
            DAT_0056c0d0 = s0->f24;
        }
        if (DAT_0056c0d8 != 0 && DAT_0056c0d8 == s0) {
            DAT_0056c0d8 = ((N_20c9f0 *)DAT_0056c0d8)->f24;
        }
        FUN_002082b0((O *)s0);
        s0 = 0;
    }
    if (s0 == arg0) {
        if (arg0->f56 > -1) {
            arg0->m = 0;
            return;
        }
        FUN_002082b0((O *)arg0);
    }
}
#pragma pop
