#pragma push
#pragma readonly_strings on
#include <stdio.h>
#include "dw4/sony/libkernl.h"
#include "dw4/p2/p2core.h"
#include "dw4/p2/p2pool.h"
#include "dw4/p2/p2texture.h"
#include "dw4/p2/p2multipass.h"
#include "dw4/p2/dmaChannel.h"
#include "dw4/p2/p2gs.h"
#include "dw4/p2/p2swap.h"
#include "dw4/p2/p2textureCalls.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

P2Texture *p2AllocTextureRecord(void);
void p2SetProgramTextureFunction(int function);
void p2SetTextureAlpha(char alpha0, unsigned char alpha1, int expandAlpha);
int p2AllocTextureMemory(P2Texture *texture);
/* Selects the mipmap levels (the textures after the first of a binding) for the draws. */
void FUN_00208830(P2Texture **levels, int palettedStages);

/* The VRAM block list, in address order, and where the next search for space starts. */
extern P2Texture *p2TextureBlocks;
extern P2Texture *p2TextureSearchStart;
/* The texture bound to each stage this frame, and the stages p2MarkTextureStage has marked. */
extern P2Texture *p2TextureStages[17];
extern unsigned int p2TextureStageMask;

/* Each program's combine mode and palette flag, four bits per program. */
extern long long p2TextureCombineBits[4];
extern const char text_textureLoadedPredicate[];
extern const char text_textureDeferredPredicate[];
/* The VRAM block range textures are placed in. */
extern int p2TextureMemoryEnd[4];
extern int p2TextureMemoryBase[4];
/* The GS pixel storage mode of each texture format. */
extern int p2TextureFormatPsm[4];
/* The register lists p2UploadGsRegisters sends for a screen copy, a texture copy, a render target
 * (context 1 then context 2) and its restore. */
extern int p2ScreenCopyRegisters[4];
extern int p2RestoreTargetRegisters[4];
extern int p2RestoreTargetContext2Registers[4];
/* FRAME, ZBUF and XYOFFSET of the display, saved by the first p2SetRenderTarget. */
extern int p2SavedFrame[4];
extern int p2SavedZbuf[4];
extern long long p2SavedScanmsk[4];
/* 1: a texture that has to wait for VRAM waits for the GS to finish drawing, else for the DMA. */
extern int p2TextureWaitMode[4];

void p2SetTextureCombineMode(int mode) {
    int idx;
    long long bitsCleared;
    int bits;
    long long bitsWide;

    idx = p2CurrentProgram * 4;
    *(int *)((char *)p2TextureCombineMode + idx) = mode;
    bitsCleared = p2TextureCombineBits[0] & ~((long long)0xF << idx);
    p2TextureCombineBits[0] = bitsCleared;
    bits = ((mode * 2) | ((*(unsigned int *)((char *)p2ProgramFlags + idx) >> 0xA) & 1)) & 0xF;
    p2DirtyFlags |= 0x111;
    bitsWide = bits;
    p2TextureCombineBits[0] = bitsCleared | (bitsWide << idx);
}

int p2GetTextureHeight(P2Texture *texture)
{
    return texture->height;
}

P2Texture *p2AllocTextureRecord(void) {
    P2Texture *texture;
    if (p2FreeTextures == 0) {
        p2GrowPool(0xA, &p2FreeTextures);
    }
    texture = (P2Texture *)p2FreeTextures;
    p2FreeTextures = (struct p2TextureRecord *)texture->next;
    texture->state = P2_TEXTURE_FREE;
    texture->drawSequence = 0;
    texture->uploadSequence = 0;
    texture->detached = 0;
    texture->palette = 0;
    texture->chain = 0;
    texture->clut = 0;
    texture->used = 0;
    texture->chainCount = 0;
    return texture;
}

static void p2FreeTextureRecord(P2Texture *texture) {
    texture->state = P2_TEXTURE_FREE;
    texture->drawSequence = 0;
    texture->uploadSequence = 0;
    texture->next = (P2Texture *)p2FreeTextures;
    texture->prev = 0;
    p2FreeTextures = (struct p2TextureRecord *)texture;
}

void p2InitTextures(void) {
    unsigned int i;
    unsigned int j;
    P2Texture *head;

    i = 0;
    p2FreeTextures = 0;
    p2TextureMemoryEnd[0] = 0x4000;
    do {
        p2TextureStages[i] = 0;
        i += 1;
    } while (i < 0x11U);
    p2TextureStageMask = 0;
    p2GrowPool(0xA, &p2FreeTextures);
    head = p2AllocTextureRecord();
    p2TextureBlocks = head;
    head->next = 0;
    p2TextureBlocks->prev = 0;
    p2GetTextureBase(&head->address);
    head->blocks = p2TextureMemoryEnd[0] - head->address;
    p2TextureSearchStart = p2TextureBlocks;
    p2TextureMemoryBase[0] = head->address;
    if (p2FirstOpen != 0) {
        p2RegisterPredicateName(textureLoadedPredicate, text_textureLoadedPredicate);
        p2RegisterPredicateName(textureDeferredPredicate, text_textureDeferredPredicate);
    }
    j = 0;
    do {
        p2TextureFunction[j] = 0;
        j += 1;
    } while (j < 0x10U);
    p2SetTextureAlpha(0, 0x80, 0);
}

void p2TextureUploadDone(void *arg) {
    P2Texture *texture = arg;
    if (texture->state == P2_TEXTURE_FENCED && p2DmaSequenceLastCompleted(1, texture->drawSequence) != 0) {
        texture->state = P2_TEXTURE_DRAWN;
    }
}

void p2TextureLoadDone(void *arg)
{
    P2Texture *texture = arg;
    const P2Texture *view = texture;

    if (view->state == P2_TEXTURE_LOADING)
        texture->state = P2_TEXTURE_RESIDENT;
}

void p2SetTexture(P2Texture *texture) {
    if (texture == 0) return;
    if (texture->clut != 0) {
        p2SetClut(texture->clut);
        return;
    }
    p2StatTextureBinds++;
    *(signed char *)&p2CurrentGsRegisters->texa = texture->texAlpha;
    if (texture->source != P2_TEXTURE_SOURCE_IMAGE) {
        if (texture->source == P2_TEXTURE_SOURCE_FRONT) {
            texture->address = p2Display.drawBuffer ? 0 : p2Display.secondBufferPage;
        }
        if (texture->source == P2_TEXTURE_SOURCE_BACK) {
            texture->address = p2Display.drawBuffer ? p2Display.secondBufferPage : 0;
        }
        if (texture->source == P2_TEXTURE_SOURCE_DEPTH) {
            texture->address = p2Display.secondBufferPage * 2;
        }
        texture->address = texture->address << 5;
    }
    if (p2CurrentProgram == 0) {
        p2CurrentGsRegisters->tex0[0].field.tbp0 = texture->address;
        p2CurrentGsRegisters->tex0[0].field.tbw = texture->tex0.field.tbw;
        p2CurrentGsRegisters->tex0[0].field.psm = texture->tex0.field.psm;
        p2CurrentGsRegisters->tex0[0].field.tw = texture->tex0.field.tw;
        p2CurrentGsRegisters->tex0[0].field.th = texture->tex0.field.th;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x48000040LL;
    } else {
        p2CurrentGsRegisters->tex0[1].field.tbp0 = texture->address;
        p2CurrentGsRegisters->tex0[1].field.tbw = texture->tex0.field.tbw;
        p2CurrentGsRegisters->tex0[1].field.psm = texture->tex0.field.psm;
        p2CurrentGsRegisters->tex0[1].field.tw = texture->tex0.field.tw;
        p2CurrentGsRegisters->tex0[1].field.th = texture->tex0.field.th;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x48000080LL;
        if (p2CurrentProgram == 1 && texture->source == P2_TEXTURE_SOURCE_IMAGE) p2UploadTex0Context2();
    }
}

void p2SetProgramTextureFunction(int function) {
    int shift;

    shift = *(int *)0x569330 * 2;
    *(int *)0x56B028 = (int) (*(int *)0x56B028 & ~(3 << shift));
    *(int *)0x56B028 = (int) (*(int *)0x56B028 | ((function & 3) << shift));
}

/* TEX0.TFX of both contexts, reached a byte at a time. */
typedef struct p2TextureFunctionBytes {
    char registersBelow[52];
    unsigned char tex0Bits32 : 3; unsigned char tfx : 2; unsigned char tex0Bits37 : 3;
    char tex0Context2[7];
    unsigned char tex0Context2Bits32 : 3; unsigned char tfxContext2 : 2; unsigned char tex0Context2Bits37 : 3;
} p2TextureFunctionBytes;
void p2SetTextureFunction(int function) {
    int dirty;
    long long dirtyRegisters;

    p2SetProgramTextureFunction(function);
    if (p2CurrentProgram == 0) {
        p2TextureFunction[p2CurrentProgram] = function;
        ((p2TextureFunctionBytes *)p2CurrentGsRegisters)->tfx = function;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x40;
    } else {
        p2TextureFunction[p2CurrentProgram] = function;
        ((p2TextureFunctionBytes *)p2CurrentGsRegisters)->tfxContext2 = function;
        dirty = p2DirtyFlags | 0x40;
        dirtyRegisters = p2GsDirtyRegisters | 0x80;
        p2DirtyFlags = dirty;
        p2GsDirtyRegisters = dirtyRegisters;
        if (p2CurrentProgram == 1) {
            p2UploadTex0Context2();
        }
    }
    p2DirtyFlags |= 0x11;
}

/* TEX0.TCC and TEX0.TFX of both contexts, reached a byte at a time. */
typedef struct p2TextureFunctionAlphaBytes {
    char registersBelow[52];
    unsigned char tex0Bits32 : 2; unsigned char tcc : 1; unsigned char tfx : 2; unsigned char tex0Bits37 : 3;
    char tex0Context2[7];
    unsigned char tex0Context2Bits32 : 2; unsigned char tccContext2 : 1; unsigned char tfxContext2 : 2;
    unsigned char tex0Context2Bits37 : 3;
} p2TextureFunctionAlphaBytes;
void p2SetTextureFunctionAndAlpha(int function, int alpha) {
    p2SetProgramTextureFunction(function);
    if (p2CurrentProgram == 0) {
        *(int *)((char *)p2TextureFunction + p2CurrentProgram * 4) = function;
        ((p2TextureFunctionAlphaBytes *)p2CurrentGsRegisters)->tfx = function;
        ((p2TextureFunctionAlphaBytes *)p2CurrentGsRegisters)->tcc = alpha;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x40;
    } else {
        *(int *)((char *)p2TextureFunction + p2CurrentProgram * 4) = function;
        ((p2TextureFunctionAlphaBytes *)p2CurrentGsRegisters)->tfxContext2 = function;
        ((p2TextureFunctionAlphaBytes *)p2CurrentGsRegisters)->tccContext2 = alpha;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x80;
        if (p2CurrentProgram == 1) {
            p2UploadTex0Context2();
        }
    }
    p2DirtyFlags |= 0x11;
}

/* CLAMP: the wrap modes and the clamp window. */
typedef struct p2GsClampBits {
    unsigned char wms : 2; unsigned char wmt : 2; unsigned short minu : 10; unsigned long long maxu : 10;
    unsigned long long minv : 10; unsigned short maxv : 10;
} p2GsClampBits;
/* TEX0.TCC and CLAMP of both contexts. */
typedef struct p2TextureClampBytes {
    char registersBelow[52];
    unsigned char tex0Bits32 : 2; unsigned char tcc : 1; unsigned char tex0Bits35 : 5;
    char tex0Context2[7];
    unsigned char tex0Context2Bits32 : 2; unsigned char tccContext2 : 1; unsigned char tex0Context2Bits35 : 5;
    char tex0Context2High[3];
    p2GsClampBits clamp1;
    p2GsClampBits clamp2;
} p2TextureClampBytes;
void p2SetTextureClamp(int wms, int wmt, int minu, long long maxu, long long minv, int maxv, int alpha) {
    int dirty;
    p2GsClampBits *clamp;
    long long dirtyRegisters;
    if (p2CurrentProgram == 0) {
        ((p2TextureClampBytes *)p2CurrentGsRegisters)->tcc = alpha;
        ((p2TextureClampBytes *)p2CurrentGsRegisters)->clamp1.wms = wms;
        ((p2TextureClampBytes *)p2CurrentGsRegisters)->clamp1.wmt = wmt;
        ((p2TextureClampBytes *)p2CurrentGsRegisters)->clamp1.minu = minu;
        clamp = &((p2TextureClampBytes *)p2CurrentGsRegisters)->clamp1;
        clamp->maxu = (int)maxu;
        clamp->minv = (int)minv;
        clamp->maxv = maxv;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x140;
    } else {
        ((p2TextureClampBytes *)p2CurrentGsRegisters)->tccContext2 = alpha;
        ((p2TextureClampBytes *)p2CurrentGsRegisters)->clamp2.wms = wms;
        ((p2TextureClampBytes *)p2CurrentGsRegisters)->clamp2.wmt = wmt;
        ((p2TextureClampBytes *)p2CurrentGsRegisters)->clamp2.minu = minu;
        clamp = &((p2TextureClampBytes *)p2CurrentGsRegisters)->clamp2;
        clamp->maxu = (int)maxu;
        clamp->minv = (int)minv;
        clamp->maxv = maxv;
        dirty = p2DirtyFlags | 0x40;
        dirtyRegisters = p2GsDirtyRegisters | 0x280;
        p2DirtyFlags = dirty;
        p2GsDirtyRegisters = dirtyRegisters;
        if (p2CurrentProgram == 1) {
            p2UploadTex0Context2();
        }
    }
}

/* The low half of TEX1: LCM, MXL, MMAG, MMIN. */
typedef struct p2GsTex1Filter {
    unsigned short lcm : 2;
    unsigned short mxl : 3;
    unsigned short mmag : 1;
    unsigned short mmin : 3;
    unsigned short tex1Bits9 : 7;
} p2GsTex1Filter;
typedef struct p2TextureFilterBytes {
    char registersBelow[104];
    p2GsTex1Filter tex1;
    char tex1High[6];
    p2GsTex1Filter tex1Context2;
} p2TextureFilterBytes;
void p2SetTextureFilter(int magnify, int minify) {
    if (p2CurrentProgram == 0) {
        ((p2TextureFilterBytes *)p2CurrentGsRegisters)->tex1.mmag = magnify;
        ((p2TextureFilterBytes *)p2CurrentGsRegisters)->tex1.mmin = minify;
        if (((p2TextureFilterBytes *)p2CurrentGsRegisters)->tex1.mmin == 1 || ((p2TextureFilterBytes *)p2CurrentGsRegisters)->tex1.mmin == 0) {
            ((p2TextureFilterBytes *)p2CurrentGsRegisters)->tex1.mxl = 0;
        }
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x2000;
    } else {
        ((p2TextureFilterBytes *)p2CurrentGsRegisters)->tex1Context2.mmag = magnify;
        ((p2TextureFilterBytes *)p2CurrentGsRegisters)->tex1Context2.mmin = minify;
        if (((p2TextureFilterBytes *)p2CurrentGsRegisters)->tex1Context2.mmin == 1 || ((p2TextureFilterBytes *)p2CurrentGsRegisters)->tex1Context2.mmin == 0) {
            ((p2TextureFilterBytes *)p2CurrentGsRegisters)->tex1Context2.mxl = 0;
        }
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x4000;
    }
}

/* TEX1's LCM, L and K of both contexts, reached a byte or a halfword at a time. */
typedef struct p2TextureLodBytes {
    char registersBelow[104];
    unsigned char lcm : 1; unsigned char tex1Bits1 : 7;
    char tex1Byte1;
    unsigned char tex1Bits16 : 3; unsigned char l : 2; unsigned char tex1Bits21 : 3;
    char tex1Byte3;
    unsigned short k : 12; unsigned short tex1Bits44 : 4;
    char tex1High[2];
    unsigned char lcmContext2 : 1; unsigned char tex1Context2Bits1 : 7;
    char tex1Context2Byte1;
    unsigned char tex1Context2Bits16 : 3; unsigned char lContext2 : 2; unsigned char tex1Context2Bits21 : 3;
    char tex1Context2Byte3;
    unsigned short kContext2 : 12; unsigned short tex1Context2Bits44 : 4;
} p2TextureLodBytes;
void p2SetTextureLod(int lcm, int l, int k) {
    if (p2CurrentProgram == 0) {
        ((p2TextureLodBytes *)p2CurrentGsRegisters)->lcm = lcm;
        ((p2TextureLodBytes *)p2CurrentGsRegisters)->l = l;
        ((p2TextureLodBytes *)p2CurrentGsRegisters)->k = k;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x2000;
    } else {
        ((p2TextureLodBytes *)p2CurrentGsRegisters)->lcmContext2 = lcm;
        ((p2TextureLodBytes *)p2CurrentGsRegisters)->lContext2 = l;
        ((p2TextureLodBytes *)p2CurrentGsRegisters)->kContext2 = k;
        p2DirtyFlags |= 0x40;
        p2GsDirtyRegisters |= 0x4000;
    }
}

/* TEXA: TA0, AEM and TA1. */
struct p2TexaBytes {
    char registersBelow[216];
    char ta0;
    unsigned char texaBit8 : 1;
    unsigned char texaBit9 : 1;
    unsigned char texaBit10 : 1;
    unsigned char texaBit11 : 1;
    unsigned char texaBit12 : 1;
    unsigned char texaBit13 : 1;
    unsigned char texaBit14 : 1;
    unsigned char aem : 1;
    char texaBytes2[2];
    char ta1;
};
void p2SetTextureAlpha(char alpha0, unsigned char alpha1, int expandAlpha) {
    ((struct p2TexaBytes *)p2CurrentGsRegisters)->ta0 = alpha0;
    ((struct p2TexaBytes *)p2CurrentGsRegisters)->ta1 = alpha1;
    ((struct p2TexaBytes *)p2CurrentGsRegisters)->aem = expandAlpha;
    p2DirtyFlags |= 0x40;
    p2GsDirtyRegisters |= 0x08000000;
}

/* The FRAME and ZBUF pages and the local-to-local transfer registers (BITBLTBUF, TRXPOS, TRXREG,
 * TRXDIR) of the register set, at the widths the transfers write them. */
struct p2TransferRegisters {
    char registersBelow[355]; unsigned char framePsm:6; char frameContext2[12];
    unsigned short zbp:9; char zbufHigh[14];
    unsigned short sbp:14; unsigned char sbw:6; unsigned char spsm:6;
    unsigned short dbp:14; unsigned char dbw:6; unsigned char dpsm:6;
    unsigned short ssax:11; unsigned short ssay:11; unsigned short dsax:11; unsigned short dsay:11; unsigned char dir:2;
    unsigned short rrw:12; char trxregHigh[2];
    unsigned short rrh:12; char trxdirLow[2]; unsigned char xdir:2;
};
/* A quadword as words or doublewords. */
typedef union p2Quadword { int w[4]; long long d[2]; } p2Quadword;
/* The GIF tag of an IMAGE transfer: NLOOP is the quadword count. */
typedef union p2ImageGifTag { struct { unsigned short nloop : 15; unsigned short eop : 1; } bits; long long d[2]; } p2ImageGifTag;
/* A DMA ref tag over the image data. */
typedef union p2ImageRefTag { struct { unsigned short qwc; short id; unsigned int addr : 31; unsigned int spr : 1; } bits; int w[4]; } p2ImageRefTag;
void p2UploadTextures(P2Texture **list, int count) {
    int p2DmaPacketQueued();
    extern unsigned int p2TextureFormatBits[];
    extern unsigned int p2TextureFormatHalfBytes[];
    extern int p2UploadRegisters[];
    extern p2Quadword p2UploadDmaTag;
    extern p2ImageRefTag p2UploadImageRef;
    extern p2ImageGifTag p2UploadGifTag;
    P2Texture *t;
    p2DmaPredicate *n;
    p2Quadword *q;
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
        seq = p2DmaCurrentPacket[P2_DMA_GIF]->waitSequence;
        if (seq >= 0 && p2DmaLastPacket[P2_DMA_GIF]->waitSequence >= seq && p2DmaLastPacket[P2_DMA_GIF]->cursor < p2DmaLastPacket[P2_DMA_GIF]->limit) {
            n = p2DmaCurrentPacket[P2_DMA_GIF]->predicates;
            p2DmaLastPacket[P2_DMA_GIF]->ready = 0;
            p2DmaCurrentPacket[P2_DMA_GIF]->waitSequence = -1;
            if (n != 0) {
                p2DmaCurrentPacket[P2_DMA_GIF]->predicates = 0;
                p2DmaCurrentPacket[P2_DMA_GIF]->lastPredicate = 0;
                n->next = p2DmaLastPacket[P2_DMA_GIF]->predicates;
                if (p2DmaLastPacket[P2_DMA_GIF]->predicates == 0) {
                    p2DmaLastPacket[P2_DMA_GIF]->lastPredicate = n;
                }
                p2DmaLastPacket[P2_DMA_GIF]->predicates = n;
            }
            p2DmaFreePackets[P2_DMA_GIF]++;
            p2DmaCurrentPacket[P2_DMA_GIF] = p2DmaLastPacket[P2_DMA_GIF];
            p2StatGifDmaCount--;
        }
    }
    EIntr();
    do {
        ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dpsm = p2TextureFormatPsm[(*list)->format];
        ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dbw = ((*list)->width + 63) / 64;
        ((struct p2TransferRegisters *)p2CurrentGsRegisters)->rrw = (*list)->width;
        ((struct p2TransferRegisters *)p2CurrentGsRegisters)->xdir = 0;
        t = *list;
        fmt = t->format;
        w = t->width;
        addr = (int)t->image;
        rows = t->height;
        max = 0xfffe0 / (w * p2TextureFormatBits[fmt]);
        y = 0;
        while (rows > 0) {
            h = rows < max ? rows : max;
            /* matching construct: permuter — qwc computed before the transfer-register stores */
            qwc = (p2TextureFormatBits[fmt] * (w * h) + 31) >> 5;
            ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dbp = t->address;
            ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dsax = 0;
            ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dsay = y;
            ((struct p2TransferRegisters *)p2CurrentGsRegisters)->rrh = h;
            p2UploadGsRegistersGif(4, p2UploadRegisters, 0);
            /* matching construct: statement-order search — y += h placed before the GIF tag NLOOP store */
            y += h;
            p2UploadGifTag.bits.nloop = qwc;
            rows -= h;
            p2UploadImageRef.bits.qwc = p2UploadGifTag.bits.nloop;
            q = (p2Quadword *)p2DmaCurrentPacket[P2_DMA_GIF]->cursor;
            p2UploadImageRef.bits.addr = addr;
            q->w[0] = p2UploadDmaTag.w[0];
            q->w[1] = p2UploadDmaTag.w[1];
            q->w[2] = p2UploadDmaTag.w[2];
            q->w[3] = p2UploadDmaTag.w[3];
            q++;
            q->d[0] = p2UploadGifTag.d[0];
            q->d[1] = p2UploadGifTag.d[1];
            q++;
            q->w[0] = p2UploadImageRef.w[0];
            q->w[1] = p2UploadImageRef.w[1];
            q->w[2] = p2UploadImageRef.w[2];
            q->w[3] = p2UploadImageRef.w[3];
            q++;
            p2DmaCurrentPacket[P2_DMA_GIF]->cursor = (unsigned int)q;
            t = *list;
            fmt = t->format;
            w = t->width;
            addr += (p2TextureFormatHalfBytes[fmt] * (w * h)) >> 1;
        }
        t->uploadSequence = p2DmaCurrentPacket[P2_DMA_GIF]->sequence;
        p2AddDmaCompletion(2, p2TextureLoadDone, *list);
        count--;
        list++;
        if (count != 0 && p2DmaCurrentPacket[P2_DMA_GIF]->cursor > p2DmaCurrentPacket[P2_DMA_GIF]->limit) {
            p2SubmitDmaPacket(2);
        }
    } while (count != 0);
    p2SubmitDmaPacket(2);
}

int p2Log2(int value) {
    int n;
    for (n = 0; (value >>= 1) != 0; n++) {}
    return n;
}

void p2CopyFramebufferToTexture(P2Texture *texture, int sourceX, int sourceY, int destinationX, int destinationY,
                                int width, int height, int fromDepth) {
    int framePsm;
    int antialiased;
    short bufferWidth;
    short bufferHeight;
    framePsm = ((struct p2TransferRegisters *)p2CurrentGsRegisters)->framePsm;
    antialiased = (p2GetDisplayFlags() & 2) != 0;
    texture->used = 1;
    switch (texture->state) {
    case P2_TEXTURE_UNPLACED:
        if (p2AllocTextureMemory(texture) == 0) return;
        texture->state = P2_TEXTURE_RESIDENT;
        break;
    case P2_TEXTURE_FENCED:
    case P2_TEXTURE_RESIDENT:
    case P2_TEXTURE_DRAWN:
        texture->state = P2_TEXTURE_RESIDENT;
        break;
    }
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dpsm = p2TextureFormatPsm[texture->format];
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dbp = texture->address;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dbw = (texture->width + 63) / 64;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->spsm = framePsm;
    if (fromDepth != 0) {
        ((struct p2TransferRegisters *)p2CurrentGsRegisters)->sbp = ((struct p2TransferRegisters *)p2CurrentGsRegisters)->zbp << 5;
    } else {
        ((struct p2TransferRegisters *)p2CurrentGsRegisters)->sbp = (p2Display.drawBuffer != 0 && !antialiased) ? (p2Display.width * p2Display.height) / 64 : 0;
    }
    if (antialiased != 0) bufferWidth = p2Display.antialiasWidth; else bufferWidth = p2Display.width;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->sbw = bufferWidth / 64;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dsax = destinationX;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dsay = destinationY;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->ssax = sourceX;
    if (antialiased != 0) bufferHeight = p2Display.antialiasHeight; else bufferHeight = p2Display.height;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->ssay = bufferHeight - (height + sourceY);
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dir = 0;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->rrw = width;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->rrh = height;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->xdir = 2;
    p2UploadGsRegisters(4, &p2ScreenCopyRegisters[0]);
}

/* matching construct: hand-tried — the records arrive as void * and are copied to typed locals, which keeps retail's register assignment */
void p2CopyTexture(void *source, int sourceX, int sourceY, void *destination, int destinationX,
                   int destinationY, int width, int height) {
    extern int p2TextureCopyRegisters[4];
    int xdir;
    int ydir;
    P2Texture *dst;
    P2Texture *src;
    xdir = sourceX < destinationX;
    ydir = sourceY < destinationY;
    dst = destination;
    src = source;
    dst->used = 1;
    switch (dst->state) {
    case P2_TEXTURE_UNPLACED:
        if (p2AllocTextureMemory(dst) == 0) return;
        dst->state = P2_TEXTURE_RESIDENT;
        break;
    case P2_TEXTURE_FENCED:
    case P2_TEXTURE_RESIDENT:
    case P2_TEXTURE_DRAWN:
        dst->state = P2_TEXTURE_RESIDENT;
        break;
    }
    src->used = 1;
    switch (src->state) {
    case P2_TEXTURE_UNPLACED:
        if (p2AllocTextureMemory(src) == 0) return;
        src->state = P2_TEXTURE_RESIDENT;
        break;
    case P2_TEXTURE_FENCED:
    case P2_TEXTURE_RESIDENT:
    case P2_TEXTURE_DRAWN:
        src->state = P2_TEXTURE_RESIDENT;
        break;
    }
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->spsm = p2TextureFormatPsm[src->format];
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->sbp = src->address;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->sbw = (src->width + 63) / 64;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dpsm = p2TextureFormatPsm[dst->format];
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dbp = dst->address;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dbw = (dst->width + 63) / 64;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dsax = destinationX;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dsay = destinationY;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->ssax = sourceX;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->ssay = sourceY;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->dir = (xdir << 1) + ydir;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->rrw = width;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->rrh = height;
    ((struct p2TransferRegisters *)p2CurrentGsRegisters)->xdir = 2;
    p2UploadGsRegisters(4, &p2TextureCopyRegisters[0]);
}

/* XYOFFSET, FRAME and ZBUF of the register set, with their context-2 copies. */
typedef struct p2RenderTargetRegisters {
    char registersBelow[136];
    union { struct { short ofx; short pad; short ofy; short high; } offset; long long word; } xyoffset;
    long long xyoffsetContext2;
    char registersBetween[24];
    union { long long word; struct { unsigned char msk : 2; } bits; } scanmsk;
    char registersBelowFrame[168];
    union { long long word; int low; struct { unsigned short fbp : 9; unsigned short frameBits9 : 7; unsigned char fbw : 6; unsigned char frameBits22 : 2; unsigned char psm : 6; } bits; } frame;
    long long frameContext2;
    union { long long word; int low; struct { unsigned short zbp : 9; unsigned short zbufBits9 : 7; char zbufByte2; unsigned char psm : 4; } bits; } zbuf;
    long long zbufContext2;
} p2RenderTargetRegisters;
/* The texture's PSM, a halfword at a time. */
typedef struct p2TextureTex0Halfword {
    char recordBelow[18];
    unsigned short tex0Bits16 : 4;
    unsigned short psm : 6;
    unsigned short tex0Bits26 : 6;
} p2TextureTex0Halfword;
int p2SetRenderTarget(P2Texture *colour, P2Texture *depth) {
    extern int p2RenderTargetRegisterList[4];
    extern int p2RenderTargetContext2RegisterList[4];
    int multipass;
    p2RenderTargetRegisters *registers;

    multipass = ((unsigned int) p2ProgramFlags[p2CurrentProgram] >> 0x17) & 1;
    colour->used = 1;
    switch (colour->state) {
    case P2_TEXTURE_UNPLACED:
        if (p2AllocTextureMemory(colour) == 0) return 0;
        colour->state = P2_TEXTURE_RESIDENT;
        if (depth != 0) {
            depth->used = 1;
            if (p2AllocTextureMemory(depth) == 0) return 0;
            depth->state = P2_TEXTURE_RESIDENT;
        }
        break;
    case P2_TEXTURE_FENCED:
    case P2_TEXTURE_RESIDENT:
    case P2_TEXTURE_DRAWN:
        colour->state = P2_TEXTURE_RESIDENT;
        break;
    default:
        return 0;
    }
    ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->xyoffset.offset.ofx = (0x800 - (colour->width >> 1)) * 0x10;
    ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->xyoffset.offset.ofy = (0x800 - (colour->height >> 1)) * 0x10;
    if (p2Display.renderTarget == -1) {
        p2Display.renderTarget = (int)colour;
        p2SavedFrame[0] = ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->frame.low;
        p2SavedZbuf[0] = ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->zbuf.low;
        p2SavedScanmsk[0] = ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->scanmsk.word;
    }
    if (depth != 0) {
        p2DepthTarget = (int)depth;
        ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->zbuf.bits.zbp = ((depth->address << 9) / 8) / 2048;
        if (depth->format == 12 && colour->format == 3) {
            depth->format = 11;
            colour->format = 2;
            ((p2TextureTex0Halfword *)colour)->psm = p2TextureFormatPsm[2];
        }
        ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->zbuf.bits.psm = p2TextureFormatPsm[depth->format] & 0xF;
    } else {
        p2DepthTarget = -1;
    }
    ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->frame.bits.fbp = ((colour->address << 9) / 8) / 2048;
    ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->frame.bits.fbw = (unsigned int)colour->width >> 6;
    ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->frame.bits.psm = p2TextureFormatPsm[colour->format];
    ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->scanmsk.bits.msk = 0;
    if (multipass != 0) {
        registers = (p2RenderTargetRegisters *)p2CurrentGsRegisters;
        registers->frameContext2 = registers->frame.word;
        registers->xyoffsetContext2 = registers->xyoffset.word;
        registers->zbufContext2 = registers->zbuf.word;
        p2UploadGsRegisters(3, &p2RenderTargetContext2RegisterList[0]);
    }
    p2UploadGsRegisters(4, &p2RenderTargetRegisterList[0]);
    return 1;
}

void p2RestoreRenderTarget(void) {
    short size;
    int antialiased;
    int multipass;
    p2RenderTargetRegisters *registers;

    multipass = ((unsigned int) p2ProgramFlags[p2CurrentProgram] >> 0x17) & 1;
    antialiased = (p2GetDisplayFlags() & 2) != 0;
    if (p2Display.renderTarget != -1) {
        ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->frame.low = p2SavedFrame[0];
        ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->zbuf.low = p2SavedZbuf[0];
        registers = (p2RenderTargetRegisters *)p2CurrentGsRegisters;
        registers->scanmsk.word = p2SavedScanmsk[0];
        if (antialiased != 0) size = p2Display.antialiasWidth; else size = p2Display.width;
        registers->xyoffset.offset.ofx = (0x800 - (size >> 1)) * 0x10;
        if (antialiased != 0) size = p2Display.antialiasHeight; else size = p2Display.height;
        ((p2RenderTargetRegisters *)p2CurrentGsRegisters)->xyoffset.offset.ofy = (0x800 - (size >> 1)) * 0x10;
        if (multipass != 0) {
            registers = (p2RenderTargetRegisters *)p2CurrentGsRegisters;
            registers->frameContext2 = registers->frame.word;
            registers->xyoffsetContext2 = registers->xyoffset.word;
            registers->zbufContext2 = registers->zbuf.word;
            p2UploadGsRegisters(3, &p2RestoreTargetContext2Registers[0]);
        }
        p2UploadGsRegisters(4, &p2RestoreTargetRegisters[0]);
        p2Display.renderTarget = -1;
        p2DepthTarget = -1;
    }
}

long long p2GetTextureUploadSequence(P2Texture *texture) {
    return texture->uploadSequence;
}

void p2PlaceTextureBlock(P2Texture *texture, P2Texture *block, int address) {
    long long blockState;
    unsigned short blocks;
    int end;
    P2Texture *below;
    int covered;
    P2Texture *split;
    int span;
    P2Texture *above;
    long long state;
    int blockEnd;
    blockState = block->state;
    while (address != block->address) {
        blocks = block->blocks;
        below = block->prev;
        covered = address >= block->address + blocks;
        if (below != 0 && below->state == P2_TEXTURE_FREE) {
            if (covered != 0) {
                below->blocks += blocks;
            } else {
                below->blocks += ((address - block->address) & 0xFFFF);
            }
        } else {
            split = p2AllocTextureRecord();
            split->address = block->address;
            split->next = block;
            split->prev = block->prev;
            block->prev = split;
            if (below != 0) {
                below->next = split;
            } else {
                p2TextureBlocks = split;
            }
            if (covered != 0) {
                split->blocks = block->blocks;
            } else {
                { int length = address - block->address; split->blocks = length; }
            }
        }
        if (covered != 0) {
            P2Texture *prev = block->prev;
            P2Texture *next = block->next;
            if (prev != 0) {
                prev->next = next;
            }
            if (next != 0) {
                next->prev = block->prev;
            }
            block->next = 0;
            block->prev = 0;
            state = block->state;
            block->state = P2_TEXTURE_UNPLACED;
            block->address = -1;
            if (blockState == 0) {
                p2FreeTextureRecord(block);
            } else {
                block->detached = 1;
            }
            block = next;
            blockState = next->state;
        } else {
            block->blocks -= ((address - block->address) & 0xFFFF);
            block->address = address;
        }
    }
    span = block->blocks;
    goto reload;
    while (((above != 0) ^ 1) == 0 && (address + texture->blocks) > (block->address + span)) {
        unsigned short aboveBlocks;
        state = above->state;
        aboveBlocks = above->blocks;
        block->next = above->next;
        span += aboveBlocks;
        if (above->next != 0) {
            above->next->prev = block;
        }
        above->next = 0;
        above->prev = 0;
        above->state = P2_TEXTURE_UNPLACED;
        above->address = -1;
        if (state == 0) {
            p2FreeTextureRecord(above);
        } else {
            above->detached = 1;
        }
    reload:
        above = block->next;
    }
    blockEnd = block->address + span;
    end = address + texture->blocks;
    if (end < blockEnd) {
        if (above != 0 && above->state == P2_TEXTURE_FREE) {
            above->blocks += ((blockEnd - end) & 0xFFFF);
            above->address = address + texture->blocks;
        } else {
            split = p2AllocTextureRecord();
            split->address = address + texture->blocks;
            { int length = span - texture->blocks; split->blocks = length; }
            split->next = above;
            split->prev = block;
            block->next = split;
            if (above != 0) {
                above->prev = split;
            }
        }
    }
    texture->address = address;
    texture->next = block->next;
    texture->prev = block->prev;
    if (block->prev != 0) {
        block->prev->next = texture;
    }
    if (block->next != 0) {
        block->next->prev = texture;
    }
    if (p2TextureBlocks == block) {
        p2TextureBlocks = texture;
    }
    state = block->state;
    block->next = 0;
    block->prev = 0;
    block->state = P2_TEXTURE_UNPLACED;
    block->address = -1;
    if (state == 0) {
        p2FreeTextureRecord(block);
        return;
    }
    block->detached = 1;
}

/* A block list record as the search for space reads it: its state may change under the DMA
 * completion handlers. */
typedef struct P2TextureBlockState {
    long long uploadSequence;
    long long drawSequence;
    char tex0[8];
    struct P2TextureBlockState *next;
    char links[28];
    int address;
    char size[4];
    unsigned short blocks;
    char format[4];
    volatile char state : 7;
    char detached : 1;
    char chainCount;
    char used;
} P2TextureBlockState;

P2TextureBlockState *p2FindTextureSpace(P2Texture *texture, int *address, int fenced, long long *drawSequence) {
    P2TextureBlockState *stop;
    P2TextureBlockState *block;
    int pass;
    long long latest;
    P2TextureBlockState *next;
    int end;
    int spanEnd;
    int alignMask;
    int start;

    stop = 0;
    block = (P2TextureBlockState *)p2TextureSearchStart;
    latest = 0;
    pass = 0;
    while (pass < 2) {
        while (block != stop) {
            if (block->used == 0 && (block->state == P2_TEXTURE_DRAWN || block->state == P2_TEXTURE_FREE || (fenced == 0 && block->state == P2_TEXTURE_FENCED))) {
                start = block->address;
                spanEnd = start + block->blocks;
                alignMask = texture->alignMask;
                end = (start + alignMask) & ~alignMask;
                next = block->next;
                latest = block->drawSequence;
                while (((next != 0) ^ 1) == 0 && next->used == 0 && (next->state == P2_TEXTURE_DRAWN || next->state == P2_TEXTURE_FREE || (fenced == 0 && next->state == P2_TEXTURE_FENCED)) && spanEnd < end + texture->blocks) {
                    if (latest < next->drawSequence) {
                        latest = next->drawSequence;
                    }
                    spanEnd += next->blocks;
                    next = next->next;
                }
                if (spanEnd >= end + texture->blocks) {
                    *address = end;
                    break;
                }
            }
            block = block->next;
        }
        if (*address != -1) {
            break;
        }
        pass++;
        block = (P2TextureBlockState *)p2TextureBlocks;
        stop = (P2TextureBlockState *)p2TextureSearchStart;
    }
    if (drawSequence != 0) {
        *drawSequence = latest;
    }
    return block;
}

int p2AllocTextureMemory(P2Texture *texture) {
    int address;
    long long drawn;
    int block;
    p2DmaPacket *packet;
    long long *wait;
    address = -1;
    block = (int)p2FindTextureSpace(texture, &address, 1, 0);
    if (address >= 0) {
        p2PlaceTextureBlock(texture, (P2Texture *)block, address);
    } else {
        block = (int)p2FindTextureSpace(texture, &address, 0, &drawn);
        if (address >= 0) {
            if (p2TextureWaitMode[0] == 1) {
                p2AddFinishFunc(p2RecordFinishedSequence, 0);
                drawn = p2DmaCurrentPacket[P2_DMA_VIF1]->sequence;
                p2SubmitDmaPacket(1);
                p2PlaceTextureBlock(texture, (P2Texture *)block, address);
                p2AddDmaPredicate(2, p2SequenceFinishedPredicate, drawn);
            } else {
                packet = p2DmaCurrentPacket[P2_DMA_VIF1];
                if (packet->sequence == drawn || packet->chain == packet->cursor) {
                    packet->restartProgram = 1;
                }
                p2SubmitDmaPacket(1);
                p2PlaceTextureBlock(texture, (P2Texture *)block, address);
                p2AddDmaPredicate(2, textureDeferredPredicate, drawn);
            }
            wait = &p2DmaCurrentPacket[P2_DMA_GIF]->waitSequence;
            if (*wait < drawn) {
                *wait = drawn;
            }
        }
    }
    if (address >= 0) {
        texture->state = P2_TEXTURE_LOADING;
        texture->uploadSequence = 0;
        texture->drawSequence = 0;
        p2TextureSearchStart = texture->next;
        if (p2TextureSearchStart == 0) {
            p2TextureSearchStart = p2TextureBlocks;
        }
    }
    return (unsigned char)((~address == 0) ^ 1);
}

static inline int p2TextureState(const P2Texture *texture) {
    return texture->state;
}

/* The state of a texture that may be absent: an absent one counts as free. */
static inline int p2TextureStateOrFree(const P2Texture *texture) {
    return texture != 0 ? texture->state : P2_TEXTURE_FREE;
}

static inline void p2FenceTextureRecord(P2Texture *texture) {
    texture->state = P2_TEXTURE_FENCED;
    texture->drawSequence = p2DmaCurrentPacket[P2_DMA_VIF1]->sequence;
    p2AddDmaCompletion(1, &p2TextureUploadDone, texture);
}

void p2FenceTexture(P2Texture *texture) {
    P2Texture *level;
    P2Texture *palette;
    int records;
    int completions;
    records = (texture->palette != 0) + 1;
    level = texture->chain;
    completions = texture->chainCount + records;
    if (texture->used == 0) {
        p2ReserveDmaCompletions(completions);
        DIntr();
        p2FenceTextureRecord(texture);
        palette = texture->palette;
        if (palette != 0) {
            palette->state = P2_TEXTURE_FENCED;
            texture->palette->drawSequence = p2DmaCurrentPacket[P2_DMA_VIF1]->sequence;
            p2AddDmaCompletion(1, &p2TextureUploadDone, texture->palette);
        }
        while (level != 0) {
            if (p2TextureState(level) != P2_TEXTURE_UNPLACED) {
                p2FenceTextureRecord(level);
            }
            level = level->chain;
        }
        EIntr();
    }
}

/* Reads a stage mask through a pointer that cannot change it. */
static inline int p2ReadStages(const int *stages) {
    return *stages;
}

/* A program without a palette clears its bit of p2PalettedStages. */
static inline void p2ClearPalettedStage(int program) {
    if (program == 0) {
        p2PalettedStages &= ~1;
    } else if (program == 1) {
        p2PalettedStages &= ~2;
    }
}

/* Binds the texture of every level in `list` (pointers to the texture, then its palette, then the
 * rest of its chain) to program `program`: fences what the program had bound, uploads the levels
 * that are not in VRAM, selects the texture and makes the draws wait for the uploads. Returns 0
 * when a level found no VRAM. */
int FUN_0020bb20(void *list, int program, int deferred) {
    P2Texture **textures = (P2Texture **)list;
    int stage;
    int uploadCount;
    int count;
    int sequence;
    P2Texture *bound;
    int state;
    int i;
    int result;
    P2Texture *texture;
    P2Texture *palette;
    int set;
    P2Texture *level;
    int j;
    int previous;
    unsigned int stages;
    P2Texture *uploads[8];
    P2Texture **slot;

    result = 1;
    slot = &p2TextureStages[program];
    bound = *slot;
    uploadCount = 0;
    state = p2TextureStateOrFree(bound);
    count = textures[0]->chainCount + ((textures[0]->palette != 0) + 1);
    if (bound != 0 && bound != textures[0] &&
        (state == P2_TEXTURE_STALE || state == P2_TEXTURE_RESIDENT || state == P2_TEXTURE_LOADING)) {
        {
            if (count == 1 && textures[0]->clut != 0) {
                palette = bound->palette;
                state = p2TextureStateOrFree(palette);
                if (palette != 0 && palette != textures[0] &&
                    (state == P2_TEXTURE_RESIDENT || state == P2_TEXTURE_LOADING)) {
                    p2FenceTexture(palette);
                }
            } else {
                p2FenceTexture(bound);
                p2TextureStageMask &= ~(1 << program);
                stages = p2TextureStageMask;
                stage = 0;
                while (stages != 0) {
                    stages >>= 1;
                    stage++;
                    if (stages & 1) {
                        texture = p2TextureStages[stage];
                        if (texture != 0) {
                            state = p2TextureStateOrFree(texture);
                            if (state == P2_TEXTURE_RESIDENT || state == P2_TEXTURE_LOADING) {
                                p2FenceTexture(texture);
                            }
                        }
                    }
                }
            }
        }
    }
    if (count > 1 || deferred != 0) {
        for (i = 0; i < count; i++) {
            if (textures[i] != 0) {
                textures[i]->used = 1;
            } else {
                count = i;
                if (i == 1) {
                    textures[0]->used = 0;
                }
            }
        }
    }
    for (i = 0; i < count; i++) {
        P2TextureFlags *flags = &textures[i]->flags;

        switch (p2TextureState(textures[i])) {
        case P2_TEXTURE_STALE:
            uploads[uploadCount++] = textures[i];
            if (textures[i]->image != 0) {
                textures[i]->state = P2_TEXTURE_LOADING;
                if (bound == textures[i]) {
                    textures[i]->drawSequence = p2DmaCurrentPacket[P2_DMA_VIF1]->sequence;
                    p2AddDmaCompletion(1, &p2TextureUploadDone, textures[i]);
                    p2SubmitDmaPacket(P2_DMA_VIF1);
                    p2AddDmaPredicate(2, &textureDeferredPredicate, textures[i]->drawSequence);
                }
            }
            break;
        case P2_TEXTURE_UNPLACED:
            if (p2AllocTextureMemory(textures[i]) == 0) {
                if (uploadCount != 0) {
                    result = 0;
                    break;
                }
                if (count > 1) {
                    for (j = 0; j < count; j++) {
                        textures[j]->used = 0;
                    }
                }
                return 0;
            }
            if (textures[i]->image != 0) {
                uploads[uploadCount++] = textures[i];
            } else {
                textures[i]->used = 1;
            }
            break;
        case P2_TEXTURE_FENCED:
        case P2_TEXTURE_DRAWN:
        case P2_TEXTURE_RESIDENT:
            flags->state = P2_TEXTURE_RESIDENT;
            break;
        case P2_TEXTURE_FREE:
        case P2_TEXTURE_LOADING:
            break;
        }
    }
    if (textures[0]->clut != 0) {
        if (*slot != 0) {
            (*slot)->palette = textures[0];
        }
    } else {
        *slot = textures[0];
    }
    if (uploadCount != 0) {
        p2UploadTextures(uploads, uploadCount);
    }
    if (count > 1 && deferred == 0) {
        for (j = 0; j < count; j++) {
            textures[j]->used = 0;
        }
    }
    p2TextureStageMask &= ~(1 << program);
    set = program > 1 ? program - 1 : 0;
    p2CurrentProgram = program;
    p2CurrentGsRegisters = &p2GsRegisterSets[set];
    p2SetTexture(textures[0]);
    if (count > 1) {
        palette = textures[0]->palette;
        previous = p2ReadStages(&p2PalettedStages);
        if (palette != 0) {
            p2SetClut((struct p2Clut *)palette->clut);
            if (program == 0) {
                p2PalettedStages |= 1;
            } else if (program == 1 && p2TextureStages[0]->palette != p2TextureStages[1]->palette) {
                p2PalettedStages |= 2;
            }
        } else {
            p2ClearPalettedStage(program);
        }
        if ((previous & 2) != (p2PalettedStages & 2) ||
            ((previous & 1) != (p2PalettedStages & 1) && (p2PalettedStages & 2))) {
            p2DirtyFlags |= 0x11;
        }
        if (textures[0]->chainCount != 0) {
            FUN_00208830(textures + 1, p2PalettedStages);
        }
    } else if (textures[0]->clut == 0) {
        p2ClearPalettedStage(program);
    }
    p2ReserveDmaPredicates(count);
    DIntr();
    sequence = -1;
    if (textureLoadedPredicate(textures[0]->uploadSequence) == 0) {
        p2AddDmaPredicate(1, &textureLoadedPredicate, textures[0]->uploadSequence);
        sequence = textures[0]->uploadSequence;
    }
    if (count > 1) {
        palette = textures[0]->palette;
        level = textures[0]->chain;
        if (palette != 0 && sequence < palette->uploadSequence && textureLoadedPredicate(palette->uploadSequence) == 0) {
            p2AddDmaPredicate(1, &textureLoadedPredicate, palette->uploadSequence);
            sequence = textures[0]->uploadSequence;
        }
        while (level != 0) {
            if (sequence < level->uploadSequence && textureLoadedPredicate(level->uploadSequence) == 0) {
                p2AddDmaPredicate(1, &textureLoadedPredicate, level->uploadSequence);
                sequence = textures[0]->uploadSequence;
            }
            level = level->chain;
            if (level != 0 && level->state == P2_TEXTURE_UNPLACED) {
                level = 0;
            }
        }
    }
    EIntr();
    p2CurrentProgram = 0;
    p2CurrentGsRegisters = &p2GsRegisterSets[0];
    return result;
}

P2Texture *p2LoadTexture(void *image, int width, int height, int format, int deferred) {
    extern int p2TextureLoadFailures[4];
    extern unsigned int p2TextureFormatBits[];
    P2Texture *t;
    int w;
    int h;

    t = p2AllocTextureRecord();
    if (t == 0) {
        p2TextureLoadFailures[0]++;
        return 0;
    }
    t->source = deferred;
    t->detached = 0;
    t->address = -1;
    t->image = image;
    t->width = width;
    t->height = height;
    t->format = format;
    t->next = 0;
    t->texAlpha = (format == 1) ? 0x80 : 0;
    t->tex0.field.tbw = (t->width + 63) / 64;
    t->tex0.field.psm = p2TextureFormatPsm[t->format];
    if (deferred == 0) {
        t->tex0.field.tw = p2Log2(t->width);
        t->tex0.field.th = p2Log2(t->height);
        t->state = P2_TEXTURE_UNPLACED;
    } else {
        h = w = 1;
        while (w < width) w <<= 1;
        while (h < height) h <<= 1;
        t->tex0.field.tw = p2Log2(w);
        t->tex0.field.th = p2Log2(h);
        t->state = P2_TEXTURE_RESIDENT;
        t->uploadSequence = 0;
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
        t->blocks = (p2TextureFormatBits[format] * (w * h)) >> 9;
        t->blocks = (t->blocks == 0) ? 1 : t->blocks;
        t->alignMask = t->blocks - 1;
        if (t->alignMask >= 32 || image == 0) t->alignMask = 31;
    }
    return t;
}

void p2ChainTexture(P2Texture *texture, P2Texture *level) {
    P2Texture *last = texture;
    while (last->chain != 0) last = last->chain;
    last->chain = level;
    level->chain = 0;
    texture->chainCount = texture->chainCount + 1;
}

void p2SetTexturePalette(P2Texture *texture, P2Texture *palette)
{
    texture->palette = palette;
}

void p2InvalidateTexture(P2Texture *texture) {
    if (p2TextureState(texture) != P2_TEXTURE_UNPLACED) {
        texture->state = P2_TEXTURE_STALE;
    }
}

void p2SetTextureImage(P2Texture *texture, void *image) {
    if (p2TextureState(texture) != P2_TEXTURE_UNPLACED) {
        texture->state = P2_TEXTURE_STALE;
    }
    texture->image = image;
}

void p2MarkTextureStage(int stage) {
    if (stage > 0) {
        *(int *)0x56C128 = (int) (*(int *)0x56C128 | (1 << stage));
    }
}

/* A record's state as p2FenceUsedTexture reads it: the DMA completion handlers change it. */
typedef struct P2TextureVolatileState {
    char recordBelow[70];
    volatile signed char state : 7;
    unsigned char detached : 1;
    char chainCount;
    char used;
} P2TextureVolatileState;
/* The state byte of a staged record, read the same way. */
typedef struct P2TextureStageState { char recordBelow[70]; volatile signed char state : 7; unsigned char detached : 1; } P2TextureStageState;
void p2FenceUsedTexture(P2Texture *texture) {
    int stage;
    unsigned int stages;
    P2Texture *staged;
    P2TextureVolatileState *record = (P2TextureVolatileState *)texture;
    if (record->state == P2_TEXTURE_FENCED || record->state == P2_TEXTURE_DRAWN || record->state == P2_TEXTURE_UNPLACED) return;
    if (record->used != 0) {
        record->used = 0;
        p2FenceTexture((P2Texture *)record);
        p2TextureStageMask &= ~1;
        stages = p2TextureStageMask;
        stage = 0;
        while (stages != 0) {
            stages = stages >> 1;
            stage += 1;
            if (stages & 1) {
                staged = p2TextureStages[stage];
                if (staged != 0 && (((P2TextureStageState *)staged)->state == P2_TEXTURE_RESIDENT || ((P2TextureStageState *)staged)->state == P2_TEXTURE_LOADING)) {
                    p2FenceTexture(staged);
                }
            }
        }
        p2TextureStageMask = 0;
    }
}

void p2SetTextureWaitMode(int mode) {
    *(int *)0x56C130 = mode;
}

void p2FreeTexture(P2Texture *texture) {
    P2Texture *merged;
    P2Texture *neighbour;
    P2Texture *stage;

    texture->used = 0;
    texture->palette = 0;
    texture->chain = 0;
    stage = p2TextureStages[0];
    merged = texture;
    if (stage == texture) {
        while (stage != 0) stage = 0;
        p2TextureStages[0] = stage;
    }
    if (texture->image == 0 && texture->source == P2_TEXTURE_SOURCE_IMAGE) {
        p2WaitDmaSequence(1, texture->drawSequence);
    }
    DIntr();
    texture->state = P2_TEXTURE_FREE;
    EIntr();
    neighbour = texture->prev;
    if (neighbour != 0 && neighbour->state == P2_TEXTURE_FREE) {
        neighbour->blocks += texture->blocks;
        merged = texture->prev;
        merged->next = texture->next;
        if (texture->next != 0) {
            texture->next->prev = merged;
        }
        if (p2TextureSearchStart != 0 && p2TextureSearchStart == texture) {
            p2TextureSearchStart = p2TextureSearchStart->next;
        }
        p2FreeTextureRecord(texture);
    }
    neighbour = merged->next;
    if (neighbour != 0 && neighbour->state == P2_TEXTURE_FREE) {
        neighbour->blocks += merged->blocks;
        merged->next->address = merged->address;
        merged->next->prev = merged->prev;
        if (merged->prev != 0) {
            merged->prev->next = merged->next;
        }
        if (merged == p2TextureBlocks) {
            p2TextureBlocks = merged->next;
        }
        if (p2TextureSearchStart != 0 && p2TextureSearchStart == merged) {
            p2TextureSearchStart = p2TextureSearchStart->next;
        }
        p2FreeTextureRecord(merged);
        merged = 0;
    }
    if (merged == texture) {
        if (texture->address > -1) {
            texture->state = P2_TEXTURE_FREE;
            return;
        }
        p2FreeTextureRecord(texture);
    }
}
#pragma pop
