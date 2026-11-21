#ifndef DW4_IGVISUALCONTEXTDISPATCHVIEW_H
#define DW4_IGVISUALCONTEXTDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"
#include "dw4/gfx/GfxMetaEnums.h"
#include "dw4/gfx/igVertexComponentFilter.h"

class igVec4f;
struct igMatrix44f;

/* The video mode a visual context reports: NTSC (59.94 Hz) or PAL (50 Hz) refresh. */
struct VideoMode {
    unsigned char enable;
    unsigned char interlace;
    int outputFormat;
    int fullHeight;
    float refreshRate;
    int swapInterval;
    int pal;
};

/* igVisualContext's virtual functions as the game calls them on igPsx2VisualContext. Slot 24 is
 * igContext's extension lookup by name; slots 175 and 176 set the colour a frame is cleared to,
 * from four floats (_clearColor, and the packed _uiClearColor derived from it) or from a packed
 * 32-bit colour (_uiClearColor); slot 184 reads the viewport (_iViewportX, _iViewportY,
 * _iViewportW, _iViewportH); slot 201 sets a matrix by type; slot 211 passes the view matrix on as a
 * hint (igVisualContext_SetViewMatrixHint); slot 252 reports the video mode. The renderers call
 * slot 173 (flushDraw), 174 (clearRenderDestination) and 181 (setClearStencil), which sit where the
 * kit's include/igGfx/igVisualContext.h declares them, and slots 48 and 55, named
 * getCurrentRenderDestination and getStencilBitsPerPixel from their use (medium confidence).
 * The attrs' synchronizeDefault reads the state getters (slots 74-240, named from igPsx2VisualContext's
 * overrides: igPsx2VisualContext_GetAlphaTestState and the rest).
 * Slot 33 has no recovered name: the context's override runs an empty hook and releases its vertex,
 * index and strip-length arrays.
 * ABI view only: never instantiated. */
class igVisualContextDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23();
    virtual igObject *GetExtension(const char *name);                       /* slot 24 */
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32();
    /* igPsx2VisualContext::vfunc_35: an empty hook, then releases _pVertexArray, _pIndexArray and _pStripLengthArray */
    virtual void releaseVertexArrays();                                     /* slot 33 */
    virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
    virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual int getCurrentRenderDestination() const;                        /* slot 48 */
    virtual void d49(); virtual void d50();
    virtual void getRenderDestinationSize(int handle, int &width, int &height) const; /* slot 51 */
    virtual int getColorBitsPerPixel(int handle) const;                     /* slot 52 */
    virtual int getAlphaBitsPerPixel(int handle) const;                     /* slot 53 */
    virtual int getDepthBitsPerPixel(int handle) const;                     /* slot 54 */
    virtual int getStencilBitsPerPixel(int handle) const;                   /* slot 55 */
    virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65();
    virtual unsigned int getColor() const;                                  /* slot 66 */
    virtual void d67();
    virtual igVertexComponentFilter getVertexMask() const;                  /* slot 68 */
    virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73();
    virtual bool getLightingState() const;                                  /* slot 74 */
    virtual void d75(); virtual void d76(); virtual void d77();
    virtual bool getLightState(int lightHandle) const;                      /* slot 78 */
    virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88();
    virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96();
    virtual float getMaterialShininess() const;                             /* slot 97 */
    virtual void d98(); virtual void d99(); virtual void d100();
    virtual void getMaterialDiffuse(igVec4f &d) const;                      /* slot 101 */
    virtual void d102();
    virtual void getMaterialEmissive(igVec4f &e) const;                     /* slot 103 */
    virtual void d104();
    virtual void getMaterialAmbient(igVec4f &a) const;                      /* slot 105 */
    virtual void d106();
    virtual void getMaterialSpecular(igVec4f &s) const;                     /* slot 107 */
    virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111();
    virtual bool getNormalizeNormalsState() const;                          /* slot 112 */
    virtual void d113(); virtual void d114(); virtual void d115();
    virtual bool getTextureStageState(int stage) const;                     /* slot 116 */
    virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126();
    virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136();
    virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144();
    virtual IG_GFX_PIXEL_PIPELINE_MODE getPixelPipelineMode() const;        /* slot 145 */
    virtual void d146();
    virtual int getTextureStageFunc(int stage) const;                       /* slot 147 */
    virtual void d148();
    virtual void getTextureStageCoordSource(int stage, IG_GFX_TEXTURE_COORD_SOURCE &source, int &coordIndex) const; /* slot 149 */
    virtual void d150();
    virtual bool getBlendingState() const;                                  /* slot 151 */
    virtual void d152();
    virtual IG_GFX_BLENDING_FUNCTION getBlendingSource() const;             /* slot 153 */
    virtual void d154();
    virtual IG_GFX_BLENDING_FUNCTION getBlendingDestination() const;        /* slot 155 */
    virtual void d156(); virtual void d157();
    virtual bool getStencilState() const;                                   /* slot 158 */
    virtual void d159();
    virtual unsigned int getStencilRefVal() const;                          /* slot 160 */
    virtual void d161();
    virtual IG_GFX_STENCIL_FUNCTION getStencilFunc() const;                 /* slot 162 */
    virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172();
    virtual void flushDraw();                                               /* slot 173 */
    virtual void clearRenderDestination(unsigned int which);                /* slot 174 */
    virtual void setClearColor(const float *rgba);                          /* slot 175 */
    virtual void setClearColor(unsigned int color);                         /* slot 176 */
    virtual void d177();
    virtual unsigned int getClearColor() const;                             /* slot 178 */
    virtual void d179();
    virtual float getClearDepth() const;                                    /* slot 180 */
    virtual void setClearStencil(unsigned int value);                       /* slot 181 */
    virtual unsigned int getClearStencil() const;                           /* slot 182 */
    virtual void d183();
    virtual void getViewport(int *x, int *y, int *width, int *height);      /* slot 184 */
    virtual void getViewport(int &x, int &y, int &w, int &h, float &nearZ, float &farZ) const; /* slot 185 */
    virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190();
    virtual void deleteRenderList(int dlistHandle);                         /* slot 191 */
    virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195();
    virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200();
    virtual int setMatrix(int type, int matrix);                            /* slot 201 */
    virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205();
    virtual void getMatrix(IG_GFX_MATRIX_STACK which, igMatrix44f &mat) const; /* slot 206 */
    virtual void d207();
    virtual bool getTextureMatrixState(int stage) const;                    /* slot 208 */
    virtual void d209();
    virtual bool getVertexBlendingState() const;                            /* slot 210 */
    virtual void SetViewMatrixHint(const float *matrix);                    /* slot 211 */
    virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215();
    virtual bool getAlphaTestState() const;                                 /* slot 216 */
    virtual void d217();
    virtual IG_GFX_ALPHA_FUNCTION getAlphaFunc() const;                     /* slot 218 */
    virtual void d219();
    virtual float getAlphaRefValue() const;                                 /* slot 220 */
    virtual void d221();
    virtual bool getViewportClippingState() const;                          /* slot 222 */
    virtual void d223();
    virtual void getColorMask(bool &r, bool &g, bool &b, bool &a) const;    /* slot 224 */
    virtual void d225();
    virtual IG_GFX_SHADING_MODE getShadingMode() const;                     /* slot 226 */
    virtual void d227();
    virtual bool getCullFaceState() const;                                  /* slot 228 */
    virtual void d229();
    virtual IG_GFX_CULL_FACE_MODE getCullFaceMode() const;                  /* slot 230 */
    virtual void d231();
    virtual bool getDepthTestState() const;                                 /* slot 232 */
    virtual void d233(); virtual void d234(); virtual void d235();
    virtual bool getDepthWriteState() const;                                /* slot 236 */
    virtual void d237();
    virtual IG_GFX_RENDER_MODE getRenderMode() const;                       /* slot 238 */
    virtual void d239();
    virtual bool getFogState() const;                                       /* slot 240 */
    virtual void d241();
    virtual float getFogDensity() const;                                    /* slot 242 */
    virtual void d243();
    virtual IG_GFX_FOG_MODE getFogMode() const;                             /* slot 244 */
    virtual void d245();
    virtual void getFogColor(igVec4f &color) const;                         /* slot 246 */
    virtual void d247();
    virtual float getFogNear() const;                                       /* slot 248 */
    virtual void d249();
    virtual float getFogFar() const;                                        /* slot 250 */
    virtual void d251();
    virtual void getVideoMode(VideoMode *mode);                             /* slot 252 */
};

#endif
