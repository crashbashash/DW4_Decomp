/* p2core.c - the p2 renderer's state, VU program table, display and display lists.
 *
 * The renderer keeps one image of the GS drawing registers per render program and marks each
 * register it changes in p2GsDirtyRegisters; the next draw sends the marked ones. Program 0 draws
 * in GS context 1, every other program in context 2, and with multipass rendering context 2
 * follows what program 0 sets. A program's capability bits in p2ProgramFlags switch its features
 * (fog, lighting, vertex blending, fixed-point vertex data) on and off.
 *
 * The VU1 microcode is a table of named programs, loaded into VU memory on demand. Opening the
 * display sets up the GS, the VU program table and the pools; closing it takes them down again.
 * A display list records the VIF1 data of a run of draws into chained heap blocks, which a later
 * frame calls with a DMA call tag instead of building the data again. */
#include "dw4/p2dma.h"
#include "dw4/p2core.h"

#define P2_CAPABILITY_COUNT 28
#define P2_VU_PROGRAM_COUNT 384
#define P2_COMPONENT_COUNT 5
#define P2_DISPLAY_LIST_BLOCK_SIZE 0x8000
#define P2_DISPLAY_LIST_RESERVE 0x1400

/* p2VuProgram.flags */
enum {
    P2_VU_PROGRAM_VU1 = 0x1,
    P2_VU_PROGRAM_ALIAS = 0x2,
    P2_VU_PROGRAM_RESIDENT = 0x4
};

/* p2VuProgram.state */
enum {
    P2_VU_PROGRAM_LOADED = 0x1
};

enum {
    P2_PRIM_SPRITE = 6,
    P2_ZTST_ALWAYS = 1,
    P2_GS_REG_TEX0_2 = 0x07,
    P2_POOL_IMAGE = 3,
    P2_POOL_DISPLAY_LIST = 0xD,
    P2_HEAP_VU = 6,
    P2_HEAP_DISPLAY_LIST = 0xB,
    P2_PSM_CT32 = 0,
    P2_PSM_CT24 = 1,
    P2_PSM_CT16 = 2,
    P2_PSM_CT16S = 10,
    P2_DISPLAY_LIST_PATCH_KEY = 0x1234
};

/* The INTC causes the display installs handlers on. */
enum {
    P2_INTC_GS = 0,
    P2_INTC_VBLANK_START = 2,
    P2_INTC_VIF1 = 5
};

/* A VIF code word. */
typedef union p2VifCode {
    struct {
        unsigned short immediate;
        unsigned char num;
        unsigned char command : 7;
        unsigned char interrupt : 1;
    } field;
    unsigned int word;
} p2VifCode;

/* A DMA tag that sends the quadwords after it, and the VIF codes it carries. */
typedef struct p2DmaTagWords {
    unsigned int word[4];
} p2DmaTagWords;

/* A DMA tag whose address field follows the next quadword. */
typedef union p2DmaChainTag {
    unsigned int word[4];
    struct {
        unsigned short qwc;
        unsigned short id;
        unsigned int addr : 31;
        unsigned int spr : 1;
    } field;
} p2DmaChainTag;

/* The fog constants' packet: tag, flush, then an UNPACK of three words to VU1. */
typedef struct p2FogUploadTemplate {
    p2DmaTagWords tag;
    unsigned int unpack;
    unsigned int f20;
    unsigned int flush;
} p2FogUploadTemplate;

/* The packets of the colour scaler and the component scales: tag, flush, UNPACK of a quadword. */
typedef struct p2VectorUploadTemplate {
    p2DmaTagWords tag;
    unsigned int flush;
    unsigned int f20;
    p2VifCode unpack;
} p2VectorUploadTemplate;

/* How one vertex component is stored: fixed point with this many integer and fraction bits,
 * or float when both are zero. */
typedef struct p2ComponentLayout {
    unsigned short isSigned : 1;
    unsigned short fractionBits : 15;
    unsigned short integerBits : 15;
    unsigned short : 1;
} p2ComponentLayout;

enum p2Component {
    P2_COMPONENT_POSITION,
    P2_COMPONENT_NORMAL,
    P2_COMPONENT_TEXCOORD,
    P2_COMPONENT_BLEND_WEIGHT,
    P2_COMPONENT_SPRITE_SIZE
};

/* A VU program: the microcode the symbol table names, where it sits in VU memory once loaded. */
typedef struct p2VuProgram {
    long long key;                /* which variant of a program this is */
    int size;
    int state;
    int index;
    unsigned int code;            /* the microcode in the VU1 symbol image */
    struct p2VuProgram *alias;
    int reserved;
    int address;
    int listValue;                /* the program list's value beside key and flags; nothing reads it */
    unsigned int flags;           /* P2_VU_PROGRAM_*; the slot in the high half */
    char *name;
    int reservedWords[4];
} p2VuProgram;

/* An image the renderer created for the visual context: a texture node of the image pool. */
typedef struct p2Texture {
    char pad0[44];
    struct p2Image *owner;
} p2Texture;

typedef struct p2Image {
    int f0;
    struct p2Image *next;
    void *pixels;
    p2Texture *texture;
    signed char format : 2;
    signed char order : 4;
    short layout : 4;
} p2Image;

/* A palette the texture code binds with its texture. */
typedef struct p2ClutImage {
    char pad0[56];
    int address;
} p2ClutImage;

typedef struct p2Clut {
    char pad0[12];
    p2ClutImage *image;
    int : 2;
    int storageMode : 4;
    int format : 4;
} p2Clut;

/* Each program's texturing: its texture function, two bits a program, and whether it maps
 * textures, a bit a program. */
typedef struct p2ProgramTextureState {
    unsigned int functions;
    unsigned short enabled;
} p2ProgramTextureState;

/* A program's blend equation, kept as its ALPHA register packs it. */
typedef struct p2BlendEquation {
    unsigned short a : 2;
    unsigned short b : 2;
    unsigned short c : 2;
    unsigned short d : 2;
    unsigned short fix : 8;
} p2BlendEquation;

int memcpy();
int memset();
int printf();
int strcmp();
int strcpy();
int strlen();
int DeleteThread();
int RemoveDmacHandler();
int RemoveIntcHandler();
int TerminateThread();
int FUN_0010b9c0();
int FUN_0010ba90();
int FUN_001f76f0();
int FUN_00202300();
int FUN_00203500();
int p2GrowPool();
int p2FreePool();
int p2InvalidateStateCache();
int p2BuildDisplayPacket();
int p2NewFinishSequence();
int p2WaitFinishSequence();
int FUN_00208200();
int p2ShutdownTimer();
int p2OpenVu1Symbols();
int p2CloseVu1Symbols();
int FUN_00330730();
int FUN_00330770();
char *FUN_003307b0(unsigned int data, int size, int heap);
p2Texture *p2LoadTexture(void *pixels, int width, int height, int psm, int flags);
void FUN_001fcb00(void);
void p2SendGsRegister(int reg);
void p2EnableLighting(void);
void p2DisableLighting(void);
void p2CopyContext1ToContext2(void);
void p2SubmitDmaPacket(int channel);
void p2WaitDmaSequence(int channel, long long sequence);
void p2ShutdownDmaChannels(void);

void p2SetCapability(int capability, int on);
void p2UploadFog(void);
void p2SoftwareBlendOneWeight(int count, float *out);
void p2SoftwareBlendTwoWeights(int count, float *out);
void p2SoftwareBlendThreeWeights(int count, float *out);
void p2SoftwareBlendFourWeights(int count, float *out);
void p2SoftwareBlendWeights(int count, int weights, float *out);
void p2DrawClearSprites(int width, int height, int depth);
int p2LoadVuProgram(int program);
void p2ParseVuProgramList(const char *list);
int p2GetDisplayFlags(void);
void p2GrowDisplayList(void);
p2DisplayList *p2AllocDisplayList(void);
void p2FreeDisplayListBlock(p2DisplayList *list);

extern int p2CurrentPrimitive;

extern char p2DepthTestEnabled[P2_PROGRAM_COUNT];
extern char p2DepthFunction[P2_PROGRAM_COUNT];
extern char p2DepthWriteDisabled[P2_PROGRAM_COUNT];
extern p2BlendEquation p2BlendEquations[P2_PROGRAM_COUNT];
extern long long p2StatCapabilityChanges;
extern p2ProgramTextureState p2ProgramTexture;
extern int p2ColorScalerState;
extern int p2FogMode;
extern float p2FogScale;
extern float p2FogOffset;
extern float p2FogEnable;
extern p2FogUploadTemplate p2FogUpload;
extern unsigned int p2FogUploadNop;
extern p2VectorUploadTemplate p2ColorScalerUpload;
extern unsigned int p2ColorScalerUploadNop;
extern p2VectorUploadTemplate p2ComponentScaleUpload;
extern unsigned int p2ComponentScaleUploadNop;

extern const float *p2BlendPositions;
extern const float *p2BlendMatrices;
extern const void *p2BlendWeights;
extern const unsigned char *p2BlendIndices;
extern int p2BlendIndexStride;
extern long long p2StatFourWeightBlendVertices;
extern int p2BlendWeightCount;
extern int p2BlendWeightLimit;
extern int p2BlendMatrixBase;
extern int p2BlendMatrixCount;
extern const void *p2BlendIndexArray;
extern const void *p2BlendWeightArray;

extern int p2ClearWidth;
extern int p2ClearPasses;
extern int p2ClearPass;
extern int p2ClearRegisters[8];

extern int p2ImagePoolSize;
extern p2Image *p2ImagePool;
extern int p2VuMemoryUsed[2];
extern int p2VuMemorySize[2];
extern p2VuProgram p2VuPrograms[P2_VU_PROGRAM_COUNT];
extern int p2VuProgramLast;
extern char p2VuProgramList[];
extern int p2VuMicrocode;
extern p2ComponentLayout p2ComponentLayouts[P2_COMPONENT_COUNT];
extern int p2VertexFormat;
extern int p2DrawPipeline;
extern int p2ConstantColour;
extern long long p2VertexCount;
extern long long p2PrimitiveCount;

extern int p2FirstOpen;
extern int p2WatchdogEnabled;
extern int p2DisplayFrameCount;
extern int p2DisplayClosing;
extern int p2RequestedFrameMode;
extern int p2GsIntcHandlerId;
extern int p2VblankStartIntcHandlerId;
extern int p2Vif1IntcHandlerId;
extern int p2WatchdogThread;
extern int p2DmaHandlerIds[P2_DMA_CHANNEL_COUNT];

extern p2DmaPacket *p2DmaCurrentPacket[P2_DMA_CHANNEL_COUNT];
extern int p2DisplayListMode;
extern p2DisplayList *p2DisplayListPool;
extern p2DmaPacket *p2SavedVif1Packet;
extern p2DmaPacket p2DisplayListPacket;
extern p2DisplayList *p2RecordingBlock;
extern p2DisplayList *p2RecordingList;
extern p2DmaChainTag p2DisplayListReturnTag;
extern p2DmaChainTag p2DisplayListNextTag;
extern unsigned int p2TexturePatchMarker;

/* Writing past the limit of the current VIF1 packet hands it over: while a display list is
 * recorded the list grows a block instead. */
static inline void p2EndVif1Write(void) {
    if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(P2_DMA_VIF1);
        }
    }
}

/* Switches a capability of the current program on; the switch runs only on a change. */
void p2EnableCapability(int capability) {
    int bit = 1 << capability;
    unsigned int *flags = &p2ProgramFlags[p2CurrentProgram];
    if (!(bit & *flags)) {
        *flags |= bit;
        p2SetCapability(capability, 1);
    }
}

void p2DisableCapability(int capability) {
    int bit = 1 << capability;
    unsigned int *flags = &p2ProgramFlags[p2CurrentProgram];
    if (bit & *flags) {
        *flags &= ~bit;
        p2SetCapability(capability, 0);
    }
}

int p2IsCapabilityEnabled(int capability) {
    int program = p2CurrentProgram;
    int bit = 1 << capability;
    return (bit & p2ProgramFlags[program]) != 0;
}

/* Sends the depth test and depth write of the current program's context; with the test off the
 * GS still needs ZTE set, so it passes every pixel and writes nothing. */
static void p2UpdateDepthTest(void) {
    if (p2CurrentProgram == 0) {
        if (p2DepthTestEnabled[0] != 0) {
            p2CurrentGsRegisters->test[0].field.zte = 1;
            p2CurrentGsRegisters->test[0].field.ztst = p2DepthFunction[0];
            p2CurrentGsRegisters->zbuf[0].field.zmsk = p2DepthWriteDisabled[0];
        } else {
            p2CurrentGsRegisters->test[0].field.zte = 1;
            p2CurrentGsRegisters->test[0].field.ztst = P2_ZTST_ALWAYS;
            p2CurrentGsRegisters->zbuf[0].field.zmsk = 1;
        }
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_1) | P2_GS_BIT(P2_GS_ZBUF_1);
        if (p2ExtraPassCount != 0) {
            p2CurrentGsRegisters->test[1].field.zte = p2CurrentGsRegisters->test[0].field.zte;
            p2CurrentGsRegisters->test[1].field.ztst = p2CurrentGsRegisters->test[0].field.ztst;
            p2CurrentGsRegisters->zbuf[1].field.zmsk = p2CurrentGsRegisters->zbuf[0].field.zmsk;
            p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
            p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_2) | P2_GS_BIT(P2_GS_ZBUF_2);
        }
    } else {
        if (p2DepthTestEnabled[1] != 0) {
            p2CurrentGsRegisters->test[1].field.zte = 1;
            p2CurrentGsRegisters->test[1].field.ztst = p2DepthFunction[1];
            p2CurrentGsRegisters->zbuf[1].field.zmsk = p2DepthWriteDisabled[1];
        } else {
            p2CurrentGsRegisters->test[1].field.zte = 1;
            p2CurrentGsRegisters->test[1].field.ztst = P2_ZTST_ALWAYS;
            p2CurrentGsRegisters->zbuf[1].field.zmsk = 1;
        }
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_2) | P2_GS_BIT(P2_GS_ZBUF_2);
    }
}

/* Switches every capability of every program off. Program 0 and program 1 share register set
 * 0; program n above 1 uses set n - 1. */
void p2InitCapabilities(void) {
    int program;
    int capability;
    int set;

    for (program = 0; program < P2_PROGRAM_COUNT; program++) {
        set = 0;
        if (program > 1) {
            set = program - 1;
        }
        p2CurrentProgram = program;
        p2CurrentGsRegisters = &p2GsRegisterSets[set];
        for (capability = 0; capability < P2_CAPABILITY_COUNT; capability++) {
            p2SetCapability(capability, 0);
        }
        p2ProgramFlags[program] = 0;
    }
    p2CurrentProgram = 0;
    p2CurrentGsRegisters = &p2GsRegisterSets[0];
}

/* Switches a capability of the current program; the next draw sends what the switch marks. */
void p2SetCapability(int capability, int on) {
    int bit;

    p2StatCapabilityChanges++;
    switch (capability) {
    case 0:
        p2DepthTestEnabled[p2CurrentProgram] = on;
        p2UpdateDepthTest();
        break;
    case 1:
        if (p2CurrentProgram == 0) {
            p2CurrentGsRegisters->prmode.field.tme = on;
            p2DirtyFlags |= 0x51;
            p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_PRMODE);
        }
        bit = 1 << p2CurrentProgram;
        if (on) {
            p2ProgramTexture.enabled |= bit;
        } else {
            p2ProgramTexture.enabled &= ~bit;
        }
        break;
    case 2:
        p2CurrentGsRegisters->prmode.field.abe = on;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_PRMODE);
        if (p2CurrentProgram != 0) {
            p2DirtyFlags |= 0x111;
        }
        break;
    case 3:
        if (p2CurrentProgram == 0) {
            p2CurrentGsRegisters->test[0].field.ate = on;
            p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
            p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_1);
            if (p2ExtraPassCount != 0) {
                p2CurrentGsRegisters->test[1].field.ate = on;
                p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
                p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_2);
            }
        } else {
            p2CurrentGsRegisters->test[1].field.ate = on;
            p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
            p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_2);
        }
        break;
    case 4:
        if (p2CurrentProgram == 0) {
            p2CurrentGsRegisters->test[0].field.date = on;
            p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
            p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_1);
            if (p2ExtraPassCount != 0) {
                p2CurrentGsRegisters->test[1].field.date = on;
                p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
                p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_2);
            }
        } else {
            p2CurrentGsRegisters->test[1].field.date = on;
            p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
            p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_2);
        }
        break;
    case 5:
        p2CurrentGsRegisters->prmode.field.aa1 = on;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_PRMODE);
        break;
    case 7:
        p2CurrentGsRegisters->prmode.field.fge = on;
        p2DirtyFlags |= 0x51;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_PRMODE);
        if (on) {
            p2FogEnable = 1.0f;
        } else {
            p2FogEnable = 0.0f;
        }
        p2UploadFog();
        break;
    case 11:
        p2CurrentGsRegisters->dthe.field.on = on;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_DTHE);
        break;
    case 13:
        p2DirtyFlags |= 0x11;
        break;
    case 14:
        p2DirtyFlags |= 0x11;
        break;
    case 12:
        p2DirtyFlags |= 0x4;
        break;
    case 16:
        p2DirtyFlags |= 0x11;
        break;
    case 15:
        p2DirtyFlags |= 0x11;
        break;
    case 17:
        p2CurrentGsRegisters->prmode.field.iip = on;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_PRMODE);
        break;
    case 8:
        if (on) {
            p2EnableLighting();
        } else {
            p2DisableLighting();
        }
        if ((p2ProgramFlags[p2CurrentProgram] >> P2_CAP_VERTEX_BLEND) & 1) {
            p2DirtyFlags |= 0x20;
        }
        break;
    case 10:
        p2DirtyFlags |= 0x11;
        if (p2CurrentProgram != 0) {
            p2DirtyFlags |= 0x100;
        }
        break;
    case 6:
        p2DirtyFlags |= 0x11;
        break;
    case 18:
        p2DirtyFlags |= 0x11;
        break;
    case 19:
        p2DirtyFlags |= 0x11;
        break;
    case 20:
        p2DirtyFlags |= 0x4;
        break;
    case P2_CAP_VERTEX_BLEND:
        p2DirtyFlags |= 0x31;
        if (((p2ProgramFlags[p2CurrentProgram] >> P2_CAP_LIGHTING) & 1) && !on) {
            p2DirtyFlags |= 0x4;
        }
        break;
    case 25:
        p2DirtyFlags |= 0x11;
        break;
    case 22:
        p2DirtyFlags |= 0x91;
        if (!on) {
            unsigned int flags = p2ProgramFlags[p2CurrentProgram];
            if ((flags >> P2_CAP_LIGHTING) & 1) {
                p2DirtyFlags |= 0x4;
            }
            if ((flags >> P2_CAP_VERTEX_BLEND) & 1) {
                p2DirtyFlags |= 0x20;
            }
        }
        break;
    case 23:
        if (on) {
            p2CopyContext1ToContext2();
            p2DirtyFlags |= 0x100;
            p2CurrentGsRegisters->prmodecont.field.on = 1;
            p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
            p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_PRMODECONT);
        } else {
            p2CurrentGsRegisters->prmodecont.field.on = 0;
            p2SendGsRegister(P2_GS_PRMODECONT);
            p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
            p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_PRMODE);
        }
        p2DirtyFlags |= 0x91;
        break;
    case 26:
        p2DirtyFlags |= 0x1;
        break;
    case 27:
        p2DirtyFlags |= 0x11;
        break;
    }
}

void p2SetDepthFunction(int function, int writeDisabled) {
    int program = p2CurrentProgram;
    p2DepthFunction[program] = function;
    p2DepthWriteDisabled[program] = writeDisabled;
    p2UpdateDepthTest();
}

/* Sets the GS blend equation of the current program, (A - B) * C >> 7 + D, and keeps it packed
 * as the program's ALPHA image. */
void p2SetBlendEquation(int a, int b, int c, int d, int fix) {
    *(unsigned short *)&p2BlendEquations[p2CurrentProgram] = a | (b << 2) | (c << 4) | (d << 6) | (fix << 8);
    if (p2CurrentProgram == 0) {
        p2CurrentGsRegisters->alpha[0].field.a = a;
        p2CurrentGsRegisters->alpha[0].field.b = b;
        p2CurrentGsRegisters->alpha[0].field.c = c;
        p2CurrentGsRegisters->alpha[0].field.d = d;
        p2CurrentGsRegisters->alpha[0].field.fix = fix;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_ALPHA_1);
    } else {
        p2CurrentGsRegisters->alpha[1].field.a = a;
        p2CurrentGsRegisters->alpha[1].field.b = b;
        p2CurrentGsRegisters->alpha[1].field.c = c;
        p2CurrentGsRegisters->alpha[1].field.d = d;
        p2CurrentGsRegisters->alpha[1].field.fix = fix;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_ALPHA_2);
    }
}

void p2SetFrameBufferAlpha(int on) {
    int value;
    long long dirty;

    if (p2CurrentProgram == 0) {
        value = on;
        p2CurrentGsRegisters->fba[0].field.on = value;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_FBA_1);
        if (p2ExtraPassCount != 0) {
            p2CurrentGsRegisters->fba[1].field.on = value;
            p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
            dirty = p2GsDirtyRegisters | P2_GS_BIT(P2_GS_FBA_2);
            p2GsDirtyRegisters = dirty;
        }
    } else {
        p2CurrentGsRegisters->fba[1].field.on = on;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        dirty = p2GsDirtyRegisters | P2_GS_BIT(P2_GS_FBA_2);
        p2GsDirtyRegisters = dirty;
    }
}

void p2SetPixelAlphaBlend(int on) {
    p2CurrentGsRegisters->pabe.field.on = on;
    p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
    p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_PABE);
}

void p2SetAlphaTest(int method, int reference, int fail) {
    long long dirty;

    if (p2CurrentProgram == 0) {
        p2CurrentGsRegisters->test[0].field.atst = method;
        p2CurrentGsRegisters->test[0].field.aref = reference;
        p2CurrentGsRegisters->test[0].field.afail = fail;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_1);
        if (p2ExtraPassCount != 0) {
            p2CurrentGsRegisters->test[1].field.atst = method;
            p2CurrentGsRegisters->test[1].field.aref = reference;
            p2CurrentGsRegisters->test[1].field.afail = fail;
            p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
            dirty = p2GsDirtyRegisters | P2_GS_BIT(P2_GS_TEST_2);
            p2GsDirtyRegisters = dirty;
        }
    } else {
        p2CurrentGsRegisters->test[1].field.atst = method;
        p2CurrentGsRegisters->test[1].field.aref = reference;
        p2CurrentGsRegisters->test[1].field.afail = fail;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        dirty = p2GsDirtyRegisters | P2_GS_BIT(P2_GS_TEST_2);
        p2GsDirtyRegisters = dirty;
    }
}

void p2SetDestinationAlphaMode(int mode) {
    if (p2CurrentProgram == 0) {
        p2CurrentGsRegisters->test[0].field.datm = mode;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_1);
        if (p2ExtraPassCount != 0) {
            p2CurrentGsRegisters->test[1].field.datm = mode;
            p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
            p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_2);
        }
    } else {
        p2CurrentGsRegisters->test[1].field.datm = mode;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEST_2);
    }
}

void p2SetFogColour(float r, float g, float b) {
    p2CurrentGsRegisters->fogcol.field.fcr = (unsigned int)(255.0f * r);
    p2CurrentGsRegisters->fogcol.field.fcg = (unsigned int)(255.0f * g);
    p2CurrentGsRegisters->fogcol.field.fcb = (unsigned int)(255.0f * b);
    p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
    p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_FOGCOL);
}

/* Sends the fog scale, offset and enable to the VU1 constants the fog programs read. */
void p2UploadFog(void) {
    unsigned int *p = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;

    p[0] = p2FogUpload.tag.word[0];
    p[1] = p2FogUpload.tag.word[1];
    p[2] = p2FogUpload.tag.word[2];
    p[3] = p2FogUpload.tag.word[3];
    p[4] = p2FogUpload.flush;
    p[5] = p2FogUploadNop;
    p[6] = p2FogUploadNop;
    p[7] = p2FogUploadNop;
    p[8] = p2FogUpload.unpack;
    ((float *)p)[9] = p2FogScale;
    ((float *)p)[10] = p2FogOffset;
    ((float *)p)[11] = p2FogEnable;
    p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)(p + 12);
    p2EndVif1Write();
}

/* Linear fog (mode 0) runs from 255 at start to 0 at end; modes 1 and 2 take the density. */
void p2SetFog(int mode, float start, float end, float density) {
    float scale;

    if (p2FogMode != mode) {
        p2FogMode = mode;
        p2DirtyFlags |= 1;
    }
    switch (mode) {
    case 0:
        scale = -255.0f / (end - start);
        p2FogScale = scale;
        p2FogOffset = 255.0f - (scale * start);
        break;
    case 1:
    case 2:
        p2FogScale = density;
        p2FogOffset = density;
        break;
    case 3:
        break;
    }
    p2UploadFog();
}

void p2SetDitherMatrix(long long matrix) {
    p2CurrentGsRegisters->dimx = matrix;
    p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
    p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_DIMX);
}

void p2SetColourClamp(int on) {
    p2CurrentGsRegisters->colclamp.field.on = on;
    p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
    p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_COLCLAMP);
}

/* Sends the colour scaler's four factors to VU1 when it is on, and records its state. */
int p2SetColorScaler(int state, const float *value) {
    unsigned int *p;

    if (state != 0) {
        p = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
        p[0] = p2ColorScalerUpload.tag.word[0];
        p[1] = p2ColorScalerUpload.tag.word[1];
        p[2] = p2ColorScalerUpload.tag.word[2];
        p[3] = p2ColorScalerUpload.tag.word[3];
        p[4] = p2ColorScalerUpload.flush;
        p[5] = p2ColorScalerUploadNop;
        p[6] = p2ColorScalerUploadNop;
        p[7] = p2ColorScalerUpload.unpack.word;
        ((float *)p)[8] = value[0];
        ((float *)p)[9] = value[1];
        ((float *)p)[10] = value[2];
        ((float *)p)[11] = value[3];
        p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)(p + 12);
        p2EndVif1Write();
    }
    p2ColorScalerState = state;
    p2DirtyFlags |= 0x11;
    return 1;
}

/* Sets the scissor rectangle in GL terms (origin at the bottom left) for the current program's
 * context, clamped to the buffer drawn into. In field rendering the buffer is half height. */
void p2SetScissor(int x, int y, int width, int height) {
    int top;
    int right;
    int bottom;
    int limit;
    int antialias;
    int bufferHeight;

    antialias = (p2GetDisplayFlags() & P2_DISPLAY_ANTIALIAS) != 0;
    if (p2Display.frameMode == 0 && p2Display.interlaced > 0 && p2Display.renderTarget == -1) {
        y = y / 2;
        height = height / 2;
    }
    if (p2Display.renderTarget < 0) {
        bufferHeight = antialias != 0 ? p2Display.antialiasHeight : p2Display.height;
    } else {
        bufferHeight = FUN_00208200(p2Display.renderTarget);
    }
    bottom = bufferHeight - y - 1;
    right = x + width - 1;
    top = bottom - height + 1;
    if (top < 0) top = 0;
    if (bottom < 0) bottom = 0;
    if (x < 0) x = 0;
    if (right < 0) right = 0;
    limit = antialias != 0 ? p2Display.antialiasWidth : p2Display.width;
    if (right >= limit) {
        limit = antialias != 0 ? p2Display.antialiasWidth : p2Display.width;
        right = limit - 1;
    }
    if (p2CurrentProgram == 0) {
        p2CurrentGsRegisters->scissor[0].field.scay1 = bottom;
        p2CurrentGsRegisters->scissor[0].field.scay0 = top;
        p2CurrentGsRegisters->scissor[0].field.scax1 = right;
        p2CurrentGsRegisters->scissor[0].field.scax0 = x;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_SCISSOR_1);
        if (p2ExtraPassCount != 0) {
            p2CurrentGsRegisters->scissor[1].field.scay1 = bottom;
            p2CurrentGsRegisters->scissor[1].field.scay0 = top;
            p2CurrentGsRegisters->scissor[1].field.scax1 = right;
            p2CurrentGsRegisters->scissor[1].field.scax0 = x;
            p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
            p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_SCISSOR_2);
        }
    } else {
        p2CurrentGsRegisters->scissor[1].field.scay1 = bottom;
        p2CurrentGsRegisters->scissor[1].field.scay0 = top;
        p2CurrentGsRegisters->scissor[1].field.scax1 = right;
        p2CurrentGsRegisters->scissor[1].field.scax0 = x;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_SCISSOR_2);
    }
}

/* The inputs of the CPU vertex blend, used when the VU1 cannot blend the array itself. */
void p2SetSoftwareBlendSource(const float *positions, const float *matrices, const void *weights,
                              const unsigned char *indices, int indexStride) {
    p2BlendPositions = positions;
    p2BlendMatrices = matrices;
    p2BlendWeights = weights;
    p2BlendIndices = indices;
    p2BlendIndexStride = indexStride;
}

int p2SoftwareBlend(int count, int weights, float *out) {
    if (weights == 4) {
        p2StatFourWeightBlendVertices += count;
    }
    switch (weights) {
    case 1:
        p2SoftwareBlendOneWeight(count, out);
        break;
    case 2:
        p2SoftwareBlendTwoWeights(count, out);
        break;
    case 3:
        p2SoftwareBlendThreeWeights(count, out);
        break;
    case 4:
        p2SoftwareBlendFourWeights(count, out);
        break;
    default:
        p2SoftwareBlendWeights(count, weights, out);
        break;
    }
    return count;
}

void p2SetBlendWeightCount(int count, int limit) {
    if (p2BlendWeightCount != count || p2BlendWeightLimit != limit) {
        p2DirtyFlags |= 0x81;
    }
    p2BlendWeightCount = count;
    p2BlendWeightLimit = limit;
}

void p2SetBlendWeightArray(const void *weights) {
    p2BlendWeightArray = weights;
}

void p2SetBlendIndexArray(const void *indices) {
    p2BlendIndexArray = indices;
}

void p2SetBlendMatrices(int base, int count) {
    p2BlendMatrixBase = base;
    p2BlendMatrixCount = count;
    p2DirtyFlags |= 0xA0;
}

void p2SetClearWidth(int width) {
    p2ClearWidth = width;
    p2BuildDisplayPacket();
}

void p2SetClearPasses(int on) {
    p2ClearPasses = on ? 2 : 0;
}

/* Clears the colour (mask bit 0) and depth (mask bit 1) of the buffer drawn into by drawing
 * sprites over it in context 1, then restores the registers it borrowed. */
void p2Clear(int mask, unsigned int colour, int depth) {
    long long prmode;
    long long zbuf;
    int antialias;
    int height;
    long long test;
    long long frame;
    long long scissor;

    antialias = (p2GetDisplayFlags() & P2_DISPLAY_ANTIALIAS) != 0;
    if (mask != 0) {
        if (p2Display.renderTarget < 0) {
            height = antialias != 0 ? p2Display.antialiasHeight : p2Display.height;
        } else {
            height = FUN_00208200(p2Display.renderTarget);
        }
        prmode = p2CurrentGsRegisters->prmode.word;
        test = p2CurrentGsRegisters->test[0].word;
        zbuf = p2CurrentGsRegisters->zbuf[0].word;
        frame = p2CurrentGsRegisters->frame[0].word;
        scissor = p2CurrentGsRegisters->scissor[0].word;
        if (!(mask & 1)) p2CurrentGsRegisters->frame[0].field.fbmsk = -1;
        p2CurrentGsRegisters->scissor[0].field.scax0 = 0;
        p2CurrentGsRegisters->scissor[0].field.scay0 = 0;
        p2CurrentGsRegisters->scissor[0].field.scax1 = (antialias != 0 ? p2Display.antialiasWidth : p2Display.width) - 1;
        p2CurrentGsRegisters->scissor[0].field.scay1 = (antialias != 0 ? p2Display.antialiasHeight : p2Display.height) - 1;
        {
            p2GsRegisterSet *gs = p2CurrentGsRegisters;
            gs->prmode.word = 0;
            gs->prim.field.type = P2_PRIM_SPRITE;
        }
        {
            p2GsRegisterSet *gs = p2CurrentGsRegisters;
            gs->test[0].word = 0;
            gs->test[0].field.zte = 1;
        }
        p2CurrentGsRegisters->test[0].field.ztst = P2_ZTST_ALWAYS;
        p2CurrentGsRegisters->zbuf[0].field.zmsk = ((mask & 2) != 0) ^ 1;
        p2ClearPass = 0;
        while (p2ClearPass < p2ClearPasses + 1) {
            if (p2ClearPasses != 0) {
                p2CurrentGsRegisters->rgbaq.field.r = p2ClearPass << 5;
            } else {
                p2CurrentGsRegisters->rgbaq.field.r = colour & 0xff;
            }
            p2CurrentGsRegisters->rgbaq.field.g = (colour >> 8) & 0xff;
            p2CurrentGsRegisters->rgbaq.field.b = (colour >> 16) & 0xff;
            p2CurrentGsRegisters->rgbaq.field.a = (colour >> 24) & 0xff;
            FUN_001f76f0(8, p2ClearRegisters);
            if (p2ClearWidth != 0) {
                p2DrawClearSprites(p2ClearWidth, height, depth);
            } else {
                p2DrawClearSprites((short)(antialias != 0 ? p2Display.antialiasWidth : p2Display.width), height, depth);
            }
            p2ClearPass += 1;
        }
        {
            p2GsRegisterSet *gs = p2CurrentGsRegisters;
            gs->prmode.word = prmode;
            gs->test[0].word = test;
            gs->zbuf[0].word = zbuf;
            gs->frame[0].word = frame;
            gs->scissor[0].word = scissor;
        }
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_PRMODE) | P2_GS_BIT(P2_GS_SCISSOR_1) | P2_GS_BIT(P2_GS_TEST_1)
            | P2_GS_BIT(P2_GS_FRAME_1) | P2_GS_BIT(P2_GS_ZBUF_1);
    }
}

void p2InitImagePool(void) {
    p2ImagePool = 0;
    p2ImagePoolSize = 0x400000;
    p2GrowPool(P2_POOL_IMAGE, &p2ImagePool);
}

p2Texture *p2GetImageTexture(p2Image *image) {
    return image->texture;
}

/* Creates a small lookup image (an 8x2 32-bit or a 16x16 16-bit one) over caller memory. */
p2Image *p2CreateImage(int format, int order, int layout, void *pixels) {
    /* matching construct: declaration-order permutation sweep (24 variants) */
    int psm;
    int width;
    int height;
    p2Image *image;

    switch (layout) {
    case 0:
    case 2:
    case 10:
        break;
    default:
        return 0;
    }
    switch (format) {
    case 0:
        width = 8;
        height = 2;
        psm = 13;
        break;
    case 1:
        width = 16;
        psm = 14;
        height = width;
        break;
    default:
        return 0;
    }
    if (p2ImagePool == 0) p2GrowPool(P2_POOL_IMAGE, &p2ImagePool);
    image = p2ImagePool;
    p2ImagePool = image->next;
    image->pixels = 0;
    image->pixels = pixels;
    image->format = format;
    image->order = order;
    image->layout = layout;
    image->texture = p2LoadTexture(image->pixels, width, height, psm, 0);
    if (image->texture != 0) image->texture->owner = image;
    return image;
}

/* Binds a palette for the current program's texture context. */
/* matching construct: a small sweep of spellings */
void p2SetClut(p2Clut *clut) {
    if (clut->image == 0) return;
    if (p2CurrentProgram == 0) {
        p2CurrentGsRegisters->tex0[0].field.cbp = clut->image->address;
        p2CurrentGsRegisters->tex0[0].field.cpsm = clut->format;
        p2CurrentGsRegisters->tex0[0].field.csm = clut->storageMode;
        p2CurrentGsRegisters->tex0[0].field.csa = 0;
        p2CurrentGsRegisters->tex0[0].field.cld = 2;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEXTURE_30) | P2_GS_BIT(P2_GS_TEXCLUT) | P2_GS_BIT(P2_GS_TEX0_1);
    } else {
        p2CurrentGsRegisters->tex0[1].field.cbp = clut->image->address;
        p2CurrentGsRegisters->tex0[1].field.cpsm = clut->format;
        p2CurrentGsRegisters->tex0[1].field.csm = clut->storageMode;
        p2CurrentGsRegisters->tex0[1].field.csa = 0;
        p2CurrentGsRegisters->tex0[1].field.cld = 2;
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_TEXTURE_30) | P2_GS_BIT(P2_GS_TEXCLUT) | P2_GS_BIT(P2_GS_TEX0_2);
        if (p2CurrentProgram == 1) FUN_001fcb00();
    }
    p2CurrentGsRegisters->texclut.field.cbw = 1;
    p2CurrentGsRegisters->texclut.field.cou = 0;
    p2CurrentGsRegisters->texclut.field.cov = 0;
}

void p2FreeImage(p2Image *image) {
    image->next = p2ImagePool;
    image->texture = 0;
    p2ImagePool = image;
    image->pixels = 0;
}

/* Empties the VU program table and, given a program list, reads it and the symbol table. The
 * built-in list separates its lines with '.', which become newlines first. */
void p2InitVuPrograms(const char *programList, const char *symbolTable) {
    int i;
    int length;

    p2VuMemoryUsed[0] = 0;
    p2VuMemoryUsed[1] = 0;
    p2VuMemorySize[0] = 0x200;
    p2VuMemorySize[1] = 0x800;
    for (i = 0; i < P2_VU_PROGRAM_COUNT; i++) {
        p2VuPrograms[i].size = -1;
    }
    p2VuProgramLast = -1;
    length = strlen(p2VuProgramList);
    for (i = 0; i < length; i++) {
        if (p2VuProgramList[i] == '.') {
            p2VuProgramList[i] = '\n';
        }
    }
    if (programList != 0 && p2OpenVu1Symbols(symbolTable, &p2VuMicrocode) != 0) {
        p2ParseVuProgramList(programList);
        p2CloseVu1Symbols();
        FUN_00202300();
    }
}

/* Unloads every program of one VU that is not resident, recounting the memory resident ones
 * keep. */
void p2UnloadVuPrograms(int vu) {
    int i;
    int last;
    int *used;
    p2VuProgram *program;

    used = &p2VuMemoryUsed[vu];
    *used = 0;
    last = p2VuProgramLast;
    for (i = 0; i <= last; i++) {
        program = &p2VuPrograms[i];
        if (vu == (program->flags & P2_VU_PROGRAM_VU1)) {
            if (!(program->flags & P2_VU_PROGRAM_RESIDENT)) {
                program->state = program->state & ~P2_VU_PROGRAM_LOADED;
            } else {
                *used += program->size;
            }
        }
    }
}

/* Loads the programs a draw needs. When one does not fit, VU1 is emptied once and every
 * program is loaded again; 0 then tells the caller its earlier uploads are gone, -1 that they
 * still do not fit. */
int p2LoadVuPrograms(int *programs, int *extraPrograms, int count, int extraCount) {
    int result;
    int i;

    result = 1;
    for (i = 0; i < count; i++) {
        if (p2LoadVuProgram(programs[i]) == 0) {
            break;
        }
    }
    if (i != count) {
        p2UnloadVuPrograms(1);
        p2InvalidateStateCache();
        result = 0;
        for (i = 0; i < count; i++) {
            if (p2LoadVuProgram(programs[i]) == 0) {
                return -1;
            }
        }
        for (i = 0; i < extraCount; i++) {
            if (p2LoadVuProgram(extraPrograms[i]) == 0) {
                return -1;
            }
        }
    }
    return result;
}

int p2GetVuProgramAddress(int program) {
    return p2VuPrograms[program].address;
}

void p2AliasVuProgram(int program, int target) {
    p2VuPrograms[program].alias = &p2VuPrograms[target];
    p2VuPrograms[program].reserved = 0;
    p2VuPrograms[program].flags = p2VuPrograms[program].flags | P2_VU_PROGRAM_ALIAS;
}

/* Adds a program whose microcode runs from start to end, as the next entry of the table. */
int p2AddVuProgram(unsigned int flags, unsigned int start, unsigned int end) {
    int result = -1;
    if (p2VuProgramLast + 1 < P2_VU_PROGRAM_COUNT) {
        result = ++p2VuProgramLast;
        p2VuPrograms[p2VuProgramLast].code = start;
        p2VuPrograms[p2VuProgramLast].size = (end - start) >> 3;
        p2VuPrograms[p2VuProgramLast].state = 0;
        p2VuPrograms[p2VuProgramLast].index = p2VuProgramLast;
        p2VuPrograms[p2VuProgramLast].address = 0;
        p2VuPrograms[p2VuProgramLast].alias = 0;
        p2VuPrograms[p2VuProgramLast].reserved = 0;
        p2VuPrograms[p2VuProgramLast].key = 0;
        p2VuPrograms[p2VuProgramLast].listValue = 0;
        p2VuPrograms[p2VuProgramLast].flags = flags;
        p2VuPrograms[p2VuProgramLast].reservedWords[0] = 0;
        p2VuPrograms[p2VuProgramLast].reservedWords[2] = 0;
        p2VuPrograms[p2VuProgramLast].reservedWords[1] = 0;
        p2VuPrograms[p2VuProgramLast].name = 0;
    }
    return result;
}

void p2SetVuProgramName(int program, const char *name) {
    char *copy;

    p2VuPrograms[program].name = (char *)FUN_00330730(strlen(name) + 1, P2_HEAP_VU);
    copy = p2VuPrograms[program].name;
    if (copy != 0) {
        strcpy(copy, name);
    }
}

char *p2GetVuProgramName(int program) {
    if (program != -1) return p2VuPrograms[program].name;
    return 0;
}

void p2SetVuProgram(int program, long long key, int listValue, unsigned int flags) {
    p2VuPrograms[program].key = key;
    p2VuPrograms[program].listValue = listValue;
    p2VuPrograms[program].flags = flags;
}

int p2IsVuProgramLoaded(int program) {
    return p2VuPrograms[program].state & P2_VU_PROGRAM_LOADED;
}

int p2FindVuProgram(const char *name) {
    int i;
    int found;

    found = -1;
    for (i = 0; p2VuProgramLast >= i; i++) {
        if (strcmp(p2VuPrograms[i].name, name) == 0) {
            found = i;
            break;
        }
    }
    return found;
}

/* Lists the variants of a program by their slot, returning how many there are. */
int p2FindVuProgramVariants(long long key, int *variants) {
    int i;
    int count = 0;

    for (i = 0; p2VuProgramLast >= i; i++) {
        p2VuProgram *program = &p2VuPrograms[i];
        if (key == program->key) {
            variants[(program->flags & 0xFFFF0000) >> 16] = i;
            count++;
        }
    }
    return count;
}

/* The first program from first on whose key has bitCount bits set in its low word. */
int p2FindVuProgramByBitCount(int bitCount, int first) {
    int bits;
    long long key;
    unsigned int bit;
    int found;

    found = 0;
    for (; first <= p2VuProgramLast; first++) {
        bits = 0;
        bit = 0;
        key = p2VuPrograms[first].key;
        do {
            if (key & 1) {
                bits += 1;
            }
            bit += 1;
            key = key >> 1;
        } while (bit < 32U);
        if (bits == bitCount) {
            found = first; break;
        }
    }
    return found;
}

void p2FreeVuProgramNames(void) {
    int i;
    char **name;

    for (i = 0; i <= p2VuProgramLast; i++) {
        name = &p2VuPrograms[i].name;
        if (*name != 0) {
            FUN_00330770(*name, P2_HEAP_VU);
            *name = 0;
        }
    }
}

void p2SetComponentLayout(int component, int isSigned, int integerBits, int fractionBits) {
    p2ComponentLayouts[component].isSigned = isSigned;
    p2ComponentLayouts[component].fractionBits = fractionBits;
    p2ComponentLayouts[component].integerBits = integerBits;
}

/* Whether a component is fixed point, and the float bits of 2^(23 - fractionBits). */
int p2GetComponentFixedScale(int component, int *scale) {
    p2ComponentLayout *layout;
    int fixed;

    layout = &p2ComponentLayouts[component];
    fixed = layout->isSigned + layout->integerBits;
    *scale = (0x96 - layout->fractionBits) << 0x17;
    return fixed != 0;
}

void p2GetComponentScale(int component, int *scale) {
    p2ComponentLayout *layout;
    int isSigned;
    int fractionBits;
    int integerBits;
    int bytes;
    int bias;
    layout = &p2ComponentLayouts[component];
    integerBits = layout->integerBits;
    isSigned = layout->isSigned;
    fractionBits = layout->fractionBits;
    bytes = (fractionBits + (isSigned + integerBits)) / 8;
    if (bytes != 0) {
        if (isSigned != 0) {
            bias = 1 << integerBits;
        } else {
            bias = 0;
        }
        *scale = (1 << (0x17 - fractionBits)) + bias;
        return;
    }
    *scale = 0;
}

/* The bytes one vertex's component takes in the vertex data. */
int p2GetComponentSize(int component) {
    p2ComponentLayout *layout = &p2ComponentLayouts[component];
    int bits = layout->fractionBits + (layout->isSigned + layout->integerBits);
    int bytes = bits / 8;
    switch (component) {
    case P2_COMPONENT_POSITION: case P2_COMPONENT_NORMAL:
        if (bytes == 0) return 12;
        return bytes * 3;
    case P2_COMPONENT_TEXCOORD:
        if (bytes == 0) return 8;
        return bytes * 2;
    case P2_COMPONENT_BLEND_WEIGHT:
        if (bytes == 0) return p2BlendWeightCount * 4;
        bytes = bytes * p2BlendWeightCount;
    case P2_COMPONENT_SPRITE_SIZE:
        break;
    }
    return bytes;
}

/* Sends the scales of the fixed-point components the current format uses to VU1. */
void p2UploadComponentScales(void) {
    int scale[P2_COMPONENT_COUNT];
    unsigned int *p = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
    p2GetComponentScale(P2_COMPONENT_POSITION, &scale[0]);
    p2GetComponentScale(P2_COMPONENT_NORMAL, &scale[1]);
    p2GetComponentScale(P2_COMPONENT_TEXCOORD, &scale[2]);
    p2GetComponentScale(P2_COMPONENT_BLEND_WEIGHT, &scale[3]);
    p2GetComponentScale(P2_COMPONENT_SPRITE_SIZE, &scale[4]);
    if (!(p2VertexFormat & (P2_FORMAT_RECORDING | P2_FORMAT_NORMALS))) scale[1] = 0;
    if (!(p2VertexFormat & (P2_FORMAT_RECORDING | P2_FORMAT_TEXCOORDS))) scale[2] = 0;
    if (!(p2VertexFormat & (P2_FORMAT_RECORDING | P2_FORMAT_BLEND_WEIGHTS))) scale[3] = 0;
    if (!(p2VertexFormat & (P2_FORMAT_RECORDING | P2_FORMAT_SPRITE_SIZE))) scale[4] = 0;
    p[0] = p2ComponentScaleUpload.tag.word[0];
    p[1] = p2ComponentScaleUpload.tag.word[1];
    p[2] = p2ComponentScaleUpload.tag.word[2];
    p[3] = p2ComponentScaleUpload.tag.word[3];
    p2ComponentScaleUpload.unpack.field.immediate = 30;
    p2ComponentScaleUpload.unpack.field.num = 1;
    p2ComponentScaleUpload.unpack.field.command = 0x6C;
    p[4] = p2ComponentScaleUpload.flush;
    p[5] = p2ComponentScaleUploadNop;
    p[6] = p2ComponentScaleUploadNop;
    p[7] = p2ComponentScaleUpload.unpack.word;
    ((float *)p)[8] = (float)scale[0];
    if (p2ComponentLayouts[P2_COMPONENT_NORMAL].integerBits + p2ComponentLayouts[P2_COMPONENT_NORMAL].fractionBits != 0)
        ((float *)p)[9] = (float)scale[1];
    else
        ((float *)p)[9] = (float)scale[4];
    ((float *)p)[10] = (float)scale[2];
    ((float *)p)[11] = (float)scale[3];
    p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)(p + 12);
    p2EndVif1Write();
}

void p2SetFrameMode(int on) {
    int value;

    value = on != 0;
    p2RequestedFrameMode = value;
    p2Display.frameMode = value;
}

void p2SetDisplayFrameCount(int count) {
    int frames;
    switch (count) {
    case 1:
    case 2:
        p2DisplayFrameCount = count;
        break;
    default:
        printf("p2SetDisplayFrameCount: invalid frame count, %d\n", count);
        break;
    }
    frames = p2DisplayFrameCount;
    p2Display.frameCount = frames;
}

void p2SetDisplayFlag(int flag, int on) {
    if (flag == P2_DISPLAY_32_BACK_16_FRONT) { if (on != 0) { p2DisplayFlags |= P2_DISPLAY_32_BACK_16_FRONT; } else { p2DisplayFlags &= ~P2_DISPLAY_32_BACK_16_FRONT; } } else if (flag == P2_DISPLAY_ANTIALIAS) { if (on != 0) { p2DisplayFlags |= P2_DISPLAY_ANTIALIAS; } else { p2DisplayFlags &= ~P2_DISPLAY_ANTIALIAS; } }
}

int p2GetDisplayFlags(void) {
    return p2DisplayFlags;
}

/* The size of the buffer drawn into, and the pixel formats of the frame and depth buffers. */
void p2GetDisplaySize(int *width, int *height, int *framePsm, int *depthPsm) {
    short w;
    short h;
    int antialias;

    antialias = (p2GetDisplayFlags() & P2_DISPLAY_ANTIALIAS) != 0;
    if (antialias != 0) {
        w = p2Display.antialiasWidth;
    } else {
        w = p2Display.width;
    }
    *width = w;
    if (antialias != 0) {
        h = p2Display.antialiasHeight;
    } else {
        h = p2Display.height;
    }
    *height = h;
    if ((p2Display.frameMode == 0) && (p2Display.interlaced > 0)) {
        *height *= 2;
    }
    if (framePsm != 0) {
        *framePsm = p2CurrentGsRegisters->frame[0].field.psm;
    }
    if (depthPsm != 0) {
        *depthPsm = p2CurrentGsRegisters->zbuf[0].field.psm;
    }
}

void p2GetTextureBase(int *base) {
    *base = p2Display.textureBase;
}

/* Turns colour channels' writes off (a channel argument of 0 masks it) for the current
 * program's frame buffer. */
void p2SetColourMask(int r, int g, int b, int a) {
    int mask;
    long long dirty;
    p2GsRegisterSet *gs;
    int psm;

    if (p2CurrentProgram == 0) {
        psm = p2CurrentGsRegisters->frame[0].field.psm;
        switch (psm) {
        case P2_PSM_CT32:
        case P2_PSM_CT24:
            mask = ((!a) ? 0xFF000000 : 0) | (((!b) ? 0xFF0000 : 0) | (((!r) ? 0xFF : 0) | ((!g) ? 0xFF00 : 0)));
            p2CurrentGsRegisters->frame[0].field.fbmsk = mask;
            break;
        case P2_PSM_CT16S:
        case P2_PSM_CT16:
            mask = ((!a) ? 0x80000000 : 0) | (((!b) ? 0xF80000 : 0) | (((!r) ? 0xF8 : 0) | ((!g) ? 0xF800 : 0)));
            p2CurrentGsRegisters->frame[0].field.fbmsk = mask;
            break;
        }
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        p2GsDirtyRegisters |= P2_GS_BIT(P2_GS_FRAME_1);
        if (p2ExtraPassCount != 0) {
            p2CurrentGsRegisters->frame[1].field.fbmsk = p2CurrentGsRegisters->frame[0].field.fbmsk;
            p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
            dirty = p2GsDirtyRegisters | P2_GS_BIT(P2_GS_FRAME_2);
            p2GsDirtyRegisters = dirty;
        }
    } else {
        gs = p2CurrentGsRegisters;
        psm = gs->frame[1].field.psm;
        switch (psm) {
        case P2_PSM_CT32:
        case P2_PSM_CT24:
            mask = ((!a) ? 0xFF000000 : 0) | (((!b) ? 0xFF0000 : 0) | (((!r) ? 0xFF : 0) | ((!g) ? 0xFF00 : 0)));
            gs->frame[1].field.fbmsk = mask;
            break;
        case P2_PSM_CT16:
        case P2_PSM_CT16S:
            mask = ((!a) ? 0x80000000 : 0) | (((!b) ? 0xF80000 : 0) | (((!r) ? 0x1F : 0) | ((!g) ? 0xF800 : 0)));
            gs->frame[1].field.fbmsk = mask;
            break;
        }
        p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
        dirty = p2GsDirtyRegisters | P2_GS_BIT(P2_GS_FRAME_2);
        p2GsDirtyRegisters = dirty;
    }
}

void p2EnableWatchdog(int on) {
    p2WatchdogEnabled = on;
}

/* Takes down what opening the display set up: the handlers, the watchdog thread, the VU
 * program names, the DMA channels and the pools. */
void p2CloseDisplay(void) {
    p2WaitFinishSequence(p2NewFinishSequence(1));
    p2DirtyFlags = P2_DIRTY_ALL;
    p2UnloadVuPrograms(1);
    p2InvalidateStateCache();
    if (p2FirstOpen == 0) {
        printf("Alchemy display closed\n");
        p2DisplayClosing = 1;
        if (FUN_0010ba90(P2_DMA_VIF1) == 0) {
            printf(" VIF1 already disabled\n");
        }
        if (FUN_0010ba90(P2_DMA_VIF0) == 0) {
            printf(" VIF0 already disabled\n");
        }
        if (FUN_0010ba90(P2_DMA_GIF) == 0) {
            printf(" GIF already disabled\n");
        }
        if (RemoveDmacHandler(P2_DMA_VIF1, p2DmaHandlerIds[P2_DMA_VIF1]) == -1) {
            printf("Error removing VIF1 dmac handler\n");
        }
        if ((p2DmaHandlerIds[P2_DMA_VIF0] != -1) && (RemoveDmacHandler(P2_DMA_VIF0, p2DmaHandlerIds[P2_DMA_VIF0]) == -1)) {
            printf("Error removing VIF0 dmac handler\n");
        }
        if (RemoveDmacHandler(P2_DMA_GIF, p2DmaHandlerIds[P2_DMA_GIF]) == -1) {
            printf("Error removing GIF dmac handler\n");
        }
        p2ShutdownTimer();
        FUN_0010b9c0(P2_INTC_GS);
        RemoveIntcHandler(P2_INTC_GS, p2GsIntcHandlerId);
        if (p2VblankStartIntcHandlerId != -1) {
            FUN_0010b9c0(P2_INTC_VBLANK_START);
            RemoveIntcHandler(P2_INTC_VBLANK_START, p2VblankStartIntcHandlerId);
        }
        if (p2Vif1IntcHandlerId != -1) {
            FUN_0010b9c0(P2_INTC_VIF1);
            RemoveIntcHandler(P2_INTC_VIF1, p2Vif1IntcHandlerId);
        }
        TerminateThread(p2WatchdogThread);
        DeleteThread(p2WatchdogThread);
        p2FreeVuProgramNames();
        FUN_00203500();
        p2ShutdownDmaChannels();
        p2FreePool(3, 0);
        p2FreePool(9, 0);
        p2FreePool(0xA, 0);
        p2FreePool(7, 0);
        p2FreePool(8, 0);
        p2FreePool(0xB, 0);
        p2FreePool(0xD, 0);
        p2FreePool(0, 0);
        p2FreePool(1, 0);
        p2FreePool(2, 0);
        p2FreePool(4, 0);
        p2FreePool(5, 0);
        p2FreePool(6, 0);
    }
}

void p2FreeDisplayListBlock(p2DisplayList *list) {
    list->next = p2DisplayListPool;
    list->previous = 0;
    p2DisplayListPool = list;
}

p2DisplayList *p2AllocDisplayList(void) {
    p2DisplayList *list;
    if (p2DisplayListPool == 0) {
        p2GrowPool(P2_POOL_DISPLAY_LIST, &p2DisplayListPool);
    }
    list = p2DisplayListPool;
    p2DisplayListPool = list->next;
    list->sequence = 0;
    list->previous = 0;
    list->ownsData = 1;
    list->fixedPoint = 0;
    return list;
}

void p2InitDisplayListPool(void) {
    p2DisplayListPool = 0;
    p2GrowPool(P2_POOL_DISPLAY_LIST, &p2DisplayListPool);
}

/* Starts recording: the VIF1 data of the draws that follow goes into the list's blocks instead
 * of the current VIF1 packet. Returns -1 while a list is already being recorded. */
p2DisplayList *p2BeginDisplayList(int mode) {
    p2DisplayList *list;

    if (p2DisplayListMode != 0) {
        return (p2DisplayList *)-1;
    }
    if ((p2ProgramFlags[p2CurrentProgram] >> P2_CAP_VERTEX_BLEND) & 1) {
        p2VertexFormat = P2_FORMAT_RECORDING | P2_FORMAT_BLEND;
        if (1 < p2BlendWeightCount) {
            p2VertexFormat = p2VertexFormat | P2_FORMAT_BLEND_WEIGHTS;
        }
    } else {
        p2VertexFormat = P2_FORMAT_RECORDING;
    }
    p2DisplayListMode = mode;
    p2DrawPipeline = 2;
    list = p2AllocDisplayList();
    p2RecordingBlock = list;
    p2RecordingList = list;
    list->next = 0;
    list->vertexCount = p2VertexCount;
    list->primitiveCount = p2PrimitiveCount;
    memset(&p2DisplayListPacket, 0, sizeof(p2DmaPacket));
    p2DisplayListPacket.chain = FUN_00330730(P2_DISPLAY_LIST_BLOCK_SIZE, P2_HEAP_DISPLAY_LIST);
    p2DisplayListPacket.cursor = p2DisplayListPacket.chain;
    p2DisplayListPacket.end = p2DisplayListPacket.chain + P2_DISPLAY_LIST_BLOCK_SIZE - 16;
    p2SavedVif1Packet = p2DmaCurrentPacket[P2_DMA_VIF1];
    p2DmaCurrentPacket[P2_DMA_VIF1] = &p2DisplayListPacket;
    p2DisplayListPacket.limit = p2DisplayListPacket.end - P2_DISPLAY_LIST_RESERVE;
    p2DisplayListPacket.f44 = p2DisplayListPacket.limit;
    list->data = p2DisplayListPacket.chain;
    return list;
}

/* Ends recording: closes the list with a DMA return tag, notes what it draws, and shrinks the
 * last block to its contents. */
void p2EndDisplayList(void) {
    int fixedPoint = p2ProgramFlags[p2CurrentProgram] >> P2_CAP_FIXED_POINT & 1;
    if (p2DisplayListMode != 0) {
        p2DisplayList *list = p2RecordingList;
        p2DisplayList *block;
        unsigned int *p;
        char *data;
        int size;
        list->primitive = p2CurrentPrimitive;
        list->constantColour = p2ConstantColour;
        list->vertexCount = p2VertexCount - list->vertexCount;
        list->primitiveCount = p2PrimitiveCount - list->primitiveCount;
        if (p2VertexFormat & P2_FORMAT_BLEND) {
            list->blendWeightCount = p2BlendWeightCount;
            list->blendMatrixCount = p2BlendMatrixCount;
        } else {
            list->blendWeightCount = 0;
            list->blendMatrixCount = 0;
        }
        list->fixedPoint = fixedPoint;
        list->format = p2VertexFormat;
        p2DrawPipeline = 0;
        p2VertexFormat &= ~P2_FORMAT_RECORDING;
        p2DirtyFlags |= 0x90;
        p = (unsigned int *)p2DisplayListPacket.cursor;
        p[0] = p2DisplayListReturnTag.word[0];
        p[1] = p2DisplayListReturnTag.word[1];
        p[2] = p2DisplayListReturnTag.word[2];
        p[3] = p2DisplayListReturnTag.word[3];
        block = p2RecordingBlock;
        block->end = (unsigned int)(p + 4);
        p2DisplayListMode = 0;
        p2DmaCurrentPacket[P2_DMA_VIF1] = p2SavedVif1Packet;
        size = block->end - block->data;
        data = FUN_003307b0(block->data, size, P2_HEAP_DISPLAY_LIST);
        if ((unsigned int)data != block->data && block->previous) {
            ((p2DmaChainTag *)(block->previous->end - 16))->field.addr = (unsigned int)data;
        }
        block->data = (unsigned int)data;
        block->end = (unsigned int)(data + size);
    }
}

/* Chains a fresh block to the list being recorded once the current one is full: the old block
 * ends with a DMA next tag that points at the new one. */
void p2GrowDisplayList(void) {
    p2DisplayList *previous;
    unsigned int *p;
    p2DisplayList *block;

    previous = p2RecordingBlock;
    p2RecordingBlock = p2AllocDisplayList();
    block = p2RecordingBlock;
    block->next = 0;
    block->previous = previous;
    block->sequence = 0;
    previous->next = block;
    p = (unsigned int *)p2DisplayListPacket.cursor;
    memset(&p2DisplayListPacket, 0, sizeof(p2DmaPacket));
    p2DisplayListPacket.chain = FUN_00330730(P2_DISPLAY_LIST_BLOCK_SIZE, P2_HEAP_DISPLAY_LIST);
    p2DisplayListPacket.cursor = p2DisplayListPacket.chain;
    p2DisplayListPacket.end = p2DisplayListPacket.chain + P2_DISPLAY_LIST_BLOCK_SIZE - 16;
    p2DisplayListPacket.limit = p2DisplayListPacket.end - P2_DISPLAY_LIST_RESERVE;
    p2DisplayListPacket.f44 = p2DisplayListPacket.limit;
    block->data = p2DisplayListPacket.chain;
    p2DisplayListNextTag.field.addr = p2DisplayListPacket.chain;
    p[0] = p2DisplayListNextTag.word[0];
    p[1] = p2DisplayListNextTag.word[1];
    p[2] = p2DisplayListNextTag.word[2];
    p[3] = p2DisplayListNextTag.word[3];
    previous->end = (unsigned int)(p + 4);
}

short p2GetDisplayListBlendWeightCount(p2DisplayList *list) {
    return list->blendWeightCount;
}

short p2GetDisplayListBlendMatrixCount(p2DisplayList *list) {
    return list->blendMatrixCount;
}

/* Fills in the texture registers a display list left open: each patch is an A+D pair marked
 * with the program whose current TEX0 it takes. */
int p2PatchDisplayListTextures(p2DisplayList *list) {
    int patched = 0;
    unsigned int *p;
    p2GsRegisterSet *gs;
    int program;
    int set;
    do {
        for (p = (unsigned int *)list->data; p < (unsigned int *)list->end; p++) {
            if (p[0] == p2TexturePatchMarker && p[2] == P2_DISPLAY_LIST_PATCH_KEY) {
                program = p[1];
                if (program == p[3] && program < P2_PROGRAM_COUNT) {
                    if (program > 1) {
                        set = program - 1;
                    } else {
                        set = 0;
                    }
                    gs = &p2GsRegisterSets[set];
                    if (p[12] == P2_GS_REG_TEX0_2) {
                        p[10] = gs->tex0[1].half[0];
                        p[11] = gs->tex0[1].half[1];
                    } else {
                        p[10] = gs->tex0[0].half[0];
                        p[11] = gs->tex0[0].half[1];
                    }
                    patched = 1;
                }
            }
        }
        list = list->next;
    } while (list != 0);
    return patched;
}

void p2FreeDisplayList(p2DisplayList *list) {
    p2DisplayList *next;

    next = list->next;
    if (next != 0) {
        p2FreeDisplayList(next);
    }
    FUN_00330770(list->data, P2_HEAP_DISPLAY_LIST);
    p2FreeDisplayListBlock(list);
}

/* Waits until the last packet that called the list has been sent, then frees it if it owns its
 * blocks. */
void p2ReleaseDisplayList(p2DisplayList *list) {
    p2WaitDmaSequence(P2_DMA_VIF1, list->sequence);
    if (list->ownsData) {
        p2FreeDisplayList(list);
    }
}

/* The bytes the list's data takes once its blocks are joined (without the chaining tags). */
int p2GetDisplayListSize(p2DisplayList *list) {
    int size = list->end - list->data;
    while ((list = list->next) != 0) {
        size -= 16;
        size += list->end - list->data;
    }
    return size;
}

unsigned int p2GetDisplayListData(p2DisplayList *list) {
    return list->data;
}

/* Joins the list's blocks into dest, writing each block over the chaining tag of the one
 * before; returns the bytes written. */
int p2CopyDisplayListData(p2DisplayList *list, char *dest) {
    p2DisplayList *block;
    int size;
    int blockSize;
    unsigned int data;
    block = list;
    size = block->end - (data = block->data);
    memcpy(dest, data, size);
    dest += size;
    while ((block = block->next) != 0) {
        dest -= 0x10;
        size -= 0x10;
        blockSize = block->end - (data = block->data);
        memcpy(dest, data, blockSize);
        dest += blockSize;
        size += blockSize;
    }
    return size;
}

p2DisplayList *p2CopyDisplayList(p2DisplayList *list) {
    p2DisplayList *copy;

    copy = (p2DisplayList *)FUN_00330730(sizeof(p2DisplayList), P2_HEAP_DISPLAY_LIST);
    memcpy(copy, list, sizeof(p2DisplayList));
    return copy;
}

/* Points a copied list at data joined elsewhere: one block, called afresh, not owning it. */
p2DisplayList *p2RebaseDisplayList(unsigned int data, p2DisplayList *list) {
    int size = list->end - list->data;
    list->sequence = 0;
    list->memory = 0;
    list->data = data;
    list->end = data + size;
    list->next = 0;
    list->previous = 0;
    list->ownsData = 0;
    return list;
}
