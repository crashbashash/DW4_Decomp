#ifndef DW4_IGPSX2VISUALCONTEXT_H
#define DW4_IGPSX2VISUALCONTEXT_H

#include "dw4/gfx/GfxMetaEnums.h"

struct igMetaObject;
struct igPsx2VisualContext;
struct igVec4f;
struct igVertexArray;
struct igIndexArray;
struct igPrimLengthArray;

/* What vfunc_46 copies into a new render destination; the render-destination attribute leaves the last
 * word unset. */
typedef struct RenderDestinationDesc {
    int type;
    int sizeX;
    int sizeY;
    int colorBitCount;
    int alphaBitCount;
    int depthBitCount;
    int stencilBitCount;
    float f28;
} RenderDestinationDesc;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igPsx2VisualContext_metaObject;
int igPsx2VisualContext_CreateRenderDestination(struct igPsx2VisualContext *self, RenderDestinationDesc *desc);
void igPsx2VisualContext_SetVertexArray(struct igPsx2VisualContext *self, struct igVertexArray *vertexArray);
void igPsx2VisualContext_SetIndexArray(struct igPsx2VisualContext *self, struct igIndexArray *indexArray);
void igPsx2VisualContext_SetPrimLengthArray(struct igPsx2VisualContext *self, struct igPrimLengthArray *stripLengths);
void igPsx2VisualContext_Draw(struct igPsx2VisualContext *vc, int primitive, unsigned int count, int first);
void igPsx2VisualContext_SetLightSpecular(struct igPsx2VisualContext *self, int light, float *color);
void igPsx2VisualContext_SetMaterial(struct igPsx2VisualContext *self, float *ambient, float *diffuse, float *specular, float *emission, float shininess);
int Gap__Gfx__igPsx2VisualContext__createTexture(struct igPsx2VisualContext *self, int width, int height, int format, int source, unsigned int textureMode, unsigned int imageCount);
void igPsx2VisualContext_SetTextureAddressingMode(struct igPsx2VisualContext *self, int texture, IG_GFX_TEXTURE_WRAP wrapS, IG_GFX_TEXTURE_WRAP wrapT);
void igPsx2VisualContext_SetTextureMinificationFilter(struct igPsx2VisualContext *self, int texture, IG_GFX_TEXTURE_FILTER minFilter);
void igPsx2VisualContext_SetTextureMagnificationFilter(struct igPsx2VisualContext *self, int texture, IG_GFX_TEXTURE_FILTER magFilter);
void igPsx2VisualContext_SetFogColor(struct igPsx2VisualContext *self, const struct igVec4f *color);
int igPsx2VisualContext_SetTextureSourceFromBuffer(struct igPsx2VisualContext *self, int texture, int videoBuffer);
void igPsx2VisualContext_SetRenderDestination(struct igPsx2VisualContext *self, int bufferIndex);
void igPsx2VisualContext_DrawMultiple(struct igPsx2VisualContext *self, int arg1, int arg2, int arg3, int arg4);
int igPsx2VisualContext_CreateLight(struct igPsx2VisualContext *self, int arg1);
void igPsx2VisualContext_SetNormalizeNormalsState(struct igPsx2VisualContext *self, unsigned char arg1);
unsigned char igPsx2VisualContext_SetTexture(struct igPsx2VisualContext *self, int index, int stage);
void igPsx2VisualContext_UnloadTexture(struct igPsx2VisualContext *self, int index);
void igPsx2VisualContext_SetPixelPipelineMode(struct igPsx2VisualContext *context, int mode);
void igPsx2VisualContext_SetTextureStageFunc(struct igPsx2VisualContext *self, int arg1, int arg2);
void igPsx2VisualContext_SetTextureStageCoordSource(struct igPsx2VisualContext *self, int n, int x, int y);
void igPsx2VisualContext_SetBlendingState(struct igPsx2VisualContext *self, unsigned char arg1);
void FUN_00174510(struct igPsx2VisualContext *self, IG_GFX_BLENDING_FUNCTION source, IG_GFX_BLENDING_FUNCTION destination, unsigned char blendConstant, int stage);
void igPsx2VisualContext_SetStencilRefVal(struct igPsx2VisualContext *self, int arg1);
void igPsx2VisualContext_SetStencilFunc(struct igPsx2VisualContext *self, unsigned int arg1);
void igPsx2VisualContext_SetStencilOps(struct igPsx2VisualContext *self, int failOp, int passZPassOp, int passZFailOp);
void igPsx2VisualContext_SetStencilReadMask(struct igPsx2VisualContext *self, unsigned int readMask);
void igPsx2VisualContext_SetStencilWriteMask(struct igPsx2VisualContext *self, unsigned int writeMask);
int igPsx2VisualContext_CopyRenderDestinationToTexture(struct igPsx2VisualContext *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8);
void igPsx2VisualContext_CopyRenderDestinationToMemory(struct igPsx2VisualContext *self, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
void igPsx2VisualContext_ClearRenderDestination(struct igPsx2VisualContext *self, int arg1);
void igPsx2VisualContext_SetClearColorPacked(struct igPsx2VisualContext *self, unsigned int x);
void igPsx2VisualContext_SetClearDepth(struct igPsx2VisualContext *self, float fparg0);
void igPsx2VisualContext_SetClearStencil(struct igPsx2VisualContext *self, int a1);
void igPsx2VisualContext_SetViewport(struct igPsx2VisualContext *self, int arg1, int arg2, int arg3, int arg4, float fparg0, float fparg1);
int igPsx2VisualContext_CreateRenderList(struct igPsx2VisualContext *self);
void igPsx2VisualContext_DeleteRenderList(struct igPsx2VisualContext *self, int arg1);
void igPsx2VisualContext_BeginRenderListDraw(struct igPsx2VisualContext *self, int arg1);
int igPsx2VisualContext_EndRenderListDraw(struct igPsx2VisualContext *self);
void igPsx2VisualContext_SetBlendingMatrices(struct igPsx2VisualContext *self, int arg1, int arg2);
void igPsx2VisualContext_SetMatrix(struct igPsx2VisualContext *self, int arg1, char *arg2);
void igPsx2VisualContext_SetAlphaTestState(struct igPsx2VisualContext *self, unsigned char enable);
void igPsx2VisualContext_SetAlphaFunc(struct igPsx2VisualContext *self, int arg1);
void igPsx2VisualContext_SetAlphaRefValue(struct igPsx2VisualContext *self, float fparg0);
void igPsx2VisualContext_SetViewportClippingState(struct igPsx2VisualContext *self, unsigned char a);
void igPsx2VisualContext_SetColorMask(struct igPsx2VisualContext *self, unsigned char arg1, unsigned char arg2, unsigned char arg3, unsigned char arg4);
void igPsx2VisualContext_SetShadingMode(struct igPsx2VisualContext *self, int arg1);
void igPsx2VisualContext_SetCullFaceMode(struct igPsx2VisualContext *self, int arg1);
void igPsx2VisualContext_SetDepthWriteState(struct igPsx2VisualContext *self, unsigned char arg1);
void igPsx2VisualContext_SetRenderMode(struct igPsx2VisualContext *self, int arg1);
void igPsx2VisualContext_SetFogDensity(struct igPsx2VisualContext *self, float fparg0);
void igPsx2VisualContext_SetFogMode(struct igPsx2VisualContext *self, int arg1);
void igPsx2VisualContext_SetFogNear(struct igPsx2VisualContext *self, float fparg0);
void igPsx2VisualContext_SetFogFar(struct igPsx2VisualContext *arg0, float fparg0);
void igPsx2VisualContext_SetRenderDestinationWithTexture(struct igPsx2VisualContext *self, int bufferIndex, int *textureIndex);
int igPsx2VisualContext_GetCurrentRenderDestination(struct igPsx2VisualContext *self);
void igPsx2VisualContext_GetRenderDestinationSize(struct igPsx2VisualContext *self, int bufferIndex, int *word0, int *word1);
int igPsx2VisualContext_GetColorBitsPerPixel(struct igPsx2VisualContext *self, int bufferIndex);
int igPsx2VisualContext_GetAlphaBitsPerPixel(struct igPsx2VisualContext *self, int bufferIndex);
int igPsx2VisualContext_GetDepthBitsPerPixel(struct igPsx2VisualContext *self, int bufferIndex);
int igPsx2VisualContext_GetStencilBitsPerPixel(struct igPsx2VisualContext *self, int buffer_index);
void igPsx2VisualContext_SetColorPacked(struct igPsx2VisualContext *self, unsigned int arg1);
void igPsx2VisualContext_SetVertexMask(struct igPsx2VisualContext *self, int *arg1);
void igPsx2VisualContext_SetLightingState(struct igPsx2VisualContext *self, unsigned char arg1);
int igPsx2VisualContext_SetLightState(struct igPsx2VisualContext *self, int arg1, int arg2);
void igPsx2VisualContext_SetLightDiffuse(struct igPsx2VisualContext *self, int arg1, float *arg2);
void igPsx2VisualContext_SetLightAmbient(struct igPsx2VisualContext *self, int arg1, float *arg2);
void igPsx2VisualContext_SetLightPosition(struct igPsx2VisualContext *self, int arg1, float *arg2);
void igPsx2VisualContext_SetLightCutoffAngle(struct igPsx2VisualContext *self, int arg1, float fparg0);
void igPsx2VisualContext_SetLightFalloffRate(struct igPsx2VisualContext *self, int arg1, float fparg0);
void igPsx2VisualContext_SetTextureStageState(struct igPsx2VisualContext *self, int unit, bool enabled);
void igPsx2VisualContext_SetStencilState(struct igPsx2VisualContext *self, bool enabled);
bool igPsx2VisualContext_ExecuteRenderList(struct igPsx2VisualContext *self, int index);
void igPsx2VisualContext_SetTextureMatrixState(struct igPsx2VisualContext *self, int unit, bool enabled);
void igPsx2VisualContext_SetVertexBlendingState(struct igPsx2VisualContext *self, bool enabled);
void igPsx2VisualContext_SetCullFaceState(struct igPsx2VisualContext *self, bool enabled);
void igPsx2VisualContext_SetDepthTestState(struct igPsx2VisualContext *self, bool enabled);
void igPsx2VisualContext_SetFogState(struct igPsx2VisualContext *self, bool enabled);
void igPsx2VisualContext_CallDmaChain(struct igPsx2VisualContext *self, void *packet, int size, int flush);
int igPsx2VisualContext_IsDisplayingFirstBuffer(struct igPsx2VisualContext *self);
void igPsx2VisualContext_SetMatrixPsx2(struct igPsx2VisualContext *self, int stack, const float *matrix);
void igPsx2VisualContext_GetMatrixPsx2(struct igPsx2VisualContext *self, int stack, float *matrix);
void igPsx2VisualContext_SetMatrixOptimizationState(struct igPsx2VisualContext *self, unsigned char enable);
unsigned char igPsx2VisualContext_GetMatrixOptimizationState(struct igPsx2VisualContext *self);
void igPsx2VisualContext_SetTextureMatrixProjectiveState(struct igPsx2VisualContext *self, int stage, unsigned char enable);
unsigned char igPsx2VisualContext_GetTextureMatrixProjectiveState(struct igPsx2VisualContext *self, int stage);

#ifdef __cplusplus
}
#endif

#endif
