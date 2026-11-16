#ifndef DW4_BEFONTIMAGE_H
#define DW4_BEFONTIMAGE_H

struct igMetaObject;
struct beFontImage;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_beFontImage_metaObject;
/* The triangles drawing `text` takes: the sum of each character's count. */
int beFontImage_CountTriangles(struct beFontImage *image, const char *text);
int beFontImage_CountTrianglesWide(struct beFontImage *image, const unsigned short *text);

#ifdef __cplusplus
}
#endif

#endif
