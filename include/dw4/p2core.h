/* p2core.h - the p2 renderer's GS register images, display state and display lists.
 *
 * The renderer keeps one image of the GS drawing registers per render program set and marks
 * each register it changes in p2GsDirtyRegisters; the next draw sends the marked ones. Program 0
 * draws in GS context 1 and every other program in context 2; with multipass rendering context 2
 * follows what program 0 sets. */
#ifndef DW4_P2CORE_H
#define DW4_P2CORE_H

#define P2_PROGRAM_COUNT 16

/* The GS registers of a register set, by index; bit n of p2GsDirtyRegisters marks register n. */
enum p2GsRegister {
    P2_GS_PRIM = 0,
    P2_GS_RGBAQ = 1,
    P2_GS_TEX0_1 = 6,
    P2_GS_TEX0_2 = 7,
    P2_GS_PRMODE = 20,
    P2_GS_TEXCLUT = 21,
    P2_GS_SCANMSK = 22,
    P2_GS_FOGCOL = 28,
    P2_GS_TEXTURE_30 = 30,
    P2_GS_SCISSOR_1 = 32,
    P2_GS_SCISSOR_2 = 33,
    P2_GS_DIMX = 36,
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
    P2_DIRTY_GS_REGISTERS = 0x40,
    P2_DIRTY_ALL = 0x1FF
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

/* The images of the GS drawing registers a render program uses, in GS register order. */
typedef struct p2GsRegisterSet {
    p2GsPrim prim;
    p2GsRgbaq rgbaq;
    unsigned long long st;
    unsigned long long uv;
    unsigned long long xyzf2;
    unsigned long long xyz2;
    p2GsTex0 tex0[2];
    unsigned long long clamp[2];
    unsigned long long fog;
    unsigned long long xyzf3;
    unsigned long long xyz3;
    unsigned long long tex1[2];
    unsigned long long tex2[2];
    p2GsXyoffset xyoffset[2];
    unsigned long long prmodecont;
    unsigned long long prmode;
    p2GsTexClut texclut;
    p2GsScanmsk scanmsk;
    unsigned long long miptbp1[2];
    unsigned long long miptbp2[2];
    unsigned long long texa;
    p2GsFogCol fogcol;
    unsigned long long f232[3];
    p2GsScissor scissor[2];
    unsigned long long alpha[2];
    unsigned long long dimx;
    unsigned long long dthe;
    p2GsBit colclamp;
    p2GsTest test[2];
    p2GsBit pabe;
    p2GsBit fba[2];
    p2GsFrame frame[2];
    p2GsZbuf zbuf[2];
    unsigned long long f384[5];
    unsigned long long signal;          /* the SIGNAL id in the low word, its mask in the high */
    unsigned long long f432[2];
} p2GsRegisterSet;

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

extern int p2DirtyFlags;
extern unsigned int p2ProgramFlags[P2_PROGRAM_COUNT];
extern int p2CurrentProgram;
extern p2GsRegisterSet p2GsRegisterSets[15];
extern p2GsRegisterSet *p2CurrentGsRegisters;
extern long long p2GsDirtyRegisters;
extern int p2ExtraPassCount;
extern p2DisplayState p2Display;
extern int p2DisplayFlags;

#endif
