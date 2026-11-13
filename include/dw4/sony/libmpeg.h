/* libmpeg (Sony runtime 2.8.0): the public stream handle and the decoder state it points at. */
#ifndef DW4_SONY_LIBMPEG_H
#define DW4_SONY_LIBMPEG_H

typedef struct sceMpeg {
    int width;
    int height;
    int frameCount;
    long pts;
    long dts;
    unsigned long flags;
    long pts2nd;
    long dts2nd;
    unsigned long flags2nd;
    struct _sceMpegDecoder *sys;
} sceMpeg;

typedef enum {
    sceMpegCbError,
    sceMpegCbNodata,
    sceMpegCbStopDMA,
    sceMpegCbRestartDMA,
    sceMpegCbBackground,
    sceMpegCbTimeStamp,
    sceMpegCbStr,
    sceMpegCbNum
} sceMpegCbType;

/* The callback records; each starts with its type. */
typedef struct {
    sceMpegCbType type;
    char *errMessage;
} sceMpegCbDataError;

typedef struct {
    sceMpegCbType type;
    long pts;
    long dts;
} sceMpegCbDataTimeStamp;

typedef struct {
    sceMpegCbType type;
    unsigned char *header;
    unsigned char *data;
    unsigned int len;
    long pts;
    long dts;
} sceMpegCbDataStr;

typedef union {
    sceMpegCbType type;
    sceMpegCbDataError error;
    sceMpegCbDataTimeStamp ts;
    sceMpegCbDataStr str;
} sceMpegCbData;

typedef int (*sceMpegCallback)(sceMpeg *mp, sceMpegCbData *cbdata, void *anyData);

typedef struct {
    sceMpegCallback func;
    void *data;
    void *gp; /* the registering context's $gp, restored around the call */
} _sceMpegCallbackSlot;

/* The bump allocator over the work area handed to sceMpegCreate. */
typedef struct {
    char *start;
    int size;
    char *cur;
    char *dynamic; /* where the per-stream allocations begin */
} _sceMpegAlalc;

/* A decoded picture in the work area. */
typedef struct {
    char *base;
    int width;
    int height;
    int mb_width;
    int mb_height;
    int pad_20;
    long pts;                              /* 24: -1 when the stream gave none */
    long dts;
    int decoded;                           /* 40 */
    int picture_structure;
    int picture_coding_type;
    int progressive_sequence;
    int progressive_frame;
    int top_field_first;
    int repeat_first_field;                /* 64 */
    int center_offsets[6];                 /* 68 */
    int disp_width;                        /* 92 */
    int disp_height;
} _sceMpegPicture;

/* The pictures one picture structure (frame, top field, bottom field) works with. */
typedef struct {
    _sceMpegPicture *ref_image;
    _sceMpegPicture *prev_image;
    _sceMpegPicture *decode;
    _sceMpegPicture *image;
} _sceMpegPictureSlot;

/* One of the two scratchpad halves a macroblock is decoded through. */
typedef struct {
    unsigned int src;
    unsigned int dst;                      /* coefficients, cleared before BDEC */
    char pad_8[288];
    char *dest;                            /* 0x128: where the macroblock lands */
    int pad_12c;
    int intra;
    int skipped;
    int predicted;
    int empty;
} _sceMpegSprBuffer;

#define MPEG_TOP_FIELD 1
#define MPEG_BOTTOM_FIELD 2
#define MPEG_FRAME_PICTURE 3

typedef struct _sceMpegDecoder {
    int is_end;                            /* 0 */
    int ref_count;                         /* pictures held for output */
    int seq_state;
    _sceMpegCallbackSlot callbacks[sceMpegCbNum];
    char *spare_buffer;                    /* 96: 2048 bytes sceMpegCreate allocates, read by nothing */
    int spare;
    unsigned int ipu_dma_env[9];           /* 104: the IPU DMA state sceIpuStopDMA saves */
    int has_pts_gap;                       /* 140 */
    long pts_gap;
    int last_pts;
    int pad_156;
    long field_count;                      /* fields the current frame is shown for */
    int half_field;
    int ni;                                /* 172: pictures to decode per type, -1 for all */
    int np;
    int nb;
    int count_i;
    int count_p;
    int count_b;
    int first_frame_no;                    /* 196 */
    int rgb32;                             /* output through colour-space conversion */
    int center_offsets[6];
    int disp_width;                        /* 228 */
    int disp_height;
    int first_picture_structure;
    unsigned int image_buff;
    int image_width;                       /* 244: pixels, 0 for a plain buffer */
    int image_height;
    int image_size;                        /* macroblocks the buffer holds */
    int set_broken_link;                   /* 256 */
    int pad_260;
    long ptm;
    int ptm_state;
    char *frame_buffers[3];                /* 276: the decoded frames' pixels, allocated per sequence */
    _sceMpegAlalc alalc;                   /* 288: the rest of the work area */
    int frame_no;                          /* 304 */
    int error;
    int second_field;
    int h_size;
    int v_size;
    int mb_width;                          /* 324 */
    int mb_height;
    int bit_rate;
    int vbv_buffer_size;
    int progressive_sequence;
    int chroma_format;                     /* 344 */
    int matrix_coefficients;
    int display_h_size;
    int display_v_size;
    int picture_coding_type;               /* 360 */
    int full_pel_forward_vector;
    int forward_f_code;
    int full_pel_backward_vector;
    int backward_f_code;
    int f_code[2][2];                      /* 380 */
    int picture_structure;                 /* 396 */
    int top_field_first;
    int frame_pred_frame_dct;
    int concealment_motion_vectors;
    int repeat_first_field;
    int progressive_frame;                 /* 416 */
    int frame_center_horizontal_offset[3];
    int frame_center_vertical_offset[3];
    int closed_gop;                        /* 444 */
    int broken_link;
    int temporal_order;
    int dc_reset;                          /* 456 */
    int quantiser_scale_code;
    _sceMpegPictureSlot slots[3];          /* 464: frame, top field, bottom field */
    _sceMpegPicture pictures[9];           /* 512: the slots' pictures */
    _sceMpegSprBuffer spr[2];              /* 1448 */
    int mb_buffer;                         /* 2088 */
    int mb_count;
    int ipu_cmd_pending;                   /* 2096 */
    unsigned int mc_work;                  /* 2100: scratchpad area of the motion-compensation kernels */
    int stopped;                           /* 2104 */
    int pad_2108;
    long pts;                              /* 2112 */
    long dts;
    unsigned int bits;                     /* 2128 */
    int bit_count;
    int load_intra_quantiser_matrix;       /* 2136 */
    int load_non_intra_quantiser_matrix;
    int mpeg2;                             /* 2144 */
    int temporal_base;
    int temporal_max;
    int gop_started;
    sceMpeg *mp;                           /* 2160 */
    char pad_2164[2092];
    int abort;                             /* 4256 */
    char pad_4260[28];
} _sceMpegDecoder;

void _sceMpegError(_sceMpegDecoder *dec, char *message);
void _sceMpegError1(_sceMpegDecoder *dec, char *format, int value);
int _sceMpegDispatchMpegCallback(sceMpeg *mp, sceMpegCbData *cbdata);
int _sceMpegDispatchMpegCbNodata(sceMpeg *mp);
void _outputFrame(_sceMpegDecoder *dec, _sceMpegPicture *picture, int frameNo);
void _outputFieldPair(_sceMpegDecoder *dec, _sceMpegPicture *top, _sceMpegPicture *bottom, int frameNo);
void _flushLastPicture(_sceMpegDecoder *dec);
char *_sceMpegAlalcAlloc(_sceMpegDecoder *dec, _sceMpegAlalc *alalc, int size, unsigned int align);

#endif
