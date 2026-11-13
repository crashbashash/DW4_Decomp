#include "dw4/p2dma.h"
int p2GetTextureBase();
extern long long p2FrameTimeMin[4];
extern long long DAT_00562cc0[4];
extern long long p2StatFourWeightBlendVertices[4];
extern int DAT_005690ac[4];
extern int DAT_005690b0[4];
extern long long DAT_00569148[4];
extern long long DAT_00569150[4];
extern long long DAT_00569158[4];
extern long long DAT_00569160[4];
extern long long DAT_00569168[4];
extern long long DAT_00569170[4];
extern long long DAT_00569178[4];
extern long long DAT_00569180[4];
extern long long DAT_00569188[4];
extern long long DAT_00569248[4];
extern long long p2VertexCount[4];
extern long long p2PrimitiveCount[4];
extern long long DAT_00569260[4];
extern long long DAT_00569268[4];
extern long long DAT_00569270[4];
extern long long DAT_00569278[4];
extern long long DAT_00569280[4];
extern long long DAT_00569288[4];
extern long long DAT_00569290[4];
extern long long DAT_00569298[4];
extern long long DAT_005692a0[4];
extern long long p2StatLightingSwitches[4];
extern long long p2StatMaterialSets[4];
extern long long p2StatLightingModeSets[4];
extern long long p2StatLightSets[4];
extern long long p2StatLightSwitches[4];
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
extern long long DAT_0056bfa0[4];
extern long long p2FramesTimed[4];
extern long long p2FrameTimeTotal[4];
extern long long p2FrameTimeMax[4];
extern long long DAT_0056c068[4];
extern long long DAT_0056c070[4];
extern int DAT_0056c150[4];
extern int DAT_0056c154[4];
extern int DAT_0056c158[4];
extern int p2DmaWaitTime;
extern int p2SwapWaitTime[4];
extern int p2FinishWaitTime[4];
extern int DAT_0056c168[4];
extern int p2SleepTime[4];
typedef struct GsPacketBuffer { char pad0[40]; unsigned int *end; unsigned int pad44; unsigned int *cursor; } GsPacketBuffer;
extern GsPacketBuffer *DAT_00568f04;
extern GsPacketBuffer *DAT_00568f08;
extern unsigned int DAT_00490f50, DAT_00490f54, DAT_00490f58, DAT_00490f5c, DAT_00490f60, DAT_00490f68, DAT_00490f70;
extern unsigned int DAT_00569328;
extern int p2DisplayListMode;
void p2GrowDisplayList(void);
void p2SubmitDmaPacket(int arg);
int printf();
long long p2readGSPrivRegister();
extern int DAT_004e5110[4];
extern long long DAT_0056ae38[4];
void FUN_001f76f0(int count, int *regs);
unsigned short p2GetVuProgramAddress(int);
void FUN_001f7e90(int count, int *regs, int flush);
int FUN_001f78d0();
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

extern DmaTag DAT_00491040;

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

extern int p2CurrentProgram;
extern int DAT_0056ae40;
extern VifCode DAT_0056aeb8;
extern DmaTag DAT_00490f90;
extern GifQuad DAT_00490f80;
extern VifQuad DAT_0056aea0;
extern VifQuad DAT_0056aeb0;
extern unsigned long long *p2CurrentGsRegisters;
extern unsigned char DAT_0056ae50[];

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
extern int DAT_00491278[4];
extern int p2DirtyFlags[4];

void FUN_001f6f50(void *arg0) {
    int sp2C;
    int temp_a1;

    *(long long *)((char *)arg0 + 0) = p2VertexCount[0];
    *(long long *)((char *)arg0 + 8) = p2PrimitiveCount[0];
    *(long long *)((char *)arg0 + 384) = DAT_00569260[0];
    *(long long *)((char *)arg0 + 392) = DAT_00569268[0];
    *(long long *)((char *)arg0 + 16) = DAT_0056c068[0];
    *(long long *)((char *)arg0 + 24) = DAT_0056c070[0];
    p2GetTextureBase((int *)&sp2C);
    sp2C = (0x4000 - sp2C) << 8;
    *(long long *)((char *)arg0 + 200) = DAT_005690ac[0];
    *(long long *)((char *)arg0 + 208) = DAT_005690b0[0];
    *(long long *)((char *)arg0 + 32) = (sp2C - DAT_0056c070[0]);
    *(long long *)((char *)arg0 + 40) = p2FramesTimed[0];
    *(long long *)((char *)arg0 + 48) = DAT_0056bfa0[0];
    *(long long *)((char *)arg0 + 56) = DAT_0056b5a8[0];
    *(long long *)((char *)arg0 + 64) = DAT_0056b5b0[0];
    *(long long *)((char *)arg0 + 72) = DAT_0056b5b8[0];
    *(long long *)((char *)arg0 + 80) = DAT_0056b5c0[0];
    *(long long *)((char *)arg0 + 88) = DAT_0056b5c8[0];
    *(long long *)((char *)arg0 + 96) = DAT_0056b5d0[0];
    *(long long *)((char *)arg0 + 104) = DAT_0056b5d8[0];
    *(long long *)((char *)arg0 + 112) = DAT_0056b5e0[0];
    *(long long *)((char *)arg0 + 120) = DAT_0056b5e8[0];
    *(long long *)((char *)arg0 + 128) = DAT_0056b5f0[0];
    *(long long *)((char *)arg0 + 136) = p2StatLightingSwitches[0];
    *(long long *)((char *)arg0 + 144) = p2StatMaterialSets[0];
    *(long long *)((char *)arg0 + 152) = p2StatLightingModeSets[0];
    *(long long *)((char *)arg0 + 160) = p2StatLightSets[0];
    *(long long *)((char *)arg0 + 168) = p2StatLightSwitches[0];
    *(long long *)((char *)arg0 + 176) = DAT_00569298[0];
    *(long long *)((char *)arg0 + 184) = DAT_005692a0[0];
    *(long long *)((char *)arg0 + 192) = DAT_00562cc0[0];
    *(long long *)((char *)arg0 + 216) = DAT_00569148[0];
    *(long long *)((char *)arg0 + 224) = DAT_00569150[0];
    *(long long *)((char *)arg0 + 232) = DAT_00569158[0];
    *(long long *)((char *)arg0 + 240) = DAT_00569160[0];
    *(long long *)((char *)arg0 + 248) = DAT_00569168[0];
    *(long long *)((char *)arg0 + 256) = DAT_00569170[0];
    *(long long *)((char *)arg0 + 264) = DAT_00569178[0];
    *(long long *)((char *)arg0 + 272) = DAT_00569180[0];
    *(long long *)((char *)arg0 + 280) = DAT_00569188[0];
    *(long long *)((char *)arg0 + 288) = p2FrameTimeTotal[0];
    *(long long *)((char *)arg0 + 296) = p2FrameTimeMin[0];
    *(long long *)((char *)arg0 + 304) = p2FrameTimeMax[0];
    *(long long *)((char *)arg0 + 312) = DAT_0056c150[0];
    *(long long *)((char *)arg0 + 320) = DAT_0056c154[0];
    *(long long *)((char *)arg0 + 328) = DAT_0056c158[0];
    *(long long *)((char *)arg0 + 336) = p2DmaWaitTime;
    *(long long *)((char *)arg0 + 344) = p2SwapWaitTime[0];
    *(long long *)((char *)arg0 + 352) = p2FinishWaitTime[0];
    *(long long *)((char *)arg0 + 360) = DAT_0056c168[0];
    *(long long *)((char *)arg0 + 368) = p2SleepTime[0];
    *(long long *)((char *)arg0 + 400) = DAT_00569270[0];
    *(long long *)((char *)arg0 + 408) = DAT_00569278[0];
    *(long long *)((char *)arg0 + 416) = DAT_00569280[0];
    *(long long *)((char *)arg0 + 424) = DAT_00569288[0];
    *(long long *)((char *)arg0 + 432) = p2StatFourWeightBlendVertices[0];
    *(long long *)((char *)arg0 + 440) = DAT_00569290[0];
    *(long long *)((char *)arg0 + 448) = DAT_00569248[0];
    p2FrameTimeMin[0] = 0xFFFFFFFFLL;
    p2FrameTimeMax[0] = 0;
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
extern p2DmaPacket *p2DmaCurrentPacket[P2_DMA_CHANNEL_COUNT];

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

void FUN_001f7340(int arg0) {
    *(int *)0x569220 = arg0;
    *(int *)0x491478 = (int) (*(int *)0x491478 | 0x11);
}

int FUN_001f7360(void)
{
    return *(int *)0x00569220;
}

void FUN_001f7370(float value) {
    unsigned int *p = DAT_00568f04->cursor;
    p[0] = DAT_00490f50;
    p[1] = DAT_00490f54;
    p[2] = DAT_00490f58;
    p[3] = DAT_00490f5c;
    p[4] = DAT_00490f60;
    p[5] = DAT_00490f70;
    p[6] = 0xFCFCFCFC;
    p[7] = DAT_00569328;
    p[8] = DAT_00490f68;
    ((float *)p)[9] = value;
    p[10] = DAT_00569328;
    p[11] = DAT_00569328;
    DAT_00568f04->cursor = p + 12;
    if (DAT_00568f04->cursor >= DAT_00568f04->end) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(1);
        }
    }
}

void FUN_001f7470(int arg0) {
    *(int *)0x490D38 = arg0;
    *(int *)0x491478 = (int) (*(int *)0x491478 | 0x19);
}

void FUN_001f7490(void) {
    long long temp_v0;
    int a, b;
    temp_v0 = p2readGSPrivRegister(0x40);
    a = (temp_v0 >> 0x18) & 0xFF;
    b = (temp_v0 >> 0x10) & 0xFF;
    printf(&DAT_004e5110[0], a, b);
}

int FUN_001f74e0(long long t)
{
    return DAT_0056ae38[0] >= t;
}

void FUN_001f7500(void *arg0) {
    long long temp_a0;

    temp_a0 = *(long long *)((char *)(arg0) + 8);
    if (DAT_0056ae38[0] < temp_a0) {
        DAT_0056ae38[0] = temp_a0;
    }
}

void FUN_001f8190(int registerIndex);
void p2FinishHandler(void);
void p2VsyncHandler(void);
void p2GsSignalHandler(void);

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

extern tGS_CSR DAT_0056ada0;
extern long long DAT_0056ade0;
extern int DAT_0056ae90;
extern int p2DisplayClosing;
extern int DAT_0056ae30;
extern int DAT_0056ae28;

int FUN_001f7530(int cause) {
    long long status;

    DAT_0056ade0 = -1;
    FUN_001f8190(0x41);
    status = p2readGSPrivRegister(0x40);
    DAT_0056ae90++;
    DAT_0056ada0.FINISH = (status & 2) ? 1 : 0;
    DAT_0056ada0.VSINT = (status & 8) ? 1 : 0;
    DAT_0056ada0.SIGNAL = (status & 1) ? 1 : 0;
    FUN_001f8190(0x40);
    if (p2DisplayClosing == 0) {
        if (status & 2) {
            p2FinishHandler();
        }
        if (status & 8) {
            p2VsyncHandler();
            DAT_0056ae30++;
        }
        if (status & 1) {
            p2GsSignalHandler();
            DAT_0056ae28++;
        }
    }
    DAT_0056ade0 = -0xB01;
    FUN_001f8190(0x41);
    __asm__ __volatile__("sync\nei\n");
    return 0;
}

void p2SendGsRegister(int arg0) {
    int sp1C;

    sp1C = arg0;
    FUN_001f76f0(1, &sp1C);
}

void FUN_001f76f0(int count, int *regs) {
    int n;

    if (p2CurrentProgram == 0) {
        DAT_0056aeb8.field.immediate = p2GetVuProgramAddress(DAT_0056ae40);
        for (; count > 0; count -= n, regs += n) {
            int i;
            unsigned __int128 *p;
            int *r;
            GsRegWrite ad;

            n = count < 16 ? count : 16;
            p = (unsigned __int128 *)DAT_00568f04->cursor;
            r = regs;
            DAT_00490f80.f.nreg = n;
            DAT_00490f90.f.qwc = n + 3;
            ((unsigned int *)p)[0] = DAT_00490f90.w[0];
            ((unsigned int *)p)[1] = DAT_00490f90.w[1];
            ((unsigned int *)p)[2] = DAT_00490f90.w[2];
            ((unsigned int *)p)[3] = DAT_00490f90.w[3];
            DAT_0056aea0.code[3].field.num = n + 1;
            p[1] = DAT_0056aea0.q;
            *(p += 2) = DAT_00490f80.q;
            p++;
            for (i = 0; i < n; i++) {
                int reg = *r++;
                ad.f.data = p2CurrentGsRegisters[reg];
                ad.f.addr = DAT_0056ae50[reg];
                *p = ad.q;
                p++;
            }
            *p = DAT_0056aeb0.q;
            DAT_00568f04->cursor = (unsigned int *)(p + 1);
            if (DAT_00568f04->cursor >= DAT_00568f04->end) {
                if (p2DisplayListMode != 0) {
                    p2GrowDisplayList();
                } else {
                    p2SubmitDmaPacket(1);
                }
            }
        }
    } else {
        FUN_001f7e90(count, regs, 1);
    }
}

void p2FlushGsRegisters(void) {
    if (*(long long *)0x56AE48 != 0) {
        FUN_001f78d0();
    }
}


extern unsigned int DAT_00491000, DAT_00491004, DAT_00491008, DAT_0049100c, DAT_00491010, DAT_00491018;
extern VifCode DAT_00491020;
extern unsigned long long DAT_00491030, DAT_00491038;
extern unsigned int DAT_0056aec8;


void FUN_001f7db0(unsigned int addr, int unused, int flush) {
    unsigned int *p = DAT_00568f08->cursor;
    DAT_00491040.f.addr = addr & 0x7FFFFFFF;
    p[0] = DAT_00491040.w[0];
    p[1] = DAT_00491040.w[1];
    p[2] = DAT_00491040.w[2];
    p[3] = DAT_00491040.w[3];
    DAT_00568f08->cursor = p + 4;
    if (flush != 0) {
        p2SubmitDmaPacket(2);
    } else if (DAT_00568f08->cursor >= DAT_00568f08->end) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(2);
        }
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

void FUN_001f8190(int arg0) {
    switch (arg0) {
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
    if (*(int *)0x490B60 != 0) {
        p2readGSPrivRegister(0x48);
    }
}

void FUN_001f8490(void) {
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

int FUN_001f8730(void)
{
    return *(int *)0x0056aef0;
}

int FUN_001f8740(void)
{
    return *(int *)0x0056aef8;
}

void FUN_001f8750(int arg0) {
    DAT_00491278[0] = arg0;
    p2DirtyFlags[0] |= 0x84;
    p2StatLightingModeSets[0] += 1;
}
