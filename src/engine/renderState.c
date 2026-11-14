#include "dw4/p2dma.h"
#include "dw4/p2core.h"
extern int FUN_001f8b50();
extern int FUN_001fffb0();
extern int FUN_00200980();
extern int p2LayoutVuBuffers();
extern int FUN_00204ea0();
extern int p2DisplayListMode;
extern int DAT_0056b3b0[4];
extern int DAT_0056b3b4[4];
extern int DAT_0056b3b8[4];
extern int DAT_0056b3c0[4];
extern int DAT_0056b448[4];
extern int DAT_0056b480[4];
extern long long DAT_0056b5a8[4];
extern long long DAT_0056b5b0[4];
extern long long DAT_0056b5b8[4];
extern long long DAT_0056b5c0[4];
extern long long DAT_0056b5c8[4];
extern long long DAT_0056b5d0[4];
extern long long DAT_0056b5d8[4];
extern long long DAT_0056b5e0[4];
extern long long DAT_0056b5e8[4];
extern long long DAT_0056b5f0[4];
extern int p2LightCalcPending[4];
extern int DAT_0056ba20[4];
extern int p2LightingFunctions[4];
extern int p2StateCacheStatus;
struct P { long long m0; long long m8; int p16; struct P *next; int sh; int count; int tab[1]; };
struct E { int w0; int w4; };
extern long long p2VertexArrayMask[4];
extern int p2VuPrograms[16];
extern int DAT_0056b490[4];
int p2GetVuProgramAddress();
int p2FindVuProgramVariants(long long, int *, int);
int p2FindVuProgramByBitCount();
void *FUN_00203000();
extern int DAT_004915a8[4];
extern int DAT_0056ae40[4];
extern int DAT_0056b078[4];
extern int DAT_0056b080[4];
extern int DAT_0056b090[4];
extern int DAT_0056b098[4];
extern int DAT_0056b0a0[4];
extern int DAT_0056b0e0[4];
extern int DAT_0056b0e8[4];
extern int DAT_0056b0f0[4];
extern int DAT_0056b100[4];
extern int DAT_0056b110[4];
extern int DAT_0056b130[4];
extern int DAT_0056b160[4];
extern int DAT_0056b170[4];
extern int DAT_0056b1c0[4];
extern int DAT_0056b220[4];
extern int DAT_0056b260[4];
extern int DAT_0056b268[4];
extern int DAT_0056b270[4];
extern int DAT_0056b278[4];
extern int DAT_0056b290[4];
extern int DAT_0056b2d0[4];
extern int DAT_0056b2d4[4];
extern int DAT_0056b2d8[4];
extern int DAT_0056b2e8[4];
extern int DAT_0056b2f0[4];
extern int DAT_0056b2f4[4];
extern int DAT_0056b2f8[4];
extern int DAT_0056b308[4];
extern int DAT_0056b310[4];
extern int DAT_0056b330[4];
extern int DAT_0056b334[4];
extern int DAT_0056b338[4];
extern int DAT_0056b33c[4];
extern int DAT_0056b340[4];
extern int DAT_0056b344[4];
extern int DAT_0056b348[4];
extern int DAT_0056b34c[4];
extern int DAT_0056b350[4];
extern int DAT_0056b354[4];
extern int DAT_0056b358[4];
extern int DAT_0056b35c[4];
extern int DAT_0056b360[4];
extern int DAT_0056b364[4];
extern int DAT_0056b368[4];
extern int DAT_0056b36c[4];
extern int DAT_0056b370[4];
extern int DAT_0056b380[4];
extern int DAT_0056b3a0[4];
extern int DAT_0056b3e0[4];
extern int DAT_0056b400[4];
extern int DAT_0056b420[4];
extern int DAT_0056b430[4];
extern int DAT_0056b440[4];
extern int DAT_0056b44c[4];
extern void *DAT_0056b460[8];
extern int * DAT_0056b4a4[4];
extern int DAT_0056b4a8[4];
extern int * DAT_0056b4ac[4];
extern int DAT_0056b4b0[4];
extern int * DAT_0056b4b4[4];
extern int DAT_0056b4b8[4];
extern int * DAT_0056b4bc[4];
extern int DAT_0056b4c0[4];
extern int * DAT_0056b4c4[4];
extern int DAT_0056b4c8[4];
extern int * DAT_0056b4cc[4];
extern int DAT_0056b4d0[4];
extern int * DAT_0056b4d4[4];
extern int DAT_0056b4d8[4];
extern int * DAT_0056b4dc[4];
extern int * DAT_0056b4e4[4];
extern int DAT_0056b4e8[4];
extern int * DAT_0056b4ec[4];
extern int DAT_0056b500[4];
extern int * DAT_0056b504[4];
extern int * DAT_0056b50c[4];
extern int * DAT_0056b514[4];
extern int * DAT_0056b51c[4];
extern int DAT_0056b528[4];
extern int * DAT_0056b52c[4];
extern int DAT_0056b540[4];
extern int * DAT_0056b544[4];
extern int DAT_0056b550[4];
extern int * DAT_0056b554[4];
extern int DAT_0056b558[4];
extern int * DAT_0056b55c[4];
extern int DAT_0056b560[4];
extern int * DAT_0056b564[4];
extern int DAT_0056b578[4];
extern int * DAT_0056b57c[4];
extern int DAT_0056b580[4];
extern int * DAT_0056b584[4];
extern int DAT_0056b590[4];
extern int * DAT_0056b594[4];
extern int DAT_0056b600[4];
extern int DAT_0056b604[4];
extern int DAT_0056b4f8[4];
extern int DAT_0056b530[4];
extern int DAT_0056b568[4];
int Memory_FreeToSelector();
void *Memory_AllocateAligned16();
double sqrt(double);

void FUN_001ff3b0(int arg0) {
    int s;
    int f;
    int n, a;
    s = p2DirtyFlags & arg0;
    if (s != 0) {
        DAT_0056b5a8[0] += 1;
    }
    if (p2DisplayListMode == 0) {
        if (s & 4) {
            DAT_0056b5c0[0] += 1;
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
                        f = DAT_0056b480[0];
                        a = f & 0x10;
                        n = 0;
                        if (a && (f & 0x20)) {
                            n++;
                            p2LightingFunctions[0] = DAT_0056b3b8[0];
                        } else if (f & 0x20) {
                            n++;
                            p2LightingFunctions[0] = DAT_0056b3b4[0];
                        } else if (a) {
                            n++;
                            p2LightingFunctions[0] = DAT_0056b3b0[0];
                        }
                        if (f & 0x40) {
                            p2LightingFunctions[n] = DAT_0056b3c0[0];
                            n++;
                        }
                        if (f & 0x1C00) {
                            p2LightingFunctions[n] = DAT_0056b3c0[(f & 0x1C00) >> 10];
                            n++;
                        }
                        p2LightingFunctions[n] = DAT_0056b448[0];
                        DAT_0056ba20[0] = n + 1;
                        if (DAT_0056ba20[0] > 1) {
                            p2LightCalcPending[0] = 1;
                        } else {
                            p2LightCalcPending[0] = 0;
                        }
                    }
                }
                if (s & 0x80) {
                    p2LayoutVuBuffers();
                }
            }
        }
        if (s & 1) DAT_0056b5b0[0] += 1;
        if (s & 2) DAT_0056b5b8[0] += 1;
        if (s & 0x10) DAT_0056b5d0[0] += 1;
        if (s & 0x80) DAT_0056b5e8[0] += 1;
        if (s & 8) DAT_0056b5c8[0] += 1;
        if (s & 0x100) DAT_0056b5f0[0] += 1;
        if (s & 0x40) DAT_0056b5e0[0] += 1;
        if (s & 0x20) DAT_0056b5d8[0] += 1;
    }
}

typedef struct GsPacketBuffer { char pad0[40]; unsigned int *end; unsigned int pad44; unsigned int *cursor; } GsPacketBuffer;
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
extern GsPacketBuffer *DAT_00568f04;
void p2GrowDisplayList();
void p2SubmitDmaPacket();
extern int p2CurrentPrimitive;
extern int DAT_00490d38;
extern int DAT_00569308;
extern unsigned int DAT_004914f0, DAT_004914f4, DAT_004914f8, DAT_004914fc;
extern VifCode DAT_00491500;
extern GifTag DAT_00491510, DAT_00491520, DAT_00491530;
extern __int128 DAT_0056b760, DAT_0056b770;

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

extern p2DmaPacket *p2DmaCurrentPacket[P2_DMA_CHANNEL_COUNT];
extern int p2LoadVuPrograms();
extern int p2FunctionTables[];
extern int p2FunctionTableSizes[3];
extern unsigned int p2FunctionTablePad;
extern p2DmaTag p2FunctionTablesTag;
extern p2VifUnpack p2LightingFunctionsUnpack, p2FunctionTable0Unpack, p2FunctionTable1Unpack;
extern unsigned int p2FunctionTablesFlush, p2LightingFunctionsStmask;
extern __int128 p2SentFunctionTables[];
extern __int128 p2SentLightingFunctionsCode, p2SentLightingFunctions;
extern int p2SentFunctionTablesQwc;
void p2UpdateLights();
void p2UploadBlendMatrices();
void p2FlushGsRegisters();
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

void p2SendGifTags(void) {
    int texPrim;
    int prim;
    unsigned int *p;
    int flag;
    GifTag *tag;
    int bits;

    p = DAT_00568f04->cursor;
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
    DAT_00491500.imm = 24;
    if (DAT_0056b490[0] & 0x100) {
        tag = &DAT_00491520;
    } else {
        tag = &DAT_00491530;
    }
    if (flag) {
        bits = p2CurrentGsRegisters->prmode.half[0] & 0x7F8;
        texPrim |= bits;
        prim |= bits;
    }
    DAT_00491510.PRIM = texPrim;
    tag->PRIM = prim;
    p[0] = DAT_004914f0;
    p[1] = DAT_004914f4;
    p[2] = DAT_004914f8;
    p[3] = DAT_004914fc;
    p[4] = DAT_00491500.word;
    p[5] = ((unsigned int *)tag)[0];
    p[6] = ((unsigned int *)tag)[1];
    p[7] = ((unsigned int *)tag)[2];
    DAT_00491500.imm++;
    p[8] = DAT_00491500.word;
    p[9] = ((unsigned int *)&DAT_00491510)[0];
    p[10] = ((unsigned int *)&DAT_00491510)[1];
    p[11] = ((unsigned int *)&DAT_00491510)[2];
    DAT_0056b760 = ((__int128 *)p)[1];
    DAT_0056b770 = ((__int128 *)p)[2];
    DAT_00568f04->cursor = p + 12;
    if (DAT_00568f04->cursor >= DAT_00568f04->end) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(1);
        }
    }
}

int FUN_00200830(struct P *p, long long *out) {
    extern struct E DAT_0056b4a0[16];
    int res = 0;
    long long m;
    int i;
    int j;
    int w;
    int k;
    int f;
    int lo;
    int hi;
    struct E *e;
    for (; p != 0; p = p->next) {
        m = p->m0;
        if (m == (m & p2VertexArrayMask[0])) {
            if (!(p->m8 & p2VertexArrayMask[0])) {
                for (i = 0; i < 32; i++) {
                    if (m & (1LL << i)) break;
                }
                j = 32;
                for (; j > 0; j--) {
                    if (m & (1LL << j)) break;
                }
                e = &DAT_0056b4a0[i];
                w = e->w0 | (DAT_0056b4a0[j].w0 << p->sh);
                k = p->tab[w];
                if (k != -1) {
                    e->w0 = w;
                    e->w4 = (int)p->tab;
                    *out &= ~p->m0 | (1LL << i);
                    f = *(int *)((char *)p2VuPrograms + (k << 6) + 40);
                    lo = f & 0x30;
                    if (lo != 0) {
                        DAT_0056b480[0] = (DAT_0056b480[0] & 0x1cc0) | lo;
                    }
                    hi = f & 0x300;
                    if (hi != 0) {
                        DAT_0056b490[0] = hi;
                    }
                    res = 1;
                }
            }
        }
    }
    return res;
}

int p2GetPassCombineMode(void);
void p2GetPassMasks(int pass, unsigned int *frameMask, unsigned int *zbufMask);
/* Declared without a prototype: p2SendPassSetup passes the combine mode too, which it ignores. */
int p2GetPassProgramAddress();

/* STMASK patterns: write only the last three words of each vector, or only the second. */
#define P2_PASS_MASK 0x03030303
#define P2_PALETTE_FLAG_MASK 0xF3F3F3F3
/* The palette flag, the second byte of a V4-8 vector: set when both stages draw paletted textures. */
#define P2_PALETTE_FLAG_BOTH 0xFF00
#define P2_PALETTE_FLAG_OTHER 0x100
#define P2_STAGES_BOTH_PALETTED 3

extern p2DmaTag p2PassSetupTag;
extern p2VifUnpack p2PassSetupUnpack;
extern unsigned int p2PassSetupFlush, p2PassSetupStmask, p2PaletteFlagUnpack;
extern int p2PalettedStages;
extern __int128 p2SentPassSetup[];

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


extern unsigned int p2VuBufferLayoutTag[4];
extern unsigned int p2VuBufferBytesUnpack, p2VuBufferHalvesUnpack, p2VuBufferLayoutFlush;
extern p2VuBufferLayout p2VuBuffers;
extern VifCode p2VuBufferBase, p2VuBufferOffset;
extern unsigned int p2VuBufferLayoutNop;
extern int p2VifOffset, p2VifBase;
extern __int128 p2SentVuBufferLayout0, p2SentVuBufferLayout1, p2SentVuBufferLayout2;

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

void FUN_00202300(void) {
    void *FUN_00202f60(void *, long long);
    int FUN_00202fa0(long long);
    extern int DAT_0056b4a0[4];
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
    DAT_0056b090[0] = -1;
    DAT_0056b098[0] = -1;
    DAT_0056b0e0[0] = -1;
    DAT_0056b0e8[0] = -1;
    do {
        temp_v0 = (int *)(&(&DAT_0056b0f0[0])[var_a1]);
        *temp_v0 = -1;
        var_a1 += 1;
    } while (var_a1 < 2);
    var_a1_2 = 0;
    do {
        temp_v0_2 = (int *)(&(&DAT_0056b100[0])[var_a1_2]);
        *temp_v0_2 = -1;
        var_a1_2 += 1;
    } while (var_a1_2 < 4);
    var_a1_3 = 0;
    DAT_0056b078[0] = -1;
    do {
        temp_v0_3 = (int *)(&(&DAT_0056b080[0])[var_a1_3]);
        *temp_v0_3 = -1;
        var_a1_3 += 1;
    } while (var_a1_3 < 4);
    var_a1_4 = 0;
    do {
        temp_v0_4 = (int *)(&(&DAT_0056b110[0])[var_a1_4]);
        *temp_v0_4 = -1;
        var_a1_4 += 1;
    } while (var_a1_4 < 8);
    var_a1_5 = 0;
    do {
        temp_v0_5 = (int *)(&(&DAT_0056b160[0])[var_a1_5]);
        *temp_v0_5 = -1;
        var_a1_5 += 1;
    } while (var_a1_5 < 2);
    var_a1_6 = 0;
    do {
        temp_v0_6 = (int *)(&(&DAT_0056b130[0])[var_a1_6]);
        *temp_v0_6 = -1;
        var_a1_6 += 1;
    } while (var_a1_6 < 0xB);
    var_a1_7 = 0;
    do {
        temp_v0_7 = (int *)(&(&DAT_0056b1c0[0])[var_a1_7]);
        *temp_v0_7 = -1;
        var_a1_7 += 1;
    } while (var_a1_7 < 0x16);
    var_a1_8 = 0;
    do {
        temp_v0_8 = (int *)(&(&DAT_0056b170[0])[var_a1_8]);
        *temp_v0_8 = -1;
        var_a1_8 += 1;
    } while (var_a1_8 < 0x14);
    var_a1_9 = 0;
    do {
        temp_v0_9 = (int *)(&(&DAT_0056b220[0])[var_a1_9]);
        *temp_v0_9 = -1;
        var_a1_9 += 1;
    } while (var_a1_9 < 0x10);
    var_a1_10 = 0;
    DAT_0056b260[0] = -1;
    do {
        temp_v0_10 = (int *)(&(&DAT_0056b268[0])[var_a1_10]);
        *temp_v0_10 = -1;
        var_a1_10 += 1;
    } while (var_a1_10 < 2);
    var_a1_11 = 0;
    DAT_0056b270[0] = -1;
    do {
        temp_v0_11 = (int *)(&(&DAT_0056b278[0])[var_a1_11]);
        *temp_v0_11 = -1;
        var_a1_11 += 1;
    } while (var_a1_11 < 3);
    var_a1_12 = 0;
    do {
        temp_v0_12 = (int *)(&(&DAT_0056b290[0])[var_a1_12]);
        *temp_v0_12 = -1;
        var_a1_12 += 1;
    } while (var_a1_12 < 0xE);
    var_a1_13 = 0;
    do {
        temp_v0_13 = (int *)(&(&DAT_0056b2d0[0])[var_a1_13]);
        *temp_v0_13 = -1;
        var_a1_13 += 1;
    } while (var_a1_13 < 0x10);
    var_a1_14 = 0;
    do {
        temp_v0_14 = (int *)(&(&DAT_0056b310[0])[var_a1_14]);
        *temp_v0_14 = -1;
        var_a1_14 += 1;
    } while (var_a1_14 < 8);
    var_a1_15 = 0;
    do {
        temp_v0_15 = (int *)(&(&DAT_0056b330[0])[var_a1_15]);
        *temp_v0_15 = -1;
        var_a1_15 += 1;
    } while (var_a1_15 < 0x10);
    var_a1_16 = 0;
    do {
        temp_v0_16 = (int *)(&(&DAT_0056b370[0])[var_a1_16]);
        *temp_v0_16 = -1;
        var_a1_16 += 1;
    } while (var_a1_16 < 2);
    var_a1_17 = 0;
    do {
        temp_v0_17 = (int *)(&(&DAT_0056b3a0[0])[var_a1_17]);
        *temp_v0_17 = -1;
        var_a1_17 += 1;
    } while (var_a1_17 < 2);
    var_a1_18 = 0;
    do {
        temp_v0_18 = (int *)(&(&DAT_0056b380[0])[var_a1_18]);
        *temp_v0_18 = -1;
        var_a1_18 += 1;
    } while (var_a1_18 < 8);
    var_a1_19 = 0;
    do {
        temp_v0_19 = (int *)(&(&DAT_0056b3b0[0])[var_a1_19]);
        *temp_v0_19 = -1;
        var_a1_19 += 1;
    } while (var_a1_19 < 0xB);
    var_a1_20 = 0;
    do {
        temp_v0_20 = (int *)(&(&DAT_0056b440[0])[var_a1_20]);
        *temp_v0_20 = -1;
        var_a1_20 += 1;
    } while (var_a1_20 < 8);
    var_a1_21 = 0;
    do {
        temp_v0_21 = (int *)(&(&DAT_0056b3e0[0])[var_a1_21]);
        *temp_v0_21 = -1;
        var_a1_21 += 1;
    } while (var_a1_21 < 8);
    var_a1_22 = 0;
    do {
        temp_v0_22 = (int *)(&(&DAT_0056b400[0])[var_a1_22]);
        *temp_v0_22 = -1;
        var_a1_22 += 1;
    } while (var_a1_22 < 8);
    var_a1_23 = 0;
    do {
        temp_v0_23 = (int *)(&(&DAT_0056b420[0])[var_a1_23]);
        *temp_v0_23 = -1;
        var_a1_23 += 1;
    } while (var_a1_23 < 4);
    var_a1_24 = 0;
    do {
        temp_v0_24 = (int *)(&(&DAT_0056b430[0])[var_a1_24]);
        *temp_v0_24 = -1;
        var_a1_24 += 1;
    } while (var_a1_24 < 3);
    DAT_0056b4d8[0] = 0;
    DAT_0056b4dc[0] = (int *)(&DAT_0056b130[0]);
    DAT_0056b50c[0] = (int *)(&DAT_0056b160[0]);
    DAT_0056b514[0] = (int *)(&DAT_0056b1c0[0]);
    DAT_0056b4e4[0] = (int *)(&DAT_0056b170[0]);
    DAT_0056b51c[0] = (int *)(&DAT_0056b220[0]);
    DAT_0056b4a4[0] = (int *)(&DAT_0056b078[0]);
    DAT_0056b4ac[0] = (int *)(&DAT_0056b080[0]);
    DAT_0056b4b4[0] = (int *)(&DAT_0056b110[0]);
    DAT_0056b4bc[0] = (int *)(&DAT_0056b090[0]);
    DAT_0056b4c4[0] = (int *)(&DAT_0056b098[0]);
    DAT_0056b4d4[0] = (int *)(&DAT_0056b0e0[0]);
    DAT_0056b4ec[0] = (int *)(&DAT_0056b0e8[0]);
    DAT_0056b504[0] = (int *)(&DAT_0056b100[0]);
    DAT_0056b52c[0] = (int *)(&DAT_0056b268[0]);
    DAT_0056b544[0] = (int *)(&DAT_0056b270[0]);
    DAT_0056b564[0] = (int *)(&DAT_0056b278[0]);
    DAT_0056b554[0] = (int *)(&DAT_0056b2d0[0]);
    DAT_0056b55c[0] = (int *)(&DAT_0056b310[0]);
    DAT_0056b584[0] = (int *)(&DAT_0056b3a0[0]);
    DAT_0056b57c[0] = (int *)(&DAT_0056b380[0]);
    DAT_0056b590[0] = 4;
    DAT_0056b594[0] = (int *)(&DAT_0056b440[0]);
    DAT_0056b4cc[0] = (int *)(&DAT_0056b0a0[0]);
    DAT_0056b4a0[0] = 0;
    DAT_0056b4a8[0] = 0;
    DAT_0056b4b0[0] = 0;
    DAT_0056b4b8[0] = 0;
    DAT_0056b4c0[0] = 0;
    DAT_0056b4d0[0] = 0;
    DAT_0056b4e8[0] = 0;
    DAT_0056b500[0] = 0;
    DAT_0056b528[0] = 0;
    DAT_0056b540[0] = 0;
    DAT_0056b560[0] = 0;
    DAT_0056b550[0] = 0;
    DAT_0056b558[0] = 0;
    DAT_0056b580[0] = 0;
    DAT_0056b578[0] = 0;
    DAT_0056b4c8[0] = 0;
    p2FindVuProgramVariants(1, &DAT_0056b078[0], 1);
    p2FindVuProgramVariants(2, &DAT_0056b080[0], 4);
    p2FindVuProgramVariants(4, &DAT_0056b110[0], 8);
    p2FindVuProgramVariants(8, &DAT_0056b090[0], 1);
    p2FindVuProgramVariants(0x10, &DAT_0056b098[0], 1);
    p2FindVuProgramVariants(0x40, &DAT_0056b0e0[0], 1);
    p2FindVuProgramVariants(0x20, &DAT_0056b0a0[0], 0x10);
    p2FindVuProgramVariants(0x200, &DAT_0056b0e8[0], 1);
    p2FindVuProgramVariants(0x800, &DAT_0056b0f0[0], 2);
    p2FindVuProgramVariants(0x1000, &DAT_0056b100[0], 4);
    p2FindVuProgramVariants(4, &DAT_0056b110[0], 8);
    p2FindVuProgramVariants(0x2000, &DAT_0056b160[0], 2);
    p2FindVuProgramVariants(0x80, &DAT_0056b130[0], 0xB);
    p2FindVuProgramVariants(0x4000, &DAT_0056b1c0[0], 0x16);
    p2FindVuProgramVariants(0x100, &DAT_0056b170[0], 0x14);
    p2FindVuProgramVariants(0x8000, &DAT_0056b220[0], 0x10);
    p2FindVuProgramVariants(0x40000, &DAT_0056b260[0], 1);
    p2FindVuProgramVariants(0x20000, &DAT_0056b268[0], 2);
    p2FindVuProgramVariants(0x100000, &DAT_0056b270[0], 1);
    p2FindVuProgramVariants(0x01000000, &DAT_0056b278[0], 3);
    p2FindVuProgramVariants(0x80000, &DAT_0056b290[0], 0xE);
    p2FindVuProgramVariants(0x400000, &DAT_0056b2d0[0], 0x10);
    p2FindVuProgramVariants(0x800000, &DAT_0056b310[0], 8);
    p2FindVuProgramVariants(0x02000000, &DAT_0056b330[0], 0x10);
    p2FindVuProgramVariants(0x04000000, &DAT_0056b370[0], 2);
    p2FindVuProgramVariants(0x10000000, &DAT_0056b3a0[0], 2);
    p2FindVuProgramVariants(0x08000000, &DAT_0056b380[0], 8);
    p2FindVuProgramVariants(0x20000000, &DAT_0056b3b0[0], 0xB);
    p2FindVuProgramVariants(0x40000000, &DAT_0056b440[0], 8);
    p2FindVuProgramVariants(0x400, &DAT_0056b3e0[0], 8);
    p2FindVuProgramVariants(0x10000, &DAT_0056b400[0], 8);
    p2FindVuProgramVariants(0x200000, &DAT_0056b420[0], 4);
    p2FindVuProgramVariants(0x80000000LL, &DAT_0056b430[0], 3);
    DAT_0056ae40[0] = DAT_0056b440[0];
    DAT_0056b2f0[0] = DAT_0056b2d0[0];
    DAT_0056b2f4[0] = DAT_0056b2d4[0];
    DAT_0056b2f8[0] = DAT_0056b2d8[0];
    DAT_0056b308[0] = DAT_0056b2e8[0];
    DAT_0056b360[0] = DAT_0056b350[0] = DAT_0056b340[0] = DAT_0056b330[0];
    DAT_0056b344[0] = DAT_0056b334[0];
    DAT_0056b348[0] = DAT_0056b338[0];
    DAT_0056b34c[0] = DAT_0056b33c[0];
    DAT_0056b354[0] = DAT_0056b334[0];
    DAT_0056b364[0] = DAT_0056b334[0];
    DAT_0056b358[0] = DAT_0056b338[0];
    DAT_0056b368[0] = DAT_0056b338[0];
    DAT_0056b35c[0] = DAT_0056b33c[0];
    DAT_0056b36c[0] = DAT_0056b33c[0];
    if (DAT_004915a8[0] != 0) {
        DAT_0056b600[0] = p2GetVuProgramAddress(DAT_0056b448[0], DAT_0056b334[0], DAT_0056b2d0[0], DAT_0056b440[0]);
        DAT_0056b604[0] = p2GetVuProgramAddress(DAT_0056b44c[0]);
        var_a0 = 0;
        do {
            temp_v0_25 = (int *)((char *)DAT_0056b460 + (var_a0 * 4));
            var_a0 += 1;
            *temp_v0_25 = 0;
        } while (var_a0 < 6);
        DAT_004915a8[0] = 0;
    }
    var_s3 = 0;
    var_s0 = 0;
    do {
        var_s2 = 0;
        temp_s1 = (void **)((char *)DAT_0056b460 + (var_s0 * 4));
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
        if (p2VertexArrayMask[0] & 0x400) {
            return p2GetVuProgramAddress(DAT_0056b0f0[DAT_0056b4f8[0]], temp_a1, temp_a2);
        }
        goto block_6;
    }
block_6:
    if ((arg0 == 1) && (p2VertexArrayMask[0] & 0x10000)) {
        return p2GetVuProgramAddress(DAT_0056b260[DAT_0056b530[0]], temp_a1, temp_a2);
    }
    if ((temp_a2 != 0) || (temp_a1 != 0)) {
        return p2GetVuProgramAddress(DAT_0056b2d0[DAT_0056b550[0]], temp_a1, temp_a2);
    }
    if (p2VertexArrayMask[0] & 0x210400) {
        var_v0 = p2GetVuProgramAddress(DAT_0056b330[DAT_0056b568[0]], temp_a1, temp_a2);
    }
    return var_v0;
}

int *FUN_00202f60(int *arg0, long long arg1) {
    for (; arg0 != 0; arg0 = (int *)arg0[5]) {
        if (arg1 == *(long long *)((char *)p2VuPrograms + (arg0[4] << 6))) break;
    }
    return arg0;
}

long long FUN_00202fa0(int arg0) {
    int m;
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
        p = DAT_0056b460[i];
        while (p != 0) {
            next = *(void **)((char *)p + 20);
            Memory_FreeToSelector(p, 0x14);
            p = next;
        }
        DAT_0056b460[i] = 0;
        i += 1;
    } while (i < 6);
}
