#ifndef DW4_IGPSX2VISUALCONTEXT_H
#define DW4_IGPSX2VISUALCONTEXT_H

#include "dw4/gfx/GfxMetaEnums.h"

struct igMetaObject;
struct igPsx2VisualContext;
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
int Gap__Gfx__igPsx2VisualContext__vfunc_46(struct igPsx2VisualContext *self, RenderDestinationDesc *desc);
void Gap__Gfx__igPsx2VisualContext__vfunc_59(struct igPsx2VisualContext *self, struct igVertexArray *vertexArray);
void Gap__Gfx__igPsx2VisualContext__vfunc_60(struct igPsx2VisualContext *self, struct igIndexArray *indexArray);
void Gap__Gfx__igPsx2VisualContext__vfunc_63(struct igPsx2VisualContext *self, struct igPrimLengthArray *stripLengths);
void Gap__Gfx__igPsx2VisualContext__vfunc_71(struct igPsx2VisualContext *vc, int primitive, unsigned int count, int first);
void Gap__Gfx__igPsx2VisualContext__vfunc_86(struct igPsx2VisualContext *self, int light, float *color);
void Gap__Gfx__igPsx2VisualContext__vfunc_112(struct igPsx2VisualContext *self, float *ambient, float *diffuse, float *specular, float *emission, float shininess);
void Gap__Gfx__igPsx2VisualContext__vfunc_136(struct igPsx2VisualContext *self, int texture, IG_GFX_TEXTURE_WRAP wrapS, IG_GFX_TEXTURE_WRAP wrapT);
void Gap__Gfx__igPsx2VisualContext__vfunc_138(struct igPsx2VisualContext *self, int texture, IG_GFX_TEXTURE_FILTER minFilter);
void Gap__Gfx__igPsx2VisualContext__vfunc_140(struct igPsx2VisualContext *self, int texture, IG_GFX_TEXTURE_FILTER magFilter);
void Gap__Gfx__igPsx2VisualContext__vfunc_247(struct igPsx2VisualContext *self, float *color);
int Gap__Gfx__igPsx2VisualContext__vfunc_260(struct igPsx2VisualContext *self, int texture, int videoBuffer);
void Gap__Gfx__igPsx2VisualContext__vfunc_48(struct igPsx2VisualContext *self, int bufferIndex);
void Gap__Gfx__igPsx2VisualContext__vfunc_74(struct igPsx2VisualContext *self, int arg1, int arg2, int arg3, int arg4);
int Gap__Gfx__igPsx2VisualContext__vfunc_77(struct igPsx2VisualContext *self, int arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_113(struct igPsx2VisualContext *self, unsigned char arg1);
unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_127(struct igPsx2VisualContext *self, int index, int stage);
void Gap__Gfx__igPsx2VisualContext__vfunc_130(struct igPsx2VisualContext *self, int index);
void Gap__Gfx__igPsx2VisualContext__vfunc_146(struct igPsx2VisualContext *context, int mode);
void Gap__Gfx__igPsx2VisualContext__vfunc_148(struct igPsx2VisualContext *self, int arg1, int arg2);
void Gap__Gfx__igPsx2VisualContext__vfunc_150(struct igPsx2VisualContext *self, int n, int x, int y);
void Gap__Gfx__igPsx2VisualContext__vfunc_152(struct igPsx2VisualContext *self, unsigned char arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_161(struct igPsx2VisualContext *self, int arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_163(struct igPsx2VisualContext *self, unsigned int arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_165(struct igPsx2VisualContext *self, int failOp, int passZPassOp, int passZFailOp);
void Gap__Gfx__igPsx2VisualContext__vfunc_167(struct igPsx2VisualContext *self, unsigned int readMask);
void Gap__Gfx__igPsx2VisualContext__vfunc_169(struct igPsx2VisualContext *self, unsigned int writeMask);
int Gap__Gfx__igPsx2VisualContext__vfunc_171(struct igPsx2VisualContext *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8);
void Gap__Gfx__igPsx2VisualContext__vfunc_172(struct igPsx2VisualContext *self, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
void Gap__Gfx__igPsx2VisualContext__vfunc_176(struct igPsx2VisualContext *self, int arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_178(struct igPsx2VisualContext *self, unsigned int x);
void Gap__Gfx__igPsx2VisualContext__vfunc_181(struct igPsx2VisualContext *self, float fparg0);
void Gap__Gfx__igPsx2VisualContext__vfunc_183(struct igPsx2VisualContext *self, int a1);
void Gap__Gfx__igPsx2VisualContext__vfunc_185(struct igPsx2VisualContext *self, int arg1, int arg2, int arg3, int arg4, float fparg0, float fparg1);
int Gap__Gfx__igPsx2VisualContext__vfunc_192(struct igPsx2VisualContext *self);
void Gap__Gfx__igPsx2VisualContext__vfunc_193(struct igPsx2VisualContext *self, int arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_194(struct igPsx2VisualContext *self, int arg1);
int Gap__Gfx__igPsx2VisualContext__vfunc_195(struct igPsx2VisualContext *self);
void Gap__Gfx__igPsx2VisualContext__vfunc_197(struct igPsx2VisualContext *self, int arg1, int arg2);
void Gap__Gfx__igPsx2VisualContext__vfunc_203(struct igPsx2VisualContext *self, int arg1, char *arg2);
void Gap__Gfx__igPsx2VisualContext__vfunc_217(struct igPsx2VisualContext *self, unsigned char enable);
void Gap__Gfx__igPsx2VisualContext__vfunc_219(struct igPsx2VisualContext *self, int arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_221(struct igPsx2VisualContext *self, float fparg0);
void Gap__Gfx__igPsx2VisualContext__vfunc_223(struct igPsx2VisualContext *self, unsigned char a);
void Gap__Gfx__igPsx2VisualContext__vfunc_225(struct igPsx2VisualContext *self, unsigned char arg1, unsigned char arg2, unsigned char arg3, unsigned char arg4);
void Gap__Gfx__igPsx2VisualContext__vfunc_227(struct igPsx2VisualContext *self, int arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_231(struct igPsx2VisualContext *self, int arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_237(struct igPsx2VisualContext *self, unsigned char arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_239(struct igPsx2VisualContext *self, int arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_243(struct igPsx2VisualContext *self, float fparg0);
void Gap__Gfx__igPsx2VisualContext__vfunc_245(struct igPsx2VisualContext *self, int arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_249(struct igPsx2VisualContext *self, float fparg0);
void Gap__Gfx__igPsx2VisualContext__vfunc_251(struct igPsx2VisualContext *arg0, float fparg0);
void Gap__Gfx__igPsx2VisualContext__vfunc_49(struct igPsx2VisualContext *self, int bufferIndex, int *textureIndex);
int Gap__Gfx__igPsx2VisualContext__vfunc_50(struct igPsx2VisualContext *self);
void Gap__Gfx__igPsx2VisualContext__vfunc_53(struct igPsx2VisualContext *self, int bufferIndex, int *word0, int *word1);
int Gap__Gfx__igPsx2VisualContext__vfunc_54(struct igPsx2VisualContext *self, int bufferIndex);
int Gap__Gfx__igPsx2VisualContext__vfunc_55(struct igPsx2VisualContext *self, int bufferIndex);
int Gap__Gfx__igPsx2VisualContext__vfunc_56(struct igPsx2VisualContext *self, int bufferIndex);
int Gap__Gfx__igPsx2VisualContext__vfunc_57(struct igPsx2VisualContext *self, int buffer_index);
void Gap__Gfx__igPsx2VisualContext__vfunc_66(struct igPsx2VisualContext *self, unsigned int arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_69(struct igPsx2VisualContext *self, int *arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_75(struct igPsx2VisualContext *self, unsigned char arg1);
int Gap__Gfx__igPsx2VisualContext__vfunc_79(struct igPsx2VisualContext *self, int arg1, int arg2);
void Gap__Gfx__igPsx2VisualContext__vfunc_82(struct igPsx2VisualContext *self, int arg1, float *arg2);
void Gap__Gfx__igPsx2VisualContext__vfunc_84(struct igPsx2VisualContext *self, int arg1, float *arg2);
void Gap__Gfx__igPsx2VisualContext__vfunc_88(struct igPsx2VisualContext *self, int arg1, float *arg2);
void Gap__Gfx__igPsx2VisualContext__vfunc_92(struct igPsx2VisualContext *self, int arg1, float fparg0);
void Gap__Gfx__igPsx2VisualContext__vfunc_94(struct igPsx2VisualContext *self, int arg1, float fparg0);
void Gap__Gfx__igPsx2VisualContext__vfunc_117(struct igPsx2VisualContext *self, int unit, bool enabled);
void Gap__Gfx__igPsx2VisualContext__vfunc_159(struct igPsx2VisualContext *self, bool enabled);
bool Gap__Gfx__igPsx2VisualContext__vfunc_196(struct igPsx2VisualContext *self, int index);
void Gap__Gfx__igPsx2VisualContext__vfunc_209(struct igPsx2VisualContext *self, int unit, bool enabled);
void Gap__Gfx__igPsx2VisualContext__vfunc_211(struct igPsx2VisualContext *self, bool enabled);
void Gap__Gfx__igPsx2VisualContext__vfunc_229(struct igPsx2VisualContext *self, bool enabled);
void Gap__Gfx__igPsx2VisualContext__vfunc_233(struct igPsx2VisualContext *self, bool enabled);
void Gap__Gfx__igPsx2VisualContext__vfunc_241(struct igPsx2VisualContext *self, bool enabled);
void igPsx2VisualContext_CallDmaChain(struct igPsx2VisualContext *self, void *packet, int size, int flush);
int igPsx2VisualContext_IsDisplayingFirstBuffer(struct igPsx2VisualContext *self);

#ifdef __cplusplus
}
#endif

#endif
