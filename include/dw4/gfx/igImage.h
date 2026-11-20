#ifndef DW4_IGIMAGE_H
#define DW4_IGIMAGE_H

struct igImage;
struct igMemoryPoolView;
struct igMetaObject;
struct igStringRef;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igImage_metaObject;
struct igImage *igImage_CreateInstance(struct igMemoryPoolView *pool);
struct igMetaObject *igImage_GetOrCreateMetaObject(void);
/* Sets the image's name: retains `name` and releases the name it replaces. */
void FUN_00156340(struct igImage *self, const struct igStringRef *name);
/* Converts the image to pixel format `format`, reading the pixels of `source` (the image itself when null);
 * returns 1. */
unsigned char FUN_00157200(struct igImage *self, int format, struct igImage *source);
/* Sizes the image to `width` x `height` in `format` and copies `pixels` in, or adopts them when they are
 * already the image's own. */
void igImage_SetPixels(struct igImage *self, void *pixels, int format, int width, int height);

#ifdef __cplusplus
}
#endif

#endif
