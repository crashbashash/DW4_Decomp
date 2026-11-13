/* libmpeg mpc: macroblock decoding (slices, macroblock modes, motion vectors) and the IPU bit reader. */
#include "dw4/sony/libmpeg.h"

#define IPU_CMD (*(volatile unsigned int *)0x10002000)
#define IPU_CMD64 (*(volatile long long *)0x10002000)
#define IPU_CTRL (*(volatile unsigned int *)0x10002010)
#define IPU_BP (*(volatile unsigned int *)0x10002020)
#define IPU_TOP64 (*(long long *)0x10002030)
#define D3_CHCR (*(volatile unsigned int *)0x1000b000)
#define D3_QWC (*(volatile unsigned int *)0x1000b020)
#define D4_CHCR (*(volatile unsigned int *)0x1000b400)
#define D4_QWC (*(volatile unsigned int *)0x1000b420)
#define D9_CHCR (*(volatile unsigned int *)0x1000d400)
#define D_ENABLER (*(volatile unsigned int *)0x1000f520)
#define D_ENABLEW (*(volatile unsigned int *)0x1000f590)

#define IPU_CTRL_BUSY 0x80000000
#define IPU_CTRL_ECD 0x4000
#define IPU_CTRL_RST 0x40000000
#define IPU_CTRL_MP1_SHIFT 23
#define IPU_CTRL_PCT_SHIFT 24
#define D_ENABLE_CPND 0x10000

#define IPU_BCLR 0x00000000
#define IPU_BDEC 0x20000000
#define IPU_VDEC 0x30000000
#define IPU_FDEC 0x40000000

/* VDEC tables */
#define VDEC_MBAI 0
#define VDEC_MB_TYPE 1
#define VDEC_MOTION_CODE 2
#define VDEC_DMVECTOR 3

#define MB_INTRA 1
#define MB_PATTERN 2
#define MB_MOTION_BACKWARD 4
#define MB_MOTION_FORWARD 8
#define MB_QUANT 0x10

#define I_TYPE 1
#define P_TYPE 2
#define B_TYPE 3

#define MC_FIELD 1
#define MC_FRAME 2
#define MC_16X8 2
#define MC_DMV 3

#define MBAI_STUFFING 34
#define MBAI_ESCAPE 35
#define MPEG1_STUFFING_CODE 15

#define POLLS_PER_NODATA 5000

void _dmaRefImage(_sceMpegDecoder *dec);
void _sprClear(unsigned int addr, int size);
void _formPredictions(_sceMpegDecoder *dec, int bx, int by, int macroblock_type, int motion_type, int PMV[2][2][2],
                      int mv_field_sel[2][2], int dmvector[2]);
void _cscMacroblock(_sceMpegDecoder *dec, int buffer);
int _waitBdec(_sceMpegDecoder *dec);
void _nextStartCode(_sceMpegDecoder *dec);
int _sliceHeader(_sceMpegDecoder *dec);

void _sceMpegWaitIpuIdle(_sceMpegDecoder *dec);
void _ipuCommand(_sceMpegDecoder *dec, unsigned int cmd);
int _ipuVdec(_sceMpegDecoder *dec, int table);
unsigned int _ipuShowBits(_sceMpegDecoder *dec, int n);
void _ipuFlushBits(_sceMpegDecoder *dec, int n);
unsigned int _ipuGetBits(_sceMpegDecoder *dec, int n);
void _motionVector(_sceMpegDecoder *dec, int *PMV, int *dmvector, int h_r_size, int v_r_size, int dmv, int mvscale,
                   int full_pel_vector);

/* "Invalid modion type -- ignored(%d)": the file's first string, ahead of those of the functions after it that
   still link from retail, so it is named rather than written here. */
extern char invalidMotionTypeMessage[];

/* Whether an IPU command leaves IPU_TOP stale, by command number: the cached bits must be refetched. */
static int _invalidatesBits[10] = {1, 1, 0, 0, 0, 1, 1, 1, 1, 1};

/* Stops the IPU's DMA channels and resets it when the stream is aborted. */
#define ABORT_IPU()                                         \
    {                                                       \
        int intr = DIntr();                                 \
        D_ENABLEW = D_ENABLER | D_ENABLE_CPND;              \
        D4_CHCR = 0;                                        \
        D3_CHCR = 0;                                        \
        D_ENABLEW = D_ENABLER & ~D_ENABLE_CPND;             \
        if (intr) {                                         \
            EIntr();                                        \
        }                                                   \
        D3_QWC = 0;                                         \
        D4_QWC = 0;                                         \
        IPU_CTRL = IPU_CTRL_RST;                            \
    }

/* Waits for the IPU to finish a command, feeding the stream every so often. */
#define IPU_WAIT(dec)                                                                    \
    {                                                                                    \
        int polls = 0;                                                                   \
        while ((IPU_CTRL & (IPU_CTRL_BUSY | IPU_CTRL_ECD)) == IPU_CTRL_BUSY && !(dec)->abort) { \
            if (polls++ > POLLS_PER_NODATA) {                                            \
                _sceMpegDispatchMpegCbNodata((dec)->mp);                                 \
                polls = 0;                                                               \
            }                                                                            \
        }                                                                                \
    }

int DIntr(void);
int EIntr(void);

/* Places the decoded macroblock: starts motion compensation for a predicted one and points its buffer at
   its spot in the picture being decoded. */
int _motionCompensation(_sceMpegDecoder *dec, int MBA, int MBAinc, int macroblock_type, int motion_type,
                        int PMV[2][2][2], int mv_field_sel[2][2], int dmvector[2])
{
    int intra = macroblock_type & MB_INTRA;
    int bx = MBA % dec->mb_width;
    int by = MBA / dec->mb_width;
    int x = bx * 16;
    int y = by * 16;
    _sceMpegPicture *picture;

    if (intra) {
        while ((D9_CHCR >> 8) & 1)
            ;
        dec->spr[dec->mb_buffer].predicted = 0;
    } else {
        if ((unsigned int)(motion_type - 1) >= 3) {
            _sceMpegError1(dec, invalidMotionTypeMessage, motion_type);
            dec->error = 1;
            return 0;
        }
        _formPredictions(dec, x, y, macroblock_type, motion_type, PMV, mv_field_sel, dmvector);
        while ((D9_CHCR >> 8) & 1)
            ;
        _dmaRefImage(dec);
        dec->spr[dec->mb_buffer].predicted = 1;
    }
    if (MBAinc == 1 && (macroblock_type & MB_PATTERN)) {
        dec->spr[dec->mb_buffer].skipped = MBAinc;
    } else {
        dec->spr[dec->mb_buffer].skipped = 0;
    }
    dec->spr[dec->mb_buffer].intra = intra;
    if (dec->picture_structure == MPEG_FRAME_PICTURE) {
        dec->spr[dec->mb_buffer].dest =
            dec->slots[0].decode->base + (bx * dec->slots[0].decode->mb_height + by) * 384;
    } else {
        picture = dec->picture_structure == MPEG_BOTTOM_FIELD ? dec->slots[2].decode : dec->slots[1].decode;
        dec->spr[dec->mb_buffer].dest = picture->base + (bx * picture->mb_height + by) * 384;
    }
    return 1;
}

void _ipuSetMpeg1(int mpeg1)
{
    IPU_CTRL = (IPU_CTRL & ~(1 << IPU_CTRL_MP1_SHIFT)) | (mpeg1 << IPU_CTRL_MP1_SHIFT);
}

static int _getDmvector(_sceMpegDecoder *dec)
{
    int dmvector = _ipuVdec(dec, VDEC_DMVECTOR);

    return dmvector;
}

/* Dual-prime: the vectors to the opposite-parity fields from the transmitted one and the differential. */
void _dualPrimeVector(_sceMpegDecoder *dec, int DMV[][2], int *dmvector, int mvx, int mvy)
{
    if (dec->picture_structure == MPEG_FRAME_PICTURE) {
        if (dec->top_field_first) {
            DMV[0][0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[0][1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1] - 1;
            DMV[1][0] = ((3 * mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[1][1] = ((3 * mvy + (mvy > 0)) >> 1) + dmvector[1] + 1;
        } else {
            DMV[0][0] = ((3 * mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[0][1] = ((3 * mvy + (mvy > 0)) >> 1) + dmvector[1] - 1;
            DMV[1][0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[1][1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1] + 1;
        }
    } else {
        DMV[0][0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
        DMV[0][1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1];
        if (dec->picture_structure == MPEG_TOP_FIELD)
            DMV[0][1]--;
        else
            DMV[0][1]++;
    }
}

int _getMacroblockAddressIncrement(_sceMpegDecoder *dec)
{
    int increment = 0;
    unsigned int code;
    int more;
    unsigned int bits;

    do {
        code = _ipuVdec(dec, VDEC_MBAI);
        switch (code) {
        case MBAI_STUFFING:
            more = 1;
            break;
        case MBAI_ESCAPE:
            more = 1;
            increment += 33;
            break;
        case 0:
            bits = _ipuShowBits(dec, 11);
            if (dec->mpeg2 && bits == MPEG1_STUFFING_CODE) {
                _ipuFlushBits(dec, 11);
                more = 1;
                break;
            }
            _sceMpegError1(dec, "Invalid macroblock_address_increment code(0x%08x)", code);
            dec->error = 1;
            return 1;
        default:
            increment += code;
            more = 0;
            break;
        }
    } while (more);
    return increment;
}

int _slice0(_sceMpegDecoder *dec, int MBAmax);

/* Decodes the picture's slices. 1: decoded; 0 with the reason in the log otherwise; 4: aborted. */
int _pictureData(_sceMpegDecoder *dec)
{
    int MBAmax;
    int ret;

    dec->mb_buffer = 0;
    MBAmax = dec->mb_width * dec->mb_height;
    dec->mb_count = 0;
    if (dec->picture_structure != MPEG_FRAME_PICTURE) {
        MBAmax >>= 1;
    }
    do {
        ret = _slice0(dec, MBAmax);
    } while (ret == 1 || ret == 3);
    _sceMpegWaitIpuIdle(dec);
    if (!_waitBdec(dec)) {
        if (dec->abort) {
            return 4;
        }
        ret = 2;
    }
    while ((D9_CHCR >> 8) & 1)
        ;
    if (ret == 0) {
        _cscMacroblock(dec, dec->mb_buffer == 0);
    }
    if (ret == 1 || ret == 2) {
        _sceMpegError(dec, "= Skip to the next picture =");
    }
    return ret == 0;
}

/* The slice header up to the first macroblock: its address and a cleared set of motion predictors. */
int _sliceA0(_sceMpegDecoder *dec, int MBAmax, int *MBA, int *MBAinc, int PMV[2][2][2])
{
    int slice_vertical_position_extension;
    unsigned int code;
    int increment;

    dec->error = 0;
    _nextStartCode(dec);
    code = _ipuShowBits(dec, 32);
    if (code - 0x101 >= 0xaf) {
        _sceMpegError1(dec, "slice_start_code(0x%08x) out of range", code);
        return 2;
    }
    _ipuFlushBits(dec, 32);
    slice_vertical_position_extension = _sliceHeader(dec);
    increment = _getMacroblockAddressIncrement(dec);
    *MBAinc = increment;
    if (dec->error) {
        _sceMpegError(dec, "_sliceA0(): error happens");
        return 1;
    }
    *MBA = (((slice_vertical_position_extension << 7) + (code & 0xff) - 1) * dec->mb_width + increment) - 1;
    *MBAinc = 1;
    dec->dc_reset = 1;
    PMV[1][0][1] = 0;
    PMV[1][0][0] = 0;
    PMV[0][0][1] = 0;
    PMV[0][0][0] = 0;
    PMV[1][1][1] = 0;
    PMV[1][1][0] = 0;
    PMV[0][1][1] = 0;
    PMV[0][1][0] = 0;
    return 0;
}

int _skipMB0(_sceMpegDecoder *dec, int PMV[2][2][2], int *motion_type, int mv_field_sel[2][2], int *macroblock_type);
int _decMB0(_sceMpegDecoder *dec, int *macroblock_type, int *motion_type, int *dct_type, int PMV[2][2][2],
            int mv_field_sel[2][2], int dmvector[2]);

/* One slice. 0: picture complete; 1: resynchronise at the next slice; 2: give up on the picture;
   3: the slice ended early; 4: aborted. */
int _slice0(_sceMpegDecoder *dec, int MBAmax)
{
    int PMV[2][2][2];
    int motion_vertical_field_select[2][2];
    int dmvector[4];
    int MBA, MBAinc, macroblock_type, motion_type, dct_type;
    int ret;

    MBA = 0;
    MBAinc = 0;

    if ((ret = _sliceA0(dec, MBAmax, &MBA, &MBAinc, PMV)) != 0)
        return ret;
    dec->error = 0;

    for (;;) {
        if (MBA >= MBAmax)
            return 0;

        dec->spr[dec->mb_buffer].empty = 0;
        if (!_waitBdec(dec))
            return dec->abort == 0 ? 2 : 4;

        if (MBAinc == 0) {
            if (!_ipuShowBits(dec, 23) || dec->error) {
                dec->error = 0;
                return 3;
            } else {
                MBAinc = _getMacroblockAddressIncrement(dec);
                if (dec->error)
                    goto resync;
            }
        }

        if (MBA >= MBAmax) {
            _sceMpegError(dec, "Too many macroblocks in picture");
            return 2;
        }

        if (MBAinc == 1) {
            if (!_decMB0(dec, &macroblock_type, &motion_type, &dct_type, PMV, motion_vertical_field_select,
                         dmvector)) {
resync:
                dec->error = 0;
                return 1;
            }
        } else {
            if (!_skipMB0(dec, PMV, &motion_type, motion_vertical_field_select, &macroblock_type))
                goto fail;
        }

        if (!_motionCompensation(dec, MBA, MBAinc, macroblock_type, motion_type, PMV, motion_vertical_field_select,
                                 dmvector)) {
fail:
            dec->error = 0;
            return 2;
        }

        if (MBA)
            _cscMacroblock(dec, dec->mb_buffer ^ 1);
        MBA++;
        dec->mb_buffer ^= 1;
        MBAinc--;
    }
}

/* A skipped macroblock: no coefficients, and the prediction carries over (reset in P pictures). */
int _skipMB0(_sceMpegDecoder *dec, int PMV[2][2][2], int *motion_type, int mv_field_sel[2][2], int *macroblock_type)
{
    int ok = 1;

    dec->spr[dec->mb_buffer].empty = 1;
    dec->dc_reset = 1;
    if (dec->picture_coding_type == P_TYPE) {
        PMV[1][0][1] = 0;
        PMV[1][0][0] = 0;
        PMV[0][0][1] = 0;
        PMV[0][0][0] = 0;
    }
    if (dec->picture_structure == MPEG_FRAME_PICTURE) {
        *motion_type = MC_FRAME;
    } else {
        *motion_type = MC_FIELD;
        mv_field_sel[0][0] = mv_field_sel[0][1] = dec->picture_structure == MPEG_BOTTOM_FIELD;
    }
    if (dec->picture_coding_type == I_TYPE) {
        _sceMpegError(dec, "skiped macroblock in I picure is not allowed");
        ok = 0;
    }
    *macroblock_type &= ~MB_INTRA;
    return ok;
}

void _motionVectors(_sceMpegDecoder *dec, int PMV[2][2][2], int *dmvector, int mv_field_sel[2][2], int s,
                    int motion_vector_count, int mv_format, int h_r_size, int v_r_size, int dmv, int mvscale);

/* The macroblock modes and motion vectors, then the IPU's BDEC of its coefficients. */
int _decMB0(_sceMpegDecoder *dec, int *pmacroblock_type, int *pmotion_type, int *pdct_type, int PMV[2][2][2],
            int motion_vertical_field_select[2][2], int *dmvector)
{
    int macroblock_type;
    int motion_vector_count, mv_format, dmv, mvscale, dct_type;

    IPU_CTRL = (IPU_CTRL & ~(7 << IPU_CTRL_PCT_SHIFT)) | (dec->picture_coding_type << IPU_CTRL_PCT_SHIFT);
    macroblock_type = *pmacroblock_type = _ipuVdec(dec, VDEC_MB_TYPE);
    if (macroblock_type == 0) {
        _sceMpegError(dec, "Invalid macroblock_type code: 0");
        dec->error = 1;
        return 0;
    }

    if (macroblock_type & (MB_MOTION_FORWARD | MB_MOTION_BACKWARD)) {
        if (dec->picture_structure == MPEG_FRAME_PICTURE && dec->frame_pred_frame_dct)
            *pmotion_type = MC_FRAME;
        else
            *pmotion_type = _ipuGetBits(dec, 2);
    } else if ((macroblock_type & MB_INTRA) && dec->concealment_motion_vectors) {
        *pmotion_type = (dec->picture_structure == MPEG_FRAME_PICTURE) ? MC_FRAME : MC_FIELD;
    }

    if (dec->picture_structure == MPEG_FRAME_PICTURE) {
        motion_vector_count = (*pmotion_type == MC_FIELD) ? 2 : 1;
        mv_format = (*pmotion_type == MC_FRAME);
    } else {
        mv_format = 0;
        motion_vector_count = (*pmotion_type == MC_16X8) ? 2 : 1;
    }
    dmv = (*pmotion_type == MC_DMV);
    mvscale = (mv_format == 0 && dec->picture_structure == MPEG_FRAME_PICTURE);
    dct_type = (dec->picture_structure == MPEG_FRAME_PICTURE) && (!dec->frame_pred_frame_dct)
                       && (*pmacroblock_type & (MB_INTRA | MB_PATTERN))
                   ? _ipuGetBits(dec, 1)
                   : 0;
    *pdct_type = dct_type;

    if (*pmacroblock_type & MB_QUANT)
        dec->quantiser_scale_code = _ipuGetBits(dec, 5);

    if ((*pmacroblock_type & MB_MOTION_FORWARD) || ((*pmacroblock_type & MB_INTRA) && dec->concealment_motion_vectors)) {
        if (dec->mpeg2)
            _motionVectors(dec, PMV, dmvector, motion_vertical_field_select, 0, motion_vector_count, mv_format,
                           dec->f_code[0][0] - 1, dec->f_code[0][1] - 1, dmv, mvscale);
        else
            _motionVector(dec, PMV[0][0], dmvector, dec->forward_f_code - 1, dec->forward_f_code - 1, 0, 0,
                          dec->full_pel_forward_vector);
    }
    if (dec->error)
        return 0;

    if (*pmacroblock_type & MB_MOTION_BACKWARD) {
        if (dec->mpeg2)
            _motionVectors(dec, PMV, dmvector, motion_vertical_field_select, 1, motion_vector_count, mv_format,
                           dec->f_code[1][0] - 1, dec->f_code[1][1] - 1, 0, mvscale);
        else
            _motionVector(dec, PMV[0][1], dmvector, dec->backward_f_code - 1, dec->backward_f_code - 1, 0, 0,
                          dec->full_pel_backward_vector);
    }
    if (dec->error)
        return 0;

    if ((*pmacroblock_type & MB_INTRA) && dec->concealment_motion_vectors)
        _ipuFlushBits(dec, 1); /* marker bit */

    if (*pmacroblock_type & (MB_INTRA | MB_PATTERN)) {
        _sprClear(dec->spr[dec->mb_buffer].dst, 0x300);
        _sceMpegWaitIpuIdle(dec);
        _ipuCommand(dec, IPU_BDEC | ((*pmacroblock_type & MB_INTRA) << 27) | (dec->dc_reset << 26)
                             | (*pdct_type << 25) | (dec->quantiser_scale_code << 16));
    } else {
        dec->spr[dec->mb_buffer].empty = 1;
    }
    dec->dc_reset = 0;
    if (dec->error)
        return 0;

    if (!(*pmacroblock_type & MB_INTRA))
        dec->dc_reset = 1;

    if ((*pmacroblock_type & MB_INTRA) && !dec->concealment_motion_vectors) {
        PMV[0][0][0] = PMV[0][0][1] = PMV[1][0][0] = PMV[1][0][1] = 0;
        PMV[0][1][0] = PMV[0][1][1] = PMV[1][1][0] = PMV[1][1][1] = 0;
    }

    if (dec->picture_coding_type == P_TYPE && !(*pmacroblock_type & (MB_MOTION_FORWARD | MB_INTRA))) {
        PMV[0][0][0] = PMV[0][0][1] = PMV[1][0][0] = PMV[1][0][1] = 0;
        if (dec->picture_structure == MPEG_FRAME_PICTURE)
            *pmotion_type = MC_FRAME;
        else {
            *pmotion_type = MC_FIELD;
            motion_vertical_field_select[0][0] = (dec->picture_structure == MPEG_BOTTOM_FIELD);
        }
    }
    return 1;
}

/* Adds a decoded motion_code/residual to a predictor, wrapping into its f_code range. */
static void _decodeMotionVector(int *pred, int r_size, int motion_code, int motion_residual, int full_pel_vector)
{
    int lim, vec;

    lim = 16 << r_size;
    vec = full_pel_vector ? (*pred >> 1) : (*pred);

    if (motion_code > 0) {
        vec += ((motion_code - 1) << r_size) + motion_residual + 1;
        if (vec >= lim)
            vec -= lim + lim;
    } else if (motion_code < 0) {
        vec -= ((-motion_code - 1) << r_size) + motion_residual + 1;
        if (vec < -lim)
            vec += lim + lim;
    }
    *pred = full_pel_vector ? (vec << 1) : vec;
}

void _motionVectors(_sceMpegDecoder *dec, int PMV[2][2][2], int *dmvector, int mv_field_sel[2][2], int s,
                    int motion_vector_count, int mv_format, int h_r_size, int v_r_size, int dmv, int mvscale)
{
    if (motion_vector_count == 1) {
        if (mv_format == 0 && !dmv) {
            mv_field_sel[1][s] = mv_field_sel[0][s] = _ipuGetBits(dec, 1);
        }
        _motionVector(dec, PMV[0][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        PMV[1][s][0] = PMV[0][s][0];
        PMV[1][s][1] = PMV[0][s][1];
    } else {
        mv_field_sel[0][s] = _ipuGetBits(dec, 1);
        _motionVector(dec, PMV[0][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        mv_field_sel[1][s] = _ipuGetBits(dec, 1);
        _motionVector(dec, PMV[1][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
    }
}

void _motionVector(_sceMpegDecoder *dec, int *PMV, int *dmvector, int h_r_size, int v_r_size, int dmv, int mvscale,
                   int full_pel_vector)
{
    int motion_code, motion_residual;

    motion_code = _ipuVdec(dec, VDEC_MOTION_CODE);
    motion_residual = (h_r_size != 0 && motion_code != 0) ? _ipuGetBits(dec, h_r_size) : 0;
    _decodeMotionVector(&PMV[0], h_r_size, motion_code, motion_residual, full_pel_vector);

    if (dmv)
        dmvector[0] = _getDmvector(dec);

    motion_code = _ipuVdec(dec, VDEC_MOTION_CODE);
    motion_residual = (v_r_size != 0 && motion_code != 0) ? _ipuGetBits(dec, v_r_size) : 0;

    if (mvscale)
        PMV[1] >>= 1;

    _decodeMotionVector(&PMV[1], v_r_size, motion_code, motion_residual, full_pel_vector);

    if (mvscale)
        PMV[1] <<= 1;

    if (dmv)
        dmvector[1] = _getDmvector(dec);
}

void _ipuCommand(_sceMpegDecoder *dec, unsigned int cmd)
{
    IPU_CMD = cmd;
    dec->ipu_cmd_pending = _invalidatesBits[cmd >> 28];
}

/* Waits out the IPU's current command; an abort stops it instead. */
void _sceMpegWaitIpuIdle(_sceMpegDecoder *dec)
{
    int polls = 0;

    while ((IPU_CTRL & (IPU_CTRL_BUSY | IPU_CTRL_ECD)) == IPU_CTRL_BUSY) {
        if (dec->abort) {
            ABORT_IPU();
            break;
        }
        if (polls++ > POLLS_PER_NODATA) {
            _sceMpegDispatchMpegCbNodata(dec->mp);
            polls = 0;
        }
    }
}

/* Waits for IPU_CMD's result to be valid and returns it (bit 63 is the busy flag). */
static long long _ipuWaitResult(_sceMpegDecoder *dec)
{
    long long result;
    int polls = 0;

    while ((result = IPU_CMD64) < 0 && !(IPU_CTRL & IPU_CTRL_ECD)) {
        if (dec->abort) {
            ABORT_IPU();
            break;
        }
        if (polls++ > POLLS_PER_NODATA) {
            _sceMpegDispatchMpegCbNodata(dec->mp);
            polls = 0;
        }
    }
    return result;
}

/* Decodes one variable-length code with the IPU's VDEC table `table`; the bits after it are cached. */
int _ipuVdec(_sceMpegDecoder *dec, int table)
{
    long long result;
    long long top;
    unsigned int bp;
    int cmd;
    int polls = 0;

    IPU_WAIT(dec);
    cmd = (table << 26) | IPU_VDEC;
    IPU_CMD = cmd;
    dec->ipu_cmd_pending = _invalidatesBits[cmd >> 28];
    while ((result = IPU_CMD64) < 0) {
        if (dec->abort) {
            ABORT_IPU();
            return 0;
        }
        if (polls++ > POLLS_PER_NODATA) {
            polls = 0;
            _sceMpegDispatchMpegCbNodata(dec->mp);
        }
    }
    bp = IPU_BP;
    top = IPU_TOP64;
    dec->bits = top;
    if (top < 0) {
        dec->bit_count = -(bp & 0x1f) & 0x1f;
    } else {
        dec->bit_count = 32;
    }
    dec->error = (int)result == 0;
    return (short)result;
}

unsigned int _ipuShowBits(_sceMpegDecoder *dec, int n)
{
    if (dec->ipu_cmd_pending || dec->bit_count < n) {
        IPU_WAIT(dec);
        IPU_CMD = IPU_FDEC;
        dec->ipu_cmd_pending = _invalidatesBits[IPU_FDEC >> 28];
        dec->bits = _ipuWaitResult(dec);
        dec->bit_count = 32;
    }
    return dec->bits >> (32 - n);
}

void _ipuFlushBits(_sceMpegDecoder *dec, int n)
{
    unsigned int cmd;

    IPU_WAIT(dec);
    cmd = n | IPU_FDEC;
    IPU_CMD = cmd;
    dec->ipu_cmd_pending = _invalidatesBits[cmd >> 28];
    dec->bits = _ipuWaitResult(dec);
    dec->bit_count = 32;
}

unsigned int _ipuGetBits(_sceMpegDecoder *dec, int n)
{
    unsigned int cmd;
    unsigned int val;

    IPU_WAIT(dec);
    if (dec->ipu_cmd_pending || dec->bit_count < n) {
        IPU_CMD = IPU_FDEC;
        dec->ipu_cmd_pending = _invalidatesBits[IPU_FDEC >> 28];
        dec->bits = _ipuWaitResult(dec);
    }
    val = dec->bits >> (32 - n);
    dec->bit_count = 32;
    cmd = n | IPU_FDEC;
    IPU_CMD = cmd;
    dec->ipu_cmd_pending = _invalidatesBits[cmd >> 28];
    dec->bits = _ipuWaitResult(dec);
    return val;
}
