#include "dw4/reflected.h"
#include "dw4/igMemoryPoolView.h"
#include "dw4/igSmartPointer.h"

/* igMovieInfo::_type: a movie of this type is an ADX audio stream played through ADXT instead of
 * a Sofdec video played through MWPLY. */
enum { kMovieTypeAdx = 2 };

/* igMovieInfo::_state */
enum { kMovieStatePlaying = 0, kMovieStatePaused = 1 };

/* The MWPLY handle's function table: CRI's mwPly* entry points that are macros over it. */
typedef struct MwPly MwPly;
typedef struct MwPlyFunctions {
    void *reserved0[5];
    void (*destroy)(MwPly *ply);             /* +20 */
    void *reserved24[2];
    int (*getStat)(MwPly *ply);              /* +32 */
    void *reserved36[1];
    void (*pause)(MwPly *ply, int sw);       /* +40 */
} MwPlyFunctions;
struct MwPly {
    MwPlyFunctions *functions;
};

/* mwPlyGetStat: the player ran to the end of the stream, or failed. */
enum { kMwPlyStatPlayEnd = 3, kMwPlyStatError = 4 };

/* MWSFD's frame object, filled by mwPlyGetCurFrm; bufadr is 0 while no frame is decoded. */
typedef struct MwsfdFrmObj {
    void *bufadr;
    int reserved4[35];
} MwsfdFrmObj;

/* igCriMovieData::_macroFunction: hands a decoded frame to the display. */
typedef unsigned char (*CriMovieFrameFunction)(igMovieInfo *movie, void *image);

/* A held reference to an igObject. */
typedef struct igObjectRef {
    igObject *object;
} igObjectRef;

/* The codec's own slots that it calls on itself. */
class igCriMovieCodecView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24();
    virtual int resume(igMovieInfo *movie);              /* slot 25 */
    virtual int pause(igMovieInfo *movie, int state);    /* slot 26 */
    virtual void d27(); virtual void d28(); virtual void d29();
    virtual int syncPauseState(igMovieInfo *movie);      /* slot 30 */
};

extern "C" {
int CriMovie_BuildTileUpload(void *packet, char *image, int tileBytes, int x, int y, int width, int height, int called);
static void Dma_SetTag(unsigned long long *tag, unsigned spr, unsigned addr, unsigned irq, unsigned id, unsigned pce, unsigned qwc);
static void Gif_SetTag(void *tag, unsigned long long regs, int nreg, int flg, int prim, int pre, int eop, int nloop);
static void Gif_SetAd(int *qword, int address, unsigned long long data);
static void Gif_SetBitbltbuf(void *qword, unsigned int dbp, unsigned int dbw, unsigned int dpsm);
static void Gif_SetTrxpos(void *qword, unsigned int dir, unsigned int dsax, unsigned int dsay);
static void Gif_SetTrxreg(void *qword, unsigned int rrw, unsigned int rrh);
static void Gif_SetTrxdir(void *qword, unsigned int xdir);
int CriMovie_BuildFrameUpload(void *packet, void *image, int x, int y, int width, int height, int called);
int CriMovie_SubmitFrame(igMovieInfo *movie, void *image);
igObjectRef *CriMovie_DestroyObjectRef(igObjectRef *ref, int deleteStorage);
void *CriMovie_Allocate(igCriMovieCodec *codec, unsigned int size);
void *CriMovie_AllocateAligned(igCriMovieCodec *codec, unsigned int size, unsigned char alignment);
void CriMovie_Free(igCriMovieCodec *codec, void *block);

int Gap__igCriMovieCodec__vfunc_28(igCriMovieCodec *self, igMovieInfo *movie, igObject **visualContext);
int Gap__igCriMovieCodec__vfunc_29(igCriMovieCodec *self);
void Gap__igCriMovieData__vfunc_11(igCriMovieData *self);
void Gap__igCriMovieCodec__vfunc_01(igCriMovieCodec *self);
void Gap__igCriMovieCodec__vfunc_02(void);
int Gap__igCriMovieCodec__vfunc_21(void);
int Gap__igCriMovieCodec__vfunc_24(igCriMovieCodec *self, igMovieInfo *movie);
int Gap__igCriMovieCodec__vfunc_25(igCriMovieCodec *self, igMovieInfo *movie);
int Gap__igCriMovieCodec__vfunc_26(igCriMovieCodec *self, igMovieInfo *movie, int state);
int Gap__igCriMovieCodec__vfunc_30(igCriMovieCodecView *self, igMovieInfo *movie);
int igCriMovieCodec_Update(igCriMovieCodecView *self, igMovieInfo *movie);
int Gap__igCriMovieCodec__vfunc_20(void);
int Gap__igCriMovieData__vfunc_20(void);

void Gap__Core__igObject__vfunc_01(void);
void Gap__Core__igObject__vfunc_02(void);
void Gap__Core__igObject__vfunc_11(void);
int igObject_IsKindOf(void *object, int metaObject);
igMemoryPoolView *igObject_GetAllocator(void *object);
igMemoryPoolView *Memory_GetAllocatorBySelector(int selector);
void *Memory_AllocateAlignedWithAllocator(unsigned int size, unsigned int alignment, igMemoryPoolView *pool);
int Memory_FreeBufferWithAllocator(void *block, igMemoryPoolView *pool);
void __dl__FPv(void *storage);
int FUN_00308320(const char *format, ...);
void igPsx2VisualContext_CallDmaChain(igObject *self, void *packet, int size, int flush);
int igPsx2VisualContext_IsDisplayingFirstBuffer(igObject *self);
void MWSFD_SetMallocFunc(void *(*allocate)(igCriMovieCodec *, unsigned int),
                         void (*release)(igCriMovieCodec *, void *), igCriMovieCodec *context);
int mwPlyIsPause(MwPly *ply);
int ADXT_GetStatPause(int adxt);
void ADXT_Pause(int adxt, int sw);
void ADXT_Stop(int adxt);
void ADXT_Destroy(int adxt);
void ADXM_ExecMain(void);
void MWSFD_ExecVsyncFrame(void);
void mwPlyGetCurFrm(MwPly *ply, MwsfdFrmObj *frame);
void mwPlyRelCurFrm(MwPly *ply);
int igMovieInfo_GetTiling(igMovieInfo *movie, int *tileWidth, int *tileHeight, int *tilesAcross, int *tilesDown);

extern unsigned char g_useOwnerAllocator;
extern unsigned char g_criMovieDmaWarningMuted;
extern int g_ndmwAllocatorSelector[4];
extern int g_igPsx2VisualContext_metaObject[4];
extern int g_igCriMovieCodec_metaObject[4];
extern int g_igCriMovieData_metaObject[4];
extern void *g_criMovieUploadPacket;
extern int g_criMovieUploadPacketSize;
extern char You_probably_didn_t_open_the_DMA[];
}

/* The visual context the movie draws through, released when the program exits. */
extern "C" {
igSmartPointer<igPsx2VisualContext> g_criMovieVisualContext;
}

static inline void mwPlyDestroy(MwPly *ply)
{
    ply->functions->destroy(ply);
}

static inline void mwPlyPause(MwPly *ply, int sw)
{
    ply->functions->pause(ply, sw);
}

static inline int mwPlyGetStat(MwPly *ply)
{
    return ply->functions->getStat(ply);
}

static inline igCriMovieData *AsCriMovieData(void *object)
{
    if (object != 0 && igObject_IsKindOf(object, g_igCriMovieData_metaObject[0]) != 0) {
        return (igCriMovieData *)object;
    }
    return 0;
}

static void Dma_SetTag(unsigned long long *tag, unsigned spr, unsigned addr, unsigned irq, unsigned id, unsigned pce, unsigned qwc) {
    *tag = (unsigned long long)qwc | (((unsigned long long)pce << 26) | (((unsigned long long)id << 28) | (((unsigned long long)irq << 31) | (((unsigned long long)spr << 63) | ((unsigned long long)(addr & ~0xFU) << 32)))));
}

static void Gif_SetTag(void *tag, unsigned long long regs, int nreg, int flg, int prim, int pre, int eop, int nloop) {
    unsigned long long mask;
    int *words = (int *)tag;
    words[0] = (eop << 0xF) | nloop;
    words[1] = (nreg << 0x1C) | ((flg << 0x1A) | ((pre << 0xE) | (prim << 0xF)));
    mask = 0xFFFF;
    mask = (mask << 16) | 0xFFFF;
    words[2] = (int)(regs & mask);
    words[3] = (int)(regs >> 32);
}

static void Gif_SetAd(int *qword, int address, unsigned long long data) {
    qword[0] = (int)(data & 0xFFFFFFFF); qword[1] = (int)(data >> 32);
    qword[2] = address;
    qword[3] = 0;
}

static void Gif_SetBitbltbuf(void *qword, unsigned int dbp, unsigned int dbw, unsigned int dpsm) {
    Gif_SetAd((int *)qword, 0x50, (unsigned long long)dbp << 32 | ((unsigned long long)dpsm << 56 | (unsigned long long)dbw << 48));
}

static void Gif_SetTrxpos(void *qword, unsigned int dir, unsigned int dsax, unsigned int dsay) {
    Gif_SetAd((int *)qword, 0x51, (unsigned long long)dsax << 32 | ((unsigned long long)dir << 59 | (unsigned long long)dsay << 48));
}

static void Gif_SetTrxreg(void *qword, unsigned int rrw, unsigned int rrh) {
    Gif_SetAd((int *)qword, 0x52, (unsigned long long)rrh << 32 | rrw);
}

static void Gif_SetTrxdir(void *qword, unsigned int xdir) {
    Gif_SetAd((int *)qword, 0x53, xdir);
}

/* Writes the DMA chain that uploads a decoded frame to the GS one 16x16 PSMCT32 tile at a time,
 * column by column; the image holds each column of tiles contiguously, tileBytes per tile. Wider
 * than 640 pixels only 40 columns go; taller than 448 lines only 28 rows go, skipping as many lines
 * at the top of each column as at the bottom. Returns the chain's size in bytes. */
int CriMovie_BuildTileUpload(void *packet, char *image, int tileBytes, int x, int y, int width, int height, int called) {
    /* matching construct: register order — cursor declared first colours after the frame's shape */
    char *cursor;
    /* matching construct: unsigned copies of x and y keep the tile position as left + column * 16
     * instead of one running induction variable */
    unsigned int left;
    unsigned int top;
    int columns;
    int rows;
    int skippedLines;
    int start;
    int column;
    int row;
    int last;

    if (width > 640) {
        columns = 40;
    } else {
        columns = width >> 4;
    }
    if (height > 448) {
        rows = 28;
        skippedLines = (height - 448) / 2;
    } else {
        rows = height >> 4;
        skippedLines = 0;
    }
    left = x;
    top = y;
    start = ((unsigned int)packet & 0x0FFFFFFF) | 0x20000000;
    cursor = (char *)start;
    Dma_SetTag((unsigned long long *)cursor, 0, 0, 0, 1, 0, 3);
    Gif_SetTag(cursor + 16, 14, 1, 0, 0, 0, 0, 2);
    Gif_SetBitbltbuf(cursor + 32, 0, 10, 0);
    Gif_SetTrxreg(cursor + 48, 16, 16);
    cursor += 64;
    image += skippedLines * 64;
    for (column = 0; column < columns; column++) {
        for (row = 0; row < rows; row++) {
            /* matching construct: `? 1 : 0` makes last an int, so it is passed without another 0xff mask */
            last = (row == rows - 1 && column == columns - 1) ? 1 : 0;
            Dma_SetTag((unsigned long long *)cursor, 0, 0, 0, 1, 0, 4);
            Gif_SetTag(cursor + 16, 14, 1, 0, 0, 0, 0, 2);
            Gif_SetTrxpos(cursor + 32, 0, left + column * 16, top + row * 16);
            Gif_SetTrxdir(cursor + 48, 0);
            Gif_SetTag(cursor + 64, 0, 0, 2, 0, 0, last, 64);
            Dma_SetTag((unsigned long long *)(cursor + 80), 0, (unsigned int)image & 0x0FFFFFFF, 0, 3, 0, 64);
            cursor += 96;
            image += tileBytes;
        }
        image += skippedLines * 128;
    }
    Dma_SetTag((unsigned long long *)cursor, 0, 0, 0, called ? 6 : 7, 0, 0);
    cursor += 16;
    return (int)cursor - start;
}

int CriMovie_BuildFrameUpload(void *packet, void *image, int x, int y, int width, int height, int called) {
    return CriMovie_BuildTileUpload(packet, (char *)image, 0x400, x, y, width, height, called);
}

/* Allocates the upload packet for the movie's frame size (six quadwords per 16x16 tile plus the
 * chain's head and tail) and takes a reference to the visual context it is sent through. */
int Gap__igCriMovieCodec__vfunc_28(igCriMovieCodec *self, igMovieInfo *movie, igObject **visualContext) {
    igMemoryPoolView *pool;
    unsigned int columns;
    unsigned int rows;
    igObject *object;
    igObject *context;

    columns = (unsigned int)movie->_width >> 4;
    rows = (unsigned int)movie->_height >> 4;
    pool = igObject_GetAllocator(self);
    pool = g_useOwnerAllocator ? pool : Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
    g_criMovieUploadPacket = Memory_AllocateAlignedWithAllocator(((unsigned int)((((columns * rows * 6) + 0xA) * 4) + 0x3F) >> 6) << 8, 0x40, pool);
    object = *visualContext;
    if ((object != 0) && (igObject_IsKindOf(object, g_igPsx2VisualContext_metaObject[0]) != 0)) {
        context = object;
    } else {
        context = 0;
    }
    g_criMovieVisualContext = (igPsx2VisualContext *)context;
    return 1;
}

int Gap__igCriMovieCodec__vfunc_29(igCriMovieCodec *self) {
    igMemoryPoolView *pool;

    pool = igObject_GetAllocator(self);
    pool = g_useOwnerAllocator ? pool : Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
    Memory_FreeBufferWithAllocator(g_criMovieUploadPacket, pool);
    return 1;
}

/* Builds the packet that copies the decoded frame into the frame-buffer half the GS buffer index
 * selects, then hands it to the visual context. */
int CriMovie_SubmitFrame(igMovieInfo *movie, void *image) {
    int firstBuffer;
    int width;
    int height;
    int answer;

    firstBuffer = igPsx2VisualContext_IsDisplayingFirstBuffer(g_criMovieVisualContext.p);
    width = movie->_width;
    height = movie->_height;
    if (g_criMovieUploadPacket == 0 && g_criMovieDmaWarningMuted == 0) {
        answer = FUN_00308320(You_probably_didn_t_open_the_DMA);
        /* 1 has no action in this build; only 2 mutes the warning, and the empty arm keeps its compare. */
        if (answer == 1) {
        } else if (answer == 2) {
            g_criMovieDmaWarningMuted = 1;
        }
    }
    g_criMovieUploadPacketSize = CriMovie_BuildFrameUpload(g_criMovieUploadPacket, image, 0, (firstBuffer != 0) ? 448 : 0, width, height, 1);
    igPsx2VisualContext_CallDmaChain(g_criMovieVisualContext.p, g_criMovieUploadPacket, g_criMovieUploadPacketSize, 1);
    return 1;
}

void Gap__igCriMovieData__vfunc_11(igCriMovieData *self) {
    Gap__Core__igObject__vfunc_11();
    self->_mwply = 0;
    self->_adxt = 0;
    self->_macroFunction = 0;
}

/* Routes MWSFD's allocations through the codec's memory pool. */
void Gap__igCriMovieCodec__vfunc_01(igCriMovieCodec *self) {
    Gap__Core__igObject__vfunc_01();
    MWSFD_SetMallocFunc(&CriMovie_Allocate, &CriMovie_Free, self);
}

void Gap__igCriMovieCodec__vfunc_02(void)
{
    Gap__Core__igObject__vfunc_02();
}

int Gap__igCriMovieCodec__vfunc_21(void)
{
    return 1;
}

igObjectRef *CriMovie_DestroyObjectRef(igObjectRef *ref, int deleteStorage) {
    if (ref) {
        igObject *object = ref->object;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
        if ((short)deleteStorage > 0) __dl__FPv(ref);
    }
    return ref;
}

/* Stops the movie and destroys its ADXT and MWPLY handles, returning their work areas. */
int Gap__igCriMovieCodec__vfunc_24(igCriMovieCodec *self, igMovieInfo *movie) {
    igCriMovieData *data;

    data = AsCriMovieData((void *)movie->_userdata);
    if (data != 0) {
        if (data->_adxt != 0) {
            ADXT_Stop(data->_adxt);
            ADXT_Destroy(data->_adxt);
            CriMovie_Free(self, (void *)data->_adxwork);
            data->_adxt = 0;
            data->_adxwork = 0;
        }
        mwPlyDestroy((MwPly *)data->_mwply);
        CriMovie_Free(self, (void *)data->_cprmbuf);
        data->_mwply = 0;
        data->_cprmbuf = 0;
        return 1;
    }
    return 0;
}

int Gap__igCriMovieCodec__vfunc_25(igCriMovieCodec *self, igMovieInfo *movie) {
    igCriMovieData *data;

    data = AsCriMovieData((void *)movie->_userdata);
    if (data != 0) {
        movie->_state = kMovieStatePlaying;
        if (movie->_type == kMovieTypeAdx) {
            if (ADXT_GetStatPause(data->_adxt) != 0) {
                ADXT_Pause(data->_adxt, 0);
            }
        } else if (mwPlyIsPause((MwPly *)data->_mwply) == 1) {
            mwPlyPause((MwPly *)data->_mwply, 0);
        }
        return 1;
    }
    return 0;
}

int Gap__igCriMovieCodec__vfunc_26(igCriMovieCodec *self, igMovieInfo *movie, int state) {
    igCriMovieData *data;

    data = AsCriMovieData((void *)movie->_userdata);
    if (data != 0) {
        movie->_state = state;
        if (movie->_type == kMovieTypeAdx) {
            if (ADXT_GetStatPause(data->_adxt) == 0) {
                ADXT_Pause(data->_adxt, 1);
            }
        } else if (mwPlyIsPause((MwPly *)data->_mwply) == 0) {
            mwPlyPause((MwPly *)data->_mwply, 1);
        }
        return 1;
    }
    return 0;
}

/* Brings the player's pause state in line with the movie's requested state. */
int Gap__igCriMovieCodec__vfunc_30(igCriMovieCodecView *self, igMovieInfo *movie) {
    igCriMovieData *data = AsCriMovieData((void *)movie->_userdata);
    if (data != 0) {
        bool paused;
        if (movie->_type == kMovieTypeAdx) {
            paused = ADXT_GetStatPause(data->_adxt) == 1;
        } else {
            paused = mwPlyIsPause((MwPly *)data->_mwply) == 1;
        }
        if (movie->_state == kMovieStatePaused && !paused) {
            return self->pause(movie, 1);
        }
        if (movie->_state == kMovieStatePlaying && paused) {
            return self->resume(movie);
        }
    }
    return 0;
}

/* Per-frame update: keeps the pause state in step, runs the CRI servers, hands a decoded frame to
 * the display and pauses the movie once the stream ends or fails. Returns whether a frame went out. */
int igCriMovieCodec_Update(igCriMovieCodecView *self, igMovieInfo *movie) {
    igCriMovieData *data;
    int shown;
    MwsfdFrmObj frame;
    int tileWidth;
    int tileHeight;
    int tilesAcross;
    int tilesDown;
    int stat;

    data = AsCriMovieData((void *)movie->_userdata);
    shown = 0;
    if (data != 0) {
        self->syncPauseState(movie);
        if (movie->_state != kMovieStatePaused) {
            MWSFD_ExecVsyncFrame();
            MWSFD_ExecVsyncFrame();
            ADXM_ExecMain();
            mwPlyGetCurFrm((MwPly *)data->_mwply, &frame);
            if (frame.bufadr != 0) {
                if (data->_macroFunction == 0) {
                    igMovieInfo_GetTiling(movie, &tileWidth, &tileHeight, &tilesAcross, &tilesDown);
                    data->_macroFunction = (int)&CriMovie_SubmitFrame;
                }
                shown = ((CriMovieFrameFunction)data->_macroFunction)(movie, frame.bufadr);
                mwPlyRelCurFrm((MwPly *)data->_mwply);
            }
            stat = mwPlyGetStat((MwPly *)data->_mwply);
            if (stat == kMwPlyStatPlayEnd || stat == kMwPlyStatError) {
                self->pause(movie, 2);
            }
        }
    }
    return shown;
}

void *CriMovie_Allocate(igCriMovieCodec *codec, unsigned int size) {
    igMemoryPoolView *pool;

    pool = igObject_GetAllocator(codec);
    return pool->Allocate(size);
}

void *CriMovie_AllocateAligned(igCriMovieCodec *codec, unsigned int size, unsigned char alignment) {
    igMemoryPoolView *pool;

    pool = igObject_GetAllocator(codec);
    return pool->AllocateAligned(size, alignment);
}

void CriMovie_Free(igCriMovieCodec *codec, void *block) {
    igMemoryPoolView *pool;

    pool = igObject_GetAllocator(codec);
    pool->Free(block);
}

int Gap__igCriMovieCodec__vfunc_20(void)
{
    return g_igCriMovieCodec_metaObject[0];
}

int Gap__igCriMovieData__vfunc_20(void)
{
    return g_igCriMovieData_metaObject[0];
}
