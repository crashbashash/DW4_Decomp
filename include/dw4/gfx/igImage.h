#ifndef DW4_IGIMAGE_H
#define DW4_IGIMAGE_H

struct igImage;
struct igMemoryPoolView;
struct igMetaObject;
struct igStringRef;

#ifdef __cplusplus
extern "C" {
#endif

/* Sets the image's name: retains `name` and releases the name it replaces. */
/* Converts the image to pixel format `format`, reading the pixels of `source` (the image itself when null);
 * returns 1. */
/* Sizes the image to `width` x `height` in `format` and copies `pixels` in, or adopts them when they are
 * already the image's own. */

#ifdef __cplusplus
}
#endif

#endif
