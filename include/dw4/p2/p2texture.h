#ifndef DW4_P2TEXTURE_H
#define DW4_P2TEXTURE_H

struct P2Texture;
struct p2TextureRecord;

#ifdef __cplusplus
extern "C" {
#endif

extern struct p2TextureRecord *p2FreeTextures;

struct P2Texture *p2LoadTexture(void *image, int width, int height, int format, int deferred);

#ifdef __cplusplus
}
#endif

#endif
