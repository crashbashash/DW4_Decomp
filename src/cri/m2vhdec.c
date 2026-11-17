#include "dw4/cri/m2v.h"
#include "dw4/cri/mpv.h"
#include <string.h>
#include "dw4/cri/cri_adxt.h"

/* Header-parser constant tables, in retail's order. */
/* Blocks per macroblock, indexed by chroma_format (0 is the reserved value). */
static const int tbl_blocks_per_macroblock[4] = {0, 6, 8, 12};
/* PicAtr field_count, indexed by (progressive_sequence * 2 + repeat_first_field) * 2 + top_field_first. */
static const unsigned char tbl_field_count[8] = {0, 0, 1, 1, 0, 0, 2, 4};
/* The user_data_start_code and the tag the second field's user data is preceded by. */
static const unsigned char m2vhdec_usrdat_2nd_mark[8] = {0x00, 0x00, 0x01, 0xB2, '2', 'n', 'd', 0x00};
static const int tbl_dc_dct_pred_reset[4] = {128, 256, 512, 1024};
static const int tbl_intra_dc_mult[4] = {8, 4, 2, 1};

/* MPEG-2 extension_data() parser of the CRI movie decoder: reads one
 * extension_start_code_identifier and its payload from the video elementary stream (ISO/IEC
 * 13818-2 section 6.2.2.x) into the decoder's header state, using an inlined MSB-first bit reader.
 * The identifiers are 1 sequence_extension, 2 sequence_display_extension, 3
 * quant_matrix_extension, 4 copyright_extension, 5 sequence_scalable_extension, 7
 * picture_display_extension, 8 picture_coding_extension, 9 picture_spatial_scalable_extension, 10
 * picture_temporal_scalable_extension (6 is not defined by the standard and counts as an error).
 * Bit reader state: p is the next byte to fetch (word aligned after the first fetch), acc a 32-bit
 * window with the next unread bit at bit 31, nxt the following 32 bits already fetched, cnt the
 * number of bits of the window consumed since the last refill. The macros are plain brace blocks
 * on purpose: a do { } while (0) wrapper changes the instruction scheduling. */
#define READ_WORD(w) \
    { \
        (w) = *p++; \
        (w) <<= 8; (w) |= *p++ & 255; \
        (w) <<= 8; (w) |= *p++ & 255; \
        (w) <<= 8; (w) |= *p++ & 255; \
    }

/* Read n (1..31) bits into dst. */
#define GET_BITS(dst, n) \
    { \
        if (cnt >= 32 - (n)) { \
            cnt -= 32 - (n); \
            if (cnt != 0) { \
                acc |= nxt >> ((n) - cnt); \
                (dst) = acc >> (32 - (n)); \
                acc = nxt << cnt; \
            } else { \
                (dst) = acc >> (32 - (n)); \
                acc = nxt; \
            } \
            READ_WORD(nxt); \
        } else { \
            (dst) = acc >> (32 - (n)); \
            acc <<= (n); \
            cnt += (n); \
        } \
    }

/* Skip one 64 x 8 bit quantiser matrix. */
#define SKIP_MATRIX() \
    { \
        int i; \
        for (i = 0; i < 64; i++) { \
            cnt += 8; \
            if (cnt >= 32) { \
                cnt -= 32; \
                acc = nxt << cnt; \
                READ_WORD(nxt); \
            } else { \
                acc <<= 8; \
            } \
        } \
    }

void M2VHDEC_Init(void)
{
    int i;

    for (i = 0; i < 64; i++) {
    }
}

/* Clears the header state (1304 bytes at +352) and sets its non-zero defaults. */
void M2VHDEC_InitHn(M2vObj *hn)
{
    Mpeg2Ext *h = &hn->ext;

    memset(h, 0, 1304);
    h->chroma_format = 1;
    h->colour_description = 0;
    h->colour_primaries = 0xFF;
    h->transfer_characteristics = 0xFF;
    h->matrix_coefficients = 0xFF;
    h->broken_link = 1;
    h->f1136[0] = 0;
    h->f1136[1] = 0;
    h->f1136[2] = 0;
    h->f1136[3] = 0;
    h->f1136[4] = 0;
    h->header_level = 0;
    h->f1164 = 0;
    h->field_968 = 0;
    h->closed_gop = 0;
    h->field_1292 = 0;
}

void M2V_SetUsrSj(M2vObj *hn, int no, SfdSj *sj, M2vUsrDatFn fn, void *obj)
{
    M2vUsrSj *usr = &hn->usrsj[no];

    usr->sj = sj;
    usr->fn = fn;
    usr->obj = obj;
}

void M2V_SetPicUsrBuf(M2vObj *hn, char *buf, int size)
{
    M2vPicUsr *usr = &hn->picusr;

    usr->buf = buf;
    usr->size = size;
}

void M2V_GetPicUsr(M2vObj *hn, char **buf, int *size)
{
    M2vPicUsr *usr = &hn->picusr;

    if (buf != 0) {
        *buf = usr->buf;
    }
    if (size != 0) {
        *size = usr->len;
    }
}

int m2vhdec_ParseSj(M2vObj *hn, SfdSj *sj);
void m2vhdec_SetPicAtr(M2vObj *hn);

int M2V_DecodePicAtr(M2vObj *hn, SfdSj *sj)
{
    int err;

    if (M2VLIB_CheckHn(hn) != 0) {
        return M2VERR_SetCode(0, 0xFF03020C);
    }
    err = m2vhdec_ParseSj(hn, sj);
    if (err == 0) {
        m2vhdec_SetPicAtr(hn);
    }
    return err;
}

/* Copies the parsed header state into the picture attributes handed to callers. */
void m2vhdec_SetPicAtr(M2vObj *hn)
{
    Mpeg2Ext *h = &hn->ext;
    M2vPicAtr *a = &hn->picatr;

    a->horizontal_size = h->horizontal_size;
    a->vertical_size = h->vertical_size;
    a->mb_width = h->mb_width;
    a->mb_height = h->mb_height;
    a->frame_rate_code = h->frame_rate_code;
    a->temporal_reference = h->temporal_reference;
    a->picture_coding_type = h->picture_coding_type;
    a->drop_frame_flag = h->drop_frame_flag;
    a->time_code_hours = h->time_code_hours;
    a->time_code_minutes = h->time_code_minutes;
    a->time_code_seconds = h->time_code_seconds;
    a->time_code_pictures = h->time_code_pictures;
    a->gsc_count = h->gsc_count;
    a->shc_count = h->shc_count;
    a->picture_structure = h->picture_structure;
    a->chroma_format = h->chroma_format;
    a->f64 = 0;
    a->f68 = 1;
    a->bit_rate = h->bit_rate;
    a->vbv_buffer_size = h->vbv_buffer_size;
    a->display_horizontal_size = h->display_horizontal_size;
    a->display_vertical_size = h->display_vertical_size;
    a->field_count = tbl_field_count[(h->progressive_sequence * 2 + h->repeat_first_field) * 2 + h->top_field_first];
    a->progressive_frame = h->progressive_frame;
    a->top_field_first = h->top_field_first;
    a->repeat_first_field = h->repeat_first_field;
    a->field_964 = h->field_964;
    a->aspect_ratio_information = h->aspect_ratio_information;
    a->constrained_parameters_flag = h->constrained_parameters_flag;
    a->frame_rate_extension_n = h->frame_rate_extension_n;
    a->frame_rate_extension_d = h->frame_rate_extension_d;
    a->profile_and_level_indication = h->profile_and_level_indication;
    a->progressive_sequence = h->progressive_sequence;
    a->low_delay = h->low_delay;
    a->video_format = h->video_format;
    a->colour_description = h->colour_description;
    a->colour_primaries = h->colour_primaries;
    a->transfer_characteristics = h->transfer_characteristics;
    a->matrix_coefficients = h->matrix_coefficients;
}

char *parseShc(M2vObj *ctx, char *buf);
char *parseSec(M2vObj *ctx, char *buf);
char *parseUdsc(M2vObj *ctx, char *buf);
char *parseEsc(M2vObj *ctx, char *buf);
char *parseGsc(M2vObj *ctx, char *buf);
char *parsePsc(M2vObj *ctx, char *buf);

int m2vhdec_ParseSj(M2vObj *ctx, SfdSj *sj)
{
    Mpeg2Ext *h = &ctx->ext;
    SfdSjChunk ck;
    SfdSjChunk rest;
    int code;
    int saved;
    int ret = 0;
    char *end;

    h->ext_state = 0;
    saved = h->error_count;
    h->expected_ext_id = 0;
    h->error_count = 0;
    while ((code = MPV_GoNextDelimSj(sj)) != 0) {
        sj->vtbl->getChunk(sj, 1, 0x7FFFFFFF, &ck);
        end = 0;
        switch (code) {
        case 64:
            end = parseShc(ctx, ck.data);
            break;
        case 128:
            end = parseSec(ctx, ck.data);
            break;
        case 32:
            end = parseUdsc(ctx, ck.data);
            break;
        case 16:
            end = parseEsc(ctx, ck.data);
            break;
        case 8:
            end = parseGsc(ctx, ck.data);
            break;
        case 4:
            end = parsePsc(ctx, ck.data);
            break;
        }
        if (end == 0) {
            sj->vtbl->ungetChunk(sj, 1, &ck);
            break;
        }
        SJ_SplitChunk(&ck, end - ck.data, &ck, &rest);
        sj->vtbl->putChunk(sj, 0, &ck);
        sj->vtbl->ungetChunk(sj, 1, &rest);
        if (h->error_count != 0) {
            ret = -2;
            break;
        }
    }
    h->error_count += saved;
    return ret;
}

void resetQuantiserMatrix(Mpeg2Ext *h)
{
}

void calcHvSize(Mpeg2Ext *h)
{
    int width = (h->horizontal_size_extension << 12) | h->horizontal_size_value;
    int height = (h->vertical_size_extension << 12) | h->vertical_size_value;

    h->mb_width = (unsigned int)(width + 15) >> 4;
    h->horizontal_size = width;
    h->vertical_size = height;
    if (h->progressive_sequence == 1) {
        h->mb_height = (unsigned int)(height + 15) >> 4;
    } else if (h->picture_structure == 3) {
        h->mb_height = ((unsigned int)(height + 31) >> 5) * 2;
    } else {
        h->mb_height = (unsigned int)(height + 31) >> 5;
    }
    h->padded_width = h->mb_width * 16;
    h->padded_height = h->mb_height * 16;
    h->half_width = h->padded_width >> 1;
    h->half_height = h->padded_height >> 1;
}

void calcNumberOfFrameCentreOffsets(Mpeg2Ext *h)
{
    if (h->progressive_sequence == 1 || h->picture_structure == 1 || h->picture_structure == 2) {
        h->number_of_frame_centre_offsets = 1;
    } else if (h->repeat_first_field == 1) {
        h->number_of_frame_centre_offsets = 3;
    } else {
        h->number_of_frame_centre_offsets = 2;
    }
}

void calcPictureCodingExt(Mpeg2Ext *h)
{
    if (h->picture_structure == 3) {
        h->field_968 = 0;
        h->field_964 = 0;
    } else {
        h->field_964 = h->field_968 % 2;
        h->field_968++;
    }
    h->dc_dct_pred_reset = tbl_dc_dct_pred_reset[h->intra_dc_precision];
    h->intra_dc_mult = tbl_intra_dc_mult[h->intra_dc_precision];
}

void calcDarSar(Mpeg2Ext *h)
{
}

char *parseShc(M2vObj *ctx, char *buf)
{
    Mpeg2Ext *h = &ctx->ext;
    char *p;
    int cnt;
    unsigned int acc, nxt;

    h->header_level = 1;
    h->shc_count++;
    if ((h->ext_state != 0 && h->ext_state != 64) || h->expected_ext_id != 0) {
        h->error_count++;
    }
    resetQuantiserMatrix(h);
    p = (char *)((unsigned int)buf & ~3);
    cnt = (buf - p) << 3;
    READ_WORD(acc);
    READ_WORD(nxt);
    acc <<= cnt;
    if (cnt != 0) {
        h->sequence_header_code = acc | (nxt >> (32 - cnt));
        acc = nxt << cnt;
    } else {
        h->sequence_header_code = acc;
        acc = nxt;
    }
    READ_WORD(nxt);
    GET_BITS(h->horizontal_size_value, 12);
    GET_BITS(h->vertical_size_value, 12);
    GET_BITS(h->aspect_ratio_information, 4);
    GET_BITS(h->frame_rate_code, 4);
    GET_BITS(h->bit_rate_value, 18);
    GET_BITS(h->marker_bit, 1);
    GET_BITS(h->vbv_buffer_size_value, 10);
    GET_BITS(h->constrained_parameters_flag, 1);
    GET_BITS(h->load_intra_quantiser_matrix, 1);
    if (h->load_intra_quantiser_matrix)
        SKIP_MATRIX();
    GET_BITS(h->load_non_intra_quantiser_matrix, 1);
    if (h->load_non_intra_quantiser_matrix)
        SKIP_MATRIX();
    calcHvSize(h);
    calcDarSar(h);
    if (h->horizontal_size == 0) {
        h->error_count++;
    }
    if (h->horizontal_size & 15) {
        h->warning_count++;
    }
    if (h->vertical_size == 0) {
        h->error_count++;
    }
    if (h->vertical_size & 15) {
        h->warning_count++;
    }
    if (h->aspect_ratio_information < 1 || h->aspect_ratio_information > 4) {
        h->error_count++;
    }
    if (h->frame_rate_code < 1 || h->frame_rate_code > 8) {
        h->error_count++;
    }
    if (h->marker_bit == 0) {
        h->error_count++;
    }
    if (h->constrained_parameters_flag != 0) {
        h->error_count++;
    }
    h->ext_state = 16;
    h->expected_ext_id = 1;
    return buf + ((cnt + (p - buf) * 8 - 57) / 8);
}

char *parseSec(M2vObj *ctx, char *buf)
{
    Mpeg2Ext *h = &ctx->ext;
    char *p;
    int cnt;
    unsigned int acc, nxt;

    h->header_level = 1;
    h->sec_count++;
    if ((h->ext_state != 0 && h->ext_state != 128) || h->expected_ext_id != 0) {
        h->error_count++;
    }
    p = (char *)((unsigned int)buf & ~3);
    cnt = (buf - p) << 3;
    READ_WORD(acc);
    READ_WORD(nxt);
    acc <<= cnt;
    if (cnt != 0) {
        h->sec_start_code = acc | (nxt >> (32 - cnt));
        acc = nxt << cnt;
    } else {
        h->sec_start_code = acc;
        acc = nxt;
    }
    READ_WORD(nxt);
    h->ext_state = 0;
    h->expected_ext_id = 0;
    return buf + ((cnt + (p - buf) * 8 - 57) / 8);
}

void m2vhdec_PutUsrDat(M2vObj *ctx, char *src, int n);

char *parseUdsc(M2vObj *ctx, char *buf)
{
    Mpeg2Ext *h = &ctx->ext;
    char *p;
    int cnt;
    unsigned int acc, nxt, v;
    int n;

    h->udsc_count++;
    if ((h->ext_state != 0 && h->ext_state != 32) || h->expected_ext_id != 0) {
        h->error_count++;
    }
    p = (char *)((unsigned int)buf & ~3);
    cnt = (buf - p) << 3;
    READ_WORD(acc);
    READ_WORD(nxt);
    acc <<= cnt;
    if (cnt != 0) {
        h->udsc_start_code = acc | (nxt >> (32 - cnt));
        acc = nxt << cnt;
    } else {
        h->udsc_start_code = acc;
        acc = nxt;
    }
    READ_WORD(nxt);
    for (n = 0; n <= 0xFFFFF; n++) {
        v = acc >> 8;
        acc <<= 8;
        if (cnt > 8) {
            v |= nxt >> (40 - cnt);
        }
        if (v == 1) break;
        cnt += 8;
        if (cnt >= 32) {
            cnt -= 32;
            acc = nxt << cnt;
            READ_WORD(nxt);
        }
    }
    m2vhdec_PutUsrDat(ctx, buf, n + 4);
    return buf + ((cnt + (p - buf) * 8 - 57) / 8);
}

void m2vhdec_AppendPicUsr(M2vObj *ctx, void *src, int len);

/* Hands n bytes of header data to the user stream the current header level selects, in up to two
 * chunks, and runs its callback; with level 3 and a picture user buffer set, the bytes (behind an 8 byte
 * marker when one was recorded) are copied there as well. */
void m2vhdec_PutUsrDat(M2vObj *ctx, char *src, int n)
{
    int idx = ctx->ext.header_level;
    SfdSj *sj = ctx->usrsj[idx].sj;
    SfdSjChunk ck;
    SfdSjChunk ck2;

    if (sj != 0) {
        sj->vtbl->getChunk(sj, 0, n, &ck);
        memcpy(ck.data, src, ck.len);
        sj->vtbl->putChunk(sj, 1, &ck);
        if (ck.len < n) {
            sj->vtbl->getChunk(sj, 0, n - ck.len, &ck2);
            memcpy(ck2.data, src + ck.len, ck2.len);
            sj->vtbl->putChunk(sj, 1, &ck2);
        }
        if (ctx->usrsj[idx].fn != 0) {
            ctx->usrsj[idx].fn(ctx->usrsj[idx].obj, idx);
        }
    }
    if (idx == 3 && ctx->picusr.buf != 0) {
        if (ctx->ext.field_964 != 0) {
            m2vhdec_AppendPicUsr(ctx, m2vhdec_usrdat_2nd_mark, 8);
        }
        m2vhdec_AppendPicUsr(ctx, src, n);
    }
}

/* Appends len bytes to the picture user buffer, as many as still fit. */
void m2vhdec_AppendPicUsr(M2vObj *ctx, void *src, int len)
{
    M2vPicUsr *b = &ctx->picusr;
    int n = b->size - b->len;
    char *dst = b->buf + b->len;

    if (len < n) {
        n = len;
    }
    b->len += n;
    memcpy(dst, src, n);
}

char *parseEsc(M2vObj *ctx, char *buf)
{
    Mpeg2Ext *h = &ctx->ext;
    char *p = (char *)((unsigned int)buf & ~3);
    int cnt = (buf - p) << 3;
    unsigned int acc, nxt;
    int i;

    h->call_count++;
    READ_WORD(acc);
    READ_WORD(nxt);
    acc <<= cnt;
    if (cnt != 0) {
        h->start_code = acc | (nxt >> (32 - cnt));
        acc = nxt << cnt;
    } else {
        h->start_code = acc;
        acc = nxt;
    }
    READ_WORD(nxt);
    GET_BITS(h->extension_id, 4);

    if ((h->ext_state != 0 && h->ext_state != 16) || (h->expected_ext_id != 0 && h->expected_ext_id != h->extension_id)) {
        h->error_count++;
    }
    if (h->header_level != 1 && (h->extension_id == 1 || h->extension_id == 2 || h->extension_id == 5)) {
        h->error_count++;
    } else if (h->header_level != 3) {
        if (h->extension_id == 3)
            h->error_count++;
        else if (h->extension_id == 4)
            h->error_count++;
        else if (h->extension_id == 7)
            h->error_count++;
        else if (h->extension_id == 8)
            h->error_count++;
        else if (h->extension_id == 9)
            h->error_count++;
        else if (h->extension_id == 10)
            h->error_count++;
    }

    switch (h->extension_id) {
    case 1:
        GET_BITS(h->profile_and_level_indication, 8);
        GET_BITS(h->progressive_sequence, 1);
        GET_BITS(h->chroma_format, 2);
        GET_BITS(h->horizontal_size_extension, 2);
        GET_BITS(h->vertical_size_extension, 2);
        GET_BITS(h->bit_rate_extension, 12);
        GET_BITS(h->marker_bit, 1);
        GET_BITS(h->vbv_buffer_size_extension, 8);
        GET_BITS(h->low_delay, 1);
        GET_BITS(h->frame_rate_extension_n, 2);
        GET_BITS(h->frame_rate_extension_d, 5);
        if (h->chroma_format != 1) {
            h->error_count++;
            h->chroma_format = 1;
        }
        h->blocks_per_macroblock = tbl_blocks_per_macroblock[h->chroma_format];
        calcHvSize(h);
        h->bit_rate = (h->bit_rate_extension << 18) | h->bit_rate_value;
        h->vbv_buffer_size = (h->vbv_buffer_size_extension << 10) | h->vbv_buffer_size_value;
        break;
    case 2:
        GET_BITS(h->video_format, 3);
        GET_BITS(h->colour_description, 1);
        if (h->colour_description) {
            GET_BITS(h->colour_primaries, 8);
            GET_BITS(h->transfer_characteristics, 8);
            GET_BITS(h->matrix_coefficients, 8);
        }
        GET_BITS(h->display_horizontal_size, 14);
        GET_BITS(h->marker_bit, 1);
        GET_BITS(h->display_vertical_size, 14);
        break;
    case 3:
        GET_BITS(h->load_intra_quantiser_matrix, 1);
        if (h->load_intra_quantiser_matrix)
            SKIP_MATRIX();
        GET_BITS(h->load_non_intra_quantiser_matrix, 1);
        if (h->load_non_intra_quantiser_matrix)
            SKIP_MATRIX();
        GET_BITS(h->load_chroma_intra_quantiser_matrix, 1);
        if (h->load_chroma_intra_quantiser_matrix)
            SKIP_MATRIX();
        GET_BITS(h->load_chroma_non_intra_quantiser_matrix, 1);
        if (h->load_chroma_non_intra_quantiser_matrix)
            SKIP_MATRIX();
        calcDarSar(h);
        break;
    case 4:
        GET_BITS(h->copyright_flag, 1);
        GET_BITS(h->copyright_identifier, 8);
        GET_BITS(h->original_or_copy, 1);
        GET_BITS(h->copyright_reserved, 7);
        GET_BITS(h->marker_bit, 1);
        GET_BITS(h->copyright_number_1, 20);
        GET_BITS(h->marker_bit, 1);
        GET_BITS(h->copyright_number_2, 22);
        GET_BITS(h->marker_bit, 1);
        GET_BITS(h->copyright_number_3, 22);
        break;
    case 5:
        h->scalable_seen = 1;
        GET_BITS(h->scalable_mode, 2);
        GET_BITS(h->layer_id, 4);
        if (h->scalable_mode == 1) {
            GET_BITS(h->lower_layer_prediction_horizontal_size, 14);
            GET_BITS(h->marker_bit, 1);
            GET_BITS(h->lower_layer_prediction_vertical_size, 14);
            GET_BITS(h->horizontal_subsampling_factor_m, 5);
            GET_BITS(h->horizontal_subsampling_factor_n, 5);
            GET_BITS(h->vertical_subsampling_factor_m, 5);
            GET_BITS(h->vertical_subsampling_factor_n, 5);
        } else if (h->scalable_mode == 3) {
            GET_BITS(h->picture_mux_enable, 1);
            if (h->picture_mux_enable)
                GET_BITS(h->mux_to_progressive_sequence, 1);
            GET_BITS(h->picture_mux_order, 3);
            GET_BITS(h->picture_mux_factor, 3);
        }
        break;
    case 7:
        calcNumberOfFrameCentreOffsets(h);
        for (i = 0; i < h->number_of_frame_centre_offsets; i++) {
            GET_BITS(h->frame_centre_horizontal_offset[i], 16);
            GET_BITS(h->marker_bit, 1);
            GET_BITS(h->frame_centre_vertical_offset[i], 16);
            GET_BITS(h->marker_bit, 1);
        }
        break;
    case 8:
        GET_BITS(h->f_code00, 4);
        GET_BITS(h->f_code01, 4);
        GET_BITS(h->f_code10, 4);
        GET_BITS(h->f_code11, 4);
        GET_BITS(h->intra_dc_precision, 2);
        GET_BITS(h->picture_structure, 2);
        GET_BITS(h->top_field_first, 1);
        GET_BITS(h->frame_pred_frame_dct, 1);
        GET_BITS(h->concealment_motion_vectors, 1);
        GET_BITS(h->q_scale_type, 1);
        GET_BITS(h->intra_vlc_format, 1);
        GET_BITS(h->alternate_scan, 1);
        GET_BITS(h->repeat_first_field, 1);
        GET_BITS(h->chroma_420_type, 1);
        GET_BITS(h->progressive_frame, 1);
        GET_BITS(h->composite_display_flag, 1);
        if (h->composite_display_flag) {
            GET_BITS(h->v_axis, 1);
            GET_BITS(h->field_sequence, 3);
            GET_BITS(h->sub_carrier, 1);
            GET_BITS(h->burst_amplitude, 7);
            GET_BITS(h->sub_carrier_phase, 8);
        }
        calcHvSize(h);
        calcPictureCodingExt(h);
        if (h->field_964 == 0)
            ctx->picusr.len = 0;
        break;
    case 9:
        h->spatial_scalable_seen = 1;
        GET_BITS(h->lower_layer_temporal_reference, 10);
        GET_BITS(h->marker_bit, 1);
        GET_BITS(h->lower_layer_horizontal_offset, 15);
        GET_BITS(h->marker_bit, 1);
        GET_BITS(h->lower_layer_vertical_offset, 15);
        GET_BITS(h->spatial_temporal_weight_code_table_index, 2);
        GET_BITS(h->lower_layer_progressive_frame, 1);
        GET_BITS(h->lower_layer_deinterlaced_field_select, 1);
        break;
    case 10:
        GET_BITS(h->reference_select_code, 2);
        GET_BITS(h->forward_temporal_reference, 10);
        GET_BITS(h->marker_bit, 1);
        GET_BITS(h->backward_temporal_reference, 10);
        break;
    default:
        h->error_count++;
        break;
    }
    h->ext_state = 0;
    h->expected_ext_id = 0;
    return buf + ((cnt + (p - buf) * 8 - 57) / 8);
}

char *parseGsc(M2vObj *ctx, char *buf)
{
    Mpeg2Ext *h = &ctx->ext;
    char *p;
    int cnt;
    unsigned int acc, nxt;

    h->header_level = 2;
    h->gsc_count++;
    if ((h->ext_state != 0 && h->ext_state != 8) || h->expected_ext_id != 0) {
        h->error_count++;
    }
    p = (char *)((unsigned int)buf & ~3);
    cnt = (buf - p) << 3;
    READ_WORD(acc);
    READ_WORD(nxt);
    acc <<= cnt;
    if (cnt != 0) {
        h->group_start_code = acc | (nxt >> (32 - cnt));
        acc = nxt << cnt;
    } else {
        h->group_start_code = acc;
        acc = nxt;
    }
    READ_WORD(nxt);
    GET_BITS(h->drop_frame_flag, 1);
    GET_BITS(h->time_code_hours, 5);
    GET_BITS(h->time_code_minutes, 6);
    GET_BITS(h->marker_bit, 1);
    GET_BITS(h->time_code_seconds, 6);
    GET_BITS(h->time_code_pictures, 6);
    GET_BITS(h->closed_gop, 1);
    GET_BITS(h->broken_link, 1);
    return buf + ((cnt + (p - buf) * 8 - 57) / 8);
}

char *parsePsc(M2vObj *ctx, char *buf)
{
    Mpeg2Ext *h = &ctx->ext;
    char *p;
    int cnt;
    unsigned int acc, nxt;

    h->header_level = 3;
    h->psc_count++;
    if ((h->ext_state != 0 && h->ext_state != 4) || h->expected_ext_id != 0) {
        h->error_count++;
    }
    p = (char *)((unsigned int)buf & ~3);
    cnt = (buf - p) << 3;
    READ_WORD(acc);
    READ_WORD(nxt);
    acc <<= cnt;
    if (cnt != 0) {
        h->picture_start_code = acc | (nxt >> (32 - cnt));
        acc = nxt << cnt;
    } else {
        h->picture_start_code = acc;
        acc = nxt;
    }
    READ_WORD(nxt);
    GET_BITS(h->temporal_reference, 10);
    GET_BITS(h->picture_coding_type, 3);
    GET_BITS(h->vbv_delay, 16);
    if (h->picture_coding_type < 1 || h->picture_coding_type > 3) {
        h->error_count++;
    }
    if (h->picture_coding_type == 2 || h->picture_coding_type == 3) {
        GET_BITS(h->full_pel_forward_vector, 1);
        GET_BITS(h->forward_f_code, 3);
        if (h->full_pel_forward_vector != 0) {
            h->error_count++;
        }
        if (h->forward_f_code != 7) {
            h->error_count++;
        }
    }
    if (h->picture_coding_type == 3) {
        GET_BITS(h->full_pel_backward_vector, 1);
        GET_BITS(h->backward_f_code, 3);
        if (h->full_pel_backward_vector != 0) {
            h->error_count++;
        }
        if (h->backward_f_code != 7) {
            h->error_count++;
        }
    }
    for (;;) {
        GET_BITS(h->extra_bit_picture, 1);
        if (h->extra_bit_picture == 0) {
            break;
        }
        GET_BITS(h->extra_information_picture, 8);
    }
    h->picture_count[h->picture_coding_type]++;
    h->ext_state = 16;
    h->expected_ext_id = 8;
    return buf + ((cnt + (p - buf) * 8 - 57) / 8);
}
