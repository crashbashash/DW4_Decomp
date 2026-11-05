/* dw4/gl_render.c — the EGL/GLES offscreen GPU backend; see include/dw4/gl_render.h. */
#define _GNU_SOURCE
#include "dw4/gl_render.h"
#include "dw4/gpupolicy.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DW4_ENABLE_GL
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include "glcontext.h"

struct dw4_gl {
    EGLDisplay dpy;
    EGLContext ctx;
    GLuint fbo, color, depth;
    GLuint prog,vao;
    GLuint vbo_pos, vbo_nrm, vbo_uv, ibo;
    GLuint tex;
    int w, h;
    uint8_t *pixels;
    uint8_t clear[4];
    dw4_glctx_saved saved;
    char renderer[128];
    GLint uRow0, uRow1, uRow2, uSx, uSy, uZn, uZb;
    GLint uNLight, uAmbient, uTint, uEye, uTwoSided;
    GLint uLType, uLPos, uLDir, uLDiff, uLAmb, uLSpec;
    GLint uLAttC, uLAttL, uLAttQ, uLRange, uLShin, uLCosCut, uLCosFall;
    GLint uHasTex, uTex,uGouraud;
    GLint uFogMode, uFogColor, uFogStart, uFogEnd, uFogDensity;
    int frame_open;              /* between dw4_gl_frame_begin and _end: the FBO is bound and set */
};

int dw4_gl_built(void) { return 1; }

#define LIGHT_DECL \
"uniform int uNLight; uniform int uTwoSided; uniform vec3 uAmbient; uniform vec3 uTint; uniform vec3 uEye;\n" \
"uniform int   uLType[8];   uniform vec3 uLPos[8];  uniform vec3 uLDir[8];\n" \
"uniform vec3  uLDiff[8];   uniform vec3 uLAmb[8];  uniform vec3 uLSpec[8];\n" \
"uniform float uLAttC[8];   uniform float uLAttL[8]; uniform float uLAttQ[8];\n" \
"uniform float uLRange[8];  uniform float uLShin[8]; uniform float uLCosCut[8];\n" \
"uniform float uLCosFall[8];\n"

#define LIGHT_FN \
"vec3 light_color(vec3 P,vec3 N){\n" \
"  vec3 c = uAmbient;\n" \
"  for (int i = 0; i < 8; i++) {\n" \
"    if (i >= uNLight) break;\n" \
"    vec3 L; float att = 1.0;\n" \
"    if (uLType[i] == 0) { L = -uLDir[i]; }\n" \
"    else {\n" \
"      vec3 dv = uLPos[i] - P; float d = length(dv);\n" \
"      L = d > 1e-6 ? dv/d : vec3(0.0,0.0,1.0);\n" \
"      att = 1.0/(uLAttC[i] + uLAttL[i]*d + uLAttQ[i]*d*d);\n" \
"      if (uLRange[i] > 0.0 && d >= uLRange[i]) att = 0.0;\n" \
"      if (uLType[i] == 2) {\n" \
"        float cd = -dot(uLDir[i], L);\n" \
"        if (cd < uLCosCut[i]) att = 0.0;\n" \
"        else if (cd < uLCosFall[i] && uLCosFall[i] > uLCosCut[i])\n" \
"          att *= (cd - uLCosCut[i])/(uLCosFall[i] - uLCosCut[i]);\n" \
"      }\n" \
"    }\n" \
"    c += att*(uLAmb[i] + (uTwoSided != 0 ? abs(dot(N,L)) : max(dot(N,L), 0.0))*uLDiff[i]);\n" \
"    if (dot(uLSpec[i],uLSpec[i]) > 0.0 && uLShin[i] > 0.0) {\n" \
"      vec3 V = normalize(uEye - P); vec3 H = normalize(L + V);\n" \
"      c += att*pow((uTwoSided != 0 ? abs(dot(N,H)) : max(dot(N,H), 0.0)), uLShin[i])*uLSpec[i];\n" \
"    }\n" \
"  }\n" \
"return clamp(c*uTint,0.0,1.0); }\n"

static const char *VS =
    "#version 300 es\n"
    "precision highp float; precision highp int;\n"
    "in vec3 aPos; in vec3 aNrm; in vec2 aUV;\n"
    "uniform vec4 uRow0, uRow1, uRow2;\n"
    "uniform float uSx, uSy, uZn, uZb;\n"
    LIGHT_DECL
    LIGHT_FN
    "uniform int uGouraud; out vec3 vGouraud; out float vClipW;\n"
    "out vec3 vPos; out vec3 vNrm; out vec2 vUV; out float vFogZ;\n"
    "void main() {\n"
    "  vec4 p = vec4(aPos, 1.0);\n"
    "  float vx = dot(p, uRow0);\n"
    "  float vy = dot(p, uRow1);\n"
    "  float vz = dot(p, uRow2);\n"
    "  gl_Position = vec4(vx*uSx, vy*uSy, uZn*vz + uZb, vz);\n"
    "  vec3 N=dot(aNrm,aNrm)>1e-12?normalize(aNrm):vec3(0);\n"
    "  vGouraud=floor(light_color(aPos,N)*255.0)*vz;vClipW=vz;\n"
    "  vPos = aPos; vNrm = aNrm; vUV = aUV; vFogZ = vz;\n"
    "}\n";

/* The row-vector view: v' = (dot(p,r0), dot(p,r1), dot(p,r2)).  `uRowN` carries (M[0],M[4],M[8],M[12])
 * so the shader's dot with vec4(p,1.0) is the affine transform. */
static const char *FS =
    "#version 300 es\n"
    "precision highp float; precision highp int;\n"
    "in vec3 vPos; in vec3 vNrm; in vec2 vUV; in float vFogZ;\n"
    "out vec4 fragColor;\n"
    "uniform int uHasTex; uniform sampler2D uTex;\n"
    "uniform int uFogMode; uniform vec3 uFogColor;\n"
    "uniform float uFogStart, uFogEnd, uFogDensity;\n"
    LIGHT_DECL
    LIGHT_FN
    "uniform int uGouraud; in vec3 vGouraud; in float vClipW;\n"
    "void main() {\n"
    "  vec3 P = vPos;\n"
    "  vec3 N = normalize(vNrm);\n"
    "  if (dot(vNrm, vNrm) < 1e-12) N = normalize(cross(dFdx(P), dFdy(P)));\n"
    "  if (uTwoSided != 0 && !gl_FrontFacing) N = -N;  /* two-sided, as the software path */\n"
    "  vec3 base = uGouraud!=0 ? floor(vGouraud/vClipW+0.5)/255.0 : light_color(P,N);\n"
    "  /* the pack stores its grids bottom-up, so `v` is flipped, as the software path does */\n"
    "  if (uHasTex != 0)\n"
    "    base *= texture(uTex, vec2(vUV.x, 1.0 - vUV.y)).rgb;\n"
    "  vec3 outc = clamp(base, 0.0, 1.0);\n"
    "  /* the VU1 FOG family: linear / exp / exp2, blended by view-space depth */\n"
    "  if (uFogMode == 1) {\n"
    "    float f = clamp((uFogEnd - vFogZ) / max(uFogEnd - uFogStart, 1e-6), 0.0, 1.0);\n"
    "    outc = mix(uFogColor, outc, f);\n"
    "  } else if (uFogMode == 2) {\n"
    "    outc = mix(uFogColor, outc, clamp(exp(-uFogDensity * vFogZ), 0.0, 1.0));\n"
    "  } else if (uFogMode == 3) {\n"
    "    float d = uFogDensity * vFogZ;\n"
    "    outc = mix(uFogColor, outc, clamp(exp(-(d * d)), 0.0, 1.0));\n"
    "  }\n"
    "  fragColor = vec4(outc, 1.0);\n"
    "}\n";

static GLuint shader(GLenum type, const char *src)
{
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, NULL);
    glCompileShader(s);
    {
        GLint ok = 0;
        glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
        if (!ok) {
            char log[1024];
            glGetShaderInfoLog(s, sizeof(log), NULL, log);
            fprintf(stderr, "gl: shader: %s\n", log);
            glDeleteShader(s);
            return 0;
        }
    }
    return s;
}

dw4_gl *dw4_gl_open(int w, int h)
{
    dw4_gl *g;
    EGLint n = 0;
    EGLConfig cfg;
    EGLint cfg_att[] = {
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
        EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 16, EGL_NONE };
    EGLint ctx_att[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    GLuint vs=0, fs=0;
    GLint ok = 0;
    const char *r;
    dw4_glctx_saved saved=dw4_glctx_save();

    if (w <= 0 || h <= 0)
        return NULL;
    /* surfaceless by default, so this runs with no display (X/Wayland) at all */
    if (!getenv("EGL_PLATFORM"))
        setenv("EGL_PLATFORM", "surfaceless", 1);
    g = (dw4_gl *)calloc(1, sizeof(*g));
    if (!g)
        return NULL;
    g->w = w;
    g->h = h;
    g->clear[0]=18;g->clear[1]=22;g->clear[2]=30;g->clear[3]=255;
    g->pixels=malloc((size_t)w*h*4);if(!g->pixels)goto fail;
    g->dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (g->dpy == EGL_NO_DISPLAY || !eglInitialize(g->dpy, NULL, NULL))
        goto fail;
    eglBindAPI(EGL_OPENGL_ES_API);
    if (!eglChooseConfig(g->dpy, cfg_att, &cfg, 1, &n) || n < 1)
        goto fail;
    g->ctx = eglCreateContext(g->dpy, cfg, EGL_NO_CONTEXT, ctx_att);
    if (g->ctx == EGL_NO_CONTEXT)
        goto fail;
    if (dw4_glctx_activate(g->dpy,g->ctx,saved))
        goto fail;

    r = (const char *)glGetString(GL_RENDERER);
    snprintf(g->renderer, sizeof(g->renderer), "%s", r ? r : "?");
    if(!dw4_gpu_policy_accept(g->renderer))goto fail;

    /* the offscreen target: a colour texture, a depth renderbuffer, one FBO */
    glGenTextures(1, &g->color);
    glBindTexture(GL_TEXTURE_2D, g->color);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenRenderbuffers(1, &g->depth);
    glBindRenderbuffer(GL_RENDERBUFFER, g->depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h);
    glGenFramebuffers(1, &g->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, g->fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g->color, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, g->depth);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        goto fail;

    vs = shader(GL_VERTEX_SHADER, VS);
    fs = shader(GL_FRAGMENT_SHADER, FS);
    if (!vs || !fs)
        goto fail;
    g->prog = glCreateProgram();
    glAttachShader(g->prog, vs);
    glAttachShader(g->prog, fs);
    glBindAttribLocation(g->prog, 0, "aPos");
    glBindAttribLocation(g->prog, 1, "aNrm");
    glBindAttribLocation(g->prog, 2, "aUV");
    glLinkProgram(g->prog);
    glDeleteShader(vs);
    glDeleteShader(fs);
    vs=fs=0;
    glGetProgramiv(g->prog, GL_LINK_STATUS, &ok);
    if (!ok){
        char log[2048];glGetProgramInfoLog(g->prog,sizeof log,NULL,log);fprintf(stderr,"gl: program: %s\n",log);
        goto fail;
    }

    g->uRow0 = glGetUniformLocation(g->prog, "uRow0");
    g->uRow1 = glGetUniformLocation(g->prog, "uRow1");
    g->uRow2 = glGetUniformLocation(g->prog, "uRow2");
    g->uSx = glGetUniformLocation(g->prog, "uSx");
    g->uSy = glGetUniformLocation(g->prog, "uSy");
    g->uZn = glGetUniformLocation(g->prog, "uZn");
    g->uZb = glGetUniformLocation(g->prog, "uZb");
    g->uNLight = glGetUniformLocation(g->prog, "uNLight");
    g->uTwoSided = glGetUniformLocation(g->prog, "uTwoSided");
    g->uAmbient = glGetUniformLocation(g->prog, "uAmbient");
    g->uTint = glGetUniformLocation(g->prog, "uTint");
    g->uEye = glGetUniformLocation(g->prog, "uEye");
    g->uLType = glGetUniformLocation(g->prog, "uLType");
    g->uLPos = glGetUniformLocation(g->prog, "uLPos");
    g->uLDir = glGetUniformLocation(g->prog, "uLDir");
    g->uLDiff = glGetUniformLocation(g->prog, "uLDiff");
    g->uLAmb = glGetUniformLocation(g->prog, "uLAmb");
    g->uLSpec = glGetUniformLocation(g->prog, "uLSpec");
    g->uLAttC = glGetUniformLocation(g->prog, "uLAttC");
    g->uLAttL = glGetUniformLocation(g->prog, "uLAttL");
    g->uLAttQ = glGetUniformLocation(g->prog, "uLAttQ");
    g->uLRange = glGetUniformLocation(g->prog, "uLRange");
    g->uLShin = glGetUniformLocation(g->prog, "uLShin");
    g->uLCosCut = glGetUniformLocation(g->prog, "uLCosCut");
    g->uLCosFall = glGetUniformLocation(g->prog, "uLCosFall");
    g->uHasTex = glGetUniformLocation(g->prog, "uHasTex");
    g->uTex = glGetUniformLocation(g->prog, "uTex");
    g->uGouraud=glGetUniformLocation(g->prog,"uGouraud");
    g->uFogMode = glGetUniformLocation(g->prog, "uFogMode");
    g->uFogColor = glGetUniformLocation(g->prog, "uFogColor");
    g->uFogStart = glGetUniformLocation(g->prog, "uFogStart");
    g->uFogEnd = glGetUniformLocation(g->prog, "uFogEnd");
    g->uFogDensity = glGetUniformLocation(g->prog, "uFogDensity");

    glGenBuffers(1, &g->vbo_pos);
    glGenBuffers(1, &g->vbo_nrm);
    glGenBuffers(1, &g->vbo_uv);
    glGenBuffers(1, &g->ibo);
    glGenVertexArrays(1,&g->vao);glBindVertexArray(g->vao);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDisable(GL_CULL_FACE);              /* the model is two-sided, as the software path */
    if(glGetError()!=GL_NO_ERROR || dw4_glctx_restore(g->dpy,saved))goto fail;
    return g;

fail:
    dw4_gpu_policy_fail("GLES mesh initialization");
    if(vs)glDeleteShader(vs);
    if(fs)glDeleteShader(fs);
    dw4_glctx_restore(g->dpy,saved);
    dw4_gl_close(g);
    return NULL;
}

void dw4_gl_close(dw4_gl *g)
{
    if (!g)
        return;
    if(g->frame_open)dw4_gl_frame_abort(g);
    dw4_glctx_saved saved=dw4_glctx_save();
    if(g->ctx!=EGL_NO_CONTEXT){
        if(!dw4_glctx_activate(g->dpy,g->ctx,saved)){
            if (g->prog) glDeleteProgram(g->prog);
            if (g->vbo_pos) glDeleteBuffers(1, &g->vbo_pos);
            if (g->vbo_nrm) glDeleteBuffers(1, &g->vbo_nrm);
            if (g->vbo_uv) glDeleteBuffers(1, &g->vbo_uv);
            if (g->ibo) glDeleteBuffers(1, &g->ibo);
            if (g->tex) glDeleteTextures(1, &g->tex);
            if (g->fbo) glDeleteFramebuffers(1, &g->fbo);
            if (g->color) glDeleteTextures(1, &g->color);
            if (g->depth) glDeleteRenderbuffers(1, &g->depth);
            glDeleteVertexArrays(1,&g->vao);
        }
        if(saved.context==g->ctx)saved=(dw4_glctx_saved){.display=EGL_NO_DISPLAY,.context=EGL_NO_CONTEXT,
            .draw=EGL_NO_SURFACE,.read=EGL_NO_SURFACE,.api=EGL_OPENGL_ES_API};
        dw4_glctx_restore(g->dpy,saved);eglDestroyContext(g->dpy,g->ctx);
    }
    /* The display is shared with layer and peer mesh contexts. */
    free(g->pixels);
    free(g);
}

const char *dw4_gl_info(dw4_gl *g) { return g ? g->renderer : ""; }
void dw4_gl_clear_color(dw4_gl *g,uint8_t r,uint8_t green,uint8_t b,uint8_t a)
{if(g){g->clear[0]=r;g->clear[1]=green;g->clear[2]=b;g->clear[3]=a;}}
int dw4_gl_frame_abort(dw4_gl *g)
{if(!g || !g->frame_open)return 0;g->frame_open=0;return dw4_glctx_restore(g->dpy,g->saved);}

static void light_uniforms(dw4_gl *g, const dw4_light *L, int n)
{
    int type[8] = {0}, i;
    float pos[24] = {0}, dir[24] = {0}, diff[24] = {0}, amb[24] = {0}, spec[24] = {0};
    float attc[8] = {0}, attl[8] = {0}, attq[8] = {0}, range[8] = {0}, shin[8] = {0};
    float cut[8] = {0}, fall[8] = {0};

    if (n > 8) n = 8;
    for (i = 0; i < n; i++) {
        type[i] = (L[i].type == DW4_LIGHT_DIRECTIONAL) ? 0
                : (L[i].type == DW4_LIGHT_POSITIONAL) ? 1 : 2;
        memcpy(pos + 3 * i, L[i].pos, 3 * sizeof(float));
        memcpy(dir + 3 * i, L[i].dir, 3 * sizeof(float));
        memcpy(diff + 3 * i, L[i].diffuse, 3 * sizeof(float));
        memcpy(amb + 3 * i, L[i].ambient, 3 * sizeof(float));
        if(L[i].specular_on && L[i].shininess>0)memcpy(spec + 3 * i, L[i].specular, 3 * sizeof(float));
        attc[i] = L[i].att_const ? L[i].att_const : 1.0f;
        attl[i] = L[i].att_linear;
        attq[i] = L[i].att_quad;
        range[i] = L[i].range;
        shin[i] = L[i].shininess > 0.0f ? L[i].shininess : 16.0f;
        cut[i] = L[i].spot_cos_cutoff;
        fall[i] = L[i].spot_cos_falloff;
    }
    glUniform1iv(g->uLType, 8, type);
    glUniform3fv(g->uLPos, 8, pos);
    glUniform3fv(g->uLDir, 8, dir);
    glUniform3fv(g->uLDiff, 8, diff);
    glUniform3fv(g->uLAmb, 8, amb);
    glUniform3fv(g->uLSpec, 8, spec);
    glUniform1fv(g->uLAttC, 8, attc);
    glUniform1fv(g->uLAttL, 8, attl);
    glUniform1fv(g->uLAttQ, 8, attq);
    glUniform1fv(g->uLRange, 8, range);
    glUniform1fv(g->uLShin, 8, shin);
    glUniform1fv(g->uLCosCut, 8, cut);
    glUniform1fv(g->uLCosFall, 8, fall);
}

/* Bind a decoded texture (RGBA8888, top row first) and tell the shader to sample it.  The pack's
 * grid is bottom-up, which the shader flips; with no texture the shader uses the shaded tint. */
static void bind_texture(dw4_gl *g, const dw4_tex *tex)
{
    if (!tex || !tex->rgba || tex->w <= 0 || tex->h <= 0) {
        glUniform1i(g->uHasTex, 0);
        return;
    }
    if (!g->tex)
        glGenTextures(1, &g->tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g->tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, dw4_render_tex_filter() ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, dw4_render_tex_filter() ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex->w, tex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 tex->rgba);
    glUniform1i(g->uTex, 0);
    glUniform1i(g->uHasTex, 1);
}

/* Clear the target and set the frame uniforms (view, projection, rig).  One `frame_begin`, any
 * number of `frame_mesh` draws, one `frame_end` -- so each mesh can carry its own tint/texture. */
int dw4_gl_frame_begin(dw4_gl *g, const float view[16], float fov, float aspect,
                       const float ambient[3], const dw4_light *lights, int nlights)
{
    float r0[4], r1[4], r2[4], f, sx, sy, zn, zb, eye[3];
    const float near = 0.05f, far = 1.0e6f;

    if (!g || !view || !ambient || g->frame_open || nlights<0 || (nlights && !lights) || !isfinite(fov) || fov<=0 || fov>=3.141593f || !isfinite(aspect) || aspect<=0)
        return -1;
    g->saved=dw4_glctx_save();
    if(dw4_glctx_activate(g->dpy,g->ctx,g->saved)){dw4_glctx_restore(g->dpy,g->saved);return -1;}
    /* Unlit: match the reference tint with ambient one and no light terms. */
    if (dw4_render_unlit()) {
        static const float white[3] = { 1.0f, 1.0f, 1.0f };
        ambient = white;
        lights = NULL;
        nlights = 0;
    }
    /* row-vector view columns, as render.c's cam_view reads them:
     * out.x = p.x*M[0] + p.y*M[4] + p.z*M[8] + M[12], so the shader dot's vector is that column. */
    r0[0] = view[0];  r0[1] = view[4];  r0[2] = view[8];   r0[3] = view[12];
    r1[0] = view[1];  r1[1] = view[5];  r1[2] = view[9];   r1[3] = view[13];
    r2[0] = view[2];  r2[1] = view[6];  r2[2] = view[10];  r2[3] = view[14];
    eye[0] = -(view[0] * view[12] + view[4] * view[13] + view[8] * view[14]);
    eye[1] = -(view[1] * view[12] + view[5] * view[13] + view[9] * view[14]);
    eye[2] = -(view[2] * view[12] + view[6] * view[13] + view[10] * view[14]);
    f = (float)g->h / (2.0f * tanf(fov * 0.5f));
    sx = f * aspect / ((float)g->w * 0.5f);
    /* positive: GL NDC is y-up and the readback below flips to the image's y-down convention, so
     * the software path's `sy = -(y/z)*f + h/2` is this sign once the flip is applied */
    sy = f / ((float)g->h * 0.5f);
    zn = (far + near) / (far - near);
    zb = -2.0f * far * near / (far - near);

    glViewport(0, 0, g->w, g->h);
    glBindFramebuffer(GL_FRAMEBUFFER, g->fbo);
    glDisable(GL_BLEND);glDisable(GL_DITHER);glDisable(GL_SCISSOR_TEST);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);glDepthMask(GL_TRUE);glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);glClearDepthf(1);
    glClearColor(g->clear[0]/255.f,g->clear[1]/255.f,g->clear[2]/255.f,g->clear[3]/255.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(g->prog);

    glUniform4fv(g->uRow0, 1, r0);
    glUniform4fv(g->uRow1, 1, r1);
    glUniform4fv(g->uRow2, 1, r2);
    glUniform1f(g->uSx, sx);
    glUniform1f(g->uSy, sy);
    glUniform1f(g->uZn, zn);
    glUniform1f(g->uZb, zb);
    glUniform1i(g->uNLight, nlights > 8 ? 8 : nlights);
    glUniform1i(g->uTwoSided, dw4_render_two_sided());
    glUniform3fv(g->uAmbient, 1, ambient);
    glUniform3fv(g->uEye, 1, eye);
    light_uniforms(g, lights, nlights);
    glUniform1i(g->uHasTex, 0);
    {
        static const float black[3] = { 0.0f, 0.0f, 0.0f };
        const dw4_fog *fog = dw4_render_get_fog();
        glUniform1i(g->uFogMode, fog ? fog->mode : 0);
        glUniform3fv(g->uFogColor, 1, fog ? fog->color : black);
        glUniform1f(g->uFogStart, fog ? fog->start : 0.0f);
        glUniform1f(g->uFogEnd, fog ? fog->end : 0.0f);
        glUniform1f(g->uFogDensity, fog ? fog->density : 0.0f);
    }
    g->frame_open = 1;
    /* Back-face culling, mirroring the software rasteriser and the game's VU1 CULLBACK.  The GL
     * winding is fixed (CCW front) so only `mode == 1` is expressible here. */
    if (dw4_render_cull() == 1) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    } else if (dw4_render_cull() == 2) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CCW);
    } else {
        glDisable(GL_CULL_FACE);
    }
    if(glGetError()!=GL_NO_ERROR){dw4_gl_frame_abort(g);return -1;}
    return 0;
}

int dw4_gl_frame_mesh(dw4_gl *g, const float *pos, const float *nrm, const float *uv,
                      const uint32_t *tris, uint32_t nv, uint32_t nt,
                      const float tint[3], const dw4_tex *tex)
{
    if (!g || !g->frame_open || !pos || !tris || !tint || nv == 0 || nt == 0)
        return -1;
    if(eglGetCurrentContext()!=g->ctx && dw4_glctx_activate(g->dpy,g->ctx,dw4_glctx_save()))return -1;
    for(size_t i=0;i<(size_t)nt*3;i++)if(tris[i]>=nv)return -1;
    glBindVertexArray(g->vao);glUseProgram(g->prog);
    glUniform3fv(g->uTint, 1, tint);
    glUniform1i(g->uGouraud,nrm && dw4_render_gouraud());
    bind_texture(g, tex);

    glBindBuffer(GL_ARRAY_BUFFER, g->vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei)(nv * 3 * sizeof(float)), pos, GL_STREAM_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    if (nrm) {
        glBindBuffer(GL_ARRAY_BUFFER, g->vbo_nrm);
        glBufferData(GL_ARRAY_BUFFER, (GLsizei)(nv * 3 * sizeof(float)), nrm, GL_STREAM_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    } else {
        /* no normal buffer: the shader's dFdx/dFdy fallback derives the geometric normal */
        glDisableVertexAttribArray(1);
        glVertexAttrib3f(1, 0.0f, 0.0f, 0.0f);
    }
    if (uv) {
        glBindBuffer(GL_ARRAY_BUFFER, g->vbo_uv);
        glBufferData(GL_ARRAY_BUFFER, (GLsizei)(nv * 2 * sizeof(float)), uv, GL_STREAM_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    } else {
        glDisableVertexAttribArray(2);
        glVertexAttrib2f(2, 0.0f, 0.0f);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei)(nt * 3 * sizeof(uint32_t)), tris,
                 GL_STREAM_DRAW);
    glDrawElements(GL_TRIANGLES, (GLsizei)(nt * 3), GL_UNSIGNED_INT, 0);
    return glGetError()==GL_NO_ERROR?0:-1;
}

/* Read the FBO back into `fb` and flip to the image's top-left convention. */
int dw4_gl_frame_end(dw4_gl *g, dw4_fb *fb)
{
    uint32_t y;

    if(!g || !g->frame_open)return -1;
    if(!fb || !fb->rgba || fb->w!=g->w || fb->h!=g->h){dw4_gl_frame_abort(g);return -1;}
    if(eglGetCurrentContext()!=g->ctx && dw4_glctx_activate(g->dpy,g->ctx,dw4_glctx_save())){dw4_gl_frame_abort(g);return -1;}
    glBindFramebuffer(GL_FRAMEBUFFER,g->fbo);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, g->w, g->h, GL_RGBA, GL_UNSIGNED_BYTE, g->pixels);
    int failed=glGetError()!=GL_NO_ERROR;
    if(dw4_gl_frame_abort(g))failed=1;
    if(failed)return -1;
    /* GL's origin is bottom-left; the framebuffer/PNG convention is top-left */
    for (y = 0; y < (uint32_t)g->h; y++)
        memcpy(fb->rgba + (size_t)y * g->w * 4,
               g->pixels + (size_t)(g->h - 1 - y) * g->w * 4, (size_t)g->w * 4);
    if(!dw4_gpu_policy_required() && fb->z)for (y = 0; y < (size_t)g->w * g->h; y++)
        fb->z[y] = 0.0f;                  /* the GL depth stays in the FBO; the software z is unused */
    return 0;
}

int dw4_gl_render(dw4_gl *g, dw4_fb *fb,
                  const float *pos, const float *nrm, const float *uv,
                  const uint32_t *tris, uint32_t nv, uint32_t nt,
                  const float view[16], float fov, float aspect,
                  const float ambient[3], const dw4_light *lights, int nlights,
                  const float tint[3], const dw4_tex *tex)
{
    if (!fb || !fb->rgba || !fb->z)
        return -1;
    if (dw4_gl_frame_begin(g, view, fov, aspect, ambient, lights, nlights) != 0)
        return -1;
    if (dw4_gl_frame_mesh(g, pos, nrm, uv, tris, nv, nt, tint, tex) != 0)
        {dw4_gl_frame_abort(g);return -1;}
    return dw4_gl_frame_end(g, fb);
}

#else /* !DW4_ENABLE_GL */

int dw4_gl_built(void) { return 0; }
dw4_gl *dw4_gl_open(int w, int h) { (void)w; (void)h; dw4_gpu_policy_fail("GLES mesh backend not compiled");return NULL; }
void dw4_gl_close(dw4_gl *g) { (void)g; }
const char *dw4_gl_info(dw4_gl *g) { (void)g; return ""; }
void dw4_gl_clear_color(dw4_gl *g,uint8_t r,uint8_t green,uint8_t b,uint8_t a)
{(void)g;(void)r;(void)green;(void)b;(void)a;}
int dw4_gl_frame_abort(dw4_gl *g){(void)g;return 0;}
int dw4_gl_frame_begin(dw4_gl *g, const float view[16], float fov, float aspect,
                       const float ambient[3], const dw4_light *lights, int nlights)
{
    (void)g; (void)view; (void)fov; (void)aspect; (void)ambient; (void)lights; (void)nlights;
    return -1;
}
int dw4_gl_frame_mesh(dw4_gl *g, const float *pos, const float *nrm, const float *uv,
                      const uint32_t *tris, uint32_t nv, uint32_t nt,
                      const float tint[3], const dw4_tex *tex)
{
    (void)g; (void)pos; (void)nrm; (void)uv; (void)tris; (void)nv; (void)nt; (void)tint; (void)tex;
    return -1;
}
int dw4_gl_frame_end(dw4_gl *g, dw4_fb *fb) { (void)g; (void)fb; return -1; }
int dw4_gl_render(dw4_gl *g, dw4_fb *fb, const float *pos, const float *nrm, const float *uv,
                  const uint32_t *tris, uint32_t nv, uint32_t nt,
                  const float view[16], float fov, float aspect,
                  const float ambient[3], const dw4_light *lights, int nlights,
                  const float tint[3], const dw4_tex *tex)
{
    (void)g; (void)fb; (void)pos; (void)nrm; (void)uv; (void)tris; (void)nv; (void)nt;
    (void)view; (void)fov; (void)aspect; (void)ambient; (void)lights; (void)nlights; (void)tint;
    (void)tex;
    return -1;
}

#endif /* DW4_ENABLE_GL */
