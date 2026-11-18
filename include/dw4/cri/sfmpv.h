#ifndef SFMPV_H
#define SFMPV_H

#include "dw4/cri/m2v.h"
#include "dw4/cri/sfd.h"
#include "dw4/sony/libmpeg.h"

typedef struct SfdPlanes {
    char *luma;
    char *chroma;
    char *base;
    short chromaStride;
    short lumaStride;
} SfdPlanes;

/* what one picture decode writes and predicts from (SDK SFMPV_MPVFRM) */
typedef struct SfdFrmPara {
    SfdPlanes ref[2];
    char *dst;
    M2vPicAtr *pic;
    int nfrm;
    int nbyte;
} SfdFrmPara;

/* The user data of a sequence header. */
typedef struct SfdUserData {
    char data[512];
    int size;
} SfdUserData;

/* The video stream's analysis in the seek record: whether it is done, the time of its first picture, the
 * time state then and the first sequence header's user data (sfmpv_SetMpvHd), replayed after a seek. */
typedef struct SfdRecVideo {
    int valid;
    int time;
    int unit;
    SfdTimeRec stamp;
    SfdUserData user;
} SfdRecVideo;

/* A decoded frame of the video driver (RE4's SFMPV_FRM): its state, its locks, its buffer, its display
 * time and the counts handed out with it (MwsfdFrmObj's errcnt, rcvcnt, concat_cnt, time_per_file and
 * time), its picture user data and attributes, and its PTS. */
typedef struct SfdSlot {
    int state;
    int refs;
    void *buf;               /* the frame's picture buffer */
    SfdTimeRec stamp;
    int ftime;               /* 56: the display time the frame is synchronised on */
    int tunit;               /* 60 */
    int errcnt;              /* 64 */
    int rcvcnt;              /* 68 */
    int concat_cnt;          /* 72 */
    int time_per_file;       /* 76 */
    int cat_time;            /* 80: the time with the files played before it */
    SfdSjChunk *blob;
    M2vPicAtr info;
    long long pts;           /* 216 */
    int frmcnt;              /* 224: SFMPVP_GetFrameCount when it was decoded */
    int pad228;
} SfdSlot;

typedef struct SfdBufPool {
    char *base;
    int count;
    int size;
    SfdSjChunk slot[18];
} SfdBufPool;

/* The video decoder's parameters (SFD_SetMpvPara, SFD_SetMpvParaTbl; RE4's SFMPV_PARA): the reference
 * frame size and area, the largest picture, the frame buffer size, count and area. The areas are aligned to
 * 64 bytes when set. */
typedef struct SfdMpvCond {
    int rfb_width;
    int rfb_height;
    int max_width;
    int max_height;
    int rfb_adr;
    int frm_width;
    int frm_height;
    int count;
    int ta_adr;
} SfdMpvCond;

typedef struct SfdMpvWorkBufs {
    int w[2];
} SfdMpvWorkBufs;

typedef struct SfdMpvFrameBufs {
    int w[16];
} SfdMpvFrameBufs;

typedef struct SfdIpuEntry {
    long long f0;
    long long f8;
    int f16;
    int f20;
} SfdIpuEntry;

/* One DMA tag quadword of the IPU input chain. */
typedef struct SfdDmaTag {
    long long tag;
    long long pad;
} SfdDmaTag;

/* The IPU input ring (Sony's vibuf.c, kept in sfmpvps2.c): the sector buffer and its DMA tags, the sectors
 * queued from headSct on, the bytes put and not yet queued, the saved DMA registers and the time stamps. */
typedef struct SfdIpuStream {
    void *base;
    SfdDmaTag *uncached;
    int sectors;
    int headSct;
    int queuedSct;
    int restBytes;
    int bytes;
    unsigned int r28;
    unsigned int r32;
    unsigned int r36;
    unsigned int r40;
    unsigned int r44;
    unsigned int r48;
    unsigned int r52;
    unsigned int r56;
    unsigned int r60;
    int sema;
    int active;          /* 68: the DMA may be restarted */
    long long totalBytes; /* 72 */
    SfdIpuEntry *entries;
    int entryCount;
    int f88;
    int f92;
} SfdIpuStream;

/* The sceMpeg/IPU decoder's work (SDK sfd_mpvp.c), inside the video work. */
typedef struct SfdIpuCtl {
    int enabled;
    int pscNext;         /* 4: picture start codes found by the put before the last */
    int pscFound;        /* 8: found by the last put */
    int pscCount;        /* 12: picture start codes waiting in the ring */
    char tail0;          /* 16: the last three bytes put, for a start code across two puts */
    char tail1;
    char tail2;
    char f19;
    int endRequest; /* 20 */
    int endSent;    /* 24 */
    int stopped;
    int value;
    int pad36;
    sceMpeg mpeg;        /* 40 */
    SfdIpuStream stream; /* 112 */
    sceMpegCbDataError error; /* 208: the last error the decoder reported */
} SfdIpuCtl;


/* The PTS complement state (RE4's pts_tmpref, pts_ofst, pts_max and ptsent): the temporal reference of
 * the picture that carried the last PTS, the frames of the GOPs since, the furthest picture seen in this
 * GOP, and that PTS queue entry. */
typedef struct SfdPtsComp {
    int tmpref;
    int ofst;
    int max;
    int pad12;
    SfdItem ptsent;
} SfdPtsComp;

/* The video driver's work (trn[2].hn, handle +9120; RE4's SFMPV_WORK). */
typedef struct SfdMpv {
    void *handle;
    SfdMpvCond cond;
    SfdMpvWorkBufs work;
    SfdMpvFrameBufs bufs;
    SfdSlot *current;
    unsigned int picstat;    /* 116: the decode state (2, 3, 5) */
    int dlmmask;             /* 120: the start codes the decoder accepts */
    int termflg;             /* 124 */
    int gopstat;             /* 128: SFMPVF_SetGopStat */
    int nskip;               /* 132: frames skipped in a row */
    int nconcat;             /* 136: files concatenated */
    M2vPicAtr pic;
    int last_ngop;           /* 268: the GOP count of the last picture */
    int newgop;              /* 272: the picture starts a new GOP */
    int limit;
    SfdPtsComp ptscomp;      /* 280 */
    int refidx_fwd;          /* 312: the forward and backward reference planes */
    int refidx_bwd;          /* 316 */
    SfdPlanes planes[2];
    SfdSlot *first;
    SfdSlot *second;
    SfdSlot *pendfrm;        /* 360: a B picture decoded into a standby frame */
    int skipret;             /* 364 */
    int dlmwait;             /* 368 */
    int tmpref_adj;          /* 372: a picture arrived out of temporal order */
    int slotCount;
    int pad380;
    SfdSlot slots[16];
    SfdBufPool pool;
    int pad4252;
    long long pts;           /* 4256: the PTS of the picture being decoded */
    SfdIpuCtl ipu;
} SfdMpv;

/* The MPEG picture type of a frame handed out (MWSFD converts it with mwl_convPtypeFromSFD). */
typedef enum SfdPicType {
    SFD_PICTYPE_I = 1,
    SFD_PICTYPE_P = 2,
    SFD_PICTYPE_B = 3
} SfdPicType;

/* The siting of the chroma samples against the luma, horizontally and vertically: the M2V decoder
 * reports 0 horizontally and 1 vertically (MPEG-2 4:2:0), the MPEG-1 decoder 1 and 1. An enum of
 * its own in CRI's header. */
typedef enum SfdChromaPos {
    SFD_CHROMAPOS_COSITED = 0,
    SFD_CHROMAPOS_CENTRE = 1
} SfdChromaPos;

typedef struct SfdFrameDetail {
    int f72;
    char pad76[4];
    long long pts;                      /* 80 */
    int picture_structure;              /* 88 */
    int chroma_format;                  /* 92 */
    int bit_rate;                       /* 96 */
    int vbv_buffer_size;                /* 100 */
    unsigned short display_horizontal_size; /* 104 */
    unsigned short display_vertical_size;   /* 106 */
    signed char progressive_frame;      /* 108 */
    signed char top_field_first;        /* 109 */
    signed char repeat_first_field;     /* 110 */
    unsigned char aspect_ratio_information; /* 111 */
    unsigned char constrained_parameters_flag; /* 112 */
    unsigned char frame_rate_extension_n; /* 113 */
    unsigned char frame_rate_extension_d; /* 114 */
    unsigned char profile_and_level_indication; /* 115 */
    unsigned char progressive_sequence; /* 116 */
    unsigned char low_delay;            /* 117 */
    unsigned char video_format;         /* 118 */
    unsigned char colour_description;   /* 119 */
    unsigned char colour_primaries;     /* 120 */
    unsigned char transfer_characteristics; /* 121 */
    unsigned char matrix_coefficients;  /* 122 */
    char pad123[5];
} SfdFrameDetail;

/* The frame information handed to the application. Its fields are enums, pointers and a union as
 * in CRI's header: the details from 72 on are also the seven words MWSFD hands on unchanged, and
 * a store through the union conflicts with every load. The counts at 36..52 become MwsfdFrmObj's
 * errcnt, rcvcnt, concat_cnt, time_per_file and time. */
typedef struct SfdFrameInfo {
    int width;               /* 0 */
    int height;              /* 4 */
    int x_mb;                /* 8 */
    int y_mb;                /* 12 */
    SfdPicType picType;      /* 16 */
    int time;                /* 20: the frame's time */
    int unit;                /* 24 */
    SfdBufFmt bufFmt;        /* 28 */
    void *buf;               /* 32 */
    int errcnt;              /* 36 */
    int rcvcnt;              /* 40 */
    int concat_cnt;          /* 44 */
    int time_per_file;       /* 48 */
    int cat_time;            /* 52 */
    SfdSjChunk *picUsr;        /* 56 */
    SfdChromaPos chromaPosH; /* 60 */
    int chromaPosV;          /* 64 */
    char pad68[4];
    union {
        SfdFrameDetail detail;
        long long words[7];
    } tail;                  /* 72 */
} SfdFrameInfo;

/* A frame of the handle's frame buffer: whether it is handed out, and the information handed out with it. */
typedef struct SfdVfrm {
    int used;                /* 0 */
    int f4;
    SfdFrameInfo inf;        /* 8 */
} SfdVfrm;

#endif
