#include <stdio.h>
#include "dw4/p2/p2dma.h"
#include "dw4/p2/p2core.h"
#include "dw4/p2/p2draw.h"
#include "dw4/p2/p2gs.h"
#include "dw4/p2/p2lighting.h"
#include "dw4/p2/p2swap.h"
#include "dw4/p2/p2timer.h"
#include "dw4/p2/dmaChannel.h"
#include "dw4/p2/renderState.h"
#include "dw4/sony/libkernl.h"
#include "dw4/p2/p2textureCalls.h"
/* The vertices and primitives drawn from display lists. */
extern long long p2StatDisplayListVertices;
extern long long p2StatDisplayListPrimitives;
extern int p2UnusedWaitTime0[4];
extern int p2UnusedWaitTime1[4];
extern int p2UnusedWaitTime2[4];
extern int p2UnusedWaitTime3[4];
extern const char text_GS_csr_id_d_csr_rev_d[];
/* The newest VIF1 sequence the GS has finished drawing, as p2RecordFinishedSequence records it. */
extern long long p2FinishedSequence[4];
typedef union DmaTag {
    struct {
        unsigned int qwc : 16;
        unsigned int pad : 10;
        unsigned int pce : 2;
        unsigned int id : 3;
        unsigned int irq : 1;
        unsigned int addr : 31;
        unsigned int spr : 1;
        unsigned int data[2];
    } f;
    unsigned int w[4];
} DmaTag;

extern DmaTag p2GifCallTag;

typedef struct GifTag {
    unsigned long long nloop : 15;
    unsigned long long eop : 1;
    unsigned long long pad : 16;
    unsigned long long id : 14;
    unsigned long long pre : 1;
    unsigned long long prim : 11;
    unsigned long long flg : 2;
    unsigned long long nreg : 4;
    unsigned long long regs;
} __attribute__((aligned(16))) GifTag;

typedef union VifCode {
    struct {
        unsigned int immediate : 16;
        unsigned int num : 8;
        unsigned int cmd : 8;
    } field;
    unsigned int word;
} VifCode;

typedef union VifQuad {
    VifCode code[4];
    unsigned __int128 q;
} VifQuad;

typedef union GsRegWrite {
    struct {
        unsigned long long data;
        unsigned long long addr;
    } f;
    unsigned __int128 q;
} GsRegWrite;

typedef union GifQuad {
    GifTag f;
    unsigned __int128 q;
} GifQuad;

extern VifCode p2GsRegisterPacketMscal;
extern DmaTag p2GsRegisterDmaTag;
extern GifQuad p2GsRegisterGifTag;
extern VifQuad p2GsRegisterPacketHead;
extern VifQuad p2GsRegisterPacketTail;
extern unsigned char p2GsRegisterAddresses[];

extern char text_p2readGSPrivRegister[];
enum GsPrivRegister {
    GSPRIV_PMODE = 0x0,
    GSPRIV_SMODE2 = 0x2,
    GSPRIV_DISPFB1 = 0x7,
    GSPRIV_DISPLAY1 = 0x8,
    GSPRIV_DISPFB2 = 0x9,
    GSPRIV_DISPLAY2 = 0xA,
    GSPRIV_EXTBUF = 0xB,
    GSPRIV_EXTDATA = 0xC,
    GSPRIV_EXTWRITE = 0xD,
    GSPRIV_BGCOLOR = 0xE,
    GSPRIV_CSR = 0x40,
    GSPRIV_IMR = 0x41,
    GSPRIV_BUSDIR = 0x44,
    GSPRIV_SIGLBLID = 0x48
};

/* Memory-mapped 64-bit registers. */
#define GS_PMODE    (*(long long *)0x12000000)
#define GS_SMODE2   (*(long long *)0x12000020)
#define GS_DISPFB1  (*(long long *)0x12000070)
#define GS_DISPLAY1 (*(long long *)0x12000080)
#define GS_DISPFB2  (*(long long *)0x12000090)
#define GS_DISPLAY2 (*(long long *)0x120000A0)
#define GS_EXTBUF   (*(long long *)0x120000B0)
#define GS_EXTDATA  (*(long long *)0x120000C0)
#define GS_EXTWRITE (*(long long *)0x120000D0)
#define GS_BGCOLOR  (*(long long *)0x120000E0)
#define GS_CSR      (*(long long *)0x12001000)
#define GS_IMR      (*(long long *)0x12001010)
#define GS_BUSDIR   (*(long long *)0x12001040)
#define GS_SIGLBLID (*(long long *)0x12001080)

void p2GetStatistics(void *statistics) {
    p2Statistics *stats = statistics;
    int textureSpace;

    stats->vertices = p2VertexCount;
    stats->primitives = p2PrimitiveCount;
    stats->displayListVertices = p2StatDisplayListVertices;
    stats->displayListPrimitives = p2StatDisplayListPrimitives;
    stats->textureBinds = p2StatTextureBinds;
    stats->textureMemoryUsed = p2StatTextureMemoryUsed;
    p2GetTextureBase(&textureSpace);
    textureSpace = (0x4000 - textureSpace) << 8;
    stats->vif1InterruptCount = p2StatVif1InterruptCount;
    stats->gifInterruptCount = p2StatGifInterruptCount;
    stats->textureMemoryFree = (textureSpace - p2StatTextureMemoryUsed);
    stats->framesTimed = p2FramesTimed;
    stats->vsyncs = p2Vsyncs;
    stats->stateSends = p2StatStateSends;
    stats->functionTablesSent = p2StatFunctionTablesSent;
    stats->lightingFunctionsSent = p2StatLightingFunctionsSent;
    stats->lightsSent = p2StatLightsSent;
    stats->gifTagsSent = p2StatGifTagsSent;
    stats->vertexFormatsSent = p2StatVertexFormatsSent;
    stats->blendMatricesSent = p2StatBlendMatricesSent;
    stats->gsRegistersSent = p2StatGsRegistersSent;
    stats->vuBufferLayoutsSent = p2StatVuBufferLayoutsSent;
    stats->passSetupsSent = p2StatPassSetupsSent;
    stats->lightingSwitches = p2StatLightingSwitches;
    stats->materialSets = p2StatMaterialSets;
    stats->lightingModeSets = p2StatLightingModeSets;
    stats->lightSets = p2StatLightSets;
    stats->lightSwitches = p2StatLightSwitches;
    stats->colourModeChanges = p2ColourModeChanges;
    stats->primitiveChanges = p2PrimitiveChanges;
    stats->capabilityChanges = p2StatCapabilityChanges;
    stats->vif1DmaCount = p2StatVif1DmaCount;
    stats->vif1PartialPackets = p2StatVif1PartialPackets;
    stats->vif1DmaQuadwords = p2StatVif1DmaQuadwords;
    stats->vif1DmaTime = p2StatVif1DmaTime;
    stats->gifDmaCount = p2StatGifDmaCount;
    stats->gifPartialPackets = p2StatGifPartialPackets;
    stats->gifDmaQuadwords = p2StatGifDmaQuadwords;
    stats->gifDmaTime = p2StatGifDmaTime;
    stats->dmaOverlapTime = p2StatDmaOverlapTime;
    stats->frameTimeTotal = p2FrameTimeTotal;
    stats->frameTimeMin = p2FrameTimeMin;
    stats->frameTimeMax = p2FrameTimeMax;
    stats->unusedWaitTime0 = p2UnusedWaitTime0[0];
    stats->unusedWaitTime1 = p2UnusedWaitTime1[0];
    stats->unusedWaitTime2 = p2UnusedWaitTime2[0];
    stats->dmaWaitTime = p2DmaWaitTime;
    stats->swapWaitTime = p2SwapWaitTime;
    stats->finishWaitTime = p2FinishWaitTime;
    stats->unusedWaitTime3 = p2UnusedWaitTime3[0];
    stats->sleepTime = p2SleepTime;
    stats->fastPathVertices = p2StatVertexCount1;
    stats->fastLitPathVertices = p2StatVertexCount4;
    stats->litPathVertices = p2StatVertexCount2;
    stats->vu1BlendVertices = p2StatVertexCount8;
    stats->vu0BlendVertices = p2StatFourWeightBlendVertices;
    stats->vu1MultiPassVertices = p2StatVertexCount16;
    stats->indexedVertices = p2IndexedVertexCount;
    p2FrameTimeMin = 0xFFFFFFFFLL;
    p2FrameTimeMax = 0;
}

/* The VIF1 chain p2SetColour sends: a DMA cnt tag over one quadword whose two VIF slots idle,
 * then a FLUSHE and an UNPACK V4-8 of the colour into VU1 data memory. */
typedef struct p2ColourPacket {
    unsigned int tag[2];
    VifCode tagCodes[2];
    VifCode flush;
    VifCode idle;
    VifCode unpack;
    unsigned int colour;
} p2ColourPacket;

/* UNPACK's immediate: the VU address in the low bits, bit 14 for unsigned elements. */
#define P2_VIF_UNPACK_UNSIGNED 0x4000
/* The VU1 data address of the current colour. */
#define P2_VU1_COLOUR 0x1B

extern p2ColourPacket p2ColourPacketTemplate;
extern unsigned int p2ColourNop;

/* Sends the current colour, packed RGBA, to VU1 data memory. */
void p2SetColour(unsigned int colour) {
    unsigned int *p = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
    p2ColourPacketTemplate.unpack.field.immediate = P2_VIF_UNPACK_UNSIGNED | P2_VU1_COLOUR;
    p[0] = p2ColourPacketTemplate.tag[0];
    p[1] = p2ColourPacketTemplate.tag[1];
    p[2] = p2ColourPacketTemplate.tagCodes[0].word;
    p[3] = p2ColourPacketTemplate.tagCodes[1].word;
    p[4] = p2ColourPacketTemplate.flush.word;
    p[5] = p2ColourNop;
    p[6] = p2ColourPacketTemplate.unpack.word;
    p += 7;
    *p++ = colour;
    p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)p;
    if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(P2_DMA_VIF1);
        }
    }
}

void FUN_001f7330(void)
{
}

void p2SetSpriteSizeMode(int mode) {
    p2SpriteSizeMode = mode;
    p2DirtyFlags |= 0x11;
}

int p2GetSpriteSizeMode(void)
{
    return p2SpriteSizeMode;
}

/* The VIF1 chain p2SetSpriteHalfSize sends: a DMA cnt tag over two quadwords, a FLUSHE, an STMASK
 * that keeps the first element of a vector, then a masked UNPACK S-32 of one word into VU1 data
 * memory. */
typedef struct p2SpriteSizeCodes {
    unsigned int tag[4];
    VifCode flush;
    unsigned int pad0;
    VifCode unpack;
    unsigned int pad1;
    VifCode stmask;
} p2SpriteSizeCodes;

extern p2SpriteSizeCodes p2SpriteSizePacket;
extern unsigned int p2SpriteSizeNop;

void p2SetSpriteHalfSize(float halfSize) {
    unsigned int *p = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
    p[0] = p2SpriteSizePacket.tag[0];
    p[1] = p2SpriteSizePacket.tag[1];
    p[2] = p2SpriteSizePacket.tag[2];
    p[3] = p2SpriteSizePacket.tag[3];
    p[4] = p2SpriteSizePacket.flush.word;
    p[5] = p2SpriteSizePacket.stmask.word;
    p[6] = 0xFCFCFCFC;
    p[7] = p2SpriteSizeNop;
    p[8] = p2SpriteSizePacket.unpack.word;
    ((float *)p)[9] = halfSize;
    p[10] = p2SpriteSizeNop;
    p[11] = p2SpriteSizeNop;
    p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)(p + 12);
    if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(1);
        }
    }
}

void p2SetPolygonMode(int mode) {
    p2PolygonMode = mode;
    p2DirtyFlags |= 0x19;
}

void p2PrintGsRevision(void) {
    long long csr;
    int id, revision;
    csr = p2readGSPrivRegister(0x40);
    id = (csr >> 0x18) & 0xFF;
    revision = (csr >> 0x10) & 0xFF;
    printf(text_GS_csr_id_d_csr_rev_d, id, revision);
}

int p2SequenceFinishedPredicate(long long sequence)
{
    return p2FinishedSequence[0] >= sequence;
}

void p2RecordFinishedSequence(p2FinishFunc *finish, int arg) {
    long long sequence;

    sequence = finish->sequence;
    if (p2FinishedSequence[0] < sequence) {
        p2FinishedSequence[0] = sequence;
    }
}


typedef struct {
    unsigned long long SIGNAL:1;
    unsigned long long FINISH:1;
    unsigned long long HSINT:1;
    unsigned long long VSINT:1;
    unsigned long long EDWINT:1;
    unsigned long long ZERO1:1;
    unsigned long long ZERO2:1;
    unsigned long long pad1:1;
    unsigned long long FLUSH:1;
    unsigned long long RESET:1;
    unsigned long long p0:2;
    unsigned long long NFIELD:1;
    unsigned long long FIELD:1;
    unsigned long long FIFO:2;
    unsigned long long REV:8;
    unsigned long long ID:8;
    unsigned long long p1:32;
} tGS_CSR;

extern tGS_CSR p2GsCsr;
extern long long p2GsImr;
extern int p2GsInterrupts;
extern int p2GsVsyncInterrupts;
extern int p2GsSignalInterrupts;

int p2GsInterruptHandler(int cause) {
    long long status;

    p2GsImr = -1;
    p2writeGSPrivRegister(0x41);
    status = p2readGSPrivRegister(0x40);
    p2GsInterrupts++;
    p2GsCsr.FINISH = (status & 2) ? 1 : 0;
    p2GsCsr.VSINT = (status & 8) ? 1 : 0;
    p2GsCsr.SIGNAL = (status & 1) ? 1 : 0;
    p2writeGSPrivRegister(0x40);
    if (p2DisplayClosing == 0) {
        if (status & 2) {
            p2FinishHandler();
        }
        if (status & 8) {
            p2VsyncHandler();
            p2GsVsyncInterrupts++;
        }
        if (status & 1) {
            p2GsSignalHandler();
            p2GsSignalInterrupts++;
        }
    }
    p2GsImr = -0xB01;
    p2writeGSPrivRegister(0x41);
    __asm__ __volatile__("sync\nei\n");
    return 0;
}

void p2SendGsRegister(int registerIndex) {
    int registers;

    registers = registerIndex;
    p2UploadGsRegisters(1, &registers);
}

void p2UploadGsRegisters(int count, int *regs) {
    int n;

    if (p2CurrentProgram == 0) {
        p2GsRegisterPacketMscal.field.immediate = p2GetVuProgramAddress(p2GsRegisterProgram);
        for (; count > 0; count -= n, regs += n) {
            int i;
            unsigned __int128 *p;
            int *r;
            GsRegWrite ad;

            n = count < 16 ? count : 16;
            p = (unsigned __int128 *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
            r = regs;
            p2GsRegisterGifTag.f.nreg = n;
            p2GsRegisterDmaTag.f.qwc = n + 3;
            ((unsigned int *)p)[0] = p2GsRegisterDmaTag.w[0];
            ((unsigned int *)p)[1] = p2GsRegisterDmaTag.w[1];
            ((unsigned int *)p)[2] = p2GsRegisterDmaTag.w[2];
            ((unsigned int *)p)[3] = p2GsRegisterDmaTag.w[3];
            p2GsRegisterPacketHead.code[3].field.num = n + 1;
            p[1] = p2GsRegisterPacketHead.q;
            *(p += 2) = p2GsRegisterGifTag.q;
            p++;
            for (i = 0; i < n; i++) {
                int reg = *r++;
                ad.f.data = ((unsigned long long *)p2CurrentGsRegisters)[reg];
                ad.f.addr = p2GsRegisterAddresses[reg];
                *p = ad.q;
                p++;
            }
            *p = p2GsRegisterPacketTail.q;
            p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)(p + 1);
            if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
                if (p2DisplayListMode != 0) {
                    p2GrowDisplayList();
                } else {
                    p2SubmitDmaPacket(1);
                }
            }
        }
    } else {
        p2UploadGsRegistersGif(count, regs, 1);
    }
}

/* The DMA and GIF tags of the packets p2UploadDirtyGsRegisters builds, a pair of their own. */
extern GifQuad p2DirtyGsRegisterGifTag;
extern DmaTag p2DirtyGsRegisterDmaTag;

/*
 * Sends every register marked in p2GsDirtyRegisters, highest index first, at most 16 to a packet, clearing
 * each mark as it goes. The scan finds the highest set bit with the EE's plzcw (leading sign bits of each
 * 32-bit word, less one), which C cannot spell: in the low word first, then in the high word.
 */
void p2UploadDirtyGsRegisters(void) {
    int more;
    int n;
    int reg;
    unsigned __int128 *p;
    unsigned int *packet;
    unsigned __int128 *head;
    GsRegWrite ad;
    long long bits;
    long long zeros;
    int top;
    long long *dirty;
    int bit;
    int base;

    more = 1;
    if (p2CurrentProgram == 0) {
        p2GsRegisterPacketMscal.field.immediate = p2GetVuProgramAddress(p2GsRegisterProgram);
        do {
            n = 0;
            asm {
                la      dirty, p2GsDirtyRegisters
                li      top, 31
            }
            packet = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
            p = (unsigned __int128 *)packet + 3;
            while (n < 16 && more) {
                asm {
                    ld      bits, 0(dirty)
                    plzcw   zeros, bits
                    sub     bit, top, zeros
                    li      base, -1
                    bne     bit, zero, found
                    dsrl32  zeros, zeros, 0
                    sub     bit, top, zeros
                    dmove   base, top
                    beq     bit, zero, none
                found:
                    add     reg, bit, base
                    li      zeros, 1
                    dsllv   zeros, zeros, reg
                    xor     bits, bits, zeros
                    sd      bits, 0(dirty)
                    b       done
                none:
                    and     more, zero, zero
                done:
                }
                if (more) {
                    ad.f.data = ((unsigned long long *)p2CurrentGsRegisters)[reg];
                    ad.f.addr = p2GsRegisterAddresses[reg];
                    n++;
                    *p = ad.q;
                    p++;
                }
            }
            if (n != 0) {
                p2DirtyGsRegisterGifTag.f.nreg = n;
                p2DirtyGsRegisterDmaTag.f.qwc = n + 3;
                p2GsRegisterPacketHead.code[3].field.num = n + 1;
                packet[0] = p2DirtyGsRegisterDmaTag.w[0];
                packet[1] = p2DirtyGsRegisterDmaTag.w[1];
                packet[2] = p2DirtyGsRegisterDmaTag.w[2];
                packet[3] = p2DirtyGsRegisterDmaTag.w[3];
                head = (unsigned __int128 *)packet;
                head++;
                *head++ = p2GsRegisterPacketHead.q;
                *head = p2DirtyGsRegisterGifTag.q;
                *p = p2GsRegisterPacketTail.q;
                p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)(p + 1);
                if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
                    if (p2DisplayListMode != 0) {
                        p2GrowDisplayList();
                    } else {
                        p2SubmitDmaPacket(1);
                    }
                }
            }
        } while (more);
    }
}

void p2FlushGsRegisters(void) {
    if (p2GsDirtyRegisters != 0) {
        p2UploadDirtyGsRegisters();
    }
}

extern DmaTag p2RestartPacketTag;
extern unsigned int p2RestartPacketUnpack;
extern unsigned int p2RestartPacketMark;
extern VifCode p2RestartPacketMscal;
/* A GIF tag as its two doublewords: the tag proper and the register descriptors. */
typedef struct GifTagWords {
    unsigned long long tag;
    unsigned long long regs;
} GifTagWords;

extern GifTagWords p2RestartPacketGifTag;
extern unsigned int p2RestartPacketNop;

/* A packet write position, stepped by words, doublewords or quadwords. */
typedef union p2PacketPointer {
    unsigned int *w;
    unsigned long long *d;
    unsigned __int128 *q;
} p2PacketPointer;

static inline void p2PutWord(unsigned int *dest, unsigned int word) {
    *dest = word;
}

static inline void p2PutGifTag(unsigned __int128 *dest, const GifTagWords *tag) {
    ((unsigned long long *)dest)[0] = tag->tag;
    ((unsigned long long *)dest)[1] = tag->regs;
}

extern DmaTag p2FinishPacketTag;
extern VifCode p2FinishPacketUnpack;
extern VifCode p2FinishPacketMark;
extern VifCode p2FinishPacketMscal;
extern unsigned int p2FinishPacketFlush;
extern GifQuad p2FinishPacketGifTag;
extern unsigned int p2FinishPacketNop;

/* Appends the end-of-packet marker: the VU1 program sets the GS LABEL register to the packet's
 * sequence and writes FINISH, through the GIF (A+D). A DMA tag, the VIF codes ahead of the GIF tag,
 * the GIF tag with its two register writes, then the VIF codes that start the program. */
void p2AppendGsFinish(void) {
    p2PacketPointer p;
    p2PacketPointer q;
    GifQuad tag;

    p.w = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
    tag = p2FinishPacketGifTag;
    p2FinishPacketMscal.field.immediate = p2GetVuProgramAddress(p2GsRegisterProgram);
    tag.f.nreg = 2;
    p2FinishPacketTag.f.qwc = 5;
    p.w[0] = p2FinishPacketTag.w[0];
    p.w[1] = p2FinishPacketTag.w[1];
    p.w[2] = p2FinishPacketTag.w[2];
    p.w[3] = p2FinishPacketTag.w[3];
    p.q++;
    p2FinishPacketMark.field.immediate = 2;
    p2FinishPacketUnpack.field.num = 3;
    p.w[0] = p2FinishPacketFlush;
    p.w[1] = p2FinishPacketNop;
    p.w[2] = p2FinishPacketMark.word;
    p.w[3] = p2FinishPacketUnpack.word;
    p.q++;
    p2PutGifTag(p.q, (GifTagWords *)&tag);
    q.q = p.q + 1;
    *q.d++ = ((unsigned long long *)p2CurrentGsRegisters)[55];
    *q.d++ = 0x62;
    *q.d++ = ((unsigned long long *)p2CurrentGsRegisters)[54];
    *q.d++ = 0x61;
    ((unsigned long long *)p.q)[1] = (~0ULL << 8) | 0xEE;
    p2FinishPacketMark.field.immediate = 3;
    q.w[0] = p2FinishPacketMark.word;
    q.w[1] = p2FinishPacketMscal.word;
    q.w[2] = p2FinishPacketNop;
    q.w[3] = p2FinishPacketFlush;
    p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)(q.w + 4);
}

/* Restarts the VU1 program: a DMA tag, the VIF codes around the program's GIF tag, then an MSCAL of
 * its entry address. */
void p2AppendProgramRestart(void) {
    p2PacketPointer p;

    p.w = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
    p2RestartPacketMscal.field.immediate = p2GetVuProgramAddress(p2GsRegisterProgram);
    p.w[0] = p2RestartPacketTag.w[0];
    p.w[1] = p2RestartPacketTag.w[1];
    p.w[2] = p2RestartPacketTag.w[2];
    p.w[3] = p2RestartPacketTag.w[3];
    p.w += 4;
    p2PutWord(p.w++, p2RestartPacketNop);
    p2PutWord(p.w++, p2RestartPacketNop);
    p2PutWord(p.w++, p2RestartPacketMark);
    p2PutWord(p.w++, p2RestartPacketUnpack);
    p2PutGifTag(p.q++, &p2RestartPacketGifTag);
    p2PutWord(p.w++, p2RestartPacketMscal.word);
    p2PutWord(p.w++, p2RestartPacketNop);
    p2PutWord(p.w++, p2RestartPacketNop);
    p2PutWord(p.w++, p2RestartPacketNop);
    p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)p.w;
}

void p2CallGifChain(unsigned int chain, int unused, int flush) {
    unsigned int *p = (unsigned int *)p2DmaCurrentPacket[P2_DMA_GIF]->cursor;
    p2GifCallTag.f.addr = chain & 0x7FFFFFFF;
    p[0] = p2GifCallTag.w[0];
    p[1] = p2GifCallTag.w[1];
    p[2] = p2GifCallTag.w[2];
    p[3] = p2GifCallTag.w[3];
    p2DmaCurrentPacket[P2_DMA_GIF]->cursor = (unsigned int)(p + 4);
    if (flush != 0) {
        p2SubmitDmaPacket(2);
    } else if (p2DmaCurrentPacket[P2_DMA_GIF]->cursor >= p2DmaCurrentPacket[P2_DMA_GIF]->limit) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(2);
        }
    }
}

extern DmaTag p2GsRegisterGifDmaTag;
extern GifQuad p2GsRegisterGifBatchTag;

/* Writes the GS registers listed in regs, in batches of at most 16, through the GIF channel: a DMA tag
 * and a GIF tag in A+D mode, then each register as its data and address doublewords. The tag's
 * register list names A+D (0xE) for each register sent and NOP (0xF) for the slots above them. */
void p2UploadGsRegistersGif(int count, int *regs, int flush) {
    int n;
    GifQuad tag;
    int i;
    unsigned long long *p;
    unsigned long long *gif;
    long long descriptors;
    long long unused;

    while (count > 0) {
        n = count < 16 ? count : 16;
        p = (unsigned long long *)p2DmaCurrentPacket[P2_DMA_GIF]->cursor;
        tag = p2GsRegisterGifBatchTag;
        descriptors = 0;
        tag.f.nreg = n;
        p2GsRegisterGifDmaTag.f.qwc = n + 1;
        ((unsigned int *)p)[0] = p2GsRegisterGifDmaTag.w[0];
        ((unsigned int *)p)[1] = p2GsRegisterGifDmaTag.w[1];
        ((unsigned int *)p)[2] = p2GsRegisterGifDmaTag.w[2];
        ((unsigned int *)p)[3] = p2GsRegisterGifDmaTag.w[3];
        gif = p + 2;
        p[2] = ((GifTagWords *)&tag)->tag;
        p[3] = ((GifTagWords *)&tag)->regs;
        p += 4;
        for (i = 0; i < n; i++) {
            int reg = regs[i];
            descriptors |= 0xELL << (i * 4);
            p[0] = ((unsigned long long *)p2CurrentGsRegisters)[reg];
            p[1] = p2GsRegisterAddresses[reg];
            p += 2;
        }
        unused = -1;
        unused <<= n * 4;
        descriptors |= unused;
        gif[1] = descriptors;
        p2DmaCurrentPacket[P2_DMA_GIF]->cursor = (unsigned int)p;
        if (flush != 0 && p2DmaCurrentPacket[P2_DMA_GIF]->cursor >= p2DmaCurrentPacket[P2_DMA_GIF]->limit) {
            if (p2DisplayListMode != 0) {
                p2GrowDisplayList();
            } else {
                p2SubmitDmaPacket(2);
            }
        }
        count -= n;
        regs += n;
    }
}

/* Reads one of the Graphics Synthesizer privileged registers by register number. The numbers are
 * the GS register-map indices; the memory-mapped address is 0x12000000 + (index << 4) for the
 * display block and 0x12001000 + ((index - 0x40) << 4) for the status block. An index the function
 * does not serve is reported through printf with the format string "p2readGSPrivRegister(%d)\n"
 * and reads as 0. */
long long p2readGSPrivRegister(int registerIndex) {
    switch (registerIndex) {
    case GSPRIV_PMODE:
        return GS_PMODE;
    case GSPRIV_SMODE2:
        return GS_SMODE2;
    case GSPRIV_DISPFB1:
        return GS_DISPFB1;
    case GSPRIV_DISPLAY1:
        return GS_DISPLAY1;
    case GSPRIV_DISPFB2:
        return GS_DISPFB2;
    case GSPRIV_DISPLAY2:
        return GS_DISPLAY2;
    case GSPRIV_EXTBUF:
        return GS_EXTBUF;
    case GSPRIV_EXTDATA:
        return GS_EXTDATA;
    case GSPRIV_EXTWRITE:
        return GS_EXTWRITE;
    case GSPRIV_BGCOLOR:
        return GS_BGCOLOR;
    case GSPRIV_CSR:
        return GS_CSR;
    case GSPRIV_IMR:
        return GS_IMR;
    case GSPRIV_BUSDIR:
        return GS_BUSDIR;
    case GSPRIV_SIGLBLID:
        return GS_SIGLBLID;
    default:
        printf(text_p2readGSPrivRegister, registerIndex);
        return 0;
    }
}

void p2writeGSPrivRegister(int registerIndex) {
    switch (registerIndex) {
    case 0:
        *(long long *)0x12000000 = *(long long *)0x0056adf0;
        break;
    case 2:
        *(long long *)0x12000020 = *(long long *)0x0056ae10;
        break;
    case 7:
        *(long long *)0x12000070 = *(long long *)0x0056ada8;
        break;
    case 8:
        *(long long *)0x12000080 = *(long long *)0x0056adb8;
        break;
    case 9:
        *(long long *)0x12000090 = *(long long *)0x0056adb0;
        break;
    case 10:
        *(long long *)0x120000a0 = *(long long *)0x0056adc0;
        break;
    case 11:
        *(long long *)0x120000b0 = *(long long *)0x0056adc8;
        break;
    case 12:
        *(long long *)0x120000c0 = *(long long *)0x0056ae20;
        break;
    case 13:
        *(long long *)0x120000d0 = *(long long *)0x0056add8;
        break;
    case 14:
        *(long long *)0x120000e0 = *(long long *)0x0056ad90;
        break;
    case 64:
        *(long long *)0x12001000 = *(long long *)0x0056ada0;
        break;
    case 65:
        *(long long *)0x12001010 = *(long long *)0x0056ade0;
        break;
    case 68:
        *(long long *)0x12001040 = *(long long *)0x0056ad98;
        break;
    case 72:
        *(long long *)0x12001090 = *(long long *)0x0056ae00;
        break;
    }
}

void FUN_001f8320(void) {
    if (p2FirstOpen != 0) {
        p2readGSPrivRegister(0x48);
    }
}

int AddIntcHandler(int cause, int (*handler)(int cause), int next);

void p2InitGsInterrupt(void) {
    VifCode unpack = { 0x8000, 0, 0x6c };
    VifCode nop = { 0 };
    VifCode mark = { 2, 0, 7 };
    VifCode mscal = { 0, 0, 0x14 };
    VifCode flusha = { 0, 0, 0x13 };

    p2GsIntcHandlerId = AddIntcHandler(0, p2GsInterruptHandler, 0);
    if (p2FirstOpen != 0) {
        p2PrintGsRevision();
    }
    EnableIntc(0);
    *(int *)0x10003010 = 4;
    p2FinishedSequence[0] = 0;
    p2GsRegisterPacketHead.code[0].word = nop.word;
    p2GsRegisterPacketHead.code[1].word = nop.word;
    p2GsRegisterPacketHead.code[2].word = mark.word;
    p2GsRegisterPacketHead.code[3].word = unpack.word;
    p2GsRegisterPacketTail.code[0].word = mark.word;
    p2GsRegisterPacketTail.code[1].word = flusha.word;
    p2GsRegisterPacketTail.code[2].word = mscal.word;
    p2GsRegisterPacketTail.code[3].word = flusha.word;
}

void p2InitGsRegisterAddresses(void) {
    *(char *)0x56AE50 = 0;
    *(char *)0x56AE51 = 1;
    *(char *)0x56AE52 = 2;
    *(char *)0x56AE53 = 3;
    *(char *)0x56AE54 = 4;
    *(char *)0x56AE55 = 5;
    *(char *)0x56AE56 = 6;
    *(char *)0x56AE57 = 7;
    *(char *)0x56AE58 = 8;
    *(char *)0x56AE59 = 9;
    *(char *)0x56AE5A = 0xA;
    *(char *)0x56AE5B = 0xC;
    *(char *)0x56AE5C = 0xD;
    *(char *)0x56AE5D = 0x14;
    *(char *)0x56AE5E = 0x15;
    *(char *)0x56AE5F = 0x16;
    *(char *)0x56AE60 = 0x17;
    *(char *)0x56AE61 = 0x18;
    *(char *)0x56AE62 = 0x19;
    *(char *)0x56AE63 = 0x1A;
    *(char *)0x56AE64 = 0x1B;
    *(char *)0x56AE65 = 0x1C;
    *(char *)0x56AE66 = 0x22;
    *(char *)0x56AE67 = 0x34;
    *(char *)0x56AE68 = 0x35;
    *(char *)0x56AE69 = 0x36;
    *(char *)0x56AE6A = 0x37;
    *(char *)0x56AE6B = 0x3B;
    *(char *)0x56AE6C = 0x3D;
    *(char *)0x56AE6E = 0x3F;
    *(char *)0x56AE70 = 0x40;
    *(char *)0x56AE71 = 0x41;
    *(char *)0x56AE72 = 0x42;
    *(char *)0x56AE73 = 0x43;
    *(char *)0x56AE74 = 0x44;
    *(char *)0x56AE75 = 0x45;
    *(char *)0x56AE76 = 0x46;
    *(char *)0x56AE77 = 0x47;
    *(char *)0x56AE78 = 0x48;
    *(char *)0x56AE79 = 0x49;
    *(char *)0x56AE7A = 0x4A;
    *(char *)0x56AE7B = 0x4B;
    *(char *)0x56AE7C = 0x4C;
    *(char *)0x56AE7D = 0x4D;
    *(char *)0x56AE7E = 0x4E;
    *(char *)0x56AE7F = 0x4F;
    *(char *)0x56AE80 = 0x50;
    *(char *)0x56AE81 = 0x51;
    *(char *)0x56AE82 = 0x52;
    *(char *)0x56AE83 = 0x53;
    *(char *)0x56AE84 = 0x54;
    *(char *)0x56AE85 = 0x60;
    *(char *)0x56AE86 = 0x61;
    *(char *)0x56AE87 = 0x62;
    *(char *)0x56AE88 = 0x7F;
}

int p2GetActiveLightCount(void)
{
    return p2ActiveLightCount;
}

int p2GetActivePointLightCount(void)
{
    return p2ActivePointLightCount;
}

void p2SetMaterialSpecularState(int enable) {
    p2MaterialSpecularState = enable;
    p2DirtyFlags |= 0x84;
    p2StatLightingModeSets += 1;
}
