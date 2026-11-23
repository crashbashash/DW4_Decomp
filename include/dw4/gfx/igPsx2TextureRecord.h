#ifndef DW4_IGPSX2TEXTURERECORD_H
#define DW4_IGPSX2TEXTURERECORD_H

#include "dw4/core/igSmartPointer.h"
#include "dw4/gfx/igPsx2HandlePool.h"

namespace Gap {
namespace Gfx {
class igImage;
}
}

/* One texture of igPsx2VisualContext (an element of its _pTexList pool, 136 bytes): the format, filters and
 * wrap modes the game gave it, the images it was made from, and the GS textures (`buffers`) that back it once
 * it is resident. Enumerated fields hold the kit's igGfx enums as words, as igPsx2RenderDestination does. */
struct igPsx2TextureRecord {
    int format;                   /* IG_GFX_TEXTURE_FORMAT; 0x10000 and up are the indexed formats */
    int minFilter;                /* IG_GFX_TEXTURE_FILTER */
    int magFilter;                /* IG_GFX_TEXTURE_FILTER */
    int wrapU;                    /* IG_GFX_TEXTURE_WRAP */
    int wrapV;                    /* IG_GFX_TEXTURE_WRAP */
    int source;                   /* IG_GFX_TEXTURE_SOURCE; 2 keeps an image the game writes, 3 backs a render destination */
    unsigned int mode;            /* createTexture's textureMode; bit 0 asks for generated mip levels */
    int stage;                    /* the stage setTexture last bound it to, -1 for none */
    int width;
    int height;
    int depth;                    /* -1, never set otherwise */
    int unused44;
    Gap::Gfx::igImage *sourceImage;                 /* the image setTextureSource was given (getTextureImage); counted */
    Gap::Gfx::igImage *image;                       /* the level 0 image the GS texture is built from; counted */
    igSmartPointer<Gap::Gfx::igImage> *mipImages;   /* the six mip level images, allocated when mipCount is not 0 */
    unsigned int mipCount;        /* mip levels below level 0, at most 6 */
    int unused64[2];
    int *buffers;                 /* eight P2Texture words: level 0, its mip levels, then the CLUT's palette texture */
    int buffer;                   /* the P2Texture of a render destination's depth buffer */
    unsigned char stateChanged;   /* a filter or wrap mode was stored since the texture was last bound */
    unsigned char reload;         /* the image changed, so the GS texture is refilled on the next bind */
    char pad82[2];
    int clampRegion[4];           /* the region arguments p2SetTextureWrap takes, reset to 0, 32, 0, 32 */
    int sharedClut;               /* handle of the shared intensity/alpha colour table of an 8-bit format, -1 for none */
    int clut;                     /* handle of the colour table of the image's own igClut, -1 for none */
    int bufferIndex;              /* the `buffers` word that receives the palette texture */
    int pixelFormat;              /* the format setTextureComponentSize chose from the bit counts */
    int redBits;
    int greenBits;
    int blueBits;
    int alphaBits;
    int state;                    /* 2 after a render destination bound its targets, 3 after a copy into the texture */
};

typedef igPsx2HandlePool<igPsx2TextureRecord> igPsx2TexturePool;

#endif
