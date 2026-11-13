#include "dw4/reflected.h"
#include "dw4/igMemoryPoolView.h"
#include "dw4/igobject_release.h"

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
    void *reserved24[4];
    void (*pause)(MwPly *ply, int sw);       /* +40 */
} MwPlyFunctions;
struct MwPly {
    MwPlyFunctions *functions;
};

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
};

extern "C" {
int CriMovie_BuildTileUpload(void *packet, void *image, int tileBytes, int x, int y, int width, int height, int called);
void Dma_SetTag(unsigned long long *tag, unsigned spr, unsigned addr, unsigned irq, unsigned id, unsigned pce, unsigned qwc);
void Gif_SetTag(void *tag, unsigned long long regs, int nreg, int flg, int prim, int pre, int eop, int nloop);
static void Gif_SetAd(int *qword, int address, unsigned long long data);
void Gif_SetBitbltbuf(int *qword, unsigned int dbp, unsigned int dbw, unsigned int dpsm);
void Gif_SetTrxpos(int *qword, unsigned int dir, unsigned int dsax, unsigned int dsay);
void Gif_SetTrxreg(int *qword, unsigned int rrw, unsigned int rrh);
void Gif_SetTrxdir(int *qword, unsigned int xdir);
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
int Gap__igCriMovieCodec__vfunc_20(void);
int Gap__igCriMovieData__vfunc_20(void);

void Gap__Core__igObject__vfunc_01(void);
void Gap__Core__igObject__vfunc_02(void);
void Gap__Core__igObject__vfunc_11(void);
int igObject_IsKindOf(void *object, int metaObject);
void igObject_Destroy(igObject *object);
igMemoryPoolView *igObject_GetAllocator(void *object);
igMemoryPoolView *Memory_GetAllocatorBySelector(int selector);
void *Memory_AllocateAlignedWithAllocator(unsigned int size, unsigned int alignment, igMemoryPoolView *pool);
int Memory_FreeBufferWithAllocator(void *block, igMemoryPoolView *pool);
void FUN_00100610(void *storage);
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

extern unsigned char g_useOwnerAllocator;
extern unsigned char g_criMovieDmaWarningMuted;
extern int g_ndmwAllocatorSelector[4];
extern int g_igPsx2VisualContext_metaObject[4];
extern int g_igCriMovieCodec_metaObject[4];
extern int g_igCriMovieData_metaObject[4];
extern void *g_criMovieUploadPacket;
extern int g_criMovieUploadPacketSize;
extern igObject *g_criMovieVisualContext;
extern char You_probably_didn_t_open_the_DMA[];
}

static inline void mwPlyDestroy(MwPly *ply)
{
    ply->functions->destroy(ply);
}

static inline void mwPlyPause(MwPly *ply, int sw)
{
    ply->functions->pause(ply, sw);
}

static inline igCriMovieData *AsCriMovieData(void *object)
{
    if (object != 0 && igObject_IsKindOf(object, g_igCriMovieData_metaObject[0]) != 0) {
        return (igCriMovieData *)object;
    }
    return 0;
}

void Dma_SetTag(unsigned long long *tag, unsigned spr, unsigned addr, unsigned irq, unsigned id, unsigned pce, unsigned qwc) {
    *tag = (unsigned long long)qwc | (((unsigned long long)pce << 26) | (((unsigned long long)id << 28) | (((unsigned long long)irq << 31) | (((unsigned long long)spr << 63) | ((unsigned long long)(addr & ~0xFU) << 32)))));
}

void Gif_SetTag(void *tag, unsigned long long regs, int nreg, int flg, int prim, int pre, int eop, int nloop) {
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

void Gif_SetBitbltbuf(int *qword, unsigned int dbp, unsigned int dbw, unsigned int dpsm) {
    Gif_SetAd(qword, 0x50, (unsigned long long)dbp << 32 | ((unsigned long long)dpsm << 56 | (unsigned long long)dbw << 48));
}

void Gif_SetTrxpos(int *qword, unsigned int dir, unsigned int dsax, unsigned int dsay) {
    Gif_SetAd(qword, 0x51, (unsigned long long)dsax << 32 | ((unsigned long long)dir << 59 | (unsigned long long)dsay << 48));
}

void Gif_SetTrxreg(int *qword, unsigned int rrw, unsigned int rrh) {
    Gif_SetAd(qword, 0x52, (unsigned long long)rrh << 32 | rrw);
}

void Gif_SetTrxdir(int *qword, unsigned int xdir) {
    Gif_SetAd(qword, 0x53, xdir);
}

int CriMovie_BuildFrameUpload(void *packet, void *image, int x, int y, int width, int height, int called) {
    return CriMovie_BuildTileUpload(packet, image, 0x400, x, y, width, height, called);
}

/* Allocates the upload packet for the movie's frame size (six quadwords per 16x16 tile plus the
 * chain's head and tail) and takes a reference to the visual context it is sent through. */
int Gap__igCriMovieCodec__vfunc_28(igCriMovieCodec *self, igMovieInfo *movie, igObject **visualContext) {
    igMemoryPoolView *pool;
    unsigned int columns;
    unsigned int rows;
    igObject *object;
    igObject *context;
    igObject *previous;

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
    if (context != 0) {
        context->_refCount = context->_refCount + 1;
    }
    previous = g_criMovieVisualContext;
    IG_OBJECT_RELEASE(previous);
    g_criMovieVisualContext = context;
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

    firstBuffer = igPsx2VisualContext_IsDisplayingFirstBuffer(g_criMovieVisualContext);
    width = movie->_width;
    height = movie->_height;
    if (g_criMovieUploadPacket == 0 && g_criMovieDmaWarningMuted == 0) {
        answer = FUN_00308320(You_probably_didn_t_open_the_DMA);
        if (answer != 1 && answer == 2) {
            g_criMovieDmaWarningMuted = 1;
        }
    }
    g_criMovieUploadPacketSize = CriMovie_BuildFrameUpload(g_criMovieUploadPacket, image, 0, (firstBuffer != 0) ? 448 : 0, width, height, 1);
    igPsx2VisualContext_CallDmaChain(g_criMovieVisualContext, g_criMovieUploadPacket, g_criMovieUploadPacketSize, 1);
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
        if ((short)deleteStorage > 0) FUN_00100610(ref);
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
