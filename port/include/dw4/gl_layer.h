/* Ordered screen-space material draws on GLES3; the CPU renderer remains the oracle. */
#ifndef DW4_GL_LAYER_H
#define DW4_GL_LAYER_H
#include "dw4/render.h"
typedef struct dw4_gl_layer dw4_gl_layer;
dw4_gl_layer *dw4_gl_layer_open(int w, int h);
void dw4_gl_layer_close(dw4_gl_layer *g);
/* Another owner of the same renderer (one resident frame across several modules); close releases one owner. */
dw4_gl_layer *dw4_gl_layer_share(dw4_gl_layer *g);
const char *dw4_gl_layer_info(const dw4_gl_layer *g);
/* GPU color/depth clear; RGBA8 readback keeps the host framebuffer bridge.
 * Resets write masks and restores the caller's context. Failure preserves fb. */
int dw4_gl_layer_clear(dw4_gl_layer *,dw4_fb *,uint8_t,uint8_t,uint8_t,uint8_t);
enum {DW4_GL_FADE_RGB,DW4_GL_SHADOW_ALPHA};
/* Pixel transforms on GPU: floor(RGB*factor), or the original caster-red to
 * black/alpha conversion. Alpha is preserved for RGB fades. Failure preserves fb. */
int dw4_gl_layer_transform(dw4_gl_layer *,dw4_fb *,int mode,float factor);
/* Conventional RGBA8 image, top-left destination origin, original integer
 * portrait opacity/blend rule. Source/destination byte storage remains borrowed. */
int dw4_gl_layer_blit(dw4_gl_layer *,dw4_fb *,const dw4_fb *,int x,int y,float opacity);
int dw4_gl_layer_plate(dw4_gl_layer *,dw4_fb *,int x,int y,int w,int h,int darken_percent);
/* Original nearest resize: source pixel floor(destination*source/destination size). */
int dw4_gl_layer_scale(dw4_gl_layer *,dw4_fb *,const dw4_fb *);
int dw4_gl_layer_multiply(dw4_gl_layer *,dw4_fb *,unsigned numerator,unsigned denominator);
/* Composite over fb, clearing layer depth to zero. Textures must outlive this renderer. Immutable images stay
 * cached; changed mutable images need texture_changed before drawing. Failure leaves fb unchanged, allowing CPU fallback. */
int dw4_gl_layer_draw(dw4_gl_layer *g, dw4_fb *fb, const dw4_layer_draw *draws, int n, int wrap,
                      int linear, float alpha_ref);
/* Deferred mode for a run of operations on one framebuffer: the frame stays resident on the GPU between
 * operations (no per-operation upload, readback or row flip) and `on=0` reads it back once. The caller must not touch
 * fb->rgba while deferred; operations on a different framebuffer write the resident frame back first. Returns 0 on
 * success; a failed closing call leaves the CPU framebuffer stale. */
int dw4_gl_layer_defer(dw4_gl_layer *, dw4_fb *, int on);
/* Mark a mutable texture for re-upload on the next draw; no GL context switch. */
void dw4_gl_layer_texture_changed(dw4_gl_layer *, const dw4_tex *);
/* Drop one uploaded texture (and its GL object) before its pixels are freed: the cache is keyed by the pixel pointer, and a later allocation at the
 * same address and size would otherwise draw the stale image (a loading card showing the previous destination's atlas). Never fails the caller. */
void dw4_gl_layer_texture_forget(dw4_gl_layer *, const dw4_tex *);
/* Diagnostics: uploaded textures currently cached, and owners holding the layer (dw4_gl_layer_share). */
int dw4_gl_layer_cached_textures(const dw4_gl_layer *);
int dw4_gl_layer_owners(const dw4_gl_layer *);
/* Forget uploaded image identities before their backing storage is replaced.
 * Keep the rendering context/program/framebuffer; failure permits CPU fallback. */
int dw4_gl_layer_textures_reset(dw4_gl_layer *);
/* Ordered STQ UI replay; unsupported legacy UV draws return failure. */
int dw4_gl_layer_ui(dw4_gl_layer *, dw4_fb *, const dw4_ui_draw *, int);
/* Try GPU then retain the CPU oracle on failure. */
void dw4_gl_layer_ui_or_cpu(dw4_gl_layer **, dw4_fb *, const dw4_ui_draw *, int, int);
#endif
