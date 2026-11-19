#include <math.h>
#include "dw4/p2/p2dma.h"
#include "dw4/p2/p2core.h"
#include "dw4/p2/dmaChannel.h"
#include "dw4/p2/p2draw.h"
#include "dw4/p2/p2gs.h"
#include "dw4/p2/renderState.h"
#include "dw4/p2/p2multipass.h"
#include "dw4/core/igMemory.h"
extern int FUN_001f8b50();
extern int FUN_001fffb0();
extern int p2LookupStateCacheEntry();

/* The programs that share a feature mask, one per combination of the settings of its features: the
 * combination of the mask's lowest and highest feature indexes the table (the highest shifted by
 * `shift`). A table applies while the vertex arrays have every feature of `key` and none of the
 * `excluded` ones between them. The tables of programs with the same number of features are chained
 * through `next`. */
typedef struct p2VariantTable {
    long long key;
    long long excluded;
    int program;                        /* the program the table was made for */
    struct p2VariantTable *next;
    int shift;
    int count;
    int programs[1];                    /* count entries; -1: no program */
} p2VariantTable;
p2VariantTable *p2FindVariantTable(p2VariantTable *table, long long key);
int p2MaskGaps(long long mask);
p2VariantTable *p2CreateVariantTable(int program);
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
p2VariantTable *p2VariantLists[6];
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

void p2PrepareRenderState(int mask) {
    int s;
    int f;
    int n, a;
    s = p2DirtyFlags & mask;
    if (s != 0) {
        p2StatStateSends += 1;
    }
    if (p2DisplayListMode == 0) {
        if (s & 4) {
            p2StatLightsSent += 1;
            FUN_001f8b50();
            s = p2DirtyFlags & mask;
        }
        if (s & 0x193) {
            p2StateCacheStatus = p2LookupStateCacheEntry();
            s = p2DirtyFlags & mask;
            if (p2StateCacheStatus == 0 || (p2StateCacheStatus == 1 && (s & 0x100))) {
                if (s & 0x10) {
                    FUN_001fffb0(p2StateCacheStatus);
                    s |= 0x80;
                    p2DirtyFlags |= 0x80;
                }
                if (s & 1) {
                    p2BuildFunctionTables();
                    s = p2DirtyFlags & mask;
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

int p2SelectVariantTables(p2VariantTable *table, long long *out) {
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
    for (; table != 0; table = table->next) {
        m = table->key;
        if (m == (m & p2VertexArrayMask)) {
            if (!(table->excluded & p2VertexArrayMask)) {
                for (i = 0; i < 32; i++) {
                    if (m & (1LL << i)) break;
                }
                j = 32;
                for (; j > 0; j--) {
                    if (m & (1LL << j)) break;
                }
                e = &p2VariantSlots[i];
                w = e->index | (p2VariantSlots[j].index << table->shift);
                k = table->programs[w];
                if (k != -1) {
                    e->index = w;
                    e->programs = table->programs;
                    *out &= ~table->key | (1LL << i);
                    f = p2VuPrograms[k].flags;
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

int p2GetPassProgramAddress(int pass, int combineMode);

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

void p2SetupProgramVariants(void) {
    int i;
    int program;
    long long excluded;
    p2VuProgram *entry;
    p2VariantTable *last;
    p2VariantTable **list;
    int bitCount;
    p2VariantTable *table;

    p2VariantsBit3[0] = -1;
    p2VariantsBit4[0] = -1;
    p2VariantsBit6[0] = -1;
    p2VariantsBit9[0] = -1;
    for (i = 0; i < 2; i++) {
        p2VariantsBit11[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        p2VariantsBit12[i] = -1;
    }
    p2VariantsBit0[0] = -1;
    for (i = 0; i < 4; i++) {
        p2VariantsBit1[i] = -1;
    }
    for (i = 0; i < 8; i++) {
        p2VariantsBit2[i] = -1;
    }
    for (i = 0; i < 2; i++) {
        p2VariantsBit13[i] = -1;
    }
    for (i = 0; i < 11; i++) {
        p2VariantsBit7[i] = -1;
    }
    for (i = 0; i < 22; i++) {
        p2VariantsBit14[i] = -1;
    }
    for (i = 0; i < 20; i++) {
        p2VariantsBit8[i] = -1;
    }
    for (i = 0; i < 16; i++) {
        p2VariantsBit15[i] = -1;
    }
    p2VariantsBit18[0] = -1;
    for (i = 0; i < 2; i++) {
        p2VariantsBit17[i] = -1;
    }
    p2VariantsBit20[0] = -1;
    for (i = 0; i < 3; i++) {
        p2VariantsBit24[i] = -1;
    }
    for (i = 0; i < 14; i++) {
        p2VariantsBit19[i] = -1;
    }
    for (i = 0; i < 16; i++) {
        p2VariantsBit22[i] = -1;
    }
    for (i = 0; i < 8; i++) {
        p2VariantsBit23[i] = -1;
    }
    for (i = 0; i < 16; i++) {
        p2VariantsBit25[i] = -1;
    }
    for (i = 0; i < 2; i++) {
        p2VariantsBit26[i] = -1;
    }
    for (i = 0; i < 2; i++) {
        p2VariantsBit28[i] = -1;
    }
    for (i = 0; i < 8; i++) {
        p2VariantsBit27[i] = -1;
    }
    for (i = 0; i < 11; i++) {
        p2VariantsBit29[i] = -1;
    }
    for (i = 0; i < 8; i++) {
        p2VariantsBit30[i] = -1;
    }
    for (i = 0; i < 8; i++) {
        p2VariantsBit10[i] = -1;
    }
    for (i = 0; i < 8; i++) {
        p2VariantsBit16[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        p2VariantsBit21[i] = -1;
    }
    for (i = 0; i < 3; i++) {
        p2VariantsBit31[i] = -1;
    }
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
        for (i = 0; i < 6; i++) {
            p2VariantLists[i] = 0;
        }
        p2VariantsFirstSetup = 0;
    }
    program = 0;
    bitCount = 0;
    do {
        last = 0;
        list = &p2VariantLists[bitCount];
        while ((program = p2FindVuProgramByBitCount(bitCount + 2, program)) != 0) {
            entry = &p2VuPrograms[program];
            excluded = p2MaskGaps(entry->key);
            table = p2FindVariantTable(*list, entry->key);
            if (table == 0) {
                table = p2CreateVariantTable(program);
                if (table != 0) {
                    table->excluded = excluded;
                    if (last != 0) {
                        last->next = table;
                    }
                    last = table;
                    if (*list == 0) {
                        *list = table;
                    }
                }
            }
            table->programs[(entry->flags & 0xFFFF0000) >> 16] = program;
            program += 1;
        }
        bitCount += 1;
    } while (bitCount < 6);
}

/* The VU program of a pass; p2SendPassSetup also passes the combine mode, which the choice ignores. */
int p2GetPassProgramAddress(int pass, int combineMode) {
    int flagBits15;
    int flagBit6;
    int address;

    address = 0;
    if (p2ExtraPassCount < pass) {
        return 0;
    }
    flagBit6 = ((unsigned int) p2ProgramFlags[0] >> 6) & 1;
    flagBits15 = ((unsigned int) p2ProgramFlags[0] >> 0xF) & 3;
    if (pass == 1) {
        if (p2VertexArrayMask & 0x400) {
            return p2GetVuProgramAddress(p2VariantsBit11[p2VariantSlots[11].index]);
        }
    }
    if ((pass == 1) && (p2VertexArrayMask & 0x10000)) {
        return p2GetVuProgramAddress(p2VariantsBit18[p2VariantSlots[18].index]);
    }
    if ((flagBit6 != 0) || (flagBits15 != 0)) {
        return p2GetVuProgramAddress(p2VariantsBit22[p2VariantSlots[22].index]);
    }
    if (p2VertexArrayMask & 0x210400) {
        address = p2GetVuProgramAddress(p2VariantsBit25[p2VariantSlots[25].index]);
    }
    return address;
}

p2VariantTable *p2FindVariantTable(p2VariantTable *table, long long key) {
    for (; table != 0; table = table->next) {
        if (key == p2VuPrograms[table->program].key) break;
    }
    return table;
}

/* The features missing from `mask` between its lowest and highest. */
int p2MaskGaps(long long mask) {
    long long filled;
    unsigned int i;
    int bit;
    int j;
    int low;

    filled = mask;
    for (i = 0; i < 0x20U; i++) {
        low = 1 << i;
        if (mask & low) {
            break;
        }
        filled |= low;
    }
    j = 0x1F;
    while (1) {
        bit = 1 << j;
        if (mask & bit) {
            break;
        }
        filled |= bit;
        j--;
    }
    return ~filled;
}

p2VariantTable *p2CreateVariantTable(int program) {
    p2VariantTable *table;
    int counts[32];
    int n;
    long long mask;
    int i;
    int total;
    int prev;

    n = 0;
    mask = p2VuPrograms[program].key;
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
    table = Memory_AllocateAligned16(total * 4 + 0x28, 0x14);
    if (table != 0) {
        table->next = 0;
        table->key = p2VuPrograms[program].key;
        table->excluded = 0;
        table->program = program;
        table->shift = sqrt(prev);
        table->count = total;
        for (i = 0; i < total; i++) {
            table->programs[i] = -1;
        }
    }
    return table;
}

void p2FreeVariantTables(void) {
    int i;
    p2VariantTable *table;
    p2VariantTable *next;

    i = 0;
    do {
        table = p2VariantLists[i];
        while (table != 0) {
            next = table->next;
            Memory_FreeToSelector(table, 0x14);
            table = next;
        }
        p2VariantLists[i] = 0;
        i += 1;
    } while (i < 6);
}
