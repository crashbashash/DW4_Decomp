#include "dw4/sony/libmpeg.h"

int DIntr(void);
int EIntr(void);
int sprintf(char *buf, const char *format, ...);
long __muldi3(long a, long b);
void _cscStoreImage(_sceMpegDecoder *dec, _sceMpegPicture *picture);

/* The fields a frame is shown for, by its repeat_first_field and top_field_first flags. */
static unsigned int _fieldCounts[16] = {2, 0, 2, 0, 2, 3, 2, 3, 0, 0, 0, 0, 2, 4, 0, 6};

int _checkImageBuffer(_sceMpegDecoder *dec, _sceMpegPicture *picture) {
    char message[256];
    int fits;

    if (dec->image_height) {
        fits = dec->image_width >= picture->width && dec->image_height >= picture->height;
    } else {
        fits = dec->image_size >= picture->mb_width * picture->mb_height;
    }
    if (!fits) {
        sprintf(message, "Too small buffer size for %dx%d picture\n", picture->width, picture->height);
        _sceMpegError(dec, message);
    }
    return fits;
}

/* Copies a raw 8-bit picture to the image buffer through the scratchpad, one macroblock column at a time. */
void _cpr8(_sceMpegDecoder *dec, _sceMpegPicture *picture) {
    int fields;
    unsigned int src = (unsigned int)picture->base & 0x0FFFFFFF;
    unsigned int dst = dec->image_buff & 0x0FFFFFFF;
    unsigned int out;
    int srcstep, dststep, qwc;
    int f, i, intr;

    if (dec->picture_structure == MPEG_FRAME_PICTURE || dec->image_height == 0) {
        srcstep = picture->mb_height * 384;
        qwc = srcstep >> 4;
        if (dec->image_height) {
            dststep = (dec->image_height >> 4) * 384;
        } else {
            dststep = srcstep;
        }
        fields = 1;
    } else {
        dststep = (dec->image_height >> 4) * 192;
        srcstep = (picture->mb_height >> 1) * 384;
        fields = 2;
        qwc = srcstep >> 4;
    }
    for (f = 0; f < fields; f++) {
        out = dst;
        for (i = 0; i < picture->mb_width; i++) {
            intr = DIntr();
            *(volatile unsigned int *)0x1000D480 = 0;
            *(volatile unsigned int *)0x1000D410 = src;
            *(volatile unsigned int *)0x1000D420 = qwc;
            *(volatile unsigned int *)0x1000D400 = 0x101;
            if (intr) {
                EIntr();
            }
            while (*(volatile unsigned int *)0x1000D400 & 0x100);
            intr = DIntr();
            *(volatile unsigned int *)0x1000D080 = 0;
            *(volatile unsigned int *)0x1000D010 = out;
            *(volatile unsigned int *)0x1000D020 = qwc;
            *(volatile unsigned int *)0x1000D000 = 0x100;
            if (intr) {
                EIntr();
            }
            while (*(volatile unsigned int *)0x1000D000 & 0x100);
            while (*(volatile unsigned int *)0x1000D020);
            out += dststep;
            src += srcstep;
        }
        dst += dec->image_size * 192;
    }
}

void _endPicture(_sceMpegDecoder *dec) {
    if (dec->seq_state != 2) {
        dec->seq_state = 2;
        dec->first_frame_no = dec->frame_no;
    }
    dec->stopped = 1;
}

/* The time stamps and flags of a picture: a picture without its own pts gets one from the last pts
 * and the default gap, and a pts set through _sceMpegSetPtm replaces it once. */
void _pictureTimeStamp(_sceMpegDecoder *dec, _sceMpegPicture *picture, long *pts, long *dts, long *flags) {
    if (dec->has_pts_gap && picture->pts < 0 && dec->last_pts >= 0) {
        int half = dec->half_field;
        int count = dec->field_count;
        int odd = count & 1;
        int carry = odd & (dec->pts_gap & 1) & (half & 1);
        *pts = dec->last_pts + ((int)((dec->pts_gap * count) >> 1) + carry);
        if (odd & dec->pts_gap) {
            dec->half_field = half + 1;
        }
    } else {
        *pts = picture->pts;
    }
    if (dec->ptm_state == 2 && dec->ptm >= 0) {
        *pts = dec->ptm;
        dec->ptm_state = 0;
        dec->ptm = -1;
    }
    *dts = picture->dts;
    *flags = (long)picture->progressive_sequence << 8 | (long)picture->progressive_frame << 7
           | (long)picture->top_field_first << 6 | (long)picture->repeat_first_field << 5
           | (long)picture->picture_coding_type << 3 | picture->picture_structure;
}

void _outputFrame(_sceMpegDecoder *dec, _sceMpegPicture *picture, int frameNo) {
    sceMpeg *mp;

    mp = dec->mp;
    _pictureTimeStamp(dec, picture, &mp->pts, &mp->dts, (long *)&mp->flags);
    mp = dec->mp;
    dec->last_pts = mp->pts;
    dec->field_count = _fieldCounts[(int)((long)mp->flags >> 5) & 0xF];
    dec->disp_width = picture->disp_width;
    dec->disp_height = picture->disp_height;
    dec->center_offsets[0] = picture->center_offsets[0];
    dec->center_offsets[1] = picture->center_offsets[1];
    dec->center_offsets[2] = picture->center_offsets[2];
    dec->center_offsets[3] = picture->center_offsets[3];
    dec->center_offsets[4] = picture->center_offsets[4];
    dec->center_offsets[5] = picture->center_offsets[5];
    if (_checkImageBuffer(dec, picture) && picture->decoded == 1) {
        if (dec->rgb32) {
            _cscStoreImage(dec, picture);
        } else {
            _cpr8(dec, picture);
        }
        _endPicture(dec);
    }
}

/* A field pair goes out as one frame: the first field's stamps in pts/dts/flags, the second's in
 * pts2nd/dts2nd/flags2nd, each centre offset from the field that carries it. */
void _outputFieldPair(_sceMpegDecoder *dec, _sceMpegPicture *top, _sceMpegPicture *bottom, int frameNo) {
    _sceMpegPicture *first;
    _sceMpegPicture *second;
    int topFirst = 0;

    if (dec->picture_structure == MPEG_BOTTOM_FIELD) {
        first = top;
        second = bottom;
        topFirst = 64;
    } else {
        first = bottom;
        second = top;
    }
    _pictureTimeStamp(dec, first, &dec->mp->pts, &dec->mp->dts, (long *)&dec->mp->flags);
    dec->last_pts = dec->mp->pts;
    dec->field_count = 1;
    _pictureTimeStamp(dec, second, &dec->mp->pts2nd, &dec->mp->dts2nd, (long *)&dec->mp->flags2nd);
    dec->last_pts = dec->mp->pts2nd;
    dec->field_count = 1;
    dec->disp_width = first->disp_width;
    dec->mp->flags |= topFirst;
    dec->mp->flags2nd |= topFirst;
    dec->disp_height = first->disp_height;
    dec->center_offsets[0] = first->center_offsets[0];
    dec->center_offsets[1] = second->center_offsets[1];
    dec->center_offsets[3] = first->center_offsets[3];
    dec->center_offsets[4] = second->center_offsets[4];
    if (_checkImageBuffer(dec, top) && top->decoded == 1 && bottom->decoded == 1) {
        top->mb_height *= 2;
        if (dec->rgb32) {
            _cscStoreImage(dec, top);
        } else {
            _cpr8(dec, top);
        }
        top->mb_height >>= 1;
        _endPicture(dec);
    }
}
