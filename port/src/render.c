/* dw4/render.c — a small software rasteriser; see include/dw4/render.h for what it is and is not.
 *
 * The camera is fitted to the mesh: the centre and radius of the vertex bounding box give a view
 * distance that puts the whole model in frame at a fixed vertical field of view.  Triangles are
 * scanned by their bounding box with barycentric coordinates and interpolated depth, so the result
 * is a real z-buffered render rather than a painter's-algorithm approximation.
 */
#define _GNU_SOURCE
#include "dw4/render.h"
#include "dw4/gpupolicy.h"
#include "dw4/gl_layer.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FOV_Y 0.90f            /* radians, ~51 degrees */

typedef struct { float x, y, z; } v3;
typedef struct { float x, y; } v2;

static float rdf(const uint8_t *p)
{
    float f;
    memcpy(&f, p, 4);
    return f;
}

/* A view that fits `pos`: rotate by yaw/pitch, then push the camera back along +Z. */
typedef struct {
    float cy, sy, cp, sp, dist, cx, cyy, cz;
} camera;

/* A supplied view (row-vector convention: v' = v * M, translation in the last row) and projection,
 * used in place of the bounding box camera when set.  See dw4_render_set_view. */
static int g_use_view;
static float g_view[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
static float g_fov = FOV_Y;
static float g_aspect = 1.0f;

void dw4_render_set_view(const float view[16], float fov_y, float aspect)
{
    memcpy(g_view, view, sizeof(g_view));
    g_fov = fov_y;
    g_aspect = aspect;
    g_use_view = 1;
}

void dw4_render_clear_view(void) { g_use_view = 0; }

int dw4_render_has_view(void) { return g_use_view; }

static void cam_view(const camera *c, v3 p, v3 *out)
{
    if (g_use_view) {
        out->x = p.x * g_view[0] + p.y * g_view[4] + p.z * g_view[8] + g_view[12];
        out->y = p.x * g_view[1] + p.y * g_view[5] + p.z * g_view[9] + g_view[13];
        out->z = p.x * g_view[2] + p.y * g_view[6] + p.z * g_view[10] + g_view[14];
        return;
    }
    float x = p.x - c->cx, y = p.y - c->cyy, z = p.z - c->cz;
    float x1 = c->cy * x + c->sy * z;           /* yaw about Y */
    float z1 = -c->sy * x + c->cy * z;
    float y2 = c->cp * y - c->sp * z1;          /* pitch about X */
    float z2 = c->sp * y + c->cp * z1;

    out->x = x1;
    out->y = y2;
    out->z = z2 + c->dist;
}

static int cam_project(const camera *c, v3 v, int width, int height, float *sx, float *sy,
                       float *sz)
{
    (void)c;
    if (v.z <= 0.05f) {
        /* A vertex behind the near plane has no screen position.  Say so through a negative z
         * rather than leaving sx/sy unset -- the scan loops read them unconditionally, so leaving
         * them undefined drew garbage triangles wherever geometry crossed the camera plane. */
        *sx = *sy = 0.0f;
        *sz = -1.0f;
        return 0;
    }
    if (g_use_view) {
        float f = (float)height / (2.0f * tanf(g_fov * 0.5f));
        *sx = (v.x / v.z) * f * g_aspect + (float)width * 0.5f;
        *sy = -(v.y / v.z) * f + (float)height * 0.5f;
        *sz = v.z;
        return 1;
    }
    *sx = (v.x / v.z) * (float)height / (2.0f * tanf(FOV_Y * 0.5f)) + (float)width * 0.5f;
    *sy = -(v.y / v.z) * (float)height / (2.0f * tanf(FOV_Y * 0.5f)) + (float)height * 0.5f;
    *sz = v.z;
    return 1;
}

static void fit_camera(const uint8_t *pos, uint32_t nverts, float yaw, float pitch, camera *c)
{
    float minx = 1e30f, miny = 1e30f, minz = 1e30f, maxx = -1e30f, maxy = -1e30f, maxz = -1e30f;
    float r, dx, dy, dz, rad;
    uint32_t i;

    for (i = 0; i < nverts; i++) {
        float x = rdf(pos + 12 * i), y = rdf(pos + 12 * i + 4), z = rdf(pos + 12 * i + 8);
        if (x < minx) minx = x;
        if (y < miny) miny = y;
        if (z < minz) minz = z;
        if (x > maxx) maxx = x;
        if (y > maxy) maxy = y;
        if (z > maxz) maxz = z;
    }
    c->cx = (minx + maxx) * 0.5f;
    c->cyy = (miny + maxy) * 0.5f;
    c->cz = (minz + maxz) * 0.5f;
    dx = maxx - minx;
    dy = maxy - miny;
    dz = maxz - minz;
    r = sqrtf(dx * dx + dy * dy + dz * dz) * 0.5f;
    rad = r > 1e-4f ? r : 1.0f;
    c->dist = rad / tanf(FOV_Y * 0.5f) * 1.35f;
    c->cy = cosf(yaw);
    c->sy = sinf(yaw);
    c->cp = cosf(pitch);
    c->sp = sinf(pitch);
}

/* The fit camera as a row-vector affine, for the GPU path.  This is exactly `cam_view`'s fit branch
 * written as a matrix: out = (p - centre) * R + (0, 0, dist), with R the yaw-then-pitch rotation. */
void dw4_render_fit_view(const uint8_t *pos, uint32_t nverts, float yaw, float pitch,
                         float view[16], float *fov_y, float *aspect)
{
    camera c;
    float cy, sy, cp, sp;

    fit_camera(pos, nverts, yaw, pitch, &c);
    cy = c.cy; sy = c.sy; cp = c.cp; sp = c.sp;
    view[0] = cy;      view[4] = 0.0f;  view[8]  = sy;     view[12] = -(c.cx * cy + c.cz * sy);
    view[1] = sp * sy; view[5] = cp;    view[9]  = -sp * cy; view[13] = -(c.cx * sp * sy + c.cyy * cp
                                                                     - c.cz * sp * cy);
    view[2] = -cp * sy; view[6] = sp;   view[10] = cp * cy;  view[14] = -(c.cx * -cp * sy + c.cyy * sp
                                                                     + c.cz * cp * cy) + c.dist;
    view[3] = view[7] = view[11] = 0.0f;
    view[15] = 1.0f;
    if (fov_y) *fov_y = FOV_Y;
    if (aspect) *aspect = 1.0f;
}

int dw4_render_parse_light(const char *s, dw4_light *l)
{
    float v[16];
    char type[16];
    int i = 0, n = 0;
    const char *p = s;

    memset(l, 0, sizeof(*l));
    while (*p && i < (int)sizeof(type) - 1 && *p != ',')
        type[i++] = *p++;
    type[i] = 0;
    if (*p == ',') p++;
    while (n < 16) {
        char *end;
        double d = strtod(p, &end);
        if (end == p) break;
        v[n++] = (float)d;
        p = end;
        if (*p == ',') p++;
    }
    if (!strcmp(type, "dir"))         l->type = DW4_LIGHT_DIRECTIONAL;
    else if (!strcmp(type, "point"))  l->type = DW4_LIGHT_POSITIONAL;
    else if (!strcmp(type, "spot"))   l->type = DW4_LIGHT_SPOT;
    else return -1;
    l->pos[0] = v[0]; l->pos[1] = v[1]; l->pos[2] = v[2];
    l->dir[0] = v[3]; l->dir[1] = v[4]; l->dir[2] = v[5];
    l->diffuse[0] = v[6]; l->diffuse[1] = v[7]; l->diffuse[2] = v[8];
    l->specular[0] = n > 9 ? v[9] : 0.0f;
    l->specular[1] = n > 10 ? v[10] : 0.0f;
    l->specular[2] = n > 11 ? v[11] : 0.0f;
    l->specular_on = (l->specular[0] || l->specular[1] || l->specular[2]);
    l->range = n > 12 ? v[12] : 0.0f;
    l->shininess = n > 13 ? v[13] : 16.0f;
    l->att_const = 1.0f; l->att_linear = 0.0f; l->att_quad = 0.0f;
    {
        /* a linear falloff to `range` plus a 1/d^2 term is the LINEAR_ATT shape; the quadratic
         * coefficient stays 0 unless a rig file supplies one through the same fields later */
        float fall = n > 14 ? v[14] : 0.0f, cut = n > 15 ? v[15] : 0.0f;
        l->spot_cos_falloff = cosf(fall * 3.14159265f / 180.0f);
        l->spot_cos_cutoff = cosf(cut * 3.14159265f / 180.0f);
    }
    return 0;
}

int dw4_render_load_lights(const char *path, dw4_light *out, int max)
{
    FILE *lf = fopen(path, "r");
    char line[512];
    int n = 0;

    if (!lf)
        return -1;
    while (fgets(line, sizeof(line), lf) && n < max) {
        char *h = strchr(line, '#');
        if (h) *h = 0;
        if (line[0] == '\n' || line[0] == 0) continue;
        if (dw4_render_parse_light(line, &out[n]) == 0)
            n++;
    }
    fclose(lf);
    return n;
}

int dw4_fb_init(dw4_fb *fb, int w, int h)
{
    fb->w = w;
    fb->h = h;
    fb->rgba = (uint8_t *)malloc((size_t)w * h * 4);
    fb->z = (float *)malloc((size_t)w * h * sizeof(float));
    if (!fb->rgba || !fb->z) {
        dw4_fb_free(fb);
        return -1;
    }
    return 0;
}

void dw4_fb_free(dw4_fb *fb)
{
    free(fb->rgba);
    free(fb->z);
    fb->rgba = NULL;
    fb->z = NULL;
    fb->w = fb->h = 0;
}

void dw4_fb_clear(dw4_fb *fb, uint8_t r, uint8_t g, uint8_t b)
{
    if(dw4_gpu_policy_cpu(DW4_CPU_FILL))return;
    size_t i, n = (size_t)fb->w * fb->h;
    for (i = 0; i < n; i++) {
        fb->rgba[4 * i] = r;
        fb->rgba[4 * i + 1] = g;
        fb->rgba[4 * i + 2] = b;
        fb->rgba[4 * i + 3] = 255;
        fb->z[i] = 1e30f;
    }
}

static void plot(dw4_fb *fb, int x, int y, float z, uint8_t r, uint8_t g, uint8_t b)
{
    size_t i;
    if (x < 0 || y < 0 || x >= fb->w || y >= fb->h)
        return;
    i = (size_t)y * fb->w + x;
    if (z >= fb->z[i])
        return;
    fb->z[i] = z;
    fb->rgba[4 * i] = r;
    fb->rgba[4 * i + 1] = g;
    fb->rgba[4 * i + 2] = b;
    fb->rgba[4 * i + 3] = 255;
}

/* The light rig. Glossary: N is the surface normal, L the unit direction from the surface toward
 * the light, V the direction toward the eye, H = normalize(L + V). The default rig below is a fit,
 * not a decode: the values the game feeds p2lighting are not on the disc. It is an ambient light
 * plus one directional light of (0.7931, 0.7938, 1.3141) along (0.3482, -0.9370, 0.0272). A
 * material whose `igLightingStateAttr._enabled = 0` really does want no term at all and is drawn
 * with `--unlit`. */
static dw4_light g_lights[DW4_MAX_LIGHTS];
static int g_nlights;                       /* 0 = use the built-in game rig */
static float g_ambient[3] = { 0.3005f, 0.2444f, 0.2986f };   /* re-fitted live rig */
static float g_eye[3];
static int g_eye_valid;
static dw4_fog g_fog;                       /* mode 0 = off */

void dw4_render_set_fog(const dw4_fog *fog)
{
    if (!fog)
        memset(&g_fog, 0, sizeof(g_fog));
    else
        g_fog = *fog;
}

const dw4_fog *dw4_render_get_fog(void) { return &g_fog; }

int dw4_render_parse_fog(const char *s, dw4_fog *f)
{
    char mode[16];
    const char *p = s;
    float v[6];
    int i = 0, n = 0;

    memset(f, 0, sizeof(*f));
    while (*p && i < (int)sizeof(mode) - 1 && *p != ',')
        mode[i++] = *p++;
    mode[i] = 0;
    if (*p == ',') p++;
    while (n < 6) {
        char *end;
        double d = strtod(p, &end);
        if (end == p) break;
        v[n++] = (float)d;
        p = end;
        if (*p == ',') p++;
    }
    if (!strcmp(mode, "linear"))      f->mode = DW4_FOG_LINEAR;
    else if (!strcmp(mode, "exp"))    f->mode = DW4_FOG_EXP;
    else if (!strcmp(mode, "exp2"))   f->mode = DW4_FOG_EXP2;
    else return -1;
    f->start = n > 0 ? v[0] : 0.0f;
    f->end = n > 1 ? v[1] : 0.0f;
    f->density = n > 2 ? v[2] : 0.0f;
    f->color[0] = n > 3 ? v[3] : 0.0f;
    f->color[1] = n > 4 ? v[4] : 0.0f;
    f->color[2] = n > 5 ? v[5] : 0.0f;
    return 0;
}

/* The game's own fog rig, recovered from the GS dump: the engine's stage fog is
 * a FOG_LINEAR program with near 60 / far 300 in view-space depth, lerping toward FOGCOL
 * 0xE5CCE5.  The dump's per-vertex F, extracted from the packed `XYZF2` 4th dword (PCSX2's
 * `GIFPackedRegHandlerSTQRGBAXYZF2`: F = (dword44 >> 4) & 0xff), is linear in the view depth to
 * 0.22/255 (100 % within 1) at these values, and the framebuffer is the #603 model
 * `out = C*(F/255) + FOGCOL*(1 - F/255)`.  This is the game's rig, not a fit: the pairs (60,300)
 * and (59.5,299.5) both reproduce the dump, and 60/300 appear as float pairs across the live RAM.
 * Returns 0 and fills `out`; the mode is DW4_FOG_LINEAR. */
int dw4_render_game_fog(dw4_fog *out)
{
    if (!out)
        return -1;
    memset(out, 0, sizeof(*out));
    out->mode = DW4_FOG_LINEAR;
    out->start = 60.0f;
    out->end = 300.0f;
    out->color[0] = 0xE5 / 255.0f;
    out->color[1] = 0xCC / 255.0f;
    out->color[2] = 0xE5 / 255.0f;
    return 0;
}

/* The fog factor for a fragment at view-space depth `z`, and the colour blend (the inverse of the
 * software `shade()`'s output).  `f` is 1 where the fog has no effect (near) and 0 at full fog. */
static float fog_factor(float z)
{
    float f;

    if (g_fog.mode == DW4_FOG_LINEAR) {
        if (g_fog.end <= g_fog.start)
            return 0.0f;
        f = (g_fog.end - z) / (g_fog.end - g_fog.start);
    } else if (g_fog.mode == DW4_FOG_EXP) {
        f = expf(-g_fog.density * z);
    } else if (g_fog.mode == DW4_FOG_EXP2) {
        float d = g_fog.density * z;
        f = expf(-(d * d));
    } else {
        return 1.0f;
    }
    if (f < 0.0f) f = 0.0f;
    if (f > 1.0f) f = 1.0f;
    return f;
}

void dw4_render_set_ambient(float r, float g, float b)
{
    g_ambient[0] = r; g_ambient[1] = g; g_ambient[2] = b;
}

/* One-sided or two-sided `N.L` (default two-sided).
 *
 * The game culls back faces -- the CLIP_*CULLFACE programs are the clip stage's own variants -- and
 * the LIGHT family has one- and two-sided bodies, so which one a surface gets is a material
 * question.  Two-sided folds the term with `fabs`, so a surface turned away from the light is lit
 * as if it faced it; one-sided drops that term instead (the surface keeps ambient), which is what a
 * culled front face gets in the game.  It is a knob, not a new default, because on the
 * camera-matched Goblin Pass frame it changes nothing measurable: every visible surface already has
 * `N.L > 0`, the key light sitting behind the camera.  That frame's flatness turned out to be the
 * *dropped vertex normals*, not this. */
static int g_two_sided = 1;

/* Back-face culling.  The game culls at the VU1 clip stage -- the ucode map has
 * CLIPBACK/CULLBACK and the twelve CLIP_*_CULLFACE programs, and render.c's own note above already
 * says "the engine draws front faces only" -- but every port rasteriser so far has drawn both
 * faces and relied on the z-buffer.  That is invisible on the closed world meshes and very visible
 * on the thin-shelled props (the barrel's rim and hoops shed bright slivers and a sawtooth edge
 * the game never shows).  `mode`: 0 off, 1 cull back faces, 2 cull front faces (the sign is a
 * property of the meshes' winding, so it is settled by measurement, not by assumption). */
static int g_cull = 0;

void dw4_render_set_cull(int mode) { g_cull = mode; }
int dw4_render_cull(void) { return g_cull; }

void dw4_render_set_two_sided(int on) { g_two_sided = on ? 1 : 0; }

int dw4_render_two_sided(void) { return g_two_sided; }

/* Unlit: the material is drawn with no light term at all, so the fragment colour is the texel
 * multiplied by the per-draw `tint` (the `igLightingStateAttr._enabled = 0` materials). It is a
 * global knob (`--unlit`), not a default: measured, it is a regression on the Goblin Pass frame,
 * whose meshes the engine lights per vertex. */
static int g_unlit;

void dw4_render_set_unlit(int on) { g_unlit = on ? 1 : 0; }

int dw4_render_unlit(void) { return g_unlit; }

/* Per-vertex (Gouraud) shading -- the game's own path.  The VU1 LIGHT programs compute one colour
 * per vertex from that vertex's normal and the GS interpolates the colour across the primitive, so
 * the game never interpolates a normal.  The port's per-pixel path (interpolate the normal, then
 * light) is a different function of the same inputs wherever a triangle spans a shading gradient,
 * so the game's own path is the DEFAULT (measured against the corrected native
 * framebuffer it wins the whole frame, the floor, the barrel and the crate over the fitted
 * per-pixel rig); `--per-pixel` restores the older default and `--gouraud` states it explicitly.
 * The vertex colours here use the authored vertex normals one-sided, exactly as measured
 * recovers the model from the GS dump (no eye-facing flip, which is what turns a back face lit). */
static int g_gouraud = 1;

void dw4_render_set_gouraud(int on) { g_gouraud = on ? 1 : 0; }

int dw4_render_gouraud(void) { return g_gouraud; }

void dw4_render_set_lights(const dw4_light *lights, int n)
{
    int i;
    if (n < 0) n = 0;
    if (n > DW4_MAX_LIGHTS) n = DW4_MAX_LIGHTS;
    for (i = 0; i < n; i++) g_lights[i] = lights[i];
    g_nlights = n;
}

int dw4_render_light_count(void) { return g_nlights; }

/* The game's light rig, fitted against the live p2lighting descriptors: an ambient light
 * (0.2846,0.2355,0.2976, carried by `g_ambient`) and one directional key light
 * (0.7931,0.7938,1.3141) along (0.3482,-0.9370,0.0272). `--lights` takes the original live read;
 * the values do not exist anywhere on the disc, which is why they are baked in here as the
 * default. */
static int builtin_rig(dw4_light *out, int max)
{
    dw4_light *l;
    if (max < 1)
        return 0;
    l = &out[0];
    memset(l, 0, sizeof(*l));
    l->type = DW4_LIGHT_DIRECTIONAL;
    l->dir[0] = 0.3482f; l->dir[1] = -0.9370f; l->dir[2] = 0.0272f;
    l->diffuse[0] = 0.7931f; l->diffuse[1] = 0.7938f; l->diffuse[2] = 1.3141f;
    l->att_const = 1.0f;
    return 1;
}

int dw4_render_builtin_rig(dw4_light *out, int max) { return builtin_rig(out, max); }

/* One light's contribution at surface point p with normal n, in the mesh's own space. */
static void light_term(const dw4_light *L, v3 n, v3 p, const float base[3], float out[3])
{
    v3 ldir = { 0, 0, 1 };
    float att = 1.0f, ndl, spot = 1.0f, spec = 0.0f;
    int k;

    if (L->type == DW4_LIGHT_DIRECTIONAL) {
        ldir.x = -L->dir[0]; ldir.y = -L->dir[1]; ldir.z = -L->dir[2];
    } else if (L->type == DW4_LIGHT_POSITIONAL || L->type == DW4_LIGHT_SPOT) {
        float dx = L->pos[0] - p.x, dy = L->pos[1] - p.y, dz = L->pos[2] - p.z;
        float d = sqrtf(dx * dx + dy * dy + dz * dz);
        if (d > 1e-6f) { ldir.x = dx / d; ldir.y = dy / d; ldir.z = dz / d; }
        att = 1.0f / (L->att_const + L->att_linear * d + L->att_quad * d * d);
        if (L->range > 0.0f && d >= L->range)
            att = 0.0f;
        if (L->type == DW4_LIGHT_SPOT) {
            /* the cone angle is between the spot's travel direction and the surface->light ray */
            float cd = -(L->dir[0] * ldir.x + L->dir[1] * ldir.y + L->dir[2] * ldir.z);
            if (cd < L->spot_cos_cutoff)
                att = 0.0f;
            else if (cd < L->spot_cos_falloff && L->spot_cos_falloff > L->spot_cos_cutoff)
                att *= (cd - L->spot_cos_cutoff) / (L->spot_cos_falloff - L->spot_cos_cutoff);
            (void)spot;
        }
    } else {
        return;
    }
    /* two-sided folds N.L with |.|; one-sided drops the back-facing term instead (see
     * `g_two_sided` above) */
    ndl = n.x * ldir.x + n.y * ldir.y + n.z * ldir.z;
    if (ndl < 0.0f) ndl = g_two_sided ? -ndl : 0.0f;
    for (k = 0; k < 3; k++)
        out[k] += att * (L->ambient[k] + ndl * L->diffuse[k]);
    if (L->specular_on && g_eye_valid && L->shininess > 0.0f) {
        v3 v = { g_eye[0] - p.x, g_eye[1] - p.y, g_eye[2] - p.z };
        float vl = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
        if (vl > 1e-6f) {
            float hx = ldir.x + v.x / vl, hy = ldir.y + v.y / vl, hz = ldir.z + v.z / vl;
            float hl = sqrtf(hx * hx + hy * hy + hz * hz);
            if (hl > 1e-6f) {
                float ndh = (n.x * hx + n.y * hy + n.z * hz) / hl;
                if (ndh < 0.0f) ndh = g_two_sided ? -ndh : 0.0f;
                spec = att * powf(ndh, L->shininess);
            }
        }
    }
    for (k = 0; k < 3; k++)
        out[k] += spec * L->specular[k];
    (void)base;
}

static void shade(v3 n, v3 p, float tint[3], uint8_t *out)
{
    float c[3] = { g_ambient[0], g_ambient[1], g_ambient[2] };
    int i, k;

    if (g_unlit) {
        /* no light term: the fragment colour is the mesh tint alone (which the caller sets to
         * white for a material that carries no colour) */
        c[0] = c[1] = c[2] = 1.0f;
    } else if (g_nlights > 0) {
        for (i = 0; i < g_nlights; i++)
            light_term(&g_lights[i], n, p, c, c);
    } else {
        dw4_light rig[2];
        int nr = builtin_rig(rig, 2);
        for (i = 0; i < nr; i++)
            light_term(&rig[i], n, p, c, c);
    }
    for (k = 0; k < 3; k++) {
        float v = c[k] * tint[k];
        out[k] = (uint8_t)(v < 0 ? 0 : (v > 1 ? 255 : v * 255.0f));
    }
}

/* The world/model-space eye, so a specular term has a view direction.  For the fit camera it is
 * the looked-at centre (cam_view subtracts exactly it); for a supplied view it is the world point
 * the view maps to its own origin, p = -R^T t for the row-vector view out = p*M + t. */
static void set_eye_fit(const camera *c)
{
    g_eye[0] = c->cx; g_eye[1] = c->cyy; g_eye[2] = c->cz; g_eye_valid = 1;
}

static void set_eye_view(void)
{
    float t[3] = { g_view[12], g_view[13], g_view[14] };
    g_eye[0] = -(g_view[0] * t[0] + g_view[4] * t[1] + g_view[8] * t[2]);
    g_eye[1] = -(g_view[1] * t[0] + g_view[5] * t[1] + g_view[9] * t[2]);
    g_eye[2] = -(g_view[2] * t[0] + g_view[6] * t[1] + g_view[10] * t[2]);
    g_eye_valid = 1;
}

/* ---- near-plane clipping ----------------------------------------------------------------
 * The camera sits *inside* the stage's ground and wall geometry, so a triangle that straddles the near plane is
 * common and must not be dropped -- dropping it is what left the frame's "gaps".  Clip each
 * triangle to z >= DW4_NEAR_Z and rasterise the resulting polygon: interpolate in view space
 * (the view transform is affine, so every mesh-space attribute interpolates with the same t),
 * reproject each new vertex, and fan-triangulate.  With all three vertices inside this is the
 * single triangle the old code drew. */
#define DW4_NEAR_Z 0.05f

typedef struct {
    float vx, vy, vz;   /* view-space position, for the clip      */
    float sx, sy, sz;   /* screen x/y and view-space depth        */
    float p[3];         /* mesh-space position (for shading)      */
    float nx, ny, nz;   /* mesh-space normal, when the mesh has one */
    float u, v;         /* texcoord, when the mesh has one        */
    float fog;          /* per-vertex fog factor (the VU1 FOG output), 1 = clear */
} rvert;

static void project_view(int width, int height, v3 v, float *sx, float *sy, float *sz)
{
    float f, z = v.z;
    if (z <= 0.0f)
        z = 1e-6f;
    if (g_use_view) {
        f = (float)height / (2.0f * tanf(g_fov * 0.5f));
        *sx = (v.x / z) * f * g_aspect + (float)width * 0.5f;
        *sy = -(v.y / z) * f + (float)height * 0.5f;
    } else {
        f = (float)height / (2.0f * tanf(FOV_Y * 0.5f));
        *sx = (v.x / z) * f + (float)width * 0.5f;
        *sy = -(v.y / z) * f + (float)height * 0.5f;
    }
    *sz = v.z;
}

static rvert rvert_lerp(const rvert *a, const rvert *b, float t, int width, int height)
{
    rvert r;
    v3 v;
    r.vx = a->vx + (b->vx - a->vx) * t;
    r.vy = a->vy + (b->vy - a->vy) * t;
    r.vz = a->vz + (b->vz - a->vz) * t;
    v.x = r.vx; v.y = r.vy; v.z = r.vz;
    project_view(width, height, v, &r.sx, &r.sy, &r.sz);
    r.p[0] = a->p[0] + (b->p[0] - a->p[0]) * t;
    r.p[1] = a->p[1] + (b->p[1] - a->p[1]) * t;
    r.p[2] = a->p[2] + (b->p[2] - a->p[2]) * t;
    r.nx = a->nx + (b->nx - a->nx) * t;
    r.ny = a->ny + (b->ny - a->ny) * t;
    r.nz = a->nz + (b->nz - a->nz) * t;
    r.u = a->u + (b->u - a->u) * t;
    r.v = a->v + (b->v - a->v) * t;
    r.fog = a->fog + (b->fog - a->fog) * t;
    return r;
}

/* Linear or nearest texel filtering (linear by default).
 *
 * The packs' own materials settle this: 300 of the 323 `igTextureAttr` records behind packs 614/621's
 * `igTextureBindAttr`s carry `_magFilter = _minFilter = 1`, and the 23 that carry 0 are the
 * placeholder records `PromotedAttr`/`WN04` -- so every named material asks for linear with no
 * mipmaps (`_mipmapMode = 0`).  Nearest sampling shows wherever a texture is magnified (the real
 * frame's floor in front of the camera is soft and the nearest-sampled frame is blocky), and linear
 * is the one change that moves the camera-matched frame toward the real capture.  `g_tex_filter`
 * drives both paths -- `gl_render.c` maps it to GL_LINEAR / GL_NEAREST. */
static int g_tex_filter = 1;   /* 0 = nearest (the earlier port), 1 = linear */

/* The engine's texture matrix (`igTextureMatrixAttr._m`).  Every live instance is the
 * identity with a translation in elements 12..13 and `_isProjective = 0`, so for the sampler it is a
 * UV offset plus, where it matters, a scale: `uv' = (uv * scale) + offset`.  The ground material (`BGGround00n`)
 * *enables* the unit (`igTextureMatrixStateAttr._enabled = 1`) without carrying a matrix, which is
 * the tile/UV question -- these knobs exist so the offset can be measured against
 * the real frame and then looked up in the live matrices. */
static float g_uv_scale = 1.0f;
static float g_uv_off[2];

void dw4_render_set_uv_offset(float u, float v) { g_uv_off[0] = u; g_uv_off[1] = v; }
void dw4_render_set_uv_scale(float s) { g_uv_scale = s > 0.0f ? s : 1.0f; }

void dw4_render_set_tex_filter(int on) { g_tex_filter = on ? 1 : 0; }

int dw4_render_tex_filter(void) { return g_tex_filter; }

/* One texel, clamped to the grid.  Every mesh here maps a full atlas and stays inside it, so
 * clamp and the GS's repeat mode agree over the drawn geometry. */
int dw4_render_tex_wrap;

static const uint8_t *texel(const dw4_tex *t, int x, int y)
{
    if (dw4_render_tex_wrap) {
        x %= (int)t->w; if (x < 0) x += (int)t->w;
        y %= (int)t->h; if (y < 0) y += (int)t->h;
        return t->rgba + 4 * ((size_t)y * t->w + x);
    }
    if (x < 0) x = 0; else if (x >= (int)t->w) x = (int)t->w - 1;
    if (y < 0) y = 0; else if (y >= (int)t->h) y = (int)t->h - 1;
    return t->rgba + 4 * ((size_t)y * t->w + x);
}

/* GS bilinear (TEX1 MMAG/MMIN linear): the four texels around (u*w - 0.5, v*h - 0.5), RGBA blended
 * by the fractional position, with the layer's wrap or the default clamp applied per texel. */
int dw4_render_tex_linear;

/* The GS alpha test (ATE=1, ATST=GREATER): a fragment whose `(At * Av) >> 7` is not above this is not
 * drawn, and does not write depth.  -1 (the default) is off.  The layer sets it per mesh from the pack's
 * `igAlphaFunctionAttr` (AREF = floor(_refValue * 128)). */
int dw4_render_aref = -1;

/* The layer's depth buffer (ZTST=GEQUAL, ZMSK=0): one float per pixel, larger = nearer, cleared to 0 by
 * `dw4_render_zbuf_clear`.  Only `dw4_render_ui_tri_stq_z` tests it. */
static float *g_zb;
static size_t g_zbn;

void dw4_render_zbuf_clear(const dw4_fb *fb)
{
    if(dw4_gpu_policy_cpu(DW4_CPU_FILL))return;
    size_t n = (size_t)fb->w * fb->h;

    if (n > g_zbn) {
        float *nz = (float *)realloc(g_zb, n * sizeof *g_zb);

        if (!nz)
            return;
        g_zb = nz;
        g_zbn = n;
    }
    memset(g_zb, 0, n * sizeof *g_zb);
}

/* A texel with the wrap/clamp mode already decided: `mx`/`my` are width-1 / height-1 when the size is a power
 * of two (wrap by mask), else -1 (wrap by modulo).  The per-pixel path calls this, not `texel()`. */
static inline const uint8_t *texel_p(const dw4_tex *t, int x, int y, int wrap, int mx, int my)
{
    if (wrap) {
        if (mx >= 0) x &= mx; else { x %= (int)t->w; if (x < 0) x += (int)t->w; }
        if (my >= 0) y &= my; else { y %= (int)t->h; if (y < 0) y += (int)t->h; }
    } else {
        if (x < 0) x = 0; else if (x >= (int)t->w) x = (int)t->w - 1;
        if (y < 0) y = 0; else if (y >= (int)t->h) y = (int)t->h - 1;
    }
    return t->rgba + 4 * ((size_t)y * t->w + x);
}

/* The 2D UI overlay. The game's HUD and every other 2D element are drawn straight to the GS in
 * screen space, unlit, with a constant per-vertex colour and the texture as a MODULATE, over the
 * scene with `ALPHA A0 B1 C0 D1`. The port has no UI system, so `--ui` replays the draws a `.gs`
 * dump recorded: this rasterises one such triangle into the framebuffer already holding the scene.
 * It is a reproduction path, not the native UI a port needs. */
/* The GS's per-pixel output, `Cv = ((A-B)*As + (C*Ad)) + D` with Ad = 0 (the menu's framebuffer is
 * 24-bit), clamped.  Three cases appear in the front-end's draws:
 *
 *   blend 0  ABE off, an opaque pass: the colour replaces the destination (and these were being
 *            dropped outright, which is most of why the backdrop came out dark)
 *   blend 1  ALPHA 0x44  A=Cs B=Cd C=Cs D=Cd  ->  (Cs-Cd)*As + Cd   the ordinary alpha blend
 *   blend 2  ALPHA 0x48  A=Cs B=0  C=Cs D=Cd  ->  Cs*As + Cd        ADDITIVE -- the light passes
 *
 * `r,g,b` arrive as `Cs*As` already (As being 1 for the opaque case). */
float dw4_render_alpha_ref = -1.0f;   /* >=0: GS alpha test, discard a fragment whose texel alpha
                                       * (as 0..1) is below this.  Off (-1) by default. */

static void ui_out(uint8_t *d, float r, float g, float b, float as, uint8_t blend, unsigned color_mask)
{
    if (blend == 2) {                            /* Cs*As + Cd */
        r += (float)d[0];
        g += (float)d[1];
        b += (float)d[2];
    } else if (blend == 1) {                     /* (Cs-Cd)*As + Cd */
        float inv = 1.0f - as;
        r += (float)d[0] * inv;
        g += (float)d[1] * inv;
        b += (float)d[2] * inv;
    }                                            /* blend 0: replace */
    if(!(color_mask & 1)) d[0] = r > 255.0f ? 255 : (r < 0.0f ? 0 : (uint8_t)(r + 0.5f));
    if(!(color_mask & 2)) d[1] = g > 255.0f ? 255 : (g < 0.0f ? 0 : (uint8_t)(g + 0.5f));
    if(!(color_mask & 4)) d[2] = b > 255.0f ? 255 : (b < 0.0f ? 0 : (uint8_t)(b + 0.5f));
    if(!(color_mask & 8)) d[3] = 255;
}

/* The two kernels below are the per-triangle work; `dw4_render_ui_draws` drives them over a whole
 * draw list. `ylo`/`yhi` clip the rows this call may touch, which lets the replay be split across
 * threads by horizontal band: a draw only ever writes pixels inside its own bbox, so a band sees
 * exactly the writes it would have seen in the serial pass, in the same order, and the result is
 * bit-identical. */
static void ui_tri_stq(dw4_fb *fb, const float v0[5], const float v1[5], const float v2[5],
                       const uint8_t rgba[3][4], const dw4_tex *tex, uint8_t blend,
                       int ylo, int yhi, const float *tz, int aref, const float *tf, int no_depth_write, int straight_rgb, const uint8_t *fog_color, int gs_raster,int depth_always,int filter,unsigned color_mask)
{
    float det, minx, maxx, miny, maxy;
    float inv_det, dwdx_a, dwdx_b, dsx, dtx, dqx, dcrx, dcgx, dcbx, dcax;
    int x, y, x0, x1, y0, y1;
    /* GS-grid submissions use integer top-left edges at integer pixel positions. Legacy
     * layers retain their displaced sample convention and UI its inclusive
     * 0.002 bias, preserving the established frontend raster contract. */
    const int wrap = dw4_render_tex_wrap, linear = filter?filter==2:dw4_render_tex_linear;
    const int tw = tex ? tex->w : 0, th = tex ? tex->h : 0;
    const int mx = (wrap && tex && (tw & (tw - 1)) == 0) ? tw - 1 : -1;
    const int my = (wrap && tex && (th & (th - 1)) == 0) ? th - 1 : -1;
    const float ftw = (float)tw, fth = (float)th;
    const float ox = gs_raster ? 0 : dw4_render_tex_wrap ? 0.5f + 1.0f / 64.0f : 0.5f;
    const float oy = gs_raster ? 0 : dw4_render_tex_wrap ? 0.5f + 1.0f / 128.0f : 0.5f;
    const float tol = dw4_render_tex_wrap ? 0.0f : 0.002f;

    det = (v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]);
    if (det > -1e-6f && det < 1e-6f)
        return;
    int64_t edge_dx[3]={0},edge_dy[3]={0},edge_x[3]={0},edge_y[3]={0};
    int inclusive[3]={0};
    if(gs_raster) {
        const float *v[3]={v0,v1,v2};
        for(unsigned e=0;e<3;e++) {
            unsigned a=det>0?e:(e+1)%3,b=det>0?(e+1)%3:e;
            edge_x[e]=(int64_t)lrintf(v[a][0]*16);edge_y[e]=(int64_t)lrintf(v[a][1]*16);
            edge_dx[e]=(int64_t)lrintf(v[b][0]*16)-edge_x[e];
            edge_dy[e]=(int64_t)lrintf(v[b][1]*16)-edge_y[e];
            inclusive[e]=edge_dy[e]<0 || (edge_dy[e]==0 && edge_dx[e]>0);
        }
    }
    minx = v0[0] < v1[0] ? v0[0] : v1[0]; if (v2[0] < minx) minx = v2[0];
    maxx = v0[0] > v1[0] ? v0[0] : v1[0]; if (v2[0] > maxx) maxx = v2[0];
    miny = v0[1] < v1[1] ? v0[1] : v1[1]; if (v2[1] < miny) miny = v2[1];
    maxy = v0[1] > v1[1] ? v0[1] : v1[1]; if (v2[1] > maxy) maxy = v2[1];
    x0 = (int)minx; if (x0 < 0) x0 = 0;
    x1 = (int)maxx + 1; if (x1 > fb->w - 1) x1 = fb->w - 1;
    y0 = (int)miny; if (y0 < 0) y0 = 0; if (y0 < ylo) y0 = ylo;
    y1 = (int)maxy + 1; if (y1 > fb->h - 1) y1 = fb->h - 1; if (y1 > yhi) y1 = yhi;
    if (y0 > y1)
        return;
    /* The per-pixel work is the whole cost of a menu frame (measured: 62.5 ms full, 12.3 ms with the
     * UI's textures switched off -- so it is here, not in the parsing), and it used to be four float
     * divides and a dozen multiplies per pixel.  Every interpolated value is *linear in x*: the
     * barycentric weights come from edge functions and the attributes and the GS's per-vertex colour
     * are affine in those weights, so a row computes its starting values once and then only adds.
     * The STQ divide survives (s/q is not linear), but it is one reciprocal shared by both axes
     * rather than two divides.  The additions accumulate rounding across a row; the inside test's
     * 0.002 bias is three orders of magnitude larger than that drift, so coverage is unchanged. */
    inv_det = 1.0f / det;
    dwdx_a = -(v1[1] - v0[1]) * inv_det;      /* d(wa)/dx */
    dwdx_b = (v2[1] - v0[1]) * inv_det;       /* d(wb)/dx */
    dsx = dwdx_a * (v2[2] - v0[2]) + dwdx_b * (v1[2] - v0[2]);
    dtx = dwdx_a * (v2[3] - v0[3]) + dwdx_b * (v1[3] - v0[3]);
    dqx = dwdx_a * (v2[4] - v0[4]) + dwdx_b * (v1[4] - v0[4]);
    dcrx = dwdx_a * (float)(rgba[2][0] - rgba[0][0]) + dwdx_b * (float)(rgba[1][0] - rgba[0][0]);
    dcgx = dwdx_a * (float)(rgba[2][1] - rgba[0][1]) + dwdx_b * (float)(rgba[1][1] - rgba[0][1]);
    dcbx = dwdx_a * (float)(rgba[2][2] - rgba[0][2]) + dwdx_b * (float)(rgba[1][2] - rgba[0][2]);
    dcax = dwdx_a * (float)(rgba[2][3] - rgba[0][3]) + dwdx_b * (float)(rgba[1][3] - rgba[0][3]);
    for (y = y0; y <= y1; y++) {
        float py = y + oy;
        float wa = ((v1[0] - v0[0]) * (py - v0[1]) - (x0 + ox - v0[0]) * (v1[1] - v0[1])) * inv_det;
        float wb = ((x0 + ox - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (py - v0[1])) * inv_det;
        float s = v0[2] + wa * (v2[2] - v0[2]) + wb * (v1[2] - v0[2]);
        float t = v0[3] + wa * (v2[3] - v0[3]) + wb * (v1[3] - v0[3]);
        float q = v0[4] + wa * (v2[4] - v0[4]) + wb * (v1[4] - v0[4]);
        float cr = (float)rgba[0][0] + wa * (float)(rgba[2][0] - rgba[0][0])
                                        + wb * (float)(rgba[1][0] - rgba[0][0]);
        float cg = (float)rgba[0][1] + wa * (float)(rgba[2][1] - rgba[0][1])
                                        + wb * (float)(rgba[1][1] - rgba[0][1]);
        float cb = (float)rgba[0][2] + wa * (float)(rgba[2][2] - rgba[0][2])
                                        + wb * (float)(rgba[1][2] - rgba[0][2]);
        float cav = (float)rgba[0][3] + wa * (float)(rgba[2][3] - rgba[0][3])
                                       + wb * (float)(rgba[1][3] - rgba[0][3]);
        for (x = x0; x <= x1; x++) {
            float inv_q, u, v, ca, sa;
            uint8_t *d;
            int outside=0;
            if(gs_raster) for(unsigned e=0;e<3;e++) {
                int64_t value=edge_dx[e]*((int64_t)y*16-edge_y[e])-
                              edge_dy[e]*((int64_t)x*16-edge_x[e]);
                if(value<0 || (!value && !inclusive[e])) {outside=1;break;}
            }
            if (gs_raster?outside:(wa < -tol || wb < -tol || wa + wb > 1.0f + tol)) {
                wa += dwdx_a; wb += dwdx_b; s += dsx; t += dtx; q += dqx;
                cr += dcrx; cg += dcgx; cb += dcbx; cav += dcax;
                continue;
            }
            if (q > -1e-9f && q < 1e-9f)
                q = 1e-9f;
            inv_q = 1.0f / q;
            u = s * inv_q;
            v = t * inv_q;
            if (tex) {
                uint8_t lin[4];
                const uint8_t *tx;

                if (linear) {
                    float fx = u * ftw - 0.5f, fy = v * fth - 0.5f;
                    int ix = (int)fx, iy = (int)fy, k;
                    float ax, ay;
                    const uint8_t *p00, *p10, *p01, *p11;

                    if (fx < (float)ix) ix--;      /* floor without the libm call */
                    if (fy < (float)iy) iy--;
                    ax = fx - (float)ix; ay = fy - (float)iy;
                    p00 = texel_p(tex, ix, iy, wrap, mx, my);
                    p10 = texel_p(tex, ix + 1, iy, wrap, mx, my);
                    p01 = texel_p(tex, ix, iy + 1, wrap, mx, my);
                    p11 = texel_p(tex, ix + 1, iy + 1, wrap, mx, my);
                    for (k = 0; k < 4; k++) {
                        if(gs_raster) {
                            unsigned wx=(unsigned)(ax*16),wy=(unsigned)(ay*16);
                            unsigned top=(p00[k]*(16-wx)+p10[k]*wx)>>4;
                            unsigned bot=(p01[k]*(16-wx)+p11[k]*wx)>>4;
                            lin[k]=(top*(16-wy)+bot*wy)>>4;
                            continue;
                        }
                        float top = (float)p00[k] + ((float)p10[k] - (float)p00[k]) * ax;
                        float bot = (float)p01[k] + ((float)p11[k] - (float)p01[k]) * ax;
                        lin[k] = (uint8_t)(top + (bot - top) * ay + 0.5f);
                    }
                    tx = lin;
                } else {
                    float fx = u * ftw, fy = v * fth;
                    int ix = (int)fx, iy = (int)fy;

                    if (fx < (float)ix) ix--;
                    if (fy < (float)iy) iy--;
                    tx = texel_p(tex, ix, iy, wrap, mx, my);
                }
                ca = (float)tx[3] * (cav * (1.0f / 16384.0f));   /* (At*Av)/128^2 */
                if (ca > 1.0f) ca = 1.0f;
                if (aref >= 0 && (int)((float)tx[3] * cav * (1.0f / 128.0f)) <= aref) {
                    wa += dwdx_a; wb += dwdx_b; s += dsx; t += dtx; q += dqx;
                    cr += dcrx; cg += dcgx; cb += dcbx; cav += dcax;
                    continue;                      /* AFAIL = KEEP: nothing written */
                }
                if (tz && g_zb) {
                    float zz = floorf(tz[0] + wa * (tz[2] - tz[0]) + wb * (tz[1] - tz[0]) + (gs_raster?0:0.5f));
                    float *zp = &g_zb[(size_t)y * fb->w + x];

                    if (!depth_always && zz < *zp) { /* ZTST = GEQUAL */
                        wa += dwdx_a; wb += dwdx_b; s += dsx; t += dtx; q += dqx;
                        cr += dcrx; cg += dcgx; cb += dcbx; cav += dcax;
                        continue;
                    }
                    if (!no_depth_write) *zp = zz;
                }
                if (dw4_render_alpha_ref < 0.0f || ca >= dw4_render_alpha_ref) {
                    d = fb->rgba + 4 * ((size_t)y * fb->w + x);
                    sa = (blend == 0) ? 1.0f : ca;
                    float pr = (float)tx[0] * (cr * (1.0f / 128.0f));
                    float pg = (float)tx[1] * (cg * (1.0f / 128.0f));
                    float pb = (float)tx[2] * (cb * (1.0f / 128.0f));
                    if(gs_raster) {
                        pr=fminf(255,floorf(tx[0]*floorf(cr*128)/16384));
                        pg=fminf(255,floorf(tx[1]*floorf(cg*128)/16384));
                        pb=fminf(255,floorf(tx[2]*floorf(cb*128)/16384));
                        ca=fminf(1,floorf(tx[3]*floorf(cav*128)/16384)/128);
                    }

                    if (tf) {                      /* the GS fog stage, FOGCOL white: C = Cs*F + (1-F)*255 */
                        float ff = (tf[0] + wa * (tf[2] - tf[0]) + wb * (tf[1] - tf[0])) * (1.0f / 255.0f);

                        if (ff < 0.0f) ff = 0.0f; else if (ff > 1.0f) ff = 1.0f;
                        if(gs_raster) {
                            float f=floorf(ff*255*128)/32768;
                            float fr=fog_color?fog_color[0]:255,fg=fog_color?fog_color[1]:255,fb=fog_color?fog_color[2]:255;
                            pr=fr+floorf((pr-fr)*f);pg=fg+floorf((pg-fg)*f);pb=fb+floorf((pb-fb)*f);
                        } else {
                            pr = pr * ff + (fog_color ? fog_color[0] : 255.0f) * (1.0f - ff);
                            pg = pg * ff + (fog_color ? fog_color[1] : 255.0f) * (1.0f - ff);
                            pb = pb * ff + (fog_color ? fog_color[2] : 255.0f) * (1.0f - ff);
                        }
                    }
                    if(gs_raster && straight_rgb) {
                        float rgb[3]={pr,pg,pb};
                        for(unsigned k=0;k<3;k++) {
                            float v=rgb[k];
                            if(blend==1) v=d[k]+floorf((v-d[k])*ca);
                            else if(blend==2) v=d[k]+floorf(v*ca);
                            if(!(color_mask & (1u<<k))) d[k]=(uint8_t)fminf(255,fmaxf(0,v));
                        }
                        if(!(color_mask & 8)) d[3]=255;
                        goto pixel_done;
                    }
                    float rgb_alpha = straight_rgb && blend == 0 ? 1.0f : ca;
                    ui_out(d, pr*rgb_alpha, pg*rgb_alpha, pb*rgb_alpha, sa, blend, color_mask);
                }
            } else {
                ca = cav * (1.0f / 128.0f);
                if (ca > 1.0f) ca = 1.0f;
                d = fb->rgba + 4 * ((size_t)y * fb->w + x);
                sa = (blend == 0) ? 1.0f : ca;
                float rgb_alpha = straight_rgb && blend == 0 ? 1.0f : ca;
                ui_out(d, cr*2.0f*rgb_alpha, cg*2.0f*rgb_alpha, cb*2.0f*rgb_alpha, sa, blend, color_mask);
            }
pixel_done:
            wa += dwdx_a; wb += dwdx_b; s += dsx; t += dtx; q += dqx;
            cr += dcrx; cg += dcgx; cb += dcbx; cav += dcax;
        }
    }
}

static void ui_tri(dw4_fb *fb, const float v0[4], const float v1[4], const float v2[4],
                   const uint8_t rgba[3][4], const dw4_tex *tex, uint8_t blend,
                   int ylo, int yhi, unsigned color_mask)
{
    float det, minx, maxx, miny, maxy;
    float inv_det, dwdx_a, dwdx_b, dsx, dtx, dcrx, dcgx, dcbx, dcax;
    int x, y, x0, x1, y0, y1;

    det = (v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]);
    if (det > -1e-6f && det < 1e-6f)
        return;
    minx = v0[0] < v1[0] ? v0[0] : v1[0]; if (v2[0] < minx) minx = v2[0];
    maxx = v0[0] > v1[0] ? v0[0] : v1[0]; if (v2[0] > maxx) maxx = v2[0];
    miny = v0[1] < v1[1] ? v0[1] : v1[1]; if (v2[1] < miny) miny = v2[1];
    maxy = v0[1] > v1[1] ? v0[1] : v1[1]; if (v2[1] > maxy) maxy = v2[1];
    x0 = (int)minx; if (x0 < 0) x0 = 0;
    x1 = (int)maxx + 1; if (x1 > fb->w - 1) x1 = fb->w - 1;
    y0 = (int)miny; if (y0 < 0) y0 = 0; if (y0 < ylo) y0 = ylo;
    y1 = (int)maxy + 1; if (y1 > fb->h - 1) y1 = fb->h - 1; if (y1 > yhi) y1 = yhi;
    if (y0 > y1)
        return;
    /* see ui_tri_stq: same hoisting, and here there is no divide left in the inner loop at all */
    inv_det = 1.0f / det;
    dwdx_a = -(v1[1] - v0[1]) * inv_det;
    dwdx_b = (v2[1] - v0[1]) * inv_det;
    dsx = dwdx_a * (v2[2] - v0[2]) + dwdx_b * (v1[2] - v0[2]);
    dtx = dwdx_a * (v2[3] - v0[3]) + dwdx_b * (v1[3] - v0[3]);
    dcrx = dwdx_a * (float)(rgba[2][0] - rgba[0][0]) + dwdx_b * (float)(rgba[1][0] - rgba[0][0]);
    dcgx = dwdx_a * (float)(rgba[2][1] - rgba[0][1]) + dwdx_b * (float)(rgba[1][1] - rgba[0][1]);
    dcbx = dwdx_a * (float)(rgba[2][2] - rgba[0][2]) + dwdx_b * (float)(rgba[1][2] - rgba[0][2]);
    dcax = dwdx_a * (float)(rgba[2][3] - rgba[0][3]) + dwdx_b * (float)(rgba[1][3] - rgba[0][3]);
    for (y = y0; y <= y1; y++) {
        float py = y + 0.5f;
        float wa = ((v1[0] - v0[0]) * (py - v0[1]) - (x0 + 0.5f - v0[0]) * (v1[1] - v0[1])) * inv_det;
        float wb = ((x0 + 0.5f - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (py - v0[1])) * inv_det;
        float u = v0[2] + wa * (v2[2] - v0[2]) + wb * (v1[2] - v0[2]);
        float v = v0[3] + wa * (v2[3] - v0[3]) + wb * (v1[3] - v0[3]);
        float cr = (float)rgba[0][0] + wa * (float)(rgba[2][0] - rgba[0][0])
                                        + wb * (float)(rgba[1][0] - rgba[0][0]);
        float cg = (float)rgba[0][1] + wa * (float)(rgba[2][1] - rgba[0][1])
                                        + wb * (float)(rgba[1][1] - rgba[0][1]);
        float cb = (float)rgba[0][2] + wa * (float)(rgba[2][2] - rgba[0][2])
                                        + wb * (float)(rgba[1][2] - rgba[0][2]);
        float cav = (float)rgba[0][3] + wa * (float)(rgba[2][3] - rgba[0][3])
                                       + wb * (float)(rgba[1][3] - rgba[0][3]);
        for (x = x0; x <= x1; x++) {
            uint8_t *d;
            if (wa < -0.002f || wb < -0.002f || wa + wb > 1.002f) {
                wa += dwdx_a; wb += dwdx_b; u += dsx; v += dtx;
                cr += dcrx; cg += dcgx; cb += dcbx; cav += dcax;
                continue;
            }
            if (tex) {
                const uint8_t *t = texel(tex, (int)floorf(u * (float)tex->w), (int)floorf(v * (float)tex->h));
                float ca = (float)t[3] * (cav * (1.0f / 16384.0f));
                float sa;
                if (ca > 1.0f) ca = 1.0f;
                if (dw4_render_alpha_ref < 0.0f || ca >= dw4_render_alpha_ref) {
                    d = fb->rgba + 4 * ((size_t)y * fb->w + x);
                    sa = (blend == 0) ? 1.0f : ca;
                    ui_out(d, (float)t[0] * (cr * (1.0f / 128.0f)) * ca,
                           (float)t[1] * (cg * (1.0f / 128.0f)) * ca,
                           (float)t[2] * (cb * (1.0f / 128.0f)) * ca, sa, blend, color_mask);
                }
            } else {
                float ca = cav * (1.0f / 128.0f);
                float sa;
                if (ca > 1.0f) ca = 1.0f;
                d = fb->rgba + 4 * ((size_t)y * fb->w + x);
                sa = (blend == 0) ? 1.0f : ca;
                ui_out(d, cr * 2.0f * ca, cg * 2.0f * ca, cb * 2.0f * ca, sa, blend, color_mask);
            }
            wa += dwdx_a; wb += dwdx_b; u += dsx; v += dtx;
            cr += dcrx; cg += dcgx; cb += dcbx; cav += dcax;
        }
    }
}

void dw4_render_ui_tri(dw4_fb *fb, const float v0[4], const float v1[4], const float v2[4],
                       const uint8_t rgba[3][4], const dw4_tex *tex, uint8_t blend)
{
    if(dw4_gpu_policy_cpu(DW4_CPU_UI))return;
    ui_tri(fb, v0, v1, v2, rgba, tex, blend, 0, (int)fb->h - 1, 0);
}

void dw4_render_ui_tri_stq(dw4_fb *fb, const float v0[5], const float v1[5], const float v2[5],
                           const uint8_t rgba[3][4], const dw4_tex *tex, uint8_t blend)
{
    if(dw4_gpu_policy_cpu(DW4_CPU_UI))return;
    ui_tri_stq(fb, v0, v1, v2, rgba, tex, blend, 0, (int)fb->h - 1, NULL, dw4_render_aref, NULL, 0, 0, NULL, 0,0,0,0);
}

/* Replaying a whole draw list across threads. The UI replay is a list of independent draws that
 * must be applied in order (the blends compose), so the parallel axis is the rows: every band
 * replays the whole list, each draw clipped to that band. The frame is bit-identical to the serial
 * pass. Bands are handed out by an atomic counter so a band full of large triangles cannot leave
 * the other threads idle. */
typedef struct {
    dw4_fb *fb;
    const dw4_ui_draw *draws;
    const dw4_layer_draw *ldraws;   /* the layer's list, when non-NULL (used instead of `draws`) */
    int n;
    int nband;
    int bandh;
    int next;                 /* atomic: the next band to claim */
    int nthreads;
} ui_job;

static void layer_run_band(dw4_fb *fb, const dw4_layer_draw *d, int n, int ylo, int yhi)
{
    int i;
    for (i = 0; i < n; i++) {
        const dw4_layer_draw *u = &d[i];
        ui_tri_stq(fb, u->v[0], u->v[1], u->v[2], u->rgba, u->tex, u->blend, ylo, yhi, u->z, u->aref,
                   u->fog ? u->f : NULL, u->no_depth_write, u->straight_rgb, u->fog == 2 ? u->fog_color : NULL, u->gs_raster,u->depth_always,u->filter,u->color_mask);
    }
}

static void ui_run_band(dw4_fb *fb, const dw4_ui_draw *d, int n, int ylo, int yhi)
{
    int i;
    for (i = 0; i < n; i++) {
        const dw4_ui_draw *u = &d[i];
        if (u->stq)
            ui_tri_stq(fb, u->v[0], u->v[1], u->v[2], u->rgba, u->tex, u->blend, ylo, yhi, u->depth_mode?u->z:NULL, dw4_render_aref, NULL, !u->depth_write, u->gs_raster, NULL, u->gs_raster,u->depth_mode==2,u->filter,u->color_mask);
        else
            ui_tri(fb, u->v[0], u->v[1], u->v[2], u->rgba, u->tex, u->blend, ylo, yhi,u->color_mask);
    }
}

#ifdef DW4_ENABLE_THREADS
#include <pthread.h>
static void *ui_worker(void *argp)
{
    ui_job *j = (ui_job *)argp;
    for (;;) {
        int b = __atomic_fetch_add(&j->next, 1, __ATOMIC_RELAXED);
        int ylo, yhi;
        if (b >= j->nband)
            break;
        ylo = b * j->bandh;
        yhi = ylo + j->bandh - 1;
        if (yhi > (int)j->fb->h - 1)
            yhi = (int)j->fb->h - 1;
        if (j->ldraws)
            layer_run_band(j->fb, j->ldraws, j->n, ylo, yhi);
        else
            ui_run_band(j->fb, j->draws, j->n, ylo, yhi);
    }
    return NULL;
}
#endif

void dw4_render_ui_draws(dw4_fb *fb, const dw4_ui_draw *draws, int n, int nthreads)
{
    ui_job j;
    if (!fb || !draws || n <= 0)
        return;
    if(dw4_gpu_policy_cpu(DW4_CPU_UI))return;
#ifdef DW4_ENABLE_THREADS
    if (nthreads > 1 && fb->h >= 32) {
        pthread_t th[32];
        int i, nt = nthreads;
        if (nt > 32)
            nt = 32;
        if (nt > (int)fb->h)
            nt = (int)fb->h;
        j.fb = fb;
        j.draws = draws;
        j.ldraws = NULL;
        j.n = n;
        j.nthreads = nt;
        /* more bands than threads, so the work items are small enough to balance out */
        j.bandh = (int)fb->h / (nt * 4);
        if (j.bandh < 8)
            j.bandh = 8;
        j.nband = ((int)fb->h + j.bandh - 1) / j.bandh;
        j.next = 0;
        for (i = 0; i < nt; i++)
            if (pthread_create(&th[i], NULL, ui_worker, &j) != 0)
                break;
        if (i == 0) {
            ui_run_band(fb, draws, n, 0, (int)fb->h - 1);   /* no thread came up: do it here */
            return;
        }
        while (i-- > 0)
            pthread_join(th[i], NULL);
        return;
    }
#else
    (void)nthreads;
#endif
    ui_run_band(fb, draws, n, 0, (int)fb->h - 1);
}

void dw4_render_layer_draws(dw4_fb *fb, const dw4_layer_draw *draws, int n, int nthreads)
{
    if (!fb || !draws || n <= 0)
        return;
    if(dw4_gpu_policy_cpu(DW4_CPU_LAYER))return;
#ifdef DW4_ENABLE_THREADS
    if (nthreads > 1 && fb->h >= 32) {
        ui_job j;
        pthread_t th[32];
        int i, nt = nthreads;

        if (nt > 32)
            nt = 32;
        j.fb = fb;
        j.draws = NULL;
        j.ldraws = draws;
        j.n = n;
        j.nthreads = nt;
        j.bandh = (int)fb->h / (nt * 4);
        if (j.bandh < 8)
            j.bandh = 8;
        j.nband = ((int)fb->h + j.bandh - 1) / j.bandh;
        j.next = 0;
        for (i = 0; i < nt; i++)
            if (pthread_create(&th[i], NULL, ui_worker, &j) != 0)
                break;
        if (i == 0) {
            layer_run_band(fb, draws, n, 0, (int)fb->h - 1);
            return;
        }
        while (i-- > 0)
            pthread_join(th[i], NULL);
        return;
    }
#else
    (void)nthreads;
#endif
    layer_run_band(fb, draws, n, 0, (int)fb->h - 1);
}

static void raster_tri(dw4_fb *fb, const rvert *A, const rvert *B, const rvert *C,
                       const dw4_tex *tex, float tint[3], int smooth)
{
    v3 e1, e2, n, na, nb, nd, pa, pb, pd, pc;
    uint8_t col[3] = { 0, 0, 0 };
    float minx, maxx, miny, maxy, det;
    float ua = A->u, va = A->v, ub = B->u, vb = B->v, ud = C->u, vd = C->v;
    float sax = A->sx, say = A->sy, sbx = B->sx, sby = B->sy, sdx = C->sx, sdy = C->sy;
    float saz = A->sz, sbz = B->sz, sdz = C->sz;
    float sfa = A->fog, sfb = B->fog, sfc = C->fog;   /* per-vertex fog (the VU1 FOG output) */
    int x, y;

    pa.x = A->p[0]; pa.y = A->p[1]; pa.z = A->p[2];
    pb.x = B->p[0]; pb.y = B->p[1]; pb.z = B->p[2];
    pd.x = C->p[0]; pd.y = C->p[1]; pd.z = C->p[2];
    na.x = A->nx; na.y = A->ny; na.z = A->nz;
    nb.x = B->nx; nb.y = B->ny; nb.z = B->nz;
    nd.x = C->nx; nd.y = C->ny; nd.z = C->nz;

    /* The normal and the shading point are in the mesh's own space -- the same space the light
     * rig is set in -- so a world-space (or object-space) rig lights correctly; the view only
     * projects. */
    e1.x = pb.x - pa.x; e1.y = pb.y - pa.y; e1.z = pb.z - pa.z;
    e2.x = pd.x - pa.x; e2.y = pd.y - pa.y; e2.z = pd.z - pa.z;
    n.x = e1.y * e2.z - e1.z * e2.y;
    n.y = e1.z * e2.x - e1.x * e2.z;
    n.z = e1.x * e2.y - e1.y * e2.x;
    {
        float len = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);
        if (len > 1e-9f) { n.x /= len; n.y /= len; n.z /= len; }
    }
    pc.x = (pa.x + pb.x + pd.x) / 3.0f;
    pc.y = (pa.y + pb.y + pd.y) / 3.0f;
    pc.z = (pa.z + pb.z + pd.z) / 3.0f;
    /* Two-sided only: face the eye, so an un-culled back face is lit too. One-sided keeps the
     * authored winding, which is what lets a surface the light does not reach go dark -- the
     * engine draws front faces only, and a front face's normal is its wound one. */
    if (g_two_sided && g_eye_valid) {
        float fd = n.x * (g_eye[0] - pc.x) + n.y * (g_eye[1] - pc.y)
                 + n.z * (g_eye[2] - pc.z);
        if (fd < 0) { n.x = -n.x; n.y = -n.y; n.z = -n.z; }
    } else if (g_two_sided && n.z < 0) {
        n.x = -n.x; n.y = -n.y; n.z = -n.z;
    }
    if (!smooth)
        shade(n, pc, tint, col);

    /* Gouraud: the game's per-vertex path -- light each corner once with its own authored normal
     * (one-sided) and interpolate the colour, never the normal. */
    float ca[3] = { 0, 0, 0 }, cb[3] = { 0, 0, 0 }, cc[3] = { 0, 0, 0 };
    if (smooth && g_gouraud) {
        uint8_t vc[3];
        v3 nv;
        /* the clip path hands back interpolated normals that are no longer unit length; the game
         * lights the authored vertex normal before clipping, so renormalise here */
        nv.x = na.x; nv.y = na.y; nv.z = na.z;
        { float l = sqrtf(nv.x * nv.x + nv.y * nv.y + nv.z * nv.z);
          if (l > 1e-9f) { nv.x /= l; nv.y /= l; nv.z /= l; } }
        shade(nv, pa, tint, vc);
        ca[0] = (float)vc[0]; ca[1] = (float)vc[1]; ca[2] = (float)vc[2];
        nv.x = nb.x; nv.y = nb.y; nv.z = nb.z;
        { float l = sqrtf(nv.x * nv.x + nv.y * nv.y + nv.z * nv.z);
          if (l > 1e-9f) { nv.x /= l; nv.y /= l; nv.z /= l; } }
        shade(nv, pb, tint, vc);
        cb[0] = (float)vc[0]; cb[1] = (float)vc[1]; cb[2] = (float)vc[2];
        nv.x = nd.x; nv.y = nd.y; nv.z = nd.z;
        { float l = sqrtf(nv.x * nv.x + nv.y * nv.y + nv.z * nv.z);
          if (l > 1e-9f) { nv.x /= l; nv.y /= l; nv.z /= l; } }
        shade(nv, pd, tint, vc);
        cc[0] = (float)vc[0]; cc[1] = (float)vc[1]; cc[2] = (float)vc[2];
    }

    det = (sbx - sax) * (sdy - say) - (sdx - sax) * (sby - say);
    if (fabsf(det) < 1e-6f)
        return;
    if (g_cull && g_eye_valid) {
        /* The authored facing: the geometric normal against the eye ray.  A mesh-space (or world
         * -space) eye is the same space `n` is in, so this is the engine's own test. */
        float cd = n.x * (g_eye[0] - pc.x) + n.y * (g_eye[1] - pc.y) + n.z * (g_eye[2] - pc.z);
        if (g_cull == 1 ? (cd <= 0.0f) : (cd >= 0.0f))
            return;
    }
    minx = sax < sbx ? sax : sbx; if (sdx < minx) minx = sdx;
    maxx = sax > sbx ? sax : sbx; if (sdx > maxx) maxx = sdx;
    miny = say < sby ? say : sby; if (sdy < miny) miny = sdy;
    maxy = say > sby ? say : sby; if (sdy > maxy) maxy = sdy;
    if (minx < 0) minx = 0;
    if (miny < 0) miny = 0;
    if (maxx > fb->w - 1) maxx = (float)(fb->w - 1);
    if (maxy > fb->h - 1) maxy = (float)(fb->h - 1);
    for (y = (int)miny; y <= (int)maxy; y++) {
        for (x = (int)minx; x <= (int)maxx; x++) {
            float px = (float)x + 0.5f, py = (float)y + 0.5f;
            float w0 = ((sbx - sax) * (py - say) - (px - sax) * (sby - say)) / det;
            float w1 = ((px - sax) * (sdy - say) - (sdx - sax) * (py - say)) / det;
            float w2 = 1.0f - w0 - w1;
            uint8_t r = col[0], g = col[1], bb = col[2];
            if (w0 < 0 || w1 < 0 || w2 < 0)
                continue;
            /* Perspective-correct interpolation.  The screen-space barycentrics (w2 -> A, w1 -> B,
             * w0 -> C) are linear in 1/w, so an attribute is sum(q_i * A_i) with q_i =
             * (w_i / z_i) / sum(w_j / z_j), and the depth is z = 1 / sum(w_j / z_j).  The old code
             * interpolated z linearly AND with the A/B weights swapped -- `w1 * saz + w2 * sbz`
             * instead of `w2 * saz + w1 * sbz` -- so a distant wall could win the depth test
             * against near geometry (the barrel/crate). */
            float invw = w2 / saz + w1 / sbz + w0 / sdz;
            float q2 = (w2 / saz) / invw;       /* perspective-correct weight for A */
            float q1 = (w1 / sbz) / invw;       /* ... B */
            float q0 = (w0 / sdz) / invw;       /* ... C */
            float z = 1.0f / invw;
            if (smooth) {
                if (g_gouraud) {
                    /* The GS's Gouraud shading interpolates the vertex colour AFFINELY in screen
                     * space (it interpolates S/T/Q affinely for the perspective-correct texture,
                     * but the colour has no Q), so the weights are the screen-space barycentrics
                     * (w2 -> A, w1 -> B, w0 -> C), not the perspective-correct q's. */
                    r = (uint8_t)(w2 * ca[0] + w1 * cb[0] + w0 * cc[0] + 0.5f);
                    g = (uint8_t)(w2 * ca[1] + w1 * cb[1] + w0 * cc[1] + 0.5f);
                    bb = (uint8_t)(w2 * ca[2] + w1 * cb[2] + w0 * cc[2] + 0.5f);
                } else {
                v3 ni, pi;
                float nl;
                ni.x = q2 * na.x + q1 * nb.x + q0 * nd.x;
                ni.y = q2 * na.y + q1 * nb.y + q0 * nd.y;
                ni.z = q2 * na.z + q1 * nb.z + q0 * nd.z;
                nl = sqrtf(ni.x * ni.x + ni.y * ni.y + ni.z * ni.z);
                if (nl > 1e-9f) {
                    ni.x /= nl; ni.y /= nl; ni.z /= nl;
                } else {
                    /* a mesh with no normal buffer carries zero normals in a merged buffer
                     * (only 195 of 549 stage meshes ship one): shade it with
                     * the face normal rather than black */
                    ni = n;
                }
                pi.x = q2 * pa.x + q1 * pb.x + q0 * pd.x;
                pi.y = q2 * pa.y + q1 * pb.y + q0 * pd.y;
                pi.z = q2 * pa.z + q1 * pb.z + q0 * pd.z;
                if (g_two_sided && g_eye_valid) {
                    float fd = ni.x * (g_eye[0] - pi.x) + ni.y * (g_eye[1] - pi.y)
                             + ni.z * (g_eye[2] - pi.z);
                    if (fd < 0) { ni.x = -ni.x; ni.y = -ni.y; ni.z = -ni.z; }
                }
                shade(ni, pi, tint, col);
                r = col[0]; g = col[1]; bb = col[2];
                }
            }
            if (tex) {
                float tu = q2 * ua + q1 * ub + q0 * ud;
                float tv = q2 * va + q1 * vb + q0 * vd;
                float fx = tu * tex->w - 0.5f;             /* texel centres at integer f */
                float fy = (1.0f - tv) * tex->h - 0.5f;    /* the pack stores grids bottom-up */
                int tr, tg, tb;
                if (!g_tex_filter) {
                    const uint8_t *t = texel(tex, (int)(tu * tex->w), (int)((1.0f - tv) * tex->h));
                    tr = t[0]; tg = t[1]; tb = t[2];
                } else {
                    int x0 = (int)floorf(fx), y0 = (int)floorf(fy);
                    float ax = fx - (float)x0, ay = fy - (float)y0;
                    const uint8_t *t00 = texel(tex, x0, y0), *t10 = texel(tex, x0 + 1, y0);
                    const uint8_t *t01 = texel(tex, x0, y0 + 1), *t11 = texel(tex, x0 + 1, y0 + 1);
                    float w00 = (1.0f - ax) * (1.0f - ay), w10 = ax * (1.0f - ay);
                    float w01 = (1.0f - ax) * ay, w11 = ax * ay;
                    tr = (int)(t00[0] * w00 + t10[0] * w10 + t01[0] * w01 + t11[0] * w11 + 0.5f);
                    tg = (int)(t00[1] * w00 + t10[1] * w10 + t01[1] * w01 + t11[1] * w11 + 0.5f);
                    tb = (int)(t00[2] * w00 + t10[2] * w10 + t01[2] * w01 + t11[2] * w11 + 0.5f);
                }
                /* modulate by the fragment colour `r,g,bb` -- the gouraud path sets those directly
                 * and never fills `col[]`, so reading `col[]` here used a stale colour from a
                 * previous triangle. */
                r = (uint8_t)((tr * r) / 255);
                g = (uint8_t)((tg * g) / 255);
                bb = (uint8_t)((tb * bb) / 255);
            }
            {
                /* Fog (the VU1 FOG family = the GS fog stage): the GS interpolates the per-vertex
                 * fog value affinely in screen space (like the vertex colour -- it has no Q), then
                 * lerps the fragment toward FOGCOL by it. `f` is 1 clear, 0 at full fog, so the
                 * blend is out = C*(F/255) + FOGCOL*(1 - F/255). */
                float f = w2 * sfa + w1 * sfb + w0 * sfc;
                if (g_fog.mode && f < 1.0f) {
                    float fr = g_fog.color[0] * 255.0f, fg = g_fog.color[1] * 255.0f;
                    float fb2 = g_fog.color[2] * 255.0f;
                    float rr = fr * (1.0f - f) + r * f;
                    float gg = fg * (1.0f - f) + g * f;
                    float b2 = fb2 * (1.0f - f) + bb * f;
                    r = (uint8_t)(rr < 0 ? 0 : (rr > 255 ? 255 : rr));
                    g = (uint8_t)(gg < 0 ? 0 : (gg > 255 ? 255 : gg));
                    bb = (uint8_t)(b2 < 0 ? 0 : (b2 > 255 ? 255 : b2));
                }
                plot(fb, x, y, z, r, g, bb);
            }
        }
    }
}

int dw4_render_mesh_n(dw4_fb *fb, const uint8_t *pos, const uint8_t *normal, const uint8_t *uv,
                      uint32_t nverts,
                        const uint32_t *tris, uint32_t ntris, float yaw, float pitch,
                        float tint[3], const dw4_tex *tex)
{
    camera c;
    v3 *view;
    float *sx, *sy, *sz;
    uint32_t i;

    (void)tex;
    if (!fb->rgba || !nverts || !tris)
        return -1;
    if(dw4_gpu_policy_cpu(DW4_CPU_MESH))return -1;
    view = (v3 *)malloc(nverts * sizeof(*view));
    sx = (float *)malloc(nverts * sizeof(*sx));
    sy = (float *)malloc(nverts * sizeof(*sy));
    sz = (float *)malloc(nverts * sizeof(*sz));
    if (!view || !sx || !sy || !sz) {
        free(view); free(sx); free(sy); free(sz);
        return -1;
    }
    fit_camera(pos, nverts, yaw, pitch, &c);
    if (g_use_view) set_eye_view(); else set_eye_fit(&c);
    for (i = 0; i < nverts; i++) {
        v3 p = { rdf(pos + 12 * i), rdf(pos + 12 * i + 4), rdf(pos + 12 * i + 8) };
        cam_view(&c, p, &view[i]);
        cam_project(&c, view[i], fb->w, fb->h, &sx[i], &sy[i], &sz[i]);
    }
    for (i = 0; i < ntris; i++) {
        uint32_t idx[3];
        rvert tri[3], poly[4];
        const dw4_tex *usetex = (tex && uv) ? tex : NULL;
        int k, np = 0, smooth = (normal != NULL);

        idx[0] = tris[3 * i];
        idx[1] = tris[3 * i + 1];
        idx[2] = tris[3 * i + 2];
        if (idx[0] >= nverts || idx[1] >= nverts || idx[2] >= nverts)
            continue;
        for (k = 0; k < 3; k++) {
            uint32_t vi = idx[k];
            rvert *r = &tri[k];
            r->vx = view[vi].x; r->vy = view[vi].y; r->vz = view[vi].z;
            r->sx = sx[vi]; r->sy = sy[vi]; r->sz = view[vi].z;
            r->p[0] = rdf(pos + 12 * vi);
            r->p[1] = rdf(pos + 12 * vi + 4);
            r->p[2] = rdf(pos + 12 * vi + 8);
            if (smooth) {
                r->nx = rdf(normal + 12 * vi);
                r->ny = rdf(normal + 12 * vi + 4);
                r->nz = rdf(normal + 12 * vi + 8);
            } else {
                r->nx = r->ny = r->nz = 0.0f;
            }
            if (usetex) {
                float uu = rdf(uv + 8 * vi), vv = rdf(uv + 8 * vi + 4);
                r->u = uu * g_uv_scale + g_uv_off[0];
                r->v = vv * g_uv_scale + g_uv_off[1];
            } else {
                r->u = r->v = 0.0f;
            }
            /* the per-vertex fog value (the VU1 FOG program's output): a pure
             * function of view-space depth, lerped per fragment toward FOGCOL. */
            r->fog = fog_factor(r->vz);
        }
        /* Clip to z >= DW4_NEAR_Z (Sutherland-Hodgman), then fan-triangulate. */
        for (k = 0; k < 3; k++) {
            const rvert *cur = &tri[k], *nxt = &tri[(k + 1) % 3];
            int cin = cur->vz > DW4_NEAR_Z, cnx = nxt->vz > DW4_NEAR_Z;
            if (cin)
                poly[np++] = *cur;
            if (cin != cnx) {
                float t = (DW4_NEAR_Z - cur->vz) / (nxt->vz - cur->vz);
                poly[np++] = rvert_lerp(cur, nxt, t, fb->w, fb->h);
            }
        }
        for (k = 1; k + 1 < np; k++)
            raster_tri(fb, &poly[0], &poly[k], &poly[k + 1], usetex, tint, smooth);
    }
    free(view); free(sx); free(sy); free(sz);
    return 0;
}

int dw4_render_mesh_tex(dw4_fb *fb, const uint8_t *pos, const uint8_t *uv, uint32_t nverts,
                        const uint32_t *tris, uint32_t ntris, float yaw, float pitch,
                        float tint[3], const dw4_tex *tex)
{
    return dw4_render_mesh_n(fb, pos, NULL, uv, nverts, tris, ntris, yaw, pitch, tint, tex);
}

int dw4_render_mesh(dw4_fb *fb, const uint8_t *pos, const uint8_t *uv, uint32_t nverts,
                    const uint32_t *tris, uint32_t ntris, float yaw, float pitch,
                    float tint[3], int width)
{
    (void)uv;
    (void)width;
    return dw4_render_mesh_n(fb, pos, NULL, NULL, nverts, tris, ntris, yaw, pitch, tint, NULL);
}

void dw4_render_wire(dw4_fb *fb, const uint8_t *pos, uint32_t nverts, const uint32_t *tris,
                     uint32_t ntris, float yaw, float pitch, int width, uint8_t r, uint8_t g,
                     uint8_t b)
{
    if(dw4_gpu_policy_cpu(DW4_CPU_MESH))return;
    (void)b;
    camera c;
    v3 *view;
    float *sx, *sy, *sz;
    uint32_t i;

    (void)width;
    view = (v3 *)malloc(nverts * sizeof(*view));
    sx = (float *)malloc(nverts * sizeof(*sx));
    sy = (float *)malloc(nverts * sizeof(*sy));
    sz = (float *)malloc(nverts * sizeof(*sz));
    if (!view || !sx || !sy || !sz) {
        free(view); free(sx); free(sy); free(sz);
        return;
    }
    fit_camera(pos, nverts, yaw, pitch, &c);
    if (g_use_view) set_eye_view(); else set_eye_fit(&c);
    for (i = 0; i < nverts; i++) {
        v3 p = { rdf(pos + 12 * i), rdf(pos + 12 * i + 4), rdf(pos + 12 * i + 8) };
        cam_view(&c, p, &view[i]);
        cam_project(&c, view[i], fb->w, fb->h, &sx[i], &sy[i], &sz[i]);
    }
    for (i = 0; i < ntris; i++) {
        uint32_t a = tris[3 * i], b = tris[3 * i + 1], d = tris[3 * i + 2];
        int steps, s;
        if (a >= nverts || b >= nverts || d >= nverts)
            continue;
        if (sz[a] < 0.0f || sz[b] < 0.0f || sz[d] < 0.0f)
            continue;              /* straddles the near plane: rejected, not drawn from bad maths */
        {
            uint32_t ends[4] = { a, b, b, d };
            int e;
            for (e = 0; e < 2; e++) {
                float x0 = sx[ends[2 * e]], y0 = sy[ends[2 * e]];
                float x1 = sx[ends[2 * e + 1]], y1 = sy[ends[2 * e + 1]];
                float z0 = sz[ends[2 * e]], z1 = sz[ends[2 * e + 1]];
                steps = (int)(fabsf(x1 - x0) > fabsf(y1 - y0) ? fabsf(x1 - x0) : fabsf(y1 - y0));
                if (steps < 1)
                    steps = 1;
                for (s = 0; s <= steps; s++) {
                    float t = (float)s / steps;
                    plot(fb, (int)(x0 + (x1 - x0) * t + 0.5f), (int)(y0 + (y1 - y0) * t + 0.5f),
                         z0 + (z1 - z0) * t - 0.001f, r, g, b);
                }
            }
        }
    }
    free(view); free(sx); free(sy); free(sz);
}

/* A readout on the frame. A 5x7 bitmap font covering only what a diagnostic readout needs (`0-9 .
 * : f p s m x space`); anything else is a blank. Each glyph row is 5 bits, leftmost pixel in bit
 * 4. This is not the game's font. */

static const char font_chars[] = "0123456789.:fpsmx";

static const uint8_t font_glyph[][7] = {
    { 0x0e, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0e },   /* 0 */
    { 0x04, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x0e },   /* 1 */
    { 0x0e, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1f },   /* 2 */
    { 0x1f, 0x02, 0x04, 0x02, 0x01, 0x11, 0x0e },   /* 3 */
    { 0x02, 0x06, 0x0a, 0x12, 0x1f, 0x02, 0x02 },   /* 4 */
    { 0x1f, 0x10, 0x1e, 0x01, 0x01, 0x11, 0x0e },   /* 5 */
    { 0x06, 0x08, 0x10, 0x1e, 0x11, 0x11, 0x0e },   /* 6 */
    { 0x1f, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08 },   /* 7 */
    { 0x0e, 0x11, 0x11, 0x0e, 0x11, 0x11, 0x0e },   /* 8 */
    { 0x0e, 0x11, 0x11, 0x0f, 0x01, 0x02, 0x0c },   /* 9 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c },   /* . */
    { 0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00 },   /* : */
    { 0x06, 0x09, 0x08, 0x1c, 0x08, 0x08, 0x08 },   /* f */
    { 0x00, 0x00, 0x1e, 0x11, 0x11, 0x1e, 0x10 },   /* p */
    { 0x00, 0x0f, 0x10, 0x0e, 0x01, 0x1e, 0x00 },   /* s */
    { 0x00, 0x00, 0x1a, 0x15, 0x15, 0x15, 0x15 },   /* m */
    { 0x00, 0x00, 0x11, 0x0a, 0x04, 0x0a, 0x11 }    /* x */
};

static const uint8_t *font_lookup(char c)
{
    const char *p;
    if (c >= 'A' && c <= 'Z')
        c = (char)(c - 'A' + 'a');
    p = strchr(font_chars, c);
    if (!p)
        return NULL;
    return font_glyph[p - font_chars];
}

static void text_block(dw4_fb *fb, int x, int y, int scale, uint8_t r, uint8_t g, uint8_t b)
{
    int px, py;
    for (py = 0; py < scale; py++) {
        int yy = y + py;
        uint8_t *row;
        if (yy < 0 || yy >= fb->h)
            continue;
        row = fb->rgba + (size_t)yy * fb->w * 4;
        for (px = 0; px < scale; px++) {
            int xx = x + px;
            if (xx < 0 || xx >= fb->w)
                continue;
            row[xx * 4 + 0] = r;
            row[xx * 4 + 1] = g;
            row[xx * 4 + 2] = b;
            row[xx * 4 + 3] = 255;
        }
    }
}

int dw4_fb_text_width(const char *s, int scale)
{
    int n = 0;
    if (!s)
        return 0;
    while (*s++)
        n++;
    return n ? (n * 6 - 1) * scale : 0;
}

void dw4_fb_text(dw4_fb *fb, int x, int y, const char *s, int scale, uint8_t r, uint8_t g, uint8_t b)
{
    if(dw4_gpu_policy_cpu(DW4_CPU_COMPOSITE))return;
    const char *p;
    if (!fb || !fb->rgba || scale < 1)
        return;
    for (p = s; *p; p++) {
        const uint8_t *glyph = font_lookup(*p);
        int gx = x;
        int ry, rx;
        if (glyph) {
            for (ry = 0; ry < 7; ry++)
                for (rx = 0; rx < 5; rx++)
                    if (glyph[ry] & (1 << (4 - rx)))
                        text_block(fb, gx + rx * scale + scale, y + ry * scale + scale, scale, 0, 0, 0);
            for (ry = 0; ry < 7; ry++)
                for (rx = 0; rx < 5; rx++)
                    if (glyph[ry] & (1 << (4 - rx)))
                        text_block(fb, gx + rx * scale, y + ry * scale, scale, r, g, b);
        }
        x += 6 * scale;
    }
}

void dw4_fb_plate(dw4_fb *fb, int x, int y, int w, int h, int darken_percent)
{
    if(dw4_gpu_policy_cpu(DW4_CPU_COMPOSITE))return;
    int px, py;
    if (!fb || !fb->rgba)
        return;
    if (darken_percent < 0)
        darken_percent = 0;
    if (darken_percent > 100)
        darken_percent = 100;
    for (py = 0; py < h; py++) {
        int yy = y + py;
        uint8_t *row;
        if (yy < 0 || yy >= fb->h)
            continue;
        row = fb->rgba + (size_t)yy * fb->w * 4;
        for (px = 0; px < w; px++) {
            int xx = x + px;
            int k;
            if (xx < 0 || xx >= fb->w)
                continue;
            for (k = 0; k < 3; k++)
                row[xx * 4 + k] = (uint8_t)(row[xx * 4 + k] * (100 - darken_percent) / 100);
        }
    }
}

/* The `--fps` readout, shared by every windowed present loop (the stage/boot renderer, the movie
 * player and `dw4asset render`) so the boot's FMV and title show the frame rate too.  The font is
 * the diagnostic 5x7 one above, not the game's text. */
void dw4_render_fps(dw4_fb *fb, double fps)
{
    char osd[64];
    int scale = 2, pad = 4, tw, th;

    if (!fb || !fb->rgba)
        return;
    snprintf(osd, sizeof(osd), "%.0f fps", fps);
    tw = dw4_fb_text_width(osd, scale);
    th = 7 * scale;
    dw4_fb_plate(fb, 8 - pad, 8 - pad, tw + 2 * pad, th + 2 * pad, 45);
    dw4_fb_text(fb, 8, 8, osd, scale, 255, 255, 255);
}

double dw4_fps_overlay=-1;
int dw4_fps_overlay_drawn;
static int render_fps_gpu_ops(dw4_gl_layer *gpu,dw4_fb *fb,double fps);
int dw4_render_fps_gpu(dw4_gl_layer *gpu,dw4_fb *fb,double fps)
{
    /* plate + glyphs as one resident run: one upload and one readback instead of two of each */
    int deferred=gpu && fb && !dw4_gl_layer_defer(gpu,fb,1);
    int rc=render_fps_gpu_ops(gpu,fb,fps);
    if(deferred && dw4_gl_layer_defer(gpu,fb,0) && !rc)rc=-1;
    return rc;
}
static int render_fps_gpu_ops(dw4_gl_layer *gpu,dw4_fb *fb,double fps)
{
    enum {GLYPHS=sizeof font_glyph/sizeof *font_glyph,AW=GLYPHS*5};
    static uint8_t atlas[AW*7*4];static int ready;
    if(!gpu || !fb || !fb->rgba)return -1;
    if(!ready){
        for(unsigned glyph=0;glyph<GLYPHS;glyph++)for(unsigned y=0;y<7;y++)for(unsigned x=0;x<5;x++){
            uint8_t *p=atlas+4*(y*AW+glyph*5+x);p[0]=p[1]=p[2]=255;
            p[3]=(font_glyph[glyph][y]&(1u<<(4-x)))?128:0;
        }ready=1; /* Immutable diagnostic font asset, not framebuffer rasterization. */
    }
    char osd[64];snprintf(osd,sizeof osd,"%.0f fps",fps);
    if(dw4_gl_layer_plate(gpu,fb,4,4,dw4_fb_text_width(osd,2)+8,22,45))return -1;
    dw4_tex tex={atlas,AW,7};dw4_ui_draw draws[64*4];unsigned count=0;int pen=8;
    for(const char *s=osd;*s;s++,pen+=12){
        char c=*s;if(c>='A' && c<='Z')c=c-'A'+'a';const char *p=strchr(font_chars,c);if(!p)continue;
        unsigned glyph=(unsigned)(p-font_chars);float u0=glyph*5.f/AW,u1=(glyph+1)*5.f/AW;
        for(unsigned pass=0;pass<2;pass++){
            float x=pen+(pass?0:2),y=8+(pass?0:2);
            float vertices[4][5]={{x,y,u0,0,1},{x+10,y,u1,0,1},{x+10,y+14,u1,1,1},{x,y+14,u0,1,1}};
            static const unsigned index[2][3]={{0,1,2},{0,2,3}};
            for(unsigned t=0;t<2;t++){
                dw4_ui_draw *d=draws+count++;memset(d,0,sizeof *d);d->tex=&tex;d->stq=d->blend=1;d->filter=1;
                for(unsigned v=0;v<3;v++){
                    memcpy(d->v[v],vertices[index[t][v]],sizeof vertices[0]);
                    d->rgba[v][0]=d->rgba[v][1]=d->rgba[v][2]=pass?128:0;d->rgba[v][3]=128;
                }
            }
        }
    }
    int wrap=dw4_render_tex_wrap;dw4_render_tex_wrap=0;
    int rc=dw4_gl_layer_ui(gpu,fb,draws,(int)count);dw4_render_tex_wrap=wrap;return rc;
}
