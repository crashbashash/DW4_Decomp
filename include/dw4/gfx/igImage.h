#ifndef DW4_IGIMAGE_H
#define DW4_IGIMAGE_H

struct igImage;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igImage_metaObject;
struct igImage *igImage_CreateInstance(int allocator);
struct igMetaObject *igImage_GetOrCreateMetaObject(void);
/* Converts the image to pixel format `format`, reading the pixels of `source` (the image itself when null);
 * returns 1. */
unsigned char FUN_00157200(struct igImage *self, int format, struct igImage *source);

#ifdef __cplusplus
}
#endif

#endif
