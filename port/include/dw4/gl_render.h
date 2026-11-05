/* dw4/gl_render.h — the host GPU backend (GLES2/3 over EGL, porting P4.1/P4.3).
 *
 * This is the real GPU path the plan asks for: the game's shading model is run as a fragment
 * shader, not emulated.  The VU1 microcode is the *specification* of that model (LIGHT 91 programs
 * = 82 % of the pipeline; findings #489/#492/#494), and the model here matches `render.c`'s
 * software implementation: ambient + two-sided N·L diffuse, positional d/d² (or linear)
 * attenuation, a spotlight cone, and Blinn-Phong specular.
 *
 * It uses **EGL surfaceless + an offscreen FBO**, so it needs no display and no window: that is
 * what makes it verifiable in a headless container and on a CI box.  It renders whatever EGL
 * provides in explicit reference mode. Normal play's hardware policy rejects
 * software/unsupported renderer labels. Constructors and split-frame operations
 * preserve the caller's EGL/SDL context; peer contexts share display lifetime.
 *
 * GL is optional, like SDL2: without `DW4_ENABLE_GL` every entry point fails cleanly.
 */
#ifndef DW4_GL_RENDER_H
#define DW4_GL_RENDER_H

#include "dw4/render.h"

typedef struct dw4_gl dw4_gl;

/* 1 when the build was compiled with EGL/GLES. */
int dw4_gl_built(void);

/* Create an offscreen surface-less context of `w` x `h`.  Returns NULL when GL is not compiled in
 * or no context can be made. */
dw4_gl *dw4_gl_open(int w, int h);
void dw4_gl_close(dw4_gl *g);
const char *dw4_gl_info(dw4_gl *g);          /* GL_RENDERER, for the boot report */
void dw4_gl_clear_color(dw4_gl *,uint8_t,uint8_t,uint8_t,uint8_t);
/* Cancel a split frame and restore the context active before begin. */
int dw4_gl_frame_abort(dw4_gl *);

/* Draw one merged mesh (world-space `pos`/`nrm`, `nv` verts, `nt` triangles) through `view`
 * (row-major, translation at 12..14, third row already negated so in-front is +z), into `fb`.
 * `uv` (may be NULL) is `nv` x 2 f32 and `tex` (may be NULL) is a decoded texture pack image: when
 * both are present the shader samples it through the mesh's UVs, exactly as the software path does.
 * `ambient`/`lights`/`tint` are the same rig `render.c` takes.  Returns 0. */
int dw4_gl_render(dw4_gl *g, dw4_fb *fb,
                  const float *pos, const float *nrm, const float *uv,
                  const uint32_t *tris, uint32_t nv, uint32_t nt,
                  const float view[16], float fov, float aspect,
                  const float ambient[3], const dw4_light *lights, int nlights,
                  const float tint[3], const dw4_tex *tex);

/* The same split so a caller can draw many meshes (each with its own tint, and soon its own
 * texture) into a single frame: `begin` clears the target and sets the view/projection/rig,
 * `mesh` adds one draw, `end` reads the result back into `fb`. */
int dw4_gl_frame_begin(dw4_gl *g, const float view[16], float fov, float aspect,
                       const float ambient[3], const dw4_light *lights, int nlights);
int dw4_gl_frame_mesh(dw4_gl *g, const float *pos, const float *nrm, const float *uv,
                      const uint32_t *tris, uint32_t nv, uint32_t nt,
                      const float tint[3], const dw4_tex *tex);
int dw4_gl_frame_end(dw4_gl *g, dw4_fb *fb);

#endif /* DW4_GL_RENDER_H */
