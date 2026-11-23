#ifndef DW4_P2TEXTURE_H
#define DW4_P2TEXTURE_H

#include "dw4/p2/p2core.h"

struct p2TextureRecord;

/* The state byte of a texture record. */
typedef struct P2TextureFlags {
    signed char state : 7;              /* P2_TEXTURE_* */
    signed char detached : 1;           /* left the block list while still referenced */
} P2TextureFlags;

/* P2Texture holds the state byte both as its two fields and as one object; the C++ units need the
 * extension that admits the unnamed struct. */
#ifdef __cplusplus
#pragma push
#pragma cpp_extensions on
#endif

/* A texture record. Every record that holds VRAM, and every free stretch of VRAM, is a block of one
 * list in address order (next/prev); a free block has state P2_TEXTURE_FREE. */
typedef struct P2Texture {
    long long uploadSequence;           /* the GIF packet that uploads the image */
    long long drawSequence;             /* the last VIF1 packet that draws with it */
    p2GsTex0 tex0;
    struct P2Texture *next;             /* the block above; the free-list link of a spare record */
    struct P2Texture *prev;
    struct P2Texture *chain;            /* records fenced with this one (its mipmap levels) */
    struct P2Texture *palette;
    int reserved40;
    void *clut;
    void *image;
    int source;                         /* 0: the image; 1-3: a display buffer (P2_TEXTURE_SOURCE_*) */
    int address;                        /* the VRAM block address, -1 while it has none */
    unsigned short width;
    unsigned short height;
    unsigned short blocks;              /* its size in VRAM blocks */
    unsigned short format;
    unsigned short alignMask;           /* the block alignment its size needs, less one */
    union {
        P2TextureFlags flags;           /* the byte as one object, for code that holds its address */
        struct {
            signed char state : 7;      /* P2_TEXTURE_* */
            signed char detached : 1;   /* left the block list while still referenced */
        };
    };
    char chainCount;
    char used;                          /* drawn with since the last fence */
    signed char texAlpha;               /* TEXA.TA0 while it is bound */
} P2Texture;

#ifdef __cplusplus
#pragma pop
#endif

/* P2Texture.state */
enum {
    P2_TEXTURE_FREE = 0,                /* a free block */
    P2_TEXTURE_UNPLACED = 1,            /* no VRAM yet */
    P2_TEXTURE_LOADING = 2,             /* placed, the GIF upload pending */
    P2_TEXTURE_RESIDENT = 3,
    P2_TEXTURE_FENCED = 4,              /* in use until drawSequence completes */
    P2_TEXTURE_DRAWN = 5,               /* its last draw has completed: the block can be reused */
    P2_TEXTURE_STALE = 6                /* the image changed: upload again */
};

/* P2Texture.source */
enum {
    P2_TEXTURE_SOURCE_IMAGE = 0,
    P2_TEXTURE_SOURCE_FRONT = 1,
    P2_TEXTURE_SOURCE_BACK = 2,
    P2_TEXTURE_SOURCE_DEPTH = 3
};

#ifdef __cplusplus
extern "C" {
#endif
extern struct p2TextureRecord *p2FreeTextures;
/* The depth texture p2SetRenderTarget drew into, -1 for the display's Z buffer. */
extern int p2DepthTarget;
/* Textures bound since the statistics were last read. */
extern long long p2StatTextureBinds;
/* GS texture memory in use, which the statistics report with the space left beside it. No code in
 * this build writes it. */
extern long long p2StatTextureMemoryUsed;

void p2SetTexture(P2Texture *texture);

P2Texture *p2LoadTexture(void *image, int width, int height, int format, int deferred);
int p2GetTextureHeight(P2Texture *texture);

#ifdef __cplusplus
}
#endif

#endif
