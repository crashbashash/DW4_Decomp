/* libmpeg ext: start codes, the picture-level headers and extensions, and the GOP header. */
#include "dw4/sony/libmpeg.h"

#define IPU_CTRL (*(volatile unsigned int *)0x10002010)
#define IPU_BP (*(volatile int *)0x10002020)

#define IPU_CTRL_IDP_SHIFT 16
#define IPU_CTRL_AS_SHIFT 20
#define IPU_CTRL_IVF_SHIFT 21
#define IPU_CTRL_QST_SHIFT 22

#define IPU_SETIQ_INTRA 0x50000000
#define IPU_SETIQ_NON_INTRA 0x58000000

#define PICTURE_START_CODE 0x100
#define USER_DATA_START_CODE 0x1b2
#define SEQUENCE_HEADER_CODE 0x1b3
#define EXTENSION_START_CODE 0x1b5
#define SEQUENCE_END_CODE 0x1b7
#define GROUP_START_CODE 0x1b8

#define B_TYPE 3

void _sceMpegWaitIpuIdle(_sceMpegDecoder *dec);
void _ipuCommand(_sceMpegDecoder *dec, unsigned int cmd);
unsigned int _ipuShowBits(_sceMpegDecoder *dec, int n);
void _ipuFlushBits(_sceMpegDecoder *dec, int n);
unsigned int _ipuGetBits(_sceMpegDecoder *dec, int n);
void _sequenceHeader(_sceMpegDecoder *dec);
void _unknownExtension(_sceMpegDecoder *dec);
void _sequenceExtension(_sceMpegDecoder *dec);
void _sequenceDisplayExtension(_sceMpegDecoder *dec);
void _sequenceScalableExtension(_sceMpegDecoder *dec);
void _pictureSpatialScalableExtension(_sceMpegDecoder *dec);
void _pictureTemporalScalableExtension(_sceMpegDecoder *dec);

void _extraBitInformation(_sceMpegDecoder *dec);
void _extensionAndUserData(_sceMpegDecoder *dec);
void _pictureHeader(_sceMpegDecoder *dec);
void _groupOfPicturesHeader(_sceMpegDecoder *dec);
void _temporalOrder(_sceMpegDecoder *dec, int temporal_reference);
void _quantMatrixExtension(_sceMpegDecoder *dec);
void _pictureDisplayExtension(_sceMpegDecoder *dec);
void _copyrightExtension(_sceMpegDecoder *dec);
void _pictureCodingExtension(_sceMpegDecoder *dec);

/* Aligns to a byte and skips to the next 0x000001 start-code prefix. */
void _nextStartCode(_sceMpegDecoder *dec)
{
    int n;

    _sceMpegWaitIpuIdle(dec);
    n = -(IPU_BP & 7) & 7;
    if (n != 0) {
        _ipuFlushBits(dec, n);
    }
    while (_ipuShowBits(dec, 24) != 1 && !dec->abort) {
        _ipuFlushBits(dec, 8);
    }
}

/* The slice header after slice_start_code; returns 0 (slice_vertical_position_extension is never sent). */
int _sliceHeader(_sceMpegDecoder *dec)
{
    dec->quantiser_scale_code = _ipuGetBits(dec, 5);
    if (_ipuGetBits(dec, 1) != 0) {
        _ipuGetBits(dec, 1);  /* intra_slice */
        _ipuFlushBits(dec, 7); /* reserved_bits */
        _extraBitInformation(dec);
    }
    return 0;
}

/* Reads headers up to the next picture; returns its coding type, 0 at the end of the sequence and -1 when
   aborted. The picture's time stamps come from the stream's callback. */
int _sceMpegNextHeader(_sceMpegDecoder *dec)
{
    unsigned int code;
    sceMpegCbData cb;

    for (;;) {
        if (dec->abort) {
            return -1;
        }
        _nextStartCode(dec);
        code = _ipuGetBits(dec, 32);
        switch (code) {
        case SEQUENCE_HEADER_CODE:
            _sequenceHeader(dec);
            break;
        case GROUP_START_CODE:
            _groupOfPicturesHeader(dec);
            break;
        case PICTURE_START_CODE:
            _pictureHeader(dec);
            cb.type = sceMpegCbTimeStamp;
            cb.ts.pts = -1;
            cb.ts.dts = -1;
            _sceMpegDispatchMpegCallback(dec->mp, &cb);
            dec->pts = cb.ts.pts;
            dec->dts = cb.ts.dts;
            return dec->picture_coding_type;
        case SEQUENCE_END_CODE:
            return 0;
        }
    }
}

void _pictureHeader(_sceMpegDecoder *dec)
{
    int temporal_reference;

    temporal_reference = _ipuGetBits(dec, 10);
    dec->picture_coding_type = _ipuGetBits(dec, 3);
    _ipuGetBits(dec, 16); /* vbv_delay */
    if ((unsigned int)(dec->picture_coding_type - 2) < 2) {
        dec->full_pel_forward_vector = _ipuGetBits(dec, 1);
        dec->forward_f_code = _ipuGetBits(dec, 3);
    }
    if (dec->picture_coding_type == B_TYPE) {
        dec->full_pel_backward_vector = _ipuGetBits(dec, 1);
        dec->backward_f_code = _ipuGetBits(dec, 3);
    }
    _extraBitInformation(dec);
    _extensionAndUserData(dec);
    _temporalOrder(dec, temporal_reference);
}

/* Extensions by extension_start_code_identifier; user data is skipped. */
void _extensionAndUserData(_sceMpegDecoder *dec)
{
    void (*extension[11])(_sceMpegDecoder *dec) = {
        _unknownExtension,
        _sequenceExtension,
        _sequenceDisplayExtension,
        _quantMatrixExtension,
        _copyrightExtension,
        _sequenceScalableExtension,
        _unknownExtension,
        _pictureDisplayExtension,
        _pictureCodingExtension,
        _pictureSpatialScalableExtension,
        _pictureTemporalScalableExtension,
    };
    unsigned int code;
    unsigned int id;

    _nextStartCode(dec);
    while ((code = _ipuShowBits(dec, 32)) == EXTENSION_START_CODE || code == USER_DATA_START_CODE) {
        if (code == EXTENSION_START_CODE) {
            _ipuFlushBits(dec, 32);
            id = _ipuGetBits(dec, 4);
            id = id > 10 ? 0 : id;
            extension[id](dec);
            _nextStartCode(dec);
        } else {
            _ipuFlushBits(dec, 32);
            _nextStartCode(dec);
        }
    }
}

void _pictureCodingExtension(_sceMpegDecoder *dec)
{
    dec->f_code[0][0] = _ipuGetBits(dec, 4);
    dec->f_code[0][1] = _ipuGetBits(dec, 4);
    dec->f_code[1][0] = _ipuGetBits(dec, 4);
    dec->f_code[1][1] = _ipuGetBits(dec, 4);
    IPU_CTRL = (IPU_CTRL & ~(3 << IPU_CTRL_IDP_SHIFT)) | (_ipuGetBits(dec, 2) << IPU_CTRL_IDP_SHIFT);
    dec->picture_structure = _ipuGetBits(dec, 2);
    if (dec->first_picture_structure == 0) {
        dec->first_picture_structure = dec->picture_structure;
    }
    dec->top_field_first = _ipuGetBits(dec, 1);
    dec->frame_pred_frame_dct = _ipuGetBits(dec, 1);
    dec->concealment_motion_vectors = _ipuGetBits(dec, 1);
    IPU_CTRL = (IPU_CTRL & ~(1 << IPU_CTRL_QST_SHIFT)) | (_ipuGetBits(dec, 1) << IPU_CTRL_QST_SHIFT);
    IPU_CTRL = (IPU_CTRL & ~(1 << IPU_CTRL_IVF_SHIFT)) | (_ipuGetBits(dec, 1) << IPU_CTRL_IVF_SHIFT);
    IPU_CTRL = (IPU_CTRL & ~(1 << IPU_CTRL_AS_SHIFT)) | (_ipuGetBits(dec, 1) << IPU_CTRL_AS_SHIFT);
    dec->repeat_first_field = _ipuGetBits(dec, 1);
    _ipuGetBits(dec, 1); /* chroma_420_type */
    dec->progressive_frame = _ipuGetBits(dec, 1);
    if (_ipuGetBits(dec, 1)) { /* composite_display_flag */
        _ipuGetBits(dec, 1);
        _ipuGetBits(dec, 3);
        _ipuGetBits(dec, 1);
        _ipuGetBits(dec, 7);
        _ipuGetBits(dec, 8);
    }
}

void _extraBitInformation(_sceMpegDecoder *dec)
{
    while (_ipuGetBits(dec, 1) != 0) {
        _ipuFlushBits(dec, 8);
    }
}

/* The picture's display order: temporal_reference counts from the GOP's start; after a GOP whose first
   picture is a B picture with a negative reference, that picture comes 1024 later. */
void _temporalOrder(_sceMpegDecoder *dec, int temporal_reference)
{
    int fresh = 0;
    int m = 0;

    if (dec->picture_coding_type != B_TYPE && temporal_reference != 0) {
        if (temporal_reference < 0) {
            fresh = dec->gop_started == 0;
        }
        dec->gop_started = 0;
        m = temporal_reference;
    }
    dec->temporal_order = dec->temporal_base + temporal_reference;
    if (fresh && m >= temporal_reference) {
        dec->temporal_order = dec->temporal_base + temporal_reference + 1024;
    }
    {
        int max = dec->temporal_max;

        if (max < dec->temporal_order)
            max = dec->temporal_order;
        dec->temporal_max = max;
    }
}

void _groupOfPicturesHeader(_sceMpegDecoder *dec)
{
    dec->set_broken_link = 0;
    dec->gop_started = 1;
    dec->temporal_base = dec->temporal_max + 1;
    _ipuGetBits(dec, 1); /* time_code: drop_flag, hours, minutes, marker, seconds, pictures */
    _ipuGetBits(dec, 5);
    _ipuGetBits(dec, 6);
    _ipuGetBits(dec, 1);
    _ipuGetBits(dec, 6);
    _ipuGetBits(dec, 6);
    dec->closed_gop = _ipuGetBits(dec, 1);
    dec->broken_link = _ipuGetBits(dec, 1);
    _extensionAndUserData(dec);
}

/* The IPU reads the matrices straight from the stream with SETIQ. */
void _quantMatrixExtension(_sceMpegDecoder *dec)
{
    if ((dec->load_intra_quantiser_matrix = _ipuGetBits(dec, 1)) != 0) {
        _sceMpegWaitIpuIdle(dec);
        _ipuCommand(dec, IPU_SETIQ_INTRA);
        _sceMpegWaitIpuIdle(dec);
    }
    if ((dec->load_non_intra_quantiser_matrix = _ipuGetBits(dec, 1)) != 0) {
        _sceMpegWaitIpuIdle(dec);
        _ipuCommand(dec, IPU_SETIQ_NON_INTRA);
        _sceMpegWaitIpuIdle(dec);
    }
    if (_ipuGetBits(dec, 1) != 0) {
        _sceMpegError(dec, "load_chroma_intra_quantizer_matrix == 1");
    }
    if (_ipuGetBits(dec, 1) != 0) {
        _sceMpegError(dec, "load_chroma_non_intra_quantizer_matrix == 1");
    }
}

void _pictureDisplayExtension(_sceMpegDecoder *dec)
{
    int i;
    int number_of_frame_center_offsets;

    if (dec->progressive_sequence) {
        if (dec->repeat_first_field) {
            if (dec->top_field_first)
                number_of_frame_center_offsets = 3;
            else
                number_of_frame_center_offsets = 2;
        } else
            number_of_frame_center_offsets = 1;
    } else {
        if (dec->picture_structure != MPEG_FRAME_PICTURE)
            number_of_frame_center_offsets = 1;
        else {
            if (dec->repeat_first_field)
                number_of_frame_center_offsets = 3;
            else
                number_of_frame_center_offsets = 2;
        }
    }

    for (i = 0; i < number_of_frame_center_offsets; i++) {
        dec->frame_center_horizontal_offset[i] = _ipuGetBits(dec, 16);
        _ipuGetBits(dec, 1); /* marker_bit */
        dec->frame_center_vertical_offset[i] = _ipuGetBits(dec, 16);
        _ipuGetBits(dec, 1);
    }
}

/* Read and dropped. */
void _copyrightExtension(_sceMpegDecoder *dec)
{
    _ipuGetBits(dec, 1); /* copyright_flag */
    _ipuGetBits(dec, 8); /* copyright_identifier */
    _ipuGetBits(dec, 1); /* original_or_copy */
    _ipuGetBits(dec, 7); /* reserved */
    _ipuGetBits(dec, 1);
    _ipuGetBits(dec, 20); /* copyright_number_1 */
    _ipuGetBits(dec, 1);
    _ipuGetBits(dec, 22); /* copyright_number_2 */
    _ipuGetBits(dec, 1);
    _ipuGetBits(dec, 22); /* copyright_number_3 */
}
