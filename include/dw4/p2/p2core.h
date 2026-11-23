/* p2core.h - the p2 renderer's GS register images, display state and display lists.
 *
 * The renderer keeps one image of the GS drawing registers per render program set and marks
 * each register it changes in p2GsDirtyRegisters; the next draw sends the marked ones. Program 0
 * draws in GS context 1 and every other program in context 2; with multipass rendering context 2
 * follows what program 0 sets. */
#ifndef DW4_P2CORE_H
#define DW4_P2CORE_H

#define P2_PROGRAM_COUNT 16
#define P2_VU_PROGRAM_COUNT 384

/* The GS registers of a register set, by index; bit n of p2GsDirtyRegisters marks register n. */
enum p2GsRegister {
    P2_GS_PRIM = 0,
    P2_GS_RGBAQ = 1,
    P2_GS_TEX0_1 = 6,
    P2_GS_TEX0_2 = 7,
    P2_GS_PRMODECONT = 19,
    P2_GS_PRMODE = 20,
    P2_GS_TEXCLUT = 21,
    P2_GS_SCANMSK = 22,
    P2_GS_FOGCOL = 28,
    P2_GS_TEXTURE_30 = 30,
    P2_GS_SCISSOR_1 = 32,
    P2_GS_SCISSOR_2 = 33,
    P2_GS_ALPHA_1 = 34,
    P2_GS_ALPHA_2 = 35,
    P2_GS_DIMX = 36,
    P2_GS_DTHE = 37,
    P2_GS_COLCLAMP = 38,
    P2_GS_TEST_1 = 39,
    P2_GS_TEST_2 = 40,
    P2_GS_PABE = 41,
    P2_GS_FBA_1 = 42,
    P2_GS_FBA_2 = 43,
    P2_GS_FRAME_1 = 44,
    P2_GS_FRAME_2 = 45,
    P2_GS_ZBUF_1 = 46,
    P2_GS_ZBUF_2 = 47,
    P2_GS_SIGNAL = 53
};

#define P2_GS_BIT(reg) (1LL << (reg))

/* p2DirtyFlags: the renderer state the next draw must send again. */
enum {
    P2_DIRTY_FUNCTION_TABLES = 0x1,     /* the vertex programs' function tables 0 and 1 */
    P2_DIRTY_LIGHTING_FUNCTIONS = 0x2,  /* function table 2, the lighting programs */
    P2_DIRTY_LIGHTS = 0x4,
    P2_DIRTY_GIF_TAGS = 0x8,
    P2_DIRTY_VERTEX_FORMAT = 0x10,
    P2_DIRTY_BLEND_MATRICES = 0x20,
    P2_DIRTY_GS_REGISTERS = 0x40,
    P2_DIRTY_VU_BUFFERS = 0x80,
    P2_DIRTY_PASSES = 0x100,            /* the multipass setup */
    P2_DIRTY_ALL = 0x1FF
};

/* Bits of p2VertexFormat: which arrays the vertex program unpacks. */
enum p2VertexFormatBit {
    P2_FORMAT_NORMALS = 0x1,
    P2_FORMAT_COLOURS = 0x2,
    P2_FORMAT_TEXCOORDS = 0x4,
    P2_FORMAT_ARRAY_BITS = 0x7,
    P2_FORMAT_BLEND_WEIGHTS = 0x8,
    P2_FORMAT_BLEND = 0x10,
    P2_FORMAT_RECORDING = 0x20,
    P2_FORMAT_SPRITE_SIZE_MODE0 = 0x40,
    P2_FORMAT_SPRITE_SIZE_MODE1 = 0x80,
    P2_FORMAT_SPRITE_SIZE = 0xC0,
    P2_FORMAT_SPRITE_BYTES = 0x100,
    P2_FORMAT_SPRITE_WORDS = 0x200
};

/* The capability bits of a program's p2ProgramFlags entry. */
enum p2Capability {
    P2_CAP_TEXTURE = 1,
    P2_CAP_VIEWPORT_CLIPPING = 6,
    P2_CAP_FOG = 7,
    P2_CAP_LIGHTING = 8,
    P2_CAP_VERTEX_BLEND = 9,
    P2_CAP_TEXTURE_COMBINE = 10,
    P2_CAP_COLOUR_MATERIAL = 12,
    P2_CAP_TEXTURE_MATRIX = 13,
    P2_CAP_15 = 15,                     /* 15 and 16: meaning not known */
    P2_CAP_NORMALIZE_NORMALS = 18,
    P2_CAP_ARRAY_FORMAT = 22,           /* the format follows the bound arrays outside recording too */
    P2_CAP_MULTIPASS = 23,
    P2_CAP_25 = 25,                     /* meaning not known */
    P2_CAP_FIXED_POINT = 27
};
/* p2DisplayFlags */
enum {
    P2_DISPLAY_32_BACK_16_FRONT = 0x1, /* a 32-bit back buffer shown through a 16-bit front buffer */
    P2_DISPLAY_ANTIALIAS = 0x2         /* drawing goes to a larger buffer the display filters down */
};

typedef union p2GsPrim {
    unsigned long long word;
    struct {
        unsigned long long type : 3;
    } field;
} p2GsPrim;

typedef union p2GsRgbaq {
    unsigned long long word;
    struct {
        unsigned long long r : 8;
        unsigned long long g : 8;
        unsigned long long b : 8;
        unsigned long long a : 8;
    } field;
} p2GsRgbaq;

typedef union p2GsTex0 {
    unsigned long long word;
    struct {
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
    } field;
    unsigned int half[2];
} p2GsTex0;

typedef union p2GsTexClut {
    unsigned long long word;
    struct {
        unsigned int cbw : 6;
        unsigned int cou : 6;
        unsigned int cov : 10;
    } field;
} p2GsTexClut;

typedef union p2GsFogCol {
    unsigned long long word;
    struct {
        unsigned long long fcr : 8;
        unsigned long long fcg : 8;
        unsigned long long fcb : 8;
    } field;
} p2GsFogCol;

typedef union p2GsScissor {
    unsigned long long word;
    struct {
        unsigned long long scax0 : 11;
        unsigned long long : 5;
        unsigned long long scax1 : 11;
        unsigned long long : 5;
        unsigned long long scay0 : 11;
        unsigned long long : 5;
        unsigned long long scay1 : 11;
    } field;
    unsigned int half[2];
} p2GsScissor;

typedef union p2GsXyoffset {
    unsigned long long word;
    struct {
        short ofx;
        short f2;
        short ofy;
        short f6;
    } field;
} p2GsXyoffset;

typedef union p2GsTest {
    unsigned long long word;
    struct {
        unsigned long long ate : 1;
        unsigned long long atst : 3;
        unsigned long long aref : 8;
        unsigned long long afail : 2;
        unsigned long long date : 1;
        unsigned long long datm : 1;
        unsigned long long zte : 1;
        unsigned long long ztst : 2;
    } field;
    unsigned int half[2];
} p2GsTest;

typedef union p2GsFrame {
    unsigned long long word;
    struct {
        unsigned int fbp : 9;
        unsigned int : 7;
        unsigned int fbw : 6;
        unsigned int : 2;
        unsigned int psm : 6;
        unsigned int : 2;
        unsigned int fbmsk;
    } field;
    unsigned int half[2];
} p2GsFrame;

typedef union p2GsScanmsk {
    unsigned long long word;
    struct {
        unsigned char msk : 2;
    } field;
} p2GsScanmsk;

typedef union p2GsZbuf {
    unsigned long long word;
    struct {
        unsigned long long zbp : 9;
        unsigned long long : 15;
        unsigned long long psm : 4;
        unsigned long long : 4;
        unsigned long long zmsk : 1;
    } field;
    unsigned int half[2];
} p2GsZbuf;

typedef union p2GsBit {
    unsigned long long word;
    struct {
        unsigned long long on : 1;
    } field;
    unsigned int half[2];
} p2GsBit;

typedef union p2GsXyz {
    unsigned long long word;
    struct {
        unsigned short x;
        unsigned short y;
        unsigned int z;
    } field;
} p2GsXyz;

typedef union p2GsPrmode {
    unsigned long long word;
    struct {
        unsigned long long : 3;
        unsigned long long iip : 1;     /* Gouraud shading */
        unsigned long long tme : 1;     /* texture mapping */
        unsigned long long fge : 1;     /* fogging */
        unsigned long long abe : 1;     /* alpha blending */
        unsigned long long aa1 : 1;     /* antialiasing */
        unsigned long long fst : 1;
        unsigned long long ctxt : 1;
        unsigned long long fix : 1;
    } field;
    unsigned int half[2];
} p2GsPrmode;

/* ALPHA: Cv = (A - B) * C >> 7 + D, each selecting Cs, Cd or 0 (C: As, Ad or FIX). */
typedef union p2GsAlpha {
    unsigned long long word;
    struct {
        unsigned long long a : 2;
        unsigned long long b : 2;
        unsigned long long c : 2;
        unsigned long long d : 2;
        unsigned long long : 24;
        unsigned long long fix : 8;
    } field;
    unsigned int half[2];
} p2GsAlpha;

/* The images of the GS drawing registers a render program uses, in GS register order. */
typedef struct p2GsRegisterSet {
    p2GsPrim prim;
    p2GsRgbaq rgbaq;
    unsigned long long st;
    unsigned long long uv;
    unsigned long long xyzf2;
    p2GsXyz xyz2;
    p2GsTex0 tex0[2];
    unsigned long long clamp[2];
    unsigned long long fog;
    unsigned long long xyzf3;
    p2GsXyz xyz3;
    unsigned long long tex1[2];
    unsigned long long tex2[2];
    p2GsXyoffset xyoffset[2];
    p2GsBit prmodecont;
    p2GsPrmode prmode;
    p2GsTexClut texclut;
    p2GsScanmsk scanmsk;
    unsigned long long miptbp1[2];
    unsigned long long miptbp2[2];
    unsigned long long texa;
    p2GsFogCol fogcol;
    unsigned long long f264[3];
    p2GsScissor scissor[2];
    p2GsAlpha alpha[2];
    unsigned long long dimx;
    p2GsBit dthe;
    p2GsBit colclamp;
    p2GsTest test[2];
    p2GsBit pabe;
    p2GsBit fba[2];
    p2GsFrame frame[2];
    p2GsZbuf zbuf[2];
    unsigned long long bitbltbuf;
    unsigned long long trxpos;
    unsigned long long trxreg;
    unsigned long long trxdir;
    unsigned long long hwreg;
    unsigned long long signal;          /* the SIGNAL id in the low word, its mask in the high */
    unsigned long long finish;
    unsigned long long label;           /* the LABEL id in the low word, its mask in the high */
} p2GsRegisterSet;

/* Where the VU1 programs keep their buffers in VU1 data memory. The vertex batches are double
 * buffered through the VIF BASE and OFFSET registers; batchVertexLimit is how many vertices one
 * batch holds. */
typedef struct p2VuBufferLayout {
    short address0;
    short address1;
    short address2;
    short address3;
    short address4;
    short byteUnpackAddress;
    short address6;
    short address7;
    short address8;
    short base;                         /* VIF BASE: the first batch buffer */
    short offset;                       /* VIF OFFSET: where the second starts, from the first */
    short batchVertexLimit;
} p2VuBufferLayout;

/* One heap block of a recorded display list; the first block describes the whole list. */
typedef struct p2DisplayList {
    long long sequence;                 /* the VIF1 packet that last called the list */
    void *memory;                       /* the pool allocation a grow block heads */
    unsigned int data;
    unsigned int end;
    struct p2DisplayList *next;
    struct p2DisplayList *previous;
    unsigned char constantColour : 1;
    unsigned char ownsData : 1;
    unsigned char fixedPoint : 1;
    int format;
    int vertexCount;
    int primitiveCount;
    int primitive;
    short blendWeightCount;
    short blendMatrixCount;
} p2DisplayList;

/* What the display was opened with. */
typedef struct p2DisplayState {
    int textureBase;                    /* the first VRAM page above the display buffers */
    int f4;
    short width;
    short height;
    short interlaced;
    short frameMode;                    /* frame rendering: full height in interlaced modes */
    short frameCount;
    short drawBuffer;                   /* the buffer being drawn, toggled at each swap */
    short displayBuffer;                /* the buffer on screen */
    short singleBuffered;
    short f24;
    short f26;
    short secondBufferPage;             /* the frame buffer page of buffer 1; buffer 0 is page 0 */
    short f30;
    short f32;
    short antialiasWidth;               /* the size of the buffer drawn into with antialiasing */
    short antialiasHeight;
    int renderTarget;                   /* -1 while drawing to the display buffer */
} p2DisplayState;

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

struct p2Clut;
struct p2Image;
struct p2Texture;

#ifdef __cplusplus
extern "C" {
#endif

extern int p2DirtyFlags;
extern unsigned int p2ProgramFlags[P2_PROGRAM_COUNT];
extern int p2CurrentProgram;
extern p2GsRegisterSet p2GsRegisterSets[15];
extern p2GsRegisterSet *p2CurrentGsRegisters;
extern long long p2GsDirtyRegisters;
extern long long p2StatCapabilityChanges;
extern int p2ExtraPassCount;
extern p2DisplayState p2Display;
extern int p2DisplayFlags;
extern int p2FirstOpen;
extern int p2DisplayClosing;
extern int p2DisplayListMode;
extern int p2BlockedSema;
extern int p2PreviousFinishFuncDone;
extern p2VuBufferLayout p2VuBuffers;
extern p2VuProgram p2VuPrograms[P2_VU_PROGRAM_COUNT];
extern struct p2Image *p2ImagePool;
extern p2DisplayList *p2DisplayListPool;

p2DisplayList *p2BeginDisplayList(int mode);
void p2Clear(int mask, unsigned int colour, int depth);
void p2CloseDisplay(void);
p2DisplayList *p2CopyDisplayList(p2DisplayList *list);
int p2CopyDisplayListData(p2DisplayList *list, char *dest);
struct p2Image *p2CreateImage(int format, int order, int layout, void *pixels);
void p2DisableCapability(int capability);
void p2EnableCapability(int capability);
void p2EndDisplayList(void);
int p2FindVuProgramByBitCount(int bitCount, int first);
int p2FindVuProgramVariants(long long key, int *variants, int bit);
void p2FreeImage(struct p2Image *image);
int p2GetComponentFixedScale(int component, int *scale);
int p2GetComponentSize(int component);
int p2GetDisplayFlags(void);
int p2GetDisplayListBlendMatrixCount(p2DisplayList *list);
int p2GetDisplayListBlendWeightCount(p2DisplayList *list);
unsigned int p2GetDisplayListData(p2DisplayList *list);
int p2GetDisplayListSize(p2DisplayList *list);
void p2GetDisplaySize(int *width, int *height, int *framePsm, int *depthPsm);
struct p2Texture *p2GetImageTexture(struct p2Image *image);
void p2GetTextureBase(int *base);
int p2GetVuProgramAddress(int program);
char *p2GetVuProgramName(int program);
void p2GrowDisplayList(void);
int p2IsCapabilityEnabled(int capability);
int p2IsVuProgramLoaded(int program);
int p2LoadVuPrograms(int *programs, int *extraPrograms, int count, int extraCount);
p2DisplayList *p2RebaseDisplayList(unsigned int data, p2DisplayList *list);
void p2ReleaseDisplayList(p2DisplayList *list);
void p2SetAlphaTest(int method, int reference, int fail);
void p2SetBlendEquation(int a, int b, int c, int d, int fix);
void p2SetBlendIndexArray(const void *indices);
void p2SetBlendMatrices(int base, int count);
void p2SetBlendWeightArray(const void *weights);
void p2SetBlendWeightCount(int count, int limit);
void p2SetClearWidth(int width);
void p2SetClut(struct p2Clut *clut);
int p2SetColorScaler(int state, const float *value);
void p2SetColourClamp(int on);
void p2SetColourMask(int r, int g, int b, int a);
void p2SetComponentLayout(int component, int isSigned, int integerBits, int fractionBits);
void p2SetDepthFunction(int function, int writeDisabled);
void p2SetDestinationAlphaMode(int mode);
void p2SetDitherMatrix(long long matrix);
void p2SetFog(int mode, int unused, float start, float end, float density, float unused0, float unused1,
              float unused2);
void p2SetFogColour(float r, float g, float b);
void p2SetFrameBufferAlpha(unsigned char on);
void p2SetPixelAlphaBlend(unsigned char on);
void p2SetScissor(int x, int y, int width, int height);
void p2SetSoftwareBlendSource(const float *positions, const float *matrices, const void *weights,
                              const unsigned char *indices, int indexStride);
/* `matrixCount`, the context's blend matrix count, is passed by the caller and not read. */
int p2SoftwareBlend(int count, int weights, float *out, int matrixCount);
void p2UploadComponentScales(void);
extern int p2ClearPasses;
extern int p2ColorScalerState;
extern int p2BlendWeightCount;
extern int p2GsIntcHandlerId;
void p2EnableWatchdog(int on);
void p2SetClearPasses(int on);
void p2SetDisplayFrameCount(int count);
void p2SetFrameMode(int on);
void p2UploadBlendMatrices(void);

#ifdef __cplusplus
}
#endif

#endif
