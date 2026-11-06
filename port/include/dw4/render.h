/* dw4/render.h — a software rasteriser (porting P4.3's first renderer).
 *
 * The plan's first renderer consumes scene data on the host rather than emulating the VU1/GS pair,
 * and a software pass is the shortest route to something you can *look at*: the loader already hands
 * out renderer-ready meshes (positions, UVs, triangles, DCC names), `png.c`
 * writes the output and the texture packs decode, so no window system or GPU is needed yet.
 *
 * What it is not: the game's own pipeline.  The GS's register state, the VU1 microcode's transform
 * and lighting, and the stage's object placement (a model node's attr list is empty in
 * the file — the controller assigns models to nodes at load) are all still open.  This draws meshes,
 * with a camera fitted to each one.
 */
#ifndef DW4_RENDER_H
#define DW4_RENDER_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    int w, h;
    uint8_t *rgba;      /* w*h*4, row-major, top row first */
    float *z;           /* w*h, the depth buffer */
} dw4_fb;

/* A texture to sample: RGBA8888, row-major, as `dw4_texpack_rgba` produces (the game's textures are
 * stored bottom-up, which `v` is flipped to compensate for). */
typedef struct {
    const uint8_t *rgba;
    int w, h;
} dw4_tex;

/* --- lighting (renderer P4.3/P4.4) -------------------------------------------------------------
 *
 * The shading *model* is the engine's: the LIGHT VU1 programs name AMBIENT, DIRECTIONAL
 * (infinite), POSITIONAL/LOCAL, SPOTLIGHT, LINEAR_ATT and `_SPEC`/`_NOSPEC`, and `igLightAttr` (`data/reflection.json`) is the serialised light those programs read.
 *
 * The *values* are not recovered: `p2lighting` reads a runtime list that is empty in every saved
 * state (`docs/engine/p2-lighting.md`), so the disc does not state them.  A caller
 * therefore supplies the rig; `dw4_render_mesh`/`dw4_render_mesh_tex` fall back to a built-in
 * placeholder rig when none is set.  Positions and directions are in the **same space as the
 * mesh's `pos` buffer** (object space for `--name`, world space for a captured scene). */
enum { DW4_LIGHT_DIRECTIONAL = 1, DW4_LIGHT_POSITIONAL = 2, DW4_LIGHT_SPOT = 3 };

typedef struct {
    int type;                 /* DW4_LIGHT_DIRECTIONAL / _POSITIONAL / _SPOT */
    float pos[3];             /* positional/spot: the light's position */
    float dir[3];             /* directional/spot: the direction the light travels (unit) */
    float ambient[3];         /* the light's ambient contribution, added flat */
    float diffuse[3];
    float specular[3];        /* ignored unless `specular_on` (the `_NOSPEC` variants) */
    int specular_on;
    float range;              /* positional/spot: distance at which `diffuse` reaches 0 (0 = no cut) */
    float att_const, att_linear, att_quad;  /* 1 / (c + l*d + q*d^2); 0,0,0 means 1,0,0 */
    float spot_cos_cutoff;    /* cos of the outer cone half-angle (0 = no spot falloff) */
    float spot_cos_falloff;   /* cos of the inner cone half-angle */
    float shininess;          /* Blinn-Phong exponent */
} dw4_light;

#define DW4_MAX_LIGHTS 8

/* --- fog (renderer P4.1, the VU1 FOG family) ----------------------------------------------------
 *
 * Three programs: `FOG_LINEAR`, `FOG_EXP`, `FOG_EXP2` (plus the `CLIP_FOG_*` variants, which are
 * the same effect at the clip stage).  Fog blends a fragment toward a colour by its **view-space
 * depth**: linear falls from `start` to `end`, exp/exp2 by `density`.  As with the light rig the
 * values are runtime state, so a caller supplies them; `mode` 0 (the default) leaves fog off. */
enum { DW4_FOG_OFF = 0, DW4_FOG_LINEAR = 1, DW4_FOG_EXP = 2, DW4_FOG_EXP2 = 3 };

typedef struct {
    int mode;               /* DW4_FOG_OFF / _LINEAR / _EXP / _EXP2 */
    float color[3];         /* the fog colour the fragment blends toward */
    float start, end;       /* linear: the view-space depth range */
    float density;          /* exp/exp2: the exponent's scale */
} dw4_fog;

/* Install a rig (`NULL` or `mode` 0 turns fog off).  A copy is kept. */
void dw4_render_set_fog(const dw4_fog *fog);
/* Parse `<linear|exp|exp2>,start,end,density,r,g,b` (start/end ignored by exp/exp2).  Returns 0. */
int dw4_render_parse_fog(const char *spec, dw4_fog *fog);
const dw4_fog *dw4_render_get_fog(void);
/* The game's own stage fog: FOG_LINEAR, near 60 / far 300, colour FOGCOL
 * 0xE5CCE5.  Fills `out`, returns 0.  The scene path uses this when the caller passes no fog. */
int dw4_render_game_fog(dw4_fog *out);

/* Ambient-only floor, added to every shaded pixel. */
void dw4_render_set_ambient(float r, float g, float b);

/* Parse one light SPEC (the `--light`/`--lights` line format):
 *
 *   <dir|point|spot>,px,py,pz,dx,dy,dz,dr,dg,db,sr,sg,sb,range,shininess,falloff_deg,cutoff_deg
 *
 * `px..pz` is the position (point/spot), `dx..dz` the direction the light travels (dir/spot),
 * `dr..db` the diffuse and `sr..sb` the specular colour (all-zero specular means `_NOSPEC`).
 * Returns 0, or -1 when the type keyword is not one of the three. */
int dw4_render_parse_light(const char *spec, dw4_light *l);
/* Load a rig from a file (`--lights`), one SPEC per line, `#` starts a comment.  Returns the number
 * of lights read (up to `max`), or -1 when the file cannot be opened. */
int dw4_render_load_lights(const char *path, dw4_light *out, int max);

/* The software fit camera's framing as a matrix, for a backend that wants the matrix itself (the
 * GPU path).  `view` gets the same row-vector view `dw4_render_set_view` accepts; `fov_y`/`aspect`
 * are the projection it was built for (the software path uses FOV_Y and 1.0 when it fits). */
void dw4_render_fit_view(const uint8_t *pos, uint32_t nverts, float yaw, float pitch,
                         float view[16], float *fov_y, float *aspect);
/* One-sided or two-sided `N.L` (default two-sided, the port's long-standing behaviour).  Two-sided
 * folds the term with `fabs`, lighting a surface turned away from the light as if it faced it;
 * `dw4_render_set_two_sided(0)` drops that term instead, which is what the game's culled front
 * faces get.  Measured a no-op on the camera-matched Goblin Pass frame, so it is a
 * knob rather than a new default. */
void dw4_render_set_two_sided(int on);
int  dw4_render_two_sided(void);

/* Back-face culling: 0 off, 1 cull back faces, 2 cull front faces.  The game culls
 * at the VU1 clip stage, so a surface the camera cannot see is never drawn; the port used to draw
 * both faces everywhere, which is what put slivers and a sawtooth rim on the props. */
void dw4_render_set_cull(int mode);
int  dw4_render_cull(void);

/* Unlit: skip the light term entirely, so the fragment colour is the texel times the mesh tint
 * (`igLightingStateAttr._enabled = 0` materials). */
void dw4_render_set_unlit(int on);
int  dw4_render_unlit(void);

/* Gouraud: light each vertex once with its own authored normal and interpolate the colour, the
 * game's own path. Enabled by default; disabling it interpolates
 * normals and lights per pixel. */
void dw4_render_set_gouraud(int on);
int  dw4_render_gouraud(void);

/* Texture sampling: bilinear (the default, as the GS filters a magnified texture) or nearest.
 * A 32x32 atlas magnified ~10x is where it shows -- the crate's wood.  The GL path
 * maps this to GL_LINEAR / GL_NEAREST. */
void dw4_render_set_tex_filter(int bilinear);
int  dw4_render_tex_filter(void);

/* The engine's texture matrix as a UV affine: `uv' = uv * scale + offset` (every live
 * `igTextureMatrixAttr` is the identity with a translation in elements 12..13). */
void dw4_render_set_uv_offset(float u, float v);
void dw4_render_set_uv_scale(float scale);

/* Replace the rig (up to `DW4_MAX_LIGHTS`; `n <= 0` restores the game's built-in rig). */
void dw4_render_set_lights(const dw4_light *lights, int n);
int  dw4_render_light_count(void);
/* The game's standard light rig, from the packs' `igLightAttr` records: fills up to
 * `max` lights and returns the count (2).  Both backends use it when the caller supplies no rig. */
int  dw4_render_builtin_rig(dw4_light *out, int max);

int  dw4_fb_init(dw4_fb *fb, int w, int h);
void dw4_fb_free(dw4_fb *fb);
void dw4_fb_clear(dw4_fb *fb, uint8_t r, uint8_t g, uint8_t b);

/* A mesh's triangles already in screen space, drawn with a z-buffer and a Lambert term.  `pos` is
 * `nverts` x 3 f32 and `uv` (may be NULL) `nverts` x 2 f32, both little-endian in memory.  `tint`
 * scales the shaded colour, so a caller can give each mesh its own hue. */
void dw4_render_set_view(const float view[16], float fov_y, float aspect);
void dw4_render_clear_view(void);
int  dw4_render_has_view(void);

int dw4_render_mesh(dw4_fb *fb, const uint8_t *pos, const uint8_t *uv, uint32_t nverts,
                    const uint32_t *tris, uint32_t ntris, float yaw, float pitch,
                    float tint[3], int width);

/* The same, with the mesh's decoded **vertex normals** (`normal`, `nverts` x 3 f32, may be NULL).
 * When present they are interpolated and shaded per pixel, so a curved surface is smooth instead of
 * faceted; when NULL the face normal is used (the flat fallback). */
int dw4_render_mesh_n(dw4_fb *fb, const uint8_t *pos, const uint8_t *normal, const uint8_t *uv,
                      uint32_t nverts, const uint32_t *tris, uint32_t ntris, float yaw,
                      float pitch, float tint[3], const dw4_tex *tex);

/* The same, sampling `tex` through the mesh's UVs and modulating it by the shaded tint.  `v` is
 * flipped, because the pack stores a grid bottom-up. */
int dw4_render_mesh_tex(dw4_fb *fb, const uint8_t *pos, const uint8_t *uv, uint32_t nverts,
                        const uint32_t *tris, uint32_t ntris, float yaw, float pitch,
                        float tint[3], const dw4_tex *tex);

/* Draw a 2D UI triangle over the frame, the way the game's UI draws reach the GS: **unlit**, with
the vertex colour and the texture alpha as a MODULATE (`(Ct*Cv)>>7`, `(At*Av)>>7`) and the GS's
`ALPHA (A-B)*C+D` blend straight over what is already there (no depth test).  Each vertex is
`{x, y, u, v}` in screen pixels with the GS's own UV (already `STQ/Q`); `rgba` is the draw's
constant per-vertex colour (0..128, as the dump stores it) and `tex` may be NULL for an untextured
overlay.  `blend` is the draw's blend: 0 opaque (ABE off), 1 alpha (ALPHA 0x44), 2 additive
(ALPHA 0x48).  `rgba` is one colour per vertex (0..128, as the dump stores it) and is interpolated
across the triangle, so a lit (Gouraud) draw renders as the GS drew it. */
void dw4_render_ui_tri(dw4_fb *fb, const float v0[4], const float v1[4], const float v2[4],
                       const uint8_t rgba[3][4], const dw4_tex *tex, uint8_t blend);

/* Perspective-correct form of the same draw: each vertex is `{x, y, s, t, q}` (the GS's raw STQ)
 * and the divide happens per pixel, as the GS does.  Use it for a triangle a *3D* draw produced
 * (the front-end's background dome): dividing per vertex warps the texture across it. */
void dw4_render_ui_tri_stq(dw4_fb *fb, const float v0[5], const float v1[5], const float v2[5],
                           const uint8_t rgba[3][4], const dw4_tex *tex, uint8_t blend);

/* The GS alpha test (probe): when >= 0, a fragment whose sampled alpha is below this is discarded.
 * -1 (the default) is off.  Used to test the front-end pack's `igAlphaFunctionAttr _refValue`. */
extern float dw4_render_alpha_ref;

/* The GS's texture wrap for the STQ triangle path: 0 clamps (the default, the UI's CLAMP), nonzero
 * repeats both axes (CLAMP WMS = WMT = 0, which the front-end layer's draws use -- its scrolled UVs go
 * outside 0..1).  */
extern int dw4_render_tex_wrap;

/* Nonzero samples the STQ triangle path bilinearly (the GS's TEX1 MMAG/MMIN linear, which the
 * front-end layer's draws use); 0 (the default) is nearest. */
extern int dw4_render_tex_linear;

/* The GS alpha test for the STQ path: a fragment with `(At * Av) >> 7 <= dw4_render_aref` is dropped (and
 * writes no depth).  -1 (the default) is off. */
extern int dw4_render_aref;

/* Clear the layer's depth buffer to 0 (the stream's clear writes Z = 0), then draw with
 * `dw4_render_ui_tri_stq_z`: the same triangle as `dw4_render_ui_tri_stq` with a per-vertex Z (larger =
 * nearer) tested GEQUAL against, and written to, that buffer. */
void dw4_render_zbuf_clear(const dw4_fb *fb);

/* One triangle of the front-end layer: `dw4_ui_draw`'s STQ form plus the GS's per-vertex Z (larger =
 * nearer, tested GEQUAL against the buffer `dw4_render_zbuf_clear` cleared, ZMSK = 0) and AREF (the alpha
 * test, -1 = off).  A list of these is drawn across threads by `dw4_render_layer_draws`, banded by rows
 * exactly like `dw4_render_ui_draws`, so the frame is bit-identical to `nthreads == 1`. */
typedef struct {
    const dw4_tex *tex;
    uint8_t blend;           /* 0 opaque, 1 alpha, 2 additive */
    int aref;
    int gs_raster;           /* 1/16-pixel XY and exact top-left coverage; legacy callers keep zero */
    int straight_rgb;        /* GS opaque RGB ignores alpha; ui_out receives premultiplied blends */
    int no_depth_write;      /* test depth but preserve it (GS ZMSK=1) */
    int depth_always;        /* bypass the comparison, retaining write policy */
    uint8_t filter;          /* 0 caller setting, 1 nearest, 2 linear */
    uint8_t color_mask;      /* disabled RGBA channels, bits 0..3; 0 writes all */
    float v[3][5];           /* {x, y, s, t, q} */
    float z[3];
    int fog;                 /* 1 = white fog (legacy); 2 = fog_color below */
    uint8_t fog_color[3];
    float f[3];              /* F per vertex, 0..255 (255 = no fog) */
    uint8_t rgba[3][4];
} dw4_layer_draw;

void dw4_render_layer_draws(dw4_fb *fb, const dw4_layer_draw *draws, int n, int nthreads);

/* A whole replay list, drawn across threads.  The draws must stay in order (the blends compose), so
 * the parallel axis is the framebuffer's *rows*: the frame is cut into horizontal bands and every
 * band replays the whole list with each draw clipped to that band.  A draw only writes pixels inside
 * its own bbox, so a band performs exactly the writes it would have performed serially, in the same
 * order -- the frame is bit-identical to `nthreads == 1` (and to looping the two calls above), which
 * tools/verify_render.py asserts.  `nthreads <= 1` replays serially.  Textures must already be
 * resident (decode them before calling: the texture cache is not thread-safe). */
typedef struct {
    const dw4_tex *tex;      /* NULL draws the vertex colour alone */
    uint8_t blend;           /* 0 opaque (ABE off), 1 alpha, 2 additive */
    uint8_t stq;             /* 1 when v holds {x, y, s, t, q}, 0 for {x, y, s, t} */
    uint8_t depth_mode;      /* 0 legacy UI, 1 GEQUAL, 2 ALWAYS; positive Z nearer */
    uint8_t depth_write;
    uint8_t gs_raster;       /* authored GS pixel grid and integer sampling */
    uint8_t filter;          /* 0 caller setting, 1 nearest, 2 linear */
    uint8_t color_mask;      /* disabled RGBA channels, bits 0..3; 0 writes all */
    float z[3];
    float v[3][5];
    uint8_t rgba[3][4];
} dw4_ui_draw;

void dw4_render_ui_draws(dw4_fb *fb, const dw4_ui_draw *draws, int n, int nthreads);

/* Draw the frame's wireframe edges over what is already there (a diagnostic view). */
void dw4_render_wire(dw4_fb *fb, const uint8_t *pos, uint32_t nverts, const uint32_t *tris,
                     uint32_t ntris, float yaw, float pitch, int width, uint8_t r, uint8_t g,
                     uint8_t b);

/* --- a readout on the frame (`--fps`, `--osd-text`) --------------------------------------------
 *
 * A deliberately minimal 5x7 bitmap font for on-screen readouts.  It is NOT the game's text: the
 * engine generates its own from `bectext.igb`'s bitmap font, and nothing of that is
 * wired up here.  This exists so a diagnostic number can be read off the frame itself.
 *
 * `dw4_fb_text` draws `s` at (x, y), one 5x7 glyph per 6*scale px, in `r,g,b`, with a 1px dark
 * shadow so it stays legible over a bright logo.  `dw4_fb_plate` darkens a rectangle under it first
 * (the framebuffer's alpha is ignored by the present path, so translucency is a blend into RGB).
 * Characters outside `0-9 . : f p s m x space` (either case) are skipped as a blank. */
void dw4_fb_text(dw4_fb *fb, int x, int y, const char *s, int scale,
                 uint8_t r, uint8_t g, uint8_t b);
void dw4_fb_plate(dw4_fb *fb, int x, int y, int w, int h, int darken_percent);
int dw4_fb_text_width(const char *s, int scale);
/* The `--fps` readout ("NN fps", top-left over a darkened plate) every windowed present loop draws:
 * the stage/boot renderer, the movie player and `dw4asset render`. */
void dw4_render_fps(dw4_fb *fb, double fps);
struct dw4_gl_layer;
int dw4_render_fps_gpu(struct dw4_gl_layer *,dw4_fb *,double fps);
/* The live loop publishes the FPS to show before a frame is drawn (<= 0: none); a world draw that has the frame resident on
 * the GPU draws the counter in the same run and sets dw4_fps_overlay_drawn so the loop does not draw it a second time. */
extern double dw4_fps_overlay;
extern int dw4_fps_overlay_drawn;


#endif /* DW4_RENDER_H */
