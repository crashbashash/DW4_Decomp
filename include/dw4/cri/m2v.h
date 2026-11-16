#ifndef DW4_CRI_M2V_H
#define DW4_CRI_M2V_H

/* CRI Sofdec's MPEG-2 video decoder (libmwsfde m2v_*.o): the decoder handle with its sequence, GOP and
 * picture header state (Mpeg2Ctx), the picture attributes handed to callers (M2vPicAtr), the library
 * work (M2vLibWork) and the per-handle error record. */

typedef struct M2vErrInf {
    int (*func)(void *obj);
    void *obj;
    int code;
    int reserved[2];
} M2vErrInf;

typedef struct M2vHnErr {
    int stat;
    M2vErrInf err;
} M2vHnErr;


typedef struct Mpeg2Ext {
    int sequence_header_code;  /* +0 */
    int horizontal_size_value;  /* +4 */
    int vertical_size_value;  /* +8 */
    int aspect_ratio_information;  /* +12 */
    int frame_rate_code;  /* +16 */
    int bit_rate_value;  /* +20 */
    int marker_bit;  /* +24 */
    int vbv_buffer_size_value;  /* +28 */
    int constrained_parameters_flag;  /* +32 */
    int load_intra_quantiser_matrix;  /* +36 */
    int load_non_intra_quantiser_matrix;  /* +40 */
    int sec_start_code;  /* +44: sequence_end_code, filled by parseSec */
    int udsc_start_code;  /* +48: user_data_start_code, filled by parseUdsc */
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
    int group_start_code;  /* +184 */
    int drop_frame_flag;  /* +188 */
    int time_code_hours;  /* +192 */
    int time_code_minutes;  /* +196 */
    int time_code_seconds;  /* +200 */
    int time_code_pictures;  /* +204 */
    int closed_gop;  /* +208 */
    int broken_link;  /* +212 */
    int picture_start_code;  /* +216 */
    int temporal_reference;  /* +220 */
    int picture_coding_type;  /* +224 */
    int vbv_delay;  /* +228 */
    int full_pel_forward_vector;  /* +232 */
    int forward_f_code;  /* +236 */
    int full_pel_backward_vector;  /* +240 */
    int backward_f_code;  /* +244 */
    int extra_bit_picture;  /* +248 */
    int extra_information_picture;  /* +252 */
    char pad4b[4];  /* +256 */
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
    char pad5[268];  /* +440 */
    int horizontal_size;  /* +708 */
    int vertical_size;  /* +712 */
    int mb_width;  /* +716 */
    int mb_height;  /* +720 */
    int bit_rate;  /* +724 */
    int vbv_buffer_size;  /* +728 */
    char pad6[44];  /* +732: not touched by this parser */
    int ext_state;  /* +776 */
    int expected_ext_id;  /* +780 */
    int scalable_seen;  /* +784 */
    int spatial_scalable_seen;  /* +788 */
    int blocks_per_macroblock;  /* +792 */
    char pad796[4];  /* +796 */
    int dc_dct_pred_reset;  /* +800 */
    char pad804[12];  /* +804 */
    int intra_dc_mult;  /* +816 */
    char pad820[128];  /* +820 */
    int padded_width;  /* +948 */
    int padded_height;  /* +952 */
    int half_width;  /* +956 */
    int half_height;  /* +960 */
    int field_964;  /* +964 */
    int field_968;  /* +968 */
    char pad8[164];  /* +972 */
    int f1136[5];  /* +1136 */
    int header_level;  /* +1156 */
    int f1160;  /* +1160 */
    int f1164;  /* +1164 */
    int shc_count;  /* +1168 */
    int sec_count;  /* +1172 */
    int udsc_count;  /* +1176 */
    int call_count;  /* +1180 */
    int gsc_count;  /* +1184 */
    int psc_count;  /* +1188 */
    int picture_count[4];  /* +1192 */
    char pad10[64];  /* +1208 */
    int error_count;  /* +1272 */
    int warning_count;  /* +1276 */
    char pad1280[12];  /* +1280 */
    int field_1292;  /* +1292 */
    char padend[1480];  /* +1296 */
} Mpeg2Ext;
typedef struct M2vPicAtr {
    int horizontal_size;  /* +0 */
    int vertical_size;  /* +4 */
    int mb_width;  /* +8 */
    int mb_height;  /* +12 */
    int frame_rate_code;  /* +16 */
    int temporal_reference;  /* +20 */
    int picture_coding_type;  /* +24 */
    int drop_frame_flag;  /* +28 */
    int time_code_hours;  /* +32 */
    int time_code_minutes;  /* +36 */
    int time_code_seconds;  /* +40 */
    int time_code_pictures;  /* +44 */
    int gsc_count;  /* +48 */
    int shc_count;  /* +52 */
    int picture_structure;  /* +56 */
    int chroma_format;  /* +60 */
    int f64;  /* +64 */
    int f68;  /* +68 */
    int bit_rate;  /* +72 */
    int vbv_buffer_size;  /* +76 */
    unsigned short display_horizontal_size;  /* +80 */
    unsigned short display_vertical_size;  /* +82 */
    unsigned char field_count;  /* +84 */
    unsigned char progressive_frame;  /* +85 */
    unsigned char top_field_first;  /* +86 */
    unsigned char repeat_first_field;  /* +87 */
    unsigned char field_964;  /* +88 */
    unsigned char aspect_ratio_information;  /* +89 */
    unsigned char constrained_parameters_flag;  /* +90 */
    unsigned char frame_rate_extension_n;  /* +91 */
    unsigned char frame_rate_extension_d;  /* +92 */
    unsigned char profile_and_level_indication;  /* +93 */
    unsigned char progressive_sequence;  /* +94 */
    unsigned char low_delay;  /* +95 */
    unsigned char video_format;  /* +96 */
    unsigned char colour_description;  /* +97 */
    unsigned char colour_primaries;  /* +98 */
    unsigned char transfer_characteristics;  /* +99 */
    unsigned char matrix_coefficients;  /* +100 */
    char pad101[27];  /* +101 */
} M2vPicAtr;
typedef struct M2vUsrSj {
    void *sj;
    void (*cb)(int arg, int index); /* called after a chunk was put to sj */
    int cbArg;
} M2vUsrSj;
typedef struct M2vPicUsr {
    void *buf;
    int size;
    int len;
} M2vPicUsr;
typedef struct Mpeg2Ctx {
    char pad0[88];
    M2vPicAtr picatr;  /* +88 */
    char pad216[64];  /* +216 */
    M2vUsrSj usrsj[4];  /* +280 */
    M2vPicUsr picusr;  /* +328 */
    char pad340[12];  /* +340 */
    Mpeg2Ext ext;  /* +352 */
} Mpeg2Ctx;
extern unsigned char D_004f28a0[];
extern int tbl_dc_dct_pred_reset[4];
extern int tbl_intra_dc_mult[4];

extern void calcHvSize(Mpeg2Ext *);
extern void calcNumberOfFrameCentreOffsets(Mpeg2Ext *);
extern void calcPictureCodingExt(Mpeg2Ext *);
extern void calcDarSar(Mpeg2Ext *);
extern void resetQuantiserMatrix(Mpeg2Ext *);
extern int D_004f2890[];   /* blocks per macroblock, indexed by chroma_format: 0, 6, 8, 12 */


typedef void (*M2vCondFn)();

typedef struct M2vObj {
    int stat;  /* +0: 1 free, 2 in use */
    char err[20];  /* +4 */
    M2vCondFn cond[16];  /* +24 */
    M2vPicAtr picatr;  /* +88 */
    char work[1448];  /* +216 */
} M2vObj;

typedef struct M2vLibWork {
    M2vCondFn cond[16];  /* +0: conditions for new handles */
    int nobj;  /* +64 */
    M2vObj *obj;  /* +68 */
} M2vLibWork;

#define M2V_OBJ_WORK_SIZE 0x700

#endif
