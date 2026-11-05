#include "dw4/gl_layer.h"
#include "dw4/gpupolicy.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef DW4_ENABLE_GL
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#ifdef DW4_ENABLE_SDL2
#include <SDL.h>
#endif

#include "glcontext.h"
typedef dw4_glctx_saved saved_context;
typedef struct {
    float xy[2], stq[3], color[4], z, fog;
} layer_vertex;
typedef struct {
    const uint8_t *pixels;
    int w, h;
    GLuint id;
    int dirty;
} layer_texture;
struct dw4_gl_layer {
    EGLDisplay display;
    EGLContext context;
    GLuint fbo, color, depth, program, vao, vbo;
    GLuint post_program,post_texture,blit_texture;
    GLint post_mode,post_factor,post_sampler,post_source,post_origin,post_rect,post_keep,post_divisor;
    GLint size, has_tex, tex, wrap, linear, aref, alpha_ref, blend, straight,
        fog;
    GLint fog_color, gs_raster;
    int w, h, capacity, ntextures;
    layer_vertex *vertices;
    layer_texture *textures;
    uint8_t *pixels;
    char renderer[160];
    /* Deferred mode (dw4_gl_layer_defer): the frame stays resident in the fbo between operations and is read back
     * once by the closing call; `stale` means the fbo is newer than the CPU copy in `res_fb`. */
    int defer,resident,stale,defer_depth;
    int refs;                    /* dw4_gl_layer_share: owners of this renderer */
    dw4_fb *res_fb;
};

static saved_context save_context(void){return dw4_glctx_save();}
static int activate_context(dw4_gl_layer *g,saved_context s)
{return dw4_glctx_activate(g->display,g->context,s);}
static int restore_context(dw4_gl_layer *g,saved_context s)
{return dw4_glctx_restore(g->display,s);}
static int fb_resident(const dw4_gl_layer *g,const dw4_fb *fb){return g->defer && g->resident && g->res_fb==fb;}
/* Context must be active.  Reads the resident frame back into its CPU framebuffer. */
static int flush_resident(dw4_gl_layer *g)
{
    if(!g->stale || !g->res_fb)return 0;
    glBindFramebuffer(GL_FRAMEBUFFER,g->fbo);
    glReadPixels(0,0,g->w,g->h,GL_RGBA,GL_UNSIGNED_BYTE,g->pixels);
    if(glGetError()!=GL_NO_ERROR)return -1;
    for(int y=0;y<g->h;y++)memcpy(g->res_fb->rgba+(size_t)y*g->w*4,g->pixels+(size_t)(g->h-1-y)*g->w*4,(size_t)g->w*4);
    g->stale=0;return 0;
}
/* Before an operation on `fb`: a resident frame belonging to another surface is written back first. */
static void release_foreign(dw4_gl_layer *g,const dw4_fb *fb)
{
    if(g->defer && g->resident && g->res_fb!=fb){flush_resident(g);g->resident=0;}
}
/* After a successful operation that left its result in the fbo. */
static void mark_resident(dw4_gl_layer *g,dw4_fb *fb){if(g->defer){g->resident=1;g->res_fb=fb;g->stale=1;}}
/* Copy the resident frame into the post texture (GPU side) instead of uploading the CPU copy. */
static void resident_to_post(dw4_gl_layer *g)
{
    glBindFramebuffer(GL_FRAMEBUFFER,g->fbo);
    glActiveTexture(GL_TEXTURE0);glBindTexture(GL_TEXTURE_2D,g->post_texture);
    glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,0,0,g->w,g->h);
}

static const char *vs_source =
    "#version 300 es\n"
    "layout(location=0) in vec2 aXY; layout(location=1) in vec3 aSTQ;\n"
    "layout(location=2) in vec4 aColor; layout(location=3) in float aZ;\n"
    "layout(location=4) in float aFog; uniform vec2 uSize; uniform int uWrap,uGS;\n"
    "out vec3 vSTQ; out vec4 vColor; out float vZ; out float vFog;\n"
    "void main(){\n"
    " vec2 xy=aXY+(uGS!=0 ? vec2(0.5) : uWrap!=0 ? -vec2(1.0/64.0,1.0/128.0) : vec2(0.0));\n"
    " gl_Position=vec4(xy.x*2.0/uSize.x-1.0,1.0-xy.y*2.0/uSize.y,0.0,1.0);\n"
    " vSTQ=aSTQ; vColor=aColor; vZ=aZ; vFog=aFog; }\n";

/* w=1 keeps colour/Z/fog/STQ affine in screen space. Divide S,T by Q only
 * in the fragment, as the GS does. Round bilinear samples to RGBA8 before
 * applying MODULATE/AREF, matching the software material contract. */
static const char *fs_source =
    "#version 300 es\nprecision highp float; precision highp int;\n"
    "in vec3 vSTQ; in vec4 vColor; in float vZ; in float vFog; out vec4 "
    "color;\n"
    "uniform sampler2D uTex; uniform int "
    "uHasTex,uWrap,uLinear,uAref,uBlend,uStraight,uFog,uGS;\n"
    "uniform float uAlphaRef; uniform vec3 uFogColor;\n"
    "vec4 fetch(ivec2 p){ ivec2 s=textureSize(uTex,0);\n"
    " if(uWrap!=0) p=((p%s)+s)%s; else p=clamp(p,ivec2(0),s-1);\n"
    /* Recover RGBA8 bytes before the GS integer truncation below. A normalized
     * sample multiplied by 255 can be just below its original integer. */
    " return floor(texelFetch(uTex,p,0)*255.0+0.5); }\n"
    "void main(){ float alpha; vec3 rgb;\n"
    " if(uHasTex!=0){\n"
    "  float q=abs(vSTQ.z)<1e-9 ? 1e-9 : vSTQ.z;\n"
    "  vec2 uv=vSTQ.xy/q*vec2(textureSize(uTex,0)); vec4 t;\n"
    "  if(uLinear!=0){ vec2 p=uv-0.5; ivec2 i=ivec2(floor(p)); vec2 "
    "a=fract(p);\n"
    "   if(uGS!=0){ a=floor(a*16.0)/16.0;\n"
    "    vec4 top=floor(mix(fetch(i),fetch(i+ivec2(1,0)),a.x));\n"
    "    vec4 bot=floor(mix(fetch(i+ivec2(0,1)),fetch(i+ivec2(1,1)),a.x));\n"
    "    t=floor(mix(top,bot,a.y));\n"
    "   }else t=floor(mix(mix(fetch(i),fetch(i+ivec2(1,0)),a.x),\n"
    "               "
    "mix(fetch(i+ivec2(0,1)),fetch(i+ivec2(1,1)),a.x),a.y)+0.5);\n"
    "  }else t=fetch(ivec2(floor(uv)));\n"
    "  float gsAlpha=t.a*vColor.a/128.0;\n"
    "  if(uAref>=0 && int(gsAlpha)<=uAref) discard;\n"
    "  alpha=min(gsAlpha/128.0,1.0);\n"
    "  if(uAlphaRef>=0.0 && alpha<uAlphaRef) discard;\n"
    "  rgb=t.rgb*vColor.rgb/128.0;\n"
    "  if(uGS!=0){ rgb=min(vec3(255.0),floor(t.rgb*floor(vColor.rgb*128.0)/16384.0));\n"
    "   alpha=min(floor(t.a*floor(vColor.a*128.0)/16384.0)/128.0,1.0); }\n"
    "  if(uFog!=0){ if(uGS!=0) rgb=uFogColor+floor((rgb-uFogColor)*floor(clamp(vFog,0.0,255.0)*128.0)/32768.0);\n"
    "   else rgb=mix(uFogColor,rgb,clamp(vFog/255.0,0.0,1.0)); }\n"
    " }else{ alpha=min(vColor.a/128.0,1.0); rgb=vColor.rgb*2.0; }\n"
    " float rgbAlpha=(uStraight!=0 && uBlend==0) ? 1.0 : alpha;\n"
    " color=vec4(rgb*rgbAlpha/255.0,uBlend==0 ? 1.0 : alpha);\n"
    " gl_FragDepth=clamp(floor(vZ+(uGS!=0 ? 0.0 : 0.5))/16777216.0,0.0,1.0); }\n";

static GLuint compile_shader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    GLint ok;
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[2048];
        glGetShaderInfoLog(shader, sizeof log, NULL, log);
        fprintf(stderr, "GPU layer shader: %s\n", log);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static const char *post_vs=
    "#version 300 es\n"
    "void main(){ vec2 p=gl_VertexID==0?vec2(-1,-1):gl_VertexID==1?vec2(3,-1):vec2(-1,3);\n"
    "gl_Position=vec4(p,0,1); }\n";
static const char *post_fs=
    "#version 300 es\nprecision highp float; precision highp int;\n"
    "uniform sampler2D uInput,uSource; uniform ivec2 uOrigin; uniform ivec4 uRect; uniform int uMode,uKeep,uDivisor; uniform float uFactor; out vec4 color;\n"
    "void main(){ if(uMode==4){ ivec2 p=ivec2(gl_FragCoord.xy),src=textureSize(uSource,0),dst=textureSize(uInput,0);\n"
    "ivec2 q=ivec2(p.x*src.x/dst.x,src.y-1-(dst.y-1-p.y)*src.y/dst.y);color=texelFetch(uSource,q,0);return;}\n"
    "vec4 bytes=floor(texelFetch(uInput,ivec2(gl_FragCoord.xy),0)*255.0+0.5);\n"
    "if(uMode==0) color=vec4(floor(bytes.rgb*uFactor),bytes.a)/255.0;\n"
    "else if(uMode==1){ float scale=bytes.r*(128.0/255.0); float alpha=floor(scale*(1.0-uFactor)+0.5);\n"
    "color=vec4(0,0,0,alpha/255.0); }\n"
    "else if(uMode==3){ ivec2 p=ivec2(gl_FragCoord.xy);color=bytes/255.0;\n"
    "if(all(greaterThanEqual(p,uRect.xy)) && all(lessThan(p,uRect.xy+uRect.zw)))\n"
    "color=vec4(vec3(uvec3(bytes.rgb)*uint(uKeep)/uint(uDivisor)),bytes.a)/255.0; }\n"
    "else{ ivec2 p=ivec2(gl_FragCoord.xy)-uOrigin; ivec2 size=textureSize(uSource,0);\n"
    "color=bytes/255.0; if(any(lessThan(p,ivec2(0))) || any(greaterThanEqual(p,size)))return;\n"
    "uvec4 src=uvec4(floor(texelFetch(uSource,p,0)*255.0+0.5)); if(src.a==0u)return;\n"
    "uint alpha=uint(floor(float(src.a)*uFactor+0.5));\n"
    "uvec3 rgb=(src.rgb*alpha+uvec3(bytes.rgb)*(255u-alpha)+127u)/255u;\n"
    "color=vec4(vec3(rgb)/255.0,1.0); } }\n";
static int post_open(dw4_gl_layer *g)
{
    if(g->post_program)return 0;
    GLuint vs=compile_shader(GL_VERTEX_SHADER,post_vs),fs=compile_shader(GL_FRAGMENT_SHADER,post_fs);
    if(!vs || !fs){glDeleteShader(vs);glDeleteShader(fs);return -1;}
    GLuint program=glCreateProgram();glAttachShader(program,vs);glAttachShader(program,fs);glLinkProgram(program);
    GLint ok=0;glGetProgramiv(program,GL_LINK_STATUS,&ok);glDeleteShader(vs);glDeleteShader(fs);
    if(!ok){glDeleteProgram(program);return -1;}
    g->post_program=program;g->post_mode=glGetUniformLocation(program,"uMode");
    g->post_factor=glGetUniformLocation(program,"uFactor");g->post_sampler=glGetUniformLocation(program,"uInput");
    g->post_source=glGetUniformLocation(program,"uSource");g->post_origin=glGetUniformLocation(program,"uOrigin");
    g->post_rect=glGetUniformLocation(program,"uRect");g->post_keep=glGetUniformLocation(program,"uKeep");
    g->post_divisor=glGetUniformLocation(program,"uDivisor");
    glGenTextures(1,&g->post_texture);glBindTexture(GL_TEXTURE_2D,g->post_texture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,g->w,g->h,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    if(glGetError()==GL_NO_ERROR)return 0;
    glDeleteTextures(1,&g->post_texture);glDeleteProgram(g->post_program);
    g->post_texture=g->post_program=0;return -1;
}

dw4_gl_layer *dw4_gl_layer_open(int w, int h)
{
    dw4_gl_layer *g;
    saved_context saved = save_context();
    EGLConfig config;
    EGLint n;
    const EGLint cfg[] = {EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
                          EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT, EGL_NONE};
    const EGLint ctx[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    PFNEGLGETPLATFORMDISPLAYEXTPROC platform;
    GLuint vs = 0, fs = 0;
    GLint ok;
    if (w <= 0 || h <= 0)
        return NULL;
    g = calloc(1, sizeof *g);
    if (g) g->refs = 1;
    if (!g)
        return NULL;
    g->w = w;
    g->h = h;
    platform = (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress(
        "eglGetPlatformDisplayEXT");
    g->display = platform ? platform(EGL_PLATFORM_SURFACELESS_MESA,
                                     EGL_DEFAULT_DISPLAY, NULL)
                          : EGL_NO_DISPLAY;
    if (g->display == EGL_NO_DISPLAY || !eglInitialize(g->display, NULL, NULL))
        goto fail;
    if (!eglBindAPI(EGL_OPENGL_ES_API) ||
        !eglChooseConfig(g->display, cfg, &config, 1, &n) || n < 1)
        goto fail;
    g->context = eglCreateContext(g->display, config, EGL_NO_CONTEXT, ctx);
    if (g->context == EGL_NO_CONTEXT || activate_context(g, saved))
        goto fail;
    const char *renderer=(const char *)glGetString(GL_RENDERER);
    snprintf(g->renderer, sizeof g->renderer, "%s",renderer?renderer:"unavailable");
    if(!dw4_gpu_policy_accept(g->renderer))goto fail;
    g->pixels = malloc((size_t)w * h * 4);
    if (!g->pixels)
        goto fail;
    glGenTextures(1, &g->color);
    glBindTexture(GL_TEXTURE_2D, g->color);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenRenderbuffers(1, &g->depth);
    glBindRenderbuffer(GL_RENDERBUFFER, g->depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32F, w, h);
    glGenFramebuffers(1, &g->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, g->fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           g->color, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, g->depth);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        goto fail;
    vs = compile_shader(GL_VERTEX_SHADER, vs_source);
    fs = compile_shader(GL_FRAGMENT_SHADER, fs_source);
    if (!vs || !fs)
        goto fail;
    g->program = glCreateProgram();
    glAttachShader(g->program, vs);
    glAttachShader(g->program, fs);
    glLinkProgram(g->program);
    glGetProgramiv(g->program, GL_LINK_STATUS, &ok);
    glDeleteShader(vs);
    glDeleteShader(fs);
    vs = fs = 0;
    if (!ok)
        goto fail;
#define UNIFORM(field, name) g->field = glGetUniformLocation(g->program, name)
    UNIFORM(size, "uSize");
    UNIFORM(has_tex, "uHasTex");
    UNIFORM(tex, "uTex");
    UNIFORM(wrap, "uWrap");
    UNIFORM(gs_raster,"uGS");
    UNIFORM(linear, "uLinear");
    UNIFORM(aref, "uAref");
    UNIFORM(alpha_ref, "uAlphaRef");
    UNIFORM(blend, "uBlend");
    UNIFORM(straight, "uStraight");
    UNIFORM(fog, "uFog");
    UNIFORM(fog_color, "uFogColor");
#undef UNIFORM
    glGenVertexArrays(1, &g->vao);
    glBindVertexArray(g->vao);
    glGenBuffers(1, &g->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, g->vbo);
#define ATTR(index, count, field)                                              \
    glEnableVertexAttribArray(index);                                          \
    glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE,                    \
                          sizeof(layer_vertex),                                \
                          (void *)offsetof(layer_vertex, field))
    ATTR(0, 2, xy);
    ATTR(1, 3, stq);
    ATTR(2, 4, color);
    ATTR(3, 1, z);
    ATTR(4, 1, fog);
#undef ATTR
    if (glGetError() != GL_NO_ERROR || restore_context(g, saved))
        goto fail;
    return g;
fail:
    dw4_gpu_policy_fail("GLES layer initialization");
    if(dw4_gpu_policy_error()[0])fprintf(stderr,"GPU layer: %s\n",dw4_gpu_policy_error());
    else fprintf(stderr, "GPU layer: setup failed (EGL 0x%x)\n", eglGetError());
    if (vs)
        glDeleteShader(vs);
    if (fs)
        glDeleteShader(fs);
    restore_context(g, saved);
    dw4_gl_layer_close(g);
    return NULL;
}

void dw4_gl_layer_close(dw4_gl_layer *g)
{
    saved_context saved;
    int i;
    if (!g)
        return;
    if (--g->refs > 0)
        return;           /* another owner still renders through it */
    saved = save_context();
    if (g->context != EGL_NO_CONTEXT && !activate_context(g, saved)) {
        for (i = 0; i < g->ntextures; i++)
            glDeleteTextures(1, &g->textures[i].id);
        glDeleteBuffers(1, &g->vbo);
        glDeleteVertexArrays(1, &g->vao);
        glDeleteProgram(g->program);
        glDeleteProgram(g->post_program);
        glDeleteTextures(1,&g->post_texture);
        glDeleteTextures(1,&g->blit_texture);
        glDeleteFramebuffers(1, &g->fbo);
        glDeleteRenderbuffers(1, &g->depth);
        glDeleteTextures(1, &g->color);
        if (saved.context == g->context)
            saved = (saved_context){.display = EGL_NO_DISPLAY,
                                    .context = EGL_NO_CONTEXT,
                                    .draw = EGL_NO_SURFACE,
                                    .read = EGL_NO_SURFACE,
                                    .api = EGL_OPENGL_ES_API};
        restore_context(g, saved);
        eglDestroyContext(g->display, g->context);
    }
    /* EGL displays are process-wide and may also serve another offscreen
     * renderer. Destroy our context/resources without terminating that shared
     * display. */
    free(g->pixels);
    free(g->textures);
    free(g->vertices);
    free(g);
}
const char *dw4_gl_layer_info(const dw4_gl_layer *g)
{
    return g ? g->renderer : "";
}

int dw4_gl_layer_clear(dw4_gl_layer *g,dw4_fb *fb,uint8_t r,uint8_t green,uint8_t b,uint8_t a)
{
    if(!g || !fb || !fb->rgba || fb->w!=g->w || fb->h!=g->h)return -1;
    saved_context saved=save_context();int rc=-1;
    if(activate_context(g,saved)){restore_context(g,saved);return -1;}
    release_foreign(g,fb);
    glBindFramebuffer(GL_FRAMEBUFFER,g->fbo);glViewport(0,0,g->w,g->h);
    glDisable(GL_SCISSOR_TEST);glDisable(GL_DITHER);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);glDepthMask(GL_TRUE);
    glClearColor(r/255.f,green/255.f,b/255.f,a/255.f);glClearDepthf(0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(!g->defer)glReadPixels(0,0,g->w,g->h,GL_RGBA,GL_UNSIGNED_BYTE,g->pixels);
    if(glGetError()==GL_NO_ERROR)rc=0;
    if(restore_context(g,saved))rc=-1;
    if(!rc && g->defer){mark_resident(g,fb);return 0;}
    if(!rc)for(int y=0;y<g->h;y++)memcpy(fb->rgba+(size_t)y*g->w*4,
        g->pixels+(size_t)(g->h-1-y)*g->w*4,(size_t)g->w*4);
    return rc;
}

int dw4_gl_layer_transform(dw4_gl_layer *g,dw4_fb *fb,int mode,float factor)
{
    if(!g || !fb || !fb->rgba || fb->w!=g->w || fb->h!=g->h ||
       (mode!=DW4_GL_FADE_RGB && mode!=DW4_GL_SHADOW_ALPHA) || !isfinite(factor) || factor<0 || factor>1)return -1;
    saved_context saved=save_context();int rc=-1;
    if(activate_context(g,saved)){restore_context(g,saved);return -1;}
    if(post_open(g))goto done;
    release_foreign(g,fb);
    if(fb_resident(g,fb))resident_to_post(g);
    else {
        for(int y=0;y<g->h;y++)memcpy(g->pixels+(size_t)y*g->w*4,
            fb->rgba+(size_t)(g->h-1-y)*g->w*4,(size_t)g->w*4);
        glActiveTexture(GL_TEXTURE0);glBindTexture(GL_TEXTURE_2D,g->post_texture);
        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,g->w,g->h,GL_RGBA,GL_UNSIGNED_BYTE,g->pixels);
    }
    glBindFramebuffer(GL_FRAMEBUFFER,g->fbo);glViewport(0,0,g->w,g->h);
    glDisable(GL_DEPTH_TEST);glDisable(GL_BLEND);glDisable(GL_CULL_FACE);glDisable(GL_SCISSOR_TEST);glDisable(GL_DITHER);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);glDepthMask(GL_FALSE);
    glUseProgram(g->post_program);glBindVertexArray(g->vao);
    glUniform1i(g->post_sampler,0);glUniform1i(g->post_mode,mode);glUniform1f(g->post_factor,factor);
    glDrawArrays(GL_TRIANGLES,0,3);
    if(!g->defer)glReadPixels(0,0,g->w,g->h,GL_RGBA,GL_UNSIGNED_BYTE,g->pixels);
    if(glGetError()==GL_NO_ERROR)rc=0;
done:
    if(restore_context(g,saved))rc=-1;
    if(!rc && g->defer){mark_resident(g,fb);return 0;}
    if(!rc)for(int y=0;y<g->h;y++)memcpy(fb->rgba+(size_t)y*g->w*4,
        g->pixels+(size_t)(g->h-1-y)*g->w*4,(size_t)g->w*4);
    return rc;
}

static int layer_image(dw4_gl_layer *g,dw4_fb *fb,const dw4_fb *src,int x,int y,float opacity,int mode)
{
    if(!g || !fb || !fb->rgba || fb->w!=g->w || fb->h!=g->h || !src || !src->rgba ||
       src==fb || src->w<=0 || src->h<=0 || !isfinite(opacity) || opacity<0 || opacity>1)return -1;
    if(mode==2 && ((int64_t)x+src->w<=0 || (int64_t)y+src->h<=0 || x>=g->w || y>=g->h))return 0;
    if((size_t)src->w>SIZE_MAX/4/(size_t)src->h)return -1;
    size_t row=(size_t)src->w*4;uint8_t *source=malloc(row*src->h);if(!source)return -1;
    for(int i=0;i<src->h;i++)memcpy(source+(size_t)i*row,src->rgba+(size_t)(src->h-1-i)*row,row);
    saved_context saved=save_context();int rc=-1;
    if(activate_context(g,saved)){restore_context(g,saved);free(source);return -1;}
    if(post_open(g))goto done;
    release_foreign(g,fb);
    if(mode==2 && fb_resident(g,fb))resident_to_post(g);
    else if(mode==2) {
        for(int i=0;i<g->h;i++)memcpy(g->pixels+(size_t)i*g->w*4,
            fb->rgba+(size_t)(g->h-1-i)*g->w*4,(size_t)g->w*4);
        glActiveTexture(GL_TEXTURE0);glBindTexture(GL_TEXTURE_2D,g->post_texture);
        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,g->w,g->h,GL_RGBA,GL_UNSIGNED_BYTE,g->pixels);
    }
    glActiveTexture(GL_TEXTURE0);glBindTexture(GL_TEXTURE_2D,g->post_texture);
    glActiveTexture(GL_TEXTURE1);
    if(!g->blit_texture)glGenTextures(1,&g->blit_texture);
    glBindTexture(GL_TEXTURE_2D,g->blit_texture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,src->w,src->h,0,GL_RGBA,GL_UNSIGNED_BYTE,source);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER,g->fbo);glViewport(0,0,g->w,g->h);
    glDisable(GL_DEPTH_TEST);glDisable(GL_BLEND);glDisable(GL_CULL_FACE);glDisable(GL_SCISSOR_TEST);glDisable(GL_DITHER);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);glDepthMask(GL_FALSE);
    glUseProgram(g->post_program);glBindVertexArray(g->vao);
    glUniform1i(g->post_sampler,0);glUniform1i(g->post_source,1);glUniform1i(g->post_mode,mode);
    glUniform2i(g->post_origin,x,(int)((int64_t)g->h-y-src->h));glUniform1f(g->post_factor,opacity);
    glDrawArrays(GL_TRIANGLES,0,3);if(!g->defer)glReadPixels(0,0,g->w,g->h,GL_RGBA,GL_UNSIGNED_BYTE,g->pixels);
    if(glGetError()==GL_NO_ERROR)rc=0;
done:
    glActiveTexture(GL_TEXTURE0);if(restore_context(g,saved))rc=-1;
    if(!rc && g->defer){mark_resident(g,fb);free(source);return 0;}
    if(!rc)for(int i=0;i<g->h;i++)memcpy(fb->rgba+(size_t)i*g->w*4,
        g->pixels+(size_t)(g->h-1-i)*g->w*4,(size_t)g->w*4);
    free(source);return rc;
}
int dw4_gl_layer_blit(dw4_gl_layer *g,dw4_fb *fb,const dw4_fb *src,int x,int y,float opacity)
{return layer_image(g,fb,src,x,y,opacity,2);}
int dw4_gl_layer_scale(dw4_gl_layer *g,dw4_fb *fb,const dw4_fb *src)
{return layer_image(g,fb,src,0,0,1,4);}

static int layer_multiply_rect(dw4_gl_layer *g,dw4_fb *fb,int x,int y,int w,int h,unsigned keep,unsigned divisor)
{
    if(!g || !fb || !fb->rgba || fb->w!=g->w || fb->h!=g->h)return -1;
    int64_t x1=(int64_t)x+w,y1=(int64_t)y+h;
    if(x<0)x=0;
    if(y<0)y=0;
    if(x1>g->w)x1=g->w;
    if(y1>g->h)y1=g->h;
    if(w<=0 || h<=0 || x1<=x || y1<=y)return 0;
    saved_context saved=save_context();int rc=-1;
    if(activate_context(g,saved)){restore_context(g,saved);return -1;}
    if(post_open(g))goto done;
    release_foreign(g,fb);
    if(fb_resident(g,fb))resident_to_post(g);
    else {
        for(int i=0;i<g->h;i++)memcpy(g->pixels+(size_t)i*g->w*4,
            fb->rgba+(size_t)(g->h-1-i)*g->w*4,(size_t)g->w*4);
        glActiveTexture(GL_TEXTURE0);glBindTexture(GL_TEXTURE_2D,g->post_texture);
        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,g->w,g->h,GL_RGBA,GL_UNSIGNED_BYTE,g->pixels);
    }
    glBindFramebuffer(GL_FRAMEBUFFER,g->fbo);glViewport(0,0,g->w,g->h);
    glDisable(GL_DEPTH_TEST);glDisable(GL_BLEND);glDisable(GL_CULL_FACE);glDisable(GL_SCISSOR_TEST);glDisable(GL_DITHER);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);glDepthMask(GL_FALSE);
    glUseProgram(g->post_program);glBindVertexArray(g->vao);
    glUniform1i(g->post_sampler,0);glUniform1i(g->post_mode,3);glUniform1i(g->post_keep,(int)keep);glUniform1i(g->post_divisor,(int)divisor);
    glUniform4i(g->post_rect,x,g->h-(int)y1,(int)x1-x,(int)y1-y);
    glDrawArrays(GL_TRIANGLES,0,3);if(!g->defer)glReadPixels(0,0,g->w,g->h,GL_RGBA,GL_UNSIGNED_BYTE,g->pixels);
    if(glGetError()==GL_NO_ERROR)rc=0;
done:
    if(restore_context(g,saved))rc=-1;
    if(!rc && g->defer){mark_resident(g,fb);return 0;}
    if(!rc)for(int i=0;i<g->h;i++)memcpy(fb->rgba+(size_t)i*g->w*4,
        g->pixels+(size_t)(g->h-1-i)*g->w*4,(size_t)g->w*4);
    return rc;
}
int dw4_gl_layer_plate(dw4_gl_layer *g,dw4_fb *fb,int x,int y,int w,int h,int darken)
{if(darken<0)darken=0;if(darken>100)darken=100;return layer_multiply_rect(g,fb,x,y,w,h,100-darken,100);}
int dw4_gl_layer_multiply(dw4_gl_layer *g,dw4_fb *fb,unsigned numerator,unsigned denominator)
{
    if(!fb || !denominator || denominator>65535 || numerator>denominator)return -1;
    return layer_multiply_rect(g,fb,0,0,fb->w,fb->h,numerator,denominator);
}

static GLuint texture(dw4_gl_layer *g, const dw4_tex *t)
{
    layer_texture *entry, *p;
    int i;
    if (!t)
        return 0;
    for (i = 0; i < g->ntextures; i++) {
        entry = g->textures + i;
        if (entry->pixels == t->rgba && entry->w == t->w && entry->h == t->h) {
            if(entry->dirty) {
                glBindTexture(GL_TEXTURE_2D,entry->id);
                glTexSubImage2D(GL_TEXTURE_2D,0,0,0,t->w,t->h,GL_RGBA,GL_UNSIGNED_BYTE,t->rgba);
                entry->dirty=0;
            }
            return entry->id;
        }
    }
    p = realloc(g->textures, (size_t)(g->ntextures + 1) * sizeof *p);
    if (!p)
        return 0;
    g->textures = p;
    entry = p + g->ntextures++;
    entry->dirty=0;
    entry->pixels = t->rgba;
    entry->w = t->w;
    entry->h = t->h;
    glGenTextures(1, &entry->id);
    glBindTexture(GL_TEXTURE_2D, entry->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, t->w, t->h, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, t->rgba);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return entry->id;
}
dw4_gl_layer *dw4_gl_layer_share(dw4_gl_layer *g){if(g)g->refs++;return g;}
int dw4_gl_layer_defer(dw4_gl_layer *g,dw4_fb *fb,int on)
{
    if(!g || !fb || !fb->rgba || fb->w!=g->w || fb->h!=g->h)return -1;
    if(on){
        if(g->defer_depth++)return 0;      /* nested: the outermost run owns the flush */
        g->defer=1;g->resident=0;g->stale=0;g->res_fb=NULL;return 0;
    }
    if(!g->defer || g->defer_depth<=0 || --g->defer_depth)return 0;
    int rc=0;
    if(g->stale){
        saved_context saved=save_context();
        if(activate_context(g,saved)){restore_context(g,saved);rc=-1;}
        else{rc=flush_resident(g);if(restore_context(g,saved))rc=-1;}
    }
    g->defer=0;g->resident=0;g->stale=0;g->res_fb=NULL;
    return rc;
}
void dw4_gl_layer_texture_changed(dw4_gl_layer *g,const dw4_tex *t)
{
    if(!g || !t) return;
    for(int i=0;i<g->ntextures;i++) if(g->textures[i].pixels==t->rgba)
        g->textures[i].dirty=1;
}
int dw4_gl_layer_cached_textures(const dw4_gl_layer *g){return g?g->ntextures:0;}
int dw4_gl_layer_owners(const dw4_gl_layer *g){return g?g->refs:0;}
void dw4_gl_layer_texture_forget(dw4_gl_layer *g,const dw4_tex *t)
{
    if(!g || !t)return;
    for(int i=0;i<g->ntextures;i++) if(g->textures[i].pixels==t->rgba && g->textures[i].w==t->w && g->textures[i].h==t->h) {
        saved_context previous=save_context();
        if(!activate_context(g,previous))glDeleteTextures(1,&g->textures[i].id);
        restore_context(g,previous);
        memmove(g->textures+i,g->textures+i+1,(size_t)(g->ntextures-i-1)*sizeof *g->textures);g->ntextures--;
        return;
    }
}
int dw4_gl_layer_textures_reset(dw4_gl_layer *g)
{
    if(!g)return 0;
    saved_context previous=save_context();
    if(activate_context(g,previous)){restore_context(g,previous);return -1;}
    for(int i=0;i<g->ntextures;i++)glDeleteTextures(1,&g->textures[i].id);
    free(g->textures);g->textures=NULL;g->ntextures=0;
    int failed=glGetError()!=GL_NO_ERROR;
    if(restore_context(g,previous))failed=1;
    return failed?-1:0;
}
static int same_material(const dw4_layer_draw *a, const dw4_layer_draw *b)
{
    return a->tex == b->tex && a->blend == b->blend && a->aref == b->aref &&
           a->straight_rgb == b->straight_rgb && a->gs_raster == b->gs_raster &&
           a->no_depth_write == b->no_depth_write && a->depth_always==b->depth_always && a->filter==b->filter && a->color_mask==b->color_mask && a->fog == b->fog &&
           !memcmp(a->fog_color, b->fog_color, 3);
}

int dw4_gl_layer_draw(dw4_gl_layer *g, dw4_fb *fb, const dw4_layer_draw *d,
                      int n, int wrap, int linear, float alpha_ref)
{
    saved_context saved;
    int i, j, k, end, rc = -1;
    if (!g || !fb || !fb->rgba || fb->w != g->w || fb->h != g->h || n < 0 ||
        (n && !d))
        return -1;
    if (!n)
        return 0;
    if (n > g->capacity) {
        layer_vertex *v = realloc(g->vertices, (size_t)n * 3 * sizeof *v);
        if (!v)
            return -1;
        g->vertices = v;
        g->capacity = n;
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < 3; j++) {
            layer_vertex *v = g->vertices + 3 * i + j;
            memcpy(v->xy, d[i].v[j], 2 * sizeof(float));
            memcpy(v->stq, d[i].v[j] + 2, 3 * sizeof(float));
            for (k = 0; k < 4; k++)
                v->color[k] = d[i].rgba[j][k];
            v->z = d[i].z[j];
            v->fog = d[i].f[j];
        }
    saved = save_context();
    if (activate_context(g, saved)) {
        restore_context(g, saved);
        return -1;
    }
    release_foreign(g, fb);
    if (!fb_resident(g, fb)) {
        for (i = 0; i < g->h; i++)
            memcpy(g->pixels + (size_t)i * g->w * 4,
                   fb->rgba + (size_t)(g->h - 1 - i) * g->w * 4, (size_t)g->w * 4);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, g->color);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, g->w, g->h, GL_RGBA,
                        GL_UNSIGNED_BYTE, g->pixels);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindFramebuffer(GL_FRAMEBUFFER, g->fbo);
    glViewport(0, 0, g->w, g->h);
    glDisable(GL_DITHER);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    glDepthFunc(GL_GEQUAL);
    glClearDepthf(0.0f);
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(g->program);
    glBindVertexArray(g->vao);
    glBindBuffer(GL_ARRAY_BUFFER, g->vbo);
    glBufferData(GL_ARRAY_BUFFER, (size_t)n * 3 * sizeof *g->vertices,
                 g->vertices, GL_STREAM_DRAW);
    glUniform2f(g->size, g->w, g->h);
    glUniform1i(g->tex, 0);
    glUniform1i(g->wrap, wrap);
    glUniform1i(g->linear, linear);
    glUniform1f(g->alpha_ref, alpha_ref);
    for (i = 0; i < n; i = end) {
        GLuint id = texture(g, d[i].tex);
        if (d[i].tex && !id)
            goto done;
        glBindTexture(GL_TEXTURE_2D, id);
        glUniform1i(g->has_tex, id != 0);
        glUniform1i(g->gs_raster,d[i].gs_raster);
        glUniform1i(g->aref, d[i].aref);
        glUniform1i(g->blend, d[i].blend);
        glUniform1i(g->linear,d[i].filter?d[i].filter==2:linear);
        glUniform1i(g->straight, d[i].straight_rgb);
        glUniform1i(g->fog, d[i].fog);
        glUniform3f(g->fog_color, d[i].fog == 2 ? d[i].fog_color[0] : 255,
                    d[i].fog == 2 ? d[i].fog_color[1] : 255,
                    d[i].fog == 2 ? d[i].fog_color[2] : 255);
        /* The CPU oracle's untextured diagnostic path bypasses layer depth. */
        if (d[i].tex)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
        glDepthMask(d[i].no_depth_write ? GL_FALSE : GL_TRUE);
        glColorMask(!(d[i].color_mask&1),!(d[i].color_mask&2),!(d[i].color_mask&4),!(d[i].color_mask&8));
        glDepthFunc(d[i].depth_always?GL_ALWAYS:GL_GEQUAL);
        if (d[i].blend) {
            glEnable(GL_BLEND);
            glBlendFuncSeparate(
                GL_ONE, d[i].blend == 2 ? GL_ONE : GL_ONE_MINUS_SRC_ALPHA,
                GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        } else
            glDisable(GL_BLEND);
        for (end = i + 1; end < n && same_material(d + i, d + end); end++) {
        }
        glDrawArrays(GL_TRIANGLES, i * 3, (end - i) * 3);
    }
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    if (!g->defer)
        glReadPixels(0, 0, g->w, g->h, GL_RGBA, GL_UNSIGNED_BYTE, g->pixels);
    if (glGetError() != GL_NO_ERROR)
        goto done;
    rc = 0;
done:
    if (restore_context(g, saved))
        rc = -1;
    if (!rc && g->defer) {
        mark_resident(g, fb);
        return 0;
    }
    if (!rc)
        for (i = 0; i < g->h; i++)
            memcpy(fb->rgba + (size_t)i * g->w * 4,
                   g->pixels + (size_t)(g->h - 1 - i) * g->w * 4,
                   (size_t)g->w * 4);
    return rc;
}
#else
void dw4_gl_layer_texture_changed(dw4_gl_layer *g,const dw4_tex *t) { (void)g;(void)t; }
void dw4_gl_layer_texture_forget(dw4_gl_layer *g,const dw4_tex *t) { (void)g;(void)t; }
int dw4_gl_layer_cached_textures(const dw4_gl_layer *g){(void)g;return 0;}
int dw4_gl_layer_owners(const dw4_gl_layer *g){(void)g;return 0;}
dw4_gl_layer *dw4_gl_layer_open(int w, int h)
{
    (void)w;
    (void)h;
    dw4_gpu_policy_fail("GLES layer backend not compiled");
    return NULL;
}
void dw4_gl_layer_close(dw4_gl_layer *g) { (void)g; }
dw4_gl_layer *dw4_gl_layer_share(dw4_gl_layer *g){return g;}
const char *dw4_gl_layer_info(const dw4_gl_layer *g)
{
    (void)g;
    return "";
}
int dw4_gl_layer_clear(dw4_gl_layer *g,dw4_fb *fb,uint8_t r,uint8_t green,uint8_t b,uint8_t a)
{(void)g;(void)fb;(void)r;(void)green;(void)b;(void)a;return -1;}
int dw4_gl_layer_transform(dw4_gl_layer *g,dw4_fb *fb,int mode,float factor)
{(void)g;(void)fb;(void)mode;(void)factor;return -1;}
int dw4_gl_layer_blit(dw4_gl_layer *g,dw4_fb *fb,const dw4_fb *src,int x,int y,float opacity)
{(void)g;(void)fb;(void)src;(void)x;(void)y;(void)opacity;return -1;}
int dw4_gl_layer_plate(dw4_gl_layer *g,dw4_fb *fb,int x,int y,int w,int h,int darken)
{(void)g;(void)fb;(void)x;(void)y;(void)w;(void)h;(void)darken;return -1;}
int dw4_gl_layer_scale(dw4_gl_layer *g,dw4_fb *fb,const dw4_fb *src)
{(void)g;(void)fb;(void)src;return -1;}
int dw4_gl_layer_multiply(dw4_gl_layer *g,dw4_fb *fb,unsigned numerator,unsigned denominator)
{(void)g;(void)fb;(void)numerator;(void)denominator;return -1;}
int dw4_gl_layer_textures_reset(dw4_gl_layer *g){return g?-1:0;}
int dw4_gl_layer_defer(dw4_gl_layer *g,dw4_fb *fb,int on){(void)fb;(void)on;return g?-1:0;}
int dw4_gl_layer_draw(dw4_gl_layer *g, dw4_fb *fb, const dw4_layer_draw *d,
                      int n, int w, int l, float a)
{
    (void)g;
    (void)fb;
    (void)d;
    (void)n;
    (void)w;
    (void)l;
    (void)a;
    return -1;
}
#endif

int dw4_gl_layer_ui(dw4_gl_layer *g, dw4_fb *fb, const dw4_ui_draw *ui, int n)
{
    dw4_layer_draw *d;
    int i, rc;
    if (!n)
        return 0;
    if (!g || n < 0 || !ui)
        return -1;
    d = calloc((size_t)n, sizeof *d);
    if (!d)
        return -1;
    for (i = 0; i < n; i++) {
        if (!ui[i].stq) {
            free(d);
            return -1;
        }
        d[i].tex = ui[i].tex;
        d[i].blend = ui[i].blend;
        d[i].aref = dw4_render_aref;
        d[i].no_depth_write = ui[i].depth_mode?!ui[i].depth_write:1;
        d[i].depth_always=ui[i].depth_mode==2;
        d[i].gs_raster=d[i].straight_rgb=ui[i].gs_raster;
        d[i].filter=ui[i].filter;
        d[i].color_mask=ui[i].color_mask;
        memcpy(d[i].v, ui[i].v, sizeof d[i].v);
        memcpy(d[i].rgba, ui[i].rgba, sizeof d[i].rgba);
        /* Legacy UI passes at constant Z without writes. Authored WN keeps its
         * per-vertex depth and explicit GEQUAL/ALWAYS policy. */
        for(unsigned j=0;j<3;j++)d[i].z[j]=ui[i].depth_mode?ui[i].z[j]:1;
    }
    rc = dw4_gl_layer_draw(g, fb, d, n, dw4_render_tex_wrap,
                           dw4_render_tex_linear, dw4_render_alpha_ref);
    free(d);
    return rc;
}
void dw4_gl_layer_ui_or_cpu(dw4_gl_layer **g, dw4_fb *fb, const dw4_ui_draw *d,
                            int n, int threads)
{
    if (*g && !dw4_gl_layer_ui(*g, fb, d, n))
        return;
    if(dw4_gpu_policy_required()){
        dw4_gpu_policy_fail(*g?"menu UI draw":"menu UI GPU unavailable");
        return;
    }
    if (*g) {
        fprintf(stderr, "  menu UI: GPU draw failed; reverting to CPU\n");
        dw4_gl_layer_close(*g);
        *g = NULL;
    }
    dw4_render_ui_draws(fb, d, n, threads);
}
