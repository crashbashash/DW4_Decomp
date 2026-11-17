#include "dw4/sony/libmpeg.h"
#include "dw4/sony/libkernl.h"

void _initSeq(sceMpeg *mp);
void _setFieldPointers(_sceMpegPicture *p0, _sceMpegPicture *p1, _sceMpegPicture *p2, _sceMpegPicture *p3,
                       _sceMpegPicture *p4, _sceMpegPicture *p5, _sceMpegPicture *p6, _sceMpegPicture *p7,
                       _sceMpegPicture *p8, char *buffer0, char *buffer1, char *buffer2, int width, int height);
void _loadQuantMatrix(_sceMpegDecoder *dec, unsigned int command, unsigned char *matrix);

#define IPU_SETIQ_INTRA 0x50000000
#define IPU_SETIQ_NON_INTRA 0x58000000

/* The MPEG-2 default quantiser matrices, in zigzag order. */
static unsigned char _defaultIntraMatrix[64] = {
    8, 16, 16, 19, 16, 19, 22, 22, 22, 22, 22, 22, 26, 24, 26, 27,
    27, 27, 26, 26, 26, 26, 27, 27, 27, 29, 29, 29, 34, 34, 34, 29,
    29, 29, 27, 27, 29, 29, 32, 32, 34, 34, 37, 38, 37, 35, 35, 34,
    35, 38, 38, 40, 40, 40, 48, 48, 46, 46, 56, 56, 58, 69, 69, 83,
};
static unsigned char _defaultNonIntraMatrix[64] = {
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
};

int _setPictureSize(_sceMpegPicture *picture, int width, int height) {
    picture->width = width;
    picture->mb_width = width >> 4;
    picture->height = height;
    picture->mb_height = height >> 4;
    return 1;
}

/* sequence_header(): the sizes and rates, and the quantiser matrices loaded into the IPU from the
 * stream or from the defaults. */
void _sequenceHeader(_sceMpegDecoder *dec) {
    unsigned int bits;

    dec->first_picture_structure = 0;
    bits = _ipuGetBits(dec, 32);
    dec->h_size = bits >> 20;
    dec->v_size = (bits >> 8) & 0xfff;
    if (dec->v_size > 2800) _sceMpegError(dec, "vertical size > 2800");
    bits = _ipuGetBits(dec, 30);
    dec->bit_rate = bits >> 12;
    dec->vbv_buffer_size = (bits >> 1) & 0x3ff;
    if ((dec->load_intra_quantiser_matrix = _ipuGetBits(dec, 1)) != 0) {
        _sceMpegWaitIpuIdle(dec);
        _ipuCommand(dec, IPU_SETIQ_INTRA);
        _sceMpegWaitIpuIdle(dec);
    } else {
        _loadQuantMatrix(dec, IPU_SETIQ_INTRA, _defaultIntraMatrix);
    }
    if ((dec->load_non_intra_quantiser_matrix = _ipuGetBits(dec, 1)) != 0) {
        _sceMpegWaitIpuIdle(dec);
        _ipuCommand(dec, IPU_SETIQ_NON_INTRA);
        _sceMpegWaitIpuIdle(dec);
    } else {
        _loadQuantMatrix(dec, IPU_SETIQ_NON_INTRA, _defaultNonIntraMatrix);
    }
    _extensionAndUserData(dec);
    _initSeq(dec->mp);
}

/* Sizes the pictures for the sequence just parsed and lays the three frame buffers out when they change. */
void _initSeq(sceMpeg *mp)
{
    _sceMpegDecoder *dec = mp->sys;
    int width, height;
    unsigned int bytes;

    if (!dec->mpeg2) {
        dec->progressive_sequence = 1;
        dec->chroma_format = 1;
        dec->progressive_frame = 1;
        dec->picture_structure = MPEG_FRAME_PICTURE;
        dec->frame_pred_frame_dct = 1;
        dec->matrix_coefficients = 5;
    }
    dec->mb_width = (dec->h_size + 15) >> 4;
    dec->mb_height = dec->mpeg2 && !dec->progressive_sequence ? (dec->v_size + 31) >> 5 << 1 : (dec->v_size + 15) >> 4;
    height = dec->mb_height << 4;
    width = dec->mb_width << 4;
    if (width == mp->width && height == mp->height) {
        return;
    }
    mp->width = width;
    mp->height = height;
    bytes = (unsigned int)(width * 384 * height) >> 8;
    _sceMpegAlalcFree(&dec->alalc);
    dec->frame_buffers[0] = _sceMpegAlalcAlloc(dec, &dec->alalc, bytes, 64);
    dec->frame_buffers[1] = _sceMpegAlalcAlloc(dec, &dec->alalc, bytes, 64);
    dec->frame_buffers[2] = _sceMpegAlalcAlloc(dec, &dec->alalc, bytes, 64);
    _setFieldPointers(&dec->pictures[0], &dec->pictures[1], &dec->pictures[2], &dec->pictures[3], &dec->pictures[4],
                      &dec->pictures[5], &dec->pictures[6], &dec->pictures[7], &dec->pictures[8],
                      dec->frame_buffers[0], dec->frame_buffers[1], dec->frame_buffers[2], width, height);
    _setPictureSize(&dec->pictures[0], width, height);
    _setPictureSize(&dec->pictures[1], width, height);
    _setPictureSize(&dec->pictures[2], width, height);
    _setPictureSize(&dec->pictures[3], width, height / 2);
    _setPictureSize(&dec->pictures[4], width, height / 2);
    _setPictureSize(&dec->pictures[5], width, height / 2);
    _setPictureSize(&dec->pictures[6], width, height / 2);
    _setPictureSize(&dec->pictures[7], width, height / 2);
    _setPictureSize(&dec->pictures[8], width, height / 2);
}

/* matching construct: decomp-permuter — an inline helper rather than a macro keeps the three bottom-field
   offsets as separate multiplies */
static __inline__ char *_uncached(char *p)
{
    return (char *)(((unsigned int)p & 0x0FFFFFFF) | 0x20000000);
}

void _setFieldPointers(_sceMpegPicture *p0, _sceMpegPicture *p1, _sceMpegPicture *p2, _sceMpegPicture *p3,
                       _sceMpegPicture *p4, _sceMpegPicture *p5, _sceMpegPicture *p6, _sceMpegPicture *p7,
                       _sceMpegPicture *p8, char *buffer0, char *buffer1, char *buffer2, int width, int height)
{
    p0->base = _uncached(buffer0);
    p1->base = _uncached(buffer1);
    p2->base = _uncached(buffer2);
    p3->base = _uncached(buffer0);
    p4->base = _uncached(buffer1);
    p5->base = _uncached(buffer2);
    p6->base = _uncached(buffer0 + width * height / 512 * 384);
    p7->base = _uncached(buffer1 + width * height / 512 * 384);
    p8->base = _uncached(buffer2 + width * height / 512 * 384);
}

/* Sends a 64-byte matrix to the IPU and loads it with `command`, with the stream's DMA stopped
 * around it. */
void _loadQuantMatrix(_sceMpegDecoder *dec, unsigned int command, unsigned char *matrix) {
    sceMpegCbData cbdata;
    int intr;

    cbdata.type = sceMpegCbStopDMA;
    _sceMpegDispatchMpegCallback(dec->mp, &cbdata);
    _sceMpegWaitIpuIdle(dec);
    *(volatile unsigned int *)0x10002000 = 0;
    _sceMpegWaitIpuIdle(dec);
    intr = DIntr();
    *(volatile unsigned int *)0x1000B410 = (unsigned int)matrix & 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000B420 = 4;
    *(volatile unsigned int *)0x1000B400 = 0x101;
    if (intr) {
        EIntr();
    }
    _ipuCommand(dec, command);
    _sceMpegWaitIpuIdle(dec);
    cbdata.type = sceMpegCbRestartDMA;
    _sceMpegDispatchMpegCallback(dec->mp, &cbdata);
}

/* sequence_extension(): the stream is MPEG-2, so the IPU leaves MPEG-1 mode and the sizes and
 * rates gain their high bits. */
void _sequenceExtension(_sceMpegDecoder *dec) {
    unsigned int bits;
    unsigned int profileLevel, bitRateExt, hSizeExt, vSizeExt, vbvExt;

    dec->mpeg2 = 1;
    _ipuSetMpeg1(0);
    bits = _ipuGetBits(dec, 28);
    bitRateExt = (bits >> 1) & 0xfff;
    dec->chroma_format = (bits >> 17) & 3;
    vSizeExt = (bits >> 13) & 3;
    hSizeExt = (bits >> 15) & 3;
    if (dec->chroma_format != 1) _sceMpegError(dec, "_chroma_format needs to be 1: 420");
    dec->progressive_sequence = (bits >> 19) & 1;
    profileLevel = bits >> 20;
    vbvExt = _ipuGetBits(dec, 16) >> 8;
    if (profileLevel != 0x48 && profileLevel != 0x58 && profileLevel != 0x44) {
        _sceMpegError(dec, "Unsupported profile/level");
    }
    dec->h_size = (hSizeExt << 12) | (dec->h_size & 0xfff);
    dec->v_size = (vSizeExt << 12) | (dec->v_size & 0xfff);
    dec->bit_rate += bitRateExt << 18;
    dec->vbv_buffer_size += vbvExt << 10;
}

void _sequenceDisplayExtension(_sceMpegDecoder *dec) {
    _ipuGetBits(dec, 3); /* video_format */
    if (_ipuGetBits(dec, 1)) {
        _ipuGetBits(dec, 8); /* colour_primaries */
        _ipuGetBits(dec, 8); /* transfer_characteristics */
        dec->matrix_coefficients = _ipuGetBits(dec, 8);
    }
    dec->display_h_size = _ipuGetBits(dec, 14);
    _ipuGetBits(dec, 1); /* marker_bit */
    dec->display_v_size = _ipuGetBits(dec, 14);
}

void _sequenceScalableExtension(_sceMpegDecoder *dec) {
    _sceMpegError(dec, "_sequenceScalableExtension() is not implemented");
}

void _unknownExtension(_sceMpegDecoder *dec) {
    _sceMpegError(dec, "Unknown Extension");
}

void _pictureSpatialScalableExtension(_sceMpegDecoder *dec) {
    _sceMpegError(dec, "_pictureSpatialScalableExtension is not supported");
}

void _pictureTemporalScalableExtension(_sceMpegDecoder *dec) {
    _sceMpegError(dec, "_pictureTemporalScalableExtension is not supported");
}
