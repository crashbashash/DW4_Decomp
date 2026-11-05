#ifndef DW4_GL_CONTEXT_H
#define DW4_GL_CONTEXT_H
#include <EGL/egl.h>
#ifdef DW4_ENABLE_SDL2
#include <SDL.h>
#endif
typedef struct {
    EGLDisplay display;EGLContext context;EGLSurface draw,read;EGLenum api;
#ifdef DW4_ENABLE_SDL2
    SDL_Window *sdl_window;SDL_GLContext sdl_context;
#endif
} dw4_glctx_saved;
static inline dw4_glctx_saved dw4_glctx_save(void)
{
    dw4_glctx_saved s={.display=eglGetCurrentDisplay(),.context=eglGetCurrentContext(),
        .draw=eglGetCurrentSurface(EGL_DRAW),.read=eglGetCurrentSurface(EGL_READ),.api=eglQueryAPI()};
#ifdef DW4_ENABLE_SDL2
    s.sdl_window=SDL_GL_GetCurrentWindow();s.sdl_context=SDL_GL_GetCurrentContext();
#endif
    return s;
}
static inline int dw4_glctx_activate(EGLDisplay display,EGLContext context,dw4_glctx_saved s)
{
#ifdef DW4_ENABLE_SDL2
    if(s.sdl_context && SDL_GL_MakeCurrent(s.sdl_window,NULL))return -1;
#else
    (void)s;
#endif
    return eglBindAPI(EGL_OPENGL_ES_API) && eglMakeCurrent(display,EGL_NO_SURFACE,EGL_NO_SURFACE,context)?0:-1;
}
static inline int dw4_glctx_restore(EGLDisplay display,dw4_glctx_saved s)
{
    int rc=0;
    if(display!=EGL_NO_DISPLAY && !eglMakeCurrent(display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT))rc=-1;
    if(!eglBindAPI(s.api))rc=-1;
    if(s.display!=EGL_NO_DISPLAY && !eglMakeCurrent(s.display,s.draw,s.read,s.context))rc=-1;
#ifdef DW4_ENABLE_SDL2
    if(s.sdl_context && SDL_GL_MakeCurrent(s.sdl_window,s.sdl_context))rc=-1;
#endif
    return rc;
}
#endif
