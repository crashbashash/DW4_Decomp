#ifndef DW4_P2TEXTURE_H
#define DW4_P2TEXTURE_H

struct P2Texture;

#ifdef __cplusplus
extern "C" {
#endif

struct P2Texture *p2LoadTexture(void *image, int width, int height, int format, int deferred);

#ifdef __cplusplus
}
#endif

#endif
