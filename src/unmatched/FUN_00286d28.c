/*
 * FUN_00286d28 -- MPEG-2 extension_data() parser of the CRI movie decoder (Sony EE GCC, -O2 -G0).
 *
 * Reads one extension_start_code_identifier and its payload from the video elementary stream
 * (ISO/IEC 13818-2 section 6.2.2.x) into the decoder's header state, using an inlined MSB-first
 * bit reader. Field names follow the syntax elements of the standard; they are hypotheses
 * derived from the bit widths and the order of the reads. The identifiers are
 *   1 sequence_extension            2 sequence_display_extension    3 quant_matrix_extension
 *   4 copyright_extension           5 sequence_scalable_extension   7 picture_display_extension
 *   8 picture_coding_extension      9 picture_spatial_scalable_ext. 10 picture_temporal_scalable_ext.
 * (6 is not defined by the standard and counts as an error.)
 *
 * Bit reader state (kept in registers by the compiler):
 *   p    - next byte to fetch, always word aligned after the first fetch
 *   acc  - 32-bit window, next unread bit at bit 31
 *   nxt  - the following 32 bits, already fetched
 *   cnt  - number of bits of the window consumed since the last refill
 * The macros are plain brace blocks on purpose: a do { } while (0) wrapper changes the
 * instruction scheduling and no longer reproduces the retail bytes.
 */
typedef struct Mpeg2Ext {
    char pad0[20];  /* +0: not touched by this parser */
    int bit_rate_value;  /* +20 */
    int marker_bit;  /* +24 */
    int vbv_buffer_size_value;  /* +28 */
    char pad1[4];  /* +32: not touched by this parser */
    int load_intra_quantiser_matrix;  /* +36 */
    int load_non_intra_quantiser_matrix;  /* +40 */
    char pad2[8];  /* +44: not touched by this parser */
    int start_code;  /* +52 */
    int number_of_frame_centre_offsets;  /* +56 */
    char pad3[4];  /* +60: not touched by this parser */
    int extension_id;  /* +64 */
    int profile_and_level_indication;  /* +68 */
    int progressive_sequence;  /* +72 */
    int chroma_format;  /* +76 */
    int horizontal_size_extension;  /* +80 */
    int vertical_size_extension;  /* +84 */
    int bit_rate_extension;  /* +88 */
    int vbv_buffer_size_extension;  /* +92 */
    int low_delay;  /* +96 */
    int frame_rate_extension_n;  /* +100 */
    int frame_rate_extension_d;  /* +104 */
    int video_format;  /* +108 */
    int colour_description;  /* +112 */
    int colour_primaries;  /* +116 */
    int transfer_characteristics;  /* +120 */
    int matrix_coefficients;  /* +124 */
    int display_horizontal_size;  /* +128 */
    int display_vertical_size;  /* +132 */
    int scalable_mode;  /* +136 */
    int layer_id;  /* +140 */
    int lower_layer_prediction_horizontal_size;  /* +144 */
    int lower_layer_prediction_vertical_size;  /* +148 */
    int horizontal_subsampling_factor_m;  /* +152 */
    int horizontal_subsampling_factor_n;  /* +156 */
    int vertical_subsampling_factor_m;  /* +160 */
    int vertical_subsampling_factor_n;  /* +164 */
    int picture_mux_enable;  /* +168 */
    int mux_to_progressive_sequence;  /* +172 */
    int picture_mux_order;  /* +176 */
    int picture_mux_factor;  /* +180 */
    char pad4[76];  /* +184: not touched by this parser */
    int f_code00;  /* +260 */
    int f_code01;  /* +264 */
    int f_code10;  /* +268 */
    int f_code11;  /* +272 */
    int intra_dc_precision;  /* +276 */
    int picture_structure;  /* +280 */
    int top_field_first;  /* +284 */
    int frame_pred_frame_dct;  /* +288 */
    int concealment_motion_vectors;  /* +292 */
    int q_scale_type;  /* +296 */
    int intra_vlc_format;  /* +300 */
    int alternate_scan;  /* +304 */
    int repeat_first_field;  /* +308 */
    int chroma_420_type;  /* +312 */
    int progressive_frame;  /* +316 */
    int composite_display_flag;  /* +320 */
    int v_axis;  /* +324 */
    int field_sequence;  /* +328 */
    int sub_carrier;  /* +332 */
    int burst_amplitude;  /* +336 */
    int sub_carrier_phase;  /* +340 */
    int load_chroma_intra_quantiser_matrix;  /* +344 */
    int load_chroma_non_intra_quantiser_matrix;  /* +348 */
    int frame_centre_horizontal_offset[3];  /* +352 */
    int frame_centre_vertical_offset[3];  /* +364 */
    int reference_select_code;  /* +376 */
    int forward_temporal_reference;  /* +380 */
    int backward_temporal_reference;  /* +384 */
    int lower_layer_temporal_reference;  /* +388 */
    int lower_layer_horizontal_offset;  /* +392 */
    int lower_layer_vertical_offset;  /* +396 */
    int spatial_temporal_weight_code_table_index;  /* +400 */
    int lower_layer_progressive_frame;  /* +404 */
    int lower_layer_deinterlaced_field_select;  /* +408 */
    int copyright_flag;  /* +412 */
    int copyright_identifier;  /* +416 */
    int original_or_copy;  /* +420 */
    int copyright_reserved;  /* +424 */
    int copyright_number_1;  /* +428 */
    int copyright_number_2;  /* +432 */
    int copyright_number_3;  /* +436 */
    char pad5[284];  /* +440: not touched by this parser */
    int bit_rate;  /* +724 */
    int vbv_buffer_size;  /* +728 */
    char pad6[44];  /* +732: not touched by this parser */
    int ext_state;  /* +776 */
    int expected_ext_id;  /* +780 */
    int scalable_seen;  /* +784 */
    int spatial_scalable_seen;  /* +788 */
    int blocks_per_macroblock;  /* +792 */
    char pad7[168];  /* +796: not touched by this parser */
    int field_964;  /* +964 */
    char pad8[188];  /* +968: not touched by this parser */
    int header_level;  /* +1156 */
    char pad9[20];  /* +1160: not touched by this parser */
    int call_count;  /* +1180 */
    char pad10[88];  /* +1184: not touched by this parser */
    int error_count;  /* +1272 */
    char padend[1500];  /* +1276: not touched by this parser */
} Mpeg2Ext;
typedef struct Mpeg2Ctx { char pad0[336]; int field_336; char pad1[12]; Mpeg2Ext ext; } Mpeg2Ctx;

extern void FUN_00285e98(Mpeg2Ext *);
extern void FUN_00285f48(Mpeg2Ext *);
extern void FUN_00285f98(Mpeg2Ext *);
extern void FUN_00286008(Mpeg2Ext *);
extern int D_004f2890[];   /* blocks per macroblock, indexed by chroma_format: 0, 6, 8, 12 */

/* Fetch the next four bytes, big endian, into w. */
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

/* Returns the position in buf just after the parsed extension. */
char *FUN_00286d28(Mpeg2Ctx *ctx, char *buf)
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
        h->blocks_per_macroblock = D_004f2890[h->chroma_format];
        FUN_00285e98(h);
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
        FUN_00286008(h);
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
        FUN_00285f48(h);
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
        FUN_00285e98(h);
        FUN_00285f98(h);
        if (h->field_964 == 0)
            ctx->field_336 = 0;
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
