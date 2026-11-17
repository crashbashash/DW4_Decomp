#include <math.h>
#include "dw4/p2dma.h"
#include "dw4/p2core.h"
#include "dw4/dmaChannel.h"
#include "dw4/p2draw.h"
#include "dw4/p2gs.h"
#include "dw4/renderState.h"
#include "dw4/p2multipass.h"
#include "dw4/igMemory.h"
int *FUN_00202f60(int *arg0, long long arg1);
int FUN_00202fa0(long long arg0);
extern int FUN_001f8b50();
extern int FUN_001fffb0();
extern int FUN_00200980();
extern int FUN_00204ea0();
struct P { long long m0; long long m8; int p16; struct P *next; int sh; int count; int tab[1]; };
void *FUN_00203000();
extern int DAT_0056ae40[4];

/* One slot per bit of a VU program's feature mask. p2VariantsBitN lists the programs that have bit N, one
 * entry per combination of that feature's settings (-1: none); the slot's programs points at it and
 * index is the combination the current state selects. */
typedef struct p2VariantSlot { int index; int *programs; } p2VariantSlot;

/* The compiler emits uninitialised C data last definition first, so these follow retail's address order from the bottom. */
unsigned int p2VuBufferLayoutNop;
unsigned int p2FunctionTablePad;
int p2FunctionTableSizes[3];
int p2LightingFunctions[6];
int p2FunctionTables[72];
int p2SentFunctionTablesQwc;
__int128 p2SentFunctionTables[19];
__int128 p2SentLightingFunctions;
__int128 p2SentLightingFunctionsCode;
__int128 p2SentGifTags1;
__int128 p2SentGifTags0;
__int128 p2SentVuBufferLayout2;
__int128 p2SentVuBufferLayout1;
__int128 p2SentVuBufferLayout0;
__int128 p2SentPassSetup[18];
int p2StateCacheStatus;
int p2CachedProgramAddresses[2];
int p2LightCalcPending;
long long p2StatPassSetupsSent;
long long p2StatVuBufferLayoutsSent;
long long p2StatGsRegistersSent;
long long p2StatBlendMatricesSent;
long long p2StatVertexFormatsSent;
long long p2StatGifTagsSent;
long long p2StatLightsSent;
long long p2StatLightingFunctionsSent;
long long p2StatFunctionTablesSent;
long long p2StatStateSends;
p2VariantSlot p2VariantSlots[33];
int p2VuProgramSpriteBits;
int p2LightingProgramBits;
int p2VuProgramLightingBits;
long long p2VertexArrayMask;
struct P *p2VariantLists[6];
int p2VariantsBit30[8];
int p2VariantsBit31[3];
int p2VariantsBit21[4];
int p2VariantsBit16[8];
int p2VariantsBit10[8];
int p2VariantsBit29[11];
int p2VariantsBit28[2];
int p2VariantsBit27[8];
int p2VariantsBit26[2];
int p2VariantsBit25[16];
int p2VariantsBit23[8];
int p2VariantsBit22[16];
int p2VariantsBit19[14];
int p2VariantsBit24[3];
int p2VariantsBit20[1];
int p2VariantsBit17[2];
int p2VariantsBit18[1];
int p2VariantsBit15[16];
int p2VariantsBit14[22];
int p2VariantsBit8[20];
int p2VariantsBit13[2];
int p2VariantsBit7[11];
int p2VariantsBit2[8];
int p2VariantsBit12[4];
int p2VariantsBit11[2];
int p2VariantsBit9[1];
int p2VariantsBit6[1];
int p2VariantsBit5[16];
int p2VariantsBit4[1];
int p2VariantsBit3[1];
int p2VariantsBit1[4];
int p2VariantsBit0[1];

void FUN_001ff3b0(int arg0) {
    int s;
    int f;
    int n, a;
    s = p2DirtyFlags & arg0;
    if (s != 0) {
        p2StatStateSends += 1;
    }
    if (p2DisplayListMode == 0) {
        if (s & 4) {
            p2StatLightsSent += 1;
            FUN_001f8b50();
            s = p2DirtyFlags & arg0;
        }
        if (s & 0x193) {
            p2StateCacheStatus = FUN_00204ea0();
            s = p2DirtyFlags & arg0;
            if (p2StateCacheStatus == 0 || (p2StateCacheStatus == 1 && (s & 0x100))) {
                if (s & 0x10) {
                    FUN_001fffb0(p2StateCacheStatus);
                    s |= 0x80;
                    p2DirtyFlags |= 0x80;
                }
                if (s & 1) {
                    FUN_00200980();
                    s = p2DirtyFlags & arg0;
                }
                if (s & 2) {
                    if (p2DisplayListMode == 0) {
                        f = p2VuProgramLightingBits;
                        a = f & 0x10;
                        n = 0;
                        if (a && (f & 0x20)) {
                            n++;
                            p2LightingFunctions[0] = p2VariantsBit29[2];
                        } else if (f & 0x20) {
                            n++;
                            p2LightingFunctions[0] = p2VariantsBit29[1];
                        } else if (a) {
                            n++;
                            p2LightingFunctions[0] = p2VariantsBit29[0];
                        }
                        if (f & 0x40) {
                            p2LightingFunctions[n] = p2VariantsBit29[4];
                            n++;
                        }
                        if (f & 0x1C00) {
                            p2LightingFunctions[n] = p2VariantsBit29[4 + ((f & 0x1C00) >> 10)];
                            n++;
                        }
                        p2LightingFunctions[n] = p2VariantsBit30[2];
                        p2FunctionTableSizes[2] = n + 1;
                        if (p2FunctionTableSizes[2] > 1) {
                            p2LightCalcPending = 1;
                        } else {
                            p2LightCalcPending = 0;
                        }
                    }
                }
                if (s & 0x80) {
                    p2LayoutVuBuffers();
                }
            }
        }
        if (s & 1) p2StatFunctionTablesSent += 1;
        if (s & 2) p2StatLightingFunctionsSent += 1;
        if (s & 0x10) p2StatVertexFormatsSent += 1;
        if (s & 0x80) p2StatVuBufferLayoutsSent += 1;
        if (s & 8) p2StatGifTagsSent += 1;
        if (s & 0x100) p2StatPassSetupsSent += 1;
        if (s & 0x40) p2StatGsRegistersSent += 1;
        if (s & 0x20) p2StatBlendMatricesSent += 1;
    }
}

typedef union VifCode { unsigned int word; unsigned short imm; } VifCode;
typedef struct GifTag {
    unsigned long long NLOOP:15;
    unsigned long long EOP:1;
    unsigned long long pad16:16;
    unsigned long long id:14;
    unsigned long long PRE:1;
    unsigned long long PRIM:11;
    unsigned long long FLG:2;
    unsigned long long NREG:4;
    unsigned long long REGS;
} GifTag;
extern int DAT_00490d38;
extern int DAT_00569308;

static inline int remap(int prim) {
    if (prim == 9) {
        return 3;
    } else if (prim == 8) {
        return 4;
    } else if (prim == 7) {
        return 4;
    }
    return prim;
}

/* A DMA tag with its quadword count in the low half, written to the packet as four words. */
typedef union p2DmaTag { unsigned int word[4]; unsigned short qwc; } p2DmaTag;
/* An UNPACK VIF code; byte 2 is its element count. */
typedef union p2VifUnpack { unsigned int word; unsigned char num[4]; } p2VifUnpack;

/* p2StateCacheStatus: what the state cache lookup found for the current state, and whether its
 * packets have been sent since. */
enum {
    P2_STATE_CACHE_MISS,
    P2_STATE_CACHE_HIT,
    P2_STATE_SENT
};

/* The STMASK pattern that leaves the first word of each lighting-table vector written and the
 * other three unchanged. */
#define P2_LIGHTING_FUNCTIONS_MASK 0xFCFCFCFC

p2DmaTag p2FunctionTablesTag = {{ 0x10000001, 0, 0, 0 }};
p2VifUnpack p2LightingFunctionsUnpack = { 0x70004027 };
p2VifUnpack p2FunctionTable0Unpack = { 0x6100404E };
p2VifUnpack p2FunctionTable1Unpack = { 0x61004021 };
unsigned int p2FunctionTablesFlush = 0x10000000;
unsigned int p2LightingFunctionsStmask = 0x20000000;
void p2UpdateLights();
void p2UploadBlendMatrices();
void p2StoreStateCacheEntry();
void p2SendGifTags(void);
void p2SendPassSetup(void);
void p2SendVuBufferLayout(void);

/* Sends the render state `mask` selects and p2DirtyFlags marks: the VU program addresses of the
 * function tables, the GIF tags, the multipass setup and the VU buffer layout (all skipped when the
 * state cache already holds them), the lights, the blend matrices and the GS registers. Recording a
 * display list sends only the GS registers and keeps everything but them and the vertex format
 * marked. */
int p2SendRenderState(int mask) {
    int k;
    int qwc;
    int j;
    unsigned int *p;
    int dirty;
    int lightingCount;
    int i;
    int load;
    unsigned short *q;
    int vertexCount;
    unsigned int *word;
    __int128 *addresses;

    dirty = p2DirtyFlags & mask;
    load = dirty;
    vertexCount = p2FunctionTableSizes[0] + p2FunctionTableSizes[1];
    lightingCount = p2FunctionTableSizes[2];
    if (p2DisplayListMode == 0) {
        if (p2StateCacheStatus != P2_STATE_SENT) {
            if (dirty & (P2_DIRTY_FUNCTION_TABLES | P2_DIRTY_LIGHTING_FUNCTIONS | P2_DIRTY_VERTEX_FORMAT |
                         P2_DIRTY_VU_BUFFERS | P2_DIRTY_PASSES)) {
                if (dirty & P2_DIRTY_FUNCTION_TABLES) {
                    if (p2LoadVuPrograms(p2FunctionTables, p2LightingFunctions, vertexCount + 1, lightingCount + 1) == 0) {
                        load |= P2_DIRTY_FUNCTION_TABLES | P2_DIRTY_LIGHTING_FUNCTIONS;
                    }
                }
                if (dirty & P2_DIRTY_LIGHTING_FUNCTIONS) {
                    if (p2LoadVuPrograms(p2LightingFunctions, p2FunctionTables, lightingCount + 1, vertexCount + 1) == 0) {
                        load |= P2_DIRTY_FUNCTION_TABLES | P2_DIRTY_LIGHTING_FUNCTIONS;
                    }
                }
                p = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
                if (load & P2_DIRTY_FUNCTION_TABLES) {
                    /* tables 0 and 1 as halfwords, each padded to whole words, the packet to a quadword */
                    p2FunctionTable0Unpack.num[2] = p2FunctionTableSizes[0];
                    if (p2FunctionTableSizes[0] % 2 != 0) {
                        p2FunctionTable0Unpack.num[2]++;
                    }
                    q = (unsigned short *)(p + 4);
                    *(unsigned int *)q = p2FunctionTablesFlush;
                    word = &((unsigned int *)q)[1];
                    q += 4;
                    *word = p2FunctionTable0Unpack.word;
                    for (i = 0; i < p2FunctionTableSizes[0]; i++) {
                        *q++ = p2GetVuProgramAddress(p2FunctionTables[i]);
                    }
                    if (p2FunctionTableSizes[0] % 2 != 0) {
                        *q++ = 0;
                    }
                    if (p2FunctionTableSizes[1] != 0) {
                        p2FunctionTable1Unpack.num[2] = p2FunctionTableSizes[1];
                        if (p2FunctionTableSizes[1] % 2 != 0) {
                            p2FunctionTable1Unpack.num[2]++;
                        }
                        word = (unsigned int *)q;
                        q = (unsigned short *)(word + 1);
                        *word = p2FunctionTable1Unpack.word;
                        for (j = 0; j < p2FunctionTableSizes[1]; j++) {
                            *q++ = p2GetVuProgramAddress(p2FunctionTables[i++]);
                        }
                        if (p2FunctionTableSizes[1] % 2 != 0) {
                            *q++ = 0;
                        }
                    }
                    while ((int)q & 0xF) {
                        word = (unsigned int *)q;
                        q = (unsigned short *)(word + 1);
                        *word = p2FunctionTablePad;
                    }
                    qwc = ((unsigned int *)q - (p + 4)) >> 2;
                    p2FunctionTablesTag.qwc = qwc;
                    p[0] = p2FunctionTablesTag.word[0];
                    p[1] = p2FunctionTablesTag.word[1];
                    p[2] = p2FunctionTablesTag.word[2];
                    p[3] = p2FunctionTablesTag.word[3];
                    for (k = 0; k < qwc; k++) {
                        p2SentFunctionTables[k] = ((__int128 *)(p + 4))[k];
                    }
                    p = (unsigned int *)q;
                    p2SentFunctionTablesQwc = k;
                }
                if (load & P2_DIRTY_LIGHTING_FUNCTIONS) {
                    /* table 2 as the first word of four vectors, a missing entry padded */
                    p2FunctionTablesTag.qwc = 2;
                    p[0] = p2FunctionTablesTag.word[0];
                    p[1] = p2FunctionTablesTag.word[1];
                    p[2] = p2FunctionTablesTag.word[2];
                    p[3] = p2FunctionTablesTag.word[3];
                    p2LightingFunctionsUnpack.num[2] = p2FunctionTableSizes[2];
                    p[4] = p2FunctionTablesFlush;
                    p[5] = p2LightingFunctionsStmask;
                    p[6] = P2_LIGHTING_FUNCTIONS_MASK;
                    p[7] = p2LightingFunctionsUnpack.word;
                    p[8] = lightingCount-- > 0 ? p2GetVuProgramAddress(p2LightingFunctions[0]) : p2FunctionTablePad;
                    addresses = (__int128 *)(p + 8);
                    p[9] = lightingCount-- > 0 ? p2GetVuProgramAddress(p2LightingFunctions[1]) : p2FunctionTablePad;
                    p[10] = lightingCount-- > 0 ? p2GetVuProgramAddress(p2LightingFunctions[2]) : p2FunctionTablePad;
                    p[11] = lightingCount > 0 ? p2GetVuProgramAddress(p2LightingFunctions[3]) : p2FunctionTablePad;
                    p2SentLightingFunctionsCode = ((__int128 *)p)[1];
                    p += 12;
                    p2SentLightingFunctions = *addresses;
                }
                p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)p;
                if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
                    if (p2DisplayListMode != 0) {
                        p2GrowDisplayList();
                    } else {
                        p2SubmitDmaPacket(P2_DMA_VIF1);
                    }
                }
                if (dirty & P2_DIRTY_GIF_TAGS) {
                    p2SendGifTags();
                    dirty |= P2_DIRTY_PASSES;
                    p2DirtyFlags |= P2_DIRTY_PASSES;
                }
                if (dirty & P2_DIRTY_PASSES) {
                    p2SendPassSetup();
                }
                if (dirty & P2_DIRTY_VU_BUFFERS) {
                    p2SendVuBufferLayout();
                }
                p2StoreStateCacheEntry();
                p2StateCacheStatus = P2_STATE_SENT;
            }
        }
        if (dirty & P2_DIRTY_LIGHTS) {
            p2UpdateLights();
        }
        if (dirty & P2_DIRTY_BLEND_MATRICES) {
            p2UploadBlendMatrices();
        }
    } else {
        mask &= ~(P2_DIRTY_ALL & ~(P2_DIRTY_GS_REGISTERS | P2_DIRTY_VERTEX_FORMAT));
    }
    if (dirty & P2_DIRTY_GS_REGISTERS) {
        p2FlushGsRegisters();
    }
    p2DirtyFlags &= ~(mask & P2_DIRTY_ALL);
    return 0;
}

p2DmaTag p2GifTagsDmaTag = {{ 0x10000002, 0, 0, 0 }};
VifCode p2GifTagsUnpack = { 0x68010000 };
GifTag p2GifTagTexPrim = { 1, 1, 0, 0, 1, 0, 0, 3, 0xFFFFFFFFFFFFF412ULL };
GifTag p2GifTagPrimColour = { 1, 1, 0, 0, 1, 0, 0, 2, 0xFFFFFFFFFFFFFF41ULL };
GifTag p2GifTagPrimTextured = { 1, 1, 0, 0, 1, 0, 0, 3, 0xFFFFFFFFFFFFF412ULL };

void p2SendGifTags(void) {
    int texPrim;
    int prim;
    unsigned int *p;
    int flag;
    GifTag *tag;
    int bits;

    p = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
    prim = p2CurrentPrimitive;
    if (prim == 0) {
        texPrim = 0;
        prim = 0;
    } else if (prim == 1 || prim == 2) {
        texPrim = 1;
    } else if (prim == 6) {
        if (DAT_00569308 != 0) {
            prim = 3;
            texPrim = 5;
        } else {
            texPrim = 6;
            prim = 6;
        }
    } else if (DAT_00490d38 == 0) {
        texPrim = 0;
        prim = 0;
    } else if (DAT_00490d38 == 1) {
        texPrim = 2;
        prim = 2;
    } else {
        prim = remap(prim);
        texPrim = 5;
    }
    flag = (p2ProgramFlags[p2CurrentProgram] >> 23) & 1;
    p2GifTagsUnpack.imm = 24;
    if (p2VuProgramSpriteBits & 0x100) {
        tag = &p2GifTagPrimColour;
    } else {
        tag = &p2GifTagPrimTextured;
    }
    if (flag) {
        bits = p2CurrentGsRegisters->prmode.half[0] & 0x7F8;
        texPrim |= bits;
        prim |= bits;
    }
    p2GifTagTexPrim.PRIM = texPrim;
    tag->PRIM = prim;
    p[0] = p2GifTagsDmaTag.word[0];
    p[1] = p2GifTagsDmaTag.word[1];
    p[2] = p2GifTagsDmaTag.word[2];
    p[3] = p2GifTagsDmaTag.word[3];
    p[4] = p2GifTagsUnpack.word;
    p[5] = ((unsigned int *)tag)[0];
    p[6] = ((unsigned int *)tag)[1];
    p[7] = ((unsigned int *)tag)[2];
    p2GifTagsUnpack.imm++;
    p[8] = p2GifTagsUnpack.word;
    p[9] = ((unsigned int *)&p2GifTagTexPrim)[0];
    p[10] = ((unsigned int *)&p2GifTagTexPrim)[1];
    p[11] = ((unsigned int *)&p2GifTagTexPrim)[2];
    p2SentGifTags0 = ((__int128 *)p)[1];
    p2SentGifTags1 = ((__int128 *)p)[2];
    p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)(p + 12);
    if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(1);
        }
    }
}

int FUN_00200830(struct P *p, long long *out) {
    int res = 0;
    long long m;
    int i;
    int j;
    int w;
    int k;
    int f;
    int lo;
    int hi;
    p2VariantSlot *e;
    for (; p != 0; p = p->next) {
        m = p->m0;
        if (m == (m & p2VertexArrayMask)) {
            if (!(p->m8 & p2VertexArrayMask)) {
                for (i = 0; i < 32; i++) {
                    if (m & (1LL << i)) break;
                }
                j = 32;
                for (; j > 0; j--) {
                    if (m & (1LL << j)) break;
                }
                e = &p2VariantSlots[i];
                w = e->index | (p2VariantSlots[j].index << p->sh);
                k = p->tab[w];
                if (k != -1) {
                    e->index = w;
                    e->programs = p->tab;
                    *out &= ~p->m0 | (1LL << i);
                    f = *(int *)((char *)p2VuPrograms + (k << 6) + 40);
                    lo = f & 0x30;
                    if (lo != 0) {
                        p2VuProgramLightingBits = (p2VuProgramLightingBits & 0x1cc0) | lo;
                    }
                    hi = f & 0x300;
                    if (hi != 0) {
                        p2VuProgramSpriteBits = hi;
                    }
                    res = 1;
                }
            }
        }
    }
    return res;
}

/* Declared without a prototype: p2SendPassSetup passes the combine mode too, which it ignores. */
int p2GetPassProgramAddress();

/* STMASK patterns: write only the last three words of each vector, or only the second. */
#define P2_PASS_MASK 0x03030303
#define P2_PALETTE_FLAG_MASK 0xF3F3F3F3
/* The palette flag, the second byte of a V4-8 vector: set when both stages draw paletted textures. */
#define P2_PALETTE_FLAG_BOTH 0xFF00
#define P2_PALETTE_FLAG_OTHER 0x100
#define P2_STAGES_BOTH_PALETTED 3

p2DmaTag p2PassSetupTag = {{ 0x10000003, 0, 0, 0 }};
p2VifUnpack p2PassSetupUnpack = { 0x7C02004E };
unsigned int p2PassSetupFlush = 0x10000000;
unsigned int p2PassSetupStmask = 0x20000000;
unsigned int p2PaletteFlagUnpack = 0x7E010049;
extern int p2PalettedStages;

/* Sends the multipass setup when the current program draws in passes: for each pass a vector of
 * its FRAME and ZBUF masks and the address of its VU program, then the palette flag. */
void p2SendPassSetup(void) {
    int n;
    int pass;
    int mode;
    unsigned int *start;
    unsigned int *p;
    int i;
    unsigned int *word;
    unsigned int frameMask;
    unsigned int zbufMask;

    if ((p2ProgramFlags[p2CurrentProgram] >> P2_CAP_MULTIPASS) & 1) {
        mode = p2GetPassCombineMode();
        p = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
        start = p;
        p2PassSetupTag.qwc = p2ExtraPassCount + 3;
        p[0] = p2PassSetupTag.word[0];
        p[1] = p2PassSetupTag.word[1];
        p[2] = p2PassSetupTag.word[2];
        p[3] = p2PassSetupTag.word[3];
        p += 4;
        word = p; p = word + 1; *word = p2PassSetupFlush;
        *p++ = p2PassSetupStmask;
        *p++ = P2_PASS_MASK;
        word = p; p = word + 1;
        p2PassSetupUnpack.num[2] = p2ExtraPassCount + 1;
        *word = p2PassSetupUnpack.word;
        for (pass = 0; pass <= p2ExtraPassCount; pass++) {
            p2GetPassMasks(pass, &frameMask, &zbufMask);
            *p++ = 0;
            *p++ = frameMask;
            *p++ = zbufMask;
            *p++ = p2GetPassProgramAddress(pass + 1, mode);
        }
        if (p2PalettedStages == P2_STAGES_BOTH_PALETTED) {
            *p++ = p2PassSetupStmask;
            *p++ = P2_PALETTE_FLAG_MASK;
            *p++ = p2PaletteFlagUnpack;
            *p++ = P2_PALETTE_FLAG_BOTH;
        } else {
            *p++ = p2PassSetupStmask;
            *p++ = P2_PALETTE_FLAG_MASK;
            *p++ = p2PaletteFlagUnpack;
            *p++ = P2_PALETTE_FLAG_OTHER;
        }
        n = p2ExtraPassCount + 3;
        for (i = 0; i < n; i++) {
            p2SentPassSetup[i] = ((__int128 *)start)[i + 1];
        }
        p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)p;
        if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
            if (p2DisplayListMode != 0) {
                p2GrowDisplayList();
            } else {
                p2SubmitDmaPacket(P2_DMA_VIF1);
            }
        }
    }
}

unsigned int p2VuBufferLayoutTag[4] = { 0x10000003, 0, 0, 0 };
unsigned int p2VuBufferBytesUnpack = 0x6E02404A;
unsigned int p2VuBufferHalvesUnpack = 0x6D01004C;
unsigned int p2VuBufferLayoutFlush = 0x11000000;
VifCode p2VuBufferBase = { 0x03000000 };
VifCode p2VuBufferOffset = { 0x02000000 };
extern int p2VifOffset, p2VifBase;

/* Sends p2VuBuffers: its addresses as bytes and halfwords to the VU1 program's constants, and its
 * double buffer as the VIF BASE and OFFSET, which p2VifBase and p2VifOffset keep for the state cache. */
void p2SendVuBufferLayout(void) {
    unsigned int *p;
    __int128 *data;

    p = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
    p[0] = p2VuBufferLayoutTag[0];
    p[1] = p2VuBufferLayoutTag[1];
    p[2] = p2VuBufferLayoutTag[2];
    p[3] = p2VuBufferLayoutTag[3];
    data = (__int128 *)(p + 4);
    p[4] = p2VuBufferLayoutFlush;
    p[5] = p2VuBufferBytesUnpack;
    ((unsigned char *)p)[24] = p2VuBuffers.address0;
    ((unsigned char *)p)[25] = p2VuBuffers.address1;
    ((unsigned char *)p)[26] = p2VuBuffers.address2;
    ((unsigned char *)p)[27] = p2VuBuffers.address3;
    ((unsigned char *)p)[28] = p2VuBuffers.address4;
    ((unsigned char *)p)[29] = p2VuBuffers.byteUnpackAddress;
    ((unsigned char *)p)[30] = p2VuBuffers.address7;
    ((unsigned char *)p)[31] = p2VuBuffers.address8;
    *(p += 8) = p2VuBufferHalvesUnpack;
    ((short *)p)[2] = p2VuBuffers.address6;
    ((short *)p)[3] = p2VuBuffers.base;
    ((short *)p)[4] = p2VuBuffers.offset + p2VuBuffers.base;
    ((short *)p)[5] = -1;
    p2VuBufferBase.imm = p2VuBuffers.base;
    p2VifBase = p2VuBuffers.base;
    p2VuBufferOffset.imm = p2VuBuffers.offset;
    p2VifOffset = p2VuBuffers.offset;
    p[3] = p2VuBufferLayoutNop;
    p[4] = p2VuBufferLayoutNop;
    p[5] = p2VuBufferLayoutNop;
    p[6] = p2VuBufferBase.word;
    p[7] = p2VuBufferOffset.word;
    p2SentVuBufferLayout0 = data[0];
    p2SentVuBufferLayout1 = data[1];
    p2SentVuBufferLayout2 = data[2];
    p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)(p + 8);
    if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(P2_DMA_VIF1);
        }
    }
}

int p2VariantsFirstSetup = 1;

void FUN_00202300(void) {
    int *temp_v0;
    int *temp_v0_10;
    int *temp_v0_11;
    int *temp_v0_12;
    int *temp_v0_13;
    int *temp_v0_14;
    int *temp_v0_15;
    int *temp_v0_16;
    int *temp_v0_17;
    int *temp_v0_18;
    int *temp_v0_19;
    int *temp_v0_20;
    int *temp_v0_21;
    int *temp_v0_22;
    int *temp_v0_23;
    int *temp_v0_24;
    int *temp_v0_25;
    int *temp_v0_2;
    int *temp_v0_3;
    int *temp_v0_4;
    int *temp_v0_5;
    int *temp_v0_6;
    int *temp_v0_7;
    int *temp_v0_8;
    int *temp_v0_9;
    int temp_v0_26;
    int var_a0;
    int var_a1;
    int var_a1_10;
    int var_a1_11;
    int var_a1_12;
    int var_a1_13;
    int var_a1_14;
    int var_a1_15;
    int var_a1_16;
    int var_a1_17;
    int var_a1_18;
    int var_a1_19;
    int var_a1_20;
    int var_a1_21;
    int var_a1_22;
    int var_a1_23;
    int var_a1_24;
    int var_a1_2;
    int var_a1_3;
    int var_a1_4;
    int var_a1_5;
    int var_a1_6;
    int var_a1_7;
    int var_a1_8;
    int var_a1_9;
    int var_s3;
    long long temp_s5;
    char *temp_s4;
    void *var_s2;
    void **temp_s1;
    int var_s0;
    void *var_v0;

    var_a1 = 0;
    p2VariantsBit3[0] = -1;
    p2VariantsBit4[0] = -1;
    p2VariantsBit6[0] = -1;
    p2VariantsBit9[0] = -1;
    do {
        temp_v0 = (int *)(&(p2VariantsBit11)[var_a1]);
        *temp_v0 = -1;
        var_a1 += 1;
    } while (var_a1 < 2);
    var_a1_2 = 0;
    do {
        temp_v0_2 = (int *)(&(p2VariantsBit12)[var_a1_2]);
        *temp_v0_2 = -1;
        var_a1_2 += 1;
    } while (var_a1_2 < 4);
    var_a1_3 = 0;
    p2VariantsBit0[0] = -1;
    do {
        temp_v0_3 = (int *)(&(p2VariantsBit1)[var_a1_3]);
        *temp_v0_3 = -1;
        var_a1_3 += 1;
    } while (var_a1_3 < 4);
    var_a1_4 = 0;
    do {
        temp_v0_4 = (int *)(&(p2VariantsBit2)[var_a1_4]);
        *temp_v0_4 = -1;
        var_a1_4 += 1;
    } while (var_a1_4 < 8);
    var_a1_5 = 0;
    do {
        temp_v0_5 = (int *)(&(p2VariantsBit13)[var_a1_5]);
        *temp_v0_5 = -1;
        var_a1_5 += 1;
    } while (var_a1_5 < 2);
    var_a1_6 = 0;
    do {
        temp_v0_6 = (int *)(&(p2VariantsBit7)[var_a1_6]);
        *temp_v0_6 = -1;
        var_a1_6 += 1;
    } while (var_a1_6 < 0xB);
    var_a1_7 = 0;
    do {
        temp_v0_7 = (int *)(&(p2VariantsBit14)[var_a1_7]);
        *temp_v0_7 = -1;
        var_a1_7 += 1;
    } while (var_a1_7 < 0x16);
    var_a1_8 = 0;
    do {
        temp_v0_8 = (int *)(&(p2VariantsBit8)[var_a1_8]);
        *temp_v0_8 = -1;
        var_a1_8 += 1;
    } while (var_a1_8 < 0x14);
    var_a1_9 = 0;
    do {
        temp_v0_9 = (int *)(&(p2VariantsBit15)[var_a1_9]);
        *temp_v0_9 = -1;
        var_a1_9 += 1;
    } while (var_a1_9 < 0x10);
    var_a1_10 = 0;
    p2VariantsBit18[0] = -1;
    do {
        temp_v0_10 = (int *)(&(p2VariantsBit17)[var_a1_10]);
        *temp_v0_10 = -1;
        var_a1_10 += 1;
    } while (var_a1_10 < 2);
    var_a1_11 = 0;
    p2VariantsBit20[0] = -1;
    do {
        temp_v0_11 = (int *)(&(p2VariantsBit24)[var_a1_11]);
        *temp_v0_11 = -1;
        var_a1_11 += 1;
    } while (var_a1_11 < 3);
    var_a1_12 = 0;
    do {
        temp_v0_12 = (int *)(&(p2VariantsBit19)[var_a1_12]);
        *temp_v0_12 = -1;
        var_a1_12 += 1;
    } while (var_a1_12 < 0xE);
    var_a1_13 = 0;
    do {
        temp_v0_13 = (int *)(&(p2VariantsBit22)[var_a1_13]);
        *temp_v0_13 = -1;
        var_a1_13 += 1;
    } while (var_a1_13 < 0x10);
    var_a1_14 = 0;
    do {
        temp_v0_14 = (int *)(&(p2VariantsBit23)[var_a1_14]);
        *temp_v0_14 = -1;
        var_a1_14 += 1;
    } while (var_a1_14 < 8);
    var_a1_15 = 0;
    do {
        temp_v0_15 = (int *)(&(p2VariantsBit25)[var_a1_15]);
        *temp_v0_15 = -1;
        var_a1_15 += 1;
    } while (var_a1_15 < 0x10);
    var_a1_16 = 0;
    do {
        temp_v0_16 = (int *)(&(p2VariantsBit26)[var_a1_16]);
        *temp_v0_16 = -1;
        var_a1_16 += 1;
    } while (var_a1_16 < 2);
    var_a1_17 = 0;
    do {
        temp_v0_17 = (int *)(&(p2VariantsBit28)[var_a1_17]);
        *temp_v0_17 = -1;
        var_a1_17 += 1;
    } while (var_a1_17 < 2);
    var_a1_18 = 0;
    do {
        temp_v0_18 = (int *)(&(p2VariantsBit27)[var_a1_18]);
        *temp_v0_18 = -1;
        var_a1_18 += 1;
    } while (var_a1_18 < 8);
    var_a1_19 = 0;
    do {
        temp_v0_19 = (int *)(&(p2VariantsBit29)[var_a1_19]);
        *temp_v0_19 = -1;
        var_a1_19 += 1;
    } while (var_a1_19 < 0xB);
    var_a1_20 = 0;
    do {
        temp_v0_20 = (int *)(&(p2VariantsBit30)[var_a1_20]);
        *temp_v0_20 = -1;
        var_a1_20 += 1;
    } while (var_a1_20 < 8);
    var_a1_21 = 0;
    do {
        temp_v0_21 = (int *)(&(p2VariantsBit10)[var_a1_21]);
        *temp_v0_21 = -1;
        var_a1_21 += 1;
    } while (var_a1_21 < 8);
    var_a1_22 = 0;
    do {
        temp_v0_22 = (int *)(&(p2VariantsBit16)[var_a1_22]);
        *temp_v0_22 = -1;
        var_a1_22 += 1;
    } while (var_a1_22 < 8);
    var_a1_23 = 0;
    do {
        temp_v0_23 = (int *)(&(p2VariantsBit21)[var_a1_23]);
        *temp_v0_23 = -1;
        var_a1_23 += 1;
    } while (var_a1_23 < 4);
    var_a1_24 = 0;
    do {
        temp_v0_24 = (int *)(&(p2VariantsBit31)[var_a1_24]);
        *temp_v0_24 = -1;
        var_a1_24 += 1;
    } while (var_a1_24 < 3);
    p2VariantSlots[7].index = 0;
    p2VariantSlots[7].programs = p2VariantsBit7;
    p2VariantSlots[13].programs = p2VariantsBit13;
    p2VariantSlots[14].programs = p2VariantsBit14;
    p2VariantSlots[8].programs = p2VariantsBit8;
    p2VariantSlots[15].programs = p2VariantsBit15;
    p2VariantSlots[0].programs = p2VariantsBit0;
    p2VariantSlots[1].programs = p2VariantsBit1;
    p2VariantSlots[2].programs = p2VariantsBit2;
    p2VariantSlots[3].programs = p2VariantsBit3;
    p2VariantSlots[4].programs = p2VariantsBit4;
    p2VariantSlots[6].programs = p2VariantsBit6;
    p2VariantSlots[9].programs = p2VariantsBit9;
    p2VariantSlots[12].programs = p2VariantsBit12;
    p2VariantSlots[17].programs = p2VariantsBit17;
    p2VariantSlots[20].programs = p2VariantsBit20;
    p2VariantSlots[24].programs = p2VariantsBit24;
    p2VariantSlots[22].programs = p2VariantsBit22;
    p2VariantSlots[23].programs = p2VariantsBit23;
    p2VariantSlots[28].programs = p2VariantsBit28;
    p2VariantSlots[27].programs = p2VariantsBit27;
    p2VariantSlots[30].index = 4;
    p2VariantSlots[30].programs = p2VariantsBit30;
    p2VariantSlots[5].programs = p2VariantsBit5;
    p2VariantSlots[0].index = 0;
    p2VariantSlots[1].index = 0;
    p2VariantSlots[2].index = 0;
    p2VariantSlots[3].index = 0;
    p2VariantSlots[4].index = 0;
    p2VariantSlots[6].index = 0;
    p2VariantSlots[9].index = 0;
    p2VariantSlots[12].index = 0;
    p2VariantSlots[17].index = 0;
    p2VariantSlots[20].index = 0;
    p2VariantSlots[24].index = 0;
    p2VariantSlots[22].index = 0;
    p2VariantSlots[23].index = 0;
    p2VariantSlots[28].index = 0;
    p2VariantSlots[27].index = 0;
    p2VariantSlots[5].index = 0;
    p2FindVuProgramVariants(1, p2VariantsBit0, 1);
    p2FindVuProgramVariants(2, p2VariantsBit1, 4);
    p2FindVuProgramVariants(4, p2VariantsBit2, 8);
    p2FindVuProgramVariants(8, p2VariantsBit3, 1);
    p2FindVuProgramVariants(0x10, p2VariantsBit4, 1);
    p2FindVuProgramVariants(0x40, p2VariantsBit6, 1);
    p2FindVuProgramVariants(0x20, p2VariantsBit5, 0x10);
    p2FindVuProgramVariants(0x200, p2VariantsBit9, 1);
    p2FindVuProgramVariants(0x800, p2VariantsBit11, 2);
    p2FindVuProgramVariants(0x1000, p2VariantsBit12, 4);
    p2FindVuProgramVariants(4, p2VariantsBit2, 8);
    p2FindVuProgramVariants(0x2000, p2VariantsBit13, 2);
    p2FindVuProgramVariants(0x80, p2VariantsBit7, 0xB);
    p2FindVuProgramVariants(0x4000, p2VariantsBit14, 0x16);
    p2FindVuProgramVariants(0x100, p2VariantsBit8, 0x14);
    p2FindVuProgramVariants(0x8000, p2VariantsBit15, 0x10);
    p2FindVuProgramVariants(0x40000, p2VariantsBit18, 1);
    p2FindVuProgramVariants(0x20000, p2VariantsBit17, 2);
    p2FindVuProgramVariants(0x100000, p2VariantsBit20, 1);
    p2FindVuProgramVariants(0x01000000, p2VariantsBit24, 3);
    p2FindVuProgramVariants(0x80000, p2VariantsBit19, 0xE);
    p2FindVuProgramVariants(0x400000, p2VariantsBit22, 0x10);
    p2FindVuProgramVariants(0x800000, p2VariantsBit23, 8);
    p2FindVuProgramVariants(0x02000000, p2VariantsBit25, 0x10);
    p2FindVuProgramVariants(0x04000000, p2VariantsBit26, 2);
    p2FindVuProgramVariants(0x10000000, p2VariantsBit28, 2);
    p2FindVuProgramVariants(0x08000000, p2VariantsBit27, 8);
    p2FindVuProgramVariants(0x20000000, p2VariantsBit29, 0xB);
    p2FindVuProgramVariants(0x40000000, p2VariantsBit30, 8);
    p2FindVuProgramVariants(0x400, p2VariantsBit10, 8);
    p2FindVuProgramVariants(0x10000, p2VariantsBit16, 8);
    p2FindVuProgramVariants(0x200000, p2VariantsBit21, 4);
    p2FindVuProgramVariants(0x80000000LL, p2VariantsBit31, 3);
    DAT_0056ae40[0] = p2VariantsBit30[0];
    p2VariantsBit22[8] = p2VariantsBit22[0];
    p2VariantsBit22[9] = p2VariantsBit22[1];
    p2VariantsBit22[10] = p2VariantsBit22[2];
    p2VariantsBit22[14] = p2VariantsBit22[6];
    p2VariantsBit25[12] = p2VariantsBit25[8] = p2VariantsBit25[4] = p2VariantsBit25[0];
    p2VariantsBit25[5] = p2VariantsBit25[1];
    p2VariantsBit25[6] = p2VariantsBit25[2];
    p2VariantsBit25[7] = p2VariantsBit25[3];
    p2VariantsBit25[9] = p2VariantsBit25[1];
    p2VariantsBit25[13] = p2VariantsBit25[1];
    p2VariantsBit25[10] = p2VariantsBit25[2];
    p2VariantsBit25[14] = p2VariantsBit25[2];
    p2VariantsBit25[11] = p2VariantsBit25[3];
    p2VariantsBit25[15] = p2VariantsBit25[3];
    if (p2VariantsFirstSetup != 0) {
        p2CachedProgramAddresses[0] = p2GetVuProgramAddress(p2VariantsBit30[2]);
        p2CachedProgramAddresses[1] = p2GetVuProgramAddress(p2VariantsBit30[3]);
        var_a0 = 0;
        do {
            temp_v0_25 = (int *)((char *)p2VariantLists + (var_a0 * 4));
            var_a0 += 1;
            *temp_v0_25 = 0;
        } while (var_a0 < 6);
        p2VariantsFirstSetup = 0;
    }
    var_s3 = 0;
    var_s0 = 0;
    do {
        var_s2 = 0;
        temp_s1 = (void **)((char *)p2VariantLists + (var_s0 * 4));
        while ((var_s3 = p2FindVuProgramByBitCount(var_s0 + 2, var_s3)) != 0) {
            temp_s4 = (char *)p2VuPrograms + (var_s3 << 6);
            temp_s5 = FUN_00202fa0(*(long long *)((char *)(temp_s4) + 0));
            var_v0 = (void *)(FUN_00202f60(*temp_s1, *(long long *)((char *)(temp_s4) + 0)));
            if (var_v0 == 0) {
                var_v0 = (void *)(FUN_00203000(var_s3));
                if (var_v0 != 0) {
                    *(long long *)((char *)(var_v0) + 8) = temp_s5;
                    if (var_s2 != 0) {
                        *(int *)((char *)(var_s2) + 20) = (int)(var_v0);
                    }
                    var_s2 = (void *)(var_v0);
                    if (*temp_s1 == 0) {
                        *temp_s1 = var_v0;
                    }
                }
            }
            *(int *)((char *)(((char *)var_v0 + (((unsigned int) (*(int *)((char *)(temp_s4) + 40) & 0xFFFF0000) >> 0x10) * 4))) + 32) = var_s3;
            var_s3 += 1;
        }
        var_s0 += 1;
    } while (var_s0 < 6);
}

int p2GetPassProgramAddress(int arg0) {
    int temp_a1;
    int temp_a2;
    int var_v0;

    var_v0 = 0;
    if (p2ExtraPassCount < arg0) {
        return 0;
    }
    temp_a2 = ((unsigned int) p2ProgramFlags[0] >> 6) & 1;
    temp_a1 = ((unsigned int) p2ProgramFlags[0] >> 0xF) & 3;
    if (arg0 == 1) {
        if (p2VertexArrayMask & 0x400) {
            return p2GetVuProgramAddress(p2VariantsBit11[p2VariantSlots[11].index]);
        }
        goto block_6;
    }
block_6:
    if ((arg0 == 1) && (p2VertexArrayMask & 0x10000)) {
        return p2GetVuProgramAddress(p2VariantsBit18[p2VariantSlots[18].index]);
    }
    if ((temp_a2 != 0) || (temp_a1 != 0)) {
        return p2GetVuProgramAddress(p2VariantsBit22[p2VariantSlots[22].index]);
    }
    if (p2VertexArrayMask & 0x210400) {
        var_v0 = p2GetVuProgramAddress(p2VariantsBit25[p2VariantSlots[25].index]);
    }
    return var_v0;
}

int *FUN_00202f60(int *arg0, long long arg1) {
    for (; arg0 != 0; arg0 = (int *)arg0[5]) {
        if (arg1 == *(long long *)((char *)p2VuPrograms + (arg0[4] << 6))) break;
    }
    return arg0;
}

int FUN_00202fa0(long long arg0) {
    long long m;
    unsigned int i;
    int c;
    int j;
    int b;

    m = arg0;
    for (i = 0; i < 0x20U; i++) {
        b = 1 << i;
        if (arg0 & b) {
            break;
        }
        m |= b;
    }
    j = 0x1F;
    while (1) {
        c = 1 << j;
        if (arg0 & c) {
            break;
        }
        m |= c;
        j--;
    }
    return ~m;
}

void *FUN_00203000(int index) {
    struct P *p;
    int counts[32];
    int n;
    long long mask;
    int i;
    int total;
    int prev;

    n = 0;
    mask = *(long long *)((char *)p2VuPrograms + (index << 6));
    if (mask & 1) counts[n++] = 1;
    if (mask & 2) counts[n++] = 4;
    if (mask & 4) counts[n++] = 8;
    if (mask & 8) counts[n++] = 1;
    if (mask & 0x40) counts[n++] = 1;
    if (mask & 0x20) counts[n++] = 0x10;
    if (mask & 0x80) counts[n++] = 0xB;
    if (mask & 0x200) counts[n++] = 1;
    if (mask & 0x800) counts[n++] = 2;
    if (mask & 0x1000) counts[n++] = 4;
    if (mask & 0x2000) counts[n++] = 2;
    if (mask & 0x100) counts[n++] = 0x14;
    if (mask & 0x4000) counts[n++] = 0x16;
    if (mask & 0x8000) counts[n++] = 0x10;
    if (mask & 0x40000) counts[n++] = 1;
    if (mask & 0x20000) counts[n++] = 2;
    if (mask & 0x100000) counts[n++] = 1;
    if (mask & 0x1000000) counts[n++] = 3;
    if (mask & 0x80000) counts[n++] = 0xE;
    if (mask & 0x800000) counts[n++] = 8;
    if (mask & 0x2000000) counts[n++] = 0x10;
    if (mask & 0x4000000) counts[n++] = 2;
    if (mask & 0x10000000) counts[n++] = 2;
    if (mask & 0x8000000) counts[n++] = 8;
    if (mask & 0x20000000) counts[n++] = 0xB;
    if (mask & 0x40000000) counts[n++] = 8;
    if (mask & 0x400) counts[n++] = 8;
    if (mask & 0x10000) counts[n++] = 8;
    if (mask & 0x200000) counts[n++] = 4;
    if (mask & 0x80000000LL) counts[n++] = 3;
    total = 1;
    prev = 0;
    for (i = 0; i < n; i++) {
        prev = total;
        total *= counts[i];
    }
    p = Memory_AllocateAligned16(total * 4 + 0x28, 0x14);
    if (p != 0) {
        p->next = 0;
        p->m0 = *(long long *)((char *)p2VuPrograms + (index << 6));
        p->m8 = 0;
        p->p16 = index;
        p->sh = sqrt(prev);
        p->count = total;
        for (i = 0; i < total; i++) {
            p->tab[i] = -1;
        }
    }
    return p;
}

void FUN_00203500(void) {
    int i;
    void *p;
    void *next;

    i = 0;
    do {
        p = p2VariantLists[i];
        while (p != 0) {
            next = *(void **)((char *)p + 20);
            Memory_FreeToSelector(p, 0x14);
            p = next;
        }
        p2VariantLists[i] = 0;
        i += 1;
    } while (i < 6);
}
