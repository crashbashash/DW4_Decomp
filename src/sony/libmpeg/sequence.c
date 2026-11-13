#include "dw4/sony/libmpeg.h"

int DIntr(void);
int EIntr(void);
void _ipuSetMpeg1(int mpeg1);
void _ipuCommand(_sceMpegDecoder *dec, unsigned int command);
void _sceMpegWaitIpuIdle(_sceMpegDecoder *dec);
unsigned int _ipuGetBits(_sceMpegDecoder *dec, int n);
void _extensionAndUserData(_sceMpegDecoder *dec);
void _initSeq(sceMpeg *mp);
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
