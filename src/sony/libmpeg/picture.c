/* libmpeg picture: decoding one picture into its slot, passing finished pictures to output, and rotating
   the reference pictures. */
#include "dw4/sony/libmpeg.h"

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
