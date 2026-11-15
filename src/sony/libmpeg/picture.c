/* libmpeg picture: decoding one picture into its slot, passing finished pictures to output, and rotating
   the reference pictures. */
#include "dw4/sony/libmpeg.h"

#define P_TYPE 2
#define B_TYPE 3

int _pictureData(_sceMpegDecoder *dec);
void _outputFrame(_sceMpegDecoder *dec, _sceMpegPicture *frame, int count);
void _outputFieldPair(_sceMpegDecoder *dec, _sceMpegPicture *top, _sceMpegPicture *bottom, int count);

/* Decodes the picture into its frame or field slot and marks the slot's picture decoded. */
int _decPicture(_sceMpegDecoder *dec)
{
    _sceMpegPicture *picture;
    int decoded;

    if (dec->picture_structure == MPEG_FRAME_PICTURE && dec->second_field) {
        _sceMpegError(dec, "odd number of field pictures");
        dec->second_field = 0;
    }
    switch (dec->picture_structure) {
    case MPEG_FRAME_PICTURE:
        picture = dec->slots[0].decode;
        break;
    case MPEG_TOP_FIELD:
        picture = dec->slots[1].decode;
        break;
    case MPEG_BOTTOM_FIELD:
        picture = dec->slots[2].decode;
        break;
    default:
        picture = dec->slots[0].decode;
        _sceMpegError(dec, "unknown picture sutructure");
        break;
    }
    decoded = _pictureData(dec);
    if (decoded) {
        picture->decoded = 1;
    }
    return decoded;
}

/* Outputs the picture now due: a B picture at once, otherwise the previous reference picture. */
void _sceMpegOutputFrame(_sceMpegDecoder *dec, int count, int output)
{
    _sceMpegPicture *top, *bottom;

    if (output) {
        if (dec->picture_structure == MPEG_FRAME_PICTURE) {
            _outputFrame(dec, dec->picture_coding_type == B_TYPE ? dec->slots[0].image : dec->slots[0].ref_image,
                         count - 1);
        } else {
            if (dec->picture_coding_type == B_TYPE) {
                top = dec->slots[1].image;
                bottom = dec->slots[2].image;
            } else {
                top = dec->slots[1].ref_image;
                bottom = dec->slots[2].ref_image;
            }
            _outputFieldPair(dec, top, bottom, count - 1);
        }
    }
    if (dec->ptm_state == 1) {
        dec->ptm_state = 2;
    }
}

/* Rotates the reference pictures for the picture about to be decoded and picks the slot's picture it fills.
 * Returns 1 when the references it needs are decoded (or no reference is needed). */
int _updateRefImage(_sceMpegDecoder *dec, int second)
{
    _sceMpegPicture *selected;
    _sceMpegPicture *picture = 0;
    int ready = 0;
    int refs_needed = dec->picture_structure == MPEG_FRAME_PICTURE ? 2 : 4;

    if (dec->picture_coding_type == B_TYPE) {
        dec->slots[0].decode = dec->slots[0].image;
        dec->slots[1].decode = dec->slots[1].image;
        dec->slots[2].decode = dec->slots[2].image;
        if (dec->count_i + dec->count_p >= refs_needed) {
            dec->set_broken_link = 0;
            dec->broken_link = 0;
            dec->closed_gop = 0;
        }
        if ((dec->set_broken_link || dec->broken_link) && !dec->closed_gop) {
            dec->slots[0].ref_image->decoded = 0;
            dec->slots[1].ref_image->decoded = 0;
            dec->slots[2].ref_image->decoded = 0;
        }
        dec->set_broken_link = 0;
        dec->broken_link = 0;
        if (dec->picture_structure == MPEG_FRAME_PICTURE) {
            if (dec->slots[0].ref_image->decoded == 1 || dec->closed_gop) {
                if (dec->slots[0].prev_image->decoded == 1) {
                    ready = 1;
                }
            }
        } else if ((dec->slots[1].ref_image->decoded == 1 && dec->slots[2].ref_image->decoded == 1) || dec->closed_gop) {
            if (dec->slots[1].prev_image->decoded == 1) {
                if (dec->slots[2].prev_image->decoded == 1) {
                    ready = 1;
                }
            }
        }
    } else {
        if (!second) {
            _sceMpegPicture *tmp;

            tmp = dec->slots[0].ref_image;
            dec->slots[0].ref_image = dec->slots[0].prev_image;
            dec->slots[0].prev_image = tmp;
            tmp = dec->slots[1].ref_image;
            dec->slots[1].ref_image = dec->slots[1].prev_image;
            dec->slots[1].prev_image = tmp;
            tmp = dec->slots[2].ref_image;
            dec->slots[2].ref_image = dec->slots[2].prev_image;
            dec->slots[2].prev_image = tmp;
        }
        dec->slots[0].decode = dec->slots[0].prev_image;
        dec->slots[1].decode = dec->slots[1].prev_image;
        dec->slots[2].decode = dec->slots[2].prev_image;
        if (dec->picture_structure == MPEG_FRAME_PICTURE) {
            if (dec->picture_coding_type != P_TYPE || dec->slots[0].ref_image->decoded == 1) {
                ready = 1;
            }
        } else {
            selected = dec->picture_structure == MPEG_TOP_FIELD ? dec->slots[2].prev_image : dec->slots[1].prev_image;
            if (dec->picture_coding_type != P_TYPE || (second && selected->decoded == 1) ||
                (dec->slots[1].ref_image->decoded == 1 && dec->slots[2].ref_image->decoded == 1)) {
                ready = 1;
            }
        }
    }
    switch (dec->picture_structure) {
    case MPEG_FRAME_PICTURE:
        picture = dec->slots[0].decode;
        break;
    case MPEG_TOP_FIELD:
        picture = dec->slots[1].decode;
        break;
    case MPEG_BOTTOM_FIELD:
        picture = dec->slots[2].decode;
        break;
    }
    picture->decoded = 0;
    picture->pts = dec->pts;
    picture->dts = dec->dts;
    picture->picture_coding_type = dec->picture_coding_type;
    picture->picture_structure = dec->picture_structure;
    picture->progressive_sequence = dec->progressive_sequence;
    picture->progressive_frame = dec->progressive_frame;
    picture->top_field_first = dec->top_field_first;
    picture->repeat_first_field = dec->repeat_first_field;
    picture->center_offsets[0] = dec->frame_center_horizontal_offset[0];
    picture->center_offsets[1] = dec->frame_center_horizontal_offset[1];
    picture->center_offsets[2] = dec->frame_center_horizontal_offset[2];
    picture->center_offsets[3] = dec->frame_center_vertical_offset[0];
    picture->center_offsets[4] = dec->frame_center_vertical_offset[1];
    picture->center_offsets[5] = dec->frame_center_vertical_offset[2];
    picture->disp_width = dec->display_h_size;
    picture->disp_height = dec->display_v_size;
    return ready;
}
