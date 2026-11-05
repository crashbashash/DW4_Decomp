/* dw4/window.c — SDL2 present backend; see include/dw4/window.h. */
#define _GNU_SOURCE
#include "dw4/window.h"
#include "dw4/gpupolicy.h"
#include "dw4/pads.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef DW4_ENABLE_SDL2
#include <SDL.h>
#ifdef DW4_ENABLE_GL
#include <GLES3/gl3.h>
#endif
#endif

int dw4_window_retry(const char *operation, const char *path)
{
#ifdef DW4_ENABLE_SDL2
    char message[4608];
    int button = 0;
    const SDL_MessageBoxButtonData buttons[] = {
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Retry"},
        {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Back"}
    };
    snprintf(message, sizeof(message), "%s:\n%s\n\nCheck the file and directory permissions, then retry.\nBack cancels this file operation.", operation, path);
    const SDL_MessageBoxData data = {SDL_MESSAGEBOX_ERROR, NULL, "Digimon World 4", message, 2, buttons, NULL};
    return SDL_ShowMessageBox(&data, &button) == 0 && button == 1;
#else
    (void)operation; (void)path;
    return 0;
#endif
}

#ifdef DW4_ENABLE_SDL2

struct dw4_window {
    SDL_Window   *win;
    SDL_Renderer *ren;
    SDL_Texture  *tex;
    SDL_GameController *pad;    /* the first gamepad SDL sees, if any */
    dw4_matepads *mates;        /* the next three: the co-op players 2-4 (dw4/pads.h) */
    int           headless;
    int focus_lost, disconnected;
    SDL_JoystickGUID assigned_guid;
    int           w, h;
};

/* SDL's controller-button codes -> the portable DW4_BTN_* set (the game's mapping is applied in
 * input.c, not here). The pad's D-pad drives menus only, as in retail. */
static int map_pad_button(Uint8 b)
{
    switch (b) {
    case SDL_CONTROLLER_BUTTON_DPAD_UP: return DW4_BTN_DPAD_UP;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN: return DW4_BTN_DPAD_DOWN;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT: return DW4_BTN_DPAD_LEFT;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: return DW4_BTN_DPAD_RIGHT;
    case SDL_CONTROLLER_BUTTON_A: return DW4_BTN_FACE_A;   /* Cross  */
    case SDL_CONTROLLER_BUTTON_B: return DW4_BTN_FACE_B;   /* Circle */
    case SDL_CONTROLLER_BUTTON_X: return DW4_BTN_FACE_X;   /* Square */
    case SDL_CONTROLLER_BUTTON_Y: return DW4_BTN_FACE_Y;   /* Triangle */
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:  return DW4_BTN_L1;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: return DW4_BTN_R1;
    case SDL_CONTROLLER_BUTTON_START: return DW4_BTN_START;
    case SDL_CONTROLLER_BUTTON_BACK:  return DW4_BTN_SELECT;
    default: return 0;      /* Guide and stick clicks are unused */
    }
}

/* Keyboard arrows share the host's digital menu directions. */
static int map_key(SDL_Scancode sc)
{
    switch (sc) {
    case SDL_SCANCODE_RETURN: case SDL_SCANCODE_KP_ENTER: return DW4_BTN_FACE_A;
    case SDL_SCANCODE_SPACE:  return DW4_BTN_FACE_A;
    case SDL_SCANCODE_BACKSPACE: case SDL_SCANCODE_ESCAPE: return DW4_BTN_FACE_B;
    case SDL_SCANCODE_S: return DW4_BTN_FACE_X;
    case SDL_SCANCODE_D: return DW4_BTN_FACE_Y;
    case SDL_SCANCODE_UP:    return DW4_BTN_UP;
    case SDL_SCANCODE_DOWN:  return DW4_BTN_DOWN;
    case SDL_SCANCODE_LEFT:  return DW4_BTN_LEFT;
    case SDL_SCANCODE_RIGHT: return DW4_BTN_RIGHT;
    case SDL_SCANCODE_TAB:   return DW4_BTN_START;
    default: return 0;
    }
}

int dw4_window_built(void) { return 1; }

int dw4_window_key_button(int scancode) { return map_key((SDL_Scancode)scancode); }
int dw4_window_pad_button(int sdl_button) { return map_pad_button((Uint8)sdl_button); }

dw4_window *dw4_window_open(int w, int h, const char *title, int headless)
{
    dw4_window *o;

    if (w <= 0 || h <= 0)
        return NULL;
    if (headless)
        SDL_setenv("SDL_VIDEODRIVER", "dummy", 1);
    /* SDL drops joystick/controller events while the app has no input focus.  A port window under a
     * compositor (sway/wayvnc) often has none, so a real pad would be silently dead; ask SDL for
     * background pad events. */
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
        SDL_Quit();
        return NULL;
    }
    o = (dw4_window *)calloc(1, sizeof(*o));
    if (!o) {
        SDL_Quit();
        return NULL;
    }
    o->w = w;
    o->h = h;
    o->headless = headless;
    o->win = SDL_CreateWindow(title ? title : "dw4", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, w, h,
                              headless ? SDL_WINDOW_HIDDEN : SDL_WINDOW_SHOWN);
    if (!o->win)
        goto fail;
    o->ren = SDL_CreateRenderer(o->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    const char *driver=SDL_GetCurrentVideoDriver();
    int diagnostic=headless || (driver && !strcmp(driver,"dummy"));
    if (!o->ren && (!dw4_gpu_policy_required() || diagnostic))
        /* the software path is the one that presents reliably here, and it must ask for vsync too:
         * without it the loop ran ~240 fps onto a 60 Hz output, so the pacing was uneven (and the
         * fps plate read a rate no display was showing) */
        o->ren = SDL_CreateRenderer(o->win, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    if (!o->ren && (!dw4_gpu_policy_required() || diagnostic))
        o->ren = SDL_CreateRenderer(o->win, -1, SDL_RENDERER_SOFTWARE);
    if (!o->ren){dw4_gpu_policy_fail("accelerated SDL presentation unavailable");
        goto fail;
    }
    SDL_RendererInfo info;
    if(SDL_GetRendererInfo(o->ren,&info)<0)goto fail;
    if(dw4_gpu_policy_required() && !diagnostic){
        if(!(info.flags&SDL_RENDERER_ACCELERATED)){dw4_gpu_policy_fail("software SDL presentation rejected");goto fail;}
#ifdef DW4_ENABLE_GL
        if(SDL_GL_GetCurrentContext() && !dw4_gpu_policy_accept((const char *)glGetString(GL_RENDERER)))goto fail;
#endif
    }
    printf("  SDL presentation: %s%s\n",info.name?info.name:"unknown",diagnostic?" (explicit headless/dummy diagnostic)":"");
    /* dw4_fb stores R,G,B,A bytes; on a little-endian host that byte order is SDL's ABGR8888.
     * ARGB8888 names the *word* order, so it read our red as blue — the live window had R and B
     * swapped while the PNG (written from the same buffer) was correct. */
    o->tex = SDL_CreateTexture(o->ren, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, w, h);
    if (!o->tex)
        goto fail;
    /* The framebuffer's own alpha is whatever the rasteriser left there (the GL readback leaves it
     * ~0), so present it opaque: the RGB is the frame, the alpha is not a mask. */
    SDL_SetTextureBlendMode(o->tex, SDL_BLENDMODE_NONE);
    /* Open the first gamepad SDL sees.  SDL does not pick up a pad inserted later, so a pad that
     * appears after this window opens is never seen -- start the virtual pad before the port. */
    if (!headless) {
        int n = SDL_NumJoysticks(), i;
        for (i = 0; i < n; i++)
            if (SDL_IsGameController(i)) { o->pad = SDL_GameControllerOpen(i); break; }
        fprintf(stderr, "  window pad: %d joystick(s), %s\n", n,
                o->pad ? SDL_GameControllerName(o->pad) : "none opened");
    }
    if (o->pad) o->assigned_guid=SDL_JoystickGetGUID(SDL_GameControllerGetJoystick(o->pad));
    if (!headless) o->mates = dw4_matepads_open(o->pad);
    return o;
fail:
    fprintf(stderr, "window: SDL setup failed: %s\n", SDL_GetError());
    if (o->tex) SDL_DestroyTexture(o->tex);
    if (o->ren) SDL_DestroyRenderer(o->ren);
    if (o->win) SDL_DestroyWindow(o->win);
    free(o);
    SDL_Quit();
    return NULL;
}

int dw4_window_present(dw4_window *o, const dw4_fb *fb)
{
    if (!o || !fb || !fb->rgba || !o->tex)
        return -1;
    if (fb->w <= 0 || fb->h <= 0)
        return -1;
    /* Movies retain their decoded size even when the boot window is larger.
     * Size the upload texture to the source; SDL scales it into the window. */
    if (fb->w != o->w || fb->h != o->h) {
        SDL_Texture *tex = SDL_CreateTexture(o->ren, SDL_PIXELFORMAT_ABGR8888,
                                             SDL_TEXTUREACCESS_STREAMING, fb->w, fb->h);
        if (!tex)
            return -1;
        SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_NONE);
        SDL_DestroyTexture(o->tex);
        o->tex = tex;
        o->w = fb->w;
        o->h = fb->h;
    }
    if (SDL_UpdateTexture(o->tex, NULL, fb->rgba, fb->w * 4) != 0)
        return -1;
    if(SDL_RenderClear(o->ren)<0 || SDL_RenderCopy(o->ren,o->tex,NULL,NULL)<0){
        dw4_gpu_policy_fail("SDL presentation draw");return -1;
    }
    SDL_RenderPresent(o->ren);
    return 0;
}

int dw4_window_order_ok(dw4_window *o)
{
    int n, i, rc;
    uint8_t *buf, back[4];

    SDL_Rect one;
    if (!o)
        return -1;
    n = o->w * o->h;
    buf = (uint8_t *)malloc((size_t)n * 4);
    if (!buf)
        return -1;
    for (i = 0; i < n; i++) {                   /* a colour no path may reorder unnoticed */
        buf[4 * i + 0] = 200;
        buf[4 * i + 1] = 60;
        buf[4 * i + 2] = 20;
        buf[4 * i + 3] = 255;
    }
    rc = -1;
    /* read the backbuffer *before* present: after SDL_RenderPresent the content is undefined */
    if (SDL_UpdateTexture(o->tex, NULL, buf, o->w * 4) == 0) {
        SDL_RenderClear(o->ren);
        SDL_RenderCopy(o->ren, o->tex, NULL, NULL);
        one.x = o->w / 2; one.y = o->h / 2; one.w = 1; one.h = 1;
        if (SDL_RenderReadPixels(o->ren, &one, SDL_PIXELFORMAT_RGBA32, back, 4) == 0) {
            rc = (abs((int)back[0] - 200) <= 2 && abs((int)back[1] - 60) <= 2 &&
                  abs((int)back[2] - 20) <= 2) ? 1 : 0;
            if (rc == 0)
                printf("  window: readback r=%d g=%d b=%d a=%d (presented 200,60,20,255)\n",
                       back[0], back[1], back[2], back[3]);
        }
        SDL_RenderPresent(o->ren);
    }
    free(buf);
    return rc;
}

int dw4_window_pump(dw4_window *o, dw4_input_state *in) { return dw4_window_pump_mates(o, in, NULL); }

int dw4_window_pump_mates(dw4_window *o, dw4_input_state *in, dw4_input_state mates[3])
{
    SDL_Event e;
    if (!o)
        return 0;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            if (in)
                dw4_input_button(in, DW4_BTN_QUIT, 1);
            return 0;
        }
        if (e.type==SDL_WINDOWEVENT && e.window.windowID==SDL_GetWindowID(o->win)) {
            if (e.window.event==SDL_WINDOWEVENT_FOCUS_LOST || e.window.event==SDL_WINDOWEVENT_MINIMIZED) {
                o->focus_lost=1;
                if (in) { dw4_input_init(in);in->focus_pause=1; }
            }
            if (e.window.event==SDL_WINDOWEVENT_FOCUS_GAINED) o->focus_lost=0;
        }
        if (!in) continue;
        if (o->mates && dw4_matepads_event(o->mates, o->pad, &e, mates)) continue;   /* a co-op mate's pad */
        switch (e.type) {
        case SDL_KEYDOWN:
            if (!e.key.repeat && e.key.keysym.scancode==SDL_SCANCODE_P) {
                in->pause=1;break;
            }
            if (!e.key.repeat && e.key.keysym.scancode==SDL_SCANCODE_R) {
                in->resume=1;break;
            }
            if (!e.key.repeat) {
                int b = map_key(e.key.keysym.scancode);
                if (b)
                    dw4_input_button(in, b, 1);
            }
            break;
        case SDL_KEYUP: {
            int b = map_key(e.key.keysym.scancode);
            if (b)
                dw4_input_button(in, b, 0);
            break;
        }
        case SDL_CONTROLLERBUTTONDOWN: {
            int b = map_pad_button(e.cbutton.button);
            if (b)
                dw4_input_button(in, b, 1);
            break;
        }
        case SDL_CONTROLLERBUTTONUP: {
            int b = map_pad_button(e.cbutton.button);
            if (b)
                dw4_input_button(in, b, 0);
            break;
        }
        case SDL_CONTROLLERAXISMOTION:
            if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
                dw4_input_axis(in, DW4_AXIS_LX, e.caxis.value / 32767.0f);
            else if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
                dw4_input_axis(in, DW4_AXIS_LY, -(e.caxis.value / 32767.0f));   /* +y is up */
            else if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)
                dw4_input_button(in, DW4_BTN_L2, e.caxis.value > 16384);
            else if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
                dw4_input_button(in, DW4_BTN_R2, e.caxis.value > 16384);
            break;
        case SDL_CONTROLLERDEVICEADDED:
            /* SDL sees a pad appear only when it enumerates; open it if we have none */
            if (!o->pad && SDL_IsGameController(e.cdevice.which)) {
                SDL_JoystickGUID guid=SDL_JoystickGetDeviceGUID(e.cdevice.which);
                if (!o->disconnected || !memcmp(&guid,&o->assigned_guid,sizeof(guid))) {
                    o->pad=SDL_GameControllerOpen(e.cdevice.which);
                    if (o->pad) { o->assigned_guid=guid;o->disconnected=0; }
                }
            }
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            if (o->pad && e.cdevice.which ==
                SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(o->pad))) {
                SDL_GameControllerClose(o->pad);
                o->pad = NULL;
                o->disconnected=1;
                int focus_pause=in->focus_pause;
                dw4_input_init(in);in->focus_pause=focus_pause;
            }
            break;
        default:
            break;
        }
    }
    if (in) { in->focus_lost=o->focus_lost;in->disconnected=o->disconnected; }
    return 1;
}

void dw4_window_close(dw4_window *o)
{
    if (!o)
        return;
    if (o->pad) SDL_GameControllerClose(o->pad);
    dw4_matepads_close(o->mates);
    if (o->tex) SDL_DestroyTexture(o->tex);
    if (o->ren) SDL_DestroyRenderer(o->ren);
    if (o->win) SDL_DestroyWindow(o->win);
    free(o);
    SDL_Quit();
}

#else /* !DW4_ENABLE_SDL2 */

int dw4_window_built(void) { return 0; }
int dw4_window_order_ok(dw4_window *o) { (void)o; return -1; }
dw4_window *dw4_window_open(int w, int h, const char *title, int headless)
{
    (void)w; (void)h; (void)title; (void)headless;
    return NULL;
}
int dw4_window_present(dw4_window *win, const dw4_fb *fb) { (void)win; (void)fb; return -1; }
int dw4_window_pump(dw4_window *win, dw4_input_state *in) { (void)win; (void)in; return 1; }
int dw4_window_pump_mates(dw4_window *win, dw4_input_state *in, dw4_input_state mates[3]) { (void)win; (void)in; (void)mates; return 1; }
int dw4_window_key_button(int scancode) { (void)scancode; return 0; }
int dw4_window_pad_button(int sdl_button) { (void)sdl_button; return 0; }
void dw4_window_close(dw4_window *win) { (void)win; }

#endif /* DW4_ENABLE_SDL2 */
