#include "dw4/support/reflected.h"
#include "dw4/core/igMemoryPoolView.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/gfx/igVisualContextDispatchView.h"
#include "dw4/core/igFileDispatchView.h"
extern "C" {
#include "dw4/cri/cri_mwsfd.h"
#include "dw4/cri/cri_adxt.h"
#include <string.h>
}

/* igMovieInfo::_type: a movie of this type is an ADX audio stream played through ADXT instead of
 * a Sofdec video played through MWPLY. */
enum { kMovieTypeAdx = 2 };

/* igMovieInfo::_state */
enum { kMovieStatePlaying = 0, kMovieStatePaused = 1 };

/* mwPlyGetStat: the player ran to the end of the stream, or failed. */
enum { kMwPlyStatPlayEnd = 3, kMwPlyStatError = 4 };

/* MWSFD's frame object, filled by mwPlyGetCurFrm; bufadr is 0 while no frame is decoded. */
typedef struct MwsfdFrmObj {
    void *bufadr;
    int reserved4[35];
} MwsfdFrmObj;

/* igCriMovieData::_macroFunction: hands a decoded frame to the display. */
typedef unsigned char (*CriMovieFrameFunction)(igMovieInfo *movie, void *image);

/* The codec's virtual functions from slot 20 on, for the slots it calls on itself; slots 0-19 are igObject's. */
class igCriMovieCodecView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int getMeta();
    virtual int isReusable();
    virtual void d22(); virtual void d23();
    virtual int close(igMovieInfo *movie);
    virtual int resume(igMovieInfo *movie);
    virtual int pause(igMovieInfo *movie, int state);
    virtual int update(igMovieInfo *movie);
    virtual int initializeDrawing(igMovieInfo *movie, igObject **visualContext);
    virtual int releaseDrawing();
    virtual int syncPauseState(igMovieInfo *movie);
};

#include "dw4/core/igObject.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igMemory.h"
#include "dw4/gfx/igPsx2VisualContext.h"
#include "dw4/movie/igMovieInfo.h"
#include "dw4/audio/igAdx.h"
#include "dw4/movie/igCriMovieData.h"
#include "dw4/movie/igCriMovieCodec.h"
#include "dw4/cri/adx_ps2.h"
#include "dw4/cri/cri_adxf.h"
#include "dw4/core/igFile.h"
#include "dw4/core/igReport.h"
#include <math.h>
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
void *CriMovie_Allocate(igCriMovieCodec *codec, unsigned int size);
void *CriMovie_AllocateAligned(igCriMovieCodec *codec, unsigned int size, unsigned char alignment);
void CriMovie_Free(igCriMovieCodec *codec, void *block);

int igCriMovieCodec_InitializeDrawing(igCriMovieCodec *self, igMovieInfo *movie, igObject **visualContext);
int igCriMovieCodec_ReleaseDrawing(igCriMovieCodec *self);
void Gap__igCriMovieData__resetFields(igCriMovieData *self, int flags);
void Gap__igCriMovieCodec__constructFields(igCriMovieCodec *self, int flags);
void Gap__igCriMovieCodec__destructFields(igCriMovieCodec *self);
int igCriMovieCodec_IsReusable(void);
int igCriMovieCodec_Close(igCriMovieCodec *self, igMovieInfo *movie);
int igCriMovieCodec_Play(igCriMovieCodec *self, igMovieInfo *movie);
int igCriMovieCodec_Pause(igCriMovieCodec *self, igMovieInfo *movie, int state);
int igCriMovieCodec_SyncPauseState(igCriMovieCodecView *self, igMovieInfo *movie);
int igCriMovieCodec_Update(igCriMovieCodecView *self, igMovieInfo *movie);
igMetaObject *igCriMovieCodec_GetMeta(void);
igMetaObject *igCriMovieData_GetMeta(void);

void mwPlySetMallocFn(void *(*allocate)(igCriMovieCodec *, unsigned int),
                         void (*release)(igCriMovieCodec *, void *), igCriMovieCodec *context);

extern unsigned char g_criMovieUseRawPath;
extern unsigned char g_criMovieOpenFailedMuted;
extern unsigned char g_criMovieAllocFailedMuted;
extern unsigned char g_criMovieReadFailedMuted;
extern unsigned char g_criMovieAhxMuted;
extern unsigned char g_criMovieUnknownTypeMuted;
extern unsigned char g_criMovieNoWidthMuted;
extern unsigned char g_criMovieNoHeightMuted;
extern unsigned char g_criMovieWidthMismatchMuted;
extern unsigned char g_criMovieHeightMismatchMuted;
extern unsigned char g_criMovieMacroblockMuted;
extern char Could_not_open_s[];
extern char Aligned_malloc_failed_d_bytes[];
extern char Read_failure_in_s[];
extern char AHX_files_aren_t_supported_yet[];
extern char Got_a_file_of_unknown_type[];
extern char Could_not_determine_size_of_video[];
extern char Movie_width_doesn_t_match_info_width[];
extern char Movie_height_doesn_t_match_info_height[];
extern char On_PS2_the_width_and_height_of_a_movie[];
void igCriMovieCodec_Initialize(igCriMovieCodec *self, igObject *visualContext, igObject *audioContext);
int igCriMovieCodec_Open(igCriMovieCodec *self, igMovieInfo *movie);
extern unsigned char g_criMovieDmaWarningMuted;
extern void *g_criMovieUploadPacket;
extern int g_criMovieUploadPacketSize;
extern char You_probably_didn_t_open_the_DMA[];
}

/* The visual context the movie draws through, released when the program exits. */
extern "C" {
igSmartPointer<igPsx2VisualContext> g_criMovieVisualContext;
}

static inline void mwPlyDestroy(MwsfdPly *ply)
{
    ply->vtbl->destroy(ply);
}

static inline void mwPlyPause(MwsfdPly *ply, int sw)
{
    ply->vtbl->pause(ply, sw);
}

static inline int mwPlyGetStat(MwsfdPly *ply)
{
    return ply->vtbl->getStat(ply);
}

/* The MWPLY and ADXT handles an igCriMovieData holds. */
static inline MwsfdPly *Player(igCriMovieData *data)
{
    return (MwsfdPly *)data->_mwply;
}

static inline AdxtObj *Adxt(igCriMovieData *data)
{
    return (AdxtObj *)data->_adxt;
}

static inline igCriMovieData *AsCriMovieData(void *object)
{
    if (object != 0 && igObject_IsKindOf((igObject *)object, g_igCriMovieData_metaObject) != 0) {
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
int igCriMovieCodec_InitializeDrawing(igCriMovieCodec *self, igMovieInfo *movie, igObject **visualContext) {
    igMemoryPoolView *pool;
    unsigned int columns;
    unsigned int rows;
    igObject *object;
    igObject *context;

    columns = (unsigned int)movie->_width >> 4;
    rows = (unsigned int)movie->_height >> 4;
    pool = igObject_GetAllocator(self);
    pool = g_useOwnerAllocator ? pool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
    g_criMovieUploadPacket = Memory_AllocateAlignedWithAllocator(((unsigned int)((((columns * rows * 6) + 0xA) * 4) + 0x3F) >> 6) << 8, 0x40, pool);
    object = *visualContext;
    if ((object != 0) && (igObject_IsKindOf(object, g_igPsx2VisualContext_metaObject) != 0)) {
        context = object;
    } else {
        context = 0;
    }
    g_criMovieVisualContext = (igPsx2VisualContext *)context;
    return 1;
}

int igCriMovieCodec_ReleaseDrawing(igCriMovieCodec *self) {
    igMemoryPoolView *pool;

    pool = igObject_GetAllocator(self);
    pool = g_useOwnerAllocator ? pool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
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
        answer = igReportError(You_probably_didn_t_open_the_DMA);
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

void Gap__igCriMovieData__resetFields(igCriMovieData *self, int flags) {
    Gap__Core__igObject__resetFields(self, flags);
    self->_mwply = 0;
    self->_adxt = 0;
    self->_macroFunction = 0;
}

/* Routes MWSFD's allocations through the codec's memory pool. */
void Gap__igCriMovieCodec__constructFields(igCriMovieCodec *self, int flags) {
    Gap__Core__igObject__constructFields(self, flags);
    mwPlySetMallocFn(&CriMovie_Allocate, &CriMovie_Free, self);
}

void Gap__igCriMovieCodec__destructFields(igCriMovieCodec *self)
{
    Gap__Core__igObject__destructFields(self);
}

int igCriMovieCodec_IsReusable(void)
{
    return 1;
}

/* Takes the visual and audio contexts the movies play through and, the first time, initialises
 * MWSFD for the display's refresh rate: NTSC 59.94 Hz or PAL 50 Hz, 60 Hz when the context
 * reports neither. */
void igCriMovieCodec_Initialize(igCriMovieCodec *self, igObject *visualContext, igObject *audioContext) {
    igVisualContextDispatchView *display;
    VideoMode mode;
    MwsfdInitPrm prm;
    float refreshRate;

    if (self->_initialized == 0) {
        reinterpret_cast<igSmartPointer<igObject> &>(self->_visualContext) = visualContext;
        reinterpret_cast<igSmartPointer<igObject> &>(self->_audioContext) = audioContext;
        refreshRate = 60.0f;
        display = (igVisualContextDispatchView *)visualContext;
        if (display != 0) {
            mode.pal = 0;
            mode.enable = 0;
            mode.interlace = 0;
            mode.refreshRate = 0.0f;
            mode.swapInterval = 0;
            display->getVideoMode(&mode);
            if (mode.pal == 0 && mode.refreshRate == 59.94f) {
                refreshRate = 59.94f;
            } else if (mode.pal == 1 && mode.refreshRate == 50.0f) {
                refreshRate = 50.0f;
            }
        }
        memset(&prm, 0, sizeof(prm));
        prm.vhz = refreshRate;
        prm.dispLatency = 1;
        prm.dispCycle = 1;
        prm.decSvr = 0;
        mwPlyInitSfdFx(&prm);
    }
    self->_initialized = 1;
}

/* Opens a movie: finds its file (an AFS entry or a plain path), reads the first sectors to tell a
 * Sofdec stream from an ADX one and takes the stream's size, then creates the MWPLY or ADXT player,
 * starts it and keeps the handles in an igCriMovieData in the movie's user data. Returns 0 when the
 * movie cannot be opened. */
int igCriMovieCodec_Open(igCriMovieCodec *self, igMovieInfo *movie) {
    char *path;
    int afsIndex;
    igMemoryPoolView *pool;
    AdxfHandle *adxf;
    void *header;
    int status;
    unsigned char isAdx;
    int answer;
    MwsfdCreInf cre;
    MwsfdHdrInf sofdecInfo;
    AdxtHdrInfo adxInfo;
    igAdxAfsFile *afsFile;

    if (g_criMovieUseRawPath != 0) {
        path = (char *)movie->_path;
    } else {
        pool = igObject_GetAllocator(self);
        pool = g_useOwnerAllocator ? pool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igSmartPointer<igFileDispatchView> file((igFileDispatchView *)igFile_Create((int)pool));
        path = file->MakeCompleteFilename((const char *)movie->_path);
    }
    afsIndex = igAdx_FindAfsFile(path);
    pool = igObject_GetAllocator(self);
    pool = g_useOwnerAllocator ? pool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    igSmartPointer<igCriMovieData> data(igCriMovieData_Create((int)pool));
    if (afsIndex != -1) {
        afsFile = ((igAdxAfsFile **)g_adxAfsFileList.p->_data)[afsIndex];
        adxf = ADXF_OpenAfs(afsFile->_ptNumber, afsFile->_fileNumber);
    } else {
        adxf = ADXF_Open(path, 0);
    }
    if (adxf == 0) {
        if (g_criMovieOpenFailedMuted == 0) {
            answer = igReportError(Could_not_open_s, path);
            if (answer == 1) {
            } else if (answer == 2) {
                g_criMovieOpenFailedMuted = 1;
            }
        }
        return 0;
    }
    header = CriMovie_AllocateAligned(self, 0x5000, 0x40);
    if (header == 0) {
        if (g_criMovieAllocFailedMuted == 0) {
            answer = igReportError(Aligned_malloc_failed_d_bytes, 0x5000);
            if (answer == 1) {
            } else if (answer == 2) {
                g_criMovieAllocFailedMuted = 1;
            }
        }
        return 0;
    }
    memset(header, 0, 0x5000);
    ADXF_ReadNw(adxf, 10, header);
    status = ADXF_GetStat(adxf);
    while (status != 3) {
        if (status == 4) {
            if (g_criMovieReadFailedMuted == 0) {
                answer = igReportError(Read_failure_in_s, path);
                if (answer == 1) {
                } else if (answer == 2) {
                    g_criMovieReadFailedMuted = 1;
                }
            }
            break;
        }
        ADXM_ExecVsyncFrame();
        ADXM_ExecMain();
        status = ADXF_GetStat(adxf);
    }
    ADXF_Close(adxf);
    mwPlyGetHdrInf((char *)header, 0x5000, &sofdecInfo);
    if (sofdecInfo.valid == 0) {
        ADXT_GetHdrInfo(header, 0x1000, &adxInfo);
        CriMovie_Free(self, header);
        if (adxInfo.fmt == 1) {
            isAdx = 1;
            movie->_type = kMovieTypeAdx;
        } else if (adxInfo.fmt == 2) {
            if (g_criMovieAhxMuted == 0) {
                answer = igReportError(AHX_files_aren_t_supported_yet, path);
                if (answer == 1) {
                } else if (answer == 2) {
                    g_criMovieAhxMuted = 1;
                }
            }
            return 0;
        } else {
            if (g_criMovieUnknownTypeMuted == 0) {
                answer = igReportError(Got_a_file_of_unknown_type, path);
                if (answer == 1) {
                } else if (answer == 2) {
                    g_criMovieUnknownTypeMuted = 1;
                }
            }
            return 0;
        }
    } else {
        CriMovie_Free(self, header);
        if (sofdecInfo.width == 0 && movie->_width == -1) {
            if (g_criMovieNoWidthMuted == 0) {
                answer = igReportError(Could_not_determine_size_of_video);
                if (answer == 1) {
                } else if (answer == 2) {
                    g_criMovieNoWidthMuted = 1;
                }
            }
            return 0;
        }
        if (sofdecInfo.height == 0 && movie->_height == -1) {
            if (g_criMovieNoHeightMuted == 0) {
                answer = igReportError(Could_not_determine_size_of_video);
                if (answer == 1) {
                } else if (answer == 2) {
                    g_criMovieNoHeightMuted = 1;
                }
            }
            return 0;
        }
        if (movie->_width != -1 && sofdecInfo.width != movie->_width && g_criMovieWidthMismatchMuted == 0) {
            answer = igReportNotice(Movie_width_doesn_t_match_info_width, movie->_width, sofdecInfo.width);
            if (answer == 1) {
            } else if (answer == 2) {
                g_criMovieWidthMismatchMuted = 1;
            }
        }
        if (movie->_height != -1 && sofdecInfo.height != movie->_height && g_criMovieHeightMismatchMuted == 0) {
            answer = igReportNotice(Movie_height_doesn_t_match_info_height, movie->_height, sofdecInfo.height);
            if (answer == 1) {
            } else if (answer == 2) {
                g_criMovieHeightMismatchMuted = 1;
            }
        }
        movie->_width = sofdecInfo.width;
        isAdx = 0;
        movie->_height = sofdecInfo.height;
    }
    if (!isAdx && (movie->_width % 16 != 0 || movie->_height % 16 != 0) && g_criMovieMacroblockMuted == 0) {
        answer = igReport_Warning(On_PS2_the_width_and_height_of_a_movie, movie->_width, movie->_height);
        if (answer == 1) {
        } else if (answer == 2) {
            g_criMovieMacroblockMuted = 1;
        }
    }
    mwPlySetTimerCh(0);
    memset(&cre, 0, sizeof(cre));
    cre.addInfMode = 0; /* asks for the additional-information stream; the store survives the memset above */
    cre.type = 1;
    cre.maxBps = (movie->_bitrate == -1) ? 0x5B8D80 : movie->_bitrate;
    cre.maxWidth = sofdecInfo.width;
    cre.maxHeight = sofdecInfo.height;
    cre.nfrmPoolWk = 2;
    cre.nfrm = 1;
    cre.workSize = mwPlyCalcWorkCprmSfd(&cre);
    cre.work = (char *)CriMovie_Allocate(self, cre.workSize);
    data->_mwply = (int)mwPlyCreateSofdec(&cre);
    data->_cprmbuf = (int)cre.work;
    if (self->_audioContext != 0) {
        if (movie->_audioChannel != -1) {
            mwPlySetAudioCh(Player(data), movie->_audioChannel);
        }
        if (movie->_audioVolume != -1) {
            float level;
            if (movie->_audioVolume != 0) {
                level = log10f((float)movie->_audioVolume) / 2.0f;
            } else {
                level = 0.0f;
            }
            Player(data)->vtbl->setOutVol(Player(data), (int)(796.0f * level - 796.0f));
        }
    }
    if (!isAdx) {
        if (afsIndex != -1) {
            afsFile = ((igAdxAfsFile **)g_adxAfsFileList.p->_data)[afsIndex];
            if (movie->_loop != 0) {
                mwPlyStartAfsLp(Player(data), afsFile->_ptNumber, afsFile->_fileNumber);
            } else {
                mwPlyStartAfs(Player(data), afsFile->_ptNumber, afsFile->_fileNumber);
            }
        } else if (movie->_loop != 0) {
            mwPlyStartFnameLp(Player(data), path);
        } else {
            Player(data)->vtbl->startFname(Player(data), path);
        }
    } else {
        data->_adxwork = (int)CriMovie_Allocate(self, 0x231E4);
        data->_adxt = (int)ADXT_Create(2, (char *)data->_adxwork, 0x231E4);
        if (afsIndex != -1) {
            afsFile = ((igAdxAfsFile **)g_adxAfsFileList.p->_data)[afsIndex];
            ADXT_StartAfs(Adxt(data), afsFile->_ptNumber, afsFile->_fileNumber);
        } else if (movie->_loop != 0) {
            ADXT_StartFnameLp(Adxt(data), path);
        } else {
            ADXT_StartFname(Adxt(data), path);
        }
    }
    reinterpret_cast<igSmartPointer<igObject> &>(movie->_userdata) = (igObject *)data.p;
    return 1;
}

/* Stops the movie and destroys its ADXT and MWPLY handles, returning their work areas. */
int igCriMovieCodec_Close(igCriMovieCodec *self, igMovieInfo *movie) {
    igCriMovieData *data;

    data = AsCriMovieData((void *)movie->_userdata);
    if (data != 0) {
        if (data->_adxt != 0) {
            ADXT_Stop(Adxt(data));
            ADXT_Destroy(Adxt(data));
            CriMovie_Free(self, (void *)data->_adxwork);
            data->_adxt = 0;
            data->_adxwork = 0;
        }
        mwPlyDestroy(Player(data));
        CriMovie_Free(self, (void *)data->_cprmbuf);
        data->_mwply = 0;
        data->_cprmbuf = 0;
        return 1;
    }
    return 0;
}

int igCriMovieCodec_Play(igCriMovieCodec *self, igMovieInfo *movie) {
    igCriMovieData *data;

    data = AsCriMovieData((void *)movie->_userdata);
    if (data != 0) {
        movie->_state = kMovieStatePlaying;
        if (movie->_type == kMovieTypeAdx) {
            if (ADXT_GetStatPause(Adxt(data)) != 0) {
                ADXT_Pause(Adxt(data), 0);
            }
        } else if (mwPlyIsPause(Player(data)) == 1) {
            mwPlyPause(Player(data), 0);
        }
        return 1;
    }
    return 0;
}

int igCriMovieCodec_Pause(igCriMovieCodec *self, igMovieInfo *movie, int state) {
    igCriMovieData *data;

    data = AsCriMovieData((void *)movie->_userdata);
    if (data != 0) {
        movie->_state = state;
        if (movie->_type == kMovieTypeAdx) {
            if (ADXT_GetStatPause(Adxt(data)) == 0) {
                ADXT_Pause(Adxt(data), 1);
            }
        } else if (mwPlyIsPause(Player(data)) == 0) {
            mwPlyPause(Player(data), 1);
        }
        return 1;
    }
    return 0;
}

/* Brings the player's pause state in line with the movie's requested state. */
int igCriMovieCodec_SyncPauseState(igCriMovieCodecView *self, igMovieInfo *movie) {
    igCriMovieData *data = AsCriMovieData((void *)movie->_userdata);
    if (data != 0) {
        bool paused;
        if (movie->_type == kMovieTypeAdx) {
            paused = ADXT_GetStatPause(Adxt(data)) == 1;
        } else {
            paused = mwPlyIsPause(Player(data)) == 1;
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
            mwPlyGetCurFrm(Player(data), (struct MwsfdFrm *)&frame); /* MwsfdFrmObj: this unit's view of the frame (only bufadr read) */
            if (frame.bufadr != 0) {
                if (data->_macroFunction == 0) {
                    igMovieInfo_GetTiling(movie, &tileWidth, &tileHeight, &tilesAcross, &tilesDown);
                    data->_macroFunction = (int)&CriMovie_SubmitFrame;
                }
                shown = ((CriMovieFrameFunction)data->_macroFunction)(movie, frame.bufadr);
                mwPlyRelCurFrm(Player(data));
            }
            stat = mwPlyGetStat(Player(data));
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

igMetaObject *igCriMovieCodec_GetMeta(void)
{
    return g_igCriMovieCodec_metaObject;
}

igMetaObject *igCriMovieData_GetMeta(void)
{
    return g_igCriMovieData_metaObject;
}
