/* png.h - the stock libpng 1.0.8 entry points the Gfx library's PNG image loader calls (the library
 * itself is src/third_party/libpng, compiled as C). Opaque structs: the loader only passes the
 * pointers on. Names, argument lists and the 32-bit `long` of the game's build follow upstream's png.h. */
#ifndef DW4_PNG_H
#define DW4_PNG_H

struct png_struct_def;
struct png_info_struct;
struct png_row_info_struct;
struct png_color_struct;
struct png_color_8_struct;
struct png_color_16_struct;
typedef struct png_struct_def *png_structp;
typedef struct png_struct_def **png_structpp;
typedef struct png_info_struct *png_infop;
typedef struct png_info_struct **png_infopp;
typedef struct png_row_info_struct *png_row_infop;
typedef struct png_color_struct *png_colorp;
typedef struct png_color_8_struct *png_color_8p;
typedef struct png_color_16_struct *png_color_16p;
/* libpng's png_color_8 (the sBIT chunk): the significant bits of each channel, which the reader's format
 * mapping reads. */
struct png_color_8_struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char gray;
    unsigned char alpha;
};

/* libpng's colour types (png_get_IHDR), the colour-type masks and the tRNS chunk's valid flag. */
#define PNG_COLOR_MASK_PALETTE 1
#define PNG_COLOR_MASK_ALPHA 4
#define PNG_COLOR_TYPE_GRAY 0
#define PNG_COLOR_TYPE_RGB 2
#define PNG_COLOR_TYPE_PALETTE 3
#define PNG_COLOR_TYPE_GRAY_ALPHA 4
#define PNG_COLOR_TYPE_RGB_ALPHA 6
#define PNG_INFO_tRNS 0x0010

typedef unsigned int png_uint_32;
typedef unsigned int png_size_t;
typedef unsigned char *png_bytep;
typedef void *png_voidp;
typedef const char *png_const_charp;
typedef void (*png_error_ptr)(png_structp, png_const_charp);
typedef void (*png_rw_ptr)(png_structp, png_bytep, png_size_t);
typedef void (*png_user_transform_ptr)(png_structp, png_row_infop, png_bytep);
typedef png_voidp (*png_malloc_ptr)(png_structp, png_size_t);
typedef void (*png_free_ptr)(png_structp, png_voidp);

#ifdef __cplusplus
extern "C" {
#endif

png_structp png_create_read_struct_2(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn,
                                     png_error_ptr warn_fn, png_voidp mem_ptr, png_malloc_ptr malloc_fn,
                                     png_free_ptr free_fn);
png_infop png_create_info_struct(png_structp png_ptr);
void png_destroy_info_struct(png_structp png_ptr, png_infopp info_ptr_ptr);
void png_destroy_read_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr);
void png_destroy_write_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr);
int png_sig_cmp(png_bytep sig, png_size_t start, png_size_t num_to_check);
void png_set_sig_bytes(png_structp png_ptr, int num_bytes);
void png_set_mem_fn(png_structp png_ptr, png_voidp mem_ptr, png_malloc_ptr malloc_fn, png_free_ptr free_fn);
void png_set_read_fn(png_structp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn);
png_voidp png_get_io_ptr(png_structp png_ptr);
void png_read_info(png_structp png_ptr, png_infop info_ptr);
void png_read_update_info(png_structp png_ptr, png_infop info_ptr);
void png_read_row(png_structp png_ptr, png_bytep row, png_bytep display_row);
void png_read_end(png_structp png_ptr, png_infop info_ptr);
png_uint_32 png_get_valid(png_structp png_ptr, png_infop info_ptr, png_uint_32 flag);
png_uint_32 png_get_rowbytes(png_structp png_ptr, png_infop info_ptr);
png_uint_32 png_get_IHDR(png_structp png_ptr, png_infop info_ptr, png_uint_32 *width, png_uint_32 *height,
                         int *bit_depth, int *color_type, int *interlace_type, int *compression_type,
                         int *filter_type);
png_uint_32 png_get_PLTE(png_structp png_ptr, png_infop info_ptr, png_colorp *palette, int *num_palette);
png_uint_32 png_get_sBIT(png_structp png_ptr, png_infop info_ptr, png_color_8p *sig_bit);
png_uint_32 png_get_tRNS(png_structp png_ptr, png_infop info_ptr, png_bytep *trans, int *num_trans,
                         png_color_16p *trans_values);
void png_set_strip_16(png_structp png_ptr);
void png_set_gray_1_2_4_to_8(png_structp png_ptr);
void png_set_tRNS_to_alpha(png_structp png_ptr);
void png_set_packing(png_structp png_ptr);
void png_set_read_user_transform_fn(png_structp png_ptr, png_user_transform_ptr read_user_transform_fn);

#ifdef __cplusplus
}
#endif

#endif
