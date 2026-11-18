/* p2textureCalls.h - the texture, render target and statistics calls of the p2 renderer that the
 * PS2 visual context makes. */
#ifndef DW4_P2TEXTURECALLS_H
#define DW4_P2TEXTURECALLS_H

#include "dw4/p2/p2texture.h"

#ifdef __cplusplus
extern "C" {
#endif

void p2SetTextureCombineMode(int mode);
void p2SetTextureFunction(int function);
void p2SetTextureFunctionAndAlpha(int function, int alpha);
void p2SetTextureClamp(int wms, int wmt, int minu, long long maxu, long long minv, int maxv, int alpha);
void p2SetTextureFilter(int magnify, int minify);
void p2CopyTexture(void *source, int sourceX, int sourceY, void *destination, int destinationX,
                   int destinationY, int width, int height);
int p2SetRenderTarget(P2Texture *colour, P2Texture *depth);
void p2RestoreRenderTarget(void);
void p2ChainTexture(P2Texture *texture, P2Texture *level);
void p2SetTexturePalette(P2Texture *texture, P2Texture *palette);
void p2InvalidateTexture(P2Texture *texture);
void p2SetTextureImage(P2Texture *texture, void *image);
void p2FreeTexture(P2Texture *texture);
void p2GetStatistics(void *statistics);
void p2SetPolygonMode(int mode);
void p2SetMaterialSpecularState(int enable);
void p2CopyFramebufferToTexture(P2Texture *texture, int sourceX, int sourceY, int destinationX, int destinationY,
                                int width, int height, int fromDepth);
long long p2GetTextureUploadSequence(P2Texture *texture);
void p2MarkTextureStage(int stage);
void p2FenceUsedTexture(P2Texture *texture);
void p2SetTextureWaitMode(int mode);

#ifdef __cplusplus
}
#endif

#endif
